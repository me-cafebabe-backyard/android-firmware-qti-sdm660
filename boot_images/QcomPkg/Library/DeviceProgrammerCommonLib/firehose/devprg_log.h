/**************************************************************************
 * FILE: devprg_log.c
 *
 * Logging APIs to log errors, warnings, information and debug data.
 *
 * Copyright (c) 2015 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Qualcomm Proprietary
 *
 *************************************************************************/

/*==========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/boot.xf/1.4/QcomPkg/Library/DeviceProgrammerCommonLib/firehose/devprg_log.h#2 $
  $DateTime: 2016/08/19 05:58:45 $
  $Author: c_mvanim $

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2015-11-17   wek   Create.

==========================================================================*/
#ifndef __DEVPRG_LOG_H__
#define __DEVPRG_LOG_H__


void logMessage(const char* format, ...);

/* Define all the log macros as logMessage. This should actually map to a
 * specific function to raise or reduce the verbosity level. */
#define DP_LOGE(f, ...)  logMessage("ERROR: "f, __VA_ARGS__) /* Error */
#define DP_LOGW(f, ...)  logMessage("WARN: "f, __VA_ARGS__) /* Warning */
#define DP_LOGI(f, ...)  logMessage("INFO: "f, __VA_ARGS__) /* Informational */
#define DP_LOGD(f, ...)  logMessage("DEBUG: "f, __VA_ARGS__) /* Debug, most verbose. */

#endif /* __DEVPRG_LOG_H__ */
