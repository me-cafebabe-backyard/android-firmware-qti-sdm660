/*
==============================================================================

FILE:         HALclkCAMSSCPP.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   CAMSSCPP clocks.

   List of clock domains:
     - HAL_clk_mMMSSCPPClkDomain


   List of power domains:
     - HAL_clk_mMMSSCAMSSCPPPowerDomain



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkCAMSSCPP.c#2 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mMMSSClockDomainControl_7;
extern HAL_clk_ClockDomainControlType  HAL_clk_mMMSSClockDomainControlRO_7;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mCPPClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mCPPClkDomainClks[] =
{
  {
    /* .szClockName      = */ "mmss_camss_cpp_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_CPP_CBCR), HWIO_OFFS(MMSS_CAMSS_CPP_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_CPP_CLK
  },
  {
    /* .szClockName      = */ "mmss_spdm_cpp_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_SPDM_CPP_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_SPDM_CPP_CLK
  },
};


/*
 * HAL_clk_mMMSSCPPClkDomain
 *
 * CPP clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mMMSSCPPClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(MMSS_CPP_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mCPPClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mCPPClkDomainClks)/sizeof(HAL_clk_mCPPClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mMMSSClockDomainControl_7,
  /* .pmNextClockDomain    = */ NULL
};


/*
 * HAL_clk_mMMSSCAMSSCPPPowerDomain
 *
 * CAMSS_CPP power domain.
 */
HAL_clk_PowerDomainDescType HAL_clk_mMMSSCAMSSCPPPowerDomain =
{
  /* .szPowerDomainName       = */ "VDD_CAMSS_CPP",
  /* .nGDSCRAddr              = */ HWIO_OFFS(MMSS_CAMSS_CPP_GDSCR),
  /* .pmControl               = */ &HAL_clk_mGenericPowerDomainControl,
  /* .pmClockMemCore          = */ NULL,
  /* .pmClockMemPeriph        = */ NULL,
  /* .pmNextPowerDomain       = */ NULL
};

