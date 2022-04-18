#ifndef SLEEP_TARGET_H
#define SLEEP_TARGET_H
/*==============================================================================
  FILE:         sleep_target.h
  
  OVERVIEW:     This file provides the externs and declarations needed for
                target specific code

  DEPENDENCIES: None

                Copyright (c) 2012-2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/sleep2.0/src/sleep_target.h#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "comdef.h"
#include "sleepi.h"
#include "spm.h"
#include "DDIChipInfo.h"
#include "sleep_solver.h"

/*==============================================================================
                             TYPE DEFINITIONS
 =============================================================================*/
/**
 * @brief Used to enumerate l2 lprm configuration
 */
typedef enum{
  L2_TCM_RET,       /* Config processor SS & L2 for L2 ret & TCM ret          */
  L2_TCM_NORET,     /* Config processor SS & L2 for L2 non-ret & TCM non-ret  */
  L2_NORET,         /* Config processor SS & L2 for L2 non-ret & TCM ret      */
  L2_NUM_RET_MODES  /* Total number of retention modes                        */
} l2_lprm;

/**
 *  @brief target config data returned by sleepTarget_initialize()
 */
typedef struct 
{
  DalChipInfoFamilyType   chip_family;    /* Chip family architecture*/
  DalChipInfoVersionType  chip_ver;       /* Chip architecture version */
  uint32                  l2_mask;        /* Mask for L2 Cache Power Ctl */
  uint32                  tcm_mask;       /* Mask for TCM Power Ctl */
} sleep_target_config;

/*==============================================================================
                             EXTERNAL FUNCTIONS
 =============================================================================*/
/**
 * sleepTarget_getHardWakeupTime
 * 
 * @brief Returns the amount of time until the next timer expiration. This is used
 *        to further decide on which low-power mode(s) can be entered.
 *
 * @param deadlines: Data strcuture pointer that will be populated with the first
 *                   absolute time (in ticks) of the various hard deadlines
 */ 
void sleepTarget_getHardWakeupTime(sleep_solver_deadlines *deadlines);

/**
 * @brief sleepTarget_initialize
 * 
 * Perform target-specific initialization of the sleep subsystem.
 */
void sleepTarget_initialize(void);

/**
 * @brief sleepTarget_initializeLPR 
 *  
 * Do target-specific initialization for the /sleep/lpr node.
 * This initialization will happen before the node is available
 * to the outside world.
 */
void sleepTarget_initializeLPR(void);

/**
 * @brief sleepTarget_enableSleepTimer
 *  
 * Set the timer match value hardware register to expire after
 * ticks amount of time. 
 * 
 * Function implementaion is defined by type of unerlying processor
 * Q6    : Converts ticks to sclks and programs IDLT
 * Others: Programs the SLEEP QTimer
 *
 * Any software overhead that is required before and after the actual 
 * sleep timer expires will have to be taken into account.
 *
 * @param wakeupTick : Absolute time in 19.2MHz ticks when wakeup 
 *                       should be programmed.
 *  
 * @return Actual wakeup time programed
 */
uint64 sleepTarget_enableSleepTimer(uint64 wakeupTick);

/**
 * @brief sleepTarget_disableSleepTimer
 *  
 * Disables any Timer Hardware that was programmed to wake-up
 * the processor.
 * 
 * Function implementaion is defined by type of unerlying processor
 * Q6    : Converts ticks to sclks and programs IDLT
 * Others: Programs the SLEEP QTimer
 *
 * 
 */
void sleepTarget_disableSleepTimer(void);

/**
 * @brief sleep function to enable DOG AUTOKICK
 */
void sleepTarget_enableWatchdog(void);

/**
 * @brief sleep function to disable DOG AUTOKICK
 */
void sleepTarget_disableWatchdog(void);


/**
 * @brief Gets the current CPU family & version
 *  
 * @param chipFamily: Return value with family of chip
 * @param chipVer: Return value with version of chip
 */
void sleepTarget_getCPUArchitecture(DalChipInfoFamilyType  *chip_family, 
                                    DalChipInfoVersionType *chip_ver);

/**
 * sleepTarget_setRPMAssistedMode
 *
 * @brief Sets an indicator if the RPM LPR enter/exit functions have been 
 * executed as part of the current synth mode 
 *  
 * This function should only be called from the RPM LPR functions. 
 *  
 * @param value: TRUE or FALSE to indicate if in RPM assisted mode 
 */
void sleepTarget_setRPMAssistedMode(boolean value);

/**
 * sleepTarget_getRPMAssistedMode
 *
 * @brief Retreives the value previously set by the "set" function that 
 * indicates if an RPM synth mode was selected for entry. 
 *
 * This function is mainly useful to the CPU VDD LPR to determine if we are 
 * in an RPM assised synth mode 
 *  
 * @return: TRUE or FALSE to indicate if we have entered RPM assisted mode
 */
boolean sleepTarget_getRPMAssistedMode(void);

/**
 * sleepTarget_getRPMStatisticsAddress
 *
 * @brief Gets the memory pointer to the shared memory location
 * of the RPM statistics data 
 *  
 * @return: Pointer to data
 */
void *sleepTarget_getRPMStatisticsAddress(void);

/**
 * sleepTarget_performInitialLPRExit
 *
 * @brief Performs any target specfic exit requirements prior to executing 
 *        the LPRM exit routines.  It is expected to call this function as
 *        early as possible in the sleep exit from power collapse routines. 
 */
void sleepTarget_performInitialLPRExit(void);

/**
 * sleepTarget_setRpmHandshake
 *
 * @brief Controls the SPM-RPM handshakeing 
 *  
 * @param performHandshake: Boolean value to enable or disable the RPM handshake 
 *                          at power collapse 
 *  
 * @return SPM results
 */
spm_result_t sleepTarget_setRpmHandshake(boolean performHandshake);

/**
 * sleepTarget_setSpmLowPowerMode
 *
 * @brief Controls the power mode that SPM will enter
 *  
 * @param coreMode: Power mode to setup
 *  
 * @return SPM results
 */
spm_result_t sleepTarget_setSpmLowPowerMode(spm_low_power_mode_type coreMode);

/**
 * sleepTarget_isInterruptPending
 *
 * @brief Checks if a particular interrupt is pending 
 *  
 * @param intNumber: Interrupt vector to check 
 *  
 * @return: TRUE if interrupt is pending, else FALSE
 */
boolean sleepTarget_isInterruptPending(uint32 intNumber);

/**
 * sleepTarget_setDefaultPowerMode
 *
 * @brief Sets a default power mode to enter should the sub-system enter the idle state. 
 *        This mode should be the most basic and quickest to enter.  Typically it will be
 *        clock gating.
 *  
 * @note When un-setting the default mode, the function will take into account any required setting 
 *       changes for the currently selected actual power mode to enter.  The intention of this function
 *       is to only be called from the ATS logic.
 *  
 * @param enable: Boolean to enable or disable the default mode 
 */
void sleepTarget_setDefaultPowerMode(boolean enable);

#endif //SLEEP_TARGET_H

