/*
==============================================================================

FILE:         HALclkSCCUART3.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   SCCUART3 clocks.

   List of clock domains:
     - HAL_clk_mLPASSSCCUART3ClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/sdm660/adsp_slpi/src/lpass/HALclkSCCUART3.c#1 $

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
 *  HAL_clk_mSCCUART3ClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mSCCUART3ClkDomainClks[] =
{
  {
    /* .szClockName      = */ "island_scc_uart_dm_uart3_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_ISLAND_SCC_UART_DM_UART3_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_ISLAND_SCC_UART_DM_UART3_CLK
  },
};


/*
 * HAL_clk_mLPASSSCCUART3ClkDomain
 *
 * SCCUART3 clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSSCCUART3ClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_SCC_UART3_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mSCCUART3ClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mSCCUART3ClkDomainClks)/sizeof(HAL_clk_mSCCUART3ClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl_1,
  /* .pmNextClockDomain    = */ NULL
};

