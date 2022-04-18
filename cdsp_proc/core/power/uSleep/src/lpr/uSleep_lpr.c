/*==============================================================================
  FILE:         uSleep_lpr.c

  OVERVIEW:     This file contains the low power modes related support functions 

  DEPENDENCIES: Object file generated from source is marked as island section
  
                Copyright (c) 2014-2015 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/src/lpr/uSleep_lpr.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "DALStdDef.h"
#include "CoreVerify.h"
#include "uSleep_lpr.h"
#include "uSleep_log.h"
#include "uSleep_target.h"

/*==============================================================================
                          EXTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/*
 * uSleepLPR_runLPRFunctions 
 */
void uSleepLPR_runLPRFunctions(boolean    enterFunction,
                               uint64     wakeupDeadline,
                               uSleep_LPR *mode)
{
  if(TRUE == enterFunction)
  {
    if(NULL != mode->enter_func)
    {
      uSleepTarget_enterLowPowerMode(mode, wakeupDeadline);
    }
  }
  else
  {
    if(NULL != mode->exit_func)
    {
      uSleepTarget_exitLowPowerMode(mode);
    }
  }

  return;
}

/* 
 * uSleepLPR_init
 */
void uSleepLPR_init(void)
{
  uint32      nLPR;
  uSleep_LPR  *LPRPtr;

  uSleepLog_printf(USLEEP_LOG_LEVEL_PROFILING, 0,
                   "Init uSleep LPR");

  for(nLPR=0; nLPR < USLEEP_NUMBER_LOW_POWER_MODES; nLPR++)
  {
    LPRPtr = &g_uSleepLPR[nLPR];
    CORE_VERIFY_PTR(LPRPtr);

    if(NULL != LPRPtr->init_func)
    {
      /* Call each LPR's init function */
      LPRPtr->init_func();
    }
  }

  return;
}

