/*! \file  pm_config_appsbl_npa_pam.c
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

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Settings/PMIC/core/pm_config_appsbl_npa_pam.c#5 $ 
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
#include "pm_appsbl_proc_npa_device.h"
/*===========================================================================

                        VARIABLES DEFINITION

===========================================================================*/

/* DISP_EXT_DP Client */
pm_npa_ldo_kvps
pm_pam_disp_ext_dp_b_ldo1 [] =
{
   // Mode: PMIC_NPA_MODE_ID_GENERIC_STANDBY
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
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
   // Mode: PMIC_NPA_MODE_ID_GENERIC_ACTIVE
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__NPM,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      PM_NPA_KEY_MICRO_VOLT, 4, 880000,  /**< [X uV] -> max aggregation. */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> summed aggregation. */
      PM_NPA_KEY_HEAD_ROOM, 4, 0,  /**< [X uV] -> voltage headroom needed. */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_ACTIVE_FLOOR, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
};
pm_npa_ldo_kvps
pm_pam_disp_ext_dp_a_ldo1 [] =
{
   // Mode: PMIC_NPA_MODE_ID_GENERIC_STANDBY
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
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
   // Mode: PMIC_NPA_MODE_ID_GENERIC_ACTIVE
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__NPM,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      PM_NPA_KEY_MICRO_VOLT, 4, 880000,  /**< [X uV] -> max aggregation. */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> summed aggregation. */
      PM_NPA_KEY_HEAD_ROOM, 4, 0,  /**< [X uV] -> voltage headroom needed. */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_ACTIVE_FLOOR, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
};

pm_npa_pam_client_cfg_type
pm_pam_disp_ext_dp_rails_info [] =
{
   {
      (void*)pm_pam_disp_ext_dp_b_ldo1,
      PM_NPA_VREG_LDO
   },
   {
      (void*)pm_pam_disp_ext_dp_a_ldo1,
      PM_NPA_VREG_LDO
   },
};
/* DISP_PRIM Client */
pm_npa_ldo_kvps
pm_pam_disp_prim_b_ldo1 [] =
{
   // Mode: PMIC_NPA_MODE_ID_GENERIC_STANDBY
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
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
   // Mode: PMIC_NPA_MODE_ID_GENERIC_ACTIVE
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__NPM,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      PM_NPA_KEY_MICRO_VOLT, 4, 880000,  /**< [X uV] -> max aggregation. */
      PM_NPA_KEY_CURRENT, 4, 76,  /**< [X mA] -> summed aggregation. */
      PM_NPA_KEY_HEAD_ROOM, 4, 0,  /**< [X uV] -> voltage headroom needed. */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_ACTIVE_FLOOR, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
};
pm_npa_ldo_kvps
pm_pam_disp_prim_a_ldo1 [] =
{
   // Mode: PMIC_NPA_MODE_ID_GENERIC_STANDBY
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
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
   // Mode: PMIC_NPA_MODE_ID_GENERIC_ACTIVE
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__NPM,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      PM_NPA_KEY_MICRO_VOLT, 4, 880000,  /**< [X uV] -> max aggregation. */
      PM_NPA_KEY_CURRENT, 4, 76,  /**< [X mA] -> summed aggregation. */
      PM_NPA_KEY_HEAD_ROOM, 4, 0,  /**< [X uV] -> voltage headroom needed. */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_ACTIVE_FLOOR, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
};
pm_npa_ldo_kvps
pm_pam_disp_prim_a_ldo11 [] =
{
   // Mode: PMIC_NPA_MODE_ID_GENERIC_STANDBY
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
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
   // Mode: PMIC_NPA_MODE_ID_GENERIC_ACTIVE
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__NPM,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      PM_NPA_KEY_MICRO_VOLT, 4, 1800000,  /**< [X uV] -> max aggregation. */
      PM_NPA_KEY_CURRENT, 4, 62,  /**< [X mA] -> summed aggregation. */
      PM_NPA_KEY_HEAD_ROOM, 4, 0,  /**< [X uV] -> voltage headroom needed. */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
};
pm_npa_ldo_kvps
pm_pam_disp_prim_a_ldo13 [] =
{
   // Mode: PMIC_NPA_MODE_ID_GENERIC_STANDBY
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
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
   // Mode: PMIC_NPA_MODE_ID_GENERIC_ACTIVE
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__NPM,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      PM_NPA_KEY_MICRO_VOLT, 4, 1800000,  /**< [X uV] -> max aggregation. */
      PM_NPA_KEY_CURRENT, 4, 225,  /**< [X mA] -> summed aggregation. */
      PM_NPA_KEY_HEAD_ROOM, 4, 0,  /**< [X uV] -> voltage headroom needed. */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
};

pm_npa_pam_client_cfg_type
pm_pam_disp_prim_rails_info [] =
{
   {
      (void*)pm_pam_disp_prim_b_ldo1,
      PM_NPA_VREG_LDO
   },
   {
      (void*)pm_pam_disp_prim_a_ldo1,
      PM_NPA_VREG_LDO
   },
   {
      (void*)pm_pam_disp_prim_a_ldo11,
      PM_NPA_VREG_LDO
   },
   {
      (void*)pm_pam_disp_prim_a_ldo13,
      PM_NPA_VREG_LDO
   },
};
/* DISP_PRIM_AMOLED Client */
pm_npa_ldo_kvps
pm_pam_disp_prim_amoled_b_ldo1 [] =
{
   // Mode: PMIC_NPA_MODE_ID_GENERIC_STANDBY
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
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
   // Mode: PMIC_NPA_MODE_ID_GENERIC_ACTIVE
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__NPM,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      PM_NPA_KEY_MICRO_VOLT, 4, 880000,  /**< [X uV] -> max aggregation. */
      PM_NPA_KEY_CURRENT, 4, 76,  /**< [X mA] -> summed aggregation. */
      PM_NPA_KEY_HEAD_ROOM, 4, 0,  /**< [X uV] -> voltage headroom needed. */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
};
pm_npa_ldo_kvps
pm_pam_disp_prim_amoled_b_ldo6 [] =
{
   // Mode: PMIC_NPA_MODE_ID_GENERIC_STANDBY
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
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
   // Mode: PMIC_NPA_MODE_ID_GENERIC_ACTIVE
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__NPM,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      PM_NPA_KEY_MICRO_VOLT, 4, 3300000,  /**< [X uV] -> max aggregation. */
      PM_NPA_KEY_CURRENT, 4, 14,  /**< [X mA] -> summed aggregation. */
      PM_NPA_KEY_HEAD_ROOM, 4, 0,  /**< [X uV] -> voltage headroom needed. */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
};
pm_npa_ldo_kvps
pm_pam_disp_prim_amoled_a_ldo1 [] =
{
   // Mode: PMIC_NPA_MODE_ID_GENERIC_STANDBY
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
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
   // Mode: PMIC_NPA_MODE_ID_GENERIC_ACTIVE
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__NPM,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      PM_NPA_KEY_MICRO_VOLT, 4, 880000,  /**< [X uV] -> max aggregation. */
      PM_NPA_KEY_CURRENT, 4, 76,  /**< [X mA] -> summed aggregation. */
      PM_NPA_KEY_HEAD_ROOM, 4, 0,  /**< [X uV] -> voltage headroom needed. */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
};
pm_npa_ldo_kvps
pm_pam_disp_prim_amoled_a_ldo13 [] =
{
   // Mode: PMIC_NPA_MODE_ID_GENERIC_STANDBY
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
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
   // Mode: PMIC_NPA_MODE_ID_GENERIC_ACTIVE
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__NPM,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      PM_NPA_KEY_MICRO_VOLT, 4, 1800000,  /**< [X uV] -> max aggregation. */
      PM_NPA_KEY_CURRENT, 4, 225,  /**< [X mA] -> summed aggregation. */
      PM_NPA_KEY_HEAD_ROOM, 4, 0,  /**< [X uV] -> voltage headroom needed. */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
};

pm_npa_pam_client_cfg_type
pm_pam_disp_prim_amoled_rails_info [] =
{
   {
      (void*)pm_pam_disp_prim_amoled_b_ldo1,
      PM_NPA_VREG_LDO
   },
   {
      (void*)pm_pam_disp_prim_amoled_b_ldo6,
      PM_NPA_VREG_LDO
   },
   {
      (void*)pm_pam_disp_prim_amoled_a_ldo1,
      PM_NPA_VREG_LDO
   },
   {
      (void*)pm_pam_disp_prim_amoled_a_ldo13,
      PM_NPA_VREG_LDO
   },
};
/* EMMC Client */
pm_npa_ldo_kvps
pm_pam_emmc_b_ldo2 [] =
{
   // Mode: PMIC_NPA_GROUP_ID_eMMC_OFF
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
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
   // Mode: PMIC_NPA_GROUP_ID_eMMC_ACTIVE
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__IPEAK,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      PM_NPA_KEY_MICRO_VOLT, 4, 2960000,  /**< [X uV] -> max aggregation. */
      PM_NPA_KEY_CURRENT, 4, 100,  /**< [X mA] -> summed aggregation. */
      PM_NPA_KEY_HEAD_ROOM, 4, 0,  /**< [X uV] -> voltage headroom needed. */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_ACTIVE_FLOOR, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
   // Mode: PMIC_NPA_GROUP_ID_eMMC_SLEEP
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_DISABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__IPEAK,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      PM_NPA_KEY_MICRO_VOLT, 4, 2950000,  /**< [X uV] -> max aggregation. */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> summed aggregation. */
      PM_NPA_KEY_HEAD_ROOM, 4, 0,  /**< [X uV] -> voltage headroom needed. */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_ACTIVE_FLOOR, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
};
pm_npa_ldo_kvps
pm_pam_emmc_b_ldo4 [] =
{
   // Mode: PMIC_NPA_GROUP_ID_eMMC_OFF
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
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
   // Mode: PMIC_NPA_GROUP_ID_eMMC_ACTIVE
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__NPM,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      PM_NPA_KEY_MICRO_VOLT, 4, 2960000,  /**< [X uV] -> max aggregation. */
      PM_NPA_KEY_CURRENT, 4, 100,  /**< [X mA] -> summed aggregation. */
      PM_NPA_KEY_HEAD_ROOM, 4, 0,  /**< [X uV] -> voltage headroom needed. */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_ACTIVE_FLOOR, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
   // Mode: PMIC_NPA_GROUP_ID_eMMC_SLEEP
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_DISABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__IPEAK,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      PM_NPA_KEY_MICRO_VOLT, 4, 2950000,  /**< [X uV] -> max aggregation. */
      PM_NPA_KEY_CURRENT, 4, 1,  /**< [X mA] -> summed aggregation. */
      PM_NPA_KEY_HEAD_ROOM, 4, 0,  /**< [X uV] -> voltage headroom needed. */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_ACTIVE_FLOOR, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
};
pm_npa_ldo_kvps
pm_pam_emmc_b_ldo5 [] =
{
   // Mode: PMIC_NPA_GROUP_ID_eMMC_OFF
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
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
   // Mode: PMIC_NPA_GROUP_ID_eMMC_ACTIVE
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__IPEAK,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      PM_NPA_KEY_MICRO_VOLT, 4, 2950000,  /**< [X uV] -> max aggregation. */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> summed aggregation. */
      PM_NPA_KEY_HEAD_ROOM, 4, 0,  /**< [X uV] -> voltage headroom needed. */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_ACTIVE_FLOOR, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
   // Mode: PMIC_NPA_GROUP_ID_eMMC_SLEEP
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_DISABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__IPEAK,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      PM_NPA_KEY_MICRO_VOLT, 4, 2950000,  /**< [X uV] -> max aggregation. */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> summed aggregation. */
      PM_NPA_KEY_HEAD_ROOM, 4, 0,  /**< [X uV] -> voltage headroom needed. */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_ACTIVE_FLOOR, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
};

pm_npa_pam_client_cfg_type
pm_pam_emmc_rails_info [] =
{
   {
      (void*)pm_pam_emmc_b_ldo2,
      PM_NPA_VREG_LDO
   },
   {
      (void*)pm_pam_emmc_b_ldo4,
      PM_NPA_VREG_LDO
   },
   {
      (void*)pm_pam_emmc_b_ldo5,
      PM_NPA_VREG_LDO
   },
};
/* USB_SS1 Client */
pm_npa_ldo_kvps
pm_pam_usb_ss1_b_ldo1 [] =
{
   // Mode: PMIC_NPA_MODE_ID_USB_OFF
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
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
   // Mode: PMIC_NPA_MODE_ID_USB_PERPH_SUSPEND
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
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
   // Mode: PMIC_NPA_MODE_ID_USB_PERPH_ACTIVE
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__NPM,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      PM_NPA_KEY_MICRO_VOLT, 4, 880000,  /**< [X uV] -> max aggregation. */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> summed aggregation. */
      PM_NPA_KEY_HEAD_ROOM, 4, 0,  /**< [X uV] -> voltage headroom needed. */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_ACTIVE_FLOOR, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
   // Mode: PMIC_NPA_MODE_ID_USB_HOST_SUSPEND
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
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
   // Mode: PMIC_NPA_MODE_ID_USB_HOST_ACTIVE
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
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
};
pm_npa_ldo_kvps
pm_pam_usb_ss1_b_ldo7 [] =
{
   // Mode: PMIC_NPA_MODE_ID_USB_OFF
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
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
   // Mode: PMIC_NPA_MODE_ID_USB_PERPH_SUSPEND
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_DISABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__IPEAK,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      PM_NPA_KEY_MICRO_VOLT, 4, 0,  /**< [X uV] -> max aggregation. */
      PM_NPA_KEY_CURRENT, 4, 1,  /**< [X mA] -> summed aggregation. */
      PM_NPA_KEY_HEAD_ROOM, 4, 0,  /**< [X uV] -> voltage headroom needed. */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_ACTIVE_FLOOR, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
   // Mode: PMIC_NPA_MODE_ID_USB_PERPH_ACTIVE
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__NPM,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      PM_NPA_KEY_MICRO_VOLT, 4, 3075000,  /**< [X uV] -> max aggregation. */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> summed aggregation. */
      PM_NPA_KEY_HEAD_ROOM, 4, 0,  /**< [X uV] -> voltage headroom needed. */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_ACTIVE_FLOOR, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
   // Mode: PMIC_NPA_MODE_ID_USB_HOST_SUSPEND
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
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
   // Mode: PMIC_NPA_MODE_ID_USB_HOST_ACTIVE
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_DISABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__NPM,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      PM_NPA_KEY_MICRO_VOLT, 4, 0,  /**< [X uV] -> max aggregation. */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> summed aggregation. */
      PM_NPA_KEY_HEAD_ROOM, 4, 0,  /**< [X uV] -> voltage headroom needed. */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_ACTIVE_FLOOR, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
};
pm_npa_ldo_kvps
pm_pam_usb_ss1_a_ldo1 [] =
{
   // Mode: PMIC_NPA_MODE_ID_USB_OFF
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
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
   // Mode: PMIC_NPA_MODE_ID_USB_PERPH_SUSPEND
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
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
   // Mode: PMIC_NPA_MODE_ID_USB_PERPH_ACTIVE
   {
      PM_NPA_KEY_SOFTWARE_ENABLE, 4, PM_NPA_GENERIC_ENABLE,  /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_KEY_LDO_SOFTWARE_MODE, 4, PM_NPA_SW_MODE_LDO__NPM,  /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_KEY_PIN_CTRL_ENABLE, 4, PM_NPA_PIN_CONTROL_ENABLE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_KEY_PIN_CTRL_POWER_MODE, 4, PM_NPA_PIN_CONTROL_POWER_MODE__NONE,  /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      PM_NPA_KEY_MICRO_VOLT, 4, 880000,  /**< [X uV] -> max aggregation. */
      PM_NPA_KEY_CURRENT, 4, 0,  /**< [X mA] -> summed aggregation. */
      PM_NPA_KEY_HEAD_ROOM, 4, 0,  /**< [X uV] -> voltage headroom needed. */
      PM_NPA_KEY_BYPASS_ALLOWED_KEY, 4, PM_NPA_BYPASS_ALLOWED,  /**< [Allowed (default), Disallowed] */
      PM_NPA_KEY_CORNER_LEVEL_KEY, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_ACTIVE_FLOOR, 4, PM_NPA_CORNER_MODE__NONE,  /**< [None, Level1 (Retention), Level2, Level3, Level4, Level5, Level6 (SuperTurbo), Not Used] */
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
   // Mode: PMIC_NPA_MODE_ID_USB_HOST_SUSPEND
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
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
   // Mode: PMIC_NPA_MODE_ID_USB_HOST_ACTIVE
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
      PM_NPA_KEY_CORNER_VOLT_LEVEL, 4, 0,  /**< Corner voltage */
      PM_NPA_KEY_CORNER_VOLT_LEVEL_FLOOR, 4, 0,  /**< Corner Voltage Floor */
   },
};

pm_npa_pam_client_cfg_type
pm_pam_usb_ss1_rails_info [] =
{
   {
      (void*)pm_pam_usb_ss1_b_ldo1,
      PM_NPA_VREG_LDO
   },
   {
      (void*)pm_pam_usb_ss1_b_ldo7,
      PM_NPA_VREG_LDO
   },
   {
      (void*)pm_pam_usb_ss1_a_ldo1,
      PM_NPA_VREG_LDO
   },
};
