#ifndef __CLOCKTURINGHWIO_H__
#define __CLOCKTURINGHWIO_H__
/*
===========================================================================
*/
/**
  @file ClockTURINGHWIO.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    SDM660 (Starlord) [starlord_v1.0.2_p3q3r108_MTO]
 
  This file contains HWIO register definitions for the following modules:
    TURING_TURING_CC_REG
    TURING_QDSP6V60SS_PUB
    SECURITY_CONTROL_CORE


  Generation parameters: 
  { u'filename': u'ClockTURINGHWIO.h',
    u'module-filter-exclude': { },
    u'module-filter-include': { },
    u'modules': [ u'TURING_TURING_CC_REG',
                  u'TURING_QDSP6V60SS_PUB',
                  u'SECURITY_CONTROL_CORE'],
    u'output-offsets': True}
*/
/*
  ===========================================================================

  Copyright (c) 2018 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

  Export of this technology or software is regulated by the U.S. Government.
  Diversion contrary to U.S. law prohibited.

  All ideas, data and information contained in or disclosed by
  this document are confidential and proprietary information of
  Qualcomm Technologies, Inc. and all rights therein are expressly reserved.
  By accepting this material the recipient agrees that this material
  and the information contained therein are held in confidence and in
  trust and will not be used, copied, reproduced in whole or in part,
  nor its contents revealed in any manner to others without the express
  written permission of Qualcomm Technologies, Inc.

  ===========================================================================

  $Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/clock/hw/sdm660/cdsp/inc/ClockTURINGHWIO.h#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $

  ===========================================================================
*/

#include "HALhwio.h"

/*=========================================================================
      Type Definitions
==========================================================================*/

extern  uint32                      Clock_nHWIOBaseTURING;
#define TURING_BASE                 Clock_nHWIOBaseTURING

extern uint32                      HAL_clk_nHWIOBaseSecurityControl;
#define SECURITY_CONTROL_BASE      HAL_clk_nHWIOBaseSecurityControl


/*----------------------------------------------------------------------------
 * MODULE: TURING_TURING_CC_REG
 *--------------------------------------------------------------------------*/

#define TURING_TURING_CC_REG_REG_BASE                                                                                  (TURING_BASE      + 0x00000000)
#define TURING_TURING_CC_REG_REG_BASE_OFFS                                                                             0x00000000

#define HWIO_TURING_TURING_DIG_PLL_L_VAL_ADDR                                                                          (TURING_TURING_CC_REG_REG_BASE      + 0x00001004)
#define HWIO_TURING_TURING_DIG_PLL_L_VAL_OFFS                                                                          (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00001004)
#define HWIO_TURING_TURING_DIG_PLL_L_VAL_RMSK                                                                          0xffffffff
#define HWIO_TURING_TURING_DIG_PLL_L_VAL_IN          \
        in_dword_masked(HWIO_TURING_TURING_DIG_PLL_L_VAL_ADDR, HWIO_TURING_TURING_DIG_PLL_L_VAL_RMSK)
#define HWIO_TURING_TURING_DIG_PLL_L_VAL_INM(m)      \
        in_dword_masked(HWIO_TURING_TURING_DIG_PLL_L_VAL_ADDR, m)
#define HWIO_TURING_TURING_DIG_PLL_L_VAL_OUT(v)      \
        out_dword(HWIO_TURING_TURING_DIG_PLL_L_VAL_ADDR,v)
#define HWIO_TURING_TURING_DIG_PLL_L_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TURING_DIG_PLL_L_VAL_ADDR,m,v,HWIO_TURING_TURING_DIG_PLL_L_VAL_IN)
#define HWIO_TURING_TURING_DIG_PLL_L_VAL_RESERVE_BITS_31_16_BMSK                                                       0xffff0000
#define HWIO_TURING_TURING_DIG_PLL_L_VAL_RESERVE_BITS_31_16_SHFT                                                             0x10
#define HWIO_TURING_TURING_DIG_PLL_L_VAL_PLL_L_BMSK                                                                        0xffff
#define HWIO_TURING_TURING_DIG_PLL_L_VAL_PLL_L_SHFT                                                                           0x0

#define HWIO_TURING_TURING_DIG_PLL_ALPHA_VAL_ADDR                                                                      (TURING_TURING_CC_REG_REG_BASE      + 0x00001008)
#define HWIO_TURING_TURING_DIG_PLL_ALPHA_VAL_OFFS                                                                      (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00001008)
#define HWIO_TURING_TURING_DIG_PLL_ALPHA_VAL_RMSK                                                                      0xffffffff
#define HWIO_TURING_TURING_DIG_PLL_ALPHA_VAL_IN          \
        in_dword_masked(HWIO_TURING_TURING_DIG_PLL_ALPHA_VAL_ADDR, HWIO_TURING_TURING_DIG_PLL_ALPHA_VAL_RMSK)
#define HWIO_TURING_TURING_DIG_PLL_ALPHA_VAL_INM(m)      \
        in_dword_masked(HWIO_TURING_TURING_DIG_PLL_ALPHA_VAL_ADDR, m)
#define HWIO_TURING_TURING_DIG_PLL_ALPHA_VAL_OUT(v)      \
        out_dword(HWIO_TURING_TURING_DIG_PLL_ALPHA_VAL_ADDR,v)
#define HWIO_TURING_TURING_DIG_PLL_ALPHA_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TURING_DIG_PLL_ALPHA_VAL_ADDR,m,v,HWIO_TURING_TURING_DIG_PLL_ALPHA_VAL_IN)
#define HWIO_TURING_TURING_DIG_PLL_ALPHA_VAL_PLL_ALPHA_31_0_BMSK                                                       0xffffffff
#define HWIO_TURING_TURING_DIG_PLL_ALPHA_VAL_PLL_ALPHA_31_0_SHFT                                                              0x0

#define HWIO_TURING_TURING_DIG_PLL_ALPHA_VAL_U_ADDR                                                                    (TURING_TURING_CC_REG_REG_BASE      + 0x0000100c)
#define HWIO_TURING_TURING_DIG_PLL_ALPHA_VAL_U_OFFS                                                                    (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x0000100c)
#define HWIO_TURING_TURING_DIG_PLL_ALPHA_VAL_U_RMSK                                                                    0xffffffff
#define HWIO_TURING_TURING_DIG_PLL_ALPHA_VAL_U_IN          \
        in_dword_masked(HWIO_TURING_TURING_DIG_PLL_ALPHA_VAL_U_ADDR, HWIO_TURING_TURING_DIG_PLL_ALPHA_VAL_U_RMSK)
#define HWIO_TURING_TURING_DIG_PLL_ALPHA_VAL_U_INM(m)      \
        in_dword_masked(HWIO_TURING_TURING_DIG_PLL_ALPHA_VAL_U_ADDR, m)
#define HWIO_TURING_TURING_DIG_PLL_ALPHA_VAL_U_OUT(v)      \
        out_dword(HWIO_TURING_TURING_DIG_PLL_ALPHA_VAL_U_ADDR,v)
#define HWIO_TURING_TURING_DIG_PLL_ALPHA_VAL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TURING_DIG_PLL_ALPHA_VAL_U_ADDR,m,v,HWIO_TURING_TURING_DIG_PLL_ALPHA_VAL_U_IN)
#define HWIO_TURING_TURING_DIG_PLL_ALPHA_VAL_U_RESERVE_BITS_31_8_BMSK                                                  0xffffff00
#define HWIO_TURING_TURING_DIG_PLL_ALPHA_VAL_U_RESERVE_BITS_31_8_SHFT                                                         0x8
#define HWIO_TURING_TURING_DIG_PLL_ALPHA_VAL_U_PLL_ALPHA_39_32_BMSK                                                          0xff
#define HWIO_TURING_TURING_DIG_PLL_ALPHA_VAL_U_PLL_ALPHA_39_32_SHFT                                                           0x0

#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_ADDR                                                                       (TURING_TURING_CC_REG_REG_BASE      + 0x00001010)
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_OFFS                                                                       (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00001010)
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_RMSK                                                                       0xffffffff
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_IN          \
        in_dword_masked(HWIO_TURING_TURING_DIG_PLL_USER_CTL_ADDR, HWIO_TURING_TURING_DIG_PLL_USER_CTL_RMSK)
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_INM(m)      \
        in_dword_masked(HWIO_TURING_TURING_DIG_PLL_USER_CTL_ADDR, m)
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_OUT(v)      \
        out_dword(HWIO_TURING_TURING_DIG_PLL_USER_CTL_ADDR,v)
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TURING_DIG_PLL_USER_CTL_ADDR,m,v,HWIO_TURING_TURING_DIG_PLL_USER_CTL_IN)
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_RESERVE_BITS31_28_BMSK                                                     0xf0000000
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_RESERVE_BITS31_28_SHFT                                                           0x1c
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_SSC_MODE_CONTROL_BMSK                                                       0x8000000
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_SSC_MODE_CONTROL_SHFT                                                            0x1b
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_RESERVE_BITS26_25_BMSK                                                      0x6000000
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_RESERVE_BITS26_25_SHFT                                                           0x19
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_ALPHA_EN_BMSK                                                               0x1000000
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_ALPHA_EN_SHFT                                                                    0x18
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_RESERVE_BITS23_22_BMSK                                                       0xc00000
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_RESERVE_BITS23_22_SHFT                                                           0x16
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_VCO_SEL_BMSK                                                                 0x300000
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_VCO_SEL_SHFT                                                                     0x14
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_RESERVE_BITS19_18_BMSK                                                        0xc0000
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_RESERVE_BITS19_18_SHFT                                                           0x12
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_AUX_POST_DIV_RATIO_BMSK                                                       0x38000
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_AUX_POST_DIV_RATIO_SHFT                                                           0xf
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_PRE_DIV_RATIO_BMSK                                                             0x7000
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_PRE_DIV_RATIO_SHFT                                                                0xc
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_POST_DIV_RATIO_BMSK                                                             0xf00
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_POST_DIV_RATIO_SHFT                                                               0x8
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_OUTPUT_INV_BMSK                                                                  0x80
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_OUTPUT_INV_SHFT                                                                   0x7
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_RESERVE_BITS6_5_BMSK                                                             0x60
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_RESERVE_BITS6_5_SHFT                                                              0x5
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_PLLOUT_LV_TEST_BMSK                                                              0x10
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_PLLOUT_LV_TEST_SHFT                                                               0x4
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_PLLOUT_LV_EARLY_BMSK                                                              0x8
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_PLLOUT_LV_EARLY_SHFT                                                              0x3
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_PLLOUT_LV_AUX2_BMSK                                                               0x4
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_PLLOUT_LV_AUX2_SHFT                                                               0x2
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_PLLOUT_LV_AUX_BMSK                                                                0x2
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_PLLOUT_LV_AUX_SHFT                                                                0x1
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_PLLOUT_LV_MAIN_BMSK                                                               0x1
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_PLLOUT_LV_MAIN_SHFT                                                               0x0

#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_U_ADDR                                                                     (TURING_TURING_CC_REG_REG_BASE      + 0x00001014)
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_U_OFFS                                                                     (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00001014)
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_U_RMSK                                                                     0xffffffff
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_U_IN          \
        in_dword_masked(HWIO_TURING_TURING_DIG_PLL_USER_CTL_U_ADDR, HWIO_TURING_TURING_DIG_PLL_USER_CTL_U_RMSK)
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_U_INM(m)      \
        in_dword_masked(HWIO_TURING_TURING_DIG_PLL_USER_CTL_U_ADDR, m)
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_U_OUT(v)      \
        out_dword(HWIO_TURING_TURING_DIG_PLL_USER_CTL_U_ADDR,v)
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TURING_DIG_PLL_USER_CTL_U_ADDR,m,v,HWIO_TURING_TURING_DIG_PLL_USER_CTL_U_IN)
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_U_CALIBRATION_L_BMSK                                                       0xffff0000
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_U_CALIBRATION_L_SHFT                                                             0x10
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_U_RESERVE_BITS15_12_BMSK                                                       0xf000
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_U_RESERVE_BITS15_12_SHFT                                                          0xc
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_U_LATCH_INTERFACE_BYPASS_BMSK                                                   0x800
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_U_LATCH_INTERFACE_BYPASS_SHFT                                                     0xb
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_U_STATUS_REGISTER_BMSK                                                          0x700
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_U_STATUS_REGISTER_SHFT                                                            0x8
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_U_DSM_BMSK                                                                       0x80
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_U_DSM_SHFT                                                                        0x7
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_U_WRITE_STATE_BMSK                                                               0x40
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_U_WRITE_STATE_SHFT                                                                0x6
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_U_TARGET_CTL_BMSK                                                                0x38
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_U_TARGET_CTL_SHFT                                                                 0x3
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_U_LOCK_DET_BMSK                                                                   0x4
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_U_LOCK_DET_SHFT                                                                   0x2
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_U_FREEZE_PLL_BMSK                                                                 0x2
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_U_FREEZE_PLL_SHFT                                                                 0x1
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_U_TOGGLE_DET_BMSK                                                                 0x1
#define HWIO_TURING_TURING_DIG_PLL_USER_CTL_U_TOGGLE_DET_SHFT                                                                 0x0

#define HWIO_TURING_TURING_DIG_PLL_CONFIG_CTL_ADDR                                                                     (TURING_TURING_CC_REG_REG_BASE      + 0x00001018)
#define HWIO_TURING_TURING_DIG_PLL_CONFIG_CTL_OFFS                                                                     (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00001018)
#define HWIO_TURING_TURING_DIG_PLL_CONFIG_CTL_RMSK                                                                     0xffffffff
#define HWIO_TURING_TURING_DIG_PLL_CONFIG_CTL_IN          \
        in_dword_masked(HWIO_TURING_TURING_DIG_PLL_CONFIG_CTL_ADDR, HWIO_TURING_TURING_DIG_PLL_CONFIG_CTL_RMSK)
#define HWIO_TURING_TURING_DIG_PLL_CONFIG_CTL_INM(m)      \
        in_dword_masked(HWIO_TURING_TURING_DIG_PLL_CONFIG_CTL_ADDR, m)
#define HWIO_TURING_TURING_DIG_PLL_CONFIG_CTL_OUT(v)      \
        out_dword(HWIO_TURING_TURING_DIG_PLL_CONFIG_CTL_ADDR,v)
#define HWIO_TURING_TURING_DIG_PLL_CONFIG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TURING_DIG_PLL_CONFIG_CTL_ADDR,m,v,HWIO_TURING_TURING_DIG_PLL_CONFIG_CTL_IN)
#define HWIO_TURING_TURING_DIG_PLL_CONFIG_CTL_SINGLE_DMET_MODE_ENABLE_BMSK                                             0x80000000
#define HWIO_TURING_TURING_DIG_PLL_CONFIG_CTL_SINGLE_DMET_MODE_ENABLE_SHFT                                                   0x1f
#define HWIO_TURING_TURING_DIG_PLL_CONFIG_CTL_DMET_WINDOW_ENABLE_BMSK                                                  0x40000000
#define HWIO_TURING_TURING_DIG_PLL_CONFIG_CTL_DMET_WINDOW_ENABLE_SHFT                                                        0x1e
#define HWIO_TURING_TURING_DIG_PLL_CONFIG_CTL_TOGGLE_DET_SAMPLE_INTER_BMSK                                             0x3c000000
#define HWIO_TURING_TURING_DIG_PLL_CONFIG_CTL_TOGGLE_DET_SAMPLE_INTER_SHFT                                                   0x1a
#define HWIO_TURING_TURING_DIG_PLL_CONFIG_CTL_TOGGLE_DET_THRESHOLD_BMSK                                                 0x3800000
#define HWIO_TURING_TURING_DIG_PLL_CONFIG_CTL_TOGGLE_DET_THRESHOLD_SHFT                                                      0x17
#define HWIO_TURING_TURING_DIG_PLL_CONFIG_CTL_TOGGLE_DET_SAMPLE_BMSK                                                     0x700000
#define HWIO_TURING_TURING_DIG_PLL_CONFIG_CTL_TOGGLE_DET_SAMPLE_SHFT                                                         0x14
#define HWIO_TURING_TURING_DIG_PLL_CONFIG_CTL_LOCK_DET_THRESHOLD_BMSK                                                     0xff000
#define HWIO_TURING_TURING_DIG_PLL_CONFIG_CTL_LOCK_DET_THRESHOLD_SHFT                                                         0xc
#define HWIO_TURING_TURING_DIG_PLL_CONFIG_CTL_LOCK_DET_SAMPLE_SIZE_BMSK                                                     0xf00
#define HWIO_TURING_TURING_DIG_PLL_CONFIG_CTL_LOCK_DET_SAMPLE_SIZE_SHFT                                                       0x8
#define HWIO_TURING_TURING_DIG_PLL_CONFIG_CTL_MIN_GLITCH_THRESHOLD_BMSK                                                      0xc0
#define HWIO_TURING_TURING_DIG_PLL_CONFIG_CTL_MIN_GLITCH_THRESHOLD_SHFT                                                       0x6
#define HWIO_TURING_TURING_DIG_PLL_CONFIG_CTL_REF_CYCLE_BMSK                                                                 0x30
#define HWIO_TURING_TURING_DIG_PLL_CONFIG_CTL_REF_CYCLE_SHFT                                                                  0x4
#define HWIO_TURING_TURING_DIG_PLL_CONFIG_CTL_KFN_BMSK                                                                        0xf
#define HWIO_TURING_TURING_DIG_PLL_CONFIG_CTL_KFN_SHFT                                                                        0x0

#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_ADDR                                                                       (TURING_TURING_CC_REG_REG_BASE      + 0x0000101c)
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_OFFS                                                                       (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x0000101c)
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_RMSK                                                                       0xffffffff
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_IN          \
        in_dword_masked(HWIO_TURING_TURING_DIG_PLL_TEST_CTL_ADDR, HWIO_TURING_TURING_DIG_PLL_TEST_CTL_RMSK)
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_INM(m)      \
        in_dword_masked(HWIO_TURING_TURING_DIG_PLL_TEST_CTL_ADDR, m)
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_OUT(v)      \
        out_dword(HWIO_TURING_TURING_DIG_PLL_TEST_CTL_ADDR,v)
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TURING_DIG_PLL_TEST_CTL_ADDR,m,v,HWIO_TURING_TURING_DIG_PLL_TEST_CTL_IN)
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_BIAS_GEN_TRIM_BMSK                                                         0xe0000000
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_BIAS_GEN_TRIM_SHFT                                                               0x1d
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_PROCESS_CALB_BMSK                                                          0x1c000000
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_PROCESS_CALB_SHFT                                                                0x1a
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_OVERRIDE_PROCESS_CALB_BMSK                                                  0x2000000
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_OVERRIDE_PROCESS_CALB_SHFT                                                       0x19
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_FINE_FCW_BMSK                                                               0x1f00000
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_FINE_FCW_SHFT                                                                    0x14
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_OVERRIDE_FINE_FCW_BMSK                                                        0x80000
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_OVERRIDE_FINE_FCW_SHFT                                                           0x13
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_COARSE_FCW_BMSK                                                               0x7e000
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_COARSE_FCW_SHFT                                                                   0xd
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_OVERRIDE_COARSE_BMSK                                                           0x1000
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_OVERRIDE_COARSE_SHFT                                                              0xc
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_DISABLE_LFSR_BMSK                                                               0x800
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_DISABLE_LFSR_SHFT                                                                 0xb
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_DTEST_SEL_BMSK                                                                  0x700
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_DTEST_SEL_SHFT                                                                    0x8
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_DTEST_EN_BMSK                                                                    0x80
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_DTEST_EN_SHFT                                                                     0x7
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_BYP_TESTAMP_BMSK                                                                 0x40
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_BYP_TESTAMP_SHFT                                                                  0x6
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_ATEST1_SEL_BMSK                                                                  0x30
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_ATEST1_SEL_SHFT                                                                   0x4
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_ATEST0_SEL_BMSK                                                                   0xc
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_ATEST0_SEL_SHFT                                                                   0x2
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_ATEST1_EN_BMSK                                                                    0x2
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_ATEST1_EN_SHFT                                                                    0x1
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_ATEST0_EN_BMSK                                                                    0x1
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_ATEST0_EN_SHFT                                                                    0x0

#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_ADDR                                                                     (TURING_TURING_CC_REG_REG_BASE      + 0x00001020)
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_OFFS                                                                     (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00001020)
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_RMSK                                                                     0xffffffff
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_IN          \
        in_dword_masked(HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_ADDR, HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_RMSK)
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_INM(m)      \
        in_dword_masked(HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_ADDR, m)
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_OUT(v)      \
        out_dword(HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_ADDR,v)
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_ADDR,m,v,HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_IN)
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_RESERVE_BITS31_22_BMSK                                                   0xffc00000
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_RESERVE_BITS31_22_SHFT                                                         0x16
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_GLITCH_DET_CNT_LIMIT_BMSK                                                  0x300000
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_GLITCH_DET_CNT_LIMIT_SHFT                                                      0x14
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_DIS_GLITCH_PREVENTION_BMSK                                                  0x80000
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_DIS_GLITCH_PREVENTION_SHFT                                                     0x13
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_DTEST_MODE_SEL_U_BMSK                                                       0x60000
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_DTEST_MODE_SEL_U_SHFT                                                          0x11
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_DITHER_SEL_BMSK                                                             0x18000
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_DITHER_SEL_SHFT                                                                 0xf
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_SEL_2B_3B_CAL_BMSK                                                           0x4000
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_SEL_2B_3B_CAL_SHFT                                                              0xe
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_OVERRIDE_FINE_FCW_MSB_BMSK                                                   0x2000
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_OVERRIDE_FINE_FCW_MSB_SHFT                                                      0xd
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_DTEST_MODE_SEL_BMSK                                                          0x1800
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_DTEST_MODE_SEL_SHFT                                                             0xb
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_NMO_OSC_SEL_BMSK                                                              0x600
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_NMO_OSC_SEL_SHFT                                                                0x9
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_RESERVE_BIT8_BMSK                                                             0x100
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_RESERVE_BIT8_SHFT                                                               0x8
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_NOISE_MAG_BMSK                                                                 0xe0
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_NOISE_MAG_SHFT                                                                  0x5
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_NOISE_GEN_BMSK                                                                 0x10
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_NOISE_GEN_SHFT                                                                  0x4
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_OSC_BIAS_GND_BMSK                                                               0x8
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_OSC_BIAS_GND_SHFT                                                               0x3
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_PLL_TEST_OUT_SEL_BMSK                                                           0x6
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_PLL_TEST_OUT_SEL_SHFT                                                           0x1
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_CAL_CODE_UPDATE_BMSK                                                            0x1
#define HWIO_TURING_TURING_DIG_PLL_TEST_CTL_U_CAL_CODE_UPDATE_SHFT                                                            0x0

#define HWIO_TURING_TURING_DIG_PLL_MODE_ADDR                                                                           (TURING_TURING_CC_REG_REG_BASE      + 0x00001000)
#define HWIO_TURING_TURING_DIG_PLL_MODE_OFFS                                                                           (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00001000)
#define HWIO_TURING_TURING_DIG_PLL_MODE_RMSK                                                                           0xffffffff
#define HWIO_TURING_TURING_DIG_PLL_MODE_IN          \
        in_dword_masked(HWIO_TURING_TURING_DIG_PLL_MODE_ADDR, HWIO_TURING_TURING_DIG_PLL_MODE_RMSK)
#define HWIO_TURING_TURING_DIG_PLL_MODE_INM(m)      \
        in_dword_masked(HWIO_TURING_TURING_DIG_PLL_MODE_ADDR, m)
#define HWIO_TURING_TURING_DIG_PLL_MODE_OUT(v)      \
        out_dword(HWIO_TURING_TURING_DIG_PLL_MODE_ADDR,v)
#define HWIO_TURING_TURING_DIG_PLL_MODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TURING_DIG_PLL_MODE_ADDR,m,v,HWIO_TURING_TURING_DIG_PLL_MODE_IN)
#define HWIO_TURING_TURING_DIG_PLL_MODE_PLL_LOCK_DET_BMSK                                                              0x80000000
#define HWIO_TURING_TURING_DIG_PLL_MODE_PLL_LOCK_DET_SHFT                                                                    0x1f
#define HWIO_TURING_TURING_DIG_PLL_MODE_PLL_ACTIVE_FLAG_BMSK                                                           0x40000000
#define HWIO_TURING_TURING_DIG_PLL_MODE_PLL_ACTIVE_FLAG_SHFT                                                                 0x1e
#define HWIO_TURING_TURING_DIG_PLL_MODE_PLL_ACK_LATCH_BMSK                                                             0x20000000
#define HWIO_TURING_TURING_DIG_PLL_MODE_PLL_ACK_LATCH_SHFT                                                                   0x1d
#define HWIO_TURING_TURING_DIG_PLL_MODE_RESERVE_BITS28_24_BMSK                                                         0x1f000000
#define HWIO_TURING_TURING_DIG_PLL_MODE_RESERVE_BITS28_24_SHFT                                                               0x18
#define HWIO_TURING_TURING_DIG_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_BMSK                                                  0x800000
#define HWIO_TURING_TURING_DIG_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_SHFT                                                      0x17
#define HWIO_TURING_TURING_DIG_PLL_MODE_PLL_UPDATE_BMSK                                                                  0x400000
#define HWIO_TURING_TURING_DIG_PLL_MODE_PLL_UPDATE_SHFT                                                                      0x16
#define HWIO_TURING_TURING_DIG_PLL_MODE_PLL_VOTE_FSM_RESET_BMSK                                                          0x200000
#define HWIO_TURING_TURING_DIG_PLL_MODE_PLL_VOTE_FSM_RESET_SHFT                                                              0x15
#define HWIO_TURING_TURING_DIG_PLL_MODE_PLL_VOTE_FSM_ENA_BMSK                                                            0x100000
#define HWIO_TURING_TURING_DIG_PLL_MODE_PLL_VOTE_FSM_ENA_SHFT                                                                0x14
#define HWIO_TURING_TURING_DIG_PLL_MODE_PLL_BIAS_COUNT_BMSK                                                               0xfc000
#define HWIO_TURING_TURING_DIG_PLL_MODE_PLL_BIAS_COUNT_SHFT                                                                   0xe
#define HWIO_TURING_TURING_DIG_PLL_MODE_PLL_LOCK_COUNT_BMSK                                                                0x3f00
#define HWIO_TURING_TURING_DIG_PLL_MODE_PLL_LOCK_COUNT_SHFT                                                                   0x8
#define HWIO_TURING_TURING_DIG_PLL_MODE_RESERVE_BITS7_4_BMSK                                                                 0xf0
#define HWIO_TURING_TURING_DIG_PLL_MODE_RESERVE_BITS7_4_SHFT                                                                  0x4
#define HWIO_TURING_TURING_DIG_PLL_MODE_PLL_PLLTEST_BMSK                                                                      0x8
#define HWIO_TURING_TURING_DIG_PLL_MODE_PLL_PLLTEST_SHFT                                                                      0x3
#define HWIO_TURING_TURING_DIG_PLL_MODE_PLL_RESET_N_BMSK                                                                      0x4
#define HWIO_TURING_TURING_DIG_PLL_MODE_PLL_RESET_N_SHFT                                                                      0x2
#define HWIO_TURING_TURING_DIG_PLL_MODE_PLL_BYPASSNL_BMSK                                                                     0x2
#define HWIO_TURING_TURING_DIG_PLL_MODE_PLL_BYPASSNL_SHFT                                                                     0x1
#define HWIO_TURING_TURING_DIG_PLL_MODE_PLL_OUTCTRL_BMSK                                                                      0x1
#define HWIO_TURING_TURING_DIG_PLL_MODE_PLL_OUTCTRL_SHFT                                                                      0x0

#define HWIO_TURING_TURING_DIG_PLL_STATUS_ADDR                                                                         (TURING_TURING_CC_REG_REG_BASE      + 0x00001024)
#define HWIO_TURING_TURING_DIG_PLL_STATUS_OFFS                                                                         (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00001024)
#define HWIO_TURING_TURING_DIG_PLL_STATUS_RMSK                                                                         0xffffffff
#define HWIO_TURING_TURING_DIG_PLL_STATUS_IN          \
        in_dword_masked(HWIO_TURING_TURING_DIG_PLL_STATUS_ADDR, HWIO_TURING_TURING_DIG_PLL_STATUS_RMSK)
#define HWIO_TURING_TURING_DIG_PLL_STATUS_INM(m)      \
        in_dword_masked(HWIO_TURING_TURING_DIG_PLL_STATUS_ADDR, m)
#define HWIO_TURING_TURING_DIG_PLL_STATUS_STATUS_31_0_BMSK                                                             0xffffffff
#define HWIO_TURING_TURING_DIG_PLL_STATUS_STATUS_31_0_SHFT                                                                    0x0

#define HWIO_TURING_TURING_DIG_PLL_FREQ_CTL_ADDR                                                                       (TURING_TURING_CC_REG_REG_BASE      + 0x00001028)
#define HWIO_TURING_TURING_DIG_PLL_FREQ_CTL_OFFS                                                                       (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00001028)
#define HWIO_TURING_TURING_DIG_PLL_FREQ_CTL_RMSK                                                                       0xffffffff
#define HWIO_TURING_TURING_DIG_PLL_FREQ_CTL_IN          \
        in_dword_masked(HWIO_TURING_TURING_DIG_PLL_FREQ_CTL_ADDR, HWIO_TURING_TURING_DIG_PLL_FREQ_CTL_RMSK)
#define HWIO_TURING_TURING_DIG_PLL_FREQ_CTL_INM(m)      \
        in_dword_masked(HWIO_TURING_TURING_DIG_PLL_FREQ_CTL_ADDR, m)
#define HWIO_TURING_TURING_DIG_PLL_FREQ_CTL_OUT(v)      \
        out_dword(HWIO_TURING_TURING_DIG_PLL_FREQ_CTL_ADDR,v)
#define HWIO_TURING_TURING_DIG_PLL_FREQ_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TURING_DIG_PLL_FREQ_CTL_ADDR,m,v,HWIO_TURING_TURING_DIG_PLL_FREQ_CTL_IN)
#define HWIO_TURING_TURING_DIG_PLL_FREQ_CTL_FREQUENCY_CTL_WORD_BMSK                                                    0xffffffff
#define HWIO_TURING_TURING_DIG_PLL_FREQ_CTL_FREQUENCY_CTL_WORD_SHFT                                                           0x0

#define HWIO_TURING_TURING_DIG_PLL_CLK_CGC_EN_ADDR                                                                     (TURING_TURING_CC_REG_REG_BASE      + 0x0000102c)
#define HWIO_TURING_TURING_DIG_PLL_CLK_CGC_EN_OFFS                                                                     (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x0000102c)
#define HWIO_TURING_TURING_DIG_PLL_CLK_CGC_EN_RMSK                                                                            0xf
#define HWIO_TURING_TURING_DIG_PLL_CLK_CGC_EN_IN          \
        in_dword_masked(HWIO_TURING_TURING_DIG_PLL_CLK_CGC_EN_ADDR, HWIO_TURING_TURING_DIG_PLL_CLK_CGC_EN_RMSK)
#define HWIO_TURING_TURING_DIG_PLL_CLK_CGC_EN_INM(m)      \
        in_dword_masked(HWIO_TURING_TURING_DIG_PLL_CLK_CGC_EN_ADDR, m)
#define HWIO_TURING_TURING_DIG_PLL_CLK_CGC_EN_OUT(v)      \
        out_dword(HWIO_TURING_TURING_DIG_PLL_CLK_CGC_EN_ADDR,v)
#define HWIO_TURING_TURING_DIG_PLL_CLK_CGC_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TURING_DIG_PLL_CLK_CGC_EN_ADDR,m,v,HWIO_TURING_TURING_DIG_PLL_CLK_CGC_EN_IN)
#define HWIO_TURING_TURING_DIG_PLL_CLK_CGC_EN_CLK_AUX_CGC_EN_BMSK                                                             0x8
#define HWIO_TURING_TURING_DIG_PLL_CLK_CGC_EN_CLK_AUX_CGC_EN_SHFT                                                             0x3
#define HWIO_TURING_TURING_DIG_PLL_CLK_CGC_EN_CLK_MAIN_CGC_EN_BMSK                                                            0x4
#define HWIO_TURING_TURING_DIG_PLL_CLK_CGC_EN_CLK_MAIN_CGC_EN_SHFT                                                            0x2
#define HWIO_TURING_TURING_DIG_PLL_CLK_CGC_EN_CLK_EARLY_SVS_CGC_EN_BMSK                                                       0x2
#define HWIO_TURING_TURING_DIG_PLL_CLK_CGC_EN_CLK_EARLY_SVS_CGC_EN_SHFT                                                       0x1
#define HWIO_TURING_TURING_DIG_PLL_CLK_CGC_EN_CLK_EARLY_CGC_EN_BMSK                                                           0x1
#define HWIO_TURING_TURING_DIG_PLL_CLK_CGC_EN_CLK_EARLY_CGC_EN_SHFT                                                           0x0

#define HWIO_TURING_TURING_DIG_PLL_CLK_DIV_ADDR                                                                        (TURING_TURING_CC_REG_REG_BASE      + 0x00001030)
#define HWIO_TURING_TURING_DIG_PLL_CLK_DIV_OFFS                                                                        (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00001030)
#define HWIO_TURING_TURING_DIG_PLL_CLK_DIV_RMSK                                                                           0x38000
#define HWIO_TURING_TURING_DIG_PLL_CLK_DIV_IN          \
        in_dword_masked(HWIO_TURING_TURING_DIG_PLL_CLK_DIV_ADDR, HWIO_TURING_TURING_DIG_PLL_CLK_DIV_RMSK)
#define HWIO_TURING_TURING_DIG_PLL_CLK_DIV_INM(m)      \
        in_dword_masked(HWIO_TURING_TURING_DIG_PLL_CLK_DIV_ADDR, m)
#define HWIO_TURING_TURING_DIG_PLL_CLK_DIV_OUT(v)      \
        out_dword(HWIO_TURING_TURING_DIG_PLL_CLK_DIV_ADDR,v)
#define HWIO_TURING_TURING_DIG_PLL_CLK_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TURING_DIG_PLL_CLK_DIV_ADDR,m,v,HWIO_TURING_TURING_DIG_PLL_CLK_DIV_IN)
#define HWIO_TURING_TURING_DIG_PLL_CLK_DIV_CLK_EARLY_DIV_BMSK                                                             0x38000
#define HWIO_TURING_TURING_DIG_PLL_CLK_DIV_CLK_EARLY_DIV_SHFT                                                                 0xf

#define HWIO_TURING_LPA_PLL_VOTE_APPS_ADDR                                                                             (TURING_TURING_CC_REG_REG_BASE      + 0x00003000)
#define HWIO_TURING_LPA_PLL_VOTE_APPS_OFFS                                                                             (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00003000)
#define HWIO_TURING_LPA_PLL_VOTE_APPS_RMSK                                                                                   0xfe
#define HWIO_TURING_LPA_PLL_VOTE_APPS_IN          \
        in_dword_masked(HWIO_TURING_LPA_PLL_VOTE_APPS_ADDR, HWIO_TURING_LPA_PLL_VOTE_APPS_RMSK)
#define HWIO_TURING_LPA_PLL_VOTE_APPS_INM(m)      \
        in_dword_masked(HWIO_TURING_LPA_PLL_VOTE_APPS_ADDR, m)
#define HWIO_TURING_LPA_PLL_VOTE_APPS_OUT(v)      \
        out_dword(HWIO_TURING_LPA_PLL_VOTE_APPS_ADDR,v)
#define HWIO_TURING_LPA_PLL_VOTE_APPS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_LPA_PLL_VOTE_APPS_ADDR,m,v,HWIO_TURING_LPA_PLL_VOTE_APPS_IN)
#define HWIO_TURING_LPA_PLL_VOTE_APPS_RESERVE_BITS7_3_BMSK                                                                   0xf8
#define HWIO_TURING_LPA_PLL_VOTE_APPS_RESERVE_BITS7_3_SHFT                                                                    0x3
#define HWIO_TURING_LPA_PLL_VOTE_APPS_QDSP6SS_PLL_BMSK                                                                        0x4
#define HWIO_TURING_LPA_PLL_VOTE_APPS_QDSP6SS_PLL_SHFT                                                                        0x2
#define HWIO_TURING_LPA_PLL_VOTE_APPS_TURING_DIG_PLL_BMSK                                                                     0x2
#define HWIO_TURING_LPA_PLL_VOTE_APPS_TURING_DIG_PLL_SHFT                                                                     0x1

#define HWIO_TURING_LPA_PLL_VOTE_TURINGQ6_ADDR                                                                         (TURING_TURING_CC_REG_REG_BASE      + 0x00004000)
#define HWIO_TURING_LPA_PLL_VOTE_TURINGQ6_OFFS                                                                         (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00004000)
#define HWIO_TURING_LPA_PLL_VOTE_TURINGQ6_RMSK                                                                               0xfe
#define HWIO_TURING_LPA_PLL_VOTE_TURINGQ6_IN          \
        in_dword_masked(HWIO_TURING_LPA_PLL_VOTE_TURINGQ6_ADDR, HWIO_TURING_LPA_PLL_VOTE_TURINGQ6_RMSK)
#define HWIO_TURING_LPA_PLL_VOTE_TURINGQ6_INM(m)      \
        in_dword_masked(HWIO_TURING_LPA_PLL_VOTE_TURINGQ6_ADDR, m)
#define HWIO_TURING_LPA_PLL_VOTE_TURINGQ6_OUT(v)      \
        out_dword(HWIO_TURING_LPA_PLL_VOTE_TURINGQ6_ADDR,v)
#define HWIO_TURING_LPA_PLL_VOTE_TURINGQ6_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_LPA_PLL_VOTE_TURINGQ6_ADDR,m,v,HWIO_TURING_LPA_PLL_VOTE_TURINGQ6_IN)
#define HWIO_TURING_LPA_PLL_VOTE_TURINGQ6_RESERVE_BITS7_3_BMSK                                                               0xf8
#define HWIO_TURING_LPA_PLL_VOTE_TURINGQ6_RESERVE_BITS7_3_SHFT                                                                0x3
#define HWIO_TURING_LPA_PLL_VOTE_TURINGQ6_QDSP6SS_PLL_BMSK                                                                    0x4
#define HWIO_TURING_LPA_PLL_VOTE_TURINGQ6_QDSP6SS_PLL_SHFT                                                                    0x2
#define HWIO_TURING_LPA_PLL_VOTE_TURINGQ6_TURING_DIG_PLL_BMSK                                                                 0x2
#define HWIO_TURING_LPA_PLL_VOTE_TURINGQ6_TURING_DIG_PLL_SHFT                                                                 0x1

#define HWIO_TURING_LPA_PLL_VOTE_TURING_HW_ADDR                                                                        (TURING_TURING_CC_REG_REG_BASE      + 0x00005000)
#define HWIO_TURING_LPA_PLL_VOTE_TURING_HW_OFFS                                                                        (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00005000)
#define HWIO_TURING_LPA_PLL_VOTE_TURING_HW_RMSK                                                                              0xfe
#define HWIO_TURING_LPA_PLL_VOTE_TURING_HW_IN          \
        in_dword_masked(HWIO_TURING_LPA_PLL_VOTE_TURING_HW_ADDR, HWIO_TURING_LPA_PLL_VOTE_TURING_HW_RMSK)
#define HWIO_TURING_LPA_PLL_VOTE_TURING_HW_INM(m)      \
        in_dword_masked(HWIO_TURING_LPA_PLL_VOTE_TURING_HW_ADDR, m)
#define HWIO_TURING_LPA_PLL_VOTE_TURING_HW_OUT(v)      \
        out_dword(HWIO_TURING_LPA_PLL_VOTE_TURING_HW_ADDR,v)
#define HWIO_TURING_LPA_PLL_VOTE_TURING_HW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_LPA_PLL_VOTE_TURING_HW_ADDR,m,v,HWIO_TURING_LPA_PLL_VOTE_TURING_HW_IN)
#define HWIO_TURING_LPA_PLL_VOTE_TURING_HW_RESERVE_BITS7_3_BMSK                                                              0xf8
#define HWIO_TURING_LPA_PLL_VOTE_TURING_HW_RESERVE_BITS7_3_SHFT                                                               0x3
#define HWIO_TURING_LPA_PLL_VOTE_TURING_HW_QDSP6SS_PLL_BMSK                                                                   0x4
#define HWIO_TURING_LPA_PLL_VOTE_TURING_HW_QDSP6SS_PLL_SHFT                                                                   0x2
#define HWIO_TURING_LPA_PLL_VOTE_TURING_HW_TURING_DIG_PLL_BMSK                                                                0x2
#define HWIO_TURING_LPA_PLL_VOTE_TURING_HW_TURING_DIG_PLL_SHFT                                                                0x1

#define HWIO_TURING_TURING_WRAPPER_BCR_ADDR                                                                            (TURING_TURING_CC_REG_REG_BASE      + 0x00007000)
#define HWIO_TURING_TURING_WRAPPER_BCR_OFFS                                                                            (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00007000)
#define HWIO_TURING_TURING_WRAPPER_BCR_RMSK                                                                            0x80000003
#define HWIO_TURING_TURING_WRAPPER_BCR_IN          \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_BCR_ADDR, HWIO_TURING_TURING_WRAPPER_BCR_RMSK)
#define HWIO_TURING_TURING_WRAPPER_BCR_INM(m)      \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_BCR_ADDR, m)
#define HWIO_TURING_TURING_WRAPPER_BCR_OUT(v)      \
        out_dword(HWIO_TURING_TURING_WRAPPER_BCR_ADDR,v)
#define HWIO_TURING_TURING_WRAPPER_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TURING_WRAPPER_BCR_ADDR,m,v,HWIO_TURING_TURING_WRAPPER_BCR_IN)
#define HWIO_TURING_TURING_WRAPPER_BCR_DFD_STATUS_BMSK                                                                 0x80000000
#define HWIO_TURING_TURING_WRAPPER_BCR_DFD_STATUS_SHFT                                                                       0x1f
#define HWIO_TURING_TURING_WRAPPER_BCR_DFD_EN_BMSK                                                                            0x2
#define HWIO_TURING_TURING_WRAPPER_BCR_DFD_EN_SHFT                                                                            0x1
#define HWIO_TURING_TURING_WRAPPER_BCR_BLK_ARES_BMSK                                                                          0x1
#define HWIO_TURING_TURING_WRAPPER_BCR_BLK_ARES_SHFT                                                                          0x0

#define HWIO_TURING_Q6SS_BCR_ADDR                                                                                      (TURING_TURING_CC_REG_REG_BASE      + 0x00008000)
#define HWIO_TURING_Q6SS_BCR_OFFS                                                                                      (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00008000)
#define HWIO_TURING_Q6SS_BCR_RMSK                                                                                      0x80000003
#define HWIO_TURING_Q6SS_BCR_IN          \
        in_dword_masked(HWIO_TURING_Q6SS_BCR_ADDR, HWIO_TURING_Q6SS_BCR_RMSK)
#define HWIO_TURING_Q6SS_BCR_INM(m)      \
        in_dword_masked(HWIO_TURING_Q6SS_BCR_ADDR, m)
#define HWIO_TURING_Q6SS_BCR_OUT(v)      \
        out_dword(HWIO_TURING_Q6SS_BCR_ADDR,v)
#define HWIO_TURING_Q6SS_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_Q6SS_BCR_ADDR,m,v,HWIO_TURING_Q6SS_BCR_IN)
#define HWIO_TURING_Q6SS_BCR_DFD_STATUS_BMSK                                                                           0x80000000
#define HWIO_TURING_Q6SS_BCR_DFD_STATUS_SHFT                                                                                 0x1f
#define HWIO_TURING_Q6SS_BCR_DFD_EN_BMSK                                                                                      0x2
#define HWIO_TURING_Q6SS_BCR_DFD_EN_SHFT                                                                                      0x1
#define HWIO_TURING_Q6SS_BCR_BLK_ARES_BMSK                                                                                    0x1
#define HWIO_TURING_Q6SS_BCR_BLK_ARES_SHFT                                                                                    0x0

#define HWIO_TURING_Q6SS_BCR_SLP_CBCR_ADDR                                                                             (TURING_TURING_CC_REG_REG_BASE      + 0x00008004)
#define HWIO_TURING_Q6SS_BCR_SLP_CBCR_OFFS                                                                             (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00008004)
#define HWIO_TURING_Q6SS_BCR_SLP_CBCR_RMSK                                                                             0x80000003
#define HWIO_TURING_Q6SS_BCR_SLP_CBCR_IN          \
        in_dword_masked(HWIO_TURING_Q6SS_BCR_SLP_CBCR_ADDR, HWIO_TURING_Q6SS_BCR_SLP_CBCR_RMSK)
#define HWIO_TURING_Q6SS_BCR_SLP_CBCR_INM(m)      \
        in_dword_masked(HWIO_TURING_Q6SS_BCR_SLP_CBCR_ADDR, m)
#define HWIO_TURING_Q6SS_BCR_SLP_CBCR_OUT(v)      \
        out_dword(HWIO_TURING_Q6SS_BCR_SLP_CBCR_ADDR,v)
#define HWIO_TURING_Q6SS_BCR_SLP_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_Q6SS_BCR_SLP_CBCR_ADDR,m,v,HWIO_TURING_Q6SS_BCR_SLP_CBCR_IN)
#define HWIO_TURING_Q6SS_BCR_SLP_CBCR_CLK_OFF_BMSK                                                                     0x80000000
#define HWIO_TURING_Q6SS_BCR_SLP_CBCR_CLK_OFF_SHFT                                                                           0x1f
#define HWIO_TURING_Q6SS_BCR_SLP_CBCR_HW_CTL_BMSK                                                                             0x2
#define HWIO_TURING_Q6SS_BCR_SLP_CBCR_HW_CTL_SHFT                                                                             0x1
#define HWIO_TURING_Q6SS_BCR_SLP_CBCR_CLK_ENABLE_BMSK                                                                         0x1
#define HWIO_TURING_Q6SS_BCR_SLP_CBCR_CLK_ENABLE_SHFT                                                                         0x0

#define HWIO_TURING_Q6_SMMU_GDSCR_ADDR                                                                                 (TURING_TURING_CC_REG_REG_BASE      + 0x0000b000)
#define HWIO_TURING_Q6_SMMU_GDSCR_OFFS                                                                                 (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x0000b000)
#define HWIO_TURING_Q6_SMMU_GDSCR_RMSK                                                                                 0xf8ffffff
#define HWIO_TURING_Q6_SMMU_GDSCR_IN          \
        in_dword_masked(HWIO_TURING_Q6_SMMU_GDSCR_ADDR, HWIO_TURING_Q6_SMMU_GDSCR_RMSK)
#define HWIO_TURING_Q6_SMMU_GDSCR_INM(m)      \
        in_dword_masked(HWIO_TURING_Q6_SMMU_GDSCR_ADDR, m)
#define HWIO_TURING_Q6_SMMU_GDSCR_OUT(v)      \
        out_dword(HWIO_TURING_Q6_SMMU_GDSCR_ADDR,v)
#define HWIO_TURING_Q6_SMMU_GDSCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_Q6_SMMU_GDSCR_ADDR,m,v,HWIO_TURING_Q6_SMMU_GDSCR_IN)
#define HWIO_TURING_Q6_SMMU_GDSCR_PWR_ON_BMSK                                                                          0x80000000
#define HWIO_TURING_Q6_SMMU_GDSCR_PWR_ON_SHFT                                                                                0x1f
#define HWIO_TURING_Q6_SMMU_GDSCR_GDSC_STATE_BMSK                                                                      0x78000000
#define HWIO_TURING_Q6_SMMU_GDSCR_GDSC_STATE_SHFT                                                                            0x1b
#define HWIO_TURING_Q6_SMMU_GDSCR_EN_REST_WAIT_BMSK                                                                      0xf00000
#define HWIO_TURING_Q6_SMMU_GDSCR_EN_REST_WAIT_SHFT                                                                          0x14
#define HWIO_TURING_Q6_SMMU_GDSCR_EN_FEW_WAIT_BMSK                                                                        0xf0000
#define HWIO_TURING_Q6_SMMU_GDSCR_EN_FEW_WAIT_SHFT                                                                           0x10
#define HWIO_TURING_Q6_SMMU_GDSCR_CLK_DIS_WAIT_BMSK                                                                        0xf000
#define HWIO_TURING_Q6_SMMU_GDSCR_CLK_DIS_WAIT_SHFT                                                                           0xc
#define HWIO_TURING_Q6_SMMU_GDSCR_RETAIN_FF_ENABLE_BMSK                                                                     0x800
#define HWIO_TURING_Q6_SMMU_GDSCR_RETAIN_FF_ENABLE_SHFT                                                                       0xb
#define HWIO_TURING_Q6_SMMU_GDSCR_RESTORE_BMSK                                                                              0x400
#define HWIO_TURING_Q6_SMMU_GDSCR_RESTORE_SHFT                                                                                0xa
#define HWIO_TURING_Q6_SMMU_GDSCR_SAVE_BMSK                                                                                 0x200
#define HWIO_TURING_Q6_SMMU_GDSCR_SAVE_SHFT                                                                                   0x9
#define HWIO_TURING_Q6_SMMU_GDSCR_RETAIN_BMSK                                                                               0x100
#define HWIO_TURING_Q6_SMMU_GDSCR_RETAIN_SHFT                                                                                 0x8
#define HWIO_TURING_Q6_SMMU_GDSCR_EN_REST_BMSK                                                                               0x80
#define HWIO_TURING_Q6_SMMU_GDSCR_EN_REST_SHFT                                                                                0x7
#define HWIO_TURING_Q6_SMMU_GDSCR_EN_FEW_BMSK                                                                                0x40
#define HWIO_TURING_Q6_SMMU_GDSCR_EN_FEW_SHFT                                                                                 0x6
#define HWIO_TURING_Q6_SMMU_GDSCR_CLAMP_IO_BMSK                                                                              0x20
#define HWIO_TURING_Q6_SMMU_GDSCR_CLAMP_IO_SHFT                                                                               0x5
#define HWIO_TURING_Q6_SMMU_GDSCR_CLK_DISABLE_BMSK                                                                           0x10
#define HWIO_TURING_Q6_SMMU_GDSCR_CLK_DISABLE_SHFT                                                                            0x4
#define HWIO_TURING_Q6_SMMU_GDSCR_PD_ARES_BMSK                                                                                0x8
#define HWIO_TURING_Q6_SMMU_GDSCR_PD_ARES_SHFT                                                                                0x3
#define HWIO_TURING_Q6_SMMU_GDSCR_SW_OVERRIDE_BMSK                                                                            0x4
#define HWIO_TURING_Q6_SMMU_GDSCR_SW_OVERRIDE_SHFT                                                                            0x2
#define HWIO_TURING_Q6_SMMU_GDSCR_HW_CONTROL_BMSK                                                                             0x2
#define HWIO_TURING_Q6_SMMU_GDSCR_HW_CONTROL_SHFT                                                                             0x1
#define HWIO_TURING_Q6_SMMU_GDSCR_SW_COLLAPSE_BMSK                                                                            0x1
#define HWIO_TURING_Q6_SMMU_GDSCR_SW_COLLAPSE_SHFT                                                                            0x0

#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_ADDR                                                           (TURING_TURING_CC_REG_REG_BASE      + 0x0000b004)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_OFFS                                                           (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x0000b004)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_RMSK                                                           0x80000003
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_IN          \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_ADDR, HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_RMSK)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_INM(m)      \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_ADDR, m)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_OUT(v)      \
        out_dword(HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_ADDR,v)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_ADDR,m,v,HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_IN)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_CLK_OFF_BMSK                                                   0x80000000
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_CLK_OFF_SHFT                                                         0x1f
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_HW_CTL_BMSK                                                           0x2
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_HW_CTL_SHFT                                                           0x1
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_CLK_ENABLE_BMSK                                                       0x1
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_CLK_ENABLE_SHFT                                                       0x0

#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_ADDR                                                            (TURING_TURING_CC_REG_REG_BASE      + 0x0000b008)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_OFFS                                                            (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x0000b008)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_RMSK                                                            0xffffffff
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_IN          \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_ADDR, HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_RMSK)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_INM(m)      \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_ADDR, m)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_OUT(v)      \
        out_dword(HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_ADDR,v)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_ADDR,m,v,HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_IN)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_POWER_ON_STATUS_BMSK                                            0x80000000
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_POWER_ON_STATUS_SHFT                                                  0x1f
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_HALT1_PWR_DOWN_ACK_STATUS_BMSK                                  0x78000000
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_HALT1_PWR_DOWN_ACK_STATUS_SHFT                                        0x1b
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_HALT1_PWR_UP_ACK_STATUS_BMSK                                     0x7800000
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_HALT1_PWR_UP_ACK_STATUS_SHFT                                          0x17
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_HALT2_PWR_DOWN_ACK_STATUS_BMSK                                    0x780000
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_HALT2_PWR_DOWN_ACK_STATUS_SHFT                                        0x13
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_HALT2_PWR_UP_ACK_STATUS_BMSK                                       0x78000
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_HALT2_PWR_UP_ACK_STATUS_SHFT                                           0xf
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_COLLAPSE_OUT_BMSK                                                   0x4000
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_COLLAPSE_OUT_SHFT                                                      0xe
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_RESERVE_BITS13_BMSK                                                 0x2000
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_RESERVE_BITS13_SHFT                                                    0xd
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_HALT_ACK_TIME_OUT_BMSK                                              0x1fe0
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_HALT_ACK_TIME_OUT_SHFT                                                 0x5
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_GDS_HW_STATE_BMSK                                                     0x1e
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_GDS_HW_STATE_SHFT                                                      0x1
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SW_OVERRIDE_BMSK                                                       0x1
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SW_OVERRIDE_SHFT                                                       0x0

#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_ADDR                                                        (TURING_TURING_CC_REG_REG_BASE      + 0x0000b00c)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_OFFS                                                        (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x0000b00c)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_RMSK                                                        0xc0000001
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_IN          \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_ADDR, HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_RMSK)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_INM(m)      \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_ADDR, m)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_OUT(v)      \
        out_dword(HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_ADDR,v)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_ADDR,m,v,HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_IN)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_DVM_HALT1_PWR_DOWN_ACK_STATUS_BMSK                          0x80000000
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_DVM_HALT1_PWR_DOWN_ACK_STATUS_SHFT                                0x1f
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_DVM_HALT1_PWR_UP_ACK_STATUS_BMSK                            0x40000000
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_DVM_HALT1_PWR_UP_ACK_STATUS_SHFT                                  0x1e
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_DVM_HALT1_REQ_SW_BMSK                                              0x1
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_DVM_HALT1_REQ_SW_SHFT                                              0x0

#define HWIO_TURING_Q6_SMMU_GDSCR_VOTE_ADDR                                                                            (TURING_TURING_CC_REG_REG_BASE      + 0x0000c000)
#define HWIO_TURING_Q6_SMMU_GDSCR_VOTE_OFFS                                                                            (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x0000c000)
#define HWIO_TURING_Q6_SMMU_GDSCR_VOTE_RMSK                                                                                   0x3
#define HWIO_TURING_Q6_SMMU_GDSCR_VOTE_IN          \
        in_dword_masked(HWIO_TURING_Q6_SMMU_GDSCR_VOTE_ADDR, HWIO_TURING_Q6_SMMU_GDSCR_VOTE_RMSK)
#define HWIO_TURING_Q6_SMMU_GDSCR_VOTE_INM(m)      \
        in_dword_masked(HWIO_TURING_Q6_SMMU_GDSCR_VOTE_ADDR, m)
#define HWIO_TURING_Q6_SMMU_GDSCR_VOTE_OUT(v)      \
        out_dword(HWIO_TURING_Q6_SMMU_GDSCR_VOTE_ADDR,v)
#define HWIO_TURING_Q6_SMMU_GDSCR_VOTE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_Q6_SMMU_GDSCR_VOTE_ADDR,m,v,HWIO_TURING_Q6_SMMU_GDSCR_VOTE_IN)
#define HWIO_TURING_Q6_SMMU_GDSCR_VOTE_RETENTION_ENABLE_VOTE_BMSK                                                             0x2
#define HWIO_TURING_Q6_SMMU_GDSCR_VOTE_RETENTION_ENABLE_VOTE_SHFT                                                             0x1
#define HWIO_TURING_Q6_SMMU_GDSCR_VOTE_SW_OVERRIDE_VOTE_BMSK                                                                  0x1
#define HWIO_TURING_Q6_SMMU_GDSCR_VOTE_SW_OVERRIDE_VOTE_SHFT                                                                  0x0

#define HWIO_TURING_Q6_SMMU_SPM_CLK_CTL_ADDR                                                                           (TURING_TURING_CC_REG_REG_BASE      + 0x0000d000)
#define HWIO_TURING_Q6_SMMU_SPM_CLK_CTL_OFFS                                                                           (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x0000d000)
#define HWIO_TURING_Q6_SMMU_SPM_CLK_CTL_RMSK                                                                                  0x1
#define HWIO_TURING_Q6_SMMU_SPM_CLK_CTL_IN          \
        in_dword_masked(HWIO_TURING_Q6_SMMU_SPM_CLK_CTL_ADDR, HWIO_TURING_Q6_SMMU_SPM_CLK_CTL_RMSK)
#define HWIO_TURING_Q6_SMMU_SPM_CLK_CTL_INM(m)      \
        in_dword_masked(HWIO_TURING_Q6_SMMU_SPM_CLK_CTL_ADDR, m)
#define HWIO_TURING_Q6_SMMU_SPM_CLK_CTL_OUT(v)      \
        out_dword(HWIO_TURING_Q6_SMMU_SPM_CLK_CTL_ADDR,v)
#define HWIO_TURING_Q6_SMMU_SPM_CLK_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_Q6_SMMU_SPM_CLK_CTL_ADDR,m,v,HWIO_TURING_Q6_SMMU_SPM_CLK_CTL_IN)
#define HWIO_TURING_Q6_SMMU_SPM_CLK_CTL_Q6_SMMU_SPM_COLLAPSE_OR_CLK_GATE_SEL_BMSK                                             0x1
#define HWIO_TURING_Q6_SMMU_SPM_CLK_CTL_Q6_SMMU_SPM_COLLAPSE_OR_CLK_GATE_SEL_SHFT                                             0x0

#define HWIO_TURING_AON_CMD_RCGR_ADDR                                                                                  (TURING_TURING_CC_REG_REG_BASE      + 0x00012000)
#define HWIO_TURING_AON_CMD_RCGR_OFFS                                                                                  (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00012000)
#define HWIO_TURING_AON_CMD_RCGR_RMSK                                                                                  0x800000f3
#define HWIO_TURING_AON_CMD_RCGR_IN          \
        in_dword_masked(HWIO_TURING_AON_CMD_RCGR_ADDR, HWIO_TURING_AON_CMD_RCGR_RMSK)
#define HWIO_TURING_AON_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_TURING_AON_CMD_RCGR_ADDR, m)
#define HWIO_TURING_AON_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_TURING_AON_CMD_RCGR_ADDR,v)
#define HWIO_TURING_AON_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_AON_CMD_RCGR_ADDR,m,v,HWIO_TURING_AON_CMD_RCGR_IN)
#define HWIO_TURING_AON_CMD_RCGR_ROOT_OFF_BMSK                                                                         0x80000000
#define HWIO_TURING_AON_CMD_RCGR_ROOT_OFF_SHFT                                                                               0x1f
#define HWIO_TURING_AON_CMD_RCGR_DIRTY_D_BMSK                                                                                0x80
#define HWIO_TURING_AON_CMD_RCGR_DIRTY_D_SHFT                                                                                 0x7
#define HWIO_TURING_AON_CMD_RCGR_DIRTY_N_BMSK                                                                                0x40
#define HWIO_TURING_AON_CMD_RCGR_DIRTY_N_SHFT                                                                                 0x6
#define HWIO_TURING_AON_CMD_RCGR_DIRTY_M_BMSK                                                                                0x20
#define HWIO_TURING_AON_CMD_RCGR_DIRTY_M_SHFT                                                                                 0x5
#define HWIO_TURING_AON_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                         0x10
#define HWIO_TURING_AON_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                          0x4
#define HWIO_TURING_AON_CMD_RCGR_ROOT_EN_BMSK                                                                                 0x2
#define HWIO_TURING_AON_CMD_RCGR_ROOT_EN_SHFT                                                                                 0x1
#define HWIO_TURING_AON_CMD_RCGR_UPDATE_BMSK                                                                                  0x1
#define HWIO_TURING_AON_CMD_RCGR_UPDATE_SHFT                                                                                  0x0

#define HWIO_TURING_AON_CFG_RCGR_ADDR                                                                                  (TURING_TURING_CC_REG_REG_BASE      + 0x00012004)
#define HWIO_TURING_AON_CFG_RCGR_OFFS                                                                                  (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00012004)
#define HWIO_TURING_AON_CFG_RCGR_RMSK                                                                                      0x771f
#define HWIO_TURING_AON_CFG_RCGR_IN          \
        in_dword_masked(HWIO_TURING_AON_CFG_RCGR_ADDR, HWIO_TURING_AON_CFG_RCGR_RMSK)
#define HWIO_TURING_AON_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_TURING_AON_CFG_RCGR_ADDR, m)
#define HWIO_TURING_AON_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_TURING_AON_CFG_RCGR_ADDR,v)
#define HWIO_TURING_AON_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_AON_CFG_RCGR_ADDR,m,v,HWIO_TURING_AON_CFG_RCGR_IN)
#define HWIO_TURING_AON_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                          0x4000
#define HWIO_TURING_AON_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                             0xe
#define HWIO_TURING_AON_CFG_RCGR_MODE_BMSK                                                                                 0x3000
#define HWIO_TURING_AON_CFG_RCGR_MODE_SHFT                                                                                    0xc
#define HWIO_TURING_AON_CFG_RCGR_SRC_SEL_BMSK                                                                               0x700
#define HWIO_TURING_AON_CFG_RCGR_SRC_SEL_SHFT                                                                                 0x8
#define HWIO_TURING_AON_CFG_RCGR_SRC_DIV_BMSK                                                                                0x1f
#define HWIO_TURING_AON_CFG_RCGR_SRC_DIV_SHFT                                                                                 0x0

#define HWIO_TURING_AON_M_ADDR                                                                                         (TURING_TURING_CC_REG_REG_BASE      + 0x00012008)
#define HWIO_TURING_AON_M_OFFS                                                                                         (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00012008)
#define HWIO_TURING_AON_M_RMSK                                                                                               0xff
#define HWIO_TURING_AON_M_IN          \
        in_dword_masked(HWIO_TURING_AON_M_ADDR, HWIO_TURING_AON_M_RMSK)
#define HWIO_TURING_AON_M_INM(m)      \
        in_dword_masked(HWIO_TURING_AON_M_ADDR, m)
#define HWIO_TURING_AON_M_OUT(v)      \
        out_dword(HWIO_TURING_AON_M_ADDR,v)
#define HWIO_TURING_AON_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_AON_M_ADDR,m,v,HWIO_TURING_AON_M_IN)
#define HWIO_TURING_AON_M_M_BMSK                                                                                             0xff
#define HWIO_TURING_AON_M_M_SHFT                                                                                              0x0

#define HWIO_TURING_AON_N_ADDR                                                                                         (TURING_TURING_CC_REG_REG_BASE      + 0x0001200c)
#define HWIO_TURING_AON_N_OFFS                                                                                         (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x0001200c)
#define HWIO_TURING_AON_N_RMSK                                                                                               0xff
#define HWIO_TURING_AON_N_IN          \
        in_dword_masked(HWIO_TURING_AON_N_ADDR, HWIO_TURING_AON_N_RMSK)
#define HWIO_TURING_AON_N_INM(m)      \
        in_dword_masked(HWIO_TURING_AON_N_ADDR, m)
#define HWIO_TURING_AON_N_OUT(v)      \
        out_dword(HWIO_TURING_AON_N_ADDR,v)
#define HWIO_TURING_AON_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_AON_N_ADDR,m,v,HWIO_TURING_AON_N_IN)
#define HWIO_TURING_AON_N_NOT_N_MINUS_M_BMSK                                                                                 0xff
#define HWIO_TURING_AON_N_NOT_N_MINUS_M_SHFT                                                                                  0x0

#define HWIO_TURING_AON_D_ADDR                                                                                         (TURING_TURING_CC_REG_REG_BASE      + 0x00012010)
#define HWIO_TURING_AON_D_OFFS                                                                                         (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00012010)
#define HWIO_TURING_AON_D_RMSK                                                                                               0xff
#define HWIO_TURING_AON_D_IN          \
        in_dword_masked(HWIO_TURING_AON_D_ADDR, HWIO_TURING_AON_D_RMSK)
#define HWIO_TURING_AON_D_INM(m)      \
        in_dword_masked(HWIO_TURING_AON_D_ADDR, m)
#define HWIO_TURING_AON_D_OUT(v)      \
        out_dword(HWIO_TURING_AON_D_ADDR,v)
#define HWIO_TURING_AON_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_AON_D_ADDR,m,v,HWIO_TURING_AON_D_IN)
#define HWIO_TURING_AON_D_NOT_2D_BMSK                                                                                        0xff
#define HWIO_TURING_AON_D_NOT_2D_SHFT                                                                                         0x0

#define HWIO_TURING_TURING_WRAPPER_AON_CBCR_ADDR                                                                       (TURING_TURING_CC_REG_REG_BASE      + 0x00012014)
#define HWIO_TURING_TURING_WRAPPER_AON_CBCR_OFFS                                                                       (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00012014)
#define HWIO_TURING_TURING_WRAPPER_AON_CBCR_RMSK                                                                       0x80000003
#define HWIO_TURING_TURING_WRAPPER_AON_CBCR_IN          \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_AON_CBCR_ADDR, HWIO_TURING_TURING_WRAPPER_AON_CBCR_RMSK)
#define HWIO_TURING_TURING_WRAPPER_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_AON_CBCR_ADDR, m)
#define HWIO_TURING_TURING_WRAPPER_AON_CBCR_OUT(v)      \
        out_dword(HWIO_TURING_TURING_WRAPPER_AON_CBCR_ADDR,v)
#define HWIO_TURING_TURING_WRAPPER_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TURING_WRAPPER_AON_CBCR_ADDR,m,v,HWIO_TURING_TURING_WRAPPER_AON_CBCR_IN)
#define HWIO_TURING_TURING_WRAPPER_AON_CBCR_CLK_OFF_BMSK                                                               0x80000000
#define HWIO_TURING_TURING_WRAPPER_AON_CBCR_CLK_OFF_SHFT                                                                     0x1f
#define HWIO_TURING_TURING_WRAPPER_AON_CBCR_HW_CTL_BMSK                                                                       0x2
#define HWIO_TURING_TURING_WRAPPER_AON_CBCR_HW_CTL_SHFT                                                                       0x1
#define HWIO_TURING_TURING_WRAPPER_AON_CBCR_CLK_ENABLE_BMSK                                                                   0x1
#define HWIO_TURING_TURING_WRAPPER_AON_CBCR_CLK_ENABLE_SHFT                                                                   0x0

#define HWIO_TURING_SLEEP_CMD_RCGR_ADDR                                                                                (TURING_TURING_CC_REG_REG_BASE      + 0x00018000)
#define HWIO_TURING_SLEEP_CMD_RCGR_OFFS                                                                                (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00018000)
#define HWIO_TURING_SLEEP_CMD_RCGR_RMSK                                                                                0x800000f3
#define HWIO_TURING_SLEEP_CMD_RCGR_IN          \
        in_dword_masked(HWIO_TURING_SLEEP_CMD_RCGR_ADDR, HWIO_TURING_SLEEP_CMD_RCGR_RMSK)
#define HWIO_TURING_SLEEP_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_TURING_SLEEP_CMD_RCGR_ADDR, m)
#define HWIO_TURING_SLEEP_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_TURING_SLEEP_CMD_RCGR_ADDR,v)
#define HWIO_TURING_SLEEP_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_SLEEP_CMD_RCGR_ADDR,m,v,HWIO_TURING_SLEEP_CMD_RCGR_IN)
#define HWIO_TURING_SLEEP_CMD_RCGR_ROOT_OFF_BMSK                                                                       0x80000000
#define HWIO_TURING_SLEEP_CMD_RCGR_ROOT_OFF_SHFT                                                                             0x1f
#define HWIO_TURING_SLEEP_CMD_RCGR_DIRTY_D_BMSK                                                                              0x80
#define HWIO_TURING_SLEEP_CMD_RCGR_DIRTY_D_SHFT                                                                               0x7
#define HWIO_TURING_SLEEP_CMD_RCGR_DIRTY_N_BMSK                                                                              0x40
#define HWIO_TURING_SLEEP_CMD_RCGR_DIRTY_N_SHFT                                                                               0x6
#define HWIO_TURING_SLEEP_CMD_RCGR_DIRTY_M_BMSK                                                                              0x20
#define HWIO_TURING_SLEEP_CMD_RCGR_DIRTY_M_SHFT                                                                               0x5
#define HWIO_TURING_SLEEP_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                       0x10
#define HWIO_TURING_SLEEP_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                        0x4
#define HWIO_TURING_SLEEP_CMD_RCGR_ROOT_EN_BMSK                                                                               0x2
#define HWIO_TURING_SLEEP_CMD_RCGR_ROOT_EN_SHFT                                                                               0x1
#define HWIO_TURING_SLEEP_CMD_RCGR_UPDATE_BMSK                                                                                0x1
#define HWIO_TURING_SLEEP_CMD_RCGR_UPDATE_SHFT                                                                                0x0

#define HWIO_TURING_SLEEP_CFG_RCGR_ADDR                                                                                (TURING_TURING_CC_REG_REG_BASE      + 0x00018004)
#define HWIO_TURING_SLEEP_CFG_RCGR_OFFS                                                                                (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00018004)
#define HWIO_TURING_SLEEP_CFG_RCGR_RMSK                                                                                    0x371f
#define HWIO_TURING_SLEEP_CFG_RCGR_IN          \
        in_dword_masked(HWIO_TURING_SLEEP_CFG_RCGR_ADDR, HWIO_TURING_SLEEP_CFG_RCGR_RMSK)
#define HWIO_TURING_SLEEP_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_TURING_SLEEP_CFG_RCGR_ADDR, m)
#define HWIO_TURING_SLEEP_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_TURING_SLEEP_CFG_RCGR_ADDR,v)
#define HWIO_TURING_SLEEP_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_SLEEP_CFG_RCGR_ADDR,m,v,HWIO_TURING_SLEEP_CFG_RCGR_IN)
#define HWIO_TURING_SLEEP_CFG_RCGR_MODE_BMSK                                                                               0x3000
#define HWIO_TURING_SLEEP_CFG_RCGR_MODE_SHFT                                                                                  0xc
#define HWIO_TURING_SLEEP_CFG_RCGR_SRC_SEL_BMSK                                                                             0x700
#define HWIO_TURING_SLEEP_CFG_RCGR_SRC_SEL_SHFT                                                                               0x8
#define HWIO_TURING_SLEEP_CFG_RCGR_SRC_DIV_BMSK                                                                              0x1f
#define HWIO_TURING_SLEEP_CFG_RCGR_SRC_DIV_SHFT                                                                               0x0

#define HWIO_TURING_XO_CMD_RCGR_ADDR                                                                                   (TURING_TURING_CC_REG_REG_BASE      + 0x00019000)
#define HWIO_TURING_XO_CMD_RCGR_OFFS                                                                                   (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00019000)
#define HWIO_TURING_XO_CMD_RCGR_RMSK                                                                                   0x800000f3
#define HWIO_TURING_XO_CMD_RCGR_IN          \
        in_dword_masked(HWIO_TURING_XO_CMD_RCGR_ADDR, HWIO_TURING_XO_CMD_RCGR_RMSK)
#define HWIO_TURING_XO_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_TURING_XO_CMD_RCGR_ADDR, m)
#define HWIO_TURING_XO_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_TURING_XO_CMD_RCGR_ADDR,v)
#define HWIO_TURING_XO_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_XO_CMD_RCGR_ADDR,m,v,HWIO_TURING_XO_CMD_RCGR_IN)
#define HWIO_TURING_XO_CMD_RCGR_ROOT_OFF_BMSK                                                                          0x80000000
#define HWIO_TURING_XO_CMD_RCGR_ROOT_OFF_SHFT                                                                                0x1f
#define HWIO_TURING_XO_CMD_RCGR_DIRTY_D_BMSK                                                                                 0x80
#define HWIO_TURING_XO_CMD_RCGR_DIRTY_D_SHFT                                                                                  0x7
#define HWIO_TURING_XO_CMD_RCGR_DIRTY_N_BMSK                                                                                 0x40
#define HWIO_TURING_XO_CMD_RCGR_DIRTY_N_SHFT                                                                                  0x6
#define HWIO_TURING_XO_CMD_RCGR_DIRTY_M_BMSK                                                                                 0x20
#define HWIO_TURING_XO_CMD_RCGR_DIRTY_M_SHFT                                                                                  0x5
#define HWIO_TURING_XO_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                          0x10
#define HWIO_TURING_XO_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                           0x4
#define HWIO_TURING_XO_CMD_RCGR_ROOT_EN_BMSK                                                                                  0x2
#define HWIO_TURING_XO_CMD_RCGR_ROOT_EN_SHFT                                                                                  0x1
#define HWIO_TURING_XO_CMD_RCGR_UPDATE_BMSK                                                                                   0x1
#define HWIO_TURING_XO_CMD_RCGR_UPDATE_SHFT                                                                                   0x0

#define HWIO_TURING_XO_CFG_RCGR_ADDR                                                                                   (TURING_TURING_CC_REG_REG_BASE      + 0x00019004)
#define HWIO_TURING_XO_CFG_RCGR_OFFS                                                                                   (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00019004)
#define HWIO_TURING_XO_CFG_RCGR_RMSK                                                                                       0x771f
#define HWIO_TURING_XO_CFG_RCGR_IN          \
        in_dword_masked(HWIO_TURING_XO_CFG_RCGR_ADDR, HWIO_TURING_XO_CFG_RCGR_RMSK)
#define HWIO_TURING_XO_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_TURING_XO_CFG_RCGR_ADDR, m)
#define HWIO_TURING_XO_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_TURING_XO_CFG_RCGR_ADDR,v)
#define HWIO_TURING_XO_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_XO_CFG_RCGR_ADDR,m,v,HWIO_TURING_XO_CFG_RCGR_IN)
#define HWIO_TURING_XO_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                           0x4000
#define HWIO_TURING_XO_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                              0xe
#define HWIO_TURING_XO_CFG_RCGR_MODE_BMSK                                                                                  0x3000
#define HWIO_TURING_XO_CFG_RCGR_MODE_SHFT                                                                                     0xc
#define HWIO_TURING_XO_CFG_RCGR_SRC_SEL_BMSK                                                                                0x700
#define HWIO_TURING_XO_CFG_RCGR_SRC_SEL_SHFT                                                                                  0x8
#define HWIO_TURING_XO_CFG_RCGR_SRC_DIV_BMSK                                                                                 0x1f
#define HWIO_TURING_XO_CFG_RCGR_SRC_DIV_SHFT                                                                                  0x0

#define HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_AON_CBCR_ADDR                                                           (TURING_TURING_CC_REG_REG_BASE      + 0x00023000)
#define HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_AON_CBCR_OFFS                                                           (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00023000)
#define HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_AON_CBCR_RMSK                                                           0x80000003
#define HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_AON_CBCR_IN          \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_AON_CBCR_ADDR, HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_AON_CBCR_RMSK)
#define HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_AON_CBCR_ADDR, m)
#define HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_AON_CBCR_OUT(v)      \
        out_dword(HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_AON_CBCR_ADDR,v)
#define HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_AON_CBCR_ADDR,m,v,HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_AON_CBCR_IN)
#define HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_AON_CBCR_CLK_OFF_BMSK                                                   0x80000000
#define HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_AON_CBCR_CLK_OFF_SHFT                                                         0x1f
#define HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_AON_CBCR_HW_CTL_BMSK                                                           0x2
#define HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_AON_CBCR_HW_CTL_SHFT                                                           0x1
#define HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_AON_CBCR_CLK_ENABLE_BMSK                                                       0x1
#define HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_AON_CBCR_CLK_ENABLE_SHFT                                                       0x0

#define HWIO_TURING_Q6SS_AHBM_AON_CBCR_ADDR                                                                            (TURING_TURING_CC_REG_REG_BASE      + 0x00024000)
#define HWIO_TURING_Q6SS_AHBM_AON_CBCR_OFFS                                                                            (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00024000)
#define HWIO_TURING_Q6SS_AHBM_AON_CBCR_RMSK                                                                            0x80000003
#define HWIO_TURING_Q6SS_AHBM_AON_CBCR_IN          \
        in_dword_masked(HWIO_TURING_Q6SS_AHBM_AON_CBCR_ADDR, HWIO_TURING_Q6SS_AHBM_AON_CBCR_RMSK)
#define HWIO_TURING_Q6SS_AHBM_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_TURING_Q6SS_AHBM_AON_CBCR_ADDR, m)
#define HWIO_TURING_Q6SS_AHBM_AON_CBCR_OUT(v)      \
        out_dword(HWIO_TURING_Q6SS_AHBM_AON_CBCR_ADDR,v)
#define HWIO_TURING_Q6SS_AHBM_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_Q6SS_AHBM_AON_CBCR_ADDR,m,v,HWIO_TURING_Q6SS_AHBM_AON_CBCR_IN)
#define HWIO_TURING_Q6SS_AHBM_AON_CBCR_CLK_OFF_BMSK                                                                    0x80000000
#define HWIO_TURING_Q6SS_AHBM_AON_CBCR_CLK_OFF_SHFT                                                                          0x1f
#define HWIO_TURING_Q6SS_AHBM_AON_CBCR_HW_CTL_BMSK                                                                            0x2
#define HWIO_TURING_Q6SS_AHBM_AON_CBCR_HW_CTL_SHFT                                                                            0x1
#define HWIO_TURING_Q6SS_AHBM_AON_CBCR_CLK_ENABLE_BMSK                                                                        0x1
#define HWIO_TURING_Q6SS_AHBM_AON_CBCR_CLK_ENABLE_SHFT                                                                        0x0

#define HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_ADDR                                                          (TURING_TURING_CC_REG_REG_BASE      + 0x00027000)
#define HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_OFFS                                                          (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00027000)
#define HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_RMSK                                                          0x80000003
#define HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_IN          \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_ADDR, HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_RMSK)
#define HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_INM(m)      \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_ADDR, m)
#define HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_OUT(v)      \
        out_dword(HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_ADDR,v)
#define HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_ADDR,m,v,HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_IN)
#define HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_CLK_OFF_BMSK                                                  0x80000000
#define HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_CLK_OFF_SHFT                                                        0x1f
#define HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_HW_CTL_BMSK                                                          0x2
#define HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_HW_CTL_SHFT                                                          0x1
#define HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_CLK_ENABLE_BMSK                                                      0x1
#define HWIO_TURING_TURING_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_CLK_ENABLE_SHFT                                                      0x0

#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_ADDR                                                          (TURING_TURING_CC_REG_REG_BASE      + 0x00029000)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_OFFS                                                          (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00029000)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_RMSK                                                          0x80000003
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_IN          \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_ADDR, HWIO_TURING_TURING_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_RMSK)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_INM(m)      \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_ADDR, m)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_OUT(v)      \
        out_dword(HWIO_TURING_TURING_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_ADDR,v)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TURING_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_ADDR,m,v,HWIO_TURING_TURING_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_IN)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_CLK_OFF_BMSK                                                  0x80000000
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_CLK_OFF_SHFT                                                        0x1f
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_HW_CTL_BMSK                                                          0x2
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_HW_CTL_SHFT                                                          0x1
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_CLK_ENABLE_BMSK                                                      0x1
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_CLK_ENABLE_SHFT                                                      0x0

#define HWIO_TURING_Q6SS_Q6_AXIM_CBCR_ADDR                                                                             (TURING_TURING_CC_REG_REG_BASE      + 0x0002b000)
#define HWIO_TURING_Q6SS_Q6_AXIM_CBCR_OFFS                                                                             (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x0002b000)
#define HWIO_TURING_Q6SS_Q6_AXIM_CBCR_RMSK                                                                             0x80000003
#define HWIO_TURING_Q6SS_Q6_AXIM_CBCR_IN          \
        in_dword_masked(HWIO_TURING_Q6SS_Q6_AXIM_CBCR_ADDR, HWIO_TURING_Q6SS_Q6_AXIM_CBCR_RMSK)
#define HWIO_TURING_Q6SS_Q6_AXIM_CBCR_INM(m)      \
        in_dword_masked(HWIO_TURING_Q6SS_Q6_AXIM_CBCR_ADDR, m)
#define HWIO_TURING_Q6SS_Q6_AXIM_CBCR_OUT(v)      \
        out_dword(HWIO_TURING_Q6SS_Q6_AXIM_CBCR_ADDR,v)
#define HWIO_TURING_Q6SS_Q6_AXIM_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_Q6SS_Q6_AXIM_CBCR_ADDR,m,v,HWIO_TURING_Q6SS_Q6_AXIM_CBCR_IN)
#define HWIO_TURING_Q6SS_Q6_AXIM_CBCR_CLK_OFF_BMSK                                                                     0x80000000
#define HWIO_TURING_Q6SS_Q6_AXIM_CBCR_CLK_OFF_SHFT                                                                           0x1f
#define HWIO_TURING_Q6SS_Q6_AXIM_CBCR_HW_CTL_BMSK                                                                             0x2
#define HWIO_TURING_Q6SS_Q6_AXIM_CBCR_HW_CTL_SHFT                                                                             0x1
#define HWIO_TURING_Q6SS_Q6_AXIM_CBCR_CLK_ENABLE_BMSK                                                                         0x1
#define HWIO_TURING_Q6SS_Q6_AXIM_CBCR_CLK_ENABLE_SHFT                                                                         0x0

#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_AXI_CBCR_ADDR                                                               (TURING_TURING_CC_REG_REG_BASE      + 0x0002c000)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_AXI_CBCR_OFFS                                                               (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x0002c000)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_AXI_CBCR_RMSK                                                               0x80000003
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_AXI_CBCR_IN          \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_Q6_SMMU_AXI_CBCR_ADDR, HWIO_TURING_TURING_WRAPPER_Q6_SMMU_AXI_CBCR_RMSK)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_AXI_CBCR_INM(m)      \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_Q6_SMMU_AXI_CBCR_ADDR, m)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_AXI_CBCR_OUT(v)      \
        out_dword(HWIO_TURING_TURING_WRAPPER_Q6_SMMU_AXI_CBCR_ADDR,v)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_AXI_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TURING_WRAPPER_Q6_SMMU_AXI_CBCR_ADDR,m,v,HWIO_TURING_TURING_WRAPPER_Q6_SMMU_AXI_CBCR_IN)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_AXI_CBCR_CLK_OFF_BMSK                                                       0x80000000
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_AXI_CBCR_CLK_OFF_SHFT                                                             0x1f
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_AXI_CBCR_HW_CTL_BMSK                                                               0x2
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_AXI_CBCR_HW_CTL_SHFT                                                               0x1
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_AXI_CBCR_CLK_ENABLE_BMSK                                                           0x1
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_AXI_CBCR_CLK_ENABLE_SHFT                                                           0x0

#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_AXI_GCC_CLK_OFF_STATUS_ADDR                                                 (TURING_TURING_CC_REG_REG_BASE      + 0x0002c004)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_AXI_GCC_CLK_OFF_STATUS_OFFS                                                 (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x0002c004)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_AXI_GCC_CLK_OFF_STATUS_RMSK                                                        0x1
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_AXI_GCC_CLK_OFF_STATUS_IN          \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_Q6_SMMU_AXI_GCC_CLK_OFF_STATUS_ADDR, HWIO_TURING_TURING_WRAPPER_Q6_SMMU_AXI_GCC_CLK_OFF_STATUS_RMSK)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_AXI_GCC_CLK_OFF_STATUS_INM(m)      \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_Q6_SMMU_AXI_GCC_CLK_OFF_STATUS_ADDR, m)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_AXI_GCC_CLK_OFF_STATUS_CLK_OFF_BMSK                                                0x1
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_AXI_GCC_CLK_OFF_STATUS_CLK_OFF_SHFT                                                0x0

#define HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_ADDR                                                            (TURING_TURING_CC_REG_REG_BASE      + 0x0002d000)
#define HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_OFFS                                                            (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x0002d000)
#define HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_RMSK                                                            0x80000003
#define HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_IN          \
        in_dword_masked(HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_ADDR, HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_RMSK)
#define HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_INM(m)      \
        in_dword_masked(HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_ADDR, m)
#define HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_OUT(v)      \
        out_dword(HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_ADDR,v)
#define HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_ADDR,m,v,HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_IN)
#define HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_CLK_OFF_BMSK                                                    0x80000000
#define HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_CLK_OFF_SHFT                                                          0x1f
#define HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_HW_CTL_BMSK                                                            0x2
#define HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_HW_CTL_SHFT                                                            0x1
#define HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_CLK_ENABLE_BMSK                                                        0x1
#define HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_CLK_ENABLE_SHFT                                                        0x0

#define HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_ADDR                                                            (TURING_TURING_CC_REG_REG_BASE      + 0x0002e000)
#define HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_OFFS                                                            (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x0002e000)
#define HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_RMSK                                                            0x80000003
#define HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_IN          \
        in_dword_masked(HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_ADDR, HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_RMSK)
#define HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_INM(m)      \
        in_dword_masked(HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_ADDR, m)
#define HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_OUT(v)      \
        out_dword(HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_ADDR,v)
#define HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_ADDR,m,v,HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_IN)
#define HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_CLK_OFF_BMSK                                                    0x80000000
#define HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_CLK_OFF_SHFT                                                          0x1f
#define HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_HW_CTL_BMSK                                                            0x2
#define HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_HW_CTL_SHFT                                                            0x1
#define HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_CLK_ENABLE_BMSK                                                        0x1
#define HWIO_TURING_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_CLK_ENABLE_SHFT                                                        0x0

#define HWIO_TURING_TURING_WRAPPER_MPU_CFG_AON_CBCR_ADDR                                                               (TURING_TURING_CC_REG_REG_BASE      + 0x0002f000)
#define HWIO_TURING_TURING_WRAPPER_MPU_CFG_AON_CBCR_OFFS                                                               (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x0002f000)
#define HWIO_TURING_TURING_WRAPPER_MPU_CFG_AON_CBCR_RMSK                                                               0x80000003
#define HWIO_TURING_TURING_WRAPPER_MPU_CFG_AON_CBCR_IN          \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_MPU_CFG_AON_CBCR_ADDR, HWIO_TURING_TURING_WRAPPER_MPU_CFG_AON_CBCR_RMSK)
#define HWIO_TURING_TURING_WRAPPER_MPU_CFG_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_MPU_CFG_AON_CBCR_ADDR, m)
#define HWIO_TURING_TURING_WRAPPER_MPU_CFG_AON_CBCR_OUT(v)      \
        out_dword(HWIO_TURING_TURING_WRAPPER_MPU_CFG_AON_CBCR_ADDR,v)
#define HWIO_TURING_TURING_WRAPPER_MPU_CFG_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TURING_WRAPPER_MPU_CFG_AON_CBCR_ADDR,m,v,HWIO_TURING_TURING_WRAPPER_MPU_CFG_AON_CBCR_IN)
#define HWIO_TURING_TURING_WRAPPER_MPU_CFG_AON_CBCR_CLK_OFF_BMSK                                                       0x80000000
#define HWIO_TURING_TURING_WRAPPER_MPU_CFG_AON_CBCR_CLK_OFF_SHFT                                                             0x1f
#define HWIO_TURING_TURING_WRAPPER_MPU_CFG_AON_CBCR_HW_CTL_BMSK                                                               0x2
#define HWIO_TURING_TURING_WRAPPER_MPU_CFG_AON_CBCR_HW_CTL_SHFT                                                               0x1
#define HWIO_TURING_TURING_WRAPPER_MPU_CFG_AON_CBCR_CLK_ENABLE_BMSK                                                           0x1
#define HWIO_TURING_TURING_WRAPPER_MPU_CFG_AON_CBCR_CLK_ENABLE_SHFT                                                           0x0

#define HWIO_TURING_TURING_WRAPPER_Q6_AHBM_MPU_AON_CBCR_ADDR                                                           (TURING_TURING_CC_REG_REG_BASE      + 0x00030000)
#define HWIO_TURING_TURING_WRAPPER_Q6_AHBM_MPU_AON_CBCR_OFFS                                                           (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00030000)
#define HWIO_TURING_TURING_WRAPPER_Q6_AHBM_MPU_AON_CBCR_RMSK                                                           0x80000003
#define HWIO_TURING_TURING_WRAPPER_Q6_AHBM_MPU_AON_CBCR_IN          \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_Q6_AHBM_MPU_AON_CBCR_ADDR, HWIO_TURING_TURING_WRAPPER_Q6_AHBM_MPU_AON_CBCR_RMSK)
#define HWIO_TURING_TURING_WRAPPER_Q6_AHBM_MPU_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_Q6_AHBM_MPU_AON_CBCR_ADDR, m)
#define HWIO_TURING_TURING_WRAPPER_Q6_AHBM_MPU_AON_CBCR_OUT(v)      \
        out_dword(HWIO_TURING_TURING_WRAPPER_Q6_AHBM_MPU_AON_CBCR_ADDR,v)
#define HWIO_TURING_TURING_WRAPPER_Q6_AHBM_MPU_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TURING_WRAPPER_Q6_AHBM_MPU_AON_CBCR_ADDR,m,v,HWIO_TURING_TURING_WRAPPER_Q6_AHBM_MPU_AON_CBCR_IN)
#define HWIO_TURING_TURING_WRAPPER_Q6_AHBM_MPU_AON_CBCR_CLK_OFF_BMSK                                                   0x80000000
#define HWIO_TURING_TURING_WRAPPER_Q6_AHBM_MPU_AON_CBCR_CLK_OFF_SHFT                                                         0x1f
#define HWIO_TURING_TURING_WRAPPER_Q6_AHBM_MPU_AON_CBCR_HW_CTL_BMSK                                                           0x2
#define HWIO_TURING_TURING_WRAPPER_Q6_AHBM_MPU_AON_CBCR_HW_CTL_SHFT                                                           0x1
#define HWIO_TURING_TURING_WRAPPER_Q6_AHBM_MPU_AON_CBCR_CLK_ENABLE_BMSK                                                       0x1
#define HWIO_TURING_TURING_WRAPPER_Q6_AHBM_MPU_AON_CBCR_CLK_ENABLE_SHFT                                                       0x0

#define HWIO_TURING_Q6SS_AHBS_AON_CBCR_ADDR                                                                            (TURING_TURING_CC_REG_REG_BASE      + 0x00031000)
#define HWIO_TURING_Q6SS_AHBS_AON_CBCR_OFFS                                                                            (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00031000)
#define HWIO_TURING_Q6SS_AHBS_AON_CBCR_RMSK                                                                            0x80000003
#define HWIO_TURING_Q6SS_AHBS_AON_CBCR_IN          \
        in_dword_masked(HWIO_TURING_Q6SS_AHBS_AON_CBCR_ADDR, HWIO_TURING_Q6SS_AHBS_AON_CBCR_RMSK)
#define HWIO_TURING_Q6SS_AHBS_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_TURING_Q6SS_AHBS_AON_CBCR_ADDR, m)
#define HWIO_TURING_Q6SS_AHBS_AON_CBCR_OUT(v)      \
        out_dword(HWIO_TURING_Q6SS_AHBS_AON_CBCR_ADDR,v)
#define HWIO_TURING_Q6SS_AHBS_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_Q6SS_AHBS_AON_CBCR_ADDR,m,v,HWIO_TURING_Q6SS_AHBS_AON_CBCR_IN)
#define HWIO_TURING_Q6SS_AHBS_AON_CBCR_CLK_OFF_BMSK                                                                    0x80000000
#define HWIO_TURING_Q6SS_AHBS_AON_CBCR_CLK_OFF_SHFT                                                                          0x1f
#define HWIO_TURING_Q6SS_AHBS_AON_CBCR_HW_CTL_BMSK                                                                            0x2
#define HWIO_TURING_Q6SS_AHBS_AON_CBCR_HW_CTL_SHFT                                                                            0x1
#define HWIO_TURING_Q6SS_AHBS_AON_CBCR_CLK_ENABLE_BMSK                                                                        0x1
#define HWIO_TURING_Q6SS_AHBS_AON_CBCR_CLK_ENABLE_SHFT                                                                        0x0

#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ADDR                                                                (TURING_TURING_CC_REG_REG_BASE      + 0x00033000)
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_CMD_RCGR_OFFS                                                                (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00033000)
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_CMD_RCGR_RMSK                                                                0x800000f3
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_CMD_RCGR_IN          \
        in_dword_masked(HWIO_TURING_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ADDR, HWIO_TURING_QOS_FIXED_LAT_COUNTER_CMD_RCGR_RMSK)
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_TURING_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ADDR, m)
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_TURING_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ADDR,v)
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ADDR,m,v,HWIO_TURING_QOS_FIXED_LAT_COUNTER_CMD_RCGR_IN)
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ROOT_OFF_BMSK                                                       0x80000000
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ROOT_OFF_SHFT                                                             0x1f
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_CMD_RCGR_DIRTY_D_BMSK                                                              0x80
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_CMD_RCGR_DIRTY_D_SHFT                                                               0x7
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_CMD_RCGR_DIRTY_N_BMSK                                                              0x40
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_CMD_RCGR_DIRTY_N_SHFT                                                               0x6
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_CMD_RCGR_DIRTY_M_BMSK                                                              0x20
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_CMD_RCGR_DIRTY_M_SHFT                                                               0x5
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                       0x10
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                        0x4
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ROOT_EN_BMSK                                                               0x2
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ROOT_EN_SHFT                                                               0x1
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_CMD_RCGR_UPDATE_BMSK                                                                0x1
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_CMD_RCGR_UPDATE_SHFT                                                                0x0

#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_CFG_RCGR_ADDR                                                                (TURING_TURING_CC_REG_REG_BASE      + 0x00033004)
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_CFG_RCGR_OFFS                                                                (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00033004)
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_CFG_RCGR_RMSK                                                                    0x771f
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_CFG_RCGR_IN          \
        in_dword_masked(HWIO_TURING_QOS_FIXED_LAT_COUNTER_CFG_RCGR_ADDR, HWIO_TURING_QOS_FIXED_LAT_COUNTER_CFG_RCGR_RMSK)
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_TURING_QOS_FIXED_LAT_COUNTER_CFG_RCGR_ADDR, m)
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_TURING_QOS_FIXED_LAT_COUNTER_CFG_RCGR_ADDR,v)
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QOS_FIXED_LAT_COUNTER_CFG_RCGR_ADDR,m,v,HWIO_TURING_QOS_FIXED_LAT_COUNTER_CFG_RCGR_IN)
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_CFG_RCGR_ALT_SRC_SEL_BMSK                                                        0x4000
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_CFG_RCGR_ALT_SRC_SEL_SHFT                                                           0xe
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_CFG_RCGR_MODE_BMSK                                                               0x3000
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_CFG_RCGR_MODE_SHFT                                                                  0xc
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_CFG_RCGR_SRC_SEL_BMSK                                                             0x700
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_CFG_RCGR_SRC_SEL_SHFT                                                               0x8
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_CFG_RCGR_SRC_DIV_BMSK                                                              0x1f
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_CFG_RCGR_SRC_DIV_SHFT                                                               0x0

#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_M_ADDR                                                                       (TURING_TURING_CC_REG_REG_BASE      + 0x00033008)
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_M_OFFS                                                                       (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00033008)
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_M_RMSK                                                                             0xff
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_M_IN          \
        in_dword_masked(HWIO_TURING_QOS_FIXED_LAT_COUNTER_M_ADDR, HWIO_TURING_QOS_FIXED_LAT_COUNTER_M_RMSK)
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_M_INM(m)      \
        in_dword_masked(HWIO_TURING_QOS_FIXED_LAT_COUNTER_M_ADDR, m)
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_M_OUT(v)      \
        out_dword(HWIO_TURING_QOS_FIXED_LAT_COUNTER_M_ADDR,v)
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QOS_FIXED_LAT_COUNTER_M_ADDR,m,v,HWIO_TURING_QOS_FIXED_LAT_COUNTER_M_IN)
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_M_M_BMSK                                                                           0xff
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_M_M_SHFT                                                                            0x0

#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_N_ADDR                                                                       (TURING_TURING_CC_REG_REG_BASE      + 0x0003300c)
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_N_OFFS                                                                       (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x0003300c)
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_N_RMSK                                                                             0xff
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_N_IN          \
        in_dword_masked(HWIO_TURING_QOS_FIXED_LAT_COUNTER_N_ADDR, HWIO_TURING_QOS_FIXED_LAT_COUNTER_N_RMSK)
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_N_INM(m)      \
        in_dword_masked(HWIO_TURING_QOS_FIXED_LAT_COUNTER_N_ADDR, m)
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_N_OUT(v)      \
        out_dword(HWIO_TURING_QOS_FIXED_LAT_COUNTER_N_ADDR,v)
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QOS_FIXED_LAT_COUNTER_N_ADDR,m,v,HWIO_TURING_QOS_FIXED_LAT_COUNTER_N_IN)
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_N_NOT_N_MINUS_M_BMSK                                                               0xff
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_N_NOT_N_MINUS_M_SHFT                                                                0x0

#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_D_ADDR                                                                       (TURING_TURING_CC_REG_REG_BASE      + 0x00033010)
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_D_OFFS                                                                       (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00033010)
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_D_RMSK                                                                             0xff
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_D_IN          \
        in_dword_masked(HWIO_TURING_QOS_FIXED_LAT_COUNTER_D_ADDR, HWIO_TURING_QOS_FIXED_LAT_COUNTER_D_RMSK)
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_D_INM(m)      \
        in_dword_masked(HWIO_TURING_QOS_FIXED_LAT_COUNTER_D_ADDR, m)
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_D_OUT(v)      \
        out_dword(HWIO_TURING_QOS_FIXED_LAT_COUNTER_D_ADDR,v)
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QOS_FIXED_LAT_COUNTER_D_ADDR,m,v,HWIO_TURING_QOS_FIXED_LAT_COUNTER_D_IN)
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_D_NOT_2D_BMSK                                                                      0xff
#define HWIO_TURING_QOS_FIXED_LAT_COUNTER_D_NOT_2D_SHFT                                                                       0x0

#define HWIO_TURING_TURING_WRAPPER_QOS_AHBS_AON_CBCR_ADDR                                                              (TURING_TURING_CC_REG_REG_BASE      + 0x00033014)
#define HWIO_TURING_TURING_WRAPPER_QOS_AHBS_AON_CBCR_OFFS                                                              (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00033014)
#define HWIO_TURING_TURING_WRAPPER_QOS_AHBS_AON_CBCR_RMSK                                                              0x80000003
#define HWIO_TURING_TURING_WRAPPER_QOS_AHBS_AON_CBCR_IN          \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_QOS_AHBS_AON_CBCR_ADDR, HWIO_TURING_TURING_WRAPPER_QOS_AHBS_AON_CBCR_RMSK)
#define HWIO_TURING_TURING_WRAPPER_QOS_AHBS_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_QOS_AHBS_AON_CBCR_ADDR, m)
#define HWIO_TURING_TURING_WRAPPER_QOS_AHBS_AON_CBCR_OUT(v)      \
        out_dword(HWIO_TURING_TURING_WRAPPER_QOS_AHBS_AON_CBCR_ADDR,v)
#define HWIO_TURING_TURING_WRAPPER_QOS_AHBS_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TURING_WRAPPER_QOS_AHBS_AON_CBCR_ADDR,m,v,HWIO_TURING_TURING_WRAPPER_QOS_AHBS_AON_CBCR_IN)
#define HWIO_TURING_TURING_WRAPPER_QOS_AHBS_AON_CBCR_CLK_OFF_BMSK                                                      0x80000000
#define HWIO_TURING_TURING_WRAPPER_QOS_AHBS_AON_CBCR_CLK_OFF_SHFT                                                            0x1f
#define HWIO_TURING_TURING_WRAPPER_QOS_AHBS_AON_CBCR_HW_CTL_BMSK                                                              0x2
#define HWIO_TURING_TURING_WRAPPER_QOS_AHBS_AON_CBCR_HW_CTL_SHFT                                                              0x1
#define HWIO_TURING_TURING_WRAPPER_QOS_AHBS_AON_CBCR_CLK_ENABLE_BMSK                                                          0x1
#define HWIO_TURING_TURING_WRAPPER_QOS_AHBS_AON_CBCR_CLK_ENABLE_SHFT                                                          0x0

#define HWIO_TURING_TURING_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_ADDR                                                        (TURING_TURING_CC_REG_REG_BASE      + 0x00033018)
#define HWIO_TURING_TURING_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_OFFS                                                        (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00033018)
#define HWIO_TURING_TURING_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_RMSK                                                        0x80000003
#define HWIO_TURING_TURING_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_IN          \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_ADDR, HWIO_TURING_TURING_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_RMSK)
#define HWIO_TURING_TURING_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_INM(m)      \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_ADDR, m)
#define HWIO_TURING_TURING_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_OUT(v)      \
        out_dword(HWIO_TURING_TURING_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_ADDR,v)
#define HWIO_TURING_TURING_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TURING_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_ADDR,m,v,HWIO_TURING_TURING_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_IN)
#define HWIO_TURING_TURING_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_CLK_OFF_BMSK                                                0x80000000
#define HWIO_TURING_TURING_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_CLK_OFF_SHFT                                                      0x1f
#define HWIO_TURING_TURING_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_HW_CTL_BMSK                                                        0x2
#define HWIO_TURING_TURING_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_HW_CTL_SHFT                                                        0x1
#define HWIO_TURING_TURING_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_CLK_ENABLE_BMSK                                                    0x1
#define HWIO_TURING_TURING_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_CLK_ENABLE_SHFT                                                    0x0

#define HWIO_TURING_TURING_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR                                            (TURING_TURING_CC_REG_REG_BASE      + 0x0003301c)
#define HWIO_TURING_TURING_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_OFFS                                            (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x0003301c)
#define HWIO_TURING_TURING_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_RMSK                                            0x80000003
#define HWIO_TURING_TURING_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_IN          \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR, HWIO_TURING_TURING_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_RMSK)
#define HWIO_TURING_TURING_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_INM(m)      \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR, m)
#define HWIO_TURING_TURING_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_OUT(v)      \
        out_dword(HWIO_TURING_TURING_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR,v)
#define HWIO_TURING_TURING_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TURING_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR,m,v,HWIO_TURING_TURING_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_IN)
#define HWIO_TURING_TURING_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_CLK_OFF_BMSK                                    0x80000000
#define HWIO_TURING_TURING_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_CLK_OFF_SHFT                                          0x1f
#define HWIO_TURING_TURING_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_HW_CTL_BMSK                                            0x2
#define HWIO_TURING_TURING_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_HW_CTL_SHFT                                            0x1
#define HWIO_TURING_TURING_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_CLK_ENABLE_BMSK                                        0x1
#define HWIO_TURING_TURING_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_CLK_ENABLE_SHFT                                        0x0

#define HWIO_TURING_TURING_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_ADDR                                              (TURING_TURING_CC_REG_REG_BASE      + 0x00033020)
#define HWIO_TURING_TURING_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_OFFS                                              (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00033020)
#define HWIO_TURING_TURING_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_RMSK                                              0x80000003
#define HWIO_TURING_TURING_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_IN          \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_ADDR, HWIO_TURING_TURING_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_RMSK)
#define HWIO_TURING_TURING_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_INM(m)      \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_ADDR, m)
#define HWIO_TURING_TURING_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_OUT(v)      \
        out_dword(HWIO_TURING_TURING_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_ADDR,v)
#define HWIO_TURING_TURING_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TURING_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_ADDR,m,v,HWIO_TURING_TURING_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_IN)
#define HWIO_TURING_TURING_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_CLK_OFF_BMSK                                      0x80000000
#define HWIO_TURING_TURING_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_CLK_OFF_SHFT                                            0x1f
#define HWIO_TURING_TURING_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_HW_CTL_BMSK                                              0x2
#define HWIO_TURING_TURING_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_HW_CTL_SHFT                                              0x1
#define HWIO_TURING_TURING_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_CLK_ENABLE_BMSK                                          0x1
#define HWIO_TURING_TURING_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_CLK_ENABLE_SHFT                                          0x0

#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_ADDR                                                      (TURING_TURING_CC_REG_REG_BASE      + 0x00035004)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_OFFS                                                      (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00035004)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_RMSK                                                             0x2
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_IN          \
        in_dword_masked(HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_ADDR, HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_RMSK)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_INM(m)      \
        in_dword_masked(HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_ADDR, m)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_OUT(v)      \
        out_dword(HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_ADDR,v)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_ADDR,m,v,HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_IN)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_BMSK                      0x2
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_SHFT                      0x1

#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_ADDR                                                      (TURING_TURING_CC_REG_REG_BASE      + 0x00035008)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_OFFS                                                      (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00035008)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_RMSK                                                             0x2
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_IN          \
        in_dword_masked(HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_ADDR, HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_RMSK)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_INM(m)      \
        in_dword_masked(HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_ADDR, m)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_OUT(v)      \
        out_dword(HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_ADDR,v)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_ADDR,m,v,HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_IN)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_Q6_SMMU_SEQUENCE_ABORT_IRQ_EN_BMSK                               0x2
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_Q6_SMMU_SEQUENCE_ABORT_IRQ_EN_SHFT                               0x1

#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR                                     (TURING_TURING_CC_REG_REG_BASE      + 0x00036000)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_OFFS                                     (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00036000)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_RMSK                                     0x80000003
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_IN          \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR, HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_RMSK)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_INM(m)      \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR, m)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_OUT(v)      \
        out_dword(HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR,v)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR,m,v,HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_IN)
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_BMSK                      0x80000000
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_SHFT                            0x1f
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_IRQ_EN_APPS_BMSK                 0x2
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_IRQ_EN_APPS_SHFT                 0x1
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_IRQ_EN_Q6_BMSK                   0x1
#define HWIO_TURING_TURING_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_IRQ_EN_Q6_SHFT                   0x0

#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_ADDR                                                    (TURING_TURING_CC_REG_REG_BASE      + 0x00036004)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_OFFS                                                    (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00036004)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_RMSK                                                           0x2
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_IN          \
        in_dword_masked(HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_ADDR, HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_RMSK)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_INM(m)      \
        in_dword_masked(HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_ADDR, m)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_OUT(v)      \
        out_dword(HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_ADDR,v)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_ADDR,m,v,HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_IN)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_BMSK                    0x2
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_SHFT                    0x1

#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_ADDR                                                    (TURING_TURING_CC_REG_REG_BASE      + 0x00036008)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_OFFS                                                    (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00036008)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_RMSK                                                           0x2
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_IN          \
        in_dword_masked(HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_ADDR, HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_RMSK)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_INM(m)      \
        in_dword_masked(HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_ADDR, m)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_OUT(v)      \
        out_dword(HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_ADDR,v)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_ADDR,m,v,HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_IN)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_Q6_SMMU_SEQUENCE_ABORT_IRQ_EN_BMSK                             0x2
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_Q6_SMMU_SEQUENCE_ABORT_IRQ_EN_SHFT                             0x1

#define HWIO_TURING_TURING_WRAPPER_Q6_VOTE_TURING_Q6_SMMU_GDS_ADDR                                                     (TURING_TURING_CC_REG_REG_BASE      + 0x00037000)
#define HWIO_TURING_TURING_WRAPPER_Q6_VOTE_TURING_Q6_SMMU_GDS_OFFS                                                     (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00037000)
#define HWIO_TURING_TURING_WRAPPER_Q6_VOTE_TURING_Q6_SMMU_GDS_RMSK                                                     0x80000001
#define HWIO_TURING_TURING_WRAPPER_Q6_VOTE_TURING_Q6_SMMU_GDS_IN          \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_Q6_VOTE_TURING_Q6_SMMU_GDS_ADDR, HWIO_TURING_TURING_WRAPPER_Q6_VOTE_TURING_Q6_SMMU_GDS_RMSK)
#define HWIO_TURING_TURING_WRAPPER_Q6_VOTE_TURING_Q6_SMMU_GDS_INM(m)      \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_Q6_VOTE_TURING_Q6_SMMU_GDS_ADDR, m)
#define HWIO_TURING_TURING_WRAPPER_Q6_VOTE_TURING_Q6_SMMU_GDS_OUT(v)      \
        out_dword(HWIO_TURING_TURING_WRAPPER_Q6_VOTE_TURING_Q6_SMMU_GDS_ADDR,v)
#define HWIO_TURING_TURING_WRAPPER_Q6_VOTE_TURING_Q6_SMMU_GDS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TURING_WRAPPER_Q6_VOTE_TURING_Q6_SMMU_GDS_ADDR,m,v,HWIO_TURING_TURING_WRAPPER_Q6_VOTE_TURING_Q6_SMMU_GDS_IN)
#define HWIO_TURING_TURING_WRAPPER_Q6_VOTE_TURING_Q6_SMMU_GDS_Q6_SMMU_PWR_ON_BMSK                                      0x80000000
#define HWIO_TURING_TURING_WRAPPER_Q6_VOTE_TURING_Q6_SMMU_GDS_Q6_SMMU_PWR_ON_SHFT                                            0x1f
#define HWIO_TURING_TURING_WRAPPER_Q6_VOTE_TURING_Q6_SMMU_GDS_Q6_SMMU_SW_COLLAPSE_BMSK                                        0x1
#define HWIO_TURING_TURING_WRAPPER_Q6_VOTE_TURING_Q6_SMMU_GDS_Q6_SMMU_SW_COLLAPSE_SHFT                                        0x0

#define HWIO_TURING_TURING_WRAPPER_BUS_TIMEOUT_AON_CBCR_ADDR                                                           (TURING_TURING_CC_REG_REG_BASE      + 0x00038000)
#define HWIO_TURING_TURING_WRAPPER_BUS_TIMEOUT_AON_CBCR_OFFS                                                           (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x00038000)
#define HWIO_TURING_TURING_WRAPPER_BUS_TIMEOUT_AON_CBCR_RMSK                                                           0x80000003
#define HWIO_TURING_TURING_WRAPPER_BUS_TIMEOUT_AON_CBCR_IN          \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_BUS_TIMEOUT_AON_CBCR_ADDR, HWIO_TURING_TURING_WRAPPER_BUS_TIMEOUT_AON_CBCR_RMSK)
#define HWIO_TURING_TURING_WRAPPER_BUS_TIMEOUT_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_TURING_TURING_WRAPPER_BUS_TIMEOUT_AON_CBCR_ADDR, m)
#define HWIO_TURING_TURING_WRAPPER_BUS_TIMEOUT_AON_CBCR_OUT(v)      \
        out_dword(HWIO_TURING_TURING_WRAPPER_BUS_TIMEOUT_AON_CBCR_ADDR,v)
#define HWIO_TURING_TURING_WRAPPER_BUS_TIMEOUT_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TURING_WRAPPER_BUS_TIMEOUT_AON_CBCR_ADDR,m,v,HWIO_TURING_TURING_WRAPPER_BUS_TIMEOUT_AON_CBCR_IN)
#define HWIO_TURING_TURING_WRAPPER_BUS_TIMEOUT_AON_CBCR_CLK_OFF_BMSK                                                   0x80000000
#define HWIO_TURING_TURING_WRAPPER_BUS_TIMEOUT_AON_CBCR_CLK_OFF_SHFT                                                         0x1f
#define HWIO_TURING_TURING_WRAPPER_BUS_TIMEOUT_AON_CBCR_HW_CTL_BMSK                                                           0x2
#define HWIO_TURING_TURING_WRAPPER_BUS_TIMEOUT_AON_CBCR_HW_CTL_SHFT                                                           0x1
#define HWIO_TURING_TURING_WRAPPER_BUS_TIMEOUT_AON_CBCR_CLK_ENABLE_BMSK                                                       0x1
#define HWIO_TURING_TURING_WRAPPER_BUS_TIMEOUT_AON_CBCR_CLK_ENABLE_SHFT                                                       0x0

#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_ADDR                                                      (TURING_TURING_CC_REG_REG_BASE      + 0x0003a004)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_OFFS                                                      (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x0003a004)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_RMSK                                                             0x2
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_IN          \
        in_dword_masked(HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_ADDR, HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_RMSK)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_INM(m)      \
        in_dword_masked(HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_ADDR, m)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_OUT(v)      \
        out_dword(HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_ADDR,v)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_ADDR,m,v,HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_IN)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_BMSK                      0x2
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_SHFT                      0x1

#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_ADDR                                                      (TURING_TURING_CC_REG_REG_BASE      + 0x0003a008)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_OFFS                                                      (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x0003a008)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_RMSK                                                             0x2
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_IN          \
        in_dword_masked(HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_ADDR, HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_RMSK)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_INM(m)      \
        in_dword_masked(HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_ADDR, m)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_OUT(v)      \
        out_dword(HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_ADDR,v)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_ADDR,m,v,HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_IN)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_Q6_SMMU_SEQUENCE_ABORT_IRQ_EN_BMSK                               0x2
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_Q6_SMMU_SEQUENCE_ABORT_IRQ_EN_SHFT                               0x1

#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_ADDR                                                     (TURING_TURING_CC_REG_REG_BASE      + 0x0003b004)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_OFFS                                                     (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x0003b004)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_RMSK                                                            0x2
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_IN          \
        in_dword_masked(HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_ADDR, HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_RMSK)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_INM(m)      \
        in_dword_masked(HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_ADDR, m)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_OUT(v)      \
        out_dword(HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_ADDR,v)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_ADDR,m,v,HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_IN)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_BMSK                     0x2
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_SHFT                     0x1

#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_ADDR                                                     (TURING_TURING_CC_REG_REG_BASE      + 0x0003b008)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_OFFS                                                     (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x0003b008)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_RMSK                                                            0x2
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_IN          \
        in_dword_masked(HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_ADDR, HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_RMSK)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_INM(m)      \
        in_dword_masked(HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_ADDR, m)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_OUT(v)      \
        out_dword(HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_ADDR,v)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_ADDR,m,v,HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_IN)
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_Q6_SMMU_SEQUENCE_ABORT_IRQ_EN_BMSK                              0x2
#define HWIO_TURING_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_Q6_SMMU_SEQUENCE_ABORT_IRQ_EN_SHFT                              0x1

#define HWIO_TURING_DBG_CLK_ADDR                                                                                       (TURING_TURING_CC_REG_REG_BASE      + 0x0003c000)
#define HWIO_TURING_DBG_CLK_OFFS                                                                                       (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x0003c000)
#define HWIO_TURING_DBG_CLK_RMSK                                                                                       0xfff0ffff
#define HWIO_TURING_DBG_CLK_IN          \
        in_dword_masked(HWIO_TURING_DBG_CLK_ADDR, HWIO_TURING_DBG_CLK_RMSK)
#define HWIO_TURING_DBG_CLK_INM(m)      \
        in_dword_masked(HWIO_TURING_DBG_CLK_ADDR, m)
#define HWIO_TURING_DBG_CLK_OUT(v)      \
        out_dword(HWIO_TURING_DBG_CLK_ADDR,v)
#define HWIO_TURING_DBG_CLK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_DBG_CLK_ADDR,m,v,HWIO_TURING_DBG_CLK_IN)
#define HWIO_TURING_DBG_CLK_RESETN_MUX_SEL_BMSK                                                                        0xe0000000
#define HWIO_TURING_DBG_CLK_RESETN_MUX_SEL_SHFT                                                                              0x1d
#define HWIO_TURING_DBG_CLK_BYPASSNL_MUX_SEL_BMSK                                                                      0x1c000000
#define HWIO_TURING_DBG_CLK_BYPASSNL_MUX_SEL_SHFT                                                                            0x1a
#define HWIO_TURING_DBG_CLK_RESERVE_BITS25_21_BMSK                                                                      0x3e00000
#define HWIO_TURING_DBG_CLK_RESERVE_BITS25_21_SHFT                                                                           0x15
#define HWIO_TURING_DBG_CLK_DBG_CLK_ENABLE_BMSK                                                                          0x100000
#define HWIO_TURING_DBG_CLK_DBG_CLK_ENABLE_SHFT                                                                              0x14
#define HWIO_TURING_DBG_CLK_DBG_CLK_MUX_SEL_BMSK                                                                           0xffff
#define HWIO_TURING_DBG_CLK_DBG_CLK_MUX_SEL_SHFT                                                                              0x0

#define HWIO_TURING_TEST_BUS_SEL_ADDR                                                                                  (TURING_TURING_CC_REG_REG_BASE      + 0x0003c004)
#define HWIO_TURING_TEST_BUS_SEL_OFFS                                                                                  (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x0003c004)
#define HWIO_TURING_TEST_BUS_SEL_RMSK                                                                                         0x1
#define HWIO_TURING_TEST_BUS_SEL_IN          \
        in_dword_masked(HWIO_TURING_TEST_BUS_SEL_ADDR, HWIO_TURING_TEST_BUS_SEL_RMSK)
#define HWIO_TURING_TEST_BUS_SEL_INM(m)      \
        in_dword_masked(HWIO_TURING_TEST_BUS_SEL_ADDR, m)
#define HWIO_TURING_TEST_BUS_SEL_OUT(v)      \
        out_dword(HWIO_TURING_TEST_BUS_SEL_ADDR,v)
#define HWIO_TURING_TEST_BUS_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TEST_BUS_SEL_ADDR,m,v,HWIO_TURING_TEST_BUS_SEL_IN)
#define HWIO_TURING_TEST_BUS_SEL_SEL_BMSK                                                                                     0x1
#define HWIO_TURING_TEST_BUS_SEL_SEL_SHFT                                                                                     0x0

#define HWIO_TURING_PLLOUT_LV_TEST_SEL_ADDR                                                                            (TURING_TURING_CC_REG_REG_BASE      + 0x0003d000)
#define HWIO_TURING_PLLOUT_LV_TEST_SEL_OFFS                                                                            (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x0003d000)
#define HWIO_TURING_PLLOUT_LV_TEST_SEL_RMSK                                                                                   0x3
#define HWIO_TURING_PLLOUT_LV_TEST_SEL_IN          \
        in_dword_masked(HWIO_TURING_PLLOUT_LV_TEST_SEL_ADDR, HWIO_TURING_PLLOUT_LV_TEST_SEL_RMSK)
#define HWIO_TURING_PLLOUT_LV_TEST_SEL_INM(m)      \
        in_dword_masked(HWIO_TURING_PLLOUT_LV_TEST_SEL_ADDR, m)
#define HWIO_TURING_PLLOUT_LV_TEST_SEL_OUT(v)      \
        out_dword(HWIO_TURING_PLLOUT_LV_TEST_SEL_ADDR,v)
#define HWIO_TURING_PLLOUT_LV_TEST_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_PLLOUT_LV_TEST_SEL_ADDR,m,v,HWIO_TURING_PLLOUT_LV_TEST_SEL_IN)
#define HWIO_TURING_PLLOUT_LV_TEST_SEL_SEL_BMSK                                                                               0x3
#define HWIO_TURING_PLLOUT_LV_TEST_SEL_SEL_SHFT                                                                               0x0

#define HWIO_TURING_TURING_CC_SPARE_REG_ADDR                                                                           (TURING_TURING_CC_REG_REG_BASE      + 0x0003e000)
#define HWIO_TURING_TURING_CC_SPARE_REG_OFFS                                                                           (TURING_TURING_CC_REG_REG_BASE_OFFS + 0x0003e000)
#define HWIO_TURING_TURING_CC_SPARE_REG_RMSK                                                                           0xffffffff
#define HWIO_TURING_TURING_CC_SPARE_REG_IN          \
        in_dword_masked(HWIO_TURING_TURING_CC_SPARE_REG_ADDR, HWIO_TURING_TURING_CC_SPARE_REG_RMSK)
#define HWIO_TURING_TURING_CC_SPARE_REG_INM(m)      \
        in_dword_masked(HWIO_TURING_TURING_CC_SPARE_REG_ADDR, m)
#define HWIO_TURING_TURING_CC_SPARE_REG_OUT(v)      \
        out_dword(HWIO_TURING_TURING_CC_SPARE_REG_ADDR,v)
#define HWIO_TURING_TURING_CC_SPARE_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TURING_CC_SPARE_REG_ADDR,m,v,HWIO_TURING_TURING_CC_SPARE_REG_IN)
#define HWIO_TURING_TURING_CC_SPARE_REG_SPARE_BMSK                                                                     0xffffffff
#define HWIO_TURING_TURING_CC_SPARE_REG_SPARE_SHFT                                                                            0x0

/*----------------------------------------------------------------------------
 * MODULE: TURING_QDSP6V60SS_PUB
 *--------------------------------------------------------------------------*/

#define TURING_QDSP6V60SS_PUB_REG_BASE                                             (TURING_BASE      + 0x00300000)
#define TURING_QDSP6V60SS_PUB_REG_BASE_OFFS                                        0x00300000

#define HWIO_TURING_QDSP6SS_VERSION_ADDR                                           (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000000)
#define HWIO_TURING_QDSP6SS_VERSION_OFFS                                           (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000000)
#define HWIO_TURING_QDSP6SS_VERSION_RMSK                                           0xffffffff
#define HWIO_TURING_QDSP6SS_VERSION_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_VERSION_ADDR, HWIO_TURING_QDSP6SS_VERSION_RMSK)
#define HWIO_TURING_QDSP6SS_VERSION_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_VERSION_ADDR, m)
#define HWIO_TURING_QDSP6SS_VERSION_MAJOR_BMSK                                     0xf0000000
#define HWIO_TURING_QDSP6SS_VERSION_MAJOR_SHFT                                           0x1c
#define HWIO_TURING_QDSP6SS_VERSION_MINOR_BMSK                                      0xfff0000
#define HWIO_TURING_QDSP6SS_VERSION_MINOR_SHFT                                           0x10
#define HWIO_TURING_QDSP6SS_VERSION_STEP_BMSK                                          0xffff
#define HWIO_TURING_QDSP6SS_VERSION_STEP_SHFT                                             0x0

#define HWIO_TURING_QDSP6SS_CONFIG_ID_ADDR                                         (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000004)
#define HWIO_TURING_QDSP6SS_CONFIG_ID_OFFS                                         (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000004)
#define HWIO_TURING_QDSP6SS_CONFIG_ID_RMSK                                         0xfff1ffff
#define HWIO_TURING_QDSP6SS_CONFIG_ID_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_CONFIG_ID_ADDR, HWIO_TURING_QDSP6SS_CONFIG_ID_RMSK)
#define HWIO_TURING_QDSP6SS_CONFIG_ID_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_CONFIG_ID_ADDR, m)
#define HWIO_TURING_QDSP6SS_CONFIG_ID_NUM_L2VIC_SRC_BMSK                           0xfff00000
#define HWIO_TURING_QDSP6SS_CONFIG_ID_NUM_L2VIC_SRC_SHFT                                 0x14
#define HWIO_TURING_QDSP6SS_CONFIG_ID_ZMEAS_PRESENT_BMSK                              0x10000
#define HWIO_TURING_QDSP6SS_CONFIG_ID_ZMEAS_PRESENT_SHFT                                 0x10
#define HWIO_TURING_QDSP6SS_CONFIG_ID_PMIC_IF_PRESENT_BMSK                             0x8000
#define HWIO_TURING_QDSP6SS_CONFIG_ID_PMIC_IF_PRESENT_SHFT                                0xf
#define HWIO_TURING_QDSP6SS_CONFIG_ID_IN_SUBSYSTEM_BMSK                                0x7000
#define HWIO_TURING_QDSP6SS_CONFIG_ID_IN_SUBSYSTEM_SHFT                                   0xc
#define HWIO_TURING_QDSP6SS_CONFIG_ID_LDO_PRESENT_BMSK                                  0x800
#define HWIO_TURING_QDSP6SS_CONFIG_ID_LDO_PRESENT_SHFT                                    0xb
#define HWIO_TURING_QDSP6SS_CONFIG_ID_BHS_PRESENT_BMSK                                  0x400
#define HWIO_TURING_QDSP6SS_CONFIG_ID_BHS_PRESENT_SHFT                                    0xa
#define HWIO_TURING_QDSP6SS_CONFIG_ID_PLL_VOTE_BMSK                                     0x200
#define HWIO_TURING_QDSP6SS_CONFIG_ID_PLL_VOTE_SHFT                                       0x9
#define HWIO_TURING_QDSP6SS_CONFIG_ID_PLL_PRESENT_BMSK                                  0x100
#define HWIO_TURING_QDSP6SS_CONFIG_ID_PLL_PRESENT_SHFT                                    0x8
#define HWIO_TURING_QDSP6SS_CONFIG_ID_CORE_TYPE_BMSK                                     0xf0
#define HWIO_TURING_QDSP6SS_CONFIG_ID_CORE_TYPE_SHFT                                      0x4
#define HWIO_TURING_QDSP6SS_CONFIG_ID_L2_SIZE_BMSK                                        0xf
#define HWIO_TURING_QDSP6SS_CONFIG_ID_L2_SIZE_SHFT                                        0x0

#define HWIO_TURING_QDSP6SS_RST_EVB_ADDR                                           (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000010)
#define HWIO_TURING_QDSP6SS_RST_EVB_OFFS                                           (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000010)
#define HWIO_TURING_QDSP6SS_RST_EVB_RMSK                                            0xffffff0
#define HWIO_TURING_QDSP6SS_RST_EVB_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_RST_EVB_ADDR, HWIO_TURING_QDSP6SS_RST_EVB_RMSK)
#define HWIO_TURING_QDSP6SS_RST_EVB_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_RST_EVB_ADDR, m)
#define HWIO_TURING_QDSP6SS_RST_EVB_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_RST_EVB_ADDR,v)
#define HWIO_TURING_QDSP6SS_RST_EVB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_RST_EVB_ADDR,m,v,HWIO_TURING_QDSP6SS_RST_EVB_IN)
#define HWIO_TURING_QDSP6SS_RST_EVB_EVB_BMSK                                        0xffffff0
#define HWIO_TURING_QDSP6SS_RST_EVB_EVB_SHFT                                              0x4

#define HWIO_TURING_QDSP6SS_RESET_ADDR                                             (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000014)
#define HWIO_TURING_QDSP6SS_RESET_OFFS                                             (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000014)
#define HWIO_TURING_QDSP6SS_RESET_RMSK                                                 0x7ff7
#define HWIO_TURING_QDSP6SS_RESET_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_RESET_ADDR, HWIO_TURING_QDSP6SS_RESET_RMSK)
#define HWIO_TURING_QDSP6SS_RESET_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_RESET_ADDR, m)
#define HWIO_TURING_QDSP6SS_RESET_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_RESET_ADDR,v)
#define HWIO_TURING_QDSP6SS_RESET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_RESET_ADDR,m,v,HWIO_TURING_QDSP6SS_RESET_IN)
#define HWIO_TURING_QDSP6SS_RESET_CSI1_ARES_BMSK                                       0x4000
#define HWIO_TURING_QDSP6SS_RESET_CSI1_ARES_SHFT                                          0xe
#define HWIO_TURING_QDSP6SS_RESET_CSI0_ARES_BMSK                                       0x2000
#define HWIO_TURING_QDSP6SS_RESET_CSI0_ARES_SHFT                                          0xd
#define HWIO_TURING_QDSP6SS_RESET_CORE_ARCH_ARES_BMSK                                  0x1000
#define HWIO_TURING_QDSP6SS_RESET_CORE_ARCH_ARES_SHFT                                     0xc
#define HWIO_TURING_QDSP6SS_RESET_CORE_NONRET_ARES_BMSK                                 0x800
#define HWIO_TURING_QDSP6SS_RESET_CORE_NONRET_ARES_SHFT                                   0xb
#define HWIO_TURING_QDSP6SS_RESET_CORE_RET_ARES_BMSK                                    0x400
#define HWIO_TURING_QDSP6SS_RESET_CORE_RET_ARES_SHFT                                      0xa
#define HWIO_TURING_QDSP6SS_RESET_AXIM2_ARES_BMSK                                       0x200
#define HWIO_TURING_QDSP6SS_RESET_AXIM2_ARES_SHFT                                         0x9
#define HWIO_TURING_QDSP6SS_RESET_AXIS_ARES_BMSK                                        0x100
#define HWIO_TURING_QDSP6SS_RESET_AXIS_ARES_SHFT                                          0x8
#define HWIO_TURING_QDSP6SS_RESET_ATBM_ARES_BMSK                                         0x80
#define HWIO_TURING_QDSP6SS_RESET_ATBM_ARES_SHFT                                          0x7
#define HWIO_TURING_QDSP6SS_RESET_AHBM_ARES_BMSK                                         0x40
#define HWIO_TURING_QDSP6SS_RESET_AHBM_ARES_SHFT                                          0x6
#define HWIO_TURING_QDSP6SS_RESET_AXIM_ARES_BMSK                                         0x20
#define HWIO_TURING_QDSP6SS_RESET_AXIM_ARES_SHFT                                          0x5
#define HWIO_TURING_QDSP6SS_RESET_ETM_ISDB_ARES_BMSK                                     0x10
#define HWIO_TURING_QDSP6SS_RESET_ETM_ISDB_ARES_SHFT                                      0x4
#define HWIO_TURING_QDSP6SS_RESET_BUS_ARES_ENA_BMSK                                       0x4
#define HWIO_TURING_QDSP6SS_RESET_BUS_ARES_ENA_SHFT                                       0x2
#define HWIO_TURING_QDSP6SS_RESET_CORE_ARES_BMSK                                          0x2
#define HWIO_TURING_QDSP6SS_RESET_CORE_ARES_SHFT                                          0x1
#define HWIO_TURING_QDSP6SS_RESET_STOP_CORE_BMSK                                          0x1
#define HWIO_TURING_QDSP6SS_RESET_STOP_CORE_SHFT                                          0x0

#define HWIO_TURING_QDSP6SS_DBG_CFG_ADDR                                           (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000018)
#define HWIO_TURING_QDSP6SS_DBG_CFG_OFFS                                           (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000018)
#define HWIO_TURING_QDSP6SS_DBG_CFG_RMSK                                           0xffff0003
#define HWIO_TURING_QDSP6SS_DBG_CFG_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_DBG_CFG_ADDR, HWIO_TURING_QDSP6SS_DBG_CFG_RMSK)
#define HWIO_TURING_QDSP6SS_DBG_CFG_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_DBG_CFG_ADDR, m)
#define HWIO_TURING_QDSP6SS_DBG_CFG_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_DBG_CFG_ADDR,v)
#define HWIO_TURING_QDSP6SS_DBG_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_DBG_CFG_ADDR,m,v,HWIO_TURING_QDSP6SS_DBG_CFG_IN)
#define HWIO_TURING_QDSP6SS_DBG_CFG_DBG_SW_REG_BMSK                                0xff000000
#define HWIO_TURING_QDSP6SS_DBG_CFG_DBG_SW_REG_SHFT                                      0x18
#define HWIO_TURING_QDSP6SS_DBG_CFG_DBG_SPARE_BMSK                                   0xff0000
#define HWIO_TURING_QDSP6SS_DBG_CFG_DBG_SPARE_SHFT                                       0x10
#define HWIO_TURING_QDSP6SS_DBG_CFG_CTI_TIHS_ENA_BMSK                                     0x2
#define HWIO_TURING_QDSP6SS_DBG_CFG_CTI_TIHS_ENA_SHFT                                     0x1
#define HWIO_TURING_QDSP6SS_DBG_CFG_DBG_ARES_ENA_BMSK                                     0x1
#define HWIO_TURING_QDSP6SS_DBG_CFG_DBG_ARES_ENA_SHFT                                     0x0

#define HWIO_TURING_QDSP6SS_RET_CFG_ADDR                                           (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x0000001c)
#define HWIO_TURING_QDSP6SS_RET_CFG_OFFS                                           (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000001c)
#define HWIO_TURING_QDSP6SS_RET_CFG_RMSK                                                  0x3
#define HWIO_TURING_QDSP6SS_RET_CFG_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_RET_CFG_ADDR, HWIO_TURING_QDSP6SS_RET_CFG_RMSK)
#define HWIO_TURING_QDSP6SS_RET_CFG_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_RET_CFG_ADDR, m)
#define HWIO_TURING_QDSP6SS_RET_CFG_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_RET_CFG_ADDR,v)
#define HWIO_TURING_QDSP6SS_RET_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_RET_CFG_ADDR,m,v,HWIO_TURING_QDSP6SS_RET_CFG_IN)
#define HWIO_TURING_QDSP6SS_RET_CFG_ARCH_ARES_ENA_BMSK                                    0x2
#define HWIO_TURING_QDSP6SS_RET_CFG_ARCH_ARES_ENA_SHFT                                    0x1
#define HWIO_TURING_QDSP6SS_RET_CFG_RET_ARES_ENA_BMSK                                     0x1
#define HWIO_TURING_QDSP6SS_RET_CFG_RET_ARES_ENA_SHFT                                     0x0

#define HWIO_TURING_QDSP6SS_GFMUX_CTL_ADDR                                         (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000020)
#define HWIO_TURING_QDSP6SS_GFMUX_CTL_OFFS                                         (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000020)
#define HWIO_TURING_QDSP6SS_GFMUX_CTL_RMSK                                              0x30f
#define HWIO_TURING_QDSP6SS_GFMUX_CTL_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_GFMUX_CTL_ADDR, HWIO_TURING_QDSP6SS_GFMUX_CTL_RMSK)
#define HWIO_TURING_QDSP6SS_GFMUX_CTL_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_GFMUX_CTL_ADDR, m)
#define HWIO_TURING_QDSP6SS_GFMUX_CTL_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_GFMUX_CTL_ADDR,v)
#define HWIO_TURING_QDSP6SS_GFMUX_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_GFMUX_CTL_ADDR,m,v,HWIO_TURING_QDSP6SS_GFMUX_CTL_IN)
#define HWIO_TURING_QDSP6SS_GFMUX_CTL_IDLE_CORE_CLK_EN_BMSK                             0x200
#define HWIO_TURING_QDSP6SS_GFMUX_CTL_IDLE_CORE_CLK_EN_SHFT                               0x9
#define HWIO_TURING_QDSP6SS_GFMUX_CTL_SRC_SWITCH_CLK_OVR_BMSK                           0x100
#define HWIO_TURING_QDSP6SS_GFMUX_CTL_SRC_SWITCH_CLK_OVR_SHFT                             0x8
#define HWIO_TURING_QDSP6SS_GFMUX_CTL_CLK_SRC_SEL_BMSK                                    0xc
#define HWIO_TURING_QDSP6SS_GFMUX_CTL_CLK_SRC_SEL_SHFT                                    0x2
#define HWIO_TURING_QDSP6SS_GFMUX_CTL_CLK_ENA_BMSK                                        0x2
#define HWIO_TURING_QDSP6SS_GFMUX_CTL_CLK_ENA_SHFT                                        0x1
#define HWIO_TURING_QDSP6SS_GFMUX_CTL_CLK_ARES_BMSK                                       0x1
#define HWIO_TURING_QDSP6SS_GFMUX_CTL_CLK_ARES_SHFT                                       0x0

#define HWIO_TURING_QDSP6SS_GFMUX_STATUS_ADDR                                      (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000024)
#define HWIO_TURING_QDSP6SS_GFMUX_STATUS_OFFS                                      (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000024)
#define HWIO_TURING_QDSP6SS_GFMUX_STATUS_RMSK                                            0x1f
#define HWIO_TURING_QDSP6SS_GFMUX_STATUS_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_GFMUX_STATUS_ADDR, HWIO_TURING_QDSP6SS_GFMUX_STATUS_RMSK)
#define HWIO_TURING_QDSP6SS_GFMUX_STATUS_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_GFMUX_STATUS_ADDR, m)
#define HWIO_TURING_QDSP6SS_GFMUX_STATUS_SEL_STATUS_BMSK                                 0x1e
#define HWIO_TURING_QDSP6SS_GFMUX_STATUS_SEL_STATUS_SHFT                                  0x1
#define HWIO_TURING_QDSP6SS_GFMUX_STATUS_SWITCH_STATUS_BMSK                               0x1
#define HWIO_TURING_QDSP6SS_GFMUX_STATUS_SWITCH_STATUS_SHFT                               0x0

#define HWIO_TURING_QDSP6SS_CORE_CMD_RCGR_ADDR                                     (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000028)
#define HWIO_TURING_QDSP6SS_CORE_CMD_RCGR_OFFS                                     (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000028)
#define HWIO_TURING_QDSP6SS_CORE_CMD_RCGR_RMSK                                     0x80000013
#define HWIO_TURING_QDSP6SS_CORE_CMD_RCGR_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_CORE_CMD_RCGR_ADDR, HWIO_TURING_QDSP6SS_CORE_CMD_RCGR_RMSK)
#define HWIO_TURING_QDSP6SS_CORE_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_CORE_CMD_RCGR_ADDR, m)
#define HWIO_TURING_QDSP6SS_CORE_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_CORE_CMD_RCGR_ADDR,v)
#define HWIO_TURING_QDSP6SS_CORE_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_CORE_CMD_RCGR_ADDR,m,v,HWIO_TURING_QDSP6SS_CORE_CMD_RCGR_IN)
#define HWIO_TURING_QDSP6SS_CORE_CMD_RCGR_ROOT_OFF_BMSK                            0x80000000
#define HWIO_TURING_QDSP6SS_CORE_CMD_RCGR_ROOT_OFF_SHFT                                  0x1f
#define HWIO_TURING_QDSP6SS_CORE_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                            0x10
#define HWIO_TURING_QDSP6SS_CORE_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                             0x4
#define HWIO_TURING_QDSP6SS_CORE_CMD_RCGR_ROOT_EN_BMSK                                    0x2
#define HWIO_TURING_QDSP6SS_CORE_CMD_RCGR_ROOT_EN_SHFT                                    0x1
#define HWIO_TURING_QDSP6SS_CORE_CMD_RCGR_UPDATE_BMSK                                     0x1
#define HWIO_TURING_QDSP6SS_CORE_CMD_RCGR_UPDATE_SHFT                                     0x0

#define HWIO_TURING_QDSP6SS_CORE_CFG_RCGR_ADDR                                     (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x0000002c)
#define HWIO_TURING_QDSP6SS_CORE_CFG_RCGR_OFFS                                     (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000002c)
#define HWIO_TURING_QDSP6SS_CORE_CFG_RCGR_RMSK                                        0x1071f
#define HWIO_TURING_QDSP6SS_CORE_CFG_RCGR_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_CORE_CFG_RCGR_ADDR, HWIO_TURING_QDSP6SS_CORE_CFG_RCGR_RMSK)
#define HWIO_TURING_QDSP6SS_CORE_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_CORE_CFG_RCGR_ADDR, m)
#define HWIO_TURING_QDSP6SS_CORE_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_CORE_CFG_RCGR_ADDR,v)
#define HWIO_TURING_QDSP6SS_CORE_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_CORE_CFG_RCGR_ADDR,m,v,HWIO_TURING_QDSP6SS_CORE_CFG_RCGR_IN)
#define HWIO_TURING_QDSP6SS_CORE_CFG_RCGR_RCGLITE_DISABLE_BMSK                        0x10000
#define HWIO_TURING_QDSP6SS_CORE_CFG_RCGR_RCGLITE_DISABLE_SHFT                           0x10
#define HWIO_TURING_QDSP6SS_CORE_CFG_RCGR_SRC_SEL_BMSK                                  0x700
#define HWIO_TURING_QDSP6SS_CORE_CFG_RCGR_SRC_SEL_SHFT                                    0x8
#define HWIO_TURING_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_BMSK                                   0x1f
#define HWIO_TURING_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_SHFT                                    0x0

#define HWIO_TURING_QDSP6SS_PWR_CTL_ADDR                                           (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000030)
#define HWIO_TURING_QDSP6SS_PWR_CTL_OFFS                                           (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000030)
#define HWIO_TURING_QDSP6SS_PWR_CTL_RMSK                                            0xf7c0000
#define HWIO_TURING_QDSP6SS_PWR_CTL_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_PWR_CTL_ADDR, HWIO_TURING_QDSP6SS_PWR_CTL_RMSK)
#define HWIO_TURING_QDSP6SS_PWR_CTL_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_PWR_CTL_ADDR, m)
#define HWIO_TURING_QDSP6SS_PWR_CTL_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_PWR_CTL_ADDR,v)
#define HWIO_TURING_QDSP6SS_PWR_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_PWR_CTL_ADDR,m,v,HWIO_TURING_QDSP6SS_PWR_CTL_IN)
#define HWIO_TURING_QDSP6SS_PWR_CTL_LDO_PWR_UP_BG_BMSK                              0x8000000
#define HWIO_TURING_QDSP6SS_PWR_CTL_LDO_PWR_UP_BG_SHFT                                   0x1b
#define HWIO_TURING_QDSP6SS_PWR_CTL_LDO_PWR_UP_BMSK                                 0x4000000
#define HWIO_TURING_QDSP6SS_PWR_CTL_LDO_PWR_UP_SHFT                                      0x1a
#define HWIO_TURING_QDSP6SS_PWR_CTL_LDO_BYP_BMSK                                    0x2000000
#define HWIO_TURING_QDSP6SS_PWR_CTL_LDO_BYP_SHFT                                         0x19
#define HWIO_TURING_QDSP6SS_PWR_CTL_BHS_ON_BMSK                                     0x1000000
#define HWIO_TURING_QDSP6SS_PWR_CTL_BHS_ON_SHFT                                          0x18
#define HWIO_TURING_QDSP6SS_PWR_CTL_CLAMP_QMC_MEM_BMSK                               0x400000
#define HWIO_TURING_QDSP6SS_PWR_CTL_CLAMP_QMC_MEM_SHFT                                   0x16
#define HWIO_TURING_QDSP6SS_PWR_CTL_CLAMP_WL_BMSK                                    0x200000
#define HWIO_TURING_QDSP6SS_PWR_CTL_CLAMP_WL_SHFT                                        0x15
#define HWIO_TURING_QDSP6SS_PWR_CTL_CLAMP_IO_BMSK                                    0x100000
#define HWIO_TURING_QDSP6SS_PWR_CTL_CLAMP_IO_SHFT                                        0x14
#define HWIO_TURING_QDSP6SS_PWR_CTL_SLP_RET_N_BMSK                                    0x80000
#define HWIO_TURING_QDSP6SS_PWR_CTL_SLP_RET_N_SHFT                                       0x13
#define HWIO_TURING_QDSP6SS_PWR_CTL_ARR_STBY_N_BMSK                                   0x40000
#define HWIO_TURING_QDSP6SS_PWR_CTL_ARR_STBY_N_SHFT                                      0x12

#define HWIO_TURING_QDSP6SS_MEM_PWR_CTL_ADDR                                       (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000034)
#define HWIO_TURING_QDSP6SS_MEM_PWR_CTL_OFFS                                       (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000034)
#define HWIO_TURING_QDSP6SS_MEM_PWR_CTL_RMSK                                       0x3fffffff
#define HWIO_TURING_QDSP6SS_MEM_PWR_CTL_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_MEM_PWR_CTL_ADDR, HWIO_TURING_QDSP6SS_MEM_PWR_CTL_RMSK)
#define HWIO_TURING_QDSP6SS_MEM_PWR_CTL_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_MEM_PWR_CTL_ADDR, m)
#define HWIO_TURING_QDSP6SS_MEM_PWR_CTL_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_MEM_PWR_CTL_ADDR,v)
#define HWIO_TURING_QDSP6SS_MEM_PWR_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_MEM_PWR_CTL_ADDR,m,v,HWIO_TURING_QDSP6SS_MEM_PWR_CTL_IN)
#define HWIO_TURING_QDSP6SS_MEM_PWR_CTL_L2PLRU_SLP_NRET_N_BMSK                     0x20000000
#define HWIO_TURING_QDSP6SS_MEM_PWR_CTL_L2PLRU_SLP_NRET_N_SHFT                           0x1d
#define HWIO_TURING_QDSP6SS_MEM_PWR_CTL_ETB_SLP_NRET_N_BMSK                        0x10000000
#define HWIO_TURING_QDSP6SS_MEM_PWR_CTL_ETB_SLP_NRET_N_SHFT                              0x1c
#define HWIO_TURING_QDSP6SS_MEM_PWR_CTL_L1IU_SLP_NRET_N_BMSK                        0xc000000
#define HWIO_TURING_QDSP6SS_MEM_PWR_CTL_L1IU_SLP_NRET_N_SHFT                             0x1a
#define HWIO_TURING_QDSP6SS_MEM_PWR_CTL_L1DU_SLP_NRET_N_BMSK                        0x3000000
#define HWIO_TURING_QDSP6SS_MEM_PWR_CTL_L1DU_SLP_NRET_N_SHFT                             0x18
#define HWIO_TURING_QDSP6SS_MEM_PWR_CTL_JU_SLP_NRET_N_BMSK                           0xe00000
#define HWIO_TURING_QDSP6SS_MEM_PWR_CTL_JU_SLP_NRET_N_SHFT                               0x15
#define HWIO_TURING_QDSP6SS_MEM_PWR_CTL_L2CLADE_SLP_NRET_N_BMSK                      0x100000
#define HWIO_TURING_QDSP6SS_MEM_PWR_CTL_L2CLADE_SLP_NRET_N_SHFT                          0x14
#define HWIO_TURING_QDSP6SS_MEM_PWR_CTL_L2TAG_SLP_NRET_N_BMSK                         0xf0000
#define HWIO_TURING_QDSP6SS_MEM_PWR_CTL_L2TAG_SLP_NRET_N_SHFT                            0x10
#define HWIO_TURING_QDSP6SS_MEM_PWR_CTL_L2DATA_SLP_NRET_N_BMSK                         0xffff
#define HWIO_TURING_QDSP6SS_MEM_PWR_CTL_L2DATA_SLP_NRET_N_SHFT                            0x0

#define HWIO_TURING_QDSP6SS_XO_CBCR_ADDR                                           (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000038)
#define HWIO_TURING_QDSP6SS_XO_CBCR_OFFS                                           (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000038)
#define HWIO_TURING_QDSP6SS_XO_CBCR_RMSK                                           0x80000001
#define HWIO_TURING_QDSP6SS_XO_CBCR_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_XO_CBCR_ADDR, HWIO_TURING_QDSP6SS_XO_CBCR_RMSK)
#define HWIO_TURING_QDSP6SS_XO_CBCR_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_XO_CBCR_ADDR, m)
#define HWIO_TURING_QDSP6SS_XO_CBCR_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_XO_CBCR_ADDR,v)
#define HWIO_TURING_QDSP6SS_XO_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_XO_CBCR_ADDR,m,v,HWIO_TURING_QDSP6SS_XO_CBCR_IN)
#define HWIO_TURING_QDSP6SS_XO_CBCR_CLKOFF_BMSK                                    0x80000000
#define HWIO_TURING_QDSP6SS_XO_CBCR_CLKOFF_SHFT                                          0x1f
#define HWIO_TURING_QDSP6SS_XO_CBCR_CLKEN_BMSK                                            0x1
#define HWIO_TURING_QDSP6SS_XO_CBCR_CLKEN_SHFT                                            0x0

#define HWIO_TURING_QDSP6SS_SLEEP_CBCR_ADDR                                        (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x0000003c)
#define HWIO_TURING_QDSP6SS_SLEEP_CBCR_OFFS                                        (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000003c)
#define HWIO_TURING_QDSP6SS_SLEEP_CBCR_RMSK                                        0x80000001
#define HWIO_TURING_QDSP6SS_SLEEP_CBCR_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_SLEEP_CBCR_ADDR, HWIO_TURING_QDSP6SS_SLEEP_CBCR_RMSK)
#define HWIO_TURING_QDSP6SS_SLEEP_CBCR_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_SLEEP_CBCR_ADDR, m)
#define HWIO_TURING_QDSP6SS_SLEEP_CBCR_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_SLEEP_CBCR_ADDR,v)
#define HWIO_TURING_QDSP6SS_SLEEP_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_SLEEP_CBCR_ADDR,m,v,HWIO_TURING_QDSP6SS_SLEEP_CBCR_IN)
#define HWIO_TURING_QDSP6SS_SLEEP_CBCR_CLKOFF_BMSK                                 0x80000000
#define HWIO_TURING_QDSP6SS_SLEEP_CBCR_CLKOFF_SHFT                                       0x1f
#define HWIO_TURING_QDSP6SS_SLEEP_CBCR_CLKEN_BMSK                                         0x1
#define HWIO_TURING_QDSP6SS_SLEEP_CBCR_CLKEN_SHFT                                         0x0

#define HWIO_TURING_QDSP6SS_NMI_ADDR                                               (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000040)
#define HWIO_TURING_QDSP6SS_NMI_OFFS                                               (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000040)
#define HWIO_TURING_QDSP6SS_NMI_RMSK                                                      0x3
#define HWIO_TURING_QDSP6SS_NMI_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_NMI_ADDR,v)
#define HWIO_TURING_QDSP6SS_NMI_CLEAR_STATUS_BMSK                                         0x2
#define HWIO_TURING_QDSP6SS_NMI_CLEAR_STATUS_SHFT                                         0x1
#define HWIO_TURING_QDSP6SS_NMI_SET_NMI_BMSK                                              0x1
#define HWIO_TURING_QDSP6SS_NMI_SET_NMI_SHFT                                              0x0

#define HWIO_TURING_QDSP6SS_NMI_STATUS_ADDR                                        (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000044)
#define HWIO_TURING_QDSP6SS_NMI_STATUS_OFFS                                        (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000044)
#define HWIO_TURING_QDSP6SS_NMI_STATUS_RMSK                                               0x7
#define HWIO_TURING_QDSP6SS_NMI_STATUS_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_NMI_STATUS_ADDR, HWIO_TURING_QDSP6SS_NMI_STATUS_RMSK)
#define HWIO_TURING_QDSP6SS_NMI_STATUS_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_NMI_STATUS_ADDR, m)
#define HWIO_TURING_QDSP6SS_NMI_STATUS_EXT_DBG_TRIG_BMSK                                  0x4
#define HWIO_TURING_QDSP6SS_NMI_STATUS_EXT_DBG_TRIG_SHFT                                  0x2
#define HWIO_TURING_QDSP6SS_NMI_STATUS_WDOG_TRIG_BMSK                                     0x2
#define HWIO_TURING_QDSP6SS_NMI_STATUS_WDOG_TRIG_SHFT                                     0x1
#define HWIO_TURING_QDSP6SS_NMI_STATUS_PUBCSR_TRIG_BMSK                                   0x1
#define HWIO_TURING_QDSP6SS_NMI_STATUS_PUBCSR_TRIG_SHFT                                   0x0

#define HWIO_TURING_QDSP6SS_CLOCK_SPDM_MON_ADDR                                    (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000048)
#define HWIO_TURING_QDSP6SS_CLOCK_SPDM_MON_OFFS                                    (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000048)
#define HWIO_TURING_QDSP6SS_CLOCK_SPDM_MON_RMSK                                           0x1
#define HWIO_TURING_QDSP6SS_CLOCK_SPDM_MON_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_CLOCK_SPDM_MON_ADDR, HWIO_TURING_QDSP6SS_CLOCK_SPDM_MON_RMSK)
#define HWIO_TURING_QDSP6SS_CLOCK_SPDM_MON_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_CLOCK_SPDM_MON_ADDR, m)
#define HWIO_TURING_QDSP6SS_CLOCK_SPDM_MON_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_CLOCK_SPDM_MON_ADDR,v)
#define HWIO_TURING_QDSP6SS_CLOCK_SPDM_MON_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_CLOCK_SPDM_MON_ADDR,m,v,HWIO_TURING_QDSP6SS_CLOCK_SPDM_MON_IN)
#define HWIO_TURING_QDSP6SS_CLOCK_SPDM_MON_Q6_MON_CLKEN_BMSK                              0x1
#define HWIO_TURING_QDSP6SS_CLOCK_SPDM_MON_Q6_MON_CLKEN_SHFT                              0x0

#define HWIO_TURING_QDSP6SS_STATERET_CTL_ADDR                                      (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x0000004c)
#define HWIO_TURING_QDSP6SS_STATERET_CTL_OFFS                                      (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000004c)
#define HWIO_TURING_QDSP6SS_STATERET_CTL_RMSK                                             0xf
#define HWIO_TURING_QDSP6SS_STATERET_CTL_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_STATERET_CTL_ADDR, HWIO_TURING_QDSP6SS_STATERET_CTL_RMSK)
#define HWIO_TURING_QDSP6SS_STATERET_CTL_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_STATERET_CTL_ADDR, m)
#define HWIO_TURING_QDSP6SS_STATERET_CTL_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_STATERET_CTL_ADDR,v)
#define HWIO_TURING_QDSP6SS_STATERET_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_STATERET_CTL_ADDR,m,v,HWIO_TURING_QDSP6SS_STATERET_CTL_IN)
#define HWIO_TURING_QDSP6SS_STATERET_CTL_WAKEUP_IN_BMSK                                   0x8
#define HWIO_TURING_QDSP6SS_STATERET_CTL_WAKEUP_IN_SHFT                                   0x3
#define HWIO_TURING_QDSP6SS_STATERET_CTL_WAKE_IRQ_BMSK                                    0x4
#define HWIO_TURING_QDSP6SS_STATERET_CTL_WAKE_IRQ_SHFT                                    0x2
#define HWIO_TURING_QDSP6SS_STATERET_CTL_RESTORE_BMSK                                     0x2
#define HWIO_TURING_QDSP6SS_STATERET_CTL_RESTORE_SHFT                                     0x1
#define HWIO_TURING_QDSP6SS_STATERET_CTL_SAVE_BMSK                                        0x1
#define HWIO_TURING_QDSP6SS_STATERET_CTL_SAVE_SHFT                                        0x0

#define HWIO_TURING_QDSP6SS_SPM_SW_TRIG_ADDR                                       (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000080)
#define HWIO_TURING_QDSP6SS_SPM_SW_TRIG_OFFS                                       (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000080)
#define HWIO_TURING_QDSP6SS_SPM_SW_TRIG_RMSK                                              0xf
#define HWIO_TURING_QDSP6SS_SPM_SW_TRIG_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_SPM_SW_TRIG_ADDR,v)
#define HWIO_TURING_QDSP6SS_SPM_SW_TRIG_CMD_BMSK                                          0xf
#define HWIO_TURING_QDSP6SS_SPM_SW_TRIG_CMD_SHFT                                          0x0

#define HWIO_TURING_QDSP6SS_SPM_TRIG_STATUS_ADDR                                   (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000084)
#define HWIO_TURING_QDSP6SS_SPM_TRIG_STATUS_OFFS                                   (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000084)
#define HWIO_TURING_QDSP6SS_SPM_TRIG_STATUS_RMSK                                          0xf
#define HWIO_TURING_QDSP6SS_SPM_TRIG_STATUS_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_SPM_TRIG_STATUS_ADDR, HWIO_TURING_QDSP6SS_SPM_TRIG_STATUS_RMSK)
#define HWIO_TURING_QDSP6SS_SPM_TRIG_STATUS_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_SPM_TRIG_STATUS_ADDR, m)
#define HWIO_TURING_QDSP6SS_SPM_TRIG_STATUS_BUSY_BMSK                                     0xf
#define HWIO_TURING_QDSP6SS_SPM_TRIG_STATUS_BUSY_SHFT                                     0x0

#define HWIO_TURING_QDSP6SS_INTF_HALTREQ_ADDR                                      (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000088)
#define HWIO_TURING_QDSP6SS_INTF_HALTREQ_OFFS                                      (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000088)
#define HWIO_TURING_QDSP6SS_INTF_HALTREQ_RMSK                                             0x7
#define HWIO_TURING_QDSP6SS_INTF_HALTREQ_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_INTF_HALTREQ_ADDR, HWIO_TURING_QDSP6SS_INTF_HALTREQ_RMSK)
#define HWIO_TURING_QDSP6SS_INTF_HALTREQ_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_INTF_HALTREQ_ADDR, m)
#define HWIO_TURING_QDSP6SS_INTF_HALTREQ_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_INTF_HALTREQ_ADDR,v)
#define HWIO_TURING_QDSP6SS_INTF_HALTREQ_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_INTF_HALTREQ_ADDR,m,v,HWIO_TURING_QDSP6SS_INTF_HALTREQ_IN)
#define HWIO_TURING_QDSP6SS_INTF_HALTREQ_AXIM2_BMSK                                       0x4
#define HWIO_TURING_QDSP6SS_INTF_HALTREQ_AXIM2_SHFT                                       0x2
#define HWIO_TURING_QDSP6SS_INTF_HALTREQ_AXIM_BMSK                                        0x2
#define HWIO_TURING_QDSP6SS_INTF_HALTREQ_AXIM_SHFT                                        0x1
#define HWIO_TURING_QDSP6SS_INTF_HALTREQ_ALL_BMSK                                         0x1
#define HWIO_TURING_QDSP6SS_INTF_HALTREQ_ALL_SHFT                                         0x0

#define HWIO_TURING_QDSP6SS_INTF_HALTACK_ADDR                                      (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x0000008c)
#define HWIO_TURING_QDSP6SS_INTF_HALTACK_OFFS                                      (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000008c)
#define HWIO_TURING_QDSP6SS_INTF_HALTACK_RMSK                                             0x7
#define HWIO_TURING_QDSP6SS_INTF_HALTACK_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_INTF_HALTACK_ADDR, HWIO_TURING_QDSP6SS_INTF_HALTACK_RMSK)
#define HWIO_TURING_QDSP6SS_INTF_HALTACK_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_INTF_HALTACK_ADDR, m)
#define HWIO_TURING_QDSP6SS_INTF_HALTACK_AXIM2_BMSK                                       0x4
#define HWIO_TURING_QDSP6SS_INTF_HALTACK_AXIM2_SHFT                                       0x2
#define HWIO_TURING_QDSP6SS_INTF_HALTACK_AXIM_BMSK                                        0x2
#define HWIO_TURING_QDSP6SS_INTF_HALTACK_AXIM_SHFT                                        0x1
#define HWIO_TURING_QDSP6SS_INTF_HALTACK_ALL_BMSK                                         0x1
#define HWIO_TURING_QDSP6SS_INTF_HALTACK_ALL_SHFT                                         0x0

#define HWIO_TURING_QDSP6SS_INTFCLAMP_SET_ADDR                                     (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000090)
#define HWIO_TURING_QDSP6SS_INTFCLAMP_SET_OFFS                                     (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000090)
#define HWIO_TURING_QDSP6SS_INTFCLAMP_SET_RMSK                                            0xf
#define HWIO_TURING_QDSP6SS_INTFCLAMP_SET_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_INTFCLAMP_SET_ADDR,v)
#define HWIO_TURING_QDSP6SS_INTFCLAMP_SET_AXIM2_CLAMP_E_BMSK                              0x8
#define HWIO_TURING_QDSP6SS_INTFCLAMP_SET_AXIM2_CLAMP_E_SHFT                              0x3
#define HWIO_TURING_QDSP6SS_INTFCLAMP_SET_AXIM2_CLAMP_L_BMSK                              0x4
#define HWIO_TURING_QDSP6SS_INTFCLAMP_SET_AXIM2_CLAMP_L_SHFT                              0x2
#define HWIO_TURING_QDSP6SS_INTFCLAMP_SET_AXIM_CLAMP_E_BMSK                               0x2
#define HWIO_TURING_QDSP6SS_INTFCLAMP_SET_AXIM_CLAMP_E_SHFT                               0x1
#define HWIO_TURING_QDSP6SS_INTFCLAMP_SET_AXIM_CLAMP_L_BMSK                               0x1
#define HWIO_TURING_QDSP6SS_INTFCLAMP_SET_AXIM_CLAMP_L_SHFT                               0x0

#define HWIO_TURING_QDSP6SS_INTFCLAMP_CLEAR_ADDR                                   (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000094)
#define HWIO_TURING_QDSP6SS_INTFCLAMP_CLEAR_OFFS                                   (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000094)
#define HWIO_TURING_QDSP6SS_INTFCLAMP_CLEAR_RMSK                                          0xf
#define HWIO_TURING_QDSP6SS_INTFCLAMP_CLEAR_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_INTFCLAMP_CLEAR_ADDR,v)
#define HWIO_TURING_QDSP6SS_INTFCLAMP_CLEAR_AXIM2_CLAMP_E_BMSK                            0x8
#define HWIO_TURING_QDSP6SS_INTFCLAMP_CLEAR_AXIM2_CLAMP_E_SHFT                            0x3
#define HWIO_TURING_QDSP6SS_INTFCLAMP_CLEAR_AXIM2_CLAMP_L_BMSK                            0x4
#define HWIO_TURING_QDSP6SS_INTFCLAMP_CLEAR_AXIM2_CLAMP_L_SHFT                            0x2
#define HWIO_TURING_QDSP6SS_INTFCLAMP_CLEAR_AXIM_CLAMP_E_BMSK                             0x2
#define HWIO_TURING_QDSP6SS_INTFCLAMP_CLEAR_AXIM_CLAMP_E_SHFT                             0x1
#define HWIO_TURING_QDSP6SS_INTFCLAMP_CLEAR_AXIM_CLAMP_L_BMSK                             0x1
#define HWIO_TURING_QDSP6SS_INTFCLAMP_CLEAR_AXIM_CLAMP_L_SHFT                             0x0

#define HWIO_TURING_QDSP6SS_INTFCLAMP_STATUS_ADDR                                  (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000098)
#define HWIO_TURING_QDSP6SS_INTFCLAMP_STATUS_OFFS                                  (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000098)
#define HWIO_TURING_QDSP6SS_INTFCLAMP_STATUS_RMSK                                         0xf
#define HWIO_TURING_QDSP6SS_INTFCLAMP_STATUS_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_INTFCLAMP_STATUS_ADDR, HWIO_TURING_QDSP6SS_INTFCLAMP_STATUS_RMSK)
#define HWIO_TURING_QDSP6SS_INTFCLAMP_STATUS_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_INTFCLAMP_STATUS_ADDR, m)
#define HWIO_TURING_QDSP6SS_INTFCLAMP_STATUS_AXIM2_CLAMP_E_BMSK                           0x8
#define HWIO_TURING_QDSP6SS_INTFCLAMP_STATUS_AXIM2_CLAMP_E_SHFT                           0x3
#define HWIO_TURING_QDSP6SS_INTFCLAMP_STATUS_AXIM2_CLAMP_L_BMSK                           0x4
#define HWIO_TURING_QDSP6SS_INTFCLAMP_STATUS_AXIM2_CLAMP_L_SHFT                           0x2
#define HWIO_TURING_QDSP6SS_INTFCLAMP_STATUS_AXIM_CLAMP_E_BMSK                            0x2
#define HWIO_TURING_QDSP6SS_INTFCLAMP_STATUS_AXIM_CLAMP_E_SHFT                            0x1
#define HWIO_TURING_QDSP6SS_INTFCLAMP_STATUS_AXIM_CLAMP_L_BMSK                            0x1
#define HWIO_TURING_QDSP6SS_INTFCLAMP_STATUS_AXIM_CLAMP_L_SHFT                            0x0

#define HWIO_TURING_QDSP6SS_INTF_FIFO_RESET_ADDR                                   (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x0000009c)
#define HWIO_TURING_QDSP6SS_INTF_FIFO_RESET_OFFS                                   (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000009c)
#define HWIO_TURING_QDSP6SS_INTF_FIFO_RESET_RMSK                                          0x3
#define HWIO_TURING_QDSP6SS_INTF_FIFO_RESET_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_INTF_FIFO_RESET_ADDR, HWIO_TURING_QDSP6SS_INTF_FIFO_RESET_RMSK)
#define HWIO_TURING_QDSP6SS_INTF_FIFO_RESET_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_INTF_FIFO_RESET_ADDR, m)
#define HWIO_TURING_QDSP6SS_INTF_FIFO_RESET_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_INTF_FIFO_RESET_ADDR,v)
#define HWIO_TURING_QDSP6SS_INTF_FIFO_RESET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_INTF_FIFO_RESET_ADDR,m,v,HWIO_TURING_QDSP6SS_INTF_FIFO_RESET_IN)
#define HWIO_TURING_QDSP6SS_INTF_FIFO_RESET_AXIM2_BMSK                                    0x2
#define HWIO_TURING_QDSP6SS_INTF_FIFO_RESET_AXIM2_SHFT                                    0x1
#define HWIO_TURING_QDSP6SS_INTF_FIFO_RESET_AXIM_BMSK                                     0x1
#define HWIO_TURING_QDSP6SS_INTF_FIFO_RESET_AXIM_SHFT                                     0x0

#define HWIO_TURING_QDSP6SS_CP_BHS_CTL_ADDR                                        (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x000000ac)
#define HWIO_TURING_QDSP6SS_CP_BHS_CTL_OFFS                                        (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x000000ac)
#define HWIO_TURING_QDSP6SS_CP_BHS_CTL_RMSK                                               0xf
#define HWIO_TURING_QDSP6SS_CP_BHS_CTL_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_CP_BHS_CTL_ADDR, HWIO_TURING_QDSP6SS_CP_BHS_CTL_RMSK)
#define HWIO_TURING_QDSP6SS_CP_BHS_CTL_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_CP_BHS_CTL_ADDR, m)
#define HWIO_TURING_QDSP6SS_CP_BHS_CTL_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_CP_BHS_CTL_ADDR,v)
#define HWIO_TURING_QDSP6SS_CP_BHS_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_CP_BHS_CTL_ADDR,m,v,HWIO_TURING_QDSP6SS_CP_BHS_CTL_IN)
#define HWIO_TURING_QDSP6SS_CP_BHS_CTL_DRIVE_SEL_BMSK                                     0xf
#define HWIO_TURING_QDSP6SS_CP_BHS_CTL_DRIVE_SEL_SHFT                                     0x0

#define HWIO_TURING_QDSP6SS_CGC_OVERRIDE_ADDR                                      (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x000000b0)
#define HWIO_TURING_QDSP6SS_CGC_OVERRIDE_OFFS                                      (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x000000b0)
#define HWIO_TURING_QDSP6SS_CGC_OVERRIDE_RMSK                                          0xaf7f
#define HWIO_TURING_QDSP6SS_CGC_OVERRIDE_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_CGC_OVERRIDE_ADDR, HWIO_TURING_QDSP6SS_CGC_OVERRIDE_RMSK)
#define HWIO_TURING_QDSP6SS_CGC_OVERRIDE_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_CGC_OVERRIDE_ADDR, m)
#define HWIO_TURING_QDSP6SS_CGC_OVERRIDE_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_CGC_OVERRIDE_ADDR,v)
#define HWIO_TURING_QDSP6SS_CGC_OVERRIDE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_CGC_OVERRIDE_ADDR,m,v,HWIO_TURING_QDSP6SS_CGC_OVERRIDE_IN)
#define HWIO_TURING_QDSP6SS_CGC_OVERRIDE_CP0_CLK_EN_BMSK                               0x8000
#define HWIO_TURING_QDSP6SS_CGC_OVERRIDE_CP0_CLK_EN_SHFT                                  0xf
#define HWIO_TURING_QDSP6SS_CGC_OVERRIDE_AXIS_CLK_EN_BMSK                              0x2000
#define HWIO_TURING_QDSP6SS_CGC_OVERRIDE_AXIS_CLK_EN_SHFT                                 0xd
#define HWIO_TURING_QDSP6SS_CGC_OVERRIDE_AHBM_CLK_EN_BMSK                               0x800
#define HWIO_TURING_QDSP6SS_CGC_OVERRIDE_AHBM_CLK_EN_SHFT                                 0xb
#define HWIO_TURING_QDSP6SS_CGC_OVERRIDE_AHBS_CLK_EN_BMSK                               0x400
#define HWIO_TURING_QDSP6SS_CGC_OVERRIDE_AHBS_CLK_EN_SHFT                                 0xa
#define HWIO_TURING_QDSP6SS_CGC_OVERRIDE_PRIV_AHBS_CLK_EN_BMSK                          0x300
#define HWIO_TURING_QDSP6SS_CGC_OVERRIDE_PRIV_AHBS_CLK_EN_SHFT                            0x8
#define HWIO_TURING_QDSP6SS_CGC_OVERRIDE_L2VIC_AHBS_CLK_EN_BMSK                          0x60
#define HWIO_TURING_QDSP6SS_CGC_OVERRIDE_L2VIC_AHBS_CLK_EN_SHFT                           0x5
#define HWIO_TURING_QDSP6SS_CGC_OVERRIDE_TEST_AHBS_CLK_EN_BMSK                           0x10
#define HWIO_TURING_QDSP6SS_CGC_OVERRIDE_TEST_AHBS_CLK_EN_SHFT                            0x4
#define HWIO_TURING_QDSP6SS_CGC_OVERRIDE_PUB_AHBS_CLK_EN_BMSK                             0x8
#define HWIO_TURING_QDSP6SS_CGC_OVERRIDE_PUB_AHBS_CLK_EN_SHFT                             0x3
#define HWIO_TURING_QDSP6SS_CGC_OVERRIDE_CORE_BUS_EN_BMSK                                 0x4
#define HWIO_TURING_QDSP6SS_CGC_OVERRIDE_CORE_BUS_EN_SHFT                                 0x2
#define HWIO_TURING_QDSP6SS_CGC_OVERRIDE_CORE_RCLK_EN_BMSK                                0x2
#define HWIO_TURING_QDSP6SS_CGC_OVERRIDE_CORE_RCLK_EN_SHFT                                0x1
#define HWIO_TURING_QDSP6SS_CGC_OVERRIDE_CORE_CLK_EN_BMSK                                 0x1
#define HWIO_TURING_QDSP6SS_CGC_OVERRIDE_CORE_CLK_EN_SHFT                                 0x0

#define HWIO_TURING_QDSP6SS_L1S_PWR_CTL_ADDR                                       (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x000000b4)
#define HWIO_TURING_QDSP6SS_L1S_PWR_CTL_OFFS                                       (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x000000b4)
#define HWIO_TURING_QDSP6SS_L1S_PWR_CTL_RMSK                                             0xff
#define HWIO_TURING_QDSP6SS_L1S_PWR_CTL_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_L1S_PWR_CTL_ADDR, HWIO_TURING_QDSP6SS_L1S_PWR_CTL_RMSK)
#define HWIO_TURING_QDSP6SS_L1S_PWR_CTL_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_L1S_PWR_CTL_ADDR, m)
#define HWIO_TURING_QDSP6SS_L1S_PWR_CTL_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_L1S_PWR_CTL_ADDR,v)
#define HWIO_TURING_QDSP6SS_L1S_PWR_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_L1S_PWR_CTL_ADDR,m,v,HWIO_TURING_QDSP6SS_L1S_PWR_CTL_IN)
#define HWIO_TURING_QDSP6SS_L1S_PWR_CTL_SLP_NRET_N_BMSK                                  0xff
#define HWIO_TURING_QDSP6SS_L1S_PWR_CTL_SLP_NRET_N_SHFT                                   0x0

#define HWIO_TURING_QDSP6SS_CORE_BHS_CTL_ADDR                                      (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x000000c0)
#define HWIO_TURING_QDSP6SS_CORE_BHS_CTL_OFFS                                      (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x000000c0)
#define HWIO_TURING_QDSP6SS_CORE_BHS_CTL_RMSK                                             0xf
#define HWIO_TURING_QDSP6SS_CORE_BHS_CTL_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_CORE_BHS_CTL_ADDR, HWIO_TURING_QDSP6SS_CORE_BHS_CTL_RMSK)
#define HWIO_TURING_QDSP6SS_CORE_BHS_CTL_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_CORE_BHS_CTL_ADDR, m)
#define HWIO_TURING_QDSP6SS_CORE_BHS_CTL_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_CORE_BHS_CTL_ADDR,v)
#define HWIO_TURING_QDSP6SS_CORE_BHS_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_CORE_BHS_CTL_ADDR,m,v,HWIO_TURING_QDSP6SS_CORE_BHS_CTL_IN)
#define HWIO_TURING_QDSP6SS_CORE_BHS_CTL_DRIVE_SEL_BMSK                                   0xf
#define HWIO_TURING_QDSP6SS_CORE_BHS_CTL_DRIVE_SEL_SHFT                                   0x0

#define HWIO_TURING_QDSP6SS_BHS_STATUS_ADDR                                        (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x000000c4)
#define HWIO_TURING_QDSP6SS_BHS_STATUS_OFFS                                        (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x000000c4)
#define HWIO_TURING_QDSP6SS_BHS_STATUS_RMSK                                               0x1
#define HWIO_TURING_QDSP6SS_BHS_STATUS_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_BHS_STATUS_ADDR, HWIO_TURING_QDSP6SS_BHS_STATUS_RMSK)
#define HWIO_TURING_QDSP6SS_BHS_STATUS_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_BHS_STATUS_ADDR, m)
#define HWIO_TURING_QDSP6SS_BHS_STATUS_BHS_EN_REST_ACK_BMSK                               0x1
#define HWIO_TURING_QDSP6SS_BHS_STATUS_BHS_EN_REST_ACK_SHFT                               0x0

#define HWIO_TURING_QDSP6SS_QMC_SVS_CTL_ADDR                                       (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x000000c8)
#define HWIO_TURING_QDSP6SS_QMC_SVS_CTL_OFFS                                       (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x000000c8)
#define HWIO_TURING_QDSP6SS_QMC_SVS_CTL_RMSK                                              0x3
#define HWIO_TURING_QDSP6SS_QMC_SVS_CTL_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_QMC_SVS_CTL_ADDR, HWIO_TURING_QDSP6SS_QMC_SVS_CTL_RMSK)
#define HWIO_TURING_QDSP6SS_QMC_SVS_CTL_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_QMC_SVS_CTL_ADDR, m)
#define HWIO_TURING_QDSP6SS_QMC_SVS_CTL_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_QMC_SVS_CTL_ADDR,v)
#define HWIO_TURING_QDSP6SS_QMC_SVS_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_QMC_SVS_CTL_ADDR,m,v,HWIO_TURING_QDSP6SS_QMC_SVS_CTL_IN)
#define HWIO_TURING_QDSP6SS_QMC_SVS_CTL_QMC_MEM_SVS_SEL_BMSK                              0x2
#define HWIO_TURING_QDSP6SS_QMC_SVS_CTL_QMC_MEM_SVS_SEL_SHFT                              0x1
#define HWIO_TURING_QDSP6SS_QMC_SVS_CTL_QMC_MEM_SVS_BMSK                                  0x1
#define HWIO_TURING_QDSP6SS_QMC_SVS_CTL_QMC_MEM_SVS_SHFT                                  0x0

#define HWIO_TURING_QDSP6SS_BHS_TEST_ADDR                                          (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x000000cc)
#define HWIO_TURING_QDSP6SS_BHS_TEST_OFFS                                          (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x000000cc)
#define HWIO_TURING_QDSP6SS_BHS_TEST_RMSK                                                 0x1
#define HWIO_TURING_QDSP6SS_BHS_TEST_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_BHS_TEST_ADDR, HWIO_TURING_QDSP6SS_BHS_TEST_RMSK)
#define HWIO_TURING_QDSP6SS_BHS_TEST_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_BHS_TEST_ADDR, m)
#define HWIO_TURING_QDSP6SS_BHS_TEST_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_BHS_TEST_ADDR,v)
#define HWIO_TURING_QDSP6SS_BHS_TEST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_BHS_TEST_ADDR,m,v,HWIO_TURING_QDSP6SS_BHS_TEST_IN)
#define HWIO_TURING_QDSP6SS_BHS_TEST_INSTANT_ON_BMSK                                      0x1
#define HWIO_TURING_QDSP6SS_BHS_TEST_INSTANT_ON_SHFT                                      0x0

#define HWIO_TURING_QDSP6SS_CP_PWR_CTL_ADDR                                        (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x000000f0)
#define HWIO_TURING_QDSP6SS_CP_PWR_CTL_OFFS                                        (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x000000f0)
#define HWIO_TURING_QDSP6SS_CP_PWR_CTL_RMSK                                               0xf
#define HWIO_TURING_QDSP6SS_CP_PWR_CTL_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_CP_PWR_CTL_ADDR, HWIO_TURING_QDSP6SS_CP_PWR_CTL_RMSK)
#define HWIO_TURING_QDSP6SS_CP_PWR_CTL_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_CP_PWR_CTL_ADDR, m)
#define HWIO_TURING_QDSP6SS_CP_PWR_CTL_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_CP_PWR_CTL_ADDR,v)
#define HWIO_TURING_QDSP6SS_CP_PWR_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_CP_PWR_CTL_ADDR,m,v,HWIO_TURING_QDSP6SS_CP_PWR_CTL_IN)
#define HWIO_TURING_QDSP6SS_CP_PWR_CTL_LDO_2PASS_ON_BMSK                                  0x8
#define HWIO_TURING_QDSP6SS_CP_PWR_CTL_LDO_2PASS_ON_SHFT                                  0x3
#define HWIO_TURING_QDSP6SS_CP_PWR_CTL_SHUNT_BHS_ON_BMSK                                  0x4
#define HWIO_TURING_QDSP6SS_CP_PWR_CTL_SHUNT_BHS_ON_SHFT                                  0x2
#define HWIO_TURING_QDSP6SS_CP_PWR_CTL_BHS_ON_BMSK                                        0x2
#define HWIO_TURING_QDSP6SS_CP_PWR_CTL_BHS_ON_SHFT                                        0x1
#define HWIO_TURING_QDSP6SS_CP_PWR_CTL_CLAMP_IO_BMSK                                      0x1
#define HWIO_TURING_QDSP6SS_CP_PWR_CTL_CLAMP_IO_SHFT                                      0x0

#define HWIO_TURING_QDSP6SS_CP_PWR_STATUS_ADDR                                     (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x000000f4)
#define HWIO_TURING_QDSP6SS_CP_PWR_STATUS_OFFS                                     (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x000000f4)
#define HWIO_TURING_QDSP6SS_CP_PWR_STATUS_RMSK                                            0x1
#define HWIO_TURING_QDSP6SS_CP_PWR_STATUS_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_CP_PWR_STATUS_ADDR, HWIO_TURING_QDSP6SS_CP_PWR_STATUS_RMSK)
#define HWIO_TURING_QDSP6SS_CP_PWR_STATUS_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_CP_PWR_STATUS_ADDR, m)
#define HWIO_TURING_QDSP6SS_CP_PWR_STATUS_ENR_ACK_BMSK                                    0x1
#define HWIO_TURING_QDSP6SS_CP_PWR_STATUS_ENR_ACK_SHFT                                    0x0

#define HWIO_TURING_QDSP6SS_CP_RESET_ADDR                                          (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x000000f8)
#define HWIO_TURING_QDSP6SS_CP_RESET_OFFS                                          (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x000000f8)
#define HWIO_TURING_QDSP6SS_CP_RESET_RMSK                                                 0x1
#define HWIO_TURING_QDSP6SS_CP_RESET_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_CP_RESET_ADDR, HWIO_TURING_QDSP6SS_CP_RESET_RMSK)
#define HWIO_TURING_QDSP6SS_CP_RESET_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_CP_RESET_ADDR, m)
#define HWIO_TURING_QDSP6SS_CP_RESET_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_CP_RESET_ADDR,v)
#define HWIO_TURING_QDSP6SS_CP_RESET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_CP_RESET_ADDR,m,v,HWIO_TURING_QDSP6SS_CP_RESET_IN)
#define HWIO_TURING_QDSP6SS_CP_RESET_ARES_BMSK                                            0x1
#define HWIO_TURING_QDSP6SS_CP_RESET_ARES_SHFT                                            0x0

#define HWIO_TURING_QDSP6SS_CP_CLK_CTL_ADDR                                        (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x000000fc)
#define HWIO_TURING_QDSP6SS_CP_CLK_CTL_OFFS                                        (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x000000fc)
#define HWIO_TURING_QDSP6SS_CP_CLK_CTL_RMSK                                               0x1
#define HWIO_TURING_QDSP6SS_CP_CLK_CTL_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_CP_CLK_CTL_ADDR, HWIO_TURING_QDSP6SS_CP_CLK_CTL_RMSK)
#define HWIO_TURING_QDSP6SS_CP_CLK_CTL_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_CP_CLK_CTL_ADDR, m)
#define HWIO_TURING_QDSP6SS_CP_CLK_CTL_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_CP_CLK_CTL_ADDR,v)
#define HWIO_TURING_QDSP6SS_CP_CLK_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_CP_CLK_CTL_ADDR,m,v,HWIO_TURING_QDSP6SS_CP_CLK_CTL_IN)
#define HWIO_TURING_QDSP6SS_CP_CLK_CTL_CLK_ENA_BMSK                                       0x1
#define HWIO_TURING_QDSP6SS_CP_CLK_CTL_CLK_ENA_SHFT                                       0x0

#define HWIO_TURING_QDSP6SS_STRAP_TCM_ADDR                                         (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000100)
#define HWIO_TURING_QDSP6SS_STRAP_TCM_OFFS                                         (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000100)
#define HWIO_TURING_QDSP6SS_STRAP_TCM_RMSK                                         0xfffc0000
#define HWIO_TURING_QDSP6SS_STRAP_TCM_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_STRAP_TCM_ADDR, HWIO_TURING_QDSP6SS_STRAP_TCM_RMSK)
#define HWIO_TURING_QDSP6SS_STRAP_TCM_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_STRAP_TCM_ADDR, m)
#define HWIO_TURING_QDSP6SS_STRAP_TCM_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_STRAP_TCM_ADDR,v)
#define HWIO_TURING_QDSP6SS_STRAP_TCM_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_STRAP_TCM_ADDR,m,v,HWIO_TURING_QDSP6SS_STRAP_TCM_IN)
#define HWIO_TURING_QDSP6SS_STRAP_TCM_BASE_ADDR_BMSK                               0xfffc0000
#define HWIO_TURING_QDSP6SS_STRAP_TCM_BASE_ADDR_SHFT                                     0x12

#define HWIO_TURING_QDSP6SS_STRAP_AHBUPPER_ADDR                                    (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000104)
#define HWIO_TURING_QDSP6SS_STRAP_AHBUPPER_OFFS                                    (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000104)
#define HWIO_TURING_QDSP6SS_STRAP_AHBUPPER_RMSK                                    0xffffc000
#define HWIO_TURING_QDSP6SS_STRAP_AHBUPPER_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_STRAP_AHBUPPER_ADDR, HWIO_TURING_QDSP6SS_STRAP_AHBUPPER_RMSK)
#define HWIO_TURING_QDSP6SS_STRAP_AHBUPPER_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_STRAP_AHBUPPER_ADDR, m)
#define HWIO_TURING_QDSP6SS_STRAP_AHBUPPER_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_STRAP_AHBUPPER_ADDR,v)
#define HWIO_TURING_QDSP6SS_STRAP_AHBUPPER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_STRAP_AHBUPPER_ADDR,m,v,HWIO_TURING_QDSP6SS_STRAP_AHBUPPER_IN)
#define HWIO_TURING_QDSP6SS_STRAP_AHBUPPER_UPPER_ADDR_BMSK                         0xffffc000
#define HWIO_TURING_QDSP6SS_STRAP_AHBUPPER_UPPER_ADDR_SHFT                                0xe

#define HWIO_TURING_QDSP6SS_STRAP_AHBLOWER_ADDR                                    (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000108)
#define HWIO_TURING_QDSP6SS_STRAP_AHBLOWER_OFFS                                    (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000108)
#define HWIO_TURING_QDSP6SS_STRAP_AHBLOWER_RMSK                                    0xffffc000
#define HWIO_TURING_QDSP6SS_STRAP_AHBLOWER_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_STRAP_AHBLOWER_ADDR, HWIO_TURING_QDSP6SS_STRAP_AHBLOWER_RMSK)
#define HWIO_TURING_QDSP6SS_STRAP_AHBLOWER_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_STRAP_AHBLOWER_ADDR, m)
#define HWIO_TURING_QDSP6SS_STRAP_AHBLOWER_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_STRAP_AHBLOWER_ADDR,v)
#define HWIO_TURING_QDSP6SS_STRAP_AHBLOWER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_STRAP_AHBLOWER_ADDR,m,v,HWIO_TURING_QDSP6SS_STRAP_AHBLOWER_IN)
#define HWIO_TURING_QDSP6SS_STRAP_AHBLOWER_LOWER_ADDR_BMSK                         0xffffc000
#define HWIO_TURING_QDSP6SS_STRAP_AHBLOWER_LOWER_ADDR_SHFT                                0xe

#define HWIO_TURING_QDSP6SS_STRAP_ACC_ADDR                                         (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000110)
#define HWIO_TURING_QDSP6SS_STRAP_ACC_OFFS                                         (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000110)
#define HWIO_TURING_QDSP6SS_STRAP_ACC_RMSK                                         0xffffffff
#define HWIO_TURING_QDSP6SS_STRAP_ACC_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_STRAP_ACC_ADDR, HWIO_TURING_QDSP6SS_STRAP_ACC_RMSK)
#define HWIO_TURING_QDSP6SS_STRAP_ACC_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_STRAP_ACC_ADDR, m)
#define HWIO_TURING_QDSP6SS_STRAP_ACC_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_STRAP_ACC_ADDR,v)
#define HWIO_TURING_QDSP6SS_STRAP_ACC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_STRAP_ACC_ADDR,m,v,HWIO_TURING_QDSP6SS_STRAP_ACC_IN)
#define HWIO_TURING_QDSP6SS_STRAP_ACC_DATA_BMSK                                    0xffffffff
#define HWIO_TURING_QDSP6SS_STRAP_ACC_DATA_SHFT                                           0x0

#define HWIO_TURING_QDSP6SS_DCC_CTRL_ADDR                                          (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000118)
#define HWIO_TURING_QDSP6SS_DCC_CTRL_OFFS                                          (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000118)
#define HWIO_TURING_QDSP6SS_DCC_CTRL_RMSK                                          0xffffffff
#define HWIO_TURING_QDSP6SS_DCC_CTRL_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_DCC_CTRL_ADDR, HWIO_TURING_QDSP6SS_DCC_CTRL_RMSK)
#define HWIO_TURING_QDSP6SS_DCC_CTRL_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_DCC_CTRL_ADDR, m)
#define HWIO_TURING_QDSP6SS_DCC_CTRL_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_DCC_CTRL_ADDR,v)
#define HWIO_TURING_QDSP6SS_DCC_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_DCC_CTRL_ADDR,m,v,HWIO_TURING_QDSP6SS_DCC_CTRL_IN)
#define HWIO_TURING_QDSP6SS_DCC_CTRL_CTRL_BMSK                                     0xffffffff
#define HWIO_TURING_QDSP6SS_DCC_CTRL_CTRL_SHFT                                            0x0

#define HWIO_TURING_QDSP6SS_STRAP_AXIM2UPPER_ADDR                                  (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x0000011c)
#define HWIO_TURING_QDSP6SS_STRAP_AXIM2UPPER_OFFS                                  (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000011c)
#define HWIO_TURING_QDSP6SS_STRAP_AXIM2UPPER_RMSK                                  0xffffc000
#define HWIO_TURING_QDSP6SS_STRAP_AXIM2UPPER_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_STRAP_AXIM2UPPER_ADDR, HWIO_TURING_QDSP6SS_STRAP_AXIM2UPPER_RMSK)
#define HWIO_TURING_QDSP6SS_STRAP_AXIM2UPPER_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_STRAP_AXIM2UPPER_ADDR, m)
#define HWIO_TURING_QDSP6SS_STRAP_AXIM2UPPER_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_STRAP_AXIM2UPPER_ADDR,v)
#define HWIO_TURING_QDSP6SS_STRAP_AXIM2UPPER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_STRAP_AXIM2UPPER_ADDR,m,v,HWIO_TURING_QDSP6SS_STRAP_AXIM2UPPER_IN)
#define HWIO_TURING_QDSP6SS_STRAP_AXIM2UPPER_UPPER_ADDR_BMSK                       0xffffc000
#define HWIO_TURING_QDSP6SS_STRAP_AXIM2UPPER_UPPER_ADDR_SHFT                              0xe

#define HWIO_TURING_QDSP6SS_STRAP_AXIM2LOWER_ADDR                                  (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000120)
#define HWIO_TURING_QDSP6SS_STRAP_AXIM2LOWER_OFFS                                  (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000120)
#define HWIO_TURING_QDSP6SS_STRAP_AXIM2LOWER_RMSK                                  0xffffc000
#define HWIO_TURING_QDSP6SS_STRAP_AXIM2LOWER_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_STRAP_AXIM2LOWER_ADDR, HWIO_TURING_QDSP6SS_STRAP_AXIM2LOWER_RMSK)
#define HWIO_TURING_QDSP6SS_STRAP_AXIM2LOWER_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_STRAP_AXIM2LOWER_ADDR, m)
#define HWIO_TURING_QDSP6SS_STRAP_AXIM2LOWER_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_STRAP_AXIM2LOWER_ADDR,v)
#define HWIO_TURING_QDSP6SS_STRAP_AXIM2LOWER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_STRAP_AXIM2LOWER_ADDR,m,v,HWIO_TURING_QDSP6SS_STRAP_AXIM2LOWER_IN)
#define HWIO_TURING_QDSP6SS_STRAP_AXIM2LOWER_LOWER_ADDR_BMSK                       0xffffc000
#define HWIO_TURING_QDSP6SS_STRAP_AXIM2LOWER_LOWER_ADDR_SHFT                              0xe

#define HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_SEL_ADDR                                 (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000124)
#define HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_SEL_OFFS                                 (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000124)
#define HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_SEL_RMSK                                        0x1
#define HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_SEL_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_SEL_ADDR, HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_SEL_RMSK)
#define HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_SEL_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_SEL_ADDR, m)
#define HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_SEL_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_SEL_ADDR,v)
#define HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_SEL_ADDR,m,v,HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_SEL_IN)
#define HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_SEL_STRAP_QMC_ACC_SEL_BMSK                      0x1
#define HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_SEL_STRAP_QMC_ACC_SEL_SHFT                      0x0

#define HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_ADDR                                     (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000128)
#define HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_OFFS                                     (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000128)
#define HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_RMSK                                     0xffffffff
#define HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_ADDR, HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_RMSK)
#define HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_ADDR, m)
#define HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_ADDR,v)
#define HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_ADDR,m,v,HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_IN)
#define HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_STRAP_QMC_ACC_BMSK                       0xffffffff
#define HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_STRAP_QMC_ACC_SHFT                              0x0

#define HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_U_ADDR                                   (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x0000012c)
#define HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_U_OFFS                                   (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000012c)
#define HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_U_RMSK                                   0xffffffff
#define HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_U_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_U_ADDR, HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_U_RMSK)
#define HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_U_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_U_ADDR, m)
#define HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_U_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_U_ADDR,v)
#define HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_U_ADDR,m,v,HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_U_IN)
#define HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_U_STRAP_QMC_ACC_U_BMSK                   0xffffffff
#define HWIO_TURING_QDSP6SS_STRAP_QMC_ACC_U_STRAP_QMC_ACC_U_SHFT                          0x0

#define HWIO_TURING_QDSP6SS_CPR_OVERRIDE_ADDR                                      (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000130)
#define HWIO_TURING_QDSP6SS_CPR_OVERRIDE_OFFS                                      (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000130)
#define HWIO_TURING_QDSP6SS_CPR_OVERRIDE_RMSK                                             0x3
#define HWIO_TURING_QDSP6SS_CPR_OVERRIDE_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_CPR_OVERRIDE_ADDR, HWIO_TURING_QDSP6SS_CPR_OVERRIDE_RMSK)
#define HWIO_TURING_QDSP6SS_CPR_OVERRIDE_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_CPR_OVERRIDE_ADDR, m)
#define HWIO_TURING_QDSP6SS_CPR_OVERRIDE_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_CPR_OVERRIDE_ADDR,v)
#define HWIO_TURING_QDSP6SS_CPR_OVERRIDE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_CPR_OVERRIDE_ADDR,m,v,HWIO_TURING_QDSP6SS_CPR_OVERRIDE_IN)
#define HWIO_TURING_QDSP6SS_CPR_OVERRIDE_EXT_ABYP_DIS_BMSK                                0x2
#define HWIO_TURING_QDSP6SS_CPR_OVERRIDE_EXT_ABYP_DIS_SHFT                                0x1
#define HWIO_TURING_QDSP6SS_CPR_OVERRIDE_LOCAL_BYP_DIS_BMSK                               0x1
#define HWIO_TURING_QDSP6SS_CPR_OVERRIDE_LOCAL_BYP_DIS_SHFT                               0x0

#define HWIO_TURING_QDSP6SS_PLL_MODE_ADDR                                          (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000200)
#define HWIO_TURING_QDSP6SS_PLL_MODE_OFFS                                          (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000200)
#define HWIO_TURING_QDSP6SS_PLL_MODE_RMSK                                          0xffffffff
#define HWIO_TURING_QDSP6SS_PLL_MODE_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_PLL_MODE_ADDR, HWIO_TURING_QDSP6SS_PLL_MODE_RMSK)
#define HWIO_TURING_QDSP6SS_PLL_MODE_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_PLL_MODE_ADDR, m)
#define HWIO_TURING_QDSP6SS_PLL_MODE_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_PLL_MODE_ADDR,v)
#define HWIO_TURING_QDSP6SS_PLL_MODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_PLL_MODE_ADDR,m,v,HWIO_TURING_QDSP6SS_PLL_MODE_IN)
#define HWIO_TURING_QDSP6SS_PLL_MODE_PLL_LOCK_DET_BMSK                             0x80000000
#define HWIO_TURING_QDSP6SS_PLL_MODE_PLL_LOCK_DET_SHFT                                   0x1f
#define HWIO_TURING_QDSP6SS_PLL_MODE_PLL_ACTIVE_FLAG_BMSK                          0x40000000
#define HWIO_TURING_QDSP6SS_PLL_MODE_PLL_ACTIVE_FLAG_SHFT                                0x1e
#define HWIO_TURING_QDSP6SS_PLL_MODE_PLL_ACK_LATCH_BMSK                            0x20000000
#define HWIO_TURING_QDSP6SS_PLL_MODE_PLL_ACK_LATCH_SHFT                                  0x1d
#define HWIO_TURING_QDSP6SS_PLL_MODE_RESERVE_BITS28_24_BMSK                        0x1f000000
#define HWIO_TURING_QDSP6SS_PLL_MODE_RESERVE_BITS28_24_SHFT                              0x18
#define HWIO_TURING_QDSP6SS_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_BMSK                 0x800000
#define HWIO_TURING_QDSP6SS_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_SHFT                     0x17
#define HWIO_TURING_QDSP6SS_PLL_MODE_PLL_UPDATE_BMSK                                 0x400000
#define HWIO_TURING_QDSP6SS_PLL_MODE_PLL_UPDATE_SHFT                                     0x16
#define HWIO_TURING_QDSP6SS_PLL_MODE_PLL_VOTE_FSM_RESET_BMSK                         0x200000
#define HWIO_TURING_QDSP6SS_PLL_MODE_PLL_VOTE_FSM_RESET_SHFT                             0x15
#define HWIO_TURING_QDSP6SS_PLL_MODE_PLL_VOTE_FSM_ENA_BMSK                           0x100000
#define HWIO_TURING_QDSP6SS_PLL_MODE_PLL_VOTE_FSM_ENA_SHFT                               0x14
#define HWIO_TURING_QDSP6SS_PLL_MODE_PLL_BIAS_COUNT_BMSK                              0xfc000
#define HWIO_TURING_QDSP6SS_PLL_MODE_PLL_BIAS_COUNT_SHFT                                  0xe
#define HWIO_TURING_QDSP6SS_PLL_MODE_PLL_LOCK_COUNT_BMSK                               0x3f00
#define HWIO_TURING_QDSP6SS_PLL_MODE_PLL_LOCK_COUNT_SHFT                                  0x8
#define HWIO_TURING_QDSP6SS_PLL_MODE_RESERVE_BITS7_4_BMSK                                0xf0
#define HWIO_TURING_QDSP6SS_PLL_MODE_RESERVE_BITS7_4_SHFT                                 0x4
#define HWIO_TURING_QDSP6SS_PLL_MODE_PLL_PLLTEST_BMSK                                     0x8
#define HWIO_TURING_QDSP6SS_PLL_MODE_PLL_PLLTEST_SHFT                                     0x3
#define HWIO_TURING_QDSP6SS_PLL_MODE_PLL_RESET_N_BMSK                                     0x4
#define HWIO_TURING_QDSP6SS_PLL_MODE_PLL_RESET_N_SHFT                                     0x2
#define HWIO_TURING_QDSP6SS_PLL_MODE_PLL_BYPASSNL_BMSK                                    0x2
#define HWIO_TURING_QDSP6SS_PLL_MODE_PLL_BYPASSNL_SHFT                                    0x1
#define HWIO_TURING_QDSP6SS_PLL_MODE_PLL_OUTCTRL_BMSK                                     0x1
#define HWIO_TURING_QDSP6SS_PLL_MODE_PLL_OUTCTRL_SHFT                                     0x0

#define HWIO_TURING_QDSP6SS_PLL_L_VAL_ADDR                                         (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000204)
#define HWIO_TURING_QDSP6SS_PLL_L_VAL_OFFS                                         (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000204)
#define HWIO_TURING_QDSP6SS_PLL_L_VAL_RMSK                                             0xffff
#define HWIO_TURING_QDSP6SS_PLL_L_VAL_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_PLL_L_VAL_ADDR, HWIO_TURING_QDSP6SS_PLL_L_VAL_RMSK)
#define HWIO_TURING_QDSP6SS_PLL_L_VAL_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_PLL_L_VAL_ADDR, m)
#define HWIO_TURING_QDSP6SS_PLL_L_VAL_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_PLL_L_VAL_ADDR,v)
#define HWIO_TURING_QDSP6SS_PLL_L_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_PLL_L_VAL_ADDR,m,v,HWIO_TURING_QDSP6SS_PLL_L_VAL_IN)
#define HWIO_TURING_QDSP6SS_PLL_L_VAL_PLL_L_BMSK                                       0xffff
#define HWIO_TURING_QDSP6SS_PLL_L_VAL_PLL_L_SHFT                                          0x0

#define HWIO_TURING_QDSP6SS_PLL_ALPHA_VAL_ADDR                                     (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000208)
#define HWIO_TURING_QDSP6SS_PLL_ALPHA_VAL_OFFS                                     (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000208)
#define HWIO_TURING_QDSP6SS_PLL_ALPHA_VAL_RMSK                                     0xffffffff
#define HWIO_TURING_QDSP6SS_PLL_ALPHA_VAL_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_PLL_ALPHA_VAL_ADDR, HWIO_TURING_QDSP6SS_PLL_ALPHA_VAL_RMSK)
#define HWIO_TURING_QDSP6SS_PLL_ALPHA_VAL_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_PLL_ALPHA_VAL_ADDR, m)
#define HWIO_TURING_QDSP6SS_PLL_ALPHA_VAL_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_PLL_ALPHA_VAL_ADDR,v)
#define HWIO_TURING_QDSP6SS_PLL_ALPHA_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_PLL_ALPHA_VAL_ADDR,m,v,HWIO_TURING_QDSP6SS_PLL_ALPHA_VAL_IN)
#define HWIO_TURING_QDSP6SS_PLL_ALPHA_VAL_PLL_ALPHA_31_0_BMSK                      0xffffffff
#define HWIO_TURING_QDSP6SS_PLL_ALPHA_VAL_PLL_ALPHA_31_0_SHFT                             0x0

#define HWIO_TURING_QDSP6SS_PLL_ALPHA_VAL_U_ADDR                                   (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x0000020c)
#define HWIO_TURING_QDSP6SS_PLL_ALPHA_VAL_U_OFFS                                   (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000020c)
#define HWIO_TURING_QDSP6SS_PLL_ALPHA_VAL_U_RMSK                                         0xff
#define HWIO_TURING_QDSP6SS_PLL_ALPHA_VAL_U_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_PLL_ALPHA_VAL_U_ADDR, HWIO_TURING_QDSP6SS_PLL_ALPHA_VAL_U_RMSK)
#define HWIO_TURING_QDSP6SS_PLL_ALPHA_VAL_U_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_PLL_ALPHA_VAL_U_ADDR, m)
#define HWIO_TURING_QDSP6SS_PLL_ALPHA_VAL_U_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_PLL_ALPHA_VAL_U_ADDR,v)
#define HWIO_TURING_QDSP6SS_PLL_ALPHA_VAL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_PLL_ALPHA_VAL_U_ADDR,m,v,HWIO_TURING_QDSP6SS_PLL_ALPHA_VAL_U_IN)
#define HWIO_TURING_QDSP6SS_PLL_ALPHA_VAL_U_PLL_ALPHA_39_32_BMSK                         0xff
#define HWIO_TURING_QDSP6SS_PLL_ALPHA_VAL_U_PLL_ALPHA_39_32_SHFT                          0x0

#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_ADDR                                      (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000210)
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_OFFS                                      (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000210)
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_RMSK                                      0xffffffff
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_PLL_USER_CTL_ADDR, HWIO_TURING_QDSP6SS_PLL_USER_CTL_RMSK)
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_PLL_USER_CTL_ADDR, m)
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_PLL_USER_CTL_ADDR,v)
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_PLL_USER_CTL_ADDR,m,v,HWIO_TURING_QDSP6SS_PLL_USER_CTL_IN)
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_RESERVE_BITS31_28_BMSK                    0xf0000000
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_RESERVE_BITS31_28_SHFT                          0x1c
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_SSC_MODE_CONTROL_BMSK                      0x8000000
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_SSC_MODE_CONTROL_SHFT                           0x1b
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_RESERVE_BITS26_25_BMSK                     0x6000000
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_RESERVE_BITS26_25_SHFT                          0x19
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_ALPHA_EN_BMSK                              0x1000000
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_ALPHA_EN_SHFT                                   0x18
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_RESERVE_BITS23_22_BMSK                      0xc00000
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_RESERVE_BITS23_22_SHFT                          0x16
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_VCO_SEL_BMSK                                0x300000
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_VCO_SEL_SHFT                                    0x14
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_RESERVE_BITS19_15_BMSK                       0xf8000
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_RESERVE_BITS19_15_SHFT                           0xf
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_PRE_DIV_RATIO_BMSK                            0x7000
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_PRE_DIV_RATIO_SHFT                               0xc
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_POST_DIV_RATIO_BMSK                            0xf00
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_POST_DIV_RATIO_SHFT                              0x8
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_OUTPUT_INV_BMSK                                 0x80
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_OUTPUT_INV_SHFT                                  0x7
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_RESERVE_BITS6_5_BMSK                            0x60
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_RESERVE_BITS6_5_SHFT                             0x5
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_TEST_BMSK                             0x10
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_TEST_SHFT                              0x4
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_EARLY_BMSK                             0x8
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_EARLY_SHFT                             0x3
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_AUX2_BMSK                              0x4
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_AUX2_SHFT                              0x2
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_AUX_BMSK                               0x2
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_AUX_SHFT                               0x1
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_MAIN_BMSK                              0x1
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_MAIN_SHFT                              0x0

#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_U_ADDR                                    (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000214)
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_U_OFFS                                    (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000214)
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_U_RMSK                                    0xffffffff
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_U_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_PLL_USER_CTL_U_ADDR, HWIO_TURING_QDSP6SS_PLL_USER_CTL_U_RMSK)
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_U_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_PLL_USER_CTL_U_ADDR, m)
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_U_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_PLL_USER_CTL_U_ADDR,v)
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_PLL_USER_CTL_U_ADDR,m,v,HWIO_TURING_QDSP6SS_PLL_USER_CTL_U_IN)
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_U_CALIBRATION_L_BMSK                      0xffff0000
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_U_CALIBRATION_L_SHFT                            0x10
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_U_RESERVE_BITS15_12_BMSK                      0xf000
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_U_RESERVE_BITS15_12_SHFT                         0xc
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_U_LATCH_INTERFACE_BYPASS_BMSK                  0x800
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_U_LATCH_INTERFACE_BYPASS_SHFT                    0xb
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_U_STATUS_REGISTER_BMSK                         0x700
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_U_STATUS_REGISTER_SHFT                           0x8
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_U_DSM_BMSK                                      0x80
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_U_DSM_SHFT                                       0x7
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_U_WRITE_STATE_BMSK                              0x40
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_U_WRITE_STATE_SHFT                               0x6
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_U_TARGET_CTL_BMSK                               0x38
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_U_TARGET_CTL_SHFT                                0x3
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_U_LOCK_DET_BMSK                                  0x4
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_U_LOCK_DET_SHFT                                  0x2
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_U_FREEZE_PLL_BMSK                                0x2
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_U_FREEZE_PLL_SHFT                                0x1
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_U_TOGGLE_DET_BMSK                                0x1
#define HWIO_TURING_QDSP6SS_PLL_USER_CTL_U_TOGGLE_DET_SHFT                                0x0

#define HWIO_TURING_QDSP6SS_PLL_CONFIG_CTL_ADDR                                    (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000218)
#define HWIO_TURING_QDSP6SS_PLL_CONFIG_CTL_OFFS                                    (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000218)
#define HWIO_TURING_QDSP6SS_PLL_CONFIG_CTL_RMSK                                    0xffffffff
#define HWIO_TURING_QDSP6SS_PLL_CONFIG_CTL_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_PLL_CONFIG_CTL_ADDR, HWIO_TURING_QDSP6SS_PLL_CONFIG_CTL_RMSK)
#define HWIO_TURING_QDSP6SS_PLL_CONFIG_CTL_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_PLL_CONFIG_CTL_ADDR, m)
#define HWIO_TURING_QDSP6SS_PLL_CONFIG_CTL_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_PLL_CONFIG_CTL_ADDR,v)
#define HWIO_TURING_QDSP6SS_PLL_CONFIG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_PLL_CONFIG_CTL_ADDR,m,v,HWIO_TURING_QDSP6SS_PLL_CONFIG_CTL_IN)
#define HWIO_TURING_QDSP6SS_PLL_CONFIG_CTL_SINGLE_DMET_MODE_ENABLE_BMSK            0x80000000
#define HWIO_TURING_QDSP6SS_PLL_CONFIG_CTL_SINGLE_DMET_MODE_ENABLE_SHFT                  0x1f
#define HWIO_TURING_QDSP6SS_PLL_CONFIG_CTL_DMET_WINDOW_ENABLE_BMSK                 0x40000000
#define HWIO_TURING_QDSP6SS_PLL_CONFIG_CTL_DMET_WINDOW_ENABLE_SHFT                       0x1e
#define HWIO_TURING_QDSP6SS_PLL_CONFIG_CTL_TOGGLE_DET_SAMPLE_INTER_BMSK            0x3c000000
#define HWIO_TURING_QDSP6SS_PLL_CONFIG_CTL_TOGGLE_DET_SAMPLE_INTER_SHFT                  0x1a
#define HWIO_TURING_QDSP6SS_PLL_CONFIG_CTL_TOGGLE_DET_THRESHOLD_BMSK                0x3800000
#define HWIO_TURING_QDSP6SS_PLL_CONFIG_CTL_TOGGLE_DET_THRESHOLD_SHFT                     0x17
#define HWIO_TURING_QDSP6SS_PLL_CONFIG_CTL_TOGGLE_DET_SAMPLE_BMSK                    0x700000
#define HWIO_TURING_QDSP6SS_PLL_CONFIG_CTL_TOGGLE_DET_SAMPLE_SHFT                        0x14
#define HWIO_TURING_QDSP6SS_PLL_CONFIG_CTL_LOCK_DET_THRESHOLD_BMSK                    0xff000
#define HWIO_TURING_QDSP6SS_PLL_CONFIG_CTL_LOCK_DET_THRESHOLD_SHFT                        0xc
#define HWIO_TURING_QDSP6SS_PLL_CONFIG_CTL_LOCK_DET_SAMPLE_SIZE_BMSK                    0xf00
#define HWIO_TURING_QDSP6SS_PLL_CONFIG_CTL_LOCK_DET_SAMPLE_SIZE_SHFT                      0x8
#define HWIO_TURING_QDSP6SS_PLL_CONFIG_CTL_GLITCH_THRESHOLD_BMSK                         0xc0
#define HWIO_TURING_QDSP6SS_PLL_CONFIG_CTL_GLITCH_THRESHOLD_SHFT                          0x6
#define HWIO_TURING_QDSP6SS_PLL_CONFIG_CTL_REF_CYCLE_BMSK                                0x30
#define HWIO_TURING_QDSP6SS_PLL_CONFIG_CTL_REF_CYCLE_SHFT                                 0x4
#define HWIO_TURING_QDSP6SS_PLL_CONFIG_CTL_KFN_BMSK                                       0xf
#define HWIO_TURING_QDSP6SS_PLL_CONFIG_CTL_KFN_SHFT                                       0x0

#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_ADDR                                      (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x0000021c)
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_OFFS                                      (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000021c)
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_RMSK                                      0xffffffff
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_PLL_TEST_CTL_ADDR, HWIO_TURING_QDSP6SS_PLL_TEST_CTL_RMSK)
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_PLL_TEST_CTL_ADDR, m)
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_PLL_TEST_CTL_ADDR,v)
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_PLL_TEST_CTL_ADDR,m,v,HWIO_TURING_QDSP6SS_PLL_TEST_CTL_IN)
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_BIAS_GEN_TRIM_BMSK                        0xe0000000
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_BIAS_GEN_TRIM_SHFT                              0x1d
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_DCO_BMSK                                  0x10000000
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_DCO_SHFT                                        0x1c
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_PROCESS_CALB_BMSK                          0xc000000
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_PROCESS_CALB_SHFT                               0x1a
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_OVERRIDE_PROCESS_CALB_BMSK                 0x2000000
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_OVERRIDE_PROCESS_CALB_SHFT                      0x19
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_FINE_FCW_BMSK                              0x1e00000
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_FINE_FCW_SHFT                                   0x15
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_OVERRIDE_FINE_FCW_BMSK                      0x100000
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_OVERRIDE_FINE_FCW_SHFT                          0x14
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_COARSE_FCW_BMSK                              0xfe000
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_COARSE_FCW_SHFT                                  0xd
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_OVERRIDE_COARSE_BMSK                          0x1000
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_OVERRIDE_COARSE_SHFT                             0xc
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_DISABLE_LFSR_BMSK                              0x800
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_DISABLE_LFSR_SHFT                                0xb
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_DTEST_SEL_BMSK                                 0x700
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_DTEST_SEL_SHFT                                   0x8
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_DTEST_EN_BMSK                                   0x80
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_DTEST_EN_SHFT                                    0x7
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_BYP_TESTAMP_BMSK                                0x40
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_BYP_TESTAMP_SHFT                                 0x6
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_ATEST1_SEL_BMSK                                 0x30
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_ATEST1_SEL_SHFT                                  0x4
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_ATEST0_SEL_BMSK                                  0xc
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_ATEST0_SEL_SHFT                                  0x2
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_ATEST1_EN_BMSK                                   0x2
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_ATEST1_EN_SHFT                                   0x1
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_ATEST0_EN_BMSK                                   0x1
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_ATEST0_EN_SHFT                                   0x0

#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_U_ADDR                                    (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000220)
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_U_OFFS                                    (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000220)
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_U_RMSK                                    0xffffffff
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_U_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_PLL_TEST_CTL_U_ADDR, HWIO_TURING_QDSP6SS_PLL_TEST_CTL_U_RMSK)
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_U_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_PLL_TEST_CTL_U_ADDR, m)
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_U_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_PLL_TEST_CTL_U_ADDR,v)
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_PLL_TEST_CTL_U_ADDR,m,v,HWIO_TURING_QDSP6SS_PLL_TEST_CTL_U_IN)
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_U_RESERVE_BITS31_14_BMSK                  0xffffc000
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_U_RESERVE_BITS31_14_SHFT                         0xe
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_U_OVERRIDE_FINE_FCW_MSB_BMSK                  0x2000
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_U_OVERRIDE_FINE_FCW_MSB_SHFT                     0xd
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_U_DTEST_MODE_SEL_BMSK                         0x1800
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_U_DTEST_MODE_SEL_SHFT                            0xb
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_U_NMO_OSC_SEL_BMSK                             0x600
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_U_NMO_OSC_SEL_SHFT                               0x9
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_U_NMO_EN_BMSK                                  0x100
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_U_NMO_EN_SHFT                                    0x8
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_U_NOISE_MAG_BMSK                                0xe0
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_U_NOISE_MAG_SHFT                                 0x5
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_U_NOISE_GEN_BMSK                                0x10
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_U_NOISE_GEN_SHFT                                 0x4
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_U_OSC_BIAS_GND_BMSK                              0x8
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_U_OSC_BIAS_GND_SHFT                              0x3
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_U_PLL_TEST_OUT_SEL_BMSK                          0x6
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_U_PLL_TEST_OUT_SEL_SHFT                          0x1
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_U_CAL_CODE_UPDATE_BMSK                           0x1
#define HWIO_TURING_QDSP6SS_PLL_TEST_CTL_U_CAL_CODE_UPDATE_SHFT                           0x0

#define HWIO_TURING_QDSP6SS_PLL_STATUS_ADDR                                        (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000224)
#define HWIO_TURING_QDSP6SS_PLL_STATUS_OFFS                                        (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000224)
#define HWIO_TURING_QDSP6SS_PLL_STATUS_RMSK                                        0xffffffff
#define HWIO_TURING_QDSP6SS_PLL_STATUS_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_PLL_STATUS_ADDR, HWIO_TURING_QDSP6SS_PLL_STATUS_RMSK)
#define HWIO_TURING_QDSP6SS_PLL_STATUS_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_PLL_STATUS_ADDR, m)
#define HWIO_TURING_QDSP6SS_PLL_STATUS_STATUS_31_0_BMSK                            0xffffffff
#define HWIO_TURING_QDSP6SS_PLL_STATUS_STATUS_31_0_SHFT                                   0x0

#define HWIO_TURING_QDSP6SS_PLL_FREQ_CTL_ADDR                                      (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000228)
#define HWIO_TURING_QDSP6SS_PLL_FREQ_CTL_OFFS                                      (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000228)
#define HWIO_TURING_QDSP6SS_PLL_FREQ_CTL_RMSK                                      0xffffffff
#define HWIO_TURING_QDSP6SS_PLL_FREQ_CTL_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_PLL_FREQ_CTL_ADDR, HWIO_TURING_QDSP6SS_PLL_FREQ_CTL_RMSK)
#define HWIO_TURING_QDSP6SS_PLL_FREQ_CTL_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_PLL_FREQ_CTL_ADDR, m)
#define HWIO_TURING_QDSP6SS_PLL_FREQ_CTL_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_PLL_FREQ_CTL_ADDR,v)
#define HWIO_TURING_QDSP6SS_PLL_FREQ_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_PLL_FREQ_CTL_ADDR,m,v,HWIO_TURING_QDSP6SS_PLL_FREQ_CTL_IN)
#define HWIO_TURING_QDSP6SS_PLL_FREQ_CTL_FREQUENCY_CTL_WORD_BMSK                   0xffffffff
#define HWIO_TURING_QDSP6SS_PLL_FREQ_CTL_FREQUENCY_CTL_WORD_SHFT                          0x0

#define HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_STATUS_ADDR                             (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000240)
#define HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_STATUS_OFFS                             (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000240)
#define HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_STATUS_RMSK                                    0x3
#define HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_STATUS_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_STATUS_ADDR, HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_STATUS_RMSK)
#define HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_STATUS_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_STATUS_ADDR, m)
#define HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_STATUS_RCG2PLL_UPD_STATUS_BMSK                 0x2
#define HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_STATUS_RCG2PLL_UPD_STATUS_SHFT                 0x1
#define HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_STATUS_PLL2RCG_UPD_STATUS_BMSK                 0x1
#define HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_STATUS_PLL2RCG_UPD_STATUS_SHFT                 0x0

#define HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_CFG_ADDR                                (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000244)
#define HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_CFG_OFFS                                (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000244)
#define HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_CFG_RMSK                                       0x3
#define HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_CFG_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_CFG_ADDR, HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_CFG_RMSK)
#define HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_CFG_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_CFG_ADDR, m)
#define HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_CFG_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_CFG_ADDR,v)
#define HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_CFG_ADDR,m,v,HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_CFG_IN)
#define HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_CFG_RCG2PLL_UPD_EN_BMSK                        0x2
#define HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_CFG_RCG2PLL_UPD_EN_SHFT                        0x1
#define HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_CFG_PLL2RCG_UPD_EN_BMSK                        0x1
#define HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_CFG_PLL2RCG_UPD_EN_SHFT                        0x0

#define HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_ADDR                             (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000248)
#define HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_OFFS                             (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000248)
#define HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_RMSK                                   0x1f
#define HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_ADDR, HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_RMSK)
#define HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_ADDR, m)
#define HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_ADDR,v)
#define HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_ADDR,m,v,HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_IN)
#define HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_MATCH_VALUE_BMSK                       0x1f
#define HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_MATCH_VALUE_SHFT                        0x0

#define HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_CMD_ADDR                                (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x0000024c)
#define HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_CMD_OFFS                                (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000024c)
#define HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_CMD_RMSK                                       0x1
#define HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_CMD_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_CMD_ADDR,v)
#define HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_CMD_CMD_BMSK                                   0x1
#define HWIO_TURING_QDSP6SS_PLL_RCG_UPDATE_CMD_CMD_SHFT                                   0x0

#define HWIO_TURING_QDSP6SS_DBG_NMI_CFG_ADDR                                       (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000300)
#define HWIO_TURING_QDSP6SS_DBG_NMI_CFG_OFFS                                       (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000300)
#define HWIO_TURING_QDSP6SS_DBG_NMI_CFG_RMSK                                              0x7
#define HWIO_TURING_QDSP6SS_DBG_NMI_CFG_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_DBG_NMI_CFG_ADDR, HWIO_TURING_QDSP6SS_DBG_NMI_CFG_RMSK)
#define HWIO_TURING_QDSP6SS_DBG_NMI_CFG_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_DBG_NMI_CFG_ADDR, m)
#define HWIO_TURING_QDSP6SS_DBG_NMI_CFG_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_DBG_NMI_CFG_ADDR,v)
#define HWIO_TURING_QDSP6SS_DBG_NMI_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_DBG_NMI_CFG_ADDR,m,v,HWIO_TURING_QDSP6SS_DBG_NMI_CFG_IN)
#define HWIO_TURING_QDSP6SS_DBG_NMI_CFG_DBG_NMI_EN_IN_PWR_COLLAPSE_BMSK                   0x4
#define HWIO_TURING_QDSP6SS_DBG_NMI_CFG_DBG_NMI_EN_IN_PWR_COLLAPSE_SHFT                   0x2
#define HWIO_TURING_QDSP6SS_DBG_NMI_CFG_DBG_NMI_DISABLE_BMSK                              0x2
#define HWIO_TURING_QDSP6SS_DBG_NMI_CFG_DBG_NMI_DISABLE_SHFT                              0x1
#define HWIO_TURING_QDSP6SS_DBG_NMI_CFG_DBG_NMI_WAKEUP_DISABLE_BMSK                       0x1
#define HWIO_TURING_QDSP6SS_DBG_NMI_CFG_DBG_NMI_WAKEUP_DISABLE_SHFT                       0x0

#define HWIO_TURING_QDSP6SS_DBG_NMI_PWR_STATUS_ADDR                                (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00000304)
#define HWIO_TURING_QDSP6SS_DBG_NMI_PWR_STATUS_OFFS                                (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000304)
#define HWIO_TURING_QDSP6SS_DBG_NMI_PWR_STATUS_RMSK                                       0x3
#define HWIO_TURING_QDSP6SS_DBG_NMI_PWR_STATUS_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_DBG_NMI_PWR_STATUS_ADDR, HWIO_TURING_QDSP6SS_DBG_NMI_PWR_STATUS_RMSK)
#define HWIO_TURING_QDSP6SS_DBG_NMI_PWR_STATUS_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_DBG_NMI_PWR_STATUS_ADDR, m)
#define HWIO_TURING_QDSP6SS_DBG_NMI_PWR_STATUS_QDSP6_PWR_COLLAPSE_BMSK                    0x2
#define HWIO_TURING_QDSP6SS_DBG_NMI_PWR_STATUS_QDSP6_PWR_COLLAPSE_SHFT                    0x1
#define HWIO_TURING_QDSP6SS_DBG_NMI_PWR_STATUS_QDSP6_IN_SLEEP_BMSK                        0x1
#define HWIO_TURING_QDSP6SS_DBG_NMI_PWR_STATUS_QDSP6_IN_SLEEP_SHFT                        0x0

#define HWIO_TURING_QDSP6SS_TEST_BUS_CTL_ADDR                                      (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00002000)
#define HWIO_TURING_QDSP6SS_TEST_BUS_CTL_OFFS                                      (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00002000)
#define HWIO_TURING_QDSP6SS_TEST_BUS_CTL_RMSK                                      0xffffffff
#define HWIO_TURING_QDSP6SS_TEST_BUS_CTL_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_TEST_BUS_CTL_ADDR, HWIO_TURING_QDSP6SS_TEST_BUS_CTL_RMSK)
#define HWIO_TURING_QDSP6SS_TEST_BUS_CTL_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_TEST_BUS_CTL_ADDR, m)
#define HWIO_TURING_QDSP6SS_TEST_BUS_CTL_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_TEST_BUS_CTL_ADDR,v)
#define HWIO_TURING_QDSP6SS_TEST_BUS_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_TEST_BUS_CTL_ADDR,m,v,HWIO_TURING_QDSP6SS_TEST_BUS_CTL_IN)
#define HWIO_TURING_QDSP6SS_TEST_BUS_CTL_SPARE_CFG_BMSK                            0xff000000
#define HWIO_TURING_QDSP6SS_TEST_BUS_CTL_SPARE_CFG_SHFT                                  0x18
#define HWIO_TURING_QDSP6SS_TEST_BUS_CTL_HWE_INV_BMSK                                0x800000
#define HWIO_TURING_QDSP6SS_TEST_BUS_CTL_HWE_INV_SHFT                                    0x17
#define HWIO_TURING_QDSP6SS_TEST_BUS_CTL_HWE_SEL_BMSK                                0x7c0000
#define HWIO_TURING_QDSP6SS_TEST_BUS_CTL_HWE_SEL_SHFT                                    0x12
#define HWIO_TURING_QDSP6SS_TEST_BUS_CTL_TESTBUS_EN_BMSK                              0x20000
#define HWIO_TURING_QDSP6SS_TEST_BUS_CTL_TESTBUS_EN_SHFT                                 0x11
#define HWIO_TURING_QDSP6SS_TEST_BUS_CTL_Q6_SEL_BMSK                                  0x10000
#define HWIO_TURING_QDSP6SS_TEST_BUS_CTL_Q6_SEL_SHFT                                     0x10
#define HWIO_TURING_QDSP6SS_TEST_BUS_CTL_SEL_BMSK                                      0xffff
#define HWIO_TURING_QDSP6SS_TEST_BUS_CTL_SEL_SHFT                                         0x0

#define HWIO_TURING_QDSP6SS_TEST_BUS_VALUE_ADDR                                    (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00002004)
#define HWIO_TURING_QDSP6SS_TEST_BUS_VALUE_OFFS                                    (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00002004)
#define HWIO_TURING_QDSP6SS_TEST_BUS_VALUE_RMSK                                    0xffffffff
#define HWIO_TURING_QDSP6SS_TEST_BUS_VALUE_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_TEST_BUS_VALUE_ADDR, HWIO_TURING_QDSP6SS_TEST_BUS_VALUE_RMSK)
#define HWIO_TURING_QDSP6SS_TEST_BUS_VALUE_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_TEST_BUS_VALUE_ADDR, m)
#define HWIO_TURING_QDSP6SS_TEST_BUS_VALUE_VALUE_BMSK                              0xffffffff
#define HWIO_TURING_QDSP6SS_TEST_BUS_VALUE_VALUE_SHFT                                     0x0

#define HWIO_TURING_QDSP6SS_TEST_BUS_WDATA_ADDR                                    (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00002008)
#define HWIO_TURING_QDSP6SS_TEST_BUS_WDATA_OFFS                                    (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00002008)
#define HWIO_TURING_QDSP6SS_TEST_BUS_WDATA_RMSK                                    0xffffffff
#define HWIO_TURING_QDSP6SS_TEST_BUS_WDATA_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_TEST_BUS_WDATA_ADDR, HWIO_TURING_QDSP6SS_TEST_BUS_WDATA_RMSK)
#define HWIO_TURING_QDSP6SS_TEST_BUS_WDATA_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_TEST_BUS_WDATA_ADDR, m)
#define HWIO_TURING_QDSP6SS_TEST_BUS_WDATA_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_TEST_BUS_WDATA_ADDR,v)
#define HWIO_TURING_QDSP6SS_TEST_BUS_WDATA_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_TEST_BUS_WDATA_ADDR,m,v,HWIO_TURING_QDSP6SS_TEST_BUS_WDATA_IN)
#define HWIO_TURING_QDSP6SS_TEST_BUS_WDATA_VALUE_BMSK                              0xffffffff
#define HWIO_TURING_QDSP6SS_TEST_BUS_WDATA_VALUE_SHFT                                     0x0

#define HWIO_TURING_QDSP6SS_PWRDBG_CTL_ADDR                                        (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x0000200c)
#define HWIO_TURING_QDSP6SS_PWRDBG_CTL_OFFS                                        (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000200c)
#define HWIO_TURING_QDSP6SS_PWRDBG_CTL_RMSK                                               0x1
#define HWIO_TURING_QDSP6SS_PWRDBG_CTL_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_PWRDBG_CTL_ADDR, HWIO_TURING_QDSP6SS_PWRDBG_CTL_RMSK)
#define HWIO_TURING_QDSP6SS_PWRDBG_CTL_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_PWRDBG_CTL_ADDR, m)
#define HWIO_TURING_QDSP6SS_PWRDBG_CTL_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_PWRDBG_CTL_ADDR,v)
#define HWIO_TURING_QDSP6SS_PWRDBG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_PWRDBG_CTL_ADDR,m,v,HWIO_TURING_QDSP6SS_PWRDBG_CTL_IN)
#define HWIO_TURING_QDSP6SS_PWRDBG_CTL_ENA_BMSK                                           0x1
#define HWIO_TURING_QDSP6SS_PWRDBG_CTL_ENA_SHFT                                           0x0

#define HWIO_TURING_QDSP6SS_TEST_CLK_CTL_ADDR                                      (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00002010)
#define HWIO_TURING_QDSP6SS_TEST_CLK_CTL_OFFS                                      (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00002010)
#define HWIO_TURING_QDSP6SS_TEST_CLK_CTL_RMSK                                            0x7f
#define HWIO_TURING_QDSP6SS_TEST_CLK_CTL_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_TEST_CLK_CTL_ADDR, HWIO_TURING_QDSP6SS_TEST_CLK_CTL_RMSK)
#define HWIO_TURING_QDSP6SS_TEST_CLK_CTL_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_TEST_CLK_CTL_ADDR, m)
#define HWIO_TURING_QDSP6SS_TEST_CLK_CTL_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_TEST_CLK_CTL_ADDR,v)
#define HWIO_TURING_QDSP6SS_TEST_CLK_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_TEST_CLK_CTL_ADDR,m,v,HWIO_TURING_QDSP6SS_TEST_CLK_CTL_IN)
#define HWIO_TURING_QDSP6SS_TEST_CLK_CTL_Q6_DBG_CLK_EN_BMSK                              0x40
#define HWIO_TURING_QDSP6SS_TEST_CLK_CTL_Q6_DBG_CLK_EN_SHFT                               0x6
#define HWIO_TURING_QDSP6SS_TEST_CLK_CTL_Q6_DBG_CLK_INV_BMSK                             0x20
#define HWIO_TURING_QDSP6SS_TEST_CLK_CTL_Q6_DBG_CLK_INV_SHFT                              0x5
#define HWIO_TURING_QDSP6SS_TEST_CLK_CTL_DBG_CLK_SEL_BMSK                                0x1f
#define HWIO_TURING_QDSP6SS_TEST_CLK_CTL_DBG_CLK_SEL_SHFT                                 0x0

#define HWIO_TURING_QDSP6SS_ZMEAS_CONFIG_ADDR                                      (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00002018)
#define HWIO_TURING_QDSP6SS_ZMEAS_CONFIG_OFFS                                      (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00002018)
#define HWIO_TURING_QDSP6SS_ZMEAS_CONFIG_RMSK                                        0xffffff
#define HWIO_TURING_QDSP6SS_ZMEAS_CONFIG_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_ZMEAS_CONFIG_ADDR, HWIO_TURING_QDSP6SS_ZMEAS_CONFIG_RMSK)
#define HWIO_TURING_QDSP6SS_ZMEAS_CONFIG_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_ZMEAS_CONFIG_ADDR, m)
#define HWIO_TURING_QDSP6SS_ZMEAS_CONFIG_OUT(v)      \
        out_dword(HWIO_TURING_QDSP6SS_ZMEAS_CONFIG_ADDR,v)
#define HWIO_TURING_QDSP6SS_ZMEAS_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QDSP6SS_ZMEAS_CONFIG_ADDR,m,v,HWIO_TURING_QDSP6SS_ZMEAS_CONFIG_IN)
#define HWIO_TURING_QDSP6SS_ZMEAS_CONFIG_ZMEAS_COUNT_BMSK                            0xffffe0
#define HWIO_TURING_QDSP6SS_ZMEAS_CONFIG_ZMEAS_COUNT_SHFT                                 0x5
#define HWIO_TURING_QDSP6SS_ZMEAS_CONFIG_MUX_SEL_BMSK                                    0x10
#define HWIO_TURING_QDSP6SS_ZMEAS_CONFIG_MUX_SEL_SHFT                                     0x4
#define HWIO_TURING_QDSP6SS_ZMEAS_CONFIG_ZMEAS_CLK_R_ENA_BMSK                             0x8
#define HWIO_TURING_QDSP6SS_ZMEAS_CONFIG_ZMEAS_CLK_R_ENA_SHFT                             0x3
#define HWIO_TURING_QDSP6SS_ZMEAS_CONFIG_ZMEAS_CGC_EN_BMSK                                0x4
#define HWIO_TURING_QDSP6SS_ZMEAS_CONFIG_ZMEAS_CGC_EN_SHFT                                0x2
#define HWIO_TURING_QDSP6SS_ZMEAS_CONFIG_ZMEAS_BYPASS_BMSK                                0x2
#define HWIO_TURING_QDSP6SS_ZMEAS_CONFIG_ZMEAS_BYPASS_SHFT                                0x1
#define HWIO_TURING_QDSP6SS_ZMEAS_CONFIG_ZMEAS_SW_RESET_BMSK                              0x1
#define HWIO_TURING_QDSP6SS_ZMEAS_CONFIG_ZMEAS_SW_RESET_SHFT                              0x0

#define HWIO_TURING_QDSP6SS_CORE_STATUS_ADDR                                       (TURING_QDSP6V60SS_PUB_REG_BASE      + 0x00002028)
#define HWIO_TURING_QDSP6SS_CORE_STATUS_OFFS                                       (TURING_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00002028)
#define HWIO_TURING_QDSP6SS_CORE_STATUS_RMSK                                              0x7
#define HWIO_TURING_QDSP6SS_CORE_STATUS_IN          \
        in_dword_masked(HWIO_TURING_QDSP6SS_CORE_STATUS_ADDR, HWIO_TURING_QDSP6SS_CORE_STATUS_RMSK)
#define HWIO_TURING_QDSP6SS_CORE_STATUS_INM(m)      \
        in_dword_masked(HWIO_TURING_QDSP6SS_CORE_STATUS_ADDR, m)
#define HWIO_TURING_QDSP6SS_CORE_STATUS_CP0_IDLE_BMSK                                     0x4
#define HWIO_TURING_QDSP6SS_CORE_STATUS_CP0_IDLE_SHFT                                     0x2
#define HWIO_TURING_QDSP6SS_CORE_STATUS_CORE_IN_SLEEP_BMSK                                0x2
#define HWIO_TURING_QDSP6SS_CORE_STATUS_CORE_IN_SLEEP_SHFT                                0x1
#define HWIO_TURING_QDSP6SS_CORE_STATUS_CORE_STATE_BMSK                                   0x1
#define HWIO_TURING_QDSP6SS_CORE_STATUS_CORE_STATE_SHFT                                   0x0

/*----------------------------------------------------------------------------
 * MODULE: SECURITY_CONTROL_CORE
 *--------------------------------------------------------------------------*/

#define SECURITY_CONTROL_CORE_REG_BASE                                                           (SECURITY_CONTROL_BASE      + 0x00000000)
#define SECURITY_CONTROL_CORE_REG_BASE_OFFS                                                      0x00000000

#define HWIO_QFPROM_RAW_CRI_CM_PRIVATEn_ADDR(n)                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000000 + 0x4 * (n))
#define HWIO_QFPROM_RAW_CRI_CM_PRIVATEn_OFFS(n)                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000000 + 0x4 * (n))
#define HWIO_QFPROM_RAW_CRI_CM_PRIVATEn_RMSK                                                     0xffffffff
#define HWIO_QFPROM_RAW_CRI_CM_PRIVATEn_MAXn                                                             71
#define HWIO_QFPROM_RAW_CRI_CM_PRIVATEn_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_CRI_CM_PRIVATEn_ADDR(n), HWIO_QFPROM_RAW_CRI_CM_PRIVATEn_RMSK)
#define HWIO_QFPROM_RAW_CRI_CM_PRIVATEn_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_CRI_CM_PRIVATEn_ADDR(n), mask)
#define HWIO_QFPROM_RAW_CRI_CM_PRIVATEn_CRI_CM_PRIVATE_BMSK                                      0xffffffff
#define HWIO_QFPROM_RAW_CRI_CM_PRIVATEn_CRI_CM_PRIVATE_SHFT                                             0x0

#define HWIO_QFPROM_RAW_QC_SPARE_REGIONn_ADDR(n)                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000120 + 0x4 * (n))
#define HWIO_QFPROM_RAW_QC_SPARE_REGIONn_OFFS(n)                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000120 + 0x4 * (n))
#define HWIO_QFPROM_RAW_QC_SPARE_REGIONn_RMSK                                                    0xffffffff
#define HWIO_QFPROM_RAW_QC_SPARE_REGIONn_MAXn                                                             3
#define HWIO_QFPROM_RAW_QC_SPARE_REGIONn_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_QC_SPARE_REGIONn_ADDR(n), HWIO_QFPROM_RAW_QC_SPARE_REGIONn_RMSK)
#define HWIO_QFPROM_RAW_QC_SPARE_REGIONn_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_QC_SPARE_REGIONn_ADDR(n), mask)
#define HWIO_QFPROM_RAW_QC_SPARE_REGIONn_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_QC_SPARE_REGIONn_ADDR(n),val)
#define HWIO_QFPROM_RAW_QC_SPARE_REGIONn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_QC_SPARE_REGIONn_ADDR(n),mask,val,HWIO_QFPROM_RAW_QC_SPARE_REGIONn_INI(n))
#define HWIO_QFPROM_RAW_QC_SPARE_REGIONn_QC_SPARE_BMSK                                           0xffffffff
#define HWIO_QFPROM_RAW_QC_SPARE_REGIONn_QC_SPARE_SHFT                                                  0x0

#define HWIO_QFPROM_RAW_PTE_ROW0_LSB_ADDR                                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000130)
#define HWIO_QFPROM_RAW_PTE_ROW0_LSB_OFFS                                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000130)
#define HWIO_QFPROM_RAW_PTE_ROW0_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_RAW_PTE_ROW0_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_PTE_ROW0_LSB_ADDR, HWIO_QFPROM_RAW_PTE_ROW0_LSB_RMSK)
#define HWIO_QFPROM_RAW_PTE_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_PTE_ROW0_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_PTE_ROW0_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_PTE_ROW0_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_PTE_ROW0_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_PTE_ROW0_LSB_ADDR,m,v,HWIO_QFPROM_RAW_PTE_ROW0_LSB_IN)
#define HWIO_QFPROM_RAW_PTE_ROW0_LSB_PTE_DATA0_BMSK                                              0xe0000000
#define HWIO_QFPROM_RAW_PTE_ROW0_LSB_PTE_DATA0_SHFT                                                    0x1d
#define HWIO_QFPROM_RAW_PTE_ROW0_LSB_MACCHIATO_EN_BMSK                                           0x10000000
#define HWIO_QFPROM_RAW_PTE_ROW0_LSB_MACCHIATO_EN_SHFT                                                 0x1c
#define HWIO_QFPROM_RAW_PTE_ROW0_LSB_FEATURE_ID_BMSK                                              0xff00000
#define HWIO_QFPROM_RAW_PTE_ROW0_LSB_FEATURE_ID_SHFT                                                   0x14
#define HWIO_QFPROM_RAW_PTE_ROW0_LSB_JTAG_ID_BMSK                                                   0xfffff
#define HWIO_QFPROM_RAW_PTE_ROW0_LSB_JTAG_ID_SHFT                                                       0x0

#define HWIO_QFPROM_RAW_PTE_ROW0_MSB_ADDR                                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000134)
#define HWIO_QFPROM_RAW_PTE_ROW0_MSB_OFFS                                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000134)
#define HWIO_QFPROM_RAW_PTE_ROW0_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_RAW_PTE_ROW0_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_PTE_ROW0_MSB_ADDR, HWIO_QFPROM_RAW_PTE_ROW0_MSB_RMSK)
#define HWIO_QFPROM_RAW_PTE_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_PTE_ROW0_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_PTE_ROW0_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_PTE_ROW0_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_PTE_ROW0_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_PTE_ROW0_MSB_ADDR,m,v,HWIO_QFPROM_RAW_PTE_ROW0_MSB_IN)
#define HWIO_QFPROM_RAW_PTE_ROW0_MSB_PTE_DATA1_BMSK                                              0xffffffff
#define HWIO_QFPROM_RAW_PTE_ROW0_MSB_PTE_DATA1_SHFT                                                     0x0

#define HWIO_QFPROM_RAW_PTE_ROW1_LSB_ADDR                                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000138)
#define HWIO_QFPROM_RAW_PTE_ROW1_LSB_OFFS                                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000138)
#define HWIO_QFPROM_RAW_PTE_ROW1_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_RAW_PTE_ROW1_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_PTE_ROW1_LSB_ADDR, HWIO_QFPROM_RAW_PTE_ROW1_LSB_RMSK)
#define HWIO_QFPROM_RAW_PTE_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_PTE_ROW1_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_PTE_ROW1_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_PTE_ROW1_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_PTE_ROW1_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_PTE_ROW1_LSB_ADDR,m,v,HWIO_QFPROM_RAW_PTE_ROW1_LSB_IN)
#define HWIO_QFPROM_RAW_PTE_ROW1_LSB_SERIAL_NUM_BMSK                                             0xffffffff
#define HWIO_QFPROM_RAW_PTE_ROW1_LSB_SERIAL_NUM_SHFT                                                    0x0

#define HWIO_QFPROM_RAW_PTE_ROW1_MSB_ADDR                                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000013c)
#define HWIO_QFPROM_RAW_PTE_ROW1_MSB_OFFS                                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000013c)
#define HWIO_QFPROM_RAW_PTE_ROW1_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_RAW_PTE_ROW1_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_PTE_ROW1_MSB_ADDR, HWIO_QFPROM_RAW_PTE_ROW1_MSB_RMSK)
#define HWIO_QFPROM_RAW_PTE_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_PTE_ROW1_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_PTE_ROW1_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_PTE_ROW1_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_PTE_ROW1_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_PTE_ROW1_MSB_ADDR,m,v,HWIO_QFPROM_RAW_PTE_ROW1_MSB_IN)
#define HWIO_QFPROM_RAW_PTE_ROW1_MSB_PTE_DATA1_BMSK                                              0xffff0000
#define HWIO_QFPROM_RAW_PTE_ROW1_MSB_PTE_DATA1_SHFT                                                    0x10
#define HWIO_QFPROM_RAW_PTE_ROW1_MSB_CHIP_ID_BMSK                                                    0xffff
#define HWIO_QFPROM_RAW_PTE_ROW1_MSB_CHIP_ID_SHFT                                                       0x0

#define HWIO_QFPROM_RAW_PTE_ROW2_LSB_ADDR                                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000140)
#define HWIO_QFPROM_RAW_PTE_ROW2_LSB_OFFS                                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000140)
#define HWIO_QFPROM_RAW_PTE_ROW2_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_RAW_PTE_ROW2_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_PTE_ROW2_LSB_ADDR, HWIO_QFPROM_RAW_PTE_ROW2_LSB_RMSK)
#define HWIO_QFPROM_RAW_PTE_ROW2_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_PTE_ROW2_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_PTE_ROW2_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_PTE_ROW2_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_PTE_ROW2_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_PTE_ROW2_LSB_ADDR,m,v,HWIO_QFPROM_RAW_PTE_ROW2_LSB_IN)
#define HWIO_QFPROM_RAW_PTE_ROW2_LSB_PTE_DATA0_BMSK                                              0xffffffff
#define HWIO_QFPROM_RAW_PTE_ROW2_LSB_PTE_DATA0_SHFT                                                     0x0

#define HWIO_QFPROM_RAW_PTE_ROW2_MSB_ADDR                                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000144)
#define HWIO_QFPROM_RAW_PTE_ROW2_MSB_OFFS                                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000144)
#define HWIO_QFPROM_RAW_PTE_ROW2_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_RAW_PTE_ROW2_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_PTE_ROW2_MSB_ADDR, HWIO_QFPROM_RAW_PTE_ROW2_MSB_RMSK)
#define HWIO_QFPROM_RAW_PTE_ROW2_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_PTE_ROW2_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_PTE_ROW2_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_PTE_ROW2_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_PTE_ROW2_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_PTE_ROW2_MSB_ADDR,m,v,HWIO_QFPROM_RAW_PTE_ROW2_MSB_IN)
#define HWIO_QFPROM_RAW_PTE_ROW2_MSB_PTE_DATA1_BMSK                                              0xffffffff
#define HWIO_QFPROM_RAW_PTE_ROW2_MSB_PTE_DATA1_SHFT                                                     0x0

#define HWIO_QFPROM_RAW_PTE_ROW3_LSB_ADDR                                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000148)
#define HWIO_QFPROM_RAW_PTE_ROW3_LSB_OFFS                                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000148)
#define HWIO_QFPROM_RAW_PTE_ROW3_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_RAW_PTE_ROW3_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_PTE_ROW3_LSB_ADDR, HWIO_QFPROM_RAW_PTE_ROW3_LSB_RMSK)
#define HWIO_QFPROM_RAW_PTE_ROW3_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_PTE_ROW3_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_PTE_ROW3_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_PTE_ROW3_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_PTE_ROW3_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_PTE_ROW3_LSB_ADDR,m,v,HWIO_QFPROM_RAW_PTE_ROW3_LSB_IN)
#define HWIO_QFPROM_RAW_PTE_ROW3_LSB_PTE_DATA0_BMSK                                              0xffffffff
#define HWIO_QFPROM_RAW_PTE_ROW3_LSB_PTE_DATA0_SHFT                                                     0x0

#define HWIO_QFPROM_RAW_PTE_ROW3_MSB_ADDR                                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000014c)
#define HWIO_QFPROM_RAW_PTE_ROW3_MSB_OFFS                                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000014c)
#define HWIO_QFPROM_RAW_PTE_ROW3_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_RAW_PTE_ROW3_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_PTE_ROW3_MSB_ADDR, HWIO_QFPROM_RAW_PTE_ROW3_MSB_RMSK)
#define HWIO_QFPROM_RAW_PTE_ROW3_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_PTE_ROW3_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_PTE_ROW3_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_PTE_ROW3_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_PTE_ROW3_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_PTE_ROW3_MSB_ADDR,m,v,HWIO_QFPROM_RAW_PTE_ROW3_MSB_IN)
#define HWIO_QFPROM_RAW_PTE_ROW3_MSB_PTE_DATA1_BMSK                                              0xffffffff
#define HWIO_QFPROM_RAW_PTE_ROW3_MSB_PTE_DATA1_SHFT                                                     0x0

#define HWIO_QFPROM_RAW_RD_PERM_LSB_ADDR                                                         (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000150)
#define HWIO_QFPROM_RAW_RD_PERM_LSB_OFFS                                                         (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000150)
#define HWIO_QFPROM_RAW_RD_PERM_LSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_RAW_RD_PERM_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_RD_PERM_LSB_ADDR, HWIO_QFPROM_RAW_RD_PERM_LSB_RMSK)
#define HWIO_QFPROM_RAW_RD_PERM_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_RD_PERM_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_RD_PERM_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_RD_PERM_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_RD_PERM_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_RD_PERM_LSB_ADDR,m,v,HWIO_QFPROM_RAW_RD_PERM_LSB_IN)
#define HWIO_QFPROM_RAW_RD_PERM_LSB_RSVD0_BMSK                                                   0x80000000
#define HWIO_QFPROM_RAW_RD_PERM_LSB_RSVD0_SHFT                                                         0x1f
#define HWIO_QFPROM_RAW_RD_PERM_LSB_OEM_SPARE_REG30_BMSK                                         0x40000000
#define HWIO_QFPROM_RAW_RD_PERM_LSB_OEM_SPARE_REG30_SHFT                                               0x1e
#define HWIO_QFPROM_RAW_RD_PERM_LSB_OEM_SPARE_REG29_BMSK                                         0x20000000
#define HWIO_QFPROM_RAW_RD_PERM_LSB_OEM_SPARE_REG29_SHFT                                               0x1d
#define HWIO_QFPROM_RAW_RD_PERM_LSB_OEM_SPARE_REG28_BMSK                                         0x10000000
#define HWIO_QFPROM_RAW_RD_PERM_LSB_OEM_SPARE_REG28_SHFT                                               0x1c
#define HWIO_QFPROM_RAW_RD_PERM_LSB_OEM_SPARE_REG27_BMSK                                          0x8000000
#define HWIO_QFPROM_RAW_RD_PERM_LSB_OEM_SPARE_REG27_SHFT                                               0x1b
#define HWIO_QFPROM_RAW_RD_PERM_LSB_OEM_SPARE_REG26_BMSK                                          0x4000000
#define HWIO_QFPROM_RAW_RD_PERM_LSB_OEM_SPARE_REG26_SHFT                                               0x1a
#define HWIO_QFPROM_RAW_RD_PERM_LSB_PK_HASH1_BMSK                                                 0x2000000
#define HWIO_QFPROM_RAW_RD_PERM_LSB_PK_HASH1_SHFT                                                      0x19
#define HWIO_QFPROM_RAW_RD_PERM_LSB_IMAGE_ENCR_KEY1_BMSK                                          0x1000000
#define HWIO_QFPROM_RAW_RD_PERM_LSB_IMAGE_ENCR_KEY1_SHFT                                               0x18
#define HWIO_QFPROM_RAW_RD_PERM_LSB_BOOT_ROM_PATCH_BMSK                                            0x800000
#define HWIO_QFPROM_RAW_RD_PERM_LSB_BOOT_ROM_PATCH_SHFT                                                0x17
#define HWIO_QFPROM_RAW_RD_PERM_LSB_SEC_KEY_DERIVATION_KEY_BMSK                                    0x400000
#define HWIO_QFPROM_RAW_RD_PERM_LSB_SEC_KEY_DERIVATION_KEY_SHFT                                        0x16
#define HWIO_QFPROM_RAW_RD_PERM_LSB_PRI_KEY_DERIVATION_KEY_BMSK                                    0x200000
#define HWIO_QFPROM_RAW_RD_PERM_LSB_PRI_KEY_DERIVATION_KEY_SHFT                                        0x15
#define HWIO_QFPROM_RAW_RD_PERM_LSB_OEM_SEC_BOOT_BMSK                                              0x100000
#define HWIO_QFPROM_RAW_RD_PERM_LSB_OEM_SEC_BOOT_SHFT                                                  0x14
#define HWIO_QFPROM_RAW_RD_PERM_LSB_OEM_IMAGE_ENCR_KEY_BMSK                                         0x80000
#define HWIO_QFPROM_RAW_RD_PERM_LSB_OEM_IMAGE_ENCR_KEY_SHFT                                            0x13
#define HWIO_QFPROM_RAW_RD_PERM_LSB_QC_SPARE_REG18_BMSK                                             0x40000
#define HWIO_QFPROM_RAW_RD_PERM_LSB_QC_SPARE_REG18_SHFT                                                0x12
#define HWIO_QFPROM_RAW_RD_PERM_LSB_QC_SPARE_REG17_BMSK                                             0x20000
#define HWIO_QFPROM_RAW_RD_PERM_LSB_QC_SPARE_REG17_SHFT                                                0x11
#define HWIO_QFPROM_RAW_RD_PERM_LSB_QC_SPARE_REG16_BMSK                                             0x10000
#define HWIO_QFPROM_RAW_RD_PERM_LSB_QC_SPARE_REG16_SHFT                                                0x10
#define HWIO_QFPROM_RAW_RD_PERM_LSB_CM_FEAT_CONFIG_BMSK                                              0x8000
#define HWIO_QFPROM_RAW_RD_PERM_LSB_CM_FEAT_CONFIG_SHFT                                                 0xf
#define HWIO_QFPROM_RAW_RD_PERM_LSB_MEM_CONFIG_BMSK                                                  0x4000
#define HWIO_QFPROM_RAW_RD_PERM_LSB_MEM_CONFIG_SHFT                                                     0xe
#define HWIO_QFPROM_RAW_RD_PERM_LSB_CALIB_BMSK                                                       0x2000
#define HWIO_QFPROM_RAW_RD_PERM_LSB_CALIB_SHFT                                                          0xd
#define HWIO_QFPROM_RAW_RD_PERM_LSB_PK_HASH0_BMSK                                                    0x1000
#define HWIO_QFPROM_RAW_RD_PERM_LSB_PK_HASH0_SHFT                                                       0xc
#define HWIO_QFPROM_RAW_RD_PERM_LSB_FEAT_CONFIG_BMSK                                                  0x800
#define HWIO_QFPROM_RAW_RD_PERM_LSB_FEAT_CONFIG_SHFT                                                    0xb
#define HWIO_QFPROM_RAW_RD_PERM_LSB_OEM_CONFIG_BMSK                                                   0x400
#define HWIO_QFPROM_RAW_RD_PERM_LSB_OEM_CONFIG_SHFT                                                     0xa
#define HWIO_QFPROM_RAW_RD_PERM_LSB_ANTI_ROLLBACK_4_BMSK                                              0x200
#define HWIO_QFPROM_RAW_RD_PERM_LSB_ANTI_ROLLBACK_4_SHFT                                                0x9
#define HWIO_QFPROM_RAW_RD_PERM_LSB_ANTI_ROLLBACK_3_BMSK                                              0x100
#define HWIO_QFPROM_RAW_RD_PERM_LSB_ANTI_ROLLBACK_3_SHFT                                                0x8
#define HWIO_QFPROM_RAW_RD_PERM_LSB_ANTI_ROLLBACK_2_BMSK                                               0x80
#define HWIO_QFPROM_RAW_RD_PERM_LSB_ANTI_ROLLBACK_2_SHFT                                                0x7
#define HWIO_QFPROM_RAW_RD_PERM_LSB_ANTI_ROLLBACK_1_BMSK                                               0x40
#define HWIO_QFPROM_RAW_RD_PERM_LSB_ANTI_ROLLBACK_1_SHFT                                                0x6
#define HWIO_QFPROM_RAW_RD_PERM_LSB_FEC_EN_BMSK                                                        0x20
#define HWIO_QFPROM_RAW_RD_PERM_LSB_FEC_EN_SHFT                                                         0x5
#define HWIO_QFPROM_RAW_RD_PERM_LSB_WR_PERM_BMSK                                                       0x10
#define HWIO_QFPROM_RAW_RD_PERM_LSB_WR_PERM_SHFT                                                        0x4
#define HWIO_QFPROM_RAW_RD_PERM_LSB_RD_PERM_BMSK                                                        0x8
#define HWIO_QFPROM_RAW_RD_PERM_LSB_RD_PERM_SHFT                                                        0x3
#define HWIO_QFPROM_RAW_RD_PERM_LSB_PTE_BMSK                                                            0x4
#define HWIO_QFPROM_RAW_RD_PERM_LSB_PTE_SHFT                                                            0x2
#define HWIO_QFPROM_RAW_RD_PERM_LSB_QC_SPARE_REGION_BMSK                                                0x2
#define HWIO_QFPROM_RAW_RD_PERM_LSB_QC_SPARE_REGION_SHFT                                                0x1
#define HWIO_QFPROM_RAW_RD_PERM_LSB_CRI_CM_PRIVATE_BMSK                                                 0x1
#define HWIO_QFPROM_RAW_RD_PERM_LSB_CRI_CM_PRIVATE_SHFT                                                 0x0

#define HWIO_QFPROM_RAW_RD_PERM_MSB_ADDR                                                         (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000154)
#define HWIO_QFPROM_RAW_RD_PERM_MSB_OFFS                                                         (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000154)
#define HWIO_QFPROM_RAW_RD_PERM_MSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_RAW_RD_PERM_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_RD_PERM_MSB_ADDR, HWIO_QFPROM_RAW_RD_PERM_MSB_RMSK)
#define HWIO_QFPROM_RAW_RD_PERM_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_RD_PERM_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_RD_PERM_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_RD_PERM_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_RD_PERM_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_RD_PERM_MSB_ADDR,m,v,HWIO_QFPROM_RAW_RD_PERM_MSB_IN)
#define HWIO_QFPROM_RAW_RD_PERM_MSB_RSVD0_BMSK                                                   0xffffffff
#define HWIO_QFPROM_RAW_RD_PERM_MSB_RSVD0_SHFT                                                          0x0

#define HWIO_QFPROM_RAW_WR_PERM_LSB_ADDR                                                         (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000158)
#define HWIO_QFPROM_RAW_WR_PERM_LSB_OFFS                                                         (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000158)
#define HWIO_QFPROM_RAW_WR_PERM_LSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_RAW_WR_PERM_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_WR_PERM_LSB_ADDR, HWIO_QFPROM_RAW_WR_PERM_LSB_RMSK)
#define HWIO_QFPROM_RAW_WR_PERM_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_WR_PERM_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_WR_PERM_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_WR_PERM_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_WR_PERM_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_WR_PERM_LSB_ADDR,m,v,HWIO_QFPROM_RAW_WR_PERM_LSB_IN)
#define HWIO_QFPROM_RAW_WR_PERM_LSB_RSVD0_BMSK                                                   0x80000000
#define HWIO_QFPROM_RAW_WR_PERM_LSB_RSVD0_SHFT                                                         0x1f
#define HWIO_QFPROM_RAW_WR_PERM_LSB_OEM_SPARE_REG30_BMSK                                         0x40000000
#define HWIO_QFPROM_RAW_WR_PERM_LSB_OEM_SPARE_REG30_SHFT                                               0x1e
#define HWIO_QFPROM_RAW_WR_PERM_LSB_OEM_SPARE_REG29_BMSK                                         0x20000000
#define HWIO_QFPROM_RAW_WR_PERM_LSB_OEM_SPARE_REG29_SHFT                                               0x1d
#define HWIO_QFPROM_RAW_WR_PERM_LSB_OEM_SPARE_REG28_BMSK                                         0x10000000
#define HWIO_QFPROM_RAW_WR_PERM_LSB_OEM_SPARE_REG28_SHFT                                               0x1c
#define HWIO_QFPROM_RAW_WR_PERM_LSB_OEM_SPARE_REG27_BMSK                                          0x8000000
#define HWIO_QFPROM_RAW_WR_PERM_LSB_OEM_SPARE_REG27_SHFT                                               0x1b
#define HWIO_QFPROM_RAW_WR_PERM_LSB_OEM_SPARE_REG26_BMSK                                          0x4000000
#define HWIO_QFPROM_RAW_WR_PERM_LSB_OEM_SPARE_REG26_SHFT                                               0x1a
#define HWIO_QFPROM_RAW_WR_PERM_LSB_PK_HASH1_BMSK                                                 0x2000000
#define HWIO_QFPROM_RAW_WR_PERM_LSB_PK_HASH1_SHFT                                                      0x19
#define HWIO_QFPROM_RAW_WR_PERM_LSB_IMAGE_ENCR_KEY1_BMSK                                          0x1000000
#define HWIO_QFPROM_RAW_WR_PERM_LSB_IMAGE_ENCR_KEY1_SHFT                                               0x18
#define HWIO_QFPROM_RAW_WR_PERM_LSB_BOOT_ROM_PATCH_BMSK                                            0x800000
#define HWIO_QFPROM_RAW_WR_PERM_LSB_BOOT_ROM_PATCH_SHFT                                                0x17
#define HWIO_QFPROM_RAW_WR_PERM_LSB_SEC_KEY_DERIVATION_KEY_BMSK                                    0x400000
#define HWIO_QFPROM_RAW_WR_PERM_LSB_SEC_KEY_DERIVATION_KEY_SHFT                                        0x16
#define HWIO_QFPROM_RAW_WR_PERM_LSB_PRI_KEY_DERIVATION_KEY_BMSK                                    0x200000
#define HWIO_QFPROM_RAW_WR_PERM_LSB_PRI_KEY_DERIVATION_KEY_SHFT                                        0x15
#define HWIO_QFPROM_RAW_WR_PERM_LSB_OEM_SEC_BOOT_BMSK                                              0x100000
#define HWIO_QFPROM_RAW_WR_PERM_LSB_OEM_SEC_BOOT_SHFT                                                  0x14
#define HWIO_QFPROM_RAW_WR_PERM_LSB_OEM_IMAGE_ENCR_KEY_BMSK                                         0x80000
#define HWIO_QFPROM_RAW_WR_PERM_LSB_OEM_IMAGE_ENCR_KEY_SHFT                                            0x13
#define HWIO_QFPROM_RAW_WR_PERM_LSB_QC_SPARE_REG18_BMSK                                             0x40000
#define HWIO_QFPROM_RAW_WR_PERM_LSB_QC_SPARE_REG18_SHFT                                                0x12
#define HWIO_QFPROM_RAW_WR_PERM_LSB_QC_SPARE_REG17_BMSK                                             0x20000
#define HWIO_QFPROM_RAW_WR_PERM_LSB_QC_SPARE_REG17_SHFT                                                0x11
#define HWIO_QFPROM_RAW_WR_PERM_LSB_QC_SPARE_REG16_BMSK                                             0x10000
#define HWIO_QFPROM_RAW_WR_PERM_LSB_QC_SPARE_REG16_SHFT                                                0x10
#define HWIO_QFPROM_RAW_WR_PERM_LSB_CM_FEAT_CONFIG_BMSK                                              0x8000
#define HWIO_QFPROM_RAW_WR_PERM_LSB_CM_FEAT_CONFIG_SHFT                                                 0xf
#define HWIO_QFPROM_RAW_WR_PERM_LSB_MEM_CONFIG_BMSK                                                  0x4000
#define HWIO_QFPROM_RAW_WR_PERM_LSB_MEM_CONFIG_SHFT                                                     0xe
#define HWIO_QFPROM_RAW_WR_PERM_LSB_CALIB_BMSK                                                       0x2000
#define HWIO_QFPROM_RAW_WR_PERM_LSB_CALIB_SHFT                                                          0xd
#define HWIO_QFPROM_RAW_WR_PERM_LSB_PK_HASH0_BMSK                                                    0x1000
#define HWIO_QFPROM_RAW_WR_PERM_LSB_PK_HASH0_SHFT                                                       0xc
#define HWIO_QFPROM_RAW_WR_PERM_LSB_FEAT_CONFIG_BMSK                                                  0x800
#define HWIO_QFPROM_RAW_WR_PERM_LSB_FEAT_CONFIG_SHFT                                                    0xb
#define HWIO_QFPROM_RAW_WR_PERM_LSB_OEM_CONFIG_BMSK                                                   0x400
#define HWIO_QFPROM_RAW_WR_PERM_LSB_OEM_CONFIG_SHFT                                                     0xa
#define HWIO_QFPROM_RAW_WR_PERM_LSB_ANTI_ROLLBACK_4_BMSK                                              0x200
#define HWIO_QFPROM_RAW_WR_PERM_LSB_ANTI_ROLLBACK_4_SHFT                                                0x9
#define HWIO_QFPROM_RAW_WR_PERM_LSB_ANTI_ROLLBACK_3_BMSK                                              0x100
#define HWIO_QFPROM_RAW_WR_PERM_LSB_ANTI_ROLLBACK_3_SHFT                                                0x8
#define HWIO_QFPROM_RAW_WR_PERM_LSB_ANTI_ROLLBACK_2_BMSK                                               0x80
#define HWIO_QFPROM_RAW_WR_PERM_LSB_ANTI_ROLLBACK_2_SHFT                                                0x7
#define HWIO_QFPROM_RAW_WR_PERM_LSB_ANTI_ROLLBACK_1_BMSK                                               0x40
#define HWIO_QFPROM_RAW_WR_PERM_LSB_ANTI_ROLLBACK_1_SHFT                                                0x6
#define HWIO_QFPROM_RAW_WR_PERM_LSB_FEC_EN_BMSK                                                        0x20
#define HWIO_QFPROM_RAW_WR_PERM_LSB_FEC_EN_SHFT                                                         0x5
#define HWIO_QFPROM_RAW_WR_PERM_LSB_WR_PERM_BMSK                                                       0x10
#define HWIO_QFPROM_RAW_WR_PERM_LSB_WR_PERM_SHFT                                                        0x4
#define HWIO_QFPROM_RAW_WR_PERM_LSB_RD_PERM_BMSK                                                        0x8
#define HWIO_QFPROM_RAW_WR_PERM_LSB_RD_PERM_SHFT                                                        0x3
#define HWIO_QFPROM_RAW_WR_PERM_LSB_PTE_BMSK                                                            0x4
#define HWIO_QFPROM_RAW_WR_PERM_LSB_PTE_SHFT                                                            0x2
#define HWIO_QFPROM_RAW_WR_PERM_LSB_QC_SPARE_REGION_BMSK                                                0x2
#define HWIO_QFPROM_RAW_WR_PERM_LSB_QC_SPARE_REGION_SHFT                                                0x1
#define HWIO_QFPROM_RAW_WR_PERM_LSB_CRI_CM_PRIVATE_BMSK                                                 0x1
#define HWIO_QFPROM_RAW_WR_PERM_LSB_CRI_CM_PRIVATE_SHFT                                                 0x0

#define HWIO_QFPROM_RAW_WR_PERM_MSB_ADDR                                                         (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000015c)
#define HWIO_QFPROM_RAW_WR_PERM_MSB_OFFS                                                         (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000015c)
#define HWIO_QFPROM_RAW_WR_PERM_MSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_RAW_WR_PERM_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_WR_PERM_MSB_ADDR, HWIO_QFPROM_RAW_WR_PERM_MSB_RMSK)
#define HWIO_QFPROM_RAW_WR_PERM_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_WR_PERM_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_WR_PERM_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_WR_PERM_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_WR_PERM_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_WR_PERM_MSB_ADDR,m,v,HWIO_QFPROM_RAW_WR_PERM_MSB_IN)
#define HWIO_QFPROM_RAW_WR_PERM_MSB_RSVD0_BMSK                                                   0xffffffff
#define HWIO_QFPROM_RAW_WR_PERM_MSB_RSVD0_SHFT                                                          0x0

#define HWIO_QFPROM_RAW_FEC_EN_LSB_ADDR                                                          (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000160)
#define HWIO_QFPROM_RAW_FEC_EN_LSB_OFFS                                                          (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000160)
#define HWIO_QFPROM_RAW_FEC_EN_LSB_RMSK                                                          0xffffffff
#define HWIO_QFPROM_RAW_FEC_EN_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_FEC_EN_LSB_ADDR, HWIO_QFPROM_RAW_FEC_EN_LSB_RMSK)
#define HWIO_QFPROM_RAW_FEC_EN_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_FEC_EN_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_FEC_EN_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_FEC_EN_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_FEC_EN_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_FEC_EN_LSB_ADDR,m,v,HWIO_QFPROM_RAW_FEC_EN_LSB_IN)
#define HWIO_QFPROM_RAW_FEC_EN_LSB_RSVD0_BMSK                                                    0x80000000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_RSVD0_SHFT                                                          0x1f
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION30_FEC_EN_BMSK                                          0x40000000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION30_FEC_EN_SHFT                                                0x1e
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION29_FEC_EN_BMSK                                          0x20000000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION29_FEC_EN_SHFT                                                0x1d
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION28_FEC_EN_BMSK                                          0x10000000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION28_FEC_EN_SHFT                                                0x1c
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION27_FEC_EN_BMSK                                           0x8000000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION27_FEC_EN_SHFT                                                0x1b
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION26_FEC_EN_BMSK                                           0x4000000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION26_FEC_EN_SHFT                                                0x1a
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION25_FEC_EN_BMSK                                           0x2000000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION25_FEC_EN_SHFT                                                0x19
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION24_FEC_EN_BMSK                                           0x1000000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION24_FEC_EN_SHFT                                                0x18
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION23_FEC_EN_BMSK                                            0x800000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION23_FEC_EN_SHFT                                                0x17
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION22_FEC_EN_BMSK                                            0x400000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION22_FEC_EN_SHFT                                                0x16
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION21_FEC_EN_BMSK                                            0x200000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION21_FEC_EN_SHFT                                                0x15
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION20_FEC_EN_BMSK                                            0x100000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION20_FEC_EN_SHFT                                                0x14
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION19_FEC_EN_BMSK                                             0x80000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION19_FEC_EN_SHFT                                                0x13
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION18_FEC_EN_BMSK                                             0x40000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION18_FEC_EN_SHFT                                                0x12
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION17_FEC_EN_BMSK                                             0x20000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION17_FEC_EN_SHFT                                                0x11
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION16_FEC_EN_BMSK                                             0x10000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION16_FEC_EN_SHFT                                                0x10
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION15_FEC_EN_BMSK                                              0x8000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION15_FEC_EN_SHFT                                                 0xf
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION14_FEC_EN_BMSK                                              0x4000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION14_FEC_EN_SHFT                                                 0xe
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION13_FEC_EN_BMSK                                              0x2000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION13_FEC_EN_SHFT                                                 0xd
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION12_FEC_EN_BMSK                                              0x1000
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION12_FEC_EN_SHFT                                                 0xc
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION11_FEC_EN_BMSK                                               0x800
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION11_FEC_EN_SHFT                                                 0xb
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION10_FEC_EN_BMSK                                               0x400
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION10_FEC_EN_SHFT                                                 0xa
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION9_FEC_EN_BMSK                                                0x200
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION9_FEC_EN_SHFT                                                  0x9
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION8_FEC_EN_BMSK                                                0x100
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION8_FEC_EN_SHFT                                                  0x8
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION7_FEC_EN_BMSK                                                 0x80
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION7_FEC_EN_SHFT                                                  0x7
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION6_FEC_EN_BMSK                                                 0x40
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION6_FEC_EN_SHFT                                                  0x6
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION5_FEC_EN_BMSK                                                 0x20
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION5_FEC_EN_SHFT                                                  0x5
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION4_FEC_EN_BMSK                                                 0x10
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION4_FEC_EN_SHFT                                                  0x4
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION3_FEC_EN_BMSK                                                  0x8
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION3_FEC_EN_SHFT                                                  0x3
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION2_FEC_EN_BMSK                                                  0x4
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION2_FEC_EN_SHFT                                                  0x2
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION1_FEC_EN_BMSK                                                  0x2
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION1_FEC_EN_SHFT                                                  0x1
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION0_FEC_EN_BMSK                                                  0x1
#define HWIO_QFPROM_RAW_FEC_EN_LSB_REGION0_FEC_EN_SHFT                                                  0x0

#define HWIO_QFPROM_RAW_FEC_EN_MSB_ADDR                                                          (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000164)
#define HWIO_QFPROM_RAW_FEC_EN_MSB_OFFS                                                          (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000164)
#define HWIO_QFPROM_RAW_FEC_EN_MSB_RMSK                                                          0xffffffff
#define HWIO_QFPROM_RAW_FEC_EN_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_FEC_EN_MSB_ADDR, HWIO_QFPROM_RAW_FEC_EN_MSB_RMSK)
#define HWIO_QFPROM_RAW_FEC_EN_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_FEC_EN_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_FEC_EN_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_FEC_EN_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_FEC_EN_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_FEC_EN_MSB_ADDR,m,v,HWIO_QFPROM_RAW_FEC_EN_MSB_IN)
#define HWIO_QFPROM_RAW_FEC_EN_MSB_RSVD0_BMSK                                                    0xffffffff
#define HWIO_QFPROM_RAW_FEC_EN_MSB_RSVD0_SHFT                                                           0x0

#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_1_LSB_ADDR                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000168)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_1_LSB_OFFS                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000168)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_1_LSB_RMSK                                                 0xffffffff
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_1_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_ANTI_ROLLBACK_1_LSB_ADDR, HWIO_QFPROM_RAW_ANTI_ROLLBACK_1_LSB_RMSK)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_1_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_ANTI_ROLLBACK_1_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_1_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_ANTI_ROLLBACK_1_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_1_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_ANTI_ROLLBACK_1_LSB_ADDR,m,v,HWIO_QFPROM_RAW_ANTI_ROLLBACK_1_LSB_IN)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_1_LSB_XBL0_BMSK                                            0xffffffff
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_1_LSB_XBL0_SHFT                                                   0x0

#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_1_MSB_ADDR                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000016c)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_1_MSB_OFFS                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000016c)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_1_MSB_RMSK                                                 0xffffffff
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_1_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_ANTI_ROLLBACK_1_MSB_ADDR, HWIO_QFPROM_RAW_ANTI_ROLLBACK_1_MSB_RMSK)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_1_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_ANTI_ROLLBACK_1_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_1_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_ANTI_ROLLBACK_1_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_1_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_ANTI_ROLLBACK_1_MSB_ADDR,m,v,HWIO_QFPROM_RAW_ANTI_ROLLBACK_1_MSB_IN)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_1_MSB_XBL1_BMSK                                            0xffffffff
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_1_MSB_XBL1_SHFT                                                   0x0

#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_2_LSB_ADDR                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000170)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_2_LSB_OFFS                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000170)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_2_LSB_RMSK                                                 0xffffffff
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_2_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_ANTI_ROLLBACK_2_LSB_ADDR, HWIO_QFPROM_RAW_ANTI_ROLLBACK_2_LSB_RMSK)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_2_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_ANTI_ROLLBACK_2_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_2_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_ANTI_ROLLBACK_2_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_2_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_ANTI_ROLLBACK_2_LSB_ADDR,m,v,HWIO_QFPROM_RAW_ANTI_ROLLBACK_2_LSB_IN)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_2_LSB_PIL_SUBSYSTEM_31_0_BMSK                              0xffffffff
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_2_LSB_PIL_SUBSYSTEM_31_0_SHFT                                     0x0

#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_2_MSB_ADDR                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000174)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_2_MSB_OFFS                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000174)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_2_MSB_RMSK                                                 0xffffffff
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_2_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_ANTI_ROLLBACK_2_MSB_ADDR, HWIO_QFPROM_RAW_ANTI_ROLLBACK_2_MSB_RMSK)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_2_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_ANTI_ROLLBACK_2_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_2_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_ANTI_ROLLBACK_2_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_2_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_ANTI_ROLLBACK_2_MSB_ADDR,m,v,HWIO_QFPROM_RAW_ANTI_ROLLBACK_2_MSB_IN)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_2_MSB_XBL_SEC_BMSK                                         0xfe000000
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_2_MSB_XBL_SEC_SHFT                                               0x19
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_2_MSB_RPM_BMSK                                              0x1fe0000
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_2_MSB_RPM_SHFT                                                   0x11
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_2_MSB_TZ_BMSK                                                 0x1ffff
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_2_MSB_TZ_SHFT                                                     0x0

#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_LSB_ADDR                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000178)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_LSB_OFFS                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000178)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_LSB_RMSK                                                 0xffffffff
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_LSB_ADDR, HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_LSB_RMSK)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_LSB_ADDR,m,v,HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_LSB_IN)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_LSB_RSVD1_BMSK                                           0xc0000000
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_LSB_RSVD1_SHFT                                                 0x1e
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_LSB_TQS_HASH_ACTIVE_BMSK                                 0x3e000000
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_LSB_TQS_HASH_ACTIVE_SHFT                                       0x19
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_LSB_RPMB_KEY_PROVISIONED_BMSK                             0x1000000
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_LSB_RPMB_KEY_PROVISIONED_SHFT                                  0x18
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_LSB_PIL_SUBSYSTEM_47_32_BMSK                               0xffff00
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_LSB_PIL_SUBSYSTEM_47_32_SHFT                                    0x8
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_LSB_SAFESWITCH_BMSK                                            0xff
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_LSB_SAFESWITCH_SHFT                                             0x0

#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_MSB_ADDR                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000017c)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_MSB_OFFS                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000017c)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_MSB_RMSK                                                 0xffffffff
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_MSB_ADDR, HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_MSB_RMSK)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_MSB_ADDR,m,v,HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_MSB_IN)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_MSB_RSVD1_BMSK                                           0xf0000000
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_MSB_RSVD1_SHFT                                                 0x1c
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_MSB_DEVICE_CFG_BMSK                                       0xffe0000
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_MSB_DEVICE_CFG_SHFT                                            0x11
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_MSB_DEBUG_POLICY_BMSK                                       0x1f000
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_MSB_DEBUG_POLICY_SHFT                                           0xc
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_MSB_HYPERVISOR_BMSK                                           0xfff
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_3_MSB_HYPERVISOR_SHFT                                             0x0

#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_4_LSB_ADDR                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000180)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_4_LSB_OFFS                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000180)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_4_LSB_RMSK                                                 0xffffffff
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_4_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_ANTI_ROLLBACK_4_LSB_ADDR, HWIO_QFPROM_RAW_ANTI_ROLLBACK_4_LSB_RMSK)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_4_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_ANTI_ROLLBACK_4_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_4_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_ANTI_ROLLBACK_4_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_4_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_ANTI_ROLLBACK_4_LSB_ADDR,m,v,HWIO_QFPROM_RAW_ANTI_ROLLBACK_4_LSB_IN)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_4_LSB_MSS_BMSK                                             0xffff0000
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_4_LSB_MSS_SHFT                                                   0x10
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_4_LSB_MBA_BMSK                                                 0xffff
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_4_LSB_MBA_SHFT                                                    0x0

#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_4_MSB_ADDR                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000184)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_4_MSB_OFFS                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000184)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_4_MSB_RMSK                                                 0xffffffff
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_4_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_ANTI_ROLLBACK_4_MSB_ADDR, HWIO_QFPROM_RAW_ANTI_ROLLBACK_4_MSB_RMSK)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_4_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_ANTI_ROLLBACK_4_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_4_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_ANTI_ROLLBACK_4_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_4_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_ANTI_ROLLBACK_4_MSB_ADDR,m,v,HWIO_QFPROM_RAW_ANTI_ROLLBACK_4_MSB_IN)
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_4_MSB_SIMLOCK_BMSK                                         0x80000000
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_4_MSB_SIMLOCK_SHFT                                               0x1f
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_4_MSB_RSVD0_BMSK                                           0x7fffffff
#define HWIO_QFPROM_RAW_ANTI_ROLLBACK_4_MSB_RSVD0_SHFT                                                  0x0

#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_ADDR                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000188)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_OFFS                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000188)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_RMSK                                                 0xffffffff
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_ADDR, HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_RMSK)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_ADDR,m,v,HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_IN)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_DCC_DEBUG_DISABLE_BMSK                               0x80000000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_DCC_DEBUG_DISABLE_SHFT                                     0x1f
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_APPS_APB_DFD_DISABLE_BMSK                            0x40000000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_APPS_APB_DFD_DISABLE_SHFT                                  0x1e
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_ALL_DEBUG_DISABLE_BMSK                               0x20000000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_ALL_DEBUG_DISABLE_SHFT                                     0x1d
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_DEBUG_POLICY_DISABLE_BMSK                            0x10000000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_DEBUG_POLICY_DISABLE_SHFT                                  0x1c
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_RSVD2_BMSK                                            0xe000000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_RSVD2_SHFT                                                 0x19
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_MSS_HASH_INTEGRITY_CHECK_DISABLE_BMSK                 0x1000000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_MSS_HASH_INTEGRITY_CHECK_DISABLE_SHFT                      0x18
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_APPS_HASH_INTEGRITY_CHECK_DISABLE_BMSK                 0x800000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_APPS_HASH_INTEGRITY_CHECK_DISABLE_SHFT                     0x17
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_USB_SS_DISABLE_BMSK                                    0x400000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_USB_SS_DISABLE_SHFT                                        0x16
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_SW_ROT_USE_SERIAL_NUM_BMSK                             0x200000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_SW_ROT_USE_SERIAL_NUM_SHFT                                 0x15
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_DISABLE_ROT_TRANSFER_BMSK                              0x100000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_DISABLE_ROT_TRANSFER_SHFT                                  0x14
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_IMAGE_ENCRYPTION_ENABLE_BMSK                            0x80000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_IMAGE_ENCRYPTION_ENABLE_SHFT                               0x13
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_RSVD1_BMSK                                              0x60000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_RSVD1_SHFT                                                 0x11
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_PBL_USB_TYPE_C_DISABLE_BMSK                             0x10000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_PBL_USB_TYPE_C_DISABLE_SHFT                                0x10
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_PBL_LOG_DISABLE_BMSK                                     0x8000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_PBL_LOG_DISABLE_SHFT                                        0xf
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_WDOG_EN_BMSK                                             0x4000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_WDOG_EN_SHFT                                                0xe
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_SPDM_SECURE_MODE_BMSK                                    0x2000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_SPDM_SECURE_MODE_SHFT                                       0xd
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_SW_FUSE_PROG_DISABLE_BMSK                                0x1000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_SW_FUSE_PROG_DISABLE_SHFT                                   0xc
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_RSVD0_BMSK                                                0xc00
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_RSVD0_SHFT                                                  0xa
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_FAST_BOOT_BMSK                                            0x3e0
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_FAST_BOOT_SHFT                                              0x5
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_SDCC_MCLK_BOOT_FREQ_BMSK                                   0x10
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_SDCC_MCLK_BOOT_FREQ_SHFT                                    0x4
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_FORCE_USB_BOOT_DISABLE_BMSK                                 0x8
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_FORCE_USB_BOOT_DISABLE_SHFT                                 0x3
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_FORCE_DLOAD_DISABLE_BMSK                                    0x4
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_FORCE_DLOAD_DISABLE_SHFT                                    0x2
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_ENUM_TIMEOUT_BMSK                                           0x2
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_ENUM_TIMEOUT_SHFT                                           0x1
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_E_DLOAD_DISABLE_BMSK                                        0x1
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_E_DLOAD_DISABLE_SHFT                                        0x0

#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_ADDR                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000018c)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_OFFS                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000018c)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_RMSK                                                 0xffffffff
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_ADDR, HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_RMSK)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_ADDR,m,v,HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_IN)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_PIMEM_SPIDEN_DISABLE_BMSK                            0x80000000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_PIMEM_SPIDEN_DISABLE_SHFT                                  0x1f
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_WCSS_SPIDEN_DISABLE_BMSK                             0x40000000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_WCSS_SPIDEN_DISABLE_SHFT                                   0x1e
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_DAP_SPIDEN_DISABLE_BMSK                              0x20000000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_DAP_SPIDEN_DISABLE_SHFT                                    0x1d
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_APPS_SPIDEN_DISABLE_BMSK                             0x10000000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_APPS_SPIDEN_DISABLE_SHFT                                   0x1c
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_LPASS_SPNIDEN_DISABLE_BMSK                            0x8000000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_LPASS_SPNIDEN_DISABLE_SHFT                                 0x1b
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_PIMEM_SPNIDEN_DISABLE_BMSK                            0x4000000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_PIMEM_SPNIDEN_DISABLE_SHFT                                 0x1a
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_WCSS_SPNIDEN_DISABLE_BMSK                             0x2000000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_WCSS_SPNIDEN_DISABLE_SHFT                                  0x19
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_DAP_SPNIDEN_DISABLE_BMSK                              0x1000000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_DAP_SPNIDEN_DISABLE_SHFT                                   0x18
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_APPS_SPNIDEN_DISABLE_BMSK                              0x800000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_APPS_SPNIDEN_DISABLE_SHFT                                  0x17
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_MSS_NIDEN_DISABLE_BMSK                                 0x400000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_MSS_NIDEN_DISABLE_SHFT                                     0x16
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_LPASS_SENSOR_NIDEN_DISABLE_BMSK                        0x200000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_LPASS_SENSOR_NIDEN_DISABLE_SHFT                            0x15
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_PIMEM_NIDEN_DISABLE_BMSK                               0x100000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_PIMEM_NIDEN_DISABLE_SHFT                                   0x14
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_RPM_NIDEN_DISABLE_BMSK                                  0x80000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_RPM_NIDEN_DISABLE_SHFT                                     0x13
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_WCSS_NIDEN_DISABLE_BMSK                                 0x40000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_WCSS_NIDEN_DISABLE_SHFT                                    0x12
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_LPASS_NIDEN_DISABLE_BMSK                                0x20000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_LPASS_NIDEN_DISABLE_SHFT                                   0x11
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_DAP_NIDEN_DISABLE_BMSK                                  0x10000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_DAP_NIDEN_DISABLE_SHFT                                     0x10
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_APPS_NIDEN_DISABLE_BMSK                                  0x8000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_APPS_NIDEN_DISABLE_SHFT                                     0xf
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_MSS_DBGEN_DISABLE_BMSK                                   0x4000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_MSS_DBGEN_DISABLE_SHFT                                      0xe
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_A5X_ISDB_DBGEN_DISABLE_BMSK                              0x2000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_A5X_ISDB_DBGEN_DISABLE_SHFT                                 0xd
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_VENUS_0_DBGEN_DISABLE_BMSK                               0x1000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_VENUS_0_DBGEN_DISABLE_SHFT                                  0xc
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_RSVD1_BMSK                                                0x800
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_RSVD1_SHFT                                                  0xb
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_LPASS_SENSOR_DBGEN_DISABLE_BMSK                           0x400
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_LPASS_SENSOR_DBGEN_DISABLE_SHFT                             0xa
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_PIMEM_DBGEN_DISABLE_BMSK                                  0x200
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_PIMEM_DBGEN_DISABLE_SHFT                                    0x9
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_RPM_DBGEN_DISABLE_BMSK                                    0x100
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_RPM_DBGEN_DISABLE_SHFT                                      0x8
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_WCSS_DBGEN_DISABLE_BMSK                                    0x80
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_WCSS_DBGEN_DISABLE_SHFT                                     0x7
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_LPASS_Q6_DBGEN_DISABLE_BMSK                                0x40
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_LPASS_Q6_DBGEN_DISABLE_SHFT                                 0x6
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_DAP_DBGEN_DISABLE_BMSK                                     0x20
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_DAP_DBGEN_DISABLE_SHFT                                      0x5
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_APPS_DBGEN_DISABLE_BMSK                                    0x10
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_APPS_DBGEN_DISABLE_SHFT                                     0x4
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_DAP_DEVICEEN_DISABLE_BMSK                                   0x8
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_DAP_DEVICEEN_DISABLE_SHFT                                   0x3
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_RPM_DAPEN_DISABLE_BMSK                                      0x4
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_RPM_DAPEN_DISABLE_SHFT                                      0x2
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_RSVD0_BMSK                                                  0x2
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_RSVD0_SHFT                                                  0x1
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_DEBUG_BUS_DISABLE_BMSK                                      0x1
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_MSB_DEBUG_BUS_DISABLE_SHFT                                      0x0

#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_ADDR                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000190)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_OFFS                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000190)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_RMSK                                                 0xffffffff
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_ADDR, HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_RMSK)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_ADDR,m,v,HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_IN)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_RSVD1_BMSK                                           0xffff8000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_RSVD1_SHFT                                                  0xf
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_OEM_SPARE_REG30_SECURE_BMSK                              0x4000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_OEM_SPARE_REG30_SECURE_SHFT                                 0xe
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_OEM_SPARE_REG29_SECURE_BMSK                              0x2000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_OEM_SPARE_REG29_SECURE_SHFT                                 0xd
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_OEM_SPARE_REG28_SECURE_BMSK                              0x1000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_OEM_SPARE_REG28_SECURE_SHFT                                 0xc
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_OEM_SPARE_REG27_SECURE_BMSK                               0x800
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_OEM_SPARE_REG27_SECURE_SHFT                                 0xb
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_OEM_SPARE_REG26_SECURE_BMSK                               0x400
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_OEM_SPARE_REG26_SECURE_SHFT                                 0xa
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_RSVD0_BMSK                                                0x3fe
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_RSVD0_SHFT                                                  0x1
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_LPASS_SPIDEN_DISABLE_BMSK                                   0x1
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_LSB_LPASS_SPIDEN_DISABLE_SHFT                                   0x0

#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_MSB_ADDR                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000194)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_MSB_OFFS                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000194)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_MSB_RMSK                                                 0xffffffff
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_MSB_ADDR, HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_MSB_RMSK)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_MSB_ADDR,m,v,HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_MSB_IN)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_MSB_OEM_PRODUCT_ID_BMSK                                  0xffff0000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_MSB_OEM_PRODUCT_ID_SHFT                                        0x10
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_MSB_OEM_HW_ID_BMSK                                           0xffff
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW1_MSB_OEM_HW_ID_SHFT                                              0x0

#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW2_LSB_ADDR                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000198)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW2_LSB_OFFS                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000198)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW2_LSB_RMSK                                                 0xffffffff
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW2_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_CONFIG_ROW2_LSB_ADDR, HWIO_QFPROM_RAW_OEM_CONFIG_ROW2_LSB_RMSK)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW2_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_CONFIG_ROW2_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW2_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_OEM_CONFIG_ROW2_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW2_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_OEM_CONFIG_ROW2_LSB_ADDR,m,v,HWIO_QFPROM_RAW_OEM_CONFIG_ROW2_LSB_IN)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW2_LSB_PERIPH_VID_BMSK                                      0xffff0000
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW2_LSB_PERIPH_VID_SHFT                                            0x10
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW2_LSB_PERIPH_PID_BMSK                                          0xffff
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW2_LSB_PERIPH_PID_SHFT                                             0x0

#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW2_MSB_ADDR                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000019c)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW2_MSB_OFFS                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000019c)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW2_MSB_RMSK                                                 0xffffffff
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW2_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_CONFIG_ROW2_MSB_ADDR, HWIO_QFPROM_RAW_OEM_CONFIG_ROW2_MSB_RMSK)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW2_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_CONFIG_ROW2_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW2_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_OEM_CONFIG_ROW2_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW2_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_OEM_CONFIG_ROW2_MSB_ADDR,m,v,HWIO_QFPROM_RAW_OEM_CONFIG_ROW2_MSB_IN)
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW2_MSB_RSVD0_BMSK                                           0xffffff00
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW2_MSB_RSVD0_SHFT                                                  0x8
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW2_MSB_ANTI_ROLLBACK_FEATURE_EN_BMSK                              0xff
#define HWIO_QFPROM_RAW_OEM_CONFIG_ROW2_MSB_ANTI_ROLLBACK_FEATURE_EN_SHFT                               0x0

#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_ADDR                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001a0)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_OFFS                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001a0)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_RMSK                                                0xffffffff
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_ADDR, HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_RMSK)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_ADDR,m,v,HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_IN)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_UFS_SW_CONTROL_DISABLE_BMSK                         0x80000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_UFS_SW_CONTROL_DISABLE_SHFT                               0x1f
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_RSVD2_BMSK                                          0x40000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_RSVD2_SHFT                                                0x1e
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_RSVD1_BMSK                                          0x20000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_RSVD1_SHFT                                                0x1d
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_GFX3D_FREQ_LIMIT_VAL_BMSK                           0x1fe00000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_GFX3D_FREQ_LIMIT_VAL_SHFT                                 0x15
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_MDSS_RESOLUTION_LIMIT_BMSK                            0x180000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_MDSS_RESOLUTION_LIMIT_SHFT                                0x13
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_VENUS_HEVC_ENCODE_DISABLE_BMSK                         0x40000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_VENUS_HEVC_ENCODE_DISABLE_SHFT                            0x12
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_VENUS_HEVC_DECODE_DISABLE_BMSK                         0x20000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_VENUS_HEVC_DECODE_DISABLE_SHFT                            0x11
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_VENUS_4K_DISABLE_BMSK                                  0x10000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_VENUS_4K_DISABLE_SHFT                                     0x10
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_VP8_DECODER_DISABLE_BMSK                                0x8000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_VP8_DECODER_DISABLE_SHFT                                   0xf
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_VP8_ENCODER_DISABLE_BMSK                                0x4000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_VP8_ENCODER_DISABLE_SHFT                                   0xe
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_HDMI_DP_DISABLE_BMSK                                    0x2000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_HDMI_DP_DISABLE_SHFT                                       0xd
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_HDCP_DISABLE_BMSK                                       0x1000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_HDCP_DISABLE_SHFT                                          0xc
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_MDP_APICAL_LTC_DISABLE_BMSK                              0x800
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_MDP_APICAL_LTC_DISABLE_SHFT                                0xb
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_HDCP_GLOBAL_KEY_SPLIT2_DISABLE_BMSK                      0x400
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_HDCP_GLOBAL_KEY_SPLIT2_DISABLE_SHFT                        0xa
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_DSI_1_DISABLE_BMSK                                       0x200
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_DSI_1_DISABLE_SHFT                                         0x9
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_USB2_DISABLE_BMSK                                        0x100
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_USB2_DISABLE_SHFT                                          0x8
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_RSVD0_BMSK                                                0x80
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_RSVD0_SHFT                                                 0x7
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_CSID_DPCM_14_DISABLE_BMSK                                 0x40
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_CSID_DPCM_14_DISABLE_SHFT                                  0x6
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_ISP_1_DISABLE_BMSK                                        0x20
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_ISP_1_DISABLE_SHFT                                         0x5
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_CSID_3_DISABLE_BMSK                                       0x10
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_CSID_3_DISABLE_SHFT                                        0x4
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_CSID_2_DISABLE_BMSK                                        0x8
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_CSID_2_DISABLE_SHFT                                        0x3
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_BOOT_ROM_PATCH_DISABLE_BMSK                                0x7
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_LSB_BOOT_ROM_PATCH_DISABLE_SHFT                                0x0

#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_ADDR                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001a4)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_OFFS                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001a4)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_RMSK                                                0xffffffff
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_ADDR, HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_RMSK)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_ADDR,m,v,HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_IN)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_ICE_FORCE_HW_KEY1_BMSK                              0x80000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_ICE_FORCE_HW_KEY1_SHFT                                    0x1f
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_ICE_FORCE_HW_KEY0_BMSK                              0x40000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_ICE_FORCE_HW_KEY0_SHFT                                    0x1e
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_ICE_DISABLE_BMSK                                    0x20000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_ICE_DISABLE_SHFT                                          0x1d
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_RSVD2_BMSK                                          0x10000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_RSVD2_SHFT                                                0x1c
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_RSVD1_BMSK                                           0x8000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_RSVD1_SHFT                                                0x1b
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_LPASS_SENSOR_DISABLE_BMSK                            0x4000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_LPASS_SENSOR_DISABLE_SHFT                                 0x1a
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_LPASS_ISLAND_MODE_Q6_CLK_DISABLE_BMSK                0x2000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_LPASS_ISLAND_MODE_Q6_CLK_DISABLE_SHFT                     0x19
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_LPASS_SW_ISLAND_MODE_DISABLE_BMSK                    0x1000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_LPASS_SW_ISLAND_MODE_DISABLE_SHFT                         0x18
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_LPASS_EFUSE_TESTBUS_READ_DISABLE_BMSK                 0x800000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_LPASS_EFUSE_TESTBUS_READ_DISABLE_SHFT                     0x17
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_APS_RESET_DISABLE_BMSK                                0x400000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_APS_RESET_DISABLE_SHFT                                    0x16
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_HVX_DISABLE_BMSK                                      0x200000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_HVX_DISABLE_SHFT                                          0x15
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_APB2JTAG_DISABLE_BMSK                                 0x100000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_APB2JTAG_DISABLE_SHFT                                     0x14
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_RSVD6_BMSK                                             0x80000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_RSVD6_SHFT                                                0x13
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_STACKED_MEMORY_ID_BMSK                                 0x7c000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_STACKED_MEMORY_ID_SHFT                                     0xe
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_PRNG_TESTMODE_DISABLE_BMSK                              0x2000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_PRNG_TESTMODE_DISABLE_SHFT                                 0xd
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_CDSP_DISABLE_BMSK                                       0x1000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_CDSP_DISABLE_SHFT                                          0xc
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_MOCHA_PART_BMSK                                          0x800
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_MOCHA_PART_SHFT                                            0xb
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_RSVD5_BMSK                                               0x400
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_RSVD5_SHFT                                                 0xa
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_RSVD4_BMSK                                               0x200
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_RSVD4_SHFT                                                 0x9
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_RSVD3_BMSK                                               0x1e0
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_RSVD3_SHFT                                                 0x5
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_CM_FEAT_CONFIG_DISABLE_BMSK                               0x10
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_CM_FEAT_CONFIG_DISABLE_SHFT                                0x4
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_VFE_RESOLUTION_LIMIT_BMSK                                  0x8
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_VFE_RESOLUTION_LIMIT_SHFT                                  0x3
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_GLD_PDX_FIFO_NIU_BMSK                                      0x4
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_GLD_PDX_FIFO_NIU_SHFT                                      0x2
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_RSVD0_BMSK                                                 0x2
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_RSVD0_SHFT                                                 0x1
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_VP9_DECODER_DISABLE_BMSK                                   0x1
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW0_MSB_VP9_DECODER_DISABLE_SHFT                                   0x0

#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_ADDR                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001a8)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_OFFS                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001a8)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_RMSK                                                0xffffffff
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_ADDR, HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_RMSK)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_ADDR,m,v,HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_IN)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_MDSP_FW_DISABLE_BMSK                                0xfff00000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_MDSP_FW_DISABLE_SHFT                                      0x14
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_RSVD0_BMSK                                             0x80000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_RSVD0_SHFT                                                0x13
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_NAV_DISABLE_BMSK                                       0x40000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_NAV_DISABLE_SHFT                                          0x12
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_SYS_APCCCFGNMFI_BMSK                                   0x20000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_SYS_APCCCFGNMFI_SHFT                                      0x11
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_GLD_PDX_FIFO_ACE1_BMSK                                 0x10000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_GLD_PDX_FIFO_ACE1_SHFT                                    0x10
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_GLD_PDX_FIFO_ACE0_BMSK                                  0x8000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_GLD_PDX_FIFO_ACE0_SHFT                                     0xf
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_MODEM_FEATURE_DISABLE_SPARE_BMSK                        0x7fe0
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_MODEM_FEATURE_DISABLE_SPARE_SHFT                           0x5
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_MODEM_FEATURE_DISABLE_SLICE_BMSK                          0x1f
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_LSB_MODEM_FEATURE_DISABLE_SLICE_SHFT                           0x0

#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_ADDR                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001ac)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_OFFS                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001ac)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_RMSK                                                0xffffffff
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_ADDR, HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_RMSK)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_ADDR,m,v,HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_IN)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_SYS_APCX_SYSBARDISABLE_BMSK                         0x80000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_SYS_APCX_SYSBARDISABLE_SHFT                               0x1f
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_SYS_APCSCFGAPMBOOTONMX_BMSK                         0x60000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_SYS_APCSCFGAPMBOOTONMX_SHFT                               0x1d
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_SYS_APCCCFGCPUPRESENT_N_BMSK                        0x1fe00000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_SYS_APCCCFGCPUPRESENT_N_SHFT                              0x15
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_APPS_ACG_DISABLE_BMSK                                 0x100000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_APPS_ACG_DISABLE_SHFT                                     0x14
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_RSVD1_BMSK                                             0xf0000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_RSVD1_SHFT                                                0x10
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_MODEM_VU_DISABLE_BMSK                                   0xffff
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW1_MSB_MODEM_VU_DISABLE_SHFT                                      0x0

#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_ADDR                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001b0)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_OFFS                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001b0)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_RMSK                                                0xffffffff
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_ADDR, HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_RMSK)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_ADDR,m,v,HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_IN)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_APPS_SPNIDEN_DISABLE_BMSK                        0x80000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_APPS_SPNIDEN_DISABLE_SHFT                              0x1f
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_MSS_NIDEN_DISABLE_BMSK                           0x40000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_MSS_NIDEN_DISABLE_SHFT                                 0x1e
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_LPASS_SENSOR_NIDEN_DISABLE_BMSK                  0x20000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_LPASS_SENSOR_NIDEN_DISABLE_SHFT                        0x1d
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_PIMEM_NIDEN_DISABLE_BMSK                         0x10000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_PIMEM_NIDEN_DISABLE_SHFT                               0x1c
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_RPM_NIDEN_DISABLE_BMSK                            0x8000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_RPM_NIDEN_DISABLE_SHFT                                 0x1b
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_WCSS_NIDEN_DISABLE_BMSK                           0x4000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_WCSS_NIDEN_DISABLE_SHFT                                0x1a
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_LPASS_NIDEN_DISABLE_BMSK                          0x2000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_LPASS_NIDEN_DISABLE_SHFT                               0x19
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_DAP_NIDEN_DISABLE_BMSK                            0x1000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_DAP_NIDEN_DISABLE_SHFT                                 0x18
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_APPS_NIDEN_DISABLE_BMSK                            0x800000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_APPS_NIDEN_DISABLE_SHFT                                0x17
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_MSS_DBGEN_DISABLE_BMSK                             0x400000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_MSS_DBGEN_DISABLE_SHFT                                 0x16
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_A5X_ISDB_DBGEN_DISABLE_BMSK                        0x200000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_A5X_ISDB_DBGEN_DISABLE_SHFT                            0x15
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_VENUS_0_DBGEN_DISABLE_BMSK                         0x100000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_VENUS_0_DBGEN_DISABLE_SHFT                             0x14
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_TURING_EFUSE_TESTBUS_READ_DISABLE_BMSK                 0x80000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_TURING_EFUSE_TESTBUS_READ_DISABLE_SHFT                    0x13
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_LPASS_SENSOR_DBGEN_DISABLE_BMSK                     0x40000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_LPASS_SENSOR_DBGEN_DISABLE_SHFT                        0x12
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_PIMEM_DBGEN_DISABLE_BMSK                            0x20000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_PIMEM_DBGEN_DISABLE_SHFT                               0x11
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_RPM_DBGEN_DISABLE_BMSK                              0x10000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_RPM_DBGEN_DISABLE_SHFT                                 0x10
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_WCSS_DBGEN_DISABLE_BMSK                              0x8000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_WCSS_DBGEN_DISABLE_SHFT                                 0xf
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_LPASS_Q6_DBGEN_DISABLE_BMSK                          0x4000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_LPASS_Q6_DBGEN_DISABLE_SHFT                             0xe
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_DAP_DBGEN_DISABLE_BMSK                               0x2000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_DAP_DBGEN_DISABLE_SHFT                                  0xd
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_APPS_DBGEN_DISABLE_BMSK                              0x1000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_APPS_DBGEN_DISABLE_SHFT                                 0xc
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_DAP_DEVICEEN_DISABLE_BMSK                             0x800
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_DAP_DEVICEEN_DISABLE_SHFT                               0xb
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_RPM_DAPEN_DISABLE_BMSK                                0x400
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_RPM_DAPEN_DISABLE_SHFT                                  0xa
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_DSI_0_DISABLE_BMSK                                       0x200
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_DSI_0_DISABLE_SHFT                                         0x9
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_DEBUG_BUS_DISABLE_BMSK                                0x100
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_DEBUG_BUS_DISABLE_SHFT                                  0x8
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_DCC_DEBUG_DISABLE_BMSK                                 0x80
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_DCC_DEBUG_DISABLE_SHFT                                  0x7
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_APPS_APB_DFD_DISABLE_BMSK                              0x40
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_APPS_APB_DFD_DISABLE_SHFT                               0x6
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_GPMU_NIDEN_DISABLE_BMSK                                0x20
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_GPMU_NIDEN_DISABLE_SHFT                                 0x5
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_GPMU_DBGEN_DISABLE_BMSK                                0x10
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_GPMU_DBGEN_DISABLE_SHFT                                 0x4
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_GPMU_DAPEN_DISABLE_BMSK                                 0x8
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QC_GPMU_DAPEN_DISABLE_SHFT                                 0x3
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QDI_SPMI_DISABLE_BMSK                                      0x4
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_QDI_SPMI_DISABLE_SHFT                                      0x2
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_SM_BIST_DISABLE_BMSK                                       0x2
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_SM_BIST_DISABLE_SHFT                                       0x1
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_TIC_DISABLE_BMSK                                           0x1
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_LSB_TIC_DISABLE_SHFT                                           0x0

#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_ADDR                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001b4)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_OFFS                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001b4)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_RMSK                                                0xffffffff
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_ADDR, HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_RMSK)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_ADDR,m,v,HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_IN)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_SYS_APCCCFGEND_BMSK                                 0x80000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_SYS_APCCCFGEND_SHFT                                       0x1f
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_SYS_APCCCP15SDISABLE_BMSK                           0x40000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_SYS_APCCCP15SDISABLE_SHFT                                 0x1e
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_SYS_APCCCFGTE_BMSK                                  0x20000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_SYS_APCCCFGTE_SHFT                                        0x1d
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_SILVER_PLL_MAX_FREQ_LVAL_BMSK                       0x1fe00000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_SILVER_PLL_MAX_FREQ_LVAL_SHFT                             0x15
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_APPS_BOOT_FSM_FUSE_BMSK                               0x1c0000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_APPS_BOOT_FSM_FUSE_SHFT                                   0x12
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_GOLD_PLL_MAX_FREQ_LVAL_BMSK                            0x3fc00
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_GOLD_PLL_MAX_FREQ_LVAL_SHFT                                0xa
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_QC_A5X_ISDB_SECURE_DBGEN_DISABLE_BMSK                    0x200
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_QC_A5X_ISDB_SECURE_DBGEN_DISABLE_SHFT                      0x9
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_QC_LPASS_SPIDEN_DISABLE_BMSK                             0x100
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_QC_LPASS_SPIDEN_DISABLE_SHFT                               0x8
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_QC_PIMEM_SPIDEN_DISABLE_BMSK                              0x80
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_QC_PIMEM_SPIDEN_DISABLE_SHFT                               0x7
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_QC_WCSS_SPIDEN_DISABLE_BMSK                               0x40
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_QC_WCSS_SPIDEN_DISABLE_SHFT                                0x6
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_QC_DAP_SPIDEN_DISABLE_BMSK                                0x20
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_QC_DAP_SPIDEN_DISABLE_SHFT                                 0x5
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_QC_APPS_SPIDEN_DISABLE_BMSK                               0x10
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_QC_APPS_SPIDEN_DISABLE_SHFT                                0x4
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_QC_LPASS_SPNIDEN_DISABLE_BMSK                              0x8
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_QC_LPASS_SPNIDEN_DISABLE_SHFT                              0x3
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_QC_PIMEM_SPNIDEN_DISABLE_BMSK                              0x4
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_QC_PIMEM_SPNIDEN_DISABLE_SHFT                              0x2
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_QC_WCSS_SPNIDEN_DISABLE_BMSK                               0x2
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_QC_WCSS_SPNIDEN_DISABLE_SHFT                               0x1
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_QC_DAP_SPNIDEN_DISABLE_BMSK                                0x1
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW2_MSB_QC_DAP_SPNIDEN_DISABLE_SHFT                                0x0

#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_LSB_ADDR                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001b8)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_LSB_OFFS                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001b8)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_LSB_RMSK                                                0xffffffff
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_LSB_ADDR, HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_LSB_RMSK)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_LSB_ADDR,m,v,HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_LSB_IN)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_LSB_TAP_GEN_SPARE_INSTR_DISABLE_13_0_BMSK               0xfffc0000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_LSB_TAP_GEN_SPARE_INSTR_DISABLE_13_0_SHFT                     0x12
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_LSB_TAP_INSTR_DISABLE_BMSK                                 0x3ffff
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_LSB_TAP_INSTR_DISABLE_SHFT                                     0x0

#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_ADDR                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001bc)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_OFFS                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001bc)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_RMSK                                                0xffffffff
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_ADDR, HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_RMSK)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_ADDR,m,v,HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_IN)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_SEC_TAP_ACCESS_DISABLE_BMSK                         0xfffc0000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_SEC_TAP_ACCESS_DISABLE_SHFT                               0x12
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_TAP_GEN_SPARE_INSTR_DISABLE_31_14_BMSK                 0x3ffff
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW3_MSB_TAP_GEN_SPARE_INSTR_DISABLE_31_14_SHFT                     0x0

#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_ADDR                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001c0)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_OFFS                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001c0)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_RMSK                                                0xffffffff
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_ADDR, HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_RMSK)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_ADDR,m,v,HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_IN)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_MODEM_PBL_PATCH_VERSION_BMSK                        0xfe000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_MODEM_PBL_PATCH_VERSION_SHFT                              0x19
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_APPS_PBL_PATCH_VERSION_BMSK                          0x1fc0000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_APPS_PBL_PATCH_VERSION_SHFT                               0x12
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_APPS_PBL_BOOT_SPEED_BMSK                               0x30000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_APPS_PBL_BOOT_SPEED_SHFT                                  0x10
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_MODEM_PBL_BOOT_BMSK                                     0x8000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_MODEM_PBL_BOOT_SHFT                                        0xf
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_RSVD1_BMSK                                              0x4000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_RSVD1_SHFT                                                 0xe
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_APPS_BOOT_FROM_ROM_BMSK                                 0x2000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_APPS_BOOT_FROM_ROM_SHFT                                    0xd
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_RSVD0_BMSK                                              0x1000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_RSVD0_SHFT                                                 0xc
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_MODEM_BOOT_FROM_ROM_BMSK                                 0x800
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_MODEM_BOOT_FROM_ROM_SHFT                                   0xb
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_MSA_ENA_BMSK                                             0x400
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_MSA_ENA_SHFT                                               0xa
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_FORCE_MSA_AUTH_EN_BMSK                                   0x200
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_FORCE_MSA_AUTH_EN_SHFT                                     0x9
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_ARM_CE_DISABLE_USAGE_BMSK                                0x100
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_ARM_CE_DISABLE_USAGE_SHFT                                  0x8
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_BOOT_ROM_CFG_BMSK                                         0xff
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_LSB_BOOT_ROM_CFG_SHFT                                          0x0

#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_MSB_ADDR                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001c4)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_MSB_OFFS                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001c4)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_MSB_RMSK                                                0xffffffff
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_MSB_ADDR, HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_MSB_RMSK)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_MSB_ADDR,m,v,HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_MSB_IN)
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_MSB_APPS_BOOT_TRIGGER_DISABLE_BMSK                      0x80000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_MSB_APPS_BOOT_TRIGGER_DISABLE_SHFT                            0x1f
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_MSB_PBL_QSEE_BOOT_FLOW_DISABLE_BMSK                     0x40000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_MSB_PBL_QSEE_BOOT_FLOW_DISABLE_SHFT                           0x1e
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_MSB_XBL_SEC_AUTH_DISABLE_BMSK                           0x20000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_MSB_XBL_SEC_AUTH_DISABLE_SHFT                                 0x1d
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_MSB_MSM_PKG_TYPE_BMSK                                   0x10000000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_MSB_MSM_PKG_TYPE_SHFT                                         0x1c
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_MSB_RSVD3_BMSK                                           0xffc0000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_MSB_RSVD3_SHFT                                                0x12
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_MSB_FOUNDRY_ID_BMSK                                        0x3c000
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_MSB_FOUNDRY_ID_SHFT                                            0xe
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_MSB_PLL_CFG_BMSK                                            0x3ff0
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_MSB_PLL_CFG_SHFT                                               0x4
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_MSB_APPS_PBL_PLL_CTRL_BMSK                                     0xf
#define HWIO_QFPROM_RAW_FEAT_CONFIG_ROW4_MSB_APPS_PBL_PLL_CTRL_SHFT                                     0x0

#define HWIO_QFPROM_RAW_PK_HASH0_ROWn_LSB_ADDR(n)                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001c8 + 0x8 * (n))
#define HWIO_QFPROM_RAW_PK_HASH0_ROWn_LSB_OFFS(n)                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001c8 + 0x8 * (n))
#define HWIO_QFPROM_RAW_PK_HASH0_ROWn_LSB_RMSK                                                   0xffffffff
#define HWIO_QFPROM_RAW_PK_HASH0_ROWn_LSB_MAXn                                                            3
#define HWIO_QFPROM_RAW_PK_HASH0_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_PK_HASH0_ROWn_LSB_ADDR(n), HWIO_QFPROM_RAW_PK_HASH0_ROWn_LSB_RMSK)
#define HWIO_QFPROM_RAW_PK_HASH0_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_PK_HASH0_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_PK_HASH0_ROWn_LSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_PK_HASH0_ROWn_LSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_PK_HASH0_ROWn_LSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_PK_HASH0_ROWn_LSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_PK_HASH0_ROWn_LSB_INI(n))
#define HWIO_QFPROM_RAW_PK_HASH0_ROWn_LSB_HASH_DATA0_BMSK                                        0xffffffff
#define HWIO_QFPROM_RAW_PK_HASH0_ROWn_LSB_HASH_DATA0_SHFT                                               0x0

#define HWIO_QFPROM_RAW_PK_HASH0_ROWn_MSB_ADDR(n)                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001cc + 0x8 * (n))
#define HWIO_QFPROM_RAW_PK_HASH0_ROWn_MSB_OFFS(n)                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001cc + 0x8 * (n))
#define HWIO_QFPROM_RAW_PK_HASH0_ROWn_MSB_RMSK                                                   0xffffffff
#define HWIO_QFPROM_RAW_PK_HASH0_ROWn_MSB_MAXn                                                            3
#define HWIO_QFPROM_RAW_PK_HASH0_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_PK_HASH0_ROWn_MSB_ADDR(n), HWIO_QFPROM_RAW_PK_HASH0_ROWn_MSB_RMSK)
#define HWIO_QFPROM_RAW_PK_HASH0_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_PK_HASH0_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_PK_HASH0_ROWn_MSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_PK_HASH0_ROWn_MSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_PK_HASH0_ROWn_MSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_PK_HASH0_ROWn_MSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_PK_HASH0_ROWn_MSB_INI(n))
#define HWIO_QFPROM_RAW_PK_HASH0_ROWn_MSB_HASH_DATA1_BMSK                                        0xffffffff
#define HWIO_QFPROM_RAW_PK_HASH0_ROWn_MSB_HASH_DATA1_SHFT                                               0x0

#define HWIO_QFPROM_RAW_CALIB_ROW0_LSB_ADDR                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001e8)
#define HWIO_QFPROM_RAW_CALIB_ROW0_LSB_OFFS                                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001e8)
#define HWIO_QFPROM_RAW_CALIB_ROW0_LSB_RMSK                                                      0xffff803e
#define HWIO_QFPROM_RAW_CALIB_ROW0_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW0_LSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW0_LSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW0_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW0_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW0_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW0_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW0_LSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW0_LSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW0_LSB_LMH_CS_FUSES_SLOPE_16_0_BMSK                              0xffff8000
#define HWIO_QFPROM_RAW_CALIB_ROW0_LSB_LMH_CS_FUSES_SLOPE_16_0_SHFT                                     0xf
#define HWIO_QFPROM_RAW_CALIB_ROW0_LSB_MSS_Q6SS0_LDO_VREF_TRIM_BMSK                                    0x3e
#define HWIO_QFPROM_RAW_CALIB_ROW0_LSB_MSS_Q6SS0_LDO_VREF_TRIM_SHFT                                     0x1

#define HWIO_QFPROM_RAW_CALIB_ROW0_MSB_ADDR                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001ec)
#define HWIO_QFPROM_RAW_CALIB_ROW0_MSB_OFFS                                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001ec)
#define HWIO_QFPROM_RAW_CALIB_ROW0_MSB_RMSK                                                      0xffffffff
#define HWIO_QFPROM_RAW_CALIB_ROW0_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW0_MSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW0_MSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW0_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW0_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW0_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW0_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW0_MSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW0_MSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW0_MSB_LMH_CS_FUSES_INTERCEPT_8_0_BMSK                           0xff800000
#define HWIO_QFPROM_RAW_CALIB_ROW0_MSB_LMH_CS_FUSES_INTERCEPT_8_0_SHFT                                 0x17
#define HWIO_QFPROM_RAW_CALIB_ROW0_MSB_LMH_CS_FUSES_SLOPE_39_17_BMSK                               0x7fffff
#define HWIO_QFPROM_RAW_CALIB_ROW0_MSB_LMH_CS_FUSES_SLOPE_39_17_SHFT                                    0x0

#define HWIO_QFPROM_RAW_CALIB_ROW1_LSB_ADDR                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001f0)
#define HWIO_QFPROM_RAW_CALIB_ROW1_LSB_OFFS                                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001f0)
#define HWIO_QFPROM_RAW_CALIB_ROW1_LSB_RMSK                                                      0xffffffff
#define HWIO_QFPROM_RAW_CALIB_ROW1_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW1_LSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW1_LSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW1_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW1_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW1_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW1_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW1_LSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW1_LSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW1_LSB_LMH_FUSES_AMP_COMP_0_BMSK                                 0x80000000
#define HWIO_QFPROM_RAW_CALIB_ROW1_LSB_LMH_FUSES_AMP_COMP_0_SHFT                                       0x1f
#define HWIO_QFPROM_RAW_CALIB_ROW1_LSB_LMH_CS_FUSES_INTERCEPT_39_9_BMSK                          0x7fffffff
#define HWIO_QFPROM_RAW_CALIB_ROW1_LSB_LMH_CS_FUSES_INTERCEPT_39_9_SHFT                                 0x0

#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_ADDR                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001f4)
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_OFFS                                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001f4)
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_RMSK                                                      0xffffffff
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW1_MSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW1_MSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW1_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW1_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW1_MSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW1_MSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_SPARE0_BMSK                                               0x80000000
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_SPARE0_SHFT                                                     0x1f
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_REFGEN_WEST_BGV_TRIM_BMSK                                 0x7f800000
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_REFGEN_WEST_BGV_TRIM_SHFT                                       0x17
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_REFGEN_EAST_BGV_TRIM_BMSK                                   0x7f8000
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_REFGEN_EAST_BGV_TRIM_SHFT                                        0xf
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_BANDGAP_TRIM_BMSK                                             0x7f00
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_BANDGAP_TRIM_SHFT                                                0x8
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_GPU_LDOVREFTRIM_BMSK                                            0xf8
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_GPU_LDOVREFTRIM_SHFT                                             0x3
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_LMH_FUSES_AMP_COMP_3_1_BMSK                                      0x7
#define HWIO_QFPROM_RAW_CALIB_ROW1_MSB_LMH_FUSES_AMP_COMP_3_1_SHFT                                      0x0

#define HWIO_QFPROM_RAW_CALIB_ROW2_LSB_ADDR                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001f8)
#define HWIO_QFPROM_RAW_CALIB_ROW2_LSB_OFFS                                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001f8)
#define HWIO_QFPROM_RAW_CALIB_ROW2_LSB_RMSK                                                      0xffffffff
#define HWIO_QFPROM_RAW_CALIB_ROW2_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW2_LSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW2_LSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW2_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW2_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW2_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW2_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW2_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW2_LSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW2_LSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW2_LSB_GPU_LMH_CS_FUSES_INTERCEPT_HM_1_0_BMSK                    0xc0000000
#define HWIO_QFPROM_RAW_CALIB_ROW2_LSB_GPU_LMH_CS_FUSES_INTERCEPT_HM_1_0_SHFT                          0x1e
#define HWIO_QFPROM_RAW_CALIB_ROW2_LSB_GPU_LMH_CS_FUSES_SLOPE_SPTP_BMSK                          0x3ff00000
#define HWIO_QFPROM_RAW_CALIB_ROW2_LSB_GPU_LMH_CS_FUSES_SLOPE_SPTP_SHFT                                0x14
#define HWIO_QFPROM_RAW_CALIB_ROW2_LSB_GPU_LMH_CS_FUSES_SLOPE_RAC_BMSK                              0xffc00
#define HWIO_QFPROM_RAW_CALIB_ROW2_LSB_GPU_LMH_CS_FUSES_SLOPE_RAC_SHFT                                  0xa
#define HWIO_QFPROM_RAW_CALIB_ROW2_LSB_GPU_LMH_CS_FUSES_SLOPE_HM_BMSK                                 0x3ff
#define HWIO_QFPROM_RAW_CALIB_ROW2_LSB_GPU_LMH_CS_FUSES_SLOPE_HM_SHFT                                   0x0

#define HWIO_QFPROM_RAW_CALIB_ROW2_MSB_ADDR                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x000001fc)
#define HWIO_QFPROM_RAW_CALIB_ROW2_MSB_OFFS                                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000001fc)
#define HWIO_QFPROM_RAW_CALIB_ROW2_MSB_RMSK                                                      0xffffffff
#define HWIO_QFPROM_RAW_CALIB_ROW2_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW2_MSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW2_MSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW2_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW2_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW2_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW2_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW2_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW2_MSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW2_MSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW2_MSB_GPU_LMH_CS_FUSES_AMP_COMP_BMSK                            0xf0000000
#define HWIO_QFPROM_RAW_CALIB_ROW2_MSB_GPU_LMH_CS_FUSES_AMP_COMP_SHFT                                  0x1c
#define HWIO_QFPROM_RAW_CALIB_ROW2_MSB_GPU_LMH_CS_FUSES_INTERCEPT_SPTP_BMSK                       0xffc0000
#define HWIO_QFPROM_RAW_CALIB_ROW2_MSB_GPU_LMH_CS_FUSES_INTERCEPT_SPTP_SHFT                            0x12
#define HWIO_QFPROM_RAW_CALIB_ROW2_MSB_GPU_LMH_CS_FUSES_INTERCEPT_RAC_BMSK                          0x3ff00
#define HWIO_QFPROM_RAW_CALIB_ROW2_MSB_GPU_LMH_CS_FUSES_INTERCEPT_RAC_SHFT                              0x8
#define HWIO_QFPROM_RAW_CALIB_ROW2_MSB_GPU_LMH_CS_FUSES_INTERCEPT_HM_9_2_BMSK                          0xff
#define HWIO_QFPROM_RAW_CALIB_ROW2_MSB_GPU_LMH_CS_FUSES_INTERCEPT_HM_9_2_SHFT                           0x0

#define HWIO_QFPROM_RAW_CALIB_ROW3_LSB_ADDR                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000200)
#define HWIO_QFPROM_RAW_CALIB_ROW3_LSB_OFFS                                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000200)
#define HWIO_QFPROM_RAW_CALIB_ROW3_LSB_RMSK                                                      0xffffffff
#define HWIO_QFPROM_RAW_CALIB_ROW3_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW3_LSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW3_LSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW3_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW3_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW3_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW3_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW3_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW3_LSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW3_LSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW3_LSB_CPR0_TARG_VOLT_OFFSET_NOM_BMSK                            0xf0000000
#define HWIO_QFPROM_RAW_CALIB_ROW3_LSB_CPR0_TARG_VOLT_OFFSET_NOM_SHFT                                  0x1c
#define HWIO_QFPROM_RAW_CALIB_ROW3_LSB_CPR0_TARG_VOLT_OFFSET_NOMPLUS_BMSK                         0xf000000
#define HWIO_QFPROM_RAW_CALIB_ROW3_LSB_CPR0_TARG_VOLT_OFFSET_NOMPLUS_SHFT                              0x18
#define HWIO_QFPROM_RAW_CALIB_ROW3_LSB_CPR0_TARG_VOLT_OFFSET_TUR_BMSK                              0xf00000
#define HWIO_QFPROM_RAW_CALIB_ROW3_LSB_CPR0_TARG_VOLT_OFFSET_TUR_SHFT                                  0x14
#define HWIO_QFPROM_RAW_CALIB_ROW3_LSB_CPR0_TARG_VOLT_SVS2_BMSK                                     0xf8000
#define HWIO_QFPROM_RAW_CALIB_ROW3_LSB_CPR0_TARG_VOLT_SVS2_SHFT                                         0xf
#define HWIO_QFPROM_RAW_CALIB_ROW3_LSB_CPR0_TARG_VOLT_SVS_BMSK                                       0x7c00
#define HWIO_QFPROM_RAW_CALIB_ROW3_LSB_CPR0_TARG_VOLT_SVS_SHFT                                          0xa
#define HWIO_QFPROM_RAW_CALIB_ROW3_LSB_CPR0_TARG_VOLT_NOM_BMSK                                        0x3e0
#define HWIO_QFPROM_RAW_CALIB_ROW3_LSB_CPR0_TARG_VOLT_NOM_SHFT                                          0x5
#define HWIO_QFPROM_RAW_CALIB_ROW3_LSB_CPR0_TARG_VOLT_TUR_BMSK                                         0x1f
#define HWIO_QFPROM_RAW_CALIB_ROW3_LSB_CPR0_TARG_VOLT_TUR_SHFT                                          0x0

#define HWIO_QFPROM_RAW_CALIB_ROW3_MSB_ADDR                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000204)
#define HWIO_QFPROM_RAW_CALIB_ROW3_MSB_OFFS                                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000204)
#define HWIO_QFPROM_RAW_CALIB_ROW3_MSB_RMSK                                                      0xffffffff
#define HWIO_QFPROM_RAW_CALIB_ROW3_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW3_MSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW3_MSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW3_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW3_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW3_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW3_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW3_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW3_MSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW3_MSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW3_MSB_CPR1_TARG_VOLT_SVS2_BMSK                                  0xf8000000
#define HWIO_QFPROM_RAW_CALIB_ROW3_MSB_CPR1_TARG_VOLT_SVS2_SHFT                                        0x1b
#define HWIO_QFPROM_RAW_CALIB_ROW3_MSB_CPR1_TARG_VOLT_SVS_BMSK                                    0x7c00000
#define HWIO_QFPROM_RAW_CALIB_ROW3_MSB_CPR1_TARG_VOLT_SVS_SHFT                                         0x16
#define HWIO_QFPROM_RAW_CALIB_ROW3_MSB_CPR1_TARG_VOLT_NOM_BMSK                                     0x3e0000
#define HWIO_QFPROM_RAW_CALIB_ROW3_MSB_CPR1_TARG_VOLT_NOM_SHFT                                         0x11
#define HWIO_QFPROM_RAW_CALIB_ROW3_MSB_CPR1_TARG_VOLT_TUR_BMSK                                      0x1f000
#define HWIO_QFPROM_RAW_CALIB_ROW3_MSB_CPR1_TARG_VOLT_TUR_SHFT                                          0xc
#define HWIO_QFPROM_RAW_CALIB_ROW3_MSB_CPR0_AGING_BMSK                                                0xff0
#define HWIO_QFPROM_RAW_CALIB_ROW3_MSB_CPR0_AGING_SHFT                                                  0x4
#define HWIO_QFPROM_RAW_CALIB_ROW3_MSB_CPR0_TARG_VOLT_OFFSET_SVSP_BMSK                                  0xf
#define HWIO_QFPROM_RAW_CALIB_ROW3_MSB_CPR0_TARG_VOLT_OFFSET_SVSP_SHFT                                  0x0

#define HWIO_QFPROM_RAW_CALIB_ROW4_LSB_ADDR                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000208)
#define HWIO_QFPROM_RAW_CALIB_ROW4_LSB_OFFS                                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000208)
#define HWIO_QFPROM_RAW_CALIB_ROW4_LSB_RMSK                                                      0xffffffff
#define HWIO_QFPROM_RAW_CALIB_ROW4_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW4_LSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW4_LSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW4_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW4_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW4_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW4_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW4_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW4_LSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW4_LSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW4_LSB_CPR2_TARG_VOLT_NOM_2_0_BMSK                               0xe0000000
#define HWIO_QFPROM_RAW_CALIB_ROW4_LSB_CPR2_TARG_VOLT_NOM_2_0_SHFT                                     0x1d
#define HWIO_QFPROM_RAW_CALIB_ROW4_LSB_CPR2_TARG_VOLT_NOMPLUS_BMSK                               0x1f000000
#define HWIO_QFPROM_RAW_CALIB_ROW4_LSB_CPR2_TARG_VOLT_NOMPLUS_SHFT                                     0x18
#define HWIO_QFPROM_RAW_CALIB_ROW4_LSB_CPR1_AGING_BMSK                                             0xff0000
#define HWIO_QFPROM_RAW_CALIB_ROW4_LSB_CPR1_AGING_SHFT                                                 0x10
#define HWIO_QFPROM_RAW_CALIB_ROW4_LSB_CPR1_TARG_VOLT_OFFSET_SVSPLUS_BMSK                            0xf000
#define HWIO_QFPROM_RAW_CALIB_ROW4_LSB_CPR1_TARG_VOLT_OFFSET_SVSPLUS_SHFT                               0xc
#define HWIO_QFPROM_RAW_CALIB_ROW4_LSB_CPR1_TARG_VOLT_OFFSET_NOM_BMSK                                 0xf00
#define HWIO_QFPROM_RAW_CALIB_ROW4_LSB_CPR1_TARG_VOLT_OFFSET_NOM_SHFT                                   0x8
#define HWIO_QFPROM_RAW_CALIB_ROW4_LSB_CPR1_TARG_VOLT_OFFSET_NOMPLUS_BMSK                              0xf0
#define HWIO_QFPROM_RAW_CALIB_ROW4_LSB_CPR1_TARG_VOLT_OFFSET_NOMPLUS_SHFT                               0x4
#define HWIO_QFPROM_RAW_CALIB_ROW4_LSB_CPR1_TARG_VOLT_OFFSET_TUR_BMSK                                   0xf
#define HWIO_QFPROM_RAW_CALIB_ROW4_LSB_CPR1_TARG_VOLT_OFFSET_TUR_SHFT                                   0x0

#define HWIO_QFPROM_RAW_CALIB_ROW4_MSB_ADDR                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000020c)
#define HWIO_QFPROM_RAW_CALIB_ROW4_MSB_OFFS                                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000020c)
#define HWIO_QFPROM_RAW_CALIB_ROW4_MSB_RMSK                                                      0xffffffff
#define HWIO_QFPROM_RAW_CALIB_ROW4_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW4_MSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW4_MSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW4_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW4_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW4_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW4_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW4_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW4_MSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW4_MSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW4_MSB_CPR2_AGING_3_0_BMSK                                       0xf0000000
#define HWIO_QFPROM_RAW_CALIB_ROW4_MSB_CPR2_AGING_3_0_SHFT                                             0x1c
#define HWIO_QFPROM_RAW_CALIB_ROW4_MSB_CPR6_SVSPLUS_ROSEL_BMSK                                    0xf000000
#define HWIO_QFPROM_RAW_CALIB_ROW4_MSB_CPR6_SVSPLUS_ROSEL_SHFT                                         0x18
#define HWIO_QFPROM_RAW_CALIB_ROW4_MSB_CPR2_TARG_VOLT_OFFSET_SVSPLUS_BMSK                          0xf00000
#define HWIO_QFPROM_RAW_CALIB_ROW4_MSB_CPR2_TARG_VOLT_OFFSET_SVSPLUS_SHFT                              0x14
#define HWIO_QFPROM_RAW_CALIB_ROW4_MSB_CPR2_TARG_VOLT_OFFSET_NOM_BMSK                               0xf0000
#define HWIO_QFPROM_RAW_CALIB_ROW4_MSB_CPR2_TARG_VOLT_OFFSET_NOM_SHFT                                  0x10
#define HWIO_QFPROM_RAW_CALIB_ROW4_MSB_CPR2_TARG_VOLT_OFFSET_NOMPLUS_BMSK                            0xf000
#define HWIO_QFPROM_RAW_CALIB_ROW4_MSB_CPR2_TARG_VOLT_OFFSET_NOMPLUS_SHFT                               0xc
#define HWIO_QFPROM_RAW_CALIB_ROW4_MSB_CPR2_TARG_VOLT_SVS2_BMSK                                       0xf80
#define HWIO_QFPROM_RAW_CALIB_ROW4_MSB_CPR2_TARG_VOLT_SVS2_SHFT                                         0x7
#define HWIO_QFPROM_RAW_CALIB_ROW4_MSB_CPR2_TARG_VOLT_SVS_BMSK                                         0x7c
#define HWIO_QFPROM_RAW_CALIB_ROW4_MSB_CPR2_TARG_VOLT_SVS_SHFT                                          0x2
#define HWIO_QFPROM_RAW_CALIB_ROW4_MSB_CPR2_TARG_VOLT_NOM_4_3_BMSK                                      0x3
#define HWIO_QFPROM_RAW_CALIB_ROW4_MSB_CPR2_TARG_VOLT_NOM_4_3_SHFT                                      0x0

#define HWIO_QFPROM_RAW_CALIB_ROW5_LSB_ADDR                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000210)
#define HWIO_QFPROM_RAW_CALIB_ROW5_LSB_OFFS                                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000210)
#define HWIO_QFPROM_RAW_CALIB_ROW5_LSB_RMSK                                                      0xffffffff
#define HWIO_QFPROM_RAW_CALIB_ROW5_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW5_LSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW5_LSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW5_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW5_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW5_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW5_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW5_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW5_LSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW5_LSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW5_LSB_CPR4_TARG_VOLT_NOM_3_0_BMSK                               0xf0000000
#define HWIO_QFPROM_RAW_CALIB_ROW5_LSB_CPR4_TARG_VOLT_NOM_3_0_SHFT                                     0x1c
#define HWIO_QFPROM_RAW_CALIB_ROW5_LSB_CPR4_TARG_VOLT_TUR_BMSK                                    0xf800000
#define HWIO_QFPROM_RAW_CALIB_ROW5_LSB_CPR4_TARG_VOLT_TUR_SHFT                                         0x17
#define HWIO_QFPROM_RAW_CALIB_ROW5_LSB_CPR4_TARG_VOLT_SVS_BMSK                                     0x7c0000
#define HWIO_QFPROM_RAW_CALIB_ROW5_LSB_CPR4_TARG_VOLT_SVS_SHFT                                         0x12
#define HWIO_QFPROM_RAW_CALIB_ROW5_LSB_CPR7_TURBO_L2_ROSEL_BMSK                                     0x3c000
#define HWIO_QFPROM_RAW_CALIB_ROW5_LSB_CPR7_TURBO_L2_ROSEL_SHFT                                         0xe
#define HWIO_QFPROM_RAW_CALIB_ROW5_LSB_CPR3_TARG_VOLT_TUR_BMSK                                       0x3e00
#define HWIO_QFPROM_RAW_CALIB_ROW5_LSB_CPR3_TARG_VOLT_TUR_SHFT                                          0x9
#define HWIO_QFPROM_RAW_CALIB_ROW5_LSB_CPR3_TARG_VOLT_NOM_BMSK                                        0x1f0
#define HWIO_QFPROM_RAW_CALIB_ROW5_LSB_CPR3_TARG_VOLT_NOM_SHFT                                          0x4
#define HWIO_QFPROM_RAW_CALIB_ROW5_LSB_CPR2_AGING_7_4_BMSK                                              0xf
#define HWIO_QFPROM_RAW_CALIB_ROW5_LSB_CPR2_AGING_7_4_SHFT                                              0x0

#define HWIO_QFPROM_RAW_CALIB_ROW5_MSB_ADDR                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000214)
#define HWIO_QFPROM_RAW_CALIB_ROW5_MSB_OFFS                                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000214)
#define HWIO_QFPROM_RAW_CALIB_ROW5_MSB_RMSK                                                       0x1ffffff
#define HWIO_QFPROM_RAW_CALIB_ROW5_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW5_MSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW5_MSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW5_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW5_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW5_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW5_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW5_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW5_MSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW5_MSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW5_MSB_CPR0_TARG_VOLT_OFFSET_SUTUR_BMSK                           0x1e00000
#define HWIO_QFPROM_RAW_CALIB_ROW5_MSB_CPR0_TARG_VOLT_OFFSET_SUTUR_SHFT                                0x15
#define HWIO_QFPROM_RAW_CALIB_ROW5_MSB_CPR0_TARG_VOLT_SUTUR_BMSK                                   0x1f0000
#define HWIO_QFPROM_RAW_CALIB_ROW5_MSB_CPR0_TARG_VOLT_SUTUR_SHFT                                       0x10
#define HWIO_QFPROM_RAW_CALIB_ROW5_MSB_CPR5_TARG_VOLT_TUR_BMSK                                       0xf800
#define HWIO_QFPROM_RAW_CALIB_ROW5_MSB_CPR5_TARG_VOLT_TUR_SHFT                                          0xb
#define HWIO_QFPROM_RAW_CALIB_ROW5_MSB_CPR5_TARG_VOLT_NOM_BMSK                                        0x7c0
#define HWIO_QFPROM_RAW_CALIB_ROW5_MSB_CPR5_TARG_VOLT_NOM_SHFT                                          0x6
#define HWIO_QFPROM_RAW_CALIB_ROW5_MSB_CPR4_TARG_VOLT_SVS2_BMSK                                        0x3e
#define HWIO_QFPROM_RAW_CALIB_ROW5_MSB_CPR4_TARG_VOLT_SVS2_SHFT                                         0x1
#define HWIO_QFPROM_RAW_CALIB_ROW5_MSB_CPR4_TARG_VOLT_NOM_4_BMSK                                        0x1
#define HWIO_QFPROM_RAW_CALIB_ROW5_MSB_CPR4_TARG_VOLT_NOM_4_SHFT                                        0x0

#define HWIO_QFPROM_RAW_CALIB_ROW6_LSB_ADDR                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000218)
#define HWIO_QFPROM_RAW_CALIB_ROW6_LSB_OFFS                                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000218)
#define HWIO_QFPROM_RAW_CALIB_ROW6_LSB_RMSK                                                      0xffffffff
#define HWIO_QFPROM_RAW_CALIB_ROW6_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW6_LSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW6_LSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW6_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW6_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW6_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW6_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW6_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW6_LSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW6_LSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW6_LSB_CPR6_TARG_VOLT_SVS_3_0_BMSK                               0xf0000000
#define HWIO_QFPROM_RAW_CALIB_ROW6_LSB_CPR6_TARG_VOLT_SVS_3_0_SHFT                                     0x1c
#define HWIO_QFPROM_RAW_CALIB_ROW6_LSB_CPR6_TARG_VOLT_NOM_BMSK                                    0xfc00000
#define HWIO_QFPROM_RAW_CALIB_ROW6_LSB_CPR6_TARG_VOLT_NOM_SHFT                                         0x16
#define HWIO_QFPROM_RAW_CALIB_ROW6_LSB_CPR6_TARG_VOLT_TUR_L1_BMSK                                  0x3f0000
#define HWIO_QFPROM_RAW_CALIB_ROW6_LSB_CPR6_TARG_VOLT_TUR_L1_SHFT                                      0x10
#define HWIO_QFPROM_RAW_CALIB_ROW6_LSB_CPR6_SVS2_ROSEL_BMSK                                          0xf000
#define HWIO_QFPROM_RAW_CALIB_ROW6_LSB_CPR6_SVS2_ROSEL_SHFT                                             0xc
#define HWIO_QFPROM_RAW_CALIB_ROW6_LSB_CPR6_SVS_ROSEL_BMSK                                            0xf00
#define HWIO_QFPROM_RAW_CALIB_ROW6_LSB_CPR6_SVS_ROSEL_SHFT                                              0x8
#define HWIO_QFPROM_RAW_CALIB_ROW6_LSB_CPR6_NOMINAL_ROSEL_BMSK                                         0xf0
#define HWIO_QFPROM_RAW_CALIB_ROW6_LSB_CPR6_NOMINAL_ROSEL_SHFT                                          0x4
#define HWIO_QFPROM_RAW_CALIB_ROW6_LSB_CPR6_TURBO_L1_ROSEL_BMSK                                         0xf
#define HWIO_QFPROM_RAW_CALIB_ROW6_LSB_CPR6_TURBO_L1_ROSEL_SHFT                                         0x0

#define HWIO_QFPROM_RAW_CALIB_ROW6_MSB_ADDR                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000021c)
#define HWIO_QFPROM_RAW_CALIB_ROW6_MSB_OFFS                                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000021c)
#define HWIO_QFPROM_RAW_CALIB_ROW6_MSB_RMSK                                                      0xffffffff
#define HWIO_QFPROM_RAW_CALIB_ROW6_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW6_MSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW6_MSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW6_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW6_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW6_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW6_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW6_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW6_MSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW6_MSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW6_MSB_CPR6_NOMINAL_QUOT_VMIN_BMSK                               0xfff00000
#define HWIO_QFPROM_RAW_CALIB_ROW6_MSB_CPR6_NOMINAL_QUOT_VMIN_SHFT                                     0x14
#define HWIO_QFPROM_RAW_CALIB_ROW6_MSB_CPR6_TURBO_L1_QUOT_VMIN_BMSK                                 0xfff00
#define HWIO_QFPROM_RAW_CALIB_ROW6_MSB_CPR6_TURBO_L1_QUOT_VMIN_SHFT                                     0x8
#define HWIO_QFPROM_RAW_CALIB_ROW6_MSB_CPR6_TARG_VOLT_SVS2_BMSK                                        0xfc
#define HWIO_QFPROM_RAW_CALIB_ROW6_MSB_CPR6_TARG_VOLT_SVS2_SHFT                                         0x2
#define HWIO_QFPROM_RAW_CALIB_ROW6_MSB_CPR6_TARG_VOLT_SVS_5_4_BMSK                                      0x3
#define HWIO_QFPROM_RAW_CALIB_ROW6_MSB_CPR6_TARG_VOLT_SVS_5_4_SHFT                                      0x0

#define HWIO_QFPROM_RAW_CALIB_ROW7_LSB_ADDR                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000220)
#define HWIO_QFPROM_RAW_CALIB_ROW7_LSB_OFFS                                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000220)
#define HWIO_QFPROM_RAW_CALIB_ROW7_LSB_RMSK                                                      0xffffffff
#define HWIO_QFPROM_RAW_CALIB_ROW7_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW7_LSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW7_LSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW7_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW7_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW7_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW7_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW7_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW7_LSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW7_LSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW7_LSB_CPR6_QUOT_OFFSET_NOM_0_BMSK                               0x80000000
#define HWIO_QFPROM_RAW_CALIB_ROW7_LSB_CPR6_QUOT_OFFSET_NOM_0_SHFT                                     0x1f
#define HWIO_QFPROM_RAW_CALIB_ROW7_LSB_CPR6_QUOT_OFFSET_TUR_L1_BMSK                              0x7f000000
#define HWIO_QFPROM_RAW_CALIB_ROW7_LSB_CPR6_QUOT_OFFSET_TUR_L1_SHFT                                    0x18
#define HWIO_QFPROM_RAW_CALIB_ROW7_LSB_CPR6_SVS2_QUOT_VMIN_BMSK                                    0xfff000
#define HWIO_QFPROM_RAW_CALIB_ROW7_LSB_CPR6_SVS2_QUOT_VMIN_SHFT                                         0xc
#define HWIO_QFPROM_RAW_CALIB_ROW7_LSB_CPR6_SVS_QUOT_VMIN_BMSK                                        0xfff
#define HWIO_QFPROM_RAW_CALIB_ROW7_LSB_CPR6_SVS_QUOT_VMIN_SHFT                                          0x0

#define HWIO_QFPROM_RAW_CALIB_ROW7_MSB_ADDR                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000224)
#define HWIO_QFPROM_RAW_CALIB_ROW7_MSB_OFFS                                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000224)
#define HWIO_QFPROM_RAW_CALIB_ROW7_MSB_RMSK                                                      0xffffffff
#define HWIO_QFPROM_RAW_CALIB_ROW7_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW7_MSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW7_MSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW7_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW7_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW7_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW7_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW7_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW7_MSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW7_MSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW7_MSB_CPR7_SVS_ROSEL_2_0_BMSK                                   0xe0000000
#define HWIO_QFPROM_RAW_CALIB_ROW7_MSB_CPR7_SVS_ROSEL_2_0_SHFT                                         0x1d
#define HWIO_QFPROM_RAW_CALIB_ROW7_MSB_CPR7_NOMINAL_ROSEL_BMSK                                   0x1e000000
#define HWIO_QFPROM_RAW_CALIB_ROW7_MSB_CPR7_NOMINAL_ROSEL_SHFT                                         0x19
#define HWIO_QFPROM_RAW_CALIB_ROW7_MSB_CPR7_TURBO_ROSEL_BMSK                                      0x1e00000
#define HWIO_QFPROM_RAW_CALIB_ROW7_MSB_CPR7_TURBO_ROSEL_SHFT                                           0x15
#define HWIO_QFPROM_RAW_CALIB_ROW7_MSB_CPR6_AGING_BMSK                                             0x1fe000
#define HWIO_QFPROM_RAW_CALIB_ROW7_MSB_CPR6_AGING_SHFT                                                  0xd
#define HWIO_QFPROM_RAW_CALIB_ROW7_MSB_CPR6_QUOT_OFFSET_SVS_BMSK                                     0x1fc0
#define HWIO_QFPROM_RAW_CALIB_ROW7_MSB_CPR6_QUOT_OFFSET_SVS_SHFT                                        0x6
#define HWIO_QFPROM_RAW_CALIB_ROW7_MSB_CPR6_QUOT_OFFSET_NOM_6_1_BMSK                                   0x3f
#define HWIO_QFPROM_RAW_CALIB_ROW7_MSB_CPR6_QUOT_OFFSET_NOM_6_1_SHFT                                    0x0

#define HWIO_QFPROM_RAW_CALIB_ROW8_LSB_ADDR                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000228)
#define HWIO_QFPROM_RAW_CALIB_ROW8_LSB_OFFS                                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000228)
#define HWIO_QFPROM_RAW_CALIB_ROW8_LSB_RMSK                                                      0xffffffff
#define HWIO_QFPROM_RAW_CALIB_ROW8_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW8_LSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW8_LSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW8_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW8_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW8_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW8_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW8_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW8_LSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW8_LSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW8_LSB_CPR7_TURBO_QUOT_VMIN_2_0_BMSK                             0xe0000000
#define HWIO_QFPROM_RAW_CALIB_ROW8_LSB_CPR7_TURBO_QUOT_VMIN_2_0_SHFT                                   0x1d
#define HWIO_QFPROM_RAW_CALIB_ROW8_LSB_CPR7_TARG_VOLT_SVSPLUS_BMSK                               0x1f800000
#define HWIO_QFPROM_RAW_CALIB_ROW8_LSB_CPR7_TARG_VOLT_SVSPLUS_SHFT                                     0x17
#define HWIO_QFPROM_RAW_CALIB_ROW8_LSB_CPR7_TARG_VOLT_SVS_BMSK                                     0x7e0000
#define HWIO_QFPROM_RAW_CALIB_ROW8_LSB_CPR7_TARG_VOLT_SVS_SHFT                                         0x11
#define HWIO_QFPROM_RAW_CALIB_ROW8_LSB_CPR7_TARG_VOLT_NOM_BMSK                                      0x1f800
#define HWIO_QFPROM_RAW_CALIB_ROW8_LSB_CPR7_TARG_VOLT_NOM_SHFT                                          0xb
#define HWIO_QFPROM_RAW_CALIB_ROW8_LSB_CPR7_TARG_VOLT_TUR_BMSK                                        0x7e0
#define HWIO_QFPROM_RAW_CALIB_ROW8_LSB_CPR7_TARG_VOLT_TUR_SHFT                                          0x5
#define HWIO_QFPROM_RAW_CALIB_ROW8_LSB_CPR7_SVSPLUS_ROSEL_BMSK                                         0x1e
#define HWIO_QFPROM_RAW_CALIB_ROW8_LSB_CPR7_SVSPLUS_ROSEL_SHFT                                          0x1
#define HWIO_QFPROM_RAW_CALIB_ROW8_LSB_CPR7_SVS_ROSEL_3_BMSK                                            0x1
#define HWIO_QFPROM_RAW_CALIB_ROW8_LSB_CPR7_SVS_ROSEL_3_SHFT                                            0x0

#define HWIO_QFPROM_RAW_CALIB_ROW8_MSB_ADDR                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000022c)
#define HWIO_QFPROM_RAW_CALIB_ROW8_MSB_OFFS                                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000022c)
#define HWIO_QFPROM_RAW_CALIB_ROW8_MSB_RMSK                                                      0xffffffff
#define HWIO_QFPROM_RAW_CALIB_ROW8_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW8_MSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW8_MSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW8_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW8_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW8_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW8_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW8_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW8_MSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW8_MSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW8_MSB_CPR7_SVS_QUOT_VMIN_10_0_BMSK                              0xffe00000
#define HWIO_QFPROM_RAW_CALIB_ROW8_MSB_CPR7_SVS_QUOT_VMIN_10_0_SHFT                                    0x15
#define HWIO_QFPROM_RAW_CALIB_ROW8_MSB_CPR7_NOM_QUOT_VMIN_BMSK                                     0x1ffe00
#define HWIO_QFPROM_RAW_CALIB_ROW8_MSB_CPR7_NOM_QUOT_VMIN_SHFT                                          0x9
#define HWIO_QFPROM_RAW_CALIB_ROW8_MSB_CPR7_TURBO_QUOT_VMIN_11_3_BMSK                                 0x1ff
#define HWIO_QFPROM_RAW_CALIB_ROW8_MSB_CPR7_TURBO_QUOT_VMIN_11_3_SHFT                                   0x0

#define HWIO_QFPROM_RAW_CALIB_ROW9_LSB_ADDR                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000230)
#define HWIO_QFPROM_RAW_CALIB_ROW9_LSB_OFFS                                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000230)
#define HWIO_QFPROM_RAW_CALIB_ROW9_LSB_RMSK                                                      0xffffffff
#define HWIO_QFPROM_RAW_CALIB_ROW9_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW9_LSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW9_LSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW9_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW9_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW9_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW9_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW9_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW9_LSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW9_LSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW9_LSB_CPR7_QOUT_OFFSET_SVSPLUS_4_0_BMSK                         0xf8000000
#define HWIO_QFPROM_RAW_CALIB_ROW9_LSB_CPR7_QOUT_OFFSET_SVSPLUS_4_0_SHFT                               0x1b
#define HWIO_QFPROM_RAW_CALIB_ROW9_LSB_CPR7_QOUT_OFFSET_NOM_BMSK                                  0x7f00000
#define HWIO_QFPROM_RAW_CALIB_ROW9_LSB_CPR7_QOUT_OFFSET_NOM_SHFT                                       0x14
#define HWIO_QFPROM_RAW_CALIB_ROW9_LSB_CPR7_QOUT_OFFSET_TUR_BMSK                                    0xfe000
#define HWIO_QFPROM_RAW_CALIB_ROW9_LSB_CPR7_QOUT_OFFSET_TUR_SHFT                                        0xd
#define HWIO_QFPROM_RAW_CALIB_ROW9_LSB_CPR7_SVSPLUS_QUOT_VMIN_BMSK                                   0x1ffe
#define HWIO_QFPROM_RAW_CALIB_ROW9_LSB_CPR7_SVSPLUS_QUOT_VMIN_SHFT                                      0x1
#define HWIO_QFPROM_RAW_CALIB_ROW9_LSB_CPR7_SVS_QUOT_VMIN_11_BMSK                                       0x1
#define HWIO_QFPROM_RAW_CALIB_ROW9_LSB_CPR7_SVS_QUOT_VMIN_11_SHFT                                       0x0

#define HWIO_QFPROM_RAW_CALIB_ROW9_MSB_ADDR                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000234)
#define HWIO_QFPROM_RAW_CALIB_ROW9_MSB_OFFS                                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000234)
#define HWIO_QFPROM_RAW_CALIB_ROW9_MSB_RMSK                                                      0xffffffff
#define HWIO_QFPROM_RAW_CALIB_ROW9_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW9_MSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW9_MSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW9_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW9_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW9_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW9_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW9_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW9_MSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW9_MSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW9_MSB_CPR7_QUOT_OFFSET_TURBO_L2_3_0_BMSK                        0xf0000000
#define HWIO_QFPROM_RAW_CALIB_ROW9_MSB_CPR7_QUOT_OFFSET_TURBO_L2_3_0_SHFT                              0x1c
#define HWIO_QFPROM_RAW_CALIB_ROW9_MSB_CPR7_TURBO_L2_QUOT_VMIN_BMSK                               0xfff0000
#define HWIO_QFPROM_RAW_CALIB_ROW9_MSB_CPR7_TURBO_L2_QUOT_VMIN_SHFT                                    0x10
#define HWIO_QFPROM_RAW_CALIB_ROW9_MSB_CPR7_TARG_VOLT_TURBO_L2_BMSK                                  0xfc00
#define HWIO_QFPROM_RAW_CALIB_ROW9_MSB_CPR7_TARG_VOLT_TURBO_L2_SHFT                                     0xa
#define HWIO_QFPROM_RAW_CALIB_ROW9_MSB_CPR7_AGING_BMSK                                                0x3fc
#define HWIO_QFPROM_RAW_CALIB_ROW9_MSB_CPR7_AGING_SHFT                                                  0x2
#define HWIO_QFPROM_RAW_CALIB_ROW9_MSB_CPR7_QOUT_OFFSET_SVSPLUS_6_5_BMSK                                0x3
#define HWIO_QFPROM_RAW_CALIB_ROW9_MSB_CPR7_QOUT_OFFSET_SVSPLUS_6_5_SHFT                                0x0

#define HWIO_QFPROM_RAW_CALIB_ROW10_LSB_ADDR                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000238)
#define HWIO_QFPROM_RAW_CALIB_ROW10_LSB_OFFS                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000238)
#define HWIO_QFPROM_RAW_CALIB_ROW10_LSB_RMSK                                                     0xffffffff
#define HWIO_QFPROM_RAW_CALIB_ROW10_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW10_LSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW10_LSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW10_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW10_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW10_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW10_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW10_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW10_LSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW10_LSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW10_LSB_CPR_GLOBAL_RC_0_BMSK                                     0x80000000
#define HWIO_QFPROM_RAW_CALIB_ROW10_LSB_CPR_GLOBAL_RC_0_SHFT                                           0x1f
#define HWIO_QFPROM_RAW_CALIB_ROW10_LSB_CPR_LOCAL_RC_BMSK                                        0x70000000
#define HWIO_QFPROM_RAW_CALIB_ROW10_LSB_CPR_LOCAL_RC_SHFT                                              0x1c
#define HWIO_QFPROM_RAW_CALIB_ROW10_LSB_CPR9_QUOT_OFFSET_SVSPLUS_BMSK                             0xfe00000
#define HWIO_QFPROM_RAW_CALIB_ROW10_LSB_CPR9_QUOT_OFFSET_SVSPLUS_SHFT                                  0x15
#define HWIO_QFPROM_RAW_CALIB_ROW10_LSB_CPR6_SVSPLUS_QUOT_VMIN_BMSK                                0x1ffe00
#define HWIO_QFPROM_RAW_CALIB_ROW10_LSB_CPR6_SVSPLUS_QUOT_VMIN_SHFT                                     0x9
#define HWIO_QFPROM_RAW_CALIB_ROW10_LSB_CPR6_TARG_VOLT_SVSPLUS_BMSK                                   0x1f8
#define HWIO_QFPROM_RAW_CALIB_ROW10_LSB_CPR6_TARG_VOLT_SVSPLUS_SHFT                                     0x3
#define HWIO_QFPROM_RAW_CALIB_ROW10_LSB_CPR7_QUOT_OFFSET_TURBO_L2_6_4_BMSK                              0x7
#define HWIO_QFPROM_RAW_CALIB_ROW10_LSB_CPR7_QUOT_OFFSET_TURBO_L2_6_4_SHFT                              0x0

#define HWIO_QFPROM_RAW_CALIB_ROW10_MSB_ADDR                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000023c)
#define HWIO_QFPROM_RAW_CALIB_ROW10_MSB_OFFS                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000023c)
#define HWIO_QFPROM_RAW_CALIB_ROW10_MSB_RMSK                                                     0xffffc07f
#define HWIO_QFPROM_RAW_CALIB_ROW10_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW10_MSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW10_MSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW10_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW10_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW10_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW10_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW10_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW10_MSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW10_MSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW10_MSB_SPARE_71_63_BMSK                                         0x80000000
#define HWIO_QFPROM_RAW_CALIB_ROW10_MSB_SPARE_71_63_SHFT                                               0x1f
#define HWIO_QFPROM_RAW_CALIB_ROW10_MSB_SPARE_71_62_BMSK                                         0x40000000
#define HWIO_QFPROM_RAW_CALIB_ROW10_MSB_SPARE_71_62_SHFT                                               0x1e
#define HWIO_QFPROM_RAW_CALIB_ROW10_MSB_SPARE_71_61_BMSK                                         0x20000000
#define HWIO_QFPROM_RAW_CALIB_ROW10_MSB_SPARE_71_61_SHFT                                               0x1d
#define HWIO_QFPROM_RAW_CALIB_ROW10_MSB_SW_CAL_REDUN_SEL_BMSK                                    0x1c000000
#define HWIO_QFPROM_RAW_CALIB_ROW10_MSB_SW_CAL_REDUN_SEL_SHFT                                          0x1a
#define HWIO_QFPROM_RAW_CALIB_ROW10_MSB_CPR_RESERVED_BMSK                                         0x3ffc000
#define HWIO_QFPROM_RAW_CALIB_ROW10_MSB_CPR_RESERVED_SHFT                                               0xe
#define HWIO_QFPROM_RAW_CALIB_ROW10_MSB_GFX_LOD_CPR_CL_ENABLE_BMSK                                     0x40
#define HWIO_QFPROM_RAW_CALIB_ROW10_MSB_GFX_LOD_CPR_CL_ENABLE_SHFT                                      0x6
#define HWIO_QFPROM_RAW_CALIB_ROW10_MSB_CPR7_BINNING_ENABLE_BMSK                                       0x20
#define HWIO_QFPROM_RAW_CALIB_ROW10_MSB_CPR7_BINNING_ENABLE_SHFT                                        0x5
#define HWIO_QFPROM_RAW_CALIB_ROW10_MSB_CPR_GFX_LDO_RC_BMSK                                            0x1c
#define HWIO_QFPROM_RAW_CALIB_ROW10_MSB_CPR_GFX_LDO_RC_SHFT                                             0x2
#define HWIO_QFPROM_RAW_CALIB_ROW10_MSB_CPR_GLOBAL_RC_2_1_BMSK                                          0x3
#define HWIO_QFPROM_RAW_CALIB_ROW10_MSB_CPR_GLOBAL_RC_2_1_SHFT                                          0x0

#define HWIO_QFPROM_RAW_CALIB_ROW11_LSB_ADDR                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000240)
#define HWIO_QFPROM_RAW_CALIB_ROW11_LSB_OFFS                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000240)
#define HWIO_QFPROM_RAW_CALIB_ROW11_LSB_RMSK                                                     0xffffffff
#define HWIO_QFPROM_RAW_CALIB_ROW11_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW11_LSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW11_LSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW11_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW11_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW11_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW11_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW11_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW11_LSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW11_LSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW11_LSB_SPARE_72_31_BMSK                                         0x80000000
#define HWIO_QFPROM_RAW_CALIB_ROW11_LSB_SPARE_72_31_SHFT                                               0x1f
#define HWIO_QFPROM_RAW_CALIB_ROW11_LSB_SPARE_72_30_BMSK                                         0x40000000
#define HWIO_QFPROM_RAW_CALIB_ROW11_LSB_SPARE_72_30_SHFT                                               0x1e
#define HWIO_QFPROM_RAW_CALIB_ROW11_LSB_QUSB_REFCLK_SEL_BMSK                                     0x20000000
#define HWIO_QFPROM_RAW_CALIB_ROW11_LSB_QUSB_REFCLK_SEL_SHFT                                           0x1d
#define HWIO_QFPROM_RAW_CALIB_ROW11_LSB_QUSB_PORT0_HSTX_TRIM_LSB_BMSK                            0x1e000000
#define HWIO_QFPROM_RAW_CALIB_ROW11_LSB_QUSB_PORT0_HSTX_TRIM_LSB_SHFT                                  0x19
#define HWIO_QFPROM_RAW_CALIB_ROW11_LSB_SRAM_AGING_SENSOR_1_BMSK                                  0x1fe0000
#define HWIO_QFPROM_RAW_CALIB_ROW11_LSB_SRAM_AGING_SENSOR_1_SHFT                                       0x11
#define HWIO_QFPROM_RAW_CALIB_ROW11_LSB_SRAM_AGING_SENSOR_0_BMSK                                    0x1fe00
#define HWIO_QFPROM_RAW_CALIB_ROW11_LSB_SRAM_AGING_SENSOR_0_SHFT                                        0x9
#define HWIO_QFPROM_RAW_CALIB_ROW11_LSB_GNSS_ADC_RSB_BMSK                                             0x1c0
#define HWIO_QFPROM_RAW_CALIB_ROW11_LSB_GNSS_ADC_RSB_SHFT                                               0x6
#define HWIO_QFPROM_RAW_CALIB_ROW11_LSB_GNSS_ADC_LDO_BMSK                                              0x38
#define HWIO_QFPROM_RAW_CALIB_ROW11_LSB_GNSS_ADC_LDO_SHFT                                               0x3
#define HWIO_QFPROM_RAW_CALIB_ROW11_LSB_GNSS_ADC_VREF_BMSK                                              0x7
#define HWIO_QFPROM_RAW_CALIB_ROW11_LSB_GNSS_ADC_VREF_SHFT                                              0x0

#define HWIO_QFPROM_RAW_CALIB_ROW11_MSB_ADDR                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000244)
#define HWIO_QFPROM_RAW_CALIB_ROW11_MSB_OFFS                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000244)
#define HWIO_QFPROM_RAW_CALIB_ROW11_MSB_RMSK                                                     0xffffffff
#define HWIO_QFPROM_RAW_CALIB_ROW11_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW11_MSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW11_MSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW11_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW11_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW11_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW11_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW11_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW11_MSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW11_MSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW11_MSB_TSENS2_OFFSET_BMSK                                       0xf0000000
#define HWIO_QFPROM_RAW_CALIB_ROW11_MSB_TSENS2_OFFSET_SHFT                                             0x1c
#define HWIO_QFPROM_RAW_CALIB_ROW11_MSB_TSENS1_OFFSET_BMSK                                        0xf000000
#define HWIO_QFPROM_RAW_CALIB_ROW11_MSB_TSENS1_OFFSET_SHFT                                             0x18
#define HWIO_QFPROM_RAW_CALIB_ROW11_MSB_TSENS0_OFFSET_BMSK                                         0xf00000
#define HWIO_QFPROM_RAW_CALIB_ROW11_MSB_TSENS0_OFFSET_SHFT                                             0x14
#define HWIO_QFPROM_RAW_CALIB_ROW11_MSB_TSENS1_BASE1_BMSK                                           0xffc00
#define HWIO_QFPROM_RAW_CALIB_ROW11_MSB_TSENS1_BASE1_SHFT                                               0xa
#define HWIO_QFPROM_RAW_CALIB_ROW11_MSB_TSENS1_BASE0_BMSK                                             0x3ff
#define HWIO_QFPROM_RAW_CALIB_ROW11_MSB_TSENS1_BASE0_SHFT                                               0x0

#define HWIO_QFPROM_RAW_CALIB_ROW12_LSB_ADDR                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000248)
#define HWIO_QFPROM_RAW_CALIB_ROW12_LSB_OFFS                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000248)
#define HWIO_QFPROM_RAW_CALIB_ROW12_LSB_RMSK                                                     0xffffffff
#define HWIO_QFPROM_RAW_CALIB_ROW12_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW12_LSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW12_LSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW12_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW12_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW12_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW12_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW12_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW12_LSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW12_LSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW12_LSB_TSENS10_OFFSET_BMSK                                      0xf0000000
#define HWIO_QFPROM_RAW_CALIB_ROW12_LSB_TSENS10_OFFSET_SHFT                                            0x1c
#define HWIO_QFPROM_RAW_CALIB_ROW12_LSB_TSENS9_OFFSET_BMSK                                        0xf000000
#define HWIO_QFPROM_RAW_CALIB_ROW12_LSB_TSENS9_OFFSET_SHFT                                             0x18
#define HWIO_QFPROM_RAW_CALIB_ROW12_LSB_TSENS8_OFFSET_BMSK                                         0xf00000
#define HWIO_QFPROM_RAW_CALIB_ROW12_LSB_TSENS8_OFFSET_SHFT                                             0x14
#define HWIO_QFPROM_RAW_CALIB_ROW12_LSB_TSENS7_OFFSET_BMSK                                          0xf0000
#define HWIO_QFPROM_RAW_CALIB_ROW12_LSB_TSENS7_OFFSET_SHFT                                             0x10
#define HWIO_QFPROM_RAW_CALIB_ROW12_LSB_TSENS6_OFFSET_BMSK                                           0xf000
#define HWIO_QFPROM_RAW_CALIB_ROW12_LSB_TSENS6_OFFSET_SHFT                                              0xc
#define HWIO_QFPROM_RAW_CALIB_ROW12_LSB_TSENS5_OFFSET_BMSK                                            0xf00
#define HWIO_QFPROM_RAW_CALIB_ROW12_LSB_TSENS5_OFFSET_SHFT                                              0x8
#define HWIO_QFPROM_RAW_CALIB_ROW12_LSB_TSENS4_OFFSET_BMSK                                             0xf0
#define HWIO_QFPROM_RAW_CALIB_ROW12_LSB_TSENS4_OFFSET_SHFT                                              0x4
#define HWIO_QFPROM_RAW_CALIB_ROW12_LSB_TSENS3_OFFSET_BMSK                                              0xf
#define HWIO_QFPROM_RAW_CALIB_ROW12_LSB_TSENS3_OFFSET_SHFT                                              0x0

#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_ADDR                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000024c)
#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_OFFS                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000024c)
#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_RMSK                                                     0x7e0fffff
#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW12_MSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW12_MSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW12_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW12_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW12_MSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW12_MSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_GFX_LDO_ENABLE_SVS3_BMSK                                 0x40000000
#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_GFX_LDO_ENABLE_SVS3_SHFT                                       0x1e
#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_GFX_LDO_ENABLE_SVS2_BMSK                                 0x20000000
#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_GFX_LDO_ENABLE_SVS2_SHFT                                       0x1d
#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_GFX_LDO_ENABLE_SVSP_BMSK                                 0x10000000
#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_GFX_LDO_ENABLE_SVSP_SHFT                                       0x1c
#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_GFX_LDO_ENABLE_SVS_BMSK                                   0x8000000
#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_GFX_LDO_ENABLE_SVS_SHFT                                        0x1b
#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_GFX_LDO_ENABLE_NOM_BMSK                                   0x4000000
#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_GFX_LDO_ENABLE_NOM_SHFT                                        0x1a
#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_GFX_LDO_ENABLE_NOMP_BMSK                                  0x2000000
#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_GFX_LDO_ENABLE_NOMP_SHFT                                       0x19
#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_MSS_Q6_LDO_ENABLE_SVS3_BMSK                                 0x80000
#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_MSS_Q6_LDO_ENABLE_SVS3_SHFT                                    0x13
#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_MSS_Q6_LDO_ENABLE_SVS2_BMSK                                 0x40000
#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_MSS_Q6_LDO_ENABLE_SVS2_SHFT                                    0x12
#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_MSS_Q6_LDO_ENABLE_SVS_BMSK                                  0x20000
#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_MSS_Q6_LDO_ENABLE_SVS_SHFT                                     0x11
#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_MSS_Q6_LDO_ENABLE_SVSP_BMSK                                 0x10000
#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_MSS_Q6_LDO_ENABLE_SVSP_SHFT                                    0x10
#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_MSS_Q6_LDO_ENABLE_NOM_BMSK                                   0x8000
#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_MSS_Q6_LDO_ENABLE_NOM_SHFT                                      0xf
#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_TSENS_CAL_SEL_BMSK                                           0x7000
#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_TSENS_CAL_SEL_SHFT                                              0xc
#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_TSENS13_OFFSET_BMSK                                           0xf00
#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_TSENS13_OFFSET_SHFT                                             0x8
#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_TSENS12_OFFSET_BMSK                                            0xf0
#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_TSENS12_OFFSET_SHFT                                             0x4
#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_TSENS11_OFFSET_BMSK                                             0xf
#define HWIO_QFPROM_RAW_CALIB_ROW12_MSB_TSENS11_OFFSET_SHFT                                             0x0

#define HWIO_QFPROM_RAW_CALIB_ROW13_LSB_ADDR                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000250)
#define HWIO_QFPROM_RAW_CALIB_ROW13_LSB_OFFS                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000250)
#define HWIO_QFPROM_RAW_CALIB_ROW13_LSB_RMSK                                                            0xf
#define HWIO_QFPROM_RAW_CALIB_ROW13_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW13_LSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW13_LSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW13_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW13_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW13_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW13_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW13_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW13_LSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW13_LSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW13_LSB_RSVD_HVX_LDO_ENABLE_SVS3_BMSK                                   0x8
#define HWIO_QFPROM_RAW_CALIB_ROW13_LSB_RSVD_HVX_LDO_ENABLE_SVS3_SHFT                                   0x3
#define HWIO_QFPROM_RAW_CALIB_ROW13_LSB_RSVD_HVX_LDO_ENABLE_SVS2_BMSK                                   0x4
#define HWIO_QFPROM_RAW_CALIB_ROW13_LSB_RSVD_HVX_LDO_ENABLE_SVS2_SHFT                                   0x2
#define HWIO_QFPROM_RAW_CALIB_ROW13_LSB_RSVD_HVX_LDO_ENABLE_SVS1_BMSK                                   0x2
#define HWIO_QFPROM_RAW_CALIB_ROW13_LSB_RSVD_HVX_LDO_ENABLE_SVS1_SHFT                                   0x1
#define HWIO_QFPROM_RAW_CALIB_ROW13_LSB_RSVD_HVX_LDO_ENABLE_SVSP_BMSK                                   0x1
#define HWIO_QFPROM_RAW_CALIB_ROW13_LSB_RSVD_HVX_LDO_ENABLE_SVSP_SHFT                                   0x0

#define HWIO_QFPROM_RAW_CALIB_ROW13_MSB_ADDR                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000254)
#define HWIO_QFPROM_RAW_CALIB_ROW13_MSB_OFFS                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000254)
#define HWIO_QFPROM_RAW_CALIB_ROW13_MSB_RMSK                                                     0xffffffff
#define HWIO_QFPROM_RAW_CALIB_ROW13_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW13_MSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW13_MSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW13_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW13_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW13_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW13_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW13_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW13_MSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW13_MSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW13_MSB_RSVD_BMSK                                                0xffffffff
#define HWIO_QFPROM_RAW_CALIB_ROW13_MSB_RSVD_SHFT                                                       0x0

#define HWIO_QFPROM_RAW_CALIB_ROW14_LSB_ADDR                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000258)
#define HWIO_QFPROM_RAW_CALIB_ROW14_LSB_OFFS                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000258)
#define HWIO_QFPROM_RAW_CALIB_ROW14_LSB_RMSK                                                     0xffffffc0
#define HWIO_QFPROM_RAW_CALIB_ROW14_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW14_LSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW14_LSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW14_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW14_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW14_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW14_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW14_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW14_LSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW14_LSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW14_LSB_VSENSE_CALIB_25_0_BMSK                                   0xffffffc0
#define HWIO_QFPROM_RAW_CALIB_ROW14_LSB_VSENSE_CALIB_25_0_SHFT                                          0x6

#define HWIO_QFPROM_RAW_CALIB_ROW14_MSB_ADDR                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000025c)
#define HWIO_QFPROM_RAW_CALIB_ROW14_MSB_OFFS                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000025c)
#define HWIO_QFPROM_RAW_CALIB_ROW14_MSB_RMSK                                                      0xfffffff
#define HWIO_QFPROM_RAW_CALIB_ROW14_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW14_MSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW14_MSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW14_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW14_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW14_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW14_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW14_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW14_MSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW14_MSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW14_MSB_VSENSE_CALIB_53_26_BMSK                                   0xfffffff
#define HWIO_QFPROM_RAW_CALIB_ROW14_MSB_VSENSE_CALIB_53_26_SHFT                                         0x0

#define HWIO_QFPROM_RAW_CALIB_ROW15_LSB_ADDR                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000260)
#define HWIO_QFPROM_RAW_CALIB_ROW15_LSB_OFFS                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000260)
#define HWIO_QFPROM_RAW_CALIB_ROW15_LSB_RMSK                                                     0xfffffffe
#define HWIO_QFPROM_RAW_CALIB_ROW15_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW15_LSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW15_LSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW15_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW15_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW15_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW15_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW15_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW15_LSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW15_LSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW15_LSB_SW_CAL_REDUNDANCY_30_0_BMSK                              0xfffffffe
#define HWIO_QFPROM_RAW_CALIB_ROW15_LSB_SW_CAL_REDUNDANCY_30_0_SHFT                                     0x1

#define HWIO_QFPROM_RAW_CALIB_ROW15_MSB_ADDR                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000264)
#define HWIO_QFPROM_RAW_CALIB_ROW15_MSB_OFFS                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000264)
#define HWIO_QFPROM_RAW_CALIB_ROW15_MSB_RMSK                                                     0xffffffff
#define HWIO_QFPROM_RAW_CALIB_ROW15_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW15_MSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW15_MSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW15_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW15_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW15_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW15_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW15_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW15_MSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW15_MSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW15_MSB_SW_CAL_REDUNDANCY_62_31_BMSK                             0xffffffff
#define HWIO_QFPROM_RAW_CALIB_ROW15_MSB_SW_CAL_REDUNDANCY_62_31_SHFT                                    0x0

#define HWIO_QFPROM_RAW_CALIB_ROW16_LSB_ADDR                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000268)
#define HWIO_QFPROM_RAW_CALIB_ROW16_LSB_OFFS                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000268)
#define HWIO_QFPROM_RAW_CALIB_ROW16_LSB_RMSK                                                     0xffffffff
#define HWIO_QFPROM_RAW_CALIB_ROW16_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW16_LSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW16_LSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW16_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW16_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW16_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW16_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW16_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW16_LSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW16_LSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW16_LSB_SW_CAL_REDUNDANCY_94_63_BMSK                             0xffffffff
#define HWIO_QFPROM_RAW_CALIB_ROW16_LSB_SW_CAL_REDUNDANCY_94_63_SHFT                                    0x0

#define HWIO_QFPROM_RAW_CALIB_ROW16_MSB_ADDR                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000026c)
#define HWIO_QFPROM_RAW_CALIB_ROW16_MSB_OFFS                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000026c)
#define HWIO_QFPROM_RAW_CALIB_ROW16_MSB_RMSK                                                     0xffffffff
#define HWIO_QFPROM_RAW_CALIB_ROW16_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW16_MSB_ADDR, HWIO_QFPROM_RAW_CALIB_ROW16_MSB_RMSK)
#define HWIO_QFPROM_RAW_CALIB_ROW16_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CALIB_ROW16_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_CALIB_ROW16_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CALIB_ROW16_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_CALIB_ROW16_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CALIB_ROW16_MSB_ADDR,m,v,HWIO_QFPROM_RAW_CALIB_ROW16_MSB_IN)
#define HWIO_QFPROM_RAW_CALIB_ROW16_MSB_SW_CAL_REDUNDANCY_126_95_BMSK                            0xffffffff
#define HWIO_QFPROM_RAW_CALIB_ROW16_MSB_SW_CAL_REDUNDANCY_126_95_SHFT                                   0x0

#define HWIO_QFPROM_RAW_MEM_CONFIG_ROWn_LSB_ADDR(n)                                              (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000270 + 0x8 * (n))
#define HWIO_QFPROM_RAW_MEM_CONFIG_ROWn_LSB_OFFS(n)                                              (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000270 + 0x8 * (n))
#define HWIO_QFPROM_RAW_MEM_CONFIG_ROWn_LSB_RMSK                                                 0xffffffff
#define HWIO_QFPROM_RAW_MEM_CONFIG_ROWn_LSB_MAXn                                                         18
#define HWIO_QFPROM_RAW_MEM_CONFIG_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_MEM_CONFIG_ROWn_LSB_ADDR(n), HWIO_QFPROM_RAW_MEM_CONFIG_ROWn_LSB_RMSK)
#define HWIO_QFPROM_RAW_MEM_CONFIG_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_MEM_CONFIG_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_MEM_CONFIG_ROWn_LSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_MEM_CONFIG_ROWn_LSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_MEM_CONFIG_ROWn_LSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_MEM_CONFIG_ROWn_LSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_MEM_CONFIG_ROWn_LSB_INI(n))
#define HWIO_QFPROM_RAW_MEM_CONFIG_ROWn_LSB_REDUN_DATA_BMSK                                      0xffffffff
#define HWIO_QFPROM_RAW_MEM_CONFIG_ROWn_LSB_REDUN_DATA_SHFT                                             0x0

#define HWIO_QFPROM_RAW_MEM_CONFIG_ROWn_MSB_ADDR(n)                                              (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000274 + 0x8 * (n))
#define HWIO_QFPROM_RAW_MEM_CONFIG_ROWn_MSB_OFFS(n)                                              (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000274 + 0x8 * (n))
#define HWIO_QFPROM_RAW_MEM_CONFIG_ROWn_MSB_RMSK                                                 0xffffffff
#define HWIO_QFPROM_RAW_MEM_CONFIG_ROWn_MSB_MAXn                                                         18
#define HWIO_QFPROM_RAW_MEM_CONFIG_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_MEM_CONFIG_ROWn_MSB_ADDR(n), HWIO_QFPROM_RAW_MEM_CONFIG_ROWn_MSB_RMSK)
#define HWIO_QFPROM_RAW_MEM_CONFIG_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_MEM_CONFIG_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_MEM_CONFIG_ROWn_MSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_MEM_CONFIG_ROWn_MSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_MEM_CONFIG_ROWn_MSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_MEM_CONFIG_ROWn_MSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_MEM_CONFIG_ROWn_MSB_INI(n))
#define HWIO_QFPROM_RAW_MEM_CONFIG_ROWn_MSB_REDUN_DATA_BMSK                                      0xffffffff
#define HWIO_QFPROM_RAW_MEM_CONFIG_ROWn_MSB_REDUN_DATA_SHFT                                             0x0

#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_ADDR                                             (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000308)
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_OFFS                                             (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000308)
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_RMSK                                             0xffffffff
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_ADDR, HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_RMSK)
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_UFS_SW_CONTROL_DISABLE_BMSK                      0x80000000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_UFS_SW_CONTROL_DISABLE_SHFT                            0x1f
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_RSVD2_BMSK                                       0x40000000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_RSVD2_SHFT                                             0x1e
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_RSVD1_BMSK                                       0x20000000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_RSVD1_SHFT                                             0x1d
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_GFX3D_FREQ_LIMIT_VAL_BMSK                        0x1fe00000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_GFX3D_FREQ_LIMIT_VAL_SHFT                              0x15
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_MDSS_RESOLUTION_LIMIT_BMSK                         0x180000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_MDSS_RESOLUTION_LIMIT_SHFT                             0x13
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_VENUS_HEVC_ENCODE_DISABLE_BMSK                      0x40000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_VENUS_HEVC_ENCODE_DISABLE_SHFT                         0x12
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_VENUS_HEVC_DECODE_DISABLE_BMSK                      0x20000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_VENUS_HEVC_DECODE_DISABLE_SHFT                         0x11
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_VENUS_4K_DISABLE_BMSK                               0x10000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_VENUS_4K_DISABLE_SHFT                                  0x10
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_VP8_DECODER_DISABLE_BMSK                             0x8000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_VP8_DECODER_DISABLE_SHFT                                0xf
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_VP8_ENCODER_DISABLE_BMSK                             0x4000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_VP8_ENCODER_DISABLE_SHFT                                0xe
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_HDMI_DP_DISABLE_BMSK                                 0x2000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_HDMI_DP_DISABLE_SHFT                                    0xd
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_HDCP_DISABLE_BMSK                                    0x1000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_HDCP_DISABLE_SHFT                                       0xc
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_MDP_APICAL_LTC_DISABLE_BMSK                           0x800
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_MDP_APICAL_LTC_DISABLE_SHFT                             0xb
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_HDCP_GLOBAL_KEY_SPLIT2_DISABLE_BMSK                   0x400
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_HDCP_GLOBAL_KEY_SPLIT2_DISABLE_SHFT                     0xa
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_DSI_1_DISABLE_BMSK                                    0x200
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_DSI_1_DISABLE_SHFT                                      0x9
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_USB2_DISABLE_BMSK                                     0x100
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_USB2_DISABLE_SHFT                                       0x8
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_RSVD0_BMSK                                             0x80
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_RSVD0_SHFT                                              0x7
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_CSID_DPCM_14_DISABLE_BMSK                              0x40
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_CSID_DPCM_14_DISABLE_SHFT                               0x6
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_ISP_1_DISABLE_BMSK                                     0x20
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_ISP_1_DISABLE_SHFT                                      0x5
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_CSID_3_DISABLE_BMSK                                    0x10
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_CSID_3_DISABLE_SHFT                                     0x4
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_CSID_2_DISABLE_BMSK                                     0x8
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_CSID_2_DISABLE_SHFT                                     0x3
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_BOOT_ROM_PATCH_DISABLE_BMSK                             0x7
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_LSB_BOOT_ROM_PATCH_DISABLE_SHFT                             0x0

#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_ADDR                                             (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000030c)
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_OFFS                                             (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000030c)
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_RMSK                                             0xffffffff
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_ADDR, HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_RMSK)
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_ICE_FORCE_HW_KEY1_BMSK                           0x80000000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_ICE_FORCE_HW_KEY1_SHFT                                 0x1f
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_ICE_FORCE_HW_KEY0_BMSK                           0x40000000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_ICE_FORCE_HW_KEY0_SHFT                                 0x1e
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_ICE_DISABLE_BMSK                                 0x20000000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_ICE_DISABLE_SHFT                                       0x1d
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_RSVD2_BMSK                                       0x10000000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_RSVD2_SHFT                                             0x1c
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_RSVD1_BMSK                                        0x8000000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_RSVD1_SHFT                                             0x1b
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_LPASS_SENSOR_DISABLE_BMSK                         0x4000000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_LPASS_SENSOR_DISABLE_SHFT                              0x1a
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_LPASS_ISLAND_MODE_Q6_CLK_DISABLE_BMSK             0x2000000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_LPASS_ISLAND_MODE_Q6_CLK_DISABLE_SHFT                  0x19
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_LPASS_SW_ISLAND_MODE_DISABLE_BMSK                 0x1000000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_LPASS_SW_ISLAND_MODE_DISABLE_SHFT                      0x18
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_LPASS_EFUSE_TESTBUS_READ_DISABLE_BMSK              0x800000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_LPASS_EFUSE_TESTBUS_READ_DISABLE_SHFT                  0x17
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_APS_RESET_DISABLE_BMSK                             0x400000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_APS_RESET_DISABLE_SHFT                                 0x16
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_HVX_DISABLE_BMSK                                   0x200000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_HVX_DISABLE_SHFT                                       0x15
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_APB2JTAG_DISABLE_BMSK                              0x100000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_APB2JTAG_DISABLE_SHFT                                  0x14
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_RSVD6_BMSK                                          0x80000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_RSVD6_SHFT                                             0x13
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_STACKED_MEMORY_ID_BMSK                              0x7c000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_STACKED_MEMORY_ID_SHFT                                  0xe
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_PRNG_TESTMODE_DISABLE_BMSK                           0x2000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_PRNG_TESTMODE_DISABLE_SHFT                              0xd
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_CDSP_DISABLE_BMSK                                    0x1000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_CDSP_DISABLE_SHFT                                       0xc
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_MOCHA_PART_BMSK                                       0x800
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_MOCHA_PART_SHFT                                         0xb
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_RSVD5_BMSK                                            0x400
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_RSVD5_SHFT                                              0xa
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_RSVD4_BMSK                                            0x200
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_RSVD4_SHFT                                              0x9
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_RSVD3_BMSK                                            0x1e0
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_RSVD3_SHFT                                              0x5
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_CM_FEAT_CONFIG_DISABLE_BMSK                            0x10
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_CM_FEAT_CONFIG_DISABLE_SHFT                             0x4
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_VFE_RESOLUTION_LIMIT_BMSK                               0x8
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_VFE_RESOLUTION_LIMIT_SHFT                               0x3
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_GLD_PDX_FIFO_NIU_BMSK                                   0x4
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_GLD_PDX_FIFO_NIU_SHFT                                   0x2
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_RSVD0_BMSK                                              0x2
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_RSVD0_SHFT                                              0x1
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_VP9_DECODER_DISABLE_BMSK                                0x1
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW0_MSB_VP9_DECODER_DISABLE_SHFT                                0x0

#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_LSB_ADDR                                             (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000310)
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_LSB_OFFS                                             (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000310)
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_LSB_RMSK                                             0xffffffff
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_LSB_ADDR, HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_LSB_RMSK)
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_LSB_MDSP_FW_DISABLE_BMSK                             0xfff00000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_LSB_MDSP_FW_DISABLE_SHFT                                   0x14
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_LSB_RSVD0_BMSK                                          0x80000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_LSB_RSVD0_SHFT                                             0x13
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_LSB_NAV_DISABLE_BMSK                                    0x40000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_LSB_NAV_DISABLE_SHFT                                       0x12
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_LSB_SYS_APCCCFGNMFI_BMSK                                0x20000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_LSB_SYS_APCCCFGNMFI_SHFT                                   0x11
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_LSB_GLD_PDX_FIFO_ACE1_BMSK                              0x10000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_LSB_GLD_PDX_FIFO_ACE1_SHFT                                 0x10
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_LSB_GLD_PDX_FIFO_ACE0_BMSK                               0x8000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_LSB_GLD_PDX_FIFO_ACE0_SHFT                                  0xf
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_LSB_MODEM_FEATURE_DISABLE_SPARE_BMSK                     0x7fe0
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_LSB_MODEM_FEATURE_DISABLE_SPARE_SHFT                        0x5
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_LSB_MODEM_FEATURE_DISABLE_SLICE_BMSK                       0x1f
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_LSB_MODEM_FEATURE_DISABLE_SLICE_SHFT                        0x0

#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_MSB_ADDR                                             (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000314)
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_MSB_OFFS                                             (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000314)
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_MSB_RMSK                                             0xffffffff
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_MSB_ADDR, HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_MSB_RMSK)
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_MSB_SYS_APCX_SYSBARDISABLE_BMSK                      0x80000000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_MSB_SYS_APCX_SYSBARDISABLE_SHFT                            0x1f
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_MSB_SYS_APCSCFGAPMBOOTONMX_BMSK                      0x60000000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_MSB_SYS_APCSCFGAPMBOOTONMX_SHFT                            0x1d
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_MSB_SYS_APCCCFGCPUPRESENT_N_BMSK                     0x1fe00000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_MSB_SYS_APCCCFGCPUPRESENT_N_SHFT                           0x15
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_MSB_APPS_ACG_DISABLE_BMSK                              0x100000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_MSB_APPS_ACG_DISABLE_SHFT                                  0x14
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_MSB_RSVD1_BMSK                                          0xf0000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_MSB_RSVD1_SHFT                                             0x10
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_MSB_MODEM_VU_DISABLE_BMSK                                0xffff
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW1_MSB_MODEM_VU_DISABLE_SHFT                                   0x0

#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_ADDR                                             (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000318)
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_OFFS                                             (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000318)
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_RMSK                                             0xffffffff
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_ADDR, HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_RMSK)
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_ADDR,m,v,HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_IN)
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_APPS_SPNIDEN_DISABLE_BMSK                     0x80000000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_APPS_SPNIDEN_DISABLE_SHFT                           0x1f
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_MSS_NIDEN_DISABLE_BMSK                        0x40000000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_MSS_NIDEN_DISABLE_SHFT                              0x1e
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_LPASS_SENSOR_NIDEN_DISABLE_BMSK               0x20000000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_LPASS_SENSOR_NIDEN_DISABLE_SHFT                     0x1d
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_PIMEM_NIDEN_DISABLE_BMSK                      0x10000000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_PIMEM_NIDEN_DISABLE_SHFT                            0x1c
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_RPM_NIDEN_DISABLE_BMSK                         0x8000000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_RPM_NIDEN_DISABLE_SHFT                              0x1b
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_WCSS_NIDEN_DISABLE_BMSK                        0x4000000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_WCSS_NIDEN_DISABLE_SHFT                             0x1a
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_LPASS_NIDEN_DISABLE_BMSK                       0x2000000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_LPASS_NIDEN_DISABLE_SHFT                            0x19
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_DAP_NIDEN_DISABLE_BMSK                         0x1000000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_DAP_NIDEN_DISABLE_SHFT                              0x18
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_APPS_NIDEN_DISABLE_BMSK                         0x800000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_APPS_NIDEN_DISABLE_SHFT                             0x17
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_MSS_DBGEN_DISABLE_BMSK                          0x400000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_MSS_DBGEN_DISABLE_SHFT                              0x16
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_A5X_ISDB_DBGEN_DISABLE_BMSK                     0x200000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_A5X_ISDB_DBGEN_DISABLE_SHFT                         0x15
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_VENUS_0_DBGEN_DISABLE_BMSK                      0x100000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_VENUS_0_DBGEN_DISABLE_SHFT                          0x14
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_TURING_EFUSE_TESTBUS_READ_DISABLE_BMSK              0x80000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_TURING_EFUSE_TESTBUS_READ_DISABLE_SHFT                 0x13
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_LPASS_SENSOR_DBGEN_DISABLE_BMSK                  0x40000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_LPASS_SENSOR_DBGEN_DISABLE_SHFT                     0x12
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_PIMEM_DBGEN_DISABLE_BMSK                         0x20000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_PIMEM_DBGEN_DISABLE_SHFT                            0x11
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_RPM_DBGEN_DISABLE_BMSK                           0x10000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_RPM_DBGEN_DISABLE_SHFT                              0x10
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_WCSS_DBGEN_DISABLE_BMSK                           0x8000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_WCSS_DBGEN_DISABLE_SHFT                              0xf
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_LPASS_Q6_DBGEN_DISABLE_BMSK                       0x4000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_LPASS_Q6_DBGEN_DISABLE_SHFT                          0xe
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_DAP_DBGEN_DISABLE_BMSK                            0x2000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_DAP_DBGEN_DISABLE_SHFT                               0xd
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_APPS_DBGEN_DISABLE_BMSK                           0x1000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_APPS_DBGEN_DISABLE_SHFT                              0xc
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_DAP_DEVICEEN_DISABLE_BMSK                          0x800
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_DAP_DEVICEEN_DISABLE_SHFT                            0xb
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_RPM_DAPEN_DISABLE_BMSK                             0x400
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_RPM_DAPEN_DISABLE_SHFT                               0xa
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_DSI_0_DISABLE_BMSK                                    0x200
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_DSI_0_DISABLE_SHFT                                      0x9
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_DEBUG_BUS_DISABLE_BMSK                             0x100
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_DEBUG_BUS_DISABLE_SHFT                               0x8
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_DCC_DEBUG_DISABLE_BMSK                              0x80
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_DCC_DEBUG_DISABLE_SHFT                               0x7
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_APPS_APB_DFD_DISABLE_BMSK                           0x40
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_APPS_APB_DFD_DISABLE_SHFT                            0x6
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_GPMU_NIDEN_DISABLE_BMSK                             0x20
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_GPMU_NIDEN_DISABLE_SHFT                              0x5
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_GPMU_DBGEN_DISABLE_BMSK                             0x10
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_GPMU_DBGEN_DISABLE_SHFT                              0x4
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_GPMU_DAPEN_DISABLE_BMSK                              0x8
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QC_GPMU_DAPEN_DISABLE_SHFT                              0x3
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QDI_SPMI_DISABLE_BMSK                                   0x4
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_QDI_SPMI_DISABLE_SHFT                                   0x2
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_SM_BIST_DISABLE_BMSK                                    0x2
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_SM_BIST_DISABLE_SHFT                                    0x1
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_TIC_DISABLE_BMSK                                        0x1
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_LSB_TIC_DISABLE_SHFT                                        0x0

#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_ADDR                                             (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000031c)
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_OFFS                                             (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000031c)
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_RMSK                                             0xffffffff
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_ADDR, HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_RMSK)
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_SYS_APCCCFGEND_BMSK                              0x80000000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_SYS_APCCCFGEND_SHFT                                    0x1f
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_SYS_APCCCP15SDISABLE_BMSK                        0x40000000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_SYS_APCCCP15SDISABLE_SHFT                              0x1e
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_SYS_APCCCFGTE_BMSK                               0x20000000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_SYS_APCCCFGTE_SHFT                                     0x1d
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_PLL_MAX_BOOST_LVAL_BMSK                          0x1fe00000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_PLL_MAX_BOOST_LVAL_SHFT                                0x15
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_APPS_BOOT_FSM_FUSE_BMSK                            0x1c0000
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_APPS_BOOT_FSM_FUSE_SHFT                                0x12
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_PLL_MAX_FREQ_LVAL_BMSK                              0x3fc00
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_PLL_MAX_FREQ_LVAL_SHFT                                  0xa
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_QC_A5X_ISDB_SECURE_DBGEN_DISABLE_BMSK                 0x200
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_QC_A5X_ISDB_SECURE_DBGEN_DISABLE_SHFT                   0x9
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_QC_LPASS_SPIDEN_DISABLE_BMSK                          0x100
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_QC_LPASS_SPIDEN_DISABLE_SHFT                            0x8
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_QC_PIMEM_SPIDEN_DISABLE_BMSK                           0x80
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_QC_PIMEM_SPIDEN_DISABLE_SHFT                            0x7
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_QC_WCSS_SPIDEN_DISABLE_BMSK                            0x40
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_QC_WCSS_SPIDEN_DISABLE_SHFT                             0x6
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_QC_DAP_SPIDEN_DISABLE_BMSK                             0x20
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_QC_DAP_SPIDEN_DISABLE_SHFT                              0x5
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_QC_APPS_SPIDEN_DISABLE_BMSK                            0x10
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_QC_APPS_SPIDEN_DISABLE_SHFT                             0x4
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_QC_LPASS_SPNIDEN_DISABLE_BMSK                           0x8
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_QC_LPASS_SPNIDEN_DISABLE_SHFT                           0x3
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_QC_PIMEM_SPNIDEN_DISABLE_BMSK                           0x4
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_QC_PIMEM_SPNIDEN_DISABLE_SHFT                           0x2
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_QC_WCSS_SPNIDEN_DISABLE_BMSK                            0x2
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_QC_WCSS_SPNIDEN_DISABLE_SHFT                            0x1
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_QC_DAP_SPNIDEN_DISABLE_BMSK                             0x1
#define HWIO_QFPROM_RAW_CM_FEAT_CONFIG_ROW2_MSB_QC_DAP_SPNIDEN_DISABLE_SHFT                             0x0

#define HWIO_QFPROM_RAW_QC_SPARE_REGn_LSB_ADDR(n)                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x000002a0 + 0x8 * (n))
#define HWIO_QFPROM_RAW_QC_SPARE_REGn_LSB_OFFS(n)                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000002a0 + 0x8 * (n))
#define HWIO_QFPROM_RAW_QC_SPARE_REGn_LSB_RMSK                                                   0xffffffff
#define HWIO_QFPROM_RAW_QC_SPARE_REGn_LSB_MAXn                                                           18
#define HWIO_QFPROM_RAW_QC_SPARE_REGn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_QC_SPARE_REGn_LSB_ADDR(n), HWIO_QFPROM_RAW_QC_SPARE_REGn_LSB_RMSK)
#define HWIO_QFPROM_RAW_QC_SPARE_REGn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_QC_SPARE_REGn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_QC_SPARE_REGn_LSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_QC_SPARE_REGn_LSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_QC_SPARE_REGn_LSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_QC_SPARE_REGn_LSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_QC_SPARE_REGn_LSB_INI(n))
#define HWIO_QFPROM_RAW_QC_SPARE_REGn_LSB_QC_SPARE_BMSK                                          0xffffffff
#define HWIO_QFPROM_RAW_QC_SPARE_REGn_LSB_QC_SPARE_SHFT                                                 0x0

#define HWIO_QFPROM_RAW_QC_SPARE_REGn_MSB_ADDR(n)                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x000002a4 + 0x8 * (n))
#define HWIO_QFPROM_RAW_QC_SPARE_REGn_MSB_OFFS(n)                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000002a4 + 0x8 * (n))
#define HWIO_QFPROM_RAW_QC_SPARE_REGn_MSB_RMSK                                                   0xffffffff
#define HWIO_QFPROM_RAW_QC_SPARE_REGn_MSB_MAXn                                                           18
#define HWIO_QFPROM_RAW_QC_SPARE_REGn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_QC_SPARE_REGn_MSB_ADDR(n), HWIO_QFPROM_RAW_QC_SPARE_REGn_MSB_RMSK)
#define HWIO_QFPROM_RAW_QC_SPARE_REGn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_QC_SPARE_REGn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_QC_SPARE_REGn_MSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_QC_SPARE_REGn_MSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_QC_SPARE_REGn_MSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_QC_SPARE_REGn_MSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_QC_SPARE_REGn_MSB_INI(n))
#define HWIO_QFPROM_RAW_QC_SPARE_REGn_MSB_RSVD0_BMSK                                             0x80000000
#define HWIO_QFPROM_RAW_QC_SPARE_REGn_MSB_RSVD0_SHFT                                                   0x1f
#define HWIO_QFPROM_RAW_QC_SPARE_REGn_MSB_FEC_VALUE_BMSK                                         0x7f000000
#define HWIO_QFPROM_RAW_QC_SPARE_REGn_MSB_FEC_VALUE_SHFT                                               0x18
#define HWIO_QFPROM_RAW_QC_SPARE_REGn_MSB_QC_SPARE_BMSK                                            0xffffff
#define HWIO_QFPROM_RAW_QC_SPARE_REGn_MSB_QC_SPARE_SHFT                                                 0x0

#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROWn_LSB_ADDR(n)                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000338 + 0x8 * (n))
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROWn_LSB_OFFS(n)                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000338 + 0x8 * (n))
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROWn_LSB_RMSK                                         0xffffffff
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROWn_LSB_MAXn                                                  1
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROWn_LSB_ADDR(n), HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROWn_LSB_RMSK)
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROWn_LSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROWn_LSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROWn_LSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROWn_LSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROWn_LSB_INI(n))
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROWn_LSB_KEY_DATA0_BMSK                               0xffffffff
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROWn_LSB_KEY_DATA0_SHFT                                      0x0

#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROWn_MSB_ADDR(n)                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000033c + 0x8 * (n))
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROWn_MSB_OFFS(n)                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000033c + 0x8 * (n))
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROWn_MSB_RMSK                                         0xffffffff
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROWn_MSB_MAXn                                                  1
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROWn_MSB_ADDR(n), HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROWn_MSB_RMSK)
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROWn_MSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROWn_MSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROWn_MSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROWn_MSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROWn_MSB_INI(n))
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROWn_MSB_RSVD1_BMSK                                   0x80000000
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROWn_MSB_RSVD1_SHFT                                         0x1f
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROWn_MSB_FEC_VALUE_BMSK                               0x7f000000
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROWn_MSB_FEC_VALUE_SHFT                                     0x18
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROWn_MSB_KEY_DATA1_BMSK                                 0xffffff
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROWn_MSB_KEY_DATA1_SHFT                                      0x0

#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROW2_LSB_ADDR                                         (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000348)
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROW2_LSB_OFFS                                         (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000348)
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROW2_LSB_RMSK                                         0xffffffff
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROW2_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROW2_LSB_ADDR, HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROW2_LSB_RMSK)
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROW2_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROW2_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROW2_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROW2_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROW2_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROW2_LSB_ADDR,m,v,HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROW2_LSB_IN)
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROW2_LSB_RSVD0_BMSK                                   0xffff0000
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROW2_LSB_RSVD0_SHFT                                         0x10
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROW2_LSB_KEY_DATA0_BMSK                                   0xffff
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROW2_LSB_KEY_DATA0_SHFT                                      0x0

#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROW2_MSB_ADDR                                         (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000034c)
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROW2_MSB_OFFS                                         (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000034c)
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROW2_MSB_RMSK                                         0xffffffff
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROW2_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROW2_MSB_ADDR, HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROW2_MSB_RMSK)
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROW2_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROW2_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROW2_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROW2_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROW2_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROW2_MSB_ADDR,m,v,HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROW2_MSB_IN)
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROW2_MSB_RSVD1_BMSK                                   0x80000000
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROW2_MSB_RSVD1_SHFT                                         0x1f
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROW2_MSB_FEC_VALUE_BMSK                               0x7f000000
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROW2_MSB_FEC_VALUE_SHFT                                     0x18
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROW2_MSB_RSVD0_BMSK                                     0xffffff
#define HWIO_QFPROM_RAW_OEM_IMAGE_ENCR_KEY_ROW2_MSB_RSVD0_SHFT                                          0x0

#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_ADDR(n)                                            (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000350 + 0x8 * (n))
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_OFFS(n)                                            (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000350 + 0x8 * (n))
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_RMSK                                               0xffffffff
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_MAXn                                                        1
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_ADDR(n), HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_RMSK)
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_INI(n))
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_SEC_BOOT4_BMSK                                     0xff000000
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_SEC_BOOT4_SHFT                                           0x18
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_SEC_BOOT3_BMSK                                       0xff0000
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_SEC_BOOT3_SHFT                                           0x10
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_SEC_BOOT2_BMSK                                         0xff00
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_SEC_BOOT2_SHFT                                            0x8
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_SEC_BOOT1_BMSK                                           0xff
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_LSB_SEC_BOOT1_SHFT                                            0x0

#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_ADDR(n)                                            (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000354 + 0x8 * (n))
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_OFFS(n)                                            (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000354 + 0x8 * (n))
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_RMSK                                               0xffffffff
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_MAXn                                                        1
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_ADDR(n), HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_RMSK)
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_INI(n))
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_RSVD1_BMSK                                         0x80000000
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_RSVD1_SHFT                                               0x1f
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_FEC_VALUE_BMSK                                     0x7f000000
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_FEC_VALUE_SHFT                                           0x18
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_SEC_BOOT7_BMSK                                       0xff0000
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_SEC_BOOT7_SHFT                                           0x10
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_SEC_BOOT6_BMSK                                         0xff00
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_SEC_BOOT6_SHFT                                            0x8
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_SEC_BOOT5_BMSK                                           0xff
#define HWIO_QFPROM_RAW_OEM_SEC_BOOT_ROWn_MSB_SEC_BOOT5_SHFT                                            0x0

#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_LSB_ADDR(n)                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000360 + 0x8 * (n))
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_LSB_OFFS(n)                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000360 + 0x8 * (n))
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_LSB_RMSK                                     0xffffffff
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_LSB_MAXn                                              3
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_LSB_ADDR(n), HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_LSB_RMSK)
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_LSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_LSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_LSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_LSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_LSB_INI(n))
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_LSB_KEY_DATA0_BMSK                           0xffffffff
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_LSB_KEY_DATA0_SHFT                                  0x0

#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_ADDR(n)                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000364 + 0x8 * (n))
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_OFFS(n)                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000364 + 0x8 * (n))
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_RMSK                                     0xffffffff
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_MAXn                                              3
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_ADDR(n), HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_RMSK)
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_INI(n))
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_RSVD1_BMSK                               0x80000000
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_RSVD1_SHFT                                     0x1f
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_FEC_VALUE_BMSK                           0x7f000000
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_FEC_VALUE_SHFT                                 0x18
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_KEY_DATA1_BMSK                             0xffffff
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROWn_MSB_KEY_DATA1_SHFT                                  0x0

#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_LSB_ADDR                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000380)
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_LSB_OFFS                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000380)
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_LSB_RMSK                                     0xffffffff
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_LSB_ADDR, HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_LSB_RMSK)
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_LSB_ADDR,m,v,HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_LSB_IN)
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_LSB_KEY_DATA0_BMSK                           0xffffffff
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_LSB_KEY_DATA0_SHFT                                  0x0

#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_MSB_ADDR                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000384)
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_MSB_OFFS                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000384)
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_MSB_RMSK                                     0xffffffff
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_MSB_ADDR, HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_MSB_RMSK)
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_MSB_ADDR,m,v,HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_MSB_IN)
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_MSB_RSVD1_BMSK                               0x80000000
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_MSB_RSVD1_SHFT                                     0x1f
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_MSB_FEC_VALUE_BMSK                           0x7f000000
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_MSB_FEC_VALUE_SHFT                                 0x18
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_MSB_RSVD0_BMSK                                 0xffffff
#define HWIO_QFPROM_RAW_PRI_KEY_DERIVATION_KEY_ROW4_MSB_RSVD0_SHFT                                      0x0

#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_LSB_ADDR(n)                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000388 + 0x8 * (n))
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_LSB_OFFS(n)                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000388 + 0x8 * (n))
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_LSB_RMSK                                     0xffffffff
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_LSB_MAXn                                              3
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_LSB_ADDR(n), HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_LSB_RMSK)
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_LSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_LSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_LSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_LSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_LSB_INI(n))
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_LSB_KEY_DATA0_BMSK                           0xffffffff
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_LSB_KEY_DATA0_SHFT                                  0x0

#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_ADDR(n)                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000038c + 0x8 * (n))
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_OFFS(n)                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000038c + 0x8 * (n))
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_RMSK                                     0xffffffff
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_MAXn                                              3
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_ADDR(n), HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_RMSK)
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_INI(n))
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_RSVD1_BMSK                               0x80000000
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_RSVD1_SHFT                                     0x1f
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_FEC_VALUE_BMSK                           0x7f000000
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_FEC_VALUE_SHFT                                 0x18
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_KEY_DATA1_BMSK                             0xffffff
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROWn_MSB_KEY_DATA1_SHFT                                  0x0

#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_LSB_ADDR                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x000003a8)
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_LSB_OFFS                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000003a8)
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_LSB_RMSK                                     0xffffffff
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_LSB_ADDR, HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_LSB_RMSK)
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_LSB_ADDR,m,v,HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_LSB_IN)
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_LSB_KEY_DATA0_BMSK                           0xffffffff
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_LSB_KEY_DATA0_SHFT                                  0x0

#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_MSB_ADDR                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x000003ac)
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_MSB_OFFS                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000003ac)
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_MSB_RMSK                                     0xffffffff
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_MSB_ADDR, HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_MSB_RMSK)
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_MSB_ADDR,m,v,HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_MSB_IN)
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_MSB_RSVD1_BMSK                               0x80000000
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_MSB_RSVD1_SHFT                                     0x1f
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_MSB_FEC_VALUE_BMSK                           0x7f000000
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_MSB_FEC_VALUE_SHFT                                 0x18
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_MSB_RSVD0_BMSK                                 0xffffff
#define HWIO_QFPROM_RAW_SEC_KEY_DERIVATION_KEY_ROW4_MSB_RSVD0_SHFT                                      0x0

#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_ADDR(n)                                               (SECURITY_CONTROL_CORE_REG_BASE      + 0x000003b0 + 0x8 * (n))
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_OFFS(n)                                               (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000003b0 + 0x8 * (n))
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_RMSK                                                  0xffffffff
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_MAXn                                                          55
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_ADDR(n), HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_RMSK)
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_INI(n))
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_PATCH_DATA_BMSK                                       0xffffffff
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_LSB_PATCH_DATA_SHFT                                              0x0

#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_ADDR(n)                                               (SECURITY_CONTROL_CORE_REG_BASE      + 0x000003b4 + 0x8 * (n))
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_OFFS(n)                                               (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000003b4 + 0x8 * (n))
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_RMSK                                                  0xffffffff
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_MAXn                                                          55
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_ADDR(n), HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_RMSK)
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_INI(n))
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_RSVD1_BMSK                                            0x80000000
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_RSVD1_SHFT                                                  0x1f
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_FEC_VALUE_BMSK                                        0x7f000000
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_FEC_VALUE_SHFT                                              0x18
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_RSVD0_BMSK                                              0xfe0000
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_RSVD0_SHFT                                                  0x11
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_PATCH_ADDR_BMSK                                          0x1fffe
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_PATCH_ADDR_SHFT                                              0x1
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_PATCH_EN_BMSK                                                0x1
#define HWIO_QFPROM_RAW_ROM_PATCH_ROWn_MSB_PATCH_EN_SHFT                                                0x0

#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROWn_LSB_ADDR(n)                                         (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000570 + 0x8 * (n))
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROWn_LSB_OFFS(n)                                         (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000570 + 0x8 * (n))
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROWn_LSB_RMSK                                            0xffffffff
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROWn_LSB_MAXn                                                     1
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROWn_LSB_ADDR(n), HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROWn_LSB_RMSK)
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROWn_LSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROWn_LSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROWn_LSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROWn_LSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROWn_LSB_INI(n))
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROWn_LSB_KEY_DATA0_BMSK                                  0xffffffff
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROWn_LSB_KEY_DATA0_SHFT                                         0x0

#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROWn_MSB_ADDR(n)                                         (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000574 + 0x8 * (n))
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROWn_MSB_OFFS(n)                                         (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000574 + 0x8 * (n))
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROWn_MSB_RMSK                                            0xffffffff
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROWn_MSB_MAXn                                                     1
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROWn_MSB_ADDR(n), HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROWn_MSB_RMSK)
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROWn_MSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROWn_MSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROWn_MSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROWn_MSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROWn_MSB_INI(n))
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROWn_MSB_RSVD1_BMSK                                      0x80000000
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROWn_MSB_RSVD1_SHFT                                            0x1f
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROWn_MSB_FEC_VALUE_BMSK                                  0x7f000000
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROWn_MSB_FEC_VALUE_SHFT                                        0x18
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROWn_MSB_KEY_DATA1_BMSK                                    0xffffff
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROWn_MSB_KEY_DATA1_SHFT                                         0x0

#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROW2_LSB_ADDR                                            (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000580)
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROW2_LSB_OFFS                                            (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000580)
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROW2_LSB_RMSK                                            0xffffffff
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROW2_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROW2_LSB_ADDR, HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROW2_LSB_RMSK)
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROW2_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROW2_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROW2_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROW2_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROW2_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROW2_LSB_ADDR,m,v,HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROW2_LSB_IN)
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROW2_LSB_RSVD0_BMSK                                      0xffff0000
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROW2_LSB_RSVD0_SHFT                                            0x10
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROW2_LSB_KEY_DATA0_BMSK                                      0xffff
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROW2_LSB_KEY_DATA0_SHFT                                         0x0

#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROW2_MSB_ADDR                                            (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000584)
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROW2_MSB_OFFS                                            (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000584)
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROW2_MSB_RMSK                                            0xffffffff
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROW2_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROW2_MSB_ADDR, HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROW2_MSB_RMSK)
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROW2_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROW2_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROW2_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROW2_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROW2_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROW2_MSB_ADDR,m,v,HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROW2_MSB_IN)
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROW2_MSB_RSVD1_BMSK                                      0x80000000
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROW2_MSB_RSVD1_SHFT                                            0x1f
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROW2_MSB_FEC_VALUE_BMSK                                  0x7f000000
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROW2_MSB_FEC_VALUE_SHFT                                        0x18
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROW2_MSB_RSVD0_BMSK                                        0xffffff
#define HWIO_QFPROM_RAW_IMAGE_ENCR_KEY1_ROW2_MSB_RSVD0_SHFT                                             0x0

#define HWIO_QFPROM_RAW_PK_HASH1_ROWn_LSB_ADDR(n)                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000588 + 0x8 * (n))
#define HWIO_QFPROM_RAW_PK_HASH1_ROWn_LSB_OFFS(n)                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000588 + 0x8 * (n))
#define HWIO_QFPROM_RAW_PK_HASH1_ROWn_LSB_RMSK                                                   0xffffffff
#define HWIO_QFPROM_RAW_PK_HASH1_ROWn_LSB_MAXn                                                            3
#define HWIO_QFPROM_RAW_PK_HASH1_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_PK_HASH1_ROWn_LSB_ADDR(n), HWIO_QFPROM_RAW_PK_HASH1_ROWn_LSB_RMSK)
#define HWIO_QFPROM_RAW_PK_HASH1_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_PK_HASH1_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_PK_HASH1_ROWn_LSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_PK_HASH1_ROWn_LSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_PK_HASH1_ROWn_LSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_PK_HASH1_ROWn_LSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_PK_HASH1_ROWn_LSB_INI(n))
#define HWIO_QFPROM_RAW_PK_HASH1_ROWn_LSB_HASH_DATA0_BMSK                                        0xffffffff
#define HWIO_QFPROM_RAW_PK_HASH1_ROWn_LSB_HASH_DATA0_SHFT                                               0x0

#define HWIO_QFPROM_RAW_PK_HASH1_ROWn_MSB_ADDR(n)                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000058c + 0x8 * (n))
#define HWIO_QFPROM_RAW_PK_HASH1_ROWn_MSB_OFFS(n)                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000058c + 0x8 * (n))
#define HWIO_QFPROM_RAW_PK_HASH1_ROWn_MSB_RMSK                                                   0xffffffff
#define HWIO_QFPROM_RAW_PK_HASH1_ROWn_MSB_MAXn                                                            3
#define HWIO_QFPROM_RAW_PK_HASH1_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_PK_HASH1_ROWn_MSB_ADDR(n), HWIO_QFPROM_RAW_PK_HASH1_ROWn_MSB_RMSK)
#define HWIO_QFPROM_RAW_PK_HASH1_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_PK_HASH1_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_PK_HASH1_ROWn_MSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_PK_HASH1_ROWn_MSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_PK_HASH1_ROWn_MSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_PK_HASH1_ROWn_MSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_PK_HASH1_ROWn_MSB_INI(n))
#define HWIO_QFPROM_RAW_PK_HASH1_ROWn_MSB_RSVD1_BMSK                                             0x80000000
#define HWIO_QFPROM_RAW_PK_HASH1_ROWn_MSB_RSVD1_SHFT                                                   0x1f
#define HWIO_QFPROM_RAW_PK_HASH1_ROWn_MSB_FEC_VALUE_BMSK                                         0x7f000000
#define HWIO_QFPROM_RAW_PK_HASH1_ROWn_MSB_FEC_VALUE_SHFT                                               0x18
#define HWIO_QFPROM_RAW_PK_HASH1_ROWn_MSB_HASH_DATA1_BMSK                                          0xffffff
#define HWIO_QFPROM_RAW_PK_HASH1_ROWn_MSB_HASH_DATA1_SHFT                                               0x0

#define HWIO_QFPROM_RAW_PK_HASH1_ROW4_LSB_ADDR                                                   (SECURITY_CONTROL_CORE_REG_BASE      + 0x000005a8)
#define HWIO_QFPROM_RAW_PK_HASH1_ROW4_LSB_OFFS                                                   (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000005a8)
#define HWIO_QFPROM_RAW_PK_HASH1_ROW4_LSB_RMSK                                                   0xffffffff
#define HWIO_QFPROM_RAW_PK_HASH1_ROW4_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_PK_HASH1_ROW4_LSB_ADDR, HWIO_QFPROM_RAW_PK_HASH1_ROW4_LSB_RMSK)
#define HWIO_QFPROM_RAW_PK_HASH1_ROW4_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_PK_HASH1_ROW4_LSB_ADDR, m)
#define HWIO_QFPROM_RAW_PK_HASH1_ROW4_LSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_PK_HASH1_ROW4_LSB_ADDR,v)
#define HWIO_QFPROM_RAW_PK_HASH1_ROW4_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_PK_HASH1_ROW4_LSB_ADDR,m,v,HWIO_QFPROM_RAW_PK_HASH1_ROW4_LSB_IN)
#define HWIO_QFPROM_RAW_PK_HASH1_ROW4_LSB_HASH_DATA0_BMSK                                        0xffffffff
#define HWIO_QFPROM_RAW_PK_HASH1_ROW4_LSB_HASH_DATA0_SHFT                                               0x0

#define HWIO_QFPROM_RAW_PK_HASH1_ROW4_MSB_ADDR                                                   (SECURITY_CONTROL_CORE_REG_BASE      + 0x000005ac)
#define HWIO_QFPROM_RAW_PK_HASH1_ROW4_MSB_OFFS                                                   (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000005ac)
#define HWIO_QFPROM_RAW_PK_HASH1_ROW4_MSB_RMSK                                                   0xffffffff
#define HWIO_QFPROM_RAW_PK_HASH1_ROW4_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_RAW_PK_HASH1_ROW4_MSB_ADDR, HWIO_QFPROM_RAW_PK_HASH1_ROW4_MSB_RMSK)
#define HWIO_QFPROM_RAW_PK_HASH1_ROW4_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_RAW_PK_HASH1_ROW4_MSB_ADDR, m)
#define HWIO_QFPROM_RAW_PK_HASH1_ROW4_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_RAW_PK_HASH1_ROW4_MSB_ADDR,v)
#define HWIO_QFPROM_RAW_PK_HASH1_ROW4_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_PK_HASH1_ROW4_MSB_ADDR,m,v,HWIO_QFPROM_RAW_PK_HASH1_ROW4_MSB_IN)
#define HWIO_QFPROM_RAW_PK_HASH1_ROW4_MSB_RSVD1_BMSK                                             0x80000000
#define HWIO_QFPROM_RAW_PK_HASH1_ROW4_MSB_RSVD1_SHFT                                                   0x1f
#define HWIO_QFPROM_RAW_PK_HASH1_ROW4_MSB_FEC_VALUE_BMSK                                         0x7f000000
#define HWIO_QFPROM_RAW_PK_HASH1_ROW4_MSB_FEC_VALUE_SHFT                                               0x18
#define HWIO_QFPROM_RAW_PK_HASH1_ROW4_MSB_RSVD0_BMSK                                               0xfffffc
#define HWIO_QFPROM_RAW_PK_HASH1_ROW4_MSB_RSVD0_SHFT                                                    0x2
#define HWIO_QFPROM_RAW_PK_HASH1_ROW4_MSB_CURRENT_SW_ROT_MODEM_BMSK                                     0x2
#define HWIO_QFPROM_RAW_PK_HASH1_ROW4_MSB_CURRENT_SW_ROT_MODEM_SHFT                                     0x1
#define HWIO_QFPROM_RAW_PK_HASH1_ROW4_MSB_CURRENT_SW_ROT_APPS_BMSK                                      0x1
#define HWIO_QFPROM_RAW_PK_HASH1_ROW4_MSB_CURRENT_SW_ROT_APPS_SHFT                                      0x0

#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW0_LSB_ADDR(n)                                          (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000410 + 0x10 * (n))
#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW0_LSB_OFFS(n)                                          (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000410 + 0x10 * (n))
#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW0_LSB_RMSK                                             0xffffffff
#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW0_LSB_MAXn                                                     30
#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW0_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW0_LSB_ADDR(n), HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW0_LSB_RMSK)
#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW0_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW0_LSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW0_LSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW0_LSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW0_LSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW0_LSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW0_LSB_INI(n))
#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW0_LSB_OEM_SPARE_BMSK                                   0xffffffff
#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW0_LSB_OEM_SPARE_SHFT                                          0x0

#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW0_MSB_ADDR(n)                                          (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000414 + 0x10 * (n))
#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW0_MSB_OFFS(n)                                          (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000414 + 0x10 * (n))
#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW0_MSB_RMSK                                             0xffffffff
#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW0_MSB_MAXn                                                     30
#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW0_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW0_MSB_ADDR(n), HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW0_MSB_RMSK)
#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW0_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW0_MSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW0_MSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW0_MSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW0_MSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW0_MSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW0_MSB_INI(n))
#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW0_MSB_OEM_SPARE_BMSK                                   0xffffffff
#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW0_MSB_OEM_SPARE_SHFT                                          0x0

#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW1_LSB_ADDR(n)                                          (SECURITY_CONTROL_CORE_REG_BASE      + 0x00000418 + 0x10 * (n))
#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW1_LSB_OFFS(n)                                          (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00000418 + 0x10 * (n))
#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW1_LSB_RMSK                                             0xffffffff
#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW1_LSB_MAXn                                                     30
#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW1_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW1_LSB_ADDR(n), HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW1_LSB_RMSK)
#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW1_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW1_LSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW1_LSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW1_LSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW1_LSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW1_LSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW1_LSB_INI(n))
#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW1_LSB_OEM_SPARE_BMSK                                   0xffffffff
#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW1_LSB_OEM_SPARE_SHFT                                          0x0

#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW1_MSB_ADDR(n)                                          (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000041c + 0x10 * (n))
#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW1_MSB_OFFS(n)                                          (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000041c + 0x10 * (n))
#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW1_MSB_RMSK                                             0xffffffff
#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW1_MSB_MAXn                                                     30
#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW1_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW1_MSB_ADDR(n), HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW1_MSB_RMSK)
#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW1_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW1_MSB_ADDR(n), mask)
#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW1_MSB_OUTI(n,val)    \
        out_dword(HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW1_MSB_ADDR(n),val)
#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW1_MSB_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW1_MSB_ADDR(n),mask,val,HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW1_MSB_INI(n))
#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW1_MSB_OEM_SPARE_BMSK                                   0xffffffff
#define HWIO_QFPROM_RAW_OEM_SPARE_REGn_ROW1_MSB_OEM_SPARE_SHFT                                          0x0

#define HWIO_QFPROM_BLOW_TIMER_ADDR                                                              (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000203c)
#define HWIO_QFPROM_BLOW_TIMER_OFFS                                                              (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000203c)
#define HWIO_QFPROM_BLOW_TIMER_RMSK                                                                   0xfff
#define HWIO_QFPROM_BLOW_TIMER_IN          \
        in_dword_masked(HWIO_QFPROM_BLOW_TIMER_ADDR, HWIO_QFPROM_BLOW_TIMER_RMSK)
#define HWIO_QFPROM_BLOW_TIMER_INM(m)      \
        in_dword_masked(HWIO_QFPROM_BLOW_TIMER_ADDR, m)
#define HWIO_QFPROM_BLOW_TIMER_OUT(v)      \
        out_dword(HWIO_QFPROM_BLOW_TIMER_ADDR,v)
#define HWIO_QFPROM_BLOW_TIMER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_BLOW_TIMER_ADDR,m,v,HWIO_QFPROM_BLOW_TIMER_IN)
#define HWIO_QFPROM_BLOW_TIMER_BLOW_TIMER_BMSK                                                        0xfff
#define HWIO_QFPROM_BLOW_TIMER_BLOW_TIMER_SHFT                                                          0x0

#define HWIO_QFPROM_TEST_CTRL_ADDR                                                               (SECURITY_CONTROL_CORE_REG_BASE      + 0x00002040)
#define HWIO_QFPROM_TEST_CTRL_OFFS                                                               (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00002040)
#define HWIO_QFPROM_TEST_CTRL_RMSK                                                                      0xf
#define HWIO_QFPROM_TEST_CTRL_IN          \
        in_dword_masked(HWIO_QFPROM_TEST_CTRL_ADDR, HWIO_QFPROM_TEST_CTRL_RMSK)
#define HWIO_QFPROM_TEST_CTRL_INM(m)      \
        in_dword_masked(HWIO_QFPROM_TEST_CTRL_ADDR, m)
#define HWIO_QFPROM_TEST_CTRL_OUT(v)      \
        out_dword(HWIO_QFPROM_TEST_CTRL_ADDR,v)
#define HWIO_QFPROM_TEST_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_TEST_CTRL_ADDR,m,v,HWIO_QFPROM_TEST_CTRL_IN)
#define HWIO_QFPROM_TEST_CTRL_SEL_TST_ROM_BMSK                                                          0x8
#define HWIO_QFPROM_TEST_CTRL_SEL_TST_ROM_SHFT                                                          0x3
#define HWIO_QFPROM_TEST_CTRL_SEL_TST_WL_BMSK                                                           0x4
#define HWIO_QFPROM_TEST_CTRL_SEL_TST_WL_SHFT                                                           0x2
#define HWIO_QFPROM_TEST_CTRL_SEL_TST_BL_BMSK                                                           0x2
#define HWIO_QFPROM_TEST_CTRL_SEL_TST_BL_SHFT                                                           0x1
#define HWIO_QFPROM_TEST_CTRL_EN_FUSE_RES_MEAS_BMSK                                                     0x1
#define HWIO_QFPROM_TEST_CTRL_EN_FUSE_RES_MEAS_SHFT                                                     0x0

#define HWIO_QFPROM_ACCEL_ADDR                                                                   (SECURITY_CONTROL_CORE_REG_BASE      + 0x00002044)
#define HWIO_QFPROM_ACCEL_OFFS                                                                   (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00002044)
#define HWIO_QFPROM_ACCEL_RMSK                                                                        0xfff
#define HWIO_QFPROM_ACCEL_IN          \
        in_dword_masked(HWIO_QFPROM_ACCEL_ADDR, HWIO_QFPROM_ACCEL_RMSK)
#define HWIO_QFPROM_ACCEL_INM(m)      \
        in_dword_masked(HWIO_QFPROM_ACCEL_ADDR, m)
#define HWIO_QFPROM_ACCEL_OUT(v)      \
        out_dword(HWIO_QFPROM_ACCEL_ADDR,v)
#define HWIO_QFPROM_ACCEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_ACCEL_ADDR,m,v,HWIO_QFPROM_ACCEL_IN)
#define HWIO_QFPROM_ACCEL_QFPROM_GATELAST_BMSK                                                        0x800
#define HWIO_QFPROM_ACCEL_QFPROM_GATELAST_SHFT                                                          0xb
#define HWIO_QFPROM_ACCEL_QFPROM_TRIPPT_SEL_BMSK                                                      0x700
#define HWIO_QFPROM_ACCEL_QFPROM_TRIPPT_SEL_SHFT                                                        0x8
#define HWIO_QFPROM_ACCEL_QFPROM_ACCEL_BMSK                                                            0xff
#define HWIO_QFPROM_ACCEL_QFPROM_ACCEL_SHFT                                                             0x0

#define HWIO_QFPROM_BLOW_STATUS_ADDR                                                             (SECURITY_CONTROL_CORE_REG_BASE      + 0x00002048)
#define HWIO_QFPROM_BLOW_STATUS_OFFS                                                             (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00002048)
#define HWIO_QFPROM_BLOW_STATUS_RMSK                                                                    0x3
#define HWIO_QFPROM_BLOW_STATUS_IN          \
        in_dword_masked(HWIO_QFPROM_BLOW_STATUS_ADDR, HWIO_QFPROM_BLOW_STATUS_RMSK)
#define HWIO_QFPROM_BLOW_STATUS_INM(m)      \
        in_dword_masked(HWIO_QFPROM_BLOW_STATUS_ADDR, m)
#define HWIO_QFPROM_BLOW_STATUS_QFPROM_WR_ERR_BMSK                                                      0x2
#define HWIO_QFPROM_BLOW_STATUS_QFPROM_WR_ERR_SHFT                                                      0x1
#define HWIO_QFPROM_BLOW_STATUS_QFPROM_BUSY_BMSK                                                        0x1
#define HWIO_QFPROM_BLOW_STATUS_QFPROM_BUSY_SHFT                                                        0x0

#define HWIO_QFPROM_ROM_ERROR_ADDR                                                               (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000204c)
#define HWIO_QFPROM_ROM_ERROR_OFFS                                                               (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000204c)
#define HWIO_QFPROM_ROM_ERROR_RMSK                                                                      0x1
#define HWIO_QFPROM_ROM_ERROR_IN          \
        in_dword_masked(HWIO_QFPROM_ROM_ERROR_ADDR, HWIO_QFPROM_ROM_ERROR_RMSK)
#define HWIO_QFPROM_ROM_ERROR_INM(m)      \
        in_dword_masked(HWIO_QFPROM_ROM_ERROR_ADDR, m)
#define HWIO_QFPROM_ROM_ERROR_ERROR_BMSK                                                                0x1
#define HWIO_QFPROM_ROM_ERROR_ERROR_SHFT                                                                0x0

#define HWIO_QFPROM0_MATCH_STATUS_ADDR                                                           (SECURITY_CONTROL_CORE_REG_BASE      + 0x00002050)
#define HWIO_QFPROM0_MATCH_STATUS_OFFS                                                           (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00002050)
#define HWIO_QFPROM0_MATCH_STATUS_RMSK                                                           0xffffffff
#define HWIO_QFPROM0_MATCH_STATUS_IN          \
        in_dword_masked(HWIO_QFPROM0_MATCH_STATUS_ADDR, HWIO_QFPROM0_MATCH_STATUS_RMSK)
#define HWIO_QFPROM0_MATCH_STATUS_INM(m)      \
        in_dword_masked(HWIO_QFPROM0_MATCH_STATUS_ADDR, m)
#define HWIO_QFPROM0_MATCH_STATUS_FLAG_BMSK                                                      0xffffffff
#define HWIO_QFPROM0_MATCH_STATUS_FLAG_SHFT                                                             0x0

#define HWIO_QFPROM1_MATCH_STATUS_ADDR                                                           (SECURITY_CONTROL_CORE_REG_BASE      + 0x00002054)
#define HWIO_QFPROM1_MATCH_STATUS_OFFS                                                           (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00002054)
#define HWIO_QFPROM1_MATCH_STATUS_RMSK                                                           0xffffffff
#define HWIO_QFPROM1_MATCH_STATUS_IN          \
        in_dword_masked(HWIO_QFPROM1_MATCH_STATUS_ADDR, HWIO_QFPROM1_MATCH_STATUS_RMSK)
#define HWIO_QFPROM1_MATCH_STATUS_INM(m)      \
        in_dword_masked(HWIO_QFPROM1_MATCH_STATUS_ADDR, m)
#define HWIO_QFPROM1_MATCH_STATUS_FLAG_BMSK                                                      0xffffffff
#define HWIO_QFPROM1_MATCH_STATUS_FLAG_SHFT                                                             0x0

#define HWIO_FEC_ESR_ADDR                                                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x00002058)
#define HWIO_FEC_ESR_OFFS                                                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00002058)
#define HWIO_FEC_ESR_RMSK                                                                            0x2fdf
#define HWIO_FEC_ESR_IN          \
        in_dword_masked(HWIO_FEC_ESR_ADDR, HWIO_FEC_ESR_RMSK)
#define HWIO_FEC_ESR_INM(m)      \
        in_dword_masked(HWIO_FEC_ESR_ADDR, m)
#define HWIO_FEC_ESR_OUT(v)      \
        out_dword(HWIO_FEC_ESR_ADDR,v)
#define HWIO_FEC_ESR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_FEC_ESR_ADDR,m,v,HWIO_FEC_ESR_IN)
#define HWIO_FEC_ESR_CORR_SW_ACC_BMSK                                                                0x2000
#define HWIO_FEC_ESR_CORR_SW_ACC_SHFT                                                                   0xd
#define HWIO_FEC_ESR_CORR_SECURE_CHANNEL_BMSK                                                         0x800
#define HWIO_FEC_ESR_CORR_SECURE_CHANNEL_SHFT                                                           0xb
#define HWIO_FEC_ESR_CORR_BOOT_ROM_BMSK                                                               0x400
#define HWIO_FEC_ESR_CORR_BOOT_ROM_SHFT                                                                 0xa
#define HWIO_FEC_ESR_CORR_FUSE_SENSE_BMSK                                                             0x200
#define HWIO_FEC_ESR_CORR_FUSE_SENSE_SHFT                                                               0x9
#define HWIO_FEC_ESR_CORR_MULT_BMSK                                                                   0x100
#define HWIO_FEC_ESR_CORR_MULT_SHFT                                                                     0x8
#define HWIO_FEC_ESR_CORR_SEEN_BMSK                                                                    0x80
#define HWIO_FEC_ESR_CORR_SEEN_SHFT                                                                     0x7
#define HWIO_FEC_ESR_ERR_SW_ACC_BMSK                                                                   0x40
#define HWIO_FEC_ESR_ERR_SW_ACC_SHFT                                                                    0x6
#define HWIO_FEC_ESR_ERR_SECURE_CHANNEL_BMSK                                                           0x10
#define HWIO_FEC_ESR_ERR_SECURE_CHANNEL_SHFT                                                            0x4
#define HWIO_FEC_ESR_ERR_BOOT_ROM_BMSK                                                                  0x8
#define HWIO_FEC_ESR_ERR_BOOT_ROM_SHFT                                                                  0x3
#define HWIO_FEC_ESR_ERR_FUSE_SENSE_BMSK                                                                0x4
#define HWIO_FEC_ESR_ERR_FUSE_SENSE_SHFT                                                                0x2
#define HWIO_FEC_ESR_ERR_MULT_BMSK                                                                      0x2
#define HWIO_FEC_ESR_ERR_MULT_SHFT                                                                      0x1
#define HWIO_FEC_ESR_ERR_SEEN_BMSK                                                                      0x1
#define HWIO_FEC_ESR_ERR_SEEN_SHFT                                                                      0x0

#define HWIO_FEC_EAR_ADDR                                                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000205c)
#define HWIO_FEC_EAR_OFFS                                                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000205c)
#define HWIO_FEC_EAR_RMSK                                                                        0xffffffff
#define HWIO_FEC_EAR_IN          \
        in_dword_masked(HWIO_FEC_EAR_ADDR, HWIO_FEC_EAR_RMSK)
#define HWIO_FEC_EAR_INM(m)      \
        in_dword_masked(HWIO_FEC_EAR_ADDR, m)
#define HWIO_FEC_EAR_CORR_ADDR_BMSK                                                              0xffff0000
#define HWIO_FEC_EAR_CORR_ADDR_SHFT                                                                    0x10
#define HWIO_FEC_EAR_ERR_ADDR_BMSK                                                                   0xffff
#define HWIO_FEC_EAR_ERR_ADDR_SHFT                                                                      0x0

#define HWIO_QFPROM_BIST_CTRL_ADDR                                                               (SECURITY_CONTROL_CORE_REG_BASE      + 0x00002060)
#define HWIO_QFPROM_BIST_CTRL_OFFS                                                               (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00002060)
#define HWIO_QFPROM_BIST_CTRL_RMSK                                                                     0xff
#define HWIO_QFPROM_BIST_CTRL_IN          \
        in_dword_masked(HWIO_QFPROM_BIST_CTRL_ADDR, HWIO_QFPROM_BIST_CTRL_RMSK)
#define HWIO_QFPROM_BIST_CTRL_INM(m)      \
        in_dword_masked(HWIO_QFPROM_BIST_CTRL_ADDR, m)
#define HWIO_QFPROM_BIST_CTRL_OUT(v)      \
        out_dword(HWIO_QFPROM_BIST_CTRL_ADDR,v)
#define HWIO_QFPROM_BIST_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_BIST_CTRL_ADDR,m,v,HWIO_QFPROM_BIST_CTRL_IN)
#define HWIO_QFPROM_BIST_CTRL_AUTH_REGION_BMSK                                                         0xfc
#define HWIO_QFPROM_BIST_CTRL_AUTH_REGION_SHFT                                                          0x2
#define HWIO_QFPROM_BIST_CTRL_SHA_ENABLE_BMSK                                                           0x2
#define HWIO_QFPROM_BIST_CTRL_SHA_ENABLE_SHFT                                                           0x1
#define HWIO_QFPROM_BIST_CTRL_START_BMSK                                                                0x1
#define HWIO_QFPROM_BIST_CTRL_START_SHFT                                                                0x0

#define HWIO_QFPROM_BIST_ERROR0_ADDR                                                             (SECURITY_CONTROL_CORE_REG_BASE      + 0x00002064)
#define HWIO_QFPROM_BIST_ERROR0_OFFS                                                             (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00002064)
#define HWIO_QFPROM_BIST_ERROR0_RMSK                                                             0xffffffff
#define HWIO_QFPROM_BIST_ERROR0_IN          \
        in_dword_masked(HWIO_QFPROM_BIST_ERROR0_ADDR, HWIO_QFPROM_BIST_ERROR0_RMSK)
#define HWIO_QFPROM_BIST_ERROR0_INM(m)      \
        in_dword_masked(HWIO_QFPROM_BIST_ERROR0_ADDR, m)
#define HWIO_QFPROM_BIST_ERROR0_ERROR_BMSK                                                       0xffffffff
#define HWIO_QFPROM_BIST_ERROR0_ERROR_SHFT                                                              0x0

#define HWIO_QFPROM_BIST_ERROR1_ADDR                                                             (SECURITY_CONTROL_CORE_REG_BASE      + 0x00002068)
#define HWIO_QFPROM_BIST_ERROR1_OFFS                                                             (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00002068)
#define HWIO_QFPROM_BIST_ERROR1_RMSK                                                             0xffffffff
#define HWIO_QFPROM_BIST_ERROR1_IN          \
        in_dword_masked(HWIO_QFPROM_BIST_ERROR1_ADDR, HWIO_QFPROM_BIST_ERROR1_RMSK)
#define HWIO_QFPROM_BIST_ERROR1_INM(m)      \
        in_dword_masked(HWIO_QFPROM_BIST_ERROR1_ADDR, m)
#define HWIO_QFPROM_BIST_ERROR1_ERROR_BMSK                                                       0xffffffff
#define HWIO_QFPROM_BIST_ERROR1_ERROR_SHFT                                                              0x0

#define HWIO_QFPROM_HASH_SIGNATUREn_ADDR(n)                                                      (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000206c + 0x4 * (n))
#define HWIO_QFPROM_HASH_SIGNATUREn_OFFS(n)                                                      (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000206c + 0x4 * (n))
#define HWIO_QFPROM_HASH_SIGNATUREn_RMSK                                                         0xffffffff
#define HWIO_QFPROM_HASH_SIGNATUREn_MAXn                                                                  7
#define HWIO_QFPROM_HASH_SIGNATUREn_INI(n)        \
        in_dword_masked(HWIO_QFPROM_HASH_SIGNATUREn_ADDR(n), HWIO_QFPROM_HASH_SIGNATUREn_RMSK)
#define HWIO_QFPROM_HASH_SIGNATUREn_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_HASH_SIGNATUREn_ADDR(n), mask)
#define HWIO_QFPROM_HASH_SIGNATUREn_HASH_VALUE_BMSK                                              0xffffffff
#define HWIO_QFPROM_HASH_SIGNATUREn_HASH_VALUE_SHFT                                                     0x0

#define HWIO_HW_KEY_STATUS_ADDR                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000208c)
#define HWIO_HW_KEY_STATUS_OFFS                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000208c)
#define HWIO_HW_KEY_STATUS_RMSK                                                                       0x7ff
#define HWIO_HW_KEY_STATUS_IN          \
        in_dword_masked(HWIO_HW_KEY_STATUS_ADDR, HWIO_HW_KEY_STATUS_RMSK)
#define HWIO_HW_KEY_STATUS_INM(m)      \
        in_dword_masked(HWIO_HW_KEY_STATUS_ADDR, m)
#define HWIO_HW_KEY_STATUS_MSA_SECURE_BMSK                                                            0x400
#define HWIO_HW_KEY_STATUS_MSA_SECURE_SHFT                                                              0xa
#define HWIO_HW_KEY_STATUS_APPS_SECURE_BMSK                                                           0x200
#define HWIO_HW_KEY_STATUS_APPS_SECURE_SHFT                                                             0x9
#define HWIO_HW_KEY_STATUS_KDF_AND_HW_KEY_SHIFT_DONE_BMSK                                             0x100
#define HWIO_HW_KEY_STATUS_KDF_AND_HW_KEY_SHIFT_DONE_SHFT                                               0x8
#define HWIO_HW_KEY_STATUS_HW_KEY_SHIFT_DONE_BMSK                                                      0x80
#define HWIO_HW_KEY_STATUS_HW_KEY_SHIFT_DONE_SHFT                                                       0x7
#define HWIO_HW_KEY_STATUS_FUSE_SENSE_DONE_BMSK                                                        0x40
#define HWIO_HW_KEY_STATUS_FUSE_SENSE_DONE_SHFT                                                         0x6
#define HWIO_HW_KEY_STATUS_CRI_CM_BOOT_DONE_BMSK                                                       0x20
#define HWIO_HW_KEY_STATUS_CRI_CM_BOOT_DONE_SHFT                                                        0x5
#define HWIO_HW_KEY_STATUS_KDF_DONE_BMSK                                                               0x10
#define HWIO_HW_KEY_STATUS_KDF_DONE_SHFT                                                                0x4
#define HWIO_HW_KEY_STATUS_MSA_KEYS_BLOCKED_BMSK                                                        0x8
#define HWIO_HW_KEY_STATUS_MSA_KEYS_BLOCKED_SHFT                                                        0x3
#define HWIO_HW_KEY_STATUS_APPS_KEYS_BLOCKED_BMSK                                                       0x4
#define HWIO_HW_KEY_STATUS_APPS_KEYS_BLOCKED_SHFT                                                       0x2
#define HWIO_HW_KEY_STATUS_SEC_KEY_DERIVATION_KEY_BLOWN_BMSK                                            0x2
#define HWIO_HW_KEY_STATUS_SEC_KEY_DERIVATION_KEY_BLOWN_SHFT                                            0x1
#define HWIO_HW_KEY_STATUS_PRI_KEY_DERIVATION_KEY_BLOWN_BMSK                                            0x1
#define HWIO_HW_KEY_STATUS_PRI_KEY_DERIVATION_KEY_BLOWN_SHFT                                            0x0

#define HWIO_RESET_JDR_STATUS_ADDR                                                               (SECURITY_CONTROL_CORE_REG_BASE      + 0x00002090)
#define HWIO_RESET_JDR_STATUS_OFFS                                                               (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00002090)
#define HWIO_RESET_JDR_STATUS_RMSK                                                                      0x3
#define HWIO_RESET_JDR_STATUS_IN          \
        in_dword_masked(HWIO_RESET_JDR_STATUS_ADDR, HWIO_RESET_JDR_STATUS_RMSK)
#define HWIO_RESET_JDR_STATUS_INM(m)      \
        in_dword_masked(HWIO_RESET_JDR_STATUS_ADDR, m)
#define HWIO_RESET_JDR_STATUS_FORCE_RESET_BMSK                                                          0x2
#define HWIO_RESET_JDR_STATUS_FORCE_RESET_SHFT                                                          0x1
#define HWIO_RESET_JDR_STATUS_DISABLE_SYSTEM_RESET_BMSK                                                 0x1
#define HWIO_RESET_JDR_STATUS_DISABLE_SYSTEM_RESET_SHFT                                                 0x0

#define HWIO_ATPG_JDR_STATUS_ADDR                                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x00002094)
#define HWIO_ATPG_JDR_STATUS_OFFS                                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00002094)
#define HWIO_ATPG_JDR_STATUS_RMSK                                                                       0x1
#define HWIO_ATPG_JDR_STATUS_IN          \
        in_dword_masked(HWIO_ATPG_JDR_STATUS_ADDR, HWIO_ATPG_JDR_STATUS_RMSK)
#define HWIO_ATPG_JDR_STATUS_INM(m)      \
        in_dword_masked(HWIO_ATPG_JDR_STATUS_ADDR, m)
#define HWIO_ATPG_JDR_STATUS_FUSE_SENSE_ATPG_CTL_BMSK                                                   0x1
#define HWIO_ATPG_JDR_STATUS_FUSE_SENSE_ATPG_CTL_SHFT                                                   0x0

#define HWIO_FEAT_PROV_OUTn_ADDR(n)                                                              (SECURITY_CONTROL_CORE_REG_BASE      + 0x00002098 + 0x4 * (n))
#define HWIO_FEAT_PROV_OUTn_OFFS(n)                                                              (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00002098 + 0x4 * (n))
#define HWIO_FEAT_PROV_OUTn_RMSK                                                                 0xffffffff
#define HWIO_FEAT_PROV_OUTn_MAXn                                                                          3
#define HWIO_FEAT_PROV_OUTn_INI(n)        \
        in_dword_masked(HWIO_FEAT_PROV_OUTn_ADDR(n), HWIO_FEAT_PROV_OUTn_RMSK)
#define HWIO_FEAT_PROV_OUTn_INMI(n,mask)    \
        in_dword_masked(HWIO_FEAT_PROV_OUTn_ADDR(n), mask)
#define HWIO_FEAT_PROV_OUTn_FEAT_PROV_OUT_VALUE_BMSK                                             0xffffffff
#define HWIO_FEAT_PROV_OUTn_FEAT_PROV_OUT_VALUE_SHFT                                                    0x0

#define HWIO_SEC_CTRL_MISC_CONFIG_STATUSn_ADDR(n)                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x000020a8 + 0x4 * (n))
#define HWIO_SEC_CTRL_MISC_CONFIG_STATUSn_OFFS(n)                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000020a8 + 0x4 * (n))
#define HWIO_SEC_CTRL_MISC_CONFIG_STATUSn_RMSK                                                   0xffffffff
#define HWIO_SEC_CTRL_MISC_CONFIG_STATUSn_MAXn                                                            3
#define HWIO_SEC_CTRL_MISC_CONFIG_STATUSn_INI(n)        \
        in_dword_masked(HWIO_SEC_CTRL_MISC_CONFIG_STATUSn_ADDR(n), HWIO_SEC_CTRL_MISC_CONFIG_STATUSn_RMSK)
#define HWIO_SEC_CTRL_MISC_CONFIG_STATUSn_INMI(n,mask)    \
        in_dword_masked(HWIO_SEC_CTRL_MISC_CONFIG_STATUSn_ADDR(n), mask)
#define HWIO_SEC_CTRL_MISC_CONFIG_STATUSn_SEC_CTRL_MISC_CONFIG_STATUS_VALUE_BMSK                 0xffffffff
#define HWIO_SEC_CTRL_MISC_CONFIG_STATUSn_SEC_CTRL_MISC_CONFIG_STATUS_VALUE_SHFT                        0x0

#define HWIO_QFPROM_CORR_CRI_CM_PRIVATEn_ADDR(n)                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004000 + 0x4 * (n))
#define HWIO_QFPROM_CORR_CRI_CM_PRIVATEn_OFFS(n)                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004000 + 0x4 * (n))
#define HWIO_QFPROM_CORR_CRI_CM_PRIVATEn_RMSK                                                    0xffffffff
#define HWIO_QFPROM_CORR_CRI_CM_PRIVATEn_MAXn                                                            71
#define HWIO_QFPROM_CORR_CRI_CM_PRIVATEn_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_CRI_CM_PRIVATEn_ADDR(n), HWIO_QFPROM_CORR_CRI_CM_PRIVATEn_RMSK)
#define HWIO_QFPROM_CORR_CRI_CM_PRIVATEn_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_CRI_CM_PRIVATEn_ADDR(n), mask)
#define HWIO_QFPROM_CORR_CRI_CM_PRIVATEn_CRI_CM_PRIVATE_BMSK                                     0xffffffff
#define HWIO_QFPROM_CORR_CRI_CM_PRIVATEn_CRI_CM_PRIVATE_SHFT                                            0x0

#define HWIO_QFPROM_CORR_QC_SPARE_REGIONn_ADDR(n)                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004120 + 0x4 * (n))
#define HWIO_QFPROM_CORR_QC_SPARE_REGIONn_OFFS(n)                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004120 + 0x4 * (n))
#define HWIO_QFPROM_CORR_QC_SPARE_REGIONn_RMSK                                                   0xffffffff
#define HWIO_QFPROM_CORR_QC_SPARE_REGIONn_MAXn                                                            3
#define HWIO_QFPROM_CORR_QC_SPARE_REGIONn_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_QC_SPARE_REGIONn_ADDR(n), HWIO_QFPROM_CORR_QC_SPARE_REGIONn_RMSK)
#define HWIO_QFPROM_CORR_QC_SPARE_REGIONn_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_QC_SPARE_REGIONn_ADDR(n), mask)
#define HWIO_QFPROM_CORR_QC_SPARE_REGIONn_QC_SPARE_BMSK                                          0xffffffff
#define HWIO_QFPROM_CORR_QC_SPARE_REGIONn_QC_SPARE_SHFT                                                 0x0

#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_ADDR                                                       (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004130)
#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_OFFS                                                       (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004130)
#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_RMSK                                                       0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW0_LSB_ADDR, HWIO_QFPROM_CORR_PTE_ROW0_LSB_RMSK)
#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW0_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_PTE_DATA0_BMSK                                             0xe0000000
#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_PTE_DATA0_SHFT                                                   0x1d
#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_MACCHIATO_EN_BMSK                                          0x10000000
#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_MACCHIATO_EN_SHFT                                                0x1c
#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_FEATURE_ID_BMSK                                             0xff00000
#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_FEATURE_ID_SHFT                                                  0x14
#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_JTAG_ID_BMSK                                                  0xfffff
#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_JTAG_ID_SHFT                                                      0x0

#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_ADDR                                                       (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004134)
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_OFFS                                                       (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004134)
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_RMSK                                                       0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW0_MSB_ADDR, HWIO_QFPROM_CORR_PTE_ROW0_MSB_RMSK)
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW0_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_PTE_DATA1_BMSK                                             0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_PTE_DATA1_SHFT                                                    0x0

#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_ADDR                                                       (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004138)
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_OFFS                                                       (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004138)
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_RMSK                                                       0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW1_LSB_ADDR, HWIO_QFPROM_CORR_PTE_ROW1_LSB_RMSK)
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW1_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_SERIAL_NUM_BMSK                                            0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_SERIAL_NUM_SHFT                                                   0x0

#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_ADDR                                                       (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000413c)
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_OFFS                                                       (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000413c)
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_RMSK                                                       0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW1_MSB_ADDR, HWIO_QFPROM_CORR_PTE_ROW1_MSB_RMSK)
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW1_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_PTE_DATA1_BMSK                                             0xffff0000
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_PTE_DATA1_SHFT                                                   0x10
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_CHIP_ID_BMSK                                                   0xffff
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_CHIP_ID_SHFT                                                      0x0

#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_ADDR                                                       (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004140)
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_OFFS                                                       (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004140)
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_RMSK                                                       0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW2_LSB_ADDR, HWIO_QFPROM_CORR_PTE_ROW2_LSB_RMSK)
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW2_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_PTE_DATA0_BMSK                                             0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_PTE_DATA0_SHFT                                                    0x0

#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_ADDR                                                       (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004144)
#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_OFFS                                                       (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004144)
#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_RMSK                                                       0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW2_MSB_ADDR, HWIO_QFPROM_CORR_PTE_ROW2_MSB_RMSK)
#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW2_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_PTE_DATA1_BMSK                                             0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_PTE_DATA1_SHFT                                                    0x0

#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_ADDR                                                       (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004148)
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_OFFS                                                       (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004148)
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_RMSK                                                       0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW3_LSB_ADDR, HWIO_QFPROM_CORR_PTE_ROW3_LSB_RMSK)
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW3_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_PTE_DATA0_BMSK                                             0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_PTE_DATA0_SHFT                                                    0x0

#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_ADDR                                                       (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000414c)
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_OFFS                                                       (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000414c)
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_RMSK                                                       0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW3_MSB_ADDR, HWIO_QFPROM_CORR_PTE_ROW3_MSB_RMSK)
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW3_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_PTE_DATA1_BMSK                                             0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_PTE_DATA1_SHFT                                                    0x0

#define HWIO_QFPROM_CORR_RD_PERM_LSB_ADDR                                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004150)
#define HWIO_QFPROM_CORR_RD_PERM_LSB_OFFS                                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004150)
#define HWIO_QFPROM_CORR_RD_PERM_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_RD_PERM_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_RD_PERM_LSB_ADDR, HWIO_QFPROM_CORR_RD_PERM_LSB_RMSK)
#define HWIO_QFPROM_CORR_RD_PERM_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_RD_PERM_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_RD_PERM_LSB_RSVD0_BMSK                                                  0x80000000
#define HWIO_QFPROM_CORR_RD_PERM_LSB_RSVD0_SHFT                                                        0x1f
#define HWIO_QFPROM_CORR_RD_PERM_LSB_OEM_SPARE_REG30_BMSK                                        0x40000000
#define HWIO_QFPROM_CORR_RD_PERM_LSB_OEM_SPARE_REG30_SHFT                                              0x1e
#define HWIO_QFPROM_CORR_RD_PERM_LSB_OEM_SPARE_REG29_BMSK                                        0x20000000
#define HWIO_QFPROM_CORR_RD_PERM_LSB_OEM_SPARE_REG29_SHFT                                              0x1d
#define HWIO_QFPROM_CORR_RD_PERM_LSB_OEM_SPARE_REG28_BMSK                                        0x10000000
#define HWIO_QFPROM_CORR_RD_PERM_LSB_OEM_SPARE_REG28_SHFT                                              0x1c
#define HWIO_QFPROM_CORR_RD_PERM_LSB_OEM_SPARE_REG27_BMSK                                         0x8000000
#define HWIO_QFPROM_CORR_RD_PERM_LSB_OEM_SPARE_REG27_SHFT                                              0x1b
#define HWIO_QFPROM_CORR_RD_PERM_LSB_OEM_SPARE_REG26_BMSK                                         0x4000000
#define HWIO_QFPROM_CORR_RD_PERM_LSB_OEM_SPARE_REG26_SHFT                                              0x1a
#define HWIO_QFPROM_CORR_RD_PERM_LSB_PK_HASH1_BMSK                                                0x2000000
#define HWIO_QFPROM_CORR_RD_PERM_LSB_PK_HASH1_SHFT                                                     0x19
#define HWIO_QFPROM_CORR_RD_PERM_LSB_IMAGE_ENCR_KEY1_BMSK                                         0x1000000
#define HWIO_QFPROM_CORR_RD_PERM_LSB_IMAGE_ENCR_KEY1_SHFT                                              0x18
#define HWIO_QFPROM_CORR_RD_PERM_LSB_BOOT_ROM_PATCH_BMSK                                           0x800000
#define HWIO_QFPROM_CORR_RD_PERM_LSB_BOOT_ROM_PATCH_SHFT                                               0x17
#define HWIO_QFPROM_CORR_RD_PERM_LSB_SEC_KEY_DERIVATION_KEY_BMSK                                   0x400000
#define HWIO_QFPROM_CORR_RD_PERM_LSB_SEC_KEY_DERIVATION_KEY_SHFT                                       0x16
#define HWIO_QFPROM_CORR_RD_PERM_LSB_PRI_KEY_DERIVATION_KEY_BMSK                                   0x200000
#define HWIO_QFPROM_CORR_RD_PERM_LSB_PRI_KEY_DERIVATION_KEY_SHFT                                       0x15
#define HWIO_QFPROM_CORR_RD_PERM_LSB_OEM_SEC_BOOT_BMSK                                             0x100000
#define HWIO_QFPROM_CORR_RD_PERM_LSB_OEM_SEC_BOOT_SHFT                                                 0x14
#define HWIO_QFPROM_CORR_RD_PERM_LSB_OEM_IMAGE_ENCR_KEY_BMSK                                        0x80000
#define HWIO_QFPROM_CORR_RD_PERM_LSB_OEM_IMAGE_ENCR_KEY_SHFT                                           0x13
#define HWIO_QFPROM_CORR_RD_PERM_LSB_QC_SPARE_REG18_BMSK                                            0x40000
#define HWIO_QFPROM_CORR_RD_PERM_LSB_QC_SPARE_REG18_SHFT                                               0x12
#define HWIO_QFPROM_CORR_RD_PERM_LSB_QC_SPARE_REG17_BMSK                                            0x20000
#define HWIO_QFPROM_CORR_RD_PERM_LSB_QC_SPARE_REG17_SHFT                                               0x11
#define HWIO_QFPROM_CORR_RD_PERM_LSB_QC_SPARE_REG16_BMSK                                            0x10000
#define HWIO_QFPROM_CORR_RD_PERM_LSB_QC_SPARE_REG16_SHFT                                               0x10
#define HWIO_QFPROM_CORR_RD_PERM_LSB_CM_FEAT_CONFIG_BMSK                                             0x8000
#define HWIO_QFPROM_CORR_RD_PERM_LSB_CM_FEAT_CONFIG_SHFT                                                0xf
#define HWIO_QFPROM_CORR_RD_PERM_LSB_MEM_CONFIG_BMSK                                                 0x4000
#define HWIO_QFPROM_CORR_RD_PERM_LSB_MEM_CONFIG_SHFT                                                    0xe
#define HWIO_QFPROM_CORR_RD_PERM_LSB_CALIB_BMSK                                                      0x2000
#define HWIO_QFPROM_CORR_RD_PERM_LSB_CALIB_SHFT                                                         0xd
#define HWIO_QFPROM_CORR_RD_PERM_LSB_PK_HASH0_BMSK                                                   0x1000
#define HWIO_QFPROM_CORR_RD_PERM_LSB_PK_HASH0_SHFT                                                      0xc
#define HWIO_QFPROM_CORR_RD_PERM_LSB_FEAT_CONFIG_BMSK                                                 0x800
#define HWIO_QFPROM_CORR_RD_PERM_LSB_FEAT_CONFIG_SHFT                                                   0xb
#define HWIO_QFPROM_CORR_RD_PERM_LSB_OEM_CONFIG_BMSK                                                  0x400
#define HWIO_QFPROM_CORR_RD_PERM_LSB_OEM_CONFIG_SHFT                                                    0xa
#define HWIO_QFPROM_CORR_RD_PERM_LSB_ANTI_ROLLBACK_4_BMSK                                             0x200
#define HWIO_QFPROM_CORR_RD_PERM_LSB_ANTI_ROLLBACK_4_SHFT                                               0x9
#define HWIO_QFPROM_CORR_RD_PERM_LSB_ANTI_ROLLBACK_3_BMSK                                             0x100
#define HWIO_QFPROM_CORR_RD_PERM_LSB_ANTI_ROLLBACK_3_SHFT                                               0x8
#define HWIO_QFPROM_CORR_RD_PERM_LSB_ANTI_ROLLBACK_2_BMSK                                              0x80
#define HWIO_QFPROM_CORR_RD_PERM_LSB_ANTI_ROLLBACK_2_SHFT                                               0x7
#define HWIO_QFPROM_CORR_RD_PERM_LSB_ANTI_ROLLBACK_1_BMSK                                              0x40
#define HWIO_QFPROM_CORR_RD_PERM_LSB_ANTI_ROLLBACK_1_SHFT                                               0x6
#define HWIO_QFPROM_CORR_RD_PERM_LSB_FEC_EN_BMSK                                                       0x20
#define HWIO_QFPROM_CORR_RD_PERM_LSB_FEC_EN_SHFT                                                        0x5
#define HWIO_QFPROM_CORR_RD_PERM_LSB_WR_PERM_BMSK                                                      0x10
#define HWIO_QFPROM_CORR_RD_PERM_LSB_WR_PERM_SHFT                                                       0x4
#define HWIO_QFPROM_CORR_RD_PERM_LSB_RD_PERM_BMSK                                                       0x8
#define HWIO_QFPROM_CORR_RD_PERM_LSB_RD_PERM_SHFT                                                       0x3
#define HWIO_QFPROM_CORR_RD_PERM_LSB_PTE_BMSK                                                           0x4
#define HWIO_QFPROM_CORR_RD_PERM_LSB_PTE_SHFT                                                           0x2
#define HWIO_QFPROM_CORR_RD_PERM_LSB_QC_SPARE_REGION_BMSK                                               0x2
#define HWIO_QFPROM_CORR_RD_PERM_LSB_QC_SPARE_REGION_SHFT                                               0x1
#define HWIO_QFPROM_CORR_RD_PERM_LSB_CRI_CM_PRIVATE_BMSK                                                0x1
#define HWIO_QFPROM_CORR_RD_PERM_LSB_CRI_CM_PRIVATE_SHFT                                                0x0

#define HWIO_QFPROM_CORR_RD_PERM_MSB_ADDR                                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004154)
#define HWIO_QFPROM_CORR_RD_PERM_MSB_OFFS                                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004154)
#define HWIO_QFPROM_CORR_RD_PERM_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_RD_PERM_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_RD_PERM_MSB_ADDR, HWIO_QFPROM_CORR_RD_PERM_MSB_RMSK)
#define HWIO_QFPROM_CORR_RD_PERM_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_RD_PERM_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_RD_PERM_MSB_RSVD0_BMSK                                                  0xffffffff
#define HWIO_QFPROM_CORR_RD_PERM_MSB_RSVD0_SHFT                                                         0x0

#define HWIO_QFPROM_CORR_WR_PERM_LSB_ADDR                                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004158)
#define HWIO_QFPROM_CORR_WR_PERM_LSB_OFFS                                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004158)
#define HWIO_QFPROM_CORR_WR_PERM_LSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_WR_PERM_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_WR_PERM_LSB_ADDR, HWIO_QFPROM_CORR_WR_PERM_LSB_RMSK)
#define HWIO_QFPROM_CORR_WR_PERM_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_WR_PERM_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_WR_PERM_LSB_RSVD0_BMSK                                                  0x80000000
#define HWIO_QFPROM_CORR_WR_PERM_LSB_RSVD0_SHFT                                                        0x1f
#define HWIO_QFPROM_CORR_WR_PERM_LSB_OEM_SPARE_REG30_BMSK                                        0x40000000
#define HWIO_QFPROM_CORR_WR_PERM_LSB_OEM_SPARE_REG30_SHFT                                              0x1e
#define HWIO_QFPROM_CORR_WR_PERM_LSB_OEM_SPARE_REG29_BMSK                                        0x20000000
#define HWIO_QFPROM_CORR_WR_PERM_LSB_OEM_SPARE_REG29_SHFT                                              0x1d
#define HWIO_QFPROM_CORR_WR_PERM_LSB_OEM_SPARE_REG28_BMSK                                        0x10000000
#define HWIO_QFPROM_CORR_WR_PERM_LSB_OEM_SPARE_REG28_SHFT                                              0x1c
#define HWIO_QFPROM_CORR_WR_PERM_LSB_OEM_SPARE_REG27_BMSK                                         0x8000000
#define HWIO_QFPROM_CORR_WR_PERM_LSB_OEM_SPARE_REG27_SHFT                                              0x1b
#define HWIO_QFPROM_CORR_WR_PERM_LSB_OEM_SPARE_REG26_BMSK                                         0x4000000
#define HWIO_QFPROM_CORR_WR_PERM_LSB_OEM_SPARE_REG26_SHFT                                              0x1a
#define HWIO_QFPROM_CORR_WR_PERM_LSB_PK_HASH1_BMSK                                                0x2000000
#define HWIO_QFPROM_CORR_WR_PERM_LSB_PK_HASH1_SHFT                                                     0x19
#define HWIO_QFPROM_CORR_WR_PERM_LSB_IMAGE_ENCR_KEY1_BMSK                                         0x1000000
#define HWIO_QFPROM_CORR_WR_PERM_LSB_IMAGE_ENCR_KEY1_SHFT                                              0x18
#define HWIO_QFPROM_CORR_WR_PERM_LSB_BOOT_ROM_PATCH_BMSK                                           0x800000
#define HWIO_QFPROM_CORR_WR_PERM_LSB_BOOT_ROM_PATCH_SHFT                                               0x17
#define HWIO_QFPROM_CORR_WR_PERM_LSB_SEC_KEY_DERIVATION_KEY_BMSK                                   0x400000
#define HWIO_QFPROM_CORR_WR_PERM_LSB_SEC_KEY_DERIVATION_KEY_SHFT                                       0x16
#define HWIO_QFPROM_CORR_WR_PERM_LSB_PRI_KEY_DERIVATION_KEY_BMSK                                   0x200000
#define HWIO_QFPROM_CORR_WR_PERM_LSB_PRI_KEY_DERIVATION_KEY_SHFT                                       0x15
#define HWIO_QFPROM_CORR_WR_PERM_LSB_OEM_SEC_BOOT_BMSK                                             0x100000
#define HWIO_QFPROM_CORR_WR_PERM_LSB_OEM_SEC_BOOT_SHFT                                                 0x14
#define HWIO_QFPROM_CORR_WR_PERM_LSB_OEM_IMAGE_ENCR_KEY_BMSK                                        0x80000
#define HWIO_QFPROM_CORR_WR_PERM_LSB_OEM_IMAGE_ENCR_KEY_SHFT                                           0x13
#define HWIO_QFPROM_CORR_WR_PERM_LSB_QC_SPARE_REG18_BMSK                                            0x40000
#define HWIO_QFPROM_CORR_WR_PERM_LSB_QC_SPARE_REG18_SHFT                                               0x12
#define HWIO_QFPROM_CORR_WR_PERM_LSB_QC_SPARE_REG17_BMSK                                            0x20000
#define HWIO_QFPROM_CORR_WR_PERM_LSB_QC_SPARE_REG17_SHFT                                               0x11
#define HWIO_QFPROM_CORR_WR_PERM_LSB_QC_SPARE_REG16_BMSK                                            0x10000
#define HWIO_QFPROM_CORR_WR_PERM_LSB_QC_SPARE_REG16_SHFT                                               0x10
#define HWIO_QFPROM_CORR_WR_PERM_LSB_CM_FEAT_CONFIG_BMSK                                             0x8000
#define HWIO_QFPROM_CORR_WR_PERM_LSB_CM_FEAT_CONFIG_SHFT                                                0xf
#define HWIO_QFPROM_CORR_WR_PERM_LSB_MEM_CONFIG_BMSK                                                 0x4000
#define HWIO_QFPROM_CORR_WR_PERM_LSB_MEM_CONFIG_SHFT                                                    0xe
#define HWIO_QFPROM_CORR_WR_PERM_LSB_CALIB_BMSK                                                      0x2000
#define HWIO_QFPROM_CORR_WR_PERM_LSB_CALIB_SHFT                                                         0xd
#define HWIO_QFPROM_CORR_WR_PERM_LSB_PK_HASH0_BMSK                                                   0x1000
#define HWIO_QFPROM_CORR_WR_PERM_LSB_PK_HASH0_SHFT                                                      0xc
#define HWIO_QFPROM_CORR_WR_PERM_LSB_FEAT_CONFIG_BMSK                                                 0x800
#define HWIO_QFPROM_CORR_WR_PERM_LSB_FEAT_CONFIG_SHFT                                                   0xb
#define HWIO_QFPROM_CORR_WR_PERM_LSB_OEM_CONFIG_BMSK                                                  0x400
#define HWIO_QFPROM_CORR_WR_PERM_LSB_OEM_CONFIG_SHFT                                                    0xa
#define HWIO_QFPROM_CORR_WR_PERM_LSB_ANTI_ROLLBACK_4_BMSK                                             0x200
#define HWIO_QFPROM_CORR_WR_PERM_LSB_ANTI_ROLLBACK_4_SHFT                                               0x9
#define HWIO_QFPROM_CORR_WR_PERM_LSB_ANTI_ROLLBACK_3_BMSK                                             0x100
#define HWIO_QFPROM_CORR_WR_PERM_LSB_ANTI_ROLLBACK_3_SHFT                                               0x8
#define HWIO_QFPROM_CORR_WR_PERM_LSB_ANTI_ROLLBACK_2_BMSK                                              0x80
#define HWIO_QFPROM_CORR_WR_PERM_LSB_ANTI_ROLLBACK_2_SHFT                                               0x7
#define HWIO_QFPROM_CORR_WR_PERM_LSB_ANTI_ROLLBACK_1_BMSK                                              0x40
#define HWIO_QFPROM_CORR_WR_PERM_LSB_ANTI_ROLLBACK_1_SHFT                                               0x6
#define HWIO_QFPROM_CORR_WR_PERM_LSB_FEC_EN_BMSK                                                       0x20
#define HWIO_QFPROM_CORR_WR_PERM_LSB_FEC_EN_SHFT                                                        0x5
#define HWIO_QFPROM_CORR_WR_PERM_LSB_WR_PERM_BMSK                                                      0x10
#define HWIO_QFPROM_CORR_WR_PERM_LSB_WR_PERM_SHFT                                                       0x4
#define HWIO_QFPROM_CORR_WR_PERM_LSB_RD_PERM_BMSK                                                       0x8
#define HWIO_QFPROM_CORR_WR_PERM_LSB_RD_PERM_SHFT                                                       0x3
#define HWIO_QFPROM_CORR_WR_PERM_LSB_PTE_BMSK                                                           0x4
#define HWIO_QFPROM_CORR_WR_PERM_LSB_PTE_SHFT                                                           0x2
#define HWIO_QFPROM_CORR_WR_PERM_LSB_QC_SPARE_REGION_BMSK                                               0x2
#define HWIO_QFPROM_CORR_WR_PERM_LSB_QC_SPARE_REGION_SHFT                                               0x1
#define HWIO_QFPROM_CORR_WR_PERM_LSB_CRI_CM_PRIVATE_BMSK                                                0x1
#define HWIO_QFPROM_CORR_WR_PERM_LSB_CRI_CM_PRIVATE_SHFT                                                0x0

#define HWIO_QFPROM_CORR_WR_PERM_MSB_ADDR                                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000415c)
#define HWIO_QFPROM_CORR_WR_PERM_MSB_OFFS                                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000415c)
#define HWIO_QFPROM_CORR_WR_PERM_MSB_RMSK                                                        0xffffffff
#define HWIO_QFPROM_CORR_WR_PERM_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_WR_PERM_MSB_ADDR, HWIO_QFPROM_CORR_WR_PERM_MSB_RMSK)
#define HWIO_QFPROM_CORR_WR_PERM_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_WR_PERM_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_WR_PERM_MSB_RSVD0_BMSK                                                  0xffffffff
#define HWIO_QFPROM_CORR_WR_PERM_MSB_RSVD0_SHFT                                                         0x0

#define HWIO_QFPROM_CORR_FEC_EN_LSB_ADDR                                                         (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004160)
#define HWIO_QFPROM_CORR_FEC_EN_LSB_OFFS                                                         (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004160)
#define HWIO_QFPROM_CORR_FEC_EN_LSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_FEC_EN_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_FEC_EN_LSB_ADDR, HWIO_QFPROM_CORR_FEC_EN_LSB_RMSK)
#define HWIO_QFPROM_CORR_FEC_EN_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_FEC_EN_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_FEC_EN_LSB_RSVD0_BMSK                                                   0x80000000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_RSVD0_SHFT                                                         0x1f
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION30_FEC_EN_BMSK                                         0x40000000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION30_FEC_EN_SHFT                                               0x1e
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION29_FEC_EN_BMSK                                         0x20000000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION29_FEC_EN_SHFT                                               0x1d
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION28_FEC_EN_BMSK                                         0x10000000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION28_FEC_EN_SHFT                                               0x1c
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION27_FEC_EN_BMSK                                          0x8000000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION27_FEC_EN_SHFT                                               0x1b
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION26_FEC_EN_BMSK                                          0x4000000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION26_FEC_EN_SHFT                                               0x1a
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION25_FEC_EN_BMSK                                          0x2000000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION25_FEC_EN_SHFT                                               0x19
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION24_FEC_EN_BMSK                                          0x1000000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION24_FEC_EN_SHFT                                               0x18
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION23_FEC_EN_BMSK                                           0x800000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION23_FEC_EN_SHFT                                               0x17
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION22_FEC_EN_BMSK                                           0x400000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION22_FEC_EN_SHFT                                               0x16
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION21_FEC_EN_BMSK                                           0x200000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION21_FEC_EN_SHFT                                               0x15
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION20_FEC_EN_BMSK                                           0x100000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION20_FEC_EN_SHFT                                               0x14
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION19_FEC_EN_BMSK                                            0x80000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION19_FEC_EN_SHFT                                               0x13
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION18_FEC_EN_BMSK                                            0x40000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION18_FEC_EN_SHFT                                               0x12
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION17_FEC_EN_BMSK                                            0x20000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION17_FEC_EN_SHFT                                               0x11
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION16_FEC_EN_BMSK                                            0x10000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION16_FEC_EN_SHFT                                               0x10
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION15_FEC_EN_BMSK                                             0x8000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION15_FEC_EN_SHFT                                                0xf
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION14_FEC_EN_BMSK                                             0x4000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION14_FEC_EN_SHFT                                                0xe
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION13_FEC_EN_BMSK                                             0x2000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION13_FEC_EN_SHFT                                                0xd
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION12_FEC_EN_BMSK                                             0x1000
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION12_FEC_EN_SHFT                                                0xc
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION11_FEC_EN_BMSK                                              0x800
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION11_FEC_EN_SHFT                                                0xb
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION10_FEC_EN_BMSK                                              0x400
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION10_FEC_EN_SHFT                                                0xa
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION9_FEC_EN_BMSK                                               0x200
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION9_FEC_EN_SHFT                                                 0x9
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION8_FEC_EN_BMSK                                               0x100
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION8_FEC_EN_SHFT                                                 0x8
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION7_FEC_EN_BMSK                                                0x80
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION7_FEC_EN_SHFT                                                 0x7
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION6_FEC_EN_BMSK                                                0x40
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION6_FEC_EN_SHFT                                                 0x6
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION5_FEC_EN_BMSK                                                0x20
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION5_FEC_EN_SHFT                                                 0x5
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION4_FEC_EN_BMSK                                                0x10
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION4_FEC_EN_SHFT                                                 0x4
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION3_FEC_EN_BMSK                                                 0x8
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION3_FEC_EN_SHFT                                                 0x3
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION2_FEC_EN_BMSK                                                 0x4
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION2_FEC_EN_SHFT                                                 0x2
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION1_FEC_EN_BMSK                                                 0x2
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION1_FEC_EN_SHFT                                                 0x1
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION0_FEC_EN_BMSK                                                 0x1
#define HWIO_QFPROM_CORR_FEC_EN_LSB_REGION0_FEC_EN_SHFT                                                 0x0

#define HWIO_QFPROM_CORR_FEC_EN_MSB_ADDR                                                         (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004164)
#define HWIO_QFPROM_CORR_FEC_EN_MSB_OFFS                                                         (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004164)
#define HWIO_QFPROM_CORR_FEC_EN_MSB_RMSK                                                         0xffffffff
#define HWIO_QFPROM_CORR_FEC_EN_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_FEC_EN_MSB_ADDR, HWIO_QFPROM_CORR_FEC_EN_MSB_RMSK)
#define HWIO_QFPROM_CORR_FEC_EN_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_FEC_EN_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_FEC_EN_MSB_RSVD0_BMSK                                                   0xffffffff
#define HWIO_QFPROM_CORR_FEC_EN_MSB_RSVD0_SHFT                                                          0x0

#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_1_LSB_ADDR                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004168)
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_1_LSB_OFFS                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004168)
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_1_LSB_RMSK                                                0xffffffff
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_1_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_ANTI_ROLLBACK_1_LSB_ADDR, HWIO_QFPROM_CORR_ANTI_ROLLBACK_1_LSB_RMSK)
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_1_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_ANTI_ROLLBACK_1_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_1_LSB_XBL0_BMSK                                           0xffffffff
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_1_LSB_XBL0_SHFT                                                  0x0

#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_1_MSB_ADDR                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000416c)
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_1_MSB_OFFS                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000416c)
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_1_MSB_RMSK                                                0xffffffff
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_1_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_ANTI_ROLLBACK_1_MSB_ADDR, HWIO_QFPROM_CORR_ANTI_ROLLBACK_1_MSB_RMSK)
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_1_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_ANTI_ROLLBACK_1_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_1_MSB_XBL1_BMSK                                           0xffffffff
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_1_MSB_XBL1_SHFT                                                  0x0

#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_2_LSB_ADDR                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004170)
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_2_LSB_OFFS                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004170)
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_2_LSB_RMSK                                                0xffffffff
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_2_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_ANTI_ROLLBACK_2_LSB_ADDR, HWIO_QFPROM_CORR_ANTI_ROLLBACK_2_LSB_RMSK)
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_2_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_ANTI_ROLLBACK_2_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_2_LSB_PIL_SUBSYSTEM_31_0_BMSK                             0xffffffff
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_2_LSB_PIL_SUBSYSTEM_31_0_SHFT                                    0x0

#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_2_MSB_ADDR                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004174)
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_2_MSB_OFFS                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004174)
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_2_MSB_RMSK                                                0xffffffff
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_2_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_ANTI_ROLLBACK_2_MSB_ADDR, HWIO_QFPROM_CORR_ANTI_ROLLBACK_2_MSB_RMSK)
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_2_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_ANTI_ROLLBACK_2_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_2_MSB_XBL_SEC_BMSK                                        0xfe000000
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_2_MSB_XBL_SEC_SHFT                                              0x19
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_2_MSB_RPM_BMSK                                             0x1fe0000
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_2_MSB_RPM_SHFT                                                  0x11
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_2_MSB_TZ_BMSK                                                0x1ffff
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_2_MSB_TZ_SHFT                                                    0x0

#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_3_LSB_ADDR                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004178)
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_3_LSB_OFFS                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004178)
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_3_LSB_RMSK                                                0xffffffff
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_3_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_ANTI_ROLLBACK_3_LSB_ADDR, HWIO_QFPROM_CORR_ANTI_ROLLBACK_3_LSB_RMSK)
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_3_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_ANTI_ROLLBACK_3_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_3_LSB_RSVD1_BMSK                                          0xc0000000
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_3_LSB_RSVD1_SHFT                                                0x1e
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_3_LSB_TQS_HASH_ACTIVE_BMSK                                0x3e000000
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_3_LSB_TQS_HASH_ACTIVE_SHFT                                      0x19
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_3_LSB_RPMB_KEY_PROVISIONED_BMSK                            0x1000000
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_3_LSB_RPMB_KEY_PROVISIONED_SHFT                                 0x18
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_3_LSB_PIL_SUBSYSTEM_47_32_BMSK                              0xffff00
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_3_LSB_PIL_SUBSYSTEM_47_32_SHFT                                   0x8
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_3_LSB_SAFESWITCH_BMSK                                           0xff
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_3_LSB_SAFESWITCH_SHFT                                            0x0

#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_3_MSB_ADDR                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000417c)
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_3_MSB_OFFS                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000417c)
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_3_MSB_RMSK                                                0xffffffff
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_3_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_ANTI_ROLLBACK_3_MSB_ADDR, HWIO_QFPROM_CORR_ANTI_ROLLBACK_3_MSB_RMSK)
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_3_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_ANTI_ROLLBACK_3_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_3_MSB_RSVD1_BMSK                                          0xf0000000
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_3_MSB_RSVD1_SHFT                                                0x1c
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_3_MSB_DEVICE_CFG_BMSK                                      0xffe0000
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_3_MSB_DEVICE_CFG_SHFT                                           0x11
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_3_MSB_DEBUG_POLICY_BMSK                                      0x1f000
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_3_MSB_DEBUG_POLICY_SHFT                                          0xc
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_3_MSB_HYPERVISOR_BMSK                                          0xfff
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_3_MSB_HYPERVISOR_SHFT                                            0x0

#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_4_LSB_ADDR                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004180)
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_4_LSB_OFFS                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004180)
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_4_LSB_RMSK                                                0xffffffff
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_4_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_ANTI_ROLLBACK_4_LSB_ADDR, HWIO_QFPROM_CORR_ANTI_ROLLBACK_4_LSB_RMSK)
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_4_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_ANTI_ROLLBACK_4_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_4_LSB_MSS_BMSK                                            0xffff0000
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_4_LSB_MSS_SHFT                                                  0x10
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_4_LSB_MBA_BMSK                                                0xffff
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_4_LSB_MBA_SHFT                                                   0x0

#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_4_MSB_ADDR                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004184)
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_4_MSB_OFFS                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004184)
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_4_MSB_RMSK                                                0xffffffff
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_4_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_ANTI_ROLLBACK_4_MSB_ADDR, HWIO_QFPROM_CORR_ANTI_ROLLBACK_4_MSB_RMSK)
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_4_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_ANTI_ROLLBACK_4_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_4_MSB_SIMLOCK_BMSK                                        0x80000000
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_4_MSB_SIMLOCK_SHFT                                              0x1f
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_4_MSB_RSVD0_BMSK                                          0x7fffffff
#define HWIO_QFPROM_CORR_ANTI_ROLLBACK_4_MSB_RSVD0_SHFT                                                 0x0

#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_ADDR                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004188)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_OFFS                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004188)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_RMSK                                                0xffffffff
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_ADDR, HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_RMSK)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_DCC_DEBUG_DISABLE_BMSK                              0x80000000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_DCC_DEBUG_DISABLE_SHFT                                    0x1f
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_APPS_APB_DFD_DISABLE_BMSK                           0x40000000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_APPS_APB_DFD_DISABLE_SHFT                                 0x1e
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_ALL_DEBUG_DISABLE_BMSK                              0x20000000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_ALL_DEBUG_DISABLE_SHFT                                    0x1d
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_DEBUG_POLICY_DISABLE_BMSK                           0x10000000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_DEBUG_POLICY_DISABLE_SHFT                                 0x1c
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_RSVD2_BMSK                                           0xe000000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_RSVD2_SHFT                                                0x19
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_MSS_HASH_INTEGRITY_CHECK_DISABLE_BMSK                0x1000000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_MSS_HASH_INTEGRITY_CHECK_DISABLE_SHFT                     0x18
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_APPS_HASH_INTEGRITY_CHECK_DISABLE_BMSK                0x800000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_APPS_HASH_INTEGRITY_CHECK_DISABLE_SHFT                    0x17
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_USB_SS_DISABLE_BMSK                                   0x400000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_USB_SS_DISABLE_SHFT                                       0x16
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_SW_ROT_USE_SERIAL_NUM_BMSK                            0x200000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_SW_ROT_USE_SERIAL_NUM_SHFT                                0x15
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_DISABLE_ROT_TRANSFER_BMSK                             0x100000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_DISABLE_ROT_TRANSFER_SHFT                                 0x14
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_IMAGE_ENCRYPTION_ENABLE_BMSK                           0x80000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_IMAGE_ENCRYPTION_ENABLE_SHFT                              0x13
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_RSVD1_BMSK                                             0x60000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_RSVD1_SHFT                                                0x11
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_PBL_USB_TYPE_C_DISABLE_BMSK                            0x10000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_PBL_USB_TYPE_C_DISABLE_SHFT                               0x10
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_PBL_LOG_DISABLE_BMSK                                    0x8000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_PBL_LOG_DISABLE_SHFT                                       0xf
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_WDOG_EN_BMSK                                            0x4000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_WDOG_EN_SHFT                                               0xe
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_SPDM_SECURE_MODE_BMSK                                   0x2000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_SPDM_SECURE_MODE_SHFT                                      0xd
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_SW_FUSE_PROG_DISABLE_BMSK                               0x1000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_SW_FUSE_PROG_DISABLE_SHFT                                  0xc
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_RSVD0_BMSK                                               0xc00
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_RSVD0_SHFT                                                 0xa
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_FAST_BOOT_BMSK                                           0x3e0
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_FAST_BOOT_SHFT                                             0x5
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_SDCC_MCLK_BOOT_FREQ_BMSK                                  0x10
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_SDCC_MCLK_BOOT_FREQ_SHFT                                   0x4
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_FORCE_USB_BOOT_DISABLE_BMSK                                0x8
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_FORCE_USB_BOOT_DISABLE_SHFT                                0x3
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_FORCE_DLOAD_DISABLE_BMSK                                   0x4
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_FORCE_DLOAD_DISABLE_SHFT                                   0x2
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_ENUM_TIMEOUT_BMSK                                          0x2
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_ENUM_TIMEOUT_SHFT                                          0x1
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_E_DLOAD_DISABLE_BMSK                                       0x1
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_LSB_E_DLOAD_DISABLE_SHFT                                       0x0

#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_ADDR                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000418c)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_OFFS                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000418c)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_RMSK                                                0xffffffff
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_ADDR, HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_RMSK)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_PIMEM_SPIDEN_DISABLE_BMSK                           0x80000000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_PIMEM_SPIDEN_DISABLE_SHFT                                 0x1f
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_WCSS_SPIDEN_DISABLE_BMSK                            0x40000000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_WCSS_SPIDEN_DISABLE_SHFT                                  0x1e
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_DAP_SPIDEN_DISABLE_BMSK                             0x20000000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_DAP_SPIDEN_DISABLE_SHFT                                   0x1d
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_APPS_SPIDEN_DISABLE_BMSK                            0x10000000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_APPS_SPIDEN_DISABLE_SHFT                                  0x1c
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_LPASS_SPNIDEN_DISABLE_BMSK                           0x8000000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_LPASS_SPNIDEN_DISABLE_SHFT                                0x1b
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_PIMEM_SPNIDEN_DISABLE_BMSK                           0x4000000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_PIMEM_SPNIDEN_DISABLE_SHFT                                0x1a
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_WCSS_SPNIDEN_DISABLE_BMSK                            0x2000000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_WCSS_SPNIDEN_DISABLE_SHFT                                 0x19
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_DAP_SPNIDEN_DISABLE_BMSK                             0x1000000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_DAP_SPNIDEN_DISABLE_SHFT                                  0x18
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_APPS_SPNIDEN_DISABLE_BMSK                             0x800000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_APPS_SPNIDEN_DISABLE_SHFT                                 0x17
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_MSS_NIDEN_DISABLE_BMSK                                0x400000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_MSS_NIDEN_DISABLE_SHFT                                    0x16
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_LPASS_SENSOR_NIDEN_DISABLE_BMSK                       0x200000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_LPASS_SENSOR_NIDEN_DISABLE_SHFT                           0x15
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_PIMEM_NIDEN_DISABLE_BMSK                              0x100000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_PIMEM_NIDEN_DISABLE_SHFT                                  0x14
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_RPM_NIDEN_DISABLE_BMSK                                 0x80000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_RPM_NIDEN_DISABLE_SHFT                                    0x13
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_WCSS_NIDEN_DISABLE_BMSK                                0x40000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_WCSS_NIDEN_DISABLE_SHFT                                   0x12
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_LPASS_NIDEN_DISABLE_BMSK                               0x20000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_LPASS_NIDEN_DISABLE_SHFT                                  0x11
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_DAP_NIDEN_DISABLE_BMSK                                 0x10000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_DAP_NIDEN_DISABLE_SHFT                                    0x10
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_APPS_NIDEN_DISABLE_BMSK                                 0x8000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_APPS_NIDEN_DISABLE_SHFT                                    0xf
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_MSS_DBGEN_DISABLE_BMSK                                  0x4000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_MSS_DBGEN_DISABLE_SHFT                                     0xe
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_A5X_ISDB_DBGEN_DISABLE_BMSK                             0x2000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_A5X_ISDB_DBGEN_DISABLE_SHFT                                0xd
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_VENUS_0_DBGEN_DISABLE_BMSK                              0x1000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_VENUS_0_DBGEN_DISABLE_SHFT                                 0xc
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_RSVD1_BMSK                                               0x800
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_RSVD1_SHFT                                                 0xb
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_LPASS_SENSOR_DBGEN_DISABLE_BMSK                          0x400
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_LPASS_SENSOR_DBGEN_DISABLE_SHFT                            0xa
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_PIMEM_DBGEN_DISABLE_BMSK                                 0x200
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_PIMEM_DBGEN_DISABLE_SHFT                                   0x9
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_RPM_DBGEN_DISABLE_BMSK                                   0x100
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_RPM_DBGEN_DISABLE_SHFT                                     0x8
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_WCSS_DBGEN_DISABLE_BMSK                                   0x80
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_WCSS_DBGEN_DISABLE_SHFT                                    0x7
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_LPASS_Q6_DBGEN_DISABLE_BMSK                               0x40
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_LPASS_Q6_DBGEN_DISABLE_SHFT                                0x6
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_DAP_DBGEN_DISABLE_BMSK                                    0x20
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_DAP_DBGEN_DISABLE_SHFT                                     0x5
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_APPS_DBGEN_DISABLE_BMSK                                   0x10
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_APPS_DBGEN_DISABLE_SHFT                                    0x4
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_DAP_DEVICEEN_DISABLE_BMSK                                  0x8
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_DAP_DEVICEEN_DISABLE_SHFT                                  0x3
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_RPM_DAPEN_DISABLE_BMSK                                     0x4
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_RPM_DAPEN_DISABLE_SHFT                                     0x2
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_RSVD0_BMSK                                                 0x2
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_RSVD0_SHFT                                                 0x1
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_DEBUG_BUS_DISABLE_BMSK                                     0x1
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW0_MSB_DEBUG_BUS_DISABLE_SHFT                                     0x0

#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_ADDR                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004190)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_OFFS                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004190)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_RMSK                                                0xffffffff
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_ADDR, HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_RMSK)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_RSVD1_BMSK                                          0xffff8000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_RSVD1_SHFT                                                 0xf
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_OEM_SPARE_REG30_SECURE_BMSK                             0x4000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_OEM_SPARE_REG30_SECURE_SHFT                                0xe
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_OEM_SPARE_REG29_SECURE_BMSK                             0x2000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_OEM_SPARE_REG29_SECURE_SHFT                                0xd
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_OEM_SPARE_REG28_SECURE_BMSK                             0x1000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_OEM_SPARE_REG28_SECURE_SHFT                                0xc
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_OEM_SPARE_REG27_SECURE_BMSK                              0x800
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_OEM_SPARE_REG27_SECURE_SHFT                                0xb
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_OEM_SPARE_REG26_SECURE_BMSK                              0x400
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_OEM_SPARE_REG26_SECURE_SHFT                                0xa
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_RSVD0_BMSK                                               0x3fe
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_RSVD0_SHFT                                                 0x1
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_LPASS_SPIDEN_DISABLE_BMSK                                  0x1
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_LSB_LPASS_SPIDEN_DISABLE_SHFT                                  0x0

#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_MSB_ADDR                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004194)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_MSB_OFFS                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004194)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_MSB_RMSK                                                0xffffffff
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_MSB_ADDR, HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_MSB_RMSK)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_MSB_OEM_PRODUCT_ID_BMSK                                 0xffff0000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_MSB_OEM_PRODUCT_ID_SHFT                                       0x10
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_MSB_OEM_HW_ID_BMSK                                          0xffff
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW1_MSB_OEM_HW_ID_SHFT                                             0x0

#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW2_LSB_ADDR                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004198)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW2_LSB_OFFS                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004198)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW2_LSB_RMSK                                                0xffffffff
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW2_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_CONFIG_ROW2_LSB_ADDR, HWIO_QFPROM_CORR_OEM_CONFIG_ROW2_LSB_RMSK)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW2_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_CONFIG_ROW2_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW2_LSB_PERIPH_VID_BMSK                                     0xffff0000
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW2_LSB_PERIPH_VID_SHFT                                           0x10
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW2_LSB_PERIPH_PID_BMSK                                         0xffff
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW2_LSB_PERIPH_PID_SHFT                                            0x0

#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW2_MSB_ADDR                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000419c)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW2_MSB_OFFS                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000419c)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW2_MSB_RMSK                                                0xffffffff
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW2_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_CONFIG_ROW2_MSB_ADDR, HWIO_QFPROM_CORR_OEM_CONFIG_ROW2_MSB_RMSK)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW2_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_CONFIG_ROW2_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW2_MSB_RSVD0_BMSK                                          0xffffff00
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW2_MSB_RSVD0_SHFT                                                 0x8
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW2_MSB_ANTI_ROLLBACK_FEATURE_EN_BMSK                             0xff
#define HWIO_QFPROM_CORR_OEM_CONFIG_ROW2_MSB_ANTI_ROLLBACK_FEATURE_EN_SHFT                              0x0

#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_ADDR                                               (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041a0)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_OFFS                                               (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041a0)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_RMSK                                               0xffffffff
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_ADDR, HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_RMSK)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_UFS_SW_CONTROL_DISABLE_BMSK                        0x80000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_UFS_SW_CONTROL_DISABLE_SHFT                              0x1f
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_RSVD2_BMSK                                         0x40000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_RSVD2_SHFT                                               0x1e
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_RSVD1_BMSK                                         0x20000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_RSVD1_SHFT                                               0x1d
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_GFX3D_FREQ_LIMIT_VAL_BMSK                          0x1fe00000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_GFX3D_FREQ_LIMIT_VAL_SHFT                                0x15
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_MDSS_RESOLUTION_LIMIT_BMSK                           0x180000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_MDSS_RESOLUTION_LIMIT_SHFT                               0x13
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_VENUS_HEVC_ENCODE_DISABLE_BMSK                        0x40000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_VENUS_HEVC_ENCODE_DISABLE_SHFT                           0x12
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_VENUS_HEVC_DECODE_DISABLE_BMSK                        0x20000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_VENUS_HEVC_DECODE_DISABLE_SHFT                           0x11
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_VENUS_4K_DISABLE_BMSK                                 0x10000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_VENUS_4K_DISABLE_SHFT                                    0x10
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_VP8_DECODER_DISABLE_BMSK                               0x8000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_VP8_DECODER_DISABLE_SHFT                                  0xf
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_VP8_ENCODER_DISABLE_BMSK                               0x4000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_VP8_ENCODER_DISABLE_SHFT                                  0xe
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_HDMI_DP_DISABLE_BMSK                                   0x2000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_HDMI_DP_DISABLE_SHFT                                      0xd
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_HDCP_DISABLE_BMSK                                      0x1000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_HDCP_DISABLE_SHFT                                         0xc
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_MDP_APICAL_LTC_DISABLE_BMSK                             0x800
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_MDP_APICAL_LTC_DISABLE_SHFT                               0xb
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_HDCP_GLOBAL_KEY_SPLIT2_DISABLE_BMSK                     0x400
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_HDCP_GLOBAL_KEY_SPLIT2_DISABLE_SHFT                       0xa
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_DSI_1_DISABLE_BMSK                                      0x200
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_DSI_1_DISABLE_SHFT                                        0x9
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_USB2_DISABLE_BMSK                                       0x100
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_USB2_DISABLE_SHFT                                         0x8
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_RSVD0_BMSK                                               0x80
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_RSVD0_SHFT                                                0x7
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_CSID_DPCM_14_DISABLE_BMSK                                0x40
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_CSID_DPCM_14_DISABLE_SHFT                                 0x6
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_ISP_1_DISABLE_BMSK                                       0x20
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_ISP_1_DISABLE_SHFT                                        0x5
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_CSID_3_DISABLE_BMSK                                      0x10
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_CSID_3_DISABLE_SHFT                                       0x4
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_CSID_2_DISABLE_BMSK                                       0x8
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_CSID_2_DISABLE_SHFT                                       0x3
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_BOOT_ROM_PATCH_DISABLE_BMSK                               0x7
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_LSB_BOOT_ROM_PATCH_DISABLE_SHFT                               0x0

#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_ADDR                                               (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041a4)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_OFFS                                               (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041a4)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_RMSK                                               0xffffffff
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_ADDR, HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_RMSK)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_ICE_FORCE_HW_KEY1_BMSK                             0x80000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_ICE_FORCE_HW_KEY1_SHFT                                   0x1f
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_ICE_FORCE_HW_KEY0_BMSK                             0x40000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_ICE_FORCE_HW_KEY0_SHFT                                   0x1e
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_ICE_DISABLE_BMSK                                   0x20000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_ICE_DISABLE_SHFT                                         0x1d
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_RSVD2_BMSK                                         0x10000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_RSVD2_SHFT                                               0x1c
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_RSVD1_BMSK                                          0x8000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_RSVD1_SHFT                                               0x1b
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_LPASS_SENSOR_DISABLE_BMSK                           0x4000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_LPASS_SENSOR_DISABLE_SHFT                                0x1a
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_LPASS_ISLAND_MODE_Q6_CLK_DISABLE_BMSK               0x2000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_LPASS_ISLAND_MODE_Q6_CLK_DISABLE_SHFT                    0x19
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_LPASS_SW_ISLAND_MODE_DISABLE_BMSK                   0x1000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_LPASS_SW_ISLAND_MODE_DISABLE_SHFT                        0x18
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_LPASS_EFUSE_TESTBUS_READ_DISABLE_BMSK                0x800000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_LPASS_EFUSE_TESTBUS_READ_DISABLE_SHFT                    0x17
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_APS_RESET_DISABLE_BMSK                               0x400000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_APS_RESET_DISABLE_SHFT                                   0x16
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_HVX_DISABLE_BMSK                                     0x200000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_HVX_DISABLE_SHFT                                         0x15
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_APB2JTAG_DISABLE_BMSK                                0x100000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_APB2JTAG_DISABLE_SHFT                                    0x14
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_RSVD6_BMSK                                            0x80000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_RSVD6_SHFT                                               0x13
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_STACKED_MEMORY_ID_BMSK                                0x7c000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_STACKED_MEMORY_ID_SHFT                                    0xe
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_PRNG_TESTMODE_DISABLE_BMSK                             0x2000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_PRNG_TESTMODE_DISABLE_SHFT                                0xd
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_CDSP_DISABLE_BMSK                                      0x1000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_CDSP_DISABLE_SHFT                                         0xc
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_MOCHA_PART_BMSK                                         0x800
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_MOCHA_PART_SHFT                                           0xb
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_RSVD5_BMSK                                              0x400
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_RSVD5_SHFT                                                0xa
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_RSVD4_BMSK                                              0x200
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_RSVD4_SHFT                                                0x9
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_RSVD3_BMSK                                              0x1e0
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_RSVD3_SHFT                                                0x5
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_CM_FEAT_CONFIG_DISABLE_BMSK                              0x10
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_CM_FEAT_CONFIG_DISABLE_SHFT                               0x4
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_VFE_RESOLUTION_LIMIT_BMSK                                 0x8
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_VFE_RESOLUTION_LIMIT_SHFT                                 0x3
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_GLD_PDX_FIFO_NIU_BMSK                                     0x4
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_GLD_PDX_FIFO_NIU_SHFT                                     0x2
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_RSVD0_BMSK                                                0x2
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_RSVD0_SHFT                                                0x1
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_VP9_DECODER_DISABLE_BMSK                                  0x1
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW0_MSB_VP9_DECODER_DISABLE_SHFT                                  0x0

#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_ADDR                                               (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041a8)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_OFFS                                               (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041a8)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_RMSK                                               0xffffffff
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_ADDR, HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_RMSK)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_MDSP_FW_DISABLE_BMSK                               0xfff00000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_MDSP_FW_DISABLE_SHFT                                     0x14
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_RSVD0_BMSK                                            0x80000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_RSVD0_SHFT                                               0x13
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_NAV_DISABLE_BMSK                                      0x40000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_NAV_DISABLE_SHFT                                         0x12
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_SYS_APCCCFGNMFI_BMSK                                  0x20000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_SYS_APCCCFGNMFI_SHFT                                     0x11
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_GLD_PDX_FIFO_ACE1_BMSK                                0x10000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_GLD_PDX_FIFO_ACE1_SHFT                                   0x10
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_GLD_PDX_FIFO_ACE0_BMSK                                 0x8000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_GLD_PDX_FIFO_ACE0_SHFT                                    0xf
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_MODEM_FEATURE_DISABLE_SPARE_BMSK                       0x7fe0
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_MODEM_FEATURE_DISABLE_SPARE_SHFT                          0x5
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_MODEM_FEATURE_DISABLE_SLICE_BMSK                         0x1f
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_LSB_MODEM_FEATURE_DISABLE_SLICE_SHFT                          0x0

#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_MSB_ADDR                                               (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041ac)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_MSB_OFFS                                               (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041ac)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_MSB_RMSK                                               0xffffffff
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_MSB_ADDR, HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_MSB_RMSK)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_MSB_SYS_APCX_SYSBARDISABLE_BMSK                        0x80000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_MSB_SYS_APCX_SYSBARDISABLE_SHFT                              0x1f
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_MSB_SYS_APCSCFGAPMBOOTONMX_BMSK                        0x60000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_MSB_SYS_APCSCFGAPMBOOTONMX_SHFT                              0x1d
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_MSB_SYS_APCCCFGCPUPRESENT_N_BMSK                       0x1fe00000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_MSB_SYS_APCCCFGCPUPRESENT_N_SHFT                             0x15
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_MSB_APPS_ACG_DISABLE_BMSK                                0x100000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_MSB_APPS_ACG_DISABLE_SHFT                                    0x14
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_MSB_RSVD1_BMSK                                            0xf0000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_MSB_RSVD1_SHFT                                               0x10
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_MSB_MODEM_VU_DISABLE_BMSK                                  0xffff
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW1_MSB_MODEM_VU_DISABLE_SHFT                                     0x0

#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_ADDR                                               (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041b0)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_OFFS                                               (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041b0)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_RMSK                                               0xffffffff
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_ADDR, HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_RMSK)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_APPS_SPNIDEN_DISABLE_BMSK                       0x80000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_APPS_SPNIDEN_DISABLE_SHFT                             0x1f
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_MSS_NIDEN_DISABLE_BMSK                          0x40000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_MSS_NIDEN_DISABLE_SHFT                                0x1e
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_LPASS_SENSOR_NIDEN_DISABLE_BMSK                 0x20000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_LPASS_SENSOR_NIDEN_DISABLE_SHFT                       0x1d
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_PIMEM_NIDEN_DISABLE_BMSK                        0x10000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_PIMEM_NIDEN_DISABLE_SHFT                              0x1c
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_RPM_NIDEN_DISABLE_BMSK                           0x8000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_RPM_NIDEN_DISABLE_SHFT                                0x1b
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_WCSS_NIDEN_DISABLE_BMSK                          0x4000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_WCSS_NIDEN_DISABLE_SHFT                               0x1a
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_LPASS_NIDEN_DISABLE_BMSK                         0x2000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_LPASS_NIDEN_DISABLE_SHFT                              0x19
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_DAP_NIDEN_DISABLE_BMSK                           0x1000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_DAP_NIDEN_DISABLE_SHFT                                0x18
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_APPS_NIDEN_DISABLE_BMSK                           0x800000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_APPS_NIDEN_DISABLE_SHFT                               0x17
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_MSS_DBGEN_DISABLE_BMSK                            0x400000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_MSS_DBGEN_DISABLE_SHFT                                0x16
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_A5X_ISDB_DBGEN_DISABLE_BMSK                       0x200000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_A5X_ISDB_DBGEN_DISABLE_SHFT                           0x15
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_VENUS_0_DBGEN_DISABLE_BMSK                        0x100000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_VENUS_0_DBGEN_DISABLE_SHFT                            0x14
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_TURING_EFUSE_TESTBUS_READ_DISABLE_BMSK                0x80000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_TURING_EFUSE_TESTBUS_READ_DISABLE_SHFT                   0x13
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_LPASS_SENSOR_DBGEN_DISABLE_BMSK                    0x40000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_LPASS_SENSOR_DBGEN_DISABLE_SHFT                       0x12
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_PIMEM_DBGEN_DISABLE_BMSK                           0x20000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_PIMEM_DBGEN_DISABLE_SHFT                              0x11
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_RPM_DBGEN_DISABLE_BMSK                             0x10000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_RPM_DBGEN_DISABLE_SHFT                                0x10
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_WCSS_DBGEN_DISABLE_BMSK                             0x8000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_WCSS_DBGEN_DISABLE_SHFT                                0xf
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_LPASS_Q6_DBGEN_DISABLE_BMSK                         0x4000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_LPASS_Q6_DBGEN_DISABLE_SHFT                            0xe
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_DAP_DBGEN_DISABLE_BMSK                              0x2000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_DAP_DBGEN_DISABLE_SHFT                                 0xd
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_APPS_DBGEN_DISABLE_BMSK                             0x1000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_APPS_DBGEN_DISABLE_SHFT                                0xc
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_DAP_DEVICEEN_DISABLE_BMSK                            0x800
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_DAP_DEVICEEN_DISABLE_SHFT                              0xb
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_RPM_DAPEN_DISABLE_BMSK                               0x400
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_RPM_DAPEN_DISABLE_SHFT                                 0xa
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_DSI_0_DISABLE_BMSK                                      0x200
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_DSI_0_DISABLE_SHFT                                        0x9
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_DEBUG_BUS_DISABLE_BMSK                               0x100
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_DEBUG_BUS_DISABLE_SHFT                                 0x8
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_DCC_DEBUG_DISABLE_BMSK                                0x80
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_DCC_DEBUG_DISABLE_SHFT                                 0x7
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_APPS_APB_DFD_DISABLE_BMSK                             0x40
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_APPS_APB_DFD_DISABLE_SHFT                              0x6
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_GPMU_NIDEN_DISABLE_BMSK                               0x20
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_GPMU_NIDEN_DISABLE_SHFT                                0x5
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_GPMU_DBGEN_DISABLE_BMSK                               0x10
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_GPMU_DBGEN_DISABLE_SHFT                                0x4
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_GPMU_DAPEN_DISABLE_BMSK                                0x8
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QC_GPMU_DAPEN_DISABLE_SHFT                                0x3
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QDI_SPMI_DISABLE_BMSK                                     0x4
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_QDI_SPMI_DISABLE_SHFT                                     0x2
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_SM_BIST_DISABLE_BMSK                                      0x2
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_SM_BIST_DISABLE_SHFT                                      0x1
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_TIC_DISABLE_BMSK                                          0x1
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_LSB_TIC_DISABLE_SHFT                                          0x0

#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_ADDR                                               (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041b4)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_OFFS                                               (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041b4)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_RMSK                                               0xffffffff
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_ADDR, HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_RMSK)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_SYS_APCCCFGEND_BMSK                                0x80000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_SYS_APCCCFGEND_SHFT                                      0x1f
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_SYS_APCCCP15SDISABLE_BMSK                          0x40000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_SYS_APCCCP15SDISABLE_SHFT                                0x1e
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_SYS_APCCCFGTE_BMSK                                 0x20000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_SYS_APCCCFGTE_SHFT                                       0x1d
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_SILVER_PLL_MAX_FREQ_LVAL_BMSK                      0x1fe00000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_SILVER_PLL_MAX_FREQ_LVAL_SHFT                            0x15
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_APPS_BOOT_FSM_FUSE_BMSK                              0x1c0000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_APPS_BOOT_FSM_FUSE_SHFT                                  0x12
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_GOLD_PLL_MAX_FREQ_LVAL_BMSK                           0x3fc00
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_GOLD_PLL_MAX_FREQ_LVAL_SHFT                               0xa
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_QC_A5X_ISDB_SECURE_DBGEN_DISABLE_BMSK                   0x200
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_QC_A5X_ISDB_SECURE_DBGEN_DISABLE_SHFT                     0x9
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_QC_LPASS_SPIDEN_DISABLE_BMSK                            0x100
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_QC_LPASS_SPIDEN_DISABLE_SHFT                              0x8
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_QC_PIMEM_SPIDEN_DISABLE_BMSK                             0x80
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_QC_PIMEM_SPIDEN_DISABLE_SHFT                              0x7
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_QC_WCSS_SPIDEN_DISABLE_BMSK                              0x40
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_QC_WCSS_SPIDEN_DISABLE_SHFT                               0x6
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_QC_DAP_SPIDEN_DISABLE_BMSK                               0x20
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_QC_DAP_SPIDEN_DISABLE_SHFT                                0x5
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_QC_APPS_SPIDEN_DISABLE_BMSK                              0x10
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_QC_APPS_SPIDEN_DISABLE_SHFT                               0x4
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_QC_LPASS_SPNIDEN_DISABLE_BMSK                             0x8
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_QC_LPASS_SPNIDEN_DISABLE_SHFT                             0x3
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_QC_PIMEM_SPNIDEN_DISABLE_BMSK                             0x4
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_QC_PIMEM_SPNIDEN_DISABLE_SHFT                             0x2
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_QC_WCSS_SPNIDEN_DISABLE_BMSK                              0x2
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_QC_WCSS_SPNIDEN_DISABLE_SHFT                              0x1
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_QC_DAP_SPNIDEN_DISABLE_BMSK                               0x1
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW2_MSB_QC_DAP_SPNIDEN_DISABLE_SHFT                               0x0

#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_LSB_ADDR                                               (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041b8)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_LSB_OFFS                                               (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041b8)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_LSB_RMSK                                               0xffffffff
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_LSB_ADDR, HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_LSB_RMSK)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_LSB_TAP_GEN_SPARE_INSTR_DISABLE_13_0_BMSK              0xfffc0000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_LSB_TAP_GEN_SPARE_INSTR_DISABLE_13_0_SHFT                    0x12
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_LSB_TAP_INSTR_DISABLE_BMSK                                0x3ffff
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_LSB_TAP_INSTR_DISABLE_SHFT                                    0x0

#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_ADDR                                               (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041bc)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_OFFS                                               (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041bc)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_RMSK                                               0xffffffff
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_ADDR, HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_RMSK)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_SEC_TAP_ACCESS_DISABLE_BMSK                        0xfffc0000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_SEC_TAP_ACCESS_DISABLE_SHFT                              0x12
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_TAP_GEN_SPARE_INSTR_DISABLE_31_14_BMSK                0x3ffff
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW3_MSB_TAP_GEN_SPARE_INSTR_DISABLE_31_14_SHFT                    0x0

#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_LSB_ADDR                                               (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041c0)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_LSB_OFFS                                               (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041c0)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_LSB_RMSK                                               0xffffffff
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_LSB_ADDR, HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_LSB_RMSK)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_LSB_MODEM_PBL_PATCH_VERSION_BMSK                       0xfe000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_LSB_MODEM_PBL_PATCH_VERSION_SHFT                             0x19
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_LSB_APPS_PBL_PATCH_VERSION_BMSK                         0x1fc0000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_LSB_APPS_PBL_PATCH_VERSION_SHFT                              0x12
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_LSB_APPS_PBL_BOOT_SPEED_BMSK                              0x30000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_LSB_APPS_PBL_BOOT_SPEED_SHFT                                 0x10
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_LSB_MODEM_PBL_BOOT_BMSK                                    0x8000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_LSB_MODEM_PBL_BOOT_SHFT                                       0xf
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_LSB_RSVD1_BMSK                                             0x4000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_LSB_RSVD1_SHFT                                                0xe
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_LSB_APPS_BOOT_FROM_ROM_BMSK                                0x2000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_LSB_APPS_BOOT_FROM_ROM_SHFT                                   0xd
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_LSB_RSVD0_BMSK                                             0x1000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_LSB_RSVD0_SHFT                                                0xc
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_LSB_MODEM_BOOT_FROM_ROM_BMSK                                0x800
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_LSB_MODEM_BOOT_FROM_ROM_SHFT                                  0xb
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_LSB_MSA_ENA_BMSK                                            0x400
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_LSB_MSA_ENA_SHFT                                              0xa
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_LSB_FORCE_MSA_AUTH_EN_BMSK                                  0x200
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_LSB_FORCE_MSA_AUTH_EN_SHFT                                    0x9
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_LSB_ARM_CE_DISABLE_USAGE_BMSK                               0x100
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_LSB_ARM_CE_DISABLE_USAGE_SHFT                                 0x8
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_LSB_BOOT_ROM_CFG_BMSK                                        0xff
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_LSB_BOOT_ROM_CFG_SHFT                                         0x0

#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_MSB_ADDR                                               (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041c4)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_MSB_OFFS                                               (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041c4)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_MSB_RMSK                                               0xffffffff
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_MSB_ADDR, HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_MSB_RMSK)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_MSB_APPS_BOOT_TRIGGER_DISABLE_BMSK                     0x80000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_MSB_APPS_BOOT_TRIGGER_DISABLE_SHFT                           0x1f
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_MSB_PBL_QSEE_BOOT_FLOW_DISABLE_BMSK                    0x40000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_MSB_PBL_QSEE_BOOT_FLOW_DISABLE_SHFT                          0x1e
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_MSB_XBL_SEC_AUTH_DISABLE_BMSK                          0x20000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_MSB_XBL_SEC_AUTH_DISABLE_SHFT                                0x1d
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_MSB_MSM_PKG_TYPE_BMSK                                  0x10000000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_MSB_MSM_PKG_TYPE_SHFT                                        0x1c
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_MSB_RSVD3_BMSK                                          0xffc0000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_MSB_RSVD3_SHFT                                               0x12
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_MSB_FOUNDRY_ID_BMSK                                       0x3c000
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_MSB_FOUNDRY_ID_SHFT                                           0xe
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_MSB_PLL_CFG_BMSK                                           0x3ff0
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_MSB_PLL_CFG_SHFT                                              0x4
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_MSB_APPS_PBL_PLL_CTRL_BMSK                                    0xf
#define HWIO_QFPROM_CORR_FEAT_CONFIG_ROW4_MSB_APPS_PBL_PLL_CTRL_SHFT                                    0x0

#define HWIO_QFPROM_CORR_PK_HASH0_ROWn_LSB_ADDR(n)                                               (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041c8 + 0x8 * (n))
#define HWIO_QFPROM_CORR_PK_HASH0_ROWn_LSB_OFFS(n)                                               (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041c8 + 0x8 * (n))
#define HWIO_QFPROM_CORR_PK_HASH0_ROWn_LSB_RMSK                                                  0xffffffff
#define HWIO_QFPROM_CORR_PK_HASH0_ROWn_LSB_MAXn                                                           3
#define HWIO_QFPROM_CORR_PK_HASH0_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_PK_HASH0_ROWn_LSB_ADDR(n), HWIO_QFPROM_CORR_PK_HASH0_ROWn_LSB_RMSK)
#define HWIO_QFPROM_CORR_PK_HASH0_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_PK_HASH0_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_PK_HASH0_ROWn_LSB_HASH_DATA0_BMSK                                       0xffffffff
#define HWIO_QFPROM_CORR_PK_HASH0_ROWn_LSB_HASH_DATA0_SHFT                                              0x0

#define HWIO_QFPROM_CORR_PK_HASH0_ROWn_MSB_ADDR(n)                                               (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041cc + 0x8 * (n))
#define HWIO_QFPROM_CORR_PK_HASH0_ROWn_MSB_OFFS(n)                                               (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041cc + 0x8 * (n))
#define HWIO_QFPROM_CORR_PK_HASH0_ROWn_MSB_RMSK                                                  0xffffffff
#define HWIO_QFPROM_CORR_PK_HASH0_ROWn_MSB_MAXn                                                           3
#define HWIO_QFPROM_CORR_PK_HASH0_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_PK_HASH0_ROWn_MSB_ADDR(n), HWIO_QFPROM_CORR_PK_HASH0_ROWn_MSB_RMSK)
#define HWIO_QFPROM_CORR_PK_HASH0_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_PK_HASH0_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_PK_HASH0_ROWn_MSB_HASH_DATA1_BMSK                                       0xffffffff
#define HWIO_QFPROM_CORR_PK_HASH0_ROWn_MSB_HASH_DATA1_SHFT                                              0x0

#define HWIO_QFPROM_CORR_CALIB_ROW0_LSB_ADDR                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041e8)
#define HWIO_QFPROM_CORR_CALIB_ROW0_LSB_OFFS                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041e8)
#define HWIO_QFPROM_CORR_CALIB_ROW0_LSB_RMSK                                                     0xffff803e
#define HWIO_QFPROM_CORR_CALIB_ROW0_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW0_LSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW0_LSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW0_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW0_LSB_LMH_CS_FUSES_SLOPE_16_0_BMSK                             0xffff8000
#define HWIO_QFPROM_CORR_CALIB_ROW0_LSB_LMH_CS_FUSES_SLOPE_16_0_SHFT                                    0xf
#define HWIO_QFPROM_CORR_CALIB_ROW0_LSB_MSS_Q6SS0_LDO_VREF_TRIM_BMSK                                   0x3e
#define HWIO_QFPROM_CORR_CALIB_ROW0_LSB_MSS_Q6SS0_LDO_VREF_TRIM_SHFT                                    0x1

#define HWIO_QFPROM_CORR_CALIB_ROW0_MSB_ADDR                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041ec)
#define HWIO_QFPROM_CORR_CALIB_ROW0_MSB_OFFS                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041ec)
#define HWIO_QFPROM_CORR_CALIB_ROW0_MSB_RMSK                                                     0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW0_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW0_MSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW0_MSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW0_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW0_MSB_LMH_CS_FUSES_INTERCEPT_8_0_BMSK                          0xff800000
#define HWIO_QFPROM_CORR_CALIB_ROW0_MSB_LMH_CS_FUSES_INTERCEPT_8_0_SHFT                                0x17
#define HWIO_QFPROM_CORR_CALIB_ROW0_MSB_LMH_CS_FUSES_SLOPE_39_17_BMSK                              0x7fffff
#define HWIO_QFPROM_CORR_CALIB_ROW0_MSB_LMH_CS_FUSES_SLOPE_39_17_SHFT                                   0x0

#define HWIO_QFPROM_CORR_CALIB_ROW1_LSB_ADDR                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041f0)
#define HWIO_QFPROM_CORR_CALIB_ROW1_LSB_OFFS                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041f0)
#define HWIO_QFPROM_CORR_CALIB_ROW1_LSB_RMSK                                                     0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW1_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW1_LSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW1_LSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW1_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW1_LSB_LMH_FUSES_AMP_COMP_0_BMSK                                0x80000000
#define HWIO_QFPROM_CORR_CALIB_ROW1_LSB_LMH_FUSES_AMP_COMP_0_SHFT                                      0x1f
#define HWIO_QFPROM_CORR_CALIB_ROW1_LSB_LMH_CS_FUSES_INTERCEPT_39_9_BMSK                         0x7fffffff
#define HWIO_QFPROM_CORR_CALIB_ROW1_LSB_LMH_CS_FUSES_INTERCEPT_39_9_SHFT                                0x0

#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_ADDR                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041f4)
#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_OFFS                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041f4)
#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_RMSK                                                     0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW1_MSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW1_MSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW1_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_SPARE0_BMSK                                              0x80000000
#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_SPARE0_SHFT                                                    0x1f
#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_REFGEN_WEST_BGV_TRIM_BMSK                                0x7f800000
#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_REFGEN_WEST_BGV_TRIM_SHFT                                      0x17
#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_REFGEN_EAST_BGV_TRIM_BMSK                                  0x7f8000
#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_REFGEN_EAST_BGV_TRIM_SHFT                                       0xf
#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_BANDGAP_TRIM_BMSK                                            0x7f00
#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_BANDGAP_TRIM_SHFT                                               0x8
#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_GPU_LDOVREFTRIM_BMSK                                           0xf8
#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_GPU_LDOVREFTRIM_SHFT                                            0x3
#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_LMH_FUSES_AMP_COMP_3_1_BMSK                                     0x7
#define HWIO_QFPROM_CORR_CALIB_ROW1_MSB_LMH_FUSES_AMP_COMP_3_1_SHFT                                     0x0

#define HWIO_QFPROM_CORR_CALIB_ROW2_LSB_ADDR                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041f8)
#define HWIO_QFPROM_CORR_CALIB_ROW2_LSB_OFFS                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041f8)
#define HWIO_QFPROM_CORR_CALIB_ROW2_LSB_RMSK                                                     0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW2_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW2_LSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW2_LSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW2_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW2_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW2_LSB_GPU_LMH_CS_FUSES_INTERCEPT_HM_1_0_BMSK                   0xc0000000
#define HWIO_QFPROM_CORR_CALIB_ROW2_LSB_GPU_LMH_CS_FUSES_INTERCEPT_HM_1_0_SHFT                         0x1e
#define HWIO_QFPROM_CORR_CALIB_ROW2_LSB_GPU_LMH_CS_FUSES_SLOPE_SPTP_BMSK                         0x3ff00000
#define HWIO_QFPROM_CORR_CALIB_ROW2_LSB_GPU_LMH_CS_FUSES_SLOPE_SPTP_SHFT                               0x14
#define HWIO_QFPROM_CORR_CALIB_ROW2_LSB_GPU_LMH_CS_FUSES_SLOPE_RAC_BMSK                             0xffc00
#define HWIO_QFPROM_CORR_CALIB_ROW2_LSB_GPU_LMH_CS_FUSES_SLOPE_RAC_SHFT                                 0xa
#define HWIO_QFPROM_CORR_CALIB_ROW2_LSB_GPU_LMH_CS_FUSES_SLOPE_HM_BMSK                                0x3ff
#define HWIO_QFPROM_CORR_CALIB_ROW2_LSB_GPU_LMH_CS_FUSES_SLOPE_HM_SHFT                                  0x0

#define HWIO_QFPROM_CORR_CALIB_ROW2_MSB_ADDR                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x000041fc)
#define HWIO_QFPROM_CORR_CALIB_ROW2_MSB_OFFS                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000041fc)
#define HWIO_QFPROM_CORR_CALIB_ROW2_MSB_RMSK                                                     0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW2_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW2_MSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW2_MSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW2_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW2_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW2_MSB_GPU_LMH_CS_FUSES_AMP_COMP_BMSK                           0xf0000000
#define HWIO_QFPROM_CORR_CALIB_ROW2_MSB_GPU_LMH_CS_FUSES_AMP_COMP_SHFT                                 0x1c
#define HWIO_QFPROM_CORR_CALIB_ROW2_MSB_GPU_LMH_CS_FUSES_INTERCEPT_SPTP_BMSK                      0xffc0000
#define HWIO_QFPROM_CORR_CALIB_ROW2_MSB_GPU_LMH_CS_FUSES_INTERCEPT_SPTP_SHFT                           0x12
#define HWIO_QFPROM_CORR_CALIB_ROW2_MSB_GPU_LMH_CS_FUSES_INTERCEPT_RAC_BMSK                         0x3ff00
#define HWIO_QFPROM_CORR_CALIB_ROW2_MSB_GPU_LMH_CS_FUSES_INTERCEPT_RAC_SHFT                             0x8
#define HWIO_QFPROM_CORR_CALIB_ROW2_MSB_GPU_LMH_CS_FUSES_INTERCEPT_HM_9_2_BMSK                         0xff
#define HWIO_QFPROM_CORR_CALIB_ROW2_MSB_GPU_LMH_CS_FUSES_INTERCEPT_HM_9_2_SHFT                          0x0

#define HWIO_QFPROM_CORR_CALIB_ROW3_LSB_ADDR                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004200)
#define HWIO_QFPROM_CORR_CALIB_ROW3_LSB_OFFS                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004200)
#define HWIO_QFPROM_CORR_CALIB_ROW3_LSB_RMSK                                                     0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW3_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW3_LSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW3_LSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW3_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW3_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW3_LSB_CPR0_TARG_VOLT_OFFSET_NOM_BMSK                           0xf0000000
#define HWIO_QFPROM_CORR_CALIB_ROW3_LSB_CPR0_TARG_VOLT_OFFSET_NOM_SHFT                                 0x1c
#define HWIO_QFPROM_CORR_CALIB_ROW3_LSB_CPR0_TARG_VOLT_OFFSET_NOMPLUS_BMSK                        0xf000000
#define HWIO_QFPROM_CORR_CALIB_ROW3_LSB_CPR0_TARG_VOLT_OFFSET_NOMPLUS_SHFT                             0x18
#define HWIO_QFPROM_CORR_CALIB_ROW3_LSB_CPR0_TARG_VOLT_OFFSET_TUR_BMSK                             0xf00000
#define HWIO_QFPROM_CORR_CALIB_ROW3_LSB_CPR0_TARG_VOLT_OFFSET_TUR_SHFT                                 0x14
#define HWIO_QFPROM_CORR_CALIB_ROW3_LSB_CPR0_TARG_VOLT_SVS2_BMSK                                    0xf8000
#define HWIO_QFPROM_CORR_CALIB_ROW3_LSB_CPR0_TARG_VOLT_SVS2_SHFT                                        0xf
#define HWIO_QFPROM_CORR_CALIB_ROW3_LSB_CPR0_TARG_VOLT_SVS_BMSK                                      0x7c00
#define HWIO_QFPROM_CORR_CALIB_ROW3_LSB_CPR0_TARG_VOLT_SVS_SHFT                                         0xa
#define HWIO_QFPROM_CORR_CALIB_ROW3_LSB_CPR0_TARG_VOLT_NOM_BMSK                                       0x3e0
#define HWIO_QFPROM_CORR_CALIB_ROW3_LSB_CPR0_TARG_VOLT_NOM_SHFT                                         0x5
#define HWIO_QFPROM_CORR_CALIB_ROW3_LSB_CPR0_TARG_VOLT_TUR_BMSK                                        0x1f
#define HWIO_QFPROM_CORR_CALIB_ROW3_LSB_CPR0_TARG_VOLT_TUR_SHFT                                         0x0

#define HWIO_QFPROM_CORR_CALIB_ROW3_MSB_ADDR                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004204)
#define HWIO_QFPROM_CORR_CALIB_ROW3_MSB_OFFS                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004204)
#define HWIO_QFPROM_CORR_CALIB_ROW3_MSB_RMSK                                                     0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW3_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW3_MSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW3_MSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW3_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW3_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW3_MSB_CPR1_TARG_VOLT_SVS2_BMSK                                 0xf8000000
#define HWIO_QFPROM_CORR_CALIB_ROW3_MSB_CPR1_TARG_VOLT_SVS2_SHFT                                       0x1b
#define HWIO_QFPROM_CORR_CALIB_ROW3_MSB_CPR1_TARG_VOLT_SVS_BMSK                                   0x7c00000
#define HWIO_QFPROM_CORR_CALIB_ROW3_MSB_CPR1_TARG_VOLT_SVS_SHFT                                        0x16
#define HWIO_QFPROM_CORR_CALIB_ROW3_MSB_CPR1_TARG_VOLT_NOM_BMSK                                    0x3e0000
#define HWIO_QFPROM_CORR_CALIB_ROW3_MSB_CPR1_TARG_VOLT_NOM_SHFT                                        0x11
#define HWIO_QFPROM_CORR_CALIB_ROW3_MSB_CPR1_TARG_VOLT_TUR_BMSK                                     0x1f000
#define HWIO_QFPROM_CORR_CALIB_ROW3_MSB_CPR1_TARG_VOLT_TUR_SHFT                                         0xc
#define HWIO_QFPROM_CORR_CALIB_ROW3_MSB_CPR0_AGING_BMSK                                               0xff0
#define HWIO_QFPROM_CORR_CALIB_ROW3_MSB_CPR0_AGING_SHFT                                                 0x4
#define HWIO_QFPROM_CORR_CALIB_ROW3_MSB_CPR0_TARG_VOLT_OFFSET_SVSP_BMSK                                 0xf
#define HWIO_QFPROM_CORR_CALIB_ROW3_MSB_CPR0_TARG_VOLT_OFFSET_SVSP_SHFT                                 0x0

#define HWIO_QFPROM_CORR_CALIB_ROW4_LSB_ADDR                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004208)
#define HWIO_QFPROM_CORR_CALIB_ROW4_LSB_OFFS                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004208)
#define HWIO_QFPROM_CORR_CALIB_ROW4_LSB_RMSK                                                     0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW4_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW4_LSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW4_LSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW4_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW4_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW4_LSB_CPR2_TARG_VOLT_NOM_2_0_BMSK                              0xe0000000
#define HWIO_QFPROM_CORR_CALIB_ROW4_LSB_CPR2_TARG_VOLT_NOM_2_0_SHFT                                    0x1d
#define HWIO_QFPROM_CORR_CALIB_ROW4_LSB_CPR2_TARG_VOLT_NOMPLUS_BMSK                              0x1f000000
#define HWIO_QFPROM_CORR_CALIB_ROW4_LSB_CPR2_TARG_VOLT_NOMPLUS_SHFT                                    0x18
#define HWIO_QFPROM_CORR_CALIB_ROW4_LSB_CPR1_AGING_BMSK                                            0xff0000
#define HWIO_QFPROM_CORR_CALIB_ROW4_LSB_CPR1_AGING_SHFT                                                0x10
#define HWIO_QFPROM_CORR_CALIB_ROW4_LSB_CPR1_TARG_VOLT_OFFSET_SVSPLUS_BMSK                           0xf000
#define HWIO_QFPROM_CORR_CALIB_ROW4_LSB_CPR1_TARG_VOLT_OFFSET_SVSPLUS_SHFT                              0xc
#define HWIO_QFPROM_CORR_CALIB_ROW4_LSB_CPR1_TARG_VOLT_OFFSET_NOM_BMSK                                0xf00
#define HWIO_QFPROM_CORR_CALIB_ROW4_LSB_CPR1_TARG_VOLT_OFFSET_NOM_SHFT                                  0x8
#define HWIO_QFPROM_CORR_CALIB_ROW4_LSB_CPR1_TARG_VOLT_OFFSET_NOMPLUS_BMSK                             0xf0
#define HWIO_QFPROM_CORR_CALIB_ROW4_LSB_CPR1_TARG_VOLT_OFFSET_NOMPLUS_SHFT                              0x4
#define HWIO_QFPROM_CORR_CALIB_ROW4_LSB_CPR1_TARG_VOLT_OFFSET_TUR_BMSK                                  0xf
#define HWIO_QFPROM_CORR_CALIB_ROW4_LSB_CPR1_TARG_VOLT_OFFSET_TUR_SHFT                                  0x0

#define HWIO_QFPROM_CORR_CALIB_ROW4_MSB_ADDR                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000420c)
#define HWIO_QFPROM_CORR_CALIB_ROW4_MSB_OFFS                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000420c)
#define HWIO_QFPROM_CORR_CALIB_ROW4_MSB_RMSK                                                     0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW4_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW4_MSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW4_MSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW4_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW4_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW4_MSB_CPR2_AGING_3_0_BMSK                                      0xf0000000
#define HWIO_QFPROM_CORR_CALIB_ROW4_MSB_CPR2_AGING_3_0_SHFT                                            0x1c
#define HWIO_QFPROM_CORR_CALIB_ROW4_MSB_CPR6_SVSPLUS_ROSEL_BMSK                                   0xf000000
#define HWIO_QFPROM_CORR_CALIB_ROW4_MSB_CPR6_SVSPLUS_ROSEL_SHFT                                        0x18
#define HWIO_QFPROM_CORR_CALIB_ROW4_MSB_CPR2_TARG_VOLT_OFFSET_SVSPLUS_BMSK                         0xf00000
#define HWIO_QFPROM_CORR_CALIB_ROW4_MSB_CPR2_TARG_VOLT_OFFSET_SVSPLUS_SHFT                             0x14
#define HWIO_QFPROM_CORR_CALIB_ROW4_MSB_CPR2_TARG_VOLT_OFFSET_NOM_BMSK                              0xf0000
#define HWIO_QFPROM_CORR_CALIB_ROW4_MSB_CPR2_TARG_VOLT_OFFSET_NOM_SHFT                                 0x10
#define HWIO_QFPROM_CORR_CALIB_ROW4_MSB_CPR2_TARG_VOLT_OFFSET_NOMPLUS_BMSK                           0xf000
#define HWIO_QFPROM_CORR_CALIB_ROW4_MSB_CPR2_TARG_VOLT_OFFSET_NOMPLUS_SHFT                              0xc
#define HWIO_QFPROM_CORR_CALIB_ROW4_MSB_CPR2_TARG_VOLT_SVS2_BMSK                                      0xf80
#define HWIO_QFPROM_CORR_CALIB_ROW4_MSB_CPR2_TARG_VOLT_SVS2_SHFT                                        0x7
#define HWIO_QFPROM_CORR_CALIB_ROW4_MSB_CPR2_TARG_VOLT_SVS_BMSK                                        0x7c
#define HWIO_QFPROM_CORR_CALIB_ROW4_MSB_CPR2_TARG_VOLT_SVS_SHFT                                         0x2
#define HWIO_QFPROM_CORR_CALIB_ROW4_MSB_CPR2_TARG_VOLT_NOM_4_3_BMSK                                     0x3
#define HWIO_QFPROM_CORR_CALIB_ROW4_MSB_CPR2_TARG_VOLT_NOM_4_3_SHFT                                     0x0

#define HWIO_QFPROM_CORR_CALIB_ROW5_LSB_ADDR                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004210)
#define HWIO_QFPROM_CORR_CALIB_ROW5_LSB_OFFS                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004210)
#define HWIO_QFPROM_CORR_CALIB_ROW5_LSB_RMSK                                                     0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW5_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW5_LSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW5_LSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW5_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW5_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW5_LSB_CPR4_TARG_VOLT_NOM_3_0_BMSK                              0xf0000000
#define HWIO_QFPROM_CORR_CALIB_ROW5_LSB_CPR4_TARG_VOLT_NOM_3_0_SHFT                                    0x1c
#define HWIO_QFPROM_CORR_CALIB_ROW5_LSB_CPR4_TARG_VOLT_TUR_BMSK                                   0xf800000
#define HWIO_QFPROM_CORR_CALIB_ROW5_LSB_CPR4_TARG_VOLT_TUR_SHFT                                        0x17
#define HWIO_QFPROM_CORR_CALIB_ROW5_LSB_CPR4_TARG_VOLT_SVS_BMSK                                    0x7c0000
#define HWIO_QFPROM_CORR_CALIB_ROW5_LSB_CPR4_TARG_VOLT_SVS_SHFT                                        0x12
#define HWIO_QFPROM_CORR_CALIB_ROW5_LSB_CPR7_TURBO_L2_ROSEL_BMSK                                    0x3c000
#define HWIO_QFPROM_CORR_CALIB_ROW5_LSB_CPR7_TURBO_L2_ROSEL_SHFT                                        0xe
#define HWIO_QFPROM_CORR_CALIB_ROW5_LSB_CPR3_TARG_VOLT_TUR_BMSK                                      0x3e00
#define HWIO_QFPROM_CORR_CALIB_ROW5_LSB_CPR3_TARG_VOLT_TUR_SHFT                                         0x9
#define HWIO_QFPROM_CORR_CALIB_ROW5_LSB_CPR3_TARG_VOLT_NOM_BMSK                                       0x1f0
#define HWIO_QFPROM_CORR_CALIB_ROW5_LSB_CPR3_TARG_VOLT_NOM_SHFT                                         0x4
#define HWIO_QFPROM_CORR_CALIB_ROW5_LSB_CPR2_AGING_7_4_BMSK                                             0xf
#define HWIO_QFPROM_CORR_CALIB_ROW5_LSB_CPR2_AGING_7_4_SHFT                                             0x0

#define HWIO_QFPROM_CORR_CALIB_ROW5_MSB_ADDR                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004214)
#define HWIO_QFPROM_CORR_CALIB_ROW5_MSB_OFFS                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004214)
#define HWIO_QFPROM_CORR_CALIB_ROW5_MSB_RMSK                                                      0x1ffffff
#define HWIO_QFPROM_CORR_CALIB_ROW5_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW5_MSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW5_MSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW5_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW5_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW5_MSB_CPR0_TARG_VOLT_OFFSET_SUTUR_BMSK                          0x1e00000
#define HWIO_QFPROM_CORR_CALIB_ROW5_MSB_CPR0_TARG_VOLT_OFFSET_SUTUR_SHFT                               0x15
#define HWIO_QFPROM_CORR_CALIB_ROW5_MSB_CPR0_TARG_VOLT_SUTUR_BMSK                                  0x1f0000
#define HWIO_QFPROM_CORR_CALIB_ROW5_MSB_CPR0_TARG_VOLT_SUTUR_SHFT                                      0x10
#define HWIO_QFPROM_CORR_CALIB_ROW5_MSB_CPR5_TARG_VOLT_TUR_BMSK                                      0xf800
#define HWIO_QFPROM_CORR_CALIB_ROW5_MSB_CPR5_TARG_VOLT_TUR_SHFT                                         0xb
#define HWIO_QFPROM_CORR_CALIB_ROW5_MSB_CPR5_TARG_VOLT_NOM_BMSK                                       0x7c0
#define HWIO_QFPROM_CORR_CALIB_ROW5_MSB_CPR5_TARG_VOLT_NOM_SHFT                                         0x6
#define HWIO_QFPROM_CORR_CALIB_ROW5_MSB_CPR4_TARG_VOLT_SVS2_BMSK                                       0x3e
#define HWIO_QFPROM_CORR_CALIB_ROW5_MSB_CPR4_TARG_VOLT_SVS2_SHFT                                        0x1
#define HWIO_QFPROM_CORR_CALIB_ROW5_MSB_CPR4_TARG_VOLT_NOM_4_BMSK                                       0x1
#define HWIO_QFPROM_CORR_CALIB_ROW5_MSB_CPR4_TARG_VOLT_NOM_4_SHFT                                       0x0

#define HWIO_QFPROM_CORR_CALIB_ROW6_LSB_ADDR                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004218)
#define HWIO_QFPROM_CORR_CALIB_ROW6_LSB_OFFS                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004218)
#define HWIO_QFPROM_CORR_CALIB_ROW6_LSB_RMSK                                                     0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW6_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW6_LSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW6_LSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW6_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW6_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW6_LSB_CPR6_TARG_VOLT_SVS_3_0_BMSK                              0xf0000000
#define HWIO_QFPROM_CORR_CALIB_ROW6_LSB_CPR6_TARG_VOLT_SVS_3_0_SHFT                                    0x1c
#define HWIO_QFPROM_CORR_CALIB_ROW6_LSB_CPR6_TARG_VOLT_NOM_BMSK                                   0xfc00000
#define HWIO_QFPROM_CORR_CALIB_ROW6_LSB_CPR6_TARG_VOLT_NOM_SHFT                                        0x16
#define HWIO_QFPROM_CORR_CALIB_ROW6_LSB_CPR6_TARG_VOLT_TUR_L1_BMSK                                 0x3f0000
#define HWIO_QFPROM_CORR_CALIB_ROW6_LSB_CPR6_TARG_VOLT_TUR_L1_SHFT                                     0x10
#define HWIO_QFPROM_CORR_CALIB_ROW6_LSB_CPR6_SVS2_ROSEL_BMSK                                         0xf000
#define HWIO_QFPROM_CORR_CALIB_ROW6_LSB_CPR6_SVS2_ROSEL_SHFT                                            0xc
#define HWIO_QFPROM_CORR_CALIB_ROW6_LSB_CPR6_SVS_ROSEL_BMSK                                           0xf00
#define HWIO_QFPROM_CORR_CALIB_ROW6_LSB_CPR6_SVS_ROSEL_SHFT                                             0x8
#define HWIO_QFPROM_CORR_CALIB_ROW6_LSB_CPR6_NOMINAL_ROSEL_BMSK                                        0xf0
#define HWIO_QFPROM_CORR_CALIB_ROW6_LSB_CPR6_NOMINAL_ROSEL_SHFT                                         0x4
#define HWIO_QFPROM_CORR_CALIB_ROW6_LSB_CPR6_TURBO_L1_ROSEL_BMSK                                        0xf
#define HWIO_QFPROM_CORR_CALIB_ROW6_LSB_CPR6_TURBO_L1_ROSEL_SHFT                                        0x0

#define HWIO_QFPROM_CORR_CALIB_ROW6_MSB_ADDR                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000421c)
#define HWIO_QFPROM_CORR_CALIB_ROW6_MSB_OFFS                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000421c)
#define HWIO_QFPROM_CORR_CALIB_ROW6_MSB_RMSK                                                     0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW6_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW6_MSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW6_MSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW6_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW6_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW6_MSB_CPR6_NOMINAL_QUOT_VMIN_BMSK                              0xfff00000
#define HWIO_QFPROM_CORR_CALIB_ROW6_MSB_CPR6_NOMINAL_QUOT_VMIN_SHFT                                    0x14
#define HWIO_QFPROM_CORR_CALIB_ROW6_MSB_CPR6_TURBO_L1_QUOT_VMIN_BMSK                                0xfff00
#define HWIO_QFPROM_CORR_CALIB_ROW6_MSB_CPR6_TURBO_L1_QUOT_VMIN_SHFT                                    0x8
#define HWIO_QFPROM_CORR_CALIB_ROW6_MSB_CPR6_TARG_VOLT_SVS2_BMSK                                       0xfc
#define HWIO_QFPROM_CORR_CALIB_ROW6_MSB_CPR6_TARG_VOLT_SVS2_SHFT                                        0x2
#define HWIO_QFPROM_CORR_CALIB_ROW6_MSB_CPR6_TARG_VOLT_SVS_5_4_BMSK                                     0x3
#define HWIO_QFPROM_CORR_CALIB_ROW6_MSB_CPR6_TARG_VOLT_SVS_5_4_SHFT                                     0x0

#define HWIO_QFPROM_CORR_CALIB_ROW7_LSB_ADDR                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004220)
#define HWIO_QFPROM_CORR_CALIB_ROW7_LSB_OFFS                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004220)
#define HWIO_QFPROM_CORR_CALIB_ROW7_LSB_RMSK                                                     0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW7_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW7_LSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW7_LSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW7_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW7_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW7_LSB_CPR6_QUOT_OFFSET_NOM_0_BMSK                              0x80000000
#define HWIO_QFPROM_CORR_CALIB_ROW7_LSB_CPR6_QUOT_OFFSET_NOM_0_SHFT                                    0x1f
#define HWIO_QFPROM_CORR_CALIB_ROW7_LSB_CPR6_QUOT_OFFSET_TUR_L1_BMSK                             0x7f000000
#define HWIO_QFPROM_CORR_CALIB_ROW7_LSB_CPR6_QUOT_OFFSET_TUR_L1_SHFT                                   0x18
#define HWIO_QFPROM_CORR_CALIB_ROW7_LSB_CPR6_SVS2_QUOT_VMIN_BMSK                                   0xfff000
#define HWIO_QFPROM_CORR_CALIB_ROW7_LSB_CPR6_SVS2_QUOT_VMIN_SHFT                                        0xc
#define HWIO_QFPROM_CORR_CALIB_ROW7_LSB_CPR6_SVS_QUOT_VMIN_BMSK                                       0xfff
#define HWIO_QFPROM_CORR_CALIB_ROW7_LSB_CPR6_SVS_QUOT_VMIN_SHFT                                         0x0

#define HWIO_QFPROM_CORR_CALIB_ROW7_MSB_ADDR                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004224)
#define HWIO_QFPROM_CORR_CALIB_ROW7_MSB_OFFS                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004224)
#define HWIO_QFPROM_CORR_CALIB_ROW7_MSB_RMSK                                                     0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW7_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW7_MSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW7_MSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW7_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW7_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW7_MSB_CPR7_SVS_ROSEL_2_0_BMSK                                  0xe0000000
#define HWIO_QFPROM_CORR_CALIB_ROW7_MSB_CPR7_SVS_ROSEL_2_0_SHFT                                        0x1d
#define HWIO_QFPROM_CORR_CALIB_ROW7_MSB_CPR7_NOMINAL_ROSEL_BMSK                                  0x1e000000
#define HWIO_QFPROM_CORR_CALIB_ROW7_MSB_CPR7_NOMINAL_ROSEL_SHFT                                        0x19
#define HWIO_QFPROM_CORR_CALIB_ROW7_MSB_CPR7_TURBO_ROSEL_BMSK                                     0x1e00000
#define HWIO_QFPROM_CORR_CALIB_ROW7_MSB_CPR7_TURBO_ROSEL_SHFT                                          0x15
#define HWIO_QFPROM_CORR_CALIB_ROW7_MSB_CPR6_AGING_BMSK                                            0x1fe000
#define HWIO_QFPROM_CORR_CALIB_ROW7_MSB_CPR6_AGING_SHFT                                                 0xd
#define HWIO_QFPROM_CORR_CALIB_ROW7_MSB_CPR6_QUOT_OFFSET_SVS_BMSK                                    0x1fc0
#define HWIO_QFPROM_CORR_CALIB_ROW7_MSB_CPR6_QUOT_OFFSET_SVS_SHFT                                       0x6
#define HWIO_QFPROM_CORR_CALIB_ROW7_MSB_CPR6_QUOT_OFFSET_NOM_6_1_BMSK                                  0x3f
#define HWIO_QFPROM_CORR_CALIB_ROW7_MSB_CPR6_QUOT_OFFSET_NOM_6_1_SHFT                                   0x0

#define HWIO_QFPROM_CORR_CALIB_ROW8_LSB_ADDR                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004228)
#define HWIO_QFPROM_CORR_CALIB_ROW8_LSB_OFFS                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004228)
#define HWIO_QFPROM_CORR_CALIB_ROW8_LSB_RMSK                                                     0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW8_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW8_LSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW8_LSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW8_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW8_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW8_LSB_CPR7_TURBO_QUOT_VMIN_2_0_BMSK                            0xe0000000
#define HWIO_QFPROM_CORR_CALIB_ROW8_LSB_CPR7_TURBO_QUOT_VMIN_2_0_SHFT                                  0x1d
#define HWIO_QFPROM_CORR_CALIB_ROW8_LSB_CPR7_TARG_VOLT_SVSPLUS_BMSK                              0x1f800000
#define HWIO_QFPROM_CORR_CALIB_ROW8_LSB_CPR7_TARG_VOLT_SVSPLUS_SHFT                                    0x17
#define HWIO_QFPROM_CORR_CALIB_ROW8_LSB_CPR7_TARG_VOLT_SVS_BMSK                                    0x7e0000
#define HWIO_QFPROM_CORR_CALIB_ROW8_LSB_CPR7_TARG_VOLT_SVS_SHFT                                        0x11
#define HWIO_QFPROM_CORR_CALIB_ROW8_LSB_CPR7_TARG_VOLT_NOM_BMSK                                     0x1f800
#define HWIO_QFPROM_CORR_CALIB_ROW8_LSB_CPR7_TARG_VOLT_NOM_SHFT                                         0xb
#define HWIO_QFPROM_CORR_CALIB_ROW8_LSB_CPR7_TARG_VOLT_TUR_BMSK                                       0x7e0
#define HWIO_QFPROM_CORR_CALIB_ROW8_LSB_CPR7_TARG_VOLT_TUR_SHFT                                         0x5
#define HWIO_QFPROM_CORR_CALIB_ROW8_LSB_CPR7_SVSPLUS_ROSEL_BMSK                                        0x1e
#define HWIO_QFPROM_CORR_CALIB_ROW8_LSB_CPR7_SVSPLUS_ROSEL_SHFT                                         0x1
#define HWIO_QFPROM_CORR_CALIB_ROW8_LSB_CPR7_SVS_ROSEL_3_BMSK                                           0x1
#define HWIO_QFPROM_CORR_CALIB_ROW8_LSB_CPR7_SVS_ROSEL_3_SHFT                                           0x0

#define HWIO_QFPROM_CORR_CALIB_ROW8_MSB_ADDR                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000422c)
#define HWIO_QFPROM_CORR_CALIB_ROW8_MSB_OFFS                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000422c)
#define HWIO_QFPROM_CORR_CALIB_ROW8_MSB_RMSK                                                     0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW8_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW8_MSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW8_MSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW8_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW8_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW8_MSB_CPR7_SVS_QUOT_VMIN_10_0_BMSK                             0xffe00000
#define HWIO_QFPROM_CORR_CALIB_ROW8_MSB_CPR7_SVS_QUOT_VMIN_10_0_SHFT                                   0x15
#define HWIO_QFPROM_CORR_CALIB_ROW8_MSB_CPR7_NOM_QUOT_VMIN_BMSK                                    0x1ffe00
#define HWIO_QFPROM_CORR_CALIB_ROW8_MSB_CPR7_NOM_QUOT_VMIN_SHFT                                         0x9
#define HWIO_QFPROM_CORR_CALIB_ROW8_MSB_CPR7_TURBO_QUOT_VMIN_11_3_BMSK                                0x1ff
#define HWIO_QFPROM_CORR_CALIB_ROW8_MSB_CPR7_TURBO_QUOT_VMIN_11_3_SHFT                                  0x0

#define HWIO_QFPROM_CORR_CALIB_ROW9_LSB_ADDR                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004230)
#define HWIO_QFPROM_CORR_CALIB_ROW9_LSB_OFFS                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004230)
#define HWIO_QFPROM_CORR_CALIB_ROW9_LSB_RMSK                                                     0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW9_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW9_LSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW9_LSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW9_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW9_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW9_LSB_CPR7_QOUT_OFFSET_SVSPLUS_4_0_BMSK                        0xf8000000
#define HWIO_QFPROM_CORR_CALIB_ROW9_LSB_CPR7_QOUT_OFFSET_SVSPLUS_4_0_SHFT                              0x1b
#define HWIO_QFPROM_CORR_CALIB_ROW9_LSB_CPR7_QOUT_OFFSET_NOM_BMSK                                 0x7f00000
#define HWIO_QFPROM_CORR_CALIB_ROW9_LSB_CPR7_QOUT_OFFSET_NOM_SHFT                                      0x14
#define HWIO_QFPROM_CORR_CALIB_ROW9_LSB_CPR7_QOUT_OFFSET_TUR_BMSK                                   0xfe000
#define HWIO_QFPROM_CORR_CALIB_ROW9_LSB_CPR7_QOUT_OFFSET_TUR_SHFT                                       0xd
#define HWIO_QFPROM_CORR_CALIB_ROW9_LSB_CPR7_SVSPLUS_QUOT_VMIN_BMSK                                  0x1ffe
#define HWIO_QFPROM_CORR_CALIB_ROW9_LSB_CPR7_SVSPLUS_QUOT_VMIN_SHFT                                     0x1
#define HWIO_QFPROM_CORR_CALIB_ROW9_LSB_CPR7_SVS_QUOT_VMIN_11_BMSK                                      0x1
#define HWIO_QFPROM_CORR_CALIB_ROW9_LSB_CPR7_SVS_QUOT_VMIN_11_SHFT                                      0x0

#define HWIO_QFPROM_CORR_CALIB_ROW9_MSB_ADDR                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004234)
#define HWIO_QFPROM_CORR_CALIB_ROW9_MSB_OFFS                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004234)
#define HWIO_QFPROM_CORR_CALIB_ROW9_MSB_RMSK                                                     0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW9_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW9_MSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW9_MSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW9_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW9_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW9_MSB_CPR7_QUOT_OFFSET_TURBO_L2_3_0_BMSK                       0xf0000000
#define HWIO_QFPROM_CORR_CALIB_ROW9_MSB_CPR7_QUOT_OFFSET_TURBO_L2_3_0_SHFT                             0x1c
#define HWIO_QFPROM_CORR_CALIB_ROW9_MSB_CPR7_TURBO_L2_QUOT_VMIN_BMSK                              0xfff0000
#define HWIO_QFPROM_CORR_CALIB_ROW9_MSB_CPR7_TURBO_L2_QUOT_VMIN_SHFT                                   0x10
#define HWIO_QFPROM_CORR_CALIB_ROW9_MSB_CPR7_TARG_VOLT_TURBO_L2_BMSK                                 0xfc00
#define HWIO_QFPROM_CORR_CALIB_ROW9_MSB_CPR7_TARG_VOLT_TURBO_L2_SHFT                                    0xa
#define HWIO_QFPROM_CORR_CALIB_ROW9_MSB_CPR7_AGING_BMSK                                               0x3fc
#define HWIO_QFPROM_CORR_CALIB_ROW9_MSB_CPR7_AGING_SHFT                                                 0x2
#define HWIO_QFPROM_CORR_CALIB_ROW9_MSB_CPR7_QOUT_OFFSET_SVSPLUS_6_5_BMSK                               0x3
#define HWIO_QFPROM_CORR_CALIB_ROW9_MSB_CPR7_QOUT_OFFSET_SVSPLUS_6_5_SHFT                               0x0

#define HWIO_QFPROM_CORR_CALIB_ROW10_LSB_ADDR                                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004238)
#define HWIO_QFPROM_CORR_CALIB_ROW10_LSB_OFFS                                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004238)
#define HWIO_QFPROM_CORR_CALIB_ROW10_LSB_RMSK                                                    0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW10_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW10_LSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW10_LSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW10_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW10_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW10_LSB_CPR_GLOBAL_RC_0_BMSK                                    0x80000000
#define HWIO_QFPROM_CORR_CALIB_ROW10_LSB_CPR_GLOBAL_RC_0_SHFT                                          0x1f
#define HWIO_QFPROM_CORR_CALIB_ROW10_LSB_CPR_LOCAL_RC_BMSK                                       0x70000000
#define HWIO_QFPROM_CORR_CALIB_ROW10_LSB_CPR_LOCAL_RC_SHFT                                             0x1c
#define HWIO_QFPROM_CORR_CALIB_ROW10_LSB_CPR9_QUOT_OFFSET_SVSPLUS_BMSK                            0xfe00000
#define HWIO_QFPROM_CORR_CALIB_ROW10_LSB_CPR9_QUOT_OFFSET_SVSPLUS_SHFT                                 0x15
#define HWIO_QFPROM_CORR_CALIB_ROW10_LSB_CPR6_SVSPLUS_QUOT_VMIN_BMSK                               0x1ffe00
#define HWIO_QFPROM_CORR_CALIB_ROW10_LSB_CPR6_SVSPLUS_QUOT_VMIN_SHFT                                    0x9
#define HWIO_QFPROM_CORR_CALIB_ROW10_LSB_CPR6_TARG_VOLT_SVSPLUS_BMSK                                  0x1f8
#define HWIO_QFPROM_CORR_CALIB_ROW10_LSB_CPR6_TARG_VOLT_SVSPLUS_SHFT                                    0x3
#define HWIO_QFPROM_CORR_CALIB_ROW10_LSB_CPR7_QUOT_OFFSET_TURBO_L2_6_4_BMSK                             0x7
#define HWIO_QFPROM_CORR_CALIB_ROW10_LSB_CPR7_QUOT_OFFSET_TURBO_L2_6_4_SHFT                             0x0

#define HWIO_QFPROM_CORR_CALIB_ROW10_MSB_ADDR                                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000423c)
#define HWIO_QFPROM_CORR_CALIB_ROW10_MSB_OFFS                                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000423c)
#define HWIO_QFPROM_CORR_CALIB_ROW10_MSB_RMSK                                                    0xffffc07f
#define HWIO_QFPROM_CORR_CALIB_ROW10_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW10_MSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW10_MSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW10_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW10_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW10_MSB_SPARE_71_63_BMSK                                        0x80000000
#define HWIO_QFPROM_CORR_CALIB_ROW10_MSB_SPARE_71_63_SHFT                                              0x1f
#define HWIO_QFPROM_CORR_CALIB_ROW10_MSB_SPARE_71_62_BMSK                                        0x40000000
#define HWIO_QFPROM_CORR_CALIB_ROW10_MSB_SPARE_71_62_SHFT                                              0x1e
#define HWIO_QFPROM_CORR_CALIB_ROW10_MSB_SPARE_71_61_BMSK                                        0x20000000
#define HWIO_QFPROM_CORR_CALIB_ROW10_MSB_SPARE_71_61_SHFT                                              0x1d
#define HWIO_QFPROM_CORR_CALIB_ROW10_MSB_SW_CAL_REDUN_SEL_BMSK                                   0x1c000000
#define HWIO_QFPROM_CORR_CALIB_ROW10_MSB_SW_CAL_REDUN_SEL_SHFT                                         0x1a
#define HWIO_QFPROM_CORR_CALIB_ROW10_MSB_CPR_RESERVED_BMSK                                        0x3ffc000
#define HWIO_QFPROM_CORR_CALIB_ROW10_MSB_CPR_RESERVED_SHFT                                              0xe
#define HWIO_QFPROM_CORR_CALIB_ROW10_MSB_GFX_LOD_CPR_CL_ENABLE_BMSK                                    0x40
#define HWIO_QFPROM_CORR_CALIB_ROW10_MSB_GFX_LOD_CPR_CL_ENABLE_SHFT                                     0x6
#define HWIO_QFPROM_CORR_CALIB_ROW10_MSB_CPR7_BINNING_ENABLE_BMSK                                      0x20
#define HWIO_QFPROM_CORR_CALIB_ROW10_MSB_CPR7_BINNING_ENABLE_SHFT                                       0x5
#define HWIO_QFPROM_CORR_CALIB_ROW10_MSB_CPR_GFX_LDO_RC_BMSK                                           0x1c
#define HWIO_QFPROM_CORR_CALIB_ROW10_MSB_CPR_GFX_LDO_RC_SHFT                                            0x2
#define HWIO_QFPROM_CORR_CALIB_ROW10_MSB_CPR_GLOBAL_RC_2_1_BMSK                                         0x3
#define HWIO_QFPROM_CORR_CALIB_ROW10_MSB_CPR_GLOBAL_RC_2_1_SHFT                                         0x0

#define HWIO_QFPROM_CORR_CALIB_ROW11_LSB_ADDR                                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004240)
#define HWIO_QFPROM_CORR_CALIB_ROW11_LSB_OFFS                                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004240)
#define HWIO_QFPROM_CORR_CALIB_ROW11_LSB_RMSK                                                    0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW11_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW11_LSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW11_LSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW11_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW11_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW11_LSB_SPARE_72_31_BMSK                                        0x80000000
#define HWIO_QFPROM_CORR_CALIB_ROW11_LSB_SPARE_72_31_SHFT                                              0x1f
#define HWIO_QFPROM_CORR_CALIB_ROW11_LSB_SPARE_72_30_BMSK                                        0x40000000
#define HWIO_QFPROM_CORR_CALIB_ROW11_LSB_SPARE_72_30_SHFT                                              0x1e
#define HWIO_QFPROM_CORR_CALIB_ROW11_LSB_QUSB_REFCLK_SEL_BMSK                                    0x20000000
#define HWIO_QFPROM_CORR_CALIB_ROW11_LSB_QUSB_REFCLK_SEL_SHFT                                          0x1d
#define HWIO_QFPROM_CORR_CALIB_ROW11_LSB_QUSB_PORT0_HSTX_TRIM_LSB_BMSK                           0x1e000000
#define HWIO_QFPROM_CORR_CALIB_ROW11_LSB_QUSB_PORT0_HSTX_TRIM_LSB_SHFT                                 0x19
#define HWIO_QFPROM_CORR_CALIB_ROW11_LSB_SRAM_AGING_SENSOR_1_BMSK                                 0x1fe0000
#define HWIO_QFPROM_CORR_CALIB_ROW11_LSB_SRAM_AGING_SENSOR_1_SHFT                                      0x11
#define HWIO_QFPROM_CORR_CALIB_ROW11_LSB_SRAM_AGING_SENSOR_0_BMSK                                   0x1fe00
#define HWIO_QFPROM_CORR_CALIB_ROW11_LSB_SRAM_AGING_SENSOR_0_SHFT                                       0x9
#define HWIO_QFPROM_CORR_CALIB_ROW11_LSB_GNSS_ADC_RSB_BMSK                                            0x1c0
#define HWIO_QFPROM_CORR_CALIB_ROW11_LSB_GNSS_ADC_RSB_SHFT                                              0x6
#define HWIO_QFPROM_CORR_CALIB_ROW11_LSB_GNSS_ADC_LDO_BMSK                                             0x38
#define HWIO_QFPROM_CORR_CALIB_ROW11_LSB_GNSS_ADC_LDO_SHFT                                              0x3
#define HWIO_QFPROM_CORR_CALIB_ROW11_LSB_GNSS_ADC_VREF_BMSK                                             0x7
#define HWIO_QFPROM_CORR_CALIB_ROW11_LSB_GNSS_ADC_VREF_SHFT                                             0x0

#define HWIO_QFPROM_CORR_CALIB_ROW11_MSB_ADDR                                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004244)
#define HWIO_QFPROM_CORR_CALIB_ROW11_MSB_OFFS                                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004244)
#define HWIO_QFPROM_CORR_CALIB_ROW11_MSB_RMSK                                                    0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW11_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW11_MSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW11_MSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW11_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW11_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW11_MSB_TSENS2_OFFSET_BMSK                                      0xf0000000
#define HWIO_QFPROM_CORR_CALIB_ROW11_MSB_TSENS2_OFFSET_SHFT                                            0x1c
#define HWIO_QFPROM_CORR_CALIB_ROW11_MSB_TSENS1_OFFSET_BMSK                                       0xf000000
#define HWIO_QFPROM_CORR_CALIB_ROW11_MSB_TSENS1_OFFSET_SHFT                                            0x18
#define HWIO_QFPROM_CORR_CALIB_ROW11_MSB_TSENS0_OFFSET_BMSK                                        0xf00000
#define HWIO_QFPROM_CORR_CALIB_ROW11_MSB_TSENS0_OFFSET_SHFT                                            0x14
#define HWIO_QFPROM_CORR_CALIB_ROW11_MSB_TSENS1_BASE1_BMSK                                          0xffc00
#define HWIO_QFPROM_CORR_CALIB_ROW11_MSB_TSENS1_BASE1_SHFT                                              0xa
#define HWIO_QFPROM_CORR_CALIB_ROW11_MSB_TSENS1_BASE0_BMSK                                            0x3ff
#define HWIO_QFPROM_CORR_CALIB_ROW11_MSB_TSENS1_BASE0_SHFT                                              0x0

#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_ADDR                                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004248)
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_OFFS                                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004248)
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_RMSK                                                    0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW12_LSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW12_LSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW12_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_TSENS10_OFFSET_BMSK                                     0xf0000000
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_TSENS10_OFFSET_SHFT                                           0x1c
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_TSENS9_OFFSET_BMSK                                       0xf000000
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_TSENS9_OFFSET_SHFT                                            0x18
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_TSENS8_OFFSET_BMSK                                        0xf00000
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_TSENS8_OFFSET_SHFT                                            0x14
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_TSENS7_OFFSET_BMSK                                         0xf0000
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_TSENS7_OFFSET_SHFT                                            0x10
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_TSENS6_OFFSET_BMSK                                          0xf000
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_TSENS6_OFFSET_SHFT                                             0xc
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_TSENS5_OFFSET_BMSK                                           0xf00
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_TSENS5_OFFSET_SHFT                                             0x8
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_TSENS4_OFFSET_BMSK                                            0xf0
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_TSENS4_OFFSET_SHFT                                             0x4
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_TSENS3_OFFSET_BMSK                                             0xf
#define HWIO_QFPROM_CORR_CALIB_ROW12_LSB_TSENS3_OFFSET_SHFT                                             0x0

#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_ADDR                                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000424c)
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_OFFS                                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000424c)
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_RMSK                                                    0x7e0fffff
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW12_MSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW12_MSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW12_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_GFX_LDO_ENABLE_SVS3_BMSK                                0x40000000
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_GFX_LDO_ENABLE_SVS3_SHFT                                      0x1e
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_GFX_LDO_ENABLE_SVS2_BMSK                                0x20000000
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_GFX_LDO_ENABLE_SVS2_SHFT                                      0x1d
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_GFX_LDO_ENABLE_SVSP_BMSK                                0x10000000
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_GFX_LDO_ENABLE_SVSP_SHFT                                      0x1c
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_GFX_LDO_ENABLE_SVS_BMSK                                  0x8000000
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_GFX_LDO_ENABLE_SVS_SHFT                                       0x1b
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_GFX_LDO_ENABLE_NOM_BMSK                                  0x4000000
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_GFX_LDO_ENABLE_NOM_SHFT                                       0x1a
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_GFX_LDO_ENABLE_NOMP_BMSK                                 0x2000000
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_GFX_LDO_ENABLE_NOMP_SHFT                                      0x19
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_MSS_Q6_LDO_ENABLE_SVS3_BMSK                                0x80000
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_MSS_Q6_LDO_ENABLE_SVS3_SHFT                                   0x13
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_MSS_Q6_LDO_ENABLE_SVS2_BMSK                                0x40000
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_MSS_Q6_LDO_ENABLE_SVS2_SHFT                                   0x12
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_MSS_Q6_LDO_ENABLE_SVS_BMSK                                 0x20000
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_MSS_Q6_LDO_ENABLE_SVS_SHFT                                    0x11
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_MSS_Q6_LDO_ENABLE_SVSP_BMSK                                0x10000
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_MSS_Q6_LDO_ENABLE_SVSP_SHFT                                   0x10
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_MSS_Q6_LDO_ENABLE_NOM_BMSK                                  0x8000
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_MSS_Q6_LDO_ENABLE_NOM_SHFT                                     0xf
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_TSENS_CAL_SEL_BMSK                                          0x7000
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_TSENS_CAL_SEL_SHFT                                             0xc
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_TSENS13_OFFSET_BMSK                                          0xf00
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_TSENS13_OFFSET_SHFT                                            0x8
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_TSENS12_OFFSET_BMSK                                           0xf0
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_TSENS12_OFFSET_SHFT                                            0x4
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_TSENS11_OFFSET_BMSK                                            0xf
#define HWIO_QFPROM_CORR_CALIB_ROW12_MSB_TSENS11_OFFSET_SHFT                                            0x0

#define HWIO_QFPROM_CORR_CALIB_ROW13_LSB_ADDR                                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004250)
#define HWIO_QFPROM_CORR_CALIB_ROW13_LSB_OFFS                                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004250)
#define HWIO_QFPROM_CORR_CALIB_ROW13_LSB_RMSK                                                           0xf
#define HWIO_QFPROM_CORR_CALIB_ROW13_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW13_LSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW13_LSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW13_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW13_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW13_LSB_RSVD_HVX_LDO_ENABLE_SVS3_BMSK                                  0x8
#define HWIO_QFPROM_CORR_CALIB_ROW13_LSB_RSVD_HVX_LDO_ENABLE_SVS3_SHFT                                  0x3
#define HWIO_QFPROM_CORR_CALIB_ROW13_LSB_RSVD_HVX_LDO_ENABLE_SVS2_BMSK                                  0x4
#define HWIO_QFPROM_CORR_CALIB_ROW13_LSB_RSVD_HVX_LDO_ENABLE_SVS2_SHFT                                  0x2
#define HWIO_QFPROM_CORR_CALIB_ROW13_LSB_RSVD_HVX_LDO_ENABLE_SVS1_BMSK                                  0x2
#define HWIO_QFPROM_CORR_CALIB_ROW13_LSB_RSVD_HVX_LDO_ENABLE_SVS1_SHFT                                  0x1
#define HWIO_QFPROM_CORR_CALIB_ROW13_LSB_RSVD_HVX_LDO_ENABLE_SVSP_BMSK                                  0x1
#define HWIO_QFPROM_CORR_CALIB_ROW13_LSB_RSVD_HVX_LDO_ENABLE_SVSP_SHFT                                  0x0

#define HWIO_QFPROM_CORR_CALIB_ROW13_MSB_ADDR                                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004254)
#define HWIO_QFPROM_CORR_CALIB_ROW13_MSB_OFFS                                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004254)
#define HWIO_QFPROM_CORR_CALIB_ROW13_MSB_RMSK                                                    0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW13_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW13_MSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW13_MSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW13_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW13_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW13_MSB_OUT(v)      \
        out_dword(HWIO_QFPROM_CORR_CALIB_ROW13_MSB_ADDR,v)
#define HWIO_QFPROM_CORR_CALIB_ROW13_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_CORR_CALIB_ROW13_MSB_ADDR,m,v,HWIO_QFPROM_CORR_CALIB_ROW13_MSB_IN)
#define HWIO_QFPROM_CORR_CALIB_ROW13_MSB_RSVD_BMSK                                               0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW13_MSB_RSVD_SHFT                                                      0x0

#define HWIO_QFPROM_CORR_CALIB_ROW14_LSB_ADDR                                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004258)
#define HWIO_QFPROM_CORR_CALIB_ROW14_LSB_OFFS                                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004258)
#define HWIO_QFPROM_CORR_CALIB_ROW14_LSB_RMSK                                                    0xffffffc0
#define HWIO_QFPROM_CORR_CALIB_ROW14_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW14_LSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW14_LSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW14_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW14_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW14_LSB_VSENSE_CALIB_25_0_BMSK                                  0xffffffc0
#define HWIO_QFPROM_CORR_CALIB_ROW14_LSB_VSENSE_CALIB_25_0_SHFT                                         0x6

#define HWIO_QFPROM_CORR_CALIB_ROW14_MSB_ADDR                                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000425c)
#define HWIO_QFPROM_CORR_CALIB_ROW14_MSB_OFFS                                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000425c)
#define HWIO_QFPROM_CORR_CALIB_ROW14_MSB_RMSK                                                     0xfffffff
#define HWIO_QFPROM_CORR_CALIB_ROW14_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW14_MSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW14_MSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW14_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW14_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW14_MSB_VSENSE_CALIB_53_26_BMSK                                  0xfffffff
#define HWIO_QFPROM_CORR_CALIB_ROW14_MSB_VSENSE_CALIB_53_26_SHFT                                        0x0

#define HWIO_QFPROM_CORR_CALIB_ROW15_LSB_ADDR                                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004260)
#define HWIO_QFPROM_CORR_CALIB_ROW15_LSB_OFFS                                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004260)
#define HWIO_QFPROM_CORR_CALIB_ROW15_LSB_RMSK                                                    0xfffffffe
#define HWIO_QFPROM_CORR_CALIB_ROW15_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW15_LSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW15_LSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW15_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW15_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW15_LSB_SW_CAL_REDUNDANCY_30_0_BMSK                             0xfffffffe
#define HWIO_QFPROM_CORR_CALIB_ROW15_LSB_SW_CAL_REDUNDANCY_30_0_SHFT                                    0x1

#define HWIO_QFPROM_CORR_CALIB_ROW15_MSB_ADDR                                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004264)
#define HWIO_QFPROM_CORR_CALIB_ROW15_MSB_OFFS                                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004264)
#define HWIO_QFPROM_CORR_CALIB_ROW15_MSB_RMSK                                                    0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW15_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW15_MSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW15_MSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW15_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW15_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW15_MSB_SW_CAL_REDUNDANCY_62_31_BMSK                            0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW15_MSB_SW_CAL_REDUNDANCY_62_31_SHFT                                   0x0

#define HWIO_QFPROM_CORR_CALIB_ROW16_LSB_ADDR                                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004268)
#define HWIO_QFPROM_CORR_CALIB_ROW16_LSB_OFFS                                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004268)
#define HWIO_QFPROM_CORR_CALIB_ROW16_LSB_RMSK                                                    0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW16_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW16_LSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW16_LSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW16_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW16_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW16_LSB_SW_CAL_REDUNDANCY_94_63_BMSK                            0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW16_LSB_SW_CAL_REDUNDANCY_94_63_SHFT                                   0x0

#define HWIO_QFPROM_CORR_CALIB_ROW16_MSB_ADDR                                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000426c)
#define HWIO_QFPROM_CORR_CALIB_ROW16_MSB_OFFS                                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000426c)
#define HWIO_QFPROM_CORR_CALIB_ROW16_MSB_RMSK                                                    0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW16_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW16_MSB_ADDR, HWIO_QFPROM_CORR_CALIB_ROW16_MSB_RMSK)
#define HWIO_QFPROM_CORR_CALIB_ROW16_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIB_ROW16_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIB_ROW16_MSB_SW_CAL_REDUNDANCY_126_95_BMSK                           0xffffffff
#define HWIO_QFPROM_CORR_CALIB_ROW16_MSB_SW_CAL_REDUNDANCY_126_95_SHFT                                  0x0

#define HWIO_QFPROM_CORR_MEM_CONFIG_ROWn_LSB_ADDR(n)                                             (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004270 + 0x8 * (n))
#define HWIO_QFPROM_CORR_MEM_CONFIG_ROWn_LSB_OFFS(n)                                             (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004270 + 0x8 * (n))
#define HWIO_QFPROM_CORR_MEM_CONFIG_ROWn_LSB_RMSK                                                0xffffffff
#define HWIO_QFPROM_CORR_MEM_CONFIG_ROWn_LSB_MAXn                                                        18
#define HWIO_QFPROM_CORR_MEM_CONFIG_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_MEM_CONFIG_ROWn_LSB_ADDR(n), HWIO_QFPROM_CORR_MEM_CONFIG_ROWn_LSB_RMSK)
#define HWIO_QFPROM_CORR_MEM_CONFIG_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_MEM_CONFIG_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_MEM_CONFIG_ROWn_LSB_REDUN_DATA_BMSK                                     0xffffffff
#define HWIO_QFPROM_CORR_MEM_CONFIG_ROWn_LSB_REDUN_DATA_SHFT                                            0x0

#define HWIO_QFPROM_CORR_MEM_CONFIG_ROWn_MSB_ADDR(n)                                             (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004274 + 0x8 * (n))
#define HWIO_QFPROM_CORR_MEM_CONFIG_ROWn_MSB_OFFS(n)                                             (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004274 + 0x8 * (n))
#define HWIO_QFPROM_CORR_MEM_CONFIG_ROWn_MSB_RMSK                                                0xffffffff
#define HWIO_QFPROM_CORR_MEM_CONFIG_ROWn_MSB_MAXn                                                        18
#define HWIO_QFPROM_CORR_MEM_CONFIG_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_MEM_CONFIG_ROWn_MSB_ADDR(n), HWIO_QFPROM_CORR_MEM_CONFIG_ROWn_MSB_RMSK)
#define HWIO_QFPROM_CORR_MEM_CONFIG_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_MEM_CONFIG_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_MEM_CONFIG_ROWn_MSB_REDUN_DATA_BMSK                                     0xffffffff
#define HWIO_QFPROM_CORR_MEM_CONFIG_ROWn_MSB_REDUN_DATA_SHFT                                            0x0

#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_ADDR                                            (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004308)
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_OFFS                                            (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004308)
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_RMSK                                            0xffffffff
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_ADDR, HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_RMSK)
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_UFS_SW_CONTROL_DISABLE_BMSK                     0x80000000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_UFS_SW_CONTROL_DISABLE_SHFT                           0x1f
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_RSVD2_BMSK                                      0x40000000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_RSVD2_SHFT                                            0x1e
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_RSVD1_BMSK                                      0x20000000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_RSVD1_SHFT                                            0x1d
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_GFX3D_FREQ_LIMIT_VAL_BMSK                       0x1fe00000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_GFX3D_FREQ_LIMIT_VAL_SHFT                             0x15
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_MDSS_RESOLUTION_LIMIT_BMSK                        0x180000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_MDSS_RESOLUTION_LIMIT_SHFT                            0x13
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_VENUS_HEVC_ENCODE_DISABLE_BMSK                     0x40000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_VENUS_HEVC_ENCODE_DISABLE_SHFT                        0x12
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_VENUS_HEVC_DECODE_DISABLE_BMSK                     0x20000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_VENUS_HEVC_DECODE_DISABLE_SHFT                        0x11
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_VENUS_4K_DISABLE_BMSK                              0x10000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_VENUS_4K_DISABLE_SHFT                                 0x10
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_VP8_DECODER_DISABLE_BMSK                            0x8000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_VP8_DECODER_DISABLE_SHFT                               0xf
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_VP8_ENCODER_DISABLE_BMSK                            0x4000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_VP8_ENCODER_DISABLE_SHFT                               0xe
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_HDMI_DP_DISABLE_BMSK                                0x2000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_HDMI_DP_DISABLE_SHFT                                   0xd
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_HDCP_DISABLE_BMSK                                   0x1000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_HDCP_DISABLE_SHFT                                      0xc
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_MDP_APICAL_LTC_DISABLE_BMSK                          0x800
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_MDP_APICAL_LTC_DISABLE_SHFT                            0xb
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_HDCP_GLOBAL_KEY_SPLIT2_DISABLE_BMSK                  0x400
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_HDCP_GLOBAL_KEY_SPLIT2_DISABLE_SHFT                    0xa
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_DSI_1_DISABLE_BMSK                                   0x200
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_DSI_1_DISABLE_SHFT                                     0x9
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_USB2_DISABLE_BMSK                                    0x100
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_USB2_DISABLE_SHFT                                      0x8
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_RSVD0_BMSK                                            0x80
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_RSVD0_SHFT                                             0x7
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_CSID_DPCM_14_DISABLE_BMSK                             0x40
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_CSID_DPCM_14_DISABLE_SHFT                              0x6
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_ISP_1_DISABLE_BMSK                                    0x20
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_ISP_1_DISABLE_SHFT                                     0x5
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_CSID_3_DISABLE_BMSK                                   0x10
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_CSID_3_DISABLE_SHFT                                    0x4
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_CSID_2_DISABLE_BMSK                                    0x8
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_CSID_2_DISABLE_SHFT                                    0x3
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_BOOT_ROM_PATCH_DISABLE_BMSK                            0x7
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_LSB_BOOT_ROM_PATCH_DISABLE_SHFT                            0x0

#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_ADDR                                            (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000430c)
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_OFFS                                            (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000430c)
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_RMSK                                            0xffffffff
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_ADDR, HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_RMSK)
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_ICE_FORCE_HW_KEY1_BMSK                          0x80000000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_ICE_FORCE_HW_KEY1_SHFT                                0x1f
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_ICE_FORCE_HW_KEY0_BMSK                          0x40000000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_ICE_FORCE_HW_KEY0_SHFT                                0x1e
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_ICE_DISABLE_BMSK                                0x20000000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_ICE_DISABLE_SHFT                                      0x1d
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_RSVD2_BMSK                                      0x10000000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_RSVD2_SHFT                                            0x1c
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_RSVD1_BMSK                                       0x8000000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_RSVD1_SHFT                                            0x1b
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_LPASS_SENSOR_DISABLE_BMSK                        0x4000000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_LPASS_SENSOR_DISABLE_SHFT                             0x1a
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_LPASS_ISLAND_MODE_Q6_CLK_DISABLE_BMSK            0x2000000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_LPASS_ISLAND_MODE_Q6_CLK_DISABLE_SHFT                 0x19
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_LPASS_SW_ISLAND_MODE_DISABLE_BMSK                0x1000000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_LPASS_SW_ISLAND_MODE_DISABLE_SHFT                     0x18
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_LPASS_EFUSE_TESTBUS_READ_DISABLE_BMSK             0x800000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_LPASS_EFUSE_TESTBUS_READ_DISABLE_SHFT                 0x17
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_APS_RESET_DISABLE_BMSK                            0x400000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_APS_RESET_DISABLE_SHFT                                0x16
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_HVX_DISABLE_BMSK                                  0x200000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_HVX_DISABLE_SHFT                                      0x15
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_APB2JTAG_DISABLE_BMSK                             0x100000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_APB2JTAG_DISABLE_SHFT                                 0x14
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_RSVD6_BMSK                                         0x80000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_RSVD6_SHFT                                            0x13
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_STACKED_MEMORY_ID_BMSK                             0x7c000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_STACKED_MEMORY_ID_SHFT                                 0xe
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_PRNG_TESTMODE_DISABLE_BMSK                          0x2000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_PRNG_TESTMODE_DISABLE_SHFT                             0xd
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_CDSP_DISABLE_BMSK                                   0x1000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_CDSP_DISABLE_SHFT                                      0xc
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_MOCHA_PART_BMSK                                      0x800
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_MOCHA_PART_SHFT                                        0xb
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_RSVD5_BMSK                                           0x400
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_RSVD5_SHFT                                             0xa
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_RSVD4_BMSK                                           0x200
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_RSVD4_SHFT                                             0x9
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_RSVD3_BMSK                                           0x1e0
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_RSVD3_SHFT                                             0x5
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_CM_FEAT_CONFIG_DISABLE_BMSK                           0x10
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_CM_FEAT_CONFIG_DISABLE_SHFT                            0x4
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_VFE_RESOLUTION_LIMIT_BMSK                              0x8
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_VFE_RESOLUTION_LIMIT_SHFT                              0x3
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_GLD_PDX_FIFO_NIU_BMSK                                  0x4
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_GLD_PDX_FIFO_NIU_SHFT                                  0x2
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_RSVD0_BMSK                                             0x2
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_RSVD0_SHFT                                             0x1
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_VP9_DECODER_DISABLE_BMSK                               0x1
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW0_MSB_VP9_DECODER_DISABLE_SHFT                               0x0

#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_LSB_ADDR                                            (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004310)
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_LSB_OFFS                                            (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004310)
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_LSB_RMSK                                            0xffffffff
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_LSB_ADDR, HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_LSB_RMSK)
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_LSB_MDSP_FW_DISABLE_BMSK                            0xfff00000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_LSB_MDSP_FW_DISABLE_SHFT                                  0x14
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_LSB_RSVD0_BMSK                                         0x80000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_LSB_RSVD0_SHFT                                            0x13
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_LSB_NAV_DISABLE_BMSK                                   0x40000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_LSB_NAV_DISABLE_SHFT                                      0x12
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_LSB_SYS_APCCCFGNMFI_BMSK                               0x20000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_LSB_SYS_APCCCFGNMFI_SHFT                                  0x11
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_LSB_GLD_PDX_FIFO_ACE1_BMSK                             0x10000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_LSB_GLD_PDX_FIFO_ACE1_SHFT                                0x10
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_LSB_GLD_PDX_FIFO_ACE0_BMSK                              0x8000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_LSB_GLD_PDX_FIFO_ACE0_SHFT                                 0xf
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_LSB_MODEM_FEATURE_DISABLE_SPARE_BMSK                    0x7fe0
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_LSB_MODEM_FEATURE_DISABLE_SPARE_SHFT                       0x5
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_LSB_MODEM_FEATURE_DISABLE_SLICE_BMSK                      0x1f
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_LSB_MODEM_FEATURE_DISABLE_SLICE_SHFT                       0x0

#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_MSB_ADDR                                            (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004314)
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_MSB_OFFS                                            (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004314)
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_MSB_RMSK                                            0xffffffff
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_MSB_ADDR, HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_MSB_RMSK)
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_MSB_SYS_APCX_SYSBARDISABLE_BMSK                     0x80000000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_MSB_SYS_APCX_SYSBARDISABLE_SHFT                           0x1f
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_MSB_SYS_APCSCFGAPMBOOTONMX_BMSK                     0x60000000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_MSB_SYS_APCSCFGAPMBOOTONMX_SHFT                           0x1d
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_MSB_SYS_APCCCFGCPUPRESENT_N_BMSK                    0x1fe00000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_MSB_SYS_APCCCFGCPUPRESENT_N_SHFT                          0x15
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_MSB_APPS_ACG_DISABLE_BMSK                             0x100000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_MSB_APPS_ACG_DISABLE_SHFT                                 0x14
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_MSB_RSVD1_BMSK                                         0xf0000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_MSB_RSVD1_SHFT                                            0x10
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_MSB_MODEM_VU_DISABLE_BMSK                               0xffff
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW1_MSB_MODEM_VU_DISABLE_SHFT                                  0x0

#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_ADDR                                            (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004318)
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_OFFS                                            (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004318)
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_RMSK                                            0xffffffff
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_ADDR, HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_RMSK)
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_APPS_SPNIDEN_DISABLE_BMSK                    0x80000000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_APPS_SPNIDEN_DISABLE_SHFT                          0x1f
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_MSS_NIDEN_DISABLE_BMSK                       0x40000000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_MSS_NIDEN_DISABLE_SHFT                             0x1e
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_LPASS_SENSOR_NIDEN_DISABLE_BMSK              0x20000000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_LPASS_SENSOR_NIDEN_DISABLE_SHFT                    0x1d
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_PIMEM_NIDEN_DISABLE_BMSK                     0x10000000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_PIMEM_NIDEN_DISABLE_SHFT                           0x1c
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_RPM_NIDEN_DISABLE_BMSK                        0x8000000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_RPM_NIDEN_DISABLE_SHFT                             0x1b
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_WCSS_NIDEN_DISABLE_BMSK                       0x4000000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_WCSS_NIDEN_DISABLE_SHFT                            0x1a
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_LPASS_NIDEN_DISABLE_BMSK                      0x2000000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_LPASS_NIDEN_DISABLE_SHFT                           0x19
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_DAP_NIDEN_DISABLE_BMSK                        0x1000000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_DAP_NIDEN_DISABLE_SHFT                             0x18
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_APPS_NIDEN_DISABLE_BMSK                        0x800000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_APPS_NIDEN_DISABLE_SHFT                            0x17
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_MSS_DBGEN_DISABLE_BMSK                         0x400000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_MSS_DBGEN_DISABLE_SHFT                             0x16
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_A5X_ISDB_DBGEN_DISABLE_BMSK                    0x200000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_A5X_ISDB_DBGEN_DISABLE_SHFT                        0x15
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_VENUS_0_DBGEN_DISABLE_BMSK                     0x100000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_VENUS_0_DBGEN_DISABLE_SHFT                         0x14
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_TURING_EFUSE_TESTBUS_READ_DISABLE_BMSK             0x80000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_TURING_EFUSE_TESTBUS_READ_DISABLE_SHFT                0x13
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_LPASS_SENSOR_DBGEN_DISABLE_BMSK                 0x40000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_LPASS_SENSOR_DBGEN_DISABLE_SHFT                    0x12
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_PIMEM_DBGEN_DISABLE_BMSK                        0x20000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_PIMEM_DBGEN_DISABLE_SHFT                           0x11
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_RPM_DBGEN_DISABLE_BMSK                          0x10000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_RPM_DBGEN_DISABLE_SHFT                             0x10
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_WCSS_DBGEN_DISABLE_BMSK                          0x8000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_WCSS_DBGEN_DISABLE_SHFT                             0xf
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_LPASS_Q6_DBGEN_DISABLE_BMSK                      0x4000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_LPASS_Q6_DBGEN_DISABLE_SHFT                         0xe
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_DAP_DBGEN_DISABLE_BMSK                           0x2000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_DAP_DBGEN_DISABLE_SHFT                              0xd
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_APPS_DBGEN_DISABLE_BMSK                          0x1000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_APPS_DBGEN_DISABLE_SHFT                             0xc
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_DAP_DEVICEEN_DISABLE_BMSK                         0x800
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_DAP_DEVICEEN_DISABLE_SHFT                           0xb
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_RPM_DAPEN_DISABLE_BMSK                            0x400
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_RPM_DAPEN_DISABLE_SHFT                              0xa
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_DSI_0_DISABLE_BMSK                                   0x200
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_DSI_0_DISABLE_SHFT                                     0x9
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_DEBUG_BUS_DISABLE_BMSK                            0x100
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_DEBUG_BUS_DISABLE_SHFT                              0x8
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_DCC_DEBUG_DISABLE_BMSK                             0x80
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_DCC_DEBUG_DISABLE_SHFT                              0x7
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_APPS_APB_DFD_DISABLE_BMSK                          0x40
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_APPS_APB_DFD_DISABLE_SHFT                           0x6
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_GPMU_NIDEN_DISABLE_BMSK                            0x20
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_GPMU_NIDEN_DISABLE_SHFT                             0x5
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_GPMU_DBGEN_DISABLE_BMSK                            0x10
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_GPMU_DBGEN_DISABLE_SHFT                             0x4
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_GPMU_DAPEN_DISABLE_BMSK                             0x8
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QC_GPMU_DAPEN_DISABLE_SHFT                             0x3
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QDI_SPMI_DISABLE_BMSK                                  0x4
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_QDI_SPMI_DISABLE_SHFT                                  0x2
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_SM_BIST_DISABLE_BMSK                                   0x2
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_SM_BIST_DISABLE_SHFT                                   0x1
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_TIC_DISABLE_BMSK                                       0x1
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_LSB_TIC_DISABLE_SHFT                                       0x0

#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_ADDR                                            (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000431c)
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_OFFS                                            (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000431c)
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_RMSK                                            0xffffffff
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_ADDR, HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_RMSK)
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_SYS_APCCCFGEND_BMSK                             0x80000000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_SYS_APCCCFGEND_SHFT                                   0x1f
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_SYS_APCCCP15SDISABLE_BMSK                       0x40000000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_SYS_APCCCP15SDISABLE_SHFT                             0x1e
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_SYS_APCCCFGTE_BMSK                              0x20000000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_SYS_APCCCFGTE_SHFT                                    0x1d
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_SILVER_PLL_MAX_FREQ_LVAL_BMSK                   0x1fe00000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_SILVER_PLL_MAX_FREQ_LVAL_SHFT                         0x15
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_APPS_BOOT_FSM_FUSE_BMSK                           0x1c0000
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_APPS_BOOT_FSM_FUSE_SHFT                               0x12
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_GOLD_PLL_MAX_FREQ_LVAL_BMSK                        0x3fc00
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_GOLD_PLL_MAX_FREQ_LVAL_SHFT                            0xa
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_QC_A5X_ISDB_SECURE_DBGEN_DISABLE_BMSK                0x200
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_QC_A5X_ISDB_SECURE_DBGEN_DISABLE_SHFT                  0x9
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_QC_LPASS_SPIDEN_DISABLE_BMSK                         0x100
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_QC_LPASS_SPIDEN_DISABLE_SHFT                           0x8
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_QC_PIMEM_SPIDEN_DISABLE_BMSK                          0x80
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_QC_PIMEM_SPIDEN_DISABLE_SHFT                           0x7
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_QC_WCSS_SPIDEN_DISABLE_BMSK                           0x40
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_QC_WCSS_SPIDEN_DISABLE_SHFT                            0x6
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_QC_DAP_SPIDEN_DISABLE_BMSK                            0x20
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_QC_DAP_SPIDEN_DISABLE_SHFT                             0x5
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_QC_APPS_SPIDEN_DISABLE_BMSK                           0x10
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_QC_APPS_SPIDEN_DISABLE_SHFT                            0x4
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_QC_LPASS_SPNIDEN_DISABLE_BMSK                          0x8
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_QC_LPASS_SPNIDEN_DISABLE_SHFT                          0x3
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_QC_PIMEM_SPNIDEN_DISABLE_BMSK                          0x4
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_QC_PIMEM_SPNIDEN_DISABLE_SHFT                          0x2
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_QC_WCSS_SPNIDEN_DISABLE_BMSK                           0x2
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_QC_WCSS_SPNIDEN_DISABLE_SHFT                           0x1
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_QC_DAP_SPNIDEN_DISABLE_BMSK                            0x1
#define HWIO_QFPROM_CORR_CM_FEAT_CONFIG_ROW2_MSB_QC_DAP_SPNIDEN_DISABLE_SHFT                            0x0

#define HWIO_QFPROM_CORR_QC_SPARE_REGn_LSB_ADDR(n)                                               (SECURITY_CONTROL_CORE_REG_BASE      + 0x000042a0 + 0x8 * (n))
#define HWIO_QFPROM_CORR_QC_SPARE_REGn_LSB_OFFS(n)                                               (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000042a0 + 0x8 * (n))
#define HWIO_QFPROM_CORR_QC_SPARE_REGn_LSB_RMSK                                                  0xffffffff
#define HWIO_QFPROM_CORR_QC_SPARE_REGn_LSB_MAXn                                                          18
#define HWIO_QFPROM_CORR_QC_SPARE_REGn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_QC_SPARE_REGn_LSB_ADDR(n), HWIO_QFPROM_CORR_QC_SPARE_REGn_LSB_RMSK)
#define HWIO_QFPROM_CORR_QC_SPARE_REGn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_QC_SPARE_REGn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_QC_SPARE_REGn_LSB_QC_SPARE_BMSK                                         0xffffffff
#define HWIO_QFPROM_CORR_QC_SPARE_REGn_LSB_QC_SPARE_SHFT                                                0x0

#define HWIO_QFPROM_CORR_QC_SPARE_REGn_MSB_ADDR(n)                                               (SECURITY_CONTROL_CORE_REG_BASE      + 0x000042a4 + 0x8 * (n))
#define HWIO_QFPROM_CORR_QC_SPARE_REGn_MSB_OFFS(n)                                               (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000042a4 + 0x8 * (n))
#define HWIO_QFPROM_CORR_QC_SPARE_REGn_MSB_RMSK                                                    0xffffff
#define HWIO_QFPROM_CORR_QC_SPARE_REGn_MSB_MAXn                                                          18
#define HWIO_QFPROM_CORR_QC_SPARE_REGn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_QC_SPARE_REGn_MSB_ADDR(n), HWIO_QFPROM_CORR_QC_SPARE_REGn_MSB_RMSK)
#define HWIO_QFPROM_CORR_QC_SPARE_REGn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_QC_SPARE_REGn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_QC_SPARE_REGn_MSB_QC_SPARE_BMSK                                           0xffffff
#define HWIO_QFPROM_CORR_QC_SPARE_REGn_MSB_QC_SPARE_SHFT                                                0x0

#define HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROWn_LSB_ADDR(n)                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004338 + 0x8 * (n))
#define HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROWn_LSB_OFFS(n)                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004338 + 0x8 * (n))
#define HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROWn_LSB_RMSK                                        0xffffffff
#define HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROWn_LSB_MAXn                                                 1
#define HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROWn_LSB_ADDR(n), HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROWn_LSB_RMSK)
#define HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROWn_LSB_KEY_DATA0_BMSK                              0xffffffff
#define HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROWn_LSB_KEY_DATA0_SHFT                                     0x0

#define HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROWn_MSB_ADDR(n)                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000433c + 0x8 * (n))
#define HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROWn_MSB_OFFS(n)                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000433c + 0x8 * (n))
#define HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROWn_MSB_RMSK                                          0xffffff
#define HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROWn_MSB_MAXn                                                 1
#define HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROWn_MSB_ADDR(n), HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROWn_MSB_RMSK)
#define HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROWn_MSB_KEY_DATA1_BMSK                                0xffffff
#define HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROWn_MSB_KEY_DATA1_SHFT                                     0x0

#define HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROW2_LSB_ADDR                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004348)
#define HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROW2_LSB_OFFS                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004348)
#define HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROW2_LSB_RMSK                                        0xffffffff
#define HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROW2_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROW2_LSB_ADDR, HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROW2_LSB_RMSK)
#define HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROW2_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROW2_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROW2_LSB_RSVD0_BMSK                                  0xffff0000
#define HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROW2_LSB_RSVD0_SHFT                                        0x10
#define HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROW2_LSB_KEY_DATA0_BMSK                                  0xffff
#define HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROW2_LSB_KEY_DATA0_SHFT                                     0x0

#define HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROW2_MSB_ADDR                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000434c)
#define HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROW2_MSB_OFFS                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000434c)
#define HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROW2_MSB_RMSK                                          0xffffff
#define HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROW2_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROW2_MSB_ADDR, HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROW2_MSB_RMSK)
#define HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROW2_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROW2_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROW2_MSB_RSVD0_BMSK                                    0xffffff
#define HWIO_QFPROM_CORR_OEM_IMAGE_ENCR_KEY_ROW2_MSB_RSVD0_SHFT                                         0x0

#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_ADDR(n)                                           (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004350 + 0x8 * (n))
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_OFFS(n)                                           (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004350 + 0x8 * (n))
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_RMSK                                              0xffffffff
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_MAXn                                                       1
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_ADDR(n), HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_RMSK)
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_SEC_BOOT4_BMSK                                    0xff000000
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_SEC_BOOT4_SHFT                                          0x18
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_SEC_BOOT3_BMSK                                      0xff0000
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_SEC_BOOT3_SHFT                                          0x10
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_SEC_BOOT2_BMSK                                        0xff00
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_SEC_BOOT2_SHFT                                           0x8
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_SEC_BOOT1_BMSK                                          0xff
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_LSB_SEC_BOOT1_SHFT                                           0x0

#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_MSB_ADDR(n)                                           (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004354 + 0x8 * (n))
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_MSB_OFFS(n)                                           (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004354 + 0x8 * (n))
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_MSB_RMSK                                                0xffffff
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_MSB_MAXn                                                       1
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_MSB_ADDR(n), HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_MSB_RMSK)
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_MSB_SEC_BOOT7_BMSK                                      0xff0000
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_MSB_SEC_BOOT7_SHFT                                          0x10
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_MSB_SEC_BOOT6_BMSK                                        0xff00
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_MSB_SEC_BOOT6_SHFT                                           0x8
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_MSB_SEC_BOOT5_BMSK                                          0xff
#define HWIO_QFPROM_CORR_OEM_SEC_BOOT_ROWn_MSB_SEC_BOOT5_SHFT                                           0x0

#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_LSB_ADDR(n)                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004360 + 0x8 * (n))
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_LSB_OFFS(n)                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004360 + 0x8 * (n))
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_LSB_RMSK                                    0xffffffff
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_LSB_MAXn                                             3
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_LSB_ADDR(n), HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_LSB_RMSK)
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_LSB_KEY_DATA0_BMSK                          0xffffffff
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_LSB_KEY_DATA0_SHFT                                 0x0

#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_MSB_ADDR(n)                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004364 + 0x8 * (n))
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_MSB_OFFS(n)                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004364 + 0x8 * (n))
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_MSB_RMSK                                      0xffffff
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_MSB_MAXn                                             3
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_MSB_ADDR(n), HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_MSB_RMSK)
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_MSB_KEY_DATA1_BMSK                            0xffffff
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROWn_MSB_KEY_DATA1_SHFT                                 0x0

#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_LSB_ADDR                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004380)
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_LSB_OFFS                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004380)
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_LSB_RMSK                                    0xffffffff
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_LSB_ADDR, HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_LSB_RMSK)
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_LSB_KEY_DATA0_BMSK                          0xffffffff
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_LSB_KEY_DATA0_SHFT                                 0x0

#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_MSB_ADDR                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004384)
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_MSB_OFFS                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004384)
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_MSB_RMSK                                      0xffffff
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_MSB_ADDR, HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_MSB_RMSK)
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_MSB_RSVD0_BMSK                                0xffffff
#define HWIO_QFPROM_CORR_PRI_KEY_DERIVATION_KEY_ROW4_MSB_RSVD0_SHFT                                     0x0

#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_LSB_ADDR(n)                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004388 + 0x8 * (n))
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_LSB_OFFS(n)                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004388 + 0x8 * (n))
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_LSB_RMSK                                    0xffffffff
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_LSB_MAXn                                             3
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_LSB_ADDR(n), HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_LSB_RMSK)
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_LSB_KEY_DATA0_BMSK                          0xffffffff
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_LSB_KEY_DATA0_SHFT                                 0x0

#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_MSB_ADDR(n)                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000438c + 0x8 * (n))
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_MSB_OFFS(n)                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000438c + 0x8 * (n))
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_MSB_RMSK                                      0xffffff
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_MSB_MAXn                                             3
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_MSB_ADDR(n), HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_MSB_RMSK)
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_MSB_KEY_DATA1_BMSK                            0xffffff
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROWn_MSB_KEY_DATA1_SHFT                                 0x0

#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_LSB_ADDR                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x000043a8)
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_LSB_OFFS                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000043a8)
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_LSB_RMSK                                    0xffffffff
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_LSB_ADDR, HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_LSB_RMSK)
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_LSB_KEY_DATA0_BMSK                          0xffffffff
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_LSB_KEY_DATA0_SHFT                                 0x0

#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_MSB_ADDR                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x000043ac)
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_MSB_OFFS                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000043ac)
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_MSB_RMSK                                      0xffffff
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_MSB_ADDR, HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_MSB_RMSK)
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_MSB_RSVD0_BMSK                                0xffffff
#define HWIO_QFPROM_CORR_SEC_KEY_DERIVATION_KEY_ROW4_MSB_RSVD0_SHFT                                     0x0

#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_LSB_ADDR(n)                                              (SECURITY_CONTROL_CORE_REG_BASE      + 0x000043b0 + 0x8 * (n))
#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_LSB_OFFS(n)                                              (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000043b0 + 0x8 * (n))
#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_LSB_RMSK                                                 0xffffffff
#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_LSB_MAXn                                                         55
#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_ROM_PATCH_ROWn_LSB_ADDR(n), HWIO_QFPROM_CORR_ROM_PATCH_ROWn_LSB_RMSK)
#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_ROM_PATCH_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_LSB_PATCH_DATA_BMSK                                      0xffffffff
#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_LSB_PATCH_DATA_SHFT                                             0x0

#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_MSB_ADDR(n)                                              (SECURITY_CONTROL_CORE_REG_BASE      + 0x000043b4 + 0x8 * (n))
#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_MSB_OFFS(n)                                              (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000043b4 + 0x8 * (n))
#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_MSB_RMSK                                                   0xffffff
#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_MSB_MAXn                                                         55
#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_ROM_PATCH_ROWn_MSB_ADDR(n), HWIO_QFPROM_CORR_ROM_PATCH_ROWn_MSB_RMSK)
#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_ROM_PATCH_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_MSB_RSVD0_BMSK                                             0xfe0000
#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_MSB_RSVD0_SHFT                                                 0x11
#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_MSB_PATCH_ADDR_BMSK                                         0x1fffe
#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_MSB_PATCH_ADDR_SHFT                                             0x1
#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_MSB_PATCH_EN_BMSK                                               0x1
#define HWIO_QFPROM_CORR_ROM_PATCH_ROWn_MSB_PATCH_EN_SHFT                                               0x0

#define HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROWn_LSB_ADDR(n)                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004570 + 0x8 * (n))
#define HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROWn_LSB_OFFS(n)                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004570 + 0x8 * (n))
#define HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROWn_LSB_RMSK                                           0xffffffff
#define HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROWn_LSB_MAXn                                                    1
#define HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROWn_LSB_ADDR(n), HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROWn_LSB_RMSK)
#define HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROWn_LSB_KEY_DATA0_BMSK                                 0xffffffff
#define HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROWn_LSB_KEY_DATA0_SHFT                                        0x0

#define HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROWn_MSB_ADDR(n)                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004574 + 0x8 * (n))
#define HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROWn_MSB_OFFS(n)                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004574 + 0x8 * (n))
#define HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROWn_MSB_RMSK                                             0xffffff
#define HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROWn_MSB_MAXn                                                    1
#define HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROWn_MSB_ADDR(n), HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROWn_MSB_RMSK)
#define HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROWn_MSB_KEY_DATA1_BMSK                                   0xffffff
#define HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROWn_MSB_KEY_DATA1_SHFT                                        0x0

#define HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROW2_LSB_ADDR                                           (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004580)
#define HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROW2_LSB_OFFS                                           (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004580)
#define HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROW2_LSB_RMSK                                           0xffffffff
#define HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROW2_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROW2_LSB_ADDR, HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROW2_LSB_RMSK)
#define HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROW2_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROW2_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROW2_LSB_RSVD0_BMSK                                     0xffff0000
#define HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROW2_LSB_RSVD0_SHFT                                           0x10
#define HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROW2_LSB_KEY_DATA0_BMSK                                     0xffff
#define HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROW2_LSB_KEY_DATA0_SHFT                                        0x0

#define HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROW2_MSB_ADDR                                           (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004584)
#define HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROW2_MSB_OFFS                                           (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004584)
#define HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROW2_MSB_RMSK                                             0xffffff
#define HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROW2_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROW2_MSB_ADDR, HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROW2_MSB_RMSK)
#define HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROW2_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROW2_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROW2_MSB_RSVD0_BMSK                                       0xffffff
#define HWIO_QFPROM_CORR_IMAGE_ENCR_KEY1_ROW2_MSB_RSVD0_SHFT                                            0x0

#define HWIO_QFPROM_CORR_PK_HASH1_ROWn_LSB_ADDR(n)                                               (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004588 + 0x8 * (n))
#define HWIO_QFPROM_CORR_PK_HASH1_ROWn_LSB_OFFS(n)                                               (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004588 + 0x8 * (n))
#define HWIO_QFPROM_CORR_PK_HASH1_ROWn_LSB_RMSK                                                  0xffffffff
#define HWIO_QFPROM_CORR_PK_HASH1_ROWn_LSB_MAXn                                                           3
#define HWIO_QFPROM_CORR_PK_HASH1_ROWn_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_PK_HASH1_ROWn_LSB_ADDR(n), HWIO_QFPROM_CORR_PK_HASH1_ROWn_LSB_RMSK)
#define HWIO_QFPROM_CORR_PK_HASH1_ROWn_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_PK_HASH1_ROWn_LSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_PK_HASH1_ROWn_LSB_HASH_DATA0_BMSK                                       0xffffffff
#define HWIO_QFPROM_CORR_PK_HASH1_ROWn_LSB_HASH_DATA0_SHFT                                              0x0

#define HWIO_QFPROM_CORR_PK_HASH1_ROWn_MSB_ADDR(n)                                               (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000458c + 0x8 * (n))
#define HWIO_QFPROM_CORR_PK_HASH1_ROWn_MSB_OFFS(n)                                               (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000458c + 0x8 * (n))
#define HWIO_QFPROM_CORR_PK_HASH1_ROWn_MSB_RMSK                                                    0xffffff
#define HWIO_QFPROM_CORR_PK_HASH1_ROWn_MSB_MAXn                                                           3
#define HWIO_QFPROM_CORR_PK_HASH1_ROWn_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_PK_HASH1_ROWn_MSB_ADDR(n), HWIO_QFPROM_CORR_PK_HASH1_ROWn_MSB_RMSK)
#define HWIO_QFPROM_CORR_PK_HASH1_ROWn_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_PK_HASH1_ROWn_MSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_PK_HASH1_ROWn_MSB_HASH_DATA1_BMSK                                         0xffffff
#define HWIO_QFPROM_CORR_PK_HASH1_ROWn_MSB_HASH_DATA1_SHFT                                              0x0

#define HWIO_QFPROM_CORR_PK_HASH1_ROW4_LSB_ADDR                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x000045a8)
#define HWIO_QFPROM_CORR_PK_HASH1_ROW4_LSB_OFFS                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000045a8)
#define HWIO_QFPROM_CORR_PK_HASH1_ROW4_LSB_RMSK                                                  0xffffffff
#define HWIO_QFPROM_CORR_PK_HASH1_ROW4_LSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_PK_HASH1_ROW4_LSB_ADDR, HWIO_QFPROM_CORR_PK_HASH1_ROW4_LSB_RMSK)
#define HWIO_QFPROM_CORR_PK_HASH1_ROW4_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_PK_HASH1_ROW4_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_PK_HASH1_ROW4_LSB_HASH_DATA0_BMSK                                       0xffffffff
#define HWIO_QFPROM_CORR_PK_HASH1_ROW4_LSB_HASH_DATA0_SHFT                                              0x0

#define HWIO_QFPROM_CORR_PK_HASH1_ROW4_MSB_ADDR                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x000045ac)
#define HWIO_QFPROM_CORR_PK_HASH1_ROW4_MSB_OFFS                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000045ac)
#define HWIO_QFPROM_CORR_PK_HASH1_ROW4_MSB_RMSK                                                    0xffffff
#define HWIO_QFPROM_CORR_PK_HASH1_ROW4_MSB_IN          \
        in_dword_masked(HWIO_QFPROM_CORR_PK_HASH1_ROW4_MSB_ADDR, HWIO_QFPROM_CORR_PK_HASH1_ROW4_MSB_RMSK)
#define HWIO_QFPROM_CORR_PK_HASH1_ROW4_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_PK_HASH1_ROW4_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_PK_HASH1_ROW4_MSB_RSVD0_BMSK                                              0xfffffc
#define HWIO_QFPROM_CORR_PK_HASH1_ROW4_MSB_RSVD0_SHFT                                                   0x2
#define HWIO_QFPROM_CORR_PK_HASH1_ROW4_MSB_CURRENT_SW_ROT_MODEM_BMSK                                    0x2
#define HWIO_QFPROM_CORR_PK_HASH1_ROW4_MSB_CURRENT_SW_ROT_MODEM_SHFT                                    0x1
#define HWIO_QFPROM_CORR_PK_HASH1_ROW4_MSB_CURRENT_SW_ROT_APPS_BMSK                                     0x1
#define HWIO_QFPROM_CORR_PK_HASH1_ROW4_MSB_CURRENT_SW_ROT_APPS_SHFT                                     0x0

#define HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW0_LSB_ADDR(n)                                         (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004410 + 0x10 * (n))
#define HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW0_LSB_OFFS(n)                                         (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004410 + 0x10 * (n))
#define HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW0_LSB_RMSK                                            0xffffffff
#define HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW0_LSB_MAXn                                                    30
#define HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW0_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW0_LSB_ADDR(n), HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW0_LSB_RMSK)
#define HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW0_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW0_LSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW0_LSB_OEM_SPARE_BMSK                                  0xffffffff
#define HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW0_LSB_OEM_SPARE_SHFT                                         0x0

#define HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW0_MSB_ADDR(n)                                         (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004414 + 0x10 * (n))
#define HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW0_MSB_OFFS(n)                                         (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004414 + 0x10 * (n))
#define HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW0_MSB_RMSK                                            0xffffffff
#define HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW0_MSB_MAXn                                                    30
#define HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW0_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW0_MSB_ADDR(n), HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW0_MSB_RMSK)
#define HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW0_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW0_MSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW0_MSB_OEM_SPARE_BMSK                                  0xffffffff
#define HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW0_MSB_OEM_SPARE_SHFT                                         0x0

#define HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW1_LSB_ADDR(n)                                         (SECURITY_CONTROL_CORE_REG_BASE      + 0x00004418 + 0x10 * (n))
#define HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW1_LSB_OFFS(n)                                         (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00004418 + 0x10 * (n))
#define HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW1_LSB_RMSK                                            0xffffffff
#define HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW1_LSB_MAXn                                                    30
#define HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW1_LSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW1_LSB_ADDR(n), HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW1_LSB_RMSK)
#define HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW1_LSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW1_LSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW1_LSB_OEM_SPARE_BMSK                                  0xffffffff
#define HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW1_LSB_OEM_SPARE_SHFT                                         0x0

#define HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW1_MSB_ADDR(n)                                         (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000441c + 0x10 * (n))
#define HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW1_MSB_OFFS(n)                                         (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000441c + 0x10 * (n))
#define HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW1_MSB_RMSK                                            0xffffffff
#define HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW1_MSB_MAXn                                                    30
#define HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW1_MSB_INI(n)        \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW1_MSB_ADDR(n), HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW1_MSB_RMSK)
#define HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW1_MSB_INMI(n,mask)    \
        in_dword_masked(HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW1_MSB_ADDR(n), mask)
#define HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW1_MSB_OEM_SPARE_BMSK                                  0xffffffff
#define HWIO_QFPROM_CORR_OEM_SPARE_REGn_ROW1_MSB_OEM_SPARE_SHFT                                         0x0

#define HWIO_SEC_CTRL_HW_VERSION_ADDR                                                            (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006000)
#define HWIO_SEC_CTRL_HW_VERSION_OFFS                                                            (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006000)
#define HWIO_SEC_CTRL_HW_VERSION_RMSK                                                            0xffffffff
#define HWIO_SEC_CTRL_HW_VERSION_IN          \
        in_dword_masked(HWIO_SEC_CTRL_HW_VERSION_ADDR, HWIO_SEC_CTRL_HW_VERSION_RMSK)
#define HWIO_SEC_CTRL_HW_VERSION_INM(m)      \
        in_dword_masked(HWIO_SEC_CTRL_HW_VERSION_ADDR, m)
#define HWIO_SEC_CTRL_HW_VERSION_MAJOR_BMSK                                                      0xf0000000
#define HWIO_SEC_CTRL_HW_VERSION_MAJOR_SHFT                                                            0x1c
#define HWIO_SEC_CTRL_HW_VERSION_MINOR_BMSK                                                       0xfff0000
#define HWIO_SEC_CTRL_HW_VERSION_MINOR_SHFT                                                            0x10
#define HWIO_SEC_CTRL_HW_VERSION_STEP_BMSK                                                           0xffff
#define HWIO_SEC_CTRL_HW_VERSION_STEP_SHFT                                                              0x0

#define HWIO_FEATURE_CONFIG0_ADDR                                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006004)
#define HWIO_FEATURE_CONFIG0_OFFS                                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006004)
#define HWIO_FEATURE_CONFIG0_RMSK                                                                0xffffffff
#define HWIO_FEATURE_CONFIG0_IN          \
        in_dword_masked(HWIO_FEATURE_CONFIG0_ADDR, HWIO_FEATURE_CONFIG0_RMSK)
#define HWIO_FEATURE_CONFIG0_INM(m)      \
        in_dword_masked(HWIO_FEATURE_CONFIG0_ADDR, m)
#define HWIO_FEATURE_CONFIG0_UFS_SW_CONTROL_DISABLE_BMSK                                         0x80000000
#define HWIO_FEATURE_CONFIG0_UFS_SW_CONTROL_DISABLE_SHFT                                               0x1f
#define HWIO_FEATURE_CONFIG0_RSVD2_BMSK                                                          0x40000000
#define HWIO_FEATURE_CONFIG0_RSVD2_SHFT                                                                0x1e
#define HWIO_FEATURE_CONFIG0_RSVD1_BMSK                                                          0x20000000
#define HWIO_FEATURE_CONFIG0_RSVD1_SHFT                                                                0x1d
#define HWIO_FEATURE_CONFIG0_GFX3D_FREQ_LIMIT_VAL_BMSK                                           0x1fe00000
#define HWIO_FEATURE_CONFIG0_GFX3D_FREQ_LIMIT_VAL_SHFT                                                 0x15
#define HWIO_FEATURE_CONFIG0_MDSS_RESOLUTION_LIMIT_BMSK                                            0x180000
#define HWIO_FEATURE_CONFIG0_MDSS_RESOLUTION_LIMIT_SHFT                                                0x13
#define HWIO_FEATURE_CONFIG0_VENUS_HEVC_ENCODE_DISABLE_BMSK                                         0x40000
#define HWIO_FEATURE_CONFIG0_VENUS_HEVC_ENCODE_DISABLE_SHFT                                            0x12
#define HWIO_FEATURE_CONFIG0_VENUS_HEVC_DECODE_DISABLE_BMSK                                         0x20000
#define HWIO_FEATURE_CONFIG0_VENUS_HEVC_DECODE_DISABLE_SHFT                                            0x11
#define HWIO_FEATURE_CONFIG0_VENUS_4K_DISABLE_BMSK                                                  0x10000
#define HWIO_FEATURE_CONFIG0_VENUS_4K_DISABLE_SHFT                                                     0x10
#define HWIO_FEATURE_CONFIG0_VP8_DECODER_DISABLE_BMSK                                                0x8000
#define HWIO_FEATURE_CONFIG0_VP8_DECODER_DISABLE_SHFT                                                   0xf
#define HWIO_FEATURE_CONFIG0_VP8_ENCODER_DISABLE_BMSK                                                0x4000
#define HWIO_FEATURE_CONFIG0_VP8_ENCODER_DISABLE_SHFT                                                   0xe
#define HWIO_FEATURE_CONFIG0_HDMI_DP_DISABLE_BMSK                                                    0x2000
#define HWIO_FEATURE_CONFIG0_HDMI_DP_DISABLE_SHFT                                                       0xd
#define HWIO_FEATURE_CONFIG0_HDCP_DISABLE_BMSK                                                       0x1000
#define HWIO_FEATURE_CONFIG0_HDCP_DISABLE_SHFT                                                          0xc
#define HWIO_FEATURE_CONFIG0_MDP_APICAL_LTC_DISABLE_BMSK                                              0x800
#define HWIO_FEATURE_CONFIG0_MDP_APICAL_LTC_DISABLE_SHFT                                                0xb
#define HWIO_FEATURE_CONFIG0_HDCP_GLOBAL_KEY_SPLIT2_DISABLE_BMSK                                      0x400
#define HWIO_FEATURE_CONFIG0_HDCP_GLOBAL_KEY_SPLIT2_DISABLE_SHFT                                        0xa
#define HWIO_FEATURE_CONFIG0_DSI_1_DISABLE_BMSK                                                       0x200
#define HWIO_FEATURE_CONFIG0_DSI_1_DISABLE_SHFT                                                         0x9
#define HWIO_FEATURE_CONFIG0_USB2_DISABLE_BMSK                                                        0x100
#define HWIO_FEATURE_CONFIG0_USB2_DISABLE_SHFT                                                          0x8
#define HWIO_FEATURE_CONFIG0_RSVD0_BMSK                                                                0x80
#define HWIO_FEATURE_CONFIG0_RSVD0_SHFT                                                                 0x7
#define HWIO_FEATURE_CONFIG0_CSID_DPCM_14_DISABLE_BMSK                                                 0x40
#define HWIO_FEATURE_CONFIG0_CSID_DPCM_14_DISABLE_SHFT                                                  0x6
#define HWIO_FEATURE_CONFIG0_ISP_1_DISABLE_BMSK                                                        0x20
#define HWIO_FEATURE_CONFIG0_ISP_1_DISABLE_SHFT                                                         0x5
#define HWIO_FEATURE_CONFIG0_CSID_3_DISABLE_BMSK                                                       0x10
#define HWIO_FEATURE_CONFIG0_CSID_3_DISABLE_SHFT                                                        0x4
#define HWIO_FEATURE_CONFIG0_CSID_2_DISABLE_BMSK                                                        0x8
#define HWIO_FEATURE_CONFIG0_CSID_2_DISABLE_SHFT                                                        0x3
#define HWIO_FEATURE_CONFIG0_BOOT_ROM_PATCH_DISABLE_BMSK                                                0x7
#define HWIO_FEATURE_CONFIG0_BOOT_ROM_PATCH_DISABLE_SHFT                                                0x0

#define HWIO_FEATURE_CONFIG1_ADDR                                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006008)
#define HWIO_FEATURE_CONFIG1_OFFS                                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006008)
#define HWIO_FEATURE_CONFIG1_RMSK                                                                0xffffffff
#define HWIO_FEATURE_CONFIG1_IN          \
        in_dword_masked(HWIO_FEATURE_CONFIG1_ADDR, HWIO_FEATURE_CONFIG1_RMSK)
#define HWIO_FEATURE_CONFIG1_INM(m)      \
        in_dword_masked(HWIO_FEATURE_CONFIG1_ADDR, m)
#define HWIO_FEATURE_CONFIG1_ICE_FORCE_HW_KEY1_BMSK                                              0x80000000
#define HWIO_FEATURE_CONFIG1_ICE_FORCE_HW_KEY1_SHFT                                                    0x1f
#define HWIO_FEATURE_CONFIG1_ICE_FORCE_HW_KEY0_BMSK                                              0x40000000
#define HWIO_FEATURE_CONFIG1_ICE_FORCE_HW_KEY0_SHFT                                                    0x1e
#define HWIO_FEATURE_CONFIG1_ICE_DISABLE_BMSK                                                    0x20000000
#define HWIO_FEATURE_CONFIG1_ICE_DISABLE_SHFT                                                          0x1d
#define HWIO_FEATURE_CONFIG1_RSVD2_BMSK                                                          0x10000000
#define HWIO_FEATURE_CONFIG1_RSVD2_SHFT                                                                0x1c
#define HWIO_FEATURE_CONFIG1_RSVD1_BMSK                                                           0x8000000
#define HWIO_FEATURE_CONFIG1_RSVD1_SHFT                                                                0x1b
#define HWIO_FEATURE_CONFIG1_LPASS_SENSOR_DISABLE_BMSK                                            0x4000000
#define HWIO_FEATURE_CONFIG1_LPASS_SENSOR_DISABLE_SHFT                                                 0x1a
#define HWIO_FEATURE_CONFIG1_LPASS_ISLAND_MODE_Q6_CLK_DISABLE_BMSK                                0x2000000
#define HWIO_FEATURE_CONFIG1_LPASS_ISLAND_MODE_Q6_CLK_DISABLE_SHFT                                     0x19
#define HWIO_FEATURE_CONFIG1_LPASS_SW_ISLAND_MODE_DISABLE_BMSK                                    0x1000000
#define HWIO_FEATURE_CONFIG1_LPASS_SW_ISLAND_MODE_DISABLE_SHFT                                         0x18
#define HWIO_FEATURE_CONFIG1_LPASS_EFUSE_TESTBUS_READ_DISABLE_BMSK                                 0x800000
#define HWIO_FEATURE_CONFIG1_LPASS_EFUSE_TESTBUS_READ_DISABLE_SHFT                                     0x17
#define HWIO_FEATURE_CONFIG1_APS_RESET_DISABLE_BMSK                                                0x400000
#define HWIO_FEATURE_CONFIG1_APS_RESET_DISABLE_SHFT                                                    0x16
#define HWIO_FEATURE_CONFIG1_HVX_DISABLE_BMSK                                                      0x200000
#define HWIO_FEATURE_CONFIG1_HVX_DISABLE_SHFT                                                          0x15
#define HWIO_FEATURE_CONFIG1_APB2JTAG_DISABLE_BMSK                                                 0x100000
#define HWIO_FEATURE_CONFIG1_APB2JTAG_DISABLE_SHFT                                                     0x14
#define HWIO_FEATURE_CONFIG1_RSVD6_BMSK                                                             0x80000
#define HWIO_FEATURE_CONFIG1_RSVD6_SHFT                                                                0x13
#define HWIO_FEATURE_CONFIG1_STACKED_MEMORY_ID_BMSK                                                 0x7c000
#define HWIO_FEATURE_CONFIG1_STACKED_MEMORY_ID_SHFT                                                     0xe
#define HWIO_FEATURE_CONFIG1_PRNG_TESTMODE_DISABLE_BMSK                                              0x2000
#define HWIO_FEATURE_CONFIG1_PRNG_TESTMODE_DISABLE_SHFT                                                 0xd
#define HWIO_FEATURE_CONFIG1_CDSP_DISABLE_BMSK                                                       0x1000
#define HWIO_FEATURE_CONFIG1_CDSP_DISABLE_SHFT                                                          0xc
#define HWIO_FEATURE_CONFIG1_MOCHA_PART_BMSK                                                          0x800
#define HWIO_FEATURE_CONFIG1_MOCHA_PART_SHFT                                                            0xb
#define HWIO_FEATURE_CONFIG1_RSVD5_BMSK                                                               0x400
#define HWIO_FEATURE_CONFIG1_RSVD5_SHFT                                                                 0xa
#define HWIO_FEATURE_CONFIG1_RSVD4_BMSK                                                               0x200
#define HWIO_FEATURE_CONFIG1_RSVD4_SHFT                                                                 0x9
#define HWIO_FEATURE_CONFIG1_RSVD3_BMSK                                                               0x1e0
#define HWIO_FEATURE_CONFIG1_RSVD3_SHFT                                                                 0x5
#define HWIO_FEATURE_CONFIG1_CM_FEAT_CONFIG_DISABLE_BMSK                                               0x10
#define HWIO_FEATURE_CONFIG1_CM_FEAT_CONFIG_DISABLE_SHFT                                                0x4
#define HWIO_FEATURE_CONFIG1_VFE_RESOLUTION_LIMIT_BMSK                                                  0x8
#define HWIO_FEATURE_CONFIG1_VFE_RESOLUTION_LIMIT_SHFT                                                  0x3
#define HWIO_FEATURE_CONFIG1_GLD_PDX_FIFO_NIU_BMSK                                                      0x4
#define HWIO_FEATURE_CONFIG1_GLD_PDX_FIFO_NIU_SHFT                                                      0x2
#define HWIO_FEATURE_CONFIG1_RSVD0_BMSK                                                                 0x2
#define HWIO_FEATURE_CONFIG1_RSVD0_SHFT                                                                 0x1
#define HWIO_FEATURE_CONFIG1_VP9_DECODER_DISABLE_BMSK                                                   0x1
#define HWIO_FEATURE_CONFIG1_VP9_DECODER_DISABLE_SHFT                                                   0x0

#define HWIO_FEATURE_CONFIG2_ADDR                                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000600c)
#define HWIO_FEATURE_CONFIG2_OFFS                                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000600c)
#define HWIO_FEATURE_CONFIG2_RMSK                                                                0xffffffff
#define HWIO_FEATURE_CONFIG2_IN          \
        in_dword_masked(HWIO_FEATURE_CONFIG2_ADDR, HWIO_FEATURE_CONFIG2_RMSK)
#define HWIO_FEATURE_CONFIG2_INM(m)      \
        in_dword_masked(HWIO_FEATURE_CONFIG2_ADDR, m)
#define HWIO_FEATURE_CONFIG2_MDSP_FW_DISABLE_BMSK                                                0xfff00000
#define HWIO_FEATURE_CONFIG2_MDSP_FW_DISABLE_SHFT                                                      0x14
#define HWIO_FEATURE_CONFIG2_RSVD0_BMSK                                                             0x80000
#define HWIO_FEATURE_CONFIG2_RSVD0_SHFT                                                                0x13
#define HWIO_FEATURE_CONFIG2_NAV_DISABLE_BMSK                                                       0x40000
#define HWIO_FEATURE_CONFIG2_NAV_DISABLE_SHFT                                                          0x12
#define HWIO_FEATURE_CONFIG2_SYS_APCCCFGNMFI_BMSK                                                   0x20000
#define HWIO_FEATURE_CONFIG2_SYS_APCCCFGNMFI_SHFT                                                      0x11
#define HWIO_FEATURE_CONFIG2_GLD_PDX_FIFO_ACE1_BMSK                                                 0x10000
#define HWIO_FEATURE_CONFIG2_GLD_PDX_FIFO_ACE1_SHFT                                                    0x10
#define HWIO_FEATURE_CONFIG2_GLD_PDX_FIFO_ACE0_BMSK                                                  0x8000
#define HWIO_FEATURE_CONFIG2_GLD_PDX_FIFO_ACE0_SHFT                                                     0xf
#define HWIO_FEATURE_CONFIG2_MODEM_FEATURE_DISABLE_SPARE_BMSK                                        0x7fe0
#define HWIO_FEATURE_CONFIG2_MODEM_FEATURE_DISABLE_SPARE_SHFT                                           0x5
#define HWIO_FEATURE_CONFIG2_MODEM_FEATURE_DISABLE_SLICE_BMSK                                          0x1f
#define HWIO_FEATURE_CONFIG2_MODEM_FEATURE_DISABLE_SLICE_SHFT                                           0x0

#define HWIO_FEATURE_CONFIG3_ADDR                                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006010)
#define HWIO_FEATURE_CONFIG3_OFFS                                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006010)
#define HWIO_FEATURE_CONFIG3_RMSK                                                                0xffffffff
#define HWIO_FEATURE_CONFIG3_IN          \
        in_dword_masked(HWIO_FEATURE_CONFIG3_ADDR, HWIO_FEATURE_CONFIG3_RMSK)
#define HWIO_FEATURE_CONFIG3_INM(m)      \
        in_dword_masked(HWIO_FEATURE_CONFIG3_ADDR, m)
#define HWIO_FEATURE_CONFIG3_SYS_APCX_SYSBARDISABLE_BMSK                                         0x80000000
#define HWIO_FEATURE_CONFIG3_SYS_APCX_SYSBARDISABLE_SHFT                                               0x1f
#define HWIO_FEATURE_CONFIG3_SYS_APCSCFGAPMBOOTONMX_BMSK                                         0x60000000
#define HWIO_FEATURE_CONFIG3_SYS_APCSCFGAPMBOOTONMX_SHFT                                               0x1d
#define HWIO_FEATURE_CONFIG3_SYS_APCCCFGCPUPRESENT_N_BMSK                                        0x1fe00000
#define HWIO_FEATURE_CONFIG3_SYS_APCCCFGCPUPRESENT_N_SHFT                                              0x15
#define HWIO_FEATURE_CONFIG3_APPS_ACG_DISABLE_BMSK                                                 0x100000
#define HWIO_FEATURE_CONFIG3_APPS_ACG_DISABLE_SHFT                                                     0x14
#define HWIO_FEATURE_CONFIG3_RSVD1_BMSK                                                             0xf0000
#define HWIO_FEATURE_CONFIG3_RSVD1_SHFT                                                                0x10
#define HWIO_FEATURE_CONFIG3_MODEM_VU_DISABLE_BMSK                                                   0xffff
#define HWIO_FEATURE_CONFIG3_MODEM_VU_DISABLE_SHFT                                                      0x0

#define HWIO_FEATURE_CONFIG4_ADDR                                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006014)
#define HWIO_FEATURE_CONFIG4_OFFS                                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006014)
#define HWIO_FEATURE_CONFIG4_RMSK                                                                0xffffffff
#define HWIO_FEATURE_CONFIG4_IN          \
        in_dword_masked(HWIO_FEATURE_CONFIG4_ADDR, HWIO_FEATURE_CONFIG4_RMSK)
#define HWIO_FEATURE_CONFIG4_INM(m)      \
        in_dword_masked(HWIO_FEATURE_CONFIG4_ADDR, m)
#define HWIO_FEATURE_CONFIG4_QC_APPS_SPNIDEN_DISABLE_BMSK                                        0x80000000
#define HWIO_FEATURE_CONFIG4_QC_APPS_SPNIDEN_DISABLE_SHFT                                              0x1f
#define HWIO_FEATURE_CONFIG4_QC_MSS_NIDEN_DISABLE_BMSK                                           0x40000000
#define HWIO_FEATURE_CONFIG4_QC_MSS_NIDEN_DISABLE_SHFT                                                 0x1e
#define HWIO_FEATURE_CONFIG4_QC_LPASS_SENSOR_NIDEN_DISABLE_BMSK                                  0x20000000
#define HWIO_FEATURE_CONFIG4_QC_LPASS_SENSOR_NIDEN_DISABLE_SHFT                                        0x1d
#define HWIO_FEATURE_CONFIG4_QC_PIMEM_NIDEN_DISABLE_BMSK                                         0x10000000
#define HWIO_FEATURE_CONFIG4_QC_PIMEM_NIDEN_DISABLE_SHFT                                               0x1c
#define HWIO_FEATURE_CONFIG4_QC_RPM_NIDEN_DISABLE_BMSK                                            0x8000000
#define HWIO_FEATURE_CONFIG4_QC_RPM_NIDEN_DISABLE_SHFT                                                 0x1b
#define HWIO_FEATURE_CONFIG4_QC_WCSS_NIDEN_DISABLE_BMSK                                           0x4000000
#define HWIO_FEATURE_CONFIG4_QC_WCSS_NIDEN_DISABLE_SHFT                                                0x1a
#define HWIO_FEATURE_CONFIG4_QC_LPASS_NIDEN_DISABLE_BMSK                                          0x2000000
#define HWIO_FEATURE_CONFIG4_QC_LPASS_NIDEN_DISABLE_SHFT                                               0x19
#define HWIO_FEATURE_CONFIG4_QC_DAP_NIDEN_DISABLE_BMSK                                            0x1000000
#define HWIO_FEATURE_CONFIG4_QC_DAP_NIDEN_DISABLE_SHFT                                                 0x18
#define HWIO_FEATURE_CONFIG4_QC_APPS_NIDEN_DISABLE_BMSK                                            0x800000
#define HWIO_FEATURE_CONFIG4_QC_APPS_NIDEN_DISABLE_SHFT                                                0x17
#define HWIO_FEATURE_CONFIG4_QC_MSS_DBGEN_DISABLE_BMSK                                             0x400000
#define HWIO_FEATURE_CONFIG4_QC_MSS_DBGEN_DISABLE_SHFT                                                 0x16
#define HWIO_FEATURE_CONFIG4_QC_A5X_ISDB_DBGEN_DISABLE_BMSK                                        0x200000
#define HWIO_FEATURE_CONFIG4_QC_A5X_ISDB_DBGEN_DISABLE_SHFT                                            0x15
#define HWIO_FEATURE_CONFIG4_QC_VENUS_0_DBGEN_DISABLE_BMSK                                         0x100000
#define HWIO_FEATURE_CONFIG4_QC_VENUS_0_DBGEN_DISABLE_SHFT                                             0x14
#define HWIO_FEATURE_CONFIG4_TURING_EFUSE_TESTBUS_READ_DISABLE_BMSK                                 0x80000
#define HWIO_FEATURE_CONFIG4_TURING_EFUSE_TESTBUS_READ_DISABLE_SHFT                                    0x13
#define HWIO_FEATURE_CONFIG4_QC_LPASS_SENSOR_DBGEN_DISABLE_BMSK                                     0x40000
#define HWIO_FEATURE_CONFIG4_QC_LPASS_SENSOR_DBGEN_DISABLE_SHFT                                        0x12
#define HWIO_FEATURE_CONFIG4_QC_PIMEM_DBGEN_DISABLE_BMSK                                            0x20000
#define HWIO_FEATURE_CONFIG4_QC_PIMEM_DBGEN_DISABLE_SHFT                                               0x11
#define HWIO_FEATURE_CONFIG4_QC_RPM_DBGEN_DISABLE_BMSK                                              0x10000
#define HWIO_FEATURE_CONFIG4_QC_RPM_DBGEN_DISABLE_SHFT                                                 0x10
#define HWIO_FEATURE_CONFIG4_QC_WCSS_DBGEN_DISABLE_BMSK                                              0x8000
#define HWIO_FEATURE_CONFIG4_QC_WCSS_DBGEN_DISABLE_SHFT                                                 0xf
#define HWIO_FEATURE_CONFIG4_QC_LPASS_Q6_DBGEN_DISABLE_BMSK                                          0x4000
#define HWIO_FEATURE_CONFIG4_QC_LPASS_Q6_DBGEN_DISABLE_SHFT                                             0xe
#define HWIO_FEATURE_CONFIG4_QC_DAP_DBGEN_DISABLE_BMSK                                               0x2000
#define HWIO_FEATURE_CONFIG4_QC_DAP_DBGEN_DISABLE_SHFT                                                  0xd
#define HWIO_FEATURE_CONFIG4_QC_APPS_DBGEN_DISABLE_BMSK                                              0x1000
#define HWIO_FEATURE_CONFIG4_QC_APPS_DBGEN_DISABLE_SHFT                                                 0xc
#define HWIO_FEATURE_CONFIG4_QC_DAP_DEVICEEN_DISABLE_BMSK                                             0x800
#define HWIO_FEATURE_CONFIG4_QC_DAP_DEVICEEN_DISABLE_SHFT                                               0xb
#define HWIO_FEATURE_CONFIG4_QC_RPM_DAPEN_DISABLE_BMSK                                                0x400
#define HWIO_FEATURE_CONFIG4_QC_RPM_DAPEN_DISABLE_SHFT                                                  0xa
#define HWIO_FEATURE_CONFIG4_DSI_0_DISABLE_BMSK                                                       0x200
#define HWIO_FEATURE_CONFIG4_DSI_0_DISABLE_SHFT                                                         0x9
#define HWIO_FEATURE_CONFIG4_QC_DEBUG_BUS_DISABLE_BMSK                                                0x100
#define HWIO_FEATURE_CONFIG4_QC_DEBUG_BUS_DISABLE_SHFT                                                  0x8
#define HWIO_FEATURE_CONFIG4_QC_DCC_DEBUG_DISABLE_BMSK                                                 0x80
#define HWIO_FEATURE_CONFIG4_QC_DCC_DEBUG_DISABLE_SHFT                                                  0x7
#define HWIO_FEATURE_CONFIG4_QC_APPS_APB_DFD_DISABLE_BMSK                                              0x40
#define HWIO_FEATURE_CONFIG4_QC_APPS_APB_DFD_DISABLE_SHFT                                               0x6
#define HWIO_FEATURE_CONFIG4_QC_GPMU_NIDEN_DISABLE_BMSK                                                0x20
#define HWIO_FEATURE_CONFIG4_QC_GPMU_NIDEN_DISABLE_SHFT                                                 0x5
#define HWIO_FEATURE_CONFIG4_QC_GPMU_DBGEN_DISABLE_BMSK                                                0x10
#define HWIO_FEATURE_CONFIG4_QC_GPMU_DBGEN_DISABLE_SHFT                                                 0x4
#define HWIO_FEATURE_CONFIG4_QC_GPMU_DAPEN_DISABLE_BMSK                                                 0x8
#define HWIO_FEATURE_CONFIG4_QC_GPMU_DAPEN_DISABLE_SHFT                                                 0x3
#define HWIO_FEATURE_CONFIG4_QDI_SPMI_DISABLE_BMSK                                                      0x4
#define HWIO_FEATURE_CONFIG4_QDI_SPMI_DISABLE_SHFT                                                      0x2
#define HWIO_FEATURE_CONFIG4_SM_BIST_DISABLE_BMSK                                                       0x2
#define HWIO_FEATURE_CONFIG4_SM_BIST_DISABLE_SHFT                                                       0x1
#define HWIO_FEATURE_CONFIG4_TIC_DISABLE_BMSK                                                           0x1
#define HWIO_FEATURE_CONFIG4_TIC_DISABLE_SHFT                                                           0x0

#define HWIO_FEATURE_CONFIG5_ADDR                                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006018)
#define HWIO_FEATURE_CONFIG5_OFFS                                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006018)
#define HWIO_FEATURE_CONFIG5_RMSK                                                                0xffffffff
#define HWIO_FEATURE_CONFIG5_IN          \
        in_dword_masked(HWIO_FEATURE_CONFIG5_ADDR, HWIO_FEATURE_CONFIG5_RMSK)
#define HWIO_FEATURE_CONFIG5_INM(m)      \
        in_dword_masked(HWIO_FEATURE_CONFIG5_ADDR, m)
#define HWIO_FEATURE_CONFIG5_SYS_APCCCFGEND_BMSK                                                 0x80000000
#define HWIO_FEATURE_CONFIG5_SYS_APCCCFGEND_SHFT                                                       0x1f
#define HWIO_FEATURE_CONFIG5_SYS_APCCCP15SDISABLE_BMSK                                           0x40000000
#define HWIO_FEATURE_CONFIG5_SYS_APCCCP15SDISABLE_SHFT                                                 0x1e
#define HWIO_FEATURE_CONFIG5_SYS_APCCCFGTE_BMSK                                                  0x20000000
#define HWIO_FEATURE_CONFIG5_SYS_APCCCFGTE_SHFT                                                        0x1d
#define HWIO_FEATURE_CONFIG5_SILVER_PLL_MAX_FREQ_LVAL_BMSK                                       0x1fe00000
#define HWIO_FEATURE_CONFIG5_SILVER_PLL_MAX_FREQ_LVAL_SHFT                                             0x15
#define HWIO_FEATURE_CONFIG5_APPS_BOOT_FSM_FUSE_BMSK                                               0x1c0000
#define HWIO_FEATURE_CONFIG5_APPS_BOOT_FSM_FUSE_SHFT                                                   0x12
#define HWIO_FEATURE_CONFIG5_GOLD_PLL_MAX_FREQ_LVAL_BMSK                                            0x3fc00
#define HWIO_FEATURE_CONFIG5_GOLD_PLL_MAX_FREQ_LVAL_SHFT                                                0xa
#define HWIO_FEATURE_CONFIG5_QC_A5X_ISDB_SECURE_DBGEN_DISABLE_BMSK                                    0x200
#define HWIO_FEATURE_CONFIG5_QC_A5X_ISDB_SECURE_DBGEN_DISABLE_SHFT                                      0x9
#define HWIO_FEATURE_CONFIG5_QC_LPASS_SPIDEN_DISABLE_BMSK                                             0x100
#define HWIO_FEATURE_CONFIG5_QC_LPASS_SPIDEN_DISABLE_SHFT                                               0x8
#define HWIO_FEATURE_CONFIG5_QC_PIMEM_SPIDEN_DISABLE_BMSK                                              0x80
#define HWIO_FEATURE_CONFIG5_QC_PIMEM_SPIDEN_DISABLE_SHFT                                               0x7
#define HWIO_FEATURE_CONFIG5_QC_WCSS_SPIDEN_DISABLE_BMSK                                               0x40
#define HWIO_FEATURE_CONFIG5_QC_WCSS_SPIDEN_DISABLE_SHFT                                                0x6
#define HWIO_FEATURE_CONFIG5_QC_DAP_SPIDEN_DISABLE_BMSK                                                0x20
#define HWIO_FEATURE_CONFIG5_QC_DAP_SPIDEN_DISABLE_SHFT                                                 0x5
#define HWIO_FEATURE_CONFIG5_QC_APPS_SPIDEN_DISABLE_BMSK                                               0x10
#define HWIO_FEATURE_CONFIG5_QC_APPS_SPIDEN_DISABLE_SHFT                                                0x4
#define HWIO_FEATURE_CONFIG5_QC_LPASS_SPNIDEN_DISABLE_BMSK                                              0x8
#define HWIO_FEATURE_CONFIG5_QC_LPASS_SPNIDEN_DISABLE_SHFT                                              0x3
#define HWIO_FEATURE_CONFIG5_QC_PIMEM_SPNIDEN_DISABLE_BMSK                                              0x4
#define HWIO_FEATURE_CONFIG5_QC_PIMEM_SPNIDEN_DISABLE_SHFT                                              0x2
#define HWIO_FEATURE_CONFIG5_QC_WCSS_SPNIDEN_DISABLE_BMSK                                               0x2
#define HWIO_FEATURE_CONFIG5_QC_WCSS_SPNIDEN_DISABLE_SHFT                                               0x1
#define HWIO_FEATURE_CONFIG5_QC_DAP_SPNIDEN_DISABLE_BMSK                                                0x1
#define HWIO_FEATURE_CONFIG5_QC_DAP_SPNIDEN_DISABLE_SHFT                                                0x0

#define HWIO_FEATURE_CONFIG6_ADDR                                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000601c)
#define HWIO_FEATURE_CONFIG6_OFFS                                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000601c)
#define HWIO_FEATURE_CONFIG6_RMSK                                                                0xffffffff
#define HWIO_FEATURE_CONFIG6_IN          \
        in_dword_masked(HWIO_FEATURE_CONFIG6_ADDR, HWIO_FEATURE_CONFIG6_RMSK)
#define HWIO_FEATURE_CONFIG6_INM(m)      \
        in_dword_masked(HWIO_FEATURE_CONFIG6_ADDR, m)
#define HWIO_FEATURE_CONFIG6_TAP_GEN_SPARE_INSTR_DISABLE_13_0_BMSK                               0xfffc0000
#define HWIO_FEATURE_CONFIG6_TAP_GEN_SPARE_INSTR_DISABLE_13_0_SHFT                                     0x12
#define HWIO_FEATURE_CONFIG6_TAP_INSTR_DISABLE_BMSK                                                 0x3ffff
#define HWIO_FEATURE_CONFIG6_TAP_INSTR_DISABLE_SHFT                                                     0x0

#define HWIO_FEATURE_CONFIG7_ADDR                                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006020)
#define HWIO_FEATURE_CONFIG7_OFFS                                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006020)
#define HWIO_FEATURE_CONFIG7_RMSK                                                                0xffffffff
#define HWIO_FEATURE_CONFIG7_IN          \
        in_dword_masked(HWIO_FEATURE_CONFIG7_ADDR, HWIO_FEATURE_CONFIG7_RMSK)
#define HWIO_FEATURE_CONFIG7_INM(m)      \
        in_dword_masked(HWIO_FEATURE_CONFIG7_ADDR, m)
#define HWIO_FEATURE_CONFIG7_SEC_TAP_ACCESS_DISABLE_BMSK                                         0xfffc0000
#define HWIO_FEATURE_CONFIG7_SEC_TAP_ACCESS_DISABLE_SHFT                                               0x12
#define HWIO_FEATURE_CONFIG7_TAP_GEN_SPARE_INSTR_DISABLE_31_14_BMSK                                 0x3ffff
#define HWIO_FEATURE_CONFIG7_TAP_GEN_SPARE_INSTR_DISABLE_31_14_SHFT                                     0x0

#define HWIO_FEATURE_CONFIG8_ADDR                                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006024)
#define HWIO_FEATURE_CONFIG8_OFFS                                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006024)
#define HWIO_FEATURE_CONFIG8_RMSK                                                                0xffffffff
#define HWIO_FEATURE_CONFIG8_IN          \
        in_dword_masked(HWIO_FEATURE_CONFIG8_ADDR, HWIO_FEATURE_CONFIG8_RMSK)
#define HWIO_FEATURE_CONFIG8_INM(m)      \
        in_dword_masked(HWIO_FEATURE_CONFIG8_ADDR, m)
#define HWIO_FEATURE_CONFIG8_MODEM_PBL_PATCH_VERSION_BMSK                                        0xfe000000
#define HWIO_FEATURE_CONFIG8_MODEM_PBL_PATCH_VERSION_SHFT                                              0x19
#define HWIO_FEATURE_CONFIG8_APPS_PBL_PATCH_VERSION_BMSK                                          0x1fc0000
#define HWIO_FEATURE_CONFIG8_APPS_PBL_PATCH_VERSION_SHFT                                               0x12
#define HWIO_FEATURE_CONFIG8_APPS_PBL_BOOT_SPEED_BMSK                                               0x30000
#define HWIO_FEATURE_CONFIG8_APPS_PBL_BOOT_SPEED_SHFT                                                  0x10
#define HWIO_FEATURE_CONFIG8_MODEM_PBL_BOOT_BMSK                                                     0x8000
#define HWIO_FEATURE_CONFIG8_MODEM_PBL_BOOT_SHFT                                                        0xf
#define HWIO_FEATURE_CONFIG8_RSVD1_BMSK                                                              0x4000
#define HWIO_FEATURE_CONFIG8_RSVD1_SHFT                                                                 0xe
#define HWIO_FEATURE_CONFIG8_APPS_BOOT_FROM_ROM_BMSK                                                 0x2000
#define HWIO_FEATURE_CONFIG8_APPS_BOOT_FROM_ROM_SHFT                                                    0xd
#define HWIO_FEATURE_CONFIG8_RSVD0_BMSK                                                              0x1000
#define HWIO_FEATURE_CONFIG8_RSVD0_SHFT                                                                 0xc
#define HWIO_FEATURE_CONFIG8_MODEM_BOOT_FROM_ROM_BMSK                                                 0x800
#define HWIO_FEATURE_CONFIG8_MODEM_BOOT_FROM_ROM_SHFT                                                   0xb
#define HWIO_FEATURE_CONFIG8_MSA_ENA_BMSK                                                             0x400
#define HWIO_FEATURE_CONFIG8_MSA_ENA_SHFT                                                               0xa
#define HWIO_FEATURE_CONFIG8_FORCE_MSA_AUTH_EN_BMSK                                                   0x200
#define HWIO_FEATURE_CONFIG8_FORCE_MSA_AUTH_EN_SHFT                                                     0x9
#define HWIO_FEATURE_CONFIG8_ARM_CE_DISABLE_USAGE_BMSK                                                0x100
#define HWIO_FEATURE_CONFIG8_ARM_CE_DISABLE_USAGE_SHFT                                                  0x8
#define HWIO_FEATURE_CONFIG8_BOOT_ROM_CFG_BMSK                                                         0xff
#define HWIO_FEATURE_CONFIG8_BOOT_ROM_CFG_SHFT                                                          0x0

#define HWIO_FEATURE_CONFIG9_ADDR                                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006028)
#define HWIO_FEATURE_CONFIG9_OFFS                                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006028)
#define HWIO_FEATURE_CONFIG9_RMSK                                                                0xffffffff
#define HWIO_FEATURE_CONFIG9_IN          \
        in_dword_masked(HWIO_FEATURE_CONFIG9_ADDR, HWIO_FEATURE_CONFIG9_RMSK)
#define HWIO_FEATURE_CONFIG9_INM(m)      \
        in_dword_masked(HWIO_FEATURE_CONFIG9_ADDR, m)
#define HWIO_FEATURE_CONFIG9_APPS_BOOT_TRIGGER_DISABLE_BMSK                                      0x80000000
#define HWIO_FEATURE_CONFIG9_APPS_BOOT_TRIGGER_DISABLE_SHFT                                            0x1f
#define HWIO_FEATURE_CONFIG9_PBL_QSEE_BOOT_FLOW_DISABLE_BMSK                                     0x40000000
#define HWIO_FEATURE_CONFIG9_PBL_QSEE_BOOT_FLOW_DISABLE_SHFT                                           0x1e
#define HWIO_FEATURE_CONFIG9_XBL_SEC_AUTH_DISABLE_BMSK                                           0x20000000
#define HWIO_FEATURE_CONFIG9_XBL_SEC_AUTH_DISABLE_SHFT                                                 0x1d
#define HWIO_FEATURE_CONFIG9_MSM_PKG_TYPE_BMSK                                                   0x10000000
#define HWIO_FEATURE_CONFIG9_MSM_PKG_TYPE_SHFT                                                         0x1c
#define HWIO_FEATURE_CONFIG9_RSVD3_BMSK                                                           0xffc0000
#define HWIO_FEATURE_CONFIG9_RSVD3_SHFT                                                                0x12
#define HWIO_FEATURE_CONFIG9_FOUNDRY_ID_BMSK                                                        0x3c000
#define HWIO_FEATURE_CONFIG9_FOUNDRY_ID_SHFT                                                            0xe
#define HWIO_FEATURE_CONFIG9_PLL_CFG_BMSK                                                            0x3ff0
#define HWIO_FEATURE_CONFIG9_PLL_CFG_SHFT                                                               0x4
#define HWIO_FEATURE_CONFIG9_APPS_PBL_PLL_CTRL_BMSK                                                     0xf
#define HWIO_FEATURE_CONFIG9_APPS_PBL_PLL_CTRL_SHFT                                                     0x0

#define HWIO_OEM_CONFIG0_ADDR                                                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006040)
#define HWIO_OEM_CONFIG0_OFFS                                                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006040)
#define HWIO_OEM_CONFIG0_RMSK                                                                    0xffffffff
#define HWIO_OEM_CONFIG0_IN          \
        in_dword_masked(HWIO_OEM_CONFIG0_ADDR, HWIO_OEM_CONFIG0_RMSK)
#define HWIO_OEM_CONFIG0_INM(m)      \
        in_dword_masked(HWIO_OEM_CONFIG0_ADDR, m)
#define HWIO_OEM_CONFIG0_DCC_DEBUG_DISABLE_BMSK                                                  0x80000000
#define HWIO_OEM_CONFIG0_DCC_DEBUG_DISABLE_SHFT                                                        0x1f
#define HWIO_OEM_CONFIG0_APPS_APB_DFD_DISABLE_BMSK                                               0x40000000
#define HWIO_OEM_CONFIG0_APPS_APB_DFD_DISABLE_SHFT                                                     0x1e
#define HWIO_OEM_CONFIG0_ALL_DEBUG_DISABLE_BMSK                                                  0x20000000
#define HWIO_OEM_CONFIG0_ALL_DEBUG_DISABLE_SHFT                                                        0x1d
#define HWIO_OEM_CONFIG0_DEBUG_POLICY_DISABLE_BMSK                                               0x10000000
#define HWIO_OEM_CONFIG0_DEBUG_POLICY_DISABLE_SHFT                                                     0x1c
#define HWIO_OEM_CONFIG0_RSVD2_BMSK                                                               0xe000000
#define HWIO_OEM_CONFIG0_RSVD2_SHFT                                                                    0x19
#define HWIO_OEM_CONFIG0_MSS_HASH_INTEGRITY_CHECK_DISABLE_BMSK                                    0x1000000
#define HWIO_OEM_CONFIG0_MSS_HASH_INTEGRITY_CHECK_DISABLE_SHFT                                         0x18
#define HWIO_OEM_CONFIG0_APPS_HASH_INTEGRITY_CHECK_DISABLE_BMSK                                    0x800000
#define HWIO_OEM_CONFIG0_APPS_HASH_INTEGRITY_CHECK_DISABLE_SHFT                                        0x17
#define HWIO_OEM_CONFIG0_USB_SS_DISABLE_BMSK                                                       0x400000
#define HWIO_OEM_CONFIG0_USB_SS_DISABLE_SHFT                                                           0x16
#define HWIO_OEM_CONFIG0_SW_ROT_USE_SERIAL_NUM_BMSK                                                0x200000
#define HWIO_OEM_CONFIG0_SW_ROT_USE_SERIAL_NUM_SHFT                                                    0x15
#define HWIO_OEM_CONFIG0_DISABLE_ROT_TRANSFER_BMSK                                                 0x100000
#define HWIO_OEM_CONFIG0_DISABLE_ROT_TRANSFER_SHFT                                                     0x14
#define HWIO_OEM_CONFIG0_IMAGE_ENCRYPTION_ENABLE_BMSK                                               0x80000
#define HWIO_OEM_CONFIG0_IMAGE_ENCRYPTION_ENABLE_SHFT                                                  0x13
#define HWIO_OEM_CONFIG0_RSVD1_BMSK                                                                 0x60000
#define HWIO_OEM_CONFIG0_RSVD1_SHFT                                                                    0x11
#define HWIO_OEM_CONFIG0_PBL_USB_TYPE_C_DISABLE_BMSK                                                0x10000
#define HWIO_OEM_CONFIG0_PBL_USB_TYPE_C_DISABLE_SHFT                                                   0x10
#define HWIO_OEM_CONFIG0_PBL_LOG_DISABLE_BMSK                                                        0x8000
#define HWIO_OEM_CONFIG0_PBL_LOG_DISABLE_SHFT                                                           0xf
#define HWIO_OEM_CONFIG0_WDOG_EN_BMSK                                                                0x4000
#define HWIO_OEM_CONFIG0_WDOG_EN_SHFT                                                                   0xe
#define HWIO_OEM_CONFIG0_SPDM_SECURE_MODE_BMSK                                                       0x2000
#define HWIO_OEM_CONFIG0_SPDM_SECURE_MODE_SHFT                                                          0xd
#define HWIO_OEM_CONFIG0_SW_FUSE_PROG_DISABLE_BMSK                                                   0x1000
#define HWIO_OEM_CONFIG0_SW_FUSE_PROG_DISABLE_SHFT                                                      0xc
#define HWIO_OEM_CONFIG0_RSVD0_BMSK                                                                   0xc00
#define HWIO_OEM_CONFIG0_RSVD0_SHFT                                                                     0xa
#define HWIO_OEM_CONFIG0_FAST_BOOT_BMSK                                                               0x3e0
#define HWIO_OEM_CONFIG0_FAST_BOOT_SHFT                                                                 0x5
#define HWIO_OEM_CONFIG0_SDCC_MCLK_BOOT_FREQ_BMSK                                                      0x10
#define HWIO_OEM_CONFIG0_SDCC_MCLK_BOOT_FREQ_SHFT                                                       0x4
#define HWIO_OEM_CONFIG0_FORCE_USB_BOOT_DISABLE_BMSK                                                    0x8
#define HWIO_OEM_CONFIG0_FORCE_USB_BOOT_DISABLE_SHFT                                                    0x3
#define HWIO_OEM_CONFIG0_FORCE_DLOAD_DISABLE_BMSK                                                       0x4
#define HWIO_OEM_CONFIG0_FORCE_DLOAD_DISABLE_SHFT                                                       0x2
#define HWIO_OEM_CONFIG0_ENUM_TIMEOUT_BMSK                                                              0x2
#define HWIO_OEM_CONFIG0_ENUM_TIMEOUT_SHFT                                                              0x1
#define HWIO_OEM_CONFIG0_E_DLOAD_DISABLE_BMSK                                                           0x1
#define HWIO_OEM_CONFIG0_E_DLOAD_DISABLE_SHFT                                                           0x0

#define HWIO_OEM_CONFIG1_ADDR                                                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006044)
#define HWIO_OEM_CONFIG1_OFFS                                                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006044)
#define HWIO_OEM_CONFIG1_RMSK                                                                    0xffffffff
#define HWIO_OEM_CONFIG1_IN          \
        in_dword_masked(HWIO_OEM_CONFIG1_ADDR, HWIO_OEM_CONFIG1_RMSK)
#define HWIO_OEM_CONFIG1_INM(m)      \
        in_dword_masked(HWIO_OEM_CONFIG1_ADDR, m)
#define HWIO_OEM_CONFIG1_PIMEM_SPIDEN_DISABLE_BMSK                                               0x80000000
#define HWIO_OEM_CONFIG1_PIMEM_SPIDEN_DISABLE_SHFT                                                     0x1f
#define HWIO_OEM_CONFIG1_WCSS_SPIDEN_DISABLE_BMSK                                                0x40000000
#define HWIO_OEM_CONFIG1_WCSS_SPIDEN_DISABLE_SHFT                                                      0x1e
#define HWIO_OEM_CONFIG1_DAP_SPIDEN_DISABLE_BMSK                                                 0x20000000
#define HWIO_OEM_CONFIG1_DAP_SPIDEN_DISABLE_SHFT                                                       0x1d
#define HWIO_OEM_CONFIG1_APPS_SPIDEN_DISABLE_BMSK                                                0x10000000
#define HWIO_OEM_CONFIG1_APPS_SPIDEN_DISABLE_SHFT                                                      0x1c
#define HWIO_OEM_CONFIG1_LPASS_SPNIDEN_DISABLE_BMSK                                               0x8000000
#define HWIO_OEM_CONFIG1_LPASS_SPNIDEN_DISABLE_SHFT                                                    0x1b
#define HWIO_OEM_CONFIG1_PIMEM_SPNIDEN_DISABLE_BMSK                                               0x4000000
#define HWIO_OEM_CONFIG1_PIMEM_SPNIDEN_DISABLE_SHFT                                                    0x1a
#define HWIO_OEM_CONFIG1_WCSS_SPNIDEN_DISABLE_BMSK                                                0x2000000
#define HWIO_OEM_CONFIG1_WCSS_SPNIDEN_DISABLE_SHFT                                                     0x19
#define HWIO_OEM_CONFIG1_DAP_SPNIDEN_DISABLE_BMSK                                                 0x1000000
#define HWIO_OEM_CONFIG1_DAP_SPNIDEN_DISABLE_SHFT                                                      0x18
#define HWIO_OEM_CONFIG1_APPS_SPNIDEN_DISABLE_BMSK                                                 0x800000
#define HWIO_OEM_CONFIG1_APPS_SPNIDEN_DISABLE_SHFT                                                     0x17
#define HWIO_OEM_CONFIG1_MSS_NIDEN_DISABLE_BMSK                                                    0x400000
#define HWIO_OEM_CONFIG1_MSS_NIDEN_DISABLE_SHFT                                                        0x16
#define HWIO_OEM_CONFIG1_LPASS_SENSOR_NIDEN_DISABLE_BMSK                                           0x200000
#define HWIO_OEM_CONFIG1_LPASS_SENSOR_NIDEN_DISABLE_SHFT                                               0x15
#define HWIO_OEM_CONFIG1_PIMEM_NIDEN_DISABLE_BMSK                                                  0x100000
#define HWIO_OEM_CONFIG1_PIMEM_NIDEN_DISABLE_SHFT                                                      0x14
#define HWIO_OEM_CONFIG1_RPM_NIDEN_DISABLE_BMSK                                                     0x80000
#define HWIO_OEM_CONFIG1_RPM_NIDEN_DISABLE_SHFT                                                        0x13
#define HWIO_OEM_CONFIG1_WCSS_NIDEN_DISABLE_BMSK                                                    0x40000
#define HWIO_OEM_CONFIG1_WCSS_NIDEN_DISABLE_SHFT                                                       0x12
#define HWIO_OEM_CONFIG1_LPASS_NIDEN_DISABLE_BMSK                                                   0x20000
#define HWIO_OEM_CONFIG1_LPASS_NIDEN_DISABLE_SHFT                                                      0x11
#define HWIO_OEM_CONFIG1_DAP_NIDEN_DISABLE_BMSK                                                     0x10000
#define HWIO_OEM_CONFIG1_DAP_NIDEN_DISABLE_SHFT                                                        0x10
#define HWIO_OEM_CONFIG1_APPS_NIDEN_DISABLE_BMSK                                                     0x8000
#define HWIO_OEM_CONFIG1_APPS_NIDEN_DISABLE_SHFT                                                        0xf
#define HWIO_OEM_CONFIG1_MSS_DBGEN_DISABLE_BMSK                                                      0x4000
#define HWIO_OEM_CONFIG1_MSS_DBGEN_DISABLE_SHFT                                                         0xe
#define HWIO_OEM_CONFIG1_A5X_ISDB_DBGEN_DISABLE_BMSK                                                 0x2000
#define HWIO_OEM_CONFIG1_A5X_ISDB_DBGEN_DISABLE_SHFT                                                    0xd
#define HWIO_OEM_CONFIG1_VENUS_0_DBGEN_DISABLE_BMSK                                                  0x1000
#define HWIO_OEM_CONFIG1_VENUS_0_DBGEN_DISABLE_SHFT                                                     0xc
#define HWIO_OEM_CONFIG1_RSVD1_BMSK                                                                   0x800
#define HWIO_OEM_CONFIG1_RSVD1_SHFT                                                                     0xb
#define HWIO_OEM_CONFIG1_LPASS_SENSOR_DBGEN_DISABLE_BMSK                                              0x400
#define HWIO_OEM_CONFIG1_LPASS_SENSOR_DBGEN_DISABLE_SHFT                                                0xa
#define HWIO_OEM_CONFIG1_PIMEM_DBGEN_DISABLE_BMSK                                                     0x200
#define HWIO_OEM_CONFIG1_PIMEM_DBGEN_DISABLE_SHFT                                                       0x9
#define HWIO_OEM_CONFIG1_RPM_DBGEN_DISABLE_BMSK                                                       0x100
#define HWIO_OEM_CONFIG1_RPM_DBGEN_DISABLE_SHFT                                                         0x8
#define HWIO_OEM_CONFIG1_WCSS_DBGEN_DISABLE_BMSK                                                       0x80
#define HWIO_OEM_CONFIG1_WCSS_DBGEN_DISABLE_SHFT                                                        0x7
#define HWIO_OEM_CONFIG1_LPASS_Q6_DBGEN_DISABLE_BMSK                                                   0x40
#define HWIO_OEM_CONFIG1_LPASS_Q6_DBGEN_DISABLE_SHFT                                                    0x6
#define HWIO_OEM_CONFIG1_DAP_DBGEN_DISABLE_BMSK                                                        0x20
#define HWIO_OEM_CONFIG1_DAP_DBGEN_DISABLE_SHFT                                                         0x5
#define HWIO_OEM_CONFIG1_APPS_DBGEN_DISABLE_BMSK                                                       0x10
#define HWIO_OEM_CONFIG1_APPS_DBGEN_DISABLE_SHFT                                                        0x4
#define HWIO_OEM_CONFIG1_DAP_DEVICEEN_DISABLE_BMSK                                                      0x8
#define HWIO_OEM_CONFIG1_DAP_DEVICEEN_DISABLE_SHFT                                                      0x3
#define HWIO_OEM_CONFIG1_RPM_DAPEN_DISABLE_BMSK                                                         0x4
#define HWIO_OEM_CONFIG1_RPM_DAPEN_DISABLE_SHFT                                                         0x2
#define HWIO_OEM_CONFIG1_RSVD0_BMSK                                                                     0x2
#define HWIO_OEM_CONFIG1_RSVD0_SHFT                                                                     0x1
#define HWIO_OEM_CONFIG1_DEBUG_BUS_DISABLE_BMSK                                                         0x1
#define HWIO_OEM_CONFIG1_DEBUG_BUS_DISABLE_SHFT                                                         0x0

#define HWIO_OEM_CONFIG2_ADDR                                                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006048)
#define HWIO_OEM_CONFIG2_OFFS                                                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006048)
#define HWIO_OEM_CONFIG2_RMSK                                                                    0xffffffff
#define HWIO_OEM_CONFIG2_IN          \
        in_dword_masked(HWIO_OEM_CONFIG2_ADDR, HWIO_OEM_CONFIG2_RMSK)
#define HWIO_OEM_CONFIG2_INM(m)      \
        in_dword_masked(HWIO_OEM_CONFIG2_ADDR, m)
#define HWIO_OEM_CONFIG2_RSVD1_BMSK                                                              0xffff8000
#define HWIO_OEM_CONFIG2_RSVD1_SHFT                                                                     0xf
#define HWIO_OEM_CONFIG2_OEM_SPARE_REG30_SECURE_BMSK                                                 0x4000
#define HWIO_OEM_CONFIG2_OEM_SPARE_REG30_SECURE_SHFT                                                    0xe
#define HWIO_OEM_CONFIG2_OEM_SPARE_REG29_SECURE_BMSK                                                 0x2000
#define HWIO_OEM_CONFIG2_OEM_SPARE_REG29_SECURE_SHFT                                                    0xd
#define HWIO_OEM_CONFIG2_OEM_SPARE_REG28_SECURE_BMSK                                                 0x1000
#define HWIO_OEM_CONFIG2_OEM_SPARE_REG28_SECURE_SHFT                                                    0xc
#define HWIO_OEM_CONFIG2_OEM_SPARE_REG27_SECURE_BMSK                                                  0x800
#define HWIO_OEM_CONFIG2_OEM_SPARE_REG27_SECURE_SHFT                                                    0xb
#define HWIO_OEM_CONFIG2_OEM_SPARE_REG26_SECURE_BMSK                                                  0x400
#define HWIO_OEM_CONFIG2_OEM_SPARE_REG26_SECURE_SHFT                                                    0xa
#define HWIO_OEM_CONFIG2_RSVD0_BMSK                                                                   0x3fe
#define HWIO_OEM_CONFIG2_RSVD0_SHFT                                                                     0x1
#define HWIO_OEM_CONFIG2_LPASS_SPIDEN_DISABLE_BMSK                                                      0x1
#define HWIO_OEM_CONFIG2_LPASS_SPIDEN_DISABLE_SHFT                                                      0x0

#define HWIO_OEM_CONFIG3_ADDR                                                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000604c)
#define HWIO_OEM_CONFIG3_OFFS                                                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000604c)
#define HWIO_OEM_CONFIG3_RMSK                                                                    0xffffffff
#define HWIO_OEM_CONFIG3_IN          \
        in_dword_masked(HWIO_OEM_CONFIG3_ADDR, HWIO_OEM_CONFIG3_RMSK)
#define HWIO_OEM_CONFIG3_INM(m)      \
        in_dword_masked(HWIO_OEM_CONFIG3_ADDR, m)
#define HWIO_OEM_CONFIG3_OEM_PRODUCT_ID_BMSK                                                     0xffff0000
#define HWIO_OEM_CONFIG3_OEM_PRODUCT_ID_SHFT                                                           0x10
#define HWIO_OEM_CONFIG3_OEM_HW_ID_BMSK                                                              0xffff
#define HWIO_OEM_CONFIG3_OEM_HW_ID_SHFT                                                                 0x0

#define HWIO_OEM_CONFIG4_ADDR                                                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006050)
#define HWIO_OEM_CONFIG4_OFFS                                                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006050)
#define HWIO_OEM_CONFIG4_RMSK                                                                    0xffffffff
#define HWIO_OEM_CONFIG4_IN          \
        in_dword_masked(HWIO_OEM_CONFIG4_ADDR, HWIO_OEM_CONFIG4_RMSK)
#define HWIO_OEM_CONFIG4_INM(m)      \
        in_dword_masked(HWIO_OEM_CONFIG4_ADDR, m)
#define HWIO_OEM_CONFIG4_PERIPH_VID_BMSK                                                         0xffff0000
#define HWIO_OEM_CONFIG4_PERIPH_VID_SHFT                                                               0x10
#define HWIO_OEM_CONFIG4_PERIPH_PID_BMSK                                                             0xffff
#define HWIO_OEM_CONFIG4_PERIPH_PID_SHFT                                                                0x0

#define HWIO_OEM_CONFIG5_ADDR                                                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006054)
#define HWIO_OEM_CONFIG5_OFFS                                                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006054)
#define HWIO_OEM_CONFIG5_RMSK                                                                    0xffffffff
#define HWIO_OEM_CONFIG5_IN          \
        in_dword_masked(HWIO_OEM_CONFIG5_ADDR, HWIO_OEM_CONFIG5_RMSK)
#define HWIO_OEM_CONFIG5_INM(m)      \
        in_dword_masked(HWIO_OEM_CONFIG5_ADDR, m)
#define HWIO_OEM_CONFIG5_RSVD0_BMSK                                                              0xffffff00
#define HWIO_OEM_CONFIG5_RSVD0_SHFT                                                                     0x8
#define HWIO_OEM_CONFIG5_ANTI_ROLLBACK_FEATURE_EN_BMSK                                                 0xff
#define HWIO_OEM_CONFIG5_ANTI_ROLLBACK_FEATURE_EN_SHFT                                                  0x0

#define HWIO_BOOT_CONFIG_ADDR                                                                    (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006070)
#define HWIO_BOOT_CONFIG_OFFS                                                                    (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006070)
#define HWIO_BOOT_CONFIG_RMSK                                                                         0x7ff
#define HWIO_BOOT_CONFIG_IN          \
        in_dword_masked(HWIO_BOOT_CONFIG_ADDR, HWIO_BOOT_CONFIG_RMSK)
#define HWIO_BOOT_CONFIG_INM(m)      \
        in_dword_masked(HWIO_BOOT_CONFIG_ADDR, m)
#define HWIO_BOOT_CONFIG_FORCE_MSA_AUTH_EN_BMSK                                                       0x400
#define HWIO_BOOT_CONFIG_FORCE_MSA_AUTH_EN_SHFT                                                         0xa
#define HWIO_BOOT_CONFIG_APPS_PBL_BOOT_SPEED_BMSK                                                     0x300
#define HWIO_BOOT_CONFIG_APPS_PBL_BOOT_SPEED_SHFT                                                       0x8
#define HWIO_BOOT_CONFIG_MODEM_BOOT_FROM_ROM_BMSK                                                      0x80
#define HWIO_BOOT_CONFIG_MODEM_BOOT_FROM_ROM_SHFT                                                       0x7
#define HWIO_BOOT_CONFIG_APPS_BOOT_FROM_ROM_BMSK                                                       0x40
#define HWIO_BOOT_CONFIG_APPS_BOOT_FROM_ROM_SHFT                                                        0x6
#define HWIO_BOOT_CONFIG_FAST_BOOT_BMSK                                                                0x3e
#define HWIO_BOOT_CONFIG_FAST_BOOT_SHFT                                                                 0x1
#define HWIO_BOOT_CONFIG_WDOG_EN_BMSK                                                                   0x1
#define HWIO_BOOT_CONFIG_WDOG_EN_SHFT                                                                   0x0

#define HWIO_SECURE_BOOTn_ADDR(n)                                                                (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006078 + 0x4 * (n))
#define HWIO_SECURE_BOOTn_OFFS(n)                                                                (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006078 + 0x4 * (n))
#define HWIO_SECURE_BOOTn_RMSK                                                                        0x1ff
#define HWIO_SECURE_BOOTn_MAXn                                                                           14
#define HWIO_SECURE_BOOTn_INI(n)        \
        in_dword_masked(HWIO_SECURE_BOOTn_ADDR(n), HWIO_SECURE_BOOTn_RMSK)
#define HWIO_SECURE_BOOTn_INMI(n,mask)    \
        in_dword_masked(HWIO_SECURE_BOOTn_ADDR(n), mask)
#define HWIO_SECURE_BOOTn_FUSE_SRC_BMSK                                                               0x100
#define HWIO_SECURE_BOOTn_FUSE_SRC_SHFT                                                                 0x8
#define HWIO_SECURE_BOOTn_RSVD_7_BMSK                                                                  0x80
#define HWIO_SECURE_BOOTn_RSVD_7_SHFT                                                                   0x7
#define HWIO_SECURE_BOOTn_USE_SERIAL_NUM_BMSK                                                          0x40
#define HWIO_SECURE_BOOTn_USE_SERIAL_NUM_SHFT                                                           0x6
#define HWIO_SECURE_BOOTn_AUTH_EN_BMSK                                                                 0x20
#define HWIO_SECURE_BOOTn_AUTH_EN_SHFT                                                                  0x5
#define HWIO_SECURE_BOOTn_PK_HASH_IN_FUSE_BMSK                                                         0x10
#define HWIO_SECURE_BOOTn_PK_HASH_IN_FUSE_SHFT                                                          0x4
#define HWIO_SECURE_BOOTn_ROM_PK_HASH_INDEX_BMSK                                                        0xf
#define HWIO_SECURE_BOOTn_ROM_PK_HASH_INDEX_SHFT                                                        0x0

#define HWIO_OVERRIDE_0_ADDR                                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x000060c0)
#define HWIO_OVERRIDE_0_OFFS                                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000060c0)
#define HWIO_OVERRIDE_0_RMSK                                                                     0xffffffff
#define HWIO_OVERRIDE_0_IN          \
        in_dword_masked(HWIO_OVERRIDE_0_ADDR, HWIO_OVERRIDE_0_RMSK)
#define HWIO_OVERRIDE_0_INM(m)      \
        in_dword_masked(HWIO_OVERRIDE_0_ADDR, m)
#define HWIO_OVERRIDE_0_OUT(v)      \
        out_dword(HWIO_OVERRIDE_0_ADDR,v)
#define HWIO_OVERRIDE_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_OVERRIDE_0_ADDR,m,v,HWIO_OVERRIDE_0_IN)
#define HWIO_OVERRIDE_0_RSVD_31_3_BMSK                                                           0xfffffff8
#define HWIO_OVERRIDE_0_RSVD_31_3_SHFT                                                                  0x3
#define HWIO_OVERRIDE_0_TX_DISABLE_BMSK                                                                 0x4
#define HWIO_OVERRIDE_0_TX_DISABLE_SHFT                                                                 0x2
#define HWIO_OVERRIDE_0_RSVD_1_0_BMSK                                                                   0x3
#define HWIO_OVERRIDE_0_RSVD_1_0_SHFT                                                                   0x0

#define HWIO_OVERRIDE_1_ADDR                                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x000060c4)
#define HWIO_OVERRIDE_1_OFFS                                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000060c4)
#define HWIO_OVERRIDE_1_RMSK                                                                     0xffffffff
#define HWIO_OVERRIDE_1_IN          \
        in_dword_masked(HWIO_OVERRIDE_1_ADDR, HWIO_OVERRIDE_1_RMSK)
#define HWIO_OVERRIDE_1_INM(m)      \
        in_dword_masked(HWIO_OVERRIDE_1_ADDR, m)
#define HWIO_OVERRIDE_1_OUT(v)      \
        out_dword(HWIO_OVERRIDE_1_ADDR,v)
#define HWIO_OVERRIDE_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_OVERRIDE_1_ADDR,m,v,HWIO_OVERRIDE_1_IN)
#define HWIO_OVERRIDE_1_RSVD_31_7_BMSK                                                           0xffffff80
#define HWIO_OVERRIDE_1_RSVD_31_7_SHFT                                                                  0x7
#define HWIO_OVERRIDE_1_OVRID_VSENSE_DEBUG_DISABLE_BMSK                                                0x40
#define HWIO_OVERRIDE_1_OVRID_VSENSE_DEBUG_DISABLE_SHFT                                                 0x6
#define HWIO_OVERRIDE_1_OVRID_DAP_DEVICEEN_DISABLE_BMSK                                                0x20
#define HWIO_OVERRIDE_1_OVRID_DAP_DEVICEEN_DISABLE_SHFT                                                 0x5
#define HWIO_OVERRIDE_1_OVRID_RPM_DAPEN_DISABLE_BMSK                                                   0x10
#define HWIO_OVERRIDE_1_OVRID_RPM_DAPEN_DISABLE_SHFT                                                    0x4
#define HWIO_OVERRIDE_1_RSVD0_BMSK                                                                      0x8
#define HWIO_OVERRIDE_1_RSVD0_SHFT                                                                      0x3
#define HWIO_OVERRIDE_1_OVRID_DEBUG_BUS_DISABLE_BMSK                                                    0x4
#define HWIO_OVERRIDE_1_OVRID_DEBUG_BUS_DISABLE_SHFT                                                    0x2
#define HWIO_OVERRIDE_1_OVRID_DCC_DEBUG_DISABLE_BMSK                                                    0x2
#define HWIO_OVERRIDE_1_OVRID_DCC_DEBUG_DISABLE_SHFT                                                    0x1
#define HWIO_OVERRIDE_1_OVRID_APPS_APB_DFD_DISABLE_BMSK                                                 0x1
#define HWIO_OVERRIDE_1_OVRID_APPS_APB_DFD_DISABLE_SHFT                                                 0x0

#define HWIO_OVERRIDE_2_ADDR                                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x000060c8)
#define HWIO_OVERRIDE_2_OFFS                                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000060c8)
#define HWIO_OVERRIDE_2_RMSK                                                                     0xffffffff
#define HWIO_OVERRIDE_2_IN          \
        in_dword_masked(HWIO_OVERRIDE_2_ADDR, HWIO_OVERRIDE_2_RMSK)
#define HWIO_OVERRIDE_2_INM(m)      \
        in_dword_masked(HWIO_OVERRIDE_2_ADDR, m)
#define HWIO_OVERRIDE_2_OUT(v)      \
        out_dword(HWIO_OVERRIDE_2_ADDR,v)
#define HWIO_OVERRIDE_2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_OVERRIDE_2_ADDR,m,v,HWIO_OVERRIDE_2_IN)
#define HWIO_OVERRIDE_2_RSVD_31_17_BMSK                                                          0xfffe0000
#define HWIO_OVERRIDE_2_RSVD_31_17_SHFT                                                                0x11
#define HWIO_OVERRIDE_2_OVRID_LPASS_SENSOR_NIDEN_DISABLE_BMSK                                       0x10000
#define HWIO_OVERRIDE_2_OVRID_LPASS_SENSOR_NIDEN_DISABLE_SHFT                                          0x10
#define HWIO_OVERRIDE_2_OVRID_PIMEM_NIDEN_DISABLE_BMSK                                               0x8000
#define HWIO_OVERRIDE_2_OVRID_PIMEM_NIDEN_DISABLE_SHFT                                                  0xf
#define HWIO_OVERRIDE_2_OVRID_RPM_NIDEN_DISABLE_BMSK                                                 0x4000
#define HWIO_OVERRIDE_2_OVRID_RPM_NIDEN_DISABLE_SHFT                                                    0xe
#define HWIO_OVERRIDE_2_OVRID_WCSS_NIDEN_DISABLE_BMSK                                                0x2000
#define HWIO_OVERRIDE_2_OVRID_WCSS_NIDEN_DISABLE_SHFT                                                   0xd
#define HWIO_OVERRIDE_2_OVRID_LPASS_NIDEN_DISABLE_BMSK                                               0x1000
#define HWIO_OVERRIDE_2_OVRID_LPASS_NIDEN_DISABLE_SHFT                                                  0xc
#define HWIO_OVERRIDE_2_OVRID_DAP_NIDEN_DISABLE_BMSK                                                  0x800
#define HWIO_OVERRIDE_2_OVRID_DAP_NIDEN_DISABLE_SHFT                                                    0xb
#define HWIO_OVERRIDE_2_OVRID_APPS_NIDEN_DISABLE_BMSK                                                 0x400
#define HWIO_OVERRIDE_2_OVRID_APPS_NIDEN_DISABLE_SHFT                                                   0xa
#define HWIO_OVERRIDE_2_OVRID_A5X_ISDB_DBGEN_DISABLE_BMSK                                             0x200
#define HWIO_OVERRIDE_2_OVRID_A5X_ISDB_DBGEN_DISABLE_SHFT                                               0x9
#define HWIO_OVERRIDE_2_OVRID_VENUS_0_DBGEN_DISABLE_BMSK                                              0x100
#define HWIO_OVERRIDE_2_OVRID_VENUS_0_DBGEN_DISABLE_SHFT                                                0x8
#define HWIO_OVERRIDE_2_RSVD1_BMSK                                                                     0x80
#define HWIO_OVERRIDE_2_RSVD1_SHFT                                                                      0x7
#define HWIO_OVERRIDE_2_OVRID_LPASS_SENSOR_DBGEN_DISABLE_BMSK                                          0x40
#define HWIO_OVERRIDE_2_OVRID_LPASS_SENSOR_DBGEN_DISABLE_SHFT                                           0x6
#define HWIO_OVERRIDE_2_OVRID_PIMEM_DBGEN_DISABLE_BMSK                                                 0x20
#define HWIO_OVERRIDE_2_OVRID_PIMEM_DBGEN_DISABLE_SHFT                                                  0x5
#define HWIO_OVERRIDE_2_OVRID_RPM_DBGEN_DISABLE_BMSK                                                   0x10
#define HWIO_OVERRIDE_2_OVRID_RPM_DBGEN_DISABLE_SHFT                                                    0x4
#define HWIO_OVERRIDE_2_OVRID_WCSS_DBGEN_DISABLE_BMSK                                                   0x8
#define HWIO_OVERRIDE_2_OVRID_WCSS_DBGEN_DISABLE_SHFT                                                   0x3
#define HWIO_OVERRIDE_2_OVRID_LPASS_Q6_DBGEN_DISABLE_BMSK                                               0x4
#define HWIO_OVERRIDE_2_OVRID_LPASS_Q6_DBGEN_DISABLE_SHFT                                               0x2
#define HWIO_OVERRIDE_2_OVRID_DAP_DBGEN_DISABLE_BMSK                                                    0x2
#define HWIO_OVERRIDE_2_OVRID_DAP_DBGEN_DISABLE_SHFT                                                    0x1
#define HWIO_OVERRIDE_2_OVRID_APPS_DBGEN_DISABLE_BMSK                                                   0x1
#define HWIO_OVERRIDE_2_OVRID_APPS_DBGEN_DISABLE_SHFT                                                   0x0

#define HWIO_OVERRIDE_3_ADDR                                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x000060cc)
#define HWIO_OVERRIDE_3_OFFS                                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000060cc)
#define HWIO_OVERRIDE_3_RMSK                                                                     0xffffffff
#define HWIO_OVERRIDE_3_IN          \
        in_dword_masked(HWIO_OVERRIDE_3_ADDR, HWIO_OVERRIDE_3_RMSK)
#define HWIO_OVERRIDE_3_INM(m)      \
        in_dword_masked(HWIO_OVERRIDE_3_ADDR, m)
#define HWIO_OVERRIDE_3_OUT(v)      \
        out_dword(HWIO_OVERRIDE_3_ADDR,v)
#define HWIO_OVERRIDE_3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_OVERRIDE_3_ADDR,m,v,HWIO_OVERRIDE_3_IN)
#define HWIO_OVERRIDE_3_RSVD_31_11_BMSK                                                          0xfffff800
#define HWIO_OVERRIDE_3_RSVD_31_11_SHFT                                                                 0xb
#define HWIO_OVERRIDE_3_OVRID_SPDM_SECURE_MODE_BMSK                                                   0x400
#define HWIO_OVERRIDE_3_OVRID_SPDM_SECURE_MODE_SHFT                                                     0xa
#define HWIO_OVERRIDE_3_OVRID_LPASS_SPIDEN_DISABLE_BMSK                                               0x200
#define HWIO_OVERRIDE_3_OVRID_LPASS_SPIDEN_DISABLE_SHFT                                                 0x9
#define HWIO_OVERRIDE_3_OVRID_PIMEM_SPIDEN_DISABLE_BMSK                                               0x100
#define HWIO_OVERRIDE_3_OVRID_PIMEM_SPIDEN_DISABLE_SHFT                                                 0x8
#define HWIO_OVERRIDE_3_OVRID_WCSS_SPIDEN_DISABLE_BMSK                                                 0x80
#define HWIO_OVERRIDE_3_OVRID_WCSS_SPIDEN_DISABLE_SHFT                                                  0x7
#define HWIO_OVERRIDE_3_OVRID_DAP_SPIDEN_DISABLE_BMSK                                                  0x40
#define HWIO_OVERRIDE_3_OVRID_DAP_SPIDEN_DISABLE_SHFT                                                   0x6
#define HWIO_OVERRIDE_3_OVRID_APPS_SPIDEN_DISABLE_BMSK                                                 0x20
#define HWIO_OVERRIDE_3_OVRID_APPS_SPIDEN_DISABLE_SHFT                                                  0x5
#define HWIO_OVERRIDE_3_OVRID_LPASS_SPNIDEN_DISABLE_BMSK                                               0x10
#define HWIO_OVERRIDE_3_OVRID_LPASS_SPNIDEN_DISABLE_SHFT                                                0x4
#define HWIO_OVERRIDE_3_OVRID_PIMEM_SPNIDEN_DISABLE_BMSK                                                0x8
#define HWIO_OVERRIDE_3_OVRID_PIMEM_SPNIDEN_DISABLE_SHFT                                                0x3
#define HWIO_OVERRIDE_3_OVRID_WCSS_SPNIDEN_DISABLE_BMSK                                                 0x4
#define HWIO_OVERRIDE_3_OVRID_WCSS_SPNIDEN_DISABLE_SHFT                                                 0x2
#define HWIO_OVERRIDE_3_OVRID_DAP_SPNIDEN_DISABLE_BMSK                                                  0x2
#define HWIO_OVERRIDE_3_OVRID_DAP_SPNIDEN_DISABLE_SHFT                                                  0x1
#define HWIO_OVERRIDE_3_OVRID_APPS_SPNIDEN_DISABLE_BMSK                                                 0x1
#define HWIO_OVERRIDE_3_OVRID_APPS_SPNIDEN_DISABLE_SHFT                                                 0x0

#define HWIO_OVERRIDE_4_ADDR                                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x000060d0)
#define HWIO_OVERRIDE_4_OFFS                                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000060d0)
#define HWIO_OVERRIDE_4_RMSK                                                                     0xffffffff
#define HWIO_OVERRIDE_4_IN          \
        in_dword_masked(HWIO_OVERRIDE_4_ADDR, HWIO_OVERRIDE_4_RMSK)
#define HWIO_OVERRIDE_4_INM(m)      \
        in_dword_masked(HWIO_OVERRIDE_4_ADDR, m)
#define HWIO_OVERRIDE_4_OUT(v)      \
        out_dword(HWIO_OVERRIDE_4_ADDR,v)
#define HWIO_OVERRIDE_4_OUTM(m,v) \
        out_dword_masked_ns(HWIO_OVERRIDE_4_ADDR,m,v,HWIO_OVERRIDE_4_IN)
#define HWIO_OVERRIDE_4_RSVD_31_2_BMSK                                                           0xfffffffc
#define HWIO_OVERRIDE_4_RSVD_31_2_SHFT                                                                  0x2
#define HWIO_OVERRIDE_4_OVRID_MSS_NIDEN_DISABLE_BMSK                                                    0x2
#define HWIO_OVERRIDE_4_OVRID_MSS_NIDEN_DISABLE_SHFT                                                    0x1
#define HWIO_OVERRIDE_4_OVRID_MSS_DBGEN_DISABLE_BMSK                                                    0x1
#define HWIO_OVERRIDE_4_OVRID_MSS_DBGEN_DISABLE_SHFT                                                    0x0

#define HWIO_OVERRIDE_5_ADDR                                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x000060d4)
#define HWIO_OVERRIDE_5_OFFS                                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000060d4)
#define HWIO_OVERRIDE_5_RMSK                                                                     0xffffffff
#define HWIO_OVERRIDE_5_IN          \
        in_dword_masked(HWIO_OVERRIDE_5_ADDR, HWIO_OVERRIDE_5_RMSK)
#define HWIO_OVERRIDE_5_INM(m)      \
        in_dword_masked(HWIO_OVERRIDE_5_ADDR, m)
#define HWIO_OVERRIDE_5_OUT(v)      \
        out_dword(HWIO_OVERRIDE_5_ADDR,v)
#define HWIO_OVERRIDE_5_OUTM(m,v) \
        out_dword_masked_ns(HWIO_OVERRIDE_5_ADDR,m,v,HWIO_OVERRIDE_5_IN)
#define HWIO_OVERRIDE_5_RSVD_31_0_BMSK                                                           0xffffffff
#define HWIO_OVERRIDE_5_RSVD_31_0_SHFT                                                                  0x0

#define HWIO_OVERRIDE_6_ADDR                                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x000060d8)
#define HWIO_OVERRIDE_6_OFFS                                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000060d8)
#define HWIO_OVERRIDE_6_RMSK                                                                     0xffffffff
#define HWIO_OVERRIDE_6_IN          \
        in_dword_masked(HWIO_OVERRIDE_6_ADDR, HWIO_OVERRIDE_6_RMSK)
#define HWIO_OVERRIDE_6_INM(m)      \
        in_dword_masked(HWIO_OVERRIDE_6_ADDR, m)
#define HWIO_OVERRIDE_6_OUT(v)      \
        out_dword(HWIO_OVERRIDE_6_ADDR,v)
#define HWIO_OVERRIDE_6_OUTM(m,v) \
        out_dword_masked_ns(HWIO_OVERRIDE_6_ADDR,m,v,HWIO_OVERRIDE_6_IN)
#define HWIO_OVERRIDE_6_RSVD_31_0_BMSK                                                           0xffffffff
#define HWIO_OVERRIDE_6_RSVD_31_0_SHFT                                                                  0x0

#define HWIO_CAPT_SEC_GPIO_ADDR                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006100)
#define HWIO_CAPT_SEC_GPIO_OFFS                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006100)
#define HWIO_CAPT_SEC_GPIO_RMSK                                                                     0x1ffff
#define HWIO_CAPT_SEC_GPIO_IN          \
        in_dword_masked(HWIO_CAPT_SEC_GPIO_ADDR, HWIO_CAPT_SEC_GPIO_RMSK)
#define HWIO_CAPT_SEC_GPIO_INM(m)      \
        in_dword_masked(HWIO_CAPT_SEC_GPIO_ADDR, m)
#define HWIO_CAPT_SEC_GPIO_OUT(v)      \
        out_dword(HWIO_CAPT_SEC_GPIO_ADDR,v)
#define HWIO_CAPT_SEC_GPIO_OUTM(m,v) \
        out_dword_masked_ns(HWIO_CAPT_SEC_GPIO_ADDR,m,v,HWIO_CAPT_SEC_GPIO_IN)
#define HWIO_CAPT_SEC_GPIO_FORCE_USB_BOOT_GPIO_BMSK                                                 0x10000
#define HWIO_CAPT_SEC_GPIO_FORCE_USB_BOOT_GPIO_SHFT                                                    0x10
#define HWIO_CAPT_SEC_GPIO_BOOT_CONFIG_GPIO_FORCE_MSA_AUTH_EN_BMSK                                   0x8000
#define HWIO_CAPT_SEC_GPIO_BOOT_CONFIG_GPIO_FORCE_MSA_AUTH_EN_SHFT                                      0xf
#define HWIO_CAPT_SEC_GPIO_BOOT_CONFIG_GPIO_AP_AUTH_EN_BMSK                                          0x4000
#define HWIO_CAPT_SEC_GPIO_BOOT_CONFIG_GPIO_AP_AUTH_EN_SHFT                                             0xe
#define HWIO_CAPT_SEC_GPIO_BOOT_CONFIG_GPIO_AP_PK_HASH_IN_FUSE_BMSK                                  0x2000
#define HWIO_CAPT_SEC_GPIO_BOOT_CONFIG_GPIO_AP_PK_HASH_IN_FUSE_SHFT                                     0xd
#define HWIO_CAPT_SEC_GPIO_BOOT_CONFIG_GPIO_MSA_AUTH_EN_BMSK                                         0x1000
#define HWIO_CAPT_SEC_GPIO_BOOT_CONFIG_GPIO_MSA_AUTH_EN_SHFT                                            0xc
#define HWIO_CAPT_SEC_GPIO_BOOT_CONFIG_GPIO_MSA_PK_HASH_IN_FUSE_BMSK                                  0x800
#define HWIO_CAPT_SEC_GPIO_BOOT_CONFIG_GPIO_MSA_PK_HASH_IN_FUSE_SHFT                                    0xb
#define HWIO_CAPT_SEC_GPIO_BOOT_CONFIG_GPIO_ALL_USE_SERIAL_NUM_BMSK                                   0x400
#define HWIO_CAPT_SEC_GPIO_BOOT_CONFIG_GPIO_ALL_USE_SERIAL_NUM_SHFT                                     0xa
#define HWIO_CAPT_SEC_GPIO_BOOT_CONFIG_GPIO_PK_HASH_INDEX_SRC_BMSK                                    0x200
#define HWIO_CAPT_SEC_GPIO_BOOT_CONFIG_GPIO_PK_HASH_INDEX_SRC_SHFT                                      0x9
#define HWIO_CAPT_SEC_GPIO_BOOT_CONFIG_GPIO_APPS_PBL_BOOT_SPEED_BMSK                                  0x180
#define HWIO_CAPT_SEC_GPIO_BOOT_CONFIG_GPIO_APPS_PBL_BOOT_SPEED_SHFT                                    0x7
#define HWIO_CAPT_SEC_GPIO_BOOT_CONFIG_GPIO_MODEM_BOOT_FROM_ROM_BMSK                                   0x40
#define HWIO_CAPT_SEC_GPIO_BOOT_CONFIG_GPIO_MODEM_BOOT_FROM_ROM_SHFT                                    0x6
#define HWIO_CAPT_SEC_GPIO_BOOT_CONFIG_GPIO_APPS_BOOT_FROM_ROM_BMSK                                    0x20
#define HWIO_CAPT_SEC_GPIO_BOOT_CONFIG_GPIO_APPS_BOOT_FROM_ROM_SHFT                                     0x5
#define HWIO_CAPT_SEC_GPIO_BOOT_CONFIG_GPIO_FAST_BOOT_BMSK                                             0x1e
#define HWIO_CAPT_SEC_GPIO_BOOT_CONFIG_GPIO_FAST_BOOT_SHFT                                              0x1
#define HWIO_CAPT_SEC_GPIO_BOOT_CONFIG_GPIO_WDOG_DISABLE_BMSK                                           0x1
#define HWIO_CAPT_SEC_GPIO_BOOT_CONFIG_GPIO_WDOG_DISABLE_SHFT                                           0x0

#define HWIO_APP_PROC_CFG_ADDR                                                                   (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006110)
#define HWIO_APP_PROC_CFG_OFFS                                                                   (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006110)
#define HWIO_APP_PROC_CFG_RMSK                                                                        0xfff
#define HWIO_APP_PROC_CFG_IN          \
        in_dword_masked(HWIO_APP_PROC_CFG_ADDR, HWIO_APP_PROC_CFG_RMSK)
#define HWIO_APP_PROC_CFG_INM(m)      \
        in_dword_masked(HWIO_APP_PROC_CFG_ADDR, m)
#define HWIO_APP_PROC_CFG_OUT(v)      \
        out_dword(HWIO_APP_PROC_CFG_ADDR,v)
#define HWIO_APP_PROC_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APP_PROC_CFG_ADDR,m,v,HWIO_APP_PROC_CFG_IN)
#define HWIO_APP_PROC_CFG_LPASS_DBG_SPNIDEN_BMSK                                                      0x800
#define HWIO_APP_PROC_CFG_LPASS_DBG_SPNIDEN_SHFT                                                        0xb
#define HWIO_APP_PROC_CFG_PIMEM_DBG_SPNIDEN_BMSK                                                      0x400
#define HWIO_APP_PROC_CFG_PIMEM_DBG_SPNIDEN_SHFT                                                        0xa
#define HWIO_APP_PROC_CFG_WCSS_DBG_SPNIDEN_BMSK                                                       0x200
#define HWIO_APP_PROC_CFG_WCSS_DBG_SPNIDEN_SHFT                                                         0x9
#define HWIO_APP_PROC_CFG_DAP_DBG_SPNIDEN_BMSK                                                        0x100
#define HWIO_APP_PROC_CFG_DAP_DBG_SPNIDEN_SHFT                                                          0x8
#define HWIO_APP_PROC_CFG_APPS_DBG_SPNIDEN_BMSK                                                        0x80
#define HWIO_APP_PROC_CFG_APPS_DBG_SPNIDEN_SHFT                                                         0x7
#define HWIO_APP_PROC_CFG_LPASS_SENSOR_DBG_NIDEN_BMSK                                                  0x40
#define HWIO_APP_PROC_CFG_LPASS_SENSOR_DBG_NIDEN_SHFT                                                   0x6
#define HWIO_APP_PROC_CFG_PIMEM_DBG_NIDEN_BMSK                                                         0x20
#define HWIO_APP_PROC_CFG_PIMEM_DBG_NIDEN_SHFT                                                          0x5
#define HWIO_APP_PROC_CFG_RPM_DBG_NIDEN_BMSK                                                           0x10
#define HWIO_APP_PROC_CFG_RPM_DBG_NIDEN_SHFT                                                            0x4
#define HWIO_APP_PROC_CFG_WCSS_DBG_NIDEN_BMSK                                                           0x8
#define HWIO_APP_PROC_CFG_WCSS_DBG_NIDEN_SHFT                                                           0x3
#define HWIO_APP_PROC_CFG_LPASS_DBG_NIDEN_BMSK                                                          0x4
#define HWIO_APP_PROC_CFG_LPASS_DBG_NIDEN_SHFT                                                          0x2
#define HWIO_APP_PROC_CFG_DAP_DBG_NIDEN_BMSK                                                            0x2
#define HWIO_APP_PROC_CFG_DAP_DBG_NIDEN_SHFT                                                            0x1
#define HWIO_APP_PROC_CFG_APPS_DBG_NIDEN_BMSK                                                           0x1
#define HWIO_APP_PROC_CFG_APPS_DBG_NIDEN_SHFT                                                           0x0

#define HWIO_MSS_PROC_CFG_ADDR                                                                   (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006114)
#define HWIO_MSS_PROC_CFG_OFFS                                                                   (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006114)
#define HWIO_MSS_PROC_CFG_RMSK                                                                          0x1
#define HWIO_MSS_PROC_CFG_IN          \
        in_dword_masked(HWIO_MSS_PROC_CFG_ADDR, HWIO_MSS_PROC_CFG_RMSK)
#define HWIO_MSS_PROC_CFG_INM(m)      \
        in_dword_masked(HWIO_MSS_PROC_CFG_ADDR, m)
#define HWIO_MSS_PROC_CFG_OUT(v)      \
        out_dword(HWIO_MSS_PROC_CFG_ADDR,v)
#define HWIO_MSS_PROC_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MSS_PROC_CFG_ADDR,m,v,HWIO_MSS_PROC_CFG_IN)
#define HWIO_MSS_PROC_CFG_MSS_DBG_NIDEN_BMSK                                                            0x1
#define HWIO_MSS_PROC_CFG_MSS_DBG_NIDEN_SHFT                                                            0x0

#define HWIO_QFPROM_CLK_CTL_ADDR                                                                 (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006118)
#define HWIO_QFPROM_CLK_CTL_OFFS                                                                 (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006118)
#define HWIO_QFPROM_CLK_CTL_RMSK                                                                        0x1
#define HWIO_QFPROM_CLK_CTL_IN          \
        in_dword_masked(HWIO_QFPROM_CLK_CTL_ADDR, HWIO_QFPROM_CLK_CTL_RMSK)
#define HWIO_QFPROM_CLK_CTL_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CLK_CTL_ADDR, m)
#define HWIO_QFPROM_CLK_CTL_OUT(v)      \
        out_dword(HWIO_QFPROM_CLK_CTL_ADDR,v)
#define HWIO_QFPROM_CLK_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_CLK_CTL_ADDR,m,v,HWIO_QFPROM_CLK_CTL_IN)
#define HWIO_QFPROM_CLK_CTL_CLK_HALT_BMSK                                                               0x1
#define HWIO_QFPROM_CLK_CTL_CLK_HALT_SHFT                                                               0x0

#define HWIO_JTAG_ID_ADDR                                                                        (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006130)
#define HWIO_JTAG_ID_OFFS                                                                        (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006130)
#define HWIO_JTAG_ID_RMSK                                                                        0xffffffff
#define HWIO_JTAG_ID_IN          \
        in_dword_masked(HWIO_JTAG_ID_ADDR, HWIO_JTAG_ID_RMSK)
#define HWIO_JTAG_ID_INM(m)      \
        in_dword_masked(HWIO_JTAG_ID_ADDR, m)
#define HWIO_JTAG_ID_JTAG_ID_BMSK                                                                0xffffffff
#define HWIO_JTAG_ID_JTAG_ID_SHFT                                                                       0x0

#define HWIO_SERIAL_NUM_ADDR                                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006134)
#define HWIO_SERIAL_NUM_OFFS                                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006134)
#define HWIO_SERIAL_NUM_RMSK                                                                     0xffffffff
#define HWIO_SERIAL_NUM_IN          \
        in_dword_masked(HWIO_SERIAL_NUM_ADDR, HWIO_SERIAL_NUM_RMSK)
#define HWIO_SERIAL_NUM_INM(m)      \
        in_dword_masked(HWIO_SERIAL_NUM_ADDR, m)
#define HWIO_SERIAL_NUM_SERIAL_NUM_BMSK                                                          0xffffffff
#define HWIO_SERIAL_NUM_SERIAL_NUM_SHFT                                                                 0x0

#define HWIO_OEM_ID_ADDR                                                                         (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006138)
#define HWIO_OEM_ID_OFFS                                                                         (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006138)
#define HWIO_OEM_ID_RMSK                                                                         0xffffffff
#define HWIO_OEM_ID_IN          \
        in_dword_masked(HWIO_OEM_ID_ADDR, HWIO_OEM_ID_RMSK)
#define HWIO_OEM_ID_INM(m)      \
        in_dword_masked(HWIO_OEM_ID_ADDR, m)
#define HWIO_OEM_ID_OEM_ID_BMSK                                                                  0xffff0000
#define HWIO_OEM_ID_OEM_ID_SHFT                                                                        0x10
#define HWIO_OEM_ID_OEM_PRODUCT_ID_BMSK                                                              0xffff
#define HWIO_OEM_ID_OEM_PRODUCT_ID_SHFT                                                                 0x0

#define HWIO_TEST_BUS_SEL_ADDR                                                                   (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000613c)
#define HWIO_TEST_BUS_SEL_OFFS                                                                   (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000613c)
#define HWIO_TEST_BUS_SEL_RMSK                                                                          0x7
#define HWIO_TEST_BUS_SEL_IN          \
        in_dword_masked(HWIO_TEST_BUS_SEL_ADDR, HWIO_TEST_BUS_SEL_RMSK)
#define HWIO_TEST_BUS_SEL_INM(m)      \
        in_dword_masked(HWIO_TEST_BUS_SEL_ADDR, m)
#define HWIO_TEST_BUS_SEL_OUT(v)      \
        out_dword(HWIO_TEST_BUS_SEL_ADDR,v)
#define HWIO_TEST_BUS_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TEST_BUS_SEL_ADDR,m,v,HWIO_TEST_BUS_SEL_IN)
#define HWIO_TEST_BUS_SEL_TEST_EN_BMSK                                                                  0x4
#define HWIO_TEST_BUS_SEL_TEST_EN_SHFT                                                                  0x2
#define HWIO_TEST_BUS_SEL_TEST_SELECT_BMSK                                                              0x3
#define HWIO_TEST_BUS_SEL_TEST_SELECT_SHFT                                                              0x0

#define HWIO_SPDM_DYN_SECURE_MODE_ADDR                                                           (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006140)
#define HWIO_SPDM_DYN_SECURE_MODE_OFFS                                                           (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006140)
#define HWIO_SPDM_DYN_SECURE_MODE_RMSK                                                                  0x1
#define HWIO_SPDM_DYN_SECURE_MODE_IN          \
        in_dword_masked(HWIO_SPDM_DYN_SECURE_MODE_ADDR, HWIO_SPDM_DYN_SECURE_MODE_RMSK)
#define HWIO_SPDM_DYN_SECURE_MODE_INM(m)      \
        in_dword_masked(HWIO_SPDM_DYN_SECURE_MODE_ADDR, m)
#define HWIO_SPDM_DYN_SECURE_MODE_OUT(v)      \
        out_dword(HWIO_SPDM_DYN_SECURE_MODE_ADDR,v)
#define HWIO_SPDM_DYN_SECURE_MODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SPDM_DYN_SECURE_MODE_ADDR,m,v,HWIO_SPDM_DYN_SECURE_MODE_IN)
#define HWIO_SPDM_DYN_SECURE_MODE_SECURE_MODE_BMSK                                                      0x1
#define HWIO_SPDM_DYN_SECURE_MODE_SECURE_MODE_SHFT                                                      0x0

#define HWIO_OEM_IMAGE_ENCR_KEYn_ADDR(n)                                                         (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006150 + 0x4 * (n))
#define HWIO_OEM_IMAGE_ENCR_KEYn_OFFS(n)                                                         (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006150 + 0x4 * (n))
#define HWIO_OEM_IMAGE_ENCR_KEYn_RMSK                                                            0xffffffff
#define HWIO_OEM_IMAGE_ENCR_KEYn_MAXn                                                                     3
#define HWIO_OEM_IMAGE_ENCR_KEYn_INI(n)        \
        in_dword_masked(HWIO_OEM_IMAGE_ENCR_KEYn_ADDR(n), HWIO_OEM_IMAGE_ENCR_KEYn_RMSK)
#define HWIO_OEM_IMAGE_ENCR_KEYn_INMI(n,mask)    \
        in_dword_masked(HWIO_OEM_IMAGE_ENCR_KEYn_ADDR(n), mask)
#define HWIO_OEM_IMAGE_ENCR_KEYn_KEY_DATA0_BMSK                                                  0xffffffff
#define HWIO_OEM_IMAGE_ENCR_KEYn_KEY_DATA0_SHFT                                                         0x0

#define HWIO_IMAGE_ENCR_KEY1_0_ADDR                                                              (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006160)
#define HWIO_IMAGE_ENCR_KEY1_0_OFFS                                                              (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006160)
#define HWIO_IMAGE_ENCR_KEY1_0_RMSK                                                              0xffffffff
#define HWIO_IMAGE_ENCR_KEY1_0_IN          \
        in_dword_masked(HWIO_IMAGE_ENCR_KEY1_0_ADDR, HWIO_IMAGE_ENCR_KEY1_0_RMSK)
#define HWIO_IMAGE_ENCR_KEY1_0_INM(m)      \
        in_dword_masked(HWIO_IMAGE_ENCR_KEY1_0_ADDR, m)
#define HWIO_IMAGE_ENCR_KEY1_0_KEY_DATA0_BMSK                                                    0xffffffff
#define HWIO_IMAGE_ENCR_KEY1_0_KEY_DATA0_SHFT                                                           0x0

#define HWIO_IMAGE_ENCR_KEY1_1_ADDR                                                              (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006164)
#define HWIO_IMAGE_ENCR_KEY1_1_OFFS                                                              (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006164)
#define HWIO_IMAGE_ENCR_KEY1_1_RMSK                                                              0xffffffff
#define HWIO_IMAGE_ENCR_KEY1_1_IN          \
        in_dword_masked(HWIO_IMAGE_ENCR_KEY1_1_ADDR, HWIO_IMAGE_ENCR_KEY1_1_RMSK)
#define HWIO_IMAGE_ENCR_KEY1_1_INM(m)      \
        in_dword_masked(HWIO_IMAGE_ENCR_KEY1_1_ADDR, m)
#define HWIO_IMAGE_ENCR_KEY1_1_KEY_DATA0_BMSK                                                    0xffffffff
#define HWIO_IMAGE_ENCR_KEY1_1_KEY_DATA0_SHFT                                                           0x0

#define HWIO_IMAGE_ENCR_KEY1_2_ADDR                                                              (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006168)
#define HWIO_IMAGE_ENCR_KEY1_2_OFFS                                                              (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006168)
#define HWIO_IMAGE_ENCR_KEY1_2_RMSK                                                              0xffffffff
#define HWIO_IMAGE_ENCR_KEY1_2_IN          \
        in_dword_masked(HWIO_IMAGE_ENCR_KEY1_2_ADDR, HWIO_IMAGE_ENCR_KEY1_2_RMSK)
#define HWIO_IMAGE_ENCR_KEY1_2_INM(m)      \
        in_dword_masked(HWIO_IMAGE_ENCR_KEY1_2_ADDR, m)
#define HWIO_IMAGE_ENCR_KEY1_2_KEY_DATA0_BMSK                                                    0xffffffff
#define HWIO_IMAGE_ENCR_KEY1_2_KEY_DATA0_SHFT                                                           0x0

#define HWIO_IMAGE_ENCR_KEY1_3_ADDR                                                              (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000616c)
#define HWIO_IMAGE_ENCR_KEY1_3_OFFS                                                              (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000616c)
#define HWIO_IMAGE_ENCR_KEY1_3_RMSK                                                              0xffffffff
#define HWIO_IMAGE_ENCR_KEY1_3_IN          \
        in_dword_masked(HWIO_IMAGE_ENCR_KEY1_3_ADDR, HWIO_IMAGE_ENCR_KEY1_3_RMSK)
#define HWIO_IMAGE_ENCR_KEY1_3_INM(m)      \
        in_dword_masked(HWIO_IMAGE_ENCR_KEY1_3_ADDR, m)
#define HWIO_IMAGE_ENCR_KEY1_3_KEY_DATA0_BMSK                                                    0xffffffff
#define HWIO_IMAGE_ENCR_KEY1_3_KEY_DATA0_SHFT                                                           0x0

#define HWIO_PK_HASH0_0_ADDR                                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006190)
#define HWIO_PK_HASH0_0_OFFS                                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006190)
#define HWIO_PK_HASH0_0_RMSK                                                                     0xffffffff
#define HWIO_PK_HASH0_0_IN          \
        in_dword_masked(HWIO_PK_HASH0_0_ADDR, HWIO_PK_HASH0_0_RMSK)
#define HWIO_PK_HASH0_0_INM(m)      \
        in_dword_masked(HWIO_PK_HASH0_0_ADDR, m)
#define HWIO_PK_HASH0_0_HASH_DATA0_BMSK                                                          0xffffffff
#define HWIO_PK_HASH0_0_HASH_DATA0_SHFT                                                                 0x0

#define HWIO_PK_HASH0_1_ADDR                                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006194)
#define HWIO_PK_HASH0_1_OFFS                                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006194)
#define HWIO_PK_HASH0_1_RMSK                                                                     0xffffffff
#define HWIO_PK_HASH0_1_IN          \
        in_dword_masked(HWIO_PK_HASH0_1_ADDR, HWIO_PK_HASH0_1_RMSK)
#define HWIO_PK_HASH0_1_INM(m)      \
        in_dword_masked(HWIO_PK_HASH0_1_ADDR, m)
#define HWIO_PK_HASH0_1_HASH_DATA0_BMSK                                                          0xffffffff
#define HWIO_PK_HASH0_1_HASH_DATA0_SHFT                                                                 0x0

#define HWIO_PK_HASH0_2_ADDR                                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006198)
#define HWIO_PK_HASH0_2_OFFS                                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006198)
#define HWIO_PK_HASH0_2_RMSK                                                                     0xffffffff
#define HWIO_PK_HASH0_2_IN          \
        in_dword_masked(HWIO_PK_HASH0_2_ADDR, HWIO_PK_HASH0_2_RMSK)
#define HWIO_PK_HASH0_2_INM(m)      \
        in_dword_masked(HWIO_PK_HASH0_2_ADDR, m)
#define HWIO_PK_HASH0_2_HASH_DATA0_BMSK                                                          0xffffffff
#define HWIO_PK_HASH0_2_HASH_DATA0_SHFT                                                                 0x0

#define HWIO_PK_HASH0_3_ADDR                                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000619c)
#define HWIO_PK_HASH0_3_OFFS                                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000619c)
#define HWIO_PK_HASH0_3_RMSK                                                                     0xffffffff
#define HWIO_PK_HASH0_3_IN          \
        in_dword_masked(HWIO_PK_HASH0_3_ADDR, HWIO_PK_HASH0_3_RMSK)
#define HWIO_PK_HASH0_3_INM(m)      \
        in_dword_masked(HWIO_PK_HASH0_3_ADDR, m)
#define HWIO_PK_HASH0_3_HASH_DATA0_BMSK                                                          0xffffffff
#define HWIO_PK_HASH0_3_HASH_DATA0_SHFT                                                                 0x0

#define HWIO_PK_HASH0_4_ADDR                                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x000061a0)
#define HWIO_PK_HASH0_4_OFFS                                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000061a0)
#define HWIO_PK_HASH0_4_RMSK                                                                     0xffffffff
#define HWIO_PK_HASH0_4_IN          \
        in_dword_masked(HWIO_PK_HASH0_4_ADDR, HWIO_PK_HASH0_4_RMSK)
#define HWIO_PK_HASH0_4_INM(m)      \
        in_dword_masked(HWIO_PK_HASH0_4_ADDR, m)
#define HWIO_PK_HASH0_4_HASH_DATA0_BMSK                                                          0xffffffff
#define HWIO_PK_HASH0_4_HASH_DATA0_SHFT                                                                 0x0

#define HWIO_PK_HASH0_5_ADDR                                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x000061a4)
#define HWIO_PK_HASH0_5_OFFS                                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000061a4)
#define HWIO_PK_HASH0_5_RMSK                                                                     0xffffffff
#define HWIO_PK_HASH0_5_IN          \
        in_dword_masked(HWIO_PK_HASH0_5_ADDR, HWIO_PK_HASH0_5_RMSK)
#define HWIO_PK_HASH0_5_INM(m)      \
        in_dword_masked(HWIO_PK_HASH0_5_ADDR, m)
#define HWIO_PK_HASH0_5_HASH_DATA0_BMSK                                                          0xffffffff
#define HWIO_PK_HASH0_5_HASH_DATA0_SHFT                                                                 0x0

#define HWIO_PK_HASH0_6_ADDR                                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x000061a8)
#define HWIO_PK_HASH0_6_OFFS                                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000061a8)
#define HWIO_PK_HASH0_6_RMSK                                                                     0xffffffff
#define HWIO_PK_HASH0_6_IN          \
        in_dword_masked(HWIO_PK_HASH0_6_ADDR, HWIO_PK_HASH0_6_RMSK)
#define HWIO_PK_HASH0_6_INM(m)      \
        in_dword_masked(HWIO_PK_HASH0_6_ADDR, m)
#define HWIO_PK_HASH0_6_HASH_DATA0_BMSK                                                          0xffffffff
#define HWIO_PK_HASH0_6_HASH_DATA0_SHFT                                                                 0x0

#define HWIO_PK_HASH0_7_ADDR                                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x000061ac)
#define HWIO_PK_HASH0_7_OFFS                                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000061ac)
#define HWIO_PK_HASH0_7_RMSK                                                                     0xffffffff
#define HWIO_PK_HASH0_7_IN          \
        in_dword_masked(HWIO_PK_HASH0_7_ADDR, HWIO_PK_HASH0_7_RMSK)
#define HWIO_PK_HASH0_7_INM(m)      \
        in_dword_masked(HWIO_PK_HASH0_7_ADDR, m)
#define HWIO_PK_HASH0_7_HASH_DATA0_BMSK                                                          0xffffffff
#define HWIO_PK_HASH0_7_HASH_DATA0_SHFT                                                                 0x0

#define HWIO_PK_HASH1_0_ADDR                                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x000061b0)
#define HWIO_PK_HASH1_0_OFFS                                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000061b0)
#define HWIO_PK_HASH1_0_RMSK                                                                     0xffffffff
#define HWIO_PK_HASH1_0_IN          \
        in_dword_masked(HWIO_PK_HASH1_0_ADDR, HWIO_PK_HASH1_0_RMSK)
#define HWIO_PK_HASH1_0_INM(m)      \
        in_dword_masked(HWIO_PK_HASH1_0_ADDR, m)
#define HWIO_PK_HASH1_0_HASH_DATA0_BMSK                                                          0xffffffff
#define HWIO_PK_HASH1_0_HASH_DATA0_SHFT                                                                 0x0

#define HWIO_PK_HASH1_1_ADDR                                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x000061b4)
#define HWIO_PK_HASH1_1_OFFS                                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000061b4)
#define HWIO_PK_HASH1_1_RMSK                                                                     0xffffffff
#define HWIO_PK_HASH1_1_IN          \
        in_dword_masked(HWIO_PK_HASH1_1_ADDR, HWIO_PK_HASH1_1_RMSK)
#define HWIO_PK_HASH1_1_INM(m)      \
        in_dword_masked(HWIO_PK_HASH1_1_ADDR, m)
#define HWIO_PK_HASH1_1_HASH_DATA0_BMSK                                                          0xffffffff
#define HWIO_PK_HASH1_1_HASH_DATA0_SHFT                                                                 0x0

#define HWIO_PK_HASH1_2_ADDR                                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x000061b8)
#define HWIO_PK_HASH1_2_OFFS                                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000061b8)
#define HWIO_PK_HASH1_2_RMSK                                                                     0xffffffff
#define HWIO_PK_HASH1_2_IN          \
        in_dword_masked(HWIO_PK_HASH1_2_ADDR, HWIO_PK_HASH1_2_RMSK)
#define HWIO_PK_HASH1_2_INM(m)      \
        in_dword_masked(HWIO_PK_HASH1_2_ADDR, m)
#define HWIO_PK_HASH1_2_HASH_DATA0_BMSK                                                          0xffffffff
#define HWIO_PK_HASH1_2_HASH_DATA0_SHFT                                                                 0x0

#define HWIO_PK_HASH1_3_ADDR                                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x000061bc)
#define HWIO_PK_HASH1_3_OFFS                                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000061bc)
#define HWIO_PK_HASH1_3_RMSK                                                                     0xffffffff
#define HWIO_PK_HASH1_3_IN          \
        in_dword_masked(HWIO_PK_HASH1_3_ADDR, HWIO_PK_HASH1_3_RMSK)
#define HWIO_PK_HASH1_3_INM(m)      \
        in_dword_masked(HWIO_PK_HASH1_3_ADDR, m)
#define HWIO_PK_HASH1_3_HASH_DATA0_BMSK                                                          0xffffffff
#define HWIO_PK_HASH1_3_HASH_DATA0_SHFT                                                                 0x0

#define HWIO_PK_HASH1_4_ADDR                                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x000061c0)
#define HWIO_PK_HASH1_4_OFFS                                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000061c0)
#define HWIO_PK_HASH1_4_RMSK                                                                     0xffffffff
#define HWIO_PK_HASH1_4_IN          \
        in_dword_masked(HWIO_PK_HASH1_4_ADDR, HWIO_PK_HASH1_4_RMSK)
#define HWIO_PK_HASH1_4_INM(m)      \
        in_dword_masked(HWIO_PK_HASH1_4_ADDR, m)
#define HWIO_PK_HASH1_4_HASH_DATA0_BMSK                                                          0xffffffff
#define HWIO_PK_HASH1_4_HASH_DATA0_SHFT                                                                 0x0

#define HWIO_PK_HASH1_5_ADDR                                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x000061c4)
#define HWIO_PK_HASH1_5_OFFS                                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000061c4)
#define HWIO_PK_HASH1_5_RMSK                                                                     0xffffffff
#define HWIO_PK_HASH1_5_IN          \
        in_dword_masked(HWIO_PK_HASH1_5_ADDR, HWIO_PK_HASH1_5_RMSK)
#define HWIO_PK_HASH1_5_INM(m)      \
        in_dword_masked(HWIO_PK_HASH1_5_ADDR, m)
#define HWIO_PK_HASH1_5_HASH_DATA0_BMSK                                                          0xffffffff
#define HWIO_PK_HASH1_5_HASH_DATA0_SHFT                                                                 0x0

#define HWIO_PK_HASH1_6_ADDR                                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x000061c8)
#define HWIO_PK_HASH1_6_OFFS                                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000061c8)
#define HWIO_PK_HASH1_6_RMSK                                                                     0xffffffff
#define HWIO_PK_HASH1_6_IN          \
        in_dword_masked(HWIO_PK_HASH1_6_ADDR, HWIO_PK_HASH1_6_RMSK)
#define HWIO_PK_HASH1_6_INM(m)      \
        in_dword_masked(HWIO_PK_HASH1_6_ADDR, m)
#define HWIO_PK_HASH1_6_HASH_DATA0_BMSK                                                          0xffffffff
#define HWIO_PK_HASH1_6_HASH_DATA0_SHFT                                                                 0x0

#define HWIO_PK_HASH1_7_ADDR                                                                     (SECURITY_CONTROL_CORE_REG_BASE      + 0x000061cc)
#define HWIO_PK_HASH1_7_OFFS                                                                     (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000061cc)
#define HWIO_PK_HASH1_7_RMSK                                                                     0xffffffff
#define HWIO_PK_HASH1_7_IN          \
        in_dword_masked(HWIO_PK_HASH1_7_ADDR, HWIO_PK_HASH1_7_RMSK)
#define HWIO_PK_HASH1_7_INM(m)      \
        in_dword_masked(HWIO_PK_HASH1_7_ADDR, m)
#define HWIO_PK_HASH1_7_HASH_DATA0_BMSK                                                          0xffffffff
#define HWIO_PK_HASH1_7_HASH_DATA0_SHFT                                                                 0x0

#define HWIO_SW_ROT_STICKY_BIT_ADDR                                                              (SECURITY_CONTROL_CORE_REG_BASE      + 0x000061e0)
#define HWIO_SW_ROT_STICKY_BIT_OFFS                                                              (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000061e0)
#define HWIO_SW_ROT_STICKY_BIT_RMSK                                                                     0x1
#define HWIO_SW_ROT_STICKY_BIT_IN          \
        in_dword_masked(HWIO_SW_ROT_STICKY_BIT_ADDR, HWIO_SW_ROT_STICKY_BIT_RMSK)
#define HWIO_SW_ROT_STICKY_BIT_INM(m)      \
        in_dword_masked(HWIO_SW_ROT_STICKY_BIT_ADDR, m)
#define HWIO_SW_ROT_STICKY_BIT_OUT(v)      \
        out_dword(HWIO_SW_ROT_STICKY_BIT_ADDR,v)
#define HWIO_SW_ROT_STICKY_BIT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SW_ROT_STICKY_BIT_ADDR,m,v,HWIO_SW_ROT_STICKY_BIT_IN)
#define HWIO_SW_ROT_STICKY_BIT_SW_ROT_STICKY_BIT_0_BMSK                                                 0x1
#define HWIO_SW_ROT_STICKY_BIT_SW_ROT_STICKY_BIT_0_SHFT                                                 0x0

#define HWIO_SW_ROT_CONFIG_ADDR                                                                  (SECURITY_CONTROL_CORE_REG_BASE      + 0x000061e4)
#define HWIO_SW_ROT_CONFIG_OFFS                                                                  (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000061e4)
#define HWIO_SW_ROT_CONFIG_RMSK                                                                         0x3
#define HWIO_SW_ROT_CONFIG_IN          \
        in_dword_masked(HWIO_SW_ROT_CONFIG_ADDR, HWIO_SW_ROT_CONFIG_RMSK)
#define HWIO_SW_ROT_CONFIG_INM(m)      \
        in_dword_masked(HWIO_SW_ROT_CONFIG_ADDR, m)
#define HWIO_SW_ROT_CONFIG_CURRENT_SW_ROT_MODEM_BMSK                                                    0x2
#define HWIO_SW_ROT_CONFIG_CURRENT_SW_ROT_MODEM_SHFT                                                    0x1
#define HWIO_SW_ROT_CONFIG_CURRENT_SW_ROT_APPS_BMSK                                                     0x1
#define HWIO_SW_ROT_CONFIG_CURRENT_SW_ROT_APPS_SHFT                                                     0x0

#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_ADDR                                               (SECURITY_CONTROL_CORE_REG_BASE      + 0x000061f0)
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_OFFS                                               (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000061f0)
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_RMSK                                               0xffffffff
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_IN          \
        in_dword_masked(HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_ADDR, HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_RMSK)
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_INM(m)      \
        in_dword_masked(HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_ADDR, m)
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_OUT(v)      \
        out_dword(HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_ADDR,v)
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_ADDR,m,v,HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_IN)
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_RSVD0_BMSK                                         0x80000000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_RSVD0_SHFT                                               0x1f
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION30_STICKY_BIT_BMSK                           0x40000000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION30_STICKY_BIT_SHFT                                 0x1e
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION29_STICKY_BIT_BMSK                           0x20000000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION29_STICKY_BIT_SHFT                                 0x1d
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION28_STICKY_BIT_BMSK                           0x10000000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION28_STICKY_BIT_SHFT                                 0x1c
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION27_STICKY_BIT_BMSK                            0x8000000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION27_STICKY_BIT_SHFT                                 0x1b
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION26_STICKY_BIT_BMSK                            0x4000000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION26_STICKY_BIT_SHFT                                 0x1a
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION25_STICKY_BIT_BMSK                            0x2000000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION25_STICKY_BIT_SHFT                                 0x19
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION24_STICKY_BIT_BMSK                            0x1000000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION24_STICKY_BIT_SHFT                                 0x18
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION23_STICKY_BIT_BMSK                             0x800000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION23_STICKY_BIT_SHFT                                 0x17
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION22_STICKY_BIT_BMSK                             0x400000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION22_STICKY_BIT_SHFT                                 0x16
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION21_STICKY_BIT_BMSK                             0x200000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION21_STICKY_BIT_SHFT                                 0x15
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION20_STICKY_BIT_BMSK                             0x100000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION20_STICKY_BIT_SHFT                                 0x14
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION19_STICKY_BIT_BMSK                              0x80000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION19_STICKY_BIT_SHFT                                 0x13
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION18_STICKY_BIT_BMSK                              0x40000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION18_STICKY_BIT_SHFT                                 0x12
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION17_STICKY_BIT_BMSK                              0x20000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION17_STICKY_BIT_SHFT                                 0x11
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION16_STICKY_BIT_BMSK                              0x10000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION16_STICKY_BIT_SHFT                                 0x10
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION15_STICKY_BIT_BMSK                               0x8000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION15_STICKY_BIT_SHFT                                  0xf
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION14_STICKY_BIT_BMSK                               0x4000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION14_STICKY_BIT_SHFT                                  0xe
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION13_STICKY_BIT_BMSK                               0x2000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION13_STICKY_BIT_SHFT                                  0xd
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION12_STICKY_BIT_BMSK                               0x1000
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION12_STICKY_BIT_SHFT                                  0xc
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION11_STICKY_BIT_BMSK                                0x800
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION11_STICKY_BIT_SHFT                                  0xb
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION10_STICKY_BIT_BMSK                                0x400
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION10_STICKY_BIT_SHFT                                  0xa
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION9_STICKY_BIT_BMSK                                 0x200
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION9_STICKY_BIT_SHFT                                   0x9
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION8_STICKY_BIT_BMSK                                 0x100
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION8_STICKY_BIT_SHFT                                   0x8
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION7_STICKY_BIT_BMSK                                  0x80
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION7_STICKY_BIT_SHFT                                   0x7
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION6_STICKY_BIT_BMSK                                  0x40
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION6_STICKY_BIT_SHFT                                   0x6
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION5_STICKY_BIT_BMSK                                  0x20
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION5_STICKY_BIT_SHFT                                   0x5
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION4_STICKY_BIT_BMSK                                  0x10
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION4_STICKY_BIT_SHFT                                   0x4
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION3_STICKY_BIT_BMSK                                   0x8
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION3_STICKY_BIT_SHFT                                   0x3
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION2_STICKY_BIT_BMSK                                   0x4
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION2_STICKY_BIT_SHFT                                   0x2
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION1_STICKY_BIT_BMSK                                   0x2
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION1_STICKY_BIT_SHFT                                   0x1
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION0_STICKY_BIT_BMSK                                   0x1
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT0_REGION0_STICKY_BIT_SHFT                                   0x0

#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_ADDR                                               (SECURITY_CONTROL_CORE_REG_BASE      + 0x000061f4)
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_OFFS                                               (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x000061f4)
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_RMSK                                               0xffffffff
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_IN          \
        in_dword_masked(HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_ADDR, HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_RMSK)
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_INM(m)      \
        in_dword_masked(HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_ADDR, m)
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_OUT(v)      \
        out_dword(HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_ADDR,v)
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_ADDR,m,v,HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_IN)
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_RSVD0_BMSK                                         0xffffffff
#define HWIO_QFPROM_WRITE_DISABLE_STICKY_BIT1_RSVD0_SHFT                                                0x0

#define HWIO_ANTI_ROLLBACK_1_0_ADDR                                                              (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006200)
#define HWIO_ANTI_ROLLBACK_1_0_OFFS                                                              (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006200)
#define HWIO_ANTI_ROLLBACK_1_0_RMSK                                                              0xffffffff
#define HWIO_ANTI_ROLLBACK_1_0_IN          \
        in_dword_masked(HWIO_ANTI_ROLLBACK_1_0_ADDR, HWIO_ANTI_ROLLBACK_1_0_RMSK)
#define HWIO_ANTI_ROLLBACK_1_0_INM(m)      \
        in_dword_masked(HWIO_ANTI_ROLLBACK_1_0_ADDR, m)
#define HWIO_ANTI_ROLLBACK_1_0_XBL0_BMSK                                                         0xffffffff
#define HWIO_ANTI_ROLLBACK_1_0_XBL0_SHFT                                                                0x0

#define HWIO_ANTI_ROLLBACK_1_1_ADDR                                                              (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006204)
#define HWIO_ANTI_ROLLBACK_1_1_OFFS                                                              (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006204)
#define HWIO_ANTI_ROLLBACK_1_1_RMSK                                                              0xffffffff
#define HWIO_ANTI_ROLLBACK_1_1_IN          \
        in_dword_masked(HWIO_ANTI_ROLLBACK_1_1_ADDR, HWIO_ANTI_ROLLBACK_1_1_RMSK)
#define HWIO_ANTI_ROLLBACK_1_1_INM(m)      \
        in_dword_masked(HWIO_ANTI_ROLLBACK_1_1_ADDR, m)
#define HWIO_ANTI_ROLLBACK_1_1_XBL1_BMSK                                                         0xffffffff
#define HWIO_ANTI_ROLLBACK_1_1_XBL1_SHFT                                                                0x0

#define HWIO_ANTI_ROLLBACK_2_0_ADDR                                                              (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006208)
#define HWIO_ANTI_ROLLBACK_2_0_OFFS                                                              (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006208)
#define HWIO_ANTI_ROLLBACK_2_0_RMSK                                                              0xffffffff
#define HWIO_ANTI_ROLLBACK_2_0_IN          \
        in_dword_masked(HWIO_ANTI_ROLLBACK_2_0_ADDR, HWIO_ANTI_ROLLBACK_2_0_RMSK)
#define HWIO_ANTI_ROLLBACK_2_0_INM(m)      \
        in_dword_masked(HWIO_ANTI_ROLLBACK_2_0_ADDR, m)
#define HWIO_ANTI_ROLLBACK_2_0_PIL_SUBSYSTEM_31_0_BMSK                                           0xffffffff
#define HWIO_ANTI_ROLLBACK_2_0_PIL_SUBSYSTEM_31_0_SHFT                                                  0x0

#define HWIO_ANTI_ROLLBACK_2_1_ADDR                                                              (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000620c)
#define HWIO_ANTI_ROLLBACK_2_1_OFFS                                                              (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000620c)
#define HWIO_ANTI_ROLLBACK_2_1_RMSK                                                              0xffffffff
#define HWIO_ANTI_ROLLBACK_2_1_IN          \
        in_dword_masked(HWIO_ANTI_ROLLBACK_2_1_ADDR, HWIO_ANTI_ROLLBACK_2_1_RMSK)
#define HWIO_ANTI_ROLLBACK_2_1_INM(m)      \
        in_dword_masked(HWIO_ANTI_ROLLBACK_2_1_ADDR, m)
#define HWIO_ANTI_ROLLBACK_2_1_XBL_SEC_BMSK                                                      0xfe000000
#define HWIO_ANTI_ROLLBACK_2_1_XBL_SEC_SHFT                                                            0x19
#define HWIO_ANTI_ROLLBACK_2_1_RPM_BMSK                                                           0x1fe0000
#define HWIO_ANTI_ROLLBACK_2_1_RPM_SHFT                                                                0x11
#define HWIO_ANTI_ROLLBACK_2_1_TZ_BMSK                                                              0x1ffff
#define HWIO_ANTI_ROLLBACK_2_1_TZ_SHFT                                                                  0x0

#define HWIO_ANTI_ROLLBACK_3_0_ADDR                                                              (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006210)
#define HWIO_ANTI_ROLLBACK_3_0_OFFS                                                              (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006210)
#define HWIO_ANTI_ROLLBACK_3_0_RMSK                                                              0xffffffff
#define HWIO_ANTI_ROLLBACK_3_0_IN          \
        in_dword_masked(HWIO_ANTI_ROLLBACK_3_0_ADDR, HWIO_ANTI_ROLLBACK_3_0_RMSK)
#define HWIO_ANTI_ROLLBACK_3_0_INM(m)      \
        in_dword_masked(HWIO_ANTI_ROLLBACK_3_0_ADDR, m)
#define HWIO_ANTI_ROLLBACK_3_0_RSVD1_BMSK                                                        0xc0000000
#define HWIO_ANTI_ROLLBACK_3_0_RSVD1_SHFT                                                              0x1e
#define HWIO_ANTI_ROLLBACK_3_0_TQS_HASH_ACTIVE_BMSK                                              0x3e000000
#define HWIO_ANTI_ROLLBACK_3_0_TQS_HASH_ACTIVE_SHFT                                                    0x19
#define HWIO_ANTI_ROLLBACK_3_0_RPMB_KEY_PROVISIONED_BMSK                                          0x1000000
#define HWIO_ANTI_ROLLBACK_3_0_RPMB_KEY_PROVISIONED_SHFT                                               0x18
#define HWIO_ANTI_ROLLBACK_3_0_PIL_SUBSYSTEM_47_32_BMSK                                            0xffff00
#define HWIO_ANTI_ROLLBACK_3_0_PIL_SUBSYSTEM_47_32_SHFT                                                 0x8
#define HWIO_ANTI_ROLLBACK_3_0_SAFESWITCH_BMSK                                                         0xff
#define HWIO_ANTI_ROLLBACK_3_0_SAFESWITCH_SHFT                                                          0x0

#define HWIO_ANTI_ROLLBACK_3_1_ADDR                                                              (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006214)
#define HWIO_ANTI_ROLLBACK_3_1_OFFS                                                              (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006214)
#define HWIO_ANTI_ROLLBACK_3_1_RMSK                                                              0xffffffff
#define HWIO_ANTI_ROLLBACK_3_1_IN          \
        in_dword_masked(HWIO_ANTI_ROLLBACK_3_1_ADDR, HWIO_ANTI_ROLLBACK_3_1_RMSK)
#define HWIO_ANTI_ROLLBACK_3_1_INM(m)      \
        in_dword_masked(HWIO_ANTI_ROLLBACK_3_1_ADDR, m)
#define HWIO_ANTI_ROLLBACK_3_1_RSVD1_BMSK                                                        0xf0000000
#define HWIO_ANTI_ROLLBACK_3_1_RSVD1_SHFT                                                              0x1c
#define HWIO_ANTI_ROLLBACK_3_1_DEVICE_CFG_BMSK                                                    0xffe0000
#define HWIO_ANTI_ROLLBACK_3_1_DEVICE_CFG_SHFT                                                         0x11
#define HWIO_ANTI_ROLLBACK_3_1_DEBUG_POLICY_BMSK                                                    0x1f000
#define HWIO_ANTI_ROLLBACK_3_1_DEBUG_POLICY_SHFT                                                        0xc
#define HWIO_ANTI_ROLLBACK_3_1_HYPERVISOR_BMSK                                                        0xfff
#define HWIO_ANTI_ROLLBACK_3_1_HYPERVISOR_SHFT                                                          0x0

#define HWIO_ANTI_ROLLBACK_4_0_ADDR                                                              (SECURITY_CONTROL_CORE_REG_BASE      + 0x00006218)
#define HWIO_ANTI_ROLLBACK_4_0_OFFS                                                              (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x00006218)
#define HWIO_ANTI_ROLLBACK_4_0_RMSK                                                              0xffffffff
#define HWIO_ANTI_ROLLBACK_4_0_IN          \
        in_dword_masked(HWIO_ANTI_ROLLBACK_4_0_ADDR, HWIO_ANTI_ROLLBACK_4_0_RMSK)
#define HWIO_ANTI_ROLLBACK_4_0_INM(m)      \
        in_dword_masked(HWIO_ANTI_ROLLBACK_4_0_ADDR, m)
#define HWIO_ANTI_ROLLBACK_4_0_MSS_BMSK                                                          0xffff0000
#define HWIO_ANTI_ROLLBACK_4_0_MSS_SHFT                                                                0x10
#define HWIO_ANTI_ROLLBACK_4_0_MBA_BMSK                                                              0xffff
#define HWIO_ANTI_ROLLBACK_4_0_MBA_SHFT                                                                 0x0

#define HWIO_ANTI_ROLLBACK_4_1_ADDR                                                              (SECURITY_CONTROL_CORE_REG_BASE      + 0x0000621c)
#define HWIO_ANTI_ROLLBACK_4_1_OFFS                                                              (SECURITY_CONTROL_CORE_REG_BASE_OFFS + 0x0000621c)
#define HWIO_ANTI_ROLLBACK_4_1_RMSK                                                              0xffffffff
#define HWIO_ANTI_ROLLBACK_4_1_IN          \
        in_dword_masked(HWIO_ANTI_ROLLBACK_4_1_ADDR, HWIO_ANTI_ROLLBACK_4_1_RMSK)
#define HWIO_ANTI_ROLLBACK_4_1_INM(m)      \
        in_dword_masked(HWIO_ANTI_ROLLBACK_4_1_ADDR, m)
#define HWIO_ANTI_ROLLBACK_4_1_SIMLOCK_BMSK                                                      0x80000000
#define HWIO_ANTI_ROLLBACK_4_1_SIMLOCK_SHFT                                                            0x1f
#define HWIO_ANTI_ROLLBACK_4_1_RSVD0_BMSK                                                        0x7fffffff
#define HWIO_ANTI_ROLLBACK_4_1_RSVD0_SHFT                                                               0x0


#endif /* __CLOCKTURINGHWIO_H__ */
