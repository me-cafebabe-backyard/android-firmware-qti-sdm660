#ifndef __SMMU_LIB_H__
#define __SMMU_LIB_H__

/*==============================================================================
@file SMMULib.h

    This file contains the function declarations for the LIB interface that
    other drivers can use to interact with the SMMUDxe driver.

        Copyright (c) 2008,2010,2014 Qualcomm Technologies, Inc.
        All Rights Reserved.
        Qualcomm Confidential and Proprietary

==============================================================================*/
/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 03/19/15   amo     Created

=============================================================================*/

/*------------------------------------------------------------------------------
* Include Files
*-----------------------------------------------------------------------------*/
#include "SMMUTypes.h"
#include <Protocol/EFISMMUProtocol.h>
#include <Library/UefiBootServicesTableLib.h>

/*------------------------------------------------------------------------------
* Function Declarations
*-----------------------------------------------------------------------------*/

/* Map/Unmap Functions */

SMMUError_t SMMU_Map(SMMUClientID_t client, const SMMUMapAttr_t *pMapAttrvar);

SMMUError_t SMMU_Unmap(SMMUClientID_t client, uint64_t inputAddrvar, 
      uint64_t sizevar);

void SMMU_Init(void);

#endif /* __SMMU_LIB_H__ */
