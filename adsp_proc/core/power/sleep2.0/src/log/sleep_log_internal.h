#ifndef SLEEP_LOG_INTERNAL_H
#define SLEEP_LOG_INTERNAL_H
/*==============================================================================
  FILE:         sleep_log_internal.h
  
  OVERVIEW:     Contains internal variables and functions declarations. This
                file is not supposed to be used outside sleep logging codes.
 
  DEPENDENCIES: None

                Copyright (c) 2011-2015 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/sleep2.0/src/log/sleep_log_internal.h#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#ifdef __cplusplus
extern "C" {
#endif

#include "DALStdDef.h"
#include "ULog.h"
#include "sleep_log.h"
/*==============================================================================
                             DATA DECLARATIONS
 =============================================================================*/

/**
 * g_sleepNumberOfLogs
 *
 * @brief Number of available logs for a given sleep log implementation.
 */
extern const uint32 g_sleepNumberOfLogs;

/**
 * g_sleepLogHandles
 *
 * @brief Array of sleep log handles. Based on the version of sleep log (low 
 *        memory, multicore or normal) it will contain different number of 
 *        handles.
 */
extern ULogHandle g_sleepLogHandles[];

/**
 * g_sleepLogSizeArray
 *
 * @brief Array for the sleep log sizes. The value at index i represents the
 *        size of log indicated by handle at i in g_sleepLogHandles array.
 */
extern uint32 g_sleepLogSizeArray[];

/**
 * g_sleepLogNameArray
 *
 * @brief  Array of the log names. Value at index i represents name of log
 *         denoted by handle at index i in sleepLogHandle.
 */
extern const char *g_sleepLogNameArray[];

/**
 * g_sleepLogLockTypeArray
 *
 * @brief  Array of the log locks. Value at index i represents 
 *         the lock type to use for the log denoted by handle at
 *         index i in sleepLogHandle.
 */
extern ULOG_LOCK_TYPE g_sleepLogLockTypeArray[];

/*==============================================================================
                              INTERNAL FUNCTIONS
 =============================================================================*/
/**
 * sleep_log_prepare_data
 *
 * @brief Prepares the log data like names and size.
 */
void sleepLog_initializeTargetCfg(void);

#ifdef __cplusplus
}
#endif

#endif  /* SLEEP_LOG_INTERNAL_H */

