#ifndef SLEEPACTIVEI_H
#define SLEEPACTIVEI_H
/*==============================================================================
  FILE:         sleepActivei.h

  OVERVIEW:     This file contains internal APIs exposed by the Sleep Active-time 
                Solver Thread.

  DEPENDENCIES: None

                Copyright (c) 2015-2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/sleep2.0/src/active/sleepActivei.h#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "comdef.h"
#include "sleep_solveri.h"
#include "synthTypes.h"

/*==============================================================================
                              GLOBAL FUNCTION DECLARATIONS
  =============================================================================*/
/**
 * @brief Returns the input parameters used by Sleep Active for 
 *        input to Active time solver
 *  
 * @return A pointer to the solver input struct
 */
sleep_solver_input *sleepActive_GetSolverInput(void);

/**
 * @brief Returns the low-power mode selected by Active time 
 *        solver
 *  
 * @return A pointer to the last chosen solver output struct
 */
sleep_solver_output *sleepActive_GetSolverOutput(void);

/**
 * @brief Configures what the main sleep task will execute when the subsystem 
 *        enters the idle state.
 *  
 * @param synthLPRM:  Selected mode to be entered at idle time 
 */
void sleepActive_configureIdleMode(sleep_synth_lprm *synthLPRM);

#endif /* SLEEPACTIVEI_H */

