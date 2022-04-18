/*==============================================================================
  FILE:         client_API.c

  OVERVIEW:     This file provides uSleep API functions for guest PD that are
                located in the ISLAND section

  DEPENDENCIES: None
  
                Copyright (c) 2014-2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/src/client/client_API.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "comdef.h"
#include "CoreVerify.h"
#include "uSleep.h"
#include "uSleepi.h"
#include "sleep_stats_global.h"
#include "sleep_pmi.h"
#include "uSleep_log.h"
#include "uSleep_util.h"
#include "uSleep_timer.h"
#include "uSleep_transi.h"
#include "uSleep_os.h"
#include "qurt.h"

/*==============================================================================
                         EXTERNAL FUNCTION REFERENCES
 =============================================================================*/
void uSleep_fatalErrorHandler(uSleep_internal_state state);

/*==============================================================================
                           TYPE & MACRO DEFINITIONS
 =============================================================================*/
/* Macros for locking/unlocking the mutex around uSleep API's that will change
 * internal states */ 
#define USLEEP_LOCK()  qurt_mutex_lock(&g_uSleepMutex);
#define USLEEP_FREE()  qurt_mutex_unlock(&g_uSleepMutex);

/*==============================================================================
                             INTERNAL VARIABLES
 =============================================================================*/
/* API lock */
qurt_mutex_t g_uSleepMutex;

/*==============================================================================
                       EXTERNAL GUEST SECTION FUNCTIONS
 =============================================================================*/
/*
 * uSleep_exit
 */
uint32 uSleep_exit(void)
{
  uSleep_internal_state       state;
  uint32                      pendingInt                              = qurt_system_vid_get();
  uSleep_transition_profiling *profileData                            = uSleep_getProfilingDataPtr();
  qurt_thread_t               taskID                                  = qurt_thread_get_id(); 
  
  /* Since we are modifying the uSleep state to exit, only allow one client to
   * do that at a time */
  uSleepLog_printf(USLEEP_LOG_LEVEL_TRANSITION, 2,
                   " Get exit mutex (Task: 0x%x) (VID: %u)",
                   taskID, pendingInt);

  USLEEP_LOCK();

  state = uSleep_getStateInternal();

  /* Check if we are in the middle of trying to enter island mode and someone
   * called exit */
  if(state & (uSLEEP_INTERNAL_STATE_STAGE1_ENTRY |
              uSLEEP_INTERNAL_STATE_STAGE2_ENTRY |
              uSLEEP_INTERNAL_STATE_FULL_ENTRY))
  {
    uSleepLog_printf(USLEEP_LOG_LEVEL_TRANSITION, 0, " Waiting for entry completion");

    /* Wait for entry to complete before exiting */
    uSleepTrans_enterSignalControl(USLEEP_TRANS_SIGNAL_WAIT);

    /* Update the internal state after waiting */
    state = uSleep_getStateInternal();
  }

  /* If we are currently active, turn on DDR and wait for full exit to happen */
  if(state & uSLEEP_INTERNAL_STATE_ACTIVE)
  {
    /* Record the start of the exit sequence */
    profileData->exit_start_time = uTimetick_Get();

    uSleepLog_QDSSPrintf(USLEEP_LOG_LEVEL_PROFILING, 
                         USLEEP_EXIT_START_NUM_ARGS,
                         USLEEP_EXIT_START_STR, 
                         USLEEP_EXIT_START,
                         pendingInt);

    /* Clear the existing uTimer that was created based on the first normal
     * mode non-deferrable timer. */
    uSleepTimer_clearTimer();

    /* Reset the exit signal so we can block the caller until uSleep has fully 
     * exited */
    uSleepTrans_exitSignalControl(USLEEP_TRANS_SIGNAL_CLEAR);

    /* Exit island mode */
    uSleepTrans_islandControl(UIMAGE_EXIT);

    /* Block until the system has fully transitioned back to normal operational
     * mode */
    uSleepTrans_exitSignalControl(USLEEP_TRANS_SIGNAL_WAIT);
  }
  else if(0 == (state & uSLEEP_INTERNAL_STATE_IN_DDR))
  {
    /* Must be in DDR state if we reached this point, otherwise something went wrong */
    uSleepLog_printf(USLEEP_LOG_LEVEL_TRANSITION, 1,
                     " ERROR: bad state on uSleep exit (State: 0x%x)",
                     state);

    uSleepOS_haltOnError();
  }

  uSleepLog_printf(USLEEP_LOG_LEVEL_TRANSITION, 1, 
                   " Give exit mutex (Task: 0x%x)",
                   taskID);

  USLEEP_FREE();

  return USLEEP_SUCCESS;
}

/*
 * uSleep_setLpmMode
 */
uint32 uSleep_setLowPowerMode(uSleep_power_mode mode)
{
  USLEEP_LOCK();
  uSleep_setLowPowerModeInternal(mode);
  USLEEP_FREE();

  return USLEEP_SUCCESS;
}

/*
 * uSleep_exitOnError
 */
void uSleep_exitOnError(void)
{
  uSleep_internal_state state = uSleep_getStateInternal();

  /* Call the target specific error handler */
  uSleep_fatalErrorHandler(state);
  return;
}

/*
 * uSleep_getCriticalExitTime
 */
uint64 uSleep_getCriticalExitTime(void)
{
  uSleep_internal_state state;
  uint64                exitTime = -1; /* Default to no critical exit time */
  
  state = uSleep_getStateInternal();

  /* If we are currently active, return the actual exit timer value */
  if(state & (uSLEEP_INTERNAL_STATE_ACTIVE        |
              uSLEEP_INTERNAL_STATE_FULL_ENTRY    |
              uSLEEP_INTERNAL_STATE_STAGE1_ENTRY  |
              uSLEEP_INTERNAL_STATE_STAGE2_ENTRY))
  {
    /* Return actual critical exit time */
    exitTime = uSleep_getDDRWakeupTimeInternal();
  }
  else if(state & (uSLEEP_INTERNAL_STATE_STAGE1_EXIT  |
                   uSLEEP_INTERNAL_STATE_STAGE2_EXIT  |
                   uSLEEP_INTERNAL_STATE_FULL_EXIT))
  {
    /* Exit has been requested, if a client asks, return 0 to indicate
     * they should not begin any work */
    exitTime = 0;
  }

  return exitTime;
}

/*
 * uSleep_isExitRequested
 */
boolean uSleep_isExitRequested(void)
{
  boolean               rtnVal  = FALSE;
  uSleep_internal_state state   = uSleep_getStateInternal();
  
  if(state & (uSLEEP_INTERNAL_STATE_STAGE1_EXIT |
              uSLEEP_INTERNAL_STATE_STAGE2_EXIT))
  {
    rtnVal = TRUE;
  }

  return rtnVal;
}
