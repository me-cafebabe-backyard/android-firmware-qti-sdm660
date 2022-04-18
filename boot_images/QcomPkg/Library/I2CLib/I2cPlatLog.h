#ifndef _I2CPLATLOG_H_
#define _I2CPLATLOG_H_
/*
===========================================================================

FILE:   I2cPlatLog.h

DESCRIPTION:
    This file contains the API for the I2C Log services 


===========================================================================

        Edit History


When     Who    What, where, why
-------- ---    -----------------------------------------------------------
02/01/17 VG     Copyright updated
08/26/14 UNR    Created

===========================================================================
    Copyright (c) 2014-2017 Qualcomm Technologies, Incorporated.
                        All rights reserved.
    Qualcomm Technologies, Confidential and Proprietary.

===========================================================================*/

#include <Library/DebugLib.h>

#define I2C_ERROR_LOG_LEVEL0(pDevLog, level, format_str, ...) \
    DEBUG((EFI_D_INFO, format_str"\n", ##__VA_ARGS__))

#define I2C_CALLTRACE_LEVEL1(pDevLog, level, format_str, ...) \
    DEBUG((EFI_D_VERBOSE, format_str"\n", ##__VA_ARGS__))

#define I2C_CALLTRACE_LEVEL2(pDevLog, level, format_str, ...) \
    DEBUG((EFI_D_VERBOSE, format_str"\n", ##__VA_ARGS__))

#define I2C_CALLDATA_LEVEL1(pDevLog, level, format_str, ...) \
    DEBUG((EFI_D_VERBOSE, format_str"\n", ##__VA_ARGS__))

#define I2C_CALLDATA_LEVEL2(pDevLog, level, format_str, ...) \
    DEBUG((EFI_D_VERBOSE, format_str"\n", ##__VA_ARGS__))

#define QUPLOG_LOG_WRITE(address,level,format_str, ...) \
    DEBUG((EFI_D_VERBOSE, format_str"\n", ##__VA_ARGS__))

#define QUPLOG_LOG_READ(address,level,format_str, ...) \
    DEBUG((EFI_D_VERBOSE, format_str"\n", ##__VA_ARGS__))

#define I2C_CONFIG_LOG(x, format_str) \
    DEBUG((EFI_D_INFO, format_str))

#endif //_I2CPLATLOG_H_

