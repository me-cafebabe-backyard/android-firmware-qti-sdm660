
/*
===========================================================================

FILE:   I2cULog.c

DESCRIPTION:
    This file contains functions for I2c logging  driver
 
===========================================================================

        Edit History


When     Who    What, where, why
-------- ---    -----------------------------------------------------------
02/01/17 VG     Copyright updated
03/31/14 UR     64 bit support added
11/02/11 SG     Created

===========================================================================
    
    Copyright (c) 2011-2017 Qualcomm Technologies, Incorporated.
                        All rights reserved.
    Qualcomm Technologies, Confidential and Proprietary.

===========================================================================
*/

#include "I2cLog.h"



// Initialization 
void 
I2cLog_Init
(
   void *uPlatDevId,
   I2CLOG_DevType **ppLogDev
)
{
}

void I2cLog_DeInit(I2CLOG_DevType *pLogDev)
{
}

void I2cLog_AssociateBlockAddress(I2CLOG_DevType *pLogDev, uint8 *uDevAddr)
{
}

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
)
{
        
}


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
)
{
}

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
)
{
}


