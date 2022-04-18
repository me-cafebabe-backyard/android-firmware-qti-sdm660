#ifndef _I2CLOG_H_
#define _I2CLOG_H_
/*
===========================================================================

FILE:   I2cLog.h

DESCRIPTION:
    This file contains the API for the I2C Log services 


===========================================================================

        Edit History


When     Who    What, where, why
-------- ---    -----------------------------------------------------------
02/01/17 VG     Copyright updated
03/31/14 UR     64 bit support added
07/10/12 LK     Created

===========================================================================
    Copyright (c) 2012-2017 Qualcomm Technologies, Incorporated.
                        All rights reserved.
    Qualcomm Technologies, Confidential and Proprietary.

===========================================================================*/

#include "I2cTransfer.h"
#include "I2cTransferCfg.h"
#include "I2cTypes.h"
#include "I2cError.h"
#include "I2cPlatLog.h"

struct I2CLOG_DevType
{
   void          *uPlatDevId;
   uint8         *uDevAddr;

   boolean        bInitialized;
   struct I2CLOG_DevType *pNext;
};

typedef struct I2CLOG_DevType I2CLOG_DevType;


extern void I2cLog_AssociateBlockAddress(I2CLOG_DevType *pLogDev, uint8 *uDevAddr);
extern void I2cLog_Init(void *uPlatDevId, I2CLOG_DevType **ppLogDev);
extern void I2cLog_DeInit(I2CLOG_DevType *pLogDev);

/** @brief logs the transfers in a sequence.

    @param[in] pLogDev        Pointer to log structure.
    @param[in] pClntCfg       Pointer to Client configuration.
  
    @return                   Nothing.
  */
void
I2CLOG_LogCltCfgData
(
   I2CLOG_DevType                      *pLogDev,
   I2cClientConfig                     *pClntCfg         
);

/** @brief logs the transfers in a sequence.

    @param[in] pLogDev        Pointer to log structure.
    @param[in] pTransfer      Pointer to transfer data.
  
    @return                   Nothing.
  */
void
I2CLOG_LogTransferData
(
   I2CLOG_DevType                      *pLogDev,
   I2cTransfer                         *pTransfer         
);

/** @brief logs the transfers in a sequence.

    @param[in] pLogDev        Pointer to log structure.
    @param[in] pSeq           Pointer to sequence.
  
    @return                   Nothing.
  */
void
I2CLOG_LogSeqData
(
   I2CLOG_DevType                      *pLogDev,
   I2cSequence                         *pSeq         
);

#endif //_I2CLOG_H_

