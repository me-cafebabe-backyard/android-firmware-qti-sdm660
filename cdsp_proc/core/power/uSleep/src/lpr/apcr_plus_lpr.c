/*==============================================================================
  FILE:         apcr_plus_lpr.c

  OVERVIEW:     This file provides uSleep APCR+ LPR functions

  DEPENDENCIES: Object file generated from source is marked as island section
  
                Copyright (c) 2015-2017 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/src/lpr/apcr_plus_lpr.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "DALStdDef.h"
#include "CoreVerify.h"
#include "uSleep_lpr.h"
#include "uSleep_log.h"
#include "uSleep_target.h"
#include "uTimetick.h"
#include "utimer.h"
#include "qurt.h"
#include "AonInt.h"

/*==============================================================================
                       EXTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/* 
 * uSleepLPR_APCRPlusEnter
 */
void uSleepLPR_APCRPlusEnter(uint64 wakeupTime)
{
  /* Enable APCR with PMI */
  uSleepTarget_configPowerMode(TARGET_POWER_MODE_APCR, TRUE);

  /* Setup for retention mode */
  AonInt_RetentionEnter();

  /* Set wakeup timer */
  uSleepTarget_programWakeupTimer(wakeupTime);

  /* Enter all wait */
  qurt_power_apcr_enter();

  return;
}

/* 
 * uSleepLPR_APCRPlusExit 
 */
void uSleepLPR_APCRPlusExit(void)
{
  /* Disable wakeup timer */
  uSleepTarget_disableWakeupTimer();

  /* Call retention exit API */
  AonInt_RetentionExit();

  return;
}

