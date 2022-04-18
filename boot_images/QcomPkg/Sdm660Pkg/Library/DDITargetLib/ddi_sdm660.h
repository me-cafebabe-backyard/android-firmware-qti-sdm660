/*==================================================================
 *
 * FILE:        ddi_sdm660.c
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
 * 2016-12-15      zhz     Initial file creation
 */


#include "ddi_firehose.h"
#include "boot_sbl_if.h"
#include "pm_config_sbl.h"

#define DDI_PLATFORM "SDM660"
#define DDI_VERSION  1

void ddi_entry(boot_pbl_shared_data_type *pbl_shared);

