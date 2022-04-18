/*
==============================================================================

FILE:         HALclkAXI.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   AXI clocks.

   List of clock domains:
     - HAL_clk_mTURINGCCTURINGAXIMCLKClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/sdm660/cdsp/src/turing/HALclkAXI.c#1 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mTURINGClockDomainControl;

/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mCCTURINGAXIMCLKClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mCCTURINGAXIMCLKClkDomainClks[] =
{
  {
    /* .szClockName      = */ "q6ss_q6_axim_clk",
    /* .mRegisters       = */ { HWIO_OFFS(TURING_Q6SS_Q6_AXIM_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
  {
    /* .szClockName      = */ "turing_wrapper_q6_smmu_axi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(TURING_TURING_WRAPPER_Q6_SMMU_AXI_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
};


/*
 * HAL_clk_mTURINGCCTURINGAXIMCLKClkDomain
 *
 * CCTURINGAXIMCLK clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mTURINGCCTURINGAXIMCLKClkDomain =
{
  /* .nCGRAddr             = */ 0, /* this domain does not have a cmd rcgr */
  /* .pmClocks             = */ HAL_clk_mCCTURINGAXIMCLKClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mCCTURINGAXIMCLKClkDomainClks)/sizeof(HAL_clk_mCCTURINGAXIMCLKClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mTURINGClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

