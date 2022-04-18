/*==============================================================================
  FILE:         uSleep_util.c

  OVERVIEW:     This file provides uSleep helper functions that are located in
                island memory space

  DEPENDENCIES: Object file generated from source is marked as island section
  
                Copyright (c) 2014-2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/src/util/uSleep_util.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "comdef.h"
#include "CoreVerify.h"
#include "qurt.h"
#include "uSleepi.h"
#include "uSleep_log.h"
#include "simple_solver.h"
#include "uSleep_timer.h"
#include "uSleep_util.h"

/*==============================================================================
                             GLOBAL VARIABLES
 =============================================================================*/
/* Main uSleep data structure that stores state & other internal data */
uSleep_global_data g_uSleepData = {0};

/* State change locking mutext */
qurt_mutex_t g_uSleepStateMutex;

/*==============================================================================
                           TYPE & MACRO DEFINITIONS
 =============================================================================*/
/* Macros for locking/unlocking the mutex around uSleep API's that will change
 * internal states */ 
#define USLEEP_STATE_LOCK()  qurt_mutex_lock(&g_uSleepStateMutex);
#define USLEEP_STATE_FREE()  qurt_mutex_unlock(&g_uSleepStateMutex);

/*==============================================================================
                       EXTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/*
 * uSleep_setStateInternal
 */
void uSleep_setStateInternal(uSleep_internal_state state)
{
  /* Only one state can be set, so ensure only 1 bit is set */
  CORE_VERIFY(state == (state & -state));

  USLEEP_STATE_LOCK();
  g_uSleepData.state = state;
  USLEEP_STATE_FREE();

  return;
}

/*
 * uSleep_getStateInternal
 */
uSleep_internal_state uSleep_getStateInternal(void)
{
  uSleep_internal_state state;

  USLEEP_STATE_LOCK();
  state = g_uSleepData.state;
  USLEEP_STATE_FREE();

  return (state);
}

/*
 * uSleep_getDDRWakeupTimeInternal
 */
uint64 uSleep_getDDRWakeupTimeInternal(void)
{
  return(g_uSleepData.ddr_wakeup_timer);
}

/*
 * uSleep_setLastSleepWakeupInternal
 */
void uSleep_setLastSleepWakeupInternal(uint64 wakeupTime)
{
  g_uSleepData.last_wakeup_timestamp = wakeupTime;
}

/*
 * uSleep_getLastPMITimestampInternal
 */
uint64 uSleep_getLastPMITimestampInternal(void)
{
  return(g_uSleepData.last_pmi_timestamp);
}

/*
 * uSleep_setLastPMITimestampInternal
 */
void uSleep_setLastPMITimestampInternal(uint64 PMITime)
{
  g_uSleepData.last_pmi_timestamp = PMITime;
}

/*
 * uSleep_getLastSleepWakeupInternal
 */
uint64 uSleep_getLastSleepWakeupInternal(void)
{
  return(g_uSleepData.last_wakeup_timestamp);
}

/*
 * uSleep_setLowPowerModeInternal
 */
void uSleep_setLowPowerModeInternal(uSleep_power_mode mode)
{
  uSleep_internal_state state;

  CORE_VERIFY(mode < USLEEP_LPM_MAX_MODE);

  state = uSleep_getStateInternal();

  /* Only change power mode setting if we are active or entering. */
  if(state & (uSLEEP_INTERNAL_STATE_ACTIVE      |
              uSLEEP_INTERNAL_STATE_FULL_ENTRY))
  {
    /* Set the mode */
    g_uSleepData.low_power_mode = mode;

    if(USLEEP_LPM_PLUS_DISABLE == mode)
    {
      /* If the LPM+ is disabled, set the current LPR mode to cached mode so it's entered
       * immediately */ 
      simpleSolver_setActiveMode(usleep_lpr_cached_idx);
    }
    else
    {
      /* Set to un-cached mode so the cached exit function is run. Actual mode
       * entered will be selected when system goes idle. */
      simpleSolver_setActiveMode(usleep_lpr_apcr_idx);
    }
  }

  return;
}

/*
 * uSleep_getLowPowerModeInternal
 */
uSleep_power_mode uSleep_getLowPowerModeInternal(void)
{
  return(g_uSleepData.low_power_mode);
}

/*
 * uSleep_getProfilingDataPtr
 */
uSleep_transition_profiling* uSleep_getProfilingDataPtr(void)
{
  return &g_uSleepData.transition_data;
}

