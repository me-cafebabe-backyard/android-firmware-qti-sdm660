/*=============================================================================

  FILE:   I2cPlatSvc.c

  OVERVIEW: This file contains the implementation for the platform services.
 
  Copyright (c) 2011-2016 Qualcomm Technologies, Incorporated.
                  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/
/*=============================================================================
EDIT HISTORY FOR MODULE

$Header: //components/rel/core.qdsp6/1.0.c2/buses/i2c/src/drv/I2cPlatSvc.c#1 $
$DateTime: 2020/02/10 01:57:30 $$Author: pwbldsvc $
When     Who    What, where, why
-------- ---    -----------------------------------------------------------
04/08/16 VG     Updated clockID names
07/17/13 LK     Added xml properties.
09/26/11 LK     Created
=============================================================================*/

/*-------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------*/

#include "I2cPlatSvc.h"
#include "I2cError.h"
#include "uClock.h"

/*-------------------------------------------------------------------------
 * Externalized Function Definitions
 * ----------------------------------------------------------------------*/

/** @brief Enables the I2C clocks.
   
    @param[in] pPlat platform device pointer.
    
    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2cPlat_Error.
  */
int32 I2cPlat_VoteI2cClkOn
(
   I2cPlat_DescType *pPlat
)
{
   
   if ( !uClock_EnableClock(pPlat->props.QupHClkId) ) {
      return I2CPLAT_ERROR_FAILED_TO_ENABLE_AHB_CLK;     
   }
   if ( !uClock_EnableClock(pPlat->props.QupAppClkId) ) {
      return I2CPLAT_ERROR_FAILED_TO_ENABLE_APPS_CLK;     
}

   return I2C_RES_SUCCESS;    
}

/** @brief Disables the I2C clocks.
    @param[in] pPlat platform device pointer.
    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2cPlat_Error.
  */
int32 I2cPlat_VoteI2cClkOff
(
   I2cPlat_DescType      *pPlat
)
{
   
   if ( !uClock_DisableClock(pPlat->props.QupHClkId) ) {
      return I2CPLAT_ERROR_FAILED_TO_DISABLE_AHB_CLK;     
   }
   if ( !uClock_DisableClock(pPlat->props.QupAppClkId) ) {
      return I2CPLAT_ERROR_FAILED_TO_DISABLE_APPS_CLK;     
}

   return I2C_RES_SUCCESS;
}



