/*==============================================================================
  FILE:         cache_lpr.c

  OVERVIEW:     This file provides the sleep LPR cache definition for the
                QDSP6 ALL WAIT low-power modes.

  DEPENDENCIES: None

                Copyright (c) 2013-2014,2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/sleep2.0/src/lpr/cache_lpr.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "comdef.h"
#include "sleep_target.h"
#include "sleep_hwio.h"
#include "q6_lpm_config.h"

/*===========================================================================
                              GLOBAL FUNCTIONS
 ==========================================================================*/
/** 
 * cacheLPR_l2RetentionEnter 
 *  
 * @brief Configure L2 for Retention
 */
void cacheLPR_L2RetentionEnter( uint64 wakeupTick )
{
  q6LPMConfig_setupL2Config(MEM_RET);
  return;
}

/** 
 * cacheLPR_l2NonRetentionEnter 
 *  
 * @brief Configure L2 for Non-Retention
 */
void cacheLPR_L2NonRetentionEnter( uint64 wakeupTick )
{
  q6LPMConfig_setupL2Config(MEM_NORET);
  return;
}

/** 
 * cacheLPR_L2NonRetentionExit
 *  
 * @brief Configure L2 for retention on exit
 */
void cacheLPR_L2NonRetentionExit( void )
{
  q6LPMConfig_setupL2Config(MEM_RET);
}

