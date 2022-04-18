/*
==============================================================================

FILE:         HALclkMMSS.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   MMSS clocks.

   List of clock domains:
     - HAL_clk_mGCCMMSSQMCOREClkDomain


   List of power domains:
     - HAL_clk_mGCCMMSSPowerDomain



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkMMSS.c#2 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControl;
extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControlRO;


/* ============================================================================
**    Data
** ==========================================================================*/


/*
 *  HAL_clk_mMMSSQMCOREClkDomainClks
 *
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mMMSSQMCOREClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_mmss_qm_core_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_MMSS_QM_CORE_CBCR), HWIO_OFFS(GCC_MMSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_MMSS_QM_CORE_CLK
  },
};


/*
 * HAL_clk_mGCCMMSSQMCOREClkDomain
 *
 * MMSSQMCORE clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCMMSSQMCOREClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_MMSS_QM_CORE_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mMMSSQMCOREClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mMMSSQMCOREClkDomainClks)/sizeof(HAL_clk_mMMSSQMCOREClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


#if 0 /* not present on apcs */

/*
 * HAL_clk_mGCCMMSSPowerDomain
 *
 * MMSS power domain.
 */
HAL_clk_PowerDomainDescType HAL_clk_mGCCMMSSPowerDomain =
{
  /* .szPowerDomainName       = */ "VDD_MMSS",
  /* .nGDSCRAddr              = */ HWIO_OFFS(GCC_MMSS_GDSCR),
  /* .pmControl               = */ &HAL_clk_mGenericPowerDomainControl,
  /* .pmClockMemCore          = */ NULL,
  /* .pmClockMemPeriph        = */ NULL,
  /* .pmNextPowerDomain       = */ NULL
};


#endif
