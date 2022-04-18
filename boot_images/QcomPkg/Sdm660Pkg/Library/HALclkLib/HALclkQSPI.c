/*
==============================================================================

FILE:         HALclkQSPI.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   QSPI clocks.

   List of clock domains:
     - HAL_clk_mGCCQSPISERClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkQSPI.c#1 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControl_5;
extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControlRO_5;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mQSPISERClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mQSPISERClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_qspi_ser_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_QSPI_SER_CBCR), HWIO_OFFS(GCC_QSPI_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_QSPI_SER_CLK
  },
};


/*
 * HAL_clk_mGCCQSPISERClkDomain
 *
 * QSPISER clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCQSPISERClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_QSPI_SER_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mQSPISERClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mQSPISERClkDomainClks)/sizeof(HAL_clk_mQSPISERClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl_5,
  /* .pmNextClockDomain    = */ NULL
};

