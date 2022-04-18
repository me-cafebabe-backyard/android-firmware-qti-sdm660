#ifndef __ICBCFG_HWIO_H__
#define __ICBCFG_HWIO_H__
/*
===========================================================================
*/
/**
  @file icbcfg_hwio.h
  @brief Auto-generated HWIO interface include file.
  Manually replaced BIMC_GLOBAL0_REG_BASE with BIMC_BASE
  This file contains HWIO register definitions for the following modules:
    BIMC_GLOBAL0
    BIMC_GLOBAL2
    GCC_CLK_CTL_REG
    LPASS_CC
    QM
    OCIMEM_CSR
    LPASS_TCSR
    MMSS_CC
    LPASS_QOS_GASKET_QOS_GASKET_THROTTLE

  'Include' filters applied: .*CLK_PERIOD*[BIMC_GLOBAL0] .*REDIRECT_CTRL*[BIMC_GLOBAL2] .*REDIRECT_MSTR_EN*[BIMC_GLOBAL2] .*LPASS_AUDIO_WRAPPER_QOS_XO*[LPASS_CC] .*LPASS_AUDIO_WRAPPER_QOS_AHBS*[LPASS_CC] .*OCIMEM_GEN_CTL*[OCIMEM_CSR] .*QM_CORE*[GCC_CLK_CTL_REG] .*QM_*[GCC_CLK_CTL_REG] .*GCC_LPASS_SWAY_CBCR*[GCC_CLK_CTL_REG] .*GCC_LPASS_Q6_AXI*[GCC_CLK_CTL_REG] .*MMSS_NOC_CFG_AHB*[GCC_CLK_CTL_REG] .*LPASS_Q6_SMMU_AHB*[GCC_CLK_CTL_REG] .*LPASS_CNOC_CFG*[GCC_CLK_CTL_REG] .*VIDEO_TOP_GDSCR*[MMSS_CC] .*MMSS_THROTTLE_VIDEO*[MMSS_CC] .*MMSS_MDSS_GDSCR*[MMSS_CC] .*MMSS_THROTTLE_MDSS*[MMSS_CC] .*MMSS_CAMSS_TOP_GDSCR*[MMSS_CC] .*MMSS_THROTTLE_CAMSS*[MMSS_CC] .*LPASS_TCSR_QOS*[LPASS_TCSR] 
  'Exclude' filters applied: .*_END$ .*_END_ADDRESS$ .*_SIZE$ EBI1_MEM_RPM_REGION. .*DDR_CHn_CLK_PERIOD*[BIMC_GLOBAL0] QM_CLNT_0_\w+_CNTRL[QM] QM_CLNT_1_\w+_CNTRL[QM] QM_CLNT_2_\w+_CNTRL[QM] QM_CLNT_3_\w+_CNTRL[QM] QM_CLNT_4_\w+_CNTRL[QM] QM_CLNT_5_\w+_CNTRL[QM] QM_CLNT_6_\w+_CNTRL[QM] QM_CLNT_7_\w+_CNTRL[QM] QM_CLNT_8_\w+_CNTRL[QM] QM_CLNT_9_\w+_CNTRL[QM] QM_CLNT_0_THROTTLE_LEVEL_QOS_n[QM] QM_CLNT_1_THROTTLE_LEVEL_QOS_n[QM] QM_CLNT_2_THROTTLE_LEVEL_QOS_n[QM] QM_CLNT_3_THROTTLE_LEVEL_QOS_n[QM] QM_CLNT_4_THROTTLE_LEVEL_QOS_n[QM] QM_CLNT_5_THROTTLE_LEVEL_QOS_n[QM] QM_CLNT_6_THROTTLE_LEVEL_QOS_n[QM] QM_CLNT_7_THROTTLE_LEVEL_QOS_n[QM] QM_CLNT_8_THROTTLE_LEVEL_QOS_n[QM] QM_CLNT_9_THROTTLE_LEVEL_QOS_n[QM] QM_CLNT_10_THROTTLE_LEVEL_QOS_n[QM] QM_CLNT_0_THROTTLE_LEVEL_MUX_CFG[QM] QM_CLNT_1_THROTTLE_LEVEL_MUX_CFG[QM] QM_CLNT_2_THROTTLE_LEVEL_MUX_CFG[QM] QM_CLNT_3_THROTTLE_LEVEL_MUX_CFG[QM] QM_CLNT_4_THROTTLE_LEVEL_MUX_CFG[QM] QM_CLNT_5_THROTTLE_LEVEL_MUX_CFG[QM] QM_CLNT_6_THROTTLE_LEVEL_MUX_CFG[QM] QM_CLNT_7_THROTTLE_LEVEL_MUX_CFG[QM] QM_CLNT_8_THROTTLE_LEVEL_MUX_CFG[QM] QM_CLNT_9_THROTTLE_LEVEL_MUX_CFG[QM] QM_CLNT_10_THROTTLE_LEVEL_MUX_CFG[QM] 
*/
/*
  ===========================================================================

  Copyright (c) 2017 Qualcomm Technologies Incorporated.
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

  $Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Settings/ICB/loader/icbcfg_hwio.h#4 $
  $DateTime: 2017/02/07 01:34:08 $
  $Author: pwbldsvc $

  ===========================================================================
*/


#include "../../../Include/msmhwiobase.h"


/*----------------------------------------------------------------------------
 * MODULE: GCC_CLK_CTL_REG
 *--------------------------------------------------------------------------*/

#define GCC_CLK_CTL_REG_REG_BASE                                                                  (CLK_CTL_BASE      + 0x00000000)

#define HWIO_GCC_MMSS_NOC_CFG_AHB_CBCR_ADDR                                                       (GCC_CLK_CTL_REG_REG_BASE      + 0x00009004)
#define HWIO_GCC_MMSS_NOC_CFG_AHB_CBCR_RMSK                                                       0xf0008005
#define HWIO_GCC_MMSS_NOC_CFG_AHB_CBCR_IN          \
        in_dword_masked(HWIO_GCC_MMSS_NOC_CFG_AHB_CBCR_ADDR, HWIO_GCC_MMSS_NOC_CFG_AHB_CBCR_RMSK)
#define HWIO_GCC_MMSS_NOC_CFG_AHB_CBCR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMSS_NOC_CFG_AHB_CBCR_ADDR, m)
#define HWIO_GCC_MMSS_NOC_CFG_AHB_CBCR_OUT(v)      \
        out_dword(HWIO_GCC_MMSS_NOC_CFG_AHB_CBCR_ADDR,v)
#define HWIO_GCC_MMSS_NOC_CFG_AHB_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMSS_NOC_CFG_AHB_CBCR_ADDR,m,v,HWIO_GCC_MMSS_NOC_CFG_AHB_CBCR_IN)
#define HWIO_GCC_MMSS_NOC_CFG_AHB_CBCR_CLK_OFF_BMSK                                               0x80000000
#define HWIO_GCC_MMSS_NOC_CFG_AHB_CBCR_CLK_OFF_SHFT                                                     0x1f
#define HWIO_GCC_MMSS_NOC_CFG_AHB_CBCR_NOC_HANDSHAKE_FSM_STATUS_BMSK                              0x70000000
#define HWIO_GCC_MMSS_NOC_CFG_AHB_CBCR_NOC_HANDSHAKE_FSM_STATUS_SHFT                                    0x1c
#define HWIO_GCC_MMSS_NOC_CFG_AHB_CBCR_NOC_HANDSHAKE_FSM_EN_BMSK                                      0x8000
#define HWIO_GCC_MMSS_NOC_CFG_AHB_CBCR_NOC_HANDSHAKE_FSM_EN_SHFT                                         0xf
#define HWIO_GCC_MMSS_NOC_CFG_AHB_CBCR_CLK_ARES_BMSK                                                     0x4
#define HWIO_GCC_MMSS_NOC_CFG_AHB_CBCR_CLK_ARES_SHFT                                                     0x2
#define HWIO_GCC_MMSS_NOC_CFG_AHB_CBCR_CLK_ENABLE_BMSK                                                   0x1
#define HWIO_GCC_MMSS_NOC_CFG_AHB_CBCR_CLK_ENABLE_SHFT                                                   0x0

#define HWIO_GCC_MMSS_QM_CORE_CBCR_ADDR                                                           (GCC_CLK_CTL_REG_REG_BASE      + 0x0000900c)
#define HWIO_GCC_MMSS_QM_CORE_CBCR_RMSK                                                           0x80000005
#define HWIO_GCC_MMSS_QM_CORE_CBCR_IN          \
        in_dword_masked(HWIO_GCC_MMSS_QM_CORE_CBCR_ADDR, HWIO_GCC_MMSS_QM_CORE_CBCR_RMSK)
#define HWIO_GCC_MMSS_QM_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMSS_QM_CORE_CBCR_ADDR, m)
#define HWIO_GCC_MMSS_QM_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_GCC_MMSS_QM_CORE_CBCR_ADDR,v)
#define HWIO_GCC_MMSS_QM_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMSS_QM_CORE_CBCR_ADDR,m,v,HWIO_GCC_MMSS_QM_CORE_CBCR_IN)
#define HWIO_GCC_MMSS_QM_CORE_CBCR_CLK_OFF_BMSK                                                   0x80000000
#define HWIO_GCC_MMSS_QM_CORE_CBCR_CLK_OFF_SHFT                                                         0x1f
#define HWIO_GCC_MMSS_QM_CORE_CBCR_CLK_ARES_BMSK                                                         0x4
#define HWIO_GCC_MMSS_QM_CORE_CBCR_CLK_ARES_SHFT                                                         0x2
#define HWIO_GCC_MMSS_QM_CORE_CBCR_CLK_ENABLE_BMSK                                                       0x1
#define HWIO_GCC_MMSS_QM_CORE_CBCR_CLK_ENABLE_SHFT                                                       0x0

#define HWIO_GCC_MMSS_QM_CORE_CMD_RCGR_ADDR                                                       (GCC_CLK_CTL_REG_REG_BASE      + 0x00009014)
#define HWIO_GCC_MMSS_QM_CORE_CMD_RCGR_RMSK                                                       0x80000013
#define HWIO_GCC_MMSS_QM_CORE_CMD_RCGR_IN          \
        in_dword_masked(HWIO_GCC_MMSS_QM_CORE_CMD_RCGR_ADDR, HWIO_GCC_MMSS_QM_CORE_CMD_RCGR_RMSK)
#define HWIO_GCC_MMSS_QM_CORE_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMSS_QM_CORE_CMD_RCGR_ADDR, m)
#define HWIO_GCC_MMSS_QM_CORE_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_GCC_MMSS_QM_CORE_CMD_RCGR_ADDR,v)
#define HWIO_GCC_MMSS_QM_CORE_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMSS_QM_CORE_CMD_RCGR_ADDR,m,v,HWIO_GCC_MMSS_QM_CORE_CMD_RCGR_IN)
#define HWIO_GCC_MMSS_QM_CORE_CMD_RCGR_ROOT_OFF_BMSK                                              0x80000000
#define HWIO_GCC_MMSS_QM_CORE_CMD_RCGR_ROOT_OFF_SHFT                                                    0x1f
#define HWIO_GCC_MMSS_QM_CORE_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                              0x10
#define HWIO_GCC_MMSS_QM_CORE_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                               0x4
#define HWIO_GCC_MMSS_QM_CORE_CMD_RCGR_ROOT_EN_BMSK                                                      0x2
#define HWIO_GCC_MMSS_QM_CORE_CMD_RCGR_ROOT_EN_SHFT                                                      0x1
#define HWIO_GCC_MMSS_QM_CORE_CMD_RCGR_UPDATE_BMSK                                                       0x1
#define HWIO_GCC_MMSS_QM_CORE_CMD_RCGR_UPDATE_SHFT                                                       0x0

#define HWIO_GCC_MMSS_QM_CORE_CFG_RCGR_ADDR                                                       (GCC_CLK_CTL_REG_REG_BASE      + 0x00009018)
#define HWIO_GCC_MMSS_QM_CORE_CFG_RCGR_RMSK                                                            0x71f
#define HWIO_GCC_MMSS_QM_CORE_CFG_RCGR_IN          \
        in_dword_masked(HWIO_GCC_MMSS_QM_CORE_CFG_RCGR_ADDR, HWIO_GCC_MMSS_QM_CORE_CFG_RCGR_RMSK)
#define HWIO_GCC_MMSS_QM_CORE_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMSS_QM_CORE_CFG_RCGR_ADDR, m)
#define HWIO_GCC_MMSS_QM_CORE_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_GCC_MMSS_QM_CORE_CFG_RCGR_ADDR,v)
#define HWIO_GCC_MMSS_QM_CORE_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMSS_QM_CORE_CFG_RCGR_ADDR,m,v,HWIO_GCC_MMSS_QM_CORE_CFG_RCGR_IN)
#define HWIO_GCC_MMSS_QM_CORE_CFG_RCGR_SRC_SEL_BMSK                                                    0x700
#define HWIO_GCC_MMSS_QM_CORE_CFG_RCGR_SRC_SEL_SHFT                                                      0x8
#define HWIO_GCC_MMSS_QM_CORE_CFG_RCGR_SRC_DIV_BMSK                                                     0x1f
#define HWIO_GCC_MMSS_QM_CORE_CFG_RCGR_SRC_DIV_SHFT                                                      0x0

#define HWIO_GCC_MMSS_QM_AHB_CBCR_ADDR                                                            (GCC_CLK_CTL_REG_REG_BASE      + 0x00009030)
#define HWIO_GCC_MMSS_QM_AHB_CBCR_RMSK                                                            0xf0008005
#define HWIO_GCC_MMSS_QM_AHB_CBCR_IN          \
        in_dword_masked(HWIO_GCC_MMSS_QM_AHB_CBCR_ADDR, HWIO_GCC_MMSS_QM_AHB_CBCR_RMSK)
#define HWIO_GCC_MMSS_QM_AHB_CBCR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMSS_QM_AHB_CBCR_ADDR, m)
#define HWIO_GCC_MMSS_QM_AHB_CBCR_OUT(v)      \
        out_dword(HWIO_GCC_MMSS_QM_AHB_CBCR_ADDR,v)
#define HWIO_GCC_MMSS_QM_AHB_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMSS_QM_AHB_CBCR_ADDR,m,v,HWIO_GCC_MMSS_QM_AHB_CBCR_IN)
#define HWIO_GCC_MMSS_QM_AHB_CBCR_CLK_OFF_BMSK                                                    0x80000000
#define HWIO_GCC_MMSS_QM_AHB_CBCR_CLK_OFF_SHFT                                                          0x1f
#define HWIO_GCC_MMSS_QM_AHB_CBCR_NOC_HANDSHAKE_FSM_STATUS_BMSK                                   0x70000000
#define HWIO_GCC_MMSS_QM_AHB_CBCR_NOC_HANDSHAKE_FSM_STATUS_SHFT                                         0x1c
#define HWIO_GCC_MMSS_QM_AHB_CBCR_NOC_HANDSHAKE_FSM_EN_BMSK                                           0x8000
#define HWIO_GCC_MMSS_QM_AHB_CBCR_NOC_HANDSHAKE_FSM_EN_SHFT                                              0xf
#define HWIO_GCC_MMSS_QM_AHB_CBCR_CLK_ARES_BMSK                                                          0x4
#define HWIO_GCC_MMSS_QM_AHB_CBCR_CLK_ARES_SHFT                                                          0x2
#define HWIO_GCC_MMSS_QM_AHB_CBCR_CLK_ENABLE_BMSK                                                        0x1
#define HWIO_GCC_MMSS_QM_AHB_CBCR_CLK_ENABLE_SHFT                                                        0x0

#define HWIO_GCC_LPASS_Q6_AXI_CBCR_ADDR                                                           (GCC_CLK_CTL_REG_REG_BASE      + 0x00047000)
#define HWIO_GCC_LPASS_Q6_AXI_CBCR_RMSK                                                           0x80000005
#define HWIO_GCC_LPASS_Q6_AXI_CBCR_IN          \
        in_dword_masked(HWIO_GCC_LPASS_Q6_AXI_CBCR_ADDR, HWIO_GCC_LPASS_Q6_AXI_CBCR_RMSK)
#define HWIO_GCC_LPASS_Q6_AXI_CBCR_INM(m)      \
        in_dword_masked(HWIO_GCC_LPASS_Q6_AXI_CBCR_ADDR, m)
#define HWIO_GCC_LPASS_Q6_AXI_CBCR_OUT(v)      \
        out_dword(HWIO_GCC_LPASS_Q6_AXI_CBCR_ADDR,v)
#define HWIO_GCC_LPASS_Q6_AXI_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_LPASS_Q6_AXI_CBCR_ADDR,m,v,HWIO_GCC_LPASS_Q6_AXI_CBCR_IN)
#define HWIO_GCC_LPASS_Q6_AXI_CBCR_CLK_OFF_BMSK                                                   0x80000000
#define HWIO_GCC_LPASS_Q6_AXI_CBCR_CLK_OFF_SHFT                                                         0x1f
#define HWIO_GCC_LPASS_Q6_AXI_CBCR_CLK_ARES_BMSK                                                         0x4
#define HWIO_GCC_LPASS_Q6_AXI_CBCR_CLK_ARES_SHFT                                                         0x2
#define HWIO_GCC_LPASS_Q6_AXI_CBCR_CLK_ENABLE_BMSK                                                       0x1
#define HWIO_GCC_LPASS_Q6_AXI_CBCR_CLK_ENABLE_SHFT                                                       0x0

#define HWIO_GCC_LPASS_SWAY_CBCR_ADDR                                                             (GCC_CLK_CTL_REG_REG_BASE      + 0x0004700c)
#define HWIO_GCC_LPASS_SWAY_CBCR_RMSK                                                             0xf0008007
#define HWIO_GCC_LPASS_SWAY_CBCR_IN          \
        in_dword_masked(HWIO_GCC_LPASS_SWAY_CBCR_ADDR, HWIO_GCC_LPASS_SWAY_CBCR_RMSK)
#define HWIO_GCC_LPASS_SWAY_CBCR_INM(m)      \
        in_dword_masked(HWIO_GCC_LPASS_SWAY_CBCR_ADDR, m)
#define HWIO_GCC_LPASS_SWAY_CBCR_OUT(v)      \
        out_dword(HWIO_GCC_LPASS_SWAY_CBCR_ADDR,v)
#define HWIO_GCC_LPASS_SWAY_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_LPASS_SWAY_CBCR_ADDR,m,v,HWIO_GCC_LPASS_SWAY_CBCR_IN)
#define HWIO_GCC_LPASS_SWAY_CBCR_CLK_OFF_BMSK                                                     0x80000000
#define HWIO_GCC_LPASS_SWAY_CBCR_CLK_OFF_SHFT                                                           0x1f
#define HWIO_GCC_LPASS_SWAY_CBCR_NOC_HANDSHAKE_FSM_STATUS_BMSK                                    0x70000000
#define HWIO_GCC_LPASS_SWAY_CBCR_NOC_HANDSHAKE_FSM_STATUS_SHFT                                          0x1c
#define HWIO_GCC_LPASS_SWAY_CBCR_NOC_HANDSHAKE_FSM_EN_BMSK                                            0x8000
#define HWIO_GCC_LPASS_SWAY_CBCR_NOC_HANDSHAKE_FSM_EN_SHFT                                               0xf
#define HWIO_GCC_LPASS_SWAY_CBCR_CLK_ARES_BMSK                                                           0x4
#define HWIO_GCC_LPASS_SWAY_CBCR_CLK_ARES_SHFT                                                           0x2
#define HWIO_GCC_LPASS_SWAY_CBCR_HW_CTL_BMSK                                                             0x2
#define HWIO_GCC_LPASS_SWAY_CBCR_HW_CTL_SHFT                                                             0x1
#define HWIO_GCC_LPASS_SWAY_CBCR_CLK_ENABLE_BMSK                                                         0x1
#define HWIO_GCC_LPASS_SWAY_CBCR_CLK_ENABLE_SHFT                                                         0x0

#define HWIO_GCC_LPASS_Q6_SMMU_AHB_CBCR_ADDR                                                      (GCC_CLK_CTL_REG_REG_BASE      + 0x00047010)
#define HWIO_GCC_LPASS_Q6_SMMU_AHB_CBCR_RMSK                                                      0xf0008005
#define HWIO_GCC_LPASS_Q6_SMMU_AHB_CBCR_IN          \
        in_dword_masked(HWIO_GCC_LPASS_Q6_SMMU_AHB_CBCR_ADDR, HWIO_GCC_LPASS_Q6_SMMU_AHB_CBCR_RMSK)
#define HWIO_GCC_LPASS_Q6_SMMU_AHB_CBCR_INM(m)      \
        in_dword_masked(HWIO_GCC_LPASS_Q6_SMMU_AHB_CBCR_ADDR, m)
#define HWIO_GCC_LPASS_Q6_SMMU_AHB_CBCR_OUT(v)      \
        out_dword(HWIO_GCC_LPASS_Q6_SMMU_AHB_CBCR_ADDR,v)
#define HWIO_GCC_LPASS_Q6_SMMU_AHB_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_LPASS_Q6_SMMU_AHB_CBCR_ADDR,m,v,HWIO_GCC_LPASS_Q6_SMMU_AHB_CBCR_IN)
#define HWIO_GCC_LPASS_Q6_SMMU_AHB_CBCR_CLK_OFF_BMSK                                              0x80000000
#define HWIO_GCC_LPASS_Q6_SMMU_AHB_CBCR_CLK_OFF_SHFT                                                    0x1f
#define HWIO_GCC_LPASS_Q6_SMMU_AHB_CBCR_NOC_HANDSHAKE_FSM_STATUS_BMSK                             0x70000000
#define HWIO_GCC_LPASS_Q6_SMMU_AHB_CBCR_NOC_HANDSHAKE_FSM_STATUS_SHFT                                   0x1c
#define HWIO_GCC_LPASS_Q6_SMMU_AHB_CBCR_NOC_HANDSHAKE_FSM_EN_BMSK                                     0x8000
#define HWIO_GCC_LPASS_Q6_SMMU_AHB_CBCR_NOC_HANDSHAKE_FSM_EN_SHFT                                        0xf
#define HWIO_GCC_LPASS_Q6_SMMU_AHB_CBCR_CLK_ARES_BMSK                                                    0x4
#define HWIO_GCC_LPASS_Q6_SMMU_AHB_CBCR_CLK_ARES_SHFT                                                    0x2
#define HWIO_GCC_LPASS_Q6_SMMU_AHB_CBCR_CLK_ENABLE_BMSK                                                  0x1
#define HWIO_GCC_LPASS_Q6_SMMU_AHB_CBCR_CLK_ENABLE_SHFT                                                  0x0

#define HWIO_GCC_LPASS_CNOC_CFG_CBCR_ADDR                                                         (GCC_CLK_CTL_REG_REG_BASE      + 0x00047038)
#define HWIO_GCC_LPASS_CNOC_CFG_CBCR_RMSK                                                         0x80000005
#define HWIO_GCC_LPASS_CNOC_CFG_CBCR_IN          \
        in_dword_masked(HWIO_GCC_LPASS_CNOC_CFG_CBCR_ADDR, HWIO_GCC_LPASS_CNOC_CFG_CBCR_RMSK)
#define HWIO_GCC_LPASS_CNOC_CFG_CBCR_INM(m)      \
        in_dword_masked(HWIO_GCC_LPASS_CNOC_CFG_CBCR_ADDR, m)
#define HWIO_GCC_LPASS_CNOC_CFG_CBCR_OUT(v)      \
        out_dword(HWIO_GCC_LPASS_CNOC_CFG_CBCR_ADDR,v)
#define HWIO_GCC_LPASS_CNOC_CFG_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_LPASS_CNOC_CFG_CBCR_ADDR,m,v,HWIO_GCC_LPASS_CNOC_CFG_CBCR_IN)
#define HWIO_GCC_LPASS_CNOC_CFG_CBCR_CLK_OFF_BMSK                                                 0x80000000
#define HWIO_GCC_LPASS_CNOC_CFG_CBCR_CLK_OFF_SHFT                                                       0x1f
#define HWIO_GCC_LPASS_CNOC_CFG_CBCR_CLK_ARES_BMSK                                                       0x4
#define HWIO_GCC_LPASS_CNOC_CFG_CBCR_CLK_ARES_SHFT                                                       0x2
#define HWIO_GCC_LPASS_CNOC_CFG_CBCR_CLK_ENABLE_BMSK                                                     0x1
#define HWIO_GCC_LPASS_CNOC_CFG_CBCR_CLK_ENABLE_SHFT                                                     0x0

/*----------------------------------------------------------------------------
 * MODULE: OCIMEM_CSR
 *--------------------------------------------------------------------------*/

#define OCIMEM_CSR_REG_BASE                                            (OCIMEM_WRAPPER_CSR_BASE      + 0x00000000)

#define HWIO_OCIMEM_GEN_CTL_ADDR                                       (OCIMEM_CSR_REG_BASE      + 0x00000008)
#define HWIO_OCIMEM_GEN_CTL_RMSK                                         0x1f000f
#define HWIO_OCIMEM_GEN_CTL_IN          \
        in_dword_masked(HWIO_OCIMEM_GEN_CTL_ADDR, HWIO_OCIMEM_GEN_CTL_RMSK)
#define HWIO_OCIMEM_GEN_CTL_INM(m)      \
        in_dword_masked(HWIO_OCIMEM_GEN_CTL_ADDR, m)
#define HWIO_OCIMEM_GEN_CTL_OUT(v)      \
        out_dword(HWIO_OCIMEM_GEN_CTL_ADDR,v)
#define HWIO_OCIMEM_GEN_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_OCIMEM_GEN_CTL_ADDR,m,v,HWIO_OCIMEM_GEN_CTL_IN)
#define HWIO_OCIMEM_GEN_CTL_EXMON_GRAN_MASK_BMSK                         0x1f0000
#define HWIO_OCIMEM_GEN_CTL_EXMON_GRAN_MASK_SHFT                             0x10
#define HWIO_OCIMEM_GEN_CTL_CLREXMONREQ_PULSE_EN_BMSK                         0x8
#define HWIO_OCIMEM_GEN_CTL_CLREXMONREQ_PULSE_EN_SHFT                         0x3
#define HWIO_OCIMEM_GEN_CTL_EXMON_GRAN_128B_EN_BMSK                           0x4
#define HWIO_OCIMEM_GEN_CTL_EXMON_GRAN_128B_EN_SHFT                           0x2
#define HWIO_OCIMEM_GEN_CTL_CSR_AHB_BRIDGE_POSTWR_DIS_BMSK                    0x2
#define HWIO_OCIMEM_GEN_CTL_CSR_AHB_BRIDGE_POSTWR_DIS_SHFT                    0x1
#define HWIO_OCIMEM_GEN_CTL_SW_STM_FLAG_BMSK                                  0x1
#define HWIO_OCIMEM_GEN_CTL_SW_STM_FLAG_SHFT                                  0x0

/*----------------------------------------------------------------------------
 * MODULE: BIMC_GLOBAL0
 *--------------------------------------------------------------------------*/

#define BIMC_BASE                                                           (DDR_SS_BASE      + 0x00003000)

#define HWIO_BIMC_DDR_CH0_CLK_PERIOD_ADDR                                               (BIMC_BASE      + 0x00000028)
#define HWIO_BIMC_DDR_CH0_CLK_PERIOD_RMSK                                               0x1001ffff
#define HWIO_BIMC_DDR_CH0_CLK_PERIOD_IN          \
        in_dword_masked(HWIO_BIMC_DDR_CH0_CLK_PERIOD_ADDR, HWIO_BIMC_DDR_CH0_CLK_PERIOD_RMSK)
#define HWIO_BIMC_DDR_CH0_CLK_PERIOD_INM(m)      \
        in_dword_masked(HWIO_BIMC_DDR_CH0_CLK_PERIOD_ADDR, m)
#define HWIO_BIMC_DDR_CH0_CLK_PERIOD_OUT(v)      \
        out_dword(HWIO_BIMC_DDR_CH0_CLK_PERIOD_ADDR,v)
#define HWIO_BIMC_DDR_CH0_CLK_PERIOD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_DDR_CH0_CLK_PERIOD_ADDR,m,v,HWIO_BIMC_DDR_CH0_CLK_PERIOD_IN)
#define HWIO_BIMC_DDR_CH0_CLK_PERIOD_CLK_PERIOD_RESOLUTION_BMSK                         0x10000000
#define HWIO_BIMC_DDR_CH0_CLK_PERIOD_CLK_PERIOD_RESOLUTION_SHFT                               0x1c
#define HWIO_BIMC_DDR_CH0_CLK_PERIOD_PERIOD_BMSK                                           0x1ffff
#define HWIO_BIMC_DDR_CH0_CLK_PERIOD_PERIOD_SHFT                                               0x0

#define HWIO_BIMC_DDR_CH1_CLK_PERIOD_ADDR                                               (BIMC_BASE      + 0x0000002c)
#define HWIO_BIMC_DDR_CH1_CLK_PERIOD_RMSK                                               0x1001ffff
#define HWIO_BIMC_DDR_CH1_CLK_PERIOD_IN          \
        in_dword_masked(HWIO_BIMC_DDR_CH1_CLK_PERIOD_ADDR, HWIO_BIMC_DDR_CH1_CLK_PERIOD_RMSK)
#define HWIO_BIMC_DDR_CH1_CLK_PERIOD_INM(m)      \
        in_dword_masked(HWIO_BIMC_DDR_CH1_CLK_PERIOD_ADDR, m)
#define HWIO_BIMC_DDR_CH1_CLK_PERIOD_OUT(v)      \
        out_dword(HWIO_BIMC_DDR_CH1_CLK_PERIOD_ADDR,v)
#define HWIO_BIMC_DDR_CH1_CLK_PERIOD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_DDR_CH1_CLK_PERIOD_ADDR,m,v,HWIO_BIMC_DDR_CH1_CLK_PERIOD_IN)
#define HWIO_BIMC_DDR_CH1_CLK_PERIOD_CLK_PERIOD_RESOLUTION_BMSK                         0x10000000
#define HWIO_BIMC_DDR_CH1_CLK_PERIOD_CLK_PERIOD_RESOLUTION_SHFT                               0x1c
#define HWIO_BIMC_DDR_CH1_CLK_PERIOD_PERIOD_BMSK                                           0x1ffff
#define HWIO_BIMC_DDR_CH1_CLK_PERIOD_PERIOD_SHFT                                               0x0

/*----------------------------------------------------------------------------
 * MODULE: BIMC_GLOBAL2
 *--------------------------------------------------------------------------*/

#define BIMC_GLOBAL_BASE2_REG_BASE                                                      (DDR_SS_BASE      + 0x00005000)

#define HWIO_BIMC_BRIC_REDIRECT_CTRL_ADDR                                          (BIMC_GLOBAL_BASE2_REG_BASE      + 0x000001f4)
#define HWIO_BIMC_BRIC_REDIRECT_CTRL_RMSK                                          0xfe00ffff
#define HWIO_BIMC_BRIC_REDIRECT_CTRL_IN          \
        in_dword_masked(HWIO_BIMC_BRIC_REDIRECT_CTRL_ADDR, HWIO_BIMC_BRIC_REDIRECT_CTRL_RMSK)
#define HWIO_BIMC_BRIC_REDIRECT_CTRL_INM(m)      \
        in_dword_masked(HWIO_BIMC_BRIC_REDIRECT_CTRL_ADDR, m)
#define HWIO_BIMC_BRIC_REDIRECT_CTRL_OUT(v)      \
        out_dword(HWIO_BIMC_BRIC_REDIRECT_CTRL_ADDR,v)
#define HWIO_BIMC_BRIC_REDIRECT_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_BRIC_REDIRECT_CTRL_ADDR,m,v,HWIO_BIMC_BRIC_REDIRECT_CTRL_IN)
#define HWIO_BIMC_BRIC_REDIRECT_CTRL_REDIRECT_CTRL_EN_BMSK                         0x80000000
#define HWIO_BIMC_BRIC_REDIRECT_CTRL_REDIRECT_CTRL_EN_SHFT                               0x1f
#define HWIO_BIMC_BRIC_REDIRECT_CTRL_REDIRECT_SEND_ACK_BMSK                        0x40000000
#define HWIO_BIMC_BRIC_REDIRECT_CTRL_REDIRECT_SEND_ACK_SHFT                              0x1e
#define HWIO_BIMC_BRIC_REDIRECT_CTRL_SW_REDIRECT_CTRL_EN_BMSK                      0x20000000
#define HWIO_BIMC_BRIC_REDIRECT_CTRL_SW_REDIRECT_CTRL_EN_SHFT                            0x1d
#define HWIO_BIMC_BRIC_REDIRECT_CTRL_SW_REDIRECT_DISABLE_REQ_BMSK                  0x10000000
#define HWIO_BIMC_BRIC_REDIRECT_CTRL_SW_REDIRECT_DISABLE_REQ_SHFT                        0x1c
#define HWIO_BIMC_BRIC_REDIRECT_CTRL_REDIRECT_CTRL_UNSTALL_BMSK                     0xc000000
#define HWIO_BIMC_BRIC_REDIRECT_CTRL_REDIRECT_CTRL_UNSTALL_SHFT                          0x1a
#define HWIO_BIMC_BRIC_REDIRECT_CTRL_REDIRECT_DIS_WAIT_BMSK                         0x2000000
#define HWIO_BIMC_BRIC_REDIRECT_CTRL_REDIRECT_DIS_WAIT_SHFT                              0x19
#define HWIO_BIMC_BRIC_REDIRECT_CTRL_REDIRECT_EN_DELAY_BMSK                            0xffff
#define HWIO_BIMC_BRIC_REDIRECT_CTRL_REDIRECT_EN_DELAY_SHFT                               0x0

#define HWIO_BIMC_BRIC_REDIRECT_MSTR_EN_ADDR                                       (BIMC_GLOBAL_BASE2_REG_BASE      + 0x000001f8)
#define HWIO_BIMC_BRIC_REDIRECT_MSTR_EN_RMSK                                         0x7f007f
#define HWIO_BIMC_BRIC_REDIRECT_MSTR_EN_IN          \
        in_dword_masked(HWIO_BIMC_BRIC_REDIRECT_MSTR_EN_ADDR, HWIO_BIMC_BRIC_REDIRECT_MSTR_EN_RMSK)
#define HWIO_BIMC_BRIC_REDIRECT_MSTR_EN_INM(m)      \
        in_dword_masked(HWIO_BIMC_BRIC_REDIRECT_MSTR_EN_ADDR, m)
#define HWIO_BIMC_BRIC_REDIRECT_MSTR_EN_OUT(v)      \
        out_dword(HWIO_BIMC_BRIC_REDIRECT_MSTR_EN_ADDR,v)
#define HWIO_BIMC_BRIC_REDIRECT_MSTR_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_BRIC_REDIRECT_MSTR_EN_ADDR,m,v,HWIO_BIMC_BRIC_REDIRECT_MSTR_EN_IN)
#define HWIO_BIMC_BRIC_REDIRECT_MSTR_EN_REDIRECT_EN_MSTR_EN_BMSK                     0x7f0000
#define HWIO_BIMC_BRIC_REDIRECT_MSTR_EN_REDIRECT_EN_MSTR_EN_SHFT                         0x10
#define HWIO_BIMC_BRIC_REDIRECT_MSTR_EN_REDIRECT_DIS_MSTR_EN_BMSK                        0x7f
#define HWIO_BIMC_BRIC_REDIRECT_MSTR_EN_REDIRECT_DIS_MSTR_EN_SHFT                         0x0

#define HWIO_BIMC_BRIC_REDIRECT_CTRL_STATUS_ADDR                                   (BIMC_GLOBAL_BASE2_REG_BASE      + 0x000001fc)
#define HWIO_BIMC_BRIC_REDIRECT_CTRL_STATUS_RMSK                                         0x7f
#define HWIO_BIMC_BRIC_REDIRECT_CTRL_STATUS_IN          \
        in_dword_masked(HWIO_BIMC_BRIC_REDIRECT_CTRL_STATUS_ADDR, HWIO_BIMC_BRIC_REDIRECT_CTRL_STATUS_RMSK)
#define HWIO_BIMC_BRIC_REDIRECT_CTRL_STATUS_INM(m)      \
        in_dword_masked(HWIO_BIMC_BRIC_REDIRECT_CTRL_STATUS_ADDR, m)
#define HWIO_BIMC_BRIC_REDIRECT_CTRL_STATUS_RDC_CURRENT_STATE_BMSK                       0x70
#define HWIO_BIMC_BRIC_REDIRECT_CTRL_STATUS_RDC_CURRENT_STATE_SHFT                        0x4
#define HWIO_BIMC_BRIC_REDIRECT_CTRL_STATUS_RDC_REDIRECT_EN_BMSK                          0x8
#define HWIO_BIMC_BRIC_REDIRECT_CTRL_STATUS_RDC_REDIRECT_EN_SHFT                          0x3
#define HWIO_BIMC_BRIC_REDIRECT_CTRL_STATUS_RDC_STALL_REQ_BMSK                            0x4
#define HWIO_BIMC_BRIC_REDIRECT_CTRL_STATUS_RDC_STALL_REQ_SHFT                            0x2
#define HWIO_BIMC_BRIC_REDIRECT_CTRL_STATUS_RDC_REDIRECT_DISABLED_BMSK                    0x2
#define HWIO_BIMC_BRIC_REDIRECT_CTRL_STATUS_RDC_REDIRECT_DISABLED_SHFT                    0x1
#define HWIO_BIMC_BRIC_REDIRECT_CTRL_STATUS_RDC_REDIRECT_DISABLE_REQ_BMSK                 0x1
#define HWIO_BIMC_BRIC_REDIRECT_CTRL_STATUS_RDC_REDIRECT_DISABLE_REQ_SHFT                 0x0

/*----------------------------------------------------------------------------
 * MODULE: MMSS_CC
 *--------------------------------------------------------------------------*/

#define MMSS_CC_REG_BASE                                                                         (MMSS_BASE      + 0x000c0000)

#define HWIO_MMSS_VIDEO_TOP_GDSCR_ADDR                                                           (MMSS_CC_REG_BASE      + 0x00001024)
#define HWIO_MMSS_VIDEO_TOP_GDSCR_RMSK                                                           0xf8ffffff
#define HWIO_MMSS_VIDEO_TOP_GDSCR_IN          \
        in_dword_masked(HWIO_MMSS_VIDEO_TOP_GDSCR_ADDR, HWIO_MMSS_VIDEO_TOP_GDSCR_RMSK)
#define HWIO_MMSS_VIDEO_TOP_GDSCR_INM(m)      \
        in_dword_masked(HWIO_MMSS_VIDEO_TOP_GDSCR_ADDR, m)
#define HWIO_MMSS_VIDEO_TOP_GDSCR_OUT(v)      \
        out_dword(HWIO_MMSS_VIDEO_TOP_GDSCR_ADDR,v)
#define HWIO_MMSS_VIDEO_TOP_GDSCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MMSS_VIDEO_TOP_GDSCR_ADDR,m,v,HWIO_MMSS_VIDEO_TOP_GDSCR_IN)
#define HWIO_MMSS_VIDEO_TOP_GDSCR_PWR_ON_BMSK                                                    0x80000000
#define HWIO_MMSS_VIDEO_TOP_GDSCR_PWR_ON_SHFT                                                          0x1f
#define HWIO_MMSS_VIDEO_TOP_GDSCR_GDSC_STATE_BMSK                                                0x78000000
#define HWIO_MMSS_VIDEO_TOP_GDSCR_GDSC_STATE_SHFT                                                      0x1b
#define HWIO_MMSS_VIDEO_TOP_GDSCR_EN_REST_WAIT_BMSK                                                0xf00000
#define HWIO_MMSS_VIDEO_TOP_GDSCR_EN_REST_WAIT_SHFT                                                    0x14
#define HWIO_MMSS_VIDEO_TOP_GDSCR_EN_FEW_WAIT_BMSK                                                  0xf0000
#define HWIO_MMSS_VIDEO_TOP_GDSCR_EN_FEW_WAIT_SHFT                                                     0x10
#define HWIO_MMSS_VIDEO_TOP_GDSCR_CLK_DIS_WAIT_BMSK                                                  0xf000
#define HWIO_MMSS_VIDEO_TOP_GDSCR_CLK_DIS_WAIT_SHFT                                                     0xc
#define HWIO_MMSS_VIDEO_TOP_GDSCR_RETAIN_FF_ENABLE_BMSK                                               0x800
#define HWIO_MMSS_VIDEO_TOP_GDSCR_RETAIN_FF_ENABLE_SHFT                                                 0xb
#define HWIO_MMSS_VIDEO_TOP_GDSCR_RESTORE_BMSK                                                        0x400
#define HWIO_MMSS_VIDEO_TOP_GDSCR_RESTORE_SHFT                                                          0xa
#define HWIO_MMSS_VIDEO_TOP_GDSCR_SAVE_BMSK                                                           0x200
#define HWIO_MMSS_VIDEO_TOP_GDSCR_SAVE_SHFT                                                             0x9
#define HWIO_MMSS_VIDEO_TOP_GDSCR_RETAIN_BMSK                                                         0x100
#define HWIO_MMSS_VIDEO_TOP_GDSCR_RETAIN_SHFT                                                           0x8
#define HWIO_MMSS_VIDEO_TOP_GDSCR_EN_REST_BMSK                                                         0x80
#define HWIO_MMSS_VIDEO_TOP_GDSCR_EN_REST_SHFT                                                          0x7
#define HWIO_MMSS_VIDEO_TOP_GDSCR_EN_FEW_BMSK                                                          0x40
#define HWIO_MMSS_VIDEO_TOP_GDSCR_EN_FEW_SHFT                                                           0x6
#define HWIO_MMSS_VIDEO_TOP_GDSCR_CLAMP_IO_BMSK                                                        0x20
#define HWIO_MMSS_VIDEO_TOP_GDSCR_CLAMP_IO_SHFT                                                         0x5
#define HWIO_MMSS_VIDEO_TOP_GDSCR_CLK_DISABLE_BMSK                                                     0x10
#define HWIO_MMSS_VIDEO_TOP_GDSCR_CLK_DISABLE_SHFT                                                      0x4
#define HWIO_MMSS_VIDEO_TOP_GDSCR_PD_ARES_BMSK                                                          0x8
#define HWIO_MMSS_VIDEO_TOP_GDSCR_PD_ARES_SHFT                                                          0x3
#define HWIO_MMSS_VIDEO_TOP_GDSCR_SW_OVERRIDE_BMSK                                                      0x4
#define HWIO_MMSS_VIDEO_TOP_GDSCR_SW_OVERRIDE_SHFT                                                      0x2
#define HWIO_MMSS_VIDEO_TOP_GDSCR_HW_CONTROL_BMSK                                                       0x2
#define HWIO_MMSS_VIDEO_TOP_GDSCR_HW_CONTROL_SHFT                                                       0x1
#define HWIO_MMSS_VIDEO_TOP_GDSCR_SW_COLLAPSE_BMSK                                                      0x1
#define HWIO_MMSS_VIDEO_TOP_GDSCR_SW_COLLAPSE_SHFT                                                      0x0

#define HWIO_MMSS_THROTTLE_VIDEO_BCR_ADDR                                                        (MMSS_CC_REG_BASE      + 0x00001180)
#define HWIO_MMSS_THROTTLE_VIDEO_BCR_RMSK                                                               0x1
#define HWIO_MMSS_THROTTLE_VIDEO_BCR_IN          \
        in_dword_masked(HWIO_MMSS_THROTTLE_VIDEO_BCR_ADDR, HWIO_MMSS_THROTTLE_VIDEO_BCR_RMSK)
#define HWIO_MMSS_THROTTLE_VIDEO_BCR_INM(m)      \
        in_dword_masked(HWIO_MMSS_THROTTLE_VIDEO_BCR_ADDR, m)
#define HWIO_MMSS_THROTTLE_VIDEO_BCR_OUT(v)      \
        out_dword(HWIO_MMSS_THROTTLE_VIDEO_BCR_ADDR,v)
#define HWIO_MMSS_THROTTLE_VIDEO_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MMSS_THROTTLE_VIDEO_BCR_ADDR,m,v,HWIO_MMSS_THROTTLE_VIDEO_BCR_IN)
#define HWIO_MMSS_THROTTLE_VIDEO_BCR_BLK_ARES_BMSK                                                      0x1
#define HWIO_MMSS_THROTTLE_VIDEO_BCR_BLK_ARES_SHFT                                                      0x0

#define HWIO_MMSS_THROTTLE_VIDEO_AHB_CBCR_ADDR                                                   (MMSS_CC_REG_BASE      + 0x00001184)
#define HWIO_MMSS_THROTTLE_VIDEO_AHB_CBCR_RMSK                                                   0xf0008003
#define HWIO_MMSS_THROTTLE_VIDEO_AHB_CBCR_IN          \
        in_dword_masked(HWIO_MMSS_THROTTLE_VIDEO_AHB_CBCR_ADDR, HWIO_MMSS_THROTTLE_VIDEO_AHB_CBCR_RMSK)
#define HWIO_MMSS_THROTTLE_VIDEO_AHB_CBCR_INM(m)      \
        in_dword_masked(HWIO_MMSS_THROTTLE_VIDEO_AHB_CBCR_ADDR, m)
#define HWIO_MMSS_THROTTLE_VIDEO_AHB_CBCR_OUT(v)      \
        out_dword(HWIO_MMSS_THROTTLE_VIDEO_AHB_CBCR_ADDR,v)
#define HWIO_MMSS_THROTTLE_VIDEO_AHB_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MMSS_THROTTLE_VIDEO_AHB_CBCR_ADDR,m,v,HWIO_MMSS_THROTTLE_VIDEO_AHB_CBCR_IN)
#define HWIO_MMSS_THROTTLE_VIDEO_AHB_CBCR_CLK_OFF_BMSK                                           0x80000000
#define HWIO_MMSS_THROTTLE_VIDEO_AHB_CBCR_CLK_OFF_SHFT                                                 0x1f
#define HWIO_MMSS_THROTTLE_VIDEO_AHB_CBCR_NOC_HANDSHAKE_FSM_STATE_BMSK                           0x70000000
#define HWIO_MMSS_THROTTLE_VIDEO_AHB_CBCR_NOC_HANDSHAKE_FSM_STATE_SHFT                                 0x1c
#define HWIO_MMSS_THROTTLE_VIDEO_AHB_CBCR_NOC_HANDSHAKE_FSM_EN_BMSK                                  0x8000
#define HWIO_MMSS_THROTTLE_VIDEO_AHB_CBCR_NOC_HANDSHAKE_FSM_EN_SHFT                                     0xf
#define HWIO_MMSS_THROTTLE_VIDEO_AHB_CBCR_HW_CTL_BMSK                                                   0x2
#define HWIO_MMSS_THROTTLE_VIDEO_AHB_CBCR_HW_CTL_SHFT                                                   0x1
#define HWIO_MMSS_THROTTLE_VIDEO_AHB_CBCR_CLK_ENABLE_BMSK                                               0x1
#define HWIO_MMSS_THROTTLE_VIDEO_AHB_CBCR_CLK_ENABLE_SHFT                                               0x0

#define HWIO_MMSS_THROTTLE_VIDEO_CXO_CBCR_ADDR                                                   (MMSS_CC_REG_BASE      + 0x00001188)
#define HWIO_MMSS_THROTTLE_VIDEO_CXO_CBCR_RMSK                                                   0x80000001
#define HWIO_MMSS_THROTTLE_VIDEO_CXO_CBCR_IN          \
        in_dword_masked(HWIO_MMSS_THROTTLE_VIDEO_CXO_CBCR_ADDR, HWIO_MMSS_THROTTLE_VIDEO_CXO_CBCR_RMSK)
#define HWIO_MMSS_THROTTLE_VIDEO_CXO_CBCR_INM(m)      \
        in_dword_masked(HWIO_MMSS_THROTTLE_VIDEO_CXO_CBCR_ADDR, m)
#define HWIO_MMSS_THROTTLE_VIDEO_CXO_CBCR_OUT(v)      \
        out_dword(HWIO_MMSS_THROTTLE_VIDEO_CXO_CBCR_ADDR,v)
#define HWIO_MMSS_THROTTLE_VIDEO_CXO_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MMSS_THROTTLE_VIDEO_CXO_CBCR_ADDR,m,v,HWIO_MMSS_THROTTLE_VIDEO_CXO_CBCR_IN)
#define HWIO_MMSS_THROTTLE_VIDEO_CXO_CBCR_CLK_OFF_BMSK                                           0x80000000
#define HWIO_MMSS_THROTTLE_VIDEO_CXO_CBCR_CLK_OFF_SHFT                                                 0x1f
#define HWIO_MMSS_THROTTLE_VIDEO_CXO_CBCR_CLK_ENABLE_BMSK                                               0x1
#define HWIO_MMSS_THROTTLE_VIDEO_CXO_CBCR_CLK_ENABLE_SHFT                                               0x0

#define HWIO_MMSS_THROTTLE_VIDEO_AXI_CBCR_ADDR                                                   (MMSS_CC_REG_BASE      + 0x0000118c)
#define HWIO_MMSS_THROTTLE_VIDEO_AXI_CBCR_RMSK                                                   0x80000001
#define HWIO_MMSS_THROTTLE_VIDEO_AXI_CBCR_IN          \
        in_dword_masked(HWIO_MMSS_THROTTLE_VIDEO_AXI_CBCR_ADDR, HWIO_MMSS_THROTTLE_VIDEO_AXI_CBCR_RMSK)
#define HWIO_MMSS_THROTTLE_VIDEO_AXI_CBCR_INM(m)      \
        in_dword_masked(HWIO_MMSS_THROTTLE_VIDEO_AXI_CBCR_ADDR, m)
#define HWIO_MMSS_THROTTLE_VIDEO_AXI_CBCR_OUT(v)      \
        out_dword(HWIO_MMSS_THROTTLE_VIDEO_AXI_CBCR_ADDR,v)
#define HWIO_MMSS_THROTTLE_VIDEO_AXI_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MMSS_THROTTLE_VIDEO_AXI_CBCR_ADDR,m,v,HWIO_MMSS_THROTTLE_VIDEO_AXI_CBCR_IN)
#define HWIO_MMSS_THROTTLE_VIDEO_AXI_CBCR_CLK_OFF_BMSK                                           0x80000000
#define HWIO_MMSS_THROTTLE_VIDEO_AXI_CBCR_CLK_OFF_SHFT                                                 0x1f
#define HWIO_MMSS_THROTTLE_VIDEO_AXI_CBCR_CLK_ENABLE_BMSK                                               0x1
#define HWIO_MMSS_THROTTLE_VIDEO_AXI_CBCR_CLK_ENABLE_SHFT                                               0x0

#define HWIO_MMSS_MDSS_GDSCR_ADDR                                                                (MMSS_CC_REG_BASE      + 0x00002304)
#define HWIO_MMSS_MDSS_GDSCR_RMSK                                                                0xf8ffffff
#define HWIO_MMSS_MDSS_GDSCR_IN          \
        in_dword_masked(HWIO_MMSS_MDSS_GDSCR_ADDR, HWIO_MMSS_MDSS_GDSCR_RMSK)
#define HWIO_MMSS_MDSS_GDSCR_INM(m)      \
        in_dword_masked(HWIO_MMSS_MDSS_GDSCR_ADDR, m)
#define HWIO_MMSS_MDSS_GDSCR_OUT(v)      \
        out_dword(HWIO_MMSS_MDSS_GDSCR_ADDR,v)
#define HWIO_MMSS_MDSS_GDSCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MMSS_MDSS_GDSCR_ADDR,m,v,HWIO_MMSS_MDSS_GDSCR_IN)
#define HWIO_MMSS_MDSS_GDSCR_PWR_ON_BMSK                                                         0x80000000
#define HWIO_MMSS_MDSS_GDSCR_PWR_ON_SHFT                                                               0x1f
#define HWIO_MMSS_MDSS_GDSCR_GDSC_STATE_BMSK                                                     0x78000000
#define HWIO_MMSS_MDSS_GDSCR_GDSC_STATE_SHFT                                                           0x1b
#define HWIO_MMSS_MDSS_GDSCR_EN_REST_WAIT_BMSK                                                     0xf00000
#define HWIO_MMSS_MDSS_GDSCR_EN_REST_WAIT_SHFT                                                         0x14
#define HWIO_MMSS_MDSS_GDSCR_EN_FEW_WAIT_BMSK                                                       0xf0000
#define HWIO_MMSS_MDSS_GDSCR_EN_FEW_WAIT_SHFT                                                          0x10
#define HWIO_MMSS_MDSS_GDSCR_CLK_DIS_WAIT_BMSK                                                       0xf000
#define HWIO_MMSS_MDSS_GDSCR_CLK_DIS_WAIT_SHFT                                                          0xc
#define HWIO_MMSS_MDSS_GDSCR_RETAIN_FF_ENABLE_BMSK                                                    0x800
#define HWIO_MMSS_MDSS_GDSCR_RETAIN_FF_ENABLE_SHFT                                                      0xb
#define HWIO_MMSS_MDSS_GDSCR_RESTORE_BMSK                                                             0x400
#define HWIO_MMSS_MDSS_GDSCR_RESTORE_SHFT                                                               0xa
#define HWIO_MMSS_MDSS_GDSCR_SAVE_BMSK                                                                0x200
#define HWIO_MMSS_MDSS_GDSCR_SAVE_SHFT                                                                  0x9
#define HWIO_MMSS_MDSS_GDSCR_RETAIN_BMSK                                                              0x100
#define HWIO_MMSS_MDSS_GDSCR_RETAIN_SHFT                                                                0x8
#define HWIO_MMSS_MDSS_GDSCR_EN_REST_BMSK                                                              0x80
#define HWIO_MMSS_MDSS_GDSCR_EN_REST_SHFT                                                               0x7
#define HWIO_MMSS_MDSS_GDSCR_EN_FEW_BMSK                                                               0x40
#define HWIO_MMSS_MDSS_GDSCR_EN_FEW_SHFT                                                                0x6
#define HWIO_MMSS_MDSS_GDSCR_CLAMP_IO_BMSK                                                             0x20
#define HWIO_MMSS_MDSS_GDSCR_CLAMP_IO_SHFT                                                              0x5
#define HWIO_MMSS_MDSS_GDSCR_CLK_DISABLE_BMSK                                                          0x10
#define HWIO_MMSS_MDSS_GDSCR_CLK_DISABLE_SHFT                                                           0x4
#define HWIO_MMSS_MDSS_GDSCR_PD_ARES_BMSK                                                               0x8
#define HWIO_MMSS_MDSS_GDSCR_PD_ARES_SHFT                                                               0x3
#define HWIO_MMSS_MDSS_GDSCR_SW_OVERRIDE_BMSK                                                           0x4
#define HWIO_MMSS_MDSS_GDSCR_SW_OVERRIDE_SHFT                                                           0x2
#define HWIO_MMSS_MDSS_GDSCR_HW_CONTROL_BMSK                                                            0x2
#define HWIO_MMSS_MDSS_GDSCR_HW_CONTROL_SHFT                                                            0x1
#define HWIO_MMSS_MDSS_GDSCR_SW_COLLAPSE_BMSK                                                           0x1
#define HWIO_MMSS_MDSS_GDSCR_SW_COLLAPSE_SHFT                                                           0x0

#define HWIO_MMSS_THROTTLE_MDSS_BCR_ADDR                                                         (MMSS_CC_REG_BASE      + 0x00002460)
#define HWIO_MMSS_THROTTLE_MDSS_BCR_RMSK                                                                0x1
#define HWIO_MMSS_THROTTLE_MDSS_BCR_IN          \
        in_dword_masked(HWIO_MMSS_THROTTLE_MDSS_BCR_ADDR, HWIO_MMSS_THROTTLE_MDSS_BCR_RMSK)
#define HWIO_MMSS_THROTTLE_MDSS_BCR_INM(m)      \
        in_dword_masked(HWIO_MMSS_THROTTLE_MDSS_BCR_ADDR, m)
#define HWIO_MMSS_THROTTLE_MDSS_BCR_OUT(v)      \
        out_dword(HWIO_MMSS_THROTTLE_MDSS_BCR_ADDR,v)
#define HWIO_MMSS_THROTTLE_MDSS_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MMSS_THROTTLE_MDSS_BCR_ADDR,m,v,HWIO_MMSS_THROTTLE_MDSS_BCR_IN)
#define HWIO_MMSS_THROTTLE_MDSS_BCR_BLK_ARES_BMSK                                                       0x1
#define HWIO_MMSS_THROTTLE_MDSS_BCR_BLK_ARES_SHFT                                                       0x0

#define HWIO_MMSS_THROTTLE_MDSS_AHB_CBCR_ADDR                                                    (MMSS_CC_REG_BASE      + 0x00002464)
#define HWIO_MMSS_THROTTLE_MDSS_AHB_CBCR_RMSK                                                    0xf0008003
#define HWIO_MMSS_THROTTLE_MDSS_AHB_CBCR_IN          \
        in_dword_masked(HWIO_MMSS_THROTTLE_MDSS_AHB_CBCR_ADDR, HWIO_MMSS_THROTTLE_MDSS_AHB_CBCR_RMSK)
#define HWIO_MMSS_THROTTLE_MDSS_AHB_CBCR_INM(m)      \
        in_dword_masked(HWIO_MMSS_THROTTLE_MDSS_AHB_CBCR_ADDR, m)
#define HWIO_MMSS_THROTTLE_MDSS_AHB_CBCR_OUT(v)      \
        out_dword(HWIO_MMSS_THROTTLE_MDSS_AHB_CBCR_ADDR,v)
#define HWIO_MMSS_THROTTLE_MDSS_AHB_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MMSS_THROTTLE_MDSS_AHB_CBCR_ADDR,m,v,HWIO_MMSS_THROTTLE_MDSS_AHB_CBCR_IN)
#define HWIO_MMSS_THROTTLE_MDSS_AHB_CBCR_CLK_OFF_BMSK                                            0x80000000
#define HWIO_MMSS_THROTTLE_MDSS_AHB_CBCR_CLK_OFF_SHFT                                                  0x1f
#define HWIO_MMSS_THROTTLE_MDSS_AHB_CBCR_NOC_HANDSHAKE_FSM_STATE_BMSK                            0x70000000
#define HWIO_MMSS_THROTTLE_MDSS_AHB_CBCR_NOC_HANDSHAKE_FSM_STATE_SHFT                                  0x1c
#define HWIO_MMSS_THROTTLE_MDSS_AHB_CBCR_NOC_HANDSHAKE_FSM_EN_BMSK                                   0x8000
#define HWIO_MMSS_THROTTLE_MDSS_AHB_CBCR_NOC_HANDSHAKE_FSM_EN_SHFT                                      0xf
#define HWIO_MMSS_THROTTLE_MDSS_AHB_CBCR_HW_CTL_BMSK                                                    0x2
#define HWIO_MMSS_THROTTLE_MDSS_AHB_CBCR_HW_CTL_SHFT                                                    0x1
#define HWIO_MMSS_THROTTLE_MDSS_AHB_CBCR_CLK_ENABLE_BMSK                                                0x1
#define HWIO_MMSS_THROTTLE_MDSS_AHB_CBCR_CLK_ENABLE_SHFT                                                0x0

#define HWIO_MMSS_THROTTLE_MDSS_CXO_CBCR_ADDR                                                    (MMSS_CC_REG_BASE      + 0x00002468)
#define HWIO_MMSS_THROTTLE_MDSS_CXO_CBCR_RMSK                                                    0x80000001
#define HWIO_MMSS_THROTTLE_MDSS_CXO_CBCR_IN          \
        in_dword_masked(HWIO_MMSS_THROTTLE_MDSS_CXO_CBCR_ADDR, HWIO_MMSS_THROTTLE_MDSS_CXO_CBCR_RMSK)
#define HWIO_MMSS_THROTTLE_MDSS_CXO_CBCR_INM(m)      \
        in_dword_masked(HWIO_MMSS_THROTTLE_MDSS_CXO_CBCR_ADDR, m)
#define HWIO_MMSS_THROTTLE_MDSS_CXO_CBCR_OUT(v)      \
        out_dword(HWIO_MMSS_THROTTLE_MDSS_CXO_CBCR_ADDR,v)
#define HWIO_MMSS_THROTTLE_MDSS_CXO_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MMSS_THROTTLE_MDSS_CXO_CBCR_ADDR,m,v,HWIO_MMSS_THROTTLE_MDSS_CXO_CBCR_IN)
#define HWIO_MMSS_THROTTLE_MDSS_CXO_CBCR_CLK_OFF_BMSK                                            0x80000000
#define HWIO_MMSS_THROTTLE_MDSS_CXO_CBCR_CLK_OFF_SHFT                                                  0x1f
#define HWIO_MMSS_THROTTLE_MDSS_CXO_CBCR_CLK_ENABLE_BMSK                                                0x1
#define HWIO_MMSS_THROTTLE_MDSS_CXO_CBCR_CLK_ENABLE_SHFT                                                0x0

#define HWIO_MMSS_THROTTLE_MDSS_AXI_CBCR_ADDR                                                    (MMSS_CC_REG_BASE      + 0x0000246c)
#define HWIO_MMSS_THROTTLE_MDSS_AXI_CBCR_RMSK                                                    0x80000001
#define HWIO_MMSS_THROTTLE_MDSS_AXI_CBCR_IN          \
        in_dword_masked(HWIO_MMSS_THROTTLE_MDSS_AXI_CBCR_ADDR, HWIO_MMSS_THROTTLE_MDSS_AXI_CBCR_RMSK)
#define HWIO_MMSS_THROTTLE_MDSS_AXI_CBCR_INM(m)      \
        in_dword_masked(HWIO_MMSS_THROTTLE_MDSS_AXI_CBCR_ADDR, m)
#define HWIO_MMSS_THROTTLE_MDSS_AXI_CBCR_OUT(v)      \
        out_dword(HWIO_MMSS_THROTTLE_MDSS_AXI_CBCR_ADDR,v)
#define HWIO_MMSS_THROTTLE_MDSS_AXI_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MMSS_THROTTLE_MDSS_AXI_CBCR_ADDR,m,v,HWIO_MMSS_THROTTLE_MDSS_AXI_CBCR_IN)
#define HWIO_MMSS_THROTTLE_MDSS_AXI_CBCR_CLK_OFF_BMSK                                            0x80000000
#define HWIO_MMSS_THROTTLE_MDSS_AXI_CBCR_CLK_OFF_SHFT                                                  0x1f
#define HWIO_MMSS_THROTTLE_MDSS_AXI_CBCR_CLK_ENABLE_BMSK                                                0x1
#define HWIO_MMSS_THROTTLE_MDSS_AXI_CBCR_CLK_ENABLE_SHFT                                                0x0

#define HWIO_MMSS_CAMSS_TOP_GDSCR_ADDR                                                           (MMSS_CC_REG_BASE      + 0x000034a0)
#define HWIO_MMSS_CAMSS_TOP_GDSCR_RMSK                                                           0xf8ffffff
#define HWIO_MMSS_CAMSS_TOP_GDSCR_IN          \
        in_dword_masked(HWIO_MMSS_CAMSS_TOP_GDSCR_ADDR, HWIO_MMSS_CAMSS_TOP_GDSCR_RMSK)
#define HWIO_MMSS_CAMSS_TOP_GDSCR_INM(m)      \
        in_dword_masked(HWIO_MMSS_CAMSS_TOP_GDSCR_ADDR, m)
#define HWIO_MMSS_CAMSS_TOP_GDSCR_OUT(v)      \
        out_dword(HWIO_MMSS_CAMSS_TOP_GDSCR_ADDR,v)
#define HWIO_MMSS_CAMSS_TOP_GDSCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MMSS_CAMSS_TOP_GDSCR_ADDR,m,v,HWIO_MMSS_CAMSS_TOP_GDSCR_IN)
#define HWIO_MMSS_CAMSS_TOP_GDSCR_PWR_ON_BMSK                                                    0x80000000
#define HWIO_MMSS_CAMSS_TOP_GDSCR_PWR_ON_SHFT                                                          0x1f
#define HWIO_MMSS_CAMSS_TOP_GDSCR_GDSC_STATE_BMSK                                                0x78000000
#define HWIO_MMSS_CAMSS_TOP_GDSCR_GDSC_STATE_SHFT                                                      0x1b
#define HWIO_MMSS_CAMSS_TOP_GDSCR_EN_REST_WAIT_BMSK                                                0xf00000
#define HWIO_MMSS_CAMSS_TOP_GDSCR_EN_REST_WAIT_SHFT                                                    0x14
#define HWIO_MMSS_CAMSS_TOP_GDSCR_EN_FEW_WAIT_BMSK                                                  0xf0000
#define HWIO_MMSS_CAMSS_TOP_GDSCR_EN_FEW_WAIT_SHFT                                                     0x10
#define HWIO_MMSS_CAMSS_TOP_GDSCR_CLK_DIS_WAIT_BMSK                                                  0xf000
#define HWIO_MMSS_CAMSS_TOP_GDSCR_CLK_DIS_WAIT_SHFT                                                     0xc
#define HWIO_MMSS_CAMSS_TOP_GDSCR_RETAIN_FF_ENABLE_BMSK                                               0x800
#define HWIO_MMSS_CAMSS_TOP_GDSCR_RETAIN_FF_ENABLE_SHFT                                                 0xb
#define HWIO_MMSS_CAMSS_TOP_GDSCR_RESTORE_BMSK                                                        0x400
#define HWIO_MMSS_CAMSS_TOP_GDSCR_RESTORE_SHFT                                                          0xa
#define HWIO_MMSS_CAMSS_TOP_GDSCR_SAVE_BMSK                                                           0x200
#define HWIO_MMSS_CAMSS_TOP_GDSCR_SAVE_SHFT                                                             0x9
#define HWIO_MMSS_CAMSS_TOP_GDSCR_RETAIN_BMSK                                                         0x100
#define HWIO_MMSS_CAMSS_TOP_GDSCR_RETAIN_SHFT                                                           0x8
#define HWIO_MMSS_CAMSS_TOP_GDSCR_EN_REST_BMSK                                                         0x80
#define HWIO_MMSS_CAMSS_TOP_GDSCR_EN_REST_SHFT                                                          0x7
#define HWIO_MMSS_CAMSS_TOP_GDSCR_EN_FEW_BMSK                                                          0x40
#define HWIO_MMSS_CAMSS_TOP_GDSCR_EN_FEW_SHFT                                                           0x6
#define HWIO_MMSS_CAMSS_TOP_GDSCR_CLAMP_IO_BMSK                                                        0x20
#define HWIO_MMSS_CAMSS_TOP_GDSCR_CLAMP_IO_SHFT                                                         0x5
#define HWIO_MMSS_CAMSS_TOP_GDSCR_CLK_DISABLE_BMSK                                                     0x10
#define HWIO_MMSS_CAMSS_TOP_GDSCR_CLK_DISABLE_SHFT                                                      0x4
#define HWIO_MMSS_CAMSS_TOP_GDSCR_PD_ARES_BMSK                                                          0x8
#define HWIO_MMSS_CAMSS_TOP_GDSCR_PD_ARES_SHFT                                                          0x3
#define HWIO_MMSS_CAMSS_TOP_GDSCR_SW_OVERRIDE_BMSK                                                      0x4
#define HWIO_MMSS_CAMSS_TOP_GDSCR_SW_OVERRIDE_SHFT                                                      0x2
#define HWIO_MMSS_CAMSS_TOP_GDSCR_HW_CONTROL_BMSK                                                       0x2
#define HWIO_MMSS_CAMSS_TOP_GDSCR_HW_CONTROL_SHFT                                                       0x1
#define HWIO_MMSS_CAMSS_TOP_GDSCR_SW_COLLAPSE_BMSK                                                      0x1
#define HWIO_MMSS_CAMSS_TOP_GDSCR_SW_COLLAPSE_SHFT                                                      0x0

#define HWIO_MMSS_THROTTLE_CAMSS_BCR_ADDR                                                        (MMSS_CC_REG_BASE      + 0x00003c30)
#define HWIO_MMSS_THROTTLE_CAMSS_BCR_RMSK                                                               0x1
#define HWIO_MMSS_THROTTLE_CAMSS_BCR_IN          \
        in_dword_masked(HWIO_MMSS_THROTTLE_CAMSS_BCR_ADDR, HWIO_MMSS_THROTTLE_CAMSS_BCR_RMSK)
#define HWIO_MMSS_THROTTLE_CAMSS_BCR_INM(m)      \
        in_dword_masked(HWIO_MMSS_THROTTLE_CAMSS_BCR_ADDR, m)
#define HWIO_MMSS_THROTTLE_CAMSS_BCR_OUT(v)      \
        out_dword(HWIO_MMSS_THROTTLE_CAMSS_BCR_ADDR,v)
#define HWIO_MMSS_THROTTLE_CAMSS_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MMSS_THROTTLE_CAMSS_BCR_ADDR,m,v,HWIO_MMSS_THROTTLE_CAMSS_BCR_IN)
#define HWIO_MMSS_THROTTLE_CAMSS_BCR_BLK_ARES_BMSK                                                      0x1
#define HWIO_MMSS_THROTTLE_CAMSS_BCR_BLK_ARES_SHFT                                                      0x0

#define HWIO_MMSS_THROTTLE_CAMSS_AHB_CBCR_ADDR                                                   (MMSS_CC_REG_BASE      + 0x00003c34)
#define HWIO_MMSS_THROTTLE_CAMSS_AHB_CBCR_RMSK                                                   0xf0008003
#define HWIO_MMSS_THROTTLE_CAMSS_AHB_CBCR_IN          \
        in_dword_masked(HWIO_MMSS_THROTTLE_CAMSS_AHB_CBCR_ADDR, HWIO_MMSS_THROTTLE_CAMSS_AHB_CBCR_RMSK)
#define HWIO_MMSS_THROTTLE_CAMSS_AHB_CBCR_INM(m)      \
        in_dword_masked(HWIO_MMSS_THROTTLE_CAMSS_AHB_CBCR_ADDR, m)
#define HWIO_MMSS_THROTTLE_CAMSS_AHB_CBCR_OUT(v)      \
        out_dword(HWIO_MMSS_THROTTLE_CAMSS_AHB_CBCR_ADDR,v)
#define HWIO_MMSS_THROTTLE_CAMSS_AHB_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MMSS_THROTTLE_CAMSS_AHB_CBCR_ADDR,m,v,HWIO_MMSS_THROTTLE_CAMSS_AHB_CBCR_IN)
#define HWIO_MMSS_THROTTLE_CAMSS_AHB_CBCR_CLK_OFF_BMSK                                           0x80000000
#define HWIO_MMSS_THROTTLE_CAMSS_AHB_CBCR_CLK_OFF_SHFT                                                 0x1f
#define HWIO_MMSS_THROTTLE_CAMSS_AHB_CBCR_NOC_HANDSHAKE_FSM_STATE_BMSK                           0x70000000
#define HWIO_MMSS_THROTTLE_CAMSS_AHB_CBCR_NOC_HANDSHAKE_FSM_STATE_SHFT                                 0x1c
#define HWIO_MMSS_THROTTLE_CAMSS_AHB_CBCR_NOC_HANDSHAKE_FSM_EN_BMSK                                  0x8000
#define HWIO_MMSS_THROTTLE_CAMSS_AHB_CBCR_NOC_HANDSHAKE_FSM_EN_SHFT                                     0xf
#define HWIO_MMSS_THROTTLE_CAMSS_AHB_CBCR_HW_CTL_BMSK                                                   0x2
#define HWIO_MMSS_THROTTLE_CAMSS_AHB_CBCR_HW_CTL_SHFT                                                   0x1
#define HWIO_MMSS_THROTTLE_CAMSS_AHB_CBCR_CLK_ENABLE_BMSK                                               0x1
#define HWIO_MMSS_THROTTLE_CAMSS_AHB_CBCR_CLK_ENABLE_SHFT                                               0x0

#define HWIO_MMSS_THROTTLE_CAMSS_CXO_CBCR_ADDR                                                   (MMSS_CC_REG_BASE      + 0x00003c38)
#define HWIO_MMSS_THROTTLE_CAMSS_CXO_CBCR_RMSK                                                   0x80000001
#define HWIO_MMSS_THROTTLE_CAMSS_CXO_CBCR_IN          \
        in_dword_masked(HWIO_MMSS_THROTTLE_CAMSS_CXO_CBCR_ADDR, HWIO_MMSS_THROTTLE_CAMSS_CXO_CBCR_RMSK)
#define HWIO_MMSS_THROTTLE_CAMSS_CXO_CBCR_INM(m)      \
        in_dword_masked(HWIO_MMSS_THROTTLE_CAMSS_CXO_CBCR_ADDR, m)
#define HWIO_MMSS_THROTTLE_CAMSS_CXO_CBCR_OUT(v)      \
        out_dword(HWIO_MMSS_THROTTLE_CAMSS_CXO_CBCR_ADDR,v)
#define HWIO_MMSS_THROTTLE_CAMSS_CXO_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MMSS_THROTTLE_CAMSS_CXO_CBCR_ADDR,m,v,HWIO_MMSS_THROTTLE_CAMSS_CXO_CBCR_IN)
#define HWIO_MMSS_THROTTLE_CAMSS_CXO_CBCR_CLK_OFF_BMSK                                           0x80000000
#define HWIO_MMSS_THROTTLE_CAMSS_CXO_CBCR_CLK_OFF_SHFT                                                 0x1f
#define HWIO_MMSS_THROTTLE_CAMSS_CXO_CBCR_CLK_ENABLE_BMSK                                               0x1
#define HWIO_MMSS_THROTTLE_CAMSS_CXO_CBCR_CLK_ENABLE_SHFT                                               0x0

#define HWIO_MMSS_THROTTLE_CAMSS_AXI_CBCR_ADDR                                                   (MMSS_CC_REG_BASE      + 0x00003c3c)
#define HWIO_MMSS_THROTTLE_CAMSS_AXI_CBCR_RMSK                                                   0x80000001
#define HWIO_MMSS_THROTTLE_CAMSS_AXI_CBCR_IN          \
        in_dword_masked(HWIO_MMSS_THROTTLE_CAMSS_AXI_CBCR_ADDR, HWIO_MMSS_THROTTLE_CAMSS_AXI_CBCR_RMSK)
#define HWIO_MMSS_THROTTLE_CAMSS_AXI_CBCR_INM(m)      \
        in_dword_masked(HWIO_MMSS_THROTTLE_CAMSS_AXI_CBCR_ADDR, m)
#define HWIO_MMSS_THROTTLE_CAMSS_AXI_CBCR_OUT(v)      \
        out_dword(HWIO_MMSS_THROTTLE_CAMSS_AXI_CBCR_ADDR,v)
#define HWIO_MMSS_THROTTLE_CAMSS_AXI_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MMSS_THROTTLE_CAMSS_AXI_CBCR_ADDR,m,v,HWIO_MMSS_THROTTLE_CAMSS_AXI_CBCR_IN)
#define HWIO_MMSS_THROTTLE_CAMSS_AXI_CBCR_CLK_OFF_BMSK                                           0x80000000
#define HWIO_MMSS_THROTTLE_CAMSS_AXI_CBCR_CLK_OFF_SHFT                                                 0x1f
#define HWIO_MMSS_THROTTLE_CAMSS_AXI_CBCR_CLK_ENABLE_BMSK                                               0x1
#define HWIO_MMSS_THROTTLE_CAMSS_AXI_CBCR_CLK_ENABLE_SHFT                                               0x0

#define HWIO_MMSS_TZ_VIDEO_TOP_GDSC_SW_CTL_ADDR                                                  (MMSS_CC_REG_BASE      + 0x0000a008)
#define HWIO_MMSS_TZ_VIDEO_TOP_GDSC_SW_CTL_RMSK                                                       0x804
#define HWIO_MMSS_TZ_VIDEO_TOP_GDSC_SW_CTL_IN          \
        in_dword_masked(HWIO_MMSS_TZ_VIDEO_TOP_GDSC_SW_CTL_ADDR, HWIO_MMSS_TZ_VIDEO_TOP_GDSC_SW_CTL_RMSK)
#define HWIO_MMSS_TZ_VIDEO_TOP_GDSC_SW_CTL_INM(m)      \
        in_dword_masked(HWIO_MMSS_TZ_VIDEO_TOP_GDSC_SW_CTL_ADDR, m)
#define HWIO_MMSS_TZ_VIDEO_TOP_GDSC_SW_CTL_OUT(v)      \
        out_dword(HWIO_MMSS_TZ_VIDEO_TOP_GDSC_SW_CTL_ADDR,v)
#define HWIO_MMSS_TZ_VIDEO_TOP_GDSC_SW_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MMSS_TZ_VIDEO_TOP_GDSC_SW_CTL_ADDR,m,v,HWIO_MMSS_TZ_VIDEO_TOP_GDSC_SW_CTL_IN)
#define HWIO_MMSS_TZ_VIDEO_TOP_GDSC_SW_CTL_RETAIN_FF_ENABLE_BMSK                                      0x800
#define HWIO_MMSS_TZ_VIDEO_TOP_GDSC_SW_CTL_RETAIN_FF_ENABLE_SHFT                                        0xb
#define HWIO_MMSS_TZ_VIDEO_TOP_GDSC_SW_CTL_SW_OVERRIDE_BMSK                                             0x4
#define HWIO_MMSS_TZ_VIDEO_TOP_GDSC_SW_CTL_SW_OVERRIDE_SHFT                                             0x2

/*----------------------------------------------------------------------------
 * MODULE: LPASS_CC
 *--------------------------------------------------------------------------*/

#define LPASS_CC_REG_BASE                                                                                             (LPASS_BASE      + 0x00000000)

#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBS_AON_CBCR_ADDR                                                               (LPASS_CC_REG_BASE      + 0x00035014)
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

#define HWIO_LPASS_AUDIO_WRAPPER_QOS_XO_LAT_COUNTER_CBCR_ADDR                                                         (LPASS_CC_REG_BASE      + 0x00035018)
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

#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_ADDR                                                               (LPASS_CC_REG_BASE      + 0x00035024)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_RMSK                                                               0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_CLK_OFF_BMSK                                                       0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_CLK_OFF_SHFT                                                             0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_HW_CTL_BMSK                                                               0x2
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_HW_CTL_SHFT                                                               0x1
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_CLK_ENABLE_BMSK                                                           0x1
#define HWIO_LPASS_AUDIO_WRAPPER_QOS_AHBM_AON_CBCR_CLK_ENABLE_SHFT                                                           0x0

/*----------------------------------------------------------------------------
 * MODULE: LPASS_TCSR
 *--------------------------------------------------------------------------*/

#define LPASS_TCSR_REG_BASE                                                              (LPASS_BASE      + 0x00080000)

#define HWIO_LPASS_TCSR_QOS_CTL_ADDR                                                     (LPASS_TCSR_REG_BASE      + 0x0001e000)
#define HWIO_LPASS_TCSR_QOS_CTL_RMSK                                                            0x1
#define HWIO_LPASS_TCSR_QOS_CTL_IN          \
        in_dword_masked(HWIO_LPASS_TCSR_QOS_CTL_ADDR, HWIO_LPASS_TCSR_QOS_CTL_RMSK)
#define HWIO_LPASS_TCSR_QOS_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_TCSR_QOS_CTL_ADDR, m)
#define HWIO_LPASS_TCSR_QOS_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_TCSR_QOS_CTL_ADDR,v)
#define HWIO_LPASS_TCSR_QOS_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_TCSR_QOS_CTL_ADDR,m,v,HWIO_LPASS_TCSR_QOS_CTL_IN)
#define HWIO_LPASS_TCSR_QOS_CTL_QOS_ENABLE_BMSK                                                 0x1
#define HWIO_LPASS_TCSR_QOS_CTL_QOS_ENABLE_SHFT                                                 0x0

/*----------------------------------------------------------------------------
 * MODULE: LPASS_QOS_GASKET_QOS_GASKET_THROTTLE
 *--------------------------------------------------------------------------*/

#define LPASS_QOS_GASKET_QOS_GASKET_THROTTLE_REG_BASE                           (LPASS_LPASS_QOS_GASKET_BASE      + 0x00000100)

#define HWIO_LPASS_QOS_GASKET_CNTRL_ADDR                                        (LPASS_QOS_GASKET_QOS_GASKET_THROTTLE_REG_BASE      + 0x00000000)
#define HWIO_LPASS_QOS_GASKET_CNTRL_RMSK                                            0xff01
#define HWIO_LPASS_QOS_GASKET_CNTRL_IN          \
        in_dword_masked(HWIO_LPASS_QOS_GASKET_CNTRL_ADDR, HWIO_LPASS_QOS_GASKET_CNTRL_RMSK)
#define HWIO_LPASS_QOS_GASKET_CNTRL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_GASKET_CNTRL_ADDR, m)
#define HWIO_LPASS_QOS_GASKET_CNTRL_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_GASKET_CNTRL_ADDR,v)
#define HWIO_LPASS_QOS_GASKET_CNTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_GASKET_CNTRL_ADDR,m,v,HWIO_LPASS_QOS_GASKET_CNTRL_IN)
#define HWIO_LPASS_QOS_GASKET_CNTRL_THRESHOLD_LEVEL_7_EN_BMSK                       0x8000
#define HWIO_LPASS_QOS_GASKET_CNTRL_THRESHOLD_LEVEL_7_EN_SHFT                          0xf
#define HWIO_LPASS_QOS_GASKET_CNTRL_THRESHOLD_LEVEL_6_EN_BMSK                       0x4000
#define HWIO_LPASS_QOS_GASKET_CNTRL_THRESHOLD_LEVEL_6_EN_SHFT                          0xe
#define HWIO_LPASS_QOS_GASKET_CNTRL_THRESHOLD_LEVEL_5_EN_BMSK                       0x2000
#define HWIO_LPASS_QOS_GASKET_CNTRL_THRESHOLD_LEVEL_5_EN_SHFT                          0xd
#define HWIO_LPASS_QOS_GASKET_CNTRL_THRESHOLD_LEVEL_4_EN_BMSK                       0x1000
#define HWIO_LPASS_QOS_GASKET_CNTRL_THRESHOLD_LEVEL_4_EN_SHFT                          0xc
#define HWIO_LPASS_QOS_GASKET_CNTRL_THRESHOLD_LEVEL_3_EN_BMSK                        0x800
#define HWIO_LPASS_QOS_GASKET_CNTRL_THRESHOLD_LEVEL_3_EN_SHFT                          0xb
#define HWIO_LPASS_QOS_GASKET_CNTRL_THRESHOLD_LEVEL_2_EN_BMSK                        0x400
#define HWIO_LPASS_QOS_GASKET_CNTRL_THRESHOLD_LEVEL_2_EN_SHFT                          0xa
#define HWIO_LPASS_QOS_GASKET_CNTRL_THRESHOLD_LEVEL_1_EN_BMSK                        0x200
#define HWIO_LPASS_QOS_GASKET_CNTRL_THRESHOLD_LEVEL_1_EN_SHFT                          0x9
#define HWIO_LPASS_QOS_GASKET_CNTRL_THRESHOLD_LEVEL_0_EN_BMSK                        0x100
#define HWIO_LPASS_QOS_GASKET_CNTRL_THRESHOLD_LEVEL_0_EN_SHFT                          0x8
#define HWIO_LPASS_QOS_GASKET_CNTRL_THROTTLE_EN_BMSK                                   0x1
#define HWIO_LPASS_QOS_GASKET_CNTRL_THROTTLE_EN_SHFT                                   0x0

#define HWIO_LPASS_QOS_GASKET_CGC_CNTRL_ADDR                                    (LPASS_QOS_GASKET_QOS_GASKET_THROTTLE_REG_BASE      + 0x00000004)
#define HWIO_LPASS_QOS_GASKET_CGC_CNTRL_RMSK                                           0x1
#define HWIO_LPASS_QOS_GASKET_CGC_CNTRL_IN          \
        in_dword_masked(HWIO_LPASS_QOS_GASKET_CGC_CNTRL_ADDR, HWIO_LPASS_QOS_GASKET_CGC_CNTRL_RMSK)
#define HWIO_LPASS_QOS_GASKET_CGC_CNTRL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_GASKET_CGC_CNTRL_ADDR, m)
#define HWIO_LPASS_QOS_GASKET_CGC_CNTRL_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_GASKET_CGC_CNTRL_ADDR,v)
#define HWIO_LPASS_QOS_GASKET_CGC_CNTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_GASKET_CGC_CNTRL_ADDR,m,v,HWIO_LPASS_QOS_GASKET_CGC_CNTRL_IN)
#define HWIO_LPASS_QOS_GASKET_CGC_CNTRL_THROTTLE_CGC_EN_BMSK                           0x1
#define HWIO_LPASS_QOS_GASKET_CGC_CNTRL_THROTTLE_CGC_EN_SHFT                           0x0

#define HWIO_LPASS_QOS_GASKET_RESET_CNTRL_ADDR                                  (LPASS_QOS_GASKET_QOS_GASKET_THROTTLE_REG_BASE      + 0x00000008)
#define HWIO_LPASS_QOS_GASKET_RESET_CNTRL_RMSK                                         0x1
#define HWIO_LPASS_QOS_GASKET_RESET_CNTRL_IN          \
        in_dword_masked(HWIO_LPASS_QOS_GASKET_RESET_CNTRL_ADDR, HWIO_LPASS_QOS_GASKET_RESET_CNTRL_RMSK)
#define HWIO_LPASS_QOS_GASKET_RESET_CNTRL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_GASKET_RESET_CNTRL_ADDR, m)
#define HWIO_LPASS_QOS_GASKET_RESET_CNTRL_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_GASKET_RESET_CNTRL_ADDR,v)
#define HWIO_LPASS_QOS_GASKET_RESET_CNTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_GASKET_RESET_CNTRL_ADDR,m,v,HWIO_LPASS_QOS_GASKET_RESET_CNTRL_IN)
#define HWIO_LPASS_QOS_GASKET_RESET_CNTRL_CORE_SW_RESET_BMSK                           0x1
#define HWIO_LPASS_QOS_GASKET_RESET_CNTRL_CORE_SW_RESET_SHFT                           0x0

#define HWIO_LPASS_QOS_GASKET_CONFIG_ADDR                                       (LPASS_QOS_GASKET_QOS_GASKET_THROTTLE_REG_BASE      + 0x0000000c)
#define HWIO_LPASS_QOS_GASKET_CONFIG_RMSK                                              0x7
#define HWIO_LPASS_QOS_GASKET_CONFIG_IN          \
        in_dword_masked(HWIO_LPASS_QOS_GASKET_CONFIG_ADDR, HWIO_LPASS_QOS_GASKET_CONFIG_RMSK)
#define HWIO_LPASS_QOS_GASKET_CONFIG_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_GASKET_CONFIG_ADDR, m)
#define HWIO_LPASS_QOS_GASKET_CONFIG_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_GASKET_CONFIG_ADDR,v)
#define HWIO_LPASS_QOS_GASKET_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_GASKET_CONFIG_ADDR,m,v,HWIO_LPASS_QOS_GASKET_CONFIG_IN)
#define HWIO_LPASS_QOS_GASKET_CONFIG_THROTTLE_CNTRL_MAX_SKEW_BMSK                      0x7
#define HWIO_LPASS_QOS_GASKET_CONFIG_THROTTLE_CNTRL_MAX_SKEW_SHFT                      0x0

#define HWIO_LPASS_QOS_GASKET_GRANT_PERIOD_ADDR                                 (LPASS_QOS_GASKET_QOS_GASKET_THROTTLE_REG_BASE      + 0x00000010)
#define HWIO_LPASS_QOS_GASKET_GRANT_PERIOD_RMSK                                     0x3fff
#define HWIO_LPASS_QOS_GASKET_GRANT_PERIOD_IN          \
        in_dword_masked(HWIO_LPASS_QOS_GASKET_GRANT_PERIOD_ADDR, HWIO_LPASS_QOS_GASKET_GRANT_PERIOD_RMSK)
#define HWIO_LPASS_QOS_GASKET_GRANT_PERIOD_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_GASKET_GRANT_PERIOD_ADDR, m)
#define HWIO_LPASS_QOS_GASKET_GRANT_PERIOD_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_GASKET_GRANT_PERIOD_ADDR,v)
#define HWIO_LPASS_QOS_GASKET_GRANT_PERIOD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_GASKET_GRANT_PERIOD_ADDR,m,v,HWIO_LPASS_QOS_GASKET_GRANT_PERIOD_IN)
#define HWIO_LPASS_QOS_GASKET_GRANT_PERIOD_GRANT_PERIOD_BMSK                        0x3fff
#define HWIO_LPASS_QOS_GASKET_GRANT_PERIOD_GRANT_PERIOD_SHFT                           0x0

#define HWIO_LPASS_QOS_GASKET_GRANT_COUNT_ADDR                                  (LPASS_QOS_GASKET_QOS_GASKET_THROTTLE_REG_BASE      + 0x00000014)
#define HWIO_LPASS_QOS_GASKET_GRANT_COUNT_RMSK                                      0xffff
#define HWIO_LPASS_QOS_GASKET_GRANT_COUNT_IN          \
        in_dword_masked(HWIO_LPASS_QOS_GASKET_GRANT_COUNT_ADDR, HWIO_LPASS_QOS_GASKET_GRANT_COUNT_RMSK)
#define HWIO_LPASS_QOS_GASKET_GRANT_COUNT_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_GASKET_GRANT_COUNT_ADDR, m)
#define HWIO_LPASS_QOS_GASKET_GRANT_COUNT_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_GASKET_GRANT_COUNT_ADDR,v)
#define HWIO_LPASS_QOS_GASKET_GRANT_COUNT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_GASKET_GRANT_COUNT_ADDR,m,v,HWIO_LPASS_QOS_GASKET_GRANT_COUNT_IN)
#define HWIO_LPASS_QOS_GASKET_GRANT_COUNT_GRANT_COUNT_BMSK                          0xffff
#define HWIO_LPASS_QOS_GASKET_GRANT_COUNT_GRANT_COUNT_SHFT                             0x0

#define HWIO_LPASS_QOS_GASKET_THRESHOLD_00_ADDR                                 (LPASS_QOS_GASKET_QOS_GASKET_THROTTLE_REG_BASE      + 0x00000018)
#define HWIO_LPASS_QOS_GASKET_THRESHOLD_00_RMSK                                 0xffffffff
#define HWIO_LPASS_QOS_GASKET_THRESHOLD_00_IN          \
        in_dword_masked(HWIO_LPASS_QOS_GASKET_THRESHOLD_00_ADDR, HWIO_LPASS_QOS_GASKET_THRESHOLD_00_RMSK)
#define HWIO_LPASS_QOS_GASKET_THRESHOLD_00_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_GASKET_THRESHOLD_00_ADDR, m)
#define HWIO_LPASS_QOS_GASKET_THRESHOLD_00_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_GASKET_THRESHOLD_00_ADDR,v)
#define HWIO_LPASS_QOS_GASKET_THRESHOLD_00_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_GASKET_THRESHOLD_00_ADDR,m,v,HWIO_LPASS_QOS_GASKET_THRESHOLD_00_IN)
#define HWIO_LPASS_QOS_GASKET_THRESHOLD_00_THRESHOLD_LEVEL_6_BMSK               0xffff0000
#define HWIO_LPASS_QOS_GASKET_THRESHOLD_00_THRESHOLD_LEVEL_6_SHFT                     0x10
#define HWIO_LPASS_QOS_GASKET_THRESHOLD_00_THRESHOLD_LEVEL_7_BMSK                   0xffff
#define HWIO_LPASS_QOS_GASKET_THRESHOLD_00_THRESHOLD_LEVEL_7_SHFT                      0x0

#define HWIO_LPASS_QOS_GASKET_THRESHOLD_01_ADDR                                 (LPASS_QOS_GASKET_QOS_GASKET_THROTTLE_REG_BASE      + 0x0000001c)
#define HWIO_LPASS_QOS_GASKET_THRESHOLD_01_RMSK                                 0xffffffff
#define HWIO_LPASS_QOS_GASKET_THRESHOLD_01_IN          \
        in_dword_masked(HWIO_LPASS_QOS_GASKET_THRESHOLD_01_ADDR, HWIO_LPASS_QOS_GASKET_THRESHOLD_01_RMSK)
#define HWIO_LPASS_QOS_GASKET_THRESHOLD_01_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_GASKET_THRESHOLD_01_ADDR, m)
#define HWIO_LPASS_QOS_GASKET_THRESHOLD_01_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_GASKET_THRESHOLD_01_ADDR,v)
#define HWIO_LPASS_QOS_GASKET_THRESHOLD_01_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_GASKET_THRESHOLD_01_ADDR,m,v,HWIO_LPASS_QOS_GASKET_THRESHOLD_01_IN)
#define HWIO_LPASS_QOS_GASKET_THRESHOLD_01_THRESHOLD_LEVEL_4_BMSK               0xffff0000
#define HWIO_LPASS_QOS_GASKET_THRESHOLD_01_THRESHOLD_LEVEL_4_SHFT                     0x10
#define HWIO_LPASS_QOS_GASKET_THRESHOLD_01_THRESHOLD_LEVEL_5_BMSK                   0xffff
#define HWIO_LPASS_QOS_GASKET_THRESHOLD_01_THRESHOLD_LEVEL_5_SHFT                      0x0

#define HWIO_LPASS_QOS_GASKET_THRESHOLD_02_ADDR                                 (LPASS_QOS_GASKET_QOS_GASKET_THROTTLE_REG_BASE      + 0x00000020)
#define HWIO_LPASS_QOS_GASKET_THRESHOLD_02_RMSK                                 0xffffffff
#define HWIO_LPASS_QOS_GASKET_THRESHOLD_02_IN          \
        in_dword_masked(HWIO_LPASS_QOS_GASKET_THRESHOLD_02_ADDR, HWIO_LPASS_QOS_GASKET_THRESHOLD_02_RMSK)
#define HWIO_LPASS_QOS_GASKET_THRESHOLD_02_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_GASKET_THRESHOLD_02_ADDR, m)
#define HWIO_LPASS_QOS_GASKET_THRESHOLD_02_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_GASKET_THRESHOLD_02_ADDR,v)
#define HWIO_LPASS_QOS_GASKET_THRESHOLD_02_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_GASKET_THRESHOLD_02_ADDR,m,v,HWIO_LPASS_QOS_GASKET_THRESHOLD_02_IN)
#define HWIO_LPASS_QOS_GASKET_THRESHOLD_02_THRESHOLD_LEVEL_2_BMSK               0xffff0000
#define HWIO_LPASS_QOS_GASKET_THRESHOLD_02_THRESHOLD_LEVEL_2_SHFT                     0x10
#define HWIO_LPASS_QOS_GASKET_THRESHOLD_02_THRESHOLD_LEVEL_3_BMSK                   0xffff
#define HWIO_LPASS_QOS_GASKET_THRESHOLD_02_THRESHOLD_LEVEL_3_SHFT                      0x0

#define HWIO_LPASS_QOS_GASKET_THRESHOLD_03_ADDR                                 (LPASS_QOS_GASKET_QOS_GASKET_THROTTLE_REG_BASE      + 0x00000024)
#define HWIO_LPASS_QOS_GASKET_THRESHOLD_03_RMSK                                 0xffffffff
#define HWIO_LPASS_QOS_GASKET_THRESHOLD_03_IN          \
        in_dword_masked(HWIO_LPASS_QOS_GASKET_THRESHOLD_03_ADDR, HWIO_LPASS_QOS_GASKET_THRESHOLD_03_RMSK)
#define HWIO_LPASS_QOS_GASKET_THRESHOLD_03_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_GASKET_THRESHOLD_03_ADDR, m)
#define HWIO_LPASS_QOS_GASKET_THRESHOLD_03_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_GASKET_THRESHOLD_03_ADDR,v)
#define HWIO_LPASS_QOS_GASKET_THRESHOLD_03_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_GASKET_THRESHOLD_03_ADDR,m,v,HWIO_LPASS_QOS_GASKET_THRESHOLD_03_IN)
#define HWIO_LPASS_QOS_GASKET_THRESHOLD_03_THRESHOLD_LEVEL_0_BMSK               0xffff0000
#define HWIO_LPASS_QOS_GASKET_THRESHOLD_03_THRESHOLD_LEVEL_0_SHFT                     0x10
#define HWIO_LPASS_QOS_GASKET_THRESHOLD_03_THRESHOLD_LEVEL_1_BMSK                   0xffff
#define HWIO_LPASS_QOS_GASKET_THRESHOLD_03_THRESHOLD_LEVEL_1_SHFT                      0x0

#define HWIO_LPASS_QOS_GASKET_PEAK_ACCUM_CREDIT_ADDR                            (LPASS_QOS_GASKET_QOS_GASKET_THROTTLE_REG_BASE      + 0x00000028)
#define HWIO_LPASS_QOS_GASKET_PEAK_ACCUM_CREDIT_RMSK                               0xfffff
#define HWIO_LPASS_QOS_GASKET_PEAK_ACCUM_CREDIT_IN          \
        in_dword_masked(HWIO_LPASS_QOS_GASKET_PEAK_ACCUM_CREDIT_ADDR, HWIO_LPASS_QOS_GASKET_PEAK_ACCUM_CREDIT_RMSK)
#define HWIO_LPASS_QOS_GASKET_PEAK_ACCUM_CREDIT_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_GASKET_PEAK_ACCUM_CREDIT_ADDR, m)
#define HWIO_LPASS_QOS_GASKET_PEAK_ACCUM_CREDIT_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_GASKET_PEAK_ACCUM_CREDIT_ADDR,v)
#define HWIO_LPASS_QOS_GASKET_PEAK_ACCUM_CREDIT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_GASKET_PEAK_ACCUM_CREDIT_ADDR,m,v,HWIO_LPASS_QOS_GASKET_PEAK_ACCUM_CREDIT_IN)
#define HWIO_LPASS_QOS_GASKET_PEAK_ACCUM_CREDIT_PEAK_ACCUM_CREDIT_BMSK             0xfffff
#define HWIO_LPASS_QOS_GASKET_PEAK_ACCUM_CREDIT_PEAK_ACCUM_CREDIT_SHFT                 0x0

#define HWIO_LPASS_QOS_GASKET_DEBUG_CNTL_ADDR                                   (LPASS_QOS_GASKET_QOS_GASKET_THROTTLE_REG_BASE      + 0x00000030)
#define HWIO_LPASS_QOS_GASKET_DEBUG_CNTL_RMSK                                        0xf01
#define HWIO_LPASS_QOS_GASKET_DEBUG_CNTL_IN          \
        in_dword_masked(HWIO_LPASS_QOS_GASKET_DEBUG_CNTL_ADDR, HWIO_LPASS_QOS_GASKET_DEBUG_CNTL_RMSK)
#define HWIO_LPASS_QOS_GASKET_DEBUG_CNTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_GASKET_DEBUG_CNTL_ADDR, m)
#define HWIO_LPASS_QOS_GASKET_DEBUG_CNTL_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_GASKET_DEBUG_CNTL_ADDR,v)
#define HWIO_LPASS_QOS_GASKET_DEBUG_CNTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_GASKET_DEBUG_CNTL_ADDR,m,v,HWIO_LPASS_QOS_GASKET_DEBUG_CNTL_IN)
#define HWIO_LPASS_QOS_GASKET_DEBUG_CNTL_DEBUG_SEL_BMSK                              0xf00
#define HWIO_LPASS_QOS_GASKET_DEBUG_CNTL_DEBUG_SEL_SHFT                                0x8
#define HWIO_LPASS_QOS_GASKET_DEBUG_CNTL_DEBUG_EN_BMSK                                 0x1
#define HWIO_LPASS_QOS_GASKET_DEBUG_CNTL_DEBUG_EN_SHFT                                 0x0

#define HWIO_LPASS_QOS_GASKET_DEBUG_READBACK_ADDR                               (LPASS_QOS_GASKET_QOS_GASKET_THROTTLE_REG_BASE      + 0x00000034)
#define HWIO_LPASS_QOS_GASKET_DEBUG_READBACK_RMSK                               0xffffffff
#define HWIO_LPASS_QOS_GASKET_DEBUG_READBACK_IN          \
        in_dword_masked(HWIO_LPASS_QOS_GASKET_DEBUG_READBACK_ADDR, HWIO_LPASS_QOS_GASKET_DEBUG_READBACK_RMSK)
#define HWIO_LPASS_QOS_GASKET_DEBUG_READBACK_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_GASKET_DEBUG_READBACK_ADDR, m)
#define HWIO_LPASS_QOS_GASKET_DEBUG_READBACK_DEBUG_BUS_READBACK_BMSK            0xffffffff
#define HWIO_LPASS_QOS_GASKET_DEBUG_READBACK_DEBUG_BUS_READBACK_SHFT                   0x0

#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_ADDR                                   (LPASS_QOS_GASKET_QOS_GASKET_THROTTLE_REG_BASE      + 0x00000040)
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_RMSK                                   0xffffffff
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_IN          \
        in_dword_masked(HWIO_LPASS_QOS_GASKET_SPARE_REGS_ADDR, HWIO_LPASS_QOS_GASKET_SPARE_REGS_RMSK)
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_GASKET_SPARE_REGS_ADDR, m)
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_GASKET_SPARE_REGS_ADDR,v)
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_GASKET_SPARE_REGS_ADDR,m,v,HWIO_LPASS_QOS_GASKET_SPARE_REGS_IN)
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_31_BMSK                  0x80000000
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_31_SHFT                        0x1f
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_30_BMSK                  0x40000000
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_30_SHFT                        0x1e
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_29_BMSK                  0x20000000
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_29_SHFT                        0x1d
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_28_BMSK                  0x10000000
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_28_SHFT                        0x1c
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_27_BMSK                   0x8000000
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_27_SHFT                        0x1b
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_26_BMSK                   0x4000000
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_26_SHFT                        0x1a
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_25_BMSK                   0x2000000
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_25_SHFT                        0x19
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_24_BMSK                   0x1000000
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_24_SHFT                        0x18
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_23_BMSK                    0x800000
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_23_SHFT                        0x17
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_22_BMSK                    0x400000
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_22_SHFT                        0x16
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_21_BMSK                    0x200000
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_21_SHFT                        0x15
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_20_BMSK                    0x100000
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_20_SHFT                        0x14
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_19_BMSK                     0x80000
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_19_SHFT                        0x13
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_18_BMSK                     0x40000
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_18_SHFT                        0x12
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_17_BMSK                     0x20000
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_17_SHFT                        0x11
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_16_BMSK                     0x10000
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_16_SHFT                        0x10
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_15_BMSK                      0x8000
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_15_SHFT                         0xf
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_14_BMSK                      0x4000
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_14_SHFT                         0xe
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_13_BMSK                      0x2000
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_13_SHFT                         0xd
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_12_BMSK                      0x1000
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_12_SHFT                         0xc
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_11_BMSK                       0x800
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_11_SHFT                         0xb
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_10_BMSK                       0x400
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_10_SHFT                         0xa
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_9_BMSK                        0x200
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_9_SHFT                          0x9
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_8_BMSK                        0x100
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_8_SHFT                          0x8
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_7_BMSK                         0x80
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_7_SHFT                          0x7
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_6_BMSK                         0x40
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_6_SHFT                          0x6
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_5_BMSK                         0x20
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_5_SHFT                          0x5
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_4_BMSK                         0x10
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_4_SHFT                          0x4
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_3_BMSK                          0x8
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_3_SHFT                          0x3
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_2_BMSK                          0x4
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_2_SHFT                          0x2
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_1_BMSK                          0x2
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_1_SHFT                          0x1
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_0_BMSK                          0x1
#define HWIO_LPASS_QOS_GASKET_SPARE_REGS_SPARE_REG_BIT_0_SHFT                          0x0

/*----------------------------------------------------------------------------
 * MODULE: QM
 *--------------------------------------------------------------------------*/

#define QM_REG_BASE                                                                                                    (QM_BASE      + 0x00000000)

#define HWIO_QM_DT_ACK_BYPASS_EN_ADDR                                                                                  (QM_REG_BASE      + 0x00000000)
#define HWIO_QM_DT_ACK_BYPASS_EN_RMSK                                                                                         0x1
#define HWIO_QM_DT_ACK_BYPASS_EN_IN          \
        in_dword_masked(HWIO_QM_DT_ACK_BYPASS_EN_ADDR, HWIO_QM_DT_ACK_BYPASS_EN_RMSK)
#define HWIO_QM_DT_ACK_BYPASS_EN_INM(m)      \
        in_dword_masked(HWIO_QM_DT_ACK_BYPASS_EN_ADDR, m)
#define HWIO_QM_DT_ACK_BYPASS_EN_OUT(v)      \
        out_dword(HWIO_QM_DT_ACK_BYPASS_EN_ADDR,v)
#define HWIO_QM_DT_ACK_BYPASS_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_DT_ACK_BYPASS_EN_ADDR,m,v,HWIO_QM_DT_ACK_BYPASS_EN_IN)
#define HWIO_QM_DT_ACK_BYPASS_EN_DT_ACK_BYPASS_EN_BMSK                                                                        0x1
#define HWIO_QM_DT_ACK_BYPASS_EN_DT_ACK_BYPASS_EN_SHFT                                                                        0x0

#define HWIO_QM_DT_AGGR_INPUT_MAX_SKEW_ADDR                                                                            (QM_REG_BASE      + 0x00000004)
#define HWIO_QM_DT_AGGR_INPUT_MAX_SKEW_RMSK                                                                                   0x7
#define HWIO_QM_DT_AGGR_INPUT_MAX_SKEW_IN          \
        in_dword_masked(HWIO_QM_DT_AGGR_INPUT_MAX_SKEW_ADDR, HWIO_QM_DT_AGGR_INPUT_MAX_SKEW_RMSK)
#define HWIO_QM_DT_AGGR_INPUT_MAX_SKEW_INM(m)      \
        in_dword_masked(HWIO_QM_DT_AGGR_INPUT_MAX_SKEW_ADDR, m)
#define HWIO_QM_DT_AGGR_INPUT_MAX_SKEW_OUT(v)      \
        out_dword(HWIO_QM_DT_AGGR_INPUT_MAX_SKEW_ADDR,v)
#define HWIO_QM_DT_AGGR_INPUT_MAX_SKEW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_DT_AGGR_INPUT_MAX_SKEW_ADDR,m,v,HWIO_QM_DT_AGGR_INPUT_MAX_SKEW_IN)
#define HWIO_QM_DT_AGGR_INPUT_MAX_SKEW_DT_AGGR_MAX_SKEW_BMSK                                                                  0x7
#define HWIO_QM_DT_AGGR_INPUT_MAX_SKEW_DT_AGGR_MAX_SKEW_SHFT                                                                  0x0

#define HWIO_QM_AGGR_SAFE_DT_OVERRIDE_CNTRL_ADDR                                                                       (QM_REG_BASE      + 0x00000008)
#define HWIO_QM_AGGR_SAFE_DT_OVERRIDE_CNTRL_RMSK                                                                            0x101
#define HWIO_QM_AGGR_SAFE_DT_OVERRIDE_CNTRL_IN          \
        in_dword_masked(HWIO_QM_AGGR_SAFE_DT_OVERRIDE_CNTRL_ADDR, HWIO_QM_AGGR_SAFE_DT_OVERRIDE_CNTRL_RMSK)
#define HWIO_QM_AGGR_SAFE_DT_OVERRIDE_CNTRL_INM(m)      \
        in_dword_masked(HWIO_QM_AGGR_SAFE_DT_OVERRIDE_CNTRL_ADDR, m)
#define HWIO_QM_AGGR_SAFE_DT_OVERRIDE_CNTRL_OUT(v)      \
        out_dword(HWIO_QM_AGGR_SAFE_DT_OVERRIDE_CNTRL_ADDR,v)
#define HWIO_QM_AGGR_SAFE_DT_OVERRIDE_CNTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_AGGR_SAFE_DT_OVERRIDE_CNTRL_ADDR,m,v,HWIO_QM_AGGR_SAFE_DT_OVERRIDE_CNTRL_IN)
#define HWIO_QM_AGGR_SAFE_DT_OVERRIDE_CNTRL_QM_AGGR_SAFE_DT_OVERRIDE_VALUE_BMSK                                             0x100
#define HWIO_QM_AGGR_SAFE_DT_OVERRIDE_CNTRL_QM_AGGR_SAFE_DT_OVERRIDE_VALUE_SHFT                                               0x8
#define HWIO_QM_AGGR_SAFE_DT_OVERRIDE_CNTRL_QM_AGGR_SAFE_DT_OVERRIDE_EN_BMSK                                                  0x1
#define HWIO_QM_AGGR_SAFE_DT_OVERRIDE_CNTRL_QM_AGGR_SAFE_DT_OVERRIDE_EN_SHFT                                                  0x0

#define HWIO_QM_DT_OVERRIDE_VALUE_ADDR                                                                                 (QM_REG_BASE      + 0x0000000c)
#define HWIO_QM_DT_OVERRIDE_VALUE_RMSK                                                                                       0x1f
#define HWIO_QM_DT_OVERRIDE_VALUE_IN          \
        in_dword_masked(HWIO_QM_DT_OVERRIDE_VALUE_ADDR, HWIO_QM_DT_OVERRIDE_VALUE_RMSK)
#define HWIO_QM_DT_OVERRIDE_VALUE_INM(m)      \
        in_dword_masked(HWIO_QM_DT_OVERRIDE_VALUE_ADDR, m)
#define HWIO_QM_DT_OVERRIDE_VALUE_OUT(v)      \
        out_dword(HWIO_QM_DT_OVERRIDE_VALUE_ADDR,v)
#define HWIO_QM_DT_OVERRIDE_VALUE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_DT_OVERRIDE_VALUE_ADDR,m,v,HWIO_QM_DT_OVERRIDE_VALUE_IN)
#define HWIO_QM_DT_OVERRIDE_VALUE_DT_ACK_OVERRIDE_VALUE_BMSK                                                                 0x10
#define HWIO_QM_DT_OVERRIDE_VALUE_DT_ACK_OVERRIDE_VALUE_SHFT                                                                  0x4
#define HWIO_QM_DT_OVERRIDE_VALUE_DT_URG_OVERRIDE_VALUE_BMSK                                                                  0xe
#define HWIO_QM_DT_OVERRIDE_VALUE_DT_URG_OVERRIDE_VALUE_SHFT                                                                  0x1
#define HWIO_QM_DT_OVERRIDE_VALUE_DT_REQ_OVERRIDE_VALUE_BMSK                                                                  0x1
#define HWIO_QM_DT_OVERRIDE_VALUE_DT_REQ_OVERRIDE_VALUE_SHFT                                                                  0x0

#define HWIO_QM_DT_OVERRIDE_EN_ADDR                                                                                    (QM_REG_BASE      + 0x00000010)
#define HWIO_QM_DT_OVERRIDE_EN_RMSK                                                                                           0x7
#define HWIO_QM_DT_OVERRIDE_EN_IN          \
        in_dword_masked(HWIO_QM_DT_OVERRIDE_EN_ADDR, HWIO_QM_DT_OVERRIDE_EN_RMSK)
#define HWIO_QM_DT_OVERRIDE_EN_INM(m)      \
        in_dword_masked(HWIO_QM_DT_OVERRIDE_EN_ADDR, m)
#define HWIO_QM_DT_OVERRIDE_EN_OUT(v)      \
        out_dword(HWIO_QM_DT_OVERRIDE_EN_ADDR,v)
#define HWIO_QM_DT_OVERRIDE_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_DT_OVERRIDE_EN_ADDR,m,v,HWIO_QM_DT_OVERRIDE_EN_IN)
#define HWIO_QM_DT_OVERRIDE_EN_DT_ACK_OVERRIDE_EN_BMSK                                                                        0x4
#define HWIO_QM_DT_OVERRIDE_EN_DT_ACK_OVERRIDE_EN_SHFT                                                                        0x2
#define HWIO_QM_DT_OVERRIDE_EN_DT_URG_OVERRIDE_EN_BMSK                                                                        0x2
#define HWIO_QM_DT_OVERRIDE_EN_DT_URG_OVERRIDE_EN_SHFT                                                                        0x1
#define HWIO_QM_DT_OVERRIDE_EN_DT_REQ_OVERRIDE_EN_BMSK                                                                        0x1
#define HWIO_QM_DT_OVERRIDE_EN_DT_REQ_OVERRIDE_EN_SHFT                                                                        0x0

#define HWIO_QM_DT_EXT_OVERRIDE_VALUE_ADDR                                                                             (QM_REG_BASE      + 0x00000014)
#define HWIO_QM_DT_EXT_OVERRIDE_VALUE_RMSK                                                                                    0xf
#define HWIO_QM_DT_EXT_OVERRIDE_VALUE_IN          \
        in_dword_masked(HWIO_QM_DT_EXT_OVERRIDE_VALUE_ADDR, HWIO_QM_DT_EXT_OVERRIDE_VALUE_RMSK)
#define HWIO_QM_DT_EXT_OVERRIDE_VALUE_INM(m)      \
        in_dword_masked(HWIO_QM_DT_EXT_OVERRIDE_VALUE_ADDR, m)
#define HWIO_QM_DT_EXT_OVERRIDE_VALUE_OUT(v)      \
        out_dword(HWIO_QM_DT_EXT_OVERRIDE_VALUE_ADDR,v)
#define HWIO_QM_DT_EXT_OVERRIDE_VALUE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_DT_EXT_OVERRIDE_VALUE_ADDR,m,v,HWIO_QM_DT_EXT_OVERRIDE_VALUE_IN)
#define HWIO_QM_DT_EXT_OVERRIDE_VALUE_DT_URG_EXT_OVERRIDE_VALUE_BMSK                                                          0xe
#define HWIO_QM_DT_EXT_OVERRIDE_VALUE_DT_URG_EXT_OVERRIDE_VALUE_SHFT                                                          0x1
#define HWIO_QM_DT_EXT_OVERRIDE_VALUE_DT_REQ_EXT_OVERRIDE_VALUE_BMSK                                                          0x1
#define HWIO_QM_DT_EXT_OVERRIDE_VALUE_DT_REQ_EXT_OVERRIDE_VALUE_SHFT                                                          0x0

#define HWIO_QM_DT_EXT_OVERRIDE_EN_ADDR                                                                                (QM_REG_BASE      + 0x00000018)
#define HWIO_QM_DT_EXT_OVERRIDE_EN_RMSK                                                                                       0x3
#define HWIO_QM_DT_EXT_OVERRIDE_EN_IN          \
        in_dword_masked(HWIO_QM_DT_EXT_OVERRIDE_EN_ADDR, HWIO_QM_DT_EXT_OVERRIDE_EN_RMSK)
#define HWIO_QM_DT_EXT_OVERRIDE_EN_INM(m)      \
        in_dword_masked(HWIO_QM_DT_EXT_OVERRIDE_EN_ADDR, m)
#define HWIO_QM_DT_EXT_OVERRIDE_EN_OUT(v)      \
        out_dword(HWIO_QM_DT_EXT_OVERRIDE_EN_ADDR,v)
#define HWIO_QM_DT_EXT_OVERRIDE_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_DT_EXT_OVERRIDE_EN_ADDR,m,v,HWIO_QM_DT_EXT_OVERRIDE_EN_IN)
#define HWIO_QM_DT_EXT_OVERRIDE_EN_DT_URG_EXT_OVERRIDE_EN_BMSK                                                                0x2
#define HWIO_QM_DT_EXT_OVERRIDE_EN_DT_URG_EXT_OVERRIDE_EN_SHFT                                                                0x1
#define HWIO_QM_DT_EXT_OVERRIDE_EN_DT_REQ_EXT_OVERRIDE_EN_BMSK                                                                0x1
#define HWIO_QM_DT_EXT_OVERRIDE_EN_DT_REQ_EXT_OVERRIDE_EN_SHFT                                                                0x0

#define HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_0_ADDR                                                                       (QM_REG_BASE      + 0x00000020)
#define HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_0_RMSK                                                                          0xfffff
#define HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_0_IN          \
        in_dword_masked(HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_0_ADDR, HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_0_RMSK)
#define HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_0_INM(m)      \
        in_dword_masked(HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_0_ADDR, m)
#define HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_0_OUT(v)      \
        out_dword(HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_0_ADDR,v)
#define HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_0_ADDR,m,v,HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_0_IN)
#define HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_0_PRE_STALL_TIMEOUT_CNT_URG_0_BMSK                                              0xfffff
#define HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_0_PRE_STALL_TIMEOUT_CNT_URG_0_SHFT                                                  0x0

#define HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_1_ADDR                                                                       (QM_REG_BASE      + 0x00000024)
#define HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_1_RMSK                                                                          0xfffff
#define HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_1_IN          \
        in_dword_masked(HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_1_ADDR, HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_1_RMSK)
#define HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_1_INM(m)      \
        in_dword_masked(HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_1_ADDR, m)
#define HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_1_OUT(v)      \
        out_dword(HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_1_ADDR,v)
#define HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_1_ADDR,m,v,HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_1_IN)
#define HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_1_PRE_STALL_TIMEOUT_CNT_URG_1_BMSK                                              0xfffff
#define HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_1_PRE_STALL_TIMEOUT_CNT_URG_1_SHFT                                                  0x0

#define HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_2_ADDR                                                                       (QM_REG_BASE      + 0x00000028)
#define HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_2_RMSK                                                                          0xfffff
#define HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_2_IN          \
        in_dword_masked(HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_2_ADDR, HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_2_RMSK)
#define HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_2_INM(m)      \
        in_dword_masked(HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_2_ADDR, m)
#define HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_2_OUT(v)      \
        out_dword(HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_2_ADDR,v)
#define HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_2_ADDR,m,v,HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_2_IN)
#define HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_2_PRE_STALL_TIMEOUT_CNT_URG_2_BMSK                                              0xfffff
#define HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_2_PRE_STALL_TIMEOUT_CNT_URG_2_SHFT                                                  0x0

#define HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_3_ADDR                                                                       (QM_REG_BASE      + 0x0000002c)
#define HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_3_RMSK                                                                          0xfffff
#define HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_3_IN          \
        in_dword_masked(HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_3_ADDR, HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_3_RMSK)
#define HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_3_INM(m)      \
        in_dword_masked(HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_3_ADDR, m)
#define HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_3_OUT(v)      \
        out_dword(HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_3_ADDR,v)
#define HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_3_ADDR,m,v,HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_3_IN)
#define HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_3_PRE_STALL_TIMEOUT_CNT_URG_3_BMSK                                              0xfffff
#define HWIO_QM_PRE_STALL_TIMEOUT_CNT_URG_3_PRE_STALL_TIMEOUT_CNT_URG_3_SHFT                                                  0x0

#define HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_0_ADDR                                                                      (QM_REG_BASE      + 0x00000030)
#define HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_0_RMSK                                                                         0xfffff
#define HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_0_IN          \
        in_dword_masked(HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_0_ADDR, HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_0_RMSK)
#define HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_0_INM(m)      \
        in_dword_masked(HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_0_ADDR, m)
#define HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_0_OUT(v)      \
        out_dword(HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_0_ADDR,v)
#define HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_0_ADDR,m,v,HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_0_IN)
#define HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_0_POST_STALL_TIMEOUT_CNT_URG_0_BMSK                                            0xfffff
#define HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_0_POST_STALL_TIMEOUT_CNT_URG_0_SHFT                                                0x0

#define HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_1_ADDR                                                                      (QM_REG_BASE      + 0x00000034)
#define HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_1_RMSK                                                                         0xfffff
#define HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_1_IN          \
        in_dword_masked(HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_1_ADDR, HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_1_RMSK)
#define HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_1_INM(m)      \
        in_dword_masked(HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_1_ADDR, m)
#define HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_1_OUT(v)      \
        out_dword(HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_1_ADDR,v)
#define HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_1_ADDR,m,v,HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_1_IN)
#define HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_1_POST_STALL_TIMEOUT_CNT_URG_1_BMSK                                            0xfffff
#define HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_1_POST_STALL_TIMEOUT_CNT_URG_1_SHFT                                                0x0

#define HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_2_ADDR                                                                      (QM_REG_BASE      + 0x00000038)
#define HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_2_RMSK                                                                         0xfffff
#define HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_2_IN          \
        in_dword_masked(HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_2_ADDR, HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_2_RMSK)
#define HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_2_INM(m)      \
        in_dword_masked(HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_2_ADDR, m)
#define HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_2_OUT(v)      \
        out_dword(HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_2_ADDR,v)
#define HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_2_ADDR,m,v,HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_2_IN)
#define HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_2_POST_STALL_TIMEOUT_CNT_URG_2_BMSK                                            0xfffff
#define HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_2_POST_STALL_TIMEOUT_CNT_URG_2_SHFT                                                0x0

#define HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_3_ADDR                                                                      (QM_REG_BASE      + 0x0000003c)
#define HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_3_RMSK                                                                         0xfffff
#define HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_3_IN          \
        in_dword_masked(HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_3_ADDR, HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_3_RMSK)
#define HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_3_INM(m)      \
        in_dword_masked(HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_3_ADDR, m)
#define HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_3_OUT(v)      \
        out_dword(HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_3_ADDR,v)
#define HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_3_ADDR,m,v,HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_3_IN)
#define HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_3_POST_STALL_TIMEOUT_CNT_URG_3_BMSK                                            0xfffff
#define HWIO_QM_POST_STALL_TIMEOUT_CNT_URG_3_POST_STALL_TIMEOUT_CNT_URG_3_SHFT                                                0x0

#define HWIO_QM_POST_STALL_WDW_OVERLAP_CNTL_ADDR                                                                       (QM_REG_BASE      + 0x00000050)
#define HWIO_QM_POST_STALL_WDW_OVERLAP_CNTL_RMSK                                                                           0x1103
#define HWIO_QM_POST_STALL_WDW_OVERLAP_CNTL_IN          \
        in_dword_masked(HWIO_QM_POST_STALL_WDW_OVERLAP_CNTL_ADDR, HWIO_QM_POST_STALL_WDW_OVERLAP_CNTL_RMSK)
#define HWIO_QM_POST_STALL_WDW_OVERLAP_CNTL_INM(m)      \
        in_dword_masked(HWIO_QM_POST_STALL_WDW_OVERLAP_CNTL_ADDR, m)
#define HWIO_QM_POST_STALL_WDW_OVERLAP_CNTL_OUT(v)      \
        out_dword(HWIO_QM_POST_STALL_WDW_OVERLAP_CNTL_ADDR,v)
#define HWIO_QM_POST_STALL_WDW_OVERLAP_CNTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_POST_STALL_WDW_OVERLAP_CNTL_ADDR,m,v,HWIO_QM_POST_STALL_WDW_OVERLAP_CNTL_IN)
#define HWIO_QM_POST_STALL_WDW_OVERLAP_CNTL_POST_WDW_TERM_BY_SAFE_BMSK                                                     0x1000
#define HWIO_QM_POST_STALL_WDW_OVERLAP_CNTL_POST_WDW_TERM_BY_SAFE_SHFT                                                        0xc
#define HWIO_QM_POST_STALL_WDW_OVERLAP_CNTL_POST_PRE_WDW_OVERLAP_PRIORITY_BMSK                                              0x100
#define HWIO_QM_POST_STALL_WDW_OVERLAP_CNTL_POST_PRE_WDW_OVERLAP_PRIORITY_SHFT                                                0x8
#define HWIO_QM_POST_STALL_WDW_OVERLAP_CNTL_POST_POST_WDW_OVERLAP_PRIORITY_BMSK                                               0x3
#define HWIO_QM_POST_STALL_WDW_OVERLAP_CNTL_POST_POST_WDW_OVERLAP_PRIORITY_SHFT                                               0x0

#define HWIO_QMIP_REVISION_ID_ADDR                                                                                     (QM_REG_BASE      + 0x00001000)
#define HWIO_QMIP_REVISION_ID_RMSK                                                                                     0xffffffff
#define HWIO_QMIP_REVISION_ID_IN          \
        in_dword_masked(HWIO_QMIP_REVISION_ID_ADDR, HWIO_QMIP_REVISION_ID_RMSK)
#define HWIO_QMIP_REVISION_ID_INM(m)      \
        in_dword_masked(HWIO_QMIP_REVISION_ID_ADDR, m)
#define HWIO_QMIP_REVISION_ID_MAJOR_BMSK                                                                               0xf0000000
#define HWIO_QMIP_REVISION_ID_MAJOR_SHFT                                                                                     0x1c
#define HWIO_QMIP_REVISION_ID_MINOR_BMSK                                                                                0xfff0000
#define HWIO_QMIP_REVISION_ID_MINOR_SHFT                                                                                     0x10
#define HWIO_QMIP_REVISION_ID_STEP_BMSK                                                                                    0xffff
#define HWIO_QMIP_REVISION_ID_STEP_SHFT                                                                                       0x0

#define HWIO_QM_CORE_CLK_CGC_CNTRL_ADDR                                                                                (QM_REG_BASE      + 0x00001004)
#define HWIO_QM_CORE_CLK_CGC_CNTRL_RMSK                                                                                      0x3f
#define HWIO_QM_CORE_CLK_CGC_CNTRL_IN          \
        in_dword_masked(HWIO_QM_CORE_CLK_CGC_CNTRL_ADDR, HWIO_QM_CORE_CLK_CGC_CNTRL_RMSK)
#define HWIO_QM_CORE_CLK_CGC_CNTRL_INM(m)      \
        in_dword_masked(HWIO_QM_CORE_CLK_CGC_CNTRL_ADDR, m)
#define HWIO_QM_CORE_CLK_CGC_CNTRL_OUT(v)      \
        out_dword(HWIO_QM_CORE_CLK_CGC_CNTRL_ADDR,v)
#define HWIO_QM_CORE_CLK_CGC_CNTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_CORE_CLK_CGC_CNTRL_ADDR,m,v,HWIO_QM_CORE_CLK_CGC_CNTRL_IN)
#define HWIO_QM_CORE_CLK_CGC_CNTRL_QM_TPDM_CGC_EN_BMSK                                                                       0x20
#define HWIO_QM_CORE_CLK_CGC_CNTRL_QM_TPDM_CGC_EN_SHFT                                                                        0x5
#define HWIO_QM_CORE_CLK_CGC_CNTRL_QM_DEBUG_CGC_EN_BMSK                                                                      0x10
#define HWIO_QM_CORE_CLK_CGC_CNTRL_QM_DEBUG_CGC_EN_SHFT                                                                       0x4
#define HWIO_QM_CORE_CLK_CGC_CNTRL_PERF_CNTR_CGC_EN_BMSK                                                                      0x8
#define HWIO_QM_CORE_CLK_CGC_CNTRL_PERF_CNTR_CGC_EN_SHFT                                                                      0x3
#define HWIO_QM_CORE_CLK_CGC_CNTRL_QM_OUTPUT_CGC_BYPASS_BMSK                                                                  0x4
#define HWIO_QM_CORE_CLK_CGC_CNTRL_QM_OUTPUT_CGC_BYPASS_SHFT                                                                  0x2
#define HWIO_QM_CORE_CLK_CGC_CNTRL_DT_CGC_BYPASS_BMSK                                                                         0x2
#define HWIO_QM_CORE_CLK_CGC_CNTRL_DT_CGC_BYPASS_SHFT                                                                         0x1
#define HWIO_QM_CORE_CLK_CGC_CNTRL_DANGER_SAFE_CGC_BYPASS_BMSK                                                                0x1
#define HWIO_QM_CORE_CLK_CGC_CNTRL_DANGER_SAFE_CGC_BYPASS_SHFT                                                                0x0

#define HWIO_QM_CORE_CLK_CGC_STATUS_ADDR                                                                               (QM_REG_BASE      + 0x00001008)
#define HWIO_QM_CORE_CLK_CGC_STATUS_RMSK                                                                                     0x3f
#define HWIO_QM_CORE_CLK_CGC_STATUS_IN          \
        in_dword_masked(HWIO_QM_CORE_CLK_CGC_STATUS_ADDR, HWIO_QM_CORE_CLK_CGC_STATUS_RMSK)
#define HWIO_QM_CORE_CLK_CGC_STATUS_INM(m)      \
        in_dword_masked(HWIO_QM_CORE_CLK_CGC_STATUS_ADDR, m)
#define HWIO_QM_CORE_CLK_CGC_STATUS_QM_TPDM_CORE_CLK_CGC_EN_READBACK_BMSK                                                    0x20
#define HWIO_QM_CORE_CLK_CGC_STATUS_QM_TPDM_CORE_CLK_CGC_EN_READBACK_SHFT                                                     0x5
#define HWIO_QM_CORE_CLK_CGC_STATUS_QM_DEBUG_CORE_CLK_CGC_EN_READBACK_BMSK                                                   0x10
#define HWIO_QM_CORE_CLK_CGC_STATUS_QM_DEBUG_CORE_CLK_CGC_EN_READBACK_SHFT                                                    0x4
#define HWIO_QM_CORE_CLK_CGC_STATUS_PERF_CNTR_CORE_CLK_CGC_EN_READBACK_BMSK                                                   0x8
#define HWIO_QM_CORE_CLK_CGC_STATUS_PERF_CNTR_CORE_CLK_CGC_EN_READBACK_SHFT                                                   0x3
#define HWIO_QM_CORE_CLK_CGC_STATUS_QM_OUTPUT_CORE_CLK_CGC_EN_READBACK_BMSK                                                   0x4
#define HWIO_QM_CORE_CLK_CGC_STATUS_QM_OUTPUT_CORE_CLK_CGC_EN_READBACK_SHFT                                                   0x2
#define HWIO_QM_CORE_CLK_CGC_STATUS_DT_CORE_CLK_CGC_EN_READBACK_BMSK                                                          0x2
#define HWIO_QM_CORE_CLK_CGC_STATUS_DT_CORE_CLK_CGC_EN_READBACK_SHFT                                                          0x1
#define HWIO_QM_CORE_CLK_CGC_STATUS_DANGER_SAFE_CORE_CLK_CGC_EN_READBACK_BMSK                                                 0x1
#define HWIO_QM_CORE_CLK_CGC_STATUS_DANGER_SAFE_CORE_CLK_CGC_EN_READBACK_SHFT                                                 0x0

#define HWIO_QM_RT_CLNT_DANGER_MAX_SKEW_ADDR                                                                           (QM_REG_BASE      + 0x0000100c)
#define HWIO_QM_RT_CLNT_DANGER_MAX_SKEW_RMSK                                                                           0x70070707
#define HWIO_QM_RT_CLNT_DANGER_MAX_SKEW_IN          \
        in_dword_masked(HWIO_QM_RT_CLNT_DANGER_MAX_SKEW_ADDR, HWIO_QM_RT_CLNT_DANGER_MAX_SKEW_RMSK)
#define HWIO_QM_RT_CLNT_DANGER_MAX_SKEW_INM(m)      \
        in_dword_masked(HWIO_QM_RT_CLNT_DANGER_MAX_SKEW_ADDR, m)
#define HWIO_QM_RT_CLNT_DANGER_MAX_SKEW_OUT(v)      \
        out_dword(HWIO_QM_RT_CLNT_DANGER_MAX_SKEW_ADDR,v)
#define HWIO_QM_RT_CLNT_DANGER_MAX_SKEW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_RT_CLNT_DANGER_MAX_SKEW_ADDR,m,v,HWIO_QM_RT_CLNT_DANGER_MAX_SKEW_IN)
#define HWIO_QM_RT_CLNT_DANGER_MAX_SKEW_DSP_MAX_SKEW_BMSK                                                              0x70000000
#define HWIO_QM_RT_CLNT_DANGER_MAX_SKEW_DSP_MAX_SKEW_SHFT                                                                    0x1c
#define HWIO_QM_RT_CLNT_DANGER_MAX_SKEW_VENUS_DANGER_MAX_SKEW_BMSK                                                        0x70000
#define HWIO_QM_RT_CLNT_DANGER_MAX_SKEW_VENUS_DANGER_MAX_SKEW_SHFT                                                           0x10
#define HWIO_QM_RT_CLNT_DANGER_MAX_SKEW_MDP_DANGER_MAX_SKEW_BMSK                                                            0x700
#define HWIO_QM_RT_CLNT_DANGER_MAX_SKEW_MDP_DANGER_MAX_SKEW_SHFT                                                              0x8
#define HWIO_QM_RT_CLNT_DANGER_MAX_SKEW_VFE_DANGER_MAX_SKEW_BMSK                                                              0x7
#define HWIO_QM_RT_CLNT_DANGER_MAX_SKEW_VFE_DANGER_MAX_SKEW_SHFT                                                              0x0

#define HWIO_QM_MODEM_DANGER_MAX_SKEW_ADDR                                                                             (QM_REG_BASE      + 0x00001010)
#define HWIO_QM_MODEM_DANGER_MAX_SKEW_RMSK                                                                                    0x7
#define HWIO_QM_MODEM_DANGER_MAX_SKEW_IN          \
        in_dword_masked(HWIO_QM_MODEM_DANGER_MAX_SKEW_ADDR, HWIO_QM_MODEM_DANGER_MAX_SKEW_RMSK)
#define HWIO_QM_MODEM_DANGER_MAX_SKEW_INM(m)      \
        in_dword_masked(HWIO_QM_MODEM_DANGER_MAX_SKEW_ADDR, m)
#define HWIO_QM_MODEM_DANGER_MAX_SKEW_OUT(v)      \
        out_dword(HWIO_QM_MODEM_DANGER_MAX_SKEW_ADDR,v)
#define HWIO_QM_MODEM_DANGER_MAX_SKEW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_MODEM_DANGER_MAX_SKEW_ADDR,m,v,HWIO_QM_MODEM_DANGER_MAX_SKEW_IN)
#define HWIO_QM_MODEM_DANGER_MAX_SKEW_MODEM_DANGER_MAX_SKEW_BMSK                                                              0x7
#define HWIO_QM_MODEM_DANGER_MAX_SKEW_MODEM_DANGER_MAX_SKEW_SHFT                                                              0x0

#define HWIO_QM_DANGER_SAFE_CNTRL_ADDR                                                                                 (QM_REG_BASE      + 0x00001014)
#define HWIO_QM_DANGER_SAFE_CNTRL_RMSK                                                                                        0x1
#define HWIO_QM_DANGER_SAFE_CNTRL_IN          \
        in_dword_masked(HWIO_QM_DANGER_SAFE_CNTRL_ADDR, HWIO_QM_DANGER_SAFE_CNTRL_RMSK)
#define HWIO_QM_DANGER_SAFE_CNTRL_INM(m)      \
        in_dword_masked(HWIO_QM_DANGER_SAFE_CNTRL_ADDR, m)
#define HWIO_QM_DANGER_SAFE_CNTRL_OUT(v)      \
        out_dword(HWIO_QM_DANGER_SAFE_CNTRL_ADDR,v)
#define HWIO_QM_DANGER_SAFE_CNTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_DANGER_SAFE_CNTRL_ADDR,m,v,HWIO_QM_DANGER_SAFE_CNTRL_IN)
#define HWIO_QM_DANGER_SAFE_CNTRL_DANGER_SAFE_EN_BMSK                                                                         0x1
#define HWIO_QM_DANGER_SAFE_CNTRL_DANGER_SAFE_EN_SHFT                                                                         0x0

#define HWIO_QM_DSP_SAFE_MASK_CNTRL_ADDR                                                                               (QM_REG_BASE      + 0x00001018)
#define HWIO_QM_DSP_SAFE_MASK_CNTRL_RMSK                                                                                      0x3
#define HWIO_QM_DSP_SAFE_MASK_CNTRL_IN          \
        in_dword_masked(HWIO_QM_DSP_SAFE_MASK_CNTRL_ADDR, HWIO_QM_DSP_SAFE_MASK_CNTRL_RMSK)
#define HWIO_QM_DSP_SAFE_MASK_CNTRL_INM(m)      \
        in_dword_masked(HWIO_QM_DSP_SAFE_MASK_CNTRL_ADDR, m)
#define HWIO_QM_DSP_SAFE_MASK_CNTRL_OUT(v)      \
        out_dword(HWIO_QM_DSP_SAFE_MASK_CNTRL_ADDR,v)
#define HWIO_QM_DSP_SAFE_MASK_CNTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_DSP_SAFE_MASK_CNTRL_ADDR,m,v,HWIO_QM_DSP_SAFE_MASK_CNTRL_IN)
#define HWIO_QM_DSP_SAFE_MASK_CNTRL_DSP_SAFE_MASK_VALUE_BMSK                                                                  0x2
#define HWIO_QM_DSP_SAFE_MASK_CNTRL_DSP_SAFE_MASK_VALUE_SHFT                                                                  0x1
#define HWIO_QM_DSP_SAFE_MASK_CNTRL_DSP_SAFE_MASK_EN_BMSK                                                                     0x1
#define HWIO_QM_DSP_SAFE_MASK_CNTRL_DSP_SAFE_MASK_EN_SHFT                                                                     0x0

#define HWIO_QM_AGGR_SAFE_OVERRIDE_CNTRL_ADDR                                                                          (QM_REG_BASE      + 0x0000101c)
#define HWIO_QM_AGGR_SAFE_OVERRIDE_CNTRL_RMSK                                                                               0x101
#define HWIO_QM_AGGR_SAFE_OVERRIDE_CNTRL_IN          \
        in_dword_masked(HWIO_QM_AGGR_SAFE_OVERRIDE_CNTRL_ADDR, HWIO_QM_AGGR_SAFE_OVERRIDE_CNTRL_RMSK)
#define HWIO_QM_AGGR_SAFE_OVERRIDE_CNTRL_INM(m)      \
        in_dword_masked(HWIO_QM_AGGR_SAFE_OVERRIDE_CNTRL_ADDR, m)
#define HWIO_QM_AGGR_SAFE_OVERRIDE_CNTRL_OUT(v)      \
        out_dword(HWIO_QM_AGGR_SAFE_OVERRIDE_CNTRL_ADDR,v)
#define HWIO_QM_AGGR_SAFE_OVERRIDE_CNTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_AGGR_SAFE_OVERRIDE_CNTRL_ADDR,m,v,HWIO_QM_AGGR_SAFE_OVERRIDE_CNTRL_IN)
#define HWIO_QM_AGGR_SAFE_OVERRIDE_CNTRL_QM_AGGR_SAFE_OVERRIDE_VALUE_BMSK                                                   0x100
#define HWIO_QM_AGGR_SAFE_OVERRIDE_CNTRL_QM_AGGR_SAFE_OVERRIDE_VALUE_SHFT                                                     0x8
#define HWIO_QM_AGGR_SAFE_OVERRIDE_CNTRL_QM_AGGR_SAFE_OVERRIDE_SEL_BMSK                                                       0x1
#define HWIO_QM_AGGR_SAFE_OVERRIDE_CNTRL_QM_AGGR_SAFE_OVERRIDE_SEL_SHFT                                                       0x0

#define HWIO_QM_CLNT_n_DANGER_AGGR_CNTRL_ADDR(n)                                                                       (QM_REG_BASE      + 0x00001020 + 0x4 * (n))
#define HWIO_QM_CLNT_n_DANGER_AGGR_CNTRL_RMSK                                                                               0x117
#define HWIO_QM_CLNT_n_DANGER_AGGR_CNTRL_MAXn                                                                                   9
#define HWIO_QM_CLNT_n_DANGER_AGGR_CNTRL_INI(n)        \
        in_dword_masked(HWIO_QM_CLNT_n_DANGER_AGGR_CNTRL_ADDR(n), HWIO_QM_CLNT_n_DANGER_AGGR_CNTRL_RMSK)
#define HWIO_QM_CLNT_n_DANGER_AGGR_CNTRL_INMI(n,mask)    \
        in_dword_masked(HWIO_QM_CLNT_n_DANGER_AGGR_CNTRL_ADDR(n), mask)
#define HWIO_QM_CLNT_n_DANGER_AGGR_CNTRL_OUTI(n,val)    \
        out_dword(HWIO_QM_CLNT_n_DANGER_AGGR_CNTRL_ADDR(n),val)
#define HWIO_QM_CLNT_n_DANGER_AGGR_CNTRL_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QM_CLNT_n_DANGER_AGGR_CNTRL_ADDR(n),mask,val,HWIO_QM_CLNT_n_DANGER_AGGR_CNTRL_INI(n))
#define HWIO_QM_CLNT_n_DANGER_AGGR_CNTRL_DANGER_AGGR_ALGO_SEL_BMSK                                                          0x100
#define HWIO_QM_CLNT_n_DANGER_AGGR_CNTRL_DANGER_AGGR_ALGO_SEL_SHFT                                                            0x8
#define HWIO_QM_CLNT_n_DANGER_AGGR_CNTRL_DSP_EN_BMSK                                                                         0x10
#define HWIO_QM_CLNT_n_DANGER_AGGR_CNTRL_DSP_EN_SHFT                                                                          0x4
#define HWIO_QM_CLNT_n_DANGER_AGGR_CNTRL_VENUS_EN_BMSK                                                                        0x4
#define HWIO_QM_CLNT_n_DANGER_AGGR_CNTRL_VENUS_EN_SHFT                                                                        0x2
#define HWIO_QM_CLNT_n_DANGER_AGGR_CNTRL_MDP_EN_BMSK                                                                          0x2
#define HWIO_QM_CLNT_n_DANGER_AGGR_CNTRL_MDP_EN_SHFT                                                                          0x1
#define HWIO_QM_CLNT_n_DANGER_AGGR_CNTRL_VFE_EN_BMSK                                                                          0x1
#define HWIO_QM_CLNT_n_DANGER_AGGR_CNTRL_VFE_EN_SHFT                                                                          0x0

#define HWIO_QM_CLNT_n_DANGER_AGGR_MODEM_CNTRL_ADDR(n)                                                                 (QM_REG_BASE      + 0x00001060 + 0x4 * (n))
#define HWIO_QM_CLNT_n_DANGER_AGGR_MODEM_CNTRL_RMSK                                                                           0x1
#define HWIO_QM_CLNT_n_DANGER_AGGR_MODEM_CNTRL_MAXn                                                                             9
#define HWIO_QM_CLNT_n_DANGER_AGGR_MODEM_CNTRL_INI(n)        \
        in_dword_masked(HWIO_QM_CLNT_n_DANGER_AGGR_MODEM_CNTRL_ADDR(n), HWIO_QM_CLNT_n_DANGER_AGGR_MODEM_CNTRL_RMSK)
#define HWIO_QM_CLNT_n_DANGER_AGGR_MODEM_CNTRL_INMI(n,mask)    \
        in_dword_masked(HWIO_QM_CLNT_n_DANGER_AGGR_MODEM_CNTRL_ADDR(n), mask)
#define HWIO_QM_CLNT_n_DANGER_AGGR_MODEM_CNTRL_OUTI(n,val)    \
        out_dword(HWIO_QM_CLNT_n_DANGER_AGGR_MODEM_CNTRL_ADDR(n),val)
#define HWIO_QM_CLNT_n_DANGER_AGGR_MODEM_CNTRL_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QM_CLNT_n_DANGER_AGGR_MODEM_CNTRL_ADDR(n),mask,val,HWIO_QM_CLNT_n_DANGER_AGGR_MODEM_CNTRL_INI(n))
#define HWIO_QM_CLNT_n_DANGER_AGGR_MODEM_CNTRL_MODEM_EN_BMSK                                                                  0x1
#define HWIO_QM_CLNT_n_DANGER_AGGR_MODEM_CNTRL_MODEM_EN_SHFT                                                                  0x0

#define HWIO_QM_DSP_DANGER_AGGR_MODEM_CNTRL_ADDR                                                                       (QM_REG_BASE      + 0x00001090)
#define HWIO_QM_DSP_DANGER_AGGR_MODEM_CNTRL_RMSK                                                                              0x1
#define HWIO_QM_DSP_DANGER_AGGR_MODEM_CNTRL_IN          \
        in_dword_masked(HWIO_QM_DSP_DANGER_AGGR_MODEM_CNTRL_ADDR, HWIO_QM_DSP_DANGER_AGGR_MODEM_CNTRL_RMSK)
#define HWIO_QM_DSP_DANGER_AGGR_MODEM_CNTRL_INM(m)      \
        in_dword_masked(HWIO_QM_DSP_DANGER_AGGR_MODEM_CNTRL_ADDR, m)
#define HWIO_QM_DSP_DANGER_AGGR_MODEM_CNTRL_OUT(v)      \
        out_dword(HWIO_QM_DSP_DANGER_AGGR_MODEM_CNTRL_ADDR,v)
#define HWIO_QM_DSP_DANGER_AGGR_MODEM_CNTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_DSP_DANGER_AGGR_MODEM_CNTRL_ADDR,m,v,HWIO_QM_DSP_DANGER_AGGR_MODEM_CNTRL_IN)
#define HWIO_QM_DSP_DANGER_AGGR_MODEM_CNTRL_MODEM_EN_BMSK                                                                     0x1
#define HWIO_QM_DSP_DANGER_AGGR_MODEM_CNTRL_MODEM_EN_SHFT                                                                     0x0

#define HWIO_QM_DSP_SYSTEM_DANGER_AGGR_MODEM_CNTRL_ADDR                                                                (QM_REG_BASE      + 0x00001094)
#define HWIO_QM_DSP_SYSTEM_DANGER_AGGR_MODEM_CNTRL_RMSK                                                                       0x1
#define HWIO_QM_DSP_SYSTEM_DANGER_AGGR_MODEM_CNTRL_IN          \
        in_dword_masked(HWIO_QM_DSP_SYSTEM_DANGER_AGGR_MODEM_CNTRL_ADDR, HWIO_QM_DSP_SYSTEM_DANGER_AGGR_MODEM_CNTRL_RMSK)
#define HWIO_QM_DSP_SYSTEM_DANGER_AGGR_MODEM_CNTRL_INM(m)      \
        in_dword_masked(HWIO_QM_DSP_SYSTEM_DANGER_AGGR_MODEM_CNTRL_ADDR, m)
#define HWIO_QM_DSP_SYSTEM_DANGER_AGGR_MODEM_CNTRL_OUT(v)      \
        out_dword(HWIO_QM_DSP_SYSTEM_DANGER_AGGR_MODEM_CNTRL_ADDR,v)
#define HWIO_QM_DSP_SYSTEM_DANGER_AGGR_MODEM_CNTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_DSP_SYSTEM_DANGER_AGGR_MODEM_CNTRL_ADDR,m,v,HWIO_QM_DSP_SYSTEM_DANGER_AGGR_MODEM_CNTRL_IN)
#define HWIO_QM_DSP_SYSTEM_DANGER_AGGR_MODEM_CNTRL_MODEM_EN_BMSK                                                              0x1
#define HWIO_QM_DSP_SYSTEM_DANGER_AGGR_MODEM_CNTRL_MODEM_EN_SHFT                                                              0x0

#define HWIO_QM_DSP_DANGER_AGGR_CNTRL_ADDR                                                                             (QM_REG_BASE      + 0x000010a0)
#define HWIO_QM_DSP_DANGER_AGGR_CNTRL_RMSK                                                                                  0x1f7
#define HWIO_QM_DSP_DANGER_AGGR_CNTRL_IN          \
        in_dword_masked(HWIO_QM_DSP_DANGER_AGGR_CNTRL_ADDR, HWIO_QM_DSP_DANGER_AGGR_CNTRL_RMSK)
#define HWIO_QM_DSP_DANGER_AGGR_CNTRL_INM(m)      \
        in_dword_masked(HWIO_QM_DSP_DANGER_AGGR_CNTRL_ADDR, m)
#define HWIO_QM_DSP_DANGER_AGGR_CNTRL_OUT(v)      \
        out_dword(HWIO_QM_DSP_DANGER_AGGR_CNTRL_ADDR,v)
#define HWIO_QM_DSP_DANGER_AGGR_CNTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_DSP_DANGER_AGGR_CNTRL_ADDR,m,v,HWIO_QM_DSP_DANGER_AGGR_CNTRL_IN)
#define HWIO_QM_DSP_DANGER_AGGR_CNTRL_DANGER_AGGR_ALGO_SEL_BMSK                                                             0x100
#define HWIO_QM_DSP_DANGER_AGGR_CNTRL_DANGER_AGGR_ALGO_SEL_SHFT                                                               0x8
#define HWIO_QM_DSP_DANGER_AGGR_CNTRL_DSP_3_EN_BMSK                                                                          0x80
#define HWIO_QM_DSP_DANGER_AGGR_CNTRL_DSP_3_EN_SHFT                                                                           0x7
#define HWIO_QM_DSP_DANGER_AGGR_CNTRL_DSP_2_EN_BMSK                                                                          0x40
#define HWIO_QM_DSP_DANGER_AGGR_CNTRL_DSP_2_EN_SHFT                                                                           0x6
#define HWIO_QM_DSP_DANGER_AGGR_CNTRL_DSP_1_EN_BMSK                                                                          0x20
#define HWIO_QM_DSP_DANGER_AGGR_CNTRL_DSP_1_EN_SHFT                                                                           0x5
#define HWIO_QM_DSP_DANGER_AGGR_CNTRL_DSP_0_EN_BMSK                                                                          0x10
#define HWIO_QM_DSP_DANGER_AGGR_CNTRL_DSP_0_EN_SHFT                                                                           0x4
#define HWIO_QM_DSP_DANGER_AGGR_CNTRL_VENUS_EN_BMSK                                                                           0x4
#define HWIO_QM_DSP_DANGER_AGGR_CNTRL_VENUS_EN_SHFT                                                                           0x2
#define HWIO_QM_DSP_DANGER_AGGR_CNTRL_MDP_EN_BMSK                                                                             0x2
#define HWIO_QM_DSP_DANGER_AGGR_CNTRL_MDP_EN_SHFT                                                                             0x1
#define HWIO_QM_DSP_DANGER_AGGR_CNTRL_VFE_EN_BMSK                                                                             0x1
#define HWIO_QM_DSP_DANGER_AGGR_CNTRL_VFE_EN_SHFT                                                                             0x0

#define HWIO_QM_DSP_SYSTEM_DANGER_AGGR_CNTRL_ADDR                                                                      (QM_REG_BASE      + 0x000010a4)
#define HWIO_QM_DSP_SYSTEM_DANGER_AGGR_CNTRL_RMSK                                                                      0x800001f7
#define HWIO_QM_DSP_SYSTEM_DANGER_AGGR_CNTRL_IN          \
        in_dword_masked(HWIO_QM_DSP_SYSTEM_DANGER_AGGR_CNTRL_ADDR, HWIO_QM_DSP_SYSTEM_DANGER_AGGR_CNTRL_RMSK)
#define HWIO_QM_DSP_SYSTEM_DANGER_AGGR_CNTRL_INM(m)      \
        in_dword_masked(HWIO_QM_DSP_SYSTEM_DANGER_AGGR_CNTRL_ADDR, m)
#define HWIO_QM_DSP_SYSTEM_DANGER_AGGR_CNTRL_OUT(v)      \
        out_dword(HWIO_QM_DSP_SYSTEM_DANGER_AGGR_CNTRL_ADDR,v)
#define HWIO_QM_DSP_SYSTEM_DANGER_AGGR_CNTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_DSP_SYSTEM_DANGER_AGGR_CNTRL_ADDR,m,v,HWIO_QM_DSP_SYSTEM_DANGER_AGGR_CNTRL_IN)
#define HWIO_QM_DSP_SYSTEM_DANGER_AGGR_CNTRL_DSP_SYSTEM_DANGER_AGGR_LEGACY_BMSK                                        0x80000000
#define HWIO_QM_DSP_SYSTEM_DANGER_AGGR_CNTRL_DSP_SYSTEM_DANGER_AGGR_LEGACY_SHFT                                              0x1f
#define HWIO_QM_DSP_SYSTEM_DANGER_AGGR_CNTRL_DANGER_AGGR_ALGO_SEL_BMSK                                                      0x100
#define HWIO_QM_DSP_SYSTEM_DANGER_AGGR_CNTRL_DANGER_AGGR_ALGO_SEL_SHFT                                                        0x8
#define HWIO_QM_DSP_SYSTEM_DANGER_AGGR_CNTRL_DSP_3_EN_BMSK                                                                   0x80
#define HWIO_QM_DSP_SYSTEM_DANGER_AGGR_CNTRL_DSP_3_EN_SHFT                                                                    0x7
#define HWIO_QM_DSP_SYSTEM_DANGER_AGGR_CNTRL_DSP_2_EN_BMSK                                                                   0x40
#define HWIO_QM_DSP_SYSTEM_DANGER_AGGR_CNTRL_DSP_2_EN_SHFT                                                                    0x6
#define HWIO_QM_DSP_SYSTEM_DANGER_AGGR_CNTRL_DSP_1_EN_BMSK                                                                   0x20
#define HWIO_QM_DSP_SYSTEM_DANGER_AGGR_CNTRL_DSP_1_EN_SHFT                                                                    0x5
#define HWIO_QM_DSP_SYSTEM_DANGER_AGGR_CNTRL_DSP_0_EN_BMSK                                                                   0x10
#define HWIO_QM_DSP_SYSTEM_DANGER_AGGR_CNTRL_DSP_0_EN_SHFT                                                                    0x4
#define HWIO_QM_DSP_SYSTEM_DANGER_AGGR_CNTRL_VENUS_EN_BMSK                                                                    0x4
#define HWIO_QM_DSP_SYSTEM_DANGER_AGGR_CNTRL_VENUS_EN_SHFT                                                                    0x2
#define HWIO_QM_DSP_SYSTEM_DANGER_AGGR_CNTRL_MDP_EN_BMSK                                                                      0x2
#define HWIO_QM_DSP_SYSTEM_DANGER_AGGR_CNTRL_MDP_EN_SHFT                                                                      0x1
#define HWIO_QM_DSP_SYSTEM_DANGER_AGGR_CNTRL_VFE_EN_BMSK                                                                      0x1
#define HWIO_QM_DSP_SYSTEM_DANGER_AGGR_CNTRL_VFE_EN_SHFT                                                                      0x0

#define HWIO_QM_DSP_HPM_RT_CLNT_CONTRIBUTE_OVERRIDE_ADDR                                                               (QM_REG_BASE      + 0x000010a8)
#define HWIO_QM_DSP_HPM_RT_CLNT_CONTRIBUTE_OVERRIDE_RMSK                                                                  0x10001
#define HWIO_QM_DSP_HPM_RT_CLNT_CONTRIBUTE_OVERRIDE_IN          \
        in_dword_masked(HWIO_QM_DSP_HPM_RT_CLNT_CONTRIBUTE_OVERRIDE_ADDR, HWIO_QM_DSP_HPM_RT_CLNT_CONTRIBUTE_OVERRIDE_RMSK)
#define HWIO_QM_DSP_HPM_RT_CLNT_CONTRIBUTE_OVERRIDE_INM(m)      \
        in_dword_masked(HWIO_QM_DSP_HPM_RT_CLNT_CONTRIBUTE_OVERRIDE_ADDR, m)
#define HWIO_QM_DSP_HPM_RT_CLNT_CONTRIBUTE_OVERRIDE_OUT(v)      \
        out_dword(HWIO_QM_DSP_HPM_RT_CLNT_CONTRIBUTE_OVERRIDE_ADDR,v)
#define HWIO_QM_DSP_HPM_RT_CLNT_CONTRIBUTE_OVERRIDE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_DSP_HPM_RT_CLNT_CONTRIBUTE_OVERRIDE_ADDR,m,v,HWIO_QM_DSP_HPM_RT_CLNT_CONTRIBUTE_OVERRIDE_IN)
#define HWIO_QM_DSP_HPM_RT_CLNT_CONTRIBUTE_OVERRIDE_DSP_SYSTEM_DANGER_HPM_RT_CLNT_CONTRIBUTE_OVERRIDE_BMSK                0x10000
#define HWIO_QM_DSP_HPM_RT_CLNT_CONTRIBUTE_OVERRIDE_DSP_SYSTEM_DANGER_HPM_RT_CLNT_CONTRIBUTE_OVERRIDE_SHFT                   0x10
#define HWIO_QM_DSP_HPM_RT_CLNT_CONTRIBUTE_OVERRIDE_DSP_HPM_RT_CLNT_CONTRIBUTE_OVERRIDE_BMSK                                  0x1
#define HWIO_QM_DSP_HPM_RT_CLNT_CONTRIBUTE_OVERRIDE_DSP_HPM_RT_CLNT_CONTRIBUTE_OVERRIDE_SHFT                                  0x0

#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_00_ADDR                                                                   (QM_REG_BASE      + 0x00001150)
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_00_RMSK                                                                     0xffffff
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_00_IN          \
        in_dword_masked(HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_00_ADDR, HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_00_RMSK)
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_00_INM(m)      \
        in_dword_masked(HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_00_ADDR, m)
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_00_OUT(v)      \
        out_dword(HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_00_ADDR,v)
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_00_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_00_ADDR,m,v,HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_00_IN)
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_7_BMSK                                             0xe00000
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_7_SHFT                                                 0x15
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_6_BMSK                                             0x1c0000
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_6_SHFT                                                 0x12
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_5_BMSK                                              0x38000
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_5_SHFT                                                  0xf
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_4_BMSK                                               0x7000
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_4_SHFT                                                  0xc
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_3_BMSK                                                0xe00
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_3_SHFT                                                  0x9
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_2_BMSK                                                0x1c0
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_2_SHFT                                                  0x6
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_1_BMSK                                                 0x38
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_1_SHFT                                                  0x3
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_0_BMSK                                                  0x7
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_0_SHFT                                                  0x0

#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_00_ADDR                                                                   (QM_REG_BASE      + 0x00001154)
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_00_RMSK                                                                     0xffffff
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_00_IN          \
        in_dword_masked(HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_00_ADDR, HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_00_RMSK)
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_00_INM(m)      \
        in_dword_masked(HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_00_ADDR, m)
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_00_OUT(v)      \
        out_dword(HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_00_ADDR,v)
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_00_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_00_ADDR,m,v,HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_00_IN)
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_7_BMSK                                             0xe00000
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_7_SHFT                                                 0x15
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_6_BMSK                                             0x1c0000
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_6_SHFT                                                 0x12
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_5_BMSK                                              0x38000
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_5_SHFT                                                  0xf
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_4_BMSK                                               0x7000
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_4_SHFT                                                  0xc
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_3_BMSK                                                0xe00
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_3_SHFT                                                  0x9
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_2_BMSK                                                0x1c0
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_2_SHFT                                                  0x6
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_1_BMSK                                                 0x38
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_1_SHFT                                                  0x3
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_0_BMSK                                                  0x7
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_0_SHFT                                                  0x0

#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_00_ADDR                                                                   (QM_REG_BASE      + 0x00001158)
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_00_RMSK                                                                     0xffffff
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_00_IN          \
        in_dword_masked(HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_00_ADDR, HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_00_RMSK)
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_00_INM(m)      \
        in_dword_masked(HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_00_ADDR, m)
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_00_OUT(v)      \
        out_dword(HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_00_ADDR,v)
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_00_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_00_ADDR,m,v,HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_00_IN)
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_7_BMSK                                             0xe00000
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_7_SHFT                                                 0x15
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_6_BMSK                                             0x1c0000
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_6_SHFT                                                 0x12
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_5_BMSK                                              0x38000
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_5_SHFT                                                  0xf
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_4_BMSK                                               0x7000
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_4_SHFT                                                  0xc
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_3_BMSK                                                0xe00
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_3_SHFT                                                  0x9
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_2_BMSK                                                0x1c0
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_2_SHFT                                                  0x6
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_1_BMSK                                                 0x38
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_1_SHFT                                                  0x3
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_0_BMSK                                                  0x7
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_0_SHFT                                                  0x0

#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_00_ADDR                                                                   (QM_REG_BASE      + 0x0000115c)
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_00_RMSK                                                                     0xffffff
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_00_IN          \
        in_dword_masked(HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_00_ADDR, HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_00_RMSK)
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_00_INM(m)      \
        in_dword_masked(HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_00_ADDR, m)
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_00_OUT(v)      \
        out_dword(HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_00_ADDR,v)
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_00_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_00_ADDR,m,v,HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_00_IN)
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_7_BMSK                                             0xe00000
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_7_SHFT                                                 0x15
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_6_BMSK                                             0x1c0000
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_6_SHFT                                                 0x12
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_5_BMSK                                              0x38000
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_5_SHFT                                                  0xf
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_4_BMSK                                               0x7000
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_4_SHFT                                                  0xc
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_3_BMSK                                                0xe00
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_3_SHFT                                                  0x9
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_2_BMSK                                                0x1c0
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_2_SHFT                                                  0x6
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_1_BMSK                                                 0x38
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_1_SHFT                                                  0x3
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_0_BMSK                                                  0x7
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_0_SHFT                                                  0x0

#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_00_ADDR                                                                   (QM_REG_BASE      + 0x00001160)
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_00_RMSK                                                                     0xffffff
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_00_IN          \
        in_dword_masked(HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_00_ADDR, HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_00_RMSK)
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_00_INM(m)      \
        in_dword_masked(HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_00_ADDR, m)
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_00_OUT(v)      \
        out_dword(HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_00_ADDR,v)
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_00_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_00_ADDR,m,v,HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_00_IN)
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_7_BMSK                                             0xe00000
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_7_SHFT                                                 0x15
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_6_BMSK                                             0x1c0000
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_6_SHFT                                                 0x12
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_5_BMSK                                              0x38000
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_5_SHFT                                                  0xf
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_4_BMSK                                               0x7000
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_4_SHFT                                                  0xc
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_3_BMSK                                                0xe00
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_3_SHFT                                                  0x9
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_2_BMSK                                                0x1c0
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_2_SHFT                                                  0x6
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_1_BMSK                                                 0x38
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_1_SHFT                                                  0x3
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_0_BMSK                                                  0x7
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_0_SHFT                                                  0x0

#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_00_ADDR                                                                   (QM_REG_BASE      + 0x00001164)
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_00_RMSK                                                                     0xffffff
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_00_IN          \
        in_dword_masked(HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_00_ADDR, HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_00_RMSK)
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_00_INM(m)      \
        in_dword_masked(HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_00_ADDR, m)
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_00_OUT(v)      \
        out_dword(HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_00_ADDR,v)
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_00_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_00_ADDR,m,v,HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_00_IN)
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_7_BMSK                                             0xe00000
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_7_SHFT                                                 0x15
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_6_BMSK                                             0x1c0000
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_6_SHFT                                                 0x12
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_5_BMSK                                              0x38000
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_5_SHFT                                                  0xf
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_4_BMSK                                               0x7000
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_4_SHFT                                                  0xc
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_3_BMSK                                                0xe00
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_3_SHFT                                                  0x9
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_2_BMSK                                                0x1c0
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_2_SHFT                                                  0x6
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_1_BMSK                                                 0x38
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_1_SHFT                                                  0x3
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_0_BMSK                                                  0x7
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_0_SHFT                                                  0x0

#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_00_ADDR                                                                   (QM_REG_BASE      + 0x00001168)
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_00_RMSK                                                                     0xffffff
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_00_IN          \
        in_dword_masked(HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_00_ADDR, HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_00_RMSK)
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_00_INM(m)      \
        in_dword_masked(HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_00_ADDR, m)
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_00_OUT(v)      \
        out_dword(HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_00_ADDR,v)
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_00_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_00_ADDR,m,v,HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_00_IN)
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_7_BMSK                                             0xe00000
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_7_SHFT                                                 0x15
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_6_BMSK                                             0x1c0000
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_6_SHFT                                                 0x12
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_5_BMSK                                              0x38000
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_5_SHFT                                                  0xf
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_4_BMSK                                               0x7000
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_4_SHFT                                                  0xc
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_3_BMSK                                                0xe00
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_3_SHFT                                                  0x9
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_2_BMSK                                                0x1c0
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_2_SHFT                                                  0x6
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_1_BMSK                                                 0x38
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_1_SHFT                                                  0x3
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_0_BMSK                                                  0x7
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_0_SHFT                                                  0x0

#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_00_ADDR                                                                   (QM_REG_BASE      + 0x0000116c)
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_00_RMSK                                                                     0xffffff
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_00_IN          \
        in_dword_masked(HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_00_ADDR, HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_00_RMSK)
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_00_INM(m)      \
        in_dword_masked(HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_00_ADDR, m)
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_00_OUT(v)      \
        out_dword(HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_00_ADDR,v)
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_00_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_00_ADDR,m,v,HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_00_IN)
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_7_BMSK                                             0xe00000
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_7_SHFT                                                 0x15
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_6_BMSK                                             0x1c0000
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_6_SHFT                                                 0x12
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_5_BMSK                                              0x38000
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_5_SHFT                                                  0xf
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_4_BMSK                                               0x7000
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_4_SHFT                                                  0xc
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_3_BMSK                                                0xe00
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_3_SHFT                                                  0x9
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_2_BMSK                                                0x1c0
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_2_SHFT                                                  0x6
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_1_BMSK                                                 0x38
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_1_SHFT                                                  0x3
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_0_BMSK                                                  0x7
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_0_SHFT                                                  0x0

#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_00_ADDR                                                                   (QM_REG_BASE      + 0x00001170)
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_00_RMSK                                                                     0xffffff
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_00_IN          \
        in_dword_masked(HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_00_ADDR, HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_00_RMSK)
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_00_INM(m)      \
        in_dword_masked(HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_00_ADDR, m)
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_00_OUT(v)      \
        out_dword(HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_00_ADDR,v)
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_00_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_00_ADDR,m,v,HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_00_IN)
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_7_BMSK                                             0xe00000
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_7_SHFT                                                 0x15
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_6_BMSK                                             0x1c0000
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_6_SHFT                                                 0x12
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_5_BMSK                                              0x38000
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_5_SHFT                                                  0xf
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_4_BMSK                                               0x7000
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_4_SHFT                                                  0xc
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_3_BMSK                                                0xe00
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_3_SHFT                                                  0x9
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_2_BMSK                                                0x1c0
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_2_SHFT                                                  0x6
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_1_BMSK                                                 0x38
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_1_SHFT                                                  0x3
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_0_BMSK                                                  0x7
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_0_SHFT                                                  0x0

#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_00_ADDR                                                                   (QM_REG_BASE      + 0x00001174)
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_00_RMSK                                                                     0xffffff
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_00_IN          \
        in_dword_masked(HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_00_ADDR, HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_00_RMSK)
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_00_INM(m)      \
        in_dword_masked(HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_00_ADDR, m)
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_00_OUT(v)      \
        out_dword(HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_00_ADDR,v)
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_00_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_00_ADDR,m,v,HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_00_IN)
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_7_BMSK                                             0xe00000
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_7_SHFT                                                 0x15
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_6_BMSK                                             0x1c0000
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_6_SHFT                                                 0x12
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_5_BMSK                                              0x38000
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_5_SHFT                                                  0xf
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_4_BMSK                                               0x7000
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_4_SHFT                                                  0xc
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_3_BMSK                                                0xe00
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_3_SHFT                                                  0x9
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_2_BMSK                                                0x1c0
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_2_SHFT                                                  0x6
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_1_BMSK                                                 0x38
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_1_SHFT                                                  0x3
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_0_BMSK                                                  0x7
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_0_SHFT                                                  0x0

#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_00_ADDR                                                                  (QM_REG_BASE      + 0x00001178)
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_00_RMSK                                                                    0xffffff
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_00_IN          \
        in_dword_masked(HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_00_ADDR, HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_00_RMSK)
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_00_INM(m)      \
        in_dword_masked(HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_00_ADDR, m)
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_00_OUT(v)      \
        out_dword(HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_00_ADDR,v)
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_00_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_00_ADDR,m,v,HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_00_IN)
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_7_BMSK                                            0xe00000
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_7_SHFT                                                0x15
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_6_BMSK                                            0x1c0000
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_6_SHFT                                                0x12
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_5_BMSK                                             0x38000
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_5_SHFT                                                 0xf
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_4_BMSK                                              0x7000
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_4_SHFT                                                 0xc
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_3_BMSK                                               0xe00
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_3_SHFT                                                 0x9
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_2_BMSK                                               0x1c0
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_2_SHFT                                                 0x6
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_1_BMSK                                                0x38
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_1_SHFT                                                 0x3
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_0_BMSK                                                 0x7
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_00_THROTTLE_LEVEL_OUTPUT_0_SHFT                                                 0x0

#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_01_ADDR                                                                   (QM_REG_BASE      + 0x000011a0)
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_01_RMSK                                                                        0xfff
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_01_IN          \
        in_dword_masked(HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_01_ADDR, HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_01_RMSK)
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_01_INM(m)      \
        in_dword_masked(HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_01_ADDR, m)
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_01_OUT(v)      \
        out_dword(HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_01_ADDR,v)
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_01_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_01_ADDR,m,v,HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_01_IN)
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_11_BMSK                                               0xe00
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_11_SHFT                                                 0x9
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_10_BMSK                                               0x1c0
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_10_SHFT                                                 0x6
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_9_BMSK                                                 0x38
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_9_SHFT                                                  0x3
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_8_BMSK                                                  0x7
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_8_SHFT                                                  0x0

#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_01_ADDR                                                                   (QM_REG_BASE      + 0x000011a4)
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_01_RMSK                                                                        0xfff
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_01_IN          \
        in_dword_masked(HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_01_ADDR, HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_01_RMSK)
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_01_INM(m)      \
        in_dword_masked(HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_01_ADDR, m)
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_01_OUT(v)      \
        out_dword(HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_01_ADDR,v)
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_01_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_01_ADDR,m,v,HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_01_IN)
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_11_BMSK                                               0xe00
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_11_SHFT                                                 0x9
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_10_BMSK                                               0x1c0
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_10_SHFT                                                 0x6
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_9_BMSK                                                 0x38
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_9_SHFT                                                  0x3
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_8_BMSK                                                  0x7
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_8_SHFT                                                  0x0

#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_01_ADDR                                                                   (QM_REG_BASE      + 0x000011a8)
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_01_RMSK                                                                        0xfff
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_01_IN          \
        in_dword_masked(HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_01_ADDR, HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_01_RMSK)
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_01_INM(m)      \
        in_dword_masked(HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_01_ADDR, m)
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_01_OUT(v)      \
        out_dword(HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_01_ADDR,v)
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_01_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_01_ADDR,m,v,HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_01_IN)
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_11_BMSK                                               0xe00
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_11_SHFT                                                 0x9
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_10_BMSK                                               0x1c0
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_10_SHFT                                                 0x6
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_9_BMSK                                                 0x38
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_9_SHFT                                                  0x3
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_8_BMSK                                                  0x7
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_8_SHFT                                                  0x0

#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_01_ADDR                                                                   (QM_REG_BASE      + 0x000011ac)
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_01_RMSK                                                                        0xfff
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_01_IN          \
        in_dword_masked(HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_01_ADDR, HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_01_RMSK)
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_01_INM(m)      \
        in_dword_masked(HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_01_ADDR, m)
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_01_OUT(v)      \
        out_dword(HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_01_ADDR,v)
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_01_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_01_ADDR,m,v,HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_01_IN)
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_11_BMSK                                               0xe00
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_11_SHFT                                                 0x9
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_10_BMSK                                               0x1c0
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_10_SHFT                                                 0x6
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_9_BMSK                                                 0x38
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_9_SHFT                                                  0x3
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_8_BMSK                                                  0x7
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_8_SHFT                                                  0x0

#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_01_ADDR                                                                   (QM_REG_BASE      + 0x000011b0)
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_01_RMSK                                                                        0xfff
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_01_IN          \
        in_dword_masked(HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_01_ADDR, HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_01_RMSK)
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_01_INM(m)      \
        in_dword_masked(HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_01_ADDR, m)
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_01_OUT(v)      \
        out_dword(HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_01_ADDR,v)
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_01_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_01_ADDR,m,v,HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_01_IN)
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_11_BMSK                                               0xe00
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_11_SHFT                                                 0x9
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_10_BMSK                                               0x1c0
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_10_SHFT                                                 0x6
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_9_BMSK                                                 0x38
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_9_SHFT                                                  0x3
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_8_BMSK                                                  0x7
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_8_SHFT                                                  0x0

#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_01_ADDR                                                                   (QM_REG_BASE      + 0x000011b4)
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_01_RMSK                                                                        0xfff
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_01_IN          \
        in_dword_masked(HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_01_ADDR, HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_01_RMSK)
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_01_INM(m)      \
        in_dword_masked(HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_01_ADDR, m)
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_01_OUT(v)      \
        out_dword(HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_01_ADDR,v)
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_01_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_01_ADDR,m,v,HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_01_IN)
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_11_BMSK                                               0xe00
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_11_SHFT                                                 0x9
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_10_BMSK                                               0x1c0
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_10_SHFT                                                 0x6
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_9_BMSK                                                 0x38
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_9_SHFT                                                  0x3
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_8_BMSK                                                  0x7
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_8_SHFT                                                  0x0

#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_01_ADDR                                                                   (QM_REG_BASE      + 0x000011b8)
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_01_RMSK                                                                        0xfff
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_01_IN          \
        in_dword_masked(HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_01_ADDR, HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_01_RMSK)
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_01_INM(m)      \
        in_dword_masked(HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_01_ADDR, m)
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_01_OUT(v)      \
        out_dword(HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_01_ADDR,v)
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_01_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_01_ADDR,m,v,HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_01_IN)
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_11_BMSK                                               0xe00
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_11_SHFT                                                 0x9
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_10_BMSK                                               0x1c0
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_10_SHFT                                                 0x6
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_9_BMSK                                                 0x38
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_9_SHFT                                                  0x3
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_8_BMSK                                                  0x7
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_8_SHFT                                                  0x0

#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_01_ADDR                                                                   (QM_REG_BASE      + 0x000011bc)
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_01_RMSK                                                                        0xfff
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_01_IN          \
        in_dword_masked(HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_01_ADDR, HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_01_RMSK)
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_01_INM(m)      \
        in_dword_masked(HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_01_ADDR, m)
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_01_OUT(v)      \
        out_dword(HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_01_ADDR,v)
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_01_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_01_ADDR,m,v,HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_01_IN)
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_11_BMSK                                               0xe00
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_11_SHFT                                                 0x9
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_10_BMSK                                               0x1c0
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_10_SHFT                                                 0x6
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_9_BMSK                                                 0x38
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_9_SHFT                                                  0x3
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_8_BMSK                                                  0x7
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_8_SHFT                                                  0x0

#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_01_ADDR                                                                   (QM_REG_BASE      + 0x000011c0)
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_01_RMSK                                                                        0xfff
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_01_IN          \
        in_dword_masked(HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_01_ADDR, HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_01_RMSK)
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_01_INM(m)      \
        in_dword_masked(HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_01_ADDR, m)
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_01_OUT(v)      \
        out_dword(HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_01_ADDR,v)
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_01_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_01_ADDR,m,v,HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_01_IN)
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_11_BMSK                                               0xe00
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_11_SHFT                                                 0x9
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_10_BMSK                                               0x1c0
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_10_SHFT                                                 0x6
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_9_BMSK                                                 0x38
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_9_SHFT                                                  0x3
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_8_BMSK                                                  0x7
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_8_SHFT                                                  0x0

#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_01_ADDR                                                                   (QM_REG_BASE      + 0x000011c4)
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_01_RMSK                                                                        0xfff
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_01_IN          \
        in_dword_masked(HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_01_ADDR, HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_01_RMSK)
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_01_INM(m)      \
        in_dword_masked(HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_01_ADDR, m)
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_01_OUT(v)      \
        out_dword(HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_01_ADDR,v)
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_01_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_01_ADDR,m,v,HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_01_IN)
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_11_BMSK                                               0xe00
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_11_SHFT                                                 0x9
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_10_BMSK                                               0x1c0
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_10_SHFT                                                 0x6
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_9_BMSK                                                 0x38
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_9_SHFT                                                  0x3
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_8_BMSK                                                  0x7
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_8_SHFT                                                  0x0

#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_01_ADDR                                                                  (QM_REG_BASE      + 0x000011c8)
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_01_RMSK                                                                       0xfff
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_01_IN          \
        in_dword_masked(HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_01_ADDR, HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_01_RMSK)
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_01_INM(m)      \
        in_dword_masked(HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_01_ADDR, m)
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_01_OUT(v)      \
        out_dword(HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_01_ADDR,v)
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_01_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_01_ADDR,m,v,HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_01_IN)
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_11_BMSK                                              0xe00
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_11_SHFT                                                0x9
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_10_BMSK                                              0x1c0
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_10_SHFT                                                0x6
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_9_BMSK                                                0x38
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_9_SHFT                                                 0x3
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_8_BMSK                                                 0x7
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_01_THROTTLE_LEVEL_OUTPUT_8_SHFT                                                 0x0

#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_EN_ADDR                                                                   (QM_REG_BASE      + 0x000011e0)
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_EN_RMSK                                                                          0x1
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_EN_IN          \
        in_dword_masked(HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_EN_ADDR, HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_EN_RMSK)
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_EN_INM(m)      \
        in_dword_masked(HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_EN_ADDR, m)
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_EN_OUT(v)      \
        out_dword(HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_EN_ADDR,v)
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_EN_ADDR,m,v,HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_EN_IN)
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_EN_THROTTLE_LEVEL_EN_BMSK                                                        0x1
#define HWIO_QM_CLNT_0_THROTTLE_LEVEL_OUTPUT_EN_THROTTLE_LEVEL_EN_SHFT                                                        0x0

#define HWIO_QM_CLNT_n_THROTTLE_LEVEL_OUTPUT_EN_ADDR(n)                                                                (QM_REG_BASE      + 0x000011e0 + 0x4 * (n))
#define HWIO_QM_CLNT_n_THROTTLE_LEVEL_OUTPUT_EN_RMSK                                                                          0x1
#define HWIO_QM_CLNT_n_THROTTLE_LEVEL_OUTPUT_EN_MAXn                                                                           10
#define HWIO_QM_CLNT_n_THROTTLE_LEVEL_OUTPUT_EN_INI(n)        \
        in_dword_masked(HWIO_QM_CLNT_n_THROTTLE_LEVEL_OUTPUT_EN_ADDR(n), HWIO_QM_CLNT_n_THROTTLE_LEVEL_OUTPUT_EN_RMSK)
#define HWIO_QM_CLNT_n_THROTTLE_LEVEL_OUTPUT_EN_INMI(n,mask)    \
        in_dword_masked(HWIO_QM_CLNT_n_THROTTLE_LEVEL_OUTPUT_EN_ADDR(n), mask)
#define HWIO_QM_CLNT_n_THROTTLE_LEVEL_OUTPUT_EN_OUTI(n,val)    \
        out_dword(HWIO_QM_CLNT_n_THROTTLE_LEVEL_OUTPUT_EN_ADDR(n),val)
#define HWIO_QM_CLNT_n_THROTTLE_LEVEL_OUTPUT_EN_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QM_CLNT_n_THROTTLE_LEVEL_OUTPUT_EN_ADDR(n),mask,val,HWIO_QM_CLNT_n_THROTTLE_LEVEL_OUTPUT_EN_INI(n))
#define HWIO_QM_CLNT_n_THROTTLE_LEVEL_OUTPUT_EN_THROTTLE_LEVEL_EN_BMSK                                                        0x1
#define HWIO_QM_CLNT_n_THROTTLE_LEVEL_OUTPUT_EN_THROTTLE_LEVEL_EN_SHFT                                                        0x0

#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_EN_ADDR                                                                   (QM_REG_BASE      + 0x000011e4)
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_EN_RMSK                                                                          0x1
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_EN_IN          \
        in_dword_masked(HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_EN_ADDR, HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_EN_RMSK)
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_EN_INM(m)      \
        in_dword_masked(HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_EN_ADDR, m)
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_EN_OUT(v)      \
        out_dword(HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_EN_ADDR,v)
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_EN_ADDR,m,v,HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_EN_IN)
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_EN_THROTTLE_LEVEL_EN_BMSK                                                        0x1
#define HWIO_QM_CLNT_1_THROTTLE_LEVEL_OUTPUT_EN_THROTTLE_LEVEL_EN_SHFT                                                        0x0

#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_EN_ADDR                                                                   (QM_REG_BASE      + 0x000011e8)
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_EN_RMSK                                                                          0x1
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_EN_IN          \
        in_dword_masked(HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_EN_ADDR, HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_EN_RMSK)
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_EN_INM(m)      \
        in_dword_masked(HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_EN_ADDR, m)
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_EN_OUT(v)      \
        out_dword(HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_EN_ADDR,v)
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_EN_ADDR,m,v,HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_EN_IN)
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_EN_THROTTLE_LEVEL_EN_BMSK                                                        0x1
#define HWIO_QM_CLNT_2_THROTTLE_LEVEL_OUTPUT_EN_THROTTLE_LEVEL_EN_SHFT                                                        0x0

#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_EN_ADDR                                                                   (QM_REG_BASE      + 0x000011ec)
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_EN_RMSK                                                                          0x1
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_EN_IN          \
        in_dword_masked(HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_EN_ADDR, HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_EN_RMSK)
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_EN_INM(m)      \
        in_dword_masked(HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_EN_ADDR, m)
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_EN_OUT(v)      \
        out_dword(HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_EN_ADDR,v)
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_EN_ADDR,m,v,HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_EN_IN)
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_EN_THROTTLE_LEVEL_EN_BMSK                                                        0x1
#define HWIO_QM_CLNT_3_THROTTLE_LEVEL_OUTPUT_EN_THROTTLE_LEVEL_EN_SHFT                                                        0x0

#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_EN_ADDR                                                                   (QM_REG_BASE      + 0x000011f0)
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_EN_RMSK                                                                          0x1
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_EN_IN          \
        in_dword_masked(HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_EN_ADDR, HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_EN_RMSK)
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_EN_INM(m)      \
        in_dword_masked(HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_EN_ADDR, m)
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_EN_OUT(v)      \
        out_dword(HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_EN_ADDR,v)
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_EN_ADDR,m,v,HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_EN_IN)
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_EN_THROTTLE_LEVEL_EN_BMSK                                                        0x1
#define HWIO_QM_CLNT_4_THROTTLE_LEVEL_OUTPUT_EN_THROTTLE_LEVEL_EN_SHFT                                                        0x0

#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_EN_ADDR                                                                   (QM_REG_BASE      + 0x000011f4)
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_EN_RMSK                                                                          0x1
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_EN_IN          \
        in_dword_masked(HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_EN_ADDR, HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_EN_RMSK)
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_EN_INM(m)      \
        in_dword_masked(HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_EN_ADDR, m)
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_EN_OUT(v)      \
        out_dword(HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_EN_ADDR,v)
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_EN_ADDR,m,v,HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_EN_IN)
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_EN_THROTTLE_LEVEL_EN_BMSK                                                        0x1
#define HWIO_QM_CLNT_5_THROTTLE_LEVEL_OUTPUT_EN_THROTTLE_LEVEL_EN_SHFT                                                        0x0

#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_EN_ADDR                                                                   (QM_REG_BASE      + 0x000011f8)
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_EN_RMSK                                                                          0x1
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_EN_IN          \
        in_dword_masked(HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_EN_ADDR, HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_EN_RMSK)
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_EN_INM(m)      \
        in_dword_masked(HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_EN_ADDR, m)
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_EN_OUT(v)      \
        out_dword(HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_EN_ADDR,v)
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_EN_ADDR,m,v,HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_EN_IN)
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_EN_THROTTLE_LEVEL_EN_BMSK                                                        0x1
#define HWIO_QM_CLNT_6_THROTTLE_LEVEL_OUTPUT_EN_THROTTLE_LEVEL_EN_SHFT                                                        0x0

#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_EN_ADDR                                                                   (QM_REG_BASE      + 0x000011fc)
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_EN_RMSK                                                                          0x1
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_EN_IN          \
        in_dword_masked(HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_EN_ADDR, HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_EN_RMSK)
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_EN_INM(m)      \
        in_dword_masked(HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_EN_ADDR, m)
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_EN_OUT(v)      \
        out_dword(HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_EN_ADDR,v)
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_EN_ADDR,m,v,HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_EN_IN)
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_EN_THROTTLE_LEVEL_EN_BMSK                                                        0x1
#define HWIO_QM_CLNT_7_THROTTLE_LEVEL_OUTPUT_EN_THROTTLE_LEVEL_EN_SHFT                                                        0x0

#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_EN_ADDR                                                                   (QM_REG_BASE      + 0x00001200)
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_EN_RMSK                                                                          0x1
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_EN_IN          \
        in_dword_masked(HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_EN_ADDR, HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_EN_RMSK)
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_EN_INM(m)      \
        in_dword_masked(HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_EN_ADDR, m)
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_EN_OUT(v)      \
        out_dword(HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_EN_ADDR,v)
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_EN_ADDR,m,v,HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_EN_IN)
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_EN_THROTTLE_LEVEL_EN_BMSK                                                        0x1
#define HWIO_QM_CLNT_8_THROTTLE_LEVEL_OUTPUT_EN_THROTTLE_LEVEL_EN_SHFT                                                        0x0

#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_EN_ADDR                                                                   (QM_REG_BASE      + 0x00001204)
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_EN_RMSK                                                                          0x1
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_EN_IN          \
        in_dword_masked(HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_EN_ADDR, HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_EN_RMSK)
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_EN_INM(m)      \
        in_dword_masked(HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_EN_ADDR, m)
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_EN_OUT(v)      \
        out_dword(HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_EN_ADDR,v)
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_EN_ADDR,m,v,HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_EN_IN)
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_EN_THROTTLE_LEVEL_EN_BMSK                                                        0x1
#define HWIO_QM_CLNT_9_THROTTLE_LEVEL_OUTPUT_EN_THROTTLE_LEVEL_EN_SHFT                                                        0x0

#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_EN_ADDR                                                                  (QM_REG_BASE      + 0x00001208)
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_EN_RMSK                                                                         0x1
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_EN_IN          \
        in_dword_masked(HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_EN_ADDR, HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_EN_RMSK)
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_EN_INM(m)      \
        in_dword_masked(HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_EN_ADDR, m)
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_EN_OUT(v)      \
        out_dword(HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_EN_ADDR,v)
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_EN_ADDR,m,v,HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_EN_IN)
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_EN_THROTTLE_LEVEL_EN_BMSK                                                       0x1
#define HWIO_QM_CLNT_10_THROTTLE_LEVEL_OUTPUT_EN_THROTTLE_LEVEL_EN_SHFT                                                       0x0

#define HWIO_QM_DSP_HPM_THROTTLE_LEVEL_OUTPUT_ADDR                                                                     (QM_REG_BASE      + 0x00001210)
#define HWIO_QM_DSP_HPM_THROTTLE_LEVEL_OUTPUT_RMSK                                                                            0x7
#define HWIO_QM_DSP_HPM_THROTTLE_LEVEL_OUTPUT_IN          \
        in_dword_masked(HWIO_QM_DSP_HPM_THROTTLE_LEVEL_OUTPUT_ADDR, HWIO_QM_DSP_HPM_THROTTLE_LEVEL_OUTPUT_RMSK)
#define HWIO_QM_DSP_HPM_THROTTLE_LEVEL_OUTPUT_INM(m)      \
        in_dword_masked(HWIO_QM_DSP_HPM_THROTTLE_LEVEL_OUTPUT_ADDR, m)
#define HWIO_QM_DSP_HPM_THROTTLE_LEVEL_OUTPUT_OUT(v)      \
        out_dword(HWIO_QM_DSP_HPM_THROTTLE_LEVEL_OUTPUT_ADDR,v)
#define HWIO_QM_DSP_HPM_THROTTLE_LEVEL_OUTPUT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_DSP_HPM_THROTTLE_LEVEL_OUTPUT_ADDR,m,v,HWIO_QM_DSP_HPM_THROTTLE_LEVEL_OUTPUT_IN)
#define HWIO_QM_DSP_HPM_THROTTLE_LEVEL_OUTPUT_DSP_HPM_THROTTLE_LEVEL_OUTPUT_BMSK                                              0x7
#define HWIO_QM_DSP_HPM_THROTTLE_LEVEL_OUTPUT_DSP_HPM_THROTTLE_LEVEL_OUTPUT_SHFT                                              0x0

#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_ADDR                                                                          (QM_REG_BASE      + 0x00001214)
#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_RMSK                                                                            0xffffff
#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_IN          \
        in_dword_masked(HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_ADDR, HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_RMSK)
#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_INM(m)      \
        in_dword_masked(HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_ADDR, m)
#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_OUT(v)      \
        out_dword(HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_ADDR,v)
#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_ADDR,m,v,HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_IN)
#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_SYSTEM_DANGER_OUTPUT_11_BMSK                                                    0xc00000
#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_SYSTEM_DANGER_OUTPUT_11_SHFT                                                        0x16
#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_SYSTEM_DANGER_OUTPUT_10_BMSK                                                    0x300000
#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_SYSTEM_DANGER_OUTPUT_10_SHFT                                                        0x14
#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_SYSTEM_DANGER_OUTPUT_9_BMSK                                                      0xc0000
#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_SYSTEM_DANGER_OUTPUT_9_SHFT                                                         0x12
#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_SYSTEM_DANGER_OUTPUT_8_BMSK                                                      0x30000
#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_SYSTEM_DANGER_OUTPUT_8_SHFT                                                         0x10
#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_SYSTEM_DANGER_OUTPUT_7_BMSK                                                       0xc000
#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_SYSTEM_DANGER_OUTPUT_7_SHFT                                                          0xe
#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_SYSTEM_DANGER_OUTPUT_6_BMSK                                                       0x3000
#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_SYSTEM_DANGER_OUTPUT_6_SHFT                                                          0xc
#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_SYSTEM_DANGER_OUTPUT_5_BMSK                                                        0xc00
#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_SYSTEM_DANGER_OUTPUT_5_SHFT                                                          0xa
#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_SYSTEM_DANGER_OUTPUT_4_BMSK                                                        0x300
#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_SYSTEM_DANGER_OUTPUT_4_SHFT                                                          0x8
#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_SYSTEM_DANGER_OUTPUT_3_BMSK                                                         0xc0
#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_SYSTEM_DANGER_OUTPUT_3_SHFT                                                          0x6
#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_SYSTEM_DANGER_OUTPUT_2_BMSK                                                         0x30
#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_SYSTEM_DANGER_OUTPUT_2_SHFT                                                          0x4
#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_SYSTEM_DANGER_OUTPUT_1_BMSK                                                          0xc
#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_SYSTEM_DANGER_OUTPUT_1_SHFT                                                          0x2
#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_SYSTEM_DANGER_OUTPUT_0_BMSK                                                          0x3
#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_SYSTEM_DANGER_OUTPUT_0_SHFT                                                          0x0

#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_EN_ADDR                                                                       (QM_REG_BASE      + 0x00001218)
#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_EN_RMSK                                                                              0x1
#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_EN_IN          \
        in_dword_masked(HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_EN_ADDR, HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_EN_RMSK)
#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_EN_INM(m)      \
        in_dword_masked(HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_EN_ADDR, m)
#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_EN_OUT(v)      \
        out_dword(HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_EN_ADDR,v)
#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_EN_ADDR,m,v,HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_EN_IN)
#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_EN_SYSTEM_DANGER_OUTPUT_EN_BMSK                                                      0x1
#define HWIO_QM_DSP_SYSTEM_DANGER_OUTPUT_EN_SYSTEM_DANGER_OUTPUT_EN_SHFT                                                      0x0

#define HWIO_QM_DSP_PRIORITY_MODE_SEL_ADDR                                                                             (QM_REG_BASE      + 0x0000121c)
#define HWIO_QM_DSP_PRIORITY_MODE_SEL_RMSK                                                                                0x70007
#define HWIO_QM_DSP_PRIORITY_MODE_SEL_IN          \
        in_dword_masked(HWIO_QM_DSP_PRIORITY_MODE_SEL_ADDR, HWIO_QM_DSP_PRIORITY_MODE_SEL_RMSK)
#define HWIO_QM_DSP_PRIORITY_MODE_SEL_INM(m)      \
        in_dword_masked(HWIO_QM_DSP_PRIORITY_MODE_SEL_ADDR, m)
#define HWIO_QM_DSP_PRIORITY_MODE_SEL_OUT(v)      \
        out_dword(HWIO_QM_DSP_PRIORITY_MODE_SEL_ADDR,v)
#define HWIO_QM_DSP_PRIORITY_MODE_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_DSP_PRIORITY_MODE_SEL_ADDR,m,v,HWIO_QM_DSP_PRIORITY_MODE_SEL_IN)
#define HWIO_QM_DSP_PRIORITY_MODE_SEL_DSP_SYSTEM_DANGER_PRIORITY_MODE_FLIP_BMSK                                           0x40000
#define HWIO_QM_DSP_PRIORITY_MODE_SEL_DSP_SYSTEM_DANGER_PRIORITY_MODE_FLIP_SHFT                                              0x12
#define HWIO_QM_DSP_PRIORITY_MODE_SEL_DSP_SYSTEM_DANGER_PRIORITY_MODE_SEL_BMSK                                            0x30000
#define HWIO_QM_DSP_PRIORITY_MODE_SEL_DSP_SYSTEM_DANGER_PRIORITY_MODE_SEL_SHFT                                               0x10
#define HWIO_QM_DSP_PRIORITY_MODE_SEL_DSP_PRIORITY_MODE_FLIP_BMSK                                                             0x4
#define HWIO_QM_DSP_PRIORITY_MODE_SEL_DSP_PRIORITY_MODE_FLIP_SHFT                                                             0x2
#define HWIO_QM_DSP_PRIORITY_MODE_SEL_DSP_PRIORITY_MODE_SEL_BMSK                                                              0x3
#define HWIO_QM_DSP_PRIORITY_MODE_SEL_DSP_PRIORITY_MODE_SEL_SHFT                                                              0x0

#define HWIO_QM_INTERRUPT_MASK_ADDR                                                                                    (QM_REG_BASE      + 0x00001220)
#define HWIO_QM_INTERRUPT_MASK_RMSK                                                                                          0x1f
#define HWIO_QM_INTERRUPT_MASK_IN          \
        in_dword_masked(HWIO_QM_INTERRUPT_MASK_ADDR, HWIO_QM_INTERRUPT_MASK_RMSK)
#define HWIO_QM_INTERRUPT_MASK_INM(m)      \
        in_dword_masked(HWIO_QM_INTERRUPT_MASK_ADDR, m)
#define HWIO_QM_INTERRUPT_MASK_OUT(v)      \
        out_dword(HWIO_QM_INTERRUPT_MASK_ADDR,v)
#define HWIO_QM_INTERRUPT_MASK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_INTERRUPT_MASK_ADDR,m,v,HWIO_QM_INTERRUPT_MASK_IN)
#define HWIO_QM_INTERRUPT_MASK_TPDM_BC_STATISTICS_DURATION_CNTR_CAPTURE_INT_MASK_BMSK                                        0x10
#define HWIO_QM_INTERRUPT_MASK_TPDM_BC_STATISTICS_DURATION_CNTR_CAPTURE_INT_MASK_SHFT                                         0x4
#define HWIO_QM_INTERRUPT_MASK_TPDM_BC_OFSAT_INT_MASK_BMSK                                                                    0x8
#define HWIO_QM_INTERRUPT_MASK_TPDM_BC_OFSAT_INT_MASK_SHFT                                                                    0x3
#define HWIO_QM_INTERRUPT_MASK_POST_STALL_TIMEOUT_INT_MASK_BMSK                                                               0x4
#define HWIO_QM_INTERRUPT_MASK_POST_STALL_TIMEOUT_INT_MASK_SHFT                                                               0x2
#define HWIO_QM_INTERRUPT_MASK_PRE_STALL_TIMEOUT_INT_MASK_BMSK                                                                0x2
#define HWIO_QM_INTERRUPT_MASK_PRE_STALL_TIMEOUT_INT_MASK_SHFT                                                                0x1
#define HWIO_QM_INTERRUPT_MASK_STATISTICS_DURATION_CNTR_SATURATE_INT_MASK_BMSK                                                0x1
#define HWIO_QM_INTERRUPT_MASK_STATISTICS_DURATION_CNTR_SATURATE_INT_MASK_SHFT                                                0x0

#define HWIO_QM_INTERRUPT_CLR_ADDR                                                                                     (QM_REG_BASE      + 0x00001224)
#define HWIO_QM_INTERRUPT_CLR_RMSK                                                                                           0x17
#define HWIO_QM_INTERRUPT_CLR_OUT(v)      \
        out_dword(HWIO_QM_INTERRUPT_CLR_ADDR,v)
#define HWIO_QM_INTERRUPT_CLR_TPDM_BC_STATISTICS_DURATION_CNTR_CAPTURE_INT_CLR_BMSK                                          0x10
#define HWIO_QM_INTERRUPT_CLR_TPDM_BC_STATISTICS_DURATION_CNTR_CAPTURE_INT_CLR_SHFT                                           0x4
#define HWIO_QM_INTERRUPT_CLR_POST_STALL_TIMEOUT_INT_CLR_BMSK                                                                 0x4
#define HWIO_QM_INTERRUPT_CLR_POST_STALL_TIMEOUT_INT_CLR_SHFT                                                                 0x2
#define HWIO_QM_INTERRUPT_CLR_PRE_STALL_TIMEOUT_INT_CLR_BMSK                                                                  0x2
#define HWIO_QM_INTERRUPT_CLR_PRE_STALL_TIMEOUT_INT_CLR_SHFT                                                                  0x1
#define HWIO_QM_INTERRUPT_CLR_STATISTICS_DURATION_CNTR_SATURATE_INT_CLR_BMSK                                                  0x1
#define HWIO_QM_INTERRUPT_CLR_STATISTICS_DURATION_CNTR_SATURATE_INT_CLR_SHFT                                                  0x0

#define HWIO_QM_INTERRUPT_STATUS_ADDR                                                                                  (QM_REG_BASE      + 0x00001228)
#define HWIO_QM_INTERRUPT_STATUS_RMSK                                                                                        0x1f
#define HWIO_QM_INTERRUPT_STATUS_IN          \
        in_dword_masked(HWIO_QM_INTERRUPT_STATUS_ADDR, HWIO_QM_INTERRUPT_STATUS_RMSK)
#define HWIO_QM_INTERRUPT_STATUS_INM(m)      \
        in_dword_masked(HWIO_QM_INTERRUPT_STATUS_ADDR, m)
#define HWIO_QM_INTERRUPT_STATUS_TPDM_BC_STATISTICS_DURATION_CNTR_CAPTURE_INT_STATUS_BMSK                                    0x10
#define HWIO_QM_INTERRUPT_STATUS_TPDM_BC_STATISTICS_DURATION_CNTR_CAPTURE_INT_STATUS_SHFT                                     0x4
#define HWIO_QM_INTERRUPT_STATUS_TPDM_BC_OFSAT_INT_STATUS_BMSK                                                                0x8
#define HWIO_QM_INTERRUPT_STATUS_TPDM_BC_OFSAT_INT_STATUS_SHFT                                                                0x3
#define HWIO_QM_INTERRUPT_STATUS_POST_STALL_TIMEOUT_INT_STATUS_BMSK                                                           0x4
#define HWIO_QM_INTERRUPT_STATUS_POST_STALL_TIMEOUT_INT_STATUS_SHFT                                                           0x2
#define HWIO_QM_INTERRUPT_STATUS_PRE_STALL_TIMEOUT_INT_STATUS_BMSK                                                            0x2
#define HWIO_QM_INTERRUPT_STATUS_PRE_STALL_TIMEOUT_INT_STATUS_SHFT                                                            0x1
#define HWIO_QM_INTERRUPT_STATUS_STATISTICS_DURATION_CNTR_SATURATE_INT_STATUS_BMSK                                            0x1
#define HWIO_QM_INTERRUPT_STATUS_STATISTICS_DURATION_CNTR_SATURATE_INT_STATUS_SHFT                                            0x0

#define HWIO_QM_SPARE_REGS_ADDR                                                                                        (QM_REG_BASE      + 0x00001300)
#define HWIO_QM_SPARE_REGS_RMSK                                                                                        0xffffffff
#define HWIO_QM_SPARE_REGS_IN          \
        in_dword_masked(HWIO_QM_SPARE_REGS_ADDR, HWIO_QM_SPARE_REGS_RMSK)
#define HWIO_QM_SPARE_REGS_INM(m)      \
        in_dword_masked(HWIO_QM_SPARE_REGS_ADDR, m)
#define HWIO_QM_SPARE_REGS_OUT(v)      \
        out_dword(HWIO_QM_SPARE_REGS_ADDR,v)
#define HWIO_QM_SPARE_REGS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_SPARE_REGS_ADDR,m,v,HWIO_QM_SPARE_REGS_IN)
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_31_BMSK                                                                       0x80000000
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_31_SHFT                                                                             0x1f
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_30_BMSK                                                                       0x40000000
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_30_SHFT                                                                             0x1e
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_29_BMSK                                                                       0x20000000
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_29_SHFT                                                                             0x1d
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_28_BMSK                                                                       0x10000000
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_28_SHFT                                                                             0x1c
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_27_BMSK                                                                        0x8000000
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_27_SHFT                                                                             0x1b
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_26_BMSK                                                                        0x4000000
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_26_SHFT                                                                             0x1a
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_25_BMSK                                                                        0x2000000
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_25_SHFT                                                                             0x19
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_24_BMSK                                                                        0x1000000
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_24_SHFT                                                                             0x18
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_23_BMSK                                                                         0x800000
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_23_SHFT                                                                             0x17
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_22_BMSK                                                                         0x400000
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_22_SHFT                                                                             0x16
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_21_BMSK                                                                         0x200000
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_21_SHFT                                                                             0x15
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_20_BMSK                                                                         0x100000
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_20_SHFT                                                                             0x14
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_19_BMSK                                                                          0x80000
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_19_SHFT                                                                             0x13
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_18_BMSK                                                                          0x40000
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_18_SHFT                                                                             0x12
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_17_BMSK                                                                          0x20000
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_17_SHFT                                                                             0x11
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_16_BMSK                                                                          0x10000
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_16_SHFT                                                                             0x10
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_15_BMSK                                                                           0x8000
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_15_SHFT                                                                              0xf
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_14_BMSK                                                                           0x4000
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_14_SHFT                                                                              0xe
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_13_BMSK                                                                           0x2000
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_13_SHFT                                                                              0xd
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_12_BMSK                                                                           0x1000
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_12_SHFT                                                                              0xc
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_11_BMSK                                                                            0x800
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_11_SHFT                                                                              0xb
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_10_BMSK                                                                            0x400
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_10_SHFT                                                                              0xa
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_9_BMSK                                                                             0x200
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_9_SHFT                                                                               0x9
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_8_BMSK                                                                             0x100
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_8_SHFT                                                                               0x8
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_7_BMSK                                                                              0x80
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_7_SHFT                                                                               0x7
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_6_BMSK                                                                              0x40
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_6_SHFT                                                                               0x6
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_5_BMSK                                                                              0x20
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_5_SHFT                                                                               0x5
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_4_BMSK                                                                              0x10
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_4_SHFT                                                                               0x4
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_3_BMSK                                                                               0x8
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_3_SHFT                                                                               0x3
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_2_BMSK                                                                               0x4
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_2_SHFT                                                                               0x2
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_1_BMSK                                                                               0x2
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_1_SHFT                                                                               0x1
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_0_BMSK                                                                               0x1
#define HWIO_QM_SPARE_REGS_SPARE_REG_BIT_0_SHFT                                                                               0x0

#define HWIO_QM_THROTTLE_LEVEL_THRESHOLD_00_ADDR                                                                       (QM_REG_BASE      + 0x00001320)
#define HWIO_QM_THROTTLE_LEVEL_THRESHOLD_00_RMSK                                                                       0x3fffffff
#define HWIO_QM_THROTTLE_LEVEL_THRESHOLD_00_IN          \
        in_dword_masked(HWIO_QM_THROTTLE_LEVEL_THRESHOLD_00_ADDR, HWIO_QM_THROTTLE_LEVEL_THRESHOLD_00_RMSK)
#define HWIO_QM_THROTTLE_LEVEL_THRESHOLD_00_INM(m)      \
        in_dword_masked(HWIO_QM_THROTTLE_LEVEL_THRESHOLD_00_ADDR, m)
#define HWIO_QM_THROTTLE_LEVEL_THRESHOLD_00_OUT(v)      \
        out_dword(HWIO_QM_THROTTLE_LEVEL_THRESHOLD_00_ADDR,v)
#define HWIO_QM_THROTTLE_LEVEL_THRESHOLD_00_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_THROTTLE_LEVEL_THRESHOLD_00_ADDR,m,v,HWIO_QM_THROTTLE_LEVEL_THRESHOLD_00_IN)
#define HWIO_QM_THROTTLE_LEVEL_THRESHOLD_00_CLNT_9_THROTTLE_LEVEL_THR_BMSK                                             0x38000000
#define HWIO_QM_THROTTLE_LEVEL_THRESHOLD_00_CLNT_9_THROTTLE_LEVEL_THR_SHFT                                                   0x1b
#define HWIO_QM_THROTTLE_LEVEL_THRESHOLD_00_CLNT_8_THROTTLE_LEVEL_THR_BMSK                                              0x7000000
#define HWIO_QM_THROTTLE_LEVEL_THRESHOLD_00_CLNT_8_THROTTLE_LEVEL_THR_SHFT                                                   0x18
#define HWIO_QM_THROTTLE_LEVEL_THRESHOLD_00_CLNT_7_THROTTLE_LEVEL_THR_BMSK                                               0xe00000
#define HWIO_QM_THROTTLE_LEVEL_THRESHOLD_00_CLNT_7_THROTTLE_LEVEL_THR_SHFT                                                   0x15
#define HWIO_QM_THROTTLE_LEVEL_THRESHOLD_00_CLNT_6_THROTTLE_LEVEL_THR_BMSK                                               0x1c0000
#define HWIO_QM_THROTTLE_LEVEL_THRESHOLD_00_CLNT_6_THROTTLE_LEVEL_THR_SHFT                                                   0x12
#define HWIO_QM_THROTTLE_LEVEL_THRESHOLD_00_CLNT_5_THROTTLE_LEVEL_THR_BMSK                                                0x38000
#define HWIO_QM_THROTTLE_LEVEL_THRESHOLD_00_CLNT_5_THROTTLE_LEVEL_THR_SHFT                                                    0xf
#define HWIO_QM_THROTTLE_LEVEL_THRESHOLD_00_CLNT_4_THROTTLE_LEVEL_THR_BMSK                                                 0x7000
#define HWIO_QM_THROTTLE_LEVEL_THRESHOLD_00_CLNT_4_THROTTLE_LEVEL_THR_SHFT                                                    0xc
#define HWIO_QM_THROTTLE_LEVEL_THRESHOLD_00_CLNT_3_THROTTLE_LEVEL_THR_BMSK                                                  0xe00
#define HWIO_QM_THROTTLE_LEVEL_THRESHOLD_00_CLNT_3_THROTTLE_LEVEL_THR_SHFT                                                    0x9
#define HWIO_QM_THROTTLE_LEVEL_THRESHOLD_00_CLNT_2_THROTTLE_LEVEL_THR_BMSK                                                  0x1c0
#define HWIO_QM_THROTTLE_LEVEL_THRESHOLD_00_CLNT_2_THROTTLE_LEVEL_THR_SHFT                                                    0x6
#define HWIO_QM_THROTTLE_LEVEL_THRESHOLD_00_CLNT_1_THROTTLE_LEVEL_THR_BMSK                                                   0x38
#define HWIO_QM_THROTTLE_LEVEL_THRESHOLD_00_CLNT_1_THROTTLE_LEVEL_THR_SHFT                                                    0x3
#define HWIO_QM_THROTTLE_LEVEL_THRESHOLD_00_CLNT_0_THROTTLE_LEVEL_THR_BMSK                                                    0x7
#define HWIO_QM_THROTTLE_LEVEL_THRESHOLD_00_CLNT_0_THROTTLE_LEVEL_THR_SHFT                                                    0x0

#define HWIO_QM_THROTTLE_LEVEL_THRESHOLD_01_ADDR                                                                       (QM_REG_BASE      + 0x00001324)
#define HWIO_QM_THROTTLE_LEVEL_THRESHOLD_01_RMSK                                                                              0x7
#define HWIO_QM_THROTTLE_LEVEL_THRESHOLD_01_IN          \
        in_dword_masked(HWIO_QM_THROTTLE_LEVEL_THRESHOLD_01_ADDR, HWIO_QM_THROTTLE_LEVEL_THRESHOLD_01_RMSK)
#define HWIO_QM_THROTTLE_LEVEL_THRESHOLD_01_INM(m)      \
        in_dword_masked(HWIO_QM_THROTTLE_LEVEL_THRESHOLD_01_ADDR, m)
#define HWIO_QM_THROTTLE_LEVEL_THRESHOLD_01_OUT(v)      \
        out_dword(HWIO_QM_THROTTLE_LEVEL_THRESHOLD_01_ADDR,v)
#define HWIO_QM_THROTTLE_LEVEL_THRESHOLD_01_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_THROTTLE_LEVEL_THRESHOLD_01_ADDR,m,v,HWIO_QM_THROTTLE_LEVEL_THRESHOLD_01_IN)
#define HWIO_QM_THROTTLE_LEVEL_THRESHOLD_01_CLNT_10_THROTTLE_LEVEL_THR_BMSK                                                   0x7
#define HWIO_QM_THROTTLE_LEVEL_THRESHOLD_01_CLNT_10_THROTTLE_LEVEL_THR_SHFT                                                   0x0

#define HWIO_QM_THROTTLE_LEVEL_LEGACY_SELECT_ADDR                                                                      (QM_REG_BASE      + 0x00001740)
#define HWIO_QM_THROTTLE_LEVEL_LEGACY_SELECT_RMSK                                                                             0x1
#define HWIO_QM_THROTTLE_LEVEL_LEGACY_SELECT_IN          \
        in_dword_masked(HWIO_QM_THROTTLE_LEVEL_LEGACY_SELECT_ADDR, HWIO_QM_THROTTLE_LEVEL_LEGACY_SELECT_RMSK)
#define HWIO_QM_THROTTLE_LEVEL_LEGACY_SELECT_INM(m)      \
        in_dword_masked(HWIO_QM_THROTTLE_LEVEL_LEGACY_SELECT_ADDR, m)
#define HWIO_QM_THROTTLE_LEVEL_LEGACY_SELECT_OUT(v)      \
        out_dword(HWIO_QM_THROTTLE_LEVEL_LEGACY_SELECT_ADDR,v)
#define HWIO_QM_THROTTLE_LEVEL_LEGACY_SELECT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_THROTTLE_LEVEL_LEGACY_SELECT_ADDR,m,v,HWIO_QM_THROTTLE_LEVEL_LEGACY_SELECT_IN)
#define HWIO_QM_THROTTLE_LEVEL_LEGACY_SELECT_THROTTLE_LEVEL_LEGACY_SELECT_BMSK                                                0x1
#define HWIO_QM_THROTTLE_LEVEL_LEGACY_SELECT_THROTTLE_LEVEL_LEGACY_SELECT_SHFT                                                0x0

#define HWIO_QM_THROTTLE_LEVEL_SU_CFG_ADDR                                                                             (QM_REG_BASE      + 0x00001744)
#define HWIO_QM_THROTTLE_LEVEL_SU_CFG_RMSK                                                                                   0x7f
#define HWIO_QM_THROTTLE_LEVEL_SU_CFG_IN          \
        in_dword_masked(HWIO_QM_THROTTLE_LEVEL_SU_CFG_ADDR, HWIO_QM_THROTTLE_LEVEL_SU_CFG_RMSK)
#define HWIO_QM_THROTTLE_LEVEL_SU_CFG_INM(m)      \
        in_dword_masked(HWIO_QM_THROTTLE_LEVEL_SU_CFG_ADDR, m)
#define HWIO_QM_THROTTLE_LEVEL_SU_CFG_OUT(v)      \
        out_dword(HWIO_QM_THROTTLE_LEVEL_SU_CFG_ADDR,v)
#define HWIO_QM_THROTTLE_LEVEL_SU_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_THROTTLE_LEVEL_SU_CFG_ADDR,m,v,HWIO_QM_THROTTLE_LEVEL_SU_CFG_IN)
#define HWIO_QM_THROTTLE_LEVEL_SU_CFG_QOS_ASSIST_REQ_MODE_7_BMSK                                                             0x40
#define HWIO_QM_THROTTLE_LEVEL_SU_CFG_QOS_ASSIST_REQ_MODE_7_SHFT                                                              0x6
#define HWIO_QM_THROTTLE_LEVEL_SU_CFG_QOS_ASSIST_REQ_MODE_6_BMSK                                                             0x20
#define HWIO_QM_THROTTLE_LEVEL_SU_CFG_QOS_ASSIST_REQ_MODE_6_SHFT                                                              0x5
#define HWIO_QM_THROTTLE_LEVEL_SU_CFG_QOS_ASSIST_REQ_MODE_5_BMSK                                                             0x10
#define HWIO_QM_THROTTLE_LEVEL_SU_CFG_QOS_ASSIST_REQ_MODE_5_SHFT                                                              0x4
#define HWIO_QM_THROTTLE_LEVEL_SU_CFG_QOS_ASSIST_REQ_MODE_4_BMSK                                                              0x8
#define HWIO_QM_THROTTLE_LEVEL_SU_CFG_QOS_ASSIST_REQ_MODE_4_SHFT                                                              0x3
#define HWIO_QM_THROTTLE_LEVEL_SU_CFG_QOS_ASSIST_REQ_MODE_3_BMSK                                                              0x4
#define HWIO_QM_THROTTLE_LEVEL_SU_CFG_QOS_ASSIST_REQ_MODE_3_SHFT                                                              0x2
#define HWIO_QM_THROTTLE_LEVEL_SU_CFG_QOS_ASSIST_REQ_MODE_2_BMSK                                                              0x2
#define HWIO_QM_THROTTLE_LEVEL_SU_CFG_QOS_ASSIST_REQ_MODE_2_SHFT                                                              0x1
#define HWIO_QM_THROTTLE_LEVEL_SU_CFG_QOS_ASSIST_REQ_MODE_1_BMSK                                                              0x1
#define HWIO_QM_THROTTLE_LEVEL_SU_CFG_QOS_ASSIST_REQ_MODE_1_SHFT                                                              0x0

#define HWIO_QOS_FREQ_BAND_BNDRY_n_ADDR(n)                                                                             (QM_REG_BASE      + 0x00001748 + 0x4 * (n))
#define HWIO_QOS_FREQ_BAND_BNDRY_n_RMSK                                                                                   0x1ffff
#define HWIO_QOS_FREQ_BAND_BNDRY_n_MAXn                                                                                         2
#define HWIO_QOS_FREQ_BAND_BNDRY_n_INI(n)        \
        in_dword_masked(HWIO_QOS_FREQ_BAND_BNDRY_n_ADDR(n), HWIO_QOS_FREQ_BAND_BNDRY_n_RMSK)
#define HWIO_QOS_FREQ_BAND_BNDRY_n_INMI(n,mask)    \
        in_dword_masked(HWIO_QOS_FREQ_BAND_BNDRY_n_ADDR(n), mask)
#define HWIO_QOS_FREQ_BAND_BNDRY_n_OUTI(n,val)    \
        out_dword(HWIO_QOS_FREQ_BAND_BNDRY_n_ADDR(n),val)
#define HWIO_QOS_FREQ_BAND_BNDRY_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QOS_FREQ_BAND_BNDRY_n_ADDR(n),mask,val,HWIO_QOS_FREQ_BAND_BNDRY_n_INI(n))
#define HWIO_QOS_FREQ_BAND_BNDRY_n_FREQ_BAND_BNDRY_BMSK                                                                   0x1ffff
#define HWIO_QOS_FREQ_BAND_BNDRY_n_FREQ_BAND_BNDRY_SHFT                                                                       0x0

#define HWIO_QM_PERIOD_BUS_CFG_ADDR                                                                                    (QM_REG_BASE      + 0x00001754)
#define HWIO_QM_PERIOD_BUS_CFG_RMSK                                                                                    0xc001ffff
#define HWIO_QM_PERIOD_BUS_CFG_IN          \
        in_dword_masked(HWIO_QM_PERIOD_BUS_CFG_ADDR, HWIO_QM_PERIOD_BUS_CFG_RMSK)
#define HWIO_QM_PERIOD_BUS_CFG_INM(m)      \
        in_dword_masked(HWIO_QM_PERIOD_BUS_CFG_ADDR, m)
#define HWIO_QM_PERIOD_BUS_CFG_OUT(v)      \
        out_dword(HWIO_QM_PERIOD_BUS_CFG_ADDR,v)
#define HWIO_QM_PERIOD_BUS_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_PERIOD_BUS_CFG_ADDR,m,v,HWIO_QM_PERIOD_BUS_CFG_IN)
#define HWIO_QM_PERIOD_BUS_CFG_PERIOD_BUS_SW_OVERRIDE_BMSK                                                             0x80000000
#define HWIO_QM_PERIOD_BUS_CFG_PERIOD_BUS_SW_OVERRIDE_SHFT                                                                   0x1f
#define HWIO_QM_PERIOD_BUS_CFG_PERIOD_BUS_LOAD_SW_BMSK                                                                 0x40000000
#define HWIO_QM_PERIOD_BUS_CFG_PERIOD_BUS_LOAD_SW_SHFT                                                                       0x1e
#define HWIO_QM_PERIOD_BUS_CFG_PERIOD_BUS_SW_BMSK                                                                         0x1ffff
#define HWIO_QM_PERIOD_BUS_CFG_PERIOD_BUS_SW_SHFT                                                                             0x0

#define HWIO_QM_PERIOD_BUS_STATUS_ADDR                                                                                 (QM_REG_BASE      + 0x00001758)
#define HWIO_QM_PERIOD_BUS_STATUS_RMSK                                                                                    0x1ffff
#define HWIO_QM_PERIOD_BUS_STATUS_IN          \
        in_dword_masked(HWIO_QM_PERIOD_BUS_STATUS_ADDR, HWIO_QM_PERIOD_BUS_STATUS_RMSK)
#define HWIO_QM_PERIOD_BUS_STATUS_INM(m)      \
        in_dword_masked(HWIO_QM_PERIOD_BUS_STATUS_ADDR, m)
#define HWIO_QM_PERIOD_BUS_STATUS_PERIOD_BUS_SAMPLE_REG_BMSK                                                              0x1ffff
#define HWIO_QM_PERIOD_BUS_STATUS_PERIOD_BUS_SAMPLE_REG_SHFT                                                                  0x0

#define HWIO_QM_THROTTLE_LEVEL_QOS_n_ADDR(n)                                                                           (QM_REG_BASE      + 0x0000175c + 0x4 * (n))
#define HWIO_QM_THROTTLE_LEVEL_QOS_n_RMSK                                                                                  0x87ff
#define HWIO_QM_THROTTLE_LEVEL_QOS_n_MAXn                                                                                       7
#define HWIO_QM_THROTTLE_LEVEL_QOS_n_INI(n)        \
        in_dword_masked(HWIO_QM_THROTTLE_LEVEL_QOS_n_ADDR(n), HWIO_QM_THROTTLE_LEVEL_QOS_n_RMSK)
#define HWIO_QM_THROTTLE_LEVEL_QOS_n_INMI(n,mask)    \
        in_dword_masked(HWIO_QM_THROTTLE_LEVEL_QOS_n_ADDR(n), mask)
#define HWIO_QM_THROTTLE_LEVEL_QOS_n_OUTI(n,val)    \
        out_dword(HWIO_QM_THROTTLE_LEVEL_QOS_n_ADDR(n),val)
#define HWIO_QM_THROTTLE_LEVEL_QOS_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QM_THROTTLE_LEVEL_QOS_n_ADDR(n),mask,val,HWIO_QM_THROTTLE_LEVEL_QOS_n_INI(n))
#define HWIO_QM_THROTTLE_LEVEL_QOS_n_THRES_FREQ_EQ_BMSK                                                                    0x8000
#define HWIO_QM_THROTTLE_LEVEL_QOS_n_THRES_FREQ_EQ_SHFT                                                                       0xf
#define HWIO_QM_THROTTLE_LEVEL_QOS_n_THRES_FREQ_BMSK                                                                        0x700
#define HWIO_QM_THROTTLE_LEVEL_QOS_n_THRES_FREQ_SHFT                                                                          0x8
#define HWIO_QM_THROTTLE_LEVEL_QOS_n_THRES_SU_H_BMSK                                                                         0xf0
#define HWIO_QM_THROTTLE_LEVEL_QOS_n_THRES_SU_H_SHFT                                                                          0x4
#define HWIO_QM_THROTTLE_LEVEL_QOS_n_THRES_SU_L_BMSK                                                                          0xf
#define HWIO_QM_THROTTLE_LEVEL_QOS_n_THRES_SU_L_SHFT                                                                          0x0

#define HWIO_QM_CLNT_m_THROTTLE_LEVEL_QOS_n_ADDR(m,n)                                                                  (QM_REG_BASE      + 0x00001760 + 0x2C * (n) + 0x4 * (m))
#define HWIO_QM_CLNT_m_THROTTLE_LEVEL_QOS_n_RMSK                                                                       0xff00008f
#define HWIO_QM_CLNT_m_THROTTLE_LEVEL_QOS_n_MAXm                                                                               10
#define HWIO_QM_CLNT_m_THROTTLE_LEVEL_QOS_n_MAXn                                                                                7
#define HWIO_QM_CLNT_m_THROTTLE_LEVEL_QOS_n_INI2(m,n)        \
        in_dword_masked(HWIO_QM_CLNT_m_THROTTLE_LEVEL_QOS_n_ADDR(m,n), HWIO_QM_CLNT_m_THROTTLE_LEVEL_QOS_n_RMSK)
#define HWIO_QM_CLNT_m_THROTTLE_LEVEL_QOS_n_INMI2(m,n,mask)    \
        in_dword_masked(HWIO_QM_CLNT_m_THROTTLE_LEVEL_QOS_n_ADDR(m,n), mask)
#define HWIO_QM_CLNT_m_THROTTLE_LEVEL_QOS_n_OUTI2(m,n,val)    \
        out_dword(HWIO_QM_CLNT_m_THROTTLE_LEVEL_QOS_n_ADDR(m,n),val)
#define HWIO_QM_CLNT_m_THROTTLE_LEVEL_QOS_n_OUTMI2(m,n,mask,val) \
        out_dword_masked_ns(HWIO_QM_CLNT_m_THROTTLE_LEVEL_QOS_n_ADDR(m,n),mask,val,HWIO_QM_CLNT_m_THROTTLE_LEVEL_QOS_n_INI2(m,n))
#define HWIO_QM_CLNT_m_THROTTLE_LEVEL_QOS_n_AGG_BOOLEAN_FUNCTION_BMSK                                                  0xff000000
#define HWIO_QM_CLNT_m_THROTTLE_LEVEL_QOS_n_AGG_BOOLEAN_FUNCTION_SHFT                                                        0x18
#define HWIO_QM_CLNT_m_THROTTLE_LEVEL_QOS_n_THRES_DANGER_EQ_BMSK                                                             0x80
#define HWIO_QM_CLNT_m_THROTTLE_LEVEL_QOS_n_THRES_DANGER_EQ_SHFT                                                              0x7
#define HWIO_QM_CLNT_m_THROTTLE_LEVEL_QOS_n_THRES_DANGER_BMSK                                                                 0xf
#define HWIO_QM_CLNT_m_THROTTLE_LEVEL_QOS_n_THRES_DANGER_SHFT                                                                 0x0

#define HWIO_QM_CLNT_n_THROTTLE_LEVEL_MUX_CFG_ADDR(n)                                                                  (QM_REG_BASE      + 0x000018c0 + 0x4 * (n))
#define HWIO_QM_CLNT_n_THROTTLE_LEVEL_MUX_CFG_RMSK                                                                     0x80000007
#define HWIO_QM_CLNT_n_THROTTLE_LEVEL_MUX_CFG_MAXn                                                                             10
#define HWIO_QM_CLNT_n_THROTTLE_LEVEL_MUX_CFG_INI(n)        \
        in_dword_masked(HWIO_QM_CLNT_n_THROTTLE_LEVEL_MUX_CFG_ADDR(n), HWIO_QM_CLNT_n_THROTTLE_LEVEL_MUX_CFG_RMSK)
#define HWIO_QM_CLNT_n_THROTTLE_LEVEL_MUX_CFG_INMI(n,mask)    \
        in_dword_masked(HWIO_QM_CLNT_n_THROTTLE_LEVEL_MUX_CFG_ADDR(n), mask)
#define HWIO_QM_CLNT_n_THROTTLE_LEVEL_MUX_CFG_OUTI(n,val)    \
        out_dword(HWIO_QM_CLNT_n_THROTTLE_LEVEL_MUX_CFG_ADDR(n),val)
#define HWIO_QM_CLNT_n_THROTTLE_LEVEL_MUX_CFG_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QM_CLNT_n_THROTTLE_LEVEL_MUX_CFG_ADDR(n),mask,val,HWIO_QM_CLNT_n_THROTTLE_LEVEL_MUX_CFG_INI(n))
#define HWIO_QM_CLNT_n_THROTTLE_LEVEL_MUX_CFG_THROTTLE_LEVEL_SW_OVERRD_BMSK                                            0x80000000
#define HWIO_QM_CLNT_n_THROTTLE_LEVEL_MUX_CFG_THROTTLE_LEVEL_SW_OVERRD_SHFT                                                  0x1f
#define HWIO_QM_CLNT_n_THROTTLE_LEVEL_MUX_CFG_THROTTLE_LEVEL_SW_BMSK                                                          0x7
#define HWIO_QM_CLNT_n_THROTTLE_LEVEL_MUX_CFG_THROTTLE_LEVEL_SW_SHFT                                                          0x0

#define HWIO_QM_STATISTICS_CNTR_RESET_ADDR                                                                             (QM_REG_BASE      + 0x00001944)
#define HWIO_QM_STATISTICS_CNTR_RESET_RMSK                                                                                    0x1
#define HWIO_QM_STATISTICS_CNTR_RESET_IN          \
        in_dword_masked(HWIO_QM_STATISTICS_CNTR_RESET_ADDR, HWIO_QM_STATISTICS_CNTR_RESET_RMSK)
#define HWIO_QM_STATISTICS_CNTR_RESET_INM(m)      \
        in_dword_masked(HWIO_QM_STATISTICS_CNTR_RESET_ADDR, m)
#define HWIO_QM_STATISTICS_CNTR_RESET_OUT(v)      \
        out_dword(HWIO_QM_STATISTICS_CNTR_RESET_ADDR,v)
#define HWIO_QM_STATISTICS_CNTR_RESET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_STATISTICS_CNTR_RESET_ADDR,m,v,HWIO_QM_STATISTICS_CNTR_RESET_IN)
#define HWIO_QM_STATISTICS_CNTR_RESET_STATISTICS_CNTR_RESET_BMSK                                                              0x1
#define HWIO_QM_STATISTICS_CNTR_RESET_STATISTICS_CNTR_RESET_SHFT                                                              0x0

#define HWIO_QM_STATISTICS_DURATION_CNTR_THR_ADDR                                                                      (QM_REG_BASE      + 0x00001948)
#define HWIO_QM_STATISTICS_DURATION_CNTR_THR_RMSK                                                                      0xffffffff
#define HWIO_QM_STATISTICS_DURATION_CNTR_THR_IN          \
        in_dword_masked(HWIO_QM_STATISTICS_DURATION_CNTR_THR_ADDR, HWIO_QM_STATISTICS_DURATION_CNTR_THR_RMSK)
#define HWIO_QM_STATISTICS_DURATION_CNTR_THR_INM(m)      \
        in_dword_masked(HWIO_QM_STATISTICS_DURATION_CNTR_THR_ADDR, m)
#define HWIO_QM_STATISTICS_DURATION_CNTR_THR_OUT(v)      \
        out_dword(HWIO_QM_STATISTICS_DURATION_CNTR_THR_ADDR,v)
#define HWIO_QM_STATISTICS_DURATION_CNTR_THR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_STATISTICS_DURATION_CNTR_THR_ADDR,m,v,HWIO_QM_STATISTICS_DURATION_CNTR_THR_IN)
#define HWIO_QM_STATISTICS_DURATION_CNTR_THR_STATISTICS_DURATION_CNTR_THR_BMSK                                         0xffffffff
#define HWIO_QM_STATISTICS_DURATION_CNTR_THR_STATISTICS_DURATION_CNTR_THR_SHFT                                                0x0

#define HWIO_QM_STATISTICS_DURATION_CNTR_READBACK_ADDR                                                                 (QM_REG_BASE      + 0x0000194c)
#define HWIO_QM_STATISTICS_DURATION_CNTR_READBACK_RMSK                                                                 0xffffffff
#define HWIO_QM_STATISTICS_DURATION_CNTR_READBACK_IN          \
        in_dword_masked(HWIO_QM_STATISTICS_DURATION_CNTR_READBACK_ADDR, HWIO_QM_STATISTICS_DURATION_CNTR_READBACK_RMSK)
#define HWIO_QM_STATISTICS_DURATION_CNTR_READBACK_INM(m)      \
        in_dword_masked(HWIO_QM_STATISTICS_DURATION_CNTR_READBACK_ADDR, m)
#define HWIO_QM_STATISTICS_DURATION_CNTR_READBACK_STATISTICS_DURATION_CNTR_READBACK_BMSK                               0xffffffff
#define HWIO_QM_STATISTICS_DURATION_CNTR_READBACK_STATISTICS_DURATION_CNTR_READBACK_SHFT                                      0x0

#define HWIO_QM_VFE_DANGER_LEVEL_n_CNTR_READBACK_ADDR(n)                                                               (QM_REG_BASE      + 0x00001950 + 0x4 * (n))
#define HWIO_QM_VFE_DANGER_LEVEL_n_CNTR_READBACK_RMSK                                                                  0xffffffff
#define HWIO_QM_VFE_DANGER_LEVEL_n_CNTR_READBACK_MAXn                                                                           3
#define HWIO_QM_VFE_DANGER_LEVEL_n_CNTR_READBACK_INI(n)        \
        in_dword_masked(HWIO_QM_VFE_DANGER_LEVEL_n_CNTR_READBACK_ADDR(n), HWIO_QM_VFE_DANGER_LEVEL_n_CNTR_READBACK_RMSK)
#define HWIO_QM_VFE_DANGER_LEVEL_n_CNTR_READBACK_INMI(n,mask)    \
        in_dword_masked(HWIO_QM_VFE_DANGER_LEVEL_n_CNTR_READBACK_ADDR(n), mask)
#define HWIO_QM_VFE_DANGER_LEVEL_n_CNTR_READBACK_VFE_DANGER_LEVEL_CNTR_READBACK_BMSK                                   0xffffffff
#define HWIO_QM_VFE_DANGER_LEVEL_n_CNTR_READBACK_VFE_DANGER_LEVEL_CNTR_READBACK_SHFT                                          0x0

#define HWIO_QM_VFE_DANGER_LEVEL_GT_0_CNTR_READBACK_ADDR                                                               (QM_REG_BASE      + 0x00001960)
#define HWIO_QM_VFE_DANGER_LEVEL_GT_0_CNTR_READBACK_RMSK                                                               0xffffffff
#define HWIO_QM_VFE_DANGER_LEVEL_GT_0_CNTR_READBACK_IN          \
        in_dword_masked(HWIO_QM_VFE_DANGER_LEVEL_GT_0_CNTR_READBACK_ADDR, HWIO_QM_VFE_DANGER_LEVEL_GT_0_CNTR_READBACK_RMSK)
#define HWIO_QM_VFE_DANGER_LEVEL_GT_0_CNTR_READBACK_INM(m)      \
        in_dword_masked(HWIO_QM_VFE_DANGER_LEVEL_GT_0_CNTR_READBACK_ADDR, m)
#define HWIO_QM_VFE_DANGER_LEVEL_GT_0_CNTR_READBACK_VFE_DANGER_LEVEL_GT_0_CNTR_READBACK_BMSK                           0xffffffff
#define HWIO_QM_VFE_DANGER_LEVEL_GT_0_CNTR_READBACK_VFE_DANGER_LEVEL_GT_0_CNTR_READBACK_SHFT                                  0x0

#define HWIO_QM_VFE_SAFE_LEVEL_LT_1_CNTR_READBACK_ADDR                                                                 (QM_REG_BASE      + 0x00001964)
#define HWIO_QM_VFE_SAFE_LEVEL_LT_1_CNTR_READBACK_RMSK                                                                 0xffffffff
#define HWIO_QM_VFE_SAFE_LEVEL_LT_1_CNTR_READBACK_IN          \
        in_dword_masked(HWIO_QM_VFE_SAFE_LEVEL_LT_1_CNTR_READBACK_ADDR, HWIO_QM_VFE_SAFE_LEVEL_LT_1_CNTR_READBACK_RMSK)
#define HWIO_QM_VFE_SAFE_LEVEL_LT_1_CNTR_READBACK_INM(m)      \
        in_dword_masked(HWIO_QM_VFE_SAFE_LEVEL_LT_1_CNTR_READBACK_ADDR, m)
#define HWIO_QM_VFE_SAFE_LEVEL_LT_1_CNTR_READBACK_VFE_SAFE_LEVEL_LT_1_CNTR_READBACK_BMSK                               0xffffffff
#define HWIO_QM_VFE_SAFE_LEVEL_LT_1_CNTR_READBACK_VFE_SAFE_LEVEL_LT_1_CNTR_READBACK_SHFT                                      0x0

#define HWIO_QM_MDP_DANGER_LEVEL_n_CNTR_READBACK_ADDR(n)                                                               (QM_REG_BASE      + 0x00001970 + 0x4 * (n))
#define HWIO_QM_MDP_DANGER_LEVEL_n_CNTR_READBACK_RMSK                                                                  0xffffffff
#define HWIO_QM_MDP_DANGER_LEVEL_n_CNTR_READBACK_MAXn                                                                           3
#define HWIO_QM_MDP_DANGER_LEVEL_n_CNTR_READBACK_INI(n)        \
        in_dword_masked(HWIO_QM_MDP_DANGER_LEVEL_n_CNTR_READBACK_ADDR(n), HWIO_QM_MDP_DANGER_LEVEL_n_CNTR_READBACK_RMSK)
#define HWIO_QM_MDP_DANGER_LEVEL_n_CNTR_READBACK_INMI(n,mask)    \
        in_dword_masked(HWIO_QM_MDP_DANGER_LEVEL_n_CNTR_READBACK_ADDR(n), mask)
#define HWIO_QM_MDP_DANGER_LEVEL_n_CNTR_READBACK_MDP_DANGER_LEVEL_CNTR_READBACK_BMSK                                   0xffffffff
#define HWIO_QM_MDP_DANGER_LEVEL_n_CNTR_READBACK_MDP_DANGER_LEVEL_CNTR_READBACK_SHFT                                          0x0

#define HWIO_QM_MDP_DANGER_LEVEL_GT_0_CNTR_READBACK_ADDR                                                               (QM_REG_BASE      + 0x00001980)
#define HWIO_QM_MDP_DANGER_LEVEL_GT_0_CNTR_READBACK_RMSK                                                               0xffffffff
#define HWIO_QM_MDP_DANGER_LEVEL_GT_0_CNTR_READBACK_IN          \
        in_dword_masked(HWIO_QM_MDP_DANGER_LEVEL_GT_0_CNTR_READBACK_ADDR, HWIO_QM_MDP_DANGER_LEVEL_GT_0_CNTR_READBACK_RMSK)
#define HWIO_QM_MDP_DANGER_LEVEL_GT_0_CNTR_READBACK_INM(m)      \
        in_dword_masked(HWIO_QM_MDP_DANGER_LEVEL_GT_0_CNTR_READBACK_ADDR, m)
#define HWIO_QM_MDP_DANGER_LEVEL_GT_0_CNTR_READBACK_MDP_DANGER_LEVEL_GT_0_CNTR_READBACK_BMSK                           0xffffffff
#define HWIO_QM_MDP_DANGER_LEVEL_GT_0_CNTR_READBACK_MDP_DANGER_LEVEL_GT_0_CNTR_READBACK_SHFT                                  0x0

#define HWIO_QM_MDP_SAFE_LEVEL_LT_1_CNTR_READBACK_ADDR                                                                 (QM_REG_BASE      + 0x00001984)
#define HWIO_QM_MDP_SAFE_LEVEL_LT_1_CNTR_READBACK_RMSK                                                                 0xffffffff
#define HWIO_QM_MDP_SAFE_LEVEL_LT_1_CNTR_READBACK_IN          \
        in_dword_masked(HWIO_QM_MDP_SAFE_LEVEL_LT_1_CNTR_READBACK_ADDR, HWIO_QM_MDP_SAFE_LEVEL_LT_1_CNTR_READBACK_RMSK)
#define HWIO_QM_MDP_SAFE_LEVEL_LT_1_CNTR_READBACK_INM(m)      \
        in_dword_masked(HWIO_QM_MDP_SAFE_LEVEL_LT_1_CNTR_READBACK_ADDR, m)
#define HWIO_QM_MDP_SAFE_LEVEL_LT_1_CNTR_READBACK_MDP_SAFE_LEVEL_LT_1_CNTR_READBACK_BMSK                               0xffffffff
#define HWIO_QM_MDP_SAFE_LEVEL_LT_1_CNTR_READBACK_MDP_SAFE_LEVEL_LT_1_CNTR_READBACK_SHFT                                      0x0

#define HWIO_QM_VENUS_DANGER_LEVEL_n_CNTR_READBACK_ADDR(n)                                                             (QM_REG_BASE      + 0x00001990 + 0x4 * (n))
#define HWIO_QM_VENUS_DANGER_LEVEL_n_CNTR_READBACK_RMSK                                                                0xffffffff
#define HWIO_QM_VENUS_DANGER_LEVEL_n_CNTR_READBACK_MAXn                                                                         3
#define HWIO_QM_VENUS_DANGER_LEVEL_n_CNTR_READBACK_INI(n)        \
        in_dword_masked(HWIO_QM_VENUS_DANGER_LEVEL_n_CNTR_READBACK_ADDR(n), HWIO_QM_VENUS_DANGER_LEVEL_n_CNTR_READBACK_RMSK)
#define HWIO_QM_VENUS_DANGER_LEVEL_n_CNTR_READBACK_INMI(n,mask)    \
        in_dword_masked(HWIO_QM_VENUS_DANGER_LEVEL_n_CNTR_READBACK_ADDR(n), mask)
#define HWIO_QM_VENUS_DANGER_LEVEL_n_CNTR_READBACK_VENUS_DANGER_LEVEL_CNTR_READBACK_BMSK                               0xffffffff
#define HWIO_QM_VENUS_DANGER_LEVEL_n_CNTR_READBACK_VENUS_DANGER_LEVEL_CNTR_READBACK_SHFT                                      0x0

#define HWIO_QM_VENUS_DANGER_LEVEL_GT_0_CNTR_READBACK_ADDR                                                             (QM_REG_BASE      + 0x000019a0)
#define HWIO_QM_VENUS_DANGER_LEVEL_GT_0_CNTR_READBACK_RMSK                                                             0xffffffff
#define HWIO_QM_VENUS_DANGER_LEVEL_GT_0_CNTR_READBACK_IN          \
        in_dword_masked(HWIO_QM_VENUS_DANGER_LEVEL_GT_0_CNTR_READBACK_ADDR, HWIO_QM_VENUS_DANGER_LEVEL_GT_0_CNTR_READBACK_RMSK)
#define HWIO_QM_VENUS_DANGER_LEVEL_GT_0_CNTR_READBACK_INM(m)      \
        in_dword_masked(HWIO_QM_VENUS_DANGER_LEVEL_GT_0_CNTR_READBACK_ADDR, m)
#define HWIO_QM_VENUS_DANGER_LEVEL_GT_0_CNTR_READBACK_VENUS_DANGER_LEVEL_GT_0_CNTR_READBACK_BMSK                       0xffffffff
#define HWIO_QM_VENUS_DANGER_LEVEL_GT_0_CNTR_READBACK_VENUS_DANGER_LEVEL_GT_0_CNTR_READBACK_SHFT                              0x0

#define HWIO_QM_VENUS_SAFE_LEVEL_LT_1_CNTR_READBACK_ADDR                                                               (QM_REG_BASE      + 0x000019a4)
#define HWIO_QM_VENUS_SAFE_LEVEL_LT_1_CNTR_READBACK_RMSK                                                               0xffffffff
#define HWIO_QM_VENUS_SAFE_LEVEL_LT_1_CNTR_READBACK_IN          \
        in_dword_masked(HWIO_QM_VENUS_SAFE_LEVEL_LT_1_CNTR_READBACK_ADDR, HWIO_QM_VENUS_SAFE_LEVEL_LT_1_CNTR_READBACK_RMSK)
#define HWIO_QM_VENUS_SAFE_LEVEL_LT_1_CNTR_READBACK_INM(m)      \
        in_dword_masked(HWIO_QM_VENUS_SAFE_LEVEL_LT_1_CNTR_READBACK_ADDR, m)
#define HWIO_QM_VENUS_SAFE_LEVEL_LT_1_CNTR_READBACK_VENUS_SAFE_LEVEL_LT_1_CNTR_READBACK_BMSK                           0xffffffff
#define HWIO_QM_VENUS_SAFE_LEVEL_LT_1_CNTR_READBACK_VENUS_SAFE_LEVEL_LT_1_CNTR_READBACK_SHFT                                  0x0

#define HWIO_QM_MODEM_DANGER_LEVEL_n_CNTR_READBACK_ADDR(n)                                                             (QM_REG_BASE      + 0x000019b0 + 0x4 * (n))
#define HWIO_QM_MODEM_DANGER_LEVEL_n_CNTR_READBACK_RMSK                                                                0xffffffff
#define HWIO_QM_MODEM_DANGER_LEVEL_n_CNTR_READBACK_MAXn                                                                         3
#define HWIO_QM_MODEM_DANGER_LEVEL_n_CNTR_READBACK_INI(n)        \
        in_dword_masked(HWIO_QM_MODEM_DANGER_LEVEL_n_CNTR_READBACK_ADDR(n), HWIO_QM_MODEM_DANGER_LEVEL_n_CNTR_READBACK_RMSK)
#define HWIO_QM_MODEM_DANGER_LEVEL_n_CNTR_READBACK_INMI(n,mask)    \
        in_dword_masked(HWIO_QM_MODEM_DANGER_LEVEL_n_CNTR_READBACK_ADDR(n), mask)
#define HWIO_QM_MODEM_DANGER_LEVEL_n_CNTR_READBACK_MODEM_DANGER_LEVEL_CNTR_READBACK_BMSK                               0xffffffff
#define HWIO_QM_MODEM_DANGER_LEVEL_n_CNTR_READBACK_MODEM_DANGER_LEVEL_CNTR_READBACK_SHFT                                      0x0

#define HWIO_QM_MODEM_DANGER_LEVEL_GT_0_CNTR_READBACK_ADDR                                                             (QM_REG_BASE      + 0x000019c0)
#define HWIO_QM_MODEM_DANGER_LEVEL_GT_0_CNTR_READBACK_RMSK                                                             0xffffffff
#define HWIO_QM_MODEM_DANGER_LEVEL_GT_0_CNTR_READBACK_IN          \
        in_dword_masked(HWIO_QM_MODEM_DANGER_LEVEL_GT_0_CNTR_READBACK_ADDR, HWIO_QM_MODEM_DANGER_LEVEL_GT_0_CNTR_READBACK_RMSK)
#define HWIO_QM_MODEM_DANGER_LEVEL_GT_0_CNTR_READBACK_INM(m)      \
        in_dword_masked(HWIO_QM_MODEM_DANGER_LEVEL_GT_0_CNTR_READBACK_ADDR, m)
#define HWIO_QM_MODEM_DANGER_LEVEL_GT_0_CNTR_READBACK_MODEM_DANGER_LEVEL_GT_0_CNTR_READBACK_BMSK                       0xffffffff
#define HWIO_QM_MODEM_DANGER_LEVEL_GT_0_CNTR_READBACK_MODEM_DANGER_LEVEL_GT_0_CNTR_READBACK_SHFT                              0x0

#define HWIO_QM_MODEM_SAFE_LEVEL_LT_1_CNTR_READBACK_ADDR                                                               (QM_REG_BASE      + 0x000019c4)
#define HWIO_QM_MODEM_SAFE_LEVEL_LT_1_CNTR_READBACK_RMSK                                                               0xffffffff
#define HWIO_QM_MODEM_SAFE_LEVEL_LT_1_CNTR_READBACK_IN          \
        in_dword_masked(HWIO_QM_MODEM_SAFE_LEVEL_LT_1_CNTR_READBACK_ADDR, HWIO_QM_MODEM_SAFE_LEVEL_LT_1_CNTR_READBACK_RMSK)
#define HWIO_QM_MODEM_SAFE_LEVEL_LT_1_CNTR_READBACK_INM(m)      \
        in_dword_masked(HWIO_QM_MODEM_SAFE_LEVEL_LT_1_CNTR_READBACK_ADDR, m)
#define HWIO_QM_MODEM_SAFE_LEVEL_LT_1_CNTR_READBACK_MODEM_SAFE_LEVEL_LT_1_CNTR_READBACK_BMSK                           0xffffffff
#define HWIO_QM_MODEM_SAFE_LEVEL_LT_1_CNTR_READBACK_MODEM_SAFE_LEVEL_LT_1_CNTR_READBACK_SHFT                                  0x0

#define HWIO_QM_DSP_DANGER_LEVEL_n_CNTR_READBACK_ADDR(n)                                                               (QM_REG_BASE      + 0x000019d0 + 0x4 * (n))
#define HWIO_QM_DSP_DANGER_LEVEL_n_CNTR_READBACK_RMSK                                                                  0xffffffff
#define HWIO_QM_DSP_DANGER_LEVEL_n_CNTR_READBACK_MAXn                                                                           3
#define HWIO_QM_DSP_DANGER_LEVEL_n_CNTR_READBACK_INI(n)        \
        in_dword_masked(HWIO_QM_DSP_DANGER_LEVEL_n_CNTR_READBACK_ADDR(n), HWIO_QM_DSP_DANGER_LEVEL_n_CNTR_READBACK_RMSK)
#define HWIO_QM_DSP_DANGER_LEVEL_n_CNTR_READBACK_INMI(n,mask)    \
        in_dword_masked(HWIO_QM_DSP_DANGER_LEVEL_n_CNTR_READBACK_ADDR(n), mask)
#define HWIO_QM_DSP_DANGER_LEVEL_n_CNTR_READBACK_DSP_DANGER_LEVEL_CNTR_READBACK_BMSK                                   0xffffffff
#define HWIO_QM_DSP_DANGER_LEVEL_n_CNTR_READBACK_DSP_DANGER_LEVEL_CNTR_READBACK_SHFT                                          0x0

#define HWIO_QM_DSP_DANGER_LEVEL_GT_0_CNTR_READBACK_ADDR                                                               (QM_REG_BASE      + 0x00001a40)
#define HWIO_QM_DSP_DANGER_LEVEL_GT_0_CNTR_READBACK_RMSK                                                               0xffffffff
#define HWIO_QM_DSP_DANGER_LEVEL_GT_0_CNTR_READBACK_IN          \
        in_dword_masked(HWIO_QM_DSP_DANGER_LEVEL_GT_0_CNTR_READBACK_ADDR, HWIO_QM_DSP_DANGER_LEVEL_GT_0_CNTR_READBACK_RMSK)
#define HWIO_QM_DSP_DANGER_LEVEL_GT_0_CNTR_READBACK_INM(m)      \
        in_dword_masked(HWIO_QM_DSP_DANGER_LEVEL_GT_0_CNTR_READBACK_ADDR, m)
#define HWIO_QM_DSP_DANGER_LEVEL_GT_0_CNTR_READBACK_DSP_DANGER_LEVEL_GT_0_CNTR_READBACK_BMSK                           0xffffffff
#define HWIO_QM_DSP_DANGER_LEVEL_GT_0_CNTR_READBACK_DSP_DANGER_LEVEL_GT_0_CNTR_READBACK_SHFT                                  0x0

#define HWIO_QM_DSP_SAFE_LEVEL_LT_1_CNTR_READBACK_ADDR                                                                 (QM_REG_BASE      + 0x00001a44)
#define HWIO_QM_DSP_SAFE_LEVEL_LT_1_CNTR_READBACK_RMSK                                                                 0xffffffff
#define HWIO_QM_DSP_SAFE_LEVEL_LT_1_CNTR_READBACK_IN          \
        in_dword_masked(HWIO_QM_DSP_SAFE_LEVEL_LT_1_CNTR_READBACK_ADDR, HWIO_QM_DSP_SAFE_LEVEL_LT_1_CNTR_READBACK_RMSK)
#define HWIO_QM_DSP_SAFE_LEVEL_LT_1_CNTR_READBACK_INM(m)      \
        in_dword_masked(HWIO_QM_DSP_SAFE_LEVEL_LT_1_CNTR_READBACK_ADDR, m)
#define HWIO_QM_DSP_SAFE_LEVEL_LT_1_CNTR_READBACK_DSP_SAFE_LEVEL_LT_1_CNTR_READBACK_BMSK                               0xffffffff
#define HWIO_QM_DSP_SAFE_LEVEL_LT_1_CNTR_READBACK_DSP_SAFE_LEVEL_LT_1_CNTR_READBACK_SHFT                                      0x0

#define HWIO_QM_SAFE_OVERRIDE_VALUE_ADDR                                                                               (QM_REG_BASE      + 0x00001a50)
#define HWIO_QM_SAFE_OVERRIDE_VALUE_RMSK                                                                               0x8000001f
#define HWIO_QM_SAFE_OVERRIDE_VALUE_IN          \
        in_dword_masked(HWIO_QM_SAFE_OVERRIDE_VALUE_ADDR, HWIO_QM_SAFE_OVERRIDE_VALUE_RMSK)
#define HWIO_QM_SAFE_OVERRIDE_VALUE_INM(m)      \
        in_dword_masked(HWIO_QM_SAFE_OVERRIDE_VALUE_ADDR, m)
#define HWIO_QM_SAFE_OVERRIDE_VALUE_OUT(v)      \
        out_dword(HWIO_QM_SAFE_OVERRIDE_VALUE_ADDR,v)
#define HWIO_QM_SAFE_OVERRIDE_VALUE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_SAFE_OVERRIDE_VALUE_ADDR,m,v,HWIO_QM_SAFE_OVERRIDE_VALUE_IN)
#define HWIO_QM_SAFE_OVERRIDE_VALUE_SW_SAFE_OVERRIDE_VALUE_BMSK                                                        0x80000000
#define HWIO_QM_SAFE_OVERRIDE_VALUE_SW_SAFE_OVERRIDE_VALUE_SHFT                                                              0x1f
#define HWIO_QM_SAFE_OVERRIDE_VALUE_MODEM_SAFE_OVERRIDE_VALUE_BMSK                                                           0x10
#define HWIO_QM_SAFE_OVERRIDE_VALUE_MODEM_SAFE_OVERRIDE_VALUE_SHFT                                                            0x4
#define HWIO_QM_SAFE_OVERRIDE_VALUE_VENUS_SAFE_OVERRIDE_VALUE_BMSK                                                            0x8
#define HWIO_QM_SAFE_OVERRIDE_VALUE_VENUS_SAFE_OVERRIDE_VALUE_SHFT                                                            0x3
#define HWIO_QM_SAFE_OVERRIDE_VALUE_MDP_SAFE_OVERRIDE_VALUE_BMSK                                                              0x4
#define HWIO_QM_SAFE_OVERRIDE_VALUE_MDP_SAFE_OVERRIDE_VALUE_SHFT                                                              0x2
#define HWIO_QM_SAFE_OVERRIDE_VALUE_VFE1_SAFE_OVERRIDE_VALUE_BMSK                                                             0x2
#define HWIO_QM_SAFE_OVERRIDE_VALUE_VFE1_SAFE_OVERRIDE_VALUE_SHFT                                                             0x1
#define HWIO_QM_SAFE_OVERRIDE_VALUE_VFE0_SAFE_OVERRIDE_VALUE_BMSK                                                             0x1
#define HWIO_QM_SAFE_OVERRIDE_VALUE_VFE0_SAFE_OVERRIDE_VALUE_SHFT                                                             0x0

#define HWIO_QM_SAFE_OVERRIDE_EN_ADDR                                                                                  (QM_REG_BASE      + 0x00001a54)
#define HWIO_QM_SAFE_OVERRIDE_EN_RMSK                                                                                  0x8000001f
#define HWIO_QM_SAFE_OVERRIDE_EN_IN          \
        in_dword_masked(HWIO_QM_SAFE_OVERRIDE_EN_ADDR, HWIO_QM_SAFE_OVERRIDE_EN_RMSK)
#define HWIO_QM_SAFE_OVERRIDE_EN_INM(m)      \
        in_dword_masked(HWIO_QM_SAFE_OVERRIDE_EN_ADDR, m)
#define HWIO_QM_SAFE_OVERRIDE_EN_OUT(v)      \
        out_dword(HWIO_QM_SAFE_OVERRIDE_EN_ADDR,v)
#define HWIO_QM_SAFE_OVERRIDE_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_SAFE_OVERRIDE_EN_ADDR,m,v,HWIO_QM_SAFE_OVERRIDE_EN_IN)
#define HWIO_QM_SAFE_OVERRIDE_EN_SW_SAFE_OVERRIDE_EN_BMSK                                                              0x80000000
#define HWIO_QM_SAFE_OVERRIDE_EN_SW_SAFE_OVERRIDE_EN_SHFT                                                                    0x1f
#define HWIO_QM_SAFE_OVERRIDE_EN_MODEM_SAFE_OVERRIDE_EN_BMSK                                                                 0x10
#define HWIO_QM_SAFE_OVERRIDE_EN_MODEM_SAFE_OVERRIDE_EN_SHFT                                                                  0x4
#define HWIO_QM_SAFE_OVERRIDE_EN_VENUS_SAFE_OVERRIDE_EN_BMSK                                                                  0x8
#define HWIO_QM_SAFE_OVERRIDE_EN_VENUS_SAFE_OVERRIDE_EN_SHFT                                                                  0x3
#define HWIO_QM_SAFE_OVERRIDE_EN_MDP_SAFE_OVERRIDE_EN_BMSK                                                                    0x4
#define HWIO_QM_SAFE_OVERRIDE_EN_MDP_SAFE_OVERRIDE_EN_SHFT                                                                    0x2
#define HWIO_QM_SAFE_OVERRIDE_EN_VFE1_SAFE_OVERRIDE_EN_BMSK                                                                   0x2
#define HWIO_QM_SAFE_OVERRIDE_EN_VFE1_SAFE_OVERRIDE_EN_SHFT                                                                   0x1
#define HWIO_QM_SAFE_OVERRIDE_EN_VFE0_SAFE_OVERRIDE_EN_BMSK                                                                   0x1
#define HWIO_QM_SAFE_OVERRIDE_EN_VFE0_SAFE_OVERRIDE_EN_SHFT                                                                   0x0

#define HWIO_QM_SAFE_SW_ADDR                                                                                           (QM_REG_BASE      + 0x00001a58)
#define HWIO_QM_SAFE_SW_RMSK                                                                                                  0x1
#define HWIO_QM_SAFE_SW_IN          \
        in_dword_masked(HWIO_QM_SAFE_SW_ADDR, HWIO_QM_SAFE_SW_RMSK)
#define HWIO_QM_SAFE_SW_INM(m)      \
        in_dword_masked(HWIO_QM_SAFE_SW_ADDR, m)
#define HWIO_QM_SAFE_SW_OUT(v)      \
        out_dword(HWIO_QM_SAFE_SW_ADDR,v)
#define HWIO_QM_SAFE_SW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_SAFE_SW_ADDR,m,v,HWIO_QM_SAFE_SW_IN)
#define HWIO_QM_SAFE_SW_SW_SAFE_BMSK                                                                                          0x1
#define HWIO_QM_SAFE_SW_SW_SAFE_SHFT                                                                                          0x0

#define HWIO_QM_AGGR_SAFE_TL_V2_OVERRIDE_CNTRL_ADDR                                                                    (QM_REG_BASE      + 0x00001a5c)
#define HWIO_QM_AGGR_SAFE_TL_V2_OVERRIDE_CNTRL_RMSK                                                                         0x101
#define HWIO_QM_AGGR_SAFE_TL_V2_OVERRIDE_CNTRL_IN          \
        in_dword_masked(HWIO_QM_AGGR_SAFE_TL_V2_OVERRIDE_CNTRL_ADDR, HWIO_QM_AGGR_SAFE_TL_V2_OVERRIDE_CNTRL_RMSK)
#define HWIO_QM_AGGR_SAFE_TL_V2_OVERRIDE_CNTRL_INM(m)      \
        in_dword_masked(HWIO_QM_AGGR_SAFE_TL_V2_OVERRIDE_CNTRL_ADDR, m)
#define HWIO_QM_AGGR_SAFE_TL_V2_OVERRIDE_CNTRL_OUT(v)      \
        out_dword(HWIO_QM_AGGR_SAFE_TL_V2_OVERRIDE_CNTRL_ADDR,v)
#define HWIO_QM_AGGR_SAFE_TL_V2_OVERRIDE_CNTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_AGGR_SAFE_TL_V2_OVERRIDE_CNTRL_ADDR,m,v,HWIO_QM_AGGR_SAFE_TL_V2_OVERRIDE_CNTRL_IN)
#define HWIO_QM_AGGR_SAFE_TL_V2_OVERRIDE_CNTRL_QM_AGGR_SAFE_TL_V2_OVERRIDE_VALUE_BMSK                                       0x100
#define HWIO_QM_AGGR_SAFE_TL_V2_OVERRIDE_CNTRL_QM_AGGR_SAFE_TL_V2_OVERRIDE_VALUE_SHFT                                         0x8
#define HWIO_QM_AGGR_SAFE_TL_V2_OVERRIDE_CNTRL_QM_AGGR_SAFE_TL_V2_OVERRIDE_EN_BMSK                                            0x1
#define HWIO_QM_AGGR_SAFE_TL_V2_OVERRIDE_CNTRL_QM_AGGR_SAFE_TL_V2_OVERRIDE_EN_SHFT                                            0x0

#define HWIO_QM_AGGR_SAFE_DSP_SYSTEM_DANGER_OVERRIDE_CNTRL_ADDR                                                        (QM_REG_BASE      + 0x00001a60)
#define HWIO_QM_AGGR_SAFE_DSP_SYSTEM_DANGER_OVERRIDE_CNTRL_RMSK                                                             0x101
#define HWIO_QM_AGGR_SAFE_DSP_SYSTEM_DANGER_OVERRIDE_CNTRL_IN          \
        in_dword_masked(HWIO_QM_AGGR_SAFE_DSP_SYSTEM_DANGER_OVERRIDE_CNTRL_ADDR, HWIO_QM_AGGR_SAFE_DSP_SYSTEM_DANGER_OVERRIDE_CNTRL_RMSK)
#define HWIO_QM_AGGR_SAFE_DSP_SYSTEM_DANGER_OVERRIDE_CNTRL_INM(m)      \
        in_dword_masked(HWIO_QM_AGGR_SAFE_DSP_SYSTEM_DANGER_OVERRIDE_CNTRL_ADDR, m)
#define HWIO_QM_AGGR_SAFE_DSP_SYSTEM_DANGER_OVERRIDE_CNTRL_OUT(v)      \
        out_dword(HWIO_QM_AGGR_SAFE_DSP_SYSTEM_DANGER_OVERRIDE_CNTRL_ADDR,v)
#define HWIO_QM_AGGR_SAFE_DSP_SYSTEM_DANGER_OVERRIDE_CNTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_AGGR_SAFE_DSP_SYSTEM_DANGER_OVERRIDE_CNTRL_ADDR,m,v,HWIO_QM_AGGR_SAFE_DSP_SYSTEM_DANGER_OVERRIDE_CNTRL_IN)
#define HWIO_QM_AGGR_SAFE_DSP_SYSTEM_DANGER_OVERRIDE_CNTRL_QM_AGGR_SAFE_DSP_SYSTEM_DANGER_OVERRIDE_VALUE_BMSK               0x100
#define HWIO_QM_AGGR_SAFE_DSP_SYSTEM_DANGER_OVERRIDE_CNTRL_QM_AGGR_SAFE_DSP_SYSTEM_DANGER_OVERRIDE_VALUE_SHFT                 0x8
#define HWIO_QM_AGGR_SAFE_DSP_SYSTEM_DANGER_OVERRIDE_CNTRL_QM_AGGR_SAFE_DSP_SYSTEM_DANGER_OVERRIDE_EN_BMSK                    0x1
#define HWIO_QM_AGGR_SAFE_DSP_SYSTEM_DANGER_OVERRIDE_CNTRL_QM_AGGR_SAFE_DSP_SYSTEM_DANGER_OVERRIDE_EN_SHFT                    0x0

#define HWIO_QM_DANGER_OVERRIDE_VALUE_ADDR                                                                             (QM_REG_BASE      + 0x00001a64)
#define HWIO_QM_DANGER_OVERRIDE_VALUE_RMSK                                                                              0x3ffffff
#define HWIO_QM_DANGER_OVERRIDE_VALUE_IN          \
        in_dword_masked(HWIO_QM_DANGER_OVERRIDE_VALUE_ADDR, HWIO_QM_DANGER_OVERRIDE_VALUE_RMSK)
#define HWIO_QM_DANGER_OVERRIDE_VALUE_INM(m)      \
        in_dword_masked(HWIO_QM_DANGER_OVERRIDE_VALUE_ADDR, m)
#define HWIO_QM_DANGER_OVERRIDE_VALUE_OUT(v)      \
        out_dword(HWIO_QM_DANGER_OVERRIDE_VALUE_ADDR,v)
#define HWIO_QM_DANGER_OVERRIDE_VALUE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_DANGER_OVERRIDE_VALUE_ADDR,m,v,HWIO_QM_DANGER_OVERRIDE_VALUE_IN)
#define HWIO_QM_DANGER_OVERRIDE_VALUE_DSP_3_OTHER_DANGER_OVERRIDE_VALUE_BMSK                                            0x3000000
#define HWIO_QM_DANGER_OVERRIDE_VALUE_DSP_3_OTHER_DANGER_OVERRIDE_VALUE_SHFT                                                 0x18
#define HWIO_QM_DANGER_OVERRIDE_VALUE_DSP_2_OTHER_DANGER_OVERRIDE_VALUE_BMSK                                             0xc00000
#define HWIO_QM_DANGER_OVERRIDE_VALUE_DSP_2_OTHER_DANGER_OVERRIDE_VALUE_SHFT                                                 0x16
#define HWIO_QM_DANGER_OVERRIDE_VALUE_DSP_1_OTHER_DANGER_OVERRIDE_VALUE_BMSK                                             0x300000
#define HWIO_QM_DANGER_OVERRIDE_VALUE_DSP_1_OTHER_DANGER_OVERRIDE_VALUE_SHFT                                                 0x14
#define HWIO_QM_DANGER_OVERRIDE_VALUE_DSP_0_OTHER_DANGER_OVERRIDE_VALUE_BMSK                                              0xc0000
#define HWIO_QM_DANGER_OVERRIDE_VALUE_DSP_0_OTHER_DANGER_OVERRIDE_VALUE_SHFT                                                 0x12
#define HWIO_QM_DANGER_OVERRIDE_VALUE_DSP_3_DANGER_OVERRIDE_VALUE_BMSK                                                    0x30000
#define HWIO_QM_DANGER_OVERRIDE_VALUE_DSP_3_DANGER_OVERRIDE_VALUE_SHFT                                                       0x10
#define HWIO_QM_DANGER_OVERRIDE_VALUE_DSP_2_DANGER_OVERRIDE_VALUE_BMSK                                                     0xc000
#define HWIO_QM_DANGER_OVERRIDE_VALUE_DSP_2_DANGER_OVERRIDE_VALUE_SHFT                                                        0xe
#define HWIO_QM_DANGER_OVERRIDE_VALUE_DSP_1_DANGER_OVERRIDE_VALUE_BMSK                                                     0x3000
#define HWIO_QM_DANGER_OVERRIDE_VALUE_DSP_1_DANGER_OVERRIDE_VALUE_SHFT                                                        0xc
#define HWIO_QM_DANGER_OVERRIDE_VALUE_DSP_0_DANGER_OVERRIDE_VALUE_BMSK                                                      0xc00
#define HWIO_QM_DANGER_OVERRIDE_VALUE_DSP_0_DANGER_OVERRIDE_VALUE_SHFT                                                        0xa
#define HWIO_QM_DANGER_OVERRIDE_VALUE_MODEM_DANGER_OVERRIDE_VALUE_BMSK                                                      0x300
#define HWIO_QM_DANGER_OVERRIDE_VALUE_MODEM_DANGER_OVERRIDE_VALUE_SHFT                                                        0x8
#define HWIO_QM_DANGER_OVERRIDE_VALUE_VENUS_DANGER_OVERRIDE_VALUE_BMSK                                                       0xc0
#define HWIO_QM_DANGER_OVERRIDE_VALUE_VENUS_DANGER_OVERRIDE_VALUE_SHFT                                                        0x6
#define HWIO_QM_DANGER_OVERRIDE_VALUE_MDP_DANGER_OVERRIDE_VALUE_BMSK                                                         0x30
#define HWIO_QM_DANGER_OVERRIDE_VALUE_MDP_DANGER_OVERRIDE_VALUE_SHFT                                                          0x4
#define HWIO_QM_DANGER_OVERRIDE_VALUE_VFE1_DANGER_OVERRIDE_VALUE_BMSK                                                         0xc
#define HWIO_QM_DANGER_OVERRIDE_VALUE_VFE1_DANGER_OVERRIDE_VALUE_SHFT                                                         0x2
#define HWIO_QM_DANGER_OVERRIDE_VALUE_VFE0_DANGER_OVERRIDE_VALUE_BMSK                                                         0x3
#define HWIO_QM_DANGER_OVERRIDE_VALUE_VFE0_DANGER_OVERRIDE_VALUE_SHFT                                                         0x0

#define HWIO_QM_DANGER_OVERRIDE_EN_ADDR                                                                                (QM_REG_BASE      + 0x00001a68)
#define HWIO_QM_DANGER_OVERRIDE_EN_RMSK                                                                                    0x1fff
#define HWIO_QM_DANGER_OVERRIDE_EN_IN          \
        in_dword_masked(HWIO_QM_DANGER_OVERRIDE_EN_ADDR, HWIO_QM_DANGER_OVERRIDE_EN_RMSK)
#define HWIO_QM_DANGER_OVERRIDE_EN_INM(m)      \
        in_dword_masked(HWIO_QM_DANGER_OVERRIDE_EN_ADDR, m)
#define HWIO_QM_DANGER_OVERRIDE_EN_OUT(v)      \
        out_dword(HWIO_QM_DANGER_OVERRIDE_EN_ADDR,v)
#define HWIO_QM_DANGER_OVERRIDE_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_DANGER_OVERRIDE_EN_ADDR,m,v,HWIO_QM_DANGER_OVERRIDE_EN_IN)
#define HWIO_QM_DANGER_OVERRIDE_EN_DSP_3_OTHER_DANGER_OVERRIDE_EN_BMSK                                                     0x1000
#define HWIO_QM_DANGER_OVERRIDE_EN_DSP_3_OTHER_DANGER_OVERRIDE_EN_SHFT                                                        0xc
#define HWIO_QM_DANGER_OVERRIDE_EN_DSP_2_OTHER_DANGER_OVERRIDE_EN_BMSK                                                      0x800
#define HWIO_QM_DANGER_OVERRIDE_EN_DSP_2_OTHER_DANGER_OVERRIDE_EN_SHFT                                                        0xb
#define HWIO_QM_DANGER_OVERRIDE_EN_DSP_1_OTHER_DANGER_OVERRIDE_EN_BMSK                                                      0x400
#define HWIO_QM_DANGER_OVERRIDE_EN_DSP_1_OTHER_DANGER_OVERRIDE_EN_SHFT                                                        0xa
#define HWIO_QM_DANGER_OVERRIDE_EN_DSP_0_OTHER_DANGER_OVERRIDE_EN_BMSK                                                      0x200
#define HWIO_QM_DANGER_OVERRIDE_EN_DSP_0_OTHER_DANGER_OVERRIDE_EN_SHFT                                                        0x9
#define HWIO_QM_DANGER_OVERRIDE_EN_DSP_3_DANGER_OVERRIDE_EN_BMSK                                                            0x100
#define HWIO_QM_DANGER_OVERRIDE_EN_DSP_3_DANGER_OVERRIDE_EN_SHFT                                                              0x8
#define HWIO_QM_DANGER_OVERRIDE_EN_DSP_2_DANGER_OVERRIDE_EN_BMSK                                                             0x80
#define HWIO_QM_DANGER_OVERRIDE_EN_DSP_2_DANGER_OVERRIDE_EN_SHFT                                                              0x7
#define HWIO_QM_DANGER_OVERRIDE_EN_DSP_1_DANGER_OVERRIDE_EN_BMSK                                                             0x40
#define HWIO_QM_DANGER_OVERRIDE_EN_DSP_1_DANGER_OVERRIDE_EN_SHFT                                                              0x6
#define HWIO_QM_DANGER_OVERRIDE_EN_DSP_0_DANGER_OVERRIDE_EN_BMSK                                                             0x20
#define HWIO_QM_DANGER_OVERRIDE_EN_DSP_0_DANGER_OVERRIDE_EN_SHFT                                                              0x5
#define HWIO_QM_DANGER_OVERRIDE_EN_MODEM_DANGER_OVERRIDE_EN_BMSK                                                             0x10
#define HWIO_QM_DANGER_OVERRIDE_EN_MODEM_DANGER_OVERRIDE_EN_SHFT                                                              0x4
#define HWIO_QM_DANGER_OVERRIDE_EN_VENUS_DANGER_OVERRIDE_EN_BMSK                                                              0x8
#define HWIO_QM_DANGER_OVERRIDE_EN_VENUS_DANGER_OVERRIDE_EN_SHFT                                                              0x3
#define HWIO_QM_DANGER_OVERRIDE_EN_MDP_DANGER_OVERRIDE_EN_BMSK                                                                0x4
#define HWIO_QM_DANGER_OVERRIDE_EN_MDP_DANGER_OVERRIDE_EN_SHFT                                                                0x2
#define HWIO_QM_DANGER_OVERRIDE_EN_VFE1_DANGER_OVERRIDE_EN_BMSK                                                               0x2
#define HWIO_QM_DANGER_OVERRIDE_EN_VFE1_DANGER_OVERRIDE_EN_SHFT                                                               0x1
#define HWIO_QM_DANGER_OVERRIDE_EN_VFE0_DANGER_OVERRIDE_EN_BMSK                                                               0x1
#define HWIO_QM_DANGER_OVERRIDE_EN_VFE0_DANGER_OVERRIDE_EN_SHFT                                                               0x0

#define HWIO_QM_SW_DANGER_OVERRIDE_VALUE_ADDR                                                                          (QM_REG_BASE      + 0x00001a6c)
#define HWIO_QM_SW_DANGER_OVERRIDE_VALUE_RMSK                                                                          0xc03fffff
#define HWIO_QM_SW_DANGER_OVERRIDE_VALUE_IN          \
        in_dword_masked(HWIO_QM_SW_DANGER_OVERRIDE_VALUE_ADDR, HWIO_QM_SW_DANGER_OVERRIDE_VALUE_RMSK)
#define HWIO_QM_SW_DANGER_OVERRIDE_VALUE_INM(m)      \
        in_dword_masked(HWIO_QM_SW_DANGER_OVERRIDE_VALUE_ADDR, m)
#define HWIO_QM_SW_DANGER_OVERRIDE_VALUE_OUT(v)      \
        out_dword(HWIO_QM_SW_DANGER_OVERRIDE_VALUE_ADDR,v)
#define HWIO_QM_SW_DANGER_OVERRIDE_VALUE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_SW_DANGER_OVERRIDE_VALUE_ADDR,m,v,HWIO_QM_SW_DANGER_OVERRIDE_VALUE_IN)
#define HWIO_QM_SW_DANGER_OVERRIDE_VALUE_SYSTEM_DANGER_SW_DANGER_OVERRIDE_VALUE_BMSK                                   0xc0000000
#define HWIO_QM_SW_DANGER_OVERRIDE_VALUE_SYSTEM_DANGER_SW_DANGER_OVERRIDE_VALUE_SHFT                                         0x1e
#define HWIO_QM_SW_DANGER_OVERRIDE_VALUE_CLNT_10_SW_DANGER_OVERRIDE_VALUE_BMSK                                           0x300000
#define HWIO_QM_SW_DANGER_OVERRIDE_VALUE_CLNT_10_SW_DANGER_OVERRIDE_VALUE_SHFT                                               0x14
#define HWIO_QM_SW_DANGER_OVERRIDE_VALUE_CLNT_9_SW_DANGER_OVERRIDE_VALUE_BMSK                                             0xc0000
#define HWIO_QM_SW_DANGER_OVERRIDE_VALUE_CLNT_9_SW_DANGER_OVERRIDE_VALUE_SHFT                                                0x12
#define HWIO_QM_SW_DANGER_OVERRIDE_VALUE_CLNT_8_SW_DANGER_OVERRIDE_VALUE_BMSK                                             0x30000
#define HWIO_QM_SW_DANGER_OVERRIDE_VALUE_CLNT_8_SW_DANGER_OVERRIDE_VALUE_SHFT                                                0x10
#define HWIO_QM_SW_DANGER_OVERRIDE_VALUE_CLNT_7_SW_DANGER_OVERRIDE_VALUE_BMSK                                              0xc000
#define HWIO_QM_SW_DANGER_OVERRIDE_VALUE_CLNT_7_SW_DANGER_OVERRIDE_VALUE_SHFT                                                 0xe
#define HWIO_QM_SW_DANGER_OVERRIDE_VALUE_CLNT_6_SW_DANGER_OVERRIDE_VALUE_BMSK                                              0x3000
#define HWIO_QM_SW_DANGER_OVERRIDE_VALUE_CLNT_6_SW_DANGER_OVERRIDE_VALUE_SHFT                                                 0xc
#define HWIO_QM_SW_DANGER_OVERRIDE_VALUE_CLNT_5_SW_DANGER_OVERRIDE_VALUE_BMSK                                               0xc00
#define HWIO_QM_SW_DANGER_OVERRIDE_VALUE_CLNT_5_SW_DANGER_OVERRIDE_VALUE_SHFT                                                 0xa
#define HWIO_QM_SW_DANGER_OVERRIDE_VALUE_CLNT_4_SW_DANGER_OVERRIDE_VALUE_BMSK                                               0x300
#define HWIO_QM_SW_DANGER_OVERRIDE_VALUE_CLNT_4_SW_DANGER_OVERRIDE_VALUE_SHFT                                                 0x8
#define HWIO_QM_SW_DANGER_OVERRIDE_VALUE_CLNT_3_SW_DANGER_OVERRIDE_VALUE_BMSK                                                0xc0
#define HWIO_QM_SW_DANGER_OVERRIDE_VALUE_CLNT_3_SW_DANGER_OVERRIDE_VALUE_SHFT                                                 0x6
#define HWIO_QM_SW_DANGER_OVERRIDE_VALUE_CLNT_2_SW_DANGER_OVERRIDE_VALUE_BMSK                                                0x30
#define HWIO_QM_SW_DANGER_OVERRIDE_VALUE_CLNT_2_SW_DANGER_OVERRIDE_VALUE_SHFT                                                 0x4
#define HWIO_QM_SW_DANGER_OVERRIDE_VALUE_CLNT_1_SW_DANGER_OVERRIDE_VALUE_BMSK                                                 0xc
#define HWIO_QM_SW_DANGER_OVERRIDE_VALUE_CLNT_1_SW_DANGER_OVERRIDE_VALUE_SHFT                                                 0x2
#define HWIO_QM_SW_DANGER_OVERRIDE_VALUE_CLNT_0_SW_DANGER_OVERRIDE_VALUE_BMSK                                                 0x3
#define HWIO_QM_SW_DANGER_OVERRIDE_VALUE_CLNT_0_SW_DANGER_OVERRIDE_VALUE_SHFT                                                 0x0

#define HWIO_QM_SW_DANGER_ADDR                                                                                         (QM_REG_BASE      + 0x00001a70)
#define HWIO_QM_SW_DANGER_RMSK                                                                                         0xc03fffff
#define HWIO_QM_SW_DANGER_IN          \
        in_dword_masked(HWIO_QM_SW_DANGER_ADDR, HWIO_QM_SW_DANGER_RMSK)
#define HWIO_QM_SW_DANGER_INM(m)      \
        in_dword_masked(HWIO_QM_SW_DANGER_ADDR, m)
#define HWIO_QM_SW_DANGER_OUT(v)      \
        out_dword(HWIO_QM_SW_DANGER_ADDR,v)
#define HWIO_QM_SW_DANGER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_SW_DANGER_ADDR,m,v,HWIO_QM_SW_DANGER_IN)
#define HWIO_QM_SW_DANGER_SYSTEM_DANGER_SW_DANGER_BMSK                                                                 0xc0000000
#define HWIO_QM_SW_DANGER_SYSTEM_DANGER_SW_DANGER_SHFT                                                                       0x1e
#define HWIO_QM_SW_DANGER_CLNT_10_SW_DANGER_BMSK                                                                         0x300000
#define HWIO_QM_SW_DANGER_CLNT_10_SW_DANGER_SHFT                                                                             0x14
#define HWIO_QM_SW_DANGER_CLNT_9_SW_DANGER_BMSK                                                                           0xc0000
#define HWIO_QM_SW_DANGER_CLNT_9_SW_DANGER_SHFT                                                                              0x12
#define HWIO_QM_SW_DANGER_CLNT_8_SW_DANGER_BMSK                                                                           0x30000
#define HWIO_QM_SW_DANGER_CLNT_8_SW_DANGER_SHFT                                                                              0x10
#define HWIO_QM_SW_DANGER_CLNT_7_SW_DANGER_BMSK                                                                            0xc000
#define HWIO_QM_SW_DANGER_CLNT_7_SW_DANGER_SHFT                                                                               0xe
#define HWIO_QM_SW_DANGER_CLNT_6_SW_DANGER_BMSK                                                                            0x3000
#define HWIO_QM_SW_DANGER_CLNT_6_SW_DANGER_SHFT                                                                               0xc
#define HWIO_QM_SW_DANGER_CLNT_5_SW_DANGER_BMSK                                                                             0xc00
#define HWIO_QM_SW_DANGER_CLNT_5_SW_DANGER_SHFT                                                                               0xa
#define HWIO_QM_SW_DANGER_CLNT_4_SW_DANGER_BMSK                                                                             0x300
#define HWIO_QM_SW_DANGER_CLNT_4_SW_DANGER_SHFT                                                                               0x8
#define HWIO_QM_SW_DANGER_CLNT_3_SW_DANGER_BMSK                                                                              0xc0
#define HWIO_QM_SW_DANGER_CLNT_3_SW_DANGER_SHFT                                                                               0x6
#define HWIO_QM_SW_DANGER_CLNT_2_SW_DANGER_BMSK                                                                              0x30
#define HWIO_QM_SW_DANGER_CLNT_2_SW_DANGER_SHFT                                                                               0x4
#define HWIO_QM_SW_DANGER_CLNT_1_SW_DANGER_BMSK                                                                               0xc
#define HWIO_QM_SW_DANGER_CLNT_1_SW_DANGER_SHFT                                                                               0x2
#define HWIO_QM_SW_DANGER_CLNT_0_SW_DANGER_BMSK                                                                               0x3
#define HWIO_QM_SW_DANGER_CLNT_0_SW_DANGER_SHFT                                                                               0x0

#define HWIO_QM_SW_DANGER_OVERRIDE_EN_ADDR                                                                             (QM_REG_BASE      + 0x00001a74)
#define HWIO_QM_SW_DANGER_OVERRIDE_EN_RMSK                                                                             0x800007ff
#define HWIO_QM_SW_DANGER_OVERRIDE_EN_IN          \
        in_dword_masked(HWIO_QM_SW_DANGER_OVERRIDE_EN_ADDR, HWIO_QM_SW_DANGER_OVERRIDE_EN_RMSK)
#define HWIO_QM_SW_DANGER_OVERRIDE_EN_INM(m)      \
        in_dword_masked(HWIO_QM_SW_DANGER_OVERRIDE_EN_ADDR, m)
#define HWIO_QM_SW_DANGER_OVERRIDE_EN_OUT(v)      \
        out_dword(HWIO_QM_SW_DANGER_OVERRIDE_EN_ADDR,v)
#define HWIO_QM_SW_DANGER_OVERRIDE_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_SW_DANGER_OVERRIDE_EN_ADDR,m,v,HWIO_QM_SW_DANGER_OVERRIDE_EN_IN)
#define HWIO_QM_SW_DANGER_OVERRIDE_EN_SYSTEM_DANGER_SW_DANGER_OVERRIDE_EN_BMSK                                         0x80000000
#define HWIO_QM_SW_DANGER_OVERRIDE_EN_SYSTEM_DANGER_SW_DANGER_OVERRIDE_EN_SHFT                                               0x1f
#define HWIO_QM_SW_DANGER_OVERRIDE_EN_CLNT_10_SW_DANGER_OVERRIDE_EN_BMSK                                                    0x400
#define HWIO_QM_SW_DANGER_OVERRIDE_EN_CLNT_10_SW_DANGER_OVERRIDE_EN_SHFT                                                      0xa
#define HWIO_QM_SW_DANGER_OVERRIDE_EN_CLNT_9_SW_DANGER_OVERRIDE_EN_BMSK                                                     0x200
#define HWIO_QM_SW_DANGER_OVERRIDE_EN_CLNT_9_SW_DANGER_OVERRIDE_EN_SHFT                                                       0x9
#define HWIO_QM_SW_DANGER_OVERRIDE_EN_CLNT_8_SW_DANGER_OVERRIDE_EN_BMSK                                                     0x100
#define HWIO_QM_SW_DANGER_OVERRIDE_EN_CLNT_8_SW_DANGER_OVERRIDE_EN_SHFT                                                       0x8
#define HWIO_QM_SW_DANGER_OVERRIDE_EN_CLNT_7_SW_DANGER_OVERRIDE_EN_BMSK                                                      0x80
#define HWIO_QM_SW_DANGER_OVERRIDE_EN_CLNT_7_SW_DANGER_OVERRIDE_EN_SHFT                                                       0x7
#define HWIO_QM_SW_DANGER_OVERRIDE_EN_CLNT_6_SW_DANGER_OVERRIDE_EN_BMSK                                                      0x40
#define HWIO_QM_SW_DANGER_OVERRIDE_EN_CLNT_6_SW_DANGER_OVERRIDE_EN_SHFT                                                       0x6
#define HWIO_QM_SW_DANGER_OVERRIDE_EN_CLNT_5_SW_DANGER_OVERRIDE_EN_BMSK                                                      0x20
#define HWIO_QM_SW_DANGER_OVERRIDE_EN_CLNT_5_SW_DANGER_OVERRIDE_EN_SHFT                                                       0x5
#define HWIO_QM_SW_DANGER_OVERRIDE_EN_CLNT_4_SW_DANGER_OVERRIDE_EN_BMSK                                                      0x10
#define HWIO_QM_SW_DANGER_OVERRIDE_EN_CLNT_4_SW_DANGER_OVERRIDE_EN_SHFT                                                       0x4
#define HWIO_QM_SW_DANGER_OVERRIDE_EN_CLNT_3_SW_DANGER_OVERRIDE_EN_BMSK                                                       0x8
#define HWIO_QM_SW_DANGER_OVERRIDE_EN_CLNT_3_SW_DANGER_OVERRIDE_EN_SHFT                                                       0x3
#define HWIO_QM_SW_DANGER_OVERRIDE_EN_CLNT_2_SW_DANGER_OVERRIDE_EN_BMSK                                                       0x4
#define HWIO_QM_SW_DANGER_OVERRIDE_EN_CLNT_2_SW_DANGER_OVERRIDE_EN_SHFT                                                       0x2
#define HWIO_QM_SW_DANGER_OVERRIDE_EN_CLNT_1_SW_DANGER_OVERRIDE_EN_BMSK                                                       0x2
#define HWIO_QM_SW_DANGER_OVERRIDE_EN_CLNT_1_SW_DANGER_OVERRIDE_EN_SHFT                                                       0x1
#define HWIO_QM_SW_DANGER_OVERRIDE_EN_CLNT_0_SW_DANGER_OVERRIDE_EN_BMSK                                                       0x1
#define HWIO_QM_SW_DANGER_OVERRIDE_EN_CLNT_0_SW_DANGER_OVERRIDE_EN_SHFT                                                       0x0

#define HWIO_QM_BIMC_QOS_CFG_ADDR                                                                                      (QM_REG_BASE      + 0x00001a90)
#define HWIO_QM_BIMC_QOS_CFG_RMSK                                                                                             0xf
#define HWIO_QM_BIMC_QOS_CFG_IN          \
        in_dword_masked(HWIO_QM_BIMC_QOS_CFG_ADDR, HWIO_QM_BIMC_QOS_CFG_RMSK)
#define HWIO_QM_BIMC_QOS_CFG_INM(m)      \
        in_dword_masked(HWIO_QM_BIMC_QOS_CFG_ADDR, m)
#define HWIO_QM_BIMC_QOS_CFG_OUT(v)      \
        out_dword(HWIO_QM_BIMC_QOS_CFG_ADDR,v)
#define HWIO_QM_BIMC_QOS_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_BIMC_QOS_CFG_ADDR,m,v,HWIO_QM_BIMC_QOS_CFG_IN)
#define HWIO_QM_BIMC_QOS_CFG_PIMEM_QOS_SEL_BMSK                                                                               0x8
#define HWIO_QM_BIMC_QOS_CFG_PIMEM_QOS_SEL_SHFT                                                                               0x3
#define HWIO_QM_BIMC_QOS_CFG_MDSP_QOS_SEL_BMSK                                                                                0x4
#define HWIO_QM_BIMC_QOS_CFG_MDSP_QOS_SEL_SHFT                                                                                0x2
#define HWIO_QM_BIMC_QOS_CFG_MNOC_QOS_SEL_BMSK                                                                                0x2
#define HWIO_QM_BIMC_QOS_CFG_MNOC_QOS_SEL_SHFT                                                                                0x1
#define HWIO_QM_BIMC_QOS_CFG_SNOC_QOS_SEL_BMSK                                                                                0x1
#define HWIO_QM_BIMC_QOS_CFG_SNOC_QOS_SEL_SHFT                                                                                0x0

#define HWIO_QM_SYSTEM_DANGER_SU_CFG_ADDR                                                                              (QM_REG_BASE      + 0x00001a94)
#define HWIO_QM_SYSTEM_DANGER_SU_CFG_RMSK                                                                                     0x7
#define HWIO_QM_SYSTEM_DANGER_SU_CFG_IN          \
        in_dword_masked(HWIO_QM_SYSTEM_DANGER_SU_CFG_ADDR, HWIO_QM_SYSTEM_DANGER_SU_CFG_RMSK)
#define HWIO_QM_SYSTEM_DANGER_SU_CFG_INM(m)      \
        in_dword_masked(HWIO_QM_SYSTEM_DANGER_SU_CFG_ADDR, m)
#define HWIO_QM_SYSTEM_DANGER_SU_CFG_OUT(v)      \
        out_dword(HWIO_QM_SYSTEM_DANGER_SU_CFG_ADDR,v)
#define HWIO_QM_SYSTEM_DANGER_SU_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_SYSTEM_DANGER_SU_CFG_ADDR,m,v,HWIO_QM_SYSTEM_DANGER_SU_CFG_IN)
#define HWIO_QM_SYSTEM_DANGER_SU_CFG_SYSTEM_DANGER_QOS_ASSIST_REQ_MODE_3_BMSK                                                 0x4
#define HWIO_QM_SYSTEM_DANGER_SU_CFG_SYSTEM_DANGER_QOS_ASSIST_REQ_MODE_3_SHFT                                                 0x2
#define HWIO_QM_SYSTEM_DANGER_SU_CFG_SYSTEM_DANGER_QOS_ASSIST_REQ_MODE_2_BMSK                                                 0x2
#define HWIO_QM_SYSTEM_DANGER_SU_CFG_SYSTEM_DANGER_QOS_ASSIST_REQ_MODE_2_SHFT                                                 0x1
#define HWIO_QM_SYSTEM_DANGER_SU_CFG_SYSTEM_DANGER_QOS_ASSIST_REQ_MODE_1_BMSK                                                 0x1
#define HWIO_QM_SYSTEM_DANGER_SU_CFG_SYSTEM_DANGER_QOS_ASSIST_REQ_MODE_1_SHFT                                                 0x0

#define HWIO_QM_SYSTEM_DANGER_SUF_QOS_n_ADDR(n)                                                                        (QM_REG_BASE      + 0x00001a98 + 0x4 * (n))
#define HWIO_QM_SYSTEM_DANGER_SUF_QOS_n_RMSK                                                                               0x87ff
#define HWIO_QM_SYSTEM_DANGER_SUF_QOS_n_MAXn                                                                                    3
#define HWIO_QM_SYSTEM_DANGER_SUF_QOS_n_INI(n)        \
        in_dword_masked(HWIO_QM_SYSTEM_DANGER_SUF_QOS_n_ADDR(n), HWIO_QM_SYSTEM_DANGER_SUF_QOS_n_RMSK)
#define HWIO_QM_SYSTEM_DANGER_SUF_QOS_n_INMI(n,mask)    \
        in_dword_masked(HWIO_QM_SYSTEM_DANGER_SUF_QOS_n_ADDR(n), mask)
#define HWIO_QM_SYSTEM_DANGER_SUF_QOS_n_OUTI(n,val)    \
        out_dword(HWIO_QM_SYSTEM_DANGER_SUF_QOS_n_ADDR(n),val)
#define HWIO_QM_SYSTEM_DANGER_SUF_QOS_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QM_SYSTEM_DANGER_SUF_QOS_n_ADDR(n),mask,val,HWIO_QM_SYSTEM_DANGER_SUF_QOS_n_INI(n))
#define HWIO_QM_SYSTEM_DANGER_SUF_QOS_n_THRES_FREQ_EQ_BMSK                                                                 0x8000
#define HWIO_QM_SYSTEM_DANGER_SUF_QOS_n_THRES_FREQ_EQ_SHFT                                                                    0xf
#define HWIO_QM_SYSTEM_DANGER_SUF_QOS_n_THRES_FREQ_BMSK                                                                     0x700
#define HWIO_QM_SYSTEM_DANGER_SUF_QOS_n_THRES_FREQ_SHFT                                                                       0x8
#define HWIO_QM_SYSTEM_DANGER_SUF_QOS_n_THRES_SU_H_BMSK                                                                      0xf0
#define HWIO_QM_SYSTEM_DANGER_SUF_QOS_n_THRES_SU_H_SHFT                                                                       0x4
#define HWIO_QM_SYSTEM_DANGER_SUF_QOS_n_THRES_SU_L_BMSK                                                                       0xf
#define HWIO_QM_SYSTEM_DANGER_SUF_QOS_n_THRES_SU_L_SHFT                                                                       0x0

#define HWIO_QM_SYSTEM_DANGER_AD_QOS_n_ADDR(n)                                                                         (QM_REG_BASE      + 0x00001aa4 + 0x4 * (n))
#define HWIO_QM_SYSTEM_DANGER_AD_QOS_n_RMSK                                                                            0xff00008f
#define HWIO_QM_SYSTEM_DANGER_AD_QOS_n_MAXn                                                                                     3
#define HWIO_QM_SYSTEM_DANGER_AD_QOS_n_INI(n)        \
        in_dword_masked(HWIO_QM_SYSTEM_DANGER_AD_QOS_n_ADDR(n), HWIO_QM_SYSTEM_DANGER_AD_QOS_n_RMSK)
#define HWIO_QM_SYSTEM_DANGER_AD_QOS_n_INMI(n,mask)    \
        in_dword_masked(HWIO_QM_SYSTEM_DANGER_AD_QOS_n_ADDR(n), mask)
#define HWIO_QM_SYSTEM_DANGER_AD_QOS_n_OUTI(n,val)    \
        out_dword(HWIO_QM_SYSTEM_DANGER_AD_QOS_n_ADDR(n),val)
#define HWIO_QM_SYSTEM_DANGER_AD_QOS_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QM_SYSTEM_DANGER_AD_QOS_n_ADDR(n),mask,val,HWIO_QM_SYSTEM_DANGER_AD_QOS_n_INI(n))
#define HWIO_QM_SYSTEM_DANGER_AD_QOS_n_AGG_BOOLEAN_FUNCTION_BMSK                                                       0xff000000
#define HWIO_QM_SYSTEM_DANGER_AD_QOS_n_AGG_BOOLEAN_FUNCTION_SHFT                                                             0x18
#define HWIO_QM_SYSTEM_DANGER_AD_QOS_n_THRES_DANGER_EQ_BMSK                                                                  0x80
#define HWIO_QM_SYSTEM_DANGER_AD_QOS_n_THRES_DANGER_EQ_SHFT                                                                   0x7
#define HWIO_QM_SYSTEM_DANGER_AD_QOS_n_THRES_DANGER_BMSK                                                                      0xf
#define HWIO_QM_SYSTEM_DANGER_AD_QOS_n_THRES_DANGER_SHFT                                                                      0x0

#define HWIO_QM_TPDM_BC_MISSION_MODE_CNTRL_ADDR                                                                        (QM_REG_BASE      + 0x00001af0)
#define HWIO_QM_TPDM_BC_MISSION_MODE_CNTRL_RMSK                                                                               0x3
#define HWIO_QM_TPDM_BC_MISSION_MODE_CNTRL_IN          \
        in_dword_masked(HWIO_QM_TPDM_BC_MISSION_MODE_CNTRL_ADDR, HWIO_QM_TPDM_BC_MISSION_MODE_CNTRL_RMSK)
#define HWIO_QM_TPDM_BC_MISSION_MODE_CNTRL_INM(m)      \
        in_dword_masked(HWIO_QM_TPDM_BC_MISSION_MODE_CNTRL_ADDR, m)
#define HWIO_QM_TPDM_BC_MISSION_MODE_CNTRL_OUT(v)      \
        out_dword(HWIO_QM_TPDM_BC_MISSION_MODE_CNTRL_ADDR,v)
#define HWIO_QM_TPDM_BC_MISSION_MODE_CNTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_TPDM_BC_MISSION_MODE_CNTRL_ADDR,m,v,HWIO_QM_TPDM_BC_MISSION_MODE_CNTRL_IN)
#define HWIO_QM_TPDM_BC_MISSION_MODE_CNTRL_MISSION_MODE_CAPTURE_BMSK                                                          0x2
#define HWIO_QM_TPDM_BC_MISSION_MODE_CNTRL_MISSION_MODE_CAPTURE_SHFT                                                          0x1
#define HWIO_QM_TPDM_BC_MISSION_MODE_CNTRL_MISSION_MODE_EN_BMSK                                                               0x1
#define HWIO_QM_TPDM_BC_MISSION_MODE_CNTRL_MISSION_MODE_EN_SHFT                                                               0x0

#define HWIO_QM_TPDM_BC_STATISTICS_DURATION_CNTR_THR_ADDR                                                              (QM_REG_BASE      + 0x00001af4)
#define HWIO_QM_TPDM_BC_STATISTICS_DURATION_CNTR_THR_RMSK                                                              0xffffffff
#define HWIO_QM_TPDM_BC_STATISTICS_DURATION_CNTR_THR_IN          \
        in_dword_masked(HWIO_QM_TPDM_BC_STATISTICS_DURATION_CNTR_THR_ADDR, HWIO_QM_TPDM_BC_STATISTICS_DURATION_CNTR_THR_RMSK)
#define HWIO_QM_TPDM_BC_STATISTICS_DURATION_CNTR_THR_INM(m)      \
        in_dword_masked(HWIO_QM_TPDM_BC_STATISTICS_DURATION_CNTR_THR_ADDR, m)
#define HWIO_QM_TPDM_BC_STATISTICS_DURATION_CNTR_THR_OUT(v)      \
        out_dword(HWIO_QM_TPDM_BC_STATISTICS_DURATION_CNTR_THR_ADDR,v)
#define HWIO_QM_TPDM_BC_STATISTICS_DURATION_CNTR_THR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_TPDM_BC_STATISTICS_DURATION_CNTR_THR_ADDR,m,v,HWIO_QM_TPDM_BC_STATISTICS_DURATION_CNTR_THR_IN)
#define HWIO_QM_TPDM_BC_STATISTICS_DURATION_CNTR_THR_STATISTICS_DURATION_CNTR_THR_BMSK                                 0xffffffff
#define HWIO_QM_TPDM_BC_STATISTICS_DURATION_CNTR_THR_STATISTICS_DURATION_CNTR_THR_SHFT                                        0x0

#define HWIO_QM_TPDM_BC_STATISTICS_DURATION_CNTR_READBACK_ADDR                                                         (QM_REG_BASE      + 0x00001af8)
#define HWIO_QM_TPDM_BC_STATISTICS_DURATION_CNTR_READBACK_RMSK                                                         0xffffffff
#define HWIO_QM_TPDM_BC_STATISTICS_DURATION_CNTR_READBACK_IN          \
        in_dword_masked(HWIO_QM_TPDM_BC_STATISTICS_DURATION_CNTR_READBACK_ADDR, HWIO_QM_TPDM_BC_STATISTICS_DURATION_CNTR_READBACK_RMSK)
#define HWIO_QM_TPDM_BC_STATISTICS_DURATION_CNTR_READBACK_INM(m)      \
        in_dword_masked(HWIO_QM_TPDM_BC_STATISTICS_DURATION_CNTR_READBACK_ADDR, m)
#define HWIO_QM_TPDM_BC_STATISTICS_DURATION_CNTR_READBACK_STATISTICS_DURATION_CNTR_READBACK_BMSK                       0xffffffff
#define HWIO_QM_TPDM_BC_STATISTICS_DURATION_CNTR_READBACK_STATISTICS_DURATION_CNTR_READBACK_SHFT                              0x0

#define HWIO_QM_TPDM_BC_STATISTICS_DURATION_STATUS_ADDR                                                                (QM_REG_BASE      + 0x00001afc)
#define HWIO_QM_TPDM_BC_STATISTICS_DURATION_STATUS_RMSK                                                                       0x3
#define HWIO_QM_TPDM_BC_STATISTICS_DURATION_STATUS_IN          \
        in_dword_masked(HWIO_QM_TPDM_BC_STATISTICS_DURATION_STATUS_ADDR, HWIO_QM_TPDM_BC_STATISTICS_DURATION_STATUS_RMSK)
#define HWIO_QM_TPDM_BC_STATISTICS_DURATION_STATUS_INM(m)      \
        in_dword_masked(HWIO_QM_TPDM_BC_STATISTICS_DURATION_STATUS_ADDR, m)
#define HWIO_QM_TPDM_BC_STATISTICS_DURATION_STATUS_STATISTICS_DURATION_CNTR_STURATED_BMSK                                     0x2
#define HWIO_QM_TPDM_BC_STATISTICS_DURATION_STATUS_STATISTICS_DURATION_CNTR_STURATED_SHFT                                     0x1
#define HWIO_QM_TPDM_BC_STATISTICS_DURATION_STATUS_STATISTICS_DURATION_CNTR_OVER_THR_BMSK                                     0x1
#define HWIO_QM_TPDM_BC_STATISTICS_DURATION_STATUS_STATISTICS_DURATION_CNTR_OVER_THR_SHFT                                     0x0

#define HWIO_QM_TPDM_BC_n_CNTR_READBACK_ADDR(n)                                                                        (QM_REG_BASE      + 0x00001b00 + 0x4 * (n))
#define HWIO_QM_TPDM_BC_n_CNTR_READBACK_RMSK                                                                           0xffffffff
#define HWIO_QM_TPDM_BC_n_CNTR_READBACK_MAXn                                                                                   31
#define HWIO_QM_TPDM_BC_n_CNTR_READBACK_INI(n)        \
        in_dword_masked(HWIO_QM_TPDM_BC_n_CNTR_READBACK_ADDR(n), HWIO_QM_TPDM_BC_n_CNTR_READBACK_RMSK)
#define HWIO_QM_TPDM_BC_n_CNTR_READBACK_INMI(n,mask)    \
        in_dword_masked(HWIO_QM_TPDM_BC_n_CNTR_READBACK_ADDR(n), mask)
#define HWIO_QM_TPDM_BC_n_CNTR_READBACK_CNTR_READBACK_BMSK                                                             0xffffffff
#define HWIO_QM_TPDM_BC_n_CNTR_READBACK_CNTR_READBACK_SHFT                                                                    0x0

#define HWIO_QM_DEBUG_BUS_CTLR_ADDR                                                                                    (QM_REG_BASE      + 0x00002008)
#define HWIO_QM_DEBUG_BUS_CTLR_RMSK                                                                                    0x80000f01
#define HWIO_QM_DEBUG_BUS_CTLR_IN          \
        in_dword_masked(HWIO_QM_DEBUG_BUS_CTLR_ADDR, HWIO_QM_DEBUG_BUS_CTLR_RMSK)
#define HWIO_QM_DEBUG_BUS_CTLR_INM(m)      \
        in_dword_masked(HWIO_QM_DEBUG_BUS_CTLR_ADDR, m)
#define HWIO_QM_DEBUG_BUS_CTLR_OUT(v)      \
        out_dword(HWIO_QM_DEBUG_BUS_CTLR_ADDR,v)
#define HWIO_QM_DEBUG_BUS_CTLR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_DEBUG_BUS_CTLR_ADDR,m,v,HWIO_QM_DEBUG_BUS_CTLR_IN)
#define HWIO_QM_DEBUG_BUS_CTLR_DEBUG_BUS_SIGNATURE_READBACK_BMSK                                                       0x80000000
#define HWIO_QM_DEBUG_BUS_CTLR_DEBUG_BUS_SIGNATURE_READBACK_SHFT                                                             0x1f
#define HWIO_QM_DEBUG_BUS_CTLR_QM_DEBUG_BUS_SEL_BMSK                                                                        0xf00
#define HWIO_QM_DEBUG_BUS_CTLR_QM_DEBUG_BUS_SEL_SHFT                                                                          0x8
#define HWIO_QM_DEBUG_BUS_CTLR_QM_DEBUG_BUS_EN_BMSK                                                                           0x1
#define HWIO_QM_DEBUG_BUS_CTLR_QM_DEBUG_BUS_EN_SHFT                                                                           0x0

#define HWIO_QM_DEBUG_BUS_SIGNATURE_ADDR                                                                               (QM_REG_BASE      + 0x0000200c)
#define HWIO_QM_DEBUG_BUS_SIGNATURE_RMSK                                                                                   0xffff
#define HWIO_QM_DEBUG_BUS_SIGNATURE_IN          \
        in_dword_masked(HWIO_QM_DEBUG_BUS_SIGNATURE_ADDR, HWIO_QM_DEBUG_BUS_SIGNATURE_RMSK)
#define HWIO_QM_DEBUG_BUS_SIGNATURE_INM(m)      \
        in_dword_masked(HWIO_QM_DEBUG_BUS_SIGNATURE_ADDR, m)
#define HWIO_QM_DEBUG_BUS_SIGNATURE_OUT(v)      \
        out_dword(HWIO_QM_DEBUG_BUS_SIGNATURE_ADDR,v)
#define HWIO_QM_DEBUG_BUS_SIGNATURE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_DEBUG_BUS_SIGNATURE_ADDR,m,v,HWIO_QM_DEBUG_BUS_SIGNATURE_IN)
#define HWIO_QM_DEBUG_BUS_SIGNATURE_DEBUG_BUS_SIGNATURE_BMSK                                                               0xffff
#define HWIO_QM_DEBUG_BUS_SIGNATURE_DEBUG_BUS_SIGNATURE_SHFT                                                                  0x0

#define HWIO_QM_DEBUG_BUS_READBACK_ADDR                                                                                (QM_REG_BASE      + 0x00002010)
#define HWIO_QM_DEBUG_BUS_READBACK_RMSK                                                                                0xffffffff
#define HWIO_QM_DEBUG_BUS_READBACK_IN          \
        in_dword_masked(HWIO_QM_DEBUG_BUS_READBACK_ADDR, HWIO_QM_DEBUG_BUS_READBACK_RMSK)
#define HWIO_QM_DEBUG_BUS_READBACK_INM(m)      \
        in_dword_masked(HWIO_QM_DEBUG_BUS_READBACK_ADDR, m)
#define HWIO_QM_DEBUG_BUS_READBACK_QM_DEBUG_BUS_READBACK_BMSK                                                          0xffffffff
#define HWIO_QM_DEBUG_BUS_READBACK_QM_DEBUG_BUS_READBACK_SHFT                                                                 0x0

#define HWIO_QM_TPDM_HWE_CTLR_ADDR                                                                                     (QM_REG_BASE      + 0x00002014)
#define HWIO_QM_TPDM_HWE_CTLR_RMSK                                                                                     0x80000000
#define HWIO_QM_TPDM_HWE_CTLR_IN          \
        in_dword_masked(HWIO_QM_TPDM_HWE_CTLR_ADDR, HWIO_QM_TPDM_HWE_CTLR_RMSK)
#define HWIO_QM_TPDM_HWE_CTLR_INM(m)      \
        in_dword_masked(HWIO_QM_TPDM_HWE_CTLR_ADDR, m)
#define HWIO_QM_TPDM_HWE_CTLR_OUT(v)      \
        out_dword(HWIO_QM_TPDM_HWE_CTLR_ADDR,v)
#define HWIO_QM_TPDM_HWE_CTLR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_TPDM_HWE_CTLR_ADDR,m,v,HWIO_QM_TPDM_HWE_CTLR_IN)
#define HWIO_QM_TPDM_HWE_CTLR_EN_BMSK                                                                                  0x80000000
#define HWIO_QM_TPDM_HWE_CTLR_EN_SHFT                                                                                        0x1f

#define HWIO_QM_HW_EVENTS_READBACK_ADDR                                                                                (QM_REG_BASE      + 0x00002018)
#define HWIO_QM_HW_EVENTS_READBACK_RMSK                                                                                0xffffffff
#define HWIO_QM_HW_EVENTS_READBACK_IN          \
        in_dword_masked(HWIO_QM_HW_EVENTS_READBACK_ADDR, HWIO_QM_HW_EVENTS_READBACK_RMSK)
#define HWIO_QM_HW_EVENTS_READBACK_INM(m)      \
        in_dword_masked(HWIO_QM_HW_EVENTS_READBACK_ADDR, m)
#define HWIO_QM_HW_EVENTS_READBACK_QM_HW_EVENTS_READBACK_BMSK                                                          0xffffffff
#define HWIO_QM_HW_EVENTS_READBACK_QM_HW_EVENTS_READBACK_SHFT                                                                 0x0

#define HWIO_QM_STM_MUX_SEL_n_ADDR(n)                                                                                  (QM_REG_BASE      + 0x00002020 + 0x4 * (n))
#define HWIO_QM_STM_MUX_SEL_n_RMSK                                                                                     0x80000007
#define HWIO_QM_STM_MUX_SEL_n_MAXn                                                                                             31
#define HWIO_QM_STM_MUX_SEL_n_INI(n)        \
        in_dword_masked(HWIO_QM_STM_MUX_SEL_n_ADDR(n), HWIO_QM_STM_MUX_SEL_n_RMSK)
#define HWIO_QM_STM_MUX_SEL_n_INMI(n,mask)    \
        in_dword_masked(HWIO_QM_STM_MUX_SEL_n_ADDR(n), mask)
#define HWIO_QM_STM_MUX_SEL_n_OUTI(n,val)    \
        out_dword(HWIO_QM_STM_MUX_SEL_n_ADDR(n),val)
#define HWIO_QM_STM_MUX_SEL_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_QM_STM_MUX_SEL_n_ADDR(n),mask,val,HWIO_QM_STM_MUX_SEL_n_INI(n))
#define HWIO_QM_STM_MUX_SEL_n_EN_BMSK                                                                                  0x80000000
#define HWIO_QM_STM_MUX_SEL_n_EN_SHFT                                                                                        0x1f
#define HWIO_QM_STM_MUX_SEL_n_SEL_BMSK                                                                                        0x7
#define HWIO_QM_STM_MUX_SEL_n_SEL_SHFT                                                                                        0x0

#define HWIO_QM_DT_STATUS_ADDR                                                                                         (QM_REG_BASE      + 0x00002200)
#define HWIO_QM_DT_STATUS_RMSK                                                                                                0x7
#define HWIO_QM_DT_STATUS_IN          \
        in_dword_masked(HWIO_QM_DT_STATUS_ADDR, HWIO_QM_DT_STATUS_RMSK)
#define HWIO_QM_DT_STATUS_INM(m)      \
        in_dword_masked(HWIO_QM_DT_STATUS_ADDR, m)
#define HWIO_QM_DT_STATUS_DT_POST_STALL_ACTIVE_READBACK_BMSK                                                                  0x4
#define HWIO_QM_DT_STATUS_DT_POST_STALL_ACTIVE_READBACK_SHFT                                                                  0x2
#define HWIO_QM_DT_STATUS_DT_PRE_STALL_ACTIVE_READBACK_BMSK                                                                   0x2
#define HWIO_QM_DT_STATUS_DT_PRE_STALL_ACTIVE_READBACK_SHFT                                                                   0x1
#define HWIO_QM_DT_STATUS_DT_ACK_BYPASS_EN_READBACK_BMSK                                                                      0x1
#define HWIO_QM_DT_STATUS_DT_ACK_BYPASS_EN_READBACK_SHFT                                                                      0x0

#define HWIO_QM_DT_PRE_STALL_CNTR_READBACK_ADDR                                                                        (QM_REG_BASE      + 0x00002204)
#define HWIO_QM_DT_PRE_STALL_CNTR_READBACK_RMSK                                                                           0xfffff
#define HWIO_QM_DT_PRE_STALL_CNTR_READBACK_IN          \
        in_dword_masked(HWIO_QM_DT_PRE_STALL_CNTR_READBACK_ADDR, HWIO_QM_DT_PRE_STALL_CNTR_READBACK_RMSK)
#define HWIO_QM_DT_PRE_STALL_CNTR_READBACK_INM(m)      \
        in_dword_masked(HWIO_QM_DT_PRE_STALL_CNTR_READBACK_ADDR, m)
#define HWIO_QM_DT_PRE_STALL_CNTR_READBACK_DT_PRE_STALL_CNTR_READBACK_BMSK                                                0xfffff
#define HWIO_QM_DT_PRE_STALL_CNTR_READBACK_DT_PRE_STALL_CNTR_READBACK_SHFT                                                    0x0

#define HWIO_QM_DT_POST_STALL_CNTR_READBACK_ADDR                                                                       (QM_REG_BASE      + 0x00002208)
#define HWIO_QM_DT_POST_STALL_CNTR_READBACK_RMSK                                                                          0xfffff
#define HWIO_QM_DT_POST_STALL_CNTR_READBACK_IN          \
        in_dword_masked(HWIO_QM_DT_POST_STALL_CNTR_READBACK_ADDR, HWIO_QM_DT_POST_STALL_CNTR_READBACK_RMSK)
#define HWIO_QM_DT_POST_STALL_CNTR_READBACK_INM(m)      \
        in_dword_masked(HWIO_QM_DT_POST_STALL_CNTR_READBACK_ADDR, m)
#define HWIO_QM_DT_POST_STALL_CNTR_READBACK_DT_POST_STALL_CNTR_READBACK_BMSK                                              0xfffff
#define HWIO_QM_DT_POST_STALL_CNTR_READBACK_DT_POST_STALL_CNTR_READBACK_SHFT                                                  0x0

#define HWIO_QM_OBS_DBG_ATB_CNTRL_ADDR                                                                                 (QM_REG_BASE      + 0x00003000)
#define HWIO_QM_OBS_DBG_ATB_CNTRL_RMSK                                                                                        0x1
#define HWIO_QM_OBS_DBG_ATB_CNTRL_IN          \
        in_dword_masked(HWIO_QM_OBS_DBG_ATB_CNTRL_ADDR, HWIO_QM_OBS_DBG_ATB_CNTRL_RMSK)
#define HWIO_QM_OBS_DBG_ATB_CNTRL_INM(m)      \
        in_dword_masked(HWIO_QM_OBS_DBG_ATB_CNTRL_ADDR, m)
#define HWIO_QM_OBS_DBG_ATB_CNTRL_OUT(v)      \
        out_dword(HWIO_QM_OBS_DBG_ATB_CNTRL_ADDR,v)
#define HWIO_QM_OBS_DBG_ATB_CNTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_OBS_DBG_ATB_CNTRL_ADDR,m,v,HWIO_QM_OBS_DBG_ATB_CNTRL_IN)
#define HWIO_QM_OBS_DBG_ATB_CNTRL_ATB_EN_BMSK                                                                                 0x1
#define HWIO_QM_OBS_DBG_ATB_CNTRL_ATB_EN_SHFT                                                                                 0x0

#define HWIO_QM_SECURE_SPARE_REGS_V2_ADDR                                                                              (QM_REG_BASE      + 0x00003004)
#define HWIO_QM_SECURE_SPARE_REGS_V2_RMSK                                                                              0xffffffff
#define HWIO_QM_SECURE_SPARE_REGS_V2_IN          \
        in_dword_masked(HWIO_QM_SECURE_SPARE_REGS_V2_ADDR, HWIO_QM_SECURE_SPARE_REGS_V2_RMSK)
#define HWIO_QM_SECURE_SPARE_REGS_V2_INM(m)      \
        in_dword_masked(HWIO_QM_SECURE_SPARE_REGS_V2_ADDR, m)
#define HWIO_QM_SECURE_SPARE_REGS_V2_OUT(v)      \
        out_dword(HWIO_QM_SECURE_SPARE_REGS_V2_ADDR,v)
#define HWIO_QM_SECURE_SPARE_REGS_V2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_QM_SECURE_SPARE_REGS_V2_ADDR,m,v,HWIO_QM_SECURE_SPARE_REGS_V2_IN)
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_31_BMSK                                                             0x80000000
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_31_SHFT                                                                   0x1f
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_30_BMSK                                                             0x40000000
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_30_SHFT                                                                   0x1e
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_29_BMSK                                                             0x20000000
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_29_SHFT                                                                   0x1d
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_28_BMSK                                                             0x10000000
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_28_SHFT                                                                   0x1c
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_27_BMSK                                                              0x8000000
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_27_SHFT                                                                   0x1b
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_26_BMSK                                                              0x4000000
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_26_SHFT                                                                   0x1a
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_25_BMSK                                                              0x2000000
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_25_SHFT                                                                   0x19
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_24_BMSK                                                              0x1000000
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_24_SHFT                                                                   0x18
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_23_BMSK                                                               0x800000
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_23_SHFT                                                                   0x17
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_22_BMSK                                                               0x400000
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_22_SHFT                                                                   0x16
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_21_BMSK                                                               0x200000
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_21_SHFT                                                                   0x15
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_20_BMSK                                                               0x100000
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_20_SHFT                                                                   0x14
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_19_BMSK                                                                0x80000
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_19_SHFT                                                                   0x13
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_18_BMSK                                                                0x40000
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_18_SHFT                                                                   0x12
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_17_BMSK                                                                0x20000
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_17_SHFT                                                                   0x11
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_16_BMSK                                                                0x10000
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_16_SHFT                                                                   0x10
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_15_BMSK                                                                 0x8000
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_15_SHFT                                                                    0xf
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_14_BMSK                                                                 0x4000
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_14_SHFT                                                                    0xe
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_13_BMSK                                                                 0x2000
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_13_SHFT                                                                    0xd
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_12_BMSK                                                                 0x1000
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_12_SHFT                                                                    0xc
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_11_BMSK                                                                  0x800
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_11_SHFT                                                                    0xb
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_10_BMSK                                                                  0x400
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_10_SHFT                                                                    0xa
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_9_BMSK                                                                   0x200
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_9_SHFT                                                                     0x9
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_8_BMSK                                                                   0x100
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_8_SHFT                                                                     0x8
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_7_BMSK                                                                    0x80
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_7_SHFT                                                                     0x7
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_6_BMSK                                                                    0x40
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_6_SHFT                                                                     0x6
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_5_BMSK                                                                    0x20
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_5_SHFT                                                                     0x5
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_4_BMSK                                                                    0x10
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_4_SHFT                                                                     0x4
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_3_BMSK                                                                     0x8
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_3_SHFT                                                                     0x3
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_2_BMSK                                                                     0x4
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_2_SHFT                                                                     0x2
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_1_BMSK                                                                     0x2
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_1_SHFT                                                                     0x1
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_0_BMSK                                                                     0x1
#define HWIO_QM_SECURE_SPARE_REGS_V2_SPARE_REG_BIT_0_SHFT                                                                     0x0


#endif /* __ICBCFG_HWIO_H__ */
