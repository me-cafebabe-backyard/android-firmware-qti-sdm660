/*
===========================================================================

FILE:   I2cSysExtUefi.c

DESCRIPTION:
    This file contains the implementation for the QUP OS Services 
    Interface: IQupI2cDevice 

===========================================================================

        Edit History


When     Who    What, where, why
-------- ---    -----------------------------------------------------------
02/01/17 VG     Copyright updated 
12/02/12 UR     Created

===========================================================================
    Copyright (c) 2011-2017 Qualcomm Technologies, Incorporated.
                        All rights reserved.
    Qualcomm Technologies, Confidential and Proprietary.

===========================================================================
*/

#include "I2cSys.h"

/**
   @brief Convert Virtual to Physical address
 
   This function converts virtual to physical address
  
   @param[in] pVirtMem  Pointer to virtual memory.
   @param[in] uSize     Size of memory buffer.
 
   @return I2CSYS_RESULT_OK on success, error code on error
 */
uint32 I2CSYS_VirtToPhys
(
   uint8       *pVirtMem,
   uint64      *pPhysAddress
)
{
  return I2CSYS_RESULT_OK;
}



