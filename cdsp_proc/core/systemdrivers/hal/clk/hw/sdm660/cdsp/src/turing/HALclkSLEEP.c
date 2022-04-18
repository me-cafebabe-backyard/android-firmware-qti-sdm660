/*
==============================================================================

FILE:         HALclkSLEEP.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   SLEEP clocks.

   List of clock domains:
     - HAL_clk_mTURINGSLEEPClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/sdm660/cdsp/src/turing/HALclkSLEEP.c#1 $

==============================================================================
            Copyright (c) 2016 QUALCOMM Technologies Incorporated.
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

extern HAL_clk_ClockDomainControlType  HAL_clk_mTURINGClockDomainControl;
extern HAL_clk_ClockDomainControlType  HAL_clk_mTURINGClockDomainControlRO;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mSLEEPClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mSLEEPClkDomainClks[] =
{
  {
    /* .szClockName      = */ "q6ss_slp_clk",
    /* .mRegisters       = */ { HWIO_OFFS(TURING_QDSP6SS_SLEEP_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
};


/*
 * HAL_clk_mTURINGSLEEPClkDomain
 *
 * SLEEP clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mTURINGSLEEPClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(TURING_SLEEP_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mSLEEPClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mSLEEPClkDomainClks)/sizeof(HAL_clk_mSLEEPClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mTURINGClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

