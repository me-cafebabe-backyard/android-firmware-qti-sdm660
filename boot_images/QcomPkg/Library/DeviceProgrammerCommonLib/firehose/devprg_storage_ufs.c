/**************************************************************************
 * FILE: devprg_storage_ufs.c
 *
 * UFS device interface.
 *
 * Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Qualcomm Proprietary
 *
 *************************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/boot.xf/1.4/QcomPkg/Library/DeviceProgrammerCommonLib/firehose/devprg_storage_ufs.c#2 $
  $DateTime: 2016/08/19 05:58:45 $
  $Author: c_mvanim $

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2016-02-10   wek   Add the option to format whole dev or erase a portion.
2016-01-19   rh    Fix the allocation unit size if segment is not 4MB.
2016-01-07   wek   Get FW version from get info.
2015-12-04   wek   Create. (9-m)

===========================================================================*/

#ifdef FEATURE_DEVPRG_UFS

#include "devprg_storage.h"
#include "devprg_storage_ufs.h"
#include "devprg_log.h"
#include "ufs_api.h"
#include "stringl/stringl.h"
#include <string.h>

struct dp_storage_ufs
{
  struct ufs_handle *handle;
  char in_use;
  uint8 lun; /* LUN opened. */
};

#ifndef DEVPRG_MAX_UFS_PHY_PARTITIONS
#define DEVPRG_MAX_UFS_PHY_PARTITIONS   10
#endif

static struct dp_storage_ufs dp_ufs_data[DEVPRG_MAX_UFS_PHY_PARTITIONS];

#define DEVPRG_MAX_UFS_SLOTS   8
/* Slot initialized bitmap, bit set to 1 if the slot was initialized.  */
static uint8 slot_init_bitmap = 0;

static enum devprg_error translate_ufs_error_simple(int32 error)
{
  enum devprg_error e;

  switch(error)
  {
  case UFS_EOK:
    e = DEVPRG_SUCCESS;
    break;
  case UFS_EINVAL:
    e = DEVPRG_ERROR_INVAL_PARAM;
    break;
  case UFS_ENOENT:
  case UFS_EIO:
  case UFS_ENOMEM:
  case UFS_EBUSY:
  case UFS_ENODEV:
  case UFS_EPROTO:
  case UFS_ETIME:
  default:
    e = DEVPRG_ERROR_STORAGE;
    break;
  }

  return e;
}

static enum devprg_error translate_ufs_error(int32 error)
{
  enum devprg_error e;

  e = translate_ufs_error_simple(error);

  if(e != DEVPRG_SUCCESS)
  {
    DP_LOGE("UFS Error %d (%d)", error, e);
  }

  return e;
}

void devprg_storage_ufs_init(void)
{
  int i;

  for(i = 0; i < DEVPRG_MAX_UFS_PHY_PARTITIONS; i++)
  {
    dp_ufs_data[i].handle = NULL;
    dp_ufs_data[i].in_use = 0;
  }

  slot_init_bitmap = 0;
}

int devprg_storage_ufs_deinit(void)
{
  return DEVPRG_SUCCESS;
}

void *devprg_storage_ufs_open(uint32 slot, uint32 partition, enum devprg_error *error)
{
  struct dp_storage_ufs *dev;
  struct ufs_handle *handle;
  int i, slot_init;

  if(slot > DEVPRG_MAX_UFS_SLOTS)
  {
    DP_LOGE("Code supports a maximum of %d slots, tried to open slot %d",
            DEVPRG_MAX_UFS_SLOTS, slot);
    *error = DEVPRG_ERROR_INVAL_PARAM;
    return NULL;
  }

  /* find an empty handle. */
  dev = NULL;

  for(i = 0; i < DEVPRG_MAX_UFS_PHY_PARTITIONS; i++)
  {
    if(dp_ufs_data[i].in_use == 0)
    {
      dev = &dp_ufs_data[i];
      break;
    }
  }

  if(dev == NULL)
  {
    *error = DEVPRG_ERROR_NOMEM;
    DP_LOGE("Ran out of physical partitions to allocate %d",
            DEVPRG_MAX_UFS_PHY_PARTITIONS);
    DP_LOGI("Device type ufs slot %d, partition %d, error %d",
            slot, partition, *error);
    return NULL;
  }

  /* Check if the slot has been initialized. */
  slot_init = (slot_init_bitmap >> slot) & 0x01;

  if(slot_init == 0)
  {
    /* Initialize the slot. */
    handle = ufs_open(slot, UFS_WLUN_DEVICE);

    if(handle == NULL)
    {
      DP_LOGE("Failed to initialize (open whole lun) UFS Device slot %d partition %d",
              slot, partition);
      return NULL;
    }

    ufs_close(handle);
    slot_init_bitmap |= (1 << slot);
  }

  if(partition == DEVPRG_WHOLE_DEVICE_PARTITION)
    partition = UFS_WLUN_DEVICE;

  handle = ufs_open(slot, partition);

  if(handle == NULL)
  {
    DP_LOGE("Failed to open the UFS Device slot %d partition %d",
            slot, partition);
    return NULL;
  }

  dev->handle = handle;
  dev->in_use = 1;
  dev->lun = partition;

  return dev;
}

int devprg_storage_ufs_close(void *device)
{
  struct dp_storage_ufs *dev = (struct dp_storage_ufs *)device;
  int32 result;

  result = ufs_close(dev->handle);

  if(result == UFS_EOK)
  {
    dev->in_use = 0;
    dev->handle = NULL;
  }

  return translate_ufs_error(result);
}

int devprg_storage_ufs_read(void *device, void *buffer,
                            uint64 start_sector, uint64 num_sectors)
{
  struct dp_storage_ufs *dev = (struct dp_storage_ufs *)device;
  int32 result = 0;

  result = ufs_read(dev->handle, buffer, start_sector, num_sectors);

  return translate_ufs_error_simple(result);

}

int devprg_storage_ufs_write(void *device, void *buffer,
                             uint64 start_sector, uint64 num_sectors)
{
  struct dp_storage_ufs *dev = (struct dp_storage_ufs *)device;
  int32 result;
  enum devprg_error error;

  result = ufs_write(dev->handle, buffer, start_sector, num_sectors);

  if(result != UFS_EOK)
  {
    error = translate_ufs_error(result);
    return error;
  }

  return DEVPRG_SUCCESS;
}

int devprg_storage_ufs_erase(void *device,
                             uint64 start_sector, uint64 num_sectors)
{
  struct dp_storage_ufs *dev = (struct dp_storage_ufs *)device;
  int32 result;
  enum devprg_error error;

  result = ufs_unmap(dev->handle, start_sector, num_sectors);

  if(result != UFS_EOK)
  {
    error = translate_ufs_error(result);
    return error;
  }

  return DEVPRG_SUCCESS;
}


int devprg_storage_ufs_format(void *device)
{
  struct dp_storage_ufs *dev = (struct dp_storage_ufs *)device;
  int32 result;
  enum devprg_error error;

  DP_LOGD("UFS Format whole LUN %s", " ");
  result = ufs_format(dev->handle);

  if(result != UFS_EOK)
  {
    error = translate_ufs_error(result);
    return error;
  }

  return DEVPRG_SUCCESS;
}

int devprg_storage_ufs_set_bootable(void *device, int enable)
{
  struct dp_storage_ufs *dev = (struct dp_storage_ufs *)device;
  int32 result;
  enum devprg_error error;
  uint32 lun = dev->lun;

  if(enable == 0)
  {
    lun = 0; /* Set the LUN to zero to disable. */
  }
  else
  {
    /* Get the currently open LUN. */
    struct ufs_info_type ufs_info;
    result = ufs_get_device_info(dev->handle, &ufs_info);

    if(result != UFS_EOK)
    {
      error = translate_ufs_error(result);
      DP_LOGE("Get info Failed for set bootable %s", " ");
      return error;
    }

    lun = ufs_info.bLUN;
  }

  result = ufs_set_bootable(dev->handle, lun);

  if(result != UFS_EOK)
  {
    error = translate_ufs_error(result);
    return error;
  }

  return DEVPRG_SUCCESS;
}

int devprg_storage_ufs_get_info(void *device,
                                struct devprg_storage_info *dev_info)
{
  struct dp_storage_ufs *dev = (struct dp_storage_ufs *)device;
  int32 result;
  enum devprg_error error;
  struct ufs_info_type info;
  uint64 serial;

  result = ufs_get_device_info(dev->handle, &info);

  if(result != UFS_EOK)
  {
    error = translate_ufs_error(result);
    return error;
  }

  /* Unalined access is not allowed by some cores and the compiler
   * does not correct for this on this case. Read the serial number
   * byte by byte. */
  serial = 0;
  serial += info.inquiry_str[info.iSerialNumber] << 24;
  serial += info.inquiry_str[info.iSerialNumber+1] << 16;
  serial += info.inquiry_str[info.iSerialNumber+2] << 8;
  serial += info.inquiry_str[info.iSerialNumber+3];

  dev_info->page_size       = info.bMinAddrBlockSize * 512;
  dev_info->block_size      = info.bMinAddrBlockSize * 512;
  dev_info->total_blocks    = info.dLuTotalBlocks;
  dev_info->manufacturer_id = info.wManufacturerID;
  dev_info->serial_num      = serial;
  dev_info->num_physical    = info.bNumberLu;

  /* According to the UFS Spec, Table 11.3 and 11.4 the version number is 4
     bytes with any ASCII value at the end of the inquiry string. */
  strlcpy(dev_info->fw_version, (char *)&info.inquiry_str[25],
          sizeof(dev_info->fw_version));
  strlcpy(dev_info->memory_type, "UFS", sizeof(dev_info->memory_type));
  strlcpy(dev_info->product_name, (char *)&info.inquiry_str[8],
          sizeof(dev_info->product_name));

  return DEVPRG_SUCCESS;
}

static void devprg_ufs_copy_cfg_data(struct ufs_config_descr *config,
                                     struct devprg_ufs_config_descr *configure)

{
  unsigned int i, number_of_luns;

  /* Copy the configuration items to the internal data structure, the two
   * structures are basically the same but the offset/address of each member
   * may be different due to alignment. */
  config->bNumberLU = configure->bNumberLU;
  config->bBootEnable = configure->bBootEnable;
  config->bDescrAccessEn = configure->bDescrAccessEn;
  config->bInitPowerMode = configure->bInitPowerMode;
  config->bHighPriorityLUN = configure->bHighPriorityLUN;
  config->bSecureRemovalType = configure->bSecureRemovalType;
  config->bInitActiveICCLevel = configure->bInitActiveICCLevel;
  config->bConfigDescrLock = configure->bConfigDescrLock;
  config->wPeriodicRTCUpdate = configure->wPeriodicRTCUpdate;
  config->qVendorConfigCode = configure->qVendorConfigCode;

  number_of_luns = sizeof(configure->unit) / sizeof(struct devprg_ufs_unit_descr);

  for(i = 0; i < number_of_luns; i++)
  {
    struct ufs_unit_descr *dest = &config->unit[i];
    struct devprg_ufs_unit_descr *src = &configure->unit[i];
    dest->bLUEnable = src->bLUEnable;
    dest->bBootLunID = src->bBootLunID;
    dest->bLUWriteProtect = src->bLUWriteProtect;
    dest->bMemoryType = src->bMemoryType;
    dest->dNumAllocUnits = src->dNumAllocUnits;
    dest->bDataReliability = src->bDataReliability;
    dest->bLogicalBlockSize = src->bLogicalBlockSize;
    dest->bProvisioningType = src->bProvisioningType;
    dest->wContextCapabilities = src->wContextCapabilities;
  }
}

int devprg_storage_ufs_configure(uint32 slot,
                                 struct devprg_storage_cfg_data *configure)
{
  int32 result;
  enum devprg_error error = DEVPRG_SUCCESS;
  struct ufs_handle *dev;
  struct ufs_info_type info;
  struct ufs_config_descr ufs_config;
  uint32 block_size;
  uint64 blocks_per_alloc_unit; /* Max value theoretical 2^40 */
  uint64 piece_alloc_unit; /* How many 512 chunks are in one alloc unit ?*/
  uint64 total_alloc_units;/* Number of allocation units on the device. */
  uint64 units_to_create, enhanced1_units, enhanced2_units;
  int i;

  devprg_ufs_copy_cfg_data(&ufs_config, &configure->ufs_config);

  dev = ufs_open(slot, UFS_WLUN_DEVICE);
  if(dev == NULL)
  {
    DP_LOGE("ufs_open(%d, WLUN_DEV) failed for configure", slot);
    return DEVPRG_ERROR_STORAGE;
  }

  ufs_set_refclk_freq(dev, 19200000);

  result = ufs_get_device_info(dev, &info);

  if(result != UFS_EOK)
  {
    error = translate_ufs_error(result);
    DP_LOGE("Get Dev Info Failed in Configure slot %d", slot);
    goto cleanup;
  }

  block_size = info.bMinAddrBlockSize * 512;
  blocks_per_alloc_unit =
    (info.dSegmentSize * info.bAllocationUnitSize) / info.bMinAddrBlockSize;

  if(blocks_per_alloc_unit == 0)
  {
    DP_LOGD("Unsupported UFS memory type %d slot %d", info.bMemoryType, slot);
    goto cleanup;
  }

  piece_alloc_unit = (info.dSegmentSize * info.bAllocationUnitSize);

  if((info.qTotalRawDeviceCapacity % piece_alloc_unit) != 0)
  {
    error = DEVPRG_ERROR_STORAGE;
    DP_LOGE("Raw capacity not a multiple of alloc unit size %d %d",
            info.qTotalRawDeviceCapacity, piece_alloc_unit);
    goto cleanup;
  }

  total_alloc_units = (info.qTotalRawDeviceCapacity / piece_alloc_unit) ;

  /* NOTE: that at this point dNumAllocUnits *is* size_in_KB and needs to be
     converted */
  units_to_create = 0;
  enhanced1_units = enhanced2_units = 0;

  for(i = 0;
      i < sizeof(ufs_config.unit) / sizeof(ufs_config.unit[0])
      && units_to_create <= total_alloc_units;
      i++)
  {
    uint32 alloc_units;
    uint8 mem_type;
    uint32 base_units;
    base_units = ufs_config.unit[i].dNumAllocUnits / (block_size / 1024);
    alloc_units = (base_units / blocks_per_alloc_unit);
    /* If the blocks per allocation unit is not a multiple of 'base_units' then
     * we need to round up. */
    if ((base_units % blocks_per_alloc_unit) != 0)
      alloc_units++;

    mem_type = ufs_config.unit[i].bMemoryType;

    if(mem_type == 0)
    {
      // Do nothing. This is just to ensure an error is not thrown
      // for this memory type
    }
    else if(mem_type == 3)
    {
      alloc_units = alloc_units * (info.wEnhanced1CapAdjFac / 0x100);
      enhanced1_units += alloc_units;
    }
    else if(mem_type == 4)
    {
      alloc_units = alloc_units * (info.wEnhanced2CapAdjFac / 0x100);
      enhanced2_units += alloc_units;
    }
    else
    {
      error = DEVPRG_ERROR_STORAGE;
      DP_LOGE("Unsupported UFS memory type %d", mem_type);
      goto cleanup;
    }

    ufs_config.unit[i].dNumAllocUnits = alloc_units;
    units_to_create += alloc_units;
  }

  /* Check if we are over allocating for the enhanced regions. */
  if(enhanced1_units > info.dEnhanced1MaxNAllocU)
  {
    error = DEVPRG_ERROR_STORAGE;
    DP_LOGE("Size %d exceeds max enhanced1 area size %d",
            enhanced1_units, info.dEnhanced1MaxNAllocU);
    goto cleanup;
  }

  if(enhanced2_units > info.dEnhanced2MaxNAllocU)
  {
    error = DEVPRG_ERROR_STORAGE;
    logMessage("Size %d exceeds max enhanced2 area size %d",
               enhanced2_units, info.dEnhanced2MaxNAllocU);
    goto cleanup;
  }

  if(units_to_create > total_alloc_units)
  {
    error = DEVPRG_ERROR_STORAGE;
    DP_LOGE("Specified size %d exceeds device size %d",
            units_to_create, total_alloc_units);
    goto cleanup;
  }

  if(configure->ufs_config.lun_to_grow != -1)
  {
    uint8 mem_type;
    uint32 conversion_ratio;
    uint32 lun_to_grow = configure->ufs_config.lun_to_grow;
    mem_type = ufs_config.unit[lun_to_grow].bMemoryType;

    /* Default there is no Enhanced area, ratio is 1. */
    conversion_ratio = 1;

    if(mem_type == 3)
      conversion_ratio = (info.wEnhanced1CapAdjFac / 0x100);
    else if(mem_type == 4)
      conversion_ratio = (info.wEnhanced2CapAdjFac / 0x100);
    else if(mem_type == 5)
      conversion_ratio = (info.wEnhanced3CapAdjFac / 0x100);
    else if(mem_type == 6)
      conversion_ratio = (info.wEnhanced4CapAdjFac / 0x100);

    ufs_config.unit[lun_to_grow].dNumAllocUnits +=
      ((total_alloc_units - units_to_create) / conversion_ratio);
  }

  result = ufs_configure_device(dev, &ufs_config);

  if(result != 0)
  {
    error = translate_ufs_error(result);
  }

cleanup:
  ufs_close(dev);

  return error;
}

int devprg_storage_ufs_fw_update(uint32 slot, void *buffer,
                                 uint32 size_in_bytes)
{
  int result = UFS_ENOENT;
  struct ufs_handle *hsdev_handle = NULL;
  struct ufs_handle *hswdev_handle = NULL;
  enum devprg_error error = DEVPRG_SUCCESS;

  hswdev_handle = ufs_open(slot, UFS_WLUN_DEVICE);
  hsdev_handle = ufs_open(slot, 0);

  if(hsdev_handle == NULL)
  {
    logMessage("Open Failed LUN 0 for slot %d. Check card.", slot);
    return DEVPRG_ERROR_STORAGE;
  }

//  result = ufs_fw_update_write (hsdev_handle, size_in_bytes, 0, buffer);
  if(result != 0)
    error = translate_ufs_error(result);
  else
    DP_LOGI("FW Update Successful. %s", " ");

  ufs_close(hswdev_handle);
  ufs_close(hsdev_handle);

  return error;
}

int devprg_storage_ufs_info_raw_size(void *device, uint32 *size)
{
  (void) device;
  *size = sizeof(struct ufs_info_type);
  return DEVPRG_SUCCESS;
}

int devprg_storage_ufs_info_raw(void *device, void *buffer,
                                uint32 *size)
{
  struct dp_storage_ufs *dev = (struct dp_storage_ufs *)device;
  int32 result;
  enum devprg_error error;
  struct ufs_info_type *info;
  uint32 max_size;

  devprg_storage_ufs_info_raw_size(device, &max_size);

  if(*size < max_size)
  {
    DP_LOGE("UFS Get info raw size too small %d < %d", *size, max_size);
    return DEVPRG_ERROR_NOMEM;
  }

  info = (struct ufs_info_type *)buffer;
  result = ufs_get_device_info(dev->handle, info);

  if(result != UFS_EOK)
  {
    error = translate_ufs_error(result);
    return error;
  }

  *size = max_size;

  return DEVPRG_SUCCESS;
}


#else /* If UFS Support is disabled (FEATURE_DEVPRG_UFS not defined)*/

#include "devprg_storage_stubs.h"
void devprg_storage_ufs_init(void)
{
  devprg_storage_stub_init();
}

int devprg_storage_ufs_deinit(void)
{
  return devprg_storage_stub_deinit();
}

void *devprg_storage_ufs_open(uint32 slot, uint32 partition,
                              enum devprg_error *error)
{
  return devprg_storage_stub_open(slot, partition, error);
}

int devprg_storage_ufs_close(void *device)
{
  return devprg_storage_stub_close(device);
}

int devprg_storage_ufs_read(void *device, void *buffer,
                            uint64 start_sector, uint64 num_sectors)
{
  return devprg_storage_stub_read(device, buffer, start_sector, num_sectors);
}

int devprg_storage_ufs_write(void *device, void *buffer,
                             uint64 start_sector, uint64 num_sectors)
{
  return devprg_storage_stub_write(device, buffer, start_sector, num_sectors);
}

int devprg_storage_ufs_erase(void *device,
                             uint64 start_sector, uint64 num_sectors)
{
  return devprg_storage_stub_erase(device, start_sector, num_sectors);
}

int devprg_storage_ufs_format(void *device)
{
  return devprg_storage_stub_format(device);
}

int devprg_storage_ufs_set_bootable(void *device, int enable)
{
  return devprg_storage_stub_set_bootable(device, enable);
}

int devprg_storage_ufs_get_info(void *device,
                                struct devprg_storage_info *dev_info)
{
  return devprg_storage_stub_get_info(device, dev_info);
}

int devprg_storage_ufs_configure(uint32 slot,
                                 struct devprg_storage_cfg_data *config)
{
  return devprg_storage_stub_configure(slot, config);
}

int devprg_storage_ufs_fw_update(uint32 slot, void *buffer,
                                 uint32 size_in_bytes)
{
  return devprg_storage_stub_fw_update(slot, buffer, size_in_bytes);
}

int devprg_storage_ufs_info_raw_size(void *device, uint32 *size)
{
  return devprg_storage_stub_info_raw_size(device, size);
}

int devprg_storage_ufs_info_raw(void *device, void *buffer,
                                uint32 *size)
{
  return devprg_storage_stub_info_raw(device, buffer, size);
}

#endif /*  FEATURE_DEVPRG_UFS */
