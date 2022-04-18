/*==============================================================================
  FILE:         apcr_lpr.c

  OVERVIEW:     This file provides uSleep APCR LPR functions

  DEPENDENCIES: Object file generated from source is marked as island section
  
                Copyright (c) 2014-2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/src/lpr/apcr_lpr.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "comdef.h"
#include "uSleep_lpr.h"
#include "qurt.h"
#include "uSleep_target.h"
#include "q6_lpm_config.h"

/*==============================================================================
                       EXTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/*
 * uSleepLPR_apcrInit
 */
void uSleepLPR_apcrInit(void)
{
  /* Enable APCR modes */
  q6LPMConfig_setupModeConfig(SPM_MODE_APCR_PLL_LPM, TRUE);
  return;
}

/*
 * uSleepLPR_apcrNoWakeEnter
 */
void uSleepLPR_apcrNoWakeEnter(uint64 wakeupTime)
{
  /* Configure for APCR without setting a wakeup time */
  uSleepTarget_configPowerMode(TARGET_POWER_MODE_APCR, TRUE);

  /* Enter all wait */
  qurt_power_apcr_enter();

  return;
}

/* 
 * uSleepLPR_apcrEnter 
 */
void uSleepLPR_apcrEnter(uint64 wakeupTime)
{
  /* Enable APCR with PMI */
  uSleepTarget_configPowerMode(TARGET_POWER_MODE_APCR, TRUE);

  /* Program the wakeup time */
  uSleepTarget_programWakeupTimer(wakeupTime);

  /* Enter all wait */
  qurt_power_apcr_enter();

  return;
}

/* 
 * uSleepLPR_apcrCachedEnter 
 */
void uSleepLPR_apcrCachedEnter(uint64 wakeupTime)
{
  /* In APCR cached mode, we do not need to run the exit function until
   * we change to an un-cached mode so disable the PMI interrupt. */
  uSleepTarget_configPowerMode(TARGET_POWER_MODE_APCR, FALSE);
  
  return;
}

/* 
 * uSleepLPR_apcrExit 
 */
void uSleepLPR_apcrExit(void)
{
  /* Disable wakeup timer */
  uSleepTarget_disableWakeupTimer();
  return;
}

