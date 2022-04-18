/*
==============================================================================

FILE:         HALclkSDCC2.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   SDCC2 clocks.

   List of clock domains:
     - HAL_clk_mGCCSDCC2APPSClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkSDCC2.c#2 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControl_1;
extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControlRO_1;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mSDCC2APPSClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mSDCC2APPSClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_sdcc2_apps_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SDCC2_APPS_CBCR), HWIO_OFFS(GCC_SDCC2_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SDCC2_APPS_CLK
  },
};


/*
 * HAL_clk_mGCCSDCC2APPSClkDomain
 *
 * SDCC2APPS clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCSDCC2APPSClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_SDCC2_APPS_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mSDCC2APPSClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mSDCC2APPSClkDomainClks)/sizeof(HAL_clk_mSDCC2APPSClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl_1,
  /* .pmNextClockDomain    = */ NULL
};

