/***********************************************************************
 * fs_blockdev_ufs.c
 *
 * Blockdev UFS device.
 * Copyright (C) 2013-2016 QUALCOMM Technologies, Inc.
 *
 * Implementation for the blockdev_ops functions specific to
 * the UFS driver.
 *
 ***********************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when         who   what, where, why
----------   ---   ---------------------------------------------------------
2016-06-25   rp    Fix return value when there is no UFS well known boot lun.
2016-04-29   rp    Support UFS well known boot lun
2015-06-22   rp    Add UFS serial number reading support.
2015-02-05   wek   Make it clear that open failed.
2014-21-15   kpa   Fix compilation warnings.
2014-10-14   wek   Change the argument type/size of erase.
2014-08-06   kh    Add format, set_bootable_partition, configure_device
2014-01-29   vm    Changes for 64-bit compilation in boot.
2013-11-20   rp    Detect embedded MMC-devices without opening them.
2013-09-09   wek   Update the entire device ID macro.
2013-06-21   rp    Adapt to the new UFS write-protection API.
2013-05-24   rp    Create

===========================================================================*/

#include "fs_hotplug_config_i.h"

#ifdef FEATURE_FS_HOTPLUG_UFS

#include "fs_blockdev_i.h"
#include "fs_blockdev_ufs_driver.h"
#include "fs_err.h"
#include "assert.h"
#include "ufs_api.h"

#include <string.h>

/* UFS has no concept of entire-disk. Each LUN is considered different
 * hardware-partition and LUN-0 is the default LUN (User-Partition).
 * Since hotplug will open entire device, we will use the default-LUN (0)
 * as the entire device.*/
#define UFS_ENTIRE_DEVICE_ID    UFS_WLUN_DEVICE

/* Storage for UFS specific data */
static struct ufs_device_data ufs_dev_data[] =
{
  {0},  /* slot_no */
#ifdef FS_UNIT_TEST
  {1}   /* slot_no */
#endif
};

/*-----------------------------------------------------------------------------
  UFS Debug fields to log the last so many UFS API failure return values.
-----------------------------------------------------------------------------*/
#define FS_BLOCKDEV_UFS_ENABLE_DEBUG

#ifndef UFS_DEBUG_MAX_API_COUNT
  #define UFS_DEBUG_MAX_API_COUNT   (50)
#endif

enum ufs_debug_api_id
{
  UFS_DEBUG_API_ID_SLOT_EMPTY = 0,
  UFS_DEBUG_API_ID_OPEN,
  UFS_DEBUG_API_ID_READ,
  UFS_DEBUG_API_ID_WRITE,
  UFS_DEBUG_API_ID_CLOSE,
  UFS_DEBUG_API_ID_GET_DEVICE_INFO,
  UFS_DEBUG_API_ID_SET_PON_WRITE_PROTECT,
  UFS_DEBUG_API_ID_MAX
};

#ifdef FS_BLOCKDEV_UFS_ENABLE_DEBUG

PACKED struct ufs_debug_info
{
  enum ufs_debug_api_id api_id;
  int  result;
} PACKED_POST ;

struct ufs_debug_info fs_ufs_debug_info[UFS_DEBUG_MAX_API_COUNT];
uint32 fs_ufs_debug_info_idx;

static void
blockdev_ufs_debug_init (void)
{
  memset (fs_ufs_debug_info, 0, sizeof (fs_ufs_debug_info));
  fs_ufs_debug_info_idx = 0;
}

static void
blockdev_ufs_add_debug_info (enum ufs_debug_api_id api_id, int result)
{
  if (fs_ufs_debug_info_idx >= UFS_DEBUG_MAX_API_COUNT)
  {
    fs_ufs_debug_info_idx = 0;
  }

  fs_ufs_debug_info[fs_ufs_debug_info_idx].api_id = api_id;
  fs_ufs_debug_info[fs_ufs_debug_info_idx].result = result;
  ++fs_ufs_debug_info_idx;
}

#else /* FS_BLOCKDEV_UFS_ENABLE_DEBUG */

static inline void
blockdev_ufs_debug_init (void)
{
}

static inline void
blockdev_ufs_add_debug_info (enum ufs_debug_api_id api_id, int result)
{
  (void) api_id; (void) result;
}

#endif /* FS_BLOCKDEV_UFS_ENABLE_DEBUG */
/*---------------------------------------------------------------------------*/

static int
blockdev_ufs_open (struct block_device *bdev, void **handle, uint32 data)
{
  struct ufs_handle *ufs_hdl;
  struct ufs_device_data *ufs_data;
  uint32 lun_no;
  int result;

  ASSERT (bdev != NULL);
  ASSERT (handle != NULL);

  if (*handle != NULL)
    return -1;

  ufs_data = bdev->device_data;
  ASSERT (ufs_data != NULL);

  lun_no = data;

  *handle = NULL;
  result = -1;

  ufs_hdl = ufs_open (ufs_data->slot_no, lun_no);
  if (ufs_hdl != NULL)
  {
    *handle = (void *)ufs_hdl;
    result = 0;
  }
  else
  {
    blockdev_ufs_add_debug_info (UFS_DEBUG_API_ID_OPEN, -1);
  }

  return result;
}

static int
blockdev_ufs_close (struct block_device *bdev, void *handle)
{
  struct ufs_handle *ufs_hdl = (struct ufs_handle *)handle;
  struct ufs_device_data *ufs_data;
  int32_t ufs_result;
  int result;

  ASSERT (bdev != NULL);
  ASSERT (handle != NULL);

  ufs_data = bdev->device_data;
  ASSERT (ufs_data != NULL);

  result = 0;
  ufs_result = ufs_close (ufs_hdl);
  if (ufs_result != UFS_EOK)
  {
    blockdev_ufs_add_debug_info (UFS_DEBUG_API_ID_CLOSE, ufs_result);
    result = -1;
  }

  return result;
}

static int
blockdev_ufs_read (struct block_device *bdev, void *handle, uint32 lba,
            unsigned char *buf, uint16 n_to_read)
{
  struct ufs_handle *ufs_hdl = (struct ufs_handle *)handle;
  int result;
  int32_t ufs_result;
  uint8_t *temp_buf;
  uint64_t temp_lba;
  uint32_t temp_num_blocks;

  ASSERT (bdev != NULL);
  ASSERT (ufs_hdl != NULL);

  temp_buf = (uint8_t*)buf;
  temp_lba = (uint64_t)lba;
  temp_num_blocks = (uint32_t)n_to_read;

  result = 0;
  ufs_result = ufs_read (ufs_hdl, temp_buf, temp_lba, temp_num_blocks);
  if (ufs_result != UFS_EOK)
  {
    blockdev_ufs_add_debug_info (UFS_DEBUG_API_ID_READ, ufs_result);
    result = -1;
  }

  return result;
}

static int
blockdev_ufs_write (struct block_device *bdev, void *handle, uint32 lba,
             unsigned char *buf, uint16 n_to_write)
{
  struct ufs_handle *ufs_hdl = (struct ufs_handle *)handle;
  int result;
  int32_t ufs_result;
  uint8_t *temp_buf;
  uint64_t temp_lba;
  uint32_t temp_num_blocks;

  ASSERT (bdev != NULL);
  ASSERT (ufs_hdl != NULL);

  temp_buf = (uint8_t*)buf;
  temp_lba = (uint64_t)lba;
  temp_num_blocks = (uint32_t)n_to_write;

  result = 0;
  ufs_result = ufs_write (ufs_hdl, temp_buf, temp_lba, temp_num_blocks);
  if (ufs_result != UFS_EOK)
  {
    blockdev_ufs_add_debug_info (UFS_DEBUG_API_ID_WRITE, ufs_result);
    result = -1;
  }

  return result;
}

static int
blockdev_ufs_reliable_write (struct block_device *bdev, void *handle,
                            uint32 lba, uint32 *buf, uint32 num_sectors)
{
  (void) bdev; (void) handle; (void) lba; (void) buf; (void) num_sectors;
  return -1;                    /* Unsupported */
}

static int
blockdev_ufs_erase (struct block_device *bdev, void *handle, uint32 lba,
                        uint32 erase_len)
{
  struct ufs_handle *ufs_hdl = (struct ufs_handle *)handle;
  int32_t ufs_result;

  ASSERT (bdev != NULL);
  ASSERT (ufs_hdl != NULL);

  if (ufs_hdl == NULL)
  {
    return -1;
  }

  ufs_result = ufs_unmap (ufs_hdl, (uint64_t)lba, (uint32_t)erase_len);
  return (ufs_result == UFS_EOK) ? 0 : -1;
}

static int
blockdev_ufs_reset (struct block_device *bdev, void *handle)
{
  struct ufs_device_data *ufs_data;

  (void) handle;

  ASSERT (bdev != NULL);
  ufs_data = bdev->device_data;
  ASSERT (ufs_data != NULL);

  return 0;
}

static int
blockdev_ufs_device_format (struct block_device *bdev, void *handle)
{
  struct ufs_handle *ufs_hdl = handle;
  ASSERT (bdev != NULL);
  ASSERT (ufs_hdl != NULL);
  if (bdev == NULL || ufs_hdl == NULL)
  {
    return -1;
  }

  return ufs_format(ufs_hdl);
}

static int
blockdev_ufs_is_present (struct block_device *bdev, void *handle)
{
  struct ufs_handle *ufs_hdl = (struct ufs_handle *)handle;
  (void) ufs_hdl;
  ASSERT (bdev != NULL);
  ASSERT (ufs_hdl != NULL);
  return 1; /* UFS is embedded, so always present. */
}

static int
blockdev_ufs_get_device_size (struct block_device *bdev, void *handle,
                             uint32 *blocks, uint16 *bytes_per_block)
{
  struct ufs_handle *ufs_hdl = (struct ufs_handle *)handle;
  struct ufs_info_type ufs_info;
  int32_t ufs_result;
  int result;

  ASSERT (bdev != NULL);
  ASSERT (blocks != NULL);
  ASSERT (bytes_per_block != NULL);

  ufs_result = ufs_get_device_info (ufs_hdl, &ufs_info);
  if (ufs_result == UFS_EOK)
  {
    *blocks = ufs_info.dLuTotalBlocks;
    *bytes_per_block = ufs_info.bMinAddrBlockSize * 512;
    result = 0;
  }
  else
  {
    blockdev_ufs_add_debug_info (UFS_DEBUG_API_ID_GET_DEVICE_INFO, ufs_result);
    result = -1;
  }

  return result;
}

static int
blockdev_ufs_get_device_info (struct block_device *bdev, void *handle,
                             struct block_device_info *dev_info)
{
  struct ufs_handle *ufs_hdl = (struct ufs_handle *)handle;
  int result = -1;
  struct ufs_info_type ufs_info;
  int32_t ufs_result;

  ASSERT (bdev != NULL);
  ASSERT (ufs_hdl != NULL);

  ufs_result = ufs_get_device_info (ufs_hdl, &ufs_info);
  if (ufs_result == UFS_EOK)
  {
    memset (dev_info, 0, sizeof (*dev_info));
    dev_info->manufacturer_id = (uint32)ufs_info.wManufacturerID;
    dev_info->card_size_in_sectors = ufs_info.dLuTotalBlocks;
    dev_info->bytes_per_sector = ufs_info.bMinAddrBlockSize * 512;

    ufs_result = ufs_get_device_info_str (ufs_hdl, ufs_info.iSerialNumber,
                                          dev_info->product_name,
                                          sizeof (dev_info->product_name));
    if (ufs_result == UFS_EOK)
    {
      result = 0;
    }
  }

  if (result != 0)
  {
    blockdev_ufs_add_debug_info (UFS_DEBUG_API_ID_GET_DEVICE_INFO, ufs_result);
    result = -1;
  }

  return result;
}


uint32
blockdev_ufs_get_entire_device_id (struct block_device *bdev, void *handle)
{
  (void) bdev; (void) handle;
  return UFS_ENTIRE_DEVICE_ID;
}

static int
blockdev_ufs_set_device_idle (struct block_device *bdev, void *handle)
{
  (void) handle; (void) bdev;
  return -1;
}

static int
blockdev_ufs_is_embedded_device (struct block_device *bdev, void *handle)
{
  (void) handle;
  ASSERT (bdev != NULL);

  return 1; /* UFS is always embedded. */
}


static int
blockdev_ufs_set_sps_end_point (struct block_device *bdev, void *handle,
                               void *param)
{
  (void) bdev; (void) handle; (void) param;
  return -1;
}

static int
blockdev_ufs_get_sps_end_point (struct block_device *bdev, void *handle,
                               void *param)
{
  (void) bdev; (void) handle; (void) param;
  return -1;
}

static int
blockdev_ufs_set_power_on_write_protection (struct block_device *bdev,
                 void *handle, uint32 start_block, uint32 num_blocks)
{
  struct ufs_handle *ufs_hdl = (struct ufs_handle *)handle;
  int32_t ufs_result;
  int result;

  (void) start_block;
  (void) num_blocks;

  ASSERT (bdev != NULL);
  if (ufs_hdl == NULL)
    return -1;

  result = 0;
  ufs_result = ufs_set_pon_write_protect (ufs_hdl);
  if (ufs_result != UFS_EOK)
  {
    blockdev_ufs_add_debug_info (UFS_DEBUG_API_ID_SET_PON_WRITE_PROTECT,
                                 ufs_result);
    result = -1;
  }
  return result;
}

static int
blockdev_ufs_set_bootable_partition (struct block_device *bdev, void *handle,
                                        void *whole_device_handle)
{
  struct ufs_handle *ufs_hdl = (struct ufs_handle *)handle;
  struct ufs_handle *ufs_device_hdl = (struct ufs_handle *)whole_device_handle;
  struct ufs_info_type ufs_info;

  if (ufs_device_hdl == NULL || ufs_hdl == NULL || bdev == NULL)
    return -1;

  /* Get LUN of this handle */
  if (ufs_get_device_info (ufs_hdl, &ufs_info) != UFS_EOK)
  {
    return -1;
  }

  if (ufs_info.bLUN == 0)
  {
    /* 0 means disable */
    return -1;
  }

  if (ufs_set_bootable (ufs_device_hdl, ufs_info.bLUN) != UFS_EOK)
  {
    return -1;
  }

  return 0;
}

static int
blockdev_ufs_configure_device (struct block_device *bdev, void *handle,
                        void *whole_device_handle, void *config_data)
{
  (void)handle;
  struct ufs_handle *ufs_device_hdl = (struct ufs_handle *)whole_device_handle;
  struct ufs_config_descr *ufs_cfg = (struct ufs_config_descr *)config_data;

  if (ufs_device_hdl == NULL || bdev == NULL || ufs_cfg == NULL)
    return -1;

  if (ufs_configure_device (ufs_device_hdl, ufs_cfg) != UFS_EOK)
  {
      return -1;
  }
  return 0;
}

static int
blockdev_ufs_get_lun_numbers (struct block_device *bdev, void *handle,
                              uint32 count, uint32 *lun_numbers,
                              uint32 *actual_count)
{
  struct ufs_handle *ufs_hdl = (struct ufs_handle *)handle;
  struct ufs_handle *ufs_boot_lun_hdl = NULL;
  struct ufs_device_data *ufs_data;
  struct ufs_info_type ufs_info;
  uint32 i, j, boot_lun_no;
  int32_t ufs_result;

  (void) bdev; (void) handle; (void) ufs_hdl;
  ASSERT (bdev != NULL);
  ASSERT (ufs_hdl != NULL);
  ASSERT (count >= 2);
  ASSERT (lun_numbers != NULL);
  ASSERT (actual_count != NULL);

  *actual_count = 0;

  ufs_data = bdev->device_data;
  ASSERT (ufs_data != NULL);

  ufs_boot_lun_hdl = ufs_open (ufs_data->slot_no, UFS_WLUN_BOOT);
  if (ufs_boot_lun_hdl == NULL)
  {
    blockdev_ufs_add_debug_info (UFS_DEBUG_API_ID_OPEN, -1);
    goto Error;
  }

  memset (&ufs_info, 0, sizeof (ufs_info));
  ufs_result = ufs_get_device_info (ufs_boot_lun_hdl, &ufs_info);
  if (ufs_result != UFS_EOK)
  {
    blockdev_ufs_add_debug_info (UFS_DEBUG_API_ID_GET_DEVICE_INFO, ufs_result);
    goto Error;
  }

  if ((ufs_info.bLUN == UFS_WLUN_BOOT) ||
      (ufs_info.bLUN >= count))
  {
    /* fallback to old LUN number behaviour */
    blockdev_ufs_add_debug_info (UFS_DEBUG_API_ID_GET_DEVICE_INFO, ufs_result);
    goto Error;
  }

  boot_lun_no = (uint32)ufs_info.bLUN;
  ASSERT (boot_lun_no <= count);

  lun_numbers[0] = boot_lun_no;
  for (i = 0, j = 1; i < count; ++i)
  {
    if (i == boot_lun_no)
      continue;
    lun_numbers[j++] = i;
    ASSERT (j <= count);
  }
  ASSERT (j == count);
  *actual_count = count;
  goto End;

Error:
  for (i = 0; i < count; ++i)
    lun_numbers[i] = i;
  *actual_count = count;

End:
  if (ufs_boot_lun_hdl != NULL)
    (void) ufs_close (ufs_boot_lun_hdl);
  return 0;

}

/* List of all device operations */
static blockdev_ops ufs_ops =
{
  blockdev_ufs_open,
  blockdev_ufs_close,
  blockdev_ufs_read,
  blockdev_ufs_write,
  blockdev_ufs_write,
  blockdev_ufs_reliable_write,
  blockdev_ufs_erase,
  blockdev_ufs_reset,
  blockdev_ufs_device_format,
  blockdev_ufs_is_present,
  blockdev_ufs_get_device_size,
  blockdev_ufs_get_device_info,
  blockdev_ufs_get_entire_device_id,
  blockdev_ufs_set_device_idle,
  blockdev_ufs_is_embedded_device,
  blockdev_ufs_set_sps_end_point,
  blockdev_ufs_get_sps_end_point,
  blockdev_ufs_set_power_on_write_protection,
  blockdev_ufs_set_bootable_partition,
  blockdev_ufs_configure_device,
  blockdev_ufs_get_lun_numbers
};

void
blockdev_ufs_device_data_init (void)
{
  blockdev_ufs_debug_init ();
}

blockdev_ops*
blockdev_ufs_get_ops (void)
{
  return &ufs_ops;
}

void*
blockdev_ufs_get_device_data (uint32 idx)
{
  uint32 total_devices;

  total_devices = sizeof (ufs_dev_data) / sizeof (ufs_dev_data[0]);
  if (idx >= total_devices)
  {
    FS_ERR_FATAL ("mismatch in device data...",0,0,0);
  }

  return &ufs_dev_data[idx];
}

#endif /* FEATURE_FS_HOTPLUG_UFS */

