/*
==============================================================================

FILE:         HALclkPeelPLL.c

DESCRIPTION:
  This file contains the clock HAL code for the Peel PLL control.
  These PLLs are of the Peel PLL variety.

==============================================================================

                             Edit History

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/v1/HALclkPeelPLL.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------- 
05/30/13   frv     Created

==============================================================================
            Copyright (c) 2014 Qualcomm Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/

#include "HALhwio.h"
#include "HALclkPeelPLL.h"
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
   HWIO_FMSK(PLL_MODE, PLL_RESET_N))

/*
 * HAL_CLK_PLL_INIT_TIME_US
 *
 * Init time in microseconds after de-asserting PLL reset (normal mode).
 */
#define HAL_CLK_PLL_INIT_TIME_US 500

/*
 * HAL_CLK_PLL_WARMUP_TIME_US
 *
 * Warm-up time in microseconds after turning on the PLL.
 */
#define HAL_CLK_PLL_WARMUP_TIME_US 2000


/* ============================================================================
**    Data Declarations
** ==========================================================================*/

/*
 * HAL_clk_PeelPLLControl
 *
 * Control function array for the Peel PLLs.
 */
HAL_clk_SourceControlType HAL_clk_PeelPLLControl =
{
  /* .Enable              = */ HAL_clk_PeelPLLEnable,
  /* .Disable             = */ HAL_clk_PeelPLLDisable,
  /* .IsEnabled           = */ HAL_clk_PeelPLLIsEnabled,
  /* .Config              = */ HAL_clk_PeelPLLConfig,
  /* .ConfigPLL           = */ HAL_clk_PeelPLLConfigPLL,
  /* .DetectPLLConfig     = */ HAL_clk_PeelPLLDetectPLLConfig,
  /* .EnableVote          = */ NULL,
  /* .DisableVote         = */ NULL,
  /* .IsVoteEnabled       = */ NULL,
};


/*============================================================================

               FUNCTION DEFINITIONS FOR MODULE

============================================================================*/


/* ===========================================================================
**  HAL_clk_PeelPLLEnable
**
** ======================================================================== */

static boolean HAL_clk_PeelPLLEnable
(
  HAL_clk_SourceDescType *pSource,
  HAL_clk_SourceDisableModeType eMode,
  void *pData
)
{
  uint32 nModeVal;
  HAL_clk_PLLContextType *pCtxt;

  /*
   * Check if PLL is already enabled and return
   */
  if (HAL_clk_PeelPLLIsEnabled(pSource))
  {
    return(TRUE);
  }

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Read current mode value./
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pCtxt);

  /*
   * Latche L value.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

  /*
   * Wait for PLL init time
   */
  HAL_clk_BusyWait(HAL_CLK_PLL_INIT_TIME_US);

  /*
   * Program the PLL to standby.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_OPMODE, pCtxt, 0x0);

  /*
   * De-assert PLL reset.
   */
  nModeVal |= HWIO_FMSK(PLL_MODE, PLL_RESET_N);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

  /*
   * Wait for the PLL warm-up time.
   */
  HAL_clk_BusyWait(HAL_CLK_PLL_WARMUP_TIME_US);

  /*
   * Program the PLL to run mode.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_OPMODE, pCtxt, 0x1);

  /*
   * Wait for lock.
   */
  while (HAL_CLK_PLL_HWIO_INF(PLL_MODE, pCtxt, PLL_LOCK_DET) == 0)
  {
    HAL_clk_BusyWait(10);
  }

  /*
   * Put the PLL in active mode
   */
  nModeVal |= HWIO_FMSK(PLL_MODE, PLL_OUTCTRL);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

  return(TRUE);

} /* END HAL_clk_PeelPLLEnable */


/* ===========================================================================
**  HAL_clk_PeelPLLDisable
**
** ======================================================================== */

static void HAL_clk_PeelPLLDisable
(
  HAL_clk_SourceDescType *pSource,
  HAL_clk_SourceDisableModeType eMode,
  void *pData
)
{
  uint32  nModeVal;
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
   * Put the PLL in reset mode
   */
  nModeVal &= ~(HWIO_FMSK(PLL_MODE, PLL_RESET_N) |
                HWIO_FMSK(PLL_MODE, PLL_OUTCTRL));
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

} /* END HAL_clk_PeelPLLDisable */


/* ===========================================================================
**  HAL_clk_PeelPLLIsEnabled
**
** ======================================================================== */

static boolean HAL_clk_PeelPLLIsEnabled
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

} /* END HAL_clk_PeelPLLIsEnabled */


/* ===========================================================================
**  HAL_clk_PeelPLLConfig
**
** ======================================================================== */

static void HAL_clk_PeelPLLConfig
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
    default:
      break;
  }

} /* END HAL_clk_PeelPLLConfig */


/* ===========================================================================
**  HAL_clk_PeelPLLConfigPLL
**
** ======================================================================== */

static boolean HAL_clk_PeelPLLConfigPLL
(
  HAL_clk_SourceDescType      *pSource,
  const HAL_clk_PLLConfigType *pConfig,
  HAL_clk_SourceConfigMode eMode
)
{
  uint32  nModeVal, nUserVal;
  boolean bPLLEnabled = FALSE;
  HAL_clk_PLLContextType *pCtxt;

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Check PLL mode.
   */
  bPLLEnabled = HAL_clk_PeelPLLIsEnabled(pSource);

  /*
   * Disable the PLL.
   */
  if (bPLLEnabled)
  {
    HAL_clk_PeelPLLDisable(pSource, HAL_CLK_SOURCE_DISABLE_MODE_NORMAL, NULL);
  }

  /*
   * Read the PLLx_Mode value
   */
  nModeVal  = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pCtxt);

  /*
   * Program L/Alpha/AlphaU values.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_L_VAL, pCtxt, pConfig->nL);
  HAL_CLK_PLL_HWIO_OUT(PLL_CAL_L_VAL, pCtxt, pConfig->nL);

  /*
   * Get the CONFIG value and clear out fields we will configure.
   */
  nUserVal  =  HAL_CLK_PLL_HWIO_IN(PLL_USER_CTL, pCtxt);
  nUserVal &= ~(HWIO_FMSK(PLL_USER_CTL, PRE_DIV_RATIO) |
                HWIO_FMSK(PLL_USER_CTL, POST_DIV_RATIO));

  /*
   * Program the pre-div value (div-1 to div-8).
   */
  if (pConfig->nPreDiv <= 8 && pConfig->nPreDiv > 0)
  {
    nUserVal |= HWIO_FVAL(PLL_USER_CTL, PRE_DIV_RATIO, (pConfig->nPreDiv - 1));
  }

  /*
   * Program the post-div value (div-1,2,4,8 and 16 are supported)
   */
  if ((pConfig->nPostDiv == 2) || (pConfig->nPostDiv == 4) ||
      (pConfig->nPostDiv == 8) || (pConfig->nPostDiv == 16))
  {
    nUserVal |=
      ((pConfig->nPostDiv - 1) << HWIO_SHFT(PLL_USER_CTL, POST_DIV_RATIO));
  }

  /*
   * Enable MAIN_OUT_ENA bit. 
   */
  nUserVal |= HWIO_FMSK(PLL_USER_CTL, PLLOUT_LV_MAIN);

  /*
   * Finally program the USER_CTL register.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL, pCtxt, nUserVal);

  /*
   * Enable the PLL if it was on before.
   */
  if (bPLLEnabled)
  {
    HAL_clk_PeelPLLEnable(pSource, HAL_CLK_SOURCE_DISABLE_MODE_NORMAL, NULL);
  }

  return(TRUE);

} /* END HAL_clk_PeelPLLConfigPLL */


/* ===========================================================================
**  HAL_clk_PeelPLLDetectPLLConfig
**
** ======================================================================== */

static void HAL_clk_PeelPLLDetectPLLConfig
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
  pConfig->eSource        = 0;
  pConfig->nL             = 0;
  pConfig->nM             = 0;
  pConfig->nN             = 0;
  pConfig->nAlpha         = 0;
  pConfig->nAlphaU        = 0;
  pConfig->nPostDiv       = 0;
  pConfig->nPreDiv        = 0;
  pConfig->nVCOMultiplier = 0;
  pConfig->eVCO           = 0;

  /*
   * Read current L, Alpha, and AlphaU values.
   */
  pConfig->nL = HAL_CLK_PLL_HWIO_IN(PLL_L_VAL, pCtxt);

  /*
   * Determine the oscillator source.
   */
  pConfig->eSource = HAL_CLK_SOURCE_SLEEPCLK;

  /*
   * Get the config value for pre and post dividers.
   */
  nConfigVal = HAL_CLK_PLL_HWIO_IN(PLL_USER_CTL, pCtxt);

  /*
   * Get the pre and post dividers.
   */
  pConfig->nPreDiv = ((nConfigVal & HWIO_FMSK(PLL_USER_CTL, PRE_DIV_RATIO))
                         >> (HWIO_SHFT(PLL_USER_CTL, PRE_DIV_RATIO))) + 1;
  pConfig->nPostDiv = ((nConfigVal & HWIO_FMSK(PLL_USER_CTL, POST_DIV_RATIO))
                >> HWIO_SHFT(PLL_USER_CTL, POST_DIV_RATIO)) + 1;

} /* END HAL_clk_PeelPLLDetectPLLConfig */

