/*
==============================================================================

FILE:         HALclkCAMSSCSI3.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   CAMSSCSI3 clocks.

   List of clock domains:
     - HAL_clk_mMMSSCSI3ClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkCAMSSCSI3.c#1 $

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
 *  HAL_clk_mCSI3ClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mCSI3ClkDomainClks[] =
{
  {
    /* .szClockName      = */ "mmss_camss_csi3_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_CSI3_CBCR), HWIO_OFFS(MMSS_CAMSS_CSI3_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_CSI3_CLK
  },
  {
    /* .szClockName      = */ "mmss_camss_csi3pix_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_CSI3PIX_CBCR), HWIO_OFFS(MMSS_CAMSS_CSI3PIX_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_CSI3PIX_CLK
  },
  {
    /* .szClockName      = */ "mmss_camss_csi3rdi_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_CSI3RDI_CBCR), HWIO_OFFS(MMSS_CAMSS_CSI3RDI_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_CSI3RDI_CLK
  },
};


/*
 * HAL_clk_mMMSSCSI3ClkDomain
 *
 * CSI3 clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mMMSSCSI3ClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(MMSS_CSI3_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mCSI3ClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mCSI3ClkDomainClks)/sizeof(HAL_clk_mCSI3ClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mMMSSClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

