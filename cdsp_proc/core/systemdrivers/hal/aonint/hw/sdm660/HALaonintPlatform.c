/*
===========================================================================

FILE:         HALaonintPlatformModem.c

DESCRIPTION:  
  This is the platform hardware abstraction layer implementation for the
  Always On Interrupt block.
  This platform is for the Target processor on the MSM8996.

===========================================================================

                             Edit History

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/aonint/hw/sdm660/HALaonintPlatform.c#1 $

when       who     what, where, why
--------   ---     --------------------------------------------------------
11/04/14   cpaulo  Created.

===========================================================================
        Copyright (c) 2014 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
===========================================================================
*/

/* -----------------------------------------------------------------------
**                           INCLUDES
** ----------------------------------------------------------------------- */

#include <HALhwio.h>
#include "HALaonint.h"
#include "HALaonintHWIO.h"

/* -----------------------------------------------------------------------
**                           FUNCTIONS
** ----------------------------------------------------------------------- */

/* ===========================================================================
**  HAL_aonint_PlatformInitEarly
**
** ======================================================================== */

void HAL_aonint_PlatformInitEarly ( HAL_aonint_PlatformInfo *pmPlatform )
{
  pmPlatform->nClearRegs[0]         = HWIO_LPASS_PMU_INT_CLR0_ADDR;
  pmPlatform->nClearRegs[1]         = HWIO_LPASS_PMU_INT_CLR1_ADDR;
  pmPlatform->nClearRegs[2]         = HWIO_LPASS_PMU_INT_CLR2_ADDR;
  pmPlatform->nClearRegs[3]         = HWIO_LPASS_PMU_INT_CLR3_ADDR;
  pmPlatform->nClearRegs[4]         = HWIO_LPASS_PMU_INT_CLR4_ADDR;
  pmPlatform->nEnableRegs[0]        = HWIO_LPASS_PMU_INT_EN0_ADDR;
  pmPlatform->nEnableRegs[1]        = HWIO_LPASS_PMU_INT_EN1_ADDR;
  pmPlatform->nEnableRegs[2]        = HWIO_LPASS_PMU_INT_EN2_ADDR;
  pmPlatform->nEnableRegs[3]        = HWIO_LPASS_PMU_INT_EN3_ADDR;
  pmPlatform->nEnableRegs[4]        = HWIO_LPASS_PMU_INT_EN4_ADDR;
  pmPlatform->nPolarityRegs[0]      = HWIO_LPASS_PMU_INT_POL0_ADDR;
  pmPlatform->nPolarityRegs[1]      = HWIO_LPASS_PMU_INT_POL1_ADDR;
  pmPlatform->nPolarityRegs[2]      = HWIO_LPASS_PMU_INT_POL2_ADDR;
  pmPlatform->nPolarityRegs[3]      = HWIO_LPASS_PMU_INT_POL3_ADDR;
  pmPlatform->nPolarityRegs[4]      = HWIO_LPASS_PMU_INT_POL4_ADDR;
  pmPlatform->nPositiveEdgeRegs[0]  = HWIO_LPASS_PMU_INT_POS_EDGE_EN0_ADDR;
  pmPlatform->nPositiveEdgeRegs[1]  = HWIO_LPASS_PMU_INT_POS_EDGE_EN1_ADDR;
  pmPlatform->nPositiveEdgeRegs[2]  = HWIO_LPASS_PMU_INT_POS_EDGE_EN2_ADDR;
  pmPlatform->nPositiveEdgeRegs[3]  = HWIO_LPASS_PMU_INT_POS_EDGE_EN3_ADDR;
  pmPlatform->nPositiveEdgeRegs[4]  = HWIO_LPASS_PMU_INT_POS_EDGE_EN4_ADDR;
  pmPlatform->nNegativeEdgeRegs[0]  = HWIO_LPASS_PMU_INT_NEG_EDGE_EN0_ADDR;
  pmPlatform->nNegativeEdgeRegs[1]  = HWIO_LPASS_PMU_INT_NEG_EDGE_EN1_ADDR;
  pmPlatform->nNegativeEdgeRegs[2]  = HWIO_LPASS_PMU_INT_NEG_EDGE_EN2_ADDR;
  pmPlatform->nNegativeEdgeRegs[3]  = HWIO_LPASS_PMU_INT_NEG_EDGE_EN3_ADDR;
  pmPlatform->nNegativeEdgeRegs[4]  = HWIO_LPASS_PMU_INT_NEG_EDGE_EN4_ADDR;
  pmPlatform->nStatusRegs[0]        = HWIO_LPASS_PMU_INT_EN0_ADDR;
  pmPlatform->nStatusRegs[1]        = HWIO_LPASS_PMU_INT_EN1_ADDR;
  pmPlatform->nStatusRegs[2]        = HWIO_LPASS_PMU_INT_EN2_ADDR;
  pmPlatform->nStatusRegs[3]        = HWIO_LPASS_PMU_INT_EN3_ADDR;
  pmPlatform->nStatusRegs[4]        = HWIO_LPASS_PMU_INT_EN4_ADDR;
} /* END HAL_aonint_PlatformInitEarly */

