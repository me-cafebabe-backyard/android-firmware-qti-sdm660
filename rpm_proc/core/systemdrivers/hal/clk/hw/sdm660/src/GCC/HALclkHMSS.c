/*
==============================================================================

FILE:         HALclkHMSS.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   HMSS clocks.

   List of clock domains:
     - HAL_clk_mGCCBIMCHMSSAXIClkDomain
     - HAL_clk_mGCCHMSSAHBClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/rpm.bf/1.8/core/systemdrivers/hal/clk/hw/sdm660/src/GCC/HALclkHMSS.c#2 $

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
 *  HAL_clk_mHMSSAHBClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mHMSSAHBClkDomainClks[] =
{

  {
    /* .szClockName      = */ "gcc_hmss_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_HMSS_AHB_CBCR), 0, HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, HMSS_AHB_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_HMSS_AHB_CLK
  },

#if 0 /* not present on rpm */
  {
    /* .szClockName      = */ "gcc_sys_noc_hmss_ahb_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SYS_NOC_HMSS_AHB_CBCR), HWIO_OFFS(GCC_SYSTEM_NOC_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, SYS_NOC_HMSS_AHB_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SYS_NOC_HMSS_AHB_CLK
  },
#endif
};


/*
 * HAL_clk_mGCCHMSSAHBClkDomain
 *
 * HMSSAHB clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCHMSSAHBClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_HMSS_AHB_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mHMSSAHBClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mHMSSAHBClkDomainClks)/sizeof(HAL_clk_mHMSSAHBClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};
