/*
==============================================================================

FILE:         HALclkSNOC.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   SNOC clocks.

   List of clock domains:
     - HAL_clk_mLPASSCCLPASSSNOCSWAYCLKClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/msm8998/adsp/src/lpass/HALclkSNOC.c#1 $

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
 *  HAL_clk_mCCLPASSSNOCSWAYCLKClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mCCLPASSSNOCSWAYCLKClkDomainClks[] =
{
  {
    /* .szClockName      = */ "lpass_audio_core_peripheral_smmu_client_core_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
  {
    /* .szClockName      = */ "lpass_audio_core_sysnoc_sway_snoc_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CLK
  },
  {
    /* .szClockName      = */ "lpass_audio_wrapper_sysnoc_sway_snoc_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CLK
  },
};


/*
 * HAL_clk_mLPASSCCLPASSSNOCSWAYCLKClkDomain
 *
 * CCLPASSSNOCSWAYCLK clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSCCLPASSSNOCSWAYCLKClkDomain =
{
  /* .nCGRAddr             = */ 0, /* this domain does not have a cmd rcgr */
  /* .pmClocks             = */ HAL_clk_mCCLPASSSNOCSWAYCLKClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mCCLPASSSNOCSWAYCLKClkDomainClks)/sizeof(HAL_clk_mCCLPASSSNOCSWAYCLKClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

