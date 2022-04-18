/*==============================================================================
  FILE:         sleep_stats_cmn.c
  
  OVERVIEW:     Contains internal common variables and functions for the implementation 
                of sleep mode statistics and dynamic latency adjustments

  DEPENDENCIES: None

                Copyright (c) 2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/sleep2.0/src/statistics/sleep_stats_cmn.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "comdef.h"
#include "sleep_stats_global.h"
#include "sleep_utils.h"
#include "rpm_messageram.h"

/*==============================================================================
                      INTERNAL VARIABLE DECLARATIONS
 =============================================================================*/
/* RPM statistic pointer is located in uImage section so we can access that
 * data in either mode */
volatile rpm_master_stats_t *g_sleepStatsRPM = NULL;

/*==============================================================================
                       INTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/*
 * sleepStats_getRpmDataPtr
 */
volatile rpm_master_stats_t *sleepStats_getRpmDataPtr(void)
{
  return(g_sleepStatsRPM);
}

/*
 * sleepStats_updateValue
 */
void sleepStats_updateValue(sleepStats_generic *stats, uint64 value)
{
  stats->count++;
  stats->total = safe_unsigned_addition(stats->total, value);

  if(value > stats->max)
    stats->max = value;

  if(value < stats->min)
    stats->min = value;

  return;
}

