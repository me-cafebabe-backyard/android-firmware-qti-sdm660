/*==============================================================================
  FILE:         uSleep_log.c
  
  OVERVIEW:     This file implements the uSleep logging system.

  DEPENDENCIES: None

                Copyright (c) 2014-2015 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/src/log/uSleep_log.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include <stdarg.h>
#include "DALStdDef.h"
#include "uSleep_log.h"

/*==============================================================================
                          VARIABLE DECLARATIONS
 =============================================================================*/
/* Array of sleep log handles. */
micro_ULogHandle g_uSleepLogHandles[USLEEP_LOG_TOTAL_NUMBER] = { NULL };

/* Pre-allocated log buffers required for island mode */
char g_uSleepLogBuffers[USLEEP_TOTAL_LOG_BUFFER_SIZE];

/*==============================================================================
                       GLOBAL FUNCTION DEFINITIONS
 =============================================================================*/
/*
 * uSleepLog_printf
 */
void uSleepLog_printf(uSleep_log_level level, int arg_count, 
                      const char *format, ...)
{
  va_list args;

  if(!USLEEP_LOG_IS_VALID_LEVEL(level))
    return;

  va_start(args, format);
  micro_ULog_RealTimeVprintf(g_uSleepLogHandles[level], arg_count, format, args);
  va_end(args);

  return;
}

