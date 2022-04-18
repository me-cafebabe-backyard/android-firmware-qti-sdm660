#ifndef __APCS_HANG_STATUS_HWIO_H__
#define __APCS_HANG_STATUS_HWIO_H__
/*
===========================================================================
*/
/**
  @file apcs_hang_status_hwio.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    SDM660 (Starlord) [starlord_v1.0_p1qxr28]
 
  This file contains HWIO register definitions for the following modules:
    APCS_COMMON_APSS_SHARED
    APCS_WDT_TMR1_APSS_WDT
    APCS_ALIAS0_APSS_ACS
    APCS_ALIAS1_APSS_ACS
    APCS_ALIAS2_APSS_ACS
    APCS_ALIAS3_APSS_ACS
    APCS_ALIAS4_APSS_ACS
    APCS_ALIAS5_APSS_ACS
    APCS_ALIAS6_APSS_ACS
    APCS_ALIAS7_APSS_ACS

  'Include' filters applied: CORE_HANG[APCS_ALIAS0_APSS_ACS] CORE_HANG[APCS_ALIAS3_APSS_ACS] CORE_HANG[APCS_ALIAS2_APSS_ACS] CORE_HANG[APCS_ALIAS1_APSS_ACS] CORE_HANG[APCS_ALIAS7_APSS_ACS] CORE_HANG[APCS_ALIAS6_APSS_ACS] CORE_HANG[APCS_ALIAS5_APSS_ACS] CORE_HANG[APCS_ALIAS4_APSS_ACS] 
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

  $Header: //components/rel/rpm.bf/1.8/core/bsp/rpm/target/660/apcs_hang_status_hwio.h#1 $
  $DateTime: 2016/11/03 00:13:13 $
  $Author: pwbldsvc $

  ===========================================================================
*/
//TODO: Check if this A53SS_base is proper for SL(660)
#define A53SS_BASE 0x77800000

/*----------------------------------------------------------------------------
 * MODULE: APCS_COMMON_APSS_SHARED
 *--------------------------------------------------------------------------*/

#define APCS_COMMON_APSS_SHARED_REG_BASE                                                     (A53SS_BASE      + 0x001d1000)

#define HWIO_APCS_COMMON_SHR_SECURE_ADDR                                                     (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000004)
#define HWIO_APCS_COMMON_SHR_SECURE_RMSK                                                            0xf
#define HWIO_APCS_COMMON_SHR_SECURE_IN          \
        in_dword_masked(HWIO_APCS_COMMON_SHR_SECURE_ADDR, HWIO_APCS_COMMON_SHR_SECURE_RMSK)
#define HWIO_APCS_COMMON_SHR_SECURE_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_SHR_SECURE_ADDR, m)
#define HWIO_APCS_COMMON_SHR_SECURE_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_SHR_SECURE_ADDR,v)
#define HWIO_APCS_COMMON_SHR_SECURE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_SHR_SECURE_ADDR,m,v,HWIO_APCS_COMMON_SHR_SECURE_IN)
#define HWIO_APCS_COMMON_SHR_SECURE_TST_BMSK                                                        0x8
#define HWIO_APCS_COMMON_SHR_SECURE_TST_SHFT                                                        0x3
#define HWIO_APCS_COMMON_SHR_SECURE_INTR_BMSK                                                       0x4
#define HWIO_APCS_COMMON_SHR_SECURE_INTR_SHFT                                                       0x2
#define HWIO_APCS_COMMON_SHR_SECURE_CLK_BMSK                                                        0x2
#define HWIO_APCS_COMMON_SHR_SECURE_CLK_SHFT                                                        0x1
#define HWIO_APCS_COMMON_SHR_SECURE_PWR_BMSK                                                        0x1
#define HWIO_APCS_COMMON_SHR_SECURE_PWR_SHFT                                                        0x0

#define HWIO_APCS_COMMON_CCI_INPUT_CFG_ADDR                                                  (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000100)
#define HWIO_APCS_COMMON_CCI_INPUT_CFG_RMSK                                                       0x7ff
#define HWIO_APCS_COMMON_CCI_INPUT_CFG_IN          \
        in_dword_masked(HWIO_APCS_COMMON_CCI_INPUT_CFG_ADDR, HWIO_APCS_COMMON_CCI_INPUT_CFG_RMSK)
#define HWIO_APCS_COMMON_CCI_INPUT_CFG_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_CCI_INPUT_CFG_ADDR, m)
#define HWIO_APCS_COMMON_CCI_INPUT_CFG_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_CCI_INPUT_CFG_ADDR,v)
#define HWIO_APCS_COMMON_CCI_INPUT_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_CCI_INPUT_CFG_ADDR,m,v,HWIO_APCS_COMMON_CCI_INPUT_CFG_IN)
#define HWIO_APCS_COMMON_CCI_INPUT_CFG_QOS_GOLD_SEL_BMSK                                          0x400
#define HWIO_APCS_COMMON_CCI_INPUT_CFG_QOS_GOLD_SEL_SHFT                                            0xa
#define HWIO_APCS_COMMON_CCI_INPUT_CFG_QOS_SILVER_SEL_BMSK                                        0x200
#define HWIO_APCS_COMMON_CCI_INPUT_CFG_QOS_SILVER_SEL_SHFT                                          0x9
#define HWIO_APCS_COMMON_CCI_INPUT_CFG_SYS_REDIRECT_DISABLE_BMSK                                  0x100
#define HWIO_APCS_COMMON_CCI_INPUT_CFG_SYS_REDIRECT_DISABLE_SHFT                                    0x8
#define HWIO_APCS_COMMON_CCI_INPUT_CFG_CFG_CLRMON_DISABLE_BMSK                                     0xc0
#define HWIO_APCS_COMMON_CCI_INPUT_CFG_CFG_CLRMON_DISABLE_SHFT                                      0x6
#define HWIO_APCS_COMMON_CCI_INPUT_CFG_CCI_TSREADY_FORCE_DISABLE_BMSK                              0x20
#define HWIO_APCS_COMMON_CCI_INPUT_CFG_CCI_TSREADY_FORCE_DISABLE_SHFT                               0x5
#define HWIO_APCS_COMMON_CCI_INPUT_CFG_CCI_CFG_STALL_ERROR_BMSK                                    0x10
#define HWIO_APCS_COMMON_CCI_INPUT_CFG_CCI_CFG_STALL_ERROR_SHFT                                     0x4
#define HWIO_APCS_COMMON_CCI_INPUT_CFG_PROTNSS2_BMSK                                                0x8
#define HWIO_APCS_COMMON_CCI_INPUT_CFG_PROTNSS2_SHFT                                                0x3
#define HWIO_APCS_COMMON_CCI_INPUT_CFG_PDXFIFOCNTDELAY_BMSK                                         0x7
#define HWIO_APCS_COMMON_CCI_INPUT_CFG_PDXFIFOCNTDELAY_SHFT                                         0x0

#define HWIO_APCS_COMMON_CCI_CMD_RCGR_ADDR                                                   (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000050)
#define HWIO_APCS_COMMON_CCI_CMD_RCGR_RMSK                                                   0x80000013
#define HWIO_APCS_COMMON_CCI_CMD_RCGR_IN          \
        in_dword_masked(HWIO_APCS_COMMON_CCI_CMD_RCGR_ADDR, HWIO_APCS_COMMON_CCI_CMD_RCGR_RMSK)
#define HWIO_APCS_COMMON_CCI_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_CCI_CMD_RCGR_ADDR, m)
#define HWIO_APCS_COMMON_CCI_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_CCI_CMD_RCGR_ADDR,v)
#define HWIO_APCS_COMMON_CCI_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_CCI_CMD_RCGR_ADDR,m,v,HWIO_APCS_COMMON_CCI_CMD_RCGR_IN)
#define HWIO_APCS_COMMON_CCI_CMD_RCGR_ROOT_OFF_BMSK                                          0x80000000
#define HWIO_APCS_COMMON_CCI_CMD_RCGR_ROOT_OFF_SHFT                                                0x1f
#define HWIO_APCS_COMMON_CCI_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                          0x10
#define HWIO_APCS_COMMON_CCI_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                           0x4
#define HWIO_APCS_COMMON_CCI_CMD_RCGR_ROOT_EN_BMSK                                                  0x2
#define HWIO_APCS_COMMON_CCI_CMD_RCGR_ROOT_EN_SHFT                                                  0x1
#define HWIO_APCS_COMMON_CCI_CMD_RCGR_UPDATE_BMSK                                                   0x1
#define HWIO_APCS_COMMON_CCI_CMD_RCGR_UPDATE_SHFT                                                   0x0

#define HWIO_APCS_COMMON_CCI_CFG_RCGR_ADDR                                                   (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000054)
#define HWIO_APCS_COMMON_CCI_CFG_RCGR_RMSK                                                        0xf1f
#define HWIO_APCS_COMMON_CCI_CFG_RCGR_IN          \
        in_dword_masked(HWIO_APCS_COMMON_CCI_CFG_RCGR_ADDR, HWIO_APCS_COMMON_CCI_CFG_RCGR_RMSK)
#define HWIO_APCS_COMMON_CCI_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_CCI_CFG_RCGR_ADDR, m)
#define HWIO_APCS_COMMON_CCI_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_CCI_CFG_RCGR_ADDR,v)
#define HWIO_APCS_COMMON_CCI_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_CCI_CFG_RCGR_ADDR,m,v,HWIO_APCS_COMMON_CCI_CFG_RCGR_IN)
#define HWIO_APCS_COMMON_CCI_CFG_RCGR_ALT_SEL_BMSK                                                0x800
#define HWIO_APCS_COMMON_CCI_CFG_RCGR_ALT_SEL_SHFT                                                  0xb
#define HWIO_APCS_COMMON_CCI_CFG_RCGR_SRC_SEL_BMSK                                                0x700
#define HWIO_APCS_COMMON_CCI_CFG_RCGR_SRC_SEL_SHFT                                                  0x8
#define HWIO_APCS_COMMON_CCI_CFG_RCGR_SRC_DIV_BMSK                                                 0x1f
#define HWIO_APCS_COMMON_CCI_CFG_RCGR_SRC_DIV_SHFT                                                  0x0

#define HWIO_APCS_COMMON_CCI_CBCR_ADDR                                                       (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000058)
#define HWIO_APCS_COMMON_CCI_CBCR_RMSK                                                       0x80000003
#define HWIO_APCS_COMMON_CCI_CBCR_IN          \
        in_dword_masked(HWIO_APCS_COMMON_CCI_CBCR_ADDR, HWIO_APCS_COMMON_CCI_CBCR_RMSK)
#define HWIO_APCS_COMMON_CCI_CBCR_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_CCI_CBCR_ADDR, m)
#define HWIO_APCS_COMMON_CCI_CBCR_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_CCI_CBCR_ADDR,v)
#define HWIO_APCS_COMMON_CCI_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_CCI_CBCR_ADDR,m,v,HWIO_APCS_COMMON_CCI_CBCR_IN)
#define HWIO_APCS_COMMON_CCI_CBCR_CLK_OFF_BMSK                                               0x80000000
#define HWIO_APCS_COMMON_CCI_CBCR_CLK_OFF_SHFT                                                     0x1f
#define HWIO_APCS_COMMON_CCI_CBCR_HW_CTL_BMSK                                                       0x2
#define HWIO_APCS_COMMON_CCI_CBCR_HW_CTL_SHFT                                                       0x1
#define HWIO_APCS_COMMON_CCI_CBCR_CLK_ENABLE_BMSK                                                   0x1
#define HWIO_APCS_COMMON_CCI_CBCR_CLK_ENABLE_SHFT                                                   0x0

#define HWIO_APCS_COMMON_CCI_HIER_CG_ADDR                                                    (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x0000005c)
#define HWIO_APCS_COMMON_CCI_HIER_CG_RMSK                                                     0xffffff1
#define HWIO_APCS_COMMON_CCI_HIER_CG_IN          \
        in_dword_masked(HWIO_APCS_COMMON_CCI_HIER_CG_ADDR, HWIO_APCS_COMMON_CCI_HIER_CG_RMSK)
#define HWIO_APCS_COMMON_CCI_HIER_CG_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_CCI_HIER_CG_ADDR, m)
#define HWIO_APCS_COMMON_CCI_HIER_CG_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_CCI_HIER_CG_ADDR,v)
#define HWIO_APCS_COMMON_CCI_HIER_CG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_CCI_HIER_CG_ADDR,m,v,HWIO_APCS_COMMON_CCI_HIER_CG_IN)
#define HWIO_APCS_COMMON_CCI_HIER_CG_CCIRAMS_TIMER_CNT_VAL_BMSK                               0xffc0000
#define HWIO_APCS_COMMON_CCI_HIER_CG_CCIRAMS_TIMER_CNT_VAL_SHFT                                    0x12
#define HWIO_APCS_COMMON_CCI_HIER_CG_CSR_CCI_CLK_OFF_EN_BMSK                                    0x20000
#define HWIO_APCS_COMMON_CCI_HIER_CG_CSR_CCI_CLK_OFF_EN_SHFT                                       0x11
#define HWIO_APCS_COMMON_CCI_HIER_CG_CSR_CCI_OTHERSDIRRAMS_SLP_RET_N_EN_BMSK                    0x10000
#define HWIO_APCS_COMMON_CCI_HIER_CG_CSR_CCI_OTHERSDIRRAMS_SLP_RET_N_EN_SHFT                       0x10
#define HWIO_APCS_COMMON_CCI_HIER_CG_CSR_CCI_PERFDIRRAMS_SLP_RET_N_EN_BMSK                       0x8000
#define HWIO_APCS_COMMON_CCI_HIER_CG_CSR_CCI_PERFDIRRAMS_SLP_RET_N_EN_SHFT                          0xf
#define HWIO_APCS_COMMON_CCI_HIER_CG_CSR_CCI_PWRDIRRAMS_SLP_RET_N_EN_BMSK                        0x4000
#define HWIO_APCS_COMMON_CCI_HIER_CG_CSR_CCI_PWRDIRRAMS_SLP_RET_N_EN_SHFT                           0xe
#define HWIO_APCS_COMMON_CCI_HIER_CG_TIMER_CNT_VAL_BMSK                                          0x3ff0
#define HWIO_APCS_COMMON_CCI_HIER_CG_TIMER_CNT_VAL_SHFT                                             0x4
#define HWIO_APCS_COMMON_CCI_HIER_CG_HIER_CG_EN_BMSK                                                0x1
#define HWIO_APCS_COMMON_CCI_HIER_CG_HIER_CG_EN_SHFT                                                0x0

#define HWIO_APCS_COMMON_L1L2_SLP_SEQ_CLK_CTL_ADDR                                           (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000070)
#define HWIO_APCS_COMMON_L1L2_SLP_SEQ_CLK_CTL_RMSK                                                  0xf
#define HWIO_APCS_COMMON_L1L2_SLP_SEQ_CLK_CTL_IN          \
        in_dword_masked(HWIO_APCS_COMMON_L1L2_SLP_SEQ_CLK_CTL_ADDR, HWIO_APCS_COMMON_L1L2_SLP_SEQ_CLK_CTL_RMSK)
#define HWIO_APCS_COMMON_L1L2_SLP_SEQ_CLK_CTL_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_L1L2_SLP_SEQ_CLK_CTL_ADDR, m)
#define HWIO_APCS_COMMON_L1L2_SLP_SEQ_CLK_CTL_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_L1L2_SLP_SEQ_CLK_CTL_ADDR,v)
#define HWIO_APCS_COMMON_L1L2_SLP_SEQ_CLK_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_L1L2_SLP_SEQ_CLK_CTL_ADDR,m,v,HWIO_APCS_COMMON_L1L2_SLP_SEQ_CLK_CTL_IN)
#define HWIO_APCS_COMMON_L1L2_SLP_SEQ_CLK_CTL_CLK_DIV_BMSK                                          0xf
#define HWIO_APCS_COMMON_L1L2_SLP_SEQ_CLK_CTL_CLK_DIV_SHFT                                          0x0

#define HWIO_APCS_COMMON_CONFIG_BID_ADDR                                                     (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000110)
#define HWIO_APCS_COMMON_CONFIG_BID_RMSK                                                            0x7
#define HWIO_APCS_COMMON_CONFIG_BID_IN          \
        in_dword_masked(HWIO_APCS_COMMON_CONFIG_BID_ADDR, HWIO_APCS_COMMON_CONFIG_BID_RMSK)
#define HWIO_APCS_COMMON_CONFIG_BID_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_CONFIG_BID_ADDR, m)
#define HWIO_APCS_COMMON_CONFIG_BID_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_CONFIG_BID_ADDR,v)
#define HWIO_APCS_COMMON_CONFIG_BID_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_CONFIG_BID_ADDR,m,v,HWIO_APCS_COMMON_CONFIG_BID_IN)
#define HWIO_APCS_COMMON_CONFIG_BID_CONFIG_BID_BMSK                                                 0x7
#define HWIO_APCS_COMMON_CONFIG_BID_CONFIG_BID_SHFT                                                 0x0

#define HWIO_APCS_COMMON_CONFIG_MID_APC0_ADDR                                                (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000118)
#define HWIO_APCS_COMMON_CONFIG_MID_APC0_RMSK                                                      0xff
#define HWIO_APCS_COMMON_CONFIG_MID_APC0_IN          \
        in_dword_masked(HWIO_APCS_COMMON_CONFIG_MID_APC0_ADDR, HWIO_APCS_COMMON_CONFIG_MID_APC0_RMSK)
#define HWIO_APCS_COMMON_CONFIG_MID_APC0_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_CONFIG_MID_APC0_ADDR, m)
#define HWIO_APCS_COMMON_CONFIG_MID_APC0_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_CONFIG_MID_APC0_ADDR,v)
#define HWIO_APCS_COMMON_CONFIG_MID_APC0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_CONFIG_MID_APC0_ADDR,m,v,HWIO_APCS_COMMON_CONFIG_MID_APC0_IN)
#define HWIO_APCS_COMMON_CONFIG_MID_APC0_CONFIG_MID_APC0_BMSK                                      0xff
#define HWIO_APCS_COMMON_CONFIG_MID_APC0_CONFIG_MID_APC0_SHFT                                       0x0

#define HWIO_APCS_COMMON_CONFIG_PID_ADDR                                                     (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000114)
#define HWIO_APCS_COMMON_CONFIG_PID_RMSK                                                           0x1f
#define HWIO_APCS_COMMON_CONFIG_PID_IN          \
        in_dword_masked(HWIO_APCS_COMMON_CONFIG_PID_ADDR, HWIO_APCS_COMMON_CONFIG_PID_RMSK)
#define HWIO_APCS_COMMON_CONFIG_PID_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_CONFIG_PID_ADDR, m)
#define HWIO_APCS_COMMON_CONFIG_PID_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_CONFIG_PID_ADDR,v)
#define HWIO_APCS_COMMON_CONFIG_PID_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_CONFIG_PID_ADDR,m,v,HWIO_APCS_COMMON_CONFIG_PID_IN)
#define HWIO_APCS_COMMON_CONFIG_PID_CONFIG_PID_BMSK                                                0x1f
#define HWIO_APCS_COMMON_CONFIG_PID_CONFIG_PID_SHFT                                                 0x0

#define HWIO_APCS_COMMON_CONFIG_BPMID_SEL_ADDR                                               (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x0000011c)
#define HWIO_APCS_COMMON_CONFIG_BPMID_SEL_RMSK                                                      0xf
#define HWIO_APCS_COMMON_CONFIG_BPMID_SEL_IN          \
        in_dword_masked(HWIO_APCS_COMMON_CONFIG_BPMID_SEL_ADDR, HWIO_APCS_COMMON_CONFIG_BPMID_SEL_RMSK)
#define HWIO_APCS_COMMON_CONFIG_BPMID_SEL_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_CONFIG_BPMID_SEL_ADDR, m)
#define HWIO_APCS_COMMON_CONFIG_BPMID_SEL_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_CONFIG_BPMID_SEL_ADDR,v)
#define HWIO_APCS_COMMON_CONFIG_BPMID_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_CONFIG_BPMID_SEL_ADDR,m,v,HWIO_APCS_COMMON_CONFIG_BPMID_SEL_IN)
#define HWIO_APCS_COMMON_CONFIG_BPMID_SEL_CSR_CFG_BID_SEL_BMSK                                      0x8
#define HWIO_APCS_COMMON_CONFIG_BPMID_SEL_CSR_CFG_BID_SEL_SHFT                                      0x3
#define HWIO_APCS_COMMON_CONFIG_BPMID_SEL_CSR_CFG_PID_SEL_BMSK                                      0x4
#define HWIO_APCS_COMMON_CONFIG_BPMID_SEL_CSR_CFG_PID_SEL_SHFT                                      0x2
#define HWIO_APCS_COMMON_CONFIG_BPMID_SEL_CSR_CFG_MID_APC1_SEL_BMSK                                 0x2
#define HWIO_APCS_COMMON_CONFIG_BPMID_SEL_CSR_CFG_MID_APC1_SEL_SHFT                                 0x1
#define HWIO_APCS_COMMON_CONFIG_BPMID_SEL_CSR_CFG_MID_APC0_SEL_BMSK                                 0x1
#define HWIO_APCS_COMMON_CONFIG_BPMID_SEL_CSR_CFG_MID_APC0_SEL_SHFT                                 0x0

#define HWIO_APCS_COMMON_CONFIG_MID_APC1_ADDR                                                (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000120)
#define HWIO_APCS_COMMON_CONFIG_MID_APC1_RMSK                                                      0xff
#define HWIO_APCS_COMMON_CONFIG_MID_APC1_IN          \
        in_dword_masked(HWIO_APCS_COMMON_CONFIG_MID_APC1_ADDR, HWIO_APCS_COMMON_CONFIG_MID_APC1_RMSK)
#define HWIO_APCS_COMMON_CONFIG_MID_APC1_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_CONFIG_MID_APC1_ADDR, m)
#define HWIO_APCS_COMMON_CONFIG_MID_APC1_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_CONFIG_MID_APC1_ADDR,v)
#define HWIO_APCS_COMMON_CONFIG_MID_APC1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_CONFIG_MID_APC1_ADDR,m,v,HWIO_APCS_COMMON_CONFIG_MID_APC1_IN)
#define HWIO_APCS_COMMON_CONFIG_MID_APC1_CONFIG_MID_APC1_BMSK                                      0xff
#define HWIO_APCS_COMMON_CONFIG_MID_APC1_CONFIG_MID_APC1_SHFT                                       0x0

#define HWIO_APCS_COMMON_PS_SW_RST_ADDR                                                      (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000124)
#define HWIO_APCS_COMMON_PS_SW_RST_RMSK                                                             0x3
#define HWIO_APCS_COMMON_PS_SW_RST_IN          \
        in_dword_masked(HWIO_APCS_COMMON_PS_SW_RST_ADDR, HWIO_APCS_COMMON_PS_SW_RST_RMSK)
#define HWIO_APCS_COMMON_PS_SW_RST_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_PS_SW_RST_ADDR, m)
#define HWIO_APCS_COMMON_PS_SW_RST_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_PS_SW_RST_ADDR,v)
#define HWIO_APCS_COMMON_PS_SW_RST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_PS_SW_RST_ADDR,m,v,HWIO_APCS_COMMON_PS_SW_RST_IN)
#define HWIO_APCS_COMMON_PS_SW_RST_A57_PS_SOFT_RST_BMSK                                             0x2
#define HWIO_APCS_COMMON_PS_SW_RST_A57_PS_SOFT_RST_SHFT                                             0x1
#define HWIO_APCS_COMMON_PS_SW_RST_A53_PS_SOFT_RST_BMSK                                             0x1
#define HWIO_APCS_COMMON_PS_SW_RST_A53_PS_SOFT_RST_SHFT                                             0x0

#define HWIO_APCS_COMMON_LMH_CMD_RCGR_ADDR                                                   (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x0000012c)
#define HWIO_APCS_COMMON_LMH_CMD_RCGR_RMSK                                                   0x80000013
#define HWIO_APCS_COMMON_LMH_CMD_RCGR_IN          \
        in_dword_masked(HWIO_APCS_COMMON_LMH_CMD_RCGR_ADDR, HWIO_APCS_COMMON_LMH_CMD_RCGR_RMSK)
#define HWIO_APCS_COMMON_LMH_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_LMH_CMD_RCGR_ADDR, m)
#define HWIO_APCS_COMMON_LMH_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_LMH_CMD_RCGR_ADDR,v)
#define HWIO_APCS_COMMON_LMH_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_LMH_CMD_RCGR_ADDR,m,v,HWIO_APCS_COMMON_LMH_CMD_RCGR_IN)
#define HWIO_APCS_COMMON_LMH_CMD_RCGR_ROOT_OFF_BMSK                                          0x80000000
#define HWIO_APCS_COMMON_LMH_CMD_RCGR_ROOT_OFF_SHFT                                                0x1f
#define HWIO_APCS_COMMON_LMH_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                          0x10
#define HWIO_APCS_COMMON_LMH_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                           0x4
#define HWIO_APCS_COMMON_LMH_CMD_RCGR_ROOT_EN_BMSK                                                  0x2
#define HWIO_APCS_COMMON_LMH_CMD_RCGR_ROOT_EN_SHFT                                                  0x1
#define HWIO_APCS_COMMON_LMH_CMD_RCGR_UPDATE_BMSK                                                   0x1
#define HWIO_APCS_COMMON_LMH_CMD_RCGR_UPDATE_SHFT                                                   0x0

#define HWIO_APCS_COMMON_LMH_CFG_RCGR_ADDR                                                   (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000130)
#define HWIO_APCS_COMMON_LMH_CFG_RCGR_RMSK                                                        0xf1f
#define HWIO_APCS_COMMON_LMH_CFG_RCGR_IN          \
        in_dword_masked(HWIO_APCS_COMMON_LMH_CFG_RCGR_ADDR, HWIO_APCS_COMMON_LMH_CFG_RCGR_RMSK)
#define HWIO_APCS_COMMON_LMH_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_LMH_CFG_RCGR_ADDR, m)
#define HWIO_APCS_COMMON_LMH_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_LMH_CFG_RCGR_ADDR,v)
#define HWIO_APCS_COMMON_LMH_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_LMH_CFG_RCGR_ADDR,m,v,HWIO_APCS_COMMON_LMH_CFG_RCGR_IN)
#define HWIO_APCS_COMMON_LMH_CFG_RCGR_ALT_SEL_BMSK                                                0x800
#define HWIO_APCS_COMMON_LMH_CFG_RCGR_ALT_SEL_SHFT                                                  0xb
#define HWIO_APCS_COMMON_LMH_CFG_RCGR_SRC_SEL_BMSK                                                0x700
#define HWIO_APCS_COMMON_LMH_CFG_RCGR_SRC_SEL_SHFT                                                  0x8
#define HWIO_APCS_COMMON_LMH_CFG_RCGR_SRC_DIV_BMSK                                                 0x1f
#define HWIO_APCS_COMMON_LMH_CFG_RCGR_SRC_DIV_SHFT                                                  0x0

#define HWIO_APCS_COMMON_GLADIATOR_ACC_ADDR                                                  (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000134)
#define HWIO_APCS_COMMON_GLADIATOR_ACC_RMSK                                                        0xff
#define HWIO_APCS_COMMON_GLADIATOR_ACC_IN          \
        in_dword_masked(HWIO_APCS_COMMON_GLADIATOR_ACC_ADDR, HWIO_APCS_COMMON_GLADIATOR_ACC_RMSK)
#define HWIO_APCS_COMMON_GLADIATOR_ACC_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_GLADIATOR_ACC_ADDR, m)
#define HWIO_APCS_COMMON_GLADIATOR_ACC_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_GLADIATOR_ACC_ADDR,v)
#define HWIO_APCS_COMMON_GLADIATOR_ACC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_GLADIATOR_ACC_ADDR,m,v,HWIO_APCS_COMMON_GLADIATOR_ACC_IN)
#define HWIO_APCS_COMMON_GLADIATOR_ACC_GLADIATOR_MEM_ACC_REG_BMSK                                  0xff
#define HWIO_APCS_COMMON_GLADIATOR_ACC_GLADIATOR_MEM_ACC_REG_SHFT                                   0x0

#define HWIO_APCS_COMMON_GLADIATOR_MEM_SVS_ADDR                                              (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000138)
#define HWIO_APCS_COMMON_GLADIATOR_MEM_SVS_RMSK                                                     0x1
#define HWIO_APCS_COMMON_GLADIATOR_MEM_SVS_IN          \
        in_dword_masked(HWIO_APCS_COMMON_GLADIATOR_MEM_SVS_ADDR, HWIO_APCS_COMMON_GLADIATOR_MEM_SVS_RMSK)
#define HWIO_APCS_COMMON_GLADIATOR_MEM_SVS_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_GLADIATOR_MEM_SVS_ADDR, m)
#define HWIO_APCS_COMMON_GLADIATOR_MEM_SVS_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_GLADIATOR_MEM_SVS_ADDR,v)
#define HWIO_APCS_COMMON_GLADIATOR_MEM_SVS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_GLADIATOR_MEM_SVS_ADDR,m,v,HWIO_APCS_COMMON_GLADIATOR_MEM_SVS_IN)
#define HWIO_APCS_COMMON_GLADIATOR_MEM_SVS_GLADIATOR_MEM_SVS_REG_BMSK                               0x1
#define HWIO_APCS_COMMON_GLADIATOR_MEM_SVS_GLADIATOR_MEM_SVS_REG_SHFT                               0x0

#define HWIO_APCS_COMMON_RVBARADDR_LO_ADDR                                                   (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000108)
#define HWIO_APCS_COMMON_RVBARADDR_LO_RMSK                                                   0xffffffff
#define HWIO_APCS_COMMON_RVBARADDR_LO_IN          \
        in_dword_masked(HWIO_APCS_COMMON_RVBARADDR_LO_ADDR, HWIO_APCS_COMMON_RVBARADDR_LO_RMSK)
#define HWIO_APCS_COMMON_RVBARADDR_LO_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_RVBARADDR_LO_ADDR, m)
#define HWIO_APCS_COMMON_RVBARADDR_LO_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_RVBARADDR_LO_ADDR,v)
#define HWIO_APCS_COMMON_RVBARADDR_LO_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_RVBARADDR_LO_ADDR,m,v,HWIO_APCS_COMMON_RVBARADDR_LO_IN)
#define HWIO_APCS_COMMON_RVBARADDR_LO_RVBARADDR_LO_REG_BMSK                                  0xffffffff
#define HWIO_APCS_COMMON_RVBARADDR_LO_RVBARADDR_LO_REG_SHFT                                         0x0

#define HWIO_APCS_COMMON_RVBARADDR_HI_ADDR                                                   (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x0000010c)
#define HWIO_APCS_COMMON_RVBARADDR_HI_RMSK                                                         0x3f
#define HWIO_APCS_COMMON_RVBARADDR_HI_IN          \
        in_dword_masked(HWIO_APCS_COMMON_RVBARADDR_HI_ADDR, HWIO_APCS_COMMON_RVBARADDR_HI_RMSK)
#define HWIO_APCS_COMMON_RVBARADDR_HI_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_RVBARADDR_HI_ADDR, m)
#define HWIO_APCS_COMMON_RVBARADDR_HI_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_RVBARADDR_HI_ADDR,v)
#define HWIO_APCS_COMMON_RVBARADDR_HI_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_RVBARADDR_HI_ADDR,m,v,HWIO_APCS_COMMON_RVBARADDR_HI_IN)
#define HWIO_APCS_COMMON_RVBARADDR_HI_RVBARADDR_HI_REG_BMSK                                        0x3f
#define HWIO_APCS_COMMON_RVBARADDR_HI_RVBARADDR_HI_REG_SHFT                                         0x0

#define HWIO_APCS_COMMON_MPS_L2_MUX_ADDR                                                     (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000200)
#define HWIO_APCS_COMMON_MPS_L2_MUX_RMSK                                                            0x3
#define HWIO_APCS_COMMON_MPS_L2_MUX_IN          \
        in_dword_masked(HWIO_APCS_COMMON_MPS_L2_MUX_ADDR, HWIO_APCS_COMMON_MPS_L2_MUX_RMSK)
#define HWIO_APCS_COMMON_MPS_L2_MUX_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_MPS_L2_MUX_ADDR, m)
#define HWIO_APCS_COMMON_MPS_L2_MUX_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_MPS_L2_MUX_ADDR,v)
#define HWIO_APCS_COMMON_MPS_L2_MUX_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_MPS_L2_MUX_ADDR,m,v,HWIO_APCS_COMMON_MPS_L2_MUX_IN)
#define HWIO_APCS_COMMON_MPS_L2_MUX_PERF_MPS_L2_CLKMUX_CONTROL_BMSK                                 0x2
#define HWIO_APCS_COMMON_MPS_L2_MUX_PERF_MPS_L2_CLKMUX_CONTROL_SHFT                                 0x1
#define HWIO_APCS_COMMON_MPS_L2_MUX_PWR_MPS_L2_CLKMUX_CONTROL_BMSK                                  0x1
#define HWIO_APCS_COMMON_MPS_L2_MUX_PWR_MPS_L2_CLKMUX_CONTROL_SHFT                                  0x0

#define HWIO_APCS_COMMON_CPR_SW_BYPASS_ADDR                                                  (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000204)
#define HWIO_APCS_COMMON_CPR_SW_BYPASS_RMSK                                                         0xf
#define HWIO_APCS_COMMON_CPR_SW_BYPASS_IN          \
        in_dword_masked(HWIO_APCS_COMMON_CPR_SW_BYPASS_ADDR, HWIO_APCS_COMMON_CPR_SW_BYPASS_RMSK)
#define HWIO_APCS_COMMON_CPR_SW_BYPASS_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_CPR_SW_BYPASS_ADDR, m)
#define HWIO_APCS_COMMON_CPR_SW_BYPASS_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_CPR_SW_BYPASS_ADDR,v)
#define HWIO_APCS_COMMON_CPR_SW_BYPASS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_CPR_SW_BYPASS_ADDR,m,v,HWIO_APCS_COMMON_CPR_SW_BYPASS_IN)
#define HWIO_APCS_COMMON_CPR_SW_BYPASS_CPR_BYPASS_BMSK                                              0xf
#define HWIO_APCS_COMMON_CPR_SW_BYPASS_CPR_BYPASS_SHFT                                              0x0

#define HWIO_APCS_COMMON_SPARE_CFG3_ADDR                                                     (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000208)
#define HWIO_APCS_COMMON_SPARE_CFG3_RMSK                                                     0xffffffff
#define HWIO_APCS_COMMON_SPARE_CFG3_IN          \
        in_dword_masked(HWIO_APCS_COMMON_SPARE_CFG3_ADDR, HWIO_APCS_COMMON_SPARE_CFG3_RMSK)
#define HWIO_APCS_COMMON_SPARE_CFG3_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_SPARE_CFG3_ADDR, m)
#define HWIO_APCS_COMMON_SPARE_CFG3_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_SPARE_CFG3_ADDR,v)
#define HWIO_APCS_COMMON_SPARE_CFG3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_SPARE_CFG3_ADDR,m,v,HWIO_APCS_COMMON_SPARE_CFG3_IN)
#define HWIO_APCS_COMMON_SPARE_CFG3_COREARST_2_APCNSAW_ENABLE_BMSK                                  0x1
#define HWIO_APCS_COMMON_SPARE_CFG3_COREARST_2_APCNSAW_ENABLE_SHFT                                  0x0

#define HWIO_APCS_COMMON_CPU_PRESENT_ADDR                                                    (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x0000020c)
#define HWIO_APCS_COMMON_CPU_PRESENT_RMSK                                                          0xff
#define HWIO_APCS_COMMON_CPU_PRESENT_IN          \
        in_dword_masked(HWIO_APCS_COMMON_CPU_PRESENT_ADDR, HWIO_APCS_COMMON_CPU_PRESENT_RMSK)
#define HWIO_APCS_COMMON_CPU_PRESENT_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_CPU_PRESENT_ADDR, m)
#define HWIO_APCS_COMMON_CPU_PRESENT_CORE_PRESENT_BMSK                                             0xff
#define HWIO_APCS_COMMON_CPU_PRESENT_CORE_PRESENT_SHFT                                              0x0

#define HWIO_APCS_COMMON_TCM_CTRL_ADDR                                                       (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000300)
#define HWIO_APCS_COMMON_TCM_CTRL_RMSK                                                           0x7fff
#define HWIO_APCS_COMMON_TCM_CTRL_IN          \
        in_dword_masked(HWIO_APCS_COMMON_TCM_CTRL_ADDR, HWIO_APCS_COMMON_TCM_CTRL_RMSK)
#define HWIO_APCS_COMMON_TCM_CTRL_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_TCM_CTRL_ADDR, m)
#define HWIO_APCS_COMMON_TCM_CTRL_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_TCM_CTRL_ADDR,v)
#define HWIO_APCS_COMMON_TCM_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_TCM_CTRL_ADDR,m,v,HWIO_APCS_COMMON_TCM_CTRL_IN)
#define HWIO_APCS_COMMON_TCM_CTRL_TCM_REDIRECT_SW_CTRL_BMSK                                      0x7fff
#define HWIO_APCS_COMMON_TCM_CTRL_TCM_REDIRECT_SW_CTRL_SHFT                                         0x0

#define HWIO_APCS_COMMON_ACSNOOP_SW_CTRL_ADDR                                                (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000400)
#define HWIO_APCS_COMMON_ACSNOOP_SW_CTRL_RMSK                                                       0x1
#define HWIO_APCS_COMMON_ACSNOOP_SW_CTRL_IN          \
        in_dword_masked(HWIO_APCS_COMMON_ACSNOOP_SW_CTRL_ADDR, HWIO_APCS_COMMON_ACSNOOP_SW_CTRL_RMSK)
#define HWIO_APCS_COMMON_ACSNOOP_SW_CTRL_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_ACSNOOP_SW_CTRL_ADDR, m)
#define HWIO_APCS_COMMON_ACSNOOP_SW_CTRL_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_ACSNOOP_SW_CTRL_ADDR,v)
#define HWIO_APCS_COMMON_ACSNOOP_SW_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_ACSNOOP_SW_CTRL_ADDR,m,v,HWIO_APCS_COMMON_ACSNOOP_SW_CTRL_IN)
#define HWIO_APCS_COMMON_ACSNOOP_SW_CTRL_ACSNOOP_SW_CTRL_BMSK                                       0x1
#define HWIO_APCS_COMMON_ACSNOOP_SW_CTRL_ACSNOOP_SW_CTRL_SHFT                                       0x0

#define HWIO_APCS_COMMON_TESTBUS_MUX_CONFIG_ADDR                                             (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000128)
#define HWIO_APCS_COMMON_TESTBUS_MUX_CONFIG_RMSK                                             0x80001fff
#define HWIO_APCS_COMMON_TESTBUS_MUX_CONFIG_IN          \
        in_dword_masked(HWIO_APCS_COMMON_TESTBUS_MUX_CONFIG_ADDR, HWIO_APCS_COMMON_TESTBUS_MUX_CONFIG_RMSK)
#define HWIO_APCS_COMMON_TESTBUS_MUX_CONFIG_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_TESTBUS_MUX_CONFIG_ADDR, m)
#define HWIO_APCS_COMMON_TESTBUS_MUX_CONFIG_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_TESTBUS_MUX_CONFIG_ADDR,v)
#define HWIO_APCS_COMMON_TESTBUS_MUX_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_TESTBUS_MUX_CONFIG_ADDR,m,v,HWIO_APCS_COMMON_TESTBUS_MUX_CONFIG_IN)
#define HWIO_APCS_COMMON_TESTBUS_MUX_CONFIG_TESTBUS_MUX_EN_BMSK                              0x80000000
#define HWIO_APCS_COMMON_TESTBUS_MUX_CONFIG_TESTBUS_MUX_EN_SHFT                                    0x1f
#define HWIO_APCS_COMMON_TESTBUS_MUX_CONFIG_TESTBUS_LVL2_OLC_SEL_BMSK                            0x1e00
#define HWIO_APCS_COMMON_TESTBUS_MUX_CONFIG_TESTBUS_LVL2_OLC_SEL_SHFT                               0x9
#define HWIO_APCS_COMMON_TESTBUS_MUX_CONFIG_TESTBUS_LVL2_SEL_BMSK                                 0x1f0
#define HWIO_APCS_COMMON_TESTBUS_MUX_CONFIG_TESTBUS_LVL2_SEL_SHFT                                   0x4
#define HWIO_APCS_COMMON_TESTBUS_MUX_CONFIG_TESTBUS_LVL1_SEL_BMSK                                   0xf
#define HWIO_APCS_COMMON_TESTBUS_MUX_CONFIG_TESTBUS_LVL1_SEL_SHFT                                   0x0

#define HWIO_APCS_COMMON_SPM_WAKE_UP_WDOG_ADDR                                               (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000180)
#define HWIO_APCS_COMMON_SPM_WAKE_UP_WDOG_RMSK                                                     0xff
#define HWIO_APCS_COMMON_SPM_WAKE_UP_WDOG_IN          \
        in_dword_masked(HWIO_APCS_COMMON_SPM_WAKE_UP_WDOG_ADDR, HWIO_APCS_COMMON_SPM_WAKE_UP_WDOG_RMSK)
#define HWIO_APCS_COMMON_SPM_WAKE_UP_WDOG_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_SPM_WAKE_UP_WDOG_ADDR, m)
#define HWIO_APCS_COMMON_SPM_WAKE_UP_WDOG_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_SPM_WAKE_UP_WDOG_ADDR,v)
#define HWIO_APCS_COMMON_SPM_WAKE_UP_WDOG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_SPM_WAKE_UP_WDOG_ADDR,m,v,HWIO_APCS_COMMON_SPM_WAKE_UP_WDOG_IN)
#define HWIO_APCS_COMMON_SPM_WAKE_UP_WDOG_SPM_WAKE_UP_WDOG_ENABLE_BMSK                             0xff
#define HWIO_APCS_COMMON_SPM_WAKE_UP_WDOG_SPM_WAKE_UP_WDOG_ENABLE_SHFT                              0x0

#define HWIO_APCS_COMMON_L2SPM_TRIGGER_C0_ADDR                                               (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x000001c8)
#define HWIO_APCS_COMMON_L2SPM_TRIGGER_C0_RMSK                                                      0x3
#define HWIO_APCS_COMMON_L2SPM_TRIGGER_C0_IN          \
        in_dword_masked(HWIO_APCS_COMMON_L2SPM_TRIGGER_C0_ADDR, HWIO_APCS_COMMON_L2SPM_TRIGGER_C0_RMSK)
#define HWIO_APCS_COMMON_L2SPM_TRIGGER_C0_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_L2SPM_TRIGGER_C0_ADDR, m)
#define HWIO_APCS_COMMON_L2SPM_TRIGGER_C0_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_L2SPM_TRIGGER_C0_ADDR,v)
#define HWIO_APCS_COMMON_L2SPM_TRIGGER_C0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_L2SPM_TRIGGER_C0_ADDR,m,v,HWIO_APCS_COMMON_L2SPM_TRIGGER_C0_IN)
#define HWIO_APCS_COMMON_L2SPM_TRIGGER_C0_CLUST0_L2_SPM_SLEEP_BMSK                                  0x2
#define HWIO_APCS_COMMON_L2SPM_TRIGGER_C0_CLUST0_L2_SPM_SLEEP_SHFT                                  0x1
#define HWIO_APCS_COMMON_L2SPM_TRIGGER_C0_CLUST0_L2_SPM_WAKEUP_BMSK                                 0x1
#define HWIO_APCS_COMMON_L2SPM_TRIGGER_C0_CLUST0_L2_SPM_WAKEUP_SHFT                                 0x0

#define HWIO_APCS_COMMON_L2SPM_TRIGGER_C1_ADDR                                               (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x000001cc)
#define HWIO_APCS_COMMON_L2SPM_TRIGGER_C1_RMSK                                                      0x3
#define HWIO_APCS_COMMON_L2SPM_TRIGGER_C1_IN          \
        in_dword_masked(HWIO_APCS_COMMON_L2SPM_TRIGGER_C1_ADDR, HWIO_APCS_COMMON_L2SPM_TRIGGER_C1_RMSK)
#define HWIO_APCS_COMMON_L2SPM_TRIGGER_C1_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_L2SPM_TRIGGER_C1_ADDR, m)
#define HWIO_APCS_COMMON_L2SPM_TRIGGER_C1_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_L2SPM_TRIGGER_C1_ADDR,v)
#define HWIO_APCS_COMMON_L2SPM_TRIGGER_C1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_L2SPM_TRIGGER_C1_ADDR,m,v,HWIO_APCS_COMMON_L2SPM_TRIGGER_C1_IN)
#define HWIO_APCS_COMMON_L2SPM_TRIGGER_C1_CLUST1_L2_SPM_SLEEP_BMSK                                  0x2
#define HWIO_APCS_COMMON_L2SPM_TRIGGER_C1_CLUST1_L2_SPM_SLEEP_SHFT                                  0x1
#define HWIO_APCS_COMMON_L2SPM_TRIGGER_C1_CLUST1_L2_SPM_WAKEUP_BMSK                                 0x1
#define HWIO_APCS_COMMON_L2SPM_TRIGGER_C1_CLUST1_L2_SPM_WAKEUP_SHFT                                 0x0

#define HWIO_APCS_COMMON_CCISPM_TRIGGER_ADDR                                                 (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x000001d0)
#define HWIO_APCS_COMMON_CCISPM_TRIGGER_RMSK                                                        0x3
#define HWIO_APCS_COMMON_CCISPM_TRIGGER_IN          \
        in_dword_masked(HWIO_APCS_COMMON_CCISPM_TRIGGER_ADDR, HWIO_APCS_COMMON_CCISPM_TRIGGER_RMSK)
#define HWIO_APCS_COMMON_CCISPM_TRIGGER_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_CCISPM_TRIGGER_ADDR, m)
#define HWIO_APCS_COMMON_CCISPM_TRIGGER_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_CCISPM_TRIGGER_ADDR,v)
#define HWIO_APCS_COMMON_CCISPM_TRIGGER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_CCISPM_TRIGGER_ADDR,m,v,HWIO_APCS_COMMON_CCISPM_TRIGGER_IN)
#define HWIO_APCS_COMMON_CCISPM_TRIGGER_CCISPM_SLEEP_BMSK                                           0x2
#define HWIO_APCS_COMMON_CCISPM_TRIGGER_CCISPM_SLEEP_SHFT                                           0x1
#define HWIO_APCS_COMMON_CCISPM_TRIGGER_CCISPM_WAKEUP_BMSK                                          0x1
#define HWIO_APCS_COMMON_CCISPM_TRIGGER_CCISPM_WAKEUP_SHFT                                          0x0

#define HWIO_APCS_COMMON_L1_L2_MEM_CGC_OVERRIDE_ADDR                                         (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000210)
#define HWIO_APCS_COMMON_L1_L2_MEM_CGC_OVERRIDE_RMSK                                               0x1f
#define HWIO_APCS_COMMON_L1_L2_MEM_CGC_OVERRIDE_IN          \
        in_dword_masked(HWIO_APCS_COMMON_L1_L2_MEM_CGC_OVERRIDE_ADDR, HWIO_APCS_COMMON_L1_L2_MEM_CGC_OVERRIDE_RMSK)
#define HWIO_APCS_COMMON_L1_L2_MEM_CGC_OVERRIDE_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_L1_L2_MEM_CGC_OVERRIDE_ADDR, m)
#define HWIO_APCS_COMMON_L1_L2_MEM_CGC_OVERRIDE_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_L1_L2_MEM_CGC_OVERRIDE_ADDR,v)
#define HWIO_APCS_COMMON_L1_L2_MEM_CGC_OVERRIDE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_L1_L2_MEM_CGC_OVERRIDE_ADDR,m,v,HWIO_APCS_COMMON_L1_L2_MEM_CGC_OVERRIDE_IN)
#define HWIO_APCS_COMMON_L1_L2_MEM_CGC_OVERRIDE_L2_CGC_OVERRIDE_BMSK                               0x10
#define HWIO_APCS_COMMON_L1_L2_MEM_CGC_OVERRIDE_L2_CGC_OVERRIDE_SHFT                                0x4
#define HWIO_APCS_COMMON_L1_L2_MEM_CGC_OVERRIDE_CORE3_L1_CGC_OVERRIDE_BMSK                          0x8
#define HWIO_APCS_COMMON_L1_L2_MEM_CGC_OVERRIDE_CORE3_L1_CGC_OVERRIDE_SHFT                          0x3
#define HWIO_APCS_COMMON_L1_L2_MEM_CGC_OVERRIDE_CORE2_L1_CGC_OVERRIDE_BMSK                          0x4
#define HWIO_APCS_COMMON_L1_L2_MEM_CGC_OVERRIDE_CORE2_L1_CGC_OVERRIDE_SHFT                          0x2
#define HWIO_APCS_COMMON_L1_L2_MEM_CGC_OVERRIDE_CORE1_L1_CGC_OVERRIDE_BMSK                          0x2
#define HWIO_APCS_COMMON_L1_L2_MEM_CGC_OVERRIDE_CORE1_L1_CGC_OVERRIDE_SHFT                          0x1
#define HWIO_APCS_COMMON_L1_L2_MEM_CGC_OVERRIDE_CORE0_L1_CGC_OVERRIDE_BMSK                          0x1
#define HWIO_APCS_COMMON_L1_L2_MEM_CGC_OVERRIDE_CORE0_L1_CGC_OVERRIDE_SHFT                          0x0

#define HWIO_APCS_COMMON_APC0_VS_CBCR_ADDR                                                   (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000214)
#define HWIO_APCS_COMMON_APC0_VS_CBCR_RMSK                                                   0x80000003
#define HWIO_APCS_COMMON_APC0_VS_CBCR_IN          \
        in_dword_masked(HWIO_APCS_COMMON_APC0_VS_CBCR_ADDR, HWIO_APCS_COMMON_APC0_VS_CBCR_RMSK)
#define HWIO_APCS_COMMON_APC0_VS_CBCR_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_APC0_VS_CBCR_ADDR, m)
#define HWIO_APCS_COMMON_APC0_VS_CBCR_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_APC0_VS_CBCR_ADDR,v)
#define HWIO_APCS_COMMON_APC0_VS_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_APC0_VS_CBCR_ADDR,m,v,HWIO_APCS_COMMON_APC0_VS_CBCR_IN)
#define HWIO_APCS_COMMON_APC0_VS_CBCR_CLK_OFF_BMSK                                           0x80000000
#define HWIO_APCS_COMMON_APC0_VS_CBCR_CLK_OFF_SHFT                                                 0x1f
#define HWIO_APCS_COMMON_APC0_VS_CBCR_HW_CTL_BMSK                                                   0x2
#define HWIO_APCS_COMMON_APC0_VS_CBCR_HW_CTL_SHFT                                                   0x1
#define HWIO_APCS_COMMON_APC0_VS_CBCR_SW_CTL_BMSK                                                   0x1
#define HWIO_APCS_COMMON_APC0_VS_CBCR_SW_CTL_SHFT                                                   0x0

#define HWIO_APCS_COMMON_APC1_VS_CBCR_ADDR                                                   (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000218)
#define HWIO_APCS_COMMON_APC1_VS_CBCR_RMSK                                                   0x80000003
#define HWIO_APCS_COMMON_APC1_VS_CBCR_IN          \
        in_dword_masked(HWIO_APCS_COMMON_APC1_VS_CBCR_ADDR, HWIO_APCS_COMMON_APC1_VS_CBCR_RMSK)
#define HWIO_APCS_COMMON_APC1_VS_CBCR_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_APC1_VS_CBCR_ADDR, m)
#define HWIO_APCS_COMMON_APC1_VS_CBCR_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_APC1_VS_CBCR_ADDR,v)
#define HWIO_APCS_COMMON_APC1_VS_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_APC1_VS_CBCR_ADDR,m,v,HWIO_APCS_COMMON_APC1_VS_CBCR_IN)
#define HWIO_APCS_COMMON_APC1_VS_CBCR_CLK_OFF_BMSK                                           0x80000000
#define HWIO_APCS_COMMON_APC1_VS_CBCR_CLK_OFF_SHFT                                                 0x1f
#define HWIO_APCS_COMMON_APC1_VS_CBCR_HW_CTL_BMSK                                                   0x2
#define HWIO_APCS_COMMON_APC1_VS_CBCR_HW_CTL_SHFT                                                   0x1
#define HWIO_APCS_COMMON_APC1_VS_CBCR_SW_CTL_BMSK                                                   0x1
#define HWIO_APCS_COMMON_APC1_VS_CBCR_SW_CTL_SHFT                                                   0x0

#define HWIO_APCS_COMMON_QSB_CBCR_ADDR                                                       (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x0000021c)
#define HWIO_APCS_COMMON_QSB_CBCR_RMSK                                                       0x80000003
#define HWIO_APCS_COMMON_QSB_CBCR_IN          \
        in_dword_masked(HWIO_APCS_COMMON_QSB_CBCR_ADDR, HWIO_APCS_COMMON_QSB_CBCR_RMSK)
#define HWIO_APCS_COMMON_QSB_CBCR_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_QSB_CBCR_ADDR, m)
#define HWIO_APCS_COMMON_QSB_CBCR_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_QSB_CBCR_ADDR,v)
#define HWIO_APCS_COMMON_QSB_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_QSB_CBCR_ADDR,m,v,HWIO_APCS_COMMON_QSB_CBCR_IN)
#define HWIO_APCS_COMMON_QSB_CBCR_CLK_OFF_BMSK                                               0x80000000
#define HWIO_APCS_COMMON_QSB_CBCR_CLK_OFF_SHFT                                                     0x1f
#define HWIO_APCS_COMMON_QSB_CBCR_HW_CTL_BMSK                                                       0x2
#define HWIO_APCS_COMMON_QSB_CBCR_HW_CTL_SHFT                                                       0x1
#define HWIO_APCS_COMMON_QSB_CBCR_SW_CTL_BMSK                                                       0x1
#define HWIO_APCS_COMMON_QSB_CBCR_SW_CTL_SHFT                                                       0x0

#define HWIO_APCS_COMMON_APB_CBCR_ADDR                                                       (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000220)
#define HWIO_APCS_COMMON_APB_CBCR_RMSK                                                       0x80000003
#define HWIO_APCS_COMMON_APB_CBCR_IN          \
        in_dword_masked(HWIO_APCS_COMMON_APB_CBCR_ADDR, HWIO_APCS_COMMON_APB_CBCR_RMSK)
#define HWIO_APCS_COMMON_APB_CBCR_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_APB_CBCR_ADDR, m)
#define HWIO_APCS_COMMON_APB_CBCR_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_APB_CBCR_ADDR,v)
#define HWIO_APCS_COMMON_APB_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_APB_CBCR_ADDR,m,v,HWIO_APCS_COMMON_APB_CBCR_IN)
#define HWIO_APCS_COMMON_APB_CBCR_CLK_OFF_BMSK                                               0x80000000
#define HWIO_APCS_COMMON_APB_CBCR_CLK_OFF_SHFT                                                     0x1f
#define HWIO_APCS_COMMON_APB_CBCR_HW_CTL_BMSK                                                       0x2
#define HWIO_APCS_COMMON_APB_CBCR_HW_CTL_SHFT                                                       0x1
#define HWIO_APCS_COMMON_APB_CBCR_SW_CTL_BMSK                                                       0x1
#define HWIO_APCS_COMMON_APB_CBCR_SW_CTL_SHFT                                                       0x0

#define HWIO_APCS_COMMON_CS_CBCR_ADDR                                                        (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000224)
#define HWIO_APCS_COMMON_CS_CBCR_RMSK                                                        0x80000003
#define HWIO_APCS_COMMON_CS_CBCR_IN          \
        in_dword_masked(HWIO_APCS_COMMON_CS_CBCR_ADDR, HWIO_APCS_COMMON_CS_CBCR_RMSK)
#define HWIO_APCS_COMMON_CS_CBCR_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_CS_CBCR_ADDR, m)
#define HWIO_APCS_COMMON_CS_CBCR_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_CS_CBCR_ADDR,v)
#define HWIO_APCS_COMMON_CS_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_CS_CBCR_ADDR,m,v,HWIO_APCS_COMMON_CS_CBCR_IN)
#define HWIO_APCS_COMMON_CS_CBCR_CLK_OFF_BMSK                                                0x80000000
#define HWIO_APCS_COMMON_CS_CBCR_CLK_OFF_SHFT                                                      0x1f
#define HWIO_APCS_COMMON_CS_CBCR_HW_CTL_BMSK                                                        0x2
#define HWIO_APCS_COMMON_CS_CBCR_HW_CTL_SHFT                                                        0x1
#define HWIO_APCS_COMMON_CS_CBCR_SW_CTL_BMSK                                                        0x1
#define HWIO_APCS_COMMON_CS_CBCR_SW_CTL_SHFT                                                        0x0

#define HWIO_APCS_COMMON_GIC_CMD_RCGR_ADDR                                                   (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000234)
#define HWIO_APCS_COMMON_GIC_CMD_RCGR_RMSK                                                   0x80000013
#define HWIO_APCS_COMMON_GIC_CMD_RCGR_IN          \
        in_dword_masked(HWIO_APCS_COMMON_GIC_CMD_RCGR_ADDR, HWIO_APCS_COMMON_GIC_CMD_RCGR_RMSK)
#define HWIO_APCS_COMMON_GIC_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_GIC_CMD_RCGR_ADDR, m)
#define HWIO_APCS_COMMON_GIC_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_GIC_CMD_RCGR_ADDR,v)
#define HWIO_APCS_COMMON_GIC_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_GIC_CMD_RCGR_ADDR,m,v,HWIO_APCS_COMMON_GIC_CMD_RCGR_IN)
#define HWIO_APCS_COMMON_GIC_CMD_RCGR_ROOT_OFF_BMSK                                          0x80000000
#define HWIO_APCS_COMMON_GIC_CMD_RCGR_ROOT_OFF_SHFT                                                0x1f
#define HWIO_APCS_COMMON_GIC_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                          0x10
#define HWIO_APCS_COMMON_GIC_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                           0x4
#define HWIO_APCS_COMMON_GIC_CMD_RCGR_ROOT_EN_BMSK                                                  0x2
#define HWIO_APCS_COMMON_GIC_CMD_RCGR_ROOT_EN_SHFT                                                  0x1
#define HWIO_APCS_COMMON_GIC_CMD_RCGR_UPDATE_BMSK                                                   0x1
#define HWIO_APCS_COMMON_GIC_CMD_RCGR_UPDATE_SHFT                                                   0x0

#define HWIO_APCS_COMMON_GIC_CFG_RCGR_ADDR                                                   (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x0000022c)
#define HWIO_APCS_COMMON_GIC_CFG_RCGR_RMSK                                                        0xf1f
#define HWIO_APCS_COMMON_GIC_CFG_RCGR_IN          \
        in_dword_masked(HWIO_APCS_COMMON_GIC_CFG_RCGR_ADDR, HWIO_APCS_COMMON_GIC_CFG_RCGR_RMSK)
#define HWIO_APCS_COMMON_GIC_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_GIC_CFG_RCGR_ADDR, m)
#define HWIO_APCS_COMMON_GIC_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_GIC_CFG_RCGR_ADDR,v)
#define HWIO_APCS_COMMON_GIC_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_GIC_CFG_RCGR_ADDR,m,v,HWIO_APCS_COMMON_GIC_CFG_RCGR_IN)
#define HWIO_APCS_COMMON_GIC_CFG_RCGR_ALT_SEL_BMSK                                                0x800
#define HWIO_APCS_COMMON_GIC_CFG_RCGR_ALT_SEL_SHFT                                                  0xb
#define HWIO_APCS_COMMON_GIC_CFG_RCGR_SRC_SEL_BMSK                                                0x700
#define HWIO_APCS_COMMON_GIC_CFG_RCGR_SRC_SEL_SHFT                                                  0x8
#define HWIO_APCS_COMMON_GIC_CFG_RCGR_CLK_CTRL_ENABLE_BMSK                                         0x1f
#define HWIO_APCS_COMMON_GIC_CFG_RCGR_CLK_CTRL_ENABLE_SHFT                                          0x0

#define HWIO_APCS_COMMON_GIC_CBCR_ADDR                                                       (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000230)
#define HWIO_APCS_COMMON_GIC_CBCR_RMSK                                                       0x80000003
#define HWIO_APCS_COMMON_GIC_CBCR_IN          \
        in_dword_masked(HWIO_APCS_COMMON_GIC_CBCR_ADDR, HWIO_APCS_COMMON_GIC_CBCR_RMSK)
#define HWIO_APCS_COMMON_GIC_CBCR_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_GIC_CBCR_ADDR, m)
#define HWIO_APCS_COMMON_GIC_CBCR_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_GIC_CBCR_ADDR,v)
#define HWIO_APCS_COMMON_GIC_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_GIC_CBCR_ADDR,m,v,HWIO_APCS_COMMON_GIC_CBCR_IN)
#define HWIO_APCS_COMMON_GIC_CBCR_CLK_OFF_BMSK                                               0x80000000
#define HWIO_APCS_COMMON_GIC_CBCR_CLK_OFF_SHFT                                                     0x1f
#define HWIO_APCS_COMMON_GIC_CBCR_HW_CTL_BMSK                                                       0x2
#define HWIO_APCS_COMMON_GIC_CBCR_HW_CTL_SHFT                                                       0x1
#define HWIO_APCS_COMMON_GIC_CBCR_SW_CTL_BMSK                                                       0x1
#define HWIO_APCS_COMMON_GIC_CBCR_SW_CTL_SHFT                                                       0x0

#define HWIO_APCS_COMMON_SPI_CONFIG_n_ADDR(n)                                                (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000304 + 0x4 * (n))
#define HWIO_APCS_COMMON_SPI_CONFIG_n_RMSK                                                   0xffffffff
#define HWIO_APCS_COMMON_SPI_CONFIG_n_MAXn                                                           18
#define HWIO_APCS_COMMON_SPI_CONFIG_n_INI(n)        \
        in_dword_masked(HWIO_APCS_COMMON_SPI_CONFIG_n_ADDR(n), HWIO_APCS_COMMON_SPI_CONFIG_n_RMSK)
#define HWIO_APCS_COMMON_SPI_CONFIG_n_INMI(n,mask)    \
        in_dword_masked(HWIO_APCS_COMMON_SPI_CONFIG_n_ADDR(n), mask)
#define HWIO_APCS_COMMON_SPI_CONFIG_n_OUTI(n,val)    \
        out_dword(HWIO_APCS_COMMON_SPI_CONFIG_n_ADDR(n),val)
#define HWIO_APCS_COMMON_SPI_CONFIG_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_APCS_COMMON_SPI_CONFIG_n_ADDR(n),mask,val,HWIO_APCS_COMMON_SPI_CONFIG_n_INI(n))
#define HWIO_APCS_COMMON_SPI_CONFIG_n_SPI_NUMBER_BMSK                                        0xffffffff
#define HWIO_APCS_COMMON_SPI_CONFIG_n_SPI_NUMBER_SHFT                                               0x0

#define HWIO_APCS_COMMON_PPI_CONFIG_n_ADDR(n)                                                (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000350 + 0x4 * (n))
#define HWIO_APCS_COMMON_PPI_CONFIG_n_RMSK                                                   0xffffffff
#define HWIO_APCS_COMMON_PPI_CONFIG_n_MAXn                                                            3
#define HWIO_APCS_COMMON_PPI_CONFIG_n_INI(n)        \
        in_dword_masked(HWIO_APCS_COMMON_PPI_CONFIG_n_ADDR(n), HWIO_APCS_COMMON_PPI_CONFIG_n_RMSK)
#define HWIO_APCS_COMMON_PPI_CONFIG_n_INMI(n,mask)    \
        in_dword_masked(HWIO_APCS_COMMON_PPI_CONFIG_n_ADDR(n), mask)
#define HWIO_APCS_COMMON_PPI_CONFIG_n_OUTI(n,val)    \
        out_dword(HWIO_APCS_COMMON_PPI_CONFIG_n_ADDR(n),val)
#define HWIO_APCS_COMMON_PPI_CONFIG_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_APCS_COMMON_PPI_CONFIG_n_ADDR(n),mask,val,HWIO_APCS_COMMON_PPI_CONFIG_n_INI(n))
#define HWIO_APCS_COMMON_PPI_CONFIG_n_PPI_NUMBER_BMSK                                        0xffffffff
#define HWIO_APCS_COMMON_PPI_CONFIG_n_PPI_NUMBER_SHFT                                               0x0

#define HWIO_APCS_COMMON_MEM_ACC_C0_0_ADDR                                                   (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000360)
#define HWIO_APCS_COMMON_MEM_ACC_C0_0_RMSK                                                   0xffffffff
#define HWIO_APCS_COMMON_MEM_ACC_C0_0_IN          \
        in_dword_masked(HWIO_APCS_COMMON_MEM_ACC_C0_0_ADDR, HWIO_APCS_COMMON_MEM_ACC_C0_0_RMSK)
#define HWIO_APCS_COMMON_MEM_ACC_C0_0_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_MEM_ACC_C0_0_ADDR, m)
#define HWIO_APCS_COMMON_MEM_ACC_C0_0_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_MEM_ACC_C0_0_ADDR,v)
#define HWIO_APCS_COMMON_MEM_ACC_C0_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_MEM_ACC_C0_0_ADDR,m,v,HWIO_APCS_COMMON_MEM_ACC_C0_0_IN)
#define HWIO_APCS_COMMON_MEM_ACC_C0_0_MEM_ACC_C0_TYPE4_BMSK                                  0xff000000
#define HWIO_APCS_COMMON_MEM_ACC_C0_0_MEM_ACC_C0_TYPE4_SHFT                                        0x18
#define HWIO_APCS_COMMON_MEM_ACC_C0_0_MEM_ACC_C0_TYPE3_BMSK                                    0xff0000
#define HWIO_APCS_COMMON_MEM_ACC_C0_0_MEM_ACC_C0_TYPE3_SHFT                                        0x10
#define HWIO_APCS_COMMON_MEM_ACC_C0_0_MEM_ACC_C0_TYPE2_BMSK                                      0xff00
#define HWIO_APCS_COMMON_MEM_ACC_C0_0_MEM_ACC_C0_TYPE2_SHFT                                         0x8
#define HWIO_APCS_COMMON_MEM_ACC_C0_0_MEM_ACC_C0_TYPE1_BMSK                                        0xff
#define HWIO_APCS_COMMON_MEM_ACC_C0_0_MEM_ACC_C0_TYPE1_SHFT                                         0x0

#define HWIO_APCS_COMMON_MEM_ACC_C0_1_ADDR                                                   (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000364)
#define HWIO_APCS_COMMON_MEM_ACC_C0_1_RMSK                                                   0x800000ff
#define HWIO_APCS_COMMON_MEM_ACC_C0_1_IN          \
        in_dword_masked(HWIO_APCS_COMMON_MEM_ACC_C0_1_ADDR, HWIO_APCS_COMMON_MEM_ACC_C0_1_RMSK)
#define HWIO_APCS_COMMON_MEM_ACC_C0_1_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_MEM_ACC_C0_1_ADDR, m)
#define HWIO_APCS_COMMON_MEM_ACC_C0_1_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_MEM_ACC_C0_1_ADDR,v)
#define HWIO_APCS_COMMON_MEM_ACC_C0_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_MEM_ACC_C0_1_ADDR,m,v,HWIO_APCS_COMMON_MEM_ACC_C0_1_IN)
#define HWIO_APCS_COMMON_MEM_ACC_C0_1_MEM_SVS_C0_BMSK                                        0x80000000
#define HWIO_APCS_COMMON_MEM_ACC_C0_1_MEM_SVS_C0_SHFT                                              0x1f
#define HWIO_APCS_COMMON_MEM_ACC_C0_1_MEM_ACC_C0_TYPE5_BMSK                                        0xff
#define HWIO_APCS_COMMON_MEM_ACC_C0_1_MEM_ACC_C0_TYPE5_SHFT                                         0x0

#define HWIO_APCS_COMMON_MEM_ACC_C1_0_ADDR                                                   (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000368)
#define HWIO_APCS_COMMON_MEM_ACC_C1_0_RMSK                                                   0xffffffff
#define HWIO_APCS_COMMON_MEM_ACC_C1_0_IN          \
        in_dword_masked(HWIO_APCS_COMMON_MEM_ACC_C1_0_ADDR, HWIO_APCS_COMMON_MEM_ACC_C1_0_RMSK)
#define HWIO_APCS_COMMON_MEM_ACC_C1_0_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_MEM_ACC_C1_0_ADDR, m)
#define HWIO_APCS_COMMON_MEM_ACC_C1_0_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_MEM_ACC_C1_0_ADDR,v)
#define HWIO_APCS_COMMON_MEM_ACC_C1_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_MEM_ACC_C1_0_ADDR,m,v,HWIO_APCS_COMMON_MEM_ACC_C1_0_IN)
#define HWIO_APCS_COMMON_MEM_ACC_C1_0_MEM_ACC_C1_TYPE4_BMSK                                  0xff000000
#define HWIO_APCS_COMMON_MEM_ACC_C1_0_MEM_ACC_C1_TYPE4_SHFT                                        0x18
#define HWIO_APCS_COMMON_MEM_ACC_C1_0_MEM_ACC_C1_TYPE3_BMSK                                    0xff0000
#define HWIO_APCS_COMMON_MEM_ACC_C1_0_MEM_ACC_C1_TYPE3_SHFT                                        0x10
#define HWIO_APCS_COMMON_MEM_ACC_C1_0_MEM_ACC_C1_TYPE2_BMSK                                      0xff00
#define HWIO_APCS_COMMON_MEM_ACC_C1_0_MEM_ACC_C1_TYPE2_SHFT                                         0x8
#define HWIO_APCS_COMMON_MEM_ACC_C1_0_MEM_ACC_C1_TYPE1_BMSK                                        0xff
#define HWIO_APCS_COMMON_MEM_ACC_C1_0_MEM_ACC_C1_TYPE1_SHFT                                         0x0

#define HWIO_APCS_COMMON_MEM_ACC_C1_1_ADDR                                                   (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x0000036c)
#define HWIO_APCS_COMMON_MEM_ACC_C1_1_RMSK                                                   0xffffffff
#define HWIO_APCS_COMMON_MEM_ACC_C1_1_IN          \
        in_dword_masked(HWIO_APCS_COMMON_MEM_ACC_C1_1_ADDR, HWIO_APCS_COMMON_MEM_ACC_C1_1_RMSK)
#define HWIO_APCS_COMMON_MEM_ACC_C1_1_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_MEM_ACC_C1_1_ADDR, m)
#define HWIO_APCS_COMMON_MEM_ACC_C1_1_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_MEM_ACC_C1_1_ADDR,v)
#define HWIO_APCS_COMMON_MEM_ACC_C1_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_MEM_ACC_C1_1_ADDR,m,v,HWIO_APCS_COMMON_MEM_ACC_C1_1_IN)
#define HWIO_APCS_COMMON_MEM_ACC_C1_1_MEM_ACC_C1_TYPE8_BMSK                                  0xff000000
#define HWIO_APCS_COMMON_MEM_ACC_C1_1_MEM_ACC_C1_TYPE8_SHFT                                        0x18
#define HWIO_APCS_COMMON_MEM_ACC_C1_1_MEM_ACC_C1_TYPE7_BMSK                                    0xff0000
#define HWIO_APCS_COMMON_MEM_ACC_C1_1_MEM_ACC_C1_TYPE7_SHFT                                        0x10
#define HWIO_APCS_COMMON_MEM_ACC_C1_1_MEM_ACC_C1_TYPE6_BMSK                                      0xff00
#define HWIO_APCS_COMMON_MEM_ACC_C1_1_MEM_ACC_C1_TYPE6_SHFT                                         0x8
#define HWIO_APCS_COMMON_MEM_ACC_C1_1_MEM_ACC_C1_TYPE5_BMSK                                        0xff
#define HWIO_APCS_COMMON_MEM_ACC_C1_1_MEM_ACC_C1_TYPE5_SHFT                                         0x0

#define HWIO_APCS_COMMON_MEM_ACC_C1_2_ADDR                                                   (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000370)
#define HWIO_APCS_COMMON_MEM_ACC_C1_2_RMSK                                                   0x800000ff
#define HWIO_APCS_COMMON_MEM_ACC_C1_2_IN          \
        in_dword_masked(HWIO_APCS_COMMON_MEM_ACC_C1_2_ADDR, HWIO_APCS_COMMON_MEM_ACC_C1_2_RMSK)
#define HWIO_APCS_COMMON_MEM_ACC_C1_2_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_MEM_ACC_C1_2_ADDR, m)
#define HWIO_APCS_COMMON_MEM_ACC_C1_2_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_MEM_ACC_C1_2_ADDR,v)
#define HWIO_APCS_COMMON_MEM_ACC_C1_2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_MEM_ACC_C1_2_ADDR,m,v,HWIO_APCS_COMMON_MEM_ACC_C1_2_IN)
#define HWIO_APCS_COMMON_MEM_ACC_C1_2_MEM_SVS_C1_BMSK                                        0x80000000
#define HWIO_APCS_COMMON_MEM_ACC_C1_2_MEM_SVS_C1_SHFT                                              0x1f
#define HWIO_APCS_COMMON_MEM_ACC_C1_2_MEM_ACC_C1_TYPE9_BMSK                                        0xff
#define HWIO_APCS_COMMON_MEM_ACC_C1_2_MEM_ACC_C1_TYPE9_SHFT                                         0x0

#define HWIO_APCS_COMMON_MEM_ACC_COMP_n_ADDR(n)                                              (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000398 + 0x4 * (n))
#define HWIO_APCS_COMMON_MEM_ACC_COMP_n_RMSK                                                       0xff
#define HWIO_APCS_COMMON_MEM_ACC_COMP_n_MAXn                                                          7
#define HWIO_APCS_COMMON_MEM_ACC_COMP_n_INI(n)        \
        in_dword_masked(HWIO_APCS_COMMON_MEM_ACC_COMP_n_ADDR(n), HWIO_APCS_COMMON_MEM_ACC_COMP_n_RMSK)
#define HWIO_APCS_COMMON_MEM_ACC_COMP_n_INMI(n,mask)    \
        in_dword_masked(HWIO_APCS_COMMON_MEM_ACC_COMP_n_ADDR(n), mask)
#define HWIO_APCS_COMMON_MEM_ACC_COMP_n_OUTI(n,val)    \
        out_dword(HWIO_APCS_COMMON_MEM_ACC_COMP_n_ADDR(n),val)
#define HWIO_APCS_COMMON_MEM_ACC_COMP_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_APCS_COMMON_MEM_ACC_COMP_n_ADDR(n),mask,val,HWIO_APCS_COMMON_MEM_ACC_COMP_n_INI(n))
#define HWIO_APCS_COMMON_MEM_ACC_COMP_n_MEM_ACC_COMP_BMSK                                          0xff
#define HWIO_APCS_COMMON_MEM_ACC_COMP_n_MEM_ACC_COMP_SHFT                                           0x0

#define HWIO_APCS_COMMON_CX_MEM_SVS_ADDR                                                     (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x000003c0)
#define HWIO_APCS_COMMON_CX_MEM_SVS_RMSK                                                            0x1
#define HWIO_APCS_COMMON_CX_MEM_SVS_IN          \
        in_dword_masked(HWIO_APCS_COMMON_CX_MEM_SVS_ADDR, HWIO_APCS_COMMON_CX_MEM_SVS_RMSK)
#define HWIO_APCS_COMMON_CX_MEM_SVS_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_CX_MEM_SVS_ADDR, m)
#define HWIO_APCS_COMMON_CX_MEM_SVS_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_CX_MEM_SVS_ADDR,v)
#define HWIO_APCS_COMMON_CX_MEM_SVS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_CX_MEM_SVS_ADDR,m,v,HWIO_APCS_COMMON_CX_MEM_SVS_IN)
#define HWIO_APCS_COMMON_CX_MEM_SVS_CX_MEM_SVS_BMSK                                                 0x1
#define HWIO_APCS_COMMON_CX_MEM_SVS_CX_MEM_SVS_SHFT                                                 0x0

#define HWIO_APCS_COMMON_ACC_MEM_SVS_SEL_ADDR                                                (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x000003c4)
#define HWIO_APCS_COMMON_ACC_MEM_SVS_SEL_RMSK                                                       0x1
#define HWIO_APCS_COMMON_ACC_MEM_SVS_SEL_IN          \
        in_dword_masked(HWIO_APCS_COMMON_ACC_MEM_SVS_SEL_ADDR, HWIO_APCS_COMMON_ACC_MEM_SVS_SEL_RMSK)
#define HWIO_APCS_COMMON_ACC_MEM_SVS_SEL_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_ACC_MEM_SVS_SEL_ADDR, m)
#define HWIO_APCS_COMMON_ACC_MEM_SVS_SEL_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_ACC_MEM_SVS_SEL_ADDR,v)
#define HWIO_APCS_COMMON_ACC_MEM_SVS_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_ACC_MEM_SVS_SEL_ADDR,m,v,HWIO_APCS_COMMON_ACC_MEM_SVS_SEL_IN)
#define HWIO_APCS_COMMON_ACC_MEM_SVS_SEL_ACC_MEM_SVS_SEL_BMSK                                       0x1
#define HWIO_APCS_COMMON_ACC_MEM_SVS_SEL_ACC_MEM_SVS_SEL_SHFT                                       0x0

#define HWIO_APCS_COMMON_GLADIATOR_HANG_COUNTER_n_ADDR(n)                                    (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000404 + 0x4 * (n))
#define HWIO_APCS_COMMON_GLADIATOR_HANG_COUNTER_n_RMSK                                       0xffffffff
#define HWIO_APCS_COMMON_GLADIATOR_HANG_COUNTER_n_MAXn                                                5
#define HWIO_APCS_COMMON_GLADIATOR_HANG_COUNTER_n_INI(n)        \
        in_dword_masked(HWIO_APCS_COMMON_GLADIATOR_HANG_COUNTER_n_ADDR(n), HWIO_APCS_COMMON_GLADIATOR_HANG_COUNTER_n_RMSK)
#define HWIO_APCS_COMMON_GLADIATOR_HANG_COUNTER_n_INMI(n,mask)    \
        in_dword_masked(HWIO_APCS_COMMON_GLADIATOR_HANG_COUNTER_n_ADDR(n), mask)
#define HWIO_APCS_COMMON_GLADIATOR_HANG_COUNTER_n_GLADIATOR_HANG_VALUE_BMSK                  0xffffffff
#define HWIO_APCS_COMMON_GLADIATOR_HANG_COUNTER_n_GLADIATOR_HANG_VALUE_SHFT                         0x0

#define HWIO_APCS_COMMON_THRESHOLD_n_ADDR(n)                                                 (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x0000041c + 0x4 * (n))
#define HWIO_APCS_COMMON_THRESHOLD_n_RMSK                                                    0xffffffff
#define HWIO_APCS_COMMON_THRESHOLD_n_MAXn                                                             5
#define HWIO_APCS_COMMON_THRESHOLD_n_INI(n)        \
        in_dword_masked(HWIO_APCS_COMMON_THRESHOLD_n_ADDR(n), HWIO_APCS_COMMON_THRESHOLD_n_RMSK)
#define HWIO_APCS_COMMON_THRESHOLD_n_INMI(n,mask)    \
        in_dword_masked(HWIO_APCS_COMMON_THRESHOLD_n_ADDR(n), mask)
#define HWIO_APCS_COMMON_THRESHOLD_n_OUTI(n,val)    \
        out_dword(HWIO_APCS_COMMON_THRESHOLD_n_ADDR(n),val)
#define HWIO_APCS_COMMON_THRESHOLD_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_APCS_COMMON_THRESHOLD_n_ADDR(n),mask,val,HWIO_APCS_COMMON_THRESHOLD_n_INI(n))
#define HWIO_APCS_COMMON_THRESHOLD_n_THRESHOLD_VALUE_BMSK                                    0xffffffff
#define HWIO_APCS_COMMON_THRESHOLD_n_THRESHOLD_VALUE_SHFT                                           0x0

#define HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_ADDR                                          (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000434)
#define HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_RMSK                                               0xf7d
#define HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_IN          \
        in_dword_masked(HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_ADDR, HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_RMSK)
#define HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_ADDR, m)
#define HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_ADDR,v)
#define HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_ADDR,m,v,HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_IN)
#define HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_PCIO_COUNTER_STS_BMSK                              0x800
#define HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_PCIO_COUNTER_STS_SHFT                                0xb
#define HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_M2_COUNTER_STS_BMSK                                0x400
#define HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_M2_COUNTER_STS_SHFT                                  0xa
#define HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_M1_COUNTER_STS_BMSK                                0x200
#define HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_M1_COUNTER_STS_SHFT                                  0x9
#define HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_IO_COUNTER_STS_BMSK                                0x100
#define HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_IO_COUNTER_STS_SHFT                                  0x8
#define HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_ACE_COUNTER_STS_BMSK                                0x40
#define HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_ACE_COUNTER_STS_SHFT                                 0x6
#define HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_PCIO_COUNTER_EN_BMSK                                0x20
#define HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_PCIO_COUNTER_EN_SHFT                                 0x5
#define HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_M2_COUNTER_EN_BMSK                                  0x10
#define HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_M2_COUNTER_EN_SHFT                                   0x4
#define HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_M1_COUNTER_EN_BMSK                                   0x8
#define HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_M1_COUNTER_EN_SHFT                                   0x3
#define HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_IO_COUNTER_EN_BMSK                                   0x4
#define HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_IO_COUNTER_EN_SHFT                                   0x2
#define HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_ACE_COUNTER_EN_BMSK                                  0x1
#define HWIO_APCS_COMMON_GLADIATOR_HANG_CONFIG_ACE_COUNTER_EN_SHFT                                  0x0

#define HWIO_APCS_COMMON_GIC_ERR_IPC_ADDR                                                    (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000438)
#define HWIO_APCS_COMMON_GIC_ERR_IPC_RMSK                                                           0x7
#define HWIO_APCS_COMMON_GIC_ERR_IPC_IN          \
        in_dword_masked(HWIO_APCS_COMMON_GIC_ERR_IPC_ADDR, HWIO_APCS_COMMON_GIC_ERR_IPC_RMSK)
#define HWIO_APCS_COMMON_GIC_ERR_IPC_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_GIC_ERR_IPC_ADDR, m)
#define HWIO_APCS_COMMON_GIC_ERR_IPC_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_GIC_ERR_IPC_ADDR,v)
#define HWIO_APCS_COMMON_GIC_ERR_IPC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_GIC_ERR_IPC_ADDR,m,v,HWIO_APCS_COMMON_GIC_ERR_IPC_IN)
#define HWIO_APCS_COMMON_GIC_ERR_IPC_ECC_FATAL_BMSK                                                 0x4
#define HWIO_APCS_COMMON_GIC_ERR_IPC_ECC_FATAL_SHFT                                                 0x2
#define HWIO_APCS_COMMON_GIC_ERR_IPC_AXIM_ERROR_CLR_BMSK                                            0x2
#define HWIO_APCS_COMMON_GIC_ERR_IPC_AXIM_ERROR_CLR_SHFT                                            0x1
#define HWIO_APCS_COMMON_GIC_ERR_IPC_AXIM_ERROR_BMSK                                                0x1
#define HWIO_APCS_COMMON_GIC_ERR_IPC_AXIM_ERROR_SHFT                                                0x0

#define HWIO_APCS_COMMON_FIRST_CORE_HANG_ADDR                                                (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000228)
#define HWIO_APCS_COMMON_FIRST_CORE_HANG_RMSK                                                      0xff
#define HWIO_APCS_COMMON_FIRST_CORE_HANG_IN          \
        in_dword_masked(HWIO_APCS_COMMON_FIRST_CORE_HANG_ADDR, HWIO_APCS_COMMON_FIRST_CORE_HANG_RMSK)
#define HWIO_APCS_COMMON_FIRST_CORE_HANG_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_FIRST_CORE_HANG_ADDR, m)
#define HWIO_APCS_COMMON_FIRST_CORE_HANG_CORE_NUMBER_BMSK                                          0xff
#define HWIO_APCS_COMMON_FIRST_CORE_HANG_CORE_NUMBER_SHFT                                           0x0

#define HWIO_APCS_COMMON_GLADIATOR_FIRST_CHANNEL_HANG_ADDR                                   (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x0000043c)
#define HWIO_APCS_COMMON_GLADIATOR_FIRST_CHANNEL_HANG_RMSK                                         0x3d
#define HWIO_APCS_COMMON_GLADIATOR_FIRST_CHANNEL_HANG_IN          \
        in_dword_masked(HWIO_APCS_COMMON_GLADIATOR_FIRST_CHANNEL_HANG_ADDR, HWIO_APCS_COMMON_GLADIATOR_FIRST_CHANNEL_HANG_RMSK)
#define HWIO_APCS_COMMON_GLADIATOR_FIRST_CHANNEL_HANG_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_GLADIATOR_FIRST_CHANNEL_HANG_ADDR, m)
#define HWIO_APCS_COMMON_GLADIATOR_FIRST_CHANNEL_HANG_PCIO_CHANNEL_BMSK                            0x20
#define HWIO_APCS_COMMON_GLADIATOR_FIRST_CHANNEL_HANG_PCIO_CHANNEL_SHFT                             0x5
#define HWIO_APCS_COMMON_GLADIATOR_FIRST_CHANNEL_HANG_M2_CHANNEL_BMSK                              0x10
#define HWIO_APCS_COMMON_GLADIATOR_FIRST_CHANNEL_HANG_M2_CHANNEL_SHFT                               0x4
#define HWIO_APCS_COMMON_GLADIATOR_FIRST_CHANNEL_HANG_M1_CHANNEL_BMSK                               0x8
#define HWIO_APCS_COMMON_GLADIATOR_FIRST_CHANNEL_HANG_M1_CHANNEL_SHFT                               0x3
#define HWIO_APCS_COMMON_GLADIATOR_FIRST_CHANNEL_HANG_IO_CHANNEL_BMSK                               0x4
#define HWIO_APCS_COMMON_GLADIATOR_FIRST_CHANNEL_HANG_IO_CHANNEL_SHFT                               0x2
#define HWIO_APCS_COMMON_GLADIATOR_FIRST_CHANNEL_HANG_ACE_CHANNEL_BMSK                              0x1
#define HWIO_APCS_COMMON_GLADIATOR_FIRST_CHANNEL_HANG_ACE_CHANNEL_SHFT                              0x0

#define HWIO_APCS_COMMON_GLADIATOR_HANG_DBG_STS_0_ADDR                                       (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000440)
#define HWIO_APCS_COMMON_GLADIATOR_HANG_DBG_STS_0_RMSK                                       0xffffffff
#define HWIO_APCS_COMMON_GLADIATOR_HANG_DBG_STS_0_IN          \
        in_dword_masked(HWIO_APCS_COMMON_GLADIATOR_HANG_DBG_STS_0_ADDR, HWIO_APCS_COMMON_GLADIATOR_HANG_DBG_STS_0_RMSK)
#define HWIO_APCS_COMMON_GLADIATOR_HANG_DBG_STS_0_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_GLADIATOR_HANG_DBG_STS_0_ADDR, m)
#define HWIO_APCS_COMMON_GLADIATOR_HANG_DBG_STS_0_GLADIATOR_HANG_DBG_STS_31_0_BMSK           0xffffffff
#define HWIO_APCS_COMMON_GLADIATOR_HANG_DBG_STS_0_GLADIATOR_HANG_DBG_STS_31_0_SHFT                  0x0

#define HWIO_APCS_COMMON_GLADIATOR_HANG_DBG_STS_1_ADDR                                       (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000444)
#define HWIO_APCS_COMMON_GLADIATOR_HANG_DBG_STS_1_RMSK                                            0xfff
#define HWIO_APCS_COMMON_GLADIATOR_HANG_DBG_STS_1_IN          \
        in_dword_masked(HWIO_APCS_COMMON_GLADIATOR_HANG_DBG_STS_1_ADDR, HWIO_APCS_COMMON_GLADIATOR_HANG_DBG_STS_1_RMSK)
#define HWIO_APCS_COMMON_GLADIATOR_HANG_DBG_STS_1_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_GLADIATOR_HANG_DBG_STS_1_ADDR, m)
#define HWIO_APCS_COMMON_GLADIATOR_HANG_DBG_STS_1_GLADIATOR_HANG_DBG_STS_42_32_BMSK               0xfff
#define HWIO_APCS_COMMON_GLADIATOR_HANG_DBG_STS_1_GLADIATOR_HANG_DBG_STS_42_32_SHFT                 0x0

#define HWIO_APCS_COMMON_CORE_HANG_DBG_STS_0_ADDR                                            (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000448)
#define HWIO_APCS_COMMON_CORE_HANG_DBG_STS_0_RMSK                                            0xffffffff
#define HWIO_APCS_COMMON_CORE_HANG_DBG_STS_0_IN          \
        in_dword_masked(HWIO_APCS_COMMON_CORE_HANG_DBG_STS_0_ADDR, HWIO_APCS_COMMON_CORE_HANG_DBG_STS_0_RMSK)
#define HWIO_APCS_COMMON_CORE_HANG_DBG_STS_0_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_CORE_HANG_DBG_STS_0_ADDR, m)
#define HWIO_APCS_COMMON_CORE_HANG_DBG_STS_0_CORE_HANG_DBG_STS_31_0_BMSK                     0xffffffff
#define HWIO_APCS_COMMON_CORE_HANG_DBG_STS_0_CORE_HANG_DBG_STS_31_0_SHFT                            0x0

#define HWIO_APCS_COMMON_CORE_HANG_DBG_STS_1_ADDR                                            (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x0000044c)
#define HWIO_APCS_COMMON_CORE_HANG_DBG_STS_1_RMSK                                              0xffffff
#define HWIO_APCS_COMMON_CORE_HANG_DBG_STS_1_IN          \
        in_dword_masked(HWIO_APCS_COMMON_CORE_HANG_DBG_STS_1_ADDR, HWIO_APCS_COMMON_CORE_HANG_DBG_STS_1_RMSK)
#define HWIO_APCS_COMMON_CORE_HANG_DBG_STS_1_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_CORE_HANG_DBG_STS_1_ADDR, m)
#define HWIO_APCS_COMMON_CORE_HANG_DBG_STS_1_GLADIATOR_HANG_DBG_STS_55_32_BMSK                 0xffffff
#define HWIO_APCS_COMMON_CORE_HANG_DBG_STS_1_GLADIATOR_HANG_DBG_STS_55_32_SHFT                      0x0

#define HWIO_APCS_COMMON_QOS_P0_SILVER_ADDR                                                  (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000500)
#define HWIO_APCS_COMMON_QOS_P0_SILVER_RMSK                                                        0xff
#define HWIO_APCS_COMMON_QOS_P0_SILVER_IN          \
        in_dword_masked(HWIO_APCS_COMMON_QOS_P0_SILVER_ADDR, HWIO_APCS_COMMON_QOS_P0_SILVER_RMSK)
#define HWIO_APCS_COMMON_QOS_P0_SILVER_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_QOS_P0_SILVER_ADDR, m)
#define HWIO_APCS_COMMON_QOS_P0_SILVER_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_QOS_P0_SILVER_ADDR,v)
#define HWIO_APCS_COMMON_QOS_P0_SILVER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_QOS_P0_SILVER_ADDR,m,v,HWIO_APCS_COMMON_QOS_P0_SILVER_IN)
#define HWIO_APCS_COMMON_QOS_P0_SILVER_AWQOS_BMSK                                                  0xf0
#define HWIO_APCS_COMMON_QOS_P0_SILVER_AWQOS_SHFT                                                   0x4
#define HWIO_APCS_COMMON_QOS_P0_SILVER_ARQOS_BMSK                                                   0xf
#define HWIO_APCS_COMMON_QOS_P0_SILVER_ARQOS_SHFT                                                   0x0

#define HWIO_APCS_COMMON_QOS_P1_SILVER_ADDR                                                  (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000504)
#define HWIO_APCS_COMMON_QOS_P1_SILVER_RMSK                                                        0xff
#define HWIO_APCS_COMMON_QOS_P1_SILVER_IN          \
        in_dword_masked(HWIO_APCS_COMMON_QOS_P1_SILVER_ADDR, HWIO_APCS_COMMON_QOS_P1_SILVER_RMSK)
#define HWIO_APCS_COMMON_QOS_P1_SILVER_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_QOS_P1_SILVER_ADDR, m)
#define HWIO_APCS_COMMON_QOS_P1_SILVER_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_QOS_P1_SILVER_ADDR,v)
#define HWIO_APCS_COMMON_QOS_P1_SILVER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_QOS_P1_SILVER_ADDR,m,v,HWIO_APCS_COMMON_QOS_P1_SILVER_IN)
#define HWIO_APCS_COMMON_QOS_P1_SILVER_AWQOS_BMSK                                                  0xf0
#define HWIO_APCS_COMMON_QOS_P1_SILVER_AWQOS_SHFT                                                   0x4
#define HWIO_APCS_COMMON_QOS_P1_SILVER_ARQOS_BMSK                                                   0xf
#define HWIO_APCS_COMMON_QOS_P1_SILVER_ARQOS_SHFT                                                   0x0

#define HWIO_APCS_COMMON_QOS_P0_GOLD_ADDR                                                    (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x00000508)
#define HWIO_APCS_COMMON_QOS_P0_GOLD_RMSK                                                          0xff
#define HWIO_APCS_COMMON_QOS_P0_GOLD_IN          \
        in_dword_masked(HWIO_APCS_COMMON_QOS_P0_GOLD_ADDR, HWIO_APCS_COMMON_QOS_P0_GOLD_RMSK)
#define HWIO_APCS_COMMON_QOS_P0_GOLD_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_QOS_P0_GOLD_ADDR, m)
#define HWIO_APCS_COMMON_QOS_P0_GOLD_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_QOS_P0_GOLD_ADDR,v)
#define HWIO_APCS_COMMON_QOS_P0_GOLD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_QOS_P0_GOLD_ADDR,m,v,HWIO_APCS_COMMON_QOS_P0_GOLD_IN)
#define HWIO_APCS_COMMON_QOS_P0_GOLD_AWQOS_BMSK                                                    0xf0
#define HWIO_APCS_COMMON_QOS_P0_GOLD_AWQOS_SHFT                                                     0x4
#define HWIO_APCS_COMMON_QOS_P0_GOLD_ARQOS_BMSK                                                     0xf
#define HWIO_APCS_COMMON_QOS_P0_GOLD_ARQOS_SHFT                                                     0x0

#define HWIO_APCS_COMMON_QOS_P1_GOLD_ADDR                                                    (APCS_COMMON_APSS_SHARED_REG_BASE      + 0x0000050c)
#define HWIO_APCS_COMMON_QOS_P1_GOLD_RMSK                                                          0xff
#define HWIO_APCS_COMMON_QOS_P1_GOLD_IN          \
        in_dword_masked(HWIO_APCS_COMMON_QOS_P1_GOLD_ADDR, HWIO_APCS_COMMON_QOS_P1_GOLD_RMSK)
#define HWIO_APCS_COMMON_QOS_P1_GOLD_INM(m)      \
        in_dword_masked(HWIO_APCS_COMMON_QOS_P1_GOLD_ADDR, m)
#define HWIO_APCS_COMMON_QOS_P1_GOLD_OUT(v)      \
        out_dword(HWIO_APCS_COMMON_QOS_P1_GOLD_ADDR,v)
#define HWIO_APCS_COMMON_QOS_P1_GOLD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_COMMON_QOS_P1_GOLD_ADDR,m,v,HWIO_APCS_COMMON_QOS_P1_GOLD_IN)
#define HWIO_APCS_COMMON_QOS_P1_GOLD_AWQOS_BMSK                                                    0xf0
#define HWIO_APCS_COMMON_QOS_P1_GOLD_AWQOS_SHFT                                                     0x4
#define HWIO_APCS_COMMON_QOS_P1_GOLD_ARQOS_BMSK                                                     0xf
#define HWIO_APCS_COMMON_QOS_P1_GOLD_ARQOS_SHFT                                                     0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_WDT_TMR1_APSS_WDT
 *--------------------------------------------------------------------------*/

#define APCS_WDT_TMR1_APSS_WDT_REG_BASE                                    (A53SS_BASE      + 0x00017000)

#define HWIO_APCS_WDT_TMR1_WDOG_SECURE_ADDR                                (APCS_WDT_TMR1_APSS_WDT_REG_BASE      + 0x00000000)
#define HWIO_APCS_WDT_TMR1_WDOG_SECURE_RMSK                                       0x1
#define HWIO_APCS_WDT_TMR1_WDOG_SECURE_IN          \
        in_dword_masked(HWIO_APCS_WDT_TMR1_WDOG_SECURE_ADDR, HWIO_APCS_WDT_TMR1_WDOG_SECURE_RMSK)
#define HWIO_APCS_WDT_TMR1_WDOG_SECURE_INM(m)      \
        in_dword_masked(HWIO_APCS_WDT_TMR1_WDOG_SECURE_ADDR, m)
#define HWIO_APCS_WDT_TMR1_WDOG_SECURE_OUT(v)      \
        out_dword(HWIO_APCS_WDT_TMR1_WDOG_SECURE_ADDR,v)
#define HWIO_APCS_WDT_TMR1_WDOG_SECURE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_WDT_TMR1_WDOG_SECURE_ADDR,m,v,HWIO_APCS_WDT_TMR1_WDOG_SECURE_IN)
#define HWIO_APCS_WDT_TMR1_WDOG_SECURE_WDT_BMSK                                   0x1
#define HWIO_APCS_WDT_TMR1_WDOG_SECURE_WDT_SHFT                                   0x0

#define HWIO_APCS_WDT_TMR1_WDOG_RESET_ADDR                                 (APCS_WDT_TMR1_APSS_WDT_REG_BASE      + 0x00000004)
#define HWIO_APCS_WDT_TMR1_WDOG_RESET_RMSK                                        0x1
#define HWIO_APCS_WDT_TMR1_WDOG_RESET_OUT(v)      \
        out_dword(HWIO_APCS_WDT_TMR1_WDOG_RESET_ADDR,v)
#define HWIO_APCS_WDT_TMR1_WDOG_RESET_RESET_BMSK                                  0x1
#define HWIO_APCS_WDT_TMR1_WDOG_RESET_RESET_SHFT                                  0x0

#define HWIO_APCS_WDT_TMR1_WDOG_CTL_ADDR                                   (APCS_WDT_TMR1_APSS_WDT_REG_BASE      + 0x00000008)
#define HWIO_APCS_WDT_TMR1_WDOG_CTL_RMSK                                          0x3
#define HWIO_APCS_WDT_TMR1_WDOG_CTL_OUT(v)      \
        out_dword(HWIO_APCS_WDT_TMR1_WDOG_CTL_ADDR,v)
#define HWIO_APCS_WDT_TMR1_WDOG_CTL_UNMASKED_INT_ENABLE_BMSK                      0x2
#define HWIO_APCS_WDT_TMR1_WDOG_CTL_UNMASKED_INT_ENABLE_SHFT                      0x1
#define HWIO_APCS_WDT_TMR1_WDOG_CTL_ENABLE_BMSK                                   0x1
#define HWIO_APCS_WDT_TMR1_WDOG_CTL_ENABLE_SHFT                                   0x0

#define HWIO_APCS_WDT_TMR1_WDOG_STATUS_ADDR                                (APCS_WDT_TMR1_APSS_WDT_REG_BASE      + 0x0000000c)
#define HWIO_APCS_WDT_TMR1_WDOG_STATUS_RMSK                                0x801fffff
#define HWIO_APCS_WDT_TMR1_WDOG_STATUS_IN          \
        in_dword_masked(HWIO_APCS_WDT_TMR1_WDOG_STATUS_ADDR, HWIO_APCS_WDT_TMR1_WDOG_STATUS_RMSK)
#define HWIO_APCS_WDT_TMR1_WDOG_STATUS_INM(m)      \
        in_dword_masked(HWIO_APCS_WDT_TMR1_WDOG_STATUS_ADDR, m)
#define HWIO_APCS_WDT_TMR1_WDOG_STATUS_FROZEN_BMSK                         0x80000000
#define HWIO_APCS_WDT_TMR1_WDOG_STATUS_FROZEN_SHFT                               0x1f
#define HWIO_APCS_WDT_TMR1_WDOG_STATUS_COUNT_BMSK                            0x1ffffe
#define HWIO_APCS_WDT_TMR1_WDOG_STATUS_COUNT_SHFT                                 0x1
#define HWIO_APCS_WDT_TMR1_WDOG_STATUS_EXPIRED_STATUS_BMSK                        0x1
#define HWIO_APCS_WDT_TMR1_WDOG_STATUS_EXPIRED_STATUS_SHFT                        0x0

#define HWIO_APCS_WDT_TMR1_WDOG_BARK_TIME_ADDR                             (APCS_WDT_TMR1_APSS_WDT_REG_BASE      + 0x00000010)
#define HWIO_APCS_WDT_TMR1_WDOG_BARK_TIME_RMSK                                0xfffff
#define HWIO_APCS_WDT_TMR1_WDOG_BARK_TIME_IN          \
        in_dword_masked(HWIO_APCS_WDT_TMR1_WDOG_BARK_TIME_ADDR, HWIO_APCS_WDT_TMR1_WDOG_BARK_TIME_RMSK)
#define HWIO_APCS_WDT_TMR1_WDOG_BARK_TIME_INM(m)      \
        in_dword_masked(HWIO_APCS_WDT_TMR1_WDOG_BARK_TIME_ADDR, m)
#define HWIO_APCS_WDT_TMR1_WDOG_BARK_TIME_OUT(v)      \
        out_dword(HWIO_APCS_WDT_TMR1_WDOG_BARK_TIME_ADDR,v)
#define HWIO_APCS_WDT_TMR1_WDOG_BARK_TIME_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_WDT_TMR1_WDOG_BARK_TIME_ADDR,m,v,HWIO_APCS_WDT_TMR1_WDOG_BARK_TIME_IN)
#define HWIO_APCS_WDT_TMR1_WDOG_BARK_TIME_DATA_BMSK                           0xfffff
#define HWIO_APCS_WDT_TMR1_WDOG_BARK_TIME_DATA_SHFT                               0x0

#define HWIO_APCS_WDT_TMR1_WDOG_BITE_TIME_ADDR                             (APCS_WDT_TMR1_APSS_WDT_REG_BASE      + 0x00000014)
#define HWIO_APCS_WDT_TMR1_WDOG_BITE_TIME_RMSK                                0xfffff
#define HWIO_APCS_WDT_TMR1_WDOG_BITE_TIME_IN          \
        in_dword_masked(HWIO_APCS_WDT_TMR1_WDOG_BITE_TIME_ADDR, HWIO_APCS_WDT_TMR1_WDOG_BITE_TIME_RMSK)
#define HWIO_APCS_WDT_TMR1_WDOG_BITE_TIME_INM(m)      \
        in_dword_masked(HWIO_APCS_WDT_TMR1_WDOG_BITE_TIME_ADDR, m)
#define HWIO_APCS_WDT_TMR1_WDOG_BITE_TIME_OUT(v)      \
        out_dword(HWIO_APCS_WDT_TMR1_WDOG_BITE_TIME_ADDR,v)
#define HWIO_APCS_WDT_TMR1_WDOG_BITE_TIME_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_WDT_TMR1_WDOG_BITE_TIME_ADDR,m,v,HWIO_APCS_WDT_TMR1_WDOG_BITE_TIME_IN)
#define HWIO_APCS_WDT_TMR1_WDOG_BITE_TIME_DATA_BMSK                           0xfffff
#define HWIO_APCS_WDT_TMR1_WDOG_BITE_TIME_DATA_SHFT                               0x0

#define HWIO_APCS_WDT_TMR1_WDOG_TEST_LOAD_STATUS_ADDR                      (APCS_WDT_TMR1_APSS_WDT_REG_BASE      + 0x00000018)
#define HWIO_APCS_WDT_TMR1_WDOG_TEST_LOAD_STATUS_RMSK                             0x1
#define HWIO_APCS_WDT_TMR1_WDOG_TEST_LOAD_STATUS_IN          \
        in_dword_masked(HWIO_APCS_WDT_TMR1_WDOG_TEST_LOAD_STATUS_ADDR, HWIO_APCS_WDT_TMR1_WDOG_TEST_LOAD_STATUS_RMSK)
#define HWIO_APCS_WDT_TMR1_WDOG_TEST_LOAD_STATUS_INM(m)      \
        in_dword_masked(HWIO_APCS_WDT_TMR1_WDOG_TEST_LOAD_STATUS_ADDR, m)
#define HWIO_APCS_WDT_TMR1_WDOG_TEST_LOAD_STATUS_SYNC_STATUS_BMSK                 0x1
#define HWIO_APCS_WDT_TMR1_WDOG_TEST_LOAD_STATUS_SYNC_STATUS_SHFT                 0x0

#define HWIO_APCS_WDT_TMR1_WDOG_TEST_LOAD_ADDR                             (APCS_WDT_TMR1_APSS_WDT_REG_BASE      + 0x0000001c)
#define HWIO_APCS_WDT_TMR1_WDOG_TEST_LOAD_RMSK                                    0x1
#define HWIO_APCS_WDT_TMR1_WDOG_TEST_LOAD_OUT(v)      \
        out_dword(HWIO_APCS_WDT_TMR1_WDOG_TEST_LOAD_ADDR,v)
#define HWIO_APCS_WDT_TMR1_WDOG_TEST_LOAD_LOAD_BMSK                               0x1
#define HWIO_APCS_WDT_TMR1_WDOG_TEST_LOAD_LOAD_SHFT                               0x0

#define HWIO_APCS_WDT_TMR1_WDOG_TEST_ADDR                                  (APCS_WDT_TMR1_APSS_WDT_REG_BASE      + 0x00000020)
#define HWIO_APCS_WDT_TMR1_WDOG_TEST_RMSK                                     0xfffff
#define HWIO_APCS_WDT_TMR1_WDOG_TEST_IN          \
        in_dword_masked(HWIO_APCS_WDT_TMR1_WDOG_TEST_ADDR, HWIO_APCS_WDT_TMR1_WDOG_TEST_RMSK)
#define HWIO_APCS_WDT_TMR1_WDOG_TEST_INM(m)      \
        in_dword_masked(HWIO_APCS_WDT_TMR1_WDOG_TEST_ADDR, m)
#define HWIO_APCS_WDT_TMR1_WDOG_TEST_OUT(v)      \
        out_dword(HWIO_APCS_WDT_TMR1_WDOG_TEST_ADDR,v)
#define HWIO_APCS_WDT_TMR1_WDOG_TEST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_WDT_TMR1_WDOG_TEST_ADDR,m,v,HWIO_APCS_WDT_TMR1_WDOG_TEST_IN)
#define HWIO_APCS_WDT_TMR1_WDOG_TEST_LOAD_VALUE_BMSK                          0xfffff
#define HWIO_APCS_WDT_TMR1_WDOG_TEST_LOAD_VALUE_SHFT                              0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_ALIAS0_APSS_ACS
 *--------------------------------------------------------------------------*/

#define APCS_ALIAS0_APSS_ACS_REG_BASE                                                       (A53SS_BASE      + 0x00188000)

#define HWIO_APCS_ALIAS0_CORE_HANG_THRESHOLD_ADDR                                           (APCS_ALIAS0_APSS_ACS_REG_BASE      + 0x000000b0)
#define HWIO_APCS_ALIAS0_CORE_HANG_THRESHOLD_RMSK                                           0xffffffff
#define HWIO_APCS_ALIAS0_CORE_HANG_THRESHOLD_IN          \
        in_dword_masked(HWIO_APCS_ALIAS0_CORE_HANG_THRESHOLD_ADDR, HWIO_APCS_ALIAS0_CORE_HANG_THRESHOLD_RMSK)
#define HWIO_APCS_ALIAS0_CORE_HANG_THRESHOLD_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS0_CORE_HANG_THRESHOLD_ADDR, m)
#define HWIO_APCS_ALIAS0_CORE_HANG_THRESHOLD_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS0_CORE_HANG_THRESHOLD_ADDR,v)
#define HWIO_APCS_ALIAS0_CORE_HANG_THRESHOLD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS0_CORE_HANG_THRESHOLD_ADDR,m,v,HWIO_APCS_ALIAS0_CORE_HANG_THRESHOLD_IN)
#define HWIO_APCS_ALIAS0_CORE_HANG_THRESHOLD_CORE_HANG_THRESHOLD_VALUE_BMSK                 0xffffffff
#define HWIO_APCS_ALIAS0_CORE_HANG_THRESHOLD_CORE_HANG_THRESHOLD_VALUE_SHFT                        0x0

#define HWIO_APCS_ALIAS0_CORE_HANG_VALUE_ADDR                                               (APCS_ALIAS0_APSS_ACS_REG_BASE      + 0x000000b4)
#define HWIO_APCS_ALIAS0_CORE_HANG_VALUE_RMSK                                               0xffffffff
#define HWIO_APCS_ALIAS0_CORE_HANG_VALUE_IN          \
        in_dword_masked(HWIO_APCS_ALIAS0_CORE_HANG_VALUE_ADDR, HWIO_APCS_ALIAS0_CORE_HANG_VALUE_RMSK)
#define HWIO_APCS_ALIAS0_CORE_HANG_VALUE_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS0_CORE_HANG_VALUE_ADDR, m)
#define HWIO_APCS_ALIAS0_CORE_HANG_VALUE_VALUE_WHEN_HUNG_BMSK                               0xffffffff
#define HWIO_APCS_ALIAS0_CORE_HANG_VALUE_VALUE_WHEN_HUNG_SHFT                                      0x0

#define HWIO_APCS_ALIAS0_CORE_HANG_CONFIG_ADDR                                              (APCS_ALIAS0_APSS_ACS_REG_BASE      + 0x000000b8)
#define HWIO_APCS_ALIAS0_CORE_HANG_CONFIG_RMSK                                                   0x3fb
#define HWIO_APCS_ALIAS0_CORE_HANG_CONFIG_IN          \
        in_dword_masked(HWIO_APCS_ALIAS0_CORE_HANG_CONFIG_ADDR, HWIO_APCS_ALIAS0_CORE_HANG_CONFIG_RMSK)
#define HWIO_APCS_ALIAS0_CORE_HANG_CONFIG_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS0_CORE_HANG_CONFIG_ADDR, m)
#define HWIO_APCS_ALIAS0_CORE_HANG_CONFIG_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS0_CORE_HANG_CONFIG_ADDR,v)
#define HWIO_APCS_ALIAS0_CORE_HANG_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS0_CORE_HANG_CONFIG_ADDR,m,v,HWIO_APCS_ALIAS0_CORE_HANG_CONFIG_IN)
#define HWIO_APCS_ALIAS0_CORE_HANG_CONFIG_PMUEVENT_LEGACY_GOLD_SEL_BMSK                          0x200
#define HWIO_APCS_ALIAS0_CORE_HANG_CONFIG_PMUEVENT_LEGACY_GOLD_SEL_SHFT                            0x9
#define HWIO_APCS_ALIAS0_CORE_HANG_CONFIG_PMUEVENT_SEL_BMSK                                      0x1f0
#define HWIO_APCS_ALIAS0_CORE_HANG_CONFIG_PMUEVENT_SEL_SHFT                                        0x4
#define HWIO_APCS_ALIAS0_CORE_HANG_CONFIG_CORE_HANG_RESET_BMSK                                     0x8
#define HWIO_APCS_ALIAS0_CORE_HANG_CONFIG_CORE_HANG_RESET_SHFT                                     0x3
#define HWIO_APCS_ALIAS0_CORE_HANG_CONFIG_CORE_HANG_COUNTER_EN_BMSK                                0x2
#define HWIO_APCS_ALIAS0_CORE_HANG_CONFIG_CORE_HANG_COUNTER_EN_SHFT                                0x1
#define HWIO_APCS_ALIAS0_CORE_HANG_CONFIG_CORE_HANG_STATUS_BMSK                                    0x1
#define HWIO_APCS_ALIAS0_CORE_HANG_CONFIG_CORE_HANG_STATUS_SHFT                                    0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_ALIAS1_APSS_ACS
 *--------------------------------------------------------------------------*/

#define APCS_ALIAS1_APSS_ACS_REG_BASE                                                       (A53SS_BASE      + 0x00198000)

#define HWIO_APCS_ALIAS1_CORE_HANG_THRESHOLD_ADDR                                           (APCS_ALIAS1_APSS_ACS_REG_BASE      + 0x000000b0)
#define HWIO_APCS_ALIAS1_CORE_HANG_THRESHOLD_RMSK                                           0xffffffff
#define HWIO_APCS_ALIAS1_CORE_HANG_THRESHOLD_IN          \
        in_dword_masked(HWIO_APCS_ALIAS1_CORE_HANG_THRESHOLD_ADDR, HWIO_APCS_ALIAS1_CORE_HANG_THRESHOLD_RMSK)
#define HWIO_APCS_ALIAS1_CORE_HANG_THRESHOLD_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS1_CORE_HANG_THRESHOLD_ADDR, m)
#define HWIO_APCS_ALIAS1_CORE_HANG_THRESHOLD_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS1_CORE_HANG_THRESHOLD_ADDR,v)
#define HWIO_APCS_ALIAS1_CORE_HANG_THRESHOLD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS1_CORE_HANG_THRESHOLD_ADDR,m,v,HWIO_APCS_ALIAS1_CORE_HANG_THRESHOLD_IN)
#define HWIO_APCS_ALIAS1_CORE_HANG_THRESHOLD_CORE_HANG_THRESHOLD_VALUE_BMSK                 0xffffffff
#define HWIO_APCS_ALIAS1_CORE_HANG_THRESHOLD_CORE_HANG_THRESHOLD_VALUE_SHFT                        0x0

#define HWIO_APCS_ALIAS1_CORE_HANG_VALUE_ADDR                                               (APCS_ALIAS1_APSS_ACS_REG_BASE      + 0x000000b4)
#define HWIO_APCS_ALIAS1_CORE_HANG_VALUE_RMSK                                               0xffffffff
#define HWIO_APCS_ALIAS1_CORE_HANG_VALUE_IN          \
        in_dword_masked(HWIO_APCS_ALIAS1_CORE_HANG_VALUE_ADDR, HWIO_APCS_ALIAS1_CORE_HANG_VALUE_RMSK)
#define HWIO_APCS_ALIAS1_CORE_HANG_VALUE_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS1_CORE_HANG_VALUE_ADDR, m)
#define HWIO_APCS_ALIAS1_CORE_HANG_VALUE_VALUE_WHEN_HUNG_BMSK                               0xffffffff
#define HWIO_APCS_ALIAS1_CORE_HANG_VALUE_VALUE_WHEN_HUNG_SHFT                                      0x0

#define HWIO_APCS_ALIAS1_CORE_HANG_CONFIG_ADDR                                              (APCS_ALIAS1_APSS_ACS_REG_BASE      + 0x000000b8)
#define HWIO_APCS_ALIAS1_CORE_HANG_CONFIG_RMSK                                                   0x3fb
#define HWIO_APCS_ALIAS1_CORE_HANG_CONFIG_IN          \
        in_dword_masked(HWIO_APCS_ALIAS1_CORE_HANG_CONFIG_ADDR, HWIO_APCS_ALIAS1_CORE_HANG_CONFIG_RMSK)
#define HWIO_APCS_ALIAS1_CORE_HANG_CONFIG_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS1_CORE_HANG_CONFIG_ADDR, m)
#define HWIO_APCS_ALIAS1_CORE_HANG_CONFIG_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS1_CORE_HANG_CONFIG_ADDR,v)
#define HWIO_APCS_ALIAS1_CORE_HANG_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS1_CORE_HANG_CONFIG_ADDR,m,v,HWIO_APCS_ALIAS1_CORE_HANG_CONFIG_IN)
#define HWIO_APCS_ALIAS1_CORE_HANG_CONFIG_PMUEVENT_LEGACY_GOLD_SEL_BMSK                          0x200
#define HWIO_APCS_ALIAS1_CORE_HANG_CONFIG_PMUEVENT_LEGACY_GOLD_SEL_SHFT                            0x9
#define HWIO_APCS_ALIAS1_CORE_HANG_CONFIG_PMUEVENT_SEL_BMSK                                      0x1f0
#define HWIO_APCS_ALIAS1_CORE_HANG_CONFIG_PMUEVENT_SEL_SHFT                                        0x4
#define HWIO_APCS_ALIAS1_CORE_HANG_CONFIG_CORE_HANG_RESET_BMSK                                     0x8
#define HWIO_APCS_ALIAS1_CORE_HANG_CONFIG_CORE_HANG_RESET_SHFT                                     0x3
#define HWIO_APCS_ALIAS1_CORE_HANG_CONFIG_CORE_HANG_COUNTER_EN_BMSK                                0x2
#define HWIO_APCS_ALIAS1_CORE_HANG_CONFIG_CORE_HANG_COUNTER_EN_SHFT                                0x1
#define HWIO_APCS_ALIAS1_CORE_HANG_CONFIG_CORE_HANG_STATUS_BMSK                                    0x1
#define HWIO_APCS_ALIAS1_CORE_HANG_CONFIG_CORE_HANG_STATUS_SHFT                                    0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_ALIAS2_APSS_ACS
 *--------------------------------------------------------------------------*/

#define APCS_ALIAS2_APSS_ACS_REG_BASE                                                       (A53SS_BASE      + 0x001a8000)

#define HWIO_APCS_ALIAS2_CORE_HANG_THRESHOLD_ADDR                                           (APCS_ALIAS2_APSS_ACS_REG_BASE      + 0x000000b0)
#define HWIO_APCS_ALIAS2_CORE_HANG_THRESHOLD_RMSK                                           0xffffffff
#define HWIO_APCS_ALIAS2_CORE_HANG_THRESHOLD_IN          \
        in_dword_masked(HWIO_APCS_ALIAS2_CORE_HANG_THRESHOLD_ADDR, HWIO_APCS_ALIAS2_CORE_HANG_THRESHOLD_RMSK)
#define HWIO_APCS_ALIAS2_CORE_HANG_THRESHOLD_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS2_CORE_HANG_THRESHOLD_ADDR, m)
#define HWIO_APCS_ALIAS2_CORE_HANG_THRESHOLD_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS2_CORE_HANG_THRESHOLD_ADDR,v)
#define HWIO_APCS_ALIAS2_CORE_HANG_THRESHOLD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS2_CORE_HANG_THRESHOLD_ADDR,m,v,HWIO_APCS_ALIAS2_CORE_HANG_THRESHOLD_IN)
#define HWIO_APCS_ALIAS2_CORE_HANG_THRESHOLD_CORE_HANG_THRESHOLD_VALUE_BMSK                 0xffffffff
#define HWIO_APCS_ALIAS2_CORE_HANG_THRESHOLD_CORE_HANG_THRESHOLD_VALUE_SHFT                        0x0

#define HWIO_APCS_ALIAS2_CORE_HANG_VALUE_ADDR                                               (APCS_ALIAS2_APSS_ACS_REG_BASE      + 0x000000b4)
#define HWIO_APCS_ALIAS2_CORE_HANG_VALUE_RMSK                                               0xffffffff
#define HWIO_APCS_ALIAS2_CORE_HANG_VALUE_IN          \
        in_dword_masked(HWIO_APCS_ALIAS2_CORE_HANG_VALUE_ADDR, HWIO_APCS_ALIAS2_CORE_HANG_VALUE_RMSK)
#define HWIO_APCS_ALIAS2_CORE_HANG_VALUE_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS2_CORE_HANG_VALUE_ADDR, m)
#define HWIO_APCS_ALIAS2_CORE_HANG_VALUE_VALUE_WHEN_HUNG_BMSK                               0xffffffff
#define HWIO_APCS_ALIAS2_CORE_HANG_VALUE_VALUE_WHEN_HUNG_SHFT                                      0x0

#define HWIO_APCS_ALIAS2_CORE_HANG_CONFIG_ADDR                                              (APCS_ALIAS2_APSS_ACS_REG_BASE      + 0x000000b8)
#define HWIO_APCS_ALIAS2_CORE_HANG_CONFIG_RMSK                                                   0x3fb
#define HWIO_APCS_ALIAS2_CORE_HANG_CONFIG_IN          \
        in_dword_masked(HWIO_APCS_ALIAS2_CORE_HANG_CONFIG_ADDR, HWIO_APCS_ALIAS2_CORE_HANG_CONFIG_RMSK)
#define HWIO_APCS_ALIAS2_CORE_HANG_CONFIG_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS2_CORE_HANG_CONFIG_ADDR, m)
#define HWIO_APCS_ALIAS2_CORE_HANG_CONFIG_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS2_CORE_HANG_CONFIG_ADDR,v)
#define HWIO_APCS_ALIAS2_CORE_HANG_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS2_CORE_HANG_CONFIG_ADDR,m,v,HWIO_APCS_ALIAS2_CORE_HANG_CONFIG_IN)
#define HWIO_APCS_ALIAS2_CORE_HANG_CONFIG_PMUEVENT_LEGACY_GOLD_SEL_BMSK                          0x200
#define HWIO_APCS_ALIAS2_CORE_HANG_CONFIG_PMUEVENT_LEGACY_GOLD_SEL_SHFT                            0x9
#define HWIO_APCS_ALIAS2_CORE_HANG_CONFIG_PMUEVENT_SEL_BMSK                                      0x1f0
#define HWIO_APCS_ALIAS2_CORE_HANG_CONFIG_PMUEVENT_SEL_SHFT                                        0x4
#define HWIO_APCS_ALIAS2_CORE_HANG_CONFIG_CORE_HANG_RESET_BMSK                                     0x8
#define HWIO_APCS_ALIAS2_CORE_HANG_CONFIG_CORE_HANG_RESET_SHFT                                     0x3
#define HWIO_APCS_ALIAS2_CORE_HANG_CONFIG_CORE_HANG_COUNTER_EN_BMSK                                0x2
#define HWIO_APCS_ALIAS2_CORE_HANG_CONFIG_CORE_HANG_COUNTER_EN_SHFT                                0x1
#define HWIO_APCS_ALIAS2_CORE_HANG_CONFIG_CORE_HANG_STATUS_BMSK                                    0x1
#define HWIO_APCS_ALIAS2_CORE_HANG_CONFIG_CORE_HANG_STATUS_SHFT                                    0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_ALIAS3_APSS_ACS
 *--------------------------------------------------------------------------*/

#define APCS_ALIAS3_APSS_ACS_REG_BASE                                                       (A53SS_BASE      + 0x001b8000)

#define HWIO_APCS_ALIAS3_CORE_HANG_THRESHOLD_ADDR                                           (APCS_ALIAS3_APSS_ACS_REG_BASE      + 0x000000b0)
#define HWIO_APCS_ALIAS3_CORE_HANG_THRESHOLD_RMSK                                           0xffffffff
#define HWIO_APCS_ALIAS3_CORE_HANG_THRESHOLD_IN          \
        in_dword_masked(HWIO_APCS_ALIAS3_CORE_HANG_THRESHOLD_ADDR, HWIO_APCS_ALIAS3_CORE_HANG_THRESHOLD_RMSK)
#define HWIO_APCS_ALIAS3_CORE_HANG_THRESHOLD_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS3_CORE_HANG_THRESHOLD_ADDR, m)
#define HWIO_APCS_ALIAS3_CORE_HANG_THRESHOLD_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS3_CORE_HANG_THRESHOLD_ADDR,v)
#define HWIO_APCS_ALIAS3_CORE_HANG_THRESHOLD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS3_CORE_HANG_THRESHOLD_ADDR,m,v,HWIO_APCS_ALIAS3_CORE_HANG_THRESHOLD_IN)
#define HWIO_APCS_ALIAS3_CORE_HANG_THRESHOLD_CORE_HANG_THRESHOLD_VALUE_BMSK                 0xffffffff
#define HWIO_APCS_ALIAS3_CORE_HANG_THRESHOLD_CORE_HANG_THRESHOLD_VALUE_SHFT                        0x0

#define HWIO_APCS_ALIAS3_CORE_HANG_VALUE_ADDR                                               (APCS_ALIAS3_APSS_ACS_REG_BASE      + 0x000000b4)
#define HWIO_APCS_ALIAS3_CORE_HANG_VALUE_RMSK                                               0xffffffff
#define HWIO_APCS_ALIAS3_CORE_HANG_VALUE_IN          \
        in_dword_masked(HWIO_APCS_ALIAS3_CORE_HANG_VALUE_ADDR, HWIO_APCS_ALIAS3_CORE_HANG_VALUE_RMSK)
#define HWIO_APCS_ALIAS3_CORE_HANG_VALUE_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS3_CORE_HANG_VALUE_ADDR, m)
#define HWIO_APCS_ALIAS3_CORE_HANG_VALUE_VALUE_WHEN_HUNG_BMSK                               0xffffffff
#define HWIO_APCS_ALIAS3_CORE_HANG_VALUE_VALUE_WHEN_HUNG_SHFT                                      0x0

#define HWIO_APCS_ALIAS3_CORE_HANG_CONFIG_ADDR                                              (APCS_ALIAS3_APSS_ACS_REG_BASE      + 0x000000b8)
#define HWIO_APCS_ALIAS3_CORE_HANG_CONFIG_RMSK                                                   0x3fb
#define HWIO_APCS_ALIAS3_CORE_HANG_CONFIG_IN          \
        in_dword_masked(HWIO_APCS_ALIAS3_CORE_HANG_CONFIG_ADDR, HWIO_APCS_ALIAS3_CORE_HANG_CONFIG_RMSK)
#define HWIO_APCS_ALIAS3_CORE_HANG_CONFIG_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS3_CORE_HANG_CONFIG_ADDR, m)
#define HWIO_APCS_ALIAS3_CORE_HANG_CONFIG_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS3_CORE_HANG_CONFIG_ADDR,v)
#define HWIO_APCS_ALIAS3_CORE_HANG_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS3_CORE_HANG_CONFIG_ADDR,m,v,HWIO_APCS_ALIAS3_CORE_HANG_CONFIG_IN)
#define HWIO_APCS_ALIAS3_CORE_HANG_CONFIG_PMUEVENT_LEGACY_GOLD_SEL_BMSK                          0x200
#define HWIO_APCS_ALIAS3_CORE_HANG_CONFIG_PMUEVENT_LEGACY_GOLD_SEL_SHFT                            0x9
#define HWIO_APCS_ALIAS3_CORE_HANG_CONFIG_PMUEVENT_SEL_BMSK                                      0x1f0
#define HWIO_APCS_ALIAS3_CORE_HANG_CONFIG_PMUEVENT_SEL_SHFT                                        0x4
#define HWIO_APCS_ALIAS3_CORE_HANG_CONFIG_CORE_HANG_RESET_BMSK                                     0x8
#define HWIO_APCS_ALIAS3_CORE_HANG_CONFIG_CORE_HANG_RESET_SHFT                                     0x3
#define HWIO_APCS_ALIAS3_CORE_HANG_CONFIG_CORE_HANG_COUNTER_EN_BMSK                                0x2
#define HWIO_APCS_ALIAS3_CORE_HANG_CONFIG_CORE_HANG_COUNTER_EN_SHFT                                0x1
#define HWIO_APCS_ALIAS3_CORE_HANG_CONFIG_CORE_HANG_STATUS_BMSK                                    0x1
#define HWIO_APCS_ALIAS3_CORE_HANG_CONFIG_CORE_HANG_STATUS_SHFT                                    0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_ALIAS4_APSS_ACS
 *--------------------------------------------------------------------------*/

#define APCS_ALIAS4_APSS_ACS_REG_BASE                                                       (A53SS_BASE      + 0x00088000)

#define HWIO_APCS_ALIAS4_CORE_HANG_THRESHOLD_ADDR                                           (APCS_ALIAS4_APSS_ACS_REG_BASE      + 0x000000b0)
#define HWIO_APCS_ALIAS4_CORE_HANG_THRESHOLD_RMSK                                           0xffffffff
#define HWIO_APCS_ALIAS4_CORE_HANG_THRESHOLD_IN          \
        in_dword_masked(HWIO_APCS_ALIAS4_CORE_HANG_THRESHOLD_ADDR, HWIO_APCS_ALIAS4_CORE_HANG_THRESHOLD_RMSK)
#define HWIO_APCS_ALIAS4_CORE_HANG_THRESHOLD_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS4_CORE_HANG_THRESHOLD_ADDR, m)
#define HWIO_APCS_ALIAS4_CORE_HANG_THRESHOLD_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS4_CORE_HANG_THRESHOLD_ADDR,v)
#define HWIO_APCS_ALIAS4_CORE_HANG_THRESHOLD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS4_CORE_HANG_THRESHOLD_ADDR,m,v,HWIO_APCS_ALIAS4_CORE_HANG_THRESHOLD_IN)
#define HWIO_APCS_ALIAS4_CORE_HANG_THRESHOLD_CORE_HANG_THRESHOLD_VALUE_BMSK                 0xffffffff
#define HWIO_APCS_ALIAS4_CORE_HANG_THRESHOLD_CORE_HANG_THRESHOLD_VALUE_SHFT                        0x0

#define HWIO_APCS_ALIAS4_CORE_HANG_VALUE_ADDR                                               (APCS_ALIAS4_APSS_ACS_REG_BASE      + 0x000000b4)
#define HWIO_APCS_ALIAS4_CORE_HANG_VALUE_RMSK                                               0xffffffff
#define HWIO_APCS_ALIAS4_CORE_HANG_VALUE_IN          \
        in_dword_masked(HWIO_APCS_ALIAS4_CORE_HANG_VALUE_ADDR, HWIO_APCS_ALIAS4_CORE_HANG_VALUE_RMSK)
#define HWIO_APCS_ALIAS4_CORE_HANG_VALUE_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS4_CORE_HANG_VALUE_ADDR, m)
#define HWIO_APCS_ALIAS4_CORE_HANG_VALUE_VALUE_WHEN_HUNG_BMSK                               0xffffffff
#define HWIO_APCS_ALIAS4_CORE_HANG_VALUE_VALUE_WHEN_HUNG_SHFT                                      0x0

#define HWIO_APCS_ALIAS4_CORE_HANG_CONFIG_ADDR                                              (APCS_ALIAS4_APSS_ACS_REG_BASE      + 0x000000b8)
#define HWIO_APCS_ALIAS4_CORE_HANG_CONFIG_RMSK                                                   0x3fb
#define HWIO_APCS_ALIAS4_CORE_HANG_CONFIG_IN          \
        in_dword_masked(HWIO_APCS_ALIAS4_CORE_HANG_CONFIG_ADDR, HWIO_APCS_ALIAS4_CORE_HANG_CONFIG_RMSK)
#define HWIO_APCS_ALIAS4_CORE_HANG_CONFIG_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS4_CORE_HANG_CONFIG_ADDR, m)
#define HWIO_APCS_ALIAS4_CORE_HANG_CONFIG_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS4_CORE_HANG_CONFIG_ADDR,v)
#define HWIO_APCS_ALIAS4_CORE_HANG_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS4_CORE_HANG_CONFIG_ADDR,m,v,HWIO_APCS_ALIAS4_CORE_HANG_CONFIG_IN)
#define HWIO_APCS_ALIAS4_CORE_HANG_CONFIG_PMUEVENT_LEGACY_GOLD_SEL_BMSK                          0x200
#define HWIO_APCS_ALIAS4_CORE_HANG_CONFIG_PMUEVENT_LEGACY_GOLD_SEL_SHFT                            0x9
#define HWIO_APCS_ALIAS4_CORE_HANG_CONFIG_PMUEVENT_SEL_BMSK                                      0x1f0
#define HWIO_APCS_ALIAS4_CORE_HANG_CONFIG_PMUEVENT_SEL_SHFT                                        0x4
#define HWIO_APCS_ALIAS4_CORE_HANG_CONFIG_CORE_HANG_RESET_BMSK                                     0x8
#define HWIO_APCS_ALIAS4_CORE_HANG_CONFIG_CORE_HANG_RESET_SHFT                                     0x3
#define HWIO_APCS_ALIAS4_CORE_HANG_CONFIG_CORE_HANG_COUNTER_EN_BMSK                                0x2
#define HWIO_APCS_ALIAS4_CORE_HANG_CONFIG_CORE_HANG_COUNTER_EN_SHFT                                0x1
#define HWIO_APCS_ALIAS4_CORE_HANG_CONFIG_CORE_HANG_STATUS_BMSK                                    0x1
#define HWIO_APCS_ALIAS4_CORE_HANG_CONFIG_CORE_HANG_STATUS_SHFT                                    0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_ALIAS5_APSS_ACS
 *--------------------------------------------------------------------------*/

#define APCS_ALIAS5_APSS_ACS_REG_BASE                                                       (A53SS_BASE      + 0x00098000)

#define HWIO_APCS_ALIAS5_CORE_HANG_THRESHOLD_ADDR                                           (APCS_ALIAS5_APSS_ACS_REG_BASE      + 0x000000b0)
#define HWIO_APCS_ALIAS5_CORE_HANG_THRESHOLD_RMSK                                           0xffffffff
#define HWIO_APCS_ALIAS5_CORE_HANG_THRESHOLD_IN          \
        in_dword_masked(HWIO_APCS_ALIAS5_CORE_HANG_THRESHOLD_ADDR, HWIO_APCS_ALIAS5_CORE_HANG_THRESHOLD_RMSK)
#define HWIO_APCS_ALIAS5_CORE_HANG_THRESHOLD_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS5_CORE_HANG_THRESHOLD_ADDR, m)
#define HWIO_APCS_ALIAS5_CORE_HANG_THRESHOLD_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS5_CORE_HANG_THRESHOLD_ADDR,v)
#define HWIO_APCS_ALIAS5_CORE_HANG_THRESHOLD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS5_CORE_HANG_THRESHOLD_ADDR,m,v,HWIO_APCS_ALIAS5_CORE_HANG_THRESHOLD_IN)
#define HWIO_APCS_ALIAS5_CORE_HANG_THRESHOLD_CORE_HANG_THRESHOLD_VALUE_BMSK                 0xffffffff
#define HWIO_APCS_ALIAS5_CORE_HANG_THRESHOLD_CORE_HANG_THRESHOLD_VALUE_SHFT                        0x0

#define HWIO_APCS_ALIAS5_CORE_HANG_VALUE_ADDR                                               (APCS_ALIAS5_APSS_ACS_REG_BASE      + 0x000000b4)
#define HWIO_APCS_ALIAS5_CORE_HANG_VALUE_RMSK                                               0xffffffff
#define HWIO_APCS_ALIAS5_CORE_HANG_VALUE_IN          \
        in_dword_masked(HWIO_APCS_ALIAS5_CORE_HANG_VALUE_ADDR, HWIO_APCS_ALIAS5_CORE_HANG_VALUE_RMSK)
#define HWIO_APCS_ALIAS5_CORE_HANG_VALUE_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS5_CORE_HANG_VALUE_ADDR, m)
#define HWIO_APCS_ALIAS5_CORE_HANG_VALUE_VALUE_WHEN_HUNG_BMSK                               0xffffffff
#define HWIO_APCS_ALIAS5_CORE_HANG_VALUE_VALUE_WHEN_HUNG_SHFT                                      0x0

#define HWIO_APCS_ALIAS5_CORE_HANG_CONFIG_ADDR                                              (APCS_ALIAS5_APSS_ACS_REG_BASE      + 0x000000b8)
#define HWIO_APCS_ALIAS5_CORE_HANG_CONFIG_RMSK                                                   0x3fb
#define HWIO_APCS_ALIAS5_CORE_HANG_CONFIG_IN          \
        in_dword_masked(HWIO_APCS_ALIAS5_CORE_HANG_CONFIG_ADDR, HWIO_APCS_ALIAS5_CORE_HANG_CONFIG_RMSK)
#define HWIO_APCS_ALIAS5_CORE_HANG_CONFIG_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS5_CORE_HANG_CONFIG_ADDR, m)
#define HWIO_APCS_ALIAS5_CORE_HANG_CONFIG_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS5_CORE_HANG_CONFIG_ADDR,v)
#define HWIO_APCS_ALIAS5_CORE_HANG_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS5_CORE_HANG_CONFIG_ADDR,m,v,HWIO_APCS_ALIAS5_CORE_HANG_CONFIG_IN)
#define HWIO_APCS_ALIAS5_CORE_HANG_CONFIG_PMUEVENT_LEGACY_GOLD_SEL_BMSK                          0x200
#define HWIO_APCS_ALIAS5_CORE_HANG_CONFIG_PMUEVENT_LEGACY_GOLD_SEL_SHFT                            0x9
#define HWIO_APCS_ALIAS5_CORE_HANG_CONFIG_PMUEVENT_SEL_BMSK                                      0x1f0
#define HWIO_APCS_ALIAS5_CORE_HANG_CONFIG_PMUEVENT_SEL_SHFT                                        0x4
#define HWIO_APCS_ALIAS5_CORE_HANG_CONFIG_CORE_HANG_RESET_BMSK                                     0x8
#define HWIO_APCS_ALIAS5_CORE_HANG_CONFIG_CORE_HANG_RESET_SHFT                                     0x3
#define HWIO_APCS_ALIAS5_CORE_HANG_CONFIG_CORE_HANG_COUNTER_EN_BMSK                                0x2
#define HWIO_APCS_ALIAS5_CORE_HANG_CONFIG_CORE_HANG_COUNTER_EN_SHFT                                0x1
#define HWIO_APCS_ALIAS5_CORE_HANG_CONFIG_CORE_HANG_STATUS_BMSK                                    0x1
#define HWIO_APCS_ALIAS5_CORE_HANG_CONFIG_CORE_HANG_STATUS_SHFT                                    0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_ALIAS6_APSS_ACS
 *--------------------------------------------------------------------------*/

#define APCS_ALIAS6_APSS_ACS_REG_BASE                                                       (A53SS_BASE      + 0x000a8000)

#define HWIO_APCS_ALIAS6_CORE_HANG_THRESHOLD_ADDR                                           (APCS_ALIAS6_APSS_ACS_REG_BASE      + 0x000000b0)
#define HWIO_APCS_ALIAS6_CORE_HANG_THRESHOLD_RMSK                                           0xffffffff
#define HWIO_APCS_ALIAS6_CORE_HANG_THRESHOLD_IN          \
        in_dword_masked(HWIO_APCS_ALIAS6_CORE_HANG_THRESHOLD_ADDR, HWIO_APCS_ALIAS6_CORE_HANG_THRESHOLD_RMSK)
#define HWIO_APCS_ALIAS6_CORE_HANG_THRESHOLD_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS6_CORE_HANG_THRESHOLD_ADDR, m)
#define HWIO_APCS_ALIAS6_CORE_HANG_THRESHOLD_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS6_CORE_HANG_THRESHOLD_ADDR,v)
#define HWIO_APCS_ALIAS6_CORE_HANG_THRESHOLD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS6_CORE_HANG_THRESHOLD_ADDR,m,v,HWIO_APCS_ALIAS6_CORE_HANG_THRESHOLD_IN)
#define HWIO_APCS_ALIAS6_CORE_HANG_THRESHOLD_CORE_HANG_THRESHOLD_VALUE_BMSK                 0xffffffff
#define HWIO_APCS_ALIAS6_CORE_HANG_THRESHOLD_CORE_HANG_THRESHOLD_VALUE_SHFT                        0x0

#define HWIO_APCS_ALIAS6_CORE_HANG_VALUE_ADDR                                               (APCS_ALIAS6_APSS_ACS_REG_BASE      + 0x000000b4)
#define HWIO_APCS_ALIAS6_CORE_HANG_VALUE_RMSK                                               0xffffffff
#define HWIO_APCS_ALIAS6_CORE_HANG_VALUE_IN          \
        in_dword_masked(HWIO_APCS_ALIAS6_CORE_HANG_VALUE_ADDR, HWIO_APCS_ALIAS6_CORE_HANG_VALUE_RMSK)
#define HWIO_APCS_ALIAS6_CORE_HANG_VALUE_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS6_CORE_HANG_VALUE_ADDR, m)
#define HWIO_APCS_ALIAS6_CORE_HANG_VALUE_VALUE_WHEN_HUNG_BMSK                               0xffffffff
#define HWIO_APCS_ALIAS6_CORE_HANG_VALUE_VALUE_WHEN_HUNG_SHFT                                      0x0

#define HWIO_APCS_ALIAS6_CORE_HANG_CONFIG_ADDR                                              (APCS_ALIAS6_APSS_ACS_REG_BASE      + 0x000000b8)
#define HWIO_APCS_ALIAS6_CORE_HANG_CONFIG_RMSK                                                   0x3fb
#define HWIO_APCS_ALIAS6_CORE_HANG_CONFIG_IN          \
        in_dword_masked(HWIO_APCS_ALIAS6_CORE_HANG_CONFIG_ADDR, HWIO_APCS_ALIAS6_CORE_HANG_CONFIG_RMSK)
#define HWIO_APCS_ALIAS6_CORE_HANG_CONFIG_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS6_CORE_HANG_CONFIG_ADDR, m)
#define HWIO_APCS_ALIAS6_CORE_HANG_CONFIG_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS6_CORE_HANG_CONFIG_ADDR,v)
#define HWIO_APCS_ALIAS6_CORE_HANG_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS6_CORE_HANG_CONFIG_ADDR,m,v,HWIO_APCS_ALIAS6_CORE_HANG_CONFIG_IN)
#define HWIO_APCS_ALIAS6_CORE_HANG_CONFIG_PMUEVENT_LEGACY_GOLD_SEL_BMSK                          0x200
#define HWIO_APCS_ALIAS6_CORE_HANG_CONFIG_PMUEVENT_LEGACY_GOLD_SEL_SHFT                            0x9
#define HWIO_APCS_ALIAS6_CORE_HANG_CONFIG_PMUEVENT_SEL_BMSK                                      0x1f0
#define HWIO_APCS_ALIAS6_CORE_HANG_CONFIG_PMUEVENT_SEL_SHFT                                        0x4
#define HWIO_APCS_ALIAS6_CORE_HANG_CONFIG_CORE_HANG_RESET_BMSK                                     0x8
#define HWIO_APCS_ALIAS6_CORE_HANG_CONFIG_CORE_HANG_RESET_SHFT                                     0x3
#define HWIO_APCS_ALIAS6_CORE_HANG_CONFIG_CORE_HANG_COUNTER_EN_BMSK                                0x2
#define HWIO_APCS_ALIAS6_CORE_HANG_CONFIG_CORE_HANG_COUNTER_EN_SHFT                                0x1
#define HWIO_APCS_ALIAS6_CORE_HANG_CONFIG_CORE_HANG_STATUS_BMSK                                    0x1
#define HWIO_APCS_ALIAS6_CORE_HANG_CONFIG_CORE_HANG_STATUS_SHFT                                    0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_ALIAS7_APSS_ACS
 *--------------------------------------------------------------------------*/

#define APCS_ALIAS7_APSS_ACS_REG_BASE                                                       (A53SS_BASE      + 0x000b8000)

#define HWIO_APCS_ALIAS7_CORE_HANG_THRESHOLD_ADDR                                           (APCS_ALIAS7_APSS_ACS_REG_BASE      + 0x000000b0)
#define HWIO_APCS_ALIAS7_CORE_HANG_THRESHOLD_RMSK                                           0xffffffff
#define HWIO_APCS_ALIAS7_CORE_HANG_THRESHOLD_IN          \
        in_dword_masked(HWIO_APCS_ALIAS7_CORE_HANG_THRESHOLD_ADDR, HWIO_APCS_ALIAS7_CORE_HANG_THRESHOLD_RMSK)
#define HWIO_APCS_ALIAS7_CORE_HANG_THRESHOLD_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS7_CORE_HANG_THRESHOLD_ADDR, m)
#define HWIO_APCS_ALIAS7_CORE_HANG_THRESHOLD_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS7_CORE_HANG_THRESHOLD_ADDR,v)
#define HWIO_APCS_ALIAS7_CORE_HANG_THRESHOLD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS7_CORE_HANG_THRESHOLD_ADDR,m,v,HWIO_APCS_ALIAS7_CORE_HANG_THRESHOLD_IN)
#define HWIO_APCS_ALIAS7_CORE_HANG_THRESHOLD_CORE_HANG_THRESHOLD_VALUE_BMSK                 0xffffffff
#define HWIO_APCS_ALIAS7_CORE_HANG_THRESHOLD_CORE_HANG_THRESHOLD_VALUE_SHFT                        0x0

#define HWIO_APCS_ALIAS7_CORE_HANG_VALUE_ADDR                                               (APCS_ALIAS7_APSS_ACS_REG_BASE      + 0x000000b4)
#define HWIO_APCS_ALIAS7_CORE_HANG_VALUE_RMSK                                               0xffffffff
#define HWIO_APCS_ALIAS7_CORE_HANG_VALUE_IN          \
        in_dword_masked(HWIO_APCS_ALIAS7_CORE_HANG_VALUE_ADDR, HWIO_APCS_ALIAS7_CORE_HANG_VALUE_RMSK)
#define HWIO_APCS_ALIAS7_CORE_HANG_VALUE_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS7_CORE_HANG_VALUE_ADDR, m)
#define HWIO_APCS_ALIAS7_CORE_HANG_VALUE_VALUE_WHEN_HUNG_BMSK                               0xffffffff
#define HWIO_APCS_ALIAS7_CORE_HANG_VALUE_VALUE_WHEN_HUNG_SHFT                                      0x0

#define HWIO_APCS_ALIAS7_CORE_HANG_CONFIG_ADDR                                              (APCS_ALIAS7_APSS_ACS_REG_BASE      + 0x000000b8)
#define HWIO_APCS_ALIAS7_CORE_HANG_CONFIG_RMSK                                                   0x3fb
#define HWIO_APCS_ALIAS7_CORE_HANG_CONFIG_IN          \
        in_dword_masked(HWIO_APCS_ALIAS7_CORE_HANG_CONFIG_ADDR, HWIO_APCS_ALIAS7_CORE_HANG_CONFIG_RMSK)
#define HWIO_APCS_ALIAS7_CORE_HANG_CONFIG_INM(m)      \
        in_dword_masked(HWIO_APCS_ALIAS7_CORE_HANG_CONFIG_ADDR, m)
#define HWIO_APCS_ALIAS7_CORE_HANG_CONFIG_OUT(v)      \
        out_dword(HWIO_APCS_ALIAS7_CORE_HANG_CONFIG_ADDR,v)
#define HWIO_APCS_ALIAS7_CORE_HANG_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APCS_ALIAS7_CORE_HANG_CONFIG_ADDR,m,v,HWIO_APCS_ALIAS7_CORE_HANG_CONFIG_IN)
#define HWIO_APCS_ALIAS7_CORE_HANG_CONFIG_PMUEVENT_LEGACY_GOLD_SEL_BMSK                          0x200
#define HWIO_APCS_ALIAS7_CORE_HANG_CONFIG_PMUEVENT_LEGACY_GOLD_SEL_SHFT                            0x9
#define HWIO_APCS_ALIAS7_CORE_HANG_CONFIG_PMUEVENT_SEL_BMSK                                      0x1f0
#define HWIO_APCS_ALIAS7_CORE_HANG_CONFIG_PMUEVENT_SEL_SHFT                                        0x4
#define HWIO_APCS_ALIAS7_CORE_HANG_CONFIG_CORE_HANG_RESET_BMSK                                     0x8
#define HWIO_APCS_ALIAS7_CORE_HANG_CONFIG_CORE_HANG_RESET_SHFT                                     0x3
#define HWIO_APCS_ALIAS7_CORE_HANG_CONFIG_CORE_HANG_COUNTER_EN_BMSK                                0x2
#define HWIO_APCS_ALIAS7_CORE_HANG_CONFIG_CORE_HANG_COUNTER_EN_SHFT                                0x1
#define HWIO_APCS_ALIAS7_CORE_HANG_CONFIG_CORE_HANG_STATUS_BMSK                                    0x1
#define HWIO_APCS_ALIAS7_CORE_HANG_CONFIG_CORE_HANG_STATUS_SHFT                                    0x0


#endif /* __APCS_HANG_STATUS_HWIO_H__ */
