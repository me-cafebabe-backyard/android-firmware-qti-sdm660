/*
==============================================================================

FILE:         HALclkSCC100.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   SCC100 clocks.

   List of clock domains:
     - HAL_clk_mLPASSSCC100MClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/sdm660/adsp_slpi/src/lpass/HALclkSCC100.c#1 $

==============================================================================
            Copyright (c) 2016 Qualcomm Technologies Incorporated.
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

extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControl_1;
extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControlRO_1;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mSCC100MClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mSCC100MClkDomainClks[] =
{
  {
    /* .szClockName      = */ "island_scc_qup_i2c1_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_ISLAND_SCC_QUP_I2C1_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_ISLAND_SCC_QUP_I2C1_CLK
  },
  {
    /* .szClockName      = */ "island_scc_qup_i2c2_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_ISLAND_SCC_QUP_I2C2_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_ISLAND_SCC_QUP_I2C2_CLK
  },
  {
    /* .szClockName      = */ "island_scc_qup_i2c3_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_ISLAND_SCC_QUP_I2C3_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_ISLAND_SCC_QUP_I2C3_CLK
  },
  {
    /* .szClockName      = */ "island_scc_qup_spi1_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_ISLAND_SCC_QUP_SPI1_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_ISLAND_SCC_QUP_SPI1_CLK
  },
  {
    /* .szClockName      = */ "island_scc_qup_spi2_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_ISLAND_SCC_QUP_SPI2_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_ISLAND_SCC_QUP_SPI2_CLK
  },
  {
    /* .szClockName      = */ "island_scc_qup_spi3_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_ISLAND_SCC_QUP_SPI3_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_ISLAND_SCC_QUP_SPI3_CLK
  },
};


/*
 * HAL_clk_mLPASSSCC100MClkDomain
 *
 * SCC100M clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSSCC100MClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_SCC_100M_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mSCC100MClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mSCC100MClkDomainClks)/sizeof(HAL_clk_mSCC100MClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl_1,
  /* .pmNextClockDomain    = */ NULL
};

