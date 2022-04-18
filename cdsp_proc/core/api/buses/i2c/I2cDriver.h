/**
@file I2cDriver.h

@defgroup i2c I2C

@ingroup buses

@brief Inter-Integrated Circuit (I2C) APIs

@details

I2C is a 2 wire bus used to connect low speed peripherals to a processor or a
microcontroller. Common I2C peripherals include touch screen controllers,
accelerometers, gyros, ambient light and temperature sensors.

The 2 wire bus comprises of a data line and a clock line and basic START, STOP
and acknowledge signals to drive transfers on the bus. An I2C peripheral is
also referred to as an I2C slave. The processor or microcontroller implements
the I2C master as defined in the I2C specification. This documentation provides
the SW interface to access the I2C master implementation.
*/
/*
===========================================================================
                                  Edit History

$Header: //components/rel/core.qdsp6/1.0.c2/api/buses/i2c/I2cDriver.h#1 $

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
#ifndef _I2CDRIVER_H_
#define _I2CDRIVER_H_

#include "I2cRegisterTransfer.h"
#include "I2cError.h"

typedef void *I2CDRV_HANDLE;

/*@{*/

/**
  @brief I2C core instance
  @details
  The instance of the i2c core that the client wants to use. This instance is
  passed in ::I2cDrv_Open.
*/
typedef enum I2cDrv_I2cBusId
{
   I2CDRV_I2C_MIN  = 0,
   I2CDRV_I2C_1    = 0,             /**< I2C core 01 */
   I2CDRV_I2C_2    = 1,             /**< I2C core 02 */
   I2CDRV_I2C_3    = 2,             /**< I2C core 03 */
   I2CDRV_I2C_4    = 3,             /**< I2C core 04 */
   I2CDRV_I2C_5    = 4,             /**< I2C core 05 */
   I2CDRV_I2C_6    = 5,             /**< I2C core 06 */
   I2CDRV_I2C_7    = 6,             /**< I2C core 07 */
   I2CDRV_I2C_8    = 7,             /**< I2C core 08 */
   I2CDRV_I2C_9    = 8,             /**< I2C core 09 */
   I2CDRV_I2C_10   = 9,             /**< I2C core 10 */
   I2CDRV_I2C_11   = 10,            /**< I2C core 11 */
   I2CDRV_I2C_12   = 11,            /**< I2C core 12 */
   I2CDRV_I2C_MAX  = I2CDRV_I2C_12,
   I2CDRV_I2C_NUM  = 12,
   I2CDRV_I2C_DEV_INVALID = -1,

} I2cDrv_I2cBusId;

/**
  @brief I2C driver command
  @details
  Control commands that can be passed to the I2C driver. These commands are
  passed in ::I2cDrv_Cmd.
*/
typedef enum I2cDrvCmdType
{
   I2cDrvCmd_Vote_PnocOn,           /**< Vote for PNOC ON. For command parameters, see \ref I2cDrvPnocVoteData */
   I2cDrvCmd_Vote_PnocOff,          /**< Vote for PNOC OFF. For command parameters, see \ref I2cDrvPnocVoteData */
   I2cDrvCmd_Vote_I2cClocsOn,       /**< Vote for I2C Clocks On */
   I2cDrvCmd_Vote_I2cClocsOff,      /**< Vote for I2C Clocks Off */
      
} I2cDrvCmdType;

/**
  @brief Client specific information
  @details
  Client specific configuration including the I2C core, bus speed and slave
  information. The information is passed in ::I2cDrv_Open.
*/
typedef struct I2cDrv_I2cBus
{
   I2cDrv_I2cBusId      i2cId;      /**< \ref I2cDrv_I2cBusId */
   I2cClientConfig      clntCfg;    /**< \ref I2cClientConfig */
   uint32               cookie;     /**< Reserved for driver use */

} I2cDrv_I2cBus;

/**
  @brief Data to be sent with I2cDrvCmd_Vote_PnocOn/I2cDrvCmd_Vote_PnocOff.
  @details
  The units use for IB/AB are bytes/sec. In general terms, IB value is the
  peak bandwidth requirement, while AB value is your average bandwidth
  requirement over whatever your active time period happens to be. The bandwidth
  refers to the peripheral (AHB) bus.
*/
typedef struct I2cDrvPnocVoteData
{
   uint64    uPnocIb;               /**< Peak bandwidth in bytes/sec */
   uint64    uPnocAb;               /**< Average bandwidth in bytes/sec */
      
} I2cDrvPnocVoteData;

/**
  @brief Opens a connection to the I2C core

  @param[in] eI2cBusId          I2C Bus ID.
  @param[in] pI2cBus            Pointer to I2C bus struct.
  @param[in] dwaccessMode       Access mode.

  @return I2C_RES_SUCCESS if successful, error otherwise.
*/
int32
I2cDrv_Open
(
   I2cDrv_I2cBusId  eI2cBusId,
   I2cDrv_I2cBus    *pI2cBus,
   uint32           dwaccessMode
);

/** @brief Closes the connection to the I2C core

    @param[in] pI2cBus            Pointer to I2C bus struct.

    @return I2C_RES_SUCCESS if successful, error otherwise.
  */
int32
I2cDrv_Close
(
   I2cDrv_I2cBus    *pI2cBus
);

/**
  @brief Read a buffer from i2c device.

  @param[in] pI2cBus            Pointer to I2C bus struct.
  @param[in] pTransfer          Pointer where transfer data will be stored.
  @param[in] pClntCfg           Pointer to Client configuration.
                                If null use previous client configuration.
  @param[in] puNumCompleted     Pointer to return number of bytes read.

  @return I2C_RES_SUCCESS if successful, error otherwise.
*/
int32
I2cDrv_Read
(
   I2cDrv_I2cBus    *pI2cBus,
   I2cTransfer      *pTransfer,
   uint32           *puNumCompleted
); 

/**
  @brief Write a buffer to i2c device.

  @param[in] pI2cBus            Pointer to I2C bus struct.
  @param[in] pTransfer          Pointer to transfer data.
  @param[in] puNumCompleted     Pointer to return number of bytes written.

  @return I2C_RES_SUCCESS if successful, error otherwise.
*/
int32
I2cDrv_Write
(
   I2cDrv_I2cBus    *pI2cBus,
   I2cTransfer      *pTransfer,
   uint32           *puNumCompleted
);

/**
  @brief Does a batch of transfers in a sequence.

  @param[in] pI2cBus            Pointer to I2C bus struct.
  @param[in] pSequence          Pointer to a sequence of transfer
                                data.
  @param[in] pIoRes             Pointer to io result.

  @return I2C_RES_SUCCESS if successful, error otherwise.
*/
int32
I2cDrv_BatchTransfer
(
   I2cDrv_I2cBus    *pI2cBus,
   I2cSequence      *pSequence,
   I2cIoResult      *pIoRes
);

/**
  @brief Send a command to the i2c driver.

  @param[in] pI2cBus            Pointer to I2C bus struct.
  @param[in] cmd                Command to send to the driver.
  @param[in] pData              Data related to the command.

  @return I2C_RES_SUCCESS if successful, error otherwise.
*/
int32
I2cDrv_Cmd
(
   I2cDrv_I2cBus    *pI2cBus,
   I2cDrvCmdType    cmd,
   void             *pData
);

/*@}*/

#endif /* _I2CDRIVER_H_ */
