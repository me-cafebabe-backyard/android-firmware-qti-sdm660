#ifndef _I2CPLATSVC_H_
#define _I2CPLATSVC_H_
/*=============================================================================

  @file   I2cPlatSvc.h

   This file contains the API for the platform services.
 
   Copyright (c) 2011-2016 Qualcomm Technologies, Incorporated.
                  All rights reserved.
   Qualcomm Technologies, Confidential and Proprietary.

=============================================================================*/
/*=============================================================================
EDIT HISTORY FOR MODULE
  ===========================================================================
 $Header: //components/rel/core.qdsp6/1.0.c2/buses/i2c/src/drv/I2cPlatSvc.h#1 $
When     Who    What, where, why
-------- ---    -----------------------------------------------------------
10/14/16 VG     Updated the Copy Rights and remove IST code
09/27/16 VG     Added macro to support the num of instance
=============================================================================*/

/*-------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------*/

#include "I2cPlatSvcTypes.h"

#include "I2cTypes.h"
#include "I2cError.h"

#define I2C_NUM_PLATFORM_DEVICES         (1)


/*-------------------------------------------------------------------------
 * Type Declarations
 * ----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Function Declarations and Documentation
 * ----------------------------------------------------------------------*/

/** @brief Releases data structures necessary to support the target calls.

    @param[in] pPlat platform device pointer.

    @return          int32 .
  */
int32 I2cPlat_ReadPlatConfig();

 
/** @brief Releases data structures necessary to support the target calls.

    @param[in] pPlat platform device pointer.

    @return          int32 .
  */
int32
I2cPlat_DeInitTarget
(
   I2cPlat_DescType *pPlat
);

/** @brief Initializes data structures necessary to support the target calls.

    @param[in] pPlat  pointer to platform device structure.
    @param[in] pProps pointer to platform properties.

    @return          int32 .
  */
int32
I2cPlat_InitTarget
(
   I2cPlat_DescType      *pPlat ,
   I2cPlat_PropertyType  *pProps
);

/** @brief Resets resources like bam pipes following a qup core reset.

    @param[in] pPlat platform device pointer.

    @return          int32 .
  */
int32
I2cPlat_ResetTarget
(
   I2cPlat_DescType *pPlat
);

/** @brief Returns the QUP virtual address.

    @param[in]  pPlat platform device pointer.

    @return          int32 .
  */
uint8*
I2cPlat_GetQupAddress
(
   I2cPlat_DescType      *pPlat
);


/** @brief sets the vote for PNOC.

    @param[in] pDev     Pointer to platform device structure.
    @param[in] hClnt    Npa client handle.
    @param[in] uIb      PNOC IB value.
    @param[in] uAb      PNOC AB value.

    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2CPLAT_Error.
  */
int32
I2cPlat_AddPnocVote
(
   I2cPlat_DescType *pPlat,
   uint64                        uIb,
   uint64                        uAb

);

/** @brief unvote for PNOC.


    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2CPLAT_Error.
  */

int32
I2cPlat_RemovePnocVote
(
   void
);

/** @brief Enables the I2C clocks.

    @param[in]  pPlat platform device pointer.

    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2cPlat_Error.
  */
int32 I2cPlat_VoteI2cClkOn
(
   I2cPlat_DescType      *pPlat
);

/** @brief Disables the I2C clocks.

    @param[in]  pPlat platform device pointer.

    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2cPlat_Error.
  */
int32 I2cPlat_VoteI2cClkOff
(
   I2cPlat_DescType      *pPlat
);


#endif /* _I2CPLATSVC_H_ */

