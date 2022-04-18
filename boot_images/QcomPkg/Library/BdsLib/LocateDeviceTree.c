/** @file LocateDeviceTree.c
  
  Copyright (c) 2014, Qualcomm Technologies, Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 01/20/14   niting  Initial revision

=============================================================================*/
#include "LocateDeviceTree.h"

/*Function that takes Device Tree, Boot images as input,
 *finds the correct device tree binary for the current platform
 *and loads the device tree binary to the designated address in memory*/
VOID LocateAndCopyDeviceTree (UINT8* DeviceTreeBuff, 
                              UINT32* DeviceTreeSize, 
                              UINT32* DeviceTreeLoadAddr)
{
  struct dt_table*             table;
  struct dt_entry*             dt_entry_ptr;
  //STATIC UINT32                dt_table_offset;
	//STATIC UINT32                dt_actual;
  STATIC UINT32                VersionOffset = 0;

  if (DeviceTreeSize)
  {
    table = (struct dt_table*) DeviceTreeBuff;

    if((dt_entry_ptr = dev_tree_get_entry_ptr(table)) == NULL)
    {
      DEBUG ((EFI_D_ERROR, "ERROR: Getting device tree address failed\n"));
			return;
		}

    VersionOffset = dt_entry_ptr->offset;

    CopyMem (DeviceTreeLoadAddr, DeviceTreeBuff + VersionOffset, dt_entry_ptr->size);
  }
}


/*Supporting function of LocateAndCopyDeviceTree
 *Function takes device tree table as input, and finds the offset of the device tree binary
 *from the current platform and chip info*/
struct dt_entry * dev_tree_get_entry_ptr(struct dt_table *table)
{
  EFI_STATUS                                 Status;
  EFI_CHIPINFO_PROTOCOL                     *pChipInfoProtocol;
  EFI_PLATFORMINFO_PROTOCOL                 *pPlatformInfoProtocol;
  EFI_PLATFORMINFO_PLATFORM_INFO_TYPE        PlatformInfo;

	struct dt_entry*             dt_entry_ptr;
	struct dt_entry*             latest_dt_entry = NULL;
  volatile STATIC UINT32       ChipId;
  volatile STATIC UINT32       PlatformNo;
  volatile STATIC UINT32       PlatformVer;
  
  /* Get Protocol handles */
  Status = gBS->LocateProtocol (&gEfiChipInfoProtocolGuid, NULL,
                               (VOID **) &pChipInfoProtocol);
  if (EFI_ERROR(Status))
  {
    DEBUG ((EFI_D_ERROR, "Locate ChipInfoProtocol failed\n"));
    return NULL;
  }

  Status = gBS->LocateProtocol ( &gEfiPlatformInfoProtocolGuid, NULL,
                                (VOID **) &pPlatformInfoProtocol);
  if (EFI_ERROR(Status))
  {
    DEBUG ((EFI_D_ERROR, "Locate PlatformInfoProtocol failed\n"));
    return NULL;
  }

  Status = pPlatformInfoProtocol->GetPlatformInfo(pPlatformInfoProtocol,
                                                  &PlatformInfo);
  if (EFI_ERROR(Status))
  {
    DEBUG ((EFI_D_ERROR, "GetPlatformInfo failed\n"));
    return NULL;
  }

  /*Following three assignments gets the hardware information needed to locate the corresponding Device Tree Binary
   *Watch out that the naming convention between LK and UEFI are different*/
  
  /*Gets Platform information*/
  PlatformNo = (UINT32)PlatformInfo.platform;

  /*Gets Platform version*/
  PlatformVer = pPlatformInfoProtocol->Version; 

  /*Gets Chip Id*/
  Status = pChipInfoProtocol->GetChipId( pChipInfoProtocol, (EFIChipInfoIdType*)&ChipId);
  if (EFI_ERROR(Status))
  {
    DEBUG ((EFI_D_ERROR, "GetChipID failed\n"));
    return NULL;
  }
 
	dt_entry_ptr = (struct dt_entry *)((CHAR8 *)table + DEV_TREE_HEADER_SIZE);

  UINT32  i;
	for(i = 0; i < table->num_entries; i++)
	{
		/* DTBs are stored in the ascending order of soc revision.
		 * For eg: Rev0..Rev1..Rev2 & so on.
		 * we pickup the DTB with highest soc rev number which is less
		 * than or equal to actual hardware
		 */
		if((dt_entry_ptr->platform_id == ChipId) &&
		   (dt_entry_ptr->variant_id == PlatformNo) &&
		   (dt_entry_ptr->soc_rev == PlatformVer))
		{
				return dt_entry_ptr;
		}
		/* if the exact match not found, return the closest match
		 * assuming it to be the nearest soc version
		 */
		if((dt_entry_ptr->platform_id == ChipId) &&
		   (dt_entry_ptr->variant_id == PlatformNo) &&
		   (dt_entry_ptr->soc_rev == PlatformVer))
		{
			latest_dt_entry = dt_entry_ptr;
		}
		dt_entry_ptr++;
	}

	if (latest_dt_entry) 
  {
    DEBUG ((EFI_D_ERROR, "Loading DTB with SOC version: %a\n", latest_dt_entry->soc_rev));
		return latest_dt_entry;
	}

	return NULL;
}


