/*
==============================================================================

FILE:         HALclkRPM.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   RPM clocks.

   List of clock domains:
     - HAL_clk_mGCCRPMClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/rpm.bf/1.8/core/systemdrivers/hal/clk/hw/sdm660/src/GCC/HALclkRPM.c#1 $

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
 *  HAL_clk_mRPMClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mRPMClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_rpm_bus_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_RPM_BUS_AHB_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_RPM_BUS_AHB_CLK
  },
  {
    /* .szClockName      = */ "gcc_rpm_proc_hclk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_RPM_PROC_HCLK_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_RPM_PROC_HCLK
  },
  {
    /* .szClockName      = */ "gcc_spdm_rpm_cy_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SPDM_RPM_CY_CBCR), HWIO_OFFS(GCC_SPDM_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SPDM_RPM_CY_CLK
  },
};


/*
 * HAL_clk_mGCCRPMClkDomain
 *
 * RPM clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCRPMClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_RPM_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mRPMClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mRPMClkDomainClks)/sizeof(HAL_clk_mRPMClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

