#ifndef USLEEP_UTIL_H
#define USLEEP_UTIL_H
/*==============================================================================
  FILE:         uSleep_util.h

  OVERVIEW:     Types & prototypes for internal utility uSleep functions

  DEPENDENCIES: None
  
                Copyright (c) 2014-2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/src/util/uSleep_util.h#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "DALStdDef.h"
#include "uSleepi.h"
#include "uSleep_transi.h"
#include "sleep_stats_global.h"

/*==============================================================================
                            DEFINITIONS & TYPES
 =============================================================================*/
/** 
 * uSleep_global_data
 * 
 * @brief Global uSleep data structure that holds various states and data
 */
typedef struct uSleep_global_data_s
{
  /* Current internal uSleep state */ 
  uSleep_internal_state state;

  /* Power mode specific to uSleep mode */
  uSleep_power_mode low_power_mode;

  /* DDR wakeup timer deadline */
  uint64 ddr_wakeup_timer; 

  /* Time of the last wakeup in uImage */
  uint64 last_wakeup_timestamp;

  /* Time of the last PMI interrupt in uImage */
  uint64 last_pmi_timestamp;

  /* Transition profiling data structure */
  uSleep_transition_profiling transition_data;
}uSleep_global_data;

/*==============================================================================
                          DDR FUNCTION DECLARATIONS
 =============================================================================*/
/**
 * uSleep_createQueryHandles
 * 
 * @brief Creates the various handles required to turn on and off DDR
 * 
 * @note This function must be called before the first entry into island mode
 *       while still in normal operational mode.
 */
void uSleep_createQueryHandles(void);

/**
 * uSleepTrans_setDDRWakeupTimeInternal
 * 
 * @brief Sets the value of the first non-deferrable timer from normal mode so uSleep 
 *        can exit to service it.
 *  
 * @note This function does not actually program a uTimer, it only sets an internal value. 
 *       Be sure to call uSleepTrans_programDDRWakeupTimeInternal to actually create a uTimer 
 *  
 * @param wakeupTimer:  Absolute time (in ticks) of the next non-deferrable 
 *                      normal operational timer. 
 */
void uSleepTrans_setDDRWakeupTimeInternal(uint64 wakeupTimer);

/*==============================================================================
                        ISLAND FUNCTION DECLARATIONS
 =============================================================================*/
/**
 * uSleep_setStateInternal
 * 
 * @brief Sets the current uSleep internal state
 * 
 * @param state: uSleep internal state to set
 */
void uSleep_setStateInternal(uSleep_internal_state state);

/**
 * uSleep_getStateInternal
 * 
 * @brief Gets the current uSleep internal state
 */
uSleep_internal_state uSleep_getStateInternal(void);

/**
 * uSleep_getDDRWakeupTimeInternal
 * 
 * @brief Gets the currently set DDR wakeup time as given to uSleep during 
 *        the entry transition.
 */
uint64 uSleep_getDDRWakeupTimeInternal(void);

/**
 * uSleep_setLastSleepWakeupInternal
 * 
 * @brief Sets the time of the wakeup from the last power cycle. 
 *  
 * @param wakeupTime: Absolute time of the last wakeup 
 */
void uSleep_setLastSleepWakeupInternal(uint64 wakeupTime);

/**
 * uSleep_getLastSleepWakeupInternal
 * 
 * @brief Gets the time of the wakeup from the last power cycle. 
 *  
 * @return Absolute time of the last wakeup. 
 */
uint64 uSleep_getLastSleepWakeupInternal(void);

/**
 * uSleep_getLastPMITimestampInternal
 * 
 * @brief Gets the time of the last PMI that occured while in uImage. 
 *  
 * @return Absolute time of the last PMI occurrence. 
 */
uint64 uSleep_getLastPMITimestampInternal(void);

/**
 * uSleep_setLastPMITimestampInternal
 * 
 * @brief Sets the time of the last PMI that occured while in uImage. 
 *  
 * @param PMITime: Absolute time of the last PMI occurrence. 
 */
void uSleep_setLastPMITimestampInternal(uint64 PMITime);

/**
 * uSleep_setLowPowerModeInternal
 * 
 * @brief Indicates if we can enter retention mode based on the use case
 *  
 * @note This is not an aggregation as in normal operational mode.  The last 
 *       function call will set the current mode.
 *  
 * @param mode: Enable or disable retention
 */
void uSleep_setLowPowerModeInternal(uSleep_power_mode mode);

/**
 * uSleep_getLowPowerModeInternal
 * 
 * @brief Gets the current state of the SSC retention power state as requested 
 *        from the use case 
 *  
 * @return Returns current retention state. 
 */
uSleep_power_mode uSleep_getLowPowerModeInternal(void);

/**
 * uSleep_getProfilingDataPtr
 * 
 * @brief Gets a pointer to the uSleep profiling data structure which can be 
 *        used to access data directly 
 */
uSleep_transition_profiling* uSleep_getProfilingDataPtr(void);

#endif /* USLEEP_UTIL_H */
