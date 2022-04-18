#ifndef LPR_SOLVER_H
#define LPR_SOLVER_H
/*==============================================================================
  FILE:         lpr_solver.h
  
  OVERVIEW:     Determines the LPR mode to enter, based on a lookup
                table provided by SleepSynth.

  DEPENDENCIES: None

                Copyright (c) 2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/sleep2.0/src/solver/lpr_solver.h#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "comdef.h"
#include "lookup_table_types.h"
#include "SleepLPR_synth_modes.h"
#include "sleep_solveri.h"

/*==============================================================================
                             EXTERNAL VARIABLES
 =============================================================================*/
/* Master lookup table that contains data to select the correct normal low power modes
 * to enter based on allowable sleep time. */
extern sleep_mLUT *SleepLPR_power_lookup_table[SLEEP_NUM_STATIC_FREQ];

/* Static frequency list from the XML inputs */
extern uint32 SleepLPR_static_freq_list[SLEEP_NUM_STATIC_FREQ];

/*==============================================================================
                              EXTERNAL FUNCTIONS
 =============================================================================*/
/** 
 * sleepLPRSolver_initialize
 * 
 * @brief Solver init function
 */ 
uint32 sleepLPRSolver_initialize(void);

/** 
 * sleepLPRSolver_mainFunction
 * 
 * @brief Main solver function to choose an LPR to enter based on the input
 *        constraints
 *
 * @param input:  Various input restrictions used to determine the power mode to enter 
 * @param output: Selected output mode and other data associated with the selected mode 
 *  
 * @return status of the solver 
 */ 
solver_status sleepLPRSolver_mainFunction(sleep_solver_input  *input,
                                          sleep_solver_output *output);

#endif /* LPR_SOLVER_H */

