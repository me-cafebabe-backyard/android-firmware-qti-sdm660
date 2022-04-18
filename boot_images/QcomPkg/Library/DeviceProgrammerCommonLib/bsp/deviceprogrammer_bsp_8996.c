/*===========================================================================

 deviceprogrammer_bsp_8996.c

GENERAL DESCRIPTION
 This file contain the platform dependent code that can be provided by boot.
  
 Copyright (c) 2015 Qualcomm Technologies, Inc.
 All Rights Reserved.
 Qualcomm Confidential and Proprietary

============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/boot.xf/1.4/QcomPkg/Library/DeviceProgrammerCommonLib/bsp/deviceprogrammer_bsp_8996.c#2 $ 
  $DateTime: 2016/08/19 05:58:45 $ 
  $Author: c_mvanim $

YYYY-MM-DD   who     what, where, why
----------   ---     ----------------------------------------------------------
2014-05-15   wek     Creation for 8996/XBL.

===========================================================================*/

#include "Target_cust.h"
#include "boot_msm.h"
#include "deviceprogrammer_bsp.h"
#include "SpmiBus.h"
#include "pm_pon.h"
#include "usb_wrapper.h"
#include "boothw_target.h"
#include "boot_dload.h"

//#define SHARED_IMEM_BASE                    0xFE805000
#define NEW_PBL_FORCE_DOWNLOAD_MAGIC_NUM_BASE   (SHARED_IMEM_BASE + 0xFE0)
#define FORCE_DLOAD_HS_USB_MAGIC_NUM_1      0x322A4F99
#define FORCE_DLOAD_HS_USB_MAGIC_NUM_2      0xC67E4350
#define FORCE_DLOAD_HS_USB_MAGIC_NUM_3      0x77777777


/******************************************************************************
*
* Description:
*    This function Resets the target
*
******************************************************************************/
void bsp_target_reset(void)
{
  boot_hw_reset(BOOT_HARD_RESET_TYPE);
}

void bsp_target_reset_edl(void)
{
  boot_dload_transition_pbl_forced_dload();
}

void bsp_target_poweroff(void)
{
  boot_hw_powerdown();
}

/******************************************************************************
*
* Description:
*    This function performs the HW Init for eHOSTDL
*    The HW init includes enabling SDRAM, Clocks etc...
*
******************************************************************************/
void bsp_hw_init(void)
{
}

