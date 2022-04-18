#ifndef __ICB_RPM_HWIO_H__
#define __ICB_RPM_HWIO_H__
/*
===========================================================================
*/
/**
  @file icb_rpm_hwio.h

  @brief Additional HWIO definitions for ICB RPM driver.
*/
/*
===========================================================================

  Copyright (c) 2016 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

===========================================================================

  $Header: //components/rel/rpm.bf/1.8/core/systemdrivers/icb/src/660/icb_rpm_hwio.h#2 $
  $DateTime: 2016/11/07 22:46:44 $
  $Author: pwbldsvc $

===========================================================================
*/
#include "msmhwiobase.h"

#ifndef BIMC_REG_BASE
#define BIMC_REG_BASE  (DDR_SS_BASE      + 0x00003000)
#endif /* BIMC_REG_BASE */

#define A2_NOC_AGGRE2_NOC_BASE  (A2_NOC_AGGRE2_NOC_WRAPPER_BASE + 0x00040000)

#endif /* __ICB_RPM_HWIO_H__ */
