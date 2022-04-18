#ifndef SLEEP_STATS_GLOBAL_H
#define SLEEP_STATS_GLOBAL_H
/*==============================================================================
  FILE:         sleep_stats_global.h
  
  OVERVIEW:     Internal functions & types for global interest statistic data
 
  DEPENDENCIES: User should not include this file directly and should use 
                the master file "sleep_stats.h"
                
                Copyright (c) 2014-2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/sleep2.0/inc/sleep_stats_global.h#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "comdef.h"
#include "rpm_messageram.h"

/*==============================================================================
                                TYPE DEFINITIONS
 =============================================================================*/
/**
 * sleepStats_generic
 *
 * @brief Basic statistics data structure
 */
typedef struct sleepStats_generic_s
{
  uint32  count;  /* measurement count */
  uint64  total;  /* measurement total */
  uint64  max;    /* measurement maximum value */
  uint64  min;    /* measurement minimum value*/
}sleepStats_generic;

/**
 * sleepStats_generic_signed
 *
 * @brief Basic SIGNED statistics data structure
 */
typedef struct sleepStats_generic_signed_s
{
  uint32  count;  /* measurement count */
  int64   total;  /* measurement total */
  int64   max;    /* measurement maximum value */
  int64   min;    /* measurement minimum value*/
}sleepStats_generic_signed;

/*==============================================================================
                              FUNCTION DECLARATIONS
 =============================================================================*/
/**
 * sleepStats_getRpmDataPtr
 *
 * @brief Returns the RPM shared memory statistics location
 */
volatile rpm_master_stats_t *sleepStats_getRpmDataPtr(void);

/** 
 * sleepStats_updateValue
 *  
 * @brief Update data fields of the generic statistics structure
 *        
 * @param stats: Pointer to generic data structure to update
 * @param value: Value that will be used for the update
 */
void sleepStats_updateValue(sleepStats_generic *stats, uint64 value);

/** 
 * sleepStats_updateSignedValue
 *  
 * @brief Updates the data fields for the generic SIGNED statistics structure
 *        
 * @param stats: Pointer to generic SIGNED data structure to update
 * @param value: Value that will be used for the update
 */
void sleepStats_updateSignedValue(sleepStats_generic_signed *stats,
                                  int64                     value);

#endif /*SLEEP_STATS_GLOBAL_H*/

