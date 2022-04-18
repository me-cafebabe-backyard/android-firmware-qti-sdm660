/*
==============================================================================

FILE:         HALclkRESAMPLER.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   RESAMPLER clocks.

   List of clock domains:
     - HAL_clk_mLPASSRESAMPLERClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/msm8998/adsp/src/lpass/HALclkRESAMPLER.c#1 $

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

extern HAL_clk_ClockControlType        HAL_clk_mLpassClockControl_1;
extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControl_1;
extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControlRO_1;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mRESAMPLERClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mRESAMPLERClkDomainClks[] =
{
  {
    /* .szClockName      = */ "lpass_audio_core_resampler_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_RESAMPLER_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mLpassClockControl_1,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_LPASS_AUDIO_CORE_RESAMPLER_CLK
  },
};


/*
 * HAL_clk_mLPASSRESAMPLERClkDomain
 *
 * RESAMPLER clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSRESAMPLERClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_RESAMPLER_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mRESAMPLERClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mRESAMPLERClkDomainClks)/sizeof(HAL_clk_mRESAMPLERClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl_1,
  /* .pmNextClockDomain    = */ NULL
};

