/*
==============================================================================

FILE:         HALclkCAMSSMCLK2.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   CAMSSMCLK2 clocks.

   List of clock domains:
     - HAL_clk_mMMSSMCLK2ClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkCAMSSMCLK2.c#2 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mMMSSClockDomainControl_2;
extern HAL_clk_ClockDomainControlType  HAL_clk_mMMSSClockDomainControlRO_2;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mMCLK2ClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mMCLK2ClkDomainClks[] =
{
  {
    /* .szClockName      = */ "mmss_camss_mclk2_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_MCLK2_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_MCLK2_CLK
  },
};


/*
 * HAL_clk_mMMSSMCLK2ClkDomain
 *
 * MCLK2 clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mMMSSMCLK2ClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(MMSS_MCLK2_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mMCLK2ClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mMCLK2ClkDomainClks)/sizeof(HAL_clk_mMCLK2ClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mMMSSClockDomainControl_2,
  /* .pmNextClockDomain    = */ NULL
};

