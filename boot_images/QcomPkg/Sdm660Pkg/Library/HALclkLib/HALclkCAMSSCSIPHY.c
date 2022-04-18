/*
==============================================================================

FILE:         HALclkCAMSSCSIPHY.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   CAMSSCSIPHY clocks.

   List of clock domains:
     - HAL_clk_mMMSSCSIPHYClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkCAMSSCSIPHY.c#1 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mMMSSClockDomainControl;
extern HAL_clk_ClockDomainControlType  HAL_clk_mMMSSClockDomainControlRO;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mCSIPHYClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mCSIPHYClkDomainClks[] =
{
  {
    /* .szClockName      = */ "mmss_camss_cphy_csid0_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_CPHY_CSID0_CBCR), HWIO_OFFS(MMSS_CAMSS_CSI0_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_CPHY_CSID0_CLK
  },
  {
    /* .szClockName      = */ "mmss_camss_cphy_csid1_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_CPHY_CSID1_CBCR), HWIO_OFFS(MMSS_CAMSS_CSI1_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_CPHY_CSID1_CLK
  },
  {
    /* .szClockName      = */ "mmss_camss_cphy_csid2_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_CPHY_CSID2_CBCR), HWIO_OFFS(MMSS_CAMSS_CSI2_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_CPHY_CSID2_CLK
  },
  {
    /* .szClockName      = */ "mmss_camss_cphy_csid3_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_CPHY_CSID3_CBCR), HWIO_OFFS(MMSS_CAMSS_CSI3_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_CPHY_CSID3_CLK
  },
  {
    /* .szClockName      = */ "mmss_camss_csiphy0_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_CSIPHY0_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_CSIPHY0_CLK
  },
  {
    /* .szClockName      = */ "mmss_camss_csiphy1_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_CSIPHY1_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_CSIPHY1_CLK
  },
  {
    /* .szClockName      = */ "mmss_camss_csiphy2_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_CSIPHY2_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_CSIPHY2_CLK
  },
};


/*
 * HAL_clk_mMMSSCSIPHYClkDomain
 *
 * CSIPHY clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mMMSSCSIPHYClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(MMSS_CSIPHY_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mCSIPHYClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mCSIPHYClkDomainClks)/sizeof(HAL_clk_mCSIPHYClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mMMSSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

