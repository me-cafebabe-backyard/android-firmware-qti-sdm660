/*
==============================================================================

FILE:         HALclkBLSP1QUP6.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   BLSP1QUP6 clocks.

   List of clock domains:
     - HAL_clk_mGCCBLSP1QUP6I2CAPPSClkDomain
     - HAL_clk_mGCCBLSP1QUP6SPIAPPSClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/msm8998/slpi/src/gcc/HALclkBLSP1QUP6.c#1 $

==============================================================================
            Copyright (c) 2015 QUALCOMM Technologies Incorporated.
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
 *  HAL_clk_mBLSP1QUP6I2CAPPSClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mBLSP1QUP6I2CAPPSClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_blsp1_qup6_i2c_apps_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BLSP1_QUP6_I2C_APPS_CBCR), HWIO_OFFS(GCC_BLSP1_QUP6_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BLSP1_QUP6_I2C_APPS_CLK
  },
};


/*
 * HAL_clk_mGCCBLSP1QUP6I2CAPPSClkDomain
 *
 * BLSP1QUP6I2CAPPS clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP6I2CAPPSClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_BLSP1_QUP6_I2C_APPS_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mBLSP1QUP6I2CAPPSClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mBLSP1QUP6I2CAPPSClkDomainClks)/sizeof(HAL_clk_mBLSP1QUP6I2CAPPSClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mBLSP1QUP6SPIAPPSClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mBLSP1QUP6SPIAPPSClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_blsp1_qup6_spi_apps_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BLSP1_QUP6_SPI_APPS_CBCR), HWIO_OFFS(GCC_BLSP1_QUP6_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BLSP1_QUP6_SPI_APPS_CLK
  },
};


/*
 * HAL_clk_mGCCBLSP1QUP6SPIAPPSClkDomain
 *
 * BLSP1QUP6SPIAPPS clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP6SPIAPPSClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_BLSP1_QUP6_SPI_APPS_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mBLSP1QUP6SPIAPPSClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mBLSP1QUP6SPIAPPSClkDomainClks)/sizeof(HAL_clk_mBLSP1QUP6SPIAPPSClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

