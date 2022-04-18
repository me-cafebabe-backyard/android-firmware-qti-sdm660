/*
==============================================================================

FILE:         HALclkPRIMARYPCM.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   PRIMARYPCM clocks.

   List of clock domains:
     - HAL_clk_mLPASSLPAIFPRIClkDomain
     - HAL_clk_mLPASSPRIMI2SCLKINClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/msm8998/slpi/src/lpass/HALclkPRIMARYPCM.c#1 $

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
 *  HAL_clk_mLPAIFPRIClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mLPAIFPRIClkDomainClks[] =
{
  {
    /* .szClockName      = */ "lpass_audio_core_lpaif_pri_ibit_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mLpass_ClockControl_2,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CLK
  },
};


/*
 * HAL_clk_mLPASSLPAIFPRIClkDomain
 *
 * LPAIFPRI clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSLPAIFPRIClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_LPAIF_PRI_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mLPAIFPRIClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mLPAIFPRIClkDomainClks)/sizeof(HAL_clk_mLPAIFPRIClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mPRIMI2SCLKINClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mPRIMI2SCLKINClkDomainClks[] =
{
  {
    /* .szClockName      = */ "lpass_audio_core_lpaif_pri_ebit_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mLpass_ClockControl_2,
    /* .nTestClock       = */ 0
  },
};


/*
 * HAL_clk_mLPASSPRIMI2SCLKINClkDomain
 *
 * PRIMI2SCLKIN clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSPRIMI2SCLKINClkDomain =
{
  /* .nCGRAddr             = */ 0, /* this domain does not have a cmd rcgr */
  /* .pmClocks             = */ HAL_clk_mPRIMI2SCLKINClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mPRIMI2SCLKINClkDomainClks)/sizeof(HAL_clk_mPRIMI2SCLKINClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

