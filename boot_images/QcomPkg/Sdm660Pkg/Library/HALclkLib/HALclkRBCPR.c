/*
==============================================================================

FILE:         HALclkRBCPR.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   RBCPR clocks.

   List of clock domains:
     - HAL_clk_mGPURBCPRClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkRBCPR.c#1 $

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
 *  HAL_clk_mRBCPRClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mRBCPRClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gpucc_rbcpr_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GPUCC_RBCPR_CBCR), HWIO_OFFS(GPUCC_RBCPR_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GPU_TEST_GPUCC_RBCPR_CLK
  },
};


/*
 * HAL_clk_mGPURBCPRClkDomain
 *
 * RBCPR clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGPURBCPRClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GPUCC_RBCPR_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mRBCPRClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mRBCPRClkDomainClks)/sizeof(HAL_clk_mRBCPRClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGPUClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

