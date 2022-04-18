/*
==============================================================================

FILE:         HALclkDEBUGTSCTRBUS.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   DEBUGTSCTRBUS clocks.

   List of clock domains:
     - HAL_clk_mLPASSSCCAONDBGTSCTRClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/sdm660/adsp_slpi/src/lpass/HALclkDEBUGTSCTRBUS.c#1 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControl_1;
extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControlRO_1;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mSCCAONDBGTSCTRClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mSCCAONDBGTSCTRClkDomainClks[] =
{
  {
    /* .szClockName      = */ "island_scc_dbg_tsctr_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_ISLAND_SCC_DBG_TSCTR_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_ISLAND_SCC_DBG_TSCTR_CLK
  },
};


/*
 * HAL_clk_mLPASSSCCAONDBGTSCTRClkDomain
 *
 * SCCAONDBGTSCTR clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSSCCAONDBGTSCTRClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mSCCAONDBGTSCTRClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mSCCAONDBGTSCTRClkDomainClks)/sizeof(HAL_clk_mSCCAONDBGTSCTRClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl_1,
  /* .pmNextClockDomain    = */ NULL
};
