/*
===========================================================================

FILE:         ddr_params.c

DESCRIPTION:
  Information of DDR devices supported by target.

===========================================================================

                             Edit History

$Header: //components/rel/rpm.bf/1.8/core/boot/ddr/platform/sdm660/params/v4/ddr_params.c#1 $

when       who     what, where, why
--------   ---     --------------------------------------------------------
05/20/14   tw      renamed lp4_shared_data to ddrsns_share_data for better 
                   future compatibility
03/12/14   sr      Initial revision.

===========================================================================
                   Copyright 2014 Qualcomm Technologies Incorporated
                              All Rights Reserved
                     Qualcomm Confidential and Proprietary
===========================================================================
*/

/*==============================================================================
                                    INCLUDES
==============================================================================*/
#include "HAL_SNS_DDR.h"
#include "ddr_params.h"
#include "stringl/stringl.h"
#include <stddef.h>

/*==============================================================================
                                      DATA
==============================================================================*/
extern char Image$$DDR_STRUCT_DATA$$Base[];
DDR_STRUCT *ddrsns_share_data = (DDR_STRUCT *)Image$$DDR_STRUCT_DATA$$Base;

/*==============================================================================
                                   FUNCTIONS
==============================================================================*/




/* ============================================================================
**  Function : ddr_get_detected_params
** ============================================================================
*/
/**
*   @brief
*   Get DDR device parameters.
*
*   @param[in]  interface_name  Interface to get DDR device parameters for
*
*   @return
*   DDR device parameters
*
*   @dependencies
*   None
*
*   @sa
*   None
*
*   @sa
*   None
*/
struct detected_ddr_device_params *ddr_get_detected_params(DDR_CHANNEL interface_name)
{
  struct detected_ddr_device_params *ddr_detected_params;
  
  ddr_detected_params = (interface_name == DDR_CH0) ? &(ddrsns_share_data->detected_ddr_device[0])
															: &(ddrsns_share_data->detected_ddr_device[1]);

  return ddr_detected_params;
} /* ddr_get_detected_params */


