/** @file ClockRPM.c
   
  This file implements specialized image specific functions such
  as init image for RPM, we have few place holders for now. 

  Copyright (c) 2013-2015, Qualcomm Technologies Inc. All rights reserved.
  
**/

/*=============================================================================
                              EDIT HISTORY

  $Header: //components/rel/rpm.bf/1.8/core/systemdrivers/clock/hw/sdm660/ClockRPM.c#6 $ 
  $DateTime: 2017/08/21 09:17:04 $ 
  $Author: pwbldsvc $ 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 05/05/15   vph     Fixed KW errors.
 11/27/13   vph     Initial version

=============================================================================*/


/*=========================================================================
      Include Files
==========================================================================*/

#include <busywait.h>

#include "DALDeviceId.h"
#include "ClockDriver.h"
#include "HALclk.h"
#include "ClockRPMNPA.h"
#include "rpmserver.h"
#include "QDSSLite.h"
#include "swevent.h"
#include "Clock.h"
#include "PlatformInfo.h"
#include "ClockCommon.h"
#include "ClockRPMBIMC.h"
#include "CoreVerify.h"
#include "icb_rpm.h"
#include "railway.h"
#include "kvp.h"
#include "rpmserver.h"


/*=========================================================================
      Type Definitions
==========================================================================*/

#define CLOCK_RPM_TEST_FLAGS_DEEP_SLEEP_RESTORE_CHECK     (0x1 << 0)

/*
 * RPM clock driver detect options.
 */
typedef enum
{
  /* Do not modify clock reference counts upon config detection. */
  CLK_DETECT_INIT_REF_COUNT_DIS,

  /*
   * Initialize clock group reference counts independently based on their enable
   * states. Do not modify 'bClkGrpEnabled' (intended for resources where
   * clock groups aren't enabled/disabled).
   */
  CLK_DETECT_INIT_REF_COUNT_IND,

  /*
   * If any clock from the group is enabled, enable any OFF clocks and
   * set 'bClkGrpEnabled' to TRUE (intended for resources that gate entire
   * clock groups on/off).
   */
  CLK_DETECT_INIT_REF_COUNT_PULL_UP,

  CLOCK_BSP_ENUM_32BITS(CLK_DETECT_INIT_REF_COUNT)
} ClockDetectInitRefCountType;


static const char szClockNPAUnitEnable[] = "Enable";

/*=========================================================================
      Module Data
==========================================================================*/

static rpm_npa_adapter clk0_adapter;    // Misc clocks: [CXO, QDSS]
static rpm_npa_adapter clk1_adapter;    // Bus clocks: [cnoc_periph, snoc, cnoc, mm/axinoc, mm/ahbnoc, mm/ocmemnoc]
static rpm_npa_adapter clk2_adapter;    // Memory clocks: [bimc] 
static rpm_npa_adapter ipa_adapter;     // IPA
static rpm_npa_adapter ce_adapter;      // CE - Crypto Engine 
static rpm_npa_adapter aggr_adapter;    // Aggregation NOCs clocks
static rpm_npa_adapter pimem_adapter;   // Sys PIMEM NOCs clocks
static rpm_npa_adapter clk_spm_adapter; // SPM - SPM master state
static rpm_npa_adapter ckmm_adapter;    // MMSS NOC AXI clocks

DALSYS_PROPERTY_HANDLE_DECLARE(hClockProperties);

/* Run-time configuration--all clock RPM tests are disabled by default */
static volatile uint32 Clock_RPMTestFlags = 0;

extern npa_resource_definition Clock_NPAResources[];

/*=========================================================================
      Functions
==========================================================================*/
extern void Clock_VoteMatchSpeed( uint32 nDDRFreqKHz );
void Clock_SNOCVoteMatchSpeed( uint32 nSNOCFreqKHz, uint32 nSNOCHSFreqKHz, uint32 *nNewSNOCFreqKHz, uint32 *nNewSNOCHSFreqKHz );
void Clock_MatchCnocPeriph(uint32 nNewFreqHz);


/*===========================================================================

  FUNCTION      Clock_GetClockGroupIds

  DESCRIPTION   Gets clock IDs for a clock resource's clock array.

  PARAMETERS    aszClockNames   [in]     - Clock name array.
                pClockRes       [in/out] - Clock resource.
                nNumClocks      [in]     - Max number of clocks.

  DEPENDENCIES  None.

  RETURN VALUE  DAL_SUCCESS iff successful.

  SIDE EFFECTS  None.

===========================================================================*/
static DALResult Clock_GetClockGroupIds
(
  const char* const   *aszClockNames,
  ClockResourceType   *pClockRes,
  uint32              nNumClocks
)
{
  DALResult   eResult;
  uint32      nIdx;

  /* Fixed Klocwork error by using pass in number of clocks */
  for ( nIdx = 0; nIdx < nNumClocks; nIdx++ )
  {
    eResult = Clock_GetClockId( aszClockNames[nIdx],
                                (ClockIdType *)&pClockRes->apClocks[nIdx] );

    if ( eResult != DAL_SUCCESS )
    {
      return eResult;
    }
  }

  return DAL_SUCCESS;
}


/*===========================================================================

  FUNCTION      Clock_GetClockResId

  DESCRIPTION   Convenience wrapper to get a single clock ID for a clock
                resource's first clock entry.

  PARAMETERS    szClockName     [in]     - Clock name.
                pClockRes       [in/out] - Clock resource.

  DEPENDENCIES  The clock resource should have only one associated clock.
                Use Clock_GetClockGroupIds() otherwise.

  RETURN VALUE  DAL_SUCCESS iff successful.

  SIDE EFFECTS  None.

===========================================================================*/
static inline DALResult Clock_GetClockResId
(
  const char          *szClockName,
  ClockResourceType   *pClockRes
)
{
  return Clock_GetClockId( szClockName,
                           (ClockIdType *)&pClockRes->apClocks[0] );
}


/* =========================================================================
**  Function : Clock_QDSSConfig
** =========================================================================*/
__attribute__((section("clk_cram_reclaim_pool")))
static DALResult Clock_QDSSConfig
(
  QDSSResourceType *pQDSSRes
)
{
  DALResult         eResult;
  ClockResourceType *pClockRes = &pQDSSRes->sClockRes;
  ClockNodeType     **apClocks = pClockRes->apClocks;
  int               nIdx;

  /* Array of clock names for QDSS clocks which are toggled. */
  static const char* aszQdssToggleClkNames[] =
  {
    [CLK_RES_QDSS_CFG_AHB_IDX]         = "gcc_qdss_cfg_ahb_clk",
    [CLK_RES_QDSS_DAP_AHB_IDX]         = "gcc_qdss_dap_ahb_clk",
    [CLK_RES_QDSS_ETR_USB_IDX]         = "gcc_qdss_etr_usb_clk",
    [CLK_RES_QDSS_TRACE_IDX]           = "gcc_qdss_traceclkin_clk",
    [CLK_RES_QDSS_STM_IDX]             = "gcc_qdss_stm_clk",
    [CLK_RES_QDSS_SNOC_STM_AXI_IDX]    = "gcc_sys_noc_qdss_stm_axi_clk",
    [CLK_RES_QDSS_DAP_IDX]             = "gcc_qdss_dap_clk",
    [CLK_RES_QDSS_TCSTR_DIV2_IDX]      = "gcc_qdss_tsctr_div2_clk",
    [CLK_RES_QDSS_TCSTR_DIV3_IDX]      = "gcc_qdss_tsctr_div3_clk",
    [CLK_RES_QDSS_TCSTR_DIV4_IDX]      = "gcc_qdss_tsctr_div4_clk",
    [CLK_RES_QDSS_TCSTR_DIV8_IDX]      = "gcc_qdss_tsctr_div8_clk",
    [CLK_RES_QDSS_TCSTR_DIV16_IDX]     = "gcc_qdss_tsctr_div16_clk",
    [CLK_RES_QDSS_APB2JTAG_IDX]        = "gcc_qdss_apb2jtag_clk",
    [CLK_RES_WCSS_TSCTR_DIV2_IDX]      = "gcc_wcss_tsctr_div2_clk",
    [CLK_RES_MMSS_TRIG_IDX]            = "gcc_mmss_trig_clk",
    [CLK_RES_QDSS_TRIG_IDX]            = "gcc_qdss_trig_clk",
    [CLK_RES_LPASS_TRIG_IDX]           = "gcc_lpass_trig_clk",
    [CLK_RES_HMSS_TRIG_IDX]            = "gcc_hmss_trig_clk",
    [CLK_RES_MSS_TRIG_IDX]             = "gcc_mss_trig_clk",
    [CLK_RES_GPU_TRIG_IDX]             = "gcc_gpu_trig_clk",
    [CLK_RES_TURING_TRIG_IDX]          = "gcc_turing_trig_clk",
    [CLK_RES_APSS_QDSS_TCSTR_DIV2_IDX] = "gcc_apss_qdss_tsctr_div2_clk",
    [CLK_RES_APSS_QDSS_TCSTR_DIV8_IDX] = "gcc_apss_qdss_tsctr_div8_clk"
  };
  
  /* Array of clock names for QDSS clocks which are not toggled. */
  static const char* aszQdssNonToggleClkNames[] =
  {
    [CLK_RES_QDSS_SYS_NOC_AT_IDX]      = "gcc_sys_noc_at_clk",
    [CLK_RES_QDSS_MMSS_NOC_AT_IDX]     = "gcc_mmss_noc_at_clk",
    [CLK_RES_QDSS_CENTER_AT_IDX]       = "gcc_qdss_center_at_clk",
    [CLK_RES_QDSS_NORTH_AT_IDX]        = "gcc_north_at_clk",
    [CLK_RES_QDSS_SOUTH_AT_IDX]        = "gcc_south_at_clk",
    [CLK_RES_QDSS_AGGRE2_AT_IDX]       = "gcc_aggre2_noc_at_clk",
    [CLK_RES_QDSS_BIMC_AT_IDX]         = "gcc_bimc_at_clk",
    [CLK_RES_QDSS_MSS_AT_IDX]          = "gcc_mss_at_clk",
    [CLK_RES_QDSS_HMSS_AT_IDX]         = "gcc_hmss_at_clk",
    [CLK_RES_NORTH_APB_IDX]            = "gcc_north_apb_clk",
    [CLK_RES_WCSS_AT_IDX]              = "gcc_wcss_at_clk",
    [CLK_RES_TURING_AT_IDX]            = "gcc_turing_at_clk",
    [CLK_RES_QDSS_GPU_AT_IDX]          = "gcc_gpu_at_clk",
    [CLK_RES_QDSS_LPASS_AT_IDX]        = "gcc_lpass_at_clk"

  };


  /* Get (toggle-able) QDSS clocks IDs. */
  eResult = Clock_GetClockGroupIds( aszQdssToggleClkNames, 
                                    pClockRes, 
                                    CLK_RES_QDSS_NUM_CLKS );
  if ( eResult != DAL_SUCCESS )
    return eResult;

  pClockRes->bClkGrpEnabled = FALSE;
  pQDSSRes->nQDSSCurrLevel  = CLOCK_QDSS_LEVEL_OFF;

  /* Get clock IDs for remaining QDSS clocks which aren't toggled. */
  for ( nIdx = 0; nIdx < CLK_RES_QDSS_AT_NUM_CLKS; nIdx++ )
  {
    eResult = Clock_GetClockId( aszQdssNonToggleClkNames[nIdx],
                                (ClockIdType *)&pQDSSRes->pQDSSATClkGroup[nIdx] );
    if ( eResult != DAL_SUCCESS )
      return eResult;
  }

  /* Enable all of the QDSS clocks which aren't toggled. */
  for ( nIdx = 0; nIdx < CLK_RES_QDSS_AT_NUM_CLKS; nIdx++ )
  {
    Clock_EnableClock((ClockIdType)pQDSSRes->pQDSSATClkGroup[nIdx] );
  }

  /*
   * QDSS clocks voltage are programmed manually to support
   * 'CLOCK_QDSS_LEVEL_DEBUG' mode where QDSS follows CX railway.
   */
  CLOCK_FLAG_SET( apClocks[CLK_RES_QDSS_TRACE_IDX]->pDomain,
                  DOMAIN_HOLD_VREG_REQUEST);
  CLOCK_FLAG_SET( pQDSSRes->pQDSSATClkGroup[CLK_RES_QDSS_SYS_NOC_AT_IDX]->pDomain, 
                  DOMAIN_HOLD_VREG_REQUEST);
  CLOCK_FLAG_SET( pQDSSRes->pQDSSATClkGroup[CLK_RES_QDSS_BIMC_AT_IDX]->pDomain, 
                  DOMAIN_HOLD_VREG_REQUEST);
  CLOCK_FLAG_SET( pQDSSRes->pQDSSATClkGroup[CLK_RES_QDSS_LPASS_AT_IDX]->pDomain, 
                  DOMAIN_HOLD_VREG_REQUEST);
  CLOCK_FLAG_SET( apClocks[CLK_RES_QDSS_TCSTR_DIV2_IDX]->pDomain, 
                  DOMAIN_HOLD_VREG_REQUEST);
  CLOCK_FLAG_SET( apClocks[CLK_RES_QDSS_STM_IDX]->pDomain, 
                  DOMAIN_HOLD_VREG_REQUEST);
  CLOCK_FLAG_SET( apClocks[CLK_RES_QDSS_TRIG_IDX]->pDomain, 
                  DOMAIN_HOLD_VREG_REQUEST);

  return DAL_SUCCESS;
}


/* =========================================================================
**  Function : Clock_IsQDSSOn
** =========================================================================*/
/**
  This function determines if QDSS clocks are ON
  
  @param 
      None
  
  @return
      TRUE if QDSS clocks are ON, FALSE otherwise
*/
boolean Clock_IsQDSSOn(void)
{
  boolean       bClockOn;
  ClockNodeType **apClocks = Clock_GetTargCtxt()->QDSSResource.sClockRes.apClocks;

  Clock_IsClockOn( (ClockIdType)apClocks[CLK_RES_QDSS_CFG_AHB_IDX], &bClockOn );

  /* Add to check another QDSS clock (ETR USB), since QDSS_CFG_AHB may be enable by SDI */
  if ( bClockOn )
  {
    Clock_IsClockOn( (ClockIdType)apClocks[CLK_RES_QDSS_ETR_USB_IDX], &bClockOn );
  }

  return bClockOn;
}


/* =========================================================================
**  Function : Clock_DetectClockEnable
** =========================================================================*/
/**
  Initializes reference counts to match with initial enable states. Also
  optionally enables each clock if at least one is enabled.

  @param 
    pClockResource    [in] -- Clock resource.
    boolean           [in] -- TRUE => If at least one clock is ON, enable all
                              clocks and set 'bClkGrpEnabled' to TRUE.
                              FALSE => Just align ref counts independentently.
  @return
    None (aborts upon failure).
  
  @dependencies
    None.
*/
__attribute__((section("clk_cram_reclaim_pool")))
static void Clock_DetectClockEnable
(
  ClockResourceType       *pClockResource,
  boolean                 bPullUp
)
{
  uint32          nIdx;
  boolean         bEnabled;
  boolean         bEnabledClockFound  = FALSE;
  ClockNodeType   **apClocks          = pClockResource->apClocks;

  /* First set ref counts to one for any clock that is enabled. */
  for ( nIdx = 0; nIdx < pClockResource->nNumClocks; nIdx++ )
  {
    CORE_DAL_VERIFY( Clock_IsClockEnabled( (ClockIdType)apClocks[nIdx], &bEnabled ) );

    if ( bEnabled )
    {
      bEnabledClockFound = TRUE;

      /* Align the ON clock's reference count. */
      Clock_EnableClockEx( (ClockIdType)apClocks[nIdx], FALSE );
    }
  }

  /*
   * Enable each clock if pull-up is requested and at least one clock
   * is enabled.
   */
  if ( bPullUp && bEnabledClockFound )
  {
    /* Mark the entire clock group as enabled. */
    pClockResource->bClkGrpEnabled = TRUE;

    for ( nIdx = 0; nIdx < pClockResource->nNumClocks; nIdx++ )
    {
      if ( apClocks[nIdx]->nReferenceCount == 0 )
      {
        /* Enable the OFF clock. */
        CORE_DAL_VERIFY( Clock_EnableClock( (ClockIdType)apClocks[nIdx] ) );
      }
    }
  }
}


/* =========================================================================
**  Function : Clock_DetectClockConfig
** =========================================================================*/
/**
  Detects the min, max, and current config level for a clock resource. Also
  updates reference counts optionally.

  @param 
    pClockResource    [in] -- Clock resource.
    eRefCountInitMode [in] -- see 'ClockDetectInitRefCountType'.
  
  @return
    None (aborts upon failure).
  
  @dependencies
    None.
*/
__attribute__((section("clk_cram_reclaim_pool")))
static void Clock_DetectClockConfig
(
  ClockResourceType             *pClockResource,
  ClockDetectInitRefCountType   eRefCountInitMode
)
{
  uint32  nCfg, nMinSupCfg, nMaxSupCfg, nDiv2x;
  HAL_clk_ClockMuxConfigType    MuxCfg;
  HAL_clk_PLLConfigType         PLLConfig;

  ClockDomainNodeType *pDomain  = CLK_DELEGATE(pClockResource)->pDomain;
  ClockMuxConfigType  *pCfg     = pDomain->pBSPConfig;

  /*-----------------------------------------------------------------------*/
  /* Get the current clock configuration.                                  */
  /*-----------------------------------------------------------------------*/

  HAL_clk_DetectClockMuxConfig(pDomain->HALHandle, &MuxCfg);
 
  /*
   * Find out the PLL configuration.
   */
  HAL_clk_DetectPLLConfig(MuxCfg.eSource, &PLLConfig);
  
  /*
   * If we got back nDiv2x less than 2 (Bypass or Div1), set to 2 since 
   *   MuxConfig will substract 1 when it used HALF_DIVIDER(mux)
   */
  if (MuxCfg.nDiv2x < 2)
  {
    MuxCfg.nDiv2x = 2;
  }

  /* Loop thru the end of BSP data for finding min/max supported level */
  nCfg = 0;
  nMaxSupCfg = 0;
  nMinSupCfg = CLK_MAX_LEVEL;
  pClockResource->nCurLevel = CLK_MAX_LEVEL;
  while ( pCfg[nCfg].nFreqHz != 0 )
  {
    /* Check supported BSP levels only. */
    if ( Clock_IsBSPSupported(&pCfg[nCfg]) )
    {
      nMaxSupCfg = nCfg;
      if(nMinSupCfg == CLK_MAX_LEVEL)
      {
        nMinSupCfg = nCfg;
      }

      /* In the case of BIMC, it may need to use upper byte [15:8] for DDRCC mode and DDRCC index */
      /* Mask out the lower byte [7:0] for Div-2 */
      nDiv2x = pCfg[nCfg].HALConfig.nDiv2x ;
      if (nDiv2x < 2)
      {
        nDiv2x = 2;
      }
  
      /* Check if this BSP level is the current configuration. */
      if ( (pClockResource->nCurLevel == CLK_MAX_LEVEL) &&
           (MuxCfg.eSource == pCfg[nCfg].HALConfig.eSource) &&
           (MuxCfg.nDiv2x == nDiv2x) )
      {
        if(pCfg[nCfg].pSourceConfig != NULL)
        {
          if(PLLConfig.nL == pCfg[nCfg].pSourceConfig->HALConfig.nL)
          {
            pCfg[nCfg].HALConfig.eSource = MuxCfg.eSource;
            pClockResource->nCurLevel = nCfg;
          }
        }
        else if(MuxCfg.eSource == pCfg[nCfg].HALConfig.eSource)
        {
          pClockResource->nCurLevel = nCfg;
        }
      }
    }

    nCfg++;
  }

  /* Require at least one supported performance level. */
  CORE_VERIFY( nCfg > 0 );

  /* Require that the current level was successfully detected. */
  CORE_VERIFY( pClockResource->nCurLevel != CLK_MAX_LEVEL );

  /* Move min/max within supported level range. */
  if ( pClockResource->nMinLevel < nMinSupCfg )
  {
    pClockResource->nMinLevel = nMinSupCfg;
  }
  else if ( pClockResource->nMinLevel > nMaxSupCfg )
  {
    pClockResource->nMinLevel = nMaxSupCfg;
  }
  if ( pClockResource->nMaxLevel < nMinSupCfg )
  {
    pClockResource->nMaxLevel = nMinSupCfg;

  }
  else if ( pClockResource->nMaxLevel > nMaxSupCfg )
  {
    pClockResource->nMaxLevel = nMaxSupCfg;
  }
  CORE_VERIFY( pClockResource->nMinLevel <= pClockResource->nMaxLevel );

  /* Set active mux config and boot up clock frequency */
  pDomain->pActiveMuxConfig = &pDomain->pBSPConfig[pClockResource->nCurLevel];

  /* Increment appropriate clock reference counts if requested. */
  if ( eRefCountInitMode != CLK_DETECT_INIT_REF_COUNT_DIS )
  {
    Clock_DetectClockEnable( pClockResource,
        (eRefCountInitMode == CLK_DETECT_INIT_REF_COUNT_PULL_UP) );
  }
}


/* =========================================================================
**  Function : Clock_ConfigBIMCClocks
** =========================================================================*/
/**
  This API is used to config BIMC clocks ID and BIMC power domain
   
  @param 
    pTargCtxt [in] - Clock driver target context.
  
  @return
    None (aborts upon failure).
  
  @dependencies
    None.
*/
__attribute__((section("clk_cram_reclaim_pool")))
static void Clock_ConfigBIMCClocks( Clock_TargCtxtType *pTargCtxt )
{
  void HAL_clk_SaveBIMCPorts( const HAL_clk_ClockMuxConfigType *pmConfig );
  ClockVRegLevelType  eVregLvl;
  ClockNodeType       *pClock;
  ClockDrvCtxt        *pDrvCtxt = Clock_GetDrvCtxt();
  uint32 id;
  HAL_clk_SourceType   nCurrPLL[MAX_BIMC_DDR_ASYNC_CLK];
  ClockMuxConfigType   *pConfig;

  BIMCResourceType *pBIMCRes = &pTargCtxt->BIMCResource;
  
  Clock_GetClockId( "gcc_bimc_ddr_cpll0_clk",
                           (ClockIdType *) &CLK_DELEGATE(&pBIMCRes->sClockRes) );

  pClock = CLK_DELEGATE(&pBIMCRes->sClockRes);

  /* Copy BIMC Plan from SMEM and detect BIMC Mux Configs */
  CORE_VERIFY( Clock_BIMCCopyPlanFromShared( pTargCtxt ) == TRUE );

  /* Get the BIMC power ID. */
  CORE_DAL_VERIFY( Clock_GetPowerDomainId( "VDD_BIMC", &pBIMCRes->nBIMCPowerID) );

  /* Get the BIMC power ID. */
  CORE_DAL_VERIFY( Clock_GetPowerDomainId( "VDD_DDR_DIM_WRAPPER", &pBIMCRes->nDDRPHYPowerID) );


  /* Enable Active GPLL Source*/
//  CORE_DAL_VERIFY( Clock_EnableSource(pDrvCtxt, pClock->pDomain->pSource) );

  pConfig = pBIMCRes->sClockRes.apClocks[0]->pDomain->pActiveMuxConfig;
  /*Enable the ASYNC RCG PLLs and  put the ref count*/
  
  nCurrPLL[0] = HAL_clk_getDDRSources(&pConfig->HALConfig);
  nCurrPLL[1] = HAL_clk_getBIMCSources(&pConfig->HALConfig);
  nCurrPLL[2] = HAL_clk_getHMSSSources(&pConfig->HALConfig);
  nCurrPLL[3] = HAL_clk_getGFXSources(&pConfig->HALConfig);
  nCurrPLL[4] = HAL_clk_getMPSSSources(&pConfig->HALConfig);
  nCurrPLL[5] = HAL_clk_get_CDSPSources(&pConfig->HALConfig);
  id = 0;
  while(id < MAX_BIMC_DDR_ASYNC_CLK)
  {
    pBIMCRes->sAsyncClockState[id].nCurrPLL = nCurrPLL[id];
    Clock_EnableSource(pDrvCtxt, &pDrvCtxt->aSources[pDrvCtxt->anSourceIndex[nCurrPLL[id]]]);
    id++;
  }

  CORE_DAL_VERIFY( Clock_EnablePowerDomain( pTargCtxt->BIMCResource.nBIMCPowerID, TRUE )); 
  CORE_DAL_VERIFY( Clock_EnablePowerDomain( pTargCtxt->BIMCResource.nDDRPHYPowerID, TRUE )); 
  
  eVregLvl = (ClockVRegLevelType)HAL_CLK_BIMC_N2D_VDDA_EBI_VOTE(pClock->pDomain->pActiveMuxConfig->HALConfig.n2D);
  Clock_InitEBIVoltage( eVregLvl,"vddmx" );
  pTargCtxt->BIMCResource.nVDDA = eVregLvl;
  
  pTargCtxt->BIMCResource.bBIMCModemEnabled = FALSE;
  HAL_clk_SaveBIMCPorts( &pClock->pDomain->pActiveMuxConfig->HALConfig );
}

/* =========================================================================
**  Function : Clock_ConfigMMSSAXIClocks
** =========================================================================*/
/**
  This API is used to config MMSS AXI clocks ID and MMSS BIMC power domain
   
  @param 
    pTargCtxt [in] - Clock driver target context.
  
  @return
    None (aborts upon failure).
  
  @dependencies
    None.
*/ 
__attribute__((section("clk_cram_reclaim_pool")))
static void Clock_ConfigMMSSAXIClocks( Clock_TargCtxtType *pTargCtxt )
{
  static const char* aszMMSSClkNames[] =
  {
    [CLK_RES_MMSS_MNOC_AXI_IDX]        = "mmss_mnoc_axi_clk",
  };
 
  MMXIResourceType *pMMXIRes = &pTargCtxt->MMAXIClockResource; 

  /* Get MMSS clocks IDs. */
  CORE_DAL_VERIFY( Clock_GetClockGroupIds( aszMMSSClkNames, 
                                    &pMMXIRes->sClockRes,
                                    CLK_RES_MMSS_NUM_CLKS ) );

  CORE_DAL_VERIFY( Clock_IsClockOn( (ClockIdType)CLK_DELEGATE(&pMMXIRes->sClockRes), &pMMXIRes->bEnabled) );

  if ( pMMXIRes->bEnabled )
  {
    Clock_EnableClockGroup( &pMMXIRes->sClockRes, TRUE );
  }

  /*-----------------------------------------------------------------------*/
  /* Get the current MMSS AXI configuration.                               */
  /*-----------------------------------------------------------------------*/
  Clock_DetectClockConfig(&pTargCtxt->MMAXIClockResource.sClockRes,
                          CLK_DETECT_INIT_REF_COUNT_IND);

 }

/* =========================================================================
**  Function : Clock_AggreSetupSNOCNode
** =========================================================================*/
/**
  Call back function for SNOC node.

  This function is invoked when the "\clk\snoc" NPA node is setup.

  @param
   npa_callback parameters

  @return
    None.

  @dependencies
    None.
*/
static void Clock_AggreSetupSNOCNode
(
  Clock_TargCtxtType *pTargCtxt,
  unsigned int unused2,
  const char **resources,
  unsigned int num_resources
)
{

  pTargCtxt->Aggre2Resource.SNOCHandle  = npa_create_sync_client(
    "/clk/snoc", "ClockRPM-Aggre2Noc", NPA_CLIENT_REQUIRED );

  CORE_VERIFY_PTR(pTargCtxt->Aggre2Resource.SNOCHandle);

  npa_issue_required_request(pTargCtxt->Aggre2Resource.SNOCHandle, Clock_NPAResources[CLK_NPA_RES_AGGRE2_IDX].handle->request_state);
}


/* =========================================================================
**  Function : Clock_IPASetupBIMCNode
** =========================================================================*/
/**
  Call back function for BIMC node.

  This function is invoked when the "\clk\bimc" NPA node is setup.

  @param
   npa_callback parameters

  @return
    None.

  @dependencies
    None.
*/
static void Clock_IPASetupBIMCNode
(
  Clock_TargCtxtType *pTargCtxt,
  unsigned int unused2,
  const char **resources,
  unsigned int num_resources
)
{
  pTargCtxt->IPAResource.BIMCHandle = npa_create_sync_client(
    "/clk/bimc", "ClockRPM-IPA", NPA_CLIENT_REQUIRED );

  CORE_VERIFY_PTR(pTargCtxt->IPAResource.BIMCHandle);

  if ( pTargCtxt->IPAResource.bEnabled )
  {
    /* Vote for bimc if the IPA clocks are ON */
    npa_issue_required_request(pTargCtxt->IPAResource.BIMCHandle, 1); 
  }
}


/* =========================================================================
**  Function : Clock_IPASetupAggre2Node
** =========================================================================*/
/**
  Call back function for Aggre2 node.

  This function is invoked when the "\clk\bimc" NPA node is setup.

  @param
   npa_callback parameters

  @return
    None.

  @dependencies
    None.
*/
static void Clock_IPASetupAggre2Node
(
  Clock_TargCtxtType *pTargCtxt,
  unsigned int unused2,
  const char **resources,
  unsigned int num_resources
)
{
  pTargCtxt->IPAResource.Aggre2Handle = npa_create_sync_client(
    "/clk/agr2", "ClockRPM-IPA", NPA_CLIENT_REQUIRED );

  CORE_VERIFY_PTR(pTargCtxt->IPAResource.Aggre2Handle);

  if ( pTargCtxt->IPAResource.bEnabled )
  {
    /* Vote for bimc if the IPA clocks are ON */
    npa_issue_required_request(pTargCtxt->IPAResource.Aggre2Handle, 1); 
  }
}


/* =========================================================================
**  Function : Clock_SetupSysPIMEMNode
** =========================================================================*/
/**
  Call back function for register PIMEM clock as the same as SysNOC

  This function is invoked when the "\clk\pmem" NPA node is setup.

  @param
   npa_callback parameters

  @return
    None.

  @dependencies
    None.
*/
#if 0
static void Clock_SetupSysPIMEMNode
(
  Clock_TargCtxtType *pTargCtxt,
  unsigned int unused2,
  const char **resources,
  unsigned int num_resources
)
{
  ClockNodeType *pSnocClk = CLK_DELEGATE(&pTargCtxt->SNOCClockResource);
  uint32        nFreqKHz  = (pSnocClk->pDomain->pActiveMuxConfig->nFreqHz / 1000);

  pTargCtxt->PIMEMHandle = npa_create_sync_client(
    "/clk/pmem", "ClockRPM-SNOC", NPA_CLIENT_REQUIRED );

  CORE_VERIFY_PTR(pTargCtxt->PIMEMHandle);

  /* Vote for PIMEM as sync with SysNoc */
  npa_issue_required_request( pTargCtxt->PIMEMHandle, nFreqKHz); 
}

#endif
/* =========================================================================
**  Function : Clock_VSenseConfig
** =========================================================================*/
/**
  Configures voltage sensor clocks.

  @param
    pTargCtxt [in] - RPM clock driver target context.

  @return
    None (aborts upon failure).

  @dependencies
    None.
*/
__attribute__((section("clk_cram_reclaim_pool")))
void Clock_VSenseConfig( Clock_TargCtxtType *pTargCtxt )
{
  static const char* aszVsenseClkNames[] =
  {
    [CLK_RES_VSENSE_CTRL_IDX]   = "gcc_vs_ctrl_clk",
    [CLK_RES_VSENSE_VDDA_IDX]   = "gcc_vdda_vs_clk",
    [CLK_RES_VSENSE_VDDCX_IDX]  = "gcc_vddcx_vs_clk",
    [CLK_RES_VSENSE_VDDMX_IDX]  = "gcc_vddmx_vs_clk",
    [CLK_RES_VSENSE_MSS_IDX]    = "gcc_mss_vs_clk"
  };

  uint32              nIdx;
  ClockResourceType   *pClockRes = &pTargCtxt->VSenseClockResource;
  ClockNodeType       **apClocks = pClockRes->apClocks;

  /* Get the clock IDs. */
  CORE_DAL_VERIFY( Clock_GetClockGroupIds( aszVsenseClkNames, 
                                           pClockRes,
                                           CLK_RES_VSENSE_NUM_CLKS) );

  /*
   * VSense clocks scale with CX voltage changes so they should not place
   * their own voltage requests.
   */
  for ( nIdx = 0; nIdx < pClockRes->nNumClocks; nIdx++ )
  {
    CLOCK_FLAG_SET( apClocks[nIdx]->pDomain, DOMAIN_HOLD_VREG_REQUEST);
  }
}


/* =========================================================================
**  Function : Clock_InitIPA
** =========================================================================*/
/**
  This function is for IPA driver to register its callback function to BIMC
  and Aggre2 NOC.  When IPA is enable, it needs to vote for both BIMC and Aggre2
  NOC also enable
   
  @param 
    None
  
  @return
    None
  
  @dependencies
    None.
*/
__attribute__((section("clk_cram_reclaim_pool")))
static void Clock_InitIPA( Clock_TargCtxtType *pTargCtxt )
{
  ClockNodeType     **ppClock;
  ClockNodeType     *pClock;
  IPAResourceType   *pIpaRes    = &pTargCtxt->IPAResource;
  ClockResourceType *pIpaClkRes = &pIpaRes->sClockRes;

  /* IPA only has one clock */
  ppClock = &pIpaClkRes->apClocks[0];

  CORE_DAL_VERIFY( Clock_GetClockId("gcc_ipa_clk", (ClockIdType *)ppClock) );
  pClock = *ppClock;

  /* Get the current IPA Configuration.                                    */
  Clock_DetectClockConfig(&pTargCtxt->IPAResource.sClockRes, CLK_DETECT_INIT_REF_COUNT_DIS);

  CORE_DAL_VERIFY( Clock_IsClockOn( (ClockIdType)*ppClock, &pIpaRes->bEnabled) );

  CLOCK_FLAG_CLEAR(pClock->pDomain, DOMAIN_SUPPRESSIBLE);
  if ( pIpaRes->bEnabled )
  {
    Clock_EnableClock( (ClockIdType)pClock);
    //CORE_DAL_VERIFY( Clock_GetPowerDomainId( "VDD_IPA", &pIpaRes->nIPAPowerID) );
  }
    
  /* IPA has dependency on BIMC.  It needs to setup a callback for register its node to keep BIMC on when IPA is enable */
  npa_resource_available_cb( "/clk/bimc", (npa_callback)Clock_IPASetupBIMCNode, pTargCtxt );
    
  /* IPA has dependency on Aggre2.  It needs to setup a callback for register its node to keep Aggre2 on when IPA is enable */
  npa_resource_available_cb( "/clk/agr2", (npa_callback)Clock_IPASetupAggre2Node, pTargCtxt );
}


/* =========================================================================
**  Function : Clock_ConfigAggreClocks
** =========================================================================*/
/**
  This API is used to config check the Aggregate NOCs clocks to match with
  SBL configure.
   
  @param 
    None
  
  @return
    None (aborts upon failure).
  
  @dependencies
    None.
*/
__attribute__((section("clk_cram_reclaim_pool")))
static void Clock_ConfigAggreClocks( Clock_TargCtxtType *pTargCtxt )
{
  /* Extern needed for array init. */
  extern Clock_TargCtxtType Clock_Resources;

  /* Aggre clock names. */
  static const char* aszAggre2ClockNames[] =
  {
    [CLK_RES_AGGRE2_SNOC_IDX]       = "gcc_aggre2_snoc_axi_clk",
    [CLK_RES_AGGRE2_SNOC_SOUTH_IDX]  = "gcc_aggre2_snoc_south_axi_clk",
    [CLK_RES_AGGRE2_SNOC_NORTH_IDX] = "gcc_aggre2_snoc_north_axi_clk",
    [CLK_RES_AGGRE2_CNOC_IDX]       = "gcc_aggre2_cnoc_ahb_clk",
    [CLK_RES_AGGRE2_SMMU_AXI_IDX]   = "gcc_smmu_aggre2_axi_clk",
    [CLK_RES_AGGRE2_SMMU_AHB_IDX]   = "gcc_smmu_aggre2_ahb_clk"
  };

  /* Aggre config table. */
  static const struct
  {
    AggreResourceType       *pAggreRes;
    const char**            aszClockNames;
    const char*             szPowerDomainName;
  } asAggreClockConigTable[] =
  {
    {
      &Clock_Resources.Aggre2Resource,
      aszAggre2ClockNames,
      "VDD_AGGRE2_NOC"
    }
  };

  DALResult           eResult;
  uint32              nIdx;
  AggreResourceType   *pAggreRes;
  ClockResourceType   *pClockRes;

  /* Configure each Aggre resource. */
  for ( nIdx = 0; nIdx < CLK_NUM_ELEM(asAggreClockConigTable); nIdx++ )
  {
    pAggreRes = asAggreClockConigTable[nIdx].pAggreRes;
    pClockRes = &pAggreRes->sClockRes;
    
    /* Get Aggre clock IDs. */
    eResult = Clock_GetClockGroupIds(
                  asAggreClockConigTable[nIdx].aszClockNames,
                  pClockRes,
                  CLK_RES_AGGRE2_NUM_CLKS );
    CORE_DAL_VERIFY( eResult );

    /* Get Aggre power ID. */
    eResult = Clock_GetPowerDomainId(
                  asAggreClockConigTable[nIdx].szPowerDomainName,
                  &pAggreRes->nAggrePowerID );
    CORE_DAL_VERIFY( eResult );

    Clock_DetectClockConfig(pClockRes, CLK_DETECT_INIT_REF_COUNT_PULL_UP);

    if ( pClockRes->bClkGrpEnabled )
    {
      CORE_DAL_VERIFY( Clock_EnablePowerDomain( pAggreRes->nAggrePowerID, TRUE ) );
    }

    /* IPA has dependency on BIMC.  It needs to setup a callback for register its node to keep BIMC on when IPA is enable */
    npa_resource_available_cb( "/clk/snoc", (npa_callback)Clock_AggreSetupSNOCNode, pTargCtxt );
 
  }
} /* END Clock_ConfigAggreClocks */


/* =========================================================================
**  Function : Clock_SetSPMStates
** =========================================================================*/
/**
  Sets proxy votes for APSS on the "/clk/spm" NPA node such that APSS
  places a non-zero vote when it enters active state and zero vote when it
  enters sleep state.

  @param 
    kvp [in] - KVP object to be used for "/clk/spm" proxy votes.

  @return
    None.

  @dependencies
    None.
*/
void Clock_SetSPMStates( kvp_t *kvp )
{
  uint32 req;

  /* Place a proxy active set vote of 1 for Apps. */
  kvp_clear(kvp);
  req = 1;
  kvp_put(kvp, *(unsigned int *)szClockNPAUnitEnable, sizeof(req), &req);
  rpm_send_init_proxy_vote(RPM_CLOCK_SPM_REQ, 0, /* Apps is master 0*/ 0, kvp);

  /* Place a proxy sleep set vote of 0 for Apps. */
  kvp_clear(kvp);
  req = 0;
  kvp_put(kvp, *(unsigned int *)szClockNPAUnitEnable, sizeof(req), &req);
  rpm_send_init_sleep_proxy_vote(RPM_CLOCK_SPM_REQ, 0, /* Apps is master 0*/ 0, kvp);

  /* Place a proxy active set vote of 1 for Modem. */
  kvp_clear(kvp);
  req = 1;
  kvp_put(kvp, *(unsigned int *)szClockNPAUnitEnable, sizeof(req), &req);
  rpm_send_init_proxy_vote(RPM_CLOCK_SPM_REQ, 0, /* Modem is master 1*/ 1, kvp);

  /* Place a proxy sleep set vote of 0 for Modem. */
  kvp_clear(kvp);
  req = 0;
  kvp_put(kvp, *(unsigned int *)szClockNPAUnitEnable, sizeof(req), &req);
  rpm_send_init_sleep_proxy_vote(RPM_CLOCK_SPM_REQ, 0, /* Modem is master 1*/ 1, kvp);
}


/* =========================================================================
**  Function : Clock_InitImage
** =========================================================================*/
/*
  See DalClock.h
*/

__attribute__((section("clk_cram_reclaim_pool")))
DALResult Clock_InitImage
(
  void
)
{
 static const char* aszCnocPeriphClockNames[] =
  {
    [CLK_RES_CNOC_PERIPH_NORTH_AHB_IDX]    = "gcc_cnoc_periph_north_ahb_clk",
    [CLK_RES_CNOC_PERIPH_SOUTH_AHB_IDX]    = "gcc_cnoc_periph_south_ahb_clk",
    [CLK_RES_CNOC_PERIPH_AHB_IDX]          = "gcc_cnoc_periph_ahb_clk",
    [CLK_RES_CNOC_PERIPH_AGGRE2_AHB_IDX]   = "gcc_aggre2_cnoc_periph_ahb_clk",
    [CLK_RES_CNOC_NORTH_PERIPH_AGGRE2_AHB_IDX]   = "gcc_aggre2_cnoc_north_periph_ahb_clk",
    [CLK_RES_CNOC_SOUTH_PERIPH_AGGRE2_AHB_IDX]   = "gcc_aggre2_cnoc_south_periph_ahb_clk",
  };

  static const char* aszCe1ClockNames[] =
  {
    [CLK_RES_CE_CLK_IDX]          = "gcc_ce1_clk",
    [CLK_RES_CE_CLK_AXI_IDX]      = "gcc_ce1_axi_clk",
    [CLK_RES_CE_CLK_AHB_IDX]      = "gcc_ce1_ahb_clk"
  };

  railway_settings        sCxRailSettings;
  ClockDomainNodeType     *pDomain;
  ClockDrvCtxt            *pDrvCtxt  = Clock_GetDrvCtxt();
  Clock_TargCtxtType      *pTargCtxt = Clock_GetTargCtxt();


  SWEVENT(CLOCK_EVENT_INIT);

  /* Default DCVS is disable. */
  pDrvCtxt->bDCVSEnabled = FALSE;

  /* Get the CX railway level. */
  railway_get_current_settings(pTargCtxt->nCXRailID, &sCxRailSettings);
  pTargCtxt->nCXVReg = (ClockVRegLevelType)sCxRailSettings.mode;

  /* Suspend voltage scaling during init */
  Clock_VoltageRequestSuspend( pDrvCtxt, CLOCK_VOLT_REQ_SUSPENDED_INIT, FALSE );

  //  Clock_InitSource(pDrvCtxt, HAL_CLK_SOURCE_MMPLL0);
  //  Clock_InitSource(pDrvCtxt, HAL_CLK_SOURCE_MMPLL1);

  /*-----------------------------------------------------------------------*/
  /* Get RPM clock ID and enable for reference count                       */
  /*-----------------------------------------------------------------------*/

  CORE_DAL_VERIFY( Clock_GetClockResId( "gcc_rpm_proc_hclk", 
                                        &pTargCtxt->CPUClockResource ) );
  Clock_DetectClockConfig(&pTargCtxt->CPUClockResource,
                          CLK_DETECT_INIT_REF_COUNT_PULL_UP);

  /*-----------------------------------------------------------------------*/
  /* Marking RPM CPU clock as non-voltage change before enable, so clock   */
  /* driver should not put in the voltage vote during clock enable         */
  /*-----------------------------------------------------------------------*/
  pDomain = CLK_DELEGATE(&pTargCtxt->CPUClockResource)->pDomain;
  CLOCK_FLAG_SET( pDomain, DOMAIN_HOLD_VREG_REQUEST );

  /* Cannot auto-detect RPM CPU clock enable--force ref count alignment. */
  Clock_EnableClockGroup(&pTargCtxt->CPUClockResource, FALSE);

  /*-----------------------------------------------------------------------*/
  /* Get Sytem NOC clock ID and enable for reference count                 */
  /*-----------------------------------------------------------------------*/
  CORE_DAL_VERIFY( Clock_GetClockResId( "gcc_sys_noc_axi_clk", 
                                        &pTargCtxt->SNOCClockResource ) );
  Clock_DetectClockConfig(&pTargCtxt->SNOCClockResource,
                          CLK_DETECT_INIT_REF_COUNT_PULL_UP);

  /*-----------------------------------------------------------------------*/
  /* Get Sytem NOC HS clock ID and enable for reference count              */
  /*-----------------------------------------------------------------------*/
  CORE_DAL_VERIFY( Clock_GetClockResId( "gcc_sys_noc_hs_axi_clk", 
                                        &pTargCtxt->SNOCHSClockResource ) );
  Clock_DetectClockConfig(&pTargCtxt->SNOCHSClockResource,
                          CLK_DETECT_INIT_REF_COUNT_PULL_UP);

  /*-----------------------------------------------------------------------*/
  /* Get Sytem NOC PIMEM clock ID and enable for reference count           */
  /*-----------------------------------------------------------------------*/
  CORE_DAL_VERIFY( Clock_GetClockResId( "gcc_sys_noc_pimem_axi_clk", 
                                        &pTargCtxt->SNOCPIMEMClockResource) );
  Clock_DetectClockConfig(&pTargCtxt->SNOCPIMEMClockResource,
                          CLK_DETECT_INIT_REF_COUNT_PULL_UP);

  /* Keep PIMEM in sync with SysNOC.  Register a callback for voting PIMEM when PIMEM NPA node is ready */
 // npa_resources_available_cb(sizeof(npa_deps)/sizeof(npa_deps[0]),npa_deps, (npa_callback)Clock_SetupSysPIMEMNode, pTargCtxt );
    
  /*-----------------------------------------------------------------------*/
  /* Get Config NOC clock ID                                               */
  /*-----------------------------------------------------------------------*/
  CORE_DAL_VERIFY( Clock_GetClockResId( "gcc_cfg_noc_ahb_clk", 
                                        &pTargCtxt->CNOCClockResource ) );
  Clock_DetectClockConfig(&pTargCtxt->CNOCClockResource,
                          CLK_DETECT_INIT_REF_COUNT_PULL_UP);

  /*-----------------------------------------------------------------------*/
  /* Get CNOC Periph clock ID                                              */
  /*-----------------------------------------------------------------------*/
  CORE_DAL_VERIFY( Clock_GetClockGroupIds( aszCnocPeriphClockNames, 
                                           &pTargCtxt->CNOCPeriphClockResource,
                                           CLK_RES_CNOC_PERIPH_NUM_CLKS) );
  Clock_DetectClockConfig(&pTargCtxt->CNOCPeriphClockResource,
                          CLK_DETECT_INIT_REF_COUNT_PULL_UP);

  /*-----------------------------------------------------------------------*/
  /* Get CE1 (Crypto Engine 1) clock ID                                    */
  /*-----------------------------------------------------------------------*/
  CORE_DAL_VERIFY( Clock_GetClockGroupIds( aszCe1ClockNames, 
                                           &pTargCtxt->CE1ClockResource,
                                           CLK_RES_CE_NUM_CLKS) );
  
  // Mark this clock as insuppressible.
  pDomain = CLK_DELEGATE(&pTargCtxt->CE1ClockResource)->pDomain;
  CLOCK_FLAG_CLEAR( pDomain, DOMAIN_SUPPRESSIBLE );

  Clock_DetectClockConfig(&pTargCtxt->CE1ClockResource,
                          CLK_DETECT_INIT_REF_COUNT_PULL_UP);

  /*-----------------------------------------------------------------------*/
  /* Get HMSS AHB clock                                                    */
  /*-----------------------------------------------------------------------*/
  CORE_DAL_VERIFY( Clock_GetClockResId( "gcc_hmss_ahb_clk", 
                                        &pTargCtxt->HMSSAHBClockResource ) );
  Clock_DetectClockConfig(&pTargCtxt->HMSSAHBClockResource,
                          CLK_DETECT_INIT_REF_COUNT_IND);

  /*-----------------------------------------------------------------------*/
  /* Get BIMC clock ID                                                     */
  /*-----------------------------------------------------------------------*/
  Clock_ConfigBIMCClocks( pTargCtxt ); 

  /*-----------------------------------------------------------------------*/
  /* Setup Voltage sensor resource                                         */
  /*-----------------------------------------------------------------------*/
  Clock_VSenseConfig( pTargCtxt );

  /*-----------------------------------------------------------------------*/
  /* Get MMSS AXI clock ID                                                 */
  /*-----------------------------------------------------------------------*/
  Clock_ConfigMMSSAXIClocks( pTargCtxt );

  /*-----------------------------------------------------------------------*/
  /* Configure Aggre NOCs clocks                                           */
  /*-----------------------------------------------------------------------*/
  Clock_ConfigAggreClocks( pTargCtxt );

  /*-----------------------------------------------------------------------*/
  /* Get IPA clock ID                                                      */
  /*-----------------------------------------------------------------------*/
  Clock_InitIPA( pTargCtxt );

  /*-----------------------------------------------------------------------*/
  /* Setup QDSS resource                                                   */
  /*-----------------------------------------------------------------------*/
  CORE_DAL_VERIFY( Clock_QDSSConfig(&pTargCtxt->QDSSResource) );

  /*-----------------------------------------------------------------------*/
  /* Initialize NPA clock data                                             */
  /*-----------------------------------------------------------------------*/
  CORE_DAL_VERIFY( Clock_InitNPA() );

  /*-----------------------------------------------------------------------*/
  /* Expose the nodes to the outside world via rpmserver                   */
  /*-----------------------------------------------------------------------*/
  clk0_adapter = rpm_create_npa_adapter(RPM_CLOCK_0_REQ, 3); // Misc clocks: [CXO, QDSS, DCVS]
  rpm_associate_npa_resource(clk0_adapter, 0, aszClockNPAResNames[CLK_NPA_RES_CXO_IDX]);
  rpm_associate_npa_resource(clk0_adapter, 1, aszClockNPAResNames[CLK_NPA_RES_QDSS_IDX]);
  rpm_associate_npa_resource(clk0_adapter, 2, aszClockNPAResNames[CLK_NPA_RES_DCVS_IDX]);

  clk1_adapter = rpm_create_npa_adapter(RPM_CLOCK_1_REQ, 4); // Bus clocks: [cnoc_periph, snoc, cnoc, snoc_hs]
  rpm_associate_npa_resource(clk1_adapter, 0, aszClockNPAResNames[CLK_NPA_RES_CNOC_PERIPH_IDX]);
  rpm_associate_npa_resource(clk1_adapter, 1, aszClockNPAResNames[CLK_NPA_RES_SNOC_IDX]);
  rpm_associate_npa_resource(clk1_adapter, 2, aszClockNPAResNames[CLK_NPA_RES_CNOC_IDX]);
  rpm_associate_npa_resource(clk1_adapter, 3, aszClockNPAResNames[CLK_NPA_RES_SNOC_HS_IDX]);

  clk2_adapter = rpm_create_npa_adapter(RPM_CLOCK_2_REQ, 1); // Memory clocks: [bimc] 
  rpm_associate_npa_resource(clk2_adapter, 0, aszClockNPAResNames[CLK_NPA_RES_BIMC_IDX]);

  ipa_adapter = rpm_create_npa_adapter(RPM_CLOCK_IPA_REQ, 1); // ipa clock
  rpm_associate_npa_resource(ipa_adapter, 0, aszClockNPAResNames[CLK_NPA_RES_IPA_IDX]);

  ce_adapter = rpm_create_npa_adapter(RPM_CLOCK_CE_REQ, 1); // CE clock
  rpm_associate_npa_resource(ce_adapter, 0, aszClockNPAResNames[CLK_NPA_RES_CE1_IDX]);

  aggr_adapter = rpm_create_npa_adapter(RPM_CLOCK_AGGR_REQ, 3); // Aggre NOC clocks
  rpm_associate_npa_resource(aggr_adapter, 2, aszClockNPAResNames[CLK_NPA_RES_AGGRE2_IDX]);

  pimem_adapter = rpm_create_npa_adapter(RPM_CLOCK_PMEM_REQ, 1); // SYS PIMEM NOC clocks
  rpm_associate_npa_resource(pimem_adapter, 0, aszClockNPAResNames[CLK_NPA_RES_SNOC_PIMEM_IDX]);

  ckmm_adapter = rpm_create_npa_adapter(RPM_CLOCK_MMXI_REQ, 1); // MMSS NOC AXI clocks
  rpm_associate_npa_resource(ckmm_adapter, 0, aszClockNPAResNames[CLK_NPA_RES_MMAXI_IDX]);
 
  
  {
   /* Keep SNOC and MMNOC AXI clock rate matching with DDR */
    ClockNodeType *pClock = CLK_DELEGATE((ClockResourceType *)&pTargCtxt->BIMCResource.sClockRes);
    Clock_VoteMatchSpeed( pClock->pDomain->pActiveMuxConfig->nFreqHz / 1000 );
   /* Keep CNOC_PERIPH clock rate matching with CNOC */
    pClock = CLK_DELEGATE((ClockResourceType *)&pTargCtxt->CNOCClockResource);
    Clock_MatchCnocPeriph(pClock->pDomain->pActiveMuxConfig->nFreqHz / 1000);
  }
   /*spm adapter creation moved here to avoid any SPMfunction calls before gDDRFreqIndex variable is initialized,
    *  gDDRFreqIndex is initialized in the above Clock_VoteMatchSpeed function call 
    */
  clk_spm_adapter = rpm_create_npa_adapter(RPM_CLOCK_SPM_REQ, 1); // For SPM state transition callbacks
  rpm_associate_npa_resource(clk_spm_adapter, 0, aszClockNPAResNames[CLK_NPA_RES_SPM_IDX]);
  
  /* Init is done, resume voltage scaling with update PMIC */
  Clock_VoltageRequestSuspend( pDrvCtxt, CLOCK_VOLT_REQ_OPEN, TRUE );

  return DAL_SUCCESS;

} /* END Clock_InitImage */


/*===========================================================================

  FUNCTION      Clock_RestoreNocSpeeds

  DESCRIPTION   Restores or collapses (non-Aggre) NOCs for deep sleep
                entry/exit.
  
  PARAMETERS    bRestore [in] - Operation type (restore vs. collapse).

  DEPENDENCIES  None.

  RETURN VALUE  None.

  SIDE EFFECTS  None.

===========================================================================*/
static void Clock_RestoreNocSpeeds
(
  boolean   bRestore
)
{
  /* Extern needed for array init. */
  extern Clock_TargCtxtType Clock_Resources;

  ClockResourceType* ClockRestoreNocSpeedTable[] =
  {
    /* Keep RPM CPU at start of this array for performance reasons. */
    &Clock_Resources.CPUClockResource,

    &Clock_Resources.CNOCPeriphClockResource,
    &Clock_Resources.CNOCClockResource,
    &Clock_Resources.SNOCClockResource,
    &Clock_Resources.SNOCHSClockResource,
    &Clock_Resources.SNOCPIMEMClockResource,
  };

  uint32                          nIdx;
  int32                           nEntryDiff;
  int32                           nIdxEntry;
  int32                           nNumEntry;
  ClockResourceType               *pClockRes;
  ClockNodeType                   *pClock;
  ClockMuxConfigType              *pCfg;

  /*
   * Iterate array in opposite directions for collapse/restore to keep RPM CPU
   * running faster as long as possible.
   */
  if ( bRestore )
  {
    nEntryDiff = 1;
    nIdxEntry = 0;
  }
  else
  {
    nEntryDiff = -1;
    nIdxEntry = CLK_LAST_IDX(ClockRestoreNocSpeedTable);
  }

  nNumEntry = CLK_NUM_ELEM(ClockRestoreNocSpeedTable);
  pClockRes = ClockRestoreNocSpeedTable[nIdxEntry];

  for ( nIdx = 0; nIdx < nNumEntry; nIdx++ )
  {
    if ( pClockRes->nCurLevel != CLK_XO_LEVEL )
    {
      pClock = CLK_DELEGATE(pClockRes);

      if ( bRestore )
      {
        pCfg = &pClock->pDomain->pBSPConfig[pClockRes->nSavLevel];
      }
      else
      {
        pClockRes->nSavLevel = pClockRes->nCurLevel;
        pCfg = &pClock->pDomain->pBSPConfig[CLK_XO_LEVEL];
      }

      Clock_SetClockConfig( pClock, pCfg );
    }

    nIdxEntry += nEntryDiff;
    if ( nIdxEntry >= 0 && nIdxEntry < nNumEntry )
    {
      pClockRes = ClockRestoreNocSpeedTable[nIdxEntry];
    }
  }
}





/* =========================================================================
**  Function : Clock_ProcessorSleep
** =========================================================================*/
/*
  See Clock.h
*/

DALResult Clock_ProcessorSleep
(
  ClockSleepModeType  eMode,
  uint32              nFlags
)
{
  extern void HAL_clk_MMSSPowerDomainRestore (bool);
  uint32                   idx;
  ClockResourceType       *pClockRes;
  Clock_TargCtxtType      *pTargCtxt;
  ClockDrvCtxt            *pDrvCtxt;
  
  pTargCtxt = Clock_GetTargCtxt();
  pDrvCtxt = Clock_GetDrvCtxt();

  /* Suspend change voltage during power collapse */
  Clock_VoltageRequestSuspend( pDrvCtxt, CLOCK_VOLT_REQ_SUSPENDED, FALSE );

  SWEVENT( CLOCK_EVENT_POWER_COLLAPSE, CLOCK_SWE_PROCESSOR_ENTER );

  /* Put BIMC in power collapsed */
  if ( nFlags != 0 )
  {
    if(Clock_RPMTestFlags & CLOCK_RPM_TEST_FLAGS_DEEP_SLEEP_RESTORE_CHECK)
    {
      /* record frequency of clock domains before sleep entry */
      for(idx = 0; idx < pDrvCtxt->nNumClockDomains; idx++)
      {
        pDrvCtxt->aClockDomains[idx].nReferenceCountPreSleep = pDrvCtxt->aClockDomains[idx].nReferenceCount;

        if(pDrvCtxt->aClockDomains[idx].nReferenceCount > 0)
        {
          pDrvCtxt->aClockDomains[idx].pActiveMuxConfigPreSleep = pDrvCtxt->aClockDomains[idx].pActiveMuxConfig;
        }
      }
    }

#ifdef CLOCK_PSCBC_TEST
    do
    {
      extern int32 HAL_clk_CheckPSCBCs( uint32 index, uint32 *retPSCBCAddr, uint32 *retPSCBCValue );
      int nPSCBCIter = 0;
      uint32 nextPSCBCAddr = 0, nextPSCBCValue = 0;

      /* Pass a 0 as the interator index on the first call.  The function will search
       * for the next PSCBC that is on, and return that address in nextPSCBCAddr, and 
       * return an index to continue the search.  Continue calling this until the return
       * value is 0, when the nextPSCBCAddr will be NULL. */
      while(0 != (nPSCBCIter = HAL_clk_CheckPSCBCs(nPSCBCIter , &nextPSCBCAddr, &nextPSCBCValue)) )
      {
        /* Log the failure */
        SWEVENT(CLOCK_EVENT_PSCBC_CHECK, nextPSCBCAddr, nextPSCBCValue);
      } while(nPSCBCIter != 0)
      /* To indicate end of the list, log a NULL. */
      SWEVENT(CLOCK_EVENT_PSCBC_CHECK, 0);
    } while(0);
#endif
    /* Switch QDSS clocks to XO speed if they are ON */
    if ( pTargCtxt->QDSSResource.nQDSSCurrLevel != CLOCK_QDSS_LEVEL_OFF )
    {
      pClockRes = &pTargCtxt->QDSSResource.sClockRes;
      pClockRes->nSavLevel = pClockRes->nCurLevel;
      Clock_SetQDSSClocks(&pTargCtxt->QDSSResource, CLOCK_QDSS_SPEED_XO);
    }
  }
  else
  {
    /* Set BIMC collapsed done before collapse all non-BIMC clocks to XO speed */
    Clock_SetBIMCPowerCollapse(TRUE);

    /* Turn misc RAM clocks off */
    HAL_clk_DeepSleepDisableMiscClk();

    /* Force NOCs off. */
    Clock_RestoreNocSpeeds( FALSE );

    HAL_clk_GPLL0_disable_deep_sleep(); 
  }
  
  SWEVENT( CLOCK_EVENT_POWER_COLLAPSE, CLOCK_SWE_PROCESSOR_DONE );

  /* Sleep done, disable voltage suspend but don't update PMIC */
  Clock_VoltageRequestSuspend( pDrvCtxt, CLOCK_VOLT_REQ_OPEN, FALSE );

  return DAL_SUCCESS;

} /* END Clock_ProcessorSleep */


/* =========================================================================
**  Function : Clock_ProcessorRestore
** =========================================================================*/
/*
  See ClockDriver.h
*/

DALResult Clock_ProcessorRestore
(
  ClockSleepModeType  eMode,
  uint32              nFlags
)
{
  uint32                   idx;
  ClockResourceType       *pClockRes;
  Clock_TargCtxtType      *pTargCtxt;
  ClockDrvCtxt            *pDrvCtxt;  

  pDrvCtxt = Clock_GetDrvCtxt();

  /* Don't allow voltage change during processor restore */
  Clock_VoltageRequestSuspend( pDrvCtxt, CLOCK_VOLT_REQ_SUSPENDED, FALSE );

  SWEVENT( CLOCK_EVENT_POWER_RESTORE, CLOCK_SWE_PROCESSOR_ENTER );
  
  pTargCtxt = Clock_GetTargCtxt();

  /* BIMC restored. */
  if ( nFlags != 0 )
  {
    /* Restore QDSS clocks */
    if ( pTargCtxt->QDSSResource.nQDSSCurrLevel != CLOCK_QDSS_LEVEL_OFF )
    {
      pClockRes = &pTargCtxt->QDSSResource.sClockRes;
      Clock_SetQDSSClocks(&pTargCtxt->QDSSResource,
                          (ClockQDSSSpeedType)pClockRes->nSavLevel);
    }

    if(Clock_RPMTestFlags & CLOCK_RPM_TEST_FLAGS_DEEP_SLEEP_RESTORE_CHECK)
    {
      /* verify frequency of clock domains after sleep exit */
      for(idx = 0; idx < pDrvCtxt->nNumClockDomains; idx++)
      {
        CORE_VERIFY(pDrvCtxt->aClockDomains[idx].nReferenceCountPreSleep == pDrvCtxt->aClockDomains[idx].nReferenceCount);

        if(pDrvCtxt->aClockDomains[idx].nReferenceCount > 0)
        {
          CORE_VERIFY(pDrvCtxt->aClockDomains[idx].pActiveMuxConfigPreSleep == pDrvCtxt->aClockDomains[idx].pActiveMuxConfig);
        }
      }
    }
  }
  else
  {
    HAL_clk_GPLL0_FSM_reset_deep_sleep();

    /* Restore NOCs. */
    Clock_RestoreNocSpeeds( TRUE );


    /* Turn MISC RAM clocks back on */
    HAL_clk_MiscClkRestoreDuringWakeup();
      
    /* Restore BIMC */
    Clock_SetBIMCPowerRestore();
  }

  /* Restore done, allow voltage change when exit power collapse, but don't update PMIC */
  Clock_VoltageRequestSuspend( pDrvCtxt, CLOCK_VOLT_REQ_OPEN, FALSE );

  SWEVENT( CLOCK_EVENT_POWER_RESTORE, CLOCK_SWE_PROCESSOR_DONE );

  return DAL_SUCCESS;

} /* END Clock_ProcessorRestore */


/* =========================================================================
**  Function : Clock_Init
** =========================================================================*/
/*
  See ClockDriver.h
*/

__attribute__((section("clk_cram_reclaim_pool")))
boolean Clock_Init (void)
{
  CORE_DAL_VERIFY( Clock_DriverInit() );

  return TRUE;

} /* END Clock_Init */
