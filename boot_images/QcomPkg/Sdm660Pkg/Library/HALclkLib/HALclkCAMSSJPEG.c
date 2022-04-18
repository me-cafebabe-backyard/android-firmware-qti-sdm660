/*
==============================================================================

FILE:         HALclkCAMSSJPEG.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   CAMSSJPEG clocks.

   List of clock domains:
     - HAL_clk_mMMSSJPEG0ClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkCAMSSJPEG.c#2 $

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
 *  HAL_clk_mJPEG0ClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mJPEG0ClkDomainClks[] =
{
  {
    /* .szClockName      = */ "mmss_camss_jpeg0_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_JPEG0_CBCR), HWIO_OFFS(MMSS_CAMSS_JPEG_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_JPEG0_CLK
  },
  {
    /* .szClockName      = */ "mmss_spdm_jpeg0_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_SPDM_JPEG0_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_SPDM_JPEG0_CLK
  },
};


/*
 * HAL_clk_mMMSSJPEG0ClkDomain
 *
 * JPEG0 clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mMMSSJPEG0ClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(MMSS_JPEG0_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mJPEG0ClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mJPEG0ClkDomainClks)/sizeof(HAL_clk_mJPEG0ClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mMMSSClockDomainControl_3,
  /* .pmNextClockDomain    = */ NULL
};

