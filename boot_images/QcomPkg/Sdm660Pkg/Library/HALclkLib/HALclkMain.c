/*
==============================================================================

FILE:         HALclkMain.c

DESCRIPTION:
  This file contains the main platform initialization code for the clock
  HAL on the apcs processor.


==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkMain.c#3 $

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
#include "Library/HALclkSharedLib/HALclkGenericPLL.h"
#include "HALhwio.h"
#include "HALclkHWIO.h"
#include "DDIPlatformInfo.h"
#include "Drivers/ClockDxe/ClockDriver.h"

/* ============================================================================
**    Prototypes
** ==========================================================================*/

void HAL_clk_PlatformInitSources(void);


/* ============================================================================
**    Externs
** ==========================================================================*/


extern void HAL_clk_PlatformInitGCCMain(void);
extern void HAL_clk_PlatformInitGPUMain(void);
extern void HAL_clk_PlatformInitMMSSMain(void);
extern void HAL_clk_PlatformInitAPCSMain(void);



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
   * GPU
   */
  HAL_clk_PlatformInitGPUMain,

  /*
   * MMSS
   */
  HAL_clk_PlatformInitMMSSMain,

  /*
   * APCS
   */
  HAL_clk_PlatformInitAPCSMain,

  NULL
};



size_t HAL_clk_nHWIOBaseGCC;
size_t HAL_clk_nHWIOBaseGPU;
size_t HAL_clk_nHWIOBaseMMSS;
size_t HAL_clk_nHWIOBaseHMSS;
size_t HAL_clk_nHWIOBaseSecCtrl;
size_t HAL_clk_nHWIOBaseCoreTopCsr;


/*
 * HAL_clk_aHWIOBases
 *
 * Declare array of HWIO bases in use on this platform.
 */
static HAL_clk_HWIOBaseType HAL_clk_aHWIOBases[] =
{

  { CLK_CTL_BASE_PHYS,          CLK_CTL_BASE_SIZE,          &HAL_clk_nHWIOBaseGCC        },
  { A5X_BASE_PHYS,              A5X_BASE_SIZE,              &HAL_clk_nHWIOBaseGPU        },
  { MMSS_BASE_PHYS,             MMSS_BASE_SIZE,             &HAL_clk_nHWIOBaseMMSS       },
  { HMSS_BASE_PHYS,             HMSS_BASE_SIZE,             &HAL_clk_nHWIOBaseHMSS       },
  { SECURITY_CONTROL_BASE_PHYS, SECURITY_CONTROL_BASE_SIZE, &HAL_clk_nHWIOBaseSecCtrl    },
  { CORE_TOP_CSR_BASE_PHYS,     CORE_TOP_CSR_BASE_SIZE,     &HAL_clk_nHWIOBaseCoreTopCsr },

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
 * GCC PLL contexts
 */
static HAL_clk_PLLContextType HAL_clk_aPLLContextGCCPLL[] =
{

  {
    HWIO_OFFS(GCC_GPLL0_MODE),
    HAL_CLK_FMSK(GCC_APCS_GPLL_ENA_VOTE, GPLL0),
    HAL_CLK_PLL_SPARK
  },

  {
    HWIO_OFFS(GCC_GPLL1_MODE),
    HAL_CLK_FMSK(GCC_APCS_GPLL_ENA_VOTE, GPLL1),
    HAL_CLK_PLL_SPARK
  },

  {
    HWIO_OFFS(GCC_GPLL4_MODE),
    HAL_CLK_FMSK(GCC_APCS_GPLL_ENA_VOTE, GPLL4),
    HAL_CLK_PLL_SPARK
  },

  {
    HWIO_OFFS(GCC_GPLL5_MODE),
    HAL_CLK_FMSK(GCC_APCS_GPLL_ENA_VOTE, GPLL5),
    HAL_CLK_PLL_SPARK
  },

};


/*
 * GPU PLL contexts
 */
static HAL_clk_PLLContextType HAL_clk_aPLLContextGPUPLL[] =
{

  {
    HWIO_OFFS(GPUCC_GPU_PLL0_PLL_MODE),
    {0},
    HAL_CLK_PLL_SPARK
  },

  {
    HWIO_OFFS(GPUCC_GPU_PLL1_PLL_MODE),
    {0},
    HAL_CLK_PLL_SPARK
  },

};


/*
 * MMSS PLL contexts
 */
static HAL_clk_PLLContextType HAL_clk_aPLLContextMMSSPLL[] =
{

  {
    HWIO_OFFS(MMSS_MMPLL0_PLL_MODE),
    HAL_CLK_FMSK(MMSS_PLL_VOTE_APCS, ENABLE_MMPLL0),
    HAL_CLK_PLL_SPARK
  },

  {
    HWIO_OFFS(MMSS_MMPLL1_PLL_MODE),
    HAL_CLK_FMSK(MMSS_PLL_VOTE_APCS, ENABLE_MMPLL1),
    HAL_CLK_PLL_SPARK
  },

  {
    HWIO_OFFS(MMSS_MMPLL3_PLL_MODE),
    {0},
    HAL_CLK_PLL_SPARK
  },

  {
    HWIO_OFFS(MMSS_MMPLL4_PLL_MODE),
    {0},
    HAL_CLK_PLL_SPARK
  },

  {
    HWIO_OFFS(MMSS_MMPLL5_PLL_MODE),
    {0},
    HAL_CLK_PLL_SPARK
  },

  {
    HWIO_OFFS(MMSS_MMPLL6_PLL_MODE),
    HAL_CLK_FMSK(MMSS_PLL_VOTE_APCS, ENABLE_MMPLL6),
    HAL_CLK_PLL_SPARK
  },

  {
    HWIO_OFFS(MMSS_MMPLL7_PLL_MODE),
    {0},
    HAL_CLK_PLL_SPARK
  },

  {
    HWIO_OFFS(MMSS_MMPLL8_PLL_MODE),
    {0},
    HAL_CLK_PLL_SPARK
  },

  {
    HWIO_OFFS(MMSS_MMPLL10_PLL_MODE),
    {0},
    HAL_CLK_PLL_BRAMMO
  },


};

/*
 * HMSS PLL contexts
 */
static HAL_clk_PLLContextType HAL_clk_aPLLContextAPCSPLL[] =
{

  {
    HWIO_OFFS(APCS_C0_PLL_MODE),
    {0},
    HAL_CLK_PLL_AGERA
  },

  {
    HWIO_OFFS(APCS_C1_PLL_MODE),
    {0},
    HAL_CLK_PLL_AGERA
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
    HAL_CLK_SOURCE_GPLL0, &HAL_clk_aPLLContextGCCPLL[0], CLK_CTL_BASE);

  HAL_clk_InstallPLL(
      HAL_CLK_SOURCE_GPLL1, &HAL_clk_aPLLContextGCCPLL[1], CLK_CTL_BASE);

  HAL_clk_InstallPLL(
    HAL_CLK_SOURCE_GPLL4, &HAL_clk_aPLLContextGCCPLL[2], CLK_CTL_BASE);

  HAL_clk_InstallPLL(
    HAL_CLK_SOURCE_GPLL5, &HAL_clk_aPLLContextGCCPLL[3], CLK_CTL_BASE);

  HAL_clk_InstallPLL(
    HAL_CLK_SOURCE_GPUPLL0, &HAL_clk_aPLLContextGPUPLL[0], A5X_BASE);

  HAL_clk_InstallPLL(
    HAL_CLK_SOURCE_GPUPLL1, &HAL_clk_aPLLContextGPUPLL[1], A5X_BASE);

  HAL_clk_InstallPLL(
    HAL_CLK_SOURCE_MMPLL0, &HAL_clk_aPLLContextMMSSPLL[0], MMSS_BASE);

  HAL_clk_InstallPLL(
    HAL_CLK_SOURCE_MMPLL1, &HAL_clk_aPLLContextMMSSPLL[1], MMSS_BASE);

  HAL_clk_InstallPLL(
    HAL_CLK_SOURCE_MMPLL3, &HAL_clk_aPLLContextMMSSPLL[2], MMSS_BASE);

  HAL_clk_InstallPLL(
    HAL_CLK_SOURCE_MMPLL4, &HAL_clk_aPLLContextMMSSPLL[3], MMSS_BASE);

  HAL_clk_InstallPLL(
    HAL_CLK_SOURCE_MMPLL5, &HAL_clk_aPLLContextMMSSPLL[4], MMSS_BASE);

  HAL_clk_InstallPLL(
    HAL_CLK_SOURCE_MMPLL6, &HAL_clk_aPLLContextMMSSPLL[5], MMSS_BASE);

  HAL_clk_InstallPLL(
    HAL_CLK_SOURCE_MMPLL7, &HAL_clk_aPLLContextMMSSPLL[6], MMSS_BASE);

  HAL_clk_InstallPLL(
      HAL_CLK_SOURCE_MMPLL8, &HAL_clk_aPLLContextMMSSPLL[7], MMSS_BASE);

  HAL_clk_InstallPLL(
      HAL_CLK_SOURCE_MMPLL10, &HAL_clk_aPLLContextMMSSPLL[8], MMSS_BASE);

  HAL_clk_InstallPLL(
    HAL_CLK_SOURCE_APCSPLL0, &HAL_clk_aPLLContextAPCSPLL[0], HMSS_BASE);

  HAL_clk_InstallPLL(
    HAL_CLK_SOURCE_APCSPLL1, &HAL_clk_aPLLContextAPCSPLL[1], HMSS_BASE);


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


