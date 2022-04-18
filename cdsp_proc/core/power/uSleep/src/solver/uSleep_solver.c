/*==============================================================================
  FILE:         uSleep_solver.c

  OVERVIEW:     This file provides the support for the simple sover in island mode

  DEPENDENCIES: Object file generated from source is marked as island section
  
                Copyright (c) 2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/src/solver/uSleep_solver.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "DALStdDef.h"
#include "CoreVerify.h"
#include "uSleep_solver.h"
#include "uSleep_log.h"
#include "uSleep_lpr.h"

/*==============================================================================
                             FORWARD DECLRATIONS
 =============================================================================*/
static void uSleepSolver_defaultSolver(uSleep_solver_input  *input, 
                                       uSleep_solver_output *output);

/*==============================================================================
                             EXTERNAL VARIABLES
 =============================================================================*/
/* Dynamically registered solver function pointer */
usleep_solver_fcn g_uSleepSolver = uSleepSolver_defaultSolver;

/*==============================================================================
                              INTERNAL FUNCTIONS
 =============================================================================*/
/**
 * uSleepSolver_defaultSolver
 * 
 * @brief Default solver function that returns a NULL power mode
 * 
 * @return NULL
 */
static void uSleepSolver_defaultSolver(uSleep_solver_input  *input, 
                                       uSleep_solver_output *output)
{
  output->mode = NULL;
  return;
}

/*==============================================================================
                              EXTERNAL FUNCTION
 =============================================================================*/
/*
 * uSleepSolver_solve
 */
void uSleepSolver_solve(uSleep_solver_input   *input, 
                        uSleep_solver_output  *output)
{
  /* Call actual solver function */
  g_uSleepSolver(input, output);

  return;
}

