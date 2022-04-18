/*
==============================================================================

FILE:         HALclkTERTIARYPCM.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   TERTIARYPCM clocks.

   List of clock domains:
     - HAL_clk_mLPASSLPAIFTERClkDomain
     - HAL_clk_mLPASSTERMI2SCLKINClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/msm8998/slpi/src/lpass/HALclkTERTIARYPCM.c#1 $

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

extern HAL_clk_ClockControlType HAL_clk_mLpass_ClockControl_2;
extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControl;
extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControlRO;

/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mLPAIFTERClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mLPAIFTERClkDomainClks[] =
{
  {
    /* .szClockName      = */ "lpass_audio_core_lpaif_ter_ibit_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mLpass_ClockControl_2,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CLK
  },
};


/*
 * HAL_clk_mLPASSLPAIFTERClkDomain
 *
 * LPAIFTER clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSLPAIFTERClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_LPAIF_TER_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mLPAIFTERClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mLPAIFTERClkDomainClks)/sizeof(HAL_clk_mLPAIFTERClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mTERMI2SCLKINClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mTERMI2SCLKINClkDomainClks[] =
{
  {
    /* .szClockName      = */ "lpass_audio_core_lpaif_ter_ebit_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mLpass_ClockControl_2,
    /* .nTestClock       = */ 0
  },
};


/*
 * HAL_clk_mLPASSTERMI2SCLKINClkDomain
 *
 * TERMI2SCLKIN clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSTERMI2SCLKINClkDomain =
{
  /* .nCGRAddr             = */ 0, /* this domain does not have a cmd rcgr */
  /* .pmClocks             = */ HAL_clk_mTERMI2SCLKINClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mTERMI2SCLKINClkDomainClks)/sizeof(HAL_clk_mTERMI2SCLKINClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

