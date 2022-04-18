#ifndef PM_RPM_VS_TRANS_APPLY__H
#define PM_RPM_VS_TRANS_APPLY__H

/*! \file pm_rpm_vs_trans_apply.h
 *  \n
 *  \brief This file contains prototype definitions for PMIC VS
 *         register resources and register resource dependencies functions.
 *  \n  
 *  \n &copy; Copyright 2011-2014 QUALCOMM Technologies Incorporated, All Rights Reserved
 */
/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/rpm.bf/1.8/core/pmic/pm/npa/inc/pm_rpm_vs_trans_apply.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/11/13   hs      Adding settling time for regulators.
04/23/13   hs      Fixed the naming convention in \config.
04/12/13   hs      Code refactoring.
07/20/12   hs      Added settling time.
04/12/12   hs      Added fields in pm_npa_vs_data for properly utilizing the 
                   TransactionManager.
01/26/12   wra     Created.

===========================================================================*/
/*===========================================================================

                        INCLUDE FILES

===========================================================================*/
#include "pm_rpm_utilities.h"
#include "rpmserver.h"
#include "pm_vs_driver.h"

#define GET_PMIC_INDEX_VS(resourceType) ((resourceType & 0xFF0000 )>> 16) - 0x61;

typedef struct 
{
    unsigned        AccessAllowed:1;         // 0 – NO NPA Access; 1 – NPA Access Granted
    unsigned        AlwaysOn:1;              // 0 - allow to be turned off; 1 - always on
    unsigned        MinSettlingTime:16;      // in micro secs
    unsigned        SettlingErrorEnabled:1;  //ignore settling failure 
    unsigned        SettlingEnabled:1;       //ignore settling 
    unsigned        Reserved:12;
    //32 bit boundary
}pm_rpm_vs_rail_info_type;

typedef struct 
{
    rpm_resource_type                         resourceType;
    pm_vs_data_type                          *vsDriverData;
    pm_rpm_vs_rail_info_type                 **railInfo;
    pm_pwr_resource_dependency_info          **depInfo;
    pm_pwr_settling_info_type                *settlingInfo;
}pm_npa_vs_data_type;

void pm_rpm_vs_register_resources(rpm_resource_type resource, uint32 num_npa_resources, uint8 pmic_index);

void pm_rpm_vs_register_resource_dependencies(rpm_resource_type resource, uint32 num_npa_resources, uint8 pmic_index);

#endif // PM_RPM_VS_TRANS_APPLY__H
