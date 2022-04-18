/*
==============================================================================

FILE:         HALclk.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
    clocks.

   List of clock domains:
     - HAL_clk_mMMSSCOREPISLEEPCLKClkDomain
     - HAL_clk_mMMSSCXOClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkCXO.c#1 $

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
 *  HAL_clk_mCOREPISLEEPCLKClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mCOREPISLEEPCLKClkDomainClks[] =
{
  {
    /* .szClockName      = */ "mmss_sleep_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_SLEEP_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
};


/*
 * HAL_clk_mMMSSCOREPISLEEPCLKClkDomain
 *
 * COREPISLEEPCLK clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mMMSSCOREPISLEEPCLKClkDomain =
{
  /* .nCGRAddr             = */ 0, /* this domain does not have a cmd rcgr */
  /* .pmClocks             = */ HAL_clk_mCOREPISLEEPCLKClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mCOREPISLEEPCLKClkDomainClks)/sizeof(HAL_clk_mCOREPISLEEPCLKClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mMMSSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mCXOClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mCXOClkDomainClks[] =
{
  {
    /* .szClockName      = */ "mmss_cxo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CXO_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
  {
    /* .szClockName      = */ "mmss_misc_cxo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_MISC_CXO_CBCR), HWIO_OFFS(MMSS_MISC_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_MISC_CXO_CLK
  },
  {
    /* .szClockName      = */ "mmss_throttle_camss_cxo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_THROTTLE_CAMSS_CXO_CBCR), HWIO_OFFS(MMSS_THROTTLE_CAMSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_THROTTLE_CAMSS_CXO_CLK
  },
  {
    /* .szClockName      = */ "mmss_throttle_mdss_cxo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_THROTTLE_MDSS_CXO_CBCR), HWIO_OFFS(MMSS_THROTTLE_MDSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_THROTTLE_MDSS_CXO_CLK
  },
  {
    /* .szClockName      = */ "mmss_throttle_video_cxo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_THROTTLE_VIDEO_CXO_CBCR), HWIO_OFFS(MMSS_THROTTLE_VIDEO_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_THROTTLE_VIDEO_CXO_CLK
  },
};


/*
 * HAL_clk_mMMSSCXOClkDomain
 *
 * CXO clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mMMSSCXOClkDomain =
{
  /* .nCGRAddr             = */ 0, /* this domain does not have a cmd rcgr */
  /* .pmClocks             = */ HAL_clk_mCXOClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mCXOClkDomainClks)/sizeof(HAL_clk_mCXOClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mMMSSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

