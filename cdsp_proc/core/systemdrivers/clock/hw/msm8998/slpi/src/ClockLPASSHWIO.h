#ifndef __CLOCKLPASSHWIO_H__
#define __CLOCKLPASSHWIO_H__
/*
===========================================================================
*/
/**
  @file ClockLPASSHWIO.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    MSM8998 (Nazgul) [nazgul_v1.0_p3q3r35]
 
  This file contains HWIO register definitions for the following modules:
    LPASS_LPASS_CC_REG
    LPASS_QDSP6V60SS_PUB

  'Include' filters applied: 
  'Exclude' filters applied: RESERVED DUMMY 
*/
/*
  ===========================================================================

  Copyright (c) 2016 Qualcomm Technologies Incorporated.
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

  $Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/clock/hw/msm8998/slpi/src/ClockLPASSHWIO.h#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $

  ===========================================================================
*/

#include "HALhwio.h"

/*=========================================================================
      Type Definitions
==========================================================================*/

extern uint32                      Clock_nHWIOBaseLPASS;
#define LPASS_BASE                 Clock_nHWIOBaseLPASS

extern uint32                      Clock_nHWIOBaseSecurity;
#define SECURITY_CONTROL_BASE      Clock_nHWIOBaseSecurity


/*----------------------------------------------------------------------------
 * MODULE: LPASS_LPASS_CC_REG
 *--------------------------------------------------------------------------*/

#define LPASS_LPASS_CC_REG_REG_BASE                                                                                   (LPASS_BASE      + 0x00000000)
#define LPASS_LPASS_CC_REG_REG_BASE_OFFS                                                                              0x00000000

#define HWIO_LPASS_LPAAUDIO_PLL_MODE_ADDR                                                                             (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000000)
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_OFFS                                                                             (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000000)
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_RMSK                                                                             0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_MODE_ADDR, HWIO_LPASS_LPAAUDIO_PLL_MODE_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_MODE_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_MODE_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_MODE_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_MODE_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_LOCK_DET_BMSK                                                                0x80000000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_LOCK_DET_SHFT                                                                      0x1f
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_ACTIVE_FLAG_BMSK                                                             0x40000000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_ACTIVE_FLAG_SHFT                                                                   0x1e
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_RESERVE_BITS29_22_BMSK                                                           0x3fc00000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_RESERVE_BITS29_22_SHFT                                                                 0x16
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_VOTE_FSM_RESET_BMSK                                                            0x200000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_VOTE_FSM_RESET_SHFT                                                                0x15
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_VOTE_FSM_ENA_BMSK                                                              0x100000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_VOTE_FSM_ENA_SHFT                                                                  0x14
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_BIAS_COUNT_BMSK                                                                 0xfc000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_BIAS_COUNT_SHFT                                                                     0xe
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_LOCK_COUNT_BMSK                                                                  0x3f00
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_LOCK_COUNT_SHFT                                                                     0x8
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_RESERVE_BITS7_4_BMSK                                                                   0xf0
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_RESERVE_BITS7_4_SHFT                                                                    0x4
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_PLLTEST_BMSK                                                                        0x8
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_PLLTEST_SHFT                                                                        0x3
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_RESET_N_BMSK                                                                        0x4
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_RESET_N_SHFT                                                                        0x2
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_BYPASSNL_BMSK                                                                       0x2
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_BYPASSNL_SHFT                                                                       0x1
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_OUTCTRL_BMSK                                                                        0x1
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_OUTCTRL_SHFT                                                                        0x0

#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_ADDR                                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000004)
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_OFFS                                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000004)
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_RMSK                                                                            0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_L_VAL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_L_VAL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_L_VAL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_L_VAL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_L_VAL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_L_VAL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_RESERVE_BITS_31_8_BMSK                                                          0xffffff00
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_RESERVE_BITS_31_8_SHFT                                                                 0x8
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_PLL_L_BMSK                                                                            0xff
#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_PLL_L_SHFT                                                                             0x0

#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_ADDR                                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000008)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_OFFS                                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000008)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_RMSK                                                                        0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_RESERVE_BITS_31_16_BMSK                                                     0xffff0000
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_RESERVE_BITS_31_16_SHFT                                                           0x10
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_PLL_ALPHA_BMSK                                                                  0xffff
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_PLL_ALPHA_SHFT                                                                     0x0

#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ADDR                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000000c)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_OFFS                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000000c)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RMSK                                                                         0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS31_28_BMSK                                                       0xf0000000
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS31_28_SHFT                                                             0x1c
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_SSC_EN_BMSK                                                                   0x8000000
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_SSC_EN_SHFT                                                                        0x1b
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BIT26_BMSK                                                            0x4000000
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BIT26_SHFT                                                                 0x1a
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ALPHA_MODE_BMSK                                                               0x2000000
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ALPHA_MODE_SHFT                                                                    0x19
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ALPHA_EN_BMSK                                                                 0x1000000
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ALPHA_EN_SHFT                                                                      0x18
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS23_21_BMSK                                                         0xe00000
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS23_21_SHFT                                                             0x15
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_DCO_POST_DIV_EN_BMSK                                                           0x100000
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_DCO_POST_DIV_EN_SHFT                                                               0x14
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS19_13_BMSK                                                          0xfe000
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS19_13_SHFT                                                              0xd
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PRE_DIV2_EN_BMSK                                                                 0x1000
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PRE_DIV2_EN_SHFT                                                                    0xc
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS11_10_BMSK                                                            0xc00
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS11_10_SHFT                                                              0xa
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_POSTDIV_CTL_BMSK                                                                  0x300
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_POSTDIV_CTL_SHFT                                                                    0x8
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_OUT_CLK_POLARITY_BMSK                                                              0x80
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_OUT_CLK_POLARITY_SHFT                                                               0x7
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS6_5_BMSK                                                               0x60
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS6_5_SHFT                                                                0x5
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_TEST_BMSK                                                                0x10
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_TEST_SHFT                                                                 0x4
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_EARLY_BMSK                                                                0x8
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_EARLY_SHFT                                                                0x3
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_AUX2_BMSK                                                                 0x4
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_AUX2_SHFT                                                                 0x2
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_AUX_BMSK                                                                  0x2
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_AUX_SHFT                                                                  0x1
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_MAIN_BMSK                                                                 0x1
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_PLLOUT_LV_MAIN_SHFT                                                                 0x0

#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_ADDR                                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000010)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_OFFS                                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000010)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_RMSK                                                                       0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_COMM_MODE_BMSK                                                             0xc0000000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_COMM_MODE_SHFT                                                                   0x1e
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_SAR_REF_BMSK                                                               0x30000000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_SAR_REF_SHFT                                                                     0x1c
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_SAR_DEL_BMSK                                                                0x8000000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_SAR_DEL_SHFT                                                                     0x1b
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_ICP_REF_DEL_INC_BMSK                                                        0x4000000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_ICP_REF_DEL_INC_SHFT                                                             0x1a
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_REF_TRIM_BMSK                                                               0x3800000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_REF_TRIM_SHFT                                                                    0x17
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_RESERVE_BIT22_BMSK                                                           0x400000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_RESERVE_BIT22_SHFT                                                               0x16
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_FBC_ALPHA_CAL_SEL_BMSK                                                       0x300000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_FBC_ALPHA_CAL_SEL_SHFT                                                           0x14
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_FBC_BETA_CAL_SEL_BMSK                                                         0xc0000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_FBC_BETA_CAL_SEL_SHFT                                                            0x12
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_BBC_DOUBLET_LEN_SEL_BMSK                                                      0x30000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_BBC_DOUBLET_LEN_SEL_SHFT                                                         0x10
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_BBC_UPDATE_LEN_SEL_BMSK                                                        0xc000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_BBC_UPDATE_LEN_SEL_SHFT                                                           0xe
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_P_FFA_SEL_BMSK                                                                 0x3c00
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_P_FFA_SEL_SHFT                                                                    0xa
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_K_P_TM_SEL_BMSK                                                                 0x300
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_K_P_TM_SEL_SHFT                                                                   0x8
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_K_I_TM_SEL_BMSK                                                                  0xc0
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_K_I_TM_SEL_SHFT                                                                   0x6
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_K_P_FFA_SEL_BMSK                                                                 0x30
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_K_P_FFA_SEL_SHFT                                                                  0x4
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_K_I_FFA_SEL_BMSK                                                                  0xc
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_K_I_FFA_SEL_SHFT                                                                  0x2
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_PFD_DZSEL_BMSK                                                                    0x3
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_PFD_DZSEL_SHFT                                                                    0x0

#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_ADDR                                                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000014)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_OFFS                                                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000014)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_RMSK                                                                     0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_ADDR, HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_FORCE_CFA_MODE_BMSK                                                      0x80000000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_FORCE_CFA_MODE_SHFT                                                            0x1f
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_TDL_BYPASS_BMSK                                                          0x40000000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_TDL_BYPASS_SHFT                                                                0x1e
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_RESETVE_BIT29_BMSK                                                       0x20000000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_RESETVE_BIT29_SHFT                                                             0x1d
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_DROOP_DIV_RESET_BMSK                                                     0x10000000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_DROOP_DIV_RESET_SHFT                                                           0x1c
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_JBIST_ENABLE_BMSK                                                         0x8000000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_JBIST_ENABLE_SHFT                                                              0x1b
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_L_VAL_JBIST_BMSK                                                          0x7f80000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_L_VAL_JBIST_SHFT                                                               0x13
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_EARLY_CLK_DIV_DROOP_MODE_BMSK                                               0x7e000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_EARLY_CLK_DIV_DROOP_MODE_SHFT                                                   0xd
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_DUTY_CYC_CTL_OVRD_BMSK                                                       0x1000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_DUTY_CYC_CTL_OVRD_SHFT                                                          0xc
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_CFA_GLITCH_DET_BYP_BMSK                                                       0x800
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_CFA_GLITCH_DET_BYP_SHFT                                                         0xb
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_DUTY_CYC_ADJ_BMSK                                                             0x7c0
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_DUTY_CYC_ADJ_SHFT                                                               0x6
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_OUTP_DUTY_CYC_CTL_BMSK                                                         0x20
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_OUTP_DUTY_CYC_CTL_SHFT                                                          0x5
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_DROOP_EN_OP_DELAY_BMSK                                                         0x18
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_DROOP_EN_OP_DELAY_SHFT                                                          0x3
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_LOW_JIT_MODE_EN_BMSK                                                            0x4
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_LOW_JIT_MODE_EN_SHFT                                                            0x2
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_CHR_PUMP_REF_CUR_ADJ_BMSK                                                       0x3
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_U_CHR_PUMP_REF_CUR_ADJ_SHFT                                                       0x0

#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ADDR                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000018)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_OFFS                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000018)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RMSK                                                                         0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RESERVE_BITS31_29_BMSK                                                       0xe0000000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RESERVE_BITS31_29_SHFT                                                             0x1d
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_LOCK_FAILURE_THRESHOLD_SEL_BMSK                                              0x18000000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_LOCK_FAILURE_THRESHOLD_SEL_SHFT                                                    0x1b
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_LOCK_FAILURE_TIMEOUT_EN_BMSK                                                  0x4000000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_LOCK_FAILURE_TIMEOUT_EN_SHFT                                                       0x1a
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_D_FINE_OVERRIDE_BMSK                                                          0x2000000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_D_FINE_OVERRIDE_SHFT                                                               0x19
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_G_BWC_OVERRIDE_VALUE_BMSK                                                     0x1fc0000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_G_BWC_OVERRIDE_VALUE_SHFT                                                          0x12
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_G_BWC_OVERRIDE_BMSK                                                             0x20000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_G_BWC_OVERRIDE_SHFT                                                                0x11
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_STAY_IN_CFA_BMSK                                                                0x10000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_STAY_IN_CFA_SHFT                                                                   0x10
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_SKIP_FFA_BMSK                                                                    0x8000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_SKIP_FFA_SHFT                                                                       0xf
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_SKIP_CFA_BMSK                                                                    0x4000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_SKIP_CFA_SHFT                                                                       0xe
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RESET_FFA_TM_ACCUM_BMSK                                                          0x2000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RESET_FFA_TM_ACCUM_SHFT                                                             0xd
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RESET_CFA_ACCUM_BMSK                                                             0x1000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RESET_CFA_ACCUM_SHFT                                                                0xc
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RESERVE_BIT11_BMSK                                                                0x800
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RESERVE_BIT11_SHFT                                                                  0xb
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_DISABLE_LFSR_BMSK                                                                 0x400
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_DISABLE_LFSR_SHFT                                                                   0xa
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ENABLE_BBC_BMSK                                                                   0x200
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ENABLE_BBC_SHFT                                                                     0x9
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_PLL_STATUS_SEL_BMSK                                                               0x1c0
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_PLL_STATUS_SEL_SHFT                                                                 0x6
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_DTEST_SEL_BMSK                                                                     0x20
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_DTEST_SEL_SHFT                                                                      0x5
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_BYP_TESTAMP_BMSK                                                                   0x10
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_BYP_TESTAMP_SHFT                                                                    0x4
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST1_SEL_BMSK                                                                     0xc
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST1_SEL_SHFT                                                                     0x2
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST1_EN_BMSK                                                                      0x2
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST1_EN_SHFT                                                                      0x1
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST0_EN_BMSK                                                                      0x1
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST0_EN_SHFT                                                                      0x0

#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_ADDR                                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000001c)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_OFFS                                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000001c)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_RMSK                                                                       0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_ADDR, HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_LV_TEST_SEL_BMSK                                                           0x80000000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_LV_TEST_SEL_SHFT                                                                 0x1f
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_CHRG_PUMP_PWR_DN_BMSK                                                      0x40000000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_CHRG_PUMP_PWR_DN_SHFT                                                            0x1e
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_ENABLE_FBC_BMSK                                                            0x20000000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_ENABLE_FBC_SHFT                                                                  0x1d
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_PTUNE_OVERRIDE_VAL_BMSK                                                    0x1c000000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_PTUNE_OVERRIDE_VAL_SHFT                                                          0x1a
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_PTUNE_OVERRIDE_BMSK                                                         0x2000000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_PTUNE_OVERRIDE_SHFT                                                              0x19
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_DIV_DC_SEL_BMSK                                                             0x1000000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_DIV_DC_SEL_SHFT                                                                  0x18
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_NGEN_CFG_BMSK                                                                0xc00000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_NGEN_CFG_SHFT                                                                    0x16
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_NGEN_EN_BMSK                                                                 0x200000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_NGEN_EN_SHFT                                                                     0x15
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_CHRG_PUMP_BIAS_BYP_BMSK                                                      0x100000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_CHRG_PUMP_BIAS_BYP_SHFT                                                          0x14
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_DEM_DCO_DAC_EN_BMSK                                                           0x80000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_DEM_DCO_DAC_EN_SHFT                                                              0x13
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_NMOSC_EN_BMSK                                                                 0x40000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_NMOSC_EN_SHFT                                                                    0x12
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_CFA_MODE_BMSK                                                                 0x20000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_CFA_MODE_SHFT                                                                    0x11
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_RESERVE_BIT18_BMSK                                                            0x10000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_RESERVE_BIT18_SHFT                                                               0x10
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_ADC_TEST_CLK_SEL_BMSK                                                          0x8000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_ADC_TEST_CLK_SEL_SHFT                                                             0xf
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_GLITCH_FILTER_EN_BMSK                                                          0x4000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_GLITCH_FILTER_EN_SHFT                                                             0xe
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_D_EXT_SEL_BMSK                                                                 0x2000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_D_EXT_SEL_SHFT                                                                    0xd
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_D_EXT_VAL_BMSK                                                                 0x1ff0
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_D_EXT_VAL_SHFT                                                                    0x4
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_ENTER_OLC_MODE_SEL_BMSK                                                           0x8
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_ENTER_OLC_MODE_SEL_SHFT                                                           0x3
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_RESERVE_BITS2_0_BMSK                                                              0x7
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_RESERVE_BITS2_0_SHFT                                                              0x0

#define HWIO_LPASS_LPAAUDIO_PLL_SSC_DELTA_ALPHA_ADDR                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000020)
#define HWIO_LPASS_LPAAUDIO_PLL_SSC_DELTA_ALPHA_OFFS                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000020)
#define HWIO_LPASS_LPAAUDIO_PLL_SSC_DELTA_ALPHA_RMSK                                                                  0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_SSC_DELTA_ALPHA_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_SSC_DELTA_ALPHA_ADDR, HWIO_LPASS_LPAAUDIO_PLL_SSC_DELTA_ALPHA_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_SSC_DELTA_ALPHA_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_SSC_DELTA_ALPHA_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_SSC_DELTA_ALPHA_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_SSC_DELTA_ALPHA_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_SSC_DELTA_ALPHA_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_SSC_DELTA_ALPHA_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_SSC_DELTA_ALPHA_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_SSC_DELTA_ALPHA_RESERVE_BITS_31_8_BMSK                                                0xffffff00
#define HWIO_LPASS_LPAAUDIO_PLL_SSC_DELTA_ALPHA_RESERVE_BITS_31_8_SHFT                                                       0x8
#define HWIO_LPASS_LPAAUDIO_PLL_SSC_DELTA_ALPHA_PLL_SCC_DELTA_ALPHA_BMSK                                                    0xff
#define HWIO_LPASS_LPAAUDIO_PLL_SSC_DELTA_ALPHA_PLL_SCC_DELTA_ALPHA_SHFT                                                     0x0

#define HWIO_LPASS_LPAAUDIO_PLL_SSC_UPDATE_RATE_ADDR                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000024)
#define HWIO_LPASS_LPAAUDIO_PLL_SSC_UPDATE_RATE_OFFS                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000024)
#define HWIO_LPASS_LPAAUDIO_PLL_SSC_UPDATE_RATE_RMSK                                                                  0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_SSC_UPDATE_RATE_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_SSC_UPDATE_RATE_ADDR, HWIO_LPASS_LPAAUDIO_PLL_SSC_UPDATE_RATE_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_SSC_UPDATE_RATE_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_SSC_UPDATE_RATE_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_SSC_UPDATE_RATE_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_SSC_UPDATE_RATE_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_SSC_UPDATE_RATE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_SSC_UPDATE_RATE_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_SSC_UPDATE_RATE_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_SSC_UPDATE_RATE_RESERVE_BITS_31_8_BMSK                                                0xffffff00
#define HWIO_LPASS_LPAAUDIO_PLL_SSC_UPDATE_RATE_RESERVE_BITS_31_8_SHFT                                                       0x8
#define HWIO_LPASS_LPAAUDIO_PLL_SSC_UPDATE_RATE_PLL_SCC_UPDATE_RATE_BMSK                                                    0xff
#define HWIO_LPASS_LPAAUDIO_PLL_SSC_UPDATE_RATE_PLL_SCC_UPDATE_RATE_SHFT                                                     0x0

#define HWIO_LPASS_LPAAUDIO_PLL_DROOP_CTL_ADDR                                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000028)
#define HWIO_LPASS_LPAAUDIO_PLL_DROOP_CTL_OFFS                                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000028)
#define HWIO_LPASS_LPAAUDIO_PLL_DROOP_CTL_RMSK                                                                        0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_DROOP_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_DROOP_CTL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_DROOP_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_DROOP_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_DROOP_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_DROOP_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_DROOP_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_DROOP_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_DROOP_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_DROOP_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_DROOP_CTL_RESERVE_BITS_31_15_BMSK                                                     0xffff8000
#define HWIO_LPASS_LPAAUDIO_PLL_DROOP_CTL_RESERVE_BITS_31_15_SHFT                                                            0xf
#define HWIO_LPASS_LPAAUDIO_PLL_DROOP_CTL_DROOP_CODE_BMSK                                                                 0x7f00
#define HWIO_LPASS_LPAAUDIO_PLL_DROOP_CTL_DROOP_CODE_SHFT                                                                    0x8
#define HWIO_LPASS_LPAAUDIO_PLL_DROOP_CTL_RESERVE_BITS_7_1_BMSK                                                             0xfe
#define HWIO_LPASS_LPAAUDIO_PLL_DROOP_CTL_RESERVE_BITS_7_1_SHFT                                                              0x1
#define HWIO_LPASS_LPAAUDIO_PLL_DROOP_CTL_DROOP_EN_BMSK                                                                      0x1
#define HWIO_LPASS_LPAAUDIO_PLL_DROOP_CTL_DROOP_EN_SHFT                                                                      0x0

#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_ADDR                                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000002c)
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_OFFS                                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000002c)
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_RMSK                                                                           0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_STATUS_ADDR, HWIO_LPASS_LPAAUDIO_PLL_STATUS_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_STATUS_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_STATUS_31_0_BMSK                                                               0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_STATUS_31_0_SHFT                                                                      0x0

#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_ADDR                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000030)
#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_OFFS                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000030)
#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_RMSK                                                                         0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_FREQUENCY_CTL_WORD_BMSK                                                      0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_FREQUENCY_CTL_WORD_SHFT                                                             0x0

#define HWIO_LPASS_LPAAUDIO_PLL_BIST_CTL_ADDR                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000034)
#define HWIO_LPASS_LPAAUDIO_PLL_BIST_CTL_OFFS                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000034)
#define HWIO_LPASS_LPAAUDIO_PLL_BIST_CTL_RMSK                                                                         0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_BIST_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_BIST_CTL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_BIST_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_BIST_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_BIST_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_BIST_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_BIST_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_BIST_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_BIST_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_BIST_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_BIST_CTL_RESERVE_BITS_31_12_BMSK                                                      0xfffff000
#define HWIO_LPASS_LPAAUDIO_PLL_BIST_CTL_RESERVE_BITS_31_12_SHFT                                                             0xc
#define HWIO_LPASS_LPAAUDIO_PLL_BIST_CTL_BIST_CTL_BMSK                                                                     0xfff
#define HWIO_LPASS_LPAAUDIO_PLL_BIST_CTL_BIST_CTL_SHFT                                                                       0x0

#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_ADDR                                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00000038)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_OFFS                                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00000038)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_RMSK                                                                              0xf
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_ADDR, HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_CLK_AUX2_CGC_EN_BMSK                                                              0x8
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_CLK_AUX2_CGC_EN_SHFT                                                              0x3
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_CLK_AUX_CGC_EN_BMSK                                                               0x4
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_CLK_AUX_CGC_EN_SHFT                                                               0x2
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_CLK_MAIN_SVS_CGC_EN_BMSK                                                          0x2
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_CLK_MAIN_SVS_CGC_EN_SHFT                                                          0x1
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_CLK_MAIN_CGC_EN_BMSK                                                              0x1
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_CLK_MAIN_CGC_EN_SHFT                                                              0x0

#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_ADDR                                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000003c)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_OFFS                                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000003c)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_RMSK                                                                              0x30f3
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_ADDR, HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_CLK_AUX2_DIV_BMSK                                                                 0x3000
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_CLK_AUX2_DIV_SHFT                                                                    0xc
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_CLK_AUX_DIV_BMSK                                                                    0xf0
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_CLK_AUX_DIV_SHFT                                                                     0x4
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_CLK_MAIN_DIV_BMSK                                                                    0x3
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_CLK_MAIN_DIV_SHFT                                                                    0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_ADDR                                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001004)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_OFFS                                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001004)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_RMSK                                                                            0xffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_PLL_L_BMSK                                                                      0xffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_PLL_L_SHFT                                                                         0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CAL_L_VAL_ADDR                                                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001008)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CAL_L_VAL_OFFS                                                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001008)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CAL_L_VAL_RMSK                                                                        0xffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CAL_L_VAL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_CAL_L_VAL_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_CAL_L_VAL_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CAL_L_VAL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_CAL_L_VAL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CAL_L_VAL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_CAL_L_VAL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CAL_L_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_CAL_L_VAL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_CAL_L_VAL_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CAL_L_VAL_PLL_CAL_L_BMSK                                                              0xffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CAL_L_VAL_PLL_CAL_L_SHFT                                                                 0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_ADDR                                                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000100c)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_OFFS                                                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000100c)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RMSK                                                                     0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RESERVE_BITS31_19_BMSK                                                   0xfff80000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RESERVE_BITS31_19_SHFT                                                         0x13
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PRE_DIV_RATIO_BMSK                                                          0x70000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PRE_DIV_RATIO_SHFT                                                             0x10
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_POST_DIV_RATIO_ODD_BMSK                                                      0xf000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_POST_DIV_RATIO_ODD_SHFT                                                         0xc
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_POST_DIV_RATIO_EVEN_BMSK                                                      0xf00
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_POST_DIV_RATIO_EVEN_SHFT                                                        0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_OUT_CLK_POLARITY_BMSK                                                          0x80
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_OUT_CLK_POLARITY_SHFT                                                           0x7
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RESERVE_BITS6_5_BMSK                                                           0x60
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RESERVE_BITS6_5_SHFT                                                            0x5
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_TEST_BMSK                                                               0x10
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_TEST_SHFT                                                                0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RESERVE_BITS3_BMSK                                                              0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RESERVE_BITS3_SHFT                                                              0x3
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_ODD_BMSK                                                                 0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_ODD_SHFT                                                                 0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_EVEN_BMSK                                                                0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_EVEN_SHFT                                                                0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_MAIN_BMSK                                                                0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_MAIN_SHFT                                                                0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_ADDR                                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001010)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_OFFS                                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001010)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_RMSK                                                                   0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_RESERVE_BITS31_19_BMSK                                                 0xfff80000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_RESERVE_BITS31_19_SHFT                                                       0x13
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_USE_PREDIV_WHEN_CAL_BMSK                                                  0x40000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_USE_PREDIV_WHEN_CAL_SHFT                                                     0x12
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_USE_EXT_SAVERESTORE_BMSK                                                  0x20000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_USE_EXT_SAVERESTORE_SHFT                                                     0x11
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_LOW_JITTER_MODE_EN_BMSK                                                   0x10000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_LOW_JITTER_MODE_EN_SHFT                                                      0x10
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_FRAC_FORMAT_SEL_BMSK                                                       0x8000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_FRAC_FORMAT_SEL_SHFT                                                          0xf
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_BIAS_ON_IN_STANDBY_BMSK                                                    0x4000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_BIAS_ON_IN_STANDBY_SHFT                                                       0xe
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_REF_CLK_AT_OUT_BMSK                                                        0x2000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_REF_CLK_AT_OUT_SHFT                                                           0xd
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_SCALE_FREQ_ON_RESTART_BMSK                                                 0x1800
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_SCALE_FREQ_ON_RESTART_SHFT                                                    0xb
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_LATCH_INTERFACE_BYPASS_BMSK                                                 0x400
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_LATCH_INTERFACE_BYPASS_SHFT                                                   0xa
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_STATUS_REGISTER_BMSK                                                        0x3e0
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_STATUS_REGISTER_SHFT                                                          0x5
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_WRITE_STATE_EN_BMSK                                                          0x10
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_WRITE_STATE_EN_SHFT                                                           0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_CALIB_CTRL_BMSK                                                               0xe
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_CALIB_CTRL_SHFT                                                               0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_USE_ONLY_FINE_LOCK_DET_BMSK                                                   0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_USE_ONLY_FINE_LOCK_DET_SHFT                                                   0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_ADDR                                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001014)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_OFFS                                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001014)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_RMSK                                                                   0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_FINE_LDC_THRESHOLD_BMSK                                                0xfc000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_FINE_LDC_THRESHOLD_SHFT                                                      0x1a
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_COARSE_LDC_THRESHOLD_BMSK                                               0x3c00000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_COARSE_LDC_THRESHOLD_SHFT                                                    0x16
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_COARSE_LOCK_DET_NEG_THRESHOLD_BMSK                                       0x3c0000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_COARSE_LOCK_DET_NEG_THRESHOLD_SHFT                                           0x12
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_COARSE_LOCK_DET_POS_THRESHOLD_BMSK                                        0x3c000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_COARSE_LOCK_DET_POS_THRESHOLD_SHFT                                            0xe
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_FINE_LOCK_DET_THRESHOLD_BMSK                                               0x3800
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_FINE_LOCK_DET_THRESHOLD_SHFT                                                  0xb
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_FINE_LOCK_DET_SAMPLE_SIZE_BMSK                                              0x700
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_FINE_LOCK_DET_SAMPLE_SIZE_SHFT                                                0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_FWD_GAIN_SLEWING_KFN_BMSK                                                    0xf0
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_FWD_GAIN_SLEWING_KFN_SHFT                                                     0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_FWD_GAIN_KFN_BMSK                                                             0xf
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_FWD_GAIN_KFN_SHFT                                                             0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_U_ADDR                                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001018)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_U_OFFS                                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001018)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_U_RMSK                                                                 0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_U_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_U_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_U_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_U_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_U_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_U_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_U_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_U_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_U_BIST_CFG_BMSK                                                        0xfff00000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_U_BIST_CFG_SHFT                                                              0x14
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_U_RESERVE_BITS_19_12_BMSK                                                 0xff000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_U_RESERVE_BITS_19_12_SHFT                                                     0xc
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_U_NUM_STEPS_FAST_LOCK_BMSK                                                  0xc00
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_U_NUM_STEPS_FAST_LOCK_SHFT                                                    0xa
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_U_PREDIV_WHEN_CAL_BMSK                                                      0x380
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_U_PREDIV_WHEN_CAL_SHFT                                                        0x7
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_U_INC_MIN_GLITCH_THRESHOLD_4X_BMSK                                           0x40
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_U_INC_MIN_GLITCH_THRESHOLD_4X_SHFT                                            0x6
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_U_MIN_GLITCH_THRESHOLD_BMSK                                                  0x30
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_U_MIN_GLITCH_THRESHOLD_SHFT                                                   0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_U_USE_BOTH_REF_CLK_EDGE_BMSK                                                  0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_U_USE_BOTH_REF_CLK_EDGE_SHFT                                                  0x3
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_U_BIAS_WARMUP_TIME_BMSK                                                       0x6
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_U_BIAS_WARMUP_TIME_SHFT                                                       0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_U_DIV_LOCK_DET_THRESHOLDS_BMSK                                                0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_U_DIV_LOCK_DET_THRESHOLDS_SHFT                                                0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ADDR                                                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000101c)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_OFFS                                                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000101c)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_RMSK                                                                     0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ADD_REF_CYC_CALIB_STEPS_BMSK                                             0xc0000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ADD_REF_CYC_CALIB_STEPS_SHFT                                                   0x1e
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_GLITCH_DETECTOR_COUNT_LIMIT_BMSK                                         0x30000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_GLITCH_DETECTOR_COUNT_LIMIT_SHFT                                               0x1c
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_GLITCH_PREVENTION_DIS_BMSK                                                0x8000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_GLITCH_PREVENTION_DIS_SHFT                                                     0x1b
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_FINE_FCW_BMSK                                                             0x7e00000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_FINE_FCW_SHFT                                                                  0x15
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_OVERRIDE_FINE_FCW_BMSK                                                     0x100000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_OVERRIDE_FINE_FCW_SHFT                                                         0x14
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_COARSE_FCW_BMSK                                                             0xff000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_COARSE_FCW_SHFT                                                                 0xc
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_OVERRIDE_COARSE_FCW_BMSK                                                      0x800
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_OVERRIDE_COARSE_FCW_SHFT                                                        0xb
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_PROCESS_CALIB_WORD_BMSK                                                       0x700
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_PROCESS_CALIB_WORD_SHFT                                                         0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_OVERRIDE_CALIB_WORD_BMSK                                                       0x80
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_OVERRIDE_CALIB_WORD_SHFT                                                        0x7
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_DISABLE_LFSR_BMSK                                                              0x40
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_DISABLE_LFSR_SHFT                                                               0x6
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ATEST1_SEL_BMSK                                                                0x30
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ATEST1_SEL_SHFT                                                                 0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ATEST0_SEL_BMSK                                                                 0xc
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ATEST0_SEL_SHFT                                                                 0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ATEST1_EN_BMSK                                                                  0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ATEST1_EN_SHFT                                                                  0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ATEST0_EN_BMSK                                                                  0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ATEST0_EN_SHFT                                                                  0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_ADDR                                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001020)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_OFFS                                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001020)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_RMSK                                                                   0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_ENABLE_TRAINING_SEQ_BMSK                                               0x80000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_ENABLE_TRAINING_SEQ_SHFT                                                     0x1f
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_BYPASS_LOGIC_DEP_BMSK                                                  0x40000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_BYPASS_LOGIC_DEP_SHFT                                                        0x1e
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_BYPASS_BIAS_DET_BMSK                                                   0x20000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_BYPASS_BIAS_DET_SHFT                                                         0x1d
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_MSB_CLOCK_SELECT_BMSK                                                  0x10000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_MSB_CLOCK_SELECT_SHFT                                                        0x1c
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_BYPASS_FIRST_ORDER_DSM_BMSK                                             0x8000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_BYPASS_FIRST_ORDER_DSM_SHFT                                                  0x1b
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_DCO_OFFSET_CURRENT_ADJUST_BMSK                                          0x6000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_DCO_OFFSET_CURRENT_ADJUST_SHFT                                               0x19
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_MIRROR_DEVICE_ADJUST_BMSK                                               0x1c00000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_MIRROR_DEVICE_ADJUST_SHFT                                                    0x16
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_BIAS_STARTUP_CIR_DIS_BMSK                                                0x200000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_BIAS_STARTUP_CIR_DIS_SHFT                                                    0x15
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_DISABLE_CLAMP_BMSK                                                       0x100000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_DISABLE_CLAMP_SHFT                                                           0x14
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_BYPASS_MODE_OF_BIAS_BMSK                                                  0x80000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_BYPASS_MODE_OF_BIAS_SHFT                                                     0x13
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_BYPASS_MODE_FOR_BIAS_EN_BMSK                                              0x40000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_BYPASS_MODE_FOR_BIAS_EN_SHFT                                                 0x12
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_BIAS_ADJUST_BMSK                                                          0x30000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_BIAS_ADJUST_SHFT                                                             0x10
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_DIV2_NMO_EN_BMSK                                                           0x8000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_DIV2_NMO_EN_SHFT                                                              0xf
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_DIS_LEAK_CMP_BMSK                                                          0x4000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_DIS_LEAK_CMP_SHFT                                                             0xe
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_SINGLE_DMET_EN_BMSK                                                        0x2000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_SINGLE_DMET_EN_SHFT                                                           0xd
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_DEMET_WINDOW_DIS_BMSK                                                      0x1000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_DEMET_WINDOW_DIS_SHFT                                                         0xc
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_NMO_OSC_SEL_BMSK                                                            0xc00
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_NMO_OSC_SEL_SHFT                                                              0xa
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_NOISE_MAG_BMSK                                                              0x380
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_NOISE_MAG_SHFT                                                                0x7
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_NOISE_GEN_EN_BMSK                                                            0x40
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_NOISE_GEN_EN_SHFT                                                             0x6
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_OSC_BIAS_GND_BMSK                                                            0x20
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_OSC_BIAS_GND_SHFT                                                             0x5
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_PLL_TEST_OUT_SEL_BMSK                                                        0x18
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_PLL_TEST_OUT_SEL_SHFT                                                         0x3
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_STATUS_REG_EN_BMSK                                                            0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_STATUS_REG_EN_SHFT                                                            0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_SKIP_FINE_TUNE_BMSK                                                           0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_SKIP_FINE_TUNE_SHFT                                                           0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_SKIP_FAST_LOCK_BMSK                                                           0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_SKIP_FAST_LOCK_SHFT                                                           0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_ADDR                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001000)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_OFFS                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001000)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_RMSK                                                                         0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_LOCK_DET_BMSK                                                            0x80000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_LOCK_DET_SHFT                                                                  0x1f
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_ACTIVE_FLAG_BMSK                                                         0x40000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_ACTIVE_FLAG_SHFT                                                               0x1e
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_ACK_LATCH_BMSK                                                           0x20000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_ACK_LATCH_SHFT                                                                 0x1d
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_LOCK_DET_FINE_BMSK                                                       0x10000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_LOCK_DET_FINE_SHFT                                                             0x1c
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_RESERVE_BITS27_24_BMSK                                                        0xf000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_RESERVE_BITS27_24_SHFT                                                             0x18
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_BMSK                                                0x800000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_SHFT                                                    0x17
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_UPDATE_BMSK                                                                0x400000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_UPDATE_SHFT                                                                    0x16
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_VOTE_FSM_RESET_BMSK                                                        0x200000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_VOTE_FSM_RESET_SHFT                                                            0x15
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_VOTE_FSM_ENA_BMSK                                                          0x100000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_VOTE_FSM_ENA_SHFT                                                              0x14
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_BIAS_COUNT_BMSK                                                             0xfc000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_BIAS_COUNT_SHFT                                                                 0xe
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_LOCK_COUNT_BMSK                                                              0x3f00
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_LOCK_COUNT_SHFT                                                                 0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_RESERVE_BITS7_3_BMSK                                                               0xf8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_RESERVE_BITS7_3_SHFT                                                                0x3
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_RESET_N_BMSK                                                                    0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_RESET_N_SHFT                                                                    0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_RESERVE_BIT1_BMSK                                                                   0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_RESERVE_BIT1_SHFT                                                                   0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_OUTCTRL_BMSK                                                                    0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_OUTCTRL_SHFT                                                                    0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_ADDR                                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001024)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_OFFS                                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001024)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_RMSK                                                                       0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_STATUS_31_0_BMSK                                                           0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_STATUS_31_0_SHFT                                                                  0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_ADDR                                                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001028)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_OFFS                                                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001028)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_RMSK                                                                     0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_RESERVE_BITS31_27_BMSK                                                   0xf8000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_RESERVE_BITS31_27_SHFT                                                         0x1b
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_FCW_PCAL_BMSK                                                             0x7000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_FCW_PCAL_SHFT                                                                  0x18
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_FCW_ACC_BMSK                                                               0xffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_FCW_ACC_SHFT                                                                    0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_OPMODE_ADDR                                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000102c)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_OPMODE_OFFS                                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000102c)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_OPMODE_RMSK                                                                              0x7
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_OPMODE_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_OPMODE_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_OPMODE_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_OPMODE_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_OPMODE_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_OPMODE_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_OPMODE_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_OPMODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_OPMODE_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_OPMODE_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_OPMODE_PLL_OPMODE_BMSK                                                                   0x7
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_OPMODE_PLL_OPMODE_SHFT                                                                   0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_STATE_ADDR                                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001030)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_STATE_OFFS                                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001030)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_STATE_RMSK                                                                               0x7
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_STATE_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_STATE_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_STATE_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_STATE_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_STATE_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_STATE_PLL_STATE_BMSK                                                                     0x7
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_STATE_PLL_STATE_SHFT                                                                     0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_DROOP_ADDR                                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001034)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_DROOP_OFFS                                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001034)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_DROOP_RMSK                                                                              0xff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_DROOP_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_DROOP_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_DROOP_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_DROOP_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_DROOP_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_DROOP_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_DROOP_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_DROOP_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_DROOP_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_DROOP_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_DROOP_DROOP_CODE_BMSK                                                                   0xfe
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_DROOP_DROOP_CODE_SHFT                                                                    0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_DROOP_DROOP_EN_BMSK                                                                      0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_DROOP_DROOP_EN_SHFT                                                                      0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FRAC_VAL_ADDR                                                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001038)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FRAC_VAL_OFFS                                                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001038)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FRAC_VAL_RMSK                                                                         0xffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FRAC_VAL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_FRAC_VAL_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_FRAC_VAL_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FRAC_VAL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_FRAC_VAL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FRAC_VAL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_FRAC_VAL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FRAC_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_FRAC_VAL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_FRAC_VAL_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FRAC_VAL_PLL_FRAC_VAL_BMSK                                                            0xffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FRAC_VAL_PLL_FRAC_VAL_SHFT                                                               0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SPARE_ADDR                                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000103c)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SPARE_OFFS                                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000103c)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SPARE_RMSK                                                                              0xff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SPARE_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_SPARE_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_SPARE_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SPARE_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_SPARE_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SPARE_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_SPARE_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SPARE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_SPARE_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_SPARE_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SPARE_SPARE_OUTPUTS_BMSK                                                                0xf0
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SPARE_SPARE_OUTPUTS_SHFT                                                                 0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SPARE_SPARE_INPUTS_BMSK                                                                  0xf
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SPARE_SPARE_INPUTS_SHFT                                                                  0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_DELTA_ALPHA_ADDR                                                              (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001040)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_DELTA_ALPHA_OFFS                                                              (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001040)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_DELTA_ALPHA_RMSK                                                                    0xff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_DELTA_ALPHA_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_DELTA_ALPHA_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_DELTA_ALPHA_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_DELTA_ALPHA_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_DELTA_ALPHA_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_DELTA_ALPHA_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_DELTA_ALPHA_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_DELTA_ALPHA_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_DELTA_ALPHA_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_DELTA_ALPHA_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_DELTA_ALPHA_SSC_DELTA_ALPHA_BMSK                                                    0xff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_DELTA_ALPHA_SSC_DELTA_ALPHA_SHFT                                                     0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_NUM_STEPS_ADDR                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001044)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_NUM_STEPS_OFFS                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001044)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_NUM_STEPS_RMSK                                                                       0xf
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_NUM_STEPS_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_NUM_STEPS_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_NUM_STEPS_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_NUM_STEPS_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_NUM_STEPS_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_NUM_STEPS_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_NUM_STEPS_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_NUM_STEPS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_NUM_STEPS_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_NUM_STEPS_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_NUM_STEPS_SSC_NUM_STEPS_BMSK                                                         0xf
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_NUM_STEPS_SSC_NUM_STEPS_SHFT                                                         0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_UPDATE_RATE_ADDR                                                              (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001048)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_UPDATE_RATE_OFFS                                                              (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001048)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_UPDATE_RATE_RMSK                                                                     0xf
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_UPDATE_RATE_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_UPDATE_RATE_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_UPDATE_RATE_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_UPDATE_RATE_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_UPDATE_RATE_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_UPDATE_RATE_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_UPDATE_RATE_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_UPDATE_RATE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_UPDATE_RATE_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_UPDATE_RATE_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_UPDATE_RATE_SSC_UPDATE_RATE_BMSK                                                     0xf
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_SSC_UPDATE_RATE_SSC_UPDATE_RATE_SHFT                                                     0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_ADDR                                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000104c)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_OFFS                                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000104c)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_RMSK                                                                          0xf
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_CLK_ODD_CGC_EN_BMSK                                                           0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_CLK_ODD_CGC_EN_SHFT                                                           0x3
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_CLK_EVEN_CGC_EN_BMSK                                                          0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_CLK_EVEN_CGC_EN_SHFT                                                          0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_CLK_MAIN_SVS_CGC_EN_BMSK                                                      0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_CLK_MAIN_SVS_CGC_EN_SHFT                                                      0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_CLK_MAIN_CGC_EN_BMSK                                                          0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_CLK_MAIN_CGC_EN_SHFT                                                          0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_ADDR                                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00001050)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_OFFS                                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00001050)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_RMSK                                                                             0x3
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_CLK_MAIN_DIV_BMSK                                                                0x3
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_CLK_MAIN_DIV_SHFT                                                                0x0

#define HWIO_LPASS_LPAAUDIO_PLL_REF_CLK_SRC_SEL_ADDR                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00002000)
#define HWIO_LPASS_LPAAUDIO_PLL_REF_CLK_SRC_SEL_OFFS                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00002000)
#define HWIO_LPASS_LPAAUDIO_PLL_REF_CLK_SRC_SEL_RMSK                                                                         0x1
#define HWIO_LPASS_LPAAUDIO_PLL_REF_CLK_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_REF_CLK_SRC_SEL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_REF_CLK_SRC_SEL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_REF_CLK_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_REF_CLK_SRC_SEL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_REF_CLK_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_REF_CLK_SRC_SEL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_REF_CLK_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_REF_CLK_SRC_SEL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_REF_CLK_SRC_SEL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_REF_CLK_SRC_SEL_PLL_CLK_SRC_SEL_BMSK                                                         0x1
#define HWIO_LPASS_LPAAUDIO_PLL_REF_CLK_SRC_SEL_PLL_CLK_SRC_SEL_SHFT                                                         0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_ADDR                                                              (LPASS_LPASS_CC_REG_REG_BASE      + 0x00003000)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_OFFS                                                              (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00003000)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_RMSK                                                                     0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_PLL_CLK_SRC_SEL_BMSK                                                     0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_PLL_CLK_SRC_SEL_SHFT                                                     0x0

#define HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_ADDR                                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00004000)
#define HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_OFFS                                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00004000)
#define HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_RMSK                                                                          0x1
#define HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_ADDR, HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_IN)
#define HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_PLL_CLK_SRC_SEL_BMSK                                                          0x1
#define HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_PLL_CLK_SRC_SEL_SHFT                                                          0x0

#define HWIO_LPASS_LPA_PLL_VOTE_APPS_ADDR                                                                             (LPASS_LPASS_CC_REG_REG_BASE      + 0x00005000)
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_OFFS                                                                             (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00005000)
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_RMSK                                                                                   0xff
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_IN          \
        in_dword_masked(HWIO_LPASS_LPA_PLL_VOTE_APPS_ADDR, HWIO_LPASS_LPA_PLL_VOTE_APPS_RMSK)
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPA_PLL_VOTE_APPS_ADDR, m)
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_OUT(v)      \
        out_dword(HWIO_LPASS_LPA_PLL_VOTE_APPS_ADDR,v)
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPA_PLL_VOTE_APPS_ADDR,m,v,HWIO_LPASS_LPA_PLL_VOTE_APPS_IN)
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_RESERVE_BITS7_3_BMSK                                                                   0xf8
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_RESERVE_BITS7_3_SHFT                                                                    0x3
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_QDSP6SS_PLL_BMSK                                                                        0x4
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_QDSP6SS_PLL_SHFT                                                                        0x2
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_LPAAUDIO_DIG_PLL_BMSK                                                                   0x2
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_LPAAUDIO_DIG_PLL_SHFT                                                                   0x1
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_LPAAUDIO_PLL_BMSK                                                                       0x1
#define HWIO_LPASS_LPA_PLL_VOTE_APPS_LPAAUDIO_PLL_SHFT                                                                       0x0

#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_ADDR                                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x00006000)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_OFFS                                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00006000)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_RMSK                                                                                0xff
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_IN          \
        in_dword_masked(HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_ADDR, HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_RMSK)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_ADDR, m)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_OUT(v)      \
        out_dword(HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_ADDR,v)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_ADDR,m,v,HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_IN)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_RESERVE_BITS7_3_BMSK                                                                0xf8
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_RESERVE_BITS7_3_SHFT                                                                 0x3
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_QDSP6SS_PLL_BMSK                                                                     0x4
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_QDSP6SS_PLL_SHFT                                                                     0x2
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_LPAAUDIO_DIG_PLL_BMSK                                                                0x2
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_LPAAUDIO_DIG_PLL_SHFT                                                                0x1
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_LPAAUDIO_PLL_BMSK                                                                    0x1
#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_LPAAUDIO_PLL_SHFT                                                                    0x0

#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_ADDR                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00007000)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_OFFS                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00007000)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_RMSK                                                                               0xff
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_IN          \
        in_dword_masked(HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_ADDR, HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_RMSK)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_ADDR, m)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_OUT(v)      \
        out_dword(HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_ADDR,v)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_ADDR,m,v,HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_IN)
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_RESERVE_BITS7_3_BMSK                                                               0xf8
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_RESERVE_BITS7_3_SHFT                                                                0x3
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_QDSP6SS_PLL_BMSK                                                                    0x4
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_QDSP6SS_PLL_SHFT                                                                    0x2
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_LPAAUDIO_DIG_PLL_BMSK                                                               0x2
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_LPAAUDIO_DIG_PLL_SHFT                                                               0x1
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_LPAAUDIO_PLL_BMSK                                                                   0x1
#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_LPAAUDIO_PLL_SHFT                                                                   0x0

#define HWIO_LPASS_AUDIO_CORE_BCR_ADDR                                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00008000)
#define HWIO_LPASS_AUDIO_CORE_BCR_OFFS                                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00008000)
#define HWIO_LPASS_AUDIO_CORE_BCR_RMSK                                                                                0xf8000007
#define HWIO_LPASS_AUDIO_CORE_BCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BCR_ADDR, HWIO_LPASS_AUDIO_CORE_BCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_BCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_BCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_BCR_IN)
#define HWIO_LPASS_AUDIO_CORE_BCR_DFD_STATUS_BMSK                                                                     0x80000000
#define HWIO_LPASS_AUDIO_CORE_BCR_DFD_STATUS_SHFT                                                                           0x1f
#define HWIO_LPASS_AUDIO_CORE_BCR_BCR_RESET_STATE_BMSK                                                                0x60000000
#define HWIO_LPASS_AUDIO_CORE_BCR_BCR_RESET_STATE_SHFT                                                                      0x1d
#define HWIO_LPASS_AUDIO_CORE_BCR_LPASS_BUS_ABORT_ACK_STATUS_BMSK                                                     0x10000000
#define HWIO_LPASS_AUDIO_CORE_BCR_LPASS_BUS_ABORT_ACK_STATUS_SHFT                                                           0x1c
#define HWIO_LPASS_AUDIO_CORE_BCR_PSMMU_ABORT_ACK_STATUS_BMSK                                                          0x8000000
#define HWIO_LPASS_AUDIO_CORE_BCR_PSMMU_ABORT_ACK_STATUS_SHFT                                                               0x1b
#define HWIO_LPASS_AUDIO_CORE_BCR_FORCE_RESET_BMSK                                                                           0x4
#define HWIO_LPASS_AUDIO_CORE_BCR_FORCE_RESET_SHFT                                                                           0x2
#define HWIO_LPASS_AUDIO_CORE_BCR_DFD_EN_BMSK                                                                                0x2
#define HWIO_LPASS_AUDIO_CORE_BCR_DFD_EN_SHFT                                                                                0x1
#define HWIO_LPASS_AUDIO_CORE_BCR_BLK_ARES_BMSK                                                                              0x1
#define HWIO_LPASS_AUDIO_CORE_BCR_BLK_ARES_SHFT                                                                              0x0

#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_ADDR                                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00008004)
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_OFFS                                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00008004)
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_RMSK                                                                       0x80000003
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_CLK_OFF_BMSK                                                               0x80000000
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_CLK_OFF_SHFT                                                                     0x1f
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_HW_CTL_BMSK                                                                       0x2
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_HW_CTL_SHFT                                                                       0x1
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_CLK_ENABLE_BMSK                                                                   0x1
#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_CLK_ENABLE_SHFT                                                                   0x0

#define HWIO_LPASS_AUDIO_WRAPPER_BCR_ADDR                                                                             (LPASS_LPASS_CC_REG_REG_BASE      + 0x00009000)
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_OFFS                                                                             (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00009000)
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_RMSK                                                                             0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_BCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_BCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_BCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_BCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_BCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_BCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_DFD_STATUS_BMSK                                                                  0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_DFD_STATUS_SHFT                                                                        0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_DFD_EN_BMSK                                                                             0x2
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_DFD_EN_SHFT                                                                             0x1
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_BLK_ARES_BMSK                                                                           0x1
#define HWIO_LPASS_AUDIO_WRAPPER_BCR_BLK_ARES_SHFT                                                                           0x0

#define HWIO_LPASS_Q6SS_BCR_ADDR                                                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000a000)
#define HWIO_LPASS_Q6SS_BCR_OFFS                                                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000a000)
#define HWIO_LPASS_Q6SS_BCR_RMSK                                                                                      0x80000003
#define HWIO_LPASS_Q6SS_BCR_IN          \
        in_dword_masked(HWIO_LPASS_Q6SS_BCR_ADDR, HWIO_LPASS_Q6SS_BCR_RMSK)
#define HWIO_LPASS_Q6SS_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6SS_BCR_ADDR, m)
#define HWIO_LPASS_Q6SS_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6SS_BCR_ADDR,v)
#define HWIO_LPASS_Q6SS_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_BCR_ADDR,m,v,HWIO_LPASS_Q6SS_BCR_IN)
#define HWIO_LPASS_Q6SS_BCR_DFD_STATUS_BMSK                                                                           0x80000000
#define HWIO_LPASS_Q6SS_BCR_DFD_STATUS_SHFT                                                                                 0x1f
#define HWIO_LPASS_Q6SS_BCR_DFD_EN_BMSK                                                                                      0x2
#define HWIO_LPASS_Q6SS_BCR_DFD_EN_SHFT                                                                                      0x1
#define HWIO_LPASS_Q6SS_BCR_BLK_ARES_BMSK                                                                                    0x1
#define HWIO_LPASS_Q6SS_BCR_BLK_ARES_SHFT                                                                                    0x0

#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_ADDR                                                                             (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000a004)
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_OFFS                                                                             (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000a004)
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_RMSK                                                                             0x80000003
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_Q6SS_BCR_SLP_CBCR_ADDR, HWIO_LPASS_Q6SS_BCR_SLP_CBCR_RMSK)
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6SS_BCR_SLP_CBCR_ADDR, m)
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6SS_BCR_SLP_CBCR_ADDR,v)
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_BCR_SLP_CBCR_ADDR,m,v,HWIO_LPASS_Q6SS_BCR_SLP_CBCR_IN)
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_CLK_OFF_BMSK                                                                     0x80000000
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_CLK_OFF_SHFT                                                                           0x1f
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_HW_CTL_BMSK                                                                             0x2
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_HW_CTL_SHFT                                                                             0x1
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_CLK_ENABLE_BMSK                                                                         0x1
#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_CLK_ENABLE_SHFT                                                                         0x0

#define HWIO_LPASS_AUDIO_CORE_GDSCR_ADDR                                                                              (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000b000)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_OFFS                                                                              (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000b000)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_RMSK                                                                              0xf8ffffff
#define HWIO_LPASS_AUDIO_CORE_GDSCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDSCR_ADDR, HWIO_LPASS_AUDIO_CORE_GDSCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDSCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_GDSCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_GDSCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_GDSCR_IN)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_PWR_ON_BMSK                                                                       0x80000000
#define HWIO_LPASS_AUDIO_CORE_GDSCR_PWR_ON_SHFT                                                                             0x1f
#define HWIO_LPASS_AUDIO_CORE_GDSCR_GDSC_STATE_BMSK                                                                   0x78000000
#define HWIO_LPASS_AUDIO_CORE_GDSCR_GDSC_STATE_SHFT                                                                         0x1b
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_REST_WAIT_BMSK                                                                   0xf00000
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_REST_WAIT_SHFT                                                                       0x14
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_FEW_WAIT_BMSK                                                                     0xf0000
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_FEW_WAIT_SHFT                                                                        0x10
#define HWIO_LPASS_AUDIO_CORE_GDSCR_CLK_DIS_WAIT_BMSK                                                                     0xf000
#define HWIO_LPASS_AUDIO_CORE_GDSCR_CLK_DIS_WAIT_SHFT                                                                        0xc
#define HWIO_LPASS_AUDIO_CORE_GDSCR_RETAIN_FF_ENABLE_BMSK                                                                  0x800
#define HWIO_LPASS_AUDIO_CORE_GDSCR_RETAIN_FF_ENABLE_SHFT                                                                    0xb
#define HWIO_LPASS_AUDIO_CORE_GDSCR_RESTORE_BMSK                                                                           0x400
#define HWIO_LPASS_AUDIO_CORE_GDSCR_RESTORE_SHFT                                                                             0xa
#define HWIO_LPASS_AUDIO_CORE_GDSCR_SAVE_BMSK                                                                              0x200
#define HWIO_LPASS_AUDIO_CORE_GDSCR_SAVE_SHFT                                                                                0x9
#define HWIO_LPASS_AUDIO_CORE_GDSCR_RETAIN_BMSK                                                                            0x100
#define HWIO_LPASS_AUDIO_CORE_GDSCR_RETAIN_SHFT                                                                              0x8
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_REST_BMSK                                                                            0x80
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_REST_SHFT                                                                             0x7
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_FEW_BMSK                                                                             0x40
#define HWIO_LPASS_AUDIO_CORE_GDSCR_EN_FEW_SHFT                                                                              0x6
#define HWIO_LPASS_AUDIO_CORE_GDSCR_CLAMP_IO_BMSK                                                                           0x20
#define HWIO_LPASS_AUDIO_CORE_GDSCR_CLAMP_IO_SHFT                                                                            0x5
#define HWIO_LPASS_AUDIO_CORE_GDSCR_CLK_DISABLE_BMSK                                                                        0x10
#define HWIO_LPASS_AUDIO_CORE_GDSCR_CLK_DISABLE_SHFT                                                                         0x4
#define HWIO_LPASS_AUDIO_CORE_GDSCR_PD_ARES_BMSK                                                                             0x8
#define HWIO_LPASS_AUDIO_CORE_GDSCR_PD_ARES_SHFT                                                                             0x3
#define HWIO_LPASS_AUDIO_CORE_GDSCR_SW_OVERRIDE_BMSK                                                                         0x4
#define HWIO_LPASS_AUDIO_CORE_GDSCR_SW_OVERRIDE_SHFT                                                                         0x2
#define HWIO_LPASS_AUDIO_CORE_GDSCR_HW_CONTROL_BMSK                                                                          0x2
#define HWIO_LPASS_AUDIO_CORE_GDSCR_HW_CONTROL_SHFT                                                                          0x1
#define HWIO_LPASS_AUDIO_CORE_GDSCR_SW_COLLAPSE_BMSK                                                                         0x1
#define HWIO_LPASS_AUDIO_CORE_GDSCR_SW_COLLAPSE_SHFT                                                                         0x0

#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_ADDR                                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000b004)
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_OFFS                                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000b004)
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_RMSK                                                                       0x80000003
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_CLK_OFF_BMSK                                                               0x80000000
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_CLK_OFF_SHFT                                                                     0x1f
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_HW_CTL_BMSK                                                                       0x2
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_HW_CTL_SHFT                                                                       0x1
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_CLK_ENABLE_BMSK                                                                   0x1
#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_CLK_ENABLE_SHFT                                                                   0x0

#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_ADDR                                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000b008)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_OFFS                                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000b008)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_RMSK                                                                        0xffffffff
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_ADDR, HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_RMSK)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_IN)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_POWER_ON_STATUS_BMSK                                                        0x80000000
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_POWER_ON_STATUS_SHFT                                                              0x1f
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_HALT1_PWR_DOWN_ACK_STATUS_BMSK                                              0x78000000
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_HALT1_PWR_DOWN_ACK_STATUS_SHFT                                                    0x1b
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_HALT1_PWR_UP_ACK_STATUS_BMSK                                                 0x7800000
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_HALT1_PWR_UP_ACK_STATUS_SHFT                                                      0x17
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_HALT2_PWR_DOWN_ACK_STATUS_BMSK                                                0x780000
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_HALT2_PWR_DOWN_ACK_STATUS_SHFT                                                    0x13
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_HALT2_PWR_UP_ACK_STATUS_BMSK                                                   0x78000
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_HALT2_PWR_UP_ACK_STATUS_SHFT                                                       0xf
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_COLLAPSE_OUT_BMSK                                                               0x4000
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_COLLAPSE_OUT_SHFT                                                                  0xe
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_RESERVE_BITS13_BMSK                                                             0x2000
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_RESERVE_BITS13_SHFT                                                                0xd
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_HALT_ACK_TIME_OUT_BMSK                                                          0x1fe0
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_HALT_ACK_TIME_OUT_SHFT                                                             0x5
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_GDS_HW_STATE_BMSK                                                                 0x1e
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_GDS_HW_STATE_SHFT                                                                  0x1
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SW_OVERRIDE_BMSK                                                                   0x1
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SW_OVERRIDE_SHFT                                                                   0x0

#define HWIO_LPASS_AUDIO_CORE_GDS_HW_DVM_CTRL_ADDR                                                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000b00c)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_DVM_CTRL_OFFS                                                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000b00c)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_DVM_CTRL_RMSK                                                                    0xc0000001
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_DVM_CTRL_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDS_HW_DVM_CTRL_ADDR, HWIO_LPASS_AUDIO_CORE_GDS_HW_DVM_CTRL_RMSK)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_DVM_CTRL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDS_HW_DVM_CTRL_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_DVM_CTRL_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_GDS_HW_DVM_CTRL_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_DVM_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_GDS_HW_DVM_CTRL_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_GDS_HW_DVM_CTRL_IN)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_DVM_CTRL_DVM_HALT1_PWR_DOWN_ACK_STATUS_BMSK                                      0x80000000
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_DVM_CTRL_DVM_HALT1_PWR_DOWN_ACK_STATUS_SHFT                                            0x1f
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_DVM_CTRL_DVM_HALT1_PWR_UP_ACK_STATUS_BMSK                                        0x40000000
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_DVM_CTRL_DVM_HALT1_PWR_UP_ACK_STATUS_SHFT                                              0x1e
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_DVM_CTRL_DVM_HALT1_REQ_SW_BMSK                                                          0x1
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_DVM_CTRL_DVM_HALT1_REQ_SW_SHFT                                                          0x0

#define HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_ADDR                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000c000)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_OFFS                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000c000)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_RMSK                                                                                0x3
#define HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_ADDR, HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_RMSK)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_IN)
#define HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_RETENTION_ENABLE_VOTE_BMSK                                                          0x2
#define HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_RETENTION_ENABLE_VOTE_SHFT                                                          0x1
#define HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_SW_OVERRIDE_VOTE_BMSK                                                               0x1
#define HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_SW_OVERRIDE_VOTE_SHFT                                                               0x0

#define HWIO_LPASS_Q6_SMMU_GDSCR_ADDR                                                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000d000)
#define HWIO_LPASS_Q6_SMMU_GDSCR_OFFS                                                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000d000)
#define HWIO_LPASS_Q6_SMMU_GDSCR_RMSK                                                                                 0xf8ffffff
#define HWIO_LPASS_Q6_SMMU_GDSCR_IN          \
        in_dword_masked(HWIO_LPASS_Q6_SMMU_GDSCR_ADDR, HWIO_LPASS_Q6_SMMU_GDSCR_RMSK)
#define HWIO_LPASS_Q6_SMMU_GDSCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6_SMMU_GDSCR_ADDR, m)
#define HWIO_LPASS_Q6_SMMU_GDSCR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6_SMMU_GDSCR_ADDR,v)
#define HWIO_LPASS_Q6_SMMU_GDSCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6_SMMU_GDSCR_ADDR,m,v,HWIO_LPASS_Q6_SMMU_GDSCR_IN)
#define HWIO_LPASS_Q6_SMMU_GDSCR_PWR_ON_BMSK                                                                          0x80000000
#define HWIO_LPASS_Q6_SMMU_GDSCR_PWR_ON_SHFT                                                                                0x1f
#define HWIO_LPASS_Q6_SMMU_GDSCR_GDSC_STATE_BMSK                                                                      0x78000000
#define HWIO_LPASS_Q6_SMMU_GDSCR_GDSC_STATE_SHFT                                                                            0x1b
#define HWIO_LPASS_Q6_SMMU_GDSCR_EN_REST_WAIT_BMSK                                                                      0xf00000
#define HWIO_LPASS_Q6_SMMU_GDSCR_EN_REST_WAIT_SHFT                                                                          0x14
#define HWIO_LPASS_Q6_SMMU_GDSCR_EN_FEW_WAIT_BMSK                                                                        0xf0000
#define HWIO_LPASS_Q6_SMMU_GDSCR_EN_FEW_WAIT_SHFT                                                                           0x10
#define HWIO_LPASS_Q6_SMMU_GDSCR_CLK_DIS_WAIT_BMSK                                                                        0xf000
#define HWIO_LPASS_Q6_SMMU_GDSCR_CLK_DIS_WAIT_SHFT                                                                           0xc
#define HWIO_LPASS_Q6_SMMU_GDSCR_RETAIN_FF_ENABLE_BMSK                                                                     0x800
#define HWIO_LPASS_Q6_SMMU_GDSCR_RETAIN_FF_ENABLE_SHFT                                                                       0xb
#define HWIO_LPASS_Q6_SMMU_GDSCR_RESTORE_BMSK                                                                              0x400
#define HWIO_LPASS_Q6_SMMU_GDSCR_RESTORE_SHFT                                                                                0xa
#define HWIO_LPASS_Q6_SMMU_GDSCR_SAVE_BMSK                                                                                 0x200
#define HWIO_LPASS_Q6_SMMU_GDSCR_SAVE_SHFT                                                                                   0x9
#define HWIO_LPASS_Q6_SMMU_GDSCR_RETAIN_BMSK                                                                               0x100
#define HWIO_LPASS_Q6_SMMU_GDSCR_RETAIN_SHFT                                                                                 0x8
#define HWIO_LPASS_Q6_SMMU_GDSCR_EN_REST_BMSK                                                                               0x80
#define HWIO_LPASS_Q6_SMMU_GDSCR_EN_REST_SHFT                                                                                0x7
#define HWIO_LPASS_Q6_SMMU_GDSCR_EN_FEW_BMSK                                                                                0x40
#define HWIO_LPASS_Q6_SMMU_GDSCR_EN_FEW_SHFT                                                                                 0x6
#define HWIO_LPASS_Q6_SMMU_GDSCR_CLAMP_IO_BMSK                                                                              0x20
#define HWIO_LPASS_Q6_SMMU_GDSCR_CLAMP_IO_SHFT                                                                               0x5
#define HWIO_LPASS_Q6_SMMU_GDSCR_CLK_DISABLE_BMSK                                                                           0x10
#define HWIO_LPASS_Q6_SMMU_GDSCR_CLK_DISABLE_SHFT                                                                            0x4
#define HWIO_LPASS_Q6_SMMU_GDSCR_PD_ARES_BMSK                                                                                0x8
#define HWIO_LPASS_Q6_SMMU_GDSCR_PD_ARES_SHFT                                                                                0x3
#define HWIO_LPASS_Q6_SMMU_GDSCR_SW_OVERRIDE_BMSK                                                                            0x4
#define HWIO_LPASS_Q6_SMMU_GDSCR_SW_OVERRIDE_SHFT                                                                            0x2
#define HWIO_LPASS_Q6_SMMU_GDSCR_HW_CONTROL_BMSK                                                                             0x2
#define HWIO_LPASS_Q6_SMMU_GDSCR_HW_CONTROL_SHFT                                                                             0x1
#define HWIO_LPASS_Q6_SMMU_GDSCR_SW_COLLAPSE_BMSK                                                                            0x1
#define HWIO_LPASS_Q6_SMMU_GDSCR_SW_COLLAPSE_SHFT                                                                            0x0

#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_ADDR                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000d004)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_OFFS                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000d004)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_RMSK                                                            0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_CLK_OFF_BMSK                                                    0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_CLK_OFF_SHFT                                                          0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_HW_CTL_BMSK                                                            0x2
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_HW_CTL_SHFT                                                            0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_CLK_ENABLE_BMSK                                                        0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDSC_XO_CBCR_CLK_ENABLE_SHFT                                                        0x0

#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_ADDR                                                             (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000d008)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_OFFS                                                             (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000d008)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_RMSK                                                             0xffffffff
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_ADDR, HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_POWER_ON_STATUS_BMSK                                             0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_POWER_ON_STATUS_SHFT                                                   0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_HALT1_PWR_DOWN_ACK_STATUS_BMSK                                   0x78000000
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_HALT1_PWR_DOWN_ACK_STATUS_SHFT                                         0x1b
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_HALT1_PWR_UP_ACK_STATUS_BMSK                                      0x7800000
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_HALT1_PWR_UP_ACK_STATUS_SHFT                                           0x17
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_HALT2_PWR_DOWN_ACK_STATUS_BMSK                                     0x780000
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_HALT2_PWR_DOWN_ACK_STATUS_SHFT                                         0x13
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_HALT2_PWR_UP_ACK_STATUS_BMSK                                        0x78000
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_HALT2_PWR_UP_ACK_STATUS_SHFT                                            0xf
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_COLLAPSE_OUT_BMSK                                                    0x4000
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_COLLAPSE_OUT_SHFT                                                       0xe
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_RESERVE_BITS13_BMSK                                                  0x2000
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_RESERVE_BITS13_SHFT                                                     0xd
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_HALT_ACK_TIME_OUT_BMSK                                               0x1fe0
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_HALT_ACK_TIME_OUT_SHFT                                                  0x5
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_GDS_HW_STATE_BMSK                                                      0x1e
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_GDS_HW_STATE_SHFT                                                       0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SW_OVERRIDE_BMSK                                                        0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SW_OVERRIDE_SHFT                                                        0x0

#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_ADDR                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000d00c)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_OFFS                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000d00c)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_RMSK                                                         0xc0000001
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_ADDR, HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_DVM_HALT1_PWR_DOWN_ACK_STATUS_BMSK                           0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_DVM_HALT1_PWR_DOWN_ACK_STATUS_SHFT                                 0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_DVM_HALT1_PWR_UP_ACK_STATUS_BMSK                             0x40000000
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_DVM_HALT1_PWR_UP_ACK_STATUS_SHFT                                   0x1e
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_DVM_HALT1_REQ_SW_BMSK                                               0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_DVM_CTRL_DVM_HALT1_REQ_SW_SHFT                                               0x0

#define HWIO_LPASS_Q6_SMMU_GDSCR_VOTE_ADDR                                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000e000)
#define HWIO_LPASS_Q6_SMMU_GDSCR_VOTE_OFFS                                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000e000)
#define HWIO_LPASS_Q6_SMMU_GDSCR_VOTE_RMSK                                                                                   0x3
#define HWIO_LPASS_Q6_SMMU_GDSCR_VOTE_IN          \
        in_dword_masked(HWIO_LPASS_Q6_SMMU_GDSCR_VOTE_ADDR, HWIO_LPASS_Q6_SMMU_GDSCR_VOTE_RMSK)
#define HWIO_LPASS_Q6_SMMU_GDSCR_VOTE_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6_SMMU_GDSCR_VOTE_ADDR, m)
#define HWIO_LPASS_Q6_SMMU_GDSCR_VOTE_OUT(v)      \
        out_dword(HWIO_LPASS_Q6_SMMU_GDSCR_VOTE_ADDR,v)
#define HWIO_LPASS_Q6_SMMU_GDSCR_VOTE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6_SMMU_GDSCR_VOTE_ADDR,m,v,HWIO_LPASS_Q6_SMMU_GDSCR_VOTE_IN)
#define HWIO_LPASS_Q6_SMMU_GDSCR_VOTE_RETENTION_ENABLE_VOTE_BMSK                                                             0x2
#define HWIO_LPASS_Q6_SMMU_GDSCR_VOTE_RETENTION_ENABLE_VOTE_SHFT                                                             0x1
#define HWIO_LPASS_Q6_SMMU_GDSCR_VOTE_SW_OVERRIDE_VOTE_BMSK                                                                  0x1
#define HWIO_LPASS_Q6_SMMU_GDSCR_VOTE_SW_OVERRIDE_VOTE_SHFT                                                                  0x0

#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_ADDR                                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000f000)
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_OFFS                                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000f000)
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_RMSK                                                                           0x800000f3
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_ADDR, HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_IN)
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_ROOT_OFF_BMSK                                                                  0x80000000
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_ROOT_OFF_SHFT                                                                        0x1f
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_DIRTY_D_BMSK                                                                         0x80
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_DIRTY_D_SHFT                                                                          0x7
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_DIRTY_N_BMSK                                                                         0x40
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_DIRTY_N_SHFT                                                                          0x6
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_DIRTY_M_BMSK                                                                         0x20
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_DIRTY_M_SHFT                                                                          0x5
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                  0x10
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                   0x4
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_ROOT_EN_BMSK                                                                          0x2
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_ROOT_EN_SHFT                                                                          0x1
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_UPDATE_BMSK                                                                           0x1
#define HWIO_LPASS_LPAIF_SPKR_CMD_RCGR_UPDATE_SHFT                                                                           0x0

#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_ADDR                                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000f004)
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_OFFS                                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000f004)
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_RMSK                                                                               0x771f
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_ADDR, HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_IN)
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                   0x4000
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                      0xe
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_MODE_BMSK                                                                          0x3000
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_MODE_SHFT                                                                             0xc
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_SRC_SEL_BMSK                                                                        0x700
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_SRC_SEL_SHFT                                                                          0x8
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_SRC_DIV_BMSK                                                                         0x1f
#define HWIO_LPASS_LPAIF_SPKR_CFG_RCGR_SRC_DIV_SHFT                                                                          0x0

#define HWIO_LPASS_LPAIF_SPKR_M_ADDR                                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000f008)
#define HWIO_LPASS_LPAIF_SPKR_M_OFFS                                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000f008)
#define HWIO_LPASS_LPAIF_SPKR_M_RMSK                                                                                        0xff
#define HWIO_LPASS_LPAIF_SPKR_M_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_M_ADDR, HWIO_LPASS_LPAIF_SPKR_M_RMSK)
#define HWIO_LPASS_LPAIF_SPKR_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_M_ADDR, m)
#define HWIO_LPASS_LPAIF_SPKR_M_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SPKR_M_ADDR,v)
#define HWIO_LPASS_LPAIF_SPKR_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SPKR_M_ADDR,m,v,HWIO_LPASS_LPAIF_SPKR_M_IN)
#define HWIO_LPASS_LPAIF_SPKR_M_M_BMSK                                                                                      0xff
#define HWIO_LPASS_LPAIF_SPKR_M_M_SHFT                                                                                       0x0

#define HWIO_LPASS_LPAIF_SPKR_N_ADDR                                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000f00c)
#define HWIO_LPASS_LPAIF_SPKR_N_OFFS                                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000f00c)
#define HWIO_LPASS_LPAIF_SPKR_N_RMSK                                                                                        0xff
#define HWIO_LPASS_LPAIF_SPKR_N_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_N_ADDR, HWIO_LPASS_LPAIF_SPKR_N_RMSK)
#define HWIO_LPASS_LPAIF_SPKR_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_N_ADDR, m)
#define HWIO_LPASS_LPAIF_SPKR_N_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SPKR_N_ADDR,v)
#define HWIO_LPASS_LPAIF_SPKR_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SPKR_N_ADDR,m,v,HWIO_LPASS_LPAIF_SPKR_N_IN)
#define HWIO_LPASS_LPAIF_SPKR_N_NOT_N_MINUS_M_BMSK                                                                          0xff
#define HWIO_LPASS_LPAIF_SPKR_N_NOT_N_MINUS_M_SHFT                                                                           0x0

#define HWIO_LPASS_LPAIF_SPKR_D_ADDR                                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000f010)
#define HWIO_LPASS_LPAIF_SPKR_D_OFFS                                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000f010)
#define HWIO_LPASS_LPAIF_SPKR_D_RMSK                                                                                        0xff
#define HWIO_LPASS_LPAIF_SPKR_D_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_D_ADDR, HWIO_LPASS_LPAIF_SPKR_D_RMSK)
#define HWIO_LPASS_LPAIF_SPKR_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SPKR_D_ADDR, m)
#define HWIO_LPASS_LPAIF_SPKR_D_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SPKR_D_ADDR,v)
#define HWIO_LPASS_LPAIF_SPKR_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SPKR_D_ADDR,m,v,HWIO_LPASS_LPAIF_SPKR_D_IN)
#define HWIO_LPASS_LPAIF_SPKR_D_NOT_2D_BMSK                                                                                 0xff
#define HWIO_LPASS_LPAIF_SPKR_D_NOT_2D_SHFT                                                                                  0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_ADDR                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000f014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_OFFS                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000f014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_RMSK                                                          0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_CLK_OFF_BMSK                                                  0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_CLK_OFF_SHFT                                                        0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_HW_CTL_BMSK                                                          0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_HW_CTL_SHFT                                                          0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_CLK_ENABLE_BMSK                                                      0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_OSR_CBCR_CLK_ENABLE_SHFT                                                      0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_ADDR                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000f018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_OFFS                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000f018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_RMSK                                                         0x81ff0003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_CLK_OFF_BMSK                                                 0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_CLK_OFF_SHFT                                                       0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_CLK_DIV_BMSK                                                  0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_CLK_DIV_SHFT                                                       0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_HW_CTL_BMSK                                                         0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_HW_CTL_SHFT                                                         0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_CLK_ENABLE_BMSK                                                     0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_IBIT_CBCR_CLK_ENABLE_SHFT                                                     0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_ADDR                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000f01c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_OFFS                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000f01c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_RMSK                                                         0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_CLK_OFF_BMSK                                                 0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_CLK_OFF_SHFT                                                       0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_HW_CTL_BMSK                                                         0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_HW_CTL_SHFT                                                         0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_CLK_ENABLE_BMSK                                                     0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EBIT_CBCR_CLK_ENABLE_SHFT                                                     0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_ADDR                                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x0000f020)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_OFFS                                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0000f020)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_RMSK                                                    0x80007f13
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_BMSK                                   0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_SHFT                                         0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_CLK_COUNTER_VALUE_BMSK                                      0x7f00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_CLK_COUNTER_VALUE_SHFT                                         0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_IRQ_CLEAR_BMSK                                                0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_IRQ_CLEAR_SHFT                                                 0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_CLK_COUNTER_EN_BMSK                                            0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_CLK_COUNTER_EN_SHFT                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_IRQ_EN_BMSK                                                    0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_CODEC_SPKR_EXT_CLK_DETECT_IRQ_EN_SHFT                                                    0x0

#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ADDR                                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00010000)
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_OFFS                                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00010000)
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_RMSK                                                                            0x800000f3
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ADDR, HWIO_LPASS_LPAIF_PRI_CMD_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_PRI_CMD_RCGR_IN)
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ROOT_OFF_BMSK                                                                   0x80000000
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ROOT_OFF_SHFT                                                                         0x1f
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_D_BMSK                                                                          0x80
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_D_SHFT                                                                           0x7
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_N_BMSK                                                                          0x40
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_N_SHFT                                                                           0x6
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_M_BMSK                                                                          0x20
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_M_SHFT                                                                           0x5
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                   0x10
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                    0x4
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ROOT_EN_BMSK                                                                           0x2
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ROOT_EN_SHFT                                                                           0x1
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_UPDATE_BMSK                                                                            0x1
#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_UPDATE_SHFT                                                                            0x0

#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_ADDR                                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00010004)
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_OFFS                                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00010004)
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_RMSK                                                                                0x771f
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_CFG_RCGR_ADDR, HWIO_LPASS_LPAIF_PRI_CFG_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PRI_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PRI_CFG_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_PRI_CFG_RCGR_IN)
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                    0x4000
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                       0xe
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_MODE_BMSK                                                                           0x3000
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_MODE_SHFT                                                                              0xc
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_SRC_SEL_BMSK                                                                         0x700
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_SRC_SEL_SHFT                                                                           0x8
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_SRC_DIV_BMSK                                                                          0x1f
#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_SRC_DIV_SHFT                                                                           0x0

#define HWIO_LPASS_LPAIF_PRI_M_ADDR                                                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00010008)
#define HWIO_LPASS_LPAIF_PRI_M_OFFS                                                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00010008)
#define HWIO_LPASS_LPAIF_PRI_M_RMSK                                                                                       0xffff
#define HWIO_LPASS_LPAIF_PRI_M_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_M_ADDR, HWIO_LPASS_LPAIF_PRI_M_RMSK)
#define HWIO_LPASS_LPAIF_PRI_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_M_ADDR, m)
#define HWIO_LPASS_LPAIF_PRI_M_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PRI_M_ADDR,v)
#define HWIO_LPASS_LPAIF_PRI_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PRI_M_ADDR,m,v,HWIO_LPASS_LPAIF_PRI_M_IN)
#define HWIO_LPASS_LPAIF_PRI_M_M_BMSK                                                                                     0xffff
#define HWIO_LPASS_LPAIF_PRI_M_M_SHFT                                                                                        0x0

#define HWIO_LPASS_LPAIF_PRI_N_ADDR                                                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001000c)
#define HWIO_LPASS_LPAIF_PRI_N_OFFS                                                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001000c)
#define HWIO_LPASS_LPAIF_PRI_N_RMSK                                                                                       0xffff
#define HWIO_LPASS_LPAIF_PRI_N_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_N_ADDR, HWIO_LPASS_LPAIF_PRI_N_RMSK)
#define HWIO_LPASS_LPAIF_PRI_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_N_ADDR, m)
#define HWIO_LPASS_LPAIF_PRI_N_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PRI_N_ADDR,v)
#define HWIO_LPASS_LPAIF_PRI_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PRI_N_ADDR,m,v,HWIO_LPASS_LPAIF_PRI_N_IN)
#define HWIO_LPASS_LPAIF_PRI_N_NOT_N_MINUS_M_BMSK                                                                         0xffff
#define HWIO_LPASS_LPAIF_PRI_N_NOT_N_MINUS_M_SHFT                                                                            0x0

#define HWIO_LPASS_LPAIF_PRI_D_ADDR                                                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00010010)
#define HWIO_LPASS_LPAIF_PRI_D_OFFS                                                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00010010)
#define HWIO_LPASS_LPAIF_PRI_D_RMSK                                                                                       0xffff
#define HWIO_LPASS_LPAIF_PRI_D_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_D_ADDR, HWIO_LPASS_LPAIF_PRI_D_RMSK)
#define HWIO_LPASS_LPAIF_PRI_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PRI_D_ADDR, m)
#define HWIO_LPASS_LPAIF_PRI_D_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PRI_D_ADDR,v)
#define HWIO_LPASS_LPAIF_PRI_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PRI_D_ADDR,m,v,HWIO_LPASS_LPAIF_PRI_D_IN)
#define HWIO_LPASS_LPAIF_PRI_D_NOT_2D_BMSK                                                                                0xffff
#define HWIO_LPASS_LPAIF_PRI_D_NOT_2D_SHFT                                                                                   0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_ADDR                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00010018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_OFFS                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00010018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_RMSK                                                                0x81ff0003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_CLK_OFF_BMSK                                                        0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_CLK_OFF_SHFT                                                              0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_CLK_DIV_BMSK                                                         0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_CLK_DIV_SHFT                                                              0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_HW_CTL_BMSK                                                                0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_HW_CTL_SHFT                                                                0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_CLK_ENABLE_BMSK                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_CLK_ENABLE_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_ADDR                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001001c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_OFFS                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001001c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_RMSK                                                                0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_CLK_OFF_BMSK                                                        0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_CLK_OFF_SHFT                                                              0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_HW_CTL_BMSK                                                                0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_HW_CTL_SHFT                                                                0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_CLK_ENABLE_BMSK                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_CLK_ENABLE_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_ADDR                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00010020)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_OFFS                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00010020)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_RMSK                                                                         0x3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_INV_EXT_CLK_BMSK                                                             0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_INV_EXT_CLK_SHFT                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_INV_INT_CLK_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_INV_INT_CLK_SHFT                                                             0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_ADDR                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x00010024)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_OFFS                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00010024)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_RMSK                                                           0x80007f13
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_BMSK                                          0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_SHFT                                                0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_CLK_COUNTER_VALUE_BMSK                                             0x7f00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_CLK_COUNTER_VALUE_SHFT                                                0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_IRQ_CLEAR_BMSK                                                       0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_IRQ_CLEAR_SHFT                                                        0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_CLK_COUNTER_EN_BMSK                                                   0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_CLK_COUNTER_EN_SHFT                                                   0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_IRQ_EN_BMSK                                                           0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_IRQ_EN_SHFT                                                           0x0

#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ADDR                                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00011000)
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_OFFS                                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00011000)
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_RMSK                                                                            0x800000f3
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ADDR, HWIO_LPASS_LPAIF_SEC_CMD_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_SEC_CMD_RCGR_IN)
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ROOT_OFF_BMSK                                                                   0x80000000
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ROOT_OFF_SHFT                                                                         0x1f
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_D_BMSK                                                                          0x80
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_D_SHFT                                                                           0x7
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_N_BMSK                                                                          0x40
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_N_SHFT                                                                           0x6
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_M_BMSK                                                                          0x20
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_M_SHFT                                                                           0x5
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                   0x10
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                    0x4
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ROOT_EN_BMSK                                                                           0x2
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ROOT_EN_SHFT                                                                           0x1
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_UPDATE_BMSK                                                                            0x1
#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_UPDATE_SHFT                                                                            0x0

#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_ADDR                                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00011004)
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_OFFS                                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00011004)
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_RMSK                                                                                0x771f
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_CFG_RCGR_ADDR, HWIO_LPASS_LPAIF_SEC_CFG_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SEC_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SEC_CFG_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_SEC_CFG_RCGR_IN)
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                    0x4000
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                       0xe
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_MODE_BMSK                                                                           0x3000
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_MODE_SHFT                                                                              0xc
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_SRC_SEL_BMSK                                                                         0x700
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_SRC_SEL_SHFT                                                                           0x8
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_SRC_DIV_BMSK                                                                          0x1f
#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_SRC_DIV_SHFT                                                                           0x0

#define HWIO_LPASS_LPAIF_SEC_M_ADDR                                                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00011008)
#define HWIO_LPASS_LPAIF_SEC_M_OFFS                                                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00011008)
#define HWIO_LPASS_LPAIF_SEC_M_RMSK                                                                                       0xffff
#define HWIO_LPASS_LPAIF_SEC_M_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_M_ADDR, HWIO_LPASS_LPAIF_SEC_M_RMSK)
#define HWIO_LPASS_LPAIF_SEC_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_M_ADDR, m)
#define HWIO_LPASS_LPAIF_SEC_M_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SEC_M_ADDR,v)
#define HWIO_LPASS_LPAIF_SEC_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SEC_M_ADDR,m,v,HWIO_LPASS_LPAIF_SEC_M_IN)
#define HWIO_LPASS_LPAIF_SEC_M_M_BMSK                                                                                     0xffff
#define HWIO_LPASS_LPAIF_SEC_M_M_SHFT                                                                                        0x0

#define HWIO_LPASS_LPAIF_SEC_N_ADDR                                                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001100c)
#define HWIO_LPASS_LPAIF_SEC_N_OFFS                                                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001100c)
#define HWIO_LPASS_LPAIF_SEC_N_RMSK                                                                                       0xffff
#define HWIO_LPASS_LPAIF_SEC_N_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_N_ADDR, HWIO_LPASS_LPAIF_SEC_N_RMSK)
#define HWIO_LPASS_LPAIF_SEC_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_N_ADDR, m)
#define HWIO_LPASS_LPAIF_SEC_N_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SEC_N_ADDR,v)
#define HWIO_LPASS_LPAIF_SEC_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SEC_N_ADDR,m,v,HWIO_LPASS_LPAIF_SEC_N_IN)
#define HWIO_LPASS_LPAIF_SEC_N_NOT_N_MINUS_M_BMSK                                                                         0xffff
#define HWIO_LPASS_LPAIF_SEC_N_NOT_N_MINUS_M_SHFT                                                                            0x0

#define HWIO_LPASS_LPAIF_SEC_D_ADDR                                                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00011010)
#define HWIO_LPASS_LPAIF_SEC_D_OFFS                                                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00011010)
#define HWIO_LPASS_LPAIF_SEC_D_RMSK                                                                                       0xffff
#define HWIO_LPASS_LPAIF_SEC_D_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_D_ADDR, HWIO_LPASS_LPAIF_SEC_D_RMSK)
#define HWIO_LPASS_LPAIF_SEC_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_SEC_D_ADDR, m)
#define HWIO_LPASS_LPAIF_SEC_D_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_SEC_D_ADDR,v)
#define HWIO_LPASS_LPAIF_SEC_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_SEC_D_ADDR,m,v,HWIO_LPASS_LPAIF_SEC_D_IN)
#define HWIO_LPASS_LPAIF_SEC_D_NOT_2D_BMSK                                                                                0xffff
#define HWIO_LPASS_LPAIF_SEC_D_NOT_2D_SHFT                                                                                   0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_ADDR                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00011018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_OFFS                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00011018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_RMSK                                                                0x81ff0003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_CLK_OFF_BMSK                                                        0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_CLK_OFF_SHFT                                                              0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_CLK_DIV_BMSK                                                         0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_CLK_DIV_SHFT                                                              0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_HW_CTL_BMSK                                                                0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_HW_CTL_SHFT                                                                0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_CLK_ENABLE_BMSK                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_CLK_ENABLE_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_ADDR                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001101c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_OFFS                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001101c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_RMSK                                                                0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_CLK_OFF_BMSK                                                        0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_CLK_OFF_SHFT                                                              0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_HW_CTL_BMSK                                                                0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_HW_CTL_SHFT                                                                0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_CLK_ENABLE_BMSK                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_CLK_ENABLE_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_ADDR                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00011020)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_OFFS                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00011020)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_RMSK                                                                         0x3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_INV_EXT_CLK_BMSK                                                             0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_INV_EXT_CLK_SHFT                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_INV_INT_CLK_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_INV_INT_CLK_SHFT                                                             0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_ADDR                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x00011024)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_OFFS                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00011024)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_RMSK                                                           0x80007f13
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_BMSK                                          0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_SHFT                                                0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_CLK_COUNTER_VALUE_BMSK                                             0x7f00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_CLK_COUNTER_VALUE_SHFT                                                0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_IRQ_CLEAR_BMSK                                                       0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_IRQ_CLEAR_SHFT                                                        0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_CLK_COUNTER_EN_BMSK                                                   0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_CLK_COUNTER_EN_SHFT                                                   0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_IRQ_EN_BMSK                                                           0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_IRQ_EN_SHFT                                                           0x0

#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_ADDR                                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00012000)
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_OFFS                                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00012000)
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_RMSK                                                                            0x800000f3
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_CMD_RCGR_ADDR, HWIO_LPASS_LPAIF_TER_CMD_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_TER_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_TER_CMD_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_TER_CMD_RCGR_IN)
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_ROOT_OFF_BMSK                                                                   0x80000000
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_ROOT_OFF_SHFT                                                                         0x1f
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_D_BMSK                                                                          0x80
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_D_SHFT                                                                           0x7
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_N_BMSK                                                                          0x40
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_N_SHFT                                                                           0x6
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_M_BMSK                                                                          0x20
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_M_SHFT                                                                           0x5
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                   0x10
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                    0x4
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_ROOT_EN_BMSK                                                                           0x2
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_ROOT_EN_SHFT                                                                           0x1
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_UPDATE_BMSK                                                                            0x1
#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_UPDATE_SHFT                                                                            0x0

#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_ADDR                                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00012004)
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_OFFS                                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00012004)
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_RMSK                                                                                0x771f
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_CFG_RCGR_ADDR, HWIO_LPASS_LPAIF_TER_CFG_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_TER_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_TER_CFG_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_TER_CFG_RCGR_IN)
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                    0x4000
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                       0xe
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_MODE_BMSK                                                                           0x3000
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_MODE_SHFT                                                                              0xc
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_SRC_SEL_BMSK                                                                         0x700
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_SRC_SEL_SHFT                                                                           0x8
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_SRC_DIV_BMSK                                                                          0x1f
#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_SRC_DIV_SHFT                                                                           0x0

#define HWIO_LPASS_LPAIF_TER_M_ADDR                                                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00012008)
#define HWIO_LPASS_LPAIF_TER_M_OFFS                                                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00012008)
#define HWIO_LPASS_LPAIF_TER_M_RMSK                                                                                       0xffff
#define HWIO_LPASS_LPAIF_TER_M_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_M_ADDR, HWIO_LPASS_LPAIF_TER_M_RMSK)
#define HWIO_LPASS_LPAIF_TER_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_M_ADDR, m)
#define HWIO_LPASS_LPAIF_TER_M_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_TER_M_ADDR,v)
#define HWIO_LPASS_LPAIF_TER_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_TER_M_ADDR,m,v,HWIO_LPASS_LPAIF_TER_M_IN)
#define HWIO_LPASS_LPAIF_TER_M_M_BMSK                                                                                     0xffff
#define HWIO_LPASS_LPAIF_TER_M_M_SHFT                                                                                        0x0

#define HWIO_LPASS_LPAIF_TER_N_ADDR                                                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001200c)
#define HWIO_LPASS_LPAIF_TER_N_OFFS                                                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001200c)
#define HWIO_LPASS_LPAIF_TER_N_RMSK                                                                                       0xffff
#define HWIO_LPASS_LPAIF_TER_N_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_N_ADDR, HWIO_LPASS_LPAIF_TER_N_RMSK)
#define HWIO_LPASS_LPAIF_TER_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_N_ADDR, m)
#define HWIO_LPASS_LPAIF_TER_N_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_TER_N_ADDR,v)
#define HWIO_LPASS_LPAIF_TER_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_TER_N_ADDR,m,v,HWIO_LPASS_LPAIF_TER_N_IN)
#define HWIO_LPASS_LPAIF_TER_N_NOT_N_MINUS_M_BMSK                                                                         0xffff
#define HWIO_LPASS_LPAIF_TER_N_NOT_N_MINUS_M_SHFT                                                                            0x0

#define HWIO_LPASS_LPAIF_TER_D_ADDR                                                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00012010)
#define HWIO_LPASS_LPAIF_TER_D_OFFS                                                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00012010)
#define HWIO_LPASS_LPAIF_TER_D_RMSK                                                                                       0xffff
#define HWIO_LPASS_LPAIF_TER_D_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_D_ADDR, HWIO_LPASS_LPAIF_TER_D_RMSK)
#define HWIO_LPASS_LPAIF_TER_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_TER_D_ADDR, m)
#define HWIO_LPASS_LPAIF_TER_D_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_TER_D_ADDR,v)
#define HWIO_LPASS_LPAIF_TER_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_TER_D_ADDR,m,v,HWIO_LPASS_LPAIF_TER_D_IN)
#define HWIO_LPASS_LPAIF_TER_D_NOT_2D_BMSK                                                                                0xffff
#define HWIO_LPASS_LPAIF_TER_D_NOT_2D_SHFT                                                                                   0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_ADDR                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00012018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_OFFS                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00012018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_RMSK                                                                0x81ff0003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_CLK_OFF_BMSK                                                        0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_CLK_OFF_SHFT                                                              0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_CLK_DIV_BMSK                                                         0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_CLK_DIV_SHFT                                                              0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_HW_CTL_BMSK                                                                0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_HW_CTL_SHFT                                                                0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_CLK_ENABLE_BMSK                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_CLK_ENABLE_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_ADDR                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001201c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_OFFS                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001201c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_RMSK                                                                0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_CLK_OFF_BMSK                                                        0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_CLK_OFF_SHFT                                                              0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_HW_CTL_BMSK                                                                0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_HW_CTL_SHFT                                                                0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_CLK_ENABLE_BMSK                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_CLK_ENABLE_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_ADDR                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00012020)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_OFFS                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00012020)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_RMSK                                                                         0x3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_INV_EXT_CLK_BMSK                                                             0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_INV_EXT_CLK_SHFT                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_INV_INT_CLK_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_INV_INT_CLK_SHFT                                                             0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_ADDR                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x00012024)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_OFFS                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00012024)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_RMSK                                                           0x80007f13
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_BMSK                                          0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_SHFT                                                0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_CLK_COUNTER_VALUE_BMSK                                             0x7f00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_CLK_COUNTER_VALUE_SHFT                                                0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_IRQ_CLEAR_BMSK                                                       0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_IRQ_CLEAR_SHFT                                                        0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_CLK_COUNTER_EN_BMSK                                                   0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_CLK_COUNTER_EN_SHFT                                                   0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_IRQ_EN_BMSK                                                           0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_IRQ_EN_SHFT                                                           0x0

#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ADDR                                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x00013000)
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_OFFS                                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00013000)
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_RMSK                                                                           0x800000f3
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ADDR, HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_IN)
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ROOT_OFF_BMSK                                                                  0x80000000
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ROOT_OFF_SHFT                                                                        0x1f
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_D_BMSK                                                                         0x80
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_D_SHFT                                                                          0x7
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_N_BMSK                                                                         0x40
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_N_SHFT                                                                          0x6
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_M_BMSK                                                                         0x20
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_M_SHFT                                                                          0x5
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                  0x10
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                   0x4
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ROOT_EN_BMSK                                                                          0x2
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ROOT_EN_SHFT                                                                          0x1
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_UPDATE_BMSK                                                                           0x1
#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_UPDATE_SHFT                                                                           0x0

#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_ADDR                                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x00013004)
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_OFFS                                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00013004)
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_RMSK                                                                               0x771f
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_ADDR, HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_IN)
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                   0x4000
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                      0xe
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_MODE_BMSK                                                                          0x3000
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_MODE_SHFT                                                                             0xc
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_SRC_SEL_BMSK                                                                        0x700
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_SRC_SEL_SHFT                                                                          0x8
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_SRC_DIV_BMSK                                                                         0x1f
#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_SRC_DIV_SHFT                                                                          0x0

#define HWIO_LPASS_LPAIF_QUAD_M_ADDR                                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00013008)
#define HWIO_LPASS_LPAIF_QUAD_M_OFFS                                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00013008)
#define HWIO_LPASS_LPAIF_QUAD_M_RMSK                                                                                      0xffff
#define HWIO_LPASS_LPAIF_QUAD_M_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_M_ADDR, HWIO_LPASS_LPAIF_QUAD_M_RMSK)
#define HWIO_LPASS_LPAIF_QUAD_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_M_ADDR, m)
#define HWIO_LPASS_LPAIF_QUAD_M_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_QUAD_M_ADDR,v)
#define HWIO_LPASS_LPAIF_QUAD_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_QUAD_M_ADDR,m,v,HWIO_LPASS_LPAIF_QUAD_M_IN)
#define HWIO_LPASS_LPAIF_QUAD_M_M_BMSK                                                                                    0xffff
#define HWIO_LPASS_LPAIF_QUAD_M_M_SHFT                                                                                       0x0

#define HWIO_LPASS_LPAIF_QUAD_N_ADDR                                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001300c)
#define HWIO_LPASS_LPAIF_QUAD_N_OFFS                                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001300c)
#define HWIO_LPASS_LPAIF_QUAD_N_RMSK                                                                                      0xffff
#define HWIO_LPASS_LPAIF_QUAD_N_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_N_ADDR, HWIO_LPASS_LPAIF_QUAD_N_RMSK)
#define HWIO_LPASS_LPAIF_QUAD_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_N_ADDR, m)
#define HWIO_LPASS_LPAIF_QUAD_N_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_QUAD_N_ADDR,v)
#define HWIO_LPASS_LPAIF_QUAD_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_QUAD_N_ADDR,m,v,HWIO_LPASS_LPAIF_QUAD_N_IN)
#define HWIO_LPASS_LPAIF_QUAD_N_NOT_N_MINUS_M_BMSK                                                                        0xffff
#define HWIO_LPASS_LPAIF_QUAD_N_NOT_N_MINUS_M_SHFT                                                                           0x0

#define HWIO_LPASS_LPAIF_QUAD_D_ADDR                                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00013010)
#define HWIO_LPASS_LPAIF_QUAD_D_OFFS                                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00013010)
#define HWIO_LPASS_LPAIF_QUAD_D_RMSK                                                                                      0xffff
#define HWIO_LPASS_LPAIF_QUAD_D_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_D_ADDR, HWIO_LPASS_LPAIF_QUAD_D_RMSK)
#define HWIO_LPASS_LPAIF_QUAD_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_QUAD_D_ADDR, m)
#define HWIO_LPASS_LPAIF_QUAD_D_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_QUAD_D_ADDR,v)
#define HWIO_LPASS_LPAIF_QUAD_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_QUAD_D_ADDR,m,v,HWIO_LPASS_LPAIF_QUAD_D_IN)
#define HWIO_LPASS_LPAIF_QUAD_D_NOT_2D_BMSK                                                                               0xffff
#define HWIO_LPASS_LPAIF_QUAD_D_NOT_2D_SHFT                                                                                  0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_ADDR                                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x00013018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_OFFS                                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00013018)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_RMSK                                                               0x81ff0003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_CLK_OFF_BMSK                                                       0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_CLK_OFF_SHFT                                                             0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_CLK_DIV_BMSK                                                        0x1ff0000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_CLK_DIV_SHFT                                                             0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_HW_CTL_BMSK                                                               0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_HW_CTL_SHFT                                                               0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_CLK_ENABLE_BMSK                                                           0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_CLK_ENABLE_SHFT                                                           0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_ADDR                                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001301c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_OFFS                                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001301c)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_RMSK                                                               0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_CLK_OFF_BMSK                                                       0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_CLK_OFF_SHFT                                                             0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_HW_CTL_BMSK                                                               0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_HW_CTL_SHFT                                                               0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_CLK_ENABLE_BMSK                                                           0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_CLK_ENABLE_SHFT                                                           0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_ADDR                                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x00013020)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_OFFS                                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00013020)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_RMSK                                                                        0x3
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_INV_EXT_CLK_BMSK                                                            0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_INV_EXT_CLK_SHFT                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_INV_INT_CLK_BMSK                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_INV_INT_CLK_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_ADDR                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x00013024)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_OFFS                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00013024)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_RMSK                                                          0x80007f13
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_BMSK                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_SHFT                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_CLK_COUNTER_VALUE_BMSK                                            0x7f00
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_CLK_COUNTER_VALUE_SHFT                                               0x8
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_IRQ_CLEAR_BMSK                                                      0x10
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_IRQ_CLEAR_SHFT                                                       0x4
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_CLK_COUNTER_EN_BMSK                                                  0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_CLK_COUNTER_EN_SHFT                                                  0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_IRQ_EN_BMSK                                                          0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_IRQ_EN_SHFT                                                          0x0

#define HWIO_LPASS_AON_CMD_RCGR_ADDR                                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00014000)
#define HWIO_LPASS_AON_CMD_RCGR_OFFS                                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00014000)
#define HWIO_LPASS_AON_CMD_RCGR_RMSK                                                                                  0x800000f3
#define HWIO_LPASS_AON_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_AON_CMD_RCGR_ADDR, HWIO_LPASS_AON_CMD_RCGR_RMSK)
#define HWIO_LPASS_AON_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AON_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_AON_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_AON_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_AON_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AON_CMD_RCGR_ADDR,m,v,HWIO_LPASS_AON_CMD_RCGR_IN)
#define HWIO_LPASS_AON_CMD_RCGR_ROOT_OFF_BMSK                                                                         0x80000000
#define HWIO_LPASS_AON_CMD_RCGR_ROOT_OFF_SHFT                                                                               0x1f
#define HWIO_LPASS_AON_CMD_RCGR_DIRTY_D_BMSK                                                                                0x80
#define HWIO_LPASS_AON_CMD_RCGR_DIRTY_D_SHFT                                                                                 0x7
#define HWIO_LPASS_AON_CMD_RCGR_DIRTY_N_BMSK                                                                                0x40
#define HWIO_LPASS_AON_CMD_RCGR_DIRTY_N_SHFT                                                                                 0x6
#define HWIO_LPASS_AON_CMD_RCGR_DIRTY_M_BMSK                                                                                0x20
#define HWIO_LPASS_AON_CMD_RCGR_DIRTY_M_SHFT                                                                                 0x5
#define HWIO_LPASS_AON_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                         0x10
#define HWIO_LPASS_AON_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                          0x4
#define HWIO_LPASS_AON_CMD_RCGR_ROOT_EN_BMSK                                                                                 0x2
#define HWIO_LPASS_AON_CMD_RCGR_ROOT_EN_SHFT                                                                                 0x1
#define HWIO_LPASS_AON_CMD_RCGR_UPDATE_BMSK                                                                                  0x1
#define HWIO_LPASS_AON_CMD_RCGR_UPDATE_SHFT                                                                                  0x0

#define HWIO_LPASS_AON_CFG_RCGR_ADDR                                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00014004)
#define HWIO_LPASS_AON_CFG_RCGR_OFFS                                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00014004)
#define HWIO_LPASS_AON_CFG_RCGR_RMSK                                                                                      0x771f
#define HWIO_LPASS_AON_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_AON_CFG_RCGR_ADDR, HWIO_LPASS_AON_CFG_RCGR_RMSK)
#define HWIO_LPASS_AON_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AON_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_AON_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_AON_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_AON_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AON_CFG_RCGR_ADDR,m,v,HWIO_LPASS_AON_CFG_RCGR_IN)
#define HWIO_LPASS_AON_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                          0x4000
#define HWIO_LPASS_AON_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                             0xe
#define HWIO_LPASS_AON_CFG_RCGR_MODE_BMSK                                                                                 0x3000
#define HWIO_LPASS_AON_CFG_RCGR_MODE_SHFT                                                                                    0xc
#define HWIO_LPASS_AON_CFG_RCGR_SRC_SEL_BMSK                                                                               0x700
#define HWIO_LPASS_AON_CFG_RCGR_SRC_SEL_SHFT                                                                                 0x8
#define HWIO_LPASS_AON_CFG_RCGR_SRC_DIV_BMSK                                                                                0x1f
#define HWIO_LPASS_AON_CFG_RCGR_SRC_DIV_SHFT                                                                                 0x0

#define HWIO_LPASS_AON_M_ADDR                                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00014008)
#define HWIO_LPASS_AON_M_OFFS                                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00014008)
#define HWIO_LPASS_AON_M_RMSK                                                                                               0xff
#define HWIO_LPASS_AON_M_IN          \
        in_dword_masked(HWIO_LPASS_AON_M_ADDR, HWIO_LPASS_AON_M_RMSK)
#define HWIO_LPASS_AON_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_AON_M_ADDR, m)
#define HWIO_LPASS_AON_M_OUT(v)      \
        out_dword(HWIO_LPASS_AON_M_ADDR,v)
#define HWIO_LPASS_AON_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AON_M_ADDR,m,v,HWIO_LPASS_AON_M_IN)
#define HWIO_LPASS_AON_M_M_BMSK                                                                                             0xff
#define HWIO_LPASS_AON_M_M_SHFT                                                                                              0x0

#define HWIO_LPASS_AON_N_ADDR                                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001400c)
#define HWIO_LPASS_AON_N_OFFS                                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001400c)
#define HWIO_LPASS_AON_N_RMSK                                                                                               0xff
#define HWIO_LPASS_AON_N_IN          \
        in_dword_masked(HWIO_LPASS_AON_N_ADDR, HWIO_LPASS_AON_N_RMSK)
#define HWIO_LPASS_AON_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_AON_N_ADDR, m)
#define HWIO_LPASS_AON_N_OUT(v)      \
        out_dword(HWIO_LPASS_AON_N_ADDR,v)
#define HWIO_LPASS_AON_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AON_N_ADDR,m,v,HWIO_LPASS_AON_N_IN)
#define HWIO_LPASS_AON_N_NOT_N_MINUS_M_BMSK                                                                                 0xff
#define HWIO_LPASS_AON_N_NOT_N_MINUS_M_SHFT                                                                                  0x0

#define HWIO_LPASS_AON_D_ADDR                                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00014010)
#define HWIO_LPASS_AON_D_OFFS                                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00014010)
#define HWIO_LPASS_AON_D_RMSK                                                                                               0xff
#define HWIO_LPASS_AON_D_IN          \
        in_dword_masked(HWIO_LPASS_AON_D_ADDR, HWIO_LPASS_AON_D_RMSK)
#define HWIO_LPASS_AON_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_AON_D_ADDR, m)
#define HWIO_LPASS_AON_D_OUT(v)      \
        out_dword(HWIO_LPASS_AON_D_ADDR,v)
#define HWIO_LPASS_AON_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AON_D_ADDR,m,v,HWIO_LPASS_AON_D_IN)
#define HWIO_LPASS_AON_D_NOT_2D_BMSK                                                                                        0xff
#define HWIO_LPASS_AON_D_NOT_2D_SHFT                                                                                         0x0

#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_ADDR                                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x00014014)
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_OFFS                                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00014014)
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_RMSK                                                                        0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_CLK_OFF_BMSK                                                                0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_CLK_OFF_SHFT                                                                      0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_HW_CTL_BMSK                                                                        0x2
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_HW_CTL_SHFT                                                                        0x1
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_CLK_ENABLE_BMSK                                                                    0x1
#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_CLK_ENABLE_SHFT                                                                    0x0

#define HWIO_LPASS_ATIME_CMD_RCGR_ADDR                                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00015000)
#define HWIO_LPASS_ATIME_CMD_RCGR_OFFS                                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00015000)
#define HWIO_LPASS_ATIME_CMD_RCGR_RMSK                                                                                0x800000f3
#define HWIO_LPASS_ATIME_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_ATIME_CMD_RCGR_ADDR, HWIO_LPASS_ATIME_CMD_RCGR_RMSK)
#define HWIO_LPASS_ATIME_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ATIME_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_ATIME_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_ATIME_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_ATIME_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ATIME_CMD_RCGR_ADDR,m,v,HWIO_LPASS_ATIME_CMD_RCGR_IN)
#define HWIO_LPASS_ATIME_CMD_RCGR_ROOT_OFF_BMSK                                                                       0x80000000
#define HWIO_LPASS_ATIME_CMD_RCGR_ROOT_OFF_SHFT                                                                             0x1f
#define HWIO_LPASS_ATIME_CMD_RCGR_DIRTY_D_BMSK                                                                              0x80
#define HWIO_LPASS_ATIME_CMD_RCGR_DIRTY_D_SHFT                                                                               0x7
#define HWIO_LPASS_ATIME_CMD_RCGR_DIRTY_N_BMSK                                                                              0x40
#define HWIO_LPASS_ATIME_CMD_RCGR_DIRTY_N_SHFT                                                                               0x6
#define HWIO_LPASS_ATIME_CMD_RCGR_DIRTY_M_BMSK                                                                              0x20
#define HWIO_LPASS_ATIME_CMD_RCGR_DIRTY_M_SHFT                                                                               0x5
#define HWIO_LPASS_ATIME_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                       0x10
#define HWIO_LPASS_ATIME_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                        0x4
#define HWIO_LPASS_ATIME_CMD_RCGR_ROOT_EN_BMSK                                                                               0x2
#define HWIO_LPASS_ATIME_CMD_RCGR_ROOT_EN_SHFT                                                                               0x1
#define HWIO_LPASS_ATIME_CMD_RCGR_UPDATE_BMSK                                                                                0x1
#define HWIO_LPASS_ATIME_CMD_RCGR_UPDATE_SHFT                                                                                0x0

#define HWIO_LPASS_ATIME_CFG_RCGR_ADDR                                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00015004)
#define HWIO_LPASS_ATIME_CFG_RCGR_OFFS                                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00015004)
#define HWIO_LPASS_ATIME_CFG_RCGR_RMSK                                                                                    0x771f
#define HWIO_LPASS_ATIME_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_ATIME_CFG_RCGR_ADDR, HWIO_LPASS_ATIME_CFG_RCGR_RMSK)
#define HWIO_LPASS_ATIME_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ATIME_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_ATIME_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_ATIME_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_ATIME_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ATIME_CFG_RCGR_ADDR,m,v,HWIO_LPASS_ATIME_CFG_RCGR_IN)
#define HWIO_LPASS_ATIME_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                        0x4000
#define HWIO_LPASS_ATIME_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                           0xe
#define HWIO_LPASS_ATIME_CFG_RCGR_MODE_BMSK                                                                               0x3000
#define HWIO_LPASS_ATIME_CFG_RCGR_MODE_SHFT                                                                                  0xc
#define HWIO_LPASS_ATIME_CFG_RCGR_SRC_SEL_BMSK                                                                             0x700
#define HWIO_LPASS_ATIME_CFG_RCGR_SRC_SEL_SHFT                                                                               0x8
#define HWIO_LPASS_ATIME_CFG_RCGR_SRC_DIV_BMSK                                                                              0x1f
#define HWIO_LPASS_ATIME_CFG_RCGR_SRC_DIV_SHFT                                                                               0x0

#define HWIO_LPASS_ATIME_M_ADDR                                                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00015008)
#define HWIO_LPASS_ATIME_M_OFFS                                                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00015008)
#define HWIO_LPASS_ATIME_M_RMSK                                                                                             0xff
#define HWIO_LPASS_ATIME_M_IN          \
        in_dword_masked(HWIO_LPASS_ATIME_M_ADDR, HWIO_LPASS_ATIME_M_RMSK)
#define HWIO_LPASS_ATIME_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_ATIME_M_ADDR, m)
#define HWIO_LPASS_ATIME_M_OUT(v)      \
        out_dword(HWIO_LPASS_ATIME_M_ADDR,v)
#define HWIO_LPASS_ATIME_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ATIME_M_ADDR,m,v,HWIO_LPASS_ATIME_M_IN)
#define HWIO_LPASS_ATIME_M_M_BMSK                                                                                           0xff
#define HWIO_LPASS_ATIME_M_M_SHFT                                                                                            0x0

#define HWIO_LPASS_ATIME_N_ADDR                                                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001500c)
#define HWIO_LPASS_ATIME_N_OFFS                                                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001500c)
#define HWIO_LPASS_ATIME_N_RMSK                                                                                             0xff
#define HWIO_LPASS_ATIME_N_IN          \
        in_dword_masked(HWIO_LPASS_ATIME_N_ADDR, HWIO_LPASS_ATIME_N_RMSK)
#define HWIO_LPASS_ATIME_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_ATIME_N_ADDR, m)
#define HWIO_LPASS_ATIME_N_OUT(v)      \
        out_dword(HWIO_LPASS_ATIME_N_ADDR,v)
#define HWIO_LPASS_ATIME_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ATIME_N_ADDR,m,v,HWIO_LPASS_ATIME_N_IN)
#define HWIO_LPASS_ATIME_N_NOT_N_MINUS_M_BMSK                                                                               0xff
#define HWIO_LPASS_ATIME_N_NOT_N_MINUS_M_SHFT                                                                                0x0

#define HWIO_LPASS_ATIME_D_ADDR                                                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00015010)
#define HWIO_LPASS_ATIME_D_OFFS                                                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00015010)
#define HWIO_LPASS_ATIME_D_RMSK                                                                                             0xff
#define HWIO_LPASS_ATIME_D_IN          \
        in_dword_masked(HWIO_LPASS_ATIME_D_ADDR, HWIO_LPASS_ATIME_D_RMSK)
#define HWIO_LPASS_ATIME_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_ATIME_D_ADDR, m)
#define HWIO_LPASS_ATIME_D_OUT(v)      \
        out_dword(HWIO_LPASS_ATIME_D_ADDR,v)
#define HWIO_LPASS_ATIME_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ATIME_D_ADDR,m,v,HWIO_LPASS_ATIME_D_IN)
#define HWIO_LPASS_ATIME_D_NOT_2D_BMSK                                                                                      0xff
#define HWIO_LPASS_ATIME_D_NOT_2D_SHFT                                                                                       0x0

#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_ADDR                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00015014)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_OFFS                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00015014)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_RMSK                                                                  0x80000003
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_CLK_OFF_BMSK                                                          0x80000000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_CLK_OFF_SHFT                                                                0x1f
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_HW_CTL_BMSK                                                                  0x2
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_HW_CTL_SHFT                                                                  0x1
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_CLK_ENABLE_BMSK                                                              0x1
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_CLK_ENABLE_SHFT                                                              0x0

#define HWIO_LPASS_RESAMPLER_CMD_RCGR_ADDR                                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00016000)
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_OFFS                                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00016000)
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_RMSK                                                                            0x800000f3
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_RESAMPLER_CMD_RCGR_ADDR, HWIO_LPASS_RESAMPLER_CMD_RCGR_RMSK)
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_RESAMPLER_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_RESAMPLER_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_RESAMPLER_CMD_RCGR_ADDR,m,v,HWIO_LPASS_RESAMPLER_CMD_RCGR_IN)
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_ROOT_OFF_BMSK                                                                   0x80000000
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_ROOT_OFF_SHFT                                                                         0x1f
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_D_BMSK                                                                          0x80
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_D_SHFT                                                                           0x7
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_N_BMSK                                                                          0x40
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_N_SHFT                                                                           0x6
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_M_BMSK                                                                          0x20
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_M_SHFT                                                                           0x5
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                   0x10
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                    0x4
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_ROOT_EN_BMSK                                                                           0x2
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_ROOT_EN_SHFT                                                                           0x1
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_UPDATE_BMSK                                                                            0x1
#define HWIO_LPASS_RESAMPLER_CMD_RCGR_UPDATE_SHFT                                                                            0x0

#define HWIO_LPASS_RESAMPLER_CFG_RCGR_ADDR                                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00016004)
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_OFFS                                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00016004)
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_RMSK                                                                                0x771f
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_RESAMPLER_CFG_RCGR_ADDR, HWIO_LPASS_RESAMPLER_CFG_RCGR_RMSK)
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_RESAMPLER_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_RESAMPLER_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_RESAMPLER_CFG_RCGR_ADDR,m,v,HWIO_LPASS_RESAMPLER_CFG_RCGR_IN)
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                    0x4000
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                       0xe
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_MODE_BMSK                                                                           0x3000
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_MODE_SHFT                                                                              0xc
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_SRC_SEL_BMSK                                                                         0x700
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_SRC_SEL_SHFT                                                                           0x8
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_SRC_DIV_BMSK                                                                          0x1f
#define HWIO_LPASS_RESAMPLER_CFG_RCGR_SRC_DIV_SHFT                                                                           0x0

#define HWIO_LPASS_RESAMPLER_M_ADDR                                                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00016008)
#define HWIO_LPASS_RESAMPLER_M_OFFS                                                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00016008)
#define HWIO_LPASS_RESAMPLER_M_RMSK                                                                                         0xff
#define HWIO_LPASS_RESAMPLER_M_IN          \
        in_dword_masked(HWIO_LPASS_RESAMPLER_M_ADDR, HWIO_LPASS_RESAMPLER_M_RMSK)
#define HWIO_LPASS_RESAMPLER_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_RESAMPLER_M_ADDR, m)
#define HWIO_LPASS_RESAMPLER_M_OUT(v)      \
        out_dword(HWIO_LPASS_RESAMPLER_M_ADDR,v)
#define HWIO_LPASS_RESAMPLER_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_RESAMPLER_M_ADDR,m,v,HWIO_LPASS_RESAMPLER_M_IN)
#define HWIO_LPASS_RESAMPLER_M_M_BMSK                                                                                       0xff
#define HWIO_LPASS_RESAMPLER_M_M_SHFT                                                                                        0x0

#define HWIO_LPASS_RESAMPLER_N_ADDR                                                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001600c)
#define HWIO_LPASS_RESAMPLER_N_OFFS                                                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001600c)
#define HWIO_LPASS_RESAMPLER_N_RMSK                                                                                         0xff
#define HWIO_LPASS_RESAMPLER_N_IN          \
        in_dword_masked(HWIO_LPASS_RESAMPLER_N_ADDR, HWIO_LPASS_RESAMPLER_N_RMSK)
#define HWIO_LPASS_RESAMPLER_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_RESAMPLER_N_ADDR, m)
#define HWIO_LPASS_RESAMPLER_N_OUT(v)      \
        out_dword(HWIO_LPASS_RESAMPLER_N_ADDR,v)
#define HWIO_LPASS_RESAMPLER_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_RESAMPLER_N_ADDR,m,v,HWIO_LPASS_RESAMPLER_N_IN)
#define HWIO_LPASS_RESAMPLER_N_NOT_N_MINUS_M_BMSK                                                                           0xff
#define HWIO_LPASS_RESAMPLER_N_NOT_N_MINUS_M_SHFT                                                                            0x0

#define HWIO_LPASS_RESAMPLER_D_ADDR                                                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00016010)
#define HWIO_LPASS_RESAMPLER_D_OFFS                                                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00016010)
#define HWIO_LPASS_RESAMPLER_D_RMSK                                                                                         0xff
#define HWIO_LPASS_RESAMPLER_D_IN          \
        in_dword_masked(HWIO_LPASS_RESAMPLER_D_ADDR, HWIO_LPASS_RESAMPLER_D_RMSK)
#define HWIO_LPASS_RESAMPLER_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_RESAMPLER_D_ADDR, m)
#define HWIO_LPASS_RESAMPLER_D_OUT(v)      \
        out_dword(HWIO_LPASS_RESAMPLER_D_ADDR,v)
#define HWIO_LPASS_RESAMPLER_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_RESAMPLER_D_ADDR,m,v,HWIO_LPASS_RESAMPLER_D_IN)
#define HWIO_LPASS_RESAMPLER_D_NOT_2D_BMSK                                                                                  0xff
#define HWIO_LPASS_RESAMPLER_D_NOT_2D_SHFT                                                                                   0x0

#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_ADDR                                                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x00016014)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_OFFS                                                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00016014)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_RMSK                                                                     0x80007ff3
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_CLK_OFF_BMSK                                                             0x80000000
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_CLK_OFF_SHFT                                                                   0x1f
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_FORCE_MEM_CORE_ON_BMSK                                                       0x4000
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_FORCE_MEM_CORE_ON_SHFT                                                          0xe
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                                     0x2000
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                        0xd
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                                    0x1000
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                       0xc
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_WAKEUP_BMSK                                                                   0xf00
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_WAKEUP_SHFT                                                                     0x8
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_SLEEP_BMSK                                                                     0xf0
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_SLEEP_SHFT                                                                      0x4
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_HW_CTL_BMSK                                                                     0x2
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_HW_CTL_SHFT                                                                     0x1
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_CLK_ENABLE_BMSK                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_CLK_ENABLE_SHFT                                                                 0x0

#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_ADDR                                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x00017000)
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_OFFS                                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00017000)
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_RMSK                                                                          0x800000f3
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_ADDR, HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_RMSK)
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_ADDR,m,v,HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_IN)
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_ROOT_OFF_BMSK                                                                 0x80000000
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_ROOT_OFF_SHFT                                                                       0x1f
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_DIRTY_D_BMSK                                                                        0x80
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_DIRTY_D_SHFT                                                                         0x7
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_DIRTY_N_BMSK                                                                        0x40
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_DIRTY_N_SHFT                                                                         0x6
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_DIRTY_M_BMSK                                                                        0x20
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_DIRTY_M_SHFT                                                                         0x5
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                 0x10
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                  0x4
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_ROOT_EN_BMSK                                                                         0x2
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_ROOT_EN_SHFT                                                                         0x1
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_UPDATE_BMSK                                                                          0x1
#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_UPDATE_SHFT                                                                          0x0

#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_ADDR                                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x00017004)
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_OFFS                                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00017004)
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_RMSK                                                                              0x771f
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_ADDR, HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_RMSK)
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_ADDR,m,v,HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_IN)
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                  0x4000
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                     0xe
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_MODE_BMSK                                                                         0x3000
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_MODE_SHFT                                                                            0xc
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_SRC_SEL_BMSK                                                                       0x700
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_SRC_SEL_SHFT                                                                         0x8
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_SRC_DIV_BMSK                                                                        0x1f
#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_SRC_DIV_SHFT                                                                         0x0

#define HWIO_LPASS_AUD_SLIMBUS_M_ADDR                                                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x00017008)
#define HWIO_LPASS_AUD_SLIMBUS_M_OFFS                                                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00017008)
#define HWIO_LPASS_AUD_SLIMBUS_M_RMSK                                                                                       0xff
#define HWIO_LPASS_AUD_SLIMBUS_M_IN          \
        in_dword_masked(HWIO_LPASS_AUD_SLIMBUS_M_ADDR, HWIO_LPASS_AUD_SLIMBUS_M_RMSK)
#define HWIO_LPASS_AUD_SLIMBUS_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUD_SLIMBUS_M_ADDR, m)
#define HWIO_LPASS_AUD_SLIMBUS_M_OUT(v)      \
        out_dword(HWIO_LPASS_AUD_SLIMBUS_M_ADDR,v)
#define HWIO_LPASS_AUD_SLIMBUS_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUD_SLIMBUS_M_ADDR,m,v,HWIO_LPASS_AUD_SLIMBUS_M_IN)
#define HWIO_LPASS_AUD_SLIMBUS_M_M_BMSK                                                                                     0xff
#define HWIO_LPASS_AUD_SLIMBUS_M_M_SHFT                                                                                      0x0

#define HWIO_LPASS_AUD_SLIMBUS_N_ADDR                                                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001700c)
#define HWIO_LPASS_AUD_SLIMBUS_N_OFFS                                                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001700c)
#define HWIO_LPASS_AUD_SLIMBUS_N_RMSK                                                                                       0xff
#define HWIO_LPASS_AUD_SLIMBUS_N_IN          \
        in_dword_masked(HWIO_LPASS_AUD_SLIMBUS_N_ADDR, HWIO_LPASS_AUD_SLIMBUS_N_RMSK)
#define HWIO_LPASS_AUD_SLIMBUS_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUD_SLIMBUS_N_ADDR, m)
#define HWIO_LPASS_AUD_SLIMBUS_N_OUT(v)      \
        out_dword(HWIO_LPASS_AUD_SLIMBUS_N_ADDR,v)
#define HWIO_LPASS_AUD_SLIMBUS_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUD_SLIMBUS_N_ADDR,m,v,HWIO_LPASS_AUD_SLIMBUS_N_IN)
#define HWIO_LPASS_AUD_SLIMBUS_N_NOT_N_MINUS_M_BMSK                                                                         0xff
#define HWIO_LPASS_AUD_SLIMBUS_N_NOT_N_MINUS_M_SHFT                                                                          0x0

#define HWIO_LPASS_AUD_SLIMBUS_D_ADDR                                                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x00017010)
#define HWIO_LPASS_AUD_SLIMBUS_D_OFFS                                                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00017010)
#define HWIO_LPASS_AUD_SLIMBUS_D_RMSK                                                                                       0xff
#define HWIO_LPASS_AUD_SLIMBUS_D_IN          \
        in_dword_masked(HWIO_LPASS_AUD_SLIMBUS_D_ADDR, HWIO_LPASS_AUD_SLIMBUS_D_RMSK)
#define HWIO_LPASS_AUD_SLIMBUS_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUD_SLIMBUS_D_ADDR, m)
#define HWIO_LPASS_AUD_SLIMBUS_D_OUT(v)      \
        out_dword(HWIO_LPASS_AUD_SLIMBUS_D_ADDR,v)
#define HWIO_LPASS_AUD_SLIMBUS_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUD_SLIMBUS_D_ADDR,m,v,HWIO_LPASS_AUD_SLIMBUS_D_IN)
#define HWIO_LPASS_AUD_SLIMBUS_D_NOT_2D_BMSK                                                                                0xff
#define HWIO_LPASS_AUD_SLIMBUS_D_NOT_2D_SHFT                                                                                 0x0

#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_ADDR                                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00017014)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_OFFS                                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00017014)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_RMSK                                                                   0x80000003
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_CLK_OFF_BMSK                                                           0x80000000
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_CLK_OFF_SHFT                                                                 0x1f
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_HW_CTL_BMSK                                                                   0x2
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_HW_CTL_SHFT                                                                   0x1
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_CLK_ENABLE_BMSK                                                               0x1
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_CLK_ENABLE_SHFT                                                               0x0

#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_ADDR                                                              (LPASS_LPASS_CC_REG_REG_BASE      + 0x00017018)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_OFFS                                                              (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00017018)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_RMSK                                                              0x80007ff3
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_CLK_OFF_BMSK                                                      0x80000000
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_CLK_OFF_SHFT                                                            0x1f
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                                                0x4000
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                                   0xe
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                              0x2000
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                 0xd
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                             0x1000
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                0xc
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_WAKEUP_BMSK                                                            0xf00
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_WAKEUP_SHFT                                                              0x8
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_SLEEP_BMSK                                                              0xf0
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_SLEEP_SHFT                                                               0x4
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_HW_CTL_BMSK                                                              0x2
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_HW_CTL_SHFT                                                              0x1
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_CLK_ENABLE_BMSK                                                          0x1
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_CLK_ENABLE_SHFT                                                          0x0

#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_ADDR                                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001701c)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_OFFS                                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001701c)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_RMSK                                                               0x80000003
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_CLK_OFF_BMSK                                                       0x80000000
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_CLK_OFF_SHFT                                                             0x1f
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_HW_CTL_BMSK                                                               0x2
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_HW_CTL_SHFT                                                               0x1
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_CLK_ENABLE_BMSK                                                           0x1
#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_CLK_ENABLE_SHFT                                                           0x0

#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_ADDR                                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x00018000)
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_OFFS                                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00018000)
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_RMSK                                                                          0x800000f3
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_ADDR, HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_RMSK)
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_ADDR,m,v,HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_IN)
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_ROOT_OFF_BMSK                                                                 0x80000000
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_ROOT_OFF_SHFT                                                                       0x1f
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_DIRTY_D_BMSK                                                                        0x80
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_DIRTY_D_SHFT                                                                         0x7
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_DIRTY_N_BMSK                                                                        0x40
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_DIRTY_N_SHFT                                                                         0x6
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_DIRTY_M_BMSK                                                                        0x20
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_DIRTY_M_SHFT                                                                         0x5
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                 0x10
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                  0x4
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_ROOT_EN_BMSK                                                                         0x2
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_ROOT_EN_SHFT                                                                         0x1
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_UPDATE_BMSK                                                                          0x1
#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_UPDATE_SHFT                                                                          0x0

#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_ADDR                                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x00018004)
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_OFFS                                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00018004)
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_RMSK                                                                              0x771f
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_ADDR, HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_RMSK)
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_ADDR,m,v,HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_IN)
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                  0x4000
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                     0xe
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_MODE_BMSK                                                                         0x3000
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_MODE_SHFT                                                                            0xc
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_SRC_SEL_BMSK                                                                       0x700
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_SRC_SEL_SHFT                                                                         0x8
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_SRC_DIV_BMSK                                                                        0x1f
#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_SRC_DIV_SHFT                                                                         0x0

#define HWIO_LPASS_QCA_SLIMBUS_M_ADDR                                                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x00018008)
#define HWIO_LPASS_QCA_SLIMBUS_M_OFFS                                                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00018008)
#define HWIO_LPASS_QCA_SLIMBUS_M_RMSK                                                                                       0xff
#define HWIO_LPASS_QCA_SLIMBUS_M_IN          \
        in_dword_masked(HWIO_LPASS_QCA_SLIMBUS_M_ADDR, HWIO_LPASS_QCA_SLIMBUS_M_RMSK)
#define HWIO_LPASS_QCA_SLIMBUS_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_QCA_SLIMBUS_M_ADDR, m)
#define HWIO_LPASS_QCA_SLIMBUS_M_OUT(v)      \
        out_dword(HWIO_LPASS_QCA_SLIMBUS_M_ADDR,v)
#define HWIO_LPASS_QCA_SLIMBUS_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QCA_SLIMBUS_M_ADDR,m,v,HWIO_LPASS_QCA_SLIMBUS_M_IN)
#define HWIO_LPASS_QCA_SLIMBUS_M_M_BMSK                                                                                     0xff
#define HWIO_LPASS_QCA_SLIMBUS_M_M_SHFT                                                                                      0x0

#define HWIO_LPASS_QCA_SLIMBUS_N_ADDR                                                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001800c)
#define HWIO_LPASS_QCA_SLIMBUS_N_OFFS                                                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001800c)
#define HWIO_LPASS_QCA_SLIMBUS_N_RMSK                                                                                       0xff
#define HWIO_LPASS_QCA_SLIMBUS_N_IN          \
        in_dword_masked(HWIO_LPASS_QCA_SLIMBUS_N_ADDR, HWIO_LPASS_QCA_SLIMBUS_N_RMSK)
#define HWIO_LPASS_QCA_SLIMBUS_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_QCA_SLIMBUS_N_ADDR, m)
#define HWIO_LPASS_QCA_SLIMBUS_N_OUT(v)      \
        out_dword(HWIO_LPASS_QCA_SLIMBUS_N_ADDR,v)
#define HWIO_LPASS_QCA_SLIMBUS_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QCA_SLIMBUS_N_ADDR,m,v,HWIO_LPASS_QCA_SLIMBUS_N_IN)
#define HWIO_LPASS_QCA_SLIMBUS_N_NOT_N_MINUS_M_BMSK                                                                         0xff
#define HWIO_LPASS_QCA_SLIMBUS_N_NOT_N_MINUS_M_SHFT                                                                          0x0

#define HWIO_LPASS_QCA_SLIMBUS_D_ADDR                                                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x00018010)
#define HWIO_LPASS_QCA_SLIMBUS_D_OFFS                                                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00018010)
#define HWIO_LPASS_QCA_SLIMBUS_D_RMSK                                                                                       0xff
#define HWIO_LPASS_QCA_SLIMBUS_D_IN          \
        in_dword_masked(HWIO_LPASS_QCA_SLIMBUS_D_ADDR, HWIO_LPASS_QCA_SLIMBUS_D_RMSK)
#define HWIO_LPASS_QCA_SLIMBUS_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_QCA_SLIMBUS_D_ADDR, m)
#define HWIO_LPASS_QCA_SLIMBUS_D_OUT(v)      \
        out_dword(HWIO_LPASS_QCA_SLIMBUS_D_ADDR,v)
#define HWIO_LPASS_QCA_SLIMBUS_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QCA_SLIMBUS_D_ADDR,m,v,HWIO_LPASS_QCA_SLIMBUS_D_IN)
#define HWIO_LPASS_QCA_SLIMBUS_D_NOT_2D_BMSK                                                                                0xff
#define HWIO_LPASS_QCA_SLIMBUS_D_NOT_2D_SHFT                                                                                 0x0

#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_ADDR                                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00018014)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_OFFS                                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00018014)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_RMSK                                                                   0x80000003
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_CLK_OFF_BMSK                                                           0x80000000
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_CLK_OFF_SHFT                                                                 0x1f
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_HW_CTL_BMSK                                                                   0x2
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_HW_CTL_SHFT                                                                   0x1
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_CLK_ENABLE_BMSK                                                               0x1
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_CLK_ENABLE_SHFT                                                               0x0

#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_ADDR                                                              (LPASS_LPASS_CC_REG_REG_BASE      + 0x00018018)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_OFFS                                                              (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00018018)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_RMSK                                                              0x80007ff3
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_CLK_OFF_BMSK                                                      0x80000000
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_CLK_OFF_SHFT                                                            0x1f
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                                                0x4000
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                                   0xe
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                              0x2000
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                 0xd
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                             0x1000
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                0xc
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_WAKEUP_BMSK                                                            0xf00
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_WAKEUP_SHFT                                                              0x8
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_SLEEP_BMSK                                                              0xf0
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_SLEEP_SHFT                                                               0x4
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_HW_CTL_BMSK                                                              0x2
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_HW_CTL_SHFT                                                              0x1
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_CLK_ENABLE_BMSK                                                          0x1
#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_CLK_ENABLE_SHFT                                                          0x0

#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ADDR                                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x00019000)
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_OFFS                                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00019000)
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_RMSK                                                                          0x800000f3
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ADDR, HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_IN)
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ROOT_OFF_BMSK                                                                 0x80000000
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ROOT_OFF_SHFT                                                                       0x1f
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_D_BMSK                                                                        0x80
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_D_SHFT                                                                         0x7
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_N_BMSK                                                                        0x40
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_N_SHFT                                                                         0x6
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_M_BMSK                                                                        0x20
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_M_SHFT                                                                         0x5
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                 0x10
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                  0x4
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ROOT_EN_BMSK                                                                         0x2
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ROOT_EN_SHFT                                                                         0x1
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_UPDATE_BMSK                                                                          0x1
#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_UPDATE_SHFT                                                                          0x0

#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_ADDR                                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x00019004)
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_OFFS                                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00019004)
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_RMSK                                                                              0x771f
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_ADDR, HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_RMSK)
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_ADDR,m,v,HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_IN)
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                  0x4000
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                     0xe
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_MODE_BMSK                                                                         0x3000
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_MODE_SHFT                                                                            0xc
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_SRC_SEL_BMSK                                                                       0x700
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_SRC_SEL_SHFT                                                                         0x8
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_SRC_DIV_BMSK                                                                        0x1f
#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_SRC_DIV_SHFT                                                                         0x0

#define HWIO_LPASS_LPAIF_PCMOE_M_ADDR                                                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x00019008)
#define HWIO_LPASS_LPAIF_PCMOE_M_OFFS                                                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00019008)
#define HWIO_LPASS_LPAIF_PCMOE_M_RMSK                                                                                       0xff
#define HWIO_LPASS_LPAIF_PCMOE_M_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_M_ADDR, HWIO_LPASS_LPAIF_PCMOE_M_RMSK)
#define HWIO_LPASS_LPAIF_PCMOE_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_M_ADDR, m)
#define HWIO_LPASS_LPAIF_PCMOE_M_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCMOE_M_ADDR,v)
#define HWIO_LPASS_LPAIF_PCMOE_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCMOE_M_ADDR,m,v,HWIO_LPASS_LPAIF_PCMOE_M_IN)
#define HWIO_LPASS_LPAIF_PCMOE_M_M_BMSK                                                                                     0xff
#define HWIO_LPASS_LPAIF_PCMOE_M_M_SHFT                                                                                      0x0

#define HWIO_LPASS_LPAIF_PCMOE_N_ADDR                                                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001900c)
#define HWIO_LPASS_LPAIF_PCMOE_N_OFFS                                                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001900c)
#define HWIO_LPASS_LPAIF_PCMOE_N_RMSK                                                                                       0xff
#define HWIO_LPASS_LPAIF_PCMOE_N_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_N_ADDR, HWIO_LPASS_LPAIF_PCMOE_N_RMSK)
#define HWIO_LPASS_LPAIF_PCMOE_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_N_ADDR, m)
#define HWIO_LPASS_LPAIF_PCMOE_N_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCMOE_N_ADDR,v)
#define HWIO_LPASS_LPAIF_PCMOE_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCMOE_N_ADDR,m,v,HWIO_LPASS_LPAIF_PCMOE_N_IN)
#define HWIO_LPASS_LPAIF_PCMOE_N_NOT_N_MINUS_M_BMSK                                                                         0xff
#define HWIO_LPASS_LPAIF_PCMOE_N_NOT_N_MINUS_M_SHFT                                                                          0x0

#define HWIO_LPASS_LPAIF_PCMOE_D_ADDR                                                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x00019010)
#define HWIO_LPASS_LPAIF_PCMOE_D_OFFS                                                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00019010)
#define HWIO_LPASS_LPAIF_PCMOE_D_RMSK                                                                                       0xff
#define HWIO_LPASS_LPAIF_PCMOE_D_IN          \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_D_ADDR, HWIO_LPASS_LPAIF_PCMOE_D_RMSK)
#define HWIO_LPASS_LPAIF_PCMOE_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAIF_PCMOE_D_ADDR, m)
#define HWIO_LPASS_LPAIF_PCMOE_D_OUT(v)      \
        out_dword(HWIO_LPASS_LPAIF_PCMOE_D_ADDR,v)
#define HWIO_LPASS_LPAIF_PCMOE_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAIF_PCMOE_D_ADDR,m,v,HWIO_LPASS_LPAIF_PCMOE_D_IN)
#define HWIO_LPASS_LPAIF_PCMOE_D_NOT_2D_BMSK                                                                                0xff
#define HWIO_LPASS_LPAIF_PCMOE_D_NOT_2D_SHFT                                                                                 0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_ADDR                                                             (LPASS_LPASS_CC_REG_REG_BASE      + 0x00019014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_OFFS                                                             (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00019014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_RMSK                                                             0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_CLK_OFF_BMSK                                                     0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_CLK_OFF_SHFT                                                           0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_HW_CTL_BMSK                                                             0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_HW_CTL_SHFT                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_CLK_ENABLE_BMSK                                                         0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_CLK_ENABLE_SHFT                                                         0x0

#define HWIO_LPASS_SLEEP_CMD_RCGR_ADDR                                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001a000)
#define HWIO_LPASS_SLEEP_CMD_RCGR_OFFS                                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001a000)
#define HWIO_LPASS_SLEEP_CMD_RCGR_RMSK                                                                                0x800000f3
#define HWIO_LPASS_SLEEP_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SLEEP_CMD_RCGR_ADDR, HWIO_LPASS_SLEEP_CMD_RCGR_RMSK)
#define HWIO_LPASS_SLEEP_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SLEEP_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_SLEEP_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SLEEP_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_SLEEP_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SLEEP_CMD_RCGR_ADDR,m,v,HWIO_LPASS_SLEEP_CMD_RCGR_IN)
#define HWIO_LPASS_SLEEP_CMD_RCGR_ROOT_OFF_BMSK                                                                       0x80000000
#define HWIO_LPASS_SLEEP_CMD_RCGR_ROOT_OFF_SHFT                                                                             0x1f
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_D_BMSK                                                                              0x80
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_D_SHFT                                                                               0x7
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_N_BMSK                                                                              0x40
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_N_SHFT                                                                               0x6
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_M_BMSK                                                                              0x20
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_M_SHFT                                                                               0x5
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                       0x10
#define HWIO_LPASS_SLEEP_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                        0x4
#define HWIO_LPASS_SLEEP_CMD_RCGR_ROOT_EN_BMSK                                                                               0x2
#define HWIO_LPASS_SLEEP_CMD_RCGR_ROOT_EN_SHFT                                                                               0x1
#define HWIO_LPASS_SLEEP_CMD_RCGR_UPDATE_BMSK                                                                                0x1
#define HWIO_LPASS_SLEEP_CMD_RCGR_UPDATE_SHFT                                                                                0x0

#define HWIO_LPASS_SLEEP_CFG_RCGR_ADDR                                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001a004)
#define HWIO_LPASS_SLEEP_CFG_RCGR_OFFS                                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001a004)
#define HWIO_LPASS_SLEEP_CFG_RCGR_RMSK                                                                                    0x371f
#define HWIO_LPASS_SLEEP_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SLEEP_CFG_RCGR_ADDR, HWIO_LPASS_SLEEP_CFG_RCGR_RMSK)
#define HWIO_LPASS_SLEEP_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SLEEP_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_SLEEP_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SLEEP_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_SLEEP_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SLEEP_CFG_RCGR_ADDR,m,v,HWIO_LPASS_SLEEP_CFG_RCGR_IN)
#define HWIO_LPASS_SLEEP_CFG_RCGR_MODE_BMSK                                                                               0x3000
#define HWIO_LPASS_SLEEP_CFG_RCGR_MODE_SHFT                                                                                  0xc
#define HWIO_LPASS_SLEEP_CFG_RCGR_SRC_SEL_BMSK                                                                             0x700
#define HWIO_LPASS_SLEEP_CFG_RCGR_SRC_SEL_SHFT                                                                               0x8
#define HWIO_LPASS_SLEEP_CFG_RCGR_SRC_DIV_BMSK                                                                              0x1f
#define HWIO_LPASS_SLEEP_CFG_RCGR_SRC_DIV_SHFT                                                                               0x0

#define HWIO_LPASS_XO_CMD_RCGR_ADDR                                                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001b000)
#define HWIO_LPASS_XO_CMD_RCGR_OFFS                                                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001b000)
#define HWIO_LPASS_XO_CMD_RCGR_RMSK                                                                                   0x800000f3
#define HWIO_LPASS_XO_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_XO_CMD_RCGR_ADDR, HWIO_LPASS_XO_CMD_RCGR_RMSK)
#define HWIO_LPASS_XO_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_XO_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_XO_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_XO_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_XO_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_XO_CMD_RCGR_ADDR,m,v,HWIO_LPASS_XO_CMD_RCGR_IN)
#define HWIO_LPASS_XO_CMD_RCGR_ROOT_OFF_BMSK                                                                          0x80000000
#define HWIO_LPASS_XO_CMD_RCGR_ROOT_OFF_SHFT                                                                                0x1f
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_D_BMSK                                                                                 0x80
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_D_SHFT                                                                                  0x7
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_N_BMSK                                                                                 0x40
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_N_SHFT                                                                                  0x6
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_M_BMSK                                                                                 0x20
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_M_SHFT                                                                                  0x5
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                          0x10
#define HWIO_LPASS_XO_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                           0x4
#define HWIO_LPASS_XO_CMD_RCGR_ROOT_EN_BMSK                                                                                  0x2
#define HWIO_LPASS_XO_CMD_RCGR_ROOT_EN_SHFT                                                                                  0x1
#define HWIO_LPASS_XO_CMD_RCGR_UPDATE_BMSK                                                                                   0x1
#define HWIO_LPASS_XO_CMD_RCGR_UPDATE_SHFT                                                                                   0x0

#define HWIO_LPASS_XO_CFG_RCGR_ADDR                                                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001b004)
#define HWIO_LPASS_XO_CFG_RCGR_OFFS                                                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001b004)
#define HWIO_LPASS_XO_CFG_RCGR_RMSK                                                                                       0x771f
#define HWIO_LPASS_XO_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_XO_CFG_RCGR_ADDR, HWIO_LPASS_XO_CFG_RCGR_RMSK)
#define HWIO_LPASS_XO_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_XO_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_XO_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_XO_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_XO_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_XO_CFG_RCGR_ADDR,m,v,HWIO_LPASS_XO_CFG_RCGR_IN)
#define HWIO_LPASS_XO_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                           0x4000
#define HWIO_LPASS_XO_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                              0xe
#define HWIO_LPASS_XO_CFG_RCGR_MODE_BMSK                                                                                  0x3000
#define HWIO_LPASS_XO_CFG_RCGR_MODE_SHFT                                                                                     0xc
#define HWIO_LPASS_XO_CFG_RCGR_SRC_SEL_BMSK                                                                                0x700
#define HWIO_LPASS_XO_CFG_RCGR_SRC_SEL_SHFT                                                                                  0x8
#define HWIO_LPASS_XO_CFG_RCGR_SRC_DIV_BMSK                                                                                 0x1f
#define HWIO_LPASS_XO_CFG_RCGR_SRC_DIV_SHFT                                                                                  0x0

#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_ADDR                                                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001c000)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_OFFS                                                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001c000)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_RMSK                                                                    0x80000003
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_CLK_OFF_BMSK                                                            0x80000000
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_CLK_OFF_SHFT                                                                  0x1f
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_HW_CTL_BMSK                                                                    0x2
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_HW_CTL_SHFT                                                                    0x1
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_CLK_ENABLE_BMSK                                                                0x1
#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_CLK_ENABLE_SHFT                                                                0x0

#define HWIO_LPASS_CORE_CMD_RCGR_ADDR                                                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001d000)
#define HWIO_LPASS_CORE_CMD_RCGR_OFFS                                                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001d000)
#define HWIO_LPASS_CORE_CMD_RCGR_RMSK                                                                                 0x800000f3
#define HWIO_LPASS_CORE_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_CORE_CMD_RCGR_ADDR, HWIO_LPASS_CORE_CMD_RCGR_RMSK)
#define HWIO_LPASS_CORE_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_CORE_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_CORE_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_CORE_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_CORE_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_CORE_CMD_RCGR_ADDR,m,v,HWIO_LPASS_CORE_CMD_RCGR_IN)
#define HWIO_LPASS_CORE_CMD_RCGR_ROOT_OFF_BMSK                                                                        0x80000000
#define HWIO_LPASS_CORE_CMD_RCGR_ROOT_OFF_SHFT                                                                              0x1f
#define HWIO_LPASS_CORE_CMD_RCGR_DIRTY_D_BMSK                                                                               0x80
#define HWIO_LPASS_CORE_CMD_RCGR_DIRTY_D_SHFT                                                                                0x7
#define HWIO_LPASS_CORE_CMD_RCGR_DIRTY_N_BMSK                                                                               0x40
#define HWIO_LPASS_CORE_CMD_RCGR_DIRTY_N_SHFT                                                                                0x6
#define HWIO_LPASS_CORE_CMD_RCGR_DIRTY_M_BMSK                                                                               0x20
#define HWIO_LPASS_CORE_CMD_RCGR_DIRTY_M_SHFT                                                                                0x5
#define HWIO_LPASS_CORE_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                        0x10
#define HWIO_LPASS_CORE_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                         0x4
#define HWIO_LPASS_CORE_CMD_RCGR_ROOT_EN_BMSK                                                                                0x2
#define HWIO_LPASS_CORE_CMD_RCGR_ROOT_EN_SHFT                                                                                0x1
#define HWIO_LPASS_CORE_CMD_RCGR_UPDATE_BMSK                                                                                 0x1
#define HWIO_LPASS_CORE_CMD_RCGR_UPDATE_SHFT                                                                                 0x0

#define HWIO_LPASS_CORE_CFG_RCGR_ADDR                                                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001d004)
#define HWIO_LPASS_CORE_CFG_RCGR_OFFS                                                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001d004)
#define HWIO_LPASS_CORE_CFG_RCGR_RMSK                                                                                     0x771f
#define HWIO_LPASS_CORE_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_CORE_CFG_RCGR_ADDR, HWIO_LPASS_CORE_CFG_RCGR_RMSK)
#define HWIO_LPASS_CORE_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_CORE_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_CORE_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_CORE_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_CORE_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_CORE_CFG_RCGR_ADDR,m,v,HWIO_LPASS_CORE_CFG_RCGR_IN)
#define HWIO_LPASS_CORE_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                         0x4000
#define HWIO_LPASS_CORE_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                            0xe
#define HWIO_LPASS_CORE_CFG_RCGR_MODE_BMSK                                                                                0x3000
#define HWIO_LPASS_CORE_CFG_RCGR_MODE_SHFT                                                                                   0xc
#define HWIO_LPASS_CORE_CFG_RCGR_SRC_SEL_BMSK                                                                              0x700
#define HWIO_LPASS_CORE_CFG_RCGR_SRC_SEL_SHFT                                                                                0x8
#define HWIO_LPASS_CORE_CFG_RCGR_SRC_DIV_BMSK                                                                               0x1f
#define HWIO_LPASS_CORE_CFG_RCGR_SRC_DIV_SHFT                                                                                0x0

#define HWIO_LPASS_CORE_M_ADDR                                                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001d008)
#define HWIO_LPASS_CORE_M_OFFS                                                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001d008)
#define HWIO_LPASS_CORE_M_RMSK                                                                                              0xff
#define HWIO_LPASS_CORE_M_IN          \
        in_dword_masked(HWIO_LPASS_CORE_M_ADDR, HWIO_LPASS_CORE_M_RMSK)
#define HWIO_LPASS_CORE_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_CORE_M_ADDR, m)
#define HWIO_LPASS_CORE_M_OUT(v)      \
        out_dword(HWIO_LPASS_CORE_M_ADDR,v)
#define HWIO_LPASS_CORE_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_CORE_M_ADDR,m,v,HWIO_LPASS_CORE_M_IN)
#define HWIO_LPASS_CORE_M_M_BMSK                                                                                            0xff
#define HWIO_LPASS_CORE_M_M_SHFT                                                                                             0x0

#define HWIO_LPASS_CORE_N_ADDR                                                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001d00c)
#define HWIO_LPASS_CORE_N_OFFS                                                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001d00c)
#define HWIO_LPASS_CORE_N_RMSK                                                                                              0xff
#define HWIO_LPASS_CORE_N_IN          \
        in_dword_masked(HWIO_LPASS_CORE_N_ADDR, HWIO_LPASS_CORE_N_RMSK)
#define HWIO_LPASS_CORE_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_CORE_N_ADDR, m)
#define HWIO_LPASS_CORE_N_OUT(v)      \
        out_dword(HWIO_LPASS_CORE_N_ADDR,v)
#define HWIO_LPASS_CORE_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_CORE_N_ADDR,m,v,HWIO_LPASS_CORE_N_IN)
#define HWIO_LPASS_CORE_N_NOT_N_MINUS_M_BMSK                                                                                0xff
#define HWIO_LPASS_CORE_N_NOT_N_MINUS_M_SHFT                                                                                 0x0

#define HWIO_LPASS_CORE_D_ADDR                                                                                        (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001d010)
#define HWIO_LPASS_CORE_D_OFFS                                                                                        (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001d010)
#define HWIO_LPASS_CORE_D_RMSK                                                                                              0xff
#define HWIO_LPASS_CORE_D_IN          \
        in_dword_masked(HWIO_LPASS_CORE_D_ADDR, HWIO_LPASS_CORE_D_RMSK)
#define HWIO_LPASS_CORE_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_CORE_D_ADDR, m)
#define HWIO_LPASS_CORE_D_OUT(v)      \
        out_dword(HWIO_LPASS_CORE_D_ADDR,v)
#define HWIO_LPASS_CORE_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_CORE_D_ADDR,m,v,HWIO_LPASS_CORE_D_IN)
#define HWIO_LPASS_CORE_D_NOT_2D_BMSK                                                                                       0xff
#define HWIO_LPASS_CORE_D_NOT_2D_SHFT                                                                                        0x0

#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_ADDR                                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001e000)
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_OFFS                                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001e000)
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_RMSK                                                                      0x80007ff3
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_CLK_OFF_BMSK                                                              0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_CLK_OFF_SHFT                                                                    0x1f
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                                                        0x4000
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                                           0xe
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                                      0x2000
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                         0xd
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                                     0x1000
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                        0xc
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_WAKEUP_BMSK                                                                    0xf00
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_WAKEUP_SHFT                                                                      0x8
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_SLEEP_BMSK                                                                      0xf0
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_SLEEP_SHFT                                                                       0x4
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_HW_CTL_BMSK                                                                      0x2
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_HW_CTL_SHFT                                                                      0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_CLK_ENABLE_BMSK                                                                  0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_CLK_ENABLE_SHFT                                                                  0x0

#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_ADDR                                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001e004)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_OFFS                                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001e004)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_RMSK                                                                 0x80007ff3
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                                                   0x4000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                                      0xe
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                                 0x2000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                    0xd
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                                0x1000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                   0xc
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_WAKEUP_BMSK                                                               0xf00
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_WAKEUP_SHFT                                                                 0x8
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_SLEEP_BMSK                                                                 0xf0
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_SLEEP_SHFT                                                                  0x4
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_HW_CTL_BMSK                                                                 0x2
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_HW_CTL_SHFT                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_ADDR                                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001e008)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_OFFS                                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001e008)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_RMSK                                                                 0x80007ff3
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                                                   0x4000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                                      0xe
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                                 0x2000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                    0xd
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                                0x1000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                   0xc
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_WAKEUP_BMSK                                                               0xf00
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_WAKEUP_SHFT                                                                 0x8
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_SLEEP_BMSK                                                                 0xf0
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_SLEEP_SHFT                                                                  0x4
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_HW_CTL_BMSK                                                                 0x2
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_HW_CTL_SHFT                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_ADDR                                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001e00c)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_OFFS                                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001e00c)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_RMSK                                                                 0x80007ff3
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                                                   0x4000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                                      0xe
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                                 0x2000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                    0xd
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                                0x1000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                   0xc
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_WAKEUP_BMSK                                                               0xf00
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_WAKEUP_SHFT                                                                 0x8
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_SLEEP_BMSK                                                                 0xf0
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_SLEEP_SHFT                                                                  0x4
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_HW_CTL_BMSK                                                                 0x2
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_HW_CTL_SHFT                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_ADDR                                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001e010)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_OFFS                                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001e010)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_RMSK                                                                 0x80007ff3
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                                                   0x4000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                                      0xe
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                                 0x2000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                    0xd
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                                0x1000
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                   0xc
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_WAKEUP_BMSK                                                               0xf00
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_WAKEUP_SHFT                                                                 0x8
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_SLEEP_BMSK                                                                 0xf0
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_SLEEP_SHFT                                                                  0x4
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_HW_CTL_BMSK                                                                 0x2
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_HW_CTL_SHFT                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_ADDR                                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x0001f000)
#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_OFFS                                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0001f000)
#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_RMSK                                                                          0x80000003
#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_CLK_OFF_BMSK                                                                  0x80000000
#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_CLK_OFF_SHFT                                                                        0x1f
#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_HW_CTL_BMSK                                                                          0x2
#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_HW_CTL_SHFT                                                                          0x1
#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_CLK_ENABLE_BMSK                                                                      0x1
#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_CLK_ENABLE_SHFT                                                                      0x0

#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_ADDR                                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00020000)
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_OFFS                                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00020000)
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_RMSK                                                                            0x800000f3
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK0_CMD_RCGR_ADDR, HWIO_LPASS_EXT_MCLK0_CMD_RCGR_RMSK)
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK0_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK0_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK0_CMD_RCGR_ADDR,m,v,HWIO_LPASS_EXT_MCLK0_CMD_RCGR_IN)
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_ROOT_OFF_BMSK                                                                   0x80000000
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_ROOT_OFF_SHFT                                                                         0x1f
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_DIRTY_D_BMSK                                                                          0x80
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_DIRTY_D_SHFT                                                                           0x7
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_DIRTY_N_BMSK                                                                          0x40
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_DIRTY_N_SHFT                                                                           0x6
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_DIRTY_M_BMSK                                                                          0x20
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_DIRTY_M_SHFT                                                                           0x5
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                   0x10
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                    0x4
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_ROOT_EN_BMSK                                                                           0x2
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_ROOT_EN_SHFT                                                                           0x1
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_UPDATE_BMSK                                                                            0x1
#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_UPDATE_SHFT                                                                            0x0

#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_ADDR                                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00020004)
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_OFFS                                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00020004)
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_RMSK                                                                                0x771f
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK0_CFG_RCGR_ADDR, HWIO_LPASS_EXT_MCLK0_CFG_RCGR_RMSK)
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK0_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK0_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK0_CFG_RCGR_ADDR,m,v,HWIO_LPASS_EXT_MCLK0_CFG_RCGR_IN)
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                    0x4000
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                       0xe
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_MODE_BMSK                                                                           0x3000
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_MODE_SHFT                                                                              0xc
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_SRC_SEL_BMSK                                                                         0x700
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_SRC_SEL_SHFT                                                                           0x8
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_SRC_DIV_BMSK                                                                          0x1f
#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_SRC_DIV_SHFT                                                                           0x0

#define HWIO_LPASS_EXT_MCLK0_M_ADDR                                                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00020008)
#define HWIO_LPASS_EXT_MCLK0_M_OFFS                                                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00020008)
#define HWIO_LPASS_EXT_MCLK0_M_RMSK                                                                                         0xff
#define HWIO_LPASS_EXT_MCLK0_M_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK0_M_ADDR, HWIO_LPASS_EXT_MCLK0_M_RMSK)
#define HWIO_LPASS_EXT_MCLK0_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK0_M_ADDR, m)
#define HWIO_LPASS_EXT_MCLK0_M_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK0_M_ADDR,v)
#define HWIO_LPASS_EXT_MCLK0_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK0_M_ADDR,m,v,HWIO_LPASS_EXT_MCLK0_M_IN)
#define HWIO_LPASS_EXT_MCLK0_M_M_BMSK                                                                                       0xff
#define HWIO_LPASS_EXT_MCLK0_M_M_SHFT                                                                                        0x0

#define HWIO_LPASS_EXT_MCLK0_N_ADDR                                                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002000c)
#define HWIO_LPASS_EXT_MCLK0_N_OFFS                                                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002000c)
#define HWIO_LPASS_EXT_MCLK0_N_RMSK                                                                                         0xff
#define HWIO_LPASS_EXT_MCLK0_N_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK0_N_ADDR, HWIO_LPASS_EXT_MCLK0_N_RMSK)
#define HWIO_LPASS_EXT_MCLK0_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK0_N_ADDR, m)
#define HWIO_LPASS_EXT_MCLK0_N_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK0_N_ADDR,v)
#define HWIO_LPASS_EXT_MCLK0_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK0_N_ADDR,m,v,HWIO_LPASS_EXT_MCLK0_N_IN)
#define HWIO_LPASS_EXT_MCLK0_N_NOT_N_MINUS_M_BMSK                                                                           0xff
#define HWIO_LPASS_EXT_MCLK0_N_NOT_N_MINUS_M_SHFT                                                                            0x0

#define HWIO_LPASS_EXT_MCLK0_D_ADDR                                                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00020010)
#define HWIO_LPASS_EXT_MCLK0_D_OFFS                                                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00020010)
#define HWIO_LPASS_EXT_MCLK0_D_RMSK                                                                                         0xff
#define HWIO_LPASS_EXT_MCLK0_D_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK0_D_ADDR, HWIO_LPASS_EXT_MCLK0_D_RMSK)
#define HWIO_LPASS_EXT_MCLK0_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK0_D_ADDR, m)
#define HWIO_LPASS_EXT_MCLK0_D_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK0_D_ADDR,v)
#define HWIO_LPASS_EXT_MCLK0_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK0_D_ADDR,m,v,HWIO_LPASS_EXT_MCLK0_D_IN)
#define HWIO_LPASS_EXT_MCLK0_D_NOT_2D_BMSK                                                                                  0xff
#define HWIO_LPASS_EXT_MCLK0_D_NOT_2D_SHFT                                                                                   0x0

#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_ADDR                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00020014)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_OFFS                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00020014)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_RMSK                                                                  0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_CLK_OFF_BMSK                                                          0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_CLK_OFF_SHFT                                                                0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_HW_CTL_BMSK                                                                  0x2
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_HW_CTL_SHFT                                                                  0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_CLK_ENABLE_BMSK                                                              0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_CLK_ENABLE_SHFT                                                              0x0

#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_ADDR                                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00021000)
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_OFFS                                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00021000)
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_RMSK                                                                            0x800000f3
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK1_CMD_RCGR_ADDR, HWIO_LPASS_EXT_MCLK1_CMD_RCGR_RMSK)
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK1_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK1_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK1_CMD_RCGR_ADDR,m,v,HWIO_LPASS_EXT_MCLK1_CMD_RCGR_IN)
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_ROOT_OFF_BMSK                                                                   0x80000000
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_ROOT_OFF_SHFT                                                                         0x1f
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_DIRTY_D_BMSK                                                                          0x80
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_DIRTY_D_SHFT                                                                           0x7
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_DIRTY_N_BMSK                                                                          0x40
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_DIRTY_N_SHFT                                                                           0x6
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_DIRTY_M_BMSK                                                                          0x20
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_DIRTY_M_SHFT                                                                           0x5
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                   0x10
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                    0x4
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_ROOT_EN_BMSK                                                                           0x2
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_ROOT_EN_SHFT                                                                           0x1
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_UPDATE_BMSK                                                                            0x1
#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_UPDATE_SHFT                                                                            0x0

#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_ADDR                                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00021004)
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_OFFS                                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00021004)
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_RMSK                                                                                0x771f
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK1_CFG_RCGR_ADDR, HWIO_LPASS_EXT_MCLK1_CFG_RCGR_RMSK)
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK1_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK1_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK1_CFG_RCGR_ADDR,m,v,HWIO_LPASS_EXT_MCLK1_CFG_RCGR_IN)
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                    0x4000
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                       0xe
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_MODE_BMSK                                                                           0x3000
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_MODE_SHFT                                                                              0xc
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_SRC_SEL_BMSK                                                                         0x700
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_SRC_SEL_SHFT                                                                           0x8
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_SRC_DIV_BMSK                                                                          0x1f
#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_SRC_DIV_SHFT                                                                           0x0

#define HWIO_LPASS_EXT_MCLK1_M_ADDR                                                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00021008)
#define HWIO_LPASS_EXT_MCLK1_M_OFFS                                                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00021008)
#define HWIO_LPASS_EXT_MCLK1_M_RMSK                                                                                         0xff
#define HWIO_LPASS_EXT_MCLK1_M_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK1_M_ADDR, HWIO_LPASS_EXT_MCLK1_M_RMSK)
#define HWIO_LPASS_EXT_MCLK1_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK1_M_ADDR, m)
#define HWIO_LPASS_EXT_MCLK1_M_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK1_M_ADDR,v)
#define HWIO_LPASS_EXT_MCLK1_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK1_M_ADDR,m,v,HWIO_LPASS_EXT_MCLK1_M_IN)
#define HWIO_LPASS_EXT_MCLK1_M_M_BMSK                                                                                       0xff
#define HWIO_LPASS_EXT_MCLK1_M_M_SHFT                                                                                        0x0

#define HWIO_LPASS_EXT_MCLK1_N_ADDR                                                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002100c)
#define HWIO_LPASS_EXT_MCLK1_N_OFFS                                                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002100c)
#define HWIO_LPASS_EXT_MCLK1_N_RMSK                                                                                         0xff
#define HWIO_LPASS_EXT_MCLK1_N_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK1_N_ADDR, HWIO_LPASS_EXT_MCLK1_N_RMSK)
#define HWIO_LPASS_EXT_MCLK1_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK1_N_ADDR, m)
#define HWIO_LPASS_EXT_MCLK1_N_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK1_N_ADDR,v)
#define HWIO_LPASS_EXT_MCLK1_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK1_N_ADDR,m,v,HWIO_LPASS_EXT_MCLK1_N_IN)
#define HWIO_LPASS_EXT_MCLK1_N_NOT_N_MINUS_M_BMSK                                                                           0xff
#define HWIO_LPASS_EXT_MCLK1_N_NOT_N_MINUS_M_SHFT                                                                            0x0

#define HWIO_LPASS_EXT_MCLK1_D_ADDR                                                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00021010)
#define HWIO_LPASS_EXT_MCLK1_D_OFFS                                                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00021010)
#define HWIO_LPASS_EXT_MCLK1_D_RMSK                                                                                         0xff
#define HWIO_LPASS_EXT_MCLK1_D_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK1_D_ADDR, HWIO_LPASS_EXT_MCLK1_D_RMSK)
#define HWIO_LPASS_EXT_MCLK1_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK1_D_ADDR, m)
#define HWIO_LPASS_EXT_MCLK1_D_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK1_D_ADDR,v)
#define HWIO_LPASS_EXT_MCLK1_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK1_D_ADDR,m,v,HWIO_LPASS_EXT_MCLK1_D_IN)
#define HWIO_LPASS_EXT_MCLK1_D_NOT_2D_BMSK                                                                                  0xff
#define HWIO_LPASS_EXT_MCLK1_D_NOT_2D_SHFT                                                                                   0x0

#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_ADDR                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00021014)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_OFFS                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00021014)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_RMSK                                                                  0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_CLK_OFF_BMSK                                                          0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_CLK_OFF_SHFT                                                                0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_HW_CTL_BMSK                                                                  0x2
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_HW_CTL_SHFT                                                                  0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_CLK_ENABLE_BMSK                                                              0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_CLK_ENABLE_SHFT                                                              0x0

#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_ADDR                                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00022000)
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_OFFS                                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00022000)
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_RMSK                                                                            0x800000f3
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK2_CMD_RCGR_ADDR, HWIO_LPASS_EXT_MCLK2_CMD_RCGR_RMSK)
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK2_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK2_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK2_CMD_RCGR_ADDR,m,v,HWIO_LPASS_EXT_MCLK2_CMD_RCGR_IN)
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_ROOT_OFF_BMSK                                                                   0x80000000
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_ROOT_OFF_SHFT                                                                         0x1f
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_DIRTY_D_BMSK                                                                          0x80
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_DIRTY_D_SHFT                                                                           0x7
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_DIRTY_N_BMSK                                                                          0x40
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_DIRTY_N_SHFT                                                                           0x6
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_DIRTY_M_BMSK                                                                          0x20
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_DIRTY_M_SHFT                                                                           0x5
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                   0x10
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                    0x4
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_ROOT_EN_BMSK                                                                           0x2
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_ROOT_EN_SHFT                                                                           0x1
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_UPDATE_BMSK                                                                            0x1
#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_UPDATE_SHFT                                                                            0x0

#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_ADDR                                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00022004)
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_OFFS                                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00022004)
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_RMSK                                                                                0x771f
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK2_CFG_RCGR_ADDR, HWIO_LPASS_EXT_MCLK2_CFG_RCGR_RMSK)
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK2_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK2_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK2_CFG_RCGR_ADDR,m,v,HWIO_LPASS_EXT_MCLK2_CFG_RCGR_IN)
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                    0x4000
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                       0xe
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_MODE_BMSK                                                                           0x3000
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_MODE_SHFT                                                                              0xc
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_SRC_SEL_BMSK                                                                         0x700
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_SRC_SEL_SHFT                                                                           0x8
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_SRC_DIV_BMSK                                                                          0x1f
#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_SRC_DIV_SHFT                                                                           0x0

#define HWIO_LPASS_EXT_MCLK2_M_ADDR                                                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00022008)
#define HWIO_LPASS_EXT_MCLK2_M_OFFS                                                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00022008)
#define HWIO_LPASS_EXT_MCLK2_M_RMSK                                                                                         0xff
#define HWIO_LPASS_EXT_MCLK2_M_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK2_M_ADDR, HWIO_LPASS_EXT_MCLK2_M_RMSK)
#define HWIO_LPASS_EXT_MCLK2_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK2_M_ADDR, m)
#define HWIO_LPASS_EXT_MCLK2_M_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK2_M_ADDR,v)
#define HWIO_LPASS_EXT_MCLK2_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK2_M_ADDR,m,v,HWIO_LPASS_EXT_MCLK2_M_IN)
#define HWIO_LPASS_EXT_MCLK2_M_M_BMSK                                                                                       0xff
#define HWIO_LPASS_EXT_MCLK2_M_M_SHFT                                                                                        0x0

#define HWIO_LPASS_EXT_MCLK2_N_ADDR                                                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002200c)
#define HWIO_LPASS_EXT_MCLK2_N_OFFS                                                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002200c)
#define HWIO_LPASS_EXT_MCLK2_N_RMSK                                                                                         0xff
#define HWIO_LPASS_EXT_MCLK2_N_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK2_N_ADDR, HWIO_LPASS_EXT_MCLK2_N_RMSK)
#define HWIO_LPASS_EXT_MCLK2_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK2_N_ADDR, m)
#define HWIO_LPASS_EXT_MCLK2_N_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK2_N_ADDR,v)
#define HWIO_LPASS_EXT_MCLK2_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK2_N_ADDR,m,v,HWIO_LPASS_EXT_MCLK2_N_IN)
#define HWIO_LPASS_EXT_MCLK2_N_NOT_N_MINUS_M_BMSK                                                                           0xff
#define HWIO_LPASS_EXT_MCLK2_N_NOT_N_MINUS_M_SHFT                                                                            0x0

#define HWIO_LPASS_EXT_MCLK2_D_ADDR                                                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00022010)
#define HWIO_LPASS_EXT_MCLK2_D_OFFS                                                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00022010)
#define HWIO_LPASS_EXT_MCLK2_D_RMSK                                                                                         0xff
#define HWIO_LPASS_EXT_MCLK2_D_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK2_D_ADDR, HWIO_LPASS_EXT_MCLK2_D_RMSK)
#define HWIO_LPASS_EXT_MCLK2_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK2_D_ADDR, m)
#define HWIO_LPASS_EXT_MCLK2_D_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK2_D_ADDR,v)
#define HWIO_LPASS_EXT_MCLK2_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK2_D_ADDR,m,v,HWIO_LPASS_EXT_MCLK2_D_IN)
#define HWIO_LPASS_EXT_MCLK2_D_NOT_2D_BMSK                                                                                  0xff
#define HWIO_LPASS_EXT_MCLK2_D_NOT_2D_SHFT                                                                                   0x0

#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_ADDR                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00022014)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_OFFS                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00022014)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_RMSK                                                                  0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_CLK_OFF_BMSK                                                          0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_CLK_OFF_SHFT                                                                0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_HW_CTL_BMSK                                                                  0x2
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_HW_CTL_SHFT                                                                  0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_CLK_ENABLE_BMSK                                                              0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_CLK_ENABLE_SHFT                                                              0x0

#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_ADDR                                                             (LPASS_LPASS_CC_REG_REG_BASE      + 0x00023000)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_OFFS                                                             (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00023000)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_RMSK                                                             0x80000003
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_CLK_OFF_BMSK                                                     0x80000000
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_CLK_OFF_SHFT                                                           0x1f
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_HW_CTL_BMSK                                                             0x2
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_HW_CTL_SHFT                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_CLK_ENABLE_BMSK                                                         0x1
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_CLK_ENABLE_SHFT                                                         0x0

#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_ADDR                                                              (LPASS_LPASS_CC_REG_REG_BASE      + 0x00024000)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_OFFS                                                              (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00024000)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_RMSK                                                              0x80000003
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_CLK_OFF_BMSK                                                      0x80000000
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_CLK_OFF_SHFT                                                            0x1f
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_HW_CTL_BMSK                                                              0x2
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_HW_CTL_SHFT                                                              0x1
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_CLK_ENABLE_BMSK                                                          0x1
#define HWIO_LPASS_AUDIO_CORE_SYSNOC_SWAY_SNOC_CBCR_CLK_ENABLE_SHFT                                                          0x0

#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_ADDR                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00025000)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_OFFS                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00025000)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_RMSK                                                            0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_CLK_OFF_BMSK                                                    0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_CLK_OFF_SHFT                                                          0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_HW_CTL_BMSK                                                            0x2
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_HW_CTL_SHFT                                                            0x1
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_CLK_ENABLE_BMSK                                                        0x1
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_CLK_ENABLE_SHFT                                                        0x0

#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_ADDR                                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00026000)
#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_OFFS                                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00026000)
#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_RMSK                                                                            0x80000003
#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_Q6SS_AHBM_AON_CBCR_ADDR, HWIO_LPASS_Q6SS_AHBM_AON_CBCR_RMSK)
#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6SS_AHBM_AON_CBCR_ADDR, m)
#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6SS_AHBM_AON_CBCR_ADDR,v)
#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_AHBM_AON_CBCR_ADDR,m,v,HWIO_LPASS_Q6SS_AHBM_AON_CBCR_IN)
#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_CLK_OFF_BMSK                                                                    0x80000000
#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_CLK_OFF_SHFT                                                                          0x1f
#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_HW_CTL_BMSK                                                                            0x2
#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_HW_CTL_SHFT                                                                            0x1
#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_CLK_ENABLE_BMSK                                                                        0x1
#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_CLK_ENABLE_SHFT                                                                        0x0

#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_ADDR                                                   (LPASS_LPASS_CC_REG_REG_BASE      + 0x00027000)
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_OFFS                                                   (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00027000)
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_RMSK                                                   0x80000003
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_CLK_OFF_BMSK                                           0x80000000
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_CLK_OFF_SHFT                                                 0x1f
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_HW_CTL_BMSK                                                   0x2
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_HW_CTL_SHFT                                                   0x1
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_CLK_ENABLE_BMSK                                               0x1
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CLIENT_CORE_CBCR_CLK_ENABLE_SHFT                                               0x0

#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_ADDR                                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x00028000)
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_OFFS                                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00028000)
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_RMSK                                                                 0x80000003
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_HW_CTL_BMSK                                                                 0x2
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_HW_CTL_SHFT                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_ADDR                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x00029000)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_OFFS                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00029000)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_RMSK                                                           0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_CLK_OFF_BMSK                                                   0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_CLK_OFF_SHFT                                                         0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_HW_CTL_BMSK                                                           0x2
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_HW_CTL_SHFT                                                           0x1
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_CLK_ENABLE_BMSK                                                       0x1
#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_SNOC_CBCR_CLK_ENABLE_SHFT                                                       0x0

#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_ADDR                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002a000)
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_OFFS                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002a000)
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_RMSK                                                      0x80000003
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_CLK_OFF_BMSK                                              0x80000000
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_CLK_OFF_SHFT                                                    0x1f
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_HW_CTL_BMSK                                                      0x2
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_HW_CTL_SHFT                                                      0x1
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_CLK_ENABLE_BMSK                                                  0x1
#define HWIO_LPASS_AUDIO_CORE_PERIPHERAL_SMMU_CFG_CNOC_CBCR_CLK_ENABLE_SHFT                                                  0x0

#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_ADDR                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002b000)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_OFFS                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002b000)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_RMSK                                                           0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_CLK_OFF_BMSK                                                   0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_CLK_OFF_SHFT                                                         0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_HW_CTL_BMSK                                                           0x2
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_HW_CTL_SHFT                                                           0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_CLK_ENABLE_BMSK                                                       0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR_CLK_ENABLE_SHFT                                                       0x0

#define HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_ADDR                                                                             (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002d000)
#define HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_OFFS                                                                             (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002d000)
#define HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_RMSK                                                                             0x80000003
#define HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_ADDR, HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_RMSK)
#define HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_ADDR, m)
#define HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_ADDR,v)
#define HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_ADDR,m,v,HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_IN)
#define HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_CLK_OFF_BMSK                                                                     0x80000000
#define HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_CLK_OFF_SHFT                                                                           0x1f
#define HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_HW_CTL_BMSK                                                                             0x2
#define HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_HW_CTL_SHFT                                                                             0x1
#define HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_CLK_ENABLE_BMSK                                                                         0x1
#define HWIO_LPASS_Q6SS_Q6_AXIM_CBCR_CLK_ENABLE_SHFT                                                                         0x0

#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_ADDR                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002e000)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_OFFS                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002e000)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_RMSK                                                                0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_CLK_OFF_BMSK                                                        0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_CLK_OFF_SHFT                                                              0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_HW_CTL_BMSK                                                                0x2
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_HW_CTL_SHFT                                                                0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_CLK_ENABLE_BMSK                                                            0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_CBCR_CLK_ENABLE_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_GCC_CLK_OFF_STATUS_ADDR                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002e004)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_GCC_CLK_OFF_STATUS_OFFS                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002e004)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_GCC_CLK_OFF_STATUS_RMSK                                                         0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_GCC_CLK_OFF_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_GCC_CLK_OFF_STATUS_ADDR, HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_GCC_CLK_OFF_STATUS_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_GCC_CLK_OFF_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_GCC_CLK_OFF_STATUS_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_GCC_CLK_OFF_STATUS_CLK_OFF_BMSK                                                 0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_AXI_GCC_CLK_OFF_STATUS_CLK_OFF_SHFT                                                 0x0

#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_ADDR                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x0002f000)
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_OFFS                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0002f000)
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_RMSK                                                            0x80000003
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_ADDR, HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_RMSK)
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_ADDR, m)
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_ADDR,v)
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_ADDR,m,v,HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_IN)
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_CLK_OFF_BMSK                                                    0x80000000
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_CLK_OFF_SHFT                                                          0x1f
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_HW_CTL_BMSK                                                            0x2
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_HW_CTL_SHFT                                                            0x1
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_CLK_ENABLE_BMSK                                                        0x1
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_0_CBCR_CLK_ENABLE_SHFT                                                        0x0

#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_ADDR                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00030000)
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_OFFS                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00030000)
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_RMSK                                                            0x80000003
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_ADDR, HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_RMSK)
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_ADDR, m)
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_ADDR,v)
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_ADDR,m,v,HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_IN)
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_CLK_OFF_BMSK                                                    0x80000000
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_CLK_OFF_SHFT                                                          0x1f
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_HW_CTL_BMSK                                                            0x2
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_HW_CTL_SHFT                                                            0x1
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_CLK_ENABLE_BMSK                                                        0x1
#define HWIO_LPASS_Q6SS_Q6_CAMSS_DSP_STREAMING_1_CBCR_CLK_ENABLE_SHFT                                                        0x0

#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_ADDR                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00031000)
#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_OFFS                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00031000)
#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_RMSK                                                                0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_CLK_OFF_BMSK                                                        0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_CLK_OFF_SHFT                                                              0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_HW_CTL_BMSK                                                                0x2
#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_HW_CTL_SHFT                                                                0x1
#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_CLK_ENABLE_BMSK                                                            0x1
#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_CLK_ENABLE_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_ADDR                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00032000)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_OFFS                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00032000)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_RMSK                                                            0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_CLK_OFF_BMSK                                                    0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_CLK_OFF_SHFT                                                          0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_HW_CTL_BMSK                                                            0x2
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_HW_CTL_SHFT                                                            0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_CLK_ENABLE_BMSK                                                        0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_CLK_ENABLE_SHFT                                                        0x0

#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_ADDR                                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00033000)
#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_OFFS                                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00033000)
#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_RMSK                                                                            0x80000003
#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_Q6SS_AHBS_AON_CBCR_ADDR, HWIO_LPASS_Q6SS_AHBS_AON_CBCR_RMSK)
#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6SS_AHBS_AON_CBCR_ADDR, m)
#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6SS_AHBS_AON_CBCR_ADDR,v)
#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6SS_AHBS_AON_CBCR_ADDR,m,v,HWIO_LPASS_Q6SS_AHBS_AON_CBCR_IN)
#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_CLK_OFF_BMSK                                                                    0x80000000
#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_CLK_OFF_SHFT                                                                          0x1f
#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_HW_CTL_BMSK                                                                            0x2
#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_HW_CTL_SHFT                                                                            0x1
#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_CLK_ENABLE_BMSK                                                                        0x1
#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_CLK_ENABLE_SHFT                                                                        0x0

#define HWIO_LPASS_DFS_HW_CTL_ADDR                                                                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x00034000)
#define HWIO_LPASS_DFS_HW_CTL_OFFS                                                                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00034000)
#define HWIO_LPASS_DFS_HW_CTL_RMSK                                                                                    0x70000071
#define HWIO_LPASS_DFS_HW_CTL_IN          \
        in_dword_masked(HWIO_LPASS_DFS_HW_CTL_ADDR, HWIO_LPASS_DFS_HW_CTL_RMSK)
#define HWIO_LPASS_DFS_HW_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_HW_CTL_ADDR, m)
#define HWIO_LPASS_DFS_HW_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_HW_CTL_ADDR,v)
#define HWIO_LPASS_DFS_HW_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_HW_CTL_ADDR,m,v,HWIO_LPASS_DFS_HW_CTL_IN)
#define HWIO_LPASS_DFS_HW_CTL_DFS_PERF_STATE_OUT_BMSK                                                                 0x70000000
#define HWIO_LPASS_DFS_HW_CTL_DFS_PERF_STATE_OUT_SHFT                                                                       0x1c
#define HWIO_LPASS_DFS_HW_CTL_DFS_PERF_STATE_BMSK                                                                           0x70
#define HWIO_LPASS_DFS_HW_CTL_DFS_PERF_STATE_SHFT                                                                            0x4
#define HWIO_LPASS_DFS_HW_CTL_DFS_HW_CTL_EN_BMSK                                                                             0x1
#define HWIO_LPASS_DFS_HW_CTL_DFS_HW_CTL_EN_SHFT                                                                             0x0

#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_ADDR                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00034004)
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_OFFS                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00034004)
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_RMSK                                                                              0x777
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_ADDR, HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_RMSK)
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_ADDR, m)
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_ADDR,v)
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_ADDR,m,v,HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_IN)
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_PERF0_RESAMPLER_RCG_SRC_SEL_BMSK                                                  0x700
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_PERF0_RESAMPLER_RCG_SRC_SEL_SHFT                                                    0x8
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_PERF0_CORE_RCG_SRC_SEL_BMSK                                                        0x70
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_PERF0_CORE_RCG_SRC_SEL_SHFT                                                         0x4
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_PERF0_AON_RCG_SRC_SEL_BMSK                                                          0x7
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_PERF0_AON_RCG_SRC_SEL_SHFT                                                          0x0

#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_ADDR                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00034008)
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_OFFS                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00034008)
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_RMSK                                                                              0x777
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_ADDR, HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_RMSK)
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_ADDR, m)
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_ADDR,v)
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_ADDR,m,v,HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_IN)
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_PERF1_RESAMPLER_RCG_SRC_SEL_BMSK                                                  0x700
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_PERF1_RESAMPLER_RCG_SRC_SEL_SHFT                                                    0x8
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_PERF1_CORE_RCG_SRC_SEL_BMSK                                                        0x70
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_PERF1_CORE_RCG_SRC_SEL_SHFT                                                         0x4
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_PERF1_AON_RCG_SRC_SEL_BMSK                                                          0x7
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_PERF1_AON_RCG_SRC_SEL_SHFT                                                          0x0

#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_ADDR                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003400c)
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_OFFS                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003400c)
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_RMSK                                                                              0x777
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_ADDR, HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_RMSK)
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_ADDR, m)
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_ADDR,v)
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_ADDR,m,v,HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_IN)
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_PERF2_RESAMPLER_RCG_SRC_SEL_BMSK                                                  0x700
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_PERF2_RESAMPLER_RCG_SRC_SEL_SHFT                                                    0x8
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_PERF2_CORE_RCG_SRC_SEL_BMSK                                                        0x70
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_PERF2_CORE_RCG_SRC_SEL_SHFT                                                         0x4
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_PERF2_AON_RCG_SRC_SEL_BMSK                                                          0x7
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_PERF2_AON_RCG_SRC_SEL_SHFT                                                          0x0

#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_ADDR                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00034010)
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_OFFS                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00034010)
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_RMSK                                                                              0x777
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_ADDR, HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_RMSK)
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_ADDR, m)
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_ADDR,v)
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_ADDR,m,v,HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_IN)
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_PERF3_RESAMPLER_RCG_SRC_SEL_BMSK                                                  0x700
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_PERF3_RESAMPLER_RCG_SRC_SEL_SHFT                                                    0x8
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_PERF3_CORE_RCG_SRC_SEL_BMSK                                                        0x70
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_PERF3_CORE_RCG_SRC_SEL_SHFT                                                         0x4
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_PERF3_AON_RCG_SRC_SEL_BMSK                                                          0x7
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_PERF3_AON_RCG_SRC_SEL_SHFT                                                          0x0

#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_ADDR                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00034014)
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_OFFS                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00034014)
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_RMSK                                                                              0x777
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_ADDR, HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_RMSK)
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_ADDR, m)
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_ADDR,v)
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_ADDR,m,v,HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_IN)
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_PERF4_RESAMPLER_RCG_SRC_SEL_BMSK                                                  0x700
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_PERF4_RESAMPLER_RCG_SRC_SEL_SHFT                                                    0x8
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_PERF4_CORE_RCG_SRC_SEL_BMSK                                                        0x70
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_PERF4_CORE_RCG_SRC_SEL_SHFT                                                         0x4
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_PERF4_AON_RCG_SRC_SEL_BMSK                                                          0x7
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_PERF4_AON_RCG_SRC_SEL_SHFT                                                          0x0

#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_ADDR                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00034018)
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_OFFS                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00034018)
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_RMSK                                                                              0x777
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_ADDR, HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_RMSK)
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_ADDR, m)
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_ADDR,v)
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_ADDR,m,v,HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_IN)
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_PERF5_RESAMPLER_RCG_SRC_SEL_BMSK                                                  0x700
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_PERF5_RESAMPLER_RCG_SRC_SEL_SHFT                                                    0x8
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_PERF5_CORE_RCG_SRC_SEL_BMSK                                                        0x70
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_PERF5_CORE_RCG_SRC_SEL_SHFT                                                         0x4
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_PERF5_AON_RCG_SRC_SEL_BMSK                                                          0x7
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_PERF5_AON_RCG_SRC_SEL_SHFT                                                          0x0

#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_ADDR                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003401c)
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_OFFS                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003401c)
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_RMSK                                                                              0x777
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_ADDR, HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_RMSK)
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_ADDR, m)
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_ADDR,v)
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_ADDR,m,v,HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_IN)
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_PERF6_RESAMPLER_RCG_SRC_SEL_BMSK                                                  0x700
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_PERF6_RESAMPLER_RCG_SRC_SEL_SHFT                                                    0x8
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_PERF6_CORE_RCG_SRC_SEL_BMSK                                                        0x70
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_PERF6_CORE_RCG_SRC_SEL_SHFT                                                         0x4
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_PERF6_AON_RCG_SRC_SEL_BMSK                                                          0x7
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_PERF6_AON_RCG_SRC_SEL_SHFT                                                          0x0

#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_ADDR                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00034020)
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_OFFS                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00034020)
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_RMSK                                                                              0x777
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_ADDR, HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_RMSK)
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_ADDR, m)
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_ADDR,v)
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_ADDR,m,v,HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_IN)
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_PERF7_RESAMPLER_RCG_SRC_SEL_BMSK                                                  0x700
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_PERF7_RESAMPLER_RCG_SRC_SEL_SHFT                                                    0x8
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_PERF7_CORE_RCG_SRC_SEL_BMSK                                                        0x70
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_PERF7_CORE_RCG_SRC_SEL_SHFT                                                         0x4
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_PERF7_AON_RCG_SRC_SEL_BMSK                                                          0x7
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_PERF7_AON_RCG_SRC_SEL_SHFT                                                          0x0

#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_ADDR                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00034024)
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_OFFS                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00034024)
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_RMSK                                                                           0x1f1f1f
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_ADDR, HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_RMSK)
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_ADDR,m,v,HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_IN)
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_PERF0_RESAMPLER_RCG_SRC_DIV_BMSK                                               0x1f0000
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_PERF0_RESAMPLER_RCG_SRC_DIV_SHFT                                                   0x10
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_PERF0_CORE_RCG_SRC_DIV_BMSK                                                      0x1f00
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_PERF0_CORE_RCG_SRC_DIV_SHFT                                                         0x8
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_PERF0_AON_RCG_SRC_DIV_BMSK                                                         0x1f
#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_PERF0_AON_RCG_SRC_DIV_SHFT                                                          0x0

#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_ADDR                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00034028)
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_OFFS                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00034028)
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_RMSK                                                                           0x1f1f1f
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_ADDR, HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_RMSK)
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_ADDR,m,v,HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_IN)
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_PERF1_RESAMPLER_RCG_SRC_DIV_BMSK                                               0x1f0000
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_PERF1_RESAMPLER_RCG_SRC_DIV_SHFT                                                   0x10
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_PERF1_CORE_RCG_SRC_DIV_BMSK                                                      0x1f00
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_PERF1_CORE_RCG_SRC_DIV_SHFT                                                         0x8
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_PERF1_AON_RCG_SRC_DIV_BMSK                                                         0x1f
#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_PERF1_AON_RCG_SRC_DIV_SHFT                                                          0x0

#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_ADDR                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003402c)
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_OFFS                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003402c)
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_RMSK                                                                           0x1f1f1f
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_ADDR, HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_RMSK)
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_ADDR,m,v,HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_IN)
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_PERF2_RESAMPLER_RCG_SRC_DIV_BMSK                                               0x1f0000
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_PERF2_RESAMPLER_RCG_SRC_DIV_SHFT                                                   0x10
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_PERF2_CORE_RCG_SRC_DIV_BMSK                                                      0x1f00
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_PERF2_CORE_RCG_SRC_DIV_SHFT                                                         0x8
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_PERF2_AON_RCG_SRC_DIV_BMSK                                                         0x1f
#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_PERF2_AON_RCG_SRC_DIV_SHFT                                                          0x0

#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_ADDR                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00034030)
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_OFFS                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00034030)
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_RMSK                                                                           0x1f1f1f
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_ADDR, HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_RMSK)
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_ADDR,m,v,HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_IN)
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_PERF3_RESAMPLER_RCG_SRC_DIV_BMSK                                               0x1f0000
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_PERF3_RESAMPLER_RCG_SRC_DIV_SHFT                                                   0x10
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_PERF3_CORE_RCG_SRC_DIV_BMSK                                                      0x1f00
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_PERF3_CORE_RCG_SRC_DIV_SHFT                                                         0x8
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_PERF3_AON_RCG_SRC_DIV_BMSK                                                         0x1f
#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_PERF3_AON_RCG_SRC_DIV_SHFT                                                          0x0

#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_ADDR                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00034034)
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_OFFS                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00034034)
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_RMSK                                                                           0x1f1f1f
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_ADDR, HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_RMSK)
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_ADDR,m,v,HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_IN)
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_PERF4_RESAMPLER_RCG_SRC_DIV_BMSK                                               0x1f0000
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_PERF4_RESAMPLER_RCG_SRC_DIV_SHFT                                                   0x10
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_PERF4_CORE_RCG_SRC_DIV_BMSK                                                      0x1f00
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_PERF4_CORE_RCG_SRC_DIV_SHFT                                                         0x8
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_PERF4_AON_RCG_SRC_DIV_BMSK                                                         0x1f
#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_PERF4_AON_RCG_SRC_DIV_SHFT                                                          0x0

#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_ADDR                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00034038)
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_OFFS                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00034038)
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_RMSK                                                                           0x1f1f1f
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_ADDR, HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_RMSK)
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_ADDR,m,v,HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_IN)
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_PERF5_RESAMPLER_RCG_SRC_DIV_BMSK                                               0x1f0000
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_PERF5_RESAMPLER_RCG_SRC_DIV_SHFT                                                   0x10
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_PERF5_CORE_RCG_SRC_DIV_BMSK                                                      0x1f00
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_PERF5_CORE_RCG_SRC_DIV_SHFT                                                         0x8
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_PERF5_AON_RCG_SRC_DIV_BMSK                                                         0x1f
#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_PERF5_AON_RCG_SRC_DIV_SHFT                                                          0x0

#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_ADDR                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003403c)
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_OFFS                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003403c)
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_RMSK                                                                           0x1f1f1f
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_ADDR, HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_RMSK)
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_ADDR,m,v,HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_IN)
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_PERF6_RESAMPLER_RCG_SRC_DIV_BMSK                                               0x1f0000
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_PERF6_RESAMPLER_RCG_SRC_DIV_SHFT                                                   0x10
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_PERF6_CORE_RCG_SRC_DIV_BMSK                                                      0x1f00
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_PERF6_CORE_RCG_SRC_DIV_SHFT                                                         0x8
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_PERF6_AON_RCG_SRC_DIV_BMSK                                                         0x1f
#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_PERF6_AON_RCG_SRC_DIV_SHFT                                                          0x0

#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_ADDR                                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00034040)
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_OFFS                                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00034040)
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_RMSK                                                                           0x1f1f1f
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_ADDR, HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_RMSK)
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_ADDR,m,v,HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_IN)
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_PERF7_RESAMPLER_RCG_SRC_DIV_BMSK                                               0x1f0000
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_PERF7_RESAMPLER_RCG_SRC_DIV_SHFT                                                   0x10
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_PERF7_CORE_RCG_SRC_DIV_BMSK                                                      0x1f00
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_PERF7_CORE_RCG_SRC_DIV_SHFT                                                         0x8
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_PERF7_AON_RCG_SRC_DIV_BMSK                                                         0x1f
#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_PERF7_AON_RCG_SRC_DIV_SHFT                                                          0x0

#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_ADDR                                                                          (LPASS_LPASS_CC_REG_REG_BASE      + 0x00034044)
#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_OFFS                                                                          (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00034044)
#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_RMSK                                                                                 0x7
#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_IN          \
        in_dword_masked(HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_ADDR, HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_RMSK)
#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_ADDR, m)
#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_ADDR,v)
#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_ADDR,m,v,HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_IN)
#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_RESAMPLER_RCG_ASYNC_CLK_EN_BMSK                                                      0x4
#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_RESAMPLER_RCG_ASYNC_CLK_EN_SHFT                                                      0x2
#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_CORE_RCG_ASYNC_CLK_EN_BMSK                                                           0x2
#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_CORE_RCG_ASYNC_CLK_EN_SHFT                                                           0x1
#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_AON_RCG_ASYNC_CLK_EN_BMSK                                                            0x1
#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_AON_RCG_ASYNC_CLK_EN_SHFT                                                            0x0

#define HWIO_LPASS_DFS_PERF0_CDIV_ADDR                                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00034048)
#define HWIO_LPASS_DFS_PERF0_CDIV_OFFS                                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00034048)
#define HWIO_LPASS_DFS_PERF0_CDIV_RMSK                                                                                      0x33
#define HWIO_LPASS_DFS_PERF0_CDIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF0_CDIV_ADDR, HWIO_LPASS_DFS_PERF0_CDIV_RMSK)
#define HWIO_LPASS_DFS_PERF0_CDIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF0_CDIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF0_CDIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF0_CDIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF0_CDIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF0_CDIV_ADDR,m,v,HWIO_LPASS_DFS_PERF0_CDIV_IN)
#define HWIO_LPASS_DFS_PERF0_CDIV_PERF0_LPAAUDIO_PLL_MAIN_SVS_CDIV_BMSK                                                     0x30
#define HWIO_LPASS_DFS_PERF0_CDIV_PERF0_LPAAUDIO_PLL_MAIN_SVS_CDIV_SHFT                                                      0x4
#define HWIO_LPASS_DFS_PERF0_CDIV_PERF0_LPAAUDIO_DIG_PLL_MAIN_SVS_CDIV_BMSK                                                  0x3
#define HWIO_LPASS_DFS_PERF0_CDIV_PERF0_LPAAUDIO_DIG_PLL_MAIN_SVS_CDIV_SHFT                                                  0x0

#define HWIO_LPASS_DFS_PERF1_CDIV_ADDR                                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003404c)
#define HWIO_LPASS_DFS_PERF1_CDIV_OFFS                                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003404c)
#define HWIO_LPASS_DFS_PERF1_CDIV_RMSK                                                                                      0x33
#define HWIO_LPASS_DFS_PERF1_CDIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF1_CDIV_ADDR, HWIO_LPASS_DFS_PERF1_CDIV_RMSK)
#define HWIO_LPASS_DFS_PERF1_CDIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF1_CDIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF1_CDIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF1_CDIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF1_CDIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF1_CDIV_ADDR,m,v,HWIO_LPASS_DFS_PERF1_CDIV_IN)
#define HWIO_LPASS_DFS_PERF1_CDIV_PERF1_LPAAUDIO_PLL_MAIN_SVS_CDIV_BMSK                                                     0x30
#define HWIO_LPASS_DFS_PERF1_CDIV_PERF1_LPAAUDIO_PLL_MAIN_SVS_CDIV_SHFT                                                      0x4
#define HWIO_LPASS_DFS_PERF1_CDIV_PERF1_LPAAUDIO_DIG_PLL_MAIN_SVS_CDIV_BMSK                                                  0x3
#define HWIO_LPASS_DFS_PERF1_CDIV_PERF1_LPAAUDIO_DIG_PLL_MAIN_SVS_CDIV_SHFT                                                  0x0

#define HWIO_LPASS_DFS_PERF2_CDIV_ADDR                                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00034050)
#define HWIO_LPASS_DFS_PERF2_CDIV_OFFS                                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00034050)
#define HWIO_LPASS_DFS_PERF2_CDIV_RMSK                                                                                      0x33
#define HWIO_LPASS_DFS_PERF2_CDIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF2_CDIV_ADDR, HWIO_LPASS_DFS_PERF2_CDIV_RMSK)
#define HWIO_LPASS_DFS_PERF2_CDIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF2_CDIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF2_CDIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF2_CDIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF2_CDIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF2_CDIV_ADDR,m,v,HWIO_LPASS_DFS_PERF2_CDIV_IN)
#define HWIO_LPASS_DFS_PERF2_CDIV_PERF2_LPAAUDIO_PLL_MAIN_SVS_CDIV_BMSK                                                     0x30
#define HWIO_LPASS_DFS_PERF2_CDIV_PERF2_LPAAUDIO_PLL_MAIN_SVS_CDIV_SHFT                                                      0x4
#define HWIO_LPASS_DFS_PERF2_CDIV_PERF2_LPAAUDIO_DIG_PLL_MAIN_SVS_CDIV_BMSK                                                  0x3
#define HWIO_LPASS_DFS_PERF2_CDIV_PERF2_LPAAUDIO_DIG_PLL_MAIN_SVS_CDIV_SHFT                                                  0x0

#define HWIO_LPASS_DFS_PERF3_CDIV_ADDR                                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00034054)
#define HWIO_LPASS_DFS_PERF3_CDIV_OFFS                                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00034054)
#define HWIO_LPASS_DFS_PERF3_CDIV_RMSK                                                                                      0x33
#define HWIO_LPASS_DFS_PERF3_CDIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF3_CDIV_ADDR, HWIO_LPASS_DFS_PERF3_CDIV_RMSK)
#define HWIO_LPASS_DFS_PERF3_CDIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF3_CDIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF3_CDIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF3_CDIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF3_CDIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF3_CDIV_ADDR,m,v,HWIO_LPASS_DFS_PERF3_CDIV_IN)
#define HWIO_LPASS_DFS_PERF3_CDIV_PERF3_LPAAUDIO_PLL_MAIN_SVS_CDIV_BMSK                                                     0x30
#define HWIO_LPASS_DFS_PERF3_CDIV_PERF3_LPAAUDIO_PLL_MAIN_SVS_CDIV_SHFT                                                      0x4
#define HWIO_LPASS_DFS_PERF3_CDIV_PERF3_LPAAUDIO_DIG_PLL_MAIN_SVS_CDIV_BMSK                                                  0x3
#define HWIO_LPASS_DFS_PERF3_CDIV_PERF3_LPAAUDIO_DIG_PLL_MAIN_SVS_CDIV_SHFT                                                  0x0

#define HWIO_LPASS_DFS_PERF4_CDIV_ADDR                                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00034058)
#define HWIO_LPASS_DFS_PERF4_CDIV_OFFS                                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00034058)
#define HWIO_LPASS_DFS_PERF4_CDIV_RMSK                                                                                      0x33
#define HWIO_LPASS_DFS_PERF4_CDIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF4_CDIV_ADDR, HWIO_LPASS_DFS_PERF4_CDIV_RMSK)
#define HWIO_LPASS_DFS_PERF4_CDIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF4_CDIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF4_CDIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF4_CDIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF4_CDIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF4_CDIV_ADDR,m,v,HWIO_LPASS_DFS_PERF4_CDIV_IN)
#define HWIO_LPASS_DFS_PERF4_CDIV_PERF4_LPAAUDIO_PLL_MAIN_SVS_CDIV_BMSK                                                     0x30
#define HWIO_LPASS_DFS_PERF4_CDIV_PERF4_LPAAUDIO_PLL_MAIN_SVS_CDIV_SHFT                                                      0x4
#define HWIO_LPASS_DFS_PERF4_CDIV_PERF4_LPAAUDIO_DIG_PLL_MAIN_SVS_CDIV_BMSK                                                  0x3
#define HWIO_LPASS_DFS_PERF4_CDIV_PERF4_LPAAUDIO_DIG_PLL_MAIN_SVS_CDIV_SHFT                                                  0x0

#define HWIO_LPASS_DFS_PERF5_CDIV_ADDR                                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003405c)
#define HWIO_LPASS_DFS_PERF5_CDIV_OFFS                                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003405c)
#define HWIO_LPASS_DFS_PERF5_CDIV_RMSK                                                                                      0x33
#define HWIO_LPASS_DFS_PERF5_CDIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF5_CDIV_ADDR, HWIO_LPASS_DFS_PERF5_CDIV_RMSK)
#define HWIO_LPASS_DFS_PERF5_CDIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF5_CDIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF5_CDIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF5_CDIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF5_CDIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF5_CDIV_ADDR,m,v,HWIO_LPASS_DFS_PERF5_CDIV_IN)
#define HWIO_LPASS_DFS_PERF5_CDIV_PERF5_LPAAUDIO_PLL_MAIN_SVS_CDIV_BMSK                                                     0x30
#define HWIO_LPASS_DFS_PERF5_CDIV_PERF5_LPAAUDIO_PLL_MAIN_SVS_CDIV_SHFT                                                      0x4
#define HWIO_LPASS_DFS_PERF5_CDIV_PERF5_LPAAUDIO_DIG_PLL_MAIN_SVS_CDIV_BMSK                                                  0x3
#define HWIO_LPASS_DFS_PERF5_CDIV_PERF5_LPAAUDIO_DIG_PLL_MAIN_SVS_CDIV_SHFT                                                  0x0

#define HWIO_LPASS_DFS_PERF6_CDIV_ADDR                                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00034060)
#define HWIO_LPASS_DFS_PERF6_CDIV_OFFS                                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00034060)
#define HWIO_LPASS_DFS_PERF6_CDIV_RMSK                                                                                      0x33
#define HWIO_LPASS_DFS_PERF6_CDIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF6_CDIV_ADDR, HWIO_LPASS_DFS_PERF6_CDIV_RMSK)
#define HWIO_LPASS_DFS_PERF6_CDIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF6_CDIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF6_CDIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF6_CDIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF6_CDIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF6_CDIV_ADDR,m,v,HWIO_LPASS_DFS_PERF6_CDIV_IN)
#define HWIO_LPASS_DFS_PERF6_CDIV_PERF6_LPAAUDIO_PLL_MAIN_SVS_CDIV_BMSK                                                     0x30
#define HWIO_LPASS_DFS_PERF6_CDIV_PERF6_LPAAUDIO_PLL_MAIN_SVS_CDIV_SHFT                                                      0x4
#define HWIO_LPASS_DFS_PERF6_CDIV_PERF6_LPAAUDIO_DIG_PLL_MAIN_SVS_CDIV_BMSK                                                  0x3
#define HWIO_LPASS_DFS_PERF6_CDIV_PERF6_LPAAUDIO_DIG_PLL_MAIN_SVS_CDIV_SHFT                                                  0x0

#define HWIO_LPASS_DFS_PERF7_CDIV_ADDR                                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00034064)
#define HWIO_LPASS_DFS_PERF7_CDIV_OFFS                                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00034064)
#define HWIO_LPASS_DFS_PERF7_CDIV_RMSK                                                                                      0x33
#define HWIO_LPASS_DFS_PERF7_CDIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF7_CDIV_ADDR, HWIO_LPASS_DFS_PERF7_CDIV_RMSK)
#define HWIO_LPASS_DFS_PERF7_CDIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF7_CDIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF7_CDIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF7_CDIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF7_CDIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF7_CDIV_ADDR,m,v,HWIO_LPASS_DFS_PERF7_CDIV_IN)
#define HWIO_LPASS_DFS_PERF7_CDIV_PERF7_LPAAUDIO_PLL_MAIN_SVS_CDIV_BMSK                                                     0x30
#define HWIO_LPASS_DFS_PERF7_CDIV_PERF7_LPAAUDIO_PLL_MAIN_SVS_CDIV_SHFT                                                      0x4
#define HWIO_LPASS_DFS_PERF7_CDIV_PERF7_LPAAUDIO_DIG_PLL_MAIN_SVS_CDIV_BMSK                                                  0x3
#define HWIO_LPASS_DFS_PERF7_CDIV_PERF7_LPAAUDIO_DIG_PLL_MAIN_SVS_CDIV_SHFT                                                  0x0

#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ADDR                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00035000)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_OFFS                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00035000)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_RMSK                                                                0x800000f3
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ADDR, HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_RMSK)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ADDR,m,v,HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_IN)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ROOT_OFF_BMSK                                                       0x80000000
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ROOT_OFF_SHFT                                                             0x1f
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_DIRTY_D_BMSK                                                              0x80
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_DIRTY_D_SHFT                                                               0x7
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_DIRTY_N_BMSK                                                              0x40
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_DIRTY_N_SHFT                                                               0x6
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_DIRTY_M_BMSK                                                              0x20
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_DIRTY_M_SHFT                                                               0x5
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                       0x10
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                        0x4
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ROOT_EN_BMSK                                                               0x2
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ROOT_EN_SHFT                                                               0x1
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_UPDATE_BMSK                                                                0x1
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_UPDATE_SHFT                                                                0x0

#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_ADDR                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00035004)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_OFFS                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00035004)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_RMSK                                                                    0x771f
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_ADDR, HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_RMSK)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_ADDR,m,v,HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_IN)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_ALT_SRC_SEL_BMSK                                                        0x4000
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_ALT_SRC_SEL_SHFT                                                           0xe
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_MODE_BMSK                                                               0x3000
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_MODE_SHFT                                                                  0xc
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_SRC_SEL_BMSK                                                             0x700
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_SRC_SEL_SHFT                                                               0x8
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_SRC_DIV_BMSK                                                              0x1f
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_SRC_DIV_SHFT                                                               0x0

#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_ADDR                                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00035008)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_OFFS                                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00035008)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_RMSK                                                                             0xff
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_IN          \
        in_dword_masked(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_ADDR, HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_RMSK)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_ADDR, m)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_ADDR,v)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_ADDR,m,v,HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_IN)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_M_BMSK                                                                           0xff
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_M_SHFT                                                                            0x0

#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_ADDR                                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003500c)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_OFFS                                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003500c)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_RMSK                                                                             0xff
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_IN          \
        in_dword_masked(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_ADDR, HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_RMSK)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_ADDR, m)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_ADDR,v)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_ADDR,m,v,HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_IN)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_NOT_N_MINUS_M_BMSK                                                               0xff
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_NOT_N_MINUS_M_SHFT                                                                0x0

#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_ADDR                                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00035010)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_OFFS                                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00035010)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_RMSK                                                                             0xff
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_IN          \
        in_dword_masked(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_ADDR, HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_RMSK)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_ADDR, m)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_ADDR,v)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_ADDR,m,v,HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_IN)
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_NOT_2D_BMSK                                                                      0xff
#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_NOT_2D_SHFT                                                                       0x0

#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_ADDR                                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x00035014)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_OFFS                                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00035014)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_RMSK                                                               0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_CLK_OFF_BMSK                                                       0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_CLK_OFF_SHFT                                                             0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_HW_CTL_BMSK                                                               0x2
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_HW_CTL_SHFT                                                               0x1
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_CLK_ENABLE_BMSK                                                           0x1
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_CLK_ENABLE_SHFT                                                           0x0

#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_ADDR                                                         (LPASS_LPASS_CC_REG_REG_BASE      + 0x00035018)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_OFFS                                                         (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00035018)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_RMSK                                                         0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_CLK_OFF_BMSK                                                 0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_CLK_OFF_SHFT                                                       0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_HW_CTL_BMSK                                                         0x2
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_HW_CTL_SHFT                                                         0x1
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_CLK_ENABLE_BMSK                                                     0x1
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_CLK_ENABLE_SHFT                                                     0x0

#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR                                             (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003501c)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_OFFS                                             (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003501c)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_RMSK                                             0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_CLK_OFF_BMSK                                     0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_CLK_OFF_SHFT                                           0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_HW_CTL_BMSK                                             0x2
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_HW_CTL_SHFT                                             0x1
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_CLK_ENABLE_BMSK                                         0x1
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_CLK_ENABLE_SHFT                                         0x0

#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_ADDR                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x00035020)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_OFFS                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00035020)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_RMSK                                               0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_CLK_OFF_BMSK                                       0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_CLK_OFF_SHFT                                             0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_HW_CTL_BMSK                                               0x2
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_HW_CTL_SHFT                                               0x1
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_CLK_ENABLE_BMSK                                           0x1
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_CLK_ENABLE_SHFT                                           0x0

#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00036000)
#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_OFFS                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00036000)
#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_RMSK                                                0x80000003
#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_CLK_OFF_BMSK                                        0x80000000
#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_CLK_OFF_SHFT                                              0x1f
#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_HW_CTL_BMSK                                                0x2
#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_HW_CTL_SHFT                                                0x1
#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_CLK_ENABLE_BMSK                                            0x1
#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_CLK_ENABLE_SHFT                                            0x0

#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR                                                 (LPASS_LPASS_CC_REG_REG_BASE      + 0x00037000)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_OFFS                                                 (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00037000)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_RMSK                                                 0x80000003
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR, HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_RMSK)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_IN)
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_BMSK                                  0x80000000
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_SHFT                                        0x1f
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_IRQ_EN_APPS_BMSK                             0x2
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_IRQ_EN_APPS_SHFT                             0x1
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_IRQ_EN_Q6_BMSK                               0x1
#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_IRQ_EN_Q6_SHFT                               0x0

#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_ADDR                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00037004)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_OFFS                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00037004)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_RMSK                                                             0x3
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_IN          \
        in_dword_masked(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_ADDR, HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_RMSK)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_INM(m)      \
        in_dword_masked(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_ADDR, m)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_OUT(v)      \
        out_dword(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_ADDR,v)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_ADDR,m,v,HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_IN)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_BMSK                      0x2
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_SHFT                      0x1
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_LPASS_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_BMSK                   0x1
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_LPASS_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_SHFT                   0x0

#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_ADDR                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00037008)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_OFFS                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00037008)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_RMSK                                                             0x3
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_IN          \
        in_dword_masked(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_ADDR, HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_RMSK)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_INM(m)      \
        in_dword_masked(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_ADDR, m)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_OUT(v)      \
        out_dword(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_ADDR,v)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_ADDR,m,v,HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_IN)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_Q6_SMMU_SEQUENCE_ABORT_IRQ_EN_BMSK                               0x2
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_Q6_SMMU_SEQUENCE_ABORT_IRQ_EN_SHFT                               0x1
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_LPASS_CORE_SEQUENCE_ABORT_IRQ_EN_BMSK                            0x1
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_LPASS_CORE_SEQUENCE_ABORT_IRQ_EN_SHFT                            0x0

#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x00038000)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_OFFS                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00038000)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_RMSK                                      0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR, HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_BMSK                       0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_SHFT                             0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_IRQ_EN_APPS_BMSK                  0x2
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_IRQ_EN_APPS_SHFT                  0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_IRQ_EN_Q6_BMSK                    0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_SEQUENCE_ABORT_IRQ_EN_Q6_SHFT                    0x0

#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_ADDR                                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x00038004)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_OFFS                                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00038004)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_RMSK                                                           0x3
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_IN          \
        in_dword_masked(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_ADDR, HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_RMSK)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_INM(m)      \
        in_dword_masked(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_ADDR, m)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_OUT(v)      \
        out_dword(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_ADDR,v)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_ADDR,m,v,HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_IN)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_BMSK                    0x2
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_SHFT                    0x1
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_LPASS_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_BMSK                 0x1
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_LPASS_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_SHFT                 0x0

#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_ADDR                                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x00038008)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_OFFS                                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00038008)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_RMSK                                                           0x3
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_IN          \
        in_dword_masked(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_ADDR, HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_RMSK)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_INM(m)      \
        in_dword_masked(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_ADDR, m)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_OUT(v)      \
        out_dword(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_ADDR,v)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_ADDR,m,v,HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_IN)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_Q6_SMMU_SEQUENCE_ABORT_IRQ_EN_BMSK                             0x2
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_Q6_SMMU_SEQUENCE_ABORT_IRQ_EN_SHFT                             0x1
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_LPASS_CORE_SEQUENCE_ABORT_IRQ_EN_BMSK                          0x1
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_LPASS_CORE_SEQUENCE_ABORT_IRQ_EN_SHFT                          0x0

#define HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_ADDR                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00039000)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_OFFS                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00039000)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_RMSK                                                       0x80000001
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_ADDR, HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_Q6_SMMU_PWR_ON_BMSK                                        0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_Q6_SMMU_PWR_ON_SHFT                                              0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_Q6_SMMU_SW_COLLAPSE_BMSK                                          0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_Q6_SMMU_SW_COLLAPSE_SHFT                                          0x0

#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_ADDR                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003a000)
#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_OFFS                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003a000)
#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_RMSK                                                            0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_CLK_OFF_BMSK                                                    0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_CLK_OFF_SHFT                                                          0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_HW_CTL_BMSK                                                            0x2
#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_HW_CTL_SHFT                                                            0x1
#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_CLK_ENABLE_BMSK                                                        0x1
#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_CLK_ENABLE_SHFT                                                        0x0

#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_ADDR                                                              (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003b000)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_OFFS                                                              (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003b000)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_RMSK                                                              0x80000003
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_CLK_OFF_BMSK                                                      0x80000000
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_CLK_OFF_SHFT                                                            0x1f
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_HW_CTL_BMSK                                                              0x2
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_HW_CTL_SHFT                                                              0x1
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_CLK_ENABLE_BMSK                                                          0x1
#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_CLK_ENABLE_SHFT                                                          0x0

#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_ADDR                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003c004)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_OFFS                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003c004)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_RMSK                                                             0x3
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_IN          \
        in_dword_masked(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_ADDR, HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_RMSK)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_INM(m)      \
        in_dword_masked(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_ADDR, m)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_OUT(v)      \
        out_dword(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_ADDR,v)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_ADDR,m,v,HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_IN)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_BMSK                      0x2
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_SHFT                      0x1
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_LPASS_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_BMSK                   0x1
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_LPASS_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_SHFT                   0x0

#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_ADDR                                                      (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003c008)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_OFFS                                                      (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003c008)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_RMSK                                                             0x3
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_IN          \
        in_dword_masked(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_ADDR, HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_RMSK)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_INM(m)      \
        in_dword_masked(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_ADDR, m)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_OUT(v)      \
        out_dword(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_ADDR,v)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_ADDR,m,v,HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_IN)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_Q6_SMMU_SEQUENCE_ABORT_IRQ_EN_BMSK                               0x2
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_Q6_SMMU_SEQUENCE_ABORT_IRQ_EN_SHFT                               0x1
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_LPASS_CORE_SEQUENCE_ABORT_IRQ_EN_BMSK                            0x1
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_LPASS_CORE_SEQUENCE_ABORT_IRQ_EN_SHFT                            0x0

#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_ADDR                                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003d004)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_OFFS                                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003d004)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_RMSK                                                            0x3
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_IN          \
        in_dword_masked(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_ADDR, HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_RMSK)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_INM(m)      \
        in_dword_masked(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_ADDR, m)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_OUT(v)      \
        out_dword(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_ADDR,v)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_ADDR,m,v,HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_IN)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_BMSK                     0x2
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_SHFT                     0x1
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_LPASS_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_BMSK                  0x1
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_LPASS_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_SHFT                  0x0

#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_ADDR                                                     (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003d008)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_OFFS                                                     (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003d008)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_RMSK                                                            0x3
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_IN          \
        in_dword_masked(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_ADDR, HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_RMSK)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_INM(m)      \
        in_dword_masked(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_ADDR, m)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_OUT(v)      \
        out_dword(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_ADDR,v)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_ADDR,m,v,HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_IN)
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_Q6_SMMU_SEQUENCE_ABORT_IRQ_EN_BMSK                              0x2
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_Q6_SMMU_SEQUENCE_ABORT_IRQ_EN_SHFT                              0x1
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_LPASS_CORE_SEQUENCE_ABORT_IRQ_EN_BMSK                           0x1
#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_LPASS_CORE_SEQUENCE_ABORT_IRQ_EN_SHFT                           0x0

#define HWIO_LPASS_JBIST_PLL_SRC_SEL_ADDR                                                                             (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003e000)
#define HWIO_LPASS_JBIST_PLL_SRC_SEL_OFFS                                                                             (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003e000)
#define HWIO_LPASS_JBIST_PLL_SRC_SEL_RMSK                                                                                    0x3
#define HWIO_LPASS_JBIST_PLL_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_JBIST_PLL_SRC_SEL_ADDR, HWIO_LPASS_JBIST_PLL_SRC_SEL_RMSK)
#define HWIO_LPASS_JBIST_PLL_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_JBIST_PLL_SRC_SEL_ADDR, m)
#define HWIO_LPASS_JBIST_PLL_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_JBIST_PLL_SRC_SEL_ADDR,v)
#define HWIO_LPASS_JBIST_PLL_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_JBIST_PLL_SRC_SEL_ADDR,m,v,HWIO_LPASS_JBIST_PLL_SRC_SEL_IN)
#define HWIO_LPASS_JBIST_PLL_SRC_SEL_JBIST_PLL_CLK_SRC_SEL_BMSK                                                              0x3
#define HWIO_LPASS_JBIST_PLL_SRC_SEL_JBIST_PLL_CLK_SRC_SEL_SHFT                                                              0x0

#define HWIO_LPASS_JBIST_MODE_ADDR                                                                                    (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003e004)
#define HWIO_LPASS_JBIST_MODE_OFFS                                                                                    (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003e004)
#define HWIO_LPASS_JBIST_MODE_RMSK                                                                                    0xffffffff
#define HWIO_LPASS_JBIST_MODE_IN          \
        in_dword_masked(HWIO_LPASS_JBIST_MODE_ADDR, HWIO_LPASS_JBIST_MODE_RMSK)
#define HWIO_LPASS_JBIST_MODE_INM(m)      \
        in_dword_masked(HWIO_LPASS_JBIST_MODE_ADDR, m)
#define HWIO_LPASS_JBIST_MODE_OUT(v)      \
        out_dword(HWIO_LPASS_JBIST_MODE_ADDR,v)
#define HWIO_LPASS_JBIST_MODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_JBIST_MODE_ADDR,m,v,HWIO_LPASS_JBIST_MODE_IN)
#define HWIO_LPASS_JBIST_MODE_RESERVE_BITS31_4_BMSK                                                                   0xfffffff0
#define HWIO_LPASS_JBIST_MODE_RESERVE_BITS31_4_SHFT                                                                          0x4
#define HWIO_LPASS_JBIST_MODE_START_MEAS_BMSK                                                                                0x8
#define HWIO_LPASS_JBIST_MODE_START_MEAS_SHFT                                                                                0x3
#define HWIO_LPASS_JBIST_MODE_JBIST_TEST_BMSK                                                                                0x4
#define HWIO_LPASS_JBIST_MODE_JBIST_TEST_SHFT                                                                                0x2
#define HWIO_LPASS_JBIST_MODE_RESET_N_BMSK                                                                                   0x2
#define HWIO_LPASS_JBIST_MODE_RESET_N_SHFT                                                                                   0x1
#define HWIO_LPASS_JBIST_MODE_SLEEP_N_BMSK                                                                                   0x1
#define HWIO_LPASS_JBIST_MODE_SLEEP_N_SHFT                                                                                   0x0

#define HWIO_LPASS_JBIST_CONFIG_CTL_ADDR                                                                              (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003e008)
#define HWIO_LPASS_JBIST_CONFIG_CTL_OFFS                                                                              (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003e008)
#define HWIO_LPASS_JBIST_CONFIG_CTL_RMSK                                                                              0xffffffff
#define HWIO_LPASS_JBIST_CONFIG_CTL_IN          \
        in_dword_masked(HWIO_LPASS_JBIST_CONFIG_CTL_ADDR, HWIO_LPASS_JBIST_CONFIG_CTL_RMSK)
#define HWIO_LPASS_JBIST_CONFIG_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_JBIST_CONFIG_CTL_ADDR, m)
#define HWIO_LPASS_JBIST_CONFIG_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_JBIST_CONFIG_CTL_ADDR,v)
#define HWIO_LPASS_JBIST_CONFIG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_JBIST_CONFIG_CTL_ADDR,m,v,HWIO_LPASS_JBIST_CONFIG_CTL_IN)
#define HWIO_LPASS_JBIST_CONFIG_CTL_JBIST_CONFIG_CTL_BMSK                                                             0xffffffff
#define HWIO_LPASS_JBIST_CONFIG_CTL_JBIST_CONFIG_CTL_SHFT                                                                    0x0

#define HWIO_LPASS_JBIST_USER_CTL_ADDR                                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003e00c)
#define HWIO_LPASS_JBIST_USER_CTL_OFFS                                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003e00c)
#define HWIO_LPASS_JBIST_USER_CTL_RMSK                                                                                0xffffffff
#define HWIO_LPASS_JBIST_USER_CTL_IN          \
        in_dword_masked(HWIO_LPASS_JBIST_USER_CTL_ADDR, HWIO_LPASS_JBIST_USER_CTL_RMSK)
#define HWIO_LPASS_JBIST_USER_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_JBIST_USER_CTL_ADDR, m)
#define HWIO_LPASS_JBIST_USER_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_JBIST_USER_CTL_ADDR,v)
#define HWIO_LPASS_JBIST_USER_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_JBIST_USER_CTL_ADDR,m,v,HWIO_LPASS_JBIST_USER_CTL_IN)
#define HWIO_LPASS_JBIST_USER_CTL_JBIST_USER_CTL_BMSK                                                                 0xffffffff
#define HWIO_LPASS_JBIST_USER_CTL_JBIST_USER_CTL_SHFT                                                                        0x0

#define HWIO_LPASS_JBIST_USER_CTL_U_ADDR                                                                              (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003e010)
#define HWIO_LPASS_JBIST_USER_CTL_U_OFFS                                                                              (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003e010)
#define HWIO_LPASS_JBIST_USER_CTL_U_RMSK                                                                              0xffffffff
#define HWIO_LPASS_JBIST_USER_CTL_U_IN          \
        in_dword_masked(HWIO_LPASS_JBIST_USER_CTL_U_ADDR, HWIO_LPASS_JBIST_USER_CTL_U_RMSK)
#define HWIO_LPASS_JBIST_USER_CTL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_JBIST_USER_CTL_U_ADDR, m)
#define HWIO_LPASS_JBIST_USER_CTL_U_OUT(v)      \
        out_dword(HWIO_LPASS_JBIST_USER_CTL_U_ADDR,v)
#define HWIO_LPASS_JBIST_USER_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_JBIST_USER_CTL_U_ADDR,m,v,HWIO_LPASS_JBIST_USER_CTL_U_IN)
#define HWIO_LPASS_JBIST_USER_CTL_U_JBIST_USER_CTL_U_BMSK                                                             0xffffffff
#define HWIO_LPASS_JBIST_USER_CTL_U_JBIST_USER_CTL_U_SHFT                                                                    0x0

#define HWIO_LPASS_JBIST_TEST_CTL_ADDR                                                                                (LPASS_LPASS_CC_REG_REG_BASE      + 0x00003e14)
#define HWIO_LPASS_JBIST_TEST_CTL_OFFS                                                                                (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00003e14)
#define HWIO_LPASS_JBIST_TEST_CTL_RMSK                                                                                0xffffffff
#define HWIO_LPASS_JBIST_TEST_CTL_IN          \
        in_dword_masked(HWIO_LPASS_JBIST_TEST_CTL_ADDR, HWIO_LPASS_JBIST_TEST_CTL_RMSK)
#define HWIO_LPASS_JBIST_TEST_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_JBIST_TEST_CTL_ADDR, m)
#define HWIO_LPASS_JBIST_TEST_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_JBIST_TEST_CTL_ADDR,v)
#define HWIO_LPASS_JBIST_TEST_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_JBIST_TEST_CTL_ADDR,m,v,HWIO_LPASS_JBIST_TEST_CTL_IN)
#define HWIO_LPASS_JBIST_TEST_CTL_JBIST_TEST_CTL_BMSK                                                                 0xffffffff
#define HWIO_LPASS_JBIST_TEST_CTL_JBIST_TEST_CTL_SHFT                                                                        0x0

#define HWIO_LPASS_JBIST_STATUS_ADDR                                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003e018)
#define HWIO_LPASS_JBIST_STATUS_OFFS                                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003e018)
#define HWIO_LPASS_JBIST_STATUS_RMSK                                                                                  0xffffffff
#define HWIO_LPASS_JBIST_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_JBIST_STATUS_ADDR, HWIO_LPASS_JBIST_STATUS_RMSK)
#define HWIO_LPASS_JBIST_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_JBIST_STATUS_ADDR, m)
#define HWIO_LPASS_JBIST_STATUS_JBIST_STATUS_BMSK                                                                     0xffffffff
#define HWIO_LPASS_JBIST_STATUS_JBIST_STATUS_SHFT                                                                            0x0

#define HWIO_LPASS_JBIST_MEAS_DONE_ADDR                                                                               (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003e01c)
#define HWIO_LPASS_JBIST_MEAS_DONE_OFFS                                                                               (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003e01c)
#define HWIO_LPASS_JBIST_MEAS_DONE_RMSK                                                                               0xffffffff
#define HWIO_LPASS_JBIST_MEAS_DONE_IN          \
        in_dword_masked(HWIO_LPASS_JBIST_MEAS_DONE_ADDR, HWIO_LPASS_JBIST_MEAS_DONE_RMSK)
#define HWIO_LPASS_JBIST_MEAS_DONE_INM(m)      \
        in_dword_masked(HWIO_LPASS_JBIST_MEAS_DONE_ADDR, m)
#define HWIO_LPASS_JBIST_MEAS_DONE_OUT(v)      \
        out_dword(HWIO_LPASS_JBIST_MEAS_DONE_ADDR,v)
#define HWIO_LPASS_JBIST_MEAS_DONE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_JBIST_MEAS_DONE_ADDR,m,v,HWIO_LPASS_JBIST_MEAS_DONE_IN)
#define HWIO_LPASS_JBIST_MEAS_DONE_RESERVE_BITS31_1_BMSK                                                              0xfffffffe
#define HWIO_LPASS_JBIST_MEAS_DONE_RESERVE_BITS31_1_SHFT                                                                     0x1
#define HWIO_LPASS_JBIST_MEAS_DONE_JBIST_MEAS_DONE_BMSK                                                                      0x1
#define HWIO_LPASS_JBIST_MEAS_DONE_JBIST_MEAS_DONE_SHFT                                                                      0x0

#define HWIO_LPASS_Q6_SMMU_SPM_CLK_CTL_ADDR                                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x0003f000)
#define HWIO_LPASS_Q6_SMMU_SPM_CLK_CTL_OFFS                                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x0003f000)
#define HWIO_LPASS_Q6_SMMU_SPM_CLK_CTL_RMSK                                                                                  0x1
#define HWIO_LPASS_Q6_SMMU_SPM_CLK_CTL_IN          \
        in_dword_masked(HWIO_LPASS_Q6_SMMU_SPM_CLK_CTL_ADDR, HWIO_LPASS_Q6_SMMU_SPM_CLK_CTL_RMSK)
#define HWIO_LPASS_Q6_SMMU_SPM_CLK_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6_SMMU_SPM_CLK_CTL_ADDR, m)
#define HWIO_LPASS_Q6_SMMU_SPM_CLK_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_Q6_SMMU_SPM_CLK_CTL_ADDR,v)
#define HWIO_LPASS_Q6_SMMU_SPM_CLK_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6_SMMU_SPM_CLK_CTL_ADDR,m,v,HWIO_LPASS_Q6_SMMU_SPM_CLK_CTL_IN)
#define HWIO_LPASS_Q6_SMMU_SPM_CLK_CTL_Q6_SMMU_SPM_COLLAPSE_OR_CLK_GATE_SEL_BMSK                                             0x1
#define HWIO_LPASS_Q6_SMMU_SPM_CLK_CTL_Q6_SMMU_SPM_COLLAPSE_OR_CLK_GATE_SEL_SHFT                                             0x0

#define HWIO_LPASS_DBG_CLK_ADDR                                                                                       (LPASS_LPASS_CC_REG_REG_BASE      + 0x00040000)
#define HWIO_LPASS_DBG_CLK_OFFS                                                                                       (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00040000)
#define HWIO_LPASS_DBG_CLK_RMSK                                                                                       0xfff0ffff
#define HWIO_LPASS_DBG_CLK_IN          \
        in_dword_masked(HWIO_LPASS_DBG_CLK_ADDR, HWIO_LPASS_DBG_CLK_RMSK)
#define HWIO_LPASS_DBG_CLK_INM(m)      \
        in_dword_masked(HWIO_LPASS_DBG_CLK_ADDR, m)
#define HWIO_LPASS_DBG_CLK_OUT(v)      \
        out_dword(HWIO_LPASS_DBG_CLK_ADDR,v)
#define HWIO_LPASS_DBG_CLK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DBG_CLK_ADDR,m,v,HWIO_LPASS_DBG_CLK_IN)
#define HWIO_LPASS_DBG_CLK_RESETN_MUX_SEL_BMSK                                                                        0xe0000000
#define HWIO_LPASS_DBG_CLK_RESETN_MUX_SEL_SHFT                                                                              0x1d
#define HWIO_LPASS_DBG_CLK_BYPASSNL_MUX_SEL_BMSK                                                                      0x1c000000
#define HWIO_LPASS_DBG_CLK_BYPASSNL_MUX_SEL_SHFT                                                                            0x1a
#define HWIO_LPASS_DBG_CLK_RESERVE_BITS25_21_BMSK                                                                      0x3e00000
#define HWIO_LPASS_DBG_CLK_RESERVE_BITS25_21_SHFT                                                                           0x15
#define HWIO_LPASS_DBG_CLK_DBG_CLK_ENABLE_BMSK                                                                          0x100000
#define HWIO_LPASS_DBG_CLK_DBG_CLK_ENABLE_SHFT                                                                              0x14
#define HWIO_LPASS_DBG_CLK_DBG_CLK_MUX_SEL_BMSK                                                                           0xffff
#define HWIO_LPASS_DBG_CLK_DBG_CLK_MUX_SEL_SHFT                                                                              0x0

#define HWIO_LPASS_TEST_BUS_SEL_ADDR                                                                                  (LPASS_LPASS_CC_REG_REG_BASE      + 0x00040004)
#define HWIO_LPASS_TEST_BUS_SEL_OFFS                                                                                  (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00040004)
#define HWIO_LPASS_TEST_BUS_SEL_RMSK                                                                                         0x3
#define HWIO_LPASS_TEST_BUS_SEL_IN          \
        in_dword_masked(HWIO_LPASS_TEST_BUS_SEL_ADDR, HWIO_LPASS_TEST_BUS_SEL_RMSK)
#define HWIO_LPASS_TEST_BUS_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_TEST_BUS_SEL_ADDR, m)
#define HWIO_LPASS_TEST_BUS_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_TEST_BUS_SEL_ADDR,v)
#define HWIO_LPASS_TEST_BUS_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_TEST_BUS_SEL_ADDR,m,v,HWIO_LPASS_TEST_BUS_SEL_IN)
#define HWIO_LPASS_TEST_BUS_SEL_SEL_BMSK                                                                                     0x3
#define HWIO_LPASS_TEST_BUS_SEL_SEL_SHFT                                                                                     0x0

#define HWIO_LPASS_PLLOUT_LV_TEST_SEL_ADDR                                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00041000)
#define HWIO_LPASS_PLLOUT_LV_TEST_SEL_OFFS                                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00041000)
#define HWIO_LPASS_PLLOUT_LV_TEST_SEL_RMSK                                                                                   0x3
#define HWIO_LPASS_PLLOUT_LV_TEST_SEL_IN          \
        in_dword_masked(HWIO_LPASS_PLLOUT_LV_TEST_SEL_ADDR, HWIO_LPASS_PLLOUT_LV_TEST_SEL_RMSK)
#define HWIO_LPASS_PLLOUT_LV_TEST_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_PLLOUT_LV_TEST_SEL_ADDR, m)
#define HWIO_LPASS_PLLOUT_LV_TEST_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_PLLOUT_LV_TEST_SEL_ADDR,v)
#define HWIO_LPASS_PLLOUT_LV_TEST_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_PLLOUT_LV_TEST_SEL_ADDR,m,v,HWIO_LPASS_PLLOUT_LV_TEST_SEL_IN)
#define HWIO_LPASS_PLLOUT_LV_TEST_SEL_SEL_BMSK                                                                               0x3
#define HWIO_LPASS_PLLOUT_LV_TEST_SEL_SEL_SHFT                                                                               0x0

#define HWIO_LPASS_LPASS_CC_SPARE_REG_ADDR                                                                            (LPASS_LPASS_CC_REG_REG_BASE      + 0x00042000)
#define HWIO_LPASS_LPASS_CC_SPARE_REG_OFFS                                                                            (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00042000)
#define HWIO_LPASS_LPASS_CC_SPARE_REG_RMSK                                                                            0xffffffff
#define HWIO_LPASS_LPASS_CC_SPARE_REG_IN          \
        in_dword_masked(HWIO_LPASS_LPASS_CC_SPARE_REG_ADDR, HWIO_LPASS_LPASS_CC_SPARE_REG_RMSK)
#define HWIO_LPASS_LPASS_CC_SPARE_REG_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPASS_CC_SPARE_REG_ADDR, m)
#define HWIO_LPASS_LPASS_CC_SPARE_REG_OUT(v)      \
        out_dword(HWIO_LPASS_LPASS_CC_SPARE_REG_ADDR,v)
#define HWIO_LPASS_LPASS_CC_SPARE_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPASS_CC_SPARE_REG_ADDR,m,v,HWIO_LPASS_LPASS_CC_SPARE_REG_IN)
#define HWIO_LPASS_LPASS_CC_SPARE_REG_SPARE_BMSK                                                                      0xffffffff
#define HWIO_LPASS_LPASS_CC_SPARE_REG_SPARE_SHFT                                                                             0x0

#define HWIO_LPASS_LPASS_CC_SPARE1_REG_ADDR                                                                           (LPASS_LPASS_CC_REG_REG_BASE      + 0x00043000)
#define HWIO_LPASS_LPASS_CC_SPARE1_REG_OFFS                                                                           (LPASS_LPASS_CC_REG_REG_BASE_OFFS + 0x00043000)
#define HWIO_LPASS_LPASS_CC_SPARE1_REG_RMSK                                                                           0xffffffff
#define HWIO_LPASS_LPASS_CC_SPARE1_REG_IN          \
        in_dword_masked(HWIO_LPASS_LPASS_CC_SPARE1_REG_ADDR, HWIO_LPASS_LPASS_CC_SPARE1_REG_RMSK)
#define HWIO_LPASS_LPASS_CC_SPARE1_REG_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPASS_CC_SPARE1_REG_ADDR, m)
#define HWIO_LPASS_LPASS_CC_SPARE1_REG_OUT(v)      \
        out_dword(HWIO_LPASS_LPASS_CC_SPARE1_REG_ADDR,v)
#define HWIO_LPASS_LPASS_CC_SPARE1_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPASS_CC_SPARE1_REG_ADDR,m,v,HWIO_LPASS_LPASS_CC_SPARE1_REG_IN)
#define HWIO_LPASS_LPASS_CC_SPARE1_REG_SPARE1_BMSK                                                                    0xffffffff
#define HWIO_LPASS_LPASS_CC_SPARE1_REG_SPARE1_SHFT                                                                           0x0

/*----------------------------------------------------------------------------
 * MODULE: LPASS_QDSP6V60SS_PUB
 *--------------------------------------------------------------------------*/

#define LPASS_QDSP6V60SS_PUB_REG_BASE                                                 (LPASS_BASE      + 0x00300000)
#define LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS                                            0x00300000

#define HWIO_LPASS_QDSP6SS_VERSION_ADDR                                               (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000000)
#define HWIO_LPASS_QDSP6SS_VERSION_OFFS                                               (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000000)
#define HWIO_LPASS_QDSP6SS_VERSION_RMSK                                               0xffffffff
#define HWIO_LPASS_QDSP6SS_VERSION_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_VERSION_ADDR, HWIO_LPASS_QDSP6SS_VERSION_RMSK)
#define HWIO_LPASS_QDSP6SS_VERSION_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_VERSION_ADDR, m)
#define HWIO_LPASS_QDSP6SS_VERSION_MAJOR_BMSK                                         0xf0000000
#define HWIO_LPASS_QDSP6SS_VERSION_MAJOR_SHFT                                               0x1c
#define HWIO_LPASS_QDSP6SS_VERSION_MINOR_BMSK                                          0xfff0000
#define HWIO_LPASS_QDSP6SS_VERSION_MINOR_SHFT                                               0x10
#define HWIO_LPASS_QDSP6SS_VERSION_STEP_BMSK                                              0xffff
#define HWIO_LPASS_QDSP6SS_VERSION_STEP_SHFT                                                 0x0

#define HWIO_LPASS_QDSP6SS_CONFIG_ID_ADDR                                             (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000004)
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_OFFS                                             (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000004)
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_RMSK                                             0xfff1ffff
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CONFIG_ID_ADDR, HWIO_LPASS_QDSP6SS_CONFIG_ID_RMSK)
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CONFIG_ID_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_NUM_L2VIC_SRC_BMSK                               0xfff00000
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_NUM_L2VIC_SRC_SHFT                                     0x14
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_ZMEAS_PRESENT_BMSK                                  0x10000
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_ZMEAS_PRESENT_SHFT                                     0x10
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_PMIC_IF_PRESENT_BMSK                                 0x8000
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_PMIC_IF_PRESENT_SHFT                                    0xf
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_IN_SUBSYSTEM_BMSK                                    0x7000
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_IN_SUBSYSTEM_SHFT                                       0xc
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_IN_SUBSYSTEM_UNKNOWN_FVAL                               0x0
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_IN_SUBSYSTEM_QDSP6SS_IN_LPASS_FVAL                      0x1
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_IN_SUBSYSTEM_QDSP6SS_IN_SSC_FVAL                        0x2
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_IN_SUBSYSTEM_QDSP6SS_IN_MSS_FVAL                        0x3
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_LDO_PRESENT_BMSK                                      0x800
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_LDO_PRESENT_SHFT                                        0xb
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_BHS_PRESENT_BMSK                                      0x400
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_BHS_PRESENT_SHFT                                        0xa
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_PLL_VOTE_BMSK                                         0x200
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_PLL_VOTE_SHFT                                           0x9
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_PLL_PRESENT_BMSK                                      0x100
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_PLL_PRESENT_SHFT                                        0x8
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_CORE_TYPE_BMSK                                         0xf0
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_CORE_TYPE_SHFT                                          0x4
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_L2_SIZE_BMSK                                            0xf
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_L2_SIZE_SHFT                                            0x0

#define HWIO_LPASS_QDSP6SS_RST_EVB_ADDR                                               (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000010)
#define HWIO_LPASS_QDSP6SS_RST_EVB_OFFS                                               (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000010)
#define HWIO_LPASS_QDSP6SS_RST_EVB_RMSK                                                0xffffff0
#define HWIO_LPASS_QDSP6SS_RST_EVB_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_RST_EVB_ADDR, HWIO_LPASS_QDSP6SS_RST_EVB_RMSK)
#define HWIO_LPASS_QDSP6SS_RST_EVB_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_RST_EVB_ADDR, m)
#define HWIO_LPASS_QDSP6SS_RST_EVB_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_RST_EVB_ADDR,v)
#define HWIO_LPASS_QDSP6SS_RST_EVB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_RST_EVB_ADDR,m,v,HWIO_LPASS_QDSP6SS_RST_EVB_IN)
#define HWIO_LPASS_QDSP6SS_RST_EVB_EVB_BMSK                                            0xffffff0
#define HWIO_LPASS_QDSP6SS_RST_EVB_EVB_SHFT                                                  0x4

#define HWIO_LPASS_QDSP6SS_RESET_ADDR                                                 (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000014)
#define HWIO_LPASS_QDSP6SS_RESET_OFFS                                                 (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000014)
#define HWIO_LPASS_QDSP6SS_RESET_RMSK                                                     0x7ff7
#define HWIO_LPASS_QDSP6SS_RESET_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_RESET_ADDR, HWIO_LPASS_QDSP6SS_RESET_RMSK)
#define HWIO_LPASS_QDSP6SS_RESET_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_RESET_ADDR, m)
#define HWIO_LPASS_QDSP6SS_RESET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_RESET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_RESET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_RESET_ADDR,m,v,HWIO_LPASS_QDSP6SS_RESET_IN)
#define HWIO_LPASS_QDSP6SS_RESET_CSI1_ARES_BMSK                                           0x4000
#define HWIO_LPASS_QDSP6SS_RESET_CSI1_ARES_SHFT                                              0xe
#define HWIO_LPASS_QDSP6SS_RESET_CSI0_ARES_BMSK                                           0x2000
#define HWIO_LPASS_QDSP6SS_RESET_CSI0_ARES_SHFT                                              0xd
#define HWIO_LPASS_QDSP6SS_RESET_CORE_ARCH_ARES_BMSK                                      0x1000
#define HWIO_LPASS_QDSP6SS_RESET_CORE_ARCH_ARES_SHFT                                         0xc
#define HWIO_LPASS_QDSP6SS_RESET_CORE_NONRET_ARES_BMSK                                     0x800
#define HWIO_LPASS_QDSP6SS_RESET_CORE_NONRET_ARES_SHFT                                       0xb
#define HWIO_LPASS_QDSP6SS_RESET_CORE_RET_ARES_BMSK                                        0x400
#define HWIO_LPASS_QDSP6SS_RESET_CORE_RET_ARES_SHFT                                          0xa
#define HWIO_LPASS_QDSP6SS_RESET_AXIM2_ARES_BMSK                                           0x200
#define HWIO_LPASS_QDSP6SS_RESET_AXIM2_ARES_SHFT                                             0x9
#define HWIO_LPASS_QDSP6SS_RESET_AXIS_ARES_BMSK                                            0x100
#define HWIO_LPASS_QDSP6SS_RESET_AXIS_ARES_SHFT                                              0x8
#define HWIO_LPASS_QDSP6SS_RESET_ATBM_ARES_BMSK                                             0x80
#define HWIO_LPASS_QDSP6SS_RESET_ATBM_ARES_SHFT                                              0x7
#define HWIO_LPASS_QDSP6SS_RESET_AHBM_ARES_BMSK                                             0x40
#define HWIO_LPASS_QDSP6SS_RESET_AHBM_ARES_SHFT                                              0x6
#define HWIO_LPASS_QDSP6SS_RESET_AXIM_ARES_BMSK                                             0x20
#define HWIO_LPASS_QDSP6SS_RESET_AXIM_ARES_SHFT                                              0x5
#define HWIO_LPASS_QDSP6SS_RESET_ETM_ISDB_ARES_BMSK                                         0x10
#define HWIO_LPASS_QDSP6SS_RESET_ETM_ISDB_ARES_SHFT                                          0x4
#define HWIO_LPASS_QDSP6SS_RESET_BUS_ARES_ENA_BMSK                                           0x4
#define HWIO_LPASS_QDSP6SS_RESET_BUS_ARES_ENA_SHFT                                           0x2
#define HWIO_LPASS_QDSP6SS_RESET_CORE_ARES_BMSK                                              0x2
#define HWIO_LPASS_QDSP6SS_RESET_CORE_ARES_SHFT                                              0x1
#define HWIO_LPASS_QDSP6SS_RESET_STOP_CORE_BMSK                                              0x1
#define HWIO_LPASS_QDSP6SS_RESET_STOP_CORE_SHFT                                              0x0

#define HWIO_LPASS_QDSP6SS_DBG_CFG_ADDR                                               (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000018)
#define HWIO_LPASS_QDSP6SS_DBG_CFG_OFFS                                               (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000018)
#define HWIO_LPASS_QDSP6SS_DBG_CFG_RMSK                                               0xffff0003
#define HWIO_LPASS_QDSP6SS_DBG_CFG_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_DBG_CFG_ADDR, HWIO_LPASS_QDSP6SS_DBG_CFG_RMSK)
#define HWIO_LPASS_QDSP6SS_DBG_CFG_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_DBG_CFG_ADDR, m)
#define HWIO_LPASS_QDSP6SS_DBG_CFG_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_DBG_CFG_ADDR,v)
#define HWIO_LPASS_QDSP6SS_DBG_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_DBG_CFG_ADDR,m,v,HWIO_LPASS_QDSP6SS_DBG_CFG_IN)
#define HWIO_LPASS_QDSP6SS_DBG_CFG_DBG_SW_REG_BMSK                                    0xff000000
#define HWIO_LPASS_QDSP6SS_DBG_CFG_DBG_SW_REG_SHFT                                          0x18
#define HWIO_LPASS_QDSP6SS_DBG_CFG_DBG_SPARE_BMSK                                       0xff0000
#define HWIO_LPASS_QDSP6SS_DBG_CFG_DBG_SPARE_SHFT                                           0x10
#define HWIO_LPASS_QDSP6SS_DBG_CFG_CTI_TIHS_ENA_BMSK                                         0x2
#define HWIO_LPASS_QDSP6SS_DBG_CFG_CTI_TIHS_ENA_SHFT                                         0x1
#define HWIO_LPASS_QDSP6SS_DBG_CFG_DBG_ARES_ENA_BMSK                                         0x1
#define HWIO_LPASS_QDSP6SS_DBG_CFG_DBG_ARES_ENA_SHFT                                         0x0

#define HWIO_LPASS_QDSP6SS_RET_CFG_ADDR                                               (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x0000001c)
#define HWIO_LPASS_QDSP6SS_RET_CFG_OFFS                                               (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000001c)
#define HWIO_LPASS_QDSP6SS_RET_CFG_RMSK                                                      0x3
#define HWIO_LPASS_QDSP6SS_RET_CFG_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_RET_CFG_ADDR, HWIO_LPASS_QDSP6SS_RET_CFG_RMSK)
#define HWIO_LPASS_QDSP6SS_RET_CFG_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_RET_CFG_ADDR, m)
#define HWIO_LPASS_QDSP6SS_RET_CFG_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_RET_CFG_ADDR,v)
#define HWIO_LPASS_QDSP6SS_RET_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_RET_CFG_ADDR,m,v,HWIO_LPASS_QDSP6SS_RET_CFG_IN)
#define HWIO_LPASS_QDSP6SS_RET_CFG_ARCH_ARES_ENA_BMSK                                        0x2
#define HWIO_LPASS_QDSP6SS_RET_CFG_ARCH_ARES_ENA_SHFT                                        0x1
#define HWIO_LPASS_QDSP6SS_RET_CFG_RET_ARES_ENA_BMSK                                         0x1
#define HWIO_LPASS_QDSP6SS_RET_CFG_RET_ARES_ENA_SHFT                                         0x0

#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_ADDR                                             (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000020)
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_OFFS                                             (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000020)
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_RMSK                                                  0x30f
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_GFMUX_CTL_ADDR, HWIO_LPASS_QDSP6SS_GFMUX_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_GFMUX_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_GFMUX_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_GFMUX_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_GFMUX_CTL_IN)
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_IDLE_CORE_CLK_EN_BMSK                                 0x200
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_IDLE_CORE_CLK_EN_SHFT                                   0x9
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_SRC_SWITCH_CLK_OVR_BMSK                               0x100
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_SRC_SWITCH_CLK_OVR_SHFT                                 0x8
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_SRC_SEL_BMSK                                        0xc
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_SRC_SEL_SHFT                                        0x2
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_ENA_BMSK                                            0x2
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_ENA_SHFT                                            0x1
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_ARES_BMSK                                           0x1
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_ARES_SHFT                                           0x0

#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_ADDR                                          (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000024)
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_OFFS                                          (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000024)
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_RMSK                                                0x1f
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_GFMUX_STATUS_ADDR, HWIO_LPASS_QDSP6SS_GFMUX_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_GFMUX_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_SEL_STATUS_BMSK                                     0x1e
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_SEL_STATUS_SHFT                                      0x1
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_SWITCH_STATUS_BMSK                                   0x1
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_SWITCH_STATUS_SHFT                                   0x0

#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ADDR                                         (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000028)
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_OFFS                                         (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000028)
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_RMSK                                         0x80000013
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ADDR, HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_RMSK)
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ADDR,m,v,HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_IN)
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ROOT_OFF_BMSK                                0x80000000
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ROOT_OFF_SHFT                                      0x1f
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                0x10
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                 0x4
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ROOT_EN_BMSK                                        0x2
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ROOT_EN_SHFT                                        0x1
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ROOT_EN_DISABLE_FVAL                                0x0
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ROOT_EN_ENABLE_FVAL                                 0x1
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_UPDATE_BMSK                                         0x1
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_UPDATE_SHFT                                         0x0
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_UPDATE_DISABLE_FVAL                                 0x0
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_UPDATE_ENABLE_FVAL                                  0x1

#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_ADDR                                         (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x0000002c)
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_OFFS                                         (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000002c)
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_RMSK                                            0x1071f
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_ADDR, HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_RMSK)
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_ADDR,m,v,HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_IN)
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_RCGLITE_DISABLE_BMSK                            0x10000
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_RCGLITE_DISABLE_SHFT                               0x10
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_SEL_BMSK                                      0x700
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_SEL_SHFT                                        0x8
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_SEL_SRC0_FVAL                                   0x0
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_SEL_SRC1_FVAL                                   0x1
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_SEL_SRC2_FVAL                                   0x2
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_SEL_SRC3_FVAL                                   0x3
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_SEL_SRC4_FVAL                                   0x4
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_SEL_SRC5_FVAL                                   0x5
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_SEL_SRC6_FVAL                                   0x6
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_SEL_SRC7_FVAL                                   0x7
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_BMSK                                       0x1f
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_SHFT                                        0x0
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_BYPASS_FVAL                                 0x0
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_DIV1_FVAL                                   0x1
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_DIV1_5_FVAL                                 0x2
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_DIV2_FVAL                                   0x3
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_DIV2_5_FVAL                                 0x4
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_DIV3_FVAL                                   0x5
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_DIV3_5_FVAL                                 0x6
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_DIV4_FVAL                                   0x7
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_DIV4_5_FVAL                                 0x8
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_DIV5_FVAL                                   0x9
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_DIV5_5_FVAL                                 0xa
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_DIV6_FVAL                                   0xb
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_DIV6_5_FVAL                                 0xc
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_DIV7_FVAL                                   0xd
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_DIV7_5_FVAL                                 0xe
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_DIV8_FVAL                                   0xf
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_DIV8_5_FVAL                                0x10
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_DIV9_FVAL                                  0x11
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_DIV9_5_FVAL                                0x12
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_DIV10_FVAL                                 0x13
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_DIV10_5_FVAL                               0x14
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_DIV11_FVAL                                 0x15
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_DIV11_5_FVAL                               0x16
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_DIV12_FVAL                                 0x17
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_DIV12_5_FVAL                               0x18
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_DIV13_FVAL                                 0x19
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_DIV13_5_FVAL                               0x1a
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_DIV14_FVAL                                 0x1b
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_DIV14_5_FVAL                               0x1c
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_DIV15_FVAL                                 0x1d
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_DIV15_5_FVAL                               0x1e
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_DIV16_FVAL                                 0x1f

#define HWIO_LPASS_QDSP6SS_PWR_CTL_ADDR                                               (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000030)
#define HWIO_LPASS_QDSP6SS_PWR_CTL_OFFS                                               (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000030)
#define HWIO_LPASS_QDSP6SS_PWR_CTL_RMSK                                                0xf7c0000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PWR_CTL_ADDR, HWIO_LPASS_QDSP6SS_PWR_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_PWR_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PWR_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PWR_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PWR_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PWR_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PWR_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PWR_CTL_IN)
#define HWIO_LPASS_QDSP6SS_PWR_CTL_LDO_PWR_UP_BG_BMSK                                  0x8000000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_LDO_PWR_UP_BG_SHFT                                       0x1b
#define HWIO_LPASS_QDSP6SS_PWR_CTL_LDO_PWR_UP_BMSK                                     0x4000000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_LDO_PWR_UP_SHFT                                          0x1a
#define HWIO_LPASS_QDSP6SS_PWR_CTL_LDO_BYP_BMSK                                        0x2000000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_LDO_BYP_SHFT                                             0x19
#define HWIO_LPASS_QDSP6SS_PWR_CTL_BHS_ON_BMSK                                         0x1000000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_BHS_ON_SHFT                                              0x18
#define HWIO_LPASS_QDSP6SS_PWR_CTL_CLAMP_QMC_MEM_BMSK                                   0x400000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_CLAMP_QMC_MEM_SHFT                                       0x16
#define HWIO_LPASS_QDSP6SS_PWR_CTL_CLAMP_WL_BMSK                                        0x200000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_CLAMP_WL_SHFT                                            0x15
#define HWIO_LPASS_QDSP6SS_PWR_CTL_CLAMP_IO_BMSK                                        0x100000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_CLAMP_IO_SHFT                                            0x14
#define HWIO_LPASS_QDSP6SS_PWR_CTL_SLP_RET_N_BMSK                                        0x80000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_SLP_RET_N_SHFT                                           0x13
#define HWIO_LPASS_QDSP6SS_PWR_CTL_ARR_STBY_N_BMSK                                       0x40000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_ARR_STBY_N_SHFT                                          0x12

#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_ADDR                                           (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000034)
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_OFFS                                           (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000034)
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_RMSK                                           0x1fffffff
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_ADDR, HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_IN)
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_JU_SLP_NRET_N_BMSK                             0x1c000000
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_JU_SLP_NRET_N_SHFT                                   0x1a
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_ETB_SLP_NRET_N_BMSK                             0x2000000
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_ETB_SLP_NRET_N_SHFT                                  0x19
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_L1IU_SLP_NRET_N_BMSK                            0x1800000
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_L1IU_SLP_NRET_N_SHFT                                 0x17
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_L1DU_SLP_NRET_N_BMSK                             0x600000
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_L1DU_SLP_NRET_N_SHFT                                 0x15
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_L2PLRU_SLP_NRET_N_BMSK                           0x100000
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_L2PLRU_SLP_NRET_N_SHFT                               0x14
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_L2TAG_SLP_NRET_N_BMSK                             0xf0000
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_L2TAG_SLP_NRET_N_SHFT                                0x10
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_L2DATA_SLP_NRET_N_BMSK                             0xffff
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_L2DATA_SLP_NRET_N_SHFT                                0x0

#define HWIO_LPASS_QDSP6SS_XO_CBCR_ADDR                                               (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000038)
#define HWIO_LPASS_QDSP6SS_XO_CBCR_OFFS                                               (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000038)
#define HWIO_LPASS_QDSP6SS_XO_CBCR_RMSK                                               0x80000001
#define HWIO_LPASS_QDSP6SS_XO_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_XO_CBCR_ADDR, HWIO_LPASS_QDSP6SS_XO_CBCR_RMSK)
#define HWIO_LPASS_QDSP6SS_XO_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_XO_CBCR_ADDR, m)
#define HWIO_LPASS_QDSP6SS_XO_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_XO_CBCR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_XO_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_XO_CBCR_ADDR,m,v,HWIO_LPASS_QDSP6SS_XO_CBCR_IN)
#define HWIO_LPASS_QDSP6SS_XO_CBCR_CLKOFF_BMSK                                        0x80000000
#define HWIO_LPASS_QDSP6SS_XO_CBCR_CLKOFF_SHFT                                              0x1f
#define HWIO_LPASS_QDSP6SS_XO_CBCR_CLKEN_BMSK                                                0x1
#define HWIO_LPASS_QDSP6SS_XO_CBCR_CLKEN_SHFT                                                0x0

#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_ADDR                                            (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x0000003c)
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_OFFS                                            (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000003c)
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_RMSK                                            0x80000001
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SLEEP_CBCR_ADDR, HWIO_LPASS_QDSP6SS_SLEEP_CBCR_RMSK)
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SLEEP_CBCR_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SLEEP_CBCR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SLEEP_CBCR_ADDR,m,v,HWIO_LPASS_QDSP6SS_SLEEP_CBCR_IN)
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_CLKOFF_BMSK                                     0x80000000
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_CLKOFF_SHFT                                           0x1f
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_CLKEN_BMSK                                             0x1
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_CLKEN_SHFT                                             0x0

#define HWIO_LPASS_QDSP6SS_NMI_ADDR                                                   (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000040)
#define HWIO_LPASS_QDSP6SS_NMI_OFFS                                                   (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000040)
#define HWIO_LPASS_QDSP6SS_NMI_RMSK                                                          0x3
#define HWIO_LPASS_QDSP6SS_NMI_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_NMI_ADDR,v)
#define HWIO_LPASS_QDSP6SS_NMI_CLEAR_STATUS_BMSK                                             0x2
#define HWIO_LPASS_QDSP6SS_NMI_CLEAR_STATUS_SHFT                                             0x1
#define HWIO_LPASS_QDSP6SS_NMI_SET_NMI_BMSK                                                  0x1
#define HWIO_LPASS_QDSP6SS_NMI_SET_NMI_SHFT                                                  0x0

#define HWIO_LPASS_QDSP6SS_NMI_STATUS_ADDR                                            (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000044)
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_OFFS                                            (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000044)
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_RMSK                                                   0x7
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_NMI_STATUS_ADDR, HWIO_LPASS_QDSP6SS_NMI_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_NMI_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_EXT_DBG_TRIG_BMSK                                      0x4
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_EXT_DBG_TRIG_SHFT                                      0x2
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_WDOG_TRIG_BMSK                                         0x2
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_WDOG_TRIG_SHFT                                         0x1
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_PUBCSR_TRIG_BMSK                                       0x1
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_PUBCSR_TRIG_SHFT                                       0x0

#define HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_ADDR                                        (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000048)
#define HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_OFFS                                        (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000048)
#define HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_RMSK                                               0x1
#define HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_ADDR, HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_RMSK)
#define HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_ADDR,v)
#define HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_ADDR,m,v,HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_IN)
#define HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_Q6_MON_CLKEN_BMSK                                  0x1
#define HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_Q6_MON_CLKEN_SHFT                                  0x0

#define HWIO_LPASS_QDSP6SS_STATERET_CTL_ADDR                                          (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x0000004c)
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_OFFS                                          (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000004c)
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_RMSK                                                 0xf
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STATERET_CTL_ADDR, HWIO_LPASS_QDSP6SS_STATERET_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STATERET_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STATERET_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STATERET_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_STATERET_CTL_IN)
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_WAKEUP_IN_BMSK                                       0x8
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_WAKEUP_IN_SHFT                                       0x3
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_WAKE_IRQ_BMSK                                        0x4
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_WAKE_IRQ_SHFT                                        0x2
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_RESTORE_BMSK                                         0x2
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_RESTORE_SHFT                                         0x1
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_SAVE_BMSK                                            0x1
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_SAVE_SHFT                                            0x0

#define HWIO_LPASS_QDSP6SS_LDO_USER_ADDR                                              (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000050)
#define HWIO_LPASS_QDSP6SS_LDO_USER_OFFS                                              (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000050)
#define HWIO_LPASS_QDSP6SS_LDO_USER_RMSK                                              0xffffffff
#define HWIO_LPASS_QDSP6SS_LDO_USER_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_USER_ADDR, HWIO_LPASS_QDSP6SS_LDO_USER_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_USER_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_USER_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_USER_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_LDO_USER_ADDR,v)
#define HWIO_LPASS_QDSP6SS_LDO_USER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_LDO_USER_ADDR,m,v,HWIO_LPASS_QDSP6SS_LDO_USER_IN)
#define HWIO_LPASS_QDSP6SS_LDO_USER_DATA_BMSK                                         0xffffffff
#define HWIO_LPASS_QDSP6SS_LDO_USER_DATA_SHFT                                                0x0

#define HWIO_LPASS_QDSP6SS_LDO_CFG0_ADDR                                              (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000054)
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_OFFS                                              (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000054)
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_RMSK                                              0xffffffff
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_CFG0_ADDR, HWIO_LPASS_QDSP6SS_LDO_CFG0_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_CFG0_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_LDO_CFG0_ADDR,v)
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_LDO_CFG0_ADDR,m,v,HWIO_LPASS_QDSP6SS_LDO_CFG0_IN)
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_DATA_BMSK                                         0xffffffff
#define HWIO_LPASS_QDSP6SS_LDO_CFG0_DATA_SHFT                                                0x0

#define HWIO_LPASS_QDSP6SS_LDO_CFG1_ADDR                                              (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000058)
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_OFFS                                              (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000058)
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_RMSK                                              0xffffffff
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_CFG1_ADDR, HWIO_LPASS_QDSP6SS_LDO_CFG1_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_CFG1_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_LDO_CFG1_ADDR,v)
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_LDO_CFG1_ADDR,m,v,HWIO_LPASS_QDSP6SS_LDO_CFG1_IN)
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_DATA_BMSK                                         0xffffffff
#define HWIO_LPASS_QDSP6SS_LDO_CFG1_DATA_SHFT                                                0x0

#define HWIO_LPASS_QDSP6SS_LDO_CFG2_ADDR                                              (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x0000005c)
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_OFFS                                              (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000005c)
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_RMSK                                              0xffffffff
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_CFG2_ADDR, HWIO_LPASS_QDSP6SS_LDO_CFG2_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_CFG2_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_LDO_CFG2_ADDR,v)
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_LDO_CFG2_ADDR,m,v,HWIO_LPASS_QDSP6SS_LDO_CFG2_IN)
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_DATA_BMSK                                         0xffffffff
#define HWIO_LPASS_QDSP6SS_LDO_CFG2_DATA_SHFT                                                0x0

#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_ADDR                                          (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000060)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_OFFS                                          (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000060)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_RMSK                                             0x1007f
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_VREF_SET_ADDR, HWIO_LPASS_QDSP6SS_LDO_VREF_SET_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_VREF_SET_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_LDO_VREF_SET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_LDO_VREF_SET_ADDR,m,v,HWIO_LPASS_QDSP6SS_LDO_VREF_SET_IN)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_LDO_VREF_SEL_RST_BMSK                            0x10000
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_LDO_VREF_SEL_RST_SHFT                               0x10
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_VREF_LDO_BMSK                                       0x7f
#define HWIO_LPASS_QDSP6SS_LDO_VREF_SET_VREF_LDO_SHFT                                        0x0

#define HWIO_LPASS_QDSP6SS_LDO_VREF_CMD_ADDR                                          (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000064)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_CMD_OFFS                                          (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000064)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_CMD_RMSK                                                 0x1
#define HWIO_LPASS_QDSP6SS_LDO_VREF_CMD_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_LDO_VREF_CMD_ADDR,v)
#define HWIO_LPASS_QDSP6SS_LDO_VREF_CMD_LDO_VREF_SEL_UPDATE_BMSK                             0x1
#define HWIO_LPASS_QDSP6SS_LDO_VREF_CMD_LDO_VREF_SEL_UPDATE_SHFT                             0x0

#define HWIO_LPASS_QDSP6SS_LDO_LD_CTL_ADDR                                            (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000068)
#define HWIO_LPASS_QDSP6SS_LDO_LD_CTL_OFFS                                            (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000068)
#define HWIO_LPASS_QDSP6SS_LDO_LD_CTL_RMSK                                                0xffff
#define HWIO_LPASS_QDSP6SS_LDO_LD_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_LD_CTL_ADDR, HWIO_LPASS_QDSP6SS_LDO_LD_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_LD_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_LD_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_LD_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_LDO_LD_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_LDO_LD_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_LDO_LD_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_LDO_LD_CTL_IN)
#define HWIO_LPASS_QDSP6SS_LDO_LD_CTL_DATA_BMSK                                           0xffff
#define HWIO_LPASS_QDSP6SS_LDO_LD_CTL_DATA_SHFT                                              0x0

#define HWIO_LPASS_QDSP6SS_LDO_TRIM_CTL_ADDR                                          (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x0000006c)
#define HWIO_LPASS_QDSP6SS_LDO_TRIM_CTL_OFFS                                          (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000006c)
#define HWIO_LPASS_QDSP6SS_LDO_TRIM_CTL_RMSK                                                0xff
#define HWIO_LPASS_QDSP6SS_LDO_TRIM_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_TRIM_CTL_ADDR, HWIO_LPASS_QDSP6SS_LDO_TRIM_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_TRIM_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_TRIM_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_TRIM_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_LDO_TRIM_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_LDO_TRIM_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_LDO_TRIM_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_LDO_TRIM_CTL_IN)
#define HWIO_LPASS_QDSP6SS_LDO_TRIM_CTL_DATA_BMSK                                           0xff
#define HWIO_LPASS_QDSP6SS_LDO_TRIM_CTL_DATA_SHFT                                            0x0

#define HWIO_LPASS_QDSP6SS_LDO_STATUS_ADDR                                            (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000070)
#define HWIO_LPASS_QDSP6SS_LDO_STATUS_OFFS                                            (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000070)
#define HWIO_LPASS_QDSP6SS_LDO_STATUS_RMSK                                            0xffffffff
#define HWIO_LPASS_QDSP6SS_LDO_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_STATUS_ADDR, HWIO_LPASS_QDSP6SS_LDO_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_STATUS_STATUS_BMSK                                     0xffffffff
#define HWIO_LPASS_QDSP6SS_LDO_STATUS_STATUS_SHFT                                            0x0

#define HWIO_LPASS_QDSP6SS_LDO_EFUSE_STATUS_ADDR                                      (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000074)
#define HWIO_LPASS_QDSP6SS_LDO_EFUSE_STATUS_OFFS                                      (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000074)
#define HWIO_LPASS_QDSP6SS_LDO_EFUSE_STATUS_RMSK                                            0x3f
#define HWIO_LPASS_QDSP6SS_LDO_EFUSE_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_EFUSE_STATUS_ADDR, HWIO_LPASS_QDSP6SS_LDO_EFUSE_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_EFUSE_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_EFUSE_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_EFUSE_STATUS_LDO_VREF_TRIM_BMSK                              0x3e
#define HWIO_LPASS_QDSP6SS_LDO_EFUSE_STATUS_LDO_VREF_TRIM_SHFT                               0x1
#define HWIO_LPASS_QDSP6SS_LDO_EFUSE_STATUS_LDO_EN_BMSK                                      0x1
#define HWIO_LPASS_QDSP6SS_LDO_EFUSE_STATUS_LDO_EN_SHFT                                      0x0

#define HWIO_LPASS_QDSP6SS_LDO_PWR_STATUS_ADDR                                        (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000078)
#define HWIO_LPASS_QDSP6SS_LDO_PWR_STATUS_OFFS                                        (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000078)
#define HWIO_LPASS_QDSP6SS_LDO_PWR_STATUS_RMSK                                               0x1
#define HWIO_LPASS_QDSP6SS_LDO_PWR_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_PWR_STATUS_ADDR, HWIO_LPASS_QDSP6SS_LDO_PWR_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_PWR_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_PWR_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_PWR_STATUS_LDO_READY_BMSK                                     0x1
#define HWIO_LPASS_QDSP6SS_LDO_PWR_STATUS_LDO_READY_SHFT                                     0x0

#define HWIO_LPASS_QDSP6SS_LDO_PREON_CTL_ADDR                                         (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x0000007c)
#define HWIO_LPASS_QDSP6SS_LDO_PREON_CTL_OFFS                                         (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000007c)
#define HWIO_LPASS_QDSP6SS_LDO_PREON_CTL_RMSK                                                0x3
#define HWIO_LPASS_QDSP6SS_LDO_PREON_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_PREON_CTL_ADDR, HWIO_LPASS_QDSP6SS_LDO_PREON_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_PREON_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_PREON_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_PREON_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_LDO_PREON_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_LDO_PREON_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_LDO_PREON_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_LDO_PREON_CTL_IN)
#define HWIO_LPASS_QDSP6SS_LDO_PREON_CTL_CORE_PREON_EN_BMSK                                  0x2
#define HWIO_LPASS_QDSP6SS_LDO_PREON_CTL_CORE_PREON_EN_SHFT                                  0x1
#define HWIO_LPASS_QDSP6SS_LDO_PREON_CTL_CP_PREON_EN_BMSK                                    0x1
#define HWIO_LPASS_QDSP6SS_LDO_PREON_CTL_CP_PREON_EN_SHFT                                    0x0

#define HWIO_LPASS_QDSP6SS_SPM_SW_TRIG_ADDR                                           (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000080)
#define HWIO_LPASS_QDSP6SS_SPM_SW_TRIG_OFFS                                           (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000080)
#define HWIO_LPASS_QDSP6SS_SPM_SW_TRIG_RMSK                                                  0xf
#define HWIO_LPASS_QDSP6SS_SPM_SW_TRIG_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPM_SW_TRIG_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPM_SW_TRIG_CMD_BMSK                                              0xf
#define HWIO_LPASS_QDSP6SS_SPM_SW_TRIG_CMD_SHFT                                              0x0

#define HWIO_LPASS_QDSP6SS_SPM_TRIG_STATUS_ADDR                                       (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000084)
#define HWIO_LPASS_QDSP6SS_SPM_TRIG_STATUS_OFFS                                       (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000084)
#define HWIO_LPASS_QDSP6SS_SPM_TRIG_STATUS_RMSK                                              0xf
#define HWIO_LPASS_QDSP6SS_SPM_TRIG_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPM_TRIG_STATUS_ADDR, HWIO_LPASS_QDSP6SS_SPM_TRIG_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_SPM_TRIG_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPM_TRIG_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SPM_TRIG_STATUS_BUSY_BMSK                                         0xf
#define HWIO_LPASS_QDSP6SS_SPM_TRIG_STATUS_BUSY_SHFT                                         0x0

#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_ADDR                                          (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000088)
#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_OFFS                                          (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000088)
#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_RMSK                                                 0x7
#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_INTF_HALTREQ_ADDR, HWIO_LPASS_QDSP6SS_INTF_HALTREQ_RMSK)
#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_INTF_HALTREQ_ADDR, m)
#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_INTF_HALTREQ_ADDR,v)
#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_INTF_HALTREQ_ADDR,m,v,HWIO_LPASS_QDSP6SS_INTF_HALTREQ_IN)
#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_AXIM2_BMSK                                           0x4
#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_AXIM2_SHFT                                           0x2
#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_AXIM_BMSK                                            0x2
#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_AXIM_SHFT                                            0x1
#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_ALL_BMSK                                             0x1
#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_ALL_SHFT                                             0x0

#define HWIO_LPASS_QDSP6SS_INTF_HALTACK_ADDR                                          (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x0000008c)
#define HWIO_LPASS_QDSP6SS_INTF_HALTACK_OFFS                                          (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000008c)
#define HWIO_LPASS_QDSP6SS_INTF_HALTACK_RMSK                                                 0x7
#define HWIO_LPASS_QDSP6SS_INTF_HALTACK_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_INTF_HALTACK_ADDR, HWIO_LPASS_QDSP6SS_INTF_HALTACK_RMSK)
#define HWIO_LPASS_QDSP6SS_INTF_HALTACK_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_INTF_HALTACK_ADDR, m)
#define HWIO_LPASS_QDSP6SS_INTF_HALTACK_AXIM2_BMSK                                           0x4
#define HWIO_LPASS_QDSP6SS_INTF_HALTACK_AXIM2_SHFT                                           0x2
#define HWIO_LPASS_QDSP6SS_INTF_HALTACK_AXIM_BMSK                                            0x2
#define HWIO_LPASS_QDSP6SS_INTF_HALTACK_AXIM_SHFT                                            0x1
#define HWIO_LPASS_QDSP6SS_INTF_HALTACK_ALL_BMSK                                             0x1
#define HWIO_LPASS_QDSP6SS_INTF_HALTACK_ALL_SHFT                                             0x0

#define HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_ADDR                                         (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000090)
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_OFFS                                         (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000090)
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_RMSK                                                0xf
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_AXIM2_CLAMP_E_BMSK                                  0x8
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_AXIM2_CLAMP_E_SHFT                                  0x3
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_AXIM2_CLAMP_L_BMSK                                  0x4
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_AXIM2_CLAMP_L_SHFT                                  0x2
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_AXIM_CLAMP_E_BMSK                                   0x2
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_AXIM_CLAMP_E_SHFT                                   0x1
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_AXIM_CLAMP_L_BMSK                                   0x1
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_AXIM_CLAMP_L_SHFT                                   0x0

#define HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_ADDR                                       (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000094)
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_OFFS                                       (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000094)
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_RMSK                                              0xf
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_AXIM2_CLAMP_E_BMSK                                0x8
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_AXIM2_CLAMP_E_SHFT                                0x3
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_AXIM2_CLAMP_L_BMSK                                0x4
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_AXIM2_CLAMP_L_SHFT                                0x2
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_AXIM_CLAMP_E_BMSK                                 0x2
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_AXIM_CLAMP_E_SHFT                                 0x1
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_AXIM_CLAMP_L_BMSK                                 0x1
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_AXIM_CLAMP_L_SHFT                                 0x0

#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_ADDR                                      (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000098)
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_OFFS                                      (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000098)
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_RMSK                                             0xf
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_ADDR, HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_AXIM2_CLAMP_E_BMSK                               0x8
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_AXIM2_CLAMP_E_SHFT                               0x3
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_AXIM2_CLAMP_L_BMSK                               0x4
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_AXIM2_CLAMP_L_SHFT                               0x2
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_AXIM_CLAMP_E_BMSK                                0x2
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_AXIM_CLAMP_E_SHFT                                0x1
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_AXIM_CLAMP_L_BMSK                                0x1
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_AXIM_CLAMP_L_SHFT                                0x0

#define HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_ADDR                                       (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x0000009c)
#define HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_OFFS                                       (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000009c)
#define HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_RMSK                                              0x3
#define HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_ADDR, HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_RMSK)
#define HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_ADDR, m)
#define HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_ADDR,m,v,HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_IN)
#define HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_AXIM2_BMSK                                        0x2
#define HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_AXIM2_SHFT                                        0x1
#define HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_AXIM_BMSK                                         0x1
#define HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_AXIM_SHFT                                         0x0

#define HWIO_LPASS_QDSP6SS_CP_BHS_CTL_ADDR                                            (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x000000ac)
#define HWIO_LPASS_QDSP6SS_CP_BHS_CTL_OFFS                                            (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x000000ac)
#define HWIO_LPASS_QDSP6SS_CP_BHS_CTL_RMSK                                                   0xf
#define HWIO_LPASS_QDSP6SS_CP_BHS_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CP_BHS_CTL_ADDR, HWIO_LPASS_QDSP6SS_CP_BHS_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_CP_BHS_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CP_BHS_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CP_BHS_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_CP_BHS_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_CP_BHS_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_CP_BHS_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_CP_BHS_CTL_IN)
#define HWIO_LPASS_QDSP6SS_CP_BHS_CTL_DRIVE_SEL_BMSK                                         0xf
#define HWIO_LPASS_QDSP6SS_CP_BHS_CTL_DRIVE_SEL_SHFT                                         0x0

#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_ADDR                                          (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x000000b0)
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_OFFS                                          (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x000000b0)
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_RMSK                                              0xaf7f
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_ADDR, HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_RMSK)
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_ADDR,v)
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_ADDR,m,v,HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_IN)
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CP0_CLK_EN_BMSK                                   0x8000
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CP0_CLK_EN_SHFT                                      0xf
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AXIS_CLK_EN_BMSK                                  0x2000
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AXIS_CLK_EN_SHFT                                     0xd
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AHBM_CLK_EN_BMSK                                   0x800
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AHBM_CLK_EN_SHFT                                     0xb
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AHBS_CLK_EN_BMSK                                   0x400
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AHBS_CLK_EN_SHFT                                     0xa
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_PRIV_AHBS_CLK_EN_BMSK                              0x300
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_PRIV_AHBS_CLK_EN_SHFT                                0x8
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_L2VIC_AHBS_CLK_EN_BMSK                              0x60
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_L2VIC_AHBS_CLK_EN_SHFT                               0x5
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_TEST_AHBS_CLK_EN_BMSK                               0x10
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_TEST_AHBS_CLK_EN_SHFT                                0x4
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_PUB_AHBS_CLK_EN_BMSK                                 0x8
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_PUB_AHBS_CLK_EN_SHFT                                 0x3
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CORE_BUS_EN_BMSK                                     0x4
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CORE_BUS_EN_SHFT                                     0x2
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CORE_RCLK_EN_BMSK                                    0x2
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CORE_RCLK_EN_SHFT                                    0x1
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CORE_CLK_EN_BMSK                                     0x1
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CORE_CLK_EN_SHFT                                     0x0

#define HWIO_LPASS_QDSP6SS_L1S_PWR_CTL_ADDR                                           (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x000000b4)
#define HWIO_LPASS_QDSP6SS_L1S_PWR_CTL_OFFS                                           (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x000000b4)
#define HWIO_LPASS_QDSP6SS_L1S_PWR_CTL_RMSK                                                 0xff
#define HWIO_LPASS_QDSP6SS_L1S_PWR_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_L1S_PWR_CTL_ADDR, HWIO_LPASS_QDSP6SS_L1S_PWR_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_L1S_PWR_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_L1S_PWR_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_L1S_PWR_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_L1S_PWR_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_L1S_PWR_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_L1S_PWR_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_L1S_PWR_CTL_IN)
#define HWIO_LPASS_QDSP6SS_L1S_PWR_CTL_SLP_NRET_N_BMSK                                      0xff
#define HWIO_LPASS_QDSP6SS_L1S_PWR_CTL_SLP_NRET_N_SHFT                                       0x0

#define HWIO_LPASS_QDSP6SS_CORE_BHS_CTL_ADDR                                          (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x000000c0)
#define HWIO_LPASS_QDSP6SS_CORE_BHS_CTL_OFFS                                          (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x000000c0)
#define HWIO_LPASS_QDSP6SS_CORE_BHS_CTL_RMSK                                                 0xf
#define HWIO_LPASS_QDSP6SS_CORE_BHS_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CORE_BHS_CTL_ADDR, HWIO_LPASS_QDSP6SS_CORE_BHS_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_CORE_BHS_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CORE_BHS_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CORE_BHS_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_CORE_BHS_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_CORE_BHS_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_CORE_BHS_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_CORE_BHS_CTL_IN)
#define HWIO_LPASS_QDSP6SS_CORE_BHS_CTL_DRIVE_SEL_BMSK                                       0xf
#define HWIO_LPASS_QDSP6SS_CORE_BHS_CTL_DRIVE_SEL_SHFT                                       0x0

#define HWIO_LPASS_QDSP6SS_BHS_STATUS_ADDR                                            (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x000000c4)
#define HWIO_LPASS_QDSP6SS_BHS_STATUS_OFFS                                            (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x000000c4)
#define HWIO_LPASS_QDSP6SS_BHS_STATUS_RMSK                                                   0x1
#define HWIO_LPASS_QDSP6SS_BHS_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_BHS_STATUS_ADDR, HWIO_LPASS_QDSP6SS_BHS_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_BHS_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_BHS_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_BHS_STATUS_BHS_EN_REST_ACK_BMSK                                   0x1
#define HWIO_LPASS_QDSP6SS_BHS_STATUS_BHS_EN_REST_ACK_SHFT                                   0x0

#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_ADDR                                           (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x000000c8)
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_OFFS                                           (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x000000c8)
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_RMSK                                                  0x3
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_ADDR, HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_IN)
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_QMC_MEM_SVS_SEL_BMSK                                  0x2
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_QMC_MEM_SVS_SEL_SHFT                                  0x1
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_QMC_MEM_SVS_BMSK                                      0x1
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_QMC_MEM_SVS_SHFT                                      0x0

#define HWIO_LPASS_QDSP6SS_BHS_TEST_ADDR                                              (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x000000cc)
#define HWIO_LPASS_QDSP6SS_BHS_TEST_OFFS                                              (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x000000cc)
#define HWIO_LPASS_QDSP6SS_BHS_TEST_RMSK                                                     0x1
#define HWIO_LPASS_QDSP6SS_BHS_TEST_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_BHS_TEST_ADDR, HWIO_LPASS_QDSP6SS_BHS_TEST_RMSK)
#define HWIO_LPASS_QDSP6SS_BHS_TEST_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_BHS_TEST_ADDR, m)
#define HWIO_LPASS_QDSP6SS_BHS_TEST_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_BHS_TEST_ADDR,v)
#define HWIO_LPASS_QDSP6SS_BHS_TEST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_BHS_TEST_ADDR,m,v,HWIO_LPASS_QDSP6SS_BHS_TEST_IN)
#define HWIO_LPASS_QDSP6SS_BHS_TEST_INSTANT_ON_BMSK                                          0x1
#define HWIO_LPASS_QDSP6SS_BHS_TEST_INSTANT_ON_SHFT                                          0x0

#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_ADDR                                            (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x000000f0)
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_OFFS                                            (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x000000f0)
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_RMSK                                                   0xf
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CP_PWR_CTL_ADDR, HWIO_LPASS_QDSP6SS_CP_PWR_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CP_PWR_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_CP_PWR_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_CP_PWR_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_CP_PWR_CTL_IN)
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_LDO_2PASS_ON_BMSK                                      0x8
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_LDO_2PASS_ON_SHFT                                      0x3
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_SHUNT_BHS_ON_BMSK                                      0x4
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_SHUNT_BHS_ON_SHFT                                      0x2
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_BHS_ON_BMSK                                            0x2
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_BHS_ON_SHFT                                            0x1
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_CLAMP_IO_BMSK                                          0x1
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_CLAMP_IO_SHFT                                          0x0

#define HWIO_LPASS_QDSP6SS_CP_PWR_STATUS_ADDR                                         (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x000000f4)
#define HWIO_LPASS_QDSP6SS_CP_PWR_STATUS_OFFS                                         (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x000000f4)
#define HWIO_LPASS_QDSP6SS_CP_PWR_STATUS_RMSK                                                0x1
#define HWIO_LPASS_QDSP6SS_CP_PWR_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CP_PWR_STATUS_ADDR, HWIO_LPASS_QDSP6SS_CP_PWR_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_CP_PWR_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CP_PWR_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CP_PWR_STATUS_ENR_ACK_BMSK                                        0x1
#define HWIO_LPASS_QDSP6SS_CP_PWR_STATUS_ENR_ACK_SHFT                                        0x0

#define HWIO_LPASS_QDSP6SS_CP_RESET_ADDR                                              (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x000000f8)
#define HWIO_LPASS_QDSP6SS_CP_RESET_OFFS                                              (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x000000f8)
#define HWIO_LPASS_QDSP6SS_CP_RESET_RMSK                                                     0x1
#define HWIO_LPASS_QDSP6SS_CP_RESET_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CP_RESET_ADDR, HWIO_LPASS_QDSP6SS_CP_RESET_RMSK)
#define HWIO_LPASS_QDSP6SS_CP_RESET_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CP_RESET_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CP_RESET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_CP_RESET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_CP_RESET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_CP_RESET_ADDR,m,v,HWIO_LPASS_QDSP6SS_CP_RESET_IN)
#define HWIO_LPASS_QDSP6SS_CP_RESET_ARES_BMSK                                                0x1
#define HWIO_LPASS_QDSP6SS_CP_RESET_ARES_SHFT                                                0x0

#define HWIO_LPASS_QDSP6SS_CP_CLK_CTL_ADDR                                            (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x000000fc)
#define HWIO_LPASS_QDSP6SS_CP_CLK_CTL_OFFS                                            (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x000000fc)
#define HWIO_LPASS_QDSP6SS_CP_CLK_CTL_RMSK                                                   0x1
#define HWIO_LPASS_QDSP6SS_CP_CLK_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CP_CLK_CTL_ADDR, HWIO_LPASS_QDSP6SS_CP_CLK_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_CP_CLK_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CP_CLK_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CP_CLK_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_CP_CLK_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_CP_CLK_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_CP_CLK_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_CP_CLK_CTL_IN)
#define HWIO_LPASS_QDSP6SS_CP_CLK_CTL_CLK_ENA_BMSK                                           0x1
#define HWIO_LPASS_QDSP6SS_CP_CLK_CTL_CLK_ENA_SHFT                                           0x0

#define HWIO_LPASS_QDSP6SS_STRAP_TCM_ADDR                                             (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000100)
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_OFFS                                             (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000100)
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_RMSK                                             0xfffc0000
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_TCM_ADDR, HWIO_LPASS_QDSP6SS_STRAP_TCM_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_TCM_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_TCM_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_TCM_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_TCM_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_BASE_ADDR_BMSK                                   0xfffc0000
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_BASE_ADDR_SHFT                                         0x12

#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_ADDR                                        (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000104)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_OFFS                                        (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000104)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_RMSK                                        0xffffc000
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_ADDR, HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_UPPER_ADDR_BMSK                             0xffffc000
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_UPPER_ADDR_SHFT                                    0xe

#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_ADDR                                        (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000108)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_OFFS                                        (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000108)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_RMSK                                        0xffffc000
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_ADDR, HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_LOWER_ADDR_BMSK                             0xffffc000
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_LOWER_ADDR_SHFT                                    0xe

#define HWIO_LPASS_QDSP6SS_STRAP_ACC_ADDR                                             (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000110)
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_OFFS                                             (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000110)
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_RMSK                                             0xffffffff
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_ACC_ADDR, HWIO_LPASS_QDSP6SS_STRAP_ACC_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_ACC_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_ACC_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_ACC_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_ACC_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_DATA_BMSK                                        0xffffffff
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_DATA_SHFT                                               0x0

#define HWIO_LPASS_QDSP6SS_DCC_CTRL_ADDR                                              (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000118)
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_OFFS                                              (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000118)
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_RMSK                                              0xffffffff
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_DCC_CTRL_ADDR, HWIO_LPASS_QDSP6SS_DCC_CTRL_RMSK)
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_DCC_CTRL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_DCC_CTRL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_DCC_CTRL_ADDR,m,v,HWIO_LPASS_QDSP6SS_DCC_CTRL_IN)
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_CTRL_BMSK                                         0xffffffff
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_CTRL_SHFT                                                0x0

#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_ADDR                                      (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x0000011c)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_OFFS                                      (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000011c)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_RMSK                                      0xffffc000
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_ADDR, HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_UPPER_ADDR_BMSK                           0xffffc000
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_UPPER_ADDR_SHFT                                  0xe

#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_ADDR                                      (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000120)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_OFFS                                      (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000120)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_RMSK                                      0xffffc000
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_ADDR, HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_LOWER_ADDR_BMSK                           0xffffc000
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_LOWER_ADDR_SHFT                                  0xe

#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_SEL_ADDR                                     (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000124)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_SEL_OFFS                                     (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000124)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_SEL_RMSK                                            0x1
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_SEL_ADDR, HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_SEL_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_SEL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_SEL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_SEL_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_SEL_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_SEL_STRAP_QMC_ACC_SEL_BMSK                          0x1
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_SEL_STRAP_QMC_ACC_SEL_SHFT                          0x0

#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_ADDR                                         (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000128)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_OFFS                                         (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000128)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_RMSK                                         0xffffffff
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_ADDR, HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_STRAP_QMC_ACC_BMSK                           0xffffffff
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_STRAP_QMC_ACC_SHFT                                  0x0

#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_U_ADDR                                       (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x0000012c)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_U_OFFS                                       (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000012c)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_U_RMSK                                       0xffffffff
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_U_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_U_ADDR, HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_U_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_U_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_U_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_U_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_U_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_U_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_U_STRAP_QMC_ACC_U_BMSK                       0xffffffff
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_U_STRAP_QMC_ACC_U_SHFT                              0x0

#define HWIO_LPASS_QDSP6SS_PLL_MODE_ADDR                                              (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000200)
#define HWIO_LPASS_QDSP6SS_PLL_MODE_OFFS                                              (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000200)
#define HWIO_LPASS_QDSP6SS_PLL_MODE_RMSK                                              0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_MODE_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_MODE_ADDR, HWIO_LPASS_QDSP6SS_PLL_MODE_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_MODE_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_MODE_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_MODE_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_MODE_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_MODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_MODE_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_MODE_IN)
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_LOCK_DET_BMSK                                 0x80000000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_LOCK_DET_SHFT                                       0x1f
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_ACTIVE_FLAG_BMSK                              0x40000000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_ACTIVE_FLAG_SHFT                                    0x1e
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_ACK_LATCH_BMSK                                0x20000000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_ACK_LATCH_SHFT                                      0x1d
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_LOCK_DET_FINE_BMSK                            0x10000000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_LOCK_DET_FINE_SHFT                                  0x1c
#define HWIO_LPASS_QDSP6SS_PLL_MODE_RESERVE_BITS27_24_BMSK                             0xf000000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_RESERVE_BITS27_24_SHFT                                  0x18
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_BMSK                     0x800000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_SHFT                         0x17
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_NO_BYPASS_FVAL                0x0
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_BYPASS_FVAL                   0x1
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_UPDATE_BMSK                                     0x400000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_UPDATE_SHFT                                         0x16
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_UPDATE_NO_UPDATE_FVAL                                0x0
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_UPDATE_UPDATE_FVAL                                   0x1
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_VOTE_FSM_RESET_BMSK                             0x200000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_VOTE_FSM_RESET_SHFT                                 0x15
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_VOTE_FSM_RESET_NO_RESET_FVAL                         0x0
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_VOTE_FSM_RESET_RESET_FVAL                            0x1
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_VOTE_FSM_ENA_BMSK                               0x100000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_VOTE_FSM_ENA_SHFT                                   0x14
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_VOTE_FSM_ENA_DISABLE_FVAL                            0x0
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_VOTE_FSM_ENA_ENABLE_FVAL                             0x1
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_BIAS_COUNT_BMSK                                  0xfc000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_BIAS_COUNT_SHFT                                      0xe
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_LOCK_COUNT_BMSK                                   0x3f00
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_LOCK_COUNT_SHFT                                      0x8
#define HWIO_LPASS_QDSP6SS_PLL_MODE_RESERVE_BITS7_3_BMSK                                    0xf8
#define HWIO_LPASS_QDSP6SS_PLL_MODE_RESERVE_BITS7_3_SHFT                                     0x3
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_RESET_N_BMSK                                         0x4
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_RESET_N_SHFT                                         0x2
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_RESET_N_RESET_FVAL                                   0x0
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_RESET_N_NO_RESET_FVAL                                0x1
#define HWIO_LPASS_QDSP6SS_PLL_MODE_RESERVE_BIT1_BMSK                                        0x2
#define HWIO_LPASS_QDSP6SS_PLL_MODE_RESERVE_BIT1_SHFT                                        0x1
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_OUTCTRL_BMSK                                         0x1
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_OUTCTRL_SHFT                                         0x0
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_OUTCTRL_DISABLE_FVAL                                 0x0
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_OUTCTRL_ENABLE_FVAL                                  0x1

#define HWIO_LPASS_QDSP6SS_PLL_L_VAL_ADDR                                             (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000204)
#define HWIO_LPASS_QDSP6SS_PLL_L_VAL_OFFS                                             (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000204)
#define HWIO_LPASS_QDSP6SS_PLL_L_VAL_RMSK                                                 0xffff
#define HWIO_LPASS_QDSP6SS_PLL_L_VAL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_L_VAL_ADDR, HWIO_LPASS_QDSP6SS_PLL_L_VAL_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_L_VAL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_L_VAL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_L_VAL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_L_VAL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_L_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_L_VAL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_L_VAL_IN)
#define HWIO_LPASS_QDSP6SS_PLL_L_VAL_PLL_L_BMSK                                           0xffff
#define HWIO_LPASS_QDSP6SS_PLL_L_VAL_PLL_L_SHFT                                              0x0

#define HWIO_LPASS_QDSP6SS_PLL_CAL_L_VAL_ADDR                                         (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000208)
#define HWIO_LPASS_QDSP6SS_PLL_CAL_L_VAL_OFFS                                         (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000208)
#define HWIO_LPASS_QDSP6SS_PLL_CAL_L_VAL_RMSK                                             0xffff
#define HWIO_LPASS_QDSP6SS_PLL_CAL_L_VAL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_CAL_L_VAL_ADDR, HWIO_LPASS_QDSP6SS_PLL_CAL_L_VAL_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_CAL_L_VAL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_CAL_L_VAL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_CAL_L_VAL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_CAL_L_VAL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_CAL_L_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_CAL_L_VAL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_CAL_L_VAL_IN)
#define HWIO_LPASS_QDSP6SS_PLL_CAL_L_VAL_PLL_CAL_L_BMSK                                   0xffff
#define HWIO_LPASS_QDSP6SS_PLL_CAL_L_VAL_PLL_CAL_L_SHFT                                      0x0

#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_ADDR                                          (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x0000020c)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_OFFS                                          (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000020c)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RMSK                                          0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_USER_CTL_ADDR, HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_USER_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_USER_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_USER_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_USER_CTL_IN)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RESERVE_BITS31_19_BMSK                        0xfff80000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RESERVE_BITS31_19_SHFT                              0x13
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PRE_DIV_RATIO_BMSK                               0x70000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PRE_DIV_RATIO_SHFT                                  0x10
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PRE_DIV_RATIO_DIVIDE_BY_1_FVAL                       0x0
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PRE_DIV_RATIO_DIVIDE_BY_2_FVAL                       0x1
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PRE_DIV_RATIO_DIVIDE_BY_4_FVAL                       0x3
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_POST_DIV_RATIO_ODD_BMSK                           0xf000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_POST_DIV_RATIO_ODD_SHFT                              0xc
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_POST_DIV_RATIO_ODD_DIVIDE_BY_1_FVAL                  0x0
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_POST_DIV_RATIO_ODD_DIVIDE_BY_3_FVAL                  0x3
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_POST_DIV_RATIO_ODD_DIVIDE_BY_5_FVAL                  0x5
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_POST_DIV_RATIO_ODD_DIVIDE_BY_7_FVAL                  0x7
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_POST_DIV_RATIO_EVEN_BMSK                           0xf00
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_POST_DIV_RATIO_EVEN_SHFT                             0x8
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_POST_DIV_RATIO_EVEN_DIVIDE_BY_1_FVAL                 0x0
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_POST_DIV_RATIO_EVEN_DIVIDE_BY_2_FVAL                 0x1
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_POST_DIV_RATIO_EVEN_DIVIDE_BY_4_FVAL                 0x3
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_POST_DIV_RATIO_EVEN_DIVIDE_BY_8_FVAL                 0x7
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_OUT_CLK_POLARITY_BMSK                               0x80
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_OUT_CLK_POLARITY_SHFT                                0x7
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_OUT_CLK_POLARITY_DO_NOT_INVERT_OUTPUT_FVAL           0x0
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_OUT_CLK_POLARITY_INVERT_OUTPUT_FVAL                  0x1
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RESERVE_BITS6_5_BMSK                                0x60
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RESERVE_BITS6_5_SHFT                                 0x5
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_TEST_BMSK                                    0x10
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_TEST_SHFT                                     0x4
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_TEST_DISABLE_FVAL                             0x0
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_TEST_ENABLE_FVAL                              0x1
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RESERVE_BIT3_BMSK                                    0x8
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RESERVE_BIT3_SHFT                                    0x3
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_ODD_BMSK                                      0x4
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_ODD_SHFT                                      0x2
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_ODD_DISABLE_FVAL                              0x0
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_ODD_ENABLE_FVAL                               0x1
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_EVEN_BMSK                                     0x2
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_EVEN_SHFT                                     0x1
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_EVEN_DISABLE_FVAL                             0x0
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_EVEN_ENABLE_FVAL                              0x1
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_MAIN_BMSK                                     0x1
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_MAIN_SHFT                                     0x0
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_MAIN_DISABLE_FVAL                             0x0
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_MAIN_ENABLE_FVAL                              0x1

#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_ADDR                                        (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000210)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_OFFS                                        (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000210)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_RMSK                                        0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_ADDR, HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_IN)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_RESERVE_BITS31_19_BMSK                      0xfff80000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_RESERVE_BITS31_19_SHFT                            0x13
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_USE_PREDIV_WHEN_CAL_BMSK                       0x40000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_USE_PREDIV_WHEN_CAL_SHFT                          0x12
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_USE_PREDIV_WHEN_CAL_DO_NOT_USE_SECONDARY_PRE_DIVIDER_SETTING_WHEN_CALIBRATING_FVAL        0x0
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_USE_PREDIV_WHEN_CAL_USE_SECONDARY_PRE_DIVIDER_SETTING_WHEN_CALIBRATING_FVAL        0x1
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_USE_EXT_SAVERESTORE_BMSK                       0x20000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_USE_EXT_SAVERESTORE_SHFT                          0x11
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_USE_EXT_SAVERESTORE_ACTIVATES_INTERNAL_SAVE_AND_RESTORE_FVAL        0x0
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_USE_EXT_SAVERESTORE_DISABLE_INTERNAL_SAVE_AND_RESTORE_FVAL        0x1
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_LOW_JITTER_MODE_EN_BMSK                        0x10000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_LOW_JITTER_MODE_EN_SHFT                           0x10
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_LOW_JITTER_MODE_EN_REGUALAR_MODE_WITH_FMAX_FVAL        0x0
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_LOW_JITTER_MODE_EN_LOW_JITTER_MODE_WITH_FMAX_FVAL        0x1
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_FRAC_FORMAT_SEL_BMSK                            0x8000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_FRAC_FORMAT_SEL_SHFT                               0xf
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_FRAC_FORMAT_SEL_ALPHA_BASED_FRACTIONAL_WORD_FVAL        0x0
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_FRAC_FORMAT_SEL_M_OVER_N_BASED_FRACTIONAL_WORD_FVAL        0x1
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_BIAS_ON_IN_STANDBY_BMSK                         0x4000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_BIAS_ON_IN_STANDBY_SHFT                            0xe
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_BIAS_ON_IN_STANDBY_BIAS_IS_OFF_WHEN_THE_PLL_IS_IN_STANDBY_FVAL        0x0
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_BIAS_ON_IN_STANDBY_BIAS_IS_ON_WHEN_THE_PLL_IS_IN_STANDBY_FVAL        0x1
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_REF_CLK_AT_OUT_BMSK                             0x2000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_REF_CLK_AT_OUT_SHFT                                0xd
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_REF_CLK_AT_OUT_OUTPUT_IS_REFERENCE_CLOCK_WHEN_NOT_LOCKED_FVAL        0x0
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_REF_CLK_AT_OUT_REFERENCE_IS_ROUTED_TO_THE_OUTPUT_ONLY_WHEN_RESETN_IS_LOW_FVAL        0x1
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_SCALE_FREQ_ON_RESTART_BMSK                      0x1800
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_SCALE_FREQ_ON_RESTART_SHFT                         0xb
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_SCALE_FREQ_ON_RESTART_NO_SCALING_FVAL              0x0
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_SCALE_FREQ_ON_RESTART_SCALE_FREQUENCY_DOWNWARD_BY_6_PERCENT_FVAL        0x1
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_SCALE_FREQ_ON_RESTART_SCALE_FREQUENCY_DOWNWARD_BY_12_PERCENT_FVAL        0x2
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_SCALE_FREQ_ON_RESTART_SCALE_FREQUENCY_DOWNWARD_BY_25_PERCENT_FVAL        0x3
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_LATCH_INTERFACE_BYPASS_BMSK                      0x400
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_LATCH_INTERFACE_BYPASS_SHFT                        0xa
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_LATCH_INTERFACE_BYPASS_DO_NOT_BYPASS_FVAL          0x0
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_LATCH_INTERFACE_BYPASS_BYPASS_FVAL                 0x1
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_STATUS_REGISTER_BMSK                             0x3e0
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_STATUS_REGISTER_SHFT                               0x5
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_WRITE_STATE_EN_BMSK                               0x10
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_WRITE_STATE_EN_SHFT                                0x4
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_WRITE_STATE_EN_DISABLE_FVAL                        0x0
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_WRITE_STATE_EN_ENABLE_FVAL                         0x1
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_CALIB_CTRL_BMSK                                    0xe
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_CALIB_CTRL_SHFT                                    0x1
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_CALIB_CTRL_ALWAYS_PERFORM_CALIBRATION_FVAL         0x0
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_CALIB_CTRL_NEVER_PERFORM_CALIBRATION_FVAL          0x1
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_CALIB_CTRL_AUTOMATIC_FVAL                          0x2
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_USE_ONLY_FINE_LOCK_DET_BMSK                        0x1
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_USE_ONLY_FINE_LOCK_DET_SHFT                        0x0
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_USE_ONLY_FINE_LOCK_DET_USE_BOTH_THE_FINE_AND_COARSE_LOCK_DETECTOR_FVAL        0x0
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_USE_ONLY_FINE_LOCK_DET_USE_ONLY_THE_FINE_LOCK_DETECTOR_FVAL        0x1

#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_ADDR                                        (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000214)
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_OFFS                                        (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000214)
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_RMSK                                        0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_ADDR, HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_IN)
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_FINE_LDC_THRESHOLD_BMSK                     0xfc000000
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_FINE_LDC_THRESHOLD_SHFT                           0x1a
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_COARSE_LDC_THRESHOLD_BMSK                    0x3c00000
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_COARSE_LDC_THRESHOLD_SHFT                         0x16
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_COARSE_LOCK_DET_NEG_THRESHOLD_BMSK            0x3c0000
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_COARSE_LOCK_DET_NEG_THRESHOLD_SHFT                0x12
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_COARSE_LOCK_DET_POS_THRESHOLD_BMSK             0x3c000
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_COARSE_LOCK_DET_POS_THRESHOLD_SHFT                 0xe
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_FINE_LOCK_DET_THRESHOLD_BMSK                    0x3800
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_FINE_LOCK_DET_THRESHOLD_SHFT                       0xb
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_FINE_LOCK_DET_SAMPLE_SIZE_BMSK                   0x700
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_FINE_LOCK_DET_SAMPLE_SIZE_SHFT                     0x8
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_FWD_GAIN_SLEWING_KFN_BMSK                         0xf0
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_FWD_GAIN_SLEWING_KFN_SHFT                          0x4
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_FWD_GAIN_KFN_BMSK                                  0xf
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_FWD_GAIN_KFN_SHFT                                  0x0

#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_ADDR                                      (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000218)
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_OFFS                                      (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000218)
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_RMSK                                      0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_ADDR, HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_IN)
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_BIST_CFG_BMSK                             0xfff00000
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_BIST_CFG_SHFT                                   0x14
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_RESERVE_BITS19_12_BMSK                       0xff000
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_RESERVE_BITS19_12_SHFT                           0xc
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_NUM_STEPS_FAST_LOCK_BMSK                       0xc00
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_NUM_STEPS_FAST_LOCK_SHFT                         0xa
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_NUM_STEPS_FAST_LOCK_USE_12_STEPS_FVAL            0x0
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_NUM_STEPS_FAST_LOCK_USE_10_STEPS_FVAL            0x1
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_NUM_STEPS_FAST_LOCK_USE_8_STEPS_FVAL             0x2
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_NUM_STEPS_FAST_LOCK_USE_6_STEPS_FVAL             0x3
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_PREDIV_WHEN_CAL_BMSK                           0x380
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_PREDIV_WHEN_CAL_SHFT                             0x7
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_PREDIV_WHEN_CAL_DIVIDE_BY_1_FVAL                 0x0
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_PREDIV_WHEN_CAL_DIVIDE_BY_2_FVAL                 0x1
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_PREDIV_WHEN_CAL_DIVIDE_BY_4_FVAL                 0x3
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_PREDIV_WHEN_CAL_DIVIDE_BY_8_FVAL                 0x7
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_INC_MIN_GLITCH_THRESHOLD_4X_BMSK                0x40
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_INC_MIN_GLITCH_THRESHOLD_4X_SHFT                 0x6
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_INC_MIN_GLITCH_THRESHOLD_4X_MINIMUM_GLITCH_THRESHOLD_IS_NOT_INCREASED_FVAL        0x0
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_INC_MIN_GLITCH_THRESHOLD_4X_MINIMUM_GLITCH_THRESHOLD_IS_INCREASED_BY_4X_FVAL        0x1
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_MIN_GLITCH_THRESHOLD_BMSK                       0x30
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_MIN_GLITCH_THRESHOLD_SHFT                        0x4
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_MIN_GLITCH_THRESHOLD_MINIMUM_OF_4_FVAL           0x0
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_MIN_GLITCH_THRESHOLD_MINIMUM_OF_16_FVAL          0x1
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_MIN_GLITCH_THRESHOLD_MINIMUM_OF_128_FVAL         0x2
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_MIN_GLITCH_THRESHOLD_MINIMUM_OF_256_FVAL         0x3
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_USE_BOTH_REF_CLK_EDGE_BMSK                       0x8
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_USE_BOTH_REF_CLK_EDGE_SHFT                       0x3
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_USE_BOTH_REF_CLK_EDGE_USE_ONLY_THE_RISING_EDGE_FVAL        0x0
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_USE_BOTH_REF_CLK_EDGE_USE_BOTH_THE_RISING_AND_FALLING_EDGES_FVAL        0x1
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_BIAS_WARMUP_TIME_BMSK                            0x6
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_BIAS_WARMUP_TIME_SHFT                            0x1
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_BIAS_WARMUP_TIME_COUNT_0_IE_DO_NOT_WAIT_FVAL        0x0
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_BIAS_WARMUP_TIME_COUNT_1_REFERENCE_CYCLES_FVAL        0x1
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_BIAS_WARMUP_TIME_COUNT_7_REFERENCE_CYCLES_FVAL        0x2
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_BIAS_WARMUP_TIME_COUNT_15_REFERENCE_CYCLES_FVAL        0x3
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_DIV_LOCK_DET_THRESHOLDS_BMSK                     0x1
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_DIV_LOCK_DET_THRESHOLDS_SHFT                     0x0
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_DIV_LOCK_DET_THRESHOLDS_DISABLE_FVAL             0x0
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_U_DIV_LOCK_DET_THRESHOLDS_ENABLE_FVAL              0x1

#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ADDR                                          (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x0000021c)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OFFS                                          (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000021c)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_RMSK                                          0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ADDR, HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_IN)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ADD_REF_CYC_CALIB_STEPS_BMSK                  0xc0000000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ADD_REF_CYC_CALIB_STEPS_SHFT                        0x1e
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ADD_REF_CYC_CALIB_STEPS_ADD_0_CYCLES_FVAL            0x0
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ADD_REF_CYC_CALIB_STEPS_ADD_1_CYCLES_FVAL            0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ADD_REF_CYC_CALIB_STEPS_ADD_2_CYCLES_FVAL            0x2
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ADD_REF_CYC_CALIB_STEPS_ADD_4_CYCLES_FVAL            0x3
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_GLITCH_DETECTOR_COUNT_LIMIT_BMSK              0x30000000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_GLITCH_DETECTOR_COUNT_LIMIT_SHFT                    0x1c
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_GLITCH_DETECTOR_COUNT_LIMIT_LIMIT_OF_4_FVAL          0x0
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_GLITCH_DETECTOR_COUNT_LIMIT_LIMIT_OF_16_FVAL         0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_GLITCH_DETECTOR_COUNT_LIMIT_LIMIT_OF_32_FVAL         0x2
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_GLITCH_DETECTOR_COUNT_LIMIT_LIMIT_OF_128_FVAL        0x3
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_GLITCH_PREVENTION_DIS_BMSK                     0x8000000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_GLITCH_PREVENTION_DIS_SHFT                          0x1b
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_GLITCH_PREVENTION_DIS_GLITCH_DETECTOR_IS_ON_FVAL        0x0
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_GLITCH_PREVENTION_DIS_GLITCH_DETECTOR_IS_OFF_FVAL        0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_FINE_FCW_BMSK                                  0x7e00000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_FINE_FCW_SHFT                                       0x15
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OVERRIDE_FINE_FCW_BMSK                          0x100000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OVERRIDE_FINE_FCW_SHFT                              0x14
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OVERRIDE_FINE_FCW_DO_NOT_OVERRIDE_FVAL               0x0
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OVERRIDE_FINE_FCW_OVERRIDE_FVAL                      0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_COARSE_FCW_BMSK                                  0xff000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_COARSE_FCW_SHFT                                      0xc
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OVERRIDE_COARSE_FCW_BMSK                           0x800
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OVERRIDE_COARSE_FCW_SHFT                             0xb
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OVERRIDE_COARSE_FCW_DO_NOT_OVERRIDE_FVAL             0x0
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OVERRIDE_COARSE_FCW_OVERRIDE_FVAL                    0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_PROCESS_CALIB_WORD_BMSK                            0x700
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_PROCESS_CALIB_WORD_SHFT                              0x8
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OVERRIDE_CALIB_WORD_BMSK                            0x80
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OVERRIDE_CALIB_WORD_SHFT                             0x7
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OVERRIDE_CALIB_WORD_DO_NOT_OVERRIDE_FVAL             0x0
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OVERRIDE_CALIB_WORD_OVERRIDE_FVAL                    0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_DISABLE_LFSR_BMSK                                   0x40
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_DISABLE_LFSR_SHFT                                    0x6
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_DISABLE_LFSR_ENABLE_FVAL                             0x0
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_DISABLE_LFSR_DISABLE_FVAL                            0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ATEST1_SEL_BMSK                                     0x30
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ATEST1_SEL_SHFT                                      0x4
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ATEST0_SEL_BMSK                                      0xc
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ATEST0_SEL_SHFT                                      0x2
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ATEST1_EN_BMSK                                       0x2
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ATEST1_EN_SHFT                                       0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ATEST1_EN_DISABLE_FVAL                               0x0
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ATEST1_EN_ENABLE_FVAL                                0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ATEST0_EN_BMSK                                       0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ATEST0_EN_SHFT                                       0x0
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ATEST0_EN_DISABLE_FVAL                               0x0
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ATEST0_EN_ENABLE_FVAL                                0x1

#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_ADDR                                        (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000220)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_OFFS                                        (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000220)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_RMSK                                        0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_ADDR, HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_IN)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_ENABLE_TRAINING_SEQ_BMSK                    0x80000000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_ENABLE_TRAINING_SEQ_SHFT                          0x1f
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_ENABLE_TRAINING_SEQ_NO_TRAINING_SEQUENCE_FVAL        0x0
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_ENABLE_TRAINING_SEQ_ENABLE_TRAINING_SEQUENCE_FVAL        0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_BYPASS_LOGIC_DEP_BMSK                       0x40000000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_BYPASS_LOGIC_DEP_SHFT                             0x1e
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_BYPASS_LOGIC_DEP_ENABLE_DCO_IS_GATED_BY_EN_BIAS_FVAL        0x0
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_BYPASS_LOGIC_DEP_NO_DEPENDENCY_FVAL                0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_BYPASS_BIAS_DET_BMSK                        0x20000000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_BYPASS_BIAS_DET_SHFT                              0x1d
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_MSB_CLOCK_SELECT_BMSK                       0x10000000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_MSB_CLOCK_SELECT_SHFT                             0x1c
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_MSB_CLOCK_SELECT_ODD_DIVIDER_OUTPUT_FVAL           0x0
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_MSB_CLOCK_SELECT_EVEN_DIVIDER_OUTPUT_FVAL          0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_BYPASS_FIRST_ORDER_DSM_BMSK                  0x8000000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_BYPASS_FIRST_ORDER_DSM_SHFT                       0x1b
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_BYPASS_FIRST_ORDER_DSM_DO_NOT_BYPASS_FVAL          0x0
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_BYPASS_FIRST_ORDER_DSM_BYPASS_FVAL                 0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_DCO_OFFSET_CURRENT_ADJUST_BMSK               0x6000000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_DCO_OFFSET_CURRENT_ADJUST_SHFT                    0x19
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_MIRROR_DEVICE_ADJUST_BMSK                    0x1c00000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_MIRROR_DEVICE_ADJUST_SHFT                         0x16
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_BIAS_STARTUP_CIR_DIS_BMSK                     0x200000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_BIAS_STARTUP_CIR_DIS_SHFT                         0x15
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_BIAS_STARTUP_CIR_DIS_ENABLE_FVAL                   0x0
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_BIAS_STARTUP_CIR_DIS_DISABLE_FVAL                  0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_DISABLE_CLAMP_BMSK                            0x100000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_DISABLE_CLAMP_SHFT                                0x14
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_DISABLE_CLAMP_ENABLE_FVAL                          0x0
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_DISABLE_CLAMP_DISABLE_FVAL                         0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_BYPASS_MODE_OF_BIAS_BMSK                       0x80000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_BYPASS_MODE_OF_BIAS_SHFT                          0x13
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_BYPASS_MODE_OF_BIAS_USE_EXTERNAL_CURRENT_AS_A_REFERENCE_FVAL        0x0
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_BYPASS_MODE_OF_BIAS_OUTPUT_BANDGAP_CURRENT_AS_A_CURRENT_SINK_FVAL        0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_BYPASS_MODE_FOR_BIAS_EN_BMSK                   0x40000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_BYPASS_MODE_FOR_BIAS_EN_SHFT                      0x12
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_BYPASS_MODE_FOR_BIAS_EN_DO_NOT_BYPASS_FVAL         0x0
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_BYPASS_MODE_FOR_BIAS_EN_BYPASS_ENABLED_FVAL        0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_BIAS_ADJUST_BMSK                               0x30000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_BIAS_ADJUST_SHFT                                  0x10
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_BIAS_ADJUST_NEGATIVE_FVAL                          0x0
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_BIAS_ADJUST_LESS_NEGATIVE_FVAL                     0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_BIAS_ADJUST_EVEN_LESS_NEGATIVE_FVAL                0x2
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_BIAS_ADJUST_ZERO_TEMPERATURE_COEFFICENT_FVAL        0x3
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_DIV2_NMO_EN_BMSK                                0x8000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_DIV2_NMO_EN_SHFT                                   0xf
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_DIV2_NMO_EN_DISABLE_FVAL                           0x0
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_DIV2_NMO_EN_ENABLE_FVAL                            0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_DIS_LEAK_CMP_BMSK                               0x4000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_DIS_LEAK_CMP_SHFT                                  0xe
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_DIS_LEAK_CMP_ENABLE_FVAL                           0x0
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_DIS_LEAK_CMP_DISABLE_FVAL                          0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_SINGLE_DMET_EN_BMSK                             0x2000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_SINGLE_DMET_EN_SHFT                                0xd
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_SINGLE_DMET_EN_DISABLE_FVAL                        0x0
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_SINGLE_DMET_EN_ENABLE_FVAL                         0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_DEMET_WINDOW_DIS_BMSK                           0x1000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_DEMET_WINDOW_DIS_SHFT                              0xc
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_DEMET_WINDOW_DIS_ENABLE_FVAL                       0x0
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_DEMET_WINDOW_DIS_DISABLE_FVAL                      0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NMO_OSC_SEL_BMSK                                 0xc00
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NMO_OSC_SEL_SHFT                                   0xa
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NMO_OSC_SEL_OFF_FVAL                               0x0
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NMO_OSC_SEL_FREQ_OF_350MHZ_FVAL                    0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NMO_OSC_SEL_FREQ_OF_700MHZ_FVAL                    0x2
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NMO_OSC_SEL_FREQ_OF_1400MHZ_FVAL                   0x3
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NOISE_MAG_BMSK                                   0x380
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NOISE_MAG_SHFT                                     0x7
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NOISE_MAG_OFF_FVAL                                 0x0
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NOISE_MAG_NOISE_OF_34MVRMS_FVAL                    0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NOISE_MAG_NOISE_OF_61MVRMS_FVAL                    0x3
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NOISE_MAG_NOISE_OF_72MVRMS_FVAL                    0x7
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NOISE_GEN_EN_BMSK                                 0x40
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NOISE_GEN_EN_SHFT                                  0x6
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NOISE_GEN_EN_DISABLE_FVAL                          0x0
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NOISE_GEN_EN_ENABLE_FVAL                           0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_OSC_BIAS_GND_BMSK                                 0x20
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_OSC_BIAS_GND_SHFT                                  0x5
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_OSC_BIAS_GND_NOT_GROUNDED_FVAL                     0x0
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_OSC_BIAS_GND_GROUNDED_FVAL                         0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_PLL_TEST_OUT_SEL_BMSK                             0x18
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_PLL_TEST_OUT_SEL_SHFT                              0x3
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_PLL_TEST_OUT_SEL_RESETN_FVAL                       0x0
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_PLL_TEST_OUT_SEL_NMO_OUTPUT_FVAL                   0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_PLL_TEST_OUT_SEL_DCO_CLOCK_WITHOUT_POST_DIVISION_FVAL        0x2
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_PLL_TEST_OUT_SEL_PLL_OUTPUT_SAME_AS_PLL_LV_MAIN_FVAL        0x3
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_STATUS_REG_EN_BMSK                                 0x4
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_STATUS_REG_EN_SHFT                                 0x2
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_STATUS_REG_EN_DISABLE_FVAL                         0x0
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_STATUS_REG_EN_ENABLE_FVAL                          0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_SKIP_FINE_TUNE_BMSK                                0x2
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_SKIP_FINE_TUNE_SHFT                                0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_SKIP_FINE_TUNE_PERFORM_FINE_TUNING_FVAL            0x0
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_SKIP_FINE_TUNE_SKIP_FINE_TUNING_FVAL               0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_SKIP_FAST_LOCK_BMSK                                0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_SKIP_FAST_LOCK_SHFT                                0x0
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_SKIP_FAST_LOCK_USE_FAST_LOCKING_FVAL               0x0
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_SKIP_FAST_LOCK_USE_LINEAR_LOCKING_FVAL             0x1

#define HWIO_LPASS_QDSP6SS_PLL_STATUS_ADDR                                            (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000224)
#define HWIO_LPASS_QDSP6SS_PLL_STATUS_OFFS                                            (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000224)
#define HWIO_LPASS_QDSP6SS_PLL_STATUS_RMSK                                            0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_STATUS_ADDR, HWIO_LPASS_QDSP6SS_PLL_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_STATUS_STATUS_31_0_BMSK                                0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_STATUS_STATUS_31_0_SHFT                                       0x0

#define HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_ADDR                                          (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000228)
#define HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_OFFS                                          (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000228)
#define HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_RMSK                                          0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_ADDR, HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_IN)
#define HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_FREQUENCY_CTL_WORD_BMSK                       0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_FREQUENCY_CTL_WORD_SHFT                              0x0

#define HWIO_LPASS_QDSP6SS_PLL_OPMODE_ADDR                                            (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x0000022c)
#define HWIO_LPASS_QDSP6SS_PLL_OPMODE_OFFS                                            (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000022c)
#define HWIO_LPASS_QDSP6SS_PLL_OPMODE_RMSK                                                   0x7
#define HWIO_LPASS_QDSP6SS_PLL_OPMODE_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_OPMODE_ADDR, HWIO_LPASS_QDSP6SS_PLL_OPMODE_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_OPMODE_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_OPMODE_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_OPMODE_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_OPMODE_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_OPMODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_OPMODE_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_OPMODE_IN)
#define HWIO_LPASS_QDSP6SS_PLL_OPMODE_PLL_OPMODE_BMSK                                        0x7
#define HWIO_LPASS_QDSP6SS_PLL_OPMODE_PLL_OPMODE_SHFT                                        0x0
#define HWIO_LPASS_QDSP6SS_PLL_OPMODE_PLL_OPMODE_STANDBY_FVAL                                0x0
#define HWIO_LPASS_QDSP6SS_PLL_OPMODE_PLL_OPMODE_RUN_FVAL                                    0x1
#define HWIO_LPASS_QDSP6SS_PLL_OPMODE_PLL_OPMODE_NA_FVAL                                     0x2
#define HWIO_LPASS_QDSP6SS_PLL_OPMODE_PLL_OPMODE_FREEZE_FVAL                                 0x3

#define HWIO_LPASS_QDSP6SS_PLL_STATE_ADDR                                             (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000230)
#define HWIO_LPASS_QDSP6SS_PLL_STATE_OFFS                                             (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000230)
#define HWIO_LPASS_QDSP6SS_PLL_STATE_RMSK                                                    0x7
#define HWIO_LPASS_QDSP6SS_PLL_STATE_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_STATE_ADDR, HWIO_LPASS_QDSP6SS_PLL_STATE_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_STATE_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_STATE_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_STATE_PLL_STATE_BMSK                                          0x7
#define HWIO_LPASS_QDSP6SS_PLL_STATE_PLL_STATE_SHFT                                          0x0

#define HWIO_LPASS_QDSP6SS_PLL_DROOP_ADDR                                             (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000234)
#define HWIO_LPASS_QDSP6SS_PLL_DROOP_OFFS                                             (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000234)
#define HWIO_LPASS_QDSP6SS_PLL_DROOP_RMSK                                                   0xff
#define HWIO_LPASS_QDSP6SS_PLL_DROOP_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_DROOP_ADDR, HWIO_LPASS_QDSP6SS_PLL_DROOP_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_DROOP_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_DROOP_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_DROOP_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_DROOP_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_DROOP_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_DROOP_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_DROOP_IN)
#define HWIO_LPASS_QDSP6SS_PLL_DROOP_DROOP_CODE_BMSK                                        0xfe
#define HWIO_LPASS_QDSP6SS_PLL_DROOP_DROOP_CODE_SHFT                                         0x1
#define HWIO_LPASS_QDSP6SS_PLL_DROOP_DROOP_EN_BMSK                                           0x1
#define HWIO_LPASS_QDSP6SS_PLL_DROOP_DROOP_EN_SHFT                                           0x0

#define HWIO_LPASS_QDSP6SS_PLL_FRAC_VAL_ADDR                                          (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000238)
#define HWIO_LPASS_QDSP6SS_PLL_FRAC_VAL_OFFS                                          (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000238)
#define HWIO_LPASS_QDSP6SS_PLL_FRAC_VAL_RMSK                                              0xffff
#define HWIO_LPASS_QDSP6SS_PLL_FRAC_VAL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_FRAC_VAL_ADDR, HWIO_LPASS_QDSP6SS_PLL_FRAC_VAL_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_FRAC_VAL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_FRAC_VAL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_FRAC_VAL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_FRAC_VAL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_FRAC_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_FRAC_VAL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_FRAC_VAL_IN)
#define HWIO_LPASS_QDSP6SS_PLL_FRAC_VAL_PLL_FRAC_VAL_BMSK                                 0xffff
#define HWIO_LPASS_QDSP6SS_PLL_FRAC_VAL_PLL_FRAC_VAL_SHFT                                    0x0

#define HWIO_LPASS_QDSP6SS_PLL_SPARE_ADDR                                             (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x0000023c)
#define HWIO_LPASS_QDSP6SS_PLL_SPARE_OFFS                                             (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000023c)
#define HWIO_LPASS_QDSP6SS_PLL_SPARE_RMSK                                                   0xff
#define HWIO_LPASS_QDSP6SS_PLL_SPARE_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_SPARE_ADDR, HWIO_LPASS_QDSP6SS_PLL_SPARE_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_SPARE_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_SPARE_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_SPARE_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_SPARE_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_SPARE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_SPARE_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_SPARE_IN)
#define HWIO_LPASS_QDSP6SS_PLL_SPARE_SPARE_OUTPUTS_BMSK                                     0xf0
#define HWIO_LPASS_QDSP6SS_PLL_SPARE_SPARE_OUTPUTS_SHFT                                      0x4
#define HWIO_LPASS_QDSP6SS_PLL_SPARE_SPARE_INPUTS_BMSK                                       0xf
#define HWIO_LPASS_QDSP6SS_PLL_SPARE_SPARE_INPUTS_SHFT                                       0x0

#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_STATUS_ADDR                                 (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000240)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_STATUS_OFFS                                 (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000240)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_STATUS_RMSK                                        0x3
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_STATUS_ADDR, HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_STATUS_RCG2PLL_UPD_STATUS_BMSK                     0x2
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_STATUS_RCG2PLL_UPD_STATUS_SHFT                     0x1
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_STATUS_PLL2RCG_UPD_STATUS_BMSK                     0x1
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_STATUS_PLL2RCG_UPD_STATUS_SHFT                     0x0

#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_ADDR                                    (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000244)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_OFFS                                    (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000244)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_RMSK                                           0x3
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_ADDR, HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_IN)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_RCG2PLL_UPD_EN_BMSK                            0x2
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_RCG2PLL_UPD_EN_SHFT                            0x1
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_PLL2RCG_UPD_EN_BMSK                            0x1
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_PLL2RCG_UPD_EN_SHFT                            0x0

#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_ADDR                                 (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000248)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_OFFS                                 (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000248)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_RMSK                                       0x1f
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_ADDR, HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_IN)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_MATCH_VALUE_BMSK                           0x1f
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_MATCH_VALUE_SHFT                            0x0

#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CMD_ADDR                                    (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x0000024c)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CMD_OFFS                                    (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000024c)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CMD_RMSK                                           0x1
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CMD_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CMD_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CMD_CMD_BMSK                                       0x1
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CMD_CMD_SHFT                                       0x0

#define HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_ADDR                                           (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000300)
#define HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_OFFS                                           (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000300)
#define HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_RMSK                                                  0x7
#define HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_ADDR, HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_RMSK)
#define HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_ADDR, m)
#define HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_ADDR,v)
#define HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_ADDR,m,v,HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_IN)
#define HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_DBG_NMI_EN_IN_PWR_COLLAPSE_BMSK                       0x4
#define HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_DBG_NMI_EN_IN_PWR_COLLAPSE_SHFT                       0x2
#define HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_DBG_NMI_DISABLE_BMSK                                  0x2
#define HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_DBG_NMI_DISABLE_SHFT                                  0x1
#define HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_DBG_NMI_WAKEUP_DISABLE_BMSK                           0x1
#define HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_DBG_NMI_WAKEUP_DISABLE_SHFT                           0x0

#define HWIO_LPASS_QDSP6SS_DBG_NMI_PWR_STATUS_ADDR                                    (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000304)
#define HWIO_LPASS_QDSP6SS_DBG_NMI_PWR_STATUS_OFFS                                    (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000304)
#define HWIO_LPASS_QDSP6SS_DBG_NMI_PWR_STATUS_RMSK                                           0x3
#define HWIO_LPASS_QDSP6SS_DBG_NMI_PWR_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_DBG_NMI_PWR_STATUS_ADDR, HWIO_LPASS_QDSP6SS_DBG_NMI_PWR_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_DBG_NMI_PWR_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_DBG_NMI_PWR_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_DBG_NMI_PWR_STATUS_QDSP6_PWR_COLLAPSE_BMSK                        0x2
#define HWIO_LPASS_QDSP6SS_DBG_NMI_PWR_STATUS_QDSP6_PWR_COLLAPSE_SHFT                        0x1
#define HWIO_LPASS_QDSP6SS_DBG_NMI_PWR_STATUS_QDSP6_IN_SLEEP_BMSK                            0x1
#define HWIO_LPASS_QDSP6SS_DBG_NMI_PWR_STATUS_QDSP6_IN_SLEEP_SHFT                            0x0

#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_ADDR                                          (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00002000)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_OFFS                                          (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00002000)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_RMSK                                          0xffffffff
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_ADDR, HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_IN)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_SPARE_CFG_BMSK                                0xff000000
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_SPARE_CFG_SHFT                                      0x18
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_HWE_INV_BMSK                                    0x800000
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_HWE_INV_SHFT                                        0x17
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_HWE_SEL_BMSK                                    0x7c0000
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_HWE_SEL_SHFT                                        0x12
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_TESTBUS_EN_BMSK                                  0x20000
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_TESTBUS_EN_SHFT                                     0x11
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_Q6_SEL_BMSK                                      0x10000
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_Q6_SEL_SHFT                                         0x10
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_SEL_BMSK                                          0xffff
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_SEL_SHFT                                             0x0

#define HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_ADDR                                        (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00002004)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_OFFS                                        (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00002004)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_RMSK                                        0xffffffff
#define HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_ADDR, HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_RMSK)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_ADDR, m)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_VALUE_BMSK                                  0xffffffff
#define HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_VALUE_SHFT                                         0x0

#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_ADDR                                        (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00002008)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_OFFS                                        (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00002008)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_RMSK                                        0xffffffff
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_ADDR, HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_RMSK)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_ADDR, m)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_ADDR,v)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_ADDR,m,v,HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_IN)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_VALUE_BMSK                                  0xffffffff
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_VALUE_SHFT                                         0x0

#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_ADDR                                            (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x0000200c)
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_OFFS                                            (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000200c)
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_RMSK                                                   0x1
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PWRDBG_CTL_ADDR, HWIO_LPASS_QDSP6SS_PWRDBG_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PWRDBG_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PWRDBG_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PWRDBG_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PWRDBG_CTL_IN)
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_ENA_BMSK                                               0x1
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_ENA_SHFT                                               0x0

#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_ADDR                                          (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00002010)
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_OFFS                                          (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00002010)
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_RMSK                                                0x7f
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_ADDR, HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_IN)
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_Q6_DBG_CLK_EN_BMSK                                  0x40
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_Q6_DBG_CLK_EN_SHFT                                   0x6
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_Q6_DBG_CLK_INV_BMSK                                 0x20
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_Q6_DBG_CLK_INV_SHFT                                  0x5
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_DBG_CLK_SEL_BMSK                                    0x1f
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_DBG_CLK_SEL_SHFT                                     0x0

#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ADDR                                          (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00002018)
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_OFFS                                          (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00002018)
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_RMSK                                            0xffffff
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ADDR, HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_RMSK)
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ADDR, m)
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ADDR,v)
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ADDR,m,v,HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_IN)
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_COUNT_BMSK                                0xffffe0
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_COUNT_SHFT                                     0x5
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_MUX_SEL_BMSK                                        0x10
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_MUX_SEL_SHFT                                         0x4
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_CLK_R_ENA_BMSK                                 0x8
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_CLK_R_ENA_SHFT                                 0x3
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_CGC_EN_BMSK                                    0x4
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_CGC_EN_SHFT                                    0x2
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_BYPASS_BMSK                                    0x2
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_BYPASS_SHFT                                    0x1
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_SW_RESET_BMSK                                  0x1
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_SW_RESET_SHFT                                  0x0

#define HWIO_LPASS_QDSP6SS_LDO_TEST_ADDR                                              (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x0000201c)
#define HWIO_LPASS_QDSP6SS_LDO_TEST_OFFS                                              (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000201c)
#define HWIO_LPASS_QDSP6SS_LDO_TEST_RMSK                                              0xffffffff
#define HWIO_LPASS_QDSP6SS_LDO_TEST_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_TEST_ADDR, HWIO_LPASS_QDSP6SS_LDO_TEST_RMSK)
#define HWIO_LPASS_QDSP6SS_LDO_TEST_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_LDO_TEST_ADDR, m)
#define HWIO_LPASS_QDSP6SS_LDO_TEST_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_LDO_TEST_ADDR,v)
#define HWIO_LPASS_QDSP6SS_LDO_TEST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_LDO_TEST_ADDR,m,v,HWIO_LPASS_QDSP6SS_LDO_TEST_IN)
#define HWIO_LPASS_QDSP6SS_LDO_TEST_DATA_BMSK                                         0xffffffff
#define HWIO_LPASS_QDSP6SS_LDO_TEST_DATA_SHFT                                                0x0

#define HWIO_LPASS_QDSP6SS_CORE_STATUS_ADDR                                           (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00002028)
#define HWIO_LPASS_QDSP6SS_CORE_STATUS_OFFS                                           (LPASS_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00002028)
#define HWIO_LPASS_QDSP6SS_CORE_STATUS_RMSK                                                  0x7
#define HWIO_LPASS_QDSP6SS_CORE_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CORE_STATUS_ADDR, HWIO_LPASS_QDSP6SS_CORE_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_CORE_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CORE_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CORE_STATUS_CP0_IDLE_BMSK                                         0x4
#define HWIO_LPASS_QDSP6SS_CORE_STATUS_CP0_IDLE_SHFT                                         0x2
#define HWIO_LPASS_QDSP6SS_CORE_STATUS_CORE_IN_SLEEP_BMSK                                    0x2
#define HWIO_LPASS_QDSP6SS_CORE_STATUS_CORE_IN_SLEEP_SHFT                                    0x1
#define HWIO_LPASS_QDSP6SS_CORE_STATUS_CORE_STATE_BMSK                                       0x1
#define HWIO_LPASS_QDSP6SS_CORE_STATUS_CORE_STATE_SHFT                                       0x0


#endif /* __CLOCKLPASSHWIO_H__ */
