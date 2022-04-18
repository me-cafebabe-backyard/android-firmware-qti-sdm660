/*
==============================================================================

FILE:         HALclkCAMSSSTREAMING0.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   CAMSSSTREAMING0 clocks.

   List of clock domains:
     - HAL_clk_mLPASSICAMSSDSPSTREAMING0CLKClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/msm8998/slpi/src/lpass/HALclkCAMSSSTREAMING0.c#1 $

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
 *  HAL_clk_mICAMSSDSPSTREAMING0CLKClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mICAMSSDSPSTREAMING0CLKClkDomainClks[] =
{
  {
    /* .szClockName      = */ "lpass_q6ss_q6_camss_dsp_streaming_0_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
};


/*
 * HAL_clk_mLPASSICAMSSDSPSTREAMING0CLKClkDomain
 *
 * ICAMSSDSPSTREAMING0CLK clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSICAMSSDSPSTREAMING0CLKClkDomain =
{
  /* .nCGRAddr             = */ 0, /* this domain does not have a cmd rcgr */
  /* .pmClocks             = */ HAL_clk_mICAMSSDSPSTREAMING0CLKClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mICAMSSDSPSTREAMING0CLKClkDomainClks)/sizeof(HAL_clk_mICAMSSDSPSTREAMING0CLKClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

