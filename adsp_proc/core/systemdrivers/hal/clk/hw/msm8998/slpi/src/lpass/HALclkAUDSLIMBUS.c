/*
==============================================================================

FILE:         HALclkAUDSLIMBUS.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   AUDSLIMBUS clocks.

   List of clock domains:
     - HAL_clk_mLPASSAUDSLIMBUSClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/msm8998/slpi/src/lpass/HALclkAUDSLIMBUS.c#1 $

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
 *  HAL_clk_mAUDSLIMBUSClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mAUDSLIMBUSClkDomainClks[] =
{
  {
    /* .szClockName      = */ "lpass_audio_core_aud_slimbus_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_LPASS_AUDIO_CORE_AUD_SLIMBUS_CLK
  },
  {
    /* .szClockName      = */ "lpass_audio_core_aud_slimbus_npl_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CLK
  },
};


/*
 * HAL_clk_mLPASSAUDSLIMBUSClkDomain
 *
 * AUDSLIMBUS clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSAUDSLIMBUSClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_AUD_SLIMBUS_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mAUDSLIMBUSClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mAUDSLIMBUSClkDomainClks)/sizeof(HAL_clk_mAUDSLIMBUSClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

