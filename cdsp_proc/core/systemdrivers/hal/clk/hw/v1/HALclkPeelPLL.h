#ifndef __HALCLKPEELPLL_H__
#define __HALCLKPEELPLL_H__
/*
==============================================================================

FILE:         HALclkPeelPLL.h

DESCRIPTION:
  Internal, chipset specific PLL definitions for the clock HAL module.

==============================================================================

                             Edit History

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/v1/HALclkPeelPLL.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------- 
10/02/14   dcf     Created.

==============================================================================
            Copyright (c) 2014 Qualcomm Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/

#include "HALclkInternal.h"



/* ============================================================================
**    Definitions
** ==========================================================================*/


/*
 * PLL register offsets.
 */
#define HWIO_PLL_MODE_OFFS                                  0x00000000
#define HWIO_PLL_L_VAL_OFFS                                 0x00000004
#define HWIO_PLL_CAL_L_VAL_OFFS                             0x00000008
#define HWIO_PLL_USER_CTL_OFFS                              0x0000000c
#define HWIO_PLL_USER_CTL_U_OFFS                            0x00000010
#define HWIO_PLL_CONFIG_CTL_OFFS                            0x00000014
#define HWIO_PLL_TEST_CTL_OFFS                              0x00000018
#define HWIO_PLL_TEST_CTL_U_OFFS                            0x0000001c
#define HWIO_PLL_STATUS_OFFS                                0x00000020
#define HWIO_PLL_FREQ_CTL_OFFS                              0x00000024
#define HWIO_PLL_OPMODE_OFFS                                0x00000028
/*
 * PLL_MODE register definitions.
 */
#define HWIO_PLL_MODE_PLL_LOCK_DET_BMSK                     0x80000000
#define HWIO_PLL_MODE_PLL_LOCK_DET_SHFT                           0x1f
#define HWIO_PLL_MODE_PLL_ACK_LATCH_BMSK                    0x20000000
#define HWIO_PLL_MODE_PLL_ACK_LATCH_SHFT                          0x1d
#define HWIO_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_BMSK         0x800000
#define HWIO_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_SHFT             0x17
#define HWIO_PLL_MODE_PLL_UPDATE_BMSK                         0x400000
#define HWIO_PLL_MODE_PLL_UPDATE_SHFT                             0x16
#define HWIO_PLL_MODE_PLL_RESET_N_BMSK                             0x4
#define HWIO_PLL_MODE_PLL_RESET_N_SHFT                             0x2
#define HWIO_PLL_MODE_PLL_OUTCTRL_BMSK                             0x1
#define HWIO_PLL_MODE_PLL_OUTCTRL_SHFT                             0x0

/*
 * PLL_USER_CTL register definitions.
 */
#define HWIO_PLL_USER_CTL_PRE_DIV_RATIO_BMSK                    0x7000
#define HWIO_PLL_USER_CTL_PRE_DIV_RATIO_SHFT                       0xc
#define HWIO_PLL_USER_CTL_POST_DIV_RATIO_BMSK                    0x300
#define HWIO_PLL_USER_CTL_POST_DIV_RATIO_SHFT                      0x8
#define HWIO_PLL_USER_CTL_OUTPUT_CLK_POLARITY_BMSK                0x80
#define HWIO_PLL_USER_CTL_OUTPUT_CLK_POLARITY_SHFT                 0x7
#define HWIO_PLL_USER_CTL_PLLOUT_LV_TEST_BMSK                     0x10
#define HWIO_PLL_USER_CTL_PLLOUT_LV_TEST_SHFT                      0x4
#define HWIO_PLL_USER_CTL_PLLOUT_LV_MAIN_BMSK                      0x1
#define HWIO_PLL_USER_CTL_PLLOUT_LV_MAIN_SHFT                      0x0


/*
 * PLL_USER_CTL_U register definitions.
 */

#define HWIO_PLL_USER_CTL_U_BIAS_ON_IN_STANDBY_BMSK             0x1000
#define HWIO_PLL_USER_CTL_U_BIAS_ON_IN_STANDBY_SHFT                0xc
#define HWIO_PLL_USER_CTL_U_REF_CLK_AT_OUT_BMSK                  0x800
#define HWIO_PLL_USER_CTL_U_REF_CLK_AT_OUT_SHFT                    0xb
#define HWIO_PLL_USER_CTL_U_SCALE_STATE_ON_RESTART_BMSK          0x600
#define HWIO_PLL_USER_CTL_U_SCALE_STATE_ON_RESTART_SHFT            0x9
#define HWIO_PLL_USER_CTL_U_LATCH_INTERFACE_BYPASS_BMSK          0x100
#define HWIO_PLL_USER_CTL_U_LATCH_INTERFACE_BYPASS_SHFT            0x8
#define HWIO_PLL_USER_CTL_U_STATUS_REGISTER_BMSK                  0xE0
#define HWIO_PLL_USER_CTL_U_STATUS_REGISTER_SHFT                   0x5
#define HWIO_PLL_USER_CTL_U_WRITE_STATE_BMSK                      0x10
#define HWIO_PLL_USER_CTL_U_WRITE_STATE_SHFT                       0x4
#define HWIO_PLL_USER_CTL_U_CALIB_CTL_BMSK                         0xE
#define HWIO_PLL_USER_CTL_U_CALIB_CTL_SHFT                         0x1
#define HWIO_PLL_USER_CTL_U_USE_ONLY_FINE_DET_BMSK                 0x1
#define HWIO_PLL_USER_CTL_U_USE_ONLY_FINE_DET_SHFT                 0x0


/*
 * PLL_OPMODE register definitions.
 */

#define HWIO_PLL_OPMODE_PLL_OPMODE_BMSK                            0x7
#define HWIO_PLL_OPMODE_PLL_OPMODE_SHFT                            0x0



/* ============================================================================
**    External Definitions
** ==========================================================================*/


/* ============================================================================
**    External Definitions
** ==========================================================================*/


/* ============================================================================
**    Functions
** ==========================================================================*/

/*
 * Source control functions.  These can be used if some of the control
 * needs to be overridden by a specific PLL.
 */
static boolean HAL_clk_PeelPLLEnable           ( HAL_clk_SourceDescType *pSource, HAL_clk_SourceDisableModeType eMode, void *pData );
static void    HAL_clk_PeelPLLDisable          ( HAL_clk_SourceDescType *pSource, HAL_clk_SourceDisableModeType eMode, void *pData );
static boolean HAL_clk_PeelPLLIsEnabled           ( HAL_clk_SourceDescType *pSource );
static void    HAL_clk_PeelPLLConfig           ( HAL_clk_SourceDescType *pSource, HAL_clk_SourceConfigType eConfig );
static boolean HAL_clk_PeelPLLConfigPLL        ( HAL_clk_SourceDescType *pSource, const HAL_clk_PLLConfigType *pmConfig, HAL_clk_SourceConfigMode eMode);
static void    HAL_clk_PeelPLLDetectPLLConfig  ( HAL_clk_SourceDescType *pSource, HAL_clk_PLLConfigType *pmConfig );

#endif  /* __HALCLKPEELPLL_H__ */

