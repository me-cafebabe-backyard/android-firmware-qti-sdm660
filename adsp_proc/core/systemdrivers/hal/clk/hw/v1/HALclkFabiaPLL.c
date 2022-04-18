/*
==============================================================================

FILE:         HALclkFabiaPLL.c

DESCRIPTION:
  This file contains the clock HAL code for the Fabia PLL control.
  These PLLs are of the Fabia PLL variety.

==============================================================================

                             Edit History

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/v1/HALclkFabiaPLL.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------- 
10/27/14   vt     Created

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
#include "HALclkFabiaPLL.h"
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
 * Definitions for configuring the PLL in FSM Mode
 */
#define HAL_CLK_PLL_BIAS_COUNT_VAL   (0x1 << HWIO_SHFT(PLL_MODE, PLL_BIAS_COUNT))
#define HAL_CLK_PLL_LOCK_COUNT_VAL   (0x0 << HWIO_SHFT(PLL_MODE, PLL_LOCK_COUNT))

/*
 * Definition for configuring M/N in FRAC_VAL register 
 * Note: This register will look like one of the following: 
 *        [b3,b2,b1,b0] - Format
 *        [0,0,M,N]     - USER_CTL_U.FRAC_FORMAT_SEL == 1
 *        [0,0,a1,a0]   - USER_CTL_U.FRAC_FORMAT_SEL == 0
 */
#define HAL_CLK_PLL_M_N_VAL(m,n) ((( ( m ) & 0xFF ) << 8 ) | ( ( n ) & 0xFF ))

/*
 * HAL_CLK_PLL_INIT_TIME_US
 *
 * Init time in microseconds after de-asserting PLL reset (normal mode).
 */
#define HAL_CLK_PLL_INIT_TIME_US 5


/*
 * HAL_CLK_LOCK_TIMEOUT_US
 *
 * Timeout in US for PLL_LOCK_DET to get set.
 */
#define HAL_CLK_LOCK_TIMEOUT_US 200

/*
 * HAL_CLK_UPDATE_TIMEOUT_US
 *
 * Timeout in US for PLL_UPDATE to get set.
 */
#define HAL_CLK_UPDATE_TIMEOUT_US 200

/*
 * HAL_CLK_PLL_OUTCTRL_OFF_US
 *
 * Wait after PLL_OUTCTRL off before setting freeze bit.
 */
#define HAL_CLK_PLL_OUTCTRL_OFF_US 5

/*
 * GPLL1 register interface is different than the other PLL's.
 * These are the registers/fields which are affected on non-RPM masters.
 */
#define HWIO_GCC_GPLL1_STATUS_PLL_ACTIVE_FLAG_BMSK 0x20000


/* ============================================================================
**    Data Declarations
** ==========================================================================*/

/*
 * HAL_clk_FabiaPLLControl
 *
 * Control function array for the Fabia PLLs.
 */
HAL_clk_SourceControlType HAL_clk_FabiaPLLControl =
{
  /* .Enable          = */ HAL_clk_FabiaPLLEnable,
  /* .Disable         = */ HAL_clk_FabiaPLLDisable,
  /* .IsEnabled       = */ HAL_clk_FabiaPLLIsEnabled,
  /* .Config          = */ HAL_clk_FabiaPLLConfig,
  /* .ConfigPLL       = */ HAL_clk_FabiaPLLConfigPLL,
  /* .DetectPLLConfig = */ HAL_clk_FabiaPLLDetectPLLConfig,
  /* .EnableVote      = */ HAL_clk_FabiaPLLEnableVote,
  /* .DisableVote     = */ HAL_clk_FabiaPLLDisableVote,
  /* .IsVoteEnabled   = */ HAL_clk_FabiaPLLIsVoteEnabled,
};


/*============================================================================

               FUNCTION DEFINITIONS FOR MODULE

============================================================================*/


/* ===========================================================================
**  HAL_clk_FabiaPLLEnableVote
**
** ======================================================================== */

static boolean HAL_clk_FabiaPLLEnableVote
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
   * Wait for the PLL to go active during the 15 us timeout period.
   */
  bResult =
    HAL_clk_ValidateRegSetTimeout(
      HAL_CLK_PLL_HWIO_ADDR(PLL_MODE, pCtxt),
      HWIO_FMSK(PLL_MODE, PLL_ACTIVE_FLAG),
      HAL_CLK_LOCK_TIMEOUT_US);

  return bResult;

} /* END HAL_clk_FabiaPLLEnableVote */


/* ===========================================================================
**  HAL_clk_FabiaPLLDisableVote
**
** ======================================================================== */

static void HAL_clk_FabiaPLLDisableVote
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

} /* END HAL_clk_FabiaPLLDisableVote */


/* ===========================================================================
**  HAL_clk_FabiaPLLIsVoteEnabled
**
** ======================================================================== */

static boolean HAL_clk_FabiaPLLIsVoteEnabled
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

} /* END HAL_clk_FabiaPLLIsVoteEnabled */


/* ===========================================================================
**  HAL_clk_FabiaPLLEnableFromStandby
**
**  PLL bringup from standby state.
**  When in the standby state, the bias is on and draws 75-100 micro amps.
**  This procedure skips calibration.
**
**  This procedure applies only to Fabia PLL types.
**
**  The following fields must have remained unchanged from the values present
**  when the HAL_clk_FabiaPLLDisableToStandby function was executed:
**  - PLL_L_VAL
**  - PLL_ALPHA_VAL
**
**  Returns:
**    boolean - TRUE if successfully enabled. FALSE otherwise.
** ======================================================================== */

static boolean HAL_clk_FabiaPLLEnableFromStandby
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
   * Set OPMODE to Run State
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_OPMODE, pCtxt, HAL_PLL_OPMODE_RUN);

  /*
   * Wait for the PLL to lock during the 15 us timeout period.
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
    return FALSE;
  }

  /*
   * Read current mode value.
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pCtxt);

  /*
   * Assert the output control field.
   */
  nModeVal |= HWIO_FMSK(PLL_MODE, PLL_OUTCTRL);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

  /*
   * Read current user ctl value.
   */
  nUserCtlUVal = HAL_CLK_PLL_HWIO_IN(PLL_USER_CTL_U, pCtxt);

  /*
   * Turn off "Bias On In Standby" to set back to default value.
   */
  nUserCtlUVal &= ~HWIO_FMSK(PLL_USER_CTL_U, BIAS_ON_IN_STANDBY);
  HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL_U, pCtxt, nUserCtlUVal);

  return TRUE;

} /* END HAL_clk_FabiaPLLEnableFromStandby */


/* ===========================================================================
**  HAL_clk_FabiaPLLEnableFromSaved
**
**  PLL bringup with restore state.
**  When in the saved state, the bias is off and draws no power.
**  This procedure skips calibration.
**
**  This procedure applies only to Fabia PLL types.
**
**  The following fields must have remained unchanged from the values present
**  when the HAL_clk_FabiaPLLDisableToSaved function was executed:
**  - PLL_L_VAL
**  - PLL_ALPHA_VAL
**
**  Returns:
**    boolean - TRUE if successfully enabled. FALSE otherwise.
** ======================================================================== */

static boolean HAL_clk_FabiaPLLEnableFromSaved
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
   * Validate that we have a place to store the calibration.
   */
  if (pnCalibration == NULL)
  {
    return FALSE;
  }

  /*
   * Read current mode value.
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pCtxt);

  /*
   * Assert the reset_n field to put the PLL in standby state.
   */
  nModeVal |= HWIO_FMSK(PLL_MODE, PLL_RESET_N);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

  /*
   * Read current user ctl value.
   */
  nUserCtlUVal = HAL_CLK_PLL_HWIO_IN(PLL_USER_CTL_U, pCtxt);

  /*
   * Assert the state enable field to force the state change.
   */
  nUserCtlUVal |= HWIO_FMSK(PLL_USER_CTL_U, WRITE_STATE_EN);
  HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL_U, pCtxt, nUserCtlUVal);

  /*
   * Restore the saved state.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_FREQ_CTL, pCtxt, *pnCalibration);

  /*
   * Read current mode value.
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pCtxt);

  /*
   * Assert the update field.
   */
  nModeVal |= HWIO_FMSK(PLL_MODE, PLL_UPDATE);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

  /*
   * Wait for the PLL to latch the state.
   */
  bResult =
    HAL_clk_ValidateRegSetTimeout(
      HAL_CLK_PLL_HWIO_ADDR(PLL_MODE, pCtxt),
      HWIO_FMSK(PLL_MODE, PLL_ACK_LATCH),
      HAL_CLK_LOCK_TIMEOUT_US);

  /*
   * Return immediately if the latch failed.
   */
  if (!bResult)
  {
    return FALSE;
  }

  /*
   * Read current mode value.
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pCtxt);

  /*
   * De-assert the update field.
   */
  nModeVal &= ~HWIO_FMSK(PLL_MODE, PLL_UPDATE);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

  /*
   * Wait for latch to go low.
   */
  bResult =
    HAL_clk_ValidateRegClearTimeout(
      HAL_CLK_PLL_HWIO_ADDR(PLL_MODE, pCtxt),
      HWIO_FMSK(PLL_MODE, PLL_ACK_LATCH),
      HAL_CLK_UPDATE_TIMEOUT_US);

  /*
   * Return immediately if the ack latch doesn't go low.
   */
  if (!bResult)
  {
    return FALSE;
  }

  /*
   * Read current user ctl value.
   */
  nUserCtlUVal = HAL_CLK_PLL_HWIO_IN(PLL_USER_CTL_U, pCtxt);

  /*
   * Clear the write state enable bit to return back to default val.
   */
  nUserCtlUVal &= ~HWIO_FMSK(PLL_USER_CTL_U, WRITE_STATE_EN);
  HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL_U, pCtxt, nUserCtlUVal);

  /*
   * Set OPMODE to Run State
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_OPMODE, pCtxt, HAL_PLL_OPMODE_RUN);

  /*
   * Wait for the PLL to lock during the 15 us timeout period.
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
    return FALSE;
  }

  /*
   * Read current mode value.
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pCtxt);

  /*
   * Assert the output control field.
   */
  nModeVal |= HWIO_FMSK(PLL_MODE, PLL_OUTCTRL);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

  return TRUE;

} /* END HAL_clk_FabiaPLLEnableFromSaved */


/* ===========================================================================
**  HAL_clk_FabiaPLLEnableNormal
**
**  PLL initial bringup.
**  When in the off state, the bias is off and draws no power.
**  This procedure results in calibration being performed.
**
**  This procedure applies only to both Fabia PLL types.
**
**  Returns:
**    boolean - TRUE if successfully enabled. FALSE otherwise.
** ======================================================================== */

static boolean HAL_clk_FabiaPLLEnableNormal
(
  HAL_clk_SourceDescType *pSource
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
   * Read current mode value.
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pCtxt);

  /*
   * Assert the reset_n field to put the PLL in standby state.
   */
  nModeVal |= HWIO_FMSK(PLL_MODE, PLL_RESET_N);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

  /*
   * Set OPMODE to Run State
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_OPMODE, pCtxt, HAL_PLL_OPMODE_RUN);

  /*
   * Wait for the PLL to lock during the 15 us timeout period.
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
    return FALSE;
  }

  /*
   * Read current mode value.
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pCtxt);

  /*
   * Assert the output control field.
   */
  nModeVal |= HWIO_FMSK(PLL_MODE, PLL_OUTCTRL);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

  return TRUE;

} /* END HAL_clk_FabiaPLLEnableNormal */


/* ===========================================================================
**  HAL_clk_FabiaPLLEnableFromFreeze
**
**  PLL bringup from 'freeze' state.
**  This procedure skips calibration.
**
**  This procedure applies only to Fabia PLL types.
**
**  The following bit must be set per HPG to prevent calibration loss
**  when the HAL_clk_FabiaPLLEnableFromFreeze function was executed:
**  - PLL_TEST_CTL_U[CAL_CODE_UPDATE]
**
**  Returns:
**    boolean - TRUE if successfully enabled. FALSE otherwise.
** ======================================================================== */

static boolean HAL_clk_FabiaPLLEnableFromFreeze
(
  HAL_clk_SourceDescType *pSource
)
{
  HAL_clk_PLLContextType *pCtxt;
  boolean                 bResult;
  uint32                  nModeVal;

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;


  /*
   * Set OPMODE to Run State
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_OPMODE, pCtxt, HAL_PLL_OPMODE_RUN);

  /*
   * Wait for the PLL to lock during the 15 us timeout period.
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
    return FALSE;
  }

  /*
   * Read current mode value.
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pCtxt);

  /*
   * Assert the output control field.
   */
  nModeVal |= HWIO_FMSK(PLL_MODE, PLL_OUTCTRL);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

  return TRUE;

} /* END HAL_clk_FabiaPLLEnableFromFreeze */


/* ===========================================================================
**  HAL_clk_FabiaPLLEnable
**
**  The appropriate enable mode is executed based on the eMode parameter.
**
**  Returns:
**    boolean - TRUE if successfully enabled. FALSE otherwise.
** ======================================================================== */

static boolean HAL_clk_FabiaPLLEnable
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
  if (HAL_clk_FabiaPLLIsEnabled(pSource))
  {
    return TRUE;
  }

  switch (eMode)
  {
    case HAL_CLK_SOURCE_DISABLE_MODE_STANDBY:
      bResult = HAL_clk_FabiaPLLEnableFromStandby(pSource);
      break;
    case HAL_CLK_SOURCE_DISABLE_MODE_SAVE:
      bResult = HAL_clk_FabiaPLLEnableFromSaved(pSource, pData);
      break;
    case HAL_CLK_SOURCE_DISABLE_MODE_FREEZE:
      bResult = HAL_clk_FabiaPLLEnableFromFreeze(pSource);
      break;
    case HAL_CLK_SOURCE_DISABLE_MODE_NORMAL:
      bResult = HAL_clk_FabiaPLLEnableNormal(pSource);
      break;
    default:
      bResult = FALSE;
      break;
  }

  return bResult;

} /* END HAL_clk_FabiaPLLEnable */


/* ===========================================================================
**  HAL_clk_FabiaPLLDisableToStandby
**
**  PLL shutdown to standby state.
**  This procedure leaves the bias on:
**    skips calibration when enabling via HAL_clk_FabiaPLLEnableFromStandby.
**    draws 75-100 micro amps while in standby mode.
**
**  This procedure applies only to Fabia PLL types.
**
** ======================================================================== */

static void HAL_clk_FabiaPLLDisableToStandby
(
  HAL_clk_SourceDescType *pSource
)
{
  uint32  nModeVal, nUserCtlUVal;
  HAL_clk_PLLContextType *pCtxt;

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Read current user ctl value.
   */
  nUserCtlUVal = HAL_CLK_PLL_HWIO_IN(PLL_USER_CTL_U, pCtxt);

  /*
   * Clear the write state enable bit to return back to default val.
   */
  nUserCtlUVal |= HWIO_FMSK(PLL_USER_CTL_U, BIAS_ON_IN_STANDBY);
  HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL_U, pCtxt, nUserCtlUVal);

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
   * Set OPMODE to Standby State
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_OPMODE, pCtxt, HAL_PLL_OPMODE_STANDBY);

} /* END HAL_clk_FabiaPLLDisableToStandby */


/* ===========================================================================
**  HAL_clk_FabiaPLLDisableToSaved
**
**  PLL shutdown with save state.
**  When in the saved state, the bias is off and draws no power.
**  The calibration data is saved in *pData to be used later when
**  calling HAL_clk_FabiaPLLEnableFromSaved.
**
**  This procedure applies only to Fabia PLL types.
**
**  NOTE: the void *pData argument is expected to be pointing to a
**  uint32. Therefore it MUST be recasted to a (uint32 *) when using it.
**
** ======================================================================== */

static void HAL_clk_FabiaPLLDisableToSaved
(
  HAL_clk_SourceDescType *pSource,
  void                   *pData
)
{
  uint32 nModeVal;
  HAL_clk_PLLContextType *pCtxt;
  uint32 *pnCalibration = (uint32 *) pData;

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Validate that we have a place to store the calibration.
   */
  if (pnCalibration == NULL)
  {
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
   * Set OPMODE to Standby State
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_OPMODE, pCtxt, HAL_PLL_OPMODE_STANDBY);

  /*
   * Read current status value.
   */
  *pnCalibration = HAL_CLK_PLL_HWIO_IN(PLL_STATUS, pCtxt);

  /*
   * Read current mode value.
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pCtxt);

  /*
   * Clear the reset field.
   */
  nModeVal &= ~HWIO_FMSK(PLL_MODE, PLL_RESET_N);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

} /* END HAL_clk_FabiaPLLDisableToSaved */


/* ===========================================================================
**  HAL_clk_FabiaPLLDisableNormal
**
**  PLL shutdown.
**  When in the off state, the bias is off and draws no power.
**  This procedure results in calibration being required upon the next enable.
**
**  This procedure applies only to both Fabia PLL types.
**
** ======================================================================== */

static void HAL_clk_FabiaPLLDisableNormal
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
  nModeVal &= ~HWIO_FMSK(PLL_MODE, PLL_RESET_N);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pCtxt, nModeVal);

  /*
   * Set OPMODE to Standby State
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_OPMODE, pCtxt, HAL_PLL_OPMODE_STANDBY);

} /* END HAL_clk_FabiaPLLDisableNormal */


/* ===========================================================================
**  HAL_clk_FabiaPLLDisableToFreeze
**
**  Put PLL in the 'freeze' state.
**
**  This procedure applies only to Fabia PLL types.
**
** ======================================================================== */

static void HAL_clk_FabiaPLLDisableToFreeze
(
  HAL_clk_SourceDescType *pSource
)
{
  HAL_clk_PLLContextType *pCtxt;
  uint32  nModeVal;

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
   * Set OPMODE to Standby State 
   * CP TODO: In MPSS, "Freeze" state is actually standby with bias 
   *   -- Need to check to see if we need to do different for freeze hw 
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_OPMODE, pCtxt, HAL_PLL_OPMODE_STANDBY);

} /* END HAL_clk_FabiaPLLDisableToFreeze */


/* ===========================================================================
**  HAL_clk_FabiaPLLDisable
**
**  The appropriate disable mode is executed based on the eMode argument.
**
** ======================================================================== */

static void HAL_clk_FabiaPLLDisable
(
  HAL_clk_SourceDescType        *pSource,
  HAL_clk_SourceDisableModeType  eMode,
  void                          *pData
)
{
  switch (eMode)
  {
    case HAL_CLK_SOURCE_DISABLE_MODE_STANDBY:
      HAL_clk_FabiaPLLDisableToStandby(pSource);
      break;
    case HAL_CLK_SOURCE_DISABLE_MODE_SAVE:
      HAL_clk_FabiaPLLDisableToSaved(pSource, pData);
      break;
    case HAL_CLK_SOURCE_DISABLE_MODE_FREEZE:
      HAL_clk_FabiaPLLDisableToFreeze(pSource);
      break;
    case HAL_CLK_SOURCE_DISABLE_MODE_NORMAL:
      HAL_clk_FabiaPLLDisableNormal(pSource);
      break;
    default:
      break;
  }

} /* END HAL_clk_FabiaPLLDisable */


/* ===========================================================================
**  HAL_clk_FabiaPLLIsEnabled
**
** ======================================================================== */

static boolean HAL_clk_FabiaPLLIsEnabled
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

} /* END HAL_clk_FabiaPLLIsEnabled */


/* ===========================================================================
**  HAL_clk_FabiaPLLConfig
**
** ======================================================================== */

static void HAL_clk_FabiaPLLConfig
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

    case HAL_CLK_CONFIG_PLL_EVEN_OUTPUT_ENABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pCtxt, PLLOUT_EVEN, 1);
      break;

    case HAL_CLK_CONFIG_PLL_EVEN_OUTPUT_DISABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pCtxt, PLLOUT_EVEN, 0);
      break;

    case HAL_CLK_CONFIG_PLL_ODD_OUTPUT_ENABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pCtxt, PLLOUT_ODD, 1);
      break;

    case HAL_CLK_CONFIG_PLL_ODD_OUTPUT_DISABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pCtxt, PLLOUT_ODD, 0);
      break;

    case HAL_CLK_CONFIG_PLL_MAIN_OUTPUT_ENABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pCtxt, PLLOUT_MAIN, 1);
      break;

    case HAL_CLK_CONFIG_PLL_MAIN_OUTPUT_DISABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pCtxt, PLLOUT_MAIN, 0);
      break;
    default:
      break;
  }

} /* END HAL_clk_FabiaPLLConfig */


/* ===========================================================================
**  HAL_clk_FabiaPLLConfigPLLSlew
**
**  Returns:
**    boolean - TRUE if successfully configured.
**              FALSE if unable to detect that the PLL successfully locked.
** ======================================================================== */

static boolean HAL_clk_FabiaPLLConfigPLLSlew
(
  HAL_clk_SourceDescType      *pSource,
  const HAL_clk_PLLConfigType *pConfig,
  boolean                      bTriggerUpdate
)
{
  uint32                  nModeVal, nUserUVal;
  HAL_clk_PLLContextType *pCtxt;
  boolean                 bResult;

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Program L value.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_L_VAL, pCtxt, pConfig->nL);

  /*
   *  Check value format to used based on whether M and N are set.
   */
  if ((pConfig->nM != 0) || (pConfig->nN != 0))
  {
    /*
     * Program M and N value since they are populated 
     * and likely more accurate than the Alpha value
     */
    nUserUVal = HAL_CLK_PLL_HWIO_IN(PLL_USER_CTL_U, pCtxt);
    nUserUVal |= HWIO_FMSK(PLL_USER_CTL_U, FRAC_FORMAT_SEL);
    HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL_U, pCtxt, nUserUVal);
    HAL_CLK_PLL_HWIO_OUT(PLL_FRAC_VAL, pCtxt, 
                         HAL_CLK_PLL_M_N_VAL(pConfig->nM,pConfig->nN));
  }
  else
  {
    /*
     * Program alpha value since M and N are not populated.
     * Likely more accurate than the M and N value.
     */
    nUserUVal = HAL_CLK_PLL_HWIO_IN(PLL_USER_CTL_U, pCtxt);
    nUserUVal &= ~HWIO_FMSK(PLL_USER_CTL_U, FRAC_FORMAT_SEL);
    HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL_U, pCtxt, nUserUVal);
    HAL_CLK_PLL_HWIO_OUT(PLL_FRAC_VAL, pCtxt, pConfig->nAlpha);
  }

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
   * Wait for PLL_UPDATE to be cleared during the timeout period.
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
    return FALSE;
  }

  /*
   * Wait 2 ticks for the PLL to change.  This is required since 
   * PLL_LOCK_DET may not transition to 0 if the change is small.
   */
  HAL_clk_BusyWait(1);

  /*
   * Wait for the PLL to lock during the timeout period.
   */
  bResult =
    HAL_clk_ValidateRegSetTimeout(
      HAL_CLK_PLL_HWIO_ADDR(PLL_MODE, pCtxt),
      HWIO_FMSK(PLL_MODE, PLL_LOCK_DET),
      HAL_CLK_LOCK_TIMEOUT_US);

  return bResult;

} /* END HAL_clk_FabiaPLLConfigPLLSlew */


/* ===========================================================================
**  HAL_clk_FabiaPLLConfigPLLNormal
**
**  Returns:
**    boolean - TRUE if successfully configured. FALSE otherwise.
** ======================================================================== */

static boolean HAL_clk_FabiaPLLConfigPLLNormal
(
  HAL_clk_SourceDescType      *pSource,
  const HAL_clk_PLLConfigType *pConfig
)
{
  uint32  nModeVal, nUserVal, nUserUVal;
  uint32  nPLLInFSMMode = 0;
  boolean bPLLEnabled = FALSE;
  HAL_clk_PLLContextType *pCtxt;

  /* CP TODO: Is this still needed?  Not quite sure... */

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Check PLL mode.
   */
  nPLLInFSMMode = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pCtxt) &
    HWIO_FMSK(PLL_MODE, PLL_VOTE_FSM_ENA);
  bPLLEnabled = HAL_clk_FabiaPLLIsEnabled(pSource);

  /*
   * Disable the PLL.
   */
  if (bPLLEnabled)
  {
    HAL_clk_FabiaPLLDisableNormal(pSource);
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
   * Program L value.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_L_VAL, pCtxt, pConfig->nL);

  /*
   *  Check value format to used based on whether M and N are set.
   */
  if ((pConfig->nM != 0) || (pConfig->nN != 0))
  {
    /*
     * Program M and N value since they are populated 
     * and likely more accurate than the Alpha value
     */
    nUserUVal = HAL_CLK_PLL_HWIO_IN(PLL_USER_CTL_U, pCtxt);
    nUserUVal |= HWIO_FMSK(PLL_USER_CTL_U, FRAC_FORMAT_SEL);
    HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL_U, pCtxt, nUserUVal);
    HAL_CLK_PLL_HWIO_OUT(PLL_FRAC_VAL, pCtxt, 
                         HAL_CLK_PLL_M_N_VAL(pConfig->nM,pConfig->nN));
  }
  else
  {
    /*
     * Program alpha value since M and N are not populated.
     * Likely more accurate than the M and N value.
     */
    nUserUVal = HAL_CLK_PLL_HWIO_IN(PLL_USER_CTL_U, pCtxt);
    nUserUVal &= ~HWIO_FMSK(PLL_USER_CTL_U, FRAC_FORMAT_SEL);
    HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL_U, pCtxt, nUserUVal);
    HAL_CLK_PLL_HWIO_OUT(PLL_FRAC_VAL, pCtxt, pConfig->nAlpha);
  }

  /*
   * Get the CONFIG value and clear out fields we will configure.
   */
  nUserVal  =  HAL_CLK_PLL_HWIO_IN(PLL_USER_CTL, pCtxt);
  nUserVal &= ~(HWIO_FMSK(PLL_USER_CTL, PRE_DIV_RATIO) |
                HWIO_FMSK(PLL_USER_CTL, POST_DIV_RATIO_ODD) |
                HWIO_FMSK(PLL_USER_CTL, POST_DIV_RATIO_EVEN));

  /*
   * Program the pre-div value (div-1 to div-8).
   */
  if (pConfig->nPreDiv <= 8 && pConfig->nPreDiv > 0)
  {
    nUserVal |= HWIO_FVAL(PLL_USER_CTL, PRE_DIV_RATIO, (pConfig->nPreDiv - 1));
  }

  /*
   * Program the post-div value.  First, check if it's even or odd.
   */
  if ( pConfig->nPostDiv & 0x1 )
  {
    /*
     * Post divider is odd, post divider field 
     * value is equal to the actual value.
     */
    nUserVal |=
      ((pConfig->nPostDiv) << HWIO_SHFT(PLL_USER_CTL, POST_DIV_RATIO_ODD));
  }
  else if ( pConfig->nPostDiv > 0 )
  {
    /*
     * Post divider is even and non-zero. Post divider 
     * field value is one less than the actual value. 
     */
    nUserVal |=
      ((pConfig->nPostDiv - 1) << HWIO_SHFT(PLL_USER_CTL, POST_DIV_RATIO_EVEN));
  }

  /*
   * Finally program the USER_CTL register.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL, pCtxt, nUserVal);

  /*
   * Set behavior of PLL_LOCK_DET to always use fine grained.
   */
  HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL_U, pCtxt, USE_ONLY_FINE_LOCK_DET, 1);

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
    HAL_clk_FabiaPLLEnableNormal(pSource);
  }

  return TRUE;

} /* END HAL_clk_FabiaPLLConfigPLLNormal */


/* ===========================================================================
**  HAL_clk_FabiaPLLConfigPLL
**
**  Returns:
**    boolean - TRUE if successfully configured. FALSE otherwise.
** ======================================================================== */

static boolean HAL_clk_FabiaPLLConfigPLL
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
    bResult = HAL_clk_FabiaPLLConfigPLLNormal(pSource, pConfig);
  }
  else if(eMode == HAL_CLK_SOURCE_CONFIG_MODE_SLEW)
  {
    bResult = HAL_clk_FabiaPLLConfigPLLSlew(pSource, pConfig, TRUE);
  }
  else if (eMode == HAL_CLK_SOURCE_CONFIG_MODE_PENDING)
  {
    bResult = HAL_clk_FabiaPLLConfigPLLSlew(pSource, pConfig, FALSE);
  }

  return bResult;

} /* END HAL_clk_FabiaPLLConfigPLL */


/* ===========================================================================
**  HAL_clk_FabiaPLLDetectPLLConfig
**
** ======================================================================== */

static void HAL_clk_FabiaPLLDetectPLLConfig
(
  HAL_clk_SourceDescType *pSource,
  HAL_clk_PLLConfigType  *pConfig
)
{
  HAL_clk_PLLContextType *pCtxt;
  uint32                  nRegVal;

  /*
   * Get the PLL context.
   */
  pCtxt = (HAL_clk_PLLContextType *)pSource->pContext;

  /*
   * Clear all config values not modified in this function.
   */
  pConfig->nM = 0;
  pConfig->nN = 0;
  pConfig->nAlphaU = 0;
  pConfig->nVCOMultiplier = 0;

  /*
   * The Fabia architecture abstracts the VCO logic away from the user so just
   * default this to the first VCO for initialization purposes.
   */
  pConfig->eVCO = HAL_CLK_PLL_VCO1;

  /*
   * Read L value.
   */
  pConfig->nL = HAL_CLK_PLL_HWIO_IN(PLL_L_VAL, pCtxt);

  /*
   * Read fractional value.
   */
  nRegVal = HAL_CLK_PLL_HWIO_INF(PLL_FRAC_VAL, pCtxt, PLL_FRAC_VAL);

  /*
   * If fractional format is set then extract into M and N fields.
   */
  if (HAL_CLK_PLL_HWIO_INF(PLL_USER_CTL_U, pCtxt, FRAC_FORMAT_SEL))
  {
    /*
     * Extract M value.
     */
    pConfig->nM =
      HAL_CLK_PLL_HWIO_INFV(PLL_FRAC_VAL, pCtxt, M_VAL, nRegVal);

    /*
     * Extract N value.
     */
    pConfig->nN =
      HAL_CLK_PLL_HWIO_INFV(PLL_FRAC_VAL, pCtxt, N_VAL, nRegVal);
  }

  /*
   * Otherwise extract into Alpha field.
   */
  else
  {
    pConfig->nAlpha = nRegVal;
  }
  
  /*
   * Default oscillator source to XO.
   */
  pConfig->eSource = HAL_CLK_SOURCE_XO;

  /*
   * Read USER_CTL register.
   */
  nRegVal = HAL_CLK_PLL_HWIO_IN(PLL_USER_CTL, pCtxt);

  /*
   * Get the pre divider.
   */
  pConfig->nPreDiv =
    HAL_CLK_PLL_HWIO_INFV(PLL_USER_CTL, pCtxt, PRE_DIV_RATIO, nRegVal) + 1;

  /*
   * Get the post divider.
   */
  if (HAL_CLK_PLL_HWIO_INFV(PLL_USER_CTL, pCtxt, POST_DIV_RATIO_EVEN, nRegVal))
  {
    pConfig->nPostDiv =
      HAL_CLK_PLL_HWIO_INFV(PLL_USER_CTL, pCtxt, POST_DIV_RATIO_EVEN, nRegVal)
      + 1;
  }
  else
  {
    pConfig->nPostDiv =
      HAL_CLK_PLL_HWIO_INFV(PLL_USER_CTL, pCtxt, POST_DIV_RATIO_ODD, nRegVal);

    /*
     * Add 1 for case where field is 0.  Otherwise leave as is.
     */
    if (pConfig->nPostDiv == 0)
    {
      pConfig->nPostDiv++;
    }
  }

} /* END HAL_clk_FabiaPLLDetectPLLConfig */

