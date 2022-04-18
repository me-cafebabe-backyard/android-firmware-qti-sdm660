/**************************************************************************
 * FILE: deviceprogrammer_storage_hp.h
 *
 * Common APIs for accessing any storage device through Hotplug
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

  $Header: //components/rel/boot.xf/1.4/QcomPkg/Library/DeviceProgrammerCommonLib/firehose/deviceprogrammer_storage_hp.h#2 $
  $DateTime: 2016/08/19 05:58:45 $
  $Author: c_mvanim $

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2016-02-10   wek   Add the option to format whole dev or erase a portion.
2015-11-10   wek   Create.

===========================================================================*/

#ifndef __DEVICEPROGRAMMER_STORAGE_HP_H__
#define __DEVICEPROGRAMMER_STORAGE_HP_H__

#include "deviceprogrammer_utils.h"
#include "deviceprogrammer_storage.h"

void storage_device_hp_init_hotplug(void);  // init hotplug without polling
void *storage_device_hp_init_struct(void);

// poll for specified type, and open first device and all its hard partitions
boolean storage_device_hp_open(void *dev, enum storage_device_type type);
boolean storage_device_hp_close(void *dev);

/* Storage device access functions.
 * Common arguments are:
 * slot        When multiple devices are connected, which device to address.
 * partition     The physical partition or LUN of the device.
 * start_sector  Sector where to write the data.
 * num_sectors   Number of sectors to read/write.
 */
boolean storage_device_hp_read(void *dev, uint32 slot, uint32 partition, byte *buffer, uint64 start_sector, uint64 num_sectors);
boolean storage_device_hp_write(void *dev, uint32 slot, uint32 partition, byte *buffer, uint64 start_sector, uint64 num_sectors);
boolean storage_device_hp_erase(void *dev, uint32 slot, uint32 partition, uint64 start_sector, uint64 num_sectors);
boolean storage_device_hp_format(void *dev, uint32 slot, uint32 partition);

boolean storage_device_hp_get_num_partition_sectors(void *dev, uint32 slot, uint32 partition, uint64 *num_partition_sectors);
boolean storage_device_hp_set_bootable_partition(void *dev, uint32 slot, uint32 partition);
boolean storage_device_hp_get_info(void *dev, uint32 slot, uint32 partition);

boolean storage_device_hp_commit_extras(void *dev, storage_device_extras_t *extras);

boolean storage_device_hp_fw_update(void *dev, byte *fw_bin, uint32 num_sectors);
boolean storage_device_hp_get_info_raw(void *dev, void *storage_info_raw, uint32 *buff_len);

boolean storage_device_hp_set_type(void *dev, enum storage_device_type type);


#endif
