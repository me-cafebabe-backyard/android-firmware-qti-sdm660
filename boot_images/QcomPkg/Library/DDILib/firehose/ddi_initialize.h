/*==================================================================
 *
 * FILE:        ddi_initialize.h
 *
 * DESCRIPTION:
 *
 *
 *        Copyright © 2016 Qualcomm Technologies Incorporated.
 *               All Rights Reserved.
 *               QUALCOMM Proprietary
 *==================================================================*/

/*===================================================================
 *
 *                       EDIT HISTORY FOR FILE
 *
 *   This section contains comments describing changes made to the
 *   module. Notice that changes are listed in reverse chronological
 *   order.
 *
 *
 * YYYY-MM-DD   who     what, where, why
 * ----------   ---     ----------------------------------------------
 * 2016-12-18   zhz      Realize ddi_entry() in target related file
 * 2015-06-24   sng      Initial checkin
 */

#ifndef DDI_INITIALIZE_H
#define DDI_INITIALIZE_H

#include "pm_config_sbl.h"

#include BOOT_PBL_H

void ddi_init_hw();
extern void ddi_entry(boot_pbl_shared_data_type *pbl_shared);

#endif

