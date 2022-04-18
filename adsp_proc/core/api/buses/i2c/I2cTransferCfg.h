/**
@file qapi_i2c_master.h

@defgroup i2c I2C

@ingroup buses

@brief I2C bus and transfer configuration

@details
Definitions of I2C transfer and bus configurations
*/
/*
===========================================================================
                                  Edit History

$Header: //components/rel/core.qdsp6/1.0.c2/api/buses/i2c/I2cTransferCfg.h#1 $

When     Who    What, where, why
-------- ---    -----------------------------------------------------------
03/21/16 UR     Documented
09/26/11 LK     Created

===========================================================================
                 Copyright c 2011 - 2016 Qualcomm Technologies Incorporated.
                              All Rights Reserved.
                           Qualcomm Proprietary/GTDR
===========================================================================
*/

#ifndef _I2CTRANSFERCFG_H_
#define _I2CTRANSFERCFG_H_

#include "I2cTypes.h"

/*@{*/

/**
  @brief I2C commands specific to transfers
  @details
  These commands do not have any meaning outside the context of a transfer and
  hence must be part of the transfer configuration.
*/
typedef enum _I2cTrCfgCmd
{
   I2cTrCfgCmd_Null             = 0x0,  /**< Don't do anything. */
   I2cTrCfgCmd_TimeStampStart   = 0x1,  /**< Timestamp the START bit on the bus.
                                             See \ref I2cTransferConfig */
   I2cTrCfgCmd_TimeStampStop    = 0x2,  /**< Timestamp the STOP bit on the bus.
                                             See \ref I2cTransferConfig */
   I2cTrCfgCmd_InsertDelayAfter = 0x4,  /**< Not implemented. */

}  I2cTrCfgCmd;

/**
  @brief I2C bus and slave specific configuration
*/
typedef struct I2cClientConfig
{
   uint32 uBusFreqKhz;              /**< I2C bus frequency in KHz. */
   uint32 uByteTransferTimeoutUs;   /**< I2C byte timeout. The total transfer
                                         timeout will be calculated from this
                                         value. */
   uint32 uSlaveAddr;               /**< Seven bit I2C slave address.*/

} I2cClientConfig;

/**
  @brief I2C transfer special configuration
*/
typedef struct I2cTransferConfig
{
   uint32      uSlaveAddr;      /**< Deprecated member. Do not use.*/

   I2cTrCfgCmd cmd;             /**< Command that should be executed along
                                     with the transfer. See \ref I2cTrCfgCmd */
   uint32      startTime;       /**< Timestamp that is returned for the
                                     I2cTrCfgCmd_TimeStampStart command. The
                                     value is equal to bits [31:8] of the 56 bit
                                     QTIMER left shifted by 8 */
   uint32      stopTime;        /**< Timestamp that is returned for the
                                     I2cTrCfgCmd_TimeStampStop command. The
                                     value is equal to bits [31:8] of the 56 bit
                                     QTIMER left shifted by 8. Not Implemented. */
   uint32      delay;           /**< Not implemented. */
   
   
   uint16      aWordVal[4];     /**< Internal use.*/ 

} I2cTransferConfig;

/*@}*/

#endif /* _I2CTRANSFERCFG_H_ */
