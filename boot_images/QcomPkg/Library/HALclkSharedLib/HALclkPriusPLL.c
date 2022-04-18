/*
==============================================================================

FILE:         HALclkPriusPLL.c

DESCRIPTION:
  This file contains the clock HAL code for the Prius/Tesla PLL control.
  These PLLs are of the Prius and Tesla PLL variety.

==============================================================================

                             Edit History


when       who     what, where, why
--------   ---     -----------------------------------------------------------
05/30/13   frv     Created

==============================================================================
   Copyright (c) 2013-2015 QUALCOMM Technologies, Inc.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/

#include "HALhwio.h"
#include "HALclkPriusPLL.h"
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

/*
 * HAL_CLK_PLL_OUTCTRL_OFF_US
 *
 * Wait after PLL_OUTCTRL off before setting freeze bit.
 */
#define HAL_CLK_PLL_OUTCTRL_OFF_US 5


/* ============================================================================
**    Data Declarations
** ==========================================================================*/

/*
 * HAL_clk_PriusPLLControl
 *
 * Control function array for the Prius/Tesla PLLs.
 */
HAL_clk_SourceControlType HAL_clk_PriusPLLControl =
{
  /* .Enable          = */ HAL_clk_PriusPLLEnable,
  /* .Disable         = */ HAL_clk_PriusPLLDisable,
  /* .IsEnabled       = */ HAL_clk_PriusPLLIsEnabled,
  /* .Config          = */ HAL_clk_PriusPLLConfig,
  /* .ConfigPLL       = */ HAL_clk_PriusPLLConfigPLL,
  /* .DetectPLLConfig = */ HAL_clk_PriusPLLDetectPLLConfig,
  /* .EnableVote      = */ HAL_clk_PriusPLLEnableVote,
  /* .DisableVote     = */ HAL_clk_PriusPLLDisableVote,
  /* .IsVoteEnabled   = */ HAL_clk_PriusPLLIsVoteEnabled,
};


/*============================================================================

               FUNCTION DEFINITIONS FOR MODULE

============================================================================*/


/* ===========================================================================
**  HAL_clk_PriusPLLEnableVote
**
** ======================================================================== */

static boolean HAL_clk_PriusPLLEnableVote
(
  HAL_clk_SourceDescType *pSource
)
{
  HAL_clk_PLLContextType *pCtxt;
  uint32 nVal;
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
    ERR_FATAL("HAL_clk_PriusPLLEnableVote Activate Failure", 0, 0, 0);
  }

  return bResult;

} /* END HAL_clk_PriusPLLEnableVote */


/* ===========================================================================
**  HAL_clk_PriusPLLDisableVote
**
** ======================================================================== */

static void HAL_clk_PriusPLLDisableVote
(
  HAL_clk_SourceDescType *pSource
)
{
  HAL_clk_PLLContextType *pCtxt;
  uint32 nVal;

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Clear the appropriate bit.
   */
  nVal = inpdw(pCtxt->VoterRegister.nAddr) & ~pCtxt->VoterRegister.nMask;
  outpdw(pCtxt->VoterRegister.nAddr, nVal);

} /* END HAL_clk_PriusPLLDisableVote */


/* ===========================================================================
**  HAL_clk_PriusPLLIsVoteEnabled
**
** ======================================================================== */

static boolean HAL_clk_PriusPLLIsVoteEnabled
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

} /* END HAL_clk_PriusPLLIsVoteEnabled */


/* ===========================================================================
**  HAL_clk_PriusPLLEnableFromStandby
**
**  PLL bringup from standby state.
**  When in the standby state, the bias is on and draws 75-100 micro amps.
**  This procedure skips calibration.
**
**  This procedure applies only to Prius PLL types.
**
**  The following fields must have remained unchanged from the values present
**  when the HAL_clk_PriusPLLDisableToStandby function was executed:
**  - PLL_L_VAL
**  - PLL_ALPHA_VAL
**  - PLL_ALPHA_VAL_U
**  - PLL_USER_CTL[ALPHA_EN]
**  - PLL_USER_CTL[VCO_SEL]
**
**  Returns:
**    boolean - TRUE if successfully enabled. FALSE otherwise.
** ======================================================================== */

static boolean HAL_clk_PriusPLLEnableFromStandby
(
  HAL_clk_SourceDescType *pSource
)
{
  uint32 nModeVal, nUserCtlUVal;
  HAL_clk_PLLContextType *pCtxt;
  boolean                 bResult;

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Only the Prius PLL supports this usage.
   */
  if (pCtxt->ePLLType != HAL_CLK_PLL_PRIUS)
  {
    ERR_FATAL("HAL_clk_PriusPLLEnableFromStandby Invalid PLL Type", 0, 0, 0);
    return FALSE;
  }

  /*
   * Read current user ctl value.
   */
  nUserCtlUVal = HAL_CLK_PLL_HWIO_IN(PLL_USER_CTL_U, pCtxt);

  /*
   * Assert the target ctl field.
   */
  nUserCtlUVal |= HWIO_FMSK(PLL_USER_CTL_U, TARGET_CTL);
  HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL_U, pCtxt, nUserCtlUVal);

  /*
   * Read current mode value.
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pCtxt);

  /*
   * Assert the reset field.
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
   * Return immediately if the lock detect failed.
   */
  if (!bResult)
  {
    ERR_FATAL("HAL_clk_PriusPLLEnableFromStandby Lock Failure", 0, 0, 0);
    return FALSE;
  }

  /*
   * Assert the output control field.
   */
  nModeVal |= HWIO_FMSK(PLL_MODE, PLL_OUTCTRL);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

  /*
   * De-assert the target ctl field.
   */
  nUserCtlUVal &= ~HWIO_FMSK(PLL_USER_CTL_U, TARGET_CTL);
  HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL_U, pCtxt, nUserCtlUVal);

  return TRUE;

} /* END HAL_clk_PriusPLLEnableFromStandby */


/* ===========================================================================
**  HAL_clk_PriusPLLEnableFromSaved
**
**  PLL bringup with restore state.
**  When in the saved state, the bias is off and draws no power.
**  This procedure skips calibration.
**
**  This procedure applies only to Prius PLL types.
**
**  The following fields must have remained unchanged from the values present
**  when the HAL_clk_PriusPLLDisableToSaved function was executed:
**  - PLL_L_VAL
**  - PLL_ALPHA_VAL
**  - PLL_ALPHA_VAL_U
**  - PLL_USER_CTL[ALPHA_EN]
**  - PLL_USER_CTL[VCO_SEL]
**
**  Returns:
**    boolean - TRUE if successfully enabled. FALSE otherwise.
** ======================================================================== */

static boolean HAL_clk_PriusPLLEnableFromSaved
(
  HAL_clk_SourceDescType *pSource,
  void                   *pData
)
{
  uint32                  nModeVal, nUserCtlUVal;
  HAL_clk_PLLContextType *pCtxt;
  boolean                 bResult;
  uint32                 *pnCalibration = (uint32 *) pData;

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Only the Prius PLL supports this usage.
   */
  if (pCtxt->ePLLType != HAL_CLK_PLL_PRIUS)
  {
    ERR_FATAL("HAL_clk_PriusPLLEnableFromSaved Invalid PLL Type", 0, 0, 0);
    return FALSE;
  }

  /*
   * Validate that we have a place to store the calibration.
   */
  if (pnCalibration == NULL)
  {
    ERR_FATAL("HAL_clk_PriusPLLEnableFromSaved Invalid Parameter", 0, 0, 0);
    return FALSE;
  }

  /*
   * Read current mode value.
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pCtxt);

  /*
   * Assert the bypassnl field to power up the bias.
   */
  nModeVal |= HWIO_FMSK(PLL_MODE, PLL_BYPASSNL);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

  /*
   * Wait 5 us for the bias to power up - enter standby state.
   */
  HAL_clk_BusyWait(5);

  /*
   * Restore the saved state.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_FREQ_CTL, pCtxt, *pnCalibration);

  /*
   * Read current user ctl value.
   */
  nUserCtlUVal = HAL_CLK_PLL_HWIO_IN(PLL_USER_CTL_U, pCtxt);

  /*
   * Assert the target ctl and write state fields.
   */
  nUserCtlUVal |= HWIO_FMSK(PLL_USER_CTL_U, TARGET_CTL);
  nUserCtlUVal |= HWIO_FMSK(PLL_USER_CTL_U, WRITE_STATE);
  HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL_U, pCtxt, nUserCtlUVal);

  /*
   * Assert the update field.
   */
  nModeVal |= HWIO_FMSK(PLL_MODE, PLL_UPDATE);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

  /*
   * Wait for PLL_UPDATE to clear within the timeout period.
   */
  bResult =
    HAL_clk_ValidateRegClearTimeout(
      HAL_CLK_PLL_HWIO_ADDR(PLL_MODE, pCtxt),
      HWIO_FMSK(PLL_MODE, PLL_UPDATE),
      HAL_CLK_UPDATE_TIMEOUT_US);

  /*
   * Return immediately if the update failed.
   */
  if (!bResult)
  {
    ERR_FATAL("HAL_clk_PriusPLLEnableFromSaved Update Failure", 0, 0, 0);
    return FALSE;
  }

  /*
   * De-assert the write state field.
   */
  nUserCtlUVal &= ~HWIO_FMSK(PLL_USER_CTL_U, WRITE_STATE);
  HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL_U, pCtxt, nUserCtlUVal);

  /*
   * Assert the reset field.
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
    ERR_FATAL("HAL_clk_PriusPLLEnableFromSaved Lock Failure", 0, 0, 0);
    return FALSE;
  }

  /*
   * Assert the outctrl field.
   */
  nModeVal |= HWIO_FMSK(PLL_MODE, PLL_OUTCTRL);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

  /*
   * De-assert the target ctl field.
   */
  nUserCtlUVal &= ~HWIO_FMSK(PLL_USER_CTL_U, TARGET_CTL);
  HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL_U, pCtxt, nUserCtlUVal);

  return TRUE;

} /* END HAL_clk_PriusPLLEnableFromSaved */


/* ===========================================================================
**  HAL_clk_PriusPLLEnableNormal
**
**  PLL initial bringup.
**  When in the off state, the bias is off and draws no power.
**  This procedure results in calibration being performed.
**
**  This procedure applies only to both Prius and Tesla PLL types.
**
**  Returns:
**    boolean - TRUE if successfully enabled. FALSE otherwise.
** ======================================================================== */

static boolean HAL_clk_PriusPLLEnableNormal
(
  HAL_clk_SourceDescType *pSource
)
{
  uint32                  nModeVal, nUserCtlUVal;
  HAL_clk_PLLContextType *pCtxt;
  boolean                 bResult;

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Read current user control value.
   */
  nUserCtlUVal = HAL_CLK_PLL_HWIO_IN(PLL_USER_CTL_U, pCtxt);

  /*
   * Set the lockdet field.
   */
  nUserCtlUVal |= HWIO_FMSK(PLL_USER_CTL_U, LOCK_DET);
  HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL_U, pCtxt, nUserCtlUVal);

  /*
   * Read current mode value.
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pCtxt);

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
    ERR_FATAL("HAL_clk_PriusPLLEnableNormal Lock Failure", 0, 0, 0);
    return FALSE;
  }

  /*
   * Put the PLL in active mode
   */
  nModeVal |= HWIO_FMSK(PLL_MODE, PLL_OUTCTRL);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

  return TRUE;

} /* END HAL_clk_PriusPLLEnableNormal */


/* ===========================================================================
**  HAL_clk_PriusPLLEnableFromFreeze
**
**  PLL bringup from 'freeze' state.
**  This procedure skips calibration.
**
**  This procedure applies only to Prius PLL types.
**
**  The following bit must be set per HPG to prevent calibration loss
**  when the HAL_clk_PriusPLLEnableFromFreeze function was executed:
**  - PLL_TEST_CTL_U[CAL_CODE_UPDATE]
**
**  Returns:
**    boolean - TRUE if successfully enabled. FALSE otherwise.
** ======================================================================== */

static boolean HAL_clk_PriusPLLEnableFromFreeze
(
  HAL_clk_SourceDescType *pSource
)
{
  HAL_clk_PLLContextType *pCtxt;
  boolean                 bResult;

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Only the Prius PLL supports this usage.
   */
  if (pCtxt->ePLLType != HAL_CLK_PLL_PRIUS)
  {
    ERR_FATAL("HAL_clk_PriusPLLEnableFromFreeze Invalid PLL Type", 0, 0, 0);
    return FALSE;
  }

  HAL_CLK_PLL_HWIO_OUTF(PLL_TEST_CTL_U, pCtxt, CAL_CODE_UPDATE, 0x1);
  HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL_U, pCtxt, FREEZE_PLL, 0x0);

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
    ERR_FATAL("HAL_clk_PriusPLLEnableFromFreeze Lock Failure", 0, 0, 0);
    return FALSE;
  }

  HAL_CLK_PLL_HWIO_OUTF(PLL_TEST_CTL_U, pCtxt, CAL_CODE_UPDATE, 0x0);
  HAL_CLK_PLL_HWIO_OUTF(PLL_MODE, pCtxt, PLL_OUTCTRL, 1);

  return TRUE;

} /* END HAL_clk_PriusPLLEnableFromFreeze */


/* ===========================================================================
**  HAL_clk_PriusPLLEnable
**
**  The appropriate enable mode is executed based on the eMode parameter.
**
**  Returns:
**    boolean - TRUE if successfully enabled. FALSE otherwise.
** ======================================================================== */

static boolean HAL_clk_PriusPLLEnable
(
  HAL_clk_SourceDescType        *pSource,
  HAL_clk_SourceDisableModeType  eMode,
  void                          *pData
)
{
  boolean bResult;

  /*
   * Check if PLL is already enabled and return
   */
  if (HAL_clk_PriusPLLIsEnabled(pSource))
  {
    return TRUE;
  }

  switch (eMode)
  {
    case HAL_CLK_SOURCE_DISABLE_MODE_STANDBY:
      bResult = HAL_clk_PriusPLLEnableFromStandby(pSource);
      break;
    case HAL_CLK_SOURCE_DISABLE_MODE_SAVE:
      bResult = HAL_clk_PriusPLLEnableFromSaved(pSource, pData);
      break;
    case HAL_CLK_SOURCE_DISABLE_MODE_FREEZE:
      bResult = HAL_clk_PriusPLLEnableFromFreeze(pSource);
      break;
    case HAL_CLK_SOURCE_DISABLE_MODE_NORMAL:
    bResult = HAL_clk_PriusPLLEnableNormal(pSource);
      break;
    default:
      bResult = FALSE;
      ERR_FATAL("HAL_clk_PriusPLLEnable Invalid Parameter", 0, 0, 0);
      break;
  }

  return bResult;

} /* END HAL_clk_PriusPLLEnable */


/* ===========================================================================
**  HAL_clk_PriusPLLDisableToStandby
**
**  PLL shutdown to standby state.
**  This procedure leaves the bias on:
**    skips calibration when enabling via HAL_clk_PriusPLLEnableFromStandby.
**    draws 75-100 micro amps while in standby mode.
**
**  This procedure applies only to Prius PLL types.
**
** ======================================================================== */

static void HAL_clk_PriusPLLDisableToStandby
(
  HAL_clk_SourceDescType *pSource
)
{
  uint32  nModeVal;
  HAL_clk_PLLContextType *pCtxt;

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Only the Prius PLL supports this usage.
   */
  if (pCtxt->ePLLType != HAL_CLK_PLL_PRIUS)
  {
    ERR_FATAL("HAL_clk_PriusPLLDisableToStandby Invalid PLL Type", 0, 0, 0);
    return;
  }

  /*
   * Read current mode value.
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pCtxt);

  /*
   * De-assert the output control field.
   */
  nModeVal &= ~HWIO_FMSK(PLL_MODE, PLL_OUTCTRL);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

  /*
   * Wait 2 ticks of the output main clock.
   */
  HAL_clk_BusyWait(1);

  /*
   * De-assert the reset field.
   */
  nModeVal &= ~HWIO_FMSK(PLL_MODE, PLL_RESET_N);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

} /* END HAL_clk_PriusPLLDisableToStandby */


/* ===========================================================================
**  HAL_clk_PriusPLLDisableToSaved
**
**  PLL shutdown with save state.
**  When in the saved state, the bias is off and draws no power.
**  The calibration data is saved in *pData to be used later when
**  calling HAL_clk_PriusPLLEnableFromSaved.
**
**  This procedure applies only to Prius PLL types.
**
**  NOTE: the void *pData argument is expected to be pointing to a
**  uint32. Therefore it MUST be recasted to a (uint32 *) when using it.
**
** ======================================================================== */

static void HAL_clk_PriusPLLDisableToSaved
(
  HAL_clk_SourceDescType *pSource,
  void                   *pData
)
{
  uint32 nModeVal, nUserCtlUVal;
  HAL_clk_PLLContextType *pCtxt;
  uint32 *pnCalibration = (uint32 *) pData;

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Only the Prius PLL supports this usage.
   */
  if (pCtxt->ePLLType != HAL_CLK_PLL_PRIUS)
  {
    ERR_FATAL("HAL_clk_PriusPLLDisableToSaved Invalid PLL Type", 0, 0, 0);
    return;
  }

  /*
   * Validate that we have a place to store the calibration.
   */
  if (pnCalibration == NULL)
  {
    ERR_FATAL("HAL_clk_PriusPLLDisableToSaved Invalid Parameter", 0, 0, 0);
    return;
  }

  /*
   * Read current mode value.
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pCtxt);

  /*
   * De-assert the output control field.
   */
  nModeVal &= ~HWIO_FMSK(PLL_MODE, PLL_OUTCTRL);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

  /*
   * Wait 2 ticks of the output main clock.
   */
  HAL_clk_BusyWait(1);

  /*
   * Read current user ctl value.
   */
  nUserCtlUVal = HAL_CLK_PLL_HWIO_IN(PLL_USER_CTL_U, pCtxt);

  /*
   * Clear the status register and set the freeze pll fields.
   */
  nUserCtlUVal &= ~HWIO_FMSK(PLL_USER_CTL_U, STATUS_REGISTER);
  nUserCtlUVal |= HWIO_FMSK(PLL_USER_CTL_U, FREEZE_PLL);
  HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL_U, pCtxt, nUserCtlUVal);

  /*
   * Read current status value.
   */
  *pnCalibration = HAL_CLK_PLL_HWIO_IN(PLL_STATUS, pCtxt);

  /*
   * Clear the bypassnl and reset fields.
   */
  nModeVal &= ~(HWIO_FMSK(PLL_MODE, PLL_RESET_N) |
                HWIO_FMSK(PLL_MODE, PLL_BYPASSNL));
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

  /*
   * Clear the freeze pll field.
   */
  nUserCtlUVal &= ~HWIO_FMSK(PLL_USER_CTL_U, FREEZE_PLL);
  HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL_U, pCtxt, nUserCtlUVal);

} /* END HAL_clk_PriusPLLDisableToSaved */


/* ===========================================================================
**  HAL_clk_PriusPLLDisableNormal
**
**  PLL shutdown.
**  When in the off state, the bias is off and draws no power.
**  This procedure results in calibration being required upon the next enable.
**
**  This procedure applies only to both Prius and Tesla PLL types.
**
** ======================================================================== */

static void HAL_clk_PriusPLLDisableNormal
(
  HAL_clk_SourceDescType *pSource
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

} /* END HAL_clk_PriusPLLDisableNormal */


/* ===========================================================================
**  HAL_clk_PriusPLLDisableToFreeze
**
**  Put PLL in the 'freeze' state.
**
**  This procedure applies only to Prius PLL types.
**
** ======================================================================== */

static void HAL_clk_PriusPLLDisableToFreeze
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
   * Only the Prius PLL supports this usage.
   */
  if (pCtxt->ePLLType != HAL_CLK_PLL_PRIUS)
  {
    ERR_FATAL("HAL_clk_PriusPLLDisableToFreeze Invalid PLL Type", 0, 0, 0);
    return;
  }

  HAL_CLK_PLL_HWIO_OUTF(PLL_MODE, pCtxt, PLL_OUTCTRL, 0);
  HAL_clk_BusyWait(HAL_CLK_PLL_OUTCTRL_OFF_US);
  HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL_U, pCtxt, FREEZE_PLL, 0x1);

} /* END HAL_clk_PriusPLLDisableToFreeze */


/* ===========================================================================
**  HAL_clk_PriusPLLDisable
**
**  The appropriate disable mode is executed based on the eMode argument.
**
** ======================================================================== */

static void HAL_clk_PriusPLLDisable
(
  HAL_clk_SourceDescType        *pSource,
  HAL_clk_SourceDisableModeType  eMode,
  void                          *pData
)
{
  switch (eMode)
  {
    case HAL_CLK_SOURCE_DISABLE_MODE_STANDBY:
      HAL_clk_PriusPLLDisableToStandby(pSource);
      break;
    case HAL_CLK_SOURCE_DISABLE_MODE_SAVE:
      HAL_clk_PriusPLLDisableToSaved(pSource, pData);
      break;
    case HAL_CLK_SOURCE_DISABLE_MODE_FREEZE:
      HAL_clk_PriusPLLDisableToFreeze(pSource);
      break;
    case HAL_CLK_SOURCE_DISABLE_MODE_NORMAL:
      HAL_clk_PriusPLLDisableNormal(pSource);
      break;
    default:
      ERR_FATAL("HAL_clk_PriusPLLDisable Invalid Parameter", 0, 0, 0);
      break;
  }

} /* END HAL_clk_PriusPLLDisable */


/* ===========================================================================
**  HAL_clk_PriusPLLIsEnabled
**
** ======================================================================== */

static boolean HAL_clk_PriusPLLIsEnabled
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

} /* END HAL_clk_PriusPLLIsEnabled */


/* ===========================================================================
**  HAL_clk_PriusPLLConfig
**
** ======================================================================== */

static void HAL_clk_PriusPLLConfig
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
      ERR_FATAL("HAL_clk_PriusPLLConfig Invalid Parameter", 0, 0, 0);
      break;
  }

} /* END HAL_clk_PriusPLLConfig */


/* ===========================================================================
**  HAL_clk_PriusPLLConfigPLLSlew
**
**  Returns:
**    boolean - TRUE if successfully configured.
**              FALSE if unable to detect that the PLL successfully locked.
** ======================================================================== */

static boolean HAL_clk_PriusPLLConfigPLLSlew
(
  HAL_clk_SourceDescType      *pSource,
  const HAL_clk_PLLConfigType *pConfig,
  boolean                      bTriggerUpdate
)
{
  uint32                  nModeVal;
  HAL_clk_PLLContextType *pCtxt;
  boolean                 bResult;

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Only the Prius PLL supports this usage.
   */
  if (pCtxt->ePLLType != HAL_CLK_PLL_PRIUS)
  {
    ERR_FATAL("HAL_clk_PriusPLLConfigPLLSlew Invalid PLL Type", 0, 0, 0);
    return FALSE;
  }

  /*
   * Program L value.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_L_VAL, pCtxt, pConfig->nL);

  /*
   * Program Alpha/AlphaU values.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_ALPHA_VAL, pCtxt, pConfig->nAlpha);
  HAL_CLK_PLL_HWIO_OUT(PLL_ALPHA_U_VAL, pCtxt, pConfig->nAlphaU);

  /*
   * [WARNING : UNTESTED FUNCTIONALITY]
   * Do not update the ALPHA_EN field during slewing.
   */

  /*
   * Check if the update will be triggered later.
   */
  if (bTriggerUpdate != TRUE)
  {
    return TRUE;
  }

  /*
   * Read the PLLx_Mode value
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pCtxt);

  /*
   * Toggle the update bit to latch the new configuration values.
   */
  nModeVal |= HWIO_FMSK(PLL_MODE, PLL_UPDATE);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

  /*
   * Wait for PLL_UPDATE to be cleared within the timeout period.
   */
  bResult =
    HAL_clk_ValidateRegClearTimeout(
      HAL_CLK_PLL_HWIO_ADDR(PLL_MODE, pCtxt),
      HWIO_FMSK(PLL_MODE, PLL_UPDATE),
      HAL_CLK_UPDATE_TIMEOUT_US);

  /*
   * Return immediately if the update failed.
   */
  if (!bResult)
  {
    ERR_FATAL("HAL_clk_PriusPLLConfigPLLSlew Update Failure", 0, 0, 0);
    return FALSE;
  }

  /*
   * Wait for 11 or more PLL clk_ref ticks for PLL_LOCK_DET to transition to 0.
   * When using a reference clock of XO, the wait requirement is 570 ns.
   */
  HAL_clk_BusyWait(1);

  /*
   * Wait for the PLL to lock within the timeout period.
   */
  bResult =
    HAL_clk_ValidateRegSetTimeout(
      HAL_CLK_PLL_HWIO_ADDR(PLL_MODE, pCtxt),
      HWIO_FMSK(PLL_MODE, PLL_LOCK_DET),
      HAL_CLK_LOCK_TIMEOUT_US);

  if (!bResult)
  {
    ERR_FATAL("HAL_clk_PriusPLLConfigPLLSlew Lock Failure", 0, 0, 0);
  }

  return bResult;

} /* END HAL_clk_PriusPLLConfigPLLSlew */


/* ===========================================================================
**  HAL_clk_PriusPLLConfigPLLNormal
**
**  Returns:
**    boolean - TRUE if successfully configured. FALSE otherwise.
** ======================================================================== */

static boolean HAL_clk_PriusPLLConfigPLLNormal
(
  HAL_clk_SourceDescType      *pSource,
  const HAL_clk_PLLConfigType *pConfig
)
{
  uint32  nModeVal, nUserVal;
  uint32  nPLLInFSMMode = 0;
  boolean bPLLEnabled = FALSE;
  HAL_clk_PLLContextType *pCtxt;

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Check PLL mode.
   */
  nPLLInFSMMode = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pCtxt) &
    HWIO_FMSK(PLL_MODE, PLL_VOTE_FSM_ENA);
  bPLLEnabled = HAL_clk_PriusPLLIsEnabled(pSource);

  /*
   * Disable the PLL.
   */
  if (bPLLEnabled)
  {
    HAL_clk_PriusPLLDisableNormal(pSource);
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
                HWIO_FMSK(PLL_USER_CTL, VCO_SEL) |
                HWIO_FMSK(PLL_USER_CTL, PRE_DIV_RATIO) |
                HWIO_FMSK(PLL_USER_CTL, POST_DIV_RATIO));

  /*
   * Find the VCO
   */
  switch (pConfig->eVCO)
  {
    case HAL_CLK_PLL_VCO4:
      nUserVal |= HWIO_FVAL(PLL_USER_CTL, VCO_SEL, 3);
      break;

    case HAL_CLK_PLL_VCO3:
      nUserVal |= HWIO_FVAL(PLL_USER_CTL, VCO_SEL, 2);
      break;

    case HAL_CLK_PLL_VCO2:
      nUserVal |= HWIO_FVAL(PLL_USER_CTL, VCO_SEL, 1);
      break;

    case HAL_CLK_PLL_VCO1:
      nUserVal |= HWIO_FVAL(PLL_USER_CTL, VCO_SEL, 0);
      break;

    default:
      ERR_FATAL("HAL_clk_PriusPLLConfigPLLNormal Invalid VCO Specification", 0, 0, 0);
      break;
  }

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
    HAL_clk_PriusPLLEnableNormal(pSource);
  }

  return TRUE;

} /* END HAL_clk_PriusPLLConfigPLLNormal */


/* ===========================================================================
**  HAL_clk_PriusPLLConfigPLL
**
**  Returns:
**    boolean - TRUE if successfully configured. FALSE otherwise.
** ======================================================================== */

static boolean HAL_clk_PriusPLLConfigPLL
(
  HAL_clk_SourceDescType      *pSource,
  const HAL_clk_PLLConfigType *pConfig,
  HAL_clk_SourceConfigMode     eMode
)
{
  boolean bResult = FALSE;

  /*
   * Program the appropriate config sequence.
   */
  if (eMode == HAL_CLK_SOURCE_CONFIG_MODE_NORMAL)
  {
    bResult = HAL_clk_PriusPLLConfigPLLNormal(pSource, pConfig);
  }
  else if(eMode == HAL_CLK_SOURCE_CONFIG_MODE_SLEW)
  {
    bResult = HAL_clk_PriusPLLConfigPLLSlew(pSource, pConfig, TRUE);
  }
  else if (eMode == HAL_CLK_SOURCE_CONFIG_MODE_PENDING)
  {
    bResult = HAL_clk_PriusPLLConfigPLLSlew(pSource, pConfig, FALSE);
  }

  return bResult;

} /* END HAL_clk_PriusPLLConfigPLL */


/* ===========================================================================
**  HAL_clk_PriusPLLDetectPLLConfig
**
** ======================================================================== */

static void HAL_clk_PriusPLLDetectPLLConfig
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
   * Get the VCO
   */
  nConfigVal = HAL_CLK_PLL_HWIO_IN(PLL_USER_CTL, pCtxt);
  pConfig->eVCO =
    (HAL_clk_PLLVCOType)((nConfigVal & HWIO_FMSK(PLL_USER_CTL, VCO_SEL))
                            >> HWIO_SHFT(PLL_USER_CTL, VCO_SEL));

  /*
   * Get the pre and post dividers.
   */
  pConfig->nPreDiv = ((nConfigVal & HWIO_FMSK(PLL_USER_CTL, PRE_DIV_RATIO))
                         >> (HWIO_SHFT(PLL_USER_CTL, PRE_DIV_RATIO))) + 1;
  pConfig->nPostDiv = ((nConfigVal & HWIO_FMSK(PLL_USER_CTL, POST_DIV_RATIO))
                >> HWIO_SHFT(PLL_USER_CTL, POST_DIV_RATIO)) + 1;

  /*
   * Get the current state of the FSM Voting Mode.
   */
  pConfig->bFsmMode = (boolean)HAL_CLK_PLL_HWIO_INF(PLL_MODE, pCtxt, PLL_VOTE_FSM_ENA);

} /* END HAL_clk_PriusPLLDetectPLLConfig */

