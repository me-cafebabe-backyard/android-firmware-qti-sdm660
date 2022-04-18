/*! \file  pm_config_appsbl_npa_node_rsrcs.c
 *  
 *  \brief  File Contains the PMIC NPA CMI Code
 *  \details  This file contains the needed definition and enum for PMIC NPA layer.
 *  
 *    PMIC code generation Version: 1.0.0.0
 *    PMIC code generation Locked Version: APPSBL_SDM660_PM660_0p4 - LOCKED

 *    This file contains code for Target specific settings and modes.
 *  
 *  &copy; Copyright 2017 Qualcomm Technologies, All Rights Reserved
 */

/*===========================================================================

                EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module over time.

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Settings/PMIC/core/pm_config_appsbl_npa_node_rsrcs.c#5 $ 
$DateTime: 2017/04/08 01:27:52 $  $Author: pwbldsvc $

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 

===========================================================================*/

/*===========================================================================

                        INCLUDE HEADER FILES

===========================================================================*/

#include "pm_npa_device_ldo.h"
#include "pm_npa.h"
#include "pm_appsbl_proc_npa.h"
#include "pmapp_npa.h"
/*===========================================================================

                        MACRO DEFINITIONS

===========================================================================*/

#define PMIC_NPA_CLIENT_NODE_DISP_EXT_DP "/node/pmic/client/disp_ext_dp"
#define PMIC_NPA_CLIENT_NODE_DISP_PRIM "/node/pmic/client/disp_prim"
#define PMIC_NPA_CLIENT_NODE_DISP_PRIM_AMOLED "/node/pmic/client/disp_prim_amoled"
#define PMIC_NPA_CLIENT_NODE_EMMC "/node/pmic/client/emmc"
#define PMIC_NPA_CLIENT_NODE_USB_SS1 "/node/pmic/client/usb_ss1"
/*===========================================================================

                        OTHER VARIABLES DEFINITION

===========================================================================*/

extern pm_npa_pam_client_cfg_type
pm_pam_disp_ext_dp_rails_info [];

extern pm_npa_pam_client_cfg_type
pm_pam_disp_prim_rails_info [];

extern pm_npa_pam_client_cfg_type
pm_pam_disp_prim_amoled_rails_info [];

extern pm_npa_pam_client_cfg_type
pm_pam_emmc_rails_info [];

extern pm_npa_pam_client_cfg_type
pm_pam_usb_ss1_rails_info [];

/*===========================================================================

                        VARIABLES DEFINITION

===========================================================================*/


/* NPA NODE DEPENDENCY */

/* DISP_EXT_DP Client */
npa_node_dependency
pm_appsbl_proc_client_dev_deps_disp_ext_dp [] =
{
   PMIC_NPA_NODE_DEP_LIST( B, ldo, 1 ),
   PMIC_NPA_NODE_DEP_LIST( A, ldo, 1 ),
};

/* DISP_PRIM Client */
npa_node_dependency
pm_appsbl_proc_client_dev_deps_disp_prim [] =
{
   PMIC_NPA_NODE_DEP_LIST( B, ldo, 1 ),
   PMIC_NPA_NODE_DEP_LIST( A, ldo, 1 ),
   PMIC_NPA_NODE_DEP_LIST( A, ldo, 11 ),
   PMIC_NPA_NODE_DEP_LIST( A, ldo, 13 ),
};

/* DISP_PRIM_AMOLED Client */
npa_node_dependency
pm_appsbl_proc_client_dev_deps_disp_prim_amoled [] =
{
   PMIC_NPA_NODE_DEP_LIST( B, ldo, 1 ),
   PMIC_NPA_NODE_DEP_LIST( B, ldo, 6 ),
   PMIC_NPA_NODE_DEP_LIST( A, ldo, 1 ),
   PMIC_NPA_NODE_DEP_LIST( A, ldo, 13 ),
};

/* EMMC Client */
npa_node_dependency
pm_appsbl_proc_client_dev_deps_emmc [] =
{
   PMIC_NPA_NODE_DEP_LIST( B, ldo, 2 ),
   PMIC_NPA_NODE_DEP_LIST( B, ldo, 4 ),
   PMIC_NPA_NODE_DEP_LIST( B, ldo, 5 ),
};

/* USB_SS1 Client */
npa_node_dependency
pm_appsbl_proc_client_dev_deps_usb_ss1 [] =
{
   PMIC_NPA_NODE_DEP_LIST( B, ldo, 1 ),
   PMIC_NPA_NODE_DEP_LIST( B, ldo, 7 ),
   PMIC_NPA_NODE_DEP_LIST( A, ldo, 1 ),
};

/* NPA NODE RESOURCE */
pm_npa_node_resource_info
pm_npa_appsbl_pam_node_rsrcs [] =
{
   {
      PMIC_NPA_GROUP_ID_DISP_EXT_DP, // Resource Name
      PMIC_NPA_MODE_ID_GENERIC_MAX - 1, // Maximum Value
      NPA_RESOURCE_SINGLE_CLIENT, // Resource Attribute
      (void*) pm_pam_disp_ext_dp_rails_info, // Resource User Data
      PMIC_NPA_CLIENT_NODE_DISP_EXT_DP, // Node Name
      NPA_NODE_DEFAULT, // Node Attributes
      NULL,
      pm_appsbl_proc_client_dev_deps_disp_ext_dp, // Node Dependency
      NPA_ARRAY_SIZE(pm_appsbl_proc_client_dev_deps_disp_ext_dp), // Deps Count & Deps Node Dependency Count
   },
   {
      PMIC_NPA_GROUP_ID_DISP_PRIM, // Resource Name
      PMIC_NPA_MODE_ID_GENERIC_MAX - 1, // Maximum Value
      NPA_RESOURCE_SINGLE_CLIENT, // Resource Attribute
      (void*) pm_pam_disp_prim_rails_info, // Resource User Data
      PMIC_NPA_CLIENT_NODE_DISP_PRIM, // Node Name
      NPA_NODE_DEFAULT, // Node Attributes
      NULL,
      pm_appsbl_proc_client_dev_deps_disp_prim, // Node Dependency
      NPA_ARRAY_SIZE(pm_appsbl_proc_client_dev_deps_disp_prim), // Deps Count & Deps Node Dependency Count
   },
   {
      PMIC_NPA_GROUP_ID_DISP_PRIM_AMOLED, // Resource Name
      PMIC_NPA_MODE_ID_GENERIC_MAX - 1, // Maximum Value
      NPA_RESOURCE_SINGLE_CLIENT, // Resource Attribute
      (void*) pm_pam_disp_prim_amoled_rails_info, // Resource User Data
      PMIC_NPA_CLIENT_NODE_DISP_PRIM_AMOLED, // Node Name
      NPA_NODE_DEFAULT, // Node Attributes
      NULL,
      pm_appsbl_proc_client_dev_deps_disp_prim_amoled, // Node Dependency
      NPA_ARRAY_SIZE(pm_appsbl_proc_client_dev_deps_disp_prim_amoled), // Deps Count & Deps Node Dependency Count
   },
   {
      PMIC_NPA_GROUP_ID_EMMC, // Resource Name
      PMIC_NPA_GROUP_ID_eMMC_MAX - 1, // Maximum Value
      NPA_RESOURCE_SINGLE_CLIENT, // Resource Attribute
      (void*) pm_pam_emmc_rails_info, // Resource User Data
      PMIC_NPA_CLIENT_NODE_EMMC, // Node Name
      NPA_NODE_DEFAULT, // Node Attributes
      NULL,
      pm_appsbl_proc_client_dev_deps_emmc, // Node Dependency
      NPA_ARRAY_SIZE(pm_appsbl_proc_client_dev_deps_emmc), // Deps Count & Deps Node Dependency Count
   },
   {
      PMIC_NPA_GROUP_ID_USB_SS1, // Resource Name
      PMIC_NPA_MODE_ID_USB_MAX - 1, // Maximum Value
      NPA_RESOURCE_SINGLE_CLIENT, // Resource Attribute
      (void*) pm_pam_usb_ss1_rails_info, // Resource User Data
      PMIC_NPA_CLIENT_NODE_USB_SS1, // Node Name
      NPA_NODE_DEFAULT, // Node Attributes
      NULL,
      pm_appsbl_proc_client_dev_deps_usb_ss1, // Node Dependency
      NPA_ARRAY_SIZE(pm_appsbl_proc_client_dev_deps_usb_ss1), // Deps Count & Deps Node Dependency Count
   },
};

uint32 num_of_pm_appsbl_nodes [] = { 5 };


pm_npa_remote_name_type
pmic_npa_ldo_remote_resources [] =
{
   { PMIC_DEV_RSRC_NAME_VEC_IN( A, ldo, 1), "ldoa\x01\x00\x00\x00"    },
   { PMIC_DEV_RSRC_NAME_VEC_IN( A, ldo, 11), "ldoa\x0B\x00\x00\x00"    },
   { PMIC_DEV_RSRC_NAME_VEC_IN( A, ldo, 13), "ldoa\x0D\x00\x00\x00"    },
   { PMIC_DEV_RSRC_NAME_VEC_IN( B, ldo, 1), "ldob\x01\x00\x00\x00"    },
   { PMIC_DEV_RSRC_NAME_VEC_IN( B, ldo, 2), "ldob\x02\x00\x00\x00"    },
   { PMIC_DEV_RSRC_NAME_VEC_IN( B, ldo, 4), "ldob\x04\x00\x00\x00"    },
   { PMIC_DEV_RSRC_NAME_VEC_IN( B, ldo, 5), "ldob\x05\x00\x00\x00"    },
   { PMIC_DEV_RSRC_NAME_VEC_IN( B, ldo, 6), "ldob\x06\x00\x00\x00"    },
   { PMIC_DEV_RSRC_NAME_VEC_IN( B, ldo, 7), "ldob\x07\x00\x00\x00"    },
};

pm_npa_remote_resource_type
pmic_npa_remote_ldo [1] = 
{
   {
      pmic_npa_ldo_remote_resources,
      9
   }
};
