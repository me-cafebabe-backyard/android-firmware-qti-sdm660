#ifndef PM_RPM_TARGET_H
#define PM_RPM_TARGET_H

/*! \file pm_rpm_target.h
*  \n
*  \brief This file contains PMIC function prototypes for sleep related functions.
*  \n
*  &copy; Copyright 2013-2015 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/rpm.bf/1.8/core/pmic/pm/framework/inc/pm_rpm_target.h#1 $  

when       who     what, where, why
--------   ---     ----------------------------------------------------------
01/24/14   kt      Updated comments header and added doxygen comments.
08/16/13   hs      Initial version. 
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_npa_device.h"
#include "pm_err_flags.h"
#include "pm_npa_irep.h"
#include "rpmserver.h"


#define   PM_MAX_SLEEP_MODE       2

/* Battery status type */
typedef struct
{
   uint32           vbat_adc;
   boolean          batt_present;
   boolean          adc_ready;
   pm_err_flag_type err_flag;
}pm_battery_status_type;

/*===========================================================================

                        MACRO DEFINITIONS 

===========================================================================*/

#define PM_MAX_SLEEP_MODE  2  

/*===========================================================================

                        GENERIC FUNCTION PROTOTYPES

===========================================================================*/

/** 
 * @name pm_rpm_sleep_init 
 *  
 * @brief This function initializes the sleep settings LUT.
 * 
 * @param None
 *
 * @return None 
 *  
 * @dependencies Sleep settings should be available in config.
 *
 */
void pm_rpm_sleep_init(void);

/** 
 * @name pm_rpm_platform_init 
 *  
 * @brief This function initialize the platform specific 
 *        settings.
 * 
 * @param None
 *
 * @return None 
 *  
 * @sideeffects None
 *
 */
void pm_rpm_platform_init(void);

/** 
 * @name pm_rpm_platform_post_init 
 *  
 * @brief This function initalizes the platform settings post 
 *        pmic_init
 * 
 * @param None
 *
 * @return pm_err_flag_type 
 *  
 * @sideeffects None
 *
 */
pm_err_flag_type pm_rpm_platform_post_init(void);


/** 
 * @name pm_rpm_target_execute_smps_pre_enable 
 *  
 * @brief Target specific function called from npa layer to 
 *        execute pre SMPS enable dependencies
 * 
 * @param pmic_index[in]: PMIC chip index 
 *        smps_index[in]: SMPS peripheral index
 *        sw_en[in]: SMPS Aggregated sw enable request
 *        continue_enable_flag[out]: flag to indicate if SMPS
 *        enable related execution needs to be continued or not.
 *
 * @return pm_err_flag_type 
 *  
 * @sideeffects None
 *
 */
pm_err_flag_type 
pm_rpm_target_execute_smps_pre_enable (uint8 pmic_index, uint8 smps_index, pm_on_off_type sw_en, 
                                       boolean *continue_enable_flag);

/**
* @brief This function returns the battery status.
* 
* @param[out] batt_status  Battery present status and voltage.
*
* @return  pm_err_flag_type 
*          PM_ERR_FLAG__SUCCESS = SUCCESS else ERROR.
*
*/
pm_err_flag_type 
pm_rpm_check_battery_status(pm_battery_status_type *batt_status);

/**
* @brief This function initialize the platform specific settings
*        prior to drivers initialization
* 
* @param none
*
* @return none
*
*/
void
pm_rpm_platform_pre_init (void);


/**
* @brief This function executes any PMIC pre dependency
* 
* @param none
*
* @return none
*
*/
pm_err_flag_type
pm_rpm_target_pre_dependency_execute(rpm_application_info *info);

#endif /* PM_RPM_TARGET_H */
