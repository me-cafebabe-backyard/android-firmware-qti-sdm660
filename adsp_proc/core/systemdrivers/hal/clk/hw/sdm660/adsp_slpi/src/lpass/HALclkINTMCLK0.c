/*
==============================================================================

FILE:         HALclkINTMCLK0.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   INTMCLK0 clocks.

   List of clock domains:
     - HAL_clk_mLPASSINTMCLK0ClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/sdm660/adsp_slpi/src/lpass/HALclkINTMCLK0.c#1 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControl;
extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControlRO;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mINTMCLK0ClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mINTMCLK0ClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_int_mclk0_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_INT_MCLK0_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_INT_MCLK0_CLK
  },
};


/*
 * HAL_clk_mLPASSINTMCLK0ClkDomain
 *
 * INTMCLK0 clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSINTMCLK0ClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_INT_MCLK0_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mINTMCLK0ClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mINTMCLK0ClkDomainClks)/sizeof(HAL_clk_mINTMCLK0ClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

