/**************************************************************************
 * FILE: deviceprogrammer_storage_store.c
 *
 * Common APIs for accessing any storage device through store block dev.
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

  $Header: //components/rel/boot.xf/1.4/QcomPkg/Library/DeviceProgrammerCommonLib/firehose/deviceprogrammer_storage_store.c#2 $
  $DateTime: 2016/08/19 05:58:45 $
  $Author: c_mvanim $

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2016-02-10   wek   Add the option to format whole dev or erase a portion.
2015-11-12   wek   Create.

===========================================================================*/

#include "deviceprogrammer_storage_store.h"
#include "devprg_storage.h"
#include "devprg_log.h"

struct storage_device_store
{
  enum storage_device_type type;
  void *handle;
};

static struct storage_device_store device_store_data;

void storage_device_store_init_hotplug(void)
{
  return;
}

void *storage_device_store_init_struct(void)
{
  struct storage_device_store *dev = &device_store_data;
  dev->type = STORAGE_DEVICE_TYPE_INVALID;
  dev->handle = NULL;
  devprg_storage_init();
  return dev;
}

boolean storage_device_store_open(void *device, enum storage_device_type type)
{
  struct storage_device_store *dev = (struct storage_device_store *) device;
  dev->type = type;
  dev->handle = NULL;
  return TRUE;
}
boolean storage_device_store_close(void *device)
{
  (void) device;
  return TRUE;
}

static enum devprg_storage_type map_devprg_types[STORAGE_DEVICE_TYPE_MAX] =
{
  DEVPRG_STORAGE_NULL, /* -> STORAGE_DEVICE_TYPE_INVALID */
  DEVPRG_STORAGE_SDCC, /* -> STORAGE_DEVICE_TYPE_MMC */
  DEVPRG_STORAGE_UFS, /* -> STORAGE_DEVICE_TYPE_UFS */
  DEVPRG_STORAGE_SPINOR, /* -> STORAGE_DEVICE_TYPE_SPI_NOR */
};

/* Converts a Storage Device Type (v1 of storage layer) to a devprg storage
type (v2 of storage layer) */
static enum devprg_storage_type
get_devprg_storage_type (enum storage_device_type type)
{
  if (type >= STORAGE_DEVICE_TYPE_MAX ||
      type <= STORAGE_DEVICE_TYPE_INVALID)
    return DEVPRG_STORAGE_NULL;

  return map_devprg_types[type];
}

boolean storage_device_store_read(void *device, uint32 slot,
     uint32 partition, byte *buffer, uint64 start_sector, uint64 num_sectors)
{
  struct storage_device_store *dev = (struct storage_device_store *) device;
  int result;
  enum devprg_error error;
  struct devprg_storage *handle;
  enum devprg_storage_type type = get_devprg_storage_type(dev->type);
  boolean status = TRUE;

  handle = devprg_storage_open(type, slot, partition, &error);
  if (handle == NULL)
  {
    DP_LOGW("Read failed to open %d slot %d, partition %d, error %d",
            type, slot,partition, error);
    return FALSE;
  }

  result = devprg_storage_read(handle, buffer, start_sector, num_sectors);
  if (result != DEVPRG_SUCCESS)
  {
    DP_LOGE("Read Failed to read %d slot %d, partition %d, start_sector %d num_sectors %d, error %d",
            type, slot, start_sector, num_sectors, partition, result);
    status = FALSE;
  }

  result = devprg_storage_close(handle);
  if (result != DEVPRG_SUCCESS)
    status = FALSE;

  return status;
}

boolean storage_device_store_write(void *device, uint32 slot, uint32 partition, byte *buffer, uint64 start_sector, uint64 num_sectors)
{
  struct storage_device_store *dev = (struct storage_device_store *) device;
  int result;
  enum devprg_error error;
  struct devprg_storage *handle;
  enum devprg_storage_type type = get_devprg_storage_type(dev->type);
  boolean status = TRUE;

  handle = devprg_storage_open(type, slot, partition, &error);
  if (handle == NULL)
  {
    DP_LOGW("Write Failed to open %d slot %d, partition %d, error %d",
            type, slot, partition, error);
    return FALSE;
  }

  result = devprg_storage_write(handle, buffer, start_sector, num_sectors);
  if (result != DEVPRG_SUCCESS)
  {
    DP_LOGE("Failed to write %d slot %d, partition %d, start_sector %d num_sectors %d, error %d",
            type, slot, start_sector, num_sectors, partition, result);
    status = FALSE;
  }

  result = devprg_storage_close(handle);
  if (result != DEVPRG_SUCCESS)
    status = FALSE;

  return status;
}


boolean storage_device_store_erase(void *device, uint32 slot, uint32 partition, uint64 start_sector, uint64 num_sectors)
{
  struct storage_device_store *dev = (struct storage_device_store *) device;
  int result;
  enum devprg_error error;
  struct devprg_storage *handle;
  enum devprg_storage_type type = get_devprg_storage_type(dev->type);
  boolean status = TRUE;

  handle = devprg_storage_open(type, slot, partition, &error);
  if (handle == NULL)
  {
    DP_LOGW("Write Failed to open %d slot %d, partition %d, error %d",
            type, slot, partition, error);
    return FALSE;
  }

  result = devprg_storage_erase(handle, start_sector, num_sectors);
  if (result != DEVPRG_SUCCESS)
  {
    DP_LOGE("Failed to erase %d slot %d, partition %d, start_sector %d num_sectors %d, error %d",
            type, slot, start_sector, num_sectors, partition, result);
    status = FALSE;
  }

  result = devprg_storage_close(handle);
  if (result != DEVPRG_SUCCESS)
    status = FALSE;

  return status;
}

boolean storage_device_store_format(void *device, uint32 slot, uint32 partition)
{
  struct storage_device_store *dev = (struct storage_device_store *) device;
  int result;
  enum devprg_error error;
  struct devprg_storage *handle;
  enum devprg_storage_type type = get_devprg_storage_type(dev->type);
  boolean status = TRUE;

  handle = devprg_storage_open(type, slot, partition, &error);
  if (handle == NULL)
  {
    DP_LOGW("Format failed to open %d slot %d, partition %d, error %d",
            type, slot, partition, error);
    return FALSE;
  }

  result = devprg_storage_format(handle);
  if (result != DEVPRG_SUCCESS)
  {
    DP_LOGE("Failed to erase/format %d slot %d, partition %d, error %d",
            type, slot, partition, result);
    status = FALSE;
  }

  result = devprg_storage_close(handle);
  if (result != DEVPRG_SUCCESS)
    status = FALSE;

  return status;
}

static boolean storage_get_info (void *device, uint32 slot, uint32 partition,
                                 struct devprg_storage_info *dev_info)
{
  struct storage_device_store *dev = (struct storage_device_store *) device;
  int result;
  enum devprg_error error;
  struct devprg_storage *handle;
  enum devprg_storage_type type = get_devprg_storage_type(dev->type);
  boolean status = TRUE;

  handle = devprg_storage_open(type, slot, partition, &error);
  if (handle == NULL)
  {
    DP_LOGW("Get Info failed to open %d slot %d, partition %d, error %d",
            type, slot, partition, error);
    return FALSE;
  }

  result = devprg_storage_get_info(handle, dev_info);
  if (result != DEVPRG_SUCCESS)
  {
    DP_LOGE("Failed to get info %d slot %d, partition %d, error %d",
            type, slot, partition, result);
    status = FALSE;
  }

  result = devprg_storage_close(handle);
  if (result != DEVPRG_SUCCESS)
    status = FALSE;

  return status;
}

boolean storage_device_store_get_num_partition_sectors(void *device, uint32 slot, uint32 partition, uint64 *num_partition_sectors)
{
  boolean status;
  struct devprg_storage_info dev_info;

  status = storage_get_info (device, slot, partition, &dev_info);
  if (status == TRUE)
    *num_partition_sectors = dev_info.total_blocks;

  return status;
}

boolean storage_device_store_set_bootable_partition(void *device, uint32 slot, uint32 partition)
{
  struct storage_device_store *dev = (struct storage_device_store *) device;
  int result;
  enum devprg_error error;
  struct devprg_storage *handle;
  enum devprg_storage_type type = get_devprg_storage_type(dev->type);
  boolean status = TRUE;

  handle = devprg_storage_open(type, slot, partition, &error);
  if (handle == NULL)
  {
    DP_LOGW("Set bootable failed to open %d slot %d, partition %d, error %d",
            type, slot, partition, error);
    return FALSE;
  }

  result = devprg_storage_set_bootable(handle, 1);
  if (result != DEVPRG_SUCCESS)
  {
    DP_LOGE("Failed to set bootable %d slot %d, partition %d, error %d",
            type, slot, partition, result);
    status = FALSE;
  }

  result = devprg_storage_close(handle);
  if (result != DEVPRG_SUCCESS)
    status = FALSE;

  return status;
}

boolean storage_device_store_get_info(void *device, uint32 slot, uint32 partition)
{
  boolean status;
  struct devprg_storage_info dev_info;

  status = storage_get_info (device, slot, partition, &dev_info);
  if (status == TRUE)
  {
    DP_LOGI("Device Total Logical Blocks: 0x%llx", dev_info.total_blocks);
    DP_LOGI("Device Block Size in Bytes: 0x%x", dev_info.block_size);
    DP_LOGI("Device Total Physical Partitions: 0x%x", 0);
    DP_LOGI("Device Manufacturer ID: 0x%llx", dev_info.manufacturer_id);
    DP_LOGI("Device Serial Number: 0x%llx", dev_info.serial_num);

    DP_LOGI("{&quot;storage_info&quot;: {&quot;total_blocks&quot;:%lld, "
           "&quot;block_size&quot;:%d, &quot;page_size&quot;:%d, "
           "&quot;num_physical&quot;:%d, &quot;manufacturer_id&quot;:%d, "
           "&quot;serial_num&quot;:%u, &quot;fw_version&quot;:&quot;%s&quot;,"
           "&quot;mem_type&quot;:&quot;%s&quot;,&quot;prod_name&quot;:&quot;%s&quot;}}",
            dev_info.total_blocks, dev_info.block_size, dev_info.page_size,
            dev_info.num_physical, dev_info.manufacturer_id,
            dev_info.serial_num,   dev_info.fw_version, dev_info.memory_type,
            dev_info.product_name);

  }
  else
  {
    DP_LOGE("Failed to get device info slot:% partition:%d", slot, partition);
  }

  return status;
}

static void
devprg_copy_emmc_config (struct devprg_sdcc_emmc_gpp_enh_desc *emmc_config,
                         struct sdcc_emmc_gpp_enh_desc *configure)
{
  emmc_config->GPP_size[0] = configure->GPP_size[0];
  emmc_config->GPP_size[1] = configure->GPP_size[1];
  emmc_config->GPP_size[2] = configure->GPP_size[2];
  emmc_config->GPP_size[3] = configure->GPP_size[3];
  emmc_config->ENH_size = configure->ENH_size;
  emmc_config->ENH_start_addr = configure->ENH_start_addr;
  emmc_config->GPP_enh_flag = configure->GPP_enh_flag;
}

static void devprg_copy_ufs_cfg_data(struct devprg_ufs_config_descr *config,
                                     struct ufs_config_descr *configure)

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

  number_of_luns = sizeof(config->unit) / sizeof(struct devprg_ufs_unit_descr);

  for(i = 0; i < number_of_luns; i++)
  {
    struct ufs_unit_descr *src = &configure->unit[i];
    struct devprg_ufs_unit_descr *dest = &config->unit[i];
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

boolean storage_device_store_commit_extras(void *device, storage_device_extras_t *extras)
{
  struct storage_device_store *dev = (struct storage_device_store *) device;
  int result;
  enum devprg_storage_type type = get_devprg_storage_type(dev->type);
  boolean status = TRUE;
  struct devprg_storage_cfg_data config;

  if (dev->type == STORAGE_DEVICE_TYPE_UFS)
  {
    devprg_copy_ufs_cfg_data(&config.ufs_config, &extras->ufs_extras);
    config.ufs_config.lun_to_grow = extras->lun_to_grow;
  }
  else if(dev->type == STORAGE_DEVICE_TYPE_MMC)
  {
    devprg_copy_emmc_config(&config.emmc_config, &extras->emmc_extras);
  }

  /* The original code for hotplug always used slot 0, so do the same here. */
  result = devprg_storage_configure (type, 0 /* Slot=0*/, &config);
  if (result != DEVPRG_SUCCESS)
  {
    DP_LOGE("Failed to store extras %d slot %d, partition %d, error %d",
            type, 0, result);
    status = FALSE;
  }

  return status;
}


boolean storage_device_store_fw_update(void *device, byte *fw_bin, uint32 num_sectors)
{
  struct storage_device_store *dev = (struct storage_device_store *) device;
  int result;
  enum devprg_storage_type type = get_devprg_storage_type(dev->type);
  boolean status = TRUE;

  result = devprg_storage_fw_update (type, 0 /* Slot=0*/, fw_bin, num_sectors);
  if (result != DEVPRG_SUCCESS)
  {
    DP_LOGE("Failed to store extras %d slot %d, partition %d, error %d",
            type, 0, result);
    status = FALSE;
  }

  return status;
}

boolean storage_device_store_get_info_raw(void *device, void *storage_info_raw, uint32 *buff_len)
{
  struct storage_device_store *dev = (struct storage_device_store *) device;
  int result;
  enum devprg_error error;
  struct devprg_storage *handle;
  enum devprg_storage_type type = get_devprg_storage_type(dev->type);
  boolean status = TRUE;
  uint32 size;

  handle = devprg_storage_open(type, 0, DEVPRG_WHOLE_DEVICE_PARTITION, &error);
  if (handle == NULL)
  {
    DP_LOGW("Get info raw failed to open %d slot %d, partition %d, error %d",
            type, 0, 0, error);
    return FALSE;
  }

  result = devprg_storage_info_raw_size(handle, &size);
  if (result != DEVPRG_SUCCESS)
  {
    DP_LOGE("Failed to get info raw size %d slot %d, partition %d, error %d",
            type, 0, 0, result);
    status = FALSE;
  }
  else if(size > *buff_len) /* Check the input buffer is large enough */
  {
    DP_LOGE("Input buffer size for get info raw size is too small %d > %d, %d slot %d, partition %d, error %d",
            size, *buff_len, type, 0, 0, result);
    status = FALSE;
  }
  else if (size != 0)/* input buffer size is large enough, get the data. */
  {
    result = devprg_storage_info_raw(handle, storage_info_raw, buff_len);
    if (result != DEVPRG_SUCCESS)
    {
      DP_LOGE("Failed to get info raw %d slot %d, partition %d, error %d",
              type, 0, 0, result);
      status = FALSE;
    }
  }

  result = devprg_storage_close(handle);
  if (result != DEVPRG_SUCCESS)
    status = FALSE;

  return status;
}


boolean storage_device_store_set_type(void *device, enum storage_device_type type)
{
  struct storage_device_store *dev = (struct storage_device_store *) device;
  dev->type = type;
  return TRUE;
}


