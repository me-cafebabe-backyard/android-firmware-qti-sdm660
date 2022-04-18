/*===========================================================================

                    BOOT EXTERN PMIC DRIVER DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external pmic drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2011-2015,2017 by Qualcomm Technologies, Incorporated.
                All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
03/08/17    sj     Added Api to qurey the battery status in XBL ramdump
11/07/16   yps     Added boot_pm_dev_get_pon_reason_hist
06/16/16   qbz     Added boot_pm_set_psi_address
02/18/16   aab     Added boot_pm_system_init()
10/05/15   kpa     Changed boot_pm_ps_hold_cfg() API to boot_pm_app_pon_pshold_cfg() to match pmic API name
09/29/15   kpa     Added support to check for warm reset status
07/11/15   rp	   Changed boot_pm_enable_led api to have LED color as an additional parameter
05/31/15   aab     Replace pm_oem_init() with pm_sbl_chg_init()  
03/27/15   kpa     Added boot_pm_device_programmer_init
01/06/15   kt      Changed PMIC PS_HOLD config API call for multi-PMIC support.
08/20/14   aab     Updated LED blinking intensity to PM_RGB_DIM_LEVEL_HIGH
09/24/14   ck      Removed FEATURE_BOOT_PON_VIBRATION flag
05/22/13   yp      Add boot_pm_vib_on and boot_pm_vib_off
05/22/13   aus     Updated RAM dump LED to support multiple targets
04/02/13   dh      Add boot_pm_pon_ps_hold_cfg.
                   Change LED light to blue and brightness to high
03/29/13   plc     Add LED Functions
02/26/13   dh      Add boot_pm_init_smem
04/18/12   dh      change boot_pm_get_power_on_status to boot_pm_dev_get_power_on_reason
09/08/11   dh      Initial Creation.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "boot_extern_pmic_interface.h"
#include "boot_logger.h"
#include <string.h>
#include <stdio.h>
#include "boot_target.h"
#include "pm_haptics.h"
#include "boot_extern_platforminfo_interface.h"

/*battery threshold for enable the disply in RAMDUMP mode*/
#define BATT_DISPLAY_THRESHOLD   3700

/* PMIC team recommended voltages (in mV)*/
#define QRD_HAPTICS_VOLTAGE   3132

/* PMIC team recommended voltages (in mV)*/
#define MTP_HAPTICS_VOLTAGE   1972



/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 
/*===========================================================================

**  Function :  boot_pm_device_init

** ==========================================================================
*/
/*! 
 * @brief This function executes the pmic device initialization
 * @return Error flag.
 *
 */ 
pm_err_flag_type boot_pm_device_init(void)
{
  return pm_device_init();
}


boolean boot_check_display_vbatt(void)
{
	
  UINT32       VBat = 0;
  UINT32      pmicDeviceIndex = PMIC_DEVICE_INDEX;
  UINT32 status = 0;
  char msg[40];
  
  status =  pm_fg_batt_info_get_vbatt (pmicDeviceIndex ,&VBat);
  
  snprintf(msg,40,"VBatt Value is %d ",VBat);
  boot_log_message(msg);
    
  if((VBat >= BATT_DISPLAY_THRESHOLD) && (status==0))
  {
    boot_log_message("vbatt is more than threshold");
    return TRUE;
  } 
  else 
  {	  
    boot_log_message("Vbatt is not more than threshold");
    return FALSE;	  
  }	  
	
}

/*===========================================================================

**  Function :  boot_pm_set_psi_address

** ==========================================================================
*/
/*! 
 * @brief This function sets psi address for PMIC image
 * @return Error flag.
 *
 */ 
pm_err_flag_type boot_pm_set_psi_address(uint64 psiAddress)
{
  return pm_psi_set_base_address(psiAddress);
}

/*===========================================================================

**  Function :  boot_pm_dev_get_power_on_reason

** ==========================================================================
*/
/*!
 * @brief  This function returns the phone power-on reason. Typically used in boot
    during early bootup and stored in memory for later access.
 *
 * INPUT PARAMETERS
 * @param pmic_device_index When the target has more than
 *          one pmic, this is the index of the PMIC in which
 *          the power on module is physically located. The device
 *          index starts at zero.
 *@param pwr_on_reason
 *    - pointer to 64-bit unsigned integer that stores the all PON reasons
 *   including PON power on, Warm Reset Reason and POFF_REASON,
 *   SOFT_RESET_REASON.
 *    PON_REASON
 *    PON_WARM_RESET_REASON
 *    PON_POFF_REASON
 *    PON_SOFT_RESET_REASON
 *
 * @return pm_err_flag_type.
 *         PM_ERR_FLAG__PAR1_OUT_OF_RANGE     = Input Parameter one is out of range.
 *         PM_ERR_FLAG__FEATURE_NOT_SUPPORTED = Feature not available on this 
 *                                       version of the PMIC.
 *         PM_ERR_FLAG__SBI_OPT_ERR           = The SBI driver failed to communicate
 *                                       with the PMIC.
 *         PM_ERR_FLAG__SUCCESS               = SUCCESS.
 *
 *@par Dependencies
 *      and pm_init() must have been called.
===========================================================================*/
pm_err_flag_type boot_pm_dev_get_power_on_reason(unsigned pmic_device_index, uint64* pwr_on_reason)
{
  return pm_pon_get_all_pon_reasons(pmic_device_index, pwr_on_reason);
}

/*=========================================================================== 
  
**  Function :  boot_pm_dev_get_pon_reason_hist 
  
** ========================================================================== 
*/ 
/*! 
 * @brief  This function returns the pon reason history for past three resets 
 * 
  
* INPUT PARAMETERS 
 *@param pon_reason_history_ptr 
 *    - pointer to 64-bit unsigned integer that stores the all PON reasons 
 *   for the past three resets 
 * 
 * @return pm_err_flag_type. 
 *         PM_ERR_FLAG__PAR1_OUT_OF_RANGE     = Input Parameter one is out of range. 
 *         PM_ERR_FLAG__FEATURE_NOT_SUPPORTED = Feature not available on this  
 *                                       version of the PMIC. 
 *         PM_ERR_FLAG__SBI_OPT_ERR           = The SBI driver failed to communicate 
 *                                       with the PMIC. 
 *         PM_ERR_FLAG__SUCCESS               = SUCCESS. 
 * 
 *@par Dependencies 
 *      and pm_init() must have been called. 
===========================================================================*/ 
pm_err_flag_type boot_pm_get_pon_reason_history_to_dump(pm_pbs_pon_reason_history_data_type* pon_reason_history_ptr) 
{ 
  return pm_get_pon_reason_history_to_dump(pon_reason_history_ptr); 
} 

/*===========================================================================

**  Function :  boot_pm_driver_init

** ==========================================================================
*/
/*! 
 * @brief This function executes the pmic device initialization
 * @return Error flag.
 *
 */ 
pm_err_flag_type boot_pm_driver_init(void)
{
  return pm_driver_init();
}


/*===========================================================================

**  Function :  boot_pm_sbl_chg_init

** ==========================================================================
*/
/*! 
 * @brief This function executes the pmic sbl charging initialization
 * @return Error flag.
 *
 */ 
pm_err_flag_type boot_pm_sbl_chg_init(void)
{
  return pm_sbl_chg_init();  
}

/*===========================================================================

**  Function :  boot_pm_system_init

** ==========================================================================
*/
/*! 
 * @brief This function executes the pmic post initialization
 * @return Error flag.
 *
 */ 
pm_err_flag_type boot_pm_system_init(void)
{
  return pm_system_init();  
}


/*===========================================================================

**  Function :  boot_pm_init_smem

** ==========================================================================
*/
/*! 
 * @brief This function executes the pmic smem initialization
 * @return Error flag.
 *
 */ 
pm_err_flag_type boot_pm_init_smem(void)
{
  return pm_smem_init();
}


/*===========================================================================

**  Function :  boot_pm_enable_led

** ==========================================================================
*/
/*! 
 * @brief This function executes the pmic rgb led functions to turn on LED
 * @return Error flag.
 *
 */ 
pm_err_flag_type boot_pm_enable_led(uint32 led_color, boolean current_led_status)
{
  /* Enable LED based on input color parameter */
  return pm_rgb_led_config(1, PM_RGB_1, led_color,  
                           PM_RGB_VOLTAGE_SOURCE_VPH, PM_RGB_DIM_LEVEL_HIGH, 
                           current_led_status);
}


/*===========================================================================

**  Function :  boot_pm_app_pon_pshold_cfg

** ==========================================================================
*/
/**
 * @brief Configures PMIC to act on MSM PS_HOLD toggle. This
 *        is an app level API which handles all the required
 *        PS_HOLD config for all the applicable PMICs
 *        internally.
 *  
 * @details Configure PMIC to act on MSM PS_HOLD state. 
 * 
 * @param ps_hold_cfg 
 *          PM_APP_PON_CFG_WARM_RESET,
 *          PM_APP_PON_CFG_HARD_RESET,
 *          PM_APP_PON_CFG_NORMAL_SHUTDOWN,
 *          
 *   
 *                   
 * @return pm_err_flag_type PM_ERR_FLAG__SUCCESS = SUCCESS else 
 *         ERROR.
 */
pm_err_flag_type boot_pm_app_pon_pshold_cfg
(
pm_app_pon_reset_cfg_type ps_hold_cfg
)
{
  return pm_app_pon_pshold_cfg(ps_hold_cfg);
}


/*===========================================================================

**  Function :  boot_pm_vib_on

** ==========================================================================
*/
/*! 
 * @brief This function initializes vibration driver voltage and turn on it
 * @return Error flag.
 *
 */ 

pm_err_flag_type boot_pm_vib_on(void)
{

  pm_err_flag_type ret_val = PM_ERR_FLAG__SUCCESS;
  
#if !defined(FEATURE_DDI_IMAGE) && !defined(FEATURE_DEVICEPROGRAMMER_IMAGE) 
  DalPlatformInfoPlatformInfoType   plat_info;
  
  boot_DalPlatformInfo_PlatformInfo((void *)&plat_info);
  if(DALPLATFORMINFO_TYPE_QRD  == plat_info.platform)
  {
    /* return value check not required; In case of failure, voltage will be default-1972mV */
    pm_haptics_set_vmax_volt(0, QRD_HAPTICS_VOLTAGE);
  }
  
  ret_val = pm_haptics_enable( 0,  PM_ON );

  if (ret_val == PM_ERR_FLAG__SUCCESS)
  {
  	ret_val = pm_haptics_play(0, PM_HAPTICS_PLAY);
  }
#endif
  return ret_val;
    
}

/*===========================================================================

**  Function :  boot_pm_vib_off

** ==========================================================================
*/
/*! 
 * @brief This function turn off vibration
 * @return Error flag.
 *
 */ 

pm_err_flag_type boot_pm_vib_off(void)
{
  pm_err_flag_type ret_val = PM_ERR_FLAG__SUCCESS;
  
#if !defined(FEATURE_DDI_IMAGE) && !defined(FEATURE_DEVICEPROGRAMMER_IMAGE) 
  ret_val =  pm_haptics_play(0, PM_HAPTICS_PAUSE);

  if (ret_val == PM_ERR_FLAG__SUCCESS)
  {
    ret_val =  pm_haptics_enable( 0,  PM_OFF );
  }
  
  ret_val = pm_haptics_set_vmax_volt(0, MTP_HAPTICS_VOLTAGE);
#endif  
  return ret_val;
}

/*===========================================================================

**  Function :  boot_pm_device_programmer_init

** ==========================================================================
*/
/*! 
 * @brief This function executes the pmic initialization for deviceprogrammer
 * @return Error flag.
 *
 */ 
pm_err_flag_type boot_pm_device_programmer_init (void)
{
  return pm_device_programmer_init();
}

/*===========================================================================

**  Function :  boot_pm_pon_warm_reset_status

** ==========================================================================
*/
/*! 
 * @brief This function provides warm reset status information
 * @return Error flag.
 *
 */ 
pm_err_flag_type boot_pm_pon_warm_reset_status
(
  unsigned pmic_device_index, 
  boolean *status
)
{
  return pm_pon_warm_reset_status(pmic_device_index, status);
}


/*===========================================================================

**  Function :  boot_pm_pon_warm_reset_status_clear

** ==========================================================================
*/
/*! 
 * @brief This function clears the warm reset status
 * @return Error flag.
 *
 */ 
pm_err_flag_type boot_pm_pon_warm_reset_status_clear
(
  unsigned pmic_device_index
)
{
  return pm_pon_warm_reset_status_clear(pmic_device_index);
}


/*===========================================================================

**  Function :  boot_pm_pon_wdog_cfg

** ==========================================================================
*/
/*!
 *@brief  This function will configure the wdog with the given timer value 
 * and with the given reset configuration type.
 *
 *INPUT PARAMETERS
 *@param pmic_device_index
 *@param s1_timer
 *@param s2_timer
 *@param reset_cfg_type
 *
 *
 *@return pm_err_flag_type.
 *
 *
 @par Dependencies
 *api boot_pm_device_init() must have been called before calling this API
 *
 */
pm_err_flag_type boot_pm_pon_wdog_cfg
(
	uint8 pmic_device_index, 
	uint32 s1_timer, 
	uint32 s2_timer, 
	pm_pon_reset_cfg_type reset_cfg_type
)
{
	return pm_pon_wdog_cfg(pmic_device_index,s1_timer, s2_timer, reset_cfg_type);
}

/*===========================================================================

**  Function :  boot_pm_pon_wdog_enable

** ==========================================================================
*/
/*!
 *@brief  This function will enable the wdog with the given pmic_device_index.
 *
 * INPUT PARAMETERS
 *@param pmic_device_index
 *@param enable flag
 *
 *@return pm_err_flag_type
 *
 *
 *@par Dependencies
 * api boot_pm_pon_wdog_cfg() must have been called before calling this API
 *
 */
pm_err_flag_type boot_pm_pon_wdog_enable
(
	uint8 pmic_device_index,
	pm_on_off_type enable
)
{
	return pm_pon_wdog_enable(pmic_device_index,enable);
}
 
/*===========================================================================

**  Function :  boot_pm_pon_wdog_disable

** ==========================================================================
*/
/*!
 *@brief  This function will disable the wdog with the given pmic_device_index.
 *
 *INPUT PARAMETERS
 *@param pmic_device_index
 *@param disable flag
 *
 *@return pm_err_flag_type.
 *
 *@par Dependencies
 * api boot_pm_pon_wdog_cfg() must have been called before calling this API
 *
 */
pm_err_flag_type boot_pm_pon_wdog_disable
(
	uint8 pmic_device_index,
	pm_on_off_type disable
)
{
	return pm_pon_wdog_enable(pmic_device_index,disable);
}
