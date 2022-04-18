#ifndef __CLOCKSSCHWIO_H__
#define __CLOCKSSCHWIO_H__
/*
===========================================================================
*/
/**
  @file ClockSSCHWIO.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    MSM8998 (Nazgul) [nazgul_v1.0_p3q2r26.0]
 
  This file contains HWIO register definitions for the following modules:
    SSC_QDSP6V60SS_PUB
    SSC_QDSP6V60SS_CSR
    SSC_MCC_REGS

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

  $Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/clock/hw/msm8998/adsp/inc/ClockSSCHWIO.h#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $

  ===========================================================================
*/

#include <HALhwio.h>

extern uint32                      Clock_nHWIOBaseSSC;
#define SSC_BASE                   Clock_nHWIOBaseSSC


/*----------------------------------------------------------------------------
 * MODULE: SSC_QDSP6V60SS_PUB
 *--------------------------------------------------------------------------*/

#define SSC_QDSP6V60SS_PUB_REG_BASE                                                 (SSC_BASE      + 0x00400000)
#define SSC_QDSP6V60SS_PUB_REG_BASE_OFFS                                            0x00400000

#define HWIO_SSC_QDSP6SS_VERSION_ADDR                                               (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000000)
#define HWIO_SSC_QDSP6SS_VERSION_OFFS                                               (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000000)
#define HWIO_SSC_QDSP6SS_VERSION_RMSK                                               0xffffffff
#define HWIO_SSC_QDSP6SS_VERSION_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_VERSION_ADDR, HWIO_SSC_QDSP6SS_VERSION_RMSK)
#define HWIO_SSC_QDSP6SS_VERSION_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_VERSION_ADDR, m)
#define HWIO_SSC_QDSP6SS_VERSION_MAJOR_BMSK                                         0xf0000000
#define HWIO_SSC_QDSP6SS_VERSION_MAJOR_SHFT                                               0x1c
#define HWIO_SSC_QDSP6SS_VERSION_MINOR_BMSK                                          0xfff0000
#define HWIO_SSC_QDSP6SS_VERSION_MINOR_SHFT                                               0x10
#define HWIO_SSC_QDSP6SS_VERSION_STEP_BMSK                                              0xffff
#define HWIO_SSC_QDSP6SS_VERSION_STEP_SHFT                                                 0x0

#define HWIO_SSC_QDSP6SS_CONFIG_ID_ADDR                                             (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000004)
#define HWIO_SSC_QDSP6SS_CONFIG_ID_OFFS                                             (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000004)
#define HWIO_SSC_QDSP6SS_CONFIG_ID_RMSK                                             0xfff1ffff
#define HWIO_SSC_QDSP6SS_CONFIG_ID_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_CONFIG_ID_ADDR, HWIO_SSC_QDSP6SS_CONFIG_ID_RMSK)
#define HWIO_SSC_QDSP6SS_CONFIG_ID_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_CONFIG_ID_ADDR, m)
#define HWIO_SSC_QDSP6SS_CONFIG_ID_NUM_L2VIC_SRC_BMSK                               0xfff00000
#define HWIO_SSC_QDSP6SS_CONFIG_ID_NUM_L2VIC_SRC_SHFT                                     0x14
#define HWIO_SSC_QDSP6SS_CONFIG_ID_ZMEAS_PRESENT_BMSK                                  0x10000
#define HWIO_SSC_QDSP6SS_CONFIG_ID_ZMEAS_PRESENT_SHFT                                     0x10
#define HWIO_SSC_QDSP6SS_CONFIG_ID_PMIC_IF_PRESENT_BMSK                                 0x8000
#define HWIO_SSC_QDSP6SS_CONFIG_ID_PMIC_IF_PRESENT_SHFT                                    0xf
#define HWIO_SSC_QDSP6SS_CONFIG_ID_IN_SUBSYSTEM_BMSK                                    0x7000
#define HWIO_SSC_QDSP6SS_CONFIG_ID_IN_SUBSYSTEM_SHFT                                       0xc
#define HWIO_SSC_QDSP6SS_CONFIG_ID_LDO_PRESENT_BMSK                                      0x800
#define HWIO_SSC_QDSP6SS_CONFIG_ID_LDO_PRESENT_SHFT                                        0xb
#define HWIO_SSC_QDSP6SS_CONFIG_ID_BHS_PRESENT_BMSK                                      0x400
#define HWIO_SSC_QDSP6SS_CONFIG_ID_BHS_PRESENT_SHFT                                        0xa
#define HWIO_SSC_QDSP6SS_CONFIG_ID_PLL_VOTE_BMSK                                         0x200
#define HWIO_SSC_QDSP6SS_CONFIG_ID_PLL_VOTE_SHFT                                           0x9
#define HWIO_SSC_QDSP6SS_CONFIG_ID_PLL_PRESENT_BMSK                                      0x100
#define HWIO_SSC_QDSP6SS_CONFIG_ID_PLL_PRESENT_SHFT                                        0x8
#define HWIO_SSC_QDSP6SS_CONFIG_ID_CORE_TYPE_BMSK                                         0xf0
#define HWIO_SSC_QDSP6SS_CONFIG_ID_CORE_TYPE_SHFT                                          0x4
#define HWIO_SSC_QDSP6SS_CONFIG_ID_L2_SIZE_BMSK                                            0xf
#define HWIO_SSC_QDSP6SS_CONFIG_ID_L2_SIZE_SHFT                                            0x0

#define HWIO_SSC_QDSP6SS_RST_EVB_ADDR                                               (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000010)
#define HWIO_SSC_QDSP6SS_RST_EVB_OFFS                                               (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000010)
#define HWIO_SSC_QDSP6SS_RST_EVB_RMSK                                                0xffffff0
#define HWIO_SSC_QDSP6SS_RST_EVB_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_RST_EVB_ADDR, HWIO_SSC_QDSP6SS_RST_EVB_RMSK)
#define HWIO_SSC_QDSP6SS_RST_EVB_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_RST_EVB_ADDR, m)
#define HWIO_SSC_QDSP6SS_RST_EVB_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_RST_EVB_ADDR,v)
#define HWIO_SSC_QDSP6SS_RST_EVB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_RST_EVB_ADDR,m,v,HWIO_SSC_QDSP6SS_RST_EVB_IN)
#define HWIO_SSC_QDSP6SS_RST_EVB_EVB_BMSK                                            0xffffff0
#define HWIO_SSC_QDSP6SS_RST_EVB_EVB_SHFT                                                  0x4

#define HWIO_SSC_QDSP6SS_RESET_ADDR                                                 (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000014)
#define HWIO_SSC_QDSP6SS_RESET_OFFS                                                 (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000014)
#define HWIO_SSC_QDSP6SS_RESET_RMSK                                                     0x7ff7
#define HWIO_SSC_QDSP6SS_RESET_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_RESET_ADDR, HWIO_SSC_QDSP6SS_RESET_RMSK)
#define HWIO_SSC_QDSP6SS_RESET_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_RESET_ADDR, m)
#define HWIO_SSC_QDSP6SS_RESET_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_RESET_ADDR,v)
#define HWIO_SSC_QDSP6SS_RESET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_RESET_ADDR,m,v,HWIO_SSC_QDSP6SS_RESET_IN)
#define HWIO_SSC_QDSP6SS_RESET_CSI1_ARES_BMSK                                           0x4000
#define HWIO_SSC_QDSP6SS_RESET_CSI1_ARES_SHFT                                              0xe
#define HWIO_SSC_QDSP6SS_RESET_CSI0_ARES_BMSK                                           0x2000
#define HWIO_SSC_QDSP6SS_RESET_CSI0_ARES_SHFT                                              0xd
#define HWIO_SSC_QDSP6SS_RESET_CORE_ARCH_ARES_BMSK                                      0x1000
#define HWIO_SSC_QDSP6SS_RESET_CORE_ARCH_ARES_SHFT                                         0xc
#define HWIO_SSC_QDSP6SS_RESET_CORE_NONRET_ARES_BMSK                                     0x800
#define HWIO_SSC_QDSP6SS_RESET_CORE_NONRET_ARES_SHFT                                       0xb
#define HWIO_SSC_QDSP6SS_RESET_CORE_RET_ARES_BMSK                                        0x400
#define HWIO_SSC_QDSP6SS_RESET_CORE_RET_ARES_SHFT                                          0xa
#define HWIO_SSC_QDSP6SS_RESET_AXIM2_ARES_BMSK                                           0x200
#define HWIO_SSC_QDSP6SS_RESET_AXIM2_ARES_SHFT                                             0x9
#define HWIO_SSC_QDSP6SS_RESET_AXIS_ARES_BMSK                                            0x100
#define HWIO_SSC_QDSP6SS_RESET_AXIS_ARES_SHFT                                              0x8
#define HWIO_SSC_QDSP6SS_RESET_ATBM_ARES_BMSK                                             0x80
#define HWIO_SSC_QDSP6SS_RESET_ATBM_ARES_SHFT                                              0x7
#define HWIO_SSC_QDSP6SS_RESET_AHBM_ARES_BMSK                                             0x40
#define HWIO_SSC_QDSP6SS_RESET_AHBM_ARES_SHFT                                              0x6
#define HWIO_SSC_QDSP6SS_RESET_AXIM_ARES_BMSK                                             0x20
#define HWIO_SSC_QDSP6SS_RESET_AXIM_ARES_SHFT                                              0x5
#define HWIO_SSC_QDSP6SS_RESET_ETM_ISDB_ARES_BMSK                                         0x10
#define HWIO_SSC_QDSP6SS_RESET_ETM_ISDB_ARES_SHFT                                          0x4
#define HWIO_SSC_QDSP6SS_RESET_BUS_ARES_ENA_BMSK                                           0x4
#define HWIO_SSC_QDSP6SS_RESET_BUS_ARES_ENA_SHFT                                           0x2
#define HWIO_SSC_QDSP6SS_RESET_CORE_ARES_BMSK                                              0x2
#define HWIO_SSC_QDSP6SS_RESET_CORE_ARES_SHFT                                              0x1
#define HWIO_SSC_QDSP6SS_RESET_STOP_CORE_BMSK                                              0x1
#define HWIO_SSC_QDSP6SS_RESET_STOP_CORE_SHFT                                              0x0

#define HWIO_SSC_QDSP6SS_DBG_CFG_ADDR                                               (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000018)
#define HWIO_SSC_QDSP6SS_DBG_CFG_OFFS                                               (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000018)
#define HWIO_SSC_QDSP6SS_DBG_CFG_RMSK                                               0xffff0003
#define HWIO_SSC_QDSP6SS_DBG_CFG_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_DBG_CFG_ADDR, HWIO_SSC_QDSP6SS_DBG_CFG_RMSK)
#define HWIO_SSC_QDSP6SS_DBG_CFG_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_DBG_CFG_ADDR, m)
#define HWIO_SSC_QDSP6SS_DBG_CFG_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_DBG_CFG_ADDR,v)
#define HWIO_SSC_QDSP6SS_DBG_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_DBG_CFG_ADDR,m,v,HWIO_SSC_QDSP6SS_DBG_CFG_IN)
#define HWIO_SSC_QDSP6SS_DBG_CFG_DBG_SW_REG_BMSK                                    0xff000000
#define HWIO_SSC_QDSP6SS_DBG_CFG_DBG_SW_REG_SHFT                                          0x18
#define HWIO_SSC_QDSP6SS_DBG_CFG_DBG_SPARE_BMSK                                       0xff0000
#define HWIO_SSC_QDSP6SS_DBG_CFG_DBG_SPARE_SHFT                                           0x10
#define HWIO_SSC_QDSP6SS_DBG_CFG_CTI_TIHS_ENA_BMSK                                         0x2
#define HWIO_SSC_QDSP6SS_DBG_CFG_CTI_TIHS_ENA_SHFT                                         0x1
#define HWIO_SSC_QDSP6SS_DBG_CFG_DBG_ARES_ENA_BMSK                                         0x1
#define HWIO_SSC_QDSP6SS_DBG_CFG_DBG_ARES_ENA_SHFT                                         0x0

#define HWIO_SSC_QDSP6SS_RET_CFG_ADDR                                               (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x0000001c)
#define HWIO_SSC_QDSP6SS_RET_CFG_OFFS                                               (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000001c)
#define HWIO_SSC_QDSP6SS_RET_CFG_RMSK                                                      0x3
#define HWIO_SSC_QDSP6SS_RET_CFG_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_RET_CFG_ADDR, HWIO_SSC_QDSP6SS_RET_CFG_RMSK)
#define HWIO_SSC_QDSP6SS_RET_CFG_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_RET_CFG_ADDR, m)
#define HWIO_SSC_QDSP6SS_RET_CFG_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_RET_CFG_ADDR,v)
#define HWIO_SSC_QDSP6SS_RET_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_RET_CFG_ADDR,m,v,HWIO_SSC_QDSP6SS_RET_CFG_IN)
#define HWIO_SSC_QDSP6SS_RET_CFG_ARCH_ARES_ENA_BMSK                                        0x2
#define HWIO_SSC_QDSP6SS_RET_CFG_ARCH_ARES_ENA_SHFT                                        0x1
#define HWIO_SSC_QDSP6SS_RET_CFG_RET_ARES_ENA_BMSK                                         0x1
#define HWIO_SSC_QDSP6SS_RET_CFG_RET_ARES_ENA_SHFT                                         0x0

#define HWIO_SSC_QDSP6SS_GFMUX_CTL_ADDR                                             (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000020)
#define HWIO_SSC_QDSP6SS_GFMUX_CTL_OFFS                                             (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000020)
#define HWIO_SSC_QDSP6SS_GFMUX_CTL_RMSK                                                  0x30f
#define HWIO_SSC_QDSP6SS_GFMUX_CTL_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_GFMUX_CTL_ADDR, HWIO_SSC_QDSP6SS_GFMUX_CTL_RMSK)
#define HWIO_SSC_QDSP6SS_GFMUX_CTL_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_GFMUX_CTL_ADDR, m)
#define HWIO_SSC_QDSP6SS_GFMUX_CTL_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_GFMUX_CTL_ADDR,v)
#define HWIO_SSC_QDSP6SS_GFMUX_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_GFMUX_CTL_ADDR,m,v,HWIO_SSC_QDSP6SS_GFMUX_CTL_IN)
#define HWIO_SSC_QDSP6SS_GFMUX_CTL_IDLE_CORE_CLK_EN_BMSK                                 0x200
#define HWIO_SSC_QDSP6SS_GFMUX_CTL_IDLE_CORE_CLK_EN_SHFT                                   0x9
#define HWIO_SSC_QDSP6SS_GFMUX_CTL_SRC_SWITCH_CLK_OVR_BMSK                               0x100
#define HWIO_SSC_QDSP6SS_GFMUX_CTL_SRC_SWITCH_CLK_OVR_SHFT                                 0x8
#define HWIO_SSC_QDSP6SS_GFMUX_CTL_CLK_SRC_SEL_BMSK                                        0xc
#define HWIO_SSC_QDSP6SS_GFMUX_CTL_CLK_SRC_SEL_SHFT                                        0x2
#define HWIO_SSC_QDSP6SS_GFMUX_CTL_CLK_ENA_BMSK                                            0x2
#define HWIO_SSC_QDSP6SS_GFMUX_CTL_CLK_ENA_SHFT                                            0x1
#define HWIO_SSC_QDSP6SS_GFMUX_CTL_CLK_ARES_BMSK                                           0x1
#define HWIO_SSC_QDSP6SS_GFMUX_CTL_CLK_ARES_SHFT                                           0x0

#define HWIO_SSC_QDSP6SS_GFMUX_STATUS_ADDR                                          (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000024)
#define HWIO_SSC_QDSP6SS_GFMUX_STATUS_OFFS                                          (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000024)
#define HWIO_SSC_QDSP6SS_GFMUX_STATUS_RMSK                                                0x1f
#define HWIO_SSC_QDSP6SS_GFMUX_STATUS_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_GFMUX_STATUS_ADDR, HWIO_SSC_QDSP6SS_GFMUX_STATUS_RMSK)
#define HWIO_SSC_QDSP6SS_GFMUX_STATUS_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_GFMUX_STATUS_ADDR, m)
#define HWIO_SSC_QDSP6SS_GFMUX_STATUS_SEL_STATUS_BMSK                                     0x1e
#define HWIO_SSC_QDSP6SS_GFMUX_STATUS_SEL_STATUS_SHFT                                      0x1
#define HWIO_SSC_QDSP6SS_GFMUX_STATUS_SWITCH_STATUS_BMSK                                   0x1
#define HWIO_SSC_QDSP6SS_GFMUX_STATUS_SWITCH_STATUS_SHFT                                   0x0

#define HWIO_SSC_QDSP6SS_CORE_CMD_RCGR_ADDR                                         (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000028)
#define HWIO_SSC_QDSP6SS_CORE_CMD_RCGR_OFFS                                         (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000028)
#define HWIO_SSC_QDSP6SS_CORE_CMD_RCGR_RMSK                                         0x80000013
#define HWIO_SSC_QDSP6SS_CORE_CMD_RCGR_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_CORE_CMD_RCGR_ADDR, HWIO_SSC_QDSP6SS_CORE_CMD_RCGR_RMSK)
#define HWIO_SSC_QDSP6SS_CORE_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_CORE_CMD_RCGR_ADDR, m)
#define HWIO_SSC_QDSP6SS_CORE_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_CORE_CMD_RCGR_ADDR,v)
#define HWIO_SSC_QDSP6SS_CORE_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_CORE_CMD_RCGR_ADDR,m,v,HWIO_SSC_QDSP6SS_CORE_CMD_RCGR_IN)
#define HWIO_SSC_QDSP6SS_CORE_CMD_RCGR_ROOT_OFF_BMSK                                0x80000000
#define HWIO_SSC_QDSP6SS_CORE_CMD_RCGR_ROOT_OFF_SHFT                                      0x1f
#define HWIO_SSC_QDSP6SS_CORE_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                0x10
#define HWIO_SSC_QDSP6SS_CORE_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                 0x4
#define HWIO_SSC_QDSP6SS_CORE_CMD_RCGR_ROOT_EN_BMSK                                        0x2
#define HWIO_SSC_QDSP6SS_CORE_CMD_RCGR_ROOT_EN_SHFT                                        0x1
#define HWIO_SSC_QDSP6SS_CORE_CMD_RCGR_UPDATE_BMSK                                         0x1
#define HWIO_SSC_QDSP6SS_CORE_CMD_RCGR_UPDATE_SHFT                                         0x0

#define HWIO_SSC_QDSP6SS_CORE_CFG_RCGR_ADDR                                         (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x0000002c)
#define HWIO_SSC_QDSP6SS_CORE_CFG_RCGR_OFFS                                         (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000002c)
#define HWIO_SSC_QDSP6SS_CORE_CFG_RCGR_RMSK                                            0x1071f
#define HWIO_SSC_QDSP6SS_CORE_CFG_RCGR_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_CORE_CFG_RCGR_ADDR, HWIO_SSC_QDSP6SS_CORE_CFG_RCGR_RMSK)
#define HWIO_SSC_QDSP6SS_CORE_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_CORE_CFG_RCGR_ADDR, m)
#define HWIO_SSC_QDSP6SS_CORE_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_CORE_CFG_RCGR_ADDR,v)
#define HWIO_SSC_QDSP6SS_CORE_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_CORE_CFG_RCGR_ADDR,m,v,HWIO_SSC_QDSP6SS_CORE_CFG_RCGR_IN)
#define HWIO_SSC_QDSP6SS_CORE_CFG_RCGR_RCGLITE_DISABLE_BMSK                            0x10000
#define HWIO_SSC_QDSP6SS_CORE_CFG_RCGR_RCGLITE_DISABLE_SHFT                               0x10
#define HWIO_SSC_QDSP6SS_CORE_CFG_RCGR_SRC_SEL_BMSK                                      0x700
#define HWIO_SSC_QDSP6SS_CORE_CFG_RCGR_SRC_SEL_SHFT                                        0x8
#define HWIO_SSC_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_BMSK                                       0x1f
#define HWIO_SSC_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_SHFT                                        0x0

#define HWIO_SSC_QDSP6SS_PWR_CTL_ADDR                                               (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000030)
#define HWIO_SSC_QDSP6SS_PWR_CTL_OFFS                                               (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000030)
#define HWIO_SSC_QDSP6SS_PWR_CTL_RMSK                                                0xf7c0000
#define HWIO_SSC_QDSP6SS_PWR_CTL_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_PWR_CTL_ADDR, HWIO_SSC_QDSP6SS_PWR_CTL_RMSK)
#define HWIO_SSC_QDSP6SS_PWR_CTL_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_PWR_CTL_ADDR, m)
#define HWIO_SSC_QDSP6SS_PWR_CTL_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_PWR_CTL_ADDR,v)
#define HWIO_SSC_QDSP6SS_PWR_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_PWR_CTL_ADDR,m,v,HWIO_SSC_QDSP6SS_PWR_CTL_IN)
#define HWIO_SSC_QDSP6SS_PWR_CTL_LDO_PWR_UP_BG_BMSK                                  0x8000000
#define HWIO_SSC_QDSP6SS_PWR_CTL_LDO_PWR_UP_BG_SHFT                                       0x1b
#define HWIO_SSC_QDSP6SS_PWR_CTL_LDO_PWR_UP_BMSK                                     0x4000000
#define HWIO_SSC_QDSP6SS_PWR_CTL_LDO_PWR_UP_SHFT                                          0x1a
#define HWIO_SSC_QDSP6SS_PWR_CTL_LDO_BYP_BMSK                                        0x2000000
#define HWIO_SSC_QDSP6SS_PWR_CTL_LDO_BYP_SHFT                                             0x19
#define HWIO_SSC_QDSP6SS_PWR_CTL_BHS_ON_BMSK                                         0x1000000
#define HWIO_SSC_QDSP6SS_PWR_CTL_BHS_ON_SHFT                                              0x18
#define HWIO_SSC_QDSP6SS_PWR_CTL_CLAMP_QMC_MEM_BMSK                                   0x400000
#define HWIO_SSC_QDSP6SS_PWR_CTL_CLAMP_QMC_MEM_SHFT                                       0x16
#define HWIO_SSC_QDSP6SS_PWR_CTL_CLAMP_WL_BMSK                                        0x200000
#define HWIO_SSC_QDSP6SS_PWR_CTL_CLAMP_WL_SHFT                                            0x15
#define HWIO_SSC_QDSP6SS_PWR_CTL_CLAMP_IO_BMSK                                        0x100000
#define HWIO_SSC_QDSP6SS_PWR_CTL_CLAMP_IO_SHFT                                            0x14
#define HWIO_SSC_QDSP6SS_PWR_CTL_SLP_RET_N_BMSK                                        0x80000
#define HWIO_SSC_QDSP6SS_PWR_CTL_SLP_RET_N_SHFT                                           0x13
#define HWIO_SSC_QDSP6SS_PWR_CTL_ARR_STBY_N_BMSK                                       0x40000
#define HWIO_SSC_QDSP6SS_PWR_CTL_ARR_STBY_N_SHFT                                          0x12

#define HWIO_SSC_QDSP6SS_MEM_PWR_CTL_ADDR                                           (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000034)
#define HWIO_SSC_QDSP6SS_MEM_PWR_CTL_OFFS                                           (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000034)
#define HWIO_SSC_QDSP6SS_MEM_PWR_CTL_RMSK                                           0x1fffffff
#define HWIO_SSC_QDSP6SS_MEM_PWR_CTL_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_MEM_PWR_CTL_ADDR, HWIO_SSC_QDSP6SS_MEM_PWR_CTL_RMSK)
#define HWIO_SSC_QDSP6SS_MEM_PWR_CTL_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_MEM_PWR_CTL_ADDR, m)
#define HWIO_SSC_QDSP6SS_MEM_PWR_CTL_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_MEM_PWR_CTL_ADDR,v)
#define HWIO_SSC_QDSP6SS_MEM_PWR_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_MEM_PWR_CTL_ADDR,m,v,HWIO_SSC_QDSP6SS_MEM_PWR_CTL_IN)
#define HWIO_SSC_QDSP6SS_MEM_PWR_CTL_JU_SLP_NRET_N_BMSK                             0x1c000000
#define HWIO_SSC_QDSP6SS_MEM_PWR_CTL_JU_SLP_NRET_N_SHFT                                   0x1a
#define HWIO_SSC_QDSP6SS_MEM_PWR_CTL_ETB_SLP_NRET_N_BMSK                             0x2000000
#define HWIO_SSC_QDSP6SS_MEM_PWR_CTL_ETB_SLP_NRET_N_SHFT                                  0x19
#define HWIO_SSC_QDSP6SS_MEM_PWR_CTL_L1IU_SLP_NRET_N_BMSK                            0x1800000
#define HWIO_SSC_QDSP6SS_MEM_PWR_CTL_L1IU_SLP_NRET_N_SHFT                                 0x17
#define HWIO_SSC_QDSP6SS_MEM_PWR_CTL_L1DU_SLP_NRET_N_BMSK                             0x600000
#define HWIO_SSC_QDSP6SS_MEM_PWR_CTL_L1DU_SLP_NRET_N_SHFT                                 0x15
#define HWIO_SSC_QDSP6SS_MEM_PWR_CTL_L2PLRU_SLP_NRET_N_BMSK                           0x100000
#define HWIO_SSC_QDSP6SS_MEM_PWR_CTL_L2PLRU_SLP_NRET_N_SHFT                               0x14
#define HWIO_SSC_QDSP6SS_MEM_PWR_CTL_L2TAG_SLP_NRET_N_BMSK                             0xf0000
#define HWIO_SSC_QDSP6SS_MEM_PWR_CTL_L2TAG_SLP_NRET_N_SHFT                                0x10
#define HWIO_SSC_QDSP6SS_MEM_PWR_CTL_L2DATA_SLP_NRET_N_BMSK                             0xffff
#define HWIO_SSC_QDSP6SS_MEM_PWR_CTL_L2DATA_SLP_NRET_N_SHFT                                0x0

#define HWIO_SSC_QDSP6SS_XO_CBCR_ADDR                                               (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000038)
#define HWIO_SSC_QDSP6SS_XO_CBCR_OFFS                                               (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000038)
#define HWIO_SSC_QDSP6SS_XO_CBCR_RMSK                                               0x80000001
#define HWIO_SSC_QDSP6SS_XO_CBCR_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_XO_CBCR_ADDR, HWIO_SSC_QDSP6SS_XO_CBCR_RMSK)
#define HWIO_SSC_QDSP6SS_XO_CBCR_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_XO_CBCR_ADDR, m)
#define HWIO_SSC_QDSP6SS_XO_CBCR_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_XO_CBCR_ADDR,v)
#define HWIO_SSC_QDSP6SS_XO_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_XO_CBCR_ADDR,m,v,HWIO_SSC_QDSP6SS_XO_CBCR_IN)
#define HWIO_SSC_QDSP6SS_XO_CBCR_CLKOFF_BMSK                                        0x80000000
#define HWIO_SSC_QDSP6SS_XO_CBCR_CLKOFF_SHFT                                              0x1f
#define HWIO_SSC_QDSP6SS_XO_CBCR_CLKEN_BMSK                                                0x1
#define HWIO_SSC_QDSP6SS_XO_CBCR_CLKEN_SHFT                                                0x0

#define HWIO_SSC_QDSP6SS_SLEEP_CBCR_ADDR                                            (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x0000003c)
#define HWIO_SSC_QDSP6SS_SLEEP_CBCR_OFFS                                            (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000003c)
#define HWIO_SSC_QDSP6SS_SLEEP_CBCR_RMSK                                            0x80000001
#define HWIO_SSC_QDSP6SS_SLEEP_CBCR_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_SLEEP_CBCR_ADDR, HWIO_SSC_QDSP6SS_SLEEP_CBCR_RMSK)
#define HWIO_SSC_QDSP6SS_SLEEP_CBCR_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_SLEEP_CBCR_ADDR, m)
#define HWIO_SSC_QDSP6SS_SLEEP_CBCR_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SLEEP_CBCR_ADDR,v)
#define HWIO_SSC_QDSP6SS_SLEEP_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_SLEEP_CBCR_ADDR,m,v,HWIO_SSC_QDSP6SS_SLEEP_CBCR_IN)
#define HWIO_SSC_QDSP6SS_SLEEP_CBCR_CLKOFF_BMSK                                     0x80000000
#define HWIO_SSC_QDSP6SS_SLEEP_CBCR_CLKOFF_SHFT                                           0x1f
#define HWIO_SSC_QDSP6SS_SLEEP_CBCR_CLKEN_BMSK                                             0x1
#define HWIO_SSC_QDSP6SS_SLEEP_CBCR_CLKEN_SHFT                                             0x0

#define HWIO_SSC_QDSP6SS_NMI_ADDR                                                   (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000040)
#define HWIO_SSC_QDSP6SS_NMI_OFFS                                                   (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000040)
#define HWIO_SSC_QDSP6SS_NMI_RMSK                                                          0x3
#define HWIO_SSC_QDSP6SS_NMI_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_NMI_ADDR,v)
#define HWIO_SSC_QDSP6SS_NMI_CLEAR_STATUS_BMSK                                             0x2
#define HWIO_SSC_QDSP6SS_NMI_CLEAR_STATUS_SHFT                                             0x1
#define HWIO_SSC_QDSP6SS_NMI_SET_NMI_BMSK                                                  0x1
#define HWIO_SSC_QDSP6SS_NMI_SET_NMI_SHFT                                                  0x0

#define HWIO_SSC_QDSP6SS_NMI_STATUS_ADDR                                            (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000044)
#define HWIO_SSC_QDSP6SS_NMI_STATUS_OFFS                                            (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000044)
#define HWIO_SSC_QDSP6SS_NMI_STATUS_RMSK                                                   0x7
#define HWIO_SSC_QDSP6SS_NMI_STATUS_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_NMI_STATUS_ADDR, HWIO_SSC_QDSP6SS_NMI_STATUS_RMSK)
#define HWIO_SSC_QDSP6SS_NMI_STATUS_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_NMI_STATUS_ADDR, m)
#define HWIO_SSC_QDSP6SS_NMI_STATUS_EXT_DBG_TRIG_BMSK                                      0x4
#define HWIO_SSC_QDSP6SS_NMI_STATUS_EXT_DBG_TRIG_SHFT                                      0x2
#define HWIO_SSC_QDSP6SS_NMI_STATUS_WDOG_TRIG_BMSK                                         0x2
#define HWIO_SSC_QDSP6SS_NMI_STATUS_WDOG_TRIG_SHFT                                         0x1
#define HWIO_SSC_QDSP6SS_NMI_STATUS_PUBCSR_TRIG_BMSK                                       0x1
#define HWIO_SSC_QDSP6SS_NMI_STATUS_PUBCSR_TRIG_SHFT                                       0x0

#define HWIO_SSC_QDSP6SS_CLOCK_SPDM_MON_ADDR                                        (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000048)
#define HWIO_SSC_QDSP6SS_CLOCK_SPDM_MON_OFFS                                        (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000048)
#define HWIO_SSC_QDSP6SS_CLOCK_SPDM_MON_RMSK                                               0x1
#define HWIO_SSC_QDSP6SS_CLOCK_SPDM_MON_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_CLOCK_SPDM_MON_ADDR, HWIO_SSC_QDSP6SS_CLOCK_SPDM_MON_RMSK)
#define HWIO_SSC_QDSP6SS_CLOCK_SPDM_MON_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_CLOCK_SPDM_MON_ADDR, m)
#define HWIO_SSC_QDSP6SS_CLOCK_SPDM_MON_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_CLOCK_SPDM_MON_ADDR,v)
#define HWIO_SSC_QDSP6SS_CLOCK_SPDM_MON_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_CLOCK_SPDM_MON_ADDR,m,v,HWIO_SSC_QDSP6SS_CLOCK_SPDM_MON_IN)
#define HWIO_SSC_QDSP6SS_CLOCK_SPDM_MON_Q6_MON_CLKEN_BMSK                                  0x1
#define HWIO_SSC_QDSP6SS_CLOCK_SPDM_MON_Q6_MON_CLKEN_SHFT                                  0x0

#define HWIO_SSC_QDSP6SS_STATERET_CTL_ADDR                                          (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x0000004c)
#define HWIO_SSC_QDSP6SS_STATERET_CTL_OFFS                                          (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000004c)
#define HWIO_SSC_QDSP6SS_STATERET_CTL_RMSK                                                 0xf
#define HWIO_SSC_QDSP6SS_STATERET_CTL_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_STATERET_CTL_ADDR, HWIO_SSC_QDSP6SS_STATERET_CTL_RMSK)
#define HWIO_SSC_QDSP6SS_STATERET_CTL_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_STATERET_CTL_ADDR, m)
#define HWIO_SSC_QDSP6SS_STATERET_CTL_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_STATERET_CTL_ADDR,v)
#define HWIO_SSC_QDSP6SS_STATERET_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_STATERET_CTL_ADDR,m,v,HWIO_SSC_QDSP6SS_STATERET_CTL_IN)
#define HWIO_SSC_QDSP6SS_STATERET_CTL_WAKEUP_IN_BMSK                                       0x8
#define HWIO_SSC_QDSP6SS_STATERET_CTL_WAKEUP_IN_SHFT                                       0x3
#define HWIO_SSC_QDSP6SS_STATERET_CTL_WAKE_IRQ_BMSK                                        0x4
#define HWIO_SSC_QDSP6SS_STATERET_CTL_WAKE_IRQ_SHFT                                        0x2
#define HWIO_SSC_QDSP6SS_STATERET_CTL_RESTORE_BMSK                                         0x2
#define HWIO_SSC_QDSP6SS_STATERET_CTL_RESTORE_SHFT                                         0x1
#define HWIO_SSC_QDSP6SS_STATERET_CTL_SAVE_BMSK                                            0x1
#define HWIO_SSC_QDSP6SS_STATERET_CTL_SAVE_SHFT                                            0x0

#define HWIO_SSC_QDSP6SS_SPM_SW_TRIG_ADDR                                           (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000080)
#define HWIO_SSC_QDSP6SS_SPM_SW_TRIG_OFFS                                           (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000080)
#define HWIO_SSC_QDSP6SS_SPM_SW_TRIG_RMSK                                                  0xf
#define HWIO_SSC_QDSP6SS_SPM_SW_TRIG_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPM_SW_TRIG_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPM_SW_TRIG_CMD_BMSK                                              0xf
#define HWIO_SSC_QDSP6SS_SPM_SW_TRIG_CMD_SHFT                                              0x0

#define HWIO_SSC_QDSP6SS_SPM_TRIG_STATUS_ADDR                                       (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000084)
#define HWIO_SSC_QDSP6SS_SPM_TRIG_STATUS_OFFS                                       (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000084)
#define HWIO_SSC_QDSP6SS_SPM_TRIG_STATUS_RMSK                                              0xf
#define HWIO_SSC_QDSP6SS_SPM_TRIG_STATUS_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_SPM_TRIG_STATUS_ADDR, HWIO_SSC_QDSP6SS_SPM_TRIG_STATUS_RMSK)
#define HWIO_SSC_QDSP6SS_SPM_TRIG_STATUS_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_SPM_TRIG_STATUS_ADDR, m)
#define HWIO_SSC_QDSP6SS_SPM_TRIG_STATUS_BUSY_BMSK                                         0xf
#define HWIO_SSC_QDSP6SS_SPM_TRIG_STATUS_BUSY_SHFT                                         0x0

#define HWIO_SSC_QDSP6SS_INTF_HALTREQ_ADDR                                          (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000088)
#define HWIO_SSC_QDSP6SS_INTF_HALTREQ_OFFS                                          (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000088)
#define HWIO_SSC_QDSP6SS_INTF_HALTREQ_RMSK                                                 0x7
#define HWIO_SSC_QDSP6SS_INTF_HALTREQ_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_INTF_HALTREQ_ADDR, HWIO_SSC_QDSP6SS_INTF_HALTREQ_RMSK)
#define HWIO_SSC_QDSP6SS_INTF_HALTREQ_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_INTF_HALTREQ_ADDR, m)
#define HWIO_SSC_QDSP6SS_INTF_HALTREQ_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_INTF_HALTREQ_ADDR,v)
#define HWIO_SSC_QDSP6SS_INTF_HALTREQ_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_INTF_HALTREQ_ADDR,m,v,HWIO_SSC_QDSP6SS_INTF_HALTREQ_IN)
#define HWIO_SSC_QDSP6SS_INTF_HALTREQ_AXIM2_BMSK                                           0x4
#define HWIO_SSC_QDSP6SS_INTF_HALTREQ_AXIM2_SHFT                                           0x2
#define HWIO_SSC_QDSP6SS_INTF_HALTREQ_AXIM_BMSK                                            0x2
#define HWIO_SSC_QDSP6SS_INTF_HALTREQ_AXIM_SHFT                                            0x1
#define HWIO_SSC_QDSP6SS_INTF_HALTREQ_ALL_BMSK                                             0x1
#define HWIO_SSC_QDSP6SS_INTF_HALTREQ_ALL_SHFT                                             0x0

#define HWIO_SSC_QDSP6SS_INTF_HALTACK_ADDR                                          (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x0000008c)
#define HWIO_SSC_QDSP6SS_INTF_HALTACK_OFFS                                          (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000008c)
#define HWIO_SSC_QDSP6SS_INTF_HALTACK_RMSK                                                 0x7
#define HWIO_SSC_QDSP6SS_INTF_HALTACK_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_INTF_HALTACK_ADDR, HWIO_SSC_QDSP6SS_INTF_HALTACK_RMSK)
#define HWIO_SSC_QDSP6SS_INTF_HALTACK_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_INTF_HALTACK_ADDR, m)
#define HWIO_SSC_QDSP6SS_INTF_HALTACK_AXIM2_BMSK                                           0x4
#define HWIO_SSC_QDSP6SS_INTF_HALTACK_AXIM2_SHFT                                           0x2
#define HWIO_SSC_QDSP6SS_INTF_HALTACK_AXIM_BMSK                                            0x2
#define HWIO_SSC_QDSP6SS_INTF_HALTACK_AXIM_SHFT                                            0x1
#define HWIO_SSC_QDSP6SS_INTF_HALTACK_ALL_BMSK                                             0x1
#define HWIO_SSC_QDSP6SS_INTF_HALTACK_ALL_SHFT                                             0x0

#define HWIO_SSC_QDSP6SS_INTFCLAMP_SET_ADDR                                         (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000090)
#define HWIO_SSC_QDSP6SS_INTFCLAMP_SET_OFFS                                         (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000090)
#define HWIO_SSC_QDSP6SS_INTFCLAMP_SET_RMSK                                                0xf
#define HWIO_SSC_QDSP6SS_INTFCLAMP_SET_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_INTFCLAMP_SET_ADDR,v)
#define HWIO_SSC_QDSP6SS_INTFCLAMP_SET_AXIM2_CLAMP_E_BMSK                                  0x8
#define HWIO_SSC_QDSP6SS_INTFCLAMP_SET_AXIM2_CLAMP_E_SHFT                                  0x3
#define HWIO_SSC_QDSP6SS_INTFCLAMP_SET_AXIM2_CLAMP_L_BMSK                                  0x4
#define HWIO_SSC_QDSP6SS_INTFCLAMP_SET_AXIM2_CLAMP_L_SHFT                                  0x2
#define HWIO_SSC_QDSP6SS_INTFCLAMP_SET_AXIM_CLAMP_E_BMSK                                   0x2
#define HWIO_SSC_QDSP6SS_INTFCLAMP_SET_AXIM_CLAMP_E_SHFT                                   0x1
#define HWIO_SSC_QDSP6SS_INTFCLAMP_SET_AXIM_CLAMP_L_BMSK                                   0x1
#define HWIO_SSC_QDSP6SS_INTFCLAMP_SET_AXIM_CLAMP_L_SHFT                                   0x0

#define HWIO_SSC_QDSP6SS_INTFCLAMP_CLEAR_ADDR                                       (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000094)
#define HWIO_SSC_QDSP6SS_INTFCLAMP_CLEAR_OFFS                                       (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000094)
#define HWIO_SSC_QDSP6SS_INTFCLAMP_CLEAR_RMSK                                              0xf
#define HWIO_SSC_QDSP6SS_INTFCLAMP_CLEAR_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_INTFCLAMP_CLEAR_ADDR,v)
#define HWIO_SSC_QDSP6SS_INTFCLAMP_CLEAR_AXIM2_CLAMP_E_BMSK                                0x8
#define HWIO_SSC_QDSP6SS_INTFCLAMP_CLEAR_AXIM2_CLAMP_E_SHFT                                0x3
#define HWIO_SSC_QDSP6SS_INTFCLAMP_CLEAR_AXIM2_CLAMP_L_BMSK                                0x4
#define HWIO_SSC_QDSP6SS_INTFCLAMP_CLEAR_AXIM2_CLAMP_L_SHFT                                0x2
#define HWIO_SSC_QDSP6SS_INTFCLAMP_CLEAR_AXIM_CLAMP_E_BMSK                                 0x2
#define HWIO_SSC_QDSP6SS_INTFCLAMP_CLEAR_AXIM_CLAMP_E_SHFT                                 0x1
#define HWIO_SSC_QDSP6SS_INTFCLAMP_CLEAR_AXIM_CLAMP_L_BMSK                                 0x1
#define HWIO_SSC_QDSP6SS_INTFCLAMP_CLEAR_AXIM_CLAMP_L_SHFT                                 0x0

#define HWIO_SSC_QDSP6SS_INTFCLAMP_STATUS_ADDR                                      (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000098)
#define HWIO_SSC_QDSP6SS_INTFCLAMP_STATUS_OFFS                                      (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000098)
#define HWIO_SSC_QDSP6SS_INTFCLAMP_STATUS_RMSK                                             0xf
#define HWIO_SSC_QDSP6SS_INTFCLAMP_STATUS_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_INTFCLAMP_STATUS_ADDR, HWIO_SSC_QDSP6SS_INTFCLAMP_STATUS_RMSK)
#define HWIO_SSC_QDSP6SS_INTFCLAMP_STATUS_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_INTFCLAMP_STATUS_ADDR, m)
#define HWIO_SSC_QDSP6SS_INTFCLAMP_STATUS_AXIM2_CLAMP_E_BMSK                               0x8
#define HWIO_SSC_QDSP6SS_INTFCLAMP_STATUS_AXIM2_CLAMP_E_SHFT                               0x3
#define HWIO_SSC_QDSP6SS_INTFCLAMP_STATUS_AXIM2_CLAMP_L_BMSK                               0x4
#define HWIO_SSC_QDSP6SS_INTFCLAMP_STATUS_AXIM2_CLAMP_L_SHFT                               0x2
#define HWIO_SSC_QDSP6SS_INTFCLAMP_STATUS_AXIM_CLAMP_E_BMSK                                0x2
#define HWIO_SSC_QDSP6SS_INTFCLAMP_STATUS_AXIM_CLAMP_E_SHFT                                0x1
#define HWIO_SSC_QDSP6SS_INTFCLAMP_STATUS_AXIM_CLAMP_L_BMSK                                0x1
#define HWIO_SSC_QDSP6SS_INTFCLAMP_STATUS_AXIM_CLAMP_L_SHFT                                0x0

#define HWIO_SSC_QDSP6SS_INTF_FIFO_RESET_ADDR                                       (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x0000009c)
#define HWIO_SSC_QDSP6SS_INTF_FIFO_RESET_OFFS                                       (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000009c)
#define HWIO_SSC_QDSP6SS_INTF_FIFO_RESET_RMSK                                              0x3
#define HWIO_SSC_QDSP6SS_INTF_FIFO_RESET_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_INTF_FIFO_RESET_ADDR, HWIO_SSC_QDSP6SS_INTF_FIFO_RESET_RMSK)
#define HWIO_SSC_QDSP6SS_INTF_FIFO_RESET_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_INTF_FIFO_RESET_ADDR, m)
#define HWIO_SSC_QDSP6SS_INTF_FIFO_RESET_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_INTF_FIFO_RESET_ADDR,v)
#define HWIO_SSC_QDSP6SS_INTF_FIFO_RESET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_INTF_FIFO_RESET_ADDR,m,v,HWIO_SSC_QDSP6SS_INTF_FIFO_RESET_IN)
#define HWIO_SSC_QDSP6SS_INTF_FIFO_RESET_AXIM2_BMSK                                        0x2
#define HWIO_SSC_QDSP6SS_INTF_FIFO_RESET_AXIM2_SHFT                                        0x1
#define HWIO_SSC_QDSP6SS_INTF_FIFO_RESET_AXIM_BMSK                                         0x1
#define HWIO_SSC_QDSP6SS_INTF_FIFO_RESET_AXIM_SHFT                                         0x0

#define HWIO_SSC_QDSP6SS_CP_BHS_CTL_ADDR                                            (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x000000ac)
#define HWIO_SSC_QDSP6SS_CP_BHS_CTL_OFFS                                            (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x000000ac)
#define HWIO_SSC_QDSP6SS_CP_BHS_CTL_RMSK                                                   0xf
#define HWIO_SSC_QDSP6SS_CP_BHS_CTL_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_CP_BHS_CTL_ADDR, HWIO_SSC_QDSP6SS_CP_BHS_CTL_RMSK)
#define HWIO_SSC_QDSP6SS_CP_BHS_CTL_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_CP_BHS_CTL_ADDR, m)
#define HWIO_SSC_QDSP6SS_CP_BHS_CTL_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_CP_BHS_CTL_ADDR,v)
#define HWIO_SSC_QDSP6SS_CP_BHS_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_CP_BHS_CTL_ADDR,m,v,HWIO_SSC_QDSP6SS_CP_BHS_CTL_IN)
#define HWIO_SSC_QDSP6SS_CP_BHS_CTL_DRIVE_SEL_BMSK                                         0xf
#define HWIO_SSC_QDSP6SS_CP_BHS_CTL_DRIVE_SEL_SHFT                                         0x0

#define HWIO_SSC_QDSP6SS_CGC_OVERRIDE_ADDR                                          (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x000000b0)
#define HWIO_SSC_QDSP6SS_CGC_OVERRIDE_OFFS                                          (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x000000b0)
#define HWIO_SSC_QDSP6SS_CGC_OVERRIDE_RMSK                                              0xaf7f
#define HWIO_SSC_QDSP6SS_CGC_OVERRIDE_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_CGC_OVERRIDE_ADDR, HWIO_SSC_QDSP6SS_CGC_OVERRIDE_RMSK)
#define HWIO_SSC_QDSP6SS_CGC_OVERRIDE_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_CGC_OVERRIDE_ADDR, m)
#define HWIO_SSC_QDSP6SS_CGC_OVERRIDE_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_CGC_OVERRIDE_ADDR,v)
#define HWIO_SSC_QDSP6SS_CGC_OVERRIDE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_CGC_OVERRIDE_ADDR,m,v,HWIO_SSC_QDSP6SS_CGC_OVERRIDE_IN)
#define HWIO_SSC_QDSP6SS_CGC_OVERRIDE_CP0_CLK_EN_BMSK                                   0x8000
#define HWIO_SSC_QDSP6SS_CGC_OVERRIDE_CP0_CLK_EN_SHFT                                      0xf
#define HWIO_SSC_QDSP6SS_CGC_OVERRIDE_AXIS_CLK_EN_BMSK                                  0x2000
#define HWIO_SSC_QDSP6SS_CGC_OVERRIDE_AXIS_CLK_EN_SHFT                                     0xd
#define HWIO_SSC_QDSP6SS_CGC_OVERRIDE_AHBM_CLK_EN_BMSK                                   0x800
#define HWIO_SSC_QDSP6SS_CGC_OVERRIDE_AHBM_CLK_EN_SHFT                                     0xb
#define HWIO_SSC_QDSP6SS_CGC_OVERRIDE_AHBS_CLK_EN_BMSK                                   0x400
#define HWIO_SSC_QDSP6SS_CGC_OVERRIDE_AHBS_CLK_EN_SHFT                                     0xa
#define HWIO_SSC_QDSP6SS_CGC_OVERRIDE_PRIV_AHBS_CLK_EN_BMSK                              0x300
#define HWIO_SSC_QDSP6SS_CGC_OVERRIDE_PRIV_AHBS_CLK_EN_SHFT                                0x8
#define HWIO_SSC_QDSP6SS_CGC_OVERRIDE_L2VIC_AHBS_CLK_EN_BMSK                              0x60
#define HWIO_SSC_QDSP6SS_CGC_OVERRIDE_L2VIC_AHBS_CLK_EN_SHFT                               0x5
#define HWIO_SSC_QDSP6SS_CGC_OVERRIDE_TEST_AHBS_CLK_EN_BMSK                               0x10
#define HWIO_SSC_QDSP6SS_CGC_OVERRIDE_TEST_AHBS_CLK_EN_SHFT                                0x4
#define HWIO_SSC_QDSP6SS_CGC_OVERRIDE_PUB_AHBS_CLK_EN_BMSK                                 0x8
#define HWIO_SSC_QDSP6SS_CGC_OVERRIDE_PUB_AHBS_CLK_EN_SHFT                                 0x3
#define HWIO_SSC_QDSP6SS_CGC_OVERRIDE_CORE_BUS_EN_BMSK                                     0x4
#define HWIO_SSC_QDSP6SS_CGC_OVERRIDE_CORE_BUS_EN_SHFT                                     0x2
#define HWIO_SSC_QDSP6SS_CGC_OVERRIDE_CORE_RCLK_EN_BMSK                                    0x2
#define HWIO_SSC_QDSP6SS_CGC_OVERRIDE_CORE_RCLK_EN_SHFT                                    0x1
#define HWIO_SSC_QDSP6SS_CGC_OVERRIDE_CORE_CLK_EN_BMSK                                     0x1
#define HWIO_SSC_QDSP6SS_CGC_OVERRIDE_CORE_CLK_EN_SHFT                                     0x0

#define HWIO_SSC_QDSP6SS_L1S_PWR_CTL_ADDR                                           (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x000000b4)
#define HWIO_SSC_QDSP6SS_L1S_PWR_CTL_OFFS                                           (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x000000b4)
#define HWIO_SSC_QDSP6SS_L1S_PWR_CTL_RMSK                                                 0xff
#define HWIO_SSC_QDSP6SS_L1S_PWR_CTL_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_L1S_PWR_CTL_ADDR, HWIO_SSC_QDSP6SS_L1S_PWR_CTL_RMSK)
#define HWIO_SSC_QDSP6SS_L1S_PWR_CTL_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_L1S_PWR_CTL_ADDR, m)
#define HWIO_SSC_QDSP6SS_L1S_PWR_CTL_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_L1S_PWR_CTL_ADDR,v)
#define HWIO_SSC_QDSP6SS_L1S_PWR_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_L1S_PWR_CTL_ADDR,m,v,HWIO_SSC_QDSP6SS_L1S_PWR_CTL_IN)
#define HWIO_SSC_QDSP6SS_L1S_PWR_CTL_SLP_NRET_N_BMSK                                      0xff
#define HWIO_SSC_QDSP6SS_L1S_PWR_CTL_SLP_NRET_N_SHFT                                       0x0

#define HWIO_SSC_QDSP6SS_CORE_BHS_CTL_ADDR                                          (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x000000c0)
#define HWIO_SSC_QDSP6SS_CORE_BHS_CTL_OFFS                                          (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x000000c0)
#define HWIO_SSC_QDSP6SS_CORE_BHS_CTL_RMSK                                                 0xf
#define HWIO_SSC_QDSP6SS_CORE_BHS_CTL_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_CORE_BHS_CTL_ADDR, HWIO_SSC_QDSP6SS_CORE_BHS_CTL_RMSK)
#define HWIO_SSC_QDSP6SS_CORE_BHS_CTL_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_CORE_BHS_CTL_ADDR, m)
#define HWIO_SSC_QDSP6SS_CORE_BHS_CTL_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_CORE_BHS_CTL_ADDR,v)
#define HWIO_SSC_QDSP6SS_CORE_BHS_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_CORE_BHS_CTL_ADDR,m,v,HWIO_SSC_QDSP6SS_CORE_BHS_CTL_IN)
#define HWIO_SSC_QDSP6SS_CORE_BHS_CTL_DRIVE_SEL_BMSK                                       0xf
#define HWIO_SSC_QDSP6SS_CORE_BHS_CTL_DRIVE_SEL_SHFT                                       0x0

#define HWIO_SSC_QDSP6SS_BHS_STATUS_ADDR                                            (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x000000c4)
#define HWIO_SSC_QDSP6SS_BHS_STATUS_OFFS                                            (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x000000c4)
#define HWIO_SSC_QDSP6SS_BHS_STATUS_RMSK                                                   0x1
#define HWIO_SSC_QDSP6SS_BHS_STATUS_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_BHS_STATUS_ADDR, HWIO_SSC_QDSP6SS_BHS_STATUS_RMSK)
#define HWIO_SSC_QDSP6SS_BHS_STATUS_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_BHS_STATUS_ADDR, m)
#define HWIO_SSC_QDSP6SS_BHS_STATUS_BHS_EN_REST_ACK_BMSK                                   0x1
#define HWIO_SSC_QDSP6SS_BHS_STATUS_BHS_EN_REST_ACK_SHFT                                   0x0

#define HWIO_SSC_QDSP6SS_QMC_SVS_CTL_ADDR                                           (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x000000c8)
#define HWIO_SSC_QDSP6SS_QMC_SVS_CTL_OFFS                                           (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x000000c8)
#define HWIO_SSC_QDSP6SS_QMC_SVS_CTL_RMSK                                                  0x3
#define HWIO_SSC_QDSP6SS_QMC_SVS_CTL_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_QMC_SVS_CTL_ADDR, HWIO_SSC_QDSP6SS_QMC_SVS_CTL_RMSK)
#define HWIO_SSC_QDSP6SS_QMC_SVS_CTL_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_QMC_SVS_CTL_ADDR, m)
#define HWIO_SSC_QDSP6SS_QMC_SVS_CTL_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_QMC_SVS_CTL_ADDR,v)
#define HWIO_SSC_QDSP6SS_QMC_SVS_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_QMC_SVS_CTL_ADDR,m,v,HWIO_SSC_QDSP6SS_QMC_SVS_CTL_IN)
#define HWIO_SSC_QDSP6SS_QMC_SVS_CTL_QMC_MEM_SVS_SEL_BMSK                                  0x2
#define HWIO_SSC_QDSP6SS_QMC_SVS_CTL_QMC_MEM_SVS_SEL_SHFT                                  0x1
#define HWIO_SSC_QDSP6SS_QMC_SVS_CTL_QMC_MEM_SVS_BMSK                                      0x1
#define HWIO_SSC_QDSP6SS_QMC_SVS_CTL_QMC_MEM_SVS_SHFT                                      0x0

#define HWIO_SSC_QDSP6SS_BHS_TEST_ADDR                                              (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x000000cc)
#define HWIO_SSC_QDSP6SS_BHS_TEST_OFFS                                              (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x000000cc)
#define HWIO_SSC_QDSP6SS_BHS_TEST_RMSK                                                     0x1
#define HWIO_SSC_QDSP6SS_BHS_TEST_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_BHS_TEST_ADDR, HWIO_SSC_QDSP6SS_BHS_TEST_RMSK)
#define HWIO_SSC_QDSP6SS_BHS_TEST_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_BHS_TEST_ADDR, m)
#define HWIO_SSC_QDSP6SS_BHS_TEST_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_BHS_TEST_ADDR,v)
#define HWIO_SSC_QDSP6SS_BHS_TEST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_BHS_TEST_ADDR,m,v,HWIO_SSC_QDSP6SS_BHS_TEST_IN)
#define HWIO_SSC_QDSP6SS_BHS_TEST_INSTANT_ON_BMSK                                          0x1
#define HWIO_SSC_QDSP6SS_BHS_TEST_INSTANT_ON_SHFT                                          0x0

#define HWIO_SSC_QDSP6SS_CP_PWR_CTL_ADDR                                            (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x000000f0)
#define HWIO_SSC_QDSP6SS_CP_PWR_CTL_OFFS                                            (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x000000f0)
#define HWIO_SSC_QDSP6SS_CP_PWR_CTL_RMSK                                                   0xf
#define HWIO_SSC_QDSP6SS_CP_PWR_CTL_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_CP_PWR_CTL_ADDR, HWIO_SSC_QDSP6SS_CP_PWR_CTL_RMSK)
#define HWIO_SSC_QDSP6SS_CP_PWR_CTL_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_CP_PWR_CTL_ADDR, m)
#define HWIO_SSC_QDSP6SS_CP_PWR_CTL_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_CP_PWR_CTL_ADDR,v)
#define HWIO_SSC_QDSP6SS_CP_PWR_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_CP_PWR_CTL_ADDR,m,v,HWIO_SSC_QDSP6SS_CP_PWR_CTL_IN)
#define HWIO_SSC_QDSP6SS_CP_PWR_CTL_LDO_2PASS_ON_BMSK                                      0x8
#define HWIO_SSC_QDSP6SS_CP_PWR_CTL_LDO_2PASS_ON_SHFT                                      0x3
#define HWIO_SSC_QDSP6SS_CP_PWR_CTL_SHUNT_BHS_ON_BMSK                                      0x4
#define HWIO_SSC_QDSP6SS_CP_PWR_CTL_SHUNT_BHS_ON_SHFT                                      0x2
#define HWIO_SSC_QDSP6SS_CP_PWR_CTL_BHS_ON_BMSK                                            0x2
#define HWIO_SSC_QDSP6SS_CP_PWR_CTL_BHS_ON_SHFT                                            0x1
#define HWIO_SSC_QDSP6SS_CP_PWR_CTL_CLAMP_IO_BMSK                                          0x1
#define HWIO_SSC_QDSP6SS_CP_PWR_CTL_CLAMP_IO_SHFT                                          0x0

#define HWIO_SSC_QDSP6SS_CP_PWR_STATUS_ADDR                                         (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x000000f4)
#define HWIO_SSC_QDSP6SS_CP_PWR_STATUS_OFFS                                         (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x000000f4)
#define HWIO_SSC_QDSP6SS_CP_PWR_STATUS_RMSK                                                0x1
#define HWIO_SSC_QDSP6SS_CP_PWR_STATUS_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_CP_PWR_STATUS_ADDR, HWIO_SSC_QDSP6SS_CP_PWR_STATUS_RMSK)
#define HWIO_SSC_QDSP6SS_CP_PWR_STATUS_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_CP_PWR_STATUS_ADDR, m)
#define HWIO_SSC_QDSP6SS_CP_PWR_STATUS_ENR_ACK_BMSK                                        0x1
#define HWIO_SSC_QDSP6SS_CP_PWR_STATUS_ENR_ACK_SHFT                                        0x0

#define HWIO_SSC_QDSP6SS_CP_RESET_ADDR                                              (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x000000f8)
#define HWIO_SSC_QDSP6SS_CP_RESET_OFFS                                              (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x000000f8)
#define HWIO_SSC_QDSP6SS_CP_RESET_RMSK                                                     0x1
#define HWIO_SSC_QDSP6SS_CP_RESET_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_CP_RESET_ADDR, HWIO_SSC_QDSP6SS_CP_RESET_RMSK)
#define HWIO_SSC_QDSP6SS_CP_RESET_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_CP_RESET_ADDR, m)
#define HWIO_SSC_QDSP6SS_CP_RESET_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_CP_RESET_ADDR,v)
#define HWIO_SSC_QDSP6SS_CP_RESET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_CP_RESET_ADDR,m,v,HWIO_SSC_QDSP6SS_CP_RESET_IN)
#define HWIO_SSC_QDSP6SS_CP_RESET_ARES_BMSK                                                0x1
#define HWIO_SSC_QDSP6SS_CP_RESET_ARES_SHFT                                                0x0

#define HWIO_SSC_QDSP6SS_CP_CLK_CTL_ADDR                                            (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x000000fc)
#define HWIO_SSC_QDSP6SS_CP_CLK_CTL_OFFS                                            (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x000000fc)
#define HWIO_SSC_QDSP6SS_CP_CLK_CTL_RMSK                                                   0x1
#define HWIO_SSC_QDSP6SS_CP_CLK_CTL_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_CP_CLK_CTL_ADDR, HWIO_SSC_QDSP6SS_CP_CLK_CTL_RMSK)
#define HWIO_SSC_QDSP6SS_CP_CLK_CTL_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_CP_CLK_CTL_ADDR, m)
#define HWIO_SSC_QDSP6SS_CP_CLK_CTL_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_CP_CLK_CTL_ADDR,v)
#define HWIO_SSC_QDSP6SS_CP_CLK_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_CP_CLK_CTL_ADDR,m,v,HWIO_SSC_QDSP6SS_CP_CLK_CTL_IN)
#define HWIO_SSC_QDSP6SS_CP_CLK_CTL_CLK_ENA_BMSK                                           0x1
#define HWIO_SSC_QDSP6SS_CP_CLK_CTL_CLK_ENA_SHFT                                           0x0

#define HWIO_SSC_QDSP6SS_STRAP_TCM_ADDR                                             (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000100)
#define HWIO_SSC_QDSP6SS_STRAP_TCM_OFFS                                             (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000100)
#define HWIO_SSC_QDSP6SS_STRAP_TCM_RMSK                                             0xfffc0000
#define HWIO_SSC_QDSP6SS_STRAP_TCM_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_STRAP_TCM_ADDR, HWIO_SSC_QDSP6SS_STRAP_TCM_RMSK)
#define HWIO_SSC_QDSP6SS_STRAP_TCM_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_STRAP_TCM_ADDR, m)
#define HWIO_SSC_QDSP6SS_STRAP_TCM_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_STRAP_TCM_ADDR,v)
#define HWIO_SSC_QDSP6SS_STRAP_TCM_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_STRAP_TCM_ADDR,m,v,HWIO_SSC_QDSP6SS_STRAP_TCM_IN)
#define HWIO_SSC_QDSP6SS_STRAP_TCM_BASE_ADDR_BMSK                                   0xfffc0000
#define HWIO_SSC_QDSP6SS_STRAP_TCM_BASE_ADDR_SHFT                                         0x12

#define HWIO_SSC_QDSP6SS_STRAP_AHBUPPER_ADDR                                        (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000104)
#define HWIO_SSC_QDSP6SS_STRAP_AHBUPPER_OFFS                                        (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000104)
#define HWIO_SSC_QDSP6SS_STRAP_AHBUPPER_RMSK                                        0xffffc000
#define HWIO_SSC_QDSP6SS_STRAP_AHBUPPER_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_STRAP_AHBUPPER_ADDR, HWIO_SSC_QDSP6SS_STRAP_AHBUPPER_RMSK)
#define HWIO_SSC_QDSP6SS_STRAP_AHBUPPER_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_STRAP_AHBUPPER_ADDR, m)
#define HWIO_SSC_QDSP6SS_STRAP_AHBUPPER_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_STRAP_AHBUPPER_ADDR,v)
#define HWIO_SSC_QDSP6SS_STRAP_AHBUPPER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_STRAP_AHBUPPER_ADDR,m,v,HWIO_SSC_QDSP6SS_STRAP_AHBUPPER_IN)
#define HWIO_SSC_QDSP6SS_STRAP_AHBUPPER_UPPER_ADDR_BMSK                             0xffffc000
#define HWIO_SSC_QDSP6SS_STRAP_AHBUPPER_UPPER_ADDR_SHFT                                    0xe

#define HWIO_SSC_QDSP6SS_STRAP_AHBLOWER_ADDR                                        (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000108)
#define HWIO_SSC_QDSP6SS_STRAP_AHBLOWER_OFFS                                        (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000108)
#define HWIO_SSC_QDSP6SS_STRAP_AHBLOWER_RMSK                                        0xffffc000
#define HWIO_SSC_QDSP6SS_STRAP_AHBLOWER_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_STRAP_AHBLOWER_ADDR, HWIO_SSC_QDSP6SS_STRAP_AHBLOWER_RMSK)
#define HWIO_SSC_QDSP6SS_STRAP_AHBLOWER_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_STRAP_AHBLOWER_ADDR, m)
#define HWIO_SSC_QDSP6SS_STRAP_AHBLOWER_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_STRAP_AHBLOWER_ADDR,v)
#define HWIO_SSC_QDSP6SS_STRAP_AHBLOWER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_STRAP_AHBLOWER_ADDR,m,v,HWIO_SSC_QDSP6SS_STRAP_AHBLOWER_IN)
#define HWIO_SSC_QDSP6SS_STRAP_AHBLOWER_LOWER_ADDR_BMSK                             0xffffc000
#define HWIO_SSC_QDSP6SS_STRAP_AHBLOWER_LOWER_ADDR_SHFT                                    0xe

#define HWIO_SSC_QDSP6SS_STRAP_ACC_ADDR                                             (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000110)
#define HWIO_SSC_QDSP6SS_STRAP_ACC_OFFS                                             (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000110)
#define HWIO_SSC_QDSP6SS_STRAP_ACC_RMSK                                             0xffffffff
#define HWIO_SSC_QDSP6SS_STRAP_ACC_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_STRAP_ACC_ADDR, HWIO_SSC_QDSP6SS_STRAP_ACC_RMSK)
#define HWIO_SSC_QDSP6SS_STRAP_ACC_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_STRAP_ACC_ADDR, m)
#define HWIO_SSC_QDSP6SS_STRAP_ACC_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_STRAP_ACC_ADDR,v)
#define HWIO_SSC_QDSP6SS_STRAP_ACC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_STRAP_ACC_ADDR,m,v,HWIO_SSC_QDSP6SS_STRAP_ACC_IN)
#define HWIO_SSC_QDSP6SS_STRAP_ACC_DATA_BMSK                                        0xffffffff
#define HWIO_SSC_QDSP6SS_STRAP_ACC_DATA_SHFT                                               0x0

#define HWIO_SSC_QDSP6SS_DCC_CTRL_ADDR                                              (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000118)
#define HWIO_SSC_QDSP6SS_DCC_CTRL_OFFS                                              (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000118)
#define HWIO_SSC_QDSP6SS_DCC_CTRL_RMSK                                              0xffffffff
#define HWIO_SSC_QDSP6SS_DCC_CTRL_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_DCC_CTRL_ADDR, HWIO_SSC_QDSP6SS_DCC_CTRL_RMSK)
#define HWIO_SSC_QDSP6SS_DCC_CTRL_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_DCC_CTRL_ADDR, m)
#define HWIO_SSC_QDSP6SS_DCC_CTRL_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_DCC_CTRL_ADDR,v)
#define HWIO_SSC_QDSP6SS_DCC_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_DCC_CTRL_ADDR,m,v,HWIO_SSC_QDSP6SS_DCC_CTRL_IN)
#define HWIO_SSC_QDSP6SS_DCC_CTRL_CTRL_BMSK                                         0xffffffff
#define HWIO_SSC_QDSP6SS_DCC_CTRL_CTRL_SHFT                                                0x0

#define HWIO_SSC_QDSP6SS_STRAP_AXIM2UPPER_ADDR                                      (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x0000011c)
#define HWIO_SSC_QDSP6SS_STRAP_AXIM2UPPER_OFFS                                      (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000011c)
#define HWIO_SSC_QDSP6SS_STRAP_AXIM2UPPER_RMSK                                      0xffffc000
#define HWIO_SSC_QDSP6SS_STRAP_AXIM2UPPER_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_STRAP_AXIM2UPPER_ADDR, HWIO_SSC_QDSP6SS_STRAP_AXIM2UPPER_RMSK)
#define HWIO_SSC_QDSP6SS_STRAP_AXIM2UPPER_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_STRAP_AXIM2UPPER_ADDR, m)
#define HWIO_SSC_QDSP6SS_STRAP_AXIM2UPPER_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_STRAP_AXIM2UPPER_ADDR,v)
#define HWIO_SSC_QDSP6SS_STRAP_AXIM2UPPER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_STRAP_AXIM2UPPER_ADDR,m,v,HWIO_SSC_QDSP6SS_STRAP_AXIM2UPPER_IN)
#define HWIO_SSC_QDSP6SS_STRAP_AXIM2UPPER_UPPER_ADDR_BMSK                           0xffffc000
#define HWIO_SSC_QDSP6SS_STRAP_AXIM2UPPER_UPPER_ADDR_SHFT                                  0xe

#define HWIO_SSC_QDSP6SS_STRAP_AXIM2LOWER_ADDR                                      (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000120)
#define HWIO_SSC_QDSP6SS_STRAP_AXIM2LOWER_OFFS                                      (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000120)
#define HWIO_SSC_QDSP6SS_STRAP_AXIM2LOWER_RMSK                                      0xffffc000
#define HWIO_SSC_QDSP6SS_STRAP_AXIM2LOWER_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_STRAP_AXIM2LOWER_ADDR, HWIO_SSC_QDSP6SS_STRAP_AXIM2LOWER_RMSK)
#define HWIO_SSC_QDSP6SS_STRAP_AXIM2LOWER_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_STRAP_AXIM2LOWER_ADDR, m)
#define HWIO_SSC_QDSP6SS_STRAP_AXIM2LOWER_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_STRAP_AXIM2LOWER_ADDR,v)
#define HWIO_SSC_QDSP6SS_STRAP_AXIM2LOWER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_STRAP_AXIM2LOWER_ADDR,m,v,HWIO_SSC_QDSP6SS_STRAP_AXIM2LOWER_IN)
#define HWIO_SSC_QDSP6SS_STRAP_AXIM2LOWER_LOWER_ADDR_BMSK                           0xffffc000
#define HWIO_SSC_QDSP6SS_STRAP_AXIM2LOWER_LOWER_ADDR_SHFT                                  0xe

#define HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_SEL_ADDR                                     (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000124)
#define HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_SEL_OFFS                                     (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000124)
#define HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_SEL_RMSK                                            0x1
#define HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_SEL_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_SEL_ADDR, HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_SEL_RMSK)
#define HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_SEL_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_SEL_ADDR, m)
#define HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_SEL_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_SEL_ADDR,v)
#define HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_SEL_ADDR,m,v,HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_SEL_IN)
#define HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_SEL_STRAP_QMC_ACC_SEL_BMSK                          0x1
#define HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_SEL_STRAP_QMC_ACC_SEL_SHFT                          0x0

#define HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_ADDR                                         (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000128)
#define HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_OFFS                                         (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000128)
#define HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_RMSK                                         0xffffffff
#define HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_ADDR, HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_RMSK)
#define HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_ADDR, m)
#define HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_ADDR,v)
#define HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_ADDR,m,v,HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_IN)
#define HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_STRAP_QMC_ACC_BMSK                           0xffffffff
#define HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_STRAP_QMC_ACC_SHFT                                  0x0

#define HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_U_ADDR                                       (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x0000012c)
#define HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_U_OFFS                                       (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000012c)
#define HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_U_RMSK                                       0xffffffff
#define HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_U_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_U_ADDR, HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_U_RMSK)
#define HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_U_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_U_ADDR, m)
#define HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_U_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_U_ADDR,v)
#define HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_U_ADDR,m,v,HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_U_IN)
#define HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_U_STRAP_QMC_ACC_U_BMSK                       0xffffffff
#define HWIO_SSC_QDSP6SS_STRAP_QMC_ACC_U_STRAP_QMC_ACC_U_SHFT                              0x0

#define HWIO_SSC_QDSP6SS_PLL_MODE_ADDR                                              (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000200)
#define HWIO_SSC_QDSP6SS_PLL_MODE_OFFS                                              (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000200)
#define HWIO_SSC_QDSP6SS_PLL_MODE_RMSK                                              0xffffffff
#define HWIO_SSC_QDSP6SS_PLL_MODE_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_MODE_ADDR, HWIO_SSC_QDSP6SS_PLL_MODE_RMSK)
#define HWIO_SSC_QDSP6SS_PLL_MODE_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_MODE_ADDR, m)
#define HWIO_SSC_QDSP6SS_PLL_MODE_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_PLL_MODE_ADDR,v)
#define HWIO_SSC_QDSP6SS_PLL_MODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_PLL_MODE_ADDR,m,v,HWIO_SSC_QDSP6SS_PLL_MODE_IN)
#define HWIO_SSC_QDSP6SS_PLL_MODE_PLL_LOCK_DET_BMSK                                 0x80000000
#define HWIO_SSC_QDSP6SS_PLL_MODE_PLL_LOCK_DET_SHFT                                       0x1f
#define HWIO_SSC_QDSP6SS_PLL_MODE_PLL_ACTIVE_FLAG_BMSK                              0x40000000
#define HWIO_SSC_QDSP6SS_PLL_MODE_PLL_ACTIVE_FLAG_SHFT                                    0x1e
#define HWIO_SSC_QDSP6SS_PLL_MODE_PLL_ACK_LATCH_BMSK                                0x20000000
#define HWIO_SSC_QDSP6SS_PLL_MODE_PLL_ACK_LATCH_SHFT                                      0x1d
#define HWIO_SSC_QDSP6SS_PLL_MODE_PLL_LOCK_DET_FINE_BMSK                            0x10000000
#define HWIO_SSC_QDSP6SS_PLL_MODE_PLL_LOCK_DET_FINE_SHFT                                  0x1c
#define HWIO_SSC_QDSP6SS_PLL_MODE_RESERVE_BITS27_24_BMSK                             0xf000000
#define HWIO_SSC_QDSP6SS_PLL_MODE_RESERVE_BITS27_24_SHFT                                  0x18
#define HWIO_SSC_QDSP6SS_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_BMSK                     0x800000
#define HWIO_SSC_QDSP6SS_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_SHFT                         0x17
#define HWIO_SSC_QDSP6SS_PLL_MODE_PLL_UPDATE_BMSK                                     0x400000
#define HWIO_SSC_QDSP6SS_PLL_MODE_PLL_UPDATE_SHFT                                         0x16
#define HWIO_SSC_QDSP6SS_PLL_MODE_PLL_VOTE_FSM_RESET_BMSK                             0x200000
#define HWIO_SSC_QDSP6SS_PLL_MODE_PLL_VOTE_FSM_RESET_SHFT                                 0x15
#define HWIO_SSC_QDSP6SS_PLL_MODE_PLL_VOTE_FSM_ENA_BMSK                               0x100000
#define HWIO_SSC_QDSP6SS_PLL_MODE_PLL_VOTE_FSM_ENA_SHFT                                   0x14
#define HWIO_SSC_QDSP6SS_PLL_MODE_PLL_BIAS_COUNT_BMSK                                  0xfc000
#define HWIO_SSC_QDSP6SS_PLL_MODE_PLL_BIAS_COUNT_SHFT                                      0xe
#define HWIO_SSC_QDSP6SS_PLL_MODE_PLL_LOCK_COUNT_BMSK                                   0x3f00
#define HWIO_SSC_QDSP6SS_PLL_MODE_PLL_LOCK_COUNT_SHFT                                      0x8
#define HWIO_SSC_QDSP6SS_PLL_MODE_RESERVE_BITS7_3_BMSK                                    0xf8
#define HWIO_SSC_QDSP6SS_PLL_MODE_RESERVE_BITS7_3_SHFT                                     0x3
#define HWIO_SSC_QDSP6SS_PLL_MODE_PLL_RESET_N_BMSK                                         0x4
#define HWIO_SSC_QDSP6SS_PLL_MODE_PLL_RESET_N_SHFT                                         0x2
#define HWIO_SSC_QDSP6SS_PLL_MODE_RESERVE_BIT1_BMSK                                        0x2
#define HWIO_SSC_QDSP6SS_PLL_MODE_RESERVE_BIT1_SHFT                                        0x1
#define HWIO_SSC_QDSP6SS_PLL_MODE_PLL_OUTCTRL_BMSK                                         0x1
#define HWIO_SSC_QDSP6SS_PLL_MODE_PLL_OUTCTRL_SHFT                                         0x0

#define HWIO_SSC_QDSP6SS_PLL_L_VAL_ADDR                                             (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000204)
#define HWIO_SSC_QDSP6SS_PLL_L_VAL_OFFS                                             (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000204)
#define HWIO_SSC_QDSP6SS_PLL_L_VAL_RMSK                                                 0xffff
#define HWIO_SSC_QDSP6SS_PLL_L_VAL_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_L_VAL_ADDR, HWIO_SSC_QDSP6SS_PLL_L_VAL_RMSK)
#define HWIO_SSC_QDSP6SS_PLL_L_VAL_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_L_VAL_ADDR, m)
#define HWIO_SSC_QDSP6SS_PLL_L_VAL_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_PLL_L_VAL_ADDR,v)
#define HWIO_SSC_QDSP6SS_PLL_L_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_PLL_L_VAL_ADDR,m,v,HWIO_SSC_QDSP6SS_PLL_L_VAL_IN)
#define HWIO_SSC_QDSP6SS_PLL_L_VAL_PLL_L_BMSK                                           0xffff
#define HWIO_SSC_QDSP6SS_PLL_L_VAL_PLL_L_SHFT                                              0x0

#define HWIO_SSC_QDSP6SS_PLL_CAL_L_VAL_ADDR                                         (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000208)
#define HWIO_SSC_QDSP6SS_PLL_CAL_L_VAL_OFFS                                         (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000208)
#define HWIO_SSC_QDSP6SS_PLL_CAL_L_VAL_RMSK                                             0xffff
#define HWIO_SSC_QDSP6SS_PLL_CAL_L_VAL_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_CAL_L_VAL_ADDR, HWIO_SSC_QDSP6SS_PLL_CAL_L_VAL_RMSK)
#define HWIO_SSC_QDSP6SS_PLL_CAL_L_VAL_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_CAL_L_VAL_ADDR, m)
#define HWIO_SSC_QDSP6SS_PLL_CAL_L_VAL_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_PLL_CAL_L_VAL_ADDR,v)
#define HWIO_SSC_QDSP6SS_PLL_CAL_L_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_PLL_CAL_L_VAL_ADDR,m,v,HWIO_SSC_QDSP6SS_PLL_CAL_L_VAL_IN)
#define HWIO_SSC_QDSP6SS_PLL_CAL_L_VAL_PLL_CAL_L_BMSK                                   0xffff
#define HWIO_SSC_QDSP6SS_PLL_CAL_L_VAL_PLL_CAL_L_SHFT                                      0x0

#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_ADDR                                          (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x0000020c)
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_OFFS                                          (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000020c)
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_RMSK                                          0xffffffff
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_USER_CTL_ADDR, HWIO_SSC_QDSP6SS_PLL_USER_CTL_RMSK)
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_USER_CTL_ADDR, m)
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_PLL_USER_CTL_ADDR,v)
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_PLL_USER_CTL_ADDR,m,v,HWIO_SSC_QDSP6SS_PLL_USER_CTL_IN)
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_RESERVE_BITS31_19_BMSK                        0xfff80000
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_RESERVE_BITS31_19_SHFT                              0x13
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_PRE_DIV_RATIO_BMSK                               0x70000
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_PRE_DIV_RATIO_SHFT                                  0x10
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_POST_DIV_RATIO_ODD_BMSK                           0xf000
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_POST_DIV_RATIO_ODD_SHFT                              0xc
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_POST_DIV_RATIO_EVEN_BMSK                           0xf00
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_POST_DIV_RATIO_EVEN_SHFT                             0x8
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_OUT_CLK_POLARITY_BMSK                               0x80
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_OUT_CLK_POLARITY_SHFT                                0x7
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_RESERVE_BITS6_5_BMSK                                0x60
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_RESERVE_BITS6_5_SHFT                                 0x5
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_PLLOUT_TEST_BMSK                                    0x10
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_PLLOUT_TEST_SHFT                                     0x4
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_RESERVE_BIT3_BMSK                                    0x8
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_RESERVE_BIT3_SHFT                                    0x3
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_PLLOUT_ODD_BMSK                                      0x4
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_PLLOUT_ODD_SHFT                                      0x2
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_PLLOUT_EVEN_BMSK                                     0x2
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_PLLOUT_EVEN_SHFT                                     0x1
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_PLLOUT_MAIN_BMSK                                     0x1
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_PLLOUT_MAIN_SHFT                                     0x0

#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_ADDR                                        (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000210)
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_OFFS                                        (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000210)
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_RMSK                                        0xffffffff
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_ADDR, HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_RMSK)
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_ADDR, m)
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_ADDR,v)
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_ADDR,m,v,HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_IN)
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_RESERVE_BITS31_19_BMSK                      0xfff80000
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_RESERVE_BITS31_19_SHFT                            0x13
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_USE_PREDIV_WHEN_CAL_BMSK                       0x40000
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_USE_PREDIV_WHEN_CAL_SHFT                          0x12
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_USE_EXT_SAVERESTORE_BMSK                       0x20000
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_USE_EXT_SAVERESTORE_SHFT                          0x11
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_LOW_JITTER_MODE_EN_BMSK                        0x10000
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_LOW_JITTER_MODE_EN_SHFT                           0x10
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_FRAC_FORMAT_SEL_BMSK                            0x8000
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_FRAC_FORMAT_SEL_SHFT                               0xf
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_BIAS_ON_IN_STANDBY_BMSK                         0x4000
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_BIAS_ON_IN_STANDBY_SHFT                            0xe
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_REF_CLK_AT_OUT_BMSK                             0x2000
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_REF_CLK_AT_OUT_SHFT                                0xd
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_SCALE_FREQ_ON_RESTART_BMSK                      0x1800
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_SCALE_FREQ_ON_RESTART_SHFT                         0xb
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_LATCH_INTERFACE_BYPASS_BMSK                      0x400
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_LATCH_INTERFACE_BYPASS_SHFT                        0xa
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_STATUS_REGISTER_BMSK                             0x3e0
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_STATUS_REGISTER_SHFT                               0x5
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_WRITE_STATE_EN_BMSK                               0x10
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_WRITE_STATE_EN_SHFT                                0x4
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_CALIB_CTRL_BMSK                                    0xe
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_CALIB_CTRL_SHFT                                    0x1
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_USE_ONLY_FINE_LOCK_DET_BMSK                        0x1
#define HWIO_SSC_QDSP6SS_PLL_USER_CTL_U_USE_ONLY_FINE_LOCK_DET_SHFT                        0x0

#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_ADDR                                        (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000214)
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_OFFS                                        (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000214)
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_RMSK                                        0xffffffff
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_ADDR, HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_RMSK)
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_ADDR, m)
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_ADDR,v)
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_ADDR,m,v,HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_IN)
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_FINE_LDC_THRESHOLD_BMSK                     0xfc000000
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_FINE_LDC_THRESHOLD_SHFT                           0x1a
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_COARSE_LDC_THRESHOLD_BMSK                    0x3c00000
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_COARSE_LDC_THRESHOLD_SHFT                         0x16
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_COARSE_LOCK_DET_NEG_THRESHOLD_BMSK            0x3c0000
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_COARSE_LOCK_DET_NEG_THRESHOLD_SHFT                0x12
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_COARSE_LOCK_DET_POS_THRESHOLD_BMSK             0x3c000
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_COARSE_LOCK_DET_POS_THRESHOLD_SHFT                 0xe
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_FINE_LOCK_DET_THRESHOLD_BMSK                    0x3800
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_FINE_LOCK_DET_THRESHOLD_SHFT                       0xb
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_FINE_LOCK_DET_SAMPLE_SIZE_BMSK                   0x700
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_FINE_LOCK_DET_SAMPLE_SIZE_SHFT                     0x8
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_FWD_GAIN_SLEWING_KFN_BMSK                         0xf0
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_FWD_GAIN_SLEWING_KFN_SHFT                          0x4
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_FWD_GAIN_KFN_BMSK                                  0xf
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_FWD_GAIN_KFN_SHFT                                  0x0

#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_U_ADDR                                      (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000218)
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_U_OFFS                                      (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000218)
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_U_RMSK                                      0xffffffff
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_U_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_U_ADDR, HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_U_RMSK)
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_U_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_U_ADDR, m)
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_U_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_U_ADDR,v)
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_U_ADDR,m,v,HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_U_IN)
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_U_BIST_CFG_BMSK                             0xfff00000
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_U_BIST_CFG_SHFT                                   0x14
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_U_RESERVE_BITS19_12_BMSK                       0xff000
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_U_RESERVE_BITS19_12_SHFT                           0xc
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_U_NUM_STEPS_FAST_LOCK_BMSK                       0xc00
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_U_NUM_STEPS_FAST_LOCK_SHFT                         0xa
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_U_PREDIV_WHEN_CAL_BMSK                           0x380
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_U_PREDIV_WHEN_CAL_SHFT                             0x7
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_U_INC_MIN_GLITCH_THRESHOLD_4X_BMSK                0x40
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_U_INC_MIN_GLITCH_THRESHOLD_4X_SHFT                 0x6
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_U_MIN_GLITCH_THRESHOLD_BMSK                       0x30
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_U_MIN_GLITCH_THRESHOLD_SHFT                        0x4
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_U_USE_BOTH_REF_CLK_EDGE_BMSK                       0x8
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_U_USE_BOTH_REF_CLK_EDGE_SHFT                       0x3
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_U_BIAS_WARMUP_TIME_BMSK                            0x6
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_U_BIAS_WARMUP_TIME_SHFT                            0x1
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_U_DIV_LOCK_DET_THRESHOLDS_BMSK                     0x1
#define HWIO_SSC_QDSP6SS_PLL_CONFIG_CTL_U_DIV_LOCK_DET_THRESHOLDS_SHFT                     0x0

#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_ADDR                                          (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x0000021c)
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_OFFS                                          (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000021c)
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_RMSK                                          0xffffffff
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_TEST_CTL_ADDR, HWIO_SSC_QDSP6SS_PLL_TEST_CTL_RMSK)
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_TEST_CTL_ADDR, m)
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_PLL_TEST_CTL_ADDR,v)
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_PLL_TEST_CTL_ADDR,m,v,HWIO_SSC_QDSP6SS_PLL_TEST_CTL_IN)
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_ADD_REF_CYC_CALIB_STEPS_BMSK                  0xc0000000
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_ADD_REF_CYC_CALIB_STEPS_SHFT                        0x1e
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_GLITCH_DETECTOR_COUNT_LIMIT_BMSK              0x30000000
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_GLITCH_DETECTOR_COUNT_LIMIT_SHFT                    0x1c
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_GLITCH_PREVENTION_DIS_BMSK                     0x8000000
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_GLITCH_PREVENTION_DIS_SHFT                          0x1b
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_FINE_FCW_BMSK                                  0x7e00000
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_FINE_FCW_SHFT                                       0x15
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_OVERRIDE_FINE_FCW_BMSK                          0x100000
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_OVERRIDE_FINE_FCW_SHFT                              0x14
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_COARSE_FCW_BMSK                                  0xff000
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_COARSE_FCW_SHFT                                      0xc
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_OVERRIDE_COARSE_FCW_BMSK                           0x800
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_OVERRIDE_COARSE_FCW_SHFT                             0xb
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_PROCESS_CALIB_WORD_BMSK                            0x700
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_PROCESS_CALIB_WORD_SHFT                              0x8
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_OVERRIDE_CALIB_WORD_BMSK                            0x80
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_OVERRIDE_CALIB_WORD_SHFT                             0x7
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_DISABLE_LFSR_BMSK                                   0x40
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_DISABLE_LFSR_SHFT                                    0x6
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_ATEST1_SEL_BMSK                                     0x30
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_ATEST1_SEL_SHFT                                      0x4
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_ATEST0_SEL_BMSK                                      0xc
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_ATEST0_SEL_SHFT                                      0x2
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_ATEST1_EN_BMSK                                       0x2
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_ATEST1_EN_SHFT                                       0x1
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_ATEST0_EN_BMSK                                       0x1
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_ATEST0_EN_SHFT                                       0x0

#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_ADDR                                        (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000220)
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_OFFS                                        (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000220)
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_RMSK                                        0xffffffff
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_ADDR, HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_RMSK)
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_ADDR, m)
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_ADDR,v)
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_ADDR,m,v,HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_IN)
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_ENABLE_TRAINING_SEQ_BMSK                    0x80000000
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_ENABLE_TRAINING_SEQ_SHFT                          0x1f
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_BYPASS_LOGIC_DEP_BMSK                       0x40000000
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_BYPASS_LOGIC_DEP_SHFT                             0x1e
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_BYPASS_BIAS_DET_BMSK                        0x20000000
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_BYPASS_BIAS_DET_SHFT                              0x1d
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_MSB_CLOCK_SELECT_BMSK                       0x10000000
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_MSB_CLOCK_SELECT_SHFT                             0x1c
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_BYPASS_FIRST_ORDER_DSM_BMSK                  0x8000000
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_BYPASS_FIRST_ORDER_DSM_SHFT                       0x1b
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_DCO_OFFSET_CURRENT_ADJUST_BMSK               0x6000000
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_DCO_OFFSET_CURRENT_ADJUST_SHFT                    0x19
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_MIRROR_DEVICE_ADJUST_BMSK                    0x1c00000
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_MIRROR_DEVICE_ADJUST_SHFT                         0x16
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_BIAS_STARTUP_CIR_DIS_BMSK                     0x200000
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_BIAS_STARTUP_CIR_DIS_SHFT                         0x15
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_DISABLE_CLAMP_BMSK                            0x100000
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_DISABLE_CLAMP_SHFT                                0x14
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_BYPASS_MODE_OF_BIAS_BMSK                       0x80000
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_BYPASS_MODE_OF_BIAS_SHFT                          0x13
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_BYPASS_MODE_FOR_BIAS_EN_BMSK                   0x40000
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_BYPASS_MODE_FOR_BIAS_EN_SHFT                      0x12
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_BIAS_ADJUST_BMSK                               0x30000
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_BIAS_ADJUST_SHFT                                  0x10
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_DIV2_NMO_EN_BMSK                                0x8000
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_DIV2_NMO_EN_SHFT                                   0xf
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_DIS_LEAK_CMP_BMSK                               0x4000
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_DIS_LEAK_CMP_SHFT                                  0xe
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_SINGLE_DMET_EN_BMSK                             0x2000
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_SINGLE_DMET_EN_SHFT                                0xd
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_DEMET_WINDOW_DIS_BMSK                           0x1000
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_DEMET_WINDOW_DIS_SHFT                              0xc
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_NMO_OSC_SEL_BMSK                                 0xc00
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_NMO_OSC_SEL_SHFT                                   0xa
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_NOISE_MAG_BMSK                                   0x380
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_NOISE_MAG_SHFT                                     0x7
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_NOISE_GEN_EN_BMSK                                 0x40
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_NOISE_GEN_EN_SHFT                                  0x6
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_OSC_BIAS_GND_BMSK                                 0x20
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_OSC_BIAS_GND_SHFT                                  0x5
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_PLL_TEST_OUT_SEL_BMSK                             0x18
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_PLL_TEST_OUT_SEL_SHFT                              0x3
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_STATUS_REG_EN_BMSK                                 0x4
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_STATUS_REG_EN_SHFT                                 0x2
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_SKIP_FINE_TUNE_BMSK                                0x2
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_SKIP_FINE_TUNE_SHFT                                0x1
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_SKIP_FAST_LOCK_BMSK                                0x1
#define HWIO_SSC_QDSP6SS_PLL_TEST_CTL_U_SKIP_FAST_LOCK_SHFT                                0x0

#define HWIO_SSC_QDSP6SS_PLL_STATUS_ADDR                                            (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000224)
#define HWIO_SSC_QDSP6SS_PLL_STATUS_OFFS                                            (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000224)
#define HWIO_SSC_QDSP6SS_PLL_STATUS_RMSK                                            0xffffffff
#define HWIO_SSC_QDSP6SS_PLL_STATUS_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_STATUS_ADDR, HWIO_SSC_QDSP6SS_PLL_STATUS_RMSK)
#define HWIO_SSC_QDSP6SS_PLL_STATUS_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_STATUS_ADDR, m)
#define HWIO_SSC_QDSP6SS_PLL_STATUS_STATUS_31_0_BMSK                                0xffffffff
#define HWIO_SSC_QDSP6SS_PLL_STATUS_STATUS_31_0_SHFT                                       0x0

#define HWIO_SSC_QDSP6SS_PLL_FREQ_CTL_ADDR                                          (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000228)
#define HWIO_SSC_QDSP6SS_PLL_FREQ_CTL_OFFS                                          (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000228)
#define HWIO_SSC_QDSP6SS_PLL_FREQ_CTL_RMSK                                          0xffffffff
#define HWIO_SSC_QDSP6SS_PLL_FREQ_CTL_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_FREQ_CTL_ADDR, HWIO_SSC_QDSP6SS_PLL_FREQ_CTL_RMSK)
#define HWIO_SSC_QDSP6SS_PLL_FREQ_CTL_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_FREQ_CTL_ADDR, m)
#define HWIO_SSC_QDSP6SS_PLL_FREQ_CTL_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_PLL_FREQ_CTL_ADDR,v)
#define HWIO_SSC_QDSP6SS_PLL_FREQ_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_PLL_FREQ_CTL_ADDR,m,v,HWIO_SSC_QDSP6SS_PLL_FREQ_CTL_IN)
#define HWIO_SSC_QDSP6SS_PLL_FREQ_CTL_FREQUENCY_CTL_WORD_BMSK                       0xffffffff
#define HWIO_SSC_QDSP6SS_PLL_FREQ_CTL_FREQUENCY_CTL_WORD_SHFT                              0x0

#define HWIO_SSC_QDSP6SS_PLL_OPMODE_ADDR                                            (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x0000022c)
#define HWIO_SSC_QDSP6SS_PLL_OPMODE_OFFS                                            (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000022c)
#define HWIO_SSC_QDSP6SS_PLL_OPMODE_RMSK                                                   0x7
#define HWIO_SSC_QDSP6SS_PLL_OPMODE_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_OPMODE_ADDR, HWIO_SSC_QDSP6SS_PLL_OPMODE_RMSK)
#define HWIO_SSC_QDSP6SS_PLL_OPMODE_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_OPMODE_ADDR, m)
#define HWIO_SSC_QDSP6SS_PLL_OPMODE_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_PLL_OPMODE_ADDR,v)
#define HWIO_SSC_QDSP6SS_PLL_OPMODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_PLL_OPMODE_ADDR,m,v,HWIO_SSC_QDSP6SS_PLL_OPMODE_IN)
#define HWIO_SSC_QDSP6SS_PLL_OPMODE_PLL_OPMODE_BMSK                                        0x7
#define HWIO_SSC_QDSP6SS_PLL_OPMODE_PLL_OPMODE_SHFT                                        0x0

#define HWIO_SSC_QDSP6SS_PLL_STATE_ADDR                                             (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000230)
#define HWIO_SSC_QDSP6SS_PLL_STATE_OFFS                                             (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000230)
#define HWIO_SSC_QDSP6SS_PLL_STATE_RMSK                                                    0x7
#define HWIO_SSC_QDSP6SS_PLL_STATE_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_STATE_ADDR, HWIO_SSC_QDSP6SS_PLL_STATE_RMSK)
#define HWIO_SSC_QDSP6SS_PLL_STATE_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_STATE_ADDR, m)
#define HWIO_SSC_QDSP6SS_PLL_STATE_PLL_STATE_BMSK                                          0x7
#define HWIO_SSC_QDSP6SS_PLL_STATE_PLL_STATE_SHFT                                          0x0

#define HWIO_SSC_QDSP6SS_PLL_DROOP_ADDR                                             (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000234)
#define HWIO_SSC_QDSP6SS_PLL_DROOP_OFFS                                             (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000234)
#define HWIO_SSC_QDSP6SS_PLL_DROOP_RMSK                                                   0xff
#define HWIO_SSC_QDSP6SS_PLL_DROOP_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_DROOP_ADDR, HWIO_SSC_QDSP6SS_PLL_DROOP_RMSK)
#define HWIO_SSC_QDSP6SS_PLL_DROOP_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_DROOP_ADDR, m)
#define HWIO_SSC_QDSP6SS_PLL_DROOP_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_PLL_DROOP_ADDR,v)
#define HWIO_SSC_QDSP6SS_PLL_DROOP_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_PLL_DROOP_ADDR,m,v,HWIO_SSC_QDSP6SS_PLL_DROOP_IN)
#define HWIO_SSC_QDSP6SS_PLL_DROOP_DROOP_CODE_BMSK                                        0xfe
#define HWIO_SSC_QDSP6SS_PLL_DROOP_DROOP_CODE_SHFT                                         0x1
#define HWIO_SSC_QDSP6SS_PLL_DROOP_DROOP_EN_BMSK                                           0x1
#define HWIO_SSC_QDSP6SS_PLL_DROOP_DROOP_EN_SHFT                                           0x0

#define HWIO_SSC_QDSP6SS_PLL_FRAC_VAL_ADDR                                          (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000238)
#define HWIO_SSC_QDSP6SS_PLL_FRAC_VAL_OFFS                                          (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000238)
#define HWIO_SSC_QDSP6SS_PLL_FRAC_VAL_RMSK                                              0xffff
#define HWIO_SSC_QDSP6SS_PLL_FRAC_VAL_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_FRAC_VAL_ADDR, HWIO_SSC_QDSP6SS_PLL_FRAC_VAL_RMSK)
#define HWIO_SSC_QDSP6SS_PLL_FRAC_VAL_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_FRAC_VAL_ADDR, m)
#define HWIO_SSC_QDSP6SS_PLL_FRAC_VAL_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_PLL_FRAC_VAL_ADDR,v)
#define HWIO_SSC_QDSP6SS_PLL_FRAC_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_PLL_FRAC_VAL_ADDR,m,v,HWIO_SSC_QDSP6SS_PLL_FRAC_VAL_IN)
#define HWIO_SSC_QDSP6SS_PLL_FRAC_VAL_PLL_FRAC_VAL_BMSK                                 0xffff
#define HWIO_SSC_QDSP6SS_PLL_FRAC_VAL_PLL_FRAC_VAL_SHFT                                    0x0

#define HWIO_SSC_QDSP6SS_PLL_SPARE_ADDR                                             (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x0000023c)
#define HWIO_SSC_QDSP6SS_PLL_SPARE_OFFS                                             (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000023c)
#define HWIO_SSC_QDSP6SS_PLL_SPARE_RMSK                                                   0xff
#define HWIO_SSC_QDSP6SS_PLL_SPARE_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_SPARE_ADDR, HWIO_SSC_QDSP6SS_PLL_SPARE_RMSK)
#define HWIO_SSC_QDSP6SS_PLL_SPARE_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_SPARE_ADDR, m)
#define HWIO_SSC_QDSP6SS_PLL_SPARE_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_PLL_SPARE_ADDR,v)
#define HWIO_SSC_QDSP6SS_PLL_SPARE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_PLL_SPARE_ADDR,m,v,HWIO_SSC_QDSP6SS_PLL_SPARE_IN)
#define HWIO_SSC_QDSP6SS_PLL_SPARE_SPARE_OUTPUTS_BMSK                                     0xf0
#define HWIO_SSC_QDSP6SS_PLL_SPARE_SPARE_OUTPUTS_SHFT                                      0x4
#define HWIO_SSC_QDSP6SS_PLL_SPARE_SPARE_INPUTS_BMSK                                       0xf
#define HWIO_SSC_QDSP6SS_PLL_SPARE_SPARE_INPUTS_SHFT                                       0x0

#define HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_STATUS_ADDR                                 (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000240)
#define HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_STATUS_OFFS                                 (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000240)
#define HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_STATUS_RMSK                                        0x3
#define HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_STATUS_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_STATUS_ADDR, HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_STATUS_RMSK)
#define HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_STATUS_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_STATUS_ADDR, m)
#define HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_STATUS_RCG2PLL_UPD_STATUS_BMSK                     0x2
#define HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_STATUS_RCG2PLL_UPD_STATUS_SHFT                     0x1
#define HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_STATUS_PLL2RCG_UPD_STATUS_BMSK                     0x1
#define HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_STATUS_PLL2RCG_UPD_STATUS_SHFT                     0x0

#define HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_CFG_ADDR                                    (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000244)
#define HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_CFG_OFFS                                    (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000244)
#define HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_CFG_RMSK                                           0x3
#define HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_CFG_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_CFG_ADDR, HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_CFG_RMSK)
#define HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_CFG_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_CFG_ADDR, m)
#define HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_CFG_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_CFG_ADDR,v)
#define HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_CFG_ADDR,m,v,HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_CFG_IN)
#define HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_CFG_RCG2PLL_UPD_EN_BMSK                            0x2
#define HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_CFG_RCG2PLL_UPD_EN_SHFT                            0x1
#define HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_CFG_PLL2RCG_UPD_EN_BMSK                            0x1
#define HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_CFG_PLL2RCG_UPD_EN_SHFT                            0x0

#define HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_ADDR                                 (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000248)
#define HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_OFFS                                 (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000248)
#define HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_RMSK                                       0x1f
#define HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_ADDR, HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_RMSK)
#define HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_ADDR, m)
#define HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_ADDR,v)
#define HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_ADDR,m,v,HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_IN)
#define HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_MATCH_VALUE_BMSK                           0x1f
#define HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_MATCH_VALUE_SHFT                            0x0

#define HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_CMD_ADDR                                    (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x0000024c)
#define HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_CMD_OFFS                                    (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000024c)
#define HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_CMD_RMSK                                           0x1
#define HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_CMD_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_CMD_ADDR,v)
#define HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_CMD_CMD_BMSK                                       0x1
#define HWIO_SSC_QDSP6SS_PLL_RCG_UPDATE_CMD_CMD_SHFT                                       0x0

#define HWIO_SSC_QDSP6SS_DBG_NMI_CFG_ADDR                                           (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000300)
#define HWIO_SSC_QDSP6SS_DBG_NMI_CFG_OFFS                                           (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000300)
#define HWIO_SSC_QDSP6SS_DBG_NMI_CFG_RMSK                                                  0x7
#define HWIO_SSC_QDSP6SS_DBG_NMI_CFG_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_DBG_NMI_CFG_ADDR, HWIO_SSC_QDSP6SS_DBG_NMI_CFG_RMSK)
#define HWIO_SSC_QDSP6SS_DBG_NMI_CFG_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_DBG_NMI_CFG_ADDR, m)
#define HWIO_SSC_QDSP6SS_DBG_NMI_CFG_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_DBG_NMI_CFG_ADDR,v)
#define HWIO_SSC_QDSP6SS_DBG_NMI_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_DBG_NMI_CFG_ADDR,m,v,HWIO_SSC_QDSP6SS_DBG_NMI_CFG_IN)
#define HWIO_SSC_QDSP6SS_DBG_NMI_CFG_DBG_NMI_EN_IN_PWR_COLLAPSE_BMSK                       0x4
#define HWIO_SSC_QDSP6SS_DBG_NMI_CFG_DBG_NMI_EN_IN_PWR_COLLAPSE_SHFT                       0x2
#define HWIO_SSC_QDSP6SS_DBG_NMI_CFG_DBG_NMI_DISABLE_BMSK                                  0x2
#define HWIO_SSC_QDSP6SS_DBG_NMI_CFG_DBG_NMI_DISABLE_SHFT                                  0x1
#define HWIO_SSC_QDSP6SS_DBG_NMI_CFG_DBG_NMI_WAKEUP_DISABLE_BMSK                           0x1
#define HWIO_SSC_QDSP6SS_DBG_NMI_CFG_DBG_NMI_WAKEUP_DISABLE_SHFT                           0x0

#define HWIO_SSC_QDSP6SS_DBG_NMI_PWR_STATUS_ADDR                                    (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00000304)
#define HWIO_SSC_QDSP6SS_DBG_NMI_PWR_STATUS_OFFS                                    (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00000304)
#define HWIO_SSC_QDSP6SS_DBG_NMI_PWR_STATUS_RMSK                                           0x3
#define HWIO_SSC_QDSP6SS_DBG_NMI_PWR_STATUS_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_DBG_NMI_PWR_STATUS_ADDR, HWIO_SSC_QDSP6SS_DBG_NMI_PWR_STATUS_RMSK)
#define HWIO_SSC_QDSP6SS_DBG_NMI_PWR_STATUS_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_DBG_NMI_PWR_STATUS_ADDR, m)
#define HWIO_SSC_QDSP6SS_DBG_NMI_PWR_STATUS_QDSP6_PWR_COLLAPSE_BMSK                        0x2
#define HWIO_SSC_QDSP6SS_DBG_NMI_PWR_STATUS_QDSP6_PWR_COLLAPSE_SHFT                        0x1
#define HWIO_SSC_QDSP6SS_DBG_NMI_PWR_STATUS_QDSP6_IN_SLEEP_BMSK                            0x1
#define HWIO_SSC_QDSP6SS_DBG_NMI_PWR_STATUS_QDSP6_IN_SLEEP_SHFT                            0x0

#define HWIO_SSC_QDSP6SS_TEST_BUS_CTL_ADDR                                          (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00002000)
#define HWIO_SSC_QDSP6SS_TEST_BUS_CTL_OFFS                                          (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00002000)
#define HWIO_SSC_QDSP6SS_TEST_BUS_CTL_RMSK                                          0xffffffff
#define HWIO_SSC_QDSP6SS_TEST_BUS_CTL_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_TEST_BUS_CTL_ADDR, HWIO_SSC_QDSP6SS_TEST_BUS_CTL_RMSK)
#define HWIO_SSC_QDSP6SS_TEST_BUS_CTL_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_TEST_BUS_CTL_ADDR, m)
#define HWIO_SSC_QDSP6SS_TEST_BUS_CTL_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_TEST_BUS_CTL_ADDR,v)
#define HWIO_SSC_QDSP6SS_TEST_BUS_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_TEST_BUS_CTL_ADDR,m,v,HWIO_SSC_QDSP6SS_TEST_BUS_CTL_IN)
#define HWIO_SSC_QDSP6SS_TEST_BUS_CTL_SPARE_CFG_BMSK                                0xff000000
#define HWIO_SSC_QDSP6SS_TEST_BUS_CTL_SPARE_CFG_SHFT                                      0x18
#define HWIO_SSC_QDSP6SS_TEST_BUS_CTL_HWE_INV_BMSK                                    0x800000
#define HWIO_SSC_QDSP6SS_TEST_BUS_CTL_HWE_INV_SHFT                                        0x17
#define HWIO_SSC_QDSP6SS_TEST_BUS_CTL_HWE_SEL_BMSK                                    0x7c0000
#define HWIO_SSC_QDSP6SS_TEST_BUS_CTL_HWE_SEL_SHFT                                        0x12
#define HWIO_SSC_QDSP6SS_TEST_BUS_CTL_TESTBUS_EN_BMSK                                  0x20000
#define HWIO_SSC_QDSP6SS_TEST_BUS_CTL_TESTBUS_EN_SHFT                                     0x11
#define HWIO_SSC_QDSP6SS_TEST_BUS_CTL_Q6_SEL_BMSK                                      0x10000
#define HWIO_SSC_QDSP6SS_TEST_BUS_CTL_Q6_SEL_SHFT                                         0x10
#define HWIO_SSC_QDSP6SS_TEST_BUS_CTL_SEL_BMSK                                          0xffff
#define HWIO_SSC_QDSP6SS_TEST_BUS_CTL_SEL_SHFT                                             0x0

#define HWIO_SSC_QDSP6SS_TEST_BUS_VALUE_ADDR                                        (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00002004)
#define HWIO_SSC_QDSP6SS_TEST_BUS_VALUE_OFFS                                        (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00002004)
#define HWIO_SSC_QDSP6SS_TEST_BUS_VALUE_RMSK                                        0xffffffff
#define HWIO_SSC_QDSP6SS_TEST_BUS_VALUE_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_TEST_BUS_VALUE_ADDR, HWIO_SSC_QDSP6SS_TEST_BUS_VALUE_RMSK)
#define HWIO_SSC_QDSP6SS_TEST_BUS_VALUE_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_TEST_BUS_VALUE_ADDR, m)
#define HWIO_SSC_QDSP6SS_TEST_BUS_VALUE_VALUE_BMSK                                  0xffffffff
#define HWIO_SSC_QDSP6SS_TEST_BUS_VALUE_VALUE_SHFT                                         0x0

#define HWIO_SSC_QDSP6SS_TEST_BUS_WDATA_ADDR                                        (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00002008)
#define HWIO_SSC_QDSP6SS_TEST_BUS_WDATA_OFFS                                        (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00002008)
#define HWIO_SSC_QDSP6SS_TEST_BUS_WDATA_RMSK                                        0xffffffff
#define HWIO_SSC_QDSP6SS_TEST_BUS_WDATA_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_TEST_BUS_WDATA_ADDR, HWIO_SSC_QDSP6SS_TEST_BUS_WDATA_RMSK)
#define HWIO_SSC_QDSP6SS_TEST_BUS_WDATA_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_TEST_BUS_WDATA_ADDR, m)
#define HWIO_SSC_QDSP6SS_TEST_BUS_WDATA_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_TEST_BUS_WDATA_ADDR,v)
#define HWIO_SSC_QDSP6SS_TEST_BUS_WDATA_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_TEST_BUS_WDATA_ADDR,m,v,HWIO_SSC_QDSP6SS_TEST_BUS_WDATA_IN)
#define HWIO_SSC_QDSP6SS_TEST_BUS_WDATA_VALUE_BMSK                                  0xffffffff
#define HWIO_SSC_QDSP6SS_TEST_BUS_WDATA_VALUE_SHFT                                         0x0

#define HWIO_SSC_QDSP6SS_PWRDBG_CTL_ADDR                                            (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x0000200c)
#define HWIO_SSC_QDSP6SS_PWRDBG_CTL_OFFS                                            (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x0000200c)
#define HWIO_SSC_QDSP6SS_PWRDBG_CTL_RMSK                                                   0x1
#define HWIO_SSC_QDSP6SS_PWRDBG_CTL_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_PWRDBG_CTL_ADDR, HWIO_SSC_QDSP6SS_PWRDBG_CTL_RMSK)
#define HWIO_SSC_QDSP6SS_PWRDBG_CTL_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_PWRDBG_CTL_ADDR, m)
#define HWIO_SSC_QDSP6SS_PWRDBG_CTL_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_PWRDBG_CTL_ADDR,v)
#define HWIO_SSC_QDSP6SS_PWRDBG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_PWRDBG_CTL_ADDR,m,v,HWIO_SSC_QDSP6SS_PWRDBG_CTL_IN)
#define HWIO_SSC_QDSP6SS_PWRDBG_CTL_ENA_BMSK                                               0x1
#define HWIO_SSC_QDSP6SS_PWRDBG_CTL_ENA_SHFT                                               0x0

#define HWIO_SSC_QDSP6SS_TEST_CLK_CTL_ADDR                                          (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00002010)
#define HWIO_SSC_QDSP6SS_TEST_CLK_CTL_OFFS                                          (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00002010)
#define HWIO_SSC_QDSP6SS_TEST_CLK_CTL_RMSK                                                0x7f
#define HWIO_SSC_QDSP6SS_TEST_CLK_CTL_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_TEST_CLK_CTL_ADDR, HWIO_SSC_QDSP6SS_TEST_CLK_CTL_RMSK)
#define HWIO_SSC_QDSP6SS_TEST_CLK_CTL_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_TEST_CLK_CTL_ADDR, m)
#define HWIO_SSC_QDSP6SS_TEST_CLK_CTL_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_TEST_CLK_CTL_ADDR,v)
#define HWIO_SSC_QDSP6SS_TEST_CLK_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_TEST_CLK_CTL_ADDR,m,v,HWIO_SSC_QDSP6SS_TEST_CLK_CTL_IN)
#define HWIO_SSC_QDSP6SS_TEST_CLK_CTL_Q6_DBG_CLK_EN_BMSK                                  0x40
#define HWIO_SSC_QDSP6SS_TEST_CLK_CTL_Q6_DBG_CLK_EN_SHFT                                   0x6
#define HWIO_SSC_QDSP6SS_TEST_CLK_CTL_Q6_DBG_CLK_INV_BMSK                                 0x20
#define HWIO_SSC_QDSP6SS_TEST_CLK_CTL_Q6_DBG_CLK_INV_SHFT                                  0x5
#define HWIO_SSC_QDSP6SS_TEST_CLK_CTL_DBG_CLK_SEL_BMSK                                    0x1f
#define HWIO_SSC_QDSP6SS_TEST_CLK_CTL_DBG_CLK_SEL_SHFT                                     0x0

#define HWIO_SSC_QDSP6SS_ZMEAS_CONFIG_ADDR                                          (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00002018)
#define HWIO_SSC_QDSP6SS_ZMEAS_CONFIG_OFFS                                          (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00002018)
#define HWIO_SSC_QDSP6SS_ZMEAS_CONFIG_RMSK                                            0xffffff
#define HWIO_SSC_QDSP6SS_ZMEAS_CONFIG_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_ZMEAS_CONFIG_ADDR, HWIO_SSC_QDSP6SS_ZMEAS_CONFIG_RMSK)
#define HWIO_SSC_QDSP6SS_ZMEAS_CONFIG_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_ZMEAS_CONFIG_ADDR, m)
#define HWIO_SSC_QDSP6SS_ZMEAS_CONFIG_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_ZMEAS_CONFIG_ADDR,v)
#define HWIO_SSC_QDSP6SS_ZMEAS_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_ZMEAS_CONFIG_ADDR,m,v,HWIO_SSC_QDSP6SS_ZMEAS_CONFIG_IN)
#define HWIO_SSC_QDSP6SS_ZMEAS_CONFIG_ZMEAS_COUNT_BMSK                                0xffffe0
#define HWIO_SSC_QDSP6SS_ZMEAS_CONFIG_ZMEAS_COUNT_SHFT                                     0x5
#define HWIO_SSC_QDSP6SS_ZMEAS_CONFIG_MUX_SEL_BMSK                                        0x10
#define HWIO_SSC_QDSP6SS_ZMEAS_CONFIG_MUX_SEL_SHFT                                         0x4
#define HWIO_SSC_QDSP6SS_ZMEAS_CONFIG_ZMEAS_CLK_R_ENA_BMSK                                 0x8
#define HWIO_SSC_QDSP6SS_ZMEAS_CONFIG_ZMEAS_CLK_R_ENA_SHFT                                 0x3
#define HWIO_SSC_QDSP6SS_ZMEAS_CONFIG_ZMEAS_CGC_EN_BMSK                                    0x4
#define HWIO_SSC_QDSP6SS_ZMEAS_CONFIG_ZMEAS_CGC_EN_SHFT                                    0x2
#define HWIO_SSC_QDSP6SS_ZMEAS_CONFIG_ZMEAS_BYPASS_BMSK                                    0x2
#define HWIO_SSC_QDSP6SS_ZMEAS_CONFIG_ZMEAS_BYPASS_SHFT                                    0x1
#define HWIO_SSC_QDSP6SS_ZMEAS_CONFIG_ZMEAS_SW_RESET_BMSK                                  0x1
#define HWIO_SSC_QDSP6SS_ZMEAS_CONFIG_ZMEAS_SW_RESET_SHFT                                  0x0

#define HWIO_SSC_QDSP6SS_CORE_STATUS_ADDR                                           (SSC_QDSP6V60SS_PUB_REG_BASE      + 0x00002028)
#define HWIO_SSC_QDSP6SS_CORE_STATUS_OFFS                                           (SSC_QDSP6V60SS_PUB_REG_BASE_OFFS + 0x00002028)
#define HWIO_SSC_QDSP6SS_CORE_STATUS_RMSK                                                  0x7
#define HWIO_SSC_QDSP6SS_CORE_STATUS_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_CORE_STATUS_ADDR, HWIO_SSC_QDSP6SS_CORE_STATUS_RMSK)
#define HWIO_SSC_QDSP6SS_CORE_STATUS_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_CORE_STATUS_ADDR, m)
#define HWIO_SSC_QDSP6SS_CORE_STATUS_CP0_IDLE_BMSK                                         0x4
#define HWIO_SSC_QDSP6SS_CORE_STATUS_CP0_IDLE_SHFT                                         0x2
#define HWIO_SSC_QDSP6SS_CORE_STATUS_CORE_IN_SLEEP_BMSK                                    0x2
#define HWIO_SSC_QDSP6SS_CORE_STATUS_CORE_IN_SLEEP_SHFT                                    0x1
#define HWIO_SSC_QDSP6SS_CORE_STATUS_CORE_STATE_BMSK                                       0x1
#define HWIO_SSC_QDSP6SS_CORE_STATUS_CORE_STATE_SHFT                                       0x0

/*----------------------------------------------------------------------------
 * MODULE: SSC_QDSP6V60SS_CSR
 *--------------------------------------------------------------------------*/

#define SSC_QDSP6V60SS_CSR_REG_BASE                                                      (SSC_BASE      + 0x00480000)
#define SSC_QDSP6V60SS_CSR_REG_BASE_OFFS                                                 0x00480000

#define HWIO_SSC_QDSP6SS_INSTANCE_ID_ADDR                                                (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00000000)
#define HWIO_SSC_QDSP6SS_INSTANCE_ID_OFFS                                                (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00000000)
#define HWIO_SSC_QDSP6SS_INSTANCE_ID_RMSK                                                       0x7
#define HWIO_SSC_QDSP6SS_INSTANCE_ID_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_INSTANCE_ID_ADDR, HWIO_SSC_QDSP6SS_INSTANCE_ID_RMSK)
#define HWIO_SSC_QDSP6SS_INSTANCE_ID_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_INSTANCE_ID_ADDR, m)
#define HWIO_SSC_QDSP6SS_INSTANCE_ID_ID_BMSK                                                    0x7
#define HWIO_SSC_QDSP6SS_INSTANCE_ID_ID_SHFT                                                    0x0

#define HWIO_SSC_QDSP6SS_CP_EFUSE_STATUS_ADDR                                            (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00000100)
#define HWIO_SSC_QDSP6SS_CP_EFUSE_STATUS_OFFS                                            (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00000100)
#define HWIO_SSC_QDSP6SS_CP_EFUSE_STATUS_RMSK                                                   0x1
#define HWIO_SSC_QDSP6SS_CP_EFUSE_STATUS_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_CP_EFUSE_STATUS_ADDR, HWIO_SSC_QDSP6SS_CP_EFUSE_STATUS_RMSK)
#define HWIO_SSC_QDSP6SS_CP_EFUSE_STATUS_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_CP_EFUSE_STATUS_ADDR, m)
#define HWIO_SSC_QDSP6SS_CP_EFUSE_STATUS_HVX_EN_BMSK                                            0x1
#define HWIO_SSC_QDSP6SS_CP_EFUSE_STATUS_HVX_EN_SHFT                                            0x0

#define HWIO_SSC_QDSP6SS_WDOG_RESET_ADDR                                                 (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00002000)
#define HWIO_SSC_QDSP6SS_WDOG_RESET_OFFS                                                 (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00002000)
#define HWIO_SSC_QDSP6SS_WDOG_RESET_RMSK                                                        0x1
#define HWIO_SSC_QDSP6SS_WDOG_RESET_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_WDOG_RESET_ADDR,v)
#define HWIO_SSC_QDSP6SS_WDOG_RESET_WDOG_RESET_BMSK                                             0x1
#define HWIO_SSC_QDSP6SS_WDOG_RESET_WDOG_RESET_SHFT                                             0x0

#define HWIO_SSC_QDSP6SS_WDOG_CTL_ADDR                                                   (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00002004)
#define HWIO_SSC_QDSP6SS_WDOG_CTL_OFFS                                                   (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00002004)
#define HWIO_SSC_QDSP6SS_WDOG_CTL_RMSK                                                          0x7
#define HWIO_SSC_QDSP6SS_WDOG_CTL_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_WDOG_CTL_ADDR, HWIO_SSC_QDSP6SS_WDOG_CTL_RMSK)
#define HWIO_SSC_QDSP6SS_WDOG_CTL_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_WDOG_CTL_ADDR, m)
#define HWIO_SSC_QDSP6SS_WDOG_CTL_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_WDOG_CTL_ADDR,v)
#define HWIO_SSC_QDSP6SS_WDOG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_WDOG_CTL_ADDR,m,v,HWIO_SSC_QDSP6SS_WDOG_CTL_IN)
#define HWIO_SSC_QDSP6SS_WDOG_CTL_WDOG_TO_NMI_EN_BMSK                                           0x4
#define HWIO_SSC_QDSP6SS_WDOG_CTL_WDOG_TO_NMI_EN_SHFT                                           0x2
#define HWIO_SSC_QDSP6SS_WDOG_CTL_UNMASKED_INT_EN_BMSK                                          0x2
#define HWIO_SSC_QDSP6SS_WDOG_CTL_UNMASKED_INT_EN_SHFT                                          0x1
#define HWIO_SSC_QDSP6SS_WDOG_CTL_ENABLE_BMSK                                                   0x1
#define HWIO_SSC_QDSP6SS_WDOG_CTL_ENABLE_SHFT                                                   0x0

#define HWIO_SSC_QDSP6SS_WDOG_STATUS_ADDR                                                (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00002008)
#define HWIO_SSC_QDSP6SS_WDOG_STATUS_OFFS                                                (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00002008)
#define HWIO_SSC_QDSP6SS_WDOG_STATUS_RMSK                                                0xf81fffff
#define HWIO_SSC_QDSP6SS_WDOG_STATUS_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_WDOG_STATUS_ADDR, HWIO_SSC_QDSP6SS_WDOG_STATUS_RMSK)
#define HWIO_SSC_QDSP6SS_WDOG_STATUS_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_WDOG_STATUS_ADDR, m)
#define HWIO_SSC_QDSP6SS_WDOG_STATUS_RESET_SYNC_STATUS_BMSK                              0x80000000
#define HWIO_SSC_QDSP6SS_WDOG_STATUS_RESET_SYNC_STATUS_SHFT                                    0x1f
#define HWIO_SSC_QDSP6SS_WDOG_STATUS_BITE_TIME_SYNC_STATUS_BMSK                          0x40000000
#define HWIO_SSC_QDSP6SS_WDOG_STATUS_BITE_TIME_SYNC_STATUS_SHFT                                0x1e
#define HWIO_SSC_QDSP6SS_WDOG_STATUS_BARK_TIME_SYNC_STATUS_BMSK                          0x20000000
#define HWIO_SSC_QDSP6SS_WDOG_STATUS_BARK_TIME_SYNC_STATUS_SHFT                                0x1d
#define HWIO_SSC_QDSP6SS_WDOG_STATUS_NMI_TIME_SYNC_STATUS_BMSK                           0x10000000
#define HWIO_SSC_QDSP6SS_WDOG_STATUS_NMI_TIME_SYNC_STATUS_SHFT                                 0x1c
#define HWIO_SSC_QDSP6SS_WDOG_STATUS_TEST_LOAD_SYNC_STATUS_BMSK                           0x8000000
#define HWIO_SSC_QDSP6SS_WDOG_STATUS_TEST_LOAD_SYNC_STATUS_SHFT                                0x1b
#define HWIO_SSC_QDSP6SS_WDOG_STATUS_WDOG_COUNT_BMSK                                       0x1ffffe
#define HWIO_SSC_QDSP6SS_WDOG_STATUS_WDOG_COUNT_SHFT                                            0x1
#define HWIO_SSC_QDSP6SS_WDOG_STATUS_WDOG_EXPIRED_STATUS_BMSK                                   0x1
#define HWIO_SSC_QDSP6SS_WDOG_STATUS_WDOG_EXPIRED_STATUS_SHFT                                   0x0

#define HWIO_SSC_QDSP6SS_WDOG_BARK_TIME_ADDR                                             (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x0000200c)
#define HWIO_SSC_QDSP6SS_WDOG_BARK_TIME_OFFS                                             (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x0000200c)
#define HWIO_SSC_QDSP6SS_WDOG_BARK_TIME_RMSK                                                0xfffff
#define HWIO_SSC_QDSP6SS_WDOG_BARK_TIME_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_WDOG_BARK_TIME_ADDR, HWIO_SSC_QDSP6SS_WDOG_BARK_TIME_RMSK)
#define HWIO_SSC_QDSP6SS_WDOG_BARK_TIME_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_WDOG_BARK_TIME_ADDR, m)
#define HWIO_SSC_QDSP6SS_WDOG_BARK_TIME_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_WDOG_BARK_TIME_ADDR,v)
#define HWIO_SSC_QDSP6SS_WDOG_BARK_TIME_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_WDOG_BARK_TIME_ADDR,m,v,HWIO_SSC_QDSP6SS_WDOG_BARK_TIME_IN)
#define HWIO_SSC_QDSP6SS_WDOG_BARK_TIME_DATA_BMSK                                           0xfffff
#define HWIO_SSC_QDSP6SS_WDOG_BARK_TIME_DATA_SHFT                                               0x0

#define HWIO_SSC_QDSP6SS_WDOG_BITE_TIME_ADDR                                             (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00002010)
#define HWIO_SSC_QDSP6SS_WDOG_BITE_TIME_OFFS                                             (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00002010)
#define HWIO_SSC_QDSP6SS_WDOG_BITE_TIME_RMSK                                                0xfffff
#define HWIO_SSC_QDSP6SS_WDOG_BITE_TIME_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_WDOG_BITE_TIME_ADDR, HWIO_SSC_QDSP6SS_WDOG_BITE_TIME_RMSK)
#define HWIO_SSC_QDSP6SS_WDOG_BITE_TIME_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_WDOG_BITE_TIME_ADDR, m)
#define HWIO_SSC_QDSP6SS_WDOG_BITE_TIME_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_WDOG_BITE_TIME_ADDR,v)
#define HWIO_SSC_QDSP6SS_WDOG_BITE_TIME_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_WDOG_BITE_TIME_ADDR,m,v,HWIO_SSC_QDSP6SS_WDOG_BITE_TIME_IN)
#define HWIO_SSC_QDSP6SS_WDOG_BITE_TIME_DATA_BMSK                                           0xfffff
#define HWIO_SSC_QDSP6SS_WDOG_BITE_TIME_DATA_SHFT                                               0x0

#define HWIO_SSC_QDSP6SS_WDOG_NMI_TIME_ADDR                                              (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00002014)
#define HWIO_SSC_QDSP6SS_WDOG_NMI_TIME_OFFS                                              (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00002014)
#define HWIO_SSC_QDSP6SS_WDOG_NMI_TIME_RMSK                                                 0xfffff
#define HWIO_SSC_QDSP6SS_WDOG_NMI_TIME_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_WDOG_NMI_TIME_ADDR, HWIO_SSC_QDSP6SS_WDOG_NMI_TIME_RMSK)
#define HWIO_SSC_QDSP6SS_WDOG_NMI_TIME_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_WDOG_NMI_TIME_ADDR, m)
#define HWIO_SSC_QDSP6SS_WDOG_NMI_TIME_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_WDOG_NMI_TIME_ADDR,v)
#define HWIO_SSC_QDSP6SS_WDOG_NMI_TIME_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_WDOG_NMI_TIME_ADDR,m,v,HWIO_SSC_QDSP6SS_WDOG_NMI_TIME_IN)
#define HWIO_SSC_QDSP6SS_WDOG_NMI_TIME_DATA_BMSK                                            0xfffff
#define HWIO_SSC_QDSP6SS_WDOG_NMI_TIME_DATA_SHFT                                                0x0

#define HWIO_SSC_QDSP6SS_WDOG_TEST_LOAD_ADDR                                             (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00002018)
#define HWIO_SSC_QDSP6SS_WDOG_TEST_LOAD_OFFS                                             (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00002018)
#define HWIO_SSC_QDSP6SS_WDOG_TEST_LOAD_RMSK                                                    0x1
#define HWIO_SSC_QDSP6SS_WDOG_TEST_LOAD_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_WDOG_TEST_LOAD_ADDR,v)
#define HWIO_SSC_QDSP6SS_WDOG_TEST_LOAD_LOAD_BMSK                                               0x1
#define HWIO_SSC_QDSP6SS_WDOG_TEST_LOAD_LOAD_SHFT                                               0x0

#define HWIO_SSC_QDSP6SS_WDOG_TEST_ADDR                                                  (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x0000201c)
#define HWIO_SSC_QDSP6SS_WDOG_TEST_OFFS                                                  (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x0000201c)
#define HWIO_SSC_QDSP6SS_WDOG_TEST_RMSK                                                    0x1fffff
#define HWIO_SSC_QDSP6SS_WDOG_TEST_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_WDOG_TEST_ADDR, HWIO_SSC_QDSP6SS_WDOG_TEST_RMSK)
#define HWIO_SSC_QDSP6SS_WDOG_TEST_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_WDOG_TEST_ADDR, m)
#define HWIO_SSC_QDSP6SS_WDOG_TEST_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_WDOG_TEST_ADDR,v)
#define HWIO_SSC_QDSP6SS_WDOG_TEST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_WDOG_TEST_ADDR,m,v,HWIO_SSC_QDSP6SS_WDOG_TEST_IN)
#define HWIO_SSC_QDSP6SS_WDOG_TEST_SYNC_STATUS_BMSK                                        0x100000
#define HWIO_SSC_QDSP6SS_WDOG_TEST_SYNC_STATUS_SHFT                                            0x14
#define HWIO_SSC_QDSP6SS_WDOG_TEST_LOAD_VALUE_BMSK                                          0xfffff
#define HWIO_SSC_QDSP6SS_WDOG_TEST_LOAD_VALUE_SHFT                                              0x0

#define HWIO_SSC_QDSP6SS_TS_m_EN_ADDR(m)                                                 (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00003000 + 0x10 * (m))
#define HWIO_SSC_QDSP6SS_TS_m_EN_OFFS(m)                                                 (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00003000 + 0x10 * (m))
#define HWIO_SSC_QDSP6SS_TS_m_EN_RMSK                                                           0x7
#define HWIO_SSC_QDSP6SS_TS_m_EN_MAXm                                                             3
#define HWIO_SSC_QDSP6SS_TS_m_EN_INI(m)        \
        in_dword_masked(HWIO_SSC_QDSP6SS_TS_m_EN_ADDR(m), HWIO_SSC_QDSP6SS_TS_m_EN_RMSK)
#define HWIO_SSC_QDSP6SS_TS_m_EN_INMI(m,mask)    \
        in_dword_masked(HWIO_SSC_QDSP6SS_TS_m_EN_ADDR(m), mask)
#define HWIO_SSC_QDSP6SS_TS_m_EN_OUTI(m,val)    \
        out_dword(HWIO_SSC_QDSP6SS_TS_m_EN_ADDR(m),val)
#define HWIO_SSC_QDSP6SS_TS_m_EN_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_TS_m_EN_ADDR(m),mask,val,HWIO_SSC_QDSP6SS_TS_m_EN_INI(m))
#define HWIO_SSC_QDSP6SS_TS_m_EN_MODE_BMSK                                                      0x4
#define HWIO_SSC_QDSP6SS_TS_m_EN_MODE_SHFT                                                      0x2
#define HWIO_SSC_QDSP6SS_TS_m_EN_CLEAR_BMSK                                                     0x2
#define HWIO_SSC_QDSP6SS_TS_m_EN_CLEAR_SHFT                                                     0x1
#define HWIO_SSC_QDSP6SS_TS_m_EN_EN_BMSK                                                        0x1
#define HWIO_SSC_QDSP6SS_TS_m_EN_EN_SHFT                                                        0x0

#define HWIO_SSC_QDSP6SS_TS_m_STATUS_ADDR(m)                                             (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00003004 + 0x10 * (m))
#define HWIO_SSC_QDSP6SS_TS_m_STATUS_OFFS(m)                                             (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00003004 + 0x10 * (m))
#define HWIO_SSC_QDSP6SS_TS_m_STATUS_RMSK                                                     0x101
#define HWIO_SSC_QDSP6SS_TS_m_STATUS_MAXm                                                         3
#define HWIO_SSC_QDSP6SS_TS_m_STATUS_INI(m)        \
        in_dword_masked(HWIO_SSC_QDSP6SS_TS_m_STATUS_ADDR(m), HWIO_SSC_QDSP6SS_TS_m_STATUS_RMSK)
#define HWIO_SSC_QDSP6SS_TS_m_STATUS_INMI(m,mask)    \
        in_dword_masked(HWIO_SSC_QDSP6SS_TS_m_STATUS_ADDR(m), mask)
#define HWIO_SSC_QDSP6SS_TS_m_STATUS_OVERFLOW_BMSK                                            0x100
#define HWIO_SSC_QDSP6SS_TS_m_STATUS_OVERFLOW_SHFT                                              0x8
#define HWIO_SSC_QDSP6SS_TS_m_STATUS_VALID_BMSK                                                 0x1
#define HWIO_SSC_QDSP6SS_TS_m_STATUS_VALID_SHFT                                                 0x0

#define HWIO_SSC_QDSP6SS_TS_m_TIMESTAMP_L_ADDR(m)                                        (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00003008 + 0x10 * (m))
#define HWIO_SSC_QDSP6SS_TS_m_TIMESTAMP_L_OFFS(m)                                        (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00003008 + 0x10 * (m))
#define HWIO_SSC_QDSP6SS_TS_m_TIMESTAMP_L_RMSK                                           0xffffffff
#define HWIO_SSC_QDSP6SS_TS_m_TIMESTAMP_L_MAXm                                                    3
#define HWIO_SSC_QDSP6SS_TS_m_TIMESTAMP_L_INI(m)        \
        in_dword_masked(HWIO_SSC_QDSP6SS_TS_m_TIMESTAMP_L_ADDR(m), HWIO_SSC_QDSP6SS_TS_m_TIMESTAMP_L_RMSK)
#define HWIO_SSC_QDSP6SS_TS_m_TIMESTAMP_L_INMI(m,mask)    \
        in_dword_masked(HWIO_SSC_QDSP6SS_TS_m_TIMESTAMP_L_ADDR(m), mask)
#define HWIO_SSC_QDSP6SS_TS_m_TIMESTAMP_L_DATA_L_BMSK                                    0xffffffff
#define HWIO_SSC_QDSP6SS_TS_m_TIMESTAMP_L_DATA_L_SHFT                                           0x0

#define HWIO_SSC_QDSP6SS_TS_m_TIMESTAMP_H_ADDR(m)                                        (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x0000300c + 0x10 * (m))
#define HWIO_SSC_QDSP6SS_TS_m_TIMESTAMP_H_OFFS(m)                                        (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x0000300c + 0x10 * (m))
#define HWIO_SSC_QDSP6SS_TS_m_TIMESTAMP_H_RMSK                                             0xffffff
#define HWIO_SSC_QDSP6SS_TS_m_TIMESTAMP_H_MAXm                                                    3
#define HWIO_SSC_QDSP6SS_TS_m_TIMESTAMP_H_INI(m)        \
        in_dword_masked(HWIO_SSC_QDSP6SS_TS_m_TIMESTAMP_H_ADDR(m), HWIO_SSC_QDSP6SS_TS_m_TIMESTAMP_H_RMSK)
#define HWIO_SSC_QDSP6SS_TS_m_TIMESTAMP_H_INMI(m,mask)    \
        in_dword_masked(HWIO_SSC_QDSP6SS_TS_m_TIMESTAMP_H_ADDR(m), mask)
#define HWIO_SSC_QDSP6SS_TS_m_TIMESTAMP_H_DATA_H_BMSK                                      0xffffff
#define HWIO_SSC_QDSP6SS_TS_m_TIMESTAMP_H_DATA_H_SHFT                                           0x0

#define HWIO_SSC_QDSP6SS_TS_HWE_SEL_ADDR                                                 (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00003100)
#define HWIO_SSC_QDSP6SS_TS_HWE_SEL_OFFS                                                 (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00003100)
#define HWIO_SSC_QDSP6SS_TS_HWE_SEL_RMSK                                                       0x1f
#define HWIO_SSC_QDSP6SS_TS_HWE_SEL_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_TS_HWE_SEL_ADDR, HWIO_SSC_QDSP6SS_TS_HWE_SEL_RMSK)
#define HWIO_SSC_QDSP6SS_TS_HWE_SEL_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_TS_HWE_SEL_ADDR, m)
#define HWIO_SSC_QDSP6SS_TS_HWE_SEL_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_TS_HWE_SEL_ADDR,v)
#define HWIO_SSC_QDSP6SS_TS_HWE_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_TS_HWE_SEL_ADDR,m,v,HWIO_SSC_QDSP6SS_TS_HWE_SEL_IN)
#define HWIO_SSC_QDSP6SS_TS_HWE_SEL_MUX_SEL_BMSK                                               0x1f
#define HWIO_SSC_QDSP6SS_TS_HWE_SEL_MUX_SEL_SHFT                                                0x0

#define HWIO_SSC_QDSP6SS_IPC_ADDR                                                        (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00005000)
#define HWIO_SSC_QDSP6SS_IPC_OFFS                                                        (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00005000)
#define HWIO_SSC_QDSP6SS_IPC_RMSK                                                        0xffffffff
#define HWIO_SSC_QDSP6SS_IPC_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_IPC_ADDR,v)
#define HWIO_SSC_QDSP6SS_IPC_INTR_BMSK                                                   0xffffffff
#define HWIO_SSC_QDSP6SS_IPC_INTR_SHFT                                                          0x0

#define HWIO_SSC_QDSP6SS_IPC1_ADDR                                                       (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00005004)
#define HWIO_SSC_QDSP6SS_IPC1_OFFS                                                       (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00005004)
#define HWIO_SSC_QDSP6SS_IPC1_RMSK                                                       0xffffffff
#define HWIO_SSC_QDSP6SS_IPC1_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_IPC1_ADDR,v)
#define HWIO_SSC_QDSP6SS_IPC1_INTR_BMSK                                                  0xffffffff
#define HWIO_SSC_QDSP6SS_IPC1_INTR_SHFT                                                         0x0

#define HWIO_SSC_QDSP6SS_BLOCK_INTR_ADDR                                                 (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00007008)
#define HWIO_SSC_QDSP6SS_BLOCK_INTR_OFFS                                                 (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00007008)
#define HWIO_SSC_QDSP6SS_BLOCK_INTR_RMSK                                                        0x7
#define HWIO_SSC_QDSP6SS_BLOCK_INTR_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_BLOCK_INTR_ADDR, HWIO_SSC_QDSP6SS_BLOCK_INTR_RMSK)
#define HWIO_SSC_QDSP6SS_BLOCK_INTR_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_BLOCK_INTR_ADDR, m)
#define HWIO_SSC_QDSP6SS_BLOCK_INTR_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_BLOCK_INTR_ADDR,v)
#define HWIO_SSC_QDSP6SS_BLOCK_INTR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_BLOCK_INTR_ADDR,m,v,HWIO_SSC_QDSP6SS_BLOCK_INTR_IN)
#define HWIO_SSC_QDSP6SS_BLOCK_INTR_CLEAR_BLOCK_BMSK                                            0x4
#define HWIO_SSC_QDSP6SS_BLOCK_INTR_CLEAR_BLOCK_SHFT                                            0x2
#define HWIO_SSC_QDSP6SS_BLOCK_INTR_BLOCK_STATUS_BMSK                                           0x2
#define HWIO_SSC_QDSP6SS_BLOCK_INTR_BLOCK_STATUS_SHFT                                           0x1
#define HWIO_SSC_QDSP6SS_BLOCK_INTR_BLOCK_INTR_BMSK                                             0x1
#define HWIO_SSC_QDSP6SS_BLOCK_INTR_BLOCK_INTR_SHFT                                             0x0

#define HWIO_SSC_QDSP6SS_SLPC_CFG_ADDR                                                   (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x0000701c)
#define HWIO_SSC_QDSP6SS_SLPC_CFG_OFFS                                                   (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x0000701c)
#define HWIO_SSC_QDSP6SS_SLPC_CFG_RMSK                                                       0x1fa8
#define HWIO_SSC_QDSP6SS_SLPC_CFG_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_SLPC_CFG_ADDR, HWIO_SSC_QDSP6SS_SLPC_CFG_RMSK)
#define HWIO_SSC_QDSP6SS_SLPC_CFG_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_SLPC_CFG_ADDR, m)
#define HWIO_SSC_QDSP6SS_SLPC_CFG_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SLPC_CFG_ADDR,v)
#define HWIO_SSC_QDSP6SS_SLPC_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_SLPC_CFG_ADDR,m,v,HWIO_SSC_QDSP6SS_SLPC_CFG_IN)
#define HWIO_SSC_QDSP6SS_SLPC_CFG_EXTHW_WAKE_EN_BMSK                                         0x1000
#define HWIO_SSC_QDSP6SS_SLPC_CFG_EXTHW_WAKE_EN_SHFT                                            0xc
#define HWIO_SSC_QDSP6SS_SLPC_CFG_MEM_PU_PERI_STAGGER_BMSK                                    0x800
#define HWIO_SSC_QDSP6SS_SLPC_CFG_MEM_PU_PERI_STAGGER_SHFT                                      0xb
#define HWIO_SSC_QDSP6SS_SLPC_CFG_MEM_PD_PERI_STAGGER_BMSK                                    0x400
#define HWIO_SSC_QDSP6SS_SLPC_CFG_MEM_PD_PERI_STAGGER_SHFT                                      0xa
#define HWIO_SSC_QDSP6SS_SLPC_CFG_MEM_PU_ARRY_STAGGER_BMSK                                    0x200
#define HWIO_SSC_QDSP6SS_SLPC_CFG_MEM_PU_ARRY_STAGGER_SHFT                                      0x9
#define HWIO_SSC_QDSP6SS_SLPC_CFG_MEM_PD_ARRY_STAGGER_BMSK                                    0x100
#define HWIO_SSC_QDSP6SS_SLPC_CFG_MEM_PD_ARRY_STAGGER_SHFT                                      0x8
#define HWIO_SSC_QDSP6SS_SLPC_CFG_WAKEUP_IN_EN_BMSK                                            0x80
#define HWIO_SSC_QDSP6SS_SLPC_CFG_WAKEUP_IN_EN_SHFT                                             0x7
#define HWIO_SSC_QDSP6SS_SLPC_CFG_CLK_GATING_MODE_BMSK                                         0x20
#define HWIO_SSC_QDSP6SS_SLPC_CFG_CLK_GATING_MODE_SHFT                                          0x5
#define HWIO_SSC_QDSP6SS_SLPC_CFG_SAW_DBG_BMSK                                                  0x8
#define HWIO_SSC_QDSP6SS_SLPC_CFG_SAW_DBG_SHFT                                                  0x3

#define HWIO_SSC_QDSP6SS_WAKEUP_CTL_ADDR                                                 (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00007024)
#define HWIO_SSC_QDSP6SS_WAKEUP_CTL_OFFS                                                 (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00007024)
#define HWIO_SSC_QDSP6SS_WAKEUP_CTL_RMSK                                                        0x3
#define HWIO_SSC_QDSP6SS_WAKEUP_CTL_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_WAKEUP_CTL_ADDR, HWIO_SSC_QDSP6SS_WAKEUP_CTL_RMSK)
#define HWIO_SSC_QDSP6SS_WAKEUP_CTL_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_WAKEUP_CTL_ADDR, m)
#define HWIO_SSC_QDSP6SS_WAKEUP_CTL_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_WAKEUP_CTL_ADDR,v)
#define HWIO_SSC_QDSP6SS_WAKEUP_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_WAKEUP_CTL_ADDR,m,v,HWIO_SSC_QDSP6SS_WAKEUP_CTL_IN)
#define HWIO_SSC_QDSP6SS_WAKEUP_CTL_NMI_WAKE_EN_BMSK                                            0x2
#define HWIO_SSC_QDSP6SS_WAKEUP_CTL_NMI_WAKE_EN_SHFT                                            0x1
#define HWIO_SSC_QDSP6SS_WAKEUP_CTL_L2VIC_WAKE_EN_BMSK                                          0x1
#define HWIO_SSC_QDSP6SS_WAKEUP_CTL_L2VIC_WAKE_EN_SHFT                                          0x0

#define HWIO_SSC_QDSP6SS_L2VIC_WAKEUP_EN_ADDR                                            (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00007028)
#define HWIO_SSC_QDSP6SS_L2VIC_WAKEUP_EN_OFFS                                            (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00007028)
#define HWIO_SSC_QDSP6SS_L2VIC_WAKEUP_EN_RMSK                                                  0x1c
#define HWIO_SSC_QDSP6SS_L2VIC_WAKEUP_EN_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_L2VIC_WAKEUP_EN_ADDR, HWIO_SSC_QDSP6SS_L2VIC_WAKEUP_EN_RMSK)
#define HWIO_SSC_QDSP6SS_L2VIC_WAKEUP_EN_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_L2VIC_WAKEUP_EN_ADDR, m)
#define HWIO_SSC_QDSP6SS_L2VIC_WAKEUP_EN_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_L2VIC_WAKEUP_EN_ADDR,v)
#define HWIO_SSC_QDSP6SS_L2VIC_WAKEUP_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_L2VIC_WAKEUP_EN_ADDR,m,v,HWIO_SSC_QDSP6SS_L2VIC_WAKEUP_EN_IN)
#define HWIO_SSC_QDSP6SS_L2VIC_WAKEUP_EN_WAKEUP_EN_BMSK                                        0x1c
#define HWIO_SSC_QDSP6SS_L2VIC_WAKEUP_EN_WAKEUP_EN_SHFT                                         0x2

#define HWIO_SSC_QDSP6SS_WAKEUP_STATUS_ADDR                                              (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x0000702c)
#define HWIO_SSC_QDSP6SS_WAKEUP_STATUS_OFFS                                              (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x0000702c)
#define HWIO_SSC_QDSP6SS_WAKEUP_STATUS_RMSK                                                    0x1f
#define HWIO_SSC_QDSP6SS_WAKEUP_STATUS_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_WAKEUP_STATUS_ADDR, HWIO_SSC_QDSP6SS_WAKEUP_STATUS_RMSK)
#define HWIO_SSC_QDSP6SS_WAKEUP_STATUS_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_WAKEUP_STATUS_ADDR, m)
#define HWIO_SSC_QDSP6SS_WAKEUP_STATUS_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_WAKEUP_STATUS_ADDR,v)
#define HWIO_SSC_QDSP6SS_WAKEUP_STATUS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_WAKEUP_STATUS_ADDR,m,v,HWIO_SSC_QDSP6SS_WAKEUP_STATUS_IN)
#define HWIO_SSC_QDSP6SS_WAKEUP_STATUS_AXIS_WAKEUP_STICKY_BMSK                                 0x10
#define HWIO_SSC_QDSP6SS_WAKEUP_STATUS_AXIS_WAKEUP_STICKY_SHFT                                  0x4
#define HWIO_SSC_QDSP6SS_WAKEUP_STATUS_AXIS_WAKEUP_BMSK                                         0x8
#define HWIO_SSC_QDSP6SS_WAKEUP_STATUS_AXIS_WAKEUP_SHFT                                         0x3
#define HWIO_SSC_QDSP6SS_WAKEUP_STATUS_DBG_NMI_BMSK                                             0x4
#define HWIO_SSC_QDSP6SS_WAKEUP_STATUS_DBG_NMI_SHFT                                             0x2
#define HWIO_SSC_QDSP6SS_WAKEUP_STATUS_EXT_TRIGGER_BMSK                                         0x2
#define HWIO_SSC_QDSP6SS_WAKEUP_STATUS_EXT_TRIGGER_SHFT                                         0x1
#define HWIO_SSC_QDSP6SS_WAKEUP_STATUS_L2VIC_WAKEUP_BMSK                                        0x1
#define HWIO_SSC_QDSP6SS_WAKEUP_STATUS_L2VIC_WAKEUP_SHFT                                        0x0

#define HWIO_SSC_QDSP6SS_SPM_EVENT_CTL_ADDR                                              (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00007050)
#define HWIO_SSC_QDSP6SS_SPM_EVENT_CTL_OFFS                                              (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00007050)
#define HWIO_SSC_QDSP6SS_SPM_EVENT_CTL_RMSK                                                   0x3ff
#define HWIO_SSC_QDSP6SS_SPM_EVENT_CTL_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_SPM_EVENT_CTL_ADDR, HWIO_SSC_QDSP6SS_SPM_EVENT_CTL_RMSK)
#define HWIO_SSC_QDSP6SS_SPM_EVENT_CTL_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_SPM_EVENT_CTL_ADDR, m)
#define HWIO_SSC_QDSP6SS_SPM_EVENT_CTL_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPM_EVENT_CTL_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPM_EVENT_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_SPM_EVENT_CTL_ADDR,m,v,HWIO_SSC_QDSP6SS_SPM_EVENT_CTL_IN)
#define HWIO_SSC_QDSP6SS_SPM_EVENT_CTL_PLL_FINE_OVRRD_BMSK                                    0x200
#define HWIO_SSC_QDSP6SS_SPM_EVENT_CTL_PLL_FINE_OVRRD_SHFT                                      0x9
#define HWIO_SSC_QDSP6SS_SPM_EVENT_CTL_LDO_READY_OVRRD_BMSK                                   0x100
#define HWIO_SSC_QDSP6SS_SPM_EVENT_CTL_LDO_READY_OVRRD_SHFT                                     0x8
#define HWIO_SSC_QDSP6SS_SPM_EVENT_CTL_SMMU_STATUS_OVRRD_BMSK                                  0x80
#define HWIO_SSC_QDSP6SS_SPM_EVENT_CTL_SMMU_STATUS_OVRRD_SHFT                                   0x7
#define HWIO_SSC_QDSP6SS_SPM_EVENT_CTL_AXIM2_HALTACK_OVRRD_BMSK                                0x40
#define HWIO_SSC_QDSP6SS_SPM_EVENT_CTL_AXIM2_HALTACK_OVRRD_SHFT                                 0x6
#define HWIO_SSC_QDSP6SS_SPM_EVENT_CTL_AXIM_HALTACK_OVRRD_BMSK                                 0x20
#define HWIO_SSC_QDSP6SS_SPM_EVENT_CTL_AXIM_HALTACK_OVRRD_SHFT                                  0x5
#define HWIO_SSC_QDSP6SS_SPM_EVENT_CTL_ALL_HALTACK_OVRRD_BMSK                                  0x10
#define HWIO_SSC_QDSP6SS_SPM_EVENT_CTL_ALL_HALTACK_OVRRD_SHFT                                   0x4
#define HWIO_SSC_QDSP6SS_SPM_EVENT_CTL_CORE_CLK_OFF_OVRRD_BMSK                                  0x8
#define HWIO_SSC_QDSP6SS_SPM_EVENT_CTL_CORE_CLK_OFF_OVRRD_SHFT                                  0x3
#define HWIO_SSC_QDSP6SS_SPM_EVENT_CTL_BHS_ACK_OVRRD_BMSK                                       0x4
#define HWIO_SSC_QDSP6SS_SPM_EVENT_CTL_BHS_ACK_OVRRD_SHFT                                       0x2
#define HWIO_SSC_QDSP6SS_SPM_EVENT_CTL_PLL_OVRRD_BMSK                                           0x2
#define HWIO_SSC_QDSP6SS_SPM_EVENT_CTL_PLL_OVRRD_SHFT                                           0x1
#define HWIO_SSC_QDSP6SS_SPM_EVENT_CTL_EXT_PLL_OVRRD_BMSK                                       0x1
#define HWIO_SSC_QDSP6SS_SPM_EVENT_CTL_EXT_PLL_OVRRD_SHFT                                       0x0

#define HWIO_SSC_QDSP6SS_SPM_TRIG_CFGn_ADDR(n)                                           (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00007080 + 0x4 * (n))
#define HWIO_SSC_QDSP6SS_SPM_TRIG_CFGn_OFFS(n)                                           (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00007080 + 0x4 * (n))
#define HWIO_SSC_QDSP6SS_SPM_TRIG_CFGn_RMSK                                                   0x1ff
#define HWIO_SSC_QDSP6SS_SPM_TRIG_CFGn_MAXn                                                       3
#define HWIO_SSC_QDSP6SS_SPM_TRIG_CFGn_INI(n)        \
        in_dword_masked(HWIO_SSC_QDSP6SS_SPM_TRIG_CFGn_ADDR(n), HWIO_SSC_QDSP6SS_SPM_TRIG_CFGn_RMSK)
#define HWIO_SSC_QDSP6SS_SPM_TRIG_CFGn_INMI(n,mask)    \
        in_dword_masked(HWIO_SSC_QDSP6SS_SPM_TRIG_CFGn_ADDR(n), mask)
#define HWIO_SSC_QDSP6SS_SPM_TRIG_CFGn_OUTI(n,val)    \
        out_dword(HWIO_SSC_QDSP6SS_SPM_TRIG_CFGn_ADDR(n),val)
#define HWIO_SSC_QDSP6SS_SPM_TRIG_CFGn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_SPM_TRIG_CFGn_ADDR(n),mask,val,HWIO_SSC_QDSP6SS_SPM_TRIG_CFGn_INI(n))
#define HWIO_SSC_QDSP6SS_SPM_TRIG_CFGn_SPM_STARTADDR_BMSK                                     0x1ff
#define HWIO_SSC_QDSP6SS_SPM_TRIG_CFGn_SPM_STARTADDR_SHFT                                       0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_ADDR                                             (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00007100)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_OFFS                                             (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00007100)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_RMSK                                                  0xfff
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_ADDR, HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_RMSK)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_ADDR, m)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_ADDR,m,v,HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_IN)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CP0_BMSK                                              0x800
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CP0_SHFT                                                0xb
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CSI1_BMSK                                             0x400
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CSI1_SHFT                                               0xa
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CSI0_BMSK                                             0x200
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CSI0_SHFT                                               0x9
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_ARCH_BMSK                                             0x100
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_ARCH_SHFT                                               0x8
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_RET_BMSK                                               0x80
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_RET_SHFT                                                0x7
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_AXIM2_BMSK                                             0x40
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_AXIM2_SHFT                                              0x6
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_AXIS_BMSK                                              0x20
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_AXIS_SHFT                                               0x5
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_ATBM_BMSK                                              0x10
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_ATBM_SHFT                                               0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_AHBM_BMSK                                               0x8
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_AHBM_SHFT                                               0x3
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_AXIM_BMSK                                               0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_AXIM_SHFT                                               0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_ISDB_ETM_BMSK                                           0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_ISDB_ETM_SHFT                                           0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CORE_BMSK                                               0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CORE_SHFT                                               0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLAMP_ADDR                                            (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00007104)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLAMP_OFFS                                            (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00007104)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLAMP_RMSK                                                   0x3
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLAMP_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_SPMCTL_EN_CLAMP_ADDR, HWIO_SSC_QDSP6SS_SPMCTL_EN_CLAMP_RMSK)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLAMP_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_SPMCTL_EN_CLAMP_ADDR, m)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLAMP_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_CLAMP_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLAMP_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_SPMCTL_EN_CLAMP_ADDR,m,v,HWIO_SSC_QDSP6SS_SPMCTL_EN_CLAMP_IN)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLAMP_CLAMP_CP0_BMSK                                         0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLAMP_CLAMP_CP0_SHFT                                         0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLAMP_CLAMP_IO_BMSK                                          0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLAMP_CLAMP_IO_SHFT                                          0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_ADDR                                              (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00007108)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_OFFS                                              (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00007108)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_RMSK                                                   0x3fd
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_ADDR, HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_RMSK)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_ADDR, m)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_ADDR,m,v,HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_IN)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_CP0_BMSK                                               0x200
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_CP0_SHFT                                                 0x9
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_CSI1_BMSK                                              0x100
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_CSI1_SHFT                                                0x8
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_CSI0_BMSK                                               0x80
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_CSI0_SHFT                                                0x7
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_AXIM2_BMSK                                              0x40
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_AXIM2_SHFT                                               0x6
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_AXIS_BMSK                                               0x20
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_AXIS_SHFT                                                0x5
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_ATBM_BMSK                                               0x10
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_ATBM_SHFT                                                0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_AHBM_BMSK                                                0x8
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_AHBM_SHFT                                                0x3
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_AXIM_BMSK                                                0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_AXIM_SHFT                                                0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_CORE_BMSK                                                0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_CORE_SHFT                                                0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_ADDR                                          (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x0000710c)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_OFFS                                          (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x0000710c)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_RMSK                                          0x1fffffff
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_ADDR, HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_RMSK)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_ADDR, m)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_ADDR,m,v,HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_IN)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_JU_BMSK                                       0x1c000000
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_JU_SHFT                                             0x1a
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_ETB_BMSK                                       0x2000000
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_ETB_SHFT                                            0x19
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_L1IU_BMSK                                      0x1800000
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_L1IU_SHFT                                           0x17
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_L1DU_BMSK                                       0x600000
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_L1DU_SHFT                                           0x15
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_L2PLRU_BMSK                                     0x100000
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_L2PLRU_SHFT                                         0x14
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_L2TAG_BMSK                                       0xf0000
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_L2TAG_SHFT                                          0x10
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_L2DATA_BMSK                                       0xffff
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_L2DATA_SHFT                                          0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_ADDR                                          (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00007110)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_OFFS                                          (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00007110)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_RMSK                                                 0xf
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_ADDR, HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_RMSK)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_ADDR, m)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_ADDR,m,v,HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_IN)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_CLAMP_QMC_MEM_BMSK                                   0x8
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_CLAMP_QMC_MEM_SHFT                                   0x3
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_CLAMP_WL_BMSK                                        0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_CLAMP_WL_SHFT                                        0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_MEM_PERIPH_BMSK                                      0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_MEM_PERIPH_SHFT                                      0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_ARR_STBY_BMSK                                        0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_ARR_STBY_SHFT                                        0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_BHS_ADDR                                              (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00007114)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_BHS_OFFS                                              (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00007114)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_BHS_RMSK                                                     0x3
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_BHS_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_SPMCTL_EN_BHS_ADDR, HWIO_SSC_QDSP6SS_SPMCTL_EN_BHS_RMSK)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_BHS_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_SPMCTL_EN_BHS_ADDR, m)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_BHS_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_BHS_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_BHS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_SPMCTL_EN_BHS_ADDR,m,v,HWIO_SSC_QDSP6SS_SPMCTL_EN_BHS_IN)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_BHS_CP0_BHS_BMSK                                             0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_BHS_CP0_BHS_SHFT                                             0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_BHS_BHS_BMSK                                                 0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_BHS_BHS_SHFT                                                 0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_ADDR                                              (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00007118)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_OFFS                                              (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00007118)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_RMSK                                                    0x61
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_ADDR, HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_RMSK)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_ADDR, m)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_ADDR,m,v,HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_IN)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_BG_OFF_BMSK                                             0x40
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_BG_OFF_SHFT                                              0x6
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_FORCEOFF_BMSK                                           0x20
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_FORCEOFF_SHFT                                            0x5
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_BYPASS_OPEN_BMSK                                         0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_BYPASS_OPEN_SHFT                                         0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_ADDR                                              (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x0000711c)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_OFFS                                              (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x0000711c)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_RMSK                                                   0x7cf
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_ADDR, HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_RMSK)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_ADDR, m)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_ADDR,m,v,HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_IN)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_SMMU_PD_VOTE_BMSK                                      0x400
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_SMMU_PD_VOTE_SHFT                                        0xa
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_SHUTDOWN_REQ_BMSK                                      0x200
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_SHUTDOWN_REQ_SHFT                                        0x9
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_SPARE1_BMSK                                            0x100
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_SPARE1_SHFT                                              0x8
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_BHS_BMSK                                                0x80
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_BHS_SHFT                                                 0x7
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_XO_ENABLE_BMSK                                          0x40
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_XO_ENABLE_SHFT                                           0x6
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_PLL_VOTE_BMSK                                            0x8
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_PLL_VOTE_SHFT                                            0x3
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_PLL_OUTDIS_BMSK                                          0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_PLL_OUTDIS_SHFT                                          0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_PLL_BYPASS_BMSK                                          0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_PLL_BYPASS_SHFT                                          0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_PLL_RESET_BMSK                                           0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_PLL_RESET_SHFT                                           0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_ADDR                                              (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00007120)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_OFFS                                              (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00007120)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_RMSK                                                    0x1f
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_ADDR, HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_RMSK)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_ADDR, m)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_ADDR,m,v,HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_IN)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_PLL_STBY_BMSK                                           0x10
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_PLL_STBY_SHFT                                            0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_PLL_VOTE_BMSK                                            0x8
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_PLL_VOTE_SHFT                                            0x3
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_PLL_OUTDIS_BMSK                                          0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_PLL_OUTDIS_SHFT                                          0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_PLL_OPMODE1_BMSK                                         0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_PLL_OPMODE1_SHFT                                         0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_PLL_RESET_BMSK                                           0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_PLL_RESET_SHFT                                           0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_ADDR                                         (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00007124)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_OFFS                                         (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00007124)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_RMSK                                                0x7
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_ADDR, HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_RMSK)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_ADDR, m)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_ADDR,m,v,HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_IN)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_WAKE_IRQ_BMSK                                       0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_WAKE_IRQ_SHFT                                       0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_RESTORE_BMSK                                        0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_RESTORE_SHFT                                        0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_SAVE_BMSK                                           0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_SAVE_SHFT                                           0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_ADDR                                      (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00007128)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_OFFS                                      (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00007128)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_RMSK                                            0x3d
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_ADDR, HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_RMSK)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_ADDR, m)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_ADDR,m,v,HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_IN)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_AXIM2_FIFO_ARESET_BMSK                          0x20
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_AXIM2_FIFO_ARESET_SHFT                           0x5
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_AXIM2_HALTREQ_BMSK                              0x10
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_AXIM2_HALTREQ_SHFT                               0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_AXIM_FIFO_ARESET_BMSK                            0x8
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_AXIM_FIFO_ARESET_SHFT                            0x3
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_AXIM_HALTREQ_BMSK                                0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_AXIM_HALTREQ_SHFT                                0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_BUSM_HALTREQ_BMSK                                0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_BUSM_HALTREQ_SHFT                                0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_ADDR                                    (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x0000712c)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_OFFS                                    (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x0000712c)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_RMSK                                          0xff
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_ADDR, HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_RMSK)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_ADDR, m)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_ADDR,m,v,HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_IN)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_AXIM2_CLAMP_E_CLEAR_BMSK                      0x80
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_AXIM2_CLAMP_E_CLEAR_SHFT                       0x7
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_AXIM2_CLAMP_E_SET_BMSK                        0x40
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_AXIM2_CLAMP_E_SET_SHFT                         0x6
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_AXIM2_CLAMP_L_CLEAR_BMSK                      0x20
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_AXIM2_CLAMP_L_CLEAR_SHFT                       0x5
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_AXIM2_CLAMP_L_SET_BMSK                        0x10
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_AXIM2_CLAMP_L_SET_SHFT                         0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_AXIM_CLAMP_E_CLEAR_BMSK                        0x8
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_AXIM_CLAMP_E_CLEAR_SHFT                        0x3
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_AXIM_CLAMP_E_SET_BMSK                          0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_AXIM_CLAMP_E_SET_SHFT                          0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_AXIM_CLAMP_L_CLEAR_BMSK                        0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_AXIM_CLAMP_L_CLEAR_SHFT                        0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_AXIM_CLAMP_L_SET_BMSK                          0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_AXIM_CLAMP_L_SET_SHFT                          0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_ADDR                                      (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00007130)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_OFFS                                      (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00007130)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_RMSK                                             0x7
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_ADDR, HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_RMSK)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_ADDR, m)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_ADDR,m,v,HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_IN)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_AXIM2_BMSK                                       0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_AXIM2_SHFT                                       0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_AXIM_BMSK                                        0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_AXIM_SHFT                                        0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_CORE_BMSK                                        0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_CORE_SHFT                                        0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_L1S_ADDR                                          (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00007140)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_L1S_OFFS                                          (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00007140)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_L1S_RMSK                                                0xff
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_L1S_IN          \
        in_dword_masked(HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_L1S_ADDR, HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_L1S_RMSK)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_L1S_INM(m)      \
        in_dword_masked(HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_L1S_ADDR, m)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_L1S_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_L1S_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_L1S_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_L1S_ADDR,m,v,HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_L1S_IN)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_L1S_L1S_BMSK                                            0xff
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_L1S_L1S_SHFT                                             0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_SET_ADDR                                         (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00007180)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_SET_OFFS                                         (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00007180)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_SET_RMSK                                              0xfff
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_SET_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_SET_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_SET_CP0_BMSK                                          0x800
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_SET_CP0_SHFT                                            0xb
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_SET_CSI1_BMSK                                         0x400
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_SET_CSI1_SHFT                                           0xa
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_SET_CSI0_BMSK                                         0x200
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_SET_CSI0_SHFT                                           0x9
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_SET_ARCH_BMSK                                         0x100
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_SET_ARCH_SHFT                                           0x8
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_SET_RET_BMSK                                           0x80
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_SET_RET_SHFT                                            0x7
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_SET_AXIM2_BMSK                                         0x40
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_SET_AXIM2_SHFT                                          0x6
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_SET_AXIS_BMSK                                          0x20
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_SET_AXIS_SHFT                                           0x5
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_SET_ATBM_BMSK                                          0x10
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_SET_ATBM_SHFT                                           0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_SET_AHBM_BMSK                                           0x8
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_SET_AHBM_SHFT                                           0x3
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_SET_AXIM_BMSK                                           0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_SET_AXIM_SHFT                                           0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_SET_ISDB_ETM_BMSK                                       0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_SET_ISDB_ETM_SHFT                                       0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_SET_CORE_BMSK                                           0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_SET_CORE_SHFT                                           0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLAMP_SET_ADDR                                        (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00007184)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLAMP_SET_OFFS                                        (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00007184)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLAMP_SET_RMSK                                               0x3
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLAMP_SET_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_CLAMP_SET_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLAMP_SET_CLAMP_CP0_BMSK                                     0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLAMP_SET_CLAMP_CP0_SHFT                                     0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLAMP_SET_CLAMP_IO_BMSK                                      0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLAMP_SET_CLAMP_IO_SHFT                                      0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_SET_ADDR                                          (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00007188)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_SET_OFFS                                          (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00007188)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_SET_RMSK                                               0x3fd
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_SET_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_SET_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_SET_CP0_BMSK                                           0x200
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_SET_CP0_SHFT                                             0x9
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_SET_CSI1_BMSK                                          0x100
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_SET_CSI1_SHFT                                            0x8
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_SET_CSI0_BMSK                                           0x80
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_SET_CSI0_SHFT                                            0x7
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_SET_AXIM2_BMSK                                          0x40
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_SET_AXIM2_SHFT                                           0x6
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_SET_AXIS_BMSK                                           0x20
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_SET_AXIS_SHFT                                            0x5
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_SET_ATBM_BMSK                                           0x10
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_SET_ATBM_SHFT                                            0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_SET_AHBM_BMSK                                            0x8
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_SET_AHBM_SHFT                                            0x3
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_SET_AXIM_BMSK                                            0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_SET_AXIM_SHFT                                            0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_SET_CORE_BMSK                                            0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_SET_CORE_SHFT                                            0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_SET_ADDR                                      (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x0000718c)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_SET_OFFS                                      (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x0000718c)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_SET_RMSK                                      0x1fffffff
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_SET_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_SET_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_SET_JU_BMSK                                   0x1c000000
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_SET_JU_SHFT                                         0x1a
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_SET_ETB_BMSK                                   0x2000000
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_SET_ETB_SHFT                                        0x19
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_SET_L1IU_BMSK                                  0x1800000
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_SET_L1IU_SHFT                                       0x17
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_SET_L1DU_BMSK                                   0x600000
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_SET_L1DU_SHFT                                       0x15
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_SET_L2PLRU_BMSK                                 0x100000
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_SET_L2PLRU_SHFT                                     0x14
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_SET_L2TAG_BMSK                                   0xf0000
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_SET_L2TAG_SHFT                                      0x10
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_SET_L2DATA_BMSK                                   0xffff
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_SET_L2DATA_SHFT                                      0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_SET_ADDR                                      (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00007190)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_SET_OFFS                                      (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00007190)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_SET_RMSK                                             0xf
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_SET_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_SET_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_SET_CLAMP_QMC_MEM_BMSK                               0x8
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_SET_CLAMP_QMC_MEM_SHFT                               0x3
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_SET_CLAMP_WL_BMSK                                    0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_SET_CLAMP_WL_SHFT                                    0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_SET_MEM_PERIPH_BMSK                                  0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_SET_MEM_PERIPH_SHFT                                  0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_SET_L2DATA_STBY_BMSK                                 0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_SET_L2DATA_STBY_SHFT                                 0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_BHS_SET_ADDR                                          (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00007194)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_BHS_SET_OFFS                                          (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00007194)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_BHS_SET_RMSK                                                 0x3
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_BHS_SET_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_BHS_SET_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_BHS_SET_CP0_BHS_BMSK                                         0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_BHS_SET_CP0_BHS_SHFT                                         0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_BHS_SET_BHS_BMSK                                             0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_BHS_SET_BHS_SHFT                                             0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_SET_ADDR                                          (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00007198)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_SET_OFFS                                          (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00007198)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_SET_RMSK                                                0x61
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_SET_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_SET_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_SET_BG_OFF_BMSK                                         0x40
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_SET_BG_OFF_SHFT                                          0x6
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_SET_FORCEOFF_BMSK                                       0x20
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_SET_FORCEOFF_SHFT                                        0x5
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_SET_BYPASS_OPEN_BMSK                                     0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_SET_BYPASS_OPEN_SHFT                                     0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_SET_ADDR                                          (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x0000719c)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_SET_OFFS                                          (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x0000719c)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_SET_RMSK                                               0x7cf
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_SET_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_SET_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_SET_SMMU_PD_VOTE_BMSK                                  0x400
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_SET_SMMU_PD_VOTE_SHFT                                    0xa
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_SET_SHUTDOWN_REQ_BMSK                                  0x200
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_SET_SHUTDOWN_REQ_SHFT                                    0x9
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_SET_SPARE1_BMSK                                        0x100
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_SET_SPARE1_SHFT                                          0x8
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_SET_BHS_BMSK                                            0x80
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_SET_BHS_SHFT                                             0x7
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_SET_XO_ENABLE_BMSK                                      0x40
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_SET_XO_ENABLE_SHFT                                       0x6
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_SET_PLL_VOTE_BMSK                                        0x8
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_SET_PLL_VOTE_SHFT                                        0x3
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_SET_PLL_OUTDIS_BMSK                                      0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_SET_PLL_OUTDIS_SHFT                                      0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_SET_PLL_BYPASS_BMSK                                      0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_SET_PLL_BYPASS_SHFT                                      0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_SET_PLL_RESET_BMSK                                       0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_SET_PLL_RESET_SHFT                                       0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_SET_ADDR                                          (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x000071a0)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_SET_OFFS                                          (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x000071a0)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_SET_RMSK                                                0x1f
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_SET_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_SET_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_SET_PLL_STBY_BMSK                                       0x10
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_SET_PLL_STBY_SHFT                                        0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_SET_PLL_VOTE_BMSK                                        0x8
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_SET_PLL_VOTE_SHFT                                        0x3
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_SET_PLL_OUTDIS_BMSK                                      0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_SET_PLL_OUTDIS_SHFT                                      0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_SET_PLL_OPMODE1_BMSK                                     0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_SET_PLL_OPMODE1_SHFT                                     0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_SET_PLL_RESET_BMSK                                       0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_SET_PLL_RESET_SHFT                                       0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_SET_ADDR                                     (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x000071a4)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_SET_OFFS                                     (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x000071a4)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_SET_RMSK                                            0x7
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_SET_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_SET_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_SET_WAKE_IRQ_BMSK                                   0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_SET_WAKE_IRQ_SHFT                                   0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_SET_RESTORE_BMSK                                    0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_SET_RESTORE_SHFT                                    0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_SET_SAVE_BMSK                                       0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_SET_SAVE_SHFT                                       0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_SET_ADDR                                  (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x000071a8)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_SET_OFFS                                  (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x000071a8)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_SET_RMSK                                        0x3d
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_SET_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_SET_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_SET_AXIM2_FIFO_ARESET_BMSK                      0x20
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_SET_AXIM2_FIFO_ARESET_SHFT                       0x5
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_SET_AXIM2_HALTREQ_BMSK                          0x10
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_SET_AXIM2_HALTREQ_SHFT                           0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_SET_AXIM_FIFO_ARESET_BMSK                        0x8
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_SET_AXIM_FIFO_ARESET_SHFT                        0x3
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_SET_AXIM_HALTREQ_BMSK                            0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_SET_AXIM_HALTREQ_SHFT                            0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_SET_BUSM_HALTREQ_BMSK                            0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_SET_BUSM_HALTREQ_SHFT                            0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_ADDR                                (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x000071ac)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_OFFS                                (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x000071ac)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_RMSK                                      0xff
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_AXIM2_CLAMP_E_CLEAR_BMSK                  0x80
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_AXIM2_CLAMP_E_CLEAR_SHFT                   0x7
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_AXIM2_CLAMP_E_SET_BMSK                    0x40
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_AXIM2_CLAMP_E_SET_SHFT                     0x6
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_AXIM2_CLAMP_L_CLEAR_BMSK                  0x20
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_AXIM2_CLAMP_L_CLEAR_SHFT                   0x5
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_AXIM2_CLAMP_L_SET_BMSK                    0x10
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_AXIM2_CLAMP_L_SET_SHFT                     0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_AXIM_CLAMP_E_CLEAR_BMSK                    0x8
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_AXIM_CLAMP_E_CLEAR_SHFT                    0x3
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_AXIM_CLAMP_E_SET_BMSK                      0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_AXIM_CLAMP_E_SET_SHFT                      0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_AXIM_CLAMP_L_CLEAR_BMSK                    0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_AXIM_CLAMP_L_CLEAR_SHFT                    0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_AXIM_CLAMP_L_SET_BMSK                      0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_AXIM_CLAMP_L_SET_SHFT                      0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_SET_ADDR                                  (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x000071b0)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_SET_OFFS                                  (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x000071b0)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_SET_RMSK                                         0x7
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_SET_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_SET_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_SET_AXIM2_BMSK                                   0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_SET_AXIM2_SHFT                                   0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_SET_AXIM_BMSK                                    0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_SET_AXIM_SHFT                                    0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_SET_CORE_BMSK                                    0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_SET_CORE_SHFT                                    0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_L1S_SET_ADDR                                      (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x000071c0)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_L1S_SET_OFFS                                      (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x000071c0)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_L1S_SET_RMSK                                            0xff
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_L1S_SET_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_L1S_SET_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_L1S_SET_L1S_BMSK                                        0xff
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_L1S_SET_L1S_SHFT                                         0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CLEAR_ADDR                                       (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00007200)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CLEAR_OFFS                                       (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00007200)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CLEAR_RMSK                                            0xfff
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CLEAR_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CLEAR_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CLEAR_CP0_BMSK                                        0x800
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CLEAR_CP0_SHFT                                          0xb
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CLEAR_CSI1_BMSK                                       0x400
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CLEAR_CSI1_SHFT                                         0xa
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CLEAR_CSI0_BMSK                                       0x200
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CLEAR_CSI0_SHFT                                         0x9
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CLEAR_ARCH_BMSK                                       0x100
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CLEAR_ARCH_SHFT                                         0x8
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CLEAR_RET_BMSK                                         0x80
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CLEAR_RET_SHFT                                          0x7
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CLEAR_AXIM2_BMSK                                       0x40
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CLEAR_AXIM2_SHFT                                        0x6
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CLEAR_AXIS_BMSK                                        0x20
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CLEAR_AXIS_SHFT                                         0x5
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CLEAR_ATBM_BMSK                                        0x10
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CLEAR_ATBM_SHFT                                         0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CLEAR_AHBM_BMSK                                         0x8
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CLEAR_AHBM_SHFT                                         0x3
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CLEAR_AXIM_BMSK                                         0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CLEAR_AXIM_SHFT                                         0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CLEAR_ISDB_ETM_BMSK                                     0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CLEAR_ISDB_ETM_SHFT                                     0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CLEAR_CORE_BMSK                                         0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ARES_CLEAR_CORE_SHFT                                         0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLAMP_CLEAR_ADDR                                      (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00007204)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLAMP_CLEAR_OFFS                                      (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00007204)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLAMP_CLEAR_RMSK                                             0x3
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLAMP_CLEAR_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_CLAMP_CLEAR_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLAMP_CLEAR_CLAMP_CP0_BMSK                                   0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLAMP_CLEAR_CLAMP_CP0_SHFT                                   0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLAMP_CLEAR_CLAMP_IO_BMSK                                    0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLAMP_CLEAR_CLAMP_IO_SHFT                                    0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_CLEAR_ADDR                                        (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00007208)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_CLEAR_OFFS                                        (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00007208)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_CLEAR_RMSK                                             0x3fd
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_CLEAR_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_CLEAR_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_CLEAR_CP0_BMSK                                         0x200
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_CLEAR_CP0_SHFT                                           0x9
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_CLEAR_CSI1_BMSK                                        0x100
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_CLEAR_CSI1_SHFT                                          0x8
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_CLEAR_CSI0_BMSK                                         0x80
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_CLEAR_CSI0_SHFT                                          0x7
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_CLEAR_AXIM2_BMSK                                        0x40
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_CLEAR_AXIM2_SHFT                                         0x6
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_CLEAR_AXIS_BMSK                                         0x20
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_CLEAR_AXIS_SHFT                                          0x5
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_CLEAR_ATBM_BMSK                                         0x10
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_CLEAR_ATBM_SHFT                                          0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_CLEAR_AHBM_BMSK                                          0x8
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_CLEAR_AHBM_SHFT                                          0x3
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_CLEAR_AXIM_BMSK                                          0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_CLEAR_AXIM_SHFT                                          0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_CLEAR_CORE_BMSK                                          0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_CLK_CLEAR_CORE_SHFT                                          0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_ADDR                                    (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x0000720c)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_OFFS                                    (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x0000720c)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_RMSK                                    0x1fffffff
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_JU_BMSK                                 0x1c000000
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_JU_SHFT                                       0x1a
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_ETB_BMSK                                 0x2000000
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_ETB_SHFT                                      0x19
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_L1IU_BMSK                                0x1800000
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_L1IU_SHFT                                     0x17
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_L1DU_BMSK                                 0x600000
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_L1DU_SHFT                                     0x15
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_L2PLRU_BMSK                               0x100000
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_L2PLRU_SHFT                                   0x14
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_L2TAG_BMSK                                 0xf0000
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_L2TAG_SHFT                                    0x10
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_L2DATA_BMSK                                 0xffff
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_L2DATA_SHFT                                    0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_CLEAR_ADDR                                    (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00007210)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_CLEAR_OFFS                                    (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00007210)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_CLEAR_RMSK                                           0xf
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_CLEAR_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_CLEAR_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_CLEAR_CLAMP_QMC_MEM_BMSK                             0x8
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_CLEAR_CLAMP_QMC_MEM_SHFT                             0x3
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_CLEAR_CLAMP_WL_BMSK                                  0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_CLEAR_CLAMP_WL_SHFT                                  0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_CLEAR_MEM_PERIPH_BMSK                                0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_CLEAR_MEM_PERIPH_SHFT                                0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_CLEAR_L2DATA_STBY_BMSK                               0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_CTL_CLEAR_L2DATA_STBY_SHFT                               0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_BHS_CLEAR_ADDR                                        (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00007214)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_BHS_CLEAR_OFFS                                        (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00007214)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_BHS_CLEAR_RMSK                                               0x3
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_BHS_CLEAR_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_BHS_CLEAR_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_BHS_CLEAR_CP0_BHS_BMSK                                       0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_BHS_CLEAR_CP0_BHS_SHFT                                       0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_BHS_CLEAR_BHS_BMSK                                           0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_BHS_CLEAR_BHS_SHFT                                           0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_CLEAR_ADDR                                        (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00007218)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_CLEAR_OFFS                                        (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00007218)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_CLEAR_RMSK                                              0x61
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_CLEAR_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_CLEAR_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_CLEAR_BG_OFF_BMSK                                       0x40
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_CLEAR_BG_OFF_SHFT                                        0x6
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_CLEAR_FORCEOFF_BMSK                                     0x20
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_CLEAR_FORCEOFF_SHFT                                      0x5
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_CLEAR_BYPASS_OPEN_BMSK                                   0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_LDO_CLEAR_BYPASS_OPEN_SHFT                                   0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_CLEAR_ADDR                                        (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x0000721c)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_CLEAR_OFFS                                        (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x0000721c)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_CLEAR_RMSK                                             0x7cf
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_CLEAR_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_CLEAR_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_CLEAR_SMMU_PD_VOTE_BMSK                                0x400
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_CLEAR_SMMU_PD_VOTE_SHFT                                  0xa
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_CLEAR_SHUTDOWN_REQ_BMSK                                0x200
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_CLEAR_SHUTDOWN_REQ_SHFT                                  0x9
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_CLEAR_SPARE1_BMSK                                      0x100
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_CLEAR_SPARE1_SHFT                                        0x8
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_CLEAR_BHS_BMSK                                          0x80
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_CLEAR_BHS_SHFT                                           0x7
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_CLEAR_XO_ENABLE_BMSK                                    0x40
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_CLEAR_XO_ENABLE_SHFT                                     0x6
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_CLEAR_PLL_VOTE_BMSK                                      0x8
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_CLEAR_PLL_VOTE_SHFT                                      0x3
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_CLEAR_PLL_OUTDIS_BMSK                                    0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_CLEAR_PLL_OUTDIS_SHFT                                    0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_CLEAR_PLL_BYPASS_BMSK                                    0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_CLEAR_PLL_BYPASS_SHFT                                    0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_CLEAR_PLL_RESET_BMSK                                     0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_EXT_CLEAR_PLL_RESET_SHFT                                     0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_CLEAR_ADDR                                        (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00007220)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_CLEAR_OFFS                                        (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00007220)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_CLEAR_RMSK                                              0x1f
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_CLEAR_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_CLEAR_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_CLEAR_PLL_STBY_BMSK                                     0x10
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_CLEAR_PLL_STBY_SHFT                                      0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_CLEAR_PLL_VOTE_BMSK                                      0x8
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_CLEAR_PLL_VOTE_SHFT                                      0x3
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_CLEAR_PLL_OUTDIS_BMSK                                    0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_CLEAR_PLL_OUTDIS_SHFT                                    0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_CLEAR_PLL_OPMODE1_BMSK                                   0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_CLEAR_PLL_OPMODE1_SHFT                                   0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_CLEAR_PLL_RESET_BMSK                                     0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_PLL_CLEAR_PLL_RESET_SHFT                                     0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_CLEAR_ADDR                                   (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00007224)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_CLEAR_OFFS                                   (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00007224)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_CLEAR_RMSK                                          0x7
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_CLEAR_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_CLEAR_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_CLEAR_WAKE_IRQ_BMSK                                 0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_CLEAR_WAKE_IRQ_SHFT                                 0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_CLEAR_RESTORE_BMSK                                  0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_CLEAR_RESTORE_SHFT                                  0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_CLEAR_SAVE_BMSK                                     0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_STATERET_CLEAR_SAVE_SHFT                                     0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_CLEAR_ADDR                                (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00007228)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_CLEAR_OFFS                                (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00007228)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_CLEAR_RMSK                                      0x3d
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_CLEAR_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_CLEAR_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_CLEAR_AXIM2_FIFO_ARESET_BMSK                    0x20
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_CLEAR_AXIM2_FIFO_ARESET_SHFT                     0x5
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_CLEAR_AXIM2_HALTREQ_BMSK                        0x10
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_CLEAR_AXIM2_HALTREQ_SHFT                         0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_CLEAR_AXIM_FIFO_ARESET_BMSK                      0x8
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_CLEAR_AXIM_FIFO_ARESET_SHFT                      0x3
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_CLEAR_AXIM_HALTREQ_BMSK                          0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_CLEAR_AXIM_HALTREQ_SHFT                          0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_CLEAR_BUSM_HALTREQ_BMSK                          0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_CLEAR_BUSM_HALTREQ_SHFT                          0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_ADDR                              (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x0000722c)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_OFFS                              (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x0000722c)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_RMSK                                    0xff
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_AXIM2_CLAMP_E_CLEAR_BMSK                0x80
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_AXIM2_CLAMP_E_CLEAR_SHFT                 0x7
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_AXIM2_CLAMP_E_SET_BMSK                  0x40
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_AXIM2_CLAMP_E_SET_SHFT                   0x6
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_AXIM2_CLAMP_L_CLEAR_BMSK                0x20
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_AXIM2_CLAMP_L_CLEAR_SHFT                 0x5
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_AXIM2_CLAMP_L_SET_BMSK                  0x10
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_AXIM2_CLAMP_L_SET_SHFT                   0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_AXIM_CLAMP_E_CLEAR_BMSK                  0x8
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_AXIM_CLAMP_E_CLEAR_SHFT                  0x3
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_AXIM_CLAMP_E_SET_BMSK                    0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_AXIM_CLAMP_E_SET_SHFT                    0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_AXIM_CLAMP_L_CLEAR_BMSK                  0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_AXIM_CLAMP_L_CLEAR_SHFT                  0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_AXIM_CLAMP_L_SET_BMSK                    0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_AXIM_CLAMP_L_SET_SHFT                    0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_CLEAR_ADDR                                (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00007230)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_CLEAR_OFFS                                (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00007230)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_CLEAR_RMSK                                       0x7
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_CLEAR_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_CLEAR_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_CLEAR_AXIM2_BMSK                                 0x4
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_CLEAR_AXIM2_SHFT                                 0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_CLEAR_AXIM_BMSK                                  0x2
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_CLEAR_AXIM_SHFT                                  0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_CLEAR_CORE_BMSK                                  0x1
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_CLEAR_CORE_SHFT                                  0x0

#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_L1S_CLEAR_ADDR                                    (SSC_QDSP6V60SS_CSR_REG_BASE      + 0x00007240)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_L1S_CLEAR_OFFS                                    (SSC_QDSP6V60SS_CSR_REG_BASE_OFFS + 0x00007240)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_L1S_CLEAR_RMSK                                          0xff
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_L1S_CLEAR_OUT(v)      \
        out_dword(HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_L1S_CLEAR_ADDR,v)
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_L1S_CLEAR_L1S_BMSK                                      0xff
#define HWIO_SSC_QDSP6SS_SPMCTL_EN_MEM_L1S_CLEAR_L1S_SHFT                                       0x0

/*----------------------------------------------------------------------------
 * MODULE: SSC_MCC_REGS
 *--------------------------------------------------------------------------*/

#define SSC_MCC_REGS_REG_BASE                                                      (SSC_BASE      + 0x00600000)
#define SSC_MCC_REGS_REG_BASE_OFFS                                                 0x00600000

#define HWIO_SSC_SSCAON_SPARE_ADDR                                                 (SSC_MCC_REGS_REG_BASE      + 0x00000000)
#define HWIO_SSC_SSCAON_SPARE_OFFS                                                 (SSC_MCC_REGS_REG_BASE_OFFS + 0x00000000)
#define HWIO_SSC_SSCAON_SPARE_RMSK                                                 0xffffffff
#define HWIO_SSC_SSCAON_SPARE_IN          \
        in_dword_masked(HWIO_SSC_SSCAON_SPARE_ADDR, HWIO_SSC_SSCAON_SPARE_RMSK)
#define HWIO_SSC_SSCAON_SPARE_INM(m)      \
        in_dword_masked(HWIO_SSC_SSCAON_SPARE_ADDR, m)
#define HWIO_SSC_SSCAON_SPARE_OUT(v)      \
        out_dword(HWIO_SSC_SSCAON_SPARE_ADDR,v)
#define HWIO_SSC_SSCAON_SPARE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSCAON_SPARE_ADDR,m,v,HWIO_SSC_SSCAON_SPARE_IN)
#define HWIO_SSC_SSCAON_SPARE_SSCAON_SSC_SPARE_IN_BMSK                             0xffff0000
#define HWIO_SSC_SSCAON_SPARE_SSCAON_SSC_SPARE_IN_SHFT                                   0x10
#define HWIO_SSC_SSCAON_SPARE_SSCAON_SSC_SPARE_OUT_BMSK                                0xffff
#define HWIO_SSC_SSCAON_SPARE_SSCAON_SSC_SPARE_OUT_SHFT                                   0x0

#define HWIO_SSC_SSCAON_COUNTER_CFG_ADDR                                           (SSC_MCC_REGS_REG_BASE      + 0x00000004)
#define HWIO_SSC_SSCAON_COUNTER_CFG_OFFS                                           (SSC_MCC_REGS_REG_BASE_OFFS + 0x00000004)
#define HWIO_SSC_SSCAON_COUNTER_CFG_RMSK                                                  0x1
#define HWIO_SSC_SSCAON_COUNTER_CFG_IN          \
        in_dword_masked(HWIO_SSC_SSCAON_COUNTER_CFG_ADDR, HWIO_SSC_SSCAON_COUNTER_CFG_RMSK)
#define HWIO_SSC_SSCAON_COUNTER_CFG_INM(m)      \
        in_dword_masked(HWIO_SSC_SSCAON_COUNTER_CFG_ADDR, m)
#define HWIO_SSC_SSCAON_COUNTER_CFG_OUT(v)      \
        out_dword(HWIO_SSC_SSCAON_COUNTER_CFG_ADDR,v)
#define HWIO_SSC_SSCAON_COUNTER_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSCAON_COUNTER_CFG_ADDR,m,v,HWIO_SSC_SSCAON_COUNTER_CFG_IN)
#define HWIO_SSC_SSCAON_COUNTER_CFG_SSC_SSCAON_QCNTR_EN_BMSK                              0x1
#define HWIO_SSC_SSCAON_COUNTER_CFG_SSC_SSCAON_QCNTR_EN_SHFT                              0x0

#define HWIO_SSC_SSCAON_COUNTER_CTL_STAT_ADDR                                      (SSC_MCC_REGS_REG_BASE      + 0x00000008)
#define HWIO_SSC_SSCAON_COUNTER_CTL_STAT_OFFS                                      (SSC_MCC_REGS_REG_BASE_OFFS + 0x00000008)
#define HWIO_SSC_SSCAON_COUNTER_CTL_STAT_RMSK                                         0x18003
#define HWIO_SSC_SSCAON_COUNTER_CTL_STAT_IN          \
        in_dword_masked(HWIO_SSC_SSCAON_COUNTER_CTL_STAT_ADDR, HWIO_SSC_SSCAON_COUNTER_CTL_STAT_RMSK)
#define HWIO_SSC_SSCAON_COUNTER_CTL_STAT_INM(m)      \
        in_dword_masked(HWIO_SSC_SSCAON_COUNTER_CTL_STAT_ADDR, m)
#define HWIO_SSC_SSCAON_COUNTER_CTL_STAT_OUT(v)      \
        out_dword(HWIO_SSC_SSCAON_COUNTER_CTL_STAT_ADDR,v)
#define HWIO_SSC_SSCAON_COUNTER_CTL_STAT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSCAON_COUNTER_CTL_STAT_ADDR,m,v,HWIO_SSC_SSCAON_COUNTER_CTL_STAT_IN)
#define HWIO_SSC_SSCAON_COUNTER_CTL_STAT_SSCAON_SSC_QCNTR_LD_COMPL_BMSK               0x10000
#define HWIO_SSC_SSCAON_COUNTER_CTL_STAT_SSCAON_SSC_QCNTR_LD_COMPL_SHFT                  0x10
#define HWIO_SSC_SSCAON_COUNTER_CTL_STAT_SSCAON_SSC_QCNTR_SYNC_COMPL_BMSK              0x8000
#define HWIO_SSC_SSCAON_COUNTER_CTL_STAT_SSCAON_SSC_QCNTR_SYNC_COMPL_SHFT                 0xf
#define HWIO_SSC_SSCAON_COUNTER_CTL_STAT_SSC_SSCAON_QCNTR_SYNC_PULSE_BMSK                 0x2
#define HWIO_SSC_SSCAON_COUNTER_CTL_STAT_SSC_SSCAON_QCNTR_SYNC_PULSE_SHFT                 0x1
#define HWIO_SSC_SSCAON_COUNTER_CTL_STAT_SSC_SSCAON_QCNTR_PRE_LD_BMSK                     0x1
#define HWIO_SSC_SSCAON_COUNTER_CTL_STAT_SSC_SSCAON_QCNTR_PRE_LD_SHFT                     0x0

#define HWIO_SSC_SSCAON_COUNTER_OFF_ADDR                                           (SSC_MCC_REGS_REG_BASE      + 0x0000000c)
#define HWIO_SSC_SSCAON_COUNTER_OFF_OFFS                                           (SSC_MCC_REGS_REG_BASE_OFFS + 0x0000000c)
#define HWIO_SSC_SSCAON_COUNTER_OFF_RMSK                                               0xffff
#define HWIO_SSC_SSCAON_COUNTER_OFF_IN          \
        in_dword_masked(HWIO_SSC_SSCAON_COUNTER_OFF_ADDR, HWIO_SSC_SSCAON_COUNTER_OFF_RMSK)
#define HWIO_SSC_SSCAON_COUNTER_OFF_INM(m)      \
        in_dword_masked(HWIO_SSC_SSCAON_COUNTER_OFF_ADDR, m)
#define HWIO_SSC_SSCAON_COUNTER_OFF_OUT(v)      \
        out_dword(HWIO_SSC_SSCAON_COUNTER_OFF_ADDR,v)
#define HWIO_SSC_SSCAON_COUNTER_OFF_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSCAON_COUNTER_OFF_ADDR,m,v,HWIO_SSC_SSCAON_COUNTER_OFF_IN)
#define HWIO_SSC_SSCAON_COUNTER_OFF_SSC_SSCAON_QCNTR_OFFSET_BMSK                       0xffff
#define HWIO_SSC_SSCAON_COUNTER_OFF_SSC_SSCAON_QCNTR_OFFSET_SHFT                          0x0

#define HWIO_SSC_SSCAON_SLP_TMR_CTL_ADDR                                           (SSC_MCC_REGS_REG_BASE      + 0x00000010)
#define HWIO_SSC_SSCAON_SLP_TMR_CTL_OFFS                                           (SSC_MCC_REGS_REG_BASE_OFFS + 0x00000010)
#define HWIO_SSC_SSCAON_SLP_TMR_CTL_RMSK                                              0x18003
#define HWIO_SSC_SSCAON_SLP_TMR_CTL_IN          \
        in_dword_masked(HWIO_SSC_SSCAON_SLP_TMR_CTL_ADDR, HWIO_SSC_SSCAON_SLP_TMR_CTL_RMSK)
#define HWIO_SSC_SSCAON_SLP_TMR_CTL_INM(m)      \
        in_dword_masked(HWIO_SSC_SSCAON_SLP_TMR_CTL_ADDR, m)
#define HWIO_SSC_SSCAON_SLP_TMR_CTL_OUT(v)      \
        out_dword(HWIO_SSC_SSCAON_SLP_TMR_CTL_ADDR,v)
#define HWIO_SSC_SSCAON_SLP_TMR_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSCAON_SLP_TMR_CTL_ADDR,m,v,HWIO_SSC_SSCAON_SLP_TMR_CTL_IN)
#define HWIO_SSC_SSCAON_SLP_TMR_CTL_SSC_SSCAON_SW_SLP_TMR_INT_RAW_BMSK                0x10000
#define HWIO_SSC_SSCAON_SLP_TMR_CTL_SSC_SSCAON_SW_SLP_TMR_INT_RAW_SHFT                   0x10
#define HWIO_SSC_SSCAON_SLP_TMR_CTL_SSC_SSCAON_SW_SLP_TMR_INT_BMSK                     0x8000
#define HWIO_SSC_SSCAON_SLP_TMR_CTL_SSC_SSCAON_SW_SLP_TMR_INT_SHFT                        0xf
#define HWIO_SSC_SSCAON_SLP_TMR_CTL_SSC_SSCAON_SW_SLP_TMR_EXP_WR_BMSK                     0x2
#define HWIO_SSC_SSCAON_SLP_TMR_CTL_SSC_SSCAON_SW_SLP_TMR_EXP_WR_SHFT                     0x1
#define HWIO_SSC_SSCAON_SLP_TMR_CTL_SSC_SSCAON_SW_SLP_TMR_INT_CLR_BMSK                    0x1
#define HWIO_SSC_SSCAON_SLP_TMR_CTL_SSC_SSCAON_SW_SLP_TMR_INT_CLR_SHFT                    0x0

#define HWIO_SSC_SSCAON_SLP_TMR_EXP_LO_ADDR                                        (SSC_MCC_REGS_REG_BASE      + 0x00000014)
#define HWIO_SSC_SSCAON_SLP_TMR_EXP_LO_OFFS                                        (SSC_MCC_REGS_REG_BASE_OFFS + 0x00000014)
#define HWIO_SSC_SSCAON_SLP_TMR_EXP_LO_RMSK                                        0xffffffff
#define HWIO_SSC_SSCAON_SLP_TMR_EXP_LO_IN          \
        in_dword_masked(HWIO_SSC_SSCAON_SLP_TMR_EXP_LO_ADDR, HWIO_SSC_SSCAON_SLP_TMR_EXP_LO_RMSK)
#define HWIO_SSC_SSCAON_SLP_TMR_EXP_LO_INM(m)      \
        in_dword_masked(HWIO_SSC_SSCAON_SLP_TMR_EXP_LO_ADDR, m)
#define HWIO_SSC_SSCAON_SLP_TMR_EXP_LO_OUT(v)      \
        out_dword(HWIO_SSC_SSCAON_SLP_TMR_EXP_LO_ADDR,v)
#define HWIO_SSC_SSCAON_SLP_TMR_EXP_LO_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSCAON_SLP_TMR_EXP_LO_ADDR,m,v,HWIO_SSC_SSCAON_SLP_TMR_EXP_LO_IN)
#define HWIO_SSC_SSCAON_SLP_TMR_EXP_LO_SSC_SSCAON_SW_SLP_TMR_EXP_LO_BMSK           0xffffffff
#define HWIO_SSC_SSCAON_SLP_TMR_EXP_LO_SSC_SSCAON_SW_SLP_TMR_EXP_LO_SHFT                  0x0

#define HWIO_SSC_SSCAON_SLP_TMR_EXP_HI_ADDR                                        (SSC_MCC_REGS_REG_BASE      + 0x00000018)
#define HWIO_SSC_SSCAON_SLP_TMR_EXP_HI_OFFS                                        (SSC_MCC_REGS_REG_BASE_OFFS + 0x00000018)
#define HWIO_SSC_SSCAON_SLP_TMR_EXP_HI_RMSK                                          0xffffff
#define HWIO_SSC_SSCAON_SLP_TMR_EXP_HI_IN          \
        in_dword_masked(HWIO_SSC_SSCAON_SLP_TMR_EXP_HI_ADDR, HWIO_SSC_SSCAON_SLP_TMR_EXP_HI_RMSK)
#define HWIO_SSC_SSCAON_SLP_TMR_EXP_HI_INM(m)      \
        in_dword_masked(HWIO_SSC_SSCAON_SLP_TMR_EXP_HI_ADDR, m)
#define HWIO_SSC_SSCAON_SLP_TMR_EXP_HI_OUT(v)      \
        out_dword(HWIO_SSC_SSCAON_SLP_TMR_EXP_HI_ADDR,v)
#define HWIO_SSC_SSCAON_SLP_TMR_EXP_HI_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSCAON_SLP_TMR_EXP_HI_ADDR,m,v,HWIO_SSC_SSCAON_SLP_TMR_EXP_HI_IN)
#define HWIO_SSC_SSCAON_SLP_TMR_EXP_HI_SSC_SSCAON_SW_SLP_TMR_EXP_HI_BMSK             0xffffff
#define HWIO_SSC_SSCAON_SLP_TMR_EXP_HI_SSC_SSCAON_SW_SLP_TMR_EXP_HI_SHFT                  0x0

#define HWIO_SSC_SSCAON_SM_CSR0_ADDR                                               (SSC_MCC_REGS_REG_BASE      + 0x00000024)
#define HWIO_SSC_SSCAON_SM_CSR0_OFFS                                               (SSC_MCC_REGS_REG_BASE_OFFS + 0x00000024)
#define HWIO_SSC_SSCAON_SM_CSR0_RMSK                                               0xf0000c07
#define HWIO_SSC_SSCAON_SM_CSR0_IN          \
        in_dword_masked(HWIO_SSC_SSCAON_SM_CSR0_ADDR, HWIO_SSC_SSCAON_SM_CSR0_RMSK)
#define HWIO_SSC_SSCAON_SM_CSR0_INM(m)      \
        in_dword_masked(HWIO_SSC_SSCAON_SM_CSR0_ADDR, m)
#define HWIO_SSC_SSCAON_SM_CSR0_OUT(v)      \
        out_dword(HWIO_SSC_SSCAON_SM_CSR0_ADDR,v)
#define HWIO_SSC_SSCAON_SM_CSR0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSCAON_SM_CSR0_ADDR,m,v,HWIO_SSC_SSCAON_SM_CSR0_IN)
#define HWIO_SSC_SSCAON_SM_CSR0_SSCAON_SSC_PMU_AON_SM_BMSK                         0xf0000000
#define HWIO_SSC_SSCAON_SM_CSR0_SSCAON_SSC_PMU_AON_SM_SHFT                               0x1c
#define HWIO_SSC_SSCAON_SM_CSR0_SSC_SSCAON_PWRDN_REQ_BMSK                               0x800
#define HWIO_SSC_SSCAON_SM_CSR0_SSC_SSCAON_PWRDN_REQ_SHFT                                 0xb
#define HWIO_SSC_SSCAON_SM_CSR0_SSC_PEEL_MODE_OVRD_BMSK                                 0x400
#define HWIO_SSC_SSCAON_SM_CSR0_SSC_PEEL_MODE_OVRD_SHFT                                   0xa
#define HWIO_SSC_SSCAON_SM_CSR0_SSC_SSCAON_FAST_WAKEUP_EN_BMSK                            0x4
#define HWIO_SSC_SSCAON_SM_CSR0_SSC_SSCAON_FAST_WAKEUP_EN_SHFT                            0x2
#define HWIO_SSC_SSCAON_SM_CSR0_SSC_SSCAON_NO_RET_MSM_BMSK                                0x2
#define HWIO_SSC_SSCAON_SM_CSR0_SSC_SSCAON_NO_RET_MSM_SHFT                                0x1
#define HWIO_SSC_SSCAON_SM_CSR0_SSC_SSCAON_NO_RETENTION_BMSK                              0x1
#define HWIO_SSC_SSCAON_SM_CSR0_SSC_SSCAON_NO_RETENTION_SHFT                              0x0

#define HWIO_SSC_SSCAON_SM_CSR1_ADDR                                               (SSC_MCC_REGS_REG_BASE      + 0x00000028)
#define HWIO_SSC_SSCAON_SM_CSR1_OFFS                                               (SSC_MCC_REGS_REG_BASE_OFFS + 0x00000028)
#define HWIO_SSC_SSCAON_SM_CSR1_RMSK                                                    0x1ff
#define HWIO_SSC_SSCAON_SM_CSR1_IN          \
        in_dword_masked(HWIO_SSC_SSCAON_SM_CSR1_ADDR, HWIO_SSC_SSCAON_SM_CSR1_RMSK)
#define HWIO_SSC_SSCAON_SM_CSR1_INM(m)      \
        in_dword_masked(HWIO_SSC_SSCAON_SM_CSR1_ADDR, m)
#define HWIO_SSC_SSCAON_SM_CSR1_OUT(v)      \
        out_dword(HWIO_SSC_SSCAON_SM_CSR1_ADDR,v)
#define HWIO_SSC_SSCAON_SM_CSR1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSCAON_SM_CSR1_ADDR,m,v,HWIO_SSC_SSCAON_SM_CSR1_IN)
#define HWIO_SSC_SSCAON_SM_CSR1_SSC_SSCAON_PEEL_TMR_EN_BMSK                             0x100
#define HWIO_SSC_SSCAON_SM_CSR1_SSC_SSCAON_PEEL_TMR_EN_SHFT                               0x8
#define HWIO_SSC_SSCAON_SM_CSR1_SSC_SSCAON_PEEL_LOCKDLY_WR_BMSK                          0x80
#define HWIO_SSC_SSCAON_SM_CSR1_SSC_SSCAON_PEEL_LOCKDLY_WR_SHFT                           0x7
#define HWIO_SSC_SSCAON_SM_CSR1_SSC_SSCAON_PEEL_LOCKDLY_BMSK                             0x7f
#define HWIO_SSC_SSCAON_SM_CSR1_SSC_SSCAON_PEEL_LOCKDLY_SHFT                              0x0

#define HWIO_SSC_SSCAON_SWITCHER_DLY_ADDR                                          (SSC_MCC_REGS_REG_BASE      + 0x0000002c)
#define HWIO_SSC_SSCAON_SWITCHER_DLY_OFFS                                          (SSC_MCC_REGS_REG_BASE_OFFS + 0x0000002c)
#define HWIO_SSC_SSCAON_SWITCHER_DLY_RMSK                                          0xffffffff
#define HWIO_SSC_SSCAON_SWITCHER_DLY_IN          \
        in_dword_masked(HWIO_SSC_SSCAON_SWITCHER_DLY_ADDR, HWIO_SSC_SSCAON_SWITCHER_DLY_RMSK)
#define HWIO_SSC_SSCAON_SWITCHER_DLY_INM(m)      \
        in_dword_masked(HWIO_SSC_SSCAON_SWITCHER_DLY_ADDR, m)
#define HWIO_SSC_SSCAON_SWITCHER_DLY_OUT(v)      \
        out_dword(HWIO_SSC_SSCAON_SWITCHER_DLY_ADDR,v)
#define HWIO_SSC_SSCAON_SWITCHER_DLY_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSCAON_SWITCHER_DLY_ADDR,m,v,HWIO_SSC_SSCAON_SWITCHER_DLY_IN)
#define HWIO_SSC_SSCAON_SWITCHER_DLY_SSC_SSCAON_SWITCHER_DLY_WR_BMSK               0x80000000
#define HWIO_SSC_SSCAON_SWITCHER_DLY_SSC_SSCAON_SWITCHER_DLY_WR_SHFT                     0x1f
#define HWIO_SSC_SSCAON_SWITCHER_DLY_SSC_SSCAON_PBS_WAIT_DLY_BMSK                  0x7fff0000
#define HWIO_SSC_SSCAON_SWITCHER_DLY_SSC_SSCAON_PBS_WAIT_DLY_SHFT                        0x10
#define HWIO_SSC_SSCAON_SWITCHER_DLY_SSC_SSCAON_SWITCHER_DLY_BMSK                      0xffff
#define HWIO_SSC_SSCAON_SWITCHER_DLY_SSC_SSCAON_SWITCHER_DLY_SHFT                         0x0

#define HWIO_SSC_SSCAON_INT_ISO_ADDR                                               (SSC_MCC_REGS_REG_BASE      + 0x00000030)
#define HWIO_SSC_SSCAON_INT_ISO_OFFS                                               (SSC_MCC_REGS_REG_BASE_OFFS + 0x00000030)
#define HWIO_SSC_SSCAON_INT_ISO_RMSK                                                      0x1
#define HWIO_SSC_SSCAON_INT_ISO_OUT(v)      \
        out_dword(HWIO_SSC_SSCAON_INT_ISO_ADDR,v)
#define HWIO_SSC_SSCAON_INT_ISO_SSC_SSCAON_INT_ISO_REQ_BMSK                               0x1
#define HWIO_SSC_SSCAON_INT_ISO_SSC_SSCAON_INT_ISO_REQ_SHFT                               0x0

#define HWIO_SSC_SSCAON_INT_CLR0_ADDR                                              (SSC_MCC_REGS_REG_BASE      + 0x00000034)
#define HWIO_SSC_SSCAON_INT_CLR0_OFFS                                              (SSC_MCC_REGS_REG_BASE_OFFS + 0x00000034)
#define HWIO_SSC_SSCAON_INT_CLR0_RMSK                                              0xffffffff
#define HWIO_SSC_SSCAON_INT_CLR0_OUT(v)      \
        out_dword(HWIO_SSC_SSCAON_INT_CLR0_ADDR,v)
#define HWIO_SSC_SSCAON_INT_CLR0_SSC_SSCAON_INT_CLR0_BMSK                          0xffffffff
#define HWIO_SSC_SSCAON_INT_CLR0_SSC_SSCAON_INT_CLR0_SHFT                                 0x0

#define HWIO_SSC_SSCAON_INT_CLR1_ADDR                                              (SSC_MCC_REGS_REG_BASE      + 0x00000038)
#define HWIO_SSC_SSCAON_INT_CLR1_OFFS                                              (SSC_MCC_REGS_REG_BASE_OFFS + 0x00000038)
#define HWIO_SSC_SSCAON_INT_CLR1_RMSK                                              0xffffffff
#define HWIO_SSC_SSCAON_INT_CLR1_OUT(v)      \
        out_dword(HWIO_SSC_SSCAON_INT_CLR1_ADDR,v)
#define HWIO_SSC_SSCAON_INT_CLR1_SSC_SSCAON_INT_CLR1_BMSK                          0xffffffff
#define HWIO_SSC_SSCAON_INT_CLR1_SSC_SSCAON_INT_CLR1_SHFT                                 0x0

#define HWIO_SSC_SSCAON_INT_CLR2_ADDR                                              (SSC_MCC_REGS_REG_BASE      + 0x0000003c)
#define HWIO_SSC_SSCAON_INT_CLR2_OFFS                                              (SSC_MCC_REGS_REG_BASE_OFFS + 0x0000003c)
#define HWIO_SSC_SSCAON_INT_CLR2_RMSK                                              0xffffffff
#define HWIO_SSC_SSCAON_INT_CLR2_OUT(v)      \
        out_dword(HWIO_SSC_SSCAON_INT_CLR2_ADDR,v)
#define HWIO_SSC_SSCAON_INT_CLR2_SSC_SSCAON_INT_CLR2_BMSK                          0xffffffff
#define HWIO_SSC_SSCAON_INT_CLR2_SSC_SSCAON_INT_CLR2_SHFT                                 0x0

#define HWIO_SSC_SSCAON_INT_POL0_ADDR                                              (SSC_MCC_REGS_REG_BASE      + 0x00000040)
#define HWIO_SSC_SSCAON_INT_POL0_OFFS                                              (SSC_MCC_REGS_REG_BASE_OFFS + 0x00000040)
#define HWIO_SSC_SSCAON_INT_POL0_RMSK                                              0xffffffff
#define HWIO_SSC_SSCAON_INT_POL0_IN          \
        in_dword_masked(HWIO_SSC_SSCAON_INT_POL0_ADDR, HWIO_SSC_SSCAON_INT_POL0_RMSK)
#define HWIO_SSC_SSCAON_INT_POL0_INM(m)      \
        in_dword_masked(HWIO_SSC_SSCAON_INT_POL0_ADDR, m)
#define HWIO_SSC_SSCAON_INT_POL0_OUT(v)      \
        out_dword(HWIO_SSC_SSCAON_INT_POL0_ADDR,v)
#define HWIO_SSC_SSCAON_INT_POL0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSCAON_INT_POL0_ADDR,m,v,HWIO_SSC_SSCAON_INT_POL0_IN)
#define HWIO_SSC_SSCAON_INT_POL0_SSC_SSCAON_INT_POL0_BMSK                          0xffffffff
#define HWIO_SSC_SSCAON_INT_POL0_SSC_SSCAON_INT_POL0_SHFT                                 0x0

#define HWIO_SSC_SSCAON_INT_POL1_ADDR                                              (SSC_MCC_REGS_REG_BASE      + 0x00000044)
#define HWIO_SSC_SSCAON_INT_POL1_OFFS                                              (SSC_MCC_REGS_REG_BASE_OFFS + 0x00000044)
#define HWIO_SSC_SSCAON_INT_POL1_RMSK                                              0xffffffff
#define HWIO_SSC_SSCAON_INT_POL1_IN          \
        in_dword_masked(HWIO_SSC_SSCAON_INT_POL1_ADDR, HWIO_SSC_SSCAON_INT_POL1_RMSK)
#define HWIO_SSC_SSCAON_INT_POL1_INM(m)      \
        in_dword_masked(HWIO_SSC_SSCAON_INT_POL1_ADDR, m)
#define HWIO_SSC_SSCAON_INT_POL1_OUT(v)      \
        out_dword(HWIO_SSC_SSCAON_INT_POL1_ADDR,v)
#define HWIO_SSC_SSCAON_INT_POL1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSCAON_INT_POL1_ADDR,m,v,HWIO_SSC_SSCAON_INT_POL1_IN)
#define HWIO_SSC_SSCAON_INT_POL1_SSC_SSCAON_INT_POL1_BMSK                          0xffffffff
#define HWIO_SSC_SSCAON_INT_POL1_SSC_SSCAON_INT_POL1_SHFT                                 0x0

#define HWIO_SSC_SSCAON_INT_POL2_ADDR                                              (SSC_MCC_REGS_REG_BASE      + 0x00000048)
#define HWIO_SSC_SSCAON_INT_POL2_OFFS                                              (SSC_MCC_REGS_REG_BASE_OFFS + 0x00000048)
#define HWIO_SSC_SSCAON_INT_POL2_RMSK                                              0xffffffff
#define HWIO_SSC_SSCAON_INT_POL2_IN          \
        in_dword_masked(HWIO_SSC_SSCAON_INT_POL2_ADDR, HWIO_SSC_SSCAON_INT_POL2_RMSK)
#define HWIO_SSC_SSCAON_INT_POL2_INM(m)      \
        in_dword_masked(HWIO_SSC_SSCAON_INT_POL2_ADDR, m)
#define HWIO_SSC_SSCAON_INT_POL2_OUT(v)      \
        out_dword(HWIO_SSC_SSCAON_INT_POL2_ADDR,v)
#define HWIO_SSC_SSCAON_INT_POL2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSCAON_INT_POL2_ADDR,m,v,HWIO_SSC_SSCAON_INT_POL2_IN)
#define HWIO_SSC_SSCAON_INT_POL2_SSC_SSCAON_INT_POL2_BMSK                          0xffffffff
#define HWIO_SSC_SSCAON_INT_POL2_SSC_SSCAON_INT_POL2_SHFT                                 0x0

#define HWIO_SSC_SSCAON_INT_POS_EDGE_EN0_ADDR                                      (SSC_MCC_REGS_REG_BASE      + 0x0000004c)
#define HWIO_SSC_SSCAON_INT_POS_EDGE_EN0_OFFS                                      (SSC_MCC_REGS_REG_BASE_OFFS + 0x0000004c)
#define HWIO_SSC_SSCAON_INT_POS_EDGE_EN0_RMSK                                      0xffffffff
#define HWIO_SSC_SSCAON_INT_POS_EDGE_EN0_IN          \
        in_dword_masked(HWIO_SSC_SSCAON_INT_POS_EDGE_EN0_ADDR, HWIO_SSC_SSCAON_INT_POS_EDGE_EN0_RMSK)
#define HWIO_SSC_SSCAON_INT_POS_EDGE_EN0_INM(m)      \
        in_dword_masked(HWIO_SSC_SSCAON_INT_POS_EDGE_EN0_ADDR, m)
#define HWIO_SSC_SSCAON_INT_POS_EDGE_EN0_OUT(v)      \
        out_dword(HWIO_SSC_SSCAON_INT_POS_EDGE_EN0_ADDR,v)
#define HWIO_SSC_SSCAON_INT_POS_EDGE_EN0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSCAON_INT_POS_EDGE_EN0_ADDR,m,v,HWIO_SSC_SSCAON_INT_POS_EDGE_EN0_IN)
#define HWIO_SSC_SSCAON_INT_POS_EDGE_EN0_SSC_SSCAON_INT_POS_EDGE_EN0_BMSK          0xffffffff
#define HWIO_SSC_SSCAON_INT_POS_EDGE_EN0_SSC_SSCAON_INT_POS_EDGE_EN0_SHFT                 0x0

#define HWIO_SSC_SSCAON_INT_POS_EDGE_EN1_ADDR                                      (SSC_MCC_REGS_REG_BASE      + 0x00000050)
#define HWIO_SSC_SSCAON_INT_POS_EDGE_EN1_OFFS                                      (SSC_MCC_REGS_REG_BASE_OFFS + 0x00000050)
#define HWIO_SSC_SSCAON_INT_POS_EDGE_EN1_RMSK                                      0xffffffff
#define HWIO_SSC_SSCAON_INT_POS_EDGE_EN1_IN          \
        in_dword_masked(HWIO_SSC_SSCAON_INT_POS_EDGE_EN1_ADDR, HWIO_SSC_SSCAON_INT_POS_EDGE_EN1_RMSK)
#define HWIO_SSC_SSCAON_INT_POS_EDGE_EN1_INM(m)      \
        in_dword_masked(HWIO_SSC_SSCAON_INT_POS_EDGE_EN1_ADDR, m)
#define HWIO_SSC_SSCAON_INT_POS_EDGE_EN1_OUT(v)      \
        out_dword(HWIO_SSC_SSCAON_INT_POS_EDGE_EN1_ADDR,v)
#define HWIO_SSC_SSCAON_INT_POS_EDGE_EN1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSCAON_INT_POS_EDGE_EN1_ADDR,m,v,HWIO_SSC_SSCAON_INT_POS_EDGE_EN1_IN)
#define HWIO_SSC_SSCAON_INT_POS_EDGE_EN1_SSC_SSCAON_INT_POS_EDGE_EN1_BMSK          0xffffffff
#define HWIO_SSC_SSCAON_INT_POS_EDGE_EN1_SSC_SSCAON_INT_POS_EDGE_EN1_SHFT                 0x0

#define HWIO_SSC_SSCAON_INT_POS_EDGE_EN2_ADDR                                      (SSC_MCC_REGS_REG_BASE      + 0x00000054)
#define HWIO_SSC_SSCAON_INT_POS_EDGE_EN2_OFFS                                      (SSC_MCC_REGS_REG_BASE_OFFS + 0x00000054)
#define HWIO_SSC_SSCAON_INT_POS_EDGE_EN2_RMSK                                      0xffffffff
#define HWIO_SSC_SSCAON_INT_POS_EDGE_EN2_IN          \
        in_dword_masked(HWIO_SSC_SSCAON_INT_POS_EDGE_EN2_ADDR, HWIO_SSC_SSCAON_INT_POS_EDGE_EN2_RMSK)
#define HWIO_SSC_SSCAON_INT_POS_EDGE_EN2_INM(m)      \
        in_dword_masked(HWIO_SSC_SSCAON_INT_POS_EDGE_EN2_ADDR, m)
#define HWIO_SSC_SSCAON_INT_POS_EDGE_EN2_OUT(v)      \
        out_dword(HWIO_SSC_SSCAON_INT_POS_EDGE_EN2_ADDR,v)
#define HWIO_SSC_SSCAON_INT_POS_EDGE_EN2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSCAON_INT_POS_EDGE_EN2_ADDR,m,v,HWIO_SSC_SSCAON_INT_POS_EDGE_EN2_IN)
#define HWIO_SSC_SSCAON_INT_POS_EDGE_EN2_SSC_SSCAON_INT_POS_EDGE_EN2_BMSK          0xffffffff
#define HWIO_SSC_SSCAON_INT_POS_EDGE_EN2_SSC_SSCAON_INT_POS_EDGE_EN2_SHFT                 0x0

#define HWIO_SSC_SSCAON_INT_NEG_EDGE_EN0_ADDR                                      (SSC_MCC_REGS_REG_BASE      + 0x00000058)
#define HWIO_SSC_SSCAON_INT_NEG_EDGE_EN0_OFFS                                      (SSC_MCC_REGS_REG_BASE_OFFS + 0x00000058)
#define HWIO_SSC_SSCAON_INT_NEG_EDGE_EN0_RMSK                                      0xffffffff
#define HWIO_SSC_SSCAON_INT_NEG_EDGE_EN0_IN          \
        in_dword_masked(HWIO_SSC_SSCAON_INT_NEG_EDGE_EN0_ADDR, HWIO_SSC_SSCAON_INT_NEG_EDGE_EN0_RMSK)
#define HWIO_SSC_SSCAON_INT_NEG_EDGE_EN0_INM(m)      \
        in_dword_masked(HWIO_SSC_SSCAON_INT_NEG_EDGE_EN0_ADDR, m)
#define HWIO_SSC_SSCAON_INT_NEG_EDGE_EN0_OUT(v)      \
        out_dword(HWIO_SSC_SSCAON_INT_NEG_EDGE_EN0_ADDR,v)
#define HWIO_SSC_SSCAON_INT_NEG_EDGE_EN0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSCAON_INT_NEG_EDGE_EN0_ADDR,m,v,HWIO_SSC_SSCAON_INT_NEG_EDGE_EN0_IN)
#define HWIO_SSC_SSCAON_INT_NEG_EDGE_EN0_SSC_SSCAON_INT_NEG_EDGE_EN0_BMSK          0xffffffff
#define HWIO_SSC_SSCAON_INT_NEG_EDGE_EN0_SSC_SSCAON_INT_NEG_EDGE_EN0_SHFT                 0x0

#define HWIO_SSC_SSCAON_INT_NEG_EDGE_EN1_ADDR                                      (SSC_MCC_REGS_REG_BASE      + 0x0000005c)
#define HWIO_SSC_SSCAON_INT_NEG_EDGE_EN1_OFFS                                      (SSC_MCC_REGS_REG_BASE_OFFS + 0x0000005c)
#define HWIO_SSC_SSCAON_INT_NEG_EDGE_EN1_RMSK                                      0xffffffff
#define HWIO_SSC_SSCAON_INT_NEG_EDGE_EN1_IN          \
        in_dword_masked(HWIO_SSC_SSCAON_INT_NEG_EDGE_EN1_ADDR, HWIO_SSC_SSCAON_INT_NEG_EDGE_EN1_RMSK)
#define HWIO_SSC_SSCAON_INT_NEG_EDGE_EN1_INM(m)      \
        in_dword_masked(HWIO_SSC_SSCAON_INT_NEG_EDGE_EN1_ADDR, m)
#define HWIO_SSC_SSCAON_INT_NEG_EDGE_EN1_OUT(v)      \
        out_dword(HWIO_SSC_SSCAON_INT_NEG_EDGE_EN1_ADDR,v)
#define HWIO_SSC_SSCAON_INT_NEG_EDGE_EN1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSCAON_INT_NEG_EDGE_EN1_ADDR,m,v,HWIO_SSC_SSCAON_INT_NEG_EDGE_EN1_IN)
#define HWIO_SSC_SSCAON_INT_NEG_EDGE_EN1_SSC_SSCAON_INT_NEG_EDGE_EN1_BMSK          0xffffffff
#define HWIO_SSC_SSCAON_INT_NEG_EDGE_EN1_SSC_SSCAON_INT_NEG_EDGE_EN1_SHFT                 0x0

#define HWIO_SSC_SSCAON_INT_NEG_EDGE_EN2_ADDR                                      (SSC_MCC_REGS_REG_BASE      + 0x00000060)
#define HWIO_SSC_SSCAON_INT_NEG_EDGE_EN2_OFFS                                      (SSC_MCC_REGS_REG_BASE_OFFS + 0x00000060)
#define HWIO_SSC_SSCAON_INT_NEG_EDGE_EN2_RMSK                                      0xffffffff
#define HWIO_SSC_SSCAON_INT_NEG_EDGE_EN2_IN          \
        in_dword_masked(HWIO_SSC_SSCAON_INT_NEG_EDGE_EN2_ADDR, HWIO_SSC_SSCAON_INT_NEG_EDGE_EN2_RMSK)
#define HWIO_SSC_SSCAON_INT_NEG_EDGE_EN2_INM(m)      \
        in_dword_masked(HWIO_SSC_SSCAON_INT_NEG_EDGE_EN2_ADDR, m)
#define HWIO_SSC_SSCAON_INT_NEG_EDGE_EN2_OUT(v)      \
        out_dword(HWIO_SSC_SSCAON_INT_NEG_EDGE_EN2_ADDR,v)
#define HWIO_SSC_SSCAON_INT_NEG_EDGE_EN2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSCAON_INT_NEG_EDGE_EN2_ADDR,m,v,HWIO_SSC_SSCAON_INT_NEG_EDGE_EN2_IN)
#define HWIO_SSC_SSCAON_INT_NEG_EDGE_EN2_SSC_SSCAON_INT_NEG_EDGE_EN2_BMSK          0xffffffff
#define HWIO_SSC_SSCAON_INT_NEG_EDGE_EN2_SSC_SSCAON_INT_NEG_EDGE_EN2_SHFT                 0x0

#define HWIO_SSC_SSCAON_INT_EN0_ADDR                                               (SSC_MCC_REGS_REG_BASE      + 0x00000064)
#define HWIO_SSC_SSCAON_INT_EN0_OFFS                                               (SSC_MCC_REGS_REG_BASE_OFFS + 0x00000064)
#define HWIO_SSC_SSCAON_INT_EN0_RMSK                                               0xffffffff
#define HWIO_SSC_SSCAON_INT_EN0_IN          \
        in_dword_masked(HWIO_SSC_SSCAON_INT_EN0_ADDR, HWIO_SSC_SSCAON_INT_EN0_RMSK)
#define HWIO_SSC_SSCAON_INT_EN0_INM(m)      \
        in_dword_masked(HWIO_SSC_SSCAON_INT_EN0_ADDR, m)
#define HWIO_SSC_SSCAON_INT_EN0_OUT(v)      \
        out_dword(HWIO_SSC_SSCAON_INT_EN0_ADDR,v)
#define HWIO_SSC_SSCAON_INT_EN0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSCAON_INT_EN0_ADDR,m,v,HWIO_SSC_SSCAON_INT_EN0_IN)
#define HWIO_SSC_SSCAON_INT_EN0_SSC_SSCAON_INT_EN0_BMSK                            0xffffffff
#define HWIO_SSC_SSCAON_INT_EN0_SSC_SSCAON_INT_EN0_SHFT                                   0x0

#define HWIO_SSC_SSCAON_INT_EN1_ADDR                                               (SSC_MCC_REGS_REG_BASE      + 0x00000068)
#define HWIO_SSC_SSCAON_INT_EN1_OFFS                                               (SSC_MCC_REGS_REG_BASE_OFFS + 0x00000068)
#define HWIO_SSC_SSCAON_INT_EN1_RMSK                                               0xffffffff
#define HWIO_SSC_SSCAON_INT_EN1_IN          \
        in_dword_masked(HWIO_SSC_SSCAON_INT_EN1_ADDR, HWIO_SSC_SSCAON_INT_EN1_RMSK)
#define HWIO_SSC_SSCAON_INT_EN1_INM(m)      \
        in_dword_masked(HWIO_SSC_SSCAON_INT_EN1_ADDR, m)
#define HWIO_SSC_SSCAON_INT_EN1_OUT(v)      \
        out_dword(HWIO_SSC_SSCAON_INT_EN1_ADDR,v)
#define HWIO_SSC_SSCAON_INT_EN1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSCAON_INT_EN1_ADDR,m,v,HWIO_SSC_SSCAON_INT_EN1_IN)
#define HWIO_SSC_SSCAON_INT_EN1_SSC_SSCAON_INT_EN1_BMSK                            0xffffffff
#define HWIO_SSC_SSCAON_INT_EN1_SSC_SSCAON_INT_EN1_SHFT                                   0x0

#define HWIO_SSC_SSCAON_INT_EN2_ADDR                                               (SSC_MCC_REGS_REG_BASE      + 0x0000006c)
#define HWIO_SSC_SSCAON_INT_EN2_OFFS                                               (SSC_MCC_REGS_REG_BASE_OFFS + 0x0000006c)
#define HWIO_SSC_SSCAON_INT_EN2_RMSK                                               0xffffffff
#define HWIO_SSC_SSCAON_INT_EN2_IN          \
        in_dword_masked(HWIO_SSC_SSCAON_INT_EN2_ADDR, HWIO_SSC_SSCAON_INT_EN2_RMSK)
#define HWIO_SSC_SSCAON_INT_EN2_INM(m)      \
        in_dword_masked(HWIO_SSC_SSCAON_INT_EN2_ADDR, m)
#define HWIO_SSC_SSCAON_INT_EN2_OUT(v)      \
        out_dword(HWIO_SSC_SSCAON_INT_EN2_ADDR,v)
#define HWIO_SSC_SSCAON_INT_EN2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSCAON_INT_EN2_ADDR,m,v,HWIO_SSC_SSCAON_INT_EN2_IN)
#define HWIO_SSC_SSCAON_INT_EN2_SSC_SSCAON_INT_EN2_BMSK                            0xffffffff
#define HWIO_SSC_SSCAON_INT_EN2_SSC_SSCAON_INT_EN2_SHFT                                   0x0

#define HWIO_SSC_SSCAON_INT_STAT0_ADDR                                             (SSC_MCC_REGS_REG_BASE      + 0x00000070)
#define HWIO_SSC_SSCAON_INT_STAT0_OFFS                                             (SSC_MCC_REGS_REG_BASE_OFFS + 0x00000070)
#define HWIO_SSC_SSCAON_INT_STAT0_RMSK                                             0xffffffff
#define HWIO_SSC_SSCAON_INT_STAT0_IN          \
        in_dword_masked(HWIO_SSC_SSCAON_INT_STAT0_ADDR, HWIO_SSC_SSCAON_INT_STAT0_RMSK)
#define HWIO_SSC_SSCAON_INT_STAT0_INM(m)      \
        in_dword_masked(HWIO_SSC_SSCAON_INT_STAT0_ADDR, m)
#define HWIO_SSC_SSCAON_INT_STAT0_SSC_SSCAON_INT_STAT0_BMSK                        0xffffffff
#define HWIO_SSC_SSCAON_INT_STAT0_SSC_SSCAON_INT_STAT0_SHFT                               0x0

#define HWIO_SSC_SSCAON_INT_STAT1_ADDR                                             (SSC_MCC_REGS_REG_BASE      + 0x00000074)
#define HWIO_SSC_SSCAON_INT_STAT1_OFFS                                             (SSC_MCC_REGS_REG_BASE_OFFS + 0x00000074)
#define HWIO_SSC_SSCAON_INT_STAT1_RMSK                                             0xffffffff
#define HWIO_SSC_SSCAON_INT_STAT1_IN          \
        in_dword_masked(HWIO_SSC_SSCAON_INT_STAT1_ADDR, HWIO_SSC_SSCAON_INT_STAT1_RMSK)
#define HWIO_SSC_SSCAON_INT_STAT1_INM(m)      \
        in_dword_masked(HWIO_SSC_SSCAON_INT_STAT1_ADDR, m)
#define HWIO_SSC_SSCAON_INT_STAT1_SSC_SSCAON_INT_STAT1_BMSK                        0xffffffff
#define HWIO_SSC_SSCAON_INT_STAT1_SSC_SSCAON_INT_STAT1_SHFT                               0x0

#define HWIO_SSC_SSCAON_INT_STAT2_ADDR                                             (SSC_MCC_REGS_REG_BASE      + 0x00000078)
#define HWIO_SSC_SSCAON_INT_STAT2_OFFS                                             (SSC_MCC_REGS_REG_BASE_OFFS + 0x00000078)
#define HWIO_SSC_SSCAON_INT_STAT2_RMSK                                             0xffffffff
#define HWIO_SSC_SSCAON_INT_STAT2_IN          \
        in_dword_masked(HWIO_SSC_SSCAON_INT_STAT2_ADDR, HWIO_SSC_SSCAON_INT_STAT2_RMSK)
#define HWIO_SSC_SSCAON_INT_STAT2_INM(m)      \
        in_dword_masked(HWIO_SSC_SSCAON_INT_STAT2_ADDR, m)
#define HWIO_SSC_SSCAON_INT_STAT2_SSC_SSCAON_INT_STAT2_BMSK                        0xffffffff
#define HWIO_SSC_SSCAON_INT_STAT2_SSC_SSCAON_INT_STAT2_SHFT                               0x0

#define HWIO_SSC_SSCAON_INT_RAW_STAT0_ADDR                                         (SSC_MCC_REGS_REG_BASE      + 0x0000007c)
#define HWIO_SSC_SSCAON_INT_RAW_STAT0_OFFS                                         (SSC_MCC_REGS_REG_BASE_OFFS + 0x0000007c)
#define HWIO_SSC_SSCAON_INT_RAW_STAT0_RMSK                                         0xffffffff
#define HWIO_SSC_SSCAON_INT_RAW_STAT0_IN          \
        in_dword_masked(HWIO_SSC_SSCAON_INT_RAW_STAT0_ADDR, HWIO_SSC_SSCAON_INT_RAW_STAT0_RMSK)
#define HWIO_SSC_SSCAON_INT_RAW_STAT0_INM(m)      \
        in_dword_masked(HWIO_SSC_SSCAON_INT_RAW_STAT0_ADDR, m)
#define HWIO_SSC_SSCAON_INT_RAW_STAT0_SSC_SSCAON_INT_RAW_STAT0_BMSK                0xffffffff
#define HWIO_SSC_SSCAON_INT_RAW_STAT0_SSC_SSCAON_INT_RAW_STAT0_SHFT                       0x0

#define HWIO_SSC_SSCAON_INT_RAW_STAT1_ADDR                                         (SSC_MCC_REGS_REG_BASE      + 0x00000080)
#define HWIO_SSC_SSCAON_INT_RAW_STAT1_OFFS                                         (SSC_MCC_REGS_REG_BASE_OFFS + 0x00000080)
#define HWIO_SSC_SSCAON_INT_RAW_STAT1_RMSK                                         0xffffffff
#define HWIO_SSC_SSCAON_INT_RAW_STAT1_IN          \
        in_dword_masked(HWIO_SSC_SSCAON_INT_RAW_STAT1_ADDR, HWIO_SSC_SSCAON_INT_RAW_STAT1_RMSK)
#define HWIO_SSC_SSCAON_INT_RAW_STAT1_INM(m)      \
        in_dword_masked(HWIO_SSC_SSCAON_INT_RAW_STAT1_ADDR, m)
#define HWIO_SSC_SSCAON_INT_RAW_STAT1_SSC_SSCAON_INT_RAW_STAT1_BMSK                0xffffffff
#define HWIO_SSC_SSCAON_INT_RAW_STAT1_SSC_SSCAON_INT_RAW_STAT1_SHFT                       0x0

#define HWIO_SSC_SSCAON_INT_RAW_STAT2_ADDR                                         (SSC_MCC_REGS_REG_BASE      + 0x00000084)
#define HWIO_SSC_SSCAON_INT_RAW_STAT2_OFFS                                         (SSC_MCC_REGS_REG_BASE_OFFS + 0x00000084)
#define HWIO_SSC_SSCAON_INT_RAW_STAT2_RMSK                                         0xffffffff
#define HWIO_SSC_SSCAON_INT_RAW_STAT2_IN          \
        in_dword_masked(HWIO_SSC_SSCAON_INT_RAW_STAT2_ADDR, HWIO_SSC_SSCAON_INT_RAW_STAT2_RMSK)
#define HWIO_SSC_SSCAON_INT_RAW_STAT2_INM(m)      \
        in_dword_masked(HWIO_SSC_SSCAON_INT_RAW_STAT2_ADDR, m)
#define HWIO_SSC_SSCAON_INT_RAW_STAT2_SSC_SSCAON_INT_RAW_STAT2_BMSK                0xffffffff
#define HWIO_SSC_SSCAON_INT_RAW_STAT2_SSC_SSCAON_INT_RAW_STAT2_SHFT                       0x0

#define HWIO_SSC_SSCAON_INT_TO_TMR_IRQ_CLR_ADDR                                    (SSC_MCC_REGS_REG_BASE      + 0x00000088)
#define HWIO_SSC_SSCAON_INT_TO_TMR_IRQ_CLR_OFFS                                    (SSC_MCC_REGS_REG_BASE_OFFS + 0x00000088)
#define HWIO_SSC_SSCAON_INT_TO_TMR_IRQ_CLR_RMSK                                           0x1
#define HWIO_SSC_SSCAON_INT_TO_TMR_IRQ_CLR_OUT(v)      \
        out_dword(HWIO_SSC_SSCAON_INT_TO_TMR_IRQ_CLR_ADDR,v)
#define HWIO_SSC_SSCAON_INT_TO_TMR_IRQ_CLR_SSC_SSCAON_TO_TMR_IRQ_CLR_BMSK                 0x1
#define HWIO_SSC_SSCAON_INT_TO_TMR_IRQ_CLR_SSC_SSCAON_TO_TMR_IRQ_CLR_SHFT                 0x0

#define HWIO_SSC_SSC_TEST_BUS_SEL_CFG_ADDR                                         (SSC_MCC_REGS_REG_BASE      + 0x00001000)
#define HWIO_SSC_SSC_TEST_BUS_SEL_CFG_OFFS                                         (SSC_MCC_REGS_REG_BASE_OFFS + 0x00001000)
#define HWIO_SSC_SSC_TEST_BUS_SEL_CFG_RMSK                                                0x1
#define HWIO_SSC_SSC_TEST_BUS_SEL_CFG_IN          \
        in_dword_masked(HWIO_SSC_SSC_TEST_BUS_SEL_CFG_ADDR, HWIO_SSC_SSC_TEST_BUS_SEL_CFG_RMSK)
#define HWIO_SSC_SSC_TEST_BUS_SEL_CFG_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_TEST_BUS_SEL_CFG_ADDR, m)
#define HWIO_SSC_SSC_TEST_BUS_SEL_CFG_OUT(v)      \
        out_dword(HWIO_SSC_SSC_TEST_BUS_SEL_CFG_ADDR,v)
#define HWIO_SSC_SSC_TEST_BUS_SEL_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSC_TEST_BUS_SEL_CFG_ADDR,m,v,HWIO_SSC_SSC_TEST_BUS_SEL_CFG_IN)
#define HWIO_SSC_SSC_TEST_BUS_SEL_CFG_SSC_TEST_BUS_SEL_BMSK                               0x1
#define HWIO_SSC_SSC_TEST_BUS_SEL_CFG_SSC_TEST_BUS_SEL_SHFT                               0x0

#define HWIO_SSC_SSC_HW_VERSION_ADDR                                               (SSC_MCC_REGS_REG_BASE      + 0x00001004)
#define HWIO_SSC_SSC_HW_VERSION_OFFS                                               (SSC_MCC_REGS_REG_BASE_OFFS + 0x00001004)
#define HWIO_SSC_SSC_HW_VERSION_RMSK                                               0xffffffff
#define HWIO_SSC_SSC_HW_VERSION_IN          \
        in_dword_masked(HWIO_SSC_SSC_HW_VERSION_ADDR, HWIO_SSC_SSC_HW_VERSION_RMSK)
#define HWIO_SSC_SSC_HW_VERSION_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_HW_VERSION_ADDR, m)
#define HWIO_SSC_SSC_HW_VERSION_MAJOR_BMSK                                         0xf0000000
#define HWIO_SSC_SSC_HW_VERSION_MAJOR_SHFT                                               0x1c
#define HWIO_SSC_SSC_HW_VERSION_MINOR_BMSK                                          0xfff0000
#define HWIO_SSC_SSC_HW_VERSION_MINOR_SHFT                                               0x10
#define HWIO_SSC_SSC_HW_VERSION_STEP_BMSK                                              0xffff
#define HWIO_SSC_SSC_HW_VERSION_STEP_SHFT                                                 0x0

#define HWIO_SSC_SSC_XO_CLK_GATE_ADDR                                              (SSC_MCC_REGS_REG_BASE      + 0x00001008)
#define HWIO_SSC_SSC_XO_CLK_GATE_OFFS                                              (SSC_MCC_REGS_REG_BASE_OFFS + 0x00001008)
#define HWIO_SSC_SSC_XO_CLK_GATE_RMSK                                                     0x1
#define HWIO_SSC_SSC_XO_CLK_GATE_IN          \
        in_dword_masked(HWIO_SSC_SSC_XO_CLK_GATE_ADDR, HWIO_SSC_SSC_XO_CLK_GATE_RMSK)
#define HWIO_SSC_SSC_XO_CLK_GATE_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_XO_CLK_GATE_ADDR, m)
#define HWIO_SSC_SSC_XO_CLK_GATE_OUT(v)      \
        out_dword(HWIO_SSC_SSC_XO_CLK_GATE_ADDR,v)
#define HWIO_SSC_SSC_XO_CLK_GATE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSC_XO_CLK_GATE_ADDR,m,v,HWIO_SSC_SSC_XO_CLK_GATE_IN)
#define HWIO_SSC_SSC_XO_CLK_GATE_SSC_XO_CLK_GATE_EN_BMSK                                  0x1
#define HWIO_SSC_SSC_XO_CLK_GATE_SSC_XO_CLK_GATE_EN_SHFT                                  0x0

#define HWIO_SSC_SSC_I2C_CFG_ADDR                                                  (SSC_MCC_REGS_REG_BASE      + 0x0000100c)
#define HWIO_SSC_SSC_I2C_CFG_OFFS                                                  (SSC_MCC_REGS_REG_BASE_OFFS + 0x0000100c)
#define HWIO_SSC_SSC_I2C_CFG_RMSK                                                         0xf
#define HWIO_SSC_SSC_I2C_CFG_IN          \
        in_dword_masked(HWIO_SSC_SSC_I2C_CFG_ADDR, HWIO_SSC_SSC_I2C_CFG_RMSK)
#define HWIO_SSC_SSC_I2C_CFG_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_I2C_CFG_ADDR, m)
#define HWIO_SSC_SSC_I2C_CFG_OUT(v)      \
        out_dword(HWIO_SSC_SSC_I2C_CFG_ADDR,v)
#define HWIO_SSC_SSC_I2C_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSC_I2C_CFG_ADDR,m,v,HWIO_SSC_SSC_I2C_CFG_IN)
#define HWIO_SSC_SSC_I2C_CFG_MODE_1_BMSK                                                  0xc
#define HWIO_SSC_SSC_I2C_CFG_MODE_1_SHFT                                                  0x2
#define HWIO_SSC_SSC_I2C_CFG_MODE_0_BMSK                                                  0x3
#define HWIO_SSC_SSC_I2C_CFG_MODE_0_SHFT                                                  0x0

#define HWIO_SSC_SSC_SW_ISLAND_MODE_DISABLE_ADDR                                   (SSC_MCC_REGS_REG_BASE      + 0x00001010)
#define HWIO_SSC_SSC_SW_ISLAND_MODE_DISABLE_OFFS                                   (SSC_MCC_REGS_REG_BASE_OFFS + 0x00001010)
#define HWIO_SSC_SSC_SW_ISLAND_MODE_DISABLE_RMSK                                          0x1
#define HWIO_SSC_SSC_SW_ISLAND_MODE_DISABLE_IN          \
        in_dword_masked(HWIO_SSC_SSC_SW_ISLAND_MODE_DISABLE_ADDR, HWIO_SSC_SSC_SW_ISLAND_MODE_DISABLE_RMSK)
#define HWIO_SSC_SSC_SW_ISLAND_MODE_DISABLE_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_SW_ISLAND_MODE_DISABLE_ADDR, m)
#define HWIO_SSC_SSC_SW_ISLAND_MODE_DISABLE_DISABLE_BMSK                                  0x1
#define HWIO_SSC_SSC_SW_ISLAND_MODE_DISABLE_DISABLE_SHFT                                  0x0

#define HWIO_SSC_SSC_IEC_CTL_ADDR                                                  (SSC_MCC_REGS_REG_BASE      + 0x00002000)
#define HWIO_SSC_SSC_IEC_CTL_OFFS                                                  (SSC_MCC_REGS_REG_BASE_OFFS + 0x00002000)
#define HWIO_SSC_SSC_IEC_CTL_RMSK                                                        0x7f
#define HWIO_SSC_SSC_IEC_CTL_IN          \
        in_dword_masked(HWIO_SSC_SSC_IEC_CTL_ADDR, HWIO_SSC_SSC_IEC_CTL_RMSK)
#define HWIO_SSC_SSC_IEC_CTL_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_IEC_CTL_ADDR, m)
#define HWIO_SSC_SSC_IEC_CTL_OUT(v)      \
        out_dword(HWIO_SSC_SSC_IEC_CTL_ADDR,v)
#define HWIO_SSC_SSC_IEC_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSC_IEC_CTL_ADDR,m,v,HWIO_SSC_SSC_IEC_CTL_IN)
#define HWIO_SSC_SSC_IEC_CTL_BUS_ISO_ENTER_ISLAND_DIS_BMSK                               0x40
#define HWIO_SSC_SSC_IEC_CTL_BUS_ISO_ENTER_ISLAND_DIS_SHFT                                0x6
#define HWIO_SSC_SSC_IEC_CTL_L2_MISS_ISLAND_EXIT_EN_BMSK                                 0x20
#define HWIO_SSC_SSC_IEC_CTL_L2_MISS_ISLAND_EXIT_EN_SHFT                                  0x5
#define HWIO_SSC_SSC_IEC_CTL_ISO_AHB_MASTER_BYPASS_BMSK                                  0x10
#define HWIO_SSC_SSC_IEC_CTL_ISO_AHB_MASTER_BYPASS_SHFT                                   0x4
#define HWIO_SSC_SSC_IEC_CTL_ISO_AHB_SLAVE_BYPASS_BMSK                                    0x8
#define HWIO_SSC_SSC_IEC_CTL_ISO_AHB_SLAVE_BYPASS_SHFT                                    0x3
#define HWIO_SSC_SSC_IEC_CTL_AHB_REQPEND_CLR_BMSK                                         0x4
#define HWIO_SSC_SSC_IEC_CTL_AHB_REQPEND_CLR_SHFT                                         0x2
#define HWIO_SSC_SSC_IEC_CTL_ENTER_ISLAND_MODE_IRQ_CLR_BMSK                               0x2
#define HWIO_SSC_SSC_IEC_CTL_ENTER_ISLAND_MODE_IRQ_CLR_SHFT                               0x1
#define HWIO_SSC_SSC_IEC_CTL_EXIT_ISLAND_MODE_TRIG_BMSK                                   0x1
#define HWIO_SSC_SSC_IEC_CTL_EXIT_ISLAND_MODE_TRIG_SHFT                                   0x0

#define HWIO_SSC_SSC_IEC_STAT_ADDR                                                 (SSC_MCC_REGS_REG_BASE      + 0x00002004)
#define HWIO_SSC_SSC_IEC_STAT_OFFS                                                 (SSC_MCC_REGS_REG_BASE_OFFS + 0x00002004)
#define HWIO_SSC_SSC_IEC_STAT_RMSK                                                        0x1
#define HWIO_SSC_SSC_IEC_STAT_IN          \
        in_dword_masked(HWIO_SSC_SSC_IEC_STAT_ADDR, HWIO_SSC_SSC_IEC_STAT_RMSK)
#define HWIO_SSC_SSC_IEC_STAT_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_IEC_STAT_ADDR, m)
#define HWIO_SSC_SSC_IEC_STAT_ISLAND_MODE_BMSK                                            0x1
#define HWIO_SSC_SSC_IEC_STAT_ISLAND_MODE_SHFT                                            0x0

#define HWIO_SSC_SSC_IEC_BSY_WAIT_ADDR                                             (SSC_MCC_REGS_REG_BASE      + 0x00002008)
#define HWIO_SSC_SSC_IEC_BSY_WAIT_OFFS                                             (SSC_MCC_REGS_REG_BASE_OFFS + 0x00002008)
#define HWIO_SSC_SSC_IEC_BSY_WAIT_RMSK                                                    0x3
#define HWIO_SSC_SSC_IEC_BSY_WAIT_IN          \
        in_dword_masked(HWIO_SSC_SSC_IEC_BSY_WAIT_ADDR, HWIO_SSC_SSC_IEC_BSY_WAIT_RMSK)
#define HWIO_SSC_SSC_IEC_BSY_WAIT_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_IEC_BSY_WAIT_ADDR, m)
#define HWIO_SSC_SSC_IEC_BSY_WAIT_OUT(v)      \
        out_dword(HWIO_SSC_SSC_IEC_BSY_WAIT_ADDR,v)
#define HWIO_SSC_SSC_IEC_BSY_WAIT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSC_IEC_BSY_WAIT_ADDR,m,v,HWIO_SSC_SSC_IEC_BSY_WAIT_IN)
#define HWIO_SSC_SSC_IEC_BSY_WAIT_BUSY_WAIT_EN_BMSK                                       0x2
#define HWIO_SSC_SSC_IEC_BSY_WAIT_BUSY_WAIT_EN_SHFT                                       0x1
#define HWIO_SSC_SSC_IEC_BSY_WAIT_BUSY_WAIT_RST_BMSK                                      0x1
#define HWIO_SSC_SSC_IEC_BSY_WAIT_BUSY_WAIT_RST_SHFT                                      0x0

#define HWIO_SSC_SSC_IEC_SQCNTR_VAL0_ADDR                                          (SSC_MCC_REGS_REG_BASE      + 0x0000200c)
#define HWIO_SSC_SSC_IEC_SQCNTR_VAL0_OFFS                                          (SSC_MCC_REGS_REG_BASE_OFFS + 0x0000200c)
#define HWIO_SSC_SSC_IEC_SQCNTR_VAL0_RMSK                                          0xffffffff
#define HWIO_SSC_SSC_IEC_SQCNTR_VAL0_IN          \
        in_dword_masked(HWIO_SSC_SSC_IEC_SQCNTR_VAL0_ADDR, HWIO_SSC_SSC_IEC_SQCNTR_VAL0_RMSK)
#define HWIO_SSC_SSC_IEC_SQCNTR_VAL0_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_IEC_SQCNTR_VAL0_ADDR, m)
#define HWIO_SSC_SSC_IEC_SQCNTR_VAL0_SQCNTR_VAL0_BMSK                              0xffffffff
#define HWIO_SSC_SSC_IEC_SQCNTR_VAL0_SQCNTR_VAL0_SHFT                                     0x0

#define HWIO_SSC_SSC_IEC_SQCNTR_VAL1_ADDR                                          (SSC_MCC_REGS_REG_BASE      + 0x00002010)
#define HWIO_SSC_SSC_IEC_SQCNTR_VAL1_OFFS                                          (SSC_MCC_REGS_REG_BASE_OFFS + 0x00002010)
#define HWIO_SSC_SSC_IEC_SQCNTR_VAL1_RMSK                                            0xffffff
#define HWIO_SSC_SSC_IEC_SQCNTR_VAL1_IN          \
        in_dword_masked(HWIO_SSC_SSC_IEC_SQCNTR_VAL1_ADDR, HWIO_SSC_SSC_IEC_SQCNTR_VAL1_RMSK)
#define HWIO_SSC_SSC_IEC_SQCNTR_VAL1_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_IEC_SQCNTR_VAL1_ADDR, m)
#define HWIO_SSC_SSC_IEC_SQCNTR_VAL1_SQCNTR_VAL1_BMSK                                0xffffff
#define HWIO_SSC_SSC_IEC_SQCNTR_VAL1_SQCNTR_VAL1_SHFT                                     0x0

#define HWIO_SSC_SSC_IEC_BUSY_WAIT_CNTR_VAL0_ADDR                                  (SSC_MCC_REGS_REG_BASE      + 0x00002014)
#define HWIO_SSC_SSC_IEC_BUSY_WAIT_CNTR_VAL0_OFFS                                  (SSC_MCC_REGS_REG_BASE_OFFS + 0x00002014)
#define HWIO_SSC_SSC_IEC_BUSY_WAIT_CNTR_VAL0_RMSK                                  0xffffffff
#define HWIO_SSC_SSC_IEC_BUSY_WAIT_CNTR_VAL0_IN          \
        in_dword_masked(HWIO_SSC_SSC_IEC_BUSY_WAIT_CNTR_VAL0_ADDR, HWIO_SSC_SSC_IEC_BUSY_WAIT_CNTR_VAL0_RMSK)
#define HWIO_SSC_SSC_IEC_BUSY_WAIT_CNTR_VAL0_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_IEC_BUSY_WAIT_CNTR_VAL0_ADDR, m)
#define HWIO_SSC_SSC_IEC_BUSY_WAIT_CNTR_VAL0_BUSY_WAIT_CNTR_VAL0_BMSK              0xffffffff
#define HWIO_SSC_SSC_IEC_BUSY_WAIT_CNTR_VAL0_BUSY_WAIT_CNTR_VAL0_SHFT                     0x0

#define HWIO_SSC_SSC_IEC_BUSY_WAIT_CNTR_VAL1_ADDR                                  (SSC_MCC_REGS_REG_BASE      + 0x00002018)
#define HWIO_SSC_SSC_IEC_BUSY_WAIT_CNTR_VAL1_OFFS                                  (SSC_MCC_REGS_REG_BASE_OFFS + 0x00002018)
#define HWIO_SSC_SSC_IEC_BUSY_WAIT_CNTR_VAL1_RMSK                                    0xffffff
#define HWIO_SSC_SSC_IEC_BUSY_WAIT_CNTR_VAL1_IN          \
        in_dword_masked(HWIO_SSC_SSC_IEC_BUSY_WAIT_CNTR_VAL1_ADDR, HWIO_SSC_SSC_IEC_BUSY_WAIT_CNTR_VAL1_RMSK)
#define HWIO_SSC_SSC_IEC_BUSY_WAIT_CNTR_VAL1_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_IEC_BUSY_WAIT_CNTR_VAL1_ADDR, m)
#define HWIO_SSC_SSC_IEC_BUSY_WAIT_CNTR_VAL1_BUSY_WAIT_CNTR_VAL1_BMSK                0xffffff
#define HWIO_SSC_SSC_IEC_BUSY_WAIT_CNTR_VAL1_BUSY_WAIT_CNTR_VAL1_SHFT                     0x0

#define HWIO_SSC_SSC_IEC_HADDR_VAL0_ADDR                                           (SSC_MCC_REGS_REG_BASE      + 0x0000201c)
#define HWIO_SSC_SSC_IEC_HADDR_VAL0_OFFS                                           (SSC_MCC_REGS_REG_BASE_OFFS + 0x0000201c)
#define HWIO_SSC_SSC_IEC_HADDR_VAL0_RMSK                                           0xffffffff
#define HWIO_SSC_SSC_IEC_HADDR_VAL0_IN          \
        in_dword_masked(HWIO_SSC_SSC_IEC_HADDR_VAL0_ADDR, HWIO_SSC_SSC_IEC_HADDR_VAL0_RMSK)
#define HWIO_SSC_SSC_IEC_HADDR_VAL0_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_IEC_HADDR_VAL0_ADDR, m)
#define HWIO_SSC_SSC_IEC_HADDR_VAL0_HADDR_VAL0_BMSK                                0xffffffff
#define HWIO_SSC_SSC_IEC_HADDR_VAL0_HADDR_VAL0_SHFT                                       0x0

#define HWIO_SSC_SSC_IEC_HADDR_VAL1_ADDR                                           (SSC_MCC_REGS_REG_BASE      + 0x00002020)
#define HWIO_SSC_SSC_IEC_HADDR_VAL1_OFFS                                           (SSC_MCC_REGS_REG_BASE_OFFS + 0x00002020)
#define HWIO_SSC_SSC_IEC_HADDR_VAL1_RMSK                                                  0xf
#define HWIO_SSC_SSC_IEC_HADDR_VAL1_IN          \
        in_dword_masked(HWIO_SSC_SSC_IEC_HADDR_VAL1_ADDR, HWIO_SSC_SSC_IEC_HADDR_VAL1_RMSK)
#define HWIO_SSC_SSC_IEC_HADDR_VAL1_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_IEC_HADDR_VAL1_ADDR, m)
#define HWIO_SSC_SSC_IEC_HADDR_VAL1_HADDR_VAL1_BMSK                                       0xf
#define HWIO_SSC_SSC_IEC_HADDR_VAL1_HADDR_VAL1_SHFT                                       0x0

#define HWIO_SSC_SSC_IEC_HMID_VAL_ADDR                                             (SSC_MCC_REGS_REG_BASE      + 0x00002024)
#define HWIO_SSC_SSC_IEC_HMID_VAL_OFFS                                             (SSC_MCC_REGS_REG_BASE_OFFS + 0x00002024)
#define HWIO_SSC_SSC_IEC_HMID_VAL_RMSK                                                   0xff
#define HWIO_SSC_SSC_IEC_HMID_VAL_IN          \
        in_dword_masked(HWIO_SSC_SSC_IEC_HMID_VAL_ADDR, HWIO_SSC_SSC_IEC_HMID_VAL_RMSK)
#define HWIO_SSC_SSC_IEC_HMID_VAL_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_IEC_HMID_VAL_ADDR, m)
#define HWIO_SSC_SSC_IEC_HMID_VAL_SSC_IEC_HMID_VAL_BMSK                                  0xff
#define HWIO_SSC_SSC_IEC_HMID_VAL_SSC_IEC_HMID_VAL_SHFT                                   0x0

#define HWIO_SSC_SSC_IEC_HWEVENTS_SEL0_ADDR                                        (SSC_MCC_REGS_REG_BASE      + 0x00002028)
#define HWIO_SSC_SSC_IEC_HWEVENTS_SEL0_OFFS                                        (SSC_MCC_REGS_REG_BASE_OFFS + 0x00002028)
#define HWIO_SSC_SSC_IEC_HWEVENTS_SEL0_RMSK                                        0xffffffff
#define HWIO_SSC_SSC_IEC_HWEVENTS_SEL0_IN          \
        in_dword_masked(HWIO_SSC_SSC_IEC_HWEVENTS_SEL0_ADDR, HWIO_SSC_SSC_IEC_HWEVENTS_SEL0_RMSK)
#define HWIO_SSC_SSC_IEC_HWEVENTS_SEL0_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_IEC_HWEVENTS_SEL0_ADDR, m)
#define HWIO_SSC_SSC_IEC_HWEVENTS_SEL0_OUT(v)      \
        out_dword(HWIO_SSC_SSC_IEC_HWEVENTS_SEL0_ADDR,v)
#define HWIO_SSC_SSC_IEC_HWEVENTS_SEL0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSC_IEC_HWEVENTS_SEL0_ADDR,m,v,HWIO_SSC_SSC_IEC_HWEVENTS_SEL0_IN)
#define HWIO_SSC_SSC_IEC_HWEVENTS_SEL0_SSC_HWEVENTS_SEL0_BMSK                      0xffffffff
#define HWIO_SSC_SSC_IEC_HWEVENTS_SEL0_SSC_HWEVENTS_SEL0_SHFT                             0x0

#define HWIO_SSC_SSC_IEC_HWEVENTS_SEL1_ADDR                                        (SSC_MCC_REGS_REG_BASE      + 0x0000202c)
#define HWIO_SSC_SSC_IEC_HWEVENTS_SEL1_OFFS                                        (SSC_MCC_REGS_REG_BASE_OFFS + 0x0000202c)
#define HWIO_SSC_SSC_IEC_HWEVENTS_SEL1_RMSK                                        0xffffffff
#define HWIO_SSC_SSC_IEC_HWEVENTS_SEL1_IN          \
        in_dword_masked(HWIO_SSC_SSC_IEC_HWEVENTS_SEL1_ADDR, HWIO_SSC_SSC_IEC_HWEVENTS_SEL1_RMSK)
#define HWIO_SSC_SSC_IEC_HWEVENTS_SEL1_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_IEC_HWEVENTS_SEL1_ADDR, m)
#define HWIO_SSC_SSC_IEC_HWEVENTS_SEL1_OUT(v)      \
        out_dword(HWIO_SSC_SSC_IEC_HWEVENTS_SEL1_ADDR,v)
#define HWIO_SSC_SSC_IEC_HWEVENTS_SEL1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSC_IEC_HWEVENTS_SEL1_ADDR,m,v,HWIO_SSC_SSC_IEC_HWEVENTS_SEL1_IN)
#define HWIO_SSC_SSC_IEC_HWEVENTS_SEL1_SSC_HWEVENTS_SEL1_BMSK                      0xffffffff
#define HWIO_SSC_SSC_IEC_HWEVENTS_SEL1_SSC_HWEVENTS_SEL1_SHFT                             0x0

#define HWIO_SSC_SSC_IEC_HWEVENTS_SEL2_ADDR                                        (SSC_MCC_REGS_REG_BASE      + 0x00002030)
#define HWIO_SSC_SSC_IEC_HWEVENTS_SEL2_OFFS                                        (SSC_MCC_REGS_REG_BASE_OFFS + 0x00002030)
#define HWIO_SSC_SSC_IEC_HWEVENTS_SEL2_RMSK                                        0xffffffff
#define HWIO_SSC_SSC_IEC_HWEVENTS_SEL2_IN          \
        in_dword_masked(HWIO_SSC_SSC_IEC_HWEVENTS_SEL2_ADDR, HWIO_SSC_SSC_IEC_HWEVENTS_SEL2_RMSK)
#define HWIO_SSC_SSC_IEC_HWEVENTS_SEL2_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_IEC_HWEVENTS_SEL2_ADDR, m)
#define HWIO_SSC_SSC_IEC_HWEVENTS_SEL2_OUT(v)      \
        out_dword(HWIO_SSC_SSC_IEC_HWEVENTS_SEL2_ADDR,v)
#define HWIO_SSC_SSC_IEC_HWEVENTS_SEL2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSC_IEC_HWEVENTS_SEL2_ADDR,m,v,HWIO_SSC_SSC_IEC_HWEVENTS_SEL2_IN)
#define HWIO_SSC_SSC_IEC_HWEVENTS_SEL2_SSC_HWEVENTS_SEL2_BMSK                      0xffffffff
#define HWIO_SSC_SSC_IEC_HWEVENTS_SEL2_SSC_HWEVENTS_SEL2_SHFT                             0x0

#define HWIO_SSC_SSC_IEC_HWEVENTS_SEL3_ADDR                                        (SSC_MCC_REGS_REG_BASE      + 0x00002034)
#define HWIO_SSC_SSC_IEC_HWEVENTS_SEL3_OFFS                                        (SSC_MCC_REGS_REG_BASE_OFFS + 0x00002034)
#define HWIO_SSC_SSC_IEC_HWEVENTS_SEL3_RMSK                                        0xffffffff
#define HWIO_SSC_SSC_IEC_HWEVENTS_SEL3_IN          \
        in_dword_masked(HWIO_SSC_SSC_IEC_HWEVENTS_SEL3_ADDR, HWIO_SSC_SSC_IEC_HWEVENTS_SEL3_RMSK)
#define HWIO_SSC_SSC_IEC_HWEVENTS_SEL3_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_IEC_HWEVENTS_SEL3_ADDR, m)
#define HWIO_SSC_SSC_IEC_HWEVENTS_SEL3_OUT(v)      \
        out_dword(HWIO_SSC_SSC_IEC_HWEVENTS_SEL3_ADDR,v)
#define HWIO_SSC_SSC_IEC_HWEVENTS_SEL3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSC_IEC_HWEVENTS_SEL3_ADDR,m,v,HWIO_SSC_SSC_IEC_HWEVENTS_SEL3_IN)
#define HWIO_SSC_SSC_IEC_HWEVENTS_SEL3_SSC_HWEVENTS_SEL3_BMSK                      0xffffffff
#define HWIO_SSC_SSC_IEC_HWEVENTS_SEL3_SSC_HWEVENTS_SEL3_SHFT                             0x0

#define HWIO_SSC_SSC_IEC_HWEVENTS_EN_ADDR                                          (SSC_MCC_REGS_REG_BASE      + 0x00002038)
#define HWIO_SSC_SSC_IEC_HWEVENTS_EN_OFFS                                          (SSC_MCC_REGS_REG_BASE_OFFS + 0x00002038)
#define HWIO_SSC_SSC_IEC_HWEVENTS_EN_RMSK                                          0xffffffff
#define HWIO_SSC_SSC_IEC_HWEVENTS_EN_IN          \
        in_dword_masked(HWIO_SSC_SSC_IEC_HWEVENTS_EN_ADDR, HWIO_SSC_SSC_IEC_HWEVENTS_EN_RMSK)
#define HWIO_SSC_SSC_IEC_HWEVENTS_EN_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_IEC_HWEVENTS_EN_ADDR, m)
#define HWIO_SSC_SSC_IEC_HWEVENTS_EN_OUT(v)      \
        out_dword(HWIO_SSC_SSC_IEC_HWEVENTS_EN_ADDR,v)
#define HWIO_SSC_SSC_IEC_HWEVENTS_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSC_IEC_HWEVENTS_EN_ADDR,m,v,HWIO_SSC_SSC_IEC_HWEVENTS_EN_IN)
#define HWIO_SSC_SSC_IEC_HWEVENTS_EN_HWEVENTS_EN_BMSK                              0xffffffff
#define HWIO_SSC_SSC_IEC_HWEVENTS_EN_HWEVENTS_EN_SHFT                                     0x0

#define HWIO_SSC_SSC_DATA_BUS_CONFIG_ADDR                                          (SSC_MCC_REGS_REG_BASE      + 0x00003000)
#define HWIO_SSC_SSC_DATA_BUS_CONFIG_OFFS                                          (SSC_MCC_REGS_REG_BASE_OFFS + 0x00003000)
#define HWIO_SSC_SSC_DATA_BUS_CONFIG_RMSK                                               0xfff
#define HWIO_SSC_SSC_DATA_BUS_CONFIG_IN          \
        in_dword_masked(HWIO_SSC_SSC_DATA_BUS_CONFIG_ADDR, HWIO_SSC_SSC_DATA_BUS_CONFIG_RMSK)
#define HWIO_SSC_SSC_DATA_BUS_CONFIG_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_DATA_BUS_CONFIG_ADDR, m)
#define HWIO_SSC_SSC_DATA_BUS_CONFIG_OUT(v)      \
        out_dword(HWIO_SSC_SSC_DATA_BUS_CONFIG_ADDR,v)
#define HWIO_SSC_SSC_DATA_BUS_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSC_DATA_BUS_CONFIG_ADDR,m,v,HWIO_SSC_SSC_DATA_BUS_CONFIG_IN)
#define HWIO_SSC_SSC_DATA_BUS_CONFIG_AHBE_GLOBAL_EN_BMSK                                0x800
#define HWIO_SSC_SSC_DATA_BUS_CONFIG_AHBE_GLOBAL_EN_SHFT                                  0xb
#define HWIO_SSC_SSC_DATA_BUS_CONFIG_AHBE_TIMEBASE_BMSK                                 0x400
#define HWIO_SSC_SSC_DATA_BUS_CONFIG_AHBE_TIMEBASE_SHFT                                   0xa
#define HWIO_SSC_SSC_DATA_BUS_CONFIG_LOCK_EN_ARRAY_BMSK                                 0x380
#define HWIO_SSC_SSC_DATA_BUS_CONFIG_LOCK_EN_ARRAY_SHFT                                   0x7
#define HWIO_SSC_SSC_DATA_BUS_CONFIG_PRIORITY_ARRAY_BMSK                                 0x7e
#define HWIO_SSC_SSC_DATA_BUS_CONFIG_PRIORITY_ARRAY_SHFT                                  0x1
#define HWIO_SSC_SSC_DATA_BUS_CONFIG_ARB_SCHEME_SEL_BMSK                                  0x1
#define HWIO_SSC_SSC_DATA_BUS_CONFIG_ARB_SCHEME_SEL_SHFT                                  0x0

#define HWIO_SSC_SSC_DATA_BUS_STATUS_ADDR                                          (SSC_MCC_REGS_REG_BASE      + 0x00003004)
#define HWIO_SSC_SSC_DATA_BUS_STATUS_OFFS                                          (SSC_MCC_REGS_REG_BASE_OFFS + 0x00003004)
#define HWIO_SSC_SSC_DATA_BUS_STATUS_RMSK                                                 0x7
#define HWIO_SSC_SSC_DATA_BUS_STATUS_IN          \
        in_dword_masked(HWIO_SSC_SSC_DATA_BUS_STATUS_ADDR, HWIO_SSC_SSC_DATA_BUS_STATUS_RMSK)
#define HWIO_SSC_SSC_DATA_BUS_STATUS_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_DATA_BUS_STATUS_ADDR, m)
#define HWIO_SSC_SSC_DATA_BUS_STATUS_AHBE_STATUS_BMSK                                     0x7
#define HWIO_SSC_SSC_DATA_BUS_STATUS_AHBE_STATUS_SHFT                                     0x0

#define HWIO_SSC_SSC_CFG_BUS_CONFIG_ADDR                                           (SSC_MCC_REGS_REG_BASE      + 0x00004000)
#define HWIO_SSC_SSC_CFG_BUS_CONFIG_OFFS                                           (SSC_MCC_REGS_REG_BASE_OFFS + 0x00004000)
#define HWIO_SSC_SSC_CFG_BUS_CONFIG_RMSK                                                0xfff
#define HWIO_SSC_SSC_CFG_BUS_CONFIG_IN          \
        in_dword_masked(HWIO_SSC_SSC_CFG_BUS_CONFIG_ADDR, HWIO_SSC_SSC_CFG_BUS_CONFIG_RMSK)
#define HWIO_SSC_SSC_CFG_BUS_CONFIG_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_CFG_BUS_CONFIG_ADDR, m)
#define HWIO_SSC_SSC_CFG_BUS_CONFIG_OUT(v)      \
        out_dword(HWIO_SSC_SSC_CFG_BUS_CONFIG_ADDR,v)
#define HWIO_SSC_SSC_CFG_BUS_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSC_CFG_BUS_CONFIG_ADDR,m,v,HWIO_SSC_SSC_CFG_BUS_CONFIG_IN)
#define HWIO_SSC_SSC_CFG_BUS_CONFIG_AHBE_GLOBAL_EN_BMSK                                 0x800
#define HWIO_SSC_SSC_CFG_BUS_CONFIG_AHBE_GLOBAL_EN_SHFT                                   0xb
#define HWIO_SSC_SSC_CFG_BUS_CONFIG_AHBE_TIMEBASE_BMSK                                  0x400
#define HWIO_SSC_SSC_CFG_BUS_CONFIG_AHBE_TIMEBASE_SHFT                                    0xa
#define HWIO_SSC_SSC_CFG_BUS_CONFIG_LOCK_EN_ARRAY_BMSK                                  0x380
#define HWIO_SSC_SSC_CFG_BUS_CONFIG_LOCK_EN_ARRAY_SHFT                                    0x7
#define HWIO_SSC_SSC_CFG_BUS_CONFIG_PRIORITY_ARRAY_BMSK                                  0x7e
#define HWIO_SSC_SSC_CFG_BUS_CONFIG_PRIORITY_ARRAY_SHFT                                   0x1
#define HWIO_SSC_SSC_CFG_BUS_CONFIG_ARB_SCHEME_SEL_BMSK                                   0x1
#define HWIO_SSC_SSC_CFG_BUS_CONFIG_ARB_SCHEME_SEL_SHFT                                   0x0

#define HWIO_SSC_SSC_CFG_BUS_STATUS_ADDR                                           (SSC_MCC_REGS_REG_BASE      + 0x00004004)
#define HWIO_SSC_SSC_CFG_BUS_STATUS_OFFS                                           (SSC_MCC_REGS_REG_BASE_OFFS + 0x00004004)
#define HWIO_SSC_SSC_CFG_BUS_STATUS_RMSK                                                  0x7
#define HWIO_SSC_SSC_CFG_BUS_STATUS_IN          \
        in_dword_masked(HWIO_SSC_SSC_CFG_BUS_STATUS_ADDR, HWIO_SSC_SSC_CFG_BUS_STATUS_RMSK)
#define HWIO_SSC_SSC_CFG_BUS_STATUS_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_CFG_BUS_STATUS_ADDR, m)
#define HWIO_SSC_SSC_CFG_BUS_STATUS_AHBE_STATUS_BMSK                                      0x7
#define HWIO_SSC_SSC_CFG_BUS_STATUS_AHBE_STATUS_SHFT                                      0x0

#define HWIO_SSC_SSC_TSGEN_PRELOAD_LO_ADDR                                         (SSC_MCC_REGS_REG_BASE      + 0x00005000)
#define HWIO_SSC_SSC_TSGEN_PRELOAD_LO_OFFS                                         (SSC_MCC_REGS_REG_BASE_OFFS + 0x00005000)
#define HWIO_SSC_SSC_TSGEN_PRELOAD_LO_RMSK                                         0xffffffff
#define HWIO_SSC_SSC_TSGEN_PRELOAD_LO_IN          \
        in_dword_masked(HWIO_SSC_SSC_TSGEN_PRELOAD_LO_ADDR, HWIO_SSC_SSC_TSGEN_PRELOAD_LO_RMSK)
#define HWIO_SSC_SSC_TSGEN_PRELOAD_LO_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_TSGEN_PRELOAD_LO_ADDR, m)
#define HWIO_SSC_SSC_TSGEN_PRELOAD_LO_OUT(v)      \
        out_dword(HWIO_SSC_SSC_TSGEN_PRELOAD_LO_ADDR,v)
#define HWIO_SSC_SSC_TSGEN_PRELOAD_LO_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSC_TSGEN_PRELOAD_LO_ADDR,m,v,HWIO_SSC_SSC_TSGEN_PRELOAD_LO_IN)
#define HWIO_SSC_SSC_TSGEN_PRELOAD_LO_TSGEN_PRELOAD_LO_BMSK                        0xffffffff
#define HWIO_SSC_SSC_TSGEN_PRELOAD_LO_TSGEN_PRELOAD_LO_SHFT                               0x0

#define HWIO_SSC_SSC_TSGEN_PRELOAD_HI_ADDR                                         (SSC_MCC_REGS_REG_BASE      + 0x00005004)
#define HWIO_SSC_SSC_TSGEN_PRELOAD_HI_OFFS                                         (SSC_MCC_REGS_REG_BASE_OFFS + 0x00005004)
#define HWIO_SSC_SSC_TSGEN_PRELOAD_HI_RMSK                                         0xffffffff
#define HWIO_SSC_SSC_TSGEN_PRELOAD_HI_IN          \
        in_dword_masked(HWIO_SSC_SSC_TSGEN_PRELOAD_HI_ADDR, HWIO_SSC_SSC_TSGEN_PRELOAD_HI_RMSK)
#define HWIO_SSC_SSC_TSGEN_PRELOAD_HI_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_TSGEN_PRELOAD_HI_ADDR, m)
#define HWIO_SSC_SSC_TSGEN_PRELOAD_HI_OUT(v)      \
        out_dword(HWIO_SSC_SSC_TSGEN_PRELOAD_HI_ADDR,v)
#define HWIO_SSC_SSC_TSGEN_PRELOAD_HI_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSC_TSGEN_PRELOAD_HI_ADDR,m,v,HWIO_SSC_SSC_TSGEN_PRELOAD_HI_IN)
#define HWIO_SSC_SSC_TSGEN_PRELOAD_HI_TSGEN_PRELOAD_HI_BMSK                        0xffffffff
#define HWIO_SSC_SSC_TSGEN_PRELOAD_HI_TSGEN_PRELOAD_HI_SHFT                               0x0

#define HWIO_SSC_SSC_TSGEN_CTR_LO_ADDR                                             (SSC_MCC_REGS_REG_BASE      + 0x00005008)
#define HWIO_SSC_SSC_TSGEN_CTR_LO_OFFS                                             (SSC_MCC_REGS_REG_BASE_OFFS + 0x00005008)
#define HWIO_SSC_SSC_TSGEN_CTR_LO_RMSK                                             0xffffffff
#define HWIO_SSC_SSC_TSGEN_CTR_LO_IN          \
        in_dword_masked(HWIO_SSC_SSC_TSGEN_CTR_LO_ADDR, HWIO_SSC_SSC_TSGEN_CTR_LO_RMSK)
#define HWIO_SSC_SSC_TSGEN_CTR_LO_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_TSGEN_CTR_LO_ADDR, m)
#define HWIO_SSC_SSC_TSGEN_CTR_LO_TSGEN_CTR_LO_BMSK                                0xffffffff
#define HWIO_SSC_SSC_TSGEN_CTR_LO_TSGEN_CTR_LO_SHFT                                       0x0

#define HWIO_SSC_SSC_TSGEN_CTR_HI_ADDR                                             (SSC_MCC_REGS_REG_BASE      + 0x0000500c)
#define HWIO_SSC_SSC_TSGEN_CTR_HI_OFFS                                             (SSC_MCC_REGS_REG_BASE_OFFS + 0x0000500c)
#define HWIO_SSC_SSC_TSGEN_CTR_HI_RMSK                                             0xffffffff
#define HWIO_SSC_SSC_TSGEN_CTR_HI_IN          \
        in_dword_masked(HWIO_SSC_SSC_TSGEN_CTR_HI_ADDR, HWIO_SSC_SSC_TSGEN_CTR_HI_RMSK)
#define HWIO_SSC_SSC_TSGEN_CTR_HI_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_TSGEN_CTR_HI_ADDR, m)
#define HWIO_SSC_SSC_TSGEN_CTR_HI_TSGEN_CTR_HI_BMSK                                0xffffffff
#define HWIO_SSC_SSC_TSGEN_CTR_HI_TSGEN_CTR_HI_SHFT                                       0x0

#define HWIO_SSC_SSC_TSGEN_CTL_ADDR                                                (SSC_MCC_REGS_REG_BASE      + 0x00005010)
#define HWIO_SSC_SSC_TSGEN_CTL_OFFS                                                (SSC_MCC_REGS_REG_BASE_OFFS + 0x00005010)
#define HWIO_SSC_SSC_TSGEN_CTL_RMSK                                                       0x3
#define HWIO_SSC_SSC_TSGEN_CTL_IN          \
        in_dword_masked(HWIO_SSC_SSC_TSGEN_CTL_ADDR, HWIO_SSC_SSC_TSGEN_CTL_RMSK)
#define HWIO_SSC_SSC_TSGEN_CTL_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_TSGEN_CTL_ADDR, m)
#define HWIO_SSC_SSC_TSGEN_CTL_OUT(v)      \
        out_dword(HWIO_SSC_SSC_TSGEN_CTL_ADDR,v)
#define HWIO_SSC_SSC_TSGEN_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSC_TSGEN_CTL_ADDR,m,v,HWIO_SSC_SSC_TSGEN_CTL_IN)
#define HWIO_SSC_SSC_TSGEN_CTL_TSGEN_PRELOAD_EN_BMSK                                      0x2
#define HWIO_SSC_SSC_TSGEN_CTL_TSGEN_PRELOAD_EN_SHFT                                      0x1
#define HWIO_SSC_SSC_TSGEN_CTL_TSGEN_DISABLE_CNT_BMSK                                     0x1
#define HWIO_SSC_SSC_TSGEN_CTL_TSGEN_DISABLE_CNT_SHFT                                     0x0

#define HWIO_SSC_SSC_ATB_LOW_POWER_HANDSHAKE_ADDR                                  (SSC_MCC_REGS_REG_BASE      + 0x00005014)
#define HWIO_SSC_SSC_ATB_LOW_POWER_HANDSHAKE_OFFS                                  (SSC_MCC_REGS_REG_BASE_OFFS + 0x00005014)
#define HWIO_SSC_SSC_ATB_LOW_POWER_HANDSHAKE_RMSK                                         0x7
#define HWIO_SSC_SSC_ATB_LOW_POWER_HANDSHAKE_IN          \
        in_dword_masked(HWIO_SSC_SSC_ATB_LOW_POWER_HANDSHAKE_ADDR, HWIO_SSC_SSC_ATB_LOW_POWER_HANDSHAKE_RMSK)
#define HWIO_SSC_SSC_ATB_LOW_POWER_HANDSHAKE_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_ATB_LOW_POWER_HANDSHAKE_ADDR, m)
#define HWIO_SSC_SSC_ATB_LOW_POWER_HANDSHAKE_OUT(v)      \
        out_dword(HWIO_SSC_SSC_ATB_LOW_POWER_HANDSHAKE_ADDR,v)
#define HWIO_SSC_SSC_ATB_LOW_POWER_HANDSHAKE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSC_ATB_LOW_POWER_HANDSHAKE_ADDR,m,v,HWIO_SSC_SSC_ATB_LOW_POWER_HANDSHAKE_IN)
#define HWIO_SSC_SSC_ATB_LOW_POWER_HANDSHAKE_REQUEST_BMSK                                 0x4
#define HWIO_SSC_SSC_ATB_LOW_POWER_HANDSHAKE_REQUEST_SHFT                                 0x2
#define HWIO_SSC_SSC_ATB_LOW_POWER_HANDSHAKE_ACTIVE_BMSK                                  0x2
#define HWIO_SSC_SSC_ATB_LOW_POWER_HANDSHAKE_ACTIVE_SHFT                                  0x1
#define HWIO_SSC_SSC_ATB_LOW_POWER_HANDSHAKE_ACK_BMSK                                     0x1
#define HWIO_SSC_SSC_ATB_LOW_POWER_HANDSHAKE_ACK_SHFT                                     0x0

#define HWIO_SSC_SSC_APB_LOW_POWER_HANDSHAKE_ADDR                                  (SSC_MCC_REGS_REG_BASE      + 0x00005018)
#define HWIO_SSC_SSC_APB_LOW_POWER_HANDSHAKE_OFFS                                  (SSC_MCC_REGS_REG_BASE_OFFS + 0x00005018)
#define HWIO_SSC_SSC_APB_LOW_POWER_HANDSHAKE_RMSK                                         0x7
#define HWIO_SSC_SSC_APB_LOW_POWER_HANDSHAKE_IN          \
        in_dword_masked(HWIO_SSC_SSC_APB_LOW_POWER_HANDSHAKE_ADDR, HWIO_SSC_SSC_APB_LOW_POWER_HANDSHAKE_RMSK)
#define HWIO_SSC_SSC_APB_LOW_POWER_HANDSHAKE_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_APB_LOW_POWER_HANDSHAKE_ADDR, m)
#define HWIO_SSC_SSC_APB_LOW_POWER_HANDSHAKE_OUT(v)      \
        out_dword(HWIO_SSC_SSC_APB_LOW_POWER_HANDSHAKE_ADDR,v)
#define HWIO_SSC_SSC_APB_LOW_POWER_HANDSHAKE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSC_APB_LOW_POWER_HANDSHAKE_ADDR,m,v,HWIO_SSC_SSC_APB_LOW_POWER_HANDSHAKE_IN)
#define HWIO_SSC_SSC_APB_LOW_POWER_HANDSHAKE_REQUEST_BMSK                                 0x4
#define HWIO_SSC_SSC_APB_LOW_POWER_HANDSHAKE_REQUEST_SHFT                                 0x2
#define HWIO_SSC_SSC_APB_LOW_POWER_HANDSHAKE_ACTIVE_BMSK                                  0x2
#define HWIO_SSC_SSC_APB_LOW_POWER_HANDSHAKE_ACTIVE_SHFT                                  0x1
#define HWIO_SSC_SSC_APB_LOW_POWER_HANDSHAKE_ACK_BMSK                                     0x1
#define HWIO_SSC_SSC_APB_LOW_POWER_HANDSHAKE_ACK_SHFT                                     0x0

#define HWIO_SSC_SSC_HM_TESTBUS_SEL_ADDR                                           (SSC_MCC_REGS_REG_BASE      + 0x00006000)
#define HWIO_SSC_SSC_HM_TESTBUS_SEL_OFFS                                           (SSC_MCC_REGS_REG_BASE_OFFS + 0x00006000)
#define HWIO_SSC_SSC_HM_TESTBUS_SEL_RMSK                                               0xffff
#define HWIO_SSC_SSC_HM_TESTBUS_SEL_IN          \
        in_dword_masked(HWIO_SSC_SSC_HM_TESTBUS_SEL_ADDR, HWIO_SSC_SSC_HM_TESTBUS_SEL_RMSK)
#define HWIO_SSC_SSC_HM_TESTBUS_SEL_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_HM_TESTBUS_SEL_ADDR, m)
#define HWIO_SSC_SSC_HM_TESTBUS_SEL_OUT(v)      \
        out_dword(HWIO_SSC_SSC_HM_TESTBUS_SEL_ADDR,v)
#define HWIO_SSC_SSC_HM_TESTBUS_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSC_HM_TESTBUS_SEL_ADDR,m,v,HWIO_SSC_SSC_HM_TESTBUS_SEL_IN)
#define HWIO_SSC_SSC_HM_TESTBUS_SEL_I_TESTBUS_SEL_BMSK                                 0xffff
#define HWIO_SSC_SSC_HM_TESTBUS_SEL_I_TESTBUS_SEL_SHFT                                    0x0

#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_ADDR                            (SSC_MCC_REGS_REG_BASE      + 0x00007000)
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_OFFS                            (SSC_MCC_REGS_REG_BASE_OFFS + 0x00007000)
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_RMSK                            0xffffffff
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_IN          \
        in_dword_masked(HWIO_SSC_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_ADDR, HWIO_SSC_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_RMSK)
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_ADDR, m)
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_OUT(v)      \
        out_dword(HWIO_SSC_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_ADDR,v)
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_ADDR,m,v,HWIO_SSC_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_IN)
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_RFU_BMSK                        0xfffffffc
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_RFU_SHFT                               0x2
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_TIMESTAMPENABLE_BMSK                   0x2
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_TIMESTAMPENABLE_SHFT                   0x1
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_CAPTURE_BMSK                           0x1
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_CAPTURE_SHFT                           0x0

#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL0_ADDR                               (SSC_MCC_REGS_REG_BASE      + 0x00007004)
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL0_OFFS                               (SSC_MCC_REGS_REG_BASE_OFFS + 0x00007004)
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL0_RMSK                               0xffffffff
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL0_IN          \
        in_dword_masked(HWIO_SSC_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL0_ADDR, HWIO_SSC_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL0_RMSK)
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL0_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL0_ADDR, m)
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL0_TIMEVAL_BMSK                       0xffffffff
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL0_TIMEVAL_SHFT                              0x0

#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL1_ADDR                               (SSC_MCC_REGS_REG_BASE      + 0x00007008)
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL1_OFFS                               (SSC_MCC_REGS_REG_BASE_OFFS + 0x00007008)
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL1_RMSK                               0xffffffff
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL1_IN          \
        in_dword_masked(HWIO_SSC_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL1_ADDR, HWIO_SSC_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL1_RMSK)
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL1_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL1_ADDR, m)
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL1_TIMEVAL_BMSK                       0xffffffff
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_AOTIMEVAL1_TIMEVAL_SHFT                              0x0

#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_ADDR                             (SSC_MCC_REGS_REG_BASE      + 0x0000700c)
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_OFFS                             (SSC_MCC_REGS_REG_BASE_OFFS + 0x0000700c)
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_RMSK                             0xffffffff
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_IN          \
        in_dword_masked(HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_ADDR, HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_RMSK)
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_ADDR, m)
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_TIMEVAL_BMSK                     0xffffffff
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_TIMEVAL_SHFT                            0x0

#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_ADDR                             (SSC_MCC_REGS_REG_BASE      + 0x00007010)
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_OFFS                             (SSC_MCC_REGS_REG_BASE_OFFS + 0x00007010)
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_RMSK                             0xffffffff
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_IN          \
        in_dword_masked(HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_ADDR, HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_RMSK)
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_ADDR, m)
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_TIMEVAL_BMSK                     0xffffffff
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_TIMEVAL_SHFT                            0x0

#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_ADDR                            (SSC_MCC_REGS_REG_BASE      + 0x00007014)
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_OFFS                            (SSC_MCC_REGS_REG_BASE_OFFS + 0x00007014)
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_RMSK                            0xffffffff
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_IN          \
        in_dword_masked(HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_ADDR, HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_RMSK)
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_ADDR, m)
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_OUT(v)      \
        out_dword(HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_ADDR,v)
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_ADDR,m,v,HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_IN)
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_TIMELOAD_BMSK                   0xffffffff
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_TIMELOAD_SHFT                          0x0

#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_ADDR                            (SSC_MCC_REGS_REG_BASE      + 0x00007018)
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_OFFS                            (SSC_MCC_REGS_REG_BASE_OFFS + 0x00007018)
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_RMSK                            0xffffffff
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_IN          \
        in_dword_masked(HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_ADDR, HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_RMSK)
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_ADDR, m)
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_OUT(v)      \
        out_dword(HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_ADDR,v)
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_ADDR,m,v,HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_IN)
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_TIMELOAD_BMSK                   0xffffffff
#define HWIO_SSC_SSC_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_TIMELOAD_SHFT                          0x0

#define HWIO_SSC_SSC_WAKEUP_PRIMARY_IE_ADDR                                        (SSC_MCC_REGS_REG_BASE      + 0x00008000)
#define HWIO_SSC_SSC_WAKEUP_PRIMARY_IE_OFFS                                        (SSC_MCC_REGS_REG_BASE_OFFS + 0x00008000)
#define HWIO_SSC_SSC_WAKEUP_PRIMARY_IE_RMSK                                             0x1ff
#define HWIO_SSC_SSC_WAKEUP_PRIMARY_IE_IN          \
        in_dword_masked(HWIO_SSC_SSC_WAKEUP_PRIMARY_IE_ADDR, HWIO_SSC_SSC_WAKEUP_PRIMARY_IE_RMSK)
#define HWIO_SSC_SSC_WAKEUP_PRIMARY_IE_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_WAKEUP_PRIMARY_IE_ADDR, m)
#define HWIO_SSC_SSC_WAKEUP_PRIMARY_IE_OUT(v)      \
        out_dword(HWIO_SSC_SSC_WAKEUP_PRIMARY_IE_ADDR,v)
#define HWIO_SSC_SSC_WAKEUP_PRIMARY_IE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSC_WAKEUP_PRIMARY_IE_ADDR,m,v,HWIO_SSC_SSC_WAKEUP_PRIMARY_IE_IN)
#define HWIO_SSC_SSC_WAKEUP_PRIMARY_IE_WAKEUP_IE_BMSK                                   0x1ff
#define HWIO_SSC_SSC_WAKEUP_PRIMARY_IE_WAKEUP_IE_SHFT                                     0x0

#define HWIO_SSC_SSC_WAKEUP_SECONDARY_IE_ADDR                                      (SSC_MCC_REGS_REG_BASE      + 0x00009000)
#define HWIO_SSC_SSC_WAKEUP_SECONDARY_IE_OFFS                                      (SSC_MCC_REGS_REG_BASE_OFFS + 0x00009000)
#define HWIO_SSC_SSC_WAKEUP_SECONDARY_IE_RMSK                                           0x1ff
#define HWIO_SSC_SSC_WAKEUP_SECONDARY_IE_IN          \
        in_dword_masked(HWIO_SSC_SSC_WAKEUP_SECONDARY_IE_ADDR, HWIO_SSC_SSC_WAKEUP_SECONDARY_IE_RMSK)
#define HWIO_SSC_SSC_WAKEUP_SECONDARY_IE_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_WAKEUP_SECONDARY_IE_ADDR, m)
#define HWIO_SSC_SSC_WAKEUP_SECONDARY_IE_OUT(v)      \
        out_dword(HWIO_SSC_SSC_WAKEUP_SECONDARY_IE_ADDR,v)
#define HWIO_SSC_SSC_WAKEUP_SECONDARY_IE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSC_WAKEUP_SECONDARY_IE_ADDR,m,v,HWIO_SSC_SSC_WAKEUP_SECONDARY_IE_IN)
#define HWIO_SSC_SSC_WAKEUP_SECONDARY_IE_WAKEUP_IE_BMSK                                 0x1ff
#define HWIO_SSC_SSC_WAKEUP_SECONDARY_IE_WAKEUP_IE_SHFT                                   0x0

#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_0_ADDR                                  (SSC_MCC_REGS_REG_BASE      + 0x0000a000)
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_0_OFFS                                  (SSC_MCC_REGS_REG_BASE_OFFS + 0x0000a000)
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_0_RMSK                                  0xffffffff
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_0_IN          \
        in_dword_masked(HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_0_ADDR, HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_0_RMSK)
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_0_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_0_ADDR, m)
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_0_OUT(v)      \
        out_dword(HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_0_ADDR,v)
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_0_ADDR,m,v,HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_0_IN)
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_0_THRESHOLD_SLOPE_BMSK                  0xff000000
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_0_THRESHOLD_SLOPE_SHFT                        0x18
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_0_THRESHOLD_MAX_BMSK                      0xff0000
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_0_THRESHOLD_MAX_SHFT                          0x10
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_0_THRESHOLD_MIN_BMSK                        0xff00
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_0_THRESHOLD_MIN_SHFT                           0x8
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_0_CAPTURE_DELAY_BMSK                          0xf0
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_0_CAPTURE_DELAY_SHFT                           0x4
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_0_TRIG_POS_BMSK                                0xc
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_0_TRIG_POS_SHFT                                0x2
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_0_WATERMARK_EN_BMSK                            0x2
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_0_WATERMARK_EN_SHFT                            0x1
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_0_AUTO_CAL_EN_BMSK                             0x1
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_0_AUTO_CAL_EN_SHFT                             0x0

#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_ADDR                                  (SSC_MCC_REGS_REG_BASE      + 0x0000a004)
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_OFFS                                  (SSC_MCC_REGS_REG_BASE_OFFS + 0x0000a004)
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_RMSK                                  0xffffffff
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_IN          \
        in_dword_masked(HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_ADDR, HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_RMSK)
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_ADDR, m)
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_OUT(v)      \
        out_dword(HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_ADDR,v)
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_ADDR,m,v,HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_IN)
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_VS_CSR_QSS_MUX_SEL_BMSK               0x80000000
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_VS_CSR_QSS_MUX_SEL_SHFT                     0x1f
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_VS_CSR_STATUS_RD_DONE_BMSK            0x40000000
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_VS_CSR_STATUS_RD_DONE_SHFT                  0x1e
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_RSVD_BITS29_23_BMSK                   0x3f800000
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_RSVD_BITS29_23_SHFT                         0x17
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_FIFO_RD_ADDRESS_BMSK                    0x7c0000
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_FIFO_RD_ADDRESS_SHFT                        0x12
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_ALARM_SLOPE_NEG_EN_BMSK                  0x20000
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_ALARM_SLOPE_NEG_EN_SHFT                     0x11
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_ALARM_SLOPE_POS_EN_BMSK                  0x10000
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_ALARM_SLOPE_POS_EN_SHFT                     0x10
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_ALARM_MIN_EN_BMSK                         0x8000
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_ALARM_MIN_EN_SHFT                            0xf
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_ALARM_MAX_EN_BMSK                         0x4000
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_ALARM_MAX_EN_SHFT                            0xe
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_POWER_EN_BMSK                             0x2000
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_POWER_EN_SHFT                                0xd
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_FUNC_EN_BMSK                              0x1000
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_FUNC_EN_SHFT                                 0xc
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_RSVD_BIT11_10_BMSK                         0xc00
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_RSVD_BIT11_10_SHFT                           0xa
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_HW_CAPTURE_EN_BMSK                         0x200
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_HW_CAPTURE_EN_SHFT                           0x9
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_SW_CAPTURE_BMSK                            0x100
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_SW_CAPTURE_SHFT                              0x8
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_TRIG_SEL_BMSK                               0xe0
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_TRIG_SEL_SHFT                                0x5
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_MODE_SEL_BMSK                               0x10
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_MODE_SEL_SHFT                                0x4
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_VCO_FILTER_EN_BMSK                           0x8
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_VCO_FILTER_EN_SHFT                           0x3
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_VCO_POWER_SEL_BMSK                           0x4
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_VCO_POWER_SEL_SHFT                           0x2
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_SLOPE_DELTA_CYC_BMSK                         0x3
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_SLOPE_DELTA_CYC_SHFT                         0x0

#define HWIO_SSC_SSC_VSENSE_SENSOR0_SUMMARY_ADDR                                   (SSC_MCC_REGS_REG_BASE      + 0x0000a008)
#define HWIO_SSC_SSC_VSENSE_SENSOR0_SUMMARY_OFFS                                   (SSC_MCC_REGS_REG_BASE_OFFS + 0x0000a008)
#define HWIO_SSC_SSC_VSENSE_SENSOR0_SUMMARY_RMSK                                   0xffffffff
#define HWIO_SSC_SSC_VSENSE_SENSOR0_SUMMARY_IN          \
        in_dword_masked(HWIO_SSC_SSC_VSENSE_SENSOR0_SUMMARY_ADDR, HWIO_SSC_SSC_VSENSE_SENSOR0_SUMMARY_RMSK)
#define HWIO_SSC_SSC_VSENSE_SENSOR0_SUMMARY_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_VSENSE_SENSOR0_SUMMARY_ADDR, m)
#define HWIO_SSC_SSC_VSENSE_SENSOR0_SUMMARY_VSENSE_SUMMARY_DATA_BMSK               0xfffc0000
#define HWIO_SSC_SSC_VSENSE_SENSOR0_SUMMARY_VSENSE_SUMMARY_DATA_SHFT                     0x12
#define HWIO_SSC_SSC_VSENSE_SENSOR0_SUMMARY_FIFO_DATA_BMSK                            0x3fc00
#define HWIO_SSC_SSC_VSENSE_SENSOR0_SUMMARY_FIFO_DATA_SHFT                                0xa
#define HWIO_SSC_SSC_VSENSE_SENSOR0_SUMMARY_FSM_STATE_BMSK                              0x3c0
#define HWIO_SSC_SSC_VSENSE_SENSOR0_SUMMARY_FSM_STATE_SHFT                                0x6
#define HWIO_SSC_SSC_VSENSE_SENSOR0_SUMMARY_FIFO_COMPLETE_BMSK                           0x20
#define HWIO_SSC_SSC_VSENSE_SENSOR0_SUMMARY_FIFO_COMPLETE_SHFT                            0x5
#define HWIO_SSC_SSC_VSENSE_SENSOR0_SUMMARY_FIFO_ACTIVE_BMSK                             0x10
#define HWIO_SSC_SSC_VSENSE_SENSOR0_SUMMARY_FIFO_ACTIVE_SHFT                              0x4
#define HWIO_SSC_SSC_VSENSE_SENSOR0_SUMMARY_ALARM_MAX_BMSK                                0x8
#define HWIO_SSC_SSC_VSENSE_SENSOR0_SUMMARY_ALARM_MAX_SHFT                                0x3
#define HWIO_SSC_SSC_VSENSE_SENSOR0_SUMMARY_ALARM_MIN_BMSK                                0x4
#define HWIO_SSC_SSC_VSENSE_SENSOR0_SUMMARY_ALARM_MIN_SHFT                                0x2
#define HWIO_SSC_SSC_VSENSE_SENSOR0_SUMMARY_ALARM_SLOPE_NEG_BMSK                          0x2
#define HWIO_SSC_SSC_VSENSE_SENSOR0_SUMMARY_ALARM_SLOPE_NEG_SHFT                          0x1
#define HWIO_SSC_SSC_VSENSE_SENSOR0_SUMMARY_ALARM_SLOPE_POS_BMSK                          0x1
#define HWIO_SSC_SSC_VSENSE_SENSOR0_SUMMARY_ALARM_SLOPE_POS_SHFT                          0x0

#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_0_ADDR                                  (SSC_MCC_REGS_REG_BASE      + 0x0000a00c)
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_0_OFFS                                  (SSC_MCC_REGS_REG_BASE_OFFS + 0x0000a00c)
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_0_RMSK                                  0xffffffff
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_0_IN          \
        in_dword_masked(HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_0_ADDR, HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_0_RMSK)
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_0_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_0_ADDR, m)
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_0_OUT(v)      \
        out_dword(HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_0_ADDR,v)
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_0_ADDR,m,v,HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_0_IN)
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_0_THRESHOLD_SLOPE_BMSK                  0xff000000
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_0_THRESHOLD_SLOPE_SHFT                        0x18
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_0_THRESHOLD_MAX_BMSK                      0xff0000
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_0_THRESHOLD_MAX_SHFT                          0x10
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_0_THRESHOLD_MIN_BMSK                        0xff00
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_0_THRESHOLD_MIN_SHFT                           0x8
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_0_CAPTURE_DELAY_BMSK                          0xf0
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_0_CAPTURE_DELAY_SHFT                           0x4
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_0_TRIG_POS_BMSK                                0xc
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_0_TRIG_POS_SHFT                                0x2
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_0_WATERMARK_EN_BMSK                            0x2
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_0_WATERMARK_EN_SHFT                            0x1
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_0_AUTO_CAL_EN_BMSK                             0x1
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_0_AUTO_CAL_EN_SHFT                             0x0

#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_ADDR                                  (SSC_MCC_REGS_REG_BASE      + 0x0000a010)
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_OFFS                                  (SSC_MCC_REGS_REG_BASE_OFFS + 0x0000a010)
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_RMSK                                  0xffffffff
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_IN          \
        in_dword_masked(HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_ADDR, HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_RMSK)
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_ADDR, m)
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_OUT(v)      \
        out_dword(HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_ADDR,v)
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_ADDR,m,v,HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_IN)
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_VS_CSR_QSS_MUX_SEL_BMSK               0x80000000
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_VS_CSR_QSS_MUX_SEL_SHFT                     0x1f
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_VS_CSR_STATUS_RD_DONE_BMSK            0x40000000
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_VS_CSR_STATUS_RD_DONE_SHFT                  0x1e
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_RSVD_BITS29_23_BMSK                   0x3f800000
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_RSVD_BITS29_23_SHFT                         0x17
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_FIFO_RD_ADDRESS_BMSK                    0x7c0000
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_FIFO_RD_ADDRESS_SHFT                        0x12
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_ALARM_SLOPE_NEG_EN_BMSK                  0x20000
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_ALARM_SLOPE_NEG_EN_SHFT                     0x11
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_ALARM_SLOPE_POS_EN_BMSK                  0x10000
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_ALARM_SLOPE_POS_EN_SHFT                     0x10
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_ALARM_MIN_EN_BMSK                         0x8000
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_ALARM_MIN_EN_SHFT                            0xf
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_ALARM_MAX_EN_BMSK                         0x4000
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_ALARM_MAX_EN_SHFT                            0xe
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_POWER_EN_BMSK                             0x2000
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_POWER_EN_SHFT                                0xd
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_FUNC_EN_BMSK                              0x1000
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_FUNC_EN_SHFT                                 0xc
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_RSVD_BIT11_10_BMSK                         0xc00
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_RSVD_BIT11_10_SHFT                           0xa
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_HW_CAPTURE_EN_BMSK                         0x200
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_HW_CAPTURE_EN_SHFT                           0x9
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_SW_CAPTURE_BMSK                            0x100
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_SW_CAPTURE_SHFT                              0x8
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_TRIG_SEL_BMSK                               0xe0
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_TRIG_SEL_SHFT                                0x5
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_MODE_SEL_BMSK                               0x10
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_MODE_SEL_SHFT                                0x4
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_VCO_FILTER_EN_BMSK                           0x8
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_VCO_FILTER_EN_SHFT                           0x3
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_VCO_POWER_SEL_BMSK                           0x4
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_VCO_POWER_SEL_SHFT                           0x2
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_SLOPE_DELTA_CYC_BMSK                         0x3
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_SLOPE_DELTA_CYC_SHFT                         0x0

#define HWIO_SSC_SSC_VSENSE_SENSOR1_SUMMARY_ADDR                                   (SSC_MCC_REGS_REG_BASE      + 0x0000a014)
#define HWIO_SSC_SSC_VSENSE_SENSOR1_SUMMARY_OFFS                                   (SSC_MCC_REGS_REG_BASE_OFFS + 0x0000a014)
#define HWIO_SSC_SSC_VSENSE_SENSOR1_SUMMARY_RMSK                                   0xffffffff
#define HWIO_SSC_SSC_VSENSE_SENSOR1_SUMMARY_IN          \
        in_dword_masked(HWIO_SSC_SSC_VSENSE_SENSOR1_SUMMARY_ADDR, HWIO_SSC_SSC_VSENSE_SENSOR1_SUMMARY_RMSK)
#define HWIO_SSC_SSC_VSENSE_SENSOR1_SUMMARY_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_VSENSE_SENSOR1_SUMMARY_ADDR, m)
#define HWIO_SSC_SSC_VSENSE_SENSOR1_SUMMARY_VSENSE_SUMMARY_DATA_BMSK               0xfffc0000
#define HWIO_SSC_SSC_VSENSE_SENSOR1_SUMMARY_VSENSE_SUMMARY_DATA_SHFT                     0x12
#define HWIO_SSC_SSC_VSENSE_SENSOR1_SUMMARY_FIFO_DATA_BMSK                            0x3fc00
#define HWIO_SSC_SSC_VSENSE_SENSOR1_SUMMARY_FIFO_DATA_SHFT                                0xa
#define HWIO_SSC_SSC_VSENSE_SENSOR1_SUMMARY_FSM_STATE_BMSK                              0x3c0
#define HWIO_SSC_SSC_VSENSE_SENSOR1_SUMMARY_FSM_STATE_SHFT                                0x6
#define HWIO_SSC_SSC_VSENSE_SENSOR1_SUMMARY_FIFO_COMPLETE_BMSK                           0x20
#define HWIO_SSC_SSC_VSENSE_SENSOR1_SUMMARY_FIFO_COMPLETE_SHFT                            0x5
#define HWIO_SSC_SSC_VSENSE_SENSOR1_SUMMARY_FIFO_ACTIVE_BMSK                             0x10
#define HWIO_SSC_SSC_VSENSE_SENSOR1_SUMMARY_FIFO_ACTIVE_SHFT                              0x4
#define HWIO_SSC_SSC_VSENSE_SENSOR1_SUMMARY_ALARM_MAX_BMSK                                0x8
#define HWIO_SSC_SSC_VSENSE_SENSOR1_SUMMARY_ALARM_MAX_SHFT                                0x3
#define HWIO_SSC_SSC_VSENSE_SENSOR1_SUMMARY_ALARM_MIN_BMSK                                0x4
#define HWIO_SSC_SSC_VSENSE_SENSOR1_SUMMARY_ALARM_MIN_SHFT                                0x2
#define HWIO_SSC_SSC_VSENSE_SENSOR1_SUMMARY_ALARM_SLOPE_NEG_BMSK                          0x2
#define HWIO_SSC_SSC_VSENSE_SENSOR1_SUMMARY_ALARM_SLOPE_NEG_SHFT                          0x1
#define HWIO_SSC_SSC_VSENSE_SENSOR1_SUMMARY_ALARM_SLOPE_POS_BMSK                          0x1
#define HWIO_SSC_SSC_VSENSE_SENSOR1_SUMMARY_ALARM_SLOPE_POS_SHFT                          0x0

#define HWIO_SSC_SSC_EFUSE_Q6SS_EVB_SEL_ADDR                                       (SSC_MCC_REGS_REG_BASE      + 0x0000b000)
#define HWIO_SSC_SSC_EFUSE_Q6SS_EVB_SEL_OFFS                                       (SSC_MCC_REGS_REG_BASE_OFFS + 0x0000b000)
#define HWIO_SSC_SSC_EFUSE_Q6SS_EVB_SEL_RMSK                                              0x1
#define HWIO_SSC_SSC_EFUSE_Q6SS_EVB_SEL_IN          \
        in_dword_masked(HWIO_SSC_SSC_EFUSE_Q6SS_EVB_SEL_ADDR, HWIO_SSC_SSC_EFUSE_Q6SS_EVB_SEL_RMSK)
#define HWIO_SSC_SSC_EFUSE_Q6SS_EVB_SEL_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_EFUSE_Q6SS_EVB_SEL_ADDR, m)
#define HWIO_SSC_SSC_EFUSE_Q6SS_EVB_SEL_OUT(v)      \
        out_dword(HWIO_SSC_SSC_EFUSE_Q6SS_EVB_SEL_ADDR,v)
#define HWIO_SSC_SSC_EFUSE_Q6SS_EVB_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSC_EFUSE_Q6SS_EVB_SEL_ADDR,m,v,HWIO_SSC_SSC_EFUSE_Q6SS_EVB_SEL_IN)
#define HWIO_SSC_SSC_EFUSE_Q6SS_EVB_SEL_SEL_BMSK                                          0x1
#define HWIO_SSC_SSC_EFUSE_Q6SS_EVB_SEL_SEL_SHFT                                          0x0

#define HWIO_SSC_SSC_EFUSE_Q6SS_EVB_ADDR_ADDR                                      (SSC_MCC_REGS_REG_BASE      + 0x0000b004)
#define HWIO_SSC_SSC_EFUSE_Q6SS_EVB_ADDR_OFFS                                      (SSC_MCC_REGS_REG_BASE_OFFS + 0x0000b004)
#define HWIO_SSC_SSC_EFUSE_Q6SS_EVB_ADDR_RMSK                                       0xfffffff
#define HWIO_SSC_SSC_EFUSE_Q6SS_EVB_ADDR_IN          \
        in_dword_masked(HWIO_SSC_SSC_EFUSE_Q6SS_EVB_ADDR_ADDR, HWIO_SSC_SSC_EFUSE_Q6SS_EVB_ADDR_RMSK)
#define HWIO_SSC_SSC_EFUSE_Q6SS_EVB_ADDR_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_EFUSE_Q6SS_EVB_ADDR_ADDR, m)
#define HWIO_SSC_SSC_EFUSE_Q6SS_EVB_ADDR_OUT(v)      \
        out_dword(HWIO_SSC_SSC_EFUSE_Q6SS_EVB_ADDR_ADDR,v)
#define HWIO_SSC_SSC_EFUSE_Q6SS_EVB_ADDR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSC_EFUSE_Q6SS_EVB_ADDR_ADDR,m,v,HWIO_SSC_SSC_EFUSE_Q6SS_EVB_ADDR_IN)
#define HWIO_SSC_SSC_EFUSE_Q6SS_EVB_ADDR_ADDR_BMSK                                  0xffffff0
#define HWIO_SSC_SSC_EFUSE_Q6SS_EVB_ADDR_ADDR_SHFT                                        0x4
#define HWIO_SSC_SSC_EFUSE_Q6SS_EVB_ADDR_RSVD_BIT3_0_BMSK                                 0xf
#define HWIO_SSC_SSC_EFUSE_Q6SS_EVB_ADDR_RSVD_BIT3_0_SHFT                                 0x0

#define HWIO_SSC_SSC_SPARE_1_ADDR                                                  (SSC_MCC_REGS_REG_BASE      + 0x0000c000)
#define HWIO_SSC_SSC_SPARE_1_OFFS                                                  (SSC_MCC_REGS_REG_BASE_OFFS + 0x0000c000)
#define HWIO_SSC_SSC_SPARE_1_RMSK                                                  0xffffffff
#define HWIO_SSC_SSC_SPARE_1_IN          \
        in_dword_masked(HWIO_SSC_SSC_SPARE_1_ADDR, HWIO_SSC_SSC_SPARE_1_RMSK)
#define HWIO_SSC_SSC_SPARE_1_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_SPARE_1_ADDR, m)
#define HWIO_SSC_SSC_SPARE_1_OUT(v)      \
        out_dword(HWIO_SSC_SSC_SPARE_1_ADDR,v)
#define HWIO_SSC_SSC_SPARE_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSC_SPARE_1_ADDR,m,v,HWIO_SSC_SSC_SPARE_1_IN)
#define HWIO_SSC_SSC_SPARE_1_SPARE_IN_BMSK                                         0xffff0000
#define HWIO_SSC_SSC_SPARE_1_SPARE_IN_SHFT                                               0x10
#define HWIO_SSC_SSC_SPARE_1_SPARE_OUT_BMSK                                            0xffff
#define HWIO_SSC_SSC_SPARE_1_SPARE_OUT_SHFT                                               0x0

#define HWIO_SSC_SSC_SPARE_2_ADDR                                                  (SSC_MCC_REGS_REG_BASE      + 0x0000d000)
#define HWIO_SSC_SSC_SPARE_2_OFFS                                                  (SSC_MCC_REGS_REG_BASE_OFFS + 0x0000d000)
#define HWIO_SSC_SSC_SPARE_2_RMSK                                                  0xffffffff
#define HWIO_SSC_SSC_SPARE_2_IN          \
        in_dword_masked(HWIO_SSC_SSC_SPARE_2_ADDR, HWIO_SSC_SSC_SPARE_2_RMSK)
#define HWIO_SSC_SSC_SPARE_2_INM(m)      \
        in_dword_masked(HWIO_SSC_SSC_SPARE_2_ADDR, m)
#define HWIO_SSC_SSC_SPARE_2_OUT(v)      \
        out_dword(HWIO_SSC_SSC_SPARE_2_ADDR,v)
#define HWIO_SSC_SSC_SPARE_2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SSC_SSC_SPARE_2_ADDR,m,v,HWIO_SSC_SSC_SPARE_2_IN)
#define HWIO_SSC_SSC_SPARE_2_SPARE_IN_BMSK                                         0xffff0000
#define HWIO_SSC_SSC_SPARE_2_SPARE_IN_SHFT                                               0x10
#define HWIO_SSC_SSC_SPARE_2_SPARE_OUT_BMSK                                            0xffff
#define HWIO_SSC_SSC_SPARE_2_SPARE_OUT_SHFT                                               0x0


#endif /* __CLOCKSSCHWIO_H__ */
