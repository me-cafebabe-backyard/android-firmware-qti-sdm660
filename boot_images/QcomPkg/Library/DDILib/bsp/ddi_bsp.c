/*===========================================================================

 ddi_bsp.c
 
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

  $Header: //components/rel/boot.xf/1.4/QcomPkg/Library/DDILib/bsp/ddi_bsp.c#1 $ 
  $DateTime: 2016/08/19 05:58:45 $ 
  $Author: c_mvanim $

YYYY-MM-DD   who     what, where, why
----------   ---     ----------------------------------------------------------
2016-07-27   qbz     Removed unused functions
2014-05-15   wek     Creation for 8996/XBL.

===========================================================================*/

#include "Target_cust.h"
#include "boot_msm.h"
#include "ddi_bsp.h"
#include "SpmiBus.h"
#include "pm_pon.h"
#include "usb_wrapper.h"
#include "boothw_target.h"

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
void bsp_target_reset_edl(void) {
    uint32 *pbl_dload_cookie_ptr = (uint32*) NEW_PBL_FORCE_DOWNLOAD_MAGIC_NUM_BASE;

    *(pbl_dload_cookie_ptr+0) = FORCE_DLOAD_HS_USB_MAGIC_NUM_1;
    *(pbl_dload_cookie_ptr+1) = FORCE_DLOAD_HS_USB_MAGIC_NUM_2;
    *(pbl_dload_cookie_ptr+2) = FORCE_DLOAD_HS_USB_MAGIC_NUM_3;

#ifdef DEVICEPROG_USB_WRITE_SCRATCH_MISSING
   usb_dci_write_scratch(0, 0, 0x0);
#endif /* DEVICEPROG_USB_WRITE_SCRATCH_MISSING */
   /* pull down pmic PS_HOLD to force a reset*/
   //   HWIO_OUTF( MPM2_MPM_PS_HOLD, PSHOLD, 0x0 );

  boot_hw_reset(BOOT_WARM_RESET_TYPE);

   for (;;)
   {
     /* let the watch dog timer expire here... */
   }
}

