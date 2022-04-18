/*
===========================================================================
*/
/**
  @file ClockRPMBIMC.c 
  
  BIMC APIs definitions for the MSM8994 RPM clock driver.
*/
/*  
  ====================================================================

  Copyright (c) 2013-2015 QUALCOMM Technologies, Inc.  All Rights Reserved.  
  QUALCOMM Proprietary and Confidential. 

  ==================================================================== 
  $Header: //components/rel/rpm.bf/1.8/core/systemdrivers/clock/hw/sdm660/ClockRPMBIMC.c#6 $
  $DateTime: 2017/02/14 22:30:40 $
  $Author: pwbldsvc $
 
  when       who     what, where, why
  --------   ---     -------------------------------------------------
  03/22/16   dai     Ported for 8998
  11/27/13   vph     Initial version
 
  ====================================================================
*/ 


/*=========================================================================
      Include Files
==========================================================================*/

#include "ddr_drivers.h"
#include "swevent.h"
#include "ClockRPMNPA.h"
#include "ClockRPMBIMC.h"
#include "ClockCommon.h"
#include "assert.h"
#include "CoreVerify.h"
#include "HALclk.h"
#include "smem.h"
#include "page_select.h"
#include "time_service.h"

/*=========================================================================
      Macros
==========================================================================*/
#define MIN_FREQ_KHZ 200000

#define NUM_LOGS 8
typedef struct
{
  uint64 nTimeStamp;
  uint32 nDDRFreqKHz;
} Clock_DDRLogType;

Clock_DDRLogType DDRLogs[NUM_LOGS];
uint32 nIndex = 0;

typedef struct
{
  uint32 clk_dbg_bimc_pc_count;
  uint32 clk_dbg_bimc_pc_restore_count;
  uint32 clk_dbg_bimc_pc_parallelization_count;
  uint32 clk_dbg_bimc_pc_parallelization_restore_count;
} bimc_pc_debug_type;

static bimc_pc_debug_type bimc_pc_debug;

/*=========================================================================
      Prototypes
==========================================================================*/
extern void Clock_VoteMatchSpeed( uint32 nDDRFreqKHz );
void Clock_SNOCVoteMatchSpeed( uint32 nSNOCFreqKHz, uint32 nSNOCHSFreqKHz, uint32 *nNewSNOCFreqKHz, uint32 *nNewSNOCHSFreqKHz );
extern void HAL_clk_DDRPC ( boolean bCollapse );
void Clock_SetDirectBusSpeed( ClockBusType eBusID, uint32 nNewSpeedKHz ){};

/*=========================================================================
      Data
==========================================================================*/\

extern Clock_TargCtxtType Clock_Resources;
extern npa_resource_definition Clock_NPAResources[];

/*
 * Dynamic DDR PLL configurations (shared from SBL).
 */
static ClockSourceConfigType *gpBIMCPLLConfig = NULL;

/*
 * DDR CPLL Clock configurations (shared from SBL).
 *
** =========================================================================
**
** 'HAL_clk_ClockMuxConfigType' repurposing (allows RPM-HAL compatibilty):
**
**    nDiv2x[15:8]  - index to DDRCC config (zeroed out for RPM)
**    nDiv2x[7:0]   - DDR nDiv2x (placed here for RPM detect mux config)
**
**    nM[15]        - 1 iff level uses DDRCC mode
**    nM[14:8]      - index to GPLL23 config
**    nM[7:0]       - APSS nDiv2x

**    nN[15:8]      - GFX nDiv2x
**    nN[7:0]       - MPSS nDiv2x
**
**    n2D[15:0]     - VDDA EBI vote
**
** =========================================================================*/
static ClockMuxConfigType *gpDDRClockConfig = NULL;

/* =========================================================================
**  Function : Clock_BIMCSetVDDAVoltage()
** =========================================================================*/
/**
  This function is used for setting VDDA_EBI voltage and store the voltage level
  for next bimc clock switching.

  @param 
      eNewLevel - New voltage level

  @return
      None
*/
void Clock_BIMCSetVDDAVoltage
( 
  ClockVRegLevelType eNewLevel 
)
{
  Clock_Resources.BIMCResource.nVDDA = eNewLevel;
  Clock_SetVDDAVoltage( eNewLevel );
}


/*===========================================================================

  FUNCTION      Clock_BIMCPrepareClockSource

  DESCRIPTION   If necessary, prepare the next BIMC PLL change.

  PARAMETERS    pNewConfig [in] - pointer to next BSP config

  DEPENDENCIES  None.

  RETURN VALUE  None.

  SIDE EFFECTS  None.

===========================================================================*/
static void Clock_BIMCPrepareClockSource
(
  ClockMuxConfigType  *pNewConfig
)
{
  /* Only GPLL2 and GPLL3 need preparation for ping-pong */
  if ( (pNewConfig->HALConfig.eSource == HAL_CLK_SOURCE_GPLL2) ||
       (pNewConfig->HALConfig.eSource == HAL_CLK_SOURCE_GPLL3) )
  {
    CORE_VERIFY_PTR( pNewConfig->pSourceConfig );

    /* Switch to an unused PLL */
    if ( HAL_clk_IsSourceVoteEnabled(HAL_CLK_SOURCE_GPLL2) == FALSE )
    {
      pNewConfig->HALConfig.eSource = HAL_CLK_SOURCE_GPLL2;
      pNewConfig->pSourceConfig->eSource = HAL_CLK_SOURCE_GPLL2;
    }
    else if ( HAL_clk_IsSourceVoteEnabled(HAL_CLK_SOURCE_GPLL3) == FALSE )
    {
      pNewConfig->HALConfig.eSource = HAL_CLK_SOURCE_GPLL3;
      pNewConfig->pSourceConfig->eSource = HAL_CLK_SOURCE_GPLL3;
    }
    else
    {
      /* Either GPLL2 or GPLL3 are required to be inactive. */
      CORE_VERIFY( FALSE );
    }
  }
}



DALResult Clock_EnableBIMCSources(bool bEnable, ClockMuxConfigType  *pNewConfig)
{
  DALResult            eResult;
  ClockDrvCtxt         *pDrvCtxt = Clock_GetDrvCtxt();
  HAL_clk_SourceType   nNewPLL[MAX_BIMC_DDR_ASYNC_CLK];
  ClockSourceNodeType  *pSource;
  int id = 0;
  Clock_BIMCAsyncClkState *pAsyncClockState =  Clock_Resources.BIMCResource.sAsyncClockState;

  nNewPLL[0] = HAL_clk_getDDRSources(&pNewConfig->HALConfig);
  nNewPLL[1] = HAL_clk_getBIMCSources(&pNewConfig->HALConfig);
  nNewPLL[2] = HAL_clk_getHMSSSources(&pNewConfig->HALConfig);
  nNewPLL[3] = HAL_clk_getGFXSources(&pNewConfig->HALConfig);
  nNewPLL[4] = HAL_clk_getMPSSSources(&pNewConfig->HALConfig);
  nNewPLL[5] = HAL_clk_get_CDSPSources(&pNewConfig->HALConfig);

//  Clock_EnableSource(pDrvCtxt, &pDrvCtxt->aSources[pDrvCtxt->anSourceIndex[nNewPLL[id]]]);


  while( id < MAX_BIMC_DDR_ASYNC_CLK)
  {
    if(nNewPLL[id] != pAsyncClockState[id].nCurrPLL)
    {
      if(bEnable)
      {
        pSource = &pDrvCtxt->aSources[pDrvCtxt->anSourceIndex[nNewPLL[id]]];
        eResult = Clock_EnableSource(pDrvCtxt, pSource);
      }
      else
      {
        pSource = &pDrvCtxt->aSources[pDrvCtxt->anSourceIndex[pAsyncClockState[id].nCurrPLL]];
        eResult = Clock_DisableSource(pDrvCtxt, pSource);
        pAsyncClockState[id].nCurrPLL = nNewPLL[id];
      }
      if(eResult != DAL_SUCCESS)
      {
        return eResult;
      }
    }
    id++;
  }
  return DAL_SUCCESS;
}


/*===========================================================================

  FUNCTION      Clock_BIMCSetClockConfig

  DESCRIPTION   Sets DDR frequency. Switches the voltage first, calls
                ddr_pre_clock_switch(), then switches the clock.
                  
  PARAMETERS    pDomain    - Clock domain for setting voltage
                pNewConfig - New config frequency

  DEPENDENCIES  None.

  RETURN VALUE  DAL_SUCCESS iff successful.

  SIDE EFFECTS  None.

===========================================================================*/
typedef enum{
BIMC_CLOCK_CFG_ENTER = 0,
BIMC_CFG_SOURCE,
BIMC_ENABLE_BIMC_SRC,
BIMC_CALLBACK_CALLED,
BIMC_BEFORE_MUX_CFG,
BIMC_BEFORE_DDR_PRE_CLK_SWITCH,
BIMC_BEFORE_DDR_CLK_SWITCH,
BIMC_BEFORE_DDR_POST_CLK_SWITCH,
BIMC_DISABLE_BIMC_SRC,
BIMC_PRE_DDR_ENTER_PC,
BIMC_POST_DDR_ENTER_PC,
BIMC_PRE_ENABLE_DDR_PWR_DOMAIN,
BIMC_POST_ENABLE_DDR_PWR_DOMAIN,
BIMC_PRE_DDR_EXIT_PC,
BIMC_POST_DDR_EXIT_PC,
BIMC_CLK_CFG_EXIT,
BIMC_CFG_INVALID = 0x7FFFFFF
}BIMC_CLOCK_CFG_DBG;
volatile BIMC_CLOCK_CFG_DBG bimc_clk_cfg_dbg = BIMC_CFG_INVALID;

DALResult Clock_BIMCSetClockConfig
(
  ClockNodeType       *pClock,
  ClockMuxConfigType  *pNewConfig
)
{
  ClockSourceNodeType     *pNewSource;
  DALResult               eResult;
  uint32                  nSrcIdx = 0xFF;
  boolean                 bVoltageRequest;
  uint32                  nCurClkKHz, nNewClkKHz;
  ClockCallbackType       pCallback;
  int                     nIdx;
  ClockDrvCtxt            *pDrvCtxt = Clock_GetDrvCtxt();
  ClockDomainNodeType     *pDomain  = pClock->pDomain;

  debug_marker(bimc_clk_cfg_dbg, BIMC_CLOCK_CFG_ENTER);
  /* Make sure the domain handle is valid */
  if ( (pDomain == NULL) || (pDomain->pActiveMuxConfig == NULL) )
  {
    return DAL_ERROR;
  }

  nCurClkKHz = pDomain->pActiveMuxConfig->nFreqHz / 1000;
  nNewClkKHz = pNewConfig->nFreqHz / 1000;

  /*
   * Determine if we should make a voltage request.  We do so if this
   * domain is not configured to make requests when enabled, or if it
   * is thus configured and is currently enabled.
   */
  bVoltageRequest = !CLOCK_FLAG_IS_SET(pDomain, DOMAIN_HOLD_VREG_REQUEST);

  /* Get the new source pointer. */
  Clock_BIMCPrepareClockSource(pNewConfig);
    
  if ( pNewConfig->HALConfig.eSource < HAL_CLK_NUM_OF_SOURCES )
  {
    nSrcIdx = pDrvCtxt->anSourceIndex[pNewConfig->HALConfig.eSource];
  }

  if (nSrcIdx != 0xFF)
  {
    pNewSource = &pDrvCtxt->aSources[nSrcIdx];
  }
  else
  {
    pNewSource = NULL;
  }

  // Set VDDA_EBI voltage
  if ( HAL_CLK_BIMC_N2D_VDDA_EBI_VOTE(pNewConfig->HALConfig.n2D) > Clock_Resources.BIMCResource.nVDDA )
  {
    Clock_BIMCSetVDDAVoltage( (ClockVRegLevelType)HAL_CLK_BIMC_N2D_VDDA_EBI_VOTE(pNewConfig->HALConfig.n2D) );
  }

  /*
   * If we are increasing the voltage requirement, do so now.
   */
  if (bVoltageRequest && pNewConfig->eVRegLevel > pDomain->eVRegLevel)
  {
    Clock_VoltageRequest(
      pDrvCtxt, &pDomain->eVRegLevel, pNewConfig->eVRegLevel, FALSE);
  }

  /*
   * Configure the source if required.
   */
  if ((pNewSource != NULL) && (pNewConfig->pSourceConfig != NULL))
  {
	debug_marker(bimc_clk_cfg_dbg, BIMC_CFG_SOURCE);
    eResult = Clock_ConfigSource(
      pDrvCtxt, pNewSource, pNewConfig->pSourceConfig);

    if (eResult != DAL_SUCCESS)
    {
      // TODO error!
      return eResult;
    }
  }


#if 0
  
  /*
   * If the new source is different from the
   * current one then we enable the new source.
   */
  if ((pDomain->pSource != pNewSource) &&
      (pNewSource != NULL))
  {
    eResult = Clock_EnableSource(pDrvCtxt, pNewSource);

    if (eResult != DAL_SUCCESS)
    {
      return eResult;
    }
  }
#endif
  
  debug_marker(bimc_clk_cfg_dbg, BIMC_ENABLE_BIMC_SRC);
  Clock_EnableBIMCSources(TRUE, pNewConfig);

  /* Call the callbacks if any are registered */
  if( pDomain->pCallbacks != NULL )
  {
    for(nIdx = 0; nIdx < CLOCK_CALLBACK_MAX; nIdx++)
    {
      if( pDomain->pCallbacks[nIdx].pCallback != NULL )
      {
        pCallback = pDomain->pCallbacks[nIdx].pCallback;
		debug_marker(bimc_clk_cfg_dbg, BIMC_CALLBACK_CALLED);
        pCallback( CLOCK_PRE_CALLBACK, nCurClkKHz, nNewClkKHz, 
                      pDomain->pCallbacks[nIdx].pCallbackData );
      }
    }
  }

  /*
   * Configure the clock MUX
   */
  debug_marker(bimc_clk_cfg_dbg, BIMC_BEFORE_MUX_CFG);
  HAL_clk_ConfigClockMux(pDomain->HALHandle, &pNewConfig->HALConfig);
 
  /* Inform BIMC that Clock Switches are complete */
  debug_marker(bimc_clk_cfg_dbg, BIMC_BEFORE_DDR_PRE_CLK_SWITCH);
  ddr_pre_clock_switch( nCurClkKHz, nNewClkKHz, SDRAM_INTERFACE_BOTH );
  debug_marker(bimc_clk_cfg_dbg, BIMC_BEFORE_DDR_CLK_SWITCH);
  ddr_clock_switch( nCurClkKHz, nNewClkKHz, SDRAM_INTERFACE_BOTH );
  debug_marker(bimc_clk_cfg_dbg, BIMC_BEFORE_DDR_POST_CLK_SWITCH);
  ddr_post_clock_switch( nCurClkKHz, nNewClkKHz, SDRAM_INTERFACE_BOTH );

  /* Log timestamp and new switch frequency */
  DDRLogs[nIndex].nTimeStamp = time_service_now();
  DDRLogs[nIndex].nDDRFreqKHz = nNewClkKHz;
  nIndex++;
  nIndex = nIndex % NUM_LOGS;

  /*
   * Disable Previous Clock
   */
  HAL_clk_DisableClock(pClock->HALHandle);

  /* Log clock frequency */
  SWEVENT( CLOCK_EVENT_FREQ,
           HAL_clk_GetTestClockId(pClock->HALHandle),
           pNewConfig->nFreqHz );


  /* Call the callbacks if any are registered */
  if( pDomain->pCallbacks != NULL )
  {
    for(nIdx = 0; nIdx < CLOCK_CALLBACK_MAX; nIdx++)
    {
      if( pDomain->pCallbacks[nIdx].pCallback != NULL )
      {
        pCallback = pDomain->pCallbacks[nIdx].pCallback;
        pCallback( CLOCK_POST_CALLBACK, nCurClkKHz, nNewClkKHz, 
                      pDomain->pCallbacks[nIdx].pCallbackData );
      }
    }
  }

#if 0
  /*
   * If the domain is active, and the new source is different from the
   * current then we disable the old source.
   */
  if ((pDomain->pSource != pNewSource) &&
      (pDomain->pSource != NULL))
  {
    Clock_DisableSource(pDrvCtxt, pDomain->pSource);
  }

#endif
  
  debug_marker(bimc_clk_cfg_dbg, BIMC_DISABLE_BIMC_SRC);
  Clock_EnableBIMCSources(FALSE, pNewConfig);

  /* Link the domain node to the new source node and update the active config */
  pDomain->pSource = pNewSource;

  /*
   * If we are decreasing the voltage requirement, do so now.
   */
  if (bVoltageRequest && pNewConfig->eVRegLevel < pDomain->eVRegLevel)
  {
    Clock_VoltageRequest(
      pDrvCtxt, &pDomain->eVRegLevel, pNewConfig->eVRegLevel, FALSE);
  }
 
  // Set VDDA_EBI voltage
  if ( HAL_CLK_BIMC_N2D_VDDA_EBI_VOTE(pNewConfig->HALConfig.n2D) < Clock_Resources.BIMCResource.nVDDA )
  {
    Clock_BIMCSetVDDAVoltage( (ClockVRegLevelType)HAL_CLK_BIMC_N2D_VDDA_EBI_VOTE(pNewConfig->HALConfig.n2D) );
  }

  /*
   * Check if the current configuration was setup dynamically
   */
  if(CLOCK_FLAG_IS_SET(pDomain, DOMAIN_DYNAMIC_CONFIG))
  {
    /*
     * If new configuration is different from the current one then
     * free up memory.
     */
    if(pDomain->pActiveMuxConfig != pNewConfig)
    {
      CLOCK_FLAG_CLEAR(pDomain, DOMAIN_DYNAMIC_CONFIG);
      DALSYS_Free (pDomain->pActiveMuxConfig);
    }
  }

  pDomain->pActiveMuxConfig = pNewConfig;
  debug_marker(bimc_clk_cfg_dbg, BIMC_CLK_CFG_EXIT);

  return DAL_SUCCESS;

} /* END Clock_BIMCSetClockConfig */


/*===========================================================================

  FUNCTION      Clock_BIMCSwitchFrequency

  DESCRIPTION   Sets BIMC clock frequencies (DDR, APPS, Modem & GFX ports).
                Does not perform BIMC collapse or restore.

  PARAMETERS    pBIMCClk   [in] - BIMC clock resource.
                nNewClkKHz [in] - New clock speed (in KHz).

  DEPENDENCIES  None.

  RETURN VALUE  New clock speed (in KHz).

  SIDE EFFECTS  None.

===========================================================================*/
static uint32 Clock_BIMCSwitchFrequency
(
  BIMCResourceType    *pBimcRes,
  uint32              nNewClkKHz
)
{
  uint32              nCurClkKHz, nCfg, nSupCfg;
  ClockResourceType   *pClockRes  = &pBimcRes->sClockRes;
  ClockNodeType       *pClock     = CLK_DELEGATE(pClockRes);
  ClockMuxConfigType  *pNewConfig = pClock->pDomain->pBSPConfig;

  /* First the new request frequency that match to support clock level */
  nSupCfg = pClockRes->nMinLevel;
  for ( nCfg = pClockRes->nMinLevel; nCfg <= pClockRes->nMaxLevel; nCfg++ )
  {
    if ( Clock_IsBSPSupported(&pNewConfig[nCfg]) )
    {
      nSupCfg = nCfg;
      // Found new config clock that close or equal the requested frequency
      if ( nNewClkKHz <= (pNewConfig[nCfg].nFreqHz / 1000) )
      {
        break;
      }
    }
  }
  nNewClkKHz = pNewConfig[nSupCfg].nFreqHz / 1000;
  nCurClkKHz = pNewConfig[pClockRes->nCurLevel].nFreqHz / 1000;

  /* Change BIMC clock if new frequency is not equal to the current one */
  if ( nNewClkKHz != nCurClkKHz )
  {
    if ( (nNewClkKHz >= 1500000) && 
         (nNewClkKHz == pNewConfig[pClockRes->nMaxLevel].nFreqHz / 1000) )
    {
      /* Switch to the one before Fmax */
      if ( nCurClkKHz < pNewConfig[pClockRes->nMaxLevel-1].nFreqHz / 1000 )
      {
        nCurClkKHz = Clock_SetClockSpeed( pClockRes, pNewConfig[pClockRes->nMaxLevel-1].nFreqHz ) / 1000;
      }
    }
    Clock_SetClockSpeed( pClockRes, nNewClkKHz * 1000 );
    Clock_VoteMatchSpeed( nNewClkKHz );
  }
  return nNewClkKHz;
}

/* =========================================================================
**  Function : Clock_BIMCCollapse
** =========================================================================*/
/**
  This function is used for putting DDR in power collapse or self-refresh mode.

  @param 
    None

  @return
    None

  @dependencies
    None

  @sa
    None
*/
static uint32 Clock_BIMCCollapse( BIMCResourceType *pBimcRes )
{
  uint32                  nNewFreqKHz = MIN_FREQ_KHZ;
  
  // Only enter this state when BIMC is in BIMC_ON.  Abort otherwise
  assert ( pBimcRes->eBIMCState == BIMC_ON );

  Clock_BIMCSwitchFrequency( pBimcRes, nNewFreqKHz );

  /* If BIMC in power collapsed mode */
  if ( pBimcRes->bPCModeEn == TRUE )
  {
    /* Put DDR to power collapse and freeze IO */
	debug_marker(bimc_clk_cfg_dbg, BIMC_PRE_DDR_ENTER_PC);
    ddr_enter_power_collapse( nNewFreqKHz );
	debug_marker(bimc_clk_cfg_dbg, BIMC_POST_DDR_ENTER_PC);
    /* Disable DDRCPLL and Port Clocks */
    HAL_clk_DDRPC ( TRUE );

	/* Debug variable count the no. of Collapses*/
    bimc_pc_debug.clk_dbg_bimc_pc_count++;

    /* Disable BIMC power domain for BIMC collapse */
    Clock_DisablePowerDomain( pBimcRes->nBIMCPowerID );
    /* Disable DDR power domain for DDR PHY collapse */
    if(pBimcRes->bPCDDRPHYModeEn == TRUE)
    {
      Clock_DisablePowerDomain( pBimcRes->nDDRPHYPowerID );
    }
  }
  else
  {
    /* Put DDR in self-refresh mode */
    ddr_pre_xo_shutdown( nNewFreqKHz );
  }

  /* Disable Current BIMC clock */
  pBimcRes->eBIMCState = BIMC_COLLAPSED;

  // Vote retention for VDDA_EBI voltage
 //  Clock_BIMCSetVDDAVoltage ( CLOCK_VREG_LEVEL_RETENTION );


  return 0;
}


/* =========================================================================
**  Function : Clock_BIMCRestore
** =========================================================================*/
/**
  This function is used for restoring BIMC clocks.  It will set
  BIMC state to BIMC_RESTORING state.

  @param 
    nFreqKHz - Restoring frequency once BIMC is up.

  @return
    None

  @dependencies
    None

  @sa
    None
*/
static uint32 Clock_BIMCRestore( BIMCResourceType *pBimcRes, uint32 nFreqKHz )
{
  uint32              nBimcMinFreqKHz = MIN_FREQ_KHZ;
  uint32              nNewFreqKHz;
  //ClockResourceType   *pClockRes;
  // Only enter this state when BIMC is in BIMC_COLLAPSED.  Abort otherwise
  assert ( pBimcRes->eBIMCState == BIMC_COLLAPSED );

  // MX is already at LOW_MINUS
 // Clock_BIMCSetVDDAVoltage ( CLOCK_VREG_LEVEL_LOW_MINUS );

//  pClockRes = &pBimcRes->sClockRes;
                  
  /* Enable the CPLL that was Active before Power Collapse*/
  HAL_clk_DDRPC ( FALSE );
  //HAL_clk_EnableClock ( (CLK_DELEGATE(pClockRes))->HALHandle );

  /* Restore BIMC from its collapsed state. */
  if ( pBimcRes->bPCModeEn == TRUE )
  {
	debug_marker(bimc_clk_cfg_dbg, BIMC_PRE_ENABLE_DDR_PWR_DOMAIN);
    /* Enable DDR power domain for BIMC collapse */
    if(pBimcRes->bPCDDRPHYModeEn == TRUE)
    {
      Clock_EnablePowerDomain( pBimcRes->nDDRPHYPowerID, FALSE );
    }
	debug_marker(bimc_clk_cfg_dbg, BIMC_POST_ENABLE_DDR_PWR_DOMAIN);
    /* Enable BIMC power domain for BIMC collapse */
    Clock_EnablePowerDomain( pBimcRes->nBIMCPowerID, FALSE );

    /* Wait for all BIMC clocks to report on */
    // Clock_WaitForClockOn( CLK_DELEGATE(pClockRes), CLK_ON_WAIT_USEC );

    /* Call DDR to for exit power collapse */
	debug_marker(bimc_clk_cfg_dbg, BIMC_PRE_DDR_EXIT_PC);
    ddr_exit_power_collapse( nBimcMinFreqKHz );
	debug_marker(bimc_clk_cfg_dbg, BIMC_POST_DDR_EXIT_PC);
	bimc_pc_debug.clk_dbg_bimc_pc_restore_count++;
  }
  else
  {
    /* Take DDR out of self-refresh as lowest level */
    ddr_post_xo_shutdown( nBimcMinFreqKHz);
  }

  nNewFreqKHz = Clock_BIMCSwitchFrequency( pBimcRes, nFreqKHz );
  
  pBimcRes->eBIMCState = BIMC_ON;
  
  /* Log clock frequency */
  SWEVENT(CLOCK_EVENT_BIMC_RESTORE, CLOCK_SWE_BIMC_RESTORING_DONE );

  return nNewFreqKHz;
}


/*===========================================================================

  FUNCTION      Clock_BIMCSetFrequency

  DESCRIPTION   Sets BIMC clock frequencies (DDR, APPS, Modem & GFX ports),
                performing BIMC collapse/restore if needed.
  
  PARAMETERS    nNewClkKHz [in] - New clock speed (in KHz).

  DEPENDENCIES  None.

  RETURN VALUE  New clock speed (in KHz).

  SIDE EFFECTS  None.

===========================================================================*/
uint32 Clock_BIMCSetFrequency
(
  BIMCResourceType    *pBimcRes,
  uint32              nNewClkKHz
)
{
  uint32        nFreqKHz  = 0;
  if(pBimcRes->nChannelDDR == 0)
  {
    pBimcRes->nChannelDDR = HALGetSLActiveCH();
  }
  
  /*for MSM1.0, only single channel is active so multiply the requst by 2*/
  if(pBimcRes->nChannelDDR == 1)
  {
    nNewClkKHz  = 3*nNewClkKHz;
  }
  /* Switch clock if BIMC is already on, and new requesting frequency is not off (0) */
  if ( (Clock_Resources.BIMCResource.eBIMCState == BIMC_ON) && (nNewClkKHz != 0) )
  {
    return Clock_BIMCSwitchFrequency( pBimcRes, nNewClkKHz );
  }
  /* New frequency is zero, collapsing BIMC */
  if ( nNewClkKHz == 0 )
  {
	if (Clock_Resources.BIMCResource.eBIMCState == BIMC_ON)
    {
      bimc_pc_debug.clk_dbg_bimc_pc_parallelization_count++;
    }
    return Clock_BIMCCollapse( pBimcRes );
  }
  /* New frequency is non-zero, restore BIMC */
  else
  {
    if(Clock_Resources.BIMCResource.eBIMCState == BIMC_COLLAPSED)
    {
      bimc_pc_debug.clk_dbg_bimc_pc_parallelization_restore_count++;
    }
    nFreqKHz = Clock_BIMCRestore( pBimcRes, nNewClkKHz );
  }
  return nFreqKHz;
}


/* =========================================================================
**  Function : Clock_SetBIMCPowerCollapse
** =========================================================================*/
/**
  This function is used for setting BIMC in Power Collapsed Mode.

  @param bCollapsed [in] 
      bCollapsed - Not used

  @return
      None
*/

void Clock_SetBIMCPowerCollapse( boolean bCollapsed )
{
  ClockResourceType *pClockRes; 
  BIMCResourceType  *pBimcRes = &Clock_Resources.BIMCResource;

  /* Save BIMC state for restore after XO restore */
  pBimcRes->eXOBIMCState = pBimcRes->eBIMCState;

  if ( pBimcRes->eBIMCState != BIMC_COLLAPSED )
  {
    pClockRes = &pBimcRes->sClockRes;
    pClockRes->nSavLevel = pClockRes->nCurLevel;
    Clock_BIMCCollapse(pBimcRes);
  }
}


/* =========================================================================
**  Function : Clock_SetBIMCPowerRestore
** =========================================================================*/
/**
  This function is used for restore BIMC out of Power Collapsed Mode.

  @param 
      None

  @return
      None
*/

void Clock_SetBIMCPowerRestore( void )
{
  uint32              nFreqKHz;
  ClockMuxConfigType  *pBimcCfg;
  ClockResourceType   *pDDRCP0ClkRes;
  BIMCResourceType    *pBimcRes   = &Clock_Resources.BIMCResource;

  /* Only restore BIMC if it was ON before XO shutdown */
  if ( pBimcRes->eXOBIMCState == BIMC_ON )
  {
    pDDRCP0ClkRes = &pBimcRes->sClockRes;
    pBimcCfg  = pDDRCP0ClkRes->apClocks[0]->pDomain->pBSPConfig;
    nFreqKHz = (pBimcCfg[pDDRCP0ClkRes->nSavLevel].nFreqHz / 1000);

    Clock_BIMCRestore(pBimcRes, nFreqKHz);
  }
}

/* =========================================================================
**  Function : Clock_BIMCCopySingleTableFromShared
** =========================================================================*/
/**
  Factored from Clock_BIMCCopyPlanFromShared, this helper function copies
  one table from shared memory into an allocated region and sets the pointer

  @param 
    pSMEM : A pointer to shared memory
    nTable : The offset of the table
    ppTable : A pointer to the table pointer to be malloc and filled.
    nSize : The sizeof() of one element of ppTable.

  @return
    TRUE : Success
    FALSE : Mismatched or missing data in shared memory.
*/
__attribute__((section("clk_cram_reclaim_pool")))
static boolean Clock_BIMCCopySingleTableFromShared
(
  char *pSMEM, 
  uint32 nTable,
  void **ppTable,
  uint32 nSize
)
{
  uint32 nItemSize, nItemCount, nItemOffset;
  ClockBIMCTableHeaderType *pBIMCTableHeaders;

  pBIMCTableHeaders = (ClockBIMCTableHeaderType *)(pSMEM + sizeof(ClockBIMCConfigInfo));

  if( pBIMCTableHeaders[nTable].nNodeSize != nSize ) return FALSE;
  nItemSize = pBIMCTableHeaders[nTable].nNodeSize;
  nItemCount = pBIMCTableHeaders[nTable].nNumNodes;
  nItemOffset = pBIMCTableHeaders[nTable].nNodeOffset;

  /* Allocate the new table */
  if(ppTable == NULL) return FALSE;
  *ppTable = malloc(nItemSize * nItemCount);
  if( *ppTable == NULL ) return FALSE;

  memcpy(*ppTable, pSMEM + nItemOffset, nItemSize * nItemCount);
  return TRUE;
}


/* =========================================================================
**  Function : Clock_BIMCCopyPlanFromShared
** =========================================================================*/
/**
  This function reads the BIMC clock plan from shared memory and copies it
  into the clock data structures.

  NOTE: only supports one DDR RCG config table to cover all BIMC clients.

  @param 
      pTargCtxt [in] - Clock driver target context.

  @return
    TRUE : Success
    FALSE : Mismatched or missing data in shared memory.
*/
__attribute__((section("clk_cram_reclaim_pool")))
boolean Clock_BIMCCopyPlanFromShared( Clock_TargCtxtType *pTargCtxt )
{
  uint32 nTable, nPLLCfgIdx, smem_size, nSrcIdx;
  ClockBIMCConfigInfo       *pBIMCConfigInfo;
  ClockBIMCTableHeaderType  *pBIMCTableHeaders;
  ClockNodeType             *pClock;
  uint32                    nPLLConfigCount = 0;
  ClockDrvCtxt              *pDrvCtxt = Clock_GetDrvCtxt();

  char *pSMEM = (char *)smem_get_addr(SMEM_CLOCK_INFO, &smem_size);

  /* update page select bit for DDR access */  
  set_page_select( 2 );

  if(pSMEM == NULL) {set_page_select(0); return FALSE;}

  pBIMCConfigInfo = (ClockBIMCConfigInfo *)pSMEM;
  if( pBIMCConfigInfo->nVersion != CLOCK_BIMC_SMEM_VERSION ) return FALSE;
  if( pBIMCConfigInfo->nNumConfig != CLOCK_BIMC_NUM_TABLES ) return FALSE;

  /* Override config for BIMC clocks */
  Clock_Resources.BIMCResource.sClockRes.nMinLevel = pBIMCConfigInfo->nMinLevel;
  Clock_Resources.BIMCResource.sClockRes.nMaxLevel = pBIMCConfigInfo->nMaxLevel;
  Clock_Resources.BIMCResource.sClockRes.nCurLevel = pBIMCConfigInfo->nActiveLevel;

  if( pBIMCConfigInfo->nConfigData != sizeof(ClockBIMCConfigInfo) ) return FALSE;

  pBIMCTableHeaders = (ClockBIMCTableHeaderType *)(pSMEM + sizeof(ClockBIMCConfigInfo));

  for(nTable = 0; nTable < pBIMCConfigInfo->nNumConfig; nTable++)
  {
    switch(pBIMCTableHeaders[nTable].eBIMCTable)
    {
      case CLOCK_BIMC_PLL:
        if( Clock_BIMCCopySingleTableFromShared(
                pSMEM, nTable, (void **)&gpBIMCPLLConfig, sizeof(gpBIMCPLLConfig[0])) == FALSE)
        {
          set_page_select(0);
          return FALSE;
        }
        nPLLConfigCount = pBIMCTableHeaders[nTable].nNumNodes;
        break;

      case CLOCK_BIMC_DDR:
        pClock = pTargCtxt->BIMCResource.sClockRes.apClocks[0];
        if( Clock_BIMCCopySingleTableFromShared(
                pSMEM, nTable, (void**)&gpDDRClockConfig, sizeof(gpDDRClockConfig[0])) == FALSE)
        {
          set_page_select(0);
          return FALSE;
        }
        if( (pClock == NULL) ||
            (pClock->pDomain == NULL) ) return FALSE;
        pClock->pDomain->pBSPConfig = gpDDRClockConfig;
        pClock->pDomain->pActiveMuxConfig = 
             &pClock->pDomain->pBSPConfig[pBIMCConfigInfo->nActiveLevel];
        
        Clock_VoltageRequest (pDrvCtxt, &pClock->pDomain->eVRegLevel,
             pClock->pDomain->pActiveMuxConfig->eVRegLevel, false);
        nSrcIdx = pDrvCtxt->anSourceIndex[pClock->pDomain->pActiveMuxConfig->HALConfig.eSource];
        pClock->pDomain->pSource = &pDrvCtxt->aSources[nSrcIdx];
        
        break;

      default: /* Unrecognized SMEM table */
      {
        set_page_select(0);
        return FALSE;
      }
    }
  }

  /* Fix the PLL reference pointers, now that all tables are filled. */
  if((gpBIMCPLLConfig != NULL) && (gpDDRClockConfig != NULL) && (nPLLConfigCount > 0))
  {
    ClockMuxConfigType *pClockMuxCfg;

    for(pClockMuxCfg = gpDDRClockConfig; (pClockMuxCfg->nFreqHz != 0); pClockMuxCfg++)
    {
      if((pClockMuxCfg->HALConfig.eSource == HAL_CLK_SOURCE_GPLL2) ||
         (pClockMuxCfg->HALConfig.eSource == HAL_CLK_SOURCE_GPLL3))
      {
        nPLLCfgIdx = HAL_CLK_BIMC_N2D_GPLL23_IDX(pClockMuxCfg->HALConfig.n2D);

        /* Enforce valid GPLL23 config index. */
        if(nPLLCfgIdx >= nPLLConfigCount)
        {
          set_page_select(0);
          return FALSE;
        }
        /*
         * Set the source configuration using the HALConfig.nN for any source listed
         * as GPLL2 or GPLL3.  Those are the reprogrammable dedicated BIMC PLLs.
         */
        pClockMuxCfg->pSourceConfig = &gpBIMCPLLConfig[nPLLCfgIdx];
      }
      else
      {
        pClockMuxCfg->pSourceConfig = NULL;
      }
    }
  }

  set_page_select(0);

  return TRUE;
}
