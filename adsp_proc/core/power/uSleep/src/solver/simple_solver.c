/*==============================================================================
  FILE:         simple_solver.c

  OVERVIEW:     This file provides the support for the simple sover

  DEPENDENCIES: Object file generated from source is marked as island section
  
                Copyright (c) 2014-2017 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/src/solver/simple_solver.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "DALStdDef.h"
#include "CoreVerify.h"
#include "uSleep_solver.h"
#include "uSleep_log.h"
#include "uSleep_lpr.h"
#include "uTimetick.h"
#include "qurt.h"

/*==============================================================================
                             INTERNAL VARIABLES
 =============================================================================*/
/* Chosen LPR mode for current sleep cycle. Initially set to APCR standalone. */
static uSleep_LPR *g_uSleepCurrentConfiguredLPR = &g_uSleepLPR[usleep_lpr_apcr_idx];

/*==============================================================================
                          EXTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/*
 * uSleepSolver_solve
 */
void simpleSolver_solve(uSleep_solver_input   *input, 
                        uSleep_solver_output  *output)
{
  const char  *LPRname        = "None";
  int32       idx             = USLEEP_NUMBER_LOW_POWER_MODES - 1;
  uint64      wakeupDeadline  = input->wakeupDeadline;
  uint64      now             = uTimetick_Get();
  uint64      duration        = wakeupDeadline - now;
  
  output->mode = NULL;

  if(wakeupDeadline < now)
  {
    return;
  }

  /* Start at highest index (most power savings) and work backwards */
  while(idx > USLEEP_LAST_CACHED_MODE)
  {
    if(duration > g_uSleepLPR[idx].latency)
    {
      output->mode = &g_uSleepLPR[idx];
      LPRname = g_uSleepLPR[idx].name;
      break;
    }
    idx--;
  }
 
  uSleepLog_printf(USLEEP_LOG_LEVEL_PROFILING, 1 + (1 * 2),
                   "Solver "
                   "(Duration: 0x%llX) (Mode: %s)",
                   MICRO_ULOG64_DATA(duration),
                   LPRname);

  return;
}

/*
 * simpleSolver_setActiveMode 
 */
void simpleSolver_setActiveMode(usleep_lpr_index index)
{
  boolean newCache;
  boolean currentCache;

  CORE_VERIFY(index < USLEEP_NUMBER_LOW_POWER_MODES);

  /* Get current and new LPR's cache mode */
  currentCache = g_uSleepCurrentConfiguredLPR->cached;
  newCache     = g_uSleepLPR[index].cached;

  uSleepLog_printf(USLEEP_LOG_LEVEL_PROFILING, 2,
                   "Set active mode "
                   "(Current: %s) "
                   "(Request: %s)",
                   g_uSleepCurrentConfiguredLPR->name,
                   g_uSleepLPR[index].name);

  /* If we are changing to a cached mode from an un-cached, run the cached enter
   * function */ 
  if(FALSE == currentCache &&
     TRUE == newCache)
  {
    /* Update current LPR first so cached enter function is run */
    g_uSleepCurrentConfiguredLPR = &g_uSleepLPR[index];

    /* Cached modes can not use wakeup time since we don't know it yet so pass 0 */
    uSleepLPR_runLPRFunctions(TRUE, 0, g_uSleepCurrentConfiguredLPR);

    /* Set override bit so APCR is entered immediately at all-wait */
    qurt_power_override_wait_for_idle(1);
  }
  else
  {
    /* If we are changing to an un-cached mode from a cached, run the cached
     * exit function first and then update the currently chosen mode. */
    if(TRUE == currentCache &&
       FALSE == newCache)
    {
      uSleepLPR_runLPRFunctions(FALSE, 0, g_uSleepCurrentConfiguredLPR);
      qurt_power_override_wait_for_idle(0);
    }

    /* Update current LPR */
    g_uSleepCurrentConfiguredLPR = &g_uSleepLPR[index];
  }

  return;
}