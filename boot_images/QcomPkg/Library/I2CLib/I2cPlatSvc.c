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
02/01/17 VG     Copyright updated
04/13/16 UR     Removed BAM code
07/13/15 UR     Fixed bug where BLSP2 was getting BLSP1 base address
10/30/14 UR     Added support for UEFI Low Power Mode
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
#include "DDIClock.h"
#include "DDIHWIO.h"

#include "DDIInterruptController.h"

#include "bam.h"
#include "DDITlmm.h"


/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
#define QUP_FREQ_HZ                            19200000

#define I2C_DEVICE_PLATBAM_MAX_BAM_THRESHOLD (32*1024)
#define I2C_DEVICE_PLATBAM_MAX_DESC_SIZE     0x100
#define I2C_DEVICE_PLATBAM_MAX_COMMAND_SIZE  0x100


/*-------------------------------------------------------------------------
 * Type Declarations
 * ----------------------------------------------------------------------*/
typedef enum I2CPLATSVC_Error
{
   I2CPLATDEV_ERROR_BASE = I2C_RES_ERROR_CLS_DEV_PLATFORM,

   I2CPLATSVC_ERROR_DAL_GET_PROPERTY_HANDLE,
   I2CPLATSVC_ERROR_DAL_GET_PROPERTY_VALUE,
   I2CPLATSVC_ERROR_DAL_GET_CHIP_BUS_INDEX_PROPERTY_VALUE,
   I2CPLATSVC_ERROR_ATTACH_TO_CLOCKS,
   I2CPLATSVC_ERROR_DETACH_FROM_CLOCKS,
   I2CPLATSVC_ERROR_ATTACH_TO_DALHWIO,
   I2CPLATSVC_ERROR_DETACH_FROM_DALHWIO,
   I2CPLATSVC_ERROR_GETTING_APPCLK_ID,
   I2CPLATSVC_ERROR_GETTING_HCLK_ID,
   I2CPLATSVC_ERROR_CREATING_DISPATCH_WORKLOOP,
   I2CPLATSVC_ERROR_CREATING_DISPATCH_EVENT,
   I2CPLATSVC_ERROR_ASSOCIATING_EVENT_WITH_WORKLOOP,
   I2CPLATSVC_ERROR_INVALID_POWER_STATE,
   I2CPLATSVC_ERROR_FAILED_TO_SET_APPCLK_FREQ,
   I2CPLATSVC_ERROR_FAILED_TO_ENABLE_APPCLK,
   I2CPLATSVC_ERROR_FAILED_TO_DISABLE_APPCLK,
   I2CPLATSVC_ERROR_FAILED_TO_ENABLE_HCLK,
   I2CPLATSVC_ERROR_FAILED_TO_DISABLE_HCLK,
   I2CPLATSVC_ERROR_FAILED_TO_MAP_BLOCK_HWIO,
   I2CPLATSVC_ERROR_FAILED_ATTACH_TO_IRQCTRL,
   I2CPLATSVC_ERROR_FAILED_TO_REGISTER_IST,
   I2CPLATSVC_ERROR_FAILED_TO_UNREGISTER_IST,
   I2CPLATSVC_ERROR_FAILED_TO_INIT_BAM_HANDLE,
   I2CPLATSVC_ERROR_FAILED_TO_DEINIT_BAM_HANDLE,
   I2CPLATSVC_ERROR_FAILED_TO_INIT_OUTPIPE_HANDLE,
   I2CPLATSVC_ERROR_FAILED_TO_DEINIT_OUTPIPE_HANDLE,
   I2CPLATSVC_ERROR_FAILED_TO_INIT_INPIPE_HANDLE,
   I2CPLATSVC_ERROR_FAILED_TO_DEINIT_INPIPE_HANDLE,
   I2CPLATSVC_ERROR_BAM_PIPE_TRANSFER,
   I2CPLATSVC_ERROR_BAM_PIPE_FULL,
   I2CPLATSVC_ERROR_FAILED_TO_ATTACH_TO_TLMM,
   I2CPLATSVC_ERROR_FAILED_TO_DETTACH_FROM_TLMM,
   I2CPLATSVC_ERROR_FAILED_TO_OPEN_TLMM,
   I2CPLATSVC_ERROR_FAILED_TO_CLOSE_TLMM,
   I2CPLATSVC_ERROR_FAILED_TO_CONFIGURE_GPIO_0,
   I2CPLATSVC_ERROR_FAILED_TO_CONFIGURE_GPIO_1, 
   I2CPLATSVC_ERROR_VIRT_TO_PHYS_ADDR_ERROR,
   I2CPLATSVC_ERROR_FAILED_TO_DISABLE_TX_PIPE,
   I2CPLATSVC_ERROR_FAILED_TO_RE_ENABLE_TX_PIPE,
   I2CPLATSVC_ERROR_FAILED_TO_DISABLE_RX_PIPE,
   I2CPLATSVC_ERROR_FAILED_TO_RE_ENABLE_RX_PIPE,
   I2CPLATSVC_ERROR_FAILED_TO_SET_APP_CLK_FREQ,

} I2CPLATSVC_Error;

typedef enum I2CPLATDEV_PowerStates
{
   I2CPLATDEV_POWER_STATE_0,/**< Bus and clocks off. */
   I2CPLATDEV_POWER_STATE_1,/**< Bus on clocks off. */
   I2CPLATDEV_POWER_STATE_2,/**< Bus on clocks on. */
} I2CPLATDEV_PowerStates;

typedef struct I2cOs_IrqType
{
   ISR_HOOK IsrHook;
   IST_HOOK IstHook;
   void     *pIsrData;
   void     *pIstData;
   uint32   uInterruptId;
   uint32   uIrqTriggerCfg;
} I2cOs_IrqType;

typedef enum I2CPLATDEV_TargetInitState
{
   I2CPLATDEV_TGT_INIT_NOT_DONE = 0,
   I2CPLATDEV_TGT_INIT_CLK_ALLOCATED  = 0x01,
   I2CPLATDEV_TGT_INIT_HWIO_ALLOCATED = 0x02,
   I2CPLATDEV_TGT_INIT_BAM_INITED     = 0x04,
   I2CPLATDEV_TGT_INIT_TLMM_ALLOCATED = 0x08,
   I2CPLATDEV_TGT_INIT_TLMM_OPENED    = 0x10,
} I2CPLATDEV_TargetInitState;

typedef struct I2CPLATDEV_TargetCfgType
{
  void                         *uPlatDevId;
  DalDeviceHandle              *pClkHandle;
  ClockIdType                   QupHClkId;
  ClockIdType                   QupAppClkId;
  uint8                        *pPeriphSsBasePtr;
  uint32                        uQupBlockOffset;
  DalDeviceHandle              *phDalHWIO;

  I2cOs_IrqType                 irq;
  DalDeviceHandle              *hInterruptCtrl;
  DalDeviceHandle              *hTlmm;
  I2CDeviceConfigType           platProps;

  uint32                        tmpPowerState;//untill clocks are operational
  I2CPLATDEV_TargetInitState    initState;

} I2CPLATDEV_TargetCfgType, *I2CPLATDEV_PTargetCfgType;

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
   DALResult dalRes;

   dalRes = DAL_DeviceAttach(DALDEVICEID_HWIO, &pDev->phDalHWIO);
   if ( (DAL_SUCCESS != dalRes) || (NULL == pDev->phDalHWIO) ) {
      return I2CPLATSVC_ERROR_ATTACH_TO_DALHWIO;
   }
   pDev->initState |= I2CPLATDEV_TGT_INIT_HWIO_ALLOCATED;
   if ( DAL_SUCCESS !=
      DalHWIO_MapRegion(pDev->phDalHWIO,
                        pDev->platProps.pPeriphSsAddrName,
                        &pDev->pPeriphSsBasePtr) ) {
      return I2CPLATSVC_ERROR_FAILED_TO_MAP_BLOCK_HWIO;
   }

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
   DALResult dalRes;

   if ( pDev->initState & I2CPLATDEV_TGT_INIT_HWIO_ALLOCATED ) {
      dalRes = DAL_DeviceDetach(pDev->phDalHWIO);
      if ( DAL_SUCCESS != dalRes ) {
         return I2CPLATSVC_ERROR_DETACH_FROM_DALHWIO;
      }
   }
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
   dalRes = DAL_DeviceAttachEx(NULL, DALDEVICEID_TLMM,
                               DALTLMM_INTERFACE_VERSION, &pDev->hTlmm);
   if ( (DAL_SUCCESS != dalRes) || (NULL == pDev->hTlmm) ) {
      return I2CPLATSVC_ERROR_FAILED_TO_ATTACH_TO_TLMM;
   }
   pDev->initState |= I2CPLATDEV_TGT_INIT_TLMM_ALLOCATED;

   dalRes = DalDevice_Open(pDev->hTlmm, DAL_OPEN_SHARED);
   if ( DAL_SUCCESS != dalRes ) {
      return I2CPLATSVC_ERROR_FAILED_TO_OPEN_TLMM;
   }
   pDev->initState |= I2CPLATDEV_TGT_INIT_TLMM_OPENED;

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
   if ( pDev->initState & I2CPLATDEV_TGT_INIT_TLMM_OPENED ) {
      dalRes = DalDevice_Close(pDev->hTlmm);
      if ( DAL_SUCCESS != dalRes ) {
         return I2CPLATSVC_ERROR_FAILED_TO_CLOSE_TLMM;
      }
   }
   if ( pDev->initState & I2CPLATDEV_TGT_INIT_TLMM_ALLOCATED ) {
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
   DALResult dalRes;
   I2CDeviceConfigType             *pProps;
   uint32                           uSetClkFreq;

   pProps = &pDev->platProps;

   /* Fails to attach to clocks, they are not available */
   dalRes = DAL_ClockDeviceAttach(DALDEVICEID_CLOCK, &pDev->pClkHandle);
   if ( (DAL_SUCCESS != dalRes) || (NULL == pDev->pClkHandle) ) {
      return I2CPLATSVC_ERROR_ATTACH_TO_CLOCKS;
   }
   pDev->initState |= I2CPLATDEV_TGT_INIT_CLK_ALLOCATED;

   if ( DAL_SUCCESS !=
        DalClock_GetClockId(pDev->pClkHandle,
                            pDev->platProps.pQupAppClkName,
                            &pDev->QupAppClkId) ) {
      return I2CPLATSVC_ERROR_GETTING_APPCLK_ID;
   }

   dalRes = DalClock_SetClockFrequency(pDev->pClkHandle,
                                       pDev->QupAppClkId,
                                       pProps->uAppClkFreqKhz,
                                       CLOCK_FREQUENCY_KHZ_EXACT,
                                       &uSetClkFreq);
   if ( DAL_SUCCESS != dalRes ) {
      return I2CPLATSVC_ERROR_FAILED_TO_SET_APP_CLK_FREQ;     
   }    
   
   if ( DAL_SUCCESS != 
        DalClock_GetClockId(pDev->pClkHandle,
                            pDev->platProps.pQupHClkName,
                            &pDev->QupHClkId) ) {
      return I2CPLATSVC_ERROR_GETTING_HCLK_ID;
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
   DALResult dalRes;

   if ( pDev->initState & I2CPLATDEV_TGT_INIT_CLK_ALLOCATED ) {
      dalRes = DAL_DeviceDetach(pDev->pClkHandle);
      if ( DAL_SUCCESS != dalRes ) {
         return I2CPLATSVC_ERROR_DETACH_FROM_CLOCKS;
      }
   }
   return I2C_RES_SUCCESS; 
}

/** @brief Enables the clocks for the qup core.
  
    @param[in] pDev     Pointer to platform device structure.
    
    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2CPLATSVC_Error.
  */
static int32
I2CPLATDEV_EnableClocks
(
   I2CPLATDEV_TargetCfgType     *pDev
)
{
   DALResult                        dalRes;
   
   /* Enable QUP Clock */  
   dalRes = DalClock_EnableClock(pDev->pClkHandle, pDev->QupAppClkId);
   if ( DAL_SUCCESS != dalRes ) {
      return I2CPLATSVC_ERROR_FAILED_TO_ENABLE_APPCLK;
   }

   /* Enable HCLK */
   dalRes = DalClock_EnableClock(pDev->pClkHandle, pDev->QupHClkId);
   if ( DAL_SUCCESS != dalRes ) {
      return I2CPLATSVC_ERROR_FAILED_TO_ENABLE_HCLK;
   }

   return I2C_RES_SUCCESS;
}

/** @brief Disables the clocks for the qup core.
  
    @param[in] pDev     Pointer to platform device structure.
    
    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2CPLATSVC_Error.
  */
static int32
I2CPLATDEV_DisableClocks
(
   I2CPLATDEV_TargetCfgType     *pDev
)
{
   DALResult dalRes;

   /* Disable QUP Clock */
   dalRes = DalClock_DisableClock(pDev->pClkHandle, pDev->QupAppClkId);
   if ( DAL_SUCCESS != dalRes ) {
       return I2CPLATSVC_ERROR_FAILED_TO_DISABLE_APPCLK; 
   }

   /* Disable HCLK */
   // COMMENTED OUT since the clock may be shared with UART on UEFI
   // dalRes = DalClock_DisableClock(pDev->pClkHandle, pDev->QupHClkId);
   // if ( DAL_SUCCESS != dalRes ) {
   //     return I2CPLATSVC_ERROR_FAILED_TO_DISABLE_HCLK;
   // }

   return I2C_RES_SUCCESS;
}

/** @brief Platform IST. Used to dispatch common drivers ISR,
           IST.
  
    @param[in] pCtxt    Context passed to the Platform IST.
    
    @return             void pointer.
  */
static void*
I2CPLATDEV_Isr
(
   void *pCtxt
)
{
   I2CPLATDEV_TargetCfgType *pDev = (I2CPLATDEV_TargetCfgType *)pCtxt;
   I2cOs_IrqType  *pIrq;

   if (NULL == pDev) {
      return NULL; 
   }
   pIrq = &pDev->irq;
   pIrq->IsrHook(pIrq->pIsrData);
   pIrq->IstHook(pIrq->pIstData);
   DalInterruptController_InterruptDone(pDev->hInterruptCtrl,pIrq->uInterruptId);
   return NULL;
}

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
   return 0;
}

/** @brief Initializes bam.
  
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
   I2CPLATDEV_TargetCfgType     *pDev = (I2CPLATDEV_TargetCfgType *)hPlat;
   int32                         res;

   if ( I2CPLATDEV_POWER_STATE_0 == state ) {
      res = I2CPLATDEV_DisableClocks(pDev);
   }
   else if ( I2CPLATDEV_POWER_STATE_1 == state ) {
      res = I2CPLATDEV_DisableClocks(pDev); /*  bus state is powered. */
   }
   else if ( I2CPLATDEV_POWER_STATE_2 == state ) {      
      res = I2CPLATDEV_EnableClocks(pDev); /* bus state is active. */
   }
   else {
      return I2CPLATSVC_ERROR_INVALID_POWER_STATE;
   }

   if ( I2C_RES_SUCCESS == res ) {
      pDev->tmpPowerState = state;
   }

   return res;
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
   I2CPLATDEV_TargetCfgType     *pDev = (I2CPLATDEV_TargetCfgType *)hPlat;

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
   pDevProp->virtBlockAddr   = pDev->pPeriphSsBasePtr + pDev->platProps.uQupBlockOffset;
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
   pDev->initState = I2CPLATDEV_TGT_INIT_NOT_DONE;
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
   int32                           clkRes,hwioRes,gpioRes,freeRes;

   pDev = (I2CPLATDEV_TargetCfgType *)hPlatDev;
   res = clkRes = hwioRes = gpioRes = freeRes = I2C_RES_SUCCESS;

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
   else if (gpioRes)
   {
      res = gpioRes;
   }
   else if (freeRes)
   {
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
   DALResult                     dalRes;
   I2CPLATDEV_TargetCfgType     *pDev;
   
   pDev = (I2CPLATDEV_TargetCfgType*)hPlatDev;
   
   if ( NULL == pDev->hInterruptCtrl ) {
      dalRes =
          DAL_InterruptControllerDeviceAttach(DALDEVICEID_INTERRUPTCONTROLLER,
                                              &pDev->hInterruptCtrl);
      if( (DAL_SUCCESS != dalRes) || (NULL == pDev->hInterruptCtrl) ) {
         return I2CPLATSVC_ERROR_FAILED_ATTACH_TO_IRQCTRL; 
      }
   }

   pDev->irq.IsrHook = IsrHook;
   pDev->irq.IstHook = IstHook;
   pDev->irq.pIsrData = pIsrData;
   pDev->irq.pIstData = pIstData;
   pDev->irq.uInterruptId = pDev->platProps.uInterruptId;
   pDev->irq.uIrqTriggerCfg = pDev->platProps.uIrqTriggerCfg;
   dalRes = DalInterruptController_RegisterISR(
                        pDev->hInterruptCtrl,
                        pDev->irq.uInterruptId,
                        I2CPLATDEV_Isr,
                        (DALISRCtx)pDev,
                        pDev->irq.uIrqTriggerCfg);
   if ( DAL_SUCCESS != dalRes ) {
      return I2CPLATSVC_ERROR_FAILED_TO_REGISTER_IST;
   }
  
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
   DALResult                     dalRes;
   I2CPLATDEV_TargetCfgType     *pDev;
   pDev = (I2CPLATDEV_TargetCfgType*)hPlatDev;
   
   if ( NULL == pDev->hInterruptCtrl ) {
      return I2CPLATSVC_ERROR_FAILED_ATTACH_TO_IRQCTRL; 
   }

   dalRes = DalInterruptController_Unregister(pDev->hInterruptCtrl,pDev->irq.uInterruptId);
   if ( DAL_SUCCESS != dalRes ) {
      return I2CPLATSVC_ERROR_FAILED_TO_UNREGISTER_IST;
   }

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



