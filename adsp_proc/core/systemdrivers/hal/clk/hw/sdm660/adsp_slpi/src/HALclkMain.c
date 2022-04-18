/*
==============================================================================

FILE:         HALclkMain.c

DESCRIPTION:
  This file contains the main platform initialization code for the clock
  HAL on the LPASS processor.


==============================================================================

                             Edit History

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/sdm660/adsp_slpi/src/HALclkMain.c#1 $

when       who     what, where, why
--------   ---     -----------------------------------------------------------
10/04/16   shm     First version for SDM660.

==============================================================================
            Copyright (c) 2016 Qualcomm Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/


#include "HALclkInternal.h"
#include "HALclkGeneric.h"
#include "HALclkGenericPLL.h"
#include "HALhwio.h"
#include "HALclkHWIO.h"


/* ============================================================================
**    Prototypes
** ==========================================================================*/

void HAL_clk_PlatformInitSources(void);


/* ============================================================================
**    Externs
** ==========================================================================*/


extern void HAL_clk_PlatformInitGCCMain(void);
extern void HAL_clk_PlatformInitLPASSMain(void);


/* ============================================================================
**    Data
** ==========================================================================*/


/*
 * HAL_clk_aInitFuncs
 *
 * Declare array of module initialization functions.
 */
static HAL_clk_InitFuncType HAL_clk_afInitFuncs[] =
{
  /*
   * Sources
   */
  HAL_clk_PlatformInitSources,
  
  /*
   * GCC
   */
  HAL_clk_PlatformInitGCCMain,

  /*
   * LPASS
   */
  HAL_clk_PlatformInitLPASSMain,

  NULL
};



uint32 HAL_clk_nHWIOBaseGCC;
uint32 HAL_clk_nHWIOBaseLPASS;


/*
 * HAL_clk_aHWIOBases
 *
 * Declare array of HWIO bases in use on this platform.
 */
static HAL_clk_HWIOBaseType HAL_clk_aHWIOBases[] =
{
  { CLK_CTL_BASE_PHYS,      CLK_CTL_BASE_SIZE,      &HAL_clk_nHWIOBaseGCC   },
  { LPASS_BASE_PHYS,        LPASS_BASE_SIZE,        &HAL_clk_nHWIOBaseLPASS },
  { 0, 0, NULL }
};


/*
 * HAL_clk_Platform;
 * Platform data.
 */
HAL_clk_PlatformType HAL_clk_Platform =
{
  HAL_clk_afInitFuncs,
  HAL_clk_aHWIOBases
};


/*
 * LPASS PLL contexts
 */
static HAL_clk_PLLContextType HAL_clk_aPLLContextLPASSPLL[] =
{
  {
    HWIO_OFFS(LPASS_LPAAUDIO_PLL_MODE),
    HAL_CLK_FMSK(LPASS_LPA_PLL_VOTE_LPASS_HW, LPAAUDIO_PLL),
    HAL_CLK_PLL_BRAMMO
  },
  {
    HWIO_OFFS(LPASS_QDSP6SS_PLL_MODE),
    {0},
    HAL_CLK_PLL_SPARK
  },
  {
    HWIO_OFFS(LPASS_LPAAUDIO_DIG_PLL_MODE),
    HAL_CLK_FMSK(LPASS_LPA_PLL_VOTE_LPASS_HW, LPAAUDIO_DIG_PLL),
    HAL_CLK_PLL_SPARK
  },
  {
    HWIO_OFFS(LPASS_SCC_PLL_MODE),
    {0},
    HAL_CLK_PLL_PEEL
  },
};


/* ============================================================================
**    Functions
** ==========================================================================*/


/* ===========================================================================
**  HAL_clk_PlatformInitSources
**
** ======================================================================== */

void HAL_clk_PlatformInitSources (void)
{
  /*
   * Install PLL handlers.
   */

  HAL_clk_InstallPLL(
      HAL_CLK_SOURCE_LPAPLL0, &HAL_clk_aPLLContextLPASSPLL[0], LPASS_BASE);

  HAL_clk_InstallPLL(
      HAL_CLK_SOURCE_LPAPLL1, &HAL_clk_aPLLContextLPASSPLL[1], LPASS_BASE);

  HAL_clk_InstallPLL(
      HAL_CLK_SOURCE_LPAPLL2, &HAL_clk_aPLLContextLPASSPLL[2], LPASS_BASE);

  HAL_clk_InstallPLL(
      HAL_CLK_SOURCE_SCCPLL0, &HAL_clk_aPLLContextLPASSPLL[3], LPASS_BASE);

} /* END HAL_clk_PlatformInitSources */


/* ===========================================================================
**  HAL_clk_Save
**
** ======================================================================== */

void HAL_clk_Save (void)
{
  /*
   * Nothing to save.
   */

} /* END HAL_clk_Save */


/* ===========================================================================
**  HAL_clk_Restore
**
** ======================================================================== */

void HAL_clk_Restore (void)
{
  /*
   * Nothing to restore.
   */
  
} /* END HAL_clk_Restore */
