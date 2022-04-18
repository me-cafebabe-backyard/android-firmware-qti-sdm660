/*
==============================================================================

FILE:         HALclkSCCVS.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   SCCVS clocks.

   List of clock domains:
     - HAL_clk_mSSCSCCVSVDDCXClkDomain
     - HAL_clk_mSSCSCCVSVDDMXClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/msm8998/slpi/src/scc/HALclkSCCVS.c#1 $

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
 *  HAL_clk_mSCCVSVDDCXClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mSCCVSVDDCXClkDomainClks[] =
{
  {
    /* .szClockName      = */ "scc_vs_vddcx_clk",
    /* .mRegisters       = */ { HWIO_OFFS(SSC_SCC_SCC_VS_VDDCX_CBCR), HWIO_OFFS(SSC_SCC_SCC_VS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_SSC_TEST_SCC_VS_VDDCX_CLK
  },
};


/*
 * HAL_clk_mSSCSCCVSVDDCXClkDomain
 *
 * SCCVSVDDCX clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mSSCSCCVSVDDCXClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(SSC_SCC_SCC_VS_VDDCX_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mSCCVSVDDCXClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mSCCVSVDDCXClkDomainClks)/sizeof(HAL_clk_mSCCVSVDDCXClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mSSCClockDomainControl,
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
    /* .szClockName      = */ "scc_vs_vddmx_clk",
    /* .mRegisters       = */ { HWIO_OFFS(SSC_SCC_SCC_VS_VDDMX_CBCR), HWIO_OFFS(SSC_SCC_SCC_VS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControlRO,
    /* .nTestClock       = */ HAL_CLK_SSC_TEST_SCC_VS_VDDMX_CLK
  },
};


/*
 * HAL_clk_mSSCSCCVSVDDMXClkDomain
 *
 * SCCVSVDDMX clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mSSCSCCVSVDDMXClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(SSC_SCC_SCC_VS_VDDMX_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mSCCVSVDDMXClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mSCCVSVDDMXClkDomainClks)/sizeof(HAL_clk_mSCCVSVDDMXClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mSSCClockDomainControlRO,
  /* .pmNextClockDomain    = */ NULL
};

