/*
==============================================================================

FILE:         HALclkINTMI2S2.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   INTMI2S2 clocks.

   List of clock domains:
     - HAL_clk_mLPASSINTI2S2ClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/sdm660/adsp_slpi/src/lpass/HALclkINTMI2S2.c#1 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControl;
extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControlRO;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mINTI2S2ClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mINTI2S2ClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_int_i2s2_ibit_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_INT_I2S2_IBIT_CLK
  },
};


/*
 * HAL_clk_mLPASSINTI2S2ClkDomain
 *
 * INTI2S2 clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSINTI2S2ClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_INT_I2S2_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mINTI2S2ClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mINTI2S2ClkDomainClks)/sizeof(HAL_clk_mINTI2S2ClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

