/**************************************************************************
 * FILE: devprg_storage.h
 *
 * Common APIs for accessing any storage device.
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

  $Header: //components/rel/boot.xf/1.4/QcomPkg/Library/DeviceProgrammerCommonLib/firehose/devprg_storage.h#2 $
  $DateTime: 2016/08/19 05:58:45 $
  $Author: c_mvanim $

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2016-02-10   wek   Add the option to format whole dev or erase a portion.
2016-01-07   wek   Add tag partition ID/number that represents whole disk.
2015-11-12   wek   Create.

===========================================================================*/

#ifndef __DEVPRG_STORAGE_H__
#define __DEVPRG_STORAGE_H__

#include "comdef.h"

enum devprg_error
{
  DEVPRG_SUCCESS = 0,
  DEVPRG_ERROR_NOMEM = 1,
  DEVPRG_ERROR_INVAL_PARAM,
  DEVPRG_ERROR_STORAGE, /* Untranslated error from storage. */
  DEVPRG_ERROR_NOT_SUPPORTED, /* Operation not supported. */
};

enum devprg_storage_type
{
  DEVPRG_STORAGE_NULL,
  DEVPRG_STORAGE_SDCC,
  DEVPRG_STORAGE_SPINOR,
  DEVPRG_STORAGE_UFS,
  DEVPRG_STORAGE_MAX_TYPE,
};

/* There are some operations that should be done on the whole device.
 * Each storage technology uses a different value to represent the whole
 * disk. The value below represents the whole disk for the storage layer
 * in devprg. Each storage technology layer would translate it accordingly
 */
#define DEVPRG_WHOLE_DEVICE_PARTITION 0xFEBA

/*
 * Initializes the internal data structures of each storage device.
 *
 * This function must not access storage, only RAM.
 */
void devprg_storage_init(void);

/*
 * Cleans up the module data.
 *
 * Cleans up the module data, if any device is open it should be closed
 * by the end of this call.
 *
 * @return Error code as given by enum devprg_error.
 */
int devprg_storage_deinit(void);

/* Private handle for all storage medias. */
struct devprg_storage;

/*
 * Open the Storage media.
 *
 * Open the storage media (eMMC, UFS, NAND, NOR, etc), on the given slot and
 * physical partition or LUN.
 *
 * @param type      Type of storage media: UFS, eMMC, NOR, NAND, etc.
 * @param slot      Slot of the device in the case of multiple slots or
 *                  controllers
 * @param partition Physical partition or LUN. Not used if device does not
 *                  support it.
 * @param error[out] Error value, populated only if handle is NULL.
 *                   List of errors in enum devprg_error.
 *
 * @return Handle to the device, NULL in case of error.
 **/
struct devprg_storage *devprg_storage_open(enum devprg_storage_type type,
    uint32 slot, uint32 partition, enum devprg_error *error);
/*
 * Close a storage device.
 *
 * Close a storage device previously opened. Depending on the underlying
 * implementation it may not actually call the underlying close to save
 * time in the subsequent opens.
 *
 * @param device   Handle returned from devprg_storage_open()
 *
 * @return Error code as given by enum devprg_error.
 **/
int devprg_storage_close(struct devprg_storage *device);

/*
 * Read data from a device.
 *
 * @param device   Handle returned from devprg_storage_open()
 * @param buffer   Buffer to write to disk.
 * @param start_sector  Sector number to write the data.
 * @param num_sectors   Number of sectors to write.
 *
 * @return Error code as given by enum devprg_error.
 **/
int devprg_storage_read(struct devprg_storage *device, void *buffer,
                        uint64 start_sector, uint64 num_sectors);


/*
 * Write data to a device.
 *
 * @param device   Handle returned from devprg_storage_open()
 * @param buffer   Buffer to write to disk.
 * @param start_sector  Sector number to write the data.
 * @param num_sectors   Number of sectors to write. *
 *
 * @return Error code as given by enum devprg_error.
 **/
int devprg_storage_write(struct devprg_storage *device, void *buffer,
                         uint64 start_sector, uint64 num_sectors);

/*
 * Erase/Unmap a group of sectors.
 *
 * @param device   Handle returned from devprg_storage_open()
 * @param start_sector  Sector number to write the data.
 * @param num_sectors   Number of sectors to write.
 *
 * @return Error code as given by enum devprg_error.
 **/
int devprg_storage_erase(struct devprg_storage *device,
                         uint64 start_sector, uint64 num_sectors);

/*
 * Format/erase the whole partition.
 *
 * @param device   Handle returned from devprg_storage_open()
 *
 * @return Error code as given by enum devprg_error.
 **/
int devprg_storage_format(struct devprg_storage *device);


/*
 * Set the bootable partition.
 *
 * Sets what physical partition or LUN will be the bootable partition.
 *
 *
 *
 * @param device   Handle returned from devprg_storage_open()
 * @param enable   1=Enable bootable partition, 0=Disable bootable partition.
 *                 Some devices like UFS allows to disable the bootable
 *                 partition.
 *
 * @return Error code as given by enum devprg_error.
 **/
int devprg_storage_set_bootable(struct devprg_storage *device, int enable);


struct devprg_storage_info
{
  uint64 total_blocks; /* Total number of blocks */
  uint32 block_size; /* Size of a block in bytes. */
  uint32 page_size; /* Size of a page/sector in bytes. */
  uint32 num_physical; /* Number of physical partitions. */
  uint64 manufacturer_id; /* ID of the manufacturer. */
  uint64 serial_num; /* Serial number of the device. */
  char   fw_version[32]; /* String containing the firmware version, null terminated. */
  char   memory_type[5]; /* String containing the Memory type: NOR, UFS, eMMC, NAND. */
  char   product_name[32];
};

/*
 * Get the Common storage device info.
 *
 * @param device        Handle returned from devprg_storage_open()
 * @param dev_info[out] Device info structure w
 *
 * @return Error code as given by enum devprg_error.
 **/
int devprg_storage_get_info(struct devprg_storage *device,
                            struct devprg_storage_info *dev_info);

/* Structured copied from sdcc API file to remove dependency it. */
PACKED struct devprg_sdcc_emmc_gpp_enh_desc
{
  uint32  GPP_size[4];    /**< Size of the GPP partitions in sectors */
  uint32  ENH_size;       /**< Size of enhanced area in sectors      */
  uint32  ENH_start_addr; /**< Start of the enhanced area in sectors  */
  uint8   GPP_enh_flag;   /**< Enhanced area flag         */
}PACKED_POST;

/* Structures copied from UFS and padded for 4 byte alignment. */
PACKED struct devprg_ufs_unit_descr {
  uint8     bLUEnable;          /**< 1 for enabled LU */
  uint8     bBootLunID;         /**< >0 for using this LU for boot */
  uint8     bLUWriteProtect;    /**< 1 = power on WP, 2 = permanent WP */
  uint8     bMemoryType;        /**< >0 for enhanced memory type */
  uint32    dNumAllocUnits;     /**< Number of allocation unit for this LU */
  uint8     bDataReliability;   /**< >0 for reliable write support */
  uint8     bLogicalBlockSize;  /**< See section 13.2.3 of UFS standard */
  uint8     bProvisioningType;  /**< >0 for thin provisioning */
  uint8     pad;  /* To make it 4 byte aligned. */
  uint16    wContextCapabilities;   /**< See Unit Descriptor Description of UFS standard */
  uint16    pad2; /* To make the structure 8 byte aligned.  */
} PACKED_POST;

PACKED struct devprg_ufs_config_descr {
  uint8     bNumberLU;      /**< Total number of active LUs */
  uint8     bBootEnable;    /**< 1 for enabling device for partial init */
  uint8     bDescrAccessEn; /**< Can device descriptor be accessed during partial init */
  uint8     bInitPowerMode; /**< Initial power mode of the device after reset */
  uint8     bHighPriorityLUN;    /**< LUN of the high priority LU */
  uint8     bSecureRemovalType;  /**< Erase configuration necessary for data removal */
  uint8     bInitActiveICCLevel; /**< ICC level after reset */
  uint8     bConfigDescrLock;    /**< Set to 1 to lock the Configation Descriptor */
  uint16    wPeriodicRTCUpdate;  /**< >0 to set a priodic RTC update rate */
  int8      lun_to_grow; /* Added to indicate the LUN to grow to max size. */
  uint8     pad; /* To make it 4 byte aligned. */
  uint32    qVendorConfigCode;   /**< Vendor specific configuration code */
  struct devprg_ufs_unit_descr unit[8];
} PACKED_POST;


struct devprg_storage_cfg_data
{
  union
  {
    struct devprg_sdcc_emmc_gpp_enh_desc emmc_config;
    struct devprg_ufs_config_descr ufs_config;
  };
};

/*
 * Configure the storage deivice (provision)
 *
 * Configure the size of each LUNs or physical partitions.
 *
 * Developer Note: This is a tricky API to make common across all storage
 * media/technologies. Device Programmer will provide a common interface
 * for the PC to send data. If the API changes on the target, then the
 * external API may also need changing which isn't desirable. Probably the
 * best way to handle this is to have a packet for each underlying storage
 * API, if the underlying API changes, that would be deprecate the old
 * packet and and a new one.
 *
 * @param device   Handle returned from devprg_storage_open()
 * @param cfg_data Configuration Data.
 *
 * @return Error code as given by enum devprg_error.
 **/
int devprg_storage_configure(enum devprg_storage_type type, uint32 slot,
                             struct devprg_storage_cfg_data *config);

/*
 * Update the firmware of the storage part.
 *
 * @param device   Handle returned from devprg_storage_open()
 * @param buffer   Pointer to the firmware data to be programmed.
 * @param size     Size in bytes of the firmware. The underlying driver will
 *         send the data as if they were sectors, therefore the buffer size
 *         should be a multiple of the sector size. For example, the
 *         firmware is 32KiB + 1 byte in size, this parameter should be
 *         32KiB + 1 byte, but the buffer should be 32KiB + 1SectorSize.
 *
 * @return Error code as given by enum devprg_error.
 **/
int devprg_storage_fw_update(enum devprg_storage_type type, uint32 slot,
                             void *buffer, uint32 size_in_bytes);

/*
 * Get the maximum size of the raw device info.
 *
 * @param device    Handle returned from devprg_storage_open()
 * @param size[out] Size in bytes of the raw device info.
 *
 * @return Error code as given by enum devprg_error.
 **/
int devprg_storage_info_raw_size(struct devprg_storage *device, uint32 *size);

/*
 * Get the raw device info.
 *
 * Each storage technology has a unique structure with information about
 * the device. This function gets the raw data from the device, the caller
 * should interpret the data depending on the specific storage part.
 *
 * @param device      Handle returned from devprg_storage_open()
 * @param buffer[out] The raw device info output buffer.
 * @param size[out]   Actual number of bytes populated in the buffer.
 *
 * @return Error code as given by enum devprg_error.
 **/
int devprg_storage_info_raw(struct devprg_storage *device, void *buffer,
                            uint32 *size);

#endif /* __DEVPRG_STORAGE_H__ */
