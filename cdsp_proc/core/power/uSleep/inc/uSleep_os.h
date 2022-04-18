#ifndef USLEEP_OS_H
#define USLEEP_OS_H
/*==============================================================================
  FILE:         uSleep_os.h

  OVERVIEW:     Provides main OS API intface functions and types for uSleep

  DEPENDENCIES: None
 
                Copyright (c) 2014-2017 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/inc/uSleep_os.h#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "DALStdDef.h"

typedef enum
{
   CLK_DISABLE = 0,
   CLK_ENABLE
}clock_enablement_type;

/* Q6 AXI clock*/
#define GCC_LPASS_Q6_AXI_CBCR  "gcc_lpass_q6_axi_clk"

/* Q6 SPM clock*/
#define LPASS_Q6_SPM_CLOCKS    "island_scc_q6_spm_clk"

/*==============================================================================
                              DEFINES & TYPES
 =============================================================================*/
/**
 * uSleep_idle_entry_ptr_type
 *
 * @brief Function pointer type for different behaviors when processor goes
 *        idle during uSleep interaction.
 */
typedef uint32 (*uSleep_idle_entry_ptr_type)(void);

/*==============================================================================
                            FUNCTION DECLARATIONS
 =============================================================================*/
/** 
 * uSleepOS_mainEntry
 *  
 * @brief This function is the main entry into uSleep mode. It will switch to 
 *        uSleep when restrictions allow it.
 *  
 * @return 0
 */
uint32 uSleepOS_mainEntry(void);

/** 
 * uSleepOS_PMIPerformer
 * 
 * @brief Island mode version of the PMI interrupt handler routine.  
 */
void uSleepOS_PMIPerformer(void);

/** 
 * uSleepOS_enterIdle
 * 
 * @brief Waits for the system to become active and performs the currently 
 *        setup power mode.
 *  
 * @note Clock gating should be setup prior to calling this function 
 */
void uSleepOS_enterIdle(void);

/** 
 * uSleepOS_haltOnError
 * 
 * @brief Called when the system is unable to return to DDR mode.
 */
void uSleepOS_haltOnError(void);

/** 
 * uSleepOS_performLPM
 * 
 * @brief Main uSleep function in island mode that will enter low power modes.
 */
uint32 uSleepOS_performLPM(void);

/** 
 * uSleepOS_performLPMExit
 * 
 * @brief Handles exiting LPR modes 
 */
void uSleepOS_performLPMExit(void);

/**
 * uSleepOS_setIdleFunctionPtr
 *
 * @brief This function sets the idle entry point used by uSleep during next
 *        idle cycle.
 *
 * @param newIdleEntryPtr: Pointer to the function that will be called when
 *                         system is idle next time.
 */
void uSleepOS_setIdleFunctionPtr(uSleep_idle_entry_ptr_type newIdleEntryPtr);

/**
 * uSleepOS_getIdleFunctionPtr
 *
 * @brief Returns pointer to the idle entry point used by uSleep in next
 *        idle cycle.
 *
 * @return see @brief
 */
uSleep_idle_entry_ptr_type uSleepOS_getIdleFunctionPtr(void);

/** 
 * uSleepOS_performError 
 *  
 * @brief This function is the fatal exit from uImage function. There is no
 *        execution or recovery from this function. The OS should never allow
 *        this function to run. 
 */
uint32 uSleepOS_performError(void);

/** 
 * uSleep_initialize
 * 
 * @brief Initialize the uSleep subsystem
 */
void uSleepOS_initialize(void);

/** 
 * uSleepOS_cleanupIslandExit
 * 
 * @brief Performs the final stages of exiting island from sleep context
 */
void uSleepOS_cleanupIslandExit(void);

/**
 * uSleepOS_perform
 * 
 * @brief Entry function for performing low power modes in uSleep.
 *
 * @return Potential error code (unused as of now)
 */
uint32 uSleepOS_perform(void);

/**
 * uSleepOS_SetSPMClockConfiguration
 *
 * @brief Set Q6 SPM clock to be configured from PEEL PLL.
 *
 * @return None
 */
 void uSleepOS_SetSPMClockConfiguration();

/**
 * uSleepOS_Set_Q6AxiClockConfiguration
 *
 * @brief SetReset CLK_ENABLE field of Q6_AXI_CBCR.

 * @return Potential error code (unused as of now)
 */
 void uSleepOS_Set_Q6AxiClockConfiguration(clock_enablement_type enable);
 

#endif /* USLEEP_OS_H */

