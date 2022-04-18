/*
==============================================================================

FILE:         HALclkBLSP1QUP4.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   BLSP1QUP4 clocks.

   List of clock domains:
     - HAL_clk_mGCCBLSP1QUP4I2CAPPSClkDomain
     - HAL_clk_mGCCBLSP1QUP4SPIAPPSClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/msm8998/adsp/src/gcc/HALclkBLSP1QUP4.c#1 $

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
 *  HAL_clk_mBLSP1QUP4I2CAPPSClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mBLSP1QUP4I2CAPPSClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_blsp1_qup4_i2c_apps_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BLSP1_QUP4_I2C_APPS_CBCR), HWIO_OFFS(GCC_BLSP1_QUP4_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BLSP1_QUP4_I2C_APPS_CLK
  },
};


/*
 * HAL_clk_mGCCBLSP1QUP4I2CAPPSClkDomain
 *
 * BLSP1QUP4I2CAPPS clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP4I2CAPPSClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_BLSP1_QUP4_I2C_APPS_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mBLSP1QUP4I2CAPPSClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mBLSP1QUP4I2CAPPSClkDomainClks)/sizeof(HAL_clk_mBLSP1QUP4I2CAPPSClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mBLSP1QUP4SPIAPPSClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mBLSP1QUP4SPIAPPSClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_blsp1_qup4_spi_apps_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BLSP1_QUP4_SPI_APPS_CBCR), HWIO_OFFS(GCC_BLSP1_QUP4_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BLSP1_QUP4_SPI_APPS_CLK
  },
};


/*
 * HAL_clk_mGCCBLSP1QUP4SPIAPPSClkDomain
 *
 * BLSP1QUP4SPIAPPS clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP4SPIAPPSClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_BLSP1_QUP4_SPI_APPS_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mBLSP1QUP4SPIAPPSClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mBLSP1QUP4SPIAPPSClkDomainClks)/sizeof(HAL_clk_mBLSP1QUP4SPIAPPSClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

