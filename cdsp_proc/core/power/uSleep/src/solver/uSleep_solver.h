#ifndef USLEEP_SOVER_H
#define USLEEP_SOVER_H
/*==============================================================================
  FILE:         uSleep_solver.h

  OVERVIEW:     Functions for the uSleep solver

  DEPENDENCIES: None
  
                Copyright (c) 2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/src/solver/uSleep_solver.h#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "DALStdDef.h"
#include "uSleep_lpr.h"

/*==============================================================================
                             TYPES & DEFINITIONS
 =============================================================================*/
/* Solver input parameters */
typedef struct uSleep_solver_input_s
{
  uint64 wakeupDeadline;
}uSleep_solver_input;

/* Solver output parameters */
typedef struct uSleep_solver_output_s
{
  uSleep_LPR *mode;
}uSleep_solver_output;

/* Dynamic solver function type */
typedef void (*usleep_solver_fcn)(uSleep_solver_input *input, 
                                  uSleep_solver_output *output);

/*==============================================================================
                            FUNCTION DECLARATIONS
 =============================================================================*/
/** 
 * uSleepSolver_solve
 * 
 * @brief Internally sets and returns the un-cacheable mode that should be 
 *        entered with the allowed amount of sleep time.  Once called, only
 *        uSleepLPR_runLPRFunctions(...) is required to enter the chosen mode.
 *   
 * @param wakeupDeadline: Value (in absolute ticks) of the hard deadline wakeup 
 *                        time.
 */
void uSleepSolver_solve(uSleep_solver_input *input, 
                               uSleep_solver_output *output);

/** 
 * uSleepSolver_setSolverFunction
 * 
 * @brief Sets the uSleep low power mode solver function
 *   
 * @param function: Solver function to use when solving for a low power mode 
 *                  to enter                   
 */
void uSleepSolver_setSolverFunction(usleep_solver_fcn function);

#endif /* USLEEP_SOVER_H */

