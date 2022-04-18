#ifndef LPI_SOLVER_H
#define LPI_SOLVER_H
/*==============================================================================
  FILE:         lpi_solver.h
  
  OVERVIEW:     Determines the LPI mode to enter, based on a lookup
                table provided by SleepSynth.

  DEPENDENCIES: None

                Copyright (c) 2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/sleep2.0/src/solver/lpi_solver.h#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "comdef.h"
#include "lookup_table_types.h"
#include "SleepLPR_synth_modes.h"
#include "sleep_solveri.h"

/*==============================================================================
                             EXTERNAL VARIABLES
 =============================================================================*/
/**
 * @brief SleepLPI_power_lookup_table
 *
 * Master lookup table that contains data to select the correct island low power modes 
 * to enter based on allowable sleep time.
 */
extern sleep_lpiLut *SleepLPI_power_lookup_table[SLEEP_NUM_STATIC_FREQ];

/*==============================================================================
                              EXTERNAL FUNCTIONS
 =============================================================================*/
/** 
 * sleepLPISolver_initialize
 * 
 * @brief Solver init function
 */ 
uint32 sleepLPISolver_initialize(void);

/** 
 * sleepLPISolver_mainFunction
 * 
 * @brief Main solver function to select an island to enter. 
 *  
 * @note  It is assumed that an island has higher priority than any normal 
 *        low power mode.  As such, this function should be called and checked
 *        for valid output before solving for any normal mode. 
 *  
 * @param input:  List of constraints that are used by the solver 
 *                to select modes.
 * @param output: List of output data from the solver -- 
 *                contains the list of modes to enter, as well as
 *                the backoff time that should be used.
  
 * @return status of the solver
 */ 
solver_status sleepLPISolver_mainFunction(sleep_solver_input  *input,
                                          sleep_solver_output *output);

#endif /* LPI_SOLVER_H */

