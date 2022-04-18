/*=============================================================================

  FILE:   I2cPlatSvc.c

  OVERVIEW: This file contains the implementation for the platform services.
 
    Copyright (c) 2011-2017 Qualcomm Technologies, Incorporated.
                        All rights reserved.
    Qualcomm Technologies, Confidential and Proprietary.

=============================================================================*/
/*=============================================================================
EDIT HISTORY FOR MODULE

When     Who    What, where, why
-------- ---    -----------------------------------------------------------
02/07/17 VG     Added BAM prototypes
02/01/17 VG     Copyright updated
03/31/14 UR     64 bit support added
02/22/13 LK     Fixed platform id not being set and added a debug logging function.
09/26/11 LK     Created
=============================================================================*/

/*-------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------*/

#include "I2cPlatSvc.h"
#include "I2cPlatBam.h"
#include "I2cSys.h"
#include "I2cError.h"
#include "I2CConfig.h"

#include "DALStdDef.h"
#include "DALDeviceId.h"
#include "DALSys.h"

#include "DDITlmm.h"
#include "HALhwio.h"
#include "HALbootHWIO.h"

#include "api/systemdrivers/ClockBoot.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Type Declarations
 * ----------------------------------------------------------------------*/
typedef enum I2CPLATSVC_Error
{
   I2CPLATDEV_ERROR_BASE = I2C_RES_ERROR_CLS_DEV_PLATFORM,

   I2CPLATSVC_ERROR_DAL_GET_PROPERTY_VALUE,
   I2CPLATSVC_ERROR_BAM_PIPE_TRANSFER,
   I2CPLATSVC_ERROR_FAILED_TO_SET_APP_CLK_FREQ,
   I2CPLATSVC_ERROR_FAILED_TO_CLEAR_APP_CLK_FREQ,
   I2CPLATSVC_ERROR_FAILED_TO_ATTACH_TO_TLMM,
   I2CPLATSVC_ERROR_FAILED_TO_DETTACH_FROM_TLMM,
   I2CPLATSVC_ERROR_FAILED_TO_CONFIGURE_GPIO_0,
   I2CPLATSVC_ERROR_FAILED_TO_CONFIGURE_GPIO_1,

} I2CPLATSVC_Error;

typedef struct I2CPLATDEV_TargetCfgType
{
  void                         *uPlatDevId;
  DalDeviceHandle              *hTlmm;
  uint32                        uQupBlockOffset;
  I2CDeviceConfigType           platProps;
  uint32                        tmpPowerState;

} I2CPLATDEV_TargetCfgType, *I2CPLATDEV_PTargetCfgType;



/*-------------------------------------------------------------------------
 * Static Variable Definitions
 * ----------------------------------------------------------------------*/



/*-------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 * ----------------------------------------------------------------------*/

/** @brief Maps the hwio address space.
  
    @param[in] pDev     Pointer to platform device structure.
    
    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2CPLATSVC_Error.
  */
static int32
I2CPLATDEV_InitHwio
(
   I2CPLATDEV_TargetCfgType     *pDev
)
{
   return I2C_RES_SUCCESS;
}

/** @brief detaches from DALDEVICEID_HWIO.
  
    @param[in] pDev     Pointer to platform device structure.
    
    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2CPLATSVC_Error.
  */
static int32
I2CPLATDEV_DeInitHwio
(
   I2CPLATDEV_TargetCfgType     *pDev
)
{
   return I2C_RES_SUCCESS;
}

/** @brief Initializes the scl,sda gpios.
  
    @param[in] pDev     Pointer to platform device structure.
    
    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2CPLATSVC_Error.
  */
static int32
I2CPLATDEV_InitGpios
(
   I2CPLATDEV_TargetCfgType     *pDev
)
{
   DALResult dalRes;

   if (FALSE == pDev->platProps.bHasGpios) {
      return I2C_RES_SUCCESS;
   }
   dalRes = DAL_DeviceAttach(DALDEVICEID_TLMM, &pDev->hTlmm); 
   if ( (DAL_SUCCESS != dalRes) || (NULL == pDev->hTlmm) ) {
      return I2CPLATSVC_ERROR_FAILED_TO_ATTACH_TO_TLMM;
   }

   dalRes = DalTlmm_ConfigGpio(pDev->hTlmm, pDev->platProps.aGpioCfg[0],
                               DAL_TLMM_GPIO_ENABLE);
   if ( DAL_SUCCESS != dalRes ) {
      return I2CPLATSVC_ERROR_FAILED_TO_CONFIGURE_GPIO_0;
   }

   dalRes = DalTlmm_ConfigGpio(pDev->hTlmm, pDev->platProps.aGpioCfg[1],
                               DAL_TLMM_GPIO_ENABLE);
   if ( DAL_SUCCESS != dalRes ) {
      return I2CPLATSVC_ERROR_FAILED_TO_CONFIGURE_GPIO_1;
   }

   return I2C_RES_SUCCESS;
}

/** @brief Initializes the scl,sda gpios.
  
    @param[in] pDev     Pointer to platform device structure.
    
    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2CPLATSVC_Error.
  */
static int32
I2CPLATDEV_DeInitGpios
(
   I2CPLATDEV_TargetCfgType     *pDev
)
{
   DALResult dalRes;

   if ( FALSE == pDev->platProps.bHasGpios ) {
      return I2C_RES_SUCCESS;
   }
   if ( pDev->hTlmm ) {
      dalRes = DAL_DeviceDetach(pDev->hTlmm);
      if ( DAL_SUCCESS != dalRes ) {
         return I2CPLATSVC_ERROR_FAILED_TO_DETTACH_FROM_TLMM;
      }
   }

   return I2C_RES_SUCCESS; 
}

/** @brief Initializes the clocks for the qup core.
  
    @param[in] pDev     Pointer to platform device structure.
    
    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2CPLATSVC_Error.
  */
static int32
I2CPLATDEV_InitClocks
(
   I2CPLATDEV_TargetCfgType     *pDev
)
{
   I2CDeviceConfigType             *pProps = &pDev->platProps;
   uint32                           uSetClkFreq;

   // pProps->uCoreIndex matches to ClockQUPI2CType enum values
   uSetClkFreq = Clock_SetI2CClockFrequency(CLOCK_BOOT_PERF_DEFAULT, (ClockQUPI2CType)pProps->uCoreIndex);    
   if (!uSetClkFreq)
   {
      return I2CPLATSVC_ERROR_FAILED_TO_SET_APP_CLK_FREQ;     
   }    
   
   return I2C_RES_SUCCESS; 
}

/** @brief Deinitializes the clocks for the qup core.
  
    @param[in] pDev     Pointer to platform device structure.
    
    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2CPLATSVC_Error.
  */
static int32
I2CPLATDEV_DeInitClocks
(
   I2CPLATDEV_TargetCfgType     *pDev
)
{  
   I2CDeviceConfigType             *pProps = &pDev->platProps;
   uint32                           uResetClkFreq;
   
   // pProps->uCoreIndex matches to ClockQUPI2CType enum values
   uResetClkFreq = Clock_DisableI2CClock((ClockQUPI2CType)pProps->uCoreIndex);
   if (!uResetClkFreq)
   {
      return I2CPLATSVC_ERROR_FAILED_TO_CLEAR_APP_CLK_FREQ;     
   }    
   return I2C_RES_SUCCESS; 
}


/**
 * @brief Schedule a single BAM transfer
  
   This function schedules a single BAM transfer.
  
   @param[in]  hPlat       Platform BAM handle
   @param[in]  pBamIoVec   Pointer to bam IO vector
   @param[out] pFreeCnt    Pointer to free descriptor count
   @param[in]  pfnCb       Function callback pointer.
   @param[in]  pUser       Arguments passed to the func cb.
  
   @return I2C_RES_SUCCESS is successful, otherwise
                        I2CPLATSVC_Error.
 */

int32 I2CPLATDEV_PlatBamTransfer
(
   I2CPLATDEV_HANDLE        hPlat,  
   I2CPLATBAM_BamIoVecType *pBamIoVec,
   uint32                  *pFreeCnt,
   I2CDEVICE_PLATBAM_CB     pfnCb,
   void                    *pArg
)
{
   return I2CPLATSVC_ERROR_BAM_PIPE_TRANSFER;
}

/**
   @brief Find Available free space in a BAM pipe
 
   @param[in] hPlat  Platform handle
   @param[in] uDir   Producer or Consumer transfer

   @return Available free space. 
 */
uint32
I2CPLATDEV_BamGetPipeFreeSpace
(
   I2CPLATDEV_HANDLE        hPlat,
   I2CPLATBAM_DirectionType eDir
)
{
   return I2C_RES_SUCCESS;
}

/** @brief Read the platform properties.
  
    @param[in]  uPlatDevId  Platform device ID.
    @param[out] pDev        Pointer to platform device
          structure.
    
    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2CPLATSVC_Error.
  */
int32
I2CPLATDEV_ReadPlatConfig
(
   void                     *uPlatDevId,
   I2CPLATDEV_TargetCfgType *pDev
)
{
   if (I2CDeviceGetConfig (uPlatDevId, &pDev->platProps) != DAL_SUCCESS)
   {
      return I2CPLATSVC_ERROR_DAL_GET_PROPERTY_VALUE;
   }

   return I2C_RES_SUCCESS;
}


/*-------------------------------------------------------------------------
 * Externalized Function Definitions
 * ----------------------------------------------------------------------*/

/** @brief Sets the power state.
  
    @param[in] hPlat  Platform handle.
    @param[in] state  New power state.
    
    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2CPLATSVC_Error.
  */
int32
I2CPLATDEV_SetPowerState
(
   I2CPLATDEV_HANDLE hPlat,
   uint32            state
)
{
   I2CPLATDEV_TargetCfgType *pDev = (I2CPLATDEV_TargetCfgType *)hPlat;
   pDev->tmpPowerState = state;
   return I2C_RES_SUCCESS;
}

/** @brief Gets the power state.
  
    @param[in] hPlat  Platform handle.
    @param[in] pState Pointer to power state.
    
    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2CPLATSVC_Error.
  */
int32
I2CPLATDEV_GetPowerState
(
   I2CPLATDEV_HANDLE  hPlat,
   uint32            *pState
)
{
   I2CPLATDEV_TargetCfgType *pDev = (I2CPLATDEV_TargetCfgType *)hPlat;
   *pState = pDev->tmpPowerState;
   return I2C_RES_SUCCESS;
}

/** @brief Sets the resource exclusive .
  
    @param[in] hPlat  Platform handle.
    @param[in] hRes   Resource handle.
    
    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2CPLATSVC_Error.
  */
int32
I2CPLATDEV_SetResourceExclusive
(
   I2CPLATDEV_HANDLE hPlat,
   QUPRES_HANDLE     hRes
)
{
   return I2C_RES_SUCCESS;
}

/** @brief Releases the resource exclusive .
  
    @param[in] hPlat  Platform handle.
    @param[in] hRes   Resource handle.
    
    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2CPLATSVC_Error.
  */
int32
I2CPLATDEV_ReleaseResourceExclusive
(
    I2CPLATDEV_HANDLE hPlat,
    QUPRES_HANDLE     hRes
)
{
   return I2C_RES_SUCCESS;
}

/** @brief Reads the properties for this device.

    @param[in]  hPlat     Platform handle.
    @param[out] pDevProp  Pointer to device properties.

    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2CPLATSVC_Error.
  */
int32
I2CPLATDEV_ReadProperties
(
   I2CPLATDEV_HANDLE        hPlat,
   I2CPLATDEV_PropertyType *pDevProp
)
{
   I2CPLATDEV_TargetCfgType     *pDev;
   
   pDev = (I2CPLATDEV_TargetCfgType*)hPlat;
   
   pDevProp->pDevName        = pDev->platProps.pDevName;
   pDevProp->virtBlockAddr   = (uint8 *) pDev->platProps.pPeriphSsAddr + pDev->platProps.uQupBlockOffset;
   pDevProp->bInterruptBased = pDev->platProps.bInterruptBased;
   pDevProp->bDisablePm      = pDev->platProps.bDisablePm;
   pDevProp->bBamAvailable   = pDev->platProps.bBamEnabled;
   pDevProp->uBamThreshold   = pDev->platProps.uBamThreshold;
   pDevProp->uI2cSrcClkKhz   = pDev->platProps.uAppClkFreqKhz;

   return I2C_RES_SUCCESS;
}

/**
    This Function initializes target support structures and subsystems.

    @param[in]  uPlatDevId  Platform specific device identifier.
    @param[out] phPlat      Pointer to platform handle.

    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2CPLATSVC_Error.
  */
int32
I2CPLATDEV_InitTarget
(
   void              *uPlatDevId,
   I2CPLATDEV_HANDLE *phPlat
)
{
   I2CPLATDEV_TargetCfgType       *pDev;
   int32                           res;
 
   res = I2CSYS_Malloc((void **)&pDev, sizeof(I2CPLATDEV_TargetCfgType));
   if (I2C_RES_SUCCESS != res) {
      return res;
   }
   res = I2CSYS_Memset(pDev, 0, sizeof(I2CPLATDEV_TargetCfgType));
   if ( I2C_RES_SUCCESS != res )  {
      I2CSYS_Free(pDev);     
      return res;
   }

   do
   {
      res = I2CPLATDEV_ReadPlatConfig(uPlatDevId, pDev);
      if ( I2C_RES_SUCCESS != res ) {
         break;
      }
      
      res = I2CPLATDEV_InitClocks(pDev);
      if ( I2C_RES_SUCCESS != res ) {
       break;
      }

      res = I2CPLATDEV_InitHwio(pDev);
      if ( I2C_RES_SUCCESS != res ) {
         break;
      }
     
      res = I2CPLATDEV_InitGpios(pDev);
      if ( I2C_RES_SUCCESS != res ) {
         break;
      }
      pDev->uPlatDevId = uPlatDevId;
      *phPlat = (I2CPLATDEV_HANDLE) pDev;
      res = I2C_RES_SUCCESS;
    } while ( 0 );

   if ( I2C_RES_SUCCESS != res ) {
      I2CPLATDEV_DeInitTarget(pDev);
   }
   return res;
}

/** @brief Resets resources like bam pipes following a qup core reset.

    @param[in] hPlatDev platform device handle.

    @return          int32 .
  */
int32
I2CPLATDEV_ResetTarget
(
   I2CPLATDEV_HANDLE hPlatDev
)
{
   return I2C_RES_SUCCESS;
}

/**
    This Function deinitializes target support structures and
    subsystems.

    @param[in]  hPlatDev     Platform handle.

    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2CPLATSVC_Error.
  */
int32
I2CPLATDEV_DeInitTarget
(
   I2CPLATDEV_HANDLE hPlatDev
)
{
   I2CPLATDEV_TargetCfgType       *pDev;
   int32                           res ;
   int32                           clkRes, hwioRes,bamRes,gpioRes,freeRes;

   pDev = (I2CPLATDEV_TargetCfgType *)hPlatDev;
   res = clkRes = hwioRes = bamRes = gpioRes = freeRes = I2C_RES_SUCCESS;

   clkRes = I2CPLATDEV_DeInitClocks(pDev);
   hwioRes = I2CPLATDEV_DeInitHwio(pDev);
   gpioRes = I2CPLATDEV_DeInitGpios(pDev);
   freeRes = I2CSYS_Free(pDev);

   if (clkRes)
   {
      res = clkRes;
   }
   else if (hwioRes)
   {
      res = hwioRes;
   }
   else if (bamRes)
   {
      res = bamRes;
   }
   else if (gpioRes)
   {
      res = gpioRes;
   }
   else if (freeRes) {
      res = freeRes;
   }

   return res;
}

/**
    This Function registers IST and ISR callbacks.

    @param[in]  hPlatDev     Platform handle.
    @param[in]  IsrHook      ISR function pointer.
    @param[in]  pIsrData     pointer to ISR callback data.
    @param[in]  IstHook      IST function pointer.
    @param[in]  pIstData     pointer to IST callback data.

    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2CPLATSVC_Error.
  */
int32
I2CSYS_RegisterISTHooks
(
   I2CPLATDEV_HANDLE hPlatDev,
   ISR_HOOK          IsrHook,
   void*             pIsrData,
   IST_HOOK          IstHook,
   void*             pIstData
)
{
   return I2C_RES_SUCCESS;
}

/**
    This Function unregisters IST and ISR callbacks.

    @param[in]  hPlatDev     Platform handle.

    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2CPLATSVC_Error.
  */
int32
I2CSYS_UnRegisterISTHooks
(
   I2CPLATDEV_HANDLE hPlatDev
)
{
   return I2C_RES_SUCCESS;
}

/**
    This Function gets the app clock freq in KHz.

    @param[in]  hPlatDev     Platform handle.

    @return             frequency in KHz.
  */
uint32
I2CPLATDEV_GetAppClkKhz
(
   I2CPLATDEV_HANDLE hPlat
)
{
   I2CPLATDEV_TargetCfgType     *pDev;
   pDev = (I2CPLATDEV_TargetCfgType*)hPlat;     

   return pDev->platProps.uAppClkFreqKhz;
}
/** @brief Acquires an interrupt lock.

    @param[in] hPlatDev platform device handle.
    @return          I2CSYS_Result .
  */
void
I2CPLATDEV_AcquireIntLock
(
   I2CPLATDEV_HANDLE hPlatDev
)
{
  
}

/** @brief Releases the interrupt lock.

    @param[in] hPlatDev platform device handle.
    @return          I2CSYS_Result .
  */
void
I2CPLATDEV_ReleaseIntLock
(
   I2CPLATDEV_HANDLE hPlatDev
)
{
  
}

/** @brief Checks if BAM is enabled.

    @param[in] hPlatDev platform device handle.
    @return    TRUE if BAM is enabled FALSE otherwise .
  */
boolean
I2CPLATDEV_IsBamEnabled
(
   I2CPLATDEV_HANDLE hPlatDev
)
{
   I2CPLATDEV_TargetCfgType     *pDev;
   pDev = (I2CPLATDEV_TargetCfgType*)hPlatDev;

   return pDev->platProps.bBamEnabled;
}



