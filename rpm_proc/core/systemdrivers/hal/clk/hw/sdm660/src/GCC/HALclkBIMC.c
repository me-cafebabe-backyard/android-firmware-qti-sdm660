/*
==============================================================================

FILE:         HALclkBIMC.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   BIMC clocks.

   List of clock domains:
     - HAL_clk_mGCCBIMCClkDomain
     - HAL_clk_mGCCBIMCDDRXOClkDomain


   List of power domains:
     - HAL_clk_mGCCBIMCPowerDomain



==============================================================================

$Header: //components/rel/rpm.bf/1.8/core/systemdrivers/hal/clk/hw/sdm660/src/GCC/HALclkBIMC.c#1 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControl;
extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControlRO;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mBIMCClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mBIMCClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_bimc_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BIMC_CBCR), HWIO_OFFS(GCC_BIMC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BIMC_CLK
  },
  {
    /* .szClockName      = */ "gcc_spdm_bimc_cy_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SPDM_BIMC_CY_CBCR), HWIO_OFFS(GCC_SPDM_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SPDM_BIMC_CY_CLK
  },
};


/*
 * HAL_clk_mGCCBIMCClkDomain
 *
 * BIMC clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCBIMCClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_BIMC_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mBIMCClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mBIMCClkDomainClks)/sizeof(HAL_clk_mBIMCClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mBIMCDDRXOClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mBIMCDDRXOClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_bimc_dtts_xo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BIMC_DTTS_XO_CBCR), HWIO_OFFS(GCC_BIMC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BIMC_DTTS_XO_CLK
  },
  {
    /* .szClockName      = */ "gcc_bimc_xo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BIMC_XO_CBCR), HWIO_OFFS(GCC_BIMC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BIMC_XO_CLK
  },
  {
    /* .szClockName      = */ "gcc_cfg_noc_ddr_cfg_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CFG_NOC_DDR_CFG_CBCR), HWIO_OFFS(GCC_CONFIG_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CFG_NOC_DDR_CFG_CLK
  },
#if 0 /* not present on rpm */

  {
    /* .szClockName      = */ "gcc_cnoc_bus_timeout5_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT5_AHB_CBCR), HWIO_OFFS(GCC_CNOC_BUS_TIMEOUT5_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CNOC_BUS_TIMEOUT5_AHB_CLK
  },
#endif

  {
    /* .szClockName      = */ "gcc_ddr_dim_cfg_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_DDR_DIM_CFG_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_DDR_DIM_CFG_CLK
  },
};


/*
 * HAL_clk_mGCCBIMCDDRXOClkDomain
 *
 * BIMCDDRXO clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCBIMCDDRXOClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_BIMC_DDR_XO_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mBIMCDDRXOClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mBIMCDDRXOClkDomainClks)/sizeof(HAL_clk_mBIMCDDRXOClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*
 * HAL_clk_mGCCBIMCPowerDomain
 *
 * BIMC power domain.
 */
HAL_clk_PowerDomainDescType HAL_clk_mGCCBIMCPowerDomain =
{
  /* .szPowerDomainName       = */ "VDD_BIMC",
  /* .nGDSCRAddr              = */ HWIO_OFFS(GCC_BIMC_GDSCR),
  /* .pmControl               = */ &HAL_clk_mGenericPowerDomainControl,
  /* .pmNextPowerDomain       = */ NULL
};

