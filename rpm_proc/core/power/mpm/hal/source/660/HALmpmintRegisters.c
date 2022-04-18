/*
===========================================================================

FILE:         HALmpmintRegisters.c

DESCRIPTION:
  Per Target register layout definitions

===========================================================================

                             Edit History

$Header: //components/rel/rpm.bf/1.8/core/power/mpm/hal/source/660/HALmpmintRegisters.c#1 $
$Date: 2016/11/03 $

when       who     what, where, why
--------   ---     --------------------------------------------------------

===========================================================================
             Copyright (c) 2015 Qualcomm Technologies, Inc.
                    All Rights Reserved.
              QUALCOMM Proprietary and Confidential
===========================================================================
*/

/* -----------------------------------------------------------------------
**                           INCLUDES
** ----------------------------------------------------------------------- */

#include "comdef.h"
#include "HALmpm.h"
#include "HALmpmintInternal.h"
#include "HALhwio.h"
#include "tlmm_hwio.h"
#include "mpm2_hwio.h"

/* -----------------------------------------------------------------------
**                           DATA
** ----------------------------------------------------------------------- */

/* We need to define the appropriate MPM registers, which can vary depending
 * on whather we need to talk to the actual MPM or to the virtual MPM, and
 * in the case of the virtual MPM it depends on the processor. */
HAL_mpmint_PlatformType registerLayout =
{
  /*.nEnableReg     = */
  {
      HWIO_MPM2_MPM_INT_EN_1_ADDR,
      HWIO_MPM2_MPM_INT_EN_2_ADDR,
      HWIO_MPM2_MPM_INT_EN_3_ADDR
  },

  /*.nEnableRegPad  = */
  {
      HWIO_TLMM_CENTER_MPM_WAKEUP_INT_EN_0_ADDR,
      HWIO_TLMM_NORTH_MPM_WAKEUP_INT_EN_0_ADDR,
      HWIO_TLMM_SOUTH_MPM_WAKEUP_INT_EN_0_ADDR,
	  HWIO_TLMM_SOUTH_MPM_WAKEUP_INT_EN_1_ADDR
  },

  /*.nStatusReg     = */
  {
      HWIO_MPM2_MPM_INT_STATUS_1_ADDR,
      HWIO_MPM2_MPM_INT_STATUS_2_ADDR,
      HWIO_MPM2_MPM_INT_STATUS_3_ADDR
  },

  /*.nClearReg      = */
  {
      HWIO_MPM2_MPM_INT_CLEAR_1_ADDR,
      HWIO_MPM2_MPM_INT_CLEAR_2_ADDR,
      HWIO_MPM2_MPM_INT_CLEAR_3_ADDR
  },

  /*.nDetectReg     = */
  {
      HWIO_MPM2_MPM_DETECT_CTL_1_ADDR,
      HWIO_MPM2_MPM_DETECT_CTL_2_ADDR,
      HWIO_MPM2_MPM_DETECT_CTL_3_ADDR,
      HWIO_MPM2_MPM_DETECT_CTL_4_ADDR,
      HWIO_MPM2_MPM_DETECT_CTL_5_ADDR,
      HWIO_MPM2_MPM_DETECT_CTL_6_ADDR
  },

  /*.nPolarityReg   = */
  {
      HWIO_MPM2_MPM_INT_POLARITY_1_ADDR,
      HWIO_MPM2_MPM_INT_POLARITY_2_ADDR,
      HWIO_MPM2_MPM_INT_POLARITY_3_ADDR
  }
};

