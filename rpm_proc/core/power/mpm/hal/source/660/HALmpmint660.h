#ifndef HALMPMINT660_H
#define HALMPMINT660_H

/*
===========================================================================

FILE:         HALmpmint8998.h

DESCRIPTION:
  Target-specific enumerations for HALmpmint.

===========================================================================

                             Edit History

$Header: //components/rel/rpm.bf/1.8/core/power/mpm/hal/source/660/HALmpmint660.h#2 $
$Date: 2017/03/15 $

when       who     what, where, why
--------   ---     --------------------------------------------------------

===========================================================================
             Copyright (c) 2015 Qualcomm Technologies, Inc.
                    All Rights Reserved.
              QUALCOMM Proprietary and Confidential
===========================================================================
*/

#ifdef __cplusplus
extern "C" {
#endif

/* -----------------------------------------------------------------------
**                           INCLUDES
** ----------------------------------------------------------------------- */

#include "comdef.h"

/* -----------------------------------------------------------------------
**                           TYPES
** ----------------------------------------------------------------------- */

/*
 * HAL_mpmint_IsrType
 *
 * List of possible interrupt sources.  All of these are not necessarily
 * supported on the HW.
 *
 * NOTE: This list must be in the same order as the lists in the
 *       MPM driver.
 */
typedef enum
{
  /* Hard Wired */
  HAL_MPMINT_QTIMER_ISR              =  0,
  HAL_MPMINT_PEN_ISR                 =  1,
  HAL_MPMINT_TSENS_UPPER_LOWER_ISR   =  2,

  /* High Voltage */
  HAL_MPMINT_GPIO1_ISR               =  3,
  HAL_MPMINT_GPIO5_ISR               =  4,
  HAL_MPMINT_GPIO9_ISR               =  5,
  HAL_MPMINT_GPIO10_ISR              =  6,
  HAL_MPMINT_GPIO66_ISR              =  7,
  HAL_MPMINT_GPIO22_ISR              =  8,
  HAL_MPMINT_GPIO25_ISR              =  9,
  HAL_MPMINT_GPIO28_ISR              = 10,
  HAL_MPMINT_GPIO58_ISR              = 11,
  HAL_MPMINT_OPEN0_ISR               = 12,
  HAL_MPMINT_GPIO41_ISR              = 13,
  HAL_MPMINT_GPIO43_ISR              = 14,
  HAL_MPMINT_GPIO40_ISR              = 15,
  HAL_MPMINT_GPIO42_ISR              = 16,
  HAL_MPMINT_GPIO46_ISR              = 17,
  HAL_MPMINT_GPIO50_ISR              = 18,
  HAL_MPMINT_GPIO44_ISR              = 19,
  HAL_MPMINT_OPEN1_ISR               = 20,
  HAL_MPMINT_GPIO56_ISR              = 21,
  HAL_MPMINT_GPIO45_ISR              = 22,
  HAL_MPMINT_GPIO68_ISR              = 23,
  HAL_MPMINT_GPIO69_ISR              = 24,
  HAL_MPMINT_GPIO70_ISR              = 25,
  HAL_MPMINT_GPIO71_ISR              = 26,
  HAL_MPMINT_GPIO72_ISR              = 27,
  HAL_MPMINT_GPIO73_ISR              = 28,
  HAL_MPMINT_GPIO64_ISR              = 29,
  HAL_MPMINT_GPIO2_ISR               = 30,
  HAL_MPMINT_GPIO13_ISR              = 31,
  HAL_MPMINT_GPIO111_ISR             = 32,
  HAL_MPMINT_GPIO74_ISR              = 33,
  HAL_MPMINT_GPIO75_ISR              = 34,
  HAL_MPMINT_GPIO76_ISR              = 35,
  HAL_MPMINT_GPIO82_ISR              = 36,
  HAL_MPMINT_GPIO17_ISR              = 37,
  HAL_MPMINT_GPIO77_ISR              = 38,
  HAL_MPMINT_GPIO47_ISR              = 39,
  HAL_MPMINT_GPIO54_ISR              = 40,
  HAL_MPMINT_GPIO48_ISR              = 41,
  HAL_MPMINT_GPIO101_ISR             = 42,
  HAL_MPMINT_GPIO49_ISR              = 43,
  HAL_MPMINT_GPIO51_ISR              = 44,
  HAL_MPMINT_GPIO86_ISR              = 45,
  HAL_MPMINT_GPIO90_ISR              = 46,
  HAL_MPMINT_GPIO91_ISR              = 47,
  HAL_MPMINT_GPIO52_ISR              = 48,
  HAL_MPMINT_USB30_PWR_EVT_ISR       = 49,
  HAL_MPMINT_GPIO55_ISR              = 50,
  HAL_MPMINT_GPIO6_ISR               = 51,
  HAL_MPMINT_PCIE_USB3_PHY_ISR       = 52,
  HAL_MPMINT_GPIO65_ISR              = 53,
  HAL_MPMINT_OPEN2_ISR               = 54,
  HAL_MPMINT_GPIO67_ISR              = 55,
  HAL_MPMINT_GPIO83_ISR              = 56,
  HAL_MPMINT_GPIO84_ISR              = 57,
  HAL_MPMINT_GPIO85_ISR              = 58,
  HAL_MPMINT_GPIO87_ISR              = 59,
  HAL_MPMINT_OPEN3_ISR               = 60,
  HAL_MPMINT_OPEN4_ISR               = 61,
  HAL_MPMINT_OPEN5_ISR               = 62,
  HAL_MPMINT_GPIO21_ISR              = 63,
  HAL_MPMINT_GPIO78_ISR              = 64,
  HAL_MPMINT_GPIO113_ISR             = 65,
  HAL_MPMINT_GPIO60_ISR              = 66,
  HAL_MPMINT_GPIO98_ISR              = 67,
  HAL_MPMINT_GPIO30_ISR              = 68,
  HAL_MPMINT_SDC1_DATA1_ISR          = 69,
  HAL_MPMINT_GPIO31_ISR              = 70,
  HAL_MPMINT_GPIO29_ISR              = 71,
  HAL_MPMINT_OPEN6_ISR               = 72,
  HAL_MPMINT_OPEN7_ISR               = 73,
  HAL_MPMINT_OPEN8_ISR               = 74,
  HAL_MPMINT_OPEN9_ISR               = 75,
  HAL_MPMINT_GPIO107_ISR             = 76,
  HAL_MPMINT_OPEN10_ISR               = 77,
  HAL_MPMINT_SRST_N_ISR              = 78,
  HAL_MPMINT_USB_PHY_DMSE_HV_ISR_1   = 79,
  HAL_MPMINT_USB_PHY_DMSE_HV_ISR_2   = 80,
  HAL_MPMINT_USB_PHY_DPSE_HV_ISR_1   = 81,
  HAL_MPMINT_USB_PHY_DPSE_HV_ISR_2   = 82,
  HAL_MPMINT_GPIO109_ISR             = 83,
  HAL_MPMINT_GPIO103_ISR             = 84,
  HAL_MPMINT_GPIO105_ISR             = 85,
  HAL_MPMINT_MPM_CLK_REQ_ISR         = 86,

  /* Always On */
  HAL_MPMINT_MPM_WAKE_SPMI_ISR       = 87,
  HAL_MPMINT_OPEN11_ISR              = 88,
  HAL_MPMINT_OPEN12_ISR              = 89,
  HAL_MPMINT_LPASS_SPM_BRINGUP_REQ_ISR  = 90,
  HAL_MPMINT_LPASS_PMPU_ISR          = 91,
  HAL_MPMINT_OPEN13_ISR              = 92,
  HAL_MPMINT_WCSS_MPM_WAKEUP_ISR     = 93,
  HAL_MPMINT_UIM_CONTROLLER_CARD_ISR = 94,
  HAL_MPMINT_UIM_CONTROLLER_BATT_ISR = 95,

  HAL_MPMINT_NUM                     = 96,

  /* Interrupts below this point are legacy definitions, not supported by this
   * version of the hardware. */
  HAL_MPMINT_NOT_DEFINED_ISR         = HAL_MPMINT_NUM,
} HAL_mpmint_IsrType;

#ifdef __cplusplus
}
#endif

#endif /* HALMPMINT660_H */

