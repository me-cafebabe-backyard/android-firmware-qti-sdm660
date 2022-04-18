/**************************************************************************
 * FILE: devprg_storage_spinor.h
 *
 * SPI-NOR Device interface.
 *
 * Copyright (c) 2015 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Qualcomm Proprietary
 *
 *************************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/boot.xf/1.4/QcomPkg/Library/DeviceProgrammerCommonLib/firehose/devprg_storage_spinor.h#2 $
  $DateTime: 2016/08/19 05:58:45 $
  $Author: c_mvanim $

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2015-11-19   wek   Create.

===========================================================================*/

#ifndef __DEVPRG_STORAGE_SPINOR_H__
#define __DEVPRG_STORAGE_SPINOR_H__

#include "devprg_storage.h"

/* For documentation see devprg_storage.h */
void devprg_storage_spinor_init(void);
int devprg_storage_spinor_deinit(void);
void *devprg_storage_spinor_open(uint32 slot, uint32 partition, enum devprg_error *error);
int devprg_storage_spinor_close(void *device);
int devprg_storage_spinor_read(void *device, void *buffer,
                               uint64 start_sector, uint64 num_sectors);
int devprg_storage_spinor_write(void *device, void *buffer,
                                uint64 start_sector, uint64 num_sectors);
int devprg_storage_spinor_erase(void *device, uint64 start_sector,
                                uint64 num_sectors);
int devprg_storage_spinor_format(void *device);
int devprg_storage_spinor_set_bootable(void *device, int enable);
int devprg_storage_spinor_get_info(void *device,
                                   struct devprg_storage_info *dev_info);
int devprg_storage_spinor_configure(uint32 slot,
                                    struct devprg_storage_cfg_data *config);
int devprg_storage_spinor_fw_update(uint32 slot, void *buffer,
                                    uint32 size_in_bytes);
int devprg_storage_spinor_info_raw_size(void *device, uint32 *size);
int devprg_storage_spinor_info_raw(void *device, void *buffer,
                                   uint32 *size);

#endif /* __DEVPRG_STORAGE_SPINOR_H__ */
