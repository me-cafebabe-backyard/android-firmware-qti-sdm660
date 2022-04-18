#ifndef SLEEP_SYNTH_H
#define SLEEP_SYNTH_H
/*==============================================================================
  FILE:         sleep_synth.h
  
  OVERVIEW:     Provides core public synth functions
  
  DEPENDENCIES: None
 
                Copyright (c) 2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/sleep2.0/inc/sleep_synth.h#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "comdef.h"

/*==============================================================================
                             FUNCTION DEFINITION
 =============================================================================*/
/**
 * synthLPI_updateLatency
 *
 * @brief Used to adjust the LPI latency times in the lookup table to optimize the 
 *        LPI solver 
 *  
 * @note It is assume there is only one LPI currently 
 *  
 * @param enterAdjustment:  Amount to adjust the enter latency of the LPI 
 * @param exitAdjustment:   Amount to adjust the exit latency of the LPI 
 */
void synthLPI_updateLatency(int32 enterAdjustment, int32 exitAdjustment);

/**
 * synthLPI_getCurrentLatency
 *
 * @brief Gets the current latency values of the LPI 
 *  
 * @note It is assume there is only one LPI currently 
 *  
 * @param enterLat:  Current enter latency
 * @param exitLat:   Current exit latency 
 * @param freqIdx:   Used to retreive the data for the given frequency index
 */
void synthLPI_getCurrentLatency(uint32 *enterLat, uint32 *exitLat, uint32 freqIdx);

#endif // SYNTHLPI_H

