#ifndef PM_AC_TZ_H
#define PM_AC_TZ_H

/*! \ file pm_ac_tz.h
*
 * \brief   <Brief Comment Block/>
 * \details <Detailed Comment Block/>
 * \n &copy; Copyright 2015 QUALCOMM Technolgoies Incorporated, All Rights Reserved
 */

/*===================================================================
                    EDIT HISTORY FOR MODULE
 This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.tz/1.0.7.1/systemdrivers/pmic/framework/inc/pm_ac_tz.h#1 $
$Author: pwbldsvc $

when       who     what, where, why
--------    ---     ------------------------------------------------
01/13/15    vtw     Created.
====================================================================*/

#include "SpmiCfg.h"
#include "HALxpu2.h"   // TODO revise me
#include "AccessControlTz.h"
// #include "pm_lib_err.h"


/* ============================================================================
**    Function Prototype.
** ==========================================================================*/

/**
 * @brief Create a MPU mapping table.
 *
 * @details This function creates an mpu mapping table .
 * It does not perform HW Read/Write. It instead sends message requesting RPM
 * for voltage change.
 *
 *  @param cfg_ptr [in/out]  Pointer to mpu table.
 *  @param rg_ptr [in]  Pointer to SPMI RGs array.
 *  @param rg_size [in]  Size of SPMI RGs array.
 *
 * @return pm_err_flag_type
 *  PM_ERR_FLAG__SUCCESS -- on success otherwise PMIC error code. \n
 * @dependencies
 *  None.
 * @sa None.
 *
 */
uint32 pm_mpu_mapping
(
  tzbsp_mpu_rg_t* cfg_ptr,
  const SpmiCfg_RGConfig* rg_ptr,
  uint32 rg_size
);


#endif // PM_AC_TZ_H
