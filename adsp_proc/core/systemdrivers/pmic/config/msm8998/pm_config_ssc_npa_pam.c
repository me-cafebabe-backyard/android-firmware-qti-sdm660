/*! \file  pm_config_ssc_npa_pam.c
 *  
 *  \brief  File Contains the PMIC NPA CMI Code
 *  \details  This file contains the needed definition and enum for PMIC NPA layer.
 *  
 *    PMIC code generation Version: 1.0.0.0
 *    PMIC code generation Locked Version: SSC_MSM8998_PMI8998_0p2 - LOCKED

 *    This file contains code for Target specific settings and modes.
 *  
 *  &copy; Copyright 2014 Qualcomm Technologies, All Rights Reserved
 */
/*===========================================================================

                EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module over time.

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/pmic/config/msm8998/pm_config_ssc_npa_pam.c#1 $ 
$DateTime: 2020/02/10 01:57:30 $  $Author: pwbldsvc $

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 

===========================================================================*/

/*===========================================================================

                        INCLUDE HEADER FILES

===========================================================================*/

#include "pm_npa.h"
#include "pmapp_npa.h"
#include "pm_npa_device.h"
#include "npa_remote_resource.h"

#include "pm_npa_device_clk_buff.h"
#include "pm_npa_device_ldo.h"
#include "pm_npa_device_smps.h"
#include "pm_npa_device_ncp.h"
#include "pm_npa_device_vs.h"

#include "pm_ssc_proc_npa.h"
#include "pm_ssc_proc_npa_device.h"

/*===========================================================================

                        VARIABLES DEFINITION

===========================================================================*/

/* SENSOR_VDD Client */
pm_npa_ldo_kvps
pm_pam_sensor_vdd_a_ldo19 [] =
{
   // Mode: PMIC_NPA_MODE_ID_SENSOR_POWER_OFF
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_DISABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__IPEAK,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      PM_NPA_KEY_MICRO_VOLT, 4, 0,  /**< [X uV] -> max aggregation. */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> summed aggregation. */
      PM_NPA_KEY_HEAD_ROOM, 4, 0,  /**< [X uV] -> voltage headroom needed. */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_ACTIVE_FLOOR, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
   },
   // Mode: PMIC_NPA_MODE_ID_SENSOR_LPM
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__IPEAK,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      PM_NPA_KEY_MICRO_VOLT, 4, 3008000,  /**< [X uV] -> max aggregation. */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> summed aggregation. */
      PM_NPA_KEY_HEAD_ROOM, 4, 0,  /**< [X uV] -> voltage headroom needed. */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_DISALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_ACTIVE_FLOOR, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
   },
   // Mode: PMIC_NPA_MODE_ID_SENSOR_POWER_ON
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__NPM,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      PM_NPA_KEY_MICRO_VOLT, 4, 3008000,  /**< [X uV] -> max aggregation. */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> summed aggregation. */
      PM_NPA_KEY_HEAD_ROOM, 4, 0,  /**< [X uV] -> voltage headroom needed. */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_DISALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_ACTIVE_FLOOR, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
   },
};

pm_npa_pam_client_cfg_type
pm_pam_sensor_vdd_rails_info [] =
{
   {
      (void*)pm_pam_sensor_vdd_a_ldo19,
      PM_NPA_VREG_LDO
   },
};

/* SENSOR_VDD_2 Client */
pm_npa_ldo_kvps
pm_pam_sensor_vdd_2_a_ldo1 [] =
{
   // Mode: PMIC_NPA_MODE_ID_SENSOR_POWER_OFF
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_DISABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__IPEAK,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      PM_NPA_KEY_MICRO_VOLT, 4, 0,  /**< [X uV] -> max aggregation. */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> summed aggregation. */
      PM_NPA_KEY_HEAD_ROOM, 4, 0,  /**< [X uV] -> voltage headroom needed. */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_ACTIVE_FLOOR, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
   },
   // Mode: PMIC_NPA_MODE_ID_SENSOR_LPM
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__IPEAK,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      PM_NPA_KEY_MICRO_VOLT, 4, 3008000,  /**< [X uV] -> max aggregation. */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> summed aggregation. */
      PM_NPA_KEY_HEAD_ROOM, 4, 0,  /**< [X uV] -> voltage headroom needed. */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_ACTIVE_FLOOR, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
   },
   // Mode: PMIC_NPA_MODE_ID_SENSOR_POWER_ON
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__NPM,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      PM_NPA_KEY_MICRO_VOLT, 4, 3008000,  /**< [X uV] -> max aggregation. */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> summed aggregation. */
      PM_NPA_KEY_HEAD_ROOM, 4, 0,  /**< [X uV] -> voltage headroom needed. */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_ACTIVE_FLOOR, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
   },
};

pm_npa_pam_client_cfg_type
pm_pam_sensor_vdd_2_rails_info [] =
{
   {
      (void*)pm_pam_sensor_vdd_2_a_ldo1,
      PM_NPA_VREG_LDO
   } ,
};

/* SENSOR_VDDIO Client */
pm_npa_vs_kvps
pm_pam_sensor_vddio_a_vs2 [] =
{
   // Mode: PMIC_NPA_MODE_ID_SENSOR_POWER_OFF
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_DISABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_KEY_MICRO_VOLT, 4, 0,  /**< [X uV] -> max aggregation. */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> summed aggregation. */
   },
   // Mode: PMIC_NPA_MODE_ID_SENSOR_LPM
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_KEY_MICRO_VOLT, 4, 1800000,  /**< [X uV] -> max aggregation. */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> summed aggregation. */
   },
   // Mode: PMIC_NPA_MODE_ID_SENSOR_POWER_ON
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_KEY_MICRO_VOLT, 4, 1800000,  /**< [X uV] -> max aggregation. */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> summed aggregation. */
   },
};

pm_npa_pam_client_cfg_type
pm_pam_sensor_vddio_rails_info [] =
{
   {
      (void*)pm_pam_sensor_vddio_a_vs2,
      PM_NPA_VREG_VS
   },
};

/* SENSOR_VDDIO_2 Client */
pm_npa_vs_kvps
pm_pam_sensor_vddio_2_a_vs2 [] =
{
   // Mode: PMIC_NPA_MODE_ID_SENSOR_POWER_OFF
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_DISABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_KEY_MICRO_VOLT, 4, 0,  /**< [X uV] -> max aggregation. */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> summed aggregation. */
   },
   // Mode: PMIC_NPA_MODE_ID_SENSOR_LPM
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_KEY_MICRO_VOLT, 4, 1800000,  /**< [X uV] -> max aggregation. */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> summed aggregation. */
   },
   // Mode: PMIC_NPA_MODE_ID_SENSOR_POWER_ON
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_KEY_MICRO_VOLT, 4, 1800000,  /**< [X uV] -> max aggregation. */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> summed aggregation. */
   },
};

pm_npa_pam_client_cfg_type
pm_pam_sensor_vddio_2_rails_info [] =
{
   {
      (void*)pm_pam_sensor_vddio_2_a_vs2,
      PM_NPA_VREG_VS
   },
};

/* start pm_config_ssc_npa_node_rsrcs.c  */

/*===========================================================================

                        MACRO DEFINITIONS

===========================================================================*/

#define PMIC_NPA_CLIENT_NODE_RAIL_SSC_CX "/node/pmic/client/rail_ssc_cx"
#define PMIC_NPA_CLIENT_NODE_RAIL_SSC_MX "/node/pmic/client/rail_ssc_mx"
#define PMIC_NPA_CLIENT_NODE_SENSOR_DSPS_PROXY "/node/pmic/client/sensor_dsp_proxy"
#define PMIC_NPA_CLIENT_NODE_SENSOR_VDD "/node/pmic/client/sensor_vdd"
#define PMIC_NPA_CLIENT_NODE_SENSOR_VDD_2 "/node/pmic/client/sensor_vdd_2"
#define PMIC_NPA_CLIENT_NODE_SENSOR_VDDIO "/node/pmic/client/sensor_vddio"
#define PMIC_NPA_CLIENT_NODE_SENSOR_VDDIO_2 "/node/pmic/client/sensor_vddio_2"
#define PMIC_NPA_CLIENT_NODE_RAIL_CX      "/node/pmic/client/rail_cx"


/*===========================================================================

                        VARIABLES DEFINITION

===========================================================================*/

/* NPA NODE DEPENDENCY */

/* SENSOR_VDD Client */
npa_node_dependency
pm_ssc_proc_client_dev_deps_sensor_vdd [] =
{
   PMIC_NPA_NODE_DEP_LIST( A, ldo, 19 ),
};

/* SENSOR_VDD_2 Client */
npa_node_dependency
pm_ssc_proc_client_dev_deps_sensor_vdd_2 [] =
{
   PMIC_NPA_NODE_DEP_LIST( A, ldo, 1 ),
};

/* SENSOR_VDDIO Client */
npa_node_dependency
pm_ssc_proc_client_dev_deps_sensor_vddio [] =
{
   PMIC_NPA_NODE_DEP_LIST( A, vs, 2 ),
};

/* SENSOR_VDDIO_2 Client */
npa_node_dependency
pm_ssc_proc_client_dev_deps_sensor_vddio_2 [] =
{
   PMIC_NPA_NODE_DEP_LIST( A, vs, 2 ),
};

/* NPA NODE RESOURCE */
pm_npa_node_resource_info
pm_npa_ssc_pam_node_rsrcs [] =
{
   {
      PMIC_NPA_GROUP_ID_SENSOR_VDD, // Resource Name
      PMIC_NPA_MODE_ID_SENSOR_MAX - 1, // Maximum Value
      NPA_RESOURCE_SINGLE_CLIENT, // Resource Attribute
      (void*) pm_pam_sensor_vdd_rails_info, // Resource User Data
      PMIC_NPA_CLIENT_NODE_SENSOR_VDD, // Node Name
      NPA_NODE_DEFAULT, // Node Attributes
      NULL,
      pm_ssc_proc_client_dev_deps_sensor_vdd, // Node Dependency
      NPA_ARRAY_SIZE(pm_ssc_proc_client_dev_deps_sensor_vdd), // Deps Count & Deps Node Dependency Count
      PM_NPA_PLUGIN_TYPE_IDENTITY,                              // Use Identity here.

   },
   {
      PMIC_NPA_GROUP_ID_SENSOR_VDD_2, // Resource Name
      PMIC_NPA_MODE_ID_SENSOR_MAX - 1, // Maximum Value
      NPA_RESOURCE_SINGLE_CLIENT, // Resource Attribute
      (void*) pm_pam_sensor_vdd_2_rails_info, // Resource User Data
      PMIC_NPA_CLIENT_NODE_SENSOR_VDD_2, // Node Name
      NPA_NODE_DEFAULT, // Node Attributes
      NULL,
      pm_ssc_proc_client_dev_deps_sensor_vdd_2, // Node Dependency
      NPA_ARRAY_SIZE(pm_ssc_proc_client_dev_deps_sensor_vdd_2), // Deps Count & Deps Node Dependency Count
      PM_NPA_PLUGIN_TYPE_IDENTITY,                                // Use Identity here.
   },
   {
      PMIC_NPA_GROUP_ID_SENSOR_VDDIO, // Resource Name
      PMIC_NPA_MODE_ID_SENSOR_MAX - 1, // Maximum Value
      NPA_RESOURCE_SINGLE_CLIENT, // Resource Attribute
      (void*) pm_pam_sensor_vddio_rails_info, // Resource User Data
      PMIC_NPA_CLIENT_NODE_SENSOR_VDDIO, // Node Name
      NPA_NODE_DEFAULT, // Node Attributes
      NULL,
      pm_ssc_proc_client_dev_deps_sensor_vddio, // Node Dependency
      NPA_ARRAY_SIZE(pm_ssc_proc_client_dev_deps_sensor_vddio), // Deps Count & Deps Node Dependency Count
      PM_NPA_PLUGIN_TYPE_IDENTITY,                             // Use Identity here.
   },
   {
      PMIC_NPA_GROUP_ID_SENSOR_VDDIO_2, // Resource Name
      PMIC_NPA_MODE_ID_SENSOR_MAX - 1, // Maximum Value
      NPA_RESOURCE_SINGLE_CLIENT, // Resource Attribute
      (void*) pm_pam_sensor_vddio_2_rails_info, // Resource User Data
      PMIC_NPA_CLIENT_NODE_SENSOR_VDDIO_2, // Node Name
      NPA_NODE_DEFAULT, // Node Attributes
      NULL,
      pm_ssc_proc_client_dev_deps_sensor_vddio_2, // Node Dependency
      NPA_ARRAY_SIZE(pm_ssc_proc_client_dev_deps_sensor_vddio_2), // Deps Count & Deps Node Dependency Count
      PM_NPA_PLUGIN_TYPE_IDENTITY,                                // Use Identity here.
   },
};

uint32 num_of_pm_ssc_nodes [] = { 4 };


pm_npa_remote_name_type
pmic_npa_ldo_remote_resources [] =
{
   { PMIC_DEV_RSRC_NAME_VEC_IN( A, ldo, 1), "ldoa\x01\x00\x00\x00"    },
   { PMIC_DEV_RSRC_NAME_VEC_IN( A, ldo, 19), "ldoa\x13\x00\x00\x00"    },
};

pm_npa_remote_resource_type
pmic_npa_remote_ldo [1] = 
{
   {
      pmic_npa_ldo_remote_resources,
      2
   }
};

pm_npa_remote_name_type
pmic_npa_vs_remote_resources [] =
{
   { PMIC_DEV_RSRC_NAME_VEC_IN( A, vs, 2), "vsa\x00\x02\x00\x00\x00"    },
};

pm_npa_remote_resource_type
pmic_npa_remote_vs [1] = 
{
   {
      pmic_npa_vs_remote_resources,
      1
   }
};

/* end pm_config_ssc_npa_node_rsrcs.c  */

/* Published resource */
static char *pmic_publish_resources[] =
{
   PMIC_NPA_GROUP_ID_SENSOR_VDD,
   PMIC_NPA_GROUP_ID_SENSOR_VDD_2,
   PMIC_NPA_GROUP_ID_SENSOR_VDDIO,
   PMIC_NPA_GROUP_ID_SENSOR_VDDIO_2
};

pm_npa_resource_publish_type npa_pub_type = 
{
   SENSOR_PD,
   pmic_publish_resources,
   4
};

/* Published resource */

