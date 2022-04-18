/*! \file
 *  
 *  \brief  pm_config_npa_dep.c ----This file contains initialization functions for NPA Device layer
 *  \details This file contains initialization functions for NPA Device layer and
 *          the node and resource definition implementations
 *  
 *    PMIC code generation Version: 1.0.0.0
 *    PMIC code generation NPA Client Version: MSM8998_baseline_0p0 NEW - Approved
 *    This file contains code for Target specific settings and modes.
 *  
 *  &copy; Copyright 2015 Qualcomm Technologies, All Rights Reserved
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.

$Header: //components/rel/rpm.bf/1.8/core/pmic/pm/config/sdm660/pm_config_npa_dep.c#2 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
03/09/17   as      Added resource dependency on ldo_dep_b (CR2017297)


===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

#include "pm_npa.h"

// Component Resource Structure Creation
static pm_pwr_resource
smps_a[] =
{
   {(rpm_resource_type)0, 0}, // this is invalid place holder
   {RPM_SMPS_A_REQ, 1},
   {RPM_SMPS_A_REQ, 2},
   {RPM_SMPS_A_REQ, 3},
   {RPM_SMPS_A_REQ, 4},
   {RPM_SMPS_A_REQ, 5},
   {RPM_SMPS_A_REQ, 6},
  
};

static pm_pwr_resource
smps_b[] =
{
   {(rpm_resource_type)0, 0}, // this is invalid place holder
   {RPM_SMPS_B_REQ, 1},
   {RPM_SMPS_B_REQ, 2},
   {RPM_SMPS_B_REQ, 3},
   {RPM_SMPS_B_REQ, 4},
   {RPM_SMPS_B_REQ, 5},
  
};

// Component Resource Structure Creation
static pm_pwr_resource
bob_b[] =
{
   {(rpm_resource_type)0, 0}, // this is invalid place holder
   {RPM_BOB_B_REQ, 1},
};

static pm_pwr_resource
ldo_a[] =
{
   {(rpm_resource_type)0, 0}, // this is invalid place holder
   {RPM_LDO_A_REQ, 1},
   {RPM_LDO_A_REQ, 2},
   {RPM_LDO_A_REQ, 3},
   {RPM_LDO_A_REQ, 4},
   {RPM_LDO_A_REQ, 5},
   {RPM_LDO_A_REQ, 6},
   {RPM_LDO_A_REQ, 7},
   {RPM_LDO_A_REQ, 8},
   {RPM_LDO_A_REQ, 9},
   {RPM_LDO_A_REQ, 10},
   {RPM_LDO_A_REQ, 11},
   {RPM_LDO_A_REQ, 12},
   {RPM_LDO_A_REQ, 13},
   {RPM_LDO_A_REQ, 14},
   {RPM_LDO_A_REQ, 15},
   {RPM_LDO_A_REQ, 16},
   {RPM_LDO_A_REQ, 17},
   {RPM_LDO_A_REQ, 18},
   {RPM_LDO_A_REQ, 19},

};

static pm_pwr_resource
ldo_b[] =
{
   {(rpm_resource_type)0, 0}, // this is invalid place holder
   {RPM_LDO_B_REQ, 1},
   {RPM_LDO_B_REQ, 2},
   {RPM_LDO_B_REQ, 3},
   {RPM_LDO_B_REQ, 4},
   {RPM_LDO_B_REQ, 5},
   {RPM_LDO_B_REQ, 6},
   {RPM_LDO_B_REQ, 7},
   {RPM_LDO_B_REQ, 8},
   {RPM_LDO_B_REQ, 9},
   {RPM_LDO_B_REQ, 10},

};


// Component Resource Child Depend Structure Creation

static pm_pwr_resource *
smps4_a_child_dep[] =
{
   &ldo_a[8],
   &ldo_a[9],
   &ldo_a[10],
   &ldo_a[11],
   &ldo_a[12],
   &ldo_a[13],
   &ldo_a[14],   
};

static pm_pwr_resource *
smps5_a_child_dep[] =
{
   &ldo_a[1],
   &ldo_a[6],
   &ldo_a[7],
};



static pm_pwr_resource *
smps2_b_child_dep[] =
{
   &ldo_a[2],
   &ldo_a[3],
   &ldo_a[5],
   &ldo_b[1],
   &ldo_b[9],
   &ldo_b[10],
};


static pm_pwr_resource *
bob1_b_child_dep[] =
{
   &ldo_a[15],
   &ldo_a[16],
   &ldo_a[17],
   &ldo_a[18],
   &ldo_a[19],
   &ldo_b[2],
   &ldo_b[3],
   &ldo_b[4],
   &ldo_b[5],
   &ldo_b[6],
   &ldo_b[7],
   &ldo_b[8],
};

// Component Resource Dependency Information
pm_pwr_resource_dependency_info
smps_dep_a[] =
{
   { NULL, NULL, 0, }, // Invalid zeroth array - NOT USED
   // S1
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // S2
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // S3
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // S4
   {
      NULL, // parent resource
      smps4_a_child_dep, // child resource dependencies
      0,  // parent internal client handle
   },
   // S5
   {
      NULL, // parent resource
      smps5_a_child_dep, // child resource dependencies
      0,  // parent internal client handle
   },
   // S6
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
};

pm_pwr_resource_dependency_info
smps_dep_b[] =
{
   { NULL, NULL, 0, }, // Invalid zeroth array - NOT USED
   // S1
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // S2
   {
      NULL, // parent resource
      smps2_b_child_dep, // child resource dependencies
      0,  // parent internal client handle
   },
   // S3
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // S4
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
};
pm_pwr_resource_dependency_info
bob_dep_b[] =
{
   { NULL, NULL, 0, }, // Invalid zeroth array - NOT USED
   // B1
   {
      NULL, // parent resource
      bob1_b_child_dep, // child resource dependencies
      0,  // parent internal client handle
   },
};

pm_pwr_resource_dependency_info
ldo_dep_a[] =
{
   { NULL, NULL, 0, }, // Invalid zeroth array - NOT USED
   // L1
   {
      &smps_a[5],
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // L2
   {
      &smps_b[2],
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // L3
   {
      &smps_b[2],
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // L4
   {
      NULL,
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // L5
   {
      &smps_b[2],
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // L6
   {
      &smps_a[5],
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // L7
   {
      &smps_a[5],
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // L8
   {
      &smps_a[4],
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // L9
   {
      &smps_a[4],
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // L10
   {
      &smps_a[4],
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // L11
   {
      &smps_a[4],
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // L12
   {
      &smps_a[4],
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // L13
   {
      &smps_a[4],
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // L14
   {
      &smps_a[4],
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // L15
   {
      &bob_b[1],
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // L16
   {
      &bob_b[1],
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // L17
   {
      &bob_b[1],
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // L18
   {
      &bob_b[1],
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // L19
   {
      &bob_b[1],
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },

};


pm_pwr_resource_dependency_info
ldo_dep_b[] =
{
   { NULL, NULL, 0, }, // Invalid zeroth array - NOT USED
   // L1
   {
      &smps_b[2],
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // L2
   {
      &bob_b[1],
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // L3
   {
      &bob_b[1],
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // L4
   {
      &bob_b[1],
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // L5
   {
      &bob_b[1],
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // L6
   {
      &bob_b[1],
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // L7
   {
      &bob_b[1],
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // L8
   {
      &bob_b[1],
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // L9
   {
      &smps_b[2],
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // L10
   {
      &smps_b[2],
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
};



pm_pwr_resource_dependency_info
clk_dep_a[] =
{
   { NULL, NULL, 0, }, // Invalid zeroth array - NOT USED
   // C1
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // C2
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // C3
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // C4
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // C5
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // C6
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // C7
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // C8
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // C9
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // C10
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // C11
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // C12
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
   // C13
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // parent internal client handle
   },
};


pm_pwr_resource_dependency_info* 
smps_dep[] = 
{
    smps_dep_a, 
    smps_dep_b, 
    NULL,
};

pm_pwr_resource_dependency_info* 
ldo_dep[] = 
{
    ldo_dep_a,
    ldo_dep_b,
    NULL,
};


pm_pwr_resource_dependency_info* 
bob_dep[] = 
{
    NULL, 
    bob_dep_b,
    NULL,
};

pm_pwr_resource_dependency_info* 
vs_dep[] = 
{
    NULL,
    NULL,
    NULL,
};

pm_pwr_resource_dependency_info* 
clk_dep[] = 
{
    clk_dep_a,
    NULL,
    NULL, 
};




