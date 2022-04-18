/*
==============================================================================

FILE:         HALclkGPU.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   GPU clocks.

   List of clock domains:
     - HAL_clk_mGCCGPUBIMCGFXClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkGPU.c#1 $

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
**    Externs
** ==========================================================================*/

extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControl_2;
extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControlRO_2;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mGPUBIMCGFXClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mGPUBIMCGFXClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_bimc_gfx_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BIMC_GFX_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BIMC_GFX_CLK
  },
  {
    /* .szClockName      = */ "gcc_gpu_bimc_gfx_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_GPU_BIMC_GFX_CBCR), HWIO_OFFS(GCC_GPU_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_GPU_BIMC_GFX_CLK
  },
  {
    /* .szClockName      = */ "gcc_gpu_bimc_gfx_src_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_GPU_BIMC_GFX_SRC_CBCR), HWIO_OFFS(GCC_GPU_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_GPU_BIMC_GFX_SRC_CLK
  },
  {
    /* .szClockName      = */ "gcc_gpu_snoc_dvm_gfx_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_GPU_SNOC_DVM_GFX_CBCR), HWIO_OFFS(GCC_GPU_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_GPU_SNOC_DVM_GFX_CLK
  },
};


/*
 * HAL_clk_mGCCGPUBIMCGFXClkDomain
 *
 * GPUBIMCGFX clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCGPUBIMCGFXClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_GPU_BIMC_GFX_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mGPUBIMCGFXClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mGPUBIMCGFXClkDomainClks)/sizeof(HAL_clk_mGPUBIMCGFXClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControlRO_2,
  /* .pmNextClockDomain    = */ NULL
};

