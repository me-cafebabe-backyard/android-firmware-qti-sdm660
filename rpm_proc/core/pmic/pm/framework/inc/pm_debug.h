#ifndef __PM_DEBUG_H__
#define __PM_DEBUG_H__

/*! \file pm_debug.h
 *  
 *  \brief This file contain commonly used PMIC utils related function prototype.
 *  \details This file contain PMIC timetick related helper functions and
 *           wrapper function of DALSYS_Malloc()
 *  
 *    &copy; Copyright 2016 Qualcomm Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/rpm.bf/1.8/core/pmic/pm/framework/inc/pm_debug.h#1 $ 

when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/20/12   hs      Created

===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_rpm_clk_buffer_trans_apply.h"
#include "pm_bob_driver.h"
#include "pm_clk_driver.h"
#include "pm_ldo_driver.h"
#include "pm_pbs_client_driver.h"
#include "pm_pon_driver.h"
#include "pm_smps_driver.h"
#include "pm_vs_driver.h"
#include "pm_droop_detect_internal.h"
#include "pm_rpm_utilities.h"
#include "pm_version.h"
#include "pm_mpm_internal.h"
/*===========================================================================

                        TYPE DEFINITIONS 

===========================================================================*/



/*===========================================================================

                        FUNCTION PROTOTYPES

===========================================================================*/

typedef struct
{
  pm_device_info_type        *pm_device_info_arr;
  /*bob driver*/
  pm_bob_data_type           **pm_bob_data_arr;
  pm_clk_data_type           **pm_clk_data_arr;
  pm_ldo_data_type           **pm_ldo_data_arr;
  pm_pbs_client_data_type    **pm_pbs_client_data_arr;
  pm_pon_data_type           **pm_pon_data_arr;
  pm_smps_data_type          **pm_smps_data_arr;
  pm_vs_data_type            **pm_vs_data_arr;
  /*droop*/
  pm_debug_droop_info_type *pm_debug_droop;
  /*settle*/
  pm_settle_info_type          *vreg_settle_info;
  pm_clk_settle_info_type      *clk_settle_info;
  /*OCP*/
  pm_pwr_ocp_rail_status      *ocp_rail_status;
  uint32                      *pm_ocp_rail_count;
  /*MPM debug info*/
  pm_mpm_debug_info_type      *pm_mpm_debug;
  }pm_debug_info_type;

//extern pm_all_debug pm_debug;

pm_debug_info_type* pm_get_debug_info(void);

pm_err_flag_type pm_debug_info_init(void);

#endif // PM_UTILS_H
