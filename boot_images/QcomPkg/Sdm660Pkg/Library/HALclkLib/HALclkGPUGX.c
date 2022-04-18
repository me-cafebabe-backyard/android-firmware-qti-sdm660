/*
==============================================================================

FILE:         HALclkGPUGX.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   GPUGX clocks.

   List of clock domains:
     - HAL_clk_mGPUGFX3DClkDomain
     - HAL_clk_mGPURBBMTIMERClkDomain


   List of power domains:
     - HAL_clk_mGPUGPUGXPowerDomain



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkGPUGX.c#1 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mGPUClockDomainControl;
extern HAL_clk_ClockDomainControlType  HAL_clk_mGPUClockDomainControlRO;


/* ============================================================================
**    Data
** ==========================================================================*/


/*
 *  HAL_clk_mGFX3DClkDomainClks
 *
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mGFX3DClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gpucc_gfx3d_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GPUCC_GFX3D_CBCR), HWIO_OFFS(GPUCC_GPU_GX_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GPU_TEST_GPUCC_GFX3D_CLK
  },
  {
    /* .szClockName      = */ "gpucc_spdm_gfx3d_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GPUCC_SPDM_GFX3D_CBCR), HWIO_OFFS(GPUCC_SPDM_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GPU_TEST_GPUCC_SPDM_GFX3D_CLK
  },
};


/*
 * HAL_clk_mGPUGFX3DClkDomain
 *
 * GFX3D clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGPUGFX3DClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GPUCC_GFX3D_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mGFX3DClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mGFX3DClkDomainClks)/sizeof(HAL_clk_mGFX3DClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGPUClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*
 *  HAL_clk_mRBBMTIMERClkDomainClks
 *
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mRBBMTIMERClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gpucc_rbbmtimer_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GPUCC_RBBMTIMER_CBCR), HWIO_OFFS(GPUCC_GPU_GX_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GPU_TEST_GPUCC_RBBMTIMER_CLK
  },
};


/*
 * HAL_clk_mGPURBBMTIMERClkDomain
 *
 * RBBMTIMER clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGPURBBMTIMERClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GPUCC_RBBMTIMER_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mRBBMTIMERClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mRBBMTIMERClkDomainClks)/sizeof(HAL_clk_mRBBMTIMERClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGPUClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*
 * HAL_clk_mGPUGPUGXPowerDomain
 *
 * GPU_GX power domain.
 */
HAL_clk_PowerDomainDescType HAL_clk_mGPUGPUGXPowerDomain =
{
  /* .szPowerDomainName       = */ "VDD_GPU_GX",
  /* .nGDSCRAddr              = */ HWIO_OFFS(GPUCC_GPU_GX_GDSCR),
  /* .pmControl               = */ &HAL_clk_mGenericPowerDomainControl,
  /* .pmClockMemCore          = */ NULL,
  /* .pmClockMemPeriph        = */ NULL,
  /* .pmNextPowerDomain       = */ NULL
};

