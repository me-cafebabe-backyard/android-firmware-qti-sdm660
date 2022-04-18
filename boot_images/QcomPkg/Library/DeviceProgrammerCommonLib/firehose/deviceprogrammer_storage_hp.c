/*==================================================================
 *
 * FILE:        deviceprogrammer_storage.c
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
 * 2016-01-19   wek     Fix the allocation unit size if segment is not 4MB.
 * 2015-11-10   wek     Add slot argument to storage APIs, but no effect.
 * 2015-11-09   wek     Remove structure coupling between fh and storage.
 * 2015-06-03   wek     Change the size given to SDCC FW update API.
 * 2015-04-15   bn      Added GetStorageInfo support.
 * 2014-12-02   wek     8996/XBL Compilation.
 * 2014-10-02   ah      Major code clean up
 * 2014-07-23   kh      Initial checkin
 */

#include "deviceprogrammer_storage_hp.h"
#include "deviceprogrammer_firehose.h"
#include <stddef.h>
#ifdef FEATURE_DEVICEPROG_HOTPLUG
#include "fs_hotplug.h"
#include "fs_hotplug_config.h"
#include "sdcc_api.h"
#include "ufs_api.h"

#ifdef DEVICEPROG_UFS_MISSING
struct ufs_handle *ufs_open( uint32 core_id, uint32 lun )
{
  return NULL;
}
int32 ufs_get_device_info( struct ufs_handle *handle, 
                             struct ufs_info_type *info )
{
  return UFS_ENODEV;
}
int32 ufs_close( struct ufs_handle *handle )
{
  return UFS_ENODEV;
}
int32 ufs_set_refclk_freq( struct ufs_handle *handle, 
                             uint32           freq)
{
  return UFS_ENODEV;
}
#endif /* DEVICEPROG_UFS_MISSING */


#define BYTES_PER_KB 1024

#define PARTITION_EMMC_USER 0

extern firehose_protocol_t fh;

static char *type_names[HOTPLUG_TYPE_ALL + 1] = {
    "INVALID",          //< Invalid device 
    "MMC",              //< SD or MMC 
    "REMOTE",           //< Device hosted on other processor 
    "USB_MS",           //< USB Host Mass Storage (thumdrive) 
    "DEVNULL",          //< NULL (nop) device 
    "FTL",              //< Flash Translation Layer (FAT-on-NAND) 
    "SD_CPRM",          //< Protected area of SD card (for CPRM) 
    "UFS",              //< UFS 
    "ALL"               //< All the above devices 
};

// convert dev type to string
static char *type_to_name(hotplug_dev_type type) {
    if (type > HOTPLUG_TYPE_ALL) {
        return "<invalid device type>";
    }
    return type_names[type];
}

// Storage device API

void storage_device_hp_init_hotplug() {
    hotplug_init_no_poll();
}

#define MAX_PARTITIONS_PER_DEVICE 8 // max number of partitions in a storage device

struct storage_device_hp {
  hotplug_dev_type current_storage_type;

  struct hotplug_device *hwhole_dev;  // whole device handle
  struct hotplug_device *hparts[MAX_PARTITIONS_PER_DEVICE];    // all available partitions

  SIZE_T num_partitions;
  SIZE_T sector_size;
  SIZE_T partition_sizes[MAX_PARTITIONS_PER_DEVICE];
  // Needed for UFS
  SIZE_T blocks_per_alloc_unit;
};
typedef struct storage_device_hp storage_device_hp_t;

static struct storage_device_hp storage_device_hp_static;

void *storage_device_hp_init_struct(void)
{
  storage_device_hp_t *dev = &storage_device_hp_static;
  dev->current_storage_type = HOTPLUG_TYPE_INVALID;

  dev->hwhole_dev = NULL;
  memset(dev->hparts, 0, sizeof(dev->hparts));

  dev->num_partitions = 0;
  dev->sector_size = 0;
  memset(dev->partition_sizes, 0, sizeof(dev->partition_sizes));
  dev->blocks_per_alloc_unit = 0;
  return dev;
}

// Get blocks_per_alloc_unit for UFS
static boolean init_ufs_params(storage_device_hp_t *dev)
{
    struct ufs_handle *ufs_hdl = NULL;
    struct ufs_info_type mem_info;
    int rc;

    ufs_hdl = ufs_open(0, UFS_WLUN_DEVICE);

    if (ufs_hdl == NULL)
    {
        logMessage("Call to ufs_open(0, UFS_WLUN_DEVICE) failed");

        //MyErrorMessage(STORAGE_OPEN_FAILURE);

        return FALSE;
    }

    rc = ufs_get_device_info(ufs_hdl, &mem_info);
    if (rc != 0)
    {
        ufs_close(ufs_hdl);

        logMessage("Could not get UFS partition info. Return code: %d", rc);
        //hotplug_release_internal_handle(dev->hwhole_dev, (void **)&ufs_hdl);
        return FALSE;
    }


    dev->sector_size = mem_info.bMinAddrBlockSize * 512;
    dev->blocks_per_alloc_unit = (mem_info.dSegmentSize * mem_info.bAllocationUnitSize * 512) / dev->sector_size;
    //hotplug_release_internal_handle(dev->hwhole_dev, (void **)&ufs_hdl);
    //return TRUE;

    ufs_close(ufs_hdl);
    return TRUE;

}

static unsigned int storage_type_to_hotplug_type [STORAGE_DEVICE_TYPE_MAX][2] =
{
  {STORAGE_DEVICE_TYPE_INVALID, HOTPLUG_TYPE_INVALID},
  {STORAGE_DEVICE_TYPE_MMC,     HOTPLUG_TYPE_MMC},
  {STORAGE_DEVICE_TYPE_UFS,     HOTPLUG_TYPE_UFS},
  {STORAGE_DEVICE_TYPE_SPI_NOR, HOTPLUG_TYPE_INVALID},
};
static hotplug_dev_type get_hotplug_type(enum storage_device_type type)
{
  if(type >= STORAGE_DEVICE_TYPE_MAX)
  {
    logMessage("INVALID device type %d, max %d", type, STORAGE_DEVICE_TYPE_MAX);
    return HOTPLUG_TYPE_INVALID;
  }

  return storage_type_to_hotplug_type[type][1];
}

boolean storage_device_hp_open(void *device, enum storage_device_type tp) {
  storage_device_hp_t *dev = (storage_device_hp_t *)device;
    struct hotplug_iter *hiter;
    struct hotplug_iter_record *hiter_rec;
    int partition;
    char whole_dev_name[FS_HOTPLUG_NAME_MAX];
    uint16 sector_size_in_bytes; // size in bytes of sector
    uint32 num_partition_sectors;
    int rc;
    hotplug_dev_type type = get_hotplug_type(tp);
    char *type_name = type_to_name(type);


    if (dev->current_storage_type == type || (dev->current_storage_type != HOTPLUG_TYPE_INVALID && type == HOTPLUG_TYPE_ALL))
    {
        // already opened this type; or opened something and user wants to open any time
        if(fh.attrs.Verbose == TRUE)
            logMessage("Returning TRUE since already opened this type; or opened something and user wants to open any time");


        // close existing one first
        if(fh.attrs.Verbose == TRUE)
            logMessage("Calling storage_device_hp_close(dev)");

        if (storage_device_hp_close(dev) == FALSE)
        {
            if(fh.attrs.Verbose == TRUE)
                logMessage("storage_device_hp_close(dev) returned FALSE");

            return FALSE;
        }

        //return TRUE;
    }
    else if (dev->current_storage_type != HOTPLUG_TYPE_INVALID)
    {
        // close existing one first
        if(fh.attrs.Verbose == TRUE)
            logMessage("Calling storage_device_hp_close(dev)");

        if (storage_device_hp_close(dev) == FALSE)
        {
            if(fh.attrs.Verbose == TRUE)
                logMessage("storage_device_hp_close(dev) returned FALSE");

            return FALSE;
        }
    }

    //if(fh.attrs.Verbose == TRUE)
    logMessage("Calling hotplug_poll_device('%s')",type_name);

    rc = hotplug_poll_device(type, HOTPLUG_ITER_ALL_DEVICES);
    if (rc != 0)
    {
        logMessage("Polling for devices of type '%s' failed - hotplug_poll_device returned %d (not 0)", type_name, rc);
        return FALSE;
    }

    if(fh.attrs.Verbose == TRUE)
        logMessage("Calling hotplug_iter_open(type, HOTPLUG_ITER_DEVICES, HOTPLUG_ITER_ALL_DEVICES)");

    // iter devices
    hiter = hotplug_iter_open(type, HOTPLUG_ITER_DEVICES, HOTPLUG_ITER_ALL_DEVICES);
    if (hiter == NULL)
    {
        logMessage("No devices of type '%s' found - hotplug_iter_open returned NULL", type_name);
        return FALSE;
    }

    if(fh.attrs.Verbose == TRUE)
        logMessage("Calling hotplug_iter_get_next(hiter)");

    hiter_rec = hotplug_iter_get_next(hiter);
    while (hiter_rec != NULL)
    {

        if(fh.attrs.Verbose == TRUE)
            logMessage("Calling hotplug_open_device('%s')",hiter_rec->hdev_name);

        dev->hwhole_dev = hotplug_open_device(hiter_rec->hdev_name);
        if (dev->hwhole_dev != NULL)
        {
            // just take first device we can open, for now
            strlcpy(whole_dev_name, hiter_rec->hdev_name, FS_HOTPLUG_NAME_MAX);
            break;
        }
        hiter_rec = hotplug_iter_get_next(hiter);
    }

    if(fh.attrs.Verbose == TRUE)
        logMessage("Calling hotplug_iter_close(hiter)");

    hotplug_iter_close(hiter);

    if (dev->hwhole_dev == NULL)
    {
        // no device can be opened
        logMessage("Storage device of type '%s' cannot be opened", type_name);
        return FALSE;
    }

    // iter hard partitions and open all
    if(fh.attrs.Verbose == TRUE)
        logMessage("Calling hotplug_iter_open(type, HOTPLUG_ITER_HARD_PARTITIONS, HOTPLUG_ITER_ALL_DEVICES)");

    hiter = hotplug_iter_open(type, HOTPLUG_ITER_HARD_PARTITIONS, HOTPLUG_ITER_ALL_DEVICES);
    if (hiter == NULL)
    {
        logMessage("Storage device of type '%s' found but no hard partitions found - hotplug_iter_open returned NULL", type_name);
        return FALSE;
    }
    dev->num_partitions = 0;

    // set current_storage_type
    dev->current_storage_type = type;

    while(1)
    {
        if(fh.attrs.Verbose == TRUE)
            logMessage("Calling hotplug_iter_get_next(hiter)");

        hiter_rec = hotplug_iter_get_next(hiter);   // check for null is in the while
        if(hiter_rec == NULL) { break;}

        if (strncmp(whole_dev_name, hiter_rec->hdev_name, strlen(whole_dev_name)) != 0) {
            // partition not in this device
            continue;
        }

        if(strlen(hiter_rec->hdev_name)<1)  // if this is 0, then below index is -1
            return FALSE;

        // parse name and get partition #
        partition = hiter_rec->hdev_name[strlen(hiter_rec->hdev_name) - 1] - '0';
        if (partition < 0 || partition >= MAX_PARTITIONS_PER_DEVICE)
        {
            logMessage("Partition number of %s device '%s' invalid", type_name, hiter_rec->hdev_name);
            hotplug_iter_close(hiter);
            return FALSE;
        }

        // open partition
        if(fh.attrs.Verbose == TRUE)
            logMessage("In storage_device_hp_open() Calling hotplug_open_device('%s')",hiter_rec->hdev_name);

        dev->hparts[partition] = hotplug_open_device(hiter_rec->hdev_name);
        if (dev->hparts[partition] == NULL)
        {
            continue;
        }

        if(fh.attrs.Verbose == TRUE)
            logMessage("In storage_device_hp_open() Calling hotplug_open_device('%s') was **SUCCESSFUL**",hiter_rec->hdev_name);

        // store size in sectors
        rc = hotplug_dev_get_size(dev->hparts[partition], &num_partition_sectors, &sector_size_in_bytes);
        if (rc != 0)
        {
            logMessage("Can't get size of partition '%s' - hotplug_dev_get_size returned %d (not 0)", hiter_rec->hdev_name, rc);
            hotplug_iter_close(hiter);
            return FALSE;
        }
        dev->partition_sizes[partition] = num_partition_sectors;

        // get sector size
        dev->sector_size = sector_size_in_bytes;

        //hiter_rec = hotplug_iter_get_next(hiter);
        dev->num_partitions++;
    }

    if(fh.attrs.Verbose == TRUE)
        logMessage("Calling hotplug_iter_close(hiter)");

    hotplug_iter_close(hiter);



    // Store UFS extra
    if (dev->current_storage_type == HOTPLUG_TYPE_UFS)
    {
        if(fh.attrs.Verbose == TRUE)
            logMessage("In storage_device_hp_open Calling init_ufs_params() since dev->current_storage_type=HOTPLUG_TYPE_UFS");

        if(init_ufs_params(dev) == FALSE)
        {
            if(fh.attrs.Verbose == TRUE)
                logMessage("In storage_device_hp_open init_ufs_params() returned FALSE");

            return FALSE;
        }
    }
    // If all is well, set current_storage_type
    //dev->current_storage_type = hotplug_get_device_type(dev->hwhole_dev);
    return TRUE;
}

boolean storage_device_hp_close(void *device) {
  storage_device_hp_t *dev = (storage_device_hp_t *)device;
    int i;
    int rc;

    if (dev->hwhole_dev) {
        rc = hotplug_close_device(dev->hwhole_dev);
        if (rc != 0) {
            logMessage("Failed to close %s device - hotplug_close_device returned %d (not 0)", type_to_name(dev->current_storage_type), rc);
            return FALSE;
        }
    }

    for (i = 0; i < MAX_PARTITIONS_PER_DEVICE; i++)
    {
        if (dev->hparts[i]) 
        {
            rc = hotplug_close_device(dev->hparts[i]);
            if (rc != 0) 
            {
                logMessage("Failed to close partition %d - hotplug_close_device returned %d (not 0)", i, rc);
                return FALSE;
            }
        }
    } // end for (i = 0; i < MAX_PARTITIONS_PER_DEVICE; i++) 

    storage_device_hp_init_struct(); // stores default values in struct
    return TRUE;
}

static boolean storage_device_hp_is_valid_partition(void *device, uint32 partition)
{
  storage_device_hp_t *dev = (storage_device_hp_t *) device;
    if(fh.attrs.Verbose == TRUE)
    {
        logMessage("In storage_device_hp_is_valid_partition(%llu) and MAX_PARTITIONS_PER_DEVICE=%d",partition,MAX_PARTITIONS_PER_DEVICE);
        logMessage("dev->current_storage_type=0x%X",dev->current_storage_type);
        logMessage("dev->hparts[partition]=0x%X",dev->hparts[partition]);
    }

    if (dev->current_storage_type != HOTPLUG_TYPE_INVALID && partition < MAX_PARTITIONS_PER_DEVICE && dev->hparts[partition] != NULL)
    {
        return TRUE;
    }
    else
    {
        if (fh.attrs.SkipStorageInit == FALSE)
            return FALSE;
        else
            return TRUE;
    }
}

boolean storage_device_hp_set_bootable_partition(void *device, uint32 slot, uint32 partition)
{
  storage_device_hp_t *dev = (storage_device_hp_t *) device;
    if (fh.attrs.SkipStorageInit == TRUE) 
    {
        logMessage("WARNING: NOT setting bootable partition to %llu since user specified skipStorageInit", partition);
        return TRUE;
    }

    if(dev->current_storage_type == HOTPLUG_TYPE_INVALID) 
    {
        if(fh.attrs.Verbose == TRUE) 
            logMessage("dev->current_storage_type == HOTPLUG_TYPE_INVALID");

        MyErrorMessage(SET_BOOTABLE_PARTITION_FAILURE);
        return FALSE;
    }
    if(storage_device_hp_is_valid_partition(dev, partition)==FALSE)
    {
        if(fh.attrs.Verbose == TRUE) 
            logMessage("storage_device_hp_is_valid_partition(dev, partition)==FALSE");
            
        MyErrorMessage(SET_BOOTABLE_PARTITION_FAILURE);
        return FALSE;
    }
    if (hotplug_set_bootable_partition(dev->hparts[partition]) != 0) 
    {
        if(fh.attrs.Verbose == TRUE) 
            logMessage("hotplug_set_bootable_partition(dev->hparts[partition]) != 0");
            
        MyErrorMessage(SET_BOOTABLE_PARTITION_FAILURE);
        return FALSE;
    }
    
    return TRUE;
}

boolean storage_device_hp_read(void *device, uint32 slot, uint32 partition, byte *buffer, uint64 start_sector, uint64 num_sectors) {
  storage_device_hp_t *dev = (storage_device_hp_t *) device;
	int err;
    //if (!storage_device_hp_is_valid_partition(dev, partition))
    //{
    //    return FALSE;
    //}
    err = hotplug_dev_read(dev->hparts[partition], start_sector, (unsigned char *)buffer, num_sectors);
    if (err != 0) 
    {
        logMessage("Storage read failed at sector %lld length %lld errno=%d", (SIZE_T)start_sector, (SIZE_T)num_sectors, err);
        MyErrorMessage(STORAGE_READ_FAILURE);
    }
    return (err == 0);
}

boolean storage_device_hp_write(void *device, uint32 slot, uint32 partition, byte *buffer, uint64 start_sector, uint64 num_sectors)
{
  storage_device_hp_t *dev = (storage_device_hp_t *) device;
	int err;
    //if (!storage_device_hp_is_valid_partition(dev, partition))
    //{
    //    return FALSE;
    //}
    
    err = hotplug_dev_write(dev->hparts[partition], start_sector, (unsigned char *)buffer, num_sectors);
    if (err != 0) 
    {
        logMessage("Storage write failed at sector %lld length %lld errno=%d (0x%X)", (SIZE_T)start_sector, (SIZE_T)num_sectors, err,err);
        MyErrorMessage(STORAGE_WRITE_FAILURE);
    }
    return (err == 0);
}

boolean storage_device_hp_erase(void *device, uint32 slot, uint32 partition,
                                uint64 start_sector, uint64 num_sectors)
{
  logMessage("Erasing Specific sectors not supported on top of Hotplug", 0);
  logMessage("Failed to erase Slot%d partition %d start %d num_sectors %d",
             slot, partition, start_sector, num_sectors);
  return FALSE;
}

boolean storage_device_hp_format(void *device, uint32 slot, uint32 partition) {
  storage_device_hp_t *dev = (storage_device_hp_t *) device;
    int rc;

    if (!storage_device_hp_is_valid_partition(dev, partition)) {
        return FALSE;
    }

    switch (dev->current_storage_type) 
    {
        case HOTPLUG_TYPE_MMC:
        
            if(fh.attrs.Verbose == TRUE)
                logMessage("Calling hotplug_dev_erase(%lld)",partition);

            rc = hotplug_dev_erase(dev->hparts[partition], 0, dev->partition_sizes[partition]);
            if (rc != 0)
            {
                logMessage("Storage erase failed - %s returned %d (not 0)", "hotplug_dev_erase", rc);
                MyErrorMessage(STORAGE_DEVICE_ERASE_FAILURE);
                return FALSE;
            }
            return TRUE;
        case HOTPLUG_TYPE_UFS:
        
            if(fh.attrs.Verbose == TRUE)
                logMessage("Calling hotplug_dev_format(%lld)",partition);
        
            rc = hotplug_dev_format(dev->hparts[partition]);
            if (rc != 0)
            {
                logMessage("Storage erase failed - %s returned %d (not 0)", "hotplug_dev_format", rc);
                MyErrorMessage(STORAGE_DEVICE_ERASE_FAILURE);
                return FALSE;
            }
            return TRUE;
        default:
        
            if(fh.attrs.Verbose == TRUE)
                logMessage("Unknown dev->current_storage_type 0x%X in storage_device_hp_erase()",dev->current_storage_type);
        
            return FALSE;
    }
}

boolean storage_device_hp_get_num_partition_sectors(void *device, uint32 slot, uint32 partition, uint64 *num_partition_sectors) {
  storage_device_hp_t *dev = (storage_device_hp_t *) device;
  if (!storage_device_hp_is_valid_partition(dev, partition) || num_partition_sectors == NULL) {
    return FALSE;
  }

  *num_partition_sectors = dev->partition_sizes[partition];
  return TRUE;
}

boolean storage_device_hp_get_info(void *device, uint32 slot, uint32 partition) {
  storage_device_hp_t *dev = (storage_device_hp_t *) device;
    struct hotplug_device_info hdev_info;

    if (fh.attrs.SkipStorageInit == TRUE)
      return TRUE;

    if (!storage_device_hp_is_valid_partition(dev, partition) ||
            hotplug_dev_get_device_info(dev->hparts[partition], &hdev_info) != 0) {
        return FALSE;
    }

    logMessage("Device Total Logical Blocks: 0x%x", (unsigned int)dev->partition_sizes[partition]);
    logMessage("Device Block Size in Bytes: 0x%x", (unsigned int)dev->sector_size);
    logMessage("Device Total Physical Paritions: 0x%x", dev->num_partitions);
    logMessage("Device Manufacturer ID: 0x%x", hdev_info.manufacturer_id);
    logMessage("Device Serial Number: 0x%x", hdev_info.prod_serial_num);
    return TRUE;
}

static boolean emmc_commit_extras(void *device, storage_device_extras_t *storage_extras) {
  storage_device_hp_t *dev = (storage_device_hp_t *) device;
    struct sdcc_device *handle;
    int32 rc = 0;

    logMessage("In emmc_commit_extras()");

    logMessage("DRIVE4_SIZE_IN_KB %d", storage_extras->emmc_extras.GPP_size[0]);
    logMessage("DRIVE5_SIZE_IN_KB %d", storage_extras->emmc_extras.GPP_size[1]);
    logMessage("DRIVE6_SIZE_IN_KB %d", storage_extras->emmc_extras.GPP_size[2]);
    logMessage("DRIVE7_SIZE_IN_KB %d", storage_extras->emmc_extras.GPP_size[3]);
    logMessage("ENH_SIZE %d", storage_extras->emmc_extras.ENH_size);
    logMessage("ENH_START_ADDR %d", storage_extras->emmc_extras.ENH_start_addr);
    logMessage("GPP_ENH_FLAG %d", storage_extras->emmc_extras.GPP_enh_flag);

    // These values are in KB right now. Therefore Y * 1024/512 becomes Y * 2 in terms of sectors
    storage_extras->emmc_extras.GPP_size[0] *= 2;
    storage_extras->emmc_extras.GPP_size[1] *= 2;
    storage_extras->emmc_extras.GPP_size[2] *= 2;
    storage_extras->emmc_extras.GPP_size[3] *= 2;

    logMessage("storage_extras->emmc_extras.GPP_size[0] = %d", storage_extras->emmc_extras.GPP_size[0]);
    logMessage("storage_extras->emmc_extras.GPP_size[1] = %d", storage_extras->emmc_extras.GPP_size[1]);
    logMessage("storage_extras->emmc_extras.GPP_size[2] = %d", storage_extras->emmc_extras.GPP_size[2]);
    logMessage("storage_extras->emmc_extras.GPP_size[3] = %d", storage_extras->emmc_extras.GPP_size[3]);

    logMessage("Calling hotplug_get_internal_handle()");

    rc = hotplug_get_internal_handle(dev->hwhole_dev, (void **)&handle);
    if (rc < 0)
    {
        logMessage("hotplug_get_internal_handle failed. Return code: %d", rc);
        MyErrorMessage(EMMC_COMMIT_EXTRAS_FAILURE);
        return FALSE;
    }

    logMessage("Calling sdcc_config_emmc_gpp_enh()");

    if (sdcc_config_emmc_gpp_enh(handle, &storage_extras->emmc_extras) != SDCC_NO_ERROR)
    {
        hotplug_release_internal_handle(dev->hwhole_dev, (void **)&handle);
        logMessage("sdcc_config_emmc_gpp_enh failed");
        MyErrorMessage(EMMC_COMMIT_EXTRAS_FAILURE);
        return FALSE;
    }

    logMessage("Calling hotplug_release_internal_handle()");
    
    hotplug_release_internal_handle(dev->hwhole_dev, (void **)&handle);
    
    return TRUE;
}

static boolean ufs_commit_extras(void *device, storage_device_extras_t *storage_extras) {
  storage_device_hp_t *dev = (storage_device_hp_t *) device;
    struct ufs_handle *partition_config;
    struct ufs_info_type mem_info;
    int32 rc = 0;
    boolean result = TRUE;
    SIZE_T alloc_units, units_to_create = 0;
    SIZE_T capacity_to_alloc_factor;
    SIZE_T enhanced1_units = 0, enhanced2_units = 0;
    SIZE_T conversion_ratio = 1;
    int i = 0;

    partition_config = ufs_open(0, UFS_WLUN_DEVICE);
    if (partition_config == NULL)
    {
        logMessage("Call to ufs_open(0, UFS_WLUN_DEVICE) failed");
        MyErrorMessage(UFS_COMMIT_EXTRAS_FAILURE);
        return FALSE;
    }

    ufs_set_refclk_freq(partition_config, 19200000);

    rc = ufs_get_device_info(partition_config, &mem_info);
    if (0 != rc)
    {
        logMessage("Could not get UFS partition info. Return code: %d", rc);

        result = FALSE;
        goto cleanup;
    }

    dev->sector_size = mem_info.bMinAddrBlockSize * 512;
    dev->blocks_per_alloc_unit = (mem_info.dSegmentSize * mem_info.bAllocationUnitSize * 512) / dev->sector_size;

    if(dev->blocks_per_alloc_unit==0)
    {
        logMessage("Unsupported UFS memory type %d", storage_extras->ufs_extras.unit[i].bMemoryType);
        MyErrorMessage(UFS_COMMIT_EXTRAS_FAILURE);
        goto cleanup;
    }

    // NOTE: that at this point dNumAllocUnits *is* size_in_KB and needs to be converted
    //

    capacity_to_alloc_factor = (dev->blocks_per_alloc_unit * dev->sector_size) / 512;
    if (mem_info.qTotalRawDeviceCapacity % capacity_to_alloc_factor != 0)
    {
        logMessage("Raw capacity not a multiple of alloc unit size");
        MyErrorMessage(UFS_COMMIT_EXTRAS_FAILURE);
        result = FALSE;
        goto cleanup;
    }
    alloc_units = (mem_info.qTotalRawDeviceCapacity / capacity_to_alloc_factor) ;

    units_to_create = 0;
    enhanced1_units = enhanced2_units = 0;
    for (i = 0; i < sizeof(storage_extras->ufs_extras.unit) / sizeof(storage_extras->ufs_extras.unit[0]) && units_to_create <= alloc_units; i++)
    {
        uint32 alloc_units;
        uint32 base_units;
        base_units = storage_extras->ufs_extras.unit[i].dNumAllocUnits  / dev->sector_size * 1024;
        alloc_units = (base_units / (dev->blocks_per_alloc_unit));
        /* If the blocks per allocation unit is not a multiple of 'base_units' then
         * we need to round up. */
        if ((base_units % dev->blocks_per_alloc_unit) != 0)
          alloc_units++;

        storage_extras->ufs_extras.unit[i].dNumAllocUnits = alloc_units;

        if (0 == storage_extras->ufs_extras.unit[i].bMemoryType) {
            // Do nothing. This is just to ensure an error is not thrown
            // for this memory type
        }
        else if (3 == storage_extras->ufs_extras.unit[i].bMemoryType) {
            storage_extras->ufs_extras.unit[i].dNumAllocUnits = storage_extras->ufs_extras.unit[i].dNumAllocUnits * (mem_info.wEnhanced1CapAdjFac / 0x100);
            enhanced1_units += storage_extras->ufs_extras.unit[i].dNumAllocUnits;
        }
        else if (4 == storage_extras->ufs_extras.unit[i].bMemoryType) {
            storage_extras->ufs_extras.unit[i].dNumAllocUnits = storage_extras->ufs_extras.unit[i].dNumAllocUnits * (mem_info.wEnhanced2CapAdjFac / 0x100);
            enhanced2_units += storage_extras->ufs_extras.unit[i].dNumAllocUnits;
        }
        else
        {
            logMessage("Unsupported UFS memory type %d", storage_extras->ufs_extras.unit[i].bMemoryType);
            MyErrorMessage(UFS_COMMIT_EXTRAS_FAILURE);
            result = FALSE;
            goto cleanup;
        }

        units_to_create += storage_extras->ufs_extras.unit[i].dNumAllocUnits;
    }
    if (enhanced1_units > mem_info.dEnhanced1MaxNAllocU)
    {
        logMessage("Size %d exceeds max enhanced%d area size %d", enhanced1_units, 1, mem_info.dEnhanced1MaxNAllocU);
        MyErrorMessage(UFS_COMMIT_EXTRAS_FAILURE);
        result = FALSE;
        goto cleanup;
    }
    if (enhanced2_units > mem_info.dEnhanced2MaxNAllocU)
    {
        logMessage("Size %d exceeds max enhanced%d area size %d", enhanced2_units, 2, mem_info.dEnhanced2MaxNAllocU);
        MyErrorMessage(UFS_COMMIT_EXTRAS_FAILURE);
        result = FALSE;
        goto cleanup;
    }
    if (units_to_create > alloc_units)
    {
        logMessage("Specified size %d exceeds device size %d", units_to_create, alloc_units);
        MyErrorMessage(UFS_COMMIT_EXTRAS_FAILURE);
        result = FALSE;
        goto cleanup;
    }

    if (storage_extras->lun_to_grow != -1) {
        if (0 == storage_extras->ufs_extras.unit[storage_extras->lun_to_grow].bMemoryType)
            conversion_ratio = 1;
        else if (3 == storage_extras->ufs_extras.unit[storage_extras->lun_to_grow].bMemoryType)
            conversion_ratio = (mem_info.wEnhanced1CapAdjFac / 0x100);
        else if (4 == storage_extras->ufs_extras.unit[storage_extras->lun_to_grow].bMemoryType)
            conversion_ratio = (mem_info.wEnhanced2CapAdjFac / 0x100);
        else if (5 == storage_extras->ufs_extras.unit[storage_extras->lun_to_grow].bMemoryType)
            conversion_ratio = (mem_info.wEnhanced3CapAdjFac / 0x100);
        else if (6 == storage_extras->ufs_extras.unit[storage_extras->lun_to_grow].bMemoryType)
            conversion_ratio = (mem_info.wEnhanced4CapAdjFac / 0x100);

        storage_extras->ufs_extras.unit[storage_extras->lun_to_grow].dNumAllocUnits += ( (alloc_units - units_to_create) / conversion_ratio );
    }

    rc = ufs_configure_device (partition_config, &(storage_extras->ufs_extras));
    if (rc != 0)
    {
        logMessage("Failed to configure UFS device. Return code: %d", rc);
        MyErrorMessage(UFS_COMMIT_EXTRAS_FAILURE);
        result = FALSE;
        goto cleanup;
    }

cleanup:
    //hotplug_release_internal_handle(dev->hwhole_dev, (void **)&partition_config);
    ufs_close(partition_config);
    return result;
}

boolean storage_device_hp_commit_extras(void *device, storage_device_extras_t *storage_extras) {
  storage_device_hp_t *dev = (storage_device_hp_t *) device;
    switch (dev->current_storage_type) {
        case HOTPLUG_TYPE_MMC:
            return emmc_commit_extras(dev, storage_extras);
        case HOTPLUG_TYPE_UFS:
            return ufs_commit_extras(dev, storage_extras);
        default:
            return FALSE;
    }
}

static boolean emmc_fw_update(void *device, byte *fw_bin, uint32 num_bytes) {
  storage_device_hp_t *dev = (storage_device_hp_t *) device;
    SDCC_STATUS rc;
    int ffu_status;
    struct sdcc_device *hsdev_handle;
    uint64 fw_ver_before = 0;
    uint64 fw_ver_after = 0;
    boolean fw_download_failed = FALSE;
    boolean result;
    int num_sectors;
    sdcc_mem_info_type sdcc_info;

    hsdev_handle = sdcc_handle_open (0, PARTITION_EMMC_USER);
    if (hsdev_handle == NULL)
    {
        logMessage("Could not open User partition. Check card.");
        MyErrorMessage(EMMC_FW_UPDATE_FAILURE);
        return FALSE;
    }

    rc = sdcc_handle_get_fw_version (hsdev_handle, &fw_ver_before);
    if (rc != SDCC_NO_ERROR)
    {
        logMessage("Failed to get current FW Version before update. Return code: %d", rc);
        MyErrorMessage(EMMC_FW_UPDATE_FAILURE);
        result = FALSE;
        goto cleanup;
    }

    rc = sdcc_handle_mem_get_device_info (hsdev_handle, &sdcc_info);
    if (rc != SDCC_NO_ERROR)
    {
        logMessage("Failed to get device info for FW update. Return code: %d", rc);
        MyErrorMessage(EMMC_FW_UPDATE_FAILURE);
        result = FALSE;
        goto cleanup;
    }

    /* The SDCC API takes the argument as sectors, therefore the image size should be a multiple of sectors. */
    if (num_bytes % sdcc_info.block_len != 0)
    {
        logMessage("Failed FW update. Image size (%d) is not a multiple of sector size (%d)", num_bytes, sdcc_info.block_len);
        MyErrorMessage(EMMC_FW_UPDATE_FAILURE);
        result = FALSE;
        goto cleanup;
    }
    num_sectors = num_bytes / sdcc_info.block_len;

    rc = sdcc_handle_fw_update (hsdev_handle, fw_bin, num_sectors);
    if (rc != SDCC_NO_ERROR)
    {
        logMessage("Failed to download FW Binary. reboot the target. Return code: %d", rc);
        fw_download_failed = TRUE; /* Note that FW Download failed, so that we
                              can return after trying card re-initialization */
        MyErrorMessage(EMMC_FW_UPDATE_FAILURE);
    }

    /* Done with handle. Close it */
    (void) sdcc_handle_close (hsdev_handle);

    /* Bring device down for reset */
    if (FALSE == storage_device_hp_close (dev))
    {
        logMessage("Failed to close storage during FW update. Please powercycle device and try again");
        MyErrorMessage(EMMC_FW_UPDATE_FAILURE);
        return FALSE;
    }

    if (sdcc_deinit_device(0) != SDCC_NO_ERROR)
    {
        logMessage("Failed to deinit storage. Please powercycle device and try again");
        MyErrorMessage(EMMC_FW_UPDATE_FAILURE);
        return FALSE;
    }

    // If FW download had failed, just return after attempting to restore the card status
    if (fw_download_failed == TRUE)
    {
        return FALSE;
    }

    hsdev_handle = sdcc_handle_open (0, PARTITION_EMMC_USER);
    if (hsdev_handle == NULL)
    {
        logMessage("Could not open User partition after reset. Check card.");
        MyErrorMessage(EMMC_FW_UPDATE_FAILURE);
        return FALSE;
    }


    if (storage_device_hp_open (dev, STORAGE_DEVICE_TYPE_MMC) == FALSE)
    {
        logMessage("storage_device_hp_open (dev, STORAGE_DEVICE_TYPE_MMC) returned FALSE");
        MyErrorMessage(EMMC_FW_UPDATE_FAILURE);
        return FALSE;
    }

    rc = sdcc_handle_get_ffu_status (hsdev_handle, &ffu_status);
    if (rc != SDCC_NO_ERROR)
    {
        logMessage("Failed to get FFU status. Return code: %d", rc);
        MyErrorMessage(EMMC_FW_UPDATE_FAILURE);
        result = FALSE;
        goto cleanup;
    }

    if (ffu_status != SDCC_NO_ERROR)
    {
        logMessage("FW Update failed with status. Return code: %d", rc);
        MyErrorMessage(EMMC_FW_UPDATE_FAILURE);
        result = FALSE;
        goto cleanup;
    }

    rc = sdcc_handle_get_fw_version (hsdev_handle, &fw_ver_after);
    if (rc != SDCC_NO_ERROR)  
    {
        logMessage("Failed to get current FW Version after update. Check card. Return code: %d", rc);
        MyErrorMessage(EMMC_FW_UPDATE_FAILURE);
        result = FALSE;
        goto cleanup;
    }

    logMessage("FW Update Successful. FW Version updated from '0x%X' to '0x%X'",
               (int) fw_ver_before, (int) fw_ver_after);
    result = TRUE;

cleanup:
    if (hsdev_handle != NULL)  {
        (void) sdcc_handle_close (hsdev_handle);
    }

    return result;
}

static boolean ufs_fw_update(byte *fw_bin, uint32 num_bytes)
{
    uint32_t rc = 1;
    struct ufs_handle *hsdev_handle = NULL;
    struct ufs_handle *hswdev_handle = NULL;
    boolean result = FALSE;

    hswdev_handle = ufs_open (0, UFS_WLUN_DEVICE);
    hsdev_handle = ufs_open (0, 0);
    if (hsdev_handle == NULL)  {
        logMessage("Could not open LU0. Check card.");
        return FALSE;
    }

//    rc = ufs_fw_update_write (hsdev_handle, num_bytes, 0, fw_bin);
    if (rc != 0) {
        logMessage("Failed to download FW Binary rc=%d", rc);
        return FALSE;
    }

    logMessage("FW Update Successful.");
    result = TRUE;

    return result;
}

boolean storage_device_hp_fw_update(void *device, byte *fw_bin, uint32 num_bytes) {
  storage_device_hp_t *dev = (storage_device_hp_t *) device;
    switch (dev->current_storage_type) {
        case HOTPLUG_TYPE_MMC:
            return emmc_fw_update(dev, fw_bin, num_bytes);
        case HOTPLUG_TYPE_UFS:
            return ufs_fw_update(fw_bin, num_bytes);
        default:
            return FALSE;
    }
}

static boolean emmc_get_device_info_raw(void *device, void *raw_data_buff, uint32 *buff_len)
{
  storage_device_hp_t *dev = (storage_device_hp_t *) device;
    SDCC_STATUS SdccStatus = SDCC_ERR_UNKNOWN;
    struct sdcc_device *storage_dev_handle;

    if (NULL == dev || NULL == raw_data_buff)
    {
        logMessage("eMMC GetStorageInfo Error. NULL pointer.");
        return FALSE;
    }

    storage_dev_handle = sdcc_handle_open (0, PARTITION_EMMC_USER);

    if (NULL == storage_dev_handle)
    {
        logMessage("eMMC GetStorageInfo Failed. Could not open eMMC handle.");
        return FALSE;
    }

    SdccStatus = sdcc_get_emmc_info_raw_data (storage_dev_handle, (void *)raw_data_buff, buff_len);
    if (SDCC_NO_ERROR != SdccStatus)
    {
        logMessage("eMMC GetStorageInfo Failed. Status =%d", SdccStatus);
        return FALSE;
    }

    return TRUE;
}

static boolean ufs_get_device_info_raw(void *device, void *raw_data_buff, uint32 *buff_len)
{
  storage_device_hp_t *dev = (storage_device_hp_t *) device;
    int32 UfsStatus = 0;
    struct ufs_handle *storage_dev_handle = NULL;

    if (NULL == dev || NULL == raw_data_buff)
    {
        logMessage("UFS GetStorageInfo. Error NULL pointer.");
        return FALSE;
    }

    storage_dev_handle = ufs_open(0, UFS_WLUN_DEVICE);

    if (NULL == storage_dev_handle)
    {
        logMessage("Could not open UFS handle.");
        return FALSE;
    }

    if (*buff_len < sizeof (struct ufs_info_type))
    {
        logMessage("UFS GetStorageInfo: Buffer is too small. Buffer Length = %d", *buff_len);
        return FALSE;
    }

    UfsStatus = ufs_get_device_info (storage_dev_handle, (struct ufs_info_type*)raw_data_buff);
    if (0 != UfsStatus)
    {
        logMessage("Could not get UFS device info. Status = %d", UfsStatus);
        return FALSE;
    }

    *buff_len = sizeof (struct ufs_info_type);

    return TRUE;
}

boolean storage_device_hp_get_info_raw(void *device, void *raw_data_buff, uint32 *buff_len)
{
  storage_device_hp_t *dev = (storage_device_hp_t *) device;
    switch (dev->current_storage_type)
    {
        case HOTPLUG_TYPE_MMC:
            return emmc_get_device_info_raw (dev, raw_data_buff, buff_len);
        case HOTPLUG_TYPE_UFS:
            return ufs_get_device_info_raw(dev, raw_data_buff, buff_len);
        default:
            return FALSE;
    }
}

boolean storage_device_hp_set_type (void *device, enum storage_device_type tp)
{
  storage_device_hp_t *dev = (storage_device_hp_t *) device;
  hotplug_dev_type type = get_hotplug_type(tp);
  dev->current_storage_type = type;
  return TRUE;
}



#else /* There is no Hotplug support. */

void storage_device_hp_init_hotplug(void){}
void *storage_device_hp_init_struct(void)
{
  return NULL;
}

boolean storage_device_hp_open(void *dev, enum storage_device_type type)
{
  (void) dev;
  (void) type;
  return FALSE;
}

boolean storage_device_hp_close(void *dev)
{
  (void) dev;
  return FALSE;
}

boolean storage_device_hp_read(void *dev, uint32 slot, uint32 partition, byte *buffer, uint64 start_sector, uint64 num_sectors)
{
  (void) dev;
  (void) slot;
  (void) partition;
  (void) buffer;
  (void) start_sector;
  (void) num_sectors;
  return FALSE;
}

boolean storage_device_hp_write(void *dev, uint32 slot, uint32 partition, byte *buffer, uint64 start_sector, uint64 num_sectors)
{
  (void) dev;
  (void) slot;
  (void) partition;
  (void) buffer;
  (void) start_sector;
  (void) num_sectors;
  return FALSE;
}

boolean storage_device_hp_erase(void *dev, uint32 slot, uint32 partition, uint64 start_sector, uint64 num_sectors)
{
  (void) dev;
  (void) slot;
  (void) partition;
  (void) start_sector;
  (void) num_sectors;
  return FALSE;
}

boolean storage_device_hp_format(void *dev, uint32 slot, uint32 partition)
{
  (void) dev;
  (void) slot;
  (void) partition;
  return FALSE;
}

boolean storage_device_hp_get_num_partition_sectors(void *dev, uint32 slot, uint32 partition, uint64 *num_partition_sectors)
{
  (void) dev;
  (void) slot;
  (void) partition;
  (void) num_partition_sectors;
  return FALSE;
}

boolean storage_device_hp_set_bootable_partition(void *dev, uint32 slot, uint32 partition)
{
  (void) dev;
  (void) slot;
  (void) partition;
  return FALSE;
}

boolean storage_device_hp_get_info(void *dev, uint32 slot, uint32 partition)
{
  (void) dev;
  (void) slot;
  (void) partition;
  return FALSE;
}

boolean storage_device_hp_commit_extras(void *dev, storage_device_extras_t *extras)
{
  (void) dev;
  (void) extras;
  return FALSE;
}

boolean storage_device_hp_fw_update(void *dev, byte *fw_bin, uint32 num_sectors)
{
  (void) dev;
  (void) fw_bin;
  (void) num_sectors;
  return FALSE;
}

boolean storage_device_hp_get_info_raw(void *dev, void *storage_info_raw, uint32 *buff_len)
{
  (void) dev;
  (void) storage_info_raw;
  (void) buff_len;
  return FALSE;
}

boolean storage_device_hp_set_type(void *dev, enum storage_device_type type)
{
  (void) dev;
  (void) type;
  return FALSE;
}

#endif
