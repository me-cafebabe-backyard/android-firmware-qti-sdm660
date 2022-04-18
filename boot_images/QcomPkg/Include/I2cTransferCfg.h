#ifndef _I2CTRANSFERCFG_H_
#define _I2CTRANSFERCFG_H_
/*
===========================================================================

FILE:   I2cTransferCfg.h

DESCRIPTION:
    This file contains transfer configuration data structures.

===========================================================================

        Edit History


When     Who    What, where, why
-------- ---    -----------------------------------------------------------
09/26/11 LK     Created

===========================================================================
              Copyright c 2011 Qualcomm Technologies Incorporated.
                              All Rights Reserved.
                           Qualcomm Proprietary/GTDR

===========================================================================
*/

#include "I2cTypes.h"

typedef struct I2cClientConfig
{
   uint32 uBusFreqKhz;
   /**< I2C bus frequency. */
   uint32 uByteTransferTimeoutUs;
   /**< I2C byte timeout. The transfer timeout will be calculated from this value. */
   uint32 uBusSDANR;
   /**< Noise rejection setting for SDA. */
   uint32 uBusSCLNR;
   /**< Noise rejection setting for SCL. */
} I2cClientConfig;

typedef struct I2cTransferConfig
{
   uint32 uSlaveAddr;
   /**< Seven bit address isleft shifted and the r/w bit added by the driver.*/ 
} I2cTransferConfig;

#endif // _I2CTRANSFERCFG_H_
