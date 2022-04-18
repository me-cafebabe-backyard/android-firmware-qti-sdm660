/** @file boot_config_Sdm660.c

  BootConfigLib is used to get boot configuration information

  Copyright (c) 2015 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential

**/

/*=============================================================================
                              EDIT HISTORY

when         who     what, where, why
----------   ---     -----------------------------------------------------------
2015-06-03   plc     Added boot_from_spi_nor stub
2015-05-08   plc     Initial version

=============================================================================*/

#include <Uefi.h>
#include "HALhwio.h"
#include "BootConfig.h"

#define BOOT_CONFIG_REG             0x00786070
#define BOOT_DEVICE_MASK(val)       (((val) & 0x3E) >> 1)

#define DEFAULT_BOOT_DEVICE         0x0
#define EMMC_SDC1_USB2_0            0x2
#define UFS_USB2_0                  0x4

/******************************************************************************
* FUNCTION      boot_from_ufs
*
* DESCRIPTION   This function returns if device boots from UFS
*
* PARAMETERS    NONE
*
* RETURN VALUE  TRUE if device boots from UFS
*
******************************************************************************/
BOOLEAN boot_from_ufs (void)
{
   UINT32 val = 0;
   val = BOOT_DEVICE_MASK(in_dword(BOOT_CONFIG_REG));
   if (val == UFS_USB2_0)
   {
      return TRUE;
   }
   else
   {
      return FALSE;
   }
}  

/******************************************************************************
* FUNCTION      boot_from_emmc
*
* DESCRIPTION   This function returns if device boots from eMMC
*
* PARAMETERS    NONE
*
* RETURN VALUE  TRUE if device boots from eMMC
*
******************************************************************************/
BOOLEAN boot_from_emmc (VOID)
{
   UINT32 val = BOOT_DEVICE_MASK(in_dword(BOOT_CONFIG_REG));

   /* eMMC is default boot device*/ 
   if ((val == DEFAULT_BOOT_DEVICE) || (val == EMMC_SDC1_USB2_0))
   {
      return TRUE;
   }
   else
   {
      return FALSE;
   }       
}

/******************************************************************************
* FUNCTION      boot_from_spi_nor
*
* DESCRIPTION   This function returns if device boots from SPI NOR
*
* PARAMETERS    NONE
*
* RETURN VALUE  TRUE if device boots from SPI NOR
*
******************************************************************************/
BOOLEAN boot_from_spi_nor (VOID)
{
   return FALSE;
}