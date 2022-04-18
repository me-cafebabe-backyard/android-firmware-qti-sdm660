/*==============================================================================
$Header: //components/rel/avs.adsp/2.8/afe/drivers/afe/timestamp/common/stub_src/hal_timestamp.cpp#2 $
$DateTime: 2017/02/13 02:08:05 $
$Author: pwbldsvc $
$Change: 12428383 $
$Revision: #2 $

FILE:     hal_vfr_driver.cpp

DESCRIPTION: VFR register programming

PUBLIC CLASSES:  Not Applicable

INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A

Copyright (c) 2013-2014,2017 QUALCOMM Technologies, Incorporated.
All Rights Reserved.
QUALCOMM Technologies Proprietary. 
==============================================================================*/
/*============================================================================
EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order. Please
use ISO format for dates.

$Header: //components/rel/avs.adsp/2.8/afe/drivers/afe/timestamp/common/stub_src/hal_timestamp.cpp#2 $

when       who     what, where, why
--------   ---     -------------------------------------------------------
7/19/2012  RP      created

============================================================================*/

#include "hal_timestamp.h"

ts_hw_drv_t  ts_hw_drv_global;

/*==========================================================================
  Macro\Constant definitions
  ========================================================================== */

ADSPResult ts_hw_drv_init()
{
   return ADSP_EUNSUPPORTED;
}

void hal_ts_release_ts_mux(uint32_t mux_id)
{
   return;
}
