/**
 * @file sns_ddf_uimg_comm_bus_spi.c
 * @brief Implementation of the Device Driver Framework communication module.
 *
 * @see sns_ddf_comm.h
 *
 * Copyright (c) 2014-2016 Qualcomm Technologies, Inc.  All Rights Reserved.
 * Qualcomm Technologies Proprietary and Confidential.
 */

/* $Header: //components/rel/ssc.slpi/2.2/ddf/src/sns_ddf_uimg_comm_bus_spi.c#1 $ */
/* $DateTime: 2017/04/17 22:20:39 $ */
/* $Author: pwbldsvc $ */

/*==============================================================================
  Edit History

  This section contains comments describing changes made to the module. Notice
  that changes are listed in reverse chronological order. Please use ISO format
  for dates.


  when       who  what, where, why
  ---------- ---  -----------------------------------------------------------
  2016-05-04 jtl  Update write_time support.
                  Enable SPI clock only once for vectored read/writes
  2016-04-21 jtl  Fixing return value for bytes written/read
  2016-01-26 ps   Remove flags to use SPI in virtio bringup
  2015-04-28 jms  Cleaning set/get spi clock
  2015-04-20 hw   Fix compiler warning
  2015-02-18 jms  Reducing SPI write buffer in DDF to 1 byte size
  2015-01-21 jms  SPI and BMI160 enabled on SLPI 1.0
  2014-09-02 jms  SPI refactored for uImage
==============================================================================*/

#include "sns_ddf_comm.h"
#include "sns_profiling.h"
#include "sns_ddf_util.h"
#include "sns_debug_str.h"
#include "sns_memmgr.h"

#include "sns_ddf_comm_priv.h"

/*----------------------------------------------------------------------------
 * Private Function Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

#define DDF_COMM_MAX( ARG1, ARG2 )         (((ARG1) > (ARG2)) ? (ARG1) : (ARG2))


//SPI read buffer size in bytes corresponding to LSM6DSM FIFO size
#define SNS_DDF_SPI_BUF_SIZE 4096

// In units of 1/1048576 seconds.
#define SPI_BUS_TXN_SETUP_TIME 57 /* 54.3 uSec */

/*----------------------------------------------------------------------------
 * Private Structure Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Public Global Variables
 * -------------------------------------------------------------------------*/

volatile bool EnableSPI = true;

/*----------------------------------------------------------------------------
 * Local Variables
 * -------------------------------------------------------------------------*/

//============================================================================
//============================================================================
//                        PUBLIC SPI BUS API
//============================================================================
//============================================================================

//============================================================================
/**
 * @brief Set the bus min and max clock frequencies
 *
 * @param[in/out] handle  Pointer to the bus information
 * @param[in]  min_slave_frequency_hz min clock freq
 * @param[in]  max_slave_frequency_hz max clock freq
 *
 * @return SNS_DDF_SUCCESS if the operation was done successfully.
 *         Otherwise SNS_DDF_EDEVICE, SNS_DDF_EBUS, SNS_DDF_EINVALID_PARAM, or
 *         SNS_DDF_EFAIL to indicate an error has occurred.
 */
sns_ddf_status_e sns_ddf_comm_bus_spi_set_clk_freq_hz
(
    const sns_ddf_handle_t    handle,
    uint32_t                  min_slave_frequency_hz,
    uint32_t                  max_slave_frequency_hz
)
{
  if ( handle == NULL )
  {
    UMSG( MSG_SSID_SNS, DBG_ERROR_PRIO, "arg is NULL");
    return SNS_DDF_EINVALID_PARAM;
  }
  if ( ((sns_ddf_sensor_info_s*)handle)->bus != SNS_DDF_BUS_SPI )
  {
       return SNS_DDF_EINVALID_PARAM;
  }

#if SNS_DDF_COMM_BUS_SPI_ENABLE_DRIVER
  sns_ddf_spi_config_s* cfg = ((sns_ddf_sensor_info_s*)handle)->spi_s.cfg;
  cfg->min_slave_freq_hz = min_slave_frequency_hz;
  cfg->max_slave_freq_hz = max_slave_frequency_hz;
#endif
  return SNS_DDF_SUCCESS;
}

//============================================================================
/**
 * @brief Get the bus min and max clock frequencies
 *
 * @param[in]   handle  Pointer to the bus information
 * @param[out]  min_slave_frequency_hz min clock freq
 * @param[out]  max_slave_frequency_hz max clock freq
 *
 * @return SNS_DDF_SUCCESS if the operation was done successfully.
 *         Otherwise SNS_DDF_EDEVICE, SNS_DDF_EBUS, SNS_DDF_EINVALID_PARAM, or
 *         SNS_DDF_EFAIL to indicate an error has occurred.
 */
sns_ddf_status_e sns_ddf_comm_bus_spi_get_clk_freq_hz
(
    const sns_ddf_handle_t    handle,
    uint32_t*                 min_slave_frequency_hz,
    uint32_t*                 max_slave_frequency_hz
)
{
  if ( handle == NULL ||
       min_slave_frequency_hz == NULL ||
       max_slave_frequency_hz == NULL )
  {
    UMSG( MSG_SSID_SNS, DBG_ERROR_PRIO, "arg is NULL");
    return SNS_DDF_EINVALID_PARAM;
  }
  if ( ((sns_ddf_sensor_info_s*)handle)->bus != SNS_DDF_BUS_SPI )
  {
    return SNS_DDF_EINVALID_PARAM;
  }

#if SNS_DDF_COMM_BUS_SPI_ENABLE_DRIVER
  const sns_ddf_spi_config_s* cfg = ((sns_ddf_sensor_info_s*)handle)->spi_s.cfg;
  *min_slave_frequency_hz = cfg->min_slave_freq_hz;
  *max_slave_frequency_hz = cfg->max_slave_freq_hz;
#endif
  return SNS_DDF_SUCCESS;
}

//============================================================================
/**
 * @brief Enable or disable spi "clk always on" in idle
 *
 * @param[in/out] handle  Pointer to the bus information
 * @param[in]     spi_clk_always_on flag status
 *
 * @return SNS_DDF_SUCCESS if the operation was done successfully.
 *         Otherwise SNS_DDF_EDEVICE, SNS_DDF_EBUS, SNS_DDF_EINVALID_PARAM, or
 *         SNS_DDF_EFAIL to indicate an error has occurred.
 */
sns_ddf_status_e sns_ddf_comm_bus_spi_set_clk_always_on
(
    const sns_ddf_handle_t    handle,
    bool                      spi_clk_always_on
)
{
#if SNS_DDF_COMM_BUS_SPI_ENABLE_DRIVER
  spi_device_id_t   spi_dev_id;

  if ( handle == NULL )
  {
    UMSG( MSG_SSID_SNS, DBG_ERROR_PRIO, "arg is NULL");
    return SNS_DDF_EINVALID_PARAM;
  }
  if ( ((sns_ddf_sensor_info_s*)handle)->bus != SNS_DDF_BUS_SPI )
  {
       return SNS_DDF_EINVALID_PARAM;
  }

  ((sns_ddf_sensor_info_s*)handle)->spi_s.cfg->spi_clk_always_on = spi_clk_always_on;


  spi_dev_id = ((sns_ddf_sensor_info_s*)handle)->spi_s.dev_id;

  //TODO  change clk state
  if ( spi_open( spi_dev_id ) != SPI_SUCCESS )
  {
    return SNS_DDF_EBUS;
  }
  spi_close( spi_dev_id );
#endif

  return SNS_DDF_SUCCESS;
}


//TODO: Other get/set functions to be implemented in relation to SPI driver new API



//============================================================================
/**
*  @brief Performs SPI data transfer
*
* @param[in]   handle        The I/O port handle that identifies a device. This
*                            is given to drivers as part of initialization.
* @param[out]  read_buffer   Pointer to the buffer to which data read is deposited to.
*                            NULL allowed for write operation.
* @param[in]   read_len      Maximum number of bytes that can be stored in read_buffer.
*                            0 allowed for write operation.
* @param[in]   write_buffer  Pointer to buffer that contains the data to be written.
* @param[in]   write_len     Maximum number of bytes that can be stored in write_buffer.
* @param[out]  tx_count      Number of bytes transfered.
* @param[out]  write_time    System time write was performed, in SSC ticks << 5.
*
* @return SNS_DDF_SUCCESS if the operation was done successfully.
*         Otherwise SNS_DDF_EINVALID_PARAM or SNS_DDF_EBUS to indicate the error.
*
*/
sns_ddf_status_e sns_ddf_spi_data_transfer_timed
(
    const sns_ddf_handle_t  handle,
    uint8_t*                read_buffer,  //NULL allowed for write operation
    uint32_t                read_len,
    const uint8_t*          write_buffer,
    uint32_t                write_len,
    uint32_t*               tx_count,
    uint64_t*               write_time
)
{
#if SNS_DDF_COMM_BUS_SPI_ENABLE_DRIVER
  SPI_RESULT        spi_result; //spi_errors.h
  SPI_RESULT        spi_open_result; //spi_errors.h
  spi_transaction_t read_transaction_info;
  spi_transaction_t write_transaction_info;
  spi_device_id_t   spi_dev_id;

  if ( handle       == NULL ||
       write_buffer == NULL ||
       write_len    == 0 )
  {
    return SNS_DDF_EINVALID_PARAM;
  }

  //NOTE: 8994 uses only spi_dev_id = SPI_DEVICE_12;
  spi_dev_id = ((sns_ddf_sensor_info_s*)handle)->spi_s.dev_id;

  read_transaction_info.buf_virt_addr = (void *)read_buffer;
  read_transaction_info.buf_phys_addr = (void *)read_buffer;
  read_transaction_info.buf_len       = read_len;

  write_transaction_info.buf_virt_addr = (void *)write_buffer;
  write_transaction_info.buf_phys_addr = (void *)write_buffer;
  write_transaction_info.buf_len       = write_len;


  if ( EnableSPI == false )
  {
    if ( tx_count != NULL )
    {
      *tx_count = read_len + write_len; //public API backward compatibility
    }
    return SNS_DDF_SUCCESS;
  }

  spi_open_result = spi_open( spi_dev_id );

  if( write_time != NULL )
  {
    sns_ddf_time_t start_time = sns_ddf_get_timestamp();
    // wait for next 32kHz clock tick, to align with clock edge
    do {
      *write_time = sns_ddf_get_timestamp();
    } while ( *write_time == start_time );
    // Hard-code SPI bus initilization time
    *write_time <<= 5;
    *write_time += SPI_BUS_TXN_SETUP_TIME;
  }

  // Perform a full duplex transfer ----------------------
  spi_result = spi_full_duplex( spi_dev_id,
                                ((sns_ddf_sensor_info_s*)handle)->spi_s.cfg,
                                &write_transaction_info, &read_transaction_info );
  if ( spi_result != SPI_SUCCESS )
  {
    spi_close(spi_dev_id);
    return SNS_DDF_EBUS;
  }

  if( spi_open_result == SPI_SUCCESS )
  {
    spi_close( spi_dev_id );
  }

  if ( tx_count != NULL )
  {
    *tx_count = read_len + write_len;  //public API backward compatibility
    //NOTE: *write_count / *read_count not implemented in SPI driver
    //Those should be the actual number of bytes written/read
  }
#endif

  return SNS_DDF_SUCCESS;
}


//============================================================================
/**
*  @brief Performs SPI data transfer
*
* @param[in]   handle        The I/O port handle that identifies a device. This
*                            is given to drivers as part of initialization.
* @param[out]  read_buffer   Pointer to the buffer to which data read is deposited to.
*                            NULL allowed for write operation.
* @param[in]   read_len      Maximum number of bytes that can be stored in read_buffer.
*                            0 allowed for write operation.
* @param[in]   write_buffer  Pointer to buffer that contains the data to be written.
* @param[in]   write_len     Maximum number of bytes that can be stored in write_buffer.
* @param[out]  read_count    Number of bytes transfered.
*
* @return SNS_DDF_SUCCESS if the operation was done successfully.
*         Otherwise SNS_DDF_EINVALID_PARAM or SNS_DDF_EBUS to indicate the error.
*
*/
sns_ddf_status_e sns_ddf_spi_data_transfer
(
    const sns_ddf_handle_t  handle,
    uint8_t*                read_buffer,  //NULL allowed for write operation
    uint32_t                read_len,
    const uint8_t*          write_buffer,
    uint32_t                write_len,
    uint32_t*               tx_count )
{
  return sns_ddf_spi_data_transfer_timed( handle, read_buffer, read_len,
                                          write_buffer, write_len, tx_count, NULL );
}

//============================================================================
//============================================================================
//                        PRIVATE  SPI  BUS
//============================================================================
//============================================================================

//============================================================================
/**
 * @brief Performs the spi bus read operation.
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
sns_ddf_status_e sns_ddf_comm_bus_spi_read
(
    const sns_ddf_handle_t  handle,
    uint16_t                reg_addr,
    uint8_t*                buffer,
    uint32_t                bytes,
    uint32_t*               read_count
)
{
  static uint8_t   read_buffer[SNS_DDF_SPI_BUF_SIZE];
  sns_ddf_status_e status;
  uint8_t          reg_addr8 = (uint8_t)reg_addr;

  if ( (bytes+1) > SNS_DDF_SPI_BUF_SIZE )
  {
    return SNS_DDF_ENOMEM;
  }

  SNS_OS_MEMSET( read_buffer,  0, (bytes+1) );

  reg_addr8 |= (1 << 7);   //set RW bit = 1 for read

  status = sns_ddf_spi_data_transfer(
        handle,
        read_buffer,
        bytes+1,
        &reg_addr8,
        sizeof(reg_addr8),
        read_count );

  if ( status != SNS_DDF_SUCCESS )
  {
    //SNS_PRINTF_STRING_ERROR_1(SNS_DBG_MOD_DSPS_DDF, "spi_data_transfer failed %u",status);
    return status;
  }

  SNS_OS_MEMCOPY( buffer, &read_buffer[1], bytes );
  //len+1 total spi transfers, 1 byte spi protocol overhead

  return SNS_DDF_SUCCESS;
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
sns_ddf_status_e sns_ddf_comm_bus_spi_write
(
    const sns_ddf_handle_t  handle,
    uint16_t                reg_addr,
    const uint8_t*          buffer,
    uint32_t                bytes,
    uint32_t*               write_count,
    uint64_t*               write_time
)
{
  sns_ddf_status_e status;
  //bytes+1 total spi transfers, 1 byte spi protocol overhead
  uint8_t          write_buffer[bytes+1];   //+1 byt
  uint8_t          reg_addr8 = (uint8_t)reg_addr;

  SNS_OS_MEMCOPY( &write_buffer[1], buffer, bytes );

  reg_addr8       &= (0xFF >> 1);        //set RW bit = 0 for write
  write_buffer[0]  = (uint8_t)reg_addr8; //NOTE: currently 8bit reg addr only

  status = sns_ddf_spi_data_transfer_timed(
        handle,
        NULL,           //read_dummy_buffer, NULL is allowed for write operation
        0,              //read_len
        write_buffer,
        bytes+1,
        write_count,
        write_time );

  if ( status != SNS_DDF_SUCCESS )
  {
    UMSG_1( MSG_SSID_SNS, DBG_ERROR_PRIO, "spi_data_transfer failed %u", status);
    return status;
  }

  return SNS_DDF_SUCCESS;
}

/**
 * @brief Reads and/or writes multiple registers
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
sns_ddf_status_e sns_ddf_comm_bus_spi_rw_v(
    const sns_ddf_handle_t      handle,
    const sns_ddf_rw_port_s    *vectors,
    int32_t                     num_vectors,
    int32_t                    *total_bytes,
    uint64_t                   *write_time )
{
  int               i;
  uint32_t          txn_count;
  SPI_RESULT        spi_open_result; //spi_errors.h
  spi_device_id_t   spi_dev_id;
  spi_dev_id = ((sns_ddf_sensor_info_s*)handle)->spi_s.dev_id;
  
  if( write_time != NULL )
  {
    *write_time = 0;
  }

  if( total_bytes != NULL )
  {
    *total_bytes = 0;
  }
  
  spi_open_result = spi_open( spi_dev_id );
  if ( spi_open_result != SPI_SUCCESS )
  {
    return SNS_DDF_EBUS;
  }

  for( i = 0; i < num_vectors; i++ )
  {
    txn_count = 0;
    if( vectors[i].is_write )
    {
      sns_ddf_comm_bus_spi_write( handle,
                                  vectors[i].reg_addr,
                                  vectors[i].buffer,
                                  vectors[i].bytes,
                                  &txn_count,
                                  write_time );
    }
    else
    {
      sns_ddf_comm_bus_spi_read( handle,
                                 vectors[i].reg_addr,
                                 vectors[i].buffer,
                                 vectors[i].bytes,
                                 &txn_count );
    }
    if( total_bytes )
    {
      *total_bytes += txn_count;
    }
  }

  spi_close( spi_dev_id );

  return SNS_DDF_SUCCESS;
}
