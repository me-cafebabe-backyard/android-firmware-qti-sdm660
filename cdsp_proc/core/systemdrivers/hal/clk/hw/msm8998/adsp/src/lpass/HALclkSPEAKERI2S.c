/*
==============================================================================

FILE:         HALclkSPEAKERI2S.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   SPEAKERI2S clocks.

   List of clock domains:
     - HAL_clk_mLPASSLPAIFSPKRClkDomain
     - HAL_clk_mLPASSSPKRI2SCLKINClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/msm8998/adsp/src/lpass/HALclkSPEAKERI2S.c#1 $

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
 *  HAL_clk_mLPAIFSPKRClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mLPAIFSPKRClkDomainClks[] =
{
  {
    /* .szClockName      = */ "lpass_audio_core_lpaif_codec_spkr_ibit_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CLK
  },
  {
    /* .szClockName      = */ "lpass_audio_core_lpaif_codec_spkr_osr_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CLK
  },
};


/*
 * HAL_clk_mLPASSLPAIFSPKRClkDomain
 *
 * LPAIFSPKR clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSLPAIFSPKRClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_LPAIF_SPKR_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mLPAIFSPKRClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mLPAIFSPKRClkDomainClks)/sizeof(HAL_clk_mLPAIFSPKRClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mSPKRI2SCLKINClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mSPKRI2SCLKINClkDomainClks[] =
{
  {
    /* .szClockName      = */ "lpass_audio_core_lpaif_codec_spkr_ebit_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
};


/*
 * HAL_clk_mLPASSSPKRI2SCLKINClkDomain
 *
 * SPKRI2SCLKIN clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSSPKRI2SCLKINClkDomain =
{
  /* .nCGRAddr             = */ 0, /* this domain does not have a cmd rcgr */
  /* .pmClocks             = */ HAL_clk_mSPKRI2SCLKINClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mSPKRI2SCLKINClkDomainClks)/sizeof(HAL_clk_mSPKRI2SCLKINClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

