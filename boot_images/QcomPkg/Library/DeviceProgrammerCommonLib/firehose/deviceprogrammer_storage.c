/**************************************************************************
 * FILE: deviceprogrammer_storage.c
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

  $Header: //components/rel/boot.xf/1.4/QcomPkg/Library/DeviceProgrammerCommonLib/firehose/deviceprogrammer_storage.c#2 $
  $DateTime: 2016/08/19 05:58:45 $
  $Author: c_mvanim $

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2016-02-10   wek   Add the option to format whole dev or erase a portion.
2016-25-01   wek   Remove warnings seen in static analysis tool.
2015-11-10   wek   Create.

===========================================================================*/


#include "deviceprogrammer_storage.h"
#include "deviceprogrammer_storage_hp.h"
#include "deviceprogrammer_storage_store.h"
#include "deviceprogrammer_firehose.h"
#include <stddef.h>

enum storage_interface
{
  HOTPLUG_INTERFACE,
  STORE_INTERFACE,
  MAX_INTERFACE
};

struct storage_device
{
  enum storage_device_type storage_type;
  enum storage_interface interface;
  void *handle[MAX_INTERFACE];
};

static struct storage_device storage_device_static;

/*
 * Define all the different Operations done by the storage devices.
 */
typedef void (*init_hotplug_func)(void);
typedef void* (*init_struct_func)(void);
typedef boolean(*open_func)(void *dev, enum storage_device_type type);
typedef boolean(*close_func)(void *dev);
typedef boolean(*read_func)(void *dev, uint32 slot, uint32 partition,
                            byte *buffer, uint64 start_sector, uint64 num_sectors);
typedef boolean(*write_func)(void *dev, uint32 slot, uint32 partition,
                             byte *buffer, uint64 start_sector, uint64 num_sectors);
typedef boolean(*erase_func)(void *dev, uint32 slot, uint32 partition,
                             uint64 start_sector, uint64 num_sectors);
typedef boolean(*format_func)(void *dev, uint32 slot, uint32 partition);
typedef boolean(*get_num_partition_sectors_func)(void *dev, uint32 slot,
    uint32 partition, uint64 *num_partition_sectors);
typedef boolean(*set_bootable_partition_func)(void *dev, uint32 slot,
    uint32 partition);
typedef boolean(*get_info_func)(void *dev, uint32 slot, uint32 partition);
typedef boolean(*commit_extras_func)(void *dev,
                                     storage_device_extras_t *extras);
typedef boolean(*fw_update_func)(void *dev, byte *fw_bin, uint32 num_sectors);
typedef boolean(*get_info_raw_func)(void *dev, void *storage_info_raw,
                                    uint32 *buff_len);
typedef boolean(*set_type_func)(void *dev, enum storage_device_type type);

/*
 * Define all the different OPS that are supported by each device.
 */
static init_hotplug_func init_hotplug_ops[MAX_INTERFACE] =
{
  storage_device_hp_init_hotplug,
  storage_device_store_init_hotplug,
};

static init_struct_func init_struct_ops[MAX_INTERFACE] =
{
  storage_device_hp_init_struct,
  storage_device_store_init_struct,
};

static open_func open_ops[MAX_INTERFACE] =
{
  storage_device_hp_open,
  storage_device_store_open,
};

static close_func close_ops[MAX_INTERFACE] =
{
  storage_device_hp_close,
  storage_device_store_close,
};

static read_func read_ops[MAX_INTERFACE] =
{
  storage_device_hp_read,
  storage_device_store_read,
};

static write_func write_ops[MAX_INTERFACE] =
{
  storage_device_hp_write,
  storage_device_store_write,
};

static erase_func erase_ops[MAX_INTERFACE] =
{
  storage_device_hp_erase,
  storage_device_store_erase,
};

static format_func format_ops[MAX_INTERFACE] =
{
  storage_device_hp_format,
  storage_device_store_format,
};


static get_num_partition_sectors_func get_num_partition_sectors_ops[MAX_INTERFACE] =
{
  storage_device_hp_get_num_partition_sectors,
  storage_device_store_get_num_partition_sectors,
};

static set_bootable_partition_func set_bootable_partition_ops[MAX_INTERFACE] =
{
  storage_device_hp_set_bootable_partition,
  storage_device_store_set_bootable_partition,
};

static get_info_func get_info_ops[MAX_INTERFACE] =
{
  storage_device_hp_get_info,
  storage_device_store_get_info,
};

static commit_extras_func commit_extras_ops[MAX_INTERFACE] =
{
  storage_device_hp_commit_extras,
  storage_device_store_commit_extras,
};

static fw_update_func fw_update_ops[MAX_INTERFACE] =
{
  storage_device_hp_fw_update,
  storage_device_store_fw_update,
};

static get_info_raw_func get_info_raw_ops[MAX_INTERFACE] =
{
  storage_device_hp_get_info_raw,
  storage_device_store_get_info_raw,
};

static set_type_func set_type_ops[MAX_INTERFACE] =
{
  storage_device_hp_set_type,
  storage_device_store_set_type,
};


void storage_device_init_hotplug(void)
{
  int i;

  for(i = HOTPLUG_INTERFACE; i < MAX_INTERFACE; i++)
  {
    init_hotplug_ops[i]();
  }
}

storage_device_t *storage_device_init_struct(void)
{
  int i;
  storage_device_t *dev = &storage_device_static;
  dev->storage_type = STORAGE_DEVICE_TYPE_INVALID;
  dev->interface = STORE_INTERFACE;

  for(i = HOTPLUG_INTERFACE; i < MAX_INTERFACE; i++)
  {
    dev->handle[i] = init_struct_ops[i]();
  }

  return dev;
}

static boolean storage_validate_dev(storage_device_t *dev)
{
  if(dev->interface < MAX_INTERFACE)
  {
    return TRUE;
  }
  return FALSE;
}

/* Gets the index for the interface to use for the given type. */
static enum storage_interface get_interface_index(enum storage_device_type type)
{
  switch(type)
  {
  /* case STORAGE_DEVICE_TYPE_UFS: */
  /*   return HOTPLUG_INTERFACE; */
  default:
    return STORE_INTERFACE;
  }
}

boolean storage_device_open(storage_device_t *dev, enum storage_device_type type)
{
  int iface;

  if(type >= STORAGE_DEVICE_TYPE_MAX)
  {
    logMessage("INVALID device type %d, max %d", type, STORAGE_DEVICE_TYPE_MAX);
    return FALSE;
  }

  dev->storage_type = type;
  dev->interface = get_interface_index(type);
  if(storage_validate_dev(dev))
  {
    iface = dev->interface;
    return open_ops[iface](dev->handle[iface], type);
  }
  return FALSE;
}

boolean storage_device_close(storage_device_t *dev)
{
  int iface;
  if(storage_validate_dev(dev))
  {
    iface = dev->interface;
    return close_ops[iface](dev->handle[iface]);
  }
  return FALSE;
}

boolean storage_device_set_bootable_partition(storage_device_t *dev,
    uint32 slot, uint32 partition)
{
  int iface;
  if(storage_validate_dev(dev))
  {
    iface = dev->interface;
    return set_bootable_partition_ops[iface](dev->handle[iface], slot, partition);
  }
  return FALSE;
}

boolean storage_device_read(storage_device_t *dev, uint32 slot,
                            uint32 partition, byte *buffer,
                            uint64 start_sector, uint64 num_sectors)
{
  int iface;
  if(storage_validate_dev(dev))
  {
    iface = dev->interface;
    return read_ops[iface](dev->handle[iface], slot, partition, buffer,
                           start_sector, num_sectors);
  }
  return FALSE;
}

boolean storage_device_write(storage_device_t *dev, uint32 slot, uint32 partition, byte *buffer, uint64 start_sector, uint64 num_sectors)
{
  int iface;
  if(storage_validate_dev(dev))
  {
    iface = dev->interface;
    return write_ops[iface](dev->handle[iface], slot, partition, buffer,
                            start_sector, num_sectors);
  }
  return FALSE;
}

boolean storage_device_erase(storage_device_t *dev, uint32 slot, uint32 partition, uint64 start_sector, uint64 num_sectors)
{
  int iface;
  if(storage_validate_dev(dev))
  {
    iface = dev->interface;
    return erase_ops[iface](dev->handle[iface], slot, partition,
                            start_sector, num_sectors);
  }
  return FALSE;
}

boolean storage_device_format(storage_device_t *dev, uint32 slot,
                             uint32 partition)
{
  int iface;
  if(storage_validate_dev(dev))
  {
    iface = dev->interface;
    return format_ops[iface](dev->handle[iface], slot, partition);
  }
  return FALSE;
}

boolean storage_device_get_num_partition_sectors(storage_device_t *dev,
    uint32 slot, uint32 partition, uint64 *num_partition_sectors)
{
  int iface;
  *num_partition_sectors = 0;
  if(storage_validate_dev(dev))
  {
    iface = dev->interface;
    return get_num_partition_sectors_ops[iface](dev->handle[iface], slot,
                                                partition, num_partition_sectors);
  }
  return FALSE;
}

boolean storage_device_get_info(storage_device_t *dev, uint32 slot,
                                uint32 partition)
{
  int iface;
  if(storage_validate_dev(dev))
  {
    iface = dev->interface;
    return get_info_ops[iface](dev->handle[iface], slot, partition);
  }
  return FALSE;
}

boolean storage_device_commit_extras(storage_device_t *dev,
                                     storage_device_extras_t *storage_extras)
{
  int iface;
  if(storage_validate_dev(dev))
  {
    iface = dev->interface;
    return commit_extras_ops[iface](dev->handle[iface], storage_extras);
  }
  return FALSE;
}

boolean storage_device_fw_update(storage_device_t *dev, byte *fw_bin,
                                 uint32 num_bytes)
{
  int iface;
  if(storage_validate_dev(dev))
  {
    iface = dev->interface;
    return fw_update_ops[iface](dev->handle[iface], fw_bin, num_bytes);
  }
  return FALSE;
}

boolean storage_device_get_info_raw(storage_device_t *dev,
                                    void *raw_data_buff, uint32 *buff_len)
{
  int iface;
  if(storage_validate_dev(dev))
  {
    iface = dev->interface;
    return get_info_raw_ops[iface](dev->handle[iface], raw_data_buff, buff_len);
  }
  return FALSE;
}

boolean storage_device_set_type(storage_device_t *dev, enum storage_device_type type)
{
  int iface;
  dev->storage_type = type;
  dev->interface = get_interface_index(type);
  if(storage_validate_dev(dev))
  {
    iface = dev->interface;
    return set_type_ops[iface](dev->handle[iface], type);
  }
  return FALSE;
}

