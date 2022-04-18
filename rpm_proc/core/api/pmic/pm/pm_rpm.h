#ifndef PM_RPM_H
#define PM_RPM_H

/*! \file pm_rpm.h
 *  \n
 *  \brief Contains PMIC external public interfaces.
 *  \n
 *  \n &copy; Copyright (c) 2013-2015 QUALCOMM Technologies Incorporated, All Rights Reserved.
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  
when       who     what, where, why
--------   ---     ----------------------------------------------------------
02/20/17   as      added pm_npa_rpm_set_auto_mode_thr() API to get threshold freq (CR#1114608)
09/29/15   aks     Created.
===========================================================================*/

/*===========================================================================

                        PMIC INCLUDE FILES

===========================================================================*/
#include "pmapp_npa.h"

/*===========================================================================

                        DEFINITIONS

===========================================================================*/

/**
*
* @brief Votes for certain SMPSs in/out of auto mode.
* @param ddr_cfg an entry that is maintained in a ddr freq- mode table 
* @note The implementation of this API is target specific.
*
* @return pmic error flag
*/
pm_err_flag_type pm_npa_rpm_smps_auto_mode_config (uint32  ddr_cfg);

/**
* @brief Use to detect threshold freq for external buck
* @param lp4x_buck_auto_mode_thr that is maintaned in ddr_automode_cfg table
* @note The implementation of this API is target specific.
*
* @return return err_flag and update threshold freq in pm_npa_rpm_smps_auto_mode_config() API in RPM 
*/
pm_err_flag_type pm_npa_rpm_set_auto_mode_thr (uint32 lp4x_buck_auto_mode_thr);

/**
*
* @brief Verfies if certain SMPS regulators are in the right SW mode.
* @param ddr_cfg an entry that is maintained in a ddr freq- mode table 
* @note The implementation of this API is target specific.
*
* @return pmic error flag
*/
pm_err_flag_type pm_npa_rpm_verify_smps_mode(uint32  ddr_cfg);

#endif // PM_RPM_H

