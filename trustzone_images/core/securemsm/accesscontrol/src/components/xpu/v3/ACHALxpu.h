#ifndef AC_HAL_XPU_H
#define AC_HAL_XPU_H

/*===========================================================================
Copyright (c) 2010-2016 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.tz/1.0.7.1/securemsm/accesscontrol/src/components/xpu/v3/ACHALxpu.h#1 $
$DateTime: 2020/01/14 12:35:09 $
$Author: pwbldsvc $

when       who     what, where, why
--------   ---     ----------------------------------------------------------

============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "HALxpu3.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
#define ACHAL_xpu_GetResourceGroupConfig(a,b,c) HAL_xpu3_GetResourceGroupConfig(a,b,c)
#define ACHAL_xpu_GetDeviceParameters(a,b) HAL_xpu3_GetDeviceParameters(a,b)
#define ACHAL_xpu_XPUDeviceParamsType  HAL_xpu3_XPUDeviceParamsType
#define ACHAL_xpu_ResourceGroupConfigType  HAL_xpu3_ResourceGroupConfigType
/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/
/*
typedef HAL_xpu3_XPUDeviceParamsType ACHAL_xpu_XPUDeviceParamsType;
typedef HAL_xpu3_ResourceGroupConfigType ACHAL_xpu_ResourceGroupConfigType;
*/
/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/

#endif /* AC_HAL_XPU_H */
