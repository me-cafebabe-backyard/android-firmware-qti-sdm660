#ifndef _QUPLOG_H_
#define _QUPLOG_H_
/*
===========================================================================

FILE:   QupLog.h

DESCRIPTION:
    This file contains the API for the QUP Log services 


===========================================================================

        Edit History


When     Who    What, where, why
-------- ---    -----------------------------------------------------------
02/01/17 VG     Copyright updated 
03/31/14 UR     Added CR to logs
07/10/12 LK     Created

===========================================================================
    Copyright (c) 2012-2017 Qualcomm Technologies, Incorporated.
                        All rights reserved.
    Qualcomm Technologies, Confidential and Proprietary.

===========================================================================
*/

#include "QupTypes.h"
#include "I2cPlatLog.h"

typedef void* QUPLOG_DEV_IMP_HANDLE;

typedef struct QupLogSvcType
{
   QUPLOG_DEV_IMP_HANDLE (*pfnGetReadHandle)(uint32 uDevAddr);
   QUPLOG_DEV_IMP_HANDLE (*pfnGetWriteHandle)(uint32 uDevAddr);
} QupLogSvcType;

#endif //_QUPLOG_H_

