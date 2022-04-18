/***********************************************************************
 * fs_blockdev_spi_nor_driver.h
 *
 * Short description
 * Copyright (C) 2015 QUALCOMM Technologies, Inc.
 *
 * Verbose description.
 *
 ***********************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when         who   what, where, why
----------   ---   ---------------------------------------------------------
2015-04-14   mj    Create

===========================================================================*/

#ifndef __FS_BLOCKDEV_SPI_NOR_DRIVER_H__
#define __FS_BLOCKDEV_SPI_NOR_DRIVER_H__

#include "fs_hotplug_config_i.h"

#ifdef FEATURE_FS_HOTPLUG_SPI_NOR

#include "fs_blockdev_i.h"
#include "fs_blockdev_driver.h"

/* SPI-NOR device specific data */
struct spi_nor_device_data
{
  uint32  slot_no;
  uint32  page_size;
  uint32  block_size;
  uint32  total_blocks;
};

extern void blockdev_spi_nor_device_data_init (void);
extern blockdev_ops* blockdev_spi_nor_get_ops (void);
extern void* blockdev_spi_nor_get_device_data (uint32 idx);

/* Handle to SPI-NOR device driver */
extern blockdev_driver blockdev_spi_nor_driver;

#endif /* FEATURE_FS_HOTPLUG_SPI_NOR */


#endif /* not __FS_BLOCKDEV_SPI_NOR_DRIVER_H__ */
