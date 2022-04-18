/*
==============================================================================

FILE:         HALclkPIMEM.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   PIMEM clocks.

   List of clock domains:
     - HAL_clk_mGCCPIMEMAXIClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/rpm.bf/1.8/core/systemdrivers/hal/clk/hw/sdm660/src/GCC/HALclkPIMEM.c#1 $

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
 *  HAL_clk_mPIMEMAXIClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mPIMEMAXIClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_bimc_pimem_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BIMC_PIMEM_AXI_CBCR), HWIO_OFFS(GCC_BIMC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BIMC_PIMEM_AXI_CLK
  },
  {
    /* .szClockName      = */ "gcc_pimem_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_PIMEM_AXI_CBCR), HWIO_OFFS(GCC_PIMEM_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_PIMEM_AXI_CLK
  },
  {
    /* .szClockName      = */ "gcc_sys_noc_pimem_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SYS_NOC_PIMEM_AXI_CBCR), HWIO_OFFS(GCC_SYSTEM_NOC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SYS_NOC_PIMEM_AXI_CLK
  },
};


/*
 * HAL_clk_mGCCPIMEMAXIClkDomain
 *
 * PIMEMAXI clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCPIMEMAXIClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_PIMEM_AXI_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mPIMEMAXIClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mPIMEMAXIClkDomainClks)/sizeof(HAL_clk_mPIMEMAXIClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

