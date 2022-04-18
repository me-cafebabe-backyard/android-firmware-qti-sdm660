/*
==============================================================================

FILE:         HALclkAXI.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   AXI clocks.

   List of clock domains:
     - HAL_clk_mLPASSCCLPASSQ6SMMUCLIENTCLKClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/msm8998/slpi/src/lpass/HALclkAXI.c#1 $

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
 *  HAL_clk_mCCLPASSQ6SMMUCLIENTCLKClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mCCLPASSQ6SMMUCLIENTCLKClkDomainClks[] =
{
  {
    /* .szClockName      = */ "lpass_q6ss_q6_axim_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_Q6SS_Q6_AXIM_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
};


/*
 * HAL_clk_mLPASSCCLPASSQ6SMMUCLIENTCLKClkDomain
 *
 * CCLPASSQ6SMMUCLIENTCLK clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSCCLPASSQ6SMMUCLIENTCLKClkDomain =
{
  /* .nCGRAddr             = */ 0, /* this domain does not have a cmd rcgr */
  /* .pmClocks             = */ HAL_clk_mCCLPASSQ6SMMUCLIENTCLKClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mCCLPASSQ6SMMUCLIENTCLKClkDomainClks)/sizeof(HAL_clk_mCCLPASSQ6SMMUCLIENTCLKClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

