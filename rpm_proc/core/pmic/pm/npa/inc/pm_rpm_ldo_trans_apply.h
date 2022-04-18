#ifndef PM_RPM_LDO_TRANS_APPLY__H
#define PM_RPM_LDO_TRANS_APPLY__H

/*! \file pm_rpm_ldo_trans_apply.h
 *  \n
 *  \brief This file contains prototype definitions for PMIC LDO
 *         register resources and register resource dependencies functions.
 *  \n  
 *  \n &copy; Copyright 2011-2016 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/rpm.bf/1.8/core/pmic/pm/npa/inc/pm_rpm_ldo_trans_apply.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/11/13   hs      Adding settling time for regulators.
04/23/13   hs      Fixed the naming convention in \config.
04/12/13   hs      Code refactoring.
07/20/12   hs      Added settling time.
04/12/12   hs      Added fields in pm_npa_ldo_data for properly utilizing the 
                   TransactionManager.
01/26/12   wra     Created.

===========================================================================*/
/*===========================================================================

                        INCLUDE FILES

===========================================================================*/
#include "pm_rpm_utilities.h"
#include "rpmserver.h"
#include "pm_ldo_driver.h"

#define GET_PMIC_INDEX_LDO(resourceType) ((resourceType & 0xFF000000 )>> 24) - 0x61;

// Give 50 micro seconds delay for non-stepper LDOs for voltage increase as 
// recommended by systems. Non-stepper LDOs wouldn't scale much in most cases.
#define PM_LDO_NON_STEPPER_VOLT_SETTLING_TIME   50 //uS

typedef struct 
{
    unsigned        LpHpCurrentThreshold:12; // in mA
    unsigned        SafetyHeadRoom:12;       // in mV
    unsigned        IsSawControlled:1;       //0 - not SAW controlled 
    unsigned        AccessAllowed:1;         // 0 – NO NPA Access; 1 – NPA Access Granted
    unsigned        AlwaysOn:1;              // 0 - allow to be turned off; 1 - always on
    unsigned        MinPwrMode:3;            // 0 - IPEAK, 1 - NPM
    unsigned        BypassDisallowed:1;      // 0 - Bypass allowed, 1 - Bypass disallowed
    unsigned        DroopDetection:1;        // 0 - OFF, 1 - ON 
    //32 bit boundary
    unsigned        MinVoltage:16;           // in mV
    unsigned        MaxVoltage:16;           // in mV
    //32 bit boundary
    unsigned        MinSettlingTime:16;      // in micro secs
    unsigned        SettlingErrorEnabled:1;  //ignore settling failure
    unsigned        SettlingEnabled:1;       //ignore settling 
    unsigned        StepDownDelay:12;         //Delay while stepping down
    unsigned        Reserved:2;
    //32 bit boundary
}pm_rpm_ldo_rail_info_type;


typedef struct 
{
    rpm_resource_type                         resourceType;
    pm_ldo_data_type                         *ldoDriverData;
    pm_rpm_ldo_rail_info_type                **railInfo;
    pm_pwr_resource_dependency_info          **depInfo;
    boolean                                  *inBypass;
    pm_pwr_settling_info_type                *settlingInfo;
}pm_npa_ldo_data_type;

void pm_rpm_ldo_register_resources(rpm_resource_type resource, uint32 num_npa_resources, uint8 pmic_index);

void pm_rpm_ldo_register_resource_dependencies(rpm_resource_type resource, uint32 num_npa_resources, uint8 pmic_index);

void pm_rpm_ldo_bypass_cb(uint32 device_index, uint32 resource_id, pm_on_off_type on_off);

pm_npa_ldo_data_type* pm_rpm_ldo_get_resource_data(uint8 pmic_index);

void pm_rpm_ldo_dependency_execute(rpm_application_info *info, pm_npa_ldo_int_rep *shadow_data);


#endif // PM_RPM_LDO_TRANS_APPLY__H
