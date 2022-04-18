/*
===========================================================================
*/
/**
  @file ClockTURING.c
  
  Main entry point for the SDM660 TURING clock driver.
*/
/*
  ====================================================================

  Copyright (c) 2017 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ==================================================================== 
  $Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/clock/hw/sdm660/cdsp/src/ClockTURING.c#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $
 
  when       who     what, where, why
  --------   ---     -------------------------------------------------
  05/24/17   shm     Added dummy Clock_SetOverride
  10/04/16   spl     First version for SDM660.
 
  ====================================================================
*/ 

/*=========================================================================
      Include Files
==========================================================================*/

#include "DALDeviceId.h"
#include "ClockDriver.h"
#include "ClockTURING.h"
#include "busywait.h"
#include "ClockSWEVT.h"
#include "ClockTURINGHWIO.h"
#include "npa_resource.h"

/*=========================================================================
      Macros
==========================================================================*/
#define Q6_FMAX_FUSE_SHIFT                   29
#define Q6_FMAX_FUSE_MASK                   0x7

/*=========================================================================
      Type Definitions
==========================================================================*/

uint32 Clock_nHWIOBaseTURING;

/*=========================================================================
      Data
==========================================================================*/

static const char *ClockNPANodeName[] =
{
  CLOCK_NPA_NODE_NAME_CPU,
  CLOCK_NPA_NODE_NAME_CPU_TEST,
  CLOCK_NPA_RESOURCE_QDSS,
  CLOCK_NPA_RESOURCE_CNOC_PERIPH,
  CLOCK_NPA_RESOURCE_SNOC,
  CLOCK_NPA_RESOURCE_CNOC,
  CLOCK_NPA_RESOURCE_AGGR2,
  CLOCK_NPA_RESOURCE_BIMC,
};

static ClockImageCtxtType Clock_ImageCtxt;

/*=========================================================================
      Prototypes
==========================================================================*/
boolean Clock_IsSpeedBinSupported
(
uint32 nSpeedBinFuse
);


/* =========================================================================
      Functions
==========================================================================*/


/* =========================================================================
**  Function : Clock_DetectBSPVersion
** =========================================================================*/
/**
  Detects which BSP configuration to use for the current HW.

  @param *pDrvCtxt [in] -- Pointer to driver context.

  @return
  DAL_ERROR if a valid configuration was not found, other DAL_SUCCESS.

  @dependencies
  None.
*/

static DALResult Clock_DetectBSPVersion
(
  ClockDrvCtxt *pDrvCtxt
)
{
  ClockImageCtxtType     *pImageCtxt;
  ClockCPUPerfConfigType *pCPUPerfConfig;
  uint32                  i;

  pImageCtxt = (ClockImageCtxtType *)pDrvCtxt->pImageCtxt;

  /*-----------------------------------------------------------------------*/
  /* Detect which CPU BSP data to use for this HW version.                 */
  /*-----------------------------------------------------------------------*/

  pCPUPerfConfig = pImageCtxt->pBSPConfig->pCPUPerfConfig;
  for (i = 0; i < pImageCtxt->pBSPConfig->nNumCPUPerfLevelConfigs; i++)
  {
    if (Clock_IsBSPSupported(&pCPUPerfConfig[i].HWVersion) == TRUE && (Clock_IsSpeedBinSupported(pCPUPerfConfig[i].nSpeedBinFuse) == TRUE))
    {
      pImageCtxt->CPUCtxt.PerfConfig.HWVersion = pCPUPerfConfig[i].HWVersion;
      pImageCtxt->CPUCtxt.PerfConfig.anPerfLevel = pCPUPerfConfig[i].anPerfLevel;
      pImageCtxt->CPUCtxt.PerfConfig.nMaxPerfLevel = pCPUPerfConfig[i].nMaxPerfLevel;
      pImageCtxt->CPUCtxt.PerfConfig.nMinPerfLevel = pCPUPerfConfig[i].nMinPerfLevel;
      pImageCtxt->CPUCtxt.PerfConfig.nNumPerfLevels = pCPUPerfConfig[i].nNumPerfLevels;
      pImageCtxt->CPUCtxt.PerfConfig.nSpeedBinFuse = pCPUPerfConfig[i].nSpeedBinFuse;
      break;
    }
  }

  if (i == pImageCtxt->pBSPConfig->nNumCPUPerfLevelConfigs)
  {
    return DAL_ERROR;
  }

  return DAL_SUCCESS;

} /* END of Clock_DetectBSPVersion */


/* =========================================================================
**  Function : ClockStub_InitImage
** =========================================================================*/
/*
  See ClockDriver.h
*/

DALResult ClockStub_InitImage
(
  ClockDrvCtxt *pDrvCtxt
)
{
  uint32 i;
  
  /*-----------------------------------------------------------------------*/
  /* Initialize the SW Events for Clocks.                                  */
  /*-----------------------------------------------------------------------*/

  Clock_SWEvent(CLOCK_EVENT_INIT, 0);

  /*-----------------------------------------------------------------------*/
  /* Create stubs for each NPA node.                                       */
  /*-----------------------------------------------------------------------*/

  for (i = 0; i < ARR_SIZE(ClockNPANodeName); i++)
  {
    npa_stub_resource(ClockNPANodeName[i]);
  }
  
  /*-----------------------------------------------------------------------*/
  /* Good to go.                                                           */
  /*-----------------------------------------------------------------------*/

  return DAL_SUCCESS;

} /* END ClockStub_InitImage */

/* =========================================================================
**  Function : Clock_InitCPUConfig
** =========================================================================*/
/**
  Initializes current configuration of CPU clock
 
  This function is invoked at driver initialization to initialize the current
  CPU configuration.
 
  @param *pDrvCtxt [in] -- Pointer to driver context.

  @return
  DAL_ERROR if configuration was not valid, other DAL_SUCCESS.

  @dependencies
  None.
*/ 

static DALResult Clock_InitCPUConfig
(
  ClockDrvCtxt *pDrvCtxt
)
{
  DALResult eResult;

  /*-----------------------------------------------------------------------*/
  /* Initialize the DCVS module.                                           */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_InitDCVS(pDrvCtxt);

  return eResult;

} /* END Clock_InitCPUConfig */


/* =========================================================================
**  Function : Clock_InitImage
** =========================================================================*/
/*
  See ClockDriver.h
*/ 

DALResult Clock_InitImage
(
  ClockDrvCtxt *pDrvCtxt
)
{
  DALResult eRes;
  uint32 nIdx;
  ClockPropertyValueType PropVal = NULL;
  ClockSourceInitType* pInitSources = NULL;
  HAL_clk_HWIOBaseType *pHWIOBases = NULL;
  ClockIdType nAONBusClkId;

  /*-----------------------------------------------------------------------*/
  /* Get the CPU Configurations.                                           */
  /*-----------------------------------------------------------------------*/

  if(DAL_SUCCESS != Clock_GetPropertyValue("ClockImageConfig", &PropVal))
  {
    return(DAL_ERROR);
  }

  Clock_ImageCtxt.pBSPConfig = (ClockImageBSPConfigType*)PropVal;

  pDrvCtxt->pImageCtxt = &Clock_ImageCtxt;

  /*-----------------------------------------------------------------------*/
  /* Initialize the Q6SS HWIO Base address.                                */
  /*-----------------------------------------------------------------------*/

  if(Clock_nHWIOBaseTURING == 0)
  {
    eRes = Clock_GetPropertyValue("ClockTURINGBase", &PropVal);

    if (eRes != DAL_SUCCESS)
    {
      return(eRes);
    }

    pHWIOBases = (HAL_clk_HWIOBaseType*)PropVal;

    if (pHWIOBases != NULL)
    {
      Clock_MapHWIORegion(
        pHWIOBases->nPhysAddr, pHWIOBases->nSize, &Clock_nHWIOBaseTURING);

      /*
       * If we are unable to map a virtual address, assume the physical one.
       */
      if(Clock_nHWIOBaseTURING == NULL)
      {
        Clock_nHWIOBaseTURING = pHWIOBases->nPhysAddr;
      }
    }
    else
    {
      /*
       * We were unable to get the base address.
       */
      return(DAL_ERROR);
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Detect the BSP version to use.                                        */
  /*-----------------------------------------------------------------------*/

  eRes = Clock_DetectBSPVersion(pDrvCtxt);
  if (eRes != DAL_SUCCESS)
  {
    DALSYS_LogEvent(
      DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Failed to detect the BSP version.");
    return eRes;
  }  

  /*-----------------------------------------------------------------------*/
  /* Initialize the XO module.                                             */
  /*-----------------------------------------------------------------------*/

  Clock_InitXO(pDrvCtxt);

  /*-----------------------------------------------------------------------*/
  /* Initialize CPU core clock frequency configuration.                    */
  /*-----------------------------------------------------------------------*/

  eRes = Clock_InitCPUConfig(pDrvCtxt);
  if (eRes != DAL_SUCCESS)
  {
    DALSYS_LogEvent(
      DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Unable to detect CPU core clock configuration.");
    return eRes;
  }

  /*-----------------------------------------------------------------------*/
  /* Initialize the required PLLs                                          */
  /*-----------------------------------------------------------------------*/

  if (DAL_SUCCESS == Clock_GetPropertyValue("ClockSourcesToInit", &PropVal))
  {
    pInitSources = (ClockSourceInitType*)PropVal;

    if (pInitSources != NULL)
    {
      nIdx = 0;
      while (pInitSources[nIdx].eSource != HAL_CLK_SOURCE_NULL)
      {
        Clock_InitSource(pDrvCtxt,
                         pInitSources[nIdx].eSource,
                         pInitSources[nIdx].nFreqHz);
        nIdx++;
      }
    }
  }

  /*----------------------------------------------------------------------*/
  /* Enable the AON bus clock and set the frequency based on what was     */
  /* programmed in the BSP in the early init.                             */
  /*----------------------------------------------------------------------*/

  if(DAL_SUCCESS == Clock_GetClockId(pDrvCtxt, "turing_wrapper_aon_clk", &nAONBusClkId))
  {
    eRes = Clock_EnableClock(Clock_GetInitialClientCtxt(), nAONBusClkId);

    if (DAL_SUCCESS != eRes)
    {
      DALSYS_LogEvent(
          DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
          "Clock_InitImage:  Failed to enable the turing_wrapper_aon_clk clock.  Error code: %x", eRes);
      return eRes;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Now that NPA is initialized, allow Q6 scaling by the power manager.   */
  /*-----------------------------------------------------------------------*/

  eRes = Clock_EnableDCVS(pDrvCtxt);

  if (DAL_SUCCESS != eRes)
  {
    DALSYS_LogEvent(
      DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Clock_InitImage: Failed to initialize DCVS %d", eRes);
    return eRes;
  }

  /*-----------------------------------------------------------------------*/
  /* Initialize the HVX Coprocessor node.                                  */
  /*-----------------------------------------------------------------------*/

  eRes = Clock_InitHvx(pDrvCtxt);

  if(DAL_SUCCESS != eRes)
  {
    DALSYS_LogEvent(
      DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
      "Clock_InitImage:  Failed to initialize HVX %d", eRes);
    return eRes;
  }
  /*-----------------------------------------------------------------------*/
  /* Good to go.                                                           */
  /*-----------------------------------------------------------------------*/
  
   if (Clock_ImageCtxt.bNPABISTEnabled)
    {
	  if (Clock_ImageCtxt.nNPABISTLogSize == 0)
      {
        Clock_ImageCtxt.nNPABISTLogSize = CLOCK_NPA_BIST_DEFAULT_LOG_SIZE;
      }
	 
	  Clock_NPA_BIST(pDrvCtxt);
    }
  return DAL_SUCCESS;

} /* END Clock_InitImage */


/* =========================================================================
**  Function : Clock_ProcessorSleep
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_ProcessorSleep
(
  ClockDrvCtxt       *pDrvCtxt,
  ClockSleepModeType  eMode,
  uint32              nFlags
)
{

  return DAL_SUCCESS;

} /* END Clock_ProcessorSleep */


/* =========================================================================
**  Function : Clock_ProcessorRestore
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_ProcessorRestore
(
  ClockDrvCtxt       *pDrvCtxt,
  ClockSleepModeType  eMode,
  uint32              nFlags
) 
{

  /*
   * Nothing to do here. HW_VOTE does SPMCTL override handling.
  */

  return DAL_SUCCESS;

} /* END Clock_ProcessorRestore */


/* =========================================================================
**  Function : Clock_AdjustSourceFrequency
** =========================================================================*/
/*
  See DDIClock.h
*/
DALResult Clock_AdjustSourceFrequency
(
   ClockDrvCtxt    *pDrvCtxt,
   ClockSourceType eSource,
   int32           nDeltaLAlpha
)
{
  return DAL_ERROR;

} /* Clock_AdjustSourceFrequency */


DALResult Clock_SelectClockSource
(
   ClockDrvCtxt    *pDrvCtxt,
   ClockIdType     nClock,
   ClockSourceType eSource
)
{

  if (eSource == CLOCK_SOURCE_PRIMARY)
  {
    return DAL_SUCCESS;
  }
  return DAL_ERROR;

} /* Clock_SelectClockSource */


/* =========================================================================
**  Function : Clock_SetOverride
** =========================================================================*/
/*
  See DDIClock.h
*/
void Clock_SetOverride
(
  void
)
{
  /* Nothing to do on Turing. */

} /* Clock_SetOverride */


/* =========================================================================
**  Function : Clock_GetImageCtxt
** =========================================================================*/
/*
  See ClockTURING.h
*/

ClockImageCtxtType* Clock_GetImageCtxt(void)
{
  return &Clock_ImageCtxt;
}

/*
 * Unused APIs are stubbed out here.
 */

DALResult Clock_ImageBIST
(
  ClockDrvCtxt  *pDrvCtxt,
  boolean       *bBISTPassed,
  uint32        *nFailedTests
)
{
  return(DAL_ERROR);
}

/* =========================================================================
**  Function : Clock_IsSpeedBinSupported
** =========================================================================*/

boolean  Clock_IsSpeedBinSupported
(
 uint32 nSpeedBinFuse
)
{
  uint32  nPVS, CurrentSpeedBin;
   
  if (nSpeedBinFuse == 0xFF) return TRUE;

  nPVS = HWIO_IN(QFPROM_RAW_PTE_ROW0_LSB);
  CurrentSpeedBin = ((nPVS >> Q6_FMAX_FUSE_SHIFT) & Q6_FMAX_FUSE_MASK);
  if(CurrentSpeedBin == nSpeedBinFuse)
  {
    return TRUE;
  }
  else 
  {
    return FALSE;
  }
}


DALResult Clock_LoadNV
(
  ClockDrvCtxt  *pDrvCtxt
)
{
  return(DAL_ERROR_NOT_SUPPORTED);
}

/* =========================================================================
**  Function : Clock_NPA_BIST
** =========================================================================*/
/**
  See ClockTURING.h

*/

void Clock_NPA_BIST(ClockDrvCtxt *pDrvCtxt)
{
   uint32                        nCfg;
  DALResult                     nResult;
  ClockCPUConfigType           *pCPUConfig;
  ClockImageCtxtType           *pImageCtxt;
  npa_client_handle             qdsp6_h;
  ClockCPUPerfConfigType       *pCPUPerfConfig;
  npa_query_type                qdsp6_state,test_state;
  uint32                        i, nFreqHz_NPA_state, nFreqHz_Calc, nDisableDCS;
  
  pImageCtxt = (ClockImageCtxtType*)pDrvCtxt->pImageCtxt; 
  pCPUPerfConfig = pImageCtxt->pBSPConfig->pCPUPerfConfig;
  pCPUConfig = pImageCtxt->pBSPConfig->pCPUConfig;
  
  /*-----------------------------------------------------------------------*/
  /* Initialize the NPA BIST log                                           */
  /*-----------------------------------------------------------------------*/

  ULogFront_RealTimeInit(
    &pImageCtxt->hClockNPABISTLog, "Clock NPA BIST Log",
    pImageCtxt->nNPABISTLogSize, ULOG_MEMORY_LOCAL, ULOG_LOCK_OS);
  ULogCore_HeaderSet(
    pImageCtxt->hClockNPABISTLog, "Content-Type: text/tagged-log-1.0;");

  /*-----------------------------------------------------------------------*/
  /* Test clocks through NPA                                               */
  /*-----------------------------------------------------------------------*/
 
    /* Enable DCS after saving current nDisableDCS flag */
    nDisableDCS = pImageCtxt->CPUCtxt.nDisableDCS;
    pImageCtxt->CPUCtxt.nDisableDCS = 0;
    
    qdsp6_h = npa_create_sync_client(
                CLOCK_NPA_NODE_NAME_CPU, "QDSP6_BIST",
                NPA_CLIENT_SUPPRESSIBLE);
	
    /* Save current Q6 state to restore later */
    npa_query_by_name(
      CLOCK_NPA_NODE_NAME_CPU, NPA_QUERY_CURRENT_STATE, &qdsp6_state);

    for (i = pCPUPerfConfig->nMinPerfLevel; i <= pCPUPerfConfig->nMaxPerfLevel;
         i++)
    {
      nCfg = pCPUPerfConfig->anPerfLevel[i];
      ULOG_RT_PRINTF_1(
        pImageCtxt->hClockNPABISTLog, 
        "Testing Q6 clock for frequency: %d Hz", pCPUConfig[nCfg].Mux.nFreqHz);

      npa_issue_scalar_request(qdsp6_h, pCPUConfig[nCfg].Mux.nFreqHz/1000);
      npa_query_by_name(
        CLOCK_NPA_NODE_NAME_CPU, NPA_QUERY_CURRENT_STATE, &test_state);
      nFreqHz_NPA_state = NPA_TO_HZ(test_state.data.state);
      
      ULOG_RT_PRINTF_1(
        pImageCtxt->hClockNPABISTLog, "Q6 resource state frequency   : %d Hz",
        nFreqHz_NPA_state);
      
      nResult = Clock_CalcClockFrequency(
                  pDrvCtxt, (ClockIdType)pImageCtxt->CPUCtxt.pClock,
                  &nFreqHz_Calc);
      
      if (nResult == DAL_SUCCESS)
      {
        if (ABS_DIFF(nFreqHz_NPA_state, nFreqHz_Calc) >
            (CLOCK_NPA_BIST_ERROR_MARGIN_PERCENT/100) * nFreqHz_NPA_state)
        {
          ULOG_RT_PRINTF_1(
            pImageCtxt->hClockNPABISTLog,
            "Q6 calculated frequency       : %d Hz", nFreqHz_Calc);
        }
        else
        {
          ULOG_RT_PRINTF_0(
            pImageCtxt->hClockNPABISTLog,
            "Q6 CPU clock set frequency: SUCCESS");
        }
      }
      else
      {
        ULOG_RT_PRINTF_0(
          pImageCtxt->hClockNPABISTLog,
          "Clock_CalcClockFrequency failed for Q6 clock");
      }
    }
    /* Restore Q6 state & nDisableDCS flag*/
    npa_issue_scalar_request(qdsp6_h, qdsp6_state.data.state);
    npa_complete_request(qdsp6_h);
    pImageCtxt->CPUCtxt.nDisableDCS = nDisableDCS;
  
  return;

} /* END Clock_NPA_BIST */
