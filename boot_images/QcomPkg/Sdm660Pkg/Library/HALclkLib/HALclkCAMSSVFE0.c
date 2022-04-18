/*
==============================================================================

FILE:         HALclkCAMSSVFE0.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   CAMSSVFE0 clocks.

   List of clock domains:
     - HAL_clk_mMMSSVFE0ClkDomain


   List of power domains:
     - HAL_clk_mMMSSCAMSSVFE0PowerDomain



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkCAMSSVFE0.c#2 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mMMSSClockDomainControl_5;
extern HAL_clk_ClockDomainControlType  HAL_clk_mMMSSClockDomainControlRO_5;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mVFE0ClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mVFE0ClkDomainClks[] =
{
  {
    /* .szClockName      = */ "mmss_camss_csi_vfe0_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_CSI_VFE0_CBCR), HWIO_OFFS(MMSS_CAMSS_CSI_VFE0_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_CSI_VFE0_CLK
  },
  {
    /* .szClockName      = */ "mmss_camss_vfe0_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_VFE0_CBCR), HWIO_OFFS(MMSS_CAMSS_VFE0_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_VFE0_CLK
  },
  {
    /* .szClockName      = */ "mmss_camss_vfe0_stream_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_VFE0_STREAM_CBCR), HWIO_OFFS(MMSS_CAMSS_VFE0_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_VFE0_STREAM_CLK
  },
  {
    /* .szClockName      = */ "mmss_spdm_vfe0_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_SPDM_VFE0_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_SPDM_VFE0_CLK
  },
};


/*
 * HAL_clk_mMMSSVFE0ClkDomain
 *
 * VFE0 clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mMMSSVFE0ClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(MMSS_VFE0_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mVFE0ClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mVFE0ClkDomainClks)/sizeof(HAL_clk_mVFE0ClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mMMSSClockDomainControl_5,
  /* .pmNextClockDomain    = */ NULL
};


/*
 * HAL_clk_mMMSSCAMSSVFE0PowerDomain
 *
 * CAMSS_VFE0 power domain.
 */
HAL_clk_PowerDomainDescType HAL_clk_mMMSSCAMSSVFE0PowerDomain =
{
  /* .szPowerDomainName       = */ "VDD_CAMSS_VFE0",
  /* .nGDSCRAddr              = */ HWIO_OFFS(MMSS_CAMSS_VFE0_GDSCR),
  /* .pmControl               = */ &HAL_clk_mGenericPowerDomainControl,
  /* .pmClockMemCore          = */ NULL,
  /* .pmClockMemPeriph        = */ NULL,
  /* .pmNextPowerDomain       = */ NULL
};

