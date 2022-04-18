/*=============================================================================

  FILE:   I2cDriver.c

  OVERVIEW:     This file contains the implementation of QUPI2CDriver API
  DEPENDENCIES: I2cDrv_AddDevice must be called first then other api's.
 
              Copyright (c) 2011-2016 Qualcomm Technologies, Incorporated.
                            All rights reserved.
              Qualcomm Technologies, Confidential and Proprietary.

  ===========================================================================*/

/*=========================================================================
  EDIT HISTORY FOR MODULE

  $Header: //components/rel/core.qdsp6/1.0.c2/buses/i2c/src/drv/I2cDriverInit.c#1 $
  $DateTime: 2020/02/10 01:57:30 $$Author: pwbldsvc $

  When     Who    What, where, why
  -------- ---    -----------------------------------------------------------
  10/17/16 VG     Updated Copy Rights
  06/11/14 LK     Removed i2cDrvSync definition from this file since it is accessed
                  in Island mode.
  01/22/12 LK     Removed Asynchronous calls and the queue 
                  to optimise transfers.
  09/26/11 LK     Created

  ===========================================================================*/

/*-------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------*/

#include "I2cDriver.h"
#include "I2cDriverTypes.h"
#include "I2cError.h"
#include "I2cDevice.h"
#include "I2cPlatSvc.h"
#include "I2cSys.h"
#include "I2cBsp.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * ----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Type Declarations
 * ----------------------------------------------------------------------*/
void 
I2cDrv_IST_HOOK
(
   void *pdata
) ;

/*-------------------------------------------------------------------------
 * Static Variable Definitions
 * ----------------------------------------------------------------------*/
/* Array of pointers to device structures. */

boolean                   bSyncInitialised = FALSE;

/*-------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 * ----------------------------------------------------------------------*/

/** @brief Adds a device and sets the handle.
  
    @param[in]  eI2cBusId  I2C bus id.
    @param[in] pDesc       Pointer to the I2C driver structure to be inited.
    
    @return             I2C_RES_SUCCESS if successful, error
                        otherwise.
  */
static int32
I2cDrv_AddDevice
(
   I2cDrv_I2cBusId  eI2cBusId,
   I2cDrv_DescType  *pDesc
)
{
   int32 res = I2C_RES_SUCCESS;
   enum I2cDrv_InitState{
	   I2CDRV_INITSTATE_UNINITIALISED,
      I2CDRV_INITSTATE_CRITSEC_INITED,
      I2CDRV_INITSTATE_EVENTS_INITED,
	   I2CDRV_INITSTATE_TARGET_INITED,
	   I2CDRV_INITSTATE_DEVICE_INITED,
   } eAddDeviceState;

   eAddDeviceState = I2CDRV_INITSTATE_UNINITIALISED;

   do
   {
      res = I2cSys_CreateCriticalSection(&pDesc->serialReqSync);
      if ( I2C_RES_SUCCESS != res ) {
         break;
      }
      eAddDeviceState = I2CDRV_INITSTATE_CRITSEC_INITED;
      
	  res = I2cPlat_InitTarget(&pDesc->plat, pDesc->pPlatProps);
	  if ( I2C_RES_SUCCESS != res ) {
	     break;
	  }
	  eAddDeviceState = I2CDRV_INITSTATE_TARGET_INITED;
     
     pDesc->pDevProps->virtBlockAddr = I2cPlat_GetQupAddress(&pDesc->plat);
	  res = I2cDev_Init(&pDesc->dev, pDesc->pDevProps);
     if ( I2C_RES_SUCCESS != res ) {
        break;
     }

      switch (eI2cBusId) {
         case I2CDRV_I2C_1:
            pDesc->dev.coreClockId = CLOCK_SCC_QUP_I2C1_CLK;
            break;
            
         case I2CDRV_I2C_2:
            pDesc->dev.coreClockId = CLOCK_SCC_QUP_I2C2_CLK;
            break;

        case I2CDRV_I2C_3:
            pDesc->dev.coreClockId = CLOCK_SCC_QUP_I2C3_CLK;
            break;

        default: break;
      }
          
     eAddDeviceState = I2CDRV_INITSTATE_DEVICE_INITED;
     aI2cDev[eI2cBusId] = pDesc;

   } while ( 0 );

   if ( I2C_RES_SUCCESS != res ) {
      switch ( eAddDeviceState ) {
              
	      case I2CDRV_INITSTATE_TARGET_INITED:
            I2cPlat_DeInitTarget(&pDesc->plat);
              
         default:
            break;
	    }
   }
      
   return res;
}

/** @brief Removes a device from the list and releases the
    	   object.
  
    @param[in]  eI2cBusId  device id.
    
    @return             I2C_RES_SUCCESS if successful, error
                        otherwise.
  */
static int32
I2cDrv_RemoveDevice
(
   I2cDrv_I2cBusId  eI2cBusId
)
{
   int32 res0,res1,res2, res3;
   I2cDrv_DescType *pDesc;

   pDesc = aI2cDev[eI2cBusId];
   if (NULL == pDesc ) {
      return I2C_RES_SUCCESS; // no device to remove
   }
   res0 = res1 = res2 = res3 = I2C_RES_SUCCESS;

   do 
   {
      I2cSys_EnterCriticalSection(&pDesc->serialReqSync);
      if (pDesc->opState & I2CDRV_OPSTATE_DEV_BUSY) {
	      res0 = I2CDRV_ERR_DEVICE_BUSY;
         break;
      }
      res1 = I2cDev_DeInit(&pDesc->dev);
      res2 = I2cPlat_DeInitTarget(&pDesc->plat);

      aI2cDev[eI2cBusId] = NULL;
      I2cSys_LeaveCriticalSection(&pDesc->serialReqSync);
      I2cSys_DestroyCriticalSection(&pDesc->serialReqSync);
   }while(0);
   
   if ( I2C_RES_SUCCESS != res0 ) {
      return res0;     
   }
   else if ( I2C_RES_SUCCESS != res1 ) {
	  return res1;
   }
   else if ( I2C_RES_SUCCESS != res2 ) {
	  return res2;
   }
   else if ( I2C_RES_SUCCESS != res3 ) {
	  return res3;
   }
      
   return I2C_RES_SUCCESS;
}

/*-------------------------------------------------------------------------
 * Externalized Function Definitions
 * ----------------------------------------------------------------------*/

/** @brief Initializes the driver.

    This Function initializes the device descriptor and data structures to support other calls into the
    driver.

    @param[in] eI2cBusId     I2C Bus ID.
    @param[in] pDesc         Pointer to the I2C driver structure to be inited.
                             This structure should be persistent.

    @return             I2C_RES_SUCCESS if successful, error
                        otherwise.
  */
int32
I2cDrv_InitDevice
(
   I2cDrv_I2cBusId  eI2cBusId,
   I2cDrv_DescType* pDesc
)
{
   int32 res;
   RETURN_IF_INVALID_BUS_ID(eI2cBusId);
   I2cSys_EnterCriticalSection(&i2cDrvSync);
   res = I2cDrv_AddDevice(eI2cBusId, pDesc);
   I2cSys_LeaveCriticalSection(&i2cDrvSync);
   return res;
}

/** @brief Deinitializes the device.

    This Function Deinitializes the device and releases
    resources acquired during init.
    
    @param[in] eI2cBusId     I2C Bus ID.

    @return             I2C_RES_SUCCESS if successful, error
                        otherwise.
  */
int32
I2cDrv_DeInitDevice
(
   I2cDrv_I2cBusId  eI2cBusId
)
{
   int32 res;

   RETURN_IF_INVALID_BUS_ID(eI2cBusId);
   I2cSys_EnterCriticalSection(&i2cDrvSync);
   res = I2cDrv_RemoveDevice(eI2cBusId);
   I2cSys_LeaveCriticalSection(&i2cDrvSync);
   return res;
}

/** @brief Initializes the driver.

    This Function Initializes the driver and creates the
    necessary data structures to support other calls into the
    driver.


    @return             I2C_RES_SUCCESS if successful, error
                        otherwise.
  */
int32
I2cDrv_Init
(
   void
)
{
   return I2cSys_CreateCriticalSection(&i2cDrvSync);
}

/** @brief Deinitializes the device.

    This Function Deinitializes the driver and releases
    resources acquired during init.
    @return             I2C_RES_SUCCESS if successful, error
                        otherwise.
  */
int32
I2cDrv_DeInit
(
   void
)
{
   return I2cSys_DestroyCriticalSection(&i2cDrvSync);
}
