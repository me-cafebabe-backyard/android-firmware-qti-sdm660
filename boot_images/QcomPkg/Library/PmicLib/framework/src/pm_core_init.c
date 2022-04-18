/*! \file pm_init.c
*   \n
*   \brief This file contains PMIC initialization function which initializes the PMIC Comm
*   \n layer, PMIC drivers and PMIC applications.
*   \n
*   \n &copy; Copyright 2010-2016 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.


when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
04/03/17   ks      Removed LCDB WA
08/08/15   aab     Added pm_device_setup()
07/23/15   al      Removing NPA from common
12/06/14   al      enabling npa
11/12/14   al      adding for compilation
07/16/14   akm     Comm change Updates
03/31/14   akm     Cleanup
01/15/13   aab     Fixed KW error
05/10/11   jtn     Fix RPM init bug for 8960
07/01/10   umr     Created.
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_resource_manager.h"
#include "pm_comm.h"
#include "device_info.h"
#include "pm_device.h"
#include "pm_target_information.h"
#include "pm_uefi.h"
#include "pm_lcdb.h"
#include "pm_version.h"

#define PM_PRIMARY_PMIC_INDEX  0

//Added WA for LCDB for Drax 1.1 -> should be removed once Display driver makes calls to this
pm_err_flag_type
pm_uefi_post_init (void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;
  
  return err_flag;
}

pm_err_flag_type pm_init( void )
{
    pm_err_flag_type err_flag = PM_ERR_FLAG__SUCCESS;

    err_flag = pm_device_setup();

    if(pm_get_pmic_model(PM_PRIMARY_PMIC_INDEX)== PMIC_IS_UNKNOWN)
    {
      return PM_ERR_FLAG__PMIC_NOT_SUPPORTED;
    }

    err_flag |= pm_target_information_init();

    pm_comm_info_init();

    pm_resource_manager_init();

    err_flag |= pm_uefi_post_init();
	
   return err_flag;

}

