/*
===========================================================================
*/
/**
  @file ClockLPASSDCVS.c
  
  DCVS NPA node definitions for SDM660 LPASS clock driver.
*/
/*
  ====================================================================

  Copyright (c) 2017 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ==================================================================== 
  $Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/clock/hw/sdm660/adsp_slpi/src/ClockLPASSDCVS.c#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $
 
  when       who     what, where, why
  --------   ---     -------------------------------------------------
  05/24/17   shm     Programmed EXT_PLL_OVRRD too during CPU switch
  11/11/16   shm     Adding support to switch between PLLs when
                     switching Q6 clock.
  10/04/16   shm     First version for SDM660.
 
  ====================================================================
*/ 


/*=========================================================================
      Include Files
==========================================================================*/

#include "DDIClock.h"
#include "ClockDriver.h"
#include "ClockLPASS.h"
#include "busywait.h"
#include "ClockSWEVT.h"
#include "ClockLPASSHWIO.h"
#include "DDIVCS.h"

#include <DALSys.h>
#include <npa.h>
#include <npa_resource.h>
#include <npa_remote.h>
#include <npa_remote_resource.h>
#include <npa_scheduler.h>
#include "rcecb.h"
#include "rcinit.h"

#include "qurt.h"

/*=========================================================================
      Externs
==========================================================================*/


/*=========================================================================
      Macros
==========================================================================*/

/*
 * NPA Resource handles
 */
#define NPA_RESOURCE_CLK_CPU                                              \
  Clock_NPACPUResources.aResource[CLOCK_RESOURCE_CLK_CPU].handle

#define NPA_RESOURCE_CLK_CPU_TEST                                         \
  Clock_NPACPUResources.aResource[CLOCK_RESOURCE_CLK_CPU_TEST].handle

/*
 * QURT API value for highest priority.
 */
#define QURT_PRIORITY_1 1

/*
 * String name for CPU NAS trigger event.
 */
#define CLOCK_NPA_NAS_TRIGGER_EVENT_NAME  "Clock NAS Event"

/*
 * Clock ID's
 */
#define CLOCK_ID_CPU   "lpass_q6core"


/*=========================================================================
      Type Definitions
==========================================================================*/

/*
 * Enumeration of local CPU resources.
 */
enum
{
  CLOCK_RESOURCE_CLK_CPU = 0,
  CLOCK_RESOURCE_CLK_CPU_TEST,
  CLOCK_RESOURCE_TOTAL
};


/*
 * Clock_NPACPUResourcesType
 *
 * Structure containing the NPA node and resource data for local nodes.
 *
 * aResource[CLOCK_RESOURCE_TOTAL]
 *   - resource data   - /clk/cpu
 *   - resource data   - /clk/cpu.test
 * dependency     - CPU dependency  - /vdd/cx
 * node           - CPU node data   - /node/clk/cpu
 * hClientBIMC    - NPA client      - /clk/bimc
 * hClientRail    - NPA client      - /vdd/cx
 */
typedef struct
{
  npa_resource_definition aResource[CLOCK_RESOURCE_TOTAL];
  npa_node_dependency     dependency;
  npa_node_definition     node;
  npa_client_handle       hClientBIMC;
  npa_client_handle       hClientRail;
  npa_client_handle       hClientAGR2;
} Clock_NPACPUResourcesType;


/*=========================================================================
      Prototypes
==========================================================================*/


static npa_resource_state Clock_NPACPUNodeDriverFunc
(
  npa_resource       *pResource,
  npa_client_handle   hClient,
  npa_resource_state  nState
);

static npa_resource_state Clock_NPACPUResourceDriverFunc
(
  npa_resource       *pResource,
  npa_client_handle   hClient,
  npa_resource_state  nState
);

static npa_resource_state Clock_NPACPUTestResourceDriverFunc
(
  npa_resource       *pResource,
  npa_client_handle   hClient,
  npa_resource_state  nState
);

static void Clock_NPACPUNodeAvailableCallback
(
  void         *pContext,
  unsigned int  nEventType,
  void         *pNodeName,
  unsigned int  nNodeNameSize
);

static void Clock_NPABIMCNodeAvailableCallback
(
  void         *pContext,
  unsigned int  nEventType,
  void         *pNodeName,
  unsigned int  nNodeNameSize
);

static void Clock_NPACPUNASEventCallback
(
  void *pData
);

static void Clock_NPAAGR2NodeAvailableCallback
(
  void         *pContext,
  unsigned int  nEventType,
  void         *pNodeName,
  unsigned int  nNodeNameSize
);

static npa_query_status Clock_NPACPUResourceQuery
(
  npa_resource   *resource,
  unsigned int    id,
  npa_query_type *result
);

static void Clock_RCECBCallback
(
  void
);


/*=========================================================================
      Data
==========================================================================*/

/*
 * NPA remote resources used on LPASS
 */

static npa_remote_resource_definition Clock_aNPARemoteResources[] =
{
  {
    CLOCK_NPA_RESOURCE_QDSS,
    "clk0\x01\x00\x00\x00",
    "/protocol/rpm/rpm",
    &npa_max_plugin,
    npa_remote_resource_local_aggregation_driver_fcn, 
    "STATE",
    NPA_MAX_STATE
  },
  {
    CLOCK_NPA_RESOURCE_CNOC_PERIPH,
    "clk1\x00\x00\x00\x00",
    "/protocol/rpm/rpm",
    &npa_max_plugin,
    npa_remote_resource_local_aggregation_driver_fcn, 
    "KHz",
    NPA_MAX_STATE
  },
  {
    CLOCK_NPA_RESOURCE_SNOC,
    "clk1\x01\x00\x00\x00",
    "/protocol/rpm/rpm",
    &npa_max_plugin,
    npa_remote_resource_local_aggregation_driver_fcn, 
    "KHz",
    NPA_MAX_STATE
  },
  {
    CLOCK_NPA_RESOURCE_CNOC,
    "clk1\x02\x00\x00\x00",
    "/protocol/rpm/rpm",
    &npa_max_plugin,
    npa_remote_resource_local_aggregation_driver_fcn, 
    "KHz",
    NPA_MAX_STATE
  },
  {
    CLOCK_NPA_RESOURCE_SNOC_HS,
    "clk1\x03\x00\x00\x00",
    "/protocol/rpm/rpm",
    &npa_max_plugin,
    npa_remote_resource_local_aggregation_driver_fcn,
    "KHz",
    NPA_MAX_STATE
  },
};


static npa_remote_resource_definition Clock_aAGRNOC2NPARemoteResource =
{
  CLOCK_NPA_RESOURCE_AGGR2,
  "aggr\x02\x00\x00\x00",
  "/protocol/rpm/rpm",
  &npa_max_plugin,
  npa_remote_resource_local_aggregation_driver_fcn,
  "KHz",
  NPA_MAX_STATE
};


/*
 * BIMC NPA remote resource used
 */
static npa_remote_resource_definition Clock_aBIMCNPARemoteResource =
{
  CLOCK_NPA_RESOURCE_BIMC,
  "clk2\x00\x00\x00\x00",
  "/protocol/rpm/rpm",
  &npa_max_plugin,
  npa_remote_resource_local_aggregation_driver_fcn,
  "KHz",
  NPA_MAX_STATE
};


/*
 * Define the local clock resources.
 */
static Clock_NPACPUResourcesType Clock_NPACPUResources =
{
  /*
   * aResource
   */
  {
    /*
     * CPU
     */
    {
      CLOCK_NPA_NODE_NAME_CPU,
      "KHz",
      0,  /* Max, fill in later */
      &npa_max_plugin,
      NPA_RESOURCE_DEFAULT | NPA_RESOURCE_IMPULSE_UNCONDITIONAL,
      (npa_user_data)NULL,
      Clock_NPACPUResourceQuery
    },

    /*
     * CPU Test
     */
    {
      CLOCK_NPA_NODE_NAME_CPU_TEST,
      "KHz",
      0,  /* Max, fill in later */
      &npa_max_plugin,
      NPA_RESOURCE_SINGLE_CLIENT,
      (npa_user_data)NULL,
      Clock_NPACPUResourceQuery
    }
  },

  /*
   * dependency
   */
  {
    NULL,          // Fill in rail string name from BSP data at init
    NPA_NO_CLIENT  // No client used because NPA doesn't allow specifying
                   // additional client data as part of this node creation
                   // process.  A separate client handle is created using
                   // a different NPA API that does allow client data parameters.
  },

  /*
   * node
   */
  {
    "/node" CLOCK_NPA_NODE_NAME_CPU,                /* name       */
    Clock_NPACPUNodeDriverFunc,                     /* driver_fcn */
    NPA_NODE_DEFAULT,                               /* attributes */
    NULL,                                           /* data       */
    1,                                              /* dep count  */
    &Clock_NPACPUResources.dependency,              /* dependency */
    ARR_SIZE(Clock_NPACPUResources.aResource),      /* res count  */
    Clock_NPACPUResources.aResource                 /* resource   */
  }
};

static Clock_VRegWarmUpType *Clock_VRegWarmupTable;

#define CLOCK_GET_WARMUP_DELTA(OpVdd, RetVdd) ((((((OpVdd) - (RetVdd))/12500) * 33300)/30500) + 1)

/*=========================================================================
      Functions
==========================================================================*/


/* =========================================================================
**  Function : Clock_UpdateWarmupTime
** =========================================================================*/
/*
  Programs the voltage warm-up time based on
*/

DALResult Clock_UpdateWarmupTime
(
  ClockDrvCtxt *pDrvCtxt,
  VCSCornerType eVRegLevel
)
{
  uint32 nWarmUpTime = 0;

  if (eVRegLevel < VCS_CORNER_NUM_OF_CORNERS)
  {
    /*
     * Program the AON controller with new warmup time.
     */
    nWarmUpTime = 
      CLOCK_GET_WARMUP_DELTA(Clock_VRegWarmupTable[eVRegLevel].nVoltageUV,
                             Clock_VRegWarmupTable[VCS_CORNER_RETENTION].nVoltageUV);
    
    HWIO_OUTF(LPASS_PMU_SWITCHER_DLY, PMU_SWITCHER_DLY, nWarmUpTime);

    return DAL_SUCCESS;
  }
  return DAL_ERROR;

}


/* =========================================================================
**  Function : Clock_SetCPUConfig
** =========================================================================*/
/**
  Set CPU configuration.
 
  This function sets CPU configuration based on input parameters.
 
  @param *pDrvCtxt [in] -- Pointer to driver context.
  @param  pConfig  [in] -- New configuration.
  @param  bIsNASRequest[in] - Boolean flag to indicate NAS vs. immediate requests.

  @return
  DAL_SUCCESS -- CPU clock set successfully.
  DAL_ERROR  --  CPU clock not set successfully.

  @dependencies
  None.
*/ 

DALResult Clock_SetCPUConfig
(
  ClockDrvCtxt       *pDrvCtxt,
  ClockCPUConfigType *pNewConfig,
  boolean             bIsNASRequest
)
{
  ClockNodeType       *pClock;
  int                  nResult;
  ClockSourceNodeType *pSource;
  boolean              bResult;
  DALResult            eResult;
  qurt_thread_t        ThreadId;
  ClockImageCtxtType  *pImageCtxt;
  ClockCPUConfigType  *pPreviousConfig;
  int                  nThreadPreviousPriority;

  /*-----------------------------------------------------------------------*/
  /* Get config data.                                                      */
  /*-----------------------------------------------------------------------*/

  pImageCtxt = (ClockImageCtxtType *)pDrvCtxt->pImageCtxt;
  pPreviousConfig = pImageCtxt->CPUCtxt.pConfig;
  pClock = pImageCtxt->CPUCtxt.pClock;
  pSource = pClock->pDomain->pSource;

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if the configuration is already active.                 */
  /*-----------------------------------------------------------------------*/

  if (pNewConfig == pPreviousConfig)
  {
    return DAL_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Schedule event w/NPA to handle post wake up portion of NAS request.   */
  /*-----------------------------------------------------------------------*/

  if (bIsNASRequest)
  {
    ULOG_RT_PRINTF_2(
      pDrvCtxt->hClockLog,
      "CPU NAS[1] switch start - Frequency[%lu -> %lu] Hz",
      pPreviousConfig->Mux.nFreqHz,
      pNewConfig->Mux.nFreqHz);

    /*
     * Keep track of the scheduled NAS request.
     */
    pImageCtxt->CPUCtxt.pNASConfig = pNewConfig;

    /*
     * Increment the NAS request counter while entering sleep.
     * This is used to match the number of NAS event callbacks invoked.
     */
    pImageCtxt->CPUCtxt.nNASRequestCount++;

    /*
     * Post NAS custom event to NPA work loop.
     * NPA will invoke our callback to handle the NAS request on wake up.
     */
    npa_notify_next_awake(Clock_NPACPUNASEventCallback, (void *)pNewConfig);
  }

  /*-----------------------------------------------------------------------*/
  /* Pre-frequency voltage update                                          */
  /*-----------------------------------------------------------------------*/

  if (pNewConfig->Mux.eVRegLevel > pPreviousConfig->Mux.eVRegLevel)
  {
    /*
     * Verify we can satisfy the change in voltage requirement.
     */
    if (Clock_NPACPUResources.hClientRail == NULL)
    {
      DALSYS_LogEvent(
        DALDEVICEID_CLOCK,
        DALSYS_LOGEVENT_FATAL_ERROR,
        "CPU handle to voltage rail NPA resource is NULL - unable to satisfy change in voltage requirement.");
    }

    /*
     * Propagate NAS attribute.
     * This is only necessary if raising the voltage, we don't want to schedule
     * a lower voltage for NAS since the CPU gets reconfigured on wake up and
     * could be under voltage if we wake up at a lower voltage than what the
     * current CPU configuration requires.
     */
    if (bIsNASRequest)
    {
      npa_set_request_attribute(
        Clock_NPACPUResources.hClientRail,
        NPA_REQUEST_NEXT_AWAKE);
    }

    npa_issue_scalar_request(
      Clock_NPACPUResources.hClientRail,
      pNewConfig->Mux.eVRegLevel);
  }

  /*-----------------------------------------------------------------------*/
  /* Return immediately if request is for NAS - change config on wake up.  */
  /*-----------------------------------------------------------------------*/

  if (bIsNASRequest)
  {
    return DAL_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Skip over HAL calls if HW_LOGIC flag is set.                          */
  /*-----------------------------------------------------------------------*/

  if (!(pImageCtxt->CPUCtxt.nDisableDCS & CLOCK_FLAG_DISABLED_HW_LOGIC))
  {
    /*
     * Pre-frequency STRAP_ACC update.
     */
    if (pNewConfig->Mux.nFreqHz > pPreviousConfig->Mux.nFreqHz)
    {
      HWIO_OUT(LPASS_QDSP6SS_STRAP_ACC, pNewConfig->nStrapACCVal);
    }

    /*
     * Get thread's current priority & save it. Then, raise to highest priority
     */
    ThreadId = qurt_thread_get_id();
    nThreadPreviousPriority = qurt_thread_get_priority(ThreadId);
    nResult = qurt_thread_set_priority(ThreadId, QURT_PRIORITY_1);
    if (nResult != 0)
    {
      DALSYS_LogEvent(
        DALDEVICEID_CLOCK,
        DALSYS_LOGEVENT_FATAL_ERROR,
        "Unable to raise thread's priority during CPU clock switch.");

      return DAL_ERROR_INTERNAL;
    }

    CLOCK_FLAG_SET(pClock->pDomain, DOMAIN_HOLD_VREG_REQUEST);

    if (pNewConfig->Mux.HALConfig.eSource != 
        pPreviousConfig->Mux.HALConfig.eSource)
    {
      /*-----------------------------------------------------------------------*/
      /* Put an extra vote to keep current source ON - we do this since        */
      /* Clock_SetClockConfig could turn OFF current source (if unused), but   */
      /* we want to keep it ON until we switch to GFMUX in HAL_clk_ConfigClock */
      /* function.                                                             */
      /*-----------------------------------------------------------------------*/

      eResult = Clock_EnableSourceInternal(pDrvCtxt, pSource, TRUE);
      if (eResult != DAL_SUCCESS)
      {
        DALSYS_LogEvent(
          DALDEVICEID_CLOCK,
          DALSYS_LOGEVENT_FATAL_ERROR,
          "Unable to enable previous source");

        return eResult;
      }

      /* Change the clock source config. */
      eResult = Clock_SetClockConfig(pDrvCtxt, pClock->pDomain, &pNewConfig->Mux);
      if (DAL_SUCCESS != eResult)
      {
        DALSYS_LogEvent(
          DALDEVICEID_CLOCK,
          DALSYS_LOGEVENT_FATAL_ERROR,
          "Unable to switch CPU clock");

        return eResult;
      }

      /*-----------------------------------------------------------------------*/
      /* Set QDSP6 core configuration.                                         */
      /*-----------------------------------------------------------------------*/
      
      if(pPreviousConfig->CoreConfig != pNewConfig->CoreConfig)
      {
        HAL_clk_ConfigClock(pClock->HALHandle, pNewConfig->CoreConfig);
      }

      /*-----------------------------------------------------------------------*/
      /* Releasing our vote for old source.                                    */
      /*-----------------------------------------------------------------------*/

      eResult = Clock_DisableSourceInternal(pDrvCtxt, pSource, TRUE, FALSE);
      if (eResult != DAL_SUCCESS)
      {
        DALSYS_LogEvent(
          DALDEVICEID_CLOCK,
          DALSYS_LOGEVENT_FATAL_ERROR,
          "Unable to disable previous source");

        return eResult;
      }
    }
    else
    {
      /*
       * Only RCG update is required if switching between levels derived
       * from SCC PLL.
       */
      if (pNewConfig->Mux.HALConfig.eSource == HAL_CLK_SOURCE_SCCPLL0)
      {
        HAL_clk_ConfigClockMux(
          pClock->pDomain->HALHandle,
          &pNewConfig->Mux.HALConfig);
      }
      else
      {
        /*
         * Update RCG before slewing the PLL if frequency is decreasing.
         */
        if ((pNewConfig->Mux.nFreqHz < pPreviousConfig->Mux.nFreqHz) &&
            (pNewConfig->Mux.HALConfig.nDiv2x !=
             pPreviousConfig->Mux.HALConfig.nDiv2x))
        {
          HAL_clk_ConfigClockMux(
            pClock->pDomain->HALHandle,
            &pNewConfig->Mux.HALConfig);
        }
      
      /*
       * Slew Q6 PLL.
       */
        bResult =
          HAL_clk_ConfigPLL(
            pNewConfig->Mux.HALConfig.eSource,
            &pNewConfig->Mux.pSourceFreqConfig->HALConfig,
            HAL_CLK_SOURCE_CONFIG_MODE_SLEW);
        if (bResult != TRUE)
        {
          DALSYS_LogEvent(
            DALDEVICEID_CLOCK,
            DALSYS_LOGEVENT_FATAL_ERROR,
            "Unable to slew Q6 PLL.");
        
          return DAL_ERROR_INTERNAL;
        }
        
        /*
         * Update RCG after slewing the PLL if frequency is increasing.
         */
        if ((pNewConfig->Mux.nFreqHz > pPreviousConfig->Mux.nFreqHz) &&
            (pNewConfig->Mux.HALConfig.nDiv2x !=
             pPreviousConfig->Mux.HALConfig.nDiv2x))
        {
          HAL_clk_ConfigClockMux(
            pClock->pDomain->HALHandle,
            &pNewConfig->Mux.HALConfig);
        }
      }
    }

    /*
     * Restore thread's previous priority
     */
    nResult = qurt_thread_set_priority(ThreadId, (unsigned short)nThreadPreviousPriority);
    if (nResult != 0)
    {
      DALSYS_LogEvent(
        DALDEVICEID_CLOCK,
        DALSYS_LOGEVENT_FATAL_ERROR,
        "Unable to restore thread's priority during CPU clock switch.");

      return DAL_ERROR_INTERNAL;
    }

    /*
     * Post-frequency STRAP_ACC update.
     */
    if (pNewConfig->Mux.nFreqHz < pPreviousConfig->Mux.nFreqHz)
    {
      HWIO_OUT(LPASS_QDSP6SS_STRAP_ACC, pNewConfig->nStrapACCVal);
    }

    CLOCK_FLAG_CLEAR(pClock->pDomain, DOMAIN_HOLD_VREG_REQUEST);
  }

  /*-----------------------------------------------------------------------*/
  /* Post-frequency voltage update                                         */
  /*-----------------------------------------------------------------------*/

  if (pNewConfig->Mux.eVRegLevel < pPreviousConfig->Mux.eVRegLevel)
  {
    /*
     * Verify we can satisfy the change in voltage requirement.
     */
    if (Clock_NPACPUResources.hClientRail == NULL)
    {
      DALSYS_LogEvent(
        DALDEVICEID_CLOCK,
        DALSYS_LOGEVENT_FATAL_ERROR,
        "CPU handle to voltage rail NPA resource is NULL - unable to satisfy change in voltage requirement.");
      
      return DAL_ERROR_INTERNAL;
    }

    npa_issue_scalar_request(
      Clock_NPACPUResources.hClientRail,
      pNewConfig->Mux.eVRegLevel);
  }

  /*-----------------------------------------------------------------------*/
  /* Update state.                                                         */
  /*-----------------------------------------------------------------------*/

  pImageCtxt->CPUCtxt.pConfig = pNewConfig;
  pClock->pDomain->pActiveMuxConfig = &pNewConfig->Mux;
  pClock->pDomain->pSource->pActiveFreqConfig =
    pNewConfig->Mux.pSourceFreqConfig;

  /*-----------------------------------------------------------------------*/
  /* Update CPU domain VRegRequest so that ClockDriver.cmm knows how to    */
  /* interpret the voltage requirement for this domain.                    */
  /*-----------------------------------------------------------------------*/

  pClock->pDomain->VRegRequest.eVRegLevel = pNewConfig->Mux.eVRegLevel;

  /*-----------------------------------------------------------------------*/
  /* Update the voltage warmup time for when coming out of retention.      */
  /*-----------------------------------------------------------------------*/

  Clock_UpdateWarmupTime(pDrvCtxt, pNewConfig->Mux.eVRegLevel);

  /*-----------------------------------------------------------------------*/
  /* Log clock frequency.                                                  */
  /*-----------------------------------------------------------------------*/

  Clock_SWEvent(
    CLOCK_EVENT_CLOCK_FREQ,
    2,
    HAL_clk_GetTestClockId(pClock->HALHandle),
    pNewConfig->Mux.nFreqHz / 1000);

  /*-----------------------------------------------------------------------*/
  /* Configure SPM to check only PLL states during                         */
  /* power collapse sequence.                                              */
  /*-----------------------------------------------------------------------*/
  
  if (pNewConfig->Mux.HALConfig.eSource !=
      pPreviousConfig->Mux.HALConfig.eSource)
  {
    if (pNewConfig->Mux.HALConfig.eSource == HAL_CLK_SOURCE_SCCPLL0)
    {
      HWIO_OUTF(LPASS_QDSP6SS_SPM_EVENT_CTL, PLL_OVRRD, 1);
      HWIO_OUTF(LPASS_QDSP6SS_SPM_EVENT_CTL, EXT_PLL_OVRRD, 0);
    }
    else
    {
      HWIO_OUTF(LPASS_QDSP6SS_SPM_EVENT_CTL, PLL_OVRRD, 0);
      HWIO_OUTF(LPASS_QDSP6SS_SPM_EVENT_CTL, EXT_PLL_OVRRD, 1);
    }
  }
  
  return DAL_SUCCESS;

} /* END Clock_SetCPUConfig */


/* =========================================================================
**  Function : Clock_SetCPUFrequency
** =========================================================================*/
/**
  Sets CPU frequency

  This function sets CPU frequency based on input parameters.

  @param *pDrvCtxt [in] -- Pointer to driver context.
  @param  nFreqHz  [in] -- New frequency.
  @param  bIsNASRequest[in] - Boolean flag to indicate NAS vs. immediate requests.

  @return
  DAL_SUCCESS -- CPU clock set successfully.
  DAL_ERROR  --  CPU clock not set successfully.

  @dependencies
  None.
*/

static DALResult Clock_SetCPUFrequency
(
  ClockDrvCtxt *pDrvCtxt,
  uint32        nFreqHz,
  boolean       bIsNASRequest
)
{
  ClockImageCtxtType     *pImageCtxt;
  ClockCPUPerfConfigType *pCPUPerfConfig;
  ClockCPUConfigType     *pCPUConfig;
  DALResult               eResult;
  uint32                  nConfig, nPL;

  pImageCtxt = (ClockImageCtxtType *)pDrvCtxt->pImageCtxt;
  pCPUPerfConfig = &pImageCtxt->CPUCtxt.PerfConfig;
  pCPUConfig  = pImageCtxt->pBSPConfig->pCPUConfig;

  /*-----------------------------------------------------------------------*/
  /* Find minimum performance level.                                       */
  /*-----------------------------------------------------------------------*/

  nPL = pCPUPerfConfig->nMinPerfLevel;
  for ( ; nPL < pCPUPerfConfig->nMaxPerfLevel; nPL++)
  {
    nConfig = pCPUPerfConfig->anPerfLevel[nPL];
    if (pCPUConfig[nConfig].Mux.nFreqHz >= nFreqHz)
    {
      break;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* If we've defaulted to the max frequency.                              */
  /*-----------------------------------------------------------------------*/

  if (nPL == pCPUPerfConfig->nMaxPerfLevel)
  {
    /*
     * Unwrap until we find the latest supported frequency.
     */
    if (Clock_IsBSPSupported(&pCPUConfig[nPL].Mux.HWVersion) == FALSE)
    {
      nPL--;
      for (; nPL >= pCPUPerfConfig->nMinPerfLevel; nPL--)
      {
        if (Clock_IsBSPSupported(&pCPUConfig[nPL].Mux.HWVersion) == TRUE)
    {
      break;
    }
  }
    }
  }

  nConfig = pCPUPerfConfig->anPerfLevel[nPL];

  /*-----------------------------------------------------------------------*/
  /* Switch the CPU clock.                                                 */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_SetCPUConfig(pDrvCtxt, &pCPUConfig[nConfig], bIsNASRequest);

  return eResult;

} /* END of Clock_SetCPUFrequency */


/* =========================================================================
**  Function : Clock_FindCPUMaxConfigAtVoltage
** =========================================================================*/
/*
  See ClockDriver.h
*/

DALResult Clock_FindCPUMaxConfigAtVoltage
(
  ClockDrvCtxt         *pDrvCtxt,
  ClockCPUConfigType  **pConfig,
  uint32                nCorner
)
{
  ClockImageCtxtType *pImageCtxt;
  ClockCPUConfigType *pCPUConfig, *pTempConfig;
  uint32              nMinPL, nMaxPL, nPL, nConfig;

  /*-----------------------------------------------------------------------*/
  /* Get config data.                                                      */
  /*-----------------------------------------------------------------------*/

  pImageCtxt = (ClockImageCtxtType *)pDrvCtxt->pImageCtxt;

  /*-----------------------------------------------------------------------*/
  /* Validate argument.                                                    */
  /*-----------------------------------------------------------------------*/

  if (pConfig == NULL)
  {
    return DAL_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* Find the highest frequency configuration.                             */
  /*-----------------------------------------------------------------------*/

  nMinPL = pImageCtxt->CPUCtxt.PerfConfig.nMinPerfLevel;
  nMaxPL = pImageCtxt->CPUCtxt.PerfConfig.nMaxPerfLevel;
  pCPUConfig = pImageCtxt->pBSPConfig->pCPUConfig;
  pTempConfig = NULL;

  for (nPL = nMinPL; nPL <= nMaxPL; nPL++)
  {
    nConfig = pImageCtxt->CPUCtxt.PerfConfig.anPerfLevel[nPL];

    if (pCPUConfig[nConfig].Mux.eVRegLevel > nCorner)
    {
      break;
    }
    else
    {
      pTempConfig = &pCPUConfig[nConfig];
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Validate config was found.                                            */
  /*-----------------------------------------------------------------------*/

  if (pTempConfig == NULL)
  {
    return DAL_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* Store config for caller.                                              */
  /*-----------------------------------------------------------------------*/

  *pConfig = pTempConfig;

  return DAL_SUCCESS;

} /* END Clock_FindCPUMaxConfigAtVoltage */


/* =========================================================================
**  Function : Clock_SetCPUMaxFrequencyAtCurrentVoltage
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_SetCPUMaxFrequencyAtCurrentVoltage
(
  ClockDrvCtxt *pDrvCtxt,
  boolean       bRequired,
  uint32       *pnResultFreqHz
)
{
  DALResult           eResult;
  ClockImageCtxtType *pImageCtxt;
  ClockCPUConfigType *pConfig;
  uint32              nCorner;

  pImageCtxt = (ClockImageCtxtType *)pDrvCtxt->pImageCtxt;

  /*-----------------------------------------------------------------------*/
  /* Find max config @ current voltage if required.                        */
  /*-----------------------------------------------------------------------*/

  if (bRequired == TRUE)
  {
    /*
     * Find the max CPU config at the current voltage.
     */
    nCorner = pImageCtxt->CPUCtxt.pConfig->Mux.eVRegLevel;
    eResult = Clock_FindCPUMaxConfigAtVoltage(pDrvCtxt, &pConfig, nCorner);
    if (eResult != DAL_SUCCESS)
    {
      return DAL_ERROR_INTERNAL;
    }

    /*
     * Configure the CPU to the max supported frequency at the current voltage.
     */
    eResult = Clock_SetCPUFrequency(pDrvCtxt, pConfig->Mux.nFreqHz, FALSE);
    if (eResult != DAL_SUCCESS)
    {
      return DAL_ERROR_INTERNAL;
    }

    /*
     * Overwrite the active state (in KHz) of the NPA node.
     */
    pConfig = pImageCtxt->CPUCtxt.pConfig;
    npa_assign_resource_state(NPA_RESOURCE_CLK_CPU, pConfig->Mux.nFreqHz / 1000);

    /*
     * Update result for caller.
     */
    if (pnResultFreqHz != NULL)
    {
      *pnResultFreqHz = pConfig->Mux.nFreqHz;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Restore CPU to requested state.                                       */
  /*-----------------------------------------------------------------------*/

  else
  {
    /*
     * Impulse request results in the resource restoring to its prior value.
     * Only issue if no NAS request pending since the NPA scheduler will
     * invoke the NAS event callback with the final frequency state.
     */
    if (pImageCtxt->CPUCtxt.pNASConfig == NULL)
    {
      npa_issue_impulse_request(pImageCtxt->CPUCtxt.hNPAClkCPUImpulse);
    }

    /*
     * Update result for caller.
     */
    if (pnResultFreqHz != NULL)
    {
      *pnResultFreqHz = pImageCtxt->CPUCtxt.pConfig->Mux.nFreqHz;
    }
  }

  return DAL_SUCCESS;

} /* END Clock_SetCPUMaxFrequencyAtCurrentVoltage */


/* =========================================================================
**  Function : Clock_InitDCVS
** =========================================================================*/
/*
  See ClockDriver.h
*/

DALResult Clock_InitDCVS
(
  ClockDrvCtxt *pDrvCtxt
)
{
  uint32              i, nPL, nConfig;
  npa_resource_state  nInitialStates[CLOCK_RESOURCE_TOTAL];
  ClockImageCtxtType *pImageCtxt;
  RCECB_HANDLE        rcecbHandle;
  ClockNPAResourcePubType *pResourcePub = NULL;
  ClockPropertyValueType PropVal = NULL;

  pImageCtxt = (ClockImageCtxtType *)pDrvCtxt->pImageCtxt;

  /*-----------------------------------------------------------------------*/
  /* We must disable scaling until:                                        */
  /*  - EFS init has complete.                                             */
  /*-----------------------------------------------------------------------*/

//  pImageCtxt->CPUCtxt.nDisableDCS = CLOCK_FLAG_DISABLED_BY_EFS;

  /*-----------------------------------------------------------------------*/
  /* Disable DCS if specified in the BSP.                                  */
  /*-----------------------------------------------------------------------*/

  if (pImageCtxt->pBSPConfig->bEnableDCS != TRUE)
  {
    pImageCtxt->CPUCtxt.nDisableDCS |= CLOCK_FLAG_DISABLED_BY_BSP;
  }

  /*-----------------------------------------------------------------------*/
  /* Create callback for end of RCINIT to lower BIMC vote.                 */
  /*-----------------------------------------------------------------------*/

  rcecbHandle =
    rcecb_register_name(
      RCINIT_RCECB_INITGROUPS,
      (RCECB_CALLBACK_FNSIG_P0)Clock_RCECBCallback);
  if (rcecbHandle == NULL)
  {
    return DAL_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* Get the Voltage Warmup Table from the BSP.                            */
  /*-----------------------------------------------------------------------*/

  if (DAL_SUCCESS != Clock_GetPropertyValue("Clock_VRegWarmupTable", &PropVal))
  {
    return DAL_ERROR;
  }

  Clock_VRegWarmupTable = (Clock_VRegWarmUpType*)PropVal;

  /*-----------------------------------------------------------------------*/
  /* Create our remote nodes.                                              */
  /*-----------------------------------------------------------------------*/

  for (i = 0; i < ARR_SIZE(Clock_aNPARemoteResources); i++)
  {
    npa_remote_define_resource(
      &Clock_aNPARemoteResources[i],
      (npa_resource_state)0,
      NULL);
  }

  /*-----------------------------------------------------------------------*/
  /* Create our AggrNOC2 remote node.                                      */
  /*-----------------------------------------------------------------------*/

  npa_remote_define_resource_cb(
    &Clock_aAGRNOC2NPARemoteResource,
    (npa_resource_state)NPA_MAX_STATE,
    Clock_NPAAGR2NodeAvailableCallback,
    NULL);

  /*-----------------------------------------------------------------------*/
  /* Create our BIMC remote node.                                          */
  /*-----------------------------------------------------------------------*/

  npa_remote_define_resource_cb(
    &Clock_aBIMCNPARemoteResource,
    (npa_resource_state)NPA_MAX_STATE,
    Clock_NPABIMCNodeAvailableCallback,
    NULL);

  /*-----------------------------------------------------------------------*/
  /* Init the NPA CPU resource/node                                        */
  /* NOTE: Our inital request is the current configuration.                */
  /*-----------------------------------------------------------------------*/

  Clock_NPACPUResources.node.data = (npa_user_data)pDrvCtxt;
  Clock_NPACPUResources.dependency.name = pImageCtxt->pBSPConfig->szRailName;

  nPL     = pImageCtxt->CPUCtxt.PerfConfig.nMaxPerfLevel;
  nConfig = pImageCtxt->CPUCtxt.PerfConfig.anPerfLevel[nPL];

  for (i = 0; i < Clock_NPACPUResources.node.resource_count; i++)
  {
    Clock_NPACPUResources.aResource[i].max =
      pImageCtxt->pBSPConfig->pCPUConfig[nConfig].Mux.nFreqHz / 1000;
  }

  nInitialStates[CLOCK_RESOURCE_CLK_CPU] =
    Clock_NPACPUResources.aResource[CLOCK_RESOURCE_CLK_CPU].max;
  nInitialStates[CLOCK_RESOURCE_CLK_CPU_TEST] = 0;

  npa_define_node_cb(
    &Clock_NPACPUResources.node,
    nInitialStates,
    Clock_NPACPUNodeAvailableCallback,
    pDrvCtxt);

  /*-----------------------------------------------------------------------*/
  /* Publish any resources requiring exposure for MPD                      */
  /*-----------------------------------------------------------------------*/

  if (DAL_SUCCESS == Clock_GetPropertyValue("ClockResourcePub", &PropVal))
  {
    pResourcePub = (ClockNPAResourcePubType*)PropVal;

    if ((NULL != pResourcePub) && (pResourcePub->nTotalResources > 0))
    {
      npa_remote_publish_resources(pResourcePub->nDomain, 
                                   pResourcePub->nTotalResources, 
                                   pResourcePub->ppszResourceList);
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Good to go.                                                           */
  /*-----------------------------------------------------------------------*/

  return DAL_SUCCESS;

} /* END Clock_InitDCVS */


/* =========================================================================
**  Function : Clock_EnableDCVS
** =========================================================================*/
/*
  See DDIClock.h
*/

DALResult Clock_EnableDCVS
(
  ClockDrvCtxt *pDrvCtxt
) 
{
  //struct npa_resource *pResource;

  /*-----------------------------------------------------------------------*/
  /* Set flag to enable DCVS.                                              */
  /*-----------------------------------------------------------------------*/

  if (pDrvCtxt->bDCVSEnabled)
  {
    return DAL_SUCCESS;
  }

  pDrvCtxt->bDCVSEnabled = TRUE;

  /*
   * No state update triggering here.  We keep Q6 at constant frequency until
   * ADSPPM is ready to request different performance levels.
   */

  return DAL_SUCCESS;

} /* END Clock_EnableDCVS */


/* =========================================================================
**  Function : Clock_InitializeCPUMax
** =========================================================================*/
/**
  Explicitly set the CPU to the maximum supported performance level in order
  to minimize the latency of SW boot up.

  This function is only called once by the CPU resource driver function
  when the CPU resource is being created.  We're guaranteed to have rail voting
  available at this time which allows the CPU clock to be scaled to any
  performance level regardless of how the BSP min/max may have been configured.

  Boot is not capable of placing voltage votes so there is a dependency on
  a proxy vote of >= NOMINAL since the Q6 is configured to the maximum config
  at NOMINAL.  This function initializes the SW context as the CPU was last
  configured in the __hexagon_bsp_init (see HALclkInitASM.S).

  This function avoids explicitly switching to TURBO to avoid potential issues
  with going to the highest voltage which has not always been possible for all
  HW versions and even more so during the bring-up phase of a target.

  @param *pDrvCtxt [in] -- Pointer to driver context.

  @return
  DAL_SUCCESS -- CPU clock initialized successfully.
  DAL_ERROR  --  CPU clock not initialized successfully.

  @dependencies
  None.
*/

static DALResult Clock_InitializeCPUMax
(
  ClockDrvCtxt *pDrvCtxt
)
{
  DALResult            eResult;
  ClockImageCtxtType  *pImageCtxt;
  ClockNodeType       *pClock;
  ClockSourceNodeType *pSource;
  ClockCPUConfigType  *pCPUConfig;
  uint32               nPL, nConfig, nSourceIndex;

  pImageCtxt = (ClockImageCtxtType *)pDrvCtxt->pImageCtxt;

  /*-----------------------------------------------------------------------*/
  /* Get CPU clock ID.                                                     */
  /*-----------------------------------------------------------------------*/

  eResult =
    Clock_GetClockId(
      pDrvCtxt, CLOCK_ID_CPU,
      (ClockIdType *)&pImageCtxt->CPUCtxt.pClock);
  if (eResult != DAL_SUCCESS)
  {
    return DAL_ERROR_INTERNAL;
  }

  pClock = pImageCtxt->CPUCtxt.pClock;

  /*-----------------------------------------------------------------------*/
  /* Setup clock/domain/source structures to reflect what configuration    */
  /* was put in place by the boot path.                                    */
  /*-----------------------------------------------------------------------*/

  nPL = pImageCtxt->pBSPConfig->nCPUBootPerfLevel;
  nConfig = pImageCtxt->pBSPConfig->pCPUPerfConfig->anPerfLevel[nPL];
  pCPUConfig = &pImageCtxt->pBSPConfig->pCPUConfig[nConfig];

  /*-----------------------------------------------------------------------*/
  /* Vote for current voltage requirement to initialize the CPU vote.      */
  /*-----------------------------------------------------------------------*/

  npa_issue_scalar_request(
    Clock_NPACPUResources.hClientRail,
    pCPUConfig->Mux.eVRegLevel);

  /*-----------------------------------------------------------------------*/
  /* Get source node.                                                      */
  /*-----------------------------------------------------------------------*/

  nSourceIndex = pDrvCtxt->anSourceIndex[pCPUConfig->Mux.HALConfig.eSource];
  if (nSourceIndex == 0xFF)
  {
    return DAL_ERROR_INTERNAL;
  }

  pSource = &pDrvCtxt->aSources[nSourceIndex];
  if (pSource == NULL)
  {
    return DAL_ERROR_INTERNAL;
  }

  /*-----------------------------------------------------------------------*/
  /* Update the Q6 PLL state.                                              */
  /* Mark the CPU PLL as having already been calibrated - done in boot.    */
  /*-----------------------------------------------------------------------*/

  pSource->pActiveFreqConfig = pCPUConfig->Mux.pSourceFreqConfig;
  pSource->nFlags |= CLOCK_FLAG_SOURCE_CALIBRATED;

  /*-----------------------------------------------------------------------*/
  /* Update CPU state.                                                     */
  /*-----------------------------------------------------------------------*/

  pClock->pDomain->pSource = pSource;
  pClock->pDomain->pActiveMuxConfig = &pCPUConfig->Mux;
  pImageCtxt->CPUCtxt.pConfig = pCPUConfig;

  /*-----------------------------------------------------------------------*/
  /* Init NAS context.                                                     */
  /*-----------------------------------------------------------------------*/

  pImageCtxt->CPUCtxt.nNASRequestCount = 0;
  pImageCtxt->CPUCtxt.pNASConfig = NULL;

  /*-----------------------------------------------------------------------*/
  /* Ensure that the CPU core clock/domain/source reference counts are 1.  */
  /*-----------------------------------------------------------------------*/

  eResult =
    Clock_EnableClock(
      Clock_GetInitialClientCtxt(),
      (ClockIdType)pImageCtxt->CPUCtxt.pClock);
  if (eResult != DAL_SUCCESS)
  {
    return DAL_ERROR_INTERNAL;
  }

  /*-----------------------------------------------------------------------*/
  /* Temporary:  Update the voltage warmup time.  This will be moved to    */
  /* VCS once details are worked out.                                      */
  /*-----------------------------------------------------------------------*/

  Clock_UpdateWarmupTime(pDrvCtxt, pCPUConfig->Mux.eVRegLevel);

  /*-----------------------------------------------------------------------*/
  /* Scale CPU to maximum supported performance level.                     */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_SetCPUFrequency(pDrvCtxt, 0xFFFFFFFF, FALSE);
  if (eResult != DAL_SUCCESS)
  {
    return DAL_ERROR_INTERNAL;
  }

  return DAL_SUCCESS;

} /* END Clock_InitializeCPUMax */


/* =========================================================================
**  Function : Clock_NPACPUResourceDriverFunc
** =========================================================================*/
/**
  NPA node driver function for the CPU resource.

  This function handles minimum frequency requests for the CPU NPA resource.

  @param *pResource [in] -- Pointer to resource whose state changed.
  @param hClient    [in] -- Client handle that triggered the change.
  @param nState     [in] -- New request state.

  @return
  npa_resource_state -- The new active state of the resource.

  @dependencies
  None.
*/

static npa_resource_state Clock_NPACPUResourceDriverFunc
(
  npa_resource       *pResource,
  npa_client_handle   hClient,
  npa_resource_state  nState
)
{
  ClockDrvCtxt       *pDrvCtxt;
  ClockImageCtxtType *pImageCtxt;
  DALResult           eResult;
  uint32              nDisableDCS, nFreqHz, nPL, nConfig;
  boolean             bIsNASRequest;
  npa_resource_state  nActiveState;

  pDrvCtxt = (ClockDrvCtxt *)pResource->node->data;
  pImageCtxt = (ClockImageCtxtType *)pDrvCtxt->pImageCtxt;
  nDisableDCS = pImageCtxt->CPUCtxt.nDisableDCS;
  nFreqHz = NPA_TO_HZ(nState);

  /*-----------------------------------------------------------------------*/
  /* Perform necessary setup during resource creation.                     */
  /*-----------------------------------------------------------------------*/

  if (hClient->type == NPA_CLIENT_INITIALIZE)
  {
    /*
     * Create client to the voltage rail resource and specify the CPU id
     * that the voltage requirement must be satisfied for.
     */
    Clock_NPACPUResources.hClientRail =
      npa_create_sync_client_ex(
        pImageCtxt->pBSPConfig->szRailName,
        "CPU",
        NPA_CLIENT_SUPPRESSIBLE,
        (unsigned int)TRUE,
        (void *)&pImageCtxt->pBSPConfig->eCPU);

    if (Clock_NPACPUResources.hClientRail == NULL)
    {
      DALSYS_LogEvent(
        DALDEVICEID_CLOCK,
        DALSYS_LOGEVENT_FATAL_ERROR,
        "Unable to create NPA sync client %s->%s.",
        pImageCtxt->pBSPConfig->szRailName,
        "CPU");

      return 0;
    }

    /*
     * Initialize the CPU to the maximum performance level.
     */
    eResult = Clock_InitializeCPUMax(pDrvCtxt);
    if (eResult != DAL_SUCCESS)
    {
      DALSYS_LogEvent(
        DALDEVICEID_CLOCK,
        DALSYS_LOGEVENT_FATAL_ERROR,
        "Unable to initialize CPU during NPA resource creation.");

      return 0;
    }

    /*
     * Return the current configuration as the active state.
     */
    return pImageCtxt->CPUCtxt.pConfig->Mux.nFreqHz / 1000;
  }

  /*-----------------------------------------------------------------------*/
  /* Short-circuit if DCS is disabled by the CPU test.                     */
  /* This is because we don't want to modify the active state of /clk/cpu  */
  /* when a request has been made on /clk/cpu.test.                        */
  /*-----------------------------------------------------------------------*/

  if (nDisableDCS & CLOCK_FLAG_DISABLED_BY_CPU_TEST)
  {
    return pImageCtxt->CPUCtxt.pConfig->Mux.nFreqHz / 1000;
  }

  if (!pDrvCtxt->bDCVSEnabled)
  {
    return pImageCtxt->CPUCtxt.pConfig->Mux.nFreqHz / 1000;;
  }  

  /*-----------------------------------------------------------------------*/
  /* If any other non-HW bit is set in the disable DCS flag then set the   */
  /* CPU to the maximum performance level.                                 */
  /*-----------------------------------------------------------------------*/

  nDisableDCS &= ~CLOCK_FLAG_DISABLED_BY_CPU_TEST;
  if (nDisableDCS & ~CLOCK_FLAG_DISABLED_HW_LOGIC)
  {
    nPL = pImageCtxt->CPUCtxt.PerfConfig.nMaxPerfLevel;
    nConfig = pImageCtxt->CPUCtxt.PerfConfig.anPerfLevel[nPL];
    nFreqHz = pImageCtxt->pBSPConfig->pCPUConfig[nConfig].Mux.nFreqHz;
  }

  /*-----------------------------------------------------------------------*/
  /* Check for NAS requests.                                               */
  /*-----------------------------------------------------------------------*/

  if (npa_request_has_attribute(hClient, NPA_REQUEST_NEXT_AWAKE))
  {
    bIsNASRequest = TRUE;
  }

  /*-----------------------------------------------------------------------*/
  /* The NPA framework doesn't support immediate requests that occur after */
  /* NAS requests but before going through a sleep transition.  Raise an   */
  /* error here if that case is detected.                                  */
  /*-----------------------------------------------------------------------*/

  else
  {
    bIsNASRequest = FALSE;

    if (pImageCtxt->CPUCtxt.pNASConfig != NULL)
    {
      if (npa_is_next_wakeup_after_nas() != TRUE)
      {
        DALSYS_LogEvent(
          DALDEVICEID_CLOCK,
          DALSYS_LOGEVENT_FATAL_ERROR,
          "Invalid request for frequency[%lu] when pending NAS request for frequency[%lu].",
          NPA_PENDING_REQUEST(hClient).state * 1000,
          pImageCtxt->CPUCtxt.pNASConfig->Mux.nFreqHz);

        return pImageCtxt->CPUCtxt.pNASConfig->Mux.nFreqHz / 1000;
      }
      else
      {
        pImageCtxt->CPUCtxt.pNASConfig = NULL;
      }
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Update clock frequency.                                               */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_SetCPUFrequency(pDrvCtxt, nFreqHz, bIsNASRequest);
  if (eResult != DAL_SUCCESS)
  {
    DALSYS_LogEvent(
      DALDEVICEID_CLOCK,
      DALSYS_LOGEVENT_FATAL_ERROR,
      "Unable to set CPU clock to %lu",
      nFreqHz);
  }

  /*-----------------------------------------------------------------------*/
  /* Clear the FIRE_AND_FORGET attribute because this resource makes no    */
  /* use of that resource and the NPA framework makes decisions if that    */
  /* attribute is set that is unfriendly for local NAS aware resources.    */
  /*-----------------------------------------------------------------------*/

  hClient->request_attr &= ~NPA_REQUEST_FIRE_AND_FORGET;

  /*-----------------------------------------------------------------------*/
  /* Return active state of this resource.                                 */
  /* NAS configurations are stored separately from actual active config.   */
  /*-----------------------------------------------------------------------*/

  if (pImageCtxt->CPUCtxt.pNASConfig != NULL)
  {
    nActiveState = pImageCtxt->CPUCtxt.pNASConfig->Mux.nFreqHz / 1000;
  }
  else
  {
    nActiveState = pImageCtxt->CPUCtxt.pConfig->Mux.nFreqHz / 1000;
  }

  return nActiveState;

} /* END Clock_NPACPUResourceDriverFunc */


/* =========================================================================
**  Function : Clock_NPACPUTestResourceDriverFunc
** =========================================================================*/
/**
  NPA node driver function for the CPU test resource.

  This function handles minimum frequency requests for the CPU test NPA resource.

  @param *pResource [in] -- Pointer to resource whose state changed.
  @param hClient    [in] -- Client handle that triggered the change.
  @param nState     [in] -- New request state.

  @return
  npa_resource_state -- The new active state of the resource.

  @dependencies
  None.
*/

static npa_resource_state Clock_NPACPUTestResourceDriverFunc
(
  npa_resource       *pResource,
  npa_client_handle   hClient,
  npa_resource_state  nState
)
{
  ClockDrvCtxt       *pDrvCtxt;
  ClockImageCtxtType *pImageCtxt;
  DALResult           eResult;

  pDrvCtxt = (ClockDrvCtxt *)pResource->node->data;
  pImageCtxt = (ClockImageCtxtType *)pDrvCtxt->pImageCtxt;

  /*-----------------------------------------------------------------------*/
  /* Nothing to do for initialization.                                     */
  /*-----------------------------------------------------------------------*/

  if (hClient->type == NPA_CLIENT_INITIALIZE)
  {
    return pResource->active_state;
  }

  /*-----------------------------------------------------------------------*/
  /* Satisfy CPU test request frequency.                                   */
  /*-----------------------------------------------------------------------*/

  if (nState)
  {
    /*
     * Set CPU test disable bit in clock scaling flag.
     */
    pImageCtxt->CPUCtxt.nDisableDCS |= CLOCK_FLAG_DISABLED_BY_CPU_TEST;

    /*
     * Set CPU to frequency requested by the test client.
     */
    eResult = Clock_SetCPUFrequency(pDrvCtxt, NPA_TO_HZ(nState), FALSE);
    if (eResult != DAL_SUCCESS)
    {
      DALSYS_LogEvent(
        DALDEVICEID_CLOCK,
        DALSYS_LOGEVENT_FATAL_ERROR,
        "Unable to set test request CPU clock to %l",
        NPA_TO_HZ(nState));
    }
    /*
     * Update the active state of the /clk/cpu resource.
     */
    else
    {
      npa_assign_resource_state(
        NPA_RESOURCE_CLK_CPU,
        pImageCtxt->CPUCtxt.pConfig->Mux.nFreqHz / 1000);
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Clear the disable flag when no client request present.                */
  /*-----------------------------------------------------------------------*/

  else
  {
    /*
     * Clear CPU test disable bit in clock scaling flag.
     */
    pImageCtxt->CPUCtxt.nDisableDCS &= ~CLOCK_FLAG_DISABLED_BY_CPU_TEST;

    /*
     * Set CPU to requested state.
     */
    npa_issue_impulse_request(pImageCtxt->CPUCtxt.hNPAClkCPUImpulse);
  }

  return nState;

} /* END of Clock_NPACPUTestResourceDriverFunc */


/* =========================================================================
**  Function : Clock_NPACPUNodeDriverFunc
** =========================================================================*/
/**
  NPA node driver function for the CPU node.

  This function handles minimum frequency requests for the CPU NPA node.

  @param *pResource [in] -- Pointer to resource whose state changed.
  @param hClient    [in] -- Client handle that triggered the change.
  @param nState     [in] -- New request state.

  @return
  npa_resource_state -- The new active state of the resource.

  @dependencies
  None.
*/

static npa_resource_state Clock_NPACPUNodeDriverFunc
(
  npa_resource       *pResource,
  npa_client_handle   hClient,
  npa_resource_state  nState
)
{
  npa_resource_state nActiveState;

  if (pResource == NPA_RESOURCE_CLK_CPU)
  {
    nActiveState = Clock_NPACPUResourceDriverFunc(pResource, hClient, nState);
  }
  else if (pResource == NPA_RESOURCE_CLK_CPU_TEST)
  {
    nActiveState = Clock_NPACPUTestResourceDriverFunc(pResource, hClient, nState);
  }
  else
  {
    DALSYS_LogEvent (
      DALDEVICEID_CLOCK,
      DALSYS_LOGEVENT_WARNING,
      "Unknown resource requested in CPU node driver func.");

    nActiveState = 0;
  }

  return nActiveState;

} /* END of Clock_NPACPUNodeDriverFunc */


/* =========================================================================
**  Function : Clock_NPACPUNodeAvailableCallback
** =========================================================================*/
/**
  Callback when a /clk/cpu node is created.

  This function is called by the NPA framework when the given /clk/cpu node
  is created.  The creation is delayed until all dependencies are also
  created.

  @param *pContext     [in] -- Context passed in npa_define_node_cb
  @param nEventType    [in] -- Zero.
  @param *pNodeName    [in] -- Name of the node being created.
  @param nNodeNameSize [in] -- Length of the name.

  @return
  None.

  @dependencies
  None.
*/

static void Clock_NPACPUNodeAvailableCallback
(
  void         *pContext,
  unsigned int  nEventType,
  void         *pNodeName,
  unsigned int  nNodeNameSize
)
{
  ClockDrvCtxt       *pDrvCtxt;
  ClockImageCtxtType *pImageCtxt;

  pDrvCtxt = (ClockDrvCtxt *)pContext;
  pImageCtxt = (ClockImageCtxtType *)pDrvCtxt->pImageCtxt;

  /*-----------------------------------------------------------------------*/
  /* Create an impulse client for triggering re-aggregation on the CPU     */
  /* resource.                                                             */
  /*-----------------------------------------------------------------------*/

  pImageCtxt->CPUCtxt.hNPAClkCPUImpulse =
    npa_create_sync_client(
      Clock_NPACPUResources.aResource[CLOCK_RESOURCE_CLK_CPU].name,
      CLOCK_NPA_CLIENT_NAME_CLK_CPU_IMPULSE,
      NPA_CLIENT_IMPULSE);
  if (pImageCtxt->CPUCtxt.hNPAClkCPUImpulse == NULL)
  {
    DALSYS_LogEvent(
      DALDEVICEID_CLOCK,
      DALSYS_LOGEVENT_FATAL_ERROR,
      "Unable to create NPA sync client %s->%s.",
      CLOCK_NPA_CLIENT_NAME_CLK_CPU_IMPULSE,
      CLOCK_NPA_NODE_NAME_CPU);
  }

} /* END Clock_NPACPUNodeAvailableCallback */


/* =========================================================================
**  Function : Clock_NPABIMCNodeAvailableCallback
** =========================================================================*/
/**
  Callback when a /clk/bimc node is created.

  This function is called by the NPA framework when the given /clk/bimc node
  is created.  The creation is delayed until all dependencies are also
  created.

  @param *pContext     [in] -- Context passed in npa_define_node_cb
  @param nEventType    [in] -- Zero.
  @param *pNodeName    [in] -- Name of the node being created.
  @param nNodeNameSize [in] -- Length of the name.

  @return
  None.

  @dependencies
  None.
*/

static void Clock_NPABIMCNodeAvailableCallback
(
  void        *pContext,
  unsigned int nEventType,
  void        *pNodeName,
  unsigned int nNodeNameSize
)
{

  Clock_NPACPUResources.hClientBIMC =
    npa_create_sync_client(
      "/clk/bimc",
      "/clock",
      NPA_CLIENT_SUPPRESSIBLE);

  if (Clock_NPACPUResources.hClientBIMC == NULL)
  {
    DALSYS_LogEvent (
      DALDEVICEID_CLOCK,
      DALSYS_LOGEVENT_FATAL_ERROR,
      "Unable to create NPA sync client %s->%s.",
      "/clk/bimc",
      "/clock");
  }

  /*-----------------------------------------------------------------------*/
  /* Place floor vote in the active set for BIMC so that RPM never power   */
  /* collapses BIMC while MPSS is in the active set.                       */
  /* The value of 1 is used as the minimal value above 0 which will be     */
  /* mapped to an actual performance level on RPM.                         */
  /*-----------------------------------------------------------------------*/

  npa_issue_scalar_request(Clock_NPACPUResources.hClientBIMC, NPA_MAX_STATE);

} /* END Clock_NPABIMCNodeAvailableCallback */


/* =========================================================================
**  Function : Clock_NPACPUNASEventCallback
** =========================================================================*/
/**
  Callback on wake-up for NAS requests submitted to the CPU.

  This function is called by the NPA framework upon wake-up for a NAS
  request that was submitted to the CPU prior to sleep.

  @param *pContext     [in] -- Context passed in npa_create_event_cb.
  @param nEventType    [in] -- Expected to be NPA_EVENT_NAS_REQUEST_ACTIVE.
  @param *pData        [in] -- Event data.
  @param nNodeNameSize [in] -- Size of event data.

  @return
  None.

  @dependencies
  None.
*/

static void Clock_NPACPUNASEventCallback
(
  void *pData
)
{
  DALResult           eResult;
  ClockDrvCtxt       *pDrvCtxt;
  ClockImageCtxtType *pImageCtxt;
  ClockCPUConfigType *pConfig;
  uint32              nPreviousFreqHz;

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/

  pConfig = (ClockCPUConfigType *)pData;
  if (pConfig == NULL)
  {
    DALSYS_LogEvent(
      DALDEVICEID_CLOCK,
      DALSYS_LOGEVENT_FATAL_ERROR,
      "Missing required arguments to NPA NAS event callback on wake up.");

    return;
  }

  pDrvCtxt = Clock_GetDrvCtxtNoLock();
  pImageCtxt = (ClockImageCtxtType *)pDrvCtxt->pImageCtxt;

  /*-----------------------------------------------------------------------*/
  /* Log the NAS Callback                                                  */
  /*-----------------------------------------------------------------------*/

  ULOG_RT_PRINTF_1(
    pDrvCtxt->hClockLog,
    "CPU NPA NAS event callback for frequency[%lu]",
    pConfig->Mux.nFreqHz);

  /*-----------------------------------------------------------------------*/
  /* NPA will potentially invoke this event trigger callback once for each */
  /* NAS request that was made.  We only take action on the first event    */
  /* notification because that was the final NAS state of the resource.    */
  /*-----------------------------------------------------------------------*/

  if (pImageCtxt->CPUCtxt.nNASRequestCount == 0)
  {
    return;
  }

  pImageCtxt->CPUCtxt.nNASRequestCount = 0;

  /*-----------------------------------------------------------------------*/
  /* If there is no pending NAS request it means that an immediate request */
  /* was already satisfied before the NPA scheduler dispatched this        */
  /* callback and thus we must ignore it.                                  */
  /*-----------------------------------------------------------------------*/

  if (pImageCtxt->CPUCtxt.pNASConfig == NULL)
  {
    return;
  }

  /*-----------------------------------------------------------------------*/
  /* Verify the final NAS config matches what was saved in context.        */
  /*-----------------------------------------------------------------------*/

  if (pConfig != pImageCtxt->CPUCtxt.pNASConfig)
  {
    DALSYS_LogEvent(
      DALDEVICEID_CLOCK,
      DALSYS_LOGEVENT_FATAL_ERROR,
      "Unexpected CPU configuration mismatch in NAS event callback on wake up.");

    return;
  }

  /*-----------------------------------------------------------------------*/
  /* Configure CPU to the final NAS request.                               */
  /*-----------------------------------------------------------------------*/

  nPreviousFreqHz = pImageCtxt->CPUCtxt.pConfig->Mux.nFreqHz;
  eResult = Clock_SetCPUConfig(pDrvCtxt, pConfig, FALSE);
  if (eResult != DAL_SUCCESS)
  {
    DALSYS_LogEvent(
      DALDEVICEID_CLOCK,
      DALSYS_LOGEVENT_FATAL_ERROR,
      "Failed to configure CPU to NAS request of %lu Hz",
      pConfig->Mux.nFreqHz);

    return;
  }

  /*-----------------------------------------------------------------------*/
  /* Log the NAS Callback                                                  */
  /*-----------------------------------------------------------------------*/

  ULOG_RT_PRINTF_2(
    pDrvCtxt->hClockLog,
    "CPU NAS[1] switch end - Frequency[%lu -> %lu] Hz",
    nPreviousFreqHz,
    pImageCtxt->CPUCtxt.pConfig->Mux.nFreqHz);

  /*-----------------------------------------------------------------------*/
  /* Clear the NAS config.                                                 */
  /*-----------------------------------------------------------------------*/

  pImageCtxt->CPUCtxt.pNASConfig = NULL;

} /* END of Clock_NPACPUNASEventCallback */


/* =========================================================================
**  Function : Clock_NPAAGR2NodeAvailableCallback
** =========================================================================*/
/**
  Callback when a /clk/agr2 node is created.

  This function is called by the NPA framework when the given /clk/agr2 node
  is created.  The creation is delayed until all dependencies are also
  created.

  @param *pContext     [in] -- Context passed in npa_define_node_cb
  @param nEventType    [in] -- Zero.
  @param *pNodeName    [in] -- Name of the node being created.
  @param nNodeNameSize [in] -- Length of the name.

  @return
  None.

  @dependencies
  None.
*/

static void Clock_NPAAGR2NodeAvailableCallback
(
  void        *pContext,
  unsigned int nEventType,
  void        *pNodeName,
  unsigned int nNodeNameSize
)
{

  Clock_NPACPUResources.hClientAGR2 =
    npa_create_sync_client(
      CLOCK_NPA_RESOURCE_AGGR2,
      "/clock",
      NPA_CLIENT_SUPPRESSIBLE);

  if (Clock_NPACPUResources.hClientAGR2 == NULL)
  {
    DALSYS_LogEvent (
      DALDEVICEID_CLOCK,
      DALSYS_LOGEVENT_FATAL_ERROR,
      "Unable to create NPA sync client %s->%s.",
      CLOCK_NPA_RESOURCE_AGGR2,
      "/clock");
  }

  /*-----------------------------------------------------------------------*/
  /* Place floor vote in the active set for BIMC so that RPM never power   */
  /* collapses BIMC while MPSS is in the active set.                       */
  /* The value of 1 is used as the minimal value above 0 which will be     */
  /* mapped to an actual performance level on RPM.                         */
  /*-----------------------------------------------------------------------*/

  npa_issue_scalar_request(Clock_NPACPUResources.hClientAGR2, NPA_MAX_STATE);

} /* END Clock_NPAAGR2NodeAvailableCallback */


/* =========================================================================
**  Function : Clock_RCECBCallback
** =========================================================================*/
/**
  Callback when the final RCINIT group completes.

  This function is called when the final RCINIT group completes in order for
  the clock driver to reduce its vote on /clk/bimc from MAX_NPA_STATE to 1.
  This is needed to ensure that some entity (the clock driver in this instance)
  maintains a non-zero vote on /clk/bimc so that RPM doesn't power collapse
  BIMC while MPSS is in the active set.

  @return
  None.

  @dependencies
  None.
*/
static void Clock_RCECBCallback
(
  void
)
{
  if (Clock_NPACPUResources.hClientBIMC == NULL)
  {
    DALSYS_LogEvent (
      DALDEVICEID_CLOCK,
      DALSYS_LOGEVENT_FATAL_ERROR,
      "No /clk/bimc NPA client handle to vote on in RCECB callback");
  }

  npa_issue_scalar_request(Clock_NPACPUResources.hClientBIMC, 1);

  if (Clock_NPACPUResources.hClientAGR2 == NULL)
  {
    DALSYS_LogEvent (
      DALDEVICEID_CLOCK,
      DALSYS_LOGEVENT_FATAL_ERROR,
      "No /clk/agr2 NPA client handle to vote on in RCECB callback");
  }

  npa_issue_scalar_request(Clock_NPACPUResources.hClientAGR2, 1);


} /* END Clock_RCECBCallback */


/* =========================================================================
**  Function : Clock_NPACPUResourceQuery
** =========================================================================*/
/**
  NPA CPU resource query function.

  This function is called by NPA query nodes to get a list of supported CPU
  frequencies, or the CPU's vote on its voltage rail.

  @param *resource  [in]  -- Pointer to the resource in question
  @param id         [in]  -- ID of the query.
  @param *result    [out] -- Pointer to the data to be filled by this function.

  @return
  npa_query_status - NPA_QUERY_SUCCESS, if query supported.
                   - NPA_QUERY_UNSUPPORTED_QUERY_ID, if query not supported.

  @dependencies
  None.
*/

static npa_query_status Clock_NPACPUResourceQuery
(
  npa_resource    *pResource,
  unsigned int     id,
  npa_query_type  *pResult
)
{
  ClockDrvCtxt             *pDrvCtxt;
  ClockImageCtxtType       *pImageCtxt;
  ClockCPUConfigType       *pCPUConfig;
  ClockCPUPerfConfigType   *pCPUPerfConfig;
  uint32                    nMinPL, nMaxPL, nConfig, nIndex;
  uint32                    nNumPerfLevels;
  npa_query_status          nStatus;
  DALResult                 eResult;

  pDrvCtxt = (ClockDrvCtxt *)pResource->node->data;
  pImageCtxt = (ClockImageCtxtType *)pDrvCtxt->pImageCtxt;
  pCPUConfig = pImageCtxt->pBSPConfig->pCPUConfig;
  pCPUPerfConfig = NULL;
  nNumPerfLevels = 0;
  nStatus  = NPA_QUERY_UNSUPPORTED_QUERY_ID;

  /*-----------------------------------------------------------------------*/
  /* Get a handle to CPU performance data.                                 */
  /*-----------------------------------------------------------------------*/

  pCPUPerfConfig = &pImageCtxt->CPUCtxt.PerfConfig;

  /*
   * Get min, max, and number of CPU performance levels.
   */
  nMinPL = pCPUPerfConfig->nMinPerfLevel;
  nMaxPL = pCPUPerfConfig->nMaxPerfLevel;
  nNumPerfLevels = nMaxPL - nMinPL + 1;

  /*-----------------------------------------------------------------------*/
  /* If this is a performance level indexing request then return the       */
  /* frequency corresponding to this performance level.                    */
  /*-----------------------------------------------------------------------*/

  if ((id >= CLOCK_NPA_QUERY_PERF_LEVEL_KHZ) &&
      (id < CLOCK_NPA_QUERY_NUM_PERF_LEVELS))
  {
    nIndex = ((uint32)id - (uint32)CLOCK_NPA_QUERY_PERF_LEVEL_KHZ);
    if (nIndex < nNumPerfLevels)
    {
      nConfig = pCPUPerfConfig->anPerfLevel[nMinPL + nIndex];
      pResult->type = NPA_QUERY_TYPE_VALUE;
      pResult->data.value = pCPUConfig[nConfig].Mux.nFreqHz / 1000;
      nStatus = NPA_QUERY_SUCCESS;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Returns the number of performance levels.                             */
  /*-----------------------------------------------------------------------*/

  else if (id == CLOCK_NPA_QUERY_NUM_PERF_LEVELS)
  {
    pResult->type = NPA_QUERY_TYPE_VALUE;
    pResult->data.value = nNumPerfLevels;
    nStatus = NPA_QUERY_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* If this is a max frequency at corner voltage indexing request then    */
  /* return the frequency corresponding to this corner voltage.            */
  /*-----------------------------------------------------------------------*/

  else if ((id >= CLOCK_NPA_QUERY_CPU_MAX_KHZ_AT_CORNER) &&
           (id < CLOCK_NPA_QUERY_MIN_FREQ_KHZ))
  {
    nIndex = ((uint32)id - (uint32)CLOCK_NPA_QUERY_CPU_MAX_KHZ_AT_CORNER);
    if (nIndex < VCS_CORNER_NUM_OF_CORNERS)
    {
      eResult = Clock_FindCPUMaxConfigAtVoltage(pDrvCtxt, &pCPUConfig, nIndex);
      if (eResult == DAL_SUCCESS)
      {
        pResult->type = NPA_QUERY_TYPE_VALUE;
        pResult->data.value = pCPUConfig->Mux.nFreqHz / 1000;
        nStatus = NPA_QUERY_SUCCESS;
      }
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Return the minimum frequency in KHz.                                  */
  /*-----------------------------------------------------------------------*/

  else if (id == CLOCK_NPA_QUERY_MIN_FREQ_KHZ)
  {
    nConfig = pCPUPerfConfig->anPerfLevel[nMinPL];
    pResult->type = NPA_QUERY_TYPE_VALUE;
    pResult->data.value = pCPUConfig[nConfig].Mux.nFreqHz / 1000;
    nStatus = NPA_QUERY_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Return the CPU's corner vote on the voltage rail.                     */
  /*-----------------------------------------------------------------------*/

  else if (id == CLOCK_NPA_QUERY_CPU_RAIL_VOLTAGE_CORNER)
  {
    pResult->type = NPA_QUERY_TYPE_VALUE;
    pResult->data.value = pImageCtxt->CPUCtxt.pConfig->Mux.eVRegLevel;
    nStatus = NPA_QUERY_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Return the identifier of the rail powering the CPU.                   */
  /*-----------------------------------------------------------------------*/

  else if (id == CLOCK_NPA_QUERY_CPU_RAIL_ID)
  {
    pResult->type = NPA_QUERY_TYPE_VALUE;
    pResult->data.value = pImageCtxt->pBSPConfig->eRail;
    nStatus = NPA_QUERY_SUCCESS;
  }

  return nStatus;

} /* END Clock_NPACPUResourceQuery */


