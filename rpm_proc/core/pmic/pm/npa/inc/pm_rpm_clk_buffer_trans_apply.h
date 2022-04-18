#ifndef PM_RPM_CLK_BUFFER_TRANS_APPLY__H
#define PM_RPM_CLK_BUFFER_TRANS_APPLY__H

/*! \file pm_rpm_clk_buffer_trans_apply.h
 *  \n
 *  \brief This file contains prototype definitions for PMIC CLOCK
 *         register resources and register resource dependencies functions.
 *  \n  
 *  \n &copy; Copyright 2011-2015 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/rpm.bf/1.8/core/pmic/pm/npa/inc/pm_rpm_clk_buffer_trans_apply.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
05/29/13   aks     Clk driver input check (do not disable critical clocks) 
04/23/13   hs      Fixed the naming convention in \config.
04/12/13   hs      Code refactoring.
04/12/12   hs      Added fields in pm_npa_clk_buffer_data for properly utilizing the 
                   TransactionManager.
01/26/12   wra     Created.

===========================================================================*/
/*===========================================================================

                        INCLUDE FILES

===========================================================================*/
#include "pm_rpm_utilities.h"
#include "rpmserver.h"
#include "pm_clk_driver.h"

#define GET_PMIC_INDEX_CLK(resourceType) ((resourceType & 0xFF000000 )>> 24) - 0x61;

typedef struct 
{
    uint64 settle_start_time;
    uint64 settle_end_time;
    uint64 prev_off_time; // previous timestamp when the clock was turned OFF
    uint32 clk_ok_us;     // settling time for off-to-on, in us.
}pm_clk_settling_time_info_type;

/* Clock settling log info */
typedef struct
{
    uint64 settle_start_time;
    uint32 actual_time_us;
    uint32 estimated_time_us;
    uint8 periph_subtype;
    uint8 periph_index;
    uint8 pmic_index;
}pm_clk_settle_info_type;


typedef struct 
{
    unsigned        AccessAllowed:1;         // 0 – NO NPA Access; 1 – NPA Access Granted
    unsigned        AlwaysOn:1;              // 0 - allow to be turned off; 1 - always on
    unsigned        SettlingErrorEnabled:1;  // ignore settling failure 
    unsigned        SettlingEnabled:1;       // ignore settling  
    unsigned        MinTimeGapOffOn:28;      // in micro secs
    //32 bit boundary
}pm_rpm_clk_info_type;


typedef struct 
{
    rpm_resource_type                         resourceType;
    pm_clk_data_type                         *clkBuffDriverData;
    pm_rpm_clk_info_type                     **clkInfo;	 
    pm_pwr_resource_dependency_info          **depInfo;
    pm_clk_settling_time_info_type           *settlingInfo;
}pm_npa_clk_buffer_data_type;

void pm_rpm_clk_buffer_register_resources(rpm_resource_type resource, uint32 num_npa_resources, uint8 pmic_index);

void pm_rpm_clk_buffer_register_resource_dependencies(rpm_resource_type resource, uint32 num_npa_resources, uint8 pmic_index);


#endif // PM_RPM_CLK_BUFFER_TRANS_APPLY__H
