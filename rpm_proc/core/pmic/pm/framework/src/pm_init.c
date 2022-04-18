/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

pm_init.c

GENERAL DESCRIPTION
This file contains PMIC initialization functions

EXTERNALIZED FUNCTIONS
None.

INITIALIZATION AND SEQUENCING REQUIREMENTS
None.

Copyright (c) 2010-2015 QUALCOMM Technologies Incorporated, All Rights Reserved.
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/rpm.bf/1.8/core/pmic/pm/framework/src/pm_init.c#2 $  

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
03/10/17   as      Removed pc_enable LDO1A vote (CR2017297)
04/23/13   hs      Fixed the naming convention in \config.
04/12/13   hs      Code refactoring.
02/27/13   hs      Code refactoring.
05/10/11   jtn     Fix RPM init bug for 8960
07/01/10   umr     Created.
===========================================================================*/
#include "pm_comm.h"
#include "pm_target_information.h"
#include "pm_rpm_npa.h"
#include "pmapp_npa.h"
#include "pm_resource_manager.h"
#include "pm_rpm_target.h"
#include "pm_mpm_internal.h"
#include "device_info.h"
#include "PlatformInfo.h"
#include "pm_debug.h"

#define PM_INDEX   0
npa_client_handle handle_rpm_init = NULL;

/* This flag to be set with PMIC Type from <VIRTIO/RUMI_load>.cmm Script */
static uint8 g_pm_stub_pmic_type = 0;


#ifdef PM_IMAGE_RPM_PROC
__attribute__((section("pm_dram_reclaim_pool")))
void pm_init( void )
#else
void pm_rpm_init( void )
#endif
{
    if (TRUE == pm_is_stub_enabled())
    {
        return ;
    }

    pm_comm_channel_init_internal();
    
    pm_version_detect();

    if ((PMIC_IS_UNKNOWN == pm_get_pmic_model(PM_INDEX)) && (PlatformInfo_GetPlatform() == PLATFORMINFO_TYPE_RUMI))
    {
      return;
    }

    pm_target_information_init();
    
    pm_rpm_platform_pre_init();

    pm_comm_info_init();

    pm_resource_manager_init();

    pm_rpm_proc_npa_init ();

    pm_rpm_platform_init();

    pm_rpm_sleep_init();

    /*Init for SPMI MPM command sequence. */
    pm_mpm_cmd_init();

    pm_rpm_platform_post_init();

    pm_debug_info_init();

    return;
}

boolean pm_is_stub_enabled ( void )
{
  if (0 != g_pm_stub_pmic_type)
  {
    return TRUE;
  }
  return FALSE;
}

