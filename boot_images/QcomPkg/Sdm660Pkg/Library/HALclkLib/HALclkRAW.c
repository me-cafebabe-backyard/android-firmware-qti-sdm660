/*
==============================================================================

FILE:         HALclkRAW.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   RAW clocks.

   List of clock domains:
     - HAL_clk_mGPUXOClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkRAW.c#1 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mGPUClockDomainControl;
extern HAL_clk_ClockDomainControlType  HAL_clk_mGPUClockDomainControlRO;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mXOClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mXOClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gpucc_cxo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GPUCC_CXO_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
};


/*
 * HAL_clk_mGPUXOClkDomain
 *
 * XO clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGPUXOClkDomain =
{
  /* .nCGRAddr             = */ 0, /* this domain does not have a cmd rcgr */
  /* .pmClocks             = */ HAL_clk_mXOClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mXOClkDomainClks)/sizeof(HAL_clk_mXOClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGPUClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

