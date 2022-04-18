/*
==============================================================================

FILE:         HALclkMSS.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   MSS clocks.

   List of clock domains:
     - HAL_clk_mGCCMSSQ6BIMCAXIClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkMSS.c#3 $

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
 *  HAL_clk_mMSSQ6BIMCAXIClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mMSSQ6BIMCAXIClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_bimc_mss_q6_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_BIMC_MSS_Q6_AXI_CBCR), HWIO_OFFS(GCC_BIMC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_BIMC_MSS_Q6_AXI_CLK
  },
  {
    /* .szClockName      = */ "gcc_mss_q6_bimc_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_MSS_Q6_BIMC_AXI_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_MSS_Q6_BIMC_AXI_CLK
  },
#if 0 /* not present on apcs */

  {
    /* .szClockName      = */ "gcc_mss_q6_msmpu_client_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_MSS_Q6_MSMPU_CLIENT_AXI_CBCR), HWIO_OFFS(GCC_MSMPU_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_MSS_Q6_MSMPU_CLIENT_AXI_CLK
  },
#endif

};


/*
 * HAL_clk_mGCCMSSQ6BIMCAXIClkDomain
 *
 * MSSQ6BIMCAXI clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCMSSQ6BIMCAXIClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_MSS_Q6_BIMC_AXI_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mMSSQ6BIMCAXIClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mMSSQ6BIMCAXIClkDomainClks)/sizeof(HAL_clk_mMSSQ6BIMCAXIClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControlRO_2,
  /* .pmNextClockDomain    = */ NULL
};

