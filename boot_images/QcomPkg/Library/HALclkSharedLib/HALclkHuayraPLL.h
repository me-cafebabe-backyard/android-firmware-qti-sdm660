#ifndef __HALCLKHUAYRAPLL_H__
#define __HALCLKHUAYRAPLL_H__
/*
==============================================================================

FILE:         HALclkHuayraPLL.h

DESCRIPTION:
  Internal, chipset specific PLL definitions for the clock HAL module.

==============================================================================

                             Edit History

$Header: //components/rel/boot.xf/1.4/QcomPkg/Library/HALclkSharedLib/HALclkHuayraPLL.h#2 $

when       who     what, where, why
--------   ---     -----------------------------------------------------------
04/07/14   sr      Created.

==============================================================================
    Copyright (c) 2014 QUALCOMM Technologies Incorporated.
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
#define HWIO_PLL_ALPHA_VAL_OFFS                             0x00000008
#define HWIO_PLL_USER_CTL_OFFS                              0x00000010
#define HWIO_PLL_CONFIG_CTL_LO_OFFS                         0x00000018
#define HWIO_PLL_CONFIG_CTL_HI_OFFS                         0x0000001c
#define HWIO_PLL_TEST_CTL_LO_OFFS                           0x00000020
#define HWIO_PLL_TEST_CTL_HI_OFFS                           0x00000024
#define HWIO_PLL_STATUS_OFFS                                0x00000028
#define HWIO_PLL_SSC_DELTA_ALPHA_OFFS                       0x00000030
#define HWIO_PLL_SSC_UPDATE_RATE_OFFS                       0x00000034
#define HWIO_PLL_DFSFSM_CTL_OFFS                            0x00000050
#define HWIO_PLL_PWRFSM_CTL_OFFS                            0x0000005c
#define HWIO_MDD_MODE_OFFS                                  0x00000060
#define HWIO_MDD_CONFIG_CTL_OFFS                            0x00000064
#define HWIO_MDD_TEST_CTL_OFFS                              0x00000068
#define HWIO_MDD_USER_CTL_LO_OFFS                           0x00000070
#define HWIO_MDD_USER_CTL_HI_OFFS                           0x00000074


/*
 * PLL_MODE register definitions.
 */
#define HWIO_PLL_MODE_LOCK_DET_BMSK                         0x80000000
#define HWIO_PLL_MODE_LOCK_DET_SHFT                               0x1f
#define HWIO_PLL_MODE_ACTIVE_FLAG_BMSK                      0x40000000
#define HWIO_PLL_MODE_ACTIVE_FLAG_SHFT                            0x1e
#define HWIO_PLL_MODE_LCKINTR_BMSK                           0x4000000
#define HWIO_PLL_MODE_LCKINTR_SHFT                                0x1a
#define HWIO_PLL_MODE_FREQDECINC_BMSK                        0x2000000
#define HWIO_PLL_MODE_FREQDECINC_SHFT                             0x19
#define HWIO_PLL_MODE_APC_PDN_BMSK                           0x1000000
#define HWIO_PLL_MODE_APC_PDN_SHFT                                0x18
#define HWIO_PLL_MODE_FSM_EN_BMSK                             0x100000
#define HWIO_PLL_MODE_FSM_EN_SHFT                                 0x14
#define HWIO_PLL_MODE_BIAS_COUNT_BMSK                          0xfc000
#define HWIO_PLL_MODE_BIAS_COUNT_SHFT                              0xe
#define HWIO_PLL_MODE_LOCK_COUNT_BMSK                           0x3f00
#define HWIO_PLL_MODE_LOCK_COUNT_SHFT                              0x8
#define HWIO_PLL_MODE_PLLTEST_BMSK                                 0x8
#define HWIO_PLL_MODE_PLLTEST_SHFT                                 0x3
#define HWIO_PLL_MODE_RESET_N_BMSK                                 0x4
#define HWIO_PLL_MODE_RESET_N_SHFT                                 0x2
#define HWIO_PLL_MODE_BYPASSNL_BMSK                                0x2
#define HWIO_PLL_MODE_BYPASSNL_SHFT                                0x1
#define HWIO_PLL_MODE_OUTCTRL_BMSK                                 0x1
#define HWIO_PLL_MODE_OUTCTRL_SHFT                                 0x0


/*
 * PLL_USER_CTL register definitions.
 */
#define HWIO_PLL_USER_CTL_MN_EN_BMSK                         0x1000000
#define HWIO_PLL_USER_CTL_MN_EN_SHFT                              0x18
#define HWIO_PLL_USER_CTL_PREDIV2_EN_BMSK                       0x1000
#define HWIO_PLL_USER_CTL_PREDIV2_EN_SHFT                          0xc
#define HWIO_PLL_USER_CTL_POSTDIV_CTL_BMSK                       0x300
#define HWIO_PLL_USER_CTL_POSTDIV_CTL_SHFT                         0x8
#define HWIO_PLL_USER_CTL_INV_OUTPUT_BMSK                         0x80
#define HWIO_PLL_USER_CTL_INV_OUTPUT_SHFT                          0x7
#define HWIO_PLL_USER_CTL_LVTEST_EN_BMSK                          0x10
#define HWIO_PLL_USER_CTL_LVTEST_EN_SHFT                           0x4
#define HWIO_PLL_USER_CTL_LVEARLY_EN_BMSK                          0x8
#define HWIO_PLL_USER_CTL_LVEARLY_EN_SHFT                          0x3
#define HWIO_PLL_USER_CTL_LVAUX2_EN_BMSK                           0x4
#define HWIO_PLL_USER_CTL_LVAUX2_EN_SHFT                           0x2
#define HWIO_PLL_USER_CTL_LVAUX_EN_BMSK                            0x2
#define HWIO_PLL_USER_CTL_LVAUX_EN_SHFT                            0x1
#define HWIO_PLL_USER_CTL_LVMAIN_EN_BMSK                           0x1
#define HWIO_PLL_USER_CTL_LVMAIN_EN_SHFT                           0x0


/*
 * PLL_TEST_CTL_LO register definitions.
 */
#define HWIO_PLL_TEST_CTL_LO_D_FINE_OVERRIDE_VALUE_0_BMSK   0xfc000000
#define HWIO_PLL_TEST_CTL_LO_D_FINE_OVERRIDE_VALUE_0_SHFT         0x1a
#define HWIO_PLL_TEST_CTL_LO_D_FINE_OVERRIDE_BMSK            0x2000000
#define HWIO_PLL_TEST_CTL_LO_D_FINE_OVERRIDE_SHFT                 0x19
#define HWIO_PLL_TEST_CTL_LO_G_BWC_OVERRIDE_VALUE_BMSK       0x1fc0000
#define HWIO_PLL_TEST_CTL_LO_G_BWC_OVERRIDE_VALUE_SHFT            0x12
#define HWIO_PLL_TEST_CTL_LO_G_BWC_OVERRIDE_BMSK               0x20000
#define HWIO_PLL_TEST_CTL_LO_G_BWC_OVERRIDE_SHFT                  0x11
#define HWIO_PLL_TEST_CTL_LO_STAY_IN_CFA_BMSK                  0x10000
#define HWIO_PLL_TEST_CTL_LO_STAY_IN_CFA_SHFT                     0x10
#define HWIO_PLL_TEST_CTL_LO_SKIP_FFA_BMSK                      0x8000
#define HWIO_PLL_TEST_CTL_LO_SKIP_FFA_SHFT                         0xf
#define HWIO_PLL_TEST_CTL_LO_SKIP_CFA_BMSK                      0x4000
#define HWIO_PLL_TEST_CTL_LO_SKIP_CFA_SHFT                         0xe
#define HWIO_PLL_TEST_CTL_LO_RESET_FFA_TM_ACCUM_BMSK            0x2000
#define HWIO_PLL_TEST_CTL_LO_RESET_FFA_TM_ACCUM_SHFT               0xd
#define HWIO_PLL_TEST_CTL_LO_RESET_CFA_ACCUM_BMSK               0x1000
#define HWIO_PLL_TEST_CTL_LO_RESET_CFA_ACCUM_SHFT                  0xc
#define HWIO_PLL_TEST_CTL_LO_DISABLE_DDC_BMSK                    0x800
#define HWIO_PLL_TEST_CTL_LO_DISABLE_DDC_SHFT                      0xb
#define HWIO_PLL_TEST_CTL_LO_DISABLE_LFSR_BMSK                   0x400
#define HWIO_PLL_TEST_CTL_LO_DISABLE_LFSR_SHFT                     0xa
#define HWIO_PLL_TEST_CTL_LO_DISABLE_BBC_BMSK                    0x200
#define HWIO_PLL_TEST_CTL_LO_DISABLE_BBC_SHFT                      0x9
#define HWIO_PLL_TEST_CTL_LO_DISABLE_FBC_BMSK                    0x100
#define HWIO_PLL_TEST_CTL_LO_DISABLE_FBC_SHFT                      0x8
#define HWIO_PLL_TEST_CTL_LO_PLL_STATUS_SEL_BMSK                  0xc0
#define HWIO_PLL_TEST_CTL_LO_PLL_STATUS_SEL_SHFT                   0x6
#define HWIO_PLL_TEST_CTL_LO_DTEST_SEL_BMSK                       0x20
#define HWIO_PLL_TEST_CTL_LO_DTEST_SEL_SHFT                        0x5
#define HWIO_PLL_TEST_CTL_LO_BYP_TESTAMP_BMSK                     0x10
#define HWIO_PLL_TEST_CTL_LO_BYP_TESTAMP_SHFT                      0x4
#define HWIO_PLL_TEST_CTL_LO_NMOSC_CFG_BMSK                        0xc
#define HWIO_PLL_TEST_CTL_LO_NMOSC_CFG_SHFT                        0x2
#define HWIO_PLL_TEST_CTL_LO_ATEST1_EN_BMSK                        0x2
#define HWIO_PLL_TEST_CTL_LO_ATEST1_EN_SHFT                        0x1
#define HWIO_PLL_TEST_CTL_LO_ATEST0_EN_BMSK                        0x1
#define HWIO_PLL_TEST_CTL_LO_ATEST0_EN_SHFT                        0x0


/*
 * PLL_MODE register definitions.
 */
#define HWIO_MDD_MODE_CAL_DONE_BMSK                         0x80000000
#define HWIO_MDD_MODE_CAL_DONE_SHFT                               0x1f
#define HWIO_MDD_MODE_APC_PDN2_SPARE_BMSK                    0x8000000
#define HWIO_MDD_MODE_APC_PDN2_SPARE_SHFT                         0x1b
#define HWIO_MDD_MODE_APC_PDN1_SPARE_BMSK                    0x4000000
#define HWIO_MDD_MODE_APC_PDN1_SPARE_SHFT                         0x1a
#define HWIO_MDD_MODE_APC_PDN0_SPARE_BMSK                    0x2000000
#define HWIO_MDD_MODE_APC_PDN0_SPARE_SHFT                         0x19
#define HWIO_MDD_MODE_APC_PDN_SPARE_BMSK                     0x1000000
#define HWIO_MDD_MODE_APC_PDN_SPARE_SHFT                          0x18
#define HWIO_MDD_MODE_PLL_DROOP_FORCE_EN_BMSK                 0x400000
#define HWIO_MDD_MODE_PLL_DROOP_FORCE_EN_SHFT                     0x16
#define HWIO_MDD_MODE_AUXCTL_SPARE_BMSK                       0x200000
#define HWIO_MDD_MODE_AUXCTL_SPARE_SHFT                           0x15
#define HWIO_MDD_MODE_CAL_EN_BMSK                             0x100000
#define HWIO_MDD_MODE_CAL_EN_SHFT                                 0x14
#define HWIO_MDD_MODE_TEST_BMSK                                    0x8
#define HWIO_MDD_MODE_TEST_SHFT                                    0x3
#define HWIO_MDD_MODE_RESET_N_BMSK                                 0x4
#define HWIO_MDD_MODE_RESET_N_SHFT                                 0x2
#define HWIO_MDD_MODE_SLEEP_N_BMSK                                 0x2
#define HWIO_MDD_MODE_SLEEP_N_SHFT                                 0x1
#define HWIO_MDD_MODE_OUTCTL_BMSK                                  0x1
#define HWIO_MDD_MODE_OUTCTL_SHFT                                  0x0


/*
 * PWRFSM_CTL register definitions.
 */
#define HWIO_PLL_PWRFSM_CTL_DDEN_BMSK                              0x8
#define HWIO_PLL_PWRFSM_CTL_DDEN_SHFT                              0x3


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
static boolean HAL_clk_HuayraPLLEnable          ( HAL_clk_SourceDescType *pSource, HAL_clk_SourceDisableModeType eMode, void *pData );
static void    HAL_clk_HuayraPLLDisable         ( HAL_clk_SourceDescType *pSource, HAL_clk_SourceDisableModeType eMode, void *pData );
static boolean HAL_clk_HuayraPLLIsEnabled       ( HAL_clk_SourceDescType *pSource );
static void    HAL_clk_HuayraPLLConfig          ( HAL_clk_SourceDescType *pSource, HAL_clk_SourceConfigType eConfig );
static boolean HAL_clk_HuayraPLLConfigPLL       ( HAL_clk_SourceDescType *pSource, const HAL_clk_PLLConfigType *pmConfig, HAL_clk_SourceConfigMode eMode );
static void    HAL_clk_HuayraPLLDetectPLLConfig ( HAL_clk_SourceDescType *pSource, HAL_clk_PLLConfigType *pmConfig );

#endif  /* __HALCLKHUAYRAPLL_H__ */

