
/*=============================================================================   
     @file I2cApi.c
   
    Copyright (c) 2014-2017 Qualcomm Technologies, Incorporated.
                        All rights reserved.
    Qualcomm Technologies, Confidential and Proprietary.
===============================================================================*/

/*=============================================================================
                              EDIT HISTORY
 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 03/10/17   vg      Added i/p param validation
 02/01/17   vg      Copyright updated 
 08/18/14   unr     Created

=============================================================================*/

#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>

/* I2C Interfaces */
#include <Protocol/EFII2C.h>

static EFI_QCOM_I2C_PROTOCOL *i2c_io = NULL;

/* i2c_open */ 
i2c_status
i2c_open(
    i2c_instance instance,
    void **i2c_handle
)
{
  EFI_STATUS estatus = EFI_SUCCESS;
  
  if (i2c_handle == NULL)
  {
    DEBUG((EFI_D_ERROR, "I2C protocol handle is invalid\n"));
    return I2C_ERROR_DRV_FWK_NULL_HANDLE;
  }
  
  /* Get the I2C protocol handle */
  estatus = gBS->LocateProtocol(&gQcomI2CProtocolGuid, NULL, (VOID **) &i2c_io);
  if ((EFI_SUCCESS != estatus) || (NULL == i2c_io))
  {
    DEBUG((EFI_D_ERROR, "Failed to get I2C protocol 0x%08x\n", estatus));
    return I2C_ERROR_DRV_FWK_INIT;
  }

  return i2c_io->open(
      instance,
      i2c_handle);
}

/* i2c_read */
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
)
{
  if (i2c_io == NULL)
  {
    DEBUG((EFI_D_ERROR, "I2C protocol handle is invalid\n"));
    return I2C_ERROR_DRV_FWK_NULL_HANDLE;
  }

  return i2c_io->read(
      i2c_handle,
      config,
      offset,
      offset_len,
      buffer,
      buffer_len,
      read,
      timeout_ms);
}

/* i2c_write */
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
)
{
  if (i2c_handle == NULL)
  {
    DEBUG((EFI_D_ERROR, "I2C protocol handle is invalid\n"));
    return I2C_ERROR_DRV_FWK_NULL_HANDLE;
  }

  return i2c_io->write(
      i2c_handle,
      config,
      offset,
      offset_len,
      buffer,
      buffer_len,
      written,
      timeout_ms);
}

/* i2c_transfer */ 
i2c_status
i2c_transfer(
    void *i2c_handle,
    i2c_config *config,
    i2c_transfer_list *transfers,
    uint32 no_of_transfers,
    uint32 *written,
    uint32 *read,
    uint32 timeout_ms
)
{
  if (i2c_handle == NULL)
  {
    DEBUG((EFI_D_ERROR, "I2C protocol handle is invalid\n"));
    return I2C_ERROR_DRV_FWK_NULL_HANDLE;
  }

  return i2c_io->transfer(
      i2c_handle,
      config,
      transfers,
      no_of_transfers,
      written,
      read,
      timeout_ms);
}

/* i2c_close */ 
i2c_status
i2c_close(
    void *i2c_handle
)
{
  if (i2c_handle == NULL)
  {
    DEBUG((EFI_D_ERROR, "I2C protocol handle is invalid\n"));
    return I2C_ERROR_DRV_FWK_NULL_HANDLE;
  }

  return i2c_io->close(
      i2c_handle);
}
