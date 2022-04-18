/*
==============================================================================

FILE:         HALclkQUATERNARYPCM.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   QUATERNARYPCM clocks.

   List of clock domains:
     - HAL_clk_mLPASSLPAIFQUADClkDomain
     - HAL_clk_mLPASSQUAMI2SCLKINClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/sdm660/adsp_slpi/src/lpass/HALclkQUATERNARYPCM.c#1 $

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

extern HAL_clk_ClockControlType        HAL_clk_mLpass_ClockControl_2;
extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControl;
extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControlRO;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mLPAIFQUADClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mLPAIFQUADClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_lpaif_quad_ibit_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mLpass_ClockControl_2,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_AUDIO_CORE_LPAIF_QUAD_IBIT_CLK
  },
};


/*
 * HAL_clk_mLPASSLPAIFQUADClkDomain
 *
 * LPAIFQUAD clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSLPAIFQUADClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_LPAIF_QUAD_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mLPAIFQUADClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mLPAIFQUADClkDomainClks)/sizeof(HAL_clk_mLPAIFQUADClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mQUAMI2SCLKINClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mQUAMI2SCLKINClkDomainClks[] =
{
  {
    /* .szClockName      = */ "audio_core_lpaif_quad_ebit_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mLpass_ClockControl_2,
    /* .nTestClock       = */ 0
  },
};


/*
 * HAL_clk_mLPASSQUAMI2SCLKINClkDomain
 *
 * QUAMI2SCLKIN clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSQUAMI2SCLKINClkDomain =
{
  /* .nCGRAddr             = */ 0, /* this domain does not have a cmd rcgr */
  /* .pmClocks             = */ HAL_clk_mQUAMI2SCLKINClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mQUAMI2SCLKINClkDomainClks)/sizeof(HAL_clk_mQUAMI2SCLKINClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

