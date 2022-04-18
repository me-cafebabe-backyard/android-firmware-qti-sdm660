/*
==============================================================================

FILE:         HALclkVIDEOTOP.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   VIDEOTOP clocks.

   List of clock domains:
     - HAL_clk_mMMSSVIDEOCOREClkDomain


   List of power domains:
     - HAL_clk_mMMSSVIDEOTOPPowerDomain



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkVIDEOTOP.c#2 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mMMSSClockDomainControl_9;
extern HAL_clk_ClockDomainControlType  HAL_clk_mMMSSClockDomainControlRO_9;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mVIDEOCOREClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mVIDEOCOREClkDomainClks[] =
{
  {
    /* .szClockName      = */ "mmss_spdm_video_core_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_SPDM_VIDEO_CORE_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_SPDM_VIDEO_CORE_CLK
  },
  {
    /* .szClockName      = */ "mmss_video_core_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_VIDEO_CORE_CBCR), HWIO_OFFS(MMSS_VIDEO_TOP_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_VIDEO_CORE_CLK
  },
  {
    /* .szClockName      = */ "mmss_video_subcore0_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_VIDEO_SUBCORE0_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_VIDEO_SUBCORE0_CLK
  },
};


/*
 * HAL_clk_mMMSSVIDEOCOREClkDomain
 *
 * VIDEOCORE clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mMMSSVIDEOCOREClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(MMSS_VIDEO_CORE_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mVIDEOCOREClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mVIDEOCOREClkDomainClks)/sizeof(HAL_clk_mVIDEOCOREClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mMMSSClockDomainControl_9,
  /* .pmNextClockDomain    = */ NULL
};


/*
 * HAL_clk_mMMSSVIDEOTOPPowerDomain
 *
 * VIDEO_TOP power domain.
 */
HAL_clk_PowerDomainDescType HAL_clk_mMMSSVIDEOTOPPowerDomain =
{
  /* .szPowerDomainName       = */ "VDD_VIDEO_TOP",
  /* .nGDSCRAddr              = */ HWIO_OFFS(MMSS_VIDEO_TOP_GDSCR),
  /* .pmControl               = */ &HAL_clk_mGenericPowerDomainControl,
  /* .pmClockMemCore          = */ NULL,
  /* .pmClockMemPeriph        = */ NULL,
  /* .pmNextPowerDomain       = */ NULL
};

