#ifndef USLEEP_TARGET_H
#define USLEEP_TARGET_H
/*==============================================================================
  FILE:         uSleep_target.h

  OVERVIEW:     Types & definitions target specific requirements for uSleep

  DEPENDENCIES: None
  
                Copyright (c) 2014-2017 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/src/target/uSleep_target.h#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "comdef.h"
#include "uSleep_lpr.h"
#include "uSleep.h"

/*==============================================================================
                                    TYPES
 =============================================================================*/
typedef enum target_power_mode
{
  TARGET_POWER_MODE_APCR      = 0,
  TARGET_POWER_MODE_CLOCKGATE
}target_power_mode;

/*==============================================================================
                            FUNCTION DECLARATIONS
 =============================================================================*/
/**
 * uSleepTarget_configPowerMode
 * 
 * @brief Configures the power mode to enter when the system goes idle
 * 
 * @param mode:       Configures for the desired power mode
 * @param enablePMI:  If TRUE, enables the PMI interrupt and runs the SW
 *                    LPRM exit sequence
 */
void uSleepTarget_configPowerMode(target_power_mode mode, boolean enablePMI);

/**
 * uSleepTarget_enterIdle
 * 
 * @brief Waits for the system to become active and performs the 
 *        pre-configured power mode.
 *  
 * @note  Clock gating should be configured before calling this function 
 */
void uSleepTarget_enterIdle(void);

/**
 * uSleepTarget_initialize
 *  
 * @brief Performs any target specific initializations 
 */
void uSleepTarget_initialize(void);

/**
 * uSleepTarget_programWakeupTimer
 *  
 * @brief Programs the wakeup time 
 *  
 * @param wakeupTime: Absolute value of the desired wakeup time 
 */
void uSleepTarget_programWakeupTimer(uint64 wakeupTime);

/**
 * uSleepTarget_disableWakeupTimer
 *  
 * @brief Disables the previously programed wakeup time 
 */
void uSleepTarget_disableWakeupTimer(void);

/**
 * uSleepTarget_enterLowPowerMode
 *  
 * @brief Enters a low power mode 
 *  
 * @param mode:       Low Power mode to enter 
 * @param wakeupTime: Absolute value of the desired wakeup time 
 */
void uSleepTarget_enterLowPowerMode(uSleep_LPR *mode, uint64 wakeupTime);

/**
 * uSleepTarget_exitLowPowerMode
 *  
 * @brief Exits the given low power mode 
 */
void uSleepTarget_exitLowPowerMode(uSleep_LPR *mode);

/**
 * uSleepTarget_setPMIHandler
 *  
 * @brief This should be called on the uImage transtion, while still 
 *        in normal mode, to point to a uImage PMI handler function. 
 */
void uSleepTarget_setPMIHandler(void);

/** 
 * uSleepTarget_enableIslandDebug
 * 
 * @brief Allows T32 to remain connected while in island mode
 *  
 * @note This function must be called outside of single threaded mode.
 *        
 * @param enable: Flag to inidate if island should be setup to allow 
 *                debug. 
 */
void uSleepTarget_enableIslandDebug(boolean enable);

/** 
 * uSleepTarget_configureIslandTransitionPowerMode
 * 
 * @brief Sets up an uncached low power mode to allow island entry. 
 *        This function will ensure no currently configured power mode will
 *        prevent island exit.
 *  
 * @param transition: Flag to indicate if we should configure the low power mode
 *                    that is entered during the island transition periods
 */
void uSleepTarget_configureIslandTransitionPowerMode(boolean transition);

/**
 * uSleepTarget_transitionNotificationCB
 * 
 * @brief Internal target specific transition callback function that 
 *        performs setup/cleanup when the island entry/exit occurs
 * 
 * @param state: Indicates if uImage is entering or exiting
 */
void uSleepTarget_transitionNotificationCB(uSleep_state_notification state);

#endif /* USLEEP_TARGET_H */

