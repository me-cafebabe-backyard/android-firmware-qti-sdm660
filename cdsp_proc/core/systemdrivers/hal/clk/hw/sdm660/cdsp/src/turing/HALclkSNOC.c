/*
==============================================================================

FILE:         HALclkSNOC.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   SNOC clocks.

   List of clock domains:
     - HAL_clk_mTURINGCCTURINGSNOCSWAYCLKClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/sdm660/cdsp/src/turing/HALclkSNOC.c#1 $

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
extern HAL_clk_ClockDomainControlType  HAL_clk_mTURINGClockDomainControlRO;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mCCTURINGSNOCSWAYCLKClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mCCTURINGSNOCSWAYCLKClkDomainClks[] =
{
  {
    /* .szClockName      = */ "turing_wrapper_sysnoc_sway_snoc_clk",
    /* .mRegisters       = */ { HWIO_OFFS(TURING_TURING_WRAPPER_SYSNOC_SWAY_SNOC_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_TURING_TEST_TURING_WRAPPER_SYSNOC_SWAY_SNOC_CLK
  },
};


/*
 * HAL_clk_mTURINGCCTURINGSNOCSWAYCLKClkDomain
 *
 * CCTURINGSNOCSWAYCLK clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mTURINGCCTURINGSNOCSWAYCLKClkDomain =
{
  /* .nCGRAddr             = */ 0, /* this domain does not have a cmd rcgr */
  /* .pmClocks             = */ HAL_clk_mCCTURINGSNOCSWAYCLKClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mCCTURINGSNOCSWAYCLKClkDomainClks)/sizeof(HAL_clk_mCCTURINGSNOCSWAYCLKClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mTURINGClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

