/*
==============================================================================

FILE:         HALclkQ6.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   Q6 clock.

   List of clock domains:


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/sdm660/cdsp/src/turing/HALclkQ6.c#1 $

==============================================================================
            Copyright (c) 2016 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/


#include <HALhwio.h>

#include "HALclkInternal.h"
#include "HALclkTest.h"
#include "HALclkGeneric.h"
#include "HALclkHWIO.h"


//Wait-time for TRS to become low
#define HAL_CLK_TRS_TIMEOUT 200

/*============================================================================

             DEFINITIONS AND DECLARATIONS FOR MODULE

=============================================================================*/


/* ============================================================================
**    Prototypes
** ==========================================================================*/

static uint32  HAL_clk_Q6SourceMapToHW       ( const HAL_clk_ClockMuxConfigType *pmConfig );
static void    HAL_clk_Q6CoreClkEnable       ( HAL_clk_ClockDescType  *pmClockDesc );
static void    HAL_clk_Q6CoreClkDisable      ( HAL_clk_ClockDescType  *pmClockDesc );
static boolean HAL_clk_Q6CoreClkIsEnabled    ( HAL_clk_ClockDescType  *pmClockDesc );
static boolean HAL_clk_Q6CoreClkIsOn         ( HAL_clk_ClockDescType  *pmClockDesc );
static void    HAL_clk_Q6CoreClkConfig       ( HAL_clk_ClockDescType  *pmClockDesc, HAL_clk_ClockConfigType eConfig );
static void    HAL_clk_Q6CoreConfigMux       ( HAL_clk_ClockDomainDescType *pmClockDomainDesc, const HAL_clk_ClockMuxConfigType *pmConfig );
static void    HAL_clk_Q6CoreDetectMuxConfig ( HAL_clk_ClockDomainDescType *pmClockDomainDesc, HAL_clk_ClockMuxConfigType *pmConfig );

/* ============================================================================
**    Externs
** ==========================================================================*/



/* ============================================================================
**    Data
** ==========================================================================*/

/*
 * HAL_clk_mQ6ClockDomainControl
 *
 * Functions for controlling Q6 clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mQ6ClockDomainControl =
{
   /* .ConfigMux          = */ HAL_clk_Q6CoreConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_Q6CoreDetectMuxConfig,
   /* .pmSourceMapping    = */ NULL
};
                                 
   
/*
 * HAL_clk_mQ6ClockControl
 *
 * Functions for controlling Q6 clock functions.
 */
HAL_clk_ClockControlType HAL_clk_mQ6ClockControl =
{
  /* .Enable           = */ HAL_clk_Q6CoreClkEnable,
  /* .Disable          = */ HAL_clk_Q6CoreClkDisable,
  /* .IsEnabled        = */ HAL_clk_Q6CoreClkIsEnabled,
  /* .IsOn             = */ HAL_clk_Q6CoreClkIsOn,
  /* .Reset            = */ NULL,
  /* .IsReset          = */ NULL,
  /* .Config           = */ HAL_clk_Q6CoreClkConfig,
  /* .DetectConfig     = */ NULL,
  /* .ConfigDivider    = */ NULL,
  /* .DetectDivider    = */ NULL,
  /* .ConfigFootswitch = */ NULL,
};   


/*                           
 *  HAL_clk_mTURINGQ6SSRCGIMAGEClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mTURINGQ6SSRCGIMAGEClkDomainClks[] =
{
  {
    /* .szClockName      = */ "turing_q6core",
    /* .mRegisters       = */ { 0, 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mQ6ClockControl,
    /* .nTestClock       = */ HAL_CLK_TURING_TEST_CLK_Q6
  },
};


/*
 * HAL_clk_mTURINGQ6SSRCGIMAGEClkDomain
 *
 * TURINGQ6SSRCGIMAGE clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mTURINGQ6SSRCGIMAGEClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(TURING_QDSP6SS_CORE_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mTURINGQ6SSRCGIMAGEClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mTURINGQ6SSRCGIMAGEClkDomainClks)/sizeof(HAL_clk_mTURINGQ6SSRCGIMAGEClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mQ6ClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

/*============================================================================

               FUNCTION DEFINITIONS FOR MODULE

============================================================================*/

static uint32 HAL_clk_Q6SourceMapToHW 
( 
  const HAL_clk_ClockMuxConfigType *pmConfig 
)
{
  /*
   * Determine the source selection value.  The Q6 RCG source selection will always
   * be the same when running on any PLL.  Selections are made through the GFMUX.
   */

  if(pmConfig->eSource == HAL_CLK_SOURCE_XO)
  {
    return 0;
  }
  return 1;

}


/* ===========================================================================
**  HAL_clk_Q6CoreClkEnable
**
** ======================================================================== */

static void HAL_clk_Q6CoreClkEnable 
( 
  HAL_clk_ClockDescType  *pmClockDesc 
)
{
  //HWIO_OUTF(LPASS_Q6CORE_CMD_RCGR, ROOT_EN, 1);

}  /* END HAL_clk_Q6CoreClkEnable */


/* ===========================================================================
**  HAL_clk_Q6CoreClkDisable
**
** ======================================================================== */

static void HAL_clk_Q6CoreClkDisable 
( 
  HAL_clk_ClockDescType  *pmClockDesc
)
{
  //HWIO_OUTF(LPASS_Q6CORE_CMD_RCGR, ROOT_EN, 0);

}  /* END HAL_clk_Q6CoreClkDisable */


/* ===========================================================================
**  HAL_clk_Q6CoreClkIsEnabled
**
** ======================================================================== */

static boolean HAL_clk_Q6CoreClkIsEnabled 
( 
  HAL_clk_ClockDescType  *pmClockDesc 
)
{
  return TRUE;

}  /* END HAL_clk_Q6CoreClkIsEnabled */


/* ===========================================================================
**  HAL_clk_Q6CoreClkIsOn
**
** ======================================================================== */

static boolean HAL_clk_Q6CoreClkIsOn
( 
  HAL_clk_ClockDescType  *pmClockDesc
)
{
  return TRUE;

}  /* END HAL_clk_Q6CoreClkIsOn */


/* ===========================================================================
**  HAL_clk_Q6CoreClkConfig
**
** ======================================================================== */

static void HAL_clk_Q6CoreClkConfig
( 
  HAL_clk_ClockDescType   *pmClockDesc, 
  HAL_clk_ClockConfigType eConfig 
)
{
  uint32 nSrcSel;
  
  switch (eConfig)
  {
    case HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCA:
      nSrcSel = 0x0;
      break;

    case HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCB:
      nSrcSel = 0x1;
      break;

    case HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCC:
      nSrcSel = 0x2;
      break;

    case HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCD:
      nSrcSel = 0x3;
      break;

    default:
      return;
  }

  HWIO_OUTF(TURING_QDSP6SS_GFMUX_CTL, CLK_SRC_SEL, nSrcSel);

}  /* END HAL_clk_Q6CoreClkConfig */


/* ===========================================================================
**  HAL_clk_Q6CoreConfigMux
**
** ======================================================================== */

static void  HAL_clk_Q6CoreConfigMux
( 
  HAL_clk_ClockDomainDescType      *pmClockDomainDesc, 
  const HAL_clk_ClockMuxConfigType *pmConfig 
)
{
  uint32 nCmdCGRAddr, nCmdCGRVal, nCfgCGRAddr, nCfgCGRVal;
  uint32 nSource;

  /*
   * Sanity check
   */
  if((pmClockDomainDesc           == NULL) || 
     (pmClockDomainDesc->nCGRAddr == 0   ))
  {
    return;
  }

  /*
   * Get current CMD and CFG register values
   */
  nCmdCGRAddr = pmClockDomainDesc->nCGRAddr;
  nCmdCGRVal  = inpdw(nCmdCGRAddr);
  nCfgCGRAddr = pmClockDomainDesc->nCGRAddr + HAL_CLK_CFG_REG_OFFSET;
  nCfgCGRVal  = inpdw(nCfgCGRAddr);

  /*
   * TODO:  SPM_CTL override functionality (if applicable).
   */


  /*
   * Clear the fields
   */
  nCfgCGRVal &= ~(HAL_CLK_CFG_CGR_SRC_SEL_FMSK |
                  HAL_CLK_CFG_CGR_SRC_DIV_FMSK);

  /*
   * Program the source and divider values.
   */
  nSource = HAL_clk_Q6SourceMapToHW(pmConfig);

  nCfgCGRVal |= ((nSource << HAL_CLK_CFG_CGR_SRC_SEL_SHFT) 
                   & HAL_CLK_CFG_CGR_SRC_SEL_FMSK);

  /*
   * Set the divider
   */
  nCfgCGRVal |= ((HALF_DIVIDER(pmConfig) << HAL_CLK_CFG_CGR_SRC_DIV_SHFT) 
                & HAL_CLK_CFG_CGR_SRC_DIV_FMSK);

  /*
   * Write the final CFG register value
   */
  outpdw(nCfgCGRAddr, nCfgCGRVal);

  /*
   * Trigger the update
   */
  nCmdCGRVal |= HAL_CLK_CMD_CFG_UPDATE_FMSK;
  outpdw(nCmdCGRAddr, nCmdCGRVal);

  /*
   * Wait until update finishes
   */
  while(inpdw(nCmdCGRAddr) & HAL_CLK_CMD_CFG_UPDATE_FMSK);

}  /* END HAL_clk_Q6CoreConfigMux */


/* ===========================================================================
**  HAL_clk_Q6CoreDetectMuxConfig
**
** ======================================================================== */

static void  HAL_clk_Q6CoreDetectMuxConfig 
( 
  HAL_clk_ClockDomainDescType *pmClockDomainDesc, 
  HAL_clk_ClockMuxConfigType  *pmConfig 
)
{
  uint32 nCfgCGRAddr, nCfgCGRVal, nSource;

  pmConfig->eSource = HAL_CLK_SOURCE_NULL;
  pmConfig->nDiv2x  = 0;
  pmConfig->n2D     = 0;
  pmConfig->nM      = 0;
  pmConfig->nN      = 0;

  /*
   * Sanity check
   */
  if((pmClockDomainDesc           == NULL) || 
     (pmClockDomainDesc->nCGRAddr == 0   ))
  {
    return;
  }

  /*
   * Get current CFG register value
   */
  nCfgCGRAddr = pmClockDomainDesc->nCGRAddr + HAL_CLK_CFG_REG_OFFSET;
  nCfgCGRVal  = inpdw(nCfgCGRAddr);

  /*
   * Get the source and divider values
   */
  pmConfig->nDiv2x = 
    ((nCfgCGRVal & HAL_CLK_CFG_CGR_SRC_DIV_FMSK) >> HAL_CLK_CFG_CGR_SRC_DIV_SHFT) + 1;

  nSource = (nCfgCGRVal & HAL_CLK_CFG_CGR_SRC_SEL_FMSK) >> HAL_CLK_CFG_CGR_SRC_SEL_SHFT;

  /*
   * The RCG of the Q6 will always select the primary PLL (QDSP6SS_PLL).  The GFMUX will
   * select the LPAAUDIO_PLL when necessary to source the Q6 as an intermediate frequency.
   */
  switch(nSource)
  {
    case 0:
      pmConfig->eSource = HAL_CLK_SOURCE_XO;
      break;

    default:
      pmConfig->eSource = HAL_CLK_SOURCE_TURINGPLL1;
      break;
  }

}  /* END HAL_clk_Q6CoreDetectMuxConfig */


/* ===========================================================================
**  HAL_clk_EnableCXiPeakLMVote
**
** ======================================================================== */

boolean  HAL_clk_EnableCXiPeakLMVote(void)
{
  uint32  nFSetVal;
  boolean bResult;
  
  /* 
   * Check if this feature is enabled
   */
  if (HWIO_INF(TCSR_CXIP_LM_VOTE_FEATURE_ENABLE,VOTE_FEATURE_ENABLE))
  {
	/* 
	 * Vote from CDSP Client if frequency is switching to Turbo(Set F_SET as 1)
	 */
	nFSetVal = HWIO_IN(TCSR_CXIP_LM_FNT_STATUS) | 
	              HWIO_TCSR_CXIP_LM_FNT_SET_F_SET_BMSK ;
	HWIO_OUT(TCSR_CXIP_LM_FNT_SET,nFSetVal);
	  
	/*
	 * Propagation delay
	 */
	HAL_clk_BusyWait(1);
	  
	/*
	 * Check if F_STATUS is high in STATUS register
	 */
	if(0 == (HWIO_INF(TCSR_CXIP_LM_FNT_STATUS,
                   F_STATUS)))
    {
      return FALSE;
    }
	  
	/*
	 * Pre-Configuration Delay
	 */
	HAL_clk_BusyWait(1);
	  
	/*
	 * Poll for TRS
	 */
	bResult =
	  HAL_clk_ValidateRegClearTimeout(
        HWIO_TCSR_CXIP_LM_TRS_ADDR,
        HWIO_FMSK(TCSR_CXIP_LM_TRS, TRS),
        HAL_CLK_TRS_TIMEOUT);
	if(!bResult)
	{
	  return FALSE;
	}
  }	
  
  return TRUE;

}  /* END HAL_clk_EnableCXiPeakLMVote */


/* ===========================================================================
**  HAL_clk_DisableCXiPeakLMVote
**
** ======================================================================== */

boolean  HAL_clk_DisableCXiPeakLMVote(void)
{
  uint32 nFnTClearVal;
   
  /*	
   * CX-iPeak Un-vote
   */
  if(HWIO_INF(TCSR_CXIP_LM_VOTE_FEATURE_ENABLE,VOTE_FEATURE_ENABLE))
  {
	/*
	 * Set F_CLEAR and T_CLEAR as 1
	 */
	nFnTClearVal = HWIO_IN(TCSR_CXIP_LM_FNT_STATUS) | 
	               HWIO_TCSR_CXIP_LM_FNT_CLEAR_F_CLEAR_BMSK |  
	                HWIO_TCSR_CXIP_LM_FNT_CLEAR_T_CLEAR_BMSK;
	HWIO_OUT(TCSR_CXIP_LM_FNT_CLEAR,nFnTClearVal);
	  
	/*
	 * Propagation delay
	 */
	HAL_clk_BusyWait(1);
	  
	/*
	 * Check if F_STATUS and T_STATUS are 0 in STATUS register
	 */
	if(1 == (HWIO_INF(TCSR_CXIP_LM_FNT_STATUS,
                 F_STATUS) | HWIO_INF(TCSR_CXIP_LM_FNT_STATUS,
                 T_STATUS)))
    {
      return FALSE;
    }
  }
  
  return TRUE;
  
} /* END HAL_clk_DisableCXiPeakLMVote */
