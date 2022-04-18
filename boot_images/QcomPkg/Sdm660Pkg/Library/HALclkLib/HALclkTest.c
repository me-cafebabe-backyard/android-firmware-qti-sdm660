/*
==============================================================================

FILE:         HALclkTest.c

DESCRIPTION:
  This file contains the implementation for the clock frequency measurement
  for the clock HAL.

==============================================================================

                             Edit History


when       who     what, where, why
--------   ---     -----------------------------------------------------------
11/15/11   vs      Created.

==============================================================================
      Copyright (c) 2011-2016 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/

#include <HALhwio.h>

#include "HALclkInternal.h"

/*
 * Chipset specific header files.
 */
#include "HALclkHWIO.h"
#include "HALclkTest.h"


/*============================================================================

             DEFINITIONS AND DECLARATIONS FOR MODULE

=============================================================================*/


/* ============================================================================
**    Defines
** ==========================================================================*/


/*
 * Define the initial count for the ring-oscillator comparator.  Arbitrary
 * but high enough to get good accuracy.
 */
#define HAL_CLK_RO_TCXO_CNT_VAL   0x8000

/*
 * This value defines the minimal valid count for a clock under test. If the
 * original count is at or below this value, there is a good chance that the
 * HW has malfunctioned during the measurement phase. In this case we allow
 * the reset loop to time out and escape the infinite loop.
 */
#define HAL_CLK_MINIMAL_COUNT       0xC0


/*============================================================================

               FUNCTION DEFINITIONS FOR MODULE

============================================================================*/


/* ===========================================================================
**  HAL_clk_CalcClockFreq
**
** ======================================================================== */

void HAL_clk_CalcClockFreq
(
  HAL_clk_ClockHandleType  pClockHandle,
  uint32                   *pnFreqHz
)
{
  boolean bIsClockSupportedIsOn;
  uint32 nCount, nCountShort;
  uint32 nDenominator;
  uint32 nTestClockSel;
  uint32 nTestClockType;
  uint32 nMultiplier = 4, nPreMultiplier = 1;

  HAL_clk_ClockDescType *pmClockDesc = (HAL_clk_ClockDescType *)pClockHandle;

  /*
   * Sanity
   */
  if (pmClockDesc == NULL || pnFreqHz == NULL)
  {
    return;
  }

  /*
   * Initialize the return value.
   */
  *pnFreqHz = 0;

  /*
   * Before performing the clock frequency calculation try to determine
   * whether the clock is actually "on". If the clock is in the "off" state,
   * return '0' and don't proceed with the computation.
   */
  bIsClockSupportedIsOn = HAL_clk_IsClockSupported (pClockHandle,
                                                    HAL_CLK_CLOCK_API_ISON);

  /*
   * Verify the clock is "on" if possible; otherwise, proceed with the
   * computation. If the clock is "off", then return '0' right away.
   */
  if (bIsClockSupportedIsOn)
  {
    if (!HAL_clk_IsClockOn(pClockHandle))
    {
      return;
    }
  }

  /*
   * Get the debug clock value.
   */
  nTestClockType = pmClockDesc->nTestClock & HAL_CLK_TEST_TYPE_MASK;
  nTestClockSel  = pmClockDesc->nTestClock & HAL_CLK_TEST_SEL_MASK;

  /*
   * Program the substem specific debug clock registers
   */
  switch (nTestClockType)
  {
    /*
     * GCC clocks.
     */
    case HAL_CLK_GCC_TEST:
      HWIO_OUTF(GCC_GCC_DEBUG_CLK_CTL, MUX_SEL, nTestClockSel);
      break;

    /*
     * MMSS clocks.
     */
    case HAL_CLK_MMSS_TEST:
      nPreMultiplier = 3;
      //HWIO_OUTF(GCC_GCC_DEBUG_CLK_CTL, CLK_ENABLE, 1);
      // HWIO_OUTF(GCC_GCC_DEBUG_CLK_CTL, MUX_SEL, nTestClockSel);
      HWIO_OUTF(MMSS_DEBUG_CLK_CTL, MUX_SEL, nTestClockSel);
      HWIO_OUTF(MMSS_DEBUG_CLK_CTL, CLK_ENABLE, 1);
	  HWIO_OUTF(MMSS_DEBUG_CLK_CTL, DBG_CLK_DIV, nPreMultiplier-1);
      HWIO_OUTF(GCC_GCC_DEBUG_CLK_CTL, MUX_SEL,
        HAL_CLK_GCC_TEST_MMSS_GCC_DBG_CLK & HAL_CLK_TEST_SEL_MASK);
      break;
	  
	 /*
	 *GPU clocks.
	 */
	case HAL_CLK_GPU_TEST:
	      nPreMultiplier = 3;
		HWIO_OUTF(GPUCC_DEBUG_CLK_CTL, MUX_SEL, nTestClockSel);
      HWIO_OUTF(GPUCC_DEBUG_CLK_CTL, CLK_ENABLE, 1);
	  HWIO_OUTF(GPUCC_DEBUG_CLK_CTL, DBG_CLK_DIV, nPreMultiplier-1);
      //HWIO_OUTF(GCC_GCC_DEBUG_CLK_CTL, MUX_SEL, nTestClockSel);
      HWIO_OUTF(GCC_GCC_DEBUG_CLK_CTL, MUX_SEL,
        HAL_CLK_GCC_TEST_GPU_GCC_DBG_CLK & HAL_CLK_TEST_SEL_MASK);
      break;

    /*
     * APCS clocks.
     */
    case HAL_CLK_APCS_TEST:
      if (pmClockDesc->nTestClock == HAL_CLK_APCS_TEST_CCI_CLK)
      {
        nPreMultiplier = 1;
        HWIO_OUTF(APCS_ALIAS0_GLB_CLK_DIAG, DBG_CDIV, 0);

        HWIO_OUTF(APCS_ALIAS0_GLB_CLK_DIAG, DBG_CLK_LVL1_SEL, 2);
        HWIO_OUTF(APCS_ALIAS0_GLB_CLK_DIAG, DBG_CLK_LVL2_SEL, 0);
        HWIO_OUTF(APCS_ALIAS0_GLB_CLK_DIAG, DBG_CLK_LVL3_SEL, 0);

        HWIO_OUTF(GCC_GCC_DEBUG_CLK_CTL, MUX_SEL,
          HAL_CLK_GCC_TEST_HMSS_GCC_DBG_CLK & HAL_CLK_TEST_SEL_MASK);
      }
      break;

    /*
     * APCS0 core clocks.
     */
    case HAL_CLK_APCS0_TEST_CORE:
      nMultiplier = 4;
      nPreMultiplier = 1;

      HWIO_OUTF(APCS_ALIAS0_GLB_CLK_DIAG, DBG_CDIV, 0);

      HWIO_OUTF(APCS_ALIAS0_GLB_CLK_DIAG, DBG_CLK_LVL1_SEL, 0);
      HWIO_OUTF(APCS_ALIAS0_GLB_CLK_DIAG, DBG_CLK_LVL2_SEL, 0);
      HWIO_OUTF(APCS_ALIAS0_GLB_CLK_DIAG, DBG_CLK_LVL3_SEL, 0);

      HWIO_OUTF(GCC_GCC_DEBUG_CLK_CTL, MUX_SEL,
        HAL_CLK_GCC_TEST_HMSS_GCC_DBG_CLK & HAL_CLK_TEST_SEL_MASK);
      break;

    /*
     * APCS1 core clocks.
     */
    case HAL_CLK_APCS1_TEST_CORE:
      nMultiplier = 8;
      nPreMultiplier = 1;

      HWIO_OUTF(APCS_ALIAS0_GLB_CLK_DIAG, DBG_CDIV, 0);

      HWIO_OUTF(APCS_ALIAS0_GLB_CLK_DIAG, DBG_CLK_LVL1_SEL, 1);
      HWIO_OUTF(APCS_ALIAS0_GLB_CLK_DIAG, DBG_CLK_LVL2_SEL, 0);
      HWIO_OUTF(APCS_ALIAS0_GLB_CLK_DIAG, DBG_CLK_LVL3_SEL, 0);

      HWIO_OUTF(GCC_GCC_DEBUG_CLK_CTL, MUX_SEL,
        HAL_CLK_GCC_TEST_HMSS_GCC_DBG_CLK & HAL_CLK_TEST_SEL_MASK);
      break;

    /*
     * Unknown
     */
    default:
      *pnFreqHz = 0;
      return;
  }

  /*
   * Divide the input clock since it might be too high for the frequency
   * measurement hardware.
   */
  HWIO_OUTF(GCC_GCC_DEBUG_CLK_CTL, CLK_ENABLE, 1);
  HWIO_OUTF(GCC_GCC_DEBUG_CLK_CTL, POST_DIV, nMultiplier ? nMultiplier - 1 : 0);

  /*
   * Config XO DIV4 comparator clock
   */
  HWIO_OUTF(GCC_GCC_XO_DIV4_CBCR, CLK_ENABLE, 1);

  /*-----------------------------------------------------------------------*/
  /* Short cycle.                                                          */
  /*-----------------------------------------------------------------------*/

  /*
   * Start with counter disabled
   */
  HWIO_OUTF(GCC_CLOCK_FRQ_MEASURE_CTL, CNT_EN, 0);

  /*
   * Program the starting counter value, high enough to get good accuracy
   */
  HWIO_OUTF(GCC_CLOCK_FRQ_MEASURE_CTL, XO_DIV4_TERM_CNT, 0);

  /*
   * Start the counting
   */
  HWIO_OUTF(GCC_CLOCK_FRQ_MEASURE_CTL, CNT_EN, 1);

  HAL_clk_BusyWait(5);

  /*
   * Wait for the counters to finish.
   */
  while (HWIO_INF(GCC_CLOCK_FRQ_MEASURE_STATUS, XO_DIV4_CNT_DONE) == 0);

  /*
   * Turn off test clock and read count
   */
  HWIO_OUT(GCC_CLOCK_FRQ_MEASURE_CTL, 0);
  nCountShort = HWIO_INF(GCC_CLOCK_FRQ_MEASURE_STATUS, MEASURE_CNT);

  /*-----------------------------------------------------------------------*/
  /* Long cycle.                                                           */
  /*-----------------------------------------------------------------------*/

  /*
   * Start with counter disabled
   */
  HWIO_OUTF(GCC_CLOCK_FRQ_MEASURE_CTL, CNT_EN, 0);

  /*
   * Program the starting counter value, high enough to get good accuracy
   */
  HWIO_OUTF(GCC_CLOCK_FRQ_MEASURE_CTL, XO_DIV4_TERM_CNT, HAL_CLK_RO_TCXO_CNT_VAL);

  /*
   * Start the counting
   */
  HWIO_OUTF(GCC_CLOCK_FRQ_MEASURE_CTL, CNT_EN, 1);

  HAL_clk_BusyWait(5);

  /*
   * Wait for the counters to finish.
   */
  while (HWIO_INF(GCC_CLOCK_FRQ_MEASURE_STATUS, XO_DIV4_CNT_DONE) == 0);

  /*
   * Turn off test clock and read count
   */
  HWIO_OUT(GCC_CLOCK_FRQ_MEASURE_CTL, 0);
  nCount = HWIO_INF(GCC_CLOCK_FRQ_MEASURE_STATUS, MEASURE_CNT);

  /*-----------------------------------------------------------------------*/
  /* Compute results.                                                      */
  /*-----------------------------------------------------------------------*/

  /*
   * Remove the divider.
   */
  HWIO_OUTF(GCC_GCC_DEBUG_CLK_CTL, POST_DIV, 0x0);

  /*
   * Calculate the frequency.  Function is provided by
   * Power Control 42.8.1.2 Measurement technique
   * f ring = f tcxo/4 * (Nring + 1.5) / (TCtcxo + 3.5)
   *
   * The formula below is the equivalent one converted
   * to integer arithmetic.
   *
   * We add half of the denominator value to the dividend
   * to guard against rounding errors inherent to
   * integer arithmetic.
   */
  nDenominator = HAL_CLK_RO_TCXO_CNT_VAL * 2 + 7;

  if (nCount != nCountShort)
  {
    *pnFreqHz = (uint32)(((9600 * (uint64)nCount + 14400) + nDenominator / 2) / nDenominator * 1000);
  }
  else
  {
    *pnFreqHz = 0;
  }

  /*
   * Take into account the multiplication factor
   */
  *pnFreqHz *= nMultiplier * nPreMultiplier;

} /* END HAL_clk_CalcClockFreq */

