/** @file UpdateCmdLine.h
  
  Copyright (c) 2014, Qualcomm Technologies, Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 01/20/14   niting  Initial revision

=============================================================================*/
#ifndef __UPDATECMDLINE_H__
#define __UPDATECMDLINE_H__

enum baseband {
	BASEBAND_MSM = 0,
	BASEBAND_APQ = 1,
	BASEBAND_CSFB = 2,
	BASEBAND_SVLTE1 = 3,
	BASEBAND_SVLTE2A = 4,
	BASEBAND_MDM = 5,
	BASEBAND_SGLTE = 6,
	BASEBAND_DSDA = 7,
	BASEBAND_DSDA2 = 8,
	BASEBAND_SGLTE2 = 9,
	BASEBAND_32BITS = 0x7FFFFFFF
};



/* Assuming unauthorized kernel image by default */
STATIC INT32 auth_kernel_img = 0;


/*Function that returns value of boolean boot_into_ffbm
 *Becomes an if condition at update_cmdline( ) */
BOOLEAN get_ffbm(CHAR8 *ffbm, UINT32 size);


/*Function that returns whether the boot is emmc boot*/
INT32 target_is_emmc_boot(VOID);


/*Function that returns whether the kernel is signed*/
BOOLEAN target_use_signed_kernel(VOID);


/* This function will always return 0 to facilitate
 * automated testing/reboot with usb connected.
 * uncomment if this feature is needed */
UINT32 target_pause_for_battery_charge(VOID);

/*Determine correct androidboot.baseband to use*/
UINT32 target_baseband(VOID);

UINT8 *update_cmdline(CONST CHAR8 * cmdline);

#endif




