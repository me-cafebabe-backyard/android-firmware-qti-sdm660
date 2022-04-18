/*========================================================================
Copyright (c) 2018 QUALCOMM Technologies, Inc.  All Rights Reserved.
QUALCOMM Technologies, Inc Proprietary.  Export of this technology or software is regulated
by the U.S. Government, Diversion contrary to U.S. law prohibited.
 ====================================================================== */

 /*============================================================================
EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order. Please
use ISO format for dates.

when       who     what, where, why
--------   ---     -------------------------------------------------------
01/12/18   saxena  Created file

============================================================================*/

/*=====================================================================
 Includes
 ======================================================================*/
#include "clock_manager.h"

/*
 * On targets without user PD, no DAL device proxy is required
 * during PD restart.
 * Returning unsupported will cause PD restart to continue.
 */
ADSPResult afe_clock_manager_device_proxy(DalDeviceHandle *pHandle)
{
	return ADSP_EUNSUPPORTED;
}
