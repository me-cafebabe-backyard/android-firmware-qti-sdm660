/*
==============================================================================

FILE:         HALclkHuayraPLL.c

DESCRIPTION:
  This file contains the clock HAL code for the Huayra PLL control.
  These PLLs are of the Huayra PLL variety.

==============================================================================

                             Edit History

$Header: //components/rel/boot.xf/1.4/QcomPkg/Library/HALclkSharedLib/HALclkHuayraPLLTemplate.c#2 $

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
  (HWIO_FMSK(PLL_MODE, OUTCTRL)  | \
   HWIO_FMSK(PLL_MODE, BYPASSNL) | \
   HWIO_FMSK(PLL_MODE, RESET_N))

/*
 * Definitions for configuring the PLL in FSM Mode
 */
#define HAL_CLK_PLL_BIAS_COUNT_VAL   (0x6 << HWIO_SHFT(PLL_MODE, BIAS_COUNT))
#define HAL_CLK_PLL_LOCK_COUNT_VAL   (0x0 << HWIO_SHFT(PLL_MODE, LOCK_COUNT))

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

/*
 * Chip family IDs.
 */
#define HAL_CLK_CHIP_FAMILY_ISTARI 56
#define HAL_CLK_CHIP_FAMILY_HAWKER 61

/*
 * Magic Number Definitions for configuring the PLL droop detecton feature
 */
#define MAGIC_NUMBER_MDD_USER_CTL_LO    0x2b00c40a
#define MAGIC_NUMBER_MDD_USER_CTL_HI    0x0801e72c
#define MAGIC_NUMBER_MDD_CONFIG_CTL     0x33c01036
#define MAGIC_NUMBER_MDD_TEST_CTL       0x00000088
#define MAGIC_NUMBER_PLL_CONFIG_CTL_LO  0x0000e000
#define MAGIC_NUMBER_PLL_CONFIG_CTL_HI  0x00004000


/*============================================================================

               FUNCTION DEFINITIONS FOR MODULE

============================================================================*/

/* ===========================================================================
**  HAL_clk_NeedQCTDD02019439
**
**  Determine if QCTDD02019439 workaround is needed for this chip version.
**
** ======================================================================== */

static boolean HAL_clk_NeedQCTDD02019439 (void)
{
  return
    (HAL_clk_GetChipFamily() == HAL_CLK_CHIP_FAMILY_HAWKER) ||
    (HAL_clk_GetChipFamily() == HAL_CLK_CHIP_FAMILY_ISTARI &&
     HAL_clk_GetChipVersion() < HAL_CLK_CHIP_VERSION(3, 0));

} /* END HAL_clk_NeedQCTDD02019439 */


/* ===========================================================================
**  HAL_clk_HuayraPLLPostDivToHW
**
** ======================================================================== */

static uint32 HAL_clk_HuayraPLLPostDivToHW (uint32 nDivider)
{
  switch (nDivider)
  {
    case 0:
    case 1:   return 0;
    case 2:   return 1;
    case 4:   return 3;
    case 8:   return 2;
    default:
      return 2;
  }

} /* END HAL_clk_HuayraPLLPostDivToHW */


/* ===========================================================================
**  HAL_clk_HuayraPLLPostDivFromHW
**
** ======================================================================== */

static uint32 HAL_clk_HuayraPLLPostDivFromHW (uint32 nDivider)
{
  switch (nDivider)
  {
    case 0:   return 1;
    case 1:   return 2;
    case 2:   return 8;
    case 3:   return 4;
    default:
      return 1;
  }

} /* END HAL_clk_HuayraPLLPostDivFromHW */



/* ===========================================================================
**  HAL_clk_HuayraPLLEnable
**
** ======================================================================== */

static boolean HAL_clk_HuayraPLLEnable
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
  if (HAL_clk_HuayraPLLIsEnabled(pSource))
  {
    return TRUE;
  }

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Read current modevalue.
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pCtxt);

  /*
   * De-assert PLL bypass.
   * This latches L and Alpha values.
   */
  nModeVal |= HWIO_FMSK(PLL_MODE, BYPASSNL);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

  /*
   * Wait for PLL init time
   */
  HAL_clk_BusyWait(HAL_CLK_PLL_INIT_TIME_US);

  /*
   * De-assert PLL reset.
   */
  nModeVal |= HWIO_FMSK(PLL_MODE, RESET_N);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

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
      HWIO_FMSK(PLL_MODE, LOCK_DET),
      HAL_CLK_LOCK_TIMEOUT_US);

  /*
   * Return immediately if the lock detect failed.
   */
  if (!bResult)
  {
    ERR_FATAL("HAL_clk_HuayraPLLEnable Lock Failure", 0, 0, 0);
    return FALSE;
  }

  /*
   * Put the PLL in active mode
   */
  nModeVal |= HWIO_FMSK(PLL_MODE, OUTCTRL);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

  return TRUE;

} /* END HAL_clk_HuayraPLLEnable */


/* ===========================================================================
**  HAL_clk_HuayraPLLDisable
**
** ======================================================================== */

static void HAL_clk_HuayraPLLDisable
(
  HAL_clk_SourceDescType        *pSource,
  HAL_clk_SourceDisableModeType  eMode,
  void                          *pData
)
{
  uint32                  nModeVal;
  HAL_clk_PLLContextType *pCtxt;

  /*
   * The Huayra PLL's only support full enable/disable mode.
   */
  if (eMode != HAL_CLK_SOURCE_DISABLE_MODE_NORMAL)
  {
    ERR_FATAL("HAL_clk_HuayraPLLDisable Invalid Parameter", 0, 0, 0);
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
  nModeVal &= ~(HWIO_FMSK(PLL_MODE, RESET_N) |
                HWIO_FMSK(PLL_MODE, BYPASSNL) |
                HWIO_FMSK(PLL_MODE, OUTCTRL));
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

} /* END HAL_clk_HuayraPLLDisable */


/* ===========================================================================
**  HAL_clk_HuayraPLLIsEnabled
**
** ======================================================================== */

static boolean HAL_clk_HuayraPLLIsEnabled
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

} /* END HAL_clk_HuayraPLLIsEnabled */


/* ===========================================================================
**  HAL_clk_HuayraPLLConfig
**
** ======================================================================== */

static void HAL_clk_HuayraPLLConfig
(
  HAL_clk_SourceDescType   *pSource,
  HAL_clk_SourceConfigType  eConfig
)
{
  HAL_clk_PLLContextType *pCtxt;
  uint32 nVal;

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
      nVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pCtxt);
      nVal &= ~HWIO_FMSK(PLL_MODE, BIAS_COUNT);
      nVal &= ~HWIO_FMSK(PLL_MODE, LOCK_COUNT);
      nVal |= HAL_CLK_PLL_BIAS_COUNT_VAL;
      nVal |= HAL_CLK_PLL_LOCK_COUNT_VAL;
      nVal |= HWIO_FMSK(PLL_MODE, FSM_EN);
      HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nVal);
      break;

    case HAL_CLK_CONFIG_PLL_FSM_MODE_DISABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_MODE, pCtxt, FSM_EN, 0);
      break;

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

    case HAL_CLK_CONFIG_PLL_DROOP_DETECTION_DISABLE:
      break;

    case HAL_CLK_CONFIG_PLL_DROOP_DETECTION_ENABLE:
      HAL_CLK_PLL_HWIO_OUT (MDD_USER_CTL_LO,   pCtxt, MAGIC_NUMBER_MDD_USER_CTL_LO);
      HAL_CLK_PLL_HWIO_OUT (MDD_USER_CTL_HI,   pCtxt, MAGIC_NUMBER_MDD_USER_CTL_HI);
      HAL_CLK_PLL_HWIO_OUT (MDD_CONFIG_CTL,    pCtxt, MAGIC_NUMBER_MDD_CONFIG_CTL);
      HAL_CLK_PLL_HWIO_OUT (MDD_TEST_CTL,      pCtxt, MAGIC_NUMBER_MDD_TEST_CTL);
      HAL_CLK_PLL_HWIO_OUT (PLL_CONFIG_CTL_LO, pCtxt, MAGIC_NUMBER_PLL_CONFIG_CTL_LO);
      HAL_CLK_PLL_HWIO_OUT (PLL_CONFIG_CTL_HI, pCtxt, MAGIC_NUMBER_PLL_CONFIG_CTL_HI);
      HAL_CLK_PLL_HWIO_OUTF(MDD_MODE,          pCtxt, CAL_EN, 1);
      HAL_CLK_PLL_HWIO_OUTF(PLL_PWRFSM_CTL,    pCtxt, DDEN, 1);
      break;

    default:
      ERR_FATAL("HAL_clk_HuayraPLLConfig Invalid Parameter", 0, 0, 0);
      break;
  }

} /* END HAL_clk_HuayraPLLConfig */


/* ===========================================================================
**  HAL_clk_HuayraPLLConfigPLLNormal
**
** ======================================================================== */

static boolean HAL_clk_HuayraPLLConfigPLLNormal
(
  HAL_clk_SourceDescType      *pSource,
  const HAL_clk_PLLConfigType *pConfig
)
{
  uint32  nModeVal;
  uint32  nUserVal;
  boolean bPLLEnabled = FALSE;
  HAL_clk_PLLContextType *pCtxt;

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Check PLL mode.
   */
  bPLLEnabled = HAL_clk_HuayraPLLIsEnabled(pSource);

  /*
   * Disable the PLL.
   */
  if (bPLLEnabled)
  {
    HAL_clk_HuayraPLLDisable(pSource, HAL_CLK_SOURCE_DISABLE_MODE_NORMAL, NULL);
  }

  /*
   * Read current mode value.
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pCtxt);

  /*
   * De-assert Clamp Output of Droop Detect circuits.
   */
  nModeVal &= ~HWIO_FMSK(PLL_MODE, APC_PDN);
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
   * Program the post-div value.
   */
  nUserVal |= HWIO_FVAL(PLL_USER_CTL, POSTDIV_CTL,
    HAL_clk_HuayraPLLPostDivToHW(pConfig->nPostDiv));

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
    HAL_clk_HuayraPLLEnable(pSource, HAL_CLK_SOURCE_DISABLE_MODE_NORMAL, NULL);
  }

  return TRUE;

} /* END HAL_clk_HuayraPLLConfigPLLNormal */


/* ===========================================================================
**  HAL_clk_HuayraPLLConfigPLLSlew
**
**  Returns:
**    boolean - TRUE if successfully configured.
**              FALSE if unable to detect that the PLL successfully locked.
** ======================================================================== */

static boolean HAL_clk_HuayraPLLConfigPLLSlew
(
  HAL_clk_SourceDescType      *pSource,
  const HAL_clk_PLLConfigType *pConfig
)
{
  uint32                  nTestVal = 0;
  HAL_clk_PLLContextType *pCtxt;
  boolean                 bResult;

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Override CFA.
   */
  if (HAL_clk_NeedQCTDD02019439())
  {
    nTestVal = HAL_CLK_PLL_HWIO_IN(PLL_TEST_CTL_LO, pCtxt);
    nTestVal |= HWIO_FVAL(PLL_TEST_CTL_LO, STAY_IN_CFA, 1);
    HAL_CLK_PLL_HWIO_OUT(PLL_TEST_CTL_LO, pCtxt, nTestVal);
  }

  /*
   * Program L value.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_L_VAL, pCtxt, pConfig->nL);

  /*
   * Wait at least 8 reference clock cycles and remove CFA override.
   */
  if (HAL_clk_NeedQCTDD02019439())
  {
    HAL_clk_BusyWait(1);
    nTestVal &= ~HWIO_FMSK(PLL_TEST_CTL_LO, STAY_IN_CFA);
    HAL_CLK_PLL_HWIO_OUT(PLL_TEST_CTL_LO, pCtxt, nTestVal);
  }

  /*
   * Wait for 11 or more PLL clk_ref ticks for PLL_LOCK_DET to transition to 0.
   * When using a reference clock of XO, the wait requirement is 570 ns.
   */
  HAL_clk_BusyWait(1);

  /*
   * Wait for the PLL to lock during the 15 us timeout period.
   */
  bResult =
    HAL_clk_ValidateRegSetTimeout(
      HAL_CLK_PLL_HWIO_ADDR(PLL_MODE, pCtxt),
      HWIO_FMSK(PLL_MODE, LOCK_DET),
      HAL_CLK_LOCK_TIMEOUT_US);

  if (!bResult)
  {
    ERR_FATAL("HAL_clk_HuayraPLLConfigPLLSlew Lock Failure", 0, 0, 0);
  }

  return bResult;

} /* END HAL_clk_HuayraPLLConfigPLLSlew */


/* ===========================================================================
**  HAL_clk_HuayraPLLConfigPLL
**
** ======================================================================== */

static boolean HAL_clk_HuayraPLLConfigPLL
(
  HAL_clk_SourceDescType      *pSource,
  const HAL_clk_PLLConfigType *pConfig,
  HAL_clk_SourceConfigMode     eMode
)
{
  boolean bResult = FALSE;

  switch (eMode)
  {
    case HAL_CLK_SOURCE_CONFIG_MODE_NORMAL:
      bResult = HAL_clk_HuayraPLLConfigPLLNormal(pSource, pConfig);
      break;
    case HAL_CLK_SOURCE_CONFIG_MODE_SLEW:
      bResult = HAL_clk_HuayraPLLConfigPLLSlew(pSource, pConfig);
      break;
    default:
      ERR_FATAL("HAL_clk_HuayraPLLConfigPLL Invalid Parameter", 0, 0, 0);
      break;
  }

  return bResult;

} /* END HAL_clk_HuayraPLLConfigPLL */


/* ===========================================================================
**  HAL_clk_HuayraPLLDetectPLLConfig
**
** ======================================================================== */

static void HAL_clk_HuayraPLLDetectPLLConfig
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
                       >> HWIO_SHFT(PLL_USER_CTL, POSTDIV_CTL));
  pConfig->nPostDiv = HAL_clk_HuayraPLLPostDivFromHW(pConfig->nPostDiv);

  /*
   * Get the current state of the FSM Voting Mode.
   */
  pConfig->bFsmMode = (boolean)HAL_CLK_PLL_HWIO_INF(PLL_MODE, pCtxt, FSM_EN);

} /* END HAL_clk_HuayraPLLDetectPLLConfig */

