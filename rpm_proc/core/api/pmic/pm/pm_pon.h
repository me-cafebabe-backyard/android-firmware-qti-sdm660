#ifndef PM_PON__H
#define PM_PON__H

/*! \file pm_pon.h
 *  \n
 *  \brief This file contains functions and variable declarations to support 
 *   the pon driver module.
 *  \n
 *  \n &copy; Copyright (c) 2012-2013 QUALCOMM Technologies Incorporated, All Rights Reserved.
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/rpm.bf/1.8/core/api/pmic/pm/pm_pon.h#1 $
  $DateTime: 2016/11/03 00:13:13 $ 

when       who     what, where, why
--------   ---     ----------------------------------------------------------
04/10/13   kt      Added PMIC Watchdog config support  
02/27/13   kt      Added PON IRQ related APIs  
12/06/12   hw      Remove comdef.h and use com_dtypes.h
22/11/12   umr     Created PON API.
===========================================================================*/
/*===========================================================================

                        HEADER FILES

===========================================================================*/
#include "pm_err_flags.h"
#include "com_dtypes.h"
#include "pm_resources_and_types.h"

/*===========================================================================

                        TYPE DEFINITIONS 

===========================================================================*/
/*! \enum pm_pon_reset_cfg_type
   \brief Reset configure type.
 */
typedef enum
{
  PM_PON_RESET_CFG_WARM_RESET,
  PM_PON_RESET_CFG_NORMAL_SHUTDOWN,
  /* Shutdown to a state of main battery removal */
  PM_PON_RESET_CFG_D_VDD_BATT_REMOVE_SHUTDOWN,
   /* Shutdown to a state of main battery and coin cell removal*/
  PM_PON_RESET_CFG_X_VDD_COIN_CELL_REMOVE_SHUTDOWN,
   /* Shutdown + Auto pwr up */
  PM_PON_RESET_CFG_HARD_RESET,
  /* Main Batt and coin cell remove Shutdown + Auto pwr up */
  PM_PON_RESET_CFG_D_VDD_BATT_REMOVE_HARD_RESET,
  PM_PON_RESET_CFG_X_VDD_COIN_CELL_REMOVE_HARD_RESET,
  PM_PON_RESET_CFG_IMMEDIATE_X_VDD_COIN_CELL_REMOVE_SHUTDOWN,
  /* Warm Reset and Main Batt/coin cell remove Shutdown */
  PM_PON_RESET_CFG_WARM_RESET_AND_D_VDD_BATT_REMOVE_SHUTDOWN,
  PM_PON_RESET_CFG_WARM_RESET_AND_X_VDD_COIN_CELL_REMOVE_SHUTDOWN,
  PM_PON_RESET_CFG_WARM_RESET_AND_SHUTDOWN,
   /* Warm Reset then Main Batt/coin cell remove Shutdown + Auto pwr up */
  PM_PON_RESET_CFG_WARM_RESET_THEN_HARD_RESET,
  PM_PON_RESET_CFG_WARM_RESET_THEN_D_VDD_BATT_REMOVE_HARD_RESET,
  PM_PON_RESET_CFG_WARM_RESET_THEN_X_VDD_COIN_CELL_REMOVE_HARD_RESET,
  PM_PON_RESET_CFG_INVALID  
}pm_pon_reset_cfg_type;
  
/*===========================================================================

                        HEADER FILES

===========================================================================*/

/**
 * @brief Configure PON PMIC Watchdog reset source
 * 
 * @param pmic_device_index When the target has more than
 *          one pmic, this is the index of the PMIC in which
 *          the power on module is physically located. The device
 *          index starts at zero.
 *  
 * @param s1_timer: Select S1 timer in seconds for bark.
 *            Supported time in seconds: 0 to 127
 *  
 * @param s2_timer: Select S2 timer in seconds for bite. This is
 *                the time after bark S1.
 *            Supported time in seconds: 0 to 127
 *  
 * @param reset_cfg_type: Configure the type of reset to be 
 *                      performed on the event.
 *  
 * @return pm_err_flag_type
 */
pm_err_flag_type
pm_pon_wdog_cfg(uint8 pmic_device_index, uint32 s1_timer, uint32 s2_timer, pm_pon_reset_cfg_type reset_cfg_type);

/**
 * @brief PON PMIC Watchdog reset Control (enable/disable)
 * 
 * @param pmic_device_index When the target has more than
 *          one pmic, this is the index of the PMIC in which
 *          the power on module is physically located. The device
 *          index starts at zero.
 *                   
 * @param enable Select enable / disable 
 * 
 * @return pm_err_flag_type
 */
pm_err_flag_type
pm_pon_wdog_enable(uint8 pmic_device_index, pm_on_off_type enable);

/**
 * @brief Clears the PMIC Watchdog timer (Pets the PMIC 
 *        Watchdog).
 * 
 * @param pmic_device_index When the target has more than
 *          one pmic, this is the index of the PMIC in which
 *          the power on module is physically located. The device
 *          index starts at zero. 
 * 
 * @return pm_err_flag_type
 */
pm_err_flag_type
pm_pon_wdog_pet(uint8 pmic_device_index);

/**
 * @brief Get PON PMIC Watchdog configuration. 
 * 
 * @param pmic_device_index When the target has more than
 *          one pmic, this is the index of the PMIC in which
 *          the power on module is physically located. The device
 *          index starts at zero.
 *  
 * @param s1_timer:  pointer to a S1 timer in seconds for bark.
 *            Supported time in seconds: 0 to 127
 *  
 * @param s2_timer:  pointer to a S2 timer in seconds for bite. This is
 *                the time after bark S1.
 *            Supported time in seconds: 0 to 127
 *
 * @param  reset_type:  pointer to the wdog reset reasone type. 
 *                Refer enum pm_pon_reset_cfg_type.
 *  
 * @return pm_err_flag_type
 */
pm_err_flag_type
pm_pon_wdog_get_cfg
(
  uint8 pmic_device_index,
  uint8* s1_timer,
  uint8* s2_timer,
  uint8* reset_type
);

/**
 * @brief This function sets the QDSS debug flag. 
 * 
 * @param[in] pmic_device_index. Primary PMIC: 0 Secondary PMIC: 1 
 *
 * @return  pm_err_flag_type 
 *          PM_ERR_FLAG__FEATURE_NOT_SUPPORTED = Feature not
 *          available on this version of the PMIC.
 *          PM_ERR_FLAG__PAR1_OUT_OF_RANGE = Device Index out of
 *          range.
 *          PM_ERR_FLAG__SUCCESS = SUCCESS.
 *
 */
pm_err_flag_type 
pm_pon_qdss_set_flag(uint8 pmic_device_index);

/**
 * @brief This function clears the QDSS debug flag.
 * 
 * @param[in] pmic_device_index. Primary PMIC: 0 Secondary PMIC: 1 
 *
 * @return  pm_err_flag_type 
 *          PM_ERR_FLAG__FEATURE_NOT_SUPPORTED = Feature not
 *          available on this version of the PMIC.
 *          PM_ERR_FLAG__PAR1_OUT_OF_RANGE = Device Index out of
 *          range.
 *          PM_ERR_FLAG__SUCCESS = SUCCESS.
 *
 */
pm_err_flag_type 
pm_pon_qdss_clear_flag(uint8 pmic_device_index);

/**
 * @brief This function returns the QDSS debug flag status on 
 *        whether the debugging has to be enabled or not and
 *        this status needs to be explicitly cleared using the
 *        pm_pon_qdss_clear_flag API.
 * 
 * @param[in] pmic_device_index. Primary PMIC: 0 Secondary PMIC: 1
 * @param[out] status:  
 *                QDSS debug status (returns TRUE if QDSS debug
 *                enabled, FALSE otherwise).
 *
 *
 * @return  pm_err_flag_type 
 *          PM_ERR_FLAG__INVALID_POINTER = Null pointer passed
 *          in as an argument.
 *          PM_ERR_FLAG__FEATURE_NOT_SUPPORTED = Feature not
 *          available on this version of the PMIC.
 *          PM_ERR_FLAG__PAR1_OUT_OF_RANGE = Device Index out of
 *          range.
 *          PM_ERR_FLAG__SUCCESS = SUCCESS.
 *
 */
pm_err_flag_type 
pm_pon_qdss_get_flag(uint8 pmic_device_index, boolean *status);

#endif // PM_PON__H
