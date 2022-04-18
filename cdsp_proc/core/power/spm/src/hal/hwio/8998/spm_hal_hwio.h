#ifndef __SPM_HAL_HWIO_H__
#define __SPM_HAL_HWIO_H__
/*
===========================================================================
*/
/**
  @file spm_hal_hwio.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    MSM8998 (Nazgul) [nazgul_v1.0_p1q1r15.0.0]
 
  This file contains HWIO register definitions for the following modules:
    LPASS_QDSP6SS_SAW4_SPM
    LPASS_QDSP6SS_SAW4_STS
    LPASS_QDSP6SS_SAW4_AVS

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

  $Header: //components/rel/core.qdsp6/1.0.c2/power/spm/src/hal/hwio/8998/spm_hal_hwio.h#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $

  ===========================================================================
*/

extern uint8 *g_spmBasePtrAddress;

#define LPASS_BASE (uint32)g_spmBasePtrAddress

/*----------------------------------------------------------------------------
 * MODULE: LPASS_QDSP6SS_SAW4_SPM
 *--------------------------------------------------------------------------*/

#define LPASS_QDSP6SS_SAW4_SPM_REG_BASE                                (LPASS_BASE      + 0x003b0000)

#define HWIO_LPASS_QDSP6SS_SAW4_SPM_CTL_ADDR                           (LPASS_QDSP6SS_SAW4_SPM_REG_BASE      + 0x00000000)
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_CTL_RMSK                           0xff7e1fff
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SAW4_SPM_CTL_ADDR, HWIO_LPASS_QDSP6SS_SAW4_SPM_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SAW4_SPM_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SAW4_SPM_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SAW4_SPM_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_SAW4_SPM_CTL_IN)
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_CTL_EVENT_SYNC_BMSK                0xff000000
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_CTL_EVENT_SYNC_SHFT                      0x18
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_CTL_PWR_STATE_IDX_BMSK               0x700000
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_CTL_PWR_STATE_IDX_SHFT                   0x14
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_CTL_SLEEP_REQ_BMSK                    0x80000
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_CTL_SLEEP_REQ_SHFT                       0x13
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_CTL_WAKEUP_REQ_BMSK                   0x40000
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_CTL_WAKEUP_REQ_SHFT                      0x12
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_CTL_SLP_CMD_MODE_BMSK                 0x20000
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_CTL_SLP_CMD_MODE_SHFT                    0x11
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_CTL_SPM_START_ADR_BMSK                 0x1ff0
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_CTL_SPM_START_ADR_SHFT                    0x4
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_CTL_ISAR_BMSK                             0x8
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_CTL_ISAR_SHFT                             0x3
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_CTL_WAKEUP_CONFIG_BMSK                    0x6
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_CTL_WAKEUP_CONFIG_SHFT                    0x1
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_CTL_SPM_EN_BMSK                           0x1
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_CTL_SPM_EN_SHFT                           0x0

#define HWIO_LPASS_QDSP6SS_SAW4_SPM_DLY_ADDR                           (LPASS_QDSP6SS_SAW4_SPM_REG_BASE      + 0x00000004)
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_DLY_RMSK                           0x3fffffff
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_DLY_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SAW4_SPM_DLY_ADDR, HWIO_LPASS_QDSP6SS_SAW4_SPM_DLY_RMSK)
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_DLY_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SAW4_SPM_DLY_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_DLY_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SAW4_SPM_DLY_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_DLY_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SAW4_SPM_DLY_ADDR,m,v,HWIO_LPASS_QDSP6SS_SAW4_SPM_DLY_IN)
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_DLY_DLY3_BMSK                      0x3ff00000
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_DLY_DLY3_SHFT                            0x14
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_DLY_DLY2_BMSK                         0xffc00
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_DLY_DLY2_SHFT                             0xa
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_DLY_DLY1_BMSK                           0x3ff
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_DLY_DLY1_SHFT                             0x0

#define HWIO_LPASS_QDSP6SS_SAW4_SPM_WAKEUP_CNT_ADDR                    (LPASS_QDSP6SS_SAW4_SPM_REG_BASE      + 0x00000008)
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_WAKEUP_CNT_RMSK                    0xffffffff
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_WAKEUP_CNT_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SAW4_SPM_WAKEUP_CNT_ADDR, HWIO_LPASS_QDSP6SS_SAW4_SPM_WAKEUP_CNT_RMSK)
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_WAKEUP_CNT_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SAW4_SPM_WAKEUP_CNT_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_WAKEUP_CNT_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SAW4_SPM_WAKEUP_CNT_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_WAKEUP_CNT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SAW4_SPM_WAKEUP_CNT_ADDR,m,v,HWIO_LPASS_QDSP6SS_SAW4_SPM_WAKEUP_CNT_IN)
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_WAKEUP_CNT_CNT_BMSK                0xffffffff
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_WAKEUP_CNT_CNT_SHFT                       0x0

#define HWIO_LPASS_QDSP6SS_SAW4_CFG_ADDR                               (LPASS_QDSP6SS_SAW4_SPM_REG_BASE      + 0x0000000c)
#define HWIO_LPASS_QDSP6SS_SAW4_CFG_RMSK                                    0x31f
#define HWIO_LPASS_QDSP6SS_SAW4_CFG_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SAW4_CFG_ADDR, HWIO_LPASS_QDSP6SS_SAW4_CFG_RMSK)
#define HWIO_LPASS_QDSP6SS_SAW4_CFG_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SAW4_CFG_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SAW4_CFG_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SAW4_CFG_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SAW4_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SAW4_CFG_ADDR,m,v,HWIO_LPASS_QDSP6SS_SAW4_CFG_IN)
#define HWIO_LPASS_QDSP6SS_SAW4_CFG_TEST_BUS_EN_BMSK                        0x200
#define HWIO_LPASS_QDSP6SS_SAW4_CFG_TEST_BUS_EN_SHFT                          0x9
#define HWIO_LPASS_QDSP6SS_SAW4_CFG_FRC_REF_CLK_ON_BMSK                     0x100
#define HWIO_LPASS_QDSP6SS_SAW4_CFG_FRC_REF_CLK_ON_SHFT                       0x8
#define HWIO_LPASS_QDSP6SS_SAW4_CFG_CLK_DIV_BMSK                             0x1f
#define HWIO_LPASS_QDSP6SS_SAW4_CFG_CLK_DIV_SHFT                              0x0

#define HWIO_LPASS_QDSP6SS_SAW4_SPM_SLP_SEQ_ENTRY_n_ADDR(n)            (LPASS_QDSP6SS_SAW4_SPM_REG_BASE      + 0x00000400 + 0x4 * (n))
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_SLP_SEQ_ENTRY_n_RMSK               0xffffffff
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_SLP_SEQ_ENTRY_n_MAXn                       31
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_SLP_SEQ_ENTRY_n_INI(n)        \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SAW4_SPM_SLP_SEQ_ENTRY_n_ADDR(n), HWIO_LPASS_QDSP6SS_SAW4_SPM_SLP_SEQ_ENTRY_n_RMSK)
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_SLP_SEQ_ENTRY_n_INMI(n,mask)    \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SAW4_SPM_SLP_SEQ_ENTRY_n_ADDR(n), mask)
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_SLP_SEQ_ENTRY_n_OUTI(n,val)    \
        out_dword(HWIO_LPASS_QDSP6SS_SAW4_SPM_SLP_SEQ_ENTRY_n_ADDR(n),val)
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_SLP_SEQ_ENTRY_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SAW4_SPM_SLP_SEQ_ENTRY_n_ADDR(n),mask,val,HWIO_LPASS_QDSP6SS_SAW4_SPM_SLP_SEQ_ENTRY_n_INI(n))
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_SLP_SEQ_ENTRY_n_CMD3_BMSK          0xff000000
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_SLP_SEQ_ENTRY_n_CMD3_SHFT                0x18
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_SLP_SEQ_ENTRY_n_CMD2_BMSK            0xff0000
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_SLP_SEQ_ENTRY_n_CMD2_SHFT                0x10
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_SLP_SEQ_ENTRY_n_CMD1_BMSK              0xff00
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_SLP_SEQ_ENTRY_n_CMD1_SHFT                 0x8
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_SLP_SEQ_ENTRY_n_CMD0_BMSK                0xff
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_SLP_SEQ_ENTRY_n_CMD0_SHFT                 0x0

/*----------------------------------------------------------------------------
 * MODULE: LPASS_QDSP6SS_SAW4_STS
 *--------------------------------------------------------------------------*/

#define LPASS_QDSP6SS_SAW4_STS_REG_BASE                                   (LPASS_BASE      + 0x003b0c00)

#define HWIO_LPASS_QDSP6SS_SAW4_SECURE_ADDR                               (LPASS_QDSP6SS_SAW4_STS_REG_BASE      + 0x00000000)
#define HWIO_LPASS_QDSP6SS_SAW4_SECURE_RMSK                                      0x7
#define HWIO_LPASS_QDSP6SS_SAW4_SECURE_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SAW4_SECURE_ADDR, HWIO_LPASS_QDSP6SS_SAW4_SECURE_RMSK)
#define HWIO_LPASS_QDSP6SS_SAW4_SECURE_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SAW4_SECURE_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SAW4_SECURE_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SAW4_SECURE_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SAW4_SECURE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SAW4_SECURE_ADDR,m,v,HWIO_LPASS_QDSP6SS_SAW4_SECURE_IN)
#define HWIO_LPASS_QDSP6SS_SAW4_SECURE_SAW_CTL_BMSK                              0x4
#define HWIO_LPASS_QDSP6SS_SAW4_SECURE_SAW_CTL_SHFT                              0x2
#define HWIO_LPASS_QDSP6SS_SAW4_SECURE_PWR_CTL_BMSK                              0x2
#define HWIO_LPASS_QDSP6SS_SAW4_SECURE_PWR_CTL_SHFT                              0x1
#define HWIO_LPASS_QDSP6SS_SAW4_SECURE_VLT_CTL_BMSK                              0x1
#define HWIO_LPASS_QDSP6SS_SAW4_SECURE_VLT_CTL_SHFT                              0x0

#define HWIO_LPASS_QDSP6SS_SAW4_ID_ADDR                                   (LPASS_QDSP6SS_SAW4_STS_REG_BASE      + 0x00000004)
#define HWIO_LPASS_QDSP6SS_SAW4_ID_RMSK                                   0xff3f1f7f
#define HWIO_LPASS_QDSP6SS_SAW4_ID_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SAW4_ID_ADDR, HWIO_LPASS_QDSP6SS_SAW4_ID_RMSK)
#define HWIO_LPASS_QDSP6SS_SAW4_ID_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SAW4_ID_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SAW4_ID_NUM_SPM_ENTRY_BMSK                     0xff000000
#define HWIO_LPASS_QDSP6SS_SAW4_ID_NUM_SPM_ENTRY_SHFT                           0x18
#define HWIO_LPASS_QDSP6SS_SAW4_ID_NUM_PWR_CTL_BMSK                         0x3f0000
#define HWIO_LPASS_QDSP6SS_SAW4_ID_NUM_PWR_CTL_SHFT                             0x10
#define HWIO_LPASS_QDSP6SS_SAW4_ID_NUM_CVS_PMIC_DATA_BMSK                     0x1c00
#define HWIO_LPASS_QDSP6SS_SAW4_ID_NUM_CVS_PMIC_DATA_SHFT                        0xa
#define HWIO_LPASS_QDSP6SS_SAW4_ID_CVS_PRESENT_BMSK                            0x200
#define HWIO_LPASS_QDSP6SS_SAW4_ID_CVS_PRESENT_SHFT                              0x9
#define HWIO_LPASS_QDSP6SS_SAW4_ID_PMIC_DATA_WIDTH_BMSK                        0x100
#define HWIO_LPASS_QDSP6SS_SAW4_ID_PMIC_DATA_WIDTH_SHFT                          0x8
#define HWIO_LPASS_QDSP6SS_SAW4_ID_NUM_SPM_PMIC_DATA_BMSK                       0x70
#define HWIO_LPASS_QDSP6SS_SAW4_ID_NUM_SPM_PMIC_DATA_SHFT                        0x4
#define HWIO_LPASS_QDSP6SS_SAW4_ID_CFG_NS_ACCESS_BMSK                            0x8
#define HWIO_LPASS_QDSP6SS_SAW4_ID_CFG_NS_ACCESS_SHFT                            0x3
#define HWIO_LPASS_QDSP6SS_SAW4_ID_PMIC_ARB_INTF_BMSK                            0x4
#define HWIO_LPASS_QDSP6SS_SAW4_ID_PMIC_ARB_INTF_SHFT                            0x2
#define HWIO_LPASS_QDSP6SS_SAW4_ID_AVS_PRESENT_BMSK                              0x2
#define HWIO_LPASS_QDSP6SS_SAW4_ID_AVS_PRESENT_SHFT                              0x1
#define HWIO_LPASS_QDSP6SS_SAW4_ID_SPM_PRESENT_BMSK                              0x1
#define HWIO_LPASS_QDSP6SS_SAW4_ID_SPM_PRESENT_SHFT                              0x0

#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS_ADDR                              (LPASS_QDSP6SS_SAW4_STS_REG_BASE      + 0x0000000c)
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS_RMSK                              0xffffffff
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SAW4_SPM_STS_ADDR, HWIO_LPASS_QDSP6SS_SAW4_SPM_STS_RMSK)
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SAW4_SPM_STS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS_SPM_EVENT_BMSK                    0xffff0000
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS_SPM_EVENT_SHFT                          0x10
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS_SHTDWN_REQ_BMSK                       0x8000
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS_SHTDWN_REQ_SHFT                          0xf
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS_SHTDWN_ACK_BMSK                       0x4000
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS_SHTDWN_ACK_SHFT                          0xe
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS_BRNGUP_REQ_BMSK                       0x2000
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS_BRNGUP_REQ_SHFT                          0xd
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS_BRNGUP_ACK_BMSK                       0x1000
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS_BRNGUP_ACK_SHFT                          0xc
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS_RPM_STATE_BMSK                         0xc00
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS_RPM_STATE_SHFT                           0xa
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS_SPM_BUSY_BMSK                          0x200
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS_SPM_BUSY_SHFT                            0x9
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS_SPM_CMD_ADDR_BMSK                      0x1ff
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS_SPM_CMD_ADDR_SHFT                        0x0

#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS2_ADDR                             (LPASS_QDSP6SS_SAW4_STS_REG_BASE      + 0x00000010)
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS2_RMSK                             0xffffffff
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS2_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SAW4_SPM_STS2_ADDR, HWIO_LPASS_QDSP6SS_SAW4_SPM_STS2_RMSK)
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS2_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SAW4_SPM_STS2_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS2_CURR_PWR_CTL_BMSK                0xffffffff
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS2_CURR_PWR_CTL_SHFT                       0x0

#define HWIO_LPASS_QDSP6SS_SAW4_AVS_STS_ADDR                              (LPASS_QDSP6SS_SAW4_STS_REG_BASE      + 0x00000014)
#define HWIO_LPASS_QDSP6SS_SAW4_AVS_STS_RMSK                              0x3ff00fff
#define HWIO_LPASS_QDSP6SS_SAW4_AVS_STS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SAW4_AVS_STS_ADDR, HWIO_LPASS_QDSP6SS_SAW4_AVS_STS_RMSK)
#define HWIO_LPASS_QDSP6SS_SAW4_AVS_STS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SAW4_AVS_STS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SAW4_AVS_STS_AVS_CURR_DLY_BMSK                 0x3ff00000
#define HWIO_LPASS_QDSP6SS_SAW4_AVS_STS_AVS_CURR_DLY_SHFT                       0x14
#define HWIO_LPASS_QDSP6SS_SAW4_AVS_STS_SIC_SW_DONE_IRQ_BMSK                   0x800
#define HWIO_LPASS_QDSP6SS_SAW4_AVS_STS_SIC_SW_DONE_IRQ_SHFT                     0xb
#define HWIO_LPASS_QDSP6SS_SAW4_AVS_STS_SIC_IRQ_BMSK                           0x400
#define HWIO_LPASS_QDSP6SS_SAW4_AVS_STS_SIC_IRQ_SHFT                             0xa
#define HWIO_LPASS_QDSP6SS_SAW4_AVS_STS_AVS_ERR_BMSK                           0x200
#define HWIO_LPASS_QDSP6SS_SAW4_AVS_STS_AVS_ERR_SHFT                             0x9
#define HWIO_LPASS_QDSP6SS_SAW4_AVS_STS_AVS_ACK_BMSK                           0x100
#define HWIO_LPASS_QDSP6SS_SAW4_AVS_STS_AVS_ACK_SHFT                             0x8
#define HWIO_LPASS_QDSP6SS_SAW4_AVS_STS_VOLTAGE_RAMP_BMSK                       0x80
#define HWIO_LPASS_QDSP6SS_SAW4_AVS_STS_VOLTAGE_RAMP_SHFT                        0x7
#define HWIO_LPASS_QDSP6SS_SAW4_AVS_STS_SW_WR_PEND_BMSK                         0x40
#define HWIO_LPASS_QDSP6SS_SAW4_AVS_STS_SW_WR_PEND_SHFT                          0x6
#define HWIO_LPASS_QDSP6SS_SAW4_AVS_STS_MAX_INT_BMSK                            0x20
#define HWIO_LPASS_QDSP6SS_SAW4_AVS_STS_MAX_INT_SHFT                             0x5
#define HWIO_LPASS_QDSP6SS_SAW4_AVS_STS_MIN_INT_BMSK                            0x10
#define HWIO_LPASS_QDSP6SS_SAW4_AVS_STS_MIN_INT_SHFT                             0x4
#define HWIO_LPASS_QDSP6SS_SAW4_AVS_STS_CPU_UP_BMSK                              0x8
#define HWIO_LPASS_QDSP6SS_SAW4_AVS_STS_CPU_UP_SHFT                              0x3
#define HWIO_LPASS_QDSP6SS_SAW4_AVS_STS_CPU_DN_BMSK                              0x4
#define HWIO_LPASS_QDSP6SS_SAW4_AVS_STS_CPU_DN_SHFT                              0x2
#define HWIO_LPASS_QDSP6SS_SAW4_AVS_STS_AVS_FSM_STATE_BMSK                       0x3
#define HWIO_LPASS_QDSP6SS_SAW4_AVS_STS_AVS_FSM_STATE_SHFT                       0x0

#define HWIO_LPASS_QDSP6SS_SAW4_PMIC_STS_ADDR                             (LPASS_QDSP6SS_SAW4_STS_REG_BASE      + 0x00000018)
#define HWIO_LPASS_QDSP6SS_SAW4_PMIC_STS_RMSK                               0xff00ff
#define HWIO_LPASS_QDSP6SS_SAW4_PMIC_STS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SAW4_PMIC_STS_ADDR, HWIO_LPASS_QDSP6SS_SAW4_PMIC_STS_RMSK)
#define HWIO_LPASS_QDSP6SS_SAW4_PMIC_STS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SAW4_PMIC_STS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SAW4_PMIC_STS_PMIC_DONE_BMSK                     0x800000
#define HWIO_LPASS_QDSP6SS_SAW4_PMIC_STS_PMIC_DONE_SHFT                         0x17
#define HWIO_LPASS_QDSP6SS_SAW4_PMIC_STS_PMIC_REQ_BMSK                      0x400000
#define HWIO_LPASS_QDSP6SS_SAW4_PMIC_STS_PMIC_REQ_SHFT                          0x16
#define HWIO_LPASS_QDSP6SS_SAW4_PMIC_STS_CURR_PMIC_ADDR_IDX_BMSK            0x380000
#define HWIO_LPASS_QDSP6SS_SAW4_PMIC_STS_CURR_PMIC_ADDR_IDX_SHFT                0x13
#define HWIO_LPASS_QDSP6SS_SAW4_PMIC_STS_CURR_PMIC_SIZE_BMSK                 0x40000
#define HWIO_LPASS_QDSP6SS_SAW4_PMIC_STS_CURR_PMIC_SIZE_SHFT                    0x12
#define HWIO_LPASS_QDSP6SS_SAW4_PMIC_STS_PMIC_STATE_BMSK                     0x30000
#define HWIO_LPASS_QDSP6SS_SAW4_PMIC_STS_PMIC_STATE_SHFT                        0x10
#define HWIO_LPASS_QDSP6SS_SAW4_PMIC_STS_CURR_PMIC_DATA_BMSK                    0xff
#define HWIO_LPASS_QDSP6SS_SAW4_PMIC_STS_CURR_PMIC_DATA_SHFT                     0x0

#define HWIO_LPASS_QDSP6SS_SAW4_RST_ADDR                                  (LPASS_QDSP6SS_SAW4_STS_REG_BASE      + 0x0000001c)
#define HWIO_LPASS_QDSP6SS_SAW4_RST_RMSK                                         0x1
#define HWIO_LPASS_QDSP6SS_SAW4_RST_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SAW4_RST_ADDR, HWIO_LPASS_QDSP6SS_SAW4_RST_RMSK)
#define HWIO_LPASS_QDSP6SS_SAW4_RST_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SAW4_RST_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SAW4_RST_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SAW4_RST_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SAW4_RST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SAW4_RST_ADDR,m,v,HWIO_LPASS_QDSP6SS_SAW4_RST_IN)
#define HWIO_LPASS_QDSP6SS_SAW4_RST_RST_BMSK                                     0x1
#define HWIO_LPASS_QDSP6SS_SAW4_RST_RST_SHFT                                     0x0

#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS3_ADDR                             (LPASS_QDSP6SS_SAW4_STS_REG_BASE      + 0x00000020)
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS3_RMSK                             0x3ff0001f
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS3_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SAW4_SPM_STS3_ADDR, HWIO_LPASS_QDSP6SS_SAW4_SPM_STS3_RMSK)
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS3_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SAW4_SPM_STS3_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS3_SPM_CURR_DLY_BMSK                0x3ff00000
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS3_SPM_CURR_DLY_SHFT                      0x14
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS3_DBG_STAY_AWAKE_BMSK                    0x10
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS3_DBG_STAY_AWAKE_SHFT                     0x4
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS3_SLEEP_STATE_BMSK                        0x8
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS3_SLEEP_STATE_SHFT                        0x3
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS3_WAKEUP_BMSK                             0x4
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS3_WAKEUP_SHFT                             0x2
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS3_WAIT_ACK_BMSK                           0x2
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS3_WAIT_ACK_SHFT                           0x1
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS3_WAIT_REQ_BMSK                           0x1
#define HWIO_LPASS_QDSP6SS_SAW4_SPM_STS3_WAIT_REQ_SHFT                           0x0

#define HWIO_LPASS_QDSP6SS_SAW4_CVS_STS_ADDR                              (LPASS_QDSP6SS_SAW4_STS_REG_BASE      + 0x00000040)
#define HWIO_LPASS_QDSP6SS_SAW4_CVS_STS_RMSK                              0xffff03ff
#define HWIO_LPASS_QDSP6SS_SAW4_CVS_STS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SAW4_CVS_STS_ADDR, HWIO_LPASS_QDSP6SS_SAW4_CVS_STS_RMSK)
#define HWIO_LPASS_QDSP6SS_SAW4_CVS_STS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SAW4_CVS_STS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SAW4_CVS_STS_CVS_EVENT_BMSK                    0xffff0000
#define HWIO_LPASS_QDSP6SS_SAW4_CVS_STS_CVS_EVENT_SHFT                          0x10
#define HWIO_LPASS_QDSP6SS_SAW4_CVS_STS_CVS_BUSY_BMSK                          0x200
#define HWIO_LPASS_QDSP6SS_SAW4_CVS_STS_CVS_BUSY_SHFT                            0x9
#define HWIO_LPASS_QDSP6SS_SAW4_CVS_STS_CVS_CMD_ADDR_BMSK                      0x1ff
#define HWIO_LPASS_QDSP6SS_SAW4_CVS_STS_CVS_CMD_ADDR_SHFT                        0x0

#define HWIO_LPASS_QDSP6SS_SAW4_CVS_STS2_ADDR                             (LPASS_QDSP6SS_SAW4_STS_REG_BASE      + 0x00000044)
#define HWIO_LPASS_QDSP6SS_SAW4_CVS_STS2_RMSK                             0xffffffff
#define HWIO_LPASS_QDSP6SS_SAW4_CVS_STS2_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SAW4_CVS_STS2_ADDR, HWIO_LPASS_QDSP6SS_SAW4_CVS_STS2_RMSK)
#define HWIO_LPASS_QDSP6SS_SAW4_CVS_STS2_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SAW4_CVS_STS2_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SAW4_CVS_STS2_CVS_PWR_CTL_BMSK                 0xffffffff
#define HWIO_LPASS_QDSP6SS_SAW4_CVS_STS2_CVS_PWR_CTL_SHFT                        0x0

#define HWIO_LPASS_QDSP6SS_SAW4_VERSION_ADDR                              (LPASS_QDSP6SS_SAW4_STS_REG_BASE      + 0x000003d0)
#define HWIO_LPASS_QDSP6SS_SAW4_VERSION_RMSK                              0xffffffff
#define HWIO_LPASS_QDSP6SS_SAW4_VERSION_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SAW4_VERSION_ADDR, HWIO_LPASS_QDSP6SS_SAW4_VERSION_RMSK)
#define HWIO_LPASS_QDSP6SS_SAW4_VERSION_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SAW4_VERSION_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SAW4_VERSION_MAJOR_BMSK                        0xf0000000
#define HWIO_LPASS_QDSP6SS_SAW4_VERSION_MAJOR_SHFT                              0x1c
#define HWIO_LPASS_QDSP6SS_SAW4_VERSION_MINOR_BMSK                         0xfff0000
#define HWIO_LPASS_QDSP6SS_SAW4_VERSION_MINOR_SHFT                              0x10
#define HWIO_LPASS_QDSP6SS_SAW4_VERSION_STEP_BMSK                             0xffff
#define HWIO_LPASS_QDSP6SS_SAW4_VERSION_STEP_SHFT                                0x0

/*----------------------------------------------------------------------------
 * MODULE: LPASS_QDSP6SS_SAW4_AVS
 *--------------------------------------------------------------------------*/

#define LPASS_QDSP6SS_SAW4_AVS_REG_BASE (LPASS_BASE      + 0x003b0800)


#endif /* __SPM_HAL_HWIO_H__ */
