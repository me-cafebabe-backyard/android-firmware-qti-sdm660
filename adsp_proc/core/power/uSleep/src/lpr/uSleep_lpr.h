#ifndef USLEEP_LPR_H
#define USLEEP_LPR_H
/*==============================================================================
  FILE:         uSleep_lpr.h

  OVERVIEW:     Types & definitions for uSleep supported low power modes

  DEPENDENCIES: None
  
                Copyright (c) 2014-2015 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/src/lpr/uSleep_lpr.h#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "DALStdDef.h"
#include "comdef.h"

/*==============================================================================
                             INTERNAL DEFINITIONS
 =============================================================================*/
/* Index values into the modes in g_uSleepLPR */
typedef enum
{
  usleep_lpr_cached_idx       = 0,
  usleep_lpr_last_cached_idx  = usleep_lpr_cached_idx,

  usleep_lpr_apcr_nowake_idx  = 1,
  usleep_lpr_apcr_idx         = 2,
  usleep_lpr_ret_idx          = 3,

  usleep_lpr_last_idx
}usleep_lpr_index;

/* Number of LPR's supported in uSleep */
#define USLEEP_NUMBER_LOW_POWER_MODES   usleep_lpr_last_idx
#define USLEEP_LAST_CACHED_MODE         usleep_lpr_last_cached_idx

/*==============================================================================
                               TYPE DEFINITIONS
 =============================================================================*/
/* LPR function types */
typedef void (*uSleep_LPR_enter_func)(uint64 wakeupTime);
typedef void (*uSleep_LPR_exit_func)(void);
typedef void (*uSleep_LPR_init_func)(void);

/* LPR type for uSleep */
typedef struct usleep_LPR_s
{
  char                  *name;      /* Name of LPRM */
  uint32                latency;    /* Enter + exit latency in ticks of LPRM */
  uint32                backoff;    /* Backoff latency in ticks of LPRM */
  uSleep_LPR_init_func  init_func;  /* Setup function that is called on transition */
  uSleep_LPR_enter_func enter_func; /* Functions to call for LPRM */
  uSleep_LPR_exit_func  exit_func;
  boolean               cached;     /* Flag to indicate if mode is cacheable */
}uSleep_LPR;

/*==============================================================================
                             EXTERNAL VARIABLES
 =============================================================================*/
extern uSleep_LPR g_uSleepLPR[USLEEP_NUMBER_LOW_POWER_MODES];

/*==============================================================================
                            FUNCTION DECLARATIONS
 =============================================================================*/
/**
 * uSleepLPR_apcrNoWakeEnter 
 *  
 * @brief Enters APCR mode, but does not set a wakeup time. This mode is 
 *        selected if there is not enough time to enter the standard APCR mode. 
 * 
 * @param wakeupTime: Absolute value of the wakeup time. 
 *                    This value is not used
 */
void uSleepLPR_apcrNoWakeEnter(uint64 wakeupTime);

/**
 * uSleepLPR_apcrEnter
 * 
 * @brief Enter function for un-cached APCR low power mode.
 * 
 * @param wakeupTime: Absolute wakeup time
 */
void uSleepLPR_apcrEnter(uint64 wakeupTime);

/**
 * uSleepLPR_apcrCachedEnter
 * 
 * @brief Enter function for cached APCR low power mode.
 * 
 * @param wakeupTime: Absolute wakeup time
 */
void uSleepLPR_apcrCachedEnter(uint64 wakeupTime);

/**
 * uSleepLPR_apcrExit
 * 
 * @brief Exit function for un-cached APCR low power mode
 */
void uSleepLPR_apcrExit(void);

/**
 * uSleepLPR_apcrInit
 * 
 * @brief This function is called while in normal operational mode and will 
 *        setup any requirements to enter APCR mode while in uSleep.
 */
void uSleepLPR_apcrInit(void);

/**
 * uSleepLPR_retentionEnter
 * 
 * @brief APCR+ LPR entry function
 * 
 * @param wakeupTime: Absolute wakeup time
 */
void uSleepLPR_APCRPlusEnter(uint64 wakeupTime);

/**
 * uSleepLPR_retentionExit
 * 
 * @brief APCR+ LPR exit function
 */
void uSleepLPR_APCRPlusExit(void);

/**
 * uSleepLPR_retentionInit
 * 
 * @brief This function is called while in normal operational mode and will 
 *        setup any requirements to enter retention mode while in uSleep.
 */
void uSleepLPR_retentionInit(void);

/**
 * uSleepLPR_init
 * 
 * @brief This function is called while in normal operational mode and executes 
 *        each low power mode's init function on the transition into island
 *        mode.
 */
void uSleepLPR_init(void);

/** 
 * uSleepLPR_runLPRFunctions
 * 
 * @brief Runs the currently selected low power mode enter or exit function 
 *  
 * @param enterFunction: TRUE   -> Run the currently selected LPRM enter 
 *                                 function
 *                       FALSE  -> Run the currently selected LPRM exit function
 *  
 * @param wakeupDeadline: Value (in absolute ticks) of the backoff adjusted 
 *                        desired wakeup time. 
 *                        If exit function is selected, this value is a don't
 *                        care.
 * @param mode:           LPR to enter or exit 
 */
void uSleepLPR_runLPRFunctions(boolean    enterFunction,
                               uint64     wakeupDeadline,
                               uSleep_LPR *mode);


#endif /* USLEEP_LPR_H */

