/**
 * @file sns_ddf_comm.c
 * @brief Implementation of the Device Driver Framework communication module.
 *
 * @see sns_ddf_comm.h
 *
 * Copyright (c) 2014 - 2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.

 */

/* $Header: //components/rel/ssc.slpi/2.2/ddf/src/sns_ddf_uimg_comm_bus_i2c.c#1 $ */
/* $DateTime: 2017/04/17 22:20:39 $ */
/* $Author: pwbldsvc $ */

/*==============================================================================
  Edit History

  This section contains comments describing changes made to the module. Notice
  that changes are listed in reverse chronological order. Please use ISO format
  for dates.


  when       who  what, where, why
  ---------- ---  -----------------------------------------------------------
  2016-11-15 bd   Added support for 4-byte register addressing 
  2016-05-04 jtl  Update write_time support
  2016-02-26 jtl  Consolodate read/write functions to save space.
  2015-10-21 jtl  Added vector transfer API.
  2016-01-26 ps   Remove flags to use I2C in virtio bringup
  2014-09-02 jms  I2C and SPI refactored for uImage
==============================================================================*/

#include "sns_profiling.h"
#include "sns_log_types.h"
#include "sns_log_api.h"
#include "sns_ddf_util.h"
#include "sns_memmgr.h"
#include "sns_debug_str.h"

#include "sns_ddf_comm_priv.h"

/*----------------------------------------------------------------------------
 * Extern Variables
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Private Function Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Big Image Static Function Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

// In units of 1/1048576 seconds.
#define I2C_BUS_TXN_SETUP_TIME 36 /* 34.5 uSec */

/*----------------------------------------------------------------------------
 * Private Structure Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Public Global Variables
 * -------------------------------------------------------------------------*/

volatile bool EnableI2C = true;

/*----------------------------------------------------------------------------
 * Local Variables
 * -------------------------------------------------------------------------*/

//============================================================================
//============================================================================
//                         PUBLIC  I2C  BUS
//============================================================================
//============================================================================

/**
 * @brief Performs a bus read operation of multiple bytes using
 *        repeated start
 *
 * @param[in]  handle      The I/O port handle that identifies a device. This is
 *                         given to drivers as part of initialization.
 * @param[in]  reg_addr    Address of the register to read on the device.
 * @param[out] buffer      Location where result will be stored. Note size of
 *                         this buffer must >= "bytes" argument.
 * @param[in]  bytes       Number of bytes to read.
 * @param[out] read_count  Number of bytes actually read into the buffer.
 *
 * @return SNS_DDF_SUCCESS if the open operation was done successfully.
 *         Otherwise SNS_DDF_EDEVICE, SNS_DDF_EBUS, SNS_DDF_EINVALID_PARAM, or
 *         SNS_DDF_EFAIL to indicate an error has occurred.
 */
sns_ddf_status_e sns_ddf_read_port_sr(
    const sns_ddf_handle_t  handle,
    uint32_t                reg_addr,
    uint8_t*                buffer,
    uint8_t                 bytes,
    uint8_t*                read_count)
{
  if (handle == NULL)
  {
    UMSG(MSG_SSID_SNS,DBG_ERROR_PRIO, "handle is NULL");
    return SNS_DDF_EINVALID_PARAM;
  }

  if ((EnableI2C == true) &&
      (((sns_ddf_sensor_info_s *)handle)->bus == SNS_DDF_BUS_I2C))
  {
    /* Need a driver to test batch transfers, until then fail the return */
    return(SNS_DDF_EFAIL);
  }
  else
  {
    *read_count = bytes;
  }

  return SNS_DDF_SUCCESS;
}


/**
* @brief Set address type of device
*
* @param[in/out]  port_config_ptr  The pointer to the port configuration
* @param[in]  addr_type      The address type to be set
*
* @param[out] status       SNS_DDF_SUCCESS if the setting bus address type
*  	   operation was done successfully. Otherwise
*  	   SNS_DDF_EINVALID_PARAM, or SNS_DDF_EFAIL to indicate
*  	   an error has occurred
*/
sns_ddf_status_e sns_ddf_set_i2c_port_addr_type (
    sns_ddf_port_config_s*     port_config_ptr,
    sns_ddf_port_addr_type_e   addr_type  )
{
  if(port_config_ptr != NULL)
  {
    port_config_ptr->bus_config.i2c->addr_type = addr_type;
    return SNS_DDF_SUCCESS;
  }

  return SNS_DDF_EFAIL;
}

/**
* @brief Performs a bus read or write operation as defined by simple_read or simple_write
*
* @param[in]  handle       The I/O port handle that identifies a device. This
*                          is given to drivers as part of initialization.
* @param[out] buffer       Location where value to be written is stored. Note
*                          that size of this buffer must >= @a bytes argument.
* @param[in]  bytes        Number of bytes to transfer.
* @param[out] count        Number of bytes actually transfered to/from the buffer.
* @param[in]  is_write     true if write operation
*
* @return SNS_DDF_SUCCESS if the operation was done
*  	   successfully. Otherwise
*				SNS_DDF_EINVALID_PARAM - Input param is NULL
*				SNS_DDF_EBUS - Failure in DAL device open or write/read
**/
sns_ddf_status_e sns_ddf_simple_txfr_port(
    sns_ddf_handle_t  handle,
    uint8_t*          buffer,
    uint8_t           bytes,
    uint8_t*          count,
    bool              is_write)
{
  int32                   result;
  I2cSimpleTrObj          tr_obj;
  sns_ddf_status_e        status     = SNS_DDF_SUCCESS;
  uint32_t                data_bytes = 0;
  sns_ddf_sensor_info_s*  ddf_handle = (sns_ddf_sensor_info_s *)handle;
  I2cTranDirection        xfer_dir;

  int32(*xfer_fn)(I2cDrv_I2cBus *pI2cBus,
                  I2cTransfer   *pTransfer,
                  uint32        *puNumCompleted);

  if( is_write )
  {
    xfer_fn = I2cDrv_Write;
    xfer_dir = I2cTranDirOut;
  }
  else
  {
    xfer_fn = I2cDrv_Read;
    xfer_dir = I2cTranDirIn;
  }
  
  if( (NULL == ddf_handle) || (NULL == buffer) || (NULL == count) )
  {
    UMSG(MSG_SSID_SNS,DBG_ERROR_PRIO, "Input param is NULL");
    return SNS_DDF_EINVALID_PARAM;
  }

  if ( true == EnableI2C )
  {
    /* Init count */
    *count = 0;

    I2c_TrObj_Init(&tr_obj.aTr[0],&tr_obj.io_vec[0], xfer_dir,
                   I2cTrCtxNotASequence);
    I2c_TrObj_AddBuffer(&tr_obj.aTr[0], 0, buffer, bytes);


    /* Start a I2C transfer */
    result = xfer_fn(&ddf_handle->i2c_s.i2c_bus, &tr_obj.aTr[0], &data_bytes);
    if ( I2C_RES_SUCCESS != result )
    {
      UMSG_3( MSG_SSID_SNS, DBG_ERROR_PRIO,
              "I2C transaction fail, result = %d, read_count = %d is_write = %d",
              result, data_bytes, is_write );

      status = SNS_DDF_EBUS;
    }

    *count = data_bytes;
  }
  else
  {
    *count = bytes;
  }
  return status;
}

/**
* @brief Performs a bus read operation with data sequence:
*	[S] [Addr+R] [ACK] [Device_data_MSB] [ACK] .... [Device_data_LSB] [NACK] [P]
*
* @param[in]  handle      The I/O port handle that identifies a device. This is
*                         given to drivers as part of initialization.
* @param[out] buffer      Location where result will be stored. Note size of
*                         this buffer must >= @a bytes argument.
* @param[in]  bytes       Number of bytes to read.
* @param[out] read_count  Number of bytes actually read into the buffer.
*
* @return SNS_DDF_SUCCESS if the open operation was done successfully.
*         Otherwise
*			SNS_DDF_EBUS - Failure in DAL device open or read
*			SNS_DDF_EINVALID_PARAM - NULL input params
**/
sns_ddf_status_e sns_ddf_simple_read_port(
    sns_ddf_handle_t  handle,
    uint8_t*          buffer,
    uint8_t           bytes,
    uint8_t*          read_count)
{
  return sns_ddf_simple_txfr_port( handle, buffer, bytes, read_count, false );
}


/**
* @brief Performs a bus write operation with data sequence:
*  [S] [Addr+W] [ACK] [Master_data_MSB] [ACK] .... [Master_data_LSB] [ACK] [P]
*
* @param[in]  handle       The I/O port handle that identifies a device. This
*                          is given to drivers as part of initialization.
* @param[out] buffer       Location where value to be written is stored. Note
*                          that size of this buffer must >= @a bytes argument.
* @param[in]  bytes        Number of bytes to write.
* @param[out] write_count  Number of bytes actually written from the buffer.
*
* @return SNS_DDF_SUCCESS if the write operation was done
*  	   successfully. Otherwise
*				SNS_DDF_EINVALID_PARAM - Input param is NULL
*				SNS_DDF_EBUS - Failure in DAL device open or write
**/
sns_ddf_status_e sns_ddf_simple_write_port(
    sns_ddf_handle_t  handle,
    uint8_t*          buffer,
    uint8_t           bytes,
    uint8_t*          write_count)
{
  return sns_ddf_simple_txfr_port( handle, buffer, bytes, write_count, true );
}

//============================================================================
//============================================================================
//                         PRIVATE  I2C  BUS
//============================================================================
//============================================================================

//============================================================================
/**
 * @brief Performs a bus read operation for up to 2^32 - 1 bytes
 *        at a time.
 *
 * @param[in]  handle      The I/O port handle that identifies a device. This is
 *                         given to drivers as part of initialization.
 * @param[in]  reg_addr    Address of the register to read on the device.
 * @param[out] buffer      Location where result will be stored. Note size of
 *                         this buffer must >= @a bytes argument.
 * @param[in]  bytes       Number of bytes to read.
 * @param[out] read_count  Number of bytes actually read into the buffer.
 *
 * @return SNS_DDF_SUCCESS if the operation was done successfully.
 *         Otherwise SNS_DDF_EDEVICE, SNS_DDF_EBUS, SNS_DDF_EINVALID_PARAM, or
 *         SNS_DDF_EFAIL to indicate an error has occurred.
 */
sns_ddf_status_e sns_ddf_comm_bus_i2c_read
(
    const sns_ddf_handle_t  handle,
    uint32_t                reg_addr,
    uint8_t*                buffer,
    uint32_t                bytes,
    uint32_t*               read_count
)
{
  sns_ddf_status_e status;
  sns_ddf_rw_port_s read_vec = {
    .is_write = false,
    .reg_addr = reg_addr,
    .buffer     = (uint8_t*)buffer,
    .bytes      = bytes };

  status = sns_ddf_comm_bus_i2c_rw_v( handle, &read_vec, 1, NULL, NULL );
  *read_count = bytes;
  return status;
}

//============================================================================
/**
 * @brief Performs a bus write operation.
 *
 * @param[in]  handle       The I/O port handle that identifies a device. This
 *                          is given to drivers as part of initialization.
 * @param[in]  reg_addr     Address of the register to write on the device.
 * @param[in]  buffer       Location where value to be written is stored. Note
 *                          that size of this buffer must >= @a bytes argument.
 * @param[in]  bytes        Number of bytes to write.
 * @param[out] write_count  Number of bytes actually written from the buffer.
 * @param[out] write_time   System time write was performed, in SSC ticks << 5.
 *
 * @return SNS_DDF_SUCCESS if the operation was done successfully.
 *         Otherwise SNS_DDF_EDEVICE, SNS_DDF_EBUS, SNS_DDF_EINVALID_PARAM, or
 *         SNS_DDF_EFAIL to indicate an error has occurred.
 */
sns_ddf_status_e sns_ddf_comm_bus_i2c_write
(
    const sns_ddf_handle_t  handle,
    uint32_t                reg_addr,
    const uint8_t*          buffer,
    uint32_t                bytes,
    uint32_t*               write_count,
    uint64_t*               write_time
)
{
  sns_ddf_status_e status;
  sns_ddf_rw_port_s write_vec = {
    .is_write = true,
    .reg_addr = reg_addr,
    .buffer     = (uint8_t*)buffer,
    .bytes      = bytes };

  status = sns_ddf_comm_bus_i2c_rw_v( handle, &write_vec, 1, NULL, write_time );
  *write_count = bytes;
  return status;
}

/**
 * @brief Reads and/or writes multiple registers with repeated starts between registers
 *
 * @param[in]  handle        The I/O port handle that identifies a device. This 
 *                           is given to drivers as part of initialization.
 * @param[in]  vectors 
 *                           An array of register read/write operations
 * @param[in]  num_vectors
 *                           Number of elements in the vectors array
 * @param[out] total_bytes
 *                           Total number of bytes read & written for all registers
 * @param[out] write_time    Time (in SSC clock ticks*32) of the bus transaction
 * 
 * @return SNS_DDF_SUCCESS if the write operation was done 
 *  	   successfully. Otherwise SNS_DDF_EDEVICE,
 *  	   SNS_DDF_EBUS, SNS_DDF_EINVALID_PARAM, or
 *  	   SNS_DDF_EFAIL to indicate an error has occurred.
 */

sns_ddf_status_e sns_ddf_comm_bus_i2c_rw_v(
    const sns_ddf_handle_t      handle,
    const sns_ddf_rw_port_s    *vectors,
    int32_t                     num_vectors,
    int32_t                    *total_bytes,
    uint64_t                   *write_time )
{
  int32_t i;
  I2cRegSeqObj reg_obj[num_vectors];
  I2cTransfer  transfer[num_vectors*2];
  I2cIoResult  ioRes;
  int32        result;
  I2cSequence  seq;
  sns_ddf_sensor_info_s*  ddf_handle = (sns_ddf_sensor_info_s *) handle;
  int32_t txn_count = 0;
  I2cRegOffsetType reg_offset_type;
  
  switch (ddf_handle->i2c_s.reg_addr_type)
  {
    case SNS_DDF_I2C_REG_ADDR_16BIT:
      reg_offset_type = I2cRegOffset_16Bit;
      break;
	  
#ifndef SNS_USES_DISABLE_32_BIT_I2C_ADDRESSING
    case SNS_DDF_I2C_REG_ADDR_32BIT:
      reg_offset_type = I2cRegOffset_32Bit;
      break;
#endif  // SNS_USES_DISABLE_32_BIT_I2C_ADDRESSING
	  
    case SNS_DDF_I2C_REG_ADDR_8BIT:
    default:
      reg_offset_type = I2cRegOffset_8Bit;
      break;
  }
  
  for( i = 0; i < num_vectors; i++ )
  {
    
    if( vectors[i].is_write )
    {
      I2c_RegObj_InitWrite(&reg_obj[i]);
      I2c_RegObj_SetWriteIoVector(&reg_obj[i], vectors[i].buffer, vectors[i].bytes);
    }
    else
    {
      I2c_RegObj_InitRead(&reg_obj[i]);
      I2c_RegObj_SetReadIoVector(&reg_obj[i], vectors[i].buffer, vectors[i].bytes);
    }

    I2c_RegObj_SetOffset(&reg_obj[i], vectors[i].reg_addr, reg_offset_type );

    transfer[txn_count] = reg_obj[i].aTr[0];
    transfer[txn_count].eTranCtxt = I2cTrCtxSeqContinue;
    if( !vectors[i].is_write )
    {
      txn_count++;
      transfer[txn_count] = reg_obj[i].aTr[1];
      transfer[txn_count].eTranCtxt = I2cTrCtxSeqContinue;
    }
    txn_count++;
  }

  if( txn_count == 1 )
  {
    transfer[txn_count-1].eTranCtxt = I2cTrCtxNotASequence;
  }
  else
  {
    transfer[0].eTranCtxt = I2cTrCtxSeqStart;
    transfer[txn_count-1].eTranCtxt = I2cTrCtxSeqEnd;
  }

  I2c_SeqObj_Init( &seq, transfer, txn_count);
    
  if( write_time != NULL )
  {
    sns_ddf_time_t start_time = sns_ddf_get_timestamp();
    // wait for next 32kHz clock tick, to align with clock edge
    do {
      *write_time = sns_ddf_get_timestamp();
    } while ( *write_time == start_time );
    // Hard-code I2C bus initilization time
    *write_time <<= 5;
    *write_time += I2C_BUS_TXN_SETUP_TIME;
  }
  result = I2cDrv_BatchTransfer( &ddf_handle->i2c_s.i2c_bus,
                                 &seq,
                                 &ioRes);
  if( total_bytes != NULL )
  {
    *total_bytes = (int32_t)(ioRes.uOutByteCnt) + (int32_t)(ioRes.uInByteCnt);
  }
  if ( result != I2C_RES_SUCCESS )
  {
    UMSG_1(MSG_SSID_SNS,DBG_ERROR_PRIO,"I2C_BatchTransfer result = %d", result);
    return SNS_DDF_EBUS;
  }
  return SNS_DDF_SUCCESS;
}
