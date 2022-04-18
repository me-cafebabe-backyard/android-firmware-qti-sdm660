#ifndef SLEEPACTIVE_H
#define SLEEPACTIVE_H
/*==============================================================================
  FILE:         sleepActive.h

  OVERVIEW:     This file contains public APIs exposed by the Sleep Active-time 
                Solver Thread.

  DEPENDENCIES: None

                Copyright (c) 2014-2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/sleep2.0/inc/sleepActive.h#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "sleep_solver.h"

/*==============================================================================
                                GLOBAL TYPE DECLARATIONS
  =============================================================================*/ 
/* List of Signals that cause the Active Time solver 
 * to re-evaluate its selection of low-power modes */
typedef enum
{
  SLEEP_SIGNAL_CONTROL              = 0x0001,   /* Enable/Disable Active Time Solver  */
  SLEEP_SIGNAL_NORMAL_LATENCY       = 0x0002,   /* Update in Latency Constraint       */
  SLEEP_SIGNAL_SOFT_DURATION        = 0x0004,   /* Update Idle Soft Duration          */
  SLEEP_SIGNAL_REGISTRY             = 0x0008,   /* Update List of Enabled Synth Modes */
  SLEEP_SIGNAL_CPU_FREQUENCY        = 0x0010,   /* Cpu Frequency Change               */
  SLEEP_SIGNAL_HARD_DURATION        = 0x0020,   /* Update idle hard duration          */
  SLEEP_SIGNAL_RPM_QUEUE_CHANGE     = 0x0040,   /* RPM message queue is empty         */
  SLEEP_SIGNAL_ISLAND_LATENCY       = 0x0080,   /* Update in island mode latency constraint */
  SLEEP_SIGNAL_ISLAND_HARD_DURATION = 0x0100,   /* Same as HARD_DURATION above, just
                                                 * used to distinguish a specific island timer */
  SLEEP_SIGNAL_THRESHOLD_EXPIRED    = 0x0200,   /* Threshold timer expired, need to resolve */

  SLEEP_SIGNAL_LAST                 = 0x0400,   /* MUST BE LAST STANDARD SIGNAL */

  /*SPECIAL INTERNAL SIGNALS
   *  Mask for all normal signals */ 
  SLEEP_SIGNAL_MASK_ALL       = (SLEEP_SIGNAL_LAST - 1),

  /*  Control signal to indicate ATS init is complete. */
  SLEEP_SIGNAL_INIT_COMPLETE  = (SLEEP_SIGNAL_LAST << 1)
} sleepActive_SignalType;

/*==============================================================================
                              GLOBAL FUNCTION DECLARATIONS
  =============================================================================*/
/**
 * @brief Trigger signal(s) of type sig on Active Time solver thread
 *
 *        Signals set on the Active Time solver are used to determine 
 *        which execution conditions that have changed. 
 *        The Active Time solver thread executes the sleep solver to determine
 *        whether these modified inputs cause a change in the selection of 
 *        low-power mode.
 * 
 * @param signals: A single or bitwise OR of specific signals to be set
 *                 for Active Time solver to take action on
 */
void sleepActive_SetSignal(sleepActive_SignalType signals);

/**
 * @brief Returns the hard deadline times (in absolute ticks) that 
 *        were used by the solver to select the low power mode 
 *  
 * @return A pointer to the deadline data structure
 */
const sleep_solver_deadlines *sleepActive_GetSolverHardDeadlines(void);

/**
 * sleepActive_setRPMQueueStatus
 * 
 * @brief This function is called to indicate the state of the RPM message queue
 *  
 * @param isEmpty:  TRUE/FALSE value to indicate if the queue is empty or not 
 */
void sleepActive_setRPMQueueStatus(boolean isEmpty);

/**
 * sleepActive_clearThreasholdTimer
 * 
 * @brief Clears the threshold timer
 */
void sleepActive_clearThreasholdTimer(void);

#endif /* SLEEPACTIVE_H */

