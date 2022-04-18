/** @file LocateDeviceTree.h
  
  Copyright (c) 2014, Qualcomm Technologies, Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 01/20/14   niting  Initial revision

=============================================================================*/
#ifndef __LOCATEDEVICETREE_H__
#define __LOCATEDEVICETREE_H__

#include "BdsInternal.h"
#include <Protocol/EFIChipInfo.h>
#include <Protocol/EFIPlatformInfo.h>

#define DEV_TREE_HEADER_SIZE       12
#define DEVICE_TREE_IMAGE_OFFSET   0x5F8800

/*Struct def for device tree entry*/
struct dt_entry
{
	UINT32 platform_id;
	UINT32 variant_id;
	UINT32 Reserved;
	UINT32 soc_rev;
	UINT32 offset;
	UINT32 size;
};

/*Struct def for device tree table*/
struct dt_table
{
	UINT32 magic;
	UINT32 version;
	UINT32 num_entries;
};


/*Function that takes Device Tree, Boot images as input,
 *finds the correct device tree binary for the current platform
 *and loads the device tree binary to the designated address in memory*/
VOID LocateAndCopyDeviceTree (UINT8*  DeviceTreeBuff, 
                              UINT32* DeviceTreeSize, 
                              UINT32* DeviceTreeLoadAddr);

/*Supporting function of LocateAndCopyDeviceTree
 *Function takes device tree table as input, and finds the offset of the device tree binary
 *from the current platform and chip info*/
struct dt_entry * dev_tree_get_entry_ptr(struct dt_table *table);


#endif
