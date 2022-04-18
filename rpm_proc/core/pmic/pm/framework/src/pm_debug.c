/*! \file pm_utils.c
 *  
 *  \brief This file contain commonly used PMIC utils related function implementation.
 *  \details This file contain PMIC timetick related helper functions implementation
 *           and wrapper function of DALSYS_Malloc()
 *  
 *    &copy; Copyright 2016 Qualcomm Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/rpm.bf/1.8/core/pmic/pm/framework/src/pm_debug.c#1 $ 

when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/09/16   al      Created
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_debug.h"

pm_debug_info_type pm_debug;
extern pm_debug_droop_info_type pm_debug_droop;
extern pm_settle_info_type pm_settle_vreg_ok_err_info[PM_SETTLE_LOG_ARRAY_SIZE];
extern pm_clk_settle_info_type pm_settle_clk_ok_err_info;
extern pm_mpm_debug_info_type pm_mpm_debug;

pm_debug_info_type* pm_get_debug_info(void)
{
  return &pm_debug;
}


pm_err_flag_type pm_debug_info_init(void)
{
  pm_debug_info_type *pmic_debug = pm_get_debug_info();
  CORE_VERIFY_PTR(pmic_debug);

  pmic_debug->vreg_settle_info = pm_settle_vreg_ok_err_info ;
  pmic_debug->clk_settle_info = &pm_settle_clk_ok_err_info;
  pmic_debug->pm_debug_droop = &pm_debug_droop ;
  pmic_debug->pm_mpm_debug = &pm_mpm_debug ;

  return PM_ERR_FLAG__SUCCESS;
}
