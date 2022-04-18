/*
==============================================================================

FILE:         HALclkMain.c

DESCRIPTION:
  This file contains the main platform initialization code for the clock
  HAL on the turing processor.


==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/sdm660/cdsp/src/HALclkMain.c#1 $

==============================================================================
            Copyright (c) 2016 QUALCOMM Technologies Incorporated.
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
extern void HAL_clk_PlatformInitTURINGMain(void);


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
   * TURING
   */
  HAL_clk_PlatformInitGCCMain,
  HAL_clk_PlatformInitTURINGMain,

  NULL
};



uint32 HAL_clk_nHWIOBaseGCC;
uint32 HAL_clk_nHWIOBaseTURING;
uint32 HAL_clk_nHWIOBaseTCSR;
uint32 HAL_clk_nHWIOBaseSecurityControl;

/*
 * HAL_clk_aHWIOBases
 *
 * Declare array of HWIO bases in use on this platform.
 */
static HAL_clk_HWIOBaseType HAL_clk_aHWIOBases[] =
{

  { CLK_CTL_BASE_PHYS,            CLK_CTL_BASE_SIZE,             &HAL_clk_nHWIOBaseGCC},
  { TURING_BASE_PHYS,             TURING_BASE_SIZE,              &HAL_clk_nHWIOBaseTURING},
  { CORE_TOP_CSR_BASE_PHYS,       CORE_TOP_CSR_BASE_SIZE,        &HAL_clk_nHWIOBaseTCSR },
  { SECURITY_CONTROL_BASE_PHYS,   SECURITY_CONTROL_BASE_SIZE,    &HAL_clk_nHWIOBaseSecurityControl },
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
 * TURING PLL contexts
 */
static HAL_clk_PLLContextType HAL_clk_aPLLContextTURINGPLL[] =
{

  {
    HWIO_OFFS(TURING_TURING_DIG_PLL_MODE),
    HAL_CLK_FMSK(TURING_LPA_PLL_VOTE_TURINGQ6,TURING_DIG_PLL),
    HAL_CLK_PLL_SPARK,
  },

  {
    HWIO_OFFS(TURING_QDSP6SS_PLL_MODE),
    {0},
    HAL_CLK_PLL_SPARK,
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
      HAL_CLK_SOURCE_TURINGPLL0, &HAL_clk_aPLLContextTURINGPLL[0], TURING_BASE);

  HAL_clk_InstallPLL(
      HAL_CLK_SOURCE_TURINGPLL1, &HAL_clk_aPLLContextTURINGPLL[1], TURING_BASE);


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


