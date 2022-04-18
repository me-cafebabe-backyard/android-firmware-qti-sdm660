/*==============================================================================
  FILE:         rpm_lpr.c

  OVERVIEW:     This file provides the LPR definition for the RPM  
                low-power modes.

  DEPENDENCIES: None

                Copyright (c) 2011-2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/sleep2.0/src/lpr/rpm_lpr.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "comdef.h"
#include "rpm.h"
#include "rpmclient.h"
#include "sleep_log.h"
#include "sleep_target.h"

/*==============================================================================
                              INTERNAL VARIABLES
 =============================================================================*/
static uint32 g_nasResult;
static uint32 g_ssResult;

/*==============================================================================
                              INTERNAL FUNCTIONS
 =============================================================================*/
/**
 * RPMSyncLPR_enter
 *
 * @brief Enter function for RPM synchronization low power mode.
 */
void RPMSyncLPR_enter( uint64 wakeupTick )
{
  /* Enable RPM handshaking */
  sleepTarget_setRpmHandshake(TRUE);

  g_ssResult = rpm_force_sync(RPM_SLEEP_SET);

  sleepLog_QDSSPrintf(SLEEP_LOG_LEVEL_INFO, SLEEP_SET_SEND_NUM_ARGS,
                      SLEEP_SET_SEND_STR, SLEEP_SET_SEND);

  g_nasResult = rpm_force_sync(RPM_NEXT_ACTIVE_SET);

  if(g_ssResult || g_nasResult)
  {
    rpm_mask_interrupt(true);
  }

  return;
}

/**
 * RPMSyncLPR_exit
 *
 * @brief Exit function for RPM synchronization low power mode.
 */
void RPMSyncLPR_exit( void )
{
  /* Ensure churn_queue uses g_nasResult if valid, else g_ssResult */
  rpm_churn_queue(g_nasResult?g_nasResult:g_ssResult);

  if(g_ssResult || g_nasResult)
  {
    rpm_mask_interrupt(false);
  }

  /* Disable RPM handshakeing */
  sleepTarget_setRpmHandshake(FALSE);

  return;
}

