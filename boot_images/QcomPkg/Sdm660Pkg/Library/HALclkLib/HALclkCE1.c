/*
==============================================================================

FILE:         HALclkCE1.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   CE1 clocks.

   List of clock domains:
     - HAL_clk_mGCCCE1ClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkCE1.c#2 $

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
 *  HAL_clk_mCE1ClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mCE1ClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_ce1_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_CE1_CBCR), HWIO_OFFS(GCC_CE1_BCR), HAL_CLK_FMSK(PROC_CLK_BRANCH_ENA_VOTE, CE1_CLK_ENA) },
    /* .pmControl        = */ &HAL_clk_mGenericClockControlRO,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_CE1_CLK
  },
};


/*
 * HAL_clk_mGCCCE1ClkDomain
 *
 * CE1 clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCCE1ClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_CE1_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mCE1ClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mCE1ClkDomainClks)/sizeof(HAL_clk_mCE1ClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControlRO_1,
  /* .pmNextClockDomain    = */ NULL
};

