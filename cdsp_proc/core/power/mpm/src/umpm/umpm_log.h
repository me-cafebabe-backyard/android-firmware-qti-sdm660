#ifndef UMPM_LOG_H
#define UMPM_LOG_H
/*==============================================================================
  FILE:         umpm_log.h
  
  OVERVIEW:     Contains internal variables and function declarations for the
                uMPM logging system
 
  DEPENDENCIES: None

                Copyright (c) 2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/mpm/src/umpm/umpm_log.h#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include <stdarg.h>
#include "DALStdDef.h"
#include "micro_ULog.h"

/*==============================================================================
                            DEFINITIONS & TYPES
 =============================================================================*/
/* Macros indicating size of the uMPM log in bytes */
#define UMPM_LOG_SIZE   MICRO_ULOG_MEM_NEEDED(512)

/*==============================================================================
                              INTERNAL FUNCTIONS
 =============================================================================*/
/**
 * umpm_logInit
 *
 * @brief Initializes the uMPM loging system
 */
void umpm_logInit(void);

/**
 * umpm_LogPrintf
 *
 * @brief Function that will log the messages.
 *
 * @param arg_count: Number of parameteres that are being logged.
 * @param format: Format string for logging function.
 */
void umpm_LogPrintf(int arg_count, const char *format, ...);

#endif  /* UMPM_LOG_H */

