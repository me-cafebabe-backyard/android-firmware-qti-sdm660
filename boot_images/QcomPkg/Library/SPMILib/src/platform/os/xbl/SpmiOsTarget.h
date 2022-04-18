/**
 * @file:  SpmiOsTarget.h
 * @brief: Implements platform specific functionality
 * 
 * Copyright (c) 2013 by Qualcomm Technologies Incorporated. All Rights Reserved.
 * 
 * $DateTime: 2016/08/19 05:58:45 $
 * $Header: //components/rel/boot.xf/1.4/QcomPkg/Library/SPMILib/src/platform/os/xbl/SpmiOsTarget.h#2 $
 * $Change: 11185940 $ 
 * 
 *                              Edit History
 * Date     Description
 * -------  -------------------------------------------------------------------
 * 10/1/13  Initial Version
 */
#ifndef SPMIOSTARGET_H
#define	SPMIOSTARGET_H

#include "SpmiTypes.h"
#include "DDIClock.h"

typedef struct {
    char   *hwioAddrStr;
    uint32  interruptVec;
} SpmiTargetConfig;

extern DALResult Spmi_ConfigureFetcherChannel(
    DalDeviceHandle *h,
    uint16 periph,
    DALBOOL enableInt,
    uint32 *pChannel);

#endif
