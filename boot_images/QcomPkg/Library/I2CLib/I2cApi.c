/*=============================================================================
     @file I2cApi.c
   
     I2C API code

    Copyright (c) 2014-2017 Qualcomm Technologies, Incorporated.
                        All rights reserved.
    Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/


/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 02/01/17   vg      Copyright updated
 02/19/15   unr     Configured noise values to avoid bus errors
 11/04/14   unr     Return correct error and use the right device instance
 08/15/14   unr     Created

=============================================================================*/

#include "DALDeviceId.h"
#include "I2cSys.h"

/* I2C Interfaces */
#include "I2cApi.h"
#include "I2cDevice.h"

/* List of I2C DAL Device IDs */
static UINT32 I2CDalDeviceList [] =
{
  DALDEVICEID_I2C_DEVICE_1,
  DALDEVICEID_I2C_DEVICE_2,
  DALDEVICEID_I2C_DEVICE_3,
  DALDEVICEID_I2C_DEVICE_4,
  DALDEVICEID_I2C_DEVICE_5,
  DALDEVICEID_I2C_DEVICE_6,
  DALDEVICEID_I2C_DEVICE_7,
  DALDEVICEID_I2C_DEVICE_8,
  DALDEVICEID_I2C_DEVICE_9,
  DALDEVICEID_I2C_DEVICE_10,
  DALDEVICEID_I2C_DEVICE_11,
  DALDEVICEID_I2C_DEVICE_12
};


/* i2c_open */ 
i2c_status
i2c_open(
    i2c_instance instance,
    void **i2c_handle
)
{
  int32 res;

  if (instance >= I2C_INSTANCE_MAX)
  {
    return I2C_ERROR_INVALID_PARAMETER;
  }

  res = I2CDEV_Init((void *) (UINTN) (I2CDalDeviceList[instance]), i2c_handle);
  if (res != I2C_RES_SUCCESS)
  {
    return I2C_ERROR_INIT;
  }

  res = I2CDEV_SetPowerState(*i2c_handle, I2CDEV_POWER_STATE_2);
  if (res != I2C_RES_SUCCESS)
  {
    return I2C_ERROR_POWER_ON;
  }

  return I2C_SUCCESS;
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
  uint8 reg[2];
  i2c_buffer_descriptor offsetd, datad;
  i2c_transfer_list     txfr[2];
  
  if ((NULL == i2c_handle)  ||
      (NULL == config)      ||
	   (NULL == buffer)      ||
	   (0 == buffer_len)     ||
      (0 == timeout_ms))      
  {
    return I2C_ERROR_INVALID_PARAMETER;
  }
  
  reg[0] = (uint8) (offset >> 8);
  reg[1] = (uint8) offset;
  
  if (offset_len == 1)
  {
    offsetd.buffer = &reg[1];
  }
  else
  {
    offsetd.buffer = reg;
  }

  offsetd.length = offset_len; 

  txfr[0].desc = &offsetd;
  txfr[0].no_of_descs = 1;
  txfr[0].write = 1;
  txfr[0].delay_ms = 0;

  datad.buffer = buffer;
  datad.length = buffer_len;

  txfr[1].desc = &datad;
  txfr[1].no_of_descs = 1;
  txfr[1].write = 0;
  txfr[1].delay_ms = 0;

  return i2c_transfer(i2c_handle, config, txfr, 2, NULL, read, timeout_ms);
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
  uint8 reg[2];
  i2c_buffer_descriptor desc[2];
  i2c_transfer_list     txfr;
  
  if ((NULL == i2c_handle)  ||
      (NULL == config)      ||
	  (NULL == buffer)      ||
	  (0 == buffer_len)     ||
      (0 == timeout_ms))      
  {
    return I2C_ERROR_INVALID_PARAMETER;
  }
  
  
  reg[0] = (uint8) (offset >> 8);
  reg[1] = (uint8) offset;
  
  if (offset_len == 1)
  {
    desc[0].buffer = &reg[1];
  }
  else
  {
    desc[0].buffer = reg;
  }
  desc[0].length = offset_len; 

  desc[1].buffer = buffer;
  desc[1].length = buffer_len;

  txfr.desc = desc;
  txfr.no_of_descs = 2;
  txfr.write = 1;
  txfr.delay_ms = 0;

  return i2c_transfer(i2c_handle, config, &txfr, 1, written, NULL, timeout_ms);
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
  I2cSequence      Sequence;
  I2cTransfer      *pTransfer = NULL;
  I2cBuffDesc      *pI2cBuffDesc = NULL;
  I2cBuffDesc      *pTempBuffDesc = NULL;
  I2cClientConfig  ClientConfig;
  I2cIoResult      I2cResult;
  int32            res = I2C_SUCCESS;
  uint32           index = 0; 
  uint32           total_no_of_descs = 0; 

  if ((NULL == i2c_handle)      ||
      (NULL == transfers)       ||
      (NULL == config)          ||
      (0    == no_of_transfers))
  {
    return I2C_ERROR_INVALID_PARAMETER;
  }

  /* Calculate the number of buffer descriptors. */
  for (index = 0; index < no_of_transfers; index++)
  {
    total_no_of_descs += (transfers + index)->no_of_descs;
  }

  res = I2CSYS_Malloc((void **) &pTransfer, sizeof(I2cTransfer) * no_of_transfers);
  if ((res != I2C_SUCCESS) || (pTransfer == NULL))
  {
    return I2C_ERROR_ALLOC_TRANSFER;
  }

  res = I2CSYS_Malloc((void **) &pI2cBuffDesc, sizeof(I2cBuffDesc) * total_no_of_descs);
  if ((res != I2C_SUCCESS) || (pI2cBuffDesc == NULL))
  {
    I2CSYS_Free(pTransfer);
    return I2C_ERROR_ALLOC_BUFFER_DESCRIPTOR;
  }

  pTempBuffDesc = pI2cBuffDesc;

  for (index = 0; index < no_of_transfers; index++)
  {
    uint32 desc_count = (transfers + index)->no_of_descs;
    uint32 tlen = 0;
    i2c_buffer_descriptor *i2c_desc = (transfers + index)->desc;
    I2cBuffDesc *pI2cBuffDescFirst = pI2cBuffDesc;

    while (desc_count > 0)
    {
      /* Initialize the buffer descriptor/s */
      pI2cBuffDesc->pBuff     = i2c_desc->buffer;
      pI2cBuffDesc->uBuffSize = i2c_desc->length;

      tlen += i2c_desc->length;
      
      desc_count--;
      pI2cBuffDesc++;
      i2c_desc++;
    }

    /* Initialize the Transfer */
    (pTransfer + index)->pI2cBuffDesc       = pI2cBuffDescFirst;
    (pTransfer + index)->uTrSize            = tlen;
    (pTransfer + index)->tranCfg.uSlaveAddr = config->slave_address;

    /* Set read or write transfer */
    if ((transfers + index)->write)
    {
      (pTransfer + index)->eTranDirection = I2cTranDirOut;
    }
    else
    {
      (pTransfer + index)->eTranDirection = I2cTranDirIn;
    }

    /* Set Start, Continue and End attributes for the transfer */
    if (no_of_transfers == 1)
    {
      (pTransfer + index)->eTranCtxt = I2cTrCtxNotASequence;
    }
    else if (index == 0)
    {
      (pTransfer + index)->eTranCtxt = I2cTrCtxSeqStart;
    }
    else if (index == (no_of_transfers - 1))
    {
      (pTransfer + index)->eTranCtxt = I2cTrCtxSeqEnd;
    }
    else
    {
      (pTransfer + index)->eTranCtxt = I2cTrCtxSeqContinue;
    }
  }

  /* Initialize the Sequence */
  Sequence.pTransfer = pTransfer;
  Sequence.uNumTransfers = no_of_transfers;

  ClientConfig.uBusFreqKhz = config->bus_frequency_khz;
  ClientConfig.uByteTransferTimeoutUs = timeout_ms * 1000;
  ClientConfig.uBusSDANR = 1;
  ClientConfig.uBusSCLNR = 1;

  res = I2CDEV_BatchTransfer (i2c_handle,
      &Sequence,
      &ClientConfig,
      &I2cResult);

  if (res == I2C_RES_SUCCESS)
  {
    if (written != NULL)
    {
      *written = I2cResult.uOutByteCnt; 
    }

    if (read != NULL)
    {
      *read = I2cResult.uInByteCnt; 
    }
  }

  if (pTempBuffDesc != NULL)
  {
    I2CSYS_Free(pTempBuffDesc);
  }

  if (pTransfer)
  {
    I2CSYS_Free(pTransfer);
  }

  return (i2c_status) res;
}

/* i2c_close */ 
i2c_status
i2c_close(
    void *i2c_handle
)
{
  int32 res;

  res = I2CDEV_DeInit (i2c_handle);
  if (res != I2C_RES_SUCCESS)
  {
    return I2C_ERROR_DEINIT;
  }
 
  return I2C_SUCCESS;
}
