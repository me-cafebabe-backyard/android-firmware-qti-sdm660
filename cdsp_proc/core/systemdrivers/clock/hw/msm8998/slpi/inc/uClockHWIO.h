#ifndef __UCLOCKHWIO_H__
#define __UCLOCKHWIO_H__
/*
===========================================================================
*/
/**
  @file uClockHWIO.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    MSM8998 (Nazgul) [nazgul_v1.0_p3q2r26.0]
 
  This file contains HWIO register definitions for the following modules:
    SSC_SCC_SCC_SCC_REG

  'Include' filters applied: 
  'Exclude' filters applied: RESERVED DUMMY 
*/
/*
  ===========================================================================

  Copyright (c) 2015 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  Qualcomm Confidential and Proprietary

  Export of this technology or software is regulated by the U.S. Government.
  Diversion contrary to U.S. law prohibited.

  All ideas, data and information contained in or disclosed by
  this document are confidential and proprietary information of
  Qualcomm Technologies Incorporated and all rights therein are expressly reserved.
  By accepting this material the recipient agrees that this material
  and the information contained therein are held in confidence and in
  trust and will not be used, copied, reproduced in whole or in part,
  nor its contents revealed in any manner to others without the express
  written permission of Qualcomm Technologies Incorporated.

  ===========================================================================

  $Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/clock/hw/msm8998/slpi/inc/uClockHWIO.h#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $

  ===========================================================================
*/

#include "msmhwiobase.h"

/*----------------------------------------------------------------------------
 * MODULE: SSC_SCC_SCC_SCC_REG
 *--------------------------------------------------------------------------*/

#define SSC_SCC_SCC_SCC_REG_REG_BASE                                                (SSC_BASE      + 0x00620000)
#define SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS                                           0x00620000

#define HWIO_SSC_SCC_SCC_PLL_MODE_ADDR                                              (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00000000)
#define HWIO_SSC_SCC_SCC_PLL_MODE_OFFS                                              (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00000000)
#define HWIO_SSC_SCC_SCC_PLL_MODE_RMSK                                              0xffffffff
#define HWIO_SSC_SCC_SCC_PLL_MODE_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_PLL_MODE_ADDR, HWIO_SSC_SCC_SCC_PLL_MODE_RMSK)
#define HWIO_SSC_SCC_SCC_PLL_MODE_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_PLL_MODE_ADDR, m)
#define HWIO_SSC_SCC_SCC_PLL_MODE_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_PLL_MODE_ADDR,v)
#define HWIO_SSC_SCC_SCC_PLL_MODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_PLL_MODE_ADDR,m,v,HWIO_SSC_SCC_SCC_PLL_MODE_IN)
#define HWIO_SSC_SCC_SCC_PLL_MODE_PLL_LOCK_DET_BMSK                                 0x80000000
#define HWIO_SSC_SCC_SCC_PLL_MODE_PLL_LOCK_DET_SHFT                                       0x1f
#define HWIO_SSC_SCC_SCC_PLL_MODE_PLL_ACTIVE_FLAG_BMSK                              0x40000000
#define HWIO_SSC_SCC_SCC_PLL_MODE_PLL_ACTIVE_FLAG_SHFT                                    0x1e
#define HWIO_SSC_SCC_SCC_PLL_MODE_PLL_ACK_LATCH_BMSK                                0x20000000
#define HWIO_SSC_SCC_SCC_PLL_MODE_PLL_ACK_LATCH_SHFT                                      0x1d
#define HWIO_SSC_SCC_SCC_PLL_MODE_PLL_LOCK_DET_FINE_BMSK                            0x10000000
#define HWIO_SSC_SCC_SCC_PLL_MODE_PLL_LOCK_DET_FINE_SHFT                                  0x1c
#define HWIO_SSC_SCC_SCC_PLL_MODE_RESERVE_BITS27_24_BMSK                             0xf000000
#define HWIO_SSC_SCC_SCC_PLL_MODE_RESERVE_BITS27_24_SHFT                                  0x18
#define HWIO_SSC_SCC_SCC_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_BMSK                     0x800000
#define HWIO_SSC_SCC_SCC_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_SHFT                         0x17
#define HWIO_SSC_SCC_SCC_PLL_MODE_PLL_UPDATE_BMSK                                     0x400000
#define HWIO_SSC_SCC_SCC_PLL_MODE_PLL_UPDATE_SHFT                                         0x16
#define HWIO_SSC_SCC_SCC_PLL_MODE_PLL_VOTE_FSM_RESET_BMSK                             0x200000
#define HWIO_SSC_SCC_SCC_PLL_MODE_PLL_VOTE_FSM_RESET_SHFT                                 0x15
#define HWIO_SSC_SCC_SCC_PLL_MODE_PLL_VOTE_FSM_ENA_BMSK                               0x100000
#define HWIO_SSC_SCC_SCC_PLL_MODE_PLL_VOTE_FSM_ENA_SHFT                                   0x14
#define HWIO_SSC_SCC_SCC_PLL_MODE_PLL_BIAS_COUNT_BMSK                                  0xfc000
#define HWIO_SSC_SCC_SCC_PLL_MODE_PLL_BIAS_COUNT_SHFT                                      0xe
#define HWIO_SSC_SCC_SCC_PLL_MODE_PLL_LOCK_COUNT_BMSK                                   0x3f00
#define HWIO_SSC_SCC_SCC_PLL_MODE_PLL_LOCK_COUNT_SHFT                                      0x8
#define HWIO_SSC_SCC_SCC_PLL_MODE_RESERVE_BITS7_3_BMSK                                    0xf8
#define HWIO_SSC_SCC_SCC_PLL_MODE_RESERVE_BITS7_3_SHFT                                     0x3
#define HWIO_SSC_SCC_SCC_PLL_MODE_PLL_RESET_N_BMSK                                         0x4
#define HWIO_SSC_SCC_SCC_PLL_MODE_PLL_RESET_N_SHFT                                         0x2
#define HWIO_SSC_SCC_SCC_PLL_MODE_RESERVE_BIT1_BMSK                                        0x2
#define HWIO_SSC_SCC_SCC_PLL_MODE_RESERVE_BIT1_SHFT                                        0x1
#define HWIO_SSC_SCC_SCC_PLL_MODE_PLL_OUTCTRL_BMSK                                         0x1
#define HWIO_SSC_SCC_SCC_PLL_MODE_PLL_OUTCTRL_SHFT                                         0x0

#define HWIO_SSC_SCC_SCC_PLL_L_VAL_ADDR                                             (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00000004)
#define HWIO_SSC_SCC_SCC_PLL_L_VAL_OFFS                                             (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00000004)
#define HWIO_SSC_SCC_SCC_PLL_L_VAL_RMSK                                                 0xffff
#define HWIO_SSC_SCC_SCC_PLL_L_VAL_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_PLL_L_VAL_ADDR, HWIO_SSC_SCC_SCC_PLL_L_VAL_RMSK)
#define HWIO_SSC_SCC_SCC_PLL_L_VAL_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_PLL_L_VAL_ADDR, m)
#define HWIO_SSC_SCC_SCC_PLL_L_VAL_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_PLL_L_VAL_ADDR,v)
#define HWIO_SSC_SCC_SCC_PLL_L_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_PLL_L_VAL_ADDR,m,v,HWIO_SSC_SCC_SCC_PLL_L_VAL_IN)
#define HWIO_SSC_SCC_SCC_PLL_L_VAL_PLL_L_BMSK                                           0xffff
#define HWIO_SSC_SCC_SCC_PLL_L_VAL_PLL_L_SHFT                                              0x0

#define HWIO_SSC_SCC_SCC_PLL_CAL_L_VAL_ADDR                                         (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00000008)
#define HWIO_SSC_SCC_SCC_PLL_CAL_L_VAL_OFFS                                         (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00000008)
#define HWIO_SSC_SCC_SCC_PLL_CAL_L_VAL_RMSK                                             0xffff
#define HWIO_SSC_SCC_SCC_PLL_CAL_L_VAL_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_PLL_CAL_L_VAL_ADDR, HWIO_SSC_SCC_SCC_PLL_CAL_L_VAL_RMSK)
#define HWIO_SSC_SCC_SCC_PLL_CAL_L_VAL_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_PLL_CAL_L_VAL_ADDR, m)
#define HWIO_SSC_SCC_SCC_PLL_CAL_L_VAL_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_PLL_CAL_L_VAL_ADDR,v)
#define HWIO_SSC_SCC_SCC_PLL_CAL_L_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_PLL_CAL_L_VAL_ADDR,m,v,HWIO_SSC_SCC_SCC_PLL_CAL_L_VAL_IN)
#define HWIO_SSC_SCC_SCC_PLL_CAL_L_VAL_PLL_CAL_L_BMSK                                   0xffff
#define HWIO_SSC_SCC_SCC_PLL_CAL_L_VAL_PLL_CAL_L_SHFT                                      0x0

#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_ADDR                                          (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x0000000c)
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_OFFS                                          (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x0000000c)
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_RMSK                                          0xffffffff
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_PLL_USER_CTL_ADDR, HWIO_SSC_SCC_SCC_PLL_USER_CTL_RMSK)
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_PLL_USER_CTL_ADDR, m)
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_PLL_USER_CTL_ADDR,v)
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_PLL_USER_CTL_ADDR,m,v,HWIO_SSC_SCC_SCC_PLL_USER_CTL_IN)
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_RESERVE_BITS31_19_BMSK                        0xfff80000
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_RESERVE_BITS31_19_SHFT                              0x13
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_PRE_DIV_RATIO_BMSK                               0x70000
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_PRE_DIV_RATIO_SHFT                                  0x10
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_POST_DIV_RATIO_ODD_BMSK                           0xf000
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_POST_DIV_RATIO_ODD_SHFT                              0xc
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_POST_DIV_RATIO_EVEN_BMSK                           0xf00
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_POST_DIV_RATIO_EVEN_SHFT                             0x8
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_OUT_CLK_POLARITY_BMSK                               0x80
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_OUT_CLK_POLARITY_SHFT                                0x7
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_RESERVE_BITS6_5_BMSK                                0x60
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_RESERVE_BITS6_5_SHFT                                 0x5
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_PLLOUT_TEST_BMSK                                    0x10
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_PLLOUT_TEST_SHFT                                     0x4
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_RESERVE_BIT3_BMSK                                    0x8
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_RESERVE_BIT3_SHFT                                    0x3
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_PLLOUT_ODD_BMSK                                      0x4
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_PLLOUT_ODD_SHFT                                      0x2
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_PLLOUT_EVEN_BMSK                                     0x2
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_PLLOUT_EVEN_SHFT                                     0x1
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_PLLOUT_MAIN_BMSK                                     0x1
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_PLLOUT_MAIN_SHFT                                     0x0

#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_ADDR                                        (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00000010)
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_OFFS                                        (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00000010)
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_RMSK                                        0xffffffff
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_ADDR, HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_RMSK)
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_ADDR, m)
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_ADDR,v)
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_ADDR,m,v,HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_IN)
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_RESERVE_BITS31_19_BMSK                      0xfff80000
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_RESERVE_BITS31_19_SHFT                            0x13
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_USE_PREDIV_WHEN_CAL_BMSK                       0x40000
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_USE_PREDIV_WHEN_CAL_SHFT                          0x12
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_USE_EXT_SAVERESTORE_BMSK                       0x20000
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_USE_EXT_SAVERESTORE_SHFT                          0x11
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_LOW_JITTER_MODE_EN_BMSK                        0x10000
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_LOW_JITTER_MODE_EN_SHFT                           0x10
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_FRAC_FORMAT_SEL_BMSK                            0x8000
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_FRAC_FORMAT_SEL_SHFT                               0xf
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_BIAS_ON_IN_STANDBY_BMSK                         0x4000
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_BIAS_ON_IN_STANDBY_SHFT                            0xe
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_REF_CLK_AT_OUT_BMSK                             0x2000
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_REF_CLK_AT_OUT_SHFT                                0xd
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_SCALE_FREQ_ON_RESTART_BMSK                      0x1800
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_SCALE_FREQ_ON_RESTART_SHFT                         0xb
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_LATCH_INTERFACE_BYPASS_BMSK                      0x400
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_LATCH_INTERFACE_BYPASS_SHFT                        0xa
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_STATUS_REGISTER_BMSK                             0x3e0
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_STATUS_REGISTER_SHFT                               0x5
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_WRITE_STATE_EN_BMSK                               0x10
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_WRITE_STATE_EN_SHFT                                0x4
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_CALIB_CTRL_BMSK                                    0xe
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_CALIB_CTRL_SHFT                                    0x1
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_USE_ONLY_FINE_LOCK_DET_BMSK                        0x1
#define HWIO_SSC_SCC_SCC_PLL_USER_CTL_U_USE_ONLY_FINE_LOCK_DET_SHFT                        0x0

#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_ADDR                                        (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00000014)
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_OFFS                                        (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00000014)
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_RMSK                                        0xffffffff
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_ADDR, HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_RMSK)
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_ADDR, m)
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_ADDR,v)
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_ADDR,m,v,HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_IN)
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_FINE_LDC_THRESHOLD_BMSK                     0xfc000000
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_FINE_LDC_THRESHOLD_SHFT                           0x1a
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_COARSE_LDC_THRESHOLD_BMSK                    0x3c00000
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_COARSE_LDC_THRESHOLD_SHFT                         0x16
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_COARSE_LOCK_DET_NEG_THRESHOLD_BMSK            0x3c0000
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_COARSE_LOCK_DET_NEG_THRESHOLD_SHFT                0x12
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_COARSE_LOCK_DET_POS_THRESHOLD_BMSK             0x3c000
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_COARSE_LOCK_DET_POS_THRESHOLD_SHFT                 0xe
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_FINE_LOCK_DET_THRESHOLD_BMSK                    0x3800
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_FINE_LOCK_DET_THRESHOLD_SHFT                       0xb
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_FINE_LOCK_DET_SAMPLE_SIZE_BMSK                   0x700
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_FINE_LOCK_DET_SAMPLE_SIZE_SHFT                     0x8
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_FWD_GAIN_SLEWING_KFN_BMSK                         0xf0
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_FWD_GAIN_SLEWING_KFN_SHFT                          0x4
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_FWD_GAIN_KFN_BMSK                                  0xf
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_FWD_GAIN_KFN_SHFT                                  0x0

#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_U_ADDR                                      (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00000018)
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_U_OFFS                                      (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00000018)
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_U_RMSK                                      0xffffffff
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_U_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_U_ADDR, HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_U_RMSK)
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_U_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_U_ADDR, m)
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_U_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_U_ADDR,v)
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_U_ADDR,m,v,HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_U_IN)
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_U_BIST_CFG_BMSK                             0xfff00000
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_U_BIST_CFG_SHFT                                   0x14
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_U_RESERVE_BITS19_12_BMSK                       0xff000
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_U_RESERVE_BITS19_12_SHFT                           0xc
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_U_NUM_STEPS_FAST_LOCK_BMSK                       0xc00
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_U_NUM_STEPS_FAST_LOCK_SHFT                         0xa
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_U_PREDIV_WHEN_CAL_BMSK                           0x380
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_U_PREDIV_WHEN_CAL_SHFT                             0x7
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_U_INC_MIN_GLITCH_THRESHOLD_4X_BMSK                0x40
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_U_INC_MIN_GLITCH_THRESHOLD_4X_SHFT                 0x6
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_U_MIN_GLITCH_THRESHOLD_BMSK                       0x30
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_U_MIN_GLITCH_THRESHOLD_SHFT                        0x4
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_U_USE_BOTH_REF_CLK_EDGE_BMSK                       0x8
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_U_USE_BOTH_REF_CLK_EDGE_SHFT                       0x3
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_U_BIAS_WARMUP_TIME_BMSK                            0x6
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_U_BIAS_WARMUP_TIME_SHFT                            0x1
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_U_DIV_LOCK_DET_THRESHOLDS_BMSK                     0x1
#define HWIO_SSC_SCC_SCC_PLL_CONFIG_CTL_U_DIV_LOCK_DET_THRESHOLDS_SHFT                     0x0

#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_ADDR                                          (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x0000001c)
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_OFFS                                          (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x0000001c)
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_RMSK                                          0xffffffff
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_PLL_TEST_CTL_ADDR, HWIO_SSC_SCC_SCC_PLL_TEST_CTL_RMSK)
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_PLL_TEST_CTL_ADDR, m)
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_PLL_TEST_CTL_ADDR,v)
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_PLL_TEST_CTL_ADDR,m,v,HWIO_SSC_SCC_SCC_PLL_TEST_CTL_IN)
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_ADD_REF_CYC_CALIB_STEPS_BMSK                  0xc0000000
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_ADD_REF_CYC_CALIB_STEPS_SHFT                        0x1e
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_GLITCH_DETECTOR_COUNT_LIMIT_BMSK              0x30000000
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_GLITCH_DETECTOR_COUNT_LIMIT_SHFT                    0x1c
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_GLITCH_PREVENTION_DIS_BMSK                     0x8000000
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_GLITCH_PREVENTION_DIS_SHFT                          0x1b
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_FINE_FCW_BMSK                                  0x7e00000
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_FINE_FCW_SHFT                                       0x15
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_OVERRIDE_FINE_FCW_BMSK                          0x100000
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_OVERRIDE_FINE_FCW_SHFT                              0x14
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_COARSE_FCW_BMSK                                  0xff000
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_COARSE_FCW_SHFT                                      0xc
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_OVERRIDE_COARSE_FCW_BMSK                           0x800
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_OVERRIDE_COARSE_FCW_SHFT                             0xb
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_PROCESS_CALIB_WORD_BMSK                            0x700
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_PROCESS_CALIB_WORD_SHFT                              0x8
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_OVERRIDE_CALIB_WORD_BMSK                            0x80
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_OVERRIDE_CALIB_WORD_SHFT                             0x7
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_DISABLE_LFSR_BMSK                                   0x40
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_DISABLE_LFSR_SHFT                                    0x6
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_ATEST1_SEL_BMSK                                     0x30
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_ATEST1_SEL_SHFT                                      0x4
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_ATEST0_SEL_BMSK                                      0xc
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_ATEST0_SEL_SHFT                                      0x2
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_ATEST1_EN_BMSK                                       0x2
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_ATEST1_EN_SHFT                                       0x1
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_ATEST0_EN_BMSK                                       0x1
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_ATEST0_EN_SHFT                                       0x0

#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_ADDR                                        (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00000020)
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_OFFS                                        (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00000020)
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_RMSK                                        0xffffffff
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_ADDR, HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_RMSK)
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_ADDR, m)
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_ADDR,v)
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_ADDR,m,v,HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_IN)
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_ENABLE_TRAINING_SEQ_BMSK                    0x80000000
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_ENABLE_TRAINING_SEQ_SHFT                          0x1f
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_BYPASS_LOGIC_DEP_BMSK                       0x40000000
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_BYPASS_LOGIC_DEP_SHFT                             0x1e
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_BYPASS_BIAS_DET_BMSK                        0x20000000
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_BYPASS_BIAS_DET_SHFT                              0x1d
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_MSB_CLOCK_SELECT_BMSK                       0x10000000
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_MSB_CLOCK_SELECT_SHFT                             0x1c
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_BYPASS_FIRST_ORDER_DSM_BMSK                  0x8000000
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_BYPASS_FIRST_ORDER_DSM_SHFT                       0x1b
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_DCO_OFFSET_CURRENT_ADJUST_BMSK               0x6000000
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_DCO_OFFSET_CURRENT_ADJUST_SHFT                    0x19
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_MIRROR_DEVICE_ADJUST_BMSK                    0x1c00000
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_MIRROR_DEVICE_ADJUST_SHFT                         0x16
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_BIAS_STARTUP_CIR_DIS_BMSK                     0x200000
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_BIAS_STARTUP_CIR_DIS_SHFT                         0x15
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_DISABLE_CLAMP_BMSK                            0x100000
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_DISABLE_CLAMP_SHFT                                0x14
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_BYPASS_MODE_OF_BIAS_BMSK                       0x80000
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_BYPASS_MODE_OF_BIAS_SHFT                          0x13
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_BYPASS_MODE_FOR_BIAS_EN_BMSK                   0x40000
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_BYPASS_MODE_FOR_BIAS_EN_SHFT                      0x12
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_BIAS_ADJUST_BMSK                               0x30000
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_BIAS_ADJUST_SHFT                                  0x10
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_DIV2_NMO_EN_BMSK                                0x8000
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_DIV2_NMO_EN_SHFT                                   0xf
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_DIS_LEAK_CMP_BMSK                               0x4000
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_DIS_LEAK_CMP_SHFT                                  0xe
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_SINGLE_DMET_EN_BMSK                             0x2000
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_SINGLE_DMET_EN_SHFT                                0xd
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_DEMET_WINDOW_DIS_BMSK                           0x1000
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_DEMET_WINDOW_DIS_SHFT                              0xc
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_NMO_OSC_SEL_BMSK                                 0xc00
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_NMO_OSC_SEL_SHFT                                   0xa
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_NOISE_MAG_BMSK                                   0x380
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_NOISE_MAG_SHFT                                     0x7
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_NOISE_GEN_EN_BMSK                                 0x40
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_NOISE_GEN_EN_SHFT                                  0x6
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_OSC_BIAS_GND_BMSK                                 0x20
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_OSC_BIAS_GND_SHFT                                  0x5
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_PLL_TEST_OUT_SEL_BMSK                             0x18
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_PLL_TEST_OUT_SEL_SHFT                              0x3
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_STATUS_REG_EN_BMSK                                 0x4
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_STATUS_REG_EN_SHFT                                 0x2
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_SKIP_FINE_TUNE_BMSK                                0x2
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_SKIP_FINE_TUNE_SHFT                                0x1
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_SKIP_FAST_LOCK_BMSK                                0x1
#define HWIO_SSC_SCC_SCC_PLL_TEST_CTL_U_SKIP_FAST_LOCK_SHFT                                0x0

#define HWIO_SSC_SCC_SCC_PLL_STATUS_ADDR                                            (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00000024)
#define HWIO_SSC_SCC_SCC_PLL_STATUS_OFFS                                            (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00000024)
#define HWIO_SSC_SCC_SCC_PLL_STATUS_RMSK                                            0xffffffff
#define HWIO_SSC_SCC_SCC_PLL_STATUS_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_PLL_STATUS_ADDR, HWIO_SSC_SCC_SCC_PLL_STATUS_RMSK)
#define HWIO_SSC_SCC_SCC_PLL_STATUS_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_PLL_STATUS_ADDR, m)
#define HWIO_SSC_SCC_SCC_PLL_STATUS_STATUS_31_0_BMSK                                0xffffffff
#define HWIO_SSC_SCC_SCC_PLL_STATUS_STATUS_31_0_SHFT                                       0x0

#define HWIO_SSC_SCC_SCC_PLL_FREQ_CTL_ADDR                                          (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00000028)
#define HWIO_SSC_SCC_SCC_PLL_FREQ_CTL_OFFS                                          (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00000028)
#define HWIO_SSC_SCC_SCC_PLL_FREQ_CTL_RMSK                                          0xffffffff
#define HWIO_SSC_SCC_SCC_PLL_FREQ_CTL_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_PLL_FREQ_CTL_ADDR, HWIO_SSC_SCC_SCC_PLL_FREQ_CTL_RMSK)
#define HWIO_SSC_SCC_SCC_PLL_FREQ_CTL_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_PLL_FREQ_CTL_ADDR, m)
#define HWIO_SSC_SCC_SCC_PLL_FREQ_CTL_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_PLL_FREQ_CTL_ADDR,v)
#define HWIO_SSC_SCC_SCC_PLL_FREQ_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_PLL_FREQ_CTL_ADDR,m,v,HWIO_SSC_SCC_SCC_PLL_FREQ_CTL_IN)
#define HWIO_SSC_SCC_SCC_PLL_FREQ_CTL_FREQUENCY_CTL_WORD_BMSK                       0xffffffff
#define HWIO_SSC_SCC_SCC_PLL_FREQ_CTL_FREQUENCY_CTL_WORD_SHFT                              0x0

#define HWIO_SSC_SCC_SCC_PLL_OPMODE_ADDR                                            (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x0000002c)
#define HWIO_SSC_SCC_SCC_PLL_OPMODE_OFFS                                            (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x0000002c)
#define HWIO_SSC_SCC_SCC_PLL_OPMODE_RMSK                                                   0x7
#define HWIO_SSC_SCC_SCC_PLL_OPMODE_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_PLL_OPMODE_ADDR, HWIO_SSC_SCC_SCC_PLL_OPMODE_RMSK)
#define HWIO_SSC_SCC_SCC_PLL_OPMODE_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_PLL_OPMODE_ADDR, m)
#define HWIO_SSC_SCC_SCC_PLL_OPMODE_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_PLL_OPMODE_ADDR,v)
#define HWIO_SSC_SCC_SCC_PLL_OPMODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_PLL_OPMODE_ADDR,m,v,HWIO_SSC_SCC_SCC_PLL_OPMODE_IN)
#define HWIO_SSC_SCC_SCC_PLL_OPMODE_PLL_OPMODE_BMSK                                        0x7
#define HWIO_SSC_SCC_SCC_PLL_OPMODE_PLL_OPMODE_SHFT                                        0x0

#define HWIO_SSC_SCC_SCC_PLL_STATE_ADDR                                             (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00000030)
#define HWIO_SSC_SCC_SCC_PLL_STATE_OFFS                                             (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00000030)
#define HWIO_SSC_SCC_SCC_PLL_STATE_RMSK                                                    0x7
#define HWIO_SSC_SCC_SCC_PLL_STATE_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_PLL_STATE_ADDR, HWIO_SSC_SCC_SCC_PLL_STATE_RMSK)
#define HWIO_SSC_SCC_SCC_PLL_STATE_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_PLL_STATE_ADDR, m)
#define HWIO_SSC_SCC_SCC_PLL_STATE_PLL_STATE_BMSK                                          0x7
#define HWIO_SSC_SCC_SCC_PLL_STATE_PLL_STATE_SHFT                                          0x0

#define HWIO_SSC_SCC_SCC_PLL_DROOP_ADDR                                             (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00000034)
#define HWIO_SSC_SCC_SCC_PLL_DROOP_OFFS                                             (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00000034)
#define HWIO_SSC_SCC_SCC_PLL_DROOP_RMSK                                                   0xff
#define HWIO_SSC_SCC_SCC_PLL_DROOP_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_PLL_DROOP_ADDR, HWIO_SSC_SCC_SCC_PLL_DROOP_RMSK)
#define HWIO_SSC_SCC_SCC_PLL_DROOP_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_PLL_DROOP_ADDR, m)
#define HWIO_SSC_SCC_SCC_PLL_DROOP_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_PLL_DROOP_ADDR,v)
#define HWIO_SSC_SCC_SCC_PLL_DROOP_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_PLL_DROOP_ADDR,m,v,HWIO_SSC_SCC_SCC_PLL_DROOP_IN)
#define HWIO_SSC_SCC_SCC_PLL_DROOP_DROOP_CODE_BMSK                                        0xfe
#define HWIO_SSC_SCC_SCC_PLL_DROOP_DROOP_CODE_SHFT                                         0x1
#define HWIO_SSC_SCC_SCC_PLL_DROOP_DROOP_EN_BMSK                                           0x1
#define HWIO_SSC_SCC_SCC_PLL_DROOP_DROOP_EN_SHFT                                           0x0

#define HWIO_SSC_SCC_SCC_PLL_FRAC_VAL_ADDR                                          (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00000038)
#define HWIO_SSC_SCC_SCC_PLL_FRAC_VAL_OFFS                                          (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00000038)
#define HWIO_SSC_SCC_SCC_PLL_FRAC_VAL_RMSK                                              0xffff
#define HWIO_SSC_SCC_SCC_PLL_FRAC_VAL_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_PLL_FRAC_VAL_ADDR, HWIO_SSC_SCC_SCC_PLL_FRAC_VAL_RMSK)
#define HWIO_SSC_SCC_SCC_PLL_FRAC_VAL_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_PLL_FRAC_VAL_ADDR, m)
#define HWIO_SSC_SCC_SCC_PLL_FRAC_VAL_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_PLL_FRAC_VAL_ADDR,v)
#define HWIO_SSC_SCC_SCC_PLL_FRAC_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_PLL_FRAC_VAL_ADDR,m,v,HWIO_SSC_SCC_SCC_PLL_FRAC_VAL_IN)
#define HWIO_SSC_SCC_SCC_PLL_FRAC_VAL_PLL_FRAC_VAL_BMSK                                 0xffff
#define HWIO_SSC_SCC_SCC_PLL_FRAC_VAL_PLL_FRAC_VAL_SHFT                                    0x0

#define HWIO_SSC_SCC_SCC_PLL_SPARE_ADDR                                             (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x0000003c)
#define HWIO_SSC_SCC_SCC_PLL_SPARE_OFFS                                             (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x0000003c)
#define HWIO_SSC_SCC_SCC_PLL_SPARE_RMSK                                                   0xff
#define HWIO_SSC_SCC_SCC_PLL_SPARE_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_PLL_SPARE_ADDR, HWIO_SSC_SCC_SCC_PLL_SPARE_RMSK)
#define HWIO_SSC_SCC_SCC_PLL_SPARE_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_PLL_SPARE_ADDR, m)
#define HWIO_SSC_SCC_SCC_PLL_SPARE_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_PLL_SPARE_ADDR,v)
#define HWIO_SSC_SCC_SCC_PLL_SPARE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_PLL_SPARE_ADDR,m,v,HWIO_SSC_SCC_SCC_PLL_SPARE_IN)
#define HWIO_SSC_SCC_SCC_PLL_SPARE_SPARE_OUTPUTS_BMSK                                     0xf0
#define HWIO_SSC_SCC_SCC_PLL_SPARE_SPARE_OUTPUTS_SHFT                                      0x4
#define HWIO_SSC_SCC_SCC_PLL_SPARE_SPARE_INPUTS_BMSK                                       0xf
#define HWIO_SSC_SCC_SCC_PLL_SPARE_SPARE_INPUTS_SHFT                                       0x0

#define HWIO_SSC_SCC_SCC_100M_CMD_RCGR_ADDR                                         (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00001000)
#define HWIO_SSC_SCC_SCC_100M_CMD_RCGR_OFFS                                         (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00001000)
#define HWIO_SSC_SCC_SCC_100M_CMD_RCGR_RMSK                                         0x80000013
#define HWIO_SSC_SCC_SCC_100M_CMD_RCGR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_100M_CMD_RCGR_ADDR, HWIO_SSC_SCC_SCC_100M_CMD_RCGR_RMSK)
#define HWIO_SSC_SCC_SCC_100M_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_100M_CMD_RCGR_ADDR, m)
#define HWIO_SSC_SCC_SCC_100M_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_100M_CMD_RCGR_ADDR,v)
#define HWIO_SSC_SCC_SCC_100M_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_100M_CMD_RCGR_ADDR,m,v,HWIO_SSC_SCC_SCC_100M_CMD_RCGR_IN)
#define HWIO_SSC_SCC_SCC_100M_CMD_RCGR_ROOT_OFF_BMSK                                0x80000000
#define HWIO_SSC_SCC_SCC_100M_CMD_RCGR_ROOT_OFF_SHFT                                      0x1f
#define HWIO_SSC_SCC_SCC_100M_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                0x10
#define HWIO_SSC_SCC_SCC_100M_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                 0x4
#define HWIO_SSC_SCC_SCC_100M_CMD_RCGR_ROOT_EN_BMSK                                        0x2
#define HWIO_SSC_SCC_SCC_100M_CMD_RCGR_ROOT_EN_SHFT                                        0x1
#define HWIO_SSC_SCC_SCC_100M_CMD_RCGR_UPDATE_BMSK                                         0x1
#define HWIO_SSC_SCC_SCC_100M_CMD_RCGR_UPDATE_SHFT                                         0x0

#define HWIO_SSC_SCC_SCC_100M_CFG_RCGR_ADDR                                         (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00001004)
#define HWIO_SSC_SCC_SCC_100M_CFG_RCGR_OFFS                                         (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00001004)
#define HWIO_SSC_SCC_SCC_100M_CFG_RCGR_RMSK                                              0x71f
#define HWIO_SSC_SCC_SCC_100M_CFG_RCGR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_100M_CFG_RCGR_ADDR, HWIO_SSC_SCC_SCC_100M_CFG_RCGR_RMSK)
#define HWIO_SSC_SCC_SCC_100M_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_100M_CFG_RCGR_ADDR, m)
#define HWIO_SSC_SCC_SCC_100M_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_100M_CFG_RCGR_ADDR,v)
#define HWIO_SSC_SCC_SCC_100M_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_100M_CFG_RCGR_ADDR,m,v,HWIO_SSC_SCC_SCC_100M_CFG_RCGR_IN)
#define HWIO_SSC_SCC_SCC_100M_CFG_RCGR_SRC_SEL_BMSK                                      0x700
#define HWIO_SSC_SCC_SCC_100M_CFG_RCGR_SRC_SEL_SHFT                                        0x8
#define HWIO_SSC_SCC_SCC_100M_CFG_RCGR_SRC_DIV_BMSK                                       0x1f
#define HWIO_SSC_SCC_SCC_100M_CFG_RCGR_SRC_DIV_SHFT                                        0x0

#define HWIO_SSC_SCC_SCC_SPI_I2C1_BCR_ADDR                                          (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00002000)
#define HWIO_SSC_SCC_SCC_SPI_I2C1_BCR_OFFS                                          (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00002000)
#define HWIO_SSC_SCC_SCC_SPI_I2C1_BCR_RMSK                                                 0x1
#define HWIO_SSC_SCC_SCC_SPI_I2C1_BCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_SPI_I2C1_BCR_ADDR, HWIO_SSC_SCC_SCC_SPI_I2C1_BCR_RMSK)
#define HWIO_SSC_SCC_SCC_SPI_I2C1_BCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_SPI_I2C1_BCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_SPI_I2C1_BCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_SPI_I2C1_BCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_SPI_I2C1_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_SPI_I2C1_BCR_ADDR,m,v,HWIO_SSC_SCC_SCC_SPI_I2C1_BCR_IN)
#define HWIO_SSC_SCC_SCC_SPI_I2C1_BCR_BLK_ARES_BMSK                                        0x1
#define HWIO_SSC_SCC_SCC_SPI_I2C1_BCR_BLK_ARES_SHFT                                        0x0

#define HWIO_SSC_SCC_SCC_QUP_SPI1_CBCR_ADDR                                         (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00002008)
#define HWIO_SSC_SCC_SCC_QUP_SPI1_CBCR_OFFS                                         (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00002008)
#define HWIO_SSC_SCC_SCC_QUP_SPI1_CBCR_RMSK                                         0x80000001
#define HWIO_SSC_SCC_SCC_QUP_SPI1_CBCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_QUP_SPI1_CBCR_ADDR, HWIO_SSC_SCC_SCC_QUP_SPI1_CBCR_RMSK)
#define HWIO_SSC_SCC_SCC_QUP_SPI1_CBCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_QUP_SPI1_CBCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_QUP_SPI1_CBCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_QUP_SPI1_CBCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_QUP_SPI1_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_QUP_SPI1_CBCR_ADDR,m,v,HWIO_SSC_SCC_SCC_QUP_SPI1_CBCR_IN)
#define HWIO_SSC_SCC_SCC_QUP_SPI1_CBCR_CLK_OFF_BMSK                                 0x80000000
#define HWIO_SSC_SCC_SCC_QUP_SPI1_CBCR_CLK_OFF_SHFT                                       0x1f
#define HWIO_SSC_SCC_SCC_QUP_SPI1_CBCR_CLK_ENABLE_BMSK                                     0x1
#define HWIO_SSC_SCC_SCC_QUP_SPI1_CBCR_CLK_ENABLE_SHFT                                     0x0

#define HWIO_SSC_SCC_SCC_QUP_I2C1_CBCR_ADDR                                         (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x0000200c)
#define HWIO_SSC_SCC_SCC_QUP_I2C1_CBCR_OFFS                                         (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x0000200c)
#define HWIO_SSC_SCC_SCC_QUP_I2C1_CBCR_RMSK                                         0x80000001
#define HWIO_SSC_SCC_SCC_QUP_I2C1_CBCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_QUP_I2C1_CBCR_ADDR, HWIO_SSC_SCC_SCC_QUP_I2C1_CBCR_RMSK)
#define HWIO_SSC_SCC_SCC_QUP_I2C1_CBCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_QUP_I2C1_CBCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_QUP_I2C1_CBCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_QUP_I2C1_CBCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_QUP_I2C1_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_QUP_I2C1_CBCR_ADDR,m,v,HWIO_SSC_SCC_SCC_QUP_I2C1_CBCR_IN)
#define HWIO_SSC_SCC_SCC_QUP_I2C1_CBCR_CLK_OFF_BMSK                                 0x80000000
#define HWIO_SSC_SCC_SCC_QUP_I2C1_CBCR_CLK_OFF_SHFT                                       0x1f
#define HWIO_SSC_SCC_SCC_QUP_I2C1_CBCR_CLK_ENABLE_BMSK                                     0x1
#define HWIO_SSC_SCC_SCC_QUP_I2C1_CBCR_CLK_ENABLE_SHFT                                     0x0

#define HWIO_SSC_SCC_SCC_SPI_I2C2_BCR_ADDR                                          (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00003000)
#define HWIO_SSC_SCC_SCC_SPI_I2C2_BCR_OFFS                                          (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00003000)
#define HWIO_SSC_SCC_SCC_SPI_I2C2_BCR_RMSK                                                 0x1
#define HWIO_SSC_SCC_SCC_SPI_I2C2_BCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_SPI_I2C2_BCR_ADDR, HWIO_SSC_SCC_SCC_SPI_I2C2_BCR_RMSK)
#define HWIO_SSC_SCC_SCC_SPI_I2C2_BCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_SPI_I2C2_BCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_SPI_I2C2_BCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_SPI_I2C2_BCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_SPI_I2C2_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_SPI_I2C2_BCR_ADDR,m,v,HWIO_SSC_SCC_SCC_SPI_I2C2_BCR_IN)
#define HWIO_SSC_SCC_SCC_SPI_I2C2_BCR_BLK_ARES_BMSK                                        0x1
#define HWIO_SSC_SCC_SCC_SPI_I2C2_BCR_BLK_ARES_SHFT                                        0x0

#define HWIO_SSC_SCC_SCC_QUP_SPI2_CBCR_ADDR                                         (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00003008)
#define HWIO_SSC_SCC_SCC_QUP_SPI2_CBCR_OFFS                                         (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00003008)
#define HWIO_SSC_SCC_SCC_QUP_SPI2_CBCR_RMSK                                         0x80000001
#define HWIO_SSC_SCC_SCC_QUP_SPI2_CBCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_QUP_SPI2_CBCR_ADDR, HWIO_SSC_SCC_SCC_QUP_SPI2_CBCR_RMSK)
#define HWIO_SSC_SCC_SCC_QUP_SPI2_CBCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_QUP_SPI2_CBCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_QUP_SPI2_CBCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_QUP_SPI2_CBCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_QUP_SPI2_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_QUP_SPI2_CBCR_ADDR,m,v,HWIO_SSC_SCC_SCC_QUP_SPI2_CBCR_IN)
#define HWIO_SSC_SCC_SCC_QUP_SPI2_CBCR_CLK_OFF_BMSK                                 0x80000000
#define HWIO_SSC_SCC_SCC_QUP_SPI2_CBCR_CLK_OFF_SHFT                                       0x1f
#define HWIO_SSC_SCC_SCC_QUP_SPI2_CBCR_CLK_ENABLE_BMSK                                     0x1
#define HWIO_SSC_SCC_SCC_QUP_SPI2_CBCR_CLK_ENABLE_SHFT                                     0x0

#define HWIO_SSC_SCC_SCC_QUP_I2C2_CBCR_ADDR                                         (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x0000300c)
#define HWIO_SSC_SCC_SCC_QUP_I2C2_CBCR_OFFS                                         (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x0000300c)
#define HWIO_SSC_SCC_SCC_QUP_I2C2_CBCR_RMSK                                         0x80000001
#define HWIO_SSC_SCC_SCC_QUP_I2C2_CBCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_QUP_I2C2_CBCR_ADDR, HWIO_SSC_SCC_SCC_QUP_I2C2_CBCR_RMSK)
#define HWIO_SSC_SCC_SCC_QUP_I2C2_CBCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_QUP_I2C2_CBCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_QUP_I2C2_CBCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_QUP_I2C2_CBCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_QUP_I2C2_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_QUP_I2C2_CBCR_ADDR,m,v,HWIO_SSC_SCC_SCC_QUP_I2C2_CBCR_IN)
#define HWIO_SSC_SCC_SCC_QUP_I2C2_CBCR_CLK_OFF_BMSK                                 0x80000000
#define HWIO_SSC_SCC_SCC_QUP_I2C2_CBCR_CLK_OFF_SHFT                                       0x1f
#define HWIO_SSC_SCC_SCC_QUP_I2C2_CBCR_CLK_ENABLE_BMSK                                     0x1
#define HWIO_SSC_SCC_SCC_QUP_I2C2_CBCR_CLK_ENABLE_SHFT                                     0x0

#define HWIO_SSC_SCC_SCC_SPI_I2C3_BCR_ADDR                                          (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00004000)
#define HWIO_SSC_SCC_SCC_SPI_I2C3_BCR_OFFS                                          (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00004000)
#define HWIO_SSC_SCC_SCC_SPI_I2C3_BCR_RMSK                                                 0x1
#define HWIO_SSC_SCC_SCC_SPI_I2C3_BCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_SPI_I2C3_BCR_ADDR, HWIO_SSC_SCC_SCC_SPI_I2C3_BCR_RMSK)
#define HWIO_SSC_SCC_SCC_SPI_I2C3_BCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_SPI_I2C3_BCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_SPI_I2C3_BCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_SPI_I2C3_BCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_SPI_I2C3_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_SPI_I2C3_BCR_ADDR,m,v,HWIO_SSC_SCC_SCC_SPI_I2C3_BCR_IN)
#define HWIO_SSC_SCC_SCC_SPI_I2C3_BCR_BLK_ARES_BMSK                                        0x1
#define HWIO_SSC_SCC_SCC_SPI_I2C3_BCR_BLK_ARES_SHFT                                        0x0

#define HWIO_SSC_SCC_SCC_QUP_SPI3_CBCR_ADDR                                         (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00004008)
#define HWIO_SSC_SCC_SCC_QUP_SPI3_CBCR_OFFS                                         (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00004008)
#define HWIO_SSC_SCC_SCC_QUP_SPI3_CBCR_RMSK                                         0x80000001
#define HWIO_SSC_SCC_SCC_QUP_SPI3_CBCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_QUP_SPI3_CBCR_ADDR, HWIO_SSC_SCC_SCC_QUP_SPI3_CBCR_RMSK)
#define HWIO_SSC_SCC_SCC_QUP_SPI3_CBCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_QUP_SPI3_CBCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_QUP_SPI3_CBCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_QUP_SPI3_CBCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_QUP_SPI3_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_QUP_SPI3_CBCR_ADDR,m,v,HWIO_SSC_SCC_SCC_QUP_SPI3_CBCR_IN)
#define HWIO_SSC_SCC_SCC_QUP_SPI3_CBCR_CLK_OFF_BMSK                                 0x80000000
#define HWIO_SSC_SCC_SCC_QUP_SPI3_CBCR_CLK_OFF_SHFT                                       0x1f
#define HWIO_SSC_SCC_SCC_QUP_SPI3_CBCR_CLK_ENABLE_BMSK                                     0x1
#define HWIO_SSC_SCC_SCC_QUP_SPI3_CBCR_CLK_ENABLE_SHFT                                     0x0

#define HWIO_SSC_SCC_SCC_QUP_I2C3_CBCR_ADDR                                         (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x0000400c)
#define HWIO_SSC_SCC_SCC_QUP_I2C3_CBCR_OFFS                                         (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x0000400c)
#define HWIO_SSC_SCC_SCC_QUP_I2C3_CBCR_RMSK                                         0x80000001
#define HWIO_SSC_SCC_SCC_QUP_I2C3_CBCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_QUP_I2C3_CBCR_ADDR, HWIO_SSC_SCC_SCC_QUP_I2C3_CBCR_RMSK)
#define HWIO_SSC_SCC_SCC_QUP_I2C3_CBCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_QUP_I2C3_CBCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_QUP_I2C3_CBCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_QUP_I2C3_CBCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_QUP_I2C3_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_QUP_I2C3_CBCR_ADDR,m,v,HWIO_SSC_SCC_SCC_QUP_I2C3_CBCR_IN)
#define HWIO_SSC_SCC_SCC_QUP_I2C3_CBCR_CLK_OFF_BMSK                                 0x80000000
#define HWIO_SSC_SCC_SCC_QUP_I2C3_CBCR_CLK_OFF_SHFT                                       0x1f
#define HWIO_SSC_SCC_SCC_QUP_I2C3_CBCR_CLK_ENABLE_BMSK                                     0x1
#define HWIO_SSC_SCC_SCC_QUP_I2C3_CBCR_CLK_ENABLE_SHFT                                     0x0

#define HWIO_SSC_SCC_SCC_UART1_BCR_ADDR                                             (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00005000)
#define HWIO_SSC_SCC_SCC_UART1_BCR_OFFS                                             (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00005000)
#define HWIO_SSC_SCC_SCC_UART1_BCR_RMSK                                                    0x1
#define HWIO_SSC_SCC_SCC_UART1_BCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART1_BCR_ADDR, HWIO_SSC_SCC_SCC_UART1_BCR_RMSK)
#define HWIO_SSC_SCC_SCC_UART1_BCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART1_BCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_UART1_BCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_UART1_BCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_UART1_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_UART1_BCR_ADDR,m,v,HWIO_SSC_SCC_SCC_UART1_BCR_IN)
#define HWIO_SSC_SCC_SCC_UART1_BCR_BLK_ARES_BMSK                                           0x1
#define HWIO_SSC_SCC_SCC_UART1_BCR_BLK_ARES_SHFT                                           0x0

#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CMD_RCGR_ADDR                                (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00005004)
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CMD_RCGR_OFFS                                (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00005004)
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CMD_RCGR_RMSK                                0x800000f3
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CMD_RCGR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART_DM_UART1_CMD_RCGR_ADDR, HWIO_SSC_SCC_SCC_UART_DM_UART1_CMD_RCGR_RMSK)
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART_DM_UART1_CMD_RCGR_ADDR, m)
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_UART_DM_UART1_CMD_RCGR_ADDR,v)
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_UART_DM_UART1_CMD_RCGR_ADDR,m,v,HWIO_SSC_SCC_SCC_UART_DM_UART1_CMD_RCGR_IN)
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CMD_RCGR_ROOT_OFF_BMSK                       0x80000000
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CMD_RCGR_ROOT_OFF_SHFT                             0x1f
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CMD_RCGR_DIRTY_D_BMSK                              0x80
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CMD_RCGR_DIRTY_D_SHFT                               0x7
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CMD_RCGR_DIRTY_N_BMSK                              0x40
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CMD_RCGR_DIRTY_N_SHFT                               0x6
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CMD_RCGR_DIRTY_M_BMSK                              0x20
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CMD_RCGR_DIRTY_M_SHFT                               0x5
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                       0x10
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                        0x4
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CMD_RCGR_ROOT_EN_BMSK                               0x2
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CMD_RCGR_ROOT_EN_SHFT                               0x1
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CMD_RCGR_UPDATE_BMSK                                0x1
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CMD_RCGR_UPDATE_SHFT                                0x0

#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CFG_RCGR_ADDR                                (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00005008)
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CFG_RCGR_OFFS                                (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00005008)
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CFG_RCGR_RMSK                                    0x371f
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CFG_RCGR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART_DM_UART1_CFG_RCGR_ADDR, HWIO_SSC_SCC_SCC_UART_DM_UART1_CFG_RCGR_RMSK)
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART_DM_UART1_CFG_RCGR_ADDR, m)
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_UART_DM_UART1_CFG_RCGR_ADDR,v)
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_UART_DM_UART1_CFG_RCGR_ADDR,m,v,HWIO_SSC_SCC_SCC_UART_DM_UART1_CFG_RCGR_IN)
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CFG_RCGR_MODE_BMSK                               0x3000
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CFG_RCGR_MODE_SHFT                                  0xc
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CFG_RCGR_SRC_SEL_BMSK                             0x700
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CFG_RCGR_SRC_SEL_SHFT                               0x8
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CFG_RCGR_SRC_DIV_BMSK                              0x1f
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CFG_RCGR_SRC_DIV_SHFT                               0x0

#define HWIO_SSC_SCC_SCC_UART_DM_UART1_M_ADDR                                       (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x0000500c)
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_M_OFFS                                       (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x0000500c)
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_M_RMSK                                           0xffff
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_M_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART_DM_UART1_M_ADDR, HWIO_SSC_SCC_SCC_UART_DM_UART1_M_RMSK)
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_M_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART_DM_UART1_M_ADDR, m)
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_M_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_UART_DM_UART1_M_ADDR,v)
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_UART_DM_UART1_M_ADDR,m,v,HWIO_SSC_SCC_SCC_UART_DM_UART1_M_IN)
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_M_M_BMSK                                         0xffff
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_M_M_SHFT                                            0x0

#define HWIO_SSC_SCC_SCC_UART_DM_UART1_N_ADDR                                       (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00005010)
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_N_OFFS                                       (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00005010)
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_N_RMSK                                           0xffff
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_N_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART_DM_UART1_N_ADDR, HWIO_SSC_SCC_SCC_UART_DM_UART1_N_RMSK)
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_N_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART_DM_UART1_N_ADDR, m)
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_N_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_UART_DM_UART1_N_ADDR,v)
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_UART_DM_UART1_N_ADDR,m,v,HWIO_SSC_SCC_SCC_UART_DM_UART1_N_IN)
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_N_NOT_N_MINUS_M_BMSK                             0xffff
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_N_NOT_N_MINUS_M_SHFT                                0x0

#define HWIO_SSC_SCC_SCC_UART_DM_UART1_D_ADDR                                       (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00005014)
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_D_OFFS                                       (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00005014)
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_D_RMSK                                           0xffff
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_D_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART_DM_UART1_D_ADDR, HWIO_SSC_SCC_SCC_UART_DM_UART1_D_RMSK)
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_D_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART_DM_UART1_D_ADDR, m)
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_D_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_UART_DM_UART1_D_ADDR,v)
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_UART_DM_UART1_D_ADDR,m,v,HWIO_SSC_SCC_SCC_UART_DM_UART1_D_IN)
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_D_NOT_2D_BMSK                                    0xffff
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_D_NOT_2D_SHFT                                       0x0

#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CBCR_ADDR                                    (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x0000501c)
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CBCR_OFFS                                    (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x0000501c)
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CBCR_RMSK                                    0x80000001
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CBCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART_DM_UART1_CBCR_ADDR, HWIO_SSC_SCC_SCC_UART_DM_UART1_CBCR_RMSK)
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CBCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART_DM_UART1_CBCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CBCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_UART_DM_UART1_CBCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_UART_DM_UART1_CBCR_ADDR,m,v,HWIO_SSC_SCC_SCC_UART_DM_UART1_CBCR_IN)
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CBCR_CLK_OFF_BMSK                            0x80000000
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CBCR_CLK_OFF_SHFT                                  0x1f
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CBCR_CLK_ENABLE_BMSK                                0x1
#define HWIO_SSC_SCC_SCC_UART_DM_UART1_CBCR_CLK_ENABLE_SHFT                                0x0

#define HWIO_SSC_SCC_SCC_UART2_BCR_ADDR                                             (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00006000)
#define HWIO_SSC_SCC_SCC_UART2_BCR_OFFS                                             (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00006000)
#define HWIO_SSC_SCC_SCC_UART2_BCR_RMSK                                                    0x1
#define HWIO_SSC_SCC_SCC_UART2_BCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART2_BCR_ADDR, HWIO_SSC_SCC_SCC_UART2_BCR_RMSK)
#define HWIO_SSC_SCC_SCC_UART2_BCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART2_BCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_UART2_BCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_UART2_BCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_UART2_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_UART2_BCR_ADDR,m,v,HWIO_SSC_SCC_SCC_UART2_BCR_IN)
#define HWIO_SSC_SCC_SCC_UART2_BCR_BLK_ARES_BMSK                                           0x1
#define HWIO_SSC_SCC_SCC_UART2_BCR_BLK_ARES_SHFT                                           0x0

#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CMD_RCGR_ADDR                                (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00006004)
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CMD_RCGR_OFFS                                (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00006004)
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CMD_RCGR_RMSK                                0x800000f3
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CMD_RCGR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART_DM_UART2_CMD_RCGR_ADDR, HWIO_SSC_SCC_SCC_UART_DM_UART2_CMD_RCGR_RMSK)
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART_DM_UART2_CMD_RCGR_ADDR, m)
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_UART_DM_UART2_CMD_RCGR_ADDR,v)
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_UART_DM_UART2_CMD_RCGR_ADDR,m,v,HWIO_SSC_SCC_SCC_UART_DM_UART2_CMD_RCGR_IN)
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CMD_RCGR_ROOT_OFF_BMSK                       0x80000000
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CMD_RCGR_ROOT_OFF_SHFT                             0x1f
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CMD_RCGR_DIRTY_D_BMSK                              0x80
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CMD_RCGR_DIRTY_D_SHFT                               0x7
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CMD_RCGR_DIRTY_N_BMSK                              0x40
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CMD_RCGR_DIRTY_N_SHFT                               0x6
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CMD_RCGR_DIRTY_M_BMSK                              0x20
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CMD_RCGR_DIRTY_M_SHFT                               0x5
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                       0x10
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                        0x4
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CMD_RCGR_ROOT_EN_BMSK                               0x2
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CMD_RCGR_ROOT_EN_SHFT                               0x1
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CMD_RCGR_UPDATE_BMSK                                0x1
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CMD_RCGR_UPDATE_SHFT                                0x0

#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CFG_RCGR_ADDR                                (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00006008)
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CFG_RCGR_OFFS                                (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00006008)
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CFG_RCGR_RMSK                                    0x371f
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CFG_RCGR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART_DM_UART2_CFG_RCGR_ADDR, HWIO_SSC_SCC_SCC_UART_DM_UART2_CFG_RCGR_RMSK)
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART_DM_UART2_CFG_RCGR_ADDR, m)
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_UART_DM_UART2_CFG_RCGR_ADDR,v)
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_UART_DM_UART2_CFG_RCGR_ADDR,m,v,HWIO_SSC_SCC_SCC_UART_DM_UART2_CFG_RCGR_IN)
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CFG_RCGR_MODE_BMSK                               0x3000
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CFG_RCGR_MODE_SHFT                                  0xc
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CFG_RCGR_SRC_SEL_BMSK                             0x700
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CFG_RCGR_SRC_SEL_SHFT                               0x8
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CFG_RCGR_SRC_DIV_BMSK                              0x1f
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CFG_RCGR_SRC_DIV_SHFT                               0x0

#define HWIO_SSC_SCC_SCC_UART_DM_UART2_M_ADDR                                       (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x0000600c)
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_M_OFFS                                       (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x0000600c)
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_M_RMSK                                           0xffff
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_M_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART_DM_UART2_M_ADDR, HWIO_SSC_SCC_SCC_UART_DM_UART2_M_RMSK)
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_M_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART_DM_UART2_M_ADDR, m)
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_M_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_UART_DM_UART2_M_ADDR,v)
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_UART_DM_UART2_M_ADDR,m,v,HWIO_SSC_SCC_SCC_UART_DM_UART2_M_IN)
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_M_M_BMSK                                         0xffff
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_M_M_SHFT                                            0x0

#define HWIO_SSC_SCC_SCC_UART_DM_UART2_N_ADDR                                       (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00006010)
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_N_OFFS                                       (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00006010)
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_N_RMSK                                           0xffff
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_N_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART_DM_UART2_N_ADDR, HWIO_SSC_SCC_SCC_UART_DM_UART2_N_RMSK)
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_N_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART_DM_UART2_N_ADDR, m)
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_N_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_UART_DM_UART2_N_ADDR,v)
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_UART_DM_UART2_N_ADDR,m,v,HWIO_SSC_SCC_SCC_UART_DM_UART2_N_IN)
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_N_NOT_N_MINUS_M_BMSK                             0xffff
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_N_NOT_N_MINUS_M_SHFT                                0x0

#define HWIO_SSC_SCC_SCC_UART_DM_UART2_D_ADDR                                       (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00006014)
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_D_OFFS                                       (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00006014)
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_D_RMSK                                           0xffff
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_D_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART_DM_UART2_D_ADDR, HWIO_SSC_SCC_SCC_UART_DM_UART2_D_RMSK)
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_D_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART_DM_UART2_D_ADDR, m)
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_D_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_UART_DM_UART2_D_ADDR,v)
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_UART_DM_UART2_D_ADDR,m,v,HWIO_SSC_SCC_SCC_UART_DM_UART2_D_IN)
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_D_NOT_2D_BMSK                                    0xffff
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_D_NOT_2D_SHFT                                       0x0

#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CBCR_ADDR                                    (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x0000601c)
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CBCR_OFFS                                    (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x0000601c)
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CBCR_RMSK                                    0x80000001
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CBCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART_DM_UART2_CBCR_ADDR, HWIO_SSC_SCC_SCC_UART_DM_UART2_CBCR_RMSK)
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CBCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART_DM_UART2_CBCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CBCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_UART_DM_UART2_CBCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_UART_DM_UART2_CBCR_ADDR,m,v,HWIO_SSC_SCC_SCC_UART_DM_UART2_CBCR_IN)
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CBCR_CLK_OFF_BMSK                            0x80000000
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CBCR_CLK_OFF_SHFT                                  0x1f
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CBCR_CLK_ENABLE_BMSK                                0x1
#define HWIO_SSC_SCC_SCC_UART_DM_UART2_CBCR_CLK_ENABLE_SHFT                                0x0

#define HWIO_SSC_SCC_SCC_UART3_BCR_ADDR                                             (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00007000)
#define HWIO_SSC_SCC_SCC_UART3_BCR_OFFS                                             (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00007000)
#define HWIO_SSC_SCC_SCC_UART3_BCR_RMSK                                                    0x1
#define HWIO_SSC_SCC_SCC_UART3_BCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART3_BCR_ADDR, HWIO_SSC_SCC_SCC_UART3_BCR_RMSK)
#define HWIO_SSC_SCC_SCC_UART3_BCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART3_BCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_UART3_BCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_UART3_BCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_UART3_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_UART3_BCR_ADDR,m,v,HWIO_SSC_SCC_SCC_UART3_BCR_IN)
#define HWIO_SSC_SCC_SCC_UART3_BCR_BLK_ARES_BMSK                                           0x1
#define HWIO_SSC_SCC_SCC_UART3_BCR_BLK_ARES_SHFT                                           0x0

#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CMD_RCGR_ADDR                                (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00007004)
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CMD_RCGR_OFFS                                (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00007004)
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CMD_RCGR_RMSK                                0x800000f3
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CMD_RCGR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART_DM_UART3_CMD_RCGR_ADDR, HWIO_SSC_SCC_SCC_UART_DM_UART3_CMD_RCGR_RMSK)
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART_DM_UART3_CMD_RCGR_ADDR, m)
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_UART_DM_UART3_CMD_RCGR_ADDR,v)
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_UART_DM_UART3_CMD_RCGR_ADDR,m,v,HWIO_SSC_SCC_SCC_UART_DM_UART3_CMD_RCGR_IN)
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CMD_RCGR_ROOT_OFF_BMSK                       0x80000000
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CMD_RCGR_ROOT_OFF_SHFT                             0x1f
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CMD_RCGR_DIRTY_D_BMSK                              0x80
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CMD_RCGR_DIRTY_D_SHFT                               0x7
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CMD_RCGR_DIRTY_N_BMSK                              0x40
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CMD_RCGR_DIRTY_N_SHFT                               0x6
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CMD_RCGR_DIRTY_M_BMSK                              0x20
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CMD_RCGR_DIRTY_M_SHFT                               0x5
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                       0x10
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                        0x4
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CMD_RCGR_ROOT_EN_BMSK                               0x2
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CMD_RCGR_ROOT_EN_SHFT                               0x1
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CMD_RCGR_UPDATE_BMSK                                0x1
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CMD_RCGR_UPDATE_SHFT                                0x0

#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CFG_RCGR_ADDR                                (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00007008)
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CFG_RCGR_OFFS                                (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00007008)
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CFG_RCGR_RMSK                                    0x371f
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CFG_RCGR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART_DM_UART3_CFG_RCGR_ADDR, HWIO_SSC_SCC_SCC_UART_DM_UART3_CFG_RCGR_RMSK)
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART_DM_UART3_CFG_RCGR_ADDR, m)
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_UART_DM_UART3_CFG_RCGR_ADDR,v)
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_UART_DM_UART3_CFG_RCGR_ADDR,m,v,HWIO_SSC_SCC_SCC_UART_DM_UART3_CFG_RCGR_IN)
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CFG_RCGR_MODE_BMSK                               0x3000
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CFG_RCGR_MODE_SHFT                                  0xc
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CFG_RCGR_SRC_SEL_BMSK                             0x700
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CFG_RCGR_SRC_SEL_SHFT                               0x8
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CFG_RCGR_SRC_DIV_BMSK                              0x1f
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CFG_RCGR_SRC_DIV_SHFT                               0x0

#define HWIO_SSC_SCC_SCC_UART_DM_UART3_M_ADDR                                       (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x0000700c)
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_M_OFFS                                       (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x0000700c)
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_M_RMSK                                           0xffff
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_M_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART_DM_UART3_M_ADDR, HWIO_SSC_SCC_SCC_UART_DM_UART3_M_RMSK)
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_M_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART_DM_UART3_M_ADDR, m)
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_M_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_UART_DM_UART3_M_ADDR,v)
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_UART_DM_UART3_M_ADDR,m,v,HWIO_SSC_SCC_SCC_UART_DM_UART3_M_IN)
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_M_M_BMSK                                         0xffff
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_M_M_SHFT                                            0x0

#define HWIO_SSC_SCC_SCC_UART_DM_UART3_N_ADDR                                       (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00007010)
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_N_OFFS                                       (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00007010)
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_N_RMSK                                           0xffff
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_N_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART_DM_UART3_N_ADDR, HWIO_SSC_SCC_SCC_UART_DM_UART3_N_RMSK)
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_N_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART_DM_UART3_N_ADDR, m)
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_N_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_UART_DM_UART3_N_ADDR,v)
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_UART_DM_UART3_N_ADDR,m,v,HWIO_SSC_SCC_SCC_UART_DM_UART3_N_IN)
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_N_NOT_N_MINUS_M_BMSK                             0xffff
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_N_NOT_N_MINUS_M_SHFT                                0x0

#define HWIO_SSC_SCC_SCC_UART_DM_UART3_D_ADDR                                       (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00007014)
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_D_OFFS                                       (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00007014)
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_D_RMSK                                           0xffff
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_D_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART_DM_UART3_D_ADDR, HWIO_SSC_SCC_SCC_UART_DM_UART3_D_RMSK)
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_D_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART_DM_UART3_D_ADDR, m)
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_D_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_UART_DM_UART3_D_ADDR,v)
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_UART_DM_UART3_D_ADDR,m,v,HWIO_SSC_SCC_SCC_UART_DM_UART3_D_IN)
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_D_NOT_2D_BMSK                                    0xffff
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_D_NOT_2D_SHFT                                       0x0

#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CBCR_ADDR                                    (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x0000701c)
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CBCR_OFFS                                    (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x0000701c)
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CBCR_RMSK                                    0x80000001
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CBCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART_DM_UART3_CBCR_ADDR, HWIO_SSC_SCC_SCC_UART_DM_UART3_CBCR_RMSK)
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CBCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_UART_DM_UART3_CBCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CBCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_UART_DM_UART3_CBCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_UART_DM_UART3_CBCR_ADDR,m,v,HWIO_SSC_SCC_SCC_UART_DM_UART3_CBCR_IN)
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CBCR_CLK_OFF_BMSK                            0x80000000
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CBCR_CLK_OFF_SHFT                                  0x1f
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CBCR_CLK_ENABLE_BMSK                                0x1
#define HWIO_SSC_SCC_SCC_UART_DM_UART3_CBCR_CLK_ENABLE_SHFT                                0x0

#define HWIO_SSC_SCC_SCC_Q6_SPM_BCR_ADDR                                            (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00008000)
#define HWIO_SSC_SCC_SCC_Q6_SPM_BCR_OFFS                                            (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00008000)
#define HWIO_SSC_SCC_SCC_Q6_SPM_BCR_RMSK                                                   0x1
#define HWIO_SSC_SCC_SCC_Q6_SPM_BCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_Q6_SPM_BCR_ADDR, HWIO_SSC_SCC_SCC_Q6_SPM_BCR_RMSK)
#define HWIO_SSC_SCC_SCC_Q6_SPM_BCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_Q6_SPM_BCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_Q6_SPM_BCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_Q6_SPM_BCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_Q6_SPM_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_Q6_SPM_BCR_ADDR,m,v,HWIO_SSC_SCC_SCC_Q6_SPM_BCR_IN)
#define HWIO_SSC_SCC_SCC_Q6_SPM_BCR_BLK_ARES_BMSK                                          0x1
#define HWIO_SSC_SCC_SCC_Q6_SPM_BCR_BLK_ARES_SHFT                                          0x0

#define HWIO_SSC_SCC_SCC_Q6_SPM_CBCR_ADDR                                           (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00008004)
#define HWIO_SSC_SCC_SCC_Q6_SPM_CBCR_OFFS                                           (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00008004)
#define HWIO_SSC_SCC_SCC_Q6_SPM_CBCR_RMSK                                           0x800f0001
#define HWIO_SSC_SCC_SCC_Q6_SPM_CBCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_Q6_SPM_CBCR_ADDR, HWIO_SSC_SCC_SCC_Q6_SPM_CBCR_RMSK)
#define HWIO_SSC_SCC_SCC_Q6_SPM_CBCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_Q6_SPM_CBCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_Q6_SPM_CBCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_Q6_SPM_CBCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_Q6_SPM_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_Q6_SPM_CBCR_ADDR,m,v,HWIO_SSC_SCC_SCC_Q6_SPM_CBCR_IN)
#define HWIO_SSC_SCC_SCC_Q6_SPM_CBCR_CLK_OFF_BMSK                                   0x80000000
#define HWIO_SSC_SCC_SCC_Q6_SPM_CBCR_CLK_OFF_SHFT                                         0x1f
#define HWIO_SSC_SCC_SCC_Q6_SPM_CBCR_CLK_DIV_BMSK                                      0xf0000
#define HWIO_SSC_SCC_SCC_Q6_SPM_CBCR_CLK_DIV_SHFT                                         0x10
#define HWIO_SSC_SCC_SCC_Q6_SPM_CBCR_CLK_ENABLE_BMSK                                       0x1
#define HWIO_SSC_SCC_SCC_Q6_SPM_CBCR_CLK_ENABLE_SHFT                                       0x0

#define HWIO_SSC_SCC_SCC_BUS_BCR_ADDR                                               (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00009000)
#define HWIO_SSC_SCC_SCC_BUS_BCR_OFFS                                               (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00009000)
#define HWIO_SSC_SCC_SCC_BUS_BCR_RMSK                                                      0x1
#define HWIO_SSC_SCC_SCC_BUS_BCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_BUS_BCR_ADDR, HWIO_SSC_SCC_SCC_BUS_BCR_RMSK)
#define HWIO_SSC_SCC_SCC_BUS_BCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_BUS_BCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_BUS_BCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_BUS_BCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_BUS_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_BUS_BCR_ADDR,m,v,HWIO_SSC_SCC_SCC_BUS_BCR_IN)
#define HWIO_SSC_SCC_SCC_BUS_BCR_BLK_ARES_BMSK                                             0x1
#define HWIO_SSC_SCC_SCC_BUS_BCR_BLK_ARES_SHFT                                             0x0

#define HWIO_SSC_SCC_SCC_CRIF_CBCR_ADDR                                             (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00009008)
#define HWIO_SSC_SCC_SCC_CRIF_CBCR_OFFS                                             (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00009008)
#define HWIO_SSC_SCC_SCC_CRIF_CBCR_RMSK                                             0x80000000
#define HWIO_SSC_SCC_SCC_CRIF_CBCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_CRIF_CBCR_ADDR, HWIO_SSC_SCC_SCC_CRIF_CBCR_RMSK)
#define HWIO_SSC_SCC_SCC_CRIF_CBCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_CRIF_CBCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_CRIF_CBCR_CLK_OFF_BMSK                                     0x80000000
#define HWIO_SSC_SCC_SCC_CRIF_CBCR_CLK_OFF_SHFT                                           0x1f

#define HWIO_SSC_SCC_SCC_CSR_H_CBCR_ADDR                                            (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x0000900c)
#define HWIO_SSC_SCC_SCC_CSR_H_CBCR_OFFS                                            (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x0000900c)
#define HWIO_SSC_SCC_SCC_CSR_H_CBCR_RMSK                                            0x80000000
#define HWIO_SSC_SCC_SCC_CSR_H_CBCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_CSR_H_CBCR_ADDR, HWIO_SSC_SCC_SCC_CSR_H_CBCR_RMSK)
#define HWIO_SSC_SCC_SCC_CSR_H_CBCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_CSR_H_CBCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_CSR_H_CBCR_CLK_OFF_BMSK                                    0x80000000
#define HWIO_SSC_SCC_SCC_CSR_H_CBCR_CLK_OFF_SHFT                                          0x1f

#define HWIO_SSC_SCC_SCC_DATA_H_CBCR_ADDR                                           (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00009010)
#define HWIO_SSC_SCC_SCC_DATA_H_CBCR_OFFS                                           (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00009010)
#define HWIO_SSC_SCC_SCC_DATA_H_CBCR_RMSK                                           0x80000001
#define HWIO_SSC_SCC_SCC_DATA_H_CBCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_DATA_H_CBCR_ADDR, HWIO_SSC_SCC_SCC_DATA_H_CBCR_RMSK)
#define HWIO_SSC_SCC_SCC_DATA_H_CBCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_DATA_H_CBCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_DATA_H_CBCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_DATA_H_CBCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_DATA_H_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_DATA_H_CBCR_ADDR,m,v,HWIO_SSC_SCC_SCC_DATA_H_CBCR_IN)
#define HWIO_SSC_SCC_SCC_DATA_H_CBCR_CLK_OFF_BMSK                                   0x80000000
#define HWIO_SSC_SCC_SCC_DATA_H_CBCR_CLK_OFF_SHFT                                         0x1f
#define HWIO_SSC_SCC_SCC_DATA_H_CBCR_CLK_ENABLE_BMSK                                       0x1
#define HWIO_SSC_SCC_SCC_DATA_H_CBCR_CLK_ENABLE_SHFT                                       0x0

#define HWIO_SSC_SCC_SCC_CFG_AHB_CBCR_ADDR                                          (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00009014)
#define HWIO_SSC_SCC_SCC_CFG_AHB_CBCR_OFFS                                          (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00009014)
#define HWIO_SSC_SCC_SCC_CFG_AHB_CBCR_RMSK                                          0x80000000
#define HWIO_SSC_SCC_SCC_CFG_AHB_CBCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_CFG_AHB_CBCR_ADDR, HWIO_SSC_SCC_SCC_CFG_AHB_CBCR_RMSK)
#define HWIO_SSC_SCC_SCC_CFG_AHB_CBCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_CFG_AHB_CBCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_CFG_AHB_CBCR_CLK_OFF_BMSK                                  0x80000000
#define HWIO_SSC_SCC_SCC_CFG_AHB_CBCR_CLK_OFF_SHFT                                        0x1f

#define HWIO_SSC_SCC_SCC_BLSP_BCR_ADDR                                              (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00009018)
#define HWIO_SSC_SCC_SCC_BLSP_BCR_OFFS                                              (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00009018)
#define HWIO_SSC_SCC_SCC_BLSP_BCR_RMSK                                                     0x1
#define HWIO_SSC_SCC_SCC_BLSP_BCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_BLSP_BCR_ADDR, HWIO_SSC_SCC_SCC_BLSP_BCR_RMSK)
#define HWIO_SSC_SCC_SCC_BLSP_BCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_BLSP_BCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_BLSP_BCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_BLSP_BCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_BLSP_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_BLSP_BCR_ADDR,m,v,HWIO_SSC_SCC_SCC_BLSP_BCR_IN)
#define HWIO_SSC_SCC_SCC_BLSP_BCR_BLK_ARES_BMSK                                            0x1
#define HWIO_SSC_SCC_SCC_BLSP_BCR_BLK_ARES_SHFT                                            0x0

#define HWIO_SSC_SCC_SCC_BLSP_H_CBCR_ADDR                                           (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x0000901c)
#define HWIO_SSC_SCC_SCC_BLSP_H_CBCR_OFFS                                           (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x0000901c)
#define HWIO_SSC_SCC_SCC_BLSP_H_CBCR_RMSK                                           0x80007ff1
#define HWIO_SSC_SCC_SCC_BLSP_H_CBCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_BLSP_H_CBCR_ADDR, HWIO_SSC_SCC_SCC_BLSP_H_CBCR_RMSK)
#define HWIO_SSC_SCC_SCC_BLSP_H_CBCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_BLSP_H_CBCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_BLSP_H_CBCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_BLSP_H_CBCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_BLSP_H_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_BLSP_H_CBCR_ADDR,m,v,HWIO_SSC_SCC_SCC_BLSP_H_CBCR_IN)
#define HWIO_SSC_SCC_SCC_BLSP_H_CBCR_CLK_OFF_BMSK                                   0x80000000
#define HWIO_SSC_SCC_SCC_BLSP_H_CBCR_CLK_OFF_SHFT                                         0x1f
#define HWIO_SSC_SCC_SCC_BLSP_H_CBCR_FORCE_MEM_CORE_ON_BMSK                             0x4000
#define HWIO_SSC_SCC_SCC_BLSP_H_CBCR_FORCE_MEM_CORE_ON_SHFT                                0xe
#define HWIO_SSC_SCC_SCC_BLSP_H_CBCR_FORCE_MEM_PERIPH_ON_BMSK                           0x2000
#define HWIO_SSC_SCC_SCC_BLSP_H_CBCR_FORCE_MEM_PERIPH_ON_SHFT                              0xd
#define HWIO_SSC_SCC_SCC_BLSP_H_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                          0x1000
#define HWIO_SSC_SCC_SCC_BLSP_H_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                             0xc
#define HWIO_SSC_SCC_SCC_BLSP_H_CBCR_WAKEUP_BMSK                                         0xf00
#define HWIO_SSC_SCC_SCC_BLSP_H_CBCR_WAKEUP_SHFT                                           0x8
#define HWIO_SSC_SCC_SCC_BLSP_H_CBCR_SLEEP_BMSK                                           0xf0
#define HWIO_SSC_SCC_SCC_BLSP_H_CBCR_SLEEP_SHFT                                            0x4
#define HWIO_SSC_SCC_SCC_BLSP_H_CBCR_CLK_ENABLE_BMSK                                       0x1
#define HWIO_SSC_SCC_SCC_BLSP_H_CBCR_CLK_ENABLE_SHFT                                       0x0

#define HWIO_SSC_SCC_SCC_Q6_AHB_BCR_ADDR                                            (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00009020)
#define HWIO_SSC_SCC_SCC_Q6_AHB_BCR_OFFS                                            (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00009020)
#define HWIO_SSC_SCC_SCC_Q6_AHB_BCR_RMSK                                                   0x1
#define HWIO_SSC_SCC_SCC_Q6_AHB_BCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_Q6_AHB_BCR_ADDR, HWIO_SSC_SCC_SCC_Q6_AHB_BCR_RMSK)
#define HWIO_SSC_SCC_SCC_Q6_AHB_BCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_Q6_AHB_BCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_Q6_AHB_BCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_Q6_AHB_BCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_Q6_AHB_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_Q6_AHB_BCR_ADDR,m,v,HWIO_SSC_SCC_SCC_Q6_AHB_BCR_IN)
#define HWIO_SSC_SCC_SCC_Q6_AHB_BCR_BLK_ARES_BMSK                                          0x1
#define HWIO_SSC_SCC_SCC_Q6_AHB_BCR_BLK_ARES_SHFT                                          0x0

#define HWIO_SSC_SCC_SCC_Q6_AHBM_CBCR_ADDR                                          (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00009024)
#define HWIO_SSC_SCC_SCC_Q6_AHBM_CBCR_OFFS                                          (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00009024)
#define HWIO_SSC_SCC_SCC_Q6_AHBM_CBCR_RMSK                                          0x80000003
#define HWIO_SSC_SCC_SCC_Q6_AHBM_CBCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_Q6_AHBM_CBCR_ADDR, HWIO_SSC_SCC_SCC_Q6_AHBM_CBCR_RMSK)
#define HWIO_SSC_SCC_SCC_Q6_AHBM_CBCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_Q6_AHBM_CBCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_Q6_AHBM_CBCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_Q6_AHBM_CBCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_Q6_AHBM_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_Q6_AHBM_CBCR_ADDR,m,v,HWIO_SSC_SCC_SCC_Q6_AHBM_CBCR_IN)
#define HWIO_SSC_SCC_SCC_Q6_AHBM_CBCR_CLK_OFF_BMSK                                  0x80000000
#define HWIO_SSC_SCC_SCC_Q6_AHBM_CBCR_CLK_OFF_SHFT                                        0x1f
#define HWIO_SSC_SCC_SCC_Q6_AHBM_CBCR_HW_CTL_BMSK                                          0x2
#define HWIO_SSC_SCC_SCC_Q6_AHBM_CBCR_HW_CTL_SHFT                                          0x1
#define HWIO_SSC_SCC_SCC_Q6_AHBM_CBCR_CLK_ENABLE_BMSK                                      0x1
#define HWIO_SSC_SCC_SCC_Q6_AHBM_CBCR_CLK_ENABLE_SHFT                                      0x0

#define HWIO_SSC_SCC_SCC_Q6_AHBS_CBCR_ADDR                                          (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00009028)
#define HWIO_SSC_SCC_SCC_Q6_AHBS_CBCR_OFFS                                          (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00009028)
#define HWIO_SSC_SCC_SCC_Q6_AHBS_CBCR_RMSK                                          0x80000003
#define HWIO_SSC_SCC_SCC_Q6_AHBS_CBCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_Q6_AHBS_CBCR_ADDR, HWIO_SSC_SCC_SCC_Q6_AHBS_CBCR_RMSK)
#define HWIO_SSC_SCC_SCC_Q6_AHBS_CBCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_Q6_AHBS_CBCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_Q6_AHBS_CBCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_Q6_AHBS_CBCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_Q6_AHBS_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_Q6_AHBS_CBCR_ADDR,m,v,HWIO_SSC_SCC_SCC_Q6_AHBS_CBCR_IN)
#define HWIO_SSC_SCC_SCC_Q6_AHBS_CBCR_CLK_OFF_BMSK                                  0x80000000
#define HWIO_SSC_SCC_SCC_Q6_AHBS_CBCR_CLK_OFF_SHFT                                        0x1f
#define HWIO_SSC_SCC_SCC_Q6_AHBS_CBCR_HW_CTL_BMSK                                          0x2
#define HWIO_SSC_SCC_SCC_Q6_AHBS_CBCR_HW_CTL_SHFT                                          0x1
#define HWIO_SSC_SCC_SCC_Q6_AHBS_CBCR_CLK_ENABLE_BMSK                                      0x1
#define HWIO_SSC_SCC_SCC_Q6_AHBS_CBCR_CLK_ENABLE_SHFT                                      0x0

#define HWIO_SSC_SCC_SCC_SMEM_BCR_ADDR                                              (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x0000902c)
#define HWIO_SSC_SCC_SCC_SMEM_BCR_OFFS                                              (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x0000902c)
#define HWIO_SSC_SCC_SCC_SMEM_BCR_RMSK                                                     0x1
#define HWIO_SSC_SCC_SCC_SMEM_BCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_SMEM_BCR_ADDR, HWIO_SSC_SCC_SCC_SMEM_BCR_RMSK)
#define HWIO_SSC_SCC_SCC_SMEM_BCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_SMEM_BCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_SMEM_BCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_SMEM_BCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_SMEM_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_SMEM_BCR_ADDR,m,v,HWIO_SSC_SCC_SCC_SMEM_BCR_IN)
#define HWIO_SSC_SCC_SCC_SMEM_BCR_BLK_ARES_BMSK                                            0x1
#define HWIO_SSC_SCC_SCC_SMEM_BCR_BLK_ARES_SHFT                                            0x0

#define HWIO_SSC_SCC_SCC_SMEM_CBCR_ADDR                                             (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00009030)
#define HWIO_SSC_SCC_SCC_SMEM_CBCR_OFFS                                             (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00009030)
#define HWIO_SSC_SCC_SCC_SMEM_CBCR_RMSK                                             0x80007ff1
#define HWIO_SSC_SCC_SCC_SMEM_CBCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_SMEM_CBCR_ADDR, HWIO_SSC_SCC_SCC_SMEM_CBCR_RMSK)
#define HWIO_SSC_SCC_SCC_SMEM_CBCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_SMEM_CBCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_SMEM_CBCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_SMEM_CBCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_SMEM_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_SMEM_CBCR_ADDR,m,v,HWIO_SSC_SCC_SCC_SMEM_CBCR_IN)
#define HWIO_SSC_SCC_SCC_SMEM_CBCR_CLK_OFF_BMSK                                     0x80000000
#define HWIO_SSC_SCC_SCC_SMEM_CBCR_CLK_OFF_SHFT                                           0x1f
#define HWIO_SSC_SCC_SCC_SMEM_CBCR_FORCE_MEM_CORE_ON_BMSK                               0x4000
#define HWIO_SSC_SCC_SCC_SMEM_CBCR_FORCE_MEM_CORE_ON_SHFT                                  0xe
#define HWIO_SSC_SCC_SCC_SMEM_CBCR_FORCE_MEM_PERIPH_ON_BMSK                             0x2000
#define HWIO_SSC_SCC_SCC_SMEM_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                0xd
#define HWIO_SSC_SCC_SCC_SMEM_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                            0x1000
#define HWIO_SSC_SCC_SCC_SMEM_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                               0xc
#define HWIO_SSC_SCC_SCC_SMEM_CBCR_WAKEUP_BMSK                                           0xf00
#define HWIO_SSC_SCC_SCC_SMEM_CBCR_WAKEUP_SHFT                                             0x8
#define HWIO_SSC_SCC_SCC_SMEM_CBCR_SLEEP_BMSK                                             0xf0
#define HWIO_SSC_SCC_SCC_SMEM_CBCR_SLEEP_SHFT                                              0x4
#define HWIO_SSC_SCC_SCC_SMEM_CBCR_CLK_ENABLE_BMSK                                         0x1
#define HWIO_SSC_SCC_SCC_SMEM_CBCR_CLK_ENABLE_SHFT                                         0x0

#define HWIO_SSC_SCC_SCC_AHB_TIMEOUT_BCR_ADDR                                       (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00009034)
#define HWIO_SSC_SCC_SCC_AHB_TIMEOUT_BCR_OFFS                                       (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00009034)
#define HWIO_SSC_SCC_SCC_AHB_TIMEOUT_BCR_RMSK                                              0x1
#define HWIO_SSC_SCC_SCC_AHB_TIMEOUT_BCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_AHB_TIMEOUT_BCR_ADDR, HWIO_SSC_SCC_SCC_AHB_TIMEOUT_BCR_RMSK)
#define HWIO_SSC_SCC_SCC_AHB_TIMEOUT_BCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_AHB_TIMEOUT_BCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_AHB_TIMEOUT_BCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_AHB_TIMEOUT_BCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_AHB_TIMEOUT_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_AHB_TIMEOUT_BCR_ADDR,m,v,HWIO_SSC_SCC_SCC_AHB_TIMEOUT_BCR_IN)
#define HWIO_SSC_SCC_SCC_AHB_TIMEOUT_BCR_BLK_ARES_BMSK                                     0x1
#define HWIO_SSC_SCC_SCC_AHB_TIMEOUT_BCR_BLK_ARES_SHFT                                     0x0

#define HWIO_SSC_SCC_SCC_AHB_TIMEOUT_CBCR_ADDR                                      (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00009038)
#define HWIO_SSC_SCC_SCC_AHB_TIMEOUT_CBCR_OFFS                                      (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00009038)
#define HWIO_SSC_SCC_SCC_AHB_TIMEOUT_CBCR_RMSK                                      0x80000001
#define HWIO_SSC_SCC_SCC_AHB_TIMEOUT_CBCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_AHB_TIMEOUT_CBCR_ADDR, HWIO_SSC_SCC_SCC_AHB_TIMEOUT_CBCR_RMSK)
#define HWIO_SSC_SCC_SCC_AHB_TIMEOUT_CBCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_AHB_TIMEOUT_CBCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_AHB_TIMEOUT_CBCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_AHB_TIMEOUT_CBCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_AHB_TIMEOUT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_AHB_TIMEOUT_CBCR_ADDR,m,v,HWIO_SSC_SCC_SCC_AHB_TIMEOUT_CBCR_IN)
#define HWIO_SSC_SCC_SCC_AHB_TIMEOUT_CBCR_CLK_OFF_BMSK                              0x80000000
#define HWIO_SSC_SCC_SCC_AHB_TIMEOUT_CBCR_CLK_OFF_SHFT                                    0x1f
#define HWIO_SSC_SCC_SCC_AHB_TIMEOUT_CBCR_CLK_ENABLE_BMSK                                  0x1
#define HWIO_SSC_SCC_SCC_AHB_TIMEOUT_CBCR_CLK_ENABLE_SHFT                                  0x0

#define HWIO_SSC_SCC_SCC_Q6_XPU2_CLIENT_CBCR_ADDR                                   (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x0000903c)
#define HWIO_SSC_SCC_SCC_Q6_XPU2_CLIENT_CBCR_OFFS                                   (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x0000903c)
#define HWIO_SSC_SCC_SCC_Q6_XPU2_CLIENT_CBCR_RMSK                                   0x80000001
#define HWIO_SSC_SCC_SCC_Q6_XPU2_CLIENT_CBCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_Q6_XPU2_CLIENT_CBCR_ADDR, HWIO_SSC_SCC_SCC_Q6_XPU2_CLIENT_CBCR_RMSK)
#define HWIO_SSC_SCC_SCC_Q6_XPU2_CLIENT_CBCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_Q6_XPU2_CLIENT_CBCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_Q6_XPU2_CLIENT_CBCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_Q6_XPU2_CLIENT_CBCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_Q6_XPU2_CLIENT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_Q6_XPU2_CLIENT_CBCR_ADDR,m,v,HWIO_SSC_SCC_SCC_Q6_XPU2_CLIENT_CBCR_IN)
#define HWIO_SSC_SCC_SCC_Q6_XPU2_CLIENT_CBCR_CLK_OFF_BMSK                           0x80000000
#define HWIO_SSC_SCC_SCC_Q6_XPU2_CLIENT_CBCR_CLK_OFF_SHFT                                 0x1f
#define HWIO_SSC_SCC_SCC_Q6_XPU2_CLIENT_CBCR_CLK_ENABLE_BMSK                               0x1
#define HWIO_SSC_SCC_SCC_Q6_XPU2_CLIENT_CBCR_CLK_ENABLE_SHFT                               0x0

#define HWIO_SSC_SCC_SCC_Q6_XPU2_CONFIG_BCR_ADDR                                    (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00009040)
#define HWIO_SSC_SCC_SCC_Q6_XPU2_CONFIG_BCR_OFFS                                    (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00009040)
#define HWIO_SSC_SCC_SCC_Q6_XPU2_CONFIG_BCR_RMSK                                           0x1
#define HWIO_SSC_SCC_SCC_Q6_XPU2_CONFIG_BCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_Q6_XPU2_CONFIG_BCR_ADDR, HWIO_SSC_SCC_SCC_Q6_XPU2_CONFIG_BCR_RMSK)
#define HWIO_SSC_SCC_SCC_Q6_XPU2_CONFIG_BCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_Q6_XPU2_CONFIG_BCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_Q6_XPU2_CONFIG_BCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_Q6_XPU2_CONFIG_BCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_Q6_XPU2_CONFIG_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_Q6_XPU2_CONFIG_BCR_ADDR,m,v,HWIO_SSC_SCC_SCC_Q6_XPU2_CONFIG_BCR_IN)
#define HWIO_SSC_SCC_SCC_Q6_XPU2_CONFIG_BCR_BLK_ARES_BMSK                                  0x1
#define HWIO_SSC_SCC_SCC_Q6_XPU2_CONFIG_BCR_BLK_ARES_SHFT                                  0x0

#define HWIO_SSC_SCC_SCC_Q6_XPU2_CONFIG_CBCR_ADDR                                   (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00009044)
#define HWIO_SSC_SCC_SCC_Q6_XPU2_CONFIG_CBCR_OFFS                                   (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00009044)
#define HWIO_SSC_SCC_SCC_Q6_XPU2_CONFIG_CBCR_RMSK                                   0x80000001
#define HWIO_SSC_SCC_SCC_Q6_XPU2_CONFIG_CBCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_Q6_XPU2_CONFIG_CBCR_ADDR, HWIO_SSC_SCC_SCC_Q6_XPU2_CONFIG_CBCR_RMSK)
#define HWIO_SSC_SCC_SCC_Q6_XPU2_CONFIG_CBCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_Q6_XPU2_CONFIG_CBCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_Q6_XPU2_CONFIG_CBCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_Q6_XPU2_CONFIG_CBCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_Q6_XPU2_CONFIG_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_Q6_XPU2_CONFIG_CBCR_ADDR,m,v,HWIO_SSC_SCC_SCC_Q6_XPU2_CONFIG_CBCR_IN)
#define HWIO_SSC_SCC_SCC_Q6_XPU2_CONFIG_CBCR_CLK_OFF_BMSK                           0x80000000
#define HWIO_SSC_SCC_SCC_Q6_XPU2_CONFIG_CBCR_CLK_OFF_SHFT                                 0x1f
#define HWIO_SSC_SCC_SCC_Q6_XPU2_CONFIG_CBCR_CLK_ENABLE_BMSK                               0x1
#define HWIO_SSC_SCC_SCC_Q6_XPU2_CONFIG_CBCR_CLK_ENABLE_SHFT                               0x0

#define HWIO_SSC_SCC_SCC_DBG_BCR_ADDR                                               (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x0000a000)
#define HWIO_SSC_SCC_SCC_DBG_BCR_OFFS                                               (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x0000a000)
#define HWIO_SSC_SCC_SCC_DBG_BCR_RMSK                                                      0x1
#define HWIO_SSC_SCC_SCC_DBG_BCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_DBG_BCR_ADDR, HWIO_SSC_SCC_SCC_DBG_BCR_RMSK)
#define HWIO_SSC_SCC_SCC_DBG_BCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_DBG_BCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_DBG_BCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_DBG_BCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_DBG_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_DBG_BCR_ADDR,m,v,HWIO_SSC_SCC_SCC_DBG_BCR_IN)
#define HWIO_SSC_SCC_SCC_DBG_BCR_BLK_ARES_BMSK                                             0x1
#define HWIO_SSC_SCC_SCC_DBG_BCR_BLK_ARES_SHFT                                             0x0

#define HWIO_SSC_SCC_SCC_AT_CBCR_ADDR                                               (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x0000a008)
#define HWIO_SSC_SCC_SCC_AT_CBCR_OFFS                                               (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x0000a008)
#define HWIO_SSC_SCC_SCC_AT_CBCR_RMSK                                               0x80007ff1
#define HWIO_SSC_SCC_SCC_AT_CBCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_AT_CBCR_ADDR, HWIO_SSC_SCC_SCC_AT_CBCR_RMSK)
#define HWIO_SSC_SCC_SCC_AT_CBCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_AT_CBCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_AT_CBCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_AT_CBCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_AT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_AT_CBCR_ADDR,m,v,HWIO_SSC_SCC_SCC_AT_CBCR_IN)
#define HWIO_SSC_SCC_SCC_AT_CBCR_CLK_OFF_BMSK                                       0x80000000
#define HWIO_SSC_SCC_SCC_AT_CBCR_CLK_OFF_SHFT                                             0x1f
#define HWIO_SSC_SCC_SCC_AT_CBCR_FORCE_MEM_CORE_ON_BMSK                                 0x4000
#define HWIO_SSC_SCC_SCC_AT_CBCR_FORCE_MEM_CORE_ON_SHFT                                    0xe
#define HWIO_SSC_SCC_SCC_AT_CBCR_FORCE_MEM_PERIPH_ON_BMSK                               0x2000
#define HWIO_SSC_SCC_SCC_AT_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                  0xd
#define HWIO_SSC_SCC_SCC_AT_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                              0x1000
#define HWIO_SSC_SCC_SCC_AT_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                 0xc
#define HWIO_SSC_SCC_SCC_AT_CBCR_WAKEUP_BMSK                                             0xf00
#define HWIO_SSC_SCC_SCC_AT_CBCR_WAKEUP_SHFT                                               0x8
#define HWIO_SSC_SCC_SCC_AT_CBCR_SLEEP_BMSK                                               0xf0
#define HWIO_SSC_SCC_SCC_AT_CBCR_SLEEP_SHFT                                                0x4
#define HWIO_SSC_SCC_SCC_AT_CBCR_CLK_ENABLE_BMSK                                           0x1
#define HWIO_SSC_SCC_SCC_AT_CBCR_CLK_ENABLE_SHFT                                           0x0

#define HWIO_SSC_SCC_SCC_Q6_ATBM_CBCR_ADDR                                          (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x0000a00c)
#define HWIO_SSC_SCC_SCC_Q6_ATBM_CBCR_OFFS                                          (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x0000a00c)
#define HWIO_SSC_SCC_SCC_Q6_ATBM_CBCR_RMSK                                          0x80000001
#define HWIO_SSC_SCC_SCC_Q6_ATBM_CBCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_Q6_ATBM_CBCR_ADDR, HWIO_SSC_SCC_SCC_Q6_ATBM_CBCR_RMSK)
#define HWIO_SSC_SCC_SCC_Q6_ATBM_CBCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_Q6_ATBM_CBCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_Q6_ATBM_CBCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_Q6_ATBM_CBCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_Q6_ATBM_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_Q6_ATBM_CBCR_ADDR,m,v,HWIO_SSC_SCC_SCC_Q6_ATBM_CBCR_IN)
#define HWIO_SSC_SCC_SCC_Q6_ATBM_CBCR_CLK_OFF_BMSK                                  0x80000000
#define HWIO_SSC_SCC_SCC_Q6_ATBM_CBCR_CLK_OFF_SHFT                                        0x1f
#define HWIO_SSC_SCC_SCC_Q6_ATBM_CBCR_CLK_ENABLE_BMSK                                      0x1
#define HWIO_SSC_SCC_SCC_Q6_ATBM_CBCR_CLK_ENABLE_SHFT                                      0x0

#define HWIO_SSC_SCC_SCC_PCLKDBG_CBCR_ADDR                                          (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x0000a010)
#define HWIO_SSC_SCC_SCC_PCLKDBG_CBCR_OFFS                                          (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x0000a010)
#define HWIO_SSC_SCC_SCC_PCLKDBG_CBCR_RMSK                                          0x80000001
#define HWIO_SSC_SCC_SCC_PCLKDBG_CBCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_PCLKDBG_CBCR_ADDR, HWIO_SSC_SCC_SCC_PCLKDBG_CBCR_RMSK)
#define HWIO_SSC_SCC_SCC_PCLKDBG_CBCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_PCLKDBG_CBCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_PCLKDBG_CBCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_PCLKDBG_CBCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_PCLKDBG_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_PCLKDBG_CBCR_ADDR,m,v,HWIO_SSC_SCC_SCC_PCLKDBG_CBCR_IN)
#define HWIO_SSC_SCC_SCC_PCLKDBG_CBCR_CLK_OFF_BMSK                                  0x80000000
#define HWIO_SSC_SCC_SCC_PCLKDBG_CBCR_CLK_OFF_SHFT                                        0x1f
#define HWIO_SSC_SCC_SCC_PCLKDBG_CBCR_CLK_ENABLE_BMSK                                      0x1
#define HWIO_SSC_SCC_SCC_PCLKDBG_CBCR_CLK_ENABLE_SHFT                                      0x0

#define HWIO_SSC_SCC_SCC_VS_BCR_ADDR                                                (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x0000a014)
#define HWIO_SSC_SCC_SCC_VS_BCR_OFFS                                                (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x0000a014)
#define HWIO_SSC_SCC_SCC_VS_BCR_RMSK                                                       0x1
#define HWIO_SSC_SCC_SCC_VS_BCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_VS_BCR_ADDR, HWIO_SSC_SCC_SCC_VS_BCR_RMSK)
#define HWIO_SSC_SCC_SCC_VS_BCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_VS_BCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_VS_BCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_VS_BCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_VS_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_VS_BCR_ADDR,m,v,HWIO_SSC_SCC_SCC_VS_BCR_IN)
#define HWIO_SSC_SCC_SCC_VS_BCR_BLK_ARES_BMSK                                              0x1
#define HWIO_SSC_SCC_SCC_VS_BCR_BLK_ARES_SHFT                                              0x0

#define HWIO_SSC_SCC_SCC_VS_VDDMX_CMD_RCGR_ADDR                                     (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x0000a018)
#define HWIO_SSC_SCC_SCC_VS_VDDMX_CMD_RCGR_OFFS                                     (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x0000a018)
#define HWIO_SSC_SCC_SCC_VS_VDDMX_CMD_RCGR_RMSK                                     0x80000013
#define HWIO_SSC_SCC_SCC_VS_VDDMX_CMD_RCGR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_VS_VDDMX_CMD_RCGR_ADDR, HWIO_SSC_SCC_SCC_VS_VDDMX_CMD_RCGR_RMSK)
#define HWIO_SSC_SCC_SCC_VS_VDDMX_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_VS_VDDMX_CMD_RCGR_ADDR, m)
#define HWIO_SSC_SCC_SCC_VS_VDDMX_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_VS_VDDMX_CMD_RCGR_ADDR,v)
#define HWIO_SSC_SCC_SCC_VS_VDDMX_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_VS_VDDMX_CMD_RCGR_ADDR,m,v,HWIO_SSC_SCC_SCC_VS_VDDMX_CMD_RCGR_IN)
#define HWIO_SSC_SCC_SCC_VS_VDDMX_CMD_RCGR_ROOT_OFF_BMSK                            0x80000000
#define HWIO_SSC_SCC_SCC_VS_VDDMX_CMD_RCGR_ROOT_OFF_SHFT                                  0x1f
#define HWIO_SSC_SCC_SCC_VS_VDDMX_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                            0x10
#define HWIO_SSC_SCC_SCC_VS_VDDMX_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                             0x4
#define HWIO_SSC_SCC_SCC_VS_VDDMX_CMD_RCGR_ROOT_EN_BMSK                                    0x2
#define HWIO_SSC_SCC_SCC_VS_VDDMX_CMD_RCGR_ROOT_EN_SHFT                                    0x1
#define HWIO_SSC_SCC_SCC_VS_VDDMX_CMD_RCGR_UPDATE_BMSK                                     0x1
#define HWIO_SSC_SCC_SCC_VS_VDDMX_CMD_RCGR_UPDATE_SHFT                                     0x0

#define HWIO_SSC_SCC_SCC_VS_VDDMX_CFG_RCGR_ADDR                                     (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x0000a01c)
#define HWIO_SSC_SCC_SCC_VS_VDDMX_CFG_RCGR_OFFS                                     (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x0000a01c)
#define HWIO_SSC_SCC_SCC_VS_VDDMX_CFG_RCGR_RMSK                                          0x71f
#define HWIO_SSC_SCC_SCC_VS_VDDMX_CFG_RCGR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_VS_VDDMX_CFG_RCGR_ADDR, HWIO_SSC_SCC_SCC_VS_VDDMX_CFG_RCGR_RMSK)
#define HWIO_SSC_SCC_SCC_VS_VDDMX_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_VS_VDDMX_CFG_RCGR_ADDR, m)
#define HWIO_SSC_SCC_SCC_VS_VDDMX_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_VS_VDDMX_CFG_RCGR_ADDR,v)
#define HWIO_SSC_SCC_SCC_VS_VDDMX_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_VS_VDDMX_CFG_RCGR_ADDR,m,v,HWIO_SSC_SCC_SCC_VS_VDDMX_CFG_RCGR_IN)
#define HWIO_SSC_SCC_SCC_VS_VDDMX_CFG_RCGR_SRC_SEL_BMSK                                  0x700
#define HWIO_SSC_SCC_SCC_VS_VDDMX_CFG_RCGR_SRC_SEL_SHFT                                    0x8
#define HWIO_SSC_SCC_SCC_VS_VDDMX_CFG_RCGR_SRC_DIV_BMSK                                   0x1f
#define HWIO_SSC_SCC_SCC_VS_VDDMX_CFG_RCGR_SRC_DIV_SHFT                                    0x0

#define HWIO_SSC_SCC_SCC_VS_VDDCX_CMD_RCGR_ADDR                                     (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x0000a030)
#define HWIO_SSC_SCC_SCC_VS_VDDCX_CMD_RCGR_OFFS                                     (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x0000a030)
#define HWIO_SSC_SCC_SCC_VS_VDDCX_CMD_RCGR_RMSK                                     0x80000013
#define HWIO_SSC_SCC_SCC_VS_VDDCX_CMD_RCGR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_VS_VDDCX_CMD_RCGR_ADDR, HWIO_SSC_SCC_SCC_VS_VDDCX_CMD_RCGR_RMSK)
#define HWIO_SSC_SCC_SCC_VS_VDDCX_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_VS_VDDCX_CMD_RCGR_ADDR, m)
#define HWIO_SSC_SCC_SCC_VS_VDDCX_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_VS_VDDCX_CMD_RCGR_ADDR,v)
#define HWIO_SSC_SCC_SCC_VS_VDDCX_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_VS_VDDCX_CMD_RCGR_ADDR,m,v,HWIO_SSC_SCC_SCC_VS_VDDCX_CMD_RCGR_IN)
#define HWIO_SSC_SCC_SCC_VS_VDDCX_CMD_RCGR_ROOT_OFF_BMSK                            0x80000000
#define HWIO_SSC_SCC_SCC_VS_VDDCX_CMD_RCGR_ROOT_OFF_SHFT                                  0x1f
#define HWIO_SSC_SCC_SCC_VS_VDDCX_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                            0x10
#define HWIO_SSC_SCC_SCC_VS_VDDCX_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                             0x4
#define HWIO_SSC_SCC_SCC_VS_VDDCX_CMD_RCGR_ROOT_EN_BMSK                                    0x2
#define HWIO_SSC_SCC_SCC_VS_VDDCX_CMD_RCGR_ROOT_EN_SHFT                                    0x1
#define HWIO_SSC_SCC_SCC_VS_VDDCX_CMD_RCGR_UPDATE_BMSK                                     0x1
#define HWIO_SSC_SCC_SCC_VS_VDDCX_CMD_RCGR_UPDATE_SHFT                                     0x0

#define HWIO_SSC_SCC_SCC_VS_VDDCX_CFG_RCGR_ADDR                                     (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x0000a034)
#define HWIO_SSC_SCC_SCC_VS_VDDCX_CFG_RCGR_OFFS                                     (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x0000a034)
#define HWIO_SSC_SCC_SCC_VS_VDDCX_CFG_RCGR_RMSK                                          0x71f
#define HWIO_SSC_SCC_SCC_VS_VDDCX_CFG_RCGR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_VS_VDDCX_CFG_RCGR_ADDR, HWIO_SSC_SCC_SCC_VS_VDDCX_CFG_RCGR_RMSK)
#define HWIO_SSC_SCC_SCC_VS_VDDCX_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_VS_VDDCX_CFG_RCGR_ADDR, m)
#define HWIO_SSC_SCC_SCC_VS_VDDCX_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_VS_VDDCX_CFG_RCGR_ADDR,v)
#define HWIO_SSC_SCC_SCC_VS_VDDCX_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_VS_VDDCX_CFG_RCGR_ADDR,m,v,HWIO_SSC_SCC_SCC_VS_VDDCX_CFG_RCGR_IN)
#define HWIO_SSC_SCC_SCC_VS_VDDCX_CFG_RCGR_SRC_SEL_BMSK                                  0x700
#define HWIO_SSC_SCC_SCC_VS_VDDCX_CFG_RCGR_SRC_SEL_SHFT                                    0x8
#define HWIO_SSC_SCC_SCC_VS_VDDCX_CFG_RCGR_SRC_DIV_BMSK                                   0x1f
#define HWIO_SSC_SCC_SCC_VS_VDDCX_CFG_RCGR_SRC_DIV_SHFT                                    0x0

#define HWIO_SSC_SCC_SCC_VS_VDDMX_CBCR_ADDR                                         (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x0000a048)
#define HWIO_SSC_SCC_SCC_VS_VDDMX_CBCR_OFFS                                         (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x0000a048)
#define HWIO_SSC_SCC_SCC_VS_VDDMX_CBCR_RMSK                                         0x80000001
#define HWIO_SSC_SCC_SCC_VS_VDDMX_CBCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_VS_VDDMX_CBCR_ADDR, HWIO_SSC_SCC_SCC_VS_VDDMX_CBCR_RMSK)
#define HWIO_SSC_SCC_SCC_VS_VDDMX_CBCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_VS_VDDMX_CBCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_VS_VDDMX_CBCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_VS_VDDMX_CBCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_VS_VDDMX_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_VS_VDDMX_CBCR_ADDR,m,v,HWIO_SSC_SCC_SCC_VS_VDDMX_CBCR_IN)
#define HWIO_SSC_SCC_SCC_VS_VDDMX_CBCR_CLK_OFF_BMSK                                 0x80000000
#define HWIO_SSC_SCC_SCC_VS_VDDMX_CBCR_CLK_OFF_SHFT                                       0x1f
#define HWIO_SSC_SCC_SCC_VS_VDDMX_CBCR_CLK_ENABLE_BMSK                                     0x1
#define HWIO_SSC_SCC_SCC_VS_VDDMX_CBCR_CLK_ENABLE_SHFT                                     0x0

#define HWIO_SSC_SCC_SCC_VS_VDDCX_CBCR_ADDR                                         (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x0000a04c)
#define HWIO_SSC_SCC_SCC_VS_VDDCX_CBCR_OFFS                                         (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x0000a04c)
#define HWIO_SSC_SCC_SCC_VS_VDDCX_CBCR_RMSK                                         0x80000001
#define HWIO_SSC_SCC_SCC_VS_VDDCX_CBCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_VS_VDDCX_CBCR_ADDR, HWIO_SSC_SCC_SCC_VS_VDDCX_CBCR_RMSK)
#define HWIO_SSC_SCC_SCC_VS_VDDCX_CBCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_VS_VDDCX_CBCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_VS_VDDCX_CBCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_VS_VDDCX_CBCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_VS_VDDCX_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_VS_VDDCX_CBCR_ADDR,m,v,HWIO_SSC_SCC_SCC_VS_VDDCX_CBCR_IN)
#define HWIO_SSC_SCC_SCC_VS_VDDCX_CBCR_CLK_OFF_BMSK                                 0x80000000
#define HWIO_SSC_SCC_SCC_VS_VDDCX_CBCR_CLK_OFF_SHFT                                       0x1f
#define HWIO_SSC_SCC_SCC_VS_VDDCX_CBCR_CLK_ENABLE_BMSK                                     0x1
#define HWIO_SSC_SCC_SCC_VS_VDDCX_CBCR_CLK_ENABLE_SHFT                                     0x0

#define HWIO_SSC_SCC_SCC_DBG_TSCTR_BCR_ADDR                                         (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x0000a050)
#define HWIO_SSC_SCC_SCC_DBG_TSCTR_BCR_OFFS                                         (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x0000a050)
#define HWIO_SSC_SCC_SCC_DBG_TSCTR_BCR_RMSK                                                0x1
#define HWIO_SSC_SCC_SCC_DBG_TSCTR_BCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_DBG_TSCTR_BCR_ADDR, HWIO_SSC_SCC_SCC_DBG_TSCTR_BCR_RMSK)
#define HWIO_SSC_SCC_SCC_DBG_TSCTR_BCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_DBG_TSCTR_BCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_DBG_TSCTR_BCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_DBG_TSCTR_BCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_DBG_TSCTR_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_DBG_TSCTR_BCR_ADDR,m,v,HWIO_SSC_SCC_SCC_DBG_TSCTR_BCR_IN)
#define HWIO_SSC_SCC_SCC_DBG_TSCTR_BCR_BLK_ARES_BMSK                                       0x1
#define HWIO_SSC_SCC_SCC_DBG_TSCTR_BCR_BLK_ARES_SHFT                                       0x0

#define HWIO_SSC_SCC_SCC_DBG_TSCTR_CBCR_ADDR                                        (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x0000a054)
#define HWIO_SSC_SCC_SCC_DBG_TSCTR_CBCR_OFFS                                        (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x0000a054)
#define HWIO_SSC_SCC_SCC_DBG_TSCTR_CBCR_RMSK                                        0x80070001
#define HWIO_SSC_SCC_SCC_DBG_TSCTR_CBCR_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_DBG_TSCTR_CBCR_ADDR, HWIO_SSC_SCC_SCC_DBG_TSCTR_CBCR_RMSK)
#define HWIO_SSC_SCC_SCC_DBG_TSCTR_CBCR_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_DBG_TSCTR_CBCR_ADDR, m)
#define HWIO_SSC_SCC_SCC_DBG_TSCTR_CBCR_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_DBG_TSCTR_CBCR_ADDR,v)
#define HWIO_SSC_SCC_SCC_DBG_TSCTR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_DBG_TSCTR_CBCR_ADDR,m,v,HWIO_SSC_SCC_SCC_DBG_TSCTR_CBCR_IN)
#define HWIO_SSC_SCC_SCC_DBG_TSCTR_CBCR_CLK_OFF_BMSK                                0x80000000
#define HWIO_SSC_SCC_SCC_DBG_TSCTR_CBCR_CLK_OFF_SHFT                                      0x1f
#define HWIO_SSC_SCC_SCC_DBG_TSCTR_CBCR_CLK_DIV_BMSK                                   0x70000
#define HWIO_SSC_SCC_SCC_DBG_TSCTR_CBCR_CLK_DIV_SHFT                                      0x10
#define HWIO_SSC_SCC_SCC_DBG_TSCTR_CBCR_CLK_ENABLE_BMSK                                    0x1
#define HWIO_SSC_SCC_SCC_DBG_TSCTR_CBCR_CLK_ENABLE_SHFT                                    0x0

#define HWIO_SSC_SCC_SCC_SPI_I2C1_CLK_CDIV_REG_ADDR                                 (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00002004)
#define HWIO_SSC_SCC_SCC_SPI_I2C1_CLK_CDIV_REG_OFFS                                 (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00002004)
#define HWIO_SSC_SCC_SCC_SPI_I2C1_CLK_CDIV_REG_RMSK                                      0x1ff
#define HWIO_SSC_SCC_SCC_SPI_I2C1_CLK_CDIV_REG_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_SPI_I2C1_CLK_CDIV_REG_ADDR, HWIO_SSC_SCC_SCC_SPI_I2C1_CLK_CDIV_REG_RMSK)
#define HWIO_SSC_SCC_SCC_SPI_I2C1_CLK_CDIV_REG_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_SPI_I2C1_CLK_CDIV_REG_ADDR, m)
#define HWIO_SSC_SCC_SCC_SPI_I2C1_CLK_CDIV_REG_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_SPI_I2C1_CLK_CDIV_REG_ADDR,v)
#define HWIO_SSC_SCC_SCC_SPI_I2C1_CLK_CDIV_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_SPI_I2C1_CLK_CDIV_REG_ADDR,m,v,HWIO_SSC_SCC_SCC_SPI_I2C1_CLK_CDIV_REG_IN)
#define HWIO_SSC_SCC_SCC_SPI_I2C1_CLK_CDIV_REG_CLK_DIV_BMSK                              0x1ff
#define HWIO_SSC_SCC_SCC_SPI_I2C1_CLK_CDIV_REG_CLK_DIV_SHFT                                0x0

#define HWIO_SSC_SCC_SCC_SPI_I2C2_CLK_CDIV_REG_ADDR                                 (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00003004)
#define HWIO_SSC_SCC_SCC_SPI_I2C2_CLK_CDIV_REG_OFFS                                 (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00003004)
#define HWIO_SSC_SCC_SCC_SPI_I2C2_CLK_CDIV_REG_RMSK                                      0x1ff
#define HWIO_SSC_SCC_SCC_SPI_I2C2_CLK_CDIV_REG_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_SPI_I2C2_CLK_CDIV_REG_ADDR, HWIO_SSC_SCC_SCC_SPI_I2C2_CLK_CDIV_REG_RMSK)
#define HWIO_SSC_SCC_SCC_SPI_I2C2_CLK_CDIV_REG_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_SPI_I2C2_CLK_CDIV_REG_ADDR, m)
#define HWIO_SSC_SCC_SCC_SPI_I2C2_CLK_CDIV_REG_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_SPI_I2C2_CLK_CDIV_REG_ADDR,v)
#define HWIO_SSC_SCC_SCC_SPI_I2C2_CLK_CDIV_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_SPI_I2C2_CLK_CDIV_REG_ADDR,m,v,HWIO_SSC_SCC_SCC_SPI_I2C2_CLK_CDIV_REG_IN)
#define HWIO_SSC_SCC_SCC_SPI_I2C2_CLK_CDIV_REG_CLK_DIV_BMSK                              0x1ff
#define HWIO_SSC_SCC_SCC_SPI_I2C2_CLK_CDIV_REG_CLK_DIV_SHFT                                0x0

#define HWIO_SSC_SCC_SCC_SPI_I2C3_CLK_CDIV_REG_ADDR                                 (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00004004)
#define HWIO_SSC_SCC_SCC_SPI_I2C3_CLK_CDIV_REG_OFFS                                 (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00004004)
#define HWIO_SSC_SCC_SCC_SPI_I2C3_CLK_CDIV_REG_RMSK                                      0x1ff
#define HWIO_SSC_SCC_SCC_SPI_I2C3_CLK_CDIV_REG_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_SPI_I2C3_CLK_CDIV_REG_ADDR, HWIO_SSC_SCC_SCC_SPI_I2C3_CLK_CDIV_REG_RMSK)
#define HWIO_SSC_SCC_SCC_SPI_I2C3_CLK_CDIV_REG_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_SPI_I2C3_CLK_CDIV_REG_ADDR, m)
#define HWIO_SSC_SCC_SCC_SPI_I2C3_CLK_CDIV_REG_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_SPI_I2C3_CLK_CDIV_REG_ADDR,v)
#define HWIO_SSC_SCC_SCC_SPI_I2C3_CLK_CDIV_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_SPI_I2C3_CLK_CDIV_REG_ADDR,m,v,HWIO_SSC_SCC_SCC_SPI_I2C3_CLK_CDIV_REG_IN)
#define HWIO_SSC_SCC_SCC_SPI_I2C3_CLK_CDIV_REG_CLK_DIV_BMSK                              0x1ff
#define HWIO_SSC_SCC_SCC_SPI_I2C3_CLK_CDIV_REG_CLK_DIV_SHFT                                0x0

#define HWIO_SSC_SCC_SCC_BUS_CLK_CDIV_REG_ADDR                                      (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00009004)
#define HWIO_SSC_SCC_SCC_BUS_CLK_CDIV_REG_OFFS                                      (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00009004)
#define HWIO_SSC_SCC_SCC_BUS_CLK_CDIV_REG_RMSK                                         0x70000
#define HWIO_SSC_SCC_SCC_BUS_CLK_CDIV_REG_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_BUS_CLK_CDIV_REG_ADDR, HWIO_SSC_SCC_SCC_BUS_CLK_CDIV_REG_RMSK)
#define HWIO_SSC_SCC_SCC_BUS_CLK_CDIV_REG_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_BUS_CLK_CDIV_REG_ADDR, m)
#define HWIO_SSC_SCC_SCC_BUS_CLK_CDIV_REG_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_BUS_CLK_CDIV_REG_ADDR,v)
#define HWIO_SSC_SCC_SCC_BUS_CLK_CDIV_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_BUS_CLK_CDIV_REG_ADDR,m,v,HWIO_SSC_SCC_SCC_BUS_CLK_CDIV_REG_IN)
#define HWIO_SSC_SCC_SCC_BUS_CLK_CDIV_REG_CLK_DIV_BMSK                                 0x70000
#define HWIO_SSC_SCC_SCC_BUS_CLK_CDIV_REG_CLK_DIV_SHFT                                    0x10

#define HWIO_SSC_SCC_SCC_DBG_CLK_CDIV_REG_ADDR                                      (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x0000a004)
#define HWIO_SSC_SCC_SCC_DBG_CLK_CDIV_REG_OFFS                                      (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x0000a004)
#define HWIO_SSC_SCC_SCC_DBG_CLK_CDIV_REG_RMSK                                         0x70000
#define HWIO_SSC_SCC_SCC_DBG_CLK_CDIV_REG_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_DBG_CLK_CDIV_REG_ADDR, HWIO_SSC_SCC_SCC_DBG_CLK_CDIV_REG_RMSK)
#define HWIO_SSC_SCC_SCC_DBG_CLK_CDIV_REG_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_DBG_CLK_CDIV_REG_ADDR, m)
#define HWIO_SSC_SCC_SCC_DBG_CLK_CDIV_REG_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_DBG_CLK_CDIV_REG_ADDR,v)
#define HWIO_SSC_SCC_SCC_DBG_CLK_CDIV_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_DBG_CLK_CDIV_REG_ADDR,m,v,HWIO_SSC_SCC_SCC_DBG_CLK_CDIV_REG_IN)
#define HWIO_SSC_SCC_SCC_DBG_CLK_CDIV_REG_CLK_DIV_BMSK                                 0x70000
#define HWIO_SSC_SCC_SCC_DBG_CLK_CDIV_REG_CLK_DIV_SHFT                                    0x10

#define HWIO_SSC_SCC_SCC_Q6_MISC_ADDR                                               (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00000040)
#define HWIO_SSC_SCC_SCC_Q6_MISC_OFFS                                               (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00000040)
#define HWIO_SSC_SCC_SCC_Q6_MISC_RMSK                                                      0x1
#define HWIO_SSC_SCC_SCC_Q6_MISC_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_Q6_MISC_ADDR, HWIO_SSC_SCC_SCC_Q6_MISC_RMSK)
#define HWIO_SSC_SCC_SCC_Q6_MISC_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_Q6_MISC_ADDR, m)
#define HWIO_SSC_SCC_SCC_Q6_MISC_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_Q6_MISC_ADDR,v)
#define HWIO_SSC_SCC_SCC_Q6_MISC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_Q6_MISC_ADDR,m,v,HWIO_SSC_SCC_SCC_Q6_MISC_IN)
#define HWIO_SSC_SCC_SCC_Q6_MISC_Q6_REF_CLK_SEL_BMSK                                       0x1
#define HWIO_SSC_SCC_SCC_Q6_MISC_Q6_REF_CLK_SEL_SHFT                                       0x0

#define HWIO_SSC_SCC_SCC_CBC_MISC_ADDR                                              (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00000044)
#define HWIO_SSC_SCC_SCC_CBC_MISC_OFFS                                              (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00000044)
#define HWIO_SSC_SCC_SCC_CBC_MISC_RMSK                                                     0x1
#define HWIO_SSC_SCC_SCC_CBC_MISC_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_CBC_MISC_ADDR, HWIO_SSC_SCC_SCC_CBC_MISC_RMSK)
#define HWIO_SSC_SCC_SCC_CBC_MISC_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_CBC_MISC_ADDR, m)
#define HWIO_SSC_SCC_SCC_CBC_MISC_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_CBC_MISC_ADDR,v)
#define HWIO_SSC_SCC_SCC_CBC_MISC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_CBC_MISC_ADDR,m,v,HWIO_SSC_SCC_SCC_CBC_MISC_IN)
#define HWIO_SSC_SCC_SCC_CBC_MISC_SCC_IDDQ_ALL_CBC_DIS_BMSK                                0x1
#define HWIO_SSC_SCC_SCC_CBC_MISC_SCC_IDDQ_ALL_CBC_DIS_SHFT                                0x0

#define HWIO_SSC_SCC_SCC_DEBUG_CLK_CTL_ADDR                                         (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00000048)
#define HWIO_SSC_SCC_SCC_DEBUG_CLK_CTL_OFFS                                         (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00000048)
#define HWIO_SSC_SCC_SCC_DEBUG_CLK_CTL_RMSK                                            0x1ffff
#define HWIO_SSC_SCC_SCC_DEBUG_CLK_CTL_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_DEBUG_CLK_CTL_ADDR, HWIO_SSC_SCC_SCC_DEBUG_CLK_CTL_RMSK)
#define HWIO_SSC_SCC_SCC_DEBUG_CLK_CTL_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_DEBUG_CLK_CTL_ADDR, m)
#define HWIO_SSC_SCC_SCC_DEBUG_CLK_CTL_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_DEBUG_CLK_CTL_ADDR,v)
#define HWIO_SSC_SCC_SCC_DEBUG_CLK_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_DEBUG_CLK_CTL_ADDR,m,v,HWIO_SSC_SCC_SCC_DEBUG_CLK_CTL_IN)
#define HWIO_SSC_SCC_SCC_DEBUG_CLK_CTL_PLL_TEST_CLK_ENABLE_BMSK                        0x10000
#define HWIO_SSC_SCC_SCC_DEBUG_CLK_CTL_PLL_TEST_CLK_ENABLE_SHFT                           0x10
#define HWIO_SSC_SCC_SCC_DEBUG_CLK_CTL_PLL_TEST_POST_DIV_BMSK                           0xf000
#define HWIO_SSC_SCC_SCC_DEBUG_CLK_CTL_PLL_TEST_POST_DIV_SHFT                              0xc
#define HWIO_SSC_SCC_SCC_DEBUG_CLK_CTL_PLL_TEST_SEL_BMSK                                 0xc00
#define HWIO_SSC_SCC_SCC_DEBUG_CLK_CTL_PLL_TEST_SEL_SHFT                                   0xa
#define HWIO_SSC_SCC_SCC_DEBUG_CLK_CTL_PLL_BYPASSNL_MUX_SEL_BMSK                         0x200
#define HWIO_SSC_SCC_SCC_DEBUG_CLK_CTL_PLL_BYPASSNL_MUX_SEL_SHFT                           0x9
#define HWIO_SSC_SCC_SCC_DEBUG_CLK_CTL_PLL_RESETN_MUX_SEL_BMSK                           0x180
#define HWIO_SSC_SCC_SCC_DEBUG_CLK_CTL_PLL_RESETN_MUX_SEL_SHFT                             0x7
#define HWIO_SSC_SCC_SCC_DEBUG_CLK_CTL_MUX_SEL_BMSK                                       0x7e
#define HWIO_SSC_SCC_SCC_DEBUG_CLK_CTL_MUX_SEL_SHFT                                        0x1
#define HWIO_SSC_SCC_SCC_DEBUG_CLK_CTL_CLK_ENABLE_BMSK                                     0x1
#define HWIO_SSC_SCC_SCC_DEBUG_CLK_CTL_CLK_ENABLE_SHFT                                     0x0

#define HWIO_SSC_SCC_SCC_PLL_OUT_MAIN_CLK_DIV_REG_ADDR                              (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x0000004c)
#define HWIO_SSC_SCC_SCC_PLL_OUT_MAIN_CLK_DIV_REG_OFFS                              (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x0000004c)
#define HWIO_SSC_SCC_SCC_PLL_OUT_MAIN_CLK_DIV_REG_RMSK                                 0xf0000
#define HWIO_SSC_SCC_SCC_PLL_OUT_MAIN_CLK_DIV_REG_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_PLL_OUT_MAIN_CLK_DIV_REG_ADDR, HWIO_SSC_SCC_SCC_PLL_OUT_MAIN_CLK_DIV_REG_RMSK)
#define HWIO_SSC_SCC_SCC_PLL_OUT_MAIN_CLK_DIV_REG_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_PLL_OUT_MAIN_CLK_DIV_REG_ADDR, m)
#define HWIO_SSC_SCC_SCC_PLL_OUT_MAIN_CLK_DIV_REG_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_PLL_OUT_MAIN_CLK_DIV_REG_ADDR,v)
#define HWIO_SSC_SCC_SCC_PLL_OUT_MAIN_CLK_DIV_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_PLL_OUT_MAIN_CLK_DIV_REG_ADDR,m,v,HWIO_SSC_SCC_SCC_PLL_OUT_MAIN_CLK_DIV_REG_IN)
#define HWIO_SSC_SCC_SCC_PLL_OUT_MAIN_CLK_DIV_REG_CLK_DIV_BMSK                         0xf0000
#define HWIO_SSC_SCC_SCC_PLL_OUT_MAIN_CLK_DIV_REG_CLK_DIV_SHFT                            0x10

#define HWIO_SSC_SCC_SCC_AON_CTRL_OVRD_REG_ADDR                                     (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x00000050)
#define HWIO_SSC_SCC_SCC_AON_CTRL_OVRD_REG_OFFS                                     (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x00000050)
#define HWIO_SSC_SCC_SCC_AON_CTRL_OVRD_REG_RMSK                                           0x3f
#define HWIO_SSC_SCC_SCC_AON_CTRL_OVRD_REG_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_AON_CTRL_OVRD_REG_ADDR, HWIO_SSC_SCC_SCC_AON_CTRL_OVRD_REG_RMSK)
#define HWIO_SSC_SCC_SCC_AON_CTRL_OVRD_REG_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_AON_CTRL_OVRD_REG_ADDR, m)
#define HWIO_SSC_SCC_SCC_AON_CTRL_OVRD_REG_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_AON_CTRL_OVRD_REG_ADDR,v)
#define HWIO_SSC_SCC_SCC_AON_CTRL_OVRD_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_AON_CTRL_OVRD_REG_ADDR,m,v,HWIO_SSC_SCC_SCC_AON_CTRL_OVRD_REG_IN)
#define HWIO_SSC_SCC_SCC_AON_CTRL_OVRD_REG_SLEEP_CLK_SEL_OVRD_VAL_BMSK                    0x20
#define HWIO_SSC_SCC_SCC_AON_CTRL_OVRD_REG_SLEEP_CLK_SEL_OVRD_VAL_SHFT                     0x5
#define HWIO_SSC_SCC_SCC_AON_CTRL_OVRD_REG_SLEEP_CLK_SEL_OVRD_BMSK                        0x10
#define HWIO_SSC_SCC_SCC_AON_CTRL_OVRD_REG_SLEEP_CLK_SEL_OVRD_SHFT                         0x4
#define HWIO_SSC_SCC_SCC_AON_CTRL_OVRD_REG_CBC_EN_OVRD_VAL_BMSK                            0x8
#define HWIO_SSC_SCC_SCC_AON_CTRL_OVRD_REG_CBC_EN_OVRD_VAL_SHFT                            0x3
#define HWIO_SSC_SCC_SCC_AON_CTRL_OVRD_REG_CBC_EN_OVRD_BMSK                                0x4
#define HWIO_SSC_SCC_SCC_AON_CTRL_OVRD_REG_CBC_EN_OVRD_SHFT                                0x2
#define HWIO_SSC_SCC_SCC_AON_CTRL_OVRD_REG_PLL_OUT_CTRL_OVRD_BMSK                          0x2
#define HWIO_SSC_SCC_SCC_AON_CTRL_OVRD_REG_PLL_OUT_CTRL_OVRD_SHFT                          0x1
#define HWIO_SSC_SCC_SCC_AON_CTRL_OVRD_REG_PLL_OPMODE_CTRL_OVRD_BMSK                       0x1
#define HWIO_SSC_SCC_SCC_AON_CTRL_OVRD_REG_PLL_OPMODE_CTRL_OVRD_SHFT                       0x0

#define HWIO_SSC_SCC_SCC_SPARE_1_ADDR                                               (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x0000b000)
#define HWIO_SSC_SCC_SCC_SPARE_1_OFFS                                               (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x0000b000)
#define HWIO_SSC_SCC_SCC_SPARE_1_RMSK                                               0xffffffff
#define HWIO_SSC_SCC_SCC_SPARE_1_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_SPARE_1_ADDR, HWIO_SSC_SCC_SCC_SPARE_1_RMSK)
#define HWIO_SSC_SCC_SCC_SPARE_1_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_SPARE_1_ADDR, m)
#define HWIO_SSC_SCC_SCC_SPARE_1_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_SPARE_1_ADDR,v)
#define HWIO_SSC_SCC_SCC_SPARE_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_SPARE_1_ADDR,m,v,HWIO_SSC_SCC_SCC_SPARE_1_IN)
#define HWIO_SSC_SCC_SCC_SPARE_1_SCC_SPARE_IN_BMSK                                  0xffff0000
#define HWIO_SSC_SCC_SCC_SPARE_1_SCC_SPARE_IN_SHFT                                        0x10
#define HWIO_SSC_SCC_SCC_SPARE_1_SCC_SPARE_OUT_BMSK                                     0xffff
#define HWIO_SSC_SCC_SCC_SPARE_1_SCC_SPARE_OUT_SHFT                                        0x0

#define HWIO_SSC_SCC_SCC_SPARE_2_ADDR                                               (SSC_SCC_SCC_SCC_REG_REG_BASE      + 0x0000c000)
#define HWIO_SSC_SCC_SCC_SPARE_2_OFFS                                               (SSC_SCC_SCC_SCC_REG_REG_BASE_OFFS + 0x0000c000)
#define HWIO_SSC_SCC_SCC_SPARE_2_RMSK                                               0xffffffff
#define HWIO_SSC_SCC_SCC_SPARE_2_IN          \
        in_dword_masked(HWIO_SSC_SCC_SCC_SPARE_2_ADDR, HWIO_SSC_SCC_SCC_SPARE_2_RMSK)
#define HWIO_SSC_SCC_SCC_SPARE_2_INM(m)      \
        in_dword_masked(HWIO_SSC_SCC_SCC_SPARE_2_ADDR, m)
#define HWIO_SSC_SCC_SCC_SPARE_2_OUT(v)      \
        out_dword(HWIO_SSC_SCC_SCC_SPARE_2_ADDR,v)
#define HWIO_SSC_SCC_SCC_SPARE_2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SCC_SCC_SPARE_2_ADDR,m,v,HWIO_SSC_SCC_SCC_SPARE_2_IN)
#define HWIO_SSC_SCC_SCC_SPARE_2_SCC_SPARE_IN_BMSK                                  0xffff0000
#define HWIO_SSC_SCC_SCC_SPARE_2_SCC_SPARE_IN_SHFT                                        0x10
#define HWIO_SSC_SCC_SCC_SPARE_2_SCC_SPARE_OUT_BMSK                                     0xffff
#define HWIO_SSC_SCC_SCC_SPARE_2_SCC_SPARE_OUT_SHFT                                        0x0


#endif /* __UCLOCKHWIO_H__ */
