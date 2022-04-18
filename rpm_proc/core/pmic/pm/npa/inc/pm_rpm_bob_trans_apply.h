#ifndef _PM_RPM_BOB_TRANS_APPLY__H_
#define _PM_RPM_BOB_TRANS_APPLY__H_

/*! \file pm_rpm_boost_byp_trans_apply.h
 *  \n
 *  \brief This file contains prototype definitions for PMIC Boost Bypass
 *         register resources and register resource dependencies functions.
 *  \n  
 *  \n &copy; Copyright 2013 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/rpm.bf/1.8/core/pmic/pm/npa/inc/pm_rpm_bob_trans_apply.h#1 $

when        who     what, where, why
--------    ---     ----------------------------------------------------------
11/22/13    kt      Created.
========================================================================== */
/*===========================================================================

                        INCLUDE FILES

===========================================================================*/
#include "pm_rpm_utilities.h"
#include "rpmserver.h"
#include "pm_bob.h"
#include "pm_bob_driver.h"

#define GET_PMIC_INDEX_BOB(resourceType) ((resourceType & 0xFF000000 )>> 24) - 0x61;

/*===========================================================================

                     STRUCTURE TYPE AND ENUM

===========================================================================*/

typedef struct 
{
    unsigned        AccessAllowed:1;  // 0 – NO NPA Access; 1 – NPA Access Granted
    unsigned        AlwaysOn:1;       // 0 - allow to be turned off; 1 - always on
    unsigned        MinPwrMode:3;     // 0 - Force Bypass, 1- Auto Boost
    unsigned        SettlingErrorEnabled:1;  //ignore settling failure
    unsigned        SettlingEnabled:1;       //ignore settling 
    unsigned        reserved:25; 
    //32 bit boundary
    unsigned        MinVoltage:16;    // in mV
    unsigned        MaxVoltage:16;    // in mV
    //32 bit boundary
    unsigned        MinPinVoltage:16; // in mV
    unsigned        MaxPinVoltage:16; // in mV
}pm_rpm_bob_rail_info_type;


/* BOB Callback data used during translate and apply */
typedef struct 
{
    rpm_resource_type                        resourceType;
    pm_bob_data_type                         *bobDriverData;
    pm_rpm_bob_rail_info_type                **railInfo;
    pm_pwr_resource_dependency_info          **depInfo;
    pm_pwr_settling_info_type                *settlingInfo;
    pm_npa_pin_control_enable_type           *bobPinMappingInfo;
}pm_npa_bob_data_type;




/*===========================================================================

                        FUNCTION PROTOTYPE

===========================================================================*/

void pm_rpm_bob_register_resources(rpm_resource_type resource, uint32 num_npa_resources, uint8 pmic_index);
void pm_rpm_bob_register_resource_dependencies(rpm_resource_type resource, uint32 num_npa_resources, uint8 pmic_index);

#endif // PM_RPM_BOOST_BYP_TRANS_APPLY__H
