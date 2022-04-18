/*
==============================================================================

FILE:         HALclkSCCUART2.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   SCCUART2 clocks.

   List of clock domains:
     - HAL_clk_mSSCSCCUARTDMUART2ClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/msm8998/adsp/src/scc/HALclkSCCUART2.c#1 $

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
 *  HAL_clk_mSCCUARTDMUART2ClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mSCCUARTDMUART2ClkDomainClks[] =
{
  {
    /* .szClockName      = */ "scc_uart_dm_uart2_clk",
    /* .mRegisters       = */ { HWIO_OFFS(SSC_SCC_SCC_UART_DM_UART2_CBCR), HWIO_OFFS(SSC_SCC_SCC_UART2_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_SSC_TEST_SCC_UART_DM_UART2_CLK
  },
};


/*
 * HAL_clk_mSSCSCCUARTDMUART2ClkDomain
 *
 * SCCUARTDMUART2 clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mSSCSCCUARTDMUART2ClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(SSC_SCC_SCC_UART_DM_UART2_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mSCCUARTDMUART2ClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mSCCUARTDMUART2ClkDomainClks)/sizeof(HAL_clk_mSCCUARTDMUART2ClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mSSCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

