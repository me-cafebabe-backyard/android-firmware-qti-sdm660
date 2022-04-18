/*
==============================================================================

FILE:         HALclkSCCVS.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   SCCVS clocks.

   List of clock domains:
     - HAL_clk_mLPASSSCCVSVDDCXClkDomain
     - HAL_clk_mLPASSSCCVSVDDMXClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/sdm660/adsp_slpi/src/lpass/HALclkSCCVS.c#1 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControl_2;
extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControlRO_2;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mSCCVSVDDCXClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mSCCVSVDDCXClkDomainClks[] =
{
  {
    /* .szClockName      = */ "island_scc_vs_vddcx_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_ISLAND_SCC_VS_VDDCX_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_ISLAND_SCC_VS_VDDCX_CLK
  },
};


/*
 * HAL_clk_mLPASSSCCVSVDDCXClkDomain
 *
 * SCCVSVDDCX clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSSCCVSVDDCXClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_SCC_VS_VDDCX_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mSCCVSVDDCXClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mSCCVSVDDCXClkDomainClks)/sizeof(HAL_clk_mSCCVSVDDCXClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl_2,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mSCCVSVDDMXClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mSCCVSVDDMXClkDomainClks[] =
{
  {
    /* .szClockName      = */ "island_scc_vs_vddmx_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_ISLAND_SCC_VS_VDDMX_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_ISLAND_SCC_VS_VDDMX_CLK
  },
};


/*
 * HAL_clk_mLPASSSCCVSVDDMXClkDomain
 *
 * SCCVSVDDMX clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSSCCVSVDDMXClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_SCC_VS_VDDMX_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mSCCVSVDDMXClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mSCCVSVDDMXClkDomainClks)/sizeof(HAL_clk_mSCCVSVDDMXClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl_2,
  /* .pmNextClockDomain    = */ NULL
};

