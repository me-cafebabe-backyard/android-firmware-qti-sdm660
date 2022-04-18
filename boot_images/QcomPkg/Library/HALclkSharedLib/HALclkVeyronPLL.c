/*
==============================================================================

FILE:         HALclkVeyronPLL.c

DESCRIPTION:
  This file contains the clock HAL code for the Veyron PLL control.
  These PLLs are of the Veyron PLL variety.

==============================================================================

                             Edit History


when       who     what, where, why
--------   ---     -----------------------------------------------------------
06/07/14   sr      Created

==============================================================================
    Copyright (c) 2014-2015 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/

#include "HALhwio.h"
#include "HALclkVeyronPLL.h"
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
 * HAL_CLK_PLL_WARMUP_TIME_US
 *
 * Warm-up time in microseconds after turning on the PLL.
 */
#define HAL_CLK_PLL_WARMUP_TIME_US 50

/*
 * HAL_CLK_LOCK_TIMEOUT_US
 *
 * Timeout in usec for PLL_LOCK_DET to get set.
 */
#define HAL_CLK_LOCK_TIMEOUT_US 200


/* ============================================================================
**    Data Declarations
** ==========================================================================*/

/*
 * HAL_clk_VeyronPLLControl
 *
 * Control function array for the Veyron PLLs.
 */
HAL_clk_SourceControlType HAL_clk_VeyronPLLControl =
{
  /* .Enable          = */ HAL_clk_VeyronPLLEnable,
  /* .Disable         = */ HAL_clk_VeyronPLLDisable,
  /* .IsEnabled       = */ HAL_clk_VeyronPLLIsEnabled,
  /* .Config          = */ HAL_clk_VeyronPLLConfig,
  /* .ConfigPLL       = */ HAL_clk_VeyronPLLConfigPLL,
  /* .DetectPLLConfig = */ HAL_clk_VeyronPLLDetectPLLConfig,
  /* .EnableVote      = */ NULL,
  /* .DisableVote     = */ NULL,
  /* .IsVoteEnabled   = */ NULL,
};


/*============================================================================

               FUNCTION DEFINITIONS FOR MODULE

============================================================================*/


/* ===========================================================================
**  HAL_clk_VeyronPLLEnable
**
** ======================================================================== */

static boolean HAL_clk_VeyronPLLEnable
(
  HAL_clk_SourceDescType        *pSource,
  HAL_clk_SourceDisableModeType  eMode,
  void                          *pData
)
{
  uint32                  nModeVal, nTestVal;
  HAL_clk_PLLContextType *pCtxt;
  boolean                 bResult;

  /*
   * Check if PLL is already enabled and return
   */
  if (HAL_clk_VeyronPLLIsEnabled(pSource))
  {
    return TRUE;
  }

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Read current mode and test values.
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pCtxt);
  nTestVal = HAL_CLK_PLL_HWIO_IN(PLL_TEST_CTL_LO, pCtxt);

  /*
   * Assert the PLL CFA mode.
   */
  nTestVal |= HWIO_FMSK(PLL_TEST_CTL_LO, STAY_IN_CFA);
  HAL_CLK_PLL_HWIO_OUT(PLL_TEST_CTL_LO, pCtxt, nTestVal);

  /*
   * De-assert PLL bypass.
   * This latches L and Alpha values.
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
   * Wait for PLL init time
   */
  HAL_clk_BusyWait(HAL_CLK_PLL_INIT_TIME_US);

  /*
   * De-assert the PLL CFA mode.
   */
  nTestVal &= ~HWIO_FMSK(PLL_TEST_CTL_LO, STAY_IN_CFA);
  HAL_CLK_PLL_HWIO_OUT(PLL_TEST_CTL_LO, pCtxt, nTestVal);

  /*
   * Wait for the PLL warm-up time.
   */
  HAL_clk_BusyWait(HAL_CLK_PLL_WARMUP_TIME_US);

  /*
   * Wait for the PLL to lock within the timeout period.
   */
  bResult =
    HAL_clk_ValidateRegSetTimeout(
      HAL_CLK_PLL_HWIO_ADDR(PLL_MODE, pCtxt),
      HWIO_FMSK(PLL_MODE, PLL_LOCK_DET),
      HAL_CLK_LOCK_TIMEOUT_US);

  /*
   * Return immediately if the lock detect failed.
   */
  if (!bResult)
  {
    ERR_FATAL("HAL_clk_VeyronPLLEnable Lock Failure", 0, 0, 0);
    return FALSE;
  }

  /*
   * Put the PLL in active mode
   */
  nModeVal |= HWIO_FMSK(PLL_MODE, PLL_OUTCTRL);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

  return TRUE;

} /* END HAL_clk_VeyronPLLEnable */


/* ===========================================================================
**  HAL_clk_VeyronPLLDisable
**
** ======================================================================== */

static void HAL_clk_VeyronPLLDisable
(
  HAL_clk_SourceDescType        *pSource,
  HAL_clk_SourceDisableModeType  eMode,
  void                          *pData
)
{
  uint32                  nModeVal;
  HAL_clk_PLLContextType *pCtxt;

  /*
   * The Veyron PLL's only support full enable/disable mode.
   */
  if (eMode != HAL_CLK_SOURCE_DISABLE_MODE_NORMAL)
  {
    ERR_FATAL("HAL_clk_VeyronPLLDisable Invalid Parameter", 0, 0, 0);
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
   * Put the PLL in reset mode
   */
  nModeVal &= ~(HWIO_FMSK(PLL_MODE, PLL_RESET_N) |
                HWIO_FMSK(PLL_MODE, PLL_BYPASSNL) |
                HWIO_FMSK(PLL_MODE, PLL_OUTCTRL));
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

} /* END HAL_clk_VeyronPLLDisable */


/* ===========================================================================
**  HAL_clk_VeyronPLLIsEnabled
**
** ======================================================================== */

static boolean HAL_clk_VeyronPLLIsEnabled
(
  HAL_clk_SourceDescType *pSource
)
{
  uint32 nModeVal;
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

} /* END HAL_clk_VeyronPLLIsEnabled */


/* ===========================================================================
**  HAL_clk_VeyronPLLConfig
**
** ======================================================================== */

static void HAL_clk_VeyronPLLConfig
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
    case HAL_CLK_CONFIG_PLL_AUX_OUTPUT_DISABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pCtxt, LVAUX_EN, 0);
      break;

    case HAL_CLK_CONFIG_PLL_AUX_OUTPUT_ENABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pCtxt, LVAUX_EN, 1);
      break;

    case HAL_CLK_CONFIG_PLL_AUX2_OUTPUT_DISABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pCtxt, LVAUX2_EN, 0);
      break;

    case HAL_CLK_CONFIG_PLL_AUX2_OUTPUT_ENABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pCtxt, LVAUX2_EN, 1);
      break;

    case HAL_CLK_CONFIG_PLL_EARLY_OUTPUT_ENABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pCtxt, LVEARLY_EN, 1);
      break;

    case HAL_CLK_CONFIG_PLL_EARLY_OUTPUT_DISABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pCtxt, LVEARLY_EN, 0);
      break;

    case HAL_CLK_CONFIG_PLL_MAIN_OUTPUT_ENABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pCtxt, LVMAIN_EN, 1);
      break;

    case HAL_CLK_CONFIG_PLL_MAIN_OUTPUT_DISABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pCtxt, LVMAIN_EN, 0);
      break;

    default:
      ERR_FATAL("HAL_clk_VeyronPLLConfig Invalid Parameter", 0, 0, 0);
      break;
  }

} /* END HAL_clk_VeyronPLLConfig */


/* ===========================================================================
**  HAL_clk_VeyronPLLConfigPLL
**
** ======================================================================== */

static boolean HAL_clk_VeyronPLLConfigPLL
(
  HAL_clk_SourceDescType      *pSource,
  const HAL_clk_PLLConfigType *pConfig,
  HAL_clk_SourceConfigMode     eMode
)
{
  uint32  nModeVal;
  uint32  nUserVal;
  boolean bPLLEnabled = FALSE;
  HAL_clk_PLLContextType *pCtxt;

  /*
   * The Veyron PLL's only support full config mode.
   */
  if (eMode != HAL_CLK_SOURCE_CONFIG_MODE_NORMAL)
  {
    ERR_FATAL("HAL_clk_VeyronPLLConfigPLL Invalid Parameter", 0, 0, 0);
    return FALSE;
  }

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Check PLL mode.
   */
  bPLLEnabled = HAL_clk_VeyronPLLIsEnabled(pSource);

  /*
   * Disable the PLL.
   */
  if (bPLLEnabled)
  {
    HAL_clk_VeyronPLLDisable(pSource, HAL_CLK_SOURCE_DISABLE_MODE_NORMAL, NULL);
  }

  /*
   * Read current mode value.
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pCtxt);

  /*
   * De-assert Clamp Output of Droop Detect circuits.
   */
  nModeVal &= ~HWIO_FMSK(PLL_MODE, PLL_APC_PDN);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

  /*
   * Program L/Alpha values.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_L_VAL, pCtxt, pConfig->nL);
  HAL_CLK_PLL_HWIO_OUT(PLL_ALPHA_VAL, pCtxt, pConfig->nAlpha);

  /*
   * Get the CONFIG value and clear out fields we will configure.
   */
  nUserVal  =  HAL_CLK_PLL_HWIO_IN(PLL_USER_CTL, pCtxt);
  nUserVal &= ~(HWIO_FMSK(PLL_USER_CTL, MN_EN) |
                HWIO_FMSK(PLL_USER_CTL, PREDIV2_EN) |
                HWIO_FMSK(PLL_USER_CTL, POSTDIV_CTL));

  /*
   * Program the pre-div value (div-1 to div-2).
   */
  if (pConfig->nPreDiv <= 2 && pConfig->nPreDiv > 0)
  {
    nUserVal |= HWIO_FVAL(PLL_USER_CTL, PREDIV2_EN, (pConfig->nPreDiv - 1));
  }

  /*
   * Program the post-div value (div-1, 2, and 4 are supported)
   */
  if ((pConfig->nPostDiv == 2) || (pConfig->nPostDiv == 4))
  {
    nUserVal |=
      ((pConfig->nPostDiv - 1) << HWIO_SHFT(PLL_USER_CTL, POSTDIV_CTL));
  }

  /*
   *  Check fractional output or integer output.
   */
  if (pConfig->nAlpha != 0)
  {
    nUserVal |= HWIO_FMSK(PLL_USER_CTL, MN_EN);
  }

  /*
   * Enable MAIN_OUT_ENA bit.
   */
  nUserVal |= HWIO_FMSK(PLL_USER_CTL, LVMAIN_EN);

  /*
   * Finally program the USER_CTL register.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL, pCtxt, nUserVal);

  /*
   * Enable the PLL if it was on before.
   */
  if (bPLLEnabled)
  {
    HAL_clk_VeyronPLLEnable(pSource, HAL_CLK_SOURCE_DISABLE_MODE_NORMAL, NULL);
  }

  return TRUE;

} /* END HAL_clk_VeyronPLLConfigPLL */


/* ===========================================================================
**  HAL_clk_VeyronPLLDetectPLLConfig
**
** ======================================================================== */

static void HAL_clk_VeyronPLLDetectPLLConfig
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
  pConfig->eVCO = HAL_CLK_PLL_VCO1;
  pConfig->nM = 0;
  pConfig->nN = 0;
  pConfig->nVCOMultiplier = 0;
  pConfig->nAlphaU = 0;
  pConfig->bFsmMode = FALSE;

  /*
   * Read current L and Alpha values.
   */
  pConfig->nL = HAL_CLK_PLL_HWIO_IN(PLL_L_VAL, pCtxt);
  pConfig->nAlpha = HAL_CLK_PLL_HWIO_IN(PLL_ALPHA_VAL, pCtxt);

  /*
   * Determine the oscillator source.
   */
  pConfig->eSource = HAL_CLK_SOURCE_XO;

  /*
   * Get the pre and post dividers.
   */
  nConfigVal = HAL_CLK_PLL_HWIO_IN(PLL_USER_CTL, pCtxt);
  pConfig->nPreDiv = ((nConfigVal & HWIO_FMSK(PLL_USER_CTL, PREDIV2_EN))
                      >> (HWIO_SHFT(PLL_USER_CTL, PREDIV2_EN))) + 1;
  pConfig->nPostDiv = ((nConfigVal & HWIO_FMSK(PLL_USER_CTL, POSTDIV_CTL))
                       >> HWIO_SHFT(PLL_USER_CTL, POSTDIV_CTL)) + 1;

} /* END HAL_clk_VeyronPLLDetectPLLConfig */

