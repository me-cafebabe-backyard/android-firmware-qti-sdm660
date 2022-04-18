/**
 * @file:  PmicArb.h
 * @brief: 
 * 
 * Copyright (c) 2013 by Qualcomm Technologies Incorporated. All Rights Reserved.
 * 
 * $DateTime: 2016/11/03 00:13:13 $
 * $Header: //components/rel/rpm.bf/1.8/core/pmic/spmi/src/core/hal/PmicArb.h#1 $
 * $Change: 11690628 $ 
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
Spmi_Result PmicArb_UpdateCache(SpmiInfo *pSpmiInfo);
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
