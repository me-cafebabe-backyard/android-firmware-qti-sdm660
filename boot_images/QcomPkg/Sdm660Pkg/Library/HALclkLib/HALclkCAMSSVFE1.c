/*
==============================================================================

FILE:         HALclkCAMSSVFE1.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   CAMSSVFE1 clocks.

   List of clock domains:
     - HAL_clk_mMMSSVFE1ClkDomain


   List of power domains:
     - HAL_clk_mMMSSCAMSSVFE1PowerDomain



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkCAMSSVFE1.c#2 $

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
 *  HAL_clk_mVFE1ClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mVFE1ClkDomainClks[] =
{
  {
    /* .szClockName      = */ "mmss_camss_csi_vfe1_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_CSI_VFE1_CBCR), HWIO_OFFS(MMSS_CAMSS_CSI_VFE1_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_CSI_VFE1_CLK
  },
  {
    /* .szClockName      = */ "mmss_camss_vfe1_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_VFE1_CBCR), HWIO_OFFS(MMSS_CAMSS_VFE1_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_VFE1_CLK
  },
  {
    /* .szClockName      = */ "mmss_camss_vfe1_stream_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_VFE1_STREAM_CBCR), HWIO_OFFS(MMSS_CAMSS_VFE1_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_VFE1_STREAM_CLK
  },
  {
    /* .szClockName      = */ "mmss_spdm_vfe1_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_SPDM_VFE1_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_SPDM_VFE1_CLK
  },
};


/*
 * HAL_clk_mMMSSVFE1ClkDomain
 *
 * VFE1 clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mMMSSVFE1ClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(MMSS_VFE1_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mVFE1ClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mVFE1ClkDomainClks)/sizeof(HAL_clk_mVFE1ClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mMMSSClockDomainControl_5,
  /* .pmNextClockDomain    = */ NULL
};


/*
 * HAL_clk_mMMSSCAMSSVFE1PowerDomain
 *
 * CAMSS_VFE1 power domain.
 */
HAL_clk_PowerDomainDescType HAL_clk_mMMSSCAMSSVFE1PowerDomain =
{
  /* .szPowerDomainName       = */ "VDD_CAMSS_VFE1",
  /* .nGDSCRAddr              = */ HWIO_OFFS(MMSS_CAMSS_VFE1_GDSCR),
  /* .pmControl               = */ &HAL_clk_mGenericPowerDomainControl,
  /* .pmClockMemCore          = */ NULL,
  /* .pmClockMemPeriph        = */ NULL,
  /* .pmNextPowerDomain       = */ NULL
};

