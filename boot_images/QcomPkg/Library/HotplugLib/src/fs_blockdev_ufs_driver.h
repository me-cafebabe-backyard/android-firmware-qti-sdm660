/***********************************************************************
 * fs_blockdev_ufs_driver.h
 *
 * Blockdev driver for the UFS device.
 * Copyright (C) 2013 QUALCOMM Technologies, Inc.
 *
 * Blockdev driver for the UFS device.
 *
 ***********************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when         who   what, where, why
----------   ---   ---------------------------------------------------------
2013-05-24   rp    Create

===========================================================================*/

#ifndef __FS_BLOCKDEV_UFS_DRIVER_H__
#define __FS_BLOCKDEV_UFS_DRIVER_H__

#include "fs_hotplug_config_i.h"

#ifdef FEATURE_FS_HOTPLUG_UFS

#include "fs_blockdev_i.h"
#include "fs_blockdev_driver.h"
#include "ufs_api.h"

/* UFS device specific data */
struct ufs_device_data
{
  uint32  slot_no;
};

extern void blockdev_ufs_device_data_init (void);
extern blockdev_ops* blockdev_ufs_get_ops (void);
extern void* blockdev_ufs_get_device_data (uint32 idx);

/* Handle to SD device driver */
extern blockdev_driver blockdev_ufs_driver;

#endif /* FEATURE_FS_HOTPLUG_UFS */


#endif /* not __FS_BLOCKDEV_UFS_DRIVER_H__ */
