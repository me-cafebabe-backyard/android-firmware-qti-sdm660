/*
==============================================================================

FILE:         HALclkSLEEP.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   SLEEP clocks.

   List of clock domains:
     - HAL_clk_mLPASSSLEEPClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/msm8998/slpi/src/lpass/HALclkSLEEP.c#1 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControl_2;
extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControlRO_2;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mSLEEPClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mSLEEPClkDomainClks[] =
{
  {
    /* .szClockName      = */ "lpass_audio_core_bcr_slp_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_BCR_SLP_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_LPASS_AUDIO_CORE_BCR_SLP_CLK
  },
  {
    /* .szClockName      = */ "lpass_q6ss_bcr_slp_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_Q6SS_BCR_SLP_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_LPASS_Q6SS_BCR_SLP_CLK
  },
  {
    /* .szClockName      = */ "lpass_qdsp6ss_sleep_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_QDSP6SS_SLEEP_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
};


/*
 * HAL_clk_mLPASSSLEEPClkDomain
 *
 * SLEEP clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSSLEEPClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_SLEEP_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mSLEEPClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mSLEEPClkDomainClks)/sizeof(HAL_clk_mSLEEPClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl_2,
  /* .pmNextClockDomain    = */ NULL
};

