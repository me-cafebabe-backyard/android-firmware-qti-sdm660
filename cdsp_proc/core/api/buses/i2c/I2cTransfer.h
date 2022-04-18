/**
@file I2cTransfer.h

@defgroup i2c I2C

@ingroup buses

@brief I2C transfer descriptors
*/
/*
===========================================================================
                                  Edit History

$Header: //components/rel/core.qdsp6/1.0.c2/api/buses/i2c/I2cTransfer.h#1 $

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

#ifndef _I2CTRANSFER_H_
#define _I2CTRANSFER_H_

#include "I2cTransferCfg.h"
#include "I2cTypes.h"

/*@{*/

/**
  @brief I2C transfer direction
*/
typedef enum _eTranDirection
{
    I2cTranDirIn,           /**< Read data from slave device. */
    I2cTranDirOut           /**< Write data to the slave device. */

} I2cTranDirection;

/**
  @brief I2C transfer context
  @details
  The common use case is to set the \ref I2cTransfer eTranCtxt to
  I2cTrCtxNotASequence when performing an I2C transfer using ::I2cDrv_Read or
  ::I2cDrv_Write. Since these transfer APIs will perform a single I2C transfer,
  the context is always set to I2cTrCtxNotASequence.

  The transfer context is of importance when an array of I2C transfers is
  collected into an \ref I2cSequence and passed into the ::I2cDrv_BatchTransfer
  API. The context controls how the START, REPEAT START and STOP bits are send out on
  the bus for multiple transfers. Usually in an array of transfers, the first
  transfer is set to a context I2cTrCtxSeqStart to indicate that this transfer
  will start with a START bit. Subsequent transfers, except the last one, will
  have their transfer contexts set to I2cTrCtxSeqContinue, so that each of these
  transfers uses a REPEAT START bit to execute the transfer on the bus. The last
  transfer context should be set to I2cTrCtxSeqEnd so that the transfer starts
  with a REPEAT START and ends with a STOP bit.
*/
typedef enum _eTranCtxt
{
    I2cTrCtxNotASequence,   /**< Transfer is not part of a sequence/batch. */
    I2cTrCtxSeqStart,       /**< Transfer is the first in a sequence/batch. */
    I2cTrCtxSeqContinue,    /**< Transfer continues a started sequence. */
    I2cTrCtxSeqEnd          /**< Transfer ends the sequence. */

}  I2cTranCtxt ;

/**
  @brief I2C buffer descriptor pointer and size
*/
typedef struct I2cIoVec 
{
    uint8   *pBuff;         /**< Address of the buffer. */
    uint32  size;           /**< Size of the buffer in bytes. */

} I2cIoVec;

/**
  @brief I2C buffer descriptor pointer and size
*/
typedef struct I2cBuffDesc 
{
    uint8   *pBuff;         /**< Address of the buffer. */
    uint32  uBuffSize;      /**< Size of the buffer in bytes. */

} I2cBuffDesc;

/**
  @brief I2C transfer
  @details
  A transfer is described as an operation in one direction only (read or write)
*/
typedef struct I2cTransfer 
{
    union
    {
        I2cBuffDesc   *pI2cBuffDesc;        /**< Buffer descriptor. */
        I2cIoVec      *pIoVec;              /**< Array of buffer descriptors. */
    };
    uint32                uTrSize;          /**< Transfer total number of bytes. Usually this is the same as the
                                             size of the buffer in the buffer descriptor. In some cases the
                                             memory buffer provided by a client may be scattered. In such cases an
                                             array of buffer descriptors can be used.  In case an array of
                                             buffer descriptors is allocated, then this value must be set to the
                                             sum of sizes of all the buffers in the buffer-descriptor-array */
    I2cTransferConfig     tranCfg;          /**< Transfer configuration. See \ref I2cTransferConfig*/
    I2cTranDirection      eTranDirection;   /**< Transfer direction. See \ref I2cTranDirection */
    I2cTranCtxt           eTranCtxt ;       /**< Transfer context. See \ref I2cTranCtxt */

} I2cTransfer;

/**
  @brief I2C operation result
  @details
  The result of a transfer is passed using this object.
*/
typedef struct I2cIoResult
{
    int32   nOperationResult;   /**< Result (failure/success) of the I2C transfer. */
    uint32  uOutByteCnt;        /**< Number of bytes written. */
    uint32  uInByteCnt;         /**< Number of bytes read. */

} I2cIoResult;

/**
  @brief I2C Sequence
  @details
  I2C Sequence is an array of \ref I2cTransfer objects that are passed into the
  ::I2cDrv_BatchTransfer API
*/
typedef struct I2cSequence 
{
    I2cTransfer *pTransfer;     /**< Pointer to array of transfers. */
    uint32      uNumTransfers;  /**< Number of transfers in this sequence. */

} I2cSequence;

/*@}*/

#endif /* _I2CTRANSFER_H_ */
