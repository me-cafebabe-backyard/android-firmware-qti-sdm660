/*
==============================================================================

FILE:         HALclkSCCUART3.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   SCCUART3 clocks.

   List of clock domains:
     - HAL_clk_mSSCSCCUARTDMUART3ClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/msm8998/adsp/src/scc/HALclkSCCUART3.c#1 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mSSCClockDomainControl;
extern HAL_clk_ClockDomainControlType  HAL_clk_mSSCClockDomainControlRO;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mSCCUARTDMUART3ClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mSCCUARTDMUART3ClkDomainClks[] =
{
  {
    /* .szClockName      = */ "scc_uart_dm_uart3_clk",
    /* .mRegisters       = */ { HWIO_OFFS(SSC_SCC_SCC_UART_DM_UART3_CBCR), HWIO_OFFS(SSC_SCC_SCC_UART3_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_SSC_TEST_SCC_UART_DM_UART3_CLK
  },
};


/*
 * HAL_clk_mSSCSCCUARTDMUART3ClkDomain
 *
 * SCCUARTDMUART3 clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mSSCSCCUARTDMUART3ClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(SSC_SCC_SCC_UART_DM_UART3_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mSCCUARTDMUART3ClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mSCCUARTDMUART3ClkDomainClks)/sizeof(HAL_clk_mSCCUARTDMUART3ClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mSSCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

