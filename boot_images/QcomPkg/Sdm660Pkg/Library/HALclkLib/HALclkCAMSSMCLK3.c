/*
==============================================================================

FILE:         HALclkCAMSSMCLK3.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   CAMSSMCLK3 clocks.

   List of clock domains:
     - HAL_clk_mMMSSMCLK3ClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkCAMSSMCLK3.c#2 $

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
 *  HAL_clk_mMCLK3ClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mMCLK3ClkDomainClks[] =
{
  {
    /* .szClockName      = */ "mmss_camss_mclk3_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_MCLK3_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_MCLK3_CLK
  },
};


/*
 * HAL_clk_mMMSSMCLK3ClkDomain
 *
 * MCLK3 clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mMMSSMCLK3ClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(MMSS_MCLK3_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mMCLK3ClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mMCLK3ClkDomainClks)/sizeof(HAL_clk_mMCLK3ClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mMMSSClockDomainControl_2,
  /* .pmNextClockDomain    = */ NULL
};

