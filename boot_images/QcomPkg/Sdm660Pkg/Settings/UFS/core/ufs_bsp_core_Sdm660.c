/**********************************************************************
* ufs_bsp_uefi_Sdm660.c
*
* Board support file for SDM660
*
* Copyright (c) 2013-2016, 2018 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
* 
*
**********************************************************************/

/*=======================================================================
                        Edit History

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Settings/UFS/core/ufs_bsp_core_Sdm660.c#3 $
$DateTime: 2018/10/16 09:22:30 $

YYYY-MM-DD   who     what, where, why
---------------------------------------------------------------------- 
2018-10-12   sb      Add reset api support
2016-08-18   jt      Skip link startup, gear switch for core  
2015-06-15   rh      Disable the PHY from decoding the LCC sequence
2014-09-17   rh      Adapted for 8996 
2013-10-30   rh      Clock regime function cleanup
2013-10-30   rh      More accurate delay added
2013-06-19   rh      Initial creation
===========================================================================*/

#include <Uefi.h>
#include <HALhwio.h>
#include <Library/PcdLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/CacheMaintenanceLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UncachedMemoryAllocationLib.h>
#include <Library/SynchronizationLib.h>
#include <Library/TimerLib.h>
#include <Protocol/EFIHWIO.h>
#include <Protocol/EFIClock.h>
#include <Protocol/LoadedImage.h> 
#include <Protocol/EFIPlatformInfo.h> 

#include <Library/PcdLib.h>
#include <Library/ArmLib.h>

#include "DDIPlatformInfo.h"
#include "../inc/ufs_osal.h"
#include "../inc/ufs_bsp.h"
#include "../inc/ufs_phy_hwio_v2.h"

#define UFS_PHY_PCS_READY_TIMEOUT      0xffffff


EFI_CLOCK_PROTOCOL *hUFS_Clock = NULL;
DalPlatformInfoPlatformType g_platform;


void ufs_bsp_clk_set (uint8_t hostid, uint32_t mode)
{
   (void) hostid;
}   

void ufs_bsp_cache_op (void *addr, uint32_t len, uint32_t op) 
{
   if (op & FLUSH) {
      WriteBackInvalidateDataCacheRange (addr, len);
   }

   if (op & INVAL) {
      InvalidateDataCacheRange (addr, len);
   }

   if (op & CLEAN) {
      WriteBackDataCacheRange (addr, len);
   }
}

void ufs_bsp_busy_wait(uint32_t us)
{
   gBS->Stall(us);
}

void ufs_bsp_memory_barrier ()
{
   ArmDataMemoryBarrier();
}

// Constant table for UFS-PHY initialization
static struct ufs_mphy_init_item ufs_bsp_mphy_init_table[] = {
     { HWIO_UFS_QSERDES_COM_VCO_TUNE_MAP_ADDR,                      0x04},       // Adjust for series A
     {0,0}};

static struct ufs_mphy_init_item ufs_bsp_mphy_rate_b_init_table[] = {
     { HWIO_UFS_QSERDES_COM_VCO_TUNE_MAP_ADDR,                      0x44},
     {0,0}};

uint32_t ufs_bsp_get_mphy_init_item_table (struct ufs_mphy_init_item **itm)
{
   *itm = ufs_bsp_mphy_init_table;
   if (g_platform == DALPLATFORMINFO_TYPE_RUMI) {
      return 0;
   }
   else {
      return sizeof(ufs_bsp_mphy_init_table)/sizeof(struct ufs_mphy_init_item);
   }
}

uint32_t ufs_bsp_get_mphy_init_rate_b_item_table (struct ufs_mphy_init_item **itm)
{
   *itm = ufs_bsp_mphy_rate_b_init_table;
   if (g_platform == DALPLATFORMINFO_TYPE_RUMI) {
      return 0;
   }
   else {
      return sizeof(ufs_bsp_mphy_rate_b_init_table)/sizeof(struct ufs_mphy_init_item);
   }
}

// Start the PHY and wait for the PHY to be ready
uint32_t ufs_bsp_mphy_start (uint8_t hostid)
{
   uintptr_t base_addr;
   int32_t tout = UFS_PHY_PCS_READY_TIMEOUT;

   if (g_platform == DALPLATFORMINFO_TYPE_RUMI) {
      return SUCCESS;
   }

   base_addr = ufs_bsp_get_reg_baseaddress (hostid);
   HWIO_REG_OUTM (base_addr, UFS_UFS_PHY_PHY_START_ADDR, 1, 1);
   ufs_bsp_busy_wait (10);
   
   while (!(HWIO_REG_IN(base_addr, UFS_UFS_PHY_PCS_READY_STATUS_ADDR) & 0x01)) {
      if (tout-- == 0) {
         return FAIL;
      }
      ufs_bsp_busy_wait (1);
   }
   return SUCCESS;
}

void ufs_bsp_post_link_init (uint8_t hostid)
{
   uintptr_t base_addr;

   base_addr = ufs_bsp_get_reg_baseaddress (hostid);
   out_dword(HWIO_UFS_UFS_PHY_LINECFG_DISABLE_ADDR + base_addr, 0x02);   
}

void ufs_bsp_reset (uint8_t hostid)
{
   (void) hostid; 
}

void ufs_bsp_device_reset (uint8_t hostid)
{
   (void) hostid; 
}

void *ufs_bsp_allocate_norm_buf (size_t size)
{
    VOID *mem;
    EFI_STATUS            status;
    status=gBS->AllocatePool(EfiBootServicesData,size,(VOID**)&mem);

    if (EFI_SUCCESS != status)
    {
        DEBUG((EFI_D_ERROR, "UFS: Allocate memory of size 0x%x     [FAILED]\n",size));
        return NULL;
    }
    return mem;
}

void  ufs_bsp_free_norm_buf (void *pmem)
{
    if ( pmem == NULL )
        return;

    gBS->FreePool(pmem);
}

void *ufs_bsp_allocate_xfer_buf (size_t size)
{
    return UncachedAllocatePool(size);
}

void  ufs_bsp_free_xfer_buf (void *pmem)
{
    if ( pmem == NULL )
        return;

    UncachedFreePool(pmem);
}

void ufs_bsp_get_platform_config (struct ufs_bsp_config_item *itm)
{
   EFI_STATUS                          eResult;
   EFI_PLATFORMINFO_PROTOCOL           *hPlatformInfoProtocol;
   EFI_PLATFORMINFO_PLATFORM_INFO_TYPE PlatformInfo;
   
   eResult = gBS->LocateProtocol(&gEfiPlatformInfoProtocolGuid, NULL,
     (VOID **) &hPlatformInfoProtocol);
   if (eResult != EFI_SUCCESS)
   {
     DEBUG((EFI_D_WARN, "Error: Failed to locate PlatformInfo protocol.\n"));
     return;
   }
   
   eResult = hPlatformInfoProtocol->GetPlatformInfo(hPlatformInfoProtocol,
     &PlatformInfo);
   if (eResult != EFI_SUCCESS)
   {
     DEBUG((EFI_D_WARN, "Error: GetPlatformInfo failed.\n"));
     return;
   }
   
   if (PlatformInfo.platform >= EFI_PLATFORMINFO_NUM_TYPES)
   {
     DEBUG((EFI_D_WARN, "Error: Unknown platform type (%d)\n", PlatformInfo.platform));
     eResult = EFI_PROTOCOL_ERROR;
     return;
   }

	if (PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_RUMI) {
   	g_platform = DALPLATFORMINFO_TYPE_RUMI;
	}

   if (g_platform == DALPLATFORMINFO_TYPE_RUMI) {
      itm->skip_gear_sw = 1;
      itm->skip_link_start = 0;
      itm->slow_xfer = 1;
      itm->core_skip = 0; 
   }
   else {
      /* VIRTIO or Silicon */
      itm->slow_xfer = 0;
      itm->skip_gear_sw = 1;
      itm->skip_link_start = 1;
      itm->core_skip = 1; 
   }
}

uintptr_t ufs_bsp_get_reg_baseaddress (uint8_t hostid)
{
   (void) hostid;
   return (uintptr_t) 0x1da0000;
}

boolean ufs_bsp_get_dal_config(struct ufs_dal_config_item *itm)
{
   (void) itm; 
   return TRUE; 
}
