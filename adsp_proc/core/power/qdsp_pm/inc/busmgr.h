/*
* Copyright (c) 2014 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.
*/

/*
 * busmgr.h
 *
 *  Created on: Feb 13, 2012
 *      Author: yrusakov
 */

#ifndef BUSMGR_H_
#define BUSMGR_H_

#include "requestmgr.h"


/**
 * @fn BusMgr_Init - bus management init
 */
Adsppm_Status BusMgr_Init(void);

/**
 * @fn BusMgr_ProcessRequest - bus management main function
 */
Adsppm_Status BusMgr_ProcessRequest(coreUtils_Q_Type *pBWReqQ);

/**
 * @fn BusMgr_GetAggregatedBwInfo - Get function for DDR ab/ib values
 */
Adsppm_Status BusMgr_GetAggregatedBwInfo(AdsppmInfoAggregatedBwType *pBusInfo);

/**
 * @fn BusMgr_GetCompensatedBw- Returns the total requested BW from compensated
 *                              request types, for the specified bus route.
 *                              The output, in bytes/second, is written to the
 *                              pointer provided in pTotalRequestedBw parameter.
 */
Adsppm_Status BusMgr_GetCompensatedBw(coreUtils_Q_Type* pBwRequestQueue,
    AdsppmBusRouteType* pRoute, uint64* pTotalRequestedBw);

/**
 * @fn busMgrRegisterEvents - bus management register events with other managers
 */

Adsppm_Status busMgrRegisterEvents (void);

/**
 * @fn BusMgr_GetCompensatedFudgedBwValue- Returns compensated external bw after applying v2 fudge factor calculation. Updated Ab/Ib values are returned in pAb, pIb pointers provided as arguments
 */

Adsppm_Status BusMgr_GetCompensatedFudgedBwValue(
    coreUtils_Q_Type* pBwRequestQueue,
    uint64* pAb, 
    uint64* pIb,
    AsicCompensatedBWFudgeFactor *pcompensatedBWFudgeFactorValues
    );



#endif /* BUSMGR_H_ */

