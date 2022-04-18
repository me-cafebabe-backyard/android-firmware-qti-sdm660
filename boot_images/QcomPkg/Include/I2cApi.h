/** 
  @file  I2cApi.h
  @brief I2C APIs
*/
/*=============================================================================
  Copyright (c) 2014 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 08/12/14   unr     Created

=============================================================================*/

#ifndef __I2CAPI_H__
#define __I2CAPI_H__

#include "I2cTypes.h"

/** @addtogroup i2c_data_types 
@{ */

/**
  I2C core passed to the i2c_open() function. 
*/
typedef enum {
  I2C_INSTANCE_001,          /**< Instance 01. */
  I2C_INSTANCE_002,          /**< Instance 02. */
  I2C_INSTANCE_003,          /**< Instance 03. */
  I2C_INSTANCE_004,          /**< Instance 04. */
  I2C_INSTANCE_005,          /**< Instance 05. */
  I2C_INSTANCE_006,          /**< Instance 06. */
  I2C_INSTANCE_007,          /**< Instance 07. */
  I2C_INSTANCE_008,          /**< Instance 08. */
  I2C_INSTANCE_009,          /**< Instance 09. */
  I2C_INSTANCE_010,          /**< Instance 10. */
  I2C_INSTANCE_011,          /**< Instance 11. */
  I2C_INSTANCE_012,          /**< Instance 12. */

  I2C_INSTANCE_MAX,          /**< Instance Check. */

} i2c_instance;

/**
  Function status codes.
*/
typedef enum {
   I2C_SUCCESS,
   /**< Operation succeeded. */
   I2C_ERROR_INVALID_PARAMETER,
   /**< Invalid parameter. */
   I2C_ERROR_INIT,
   /**< Initialization failed. */
   I2C_ERROR_DEINIT,
   /**< De-initialization failed. */
   I2C_ERROR_POWER_ON,
   /**< Power ON sequence failed. */
   I2C_ERROR_ALLOC_BUFFER_DESCRIPTOR,
   /**< Buffer Allocation failed. */
   I2C_ERROR_ALLOC_TRANSFER,
   /**< Transfer Allocation failed. */
   I2C_ERROR_SLAVE_ADDRESS_NACK,
   /**< Slave not present or not configured. */
   I2C_ERROR_SLAVE_DATA_NACK,
   /**< Slave did not acknowledge data. */
   I2C_ERROR_DRV_FWK_INIT,
   /**< Driver framework specific initiliazation failed. */
   I2C_ERROR_DRV_FWK_NULL_HANDLE
   /**< Driver framework specific handle is invalid. */

} i2c_status;

/**
  Slave address length in bits used in the #i2c_config data structure.
*/
typedef enum
{
   I2C_07_BIT_SLAVE_ADDRESS, /**< 7-bit slave address. */
   I2C_10_BIT_SLAVE_ADDRESS, /**< 10-bit slave address. */

} i2c_slave_address_type;

/**
  I2C configuration passed to the i2c_transfer() function.
*/
typedef struct
{
  uint32 bus_frequency_khz;
  /**< Bus frequency in kHz. */
  uint32 slave_address;
  /**< Slave address. */
  i2c_slave_address_type slave_address_type;
  /**< Slave address Type; see #i2c_slave_addr_type for details. */

} /** @cond */i2c_config/** @endcond */;

/**
  I2C buffer descriptor passed in i2c_transfer structure.
*/
typedef struct
{
  uint8     *buffer;
  /**< Buffer. */
  uint32     length;
  /**< Length of the buffer. */

} /** @cond */i2c_buffer_descriptor/** @endcond */;

/**
  I2C Transfer passed to i2c_transfer() function.
*/
typedef struct
{
  i2c_buffer_descriptor *desc;
  /**< Read or Write buffer. */
  uint32                no_of_descs;
  /**< Number of buffer descriptors. */
  boolean               write;
  /**< Flags that define transfer behavior. */
  uint32                delay_ms;
  /**< Delay before executing transfer in milliseconds. */

} /** @cond */i2c_transfer_list/** @endcond */;
/** @} */ /* end_addtogroup i2c_data_types */

/*===========================================================================
  FUNCTION DEFINITIONS
===========================================================================*/
/* i2c_open */ 
/** @ingroup i2c_open
  @par Summary
  This function is called by the client code to initialize the respective 
  I2C core instance used by the client. On success, i2c_handle points to the handle 
  for the I2C core. 
  
  @param[in]  instance              I2C core instance that the client intends to
                                    initialize; see #i2c_instance for 
                                    details.
  @param[out] i2c_handle            Pointer location to be filled by the
                                    driver with a handle to the core.

  @return
  See #i2c_status for details.
*/
i2c_status
i2c_open(
    i2c_instance instance,
    void **i2c_handle
);

/* i2c_read */
/** @ingroup i2c_read
  @par Summary
  Performs an i2c read. Optionally reads from an offset.

  @param[in]  i2c_handle            Handle to the I2C core.
  @param[in]  config                Slave configuration. See #i2c_config for
                                    details.
  @param[in]  offset                If offset_len is non zero, this parameter
                                    specifies either the register or memory
                                    offset to read data from.
                                    #i2c_transfer for details.
  @param[in]  offset_len            Length of the offset. For simple slaves,
                                    this is 0. For register addressed slaves, it
                                    is 1 and for memory addressed slaves it is
                                    2.
  @param[out] buffer                Buffer into which data is read.
  @param[in]  buffer_len            Length of data that needs to be read.
                                    the slave.
  @param[out] read                  Number of bytes actually read.
  @param[in]  timeout_ms            Timeout value in milliseconds for transfer
                                    to complete.

  @return 
  See #i2c_status for details.
*/
i2c_status
i2c_read(
    void *i2c_handle,
    i2c_config *config,
    uint16 offset,
    uint16 offset_len,
    uint8  *buffer,
    uint16 buffer_len,
    uint32 *read,
    uint32 timeout_ms
);

/* i2c_write */
/** @ingroup i2c_write
  @par Summary
  Performs an i2c write. Optionally writes to an offset.

  @param[in]  i2c_handle            Handle to the I2C core.
  @param[in]  config                Slave configuration. See #i2c_config for
                                    details.
  @param[in]  offset                If offset_len is non zero, this parameter
                                    specifies either the register or memory
                                    offset to write data to.
                                    #i2c_transfer for details.
  @param[in]  offset_len            Length of the offset. For simple slaves,
                                    this is 0. For register addressed slaves, it
                                    is 1 and for memory addressed slaves it is
                                    2.
  @param[out] buffer                Buffer from which data is written.
  @param[in]  buffer_len            Length of data that needs to be written.
                                    the slave.
  @param[out] written               Number of bytes actually written.
  @param[in]  timeout_ms            Timeout value in milliseconds for transfer
                                    to complete.

  @return 
  See #i2c_status for details.
*/
i2c_status
i2c_write(
    void *i2c_handle,
    i2c_config *config,
    uint16 offset,
    uint16 offset_len,
    uint8  *buffer,
    uint16 buffer_len,
    uint32 *written,
    uint32 timeout_ms
);

/* i2c_transfer */ 
/** @ingroup i2c_transfer
  @par Summary
  Transfers an array of I2C transfers.

  @param[in]  i2c_handle            Handle to the I2C core.
  @param[in]  config                Slave configuration. See #i2c_config for
                                    details.
  @param[in]  transfers             An array of read and write trasnfers. See
                                    #i2c_transfer for details.
  @param[out] no_of_transfers       Number of transfers in the transfers array.
  @param[out] written               Number of bytes successfully written to
                                    the slave.
  @param[out] read                  Number of bytes actually read.
  @param[in]  timeout_ms            Timeout value in milliseconds for transfer
                                    to complete.

  @return 
  See #i2c_status for details.
*/
i2c_status
i2c_transfer(
    void *i2c_handle,
    i2c_config *config,
    i2c_transfer_list *transfers,
    uint32 no_of_transfers,
    uint32 *written,
    uint32 *read,
    uint32 timeout_ms
);

/* i2c_close */ 
/** @ingroup i2c_close
  @par Summary
  De-initializes the I2C core.

  @param[in] i2c_handle             Handle to the I2C core.

  @return
  See #i2c_status for details.
*/
i2c_status
i2c_close(
    void *i2c_handle
);

#endif	/* __I2CAPI_H__ */
