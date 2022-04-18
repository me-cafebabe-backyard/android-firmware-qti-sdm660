/*
==============================================================================

FILE:         HALclkSDCC1.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   SDCC1 clocks.

   List of clock domains:
     - HAL_clk_mGCCSDCC1APPSClkDomain
     - HAL_clk_mGCCSDCC1ICECOREClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkSDCC1.c#1 $

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
extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControl_3;
extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControlRO_3;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mSDCC1APPSClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mSDCC1APPSClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_sdcc1_apps_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SDCC1_APPS_CBCR), HWIO_OFFS(GCC_SDCC1_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SDCC1_APPS_CLK
  },
};


/*
 * HAL_clk_mGCCSDCC1APPSClkDomain
 *
 * SDCC1APPS clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCSDCC1APPSClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_SDCC1_APPS_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mSDCC1APPSClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mSDCC1APPSClkDomainClks)/sizeof(HAL_clk_mSDCC1APPSClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl_3,
  /* .pmNextClockDomain    = */ NULL
};


/*                           
 *  HAL_clk_mSDCC1ICECOREClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mSDCC1ICECOREClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_sdcc1_ice_core_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SDCC1_ICE_CORE_CBCR), HWIO_OFFS(GCC_SDCC1_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SDCC1_ICE_CORE_CLK
  },
};


/*
 * HAL_clk_mGCCSDCC1ICECOREClkDomain
 *
 * SDCC1ICECORE clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCSDCC1ICECOREClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_SDCC1_ICE_CORE_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mSDCC1ICECOREClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mSDCC1ICECOREClkDomainClks)/sizeof(HAL_clk_mSDCC1ICECOREClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

