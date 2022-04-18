/**
 * @file:  SpmiHal.c
 * 
 * Copyright (c) 2013-2014 by Qualcomm Technologies Incorporated. All Rights Reserved.
 * 
 * $DateTime: 2016/08/19 05:58:45 $
 * $Header: //components/rel/boot.xf/1.4/QcomPkg/Library/SPMILib/src/core/hal/SpmiHal.c#2 $
 * $Change: 11185940 $ 
 * 
 *                              Edit History
 * Date     Description
 * -------  -------------------------------------------------------------------
 * 1/20/15  Multiple bus support
 * 10/1/13  Initial Version
 */

#include "SpmiHal.h"
#include "SpmiLogs.h"
#include "SpmiOs.h"

//******************************************************************************
// Global Data
//******************************************************************************


//******************************************************************************
// Public API Functions
//******************************************************************************

Spmi_Result SpmiHal_Init()
{
    return SPMI_SUCCESS;
}

