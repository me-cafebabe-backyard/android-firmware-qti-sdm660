/*
==============================================================================

FILE:         HALclkBrammoPLL.c

DESCRIPTION:
  This file contains the clock HAL code for the Brammo PLL control.
  These PLLs are of the Brammo PLL variety.

==============================================================================

                             Edit History


when       who     what, where, why
--------   ---     -----------------------------------------------------------
10/14/14   sr      Ported from Prius PLL.
05/30/13   frv     Created

==============================================================================
   Copyright (c) 2013-2015 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/

#include "HALhwio.h"
#include "HALclkBrammoPLL.h"
#include "HALclkGenericPLL.h"


/*============================================================================

             DEFINITIONS AND DECLARATIONS FOR MODULE

=============================================================================*/


/* ============================================================================
**    Definitions
** ==========================================================================*/


/*
 * HAL_CLK_PLL_MODE_*
 *
 * Definitions for configuring the PLLn_MODE register.
 */
#define HAL_CLK_PLL_MODE_ACTIVE  \
  (HWIO_FMSK(PLL_MODE, PLL_OUTCTRL)  | \
   HWIO_FMSK(PLL_MODE, PLL_BYPASSNL) | \
   HWIO_FMSK(PLL_MODE, PLL_RESET_N))

/*
 * Definitions for configuring the PLL in FSM Mode
 */
#define HAL_CLK_PLL_BIAS_COUNT_VAL   (0x1 << HWIO_SHFT(PLL_MODE, PLL_BIAS_COUNT))
#define HAL_CLK_PLL_LOCK_COUNT_VAL   (0x0 << HWIO_SHFT(PLL_MODE, PLL_LOCK_COUNT))

/*
 * HAL_CLK_PLL_INIT_TIME_US
 *
 * Init time in microseconds after de-asserting PLL reset (normal mode).
 */
#define HAL_CLK_PLL_INIT_TIME_US 5


/*
 * HAL_CLK_LOCK_TIMEOUT_US
 *
 * Timeout in usec for PLL_LOCK_DET to get set.
 */
#define HAL_CLK_LOCK_TIMEOUT_US 200

/*
 * HAL_CLK_UPDATE_TIMEOUT_US
 *
 * Timeout in usec for PLL_UPDATE to get set.
 */
#define HAL_CLK_UPDATE_TIMEOUT_US 200


/* ============================================================================
**    Data Declarations
** ==========================================================================*/

/*
 * HAL_clk_BrammoPLLControl
 *
 * Control function array for the Brammo PLLs.
 */
HAL_clk_SourceControlType HAL_clk_BrammoPLLControl =
{
  /* .Enable          = */ HAL_clk_BrammoPLLEnable,
  /* .Disable         = */ HAL_clk_BrammoPLLDisable,
  /* .IsEnabled       = */ HAL_clk_BrammoPLLIsEnabled,
  /* .Config          = */ HAL_clk_BrammoPLLConfig,
  /* .ConfigPLL       = */ HAL_clk_BrammoPLLConfigPLL,
  /* .DetectPLLConfig = */ HAL_clk_BrammoPLLDetectPLLConfig,
  /* .EnableVote      = */ HAL_clk_BrammoPLLEnableVote,
  /* .DisableVote     = */ HAL_clk_BrammoPLLDisableVote,
  /* .IsVoteEnabled   = */ HAL_clk_BrammoPLLIsVoteEnabled,
};


/*============================================================================

               FUNCTION DEFINITIONS FOR MODULE

============================================================================*/


/* ===========================================================================
**  HAL_clk_BrammoPLLEnableVote
**
** ======================================================================== */

static boolean HAL_clk_BrammoPLLEnableVote
(
  HAL_clk_SourceDescType *pSource
)
{
  HAL_clk_PLLContextType *pCtxt;
  uint32                  nVal;
  boolean                 bResult;

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Set the appropriate bit.
   */
  nVal = inpdw(pCtxt->VoterRegister.nAddr) | pCtxt->VoterRegister.nMask;
  outpdw(pCtxt->VoterRegister.nAddr, nVal);

  /*
   * Wait for the PLL to go active within the timeout period.
   */
  bResult =
    HAL_clk_ValidateRegSetTimeout(
      HAL_CLK_PLL_HWIO_ADDR(PLL_MODE, pCtxt),
      HWIO_FMSK(PLL_MODE, PLL_ACTIVE_FLAG),
      HAL_CLK_LOCK_TIMEOUT_US);

  if (!bResult)
  {
    ERR_FATAL("HAL_clk_BrammoPLLEnableVote Activate Failure", 0, 0, 0);
  }

  return bResult;

} /* END HAL_clk_BrammoPLLEnableVote */


/* ===========================================================================
**  HAL_clk_BrammoPLLDisableVote
**
** ======================================================================== */

static void HAL_clk_BrammoPLLDisableVote
(
  HAL_clk_SourceDescType *pSource
)
{
  HAL_clk_PLLContextType *pCtxt;
  uint32                  nVal;

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Clear the appropriate bit.
   */
  nVal = inpdw(pCtxt->VoterRegister.nAddr) & ~pCtxt->VoterRegister.nMask;
  outpdw(pCtxt->VoterRegister.nAddr, nVal);

} /* END HAL_clk_BrammoPLLDisableVote */


/* ===========================================================================
**  HAL_clk_BrammoPLLIsVoteEnabled
**
** ======================================================================== */

static boolean HAL_clk_BrammoPLLIsVoteEnabled
(
  HAL_clk_SourceDescType *pSource
)
{
  HAL_clk_PLLContextType *pCtxt;

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Check the appropriate bit.
   */
  if (inpdw(pCtxt->VoterRegister.nAddr) & pCtxt->VoterRegister.nMask)
  {
    return TRUE;
  }

  return FALSE;

} /* END HAL_clk_BrammoPLLIsVoteEnabled */


/* ===========================================================================
**  HAL_clk_BrammoPLLEnable
**
**  PLL initial bringup.
**  When in the off state, the bias is off and draws no power.
**  This procedure results in calibration being performed.
**
**  Returns:
**    boolean - TRUE if successfully enabled. FALSE otherwise.
** ======================================================================== */

static boolean HAL_clk_BrammoPLLEnable
(
  HAL_clk_SourceDescType        *pSource,
  HAL_clk_SourceDisableModeType  eMode,
  void                          *pData
)
{
  uint32                  nModeVal;
  HAL_clk_PLLContextType *pCtxt;
  boolean                 bResult;

  /*
   * Check if PLL is already enabled and return
   */
  if (HAL_clk_BrammoPLLIsEnabled(pSource))
  {
    return TRUE;
  }

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Read current mode value.
   */
  nModeVal  = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pCtxt);

  /*
   * De-assert PLL bypass.
   * This latches L, Alpha, and AlphaU values.
   */
  nModeVal |= HWIO_FMSK(PLL_MODE, PLL_BYPASSNL);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

  /*
   * Wait for PLL init time
   */
  HAL_clk_BusyWait(HAL_CLK_PLL_INIT_TIME_US);

  /*
   * De-assert PLL reset.
   */
  nModeVal |= HWIO_FMSK(PLL_MODE, PLL_RESET_N);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

  /*
   * Wait for the PLL to lock within the timeout period.
   */
  bResult =
    HAL_clk_ValidateRegSetTimeout(
      HAL_CLK_PLL_HWIO_ADDR(PLL_MODE, pCtxt),
      HWIO_FMSK(PLL_MODE, PLL_LOCK_DET),
      HAL_CLK_LOCK_TIMEOUT_US);

  /*
   * Return immediately if the lock failed.
   */
  if (!bResult)
  {
    ERR_FATAL("HAL_clk_BrammoPLLEnable Lock Failure", 0, 0, 0);
    return FALSE;
  }

  /*
   * Put the PLL in active mode
   */
  nModeVal |= HWIO_FMSK(PLL_MODE, PLL_OUTCTRL);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

  return TRUE;

} /* END HAL_clk_BrammoPLLEnable */


/* ===========================================================================
**  HAL_clk_BrammoPLLDisable
**
**  PLL shutdown.
**  When in the off state, the bias is off and draws no power.
**  This procedure results in calibration being required upon the next enable.
**
** ======================================================================== */

static void HAL_clk_BrammoPLLDisable
(
  HAL_clk_SourceDescType        *pSource,
  HAL_clk_SourceDisableModeType  eMode,
  void                          *pData
)
{
  uint32                  nModeVal;
  HAL_clk_PLLContextType *pCtxt;

  /*
   * The Brammo PLL's only support full enable/disable mode.
   */
  if (eMode != HAL_CLK_SOURCE_DISABLE_MODE_NORMAL)
  {
    ERR_FATAL("HAL_clk_BrammoPLLDisable Invalid Parameter", 0, 0, 0);
    return;
  }

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Read current mode value.
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pCtxt);

  /*
   * De-assert the OUTCTL field.
   */
  nModeVal &= ~HWIO_FMSK(PLL_MODE, PLL_OUTCTRL);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

  /*
   * Wait 2 ticks of the output main clock.
   */
  HAL_clk_BusyWait(1);

  /*
   * Put the PLL in reset mode
   */
  nModeVal &= ~(HWIO_FMSK(PLL_MODE, PLL_RESET_N) |
                HWIO_FMSK(PLL_MODE, PLL_BYPASSNL));
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

} /* END HAL_clk_BrammoPLLDisable */


/* ===========================================================================
**  HAL_clk_BrammoPLLIsEnabled
**
** ======================================================================== */

static boolean HAL_clk_BrammoPLLIsEnabled
(
  HAL_clk_SourceDescType *pSource
)
{
  uint32                  nModeVal;
  HAL_clk_PLLContextType *pCtxt;

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Read current mode value.
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pCtxt);

  /*
   * Check whether the PLL is enabled.
   */
  return ((nModeVal & HAL_CLK_PLL_MODE_ACTIVE) == HAL_CLK_PLL_MODE_ACTIVE);

} /* END HAL_clk_BrammoPLLIsEnabled */


/* ===========================================================================
**  HAL_clk_BrammoPLLConfig
**
** ======================================================================== */

static void HAL_clk_BrammoPLLConfig
(
  HAL_clk_SourceDescType   *pSource,
  HAL_clk_SourceConfigType  eConfig
)
{
  HAL_clk_PLLContextType *pCtxt;

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Take action.
   */
  switch (eConfig)
  {
    case HAL_CLK_CONFIG_PLL_FSM_MODE_ENABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_MODE, pCtxt, PLL_VOTE_FSM_ENA, 1);
      break;

    case HAL_CLK_CONFIG_PLL_FSM_MODE_DISABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_MODE, pCtxt, PLL_VOTE_FSM_ENA, 0);
      break;

    case HAL_CLK_CONFIG_PLL_AUX_OUTPUT_DISABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pCtxt, PLLOUT_LV_AUX, 0);
      break;

    case HAL_CLK_CONFIG_PLL_AUX_OUTPUT_ENABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pCtxt, PLLOUT_LV_AUX, 1);
      break;

    case HAL_CLK_CONFIG_PLL_AUX2_OUTPUT_DISABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pCtxt, PLLOUT_LV_AUX2, 0);
      break;

    case HAL_CLK_CONFIG_PLL_AUX2_OUTPUT_ENABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pCtxt, PLLOUT_LV_AUX2, 1);
      break;

    case HAL_CLK_CONFIG_PLL_EARLY_OUTPUT_ENABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pCtxt, PLLOUT_LV_EARLY, 1);
      break;

    case HAL_CLK_CONFIG_PLL_EARLY_OUTPUT_DISABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pCtxt, PLLOUT_LV_EARLY, 0);
      break;

    case HAL_CLK_CONFIG_PLL_MAIN_OUTPUT_ENABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pCtxt, PLLOUT_LV_MAIN, 1);
      break;

    case HAL_CLK_CONFIG_PLL_MAIN_OUTPUT_DISABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pCtxt, PLLOUT_LV_MAIN, 0);
      break;
    default:
      ERR_FATAL("HAL_clk_PriusPLLEnableFromSaved Invalid Parameter", 0, 0, 0);
      break;
  }

} /* END HAL_clk_BrammoPLLConfig */


/* ===========================================================================
**  HAL_clk_BrammoPLLConfigPLL
**
**  Returns:
**    boolean - TRUE if successfully configured. FALSE otherwise.
** ======================================================================== */

static boolean HAL_clk_BrammoPLLConfigPLL
(
  HAL_clk_SourceDescType      *pSource,
  const HAL_clk_PLLConfigType *pConfig,
  HAL_clk_SourceConfigMode     eMode
)
{
  uint32  nModeVal, nUserVal;
  uint32  nPLLInFSMMode = 0;
  boolean bPLLEnabled = FALSE;
  HAL_clk_PLLContextType *pCtxt;

  /*
   * Program the appropriate config sequence.
   */
  if (eMode != HAL_CLK_SOURCE_CONFIG_MODE_NORMAL)
  {
    ERR_FATAL("HAL_clk_BrammoPLLConfigPLL Invalid Parameter", 0, 0, 0);
    return FALSE;
  }

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Check PLL mode.
   */
  nPLLInFSMMode = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pCtxt) &
    HWIO_FMSK(PLL_MODE, PLL_VOTE_FSM_ENA);
  bPLLEnabled = HAL_clk_BrammoPLLIsEnabled(pSource);

  /*
   * Disable the PLL.
   */
  if (bPLLEnabled)
  {
    HAL_clk_BrammoPLLDisable(pSource, HAL_CLK_SOURCE_DISABLE_MODE_NORMAL, NULL);
  }

  /*
   * Read the PLLx_Mode value
   */
  nModeVal  = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pCtxt);

  /*
   * Disable FSM Mode
   */
  if (nPLLInFSMMode != 0)
  {
    nModeVal &= ~HWIO_FMSK(PLL_MODE, PLL_VOTE_FSM_ENA);
    HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);
  }

  /*
   * Program L/Alpha/AlphaU values.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_L_VAL, pCtxt, pConfig->nL);
  HAL_CLK_PLL_HWIO_OUT(PLL_ALPHA_VAL, pCtxt, pConfig->nAlpha);
  HAL_CLK_PLL_HWIO_OUT(PLL_ALPHA_U_VAL, pCtxt, pConfig->nAlphaU);

  /*
   * Get the CONFIG value and clear out fields we will configure.
   */
  nUserVal  =  HAL_CLK_PLL_HWIO_IN(PLL_USER_CTL, pCtxt);
  nUserVal &= ~(HWIO_FMSK(PLL_USER_CTL, ALPHA_EN) |
                HWIO_FMSK(PLL_USER_CTL, INCLK_SEL) |
                HWIO_FMSK(PLL_USER_CTL, POSTDIV_CTL));

  /*
   * Program the inclk_sel value (div-1, div-2, mul-2 on rising edge, or mul-2 on falling edge).
   */
  if (pConfig->nPreDiv <= 4 && pConfig->nPreDiv > 0)
  {
    nUserVal |= HWIO_FVAL(PLL_USER_CTL, INCLK_SEL, (pConfig->nPreDiv - 1));
  }

  /*
   * Program the post-div value (div-1, 2, and 4 are supported)
   */
  if ((pConfig->nPostDiv == 1) || (pConfig->nPostDiv == 2) || (pConfig->nPostDiv == 4))
  {
    nUserVal |= HWIO_FVAL(PLL_USER_CTL, POSTDIV_CTL, (pConfig->nPostDiv - 1));
  }

  /*
   *  Check fractional output or integer output.
   */
  if ((pConfig->nAlpha != 0) || (pConfig->nAlphaU != 0))
  {
    nUserVal |= HWIO_FMSK(PLL_USER_CTL, ALPHA_EN);
  }

  /*
   * Finally program the USER_CTL register.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL, pCtxt, nUserVal);

  /*
   * If there is an address for a voting register, then the PLL is in
   * FSM voteable mode. In this case, the enable sequence is handled in
   * hardware, guided by the BIAS and LOCK counts.
   */
  if (nPLLInFSMMode)
  {
    /*
     * Put the FSM in reset.
     */
    nModeVal |= HWIO_FMSK(PLL_MODE, PLL_VOTE_FSM_RESET);
    HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

    /*
     * Program the FSM portion of the mode register.
     */
    nModeVal &= ~HWIO_FMSK(PLL_MODE, PLL_BIAS_COUNT);
    nModeVal &= ~HWIO_FMSK(PLL_MODE, PLL_LOCK_COUNT);

    nModeVal |= HAL_CLK_PLL_BIAS_COUNT_VAL;
    nModeVal |= HAL_CLK_PLL_LOCK_COUNT_VAL;

    nModeVal |= HWIO_FMSK(PLL_MODE, PLL_VOTE_FSM_ENA);
    /*
     * Finally program the Mode register.
     */
    HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

    /*
     * Take the FSM out of reset.
     */
    nModeVal &= ~HWIO_FMSK(PLL_MODE, PLL_VOTE_FSM_RESET);
    HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);
  }

  /*
   * Enable the PLL if it was on before and not in FSM mode (in FSM
   * mode this function is not used).
   */
  if (bPLLEnabled && nPLLInFSMMode == 0)
  {
    HAL_clk_BrammoPLLEnable(pSource, HAL_CLK_SOURCE_DISABLE_MODE_NORMAL, NULL);
  }

  return TRUE;

} /* END HAL_clk_BrammoPLLConfigPLL */


/* ===========================================================================
**  HAL_clk_BrammoPLLDetectPLLConfig
**
** ======================================================================== */

static void HAL_clk_BrammoPLLDetectPLLConfig
(
  HAL_clk_SourceDescType *pSource,
  HAL_clk_PLLConfigType  *pConfig
)
{
  uint32 nConfigVal;
  HAL_clk_PLLContextType *pCtxt;

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Clear all config values not modified in this function.
   */
  pConfig->nM = 0;
  pConfig->nN = 0;
  pConfig->nVCOMultiplier = 0;

  /*
   * Read current L, Alpha, and AlphaU values.
   */
  pConfig->nL = HAL_CLK_PLL_HWIO_IN(PLL_L_VAL, pCtxt);
  pConfig->nAlpha = HAL_CLK_PLL_HWIO_IN(PLL_ALPHA_VAL, pCtxt);
  pConfig->nAlphaU = HAL_CLK_PLL_HWIO_IN(PLL_ALPHA_U_VAL, pCtxt);

  /*
   * Determine the oscillator source.
   */
  pConfig->eSource = HAL_CLK_SOURCE_XO;

  /*
   * Get the pre and post dividers.
   */
  nConfigVal = HAL_CLK_PLL_HWIO_IN(PLL_USER_CTL, pCtxt);
  pConfig->nPreDiv = ((nConfigVal & HWIO_FMSK(PLL_USER_CTL, INCLK_SEL))
                   >> HWIO_SHFT(PLL_USER_CTL, INCLK_SEL)) + 1;
  pConfig->nPostDiv = ((nConfigVal & HWIO_FMSK(PLL_USER_CTL, POSTDIV_CTL))
                    >> HWIO_SHFT(PLL_USER_CTL, POSTDIV_CTL)) + 1;

  /*
   * Get the current state of the FSM Voting Mode.
   */
  pConfig->bFsmMode = (boolean)HAL_CLK_PLL_HWIO_INF(PLL_MODE, pCtxt, PLL_VOTE_FSM_ENA);

} /* END HAL_clk_BrammoPLLDetectPLLConfig */

