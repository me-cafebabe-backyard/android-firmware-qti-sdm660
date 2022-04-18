#ifndef BOOT_EXTERN_PMIC_INTERFACE_H
#define BOOT_EXTERN_PMIC_INTERFACE_H

/*===========================================================================

                    BOOT EXTERN PMIC DRIVER DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external pmic drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2011-2017 by Qualcomm Technologies Incorporated.  All Rights Reserved.
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
04/18/16   digants Updated with changes for warm reset status check
02/18/16   aab     Added boot_pm_system_init()
10/05/15   kpa     Changed boot_pm_ps_hold_cfg() API to boot_pm_app_pon_pshold_cfg() to match pmic API name
09/29/15   kpa     Added support to check for warm reset status
07/11/15   rp	   Changed boot_pm_enable_led api to have LED color as an additional parameter
05/31/15   kpa     Replace pm_oem_init() with pm_sbl_chg_init()  
03/27/15   kpa     Added boot_pm_device_programmer_init
09/23/14   ck      Removed feature flag as API is always enabled in XBL
05/24/13   yp      Add boot_pm_vib_on and boot_pm_vib_off.
04/02/13   dh      Add boot_pm_pon_ps_hold_cfg.
03/29/13   plc     Add LED functions
02/26/13   dh      Add boot_pm_init_smem
09/26/12   dh      Add boot_pm_oem_init and boot_pm_driver_init
04/18/12   dh      change boot_pm_get_power_on_status to boot_pm_dev_get_power_on_reason
09/08/11   dh      Initial Creation.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "pm.h"
#include "pm_rgb.h"
#include "pm_fg_batt_info.h"
#include "boot_logger.h"
#include "boot_logger_timer.h"


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
pm_err_flag_type boot_pm_device_init(void);


/*===========================================================================

**  Function :  boot_pm_set_psi_address

** ==========================================================================
*/
/*! 
 * @brief This function sets psi address for PMIC image
 * @return Error flag.
 *
 */ 
pm_err_flag_type boot_pm_set_psi_address(uint64 psiAddress);


/*===========================================================================

**  Function :  boot_pm_get_power_on_status

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
pm_err_flag_type boot_pm_dev_get_power_on_reason(unsigned pmic_device_index,
                                                 uint64 * pwr_on_reason);

/*===========================================================================   

**  Function :  boot_pm_get_pon_reason_history 
  
** ========================================================================== 
*/ 
/*! 
 * @brief  This function returns the phone pon reason history from PBS RAM 
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
pm_err_flag_type boot_pm_get_pon_reason_history_to_dump(pm_pbs_pon_reason_history_data_type* pon_reason_history); 


/*===========================================================================

**  Function :  boot_pm_driver_init

** ==========================================================================
*/
/*! 
 * @brief This function executes the pmic sw driver initialization
 * @return Error flag.
 *
 */ 
pm_err_flag_type boot_pm_driver_init(void);


/*===========================================================================

**  Function :  boot_pm_sbl_chg_init

** ==========================================================================
*/
/*! 
 * @brief This function executes the pmic sw driver initialization
 * @return Error flag.
 *
 */ 
pm_err_flag_type boot_pm_sbl_chg_init(void);


/*===========================================================================

**  Function :  boot_pm_system_init

** ==========================================================================
*/
/*! 
 * @brief This function executes pmic post initialization
 * @return Error flag.
 *
 */ 
pm_err_flag_type boot_pm_system_init(void);


/*===========================================================================

**  Function :  boot_pm_init_smem

** ==========================================================================
*/
/*! 
 * @brief This function executes the pmic smem initialization
 * @return Error flag.
 *
 */ 
pm_err_flag_type boot_pm_init_smem(void);


/*===========================================================================

**  Function :  boot_pm_enable_led

** ==========================================================================
*/
/*! 
 * @brief This function executes the pmic rgb led functions to turn on an LED
 * @return Error flag.
 *
 */ 
pm_err_flag_type boot_pm_enable_led(uint32, boolean);


/*===========================================================================

**  Function :  boot_pm_app_pon_pshold_cfg

** ==========================================================================
*/
/**
 * @brief Configure MSM PS_HOLD behavior.
 *  
 * @details Configure PMIC to act on MSM PS_HOLD state
 * 
 * @param pmic_device_index When the target has more than
 *          one pmic, this is the index of the PMIC in which
 *          the power on module is physically located. The device
 *          index starts at zero.
 * @param ps_hold_cfg 
 *          PM_APP_PON_CFG_WARM_RESET,
 *          PM_APP_PON_CFG_HARD_RESET,
 *          PM_APP_PON_CFG_NORMAL_SHUTDOWN,
 *   
 *                   
 * @return pm_err_flag_type
 */
pm_err_flag_type boot_pm_app_pon_pshold_cfg(pm_app_pon_reset_cfg_type);


/*===========================================================================

**  Function :  boot_pm_vib_on

** ==========================================================================
*/
/*! 
* @brief This function initializes vibration driver voltage and turn on it
* @return Error flag.
*
*/
pm_err_flag_type boot_pm_vib_on(void);


/*===========================================================================

**  Function :  boot_pm_vib_off

** ==========================================================================
*/
/*! 
 * @brief This function turn off vibration
 * @return Error flag.
 *
 */ 
pm_err_flag_type boot_pm_vib_off(void);


/*===========================================================================

**  Function :  boot_pm_device_programmer_init

** ==========================================================================
*/
/*! 
 * @brief This function executes the pmic initialization for deviceprogrammer
 * @return Error flag.
 *
 */ 
pm_err_flag_type boot_pm_device_programmer_init (void);

/*===========================================================================

**  Function :  boot_pm_pon_warm_reset_status

** ==========================================================================
*/
/*! 
 * @brief This function provides warm reset status information
 * @return Error flag.
 *
 */ 
pm_err_flag_type boot_pm_pon_warm_reset_status( 
  unsigned pmic_device_index, 
  boolean *status
);


/*===========================================================================

**  Function :  boot_pm_pon_warm_reset_status_clear

** ==========================================================================
*/
/*! 
 * @brief This function clears the warm reset status
 * @return Error flag.
 *
 */ 
pm_err_flag_type boot_pm_pon_warm_reset_status_clear(
  unsigned pmic_device_index
);

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
 *api boot_pm_device_init() must have been called before calling this API
 *
 */
pm_err_flag_type boot_pm_pon_wdog_cfg(uint8 pmic_device_index,uint32 s1_timer,uint32 s2_timer,pm_pon_reset_cfg_type reset_cfg_type);
 
 /*===========================================================================

**  Function :  boot_pm_pon_wdog_enable

** ==========================================================================
*/
/*!
 *@brief  This function will enable the wdog with the given pmic_device_index.
 *
 *INPUT PARAMETERS
 *@param pmic_device_index
 *@param enable flag
 *
 *@return pm_err_flag_type.
 *
 *
 *@par Dependencies
 * api boot_pm_pon_wdog_cfg() must have been called before calling this API
 *
 */

pm_err_flag_type boot_pm_pon_wdog_enable(uint8 pmic_device_index,pm_on_off_type enable);
	

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
 *
 *@par Dependencies
 *api boot_pm_pon_wdog_cfg() must have been called before calling this API
 *
 */

pm_err_flag_type boot_pm_pon_wdog_disable(uint8 pmic_device_index, pm_on_off_type disable);

/*===========================================================================

**  Function :  boot_pm_pon_warm_reset_status

** ==========================================================================
*/
/*! 
 * @brief This function provides warm reset status information
 * @return Error flag.
 *
 */ 
pm_err_flag_type boot_pm_pon_warm_reset_status( 
  unsigned pmic_device_index, 
  boolean *status
);


/*===========================================================================

**  Function :  boot_pm_pon_warm_reset_status_clear

** ==========================================================================
*/
/*! 
 * @brief This function clears the warm reset status
 * @return Error flag.
 *
 */ 
pm_err_flag_type boot_pm_pon_warm_reset_status_clear(
  unsigned pmic_device_index
);

boolean boot_check_display_vbatt(void);

#endif /* BOOT_EXTERN_PMIC_INTERFACE_H */
