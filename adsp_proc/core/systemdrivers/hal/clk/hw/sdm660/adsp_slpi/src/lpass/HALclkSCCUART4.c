/*
==============================================================================

FILE:         HALclkSCCUART4.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   SCCUART4 clocks.

   List of clock domains:
     - HAL_clk_mLPASSSCCUART4ClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/sdm660/adsp_slpi/src/lpass/HALclkSCCUART4.c#1 $

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
 *  HAL_clk_mSCCUART4ClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mSCCUART4ClkDomainClks[] =
{
  {
    /* .szClockName      = */ "island_scc_uart_dm_uart4_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_ISLAND_SCC_UART_DM_UART4_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_ISLAND_SCC_UART_DM_UART4_CLK
  },
};


/*
 * HAL_clk_mLPASSSCCUART4ClkDomain
 *
 * SCCUART4 clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSSCCUART4ClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_SCC_UART4_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mSCCUART4ClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mSCCUART4ClkDomainClks)/sizeof(HAL_clk_mSCCUART4ClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl_1,
  /* .pmNextClockDomain    = */ NULL
};
