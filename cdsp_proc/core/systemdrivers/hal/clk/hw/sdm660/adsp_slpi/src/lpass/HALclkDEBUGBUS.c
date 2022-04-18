/*
==============================================================================

FILE:         HALclkDEBUGBUS.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   DEBUGBUS clocks.

   List of clock domains:
     - HAL_clk_mLPASSSCCAONDBGClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/sdm660/adsp_slpi/src/lpass/HALclkDEBUGBUS.c#1 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControl_1;
extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControlRO_1;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mSCCAONDBGClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mSCCAONDBGClkDomainClks[] =
{
  {
    /* .szClockName      = */ "island_scc_at_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_ISLAND_SCC_AT_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_ISLAND_SCC_AT_CLK
  },
  {
    /* .szClockName      = */ "island_scc_pclkdbg_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_ISLAND_SCC_PCLKDBG_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_ISLAND_SCC_PCLKDBG_CLK
  },
  {
    /* .szClockName      = */ "island_scc_q6_atbm_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_ISLAND_SCC_Q6_ATBM_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_ISLAND_SCC_Q6_ATBM_CLK
  },
};


/*
 * HAL_clk_mLPASSSCCAONDBGClkDomain
 *
 * SCCAONDBG clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSSCCAONDBGClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_SCC_AON_DBG_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mSCCAONDBGClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mSCCAONDBGClkDomainClks)/sizeof(HAL_clk_mSCCAONDBGClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl_1,
  /* .pmNextClockDomain    = */ NULL
};
