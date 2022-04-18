/*
==============================================================================

FILE:         HALclkCAMSSPHY0.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   CAMSSPHY0 clocks.

   List of clock domains:
     - HAL_clk_mMMSSCSI0PHYTIMERClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkCAMSSPHY0.c#2 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mMMSSClockDomainControl_3;
extern HAL_clk_ClockDomainControlType  HAL_clk_mMMSSClockDomainControlRO_3;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mCSI0PHYTIMERClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mCSI0PHYTIMERClkDomainClks[] =
{
  {
    /* .szClockName      = */ "mmss_camss_csi0phytimer_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_CSI0PHYTIMER_CBCR), HWIO_OFFS(MMSS_CAMSS_PHY0_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_CSI0PHYTIMER_CLK
  },
};


/*
 * HAL_clk_mMMSSCSI0PHYTIMERClkDomain
 *
 * CSI0PHYTIMER clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mMMSSCSI0PHYTIMERClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(MMSS_CSI0PHYTIMER_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mCSI0PHYTIMERClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mCSI0PHYTIMERClkDomainClks)/sizeof(HAL_clk_mCSI0PHYTIMERClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mMMSSClockDomainControl_3,
  /* .pmNextClockDomain    = */ NULL
};

