#ifndef SIMPLE_SOVER_H
#define SIMPLE_SOVER_H
/*==============================================================================
  FILE:         simple_solver.h

  OVERVIEW:     Prototypes & definitions for the simple solver

  DEPENDENCIES: None
  
                Copyright (c) 2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/src/solver/simple_solver.h#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "DALStdDef.h"
#include "uSleep_solver.h"

/*==============================================================================
                            FUNCTION DECLARATIONS
 =============================================================================*/
/** 
 * simpleSolver_solve
 * 
 * @brief Implementation of the simple solver that returns the power mode to enter
 *        given the wakeup deadline
 *   
 * @param input:  Various input parameters required to solver for a low power mode
 * @param output: Output paremters after running solver function
 */
void simpleSolver_solve(uSleep_solver_input *input, 
                        uSleep_solver_output *output);

/** 
 * simpleSolver_setActiveMode
 * 
 * @brief Set the active low power mode that will be executed the next time 
 *        the system goes idle
 *  
 * @param index: Enum of the desired low power mode 
 */
void simpleSolver_setActiveMode(usleep_lpr_index index);

#endif /* SIMPLE_SOVER_H */

