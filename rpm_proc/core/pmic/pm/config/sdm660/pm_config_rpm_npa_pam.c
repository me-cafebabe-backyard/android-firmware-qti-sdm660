/*! \file  pm_config_rpm_npa_pam.c
 *  
 *  \brief  File Contains the PMIC NPA CMI Code
 *  \details  This file contains the needed definition and enum for PMIC NPA layer.
 *  
 *    PMIC code generation Version: 1.0.0.0
 *    PMIC code generation Locked Version: RPM_SMD660_PM660_0p3 - LOCKED

=============================================================================

                      THIS NPA SW LABEL IS UNLOCKED
    DO NOT SUBMIT THIS GENERATED FILE TO P4 BY REMOVING THIS SECTION!!!

=============================================================================


 *    This file contains code for Target specific settings and modes.
 *  
 *  &copy; Copyright 2016 Qualcomm Technologies, All Rights Reserved
 */

/*===========================================================================

                EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module over time.

$Header: //components/rel/rpm.bf/1.8/core/pmic/pm/config/sdm660/pm_config_rpm_npa_pam.c#4 $ 
$DateTime: 2017/03/10 08:02:29 $  $Author: asuthar 

$when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
03/10/17   as      Removed pc_enable LDO1A vote (CR2017297)

===========================================================================*/

/*===========================================================================

                        INCLUDE HEADER FILES

===========================================================================*/

#include "pm_npa_device_ldo.h"
#include "pm_npa_device_smps.h"
#include "pm_npa.h"
#include "pm_rpm_npa.h"
#include "pm_rpm_npa_device.h"
/*===========================================================================

                        VARIABLES DEFINITION

===========================================================================*/

/* DDR Client */
static pm_npa_ldo_int_rep
pm_rpm_pam_ddr_b_ldo1 [] =
{
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_0 */
   /**< Comments: No Activity */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_LDO__IPEAK, /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      1, /**< Perpherial Index */
      1, /**< Primary (0) or Secondary (1) PMIC */
      0, /**< If((old sw_en == disable) && (new sw_en == enable) || new pc_en == enable then ldo_en_trans = true else ldo_en_trans = false */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed]*/
      0, /**< reserve 1 - for 32 bit boundary */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      0, /**< [X uV] -> voltage headroom needed. */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_1 */
   /**< Comments: <=200 */
   {
      PM_NPA_GENERIC_ENABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_LDO__NPM, /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      1, /**< Perpherial Index */
      1, /**< Primary (0) or Secondary (1) PMIC */
      0, /**< If((old sw_en == disable) && (new sw_en == enable) || new pc_en == enable then ldo_en_trans = true else ldo_en_trans = false */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed]*/
      0, /**< reserve 1 - for 32 bit boundary */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      0, /**< [X uV] -> voltage headroom needed. */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_2 */
   /**< Comments: 201 - 300 */
   {
      PM_NPA_GENERIC_ENABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_LDO__NPM, /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      1, /**< Perpherial Index */
      1, /**< Primary (0) or Secondary (1) PMIC */
      0, /**< If((old sw_en == disable) && (new sw_en == enable) || new pc_en == enable then ldo_en_trans = true else ldo_en_trans = false */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed]*/
      0, /**< reserve 1 - for 32 bit boundary */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      0, /**< [X uV] -> voltage headroom needed. */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_3 */
   /**< Comments: 301 - 412.8 */
   {
      PM_NPA_GENERIC_ENABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_LDO__NPM, /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      1, /**< Perpherial Index */
      1, /**< Primary (0) or Secondary (1) PMIC */
      0, /**< If((old sw_en == disable) && (new sw_en == enable) || new pc_en == enable then ldo_en_trans = true else ldo_en_trans = false */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed]*/
      0, /**< reserve 1 - for 32 bit boundary */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      0, /**< [X uV] -> voltage headroom needed. */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_4 */
   /**< Comments: 413 - 547.2 */
   {
      PM_NPA_GENERIC_ENABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_LDO__NPM, /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      1, /**< Perpherial Index */
      1, /**< Primary (0) or Secondary (1) PMIC */
      0, /**< If((old sw_en == disable) && (new sw_en == enable) || new pc_en == enable then ldo_en_trans = true else ldo_en_trans = false */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed]*/
      0, /**< reserve 1 - for 32 bit boundary */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      0, /**< [X uV] -> voltage headroom needed. */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_5 */
   /**< Comments: 548 - 681.6 */
   {
      PM_NPA_GENERIC_ENABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_LDO__NPM, /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      1, /**< Perpherial Index */
      1, /**< Primary (0) or Secondary (1) PMIC */
      0, /**< If((old sw_en == disable) && (new sw_en == enable) || new pc_en == enable then ldo_en_trans = true else ldo_en_trans = false */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed]*/
      0, /**< reserve 1 - for 32 bit boundary */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      0, /**< [X uV] -> voltage headroom needed. */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_6 */
   /**< Comments: 682 - 768.0 */
   {
      PM_NPA_GENERIC_ENABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_LDO__NPM, /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      1, /**< Perpherial Index */
      1, /**< Primary (0) or Secondary (1) PMIC */
      0, /**< If((old sw_en == disable) && (new sw_en == enable) || new pc_en == enable then ldo_en_trans = true else ldo_en_trans = false */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed]*/
      0, /**< reserve 1 - for 32 bit boundary */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      0, /**< [X uV] -> voltage headroom needed. */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_7 */
   /**< Comments: 769 - 1017.6 */
   {
      PM_NPA_GENERIC_ENABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_LDO__NPM, /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      1, /**< Perpherial Index */
      1, /**< Primary (0) or Secondary (1) PMIC */
      0, /**< If((old sw_en == disable) && (new sw_en == enable) || new pc_en == enable then ldo_en_trans = true else ldo_en_trans = false */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed]*/
      0, /**< reserve 1 - for 32 bit boundary */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      0, /**< [X uV] -> voltage headroom needed. */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_8 */
   /**< Comments: 1018 - 1296.0 */
   {
      PM_NPA_GENERIC_ENABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_LDO__NPM, /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      1, /**< Perpherial Index */
      1, /**< Primary (0) or Secondary (1) PMIC */
      0, /**< If((old sw_en == disable) && (new sw_en == enable) || new pc_en == enable then ldo_en_trans = true else ldo_en_trans = false */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed]*/
      0, /**< reserve 1 - for 32 bit boundary */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      0, /**< [X uV] -> voltage headroom needed. */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_9 */
   /**< Comments: 1226  - 1353.6 */
   {
      PM_NPA_GENERIC_ENABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_LDO__NPM, /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      1, /**< Perpherial Index */
      1, /**< Primary (0) or Secondary (1) PMIC */
      0, /**< If((old sw_en == disable) && (new sw_en == enable) || new pc_en == enable then ldo_en_trans = true else ldo_en_trans = false */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed]*/
      0, /**< reserve 1 - for 32 bit boundary */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      0, /**< [X uV] -> voltage headroom needed. */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_10 */
   /**< Comments: 1354 - 1555.2 */
   {
      PM_NPA_GENERIC_ENABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_LDO__NPM, /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      1, /**< Perpherial Index */
      1, /**< Primary (0) or Secondary (1) PMIC */
      0, /**< If((old sw_en == disable) && (new sw_en == enable) || new pc_en == enable then ldo_en_trans = true else ldo_en_trans = false */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed]*/
      0, /**< reserve 1 - for 32 bit boundary */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      0, /**< [X uV] -> voltage headroom needed. */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_11 */
   /**< Comments: 1556 - 1804.8 */
   {
      PM_NPA_GENERIC_ENABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_LDO__NPM, /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      1, /**< Perpherial Index */
      1, /**< Primary (0) or Secondary (1) PMIC */
      0, /**< If((old sw_en == disable) && (new sw_en == enable) || new pc_en == enable then ldo_en_trans = true else ldo_en_trans = false */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed]*/
      0, /**< reserve 1 - for 32 bit boundary */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      0, /**< [X uV] -> voltage headroom needed. */
   },
};
static pm_npa_smps_int_rep
pm_rpm_pam_ddr_b_smps1 [] =
{
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_0 */
   /**< Comments: No Activity */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__AUTO, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_1 */
   /**< Comments: <=200 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__AUTO, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_2 */
   /**< Comments: 201 - 300 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__AUTO, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_3 */
   /**< Comments: 301 - 412.8 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__AUTO, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_4 */
   /**< Comments: 413 - 547.2 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__AUTO, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_5 */
   /**< Comments: 548 - 681.6 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__NPM, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_6 */
   /**< Comments: 682 - 768.0 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__NPM, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_7 */
   /**< Comments: 769 - 1017.6 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__NPM, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_8 */
   /**< Comments: 1018 - 1296.0 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__NPM, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_9 */
   /**< Comments: 1226  - 1353.6 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__NPM, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_10 */
   /**< Comments: 1354 - 1555.2 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__NPM, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_11 */
   /**< Comments: 1556 - 1804.8 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__NPM, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
};
static pm_npa_smps_int_rep
pm_rpm_pam_ddr_b_smps3 [] =
{
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_0 */
   /**< Comments: No Activity */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__AUTO, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_1 */
   /**< Comments: <=200 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__AUTO, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_2 */
   /**< Comments: 201 - 300 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__AUTO, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_3 */
   /**< Comments: 301 - 412.8 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__AUTO, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_4 */
   /**< Comments: 413 - 547.2 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__AUTO, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */      
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_5 */
   /**< Comments: 548 - 681.6 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__NPM, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_6 */
   /**< Comments: 682 - 768.0 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__NPM, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_7 */
   /**< Comments: 769 - 1017.6 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__NPM, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_8 */
   /**< Comments: 1018 - 1296.0 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__NPM, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_9 */
   /**< Comments: 1226  - 1353.6 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__NPM, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_10 */
   /**< Comments: 1354 - 1555.2 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__NPM, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_11 */
   /**< Comments: 1556 - 1804.8 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__NPM, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
};
static pm_npa_smps_int_rep
pm_rpm_pam_ddr_b_smps5 [] =
{
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_0 */
   /**< Comments: No Activity */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__AUTO, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_1 */
   /**< Comments: <=200 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__AUTO, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_2 */
   /**< Comments: 201 - 300 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__AUTO, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_3 */
   /**< Comments: 301 - 412.8 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__AUTO, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_4 */
   /**< Comments: 413 - 547.2 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__AUTO, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_5 */
   /**< Comments: 548 - 681.6 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__NPM, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_6 */
   /**< Comments: 682 - 768.0 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__NPM, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_7 */
   /**< Comments: 769 - 1017.6 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__NPM, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_8 */
   /**< Comments: 1018 - 1296.0 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__NPM, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_9 */
   /**< Comments: 1226  - 1353.6 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__NPM, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_10 */
   /**< Comments: 1354 - 1555.2 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__NPM, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_11 */
   /**< Comments: 1556 - 1804.8 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__NPM, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
};
static pm_npa_ldo_int_rep
pm_rpm_pam_ddr_a_ldo1 [] =
{
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_0 */
   /**< Comments: No Activity */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_LDO__IPEAK, /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      1, /**< Perpherial Index */
      0, /**< Primary (0) or Secondary (1) PMIC */
      0, /**< If((old sw_en == disable) && (new sw_en == enable) || new pc_en == enable then ldo_en_trans = true else ldo_en_trans = false */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed]*/
      0, /**< reserve 1 - for 32 bit boundary */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      0, /**< [X uV] -> voltage headroom needed. */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_1 */
   /**< Comments: <=200 */
   {
      PM_NPA_GENERIC_ENABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_LDO__NPM, /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      1, /**< Perpherial Index */
      0, /**< Primary (0) or Secondary (1) PMIC */
      0, /**< If((old sw_en == disable) && (new sw_en == enable) || new pc_en == enable then ldo_en_trans = true else ldo_en_trans = false */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed]*/
      0, /**< reserve 1 - for 32 bit boundary */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      0, /**< [X uV] -> voltage headroom needed. */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_2 */
   /**< Comments: 201 - 300 */
   {
      PM_NPA_GENERIC_ENABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_LDO__NPM, /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      1, /**< Perpherial Index */
      0, /**< Primary (0) or Secondary (1) PMIC */
      0, /**< If((old sw_en == disable) && (new sw_en == enable) || new pc_en == enable then ldo_en_trans = true else ldo_en_trans = false */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed]*/
      0, /**< reserve 1 - for 32 bit boundary */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      0, /**< [X uV] -> voltage headroom needed. */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_3 */
   /**< Comments: 301 - 412.8 */
   {
      PM_NPA_GENERIC_ENABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_LDO__NPM, /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      1, /**< Perpherial Index */
      0, /**< Primary (0) or Secondary (1) PMIC */
      0, /**< If((old sw_en == disable) && (new sw_en == enable) || new pc_en == enable then ldo_en_trans = true else ldo_en_trans = false */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed]*/
      0, /**< reserve 1 - for 32 bit boundary */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      0, /**< [X uV] -> voltage headroom needed. */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_4 */
   /**< Comments: 413 - 547.2 */
   {
      PM_NPA_GENERIC_ENABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_LDO__NPM, /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      1, /**< Perpherial Index */
      0, /**< Primary (0) or Secondary (1) PMIC */
      0, /**< If((old sw_en == disable) && (new sw_en == enable) || new pc_en == enable then ldo_en_trans = true else ldo_en_trans = false */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed]*/
      0, /**< reserve 1 - for 32 bit boundary */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      0, /**< [X uV] -> voltage headroom needed. */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_5 */
   /**< Comments: 548 - 681.6 */
   {
      PM_NPA_GENERIC_ENABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_LDO__NPM, /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      1, /**< Perpherial Index */
      0, /**< Primary (0) or Secondary (1) PMIC */
      0, /**< If((old sw_en == disable) && (new sw_en == enable) || new pc_en == enable then ldo_en_trans = true else ldo_en_trans = false */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed]*/
      0, /**< reserve 1 - for 32 bit boundary */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      0, /**< [X uV] -> voltage headroom needed. */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_6 */
   /**< Comments: 682 - 768.0 */
   {
      PM_NPA_GENERIC_ENABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_LDO__NPM, /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      1, /**< Perpherial Index */
      0, /**< Primary (0) or Secondary (1) PMIC */
      0, /**< If((old sw_en == disable) && (new sw_en == enable) || new pc_en == enable then ldo_en_trans = true else ldo_en_trans = false */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed]*/
      0, /**< reserve 1 - for 32 bit boundary */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      0, /**< [X uV] -> voltage headroom needed. */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_7 */
   /**< Comments: 769 - 1017.6 */
   {
      PM_NPA_GENERIC_ENABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_LDO__NPM, /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      1, /**< Perpherial Index */
      0, /**< Primary (0) or Secondary (1) PMIC */
      0, /**< If((old sw_en == disable) && (new sw_en == enable) || new pc_en == enable then ldo_en_trans = true else ldo_en_trans = false */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed]*/
      0, /**< reserve 1 - for 32 bit boundary */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      0, /**< [X uV] -> voltage headroom needed. */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_8 */
   /**< Comments: 1018 - 1296.0 */
   {
      PM_NPA_GENERIC_ENABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_LDO__NPM, /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      1, /**< Perpherial Index */
      0, /**< Primary (0) or Secondary (1) PMIC */
      0, /**< If((old sw_en == disable) && (new sw_en == enable) || new pc_en == enable then ldo_en_trans = true else ldo_en_trans = false */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed]*/
      0, /**< reserve 1 - for 32 bit boundary */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      0, /**< [X uV] -> voltage headroom needed. */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_9 */
   /**< Comments: 1226  - 1353.6 */
   {
      PM_NPA_GENERIC_ENABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_LDO__NPM, /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      1, /**< Perpherial Index */
      0, /**< Primary (0) or Secondary (1) PMIC */
      0, /**< If((old sw_en == disable) && (new sw_en == enable) || new pc_en == enable then ldo_en_trans = true else ldo_en_trans = false */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed]*/
      0, /**< reserve 1 - for 32 bit boundary */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      0, /**< [X uV] -> voltage headroom needed. */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_10 */
   /**< Comments: 1354 - 1555.2 */
   {
      PM_NPA_GENERIC_ENABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_LDO__NPM, /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      1, /**< Perpherial Index */
      0, /**< Primary (0) or Secondary (1) PMIC */
      0, /**< If((old sw_en == disable) && (new sw_en == enable) || new pc_en == enable then ldo_en_trans = true else ldo_en_trans = false */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed]*/
      0, /**< reserve 1 - for 32 bit boundary */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      0, /**< [X uV] -> voltage headroom needed. */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_11 */
   /**< Comments: 1556 - 1804.8 */
   {
      PM_NPA_GENERIC_ENABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_LDO__NPM, /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      1, /**< Perpherial Index */
      0, /**< Primary (0) or Secondary (1) PMIC */
      0, /**< If((old sw_en == disable) && (new sw_en == enable) || new pc_en == enable then ldo_en_trans = true else ldo_en_trans = false */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed]*/
      0, /**< reserve 1 - for 32 bit boundary */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      0, /**< [X uV] -> voltage headroom needed. */
   },
};

pm_npa_pam_client_cfg_type
pm_rpm_pam_ddr_rails_info [] =
{
   {
      (void*)pm_rpm_pam_ddr_b_ldo1,
      PM_NPA_VREG_LDO
   },
   {
      (void*)pm_rpm_pam_ddr_b_smps1,
      PM_NPA_VREG_SMPS
   },
   {
      (void*)pm_rpm_pam_ddr_b_smps3,
      PM_NPA_VREG_SMPS
   },
   {
      (void*)pm_rpm_pam_ddr_b_smps5,
      PM_NPA_VREG_SMPS
   },
   {
      (void*)pm_rpm_pam_ddr_a_ldo1,
      PM_NPA_VREG_LDO
   },
};
/* DDR_2 Client */
static pm_npa_smps_int_rep
pm_rpm_pam_ddr_2_b_smps3 [] =
{
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_0 */
   /**< Comments: No Activity */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__AUTO, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_1 */
   /**< Comments: <=200 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__AUTO, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_2 */
   /**< Comments: 201 - 300 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__AUTO, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_3 */
   /**< Comments: 301 - 412.8 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__AUTO, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_4 */
   /**< Comments: 413 - 547.2 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__AUTO, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_5 */
   /**< Comments: 548 - 681.6 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__AUTO, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_6 */
   /**< Comments: 682 - 768.0 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__NPM, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_7 */
   /**< Comments: 769 - 1017.6 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__NPM, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_8 */
   /**< Comments: 1018 - 1296.0 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__NPM, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_9 */
   /**< Comments: 1296  - 1353.6 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__NPM, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_10 */
   /**< Comments: 1354 - 1555.2 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__NPM, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_11 */
   /**< Comments: 1556 - 1804.8 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__NPM, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
};
static pm_npa_smps_int_rep
pm_rpm_pam_ddr_2_b_smps5 [] =
{
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_0 */
   /**< Comments: No Activity */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__AUTO, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_1 */
   /**< Comments: <=200 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__AUTO, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_2 */
   /**< Comments: 201 - 300 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__AUTO, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_3 */
   /**< Comments: 301 - 412.8 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__AUTO, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_4 */
   /**< Comments: 413 - 547.2 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__AUTO, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_5 */
   /**< Comments: 548 - 681.6 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__AUTO, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_6 */
   /**< Comments: 682 - 768.0 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__NPM, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_7 */
   /**< Comments: 769 - 1017.6 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__NPM, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_8 */
   /**< Comments: 1018 - 1296.0 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__NPM, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_9 */
   /**< Comments: 1296  - 1353.6 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__NPM, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_10 */
   /**< Comments: 1354 - 1555.2 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__NPM, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
   /**< Mode: PMIC_NPA_MODE_ID_DDR_CFG_11 */
   /**< Comments: 1556 - 1804.8 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_SMPS__NPM, /**< [AUTO (default), IPEAK, NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      0, /**< global_byp_en - Keeps whether the child LDOs are allowed to go into bypass */
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */
      PM_SWITCHING_FREQ_FREQ_NONE, /**< [xx MHz] -> max within a priority group. */
      PM_NPA_FREQ_REASON_NONE, /**< Freq4 BT -> Freq4 GPS -> Freq4 WLAN -> Freq 4 WAN (lowest to highest priority). */
      PM_NPA_QUIET_MODE__DISABLE, /**< [None, Quiet, Super Quiet] -> max aggregation (left to right). */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed] */
   },
};

pm_npa_pam_client_cfg_type
pm_rpm_pam_ddr_2_rails_info [] =
{
   {
      (void*)pm_rpm_pam_ddr_2_b_smps3,
      PM_NPA_VREG_SMPS
   },
   {
      (void*)pm_rpm_pam_ddr_2_b_smps5,
      PM_NPA_VREG_SMPS
   },
};
/* RPM_INIT Client */
static pm_npa_ldo_int_rep
pm_rpm_pam_rpm_init_a_ldo1 [] =
{
   /**< Mode: PMIC_NPA_MODE_ID_RPM_INIT_MODE_0 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_LDO__IPEAK, /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      1, /**< Perpherial Index */
      0, /**< Primary (0) or Secondary (1) PMIC */
      0, /**< If((old sw_en == disable) && (new sw_en == enable) || new pc_en == enable then ldo_en_trans = true else ldo_en_trans = false */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed]*/
      0, /**< reserve 1 - for 32 bit boundary */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */      
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
   },
   /**< Mode: PMIC_NPA_MODE_ID_RPM_INIT_MODE_1 */
   {
      PM_NPA_GENERIC_DISABLE, /**< [Disable (default), Enable] -> max aggregation (left to right). */
      PM_NPA_SW_MODE_LDO__IPEAK, /**< [BYPASS, IPEAK (default), NPM] -> max aggregation (left to right). */
      PM_NPA_PIN_CONTROL_ENABLE__NONE, /**< [NONE, EN1, EN2, EN3, EN4] -> ORed value of list. */
      PM_NPA_PIN_CONTROL_POWER_MODE__NONE, /**< [NONE, EN1, EN2, EN3, EN4, SLEEPB] -> ORed value of list. */
      1, /**< Perpherial Index */
      0, /**< Primary (0) or Secondary (1) PMIC */
      0, /**< If((old sw_en == disable) && (new sw_en == enable) || new pc_en == enable then ldo_en_trans = true else ldo_en_trans = false */
      PM_NPA_BYPASS_ALLOWED, /**< [Allowed (default), Disallowed]*/
      0, /**< reserve 1 - for 32 bit boundary */
      0, /**< [X uV] -> max aggregation. */
      0, /**< [X mA] -> summed aggregation. */      
      0, /**< [X uV] -> voltage headroom needed. */
      0, /**< [X uV] -> max aggregation. */
   },
};

pm_npa_pam_client_cfg_type
pm_rpm_pam_rpm_init_rails_info [] =
{
   {
      (void*)pm_rpm_pam_rpm_init_a_ldo1,
      PM_NPA_VREG_LDO
   },
};
