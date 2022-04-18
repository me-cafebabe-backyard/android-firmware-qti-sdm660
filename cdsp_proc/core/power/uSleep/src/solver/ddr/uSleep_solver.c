/*==============================================================================
  FILE:         uSleep_solver.c

  OVERVIEW:     This file provides the support for the simple sover in normal mode

  DEPENDENCIES: Object file generated from source is marked as island section
  
                Copyright (c) 2014-2015 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/src/solver/ddr/uSleep_solver.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "DALStdDef.h"
#include "CoreVerify.h"
#include "uSleep_solver.h"
#include "uSleep_ddr_log.h"

/*==============================================================================
                             EXTERNAL VARIABLES
 =============================================================================*/
extern usleep_solver_fcn g_uSleepSolver;

/*==============================================================================
                          EXTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/*
 * uSleepSolver_setSolverFunction
 */ 
void uSleepSolver_setSolverFunction(usleep_solver_fcn function)
{
  CORE_VERIFY_PTR(function);

  uSleepDDRLog_printf(USLEEP_DDR_LOG_LEVEL_TRANSITION, 1,
                      "Setting uSolver (Fcn: 0x%x)",
                      (uint32)function);

  g_uSleepSolver = function;

  return;
}

