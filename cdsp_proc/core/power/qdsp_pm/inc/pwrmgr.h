/*
* Copyright (c) 2014 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.
*/

/*
 * pwrmgr.h
 *
 *  Created on: Feb 13, 2012
 *      Author: yrusakov
 */

#ifndef PWRMGR_H_
#define PWRMGR_H_

#include "requestmgr.h"


Adsppm_Status PWR_Init(void);

Adsppm_Status PWR_ProcessRequest(coreUtils_Q_Type *pPwrReqQ);


#endif /* PWRMGR_H_ */

