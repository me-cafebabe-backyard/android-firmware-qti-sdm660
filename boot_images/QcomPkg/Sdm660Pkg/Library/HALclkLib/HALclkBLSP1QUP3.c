/*
==============================================================================

FILE:         HALclkBLSP1QUP3.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   BLSP1QUP3 clocks.

   List of clock domains:
     - HAL_clk_mGCCBLSP1QUP3I2CAPPSClkDomain
     - HAL_clk_mGCCBLSP1QUP3SPIAPPSClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkBLSP1QUP3.c#2 $

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
extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControl_1;
extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControlRO_1;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mBLSP1QUP3I2CAPPSClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mBLSP1QUP3I2CAPPSClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_blsp1_qup3_i2c_apps_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BLSP1_QUP3_I2C_APPS_CBCR), HWIO_OFFS(GCC_BLSP1_QUP3_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BLSP1_QUP3_I2C_APPS_CLK
  },
};


/*
 * HAL_clk_mGCCBLSP1QUP3I2CAPPSClkDomain
 *
 * BLSP1QUP3I2CAPPS clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP3I2CAPPSClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_BLSP1_QUP3_I2C_APPS_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mBLSP1QUP3I2CAPPSClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mBLSP1QUP3I2CAPPSClkDomainClks)/sizeof(HAL_clk_mBLSP1QUP3I2CAPPSClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl_1,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mBLSP1QUP3SPIAPPSClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mBLSP1QUP3SPIAPPSClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_blsp1_qup3_spi_apps_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BLSP1_QUP3_SPI_APPS_CBCR), HWIO_OFFS(GCC_BLSP1_QUP3_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BLSP1_QUP3_SPI_APPS_CLK
  },
};


/*
 * HAL_clk_mGCCBLSP1QUP3SPIAPPSClkDomain
 *
 * BLSP1QUP3SPIAPPS clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP3SPIAPPSClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_BLSP1_QUP3_SPI_APPS_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mBLSP1QUP3SPIAPPSClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mBLSP1QUP3SPIAPPSClkDomainClks)/sizeof(HAL_clk_mBLSP1QUP3SPIAPPSClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

