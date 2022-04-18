/*=============================================================================

  FILE:   I2cPlatSvc.c

  OVERVIEW: This file contains the implementation for the platform services.
 
  Copyright (c) 2011-2016 Qualcomm Technologies, Incorporated.
                  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/
/*=============================================================================
EDIT HISTORY FOR MODULE

$Header: //components/rel/core.qdsp6/1.0.c2/buses/i2c/src/drv/I2cPlatSvcInit.c#1 $
$DateTime: 2020/02/10 01:57:30 $$Author: pwbldsvc $
When     Who    What, where, why
-------- ---    -----------------------------------------------------------
10/14/16 VG     Removed  unused code
07/17/13 LK     Added xml properties.
09/26/11 LK     Created
=============================================================================*/

/*-------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------*/

#include "I2cPlatSvc.h"
#include "I2cSys.h"
#include "I2cError.h"
#include "DALDeviceId.h"
#include "uTlmm.h" 
#include "DDIHWIO.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Static Variable Definitions
 * ----------------------------------------------------------------------*/
static uint8                         *pPeriphSsBasePtr  = NULL;
static DalDeviceHandle               *phDalHWIO         = NULL;
static uint32                         uTgtCnt           = 0;

/*-------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 * ----------------------------------------------------------------------*/

/** @brief Configures and enables I2C gpios.
  
    @param[in] pDev     Pointer to platform device structure.
    
    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2cPlat_Error.
  */
static int32
I2cPlat_EnableI2cGpios
(
   I2cPlat_DescType *pPlat
)
{
   uint32 uGpioInd;

   for (uGpioInd = 0; uGpioInd <  pPlat->props.uNumGpios ; uGpioInd++) {

      if (TRUE != uTlmm_ConfigGpio(pPlat->props.aGpioCfg[uGpioInd], UTLMM_GPIO_ENABLE)) {
         return I2CPLAT_ERROR_FAILED_TO_CONFIGURE_GPIO;
      }

   }
   return I2C_RES_SUCCESS;
}

/** @brief disables I2C gpios.
  
    @param[in] pDev     Pointer to platform device structure.
    
    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2cPlat_Error.
  */
static int32
I2cPlat_DisableI2cGpios
(
   I2cPlat_DescType *pPlat
)
{
   uint32 uGpioInd;


   for (uGpioInd = 0; uGpioInd <  pPlat->props.uNumGpios ; uGpioInd++) {

      if (TRUE != uTlmm_ConfigGpio(pPlat->props.aGpioCfg[uGpioInd], UTLMM_GPIO_DISABLE)) {
         return I2CPLAT_ERROR_FAILED_TO_CONFIGURE_GPIO;
      }
   }
   return I2C_RES_SUCCESS; 
}


/** @brief Maps the hwio address space.
  
    @param[in] pPlat    Pointer to platform struct.
    @param[in] pProps   Pointer to platform properties.
    
    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2CPLAT_Error.
  */
static int32
I2cPlat_InitHwio
(
   I2cPlat_DescType *pPlat,
   I2cPlat_PropertyType  *pProps
)
{
   DALResult dalRes;

   if ( NULL == pPeriphSsBasePtr ) {
      dalRes = DAL_DeviceAttach(DALDEVICEID_HWIO, &phDalHWIO);
      if ( (DAL_SUCCESS != dalRes) || (NULL == phDalHWIO) ) {
         return I2CPLAT_ERROR_ATTACH_TO_DALHWIO;
      }
      pPlat->initState |= I2CPLAT_TGT_INIT_HWIO_ALLOCATED;

      if ( DAL_SUCCESS !=
             DalHWIO_MapRegion(phDalHWIO,
                               pProps->pPeriphSsAddrName,
                               &pPeriphSsBasePtr) ) {
         return I2CPLAT_ERROR_FAILED_TO_MAP_BLOCK_HWIO;
      }
   }
   pPlat->pQupAddr = pPeriphSsBasePtr + pPlat->props.coreOffset;
   return I2C_RES_SUCCESS;
}

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
   I2cPlat_DescType             *pPlat,
   uint64                        uIb,
   uint64                        uAb

)
{
   /*
   ICBArb_RequestType            i2cPnocRequest;
   ICBArb_ErrorType              i2cArbError;
   
   
   if ( NULL == hNpaClient ) { 
      return I2CPLAT_ERROR_PNOC_CLIENT_NOT_CREATED;
   }
 
   i2cPnocRequest.arbType =    ICBARB_REQUEST_TYPE_3;     // Ib/Ab pair 
     
   // Bandwidth in Bytes/second 
   i2cPnocRequest.arbData.type3.uIb = uIb;      
   i2cPnocRequest.arbData.type3.uAb = uAb;     

    i2cArbError = icbarb_issue_request(hNpaClient, &i2cPnocRequest,
                                      I2C_PNOC_MSTRSLV_PAIRS_NUM);
   
   if(i2cArbError != ICBARB_ERROR_SUCCESS)
   {
      return I2CPLAT_ERROR_FAILED_TO_ISSUE_PNOC_REQ;
   }
   */    
   return I2C_RES_SUCCESS;
}

/** @brief unvote for PNOC.
  
    
    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2CPLAT_Error.
  */

int32
I2cPlat_RemovePnocVote
(
   void
)
{ 
   //icbarb_complete_request(hNpaClient);
   return I2C_RES_SUCCESS; 
}

/** @brief detaches from DALDEVICEID_HWIO.
  
    @param[in] pDev     Pointer to platform device structure.
    
    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2CPLAT_Error.
  */
static int32
I2cPlat_DeInitHwio
(
   I2cPlat_DescType     *pDev
)
{
   DALResult dalRes;

   if ( NULL != phDalHWIO ) {
      dalRes = DAL_DeviceDetach(phDalHWIO);
      if ( DAL_SUCCESS != dalRes ) {
         return I2CPLAT_ERROR_DETACH_FROM_DALHWIO;
      }
   }
   return I2C_RES_SUCCESS;
}

/*-------------------------------------------------------------------------
 * Externalized Function Definitions
 * ----------------------------------------------------------------------*/



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
 )
{
   int32                           res;

   do
   {
	   uTgtCnt++;
      
      pPlat->initState = I2CPLAT_TGT_INIT_NOT_DONE;
      
      pPlat->props = *pProps;

      res = I2cPlat_EnableI2cGpios(pPlat);
      if ( I2C_RES_SUCCESS != res ) {
         break;
      }
/* //pnoc voting not yet present
      res = I2cPlat_RegisterSuppressibleClient();
      if ( I2C_RES_SUCCESS != res ) {
         break;
      }
*/
      res = I2cPlat_InitHwio(pPlat, pProps);
      if ( I2C_RES_SUCCESS != res ) {
         break;
      }
     
      res = I2C_RES_SUCCESS;
    } while ( 0 );

   if ( I2C_RES_SUCCESS != res ) {
      I2cPlat_DeInitTarget(pPlat);
   }
   return res;
}


/** @brief Releases data structures necessary to support the target calls.

    @param[in] pPlat platform device pointer.

    @return          int32 .
  */
int32
I2cPlat_DeInitTarget
(
   I2cPlat_DescType *pPlat
)
{
   int32      res, ret = I2C_RES_SUCCESS;

   uTgtCnt--;

   res = I2cPlat_DisableI2cGpios(pPlat);
   if ( I2C_RES_SUCCESS != res ) {
      ret = res;     
   }
   if ( 0 == uTgtCnt) {
      res = I2cPlat_DeInitHwio(pPlat);
      if ( I2C_RES_SUCCESS != res ) {
         ret = res;     
   }
   }

   return ret;
}

/** @brief Returns the QUP virtual address.

    @param[in]  pPlat platform device pointer.

    @return          int32 .
  */
uint8*
I2cPlat_GetQupAddress
(
   I2cPlat_DescType      *pPlat
)
{
   return pPlat->pQupAddr;

}

