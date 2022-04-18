/*
==============================================================================

FILE:         HALclkLPASS.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   LPASS clocks.

   List of clock domains:
     - HAL_clk_mGCCCDSPBIMCClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/sdm660/cdsp/src/gcc/HALclkTURINGBIMC.c#1 $

==============================================================================
            Copyright (c) 2016 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/


#include <HALhwio.h>

#include "HALclkInternal.h"
#include "HALclkTest.h"
#include "HALclkGeneric.h"
#include "HALclkHWIO.h"


/*============================================================================

             DEFINITIONS AND DECLARATIONS FOR MODULE

=============================================================================*/


/* ============================================================================
**    Prototypes
** ==========================================================================*/




/* ============================================================================
**    Data
** ==========================================================================*/


/*
 * aGCCCDSPBIMCSourceMap
 *
 * GCC HW source mapping
 * 
 */
static HAL_clk_SourceMapType aGCCCDSPBIMCSourceMap[] =
{
  { HAL_CLK_SOURCE_XO,                 0 },
  { HAL_CLK_SOURCE_GPLL0,              1 },
  { HAL_CLK_SOURCE_GPLL2,              2 },
  { HAL_CLK_SOURCE_GPLL3,              3 },
  { HAL_CLK_SOURCE_GPLL1,              4 },
  { HAL_CLK_SOURCE_GPLL4,              5 },
  { HAL_CLK_SOURCE_GPLL0_DIV2,         6 },
  { HAL_CLK_SOURCE_PLLTEST,            7 },
  { HAL_CLK_SOURCE_NULL,               HAL_CLK_SOURCE_INDEX_INVALID }
};


/*
 * HAL_clk_mGCCCDSPBIMCClockDomainControl
 *
 * Functions for controlling GCC clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mGCCCDSPBIMCClockDomainControl =
{
   /* .ConfigMux          = */ HAL_clk_GenericConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .IsOn               = */ HAL_clk_GenericDomainIsOn,
   /* .pmSourceMap        = */ aGCCCDSPBIMCSourceMap
};


/*
 * HAL_clk_mGCCCDSPBIMCClockDomainControlRO
 *
 * Read-only functions for GCC clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mGCCCDSPBIMCClockDomainControlRO =
{
   /* .ConfigMux          = */ NULL,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .IsOn               = */ HAL_clk_GenericDomainIsOn,
   /* .pmSourceMap        = */ aGCCCDSPBIMCSourceMap
};


/*                           
 *  HAL_clk_mCDSPBIMCClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mCDSPBIMCClkDomainClks[] =
{
#if 0 /* not present on turing */

  {
    /* .szClockName      = */ "gcc_cdsp_bimc_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CDSP_BIMC_CBCR), HWIO_OFFS(GCC_BIMC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CDSP_BIMC_CLK
  },
#endif

#if 0 /* not present on turing */

  {
    /* .szClockName      = */ "gcc_sys_noc_cdsp_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SYS_NOC_CDSP_CBCR), HWIO_OFFS(GCC_SYSTEM_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SYS_NOC_CDSP_CLK
  },
#endif

#if 0 /* not present on turing */

  {
    /* .szClockName      = */ "gcc_turing_q6_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_TURING_Q6_AXI_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_TURING_Q6_AXI_CLK
  },
#endif

  {
    /* .szClockName      = */ "gcc_turing_q6_smmu_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_TURING_Q6_SMMU_AXI_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_TURING_Q6_SMMU_AXI_CLK
  },
  {
    /* .szClockName      = */ "gcc_turing_q6_smmu_axi_src_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_TURING_Q6_SMMU_AXI_SRC_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_TURING_Q6_SMMU_AXI_SRC_CLK
  },
};


/*
 * HAL_clk_mGCCCDSPBIMCClkDomain
 *
 * CDSPBIMC clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCCDSPBIMCClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_CDSP_BIMC_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mCDSPBIMCClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mCDSPBIMCClkDomainClks)/sizeof(HAL_clk_mCDSPBIMCClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCCDSPBIMCClockDomainControlRO,
  /* .pmNextClockDomain    = */ NULL
};

