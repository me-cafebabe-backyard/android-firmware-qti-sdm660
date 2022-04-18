/*==================================================================
 *
 * FILE:        deviceprogrammer_storage.h
 *
 * DESCRIPTION:
 *
 *
 *        Copyright (c) 2014-2016 Qualcomm Technologies Incorporated.
 *               All Rights Reserved.
 *               QUALCOMM Proprietary
 *==================================================================*/

/*===================================================================
 *
 *                       EDIT HISTORY FOR FILE
 *
 *   This section contains comments describing changes made to the
 *   module. Notice that changes are listed in reverse chronological
 *   order.
 *
 *
 * YYYY-MM-DD   who     what, where, why
 * ----------   ---     ----------------------------------------------
 * 2016-02-10   wek     Add option to format whole dev or erase portion.
 * 2015-11-10   wek     Add slot argument to storage APIs, but no effect.
 * 2015-11-09   wek     Remove structure coupling between fh and storage.
 * 2015-04-15   bn      Added GetStorageInfo support
 * 2014-10-02   ah      Major code clean up
 * 2014-07-23   kh      Initial checkin
 */
#ifndef __DEVICEPROGRAMMER_STORAGE_H__
#define __DEVICEPROGRAMMER_STORAGE_H__

#include "deviceprogrammer_utils.h"

#include "sdcc_api.h"
#include "ufs_api.h"

struct storage_device;
typedef struct storage_device storage_device_t;

enum storage_device_type
{
  STORAGE_DEVICE_TYPE_INVALID = 0, /**< Invalid device */
  STORAGE_DEVICE_TYPE_MMC     = 1, /**< SD or MMC */
  STORAGE_DEVICE_TYPE_UFS     = 2, /**< UFS */
  STORAGE_DEVICE_TYPE_SPI_NOR = 3, /**< SPI_NOR */
  STORAGE_DEVICE_TYPE_MAX     = 4, /**< All the above devices */
};

void storage_device_init_hotplug(void);  // init hotplug without polling
storage_device_t *storage_device_init_struct(void);

// poll for specified type, and open first device and all its hard partitions
boolean storage_device_open(storage_device_t *dev, enum storage_device_type type);
boolean storage_device_close(storage_device_t *dev);

/* Storage device access functions.
 * Common arguments are:
 * slot        When multiple devices are connected, which device to address.
 * partition     The physical partition or LUN of the device.
 * start_sector  Sector where to write the data.
 * num_sectors   Number of sectors to read/write.
 */
boolean storage_device_read(storage_device_t *dev, uint32 slot, uint32 partition, byte *buffer, uint64 start_sector, uint64 num_sectors);
boolean storage_device_write(storage_device_t *dev, uint32 slot, uint32 partition, byte *buffer, uint64 start_sector, uint64 num_sectors);
boolean storage_device_erase(storage_device_t *dev, uint32 slot, uint32 partition, uint64 start_sector, uint64 num_sectors);
boolean storage_device_format(storage_device_t *dev, uint32 slot, uint32 partition);

boolean storage_device_get_num_partition_sectors(storage_device_t *dev, uint32 slot, uint32 partition, uint64 *num_partition_sectors);
boolean storage_device_set_bootable_partition(storage_device_t *dev, uint32 slot, uint32 partition);
boolean storage_device_get_info(storage_device_t *dev, uint32 slot, uint32 partition);

// FW update and device configure not supported for VS testing
typedef struct {
    //union {
        sdcc_emmc_gpp_enh_desc_type emmc_extras;
        struct ufs_config_descr 	ufs_extras;
    //};

  SIZE_T lun_to_grow;	// Extra UFS parameters
} storage_device_extras_t;

boolean storage_device_commit_extras(storage_device_t *dev, storage_device_extras_t *extras);

boolean storage_device_fw_update(storage_device_t *dev, byte *fw_bin, uint32 num_sectors);
boolean storage_device_get_info_raw (storage_device_t *dev, void *storage_info_raw, uint32 *buff_len);

boolean storage_device_set_type (storage_device_t *dev, enum storage_device_type type);

#endif
