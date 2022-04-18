/*
==============================================================================

FILE:         HALclkDEBUG.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   DEBUG clocks.

   List of clock domains:
     - HAL_clk_mGCCGCCDEBUGPREDIVCLKWITHTCKClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/rpm.bf/1.8/core/systemdrivers/hal/clk/hw/sdm660/src/GCC/HALclkDEBUG.c#1 $

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
 *  HAL_clk_mGCCDEBUGPREDIVCLKWITHTCKClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mGCCDEBUGPREDIVCLKWITHTCKClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_spdm_debug_cy_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SPDM_DEBUG_CY_CBCR), HWIO_OFFS(GCC_SPDM_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
};


/*
 * HAL_clk_mGCCGCCDEBUGPREDIVCLKWITHTCKClkDomain
 *
 * GCCDEBUGPREDIVCLKWITHTCK clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCGCCDEBUGPREDIVCLKWITHTCKClkDomain =
{
  /* .nCGRAddr             = */ 0, /* this domain does not have a cmd rcgr */
  /* .pmClocks             = */ HAL_clk_mGCCDEBUGPREDIVCLKWITHTCKClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mGCCDEBUGPREDIVCLKWITHTCKClkDomainClks)/sizeof(HAL_clk_mGCCDEBUGPREDIVCLKWITHTCKClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

