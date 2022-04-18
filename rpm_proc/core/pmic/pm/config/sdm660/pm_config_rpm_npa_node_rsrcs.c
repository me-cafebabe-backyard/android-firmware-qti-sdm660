/*! \file  pm_config_rpm_npa_node_rsrcs.c
 *  
 *  \brief  File Contains the PMIC NPA CMI Code
 *  \details  This file contains the needed definition and enum for PMIC NPA layer.
 *  
 *    PMIC code generation Version: 1.0.0.0
 *    PMIC code generation Locked Version: RPM_SMD660_PM660_0p2 - LOCKED

 *    This file contains code for Target specific settings and modes.
 *  
 *  &copy; Copyright 2016 Qualcomm Technologies, All Rights Reserved
 */

/*===========================================================================

                EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module over time.

$Header: //components/rel/rpm.bf/1.8/core/pmic/pm/config/sdm660/pm_config_rpm_npa_node_rsrcs.c#3 $ 
$DateTime: 2017/02/09 04:15:10 $  $Author: pwbldsvc $

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 

===========================================================================*/

/*===========================================================================

                        INCLUDE HEADER FILES

===========================================================================*/

#include "pm_npa.h"
#include "pm_rpm_npa.h"
#include "pmapp_npa.h"

/*===========================================================================

                        MACRO DEFINITIONS

===========================================================================*/

#define PMIC_NPA_CLIENT_NODE_DDR "/node/pmic/client/ddr"
#define PMIC_NPA_CLIENT_NODE_DDR_2 "/node/pmic/client/ddr2"
#define PMIC_NPA_CLIENT_NODE_RPM_INIT "/node/pmic/client/rpm_init"
/*===========================================================================

                        OTHER VARIABLES DEFINITION

===========================================================================*/

extern pm_npa_pam_client_cfg_type
pm_rpm_pam_ddr_rails_info [];

extern pm_npa_pam_client_cfg_type
pm_rpm_pam_ddr_2_rails_info [];

extern pm_npa_pam_client_cfg_type
pm_rpm_pam_rpm_init_rails_info [];

/*===========================================================================

                        VARIABLES DEFINITION

===========================================================================*/

/* NPA NODE DEPENDENCY */
/* DDR Client */
static pm_rpm_local_resource_client_dependency
pm_rpm_proc_client_dev_deps_ddr [] =
{
   {RPM_LDO_B_REQ, 1, PM_RPM_NPA_CLIENT_LDO_REQ, 0 },
   {RPM_SMPS_B_REQ, 1, PM_RPM_NPA_CLIENT_SMPS_REQ, 0 },
   {RPM_SMPS_B_REQ, 3, PM_RPM_NPA_CLIENT_SMPS_REQ, 0 },
   {RPM_SMPS_B_REQ, 5, PM_RPM_NPA_CLIENT_SMPS_REQ, 0 },
   {RPM_LDO_A_REQ, 1, PM_RPM_NPA_CLIENT_LDO_REQ, 0 },
};

static pm_rpm_resource_client_dependency_info
pm_rpm_proc_client_dev_deps_ddr_info =
{
   NPA_ARRAY_SIZE(pm_rpm_proc_client_dev_deps_ddr),
   pm_rpm_proc_client_dev_deps_ddr
};
/* DDR_2 Client */
static pm_rpm_local_resource_client_dependency
pm_rpm_proc_client_dev_deps_ddr_2 [] =
{
   {RPM_SMPS_B_REQ, 3, PM_RPM_NPA_CLIENT_SMPS_REQ, 0 },
   {RPM_SMPS_B_REQ, 5, PM_RPM_NPA_CLIENT_SMPS_REQ, 0 },
   };

static pm_rpm_resource_client_dependency_info
pm_rpm_proc_client_dev_deps_ddr_2_info =
{
   NPA_ARRAY_SIZE(pm_rpm_proc_client_dev_deps_ddr_2),
   pm_rpm_proc_client_dev_deps_ddr_2
};

/* RPM_INIT Client */
static pm_rpm_local_resource_client_dependency
pm_rpm_proc_client_dev_deps_rpm_init[] =
{
   {RPM_LDO_A_REQ, 1, PM_RPM_NPA_CLIENT_LDO_REQ, 0},
}; 

static pm_rpm_resource_client_dependency_info
pm_rpm_proc_client_dev_deps_rpm_init_info =
{
   NPA_ARRAY_SIZE(pm_rpm_proc_client_dev_deps_rpm_init),
   pm_rpm_proc_client_dev_deps_rpm_init
};

/* NPA NODE RESOURCE */
pm_npa_node_resource_info
pm_npa_rpm_pam_node_rsrcs [] =
{
   {
      PMIC_NPA_GROUP_ID_DDR, // Resource Name
      PMIC_NPA_MODE_ID_DDR_CFG_MAX - 1, // Maximum Value
      NPA_RESOURCE_SINGLE_CLIENT, // Resource Attribute
      (void*) pm_rpm_pam_ddr_rails_info, // Resource User Data
      PMIC_NPA_CLIENT_NODE_DDR, // Node Name
      NPA_NODE_DEFAULT, // Node Attributes
      (npa_user_data*)&pm_rpm_proc_client_dev_deps_ddr_info, // Deps Count & Deps
      NULL,
   },
   {
      PMIC_NPA_GROUP_ID_DDR2, // Resource Name
      PMIC_NPA_MODE_ID_DDR_CFG_MAX - 1, // Maximum Value
      NPA_RESOURCE_SINGLE_CLIENT, // Resource Attribute
      (void*) pm_rpm_pam_ddr_2_rails_info, // Resource User Data
      PMIC_NPA_CLIENT_NODE_DDR_2, // Node Name
      NPA_NODE_DEFAULT, // Node Attributes
      (npa_user_data*)&pm_rpm_proc_client_dev_deps_ddr_2_info, // Deps Count & Deps
      NULL,
   },
   {
      PMIC_NPA_GROUP_ID_RPM_INIT, // Resource Name
      PMIC_NPA_MODE_ID_RPM_INIT_MODE_MAX - 1, // Maximum Value
      NPA_RESOURCE_SINGLE_CLIENT, // Resource Attribute
      (void*) pm_rpm_pam_rpm_init_rails_info, // Resource User Data
      PMIC_NPA_CLIENT_NODE_RPM_INIT, // Node Name
      NPA_NODE_DEFAULT, // Node Attributes
      (npa_user_data*)&pm_rpm_proc_client_dev_deps_rpm_init_info, // Deps Count & Deps
      NULL,
   },
};

uint32 num_of_pm_rpm_nodes [] = { 3 };

