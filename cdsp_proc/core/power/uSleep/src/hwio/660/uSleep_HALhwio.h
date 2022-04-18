#ifndef __USLEEP_HALHWIO_H__
#define __USLEEP_HALHWIO_H__
/*
===========================================================================
*/
/**
  @file uSleep_HALhwio.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    SDM660 (Starlord) [starlord_v1.0_p3q3r97_MTO]
 
  This file contains HWIO register definitions for the following modules:
    LPASS_QDSP6V60SS_PUB
    LPASS_QDSP6V60SS_CSR
    LPASS_SCSR_REGS
    LPASS_CC
    LPASS_QDSP6V60SS_L2VIC

  'Include' filters applied: 
  'Exclude' filters applied: RESERVED DUMMY 
*/
/*
  ===========================================================================

  Copyright (c) 2016-2017 Qualcomm Technologies Incorporated.
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

  $Header: //components/rel/core.qdsp6/1.0.c2/power/uSleep/src/hwio/660/uSleep_HALhwio.h#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $

  ===========================================================================
*/

#include "msmhwiobase.h"

/*----------------------------------------------------------------------------
 * MODULE: LPASS_QDSP6V60SS_PUB
 *--------------------------------------------------------------------------*/

#define LPASS_QDSP6V60SS_PUB_REG_BASE                                             (LPASS_BASE      + 0x00700000)

#define HWIO_LPASS_QDSP6SS_VERSION_ADDR                                           (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000000)
#define HWIO_LPASS_QDSP6SS_VERSION_RMSK                                           0xffffffff
#define HWIO_LPASS_QDSP6SS_VERSION_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_VERSION_ADDR, HWIO_LPASS_QDSP6SS_VERSION_RMSK)
#define HWIO_LPASS_QDSP6SS_VERSION_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_VERSION_ADDR, m)
#define HWIO_LPASS_QDSP6SS_VERSION_MAJOR_BMSK                                     0xf0000000
#define HWIO_LPASS_QDSP6SS_VERSION_MAJOR_SHFT                                           0x1c
#define HWIO_LPASS_QDSP6SS_VERSION_MINOR_BMSK                                      0xfff0000
#define HWIO_LPASS_QDSP6SS_VERSION_MINOR_SHFT                                           0x10
#define HWIO_LPASS_QDSP6SS_VERSION_STEP_BMSK                                          0xffff
#define HWIO_LPASS_QDSP6SS_VERSION_STEP_SHFT                                             0x0

#define HWIO_LPASS_QDSP6SS_CONFIG_ID_ADDR                                         (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000004)
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_RMSK                                         0xfff1ffff
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CONFIG_ID_ADDR, HWIO_LPASS_QDSP6SS_CONFIG_ID_RMSK)
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CONFIG_ID_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_NUM_L2VIC_SRC_BMSK                           0xfff00000
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_NUM_L2VIC_SRC_SHFT                                 0x14
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_ZMEAS_PRESENT_BMSK                              0x10000
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_ZMEAS_PRESENT_SHFT                                 0x10
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_PMIC_IF_PRESENT_BMSK                             0x8000
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_PMIC_IF_PRESENT_SHFT                                0xf
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_IN_SUBSYSTEM_BMSK                                0x7000
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_IN_SUBSYSTEM_SHFT                                   0xc
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_LDO_PRESENT_BMSK                                  0x800
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_LDO_PRESENT_SHFT                                    0xb
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_BHS_PRESENT_BMSK                                  0x400
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_BHS_PRESENT_SHFT                                    0xa
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_PLL_VOTE_BMSK                                     0x200
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_PLL_VOTE_SHFT                                       0x9
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_PLL_PRESENT_BMSK                                  0x100
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_PLL_PRESENT_SHFT                                    0x8
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_CORE_TYPE_BMSK                                     0xf0
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_CORE_TYPE_SHFT                                      0x4
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_L2_SIZE_BMSK                                        0xf
#define HWIO_LPASS_QDSP6SS_CONFIG_ID_L2_SIZE_SHFT                                        0x0

#define HWIO_LPASS_QDSP6SS_RST_EVB_ADDR                                           (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000010)
#define HWIO_LPASS_QDSP6SS_RST_EVB_RMSK                                            0xffffff0
#define HWIO_LPASS_QDSP6SS_RST_EVB_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_RST_EVB_ADDR, HWIO_LPASS_QDSP6SS_RST_EVB_RMSK)
#define HWIO_LPASS_QDSP6SS_RST_EVB_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_RST_EVB_ADDR, m)
#define HWIO_LPASS_QDSP6SS_RST_EVB_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_RST_EVB_ADDR,v)
#define HWIO_LPASS_QDSP6SS_RST_EVB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_RST_EVB_ADDR,m,v,HWIO_LPASS_QDSP6SS_RST_EVB_IN)
#define HWIO_LPASS_QDSP6SS_RST_EVB_EVB_BMSK                                        0xffffff0
#define HWIO_LPASS_QDSP6SS_RST_EVB_EVB_SHFT                                              0x4

#define HWIO_LPASS_QDSP6SS_RESET_ADDR                                             (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000014)
#define HWIO_LPASS_QDSP6SS_RESET_RMSK                                                 0x7ff7
#define HWIO_LPASS_QDSP6SS_RESET_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_RESET_ADDR, HWIO_LPASS_QDSP6SS_RESET_RMSK)
#define HWIO_LPASS_QDSP6SS_RESET_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_RESET_ADDR, m)
#define HWIO_LPASS_QDSP6SS_RESET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_RESET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_RESET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_RESET_ADDR,m,v,HWIO_LPASS_QDSP6SS_RESET_IN)
#define HWIO_LPASS_QDSP6SS_RESET_CSI1_ARES_BMSK                                       0x4000
#define HWIO_LPASS_QDSP6SS_RESET_CSI1_ARES_SHFT                                          0xe
#define HWIO_LPASS_QDSP6SS_RESET_CSI0_ARES_BMSK                                       0x2000
#define HWIO_LPASS_QDSP6SS_RESET_CSI0_ARES_SHFT                                          0xd
#define HWIO_LPASS_QDSP6SS_RESET_CORE_ARCH_ARES_BMSK                                  0x1000
#define HWIO_LPASS_QDSP6SS_RESET_CORE_ARCH_ARES_SHFT                                     0xc
#define HWIO_LPASS_QDSP6SS_RESET_CORE_NONRET_ARES_BMSK                                 0x800
#define HWIO_LPASS_QDSP6SS_RESET_CORE_NONRET_ARES_SHFT                                   0xb
#define HWIO_LPASS_QDSP6SS_RESET_CORE_RET_ARES_BMSK                                    0x400
#define HWIO_LPASS_QDSP6SS_RESET_CORE_RET_ARES_SHFT                                      0xa
#define HWIO_LPASS_QDSP6SS_RESET_AXIM2_ARES_BMSK                                       0x200
#define HWIO_LPASS_QDSP6SS_RESET_AXIM2_ARES_SHFT                                         0x9
#define HWIO_LPASS_QDSP6SS_RESET_AXIS_ARES_BMSK                                        0x100
#define HWIO_LPASS_QDSP6SS_RESET_AXIS_ARES_SHFT                                          0x8
#define HWIO_LPASS_QDSP6SS_RESET_ATBM_ARES_BMSK                                         0x80
#define HWIO_LPASS_QDSP6SS_RESET_ATBM_ARES_SHFT                                          0x7
#define HWIO_LPASS_QDSP6SS_RESET_AHBM_ARES_BMSK                                         0x40
#define HWIO_LPASS_QDSP6SS_RESET_AHBM_ARES_SHFT                                          0x6
#define HWIO_LPASS_QDSP6SS_RESET_AXIM_ARES_BMSK                                         0x20
#define HWIO_LPASS_QDSP6SS_RESET_AXIM_ARES_SHFT                                          0x5
#define HWIO_LPASS_QDSP6SS_RESET_ETM_ISDB_ARES_BMSK                                     0x10
#define HWIO_LPASS_QDSP6SS_RESET_ETM_ISDB_ARES_SHFT                                      0x4
#define HWIO_LPASS_QDSP6SS_RESET_BUS_ARES_ENA_BMSK                                       0x4
#define HWIO_LPASS_QDSP6SS_RESET_BUS_ARES_ENA_SHFT                                       0x2
#define HWIO_LPASS_QDSP6SS_RESET_CORE_ARES_BMSK                                          0x2
#define HWIO_LPASS_QDSP6SS_RESET_CORE_ARES_SHFT                                          0x1
#define HWIO_LPASS_QDSP6SS_RESET_STOP_CORE_BMSK                                          0x1
#define HWIO_LPASS_QDSP6SS_RESET_STOP_CORE_SHFT                                          0x0

#define HWIO_LPASS_QDSP6SS_DBG_CFG_ADDR                                           (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000018)
#define HWIO_LPASS_QDSP6SS_DBG_CFG_RMSK                                           0xffff0003
#define HWIO_LPASS_QDSP6SS_DBG_CFG_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_DBG_CFG_ADDR, HWIO_LPASS_QDSP6SS_DBG_CFG_RMSK)
#define HWIO_LPASS_QDSP6SS_DBG_CFG_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_DBG_CFG_ADDR, m)
#define HWIO_LPASS_QDSP6SS_DBG_CFG_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_DBG_CFG_ADDR,v)
#define HWIO_LPASS_QDSP6SS_DBG_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_DBG_CFG_ADDR,m,v,HWIO_LPASS_QDSP6SS_DBG_CFG_IN)
#define HWIO_LPASS_QDSP6SS_DBG_CFG_DBG_SW_REG_BMSK                                0xff000000
#define HWIO_LPASS_QDSP6SS_DBG_CFG_DBG_SW_REG_SHFT                                      0x18
#define HWIO_LPASS_QDSP6SS_DBG_CFG_DBG_SPARE_BMSK                                   0xff0000
#define HWIO_LPASS_QDSP6SS_DBG_CFG_DBG_SPARE_SHFT                                       0x10
#define HWIO_LPASS_QDSP6SS_DBG_CFG_CTI_TIHS_ENA_BMSK                                     0x2
#define HWIO_LPASS_QDSP6SS_DBG_CFG_CTI_TIHS_ENA_SHFT                                     0x1
#define HWIO_LPASS_QDSP6SS_DBG_CFG_DBG_ARES_ENA_BMSK                                     0x1
#define HWIO_LPASS_QDSP6SS_DBG_CFG_DBG_ARES_ENA_SHFT                                     0x0

#define HWIO_LPASS_QDSP6SS_RET_CFG_ADDR                                           (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x0000001c)
#define HWIO_LPASS_QDSP6SS_RET_CFG_RMSK                                                  0x3
#define HWIO_LPASS_QDSP6SS_RET_CFG_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_RET_CFG_ADDR, HWIO_LPASS_QDSP6SS_RET_CFG_RMSK)
#define HWIO_LPASS_QDSP6SS_RET_CFG_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_RET_CFG_ADDR, m)
#define HWIO_LPASS_QDSP6SS_RET_CFG_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_RET_CFG_ADDR,v)
#define HWIO_LPASS_QDSP6SS_RET_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_RET_CFG_ADDR,m,v,HWIO_LPASS_QDSP6SS_RET_CFG_IN)
#define HWIO_LPASS_QDSP6SS_RET_CFG_ARCH_ARES_ENA_BMSK                                    0x2
#define HWIO_LPASS_QDSP6SS_RET_CFG_ARCH_ARES_ENA_SHFT                                    0x1
#define HWIO_LPASS_QDSP6SS_RET_CFG_RET_ARES_ENA_BMSK                                     0x1
#define HWIO_LPASS_QDSP6SS_RET_CFG_RET_ARES_ENA_SHFT                                     0x0

#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_ADDR                                         (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000020)
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_RMSK                                              0x30f
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_GFMUX_CTL_ADDR, HWIO_LPASS_QDSP6SS_GFMUX_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_GFMUX_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_GFMUX_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_GFMUX_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_GFMUX_CTL_IN)
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_IDLE_CORE_CLK_EN_BMSK                             0x200
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_IDLE_CORE_CLK_EN_SHFT                               0x9
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_SRC_SWITCH_CLK_OVR_BMSK                           0x100
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_SRC_SWITCH_CLK_OVR_SHFT                             0x8
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_SRC_SEL_BMSK                                    0xc
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_SRC_SEL_SHFT                                    0x2
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_ENA_BMSK                                        0x2
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_ENA_SHFT                                        0x1
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_ARES_BMSK                                       0x1
#define HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_ARES_SHFT                                       0x0

#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_ADDR                                      (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000024)
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_RMSK                                            0x1f
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_GFMUX_STATUS_ADDR, HWIO_LPASS_QDSP6SS_GFMUX_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_GFMUX_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_SEL_STATUS_BMSK                                 0x1e
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_SEL_STATUS_SHFT                                  0x1
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_SWITCH_STATUS_BMSK                               0x1
#define HWIO_LPASS_QDSP6SS_GFMUX_STATUS_SWITCH_STATUS_SHFT                               0x0

#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ADDR                                     (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000028)
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_RMSK                                     0x80000013
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ADDR, HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_RMSK)
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ADDR,m,v,HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_IN)
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ROOT_OFF_BMSK                            0x80000000
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ROOT_OFF_SHFT                                  0x1f
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                            0x10
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                             0x4
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ROOT_EN_BMSK                                    0x2
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ROOT_EN_SHFT                                    0x1
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_UPDATE_BMSK                                     0x1
#define HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_UPDATE_SHFT                                     0x0

#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_ADDR                                     (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x0000002c)
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_RMSK                                        0x1071f
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_ADDR, HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_RMSK)
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_ADDR,m,v,HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_IN)
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_RCGLITE_DISABLE_BMSK                        0x10000
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_RCGLITE_DISABLE_SHFT                           0x10
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_SEL_BMSK                                  0x700
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_SEL_SHFT                                    0x8
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_BMSK                                   0x1f
#define HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_SHFT                                    0x0

#define HWIO_LPASS_QDSP6SS_PWR_CTL_ADDR                                           (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000030)
#define HWIO_LPASS_QDSP6SS_PWR_CTL_RMSK                                            0xf7c0000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PWR_CTL_ADDR, HWIO_LPASS_QDSP6SS_PWR_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_PWR_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PWR_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PWR_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PWR_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PWR_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PWR_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PWR_CTL_IN)
#define HWIO_LPASS_QDSP6SS_PWR_CTL_LDO_PWR_UP_BG_BMSK                              0x8000000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_LDO_PWR_UP_BG_SHFT                                   0x1b
#define HWIO_LPASS_QDSP6SS_PWR_CTL_LDO_PWR_UP_BMSK                                 0x4000000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_LDO_PWR_UP_SHFT                                      0x1a
#define HWIO_LPASS_QDSP6SS_PWR_CTL_LDO_BYP_BMSK                                    0x2000000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_LDO_BYP_SHFT                                         0x19
#define HWIO_LPASS_QDSP6SS_PWR_CTL_BHS_ON_BMSK                                     0x1000000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_BHS_ON_SHFT                                          0x18
#define HWIO_LPASS_QDSP6SS_PWR_CTL_CLAMP_QMC_MEM_BMSK                               0x400000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_CLAMP_QMC_MEM_SHFT                                   0x16
#define HWIO_LPASS_QDSP6SS_PWR_CTL_CLAMP_WL_BMSK                                    0x200000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_CLAMP_WL_SHFT                                        0x15
#define HWIO_LPASS_QDSP6SS_PWR_CTL_CLAMP_IO_BMSK                                    0x100000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_CLAMP_IO_SHFT                                        0x14
#define HWIO_LPASS_QDSP6SS_PWR_CTL_SLP_RET_N_BMSK                                    0x80000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_SLP_RET_N_SHFT                                       0x13
#define HWIO_LPASS_QDSP6SS_PWR_CTL_ARR_STBY_N_BMSK                                   0x40000
#define HWIO_LPASS_QDSP6SS_PWR_CTL_ARR_STBY_N_SHFT                                      0x12

#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_ADDR                                       (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000034)
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_RMSK                                       0x3fffffff
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_ADDR, HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_IN)
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_L2PLRU_SLP_NRET_N_BMSK                     0x20000000
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_L2PLRU_SLP_NRET_N_SHFT                           0x1d
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_ETB_SLP_NRET_N_BMSK                        0x10000000
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_ETB_SLP_NRET_N_SHFT                              0x1c
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_L1IU_SLP_NRET_N_BMSK                        0xc000000
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_L1IU_SLP_NRET_N_SHFT                             0x1a
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_L1DU_SLP_NRET_N_BMSK                        0x3000000
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_L1DU_SLP_NRET_N_SHFT                             0x18
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_JU_SLP_NRET_N_BMSK                           0xe00000
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_JU_SLP_NRET_N_SHFT                               0x15
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_L2CLADE_SLP_NRET_N_BMSK                      0x100000
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_L2CLADE_SLP_NRET_N_SHFT                          0x14
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_L2TAG_SLP_NRET_N_BMSK                         0xf0000
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_L2TAG_SLP_NRET_N_SHFT                            0x10
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_L2DATA_SLP_NRET_N_BMSK                         0xffff
#define HWIO_LPASS_QDSP6SS_MEM_PWR_CTL_L2DATA_SLP_NRET_N_SHFT                            0x0

#define HWIO_LPASS_QDSP6SS_XO_CBCR_ADDR                                           (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000038)
#define HWIO_LPASS_QDSP6SS_XO_CBCR_RMSK                                           0x80000001
#define HWIO_LPASS_QDSP6SS_XO_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_XO_CBCR_ADDR, HWIO_LPASS_QDSP6SS_XO_CBCR_RMSK)
#define HWIO_LPASS_QDSP6SS_XO_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_XO_CBCR_ADDR, m)
#define HWIO_LPASS_QDSP6SS_XO_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_XO_CBCR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_XO_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_XO_CBCR_ADDR,m,v,HWIO_LPASS_QDSP6SS_XO_CBCR_IN)
#define HWIO_LPASS_QDSP6SS_XO_CBCR_CLKOFF_BMSK                                    0x80000000
#define HWIO_LPASS_QDSP6SS_XO_CBCR_CLKOFF_SHFT                                          0x1f
#define HWIO_LPASS_QDSP6SS_XO_CBCR_CLKEN_BMSK                                            0x1
#define HWIO_LPASS_QDSP6SS_XO_CBCR_CLKEN_SHFT                                            0x0

#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_ADDR                                        (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x0000003c)
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_RMSK                                        0x80000001
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SLEEP_CBCR_ADDR, HWIO_LPASS_QDSP6SS_SLEEP_CBCR_RMSK)
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SLEEP_CBCR_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SLEEP_CBCR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SLEEP_CBCR_ADDR,m,v,HWIO_LPASS_QDSP6SS_SLEEP_CBCR_IN)
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_CLKOFF_BMSK                                 0x80000000
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_CLKOFF_SHFT                                       0x1f
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_CLKEN_BMSK                                         0x1
#define HWIO_LPASS_QDSP6SS_SLEEP_CBCR_CLKEN_SHFT                                         0x0

#define HWIO_LPASS_QDSP6SS_NMI_ADDR                                               (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000040)
#define HWIO_LPASS_QDSP6SS_NMI_RMSK                                                      0x3
#define HWIO_LPASS_QDSP6SS_NMI_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_NMI_ADDR,v)
#define HWIO_LPASS_QDSP6SS_NMI_CLEAR_STATUS_BMSK                                         0x2
#define HWIO_LPASS_QDSP6SS_NMI_CLEAR_STATUS_SHFT                                         0x1
#define HWIO_LPASS_QDSP6SS_NMI_SET_NMI_BMSK                                              0x1
#define HWIO_LPASS_QDSP6SS_NMI_SET_NMI_SHFT                                              0x0

#define HWIO_LPASS_QDSP6SS_NMI_STATUS_ADDR                                        (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000044)
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_RMSK                                               0x7
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_NMI_STATUS_ADDR, HWIO_LPASS_QDSP6SS_NMI_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_NMI_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_EXT_DBG_TRIG_BMSK                                  0x4
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_EXT_DBG_TRIG_SHFT                                  0x2
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_WDOG_TRIG_BMSK                                     0x2
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_WDOG_TRIG_SHFT                                     0x1
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_PUBCSR_TRIG_BMSK                                   0x1
#define HWIO_LPASS_QDSP6SS_NMI_STATUS_PUBCSR_TRIG_SHFT                                   0x0

#define HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_ADDR                                    (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000048)
#define HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_RMSK                                           0x1
#define HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_ADDR, HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_RMSK)
#define HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_ADDR,v)
#define HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_ADDR,m,v,HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_IN)
#define HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_Q6_MON_CLKEN_BMSK                              0x1
#define HWIO_LPASS_QDSP6SS_CLOCK_SPDM_MON_Q6_MON_CLKEN_SHFT                              0x0

#define HWIO_LPASS_QDSP6SS_STATERET_CTL_ADDR                                      (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x0000004c)
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_RMSK                                             0xf
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STATERET_CTL_ADDR, HWIO_LPASS_QDSP6SS_STATERET_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STATERET_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STATERET_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STATERET_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_STATERET_CTL_IN)
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_WAKEUP_IN_BMSK                                   0x8
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_WAKEUP_IN_SHFT                                   0x3
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_WAKE_IRQ_BMSK                                    0x4
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_WAKE_IRQ_SHFT                                    0x2
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_RESTORE_BMSK                                     0x2
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_RESTORE_SHFT                                     0x1
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_SAVE_BMSK                                        0x1
#define HWIO_LPASS_QDSP6SS_STATERET_CTL_SAVE_SHFT                                        0x0

#define HWIO_LPASS_QDSP6SS_SPM_SW_TRIG_ADDR                                       (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000080)
#define HWIO_LPASS_QDSP6SS_SPM_SW_TRIG_RMSK                                              0xf
#define HWIO_LPASS_QDSP6SS_SPM_SW_TRIG_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPM_SW_TRIG_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPM_SW_TRIG_CMD_BMSK                                          0xf
#define HWIO_LPASS_QDSP6SS_SPM_SW_TRIG_CMD_SHFT                                          0x0

#define HWIO_LPASS_QDSP6SS_SPM_TRIG_STATUS_ADDR                                   (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000084)
#define HWIO_LPASS_QDSP6SS_SPM_TRIG_STATUS_RMSK                                          0xf
#define HWIO_LPASS_QDSP6SS_SPM_TRIG_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPM_TRIG_STATUS_ADDR, HWIO_LPASS_QDSP6SS_SPM_TRIG_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_SPM_TRIG_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPM_TRIG_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SPM_TRIG_STATUS_BUSY_BMSK                                     0xf
#define HWIO_LPASS_QDSP6SS_SPM_TRIG_STATUS_BUSY_SHFT                                     0x0

#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_ADDR                                      (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000088)
#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_RMSK                                             0x7
#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_INTF_HALTREQ_ADDR, HWIO_LPASS_QDSP6SS_INTF_HALTREQ_RMSK)
#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_INTF_HALTREQ_ADDR, m)
#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_INTF_HALTREQ_ADDR,v)
#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_INTF_HALTREQ_ADDR,m,v,HWIO_LPASS_QDSP6SS_INTF_HALTREQ_IN)
#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_AXIM2_BMSK                                       0x4
#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_AXIM2_SHFT                                       0x2
#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_AXIM_BMSK                                        0x2
#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_AXIM_SHFT                                        0x1
#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_ALL_BMSK                                         0x1
#define HWIO_LPASS_QDSP6SS_INTF_HALTREQ_ALL_SHFT                                         0x0

#define HWIO_LPASS_QDSP6SS_INTF_HALTACK_ADDR                                      (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x0000008c)
#define HWIO_LPASS_QDSP6SS_INTF_HALTACK_RMSK                                             0x7
#define HWIO_LPASS_QDSP6SS_INTF_HALTACK_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_INTF_HALTACK_ADDR, HWIO_LPASS_QDSP6SS_INTF_HALTACK_RMSK)
#define HWIO_LPASS_QDSP6SS_INTF_HALTACK_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_INTF_HALTACK_ADDR, m)
#define HWIO_LPASS_QDSP6SS_INTF_HALTACK_AXIM2_BMSK                                       0x4
#define HWIO_LPASS_QDSP6SS_INTF_HALTACK_AXIM2_SHFT                                       0x2
#define HWIO_LPASS_QDSP6SS_INTF_HALTACK_AXIM_BMSK                                        0x2
#define HWIO_LPASS_QDSP6SS_INTF_HALTACK_AXIM_SHFT                                        0x1
#define HWIO_LPASS_QDSP6SS_INTF_HALTACK_ALL_BMSK                                         0x1
#define HWIO_LPASS_QDSP6SS_INTF_HALTACK_ALL_SHFT                                         0x0

#define HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_ADDR                                     (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000090)
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_RMSK                                            0xf
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_AXIM2_CLAMP_E_BMSK                              0x8
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_AXIM2_CLAMP_E_SHFT                              0x3
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_AXIM2_CLAMP_L_BMSK                              0x4
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_AXIM2_CLAMP_L_SHFT                              0x2
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_AXIM_CLAMP_E_BMSK                               0x2
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_AXIM_CLAMP_E_SHFT                               0x1
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_AXIM_CLAMP_L_BMSK                               0x1
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_SET_AXIM_CLAMP_L_SHFT                               0x0

#define HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_ADDR                                   (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000094)
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_RMSK                                          0xf
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_AXIM2_CLAMP_E_BMSK                            0x8
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_AXIM2_CLAMP_E_SHFT                            0x3
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_AXIM2_CLAMP_L_BMSK                            0x4
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_AXIM2_CLAMP_L_SHFT                            0x2
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_AXIM_CLAMP_E_BMSK                             0x2
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_AXIM_CLAMP_E_SHFT                             0x1
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_AXIM_CLAMP_L_BMSK                             0x1
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_CLEAR_AXIM_CLAMP_L_SHFT                             0x0

#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_ADDR                                  (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000098)
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_RMSK                                         0xf
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_ADDR, HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_AXIM2_CLAMP_E_BMSK                           0x8
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_AXIM2_CLAMP_E_SHFT                           0x3
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_AXIM2_CLAMP_L_BMSK                           0x4
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_AXIM2_CLAMP_L_SHFT                           0x2
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_AXIM_CLAMP_E_BMSK                            0x2
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_AXIM_CLAMP_E_SHFT                            0x1
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_AXIM_CLAMP_L_BMSK                            0x1
#define HWIO_LPASS_QDSP6SS_INTFCLAMP_STATUS_AXIM_CLAMP_L_SHFT                            0x0

#define HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_ADDR                                   (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x0000009c)
#define HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_RMSK                                          0x3
#define HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_ADDR, HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_RMSK)
#define HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_ADDR, m)
#define HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_ADDR,m,v,HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_IN)
#define HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_AXIM2_BMSK                                    0x2
#define HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_AXIM2_SHFT                                    0x1
#define HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_AXIM_BMSK                                     0x1
#define HWIO_LPASS_QDSP6SS_INTF_FIFO_RESET_AXIM_SHFT                                     0x0

#define HWIO_LPASS_QDSP6SS_CP_BHS_CTL_ADDR                                        (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x000000ac)
#define HWIO_LPASS_QDSP6SS_CP_BHS_CTL_RMSK                                               0xf
#define HWIO_LPASS_QDSP6SS_CP_BHS_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CP_BHS_CTL_ADDR, HWIO_LPASS_QDSP6SS_CP_BHS_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_CP_BHS_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CP_BHS_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CP_BHS_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_CP_BHS_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_CP_BHS_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_CP_BHS_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_CP_BHS_CTL_IN)
#define HWIO_LPASS_QDSP6SS_CP_BHS_CTL_DRIVE_SEL_BMSK                                     0xf
#define HWIO_LPASS_QDSP6SS_CP_BHS_CTL_DRIVE_SEL_SHFT                                     0x0

#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_ADDR                                      (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x000000b0)
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_RMSK                                          0xaf7f
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_ADDR, HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_RMSK)
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_ADDR,v)
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_ADDR,m,v,HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_IN)
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CP0_CLK_EN_BMSK                               0x8000
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CP0_CLK_EN_SHFT                                  0xf
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AXIS_CLK_EN_BMSK                              0x2000
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AXIS_CLK_EN_SHFT                                 0xd
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AHBM_CLK_EN_BMSK                               0x800
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AHBM_CLK_EN_SHFT                                 0xb
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AHBS_CLK_EN_BMSK                               0x400
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_AHBS_CLK_EN_SHFT                                 0xa
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_PRIV_AHBS_CLK_EN_BMSK                          0x300
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_PRIV_AHBS_CLK_EN_SHFT                            0x8
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_L2VIC_AHBS_CLK_EN_BMSK                          0x60
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_L2VIC_AHBS_CLK_EN_SHFT                           0x5
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_TEST_AHBS_CLK_EN_BMSK                           0x10
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_TEST_AHBS_CLK_EN_SHFT                            0x4
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_PUB_AHBS_CLK_EN_BMSK                             0x8
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_PUB_AHBS_CLK_EN_SHFT                             0x3
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CORE_BUS_EN_BMSK                                 0x4
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CORE_BUS_EN_SHFT                                 0x2
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CORE_RCLK_EN_BMSK                                0x2
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CORE_RCLK_EN_SHFT                                0x1
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CORE_CLK_EN_BMSK                                 0x1
#define HWIO_LPASS_QDSP6SS_CGC_OVERRIDE_CORE_CLK_EN_SHFT                                 0x0

#define HWIO_LPASS_QDSP6SS_L1S_PWR_CTL_ADDR                                       (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x000000b4)
#define HWIO_LPASS_QDSP6SS_L1S_PWR_CTL_RMSK                                             0xff
#define HWIO_LPASS_QDSP6SS_L1S_PWR_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_L1S_PWR_CTL_ADDR, HWIO_LPASS_QDSP6SS_L1S_PWR_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_L1S_PWR_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_L1S_PWR_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_L1S_PWR_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_L1S_PWR_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_L1S_PWR_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_L1S_PWR_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_L1S_PWR_CTL_IN)
#define HWIO_LPASS_QDSP6SS_L1S_PWR_CTL_SLP_NRET_N_BMSK                                  0xff
#define HWIO_LPASS_QDSP6SS_L1S_PWR_CTL_SLP_NRET_N_SHFT                                   0x0

#define HWIO_LPASS_QDSP6SS_CORE_BHS_CTL_ADDR                                      (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x000000c0)
#define HWIO_LPASS_QDSP6SS_CORE_BHS_CTL_RMSK                                             0xf
#define HWIO_LPASS_QDSP6SS_CORE_BHS_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CORE_BHS_CTL_ADDR, HWIO_LPASS_QDSP6SS_CORE_BHS_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_CORE_BHS_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CORE_BHS_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CORE_BHS_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_CORE_BHS_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_CORE_BHS_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_CORE_BHS_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_CORE_BHS_CTL_IN)
#define HWIO_LPASS_QDSP6SS_CORE_BHS_CTL_DRIVE_SEL_BMSK                                   0xf
#define HWIO_LPASS_QDSP6SS_CORE_BHS_CTL_DRIVE_SEL_SHFT                                   0x0

#define HWIO_LPASS_QDSP6SS_BHS_STATUS_ADDR                                        (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x000000c4)
#define HWIO_LPASS_QDSP6SS_BHS_STATUS_RMSK                                               0x1
#define HWIO_LPASS_QDSP6SS_BHS_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_BHS_STATUS_ADDR, HWIO_LPASS_QDSP6SS_BHS_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_BHS_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_BHS_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_BHS_STATUS_BHS_EN_REST_ACK_BMSK                               0x1
#define HWIO_LPASS_QDSP6SS_BHS_STATUS_BHS_EN_REST_ACK_SHFT                               0x0

#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_ADDR                                       (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x000000c8)
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_RMSK                                              0x3
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_ADDR, HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_IN)
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_QMC_MEM_SVS_SEL_BMSK                              0x2
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_QMC_MEM_SVS_SEL_SHFT                              0x1
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_QMC_MEM_SVS_BMSK                                  0x1
#define HWIO_LPASS_QDSP6SS_QMC_SVS_CTL_QMC_MEM_SVS_SHFT                                  0x0

#define HWIO_LPASS_QDSP6SS_BHS_TEST_ADDR                                          (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x000000cc)
#define HWIO_LPASS_QDSP6SS_BHS_TEST_RMSK                                                 0x1
#define HWIO_LPASS_QDSP6SS_BHS_TEST_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_BHS_TEST_ADDR, HWIO_LPASS_QDSP6SS_BHS_TEST_RMSK)
#define HWIO_LPASS_QDSP6SS_BHS_TEST_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_BHS_TEST_ADDR, m)
#define HWIO_LPASS_QDSP6SS_BHS_TEST_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_BHS_TEST_ADDR,v)
#define HWIO_LPASS_QDSP6SS_BHS_TEST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_BHS_TEST_ADDR,m,v,HWIO_LPASS_QDSP6SS_BHS_TEST_IN)
#define HWIO_LPASS_QDSP6SS_BHS_TEST_INSTANT_ON_BMSK                                      0x1
#define HWIO_LPASS_QDSP6SS_BHS_TEST_INSTANT_ON_SHFT                                      0x0

#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_ADDR                                        (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x000000f0)
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_RMSK                                               0xf
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CP_PWR_CTL_ADDR, HWIO_LPASS_QDSP6SS_CP_PWR_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CP_PWR_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_CP_PWR_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_CP_PWR_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_CP_PWR_CTL_IN)
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_LDO_2PASS_ON_BMSK                                  0x8
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_LDO_2PASS_ON_SHFT                                  0x3
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_SHUNT_BHS_ON_BMSK                                  0x4
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_SHUNT_BHS_ON_SHFT                                  0x2
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_BHS_ON_BMSK                                        0x2
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_BHS_ON_SHFT                                        0x1
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_CLAMP_IO_BMSK                                      0x1
#define HWIO_LPASS_QDSP6SS_CP_PWR_CTL_CLAMP_IO_SHFT                                      0x0

#define HWIO_LPASS_QDSP6SS_CP_PWR_STATUS_ADDR                                     (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x000000f4)
#define HWIO_LPASS_QDSP6SS_CP_PWR_STATUS_RMSK                                            0x1
#define HWIO_LPASS_QDSP6SS_CP_PWR_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CP_PWR_STATUS_ADDR, HWIO_LPASS_QDSP6SS_CP_PWR_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_CP_PWR_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CP_PWR_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CP_PWR_STATUS_ENR_ACK_BMSK                                    0x1
#define HWIO_LPASS_QDSP6SS_CP_PWR_STATUS_ENR_ACK_SHFT                                    0x0

#define HWIO_LPASS_QDSP6SS_CP_RESET_ADDR                                          (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x000000f8)
#define HWIO_LPASS_QDSP6SS_CP_RESET_RMSK                                                 0x1
#define HWIO_LPASS_QDSP6SS_CP_RESET_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CP_RESET_ADDR, HWIO_LPASS_QDSP6SS_CP_RESET_RMSK)
#define HWIO_LPASS_QDSP6SS_CP_RESET_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CP_RESET_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CP_RESET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_CP_RESET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_CP_RESET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_CP_RESET_ADDR,m,v,HWIO_LPASS_QDSP6SS_CP_RESET_IN)
#define HWIO_LPASS_QDSP6SS_CP_RESET_ARES_BMSK                                            0x1
#define HWIO_LPASS_QDSP6SS_CP_RESET_ARES_SHFT                                            0x0

#define HWIO_LPASS_QDSP6SS_CP_CLK_CTL_ADDR                                        (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x000000fc)
#define HWIO_LPASS_QDSP6SS_CP_CLK_CTL_RMSK                                               0x1
#define HWIO_LPASS_QDSP6SS_CP_CLK_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CP_CLK_CTL_ADDR, HWIO_LPASS_QDSP6SS_CP_CLK_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_CP_CLK_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CP_CLK_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CP_CLK_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_CP_CLK_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_CP_CLK_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_CP_CLK_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_CP_CLK_CTL_IN)
#define HWIO_LPASS_QDSP6SS_CP_CLK_CTL_CLK_ENA_BMSK                                       0x1
#define HWIO_LPASS_QDSP6SS_CP_CLK_CTL_CLK_ENA_SHFT                                       0x0

#define HWIO_LPASS_QDSP6SS_STRAP_TCM_ADDR                                         (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000100)
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_RMSK                                         0xfffc0000
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_TCM_ADDR, HWIO_LPASS_QDSP6SS_STRAP_TCM_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_TCM_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_TCM_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_TCM_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_TCM_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_BASE_ADDR_BMSK                               0xfffc0000
#define HWIO_LPASS_QDSP6SS_STRAP_TCM_BASE_ADDR_SHFT                                     0x12

#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_ADDR                                    (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000104)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_RMSK                                    0xffffc000
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_ADDR, HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_UPPER_ADDR_BMSK                         0xffffc000
#define HWIO_LPASS_QDSP6SS_STRAP_AHBUPPER_UPPER_ADDR_SHFT                                0xe

#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_ADDR                                    (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000108)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_RMSK                                    0xffffc000
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_ADDR, HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_LOWER_ADDR_BMSK                         0xffffc000
#define HWIO_LPASS_QDSP6SS_STRAP_AHBLOWER_LOWER_ADDR_SHFT                                0xe

#define HWIO_LPASS_QDSP6SS_STRAP_ACC_ADDR                                         (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000110)
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_RMSK                                         0xffffffff
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_ACC_ADDR, HWIO_LPASS_QDSP6SS_STRAP_ACC_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_ACC_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_ACC_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_ACC_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_ACC_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_DATA_BMSK                                    0xffffffff
#define HWIO_LPASS_QDSP6SS_STRAP_ACC_DATA_SHFT                                           0x0

#define HWIO_LPASS_QDSP6SS_DCC_CTRL_ADDR                                          (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000118)
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_RMSK                                          0xffffffff
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_DCC_CTRL_ADDR, HWIO_LPASS_QDSP6SS_DCC_CTRL_RMSK)
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_DCC_CTRL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_DCC_CTRL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_DCC_CTRL_ADDR,m,v,HWIO_LPASS_QDSP6SS_DCC_CTRL_IN)
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_CTRL_BMSK                                     0xffffffff
#define HWIO_LPASS_QDSP6SS_DCC_CTRL_CTRL_SHFT                                            0x0

#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_ADDR                                  (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x0000011c)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_RMSK                                  0xffffc000
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_ADDR, HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_UPPER_ADDR_BMSK                       0xffffc000
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2UPPER_UPPER_ADDR_SHFT                              0xe

#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_ADDR                                  (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000120)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_RMSK                                  0xffffc000
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_ADDR, HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_LOWER_ADDR_BMSK                       0xffffc000
#define HWIO_LPASS_QDSP6SS_STRAP_AXIM2LOWER_LOWER_ADDR_SHFT                              0xe

#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_SEL_ADDR                                 (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000124)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_SEL_RMSK                                        0x1
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_SEL_ADDR, HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_SEL_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_SEL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_SEL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_SEL_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_SEL_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_SEL_STRAP_QMC_ACC_SEL_BMSK                      0x1
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_SEL_STRAP_QMC_ACC_SEL_SHFT                      0x0

#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_ADDR                                     (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000128)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_RMSK                                     0xffffffff
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_ADDR, HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_STRAP_QMC_ACC_BMSK                       0xffffffff
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_STRAP_QMC_ACC_SHFT                              0x0

#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_U_ADDR                                   (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x0000012c)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_U_RMSK                                   0xffffffff
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_U_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_U_ADDR, HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_U_RMSK)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_U_ADDR, m)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_U_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_U_ADDR,v)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_U_ADDR,m,v,HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_U_IN)
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_U_STRAP_QMC_ACC_U_BMSK                   0xffffffff
#define HWIO_LPASS_QDSP6SS_STRAP_QMC_ACC_U_STRAP_QMC_ACC_U_SHFT                          0x0

#define HWIO_LPASS_QDSP6SS_CPR_OVERRIDE_ADDR                                      (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000130)
#define HWIO_LPASS_QDSP6SS_CPR_OVERRIDE_RMSK                                             0x3
#define HWIO_LPASS_QDSP6SS_CPR_OVERRIDE_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CPR_OVERRIDE_ADDR, HWIO_LPASS_QDSP6SS_CPR_OVERRIDE_RMSK)
#define HWIO_LPASS_QDSP6SS_CPR_OVERRIDE_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CPR_OVERRIDE_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CPR_OVERRIDE_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_CPR_OVERRIDE_ADDR,v)
#define HWIO_LPASS_QDSP6SS_CPR_OVERRIDE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_CPR_OVERRIDE_ADDR,m,v,HWIO_LPASS_QDSP6SS_CPR_OVERRIDE_IN)
#define HWIO_LPASS_QDSP6SS_CPR_OVERRIDE_EXT_ABYP_DIS_BMSK                                0x2
#define HWIO_LPASS_QDSP6SS_CPR_OVERRIDE_EXT_ABYP_DIS_SHFT                                0x1
#define HWIO_LPASS_QDSP6SS_CPR_OVERRIDE_LOCAL_BYP_DIS_BMSK                               0x1
#define HWIO_LPASS_QDSP6SS_CPR_OVERRIDE_LOCAL_BYP_DIS_SHFT                               0x0

#define HWIO_LPASS_QDSP6SS_PLL_MODE_ADDR                                          (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000200)
#define HWIO_LPASS_QDSP6SS_PLL_MODE_RMSK                                          0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_MODE_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_MODE_ADDR, HWIO_LPASS_QDSP6SS_PLL_MODE_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_MODE_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_MODE_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_MODE_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_MODE_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_MODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_MODE_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_MODE_IN)
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_LOCK_DET_BMSK                             0x80000000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_LOCK_DET_SHFT                                   0x1f
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_ACTIVE_FLAG_BMSK                          0x40000000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_ACTIVE_FLAG_SHFT                                0x1e
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_ACK_LATCH_BMSK                            0x20000000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_ACK_LATCH_SHFT                                  0x1d
#define HWIO_LPASS_QDSP6SS_PLL_MODE_RESERVE_BITS28_24_BMSK                        0x1f000000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_RESERVE_BITS28_24_SHFT                              0x18
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_BMSK                 0x800000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_SHFT                     0x17
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_UPDATE_BMSK                                 0x400000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_UPDATE_SHFT                                     0x16
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_VOTE_FSM_RESET_BMSK                         0x200000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_VOTE_FSM_RESET_SHFT                             0x15
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_VOTE_FSM_ENA_BMSK                           0x100000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_VOTE_FSM_ENA_SHFT                               0x14
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_BIAS_COUNT_BMSK                              0xfc000
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_BIAS_COUNT_SHFT                                  0xe
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_LOCK_COUNT_BMSK                               0x3f00
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_LOCK_COUNT_SHFT                                  0x8
#define HWIO_LPASS_QDSP6SS_PLL_MODE_RESERVE_BITS7_4_BMSK                                0xf0
#define HWIO_LPASS_QDSP6SS_PLL_MODE_RESERVE_BITS7_4_SHFT                                 0x4
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_PLLTEST_BMSK                                     0x8
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_PLLTEST_SHFT                                     0x3
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_RESET_N_BMSK                                     0x4
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_RESET_N_SHFT                                     0x2
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_BYPASSNL_BMSK                                    0x2
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_BYPASSNL_SHFT                                    0x1
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_OUTCTRL_BMSK                                     0x1
#define HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_OUTCTRL_SHFT                                     0x0

#define HWIO_LPASS_QDSP6SS_PLL_L_VAL_ADDR                                         (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000204)
#define HWIO_LPASS_QDSP6SS_PLL_L_VAL_RMSK                                             0xffff
#define HWIO_LPASS_QDSP6SS_PLL_L_VAL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_L_VAL_ADDR, HWIO_LPASS_QDSP6SS_PLL_L_VAL_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_L_VAL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_L_VAL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_L_VAL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_L_VAL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_L_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_L_VAL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_L_VAL_IN)
#define HWIO_LPASS_QDSP6SS_PLL_L_VAL_PLL_L_BMSK                                       0xffff
#define HWIO_LPASS_QDSP6SS_PLL_L_VAL_PLL_L_SHFT                                          0x0

#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_ADDR                                     (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000208)
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_RMSK                                     0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_ADDR, HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_IN)
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_PLL_ALPHA_31_0_BMSK                      0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_PLL_ALPHA_31_0_SHFT                             0x0

#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_ADDR                                   (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x0000020c)
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_RMSK                                         0xff
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_ADDR, HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_IN)
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_PLL_ALPHA_39_32_BMSK                         0xff
#define HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_PLL_ALPHA_39_32_SHFT                          0x0

#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_ADDR                                      (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000210)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RMSK                                      0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_USER_CTL_ADDR, HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_USER_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_USER_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_USER_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_USER_CTL_IN)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RESERVE_BITS31_28_BMSK                    0xf0000000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RESERVE_BITS31_28_SHFT                          0x1c
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_SSC_MODE_CONTROL_BMSK                      0x8000000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_SSC_MODE_CONTROL_SHFT                           0x1b
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RESERVE_BITS26_25_BMSK                     0x6000000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RESERVE_BITS26_25_SHFT                          0x19
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_ALPHA_EN_BMSK                              0x1000000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_ALPHA_EN_SHFT                                   0x18
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RESERVE_BITS23_22_BMSK                      0xc00000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RESERVE_BITS23_22_SHFT                          0x16
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_VCO_SEL_BMSK                                0x300000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_VCO_SEL_SHFT                                    0x14
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RESERVE_BITS19_15_BMSK                       0xf8000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RESERVE_BITS19_15_SHFT                           0xf
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PRE_DIV_RATIO_BMSK                            0x7000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PRE_DIV_RATIO_SHFT                               0xc
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_POST_DIV_RATIO_BMSK                            0xf00
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_POST_DIV_RATIO_SHFT                              0x8
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_OUTPUT_INV_BMSK                                 0x80
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_OUTPUT_INV_SHFT                                  0x7
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RESERVE_BITS6_5_BMSK                            0x60
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_RESERVE_BITS6_5_SHFT                             0x5
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_TEST_BMSK                             0x10
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_TEST_SHFT                              0x4
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_EARLY_BMSK                             0x8
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_EARLY_SHFT                             0x3
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_AUX2_BMSK                              0x4
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_AUX2_SHFT                              0x2
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_AUX_BMSK                               0x2
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_AUX_SHFT                               0x1
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_MAIN_BMSK                              0x1
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_MAIN_SHFT                              0x0

#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_ADDR                                    (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000214)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_RMSK                                    0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_ADDR, HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_IN)
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_CALIBRATION_L_BMSK                      0xffff0000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_CALIBRATION_L_SHFT                            0x10
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_RESERVE_BITS15_12_BMSK                      0xf000
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_RESERVE_BITS15_12_SHFT                         0xc
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_LATCH_INTERFACE_BYPASS_BMSK                  0x800
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_LATCH_INTERFACE_BYPASS_SHFT                    0xb
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_STATUS_REGISTER_BMSK                         0x700
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_STATUS_REGISTER_SHFT                           0x8
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_DSM_BMSK                                      0x80
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_DSM_SHFT                                       0x7
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_WRITE_STATE_BMSK                              0x40
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_WRITE_STATE_SHFT                               0x6
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_TARGET_CTL_BMSK                               0x38
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_TARGET_CTL_SHFT                                0x3
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_LOCK_DET_BMSK                                  0x4
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_LOCK_DET_SHFT                                  0x2
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_FREEZE_PLL_BMSK                                0x2
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_FREEZE_PLL_SHFT                                0x1
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_TOGGLE_DET_BMSK                                0x1
#define HWIO_LPASS_QDSP6SS_PLL_USER_CTL_U_TOGGLE_DET_SHFT                                0x0

#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_ADDR                                    (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000218)
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_RMSK                                    0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_ADDR, HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_IN)
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_SINGLE_DMET_MODE_ENABLE_BMSK            0x80000000
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_SINGLE_DMET_MODE_ENABLE_SHFT                  0x1f
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_DMET_WINDOW_ENABLE_BMSK                 0x40000000
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_DMET_WINDOW_ENABLE_SHFT                       0x1e
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_TOGGLE_DET_SAMPLE_INTER_BMSK            0x3c000000
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_TOGGLE_DET_SAMPLE_INTER_SHFT                  0x1a
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_TOGGLE_DET_THRESHOLD_BMSK                0x3800000
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_TOGGLE_DET_THRESHOLD_SHFT                     0x17
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_TOGGLE_DET_SAMPLE_BMSK                    0x700000
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_TOGGLE_DET_SAMPLE_SHFT                        0x14
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_LOCK_DET_THRESHOLD_BMSK                    0xff000
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_LOCK_DET_THRESHOLD_SHFT                        0xc
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_LOCK_DET_SAMPLE_SIZE_BMSK                    0xf00
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_LOCK_DET_SAMPLE_SIZE_SHFT                      0x8
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_GLITCH_THRESHOLD_BMSK                         0xc0
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_GLITCH_THRESHOLD_SHFT                          0x6
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_REF_CYCLE_BMSK                                0x30
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_REF_CYCLE_SHFT                                 0x4
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_KFN_BMSK                                       0xf
#define HWIO_LPASS_QDSP6SS_PLL_CONFIG_CTL_KFN_SHFT                                       0x0

#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ADDR                                      (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x0000021c)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_RMSK                                      0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ADDR, HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_IN)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_BIAS_GEN_TRIM_BMSK                        0xe0000000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_BIAS_GEN_TRIM_SHFT                              0x1d
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_DCO_BMSK                                  0x10000000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_DCO_SHFT                                        0x1c
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_PROCESS_CALB_BMSK                          0xc000000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_PROCESS_CALB_SHFT                               0x1a
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OVERRIDE_PROCESS_CALB_BMSK                 0x2000000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OVERRIDE_PROCESS_CALB_SHFT                      0x19
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_FINE_FCW_BMSK                              0x1e00000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_FINE_FCW_SHFT                                   0x15
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OVERRIDE_FINE_FCW_BMSK                      0x100000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OVERRIDE_FINE_FCW_SHFT                          0x14
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_COARSE_FCW_BMSK                              0xfe000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_COARSE_FCW_SHFT                                  0xd
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OVERRIDE_COARSE_BMSK                          0x1000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_OVERRIDE_COARSE_SHFT                             0xc
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_DISABLE_LFSR_BMSK                              0x800
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_DISABLE_LFSR_SHFT                                0xb
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_DTEST_SEL_BMSK                                 0x700
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_DTEST_SEL_SHFT                                   0x8
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_DTEST_EN_BMSK                                   0x80
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_DTEST_EN_SHFT                                    0x7
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_BYP_TESTAMP_BMSK                                0x40
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_BYP_TESTAMP_SHFT                                 0x6
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ATEST1_SEL_BMSK                                 0x30
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ATEST1_SEL_SHFT                                  0x4
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ATEST0_SEL_BMSK                                  0xc
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ATEST0_SEL_SHFT                                  0x2
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ATEST1_EN_BMSK                                   0x2
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ATEST1_EN_SHFT                                   0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ATEST0_EN_BMSK                                   0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_ATEST0_EN_SHFT                                   0x0

#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_ADDR                                    (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000220)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_RMSK                                    0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_ADDR, HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_IN)
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_RESERVE_BITS31_14_BMSK                  0xffffc000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_RESERVE_BITS31_14_SHFT                         0xe
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_OVERRIDE_FINE_FCW_MSB_BMSK                  0x2000
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_OVERRIDE_FINE_FCW_MSB_SHFT                     0xd
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_DTEST_MODE_SEL_BMSK                         0x1800
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_DTEST_MODE_SEL_SHFT                            0xb
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NMO_OSC_SEL_BMSK                             0x600
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NMO_OSC_SEL_SHFT                               0x9
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NMO_EN_BMSK                                  0x100
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NMO_EN_SHFT                                    0x8
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NOISE_MAG_BMSK                                0xe0
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NOISE_MAG_SHFT                                 0x5
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NOISE_GEN_BMSK                                0x10
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_NOISE_GEN_SHFT                                 0x4
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_OSC_BIAS_GND_BMSK                              0x8
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_OSC_BIAS_GND_SHFT                              0x3
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_PLL_TEST_OUT_SEL_BMSK                          0x6
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_PLL_TEST_OUT_SEL_SHFT                          0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_CAL_CODE_UPDATE_BMSK                           0x1
#define HWIO_LPASS_QDSP6SS_PLL_TEST_CTL_U_CAL_CODE_UPDATE_SHFT                           0x0

#define HWIO_LPASS_QDSP6SS_PLL_STATUS_ADDR                                        (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000224)
#define HWIO_LPASS_QDSP6SS_PLL_STATUS_RMSK                                        0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_STATUS_ADDR, HWIO_LPASS_QDSP6SS_PLL_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_STATUS_STATUS_31_0_BMSK                            0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_STATUS_STATUS_31_0_SHFT                                   0x0

#define HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_ADDR                                      (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000228)
#define HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_RMSK                                      0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_ADDR, HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_IN)
#define HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_FREQUENCY_CTL_WORD_BMSK                   0xffffffff
#define HWIO_LPASS_QDSP6SS_PLL_FREQ_CTL_FREQUENCY_CTL_WORD_SHFT                          0x0

#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_STATUS_ADDR                             (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000240)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_STATUS_RMSK                                    0x3
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_STATUS_ADDR, HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_STATUS_RCG2PLL_UPD_STATUS_BMSK                 0x2
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_STATUS_RCG2PLL_UPD_STATUS_SHFT                 0x1
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_STATUS_PLL2RCG_UPD_STATUS_BMSK                 0x1
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_STATUS_PLL2RCG_UPD_STATUS_SHFT                 0x0

#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_ADDR                                (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000244)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_RMSK                                       0x3
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_ADDR, HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_IN)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_RCG2PLL_UPD_EN_BMSK                        0x2
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_RCG2PLL_UPD_EN_SHFT                        0x1
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_PLL2RCG_UPD_EN_BMSK                        0x1
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CFG_PLL2RCG_UPD_EN_SHFT                        0x0

#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_ADDR                             (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000248)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_RMSK                                   0x1f
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_ADDR, HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_IN)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_MATCH_VALUE_BMSK                       0x1f
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_DLYCTL_MATCH_VALUE_SHFT                        0x0

#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CMD_ADDR                                (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x0000024c)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CMD_RMSK                                       0x1
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CMD_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CMD_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CMD_CMD_BMSK                                   0x1
#define HWIO_LPASS_QDSP6SS_PLL_RCG_UPDATE_CMD_CMD_SHFT                                   0x0

#define HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_ADDR                                       (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000300)
#define HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_RMSK                                              0x7
#define HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_ADDR, HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_RMSK)
#define HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_ADDR, m)
#define HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_ADDR,v)
#define HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_ADDR,m,v,HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_IN)
#define HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_DBG_NMI_EN_IN_PWR_COLLAPSE_BMSK                   0x4
#define HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_DBG_NMI_EN_IN_PWR_COLLAPSE_SHFT                   0x2
#define HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_DBG_NMI_DISABLE_BMSK                              0x2
#define HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_DBG_NMI_DISABLE_SHFT                              0x1
#define HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_DBG_NMI_WAKEUP_DISABLE_BMSK                       0x1
#define HWIO_LPASS_QDSP6SS_DBG_NMI_CFG_DBG_NMI_WAKEUP_DISABLE_SHFT                       0x0

#define HWIO_LPASS_QDSP6SS_DBG_NMI_PWR_STATUS_ADDR                                (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00000304)
#define HWIO_LPASS_QDSP6SS_DBG_NMI_PWR_STATUS_RMSK                                       0x3
#define HWIO_LPASS_QDSP6SS_DBG_NMI_PWR_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_DBG_NMI_PWR_STATUS_ADDR, HWIO_LPASS_QDSP6SS_DBG_NMI_PWR_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_DBG_NMI_PWR_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_DBG_NMI_PWR_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_DBG_NMI_PWR_STATUS_QDSP6_PWR_COLLAPSE_BMSK                    0x2
#define HWIO_LPASS_QDSP6SS_DBG_NMI_PWR_STATUS_QDSP6_PWR_COLLAPSE_SHFT                    0x1
#define HWIO_LPASS_QDSP6SS_DBG_NMI_PWR_STATUS_QDSP6_IN_SLEEP_BMSK                        0x1
#define HWIO_LPASS_QDSP6SS_DBG_NMI_PWR_STATUS_QDSP6_IN_SLEEP_SHFT                        0x0

#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_ADDR                                      (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00002000)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_RMSK                                      0xffffffff
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_ADDR, HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_IN)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_SPARE_CFG_BMSK                            0xff000000
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_SPARE_CFG_SHFT                                  0x18
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_HWE_INV_BMSK                                0x800000
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_HWE_INV_SHFT                                    0x17
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_HWE_SEL_BMSK                                0x7c0000
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_HWE_SEL_SHFT                                    0x12
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_TESTBUS_EN_BMSK                              0x20000
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_TESTBUS_EN_SHFT                                 0x11
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_Q6_SEL_BMSK                                  0x10000
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_Q6_SEL_SHFT                                     0x10
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_SEL_BMSK                                      0xffff
#define HWIO_LPASS_QDSP6SS_TEST_BUS_CTL_SEL_SHFT                                         0x0

#define HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_ADDR                                    (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00002004)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_RMSK                                    0xffffffff
#define HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_ADDR, HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_RMSK)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_ADDR, m)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_VALUE_BMSK                              0xffffffff
#define HWIO_LPASS_QDSP6SS_TEST_BUS_VALUE_VALUE_SHFT                                     0x0

#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_ADDR                                    (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00002008)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_RMSK                                    0xffffffff
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_ADDR, HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_RMSK)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_ADDR, m)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_ADDR,v)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_ADDR,m,v,HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_IN)
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_VALUE_BMSK                              0xffffffff
#define HWIO_LPASS_QDSP6SS_TEST_BUS_WDATA_VALUE_SHFT                                     0x0

#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_ADDR                                        (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x0000200c)
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_RMSK                                               0x1
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PWRDBG_CTL_ADDR, HWIO_LPASS_QDSP6SS_PWRDBG_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PWRDBG_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PWRDBG_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PWRDBG_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PWRDBG_CTL_IN)
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_ENA_BMSK                                           0x1
#define HWIO_LPASS_QDSP6SS_PWRDBG_CTL_ENA_SHFT                                           0x0

#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_ADDR                                      (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00002010)
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_RMSK                                            0x7f
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_ADDR, HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_IN)
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_Q6_DBG_CLK_EN_BMSK                              0x40
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_Q6_DBG_CLK_EN_SHFT                               0x6
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_Q6_DBG_CLK_INV_BMSK                             0x20
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_Q6_DBG_CLK_INV_SHFT                              0x5
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_DBG_CLK_SEL_BMSK                                0x1f
#define HWIO_LPASS_QDSP6SS_TEST_CLK_CTL_DBG_CLK_SEL_SHFT                                 0x0

#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ADDR                                      (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00002018)
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_RMSK                                        0xffffff
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ADDR, HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_RMSK)
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ADDR, m)
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ADDR,v)
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ADDR,m,v,HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_IN)
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_COUNT_BMSK                            0xffffe0
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_COUNT_SHFT                                 0x5
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_MUX_SEL_BMSK                                    0x10
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_MUX_SEL_SHFT                                     0x4
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_CLK_R_ENA_BMSK                             0x8
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_CLK_R_ENA_SHFT                             0x3
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_CGC_EN_BMSK                                0x4
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_CGC_EN_SHFT                                0x2
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_BYPASS_BMSK                                0x2
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_BYPASS_SHFT                                0x1
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_SW_RESET_BMSK                              0x1
#define HWIO_LPASS_QDSP6SS_ZMEAS_CONFIG_ZMEAS_SW_RESET_SHFT                              0x0

#define HWIO_LPASS_QDSP6SS_CORE_STATUS_ADDR                                       (LPASS_QDSP6V60SS_PUB_REG_BASE      + 0x00002028)
#define HWIO_LPASS_QDSP6SS_CORE_STATUS_RMSK                                              0x7
#define HWIO_LPASS_QDSP6SS_CORE_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CORE_STATUS_ADDR, HWIO_LPASS_QDSP6SS_CORE_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_CORE_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CORE_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CORE_STATUS_CP0_IDLE_BMSK                                     0x4
#define HWIO_LPASS_QDSP6SS_CORE_STATUS_CP0_IDLE_SHFT                                     0x2
#define HWIO_LPASS_QDSP6SS_CORE_STATUS_CORE_IN_SLEEP_BMSK                                0x2
#define HWIO_LPASS_QDSP6SS_CORE_STATUS_CORE_IN_SLEEP_SHFT                                0x1
#define HWIO_LPASS_QDSP6SS_CORE_STATUS_CORE_STATE_BMSK                                   0x1
#define HWIO_LPASS_QDSP6SS_CORE_STATUS_CORE_STATE_SHFT                                   0x0

/*----------------------------------------------------------------------------
 * MODULE: LPASS_QDSP6V60SS_CSR
 *--------------------------------------------------------------------------*/

#define LPASS_QDSP6V60SS_CSR_REG_BASE                                                      (LPASS_BASE      + 0x00780000)

#define HWIO_LPASS_QDSP6SS_INSTANCE_ID_ADDR                                                (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00000000)
#define HWIO_LPASS_QDSP6SS_INSTANCE_ID_RMSK                                                       0x7
#define HWIO_LPASS_QDSP6SS_INSTANCE_ID_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_INSTANCE_ID_ADDR, HWIO_LPASS_QDSP6SS_INSTANCE_ID_RMSK)
#define HWIO_LPASS_QDSP6SS_INSTANCE_ID_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_INSTANCE_ID_ADDR, m)
#define HWIO_LPASS_QDSP6SS_INSTANCE_ID_ID_BMSK                                                    0x7
#define HWIO_LPASS_QDSP6SS_INSTANCE_ID_ID_SHFT                                                    0x0

#define HWIO_LPASS_QDSP6SS_CP_EFUSE_STATUS_ADDR                                            (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00000100)
#define HWIO_LPASS_QDSP6SS_CP_EFUSE_STATUS_RMSK                                                   0x1
#define HWIO_LPASS_QDSP6SS_CP_EFUSE_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CP_EFUSE_STATUS_ADDR, HWIO_LPASS_QDSP6SS_CP_EFUSE_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_CP_EFUSE_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_CP_EFUSE_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_CP_EFUSE_STATUS_HVX_EN_BMSK                                            0x1
#define HWIO_LPASS_QDSP6SS_CP_EFUSE_STATUS_HVX_EN_SHFT                                            0x0

#define HWIO_LPASS_QDSP6SS_WDOG_RESET_ADDR                                                 (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00002000)
#define HWIO_LPASS_QDSP6SS_WDOG_RESET_RMSK                                                        0x1
#define HWIO_LPASS_QDSP6SS_WDOG_RESET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_WDOG_RESET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_WDOG_RESET_WDOG_RESET_BMSK                                             0x1
#define HWIO_LPASS_QDSP6SS_WDOG_RESET_WDOG_RESET_SHFT                                             0x0

#define HWIO_LPASS_QDSP6SS_WDOG_CTL_ADDR                                                   (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00002004)
#define HWIO_LPASS_QDSP6SS_WDOG_CTL_RMSK                                                          0x7
#define HWIO_LPASS_QDSP6SS_WDOG_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WDOG_CTL_ADDR, HWIO_LPASS_QDSP6SS_WDOG_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_WDOG_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WDOG_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_WDOG_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_WDOG_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_WDOG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_WDOG_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_WDOG_CTL_IN)
#define HWIO_LPASS_QDSP6SS_WDOG_CTL_WDOG_TO_NMI_EN_BMSK                                           0x4
#define HWIO_LPASS_QDSP6SS_WDOG_CTL_WDOG_TO_NMI_EN_SHFT                                           0x2
#define HWIO_LPASS_QDSP6SS_WDOG_CTL_UNMASKED_INT_EN_BMSK                                          0x2
#define HWIO_LPASS_QDSP6SS_WDOG_CTL_UNMASKED_INT_EN_SHFT                                          0x1
#define HWIO_LPASS_QDSP6SS_WDOG_CTL_ENABLE_BMSK                                                   0x1
#define HWIO_LPASS_QDSP6SS_WDOG_CTL_ENABLE_SHFT                                                   0x0

#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_ADDR                                                (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00002008)
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_RMSK                                                0xf81fffff
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WDOG_STATUS_ADDR, HWIO_LPASS_QDSP6SS_WDOG_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WDOG_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_RESET_SYNC_STATUS_BMSK                              0x80000000
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_RESET_SYNC_STATUS_SHFT                                    0x1f
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_BITE_TIME_SYNC_STATUS_BMSK                          0x40000000
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_BITE_TIME_SYNC_STATUS_SHFT                                0x1e
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_BARK_TIME_SYNC_STATUS_BMSK                          0x20000000
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_BARK_TIME_SYNC_STATUS_SHFT                                0x1d
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_NMI_TIME_SYNC_STATUS_BMSK                           0x10000000
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_NMI_TIME_SYNC_STATUS_SHFT                                 0x1c
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_TEST_LOAD_SYNC_STATUS_BMSK                           0x8000000
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_TEST_LOAD_SYNC_STATUS_SHFT                                0x1b
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_WDOG_COUNT_BMSK                                       0x1ffffe
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_WDOG_COUNT_SHFT                                            0x1
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_WDOG_EXPIRED_STATUS_BMSK                                   0x1
#define HWIO_LPASS_QDSP6SS_WDOG_STATUS_WDOG_EXPIRED_STATUS_SHFT                                   0x0

#define HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_ADDR                                             (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x0000200c)
#define HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_RMSK                                                0xfffff
#define HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_ADDR, HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_RMSK)
#define HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_ADDR, m)
#define HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_ADDR,v)
#define HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_ADDR,m,v,HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_IN)
#define HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_DATA_BMSK                                           0xfffff
#define HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_DATA_SHFT                                               0x0

#define HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_ADDR                                             (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00002010)
#define HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_RMSK                                                0xfffff
#define HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_ADDR, HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_RMSK)
#define HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_ADDR, m)
#define HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_ADDR,v)
#define HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_ADDR,m,v,HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_IN)
#define HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_DATA_BMSK                                           0xfffff
#define HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_DATA_SHFT                                               0x0

#define HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_ADDR                                              (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00002014)
#define HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_RMSK                                                 0xfffff
#define HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_ADDR, HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_RMSK)
#define HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_ADDR, m)
#define HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_ADDR,v)
#define HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_ADDR,m,v,HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_IN)
#define HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_DATA_BMSK                                            0xfffff
#define HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_DATA_SHFT                                                0x0

#define HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_ADDR                                             (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00002018)
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_RMSK                                                    0x1
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_ADDR,v)
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_LOAD_BMSK                                               0x1
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_LOAD_SHFT                                               0x0

#define HWIO_LPASS_QDSP6SS_WDOG_TEST_ADDR                                                  (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x0000201c)
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_RMSK                                                    0x1fffff
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WDOG_TEST_ADDR, HWIO_LPASS_QDSP6SS_WDOG_TEST_RMSK)
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WDOG_TEST_ADDR, m)
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_WDOG_TEST_ADDR,v)
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_WDOG_TEST_ADDR,m,v,HWIO_LPASS_QDSP6SS_WDOG_TEST_IN)
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_SYNC_STATUS_BMSK                                        0x100000
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_SYNC_STATUS_SHFT                                            0x14
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_VALUE_BMSK                                          0xfffff
#define HWIO_LPASS_QDSP6SS_WDOG_TEST_LOAD_VALUE_SHFT                                              0x0

#define HWIO_LPASS_QDSP6SS_GLBCNT_TRIG_CFG_ADDR                                            (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00002100)
#define HWIO_LPASS_QDSP6SS_GLBCNT_TRIG_CFG_RMSK                                                   0xf
#define HWIO_LPASS_QDSP6SS_GLBCNT_TRIG_CFG_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_GLBCNT_TRIG_CFG_ADDR, HWIO_LPASS_QDSP6SS_GLBCNT_TRIG_CFG_RMSK)
#define HWIO_LPASS_QDSP6SS_GLBCNT_TRIG_CFG_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_GLBCNT_TRIG_CFG_ADDR, m)
#define HWIO_LPASS_QDSP6SS_GLBCNT_TRIG_CFG_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_GLBCNT_TRIG_CFG_ADDR,v)
#define HWIO_LPASS_QDSP6SS_GLBCNT_TRIG_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_GLBCNT_TRIG_CFG_ADDR,m,v,HWIO_LPASS_QDSP6SS_GLBCNT_TRIG_CFG_IN)
#define HWIO_LPASS_QDSP6SS_GLBCNT_TRIG_CFG_MAX_COUNT_BMSK                                         0xe
#define HWIO_LPASS_QDSP6SS_GLBCNT_TRIG_CFG_MAX_COUNT_SHFT                                         0x1
#define HWIO_LPASS_QDSP6SS_GLBCNT_TRIG_CFG_DISABLE_BMSK                                           0x1
#define HWIO_LPASS_QDSP6SS_GLBCNT_TRIG_CFG_DISABLE_SHFT                                           0x0

#define HWIO_LPASS_QDSP6SS_TS_m_EN_ADDR(m)                                                 (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00003000 + 0x10 * (m))
#define HWIO_LPASS_QDSP6SS_TS_m_EN_RMSK                                                           0x7
#define HWIO_LPASS_QDSP6SS_TS_m_EN_MAXm                                                             3
#define HWIO_LPASS_QDSP6SS_TS_m_EN_INI(m)        \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TS_m_EN_ADDR(m), HWIO_LPASS_QDSP6SS_TS_m_EN_RMSK)
#define HWIO_LPASS_QDSP6SS_TS_m_EN_INMI(m,mask)    \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TS_m_EN_ADDR(m), mask)
#define HWIO_LPASS_QDSP6SS_TS_m_EN_OUTI(m,val)    \
        out_dword(HWIO_LPASS_QDSP6SS_TS_m_EN_ADDR(m),val)
#define HWIO_LPASS_QDSP6SS_TS_m_EN_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_TS_m_EN_ADDR(m),mask,val,HWIO_LPASS_QDSP6SS_TS_m_EN_INI(m))
#define HWIO_LPASS_QDSP6SS_TS_m_EN_MODE_BMSK                                                      0x4
#define HWIO_LPASS_QDSP6SS_TS_m_EN_MODE_SHFT                                                      0x2
#define HWIO_LPASS_QDSP6SS_TS_m_EN_CLEAR_BMSK                                                     0x2
#define HWIO_LPASS_QDSP6SS_TS_m_EN_CLEAR_SHFT                                                     0x1
#define HWIO_LPASS_QDSP6SS_TS_m_EN_EN_BMSK                                                        0x1
#define HWIO_LPASS_QDSP6SS_TS_m_EN_EN_SHFT                                                        0x0

#define HWIO_LPASS_QDSP6SS_TS_m_STATUS_ADDR(m)                                             (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00003004 + 0x10 * (m))
#define HWIO_LPASS_QDSP6SS_TS_m_STATUS_RMSK                                                     0x101
#define HWIO_LPASS_QDSP6SS_TS_m_STATUS_MAXm                                                         3
#define HWIO_LPASS_QDSP6SS_TS_m_STATUS_INI(m)        \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TS_m_STATUS_ADDR(m), HWIO_LPASS_QDSP6SS_TS_m_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_TS_m_STATUS_INMI(m,mask)    \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TS_m_STATUS_ADDR(m), mask)
#define HWIO_LPASS_QDSP6SS_TS_m_STATUS_OVERFLOW_BMSK                                            0x100
#define HWIO_LPASS_QDSP6SS_TS_m_STATUS_OVERFLOW_SHFT                                              0x8
#define HWIO_LPASS_QDSP6SS_TS_m_STATUS_VALID_BMSK                                                 0x1
#define HWIO_LPASS_QDSP6SS_TS_m_STATUS_VALID_SHFT                                                 0x0

#define HWIO_LPASS_QDSP6SS_TS_m_TIMESTAMP_L_ADDR(m)                                        (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00003008 + 0x10 * (m))
#define HWIO_LPASS_QDSP6SS_TS_m_TIMESTAMP_L_RMSK                                           0xffffffff
#define HWIO_LPASS_QDSP6SS_TS_m_TIMESTAMP_L_MAXm                                                    3
#define HWIO_LPASS_QDSP6SS_TS_m_TIMESTAMP_L_INI(m)        \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TS_m_TIMESTAMP_L_ADDR(m), HWIO_LPASS_QDSP6SS_TS_m_TIMESTAMP_L_RMSK)
#define HWIO_LPASS_QDSP6SS_TS_m_TIMESTAMP_L_INMI(m,mask)    \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TS_m_TIMESTAMP_L_ADDR(m), mask)
#define HWIO_LPASS_QDSP6SS_TS_m_TIMESTAMP_L_DATA_L_BMSK                                    0xffffffff
#define HWIO_LPASS_QDSP6SS_TS_m_TIMESTAMP_L_DATA_L_SHFT                                           0x0

#define HWIO_LPASS_QDSP6SS_TS_m_TIMESTAMP_H_ADDR(m)                                        (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x0000300c + 0x10 * (m))
#define HWIO_LPASS_QDSP6SS_TS_m_TIMESTAMP_H_RMSK                                             0xffffff
#define HWIO_LPASS_QDSP6SS_TS_m_TIMESTAMP_H_MAXm                                                    3
#define HWIO_LPASS_QDSP6SS_TS_m_TIMESTAMP_H_INI(m)        \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TS_m_TIMESTAMP_H_ADDR(m), HWIO_LPASS_QDSP6SS_TS_m_TIMESTAMP_H_RMSK)
#define HWIO_LPASS_QDSP6SS_TS_m_TIMESTAMP_H_INMI(m,mask)    \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TS_m_TIMESTAMP_H_ADDR(m), mask)
#define HWIO_LPASS_QDSP6SS_TS_m_TIMESTAMP_H_DATA_H_BMSK                                      0xffffff
#define HWIO_LPASS_QDSP6SS_TS_m_TIMESTAMP_H_DATA_H_SHFT                                           0x0

#define HWIO_LPASS_QDSP6SS_TS_HWE_SEL_ADDR                                                 (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00003100)
#define HWIO_LPASS_QDSP6SS_TS_HWE_SEL_RMSK                                                       0x1f
#define HWIO_LPASS_QDSP6SS_TS_HWE_SEL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TS_HWE_SEL_ADDR, HWIO_LPASS_QDSP6SS_TS_HWE_SEL_RMSK)
#define HWIO_LPASS_QDSP6SS_TS_HWE_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_TS_HWE_SEL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_TS_HWE_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_TS_HWE_SEL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_TS_HWE_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_TS_HWE_SEL_ADDR,m,v,HWIO_LPASS_QDSP6SS_TS_HWE_SEL_IN)
#define HWIO_LPASS_QDSP6SS_TS_HWE_SEL_MUX_SEL_BMSK                                               0x1f
#define HWIO_LPASS_QDSP6SS_TS_HWE_SEL_MUX_SEL_SHFT                                                0x0

#define HWIO_LPASS_QDSP6SS_IPC_ADDR                                                        (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00005000)
#define HWIO_LPASS_QDSP6SS_IPC_RMSK                                                        0xffffffff
#define HWIO_LPASS_QDSP6SS_IPC_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_IPC_ADDR,v)
#define HWIO_LPASS_QDSP6SS_IPC_INTR_BMSK                                                   0xffffffff
#define HWIO_LPASS_QDSP6SS_IPC_INTR_SHFT                                                          0x0

#define HWIO_LPASS_QDSP6SS_IPC1_ADDR                                                       (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00005004)
#define HWIO_LPASS_QDSP6SS_IPC1_RMSK                                                       0xffffffff
#define HWIO_LPASS_QDSP6SS_IPC1_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_IPC1_ADDR,v)
#define HWIO_LPASS_QDSP6SS_IPC1_INTR_BMSK                                                  0xffffffff
#define HWIO_LPASS_QDSP6SS_IPC1_INTR_SHFT                                                         0x0

#define HWIO_LPASS_QDSP6SS_BLOCK_INTR_ADDR                                                 (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00007008)
#define HWIO_LPASS_QDSP6SS_BLOCK_INTR_RMSK                                                        0x7
#define HWIO_LPASS_QDSP6SS_BLOCK_INTR_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_BLOCK_INTR_ADDR, HWIO_LPASS_QDSP6SS_BLOCK_INTR_RMSK)
#define HWIO_LPASS_QDSP6SS_BLOCK_INTR_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_BLOCK_INTR_ADDR, m)
#define HWIO_LPASS_QDSP6SS_BLOCK_INTR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_BLOCK_INTR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_BLOCK_INTR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_BLOCK_INTR_ADDR,m,v,HWIO_LPASS_QDSP6SS_BLOCK_INTR_IN)
#define HWIO_LPASS_QDSP6SS_BLOCK_INTR_CLEAR_BLOCK_BMSK                                            0x4
#define HWIO_LPASS_QDSP6SS_BLOCK_INTR_CLEAR_BLOCK_SHFT                                            0x2
#define HWIO_LPASS_QDSP6SS_BLOCK_INTR_BLOCK_STATUS_BMSK                                           0x2
#define HWIO_LPASS_QDSP6SS_BLOCK_INTR_BLOCK_STATUS_SHFT                                           0x1
#define HWIO_LPASS_QDSP6SS_BLOCK_INTR_BLOCK_INTR_BMSK                                             0x1
#define HWIO_LPASS_QDSP6SS_BLOCK_INTR_BLOCK_INTR_SHFT                                             0x0

#define HWIO_LPASS_QDSP6SS_SLPC_CFG_ADDR                                                   (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x0000701c)
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_RMSK                                                       0x1fa8
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SLPC_CFG_ADDR, HWIO_LPASS_QDSP6SS_SLPC_CFG_RMSK)
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SLPC_CFG_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SLPC_CFG_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SLPC_CFG_ADDR,m,v,HWIO_LPASS_QDSP6SS_SLPC_CFG_IN)
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_EXTHW_WAKE_EN_BMSK                                         0x1000
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_EXTHW_WAKE_EN_SHFT                                            0xc
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_MEM_PU_PERI_STAGGER_BMSK                                    0x800
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_MEM_PU_PERI_STAGGER_SHFT                                      0xb
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_MEM_PD_PERI_STAGGER_BMSK                                    0x400
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_MEM_PD_PERI_STAGGER_SHFT                                      0xa
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_MEM_PU_ARRY_STAGGER_BMSK                                    0x200
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_MEM_PU_ARRY_STAGGER_SHFT                                      0x9
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_MEM_PD_ARRY_STAGGER_BMSK                                    0x100
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_MEM_PD_ARRY_STAGGER_SHFT                                      0x8
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_WAKEUP_IN_EN_BMSK                                            0x80
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_WAKEUP_IN_EN_SHFT                                             0x7
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_CLK_GATING_MODE_BMSK                                         0x20
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_CLK_GATING_MODE_SHFT                                          0x5
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_SAW_DBG_BMSK                                                  0x8
#define HWIO_LPASS_QDSP6SS_SLPC_CFG_SAW_DBG_SHFT                                                  0x3

#define HWIO_LPASS_QDSP6SS_WAKEUP_CTL_ADDR                                                 (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00007024)
#define HWIO_LPASS_QDSP6SS_WAKEUP_CTL_RMSK                                                        0x3
#define HWIO_LPASS_QDSP6SS_WAKEUP_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WAKEUP_CTL_ADDR, HWIO_LPASS_QDSP6SS_WAKEUP_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_WAKEUP_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WAKEUP_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_WAKEUP_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_WAKEUP_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_WAKEUP_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_WAKEUP_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_WAKEUP_CTL_IN)
#define HWIO_LPASS_QDSP6SS_WAKEUP_CTL_NMI_WAKE_EN_BMSK                                            0x2
#define HWIO_LPASS_QDSP6SS_WAKEUP_CTL_NMI_WAKE_EN_SHFT                                            0x1
#define HWIO_LPASS_QDSP6SS_WAKEUP_CTL_L2VIC_WAKE_EN_BMSK                                          0x1
#define HWIO_LPASS_QDSP6SS_WAKEUP_CTL_L2VIC_WAKE_EN_SHFT                                          0x0

#define HWIO_LPASS_QDSP6SS_L2VIC_WAKEUP_EN_ADDR                                            (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00007028)
#define HWIO_LPASS_QDSP6SS_L2VIC_WAKEUP_EN_RMSK                                                  0x1c
#define HWIO_LPASS_QDSP6SS_L2VIC_WAKEUP_EN_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_L2VIC_WAKEUP_EN_ADDR, HWIO_LPASS_QDSP6SS_L2VIC_WAKEUP_EN_RMSK)
#define HWIO_LPASS_QDSP6SS_L2VIC_WAKEUP_EN_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_L2VIC_WAKEUP_EN_ADDR, m)
#define HWIO_LPASS_QDSP6SS_L2VIC_WAKEUP_EN_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_L2VIC_WAKEUP_EN_ADDR,v)
#define HWIO_LPASS_QDSP6SS_L2VIC_WAKEUP_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_L2VIC_WAKEUP_EN_ADDR,m,v,HWIO_LPASS_QDSP6SS_L2VIC_WAKEUP_EN_IN)
#define HWIO_LPASS_QDSP6SS_L2VIC_WAKEUP_EN_WAKEUP_EN_BMSK                                        0x1c
#define HWIO_LPASS_QDSP6SS_L2VIC_WAKEUP_EN_WAKEUP_EN_SHFT                                         0x2

#define HWIO_LPASS_QDSP6SS_WAKEUP_STATUS_ADDR                                              (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x0000702c)
#define HWIO_LPASS_QDSP6SS_WAKEUP_STATUS_RMSK                                                    0x1f
#define HWIO_LPASS_QDSP6SS_WAKEUP_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WAKEUP_STATUS_ADDR, HWIO_LPASS_QDSP6SS_WAKEUP_STATUS_RMSK)
#define HWIO_LPASS_QDSP6SS_WAKEUP_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_WAKEUP_STATUS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_WAKEUP_STATUS_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_WAKEUP_STATUS_ADDR,v)
#define HWIO_LPASS_QDSP6SS_WAKEUP_STATUS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_WAKEUP_STATUS_ADDR,m,v,HWIO_LPASS_QDSP6SS_WAKEUP_STATUS_IN)
#define HWIO_LPASS_QDSP6SS_WAKEUP_STATUS_AXIS_WAKEUP_STICKY_BMSK                                 0x10
#define HWIO_LPASS_QDSP6SS_WAKEUP_STATUS_AXIS_WAKEUP_STICKY_SHFT                                  0x4
#define HWIO_LPASS_QDSP6SS_WAKEUP_STATUS_AXIS_WAKEUP_BMSK                                         0x8
#define HWIO_LPASS_QDSP6SS_WAKEUP_STATUS_AXIS_WAKEUP_SHFT                                         0x3
#define HWIO_LPASS_QDSP6SS_WAKEUP_STATUS_DBG_NMI_BMSK                                             0x4
#define HWIO_LPASS_QDSP6SS_WAKEUP_STATUS_DBG_NMI_SHFT                                             0x2
#define HWIO_LPASS_QDSP6SS_WAKEUP_STATUS_EXT_TRIGGER_BMSK                                         0x2
#define HWIO_LPASS_QDSP6SS_WAKEUP_STATUS_EXT_TRIGGER_SHFT                                         0x1
#define HWIO_LPASS_QDSP6SS_WAKEUP_STATUS_L2VIC_WAKEUP_BMSK                                        0x1
#define HWIO_LPASS_QDSP6SS_WAKEUP_STATUS_L2VIC_WAKEUP_SHFT                                        0x0

#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_ADDR                                              (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00007050)
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_RMSK                                                   0x3ff
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_ADDR, HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_IN)
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_PLL_FINE_OVRRD_BMSK                                    0x200
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_PLL_FINE_OVRRD_SHFT                                      0x9
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_LDO_READY_OVRRD_BMSK                                   0x100
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_LDO_READY_OVRRD_SHFT                                     0x8
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_SMMU_STATUS_OVRRD_BMSK                                  0x80
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_SMMU_STATUS_OVRRD_SHFT                                   0x7
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_AXIM2_HALTACK_OVRRD_BMSK                                0x40
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_AXIM2_HALTACK_OVRRD_SHFT                                 0x6
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_AXIM_HALTACK_OVRRD_BMSK                                 0x20
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_AXIM_HALTACK_OVRRD_SHFT                                  0x5
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_ALL_HALTACK_OVRRD_BMSK                                  0x10
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_ALL_HALTACK_OVRRD_SHFT                                   0x4
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_CORE_CLK_OFF_OVRRD_BMSK                                  0x8
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_CORE_CLK_OFF_OVRRD_SHFT                                  0x3
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_BHS_ACK_OVRRD_BMSK                                       0x4
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_BHS_ACK_OVRRD_SHFT                                       0x2
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_PLL_OVRRD_BMSK                                           0x2
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_PLL_OVRRD_SHFT                                           0x1
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_EXT_PLL_OVRRD_BMSK                                       0x1
#define HWIO_LPASS_QDSP6SS_SPM_EVENT_CTL_EXT_PLL_OVRRD_SHFT                                       0x0

#define HWIO_LPASS_QDSP6SS_SPM_TRIG_CFGn_ADDR(n)                                           (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00007080 + 0x4 * (n))
#define HWIO_LPASS_QDSP6SS_SPM_TRIG_CFGn_RMSK                                                   0x1ff
#define HWIO_LPASS_QDSP6SS_SPM_TRIG_CFGn_MAXn                                                       3
#define HWIO_LPASS_QDSP6SS_SPM_TRIG_CFGn_INI(n)        \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPM_TRIG_CFGn_ADDR(n), HWIO_LPASS_QDSP6SS_SPM_TRIG_CFGn_RMSK)
#define HWIO_LPASS_QDSP6SS_SPM_TRIG_CFGn_INMI(n,mask)    \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPM_TRIG_CFGn_ADDR(n), mask)
#define HWIO_LPASS_QDSP6SS_SPM_TRIG_CFGn_OUTI(n,val)    \
        out_dword(HWIO_LPASS_QDSP6SS_SPM_TRIG_CFGn_ADDR(n),val)
#define HWIO_LPASS_QDSP6SS_SPM_TRIG_CFGn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SPM_TRIG_CFGn_ADDR(n),mask,val,HWIO_LPASS_QDSP6SS_SPM_TRIG_CFGn_INI(n))
#define HWIO_LPASS_QDSP6SS_SPM_TRIG_CFGn_SPM_STARTADDR_BMSK                                     0x1ff
#define HWIO_LPASS_QDSP6SS_SPM_TRIG_CFGn_SPM_STARTADDR_SHFT                                       0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_ADDR                                             (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00007100)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_RMSK                                                  0xfff
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_ADDR, HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_RMSK)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_ADDR,m,v,HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_IN)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CP0_BMSK                                              0x800
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CP0_SHFT                                                0xb
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CSI1_BMSK                                             0x400
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CSI1_SHFT                                               0xa
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CSI0_BMSK                                             0x200
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CSI0_SHFT                                               0x9
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_ARCH_BMSK                                             0x100
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_ARCH_SHFT                                               0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_RET_BMSK                                               0x80
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_RET_SHFT                                                0x7
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_AXIM2_BMSK                                             0x40
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_AXIM2_SHFT                                              0x6
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_AXIS_BMSK                                              0x20
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_AXIS_SHFT                                               0x5
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_ATBM_BMSK                                              0x10
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_ATBM_SHFT                                               0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_AHBM_BMSK                                               0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_AHBM_SHFT                                               0x3
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_AXIM_BMSK                                               0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_AXIM_SHFT                                               0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_ISDB_ETM_BMSK                                           0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_ISDB_ETM_SHFT                                           0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CORE_BMSK                                               0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CORE_SHFT                                               0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_ADDR                                            (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00007104)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_RMSK                                                   0x3
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_ADDR, HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_RMSK)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_ADDR,m,v,HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_IN)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_CLAMP_CP0_BMSK                                         0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_CLAMP_CP0_SHFT                                         0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_CLAMP_IO_BMSK                                          0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_CLAMP_IO_SHFT                                          0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_ADDR                                              (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00007108)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_RMSK                                                   0x3fd
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_ADDR, HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_RMSK)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_ADDR,m,v,HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_IN)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_CP0_BMSK                                               0x200
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_CP0_SHFT                                                 0x9
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_CSI1_BMSK                                              0x100
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_CSI1_SHFT                                                0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_CSI0_BMSK                                               0x80
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_CSI0_SHFT                                                0x7
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_AXIM2_BMSK                                              0x40
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_AXIM2_SHFT                                               0x6
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_AXIS_BMSK                                               0x20
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_AXIS_SHFT                                                0x5
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_ATBM_BMSK                                               0x10
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_ATBM_SHFT                                                0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_AHBM_BMSK                                                0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_AHBM_SHFT                                                0x3
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_AXIM_BMSK                                                0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_AXIM_SHFT                                                0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_CORE_BMSK                                                0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_CORE_SHFT                                                0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_ADDR                                          (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x0000710c)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_RMSK                                          0x3fffffff
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_ADDR, HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_RMSK)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_ADDR,m,v,HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_IN)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_L2PLRU_BMSK                                   0x20000000
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_L2PLRU_SHFT                                         0x1d
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_ETB_BMSK                                      0x10000000
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_ETB_SHFT                                            0x1c
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_L1IU_BMSK                                      0xc000000
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_L1IU_SHFT                                           0x1a
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_L1DU_BMSK                                      0x3000000
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_L1DU_SHFT                                           0x18
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_JU_BMSK                                         0xe00000
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_JU_SHFT                                             0x15
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_L2CLADE_BMSK                                    0x100000
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_L2CLADE_SHFT                                        0x14
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_L2TAG_BMSK                                       0xf0000
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_L2TAG_SHFT                                          0x10
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_L2DATA_BMSK                                       0xffff
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_L2DATA_SHFT                                          0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_ADDR                                          (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00007110)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_RMSK                                                 0xf
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_ADDR, HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_IN)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_CLAMP_QMC_MEM_BMSK                                   0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_CLAMP_QMC_MEM_SHFT                                   0x3
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_CLAMP_WL_BMSK                                        0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_CLAMP_WL_SHFT                                        0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_MEM_PERIPH_BMSK                                      0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_MEM_PERIPH_SHFT                                      0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_ARR_STBY_BMSK                                        0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_ARR_STBY_SHFT                                        0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_ADDR                                              (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00007114)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_RMSK                                                     0x3
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_ADDR, HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_RMSK)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_ADDR,m,v,HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_IN)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_CP0_BHS_BMSK                                             0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_CP0_BHS_SHFT                                             0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_BHS_BMSK                                                 0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_BHS_SHFT                                                 0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_ADDR                                              (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00007118)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_RMSK                                                    0x61
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_ADDR, HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_RMSK)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_ADDR,m,v,HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_IN)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_BG_OFF_BMSK                                             0x40
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_BG_OFF_SHFT                                              0x6
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_FORCEOFF_BMSK                                           0x20
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_FORCEOFF_SHFT                                            0x5
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_BYPASS_OPEN_BMSK                                         0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_BYPASS_OPEN_SHFT                                         0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_ADDR                                              (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x0000711c)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_RMSK                                                   0x7cf
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_ADDR, HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_RMSK)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_ADDR,m,v,HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_IN)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_SMMU_PD_VOTE_BMSK                                      0x400
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_SMMU_PD_VOTE_SHFT                                        0xa
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_SHUTDOWN_REQ_BMSK                                      0x200
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_SHUTDOWN_REQ_SHFT                                        0x9
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_SPARE1_BMSK                                            0x100
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_SPARE1_SHFT                                              0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_BHS_BMSK                                                0x80
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_BHS_SHFT                                                 0x7
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_XO_ENABLE_BMSK                                          0x40
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_XO_ENABLE_SHFT                                           0x6
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_PLL_VOTE_BMSK                                            0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_PLL_VOTE_SHFT                                            0x3
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_PLL_OUTDIS_BMSK                                          0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_PLL_OUTDIS_SHFT                                          0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_PLL_BYPASS_BMSK                                          0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_PLL_BYPASS_SHFT                                          0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_PLL_RESET_BMSK                                           0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_PLL_RESET_SHFT                                           0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_ADDR                                              (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00007120)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_RMSK                                                    0x1f
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_ADDR, HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_RMSK)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_ADDR,m,v,HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_IN)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_PLL_FREEZE_BMSK                                         0x10
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_PLL_FREEZE_SHFT                                          0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_PLL_VOTE_BMSK                                            0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_PLL_VOTE_SHFT                                            0x3
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_PLL_OUTDIS_BMSK                                          0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_PLL_OUTDIS_SHFT                                          0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_PLL_BYPASS_BMSK                                          0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_PLL_BYPASS_SHFT                                          0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_PLL_RESET_BMSK                                           0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_PLL_RESET_SHFT                                           0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_ADDR                                         (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00007124)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_RMSK                                                0x7
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_ADDR, HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_RMSK)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_ADDR,m,v,HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_IN)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_WAKE_IRQ_BMSK                                       0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_WAKE_IRQ_SHFT                                       0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_RESTORE_BMSK                                        0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_RESTORE_SHFT                                        0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_SAVE_BMSK                                           0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_SAVE_SHFT                                           0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_ADDR                                      (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00007128)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_RMSK                                            0x3d
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_ADDR, HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_RMSK)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_ADDR,m,v,HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_IN)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_AXIM2_FIFO_ARESET_BMSK                          0x20
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_AXIM2_FIFO_ARESET_SHFT                           0x5
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_AXIM2_HALTREQ_BMSK                              0x10
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_AXIM2_HALTREQ_SHFT                               0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_AXIM_FIFO_ARESET_BMSK                            0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_AXIM_FIFO_ARESET_SHFT                            0x3
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_AXIM_HALTREQ_BMSK                                0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_AXIM_HALTREQ_SHFT                                0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_BUSM_HALTREQ_BMSK                                0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_BUSM_HALTREQ_SHFT                                0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_ADDR                                    (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x0000712c)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_RMSK                                          0xff
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_ADDR, HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_RMSK)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_ADDR,m,v,HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_IN)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_AXIM2_CLAMP_E_CLEAR_BMSK                      0x80
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_AXIM2_CLAMP_E_CLEAR_SHFT                       0x7
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_AXIM2_CLAMP_E_SET_BMSK                        0x40
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_AXIM2_CLAMP_E_SET_SHFT                         0x6
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_AXIM2_CLAMP_L_CLEAR_BMSK                      0x20
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_AXIM2_CLAMP_L_CLEAR_SHFT                       0x5
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_AXIM2_CLAMP_L_SET_BMSK                        0x10
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_AXIM2_CLAMP_L_SET_SHFT                         0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_AXIM_CLAMP_E_CLEAR_BMSK                        0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_AXIM_CLAMP_E_CLEAR_SHFT                        0x3
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_AXIM_CLAMP_E_SET_BMSK                          0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_AXIM_CLAMP_E_SET_SHFT                          0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_AXIM_CLAMP_L_CLEAR_BMSK                        0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_AXIM_CLAMP_L_CLEAR_SHFT                        0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_AXIM_CLAMP_L_SET_BMSK                          0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_AXIM_CLAMP_L_SET_SHFT                          0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_ADDR                                      (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00007130)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_RMSK                                             0x7
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_ADDR, HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_RMSK)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_ADDR,m,v,HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_IN)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_AXIM2_BMSK                                       0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_AXIM2_SHFT                                       0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_AXIM_BMSK                                        0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_AXIM_SHFT                                        0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_CORE_BMSK                                        0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_CORE_SHFT                                        0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L1S_ADDR                                          (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00007140)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L1S_RMSK                                                0xff
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L1S_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L1S_ADDR, HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L1S_RMSK)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L1S_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L1S_ADDR, m)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L1S_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L1S_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L1S_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L1S_ADDR,m,v,HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L1S_IN)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L1S_L1S_BMSK                                            0xff
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L1S_L1S_SHFT                                             0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_SET_ADDR                                         (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00007180)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_SET_RMSK                                              0xfff
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_SET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_SET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_SET_CP0_BMSK                                          0x800
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_SET_CP0_SHFT                                            0xb
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_SET_CSI1_BMSK                                         0x400
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_SET_CSI1_SHFT                                           0xa
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_SET_CSI0_BMSK                                         0x200
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_SET_CSI0_SHFT                                           0x9
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_SET_ARCH_BMSK                                         0x100
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_SET_ARCH_SHFT                                           0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_SET_RET_BMSK                                           0x80
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_SET_RET_SHFT                                            0x7
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_SET_AXIM2_BMSK                                         0x40
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_SET_AXIM2_SHFT                                          0x6
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_SET_AXIS_BMSK                                          0x20
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_SET_AXIS_SHFT                                           0x5
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_SET_ATBM_BMSK                                          0x10
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_SET_ATBM_SHFT                                           0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_SET_AHBM_BMSK                                           0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_SET_AHBM_SHFT                                           0x3
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_SET_AXIM_BMSK                                           0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_SET_AXIM_SHFT                                           0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_SET_ISDB_ETM_BMSK                                       0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_SET_ISDB_ETM_SHFT                                       0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_SET_CORE_BMSK                                           0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_SET_CORE_SHFT                                           0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_SET_ADDR                                        (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00007184)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_SET_RMSK                                               0x3
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_SET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_SET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_SET_CLAMP_CP0_BMSK                                     0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_SET_CLAMP_CP0_SHFT                                     0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_SET_CLAMP_IO_BMSK                                      0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_SET_CLAMP_IO_SHFT                                      0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_SET_ADDR                                          (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00007188)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_SET_RMSK                                               0x3fd
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_SET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_SET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_SET_CP0_BMSK                                           0x200
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_SET_CP0_SHFT                                             0x9
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_SET_CSI1_BMSK                                          0x100
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_SET_CSI1_SHFT                                            0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_SET_CSI0_BMSK                                           0x80
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_SET_CSI0_SHFT                                            0x7
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_SET_AXIM2_BMSK                                          0x40
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_SET_AXIM2_SHFT                                           0x6
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_SET_AXIS_BMSK                                           0x20
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_SET_AXIS_SHFT                                            0x5
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_SET_ATBM_BMSK                                           0x10
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_SET_ATBM_SHFT                                            0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_SET_AHBM_BMSK                                            0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_SET_AHBM_SHFT                                            0x3
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_SET_AXIM_BMSK                                            0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_SET_AXIM_SHFT                                            0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_SET_CORE_BMSK                                            0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_SET_CORE_SHFT                                            0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_SET_ADDR                                      (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x0000718c)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_SET_RMSK                                      0x3fffffff
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_SET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_SET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_SET_L2PLRU_BMSK                               0x20000000
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_SET_L2PLRU_SHFT                                     0x1d
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_SET_ETB_BMSK                                  0x10000000
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_SET_ETB_SHFT                                        0x1c
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_SET_L1IU_BMSK                                  0xc000000
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_SET_L1IU_SHFT                                       0x1a
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_SET_L1DU_BMSK                                  0x3000000
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_SET_L1DU_SHFT                                       0x18
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_SET_JU_BMSK                                     0xe00000
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_SET_JU_SHFT                                         0x15
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_SET_L2CLADE_BMSK                                0x100000
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_SET_L2CLADE_SHFT                                    0x14
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_SET_L2TAG_BMSK                                   0xf0000
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_SET_L2TAG_SHFT                                      0x10
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_SET_L2DATA_BMSK                                   0xffff
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_SET_L2DATA_SHFT                                      0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_SET_ADDR                                      (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00007190)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_SET_RMSK                                             0xf
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_SET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_SET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_SET_CLAMP_QMC_MEM_BMSK                               0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_SET_CLAMP_QMC_MEM_SHFT                               0x3
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_SET_CLAMP_WL_BMSK                                    0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_SET_CLAMP_WL_SHFT                                    0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_SET_MEM_PERIPH_BMSK                                  0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_SET_MEM_PERIPH_SHFT                                  0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_SET_L2DATA_STBY_BMSK                                 0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_SET_L2DATA_STBY_SHFT                                 0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_SET_ADDR                                          (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00007194)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_SET_RMSK                                                 0x3
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_SET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_SET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_SET_CP0_BHS_BMSK                                         0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_SET_CP0_BHS_SHFT                                         0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_SET_BHS_BMSK                                             0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_SET_BHS_SHFT                                             0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_SET_ADDR                                          (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00007198)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_SET_RMSK                                                0x61
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_SET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_SET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_SET_BG_OFF_BMSK                                         0x40
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_SET_BG_OFF_SHFT                                          0x6
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_SET_FORCEOFF_BMSK                                       0x20
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_SET_FORCEOFF_SHFT                                        0x5
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_SET_BYPASS_OPEN_BMSK                                     0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_SET_BYPASS_OPEN_SHFT                                     0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_SET_ADDR                                          (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x0000719c)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_SET_RMSK                                               0x7cf
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_SET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_SET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_SET_SMMU_PD_VOTE_BMSK                                  0x400
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_SET_SMMU_PD_VOTE_SHFT                                    0xa
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_SET_SHUTDOWN_REQ_BMSK                                  0x200
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_SET_SHUTDOWN_REQ_SHFT                                    0x9
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_SET_SPARE1_BMSK                                        0x100
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_SET_SPARE1_SHFT                                          0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_SET_BHS_BMSK                                            0x80
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_SET_BHS_SHFT                                             0x7
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_SET_XO_ENABLE_BMSK                                      0x40
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_SET_XO_ENABLE_SHFT                                       0x6
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_SET_PLL_VOTE_BMSK                                        0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_SET_PLL_VOTE_SHFT                                        0x3
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_SET_PLL_OUTDIS_BMSK                                      0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_SET_PLL_OUTDIS_SHFT                                      0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_SET_PLL_BYPASS_BMSK                                      0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_SET_PLL_BYPASS_SHFT                                      0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_SET_PLL_RESET_BMSK                                       0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_SET_PLL_RESET_SHFT                                       0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_SET_ADDR                                          (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x000071a0)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_SET_RMSK                                                0x1f
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_SET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_SET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_SET_PLL_FREEZE_BMSK                                     0x10
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_SET_PLL_FREEZE_SHFT                                      0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_SET_PLL_VOTE_BMSK                                        0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_SET_PLL_VOTE_SHFT                                        0x3
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_SET_PLL_OUTDIS_BMSK                                      0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_SET_PLL_OUTDIS_SHFT                                      0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_SET_PLL_BYPASS_BMSK                                      0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_SET_PLL_BYPASS_SHFT                                      0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_SET_PLL_RESET_BMSK                                       0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_SET_PLL_RESET_SHFT                                       0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_SET_ADDR                                     (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x000071a4)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_SET_RMSK                                            0x7
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_SET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_SET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_SET_WAKE_IRQ_BMSK                                   0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_SET_WAKE_IRQ_SHFT                                   0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_SET_RESTORE_BMSK                                    0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_SET_RESTORE_SHFT                                    0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_SET_SAVE_BMSK                                       0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_SET_SAVE_SHFT                                       0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_SET_ADDR                                  (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x000071a8)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_SET_RMSK                                        0x3d
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_SET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_SET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_SET_AXIM2_FIFO_ARESET_BMSK                      0x20
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_SET_AXIM2_FIFO_ARESET_SHFT                       0x5
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_SET_AXIM2_HALTREQ_BMSK                          0x10
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_SET_AXIM2_HALTREQ_SHFT                           0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_SET_AXIM_FIFO_ARESET_BMSK                        0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_SET_AXIM_FIFO_ARESET_SHFT                        0x3
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_SET_AXIM_HALTREQ_BMSK                            0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_SET_AXIM_HALTREQ_SHFT                            0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_SET_BUSM_HALTREQ_BMSK                            0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_SET_BUSM_HALTREQ_SHFT                            0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_ADDR                                (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x000071ac)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_RMSK                                      0xff
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_AXIM2_CLAMP_E_CLEAR_BMSK                  0x80
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_AXIM2_CLAMP_E_CLEAR_SHFT                   0x7
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_AXIM2_CLAMP_E_SET_BMSK                    0x40
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_AXIM2_CLAMP_E_SET_SHFT                     0x6
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_AXIM2_CLAMP_L_CLEAR_BMSK                  0x20
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_AXIM2_CLAMP_L_CLEAR_SHFT                   0x5
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_AXIM2_CLAMP_L_SET_BMSK                    0x10
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_AXIM2_CLAMP_L_SET_SHFT                     0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_AXIM_CLAMP_E_CLEAR_BMSK                    0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_AXIM_CLAMP_E_CLEAR_SHFT                    0x3
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_AXIM_CLAMP_E_SET_BMSK                      0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_AXIM_CLAMP_E_SET_SHFT                      0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_AXIM_CLAMP_L_CLEAR_BMSK                    0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_AXIM_CLAMP_L_CLEAR_SHFT                    0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_AXIM_CLAMP_L_SET_BMSK                      0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_SET_AXIM_CLAMP_L_SET_SHFT                      0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_SET_ADDR                                  (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x000071b0)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_SET_RMSK                                         0x7
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_SET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_SET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_SET_AXIM2_BMSK                                   0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_SET_AXIM2_SHFT                                   0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_SET_AXIM_BMSK                                    0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_SET_AXIM_SHFT                                    0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_SET_CORE_BMSK                                    0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_SET_CORE_SHFT                                    0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L1S_SET_ADDR                                      (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x000071c0)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L1S_SET_RMSK                                            0xff
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L1S_SET_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L1S_SET_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L1S_SET_L1S_BMSK                                        0xff
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L1S_SET_L1S_SHFT                                         0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CLEAR_ADDR                                       (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00007200)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CLEAR_RMSK                                            0xfff
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CLEAR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CLEAR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CLEAR_CP0_BMSK                                        0x800
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CLEAR_CP0_SHFT                                          0xb
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CLEAR_CSI1_BMSK                                       0x400
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CLEAR_CSI1_SHFT                                         0xa
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CLEAR_CSI0_BMSK                                       0x200
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CLEAR_CSI0_SHFT                                         0x9
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CLEAR_ARCH_BMSK                                       0x100
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CLEAR_ARCH_SHFT                                         0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CLEAR_RET_BMSK                                         0x80
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CLEAR_RET_SHFT                                          0x7
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CLEAR_AXIM2_BMSK                                       0x40
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CLEAR_AXIM2_SHFT                                        0x6
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CLEAR_AXIS_BMSK                                        0x20
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CLEAR_AXIS_SHFT                                         0x5
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CLEAR_ATBM_BMSK                                        0x10
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CLEAR_ATBM_SHFT                                         0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CLEAR_AHBM_BMSK                                         0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CLEAR_AHBM_SHFT                                         0x3
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CLEAR_AXIM_BMSK                                         0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CLEAR_AXIM_SHFT                                         0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CLEAR_ISDB_ETM_BMSK                                     0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CLEAR_ISDB_ETM_SHFT                                     0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CLEAR_CORE_BMSK                                         0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ARES_CLEAR_CORE_SHFT                                         0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_CLEAR_ADDR                                      (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00007204)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_CLEAR_RMSK                                             0x3
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_CLEAR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_CLEAR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_CLEAR_CLAMP_CP0_BMSK                                   0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_CLEAR_CLAMP_CP0_SHFT                                   0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_CLEAR_CLAMP_IO_BMSK                                    0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLAMP_CLEAR_CLAMP_IO_SHFT                                    0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_CLEAR_ADDR                                        (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00007208)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_CLEAR_RMSK                                             0x3fd
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_CLEAR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_CLEAR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_CLEAR_CP0_BMSK                                         0x200
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_CLEAR_CP0_SHFT                                           0x9
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_CLEAR_CSI1_BMSK                                        0x100
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_CLEAR_CSI1_SHFT                                          0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_CLEAR_CSI0_BMSK                                         0x80
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_CLEAR_CSI0_SHFT                                          0x7
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_CLEAR_AXIM2_BMSK                                        0x40
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_CLEAR_AXIM2_SHFT                                         0x6
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_CLEAR_AXIS_BMSK                                         0x20
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_CLEAR_AXIS_SHFT                                          0x5
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_CLEAR_ATBM_BMSK                                         0x10
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_CLEAR_ATBM_SHFT                                          0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_CLEAR_AHBM_BMSK                                          0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_CLEAR_AHBM_SHFT                                          0x3
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_CLEAR_AXIM_BMSK                                          0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_CLEAR_AXIM_SHFT                                          0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_CLEAR_CORE_BMSK                                          0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_CLK_CLEAR_CORE_SHFT                                          0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_ADDR                                    (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x0000720c)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_RMSK                                    0x3fffffff
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_L2PLRU_BMSK                             0x20000000
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_L2PLRU_SHFT                                   0x1d
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_ETB_BMSK                                0x10000000
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_ETB_SHFT                                      0x1c
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_L1IU_BMSK                                0xc000000
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_L1IU_SHFT                                     0x1a
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_L1DU_BMSK                                0x3000000
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_L1DU_SHFT                                     0x18
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_JU_BMSK                                   0xe00000
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_JU_SHFT                                       0x15
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_L2CLADE_BMSK                              0x100000
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_L2CLADE_SHFT                                  0x14
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_L2TAG_BMSK                                 0xf0000
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_L2TAG_SHFT                                    0x10
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_L2DATA_BMSK                                 0xffff
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_RET_CLEAR_L2DATA_SHFT                                    0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_CLEAR_ADDR                                    (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00007210)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_CLEAR_RMSK                                           0xf
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_CLEAR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_CLEAR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_CLEAR_CLAMP_QMC_MEM_BMSK                             0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_CLEAR_CLAMP_QMC_MEM_SHFT                             0x3
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_CLEAR_CLAMP_WL_BMSK                                  0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_CLEAR_CLAMP_WL_SHFT                                  0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_CLEAR_MEM_PERIPH_BMSK                                0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_CLEAR_MEM_PERIPH_SHFT                                0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_CLEAR_L2DATA_STBY_BMSK                               0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_CTL_CLEAR_L2DATA_STBY_SHFT                               0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_CLEAR_ADDR                                        (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00007214)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_CLEAR_RMSK                                               0x3
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_CLEAR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_CLEAR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_CLEAR_CP0_BHS_BMSK                                       0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_CLEAR_CP0_BHS_SHFT                                       0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_CLEAR_BHS_BMSK                                           0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_BHS_CLEAR_BHS_SHFT                                           0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_CLEAR_ADDR                                        (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00007218)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_CLEAR_RMSK                                              0x61
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_CLEAR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_CLEAR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_CLEAR_BG_OFF_BMSK                                       0x40
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_CLEAR_BG_OFF_SHFT                                        0x6
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_CLEAR_FORCEOFF_BMSK                                     0x20
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_CLEAR_FORCEOFF_SHFT                                      0x5
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_CLEAR_BYPASS_OPEN_BMSK                                   0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_LDO_CLEAR_BYPASS_OPEN_SHFT                                   0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_CLEAR_ADDR                                        (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x0000721c)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_CLEAR_RMSK                                             0x7cf
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_CLEAR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_CLEAR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_CLEAR_SMMU_PD_VOTE_BMSK                                0x400
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_CLEAR_SMMU_PD_VOTE_SHFT                                  0xa
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_CLEAR_SHUTDOWN_REQ_BMSK                                0x200
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_CLEAR_SHUTDOWN_REQ_SHFT                                  0x9
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_CLEAR_SPARE1_BMSK                                      0x100
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_CLEAR_SPARE1_SHFT                                        0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_CLEAR_BHS_BMSK                                          0x80
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_CLEAR_BHS_SHFT                                           0x7
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_CLEAR_XO_ENABLE_BMSK                                    0x40
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_CLEAR_XO_ENABLE_SHFT                                     0x6
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_CLEAR_PLL_VOTE_BMSK                                      0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_CLEAR_PLL_VOTE_SHFT                                      0x3
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_CLEAR_PLL_OUTDIS_BMSK                                    0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_CLEAR_PLL_OUTDIS_SHFT                                    0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_CLEAR_PLL_BYPASS_BMSK                                    0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_CLEAR_PLL_BYPASS_SHFT                                    0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_CLEAR_PLL_RESET_BMSK                                     0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_EXT_CLEAR_PLL_RESET_SHFT                                     0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_CLEAR_ADDR                                        (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00007220)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_CLEAR_RMSK                                              0x1f
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_CLEAR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_CLEAR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_CLEAR_PLL_FREEZE_BMSK                                   0x10
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_CLEAR_PLL_FREEZE_SHFT                                    0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_CLEAR_PLL_VOTE_BMSK                                      0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_CLEAR_PLL_VOTE_SHFT                                      0x3
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_CLEAR_PLL_OUTDIS_BMSK                                    0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_CLEAR_PLL_OUTDIS_SHFT                                    0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_CLEAR_PLL_BYPASS_BMSK                                    0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_CLEAR_PLL_BYPASS_SHFT                                    0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_CLEAR_PLL_RESET_BMSK                                     0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_PLL_CLEAR_PLL_RESET_SHFT                                     0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_CLEAR_ADDR                                   (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00007224)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_CLEAR_RMSK                                          0x7
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_CLEAR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_CLEAR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_CLEAR_WAKE_IRQ_BMSK                                 0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_CLEAR_WAKE_IRQ_SHFT                                 0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_CLEAR_RESTORE_BMSK                                  0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_CLEAR_RESTORE_SHFT                                  0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_CLEAR_SAVE_BMSK                                     0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_STATERET_CLEAR_SAVE_SHFT                                     0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_CLEAR_ADDR                                (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00007228)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_CLEAR_RMSK                                      0x3d
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_CLEAR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_CLEAR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_CLEAR_AXIM2_FIFO_ARESET_BMSK                    0x20
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_CLEAR_AXIM2_FIFO_ARESET_SHFT                     0x5
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_CLEAR_AXIM2_HALTREQ_BMSK                        0x10
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_CLEAR_AXIM2_HALTREQ_SHFT                         0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_CLEAR_AXIM_FIFO_ARESET_BMSK                      0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_CLEAR_AXIM_FIFO_ARESET_SHFT                      0x3
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_CLEAR_AXIM_HALTREQ_BMSK                          0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_CLEAR_AXIM_HALTREQ_SHFT                          0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_CLEAR_BUSM_HALTREQ_BMSK                          0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CTL_CLEAR_BUSM_HALTREQ_SHFT                          0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_ADDR                              (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x0000722c)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_RMSK                                    0xff
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_AXIM2_CLAMP_E_CLEAR_BMSK                0x80
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_AXIM2_CLAMP_E_CLEAR_SHFT                 0x7
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_AXIM2_CLAMP_E_SET_BMSK                  0x40
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_AXIM2_CLAMP_E_SET_SHFT                   0x6
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_AXIM2_CLAMP_L_CLEAR_BMSK                0x20
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_AXIM2_CLAMP_L_CLEAR_SHFT                 0x5
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_AXIM2_CLAMP_L_SET_BMSK                  0x10
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_AXIM2_CLAMP_L_SET_SHFT                   0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_AXIM_CLAMP_E_CLEAR_BMSK                  0x8
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_AXIM_CLAMP_E_CLEAR_SHFT                  0x3
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_AXIM_CLAMP_E_SET_BMSK                    0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_AXIM_CLAMP_E_SET_SHFT                    0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_AXIM_CLAMP_L_CLEAR_BMSK                  0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_AXIM_CLAMP_L_CLEAR_SHFT                  0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_AXIM_CLAMP_L_SET_BMSK                    0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLAMP_CLEAR_AXIM_CLAMP_L_SET_SHFT                    0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_CLEAR_ADDR                                (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00007230)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_CLEAR_RMSK                                       0x7
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_CLEAR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_CLEAR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_CLEAR_AXIM2_BMSK                                 0x4
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_CLEAR_AXIM2_SHFT                                 0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_CLEAR_AXIM_BMSK                                  0x2
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_CLEAR_AXIM_SHFT                                  0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_CLEAR_CORE_BMSK                                  0x1
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_ISOINTF_CLK_CLEAR_CORE_SHFT                                  0x0

#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L1S_CLEAR_ADDR                                    (LPASS_QDSP6V60SS_CSR_REG_BASE      + 0x00007240)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L1S_CLEAR_RMSK                                          0xff
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L1S_CLEAR_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L1S_CLEAR_ADDR,v)
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L1S_CLEAR_L1S_BMSK                                      0xff
#define HWIO_LPASS_QDSP6SS_SPMCTL_EN_MEM_L1S_CLEAR_L1S_SHFT                                       0x0

/*----------------------------------------------------------------------------
 * MODULE: LPASS_SCSR_REGS
 *--------------------------------------------------------------------------*/

#define LPASS_SCSR_REGS_REG_BASE                                                    (LPASS_BASE      + 0x00061000)

#define HWIO_LPASS_SCSR_TEST_BUS_SEL_CFG_ADDR                                       (LPASS_SCSR_REGS_REG_BASE      + 0x00000000)
#define HWIO_LPASS_SCSR_TEST_BUS_SEL_CFG_RMSK                                              0x1
#define HWIO_LPASS_SCSR_TEST_BUS_SEL_CFG_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_TEST_BUS_SEL_CFG_ADDR, HWIO_LPASS_SCSR_TEST_BUS_SEL_CFG_RMSK)
#define HWIO_LPASS_SCSR_TEST_BUS_SEL_CFG_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_TEST_BUS_SEL_CFG_ADDR, m)
#define HWIO_LPASS_SCSR_TEST_BUS_SEL_CFG_OUT(v)      \
        out_dword(HWIO_LPASS_SCSR_TEST_BUS_SEL_CFG_ADDR,v)
#define HWIO_LPASS_SCSR_TEST_BUS_SEL_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_TEST_BUS_SEL_CFG_ADDR,m,v,HWIO_LPASS_SCSR_TEST_BUS_SEL_CFG_IN)
#define HWIO_LPASS_SCSR_TEST_BUS_SEL_CFG_SCSR_TEST_BUS_SEL_BMSK                            0x1
#define HWIO_LPASS_SCSR_TEST_BUS_SEL_CFG_SCSR_TEST_BUS_SEL_SHFT                            0x0

#define HWIO_LPASS_SCSR_HW_VERSION_ADDR                                             (LPASS_SCSR_REGS_REG_BASE      + 0x00000004)
#define HWIO_LPASS_SCSR_HW_VERSION_RMSK                                             0xffffffff
#define HWIO_LPASS_SCSR_HW_VERSION_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_HW_VERSION_ADDR, HWIO_LPASS_SCSR_HW_VERSION_RMSK)
#define HWIO_LPASS_SCSR_HW_VERSION_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_HW_VERSION_ADDR, m)
#define HWIO_LPASS_SCSR_HW_VERSION_MAJOR_BMSK                                       0xf0000000
#define HWIO_LPASS_SCSR_HW_VERSION_MAJOR_SHFT                                             0x1c
#define HWIO_LPASS_SCSR_HW_VERSION_MINOR_BMSK                                        0xfff0000
#define HWIO_LPASS_SCSR_HW_VERSION_MINOR_SHFT                                             0x10
#define HWIO_LPASS_SCSR_HW_VERSION_STEP_BMSK                                            0xffff
#define HWIO_LPASS_SCSR_HW_VERSION_STEP_SHFT                                               0x0

#define HWIO_LPASS_SCSR_XO_CLK_GATE_ADDR                                            (LPASS_SCSR_REGS_REG_BASE      + 0x00000008)
#define HWIO_LPASS_SCSR_XO_CLK_GATE_RMSK                                                   0x1
#define HWIO_LPASS_SCSR_XO_CLK_GATE_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_XO_CLK_GATE_ADDR, HWIO_LPASS_SCSR_XO_CLK_GATE_RMSK)
#define HWIO_LPASS_SCSR_XO_CLK_GATE_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_XO_CLK_GATE_ADDR, m)
#define HWIO_LPASS_SCSR_XO_CLK_GATE_OUT(v)      \
        out_dword(HWIO_LPASS_SCSR_XO_CLK_GATE_ADDR,v)
#define HWIO_LPASS_SCSR_XO_CLK_GATE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_XO_CLK_GATE_ADDR,m,v,HWIO_LPASS_SCSR_XO_CLK_GATE_IN)
#define HWIO_LPASS_SCSR_XO_CLK_GATE_SCSR_XO_CLK_GATE_EN_BMSK                               0x1
#define HWIO_LPASS_SCSR_XO_CLK_GATE_SCSR_XO_CLK_GATE_EN_SHFT                               0x0

#define HWIO_LPASS_SCSR_I2C_CFG_ADDR                                                (LPASS_SCSR_REGS_REG_BASE      + 0x0000000c)
#define HWIO_LPASS_SCSR_I2C_CFG_RMSK                                                       0xf
#define HWIO_LPASS_SCSR_I2C_CFG_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_I2C_CFG_ADDR, HWIO_LPASS_SCSR_I2C_CFG_RMSK)
#define HWIO_LPASS_SCSR_I2C_CFG_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_I2C_CFG_ADDR, m)
#define HWIO_LPASS_SCSR_I2C_CFG_OUT(v)      \
        out_dword(HWIO_LPASS_SCSR_I2C_CFG_ADDR,v)
#define HWIO_LPASS_SCSR_I2C_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_I2C_CFG_ADDR,m,v,HWIO_LPASS_SCSR_I2C_CFG_IN)
#define HWIO_LPASS_SCSR_I2C_CFG_MODE_1_BMSK                                                0xc
#define HWIO_LPASS_SCSR_I2C_CFG_MODE_1_SHFT                                                0x2
#define HWIO_LPASS_SCSR_I2C_CFG_MODE_0_BMSK                                                0x3
#define HWIO_LPASS_SCSR_I2C_CFG_MODE_0_SHFT                                                0x0

#define HWIO_LPASS_SCSR_SW_ISLAND_MODE_DISABLE_ADDR                                 (LPASS_SCSR_REGS_REG_BASE      + 0x00000010)
#define HWIO_LPASS_SCSR_SW_ISLAND_MODE_DISABLE_RMSK                                        0x1
#define HWIO_LPASS_SCSR_SW_ISLAND_MODE_DISABLE_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_SW_ISLAND_MODE_DISABLE_ADDR, HWIO_LPASS_SCSR_SW_ISLAND_MODE_DISABLE_RMSK)
#define HWIO_LPASS_SCSR_SW_ISLAND_MODE_DISABLE_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_SW_ISLAND_MODE_DISABLE_ADDR, m)
#define HWIO_LPASS_SCSR_SW_ISLAND_MODE_DISABLE_DISABLE_BMSK                                0x1
#define HWIO_LPASS_SCSR_SW_ISLAND_MODE_DISABLE_DISABLE_SHFT                                0x0

#define HWIO_LPASS_SCSR_IEC_CTL_ADDR                                                (LPASS_SCSR_REGS_REG_BASE      + 0x00001000)
#define HWIO_LPASS_SCSR_IEC_CTL_RMSK                                                      0xff
#define HWIO_LPASS_SCSR_IEC_CTL_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_CTL_ADDR, HWIO_LPASS_SCSR_IEC_CTL_RMSK)
#define HWIO_LPASS_SCSR_IEC_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_CTL_ADDR, m)
#define HWIO_LPASS_SCSR_IEC_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_SCSR_IEC_CTL_ADDR,v)
#define HWIO_LPASS_SCSR_IEC_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_IEC_CTL_ADDR,m,v,HWIO_LPASS_SCSR_IEC_CTL_IN)
#define HWIO_LPASS_SCSR_IEC_CTL_ENTER_ISLAND_MODE_TRIG_BMSK                               0x80
#define HWIO_LPASS_SCSR_IEC_CTL_ENTER_ISLAND_MODE_TRIG_SHFT                                0x7
#define HWIO_LPASS_SCSR_IEC_CTL_BUS_ISO_ENTER_ISLAND_DIS_BMSK                             0x40
#define HWIO_LPASS_SCSR_IEC_CTL_BUS_ISO_ENTER_ISLAND_DIS_SHFT                              0x6
#define HWIO_LPASS_SCSR_IEC_CTL_L2_MISS_ISLAND_EXIT_EN_BMSK                               0x20
#define HWIO_LPASS_SCSR_IEC_CTL_L2_MISS_ISLAND_EXIT_EN_SHFT                                0x5
#define HWIO_LPASS_SCSR_IEC_CTL_ISO_AHB_MASTER_BYPASS_BMSK                                0x10
#define HWIO_LPASS_SCSR_IEC_CTL_ISO_AHB_MASTER_BYPASS_SHFT                                 0x4
#define HWIO_LPASS_SCSR_IEC_CTL_ISO_AHB_SLAVE_BYPASS_BMSK                                  0x8
#define HWIO_LPASS_SCSR_IEC_CTL_ISO_AHB_SLAVE_BYPASS_SHFT                                  0x3
#define HWIO_LPASS_SCSR_IEC_CTL_AHB_REQPEND_CLR_BMSK                                       0x4
#define HWIO_LPASS_SCSR_IEC_CTL_AHB_REQPEND_CLR_SHFT                                       0x2
#define HWIO_LPASS_SCSR_IEC_CTL_ENTER_ISLAND_MODE_IRQ_CLR_BMSK                             0x2
#define HWIO_LPASS_SCSR_IEC_CTL_ENTER_ISLAND_MODE_IRQ_CLR_SHFT                             0x1
#define HWIO_LPASS_SCSR_IEC_CTL_EXIT_ISLAND_MODE_TRIG_BMSK                                 0x1
#define HWIO_LPASS_SCSR_IEC_CTL_EXIT_ISLAND_MODE_TRIG_SHFT                                 0x0

#define HWIO_LPASS_SCSR_IEC_STAT_ADDR                                               (LPASS_SCSR_REGS_REG_BASE      + 0x00001004)
#define HWIO_LPASS_SCSR_IEC_STAT_RMSK                                                      0x1
#define HWIO_LPASS_SCSR_IEC_STAT_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_STAT_ADDR, HWIO_LPASS_SCSR_IEC_STAT_RMSK)
#define HWIO_LPASS_SCSR_IEC_STAT_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_STAT_ADDR, m)
#define HWIO_LPASS_SCSR_IEC_STAT_ISLAND_MODE_BMSK                                          0x1
#define HWIO_LPASS_SCSR_IEC_STAT_ISLAND_MODE_SHFT                                          0x0

#define HWIO_LPASS_SCSR_IEC_BSY_WAIT_ADDR                                           (LPASS_SCSR_REGS_REG_BASE      + 0x00001008)
#define HWIO_LPASS_SCSR_IEC_BSY_WAIT_RMSK                                                  0x3
#define HWIO_LPASS_SCSR_IEC_BSY_WAIT_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_BSY_WAIT_ADDR, HWIO_LPASS_SCSR_IEC_BSY_WAIT_RMSK)
#define HWIO_LPASS_SCSR_IEC_BSY_WAIT_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_BSY_WAIT_ADDR, m)
#define HWIO_LPASS_SCSR_IEC_BSY_WAIT_OUT(v)      \
        out_dword(HWIO_LPASS_SCSR_IEC_BSY_WAIT_ADDR,v)
#define HWIO_LPASS_SCSR_IEC_BSY_WAIT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_IEC_BSY_WAIT_ADDR,m,v,HWIO_LPASS_SCSR_IEC_BSY_WAIT_IN)
#define HWIO_LPASS_SCSR_IEC_BSY_WAIT_BUSY_WAIT_EN_BMSK                                     0x2
#define HWIO_LPASS_SCSR_IEC_BSY_WAIT_BUSY_WAIT_EN_SHFT                                     0x1
#define HWIO_LPASS_SCSR_IEC_BSY_WAIT_BUSY_WAIT_RST_BMSK                                    0x1
#define HWIO_LPASS_SCSR_IEC_BSY_WAIT_BUSY_WAIT_RST_SHFT                                    0x0

#define HWIO_LPASS_SCSR_IEC_SQCNTR_VAL0_ADDR                                        (LPASS_SCSR_REGS_REG_BASE      + 0x0000100c)
#define HWIO_LPASS_SCSR_IEC_SQCNTR_VAL0_RMSK                                        0xffffffff
#define HWIO_LPASS_SCSR_IEC_SQCNTR_VAL0_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_SQCNTR_VAL0_ADDR, HWIO_LPASS_SCSR_IEC_SQCNTR_VAL0_RMSK)
#define HWIO_LPASS_SCSR_IEC_SQCNTR_VAL0_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_SQCNTR_VAL0_ADDR, m)
#define HWIO_LPASS_SCSR_IEC_SQCNTR_VAL0_SQCNTR_VAL0_BMSK                            0xffffffff
#define HWIO_LPASS_SCSR_IEC_SQCNTR_VAL0_SQCNTR_VAL0_SHFT                                   0x0

#define HWIO_LPASS_SCSR_IEC_SQCNTR_VAL1_ADDR                                        (LPASS_SCSR_REGS_REG_BASE      + 0x00001010)
#define HWIO_LPASS_SCSR_IEC_SQCNTR_VAL1_RMSK                                          0xffffff
#define HWIO_LPASS_SCSR_IEC_SQCNTR_VAL1_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_SQCNTR_VAL1_ADDR, HWIO_LPASS_SCSR_IEC_SQCNTR_VAL1_RMSK)
#define HWIO_LPASS_SCSR_IEC_SQCNTR_VAL1_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_SQCNTR_VAL1_ADDR, m)
#define HWIO_LPASS_SCSR_IEC_SQCNTR_VAL1_SQCNTR_VAL1_BMSK                              0xffffff
#define HWIO_LPASS_SCSR_IEC_SQCNTR_VAL1_SQCNTR_VAL1_SHFT                                   0x0

#define HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL0_ADDR                                (LPASS_SCSR_REGS_REG_BASE      + 0x00001014)
#define HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL0_RMSK                                0xffffffff
#define HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL0_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL0_ADDR, HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL0_RMSK)
#define HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL0_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL0_ADDR, m)
#define HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL0_BUSY_WAIT_CNTR_VAL0_BMSK            0xffffffff
#define HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL0_BUSY_WAIT_CNTR_VAL0_SHFT                   0x0

#define HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL1_ADDR                                (LPASS_SCSR_REGS_REG_BASE      + 0x00001018)
#define HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL1_RMSK                                  0xffffff
#define HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL1_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL1_ADDR, HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL1_RMSK)
#define HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL1_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL1_ADDR, m)
#define HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL1_BUSY_WAIT_CNTR_VAL1_BMSK              0xffffff
#define HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL1_BUSY_WAIT_CNTR_VAL1_SHFT                   0x0

#define HWIO_LPASS_SCSR_IEC_HADDR_VAL0_ADDR                                         (LPASS_SCSR_REGS_REG_BASE      + 0x0000101c)
#define HWIO_LPASS_SCSR_IEC_HADDR_VAL0_RMSK                                         0xffffffff
#define HWIO_LPASS_SCSR_IEC_HADDR_VAL0_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_HADDR_VAL0_ADDR, HWIO_LPASS_SCSR_IEC_HADDR_VAL0_RMSK)
#define HWIO_LPASS_SCSR_IEC_HADDR_VAL0_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_HADDR_VAL0_ADDR, m)
#define HWIO_LPASS_SCSR_IEC_HADDR_VAL0_HADDR_VAL0_BMSK                              0xffffffff
#define HWIO_LPASS_SCSR_IEC_HADDR_VAL0_HADDR_VAL0_SHFT                                     0x0

#define HWIO_LPASS_SCSR_IEC_HADDR_VAL1_ADDR                                         (LPASS_SCSR_REGS_REG_BASE      + 0x00001020)
#define HWIO_LPASS_SCSR_IEC_HADDR_VAL1_RMSK                                                0xf
#define HWIO_LPASS_SCSR_IEC_HADDR_VAL1_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_HADDR_VAL1_ADDR, HWIO_LPASS_SCSR_IEC_HADDR_VAL1_RMSK)
#define HWIO_LPASS_SCSR_IEC_HADDR_VAL1_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_HADDR_VAL1_ADDR, m)
#define HWIO_LPASS_SCSR_IEC_HADDR_VAL1_HADDR_VAL1_BMSK                                     0xf
#define HWIO_LPASS_SCSR_IEC_HADDR_VAL1_HADDR_VAL1_SHFT                                     0x0

#define HWIO_LPASS_SCSR_IEC_HMID_VAL_ADDR                                           (LPASS_SCSR_REGS_REG_BASE      + 0x00001024)
#define HWIO_LPASS_SCSR_IEC_HMID_VAL_RMSK                                                 0xff
#define HWIO_LPASS_SCSR_IEC_HMID_VAL_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_HMID_VAL_ADDR, HWIO_LPASS_SCSR_IEC_HMID_VAL_RMSK)
#define HWIO_LPASS_SCSR_IEC_HMID_VAL_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_HMID_VAL_ADDR, m)
#define HWIO_LPASS_SCSR_IEC_HMID_VAL_SCSR_IEC_HMID_VAL_BMSK                               0xff
#define HWIO_LPASS_SCSR_IEC_HMID_VAL_SCSR_IEC_HMID_VAL_SHFT                                0x0

#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL0_ADDR                                      (LPASS_SCSR_REGS_REG_BASE      + 0x00001028)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL0_RMSK                                      0xffffffff
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL0_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL0_ADDR, HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL0_RMSK)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL0_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL0_ADDR, m)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL0_OUT(v)      \
        out_dword(HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL0_ADDR,v)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL0_ADDR,m,v,HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL0_IN)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL0_SCSR_HWEVENTS_SEL0_BMSK                   0xffffffff
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL0_SCSR_HWEVENTS_SEL0_SHFT                          0x0

#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL1_ADDR                                      (LPASS_SCSR_REGS_REG_BASE      + 0x0000102c)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL1_RMSK                                      0xffffffff
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL1_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL1_ADDR, HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL1_RMSK)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL1_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL1_ADDR, m)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL1_OUT(v)      \
        out_dword(HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL1_ADDR,v)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL1_ADDR,m,v,HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL1_IN)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL1_SCSR_HWEVENTS_SEL1_BMSK                   0xffffffff
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL1_SCSR_HWEVENTS_SEL1_SHFT                          0x0

#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL2_ADDR                                      (LPASS_SCSR_REGS_REG_BASE      + 0x00001030)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL2_RMSK                                      0xffffffff
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL2_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL2_ADDR, HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL2_RMSK)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL2_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL2_ADDR, m)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL2_OUT(v)      \
        out_dword(HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL2_ADDR,v)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL2_ADDR,m,v,HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL2_IN)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL2_SCSR_HWEVENTS_SEL2_BMSK                   0xffffffff
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL2_SCSR_HWEVENTS_SEL2_SHFT                          0x0

#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL3_ADDR                                      (LPASS_SCSR_REGS_REG_BASE      + 0x00001034)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL3_RMSK                                      0xffffffff
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL3_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL3_ADDR, HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL3_RMSK)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL3_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL3_ADDR, m)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL3_OUT(v)      \
        out_dword(HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL3_ADDR,v)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL3_ADDR,m,v,HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL3_IN)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL3_SCSR_HWEVENTS_SEL3_BMSK                   0xffffffff
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL3_SCSR_HWEVENTS_SEL3_SHFT                          0x0

#define HWIO_LPASS_SCSR_IEC_HWEVENTS_EN_ADDR                                        (LPASS_SCSR_REGS_REG_BASE      + 0x00001038)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_EN_RMSK                                        0xffffffff
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_EN_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_HWEVENTS_EN_ADDR, HWIO_LPASS_SCSR_IEC_HWEVENTS_EN_RMSK)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_EN_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_HWEVENTS_EN_ADDR, m)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_EN_OUT(v)      \
        out_dword(HWIO_LPASS_SCSR_IEC_HWEVENTS_EN_ADDR,v)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_IEC_HWEVENTS_EN_ADDR,m,v,HWIO_LPASS_SCSR_IEC_HWEVENTS_EN_IN)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_EN_HWEVENTS_EN_BMSK                            0xffffffff
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_EN_HWEVENTS_EN_SHFT                                   0x0

#define HWIO_LPASS_SCSR_DATA_BUS_CONFIG_ADDR                                        (LPASS_SCSR_REGS_REG_BASE      + 0x00002000)
#define HWIO_LPASS_SCSR_DATA_BUS_CONFIG_RMSK                                             0xfff
#define HWIO_LPASS_SCSR_DATA_BUS_CONFIG_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_DATA_BUS_CONFIG_ADDR, HWIO_LPASS_SCSR_DATA_BUS_CONFIG_RMSK)
#define HWIO_LPASS_SCSR_DATA_BUS_CONFIG_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_DATA_BUS_CONFIG_ADDR, m)
#define HWIO_LPASS_SCSR_DATA_BUS_CONFIG_OUT(v)      \
        out_dword(HWIO_LPASS_SCSR_DATA_BUS_CONFIG_ADDR,v)
#define HWIO_LPASS_SCSR_DATA_BUS_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_DATA_BUS_CONFIG_ADDR,m,v,HWIO_LPASS_SCSR_DATA_BUS_CONFIG_IN)
#define HWIO_LPASS_SCSR_DATA_BUS_CONFIG_AHBE_GLOBAL_EN_BMSK                              0x800
#define HWIO_LPASS_SCSR_DATA_BUS_CONFIG_AHBE_GLOBAL_EN_SHFT                                0xb
#define HWIO_LPASS_SCSR_DATA_BUS_CONFIG_AHBE_TIMEBASE_BMSK                               0x400
#define HWIO_LPASS_SCSR_DATA_BUS_CONFIG_AHBE_TIMEBASE_SHFT                                 0xa
#define HWIO_LPASS_SCSR_DATA_BUS_CONFIG_LOCK_EN_ARRAY_BMSK                               0x380
#define HWIO_LPASS_SCSR_DATA_BUS_CONFIG_LOCK_EN_ARRAY_SHFT                                 0x7
#define HWIO_LPASS_SCSR_DATA_BUS_CONFIG_PRIORITY_ARRAY_BMSK                               0x7e
#define HWIO_LPASS_SCSR_DATA_BUS_CONFIG_PRIORITY_ARRAY_SHFT                                0x1
#define HWIO_LPASS_SCSR_DATA_BUS_CONFIG_ARB_SCHEME_SEL_BMSK                                0x1
#define HWIO_LPASS_SCSR_DATA_BUS_CONFIG_ARB_SCHEME_SEL_SHFT                                0x0

#define HWIO_LPASS_SCSR_DATA_BUS_STATUS_ADDR                                        (LPASS_SCSR_REGS_REG_BASE      + 0x00002004)
#define HWIO_LPASS_SCSR_DATA_BUS_STATUS_RMSK                                               0x7
#define HWIO_LPASS_SCSR_DATA_BUS_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_DATA_BUS_STATUS_ADDR, HWIO_LPASS_SCSR_DATA_BUS_STATUS_RMSK)
#define HWIO_LPASS_SCSR_DATA_BUS_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_DATA_BUS_STATUS_ADDR, m)
#define HWIO_LPASS_SCSR_DATA_BUS_STATUS_AHBE_STATUS_BMSK                                   0x7
#define HWIO_LPASS_SCSR_DATA_BUS_STATUS_AHBE_STATUS_SHFT                                   0x0

#define HWIO_LPASS_SCSR_CFG_BUS_CONFIG_ADDR                                         (LPASS_SCSR_REGS_REG_BASE      + 0x00003000)
#define HWIO_LPASS_SCSR_CFG_BUS_CONFIG_RMSK                                              0xfff
#define HWIO_LPASS_SCSR_CFG_BUS_CONFIG_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_CFG_BUS_CONFIG_ADDR, HWIO_LPASS_SCSR_CFG_BUS_CONFIG_RMSK)
#define HWIO_LPASS_SCSR_CFG_BUS_CONFIG_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_CFG_BUS_CONFIG_ADDR, m)
#define HWIO_LPASS_SCSR_CFG_BUS_CONFIG_OUT(v)      \
        out_dword(HWIO_LPASS_SCSR_CFG_BUS_CONFIG_ADDR,v)
#define HWIO_LPASS_SCSR_CFG_BUS_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_CFG_BUS_CONFIG_ADDR,m,v,HWIO_LPASS_SCSR_CFG_BUS_CONFIG_IN)
#define HWIO_LPASS_SCSR_CFG_BUS_CONFIG_AHBE_GLOBAL_EN_BMSK                               0x800
#define HWIO_LPASS_SCSR_CFG_BUS_CONFIG_AHBE_GLOBAL_EN_SHFT                                 0xb
#define HWIO_LPASS_SCSR_CFG_BUS_CONFIG_AHBE_TIMEBASE_BMSK                                0x400
#define HWIO_LPASS_SCSR_CFG_BUS_CONFIG_AHBE_TIMEBASE_SHFT                                  0xa
#define HWIO_LPASS_SCSR_CFG_BUS_CONFIG_LOCK_EN_ARRAY_BMSK                                0x380
#define HWIO_LPASS_SCSR_CFG_BUS_CONFIG_LOCK_EN_ARRAY_SHFT                                  0x7
#define HWIO_LPASS_SCSR_CFG_BUS_CONFIG_PRIORITY_ARRAY_BMSK                                0x7e
#define HWIO_LPASS_SCSR_CFG_BUS_CONFIG_PRIORITY_ARRAY_SHFT                                 0x1
#define HWIO_LPASS_SCSR_CFG_BUS_CONFIG_ARB_SCHEME_SEL_BMSK                                 0x1
#define HWIO_LPASS_SCSR_CFG_BUS_CONFIG_ARB_SCHEME_SEL_SHFT                                 0x0

#define HWIO_LPASS_SCSR_CFG_BUS_STATUS_ADDR                                         (LPASS_SCSR_REGS_REG_BASE      + 0x00003004)
#define HWIO_LPASS_SCSR_CFG_BUS_STATUS_RMSK                                                0x7
#define HWIO_LPASS_SCSR_CFG_BUS_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_CFG_BUS_STATUS_ADDR, HWIO_LPASS_SCSR_CFG_BUS_STATUS_RMSK)
#define HWIO_LPASS_SCSR_CFG_BUS_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_CFG_BUS_STATUS_ADDR, m)
#define HWIO_LPASS_SCSR_CFG_BUS_STATUS_AHBE_STATUS_BMSK                                    0x7
#define HWIO_LPASS_SCSR_CFG_BUS_STATUS_AHBE_STATUS_SHFT                                    0x0

#define HWIO_LPASS_SCSR_TSGEN_PRELOAD_LO_ADDR                                       (LPASS_SCSR_REGS_REG_BASE      + 0x00004000)
#define HWIO_LPASS_SCSR_TSGEN_PRELOAD_LO_RMSK                                       0xffffffff
#define HWIO_LPASS_SCSR_TSGEN_PRELOAD_LO_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_TSGEN_PRELOAD_LO_ADDR, HWIO_LPASS_SCSR_TSGEN_PRELOAD_LO_RMSK)
#define HWIO_LPASS_SCSR_TSGEN_PRELOAD_LO_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_TSGEN_PRELOAD_LO_ADDR, m)
#define HWIO_LPASS_SCSR_TSGEN_PRELOAD_LO_OUT(v)      \
        out_dword(HWIO_LPASS_SCSR_TSGEN_PRELOAD_LO_ADDR,v)
#define HWIO_LPASS_SCSR_TSGEN_PRELOAD_LO_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_TSGEN_PRELOAD_LO_ADDR,m,v,HWIO_LPASS_SCSR_TSGEN_PRELOAD_LO_IN)
#define HWIO_LPASS_SCSR_TSGEN_PRELOAD_LO_TSGEN_PRELOAD_LO_BMSK                      0xffffffff
#define HWIO_LPASS_SCSR_TSGEN_PRELOAD_LO_TSGEN_PRELOAD_LO_SHFT                             0x0

#define HWIO_LPASS_SCSR_TSGEN_PRELOAD_HI_ADDR                                       (LPASS_SCSR_REGS_REG_BASE      + 0x00004004)
#define HWIO_LPASS_SCSR_TSGEN_PRELOAD_HI_RMSK                                       0xffffffff
#define HWIO_LPASS_SCSR_TSGEN_PRELOAD_HI_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_TSGEN_PRELOAD_HI_ADDR, HWIO_LPASS_SCSR_TSGEN_PRELOAD_HI_RMSK)
#define HWIO_LPASS_SCSR_TSGEN_PRELOAD_HI_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_TSGEN_PRELOAD_HI_ADDR, m)
#define HWIO_LPASS_SCSR_TSGEN_PRELOAD_HI_OUT(v)      \
        out_dword(HWIO_LPASS_SCSR_TSGEN_PRELOAD_HI_ADDR,v)
#define HWIO_LPASS_SCSR_TSGEN_PRELOAD_HI_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_TSGEN_PRELOAD_HI_ADDR,m,v,HWIO_LPASS_SCSR_TSGEN_PRELOAD_HI_IN)
#define HWIO_LPASS_SCSR_TSGEN_PRELOAD_HI_TSGEN_PRELOAD_HI_BMSK                      0xffffffff
#define HWIO_LPASS_SCSR_TSGEN_PRELOAD_HI_TSGEN_PRELOAD_HI_SHFT                             0x0

#define HWIO_LPASS_SCSR_TSGEN_CTR_LO_ADDR                                           (LPASS_SCSR_REGS_REG_BASE      + 0x00004008)
#define HWIO_LPASS_SCSR_TSGEN_CTR_LO_RMSK                                           0xffffffff
#define HWIO_LPASS_SCSR_TSGEN_CTR_LO_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_TSGEN_CTR_LO_ADDR, HWIO_LPASS_SCSR_TSGEN_CTR_LO_RMSK)
#define HWIO_LPASS_SCSR_TSGEN_CTR_LO_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_TSGEN_CTR_LO_ADDR, m)
#define HWIO_LPASS_SCSR_TSGEN_CTR_LO_TSGEN_CTR_LO_BMSK                              0xffffffff
#define HWIO_LPASS_SCSR_TSGEN_CTR_LO_TSGEN_CTR_LO_SHFT                                     0x0

#define HWIO_LPASS_SCSR_TSGEN_CTR_HI_ADDR                                           (LPASS_SCSR_REGS_REG_BASE      + 0x0000400c)
#define HWIO_LPASS_SCSR_TSGEN_CTR_HI_RMSK                                           0xffffffff
#define HWIO_LPASS_SCSR_TSGEN_CTR_HI_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_TSGEN_CTR_HI_ADDR, HWIO_LPASS_SCSR_TSGEN_CTR_HI_RMSK)
#define HWIO_LPASS_SCSR_TSGEN_CTR_HI_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_TSGEN_CTR_HI_ADDR, m)
#define HWIO_LPASS_SCSR_TSGEN_CTR_HI_TSGEN_CTR_HI_BMSK                              0xffffffff
#define HWIO_LPASS_SCSR_TSGEN_CTR_HI_TSGEN_CTR_HI_SHFT                                     0x0

#define HWIO_LPASS_SCSR_TSGEN_CTL_ADDR                                              (LPASS_SCSR_REGS_REG_BASE      + 0x00004010)
#define HWIO_LPASS_SCSR_TSGEN_CTL_RMSK                                                    0x13
#define HWIO_LPASS_SCSR_TSGEN_CTL_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_TSGEN_CTL_ADDR, HWIO_LPASS_SCSR_TSGEN_CTL_RMSK)
#define HWIO_LPASS_SCSR_TSGEN_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_TSGEN_CTL_ADDR, m)
#define HWIO_LPASS_SCSR_TSGEN_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_SCSR_TSGEN_CTL_ADDR,v)
#define HWIO_LPASS_SCSR_TSGEN_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_TSGEN_CTL_ADDR,m,v,HWIO_LPASS_SCSR_TSGEN_CTL_IN)
#define HWIO_LPASS_SCSR_TSGEN_CTL_TSGEN_LEGACY_MODE_BMSK                                  0x10
#define HWIO_LPASS_SCSR_TSGEN_CTL_TSGEN_LEGACY_MODE_SHFT                                   0x4
#define HWIO_LPASS_SCSR_TSGEN_CTL_TSGEN_PRELOAD_EN_BMSK                                    0x2
#define HWIO_LPASS_SCSR_TSGEN_CTL_TSGEN_PRELOAD_EN_SHFT                                    0x1
#define HWIO_LPASS_SCSR_TSGEN_CTL_TSGEN_DISABLE_CNT_BMSK                                   0x1
#define HWIO_LPASS_SCSR_TSGEN_CTL_TSGEN_DISABLE_CNT_SHFT                                   0x0

#define HWIO_LPASS_SCSR_ATB_LOW_POWER_HANDSHAKE_ADDR                                (LPASS_SCSR_REGS_REG_BASE      + 0x00004020)
#define HWIO_LPASS_SCSR_ATB_LOW_POWER_HANDSHAKE_RMSK                                       0x7
#define HWIO_LPASS_SCSR_ATB_LOW_POWER_HANDSHAKE_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_ATB_LOW_POWER_HANDSHAKE_ADDR, HWIO_LPASS_SCSR_ATB_LOW_POWER_HANDSHAKE_RMSK)
#define HWIO_LPASS_SCSR_ATB_LOW_POWER_HANDSHAKE_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_ATB_LOW_POWER_HANDSHAKE_ADDR, m)
#define HWIO_LPASS_SCSR_ATB_LOW_POWER_HANDSHAKE_OUT(v)      \
        out_dword(HWIO_LPASS_SCSR_ATB_LOW_POWER_HANDSHAKE_ADDR,v)
#define HWIO_LPASS_SCSR_ATB_LOW_POWER_HANDSHAKE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_ATB_LOW_POWER_HANDSHAKE_ADDR,m,v,HWIO_LPASS_SCSR_ATB_LOW_POWER_HANDSHAKE_IN)
#define HWIO_LPASS_SCSR_ATB_LOW_POWER_HANDSHAKE_REQUEST_BMSK                               0x4
#define HWIO_LPASS_SCSR_ATB_LOW_POWER_HANDSHAKE_REQUEST_SHFT                               0x2
#define HWIO_LPASS_SCSR_ATB_LOW_POWER_HANDSHAKE_ACTIVE_BMSK                                0x2
#define HWIO_LPASS_SCSR_ATB_LOW_POWER_HANDSHAKE_ACTIVE_SHFT                                0x1
#define HWIO_LPASS_SCSR_ATB_LOW_POWER_HANDSHAKE_ACK_BMSK                                   0x1
#define HWIO_LPASS_SCSR_ATB_LOW_POWER_HANDSHAKE_ACK_SHFT                                   0x0

#define HWIO_LPASS_SCSR_APB_LOW_POWER_HANDSHAKE_ADDR                                (LPASS_SCSR_REGS_REG_BASE      + 0x00004024)
#define HWIO_LPASS_SCSR_APB_LOW_POWER_HANDSHAKE_RMSK                                       0x7
#define HWIO_LPASS_SCSR_APB_LOW_POWER_HANDSHAKE_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_APB_LOW_POWER_HANDSHAKE_ADDR, HWIO_LPASS_SCSR_APB_LOW_POWER_HANDSHAKE_RMSK)
#define HWIO_LPASS_SCSR_APB_LOW_POWER_HANDSHAKE_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_APB_LOW_POWER_HANDSHAKE_ADDR, m)
#define HWIO_LPASS_SCSR_APB_LOW_POWER_HANDSHAKE_OUT(v)      \
        out_dword(HWIO_LPASS_SCSR_APB_LOW_POWER_HANDSHAKE_ADDR,v)
#define HWIO_LPASS_SCSR_APB_LOW_POWER_HANDSHAKE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_APB_LOW_POWER_HANDSHAKE_ADDR,m,v,HWIO_LPASS_SCSR_APB_LOW_POWER_HANDSHAKE_IN)
#define HWIO_LPASS_SCSR_APB_LOW_POWER_HANDSHAKE_REQUEST_BMSK                               0x4
#define HWIO_LPASS_SCSR_APB_LOW_POWER_HANDSHAKE_REQUEST_SHFT                               0x2
#define HWIO_LPASS_SCSR_APB_LOW_POWER_HANDSHAKE_ACTIVE_BMSK                                0x2
#define HWIO_LPASS_SCSR_APB_LOW_POWER_HANDSHAKE_ACTIVE_SHFT                                0x1
#define HWIO_LPASS_SCSR_APB_LOW_POWER_HANDSHAKE_ACK_BMSK                                   0x1
#define HWIO_LPASS_SCSR_APB_LOW_POWER_HANDSHAKE_ACK_SHFT                                   0x0

#define HWIO_LPASS_SCSR_TS_LOW_POWER_HANDSHAKE_ADDR                                 (LPASS_SCSR_REGS_REG_BASE      + 0x00004028)
#define HWIO_LPASS_SCSR_TS_LOW_POWER_HANDSHAKE_RMSK                                       0x37
#define HWIO_LPASS_SCSR_TS_LOW_POWER_HANDSHAKE_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_TS_LOW_POWER_HANDSHAKE_ADDR, HWIO_LPASS_SCSR_TS_LOW_POWER_HANDSHAKE_RMSK)
#define HWIO_LPASS_SCSR_TS_LOW_POWER_HANDSHAKE_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_TS_LOW_POWER_HANDSHAKE_ADDR, m)
#define HWIO_LPASS_SCSR_TS_LOW_POWER_HANDSHAKE_OUT(v)      \
        out_dword(HWIO_LPASS_SCSR_TS_LOW_POWER_HANDSHAKE_ADDR,v)
#define HWIO_LPASS_SCSR_TS_LOW_POWER_HANDSHAKE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_TS_LOW_POWER_HANDSHAKE_ADDR,m,v,HWIO_LPASS_SCSR_TS_LOW_POWER_HANDSHAKE_IN)
#define HWIO_LPASS_SCSR_TS_LOW_POWER_HANDSHAKE_TSGEN_ACTIVE_BMSK                          0x20
#define HWIO_LPASS_SCSR_TS_LOW_POWER_HANDSHAKE_TSGEN_ACTIVE_SHFT                           0x5
#define HWIO_LPASS_SCSR_TS_LOW_POWER_HANDSHAKE_TSGEN_ACK_BMSK                             0x10
#define HWIO_LPASS_SCSR_TS_LOW_POWER_HANDSHAKE_TSGEN_ACK_SHFT                              0x4
#define HWIO_LPASS_SCSR_TS_LOW_POWER_HANDSHAKE_REQUEST_BMSK                                0x4
#define HWIO_LPASS_SCSR_TS_LOW_POWER_HANDSHAKE_REQUEST_SHFT                                0x2
#define HWIO_LPASS_SCSR_TS_LOW_POWER_HANDSHAKE_ACTIVE_BMSK                                 0x2
#define HWIO_LPASS_SCSR_TS_LOW_POWER_HANDSHAKE_ACTIVE_SHFT                                 0x1
#define HWIO_LPASS_SCSR_TS_LOW_POWER_HANDSHAKE_ACK_BMSK                                    0x1
#define HWIO_LPASS_SCSR_TS_LOW_POWER_HANDSHAKE_ACK_SHFT                                    0x0

#define HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_ADDR                                         (LPASS_SCSR_REGS_REG_BASE      + 0x00004100)
#define HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_RMSK                                             0x330f
#define HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_ADDR, HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_RMSK)
#define HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_ADDR, m)
#define HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_OUT(v)      \
        out_dword(HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_ADDR,v)
#define HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_ADDR,m,v,HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_IN)
#define HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_APB_MAX_COUNT_BMSK                               0x3000
#define HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_APB_MAX_COUNT_SHFT                                  0xc
#define HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_TS_MAX_COUNT_BMSK                                 0x300
#define HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_TS_MAX_COUNT_SHFT                                   0x8
#define HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_TPDA_FREQREQ_EN_BMSK                                0x8
#define HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_TPDA_FREQREQ_EN_SHFT                                0x3
#define HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_SLP_CORR_EN_BMSK                                    0x4
#define HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_SLP_CORR_EN_SHFT                                    0x2
#define HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_SOURCE_BMSK                                         0x3
#define HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_SOURCE_SHFT                                         0x0

#define HWIO_LPASS_SCSR_WCSS_QDSS_TSTMP_VAL_LO_ADDR                                 (LPASS_SCSR_REGS_REG_BASE      + 0x00004104)
#define HWIO_LPASS_SCSR_WCSS_QDSS_TSTMP_VAL_LO_RMSK                                 0xffffffff
#define HWIO_LPASS_SCSR_WCSS_QDSS_TSTMP_VAL_LO_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_WCSS_QDSS_TSTMP_VAL_LO_ADDR, HWIO_LPASS_SCSR_WCSS_QDSS_TSTMP_VAL_LO_RMSK)
#define HWIO_LPASS_SCSR_WCSS_QDSS_TSTMP_VAL_LO_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_WCSS_QDSS_TSTMP_VAL_LO_ADDR, m)
#define HWIO_LPASS_SCSR_WCSS_QDSS_TSTMP_VAL_LO_TSTMP_VAL_31_0_BMSK                  0xffffffff
#define HWIO_LPASS_SCSR_WCSS_QDSS_TSTMP_VAL_LO_TSTMP_VAL_31_0_SHFT                         0x0

#define HWIO_LPASS_SCSR_WCSS_QDSS_TSTMP_VAL_HI_ADDR                                 (LPASS_SCSR_REGS_REG_BASE      + 0x00004108)
#define HWIO_LPASS_SCSR_WCSS_QDSS_TSTMP_VAL_HI_RMSK                                 0xffffffff
#define HWIO_LPASS_SCSR_WCSS_QDSS_TSTMP_VAL_HI_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_WCSS_QDSS_TSTMP_VAL_HI_ADDR, HWIO_LPASS_SCSR_WCSS_QDSS_TSTMP_VAL_HI_RMSK)
#define HWIO_LPASS_SCSR_WCSS_QDSS_TSTMP_VAL_HI_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_WCSS_QDSS_TSTMP_VAL_HI_ADDR, m)
#define HWIO_LPASS_SCSR_WCSS_QDSS_TSTMP_VAL_HI_TSTMP_VAL_63_32_BMSK                 0xffffffff
#define HWIO_LPASS_SCSR_WCSS_QDSS_TSTMP_VAL_HI_TSTMP_VAL_63_32_SHFT                        0x0

#define HWIO_LPASS_SCSR_WCSS_INT_TSTMP_VAL_LO_ADDR                                  (LPASS_SCSR_REGS_REG_BASE      + 0x0000410c)
#define HWIO_LPASS_SCSR_WCSS_INT_TSTMP_VAL_LO_RMSK                                  0xffffffff
#define HWIO_LPASS_SCSR_WCSS_INT_TSTMP_VAL_LO_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_WCSS_INT_TSTMP_VAL_LO_ADDR, HWIO_LPASS_SCSR_WCSS_INT_TSTMP_VAL_LO_RMSK)
#define HWIO_LPASS_SCSR_WCSS_INT_TSTMP_VAL_LO_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_WCSS_INT_TSTMP_VAL_LO_ADDR, m)
#define HWIO_LPASS_SCSR_WCSS_INT_TSTMP_VAL_LO_TSTMP_VAL_31_0_BMSK                   0xffffffff
#define HWIO_LPASS_SCSR_WCSS_INT_TSTMP_VAL_LO_TSTMP_VAL_31_0_SHFT                          0x0

#define HWIO_LPASS_SCSR_WCSS_INT_TSTMP_VAL_HI_ADDR                                  (LPASS_SCSR_REGS_REG_BASE      + 0x00004110)
#define HWIO_LPASS_SCSR_WCSS_INT_TSTMP_VAL_HI_RMSK                                  0xffffffff
#define HWIO_LPASS_SCSR_WCSS_INT_TSTMP_VAL_HI_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_WCSS_INT_TSTMP_VAL_HI_ADDR, HWIO_LPASS_SCSR_WCSS_INT_TSTMP_VAL_HI_RMSK)
#define HWIO_LPASS_SCSR_WCSS_INT_TSTMP_VAL_HI_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_WCSS_INT_TSTMP_VAL_HI_ADDR, m)
#define HWIO_LPASS_SCSR_WCSS_INT_TSTMP_VAL_HI_TSTMP_VAL_63_32_BMSK                  0xffffffff
#define HWIO_LPASS_SCSR_WCSS_INT_TSTMP_VAL_HI_TSTMP_VAL_63_32_SHFT                         0x0

#define HWIO_LPASS_SCSR_WCSS_CXO_FREQ_ADDR                                          (LPASS_SCSR_REGS_REG_BASE      + 0x00004114)
#define HWIO_LPASS_SCSR_WCSS_CXO_FREQ_RMSK                                           0x3ffffff
#define HWIO_LPASS_SCSR_WCSS_CXO_FREQ_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_WCSS_CXO_FREQ_ADDR, HWIO_LPASS_SCSR_WCSS_CXO_FREQ_RMSK)
#define HWIO_LPASS_SCSR_WCSS_CXO_FREQ_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_WCSS_CXO_FREQ_ADDR, m)
#define HWIO_LPASS_SCSR_WCSS_CXO_FREQ_OUT(v)      \
        out_dword(HWIO_LPASS_SCSR_WCSS_CXO_FREQ_ADDR,v)
#define HWIO_LPASS_SCSR_WCSS_CXO_FREQ_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_WCSS_CXO_FREQ_ADDR,m,v,HWIO_LPASS_SCSR_WCSS_CXO_FREQ_IN)
#define HWIO_LPASS_SCSR_WCSS_CXO_FREQ_FREQ_BMSK                                      0x3ffffff
#define HWIO_LPASS_SCSR_WCSS_CXO_FREQ_FREQ_SHFT                                            0x0

#define HWIO_LPASS_SCSR_WCSS_CXO_FREQ_IN_KHZ_ADDR                                   (LPASS_SCSR_REGS_REG_BASE      + 0x00004118)
#define HWIO_LPASS_SCSR_WCSS_CXO_FREQ_IN_KHZ_RMSK                                       0xffff
#define HWIO_LPASS_SCSR_WCSS_CXO_FREQ_IN_KHZ_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_WCSS_CXO_FREQ_IN_KHZ_ADDR, HWIO_LPASS_SCSR_WCSS_CXO_FREQ_IN_KHZ_RMSK)
#define HWIO_LPASS_SCSR_WCSS_CXO_FREQ_IN_KHZ_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_WCSS_CXO_FREQ_IN_KHZ_ADDR, m)
#define HWIO_LPASS_SCSR_WCSS_CXO_FREQ_IN_KHZ_OUT(v)      \
        out_dword(HWIO_LPASS_SCSR_WCSS_CXO_FREQ_IN_KHZ_ADDR,v)
#define HWIO_LPASS_SCSR_WCSS_CXO_FREQ_IN_KHZ_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_WCSS_CXO_FREQ_IN_KHZ_ADDR,m,v,HWIO_LPASS_SCSR_WCSS_CXO_FREQ_IN_KHZ_IN)
#define HWIO_LPASS_SCSR_WCSS_CXO_FREQ_IN_KHZ_FREQ_BMSK                                  0xffff
#define HWIO_LPASS_SCSR_WCSS_CXO_FREQ_IN_KHZ_FREQ_SHFT                                     0x0

#define HWIO_LPASS_SCSR_WCSS_CLK_INFO_ADDR                                          (LPASS_SCSR_REGS_REG_BASE      + 0x0000411c)
#define HWIO_LPASS_SCSR_WCSS_CLK_INFO_RMSK                                             0x331f1
#define HWIO_LPASS_SCSR_WCSS_CLK_INFO_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_WCSS_CLK_INFO_ADDR, HWIO_LPASS_SCSR_WCSS_CLK_INFO_RMSK)
#define HWIO_LPASS_SCSR_WCSS_CLK_INFO_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_WCSS_CLK_INFO_ADDR, m)
#define HWIO_LPASS_SCSR_WCSS_CLK_INFO_TSTMP_DIV_BMSK                                   0x30000
#define HWIO_LPASS_SCSR_WCSS_CLK_INFO_TSTMP_DIV_SHFT                                      0x10
#define HWIO_LPASS_SCSR_WCSS_CLK_INFO_APB_DIV_BMSK                                      0x3000
#define HWIO_LPASS_SCSR_WCSS_CLK_INFO_APB_DIV_SHFT                                         0xc
#define HWIO_LPASS_SCSR_WCSS_CLK_INFO_ATB_DIV_BMSK                                       0x1f0
#define HWIO_LPASS_SCSR_WCSS_CLK_INFO_ATB_DIV_SHFT                                         0x4
#define HWIO_LPASS_SCSR_WCSS_CLK_INFO_SRC_BMSK                                             0x1
#define HWIO_LPASS_SCSR_WCSS_CLK_INFO_SRC_SHFT                                             0x0

#define HWIO_LPASS_SCSR_WCSS_SPARE_ADDR                                             (LPASS_SCSR_REGS_REG_BASE      + 0x00004120)
#define HWIO_LPASS_SCSR_WCSS_SPARE_RMSK                                             0xffffffff
#define HWIO_LPASS_SCSR_WCSS_SPARE_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_WCSS_SPARE_ADDR, HWIO_LPASS_SCSR_WCSS_SPARE_RMSK)
#define HWIO_LPASS_SCSR_WCSS_SPARE_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_WCSS_SPARE_ADDR, m)
#define HWIO_LPASS_SCSR_WCSS_SPARE_OUT(v)      \
        out_dword(HWIO_LPASS_SCSR_WCSS_SPARE_ADDR,v)
#define HWIO_LPASS_SCSR_WCSS_SPARE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_WCSS_SPARE_ADDR,m,v,HWIO_LPASS_SCSR_WCSS_SPARE_IN)
#define HWIO_LPASS_SCSR_WCSS_SPARE_SPARE_BMSK                                       0xffffffff
#define HWIO_LPASS_SCSR_WCSS_SPARE_SPARE_SHFT                                              0x0

#define HWIO_LPASS_SCSR_HM_TESTBUS_SEL_ADDR                                         (LPASS_SCSR_REGS_REG_BASE      + 0x00005000)
#define HWIO_LPASS_SCSR_HM_TESTBUS_SEL_RMSK                                             0xffff
#define HWIO_LPASS_SCSR_HM_TESTBUS_SEL_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_HM_TESTBUS_SEL_ADDR, HWIO_LPASS_SCSR_HM_TESTBUS_SEL_RMSK)
#define HWIO_LPASS_SCSR_HM_TESTBUS_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_HM_TESTBUS_SEL_ADDR, m)
#define HWIO_LPASS_SCSR_HM_TESTBUS_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_SCSR_HM_TESTBUS_SEL_ADDR,v)
#define HWIO_LPASS_SCSR_HM_TESTBUS_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_HM_TESTBUS_SEL_ADDR,m,v,HWIO_LPASS_SCSR_HM_TESTBUS_SEL_IN)
#define HWIO_LPASS_SCSR_HM_TESTBUS_SEL_I_TESTBUS_SEL_BMSK                               0xffff
#define HWIO_LPASS_SCSR_HM_TESTBUS_SEL_I_TESTBUS_SEL_SHFT                                  0x0

#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_ADDR                          (LPASS_SCSR_REGS_REG_BASE      + 0x00006000)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_RMSK                          0xffffffff
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_ADDR, HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_RMSK)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_ADDR, m)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_OUT(v)      \
        out_dword(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_ADDR,v)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_ADDR,m,v,HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_IN)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_RFU_BMSK                      0xfffffffc
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_RFU_SHFT                             0x2
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_TIMESTAMPENABLE_BMSK                 0x2
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_TIMESTAMPENABLE_SHFT                 0x1
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_CAPTURE_BMSK                         0x1
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_CAPTURE_SHFT                         0x0

#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_AOTIMEVAL0_ADDR                             (LPASS_SCSR_REGS_REG_BASE      + 0x00006004)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_AOTIMEVAL0_RMSK                             0xffffffff
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_AOTIMEVAL0_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_AOTIMEVAL0_ADDR, HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_AOTIMEVAL0_RMSK)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_AOTIMEVAL0_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_AOTIMEVAL0_ADDR, m)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_AOTIMEVAL0_TIMEVAL_BMSK                     0xffffffff
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_AOTIMEVAL0_TIMEVAL_SHFT                            0x0

#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_AOTIMEVAL1_ADDR                             (LPASS_SCSR_REGS_REG_BASE      + 0x00006008)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_AOTIMEVAL1_RMSK                             0xffffffff
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_AOTIMEVAL1_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_AOTIMEVAL1_ADDR, HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_AOTIMEVAL1_RMSK)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_AOTIMEVAL1_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_AOTIMEVAL1_ADDR, m)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_AOTIMEVAL1_TIMEVAL_BMSK                     0xffffffff
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_AOTIMEVAL1_TIMEVAL_SHFT                            0x0

#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_ADDR                           (LPASS_SCSR_REGS_REG_BASE      + 0x0000600c)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_RMSK                           0xffffffff
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_ADDR, HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_RMSK)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_ADDR, m)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_TIMEVAL_BMSK                   0xffffffff
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_TIMEVAL_SHFT                          0x0

#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_ADDR                           (LPASS_SCSR_REGS_REG_BASE      + 0x00006010)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_RMSK                           0xffffffff
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_ADDR, HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_RMSK)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_ADDR, m)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_TIMEVAL_BMSK                   0xffffffff
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_TIMEVAL_SHFT                          0x0

#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_ADDR                          (LPASS_SCSR_REGS_REG_BASE      + 0x00006014)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_RMSK                          0xffffffff
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_ADDR, HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_RMSK)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_ADDR, m)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_OUT(v)      \
        out_dword(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_ADDR,v)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_ADDR,m,v,HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_IN)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_TIMELOAD_BMSK                 0xffffffff
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_TIMELOAD_SHFT                        0x0

#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_ADDR                          (LPASS_SCSR_REGS_REG_BASE      + 0x00006018)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_RMSK                          0xffffffff
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_ADDR, HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_RMSK)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_ADDR, m)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_OUT(v)      \
        out_dword(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_ADDR,v)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_ADDR,m,v,HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_IN)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_TIMELOAD_BMSK                 0xffffffff
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_TIMELOAD_SHFT                        0x0

#define HWIO_LPASS_SCSR_WAKEUP_PRIMARY_IE_ADDR                                      (LPASS_SCSR_REGS_REG_BASE      + 0x00007000)
#define HWIO_LPASS_SCSR_WAKEUP_PRIMARY_IE_RMSK                                           0x1ff
#define HWIO_LPASS_SCSR_WAKEUP_PRIMARY_IE_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_WAKEUP_PRIMARY_IE_ADDR, HWIO_LPASS_SCSR_WAKEUP_PRIMARY_IE_RMSK)
#define HWIO_LPASS_SCSR_WAKEUP_PRIMARY_IE_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_WAKEUP_PRIMARY_IE_ADDR, m)
#define HWIO_LPASS_SCSR_WAKEUP_PRIMARY_IE_OUT(v)      \
        out_dword(HWIO_LPASS_SCSR_WAKEUP_PRIMARY_IE_ADDR,v)
#define HWIO_LPASS_SCSR_WAKEUP_PRIMARY_IE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_WAKEUP_PRIMARY_IE_ADDR,m,v,HWIO_LPASS_SCSR_WAKEUP_PRIMARY_IE_IN)
#define HWIO_LPASS_SCSR_WAKEUP_PRIMARY_IE_WAKEUP_IE_BMSK                                 0x1ff
#define HWIO_LPASS_SCSR_WAKEUP_PRIMARY_IE_WAKEUP_IE_SHFT                                   0x0

#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_ADDR                                (LPASS_SCSR_REGS_REG_BASE      + 0x00008000)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_RMSK                                0xfffffffc
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_ADDR, HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_RMSK)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_ADDR, m)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_OUT(v)      \
        out_dword(HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_ADDR,v)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_ADDR,m,v,HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_IN)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_THRESHOLD_SLOPE_BMSK                0xff000000
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_THRESHOLD_SLOPE_SHFT                      0x18
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_THRESHOLD_MAX_BMSK                    0xff0000
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_THRESHOLD_MAX_SHFT                        0x10
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_THRESHOLD_MIN_BMSK                      0xff00
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_THRESHOLD_MIN_SHFT                         0x8
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_CAPTURE_DELAY_BMSK                        0xf0
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_CAPTURE_DELAY_SHFT                         0x4
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_TRIG_POS_BMSK                              0xc
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_TRIG_POS_SHFT                              0x2

#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_ADDR                                (LPASS_SCSR_REGS_REG_BASE      + 0x00008004)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_RMSK                                0x80fffbff
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_ADDR, HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_RMSK)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_ADDR, m)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_OUT(v)      \
        out_dword(HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_ADDR,v)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_ADDR,m,v,HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_IN)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_VS_CSR_QSS_MUX_SEL_BMSK             0x80000000
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_VS_CSR_QSS_MUX_SEL_SHFT                   0x1f
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_FIFO_RD_ADDRESS_BMSK                  0xfc0000
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_FIFO_RD_ADDRESS_SHFT                      0x12
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_ALARM_SLOPE_NEG_EN_BMSK                0x20000
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_ALARM_SLOPE_NEG_EN_SHFT                   0x11
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_ALARM_SLOPE_POS_EN_BMSK                0x10000
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_ALARM_SLOPE_POS_EN_SHFT                   0x10
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_ALARM_MIN_EN_BMSK                       0x8000
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_ALARM_MIN_EN_SHFT                          0xf
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_ALARM_MAX_EN_BMSK                       0x4000
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_ALARM_MAX_EN_SHFT                          0xe
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_POWER_EN_BMSK                           0x2000
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_POWER_EN_SHFT                              0xd
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_FUNC_EN_BMSK                            0x1000
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_FUNC_EN_SHFT                               0xc
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_CLEAR_BMSK                               0x800
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_CLEAR_SHFT                                 0xb
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_HW_CAPTURE_EN_BMSK                       0x200
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_HW_CAPTURE_EN_SHFT                         0x9
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_SW_CAPTURE_BMSK                          0x100
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_SW_CAPTURE_SHFT                            0x8
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_TRIG_SEL_BMSK                             0xe0
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_TRIG_SEL_SHFT                              0x5
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_MODE_SEL_BMSK                             0x10
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_MODE_SEL_SHFT                              0x4
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_VCO_FILTER_EN_BMSK                         0x8
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_VCO_FILTER_EN_SHFT                         0x3
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_SLOPE_DELTA_CYC_BMSK                       0x7
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_SLOPE_DELTA_CYC_SHFT                       0x0

#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_SUMMARY_ADDR                                 (LPASS_SCSR_REGS_REG_BASE      + 0x00008008)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_SUMMARY_RMSK                                    0x3ffff
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_SUMMARY_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_VSENSE_SENSOR0_SUMMARY_ADDR, HWIO_LPASS_SCSR_VSENSE_SENSOR0_SUMMARY_RMSK)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_SUMMARY_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_VSENSE_SENSOR0_SUMMARY_ADDR, m)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_SUMMARY_FIFO_DATA_BMSK                          0x3fc00
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_SUMMARY_FIFO_DATA_SHFT                              0xa
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_SUMMARY_FSM_STATE_BMSK                            0x3c0
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_SUMMARY_FSM_STATE_SHFT                              0x6
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_SUMMARY_FIFO_COMPLETE_BMSK                         0x20
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_SUMMARY_FIFO_COMPLETE_SHFT                          0x5
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_SUMMARY_FIFO_ACTIVE_BMSK                           0x10
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_SUMMARY_FIFO_ACTIVE_SHFT                            0x4
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_SUMMARY_ALARM_MAX_BMSK                              0x8
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_SUMMARY_ALARM_MAX_SHFT                              0x3
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_SUMMARY_ALARM_MIN_BMSK                              0x4
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_SUMMARY_ALARM_MIN_SHFT                              0x2
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_SUMMARY_ALARM_SLOPE_NEG_BMSK                        0x2
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_SUMMARY_ALARM_SLOPE_NEG_SHFT                        0x1
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_SUMMARY_ALARM_SLOPE_POS_BMSK                        0x1
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_SUMMARY_ALARM_SLOPE_POS_SHFT                        0x0

#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_ADDR                                (LPASS_SCSR_REGS_REG_BASE      + 0x0000800c)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_RMSK                                0xfffffffc
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_ADDR, HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_RMSK)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_ADDR, m)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_OUT(v)      \
        out_dword(HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_ADDR,v)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_ADDR,m,v,HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_IN)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_THRESHOLD_SLOPE_BMSK                0xff000000
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_THRESHOLD_SLOPE_SHFT                      0x18
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_THRESHOLD_MAX_BMSK                    0xff0000
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_THRESHOLD_MAX_SHFT                        0x10
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_THRESHOLD_MIN_BMSK                      0xff00
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_THRESHOLD_MIN_SHFT                         0x8
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_CAPTURE_DELAY_BMSK                        0xf0
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_CAPTURE_DELAY_SHFT                         0x4
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_TRIG_POS_BMSK                              0xc
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_TRIG_POS_SHFT                              0x2

#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_ADDR                                (LPASS_SCSR_REGS_REG_BASE      + 0x00008010)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_RMSK                                0x80fffbff
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_ADDR, HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_RMSK)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_ADDR, m)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_OUT(v)      \
        out_dword(HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_ADDR,v)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_ADDR,m,v,HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_IN)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_VS_CSR_QSS_MUX_SEL_BMSK             0x80000000
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_VS_CSR_QSS_MUX_SEL_SHFT                   0x1f
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_FIFO_RD_ADDRESS_BMSK                  0xfc0000
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_FIFO_RD_ADDRESS_SHFT                      0x12
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_ALARM_SLOPE_NEG_EN_BMSK                0x20000
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_ALARM_SLOPE_NEG_EN_SHFT                   0x11
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_ALARM_SLOPE_POS_EN_BMSK                0x10000
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_ALARM_SLOPE_POS_EN_SHFT                   0x10
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_ALARM_MIN_EN_BMSK                       0x8000
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_ALARM_MIN_EN_SHFT                          0xf
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_ALARM_MAX_EN_BMSK                       0x4000
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_ALARM_MAX_EN_SHFT                          0xe
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_POWER_EN_BMSK                           0x2000
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_POWER_EN_SHFT                              0xd
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_FUNC_EN_BMSK                            0x1000
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_FUNC_EN_SHFT                               0xc
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_CLEAR_BMSK                               0x800
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_CLEAR_SHFT                                 0xb
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_HW_CAPTURE_EN_BMSK                       0x200
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_HW_CAPTURE_EN_SHFT                         0x9
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_SW_CAPTURE_BMSK                          0x100
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_SW_CAPTURE_SHFT                            0x8
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_TRIG_SEL_BMSK                             0xe0
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_TRIG_SEL_SHFT                              0x5
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_MODE_SEL_BMSK                             0x10
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_MODE_SEL_SHFT                              0x4
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_VCO_FILTER_EN_BMSK                         0x8
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_VCO_FILTER_EN_SHFT                         0x3
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_SLOPE_DELTA_CYC_BMSK                       0x7
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_SLOPE_DELTA_CYC_SHFT                       0x0

#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_SUMMARY_ADDR                                 (LPASS_SCSR_REGS_REG_BASE      + 0x00008014)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_SUMMARY_RMSK                                    0x3ffff
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_SUMMARY_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_VSENSE_SENSOR1_SUMMARY_ADDR, HWIO_LPASS_SCSR_VSENSE_SENSOR1_SUMMARY_RMSK)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_SUMMARY_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_VSENSE_SENSOR1_SUMMARY_ADDR, m)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_SUMMARY_FIFO_DATA_BMSK                          0x3fc00
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_SUMMARY_FIFO_DATA_SHFT                              0xa
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_SUMMARY_FSM_STATE_BMSK                            0x3c0
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_SUMMARY_FSM_STATE_SHFT                              0x6
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_SUMMARY_FIFO_COMPLETE_BMSK                         0x20
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_SUMMARY_FIFO_COMPLETE_SHFT                          0x5
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_SUMMARY_FIFO_ACTIVE_BMSK                           0x10
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_SUMMARY_FIFO_ACTIVE_SHFT                            0x4
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_SUMMARY_ALARM_MAX_BMSK                              0x8
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_SUMMARY_ALARM_MAX_SHFT                              0x3
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_SUMMARY_ALARM_MIN_BMSK                              0x4
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_SUMMARY_ALARM_MIN_SHFT                              0x2
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_SUMMARY_ALARM_SLOPE_NEG_BMSK                        0x2
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_SUMMARY_ALARM_SLOPE_NEG_SHFT                        0x1
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_SUMMARY_ALARM_SLOPE_POS_BMSK                        0x1
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_SUMMARY_ALARM_SLOPE_POS_SHFT                        0x0

#define HWIO_LPASS_SCSR_WAKEUP_SECONDARY_IE_ADDR                                    (LPASS_SCSR_REGS_REG_BASE      + 0x00009000)
#define HWIO_LPASS_SCSR_WAKEUP_SECONDARY_IE_RMSK                                         0x1ff
#define HWIO_LPASS_SCSR_WAKEUP_SECONDARY_IE_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_WAKEUP_SECONDARY_IE_ADDR, HWIO_LPASS_SCSR_WAKEUP_SECONDARY_IE_RMSK)
#define HWIO_LPASS_SCSR_WAKEUP_SECONDARY_IE_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_WAKEUP_SECONDARY_IE_ADDR, m)
#define HWIO_LPASS_SCSR_WAKEUP_SECONDARY_IE_OUT(v)      \
        out_dword(HWIO_LPASS_SCSR_WAKEUP_SECONDARY_IE_ADDR,v)
#define HWIO_LPASS_SCSR_WAKEUP_SECONDARY_IE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_WAKEUP_SECONDARY_IE_ADDR,m,v,HWIO_LPASS_SCSR_WAKEUP_SECONDARY_IE_IN)
#define HWIO_LPASS_SCSR_WAKEUP_SECONDARY_IE_WAKEUP_IE_BMSK                               0x1ff
#define HWIO_LPASS_SCSR_WAKEUP_SECONDARY_IE_WAKEUP_IE_SHFT                                 0x0

#define HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_SEL_ADDR                                     (LPASS_SCSR_REGS_REG_BASE      + 0x0000a000)
#define HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_SEL_RMSK                                            0x1
#define HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_SEL_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_SEL_ADDR, HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_SEL_RMSK)
#define HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_SEL_ADDR, m)
#define HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_SEL_ADDR,v)
#define HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_SEL_ADDR,m,v,HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_SEL_IN)
#define HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_SEL_SEL_BMSK                                        0x1
#define HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_SEL_SEL_SHFT                                        0x0

#define HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_ADDR_ADDR                                    (LPASS_SCSR_REGS_REG_BASE      + 0x0000a004)
#define HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_ADDR_RMSK                                     0xfffffff
#define HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_ADDR_IN          \
        in_dword_masked(HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_ADDR_ADDR, HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_ADDR_RMSK)
#define HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_ADDR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_ADDR_ADDR, m)
#define HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_ADDR_OUT(v)      \
        out_dword(HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_ADDR_ADDR,v)
#define HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_ADDR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_ADDR_ADDR,m,v,HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_ADDR_IN)
#define HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_ADDR_ADDR_BMSK                                0xffffff0
#define HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_ADDR_ADDR_SHFT                                      0x4
#define HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_ADDR_RSVD_BIT3_0_BMSK                               0xf
#define HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_ADDR_RSVD_BIT3_0_SHFT                               0x0

/*----------------------------------------------------------------------------
 * MODULE: LPASS_CC
 *--------------------------------------------------------------------------*/

#define LPASS_CC_REG_BASE                                                                                             (LPASS_BASE      + 0x00000000)

#define HWIO_LPASS_LPAAUDIO_PLL_MODE_ADDR                                                                             (LPASS_CC_REG_BASE      + 0x00000000)
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
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_ACK_LATCH_BMSK                                                               0x20000000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_ACK_LATCH_SHFT                                                                     0x1d
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_RESERVE_BITS28_24_BMSK                                                           0x1f000000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_RESERVE_BITS28_24_SHFT                                                                 0x18
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_BMSK                                                    0x800000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_SHFT                                                        0x17
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_UPDATE_BMSK                                                                    0x400000
#define HWIO_LPASS_LPAAUDIO_PLL_MODE_PLL_UPDATE_SHFT                                                                        0x16
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

#define HWIO_LPASS_LPAAUDIO_PLL_L_VAL_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00000004)
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

#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_ADDR                                                                        (LPASS_CC_REG_BASE      + 0x00000008)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_RMSK                                                                        0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_PLL_ALPHA_31_0_BMSK                                                         0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_PLL_ALPHA_31_0_SHFT                                                                0x0

#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_ADDR                                                                      (LPASS_CC_REG_BASE      + 0x0000000c)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_RMSK                                                                      0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_ADDR, HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_RESERVE_BITS_31_8_BMSK                                                    0xffffff00
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_RESERVE_BITS_31_8_SHFT                                                           0x8
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_PLL_ALPHA_39_32_BMSK                                                            0xff
#define HWIO_LPASS_LPAAUDIO_PLL_ALPHA_VAL_U_PLL_ALPHA_39_32_SHFT                                                             0x0

#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00000010)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RMSK                                                                         0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS31_25_BMSK                                                       0xfe000000
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS31_25_SHFT                                                             0x19
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ALPHA_EN_BMSK                                                                 0x1000000
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_ALPHA_EN_SHFT                                                                      0x18
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS23_14_BMSK                                                         0xffc000
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS23_14_SHFT                                                              0xe
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_INCLK_SEL_BMSK                                                                   0x3000
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_INCLK_SEL_SHFT                                                                      0xc
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS11_10_BMSK                                                            0xc00
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_RESERVE_BITS11_10_SHFT                                                              0xa
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_POSTDIV_CTL_BMSK                                                                  0x300
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_POSTDIV_CTL_SHFT                                                                    0x8
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_OUTPUT_INV_BMSK                                                                    0x80
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_OUTPUT_INV_SHFT                                                                     0x7
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

#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_ADDR                                                                       (LPASS_CC_REG_BASE      + 0x00000014)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_RMSK                                                                       0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_ADDR, HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_RESERVE_BITS31_0_BMSK                                                      0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_USER_CTL_U_RESERVE_BITS31_0_SHFT                                                             0x0

#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_ADDR                                                                       (LPASS_CC_REG_BASE      + 0x00000018)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_RMSK                                                                       0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_RESERVE_BITS31_18_BMSK                                                     0xfffc0000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_RESERVE_BITS31_18_SHFT                                                           0x12
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_DITHER_SEL_BMSK                                                               0x30000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_DITHER_SEL_SHFT                                                                  0x10
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_CORR_EN_BMSK                                                                   0x8000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_CORR_EN_SHFT                                                                      0xf
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_RVSIG_DEL_BMSK                                                                 0x6000
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_RVSIG_DEL_SHFT                                                                    0xd
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_PFD_DZSEL_BMSK                                                                 0x1800
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_PFD_DZSEL_SHFT                                                                    0xb
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_FORCE_ISEED_BMSK                                                                0x400
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_FORCE_ISEED_SHFT                                                                  0xa
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_CPI_2X_BMSK                                                                     0x200
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_CPI_2X_SHFT                                                                       0x9
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_CPI_CNT_BMSK                                                                    0x1c0
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_CPI_CNT_SHFT                                                                      0x6
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_FILT_BS_CNTL_BMSK                                                                0x30
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_FILT_BS_CNTL_SHFT                                                                 0x4
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_SEL_IREG_OSC_BMSK                                                                 0xc
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_SEL_IREG_OSC_SHFT                                                                 0x2
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_LCKDET_CNFG_BMSK                                                                  0x3
#define HWIO_LPASS_LPAAUDIO_PLL_CONFIG_CTL_LCKDET_CNFG_SHFT                                                                  0x0

#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x0000001c)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RMSK                                                                         0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ADDR, HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RESERVE_BITS31_23_BMSK                                                       0xff800000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RESERVE_BITS31_23_SHFT                                                             0x17
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_EN_BMSK                                                                        0x700000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_EN_SHFT                                                                            0x14
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_PUP_BMSK                                                                        0x80000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_PUP_SHFT                                                                           0x13
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_CFG_BMSK                                                                        0x60000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_CFG_SHFT                                                                           0x11
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_TEST_OUT_SEL_BMSK                                                               0x10000
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_TEST_OUT_SEL_SHFT                                                                  0x10
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RESERVE_BITS15_10_BMSK                                                           0xfc00
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_RESERVE_BITS15_10_SHFT                                                              0xa
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_SEL_IEXT_BMSK                                                                     0x200
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_SEL_IEXT_SHFT                                                                       0x9
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_DTEST_SEL_BMSK                                                                    0x180
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_DTEST_SEL_SHFT                                                                      0x7
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_BYP_TESTAMP_BMSK                                                                   0x40
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_BYP_TESTAMP_SHFT                                                                    0x6
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST1_SEL_BMSK                                                                    0x30
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST1_SEL_SHFT                                                                     0x4
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST0_SEL_BMSK                                                                     0xc
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST0_SEL_SHFT                                                                     0x2
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST1_EN_BMSK                                                                      0x2
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST1_EN_SHFT                                                                      0x1
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST0_EN_BMSK                                                                      0x1
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_ATEST0_EN_SHFT                                                                      0x0

#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_ADDR                                                                       (LPASS_CC_REG_BASE      + 0x00000020)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_RMSK                                                                       0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_ADDR, HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_RESERVE_BITS31_0_BMSK                                                      0xffffffff
#define HWIO_LPASS_LPAAUDIO_PLL_TEST_CTL_U_RESERVE_BITS31_0_SHFT                                                             0x0

#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_ADDR                                                                           (LPASS_CC_REG_BASE      + 0x00000024)
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_RMSK                                                                               0xffff
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_STATUS_ADDR, HWIO_LPASS_LPAAUDIO_PLL_STATUS_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_STATUS_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_RESERVE_BITS15_2_BMSK                                                              0xfffc
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_RESERVE_BITS15_2_SHFT                                                                 0x2
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_PLL_ACK_LATCH_BMSK                                                                    0x2
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_PLL_ACK_LATCH_SHFT                                                                    0x1
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_CLOCK_DETECT_BMSK                                                                     0x1
#define HWIO_LPASS_LPAAUDIO_PLL_STATUS_CLOCK_DETECT_SHFT                                                                     0x0

#define HWIO_LPASS_LPAAUDIO_PLL_FREQ_CTL_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00000028)
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

#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_ADDR                                                                       (LPASS_CC_REG_BASE      + 0x0000002c)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_RMSK                                                                              0x3
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_ADDR, HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_CLK_MAIN_SVS_CGC_EN_BMSK                                                          0x2
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_CLK_MAIN_SVS_CGC_EN_SHFT                                                          0x1
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_CLK_MAIN_CGC_EN_BMSK                                                              0x1
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_CGC_EN_CLK_MAIN_CGC_EN_SHFT                                                              0x0

#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_ADDR                                                                          (LPASS_CC_REG_BASE      + 0x00000030)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_RMSK                                                                                 0x3
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_ADDR, HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_RMSK)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_ADDR,m,v,HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_IN)
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_CLK_MAIN_DIV_BMSK                                                                    0x3
#define HWIO_LPASS_LPAAUDIO_PLL_CLK_DIV_CLK_MAIN_DIV_SHFT                                                                    0x0

#define HWIO_LPASS_LPAAUDIO_PLL_REF_CLK_SRC_SEL_ADDR                                                                  (LPASS_CC_REG_BASE      + 0x00000034)
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

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00001000)
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
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_RESERVE_BITS28_24_BMSK                                                       0x1f000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_RESERVE_BITS28_24_SHFT                                                             0x18
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
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_RESERVE_BITS7_4_BMSK                                                               0xf0
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_RESERVE_BITS7_4_SHFT                                                                0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_PLLTEST_BMSK                                                                    0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_PLLTEST_SHFT                                                                    0x3
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_RESET_N_BMSK                                                                    0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_RESET_N_SHFT                                                                    0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_BYPASSNL_BMSK                                                                   0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_BYPASSNL_SHFT                                                                   0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_OUTCTRL_BMSK                                                                    0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_MODE_PLL_OUTCTRL_SHFT                                                                    0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_ADDR                                                                        (LPASS_CC_REG_BASE      + 0x00001004)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_RMSK                                                                        0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_RESERVE_BITS_31_16_BMSK                                                     0xffff0000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_RESERVE_BITS_31_16_SHFT                                                           0x10
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_PLL_L_BMSK                                                                      0xffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_L_VAL_PLL_L_SHFT                                                                         0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_ADDR                                                                    (LPASS_CC_REG_BASE      + 0x00001008)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_RMSK                                                                    0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_PLL_ALPHA_31_0_BMSK                                                     0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_PLL_ALPHA_31_0_SHFT                                                            0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_ADDR                                                                  (LPASS_CC_REG_BASE      + 0x0000100c)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_RMSK                                                                  0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_RESERVE_BITS_31_8_BMSK                                                0xffffff00
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_RESERVE_BITS_31_8_SHFT                                                       0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_PLL_ALPHA_39_32_BMSK                                                        0xff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_ALPHA_VAL_U_PLL_ALPHA_39_32_SHFT                                                         0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_ADDR                                                                     (LPASS_CC_REG_BASE      + 0x00001010)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RMSK                                                                     0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RESERVE_BITS31_28_BMSK                                                   0xf0000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RESERVE_BITS31_28_SHFT                                                         0x1c
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_SSC_MODE_CONTROL_BMSK                                                     0x8000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_SSC_MODE_CONTROL_SHFT                                                          0x1b
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RESERVE_BITS26_25_BMSK                                                    0x6000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RESERVE_BITS26_25_SHFT                                                         0x19
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_ALPHA_EN_BMSK                                                             0x1000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_ALPHA_EN_SHFT                                                                  0x18
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RESERVE_BITS23_22_BMSK                                                     0xc00000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RESERVE_BITS23_22_SHFT                                                         0x16
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_VCO_SEL_BMSK                                                               0x300000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_VCO_SEL_SHFT                                                                   0x14
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RESERVE_BITS19_18_BMSK                                                      0xc0000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RESERVE_BITS19_18_SHFT                                                         0x12
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_AUX_POST_DIV_RATIO_BMSK                                                     0x38000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_AUX_POST_DIV_RATIO_SHFT                                                         0xf
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PRE_DIV_RATIO_BMSK                                                           0x7000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PRE_DIV_RATIO_SHFT                                                              0xc
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_POST_DIV_RATIO_BMSK                                                           0xf00
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_POST_DIV_RATIO_SHFT                                                             0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_OUTPUT_INV_BMSK                                                                0x80
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_OUTPUT_INV_SHFT                                                                 0x7
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RESERVE_BITS6_5_BMSK                                                           0x60
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_RESERVE_BITS6_5_SHFT                                                            0x5
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_LV_TEST_BMSK                                                            0x10
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_LV_TEST_SHFT                                                             0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_LV_EARLY_BMSK                                                            0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_LV_EARLY_SHFT                                                            0x3
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_LV_AUX2_BMSK                                                             0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_LV_AUX2_SHFT                                                             0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_LV_AUX_BMSK                                                              0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_LV_AUX_SHFT                                                              0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_LV_MAIN_BMSK                                                             0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_PLLOUT_LV_MAIN_SHFT                                                             0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_ADDR                                                                   (LPASS_CC_REG_BASE      + 0x00001014)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_RMSK                                                                   0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_RESERVE_BITS31_12_BMSK                                                 0xfffff000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_RESERVE_BITS31_12_SHFT                                                        0xc
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_LATCH_INTERFACE_BYPASS_BMSK                                                 0x800
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_LATCH_INTERFACE_BYPASS_SHFT                                                   0xb
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_STATUS_REGISTER_BMSK                                                        0x700
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_STATUS_REGISTER_SHFT                                                          0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_DSM_BMSK                                                                     0x80
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_DSM_SHFT                                                                      0x7
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_WRITE_STATE_BMSK                                                             0x40
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_WRITE_STATE_SHFT                                                              0x6
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_TARGET_CTL_BMSK                                                              0x38
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_TARGET_CTL_SHFT                                                               0x3
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_LOCK_DET_BMSK                                                                 0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_LOCK_DET_SHFT                                                                 0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_FREEZE_PLL_BMSK                                                               0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_FREEZE_PLL_SHFT                                                               0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_TOGGLE_DET_BMSK                                                               0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_USER_CTL_U_TOGGLE_DET_SHFT                                                               0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_ADDR                                                                   (LPASS_CC_REG_BASE      + 0x00001018)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_RMSK                                                                   0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_SINGLE_DMET_MODE_ENABLE_BMSK                                           0x80000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_SINGLE_DMET_MODE_ENABLE_SHFT                                                 0x1f
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_DMET_WINDOW_ENABLE_BMSK                                                0x40000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_DMET_WINDOW_ENABLE_SHFT                                                      0x1e
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_TOGGLE_DET_SAMPLE_INTER_BMSK                                           0x3c000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_TOGGLE_DET_SAMPLE_INTER_SHFT                                                 0x1a
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_TOGGLE_DET_THRESHOLD_BMSK                                               0x3800000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_TOGGLE_DET_THRESHOLD_SHFT                                                    0x17
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_TOGGLE_DET_SAMPLE_BMSK                                                   0x700000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_TOGGLE_DET_SAMPLE_SHFT                                                       0x14
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_LOCK_DET_THRESHOLD_BMSK                                                   0xff000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_LOCK_DET_THRESHOLD_SHFT                                                       0xc
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_LOCK_DET_SAMPLE_SIZE_BMSK                                                   0xf00
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_LOCK_DET_SAMPLE_SIZE_SHFT                                                     0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_MIN_GLITCH_THRESHOLD_BMSK                                                    0xc0
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_MIN_GLITCH_THRESHOLD_SHFT                                                     0x6
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_REF_CYCLE_BMSK                                                               0x30
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_REF_CYCLE_SHFT                                                                0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_KFN_BMSK                                                                      0xf
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CONFIG_CTL_KFN_SHFT                                                                      0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ADDR                                                                     (LPASS_CC_REG_BASE      + 0x0000101c)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_RMSK                                                                     0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_BIAS_GEN_TRIM_BMSK                                                       0xe0000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_BIAS_GEN_TRIM_SHFT                                                             0x1d
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_PROCESS_CALB_BMSK                                                        0x1c000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_PROCESS_CALB_SHFT                                                              0x1a
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_OVERRIDE_PROCESS_CALB_BMSK                                                0x2000000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_OVERRIDE_PROCESS_CALB_SHFT                                                     0x19
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_FINE_FCW_BMSK                                                             0x1f00000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_FINE_FCW_SHFT                                                                  0x14
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_OVERRIDE_FINE_FCW_BMSK                                                      0x80000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_OVERRIDE_FINE_FCW_SHFT                                                         0x13
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_COARSE_FCW_BMSK                                                             0x7e000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_COARSE_FCW_SHFT                                                                 0xd
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_OVERRIDE_COARSE_BMSK                                                         0x1000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_OVERRIDE_COARSE_SHFT                                                            0xc
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_DISABLE_LFSR_BMSK                                                             0x800
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_DISABLE_LFSR_SHFT                                                               0xb
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_DTEST_SEL_BMSK                                                                0x700
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_DTEST_SEL_SHFT                                                                  0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_DTEST_EN_BMSK                                                                  0x80
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_DTEST_EN_SHFT                                                                   0x7
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_BYP_TESTAMP_BMSK                                                               0x40
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_BYP_TESTAMP_SHFT                                                                0x6
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ATEST1_SEL_BMSK                                                                0x30
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ATEST1_SEL_SHFT                                                                 0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ATEST0_SEL_BMSK                                                                 0xc
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ATEST0_SEL_SHFT                                                                 0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ATEST1_EN_BMSK                                                                  0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ATEST1_EN_SHFT                                                                  0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ATEST0_EN_BMSK                                                                  0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_ATEST0_EN_SHFT                                                                  0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_ADDR                                                                   (LPASS_CC_REG_BASE      + 0x00001020)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_RMSK                                                                   0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_RESERVE_BITS31_22_BMSK                                                 0xffc00000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_RESERVE_BITS31_22_SHFT                                                       0x16
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_GLITCH_DET_CNT_LIMIT_BMSK                                                0x300000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_GLITCH_DET_CNT_LIMIT_SHFT                                                    0x14
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_DIS_GLITCH_PREVENTION_BMSK                                                0x80000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_DIS_GLITCH_PREVENTION_SHFT                                                   0x13
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_DTEST_MODE_SEL_U_BMSK                                                     0x60000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_DTEST_MODE_SEL_U_SHFT                                                        0x11
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_DITHER_SEL_BMSK                                                           0x18000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_DITHER_SEL_SHFT                                                               0xf
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_SEL_2B_3B_CAL_BMSK                                                         0x4000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_SEL_2B_3B_CAL_SHFT                                                            0xe
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_OVERRIDE_FINE_FCW_MSB_BMSK                                                 0x2000
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_OVERRIDE_FINE_FCW_MSB_SHFT                                                    0xd
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_DTEST_MODE_SEL_BMSK                                                        0x1800
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_DTEST_MODE_SEL_SHFT                                                           0xb
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_NMO_OSC_SEL_BMSK                                                            0x600
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_NMO_OSC_SEL_SHFT                                                              0x9
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_RESERVE_BIT8_BMSK                                                           0x100
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_RESERVE_BIT8_SHFT                                                             0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_NOISE_MAG_BMSK                                                               0xe0
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_NOISE_MAG_SHFT                                                                0x5
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_NOISE_GEN_BMSK                                                               0x10
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_NOISE_GEN_SHFT                                                                0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_OSC_BIAS_GND_BMSK                                                             0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_OSC_BIAS_GND_SHFT                                                             0x3
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_PLL_TEST_OUT_SEL_BMSK                                                         0x6
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_PLL_TEST_OUT_SEL_SHFT                                                         0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_CAL_CODE_UPDATE_BMSK                                                          0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_TEST_CTL_U_CAL_CODE_UPDATE_SHFT                                                          0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_ADDR                                                                       (LPASS_CC_REG_BASE      + 0x00001024)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_RMSK                                                                       0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_STATUS_31_0_BMSK                                                           0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_STATUS_STATUS_31_0_SHFT                                                                  0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_ADDR                                                                     (LPASS_CC_REG_BASE      + 0x00001028)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_RMSK                                                                     0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_FREQUENCY_CTL_WORD_BMSK                                                  0xffffffff
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_FREQ_CTL_FREQUENCY_CTL_WORD_SHFT                                                         0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_ADDR                                                                   (LPASS_CC_REG_BASE      + 0x0000102c)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_RMSK                                                                          0xf
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_CLK_AUX_CGC_EN_BMSK                                                           0x8
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_CLK_AUX_CGC_EN_SHFT                                                           0x3
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_CLK_MAIN_CGC_EN_BMSK                                                          0x4
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_CLK_MAIN_CGC_EN_SHFT                                                          0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_CLK_EARLY_SVS_CGC_EN_BMSK                                                     0x2
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_CLK_EARLY_SVS_CGC_EN_SHFT                                                     0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_CLK_EARLY_CGC_EN_BMSK                                                         0x1
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_CGC_EN_CLK_EARLY_CGC_EN_SHFT                                                         0x0

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_CLK_DIV_ADDR                                                                      (LPASS_CC_REG_BASE      + 0x00001030)
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

#define HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_ADDR                                                              (LPASS_CC_REG_BASE      + 0x00001034)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_RMSK                                                                     0x3
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_ADDR, HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_RMSK)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_IN)
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_PLL_CLK_SRC_SEL_BMSK                                                     0x3
#define HWIO_LPASS_LPAAUDIO_DIG_PLL_REF_CLK_SRC_SEL_PLL_CLK_SRC_SEL_SHFT                                                     0x0

#define HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_ADDR                                                                   (LPASS_CC_REG_BASE      + 0x00002000)
#define HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_RMSK                                                                          0x3
#define HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_ADDR, HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_RMSK)
#define HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_ADDR, m)
#define HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_ADDR,v)
#define HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_ADDR,m,v,HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_IN)
#define HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_PLL_CLK_SRC_SEL_BMSK                                                          0x3
#define HWIO_LPASS_QDSP6SS_PLL_REF_CLK_SRC_SEL_PLL_CLK_SRC_SEL_SHFT                                                          0x0

#define HWIO_LPASS_LPAAUDIO_XO_CLK_CTL_ADDR                                                                           (LPASS_CC_REG_BASE      + 0x00003000)
#define HWIO_LPASS_LPAAUDIO_XO_CLK_CTL_RMSK                                                                                  0x1
#define HWIO_LPASS_LPAAUDIO_XO_CLK_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_XO_CLK_CTL_ADDR, HWIO_LPASS_LPAAUDIO_XO_CLK_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_XO_CLK_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_XO_CLK_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_XO_CLK_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_XO_CLK_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_XO_CLK_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_XO_CLK_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_XO_CLK_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_XO_CLK_CTL_XO_CLK_CGC_EN_BMSK                                                                    0x1
#define HWIO_LPASS_LPAAUDIO_XO_CLK_CTL_XO_CLK_CGC_EN_SHFT                                                                    0x0

#define HWIO_LPASS_LPAAUDIO_RAW_CLK_CTL_ADDR                                                                          (LPASS_CC_REG_BASE      + 0x00003004)
#define HWIO_LPASS_LPAAUDIO_RAW_CLK_CTL_RMSK                                                                                 0x3
#define HWIO_LPASS_LPAAUDIO_RAW_CLK_CTL_IN          \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_RAW_CLK_CTL_ADDR, HWIO_LPASS_LPAAUDIO_RAW_CLK_CTL_RMSK)
#define HWIO_LPASS_LPAAUDIO_RAW_CLK_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_LPAAUDIO_RAW_CLK_CTL_ADDR, m)
#define HWIO_LPASS_LPAAUDIO_RAW_CLK_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_LPAAUDIO_RAW_CLK_CTL_ADDR,v)
#define HWIO_LPASS_LPAAUDIO_RAW_CLK_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_LPAAUDIO_RAW_CLK_CTL_ADDR,m,v,HWIO_LPASS_LPAAUDIO_RAW_CLK_CTL_IN)
#define HWIO_LPASS_LPAAUDIO_RAW_CLK_CTL_RAW_CLK_SRC_SEL_BMSK                                                                 0x2
#define HWIO_LPASS_LPAAUDIO_RAW_CLK_CTL_RAW_CLK_SRC_SEL_SHFT                                                                 0x1
#define HWIO_LPASS_LPAAUDIO_RAW_CLK_CTL_RAW_CLK_CGC_EN_BMSK                                                                  0x1
#define HWIO_LPASS_LPAAUDIO_RAW_CLK_CTL_RAW_CLK_CGC_EN_SHFT                                                                  0x0

#define HWIO_LPASS_LPA_PLL_VOTE_APPS_ADDR                                                                             (LPASS_CC_REG_BASE      + 0x00005000)
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

#define HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_ADDR                                                                          (LPASS_CC_REG_BASE      + 0x00006000)
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

#define HWIO_LPASS_LPA_PLL_VOTE_LPASS_HW_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00007000)
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

#define HWIO_LPASS_AUDIO_CORE_BCR_ADDR                                                                                (LPASS_CC_REG_BASE      + 0x00008000)
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

#define HWIO_LPASS_AUDIO_CORE_BCR_SLP_CBCR_ADDR                                                                       (LPASS_CC_REG_BASE      + 0x00008004)
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

#define HWIO_LPASS_AUDIO_WRAPPER_BCR_ADDR                                                                             (LPASS_CC_REG_BASE      + 0x00009000)
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

#define HWIO_LPASS_SENSOR_CORE_BCR_ADDR                                                                               (LPASS_CC_REG_BASE      + 0x00009004)
#define HWIO_LPASS_SENSOR_CORE_BCR_RMSK                                                                               0x70000005
#define HWIO_LPASS_SENSOR_CORE_BCR_IN          \
        in_dword_masked(HWIO_LPASS_SENSOR_CORE_BCR_ADDR, HWIO_LPASS_SENSOR_CORE_BCR_RMSK)
#define HWIO_LPASS_SENSOR_CORE_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SENSOR_CORE_BCR_ADDR, m)
#define HWIO_LPASS_SENSOR_CORE_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_SENSOR_CORE_BCR_ADDR,v)
#define HWIO_LPASS_SENSOR_CORE_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SENSOR_CORE_BCR_ADDR,m,v,HWIO_LPASS_SENSOR_CORE_BCR_IN)
#define HWIO_LPASS_SENSOR_CORE_BCR_BCR_RESET_STATE_BMSK                                                               0x60000000
#define HWIO_LPASS_SENSOR_CORE_BCR_BCR_RESET_STATE_SHFT                                                                     0x1d
#define HWIO_LPASS_SENSOR_CORE_BCR_SENSOR_CORE_BUS_ABORT_ACK_STATUS_BMSK                                              0x10000000
#define HWIO_LPASS_SENSOR_CORE_BCR_SENSOR_CORE_BUS_ABORT_ACK_STATUS_SHFT                                                    0x1c
#define HWIO_LPASS_SENSOR_CORE_BCR_FORCE_RESET_BMSK                                                                          0x4
#define HWIO_LPASS_SENSOR_CORE_BCR_FORCE_RESET_SHFT                                                                          0x2
#define HWIO_LPASS_SENSOR_CORE_BCR_BLK_ARES_BMSK                                                                             0x1
#define HWIO_LPASS_SENSOR_CORE_BCR_BLK_ARES_SHFT                                                                             0x0

#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_ADDR                                                           (LPASS_CC_REG_BASE      + 0x00009008)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_RMSK                                                           0x80000003
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_CLK_OFF_BMSK                                                   0x80000000
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_CLK_OFF_SHFT                                                         0x1f
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_HW_CTL_BMSK                                                           0x2
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_HW_CTL_SHFT                                                           0x1
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_CLK_ENABLE_BMSK                                                       0x1
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_SLP_CBCR_CLK_ENABLE_SHFT                                                       0x0

#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_ADDR                                                            (LPASS_CC_REG_BASE      + 0x0000900c)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_RMSK                                                            0x80000003
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_CLK_OFF_BMSK                                                    0x80000000
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_CLK_OFF_SHFT                                                          0x1f
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_HW_CTL_BMSK                                                            0x2
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_HW_CTL_SHFT                                                            0x1
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_CLK_ENABLE_BMSK                                                        0x1
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR_CLK_ENABLE_SHFT                                                        0x0

#define HWIO_LPASS_Q6SS_BCR_ADDR                                                                                      (LPASS_CC_REG_BASE      + 0x0000a000)
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

#define HWIO_LPASS_Q6SS_BCR_SLP_CBCR_ADDR                                                                             (LPASS_CC_REG_BASE      + 0x0000a004)
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

#define HWIO_LPASS_AUDIO_CORE_GDSCR_ADDR                                                                              (LPASS_CC_REG_BASE      + 0x0000b000)
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

#define HWIO_LPASS_AUDIO_CORE_GDSC_XO_CBCR_ADDR                                                                       (LPASS_CC_REG_BASE      + 0x0000b004)
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

#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_ADDR                                                                        (LPASS_CC_REG_BASE      + 0x0000b008)
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

#define HWIO_LPASS_AUDIO_CORE_GDSCR_VOTE_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x0000c000)
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

#define HWIO_LPASS_LPAIF_PRI_CMD_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00010000)
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

#define HWIO_LPASS_LPAIF_PRI_CFG_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00010004)
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

#define HWIO_LPASS_LPAIF_PRI_M_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00010008)
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

#define HWIO_LPASS_LPAIF_PRI_N_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x0001000c)
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

#define HWIO_LPASS_LPAIF_PRI_D_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00010010)
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

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x00010014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_RMSK                                                                 0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_HW_CTL_BMSK                                                                 0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_HW_CTL_SHFT                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_OSR_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_IBIT_CBCR_ADDR                                                                (LPASS_CC_REG_BASE      + 0x00010018)
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

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EBIT_CBCR_ADDR                                                                (LPASS_CC_REG_BASE      + 0x0001001c)
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

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_CLK_INV_ADDR                                                                  (LPASS_CC_REG_BASE      + 0x00010020)
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

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PRI_EXT_CLK_DETECT_ADDR                                                           (LPASS_CC_REG_BASE      + 0x00010024)
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

#define HWIO_LPASS_LPAIF_SEC_CMD_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00011000)
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

#define HWIO_LPASS_LPAIF_SEC_CFG_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00011004)
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

#define HWIO_LPASS_LPAIF_SEC_M_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00011008)
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

#define HWIO_LPASS_LPAIF_SEC_N_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x0001100c)
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

#define HWIO_LPASS_LPAIF_SEC_D_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00011010)
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

#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x00011014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_RMSK                                                                 0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_HW_CTL_BMSK                                                                 0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_HW_CTL_SHFT                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_OSR_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_IBIT_CBCR_ADDR                                                                (LPASS_CC_REG_BASE      + 0x00011018)
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

#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EBIT_CBCR_ADDR                                                                (LPASS_CC_REG_BASE      + 0x0001101c)
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

#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_CLK_INV_ADDR                                                                  (LPASS_CC_REG_BASE      + 0x00011020)
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

#define HWIO_LPASS_AUDIO_CORE_LPAIF_SEC_EXT_CLK_DETECT_ADDR                                                           (LPASS_CC_REG_BASE      + 0x00011024)
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

#define HWIO_LPASS_LPAIF_TER_CMD_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00012000)
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

#define HWIO_LPASS_LPAIF_TER_CFG_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00012004)
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

#define HWIO_LPASS_LPAIF_TER_M_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00012008)
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

#define HWIO_LPASS_LPAIF_TER_N_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x0001200c)
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

#define HWIO_LPASS_LPAIF_TER_D_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00012010)
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

#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x00012014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_RMSK                                                                 0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_HW_CTL_BMSK                                                                 0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_HW_CTL_SHFT                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_OSR_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_IBIT_CBCR_ADDR                                                                (LPASS_CC_REG_BASE      + 0x00012018)
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

#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EBIT_CBCR_ADDR                                                                (LPASS_CC_REG_BASE      + 0x0001201c)
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

#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_CLK_INV_ADDR                                                                  (LPASS_CC_REG_BASE      + 0x00012020)
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

#define HWIO_LPASS_AUDIO_CORE_LPAIF_TER_EXT_CLK_DETECT_ADDR                                                           (LPASS_CC_REG_BASE      + 0x00012024)
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

#define HWIO_LPASS_LPAIF_QUAD_CMD_RCGR_ADDR                                                                           (LPASS_CC_REG_BASE      + 0x00013000)
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

#define HWIO_LPASS_LPAIF_QUAD_CFG_RCGR_ADDR                                                                           (LPASS_CC_REG_BASE      + 0x00013004)
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

#define HWIO_LPASS_LPAIF_QUAD_M_ADDR                                                                                  (LPASS_CC_REG_BASE      + 0x00013008)
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

#define HWIO_LPASS_LPAIF_QUAD_N_ADDR                                                                                  (LPASS_CC_REG_BASE      + 0x0001300c)
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

#define HWIO_LPASS_LPAIF_QUAD_D_ADDR                                                                                  (LPASS_CC_REG_BASE      + 0x00013010)
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

#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_ADDR                                                                (LPASS_CC_REG_BASE      + 0x00013014)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_RMSK                                                                0x80000003
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_CLK_OFF_BMSK                                                        0x80000000
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_CLK_OFF_SHFT                                                              0x1f
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_HW_CTL_BMSK                                                                0x2
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_HW_CTL_SHFT                                                                0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_CLK_ENABLE_BMSK                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_OSR_CBCR_CLK_ENABLE_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_IBIT_CBCR_ADDR                                                               (LPASS_CC_REG_BASE      + 0x00013018)
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

#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EBIT_CBCR_ADDR                                                               (LPASS_CC_REG_BASE      + 0x0001301c)
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

#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_CLK_INV_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x00013020)
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

#define HWIO_LPASS_AUDIO_CORE_LPAIF_QUAD_EXT_CLK_DETECT_ADDR                                                          (LPASS_CC_REG_BASE      + 0x00013024)
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

#define HWIO_LPASS_AON_CMD_RCGR_ADDR                                                                                  (LPASS_CC_REG_BASE      + 0x00014000)
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

#define HWIO_LPASS_AON_CFG_RCGR_ADDR                                                                                  (LPASS_CC_REG_BASE      + 0x00014004)
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

#define HWIO_LPASS_AON_M_ADDR                                                                                         (LPASS_CC_REG_BASE      + 0x00014008)
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

#define HWIO_LPASS_AON_N_ADDR                                                                                         (LPASS_CC_REG_BASE      + 0x0001400c)
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

#define HWIO_LPASS_AON_D_ADDR                                                                                         (LPASS_CC_REG_BASE      + 0x00014010)
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

#define HWIO_LPASS_AUDIO_WRAPPER_AON_CBCR_ADDR                                                                        (LPASS_CC_REG_BASE      + 0x00014014)
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

#define HWIO_LPASS_ATIME_CMD_RCGR_ADDR                                                                                (LPASS_CC_REG_BASE      + 0x00015000)
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

#define HWIO_LPASS_ATIME_CFG_RCGR_ADDR                                                                                (LPASS_CC_REG_BASE      + 0x00015004)
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

#define HWIO_LPASS_ATIME_M_ADDR                                                                                       (LPASS_CC_REG_BASE      + 0x00015008)
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

#define HWIO_LPASS_ATIME_N_ADDR                                                                                       (LPASS_CC_REG_BASE      + 0x0001500c)
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

#define HWIO_LPASS_ATIME_D_ADDR                                                                                       (LPASS_CC_REG_BASE      + 0x00015010)
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

#define HWIO_LPASS_AUDIO_CORE_AVSYNC_ATIME_CBCR_ADDR                                                                  (LPASS_CC_REG_BASE      + 0x00015014)
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

#define HWIO_LPASS_RESAMPLER_CMD_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00016000)
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

#define HWIO_LPASS_RESAMPLER_CFG_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00016004)
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

#define HWIO_LPASS_RESAMPLER_M_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00016008)
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

#define HWIO_LPASS_RESAMPLER_N_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x0001600c)
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

#define HWIO_LPASS_RESAMPLER_D_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00016010)
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

#define HWIO_LPASS_AUDIO_CORE_RESAMPLER_CBCR_ADDR                                                                     (LPASS_CC_REG_BASE      + 0x00016014)
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

#define HWIO_LPASS_AUD_SLIMBUS_CMD_RCGR_ADDR                                                                          (LPASS_CC_REG_BASE      + 0x00017000)
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

#define HWIO_LPASS_AUD_SLIMBUS_CFG_RCGR_ADDR                                                                          (LPASS_CC_REG_BASE      + 0x00017004)
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

#define HWIO_LPASS_AUD_SLIMBUS_M_ADDR                                                                                 (LPASS_CC_REG_BASE      + 0x00017008)
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

#define HWIO_LPASS_AUD_SLIMBUS_N_ADDR                                                                                 (LPASS_CC_REG_BASE      + 0x0001700c)
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

#define HWIO_LPASS_AUD_SLIMBUS_D_ADDR                                                                                 (LPASS_CC_REG_BASE      + 0x00017010)
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

#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CBCR_ADDR                                                                   (LPASS_CC_REG_BASE      + 0x00017014)
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

#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR_ADDR                                                              (LPASS_CC_REG_BASE      + 0x00017018)
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

#define HWIO_LPASS_AUDIO_CORE_AUD_SLIMBUS_NPL_CBCR_ADDR                                                               (LPASS_CC_REG_BASE      + 0x0001701c)
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

#define HWIO_LPASS_QCA_SLIMBUS_CMD_RCGR_ADDR                                                                          (LPASS_CC_REG_BASE      + 0x00018000)
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

#define HWIO_LPASS_QCA_SLIMBUS_CFG_RCGR_ADDR                                                                          (LPASS_CC_REG_BASE      + 0x00018004)
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

#define HWIO_LPASS_QCA_SLIMBUS_M_ADDR                                                                                 (LPASS_CC_REG_BASE      + 0x00018008)
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

#define HWIO_LPASS_QCA_SLIMBUS_N_ADDR                                                                                 (LPASS_CC_REG_BASE      + 0x0001800c)
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

#define HWIO_LPASS_QCA_SLIMBUS_D_ADDR                                                                                 (LPASS_CC_REG_BASE      + 0x00018010)
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

#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CBCR_ADDR                                                                   (LPASS_CC_REG_BASE      + 0x00018014)
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

#define HWIO_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR_ADDR                                                              (LPASS_CC_REG_BASE      + 0x00018018)
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

#define HWIO_LPASS_LPAIF_PCMOE_CMD_RCGR_ADDR                                                                          (LPASS_CC_REG_BASE      + 0x00019000)
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

#define HWIO_LPASS_LPAIF_PCMOE_CFG_RCGR_ADDR                                                                          (LPASS_CC_REG_BASE      + 0x00019004)
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

#define HWIO_LPASS_LPAIF_PCMOE_M_ADDR                                                                                 (LPASS_CC_REG_BASE      + 0x00019008)
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

#define HWIO_LPASS_LPAIF_PCMOE_N_ADDR                                                                                 (LPASS_CC_REG_BASE      + 0x0001900c)
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

#define HWIO_LPASS_LPAIF_PCMOE_D_ADDR                                                                                 (LPASS_CC_REG_BASE      + 0x00019010)
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

#define HWIO_LPASS_AUDIO_CORE_LPAIF_PCM_DATA_OE_CBCR_ADDR                                                             (LPASS_CC_REG_BASE      + 0x00019014)
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

#define HWIO_LPASS_SLEEP_CMD_RCGR_ADDR                                                                                (LPASS_CC_REG_BASE      + 0x0001a000)
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

#define HWIO_LPASS_SLEEP_CFG_RCGR_ADDR                                                                                (LPASS_CC_REG_BASE      + 0x0001a004)
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

#define HWIO_LPASS_XO_CMD_RCGR_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x0001b000)
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

#define HWIO_LPASS_XO_CFG_RCGR_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x0001b004)
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

#define HWIO_LPASS_AUDIO_CORE_AVSYNC_STC_CBCR_ADDR                                                                    (LPASS_CC_REG_BASE      + 0x0001c000)
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

#define HWIO_LPASS_CORE_CMD_RCGR_ADDR                                                                                 (LPASS_CC_REG_BASE      + 0x0001d000)
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

#define HWIO_LPASS_CORE_CFG_RCGR_ADDR                                                                                 (LPASS_CC_REG_BASE      + 0x0001d004)
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

#define HWIO_LPASS_CORE_M_ADDR                                                                                        (LPASS_CC_REG_BASE      + 0x0001d008)
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

#define HWIO_LPASS_CORE_N_ADDR                                                                                        (LPASS_CC_REG_BASE      + 0x0001d00c)
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

#define HWIO_LPASS_CORE_D_ADDR                                                                                        (LPASS_CC_REG_BASE      + 0x0001d010)
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

#define HWIO_LPASS_AUDIO_CORE_LPM_CORE_CBCR_ADDR                                                                      (LPASS_CC_REG_BASE      + 0x0001e000)
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

#define HWIO_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x0001e004)
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

#define HWIO_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x0001e008)
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

#define HWIO_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x0001e00c)
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

#define HWIO_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x0001e010)
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

#define HWIO_LPASS_AUDIO_CORE_CORE_CBCR_ADDR                                                                          (LPASS_CC_REG_BASE      + 0x0001f000)
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

#define HWIO_LPASS_EXT_MCLK0_CMD_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00020000)
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

#define HWIO_LPASS_EXT_MCLK0_CFG_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00020004)
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

#define HWIO_LPASS_EXT_MCLK0_M_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00020008)
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

#define HWIO_LPASS_EXT_MCLK0_N_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x0002000c)
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

#define HWIO_LPASS_EXT_MCLK0_D_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00020010)
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

#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CBCR_ADDR                                                                  (LPASS_CC_REG_BASE      + 0x00020014)
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

#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CTRL_CLK_OE_ADDR                                                           (LPASS_CC_REG_BASE      + 0x00020018)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CTRL_CLK_OE_RMSK                                                                  0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CTRL_CLK_OE_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CTRL_CLK_OE_ADDR, HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CTRL_CLK_OE_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CTRL_CLK_OE_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CTRL_CLK_OE_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CTRL_CLK_OE_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CTRL_CLK_OE_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CTRL_CLK_OE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CTRL_CLK_OE_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CTRL_CLK_OE_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CTRL_CLK_OE_CTRL_CLK_OE_BMSK                                                      0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK0_CTRL_CLK_OE_CTRL_CLK_OE_SHFT                                                      0x0

#define HWIO_LPASS_EXT_MCLK1_CMD_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00021000)
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

#define HWIO_LPASS_EXT_MCLK1_CFG_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00021004)
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

#define HWIO_LPASS_EXT_MCLK1_M_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00021008)
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

#define HWIO_LPASS_EXT_MCLK1_N_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x0002100c)
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

#define HWIO_LPASS_EXT_MCLK1_D_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00021010)
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

#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CBCR_ADDR                                                                  (LPASS_CC_REG_BASE      + 0x00021014)
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

#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CTRL_CLK_OE_ADDR                                                           (LPASS_CC_REG_BASE      + 0x00021018)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CTRL_CLK_OE_RMSK                                                                  0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CTRL_CLK_OE_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CTRL_CLK_OE_ADDR, HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CTRL_CLK_OE_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CTRL_CLK_OE_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CTRL_CLK_OE_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CTRL_CLK_OE_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CTRL_CLK_OE_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CTRL_CLK_OE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CTRL_CLK_OE_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CTRL_CLK_OE_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CTRL_CLK_OE_CTRL_CLK_OE_BMSK                                                      0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK1_CTRL_CLK_OE_CTRL_CLK_OE_SHFT                                                      0x0

#define HWIO_LPASS_EXT_MCLK2_CMD_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00022000)
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

#define HWIO_LPASS_EXT_MCLK2_CFG_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00022004)
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

#define HWIO_LPASS_EXT_MCLK2_M_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00022008)
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

#define HWIO_LPASS_EXT_MCLK2_N_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x0002200c)
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

#define HWIO_LPASS_EXT_MCLK2_D_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00022010)
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

#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK2_CBCR_ADDR                                                                  (LPASS_CC_REG_BASE      + 0x00022014)
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

#define HWIO_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR_ADDR                                                             (LPASS_CC_REG_BASE      + 0x00023000)
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

#define HWIO_LPASS_AUDIO_WRAPPER_SYSNOC_SWAY_AON_CBCR_ADDR                                                            (LPASS_CC_REG_BASE      + 0x00025000)
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

#define HWIO_LPASS_Q6SS_AHBM_AON_CBCR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00026000)
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

#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00027000)
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_RMSK                                                                            0x800000f3
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK3_CMD_RCGR_ADDR, HWIO_LPASS_EXT_MCLK3_CMD_RCGR_RMSK)
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK3_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK3_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK3_CMD_RCGR_ADDR,m,v,HWIO_LPASS_EXT_MCLK3_CMD_RCGR_IN)
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_ROOT_OFF_BMSK                                                                   0x80000000
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_ROOT_OFF_SHFT                                                                         0x1f
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_DIRTY_D_BMSK                                                                          0x80
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_DIRTY_D_SHFT                                                                           0x7
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_DIRTY_N_BMSK                                                                          0x40
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_DIRTY_N_SHFT                                                                           0x6
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_DIRTY_M_BMSK                                                                          0x20
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_DIRTY_M_SHFT                                                                           0x5
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                   0x10
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                    0x4
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_ROOT_EN_BMSK                                                                           0x2
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_ROOT_EN_SHFT                                                                           0x1
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_UPDATE_BMSK                                                                            0x1
#define HWIO_LPASS_EXT_MCLK3_CMD_RCGR_UPDATE_SHFT                                                                            0x0

#define HWIO_LPASS_EXT_MCLK3_CFG_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00027004)
#define HWIO_LPASS_EXT_MCLK3_CFG_RCGR_RMSK                                                                                0x771f
#define HWIO_LPASS_EXT_MCLK3_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK3_CFG_RCGR_ADDR, HWIO_LPASS_EXT_MCLK3_CFG_RCGR_RMSK)
#define HWIO_LPASS_EXT_MCLK3_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK3_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_EXT_MCLK3_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK3_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_EXT_MCLK3_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK3_CFG_RCGR_ADDR,m,v,HWIO_LPASS_EXT_MCLK3_CFG_RCGR_IN)
#define HWIO_LPASS_EXT_MCLK3_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                    0x4000
#define HWIO_LPASS_EXT_MCLK3_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                       0xe
#define HWIO_LPASS_EXT_MCLK3_CFG_RCGR_MODE_BMSK                                                                           0x3000
#define HWIO_LPASS_EXT_MCLK3_CFG_RCGR_MODE_SHFT                                                                              0xc
#define HWIO_LPASS_EXT_MCLK3_CFG_RCGR_SRC_SEL_BMSK                                                                         0x700
#define HWIO_LPASS_EXT_MCLK3_CFG_RCGR_SRC_SEL_SHFT                                                                           0x8
#define HWIO_LPASS_EXT_MCLK3_CFG_RCGR_SRC_DIV_BMSK                                                                          0x1f
#define HWIO_LPASS_EXT_MCLK3_CFG_RCGR_SRC_DIV_SHFT                                                                           0x0

#define HWIO_LPASS_EXT_MCLK3_M_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00027008)
#define HWIO_LPASS_EXT_MCLK3_M_RMSK                                                                                         0xff
#define HWIO_LPASS_EXT_MCLK3_M_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK3_M_ADDR, HWIO_LPASS_EXT_MCLK3_M_RMSK)
#define HWIO_LPASS_EXT_MCLK3_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK3_M_ADDR, m)
#define HWIO_LPASS_EXT_MCLK3_M_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK3_M_ADDR,v)
#define HWIO_LPASS_EXT_MCLK3_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK3_M_ADDR,m,v,HWIO_LPASS_EXT_MCLK3_M_IN)
#define HWIO_LPASS_EXT_MCLK3_M_M_BMSK                                                                                       0xff
#define HWIO_LPASS_EXT_MCLK3_M_M_SHFT                                                                                        0x0

#define HWIO_LPASS_EXT_MCLK3_N_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x0002700c)
#define HWIO_LPASS_EXT_MCLK3_N_RMSK                                                                                         0xff
#define HWIO_LPASS_EXT_MCLK3_N_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK3_N_ADDR, HWIO_LPASS_EXT_MCLK3_N_RMSK)
#define HWIO_LPASS_EXT_MCLK3_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK3_N_ADDR, m)
#define HWIO_LPASS_EXT_MCLK3_N_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK3_N_ADDR,v)
#define HWIO_LPASS_EXT_MCLK3_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK3_N_ADDR,m,v,HWIO_LPASS_EXT_MCLK3_N_IN)
#define HWIO_LPASS_EXT_MCLK3_N_NOT_N_MINUS_M_BMSK                                                                           0xff
#define HWIO_LPASS_EXT_MCLK3_N_NOT_N_MINUS_M_SHFT                                                                            0x0

#define HWIO_LPASS_EXT_MCLK3_D_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00027010)
#define HWIO_LPASS_EXT_MCLK3_D_RMSK                                                                                         0xff
#define HWIO_LPASS_EXT_MCLK3_D_IN          \
        in_dword_masked(HWIO_LPASS_EXT_MCLK3_D_ADDR, HWIO_LPASS_EXT_MCLK3_D_RMSK)
#define HWIO_LPASS_EXT_MCLK3_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_EXT_MCLK3_D_ADDR, m)
#define HWIO_LPASS_EXT_MCLK3_D_OUT(v)      \
        out_dword(HWIO_LPASS_EXT_MCLK3_D_ADDR,v)
#define HWIO_LPASS_EXT_MCLK3_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_EXT_MCLK3_D_ADDR,m,v,HWIO_LPASS_EXT_MCLK3_D_IN)
#define HWIO_LPASS_EXT_MCLK3_D_NOT_2D_BMSK                                                                                  0xff
#define HWIO_LPASS_EXT_MCLK3_D_NOT_2D_SHFT                                                                                   0x0

#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_ADDR                                                                  (LPASS_CC_REG_BASE      + 0x00027014)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_RMSK                                                                  0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_CLK_OFF_BMSK                                                          0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_CLK_OFF_SHFT                                                                0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_HW_CTL_BMSK                                                                  0x2
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_HW_CTL_SHFT                                                                  0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_CLK_ENABLE_BMSK                                                              0x1
#define HWIO_LPASS_AUDIO_WRAPPER_EXT_MCLK3_CBCR_CLK_ENABLE_SHFT                                                              0x0

#define HWIO_LPASS_AUDIO_CORE_QDSP_SWAY_AON_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x00028000)
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

#define HWIO_LPASS_ISLAND_SCC_DBG_BCR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x0002d000)
#define HWIO_LPASS_ISLAND_SCC_DBG_BCR_RMSK                                                                                   0x1
#define HWIO_LPASS_ISLAND_SCC_DBG_BCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_DBG_BCR_ADDR, HWIO_LPASS_ISLAND_SCC_DBG_BCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_DBG_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_DBG_BCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_DBG_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_DBG_BCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_DBG_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_DBG_BCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_DBG_BCR_IN)
#define HWIO_LPASS_ISLAND_SCC_DBG_BCR_BLK_ARES_BMSK                                                                          0x1
#define HWIO_LPASS_ISLAND_SCC_DBG_BCR_BLK_ARES_SHFT                                                                          0x0

#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_ADDR                                                                          (LPASS_CC_REG_BASE      + 0x0002d004)
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_RMSK                                                                          0x800000f3
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_ADDR, HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_RMSK)
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_ADDR,m,v,HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_IN)
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_ROOT_OFF_BMSK                                                                 0x80000000
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_ROOT_OFF_SHFT                                                                       0x1f
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_DIRTY_D_BMSK                                                                        0x80
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_DIRTY_D_SHFT                                                                         0x7
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_DIRTY_N_BMSK                                                                        0x40
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_DIRTY_N_SHFT                                                                         0x6
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_DIRTY_M_BMSK                                                                        0x20
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_DIRTY_M_SHFT                                                                         0x5
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                 0x10
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                  0x4
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_ROOT_EN_BMSK                                                                         0x2
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_ROOT_EN_SHFT                                                                         0x1
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_UPDATE_BMSK                                                                          0x1
#define HWIO_LPASS_SCC_AON_DBG_CMD_RCGR_UPDATE_SHFT                                                                          0x0

#define HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_ADDR                                                                          (LPASS_CC_REG_BASE      + 0x0002d008)
#define HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_RMSK                                                                              0x771f
#define HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_ADDR, HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_RMSK)
#define HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_ADDR,m,v,HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_IN)
#define HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                  0x4000
#define HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                     0xe
#define HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_MODE_BMSK                                                                         0x3000
#define HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_MODE_SHFT                                                                            0xc
#define HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_SRC_SEL_BMSK                                                                       0x700
#define HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_SRC_SEL_SHFT                                                                         0x8
#define HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_SRC_DIV_BMSK                                                                        0x1f
#define HWIO_LPASS_SCC_AON_DBG_CFG_RCGR_SRC_DIV_SHFT                                                                         0x0

#define HWIO_LPASS_SCC_AON_DBG_M_ADDR                                                                                 (LPASS_CC_REG_BASE      + 0x0002d00c)
#define HWIO_LPASS_SCC_AON_DBG_M_RMSK                                                                                       0xff
#define HWIO_LPASS_SCC_AON_DBG_M_IN          \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_M_ADDR, HWIO_LPASS_SCC_AON_DBG_M_RMSK)
#define HWIO_LPASS_SCC_AON_DBG_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_M_ADDR, m)
#define HWIO_LPASS_SCC_AON_DBG_M_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_AON_DBG_M_ADDR,v)
#define HWIO_LPASS_SCC_AON_DBG_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_AON_DBG_M_ADDR,m,v,HWIO_LPASS_SCC_AON_DBG_M_IN)
#define HWIO_LPASS_SCC_AON_DBG_M_M_BMSK                                                                                     0xff
#define HWIO_LPASS_SCC_AON_DBG_M_M_SHFT                                                                                      0x0

#define HWIO_LPASS_SCC_AON_DBG_N_ADDR                                                                                 (LPASS_CC_REG_BASE      + 0x0002d010)
#define HWIO_LPASS_SCC_AON_DBG_N_RMSK                                                                                       0xff
#define HWIO_LPASS_SCC_AON_DBG_N_IN          \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_N_ADDR, HWIO_LPASS_SCC_AON_DBG_N_RMSK)
#define HWIO_LPASS_SCC_AON_DBG_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_N_ADDR, m)
#define HWIO_LPASS_SCC_AON_DBG_N_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_AON_DBG_N_ADDR,v)
#define HWIO_LPASS_SCC_AON_DBG_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_AON_DBG_N_ADDR,m,v,HWIO_LPASS_SCC_AON_DBG_N_IN)
#define HWIO_LPASS_SCC_AON_DBG_N_NOT_N_MINUS_M_BMSK                                                                         0xff
#define HWIO_LPASS_SCC_AON_DBG_N_NOT_N_MINUS_M_SHFT                                                                          0x0

#define HWIO_LPASS_SCC_AON_DBG_D_ADDR                                                                                 (LPASS_CC_REG_BASE      + 0x0002d014)
#define HWIO_LPASS_SCC_AON_DBG_D_RMSK                                                                                       0xff
#define HWIO_LPASS_SCC_AON_DBG_D_IN          \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_D_ADDR, HWIO_LPASS_SCC_AON_DBG_D_RMSK)
#define HWIO_LPASS_SCC_AON_DBG_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_D_ADDR, m)
#define HWIO_LPASS_SCC_AON_DBG_D_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_AON_DBG_D_ADDR,v)
#define HWIO_LPASS_SCC_AON_DBG_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_AON_DBG_D_ADDR,m,v,HWIO_LPASS_SCC_AON_DBG_D_IN)
#define HWIO_LPASS_SCC_AON_DBG_D_NOT_2D_BMSK                                                                                0xff
#define HWIO_LPASS_SCC_AON_DBG_D_NOT_2D_SHFT                                                                                 0x0

#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x0002d018)
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_RMSK                                                                            0x80007ff1
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_AT_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_AT_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_AT_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_AT_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_AT_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_AT_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_CLK_OFF_BMSK                                                                    0x80000000
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_CLK_OFF_SHFT                                                                          0x1f
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_FORCE_MEM_CORE_ON_BMSK                                                              0x4000
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_FORCE_MEM_CORE_ON_SHFT                                                                 0xe
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                                            0x2000
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                               0xd
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                                           0x1000
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                              0xc
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_WAKEUP_BMSK                                                                          0xf00
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_WAKEUP_SHFT                                                                            0x8
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_SLEEP_BMSK                                                                            0xf0
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_SLEEP_SHFT                                                                             0x4
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_CLK_ENABLE_BMSK                                                                        0x1
#define HWIO_LPASS_ISLAND_SCC_AT_CBCR_CLK_ENABLE_SHFT                                                                        0x0

#define HWIO_LPASS_ISLAND_SCC_Q6_ATBM_CBCR_ADDR                                                                       (LPASS_CC_REG_BASE      + 0x0002d01c)
#define HWIO_LPASS_ISLAND_SCC_Q6_ATBM_CBCR_RMSK                                                                       0x80000001
#define HWIO_LPASS_ISLAND_SCC_Q6_ATBM_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_Q6_ATBM_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_Q6_ATBM_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_Q6_ATBM_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_Q6_ATBM_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_Q6_ATBM_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_Q6_ATBM_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_Q6_ATBM_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_Q6_ATBM_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_Q6_ATBM_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_Q6_ATBM_CBCR_CLK_OFF_BMSK                                                               0x80000000
#define HWIO_LPASS_ISLAND_SCC_Q6_ATBM_CBCR_CLK_OFF_SHFT                                                                     0x1f
#define HWIO_LPASS_ISLAND_SCC_Q6_ATBM_CBCR_CLK_ENABLE_BMSK                                                                   0x1
#define HWIO_LPASS_ISLAND_SCC_Q6_ATBM_CBCR_CLK_ENABLE_SHFT                                                                   0x0

#define HWIO_LPASS_ISLAND_SCC_PCLKDBG_CBCR_ADDR                                                                       (LPASS_CC_REG_BASE      + 0x0002d020)
#define HWIO_LPASS_ISLAND_SCC_PCLKDBG_CBCR_RMSK                                                                       0x80000001
#define HWIO_LPASS_ISLAND_SCC_PCLKDBG_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_PCLKDBG_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_PCLKDBG_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_PCLKDBG_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_PCLKDBG_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_PCLKDBG_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_PCLKDBG_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_PCLKDBG_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_PCLKDBG_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_PCLKDBG_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_PCLKDBG_CBCR_CLK_OFF_BMSK                                                               0x80000000
#define HWIO_LPASS_ISLAND_SCC_PCLKDBG_CBCR_CLK_OFF_SHFT                                                                     0x1f
#define HWIO_LPASS_ISLAND_SCC_PCLKDBG_CBCR_CLK_ENABLE_BMSK                                                                   0x1
#define HWIO_LPASS_ISLAND_SCC_PCLKDBG_CBCR_CLK_ENABLE_SHFT                                                                   0x0

#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_BCR_ADDR                                                                      (LPASS_CC_REG_BASE      + 0x0002e000)
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_BCR_RMSK                                                                             0x1
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_BCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_BCR_ADDR, HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_BCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_BCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_BCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_BCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_BCR_IN)
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_BCR_BLK_ARES_BMSK                                                                    0x1
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_BCR_BLK_ARES_SHFT                                                                    0x0

#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_ADDR                                                                    (LPASS_CC_REG_BASE      + 0x0002e004)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_RMSK                                                                    0x800000f3
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_ADDR, HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_RMSK)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_ADDR,m,v,HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_IN)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_ROOT_OFF_BMSK                                                           0x80000000
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_ROOT_OFF_SHFT                                                                 0x1f
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_DIRTY_D_BMSK                                                                  0x80
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_DIRTY_D_SHFT                                                                   0x7
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_DIRTY_N_BMSK                                                                  0x40
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_DIRTY_N_SHFT                                                                   0x6
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_DIRTY_M_BMSK                                                                  0x20
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_DIRTY_M_SHFT                                                                   0x5
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                           0x10
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                            0x4
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_ROOT_EN_BMSK                                                                   0x2
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_ROOT_EN_SHFT                                                                   0x1
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_UPDATE_BMSK                                                                    0x1
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CMD_RCGR_UPDATE_SHFT                                                                    0x0

#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_ADDR                                                                    (LPASS_CC_REG_BASE      + 0x0002e008)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_RMSK                                                                        0x771f
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_ADDR, HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_RMSK)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_ADDR,m,v,HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_IN)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_ALT_SRC_SEL_BMSK                                                            0x4000
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_ALT_SRC_SEL_SHFT                                                               0xe
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_MODE_BMSK                                                                   0x3000
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_MODE_SHFT                                                                      0xc
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_SRC_SEL_BMSK                                                                 0x700
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_SRC_SEL_SHFT                                                                   0x8
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_SRC_DIV_BMSK                                                                  0x1f
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_CFG_RCGR_SRC_DIV_SHFT                                                                   0x0

#define HWIO_LPASS_SCC_AON_DBG_TSCTR_M_ADDR                                                                           (LPASS_CC_REG_BASE      + 0x0002e00c)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_M_RMSK                                                                                 0xff
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_M_IN          \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_TSCTR_M_ADDR, HWIO_LPASS_SCC_AON_DBG_TSCTR_M_RMSK)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_TSCTR_M_ADDR, m)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_M_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_AON_DBG_TSCTR_M_ADDR,v)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_AON_DBG_TSCTR_M_ADDR,m,v,HWIO_LPASS_SCC_AON_DBG_TSCTR_M_IN)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_M_M_BMSK                                                                               0xff
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_M_M_SHFT                                                                                0x0

#define HWIO_LPASS_SCC_AON_DBG_TSCTR_N_ADDR                                                                           (LPASS_CC_REG_BASE      + 0x0002e010)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_N_RMSK                                                                                 0xff
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_N_IN          \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_TSCTR_N_ADDR, HWIO_LPASS_SCC_AON_DBG_TSCTR_N_RMSK)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_TSCTR_N_ADDR, m)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_N_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_AON_DBG_TSCTR_N_ADDR,v)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_AON_DBG_TSCTR_N_ADDR,m,v,HWIO_LPASS_SCC_AON_DBG_TSCTR_N_IN)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_N_NOT_N_MINUS_M_BMSK                                                                   0xff
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_N_NOT_N_MINUS_M_SHFT                                                                    0x0

#define HWIO_LPASS_SCC_AON_DBG_TSCTR_D_ADDR                                                                           (LPASS_CC_REG_BASE      + 0x0002e014)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_D_RMSK                                                                                 0xff
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_D_IN          \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_TSCTR_D_ADDR, HWIO_LPASS_SCC_AON_DBG_TSCTR_D_RMSK)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_AON_DBG_TSCTR_D_ADDR, m)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_D_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_AON_DBG_TSCTR_D_ADDR,v)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_AON_DBG_TSCTR_D_ADDR,m,v,HWIO_LPASS_SCC_AON_DBG_TSCTR_D_IN)
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_D_NOT_2D_BMSK                                                                          0xff
#define HWIO_LPASS_SCC_AON_DBG_TSCTR_D_NOT_2D_SHFT                                                                           0x0

#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_ADDR                                                                     (LPASS_CC_REG_BASE      + 0x0002e018)
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_RMSK                                                                     0x80070001
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_CLK_OFF_BMSK                                                             0x80000000
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_CLK_OFF_SHFT                                                                   0x1f
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_CLK_DIV_BMSK                                                                0x70000
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_CLK_DIV_SHFT                                                                   0x10
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_CLK_ENABLE_BMSK                                                                 0x1
#define HWIO_LPASS_ISLAND_SCC_DBG_TSCTR_CBCR_CLK_ENABLE_SHFT                                                                 0x0

#define HWIO_LPASS_AUDIO_WRAPPER_MPU_CFG_AON_CBCR_ADDR                                                                (LPASS_CC_REG_BASE      + 0x00031000)
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

#define HWIO_LPASS_AUDIO_WRAPPER_Q6_AHBM_MPU_AON_CBCR_ADDR                                                            (LPASS_CC_REG_BASE      + 0x00032000)
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

#define HWIO_LPASS_Q6SS_AHBS_AON_CBCR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00033000)
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

#define HWIO_LPASS_DFS_HW_CTL_ADDR                                                                                    (LPASS_CC_REG_BASE      + 0x00034000)
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

#define HWIO_LPASS_DFS_PERF0_RCG_SRC_SEL_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00034004)
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

#define HWIO_LPASS_DFS_PERF1_RCG_SRC_SEL_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00034008)
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

#define HWIO_LPASS_DFS_PERF2_RCG_SRC_SEL_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x0003400c)
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

#define HWIO_LPASS_DFS_PERF3_RCG_SRC_SEL_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00034010)
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

#define HWIO_LPASS_DFS_PERF4_RCG_SRC_SEL_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00034014)
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

#define HWIO_LPASS_DFS_PERF5_RCG_SRC_SEL_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00034018)
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

#define HWIO_LPASS_DFS_PERF6_RCG_SRC_SEL_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x0003401c)
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

#define HWIO_LPASS_DFS_PERF7_RCG_SRC_SEL_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00034020)
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

#define HWIO_LPASS_DFS_PERF0_RCG_SRC_DIV_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00034024)
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

#define HWIO_LPASS_DFS_PERF1_RCG_SRC_DIV_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00034028)
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

#define HWIO_LPASS_DFS_PERF2_RCG_SRC_DIV_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x0003402c)
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

#define HWIO_LPASS_DFS_PERF3_RCG_SRC_DIV_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00034030)
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

#define HWIO_LPASS_DFS_PERF4_RCG_SRC_DIV_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00034034)
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

#define HWIO_LPASS_DFS_PERF5_RCG_SRC_DIV_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00034038)
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

#define HWIO_LPASS_DFS_PERF6_RCG_SRC_DIV_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x0003403c)
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

#define HWIO_LPASS_DFS_PERF7_RCG_SRC_DIV_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00034040)
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

#define HWIO_LPASS_DFS_RCG_ASYNC_CLK_EN_ADDR                                                                          (LPASS_CC_REG_BASE      + 0x00034044)
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

#define HWIO_LPASS_DFS_PERF0_CDIV_ADDR                                                                                (LPASS_CC_REG_BASE      + 0x00034048)
#define HWIO_LPASS_DFS_PERF0_CDIV_RMSK                                                                                      0x77
#define HWIO_LPASS_DFS_PERF0_CDIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF0_CDIV_ADDR, HWIO_LPASS_DFS_PERF0_CDIV_RMSK)
#define HWIO_LPASS_DFS_PERF0_CDIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF0_CDIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF0_CDIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF0_CDIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF0_CDIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF0_CDIV_ADDR,m,v,HWIO_LPASS_DFS_PERF0_CDIV_IN)
#define HWIO_LPASS_DFS_PERF0_CDIV_PERF0_LPAAUDIO_PLL_MAIN_SVS_CDIV_BMSK                                                     0x70
#define HWIO_LPASS_DFS_PERF0_CDIV_PERF0_LPAAUDIO_PLL_MAIN_SVS_CDIV_SHFT                                                      0x4
#define HWIO_LPASS_DFS_PERF0_CDIV_PERF0_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_BMSK                                                 0x7
#define HWIO_LPASS_DFS_PERF0_CDIV_PERF0_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_SHFT                                                 0x0

#define HWIO_LPASS_DFS_PERF1_CDIV_ADDR                                                                                (LPASS_CC_REG_BASE      + 0x0003404c)
#define HWIO_LPASS_DFS_PERF1_CDIV_RMSK                                                                                      0x77
#define HWIO_LPASS_DFS_PERF1_CDIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF1_CDIV_ADDR, HWIO_LPASS_DFS_PERF1_CDIV_RMSK)
#define HWIO_LPASS_DFS_PERF1_CDIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF1_CDIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF1_CDIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF1_CDIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF1_CDIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF1_CDIV_ADDR,m,v,HWIO_LPASS_DFS_PERF1_CDIV_IN)
#define HWIO_LPASS_DFS_PERF1_CDIV_PERF1_LPAAUDIO_PLL_MAIN_SVS_CDIV_BMSK                                                     0x70
#define HWIO_LPASS_DFS_PERF1_CDIV_PERF1_LPAAUDIO_PLL_MAIN_SVS_CDIV_SHFT                                                      0x4
#define HWIO_LPASS_DFS_PERF1_CDIV_PERF1_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_BMSK                                                 0x7
#define HWIO_LPASS_DFS_PERF1_CDIV_PERF1_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_SHFT                                                 0x0

#define HWIO_LPASS_DFS_PERF2_CDIV_ADDR                                                                                (LPASS_CC_REG_BASE      + 0x00034050)
#define HWIO_LPASS_DFS_PERF2_CDIV_RMSK                                                                                      0x77
#define HWIO_LPASS_DFS_PERF2_CDIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF2_CDIV_ADDR, HWIO_LPASS_DFS_PERF2_CDIV_RMSK)
#define HWIO_LPASS_DFS_PERF2_CDIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF2_CDIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF2_CDIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF2_CDIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF2_CDIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF2_CDIV_ADDR,m,v,HWIO_LPASS_DFS_PERF2_CDIV_IN)
#define HWIO_LPASS_DFS_PERF2_CDIV_PERF2_LPAAUDIO_PLL_MAIN_SVS_CDIV_BMSK                                                     0x70
#define HWIO_LPASS_DFS_PERF2_CDIV_PERF2_LPAAUDIO_PLL_MAIN_SVS_CDIV_SHFT                                                      0x4
#define HWIO_LPASS_DFS_PERF2_CDIV_PERF2_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_BMSK                                                 0x7
#define HWIO_LPASS_DFS_PERF2_CDIV_PERF2_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_SHFT                                                 0x0

#define HWIO_LPASS_DFS_PERF3_CDIV_ADDR                                                                                (LPASS_CC_REG_BASE      + 0x00034054)
#define HWIO_LPASS_DFS_PERF3_CDIV_RMSK                                                                                      0x77
#define HWIO_LPASS_DFS_PERF3_CDIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF3_CDIV_ADDR, HWIO_LPASS_DFS_PERF3_CDIV_RMSK)
#define HWIO_LPASS_DFS_PERF3_CDIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF3_CDIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF3_CDIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF3_CDIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF3_CDIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF3_CDIV_ADDR,m,v,HWIO_LPASS_DFS_PERF3_CDIV_IN)
#define HWIO_LPASS_DFS_PERF3_CDIV_PERF3_LPAAUDIO_PLL_MAIN_SVS_CDIV_BMSK                                                     0x70
#define HWIO_LPASS_DFS_PERF3_CDIV_PERF3_LPAAUDIO_PLL_MAIN_SVS_CDIV_SHFT                                                      0x4
#define HWIO_LPASS_DFS_PERF3_CDIV_PERF3_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_BMSK                                                 0x7
#define HWIO_LPASS_DFS_PERF3_CDIV_PERF3_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_SHFT                                                 0x0

#define HWIO_LPASS_DFS_PERF4_CDIV_ADDR                                                                                (LPASS_CC_REG_BASE      + 0x00034058)
#define HWIO_LPASS_DFS_PERF4_CDIV_RMSK                                                                                      0x77
#define HWIO_LPASS_DFS_PERF4_CDIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF4_CDIV_ADDR, HWIO_LPASS_DFS_PERF4_CDIV_RMSK)
#define HWIO_LPASS_DFS_PERF4_CDIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF4_CDIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF4_CDIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF4_CDIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF4_CDIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF4_CDIV_ADDR,m,v,HWIO_LPASS_DFS_PERF4_CDIV_IN)
#define HWIO_LPASS_DFS_PERF4_CDIV_PERF4_LPAAUDIO_PLL_MAIN_SVS_CDIV_BMSK                                                     0x70
#define HWIO_LPASS_DFS_PERF4_CDIV_PERF4_LPAAUDIO_PLL_MAIN_SVS_CDIV_SHFT                                                      0x4
#define HWIO_LPASS_DFS_PERF4_CDIV_PERF4_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_BMSK                                                 0x7
#define HWIO_LPASS_DFS_PERF4_CDIV_PERF4_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_SHFT                                                 0x0

#define HWIO_LPASS_DFS_PERF5_CDIV_ADDR                                                                                (LPASS_CC_REG_BASE      + 0x0003405c)
#define HWIO_LPASS_DFS_PERF5_CDIV_RMSK                                                                                      0x77
#define HWIO_LPASS_DFS_PERF5_CDIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF5_CDIV_ADDR, HWIO_LPASS_DFS_PERF5_CDIV_RMSK)
#define HWIO_LPASS_DFS_PERF5_CDIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF5_CDIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF5_CDIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF5_CDIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF5_CDIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF5_CDIV_ADDR,m,v,HWIO_LPASS_DFS_PERF5_CDIV_IN)
#define HWIO_LPASS_DFS_PERF5_CDIV_PERF5_LPAAUDIO_PLL_MAIN_SVS_CDIV_BMSK                                                     0x70
#define HWIO_LPASS_DFS_PERF5_CDIV_PERF5_LPAAUDIO_PLL_MAIN_SVS_CDIV_SHFT                                                      0x4
#define HWIO_LPASS_DFS_PERF5_CDIV_PERF5_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_BMSK                                                 0x7
#define HWIO_LPASS_DFS_PERF5_CDIV_PERF5_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_SHFT                                                 0x0

#define HWIO_LPASS_DFS_PERF6_CDIV_ADDR                                                                                (LPASS_CC_REG_BASE      + 0x00034060)
#define HWIO_LPASS_DFS_PERF6_CDIV_RMSK                                                                                      0x77
#define HWIO_LPASS_DFS_PERF6_CDIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF6_CDIV_ADDR, HWIO_LPASS_DFS_PERF6_CDIV_RMSK)
#define HWIO_LPASS_DFS_PERF6_CDIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF6_CDIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF6_CDIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF6_CDIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF6_CDIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF6_CDIV_ADDR,m,v,HWIO_LPASS_DFS_PERF6_CDIV_IN)
#define HWIO_LPASS_DFS_PERF6_CDIV_PERF6_LPAAUDIO_PLL_MAIN_SVS_CDIV_BMSK                                                     0x70
#define HWIO_LPASS_DFS_PERF6_CDIV_PERF6_LPAAUDIO_PLL_MAIN_SVS_CDIV_SHFT                                                      0x4
#define HWIO_LPASS_DFS_PERF6_CDIV_PERF6_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_BMSK                                                 0x7
#define HWIO_LPASS_DFS_PERF6_CDIV_PERF6_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_SHFT                                                 0x0

#define HWIO_LPASS_DFS_PERF7_CDIV_ADDR                                                                                (LPASS_CC_REG_BASE      + 0x00034064)
#define HWIO_LPASS_DFS_PERF7_CDIV_RMSK                                                                                      0x77
#define HWIO_LPASS_DFS_PERF7_CDIV_IN          \
        in_dword_masked(HWIO_LPASS_DFS_PERF7_CDIV_ADDR, HWIO_LPASS_DFS_PERF7_CDIV_RMSK)
#define HWIO_LPASS_DFS_PERF7_CDIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_DFS_PERF7_CDIV_ADDR, m)
#define HWIO_LPASS_DFS_PERF7_CDIV_OUT(v)      \
        out_dword(HWIO_LPASS_DFS_PERF7_CDIV_ADDR,v)
#define HWIO_LPASS_DFS_PERF7_CDIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_DFS_PERF7_CDIV_ADDR,m,v,HWIO_LPASS_DFS_PERF7_CDIV_IN)
#define HWIO_LPASS_DFS_PERF7_CDIV_PERF7_LPAAUDIO_PLL_MAIN_SVS_CDIV_BMSK                                                     0x70
#define HWIO_LPASS_DFS_PERF7_CDIV_PERF7_LPAAUDIO_PLL_MAIN_SVS_CDIV_SHFT                                                      0x4
#define HWIO_LPASS_DFS_PERF7_CDIV_PERF7_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_BMSK                                                 0x7
#define HWIO_LPASS_DFS_PERF7_CDIV_PERF7_LPAAUDIO_DIG_PLL_EARLY_SVS_CDIV_SHFT                                                 0x0

#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CMD_RCGR_ADDR                                                                (LPASS_CC_REG_BASE      + 0x00035000)
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

#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_CFG_RCGR_ADDR                                                                (LPASS_CC_REG_BASE      + 0x00035004)
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

#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_M_ADDR                                                                       (LPASS_CC_REG_BASE      + 0x00035008)
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

#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_N_ADDR                                                                       (LPASS_CC_REG_BASE      + 0x0003500c)
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

#define HWIO_LPASS_QOS_FIXED_LAT_COUNTER_D_ADDR                                                                       (LPASS_CC_REG_BASE      + 0x00035010)
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

#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR                                             (LPASS_CC_REG_BASE      + 0x0003501c)
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

#define HWIO_LPASS_AUDIO_WRAPPER_QOS_DANGER_FIXED_LAT_COUNTER_CBCR_ADDR                                               (LPASS_CC_REG_BASE      + 0x00035020)
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

#define HWIO_LPASS_AUDIO_CORE_QOS_DMONITOR_FIXED_LAT_COUNTER_CBCR_ADDR                                                (LPASS_CC_REG_BASE      + 0x00036000)
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

#define HWIO_LPASS_AUDIO_CORE_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR                                                 (LPASS_CC_REG_BASE      + 0x00037000)
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

#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_Q6_ADDR                                                      (LPASS_CC_REG_BASE      + 0x00037004)
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

#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_Q6_ADDR                                                      (LPASS_CC_REG_BASE      + 0x00037008)
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

#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_CTL_ADDR                                      (LPASS_CC_REG_BASE      + 0x00038000)
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

#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_APPS_ADDR                                                    (LPASS_CC_REG_BASE      + 0x00038004)
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

#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_APPS_ADDR                                                    (LPASS_CC_REG_BASE      + 0x00038008)
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

#define HWIO_LPASS_AUDIO_WRAPPER_Q6_VOTE_LPASS_Q6_SMMU_GDS_ADDR                                                       (LPASS_CC_REG_BASE      + 0x00039000)
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

#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_SPM_CLK_CTL_ADDR                                                             (LPASS_CC_REG_BASE      + 0x00039004)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_SPM_CLK_CTL_RMSK                                                                    0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_SPM_CLK_CTL_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_SPM_CLK_CTL_ADDR, HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_SPM_CLK_CTL_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_SPM_CLK_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_SPM_CLK_CTL_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_SPM_CLK_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_SPM_CLK_CTL_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_SPM_CLK_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_SPM_CLK_CTL_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_SPM_CLK_CTL_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_SPM_CLK_CTL_Q6_SMMU_SPM_COLLAPSE_OR_CLK_GATE_SEL_BMSK                               0x1
#define HWIO_LPASS_AUDIO_WRAPPER_Q6_SMMU_SPM_CLK_CTL_Q6_SMMU_SPM_COLLAPSE_OR_CLK_GATE_SEL_SHFT                               0x0

#define HWIO_LPASS_AUDIO_WRAPPER_BUS_TIMEOUT_AON_CBCR_ADDR                                                            (LPASS_CC_REG_BASE      + 0x0003a000)
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

#define HWIO_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR_ADDR                                                              (LPASS_CC_REG_BASE      + 0x0003b000)
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

#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_TZ_ADDR                                                      (LPASS_CC_REG_BASE      + 0x0003c004)
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

#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_TZ_ADDR                                                      (LPASS_CC_REG_BASE      + 0x0003c008)
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

#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_STATUS_HYP_ADDR                                                     (LPASS_CC_REG_BASE      + 0x0003d004)
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

#define HWIO_LPASS_GDS_HW_CTRL_SEQUENCE_ABORT_IRQ_ENABLE_HYP_ADDR                                                     (LPASS_CC_REG_BASE      + 0x0003d008)
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

#define HWIO_LPASS_SCC_PLL_MODE_ADDR                                                                                  (LPASS_CC_REG_BASE      + 0x0003e000)
#define HWIO_LPASS_SCC_PLL_MODE_RMSK                                                                                  0xffffffff
#define HWIO_LPASS_SCC_PLL_MODE_IN          \
        in_dword_masked(HWIO_LPASS_SCC_PLL_MODE_ADDR, HWIO_LPASS_SCC_PLL_MODE_RMSK)
#define HWIO_LPASS_SCC_PLL_MODE_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_PLL_MODE_ADDR, m)
#define HWIO_LPASS_SCC_PLL_MODE_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_PLL_MODE_ADDR,v)
#define HWIO_LPASS_SCC_PLL_MODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_PLL_MODE_ADDR,m,v,HWIO_LPASS_SCC_PLL_MODE_IN)
#define HWIO_LPASS_SCC_PLL_MODE_PLL_LOCK_DET_BMSK                                                                     0x80000000
#define HWIO_LPASS_SCC_PLL_MODE_PLL_LOCK_DET_SHFT                                                                           0x1f
#define HWIO_LPASS_SCC_PLL_MODE_RESERVE_BIT30_BMSK                                                                    0x40000000
#define HWIO_LPASS_SCC_PLL_MODE_RESERVE_BIT30_SHFT                                                                          0x1e
#define HWIO_LPASS_SCC_PLL_MODE_PLL_ACK_LATCH_BMSK                                                                    0x20000000
#define HWIO_LPASS_SCC_PLL_MODE_PLL_ACK_LATCH_SHFT                                                                          0x1d
#define HWIO_LPASS_SCC_PLL_MODE_RESERVE_BITS28_24_BMSK                                                                0x1f000000
#define HWIO_LPASS_SCC_PLL_MODE_RESERVE_BITS28_24_SHFT                                                                      0x18
#define HWIO_LPASS_SCC_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_BMSK                                                         0x800000
#define HWIO_LPASS_SCC_PLL_MODE_PLL_HW_UPDATE_LOGIC_BYPASS_SHFT                                                             0x17
#define HWIO_LPASS_SCC_PLL_MODE_PLL_UPDATE_BMSK                                                                         0x400000
#define HWIO_LPASS_SCC_PLL_MODE_PLL_UPDATE_SHFT                                                                             0x16
#define HWIO_LPASS_SCC_PLL_MODE_RESERVE_BITS21_3_BMSK                                                                   0x3ffff8
#define HWIO_LPASS_SCC_PLL_MODE_RESERVE_BITS21_3_SHFT                                                                        0x3
#define HWIO_LPASS_SCC_PLL_MODE_PLL_RESET_N_BMSK                                                                             0x4
#define HWIO_LPASS_SCC_PLL_MODE_PLL_RESET_N_SHFT                                                                             0x2
#define HWIO_LPASS_SCC_PLL_MODE_RESERVE_BIT1_BMSK                                                                            0x2
#define HWIO_LPASS_SCC_PLL_MODE_RESERVE_BIT1_SHFT                                                                            0x1
#define HWIO_LPASS_SCC_PLL_MODE_PLL_OUTCTRL_BMSK                                                                             0x1
#define HWIO_LPASS_SCC_PLL_MODE_PLL_OUTCTRL_SHFT                                                                             0x0

#define HWIO_LPASS_SCC_PLL_L_VAL_ADDR                                                                                 (LPASS_CC_REG_BASE      + 0x0003e004)
#define HWIO_LPASS_SCC_PLL_L_VAL_RMSK                                                                                     0xffff
#define HWIO_LPASS_SCC_PLL_L_VAL_IN          \
        in_dword_masked(HWIO_LPASS_SCC_PLL_L_VAL_ADDR, HWIO_LPASS_SCC_PLL_L_VAL_RMSK)
#define HWIO_LPASS_SCC_PLL_L_VAL_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_PLL_L_VAL_ADDR, m)
#define HWIO_LPASS_SCC_PLL_L_VAL_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_PLL_L_VAL_ADDR,v)
#define HWIO_LPASS_SCC_PLL_L_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_PLL_L_VAL_ADDR,m,v,HWIO_LPASS_SCC_PLL_L_VAL_IN)
#define HWIO_LPASS_SCC_PLL_L_VAL_PLL_L_BMSK                                                                               0xffff
#define HWIO_LPASS_SCC_PLL_L_VAL_PLL_L_SHFT                                                                                  0x0

#define HWIO_LPASS_SCC_PLL_CAL_L_VAL_ADDR                                                                             (LPASS_CC_REG_BASE      + 0x0003e008)
#define HWIO_LPASS_SCC_PLL_CAL_L_VAL_RMSK                                                                                 0xffff
#define HWIO_LPASS_SCC_PLL_CAL_L_VAL_IN          \
        in_dword_masked(HWIO_LPASS_SCC_PLL_CAL_L_VAL_ADDR, HWIO_LPASS_SCC_PLL_CAL_L_VAL_RMSK)
#define HWIO_LPASS_SCC_PLL_CAL_L_VAL_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_PLL_CAL_L_VAL_ADDR, m)
#define HWIO_LPASS_SCC_PLL_CAL_L_VAL_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_PLL_CAL_L_VAL_ADDR,v)
#define HWIO_LPASS_SCC_PLL_CAL_L_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_PLL_CAL_L_VAL_ADDR,m,v,HWIO_LPASS_SCC_PLL_CAL_L_VAL_IN)
#define HWIO_LPASS_SCC_PLL_CAL_L_VAL_PLL_CAL_L_BMSK                                                                       0xffff
#define HWIO_LPASS_SCC_PLL_CAL_L_VAL_PLL_CAL_L_SHFT                                                                          0x0

#define HWIO_LPASS_SCC_PLL_USER_CTL_ADDR                                                                              (LPASS_CC_REG_BASE      + 0x0003e00c)
#define HWIO_LPASS_SCC_PLL_USER_CTL_RMSK                                                                              0xffffffff
#define HWIO_LPASS_SCC_PLL_USER_CTL_IN          \
        in_dword_masked(HWIO_LPASS_SCC_PLL_USER_CTL_ADDR, HWIO_LPASS_SCC_PLL_USER_CTL_RMSK)
#define HWIO_LPASS_SCC_PLL_USER_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_PLL_USER_CTL_ADDR, m)
#define HWIO_LPASS_SCC_PLL_USER_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_PLL_USER_CTL_ADDR,v)
#define HWIO_LPASS_SCC_PLL_USER_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_PLL_USER_CTL_ADDR,m,v,HWIO_LPASS_SCC_PLL_USER_CTL_IN)
#define HWIO_LPASS_SCC_PLL_USER_CTL_RESERVE_BITS31_15_BMSK                                                            0xffff8000
#define HWIO_LPASS_SCC_PLL_USER_CTL_RESERVE_BITS31_15_SHFT                                                                   0xf
#define HWIO_LPASS_SCC_PLL_USER_CTL_PRE_DIV_RATIO_BMSK                                                                    0x7000
#define HWIO_LPASS_SCC_PLL_USER_CTL_PRE_DIV_RATIO_SHFT                                                                       0xc
#define HWIO_LPASS_SCC_PLL_USER_CTL_POST_DIV_RATIO_BMSK                                                                    0xf00
#define HWIO_LPASS_SCC_PLL_USER_CTL_POST_DIV_RATIO_SHFT                                                                      0x8
#define HWIO_LPASS_SCC_PLL_USER_CTL_OUT_CLK_POLARITY_BMSK                                                                   0x80
#define HWIO_LPASS_SCC_PLL_USER_CTL_OUT_CLK_POLARITY_SHFT                                                                    0x7
#define HWIO_LPASS_SCC_PLL_USER_CTL_RESERVE_BITS6_5_BMSK                                                                    0x60
#define HWIO_LPASS_SCC_PLL_USER_CTL_RESERVE_BITS6_5_SHFT                                                                     0x5
#define HWIO_LPASS_SCC_PLL_USER_CTL_PLLOUT_LV_TEST_BMSK                                                                     0x10
#define HWIO_LPASS_SCC_PLL_USER_CTL_PLLOUT_LV_TEST_SHFT                                                                      0x4
#define HWIO_LPASS_SCC_PLL_USER_CTL_RESERVE_BITS3_1_BMSK                                                                     0xe
#define HWIO_LPASS_SCC_PLL_USER_CTL_RESERVE_BITS3_1_SHFT                                                                     0x1
#define HWIO_LPASS_SCC_PLL_USER_CTL_PLLOUT_LV_MAIN_BMSK                                                                      0x1
#define HWIO_LPASS_SCC_PLL_USER_CTL_PLLOUT_LV_MAIN_SHFT                                                                      0x0

#define HWIO_LPASS_SCC_PLL_USER_CTL_U_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x0003e010)
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_RMSK                                                                            0xffffffff
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_IN          \
        in_dword_masked(HWIO_LPASS_SCC_PLL_USER_CTL_U_ADDR, HWIO_LPASS_SCC_PLL_USER_CTL_U_RMSK)
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_PLL_USER_CTL_U_ADDR, m)
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_PLL_USER_CTL_U_ADDR,v)
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_PLL_USER_CTL_U_ADDR,m,v,HWIO_LPASS_SCC_PLL_USER_CTL_U_IN)
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_RESERVE_BITS31_13_BMSK                                                          0xffffe000
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_RESERVE_BITS31_13_SHFT                                                                 0xd
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_BIAS_ON_IN_STANDBY_BMSK                                                             0x1000
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_BIAS_ON_IN_STANDBY_SHFT                                                                0xc
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_REF_CLK_AT_OUT_BMSK                                                                  0x800
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_REF_CLK_AT_OUT_SHFT                                                                    0xb
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_SCALE_STATE_ON_RESTART_BMSK                                                          0x600
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_SCALE_STATE_ON_RESTART_SHFT                                                            0x9
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_LATCH_INTERFACE_BYPASS_BMSK                                                          0x100
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_LATCH_INTERFACE_BYPASS_SHFT                                                            0x8
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_STATUS_REGISTER_BMSK                                                                  0xe0
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_STATUS_REGISTER_SHFT                                                                   0x5
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_WRITE_STATE_BMSK                                                                      0x10
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_WRITE_STATE_SHFT                                                                       0x4
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_CALIB_CTRL_BMSK                                                                        0xe
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_CALIB_CTRL_SHFT                                                                        0x1
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_USE_ONLY_FINE_DET_BMSK                                                                 0x1
#define HWIO_LPASS_SCC_PLL_USER_CTL_U_USE_ONLY_FINE_DET_SHFT                                                                 0x0

#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x0003e014)
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_RMSK                                                                            0xffffffff
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_IN          \
        in_dword_masked(HWIO_LPASS_SCC_PLL_CONFIG_CTL_ADDR, HWIO_LPASS_SCC_PLL_CONFIG_CTL_RMSK)
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_PLL_CONFIG_CTL_ADDR, m)
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_PLL_CONFIG_CTL_ADDR,v)
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_PLL_CONFIG_CTL_ADDR,m,v,HWIO_LPASS_SCC_PLL_CONFIG_CTL_IN)
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_RESERVE_BIT_31_BMSK                                                             0x80000000
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_RESERVE_BIT_31_SHFT                                                                   0x1f
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_USE_BOTH_REF_CLK_EDGE_BMSK                                                      0x40000000
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_USE_BOTH_REF_CLK_EDGE_SHFT                                                            0x1e
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_BIAS_WARMUP_TIME_BMSK                                                           0x30000000
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_BIAS_WARMUP_TIME_SHFT                                                                 0x1c
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_FINE_LDC_THRESHOLD_BMSK                                                          0xf000000
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_FINE_LDC_THRESHOLD_SHFT                                                               0x18
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_COARSE_LDC_THRESHOLD_BMSK                                                         0xf00000
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_COARSE_LDC_THRESHOLD_SHFT                                                             0x14
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_COARSE_LOCK_DET_NEG_THRESHOLD_BMSK                                                 0xf0000
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_COARSE_LOCK_DET_NEG_THRESHOLD_SHFT                                                    0x10
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_COARSE_LOCK_DET_POS_THRESHOLD_BMSK                                                  0xf000
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_COARSE_LOCK_DET_POS_THRESHOLD_SHFT                                                     0xc
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_FINE_LOCK_DET_THRESHOLD_BMSK                                                         0xe00
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_FINE_LOCK_DET_THRESHOLD_SHFT                                                           0x9
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_FINE_LOCK_DET_SAMPLE_SIZE_BMSK                                                       0x1c0
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_FINE_LOCK_DET_SAMPLE_SIZE_SHFT                                                         0x6
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_MIN_GLITCH_THRESHOLD_BMSK                                                             0x30
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_MIN_GLITCH_THRESHOLD_SHFT                                                              0x4
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_KFN_BMSK                                                                               0xf
#define HWIO_LPASS_SCC_PLL_CONFIG_CTL_KFN_SHFT                                                                               0x0

#define HWIO_LPASS_SCC_PLL_TEST_CTL_ADDR                                                                              (LPASS_CC_REG_BASE      + 0x0003e018)
#define HWIO_LPASS_SCC_PLL_TEST_CTL_RMSK                                                                              0xffffffff
#define HWIO_LPASS_SCC_PLL_TEST_CTL_IN          \
        in_dword_masked(HWIO_LPASS_SCC_PLL_TEST_CTL_ADDR, HWIO_LPASS_SCC_PLL_TEST_CTL_RMSK)
#define HWIO_LPASS_SCC_PLL_TEST_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_PLL_TEST_CTL_ADDR, m)
#define HWIO_LPASS_SCC_PLL_TEST_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_PLL_TEST_CTL_ADDR,v)
#define HWIO_LPASS_SCC_PLL_TEST_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_PLL_TEST_CTL_ADDR,m,v,HWIO_LPASS_SCC_PLL_TEST_CTL_IN)
#define HWIO_LPASS_SCC_PLL_TEST_CTL_NOISE_MAG_BMSK                                                                    0xc0000000
#define HWIO_LPASS_SCC_PLL_TEST_CTL_NOISE_MAG_SHFT                                                                          0x1e
#define HWIO_LPASS_SCC_PLL_TEST_CTL_NOISE_GEN_BMSK                                                                    0x20000000
#define HWIO_LPASS_SCC_PLL_TEST_CTL_NOISE_GEN_SHFT                                                                          0x1d
#define HWIO_LPASS_SCC_PLL_TEST_CTL_OSC_BIAS_GND_BMSK                                                                 0x10000000
#define HWIO_LPASS_SCC_PLL_TEST_CTL_OSC_BIAS_GND_SHFT                                                                       0x1c
#define HWIO_LPASS_SCC_PLL_TEST_CTL_PLL_TEST_OUT_SEL_BMSK                                                              0xc000000
#define HWIO_LPASS_SCC_PLL_TEST_CTL_PLL_TEST_OUT_SEL_SHFT                                                                   0x1a
#define HWIO_LPASS_SCC_PLL_TEST_CTL_COARSE_FCW_BMSK                                                                    0x3fc0000
#define HWIO_LPASS_SCC_PLL_TEST_CTL_COARSE_FCW_SHFT                                                                         0x12
#define HWIO_LPASS_SCC_PLL_TEST_CTL_OVERRIDE_COARSE_FCW_BMSK                                                             0x20000
#define HWIO_LPASS_SCC_PLL_TEST_CTL_OVERRIDE_COARSE_FCW_SHFT                                                                0x11
#define HWIO_LPASS_SCC_PLL_TEST_CTL_COARSE_PCW_BMSK                                                                      0x1c000
#define HWIO_LPASS_SCC_PLL_TEST_CTL_COARSE_PCW_SHFT                                                                          0xe
#define HWIO_LPASS_SCC_PLL_TEST_CTL_OVERRIDE_COARSE_PCW_BMSK                                                              0x2000
#define HWIO_LPASS_SCC_PLL_TEST_CTL_OVERRIDE_COARSE_PCW_SHFT                                                                 0xd
#define HWIO_LPASS_SCC_PLL_TEST_CTL_DISABLE_LFSR_BMSK                                                                     0x1000
#define HWIO_LPASS_SCC_PLL_TEST_CTL_DISABLE_LFSR_SHFT                                                                        0xc
#define HWIO_LPASS_SCC_PLL_TEST_CTL_DTEST_SEL_BMSK                                                                         0xf80
#define HWIO_LPASS_SCC_PLL_TEST_CTL_DTEST_SEL_SHFT                                                                           0x7
#define HWIO_LPASS_SCC_PLL_TEST_CTL_DTEST_EN_BMSK                                                                           0x40
#define HWIO_LPASS_SCC_PLL_TEST_CTL_DTEST_EN_SHFT                                                                            0x6
#define HWIO_LPASS_SCC_PLL_TEST_CTL_ATEST1_SEL_BMSK                                                                         0x30
#define HWIO_LPASS_SCC_PLL_TEST_CTL_ATEST1_SEL_SHFT                                                                          0x4
#define HWIO_LPASS_SCC_PLL_TEST_CTL_ATEST0_SEL_BMSK                                                                          0xc
#define HWIO_LPASS_SCC_PLL_TEST_CTL_ATEST0_SEL_SHFT                                                                          0x2
#define HWIO_LPASS_SCC_PLL_TEST_CTL_ATEST1_EN_BMSK                                                                           0x2
#define HWIO_LPASS_SCC_PLL_TEST_CTL_ATEST1_EN_SHFT                                                                           0x1
#define HWIO_LPASS_SCC_PLL_TEST_CTL_ATEST0_EN_BMSK                                                                           0x1
#define HWIO_LPASS_SCC_PLL_TEST_CTL_ATEST0_EN_SHFT                                                                           0x0

#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x0003e01c)
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_RMSK                                                                            0xffffffff
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_IN          \
        in_dword_masked(HWIO_LPASS_SCC_PLL_TEST_CTL_U_ADDR, HWIO_LPASS_SCC_PLL_TEST_CTL_U_RMSK)
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_PLL_TEST_CTL_U_ADDR, m)
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_PLL_TEST_CTL_U_ADDR,v)
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_PLL_TEST_CTL_U_ADDR,m,v,HWIO_LPASS_SCC_PLL_TEST_CTL_U_IN)
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_RESERVE_BITS31_9_BMSK                                                           0xfffffe00
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_RESERVE_BITS31_9_SHFT                                                                  0x9
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_USE_LINEAR_SETTLING_BMSK                                                             0x100
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_USE_LINEAR_SETTLING_SHFT                                                               0x8
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_DIS_AUTO_UPDATE_CALIB_CODE_BMSK                                                       0x80
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_DIS_AUTO_UPDATE_CALIB_CODE_SHFT                                                        0x7
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_NUM_REF_CYCLE_PER_CALIB_STEP_BMSK                                                     0x60
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_NUM_REF_CYCLE_PER_CALIB_STEP_SHFT                                                      0x5
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_GLITCH_DET_COUNT_BMSK                                                                 0x18
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_GLITCH_DET_COUNT_SHFT                                                                  0x3
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_DIS_GLITCH_PREV_BMSK                                                                   0x4
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_DIS_GLITCH_PREV_SHFT                                                                   0x2
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_NMO_OSC_SEL_BMSK                                                                       0x3
#define HWIO_LPASS_SCC_PLL_TEST_CTL_U_NMO_OSC_SEL_SHFT                                                                       0x0

#define HWIO_LPASS_SCC_PLL_STATUS_ADDR                                                                                (LPASS_CC_REG_BASE      + 0x0003e020)
#define HWIO_LPASS_SCC_PLL_STATUS_RMSK                                                                                0xffffffff
#define HWIO_LPASS_SCC_PLL_STATUS_IN          \
        in_dword_masked(HWIO_LPASS_SCC_PLL_STATUS_ADDR, HWIO_LPASS_SCC_PLL_STATUS_RMSK)
#define HWIO_LPASS_SCC_PLL_STATUS_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_PLL_STATUS_ADDR, m)
#define HWIO_LPASS_SCC_PLL_STATUS_STATUS_31_0_BMSK                                                                    0xffffffff
#define HWIO_LPASS_SCC_PLL_STATUS_STATUS_31_0_SHFT                                                                           0x0

#define HWIO_LPASS_SCC_PLL_FREQ_CTL_ADDR                                                                              (LPASS_CC_REG_BASE      + 0x0003e024)
#define HWIO_LPASS_SCC_PLL_FREQ_CTL_RMSK                                                                              0xffffffff
#define HWIO_LPASS_SCC_PLL_FREQ_CTL_IN          \
        in_dword_masked(HWIO_LPASS_SCC_PLL_FREQ_CTL_ADDR, HWIO_LPASS_SCC_PLL_FREQ_CTL_RMSK)
#define HWIO_LPASS_SCC_PLL_FREQ_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_PLL_FREQ_CTL_ADDR, m)
#define HWIO_LPASS_SCC_PLL_FREQ_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_PLL_FREQ_CTL_ADDR,v)
#define HWIO_LPASS_SCC_PLL_FREQ_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_PLL_FREQ_CTL_ADDR,m,v,HWIO_LPASS_SCC_PLL_FREQ_CTL_IN)
#define HWIO_LPASS_SCC_PLL_FREQ_CTL_FREQUENCY_CTL_WORD_BMSK                                                           0xffffffff
#define HWIO_LPASS_SCC_PLL_FREQ_CTL_FREQUENCY_CTL_WORD_SHFT                                                                  0x0

#define HWIO_LPASS_SCC_PLL_OPMODE_ADDR                                                                                (LPASS_CC_REG_BASE      + 0x0003e028)
#define HWIO_LPASS_SCC_PLL_OPMODE_RMSK                                                                                       0x7
#define HWIO_LPASS_SCC_PLL_OPMODE_IN          \
        in_dword_masked(HWIO_LPASS_SCC_PLL_OPMODE_ADDR, HWIO_LPASS_SCC_PLL_OPMODE_RMSK)
#define HWIO_LPASS_SCC_PLL_OPMODE_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_PLL_OPMODE_ADDR, m)
#define HWIO_LPASS_SCC_PLL_OPMODE_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_PLL_OPMODE_ADDR,v)
#define HWIO_LPASS_SCC_PLL_OPMODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_PLL_OPMODE_ADDR,m,v,HWIO_LPASS_SCC_PLL_OPMODE_IN)
#define HWIO_LPASS_SCC_PLL_OPMODE_PLL_OPMODE_BMSK                                                                            0x7
#define HWIO_LPASS_SCC_PLL_OPMODE_PLL_OPMODE_SHFT                                                                            0x0

#define HWIO_LPASS_SCC_CBC_MISC_ADDR                                                                                  (LPASS_CC_REG_BASE      + 0x0003e04c)
#define HWIO_LPASS_SCC_CBC_MISC_RMSK                                                                                         0x1
#define HWIO_LPASS_SCC_CBC_MISC_IN          \
        in_dword_masked(HWIO_LPASS_SCC_CBC_MISC_ADDR, HWIO_LPASS_SCC_CBC_MISC_RMSK)
#define HWIO_LPASS_SCC_CBC_MISC_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_CBC_MISC_ADDR, m)
#define HWIO_LPASS_SCC_CBC_MISC_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_CBC_MISC_ADDR,v)
#define HWIO_LPASS_SCC_CBC_MISC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_CBC_MISC_ADDR,m,v,HWIO_LPASS_SCC_CBC_MISC_IN)
#define HWIO_LPASS_SCC_CBC_MISC_SCC_IDDQ_ALL_CBC_DIS_BMSK                                                                    0x1
#define HWIO_LPASS_SCC_CBC_MISC_SCC_IDDQ_ALL_CBC_DIS_SHFT                                                                    0x0

#define HWIO_LPASS_SCC_DEBUG_CLK_CTL_ADDR                                                                             (LPASS_CC_REG_BASE      + 0x0003e050)
#define HWIO_LPASS_SCC_DEBUG_CLK_CTL_RMSK                                                                                    0x7
#define HWIO_LPASS_SCC_DEBUG_CLK_CTL_IN          \
        in_dword_masked(HWIO_LPASS_SCC_DEBUG_CLK_CTL_ADDR, HWIO_LPASS_SCC_DEBUG_CLK_CTL_RMSK)
#define HWIO_LPASS_SCC_DEBUG_CLK_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_DEBUG_CLK_CTL_ADDR, m)
#define HWIO_LPASS_SCC_DEBUG_CLK_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_DEBUG_CLK_CTL_ADDR,v)
#define HWIO_LPASS_SCC_DEBUG_CLK_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_DEBUG_CLK_CTL_ADDR,m,v,HWIO_LPASS_SCC_DEBUG_CLK_CTL_IN)
#define HWIO_LPASS_SCC_DEBUG_CLK_CTL_PLL_TEST_CLK_ENABLE_BMSK                                                                0x4
#define HWIO_LPASS_SCC_DEBUG_CLK_CTL_PLL_TEST_CLK_ENABLE_SHFT                                                                0x2
#define HWIO_LPASS_SCC_DEBUG_CLK_CTL_PLL_TEST_POST_DIV_BMSK                                                                  0x3
#define HWIO_LPASS_SCC_DEBUG_CLK_CTL_PLL_TEST_POST_DIV_SHFT                                                                  0x0

#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x0003e054)
#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_RMSK                                                                               0x3f
#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_IN          \
        in_dword_masked(HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_ADDR, HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_RMSK)
#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_ADDR, m)
#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_ADDR,v)
#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_ADDR,m,v,HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_IN)
#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_SLEEP_CLK_SEL_OVRD_VAL_BMSK                                                        0x20
#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_SLEEP_CLK_SEL_OVRD_VAL_SHFT                                                         0x5
#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_SLEEP_CLK_SEL_OVRD_BMSK                                                            0x10
#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_SLEEP_CLK_SEL_OVRD_SHFT                                                             0x4
#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_CBC_EN_OVRD_VAL_BMSK                                                                0x8
#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_CBC_EN_OVRD_VAL_SHFT                                                                0x3
#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_CBC_EN_OVRD_BMSK                                                                    0x4
#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_CBC_EN_OVRD_SHFT                                                                    0x2
#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_PLL_OUT_CTRL_OVRD_BMSK                                                              0x2
#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_PLL_OUT_CTRL_OVRD_SHFT                                                              0x1
#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_PLL_OPMODE_CTRL_OVRD_BMSK                                                           0x1
#define HWIO_LPASS_SCC_AON_CTRL_OVRD_REG_PLL_OPMODE_CTRL_OVRD_SHFT                                                           0x0

#define HWIO_LPASS_SCC_PLL_CLK_DIV_ADDR                                                                               (LPASS_CC_REG_BASE      + 0x0003e058)
#define HWIO_LPASS_SCC_PLL_CLK_DIV_RMSK                                                                                      0xf
#define HWIO_LPASS_SCC_PLL_CLK_DIV_IN          \
        in_dword_masked(HWIO_LPASS_SCC_PLL_CLK_DIV_ADDR, HWIO_LPASS_SCC_PLL_CLK_DIV_RMSK)
#define HWIO_LPASS_SCC_PLL_CLK_DIV_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_PLL_CLK_DIV_ADDR, m)
#define HWIO_LPASS_SCC_PLL_CLK_DIV_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_PLL_CLK_DIV_ADDR,v)
#define HWIO_LPASS_SCC_PLL_CLK_DIV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_PLL_CLK_DIV_ADDR,m,v,HWIO_LPASS_SCC_PLL_CLK_DIV_IN)
#define HWIO_LPASS_SCC_PLL_CLK_DIV_CLK_MAIN_DIV_BMSK                                                                         0xf
#define HWIO_LPASS_SCC_PLL_CLK_DIV_CLK_MAIN_DIV_SHFT                                                                         0x0

#define HWIO_LPASS_SCC_PLL_REF_CLK_SRC_SEL_ADDR                                                                       (LPASS_CC_REG_BASE      + 0x0003e05c)
#define HWIO_LPASS_SCC_PLL_REF_CLK_SRC_SEL_RMSK                                                                              0x3
#define HWIO_LPASS_SCC_PLL_REF_CLK_SRC_SEL_IN          \
        in_dword_masked(HWIO_LPASS_SCC_PLL_REF_CLK_SRC_SEL_ADDR, HWIO_LPASS_SCC_PLL_REF_CLK_SRC_SEL_RMSK)
#define HWIO_LPASS_SCC_PLL_REF_CLK_SRC_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_PLL_REF_CLK_SRC_SEL_ADDR, m)
#define HWIO_LPASS_SCC_PLL_REF_CLK_SRC_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_PLL_REF_CLK_SRC_SEL_ADDR,v)
#define HWIO_LPASS_SCC_PLL_REF_CLK_SRC_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_PLL_REF_CLK_SRC_SEL_ADDR,m,v,HWIO_LPASS_SCC_PLL_REF_CLK_SRC_SEL_IN)
#define HWIO_LPASS_SCC_PLL_REF_CLK_SRC_SEL_PLL_CLK_SRC_SEL_BMSK                                                              0x3
#define HWIO_LPASS_SCC_PLL_REF_CLK_SRC_SEL_PLL_CLK_SRC_SEL_SHFT                                                              0x0

#define HWIO_LPASS_SCC_100M_CMD_RCGR_ADDR                                                                             (LPASS_CC_REG_BASE      + 0x0003f000)
#define HWIO_LPASS_SCC_100M_CMD_RCGR_RMSK                                                                             0x800000f3
#define HWIO_LPASS_SCC_100M_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SCC_100M_CMD_RCGR_ADDR, HWIO_LPASS_SCC_100M_CMD_RCGR_RMSK)
#define HWIO_LPASS_SCC_100M_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_100M_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_SCC_100M_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_100M_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_SCC_100M_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_100M_CMD_RCGR_ADDR,m,v,HWIO_LPASS_SCC_100M_CMD_RCGR_IN)
#define HWIO_LPASS_SCC_100M_CMD_RCGR_ROOT_OFF_BMSK                                                                    0x80000000
#define HWIO_LPASS_SCC_100M_CMD_RCGR_ROOT_OFF_SHFT                                                                          0x1f
#define HWIO_LPASS_SCC_100M_CMD_RCGR_DIRTY_D_BMSK                                                                           0x80
#define HWIO_LPASS_SCC_100M_CMD_RCGR_DIRTY_D_SHFT                                                                            0x7
#define HWIO_LPASS_SCC_100M_CMD_RCGR_DIRTY_N_BMSK                                                                           0x40
#define HWIO_LPASS_SCC_100M_CMD_RCGR_DIRTY_N_SHFT                                                                            0x6
#define HWIO_LPASS_SCC_100M_CMD_RCGR_DIRTY_M_BMSK                                                                           0x20
#define HWIO_LPASS_SCC_100M_CMD_RCGR_DIRTY_M_SHFT                                                                            0x5
#define HWIO_LPASS_SCC_100M_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                    0x10
#define HWIO_LPASS_SCC_100M_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                     0x4
#define HWIO_LPASS_SCC_100M_CMD_RCGR_ROOT_EN_BMSK                                                                            0x2
#define HWIO_LPASS_SCC_100M_CMD_RCGR_ROOT_EN_SHFT                                                                            0x1
#define HWIO_LPASS_SCC_100M_CMD_RCGR_UPDATE_BMSK                                                                             0x1
#define HWIO_LPASS_SCC_100M_CMD_RCGR_UPDATE_SHFT                                                                             0x0

#define HWIO_LPASS_SCC_100M_CFG_RCGR_ADDR                                                                             (LPASS_CC_REG_BASE      + 0x0003f004)
#define HWIO_LPASS_SCC_100M_CFG_RCGR_RMSK                                                                                  0x71f
#define HWIO_LPASS_SCC_100M_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SCC_100M_CFG_RCGR_ADDR, HWIO_LPASS_SCC_100M_CFG_RCGR_RMSK)
#define HWIO_LPASS_SCC_100M_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_100M_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_SCC_100M_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_100M_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_SCC_100M_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_100M_CFG_RCGR_ADDR,m,v,HWIO_LPASS_SCC_100M_CFG_RCGR_IN)
#define HWIO_LPASS_SCC_100M_CFG_RCGR_SRC_SEL_BMSK                                                                          0x700
#define HWIO_LPASS_SCC_100M_CFG_RCGR_SRC_SEL_SHFT                                                                            0x8
#define HWIO_LPASS_SCC_100M_CFG_RCGR_SRC_DIV_BMSK                                                                           0x1f
#define HWIO_LPASS_SCC_100M_CFG_RCGR_SRC_DIV_SHFT                                                                            0x0

#define HWIO_LPASS_ISLAND_SCC_SPI_I2C1_BCR_ADDR                                                                       (LPASS_CC_REG_BASE      + 0x00040000)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C1_BCR_RMSK                                                                              0x1
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C1_BCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SPI_I2C1_BCR_ADDR, HWIO_LPASS_ISLAND_SCC_SPI_I2C1_BCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C1_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SPI_I2C1_BCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C1_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_SPI_I2C1_BCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C1_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_SPI_I2C1_BCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_SPI_I2C1_BCR_IN)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C1_BCR_BLK_ARES_BMSK                                                                     0x1
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C1_BCR_BLK_ARES_SHFT                                                                     0x0

#define HWIO_LPASS_ISLAND_SCC_SPI_I2C1_CLK_CDIV_REG_ADDR                                                              (LPASS_CC_REG_BASE      + 0x00040004)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C1_CLK_CDIV_REG_RMSK                                                                   0x1ff
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C1_CLK_CDIV_REG_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SPI_I2C1_CLK_CDIV_REG_ADDR, HWIO_LPASS_ISLAND_SCC_SPI_I2C1_CLK_CDIV_REG_RMSK)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C1_CLK_CDIV_REG_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SPI_I2C1_CLK_CDIV_REG_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C1_CLK_CDIV_REG_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_SPI_I2C1_CLK_CDIV_REG_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C1_CLK_CDIV_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_SPI_I2C1_CLK_CDIV_REG_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_SPI_I2C1_CLK_CDIV_REG_IN)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C1_CLK_CDIV_REG_CLK_DIV_BMSK                                                           0x1ff
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C1_CLK_CDIV_REG_CLK_DIV_SHFT                                                             0x0

#define HWIO_LPASS_ISLAND_SCC_QUP_SPI1_CBCR_ADDR                                                                      (LPASS_CC_REG_BASE      + 0x00040008)
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI1_CBCR_RMSK                                                                      0x80000001
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI1_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_QUP_SPI1_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_QUP_SPI1_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI1_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_QUP_SPI1_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI1_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_QUP_SPI1_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI1_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_QUP_SPI1_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_QUP_SPI1_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI1_CBCR_CLK_OFF_BMSK                                                              0x80000000
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI1_CBCR_CLK_OFF_SHFT                                                                    0x1f
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI1_CBCR_CLK_ENABLE_BMSK                                                                  0x1
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI1_CBCR_CLK_ENABLE_SHFT                                                                  0x0

#define HWIO_LPASS_ISLAND_SCC_QUP_I2C1_CBCR_ADDR                                                                      (LPASS_CC_REG_BASE      + 0x0004000c)
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C1_CBCR_RMSK                                                                      0x80000001
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C1_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_QUP_I2C1_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_QUP_I2C1_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C1_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_QUP_I2C1_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C1_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_QUP_I2C1_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C1_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_QUP_I2C1_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_QUP_I2C1_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C1_CBCR_CLK_OFF_BMSK                                                              0x80000000
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C1_CBCR_CLK_OFF_SHFT                                                                    0x1f
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C1_CBCR_CLK_ENABLE_BMSK                                                                  0x1
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C1_CBCR_CLK_ENABLE_SHFT                                                                  0x0

#define HWIO_LPASS_ISLAND_SCC_SPI_I2C2_BCR_ADDR                                                                       (LPASS_CC_REG_BASE      + 0x00041000)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C2_BCR_RMSK                                                                              0x1
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C2_BCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SPI_I2C2_BCR_ADDR, HWIO_LPASS_ISLAND_SCC_SPI_I2C2_BCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C2_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SPI_I2C2_BCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C2_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_SPI_I2C2_BCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C2_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_SPI_I2C2_BCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_SPI_I2C2_BCR_IN)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C2_BCR_BLK_ARES_BMSK                                                                     0x1
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C2_BCR_BLK_ARES_SHFT                                                                     0x0

#define HWIO_LPASS_ISLAND_SCC_SPI_I2C2_CLK_CDIV_REG_ADDR                                                              (LPASS_CC_REG_BASE      + 0x00041004)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C2_CLK_CDIV_REG_RMSK                                                                   0x1ff
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C2_CLK_CDIV_REG_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SPI_I2C2_CLK_CDIV_REG_ADDR, HWIO_LPASS_ISLAND_SCC_SPI_I2C2_CLK_CDIV_REG_RMSK)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C2_CLK_CDIV_REG_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SPI_I2C2_CLK_CDIV_REG_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C2_CLK_CDIV_REG_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_SPI_I2C2_CLK_CDIV_REG_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C2_CLK_CDIV_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_SPI_I2C2_CLK_CDIV_REG_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_SPI_I2C2_CLK_CDIV_REG_IN)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C2_CLK_CDIV_REG_CLK_DIV_BMSK                                                           0x1ff
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C2_CLK_CDIV_REG_CLK_DIV_SHFT                                                             0x0

#define HWIO_LPASS_ISLAND_SCC_QUP_SPI2_CBCR_ADDR                                                                      (LPASS_CC_REG_BASE      + 0x00041008)
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI2_CBCR_RMSK                                                                      0x80000001
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI2_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_QUP_SPI2_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_QUP_SPI2_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI2_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_QUP_SPI2_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI2_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_QUP_SPI2_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI2_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_QUP_SPI2_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_QUP_SPI2_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI2_CBCR_CLK_OFF_BMSK                                                              0x80000000
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI2_CBCR_CLK_OFF_SHFT                                                                    0x1f
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI2_CBCR_CLK_ENABLE_BMSK                                                                  0x1
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI2_CBCR_CLK_ENABLE_SHFT                                                                  0x0

#define HWIO_LPASS_ISLAND_SCC_QUP_I2C2_CBCR_ADDR                                                                      (LPASS_CC_REG_BASE      + 0x0004100c)
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C2_CBCR_RMSK                                                                      0x80000001
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C2_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_QUP_I2C2_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_QUP_I2C2_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C2_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_QUP_I2C2_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C2_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_QUP_I2C2_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C2_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_QUP_I2C2_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_QUP_I2C2_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C2_CBCR_CLK_OFF_BMSK                                                              0x80000000
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C2_CBCR_CLK_OFF_SHFT                                                                    0x1f
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C2_CBCR_CLK_ENABLE_BMSK                                                                  0x1
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C2_CBCR_CLK_ENABLE_SHFT                                                                  0x0

#define HWIO_LPASS_ISLAND_SCC_SPI_I2C3_BCR_ADDR                                                                       (LPASS_CC_REG_BASE      + 0x00042000)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C3_BCR_RMSK                                                                              0x1
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C3_BCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SPI_I2C3_BCR_ADDR, HWIO_LPASS_ISLAND_SCC_SPI_I2C3_BCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C3_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SPI_I2C3_BCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C3_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_SPI_I2C3_BCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C3_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_SPI_I2C3_BCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_SPI_I2C3_BCR_IN)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C3_BCR_BLK_ARES_BMSK                                                                     0x1
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C3_BCR_BLK_ARES_SHFT                                                                     0x0

#define HWIO_LPASS_ISLAND_SCC_SPI_I2C3_CLK_CDIV_REG_ADDR                                                              (LPASS_CC_REG_BASE      + 0x00042004)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C3_CLK_CDIV_REG_RMSK                                                                   0x1ff
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C3_CLK_CDIV_REG_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SPI_I2C3_CLK_CDIV_REG_ADDR, HWIO_LPASS_ISLAND_SCC_SPI_I2C3_CLK_CDIV_REG_RMSK)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C3_CLK_CDIV_REG_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SPI_I2C3_CLK_CDIV_REG_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C3_CLK_CDIV_REG_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_SPI_I2C3_CLK_CDIV_REG_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C3_CLK_CDIV_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_SPI_I2C3_CLK_CDIV_REG_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_SPI_I2C3_CLK_CDIV_REG_IN)
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C3_CLK_CDIV_REG_CLK_DIV_BMSK                                                           0x1ff
#define HWIO_LPASS_ISLAND_SCC_SPI_I2C3_CLK_CDIV_REG_CLK_DIV_SHFT                                                             0x0

#define HWIO_LPASS_ISLAND_SCC_QUP_SPI3_CBCR_ADDR                                                                      (LPASS_CC_REG_BASE      + 0x00042008)
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI3_CBCR_RMSK                                                                      0x80000001
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI3_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_QUP_SPI3_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_QUP_SPI3_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI3_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_QUP_SPI3_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI3_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_QUP_SPI3_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI3_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_QUP_SPI3_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_QUP_SPI3_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI3_CBCR_CLK_OFF_BMSK                                                              0x80000000
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI3_CBCR_CLK_OFF_SHFT                                                                    0x1f
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI3_CBCR_CLK_ENABLE_BMSK                                                                  0x1
#define HWIO_LPASS_ISLAND_SCC_QUP_SPI3_CBCR_CLK_ENABLE_SHFT                                                                  0x0

#define HWIO_LPASS_ISLAND_SCC_QUP_I2C3_CBCR_ADDR                                                                      (LPASS_CC_REG_BASE      + 0x0004200c)
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C3_CBCR_RMSK                                                                      0x80000001
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C3_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_QUP_I2C3_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_QUP_I2C3_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C3_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_QUP_I2C3_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C3_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_QUP_I2C3_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C3_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_QUP_I2C3_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_QUP_I2C3_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C3_CBCR_CLK_OFF_BMSK                                                              0x80000000
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C3_CBCR_CLK_OFF_SHFT                                                                    0x1f
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C3_CBCR_CLK_ENABLE_BMSK                                                                  0x1
#define HWIO_LPASS_ISLAND_SCC_QUP_I2C3_CBCR_CLK_ENABLE_SHFT                                                                  0x0

#define HWIO_LPASS_ISLAND_SCC_UART1_BCR_ADDR                                                                          (LPASS_CC_REG_BASE      + 0x00043000)
#define HWIO_LPASS_ISLAND_SCC_UART1_BCR_RMSK                                                                                 0x1
#define HWIO_LPASS_ISLAND_SCC_UART1_BCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_UART1_BCR_ADDR, HWIO_LPASS_ISLAND_SCC_UART1_BCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_UART1_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_UART1_BCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_UART1_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_UART1_BCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_UART1_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_UART1_BCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_UART1_BCR_IN)
#define HWIO_LPASS_ISLAND_SCC_UART1_BCR_BLK_ARES_BMSK                                                                        0x1
#define HWIO_LPASS_ISLAND_SCC_UART1_BCR_BLK_ARES_SHFT                                                                        0x0

#define HWIO_LPASS_SCC_UART1_CMD_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00043004)
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_RMSK                                                                            0x800000f3
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART1_CMD_RCGR_ADDR, HWIO_LPASS_SCC_UART1_CMD_RCGR_RMSK)
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART1_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART1_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART1_CMD_RCGR_ADDR,m,v,HWIO_LPASS_SCC_UART1_CMD_RCGR_IN)
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_ROOT_OFF_BMSK                                                                   0x80000000
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_ROOT_OFF_SHFT                                                                         0x1f
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_DIRTY_D_BMSK                                                                          0x80
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_DIRTY_D_SHFT                                                                           0x7
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_DIRTY_N_BMSK                                                                          0x40
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_DIRTY_N_SHFT                                                                           0x6
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_DIRTY_M_BMSK                                                                          0x20
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_DIRTY_M_SHFT                                                                           0x5
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                   0x10
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                    0x4
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_ROOT_EN_BMSK                                                                           0x2
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_ROOT_EN_SHFT                                                                           0x1
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_UPDATE_BMSK                                                                            0x1
#define HWIO_LPASS_SCC_UART1_CMD_RCGR_UPDATE_SHFT                                                                            0x0

#define HWIO_LPASS_SCC_UART1_CFG_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00043008)
#define HWIO_LPASS_SCC_UART1_CFG_RCGR_RMSK                                                                                0x771f
#define HWIO_LPASS_SCC_UART1_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART1_CFG_RCGR_ADDR, HWIO_LPASS_SCC_UART1_CFG_RCGR_RMSK)
#define HWIO_LPASS_SCC_UART1_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART1_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_SCC_UART1_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART1_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_SCC_UART1_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART1_CFG_RCGR_ADDR,m,v,HWIO_LPASS_SCC_UART1_CFG_RCGR_IN)
#define HWIO_LPASS_SCC_UART1_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                    0x4000
#define HWIO_LPASS_SCC_UART1_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                       0xe
#define HWIO_LPASS_SCC_UART1_CFG_RCGR_MODE_BMSK                                                                           0x3000
#define HWIO_LPASS_SCC_UART1_CFG_RCGR_MODE_SHFT                                                                              0xc
#define HWIO_LPASS_SCC_UART1_CFG_RCGR_SRC_SEL_BMSK                                                                         0x700
#define HWIO_LPASS_SCC_UART1_CFG_RCGR_SRC_SEL_SHFT                                                                           0x8
#define HWIO_LPASS_SCC_UART1_CFG_RCGR_SRC_DIV_BMSK                                                                          0x1f
#define HWIO_LPASS_SCC_UART1_CFG_RCGR_SRC_DIV_SHFT                                                                           0x0

#define HWIO_LPASS_SCC_UART1_M_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x0004300c)
#define HWIO_LPASS_SCC_UART1_M_RMSK                                                                                       0xffff
#define HWIO_LPASS_SCC_UART1_M_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART1_M_ADDR, HWIO_LPASS_SCC_UART1_M_RMSK)
#define HWIO_LPASS_SCC_UART1_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART1_M_ADDR, m)
#define HWIO_LPASS_SCC_UART1_M_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART1_M_ADDR,v)
#define HWIO_LPASS_SCC_UART1_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART1_M_ADDR,m,v,HWIO_LPASS_SCC_UART1_M_IN)
#define HWIO_LPASS_SCC_UART1_M_M_BMSK                                                                                     0xffff
#define HWIO_LPASS_SCC_UART1_M_M_SHFT                                                                                        0x0

#define HWIO_LPASS_SCC_UART1_N_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00043010)
#define HWIO_LPASS_SCC_UART1_N_RMSK                                                                                       0xffff
#define HWIO_LPASS_SCC_UART1_N_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART1_N_ADDR, HWIO_LPASS_SCC_UART1_N_RMSK)
#define HWIO_LPASS_SCC_UART1_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART1_N_ADDR, m)
#define HWIO_LPASS_SCC_UART1_N_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART1_N_ADDR,v)
#define HWIO_LPASS_SCC_UART1_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART1_N_ADDR,m,v,HWIO_LPASS_SCC_UART1_N_IN)
#define HWIO_LPASS_SCC_UART1_N_NOT_N_MINUS_M_BMSK                                                                         0xffff
#define HWIO_LPASS_SCC_UART1_N_NOT_N_MINUS_M_SHFT                                                                            0x0

#define HWIO_LPASS_SCC_UART1_D_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00043014)
#define HWIO_LPASS_SCC_UART1_D_RMSK                                                                                       0xffff
#define HWIO_LPASS_SCC_UART1_D_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART1_D_ADDR, HWIO_LPASS_SCC_UART1_D_RMSK)
#define HWIO_LPASS_SCC_UART1_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART1_D_ADDR, m)
#define HWIO_LPASS_SCC_UART1_D_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART1_D_ADDR,v)
#define HWIO_LPASS_SCC_UART1_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART1_D_ADDR,m,v,HWIO_LPASS_SCC_UART1_D_IN)
#define HWIO_LPASS_SCC_UART1_D_NOT_2D_BMSK                                                                                0xffff
#define HWIO_LPASS_SCC_UART1_D_NOT_2D_SHFT                                                                                   0x0

#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART1_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x00043018)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART1_CBCR_RMSK                                                                 0x80000001
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART1_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_UART_DM_UART1_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_UART_DM_UART1_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART1_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_UART_DM_UART1_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART1_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_UART_DM_UART1_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART1_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_UART_DM_UART1_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_UART_DM_UART1_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART1_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART1_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART1_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART1_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_ISLAND_SCC_UART2_BCR_ADDR                                                                          (LPASS_CC_REG_BASE      + 0x00044000)
#define HWIO_LPASS_ISLAND_SCC_UART2_BCR_RMSK                                                                                 0x1
#define HWIO_LPASS_ISLAND_SCC_UART2_BCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_UART2_BCR_ADDR, HWIO_LPASS_ISLAND_SCC_UART2_BCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_UART2_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_UART2_BCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_UART2_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_UART2_BCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_UART2_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_UART2_BCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_UART2_BCR_IN)
#define HWIO_LPASS_ISLAND_SCC_UART2_BCR_BLK_ARES_BMSK                                                                        0x1
#define HWIO_LPASS_ISLAND_SCC_UART2_BCR_BLK_ARES_SHFT                                                                        0x0

#define HWIO_LPASS_SCC_UART2_CMD_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00044004)
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_RMSK                                                                            0x800000f3
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART2_CMD_RCGR_ADDR, HWIO_LPASS_SCC_UART2_CMD_RCGR_RMSK)
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART2_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART2_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART2_CMD_RCGR_ADDR,m,v,HWIO_LPASS_SCC_UART2_CMD_RCGR_IN)
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_ROOT_OFF_BMSK                                                                   0x80000000
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_ROOT_OFF_SHFT                                                                         0x1f
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_DIRTY_D_BMSK                                                                          0x80
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_DIRTY_D_SHFT                                                                           0x7
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_DIRTY_N_BMSK                                                                          0x40
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_DIRTY_N_SHFT                                                                           0x6
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_DIRTY_M_BMSK                                                                          0x20
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_DIRTY_M_SHFT                                                                           0x5
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                   0x10
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                    0x4
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_ROOT_EN_BMSK                                                                           0x2
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_ROOT_EN_SHFT                                                                           0x1
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_UPDATE_BMSK                                                                            0x1
#define HWIO_LPASS_SCC_UART2_CMD_RCGR_UPDATE_SHFT                                                                            0x0

#define HWIO_LPASS_SCC_UART2_CFG_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00044008)
#define HWIO_LPASS_SCC_UART2_CFG_RCGR_RMSK                                                                                0x771f
#define HWIO_LPASS_SCC_UART2_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART2_CFG_RCGR_ADDR, HWIO_LPASS_SCC_UART2_CFG_RCGR_RMSK)
#define HWIO_LPASS_SCC_UART2_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART2_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_SCC_UART2_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART2_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_SCC_UART2_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART2_CFG_RCGR_ADDR,m,v,HWIO_LPASS_SCC_UART2_CFG_RCGR_IN)
#define HWIO_LPASS_SCC_UART2_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                    0x4000
#define HWIO_LPASS_SCC_UART2_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                       0xe
#define HWIO_LPASS_SCC_UART2_CFG_RCGR_MODE_BMSK                                                                           0x3000
#define HWIO_LPASS_SCC_UART2_CFG_RCGR_MODE_SHFT                                                                              0xc
#define HWIO_LPASS_SCC_UART2_CFG_RCGR_SRC_SEL_BMSK                                                                         0x700
#define HWIO_LPASS_SCC_UART2_CFG_RCGR_SRC_SEL_SHFT                                                                           0x8
#define HWIO_LPASS_SCC_UART2_CFG_RCGR_SRC_DIV_BMSK                                                                          0x1f
#define HWIO_LPASS_SCC_UART2_CFG_RCGR_SRC_DIV_SHFT                                                                           0x0

#define HWIO_LPASS_SCC_UART2_M_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x0004400c)
#define HWIO_LPASS_SCC_UART2_M_RMSK                                                                                       0xffff
#define HWIO_LPASS_SCC_UART2_M_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART2_M_ADDR, HWIO_LPASS_SCC_UART2_M_RMSK)
#define HWIO_LPASS_SCC_UART2_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART2_M_ADDR, m)
#define HWIO_LPASS_SCC_UART2_M_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART2_M_ADDR,v)
#define HWIO_LPASS_SCC_UART2_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART2_M_ADDR,m,v,HWIO_LPASS_SCC_UART2_M_IN)
#define HWIO_LPASS_SCC_UART2_M_M_BMSK                                                                                     0xffff
#define HWIO_LPASS_SCC_UART2_M_M_SHFT                                                                                        0x0

#define HWIO_LPASS_SCC_UART2_N_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00044010)
#define HWIO_LPASS_SCC_UART2_N_RMSK                                                                                       0xffff
#define HWIO_LPASS_SCC_UART2_N_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART2_N_ADDR, HWIO_LPASS_SCC_UART2_N_RMSK)
#define HWIO_LPASS_SCC_UART2_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART2_N_ADDR, m)
#define HWIO_LPASS_SCC_UART2_N_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART2_N_ADDR,v)
#define HWIO_LPASS_SCC_UART2_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART2_N_ADDR,m,v,HWIO_LPASS_SCC_UART2_N_IN)
#define HWIO_LPASS_SCC_UART2_N_NOT_N_MINUS_M_BMSK                                                                         0xffff
#define HWIO_LPASS_SCC_UART2_N_NOT_N_MINUS_M_SHFT                                                                            0x0

#define HWIO_LPASS_SCC_UART2_D_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00044014)
#define HWIO_LPASS_SCC_UART2_D_RMSK                                                                                       0xffff
#define HWIO_LPASS_SCC_UART2_D_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART2_D_ADDR, HWIO_LPASS_SCC_UART2_D_RMSK)
#define HWIO_LPASS_SCC_UART2_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART2_D_ADDR, m)
#define HWIO_LPASS_SCC_UART2_D_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART2_D_ADDR,v)
#define HWIO_LPASS_SCC_UART2_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART2_D_ADDR,m,v,HWIO_LPASS_SCC_UART2_D_IN)
#define HWIO_LPASS_SCC_UART2_D_NOT_2D_BMSK                                                                                0xffff
#define HWIO_LPASS_SCC_UART2_D_NOT_2D_SHFT                                                                                   0x0

#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART2_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x00044018)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART2_CBCR_RMSK                                                                 0x80000001
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART2_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_UART_DM_UART2_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_UART_DM_UART2_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART2_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_UART_DM_UART2_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART2_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_UART_DM_UART2_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART2_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_UART_DM_UART2_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_UART_DM_UART2_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART2_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART2_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART2_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART2_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_ISLAND_SCC_UART3_BCR_ADDR                                                                          (LPASS_CC_REG_BASE      + 0x00045000)
#define HWIO_LPASS_ISLAND_SCC_UART3_BCR_RMSK                                                                                 0x1
#define HWIO_LPASS_ISLAND_SCC_UART3_BCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_UART3_BCR_ADDR, HWIO_LPASS_ISLAND_SCC_UART3_BCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_UART3_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_UART3_BCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_UART3_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_UART3_BCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_UART3_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_UART3_BCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_UART3_BCR_IN)
#define HWIO_LPASS_ISLAND_SCC_UART3_BCR_BLK_ARES_BMSK                                                                        0x1
#define HWIO_LPASS_ISLAND_SCC_UART3_BCR_BLK_ARES_SHFT                                                                        0x0

#define HWIO_LPASS_SCC_UART3_CMD_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00045004)
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_RMSK                                                                            0x800000f3
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART3_CMD_RCGR_ADDR, HWIO_LPASS_SCC_UART3_CMD_RCGR_RMSK)
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART3_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART3_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART3_CMD_RCGR_ADDR,m,v,HWIO_LPASS_SCC_UART3_CMD_RCGR_IN)
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_ROOT_OFF_BMSK                                                                   0x80000000
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_ROOT_OFF_SHFT                                                                         0x1f
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_DIRTY_D_BMSK                                                                          0x80
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_DIRTY_D_SHFT                                                                           0x7
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_DIRTY_N_BMSK                                                                          0x40
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_DIRTY_N_SHFT                                                                           0x6
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_DIRTY_M_BMSK                                                                          0x20
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_DIRTY_M_SHFT                                                                           0x5
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                   0x10
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                    0x4
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_ROOT_EN_BMSK                                                                           0x2
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_ROOT_EN_SHFT                                                                           0x1
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_UPDATE_BMSK                                                                            0x1
#define HWIO_LPASS_SCC_UART3_CMD_RCGR_UPDATE_SHFT                                                                            0x0

#define HWIO_LPASS_SCC_UART3_CFG_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00045008)
#define HWIO_LPASS_SCC_UART3_CFG_RCGR_RMSK                                                                                0x771f
#define HWIO_LPASS_SCC_UART3_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART3_CFG_RCGR_ADDR, HWIO_LPASS_SCC_UART3_CFG_RCGR_RMSK)
#define HWIO_LPASS_SCC_UART3_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART3_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_SCC_UART3_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART3_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_SCC_UART3_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART3_CFG_RCGR_ADDR,m,v,HWIO_LPASS_SCC_UART3_CFG_RCGR_IN)
#define HWIO_LPASS_SCC_UART3_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                    0x4000
#define HWIO_LPASS_SCC_UART3_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                       0xe
#define HWIO_LPASS_SCC_UART3_CFG_RCGR_MODE_BMSK                                                                           0x3000
#define HWIO_LPASS_SCC_UART3_CFG_RCGR_MODE_SHFT                                                                              0xc
#define HWIO_LPASS_SCC_UART3_CFG_RCGR_SRC_SEL_BMSK                                                                         0x700
#define HWIO_LPASS_SCC_UART3_CFG_RCGR_SRC_SEL_SHFT                                                                           0x8
#define HWIO_LPASS_SCC_UART3_CFG_RCGR_SRC_DIV_BMSK                                                                          0x1f
#define HWIO_LPASS_SCC_UART3_CFG_RCGR_SRC_DIV_SHFT                                                                           0x0

#define HWIO_LPASS_SCC_UART3_M_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x0004500c)
#define HWIO_LPASS_SCC_UART3_M_RMSK                                                                                       0xffff
#define HWIO_LPASS_SCC_UART3_M_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART3_M_ADDR, HWIO_LPASS_SCC_UART3_M_RMSK)
#define HWIO_LPASS_SCC_UART3_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART3_M_ADDR, m)
#define HWIO_LPASS_SCC_UART3_M_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART3_M_ADDR,v)
#define HWIO_LPASS_SCC_UART3_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART3_M_ADDR,m,v,HWIO_LPASS_SCC_UART3_M_IN)
#define HWIO_LPASS_SCC_UART3_M_M_BMSK                                                                                     0xffff
#define HWIO_LPASS_SCC_UART3_M_M_SHFT                                                                                        0x0

#define HWIO_LPASS_SCC_UART3_N_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00045010)
#define HWIO_LPASS_SCC_UART3_N_RMSK                                                                                       0xffff
#define HWIO_LPASS_SCC_UART3_N_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART3_N_ADDR, HWIO_LPASS_SCC_UART3_N_RMSK)
#define HWIO_LPASS_SCC_UART3_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART3_N_ADDR, m)
#define HWIO_LPASS_SCC_UART3_N_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART3_N_ADDR,v)
#define HWIO_LPASS_SCC_UART3_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART3_N_ADDR,m,v,HWIO_LPASS_SCC_UART3_N_IN)
#define HWIO_LPASS_SCC_UART3_N_NOT_N_MINUS_M_BMSK                                                                         0xffff
#define HWIO_LPASS_SCC_UART3_N_NOT_N_MINUS_M_SHFT                                                                            0x0

#define HWIO_LPASS_SCC_UART3_D_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00045014)
#define HWIO_LPASS_SCC_UART3_D_RMSK                                                                                       0xffff
#define HWIO_LPASS_SCC_UART3_D_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART3_D_ADDR, HWIO_LPASS_SCC_UART3_D_RMSK)
#define HWIO_LPASS_SCC_UART3_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART3_D_ADDR, m)
#define HWIO_LPASS_SCC_UART3_D_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART3_D_ADDR,v)
#define HWIO_LPASS_SCC_UART3_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART3_D_ADDR,m,v,HWIO_LPASS_SCC_UART3_D_IN)
#define HWIO_LPASS_SCC_UART3_D_NOT_2D_BMSK                                                                                0xffff
#define HWIO_LPASS_SCC_UART3_D_NOT_2D_SHFT                                                                                   0x0

#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART3_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x00045018)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART3_CBCR_RMSK                                                                 0x80000001
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART3_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_UART_DM_UART3_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_UART_DM_UART3_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART3_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_UART_DM_UART3_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART3_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_UART_DM_UART3_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART3_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_UART_DM_UART3_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_UART_DM_UART3_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART3_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART3_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART3_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART3_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_ISLAND_SCC_BUS_BCR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00046000)
#define HWIO_LPASS_ISLAND_SCC_BUS_BCR_RMSK                                                                                   0x1
#define HWIO_LPASS_ISLAND_SCC_BUS_BCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_BUS_BCR_ADDR, HWIO_LPASS_ISLAND_SCC_BUS_BCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_BUS_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_BUS_BCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_BUS_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_BUS_BCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_BUS_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_BUS_BCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_BUS_BCR_IN)
#define HWIO_LPASS_ISLAND_SCC_BUS_BCR_BLK_ARES_BMSK                                                                          0x1
#define HWIO_LPASS_ISLAND_SCC_BUS_BCR_BLK_ARES_SHFT                                                                          0x0

#define HWIO_LPASS_ISLAND_SCC_BUS_CLK_CDIV_REG_ADDR                                                                   (LPASS_CC_REG_BASE      + 0x00046004)
#define HWIO_LPASS_ISLAND_SCC_BUS_CLK_CDIV_REG_RMSK                                                                      0x70000
#define HWIO_LPASS_ISLAND_SCC_BUS_CLK_CDIV_REG_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_BUS_CLK_CDIV_REG_ADDR, HWIO_LPASS_ISLAND_SCC_BUS_CLK_CDIV_REG_RMSK)
#define HWIO_LPASS_ISLAND_SCC_BUS_CLK_CDIV_REG_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_BUS_CLK_CDIV_REG_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_BUS_CLK_CDIV_REG_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_BUS_CLK_CDIV_REG_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_BUS_CLK_CDIV_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_BUS_CLK_CDIV_REG_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_BUS_CLK_CDIV_REG_IN)
#define HWIO_LPASS_ISLAND_SCC_BUS_CLK_CDIV_REG_CLK_DIV_BMSK                                                              0x70000
#define HWIO_LPASS_ISLAND_SCC_BUS_CLK_CDIV_REG_CLK_DIV_SHFT                                                                 0x10

#define HWIO_LPASS_ISLAND_SCC_CRIF_AON_CBCR_ADDR                                                                      (LPASS_CC_REG_BASE      + 0x00046008)
#define HWIO_LPASS_ISLAND_SCC_CRIF_AON_CBCR_RMSK                                                                      0x80000000
#define HWIO_LPASS_ISLAND_SCC_CRIF_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_CRIF_AON_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_CRIF_AON_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_CRIF_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_CRIF_AON_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_CRIF_AON_CBCR_CLK_OFF_BMSK                                                              0x80000000
#define HWIO_LPASS_ISLAND_SCC_CRIF_AON_CBCR_CLK_OFF_SHFT                                                                    0x1f

#define HWIO_LPASS_ISLAND_SCC_CSR_H_AON_CBCR_ADDR                                                                     (LPASS_CC_REG_BASE      + 0x0004600c)
#define HWIO_LPASS_ISLAND_SCC_CSR_H_AON_CBCR_RMSK                                                                     0x80000000
#define HWIO_LPASS_ISLAND_SCC_CSR_H_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_CSR_H_AON_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_CSR_H_AON_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_CSR_H_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_CSR_H_AON_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_CSR_H_AON_CBCR_CLK_OFF_BMSK                                                             0x80000000
#define HWIO_LPASS_ISLAND_SCC_CSR_H_AON_CBCR_CLK_OFF_SHFT                                                                   0x1f

#define HWIO_LPASS_ISLAND_SCC_DATA_H_AON_CBCR_ADDR                                                                    (LPASS_CC_REG_BASE      + 0x00046010)
#define HWIO_LPASS_ISLAND_SCC_DATA_H_AON_CBCR_RMSK                                                                    0x80000001
#define HWIO_LPASS_ISLAND_SCC_DATA_H_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_DATA_H_AON_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_DATA_H_AON_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_DATA_H_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_DATA_H_AON_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_DATA_H_AON_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_DATA_H_AON_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_DATA_H_AON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_DATA_H_AON_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_DATA_H_AON_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_DATA_H_AON_CBCR_CLK_OFF_BMSK                                                            0x80000000
#define HWIO_LPASS_ISLAND_SCC_DATA_H_AON_CBCR_CLK_OFF_SHFT                                                                  0x1f
#define HWIO_LPASS_ISLAND_SCC_DATA_H_AON_CBCR_CLK_ENABLE_BMSK                                                                0x1
#define HWIO_LPASS_ISLAND_SCC_DATA_H_AON_CBCR_CLK_ENABLE_SHFT                                                                0x0

#define HWIO_LPASS_ISLAND_SCC_CFG_AHB_AON_CBCR_ADDR                                                                   (LPASS_CC_REG_BASE      + 0x00046014)
#define HWIO_LPASS_ISLAND_SCC_CFG_AHB_AON_CBCR_RMSK                                                                   0x80000000
#define HWIO_LPASS_ISLAND_SCC_CFG_AHB_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_CFG_AHB_AON_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_CFG_AHB_AON_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_CFG_AHB_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_CFG_AHB_AON_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_CFG_AHB_AON_CBCR_CLK_OFF_BMSK                                                           0x80000000
#define HWIO_LPASS_ISLAND_SCC_CFG_AHB_AON_CBCR_CLK_OFF_SHFT                                                                 0x1f

#define HWIO_LPASS_ISLAND_SCC_Q6_AHB_BCR_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00046018)
#define HWIO_LPASS_ISLAND_SCC_Q6_AHB_BCR_RMSK                                                                                0x1
#define HWIO_LPASS_ISLAND_SCC_Q6_AHB_BCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_Q6_AHB_BCR_ADDR, HWIO_LPASS_ISLAND_SCC_Q6_AHB_BCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_Q6_AHB_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_Q6_AHB_BCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_Q6_AHB_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_Q6_AHB_BCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_Q6_AHB_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_Q6_AHB_BCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_Q6_AHB_BCR_IN)
#define HWIO_LPASS_ISLAND_SCC_Q6_AHB_BCR_BLK_ARES_BMSK                                                                       0x1
#define HWIO_LPASS_ISLAND_SCC_Q6_AHB_BCR_BLK_ARES_SHFT                                                                       0x0

#define HWIO_LPASS_ISLAND_SCC_Q6_XPU2_CONFIG_BCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x0004601c)
#define HWIO_LPASS_ISLAND_SCC_Q6_XPU2_CONFIG_BCR_RMSK                                                                        0x1
#define HWIO_LPASS_ISLAND_SCC_Q6_XPU2_CONFIG_BCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_Q6_XPU2_CONFIG_BCR_ADDR, HWIO_LPASS_ISLAND_SCC_Q6_XPU2_CONFIG_BCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_Q6_XPU2_CONFIG_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_Q6_XPU2_CONFIG_BCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_Q6_XPU2_CONFIG_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_Q6_XPU2_CONFIG_BCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_Q6_XPU2_CONFIG_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_Q6_XPU2_CONFIG_BCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_Q6_XPU2_CONFIG_BCR_IN)
#define HWIO_LPASS_ISLAND_SCC_Q6_XPU2_CONFIG_BCR_BLK_ARES_BMSK                                                               0x1
#define HWIO_LPASS_ISLAND_SCC_Q6_XPU2_CONFIG_BCR_BLK_ARES_SHFT                                                               0x0

#define HWIO_LPASS_ISLAND_SCC_QDSP_SWAY_AON_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x00046020)
#define HWIO_LPASS_ISLAND_SCC_QDSP_SWAY_AON_CBCR_RMSK                                                                 0x80000000
#define HWIO_LPASS_ISLAND_SCC_QDSP_SWAY_AON_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_QDSP_SWAY_AON_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_QDSP_SWAY_AON_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_QDSP_SWAY_AON_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_QDSP_SWAY_AON_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_QDSP_SWAY_AON_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_ISLAND_SCC_QDSP_SWAY_AON_CBCR_CLK_OFF_SHFT                                                               0x1f

#define HWIO_LPASS_ISLAND_SCC_BLSP_BCR_ADDR                                                                           (LPASS_CC_REG_BASE      + 0x00047000)
#define HWIO_LPASS_ISLAND_SCC_BLSP_BCR_RMSK                                                                                  0x1
#define HWIO_LPASS_ISLAND_SCC_BLSP_BCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_BLSP_BCR_ADDR, HWIO_LPASS_ISLAND_SCC_BLSP_BCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_BLSP_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_BLSP_BCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_BLSP_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_BLSP_BCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_BLSP_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_BLSP_BCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_BLSP_BCR_IN)
#define HWIO_LPASS_ISLAND_SCC_BLSP_BCR_BLK_ARES_BMSK                                                                         0x1
#define HWIO_LPASS_ISLAND_SCC_BLSP_BCR_BLK_ARES_SHFT                                                                         0x0

#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_ADDR                                                                   (LPASS_CC_REG_BASE      + 0x00047004)
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_RMSK                                                                   0x80007ff1
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_CLK_OFF_BMSK                                                           0x80000000
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_CLK_OFF_SHFT                                                                 0x1f
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                                                     0x4000
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                                        0xe
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                                   0x2000
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                      0xd
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                                  0x1000
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                     0xc
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_WAKEUP_BMSK                                                                 0xf00
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_WAKEUP_SHFT                                                                   0x8
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_SLEEP_BMSK                                                                   0xf0
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_SLEEP_SHFT                                                                    0x4
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_CLK_ENABLE_BMSK                                                               0x1
#define HWIO_LPASS_ISLAND_SCC_BLSP_H_CORE_CBCR_CLK_ENABLE_SHFT                                                               0x0

#define HWIO_LPASS_ISLAND_SCC_SMEM_BCR_ADDR                                                                           (LPASS_CC_REG_BASE      + 0x00047008)
#define HWIO_LPASS_ISLAND_SCC_SMEM_BCR_RMSK                                                                                  0x1
#define HWIO_LPASS_ISLAND_SCC_SMEM_BCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SMEM_BCR_ADDR, HWIO_LPASS_ISLAND_SCC_SMEM_BCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_SMEM_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SMEM_BCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_SMEM_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_SMEM_BCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_SMEM_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_SMEM_BCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_SMEM_BCR_IN)
#define HWIO_LPASS_ISLAND_SCC_SMEM_BCR_BLK_ARES_BMSK                                                                         0x1
#define HWIO_LPASS_ISLAND_SCC_SMEM_BCR_BLK_ARES_SHFT                                                                         0x0

#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_ADDR                                                                     (LPASS_CC_REG_BASE      + 0x0004700c)
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_RMSK                                                                     0x80007ff1
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_CLK_OFF_BMSK                                                             0x80000000
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_CLK_OFF_SHFT                                                                   0x1f
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                                                       0x4000
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                                          0xe
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                                     0x2000
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                        0xd
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                                    0x1000
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                       0xc
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_WAKEUP_BMSK                                                                   0xf00
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_WAKEUP_SHFT                                                                     0x8
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_SLEEP_BMSK                                                                     0xf0
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_SLEEP_SHFT                                                                      0x4
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_CLK_ENABLE_BMSK                                                                 0x1
#define HWIO_LPASS_ISLAND_SCC_SMEM_CORE_CBCR_CLK_ENABLE_SHFT                                                                 0x0

#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_ADDR                                                                (LPASS_CC_REG_BASE      + 0x00047010)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_RMSK                                                                0x80007ff3
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_CLK_OFF_BMSK                                                        0x80000000
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_CLK_OFF_SHFT                                                              0x1f
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                                                  0x4000
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                                     0xe
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                                0x2000
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                   0xd
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                               0x1000
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                  0xc
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_WAKEUP_BMSK                                                              0xf00
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_WAKEUP_SHFT                                                                0x8
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_SLEEP_BMSK                                                                0xf0
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_SLEEP_SHFT                                                                 0x4
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_HW_CTL_BMSK                                                                0x2
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_HW_CTL_SHFT                                                                0x1
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_CLK_ENABLE_BMSK                                                            0x1
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM0_CORE_CBCR_CLK_ENABLE_SHFT                                                            0x0

#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_ADDR                                                                (LPASS_CC_REG_BASE      + 0x00047014)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_RMSK                                                                0x80007ff3
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_CLK_OFF_BMSK                                                        0x80000000
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_CLK_OFF_SHFT                                                              0x1f
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                                                  0x4000
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                                     0xe
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                                0x2000
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                   0xd
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                               0x1000
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                  0xc
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_WAKEUP_BMSK                                                              0xf00
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_WAKEUP_SHFT                                                                0x8
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_SLEEP_BMSK                                                                0xf0
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_SLEEP_SHFT                                                                 0x4
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_HW_CTL_BMSK                                                                0x2
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_HW_CTL_SHFT                                                                0x1
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_CLK_ENABLE_BMSK                                                            0x1
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM1_CORE_CBCR_CLK_ENABLE_SHFT                                                            0x0

#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_ADDR                                                                (LPASS_CC_REG_BASE      + 0x00047018)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_RMSK                                                                0x80007ff3
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_CLK_OFF_BMSK                                                        0x80000000
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_CLK_OFF_SHFT                                                              0x1f
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                                                  0x4000
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                                     0xe
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                                0x2000
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                   0xd
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                               0x1000
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                  0xc
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_WAKEUP_BMSK                                                              0xf00
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_WAKEUP_SHFT                                                                0x8
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_SLEEP_BMSK                                                                0xf0
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_SLEEP_SHFT                                                                 0x4
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_HW_CTL_BMSK                                                                0x2
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_HW_CTL_SHFT                                                                0x1
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_CLK_ENABLE_BMSK                                                            0x1
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM2_CORE_CBCR_CLK_ENABLE_SHFT                                                            0x0

#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_ADDR                                                                (LPASS_CC_REG_BASE      + 0x0004701c)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_RMSK                                                                0x80007ff3
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_CLK_OFF_BMSK                                                        0x80000000
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_CLK_OFF_SHFT                                                              0x1f
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK                                                  0x4000
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT                                                     0xe
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                                0x2000
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                   0xd
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                               0x1000
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                  0xc
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_WAKEUP_BMSK                                                              0xf00
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_WAKEUP_SHFT                                                                0x8
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_SLEEP_BMSK                                                                0xf0
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_SLEEP_SHFT                                                                 0x4
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_HW_CTL_BMSK                                                                0x2
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_HW_CTL_SHFT                                                                0x1
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_CLK_ENABLE_BMSK                                                            0x1
#define HWIO_LPASS_ISLAND_SCC_SMEM_MEM3_CORE_CBCR_CLK_ENABLE_SHFT                                                            0x0

#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_BCR_ADDR                                                                    (LPASS_CC_REG_BASE      + 0x00047020)
#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_BCR_RMSK                                                                           0x1
#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_BCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_BCR_ADDR, HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_BCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_BCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_BCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_BCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_BCR_IN)
#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_BCR_BLK_ARES_BMSK                                                                  0x1
#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_BCR_BLK_ARES_SHFT                                                                  0x0

#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_CORE_CBCR_ADDR                                                              (LPASS_CC_REG_BASE      + 0x00047024)
#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_CORE_CBCR_RMSK                                                              0x80000001
#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_CORE_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_CORE_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_CORE_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_CORE_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_CORE_CBCR_CLK_OFF_BMSK                                                      0x80000000
#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_CORE_CBCR_CLK_OFF_SHFT                                                            0x1f
#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_CORE_CBCR_CLK_ENABLE_BMSK                                                          0x1
#define HWIO_LPASS_ISLAND_SCC_AHB_TIMEOUT_CORE_CBCR_CLK_ENABLE_SHFT                                                          0x0

#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_ADDR                                                                    (LPASS_CC_REG_BASE      + 0x00047028)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_RMSK                                                                           0x1
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_ADDR, HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_IN)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_BLK_ARES_BMSK                                                                  0x1
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_BCR_BLK_ARES_SHFT                                                                  0x0

#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_CORE_CBCR_ADDR                                                              (LPASS_CC_REG_BASE      + 0x0004702c)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_CORE_CBCR_RMSK                                                              0x80000001
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_CORE_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_CORE_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_CORE_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_CORE_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_CORE_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_CORE_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_CORE_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_CORE_CBCR_CLK_OFF_BMSK                                                      0x80000000
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_CORE_CBCR_CLK_OFF_SHFT                                                            0x1f
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_CORE_CBCR_CLK_ENABLE_BMSK                                                          0x1
#define HWIO_LPASS_ISLAND_SCC_SENSOR_CORE_CORE_CBCR_CLK_ENABLE_SHFT                                                          0x0

#define HWIO_LPASS_ISLAND_SCC_VS_BCR_ADDR                                                                             (LPASS_CC_REG_BASE      + 0x00048014)
#define HWIO_LPASS_ISLAND_SCC_VS_BCR_RMSK                                                                                    0x1
#define HWIO_LPASS_ISLAND_SCC_VS_BCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_VS_BCR_ADDR, HWIO_LPASS_ISLAND_SCC_VS_BCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_VS_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_VS_BCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_VS_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_VS_BCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_VS_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_VS_BCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_VS_BCR_IN)
#define HWIO_LPASS_ISLAND_SCC_VS_BCR_BLK_ARES_BMSK                                                                           0x1
#define HWIO_LPASS_ISLAND_SCC_VS_BCR_BLK_ARES_SHFT                                                                           0x0

#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00048018)
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_RMSK                                                                         0x800000f3
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_ADDR, HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_RMSK)
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_ADDR,m,v,HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_IN)
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_ROOT_OFF_BMSK                                                                0x80000000
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_ROOT_OFF_SHFT                                                                      0x1f
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_DIRTY_D_BMSK                                                                       0x80
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_DIRTY_D_SHFT                                                                        0x7
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_DIRTY_N_BMSK                                                                       0x40
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_DIRTY_N_SHFT                                                                        0x6
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_DIRTY_M_BMSK                                                                       0x20
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_DIRTY_M_SHFT                                                                        0x5
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                0x10
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                 0x4
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_ROOT_EN_BMSK                                                                        0x2
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_ROOT_EN_SHFT                                                                        0x1
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_UPDATE_BMSK                                                                         0x1
#define HWIO_LPASS_SCC_VS_VDDMX_CMD_RCGR_UPDATE_SHFT                                                                         0x0

#define HWIO_LPASS_SCC_VS_VDDMX_CFG_RCGR_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x0004801c)
#define HWIO_LPASS_SCC_VS_VDDMX_CFG_RCGR_RMSK                                                                              0x71f
#define HWIO_LPASS_SCC_VS_VDDMX_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SCC_VS_VDDMX_CFG_RCGR_ADDR, HWIO_LPASS_SCC_VS_VDDMX_CFG_RCGR_RMSK)
#define HWIO_LPASS_SCC_VS_VDDMX_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_VS_VDDMX_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_SCC_VS_VDDMX_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_VS_VDDMX_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_SCC_VS_VDDMX_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_VS_VDDMX_CFG_RCGR_ADDR,m,v,HWIO_LPASS_SCC_VS_VDDMX_CFG_RCGR_IN)
#define HWIO_LPASS_SCC_VS_VDDMX_CFG_RCGR_SRC_SEL_BMSK                                                                      0x700
#define HWIO_LPASS_SCC_VS_VDDMX_CFG_RCGR_SRC_SEL_SHFT                                                                        0x8
#define HWIO_LPASS_SCC_VS_VDDMX_CFG_RCGR_SRC_DIV_BMSK                                                                       0x1f
#define HWIO_LPASS_SCC_VS_VDDMX_CFG_RCGR_SRC_DIV_SHFT                                                                        0x0

#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00048030)
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_RMSK                                                                         0x800000f3
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_ADDR, HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_RMSK)
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_ADDR,m,v,HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_IN)
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_ROOT_OFF_BMSK                                                                0x80000000
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_ROOT_OFF_SHFT                                                                      0x1f
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_DIRTY_D_BMSK                                                                       0x80
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_DIRTY_D_SHFT                                                                        0x7
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_DIRTY_N_BMSK                                                                       0x40
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_DIRTY_N_SHFT                                                                        0x6
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_DIRTY_M_BMSK                                                                       0x20
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_DIRTY_M_SHFT                                                                        0x5
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                0x10
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                 0x4
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_ROOT_EN_BMSK                                                                        0x2
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_ROOT_EN_SHFT                                                                        0x1
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_UPDATE_BMSK                                                                         0x1
#define HWIO_LPASS_SCC_VS_VDDCX_CMD_RCGR_UPDATE_SHFT                                                                         0x0

#define HWIO_LPASS_SCC_VS_VDDCX_CFG_RCGR_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00048034)
#define HWIO_LPASS_SCC_VS_VDDCX_CFG_RCGR_RMSK                                                                              0x71f
#define HWIO_LPASS_SCC_VS_VDDCX_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SCC_VS_VDDCX_CFG_RCGR_ADDR, HWIO_LPASS_SCC_VS_VDDCX_CFG_RCGR_RMSK)
#define HWIO_LPASS_SCC_VS_VDDCX_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_VS_VDDCX_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_SCC_VS_VDDCX_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_VS_VDDCX_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_SCC_VS_VDDCX_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_VS_VDDCX_CFG_RCGR_ADDR,m,v,HWIO_LPASS_SCC_VS_VDDCX_CFG_RCGR_IN)
#define HWIO_LPASS_SCC_VS_VDDCX_CFG_RCGR_SRC_SEL_BMSK                                                                      0x700
#define HWIO_LPASS_SCC_VS_VDDCX_CFG_RCGR_SRC_SEL_SHFT                                                                        0x8
#define HWIO_LPASS_SCC_VS_VDDCX_CFG_RCGR_SRC_DIV_BMSK                                                                       0x1f
#define HWIO_LPASS_SCC_VS_VDDCX_CFG_RCGR_SRC_DIV_SHFT                                                                        0x0

#define HWIO_LPASS_ISLAND_SCC_VS_VDDMX_CBCR_ADDR                                                                      (LPASS_CC_REG_BASE      + 0x00048048)
#define HWIO_LPASS_ISLAND_SCC_VS_VDDMX_CBCR_RMSK                                                                      0x80000001
#define HWIO_LPASS_ISLAND_SCC_VS_VDDMX_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_VS_VDDMX_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_VS_VDDMX_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_VS_VDDMX_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_VS_VDDMX_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_VS_VDDMX_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_VS_VDDMX_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_VS_VDDMX_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_VS_VDDMX_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_VS_VDDMX_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_VS_VDDMX_CBCR_CLK_OFF_BMSK                                                              0x80000000
#define HWIO_LPASS_ISLAND_SCC_VS_VDDMX_CBCR_CLK_OFF_SHFT                                                                    0x1f
#define HWIO_LPASS_ISLAND_SCC_VS_VDDMX_CBCR_CLK_ENABLE_BMSK                                                                  0x1
#define HWIO_LPASS_ISLAND_SCC_VS_VDDMX_CBCR_CLK_ENABLE_SHFT                                                                  0x0

#define HWIO_LPASS_ISLAND_SCC_VS_VDDCX_CBCR_ADDR                                                                      (LPASS_CC_REG_BASE      + 0x0004804c)
#define HWIO_LPASS_ISLAND_SCC_VS_VDDCX_CBCR_RMSK                                                                      0x80000001
#define HWIO_LPASS_ISLAND_SCC_VS_VDDCX_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_VS_VDDCX_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_VS_VDDCX_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_VS_VDDCX_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_VS_VDDCX_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_VS_VDDCX_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_VS_VDDCX_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_VS_VDDCX_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_VS_VDDCX_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_VS_VDDCX_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_VS_VDDCX_CBCR_CLK_OFF_BMSK                                                              0x80000000
#define HWIO_LPASS_ISLAND_SCC_VS_VDDCX_CBCR_CLK_OFF_SHFT                                                                    0x1f
#define HWIO_LPASS_ISLAND_SCC_VS_VDDCX_CBCR_CLK_ENABLE_BMSK                                                                  0x1
#define HWIO_LPASS_ISLAND_SCC_VS_VDDCX_CBCR_CLK_ENABLE_SHFT                                                                  0x0

#define HWIO_LPASS_Q6_SPM_CMD_RCGR_ADDR                                                                               (LPASS_CC_REG_BASE      + 0x00049000)
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_RMSK                                                                               0x800000f3
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_Q6_SPM_CMD_RCGR_ADDR, HWIO_LPASS_Q6_SPM_CMD_RCGR_RMSK)
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6_SPM_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6_SPM_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6_SPM_CMD_RCGR_ADDR,m,v,HWIO_LPASS_Q6_SPM_CMD_RCGR_IN)
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_ROOT_OFF_BMSK                                                                      0x80000000
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_ROOT_OFF_SHFT                                                                            0x1f
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_DIRTY_D_BMSK                                                                             0x80
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_DIRTY_D_SHFT                                                                              0x7
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_DIRTY_N_BMSK                                                                             0x40
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_DIRTY_N_SHFT                                                                              0x6
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_DIRTY_M_BMSK                                                                             0x20
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_DIRTY_M_SHFT                                                                              0x5
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                      0x10
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                       0x4
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_ROOT_EN_BMSK                                                                              0x2
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_ROOT_EN_SHFT                                                                              0x1
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_UPDATE_BMSK                                                                               0x1
#define HWIO_LPASS_Q6_SPM_CMD_RCGR_UPDATE_SHFT                                                                               0x0

#define HWIO_LPASS_Q6_SPM_CFG_RCGR_ADDR                                                                               (LPASS_CC_REG_BASE      + 0x00049004)
#define HWIO_LPASS_Q6_SPM_CFG_RCGR_RMSK                                                                                   0x771f
#define HWIO_LPASS_Q6_SPM_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_Q6_SPM_CFG_RCGR_ADDR, HWIO_LPASS_Q6_SPM_CFG_RCGR_RMSK)
#define HWIO_LPASS_Q6_SPM_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_Q6_SPM_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_Q6_SPM_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_Q6_SPM_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_Q6_SPM_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_Q6_SPM_CFG_RCGR_ADDR,m,v,HWIO_LPASS_Q6_SPM_CFG_RCGR_IN)
#define HWIO_LPASS_Q6_SPM_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                       0x4000
#define HWIO_LPASS_Q6_SPM_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                          0xe
#define HWIO_LPASS_Q6_SPM_CFG_RCGR_MODE_BMSK                                                                              0x3000
#define HWIO_LPASS_Q6_SPM_CFG_RCGR_MODE_SHFT                                                                                 0xc
#define HWIO_LPASS_Q6_SPM_CFG_RCGR_SRC_SEL_BMSK                                                                            0x700
#define HWIO_LPASS_Q6_SPM_CFG_RCGR_SRC_SEL_SHFT                                                                              0x8
#define HWIO_LPASS_Q6_SPM_CFG_RCGR_SRC_DIV_BMSK                                                                             0x1f
#define HWIO_LPASS_Q6_SPM_CFG_RCGR_SRC_DIV_SHFT                                                                              0x0

#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_BCR_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00049008)
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_BCR_RMSK                                                                                0x1
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_BCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_Q6_SPM_BCR_ADDR, HWIO_LPASS_ISLAND_SCC_Q6_SPM_BCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_Q6_SPM_BCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_Q6_SPM_BCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_Q6_SPM_BCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_Q6_SPM_BCR_IN)
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_BCR_BLK_ARES_BMSK                                                                       0x1
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_BCR_BLK_ARES_SHFT                                                                       0x0

#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_ADDR                                                                        (LPASS_CC_REG_BASE      + 0x0004900c)
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_RMSK                                                                        0x800f0001
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_CLK_OFF_BMSK                                                                0x80000000
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_CLK_OFF_SHFT                                                                      0x1f
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_CLK_DIV_BMSK                                                                   0xf0000
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_CLK_DIV_SHFT                                                                      0x10
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_CLK_ENABLE_BMSK                                                                    0x1
#define HWIO_LPASS_ISLAND_SCC_Q6_SPM_CBCR_CLK_ENABLE_SHFT                                                                    0x0

#define HWIO_LPASS_SW_NPL_CMD_RCGR_ADDR                                                                               (LPASS_CC_REG_BASE      + 0x0004d000)
#define HWIO_LPASS_SW_NPL_CMD_RCGR_RMSK                                                                               0x800000f3
#define HWIO_LPASS_SW_NPL_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SW_NPL_CMD_RCGR_ADDR, HWIO_LPASS_SW_NPL_CMD_RCGR_RMSK)
#define HWIO_LPASS_SW_NPL_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SW_NPL_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_SW_NPL_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SW_NPL_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_SW_NPL_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SW_NPL_CMD_RCGR_ADDR,m,v,HWIO_LPASS_SW_NPL_CMD_RCGR_IN)
#define HWIO_LPASS_SW_NPL_CMD_RCGR_ROOT_OFF_BMSK                                                                      0x80000000
#define HWIO_LPASS_SW_NPL_CMD_RCGR_ROOT_OFF_SHFT                                                                            0x1f
#define HWIO_LPASS_SW_NPL_CMD_RCGR_DIRTY_D_BMSK                                                                             0x80
#define HWIO_LPASS_SW_NPL_CMD_RCGR_DIRTY_D_SHFT                                                                              0x7
#define HWIO_LPASS_SW_NPL_CMD_RCGR_DIRTY_N_BMSK                                                                             0x40
#define HWIO_LPASS_SW_NPL_CMD_RCGR_DIRTY_N_SHFT                                                                              0x6
#define HWIO_LPASS_SW_NPL_CMD_RCGR_DIRTY_M_BMSK                                                                             0x20
#define HWIO_LPASS_SW_NPL_CMD_RCGR_DIRTY_M_SHFT                                                                              0x5
#define HWIO_LPASS_SW_NPL_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                      0x10
#define HWIO_LPASS_SW_NPL_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                       0x4
#define HWIO_LPASS_SW_NPL_CMD_RCGR_ROOT_EN_BMSK                                                                              0x2
#define HWIO_LPASS_SW_NPL_CMD_RCGR_ROOT_EN_SHFT                                                                              0x1
#define HWIO_LPASS_SW_NPL_CMD_RCGR_UPDATE_BMSK                                                                               0x1
#define HWIO_LPASS_SW_NPL_CMD_RCGR_UPDATE_SHFT                                                                               0x0

#define HWIO_LPASS_SW_NPL_CFG_RCGR_ADDR                                                                               (LPASS_CC_REG_BASE      + 0x0004d004)
#define HWIO_LPASS_SW_NPL_CFG_RCGR_RMSK                                                                                   0x771f
#define HWIO_LPASS_SW_NPL_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SW_NPL_CFG_RCGR_ADDR, HWIO_LPASS_SW_NPL_CFG_RCGR_RMSK)
#define HWIO_LPASS_SW_NPL_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SW_NPL_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_SW_NPL_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SW_NPL_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_SW_NPL_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SW_NPL_CFG_RCGR_ADDR,m,v,HWIO_LPASS_SW_NPL_CFG_RCGR_IN)
#define HWIO_LPASS_SW_NPL_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                       0x4000
#define HWIO_LPASS_SW_NPL_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                          0xe
#define HWIO_LPASS_SW_NPL_CFG_RCGR_MODE_BMSK                                                                              0x3000
#define HWIO_LPASS_SW_NPL_CFG_RCGR_MODE_SHFT                                                                                 0xc
#define HWIO_LPASS_SW_NPL_CFG_RCGR_SRC_SEL_BMSK                                                                            0x700
#define HWIO_LPASS_SW_NPL_CFG_RCGR_SRC_SEL_SHFT                                                                              0x8
#define HWIO_LPASS_SW_NPL_CFG_RCGR_SRC_DIV_BMSK                                                                             0x1f
#define HWIO_LPASS_SW_NPL_CFG_RCGR_SRC_DIV_SHFT                                                                              0x0

#define HWIO_LPASS_SW_NPL_M_ADDR                                                                                      (LPASS_CC_REG_BASE      + 0x0004d008)
#define HWIO_LPASS_SW_NPL_M_RMSK                                                                                            0xff
#define HWIO_LPASS_SW_NPL_M_IN          \
        in_dword_masked(HWIO_LPASS_SW_NPL_M_ADDR, HWIO_LPASS_SW_NPL_M_RMSK)
#define HWIO_LPASS_SW_NPL_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_SW_NPL_M_ADDR, m)
#define HWIO_LPASS_SW_NPL_M_OUT(v)      \
        out_dword(HWIO_LPASS_SW_NPL_M_ADDR,v)
#define HWIO_LPASS_SW_NPL_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SW_NPL_M_ADDR,m,v,HWIO_LPASS_SW_NPL_M_IN)
#define HWIO_LPASS_SW_NPL_M_M_BMSK                                                                                          0xff
#define HWIO_LPASS_SW_NPL_M_M_SHFT                                                                                           0x0

#define HWIO_LPASS_SW_NPL_N_ADDR                                                                                      (LPASS_CC_REG_BASE      + 0x0004d00c)
#define HWIO_LPASS_SW_NPL_N_RMSK                                                                                            0xff
#define HWIO_LPASS_SW_NPL_N_IN          \
        in_dword_masked(HWIO_LPASS_SW_NPL_N_ADDR, HWIO_LPASS_SW_NPL_N_RMSK)
#define HWIO_LPASS_SW_NPL_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_SW_NPL_N_ADDR, m)
#define HWIO_LPASS_SW_NPL_N_OUT(v)      \
        out_dword(HWIO_LPASS_SW_NPL_N_ADDR,v)
#define HWIO_LPASS_SW_NPL_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SW_NPL_N_ADDR,m,v,HWIO_LPASS_SW_NPL_N_IN)
#define HWIO_LPASS_SW_NPL_N_NOT_N_MINUS_M_BMSK                                                                              0xff
#define HWIO_LPASS_SW_NPL_N_NOT_N_MINUS_M_SHFT                                                                               0x0

#define HWIO_LPASS_SW_NPL_D_ADDR                                                                                      (LPASS_CC_REG_BASE      + 0x0004d010)
#define HWIO_LPASS_SW_NPL_D_RMSK                                                                                            0xff
#define HWIO_LPASS_SW_NPL_D_IN          \
        in_dword_masked(HWIO_LPASS_SW_NPL_D_ADDR, HWIO_LPASS_SW_NPL_D_RMSK)
#define HWIO_LPASS_SW_NPL_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_SW_NPL_D_ADDR, m)
#define HWIO_LPASS_SW_NPL_D_OUT(v)      \
        out_dword(HWIO_LPASS_SW_NPL_D_ADDR,v)
#define HWIO_LPASS_SW_NPL_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SW_NPL_D_ADDR,m,v,HWIO_LPASS_SW_NPL_D_IN)
#define HWIO_LPASS_SW_NPL_D_NOT_2D_BMSK                                                                                     0xff
#define HWIO_LPASS_SW_NPL_D_NOT_2D_SHFT                                                                                      0x0

#define HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_ADDR                                                                     (LPASS_CC_REG_BASE      + 0x0004d014)
#define HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_RMSK                                                                     0x80000003
#define HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_ADDR, HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_IN)
#define HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_CLK_OFF_BMSK                                                             0x80000000
#define HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_CLK_OFF_SHFT                                                                   0x1f
#define HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_HW_CTL_BMSK                                                                     0x2
#define HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_HW_CTL_SHFT                                                                     0x1
#define HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_CLK_ENABLE_BMSK                                                                 0x1
#define HWIO_LPASS_AUDIO_WRAPPER_SW_NPL_CBCR_CLK_ENABLE_SHFT                                                                 0x0

#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_ADDR                                                                           (LPASS_CC_REG_BASE      + 0x0004e000)
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_RMSK                                                                           0x800000f3
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S0_1_CMD_RCGR_ADDR, HWIO_LPASS_INT_I2S0_1_CMD_RCGR_RMSK)
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S0_1_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S0_1_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S0_1_CMD_RCGR_ADDR,m,v,HWIO_LPASS_INT_I2S0_1_CMD_RCGR_IN)
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_ROOT_OFF_BMSK                                                                  0x80000000
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_ROOT_OFF_SHFT                                                                        0x1f
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_DIRTY_D_BMSK                                                                         0x80
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_DIRTY_D_SHFT                                                                          0x7
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_DIRTY_N_BMSK                                                                         0x40
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_DIRTY_N_SHFT                                                                          0x6
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_DIRTY_M_BMSK                                                                         0x20
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_DIRTY_M_SHFT                                                                          0x5
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                  0x10
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                   0x4
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_ROOT_EN_BMSK                                                                          0x2
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_ROOT_EN_SHFT                                                                          0x1
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_UPDATE_BMSK                                                                           0x1
#define HWIO_LPASS_INT_I2S0_1_CMD_RCGR_UPDATE_SHFT                                                                           0x0

#define HWIO_LPASS_INT_I2S0_1_CFG_RCGR_ADDR                                                                           (LPASS_CC_REG_BASE      + 0x0004e004)
#define HWIO_LPASS_INT_I2S0_1_CFG_RCGR_RMSK                                                                               0x771f
#define HWIO_LPASS_INT_I2S0_1_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S0_1_CFG_RCGR_ADDR, HWIO_LPASS_INT_I2S0_1_CFG_RCGR_RMSK)
#define HWIO_LPASS_INT_I2S0_1_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S0_1_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_INT_I2S0_1_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S0_1_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_INT_I2S0_1_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S0_1_CFG_RCGR_ADDR,m,v,HWIO_LPASS_INT_I2S0_1_CFG_RCGR_IN)
#define HWIO_LPASS_INT_I2S0_1_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                   0x4000
#define HWIO_LPASS_INT_I2S0_1_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                      0xe
#define HWIO_LPASS_INT_I2S0_1_CFG_RCGR_MODE_BMSK                                                                          0x3000
#define HWIO_LPASS_INT_I2S0_1_CFG_RCGR_MODE_SHFT                                                                             0xc
#define HWIO_LPASS_INT_I2S0_1_CFG_RCGR_SRC_SEL_BMSK                                                                        0x700
#define HWIO_LPASS_INT_I2S0_1_CFG_RCGR_SRC_SEL_SHFT                                                                          0x8
#define HWIO_LPASS_INT_I2S0_1_CFG_RCGR_SRC_DIV_BMSK                                                                         0x1f
#define HWIO_LPASS_INT_I2S0_1_CFG_RCGR_SRC_DIV_SHFT                                                                          0x0

#define HWIO_LPASS_INT_I2S0_1_M_ADDR                                                                                  (LPASS_CC_REG_BASE      + 0x0004e008)
#define HWIO_LPASS_INT_I2S0_1_M_RMSK                                                                                        0xff
#define HWIO_LPASS_INT_I2S0_1_M_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S0_1_M_ADDR, HWIO_LPASS_INT_I2S0_1_M_RMSK)
#define HWIO_LPASS_INT_I2S0_1_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S0_1_M_ADDR, m)
#define HWIO_LPASS_INT_I2S0_1_M_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S0_1_M_ADDR,v)
#define HWIO_LPASS_INT_I2S0_1_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S0_1_M_ADDR,m,v,HWIO_LPASS_INT_I2S0_1_M_IN)
#define HWIO_LPASS_INT_I2S0_1_M_M_BMSK                                                                                      0xff
#define HWIO_LPASS_INT_I2S0_1_M_M_SHFT                                                                                       0x0

#define HWIO_LPASS_INT_I2S0_1_N_ADDR                                                                                  (LPASS_CC_REG_BASE      + 0x0004e00c)
#define HWIO_LPASS_INT_I2S0_1_N_RMSK                                                                                        0xff
#define HWIO_LPASS_INT_I2S0_1_N_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S0_1_N_ADDR, HWIO_LPASS_INT_I2S0_1_N_RMSK)
#define HWIO_LPASS_INT_I2S0_1_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S0_1_N_ADDR, m)
#define HWIO_LPASS_INT_I2S0_1_N_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S0_1_N_ADDR,v)
#define HWIO_LPASS_INT_I2S0_1_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S0_1_N_ADDR,m,v,HWIO_LPASS_INT_I2S0_1_N_IN)
#define HWIO_LPASS_INT_I2S0_1_N_NOT_N_MINUS_M_BMSK                                                                          0xff
#define HWIO_LPASS_INT_I2S0_1_N_NOT_N_MINUS_M_SHFT                                                                           0x0

#define HWIO_LPASS_INT_I2S0_1_D_ADDR                                                                                  (LPASS_CC_REG_BASE      + 0x0004e010)
#define HWIO_LPASS_INT_I2S0_1_D_RMSK                                                                                        0xff
#define HWIO_LPASS_INT_I2S0_1_D_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S0_1_D_ADDR, HWIO_LPASS_INT_I2S0_1_D_RMSK)
#define HWIO_LPASS_INT_I2S0_1_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S0_1_D_ADDR, m)
#define HWIO_LPASS_INT_I2S0_1_D_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S0_1_D_ADDR,v)
#define HWIO_LPASS_INT_I2S0_1_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S0_1_D_ADDR,m,v,HWIO_LPASS_INT_I2S0_1_D_IN)
#define HWIO_LPASS_INT_I2S0_1_D_NOT_2D_BMSK                                                                                 0xff
#define HWIO_LPASS_INT_I2S0_1_D_NOT_2D_SHFT                                                                                  0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_ADDR                                                               (LPASS_CC_REG_BASE      + 0x0004e014)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_RMSK                                                               0x80000003
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_CLK_OFF_BMSK                                                       0x80000000
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_CLK_OFF_SHFT                                                             0x1f
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_HW_CTL_BMSK                                                               0x2
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_HW_CTL_SHFT                                                               0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_CLK_ENABLE_BMSK                                                           0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_IBIT_CBCR_CLK_ENABLE_SHFT                                                           0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_ADDR                                                               (LPASS_CC_REG_BASE      + 0x0004e018)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_RMSK                                                               0x80000003
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_CLK_OFF_BMSK                                                       0x80000000
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_CLK_OFF_SHFT                                                             0x1f
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_HW_CTL_BMSK                                                               0x2
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_HW_CTL_SHFT                                                               0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_CLK_ENABLE_BMSK                                                           0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EBIT_CBCR_CLK_ENABLE_SHFT                                                           0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_ADDR                                                          (LPASS_CC_REG_BASE      + 0x0004e01c)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_RMSK                                                          0x80007f13
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_BMSK                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_SHFT                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_CLK_COUNTER_VALUE_BMSK                                            0x7f00
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_CLK_COUNTER_VALUE_SHFT                                               0x8
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_IRQ_CLEAR_BMSK                                                      0x10
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_IRQ_CLEAR_SHFT                                                       0x4
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_CLK_COUNTER_EN_BMSK                                                  0x2
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_CLK_COUNTER_EN_SHFT                                                  0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_IRQ_EN_BMSK                                                          0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_EXT_CLK_DETECT_IRQ_EN_SHFT                                                          0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_TEST_ENABLE_ADDR                                                             (LPASS_CC_REG_BASE      + 0x0004e020)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_TEST_ENABLE_RMSK                                                                    0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_TEST_ENABLE_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_TEST_ENABLE_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_TEST_ENABLE_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_TEST_ENABLE_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_TEST_ENABLE_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_TEST_ENABLE_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_TEST_ENABLE_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_TEST_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_TEST_ENABLE_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_TEST_ENABLE_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_TEST_ENABLE_TEST_CLK_ENABLE_BMSK                                                    0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S0_1_TEST_ENABLE_TEST_CLK_ENABLE_SHFT                                                    0x0

#define HWIO_LPASS_INT_I2S2_CMD_RCGR_ADDR                                                                             (LPASS_CC_REG_BASE      + 0x0004f000)
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_RMSK                                                                             0x800000f3
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S2_CMD_RCGR_ADDR, HWIO_LPASS_INT_I2S2_CMD_RCGR_RMSK)
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S2_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S2_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S2_CMD_RCGR_ADDR,m,v,HWIO_LPASS_INT_I2S2_CMD_RCGR_IN)
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_ROOT_OFF_BMSK                                                                    0x80000000
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_ROOT_OFF_SHFT                                                                          0x1f
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_DIRTY_D_BMSK                                                                           0x80
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_DIRTY_D_SHFT                                                                            0x7
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_DIRTY_N_BMSK                                                                           0x40
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_DIRTY_N_SHFT                                                                            0x6
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_DIRTY_M_BMSK                                                                           0x20
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_DIRTY_M_SHFT                                                                            0x5
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                    0x10
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                     0x4
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_ROOT_EN_BMSK                                                                            0x2
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_ROOT_EN_SHFT                                                                            0x1
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_UPDATE_BMSK                                                                             0x1
#define HWIO_LPASS_INT_I2S2_CMD_RCGR_UPDATE_SHFT                                                                             0x0

#define HWIO_LPASS_INT_I2S2_CFG_RCGR_ADDR                                                                             (LPASS_CC_REG_BASE      + 0x0004f004)
#define HWIO_LPASS_INT_I2S2_CFG_RCGR_RMSK                                                                                 0x771f
#define HWIO_LPASS_INT_I2S2_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S2_CFG_RCGR_ADDR, HWIO_LPASS_INT_I2S2_CFG_RCGR_RMSK)
#define HWIO_LPASS_INT_I2S2_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S2_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_INT_I2S2_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S2_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_INT_I2S2_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S2_CFG_RCGR_ADDR,m,v,HWIO_LPASS_INT_I2S2_CFG_RCGR_IN)
#define HWIO_LPASS_INT_I2S2_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                     0x4000
#define HWIO_LPASS_INT_I2S2_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                        0xe
#define HWIO_LPASS_INT_I2S2_CFG_RCGR_MODE_BMSK                                                                            0x3000
#define HWIO_LPASS_INT_I2S2_CFG_RCGR_MODE_SHFT                                                                               0xc
#define HWIO_LPASS_INT_I2S2_CFG_RCGR_SRC_SEL_BMSK                                                                          0x700
#define HWIO_LPASS_INT_I2S2_CFG_RCGR_SRC_SEL_SHFT                                                                            0x8
#define HWIO_LPASS_INT_I2S2_CFG_RCGR_SRC_DIV_BMSK                                                                           0x1f
#define HWIO_LPASS_INT_I2S2_CFG_RCGR_SRC_DIV_SHFT                                                                            0x0

#define HWIO_LPASS_INT_I2S2_M_ADDR                                                                                    (LPASS_CC_REG_BASE      + 0x0004f008)
#define HWIO_LPASS_INT_I2S2_M_RMSK                                                                                          0xff
#define HWIO_LPASS_INT_I2S2_M_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S2_M_ADDR, HWIO_LPASS_INT_I2S2_M_RMSK)
#define HWIO_LPASS_INT_I2S2_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S2_M_ADDR, m)
#define HWIO_LPASS_INT_I2S2_M_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S2_M_ADDR,v)
#define HWIO_LPASS_INT_I2S2_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S2_M_ADDR,m,v,HWIO_LPASS_INT_I2S2_M_IN)
#define HWIO_LPASS_INT_I2S2_M_M_BMSK                                                                                        0xff
#define HWIO_LPASS_INT_I2S2_M_M_SHFT                                                                                         0x0

#define HWIO_LPASS_INT_I2S2_N_ADDR                                                                                    (LPASS_CC_REG_BASE      + 0x0004f00c)
#define HWIO_LPASS_INT_I2S2_N_RMSK                                                                                          0xff
#define HWIO_LPASS_INT_I2S2_N_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S2_N_ADDR, HWIO_LPASS_INT_I2S2_N_RMSK)
#define HWIO_LPASS_INT_I2S2_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S2_N_ADDR, m)
#define HWIO_LPASS_INT_I2S2_N_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S2_N_ADDR,v)
#define HWIO_LPASS_INT_I2S2_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S2_N_ADDR,m,v,HWIO_LPASS_INT_I2S2_N_IN)
#define HWIO_LPASS_INT_I2S2_N_NOT_N_MINUS_M_BMSK                                                                            0xff
#define HWIO_LPASS_INT_I2S2_N_NOT_N_MINUS_M_SHFT                                                                             0x0

#define HWIO_LPASS_INT_I2S2_D_ADDR                                                                                    (LPASS_CC_REG_BASE      + 0x0004f010)
#define HWIO_LPASS_INT_I2S2_D_RMSK                                                                                          0xff
#define HWIO_LPASS_INT_I2S2_D_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S2_D_ADDR, HWIO_LPASS_INT_I2S2_D_RMSK)
#define HWIO_LPASS_INT_I2S2_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S2_D_ADDR, m)
#define HWIO_LPASS_INT_I2S2_D_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S2_D_ADDR,v)
#define HWIO_LPASS_INT_I2S2_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S2_D_ADDR,m,v,HWIO_LPASS_INT_I2S2_D_IN)
#define HWIO_LPASS_INT_I2S2_D_NOT_2D_BMSK                                                                                   0xff
#define HWIO_LPASS_INT_I2S2_D_NOT_2D_SHFT                                                                                    0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x0004f014)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_RMSK                                                                 0x80000003
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_HW_CTL_BMSK                                                                 0x2
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_HW_CTL_SHFT                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_IBIT_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x0004f018)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_RMSK                                                                 0x80000003
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_HW_CTL_BMSK                                                                 0x2
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_HW_CTL_SHFT                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EBIT_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_ADDR                                                            (LPASS_CC_REG_BASE      + 0x0004f01c)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_RMSK                                                            0x80007f13
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_BMSK                                           0x80000000
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_SHFT                                                 0x1f
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_CLK_COUNTER_VALUE_BMSK                                              0x7f00
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_CLK_COUNTER_VALUE_SHFT                                                 0x8
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_IRQ_CLEAR_BMSK                                                        0x10
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_IRQ_CLEAR_SHFT                                                         0x4
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_CLK_COUNTER_EN_BMSK                                                    0x2
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_CLK_COUNTER_EN_SHFT                                                    0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_IRQ_EN_BMSK                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_EXT_CLK_DETECT_IRQ_EN_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_TEST_ENABLE_ADDR                                                               (LPASS_CC_REG_BASE      + 0x0004f020)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_TEST_ENABLE_RMSK                                                                      0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_TEST_ENABLE_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S2_TEST_ENABLE_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S2_TEST_ENABLE_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_TEST_ENABLE_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S2_TEST_ENABLE_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_TEST_ENABLE_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S2_TEST_ENABLE_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_TEST_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S2_TEST_ENABLE_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S2_TEST_ENABLE_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_TEST_ENABLE_TEST_CLK_ENABLE_BMSK                                                      0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S2_TEST_ENABLE_TEST_CLK_ENABLE_SHFT                                                      0x0

#define HWIO_LPASS_INT_I2S3_CMD_RCGR_ADDR                                                                             (LPASS_CC_REG_BASE      + 0x00050000)
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_RMSK                                                                             0x800000f3
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S3_CMD_RCGR_ADDR, HWIO_LPASS_INT_I2S3_CMD_RCGR_RMSK)
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S3_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S3_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S3_CMD_RCGR_ADDR,m,v,HWIO_LPASS_INT_I2S3_CMD_RCGR_IN)
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_ROOT_OFF_BMSK                                                                    0x80000000
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_ROOT_OFF_SHFT                                                                          0x1f
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_DIRTY_D_BMSK                                                                           0x80
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_DIRTY_D_SHFT                                                                            0x7
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_DIRTY_N_BMSK                                                                           0x40
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_DIRTY_N_SHFT                                                                            0x6
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_DIRTY_M_BMSK                                                                           0x20
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_DIRTY_M_SHFT                                                                            0x5
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                    0x10
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                     0x4
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_ROOT_EN_BMSK                                                                            0x2
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_ROOT_EN_SHFT                                                                            0x1
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_UPDATE_BMSK                                                                             0x1
#define HWIO_LPASS_INT_I2S3_CMD_RCGR_UPDATE_SHFT                                                                             0x0

#define HWIO_LPASS_INT_I2S3_CFG_RCGR_ADDR                                                                             (LPASS_CC_REG_BASE      + 0x00050004)
#define HWIO_LPASS_INT_I2S3_CFG_RCGR_RMSK                                                                                 0x771f
#define HWIO_LPASS_INT_I2S3_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S3_CFG_RCGR_ADDR, HWIO_LPASS_INT_I2S3_CFG_RCGR_RMSK)
#define HWIO_LPASS_INT_I2S3_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S3_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_INT_I2S3_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S3_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_INT_I2S3_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S3_CFG_RCGR_ADDR,m,v,HWIO_LPASS_INT_I2S3_CFG_RCGR_IN)
#define HWIO_LPASS_INT_I2S3_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                     0x4000
#define HWIO_LPASS_INT_I2S3_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                        0xe
#define HWIO_LPASS_INT_I2S3_CFG_RCGR_MODE_BMSK                                                                            0x3000
#define HWIO_LPASS_INT_I2S3_CFG_RCGR_MODE_SHFT                                                                               0xc
#define HWIO_LPASS_INT_I2S3_CFG_RCGR_SRC_SEL_BMSK                                                                          0x700
#define HWIO_LPASS_INT_I2S3_CFG_RCGR_SRC_SEL_SHFT                                                                            0x8
#define HWIO_LPASS_INT_I2S3_CFG_RCGR_SRC_DIV_BMSK                                                                           0x1f
#define HWIO_LPASS_INT_I2S3_CFG_RCGR_SRC_DIV_SHFT                                                                            0x0

#define HWIO_LPASS_INT_I2S3_M_ADDR                                                                                    (LPASS_CC_REG_BASE      + 0x00050008)
#define HWIO_LPASS_INT_I2S3_M_RMSK                                                                                          0xff
#define HWIO_LPASS_INT_I2S3_M_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S3_M_ADDR, HWIO_LPASS_INT_I2S3_M_RMSK)
#define HWIO_LPASS_INT_I2S3_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S3_M_ADDR, m)
#define HWIO_LPASS_INT_I2S3_M_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S3_M_ADDR,v)
#define HWIO_LPASS_INT_I2S3_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S3_M_ADDR,m,v,HWIO_LPASS_INT_I2S3_M_IN)
#define HWIO_LPASS_INT_I2S3_M_M_BMSK                                                                                        0xff
#define HWIO_LPASS_INT_I2S3_M_M_SHFT                                                                                         0x0

#define HWIO_LPASS_INT_I2S3_N_ADDR                                                                                    (LPASS_CC_REG_BASE      + 0x0005000c)
#define HWIO_LPASS_INT_I2S3_N_RMSK                                                                                          0xff
#define HWIO_LPASS_INT_I2S3_N_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S3_N_ADDR, HWIO_LPASS_INT_I2S3_N_RMSK)
#define HWIO_LPASS_INT_I2S3_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S3_N_ADDR, m)
#define HWIO_LPASS_INT_I2S3_N_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S3_N_ADDR,v)
#define HWIO_LPASS_INT_I2S3_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S3_N_ADDR,m,v,HWIO_LPASS_INT_I2S3_N_IN)
#define HWIO_LPASS_INT_I2S3_N_NOT_N_MINUS_M_BMSK                                                                            0xff
#define HWIO_LPASS_INT_I2S3_N_NOT_N_MINUS_M_SHFT                                                                             0x0

#define HWIO_LPASS_INT_I2S3_D_ADDR                                                                                    (LPASS_CC_REG_BASE      + 0x00050010)
#define HWIO_LPASS_INT_I2S3_D_RMSK                                                                                          0xff
#define HWIO_LPASS_INT_I2S3_D_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S3_D_ADDR, HWIO_LPASS_INT_I2S3_D_RMSK)
#define HWIO_LPASS_INT_I2S3_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S3_D_ADDR, m)
#define HWIO_LPASS_INT_I2S3_D_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S3_D_ADDR,v)
#define HWIO_LPASS_INT_I2S3_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S3_D_ADDR,m,v,HWIO_LPASS_INT_I2S3_D_IN)
#define HWIO_LPASS_INT_I2S3_D_NOT_2D_BMSK                                                                                   0xff
#define HWIO_LPASS_INT_I2S3_D_NOT_2D_SHFT                                                                                    0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x00050014)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_RMSK                                                                 0x80000003
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_HW_CTL_BMSK                                                                 0x2
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_HW_CTL_SHFT                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_IBIT_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x00050018)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_RMSK                                                                 0x80000003
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_HW_CTL_BMSK                                                                 0x2
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_HW_CTL_SHFT                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EBIT_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_ADDR                                                            (LPASS_CC_REG_BASE      + 0x0005001c)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_RMSK                                                            0x80007f13
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_BMSK                                           0x80000000
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_SHFT                                                 0x1f
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_CLK_COUNTER_VALUE_BMSK                                              0x7f00
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_CLK_COUNTER_VALUE_SHFT                                                 0x8
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_IRQ_CLEAR_BMSK                                                        0x10
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_IRQ_CLEAR_SHFT                                                         0x4
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_CLK_COUNTER_EN_BMSK                                                    0x2
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_CLK_COUNTER_EN_SHFT                                                    0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_IRQ_EN_BMSK                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_EXT_CLK_DETECT_IRQ_EN_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_TEST_ENABLE_ADDR                                                               (LPASS_CC_REG_BASE      + 0x00050020)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_TEST_ENABLE_RMSK                                                                      0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_TEST_ENABLE_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S3_TEST_ENABLE_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S3_TEST_ENABLE_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_TEST_ENABLE_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S3_TEST_ENABLE_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_TEST_ENABLE_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S3_TEST_ENABLE_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_TEST_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S3_TEST_ENABLE_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S3_TEST_ENABLE_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_TEST_ENABLE_TEST_CLK_ENABLE_BMSK                                                      0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S3_TEST_ENABLE_TEST_CLK_ENABLE_SHFT                                                      0x0

#define HWIO_LPASS_INT_I2S4_CMD_RCGR_ADDR                                                                             (LPASS_CC_REG_BASE      + 0x00051000)
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_RMSK                                                                             0x800000f3
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S4_CMD_RCGR_ADDR, HWIO_LPASS_INT_I2S4_CMD_RCGR_RMSK)
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S4_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S4_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S4_CMD_RCGR_ADDR,m,v,HWIO_LPASS_INT_I2S4_CMD_RCGR_IN)
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_ROOT_OFF_BMSK                                                                    0x80000000
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_ROOT_OFF_SHFT                                                                          0x1f
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_DIRTY_D_BMSK                                                                           0x80
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_DIRTY_D_SHFT                                                                            0x7
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_DIRTY_N_BMSK                                                                           0x40
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_DIRTY_N_SHFT                                                                            0x6
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_DIRTY_M_BMSK                                                                           0x20
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_DIRTY_M_SHFT                                                                            0x5
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                    0x10
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                     0x4
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_ROOT_EN_BMSK                                                                            0x2
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_ROOT_EN_SHFT                                                                            0x1
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_UPDATE_BMSK                                                                             0x1
#define HWIO_LPASS_INT_I2S4_CMD_RCGR_UPDATE_SHFT                                                                             0x0

#define HWIO_LPASS_INT_I2S4_CFG_RCGR_ADDR                                                                             (LPASS_CC_REG_BASE      + 0x00051004)
#define HWIO_LPASS_INT_I2S4_CFG_RCGR_RMSK                                                                                 0x771f
#define HWIO_LPASS_INT_I2S4_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S4_CFG_RCGR_ADDR, HWIO_LPASS_INT_I2S4_CFG_RCGR_RMSK)
#define HWIO_LPASS_INT_I2S4_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S4_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_INT_I2S4_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S4_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_INT_I2S4_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S4_CFG_RCGR_ADDR,m,v,HWIO_LPASS_INT_I2S4_CFG_RCGR_IN)
#define HWIO_LPASS_INT_I2S4_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                     0x4000
#define HWIO_LPASS_INT_I2S4_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                        0xe
#define HWIO_LPASS_INT_I2S4_CFG_RCGR_MODE_BMSK                                                                            0x3000
#define HWIO_LPASS_INT_I2S4_CFG_RCGR_MODE_SHFT                                                                               0xc
#define HWIO_LPASS_INT_I2S4_CFG_RCGR_SRC_SEL_BMSK                                                                          0x700
#define HWIO_LPASS_INT_I2S4_CFG_RCGR_SRC_SEL_SHFT                                                                            0x8
#define HWIO_LPASS_INT_I2S4_CFG_RCGR_SRC_DIV_BMSK                                                                           0x1f
#define HWIO_LPASS_INT_I2S4_CFG_RCGR_SRC_DIV_SHFT                                                                            0x0

#define HWIO_LPASS_INT_I2S4_M_ADDR                                                                                    (LPASS_CC_REG_BASE      + 0x00051008)
#define HWIO_LPASS_INT_I2S4_M_RMSK                                                                                          0xff
#define HWIO_LPASS_INT_I2S4_M_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S4_M_ADDR, HWIO_LPASS_INT_I2S4_M_RMSK)
#define HWIO_LPASS_INT_I2S4_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S4_M_ADDR, m)
#define HWIO_LPASS_INT_I2S4_M_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S4_M_ADDR,v)
#define HWIO_LPASS_INT_I2S4_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S4_M_ADDR,m,v,HWIO_LPASS_INT_I2S4_M_IN)
#define HWIO_LPASS_INT_I2S4_M_M_BMSK                                                                                        0xff
#define HWIO_LPASS_INT_I2S4_M_M_SHFT                                                                                         0x0

#define HWIO_LPASS_INT_I2S4_N_ADDR                                                                                    (LPASS_CC_REG_BASE      + 0x0005100c)
#define HWIO_LPASS_INT_I2S4_N_RMSK                                                                                          0xff
#define HWIO_LPASS_INT_I2S4_N_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S4_N_ADDR, HWIO_LPASS_INT_I2S4_N_RMSK)
#define HWIO_LPASS_INT_I2S4_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S4_N_ADDR, m)
#define HWIO_LPASS_INT_I2S4_N_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S4_N_ADDR,v)
#define HWIO_LPASS_INT_I2S4_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S4_N_ADDR,m,v,HWIO_LPASS_INT_I2S4_N_IN)
#define HWIO_LPASS_INT_I2S4_N_NOT_N_MINUS_M_BMSK                                                                            0xff
#define HWIO_LPASS_INT_I2S4_N_NOT_N_MINUS_M_SHFT                                                                             0x0

#define HWIO_LPASS_INT_I2S4_D_ADDR                                                                                    (LPASS_CC_REG_BASE      + 0x00051010)
#define HWIO_LPASS_INT_I2S4_D_RMSK                                                                                          0xff
#define HWIO_LPASS_INT_I2S4_D_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S4_D_ADDR, HWIO_LPASS_INT_I2S4_D_RMSK)
#define HWIO_LPASS_INT_I2S4_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S4_D_ADDR, m)
#define HWIO_LPASS_INT_I2S4_D_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S4_D_ADDR,v)
#define HWIO_LPASS_INT_I2S4_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S4_D_ADDR,m,v,HWIO_LPASS_INT_I2S4_D_IN)
#define HWIO_LPASS_INT_I2S4_D_NOT_2D_BMSK                                                                                   0xff
#define HWIO_LPASS_INT_I2S4_D_NOT_2D_SHFT                                                                                    0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x00051014)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_RMSK                                                                 0x80000003
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_HW_CTL_BMSK                                                                 0x2
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_HW_CTL_SHFT                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_IBIT_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x00051018)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_RMSK                                                                 0x80000003
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_HW_CTL_BMSK                                                                 0x2
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_HW_CTL_SHFT                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EBIT_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_ADDR                                                            (LPASS_CC_REG_BASE      + 0x0005101c)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_RMSK                                                            0x80007f13
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_BMSK                                           0x80000000
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_SHFT                                                 0x1f
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_CLK_COUNTER_VALUE_BMSK                                              0x7f00
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_CLK_COUNTER_VALUE_SHFT                                                 0x8
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_IRQ_CLEAR_BMSK                                                        0x10
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_IRQ_CLEAR_SHFT                                                         0x4
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_CLK_COUNTER_EN_BMSK                                                    0x2
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_CLK_COUNTER_EN_SHFT                                                    0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_IRQ_EN_BMSK                                                            0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_EXT_CLK_DETECT_IRQ_EN_SHFT                                                            0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_TEST_ENABLE_ADDR                                                               (LPASS_CC_REG_BASE      + 0x00051020)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_TEST_ENABLE_RMSK                                                                      0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_TEST_ENABLE_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S4_TEST_ENABLE_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S4_TEST_ENABLE_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_TEST_ENABLE_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S4_TEST_ENABLE_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_TEST_ENABLE_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S4_TEST_ENABLE_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_TEST_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S4_TEST_ENABLE_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S4_TEST_ENABLE_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_TEST_ENABLE_TEST_CLK_ENABLE_BMSK                                                      0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S4_TEST_ENABLE_TEST_CLK_ENABLE_SHFT                                                      0x0

#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_ADDR                                                                           (LPASS_CC_REG_BASE      + 0x00052000)
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_RMSK                                                                           0x800000f3
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S5_6_CMD_RCGR_ADDR, HWIO_LPASS_INT_I2S5_6_CMD_RCGR_RMSK)
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S5_6_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S5_6_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S5_6_CMD_RCGR_ADDR,m,v,HWIO_LPASS_INT_I2S5_6_CMD_RCGR_IN)
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_ROOT_OFF_BMSK                                                                  0x80000000
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_ROOT_OFF_SHFT                                                                        0x1f
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_DIRTY_D_BMSK                                                                         0x80
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_DIRTY_D_SHFT                                                                          0x7
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_DIRTY_N_BMSK                                                                         0x40
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_DIRTY_N_SHFT                                                                          0x6
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_DIRTY_M_BMSK                                                                         0x20
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_DIRTY_M_SHFT                                                                          0x5
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                  0x10
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                   0x4
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_ROOT_EN_BMSK                                                                          0x2
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_ROOT_EN_SHFT                                                                          0x1
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_UPDATE_BMSK                                                                           0x1
#define HWIO_LPASS_INT_I2S5_6_CMD_RCGR_UPDATE_SHFT                                                                           0x0

#define HWIO_LPASS_INT_I2S5_6_CFG_RCGR_ADDR                                                                           (LPASS_CC_REG_BASE      + 0x00052004)
#define HWIO_LPASS_INT_I2S5_6_CFG_RCGR_RMSK                                                                               0x771f
#define HWIO_LPASS_INT_I2S5_6_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S5_6_CFG_RCGR_ADDR, HWIO_LPASS_INT_I2S5_6_CFG_RCGR_RMSK)
#define HWIO_LPASS_INT_I2S5_6_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S5_6_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_INT_I2S5_6_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S5_6_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_INT_I2S5_6_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S5_6_CFG_RCGR_ADDR,m,v,HWIO_LPASS_INT_I2S5_6_CFG_RCGR_IN)
#define HWIO_LPASS_INT_I2S5_6_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                   0x4000
#define HWIO_LPASS_INT_I2S5_6_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                      0xe
#define HWIO_LPASS_INT_I2S5_6_CFG_RCGR_MODE_BMSK                                                                          0x3000
#define HWIO_LPASS_INT_I2S5_6_CFG_RCGR_MODE_SHFT                                                                             0xc
#define HWIO_LPASS_INT_I2S5_6_CFG_RCGR_SRC_SEL_BMSK                                                                        0x700
#define HWIO_LPASS_INT_I2S5_6_CFG_RCGR_SRC_SEL_SHFT                                                                          0x8
#define HWIO_LPASS_INT_I2S5_6_CFG_RCGR_SRC_DIV_BMSK                                                                         0x1f
#define HWIO_LPASS_INT_I2S5_6_CFG_RCGR_SRC_DIV_SHFT                                                                          0x0

#define HWIO_LPASS_INT_I2S5_6_M_ADDR                                                                                  (LPASS_CC_REG_BASE      + 0x00052008)
#define HWIO_LPASS_INT_I2S5_6_M_RMSK                                                                                        0xff
#define HWIO_LPASS_INT_I2S5_6_M_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S5_6_M_ADDR, HWIO_LPASS_INT_I2S5_6_M_RMSK)
#define HWIO_LPASS_INT_I2S5_6_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S5_6_M_ADDR, m)
#define HWIO_LPASS_INT_I2S5_6_M_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S5_6_M_ADDR,v)
#define HWIO_LPASS_INT_I2S5_6_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S5_6_M_ADDR,m,v,HWIO_LPASS_INT_I2S5_6_M_IN)
#define HWIO_LPASS_INT_I2S5_6_M_M_BMSK                                                                                      0xff
#define HWIO_LPASS_INT_I2S5_6_M_M_SHFT                                                                                       0x0

#define HWIO_LPASS_INT_I2S5_6_N_ADDR                                                                                  (LPASS_CC_REG_BASE      + 0x0005200c)
#define HWIO_LPASS_INT_I2S5_6_N_RMSK                                                                                        0xff
#define HWIO_LPASS_INT_I2S5_6_N_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S5_6_N_ADDR, HWIO_LPASS_INT_I2S5_6_N_RMSK)
#define HWIO_LPASS_INT_I2S5_6_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S5_6_N_ADDR, m)
#define HWIO_LPASS_INT_I2S5_6_N_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S5_6_N_ADDR,v)
#define HWIO_LPASS_INT_I2S5_6_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S5_6_N_ADDR,m,v,HWIO_LPASS_INT_I2S5_6_N_IN)
#define HWIO_LPASS_INT_I2S5_6_N_NOT_N_MINUS_M_BMSK                                                                          0xff
#define HWIO_LPASS_INT_I2S5_6_N_NOT_N_MINUS_M_SHFT                                                                           0x0

#define HWIO_LPASS_INT_I2S5_6_D_ADDR                                                                                  (LPASS_CC_REG_BASE      + 0x00052010)
#define HWIO_LPASS_INT_I2S5_6_D_RMSK                                                                                        0xff
#define HWIO_LPASS_INT_I2S5_6_D_IN          \
        in_dword_masked(HWIO_LPASS_INT_I2S5_6_D_ADDR, HWIO_LPASS_INT_I2S5_6_D_RMSK)
#define HWIO_LPASS_INT_I2S5_6_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_I2S5_6_D_ADDR, m)
#define HWIO_LPASS_INT_I2S5_6_D_OUT(v)      \
        out_dword(HWIO_LPASS_INT_I2S5_6_D_ADDR,v)
#define HWIO_LPASS_INT_I2S5_6_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_I2S5_6_D_ADDR,m,v,HWIO_LPASS_INT_I2S5_6_D_IN)
#define HWIO_LPASS_INT_I2S5_6_D_NOT_2D_BMSK                                                                                 0xff
#define HWIO_LPASS_INT_I2S5_6_D_NOT_2D_SHFT                                                                                  0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_ADDR                                                               (LPASS_CC_REG_BASE      + 0x00052014)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_RMSK                                                               0x80000003
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_CLK_OFF_BMSK                                                       0x80000000
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_CLK_OFF_SHFT                                                             0x1f
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_HW_CTL_BMSK                                                               0x2
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_HW_CTL_SHFT                                                               0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_CLK_ENABLE_BMSK                                                           0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_IBIT_CBCR_CLK_ENABLE_SHFT                                                           0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_ADDR                                                               (LPASS_CC_REG_BASE      + 0x00052018)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_RMSK                                                               0x80000003
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_CLK_OFF_BMSK                                                       0x80000000
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_CLK_OFF_SHFT                                                             0x1f
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_HW_CTL_BMSK                                                               0x2
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_HW_CTL_SHFT                                                               0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_CLK_ENABLE_BMSK                                                           0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EBIT_CBCR_CLK_ENABLE_SHFT                                                           0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_ADDR                                                          (LPASS_CC_REG_BASE      + 0x0005201c)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_RMSK                                                          0x80007f13
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_BMSK                                         0x80000000
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_CLK_INACTIVE_IRQ_SHFT                                               0x1f
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_CLK_COUNTER_VALUE_BMSK                                            0x7f00
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_CLK_COUNTER_VALUE_SHFT                                               0x8
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_IRQ_CLEAR_BMSK                                                      0x10
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_IRQ_CLEAR_SHFT                                                       0x4
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_CLK_COUNTER_EN_BMSK                                                  0x2
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_CLK_COUNTER_EN_SHFT                                                  0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_IRQ_EN_BMSK                                                          0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_EXT_CLK_DETECT_IRQ_EN_SHFT                                                          0x0

#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_TEST_ENABLE_ADDR                                                             (LPASS_CC_REG_BASE      + 0x00052020)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_TEST_ENABLE_RMSK                                                                    0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_TEST_ENABLE_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_TEST_ENABLE_ADDR, HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_TEST_ENABLE_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_TEST_ENABLE_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_TEST_ENABLE_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_TEST_ENABLE_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_TEST_ENABLE_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_TEST_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_TEST_ENABLE_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_TEST_ENABLE_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_TEST_ENABLE_TEST_CLK_ENABLE_BMSK                                                    0x1
#define HWIO_LPASS_AUDIO_CORE_INT_I2S5_6_TEST_ENABLE_TEST_CLK_ENABLE_SHFT                                                    0x0

#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00053000)
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_RMSK                                                                            0x800000f3
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_INT_MCLK0_CMD_RCGR_ADDR, HWIO_LPASS_INT_MCLK0_CMD_RCGR_RMSK)
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_MCLK0_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_INT_MCLK0_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_MCLK0_CMD_RCGR_ADDR,m,v,HWIO_LPASS_INT_MCLK0_CMD_RCGR_IN)
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_ROOT_OFF_BMSK                                                                   0x80000000
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_ROOT_OFF_SHFT                                                                         0x1f
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_DIRTY_D_BMSK                                                                          0x80
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_DIRTY_D_SHFT                                                                           0x7
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_DIRTY_N_BMSK                                                                          0x40
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_DIRTY_N_SHFT                                                                           0x6
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_DIRTY_M_BMSK                                                                          0x20
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_DIRTY_M_SHFT                                                                           0x5
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                   0x10
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                    0x4
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_ROOT_EN_BMSK                                                                           0x2
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_ROOT_EN_SHFT                                                                           0x1
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_UPDATE_BMSK                                                                            0x1
#define HWIO_LPASS_INT_MCLK0_CMD_RCGR_UPDATE_SHFT                                                                            0x0

#define HWIO_LPASS_INT_MCLK0_CFG_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00053004)
#define HWIO_LPASS_INT_MCLK0_CFG_RCGR_RMSK                                                                                0x771f
#define HWIO_LPASS_INT_MCLK0_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_INT_MCLK0_CFG_RCGR_ADDR, HWIO_LPASS_INT_MCLK0_CFG_RCGR_RMSK)
#define HWIO_LPASS_INT_MCLK0_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_MCLK0_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_INT_MCLK0_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_INT_MCLK0_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_INT_MCLK0_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_MCLK0_CFG_RCGR_ADDR,m,v,HWIO_LPASS_INT_MCLK0_CFG_RCGR_IN)
#define HWIO_LPASS_INT_MCLK0_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                    0x4000
#define HWIO_LPASS_INT_MCLK0_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                       0xe
#define HWIO_LPASS_INT_MCLK0_CFG_RCGR_MODE_BMSK                                                                           0x3000
#define HWIO_LPASS_INT_MCLK0_CFG_RCGR_MODE_SHFT                                                                              0xc
#define HWIO_LPASS_INT_MCLK0_CFG_RCGR_SRC_SEL_BMSK                                                                         0x700
#define HWIO_LPASS_INT_MCLK0_CFG_RCGR_SRC_SEL_SHFT                                                                           0x8
#define HWIO_LPASS_INT_MCLK0_CFG_RCGR_SRC_DIV_BMSK                                                                          0x1f
#define HWIO_LPASS_INT_MCLK0_CFG_RCGR_SRC_DIV_SHFT                                                                           0x0

#define HWIO_LPASS_INT_MCLK0_M_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00053008)
#define HWIO_LPASS_INT_MCLK0_M_RMSK                                                                                         0xff
#define HWIO_LPASS_INT_MCLK0_M_IN          \
        in_dword_masked(HWIO_LPASS_INT_MCLK0_M_ADDR, HWIO_LPASS_INT_MCLK0_M_RMSK)
#define HWIO_LPASS_INT_MCLK0_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_MCLK0_M_ADDR, m)
#define HWIO_LPASS_INT_MCLK0_M_OUT(v)      \
        out_dword(HWIO_LPASS_INT_MCLK0_M_ADDR,v)
#define HWIO_LPASS_INT_MCLK0_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_MCLK0_M_ADDR,m,v,HWIO_LPASS_INT_MCLK0_M_IN)
#define HWIO_LPASS_INT_MCLK0_M_M_BMSK                                                                                       0xff
#define HWIO_LPASS_INT_MCLK0_M_M_SHFT                                                                                        0x0

#define HWIO_LPASS_INT_MCLK0_N_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x0005300c)
#define HWIO_LPASS_INT_MCLK0_N_RMSK                                                                                         0xff
#define HWIO_LPASS_INT_MCLK0_N_IN          \
        in_dword_masked(HWIO_LPASS_INT_MCLK0_N_ADDR, HWIO_LPASS_INT_MCLK0_N_RMSK)
#define HWIO_LPASS_INT_MCLK0_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_MCLK0_N_ADDR, m)
#define HWIO_LPASS_INT_MCLK0_N_OUT(v)      \
        out_dword(HWIO_LPASS_INT_MCLK0_N_ADDR,v)
#define HWIO_LPASS_INT_MCLK0_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_MCLK0_N_ADDR,m,v,HWIO_LPASS_INT_MCLK0_N_IN)
#define HWIO_LPASS_INT_MCLK0_N_NOT_N_MINUS_M_BMSK                                                                           0xff
#define HWIO_LPASS_INT_MCLK0_N_NOT_N_MINUS_M_SHFT                                                                            0x0

#define HWIO_LPASS_INT_MCLK0_D_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00053010)
#define HWIO_LPASS_INT_MCLK0_D_RMSK                                                                                         0xff
#define HWIO_LPASS_INT_MCLK0_D_IN          \
        in_dword_masked(HWIO_LPASS_INT_MCLK0_D_ADDR, HWIO_LPASS_INT_MCLK0_D_RMSK)
#define HWIO_LPASS_INT_MCLK0_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_MCLK0_D_ADDR, m)
#define HWIO_LPASS_INT_MCLK0_D_OUT(v)      \
        out_dword(HWIO_LPASS_INT_MCLK0_D_ADDR,v)
#define HWIO_LPASS_INT_MCLK0_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_MCLK0_D_ADDR,m,v,HWIO_LPASS_INT_MCLK0_D_IN)
#define HWIO_LPASS_INT_MCLK0_D_NOT_2D_BMSK                                                                                  0xff
#define HWIO_LPASS_INT_MCLK0_D_NOT_2D_SHFT                                                                                   0x0

#define HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_ADDR                                                                     (LPASS_CC_REG_BASE      + 0x00053014)
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_RMSK                                                                     0x80000003
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_CLK_OFF_BMSK                                                             0x80000000
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_CLK_OFF_SHFT                                                                   0x1f
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_HW_CTL_BMSK                                                                     0x2
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_HW_CTL_SHFT                                                                     0x1
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_CLK_ENABLE_BMSK                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK0_CBCR_CLK_ENABLE_SHFT                                                                 0x0

#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00054000)
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_RMSK                                                                            0x800000f3
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_INT_MCLK1_CMD_RCGR_ADDR, HWIO_LPASS_INT_MCLK1_CMD_RCGR_RMSK)
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_MCLK1_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_INT_MCLK1_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_MCLK1_CMD_RCGR_ADDR,m,v,HWIO_LPASS_INT_MCLK1_CMD_RCGR_IN)
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_ROOT_OFF_BMSK                                                                   0x80000000
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_ROOT_OFF_SHFT                                                                         0x1f
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_DIRTY_D_BMSK                                                                          0x80
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_DIRTY_D_SHFT                                                                           0x7
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_DIRTY_N_BMSK                                                                          0x40
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_DIRTY_N_SHFT                                                                           0x6
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_DIRTY_M_BMSK                                                                          0x20
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_DIRTY_M_SHFT                                                                           0x5
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                   0x10
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                    0x4
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_ROOT_EN_BMSK                                                                           0x2
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_ROOT_EN_SHFT                                                                           0x1
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_UPDATE_BMSK                                                                            0x1
#define HWIO_LPASS_INT_MCLK1_CMD_RCGR_UPDATE_SHFT                                                                            0x0

#define HWIO_LPASS_INT_MCLK1_CFG_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00054004)
#define HWIO_LPASS_INT_MCLK1_CFG_RCGR_RMSK                                                                                0x771f
#define HWIO_LPASS_INT_MCLK1_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_INT_MCLK1_CFG_RCGR_ADDR, HWIO_LPASS_INT_MCLK1_CFG_RCGR_RMSK)
#define HWIO_LPASS_INT_MCLK1_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_MCLK1_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_INT_MCLK1_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_INT_MCLK1_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_INT_MCLK1_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_MCLK1_CFG_RCGR_ADDR,m,v,HWIO_LPASS_INT_MCLK1_CFG_RCGR_IN)
#define HWIO_LPASS_INT_MCLK1_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                    0x4000
#define HWIO_LPASS_INT_MCLK1_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                       0xe
#define HWIO_LPASS_INT_MCLK1_CFG_RCGR_MODE_BMSK                                                                           0x3000
#define HWIO_LPASS_INT_MCLK1_CFG_RCGR_MODE_SHFT                                                                              0xc
#define HWIO_LPASS_INT_MCLK1_CFG_RCGR_SRC_SEL_BMSK                                                                         0x700
#define HWIO_LPASS_INT_MCLK1_CFG_RCGR_SRC_SEL_SHFT                                                                           0x8
#define HWIO_LPASS_INT_MCLK1_CFG_RCGR_SRC_DIV_BMSK                                                                          0x1f
#define HWIO_LPASS_INT_MCLK1_CFG_RCGR_SRC_DIV_SHFT                                                                           0x0

#define HWIO_LPASS_INT_MCLK1_M_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00054008)
#define HWIO_LPASS_INT_MCLK1_M_RMSK                                                                                         0xff
#define HWIO_LPASS_INT_MCLK1_M_IN          \
        in_dword_masked(HWIO_LPASS_INT_MCLK1_M_ADDR, HWIO_LPASS_INT_MCLK1_M_RMSK)
#define HWIO_LPASS_INT_MCLK1_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_MCLK1_M_ADDR, m)
#define HWIO_LPASS_INT_MCLK1_M_OUT(v)      \
        out_dword(HWIO_LPASS_INT_MCLK1_M_ADDR,v)
#define HWIO_LPASS_INT_MCLK1_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_MCLK1_M_ADDR,m,v,HWIO_LPASS_INT_MCLK1_M_IN)
#define HWIO_LPASS_INT_MCLK1_M_M_BMSK                                                                                       0xff
#define HWIO_LPASS_INT_MCLK1_M_M_SHFT                                                                                        0x0

#define HWIO_LPASS_INT_MCLK1_N_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x0005400c)
#define HWIO_LPASS_INT_MCLK1_N_RMSK                                                                                         0xff
#define HWIO_LPASS_INT_MCLK1_N_IN          \
        in_dword_masked(HWIO_LPASS_INT_MCLK1_N_ADDR, HWIO_LPASS_INT_MCLK1_N_RMSK)
#define HWIO_LPASS_INT_MCLK1_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_MCLK1_N_ADDR, m)
#define HWIO_LPASS_INT_MCLK1_N_OUT(v)      \
        out_dword(HWIO_LPASS_INT_MCLK1_N_ADDR,v)
#define HWIO_LPASS_INT_MCLK1_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_MCLK1_N_ADDR,m,v,HWIO_LPASS_INT_MCLK1_N_IN)
#define HWIO_LPASS_INT_MCLK1_N_NOT_N_MINUS_M_BMSK                                                                           0xff
#define HWIO_LPASS_INT_MCLK1_N_NOT_N_MINUS_M_SHFT                                                                            0x0

#define HWIO_LPASS_INT_MCLK1_D_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00054010)
#define HWIO_LPASS_INT_MCLK1_D_RMSK                                                                                         0xff
#define HWIO_LPASS_INT_MCLK1_D_IN          \
        in_dword_masked(HWIO_LPASS_INT_MCLK1_D_ADDR, HWIO_LPASS_INT_MCLK1_D_RMSK)
#define HWIO_LPASS_INT_MCLK1_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_INT_MCLK1_D_ADDR, m)
#define HWIO_LPASS_INT_MCLK1_D_OUT(v)      \
        out_dword(HWIO_LPASS_INT_MCLK1_D_ADDR,v)
#define HWIO_LPASS_INT_MCLK1_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_INT_MCLK1_D_ADDR,m,v,HWIO_LPASS_INT_MCLK1_D_IN)
#define HWIO_LPASS_INT_MCLK1_D_NOT_2D_BMSK                                                                                  0xff
#define HWIO_LPASS_INT_MCLK1_D_NOT_2D_SHFT                                                                                   0x0

#define HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_ADDR                                                                     (LPASS_CC_REG_BASE      + 0x00054014)
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_RMSK                                                                     0x80000003
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_ADDR, HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_RMSK)
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_ADDR, m)
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_ADDR,v)
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_ADDR,m,v,HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_IN)
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_CLK_OFF_BMSK                                                             0x80000000
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_CLK_OFF_SHFT                                                                   0x1f
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_HW_CTL_BMSK                                                                     0x2
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_HW_CTL_SHFT                                                                     0x1
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_CLK_ENABLE_BMSK                                                                 0x1
#define HWIO_LPASS_AUDIO_CORE_INT_MCLK1_CBCR_CLK_ENABLE_SHFT                                                                 0x0

#define HWIO_LPASS_ISLAND_SCC_UART4_BCR_ADDR                                                                          (LPASS_CC_REG_BASE      + 0x00055000)
#define HWIO_LPASS_ISLAND_SCC_UART4_BCR_RMSK                                                                                 0x1
#define HWIO_LPASS_ISLAND_SCC_UART4_BCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_UART4_BCR_ADDR, HWIO_LPASS_ISLAND_SCC_UART4_BCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_UART4_BCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_UART4_BCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_UART4_BCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_UART4_BCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_UART4_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_UART4_BCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_UART4_BCR_IN)
#define HWIO_LPASS_ISLAND_SCC_UART4_BCR_BLK_ARES_BMSK                                                                        0x1
#define HWIO_LPASS_ISLAND_SCC_UART4_BCR_BLK_ARES_SHFT                                                                        0x0

#define HWIO_LPASS_SCC_UART4_CMD_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00055004)
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_RMSK                                                                            0x800000f3
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART4_CMD_RCGR_ADDR, HWIO_LPASS_SCC_UART4_CMD_RCGR_RMSK)
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART4_CMD_RCGR_ADDR, m)
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART4_CMD_RCGR_ADDR,v)
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART4_CMD_RCGR_ADDR,m,v,HWIO_LPASS_SCC_UART4_CMD_RCGR_IN)
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_ROOT_OFF_BMSK                                                                   0x80000000
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_ROOT_OFF_SHFT                                                                         0x1f
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_DIRTY_D_BMSK                                                                          0x80
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_DIRTY_D_SHFT                                                                           0x7
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_DIRTY_N_BMSK                                                                          0x40
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_DIRTY_N_SHFT                                                                           0x6
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_DIRTY_M_BMSK                                                                          0x20
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_DIRTY_M_SHFT                                                                           0x5
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                                   0x10
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                                    0x4
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_ROOT_EN_BMSK                                                                           0x2
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_ROOT_EN_SHFT                                                                           0x1
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_UPDATE_BMSK                                                                            0x1
#define HWIO_LPASS_SCC_UART4_CMD_RCGR_UPDATE_SHFT                                                                            0x0

#define HWIO_LPASS_SCC_UART4_CFG_RCGR_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00055008)
#define HWIO_LPASS_SCC_UART4_CFG_RCGR_RMSK                                                                                0x771f
#define HWIO_LPASS_SCC_UART4_CFG_RCGR_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART4_CFG_RCGR_ADDR, HWIO_LPASS_SCC_UART4_CFG_RCGR_RMSK)
#define HWIO_LPASS_SCC_UART4_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART4_CFG_RCGR_ADDR, m)
#define HWIO_LPASS_SCC_UART4_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART4_CFG_RCGR_ADDR,v)
#define HWIO_LPASS_SCC_UART4_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART4_CFG_RCGR_ADDR,m,v,HWIO_LPASS_SCC_UART4_CFG_RCGR_IN)
#define HWIO_LPASS_SCC_UART4_CFG_RCGR_ALT_SRC_SEL_BMSK                                                                    0x4000
#define HWIO_LPASS_SCC_UART4_CFG_RCGR_ALT_SRC_SEL_SHFT                                                                       0xe
#define HWIO_LPASS_SCC_UART4_CFG_RCGR_MODE_BMSK                                                                           0x3000
#define HWIO_LPASS_SCC_UART4_CFG_RCGR_MODE_SHFT                                                                              0xc
#define HWIO_LPASS_SCC_UART4_CFG_RCGR_SRC_SEL_BMSK                                                                         0x700
#define HWIO_LPASS_SCC_UART4_CFG_RCGR_SRC_SEL_SHFT                                                                           0x8
#define HWIO_LPASS_SCC_UART4_CFG_RCGR_SRC_DIV_BMSK                                                                          0x1f
#define HWIO_LPASS_SCC_UART4_CFG_RCGR_SRC_DIV_SHFT                                                                           0x0

#define HWIO_LPASS_SCC_UART4_M_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x0005500c)
#define HWIO_LPASS_SCC_UART4_M_RMSK                                                                                       0xffff
#define HWIO_LPASS_SCC_UART4_M_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART4_M_ADDR, HWIO_LPASS_SCC_UART4_M_RMSK)
#define HWIO_LPASS_SCC_UART4_M_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART4_M_ADDR, m)
#define HWIO_LPASS_SCC_UART4_M_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART4_M_ADDR,v)
#define HWIO_LPASS_SCC_UART4_M_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART4_M_ADDR,m,v,HWIO_LPASS_SCC_UART4_M_IN)
#define HWIO_LPASS_SCC_UART4_M_M_BMSK                                                                                     0xffff
#define HWIO_LPASS_SCC_UART4_M_M_SHFT                                                                                        0x0

#define HWIO_LPASS_SCC_UART4_N_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00055010)
#define HWIO_LPASS_SCC_UART4_N_RMSK                                                                                       0xffff
#define HWIO_LPASS_SCC_UART4_N_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART4_N_ADDR, HWIO_LPASS_SCC_UART4_N_RMSK)
#define HWIO_LPASS_SCC_UART4_N_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART4_N_ADDR, m)
#define HWIO_LPASS_SCC_UART4_N_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART4_N_ADDR,v)
#define HWIO_LPASS_SCC_UART4_N_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART4_N_ADDR,m,v,HWIO_LPASS_SCC_UART4_N_IN)
#define HWIO_LPASS_SCC_UART4_N_NOT_N_MINUS_M_BMSK                                                                         0xffff
#define HWIO_LPASS_SCC_UART4_N_NOT_N_MINUS_M_SHFT                                                                            0x0

#define HWIO_LPASS_SCC_UART4_D_ADDR                                                                                   (LPASS_CC_REG_BASE      + 0x00055014)
#define HWIO_LPASS_SCC_UART4_D_RMSK                                                                                       0xffff
#define HWIO_LPASS_SCC_UART4_D_IN          \
        in_dword_masked(HWIO_LPASS_SCC_UART4_D_ADDR, HWIO_LPASS_SCC_UART4_D_RMSK)
#define HWIO_LPASS_SCC_UART4_D_INM(m)      \
        in_dword_masked(HWIO_LPASS_SCC_UART4_D_ADDR, m)
#define HWIO_LPASS_SCC_UART4_D_OUT(v)      \
        out_dword(HWIO_LPASS_SCC_UART4_D_ADDR,v)
#define HWIO_LPASS_SCC_UART4_D_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCC_UART4_D_ADDR,m,v,HWIO_LPASS_SCC_UART4_D_IN)
#define HWIO_LPASS_SCC_UART4_D_NOT_2D_BMSK                                                                                0xffff
#define HWIO_LPASS_SCC_UART4_D_NOT_2D_SHFT                                                                                   0x0

#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART4_CBCR_ADDR                                                                 (LPASS_CC_REG_BASE      + 0x00055018)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART4_CBCR_RMSK                                                                 0x80000001
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART4_CBCR_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_UART_DM_UART4_CBCR_ADDR, HWIO_LPASS_ISLAND_SCC_UART_DM_UART4_CBCR_RMSK)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART4_CBCR_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_SCC_UART_DM_UART4_CBCR_ADDR, m)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART4_CBCR_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_SCC_UART_DM_UART4_CBCR_ADDR,v)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART4_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_SCC_UART_DM_UART4_CBCR_ADDR,m,v,HWIO_LPASS_ISLAND_SCC_UART_DM_UART4_CBCR_IN)
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART4_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART4_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART4_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_LPASS_ISLAND_SCC_UART_DM_UART4_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_LPASS_ISLAND_MODE_SMMU_CTRL_ADDR                                                                         (LPASS_CC_REG_BASE      + 0x00056000)
#define HWIO_LPASS_ISLAND_MODE_SMMU_CTRL_RMSK                                                                                0x1
#define HWIO_LPASS_ISLAND_MODE_SMMU_CTRL_IN          \
        in_dword_masked(HWIO_LPASS_ISLAND_MODE_SMMU_CTRL_ADDR, HWIO_LPASS_ISLAND_MODE_SMMU_CTRL_RMSK)
#define HWIO_LPASS_ISLAND_MODE_SMMU_CTRL_INM(m)      \
        in_dword_masked(HWIO_LPASS_ISLAND_MODE_SMMU_CTRL_ADDR, m)
#define HWIO_LPASS_ISLAND_MODE_SMMU_CTRL_OUT(v)      \
        out_dword(HWIO_LPASS_ISLAND_MODE_SMMU_CTRL_ADDR,v)
#define HWIO_LPASS_ISLAND_MODE_SMMU_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_ISLAND_MODE_SMMU_CTRL_ADDR,m,v,HWIO_LPASS_ISLAND_MODE_SMMU_CTRL_IN)
#define HWIO_LPASS_ISLAND_MODE_SMMU_CTRL_ISLAND_MODE_ENTRY_ENABLE_BMSK                                                       0x1
#define HWIO_LPASS_ISLAND_MODE_SMMU_CTRL_ISLAND_MODE_ENTRY_ENABLE_SHFT                                                       0x0

#define HWIO_LPASS_DBG_CLK_ADDR                                                                                       (LPASS_CC_REG_BASE      + 0x00057000)
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

#define HWIO_LPASS_TEST_BUS_SEL_ADDR                                                                                  (LPASS_CC_REG_BASE      + 0x00057004)
#define HWIO_LPASS_TEST_BUS_SEL_RMSK                                                                                         0x7
#define HWIO_LPASS_TEST_BUS_SEL_IN          \
        in_dword_masked(HWIO_LPASS_TEST_BUS_SEL_ADDR, HWIO_LPASS_TEST_BUS_SEL_RMSK)
#define HWIO_LPASS_TEST_BUS_SEL_INM(m)      \
        in_dword_masked(HWIO_LPASS_TEST_BUS_SEL_ADDR, m)
#define HWIO_LPASS_TEST_BUS_SEL_OUT(v)      \
        out_dword(HWIO_LPASS_TEST_BUS_SEL_ADDR,v)
#define HWIO_LPASS_TEST_BUS_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_TEST_BUS_SEL_ADDR,m,v,HWIO_LPASS_TEST_BUS_SEL_IN)
#define HWIO_LPASS_TEST_BUS_SEL_SEL_BMSK                                                                                     0x7
#define HWIO_LPASS_TEST_BUS_SEL_SEL_SHFT                                                                                     0x0

#define HWIO_LPASS_PLLOUT_LV_TEST_SEL_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x00057008)
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

#define HWIO_LPASS_LPASS_CC_SPARE_REG_ADDR                                                                            (LPASS_CC_REG_BASE      + 0x0005700c)
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

#define HWIO_LPASS_LPASS_CC_SPARE1_REG_ADDR                                                                           (LPASS_CC_REG_BASE      + 0x00057010)
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
 * MODULE: LPASS_QDSP6V60SS_L2VIC
 *--------------------------------------------------------------------------*/

#define LPASS_QDSP6V60SS_L2VIC_REG_BASE                                (LPASS_BASE      + 0x00790000)

#define HWIO_LPASS_QDSP6SS_L2VIC_VID_ADDR                              (LPASS_QDSP6V60SS_L2VIC_REG_BASE      + 0x00000000)
#define HWIO_LPASS_QDSP6SS_L2VIC_VID_RMSK                                   0x3ff
#define HWIO_LPASS_QDSP6SS_L2VIC_VID_IN          \
        in_dword_masked(HWIO_LPASS_QDSP6SS_L2VIC_VID_ADDR, HWIO_LPASS_QDSP6SS_L2VIC_VID_RMSK)
#define HWIO_LPASS_QDSP6SS_L2VIC_VID_INM(m)      \
        in_dword_masked(HWIO_LPASS_QDSP6SS_L2VIC_VID_ADDR, m)
#define HWIO_LPASS_QDSP6SS_L2VIC_VID_VID_BMSK                               0x3ff
#define HWIO_LPASS_QDSP6SS_L2VIC_VID_VID_SHFT                                 0x0

#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLEn_ADDR(n)                   (LPASS_QDSP6V60SS_L2VIC_REG_BASE      + 0x00000100 + 0x4 * (n))
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLEn_RMSK                      0xffffffff
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLEn_MAXn                              31
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLEn_INI(n)        \
        in_dword_masked(HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLEn_ADDR(n), HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLEn_RMSK)
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLEn_INMI(n,mask)    \
        in_dword_masked(HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLEn_ADDR(n), mask)
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLEn_OUTI(n,val)    \
        out_dword(HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLEn_ADDR(n),val)
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLEn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLEn_ADDR(n),mask,val,HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLEn_INI(n))
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLEn_ENABLE_BMSK               0xffffffff
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLEn_ENABLE_SHFT                      0x0

#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLE_CLEARn_ADDR(n)             (LPASS_QDSP6V60SS_L2VIC_REG_BASE      + 0x00000180 + 0x4 * (n))
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLE_CLEARn_RMSK                0xffffffff
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLE_CLEARn_MAXn                        31
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLE_CLEARn_OUTI(n,val)    \
        out_dword(HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLE_CLEARn_ADDR(n),val)
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLE_CLEARn_CLEAR_BMSK          0xffffffff
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLE_CLEARn_CLEAR_SHFT                 0x0

#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLE_SETn_ADDR(n)               (LPASS_QDSP6V60SS_L2VIC_REG_BASE      + 0x00000200 + 0x4 * (n))
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLE_SETn_RMSK                  0xffffffff
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLE_SETn_MAXn                          31
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLE_SETn_OUTI(n,val)    \
        out_dword(HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLE_SETn_ADDR(n),val)
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLE_SETn_SET_BMSK              0xffffffff
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_ENABLE_SETn_SET_SHFT                     0x0

#define HWIO_LPASS_QDSP6SS_L2VIC_INT_TYPEn_ADDR(n)                     (LPASS_QDSP6V60SS_L2VIC_REG_BASE      + 0x00000280 + 0x4 * (n))
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_TYPEn_RMSK                        0xffffffff
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_TYPEn_MAXn                                31
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_TYPEn_INI(n)        \
        in_dword_masked(HWIO_LPASS_QDSP6SS_L2VIC_INT_TYPEn_ADDR(n), HWIO_LPASS_QDSP6SS_L2VIC_INT_TYPEn_RMSK)
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_TYPEn_INMI(n,mask)    \
        in_dword_masked(HWIO_LPASS_QDSP6SS_L2VIC_INT_TYPEn_ADDR(n), mask)
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_TYPEn_OUTI(n,val)    \
        out_dword(HWIO_LPASS_QDSP6SS_L2VIC_INT_TYPEn_ADDR(n),val)
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_TYPEn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_LPASS_QDSP6SS_L2VIC_INT_TYPEn_ADDR(n),mask,val,HWIO_LPASS_QDSP6SS_L2VIC_INT_TYPEn_INI(n))
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_TYPEn_SRC_TYPE_BMSK               0xffffffff
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_TYPEn_SRC_TYPE_SHFT                      0x0

#define HWIO_LPASS_QDSP6SS_L2VIC_INT_STATUSn_ADDR(n)                   (LPASS_QDSP6V60SS_L2VIC_REG_BASE      + 0x00000380 + 0x4 * (n))
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_STATUSn_RMSK                      0xffffffff
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_STATUSn_MAXn                              31
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_STATUSn_INI(n)        \
        in_dword_masked(HWIO_LPASS_QDSP6SS_L2VIC_INT_STATUSn_ADDR(n), HWIO_LPASS_QDSP6SS_L2VIC_INT_STATUSn_RMSK)
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_STATUSn_INMI(n,mask)    \
        in_dword_masked(HWIO_LPASS_QDSP6SS_L2VIC_INT_STATUSn_ADDR(n), mask)
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_STATUSn_STATUS_BMSK               0xffffffff
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_STATUSn_STATUS_SHFT                      0x0

#define HWIO_LPASS_QDSP6SS_L2VIC_INT_CLEARn_ADDR(n)                    (LPASS_QDSP6V60SS_L2VIC_REG_BASE      + 0x00000400 + 0x4 * (n))
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_CLEARn_RMSK                       0xffffffff
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_CLEARn_MAXn                               31
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_CLEARn_OUTI(n,val)    \
        out_dword(HWIO_LPASS_QDSP6SS_L2VIC_INT_CLEARn_ADDR(n),val)
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_CLEARn_CLEAR_BMSK                 0xffffffff
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_CLEARn_CLEAR_SHFT                        0x0

#define HWIO_LPASS_QDSP6SS_L2VIC_SOFT_INTn_ADDR(n)                     (LPASS_QDSP6V60SS_L2VIC_REG_BASE      + 0x00000480 + 0x4 * (n))
#define HWIO_LPASS_QDSP6SS_L2VIC_SOFT_INTn_RMSK                        0xffffffff
#define HWIO_LPASS_QDSP6SS_L2VIC_SOFT_INTn_MAXn                                31
#define HWIO_LPASS_QDSP6SS_L2VIC_SOFT_INTn_OUTI(n,val)    \
        out_dword(HWIO_LPASS_QDSP6SS_L2VIC_SOFT_INTn_ADDR(n),val)
#define HWIO_LPASS_QDSP6SS_L2VIC_SOFT_INTn_SW_INT_BMSK                 0xffffffff
#define HWIO_LPASS_QDSP6SS_L2VIC_SOFT_INTn_SW_INT_SHFT                        0x0

#define HWIO_LPASS_QDSP6SS_L2VIC_INT_PENDINGn_ADDR(n)                  (LPASS_QDSP6V60SS_L2VIC_REG_BASE      + 0x00000500 + 0x4 * (n))
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_PENDINGn_RMSK                     0xffffffff
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_PENDINGn_MAXn                             31
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_PENDINGn_INI(n)        \
        in_dword_masked(HWIO_LPASS_QDSP6SS_L2VIC_INT_PENDINGn_ADDR(n), HWIO_LPASS_QDSP6SS_L2VIC_INT_PENDINGn_RMSK)
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_PENDINGn_INMI(n,mask)    \
        in_dword_masked(HWIO_LPASS_QDSP6SS_L2VIC_INT_PENDINGn_ADDR(n), mask)
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_PENDINGn_STATUS_BMSK              0xffffffff
#define HWIO_LPASS_QDSP6SS_L2VIC_INT_PENDINGn_STATUS_SHFT                     0x0

#endif /* __USLEEP_HALHWIO_H__ */
