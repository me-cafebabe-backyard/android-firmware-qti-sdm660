/*
===========================================================================
*/
/**
  @file ClockFwk.c
  
  DAL framework implementation file for the clock device driver.
*/
/*  
  ====================================================================

  Copyright (c) 2016 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================

  $Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/clock/src/adsp_slpi/ClockFwk.c#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $

  ====================================================================
*/ 


/*=========================================================================
      Include Files
==========================================================================*/

#include "DALFramework.h"
#include "DalDevice.h"
#include "DALDeviceId.h"
#include "DDIClock.h"
#include "ClockDriver.h"
#include "DDIHWIO.h"
#include "DDIPlatformInfo.h"
#include "DALPropDef.h"
#include "qurt_pimutex.h"


/*=========================================================================
      Macro Definitions
==========================================================================*/


/*
 * Take a DAL driver handle and dereference into the driver context.
 */
#define HANDLE2CTXT(h) \
  &((ClockDALClientCtxt *)(h->pClientCtxt))->pClockDevCtxt->pClockDrvCtxt->DrvCtxt


/*=========================================================================
      Type Definitions
==========================================================================*/


/*=========================================================================
      Function Prototypes
==========================================================================*/

DALResult Clock_DeviceAttachEx(const char *, DALDEVICEID, DalDeviceHandle **, int);
static DALResult DALClock_DriverInit(ClockDALDrvCtxt *);
static DALResult DALClock_DriverDeInit(ClockDALDrvCtxt *);
static void Clock_ReleaseClientResources(ClockDALClientCtxt* pClientCtxt);


/*=========================================================================
      Data Declarations
==========================================================================*/

static DALDEVICEID DALClock_DeviceId[1] =
{
  DALDEVICEID_CLOCK
};

const DALREG_DriverInfo DALClock_DriverInfo =
{
  {.pfnDALNewFuncEx = Clock_DeviceAttachEx}, 1, DALClock_DeviceId
};

static ClockDALDrvCtxt Clock_DriverCtxt =
{
  {
    DALClock_DriverInit,
    DALClock_DriverDeInit
    },
  1,
  sizeof(ClockDALDevCtxt)
};

/*
 * Mutex for lite implementation.
 */
static qurt_mutex_t hClockLiteMutex = QURT_MUTEX_INIT;


/*
 * Static array of client contexts.  The number of client contexts in this
 * array must be sufficiently large to accommodate the number of s
 * supported on the subsystem.
 */
static ClockDALClientCtxt ClockClientCtxts[CLOCK_CTXT_TOTAL];


/*=========================================================================
      Functions
==========================================================================*/


static uint32
Clock_AddRef(DalClockHandle *h)
{
   return DALFW_AddRef((DALClientCtxt *)(h->pClientCtxt));
}

static uint32
Clock_DeviceDetach(DalDeviceHandle* h)
{
   uint32 dwref = DALFW_Release((DALClientCtxt *)(h->pClientCtxt));

   if (dwref == 0)
   {
     /*
      * Release all allocated resources for this client context.
      */
     Clock_ReleaseClientResources(((DalClockHandle *)h)->pClientCtxt);
   }
   return dwref;
}

static DALResult
Clock_DeviceInit(DalDeviceHandle *h)
{
   return DAL_SUCCESS;
}

static DALResult
Clock_DeviceDeInit(DalDeviceHandle *h)
{
   return DAL_SUCCESS;
}

static DALResult
Clock_DevicePowerEvent(DalDeviceHandle *h, DalPowerCmd PowerCmd,
                                DalPowerDomain PowerDomain )
{
   return DAL_SUCCESS;

}

static DALResult
Clock_DeviceOpen(DalDeviceHandle* h, uint32 mode)
{
   return DAL_SUCCESS;
}

static DALResult
Clock_DeviceClose(DalDeviceHandle* h)
{
   return DAL_SUCCESS;
}

static DALResult
Clock_DeviceInfo(DalDeviceHandle* h, DalDeviceInfo* info, uint32 infoSize)
{
   info->Version = DALCLOCK_INTERFACE_VERSION;
   return DAL_SUCCESS;
}

static DALResult
Clock_DeviceSysRequest(DalDeviceHandle* h,DalSysReq ReqIdx,
                                const void* SrcBuf, uint32 SrcBufLen,
                                void* DestBuf, uint32 DestBufLen, uint32* DestBufLenReq)
{
   return DAL_SUCCESS;
}


static void DALClock_GetStubFlags
(
  ClockDrvCtxt *pDrvCtxt
)
{
  DALResult               eResult;
  ClockPropertyValueType  PropVal;
  ClockStubType               *pClockStubConfig;
  DalPlatformInfoPlatformType  PlatformInfo;

  /*-----------------------------------------------------------------------*/
  /* Get the stub config.                                                  */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_GetPropertyValue("ClockStubConfig", &PropVal);
  if (eResult == DAL_SUCCESS)
  {
    pClockStubConfig = (ClockStubType *)PropVal;
    PlatformInfo = DalPlatformInfo_Platform();

    if ((PlatformInfo == DALPLATFORMINFO_TYPE_RUMI) &&
        (pClockStubConfig->bRUMI == TRUE))
    {
      CLOCK_GLOBAL_FLAG_SET(STUB_API);

      DALSYS_LogEvent (
        DALDEVICEID_CLOCK, DALSYS_LOGEVENT_INFO,
        "CLOCK_GLOBAL_FLAG_STUB_API set - stubbing out on RUMI.");
    }
    if ((PlatformInfo == DALPLATFORMINFO_TYPE_VIRTIO) &&
        (pClockStubConfig->bVirtio == TRUE))
    {
      CLOCK_GLOBAL_FLAG_SET(STUB_API);

      DALSYS_LogEvent (
        DALDEVICEID_CLOCK, DALSYS_LOGEVENT_INFO,
        "CLOCK_GLOBAL_FLAG_STUB_API set - stubbing out on Virtio.");
    }
  }
}


static DALResult DALClock_DriverInit
(
  ClockDALDrvCtxt *drvCtxt
)
{
  DALResult eRes;
  ClockDrvCtxt *pDrvCtxt;

  /*-----------------------------------------------------------------------*/
  /* ENTER CRITICAL SECTION: Protect vs. lite implementation.              */
  /*-----------------------------------------------------------------------*/

  pDrvCtxt = Clock_GetDrvCtxt();

  /*-----------------------------------------------------------------------*/
  /* Get our property handle.                                              */
  /*-----------------------------------------------------------------------*/

  eRes = DALSYS_GetDALPropertyHandle(
    DALDEVICEID_CLOCK, Clock_DriverCtxt.ClockDevCtxt[0].hProp);

  if (eRes != DAL_SUCCESS)
  {
    Clock_ReleaseDrvCtxt();
    return eRes;
  }

  /*-----------------------------------------------------------------------*/
  /* Attach to the HWIO DAL.  This is done here since the common code may  */
  /* live in environments without the DAL framework.                       */
  /*-----------------------------------------------------------------------*/

  DAL_DeviceAttach(DALDEVICEID_HWIO, &Clock_DriverCtxt.phHWIO);

  /*-----------------------------------------------------------------------*/
  /* Get the stub flags.                                                   */
  /*-----------------------------------------------------------------------*/

  DALClock_GetStubFlags(pDrvCtxt);

  /*-----------------------------------------------------------------------*/
  /* Perform driver initialization.                                        */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    eRes = ClockStub_DriverInit(pDrvCtxt);
  }
  else
  {
    eRes = Clock_DriverInit(pDrvCtxt);
  }

  /*-----------------------------------------------------------------------*/
  /* Transfer reference counts from lite implementation to DAL.            */
  /*-----------------------------------------------------------------------*/

  eRes = Clock_TransferReferenceCount();
  if (eRes != DAL_SUCCESS)
  {
    DALSYS_LogEvent(
      DALDEVICEID_CLOCK,
      DALSYS_LOGEVENT_FATAL_ERROR,
      "Clock_TransferReferenceCount failed.");
  }

  /*-----------------------------------------------------------------------*/
  /* END CRITICAL SECTION: Protect vs. lite implementation.                */
  /*-----------------------------------------------------------------------*/

  Clock_ReleaseDrvCtxt();

  return eRes;
}
 
static DALResult DALClock_DriverDeInit(ClockDALDrvCtxt *drvCtxt)
{ 
  DALResult      eRes;
  ClockDrvCtxt  *pDrvCtxt = &drvCtxt->DrvCtxt;

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    eRes = ClockStub_DriverDeInit(&drvCtxt->DrvCtxt);
  }
  else
  {
    eRes = Clock_DriverDeInit(&drvCtxt->DrvCtxt);
  }

  return eRes;
}

static DALResult DALClock_GetClockId( DalDeviceHandle * h,  const char * szClock,  ClockIdType * pnId)
  { return Clock_GetClockId(HANDLE2CTXT(h), szClock, pnId); }

static DALResult DALClock_EnableClock( DalDeviceHandle * h,  ClockIdType  nClock)
  { 
    if ((nClock != NULL) && CLOCK_FLAG_IS_SET(((ClockNodeType *)nClock), INTERNAL_CONTROL))
    {
      return DAL_ERROR;
    }
      
    return Clock_EnableClock(((DalClockHandle *)h)->pClientCtxt, nClock);
  }

static DALResult DALClock_DisableClock( DalDeviceHandle * h,  ClockIdType  nClock)
  { 
    if ((nClock != NULL) && CLOCK_FLAG_IS_SET(((ClockNodeType *)nClock), INTERNAL_CONTROL))
    {
      return DAL_ERROR;
    }

    return Clock_DisableClock(((DalClockHandle *)h)->pClientCtxt, nClock);
  }

static DALResult DALClock_SetClockFrequency( DalDeviceHandle * h,  ClockIdType  nClock,  uint32  nFreq,  ClockFrequencyType  eMatch, uint32 *pnResultFreq )
  { 
    if ((nClock != NULL) && (((ClockNodeType *)nClock)->pDomain != NULL) && CLOCK_FLAG_IS_SET(((ClockNodeType *)nClock)->pDomain, INTERNAL_CONTROL))
    {
      return DAL_ERROR;
    }

    return Clock_SetClockFrequency(HANDLE2CTXT(h), nClock, nFreq, eMatch, pnResultFreq); 
  }

static DALResult DALClock_SetClockDivider( DalDeviceHandle * h,  ClockIdType  nClock,  uint32  nDivider)
  { 
    if ((nClock != NULL) && CLOCK_FLAG_IS_SET((ClockNodeType *)nClock, INTERNAL_CONTROL))
    {
      return DAL_ERROR;
    }

    return Clock_SetClockDivider(HANDLE2CTXT(h), nClock, nDivider);
  }

static DALResult DALClock_InvertClock( DalDeviceHandle * h,  ClockIdType  nClock,  boolean  bInvert)
  { 
    if ((nClock != NULL) && CLOCK_FLAG_IS_SET((ClockNodeType *)nClock, INTERNAL_CONTROL))
    {
      return DAL_ERROR;
    }

    return Clock_InvertClock(HANDLE2CTXT(h), nClock, bInvert);
  }

static DALResult DALClock_ResetClock( DalDeviceHandle * h,  ClockIdType  nClock,  ClockResetType  eReset)
  {
    if ((nClock != NULL) && CLOCK_FLAG_IS_SET((ClockNodeType *)nClock, INTERNAL_CONTROL))
    {
      return DAL_ERROR;
    }

    return Clock_ResetClock(HANDLE2CTXT(h), nClock, eReset);
  }

static DALResult DALClock_ResetClock_STM( DalDeviceHandle * h,  ClockIdType  nClock,  ClockResetType  eReset)
  {
    if ((nClock != NULL) && CLOCK_FLAG_IS_SET((ClockNodeType *)nClock, INTERNAL_CONTROL))
    {
      return DAL_ERROR;
    }

    return Clock_ResetClock_STM(HANDLE2CTXT(h), nClock, eReset);
  }

static DALResult DALClock_IsClockEnabled( DalDeviceHandle * h,  ClockIdType  nClock,  boolean * pbIsEnabled)
  { return Clock_IsClockEnabled(HANDLE2CTXT(h), nClock, pbIsEnabled); }

static DALResult DALClock_IsClockOn( DalDeviceHandle * h,  ClockIdType  nClock,  boolean * pbIsOn)
  { return Clock_IsClockOn(HANDLE2CTXT(h), nClock, pbIsOn); }

static DALResult DALClock_GetClockFrequency( DalDeviceHandle * h,  ClockIdType  nClock,  uint32 * pnFrequencyHz)
  { return Clock_GetClockFrequency(HANDLE2CTXT(h), nClock, pnFrequencyHz); }

static DALResult DALClock_SelectExternalSource( DalDeviceHandle * h,  ClockIdType  nClock, uint32 nFreqHz, uint32 nSource, uint32  nDiv2x,  uint32  nM,  uint32  nN,  uint32  n2D)
  { return Clock_SelectExternalSource(HANDLE2CTXT(h), nClock, nFreqHz, nSource, nDiv2x, nM, nN, n2D); }

static DALResult DALClock_CalcClockFrequency( DalDeviceHandle * h,  ClockIdType  nClock,  uint32 * pnFrequencyHz)
  { return Clock_CalcClockFrequency(HANDLE2CTXT(h), nClock, pnFrequencyHz); }

static DALResult DALClock_GetPowerDomainId( DalDeviceHandle * h,  const char * szPowerDomain,  ClockPowerDomainIdType * pnPowerDomainId)
  { return Clock_GetPowerDomainId(HANDLE2CTXT(h), szPowerDomain, pnPowerDomainId); }

static DALResult DALClock_EnablePowerDomain( DalDeviceHandle * h,  ClockPowerDomainIdType  nPowerDomainId)
  {
    if ((nPowerDomainId != NULL) && CLOCK_FLAG_IS_SET((ClockPowerDomainNodeType *)nPowerDomainId, INTERNAL_CONTROL))
    {
      return DAL_ERROR;
    }

    return Clock_EnablePowerDomain(((DalClockHandle *)h)->pClientCtxt, nPowerDomainId); 
  }

static DALResult DALClock_DisablePowerDomain( DalDeviceHandle * h,  ClockPowerDomainIdType  nPowerDomainId)
  {
    if ((nPowerDomainId != NULL) && CLOCK_FLAG_IS_SET((ClockPowerDomainNodeType *)nPowerDomainId, INTERNAL_CONTROL))
    {
      return DAL_ERROR;
    }

    return Clock_DisablePowerDomain(((DalClockHandle *)h)->pClientCtxt, nPowerDomainId);
  }

static DALResult DALClock_EnableDCVS( DalDeviceHandle * h)
  { return Clock_EnableDCVS(HANDLE2CTXT(h)); }

static DALResult DALClock_LoadNV( DalDeviceHandle * h)
  { return Clock_LoadNV(HANDLE2CTXT(h)); }

static DALResult DALClock_ProcessorSleep( DalDeviceHandle * h,  ClockSleepModeType  eMode,  uint32  nFlags)
  { return Clock_ProcessorSleep(HANDLE2CTXT(h), eMode, nFlags); }

static DALResult DALClock_ProcessorRestore( DalDeviceHandle * h,  ClockSleepModeType  eMode,  uint32  nFlags)
  { return Clock_ProcessorRestore(HANDLE2CTXT(h), eMode, nFlags); }

static DALResult DALClock_ConfigClock( DalDeviceHandle * h,  ClockIdType  nClock,  ClockConfigType  eConfig)
  {
    if ((nClock != NULL) && CLOCK_FLAG_IS_SET((ClockNodeType *)nClock, INTERNAL_CONTROL))
    {
      return DAL_ERROR;
    }

    return Clock_ConfigClock(HANDLE2CTXT(h), nClock, eConfig);
  }

static DALResult DALClock_SetUARTBaudClock( DalDeviceHandle * h,  ClockIdType  nClock, ClockIdType nRefClock, uint32 nDI, uint32 nFI, uint32 *pnResultFreqHz)
  { return Clock_SetUARTBaudClock(HANDLE2CTXT(h), nClock, nRefClock, nDI, nFI, pnResultFreqHz); }

static DALResult DALClock_LogState( DalDeviceHandle * h,  void *pULog,  uint32 nFlags)
  { return Clock_LogState(HANDLE2CTXT(h), (ULogHandle)pULog, nFlags); }

static DALResult DALClock_AdjustSourceFrequency(DalDeviceHandle * h,  ClockSourceType eSource,  int32 nDeltaLAlpha)
  { return Clock_AdjustSourceFrequency(HANDLE2CTXT(h), eSource, nDeltaLAlpha); }

static DALResult DALClock_SelectClockSource(DalDeviceHandle * h,  ClockIdType nClock, ClockSourceType eSource)
  { return Clock_SelectClockSource(HANDLE2CTXT(h), nClock, eSource); }

static DALResult DALClock_GetSourceId( DalDeviceHandle * h,  const char * szSource,  SourceIdType * pnId)
  { return Clock_GetSourceId(HANDLE2CTXT(h), szSource, pnId); }

static DALResult DALClock_EnableSource( DalDeviceHandle * h,  SourceIdType  nSource)
  { return Clock_EnableSource(((DalClockHandle *)h)->pClientCtxt, nSource); }

static DALResult DALClock_DisableSource( DalDeviceHandle * h,  SourceIdType  nSource)
  { return Clock_DisableSource(((DalClockHandle *)h)->pClientCtxt, nSource); }

static DALResult DALClock_SetSourceFrequency( DalDeviceHandle * h,  SourceIdType  nSource,  uint32  nFreq,  ClockFrequencyType  eMatch, uint32 *pnResultFreq )
  { return Clock_SetSourceFrequency(HANDLE2CTXT(h), nSource, nFreq, eMatch, pnResultFreq); }

static DALResult DALClock_GetSourceFrequency( DalDeviceHandle * h,  SourceIdType  nSource,  uint32 * pnFrequencyHz)
  { return Clock_GetSourceFrequency(HANDLE2CTXT(h), nSource, pnFrequencyHz); }

static DALResult DALClock_SetCPUMaxFrequencyAtCurrentVoltage( DalDeviceHandle * h, boolean bRequired, uint32 * pnResultFreqHz)
  { return Clock_SetCPUMaxFrequencyAtCurrentVoltage(HANDLE2CTXT(h), bRequired, pnResultFreqHz); }


/*-----------------------------------------------------------------------*/
/* Stubs.                                                                */
/*-----------------------------------------------------------------------*/


static DALResult DALClockStub_GetClockId( DalDeviceHandle * h,  const char * szClock,  ClockIdType * pnId)
  { return DAL_SUCCESS; }

static DALResult DALClockStub_EnableClock( DalDeviceHandle * h,  ClockIdType  nClock)
  { return DAL_SUCCESS; }

static DALResult DALClockStub_DisableClock( DalDeviceHandle * h,  ClockIdType  nClock)
  { return DAL_SUCCESS; }

static DALResult DALClockStub_SetClockFrequency( DalDeviceHandle * h,  ClockIdType  nClock,  uint32  nFreq,  ClockFrequencyType  eMatch, uint32 *pnResultFreq )
  {
    if (pnResultFreq != NULL)
	{
	  *pnResultFreq = nFreq;
	}

    return DAL_SUCCESS;
  }

static DALResult DALClockStub_SetClockDivider( DalDeviceHandle * h,  ClockIdType  nClock,  uint32  nDivider)
  { return DAL_SUCCESS; }

static DALResult DALClockStub_InvertClock( DalDeviceHandle * h,  ClockIdType  nClock,  boolean  bInvert)
  { return DAL_SUCCESS; }

static DALResult DALClockStub_ResetClock( DalDeviceHandle * h,  ClockIdType  nClock,  ClockResetType  eReset)
  { return DAL_SUCCESS; }

static DALResult DALClockStub_ResetClock_STM( DalDeviceHandle * h,  ClockIdType  nClock,  ClockResetType  eReset)
  { return DAL_SUCCESS; }

static DALResult DALClockStub_IsClockEnabled( DalDeviceHandle * h,  ClockIdType  nClock,  boolean * pbIsEnabled)
  { return DAL_SUCCESS; }

static DALResult DALClockStub_IsClockOn( DalDeviceHandle * h,  ClockIdType  nClock,  boolean * pbIsOn)
  { return DAL_SUCCESS; }

static DALResult DALClockStub_GetClockFrequency( DalDeviceHandle * h,  ClockIdType  nClock,  uint32 * pnFrequencyHz)
  { return DAL_SUCCESS; }

static DALResult DALClockStub_SelectExternalSource( DalDeviceHandle * h,  ClockIdType  nClock,  uint32 nFreqHz,  uint32 nSource, uint32  nDiv2x,  uint32  nM,  uint32  nN,  uint32  n2D)
  { return DAL_SUCCESS; }

static DALResult DALClockStub_CalcClockFrequency( DalDeviceHandle * h,  ClockIdType  nClock,  uint32 * pnFrequencyHz)
  { return DAL_SUCCESS; }

static DALResult DALClockStub_GetPowerDomainId( DalDeviceHandle * h,  const char * szPowerDomain,  ClockPowerDomainIdType * pnPowerDomainId)
  { return DAL_SUCCESS; }

static DALResult DALClockStub_EnablePowerDomain( DalDeviceHandle * h,  ClockPowerDomainIdType  nPowerDomainId)
  { return DAL_SUCCESS; }

static DALResult DALClockStub_DisablePowerDomain( DalDeviceHandle * h,  ClockPowerDomainIdType  nPowerDomainId)
  { return DAL_SUCCESS; }

static DALResult DALClockStub_EnableDCVS( DalDeviceHandle * h)
  { return DAL_SUCCESS; }

static DALResult DALClockStub_LoadNV( DalDeviceHandle * h)
  { return DAL_SUCCESS; }

static DALResult DALClockStub_ProcessorSleep( DalDeviceHandle * h,  ClockSleepModeType  eMode,  uint32  nFlags)
  { return DAL_SUCCESS; }

static DALResult DALClockStub_ProcessorRestore( DalDeviceHandle * h,  ClockSleepModeType  eMode,  uint32  nFlags)
  { return DAL_SUCCESS; }

static DALResult DALClockStub_ConfigClock( DalDeviceHandle * h,  ClockIdType  nClock,  ClockConfigType  eConfig)
  { return DAL_SUCCESS; }

static DALResult DALClockStub_SetUARTBaudClock( DalDeviceHandle * h,  ClockIdType  nClock, ClockIdType nRefClock, uint32 nDI, uint32 nFI, uint32 *pnResultFreqHz)
  { return DAL_SUCCESS; }

static DALResult DALClockStub_LogState( DalDeviceHandle * h,  void *pULog,  uint32 nFlags)
  { return DAL_SUCCESS; }

static DALResult DALClockStub_AdjustSourceFrequency(DalDeviceHandle * h,  ClockSourceType eSource,  int32 nDeltaLAlpha)
  { return DAL_SUCCESS; }

static DALResult DALClockStub_SelectClockSource(DalDeviceHandle * h,  ClockIdType nClock, ClockSourceType eSource)
  { return DAL_SUCCESS; }

static DALResult DALClockStub_GetSourceId( DalDeviceHandle * h,  const char * szSource,  SourceIdType * pnId)
  { return DAL_SUCCESS; }

static DALResult DALClockStub_EnableSource( DalDeviceHandle * h,  SourceIdType  nSource)
  { return DAL_SUCCESS; }

static DALResult DALClockStub_DisableSource( DalDeviceHandle * h,  SourceIdType  nSource)
  { return DAL_SUCCESS; }

static DALResult DALClockStub_SetSourceFrequency( DalDeviceHandle * h,  SourceIdType  nSource,  uint32  nFreq,  ClockFrequencyType  eMatch, uint32 *pnResultFreq )
  {
    if (pnResultFreq != NULL)
	{
	  *pnResultFreq = nFreq;
	}

    return DAL_SUCCESS;
  }

static DALResult DALClockStub_GetSourceFrequency( DalDeviceHandle * h,  SourceIdType  nSource,  uint32 * pnFrequencyHz)
  { return DAL_SUCCESS; }

static DALResult DALClockStub_SetCPUMaxFrequencyAtCurrentVoltage( DalDeviceHandle * h, boolean bRequired, uint32 * pnResultFreqHz)
  {
    if (pnResultFreqHz != NULL)
        {
          *pnResultFreqHz = 0;
        }

    return DAL_SUCCESS;
  }


/* =========================================================================
**  Function : Clock_InitInterface
** =========================================================================*/
/**
  Initialize the client context for communicating to the DAL.
 
  This function initializes the given client context.  It is invoked
  internally when a client attaches to the dal.
 
  @param *pclientCtxt [in] -- Pointer to the DAL client context.

  @return
  None.

  @dependencies
  None.
*/ 

static void Clock_InitInterface
(
  ClockDALClientCtxt* pclientCtxt
)
{
  ClockDrvCtxt  *pDrvCtxt = &pclientCtxt->pClockDevCtxt->pClockDrvCtxt->DrvCtxt;
  static DalClock vtbl =
   {
      {
        {.AttachEx = Clock_DeviceAttachEx},
         Clock_DeviceDetach,
         Clock_DeviceInit,
         Clock_DeviceDeInit,
         Clock_DeviceOpen,
         Clock_DeviceClose,
         Clock_DeviceInfo,
         Clock_DevicePowerEvent,
         Clock_DeviceSysRequest
      },
   
      DALClock_GetClockId,
      DALClock_EnableClock,
      DALClock_DisableClock,
      DALClock_SetClockFrequency,
      DALClock_SetClockDivider,
      DALClock_InvertClock,
      DALClock_ResetClock,
      DALClock_ResetClock_STM,
      DALClock_IsClockEnabled,
      DALClock_IsClockOn,
      DALClock_GetClockFrequency,
      DALClock_SelectExternalSource,
      DALClock_GetPowerDomainId,
      DALClock_EnablePowerDomain,
      DALClock_DisablePowerDomain,
      DALClock_EnableDCVS,
      DALClock_LoadNV,
      DALClock_ProcessorSleep,
      DALClock_ProcessorRestore,
      DALClock_CalcClockFrequency,
      DALClock_ConfigClock,
      DALClock_SetUARTBaudClock,
      DALClock_LogState,
      DALClock_AdjustSourceFrequency,
      DALClock_SelectClockSource,
      DALClock_GetSourceId,
      DALClock_EnableSource,
      DALClock_DisableSource,
      DALClock_SetSourceFrequency,
      DALClock_GetSourceFrequency,
      DALClock_SetCPUMaxFrequencyAtCurrentVoltage,
   };

  /*-----------------------------------------------------------------------*/
  /* Stub out the DAL API if the API stub flag is set.                     */
  /*-----------------------------------------------------------------------*/

  if (CLOCK_GLOBAL_FLAG_IS_SET(STUB_API))
  {
    vtbl.GetClockId                         = DALClockStub_GetClockId;
    vtbl.EnableClock                        = DALClockStub_EnableClock;
    vtbl.DisableClock                       = DALClockStub_DisableClock;
    vtbl.SetClockFrequency                  = DALClockStub_SetClockFrequency;
    vtbl.SetClockDivider                    = DALClockStub_SetClockDivider;
    vtbl.InvertClock                        = DALClockStub_InvertClock;
    vtbl.ResetClock                         = DALClockStub_ResetClock;
    vtbl.ResetClock_STM                     = DALClockStub_ResetClock_STM;
    vtbl.IsClockEnabled                     = DALClockStub_IsClockEnabled;
    vtbl.IsClockOn                          = DALClockStub_IsClockOn;
    vtbl.GetClockFrequency                  = DALClockStub_GetClockFrequency;
    vtbl.SelectExternalSource               = DALClockStub_SelectExternalSource;
    vtbl.GetPowerDomainId                   = DALClockStub_GetPowerDomainId;
    vtbl.EnablePowerDomain                  = DALClockStub_EnablePowerDomain;
    vtbl.DisablePowerDomain                 = DALClockStub_DisablePowerDomain;
    vtbl.EnableDCVS                         = DALClockStub_EnableDCVS;
    vtbl.LoadNV                             = DALClockStub_LoadNV;
    vtbl.ProcessorSleep                     = DALClockStub_ProcessorSleep;
    vtbl.ProcessorRestore                   = DALClockStub_ProcessorRestore;
    vtbl.CalcClockFrequency                 = DALClockStub_CalcClockFrequency;
    vtbl.ConfigClock                        = DALClockStub_ConfigClock;
    vtbl.SetUARTBaudClock                   = DALClockStub_SetUARTBaudClock;
    vtbl.LogState                           = DALClockStub_LogState;
    vtbl.AdjustSourceFrequency              = DALClockStub_AdjustSourceFrequency;
    vtbl.SelectClockSource                  = DALClockStub_SelectClockSource;
    vtbl.GetSourceId                        = DALClockStub_GetSourceId;
    vtbl.EnableSource                       = DALClockStub_EnableSource;
    vtbl.DisableSource                      = DALClockStub_DisableSource;
    vtbl.SetSourceFrequency                 = DALClockStub_SetSourceFrequency;
    vtbl.GetSourceFrequency                 = DALClockStub_GetSourceFrequency;
    vtbl.SetCPUMaxFrequencyAtCurrentVoltage = DALClockStub_SetCPUMaxFrequencyAtCurrentVoltage;
  }

   pclientCtxt->DalClockHandle.dwDalHandleId = DALDEVICE_INTERFACE_HANDLE_ID;
   pclientCtxt->DalClockHandle.pVtbl  = &vtbl;
   pclientCtxt->DalClockHandle.pClientCtxt = pclientCtxt;
  pclientCtxt->DalClockHandle.dwVtblen = sizeof(vtbl)/sizeof(void (*)(void));

} /* END Clock_InitInterface */


/* =========================================================================
**  Function : Clock_DeviceAttachEx
** =========================================================================*/
/**
  Internal DAL framework function for attaching to the clock DAL in multi-
  environments.
 
  This function attaches to the clock DAL and initializes the given
  device handle in multi- environments for providing multi- restart 
  functionality.
 
  @param *pszArg[in] -- String passed by user during attach.
  @param DeviceId   [in]  -- The device id, should be DALDEVICEID_CLOCK
  @param phDalDevice[out] -- DAL device handle to fill in.
  @param nPDID  [in]  -- Client ID/ that the call is coming from.

  @return
  DAL_SUCCESS - Successfully initialized and attached to driver.
  DAL_ERROR   - Failed to initialize the driver.

  @dependencies
  None.
*/ 

DALResult
Clock_DeviceAttachEx(const char *pszArg,
                        DALDEVICEID DeviceId,
                        DalDeviceHandle **phDalDevice,
                        int nPDID)
{
   DALResult nErr;
   uint32 nIdx;
   ClockDALClientCtxt *pClientCtxt = NULL;
   *phDalDevice = NULL;

   /*
    * Look for a valid client context containing a matching nPDID value and
    * connect this request if found.
    */
   for (nIdx=0; nIdx<CLOCK_CTXT_TOTAL; nIdx++)
   {
     if ((ClockClientCtxts[nIdx].CtxtInfo.nPDID == nPDID) &&
         (ClockClientCtxts[nIdx].CtxtInfo.bInUse == TRUE))
     {
       pClientCtxt = &ClockClientCtxts[nIdx];
       break;
     }
   }

   /*
    * If there was no valid client context associated with the client ID, then
    * look for the next available client context that can be connected to this
    * nPDID.
    */
   if (pClientCtxt == NULL)
   {
     for (nIdx=0; nIdx<CLOCK_CTXT_TOTAL; nIdx++)
     {
       if(ClockClientCtxts[nIdx].CtxtInfo.bInUse == FALSE)
       {
         pClientCtxt = &ClockClientCtxts[nIdx];
         pClientCtxt->CtxtInfo.nPDID = nPDID;
         pClientCtxt->CtxtInfo.nIdx = nIdx;
         pClientCtxt->CtxtInfo.bInUse = TRUE;
         break;
       }
     }

     if (pClientCtxt == NULL)
     {
       return DAL_ERROR;
     }
   }

   nErr = DALFW_AttachToDevice(DeviceId,(DALDrvCtxt *)&Clock_DriverCtxt,
                                        (DALClientCtxt *)pClientCtxt);
   if (DAL_SUCCESS == nErr)
   {
      Clock_InitInterface(pClientCtxt);
      Clock_AddRef(&(pClientCtxt->DalClockHandle));
      *phDalDevice = (DalDeviceHandle *)&(pClientCtxt->DalClockHandle);
   }
   return nErr;

} /* END Clock_DeviceAttachEx */


/* =========================================================================
**  Function : Clock_GetPropertyValue
** =========================================================================*/
/*
  See ClockDriver.h
*/ 

DALResult Clock_GetPropertyValue
(
  const char              *szName,
  ClockPropertyValueType  *pValue
)
{
  DALResult         eRes;
  DALSYSPropertyVar Var;

  eRes = DALSYS_GetPropertyValue(
    Clock_DriverCtxt.ClockDevCtxt[0].hProp, szName, 0, &Var); 

  if (eRes != DAL_SUCCESS)
  {
    return eRes;
  }

  if (Var.dwType == DALPROP_ATTR_TYPE_STRUCT_PTR)
  {
    *pValue = (ClockPropertyValueType)Var.Val.pStruct;
  }
  else if (Var.dwType == DALPROP_ATTR_TYPE_UINT32)
  {
    *pValue = (ClockPropertyValueType)Var.Val.dwVal;
  }

  return DAL_SUCCESS;

} /* END Clock_GetPropertyValue */


/* =========================================================================
**  Function : Clock_MapHWIORegion
** =========================================================================*/
/*
  See ClockDriver.h
*/ 

DALResult Clock_MapHWIORegion
(
  uint32  nPhysAddr,
  uint32  nSizeBytes,
  uint32 *pnVirtAddr
)
{
  DALResult eRes = DAL_SUCCESS;

  /*-----------------------------------------------------------------------*/
  /* If we attached to the HWIO DAL, then map the regions.                 */
  /*-----------------------------------------------------------------------*/

  if (Clock_DriverCtxt.phHWIO != NULL)
  {
    eRes = DalHWIO_MapRegionByAddress(
      Clock_DriverCtxt.phHWIO, (uint8 *)nPhysAddr, (uint8 **)pnVirtAddr);
  }

  /*-----------------------------------------------------------------------*/
  /* No HWIO DAL, so assume base address is the physical address.          */
  /*-----------------------------------------------------------------------*/

  else
  {
    *pnVirtAddr = nPhysAddr;
  }

  return eRes;

} /* END Clock_MapHWIORegion */


/*=========================================================================
**  Function : Clock_GetDrvCtxt
** =========================================================================*/
/**
  See ClockDriver.h
*/

ClockDrvCtxt *Clock_GetDrvCtxt(void)
{
  /*-----------------------------------------------------------------------*/
  /* Acquire mutex shared with lite API.                                   */
  /*-----------------------------------------------------------------------*/

  qurt_pimutex_lock(&hClockLiteMutex);

  /*-----------------------------------------------------------------------*/
  /* Return driver context.                                                */
  /*-----------------------------------------------------------------------*/

  return &Clock_DriverCtxt.DrvCtxt;

} /* END of Clock_GetDrvCtxt */


/*=========================================================================
**  Function : Clock_GetDrvCtxtNoLock
** =========================================================================*/
/**
  Internal DAL Clock API to retrieve the driver context without causing a
  mutex lock.

  THis function returns the static clock driver context without locking a
  mutex in the process.

  @return
  A pointer to the static clock driver context.

  @dependencies
  None.
*/
ClockDrvCtxt *Clock_GetDrvCtxtNoLock(void)
{
  return &Clock_DriverCtxt.DrvCtxt;

} /* END Clock_GetDrvCtxtNoLock */


/*=========================================================================
**  Function : Clock_ReleaseDrvCtxt
** =========================================================================*/
/**
  See ClockDriver.h
*/

void Clock_ReleaseDrvCtxt(void)
{
  /*-----------------------------------------------------------------------*/
  /* Release mutex shared with lite API.                                   */
  /*-----------------------------------------------------------------------*/

  qurt_pimutex_unlock(&hClockLiteMutex);

} /* END of Clock_ReleaseDrvCtxt */


/*=========================================================================
**  Function : Clock_GetInitialClientCtxt
** =========================================================================*/
/**
  Internal DAL framework function for retrieving the first client context
 
  This function retrieves the first client context which will be associated
  with the root client (or ).  This will always be initialized on the first
  attach from RCINIT.

  @return
  Pointer to the first client context (or root ).

  @dependencies
  None.
*/

ClockDALClientCtxt *Clock_GetInitialClientCtxt(void)
{
  return &ClockClientCtxts[0];

} /* END Clock_GetInitialClientCtxt */


/*=========================================================================
**  Function : Clock_ReleaseClientResources
** =========================================================================*/
/**
  Internal API to release resources

  Cleans up all enabled clock resources for a particular client that
  has done a final detach on the clock driver.  In most cases this will occur
  after a  restart after the DAL framework has decremented all stale 
  device attach references.

  @return
  None.

  @dependencies
  None.
*/

static void Clock_ReleaseClientResources
(
  ClockDALClientCtxt* pClientCtxt
)
{
  uint32        nIdx;
  ClockDrvCtxt *pDrvCtxt = Clock_GetDrvCtxtNoLock();

  /*
   * Disable all clocks associated with this client context.
   */
  if (pClientCtxt->CtxtInfo.TotalCtxtReferences.nClockRefs > 0)
  {
    for (nIdx=0; nIdx<pDrvCtxt->nNumClocks; nIdx++)
    {
      while (pDrvCtxt->aClocks[nIdx].nReferenceCount[pClientCtxt->CtxtInfo.nIdx] > 0)
      {
        Clock_DisableClock(pClientCtxt, (ClockIdType)(&pDrvCtxt->aClocks[nIdx]));
      }
    }
  }
   
  /*
   * Disable all external source requests associated with this client context.
   */
  if (pClientCtxt->CtxtInfo.TotalCtxtReferences.nSourceRefs > 0)
  {
    for (nIdx=0; nIdx<pDrvCtxt->nNumSources; nIdx++)
    {
      while (pDrvCtxt->aSources[nIdx].nReferenceCountExternal[pClientCtxt->CtxtInfo.nIdx] > 0)
      {
        Clock_DisableSource(pClientCtxt,
            (SourceIdType)(&pDrvCtxt->aSources[nIdx]));
      }
    }
  }

  /*
   * Disable all power domains associated with this client context.
   */
  if (pClientCtxt->CtxtInfo.TotalCtxtReferences.nPowerDomainRefs > 0)
  {
    for (nIdx=0; nIdx<pDrvCtxt->nNumPowerDomains; nIdx++)
    {
      while (pDrvCtxt->aPowerDomains[nIdx].nReferenceCount[pClientCtxt->CtxtInfo.nIdx] > 0)
      {
        Clock_DisablePowerDomain(pClientCtxt, 
            (ClockPowerDomainIdType)(&pDrvCtxt->aPowerDomains[nIdx]));
      }
    }
  }

  /*
   * Clean up and allow resuse of the client context.
   */
   ClockClientCtxts[pClientCtxt->CtxtInfo.nIdx].CtxtInfo.nPDID = 0;
   ClockClientCtxts[pClientCtxt->CtxtInfo.nIdx].CtxtInfo.bInUse = FALSE;

} /* END Clock_ReleaseClientResources */

