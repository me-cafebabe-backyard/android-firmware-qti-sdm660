#ifndef PM_RPM_BOOST_TRANS_APPLY__H
#define PM_RPM_BOOST_TRANS_APPLY__H

/*! \file pm_rpm_boost_trans_apply.h
 *  \n
 *  \brief This file contains prototype definitions for PMIC BOOST
 *         register resources and register resource dependencies functions.
 *  \n  
 *  \n &copy; Copyright 2013-2014 QUALCOMM Technologies Incorporated, All Rights Reserved
 */
/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/rpm.bf/1.8/core/pmic/pm/npa/inc/pm_rpm_boost_trans_apply.h#1 $

when       who     what, where, why
--------   ---      ---------------------------------------------------------- 
06/11/13   hs      Adding settling time for regulators.
04/23/13   hs      Fixed the naming convention in \config.
04/12/13   hs      Code refactoring.
1/29/13    aks     Adding support for 5v boost as a separate driver

===========================================================================*/
/*===========================================================================

                        INCLUDE FILES

===========================================================================*/
#include "pm_rpm_utilities.h"
#include "rpmserver.h"
#include "pm_boost_driver.h"
#include "pmapp_npa.h"

#define GET_PMIC_INDEX_BOOST(resourceType) ((resourceType & 0xFF000000 )>> 24) - 0x61;


typedef struct 
{
    unsigned        AccessAllowed:1;         // 0 – NO NPA Access; 1 – NPA Access Granted
    unsigned        AlwaysOn:1;              // 0 - allow to be turned off; 1 - always on
    unsigned        MinSettlingTime:16;      // in micro secs
    unsigned        SettlingErrorEnabled:1;  //ignore settling failure 
    unsigned        SettlingEnabled:1;       //ignore settling
    unsigned        Reserved:12;
    //32 bit boundary
}pm_rpm_boost_rail_info_type;

// BOOST Callback data used during translate and apply
typedef struct 
{
    rpm_resource_type                        resourceType;
    pm_boost_data_type                       *boostDriverData;
    pm_pwr_resource_dependency_info          **depInfo;
    pm_rpm_boost_rail_info_type              **railInfo;
    pm_pwr_settling_info_type                *settlingInfo;
}pm_npa_boost_data_type;

void pm_rpm_boost_register_resources(rpm_resource_type resource, uint32 num_npa_resources, uint8 pmic_index);
void pm_rpm_boost_register_resource_dependencies(rpm_resource_type resource, uint32 num_npa_resources, uint8 pmic_index);
pm_npa_boost_data_type* pm_rpm_boost_get_resource_data(uint8 pmic_index);
void pm_rpm_boost_dependency_execute(rpm_application_info *info, pm_npa_boost_int_rep* shadow_data);

#endif // PM_RPM_BOOST_TRANS_APPLY__H
