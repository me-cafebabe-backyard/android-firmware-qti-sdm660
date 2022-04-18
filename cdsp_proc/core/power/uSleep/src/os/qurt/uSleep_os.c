/*==============================================================================
  FILE:         uSleep_os.c

  OVERVIEW:     This file provides the main uSleep functions that reside in
                island memory space

  DEPENDENCIES: Object file generated from source is marked as island section
  
                Copyright (c) 2014-2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/src/os/qurt/uSleep_os.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "DALStdDef.h"
#include "CoreVerify.h"
#include "CoreTime.h"
#include "dog_hal.h"
#include "qurt.h"
#include "spm.h"
#include "utimer.h"
#include "uTimetick.h"
#include "uSleepi.h"
#include "sleep_stats_global.h"
#include "uSleep_util.h"
#include "uSleep_log.h"
#include "uSleep_lpr.h"
#include "sleep_os.h"
#include "uSleep_os.h"
#include "uSleep_transi.h"
#include "uSleep_solver.h"
#include "uSleep_target.h"

/*==============================================================================
                             INTERNAL VARIABLES
 =============================================================================*/
/* uSleep solver output data */
static uSleep_solver_output g_solverOutput;

/*==============================================================================
                            EXTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/* 
 * uSleepOS_performLPM
 */
uint32 uSleepOS_performLPM(void)
{
  uSleep_internal_state       state;
  uint64                      now;
  uSleep_solver_input         solverInput;

  /* Wait for all other HW threads to go idle.
   * 1. If override is set, we will enter all-wait when all threads go idle and
   *    this function does not return.
   * 2. If override is not set, this call will return when all threads go
   *    idle and we will be in STM 
   * 3. If the call is forced to return when the HW is not idle, the override bit
   *    setting is ignored, the function will return, but we will not be in STM.  This will
   *    typically be in the case where we want to exit island and we need to run a different
   *    sleep function in the sleep context. */ 
  if(qurt_power_wait_for_idle())
  {
    uSleepLog_printf(USLEEP_LOG_LEVEL_TRANSITION, 0,
                     "uSleep perform exit (Reason: wait for idle canceled)");

    /* Return value is currently meaningless, however just return a unique value different from 
     * other exit cases */
    return 2;
  }
 
  /* Refresh current state of uSleep to verify that an exit request has not been
   * made. */
  state = uSleep_getStateInternal();
  
  /* Check if the function pointer has changed or if an island exit has been requested and
   * simply return from this function.
   * The exit request state check should not be true, as the exit routines should have
   * forced an exit from the wait_for_idle call above, but the logic is here just in case. */
  if((uSleepOS_getIdleFunctionPtr() != uSleepOS_performLPM) ||
     (uSLEEP_INTERNAL_STATE_STAGE2_EXIT == state))
  {
    uSleepLog_printf(USLEEP_LOG_LEVEL_TRANSITION, 2,
                     "uSleep perform exit "
                     "(Reason: Function change or exit request) "
                     "(Fcn: 0x%x) "
                     "(state: 0x%x)",
                     (uint32)uSleepOS_getIdleFunctionPtr(),
                     state);

    /* Exit STM */
    qurt_power_exit();

    return 1;
  }

  uSleepLog_printf(USLEEP_LOG_LEVEL_PROFILING, 0, "uSleep cycle start");

  /* Get first timer to expire */
  solverInput.wakeupDeadline = utimer_get_first_non_deferrable_timer_expiry();

  uSleepLog_printf(USLEEP_LOG_LEVEL_PROFILING, (1*2),
                   "Wakeup deadline "
                   "(uTimer: 0x%llx) ",
                   MICRO_ULOG64_DATA(solverInput.wakeupDeadline));

  /* Solve and set the mode to enter. */
  uSleepSolver_solve(&solverInput, &g_solverOutput);
  
  if(NULL != g_solverOutput.mode)
  {
    /* Adjust wakeup time by LPRM backoff time */
    solverInput.wakeupDeadline -= g_solverOutput.mode->backoff;

    /* Defer the uImage timers */
    utimer_defer_match_interrupt_64();

    /* Last check to make sure we can enter the mode still. */
    now = uTimetick_Get();
    if(solverInput.wakeupDeadline <= now)
    {
      uSleepLog_printf(USLEEP_LOG_LEVEL_PROFILING, 0,
                       "Skipping LPM - wakeup in past");

      utimer_undefer_match_interrupt_64();

      /* Exit STM */
      qurt_power_exit();
      return 0;
    }

    /* Run the enter functions for the selected LPR that was previously chosen. */
    uSleepLPR_runLPRFunctions(TRUE, solverInput.wakeupDeadline, g_solverOutput.mode);
  }
  else
  {
    uSleepLog_printf(USLEEP_LOG_LEVEL_PROFILING, 0,
                     "Skipping LPM - no mode chosen");

    g_solverOutput.mode = NULL;

    /* Exit STM */
    qurt_power_exit();
  }

  return 0;
}

/*
 * uSleepOS_performLPMExit
 */
void uSleepOS_performLPMExit(void)
{
  uint64          STMExit;
  uint64          lastPMITime = uSleep_getLastPMITimestampInternal();
  unsigned int    interrupt   = qurt_system_vid_get();
  
  /* Verify that an exit funtion needs to be called */
  if(NULL != g_solverOutput.mode)
  {
    /* Run exit function */
    uSleepLPR_runLPRFunctions(FALSE, 0, g_solverOutput.mode);
  }
  
  g_solverOutput.mode = NULL; 

  /* Record STM exit time */
  STMExit = uTimetick_Get();

  /* Exit STM */
  qurt_power_exit();
  utimer_undefer_match_interrupt_64();

  uSleepLog_QDSSPrintf(USLEEP_LOG_LEVEL_PROFILING, 
                       USLEEP_MASTER_WAKEUP_NUM_ARGS,
                       USLEEP_MASTER_WAKEUP_STR, 
                       USLEEP_MASTER_WAKEUP,
                       interrupt,
                       MICRO_ULOG64_DATA(uSleep_getLastSleepWakeupInternal()),
                       MICRO_ULOG64_DATA(STMExit),
                       MICRO_ULOG64_DATA(lastPMITime));

  return;
}

/*
 * uSleepOS_performError
 */ 
uint32 uSleepOS_performError(void)
{
  /* Set via fatal error exit from uImage transition. This function should
   * NEVER be allowed to run from OS scheduler, but core verify just in case. */
  uSleepOS_haltOnError();

  return 1; /* Just here for compliance with prototype. */
}

/** 
 * uSleepOS_PMIPerformer
 * 
 * @brief Island mode version of the PMI interrupt handler routine.  
 */
void uSleepOS_PMIPerformer(void)
{
  uSleep_setLastPMITimestampInternal(uTimetick_Get());

  /* Call exit function */
  uSleepOS_performLPMExit();
  return;
}

/*
 * uSleepOS_setIdleFunctionPtr
 */
void uSleepOS_setIdleFunctionPtr(uSleep_idle_entry_ptr_type newIdleEntryPtr)
{
  /* Use main sleeps function pointer setting function since uSleep is
   * running in the sleep thread */
  sleepOS_setLPIEntryFunction((sleep_idle_entry_ptr_type)newIdleEntryPtr);
}

/*
 * uSleepOS_getIdleFunctionPtr
 */
uSleep_idle_entry_ptr_type uSleepOS_getIdleFunctionPtr(void)
{
  /* Use main sleeps API to retrieve the current LPI function */
  return ((uSleep_idle_entry_ptr_type)sleepOS_getLPIEntryFunction());
}

/*
 * uSleepOS_getIdleFunctionPtr
 */
void uSleepOS_enterIdle(void)
{
  /* Unmask global interrupt which was masked in
   * call to sleep_os_wait_for_idle() and places 
   * sleep task in ready queue. 
   * Returns when any other thread is awakened */
  qurt_power_wait_for_active();
  return;
}

/*
 * uSleepOS_haltOnError
 */
void uSleepOS_haltOnError(void)
{
  HAL_dogForceBite();
  while(1);
}

