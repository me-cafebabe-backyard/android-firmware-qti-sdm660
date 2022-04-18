/*==============================================================================
  FILE:         uSleep_lpr_modes.c

  OVERVIEW:     This file contains the low power modes supported in island mode
               

  DEPENDENCIES: Object file generated from source is marked as island section
  
                Copyright (c) 2014-2015 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/src/lpr/uSleep_lpr_modes.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "DALStdDef.h"
#include "uSleep_lpr.h"
#include "uSleep_target.h"
#include "uSleep_os.h"

/*==============================================================================
                             INTERNAL VARIABLES
 =============================================================================*/
/* Supported LPR's in uSleep. Note that threshold values are not currently used. */
uSleep_LPR g_uSleepLPR[USLEEP_NUMBER_LOW_POWER_MODES] =
{
  /* APCR pll off 
   * Used when retention is explicitly disabled and will enable the override setting. */ 
  {"Cached APCR",                 /* LPR name */
    0,                            /* Enter + exit latency */  
    0,                            /* Backoff latency */         
    NULL,                         /* Init function */
    uSleepLPR_apcrCachedEnter,    /* Enter & exit functions for the LPR */
    NULL,                         /* Cacheable flag */
    TRUE},

  /* APCR with no wakeup timer
   * Does not set a wakeup time, and entered at idle time */
  {"APCR No Wake",
    300, 0,                          
    NULL, uSleepLPR_apcrNoWakeEnter, NULL, 
    FALSE},                     

  /* APCR pll off. Used when retention is enabled, but there is not enough time 
   * to enter it.
   * Wakeup timer requires 100uS for match value to set, disable requires additional 100uS to
   * clear the interrupt after setting match value. */ 
  {"APCR", 
    5850, 3875, 
    uSleepLPR_apcrInit, uSleepLPR_apcrEnter, uSleepLPR_apcrExit, 
    FALSE},

  /* APCR pll off + SSC retention */
  {"APCR+", 
    40000, 25400, /* Has timer delay's (3 sleep clocks) + PMIC delay + AON state/PLL time (~17.8k)*/
    NULL, uSleepLPR_APCRPlusEnter, uSleepLPR_APCRPlusExit,  
    FALSE}
};

