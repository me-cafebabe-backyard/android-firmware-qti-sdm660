#ifndef USLEEP_MODE_TRANS_H
#define USLEEP_MODE_TRANS_H
/*==============================================================================
  FILE:         uSleep_mode_trans.h

  OVERVIEW:     Provides the public API functions and types to support
                normal <-> island transitions

  DEPENDENCIES: The build option for island must be enabled
  
                Copyright (c) 2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/api/power/uSleep/uSleep_mode_trans.h#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "comdef.h"

/*==============================================================================
                              DEFINES & TYPES
 =============================================================================*/
/* Enumeration for the uSleep notification callback function parameter */
typedef enum uSleep_state_notification
{
  USLEEP_STATE_ENTER = 0,  /* uSleep mode is about to be entered */
  USLEEP_STATE_EXIT        /* uSleep mode has been exited */
}uSleep_state_notification;

/* Handle to registered callback notification function */
typedef uint32 uSleep_notification_cb_handle; 

/* Callback notification function prototype */
typedef void (*uSleep_notification_cb_type)(uSleep_state_notification state);

/*==============================================================================
                      MAIN uSLEEP FUNCTION DECLARATIONS
 =============================================================================*/
/** 
 * uSleep_exit
 * 
 * @brief Explicitly exit uSleep mode. The caller will be blocked while DDR is
 *        enabled and the exit process continues at the next idle period.
 * 
 * @note This function only exits uSleep mode, it will not disable it and
 *       uSleep could be entered again on the next sleep cycle.
 *       It is only intended to be called while in uImage mode; calling it
 *       in normal operational mode has no effect.
 * 
 * @return USLEEP_SUCCESS or USLEEP_FAILURE
 */
uint32 uSleep_exit(void);

/** 
 * uSleep_exitOnError
 * 
 * @brief Explicitly exit uSleep mode without calling function callbacks or 
 *        performing any of the normal exit routines.  It will block the
 *        caller while the exit process occurs.
 *  
 * @note This function is intended to ONLY be called from the OS in a 
 *       FATAL ERROR case. It does not allow reentry into any type of sleep
 *       modes and will loop forever if system is allowed to enter the idle
 *       state again.
 *  
 *       It is only intended to be called while in uImage mode.
 */
void uSleep_exitOnError(void);

/** 
 * uSleep_registerNotificationCallback
 * 
 * @brief Registers a client callback function for notification when uSleep 
 *        is entered or exited 
 *  
 * @note  This function must be called only once during initialization, while 
 *        in normal operational mode.
 *  
 *        The registered function will be called while in single threaded
 *        mode and must not invoke other threads or otherwise exit STM.
 * 
 *        The registered function should be as minial as possible to keep the
 *        transtion times as fast as possible. 
 *     
 *  
 * @param enterLat: Time in ticks taken to execute the CB when entering uImage
 * @param exitLat:  Time in ticks taken to execute the CB when exiting uImage
 * @param callback: Function to be called
 *  
 * @return Handle of registered function; 0 = error
 */
uSleep_notification_cb_handle uSleep_registerNotificationCallback(
                                uint32                      enterLat,
                                uint32                      exitLat,
                                uSleep_notification_cb_type callback);

/** 
 * uSleep_getCriticalExitTime
 * 
 * @brief Returns the absolute time (in ticks) at which uSleep will automatically 
 *        trigger an island exit due to a normal operational mode timer. Thread
 *        processing should not occur past this time or the normal mode timer
 *        service may be delayed.
 *  
 * @return The absolute value (in ticks) of the time that uSleep will 
 *         initiate island exit.
 *  
 *         If not in island mode, the value is not valid, and will be -1 to indicate
 *         a critical deadline infinitely in the future
 *  
 *         If an exit request is already in progress, the value will be 0 to indicate
 *         a critical deadline in past and the caller should stop processing work immediatly.  
 */ 
uint64 uSleep_getCriticalExitTime(void);

/** 
 * uSleep_isExitRequested
 * 
 * @brief Used to determine if there is a current request to exit island.  
 *  
 * @return  TRUE: An exit request exists and the caller should stop processing as soon as possible to prevent
                  delaying the exit
            FALSE: No exit has been requested
 */ 
boolean uSleep_isExitRequested(void);

#endif /* USLEEP_MODE_TRANS_H */

