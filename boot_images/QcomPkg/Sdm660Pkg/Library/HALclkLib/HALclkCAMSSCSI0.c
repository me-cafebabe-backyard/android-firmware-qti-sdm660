/*
==============================================================================

FILE:         HALclkCAMSSCSI0.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   CAMSSCSI0 clocks.

   List of clock domains:
     - HAL_clk_mMMSSCSI0ClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkCAMSSCSI0.c#1 $

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
 *  HAL_clk_mCSI0ClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mCSI0ClkDomainClks[] =
{
  {
    /* .szClockName      = */ "mmss_camss_csi0_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_CSI0_CBCR), HWIO_OFFS(MMSS_CAMSS_CSI0_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_CSI0_CLK
  },
  {
    /* .szClockName      = */ "mmss_camss_csi0pix_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_CSI0PIX_CBCR), HWIO_OFFS(MMSS_CAMSS_CSI0PIX_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_CSI0PIX_CLK
  },
  {
    /* .szClockName      = */ "mmss_camss_csi0rdi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_CSI0RDI_CBCR), HWIO_OFFS(MMSS_CAMSS_CSI0RDI_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_CSI0RDI_CLK
  },
  {
    /* .szClockName      = */ "mmss_spdm_csi0_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_SPDM_CSI0_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_SPDM_CSI0_CLK
  },
  {
    /* .szClockName      = */ "mmss_spdm_debug_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_SPDM_DEBUG_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
};


/*
 * HAL_clk_mMMSSCSI0ClkDomain
 *
 * CSI0 clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mMMSSCSI0ClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(MMSS_CSI0_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mCSI0ClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mCSI0ClkDomainClks)/sizeof(HAL_clk_mCSI0ClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mMMSSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

