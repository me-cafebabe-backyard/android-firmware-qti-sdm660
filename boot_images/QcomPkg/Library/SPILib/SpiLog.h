#ifndef _SPI_LOG_H
#define _SPI_LOG_H

/*
===========================================================================

FILE:   SpiLog.h

DESCRIPTION:
    This file contains functions data structure declarations for SPI logging
    driver
 
===========================================================================

                                  Edit History


When     Who    What, where, why
-------- ---    -----------------------------------------------------------
12/17/13 sg     Updated new logging macro.
01/24/13 unr    Created

===========================================================================
              Copyright c 2011 - 2013 Qualcomm Technologies Incorporated.
                              All Rights Reserved.
                           Qualcomm Proprietary/GTDR

===========================================================================
*/
#include <Library/DebugLib.h>
#include "SpiDeviceTypes.h"


/*-------------------------------------------------------------------------
* Preprocessor Definitions and Constants
* ----------------------------------------------------------------------*/
#define SPI_LOG_LEVEL_MAX 			SPI_LOG_LEVEL_VERBOSE
#define SPI_LOG_LEVEL_VERBOSE 		5
#define SPI_LOG_LEVEL_INFO 			4
#define SPI_LOG_LEVEL_WARNING 		3
#define SPI_LOG_LEVEL_ERROR 		2
#define SPI_LOG_LEVEL_FATAL_ERROR 	1
#define SPI_LOG_LEVEL_NONE 			0

#define SPIDEVICE_LOG(severity, format_str, ...) SPI_LOG_##severity(format_str, ##__VA_ARGS__)
#define _SPIDEBUG(EfiD, Expression, ...)	DEBUG((EfiD, Expression, ##__VA_ARGS__))

#define SPI_LOG_VERBOSE(format_str, ...) \
   if(SpiLog_GetLogLevel() >= SPI_LOG_LEVEL_VERBOSE) \
   {\
       _SPIDEBUG(EFI_D_ERROR, "%s: " format_str"\n", __FUNCTION__, ##__VA_ARGS__); \
   }

#define SPI_LOG_INFO(format_str, ...) \
	if(SpiLog_GetLogLevel() >= SPI_LOG_LEVEL_INFO) \
	{\
		_SPIDEBUG(EFI_D_ERROR, "%s: " format_str"\n", __FUNCTION__, ##__VA_ARGS__); \
	}

#define SPI_LOG_WARNING(format_str, ...) \
	if(SpiLog_GetLogLevel() >= SPI_LOG_LEVEL_WARNING) \
	{\
		_SPIDEBUG(EFI_D_ERROR, "%s: " format_str"\n", __FUNCTION__, ##__VA_ARGS__); \
	}

#define SPI_LOG_ERROR(format_str, ...) \
	if(SpiLog_GetLogLevel() >= SPI_LOG_LEVEL_ERROR) \
	{\
		_SPIDEBUG(EFI_D_ERROR, "%s: " format_str"\n", __FUNCTION__, ##__VA_ARGS__); \
	}
    
#define SPI_LOG_FATAL_ERROR(format_str, ...) \
	if(SpiLog_GetLogLevel() >= SPI_LOG_LEVEL_FATAL_ERROR) \
	{\
		 _SPIDEBUG(EFI_D_ERROR, "%s: " format_str"\n", __FUNCTION__, ##__VA_ARGS__); \
	}

int32 SpiLog_Init(void);
uint32 SpiLog_GetLogLevel(void);
void SpiLog_SetLogLevel(uint32 uLogLevel);

#endif /* _SPI_LOG_H */

