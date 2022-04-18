/*
* Copyright (c) 2014 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.
*/

/*
 * hal_busdrv.h
 *
 *  Created on: Feb 13, 2012
 *      Author: yrusakov
 */

#ifndef HAL_BUSDRV_H_
#define HAL_BUSDRV_H_

#include "adsppm.h"


#define ICBARB_NODE_NAME "/icb/arbiter"
#define SNOC_NODE_NAME   "/clk/snoc"

// Definition of the number of MIPS routes exposed in Bus_IssueBWRequest_MIPS
#define BUS_NUMBER_MIPS_ROUTES 2

AdsppmStatusType Bus_Init(void);

AdsppmStatusType Bus_ReleaseBWRequest_MIPS(void);

AdsppmStatusType Bus_IssueBWRequest_MIPS(AdsppmBusBWRequestValueType *pRequest);

AdsppmStatusType Bus_IssueBWRequest(uint32 num, AdsppmBusBWRequestValueType *pRequest);

AdsppmStatusType Bus_ReleaseBWRequest(uint32 num, AdsppmBusBWRequestValueType *pRequest);

AdsppmStatusType Bus_IssueSnocRequest(uint32 snocVoteMhz);

AdsppmBusBWDataIbAbType Bus_GetRequestedBw(AdsppmBusRouteType *pRoute);


#endif /* HAL_BUSDRV_H_ */

