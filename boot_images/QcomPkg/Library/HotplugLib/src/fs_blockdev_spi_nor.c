/***********************************************************************
 * fs_blockdev_spi_nor.c
 *
 * Short description.
 * Copyright (C) 2015-2016 QUALCOMM Technologies, Inc.
 *
 * Verbose Description
 *
 ***********************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when         who   what, where, why
----------   ---   ---------------------------------------------------------
2016-04-29   rp    Support UFS well known boot lun
2015-04-14   mj    Create

===========================================================================*/
#include "fs_hotplug_config_i.h"

#ifdef FEATURE_FS_HOTPLUG_SPI_NOR

#include "fs_blockdev_i.h"
#include "fs_blockdev_spi_nor_driver.h"
#include "fs_err.h"
#include "assert.h"
#include "flash.h"
#include "DALDeviceId.h"
#include <string.h>

#define SPI_NOR_ENTIRE_DEVICE_ID    0

#define FLASH_COMPLETE_DEVICE "0:ALL"
#define FS_DEVICE_FLASH_MAX_DEVICES        (1)


/* Storage for SPI_NOR specific data */
static struct spi_nor_device_data spi_nor_dev_data[] =
{
  {0,0,0,0},  /* slot_no */
};

/* SPI NOR device structure */
static flash_handle_t handle_flash;
static struct flash_info dev_info;


/*-----------------------------------------------------------------------------
  SPI_NOR Debug fields to log the last so many API failure return values.
-----------------------------------------------------------------------------*/

#define FS_BLOCKDEV_SPI_NOR_ENABLE_DEBUG

#ifndef SPI_NOR_DEBUG_MAX_API_COUNT
  #define SPI_NOR_DEBUG_MAX_API_COUNT   (50)
#endif

enum spi_nor_debug_api_id
{
  SPI_NOR_DEBUG_API_ID_OPEN,
  SPI_NOR_DEBUG_API_ID_READ,
  SPI_NOR_DEBUG_API_ID_WRITE,
  SPI_NOR_DEBUG_API_ID_ERASE,
  SPI_NOR_DEBUG_API_ID_CLOSE,
  SPI_NOR_DEBUG_API_ID_GET_DEVICE_INFO,
  SPI_NOR_DEBUG_API_ID_SET_PON_WRITE_PROTECT,
  SPI_NOR_DEBUG_API_ID_MAX
};

#ifdef FS_BLOCKDEV_SPI_NOR_ENABLE_DEBUG

PACKED struct spi_nor_debug_info
{
  enum spi_nor_debug_api_id api_id;
  int  result;
} PACKED_POST ;

static struct spi_nor_debug_info fs_spi_nor_debug_info[SPI_NOR_DEBUG_MAX_API_COUNT];

static uint32 fs_spi_nor_debug_info_idx;

static void
blockdev_spi_nor_debug_init (void)
{
  memset (fs_spi_nor_debug_info, 0, sizeof (fs_spi_nor_debug_info));
  fs_spi_nor_debug_info_idx = 0;
}

static void
blockdev_spi_nor_add_debug_info (enum spi_nor_debug_api_id api_id, int result)
{
  if (fs_spi_nor_debug_info_idx >= SPI_NOR_DEBUG_MAX_API_COUNT)
  {
    fs_spi_nor_debug_info_idx = 0;
  }
  fs_spi_nor_debug_info[fs_spi_nor_debug_info_idx].api_id = api_id;
  fs_spi_nor_debug_info[fs_spi_nor_debug_info_idx].result = result;
  ++fs_spi_nor_debug_info_idx;
}

#else /* FS_BLOCKDEV_SPI_NOR_ENABLE_DEBUG */

static inline void
blockdev_spi_nor_debug_init (void)
{
}

static inline void
blockdev_spi_nor_add_debug_info (enum spi_nor_debug_api_id api_id, int result)
{
  (void) api_id; (void) result;
}

#endif /* FS_BLOCKDEV_SPI_NOR_ENABLE_DEBUG */


/*---------------------------------------------------------------------------*/
static int
blockdev_spi_nor_open (struct block_device *bdev, void **handle, uint32 data)
{
  struct spi_nor_device_data *spi_nor_data;
  uint32 which_spi_nor;
  int result = -1;

  ASSERT (bdev != NULL);
  ASSERT (handle != NULL);

  if (*handle != NULL)
    return -1;

  if (data > 0)
    return -1;

  which_spi_nor = data;

  if (which_spi_nor >= FS_DEVICE_FLASH_MAX_DEVICES)
    goto End;

  spi_nor_data = bdev->device_data;
  ASSERT (spi_nor_data != NULL);

  memset(spi_nor_data, 0, sizeof (struct spi_nor_device_data));
  *handle = NULL;

  if (FLASH_DEVICE_DONE != flash_device_attach(DALDEVICEID_FLASH_DEVICE_1,
                              &handle_flash))
  {
    blockdev_spi_nor_add_debug_info (SPI_NOR_DEBUG_API_ID_OPEN, 0);
    goto End;
  }

  if (FLASH_DEVICE_DONE != flash_device_open(handle_flash))
  {
    blockdev_spi_nor_add_debug_info (SPI_NOR_DEBUG_API_ID_OPEN, 0);
    goto End;
  }

  if (FLASH_DEVICE_DONE != flash_get_info(handle_flash, FLASH_DEVICE_INFO, &dev_info))
  {
    blockdev_spi_nor_add_debug_info (SPI_NOR_DEBUG_API_ID_OPEN, 0);
    goto End;
  }

  spi_nor_data->page_size = dev_info.page_size_bytes;
  spi_nor_data->block_size = dev_info.pages_per_block;
  spi_nor_data->total_blocks = dev_info.block_count;

  *handle = (void *) handle_flash;
  result = 0;
End:
  return result;
}

static int
blockdev_spi_nor_close (struct block_device *bdev, void *handle)
{
  struct spi_nor_device_data *spi_nor_data;
  int result,spi_res;

  ASSERT (bdev != NULL);
  ASSERT (handle != NULL);

  spi_nor_data = bdev->device_data;
  ASSERT (spi_nor_data != NULL);
  result = 0;

  spi_res = flash_device_close(handle);

  if (FLASH_DEVICE_DONE != spi_res)
  {
    blockdev_spi_nor_add_debug_info(SPI_NOR_DEBUG_API_ID_CLOSE, spi_res);
    result = -1;
  }

  spi_res = flash_device_detach(handle);

  if (FLASH_DEVICE_DONE != spi_res)
  {
    blockdev_spi_nor_add_debug_info(SPI_NOR_DEBUG_API_ID_CLOSE, spi_res);
    result = -1;
  }
  return result;
}

static int
blockdev_spi_nor_read (struct block_device *bdev, void *handle, uint32 lba,
                       unsigned char *buf, uint16 n_to_read)
{
  struct spi_nor_device_data *spi_nor_data;
  int result, spi_res ;
  uint8 *cur_buf;
  uint32 curr_page_no, total_pages;

  ASSERT (bdev != NULL);
  ASSERT (handle != NULL);
  ASSERT (buf != NULL);

  spi_nor_data = bdev->device_data;
  ASSERT (spi_nor_data != NULL);

  result = -1;

  cur_buf = buf;

  curr_page_no = lba * spi_nor_data->block_size;
  total_pages = (uint32)n_to_read * spi_nor_data->block_size;

  spi_res = flash_read_pages(handle, cur_buf, curr_page_no, total_pages);

  if (FLASH_DEVICE_DONE != spi_res)
  {
    blockdev_spi_nor_add_debug_info (SPI_NOR_DEBUG_API_ID_READ, spi_res);
    result = -1;
    goto End;
  }

  result = 0;
End:
  return result;
}

static int
blockdev_spi_nor_write (struct block_device *bdev, void *handle, uint32 lba,
             unsigned char *buf, uint16 n_to_write)
{
  struct spi_nor_device_data *spi_nor_data;
  int result, spi_res;
  uint8 *cur_buf;
  uint32 cur_block, total_blocks, curr_page_no, total_pages;

  ASSERT (bdev != NULL);
  ASSERT (handle != NULL);
  ASSERT (buf != NULL);

  spi_nor_data = bdev->device_data;
  ASSERT (spi_nor_data != NULL);

  result = -1;
  cur_block = lba;
  total_blocks = (uint32)n_to_write;

  cur_buf = buf;

  spi_res = flash_erase_blocks(handle, cur_block, total_blocks);

  if (FLASH_DEVICE_DONE != spi_res)
  {
    blockdev_spi_nor_add_debug_info (SPI_NOR_DEBUG_API_ID_ERASE, spi_res);
    result = -1;
    goto End;
  }

  curr_page_no = cur_block * spi_nor_data->block_size;
  total_pages = total_blocks * spi_nor_data->block_size;

  spi_res = flash_write_pages(handle, cur_buf, curr_page_no, total_pages);

  if (FLASH_DEVICE_DONE != spi_res)
  {
    blockdev_spi_nor_add_debug_info (SPI_NOR_DEBUG_API_ID_WRITE, spi_res);
    result = -1;
    goto End;
  }

  result = 0;

End:
  return result;
}

static int
blockdev_spi_nor_reliable_write (struct block_device *bdev, void *handle,
                            uint32 lba, uint32 *buf, uint32 num_sectors)
{
  struct spi_nor_device_data *spi_nor_data;
  (void) handle;
  (void) lba;
  (void) buf;
  (void) num_sectors;

  ASSERT (bdev != NULL);
  spi_nor_data = bdev->device_data;
  ASSERT (spi_nor_data != NULL);

  return -1;  /*Unsupported*/
}

static int
blockdev_spi_nor_erase (struct block_device *bdev, void *handle, uint32 lba,
                        uint32 erase_len)
{
  struct spi_nor_device_data *spi_nor_data;
  int result, spi_res;

  ASSERT (bdev != NULL);
  ASSERT (handle != NULL);

  spi_nor_data = bdev->device_data;
  ASSERT (spi_nor_data != NULL);

  result = -1;

  spi_res = flash_erase_blocks(handle, lba, erase_len);

  if (FLASH_DEVICE_DONE != spi_res)
  {
    blockdev_spi_nor_add_debug_info (SPI_NOR_DEBUG_API_ID_ERASE, spi_res);
    result = -1;
    goto End;
  }

  result = 0;
End:
  return result;
}

static int
blockdev_spi_nor_reset (struct block_device *bdev, void *handle)
{
  struct spi_nor_device_data *spi_nor_data;
  (void) handle;

  ASSERT (bdev != NULL);
  spi_nor_data = bdev->device_data;
  ASSERT (spi_nor_data != NULL);

  return 0;
}

static int
blockdev_spi_nor_device_format (struct block_device *bdev, void *handle)
{
  struct spi_nor_device_data *spi_nor_data;
  (void) handle;

  ASSERT (bdev != NULL);
  spi_nor_data = bdev->device_data;
  ASSERT (spi_nor_data != NULL);

  return -1;   /*Unsupported*/
}

static int
blockdev_spi_nor_is_present (struct block_device *bdev, void *handle)
{
  struct spi_nor_device_data *spi_nor_data;
  (void) handle;

  ASSERT (bdev != NULL);
  spi_nor_data = bdev->device_data;
  ASSERT (spi_nor_data != NULL);

  return 1; /* SPI-NOR is embedded, so always present. */
}

static int
blockdev_spi_nor_get_device_size (struct block_device *bdev, void *handle,
                             uint32 *blocks, uint16 *bytes_per_block)
{
  struct spi_nor_device_data *spi_nor_data;
  (void) handle;

  ASSERT (bdev != NULL);
  spi_nor_data = bdev->device_data;
  ASSERT (spi_nor_data != NULL);

  ASSERT (blocks != NULL);
  ASSERT (bytes_per_block != NULL);

  *blocks = spi_nor_data->total_blocks;
  *bytes_per_block = (uint16)(spi_nor_data->page_size * spi_nor_data->block_size);

  return 0;
}

static int
blockdev_spi_nor_get_device_info (struct block_device *bdev, void *handle,
                                  struct block_device_info *dev_info)
{
  struct spi_nor_device_data *spi_nor_data;
  (void) dev_info;
  (void) handle;

  ASSERT (bdev != NULL);
  spi_nor_data = bdev->device_data;
  ASSERT (spi_nor_data != NULL);

  memset (dev_info, 0, sizeof (*dev_info));
  dev_info->card_size_in_sectors = spi_nor_data->total_blocks;
  dev_info->bytes_per_sector = (uint32)(spi_nor_data->page_size * spi_nor_data->block_size);

  return 0;
}

uint32
blockdev_spi_nor_get_entire_device_id (struct block_device *bdev, void *handle)
{
  (void) bdev; (void) handle;

  ASSERT (bdev != NULL);
  return SPI_NOR_ENTIRE_DEVICE_ID;
}

static int
blockdev_spi_nor_set_device_idle (struct block_device *bdev, void *handle)
{
  struct spi_nor_device_data *spi_nor_data;
  (void) handle;

  ASSERT (bdev != NULL);
  spi_nor_data = bdev->device_data;
  ASSERT (spi_nor_data != NULL);

  return -1;  /*Unsupported*/
}

static int
blockdev_spi_nor_is_embedded_device (struct block_device *bdev, void *handle)
{
  (void) handle;
  ASSERT (bdev != NULL);

  return 1; /* SPI-NOR is always embedded. */
}

static int
blockdev_spi_nor_set_sps_end_point (struct block_device *bdev, void *handle,
                               void *param)
{
  struct spi_nor_device_data *spi_nor_data;
  (void) handle;
  (void) param;

  ASSERT (bdev != NULL);
  spi_nor_data = bdev->device_data;
  ASSERT (spi_nor_data != NULL);

  return -1;  /*Unsupported*/
}

static int
blockdev_spi_nor_get_sps_end_point (struct block_device *bdev, void *handle,
                               void *param)
{
  struct spi_nor_device_data *spi_nor_data;
  (void) handle;
  (void) param;

  ASSERT (bdev != NULL);
  spi_nor_data = bdev->device_data;
  ASSERT (spi_nor_data != NULL);

  return -1;  /*Unsupported*/
}

static int
blockdev_spi_nor_set_power_on_write_protection (struct block_device *bdev,
                      void *handle, uint32 start_block, uint32 num_blocks)
{
  struct spi_nor_device_data *spi_nor_data;
  (void) handle;
  (void) start_block;
  (void) num_blocks;

  ASSERT (bdev != NULL);
  spi_nor_data = bdev->device_data;
  ASSERT (spi_nor_data != NULL);

  return -1;  /*Unsupported*/
}

static int
blockdev_spi_nor_set_bootable_partition (struct block_device *bdev,
                           void *handle, void *whole_device_handle)
{
  struct spi_nor_device_data *spi_nor_data;
  (void) handle;
  (void) whole_device_handle;

  ASSERT (bdev != NULL);
  spi_nor_data = bdev->device_data;
  ASSERT (spi_nor_data != NULL);

  return -1;  /*Unsupported*/
}

static int
blockdev_spi_nor_configure_device (struct block_device *bdev, void *handle,
                              void *whole_device_handle, void *config_data)
{
  struct spi_nor_device_data *spi_nor_data;
  (void) handle;
  (void) whole_device_handle, (void) config_data;

  ASSERT (bdev != NULL);
  spi_nor_data = bdev->device_data;
  ASSERT (spi_nor_data != NULL);

  return -1;  /*Unsupported*/
}

static int
blockdev_spi_nor_get_lun_numbers (struct block_device *bdev, void *handle,
                     uint32 count, uint32 *lun_numbers, uint32 *actual_count)
{
  uint32 i;

  (void) bdev; (void) handle;
  ASSERT (bdev != NULL);
  ASSERT (lun_numbers != NULL);
  ASSERT (actual_count != NULL);

  for (i = 0; i < count; ++i)
    lun_numbers[i] = i;
  *actual_count = count;

  return 0;
}


/* List of all device operations */
static blockdev_ops spi_nor_ops =
{
  blockdev_spi_nor_open,
  blockdev_spi_nor_close,
  blockdev_spi_nor_read,
  blockdev_spi_nor_write,
  blockdev_spi_nor_write,
  blockdev_spi_nor_reliable_write,
  blockdev_spi_nor_erase,
  blockdev_spi_nor_reset,
  blockdev_spi_nor_device_format,
  blockdev_spi_nor_is_present,
  blockdev_spi_nor_get_device_size,
  blockdev_spi_nor_get_device_info,
  blockdev_spi_nor_get_entire_device_id,
  blockdev_spi_nor_set_device_idle,
  blockdev_spi_nor_is_embedded_device,
  blockdev_spi_nor_set_sps_end_point,
  blockdev_spi_nor_get_sps_end_point,
  blockdev_spi_nor_set_power_on_write_protection,
  blockdev_spi_nor_set_bootable_partition,
  blockdev_spi_nor_configure_device,
  blockdev_spi_nor_get_lun_numbers
};

void
blockdev_spi_nor_device_data_init (void)
{
  blockdev_spi_nor_debug_init ();
}

blockdev_ops*
blockdev_spi_nor_get_ops (void)
{
  return &spi_nor_ops;
}

void*
blockdev_spi_nor_get_device_data (uint32 idx)
{
  uint32 total_devices;
  total_devices = sizeof (spi_nor_dev_data) / sizeof (spi_nor_dev_data[0]);
  if (idx >= total_devices)
  {
    FS_ERR_FATAL ("index value %d exceeds total number of devices %d",idx,total_devices,0);
  }
  return &spi_nor_dev_data[idx];
}

#endif /* FEATURE_FS_HOTPLUG_SPI_NOR */
