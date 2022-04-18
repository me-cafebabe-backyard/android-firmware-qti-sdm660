#ifndef SLEEP_STATSDYNAMIC_H
#define SLEEP_STATSDYNAMIC_H
/*==============================================================================
  FILE:         sleep_stats_dynamic.h
  
  OVERVIEW:     Internal generic types to gather and adjust sleep statistics for 
                synth modes
 
  DEPENDENCIES: None
 
                Copyright (c) 2013-2015 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/sleep2.0/src/statistics/sleep_stats_dynamic.h#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "sleep_stats.h"
#include "sleep_stats_global.h"
#include "sleep_target.h"
#include "sleep_qr_types.h"

/*==============================================================================
                           INTERNAL TYPE DEFINITIONS
 =============================================================================*/
/** 
 * synth_LPRM_dyn_data
 * 
 * @brief Synthmode component based statistic data
 */
typedef struct synth_LPRM_dyn_data_s
{
  uint32                    backoff;      /* Adjusted synth LPRM backoff time */
  sleepStats_generic_signed wakeup_stats; /* Wakeup statistics for synth LPRM */
  uint32                    adjust_cnt;   /* Backoff adjustment count */
  sleepQR_synthMode         QR_data;      /* Quick response data for the synth */
}synth_LPRM_dyn_data;

/** 
 * synth_LPR_dyn_data
 * 
 * @brief Synthmode based statistic data
 */
typedef struct synth_LPR_dyn_data_s
{
  /* Noting to track on LPR basis yet */
}synth_LPR_dyn_data;

/** 
 * sleep_LPRM_dyn_data
 * 
 * @brief Sleep component mode based statistic data
 */
typedef struct sleep_LPRM_dyn_data_s
{
  /* sleep component LPRM time statistics
   * 
   * Exit stats are not represented here because there is currently not
   * enough information at runtime to determine proper exit latency.
   */
  sleepQR_componentMode QR_data; /* Quick response data strcuture for sleep LPRMs */
}sleep_LPRM_dyn_data;

/** 
 * synth_dyn_data
 * 
 * @brief Root data structure that holds synth based statistics
 */
typedef struct synth_dyn_data_s
{
  synth_LPR_dyn_data  LPR;
#ifdef SLEEP_ENABLE_AUTO_SYNTH_BACKOFF_ADJUSTMENT
  synth_LPRM_dyn_data LPRM[SLEEP_LPR_NUM_SYNTHESIZED_MODES];
#endif
}synth_dyn_data;

/** 
 * sleepStats_dynamic_data
 * 
 * @brief Master dynamic statistic data structure
 */
typedef struct sleepStats_dynamic_data_s
{
  synth_dyn_data          synth;                             /* Synth LPR(M)'s */
  sleep_LPRM_dyn_data     sleep_LPRM[SLEEP_NUM_TOTAL_LPRMS]; /* Component LPRM's */
}sleepStats_dynamic_data;

#endif /* SLEEP_STATSDYNAMIC_H */

