/*
==============================================================================

FILE:         HALclkSWNPL.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   SWNPL clocks.

   List of clock domains:
     - HAL_clk_mLPASSSWNPLClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/sdm660/adsp_slpi/src/lpass/HALclkSWNPL.c#1 $

==============================================================================
            Copyright (c) 2016 Qualcomm Technologies Incorporated.
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
 *  HAL_clk_mSWNPLClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mSWNPLClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_wrapper_sw_npl_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_WRAPPER_SW_NPL_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_WRAPPER_SW_NPL_CLK
  },
};


/*
 * HAL_clk_mLPASSSWNPLClkDomain
 *
 * SWNPL clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSSWNPLClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_SW_NPL_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mSWNPLClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mSWNPLClkDomainClks)/sizeof(HAL_clk_mSWNPLClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl_2,
  /* .pmNextClockDomain    = */ NULL
};

