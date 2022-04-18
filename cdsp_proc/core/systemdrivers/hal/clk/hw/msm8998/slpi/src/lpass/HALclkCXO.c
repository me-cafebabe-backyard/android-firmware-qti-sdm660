/*
==============================================================================

FILE:         HALclkCXO.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   CXO clocks.

   List of clock domains:
     - HAL_clk_mLPASSXOClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/msm8998/slpi/src/lpass/HALclkCXO.c#1 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControl;
extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControlRO;


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
    /* .szClockName      = */ "lpass_audio_core_avsync_stc_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_AVSYNC_STC_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_LPASS_AUDIO_CORE_AVSYNC_STC_CLK
  },
  {
    /* .szClockName      = */ "lpass_audio_core_gdsc_xo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_GDSC_XO_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_LPASS_AUDIO_CORE_GDSC_XO_CLK
  },
  {
    /* .szClockName      = */ "lpass_audio_wrapper_q6_smmu_gdsc_xo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CLK
  },
  {
    /* .szClockName      = */ "lpass_audio_wrapper_qos_xo_lat_counter_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CLK
  },
  {
    /* .szClockName      = */ "lpass_qdsp6ss_xo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_QDSP6SS_XO_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
};


/*
 * HAL_clk_mLPASSXOClkDomain
 *
 * XO clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSXOClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_XO_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mXOClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mXOClkDomainClks)/sizeof(HAL_clk_mXOClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

