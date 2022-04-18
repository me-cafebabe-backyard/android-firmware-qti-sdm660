/*
==============================================================================

FILE:         HALclkCLOCKDRIVERGENNODOMAIN.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the
   CLOCKDRIVERGENNODOMAIN clocks.

   List of clock domains:
    - HAL_clk_mGCCCLOCKDRIVERGENNODOMAINClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkCLOCKDRIVERGENNODOMAIN.c#1 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControl_1;
extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControlRO_1;


/* ============================================================================
**    Data
** ==========================================================================*/


/*
 *  HAL_clk_mCLOCKDRIVERGENNODOMAINClkDomainClks
 *
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mCLOCKDRIVERGENNODOMAINClkDomainClks[] =
{
  {
    /* .szClockName      = */ "gcc_rx1_usb2_clkref_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_RX1_USB2_CLKREF_EN), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
  {
    /* .szClockName      = */ "gcc_rx0_usb2_clkref_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_RX0_USB2_CLKREF_EN), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
  {
    /* .szClockName      = */ "gcc_ufs_clkref_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_UFS_CLKREF_EN), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
  {
    /* .szClockName      = */ "gcc_usb3_clkref_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_USB3_CLKREF_EN), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
};


/*
 * HAL_clk_mGCCCLOCKDRIVERGENNODOMAINClkDomain
 *
 * CLOCKDRIVERGENNODOMAIN clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCCLOCKDRIVERGENNODOMAINClkDomain =
{
  /* .nCGRAddr             = */ 0,
  /* .pmClocks             = */ HAL_clk_mCLOCKDRIVERGENNODOMAINClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mCLOCKDRIVERGENNODOMAINClkDomainClks)/sizeof(HAL_clk_mCLOCKDRIVERGENNODOMAINClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControlRO_1,
  /* .pmNextClockDomain    = */ NULL
};

