/*==============================================================================
$Header: //components/rel/avs.adsp/2.8/afe/drivers/afe/common/stub_src/lpi_gpio/afe_lpi_gpio_driver_stub.cpp#2 $
$DateTime: 2017/05/01 08:25:18 $
$Author: pwbldsvc $
$Change: 13178082 $
$Revision: #2 $

FILE:     afe_lpi_gpio_driver_stub.cpp

DESCRIPTION: Stub for LPI GPIO configuration functions

PUBLIC CLASSES:  Not Applicable

INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A

Copyright (c) 2017 QUALCOMM Technologies, Inc. (QTI)
All Rights Reserved.
QUALCOMM Proprietary/GTDR
==============================================================================*/
/*============================================================================
EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order. Please
use ISO format for dates.

$Header: //components/rel/avs.adsp/2.8/afe/drivers/afe/common/stub_src/lpi_gpio/afe_lpi_gpio_driver_stub.cpp#2 $

when       who     what, where, why
--------   ---     -------------------------------------------------------
01/06/17    sudhir      Created file

============================================================================*/

/*=====================================================================
 Includes
 ======================================================================*/

#include "adsp_error_codes.h"
#include  "AFEDevCommon.h"


ADSPResult afe_device_lpi_gpio_init(gpio_int_properties_t *gpio_int_prop_ptr)
{
   return ADSP_EUNSUPPORTED;
}

ADSPResult afe_device_lpi_gpio_deinit(gpio_int_properties_t *gpio_int_prop_ptr)
{
   return ADSP_EUNSUPPORTED;
}

