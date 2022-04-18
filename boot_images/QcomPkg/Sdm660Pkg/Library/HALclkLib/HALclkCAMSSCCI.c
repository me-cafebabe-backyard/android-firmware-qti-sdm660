/*
==============================================================================

FILE:         HALclkCAMSSCCI.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   CAMSSCCI clocks.

   List of clock domains:
     - HAL_clk_mMMSSCCIClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkCAMSSCCI.c#1 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mMMSSClockDomainControl_4;
extern HAL_clk_ClockDomainControlType  HAL_clk_mMMSSClockDomainControlRO_4;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mCCIClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mCCIClkDomainClks[] =
{
  {
    /* .szClockName      = */ "mmss_camss_cci_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_CCI_CBCR), HWIO_OFFS(MMSS_CAMSS_CCI_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_CCI_CLK
  },
};


/*
 * HAL_clk_mMMSSCCIClkDomain
 *
 * CCI clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mMMSSCCIClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(MMSS_CCI_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mCCIClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mCCIClkDomainClks)/sizeof(HAL_clk_mCCIClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mMMSSClockDomainControl_4,
  /* .pmNextClockDomain    = */ NULL
};

