#ifndef SLEEP_SOLVER_H
#define SLEEP_SOLVER_H
/*==============================================================================
  FILE:         sleep_solver.h
  
  OVERVIEW:     This file declares the public types and functions to access data
                from the main sleep solver.

  DEPENDENCIES: None

                Copyright (c) 2015-2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/sleep2.0/inc/sleep_solver.h#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "comdef.h"

/*==============================================================================
                          GLOBAL TYPE DEFINITIONS
 =============================================================================*/
 /**
 * @brief sleep_solver_deadlines
 * 
 * Data structure to hold the various hard deadlines that the solver will use to 
 * select a low power mode. 
 */
typedef struct sleep_solver_deadlines_s
{
  uint64  island_timer; /* The time of the next non-deferrable island timer expiry */
  uint64  normal_timer; /* The time of the next non-deferrable normal-mode timer expiry */
  uint64  normal_min;   /* Minimum of all normal mode specific deadlines */
  uint64  overall_min;  /* Minimum of all island & normal mode deadlines */
} sleep_solver_deadlines;

#endif /* SLEEP_SOLVER_H */

