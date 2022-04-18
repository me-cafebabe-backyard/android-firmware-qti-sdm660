/*
* Copyright (c) 2015 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.
*/

/*
@file: mipsmgr.h
@brief: Header for ADSPPM MIPS/MPPS Manager.

$Header: //components/rel/core.qdsp6/1.0.c2/power/qdsp_pm/inc/mipsmgr.h#1 $
*/

#ifndef MIPSMGR_H_
#define MIPSMGR_H_

#include "requestmgr.h"


Adsppm_Status MIPS_Init(void);

Adsppm_Status MIPS_ProcessRequest(coreUtils_Q_Type *pMipsReqQ);

uint32 MIPS_GetMppsAggregationInfo(uint32 clientClasses);

Adsppm_Status mipsmgr_GetMppsPerClientClass( MmpmClientClassType clientClass, uint32 *mppsvalue);


#endif /* MIPSMGR_H_ */

