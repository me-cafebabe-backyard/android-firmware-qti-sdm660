#ifndef PM_APP_SMBCHG__H
#define PM_APP_SMBCHG__H

/*! \file pm_app_smbchg.h
 *  \n
 *  \brief  PMIC sbl charger algorithms
 *  \details  This file contains functions and variable declarations to support
 *   the PMIC SBL charging
 *
 *
 *  \n &copy; Copyright (c) 2012-2015  by QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/*===========================================================================
                                Edit History
This document is created by a code generator, therefore this section will
not contain comments describing changes made to the module.

 
when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
10/20/15   aab     Added dbc_high_current_mode parameter 
09/28/15   aab     Updated pm_smbchg_specific_data_type struct to include APSD reset parameters 
10/09/15   aab     Added pm_sbl_chg_cfg_cls_platform() to support platform type DALPLATFORMINFO_TYPE_CLS 
02/04/15   aab     Added parameter wipwr_bootup_battery_theshold_mv  to be used when Wireless charger is detected
11/18/14   aab     Updated SBL charger driver to use Vbatt ADC
10/15/14   aab     Added pm_sbl_config_chg_parameters() 
10/14/14   aab     Added pm_sbl_config_fg_sram (). Updated pm_smbchg_specific_data_type
08/20/14   aab     Added pm_smbchg_specific_data_type to hold DBC charging related parameters
04/29/14   aab     Creation
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

#include "pm_err_flags.h"
#include "pm_smbchg_bat_if.h"
#include "pm_smbchg_misc.h"
#include "pm_smbchg_usb_chgpth.h"
#include "pm_resources_and_types.h"

/*=========================================================================== 
 
                     GLOBAL DEFINES
 
===========================================================================*/



/*=========================================================================== 
 
                     GLOBAL TYPE DEFINITIONS
 
===========================================================================*/
#if 0
typedef struct
{
   pm_smbchg_bat_if_low_bat_thresh_type  vlowbatt_threshold;
   pm_smbchg_param_config_enable_type    enable_config;
} pm_smbchg_vlowbatt_threshold_data_type;

typedef struct
{
   pm_smbchg_chgpth_input_priority_type  chgpth_input_priority; //0=DCIN; 1=USBIN
   pm_smbchg_param_config_enable_type    enable_config;
} pm_smbchg_chgpth_input_priority_data_type;


typedef struct
{
   pm_smbchg_bat_miss_detect_src_type  bat_missing_detection_src; 
   pm_smbchg_param_config_enable_type  enable_config;
} pm_smbchg_bat_miss_detect_src_data_type ;


typedef struct
{
   pm_smbchg_wdog_timeout_type         wdog_timeout;
   pm_smbchg_param_config_enable_type  enable_config;
} pm_smbchg_wdog_timeout_data_type;


typedef struct
{
   boolean enable_wdog;
   pm_smbchg_param_config_enable_type enable_config;
} pm_smbchg_enable_wdog_data_type;


typedef struct
{
   uint32 fast_chg_i_ma; //Valid values are 300 to 3000 mAmp
   pm_smbchg_param_config_enable_type enable_config;
} pm_smbchg_fast_chg_current_data_type;


typedef struct
{
   uint32 pre_chg_i_ma; //Valid values are 100 to 550 mAmp
   pm_smbchg_param_config_enable_type enable_config;
} pm_smbchg_pre_chg_current_data_type;


typedef struct
{
   uint32 pre_to_fast_chg_theshold_mv; //Valid range is 2400mV to 3000mV
   pm_smbchg_param_config_enable_type enable_config;
} pm_smbchg_pre_to_fast_chg_threshold_data_type;


typedef struct
{
   uint32 float_volt_theshold_mv; //Valid range is 3600mV to 4500 mv
   pm_smbchg_param_config_enable_type enable_config;
} pm_smbchg_float_voltage_threshold_data_type;

typedef struct
{
   uint32  usbin_input_current_limit; //Valid value is 300 to 3000mAmp
   pm_smbchg_param_config_enable_type enable_config;
} pm_smbchg_usbin_input_current_limit_data_type;


typedef struct
{
   uint32  dcin_input_current_limit; //valid range is 300 to 2000 mAmp
   pm_smbchg_param_config_enable_type enable_config;
} pm_smbchg_dcin_input_current_limit_data_type;




typedef struct
{
    pm_smbchg_vlowbatt_threshold_data_type         dbc_bootup_volt_threshold;
    pm_smbchg_vlowbatt_threshold_data_type         apsd_reset_vlowbatt_threshold;
    pm_smbchg_chgpth_input_priority_data_type      chgpth_input_priority;
    pm_smbchg_bat_miss_detect_src_data_type        bat_miss_detect_src;
    pm_smbchg_wdog_timeout_data_type               wdog_timeout;
    pm_smbchg_enable_wdog_data_type                enable_wdog;
    pm_smbchg_fast_chg_current_data_type           fast_chg_i;
    pm_smbchg_pre_chg_current_data_type            pre_chg_i;
    pm_smbchg_pre_to_fast_chg_threshold_data_type  pre_to_fast_chg_theshold_mv;
    pm_smbchg_float_voltage_threshold_data_type    float_volt_theshold_mv;
    pm_smbchg_usbin_input_current_limit_data_type  usbin_input_current_limit;
    pm_smbchg_dcin_input_current_limit_data_type   dcin_input_current_limit;
    uint32  bootup_battery_theshold_mv;
    uint32  wipwr_bootup_battery_theshold_mv;
    uint32  apsd_reset_threshold_mv;
    uint32  apsd_reset_theshold_no_uvlo_mv;
    uint32  apsd_reset_theshold_uvlo_mv;
    boolean enable_jeita_hard_limit_check;
    boolean dbc_usb_500_mode;
} pm_smbchg_specific_data_type;

#endif

/*===========================================================================

                     PROTOTYPES 

===========================================================================*/
/**
 * @name 
 *     pm_sbl_chg_config_vbat_low_threshold
 *
 * @description
 *    This function configures battery charge status 
 * 
 * @param 
 *     None
 * 
 * @return 
 *     pm_err_flag_type
 * 
 * @dependency
 *     The following function must have been called:
 *        pm_target_information_init()
 */
//pm_err_flag_type pm_sbl_chg_config_vbat_low_threshold(uint32 device_index, pm_smbchg_vlowbatt_threshold_data_type vlowbatt_threshold_data);



/**
 * @name 
 *     pm_sbl_chg_check_weak_battery_status
 *
 * @description
 *    This function checks the battery charge status 
 * 
 * @param 
 *     None
 * 
 * @return 
 *     pm_err_flag_type
 * 
 * @dependency
 *     The following function must have been called:
 *        pm_driver_init()
 */
pm_err_flag_type pm_sbl_chg_check_weak_battery_status(uint32 device_index);

/**
 * @name 
 *     pm_sbl_config_fg_sram
 *
 * @description
 *    This function configures fg related parameters to SRAM
 * 
 * @param 
 *     None
 * 
 * @return 
 *     pm_err_flag_type
 * 
 * @dependency
 *     The following function must have been called:
 *        pm_driver_init()
 */
pm_err_flag_type pm_sbl_config_fg_sram(uint32 device_index);

/**
 * @name 
 *     pm_sbl_config_chg_parameters
 *
 * @description
 *    This function configures charger parameters whose value is updated on configuration file
 * 
 * @param 
 *     None
 * 
 * @return 
 *     pm_err_flag_type
 * 
 * @dependency
 *     The following function must have been called:
 *        pm_driver_init()
 */
pm_err_flag_type pm_sbl_config_chg_parameters(uint32 device_index);


/**
 * @name 
 *     pm_sbl_chg_cfg_cls_platform
 *
 * @description
 *    This function configures charger parameters for target platform type DALPLATFORMINFO_TYPE_CLS 
 * 
 * @param 
 *     device_index :  pmic index
 * 
 * @return 
 *     pm_err_flag_type
 * 
 * @dependency
 *     The following function must have been called:
 *        pm_driver_init()
 */
pm_err_flag_type pm_sbl_chg_cfg_cls_platform(uint32 device_index);

#endif  //PM_APP_SMBCHG__H

