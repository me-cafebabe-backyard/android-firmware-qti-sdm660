/*==============================================================================
  FILE:         uSleep_ddr_log.c
  
  OVERVIEW:     This file implements the uSleep logging system for DDR logs.

  DEPENDENCIES: None

                Copyright (c) 2015 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/src/log/ddr/uSleep_ddr_log.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include <stdarg.h>
#include "DALStdDef.h"
#include "uSleep_ddr_log.h"

/*==============================================================================
                                GLOBAL VARIABLES
 =============================================================================*/
ULogHandle g_uSleepDDRLogHandles[USLEEP_DDR_LOG_TOTAL_NUMBER] = { NULL };

/*==============================================================================
                            GLOBAL FUNCTION DEFINITIONS
 =============================================================================*/
/*
 * uSleepDDRLog_printf
 */
void uSleepDDRLog_printf(uSleep_ddr_log_level level, int arg_count, 
                         const char *format, ...)
{
  va_list args;

  if(!USLEEP_DDR_LOG_IS_VALID_LEVEL(level))
    return;

  va_start(args, format);
  ULogFront_RealTimeVprintf(g_uSleepDDRLogHandles[level], arg_count, format, args);
  va_end(args);

  return;
}

