#ifndef USLEEP_TIMER_H
#define USLEEP_TIMER_H
/*==============================================================================
  FILE:         uSleep_timer.h

  OVERVIEW:     Internal types and definitions for the handling of the normal
                operational mode timer

  DEPENDENCIES: None
  
                Copyright (c) 2014-2015 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/src/transition/uSleep_timer.h#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "DALStdDef.h"

/*==============================================================================
                            DEFINITIONS & TYPES
 =============================================================================*/
#define DDR_TIMER_HANDLER_STACK_SIZE  768  /* Stack size for the timer handler task */
#define DDR_TIMER_HANDLER_PRIORITY    9     /* Pritory for the task */

/* Signal types for the timer task */
typedef enum uSleep_timer_signals
{
  USLEEP_TIMER_EXIT_EXPIRED     = 0x01, /* Adjusted DDR timer expired */
  USLEEP_TIMER_DURATION_CHANGED = 0x02, /* uTimer frame has changed */
}uSleep_timer_signals;

/*==============================================================================
                            FUNCTION DECLARATIONS
 =============================================================================*/
/**
 * uSleepTimer_init
 * 
 * @brief Initializes the uSleep timer handler task that will allow uSleep
 *        to exit early enough to service the first non-deferrable DDR timer.
 */
void uSleepTimer_init(void);

/**
 * uSleepTimer_setValue
 * 
 * @brief Adds a non-deferrable uTimer in order to exit uSleep mode in time to 
 *        service the DDR timer.
 *  
 * @param deadline: Absolute timer value in ticks
 */
void uSleepTimer_setValue(uint64 deadline);

/**
 * uSleepTimer_clearTimer 
 *  
 * @brief Clears the uTimer that was created from the normal mode timer.  This 
 *        function should be called on the exit transition. 
 */
void uSleepTimer_clearTimer(void);

/**
 * uSleepTimer_timerSignalTask 
 *  
 * @brief Main uSleep timer task that handles exiting island mode when a DDR 
 *        timer triggers the exit.   
 */
void uSleepTimer_timerSignalTask(void *ignored);

#endif /* USLEEP_TIMER_H */

