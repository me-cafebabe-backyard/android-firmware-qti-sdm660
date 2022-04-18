/*
===========================================================================

FILE:         HALmpmintPlatform.c

DESCRIPTION:
  This is the platform hardware abstraction layer implementation for the
  MPM interrupt controller block.
  This platform is for the RPM on 8998.

===========================================================================

                             Edit History

$Header: //components/rel/rpm.bf/1.8/core/power/mpm/hal/source/660/HALmpmintTable.c#3 $

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

#include <HALmpmint.h>
#include "HALmpmintInternal.h"

/* -----------------------------------------------------------------------
**                           TYPES
** ----------------------------------------------------------------------- */

/* -----------------------------------------------------------------------
**                           DATA
** ----------------------------------------------------------------------- */

/*
 * DEFINE_IRQ
 *
 * Macro to define an IRQ mpmint_irq_data_type entry in the table
 */
#define DEFINE_IRQ( trigger, gpio, padPos ) \
  {                                                 \
    HAL_MPMINT_TRIGGER_##trigger,                   \
    gpio,                                           \
    padPos,                                         \
  }

/*
 * Target-specific interrupt configurations
 */
HAL_mpmint_PlatformIntType aInterruptTable[HAL_MPMINT_NUM] =
{
  /*          Trigger            GPIO                      Pad Bit          */
  /*          -------  -----------------------   -------------------------- */
  DEFINE_IRQ( HIGH,    HAL_MPMINT_INVALID_GPIO,  HAL_MPMINT_INVALID_BIT_POS ), /* HAL_MPMINT_QTIMER_ISR              =  0 */
  DEFINE_IRQ( RISING,  HAL_MPMINT_INVALID_GPIO,  HAL_MPMINT_INVALID_BIT_POS ), /* HAL_MPMINT_PEN_ISR                 =  1 */
  DEFINE_IRQ( HIGH,    HAL_MPMINT_INVALID_GPIO,  HAL_MPMINT_INVALID_BIT_POS ), /* HAL_MPMINT_TSENS_UPPER_LOWER_ISR   =  2 */
  DEFINE_IRQ( RISING,  1,                        64 + 0                     ), /* HAL_MPMINT_GPIO1_ISR               =  3 */
  DEFINE_IRQ( RISING,  5,                        64 + 2                     ), /* HAL_MPMINT_GPIO5_ISR               =  4 */
  DEFINE_IRQ( RISING,  9,                        32 + 6                     ), /* HAL_MPMINT_GPIO9_ISR               =  5 */
  DEFINE_IRQ( RISING,  10,                       32 + 7                     ), /* HAL_MPMINT_GPIO10_ISR              =  6 */
  DEFINE_IRQ( RISING,  66,                       32 + 12                    ), /* HAL_MPMINT_GPIO66_ISR              =  7 */
  DEFINE_IRQ( RISING,  22,                       4                          ), /* HAL_MPMINT_GPIO22_ISR              =  8 */
  DEFINE_IRQ( RISING,  25,                       32 + 9                     ), /* HAL_MPMINT_GPIO25_ISR              =  9 */
  DEFINE_IRQ( RISING,  28,                       5                          ), /* HAL_MPMINT_GPIO28_ISR              = 10 */
  DEFINE_IRQ( RISING,  58,                       64 + 20                    ), /* HAL_MPMINT_GPIO58_ISR              = 11 */
  DEFINE_IRQ( RISING,  HAL_MPMINT_INVALID_GPIO,  HAL_MPMINT_INVALID_BIT_POS ), /* HAL_MPMINT_GPIO91_ISR              = 12 */
  DEFINE_IRQ( RISING,  41,                       64 + 6                     ), /* HAL_MPMINT_GPIO41_ISR              = 13 */
  DEFINE_IRQ( RISING,  43,                       64 + 8                     ), /* HAL_MPMINT_GPIO43_ISR              = 14 */
  DEFINE_IRQ( RISING,  40,                       64 + 5                     ), /* HAL_MPMINT_GPIO40_ISR              = 15 */
  DEFINE_IRQ( RISING,  42,                       64 + 7                     ), /* HAL_MPMINT_GPIO42_ISR              = 16 */
  DEFINE_IRQ( RISING,  46,                       64 + 11                    ), /* HAL_MPMINT_GPIO46_ISR              = 17 */
  DEFINE_IRQ( RISING,  50,                       64 + 15                    ), /* HAL_MPMINT_GPIO50_ISR              = 18 */
  DEFINE_IRQ( RISING,  44,                       64 + 9                     ), /* HAL_MPMINT_GPIO44_ISR              = 19 */
  DEFINE_IRQ( RISING,  HAL_MPMINT_INVALID_GPIO,  HAL_MPMINT_INVALID_BIT_POS ), /* HAL_MPMINT_GPIO87_ISR              = 20 */
  DEFINE_IRQ( RISING,  56,                       64 + 19                    ), /* HAL_MPMINT_GPIO56_ISR              = 21 */
  DEFINE_IRQ( RISING,  45,                       64 + 10                    ), /* HAL_MPMINT_GPIO45_ISR              = 22 */
  DEFINE_IRQ( RISING,  68,                       32 + 14                    ), /* HAL_MPMINT_GPIO68_ISR              = 23 */
  DEFINE_IRQ( RISING,  69,                       32 + 15                    ), /* HAL_MPMINT_GPIO69_ISR              = 24 */
  DEFINE_IRQ( RISING,  70,                       32 + 16                    ), /* HAL_MPMINT_GPIO70_ISR              = 25 */
  DEFINE_IRQ( RISING,  71,                       32 + 17                    ), /* HAL_MPMINT_GPIO71_ISR              = 26 */
  DEFINE_IRQ( RISING,  72,                       32 + 18                    ), /* HAL_MPMINT_GPIO72_ISR              = 27 */
  DEFINE_IRQ( RISING,  73,                       32 + 19                    ), /* HAL_MPMINT_GPIO73_ISR              = 28 */
  DEFINE_IRQ( RISING,  64,                       64 + 21                    ), /* HAL_MPMINT_GPIO64_ISR              = 29 */
  DEFINE_IRQ( RISING,  2,                        64 + 1                     ), /* HAL_MPMINT_GPIO2_ISR               = 30 */
  DEFINE_IRQ( RISING,  13,                       32 + 8                     ), /* HAL_MPMINT_GPIO13_ISR              = 31 */
  DEFINE_IRQ( RISING,  111,                      96 + 4                     ), /* HAL_MPMINT_GPIO111_ISR             = 32 */
  DEFINE_IRQ( RISING,  74,                       32 + 20                    ), /* HAL_MPMINT_GPIO74_ISR              = 33 */
  DEFINE_IRQ( RISING,  75,                       32 + 21                    ), /* HAL_MPMINT_GPIO75_ISR              = 34 */
  DEFINE_IRQ( RISING,  76,                       32 + 22                    ), /* HAL_MPMINT_GPIO76_ISR              = 35 */
  DEFINE_IRQ( RISING,  82,                       9                          ), /* HAL_MPMINT_GPIO82_ISR              = 36 */
  DEFINE_IRQ( RISING,  17,                       3                    		), /* HAL_MPMINT_GPIO17_ISR              = 37 */
  DEFINE_IRQ( RISING,  77,                       32 + 23                    ), /* HAL_MPMINT_GPIO77_ISR              = 38 */
  DEFINE_IRQ( RISING,  47,                       64 + 12                    ), /* HAL_MPMINT_GPIO47_ISR              = 39 */
  DEFINE_IRQ( RISING,  54,                       32 + 10                    ), /* HAL_MPMINT_GPIO54_ISR              = 40 */
  DEFINE_IRQ( RISING,  48,                       64 + 13                    ), /* HAL_MPMINT_GPIO48_ISR              = 41 */
  DEFINE_IRQ( RISING,  101,                      64 + 31                    ), /* HAL_MPMINT_GPIO101_ISR             = 42 */
  DEFINE_IRQ( RISING,  49,                       64 + 14                    ), /* HAL_MPMINT_GPIO49_ISR              = 43 */
  DEFINE_IRQ( RISING,  51,                       64 + 16                    ), /* HAL_MPMINT_GPIO51_ISR              = 44 */
  DEFINE_IRQ( RISING,  86,                       64 + 26                    ), /* HAL_MPMINT_GPIO86_ISR              = 45 */
  DEFINE_IRQ( RISING,  90,                       64 + 28                    ), /* HAL_MPMINT_GPIO90_ISR              = 46 */
  DEFINE_IRQ( RISING,  91,                       64 + 29                    ), /* HAL_MPMINT_GPIO91_ISR              = 47 */
  DEFINE_IRQ( RISING,  52,                       64 + 17                    ), /* HAL_MPMINT_GPIO52_ISR              = 48 */
  DEFINE_IRQ( DUAL,    HAL_MPMINT_INVALID_GPIO,  HAL_MPMINT_INVALID_BIT_POS ), /* HAL_MPMINT_USB30_PWR_EVT_ISR       = 49 */
  DEFINE_IRQ( RISING,  55,                       64 + 18                    ), /* HAL_MPMINT_GPIO55_ISR              = 50 */
  DEFINE_IRQ( RISING,  6,                        64 + 3                     ), /* HAL_MPMINT_GPIO6_ISR               = 51 */
  DEFINE_IRQ( DUAL,    HAL_MPMINT_INVALID_GPIO,  HAL_MPMINT_INVALID_BIT_POS ), /* HAL_MPMINT_PCIE_USB3_PHY_ISR       = 52 */
  DEFINE_IRQ( RISING,  65,  					 64 + 22 					), /* HAL_MPMINT_GPIO65_ISR              = 53 */
  DEFINE_IRQ( RISING,  HAL_MPMINT_INVALID_GPIO,  HAL_MPMINT_INVALID_BIT_POS ), /* HAL_MPMINT_GPIO67_ISR              = 54 */
  DEFINE_IRQ( RISING,  67,                       32 + 13                    ), /* HAL_MPMINT_GPIO67_ISR              = 55 */
  DEFINE_IRQ( RISING,  83,                       64 + 23                    ), /* HAL_MPMINT_GPIO83_ISR              = 56 */
  DEFINE_IRQ( RISING,  84,                       64 + 24                    ), /* HAL_MPMINT_GPIO84_ISR              = 57 */
  DEFINE_IRQ( RISING,  85,                       64 + 25                    ), /* HAL_MPMINT_GPIO85_ISR              = 58 */
  DEFINE_IRQ( RISING,  87,                       64 + 27                    ), /* HAL_MPMINT_GPIO87_ISR              = 59 */
  DEFINE_IRQ( RISING,  HAL_MPMINT_INVALID_GPIO,  HAL_MPMINT_INVALID_BIT_POS ), /* HAL_MPMINT_OPEN0_ISR               = 60 */
  DEFINE_IRQ( RISING,  HAL_MPMINT_INVALID_GPIO,  HAL_MPMINT_INVALID_BIT_POS ), /* HAL_MPMINT_OPEN1_ISR               = 61 */
  DEFINE_IRQ( RISING,  HAL_MPMINT_INVALID_GPIO,  HAL_MPMINT_INVALID_BIT_POS ), /* HAL_MPMINT_OPEN2_ISR               = 62 */
  DEFINE_IRQ( RISING,  21,                       64 + 4                     ), /* HAL_MPMINT_GPIO21_ISR              = 63 */
  DEFINE_IRQ( RISING,  78,                       32 + 24                    ), /* HAL_MPMINT_GPIO78_ISR              = 64 */
  DEFINE_IRQ( RISING,  113,                      96 + 5                     ), /* HAL_MPMINT_GPIO113_ISR             = 65 */
  DEFINE_IRQ( RISING,  60,                       32 + 11                    ), /* HAL_MPMINT_GPIO60_ISR              = 66 */
  DEFINE_IRQ( RISING,  98,                       64 + 30                    ), /* HAL_MPMINT_GPIO98_ISR              = 67 */
  DEFINE_IRQ( RISING,  30,                       7                          ), /* HAL_MPMINT_GPIO30_ISR              = 68 */
  DEFINE_IRQ( RISING,  HAL_MPMINT_INVALID_GPIO,  32 + 0                     ), /* HAL_MPMINT_SDC1_DATA1_ISR          = 69 */
  DEFINE_IRQ( RISING,  31,  					 8 							), /* HAL_MPMINT_GPIO31_ISR              = 70 */
  DEFINE_IRQ( RISING,  29,  					 6 							), /* HAL_MPMINT_GPIO29_ISR              = 71 */
  DEFINE_IRQ( RISING,  HAL_MPMINT_INVALID_GPIO,  HAL_MPMINT_INVALID_BIT_POS ), /* HAL_MPMINT_OPEN5_ISR               = 72 */
  DEFINE_IRQ( RISING,  HAL_MPMINT_INVALID_GPIO,  HAL_MPMINT_INVALID_BIT_POS	), /* HAL_MPMINT_OPEN6_ISR               = 73 */
  DEFINE_IRQ( RISING,  HAL_MPMINT_INVALID_GPIO,  HAL_MPMINT_INVALID_BIT_POS ), /* HAL_MPMINT_OPEN7_ISR               = 74 */
  DEFINE_IRQ( RISING,  HAL_MPMINT_INVALID_GPIO,  HAL_MPMINT_INVALID_BIT_POS ), /* HAL_MPMINT_OPEN8_ISR               = 75 */
  DEFINE_IRQ( RISING,  107,  					 96 + 2 					), /* HAL_MPMINT_GPIO107_ISR             = 76 */
  DEFINE_IRQ( RISING,  HAL_MPMINT_INVALID_GPIO,  HAL_MPMINT_INVALID_BIT_POS ), /* HAL_MPMINT_OPEN9_ISR                      = 77 */
  DEFINE_IRQ( RISING,  HAL_MPMINT_INVALID_GPIO,  32 + 5                     ), /* HAL_MPMINT_SRST_N_ISR              = 78 */
  DEFINE_IRQ( DUAL,    HAL_MPMINT_INVALID_GPIO,  HAL_MPMINT_INVALID_BIT_POS ), /* HAL_MPMINT_USB_PHY_DMSE_HV_ISR_1   = 79 */
  DEFINE_IRQ( DUAL,    HAL_MPMINT_INVALID_GPIO,  HAL_MPMINT_INVALID_BIT_POS ), /* HAL_MPMINT_USB_PHY_DMSE_HV_ISR_2   = 80 */
  DEFINE_IRQ( DUAL,    HAL_MPMINT_INVALID_GPIO,  HAL_MPMINT_INVALID_BIT_POS ), /* HAL_MPMINT_USB_PHY_DPSE_HV_ISR_1   = 81 */
  DEFINE_IRQ( DUAL,    HAL_MPMINT_INVALID_GPIO,  HAL_MPMINT_INVALID_BIT_POS ), /* HAL_MPMINT_USB_PHY_DPSE_HV_ISR_2   = 82 */
  DEFINE_IRQ( RISING,  109,                      96 + 3                     ), /* HAL_MPMINT_GPIO109_ISR             = 83 */
  DEFINE_IRQ( RISING,  103,                      96 + 0                     ), /* HAL_MPMINT_GPIO103_ISR             = 84 */
  DEFINE_IRQ( RISING,  105,                      96 + 1                     ), /* HAL_MPMINT_GPIO105_ISR             = 85 */
  DEFINE_IRQ( RISING,  HAL_MPMINT_INVALID_GPIO,  HAL_MPMINT_INVALID_BIT_POS ), /* HAL_MPMINT_MPM_CLK_REQ_ISR         = 86 */
  DEFINE_IRQ( HIGH,    HAL_MPMINT_INVALID_GPIO,  HAL_MPMINT_INVALID_BIT_POS ), /* HAL_MPMINT_MPM_WAKE_SPMI_ISR       = 87 */
  DEFINE_IRQ( RISING,  HAL_MPMINT_INVALID_GPIO,  HAL_MPMINT_INVALID_BIT_POS ), /* HAL_MPMINT_OPEN10_ISR              = 88 */
  DEFINE_IRQ( RISING,  HAL_MPMINT_INVALID_GPIO,  HAL_MPMINT_INVALID_BIT_POS ), /* HAL_MPMINT_OPEN11_ISR              = 89 */
  DEFINE_IRQ( HIGH,    HAL_MPMINT_INVALID_GPIO,  HAL_MPMINT_INVALID_BIT_POS ), /* HAL_MPMINT_LPASS_SPM_BRINGUP_REQ_ISR = 90 */
  DEFINE_IRQ( RISING,  HAL_MPMINT_INVALID_GPIO,  HAL_MPMINT_INVALID_BIT_POS ), /* HAL_MPMINT_LPASS_PMPU_ISR          = 91 */
  DEFINE_IRQ( RISING,  HAL_MPMINT_INVALID_GPIO,  HAL_MPMINT_INVALID_BIT_POS ), /* HAL_MPMINT_OPEN12_ISR              = 92 */
  DEFINE_IRQ( HIGH,    HAL_MPMINT_INVALID_GPIO,  HAL_MPMINT_INVALID_BIT_POS ), /* HAL_MPMINT_WCSS_MPM_WAKEUP_ISR     = 93 */
  DEFINE_IRQ( HIGH,    HAL_MPMINT_INVALID_GPIO,  HAL_MPMINT_INVALID_BIT_POS ), /* HAL_MPMINT_UIM_CONTROLLER_CARD_ISR = 94 */
  DEFINE_IRQ( HIGH,    HAL_MPMINT_INVALID_GPIO,  HAL_MPMINT_INVALID_BIT_POS ), /* HAL_MPMINT_UIM_CONTROLLER_BATT_ISR = 95 */
};

