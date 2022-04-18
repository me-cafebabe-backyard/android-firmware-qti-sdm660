/**
 * @file:  PmicArb.h
 * @brief: 
 * 
 * Copyright (c) 2013-2015 by Qualcomm Technologies Incorporated. All Rights Reserved.
 * 
 * $DateTime: 2016/08/19 05:58:45 $
 * $Header: //components/rel/boot.xf/1.4/QcomPkg/Library/SPMILib/src/core/hal/PmicArb.h#2 $
 * $Change: 11185940 $ 
 * 
 *                              Edit History
 * Date     Description
 * -------  -------------------------------------------------------------------
 * 1/20/15  Multiple bus support
 * 10/1/13  Initial Version
 */
#ifndef PMICARB_H
#define	PMICARB_H

#include "SpmiTypes.h"
#include "SpmiUtils.h"
#include "SpmiHal.h"
#include "SpmiInfo.h"

typedef struct 
{
    uint32 irqStatus;
    uint32 geniStatus;
    uint32 geniCtrl;
} PmicArbHwStatus;


Spmi_Result PmicArb_Init(SpmiInfo *pSpmiInfo);
Spmi_Result PmicArb_FindChannel(SpmiDevInfo *pDev, uint8 slaveId, uint8 periph, uint16* channel);
Spmi_Result PmicArb_InvalidateCache(SpmiDevInfo *pDev);
Spmi_Result PmicArb_UpdateCache(SpmiInfo *pSpmiInfo);
Spmi_Result PmicArb_RemoveCacheEntry(SpmiDevInfo *pDev, uint32 chan);
Spmi_Result PmicArb_AddCacheEntry(SpmiDevInfo *pDev, uint32 chan, uint8 sid, uint8 periph);
Spmi_Result PmicArb_ExecuteCommand(SpmiDevInfo *pDev,
                                   PmicArbCmd cmd,
                                   Spmi_AccessPriority priority,
                                   uint8 owner,
                                   uint16 channel,
                                   uint16 offset,
                                   uint8* data,
                                   uint32 dataLen,
                                   uint32* bytesTransacted);


void PmicArb_GetHwStatus(SpmiDevInfo *pDev, PmicArbHwStatus* status);

#endif
