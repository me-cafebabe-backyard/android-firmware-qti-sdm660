#ifndef __DDR_HWIO_H__
#define __DDR_HWIO_H__
/*
===========================================================================
*/
/**
  @file ddr_hwio.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    MSM8998 (Nazgul) [nazgul_v1.0_p3q3r32]
 
  This file contains HWIO register definitions for the following modules:
    BIMC_S_SYS0_SWAY
    BIMC_S_SYS1_SWAY
    BIMC_M_APP_MPORT

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

  $Header: //components/rel/rpm.bf/1.8/core/boot/ddr/hw/sdm660/ddr_hwio.h#1 $
  $DateTime: 2016/11/03 00:13:13 $
  $Author: pwbldsvc $

  ===========================================================================
*/

/*----------------------------------------------------------------------------
 * MODULE: BIMC_S_SYS0_SWAY
 *--------------------------------------------------------------------------*/

#define BIMC_S_SYS0_SWAY_REG_BASE                                                        (DDR_SS_BASE      + 0x00053000)

#define HWIO_BIMC_S_SYS0_SWAY_COMPONENT_INFO_ADDR                                        (BIMC_S_SYS0_SWAY_REG_BASE      + 0x00000000)
#define HWIO_BIMC_S_SYS0_SWAY_COMPONENT_INFO_RMSK                                          0xffffff
#define HWIO_BIMC_S_SYS0_SWAY_COMPONENT_INFO_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_COMPONENT_INFO_ADDR, HWIO_BIMC_S_SYS0_SWAY_COMPONENT_INFO_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_COMPONENT_INFO_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_COMPONENT_INFO_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_COMPONENT_INFO_INSTANCE_BMSK                                 0xff0000
#define HWIO_BIMC_S_SYS0_SWAY_COMPONENT_INFO_INSTANCE_SHFT                                     0x10
#define HWIO_BIMC_S_SYS0_SWAY_COMPONENT_INFO_SUB_TYPE_BMSK                                   0xff00
#define HWIO_BIMC_S_SYS0_SWAY_COMPONENT_INFO_SUB_TYPE_SHFT                                      0x8
#define HWIO_BIMC_S_SYS0_SWAY_COMPONENT_INFO_TYPE_BMSK                                         0xff
#define HWIO_BIMC_S_SYS0_SWAY_COMPONENT_INFO_TYPE_SHFT                                          0x0

#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_0_ADDR                                  (BIMC_S_SYS0_SWAY_REG_BASE      + 0x00000020)
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_0_RMSK                                  0xff0000ff
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_0_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_0_ADDR, HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_0_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_0_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_0_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_0_SYNC_MODE_BMSK                        0xff000000
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_0_SYNC_MODE_SHFT                              0x18
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_0_FUNCTIONALITY_BMSK                          0xff
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_0_FUNCTIONALITY_SHFT                           0x0

#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_1_ADDR                                  (BIMC_S_SYS0_SWAY_REG_BASE      + 0x00000030)
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_1_RMSK                                  0xffffffff
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_1_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_1_ADDR, HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_1_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_1_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_1_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_1_MPORT_CONNECTIVITY_BMSK               0xffffffff
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_1_MPORT_CONNECTIVITY_SHFT                      0x0

#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_2_ADDR                                  (BIMC_S_SYS0_SWAY_REG_BASE      + 0x00000040)
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_2_RMSK                                  0xffffffff
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_2_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_2_ADDR, HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_2_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_2_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_2_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_2_S_DATA_WIDTH_BMSK                     0xffff0000
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_2_S_DATA_WIDTH_SHFT                           0x10
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_2_S_TID_WIDTH_BMSK                          0xff00
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_2_S_TID_WIDTH_SHFT                             0x8
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_2_S_MID_WIDTH_BMSK                            0xff
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_2_S_MID_WIDTH_SHFT                             0x0

#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_3_ADDR                                  (BIMC_S_SYS0_SWAY_REG_BASE      + 0x00000050)
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_3_RMSK                                  0xffffffff
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_3_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_3_ADDR, HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_3_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_3_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_3_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_3_RCH0_DEPTH_BMSK                       0xff000000
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_3_RCH0_DEPTH_SHFT                             0x18
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_3_BCH_DEPTH_BMSK                          0xff0000
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_3_BCH_DEPTH_SHFT                              0x10
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_3_WCH_DEPTH_BMSK                            0xff00
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_3_WCH_DEPTH_SHFT                               0x8
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_3_ACH_DEPTH_BMSK                              0xff
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_3_ACH_DEPTH_SHFT                               0x0

#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_4_ADDR                                  (BIMC_S_SYS0_SWAY_REG_BASE      + 0x00000060)
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_4_RMSK                                  0x800000ff
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_4_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_4_ADDR, HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_4_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_4_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_4_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_4_DUAL_RCH_EN_BMSK                      0x80000000
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_4_DUAL_RCH_EN_SHFT                            0x1f
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_4_RCH1_DEPTH_BMSK                             0xff
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_4_RCH1_DEPTH_SHFT                              0x0

#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_5_ADDR                                  (BIMC_S_SYS0_SWAY_REG_BASE      + 0x00000070)
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_5_RMSK                                  0x80000000
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_5_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_5_ADDR, HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_5_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_5_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_5_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_5_QOS_EN_BMSK                           0x80000000
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_5_QOS_EN_SHFT                                 0x1f

#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_6A_ADDR                                 (BIMC_S_SYS0_SWAY_REG_BASE      + 0x00000080)
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_6A_RMSK                                 0xffffffff
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_6A_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_6A_ADDR, HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_6A_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_6A_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_6A_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_6A_ACH_PIPELINE_STAGES_BMSK             0xffffffff
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_6A_ACH_PIPELINE_STAGES_SHFT                    0x0

#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_6B_ADDR                                 (BIMC_S_SYS0_SWAY_REG_BASE      + 0x00000084)
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_6B_RMSK                                 0xffffffff
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_6B_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_6B_ADDR, HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_6B_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_6B_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_6B_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_6B_WCH_PIPELINE_STAGES_BMSK             0xffffffff
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_6B_WCH_PIPELINE_STAGES_SHFT                    0x0

#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_6C_ADDR                                 (BIMC_S_SYS0_SWAY_REG_BASE      + 0x00000088)
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_6C_RMSK                                 0xffffffff
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_6C_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_6C_ADDR, HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_6C_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_6C_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_6C_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_6C_BCH_PIPELINE_STAGES_BMSK             0xffffffff
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_6C_BCH_PIPELINE_STAGES_SHFT                    0x0

#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_6D_ADDR                                 (BIMC_S_SYS0_SWAY_REG_BASE      + 0x0000008c)
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_6D_RMSK                                 0xffffffff
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_6D_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_6D_ADDR, HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_6D_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_6D_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_6D_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_6D_RCH_PIPELINE_STAGES_BMSK             0xffffffff
#define HWIO_BIMC_S_SYS0_SWAY_CONFIGURATION_INFO_6D_RCH_PIPELINE_STAGES_SHFT                    0x0

#define HWIO_BIMC_S_SYS0_SWAY_INTERRUPT_STATUS_ADDR                                      (BIMC_S_SYS0_SWAY_REG_BASE      + 0x00000100)
#define HWIO_BIMC_S_SYS0_SWAY_INTERRUPT_STATUS_RMSK                                             0x3
#define HWIO_BIMC_S_SYS0_SWAY_INTERRUPT_STATUS_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_INTERRUPT_STATUS_ADDR, HWIO_BIMC_S_SYS0_SWAY_INTERRUPT_STATUS_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_INTERRUPT_STATUS_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_INTERRUPT_STATUS_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_INTERRUPT_STATUS_RFU_BMSK                                         0x3
#define HWIO_BIMC_S_SYS0_SWAY_INTERRUPT_STATUS_RFU_SHFT                                         0x0

#define HWIO_BIMC_S_SYS0_SWAY_INTERRUPT_CLEAR_ADDR                                       (BIMC_S_SYS0_SWAY_REG_BASE      + 0x00000108)
#define HWIO_BIMC_S_SYS0_SWAY_INTERRUPT_CLEAR_RMSK                                              0x3
#define HWIO_BIMC_S_SYS0_SWAY_INTERRUPT_CLEAR_OUT(v)      \
        out_dword(HWIO_BIMC_S_SYS0_SWAY_INTERRUPT_CLEAR_ADDR,v)
#define HWIO_BIMC_S_SYS0_SWAY_INTERRUPT_CLEAR_RFU_BMSK                                          0x3
#define HWIO_BIMC_S_SYS0_SWAY_INTERRUPT_CLEAR_RFU_SHFT                                          0x0

#define HWIO_BIMC_S_SYS0_SWAY_INTERRUPT_ENABLE_ADDR                                      (BIMC_S_SYS0_SWAY_REG_BASE      + 0x0000010c)
#define HWIO_BIMC_S_SYS0_SWAY_INTERRUPT_ENABLE_RMSK                                             0x3
#define HWIO_BIMC_S_SYS0_SWAY_INTERRUPT_ENABLE_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_INTERRUPT_ENABLE_ADDR, HWIO_BIMC_S_SYS0_SWAY_INTERRUPT_ENABLE_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_INTERRUPT_ENABLE_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_INTERRUPT_ENABLE_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_INTERRUPT_ENABLE_OUT(v)      \
        out_dword(HWIO_BIMC_S_SYS0_SWAY_INTERRUPT_ENABLE_ADDR,v)
#define HWIO_BIMC_S_SYS0_SWAY_INTERRUPT_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_S_SYS0_SWAY_INTERRUPT_ENABLE_ADDR,m,v,HWIO_BIMC_S_SYS0_SWAY_INTERRUPT_ENABLE_IN)
#define HWIO_BIMC_S_SYS0_SWAY_INTERRUPT_ENABLE_RFU_BMSK                                         0x3
#define HWIO_BIMC_S_SYS0_SWAY_INTERRUPT_ENABLE_RFU_SHFT                                         0x0

#define HWIO_BIMC_S_SYS0_SWAY_CLOCK_CTRL_ADDR                                            (BIMC_S_SYS0_SWAY_REG_BASE      + 0x00000200)
#define HWIO_BIMC_S_SYS0_SWAY_CLOCK_CTRL_RMSK                                            0xff030003
#define HWIO_BIMC_S_SYS0_SWAY_CLOCK_CTRL_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_CLOCK_CTRL_ADDR, HWIO_BIMC_S_SYS0_SWAY_CLOCK_CTRL_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_CLOCK_CTRL_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_CLOCK_CTRL_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_CLOCK_CTRL_OUT(v)      \
        out_dword(HWIO_BIMC_S_SYS0_SWAY_CLOCK_CTRL_ADDR,v)
#define HWIO_BIMC_S_SYS0_SWAY_CLOCK_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_S_SYS0_SWAY_CLOCK_CTRL_ADDR,m,v,HWIO_BIMC_S_SYS0_SWAY_CLOCK_CTRL_IN)
#define HWIO_BIMC_S_SYS0_SWAY_CLOCK_CTRL_IDLE_HYSTERESIS_BMSK                            0xff000000
#define HWIO_BIMC_S_SYS0_SWAY_CLOCK_CTRL_IDLE_HYSTERESIS_SHFT                                  0x18
#define HWIO_BIMC_S_SYS0_SWAY_CLOCK_CTRL_IDLE_CLOCK_ON_REQ_EN_BMSK                          0x20000
#define HWIO_BIMC_S_SYS0_SWAY_CLOCK_CTRL_IDLE_CLOCK_ON_REQ_EN_SHFT                             0x11
#define HWIO_BIMC_S_SYS0_SWAY_CLOCK_CTRL_IDLE_GATING_EN_BMSK                                0x10000
#define HWIO_BIMC_S_SYS0_SWAY_CLOCK_CTRL_IDLE_GATING_EN_SHFT                                   0x10
#define HWIO_BIMC_S_SYS0_SWAY_CLOCK_CTRL_SLAVE_CLOCK_GATING_EN_BMSK                             0x2
#define HWIO_BIMC_S_SYS0_SWAY_CLOCK_CTRL_SLAVE_CLOCK_GATING_EN_SHFT                             0x1
#define HWIO_BIMC_S_SYS0_SWAY_CLOCK_CTRL_CORE_CLOCK_GATING_EN_BMSK                              0x1
#define HWIO_BIMC_S_SYS0_SWAY_CLOCK_CTRL_CORE_CLOCK_GATING_EN_SHFT                              0x0

#define HWIO_BIMC_S_SYS0_SWAY_CDC_CTRL_ADDR                                              (BIMC_S_SYS0_SWAY_REG_BASE      + 0x00000208)
#define HWIO_BIMC_S_SYS0_SWAY_CDC_CTRL_RMSK                                                     0x3
#define HWIO_BIMC_S_SYS0_SWAY_CDC_CTRL_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_CDC_CTRL_ADDR, HWIO_BIMC_S_SYS0_SWAY_CDC_CTRL_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_CDC_CTRL_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_CDC_CTRL_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_CDC_CTRL_OUT(v)      \
        out_dword(HWIO_BIMC_S_SYS0_SWAY_CDC_CTRL_ADDR,v)
#define HWIO_BIMC_S_SYS0_SWAY_CDC_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_S_SYS0_SWAY_CDC_CTRL_ADDR,m,v,HWIO_BIMC_S_SYS0_SWAY_CDC_CTRL_IN)
#define HWIO_BIMC_S_SYS0_SWAY_CDC_CTRL_SLAVE_CLOCK_DEMETA_SEL_BMSK                              0x2
#define HWIO_BIMC_S_SYS0_SWAY_CDC_CTRL_SLAVE_CLOCK_DEMETA_SEL_SHFT                              0x1
#define HWIO_BIMC_S_SYS0_SWAY_CDC_CTRL_CORE_CLOCK_DEMETA_SEL_BMSK                               0x1
#define HWIO_BIMC_S_SYS0_SWAY_CDC_CTRL_CORE_CLOCK_DEMETA_SEL_SHFT                               0x0

#define HWIO_BIMC_S_SYS0_SWAY_RCH_SELECT_ADDR                                            (BIMC_S_SYS0_SWAY_REG_BASE      + 0x00000210)
#define HWIO_BIMC_S_SYS0_SWAY_RCH_SELECT_RMSK                                                  0x3f
#define HWIO_BIMC_S_SYS0_SWAY_RCH_SELECT_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_RCH_SELECT_ADDR, HWIO_BIMC_S_SYS0_SWAY_RCH_SELECT_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_RCH_SELECT_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_RCH_SELECT_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_RCH_SELECT_UNUSED_BMSK                                           0x3f
#define HWIO_BIMC_S_SYS0_SWAY_RCH_SELECT_UNUSED_SHFT                                            0x0

#define HWIO_BIMC_S_SYS0_SWAY_MAX_OUTSTANDING_REQUESTS_ADDR                              (BIMC_S_SYS0_SWAY_REG_BASE      + 0x00000220)
#define HWIO_BIMC_S_SYS0_SWAY_MAX_OUTSTANDING_REQUESTS_RMSK                                  0xffff
#define HWIO_BIMC_S_SYS0_SWAY_MAX_OUTSTANDING_REQUESTS_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_MAX_OUTSTANDING_REQUESTS_ADDR, HWIO_BIMC_S_SYS0_SWAY_MAX_OUTSTANDING_REQUESTS_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_MAX_OUTSTANDING_REQUESTS_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_MAX_OUTSTANDING_REQUESTS_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_MAX_OUTSTANDING_REQUESTS_OUT(v)      \
        out_dword(HWIO_BIMC_S_SYS0_SWAY_MAX_OUTSTANDING_REQUESTS_ADDR,v)
#define HWIO_BIMC_S_SYS0_SWAY_MAX_OUTSTANDING_REQUESTS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_S_SYS0_SWAY_MAX_OUTSTANDING_REQUESTS_ADDR,m,v,HWIO_BIMC_S_SYS0_SWAY_MAX_OUTSTANDING_REQUESTS_IN)
#define HWIO_BIMC_S_SYS0_SWAY_MAX_OUTSTANDING_REQUESTS_WRITE_BMSK                            0xff00
#define HWIO_BIMC_S_SYS0_SWAY_MAX_OUTSTANDING_REQUESTS_WRITE_SHFT                               0x8
#define HWIO_BIMC_S_SYS0_SWAY_MAX_OUTSTANDING_REQUESTS_READ_BMSK                               0xff
#define HWIO_BIMC_S_SYS0_SWAY_MAX_OUTSTANDING_REQUESTS_READ_SHFT                                0x0

#define HWIO_BIMC_S_SYS0_SWAY_GATHERING_ADDR                                             (BIMC_S_SYS0_SWAY_REG_BASE      + 0x00000230)
#define HWIO_BIMC_S_SYS0_SWAY_GATHERING_RMSK                                                    0xf
#define HWIO_BIMC_S_SYS0_SWAY_GATHERING_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_GATHERING_ADDR, HWIO_BIMC_S_SYS0_SWAY_GATHERING_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_GATHERING_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_GATHERING_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_GATHERING_OUT(v)      \
        out_dword(HWIO_BIMC_S_SYS0_SWAY_GATHERING_ADDR,v)
#define HWIO_BIMC_S_SYS0_SWAY_GATHERING_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_S_SYS0_SWAY_GATHERING_ADDR,m,v,HWIO_BIMC_S_SYS0_SWAY_GATHERING_IN)
#define HWIO_BIMC_S_SYS0_SWAY_GATHERING_RD_GATHER_BEATS_BMSK                                    0xf
#define HWIO_BIMC_S_SYS0_SWAY_GATHERING_RD_GATHER_BEATS_SHFT                                    0x0

#define HWIO_BIMC_S_SYS0_SWAY_MODE_ADDR                                                  (BIMC_S_SYS0_SWAY_REG_BASE      + 0x00000240)
#define HWIO_BIMC_S_SYS0_SWAY_MODE_RMSK                                                  0x8000007f
#define HWIO_BIMC_S_SYS0_SWAY_MODE_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_MODE_ADDR, HWIO_BIMC_S_SYS0_SWAY_MODE_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_MODE_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_MODE_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_MODE_OUT(v)      \
        out_dword(HWIO_BIMC_S_SYS0_SWAY_MODE_ADDR,v)
#define HWIO_BIMC_S_SYS0_SWAY_MODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_S_SYS0_SWAY_MODE_ADDR,m,v,HWIO_BIMC_S_SYS0_SWAY_MODE_IN)
#define HWIO_BIMC_S_SYS0_SWAY_MODE_RFU_1_BMSK                                            0x80000000
#define HWIO_BIMC_S_SYS0_SWAY_MODE_RFU_1_SHFT                                                  0x1f
#define HWIO_BIMC_S_SYS0_SWAY_MODE_RESTRICT_ONE_PER_MASTER_BMSK                                0x40
#define HWIO_BIMC_S_SYS0_SWAY_MODE_RESTRICT_ONE_PER_MASTER_SHFT                                 0x6
#define HWIO_BIMC_S_SYS0_SWAY_MODE_CONVERT_16BYTE_EXCL_BMSK                                    0x20
#define HWIO_BIMC_S_SYS0_SWAY_MODE_CONVERT_16BYTE_EXCL_SHFT                                     0x5
#define HWIO_BIMC_S_SYS0_SWAY_MODE_CONVERT_ALL_EXCL_BMSK                                       0x10
#define HWIO_BIMC_S_SYS0_SWAY_MODE_CONVERT_ALL_EXCL_SHFT                                        0x4
#define HWIO_BIMC_S_SYS0_SWAY_MODE_RFU_0_BMSK                                                   0xe
#define HWIO_BIMC_S_SYS0_SWAY_MODE_RFU_0_SHFT                                                   0x1
#define HWIO_BIMC_S_SYS0_SWAY_MODE_BURST_SPLIT_BMSK                                             0x1
#define HWIO_BIMC_S_SYS0_SWAY_MODE_BURST_SPLIT_SHFT                                             0x0

#define HWIO_BIMC_S_SYS0_SWAY_READ_COMMAND_OVERRIDE_ADDR                                 (BIMC_S_SYS0_SWAY_REG_BASE      + 0x00000250)
#define HWIO_BIMC_S_SYS0_SWAY_READ_COMMAND_OVERRIDE_RMSK                                  0xf7f0bcb
#define HWIO_BIMC_S_SYS0_SWAY_READ_COMMAND_OVERRIDE_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_READ_COMMAND_OVERRIDE_ADDR, HWIO_BIMC_S_SYS0_SWAY_READ_COMMAND_OVERRIDE_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_READ_COMMAND_OVERRIDE_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_READ_COMMAND_OVERRIDE_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_READ_COMMAND_OVERRIDE_OUT(v)      \
        out_dword(HWIO_BIMC_S_SYS0_SWAY_READ_COMMAND_OVERRIDE_ADDR,v)
#define HWIO_BIMC_S_SYS0_SWAY_READ_COMMAND_OVERRIDE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_S_SYS0_SWAY_READ_COMMAND_OVERRIDE_ADDR,m,v,HWIO_BIMC_S_SYS0_SWAY_READ_COMMAND_OVERRIDE_IN)
#define HWIO_BIMC_S_SYS0_SWAY_READ_COMMAND_OVERRIDE_ASNOOP_BMSK                           0xf000000
#define HWIO_BIMC_S_SYS0_SWAY_READ_COMMAND_OVERRIDE_ASNOOP_SHFT                                0x18
#define HWIO_BIMC_S_SYS0_SWAY_READ_COMMAND_OVERRIDE_AMEMTYPE_BMSK                          0x7f0000
#define HWIO_BIMC_S_SYS0_SWAY_READ_COMMAND_OVERRIDE_AMEMTYPE_SHFT                              0x10
#define HWIO_BIMC_S_SYS0_SWAY_READ_COMMAND_OVERRIDE_APORTMREL_BMSK                            0x800
#define HWIO_BIMC_S_SYS0_SWAY_READ_COMMAND_OVERRIDE_APORTMREL_SHFT                              0xb
#define HWIO_BIMC_S_SYS0_SWAY_READ_COMMAND_OVERRIDE_ASHARED_BMSK                              0x200
#define HWIO_BIMC_S_SYS0_SWAY_READ_COMMAND_OVERRIDE_ASHARED_SHFT                                0x9
#define HWIO_BIMC_S_SYS0_SWAY_READ_COMMAND_OVERRIDE_AINNERSHARED_BMSK                         0x100
#define HWIO_BIMC_S_SYS0_SWAY_READ_COMMAND_OVERRIDE_AINNERSHARED_SHFT                           0x8
#define HWIO_BIMC_S_SYS0_SWAY_READ_COMMAND_OVERRIDE_OVERRIDE_ASNOOP_BMSK                       0x80
#define HWIO_BIMC_S_SYS0_SWAY_READ_COMMAND_OVERRIDE_OVERRIDE_ASNOOP_SHFT                        0x7
#define HWIO_BIMC_S_SYS0_SWAY_READ_COMMAND_OVERRIDE_OVERRIDE_AMEMTYPE_BMSK                     0x40
#define HWIO_BIMC_S_SYS0_SWAY_READ_COMMAND_OVERRIDE_OVERRIDE_AMEMTYPE_SHFT                      0x6
#define HWIO_BIMC_S_SYS0_SWAY_READ_COMMAND_OVERRIDE_OVERRIDE_APORTMREL_BMSK                     0x8
#define HWIO_BIMC_S_SYS0_SWAY_READ_COMMAND_OVERRIDE_OVERRIDE_APORTMREL_SHFT                     0x3
#define HWIO_BIMC_S_SYS0_SWAY_READ_COMMAND_OVERRIDE_OVERRIDE_ASHARED_BMSK                       0x2
#define HWIO_BIMC_S_SYS0_SWAY_READ_COMMAND_OVERRIDE_OVERRIDE_ASHARED_SHFT                       0x1
#define HWIO_BIMC_S_SYS0_SWAY_READ_COMMAND_OVERRIDE_OVERRIDE_AINNERSHARED_BMSK                  0x1
#define HWIO_BIMC_S_SYS0_SWAY_READ_COMMAND_OVERRIDE_OVERRIDE_AINNERSHARED_SHFT                  0x0

#define HWIO_BIMC_S_SYS0_SWAY_WRITE_COMMAND_OVERRIDE_ADDR                                (BIMC_S_SYS0_SWAY_REG_BASE      + 0x00000260)
#define HWIO_BIMC_S_SYS0_SWAY_WRITE_COMMAND_OVERRIDE_RMSK                                 0xf7f0fcf
#define HWIO_BIMC_S_SYS0_SWAY_WRITE_COMMAND_OVERRIDE_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_WRITE_COMMAND_OVERRIDE_ADDR, HWIO_BIMC_S_SYS0_SWAY_WRITE_COMMAND_OVERRIDE_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_WRITE_COMMAND_OVERRIDE_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_WRITE_COMMAND_OVERRIDE_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_WRITE_COMMAND_OVERRIDE_OUT(v)      \
        out_dword(HWIO_BIMC_S_SYS0_SWAY_WRITE_COMMAND_OVERRIDE_ADDR,v)
#define HWIO_BIMC_S_SYS0_SWAY_WRITE_COMMAND_OVERRIDE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_S_SYS0_SWAY_WRITE_COMMAND_OVERRIDE_ADDR,m,v,HWIO_BIMC_S_SYS0_SWAY_WRITE_COMMAND_OVERRIDE_IN)
#define HWIO_BIMC_S_SYS0_SWAY_WRITE_COMMAND_OVERRIDE_ASNOOP_BMSK                          0xf000000
#define HWIO_BIMC_S_SYS0_SWAY_WRITE_COMMAND_OVERRIDE_ASNOOP_SHFT                               0x18
#define HWIO_BIMC_S_SYS0_SWAY_WRITE_COMMAND_OVERRIDE_AMEMTYPE_BMSK                         0x7f0000
#define HWIO_BIMC_S_SYS0_SWAY_WRITE_COMMAND_OVERRIDE_AMEMTYPE_SHFT                             0x10
#define HWIO_BIMC_S_SYS0_SWAY_WRITE_COMMAND_OVERRIDE_APORTMREL_BMSK                           0x800
#define HWIO_BIMC_S_SYS0_SWAY_WRITE_COMMAND_OVERRIDE_APORTMREL_SHFT                             0xb
#define HWIO_BIMC_S_SYS0_SWAY_WRITE_COMMAND_OVERRIDE_AUNIQUE_BMSK                             0x400
#define HWIO_BIMC_S_SYS0_SWAY_WRITE_COMMAND_OVERRIDE_AUNIQUE_SHFT                               0xa
#define HWIO_BIMC_S_SYS0_SWAY_WRITE_COMMAND_OVERRIDE_ASHARED_BMSK                             0x200
#define HWIO_BIMC_S_SYS0_SWAY_WRITE_COMMAND_OVERRIDE_ASHARED_SHFT                               0x9
#define HWIO_BIMC_S_SYS0_SWAY_WRITE_COMMAND_OVERRIDE_AINNERSHARED_BMSK                        0x100
#define HWIO_BIMC_S_SYS0_SWAY_WRITE_COMMAND_OVERRIDE_AINNERSHARED_SHFT                          0x8
#define HWIO_BIMC_S_SYS0_SWAY_WRITE_COMMAND_OVERRIDE_OVERRIDE_ASNOOP_BMSK                      0x80
#define HWIO_BIMC_S_SYS0_SWAY_WRITE_COMMAND_OVERRIDE_OVERRIDE_ASNOOP_SHFT                       0x7
#define HWIO_BIMC_S_SYS0_SWAY_WRITE_COMMAND_OVERRIDE_OVERRIDE_AMEMTYPE_BMSK                    0x40
#define HWIO_BIMC_S_SYS0_SWAY_WRITE_COMMAND_OVERRIDE_OVERRIDE_AMEMTYPE_SHFT                     0x6
#define HWIO_BIMC_S_SYS0_SWAY_WRITE_COMMAND_OVERRIDE_OVERRIDE_APORTMREL_BMSK                    0x8
#define HWIO_BIMC_S_SYS0_SWAY_WRITE_COMMAND_OVERRIDE_OVERRIDE_APORTMREL_SHFT                    0x3
#define HWIO_BIMC_S_SYS0_SWAY_WRITE_COMMAND_OVERRIDE_OVERRIDE_AUNIQUE_BMSK                      0x4
#define HWIO_BIMC_S_SYS0_SWAY_WRITE_COMMAND_OVERRIDE_OVERRIDE_AUNIQUE_SHFT                      0x2
#define HWIO_BIMC_S_SYS0_SWAY_WRITE_COMMAND_OVERRIDE_OVERRIDE_ASHARED_BMSK                      0x2
#define HWIO_BIMC_S_SYS0_SWAY_WRITE_COMMAND_OVERRIDE_OVERRIDE_ASHARED_SHFT                      0x1
#define HWIO_BIMC_S_SYS0_SWAY_WRITE_COMMAND_OVERRIDE_OVERRIDE_AINNERSHARED_BMSK                 0x1
#define HWIO_BIMC_S_SYS0_SWAY_WRITE_COMMAND_OVERRIDE_OVERRIDE_AINNERSHARED_SHFT                 0x0

#define HWIO_BIMC_S_SYS0_SWAY_STATUS_0A_ADDR                                             (BIMC_S_SYS0_SWAY_REG_BASE      + 0x00000400)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_0A_RMSK                                               0xff00ff
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_0A_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_STATUS_0A_ADDR, HWIO_BIMC_S_SYS0_SWAY_STATUS_0A_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_0A_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_STATUS_0A_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_0A_WR_PENDING_PRE_BUF_BMSK                            0xff0000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_0A_WR_PENDING_PRE_BUF_SHFT                                0x10
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_0A_RD_PENDING_PRE_BUF_BMSK                                0xff
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_0A_RD_PENDING_PRE_BUF_SHFT                                 0x0

#define HWIO_BIMC_S_SYS0_SWAY_STATUS_0B_ADDR                                             (BIMC_S_SYS0_SWAY_REG_BASE      + 0x00000404)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_0B_RMSK                                               0xff00ff
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_0B_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_STATUS_0B_ADDR, HWIO_BIMC_S_SYS0_SWAY_STATUS_0B_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_0B_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_STATUS_0B_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_0B_WR_PENDING_POST_BUF_BMSK                           0xff0000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_0B_WR_PENDING_POST_BUF_SHFT                               0x10
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_0B_RD_PENDING_POST_BUF_BMSK                               0xff
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_0B_RD_PENDING_POST_BUF_SHFT                                0x0

#define HWIO_BIMC_S_SYS0_SWAY_STATUS_0C_ADDR                                             (BIMC_S_SYS0_SWAY_REG_BASE      + 0x00000408)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_0C_RMSK                                              0x3f03f0f
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_0C_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_STATUS_0C_ADDR, HWIO_BIMC_S_SYS0_SWAY_STATUS_0C_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_0C_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_STATUS_0C_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_0C_RDQ_FULL_BMSK                                     0x3f00000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_0C_RDQ_FULL_SHFT                                          0x14
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_0C_WRQ_FULL_BMSK                                        0x3f00
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_0C_WRQ_FULL_SHFT                                           0x8
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_0C_CMDQ_FULL_BMSK                                          0xf
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_0C_CMDQ_FULL_SHFT                                          0x0

#define HWIO_BIMC_S_SYS0_SWAY_STATUS_0D_ADDR                                             (BIMC_S_SYS0_SWAY_REG_BASE      + 0x0000040c)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_0D_RMSK                                              0x3f03f0f
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_0D_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_STATUS_0D_ADDR, HWIO_BIMC_S_SYS0_SWAY_STATUS_0D_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_0D_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_STATUS_0D_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_0D_RDQ_ALMOST_FULL_BMSK                              0x3f00000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_0D_RDQ_ALMOST_FULL_SHFT                                   0x14
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_0D_WRQ_ALMOST_FULL_BMSK                                 0x3f00
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_0D_WRQ_ALMOST_FULL_SHFT                                    0x8
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_0D_CMDQ_ALMOST_FULL_BMSK                                   0xf
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_0D_CMDQ_ALMOST_FULL_SHFT                                   0x0

#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_ADDR                                             (BIMC_S_SYS0_SWAY_REG_BASE      + 0x00000410)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_RMSK                                             0xff333333
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_ADDR, HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_RCB0_DATA_RD_FULL_BMSK                           0x80000000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_RCB0_DATA_RD_FULL_SHFT                                 0x1f
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_RCB0_DATA_RD_EMPTY_BMSK                          0x40000000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_RCB0_DATA_RD_EMPTY_SHFT                                0x1e
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_RCB0_CTRL_RD_FULL_BMSK                           0x20000000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_RCB0_CTRL_RD_FULL_SHFT                                 0x1d
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_RCB0_CTRL_RD_EMPTY_BMSK                          0x10000000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_RCB0_CTRL_RD_EMPTY_SHFT                                0x1c
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_RCB0_DATA_WR_FULL_BMSK                            0x8000000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_RCB0_DATA_WR_FULL_SHFT                                 0x1b
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_RCB0_DATA_WR_EMPTY_BMSK                           0x4000000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_RCB0_DATA_WR_EMPTY_SHFT                                0x1a
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_RCB0_CTRL_WR_FULL_BMSK                            0x2000000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_RCB0_CTRL_WR_FULL_SHFT                                 0x19
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_RCB0_CTRL_WR_EMPTY_BMSK                           0x1000000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_RCB0_CTRL_WR_EMPTY_SHFT                                0x18
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_BCB_RD_FULL_BMSK                                   0x200000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_BCB_RD_FULL_SHFT                                       0x15
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_BCB_RD_EMPTY_BMSK                                  0x100000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_BCB_RD_EMPTY_SHFT                                      0x14
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_BCB_WR_FULL_BMSK                                    0x20000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_BCB_WR_FULL_SHFT                                       0x11
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_BCB_WR_EMPTY_BMSK                                   0x10000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_BCB_WR_EMPTY_SHFT                                      0x10
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_WCB_RD_FULL_BMSK                                     0x2000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_WCB_RD_FULL_SHFT                                        0xd
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_WCB_RD_EMPTY_BMSK                                    0x1000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_WCB_RD_EMPTY_SHFT                                       0xc
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_WCB_WR_FULL_BMSK                                      0x200
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_WCB_WR_FULL_SHFT                                        0x9
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_WCB_WR_EMPTY_BMSK                                     0x100
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_WCB_WR_EMPTY_SHFT                                       0x8
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_ACB_RD_FULL_BMSK                                       0x20
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_ACB_RD_FULL_SHFT                                        0x5
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_ACB_RD_EMPTY_BMSK                                      0x10
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_ACB_RD_EMPTY_SHFT                                       0x4
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_ACB_WR_FULL_BMSK                                        0x2
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_ACB_WR_FULL_SHFT                                        0x1
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_ACB_WR_EMPTY_BMSK                                       0x1
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1A_ACB_WR_EMPTY_SHFT                                       0x0

#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_ADDR                                             (BIMC_S_SYS0_SWAY_REG_BASE      + 0x00000414)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_RMSK                                             0x33333333
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_ADDR, HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_WIB_RD_FULL_BMSK                                 0x20000000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_WIB_RD_FULL_SHFT                                       0x1d
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_WIB_RD_EMPTY_BMSK                                0x10000000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_WIB_RD_EMPTY_SHFT                                      0x1c
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_WIB_WR_FULL_BMSK                                  0x2000000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_WIB_WR_FULL_SHFT                                       0x19
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_WIB_WR_EMPTY_BMSK                                 0x1000000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_WIB_WR_EMPTY_SHFT                                      0x18
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_RGB0_RD_FULL_BMSK                                  0x200000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_RGB0_RD_FULL_SHFT                                      0x15
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_RGB0_RD_EMPTY_BMSK                                 0x100000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_RGB0_RD_EMPTY_SHFT                                     0x14
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_RGB0_WR_FULL_BMSK                                   0x20000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_RGB0_WR_FULL_SHFT                                      0x11
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_RGB0_WR_EMPTY_BMSK                                  0x10000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_RGB0_WR_EMPTY_SHFT                                     0x10
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_W2AB_RD_FULL_BMSK                                    0x2000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_W2AB_RD_FULL_SHFT                                       0xd
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_W2AB_RD_EMPTY_BMSK                                   0x1000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_W2AB_RD_EMPTY_SHFT                                      0xc
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_W2AB_WR_FULL_BMSK                                     0x200
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_W2AB_WR_FULL_SHFT                                       0x9
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_W2AB_WR_EMPTY_BMSK                                    0x100
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_W2AB_WR_EMPTY_SHFT                                      0x8
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_A2WB_RD_FULL_BMSK                                      0x20
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_A2WB_RD_FULL_SHFT                                       0x5
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_A2WB_RD_EMPTY_BMSK                                     0x10
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_A2WB_RD_EMPTY_SHFT                                      0x4
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_A2WB_WR_FULL_BMSK                                       0x2
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_A2WB_WR_FULL_SHFT                                       0x1
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_A2WB_WR_EMPTY_BMSK                                      0x1
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1B_A2WB_WR_EMPTY_SHFT                                      0x0

#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1C_ADDR                                             (BIMC_S_SYS0_SWAY_REG_BASE      + 0x00000418)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1C_RMSK                                                 0x33ff
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1C_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_STATUS_1C_ADDR, HWIO_BIMC_S_SYS0_SWAY_STATUS_1C_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1C_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_STATUS_1C_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1C_RGB1_RD_FULL_BMSK                                    0x2000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1C_RGB1_RD_FULL_SHFT                                       0xd
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1C_RGB1_RD_EMPTY_BMSK                                   0x1000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1C_RGB1_RD_EMPTY_SHFT                                      0xc
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1C_RGB1_WR_FULL_BMSK                                     0x200
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1C_RGB1_WR_FULL_SHFT                                       0x9
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1C_RGB1_WR_EMPTY_BMSK                                    0x100
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1C_RGB1_WR_EMPTY_SHFT                                      0x8
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1C_RCB1_DATA_RD_FULL_BMSK                                 0x80
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1C_RCB1_DATA_RD_FULL_SHFT                                  0x7
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1C_RCB1_DATA_RD_EMPTY_BMSK                                0x40
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1C_RCB1_DATA_RD_EMPTY_SHFT                                 0x6
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1C_RCB1_CTRL_RD_FULL_BMSK                                 0x20
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1C_RCB1_CTRL_RD_FULL_SHFT                                  0x5
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1C_RCB1_CTRL_RD_EMPTY_BMSK                                0x10
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1C_RCB1_CTRL_RD_EMPTY_SHFT                                 0x4
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1C_RCB1_DATA_WR_FULL_BMSK                                  0x8
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1C_RCB1_DATA_WR_FULL_SHFT                                  0x3
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1C_RCB1_DATA_WR_EMPTY_BMSK                                 0x4
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1C_RCB1_DATA_WR_EMPTY_SHFT                                 0x2
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1C_RCB1_CTRL_WR_FULL_BMSK                                  0x2
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1C_RCB1_CTRL_WR_FULL_SHFT                                  0x1
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1C_RCB1_CTRL_WR_EMPTY_BMSK                                 0x1
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_1C_RCB1_CTRL_WR_EMPTY_SHFT                                 0x0

#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2A_ADDR                                             (BIMC_S_SYS0_SWAY_REG_BASE      + 0x00000420)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2A_RMSK                                             0xffffffff
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2A_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_STATUS_2A_ADDR, HWIO_BIMC_S_SYS0_SWAY_STATUS_2A_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2A_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_STATUS_2A_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2A_RD_PENDING_PER_MSTR_3_BMSK                       0xff000000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2A_RD_PENDING_PER_MSTR_3_SHFT                             0x18
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2A_RD_PENDING_PER_MSTR_2_BMSK                         0xff0000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2A_RD_PENDING_PER_MSTR_2_SHFT                             0x10
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2A_RD_PENDING_PER_MSTR_1_BMSK                           0xff00
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2A_RD_PENDING_PER_MSTR_1_SHFT                              0x8
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2A_RD_PENDING_PER_MSTR_0_BMSK                             0xff
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2A_RD_PENDING_PER_MSTR_0_SHFT                              0x0

#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2B_ADDR                                             (BIMC_S_SYS0_SWAY_REG_BASE      + 0x00000424)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2B_RMSK                                             0xffffffff
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2B_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_STATUS_2B_ADDR, HWIO_BIMC_S_SYS0_SWAY_STATUS_2B_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2B_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_STATUS_2B_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2B_RD_PENDING_PER_MSTR_7_BMSK                       0xff000000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2B_RD_PENDING_PER_MSTR_7_SHFT                             0x18
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2B_RD_PENDING_PER_MSTR_6_BMSK                         0xff0000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2B_RD_PENDING_PER_MSTR_6_SHFT                             0x10
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2B_RD_PENDING_PER_MSTR_5_BMSK                           0xff00
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2B_RD_PENDING_PER_MSTR_5_SHFT                              0x8
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2B_RD_PENDING_PER_MSTR_4_BMSK                             0xff
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2B_RD_PENDING_PER_MSTR_4_SHFT                              0x0

#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2C_ADDR                                             (BIMC_S_SYS0_SWAY_REG_BASE      + 0x00000428)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2C_RMSK                                             0xffffffff
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2C_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_STATUS_2C_ADDR, HWIO_BIMC_S_SYS0_SWAY_STATUS_2C_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2C_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_STATUS_2C_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2C_RD_PENDING_PER_MSTR_11_BMSK                      0xff000000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2C_RD_PENDING_PER_MSTR_11_SHFT                            0x18
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2C_RD_PENDING_PER_MSTR_10_BMSK                        0xff0000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2C_RD_PENDING_PER_MSTR_10_SHFT                            0x10
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2C_RD_PENDING_PER_MSTR_9_BMSK                           0xff00
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2C_RD_PENDING_PER_MSTR_9_SHFT                              0x8
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2C_RD_PENDING_PER_MSTR_8_BMSK                             0xff
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2C_RD_PENDING_PER_MSTR_8_SHFT                              0x0

#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2D_ADDR                                             (BIMC_S_SYS0_SWAY_REG_BASE      + 0x0000042c)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2D_RMSK                                             0xffffffff
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2D_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_STATUS_2D_ADDR, HWIO_BIMC_S_SYS0_SWAY_STATUS_2D_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2D_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_STATUS_2D_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2D_RD_PENDING_PER_MSTR_15_BMSK                      0xff000000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2D_RD_PENDING_PER_MSTR_15_SHFT                            0x18
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2D_RD_PENDING_PER_MSTR_14_BMSK                        0xff0000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2D_RD_PENDING_PER_MSTR_14_SHFT                            0x10
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2D_RD_PENDING_PER_MSTR_13_BMSK                          0xff00
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2D_RD_PENDING_PER_MSTR_13_SHFT                             0x8
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2D_RD_PENDING_PER_MSTR_12_BMSK                            0xff
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_2D_RD_PENDING_PER_MSTR_12_SHFT                             0x0

#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3A_ADDR                                             (BIMC_S_SYS0_SWAY_REG_BASE      + 0x00000430)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3A_RMSK                                             0xffffffff
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3A_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_STATUS_3A_ADDR, HWIO_BIMC_S_SYS0_SWAY_STATUS_3A_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3A_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_STATUS_3A_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3A_WR_PENDING_PER_MSTR_3_BMSK                       0xff000000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3A_WR_PENDING_PER_MSTR_3_SHFT                             0x18
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3A_WR_PENDING_PER_MSTR_2_BMSK                         0xff0000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3A_WR_PENDING_PER_MSTR_2_SHFT                             0x10
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3A_WR_PENDING_PER_MSTR_1_BMSK                           0xff00
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3A_WR_PENDING_PER_MSTR_1_SHFT                              0x8
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3A_WR_PENDING_PER_MSTR_0_BMSK                             0xff
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3A_WR_PENDING_PER_MSTR_0_SHFT                              0x0

#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3B_ADDR                                             (BIMC_S_SYS0_SWAY_REG_BASE      + 0x00000434)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3B_RMSK                                             0xffffffff
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3B_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_STATUS_3B_ADDR, HWIO_BIMC_S_SYS0_SWAY_STATUS_3B_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3B_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_STATUS_3B_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3B_WR_PENDING_PER_MSTR_7_BMSK                       0xff000000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3B_WR_PENDING_PER_MSTR_7_SHFT                             0x18
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3B_WR_PENDING_PER_MSTR_6_BMSK                         0xff0000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3B_WR_PENDING_PER_MSTR_6_SHFT                             0x10
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3B_WR_PENDING_PER_MSTR_5_BMSK                           0xff00
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3B_WR_PENDING_PER_MSTR_5_SHFT                              0x8
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3B_WR_PENDING_PER_MSTR_4_BMSK                             0xff
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3B_WR_PENDING_PER_MSTR_4_SHFT                              0x0

#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3C_ADDR                                             (BIMC_S_SYS0_SWAY_REG_BASE      + 0x00000438)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3C_RMSK                                             0xffffffff
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3C_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_STATUS_3C_ADDR, HWIO_BIMC_S_SYS0_SWAY_STATUS_3C_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3C_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_STATUS_3C_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3C_WR_PENDING_PER_MSTR_11_BMSK                      0xff000000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3C_WR_PENDING_PER_MSTR_11_SHFT                            0x18
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3C_WR_PENDING_PER_MSTR_10_BMSK                        0xff0000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3C_WR_PENDING_PER_MSTR_10_SHFT                            0x10
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3C_WR_PENDING_PER_MSTR_9_BMSK                           0xff00
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3C_WR_PENDING_PER_MSTR_9_SHFT                              0x8
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3C_WR_PENDING_PER_MSTR_8_BMSK                             0xff
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3C_WR_PENDING_PER_MSTR_8_SHFT                              0x0

#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3D_ADDR                                             (BIMC_S_SYS0_SWAY_REG_BASE      + 0x0000043c)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3D_RMSK                                             0xffffffff
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3D_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_STATUS_3D_ADDR, HWIO_BIMC_S_SYS0_SWAY_STATUS_3D_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3D_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_STATUS_3D_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3D_WR_PENDING_PER_MSTR_15_BMSK                      0xff000000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3D_WR_PENDING_PER_MSTR_15_SHFT                            0x18
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3D_WR_PENDING_PER_MSTR_14_BMSK                        0xff0000
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3D_WR_PENDING_PER_MSTR_14_SHFT                            0x10
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3D_WR_PENDING_PER_MSTR_13_BMSK                          0xff00
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3D_WR_PENDING_PER_MSTR_13_SHFT                             0x8
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3D_WR_PENDING_PER_MSTR_12_BMSK                            0xff
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_3D_WR_PENDING_PER_MSTR_12_SHFT                             0x0

#define HWIO_BIMC_S_SYS0_SWAY_STATUS_4A_ADDR                                             (BIMC_S_SYS0_SWAY_REG_BASE      + 0x00000440)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_4A_RMSK                                                   0xff
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_4A_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_STATUS_4A_ADDR, HWIO_BIMC_S_SYS0_SWAY_STATUS_4A_RMSK)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_4A_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS0_SWAY_STATUS_4A_ADDR, m)
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_4A_SWAY_VALID_READY_BMSK                                  0xff
#define HWIO_BIMC_S_SYS0_SWAY_STATUS_4A_SWAY_VALID_READY_SHFT                                   0x0

/*----------------------------------------------------------------------------
 * MODULE: BIMC_S_SYS1_SWAY
 *--------------------------------------------------------------------------*/

#define BIMC_S_SYS1_SWAY_REG_BASE                                                        (DDR_SS_BASE      + 0x0005b000)

#define HWIO_BIMC_S_SYS1_SWAY_COMPONENT_INFO_ADDR                                        (BIMC_S_SYS1_SWAY_REG_BASE      + 0x00000000)
#define HWIO_BIMC_S_SYS1_SWAY_COMPONENT_INFO_RMSK                                          0xffffff
#define HWIO_BIMC_S_SYS1_SWAY_COMPONENT_INFO_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_COMPONENT_INFO_ADDR, HWIO_BIMC_S_SYS1_SWAY_COMPONENT_INFO_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_COMPONENT_INFO_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_COMPONENT_INFO_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_COMPONENT_INFO_INSTANCE_BMSK                                 0xff0000
#define HWIO_BIMC_S_SYS1_SWAY_COMPONENT_INFO_INSTANCE_SHFT                                     0x10
#define HWIO_BIMC_S_SYS1_SWAY_COMPONENT_INFO_SUB_TYPE_BMSK                                   0xff00
#define HWIO_BIMC_S_SYS1_SWAY_COMPONENT_INFO_SUB_TYPE_SHFT                                      0x8
#define HWIO_BIMC_S_SYS1_SWAY_COMPONENT_INFO_TYPE_BMSK                                         0xff
#define HWIO_BIMC_S_SYS1_SWAY_COMPONENT_INFO_TYPE_SHFT                                          0x0

#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_0_ADDR                                  (BIMC_S_SYS1_SWAY_REG_BASE      + 0x00000020)
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_0_RMSK                                  0xff0000ff
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_0_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_0_ADDR, HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_0_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_0_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_0_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_0_SYNC_MODE_BMSK                        0xff000000
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_0_SYNC_MODE_SHFT                              0x18
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_0_FUNCTIONALITY_BMSK                          0xff
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_0_FUNCTIONALITY_SHFT                           0x0

#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_1_ADDR                                  (BIMC_S_SYS1_SWAY_REG_BASE      + 0x00000030)
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_1_RMSK                                  0xffffffff
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_1_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_1_ADDR, HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_1_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_1_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_1_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_1_MPORT_CONNECTIVITY_BMSK               0xffffffff
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_1_MPORT_CONNECTIVITY_SHFT                      0x0

#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_2_ADDR                                  (BIMC_S_SYS1_SWAY_REG_BASE      + 0x00000040)
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_2_RMSK                                  0xffffffff
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_2_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_2_ADDR, HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_2_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_2_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_2_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_2_S_DATA_WIDTH_BMSK                     0xffff0000
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_2_S_DATA_WIDTH_SHFT                           0x10
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_2_S_TID_WIDTH_BMSK                          0xff00
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_2_S_TID_WIDTH_SHFT                             0x8
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_2_S_MID_WIDTH_BMSK                            0xff
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_2_S_MID_WIDTH_SHFT                             0x0

#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_3_ADDR                                  (BIMC_S_SYS1_SWAY_REG_BASE      + 0x00000050)
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_3_RMSK                                  0xffffffff
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_3_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_3_ADDR, HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_3_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_3_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_3_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_3_RCH0_DEPTH_BMSK                       0xff000000
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_3_RCH0_DEPTH_SHFT                             0x18
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_3_BCH_DEPTH_BMSK                          0xff0000
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_3_BCH_DEPTH_SHFT                              0x10
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_3_WCH_DEPTH_BMSK                            0xff00
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_3_WCH_DEPTH_SHFT                               0x8
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_3_ACH_DEPTH_BMSK                              0xff
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_3_ACH_DEPTH_SHFT                               0x0

#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_4_ADDR                                  (BIMC_S_SYS1_SWAY_REG_BASE      + 0x00000060)
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_4_RMSK                                  0x800000ff
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_4_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_4_ADDR, HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_4_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_4_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_4_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_4_DUAL_RCH_EN_BMSK                      0x80000000
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_4_DUAL_RCH_EN_SHFT                            0x1f
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_4_RCH1_DEPTH_BMSK                             0xff
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_4_RCH1_DEPTH_SHFT                              0x0

#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_5_ADDR                                  (BIMC_S_SYS1_SWAY_REG_BASE      + 0x00000070)
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_5_RMSK                                  0x80000000
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_5_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_5_ADDR, HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_5_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_5_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_5_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_5_QOS_EN_BMSK                           0x80000000
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_5_QOS_EN_SHFT                                 0x1f

#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_6A_ADDR                                 (BIMC_S_SYS1_SWAY_REG_BASE      + 0x00000080)
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_6A_RMSK                                 0xffffffff
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_6A_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_6A_ADDR, HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_6A_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_6A_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_6A_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_6A_ACH_PIPELINE_STAGES_BMSK             0xffffffff
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_6A_ACH_PIPELINE_STAGES_SHFT                    0x0

#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_6B_ADDR                                 (BIMC_S_SYS1_SWAY_REG_BASE      + 0x00000084)
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_6B_RMSK                                 0xffffffff
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_6B_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_6B_ADDR, HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_6B_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_6B_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_6B_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_6B_WCH_PIPELINE_STAGES_BMSK             0xffffffff
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_6B_WCH_PIPELINE_STAGES_SHFT                    0x0

#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_6C_ADDR                                 (BIMC_S_SYS1_SWAY_REG_BASE      + 0x00000088)
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_6C_RMSK                                 0xffffffff
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_6C_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_6C_ADDR, HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_6C_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_6C_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_6C_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_6C_BCH_PIPELINE_STAGES_BMSK             0xffffffff
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_6C_BCH_PIPELINE_STAGES_SHFT                    0x0

#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_6D_ADDR                                 (BIMC_S_SYS1_SWAY_REG_BASE      + 0x0000008c)
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_6D_RMSK                                 0xffffffff
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_6D_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_6D_ADDR, HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_6D_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_6D_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_6D_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_6D_RCH_PIPELINE_STAGES_BMSK             0xffffffff
#define HWIO_BIMC_S_SYS1_SWAY_CONFIGURATION_INFO_6D_RCH_PIPELINE_STAGES_SHFT                    0x0

#define HWIO_BIMC_S_SYS1_SWAY_INTERRUPT_STATUS_ADDR                                      (BIMC_S_SYS1_SWAY_REG_BASE      + 0x00000100)
#define HWIO_BIMC_S_SYS1_SWAY_INTERRUPT_STATUS_RMSK                                             0x3
#define HWIO_BIMC_S_SYS1_SWAY_INTERRUPT_STATUS_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_INTERRUPT_STATUS_ADDR, HWIO_BIMC_S_SYS1_SWAY_INTERRUPT_STATUS_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_INTERRUPT_STATUS_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_INTERRUPT_STATUS_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_INTERRUPT_STATUS_RFU_BMSK                                         0x3
#define HWIO_BIMC_S_SYS1_SWAY_INTERRUPT_STATUS_RFU_SHFT                                         0x0

#define HWIO_BIMC_S_SYS1_SWAY_INTERRUPT_CLEAR_ADDR                                       (BIMC_S_SYS1_SWAY_REG_BASE      + 0x00000108)
#define HWIO_BIMC_S_SYS1_SWAY_INTERRUPT_CLEAR_RMSK                                              0x3
#define HWIO_BIMC_S_SYS1_SWAY_INTERRUPT_CLEAR_OUT(v)      \
        out_dword(HWIO_BIMC_S_SYS1_SWAY_INTERRUPT_CLEAR_ADDR,v)
#define HWIO_BIMC_S_SYS1_SWAY_INTERRUPT_CLEAR_RFU_BMSK                                          0x3
#define HWIO_BIMC_S_SYS1_SWAY_INTERRUPT_CLEAR_RFU_SHFT                                          0x0

#define HWIO_BIMC_S_SYS1_SWAY_INTERRUPT_ENABLE_ADDR                                      (BIMC_S_SYS1_SWAY_REG_BASE      + 0x0000010c)
#define HWIO_BIMC_S_SYS1_SWAY_INTERRUPT_ENABLE_RMSK                                             0x3
#define HWIO_BIMC_S_SYS1_SWAY_INTERRUPT_ENABLE_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_INTERRUPT_ENABLE_ADDR, HWIO_BIMC_S_SYS1_SWAY_INTERRUPT_ENABLE_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_INTERRUPT_ENABLE_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_INTERRUPT_ENABLE_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_INTERRUPT_ENABLE_OUT(v)      \
        out_dword(HWIO_BIMC_S_SYS1_SWAY_INTERRUPT_ENABLE_ADDR,v)
#define HWIO_BIMC_S_SYS1_SWAY_INTERRUPT_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_S_SYS1_SWAY_INTERRUPT_ENABLE_ADDR,m,v,HWIO_BIMC_S_SYS1_SWAY_INTERRUPT_ENABLE_IN)
#define HWIO_BIMC_S_SYS1_SWAY_INTERRUPT_ENABLE_RFU_BMSK                                         0x3
#define HWIO_BIMC_S_SYS1_SWAY_INTERRUPT_ENABLE_RFU_SHFT                                         0x0

#define HWIO_BIMC_S_SYS1_SWAY_CLOCK_CTRL_ADDR                                            (BIMC_S_SYS1_SWAY_REG_BASE      + 0x00000200)
#define HWIO_BIMC_S_SYS1_SWAY_CLOCK_CTRL_RMSK                                            0xff030003
#define HWIO_BIMC_S_SYS1_SWAY_CLOCK_CTRL_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_CLOCK_CTRL_ADDR, HWIO_BIMC_S_SYS1_SWAY_CLOCK_CTRL_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_CLOCK_CTRL_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_CLOCK_CTRL_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_CLOCK_CTRL_OUT(v)      \
        out_dword(HWIO_BIMC_S_SYS1_SWAY_CLOCK_CTRL_ADDR,v)
#define HWIO_BIMC_S_SYS1_SWAY_CLOCK_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_S_SYS1_SWAY_CLOCK_CTRL_ADDR,m,v,HWIO_BIMC_S_SYS1_SWAY_CLOCK_CTRL_IN)
#define HWIO_BIMC_S_SYS1_SWAY_CLOCK_CTRL_IDLE_HYSTERESIS_BMSK                            0xff000000
#define HWIO_BIMC_S_SYS1_SWAY_CLOCK_CTRL_IDLE_HYSTERESIS_SHFT                                  0x18
#define HWIO_BIMC_S_SYS1_SWAY_CLOCK_CTRL_IDLE_CLOCK_ON_REQ_EN_BMSK                          0x20000
#define HWIO_BIMC_S_SYS1_SWAY_CLOCK_CTRL_IDLE_CLOCK_ON_REQ_EN_SHFT                             0x11
#define HWIO_BIMC_S_SYS1_SWAY_CLOCK_CTRL_IDLE_GATING_EN_BMSK                                0x10000
#define HWIO_BIMC_S_SYS1_SWAY_CLOCK_CTRL_IDLE_GATING_EN_SHFT                                   0x10
#define HWIO_BIMC_S_SYS1_SWAY_CLOCK_CTRL_SLAVE_CLOCK_GATING_EN_BMSK                             0x2
#define HWIO_BIMC_S_SYS1_SWAY_CLOCK_CTRL_SLAVE_CLOCK_GATING_EN_SHFT                             0x1
#define HWIO_BIMC_S_SYS1_SWAY_CLOCK_CTRL_CORE_CLOCK_GATING_EN_BMSK                              0x1
#define HWIO_BIMC_S_SYS1_SWAY_CLOCK_CTRL_CORE_CLOCK_GATING_EN_SHFT                              0x0

#define HWIO_BIMC_S_SYS1_SWAY_CDC_CTRL_ADDR                                              (BIMC_S_SYS1_SWAY_REG_BASE      + 0x00000208)
#define HWIO_BIMC_S_SYS1_SWAY_CDC_CTRL_RMSK                                                     0x3
#define HWIO_BIMC_S_SYS1_SWAY_CDC_CTRL_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_CDC_CTRL_ADDR, HWIO_BIMC_S_SYS1_SWAY_CDC_CTRL_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_CDC_CTRL_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_CDC_CTRL_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_CDC_CTRL_OUT(v)      \
        out_dword(HWIO_BIMC_S_SYS1_SWAY_CDC_CTRL_ADDR,v)
#define HWIO_BIMC_S_SYS1_SWAY_CDC_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_S_SYS1_SWAY_CDC_CTRL_ADDR,m,v,HWIO_BIMC_S_SYS1_SWAY_CDC_CTRL_IN)
#define HWIO_BIMC_S_SYS1_SWAY_CDC_CTRL_SLAVE_CLOCK_DEMETA_SEL_BMSK                              0x2
#define HWIO_BIMC_S_SYS1_SWAY_CDC_CTRL_SLAVE_CLOCK_DEMETA_SEL_SHFT                              0x1
#define HWIO_BIMC_S_SYS1_SWAY_CDC_CTRL_CORE_CLOCK_DEMETA_SEL_BMSK                               0x1
#define HWIO_BIMC_S_SYS1_SWAY_CDC_CTRL_CORE_CLOCK_DEMETA_SEL_SHFT                               0x0

#define HWIO_BIMC_S_SYS1_SWAY_RCH_SELECT_ADDR                                            (BIMC_S_SYS1_SWAY_REG_BASE      + 0x00000210)
#define HWIO_BIMC_S_SYS1_SWAY_RCH_SELECT_RMSK                                                  0x3f
#define HWIO_BIMC_S_SYS1_SWAY_RCH_SELECT_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_RCH_SELECT_ADDR, HWIO_BIMC_S_SYS1_SWAY_RCH_SELECT_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_RCH_SELECT_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_RCH_SELECT_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_RCH_SELECT_UNUSED_BMSK                                           0x3f
#define HWIO_BIMC_S_SYS1_SWAY_RCH_SELECT_UNUSED_SHFT                                            0x0

#define HWIO_BIMC_S_SYS1_SWAY_MAX_OUTSTANDING_REQUESTS_ADDR                              (BIMC_S_SYS1_SWAY_REG_BASE      + 0x00000220)
#define HWIO_BIMC_S_SYS1_SWAY_MAX_OUTSTANDING_REQUESTS_RMSK                                  0xffff
#define HWIO_BIMC_S_SYS1_SWAY_MAX_OUTSTANDING_REQUESTS_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_MAX_OUTSTANDING_REQUESTS_ADDR, HWIO_BIMC_S_SYS1_SWAY_MAX_OUTSTANDING_REQUESTS_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_MAX_OUTSTANDING_REQUESTS_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_MAX_OUTSTANDING_REQUESTS_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_MAX_OUTSTANDING_REQUESTS_OUT(v)      \
        out_dword(HWIO_BIMC_S_SYS1_SWAY_MAX_OUTSTANDING_REQUESTS_ADDR,v)
#define HWIO_BIMC_S_SYS1_SWAY_MAX_OUTSTANDING_REQUESTS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_S_SYS1_SWAY_MAX_OUTSTANDING_REQUESTS_ADDR,m,v,HWIO_BIMC_S_SYS1_SWAY_MAX_OUTSTANDING_REQUESTS_IN)
#define HWIO_BIMC_S_SYS1_SWAY_MAX_OUTSTANDING_REQUESTS_WRITE_BMSK                            0xff00
#define HWIO_BIMC_S_SYS1_SWAY_MAX_OUTSTANDING_REQUESTS_WRITE_SHFT                               0x8
#define HWIO_BIMC_S_SYS1_SWAY_MAX_OUTSTANDING_REQUESTS_READ_BMSK                               0xff
#define HWIO_BIMC_S_SYS1_SWAY_MAX_OUTSTANDING_REQUESTS_READ_SHFT                                0x0

#define HWIO_BIMC_S_SYS1_SWAY_GATHERING_ADDR                                             (BIMC_S_SYS1_SWAY_REG_BASE      + 0x00000230)
#define HWIO_BIMC_S_SYS1_SWAY_GATHERING_RMSK                                                    0xf
#define HWIO_BIMC_S_SYS1_SWAY_GATHERING_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_GATHERING_ADDR, HWIO_BIMC_S_SYS1_SWAY_GATHERING_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_GATHERING_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_GATHERING_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_GATHERING_OUT(v)      \
        out_dword(HWIO_BIMC_S_SYS1_SWAY_GATHERING_ADDR,v)
#define HWIO_BIMC_S_SYS1_SWAY_GATHERING_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_S_SYS1_SWAY_GATHERING_ADDR,m,v,HWIO_BIMC_S_SYS1_SWAY_GATHERING_IN)
#define HWIO_BIMC_S_SYS1_SWAY_GATHERING_RD_GATHER_BEATS_BMSK                                    0xf
#define HWIO_BIMC_S_SYS1_SWAY_GATHERING_RD_GATHER_BEATS_SHFT                                    0x0

#define HWIO_BIMC_S_SYS1_SWAY_MODE_ADDR                                                  (BIMC_S_SYS1_SWAY_REG_BASE      + 0x00000240)
#define HWIO_BIMC_S_SYS1_SWAY_MODE_RMSK                                                  0x8000007f
#define HWIO_BIMC_S_SYS1_SWAY_MODE_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_MODE_ADDR, HWIO_BIMC_S_SYS1_SWAY_MODE_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_MODE_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_MODE_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_MODE_OUT(v)      \
        out_dword(HWIO_BIMC_S_SYS1_SWAY_MODE_ADDR,v)
#define HWIO_BIMC_S_SYS1_SWAY_MODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_S_SYS1_SWAY_MODE_ADDR,m,v,HWIO_BIMC_S_SYS1_SWAY_MODE_IN)
#define HWIO_BIMC_S_SYS1_SWAY_MODE_RFU_1_BMSK                                            0x80000000
#define HWIO_BIMC_S_SYS1_SWAY_MODE_RFU_1_SHFT                                                  0x1f
#define HWIO_BIMC_S_SYS1_SWAY_MODE_RESTRICT_ONE_PER_MASTER_BMSK                                0x40
#define HWIO_BIMC_S_SYS1_SWAY_MODE_RESTRICT_ONE_PER_MASTER_SHFT                                 0x6
#define HWIO_BIMC_S_SYS1_SWAY_MODE_CONVERT_16BYTE_EXCL_BMSK                                    0x20
#define HWIO_BIMC_S_SYS1_SWAY_MODE_CONVERT_16BYTE_EXCL_SHFT                                     0x5
#define HWIO_BIMC_S_SYS1_SWAY_MODE_CONVERT_ALL_EXCL_BMSK                                       0x10
#define HWIO_BIMC_S_SYS1_SWAY_MODE_CONVERT_ALL_EXCL_SHFT                                        0x4
#define HWIO_BIMC_S_SYS1_SWAY_MODE_RFU_0_BMSK                                                   0xe
#define HWIO_BIMC_S_SYS1_SWAY_MODE_RFU_0_SHFT                                                   0x1
#define HWIO_BIMC_S_SYS1_SWAY_MODE_BURST_SPLIT_BMSK                                             0x1
#define HWIO_BIMC_S_SYS1_SWAY_MODE_BURST_SPLIT_SHFT                                             0x0

#define HWIO_BIMC_S_SYS1_SWAY_READ_COMMAND_OVERRIDE_ADDR                                 (BIMC_S_SYS1_SWAY_REG_BASE      + 0x00000250)
#define HWIO_BIMC_S_SYS1_SWAY_READ_COMMAND_OVERRIDE_RMSK                                  0xf7f0bcb
#define HWIO_BIMC_S_SYS1_SWAY_READ_COMMAND_OVERRIDE_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_READ_COMMAND_OVERRIDE_ADDR, HWIO_BIMC_S_SYS1_SWAY_READ_COMMAND_OVERRIDE_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_READ_COMMAND_OVERRIDE_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_READ_COMMAND_OVERRIDE_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_READ_COMMAND_OVERRIDE_OUT(v)      \
        out_dword(HWIO_BIMC_S_SYS1_SWAY_READ_COMMAND_OVERRIDE_ADDR,v)
#define HWIO_BIMC_S_SYS1_SWAY_READ_COMMAND_OVERRIDE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_S_SYS1_SWAY_READ_COMMAND_OVERRIDE_ADDR,m,v,HWIO_BIMC_S_SYS1_SWAY_READ_COMMAND_OVERRIDE_IN)
#define HWIO_BIMC_S_SYS1_SWAY_READ_COMMAND_OVERRIDE_ASNOOP_BMSK                           0xf000000
#define HWIO_BIMC_S_SYS1_SWAY_READ_COMMAND_OVERRIDE_ASNOOP_SHFT                                0x18
#define HWIO_BIMC_S_SYS1_SWAY_READ_COMMAND_OVERRIDE_AMEMTYPE_BMSK                          0x7f0000
#define HWIO_BIMC_S_SYS1_SWAY_READ_COMMAND_OVERRIDE_AMEMTYPE_SHFT                              0x10
#define HWIO_BIMC_S_SYS1_SWAY_READ_COMMAND_OVERRIDE_APORTMREL_BMSK                            0x800
#define HWIO_BIMC_S_SYS1_SWAY_READ_COMMAND_OVERRIDE_APORTMREL_SHFT                              0xb
#define HWIO_BIMC_S_SYS1_SWAY_READ_COMMAND_OVERRIDE_ASHARED_BMSK                              0x200
#define HWIO_BIMC_S_SYS1_SWAY_READ_COMMAND_OVERRIDE_ASHARED_SHFT                                0x9
#define HWIO_BIMC_S_SYS1_SWAY_READ_COMMAND_OVERRIDE_AINNERSHARED_BMSK                         0x100
#define HWIO_BIMC_S_SYS1_SWAY_READ_COMMAND_OVERRIDE_AINNERSHARED_SHFT                           0x8
#define HWIO_BIMC_S_SYS1_SWAY_READ_COMMAND_OVERRIDE_OVERRIDE_ASNOOP_BMSK                       0x80
#define HWIO_BIMC_S_SYS1_SWAY_READ_COMMAND_OVERRIDE_OVERRIDE_ASNOOP_SHFT                        0x7
#define HWIO_BIMC_S_SYS1_SWAY_READ_COMMAND_OVERRIDE_OVERRIDE_AMEMTYPE_BMSK                     0x40
#define HWIO_BIMC_S_SYS1_SWAY_READ_COMMAND_OVERRIDE_OVERRIDE_AMEMTYPE_SHFT                      0x6
#define HWIO_BIMC_S_SYS1_SWAY_READ_COMMAND_OVERRIDE_OVERRIDE_APORTMREL_BMSK                     0x8
#define HWIO_BIMC_S_SYS1_SWAY_READ_COMMAND_OVERRIDE_OVERRIDE_APORTMREL_SHFT                     0x3
#define HWIO_BIMC_S_SYS1_SWAY_READ_COMMAND_OVERRIDE_OVERRIDE_ASHARED_BMSK                       0x2
#define HWIO_BIMC_S_SYS1_SWAY_READ_COMMAND_OVERRIDE_OVERRIDE_ASHARED_SHFT                       0x1
#define HWIO_BIMC_S_SYS1_SWAY_READ_COMMAND_OVERRIDE_OVERRIDE_AINNERSHARED_BMSK                  0x1
#define HWIO_BIMC_S_SYS1_SWAY_READ_COMMAND_OVERRIDE_OVERRIDE_AINNERSHARED_SHFT                  0x0

#define HWIO_BIMC_S_SYS1_SWAY_WRITE_COMMAND_OVERRIDE_ADDR                                (BIMC_S_SYS1_SWAY_REG_BASE      + 0x00000260)
#define HWIO_BIMC_S_SYS1_SWAY_WRITE_COMMAND_OVERRIDE_RMSK                                 0xf7f0fcf
#define HWIO_BIMC_S_SYS1_SWAY_WRITE_COMMAND_OVERRIDE_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_WRITE_COMMAND_OVERRIDE_ADDR, HWIO_BIMC_S_SYS1_SWAY_WRITE_COMMAND_OVERRIDE_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_WRITE_COMMAND_OVERRIDE_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_WRITE_COMMAND_OVERRIDE_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_WRITE_COMMAND_OVERRIDE_OUT(v)      \
        out_dword(HWIO_BIMC_S_SYS1_SWAY_WRITE_COMMAND_OVERRIDE_ADDR,v)
#define HWIO_BIMC_S_SYS1_SWAY_WRITE_COMMAND_OVERRIDE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_S_SYS1_SWAY_WRITE_COMMAND_OVERRIDE_ADDR,m,v,HWIO_BIMC_S_SYS1_SWAY_WRITE_COMMAND_OVERRIDE_IN)
#define HWIO_BIMC_S_SYS1_SWAY_WRITE_COMMAND_OVERRIDE_ASNOOP_BMSK                          0xf000000
#define HWIO_BIMC_S_SYS1_SWAY_WRITE_COMMAND_OVERRIDE_ASNOOP_SHFT                               0x18
#define HWIO_BIMC_S_SYS1_SWAY_WRITE_COMMAND_OVERRIDE_AMEMTYPE_BMSK                         0x7f0000
#define HWIO_BIMC_S_SYS1_SWAY_WRITE_COMMAND_OVERRIDE_AMEMTYPE_SHFT                             0x10
#define HWIO_BIMC_S_SYS1_SWAY_WRITE_COMMAND_OVERRIDE_APORTMREL_BMSK                           0x800
#define HWIO_BIMC_S_SYS1_SWAY_WRITE_COMMAND_OVERRIDE_APORTMREL_SHFT                             0xb
#define HWIO_BIMC_S_SYS1_SWAY_WRITE_COMMAND_OVERRIDE_AUNIQUE_BMSK                             0x400
#define HWIO_BIMC_S_SYS1_SWAY_WRITE_COMMAND_OVERRIDE_AUNIQUE_SHFT                               0xa
#define HWIO_BIMC_S_SYS1_SWAY_WRITE_COMMAND_OVERRIDE_ASHARED_BMSK                             0x200
#define HWIO_BIMC_S_SYS1_SWAY_WRITE_COMMAND_OVERRIDE_ASHARED_SHFT                               0x9
#define HWIO_BIMC_S_SYS1_SWAY_WRITE_COMMAND_OVERRIDE_AINNERSHARED_BMSK                        0x100
#define HWIO_BIMC_S_SYS1_SWAY_WRITE_COMMAND_OVERRIDE_AINNERSHARED_SHFT                          0x8
#define HWIO_BIMC_S_SYS1_SWAY_WRITE_COMMAND_OVERRIDE_OVERRIDE_ASNOOP_BMSK                      0x80
#define HWIO_BIMC_S_SYS1_SWAY_WRITE_COMMAND_OVERRIDE_OVERRIDE_ASNOOP_SHFT                       0x7
#define HWIO_BIMC_S_SYS1_SWAY_WRITE_COMMAND_OVERRIDE_OVERRIDE_AMEMTYPE_BMSK                    0x40
#define HWIO_BIMC_S_SYS1_SWAY_WRITE_COMMAND_OVERRIDE_OVERRIDE_AMEMTYPE_SHFT                     0x6
#define HWIO_BIMC_S_SYS1_SWAY_WRITE_COMMAND_OVERRIDE_OVERRIDE_APORTMREL_BMSK                    0x8
#define HWIO_BIMC_S_SYS1_SWAY_WRITE_COMMAND_OVERRIDE_OVERRIDE_APORTMREL_SHFT                    0x3
#define HWIO_BIMC_S_SYS1_SWAY_WRITE_COMMAND_OVERRIDE_OVERRIDE_AUNIQUE_BMSK                      0x4
#define HWIO_BIMC_S_SYS1_SWAY_WRITE_COMMAND_OVERRIDE_OVERRIDE_AUNIQUE_SHFT                      0x2
#define HWIO_BIMC_S_SYS1_SWAY_WRITE_COMMAND_OVERRIDE_OVERRIDE_ASHARED_BMSK                      0x2
#define HWIO_BIMC_S_SYS1_SWAY_WRITE_COMMAND_OVERRIDE_OVERRIDE_ASHARED_SHFT                      0x1
#define HWIO_BIMC_S_SYS1_SWAY_WRITE_COMMAND_OVERRIDE_OVERRIDE_AINNERSHARED_BMSK                 0x1
#define HWIO_BIMC_S_SYS1_SWAY_WRITE_COMMAND_OVERRIDE_OVERRIDE_AINNERSHARED_SHFT                 0x0

#define HWIO_BIMC_S_SYS1_SWAY_STATUS_0A_ADDR                                             (BIMC_S_SYS1_SWAY_REG_BASE      + 0x00000400)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_0A_RMSK                                               0xff00ff
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_0A_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_STATUS_0A_ADDR, HWIO_BIMC_S_SYS1_SWAY_STATUS_0A_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_0A_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_STATUS_0A_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_0A_WR_PENDING_PRE_BUF_BMSK                            0xff0000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_0A_WR_PENDING_PRE_BUF_SHFT                                0x10
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_0A_RD_PENDING_PRE_BUF_BMSK                                0xff
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_0A_RD_PENDING_PRE_BUF_SHFT                                 0x0

#define HWIO_BIMC_S_SYS1_SWAY_STATUS_0B_ADDR                                             (BIMC_S_SYS1_SWAY_REG_BASE      + 0x00000404)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_0B_RMSK                                               0xff00ff
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_0B_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_STATUS_0B_ADDR, HWIO_BIMC_S_SYS1_SWAY_STATUS_0B_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_0B_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_STATUS_0B_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_0B_WR_PENDING_POST_BUF_BMSK                           0xff0000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_0B_WR_PENDING_POST_BUF_SHFT                               0x10
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_0B_RD_PENDING_POST_BUF_BMSK                               0xff
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_0B_RD_PENDING_POST_BUF_SHFT                                0x0

#define HWIO_BIMC_S_SYS1_SWAY_STATUS_0C_ADDR                                             (BIMC_S_SYS1_SWAY_REG_BASE      + 0x00000408)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_0C_RMSK                                              0x3f03f0f
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_0C_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_STATUS_0C_ADDR, HWIO_BIMC_S_SYS1_SWAY_STATUS_0C_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_0C_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_STATUS_0C_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_0C_RDQ_FULL_BMSK                                     0x3f00000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_0C_RDQ_FULL_SHFT                                          0x14
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_0C_WRQ_FULL_BMSK                                        0x3f00
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_0C_WRQ_FULL_SHFT                                           0x8
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_0C_CMDQ_FULL_BMSK                                          0xf
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_0C_CMDQ_FULL_SHFT                                          0x0

#define HWIO_BIMC_S_SYS1_SWAY_STATUS_0D_ADDR                                             (BIMC_S_SYS1_SWAY_REG_BASE      + 0x0000040c)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_0D_RMSK                                              0x3f03f0f
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_0D_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_STATUS_0D_ADDR, HWIO_BIMC_S_SYS1_SWAY_STATUS_0D_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_0D_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_STATUS_0D_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_0D_RDQ_ALMOST_FULL_BMSK                              0x3f00000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_0D_RDQ_ALMOST_FULL_SHFT                                   0x14
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_0D_WRQ_ALMOST_FULL_BMSK                                 0x3f00
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_0D_WRQ_ALMOST_FULL_SHFT                                    0x8
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_0D_CMDQ_ALMOST_FULL_BMSK                                   0xf
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_0D_CMDQ_ALMOST_FULL_SHFT                                   0x0

#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_ADDR                                             (BIMC_S_SYS1_SWAY_REG_BASE      + 0x00000410)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_RMSK                                             0xff333333
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_ADDR, HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_RCB0_DATA_RD_FULL_BMSK                           0x80000000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_RCB0_DATA_RD_FULL_SHFT                                 0x1f
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_RCB0_DATA_RD_EMPTY_BMSK                          0x40000000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_RCB0_DATA_RD_EMPTY_SHFT                                0x1e
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_RCB0_CTRL_RD_FULL_BMSK                           0x20000000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_RCB0_CTRL_RD_FULL_SHFT                                 0x1d
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_RCB0_CTRL_RD_EMPTY_BMSK                          0x10000000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_RCB0_CTRL_RD_EMPTY_SHFT                                0x1c
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_RCB0_DATA_WR_FULL_BMSK                            0x8000000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_RCB0_DATA_WR_FULL_SHFT                                 0x1b
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_RCB0_DATA_WR_EMPTY_BMSK                           0x4000000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_RCB0_DATA_WR_EMPTY_SHFT                                0x1a
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_RCB0_CTRL_WR_FULL_BMSK                            0x2000000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_RCB0_CTRL_WR_FULL_SHFT                                 0x19
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_RCB0_CTRL_WR_EMPTY_BMSK                           0x1000000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_RCB0_CTRL_WR_EMPTY_SHFT                                0x18
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_BCB_RD_FULL_BMSK                                   0x200000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_BCB_RD_FULL_SHFT                                       0x15
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_BCB_RD_EMPTY_BMSK                                  0x100000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_BCB_RD_EMPTY_SHFT                                      0x14
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_BCB_WR_FULL_BMSK                                    0x20000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_BCB_WR_FULL_SHFT                                       0x11
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_BCB_WR_EMPTY_BMSK                                   0x10000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_BCB_WR_EMPTY_SHFT                                      0x10
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_WCB_RD_FULL_BMSK                                     0x2000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_WCB_RD_FULL_SHFT                                        0xd
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_WCB_RD_EMPTY_BMSK                                    0x1000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_WCB_RD_EMPTY_SHFT                                       0xc
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_WCB_WR_FULL_BMSK                                      0x200
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_WCB_WR_FULL_SHFT                                        0x9
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_WCB_WR_EMPTY_BMSK                                     0x100
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_WCB_WR_EMPTY_SHFT                                       0x8
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_ACB_RD_FULL_BMSK                                       0x20
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_ACB_RD_FULL_SHFT                                        0x5
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_ACB_RD_EMPTY_BMSK                                      0x10
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_ACB_RD_EMPTY_SHFT                                       0x4
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_ACB_WR_FULL_BMSK                                        0x2
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_ACB_WR_FULL_SHFT                                        0x1
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_ACB_WR_EMPTY_BMSK                                       0x1
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1A_ACB_WR_EMPTY_SHFT                                       0x0

#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_ADDR                                             (BIMC_S_SYS1_SWAY_REG_BASE      + 0x00000414)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_RMSK                                             0x33333333
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_ADDR, HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_WIB_RD_FULL_BMSK                                 0x20000000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_WIB_RD_FULL_SHFT                                       0x1d
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_WIB_RD_EMPTY_BMSK                                0x10000000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_WIB_RD_EMPTY_SHFT                                      0x1c
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_WIB_WR_FULL_BMSK                                  0x2000000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_WIB_WR_FULL_SHFT                                       0x19
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_WIB_WR_EMPTY_BMSK                                 0x1000000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_WIB_WR_EMPTY_SHFT                                      0x18
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_RGB0_RD_FULL_BMSK                                  0x200000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_RGB0_RD_FULL_SHFT                                      0x15
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_RGB0_RD_EMPTY_BMSK                                 0x100000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_RGB0_RD_EMPTY_SHFT                                     0x14
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_RGB0_WR_FULL_BMSK                                   0x20000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_RGB0_WR_FULL_SHFT                                      0x11
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_RGB0_WR_EMPTY_BMSK                                  0x10000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_RGB0_WR_EMPTY_SHFT                                     0x10
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_W2AB_RD_FULL_BMSK                                    0x2000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_W2AB_RD_FULL_SHFT                                       0xd
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_W2AB_RD_EMPTY_BMSK                                   0x1000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_W2AB_RD_EMPTY_SHFT                                      0xc
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_W2AB_WR_FULL_BMSK                                     0x200
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_W2AB_WR_FULL_SHFT                                       0x9
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_W2AB_WR_EMPTY_BMSK                                    0x100
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_W2AB_WR_EMPTY_SHFT                                      0x8
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_A2WB_RD_FULL_BMSK                                      0x20
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_A2WB_RD_FULL_SHFT                                       0x5
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_A2WB_RD_EMPTY_BMSK                                     0x10
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_A2WB_RD_EMPTY_SHFT                                      0x4
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_A2WB_WR_FULL_BMSK                                       0x2
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_A2WB_WR_FULL_SHFT                                       0x1
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_A2WB_WR_EMPTY_BMSK                                      0x1
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1B_A2WB_WR_EMPTY_SHFT                                      0x0

#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1C_ADDR                                             (BIMC_S_SYS1_SWAY_REG_BASE      + 0x00000418)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1C_RMSK                                                 0x33ff
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1C_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_STATUS_1C_ADDR, HWIO_BIMC_S_SYS1_SWAY_STATUS_1C_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1C_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_STATUS_1C_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1C_RGB1_RD_FULL_BMSK                                    0x2000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1C_RGB1_RD_FULL_SHFT                                       0xd
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1C_RGB1_RD_EMPTY_BMSK                                   0x1000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1C_RGB1_RD_EMPTY_SHFT                                      0xc
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1C_RGB1_WR_FULL_BMSK                                     0x200
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1C_RGB1_WR_FULL_SHFT                                       0x9
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1C_RGB1_WR_EMPTY_BMSK                                    0x100
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1C_RGB1_WR_EMPTY_SHFT                                      0x8
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1C_RCB1_DATA_RD_FULL_BMSK                                 0x80
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1C_RCB1_DATA_RD_FULL_SHFT                                  0x7
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1C_RCB1_DATA_RD_EMPTY_BMSK                                0x40
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1C_RCB1_DATA_RD_EMPTY_SHFT                                 0x6
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1C_RCB1_CTRL_RD_FULL_BMSK                                 0x20
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1C_RCB1_CTRL_RD_FULL_SHFT                                  0x5
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1C_RCB1_CTRL_RD_EMPTY_BMSK                                0x10
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1C_RCB1_CTRL_RD_EMPTY_SHFT                                 0x4
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1C_RCB1_DATA_WR_FULL_BMSK                                  0x8
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1C_RCB1_DATA_WR_FULL_SHFT                                  0x3
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1C_RCB1_DATA_WR_EMPTY_BMSK                                 0x4
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1C_RCB1_DATA_WR_EMPTY_SHFT                                 0x2
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1C_RCB1_CTRL_WR_FULL_BMSK                                  0x2
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1C_RCB1_CTRL_WR_FULL_SHFT                                  0x1
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1C_RCB1_CTRL_WR_EMPTY_BMSK                                 0x1
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_1C_RCB1_CTRL_WR_EMPTY_SHFT                                 0x0

#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2A_ADDR                                             (BIMC_S_SYS1_SWAY_REG_BASE      + 0x00000420)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2A_RMSK                                             0xffffffff
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2A_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_STATUS_2A_ADDR, HWIO_BIMC_S_SYS1_SWAY_STATUS_2A_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2A_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_STATUS_2A_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2A_RD_PENDING_PER_MSTR_3_BMSK                       0xff000000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2A_RD_PENDING_PER_MSTR_3_SHFT                             0x18
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2A_RD_PENDING_PER_MSTR_2_BMSK                         0xff0000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2A_RD_PENDING_PER_MSTR_2_SHFT                             0x10
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2A_RD_PENDING_PER_MSTR_1_BMSK                           0xff00
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2A_RD_PENDING_PER_MSTR_1_SHFT                              0x8
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2A_RD_PENDING_PER_MSTR_0_BMSK                             0xff
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2A_RD_PENDING_PER_MSTR_0_SHFT                              0x0

#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2B_ADDR                                             (BIMC_S_SYS1_SWAY_REG_BASE      + 0x00000424)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2B_RMSK                                             0xffffffff
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2B_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_STATUS_2B_ADDR, HWIO_BIMC_S_SYS1_SWAY_STATUS_2B_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2B_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_STATUS_2B_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2B_RD_PENDING_PER_MSTR_7_BMSK                       0xff000000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2B_RD_PENDING_PER_MSTR_7_SHFT                             0x18
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2B_RD_PENDING_PER_MSTR_6_BMSK                         0xff0000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2B_RD_PENDING_PER_MSTR_6_SHFT                             0x10
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2B_RD_PENDING_PER_MSTR_5_BMSK                           0xff00
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2B_RD_PENDING_PER_MSTR_5_SHFT                              0x8
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2B_RD_PENDING_PER_MSTR_4_BMSK                             0xff
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2B_RD_PENDING_PER_MSTR_4_SHFT                              0x0

#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2C_ADDR                                             (BIMC_S_SYS1_SWAY_REG_BASE      + 0x00000428)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2C_RMSK                                             0xffffffff
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2C_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_STATUS_2C_ADDR, HWIO_BIMC_S_SYS1_SWAY_STATUS_2C_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2C_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_STATUS_2C_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2C_RD_PENDING_PER_MSTR_11_BMSK                      0xff000000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2C_RD_PENDING_PER_MSTR_11_SHFT                            0x18
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2C_RD_PENDING_PER_MSTR_10_BMSK                        0xff0000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2C_RD_PENDING_PER_MSTR_10_SHFT                            0x10
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2C_RD_PENDING_PER_MSTR_9_BMSK                           0xff00
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2C_RD_PENDING_PER_MSTR_9_SHFT                              0x8
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2C_RD_PENDING_PER_MSTR_8_BMSK                             0xff
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2C_RD_PENDING_PER_MSTR_8_SHFT                              0x0

#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2D_ADDR                                             (BIMC_S_SYS1_SWAY_REG_BASE      + 0x0000042c)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2D_RMSK                                             0xffffffff
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2D_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_STATUS_2D_ADDR, HWIO_BIMC_S_SYS1_SWAY_STATUS_2D_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2D_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_STATUS_2D_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2D_RD_PENDING_PER_MSTR_15_BMSK                      0xff000000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2D_RD_PENDING_PER_MSTR_15_SHFT                            0x18
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2D_RD_PENDING_PER_MSTR_14_BMSK                        0xff0000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2D_RD_PENDING_PER_MSTR_14_SHFT                            0x10
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2D_RD_PENDING_PER_MSTR_13_BMSK                          0xff00
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2D_RD_PENDING_PER_MSTR_13_SHFT                             0x8
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2D_RD_PENDING_PER_MSTR_12_BMSK                            0xff
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_2D_RD_PENDING_PER_MSTR_12_SHFT                             0x0

#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3A_ADDR                                             (BIMC_S_SYS1_SWAY_REG_BASE      + 0x00000430)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3A_RMSK                                             0xffffffff
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3A_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_STATUS_3A_ADDR, HWIO_BIMC_S_SYS1_SWAY_STATUS_3A_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3A_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_STATUS_3A_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3A_WR_PENDING_PER_MSTR_3_BMSK                       0xff000000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3A_WR_PENDING_PER_MSTR_3_SHFT                             0x18
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3A_WR_PENDING_PER_MSTR_2_BMSK                         0xff0000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3A_WR_PENDING_PER_MSTR_2_SHFT                             0x10
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3A_WR_PENDING_PER_MSTR_1_BMSK                           0xff00
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3A_WR_PENDING_PER_MSTR_1_SHFT                              0x8
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3A_WR_PENDING_PER_MSTR_0_BMSK                             0xff
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3A_WR_PENDING_PER_MSTR_0_SHFT                              0x0

#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3B_ADDR                                             (BIMC_S_SYS1_SWAY_REG_BASE      + 0x00000434)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3B_RMSK                                             0xffffffff
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3B_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_STATUS_3B_ADDR, HWIO_BIMC_S_SYS1_SWAY_STATUS_3B_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3B_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_STATUS_3B_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3B_WR_PENDING_PER_MSTR_7_BMSK                       0xff000000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3B_WR_PENDING_PER_MSTR_7_SHFT                             0x18
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3B_WR_PENDING_PER_MSTR_6_BMSK                         0xff0000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3B_WR_PENDING_PER_MSTR_6_SHFT                             0x10
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3B_WR_PENDING_PER_MSTR_5_BMSK                           0xff00
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3B_WR_PENDING_PER_MSTR_5_SHFT                              0x8
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3B_WR_PENDING_PER_MSTR_4_BMSK                             0xff
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3B_WR_PENDING_PER_MSTR_4_SHFT                              0x0

#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3C_ADDR                                             (BIMC_S_SYS1_SWAY_REG_BASE      + 0x00000438)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3C_RMSK                                             0xffffffff
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3C_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_STATUS_3C_ADDR, HWIO_BIMC_S_SYS1_SWAY_STATUS_3C_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3C_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_STATUS_3C_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3C_WR_PENDING_PER_MSTR_11_BMSK                      0xff000000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3C_WR_PENDING_PER_MSTR_11_SHFT                            0x18
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3C_WR_PENDING_PER_MSTR_10_BMSK                        0xff0000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3C_WR_PENDING_PER_MSTR_10_SHFT                            0x10
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3C_WR_PENDING_PER_MSTR_9_BMSK                           0xff00
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3C_WR_PENDING_PER_MSTR_9_SHFT                              0x8
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3C_WR_PENDING_PER_MSTR_8_BMSK                             0xff
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3C_WR_PENDING_PER_MSTR_8_SHFT                              0x0

#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3D_ADDR                                             (BIMC_S_SYS1_SWAY_REG_BASE      + 0x0000043c)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3D_RMSK                                             0xffffffff
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3D_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_STATUS_3D_ADDR, HWIO_BIMC_S_SYS1_SWAY_STATUS_3D_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3D_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_STATUS_3D_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3D_WR_PENDING_PER_MSTR_15_BMSK                      0xff000000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3D_WR_PENDING_PER_MSTR_15_SHFT                            0x18
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3D_WR_PENDING_PER_MSTR_14_BMSK                        0xff0000
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3D_WR_PENDING_PER_MSTR_14_SHFT                            0x10
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3D_WR_PENDING_PER_MSTR_13_BMSK                          0xff00
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3D_WR_PENDING_PER_MSTR_13_SHFT                             0x8
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3D_WR_PENDING_PER_MSTR_12_BMSK                            0xff
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_3D_WR_PENDING_PER_MSTR_12_SHFT                             0x0

#define HWIO_BIMC_S_SYS1_SWAY_STATUS_4A_ADDR                                             (BIMC_S_SYS1_SWAY_REG_BASE      + 0x00000440)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_4A_RMSK                                                   0xff
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_4A_IN          \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_STATUS_4A_ADDR, HWIO_BIMC_S_SYS1_SWAY_STATUS_4A_RMSK)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_4A_INM(m)      \
        in_dword_masked(HWIO_BIMC_S_SYS1_SWAY_STATUS_4A_ADDR, m)
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_4A_SWAY_VALID_READY_BMSK                                  0xff
#define HWIO_BIMC_S_SYS1_SWAY_STATUS_4A_SWAY_VALID_READY_SHFT                                   0x0

/*----------------------------------------------------------------------------
 * MODULE: BIMC_M_APP_MPORT
 *--------------------------------------------------------------------------*/

#define BIMC_M_APP_MPORT_REG_BASE                                                           (DDR_SS_BASE      + 0x0000b000)

#define HWIO_BIMC_M_APP_MPORT_COMPONENT_INFO_ADDR                                           (BIMC_M_APP_MPORT_REG_BASE      + 0x00000000)
#define HWIO_BIMC_M_APP_MPORT_COMPONENT_INFO_RMSK                                             0xffffff
#define HWIO_BIMC_M_APP_MPORT_COMPONENT_INFO_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_COMPONENT_INFO_ADDR, HWIO_BIMC_M_APP_MPORT_COMPONENT_INFO_RMSK)
#define HWIO_BIMC_M_APP_MPORT_COMPONENT_INFO_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_COMPONENT_INFO_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_COMPONENT_INFO_INSTANCE_BMSK                                    0xff0000
#define HWIO_BIMC_M_APP_MPORT_COMPONENT_INFO_INSTANCE_SHFT                                        0x10
#define HWIO_BIMC_M_APP_MPORT_COMPONENT_INFO_SUB_TYPE_BMSK                                      0xff00
#define HWIO_BIMC_M_APP_MPORT_COMPONENT_INFO_SUB_TYPE_SHFT                                         0x8
#define HWIO_BIMC_M_APP_MPORT_COMPONENT_INFO_TYPE_BMSK                                            0xff
#define HWIO_BIMC_M_APP_MPORT_COMPONENT_INFO_TYPE_SHFT                                             0x0

#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_0_ADDR                                     (BIMC_M_APP_MPORT_REG_BASE      + 0x00000020)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_0_RMSK                                     0x3f00ffff
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_0_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_0_ADDR, HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_0_RMSK)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_0_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_0_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_0_PIPE2_SYNC_MODE_BMSK                     0x30000000
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_0_PIPE2_SYNC_MODE_SHFT                           0x1c
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_0_PIPE1_SYNC_MODE_BMSK                      0xc000000
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_0_PIPE1_SYNC_MODE_SHFT                           0x1a
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_0_PIPE0_SYNC_MODE_BMSK                      0x3000000
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_0_PIPE0_SYNC_MODE_SHFT                           0x18
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_0_CONNECTION_TYPE_BMSK                         0xff00
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_0_CONNECTION_TYPE_SHFT                            0x8
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_0_FUNCTIONALITY_BMSK                             0xff
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_0_FUNCTIONALITY_SHFT                              0x0

#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_1_ADDR                                     (BIMC_M_APP_MPORT_REG_BASE      + 0x00000030)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_1_RMSK                                     0xffffffff
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_1_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_1_ADDR, HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_1_RMSK)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_1_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_1_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_1_SWAY_CONNECTIVITY_BMSK                   0xffffffff
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_1_SWAY_CONNECTIVITY_SHFT                          0x0

#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_2A_ADDR                                    (BIMC_M_APP_MPORT_REG_BASE      + 0x00000040)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_2A_RMSK                                    0xffffffff
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_2A_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_2A_ADDR, HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_2A_RMSK)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_2A_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_2A_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_2A_M_DATA_WIDTH_BMSK                       0xffff0000
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_2A_M_DATA_WIDTH_SHFT                             0x10
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_2A_M_TID_WIDTH_BMSK                            0xff00
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_2A_M_TID_WIDTH_SHFT                               0x8
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_2A_M_MID_WIDTH_BMSK                              0xff
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_2A_M_MID_WIDTH_SHFT                               0x0

#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_2B_ADDR                                    (BIMC_M_APP_MPORT_REG_BASE      + 0x00000044)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_2B_RMSK                                    0xffffffff
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_2B_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_2B_ADDR, HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_2B_RMSK)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_2B_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_2B_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_2B_PIPE1_DATA_WIDTH_BMSK                   0xffff0000
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_2B_PIPE1_DATA_WIDTH_SHFT                         0x10
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_2B_PIPE0_DATA_WIDTH_BMSK                       0xffff
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_2B_PIPE0_DATA_WIDTH_SHFT                          0x0

#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_2C_ADDR                                    (BIMC_M_APP_MPORT_REG_BASE      + 0x00000048)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_2C_RMSK                                        0xffff
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_2C_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_2C_ADDR, HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_2C_RMSK)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_2C_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_2C_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_2C_PIPE2_DATA_WIDTH_BMSK                       0xffff
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_2C_PIPE2_DATA_WIDTH_SHFT                          0x0

#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3A_ADDR                                    (BIMC_M_APP_MPORT_REG_BASE      + 0x00000050)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3A_RMSK                                    0xffffffff
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3A_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3A_ADDR, HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3A_RMSK)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3A_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3A_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3A_PIPE0_RCH_DEPTH_BMSK                    0xff000000
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3A_PIPE0_RCH_DEPTH_SHFT                          0x18
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3A_PIPE0_BCH_DEPTH_BMSK                      0xff0000
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3A_PIPE0_BCH_DEPTH_SHFT                          0x10
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3A_PIPE0_WCH_DEPTH_BMSK                        0xff00
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3A_PIPE0_WCH_DEPTH_SHFT                           0x8
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3A_PIPE0_ACH_DEPTH_BMSK                          0xff
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3A_PIPE0_ACH_DEPTH_SHFT                           0x0

#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3B_ADDR                                    (BIMC_M_APP_MPORT_REG_BASE      + 0x00000054)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3B_RMSK                                    0xffffffff
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3B_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3B_ADDR, HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3B_RMSK)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3B_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3B_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3B_PIPE1_RCH_DEPTH_BMSK                    0xff000000
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3B_PIPE1_RCH_DEPTH_SHFT                          0x18
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3B_PIPE1_BCH_DEPTH_BMSK                      0xff0000
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3B_PIPE1_BCH_DEPTH_SHFT                          0x10
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3B_PIPE1_WCH_DEPTH_BMSK                        0xff00
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3B_PIPE1_WCH_DEPTH_SHFT                           0x8
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3B_PIPE1_ACH_DEPTH_BMSK                          0xff
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3B_PIPE1_ACH_DEPTH_SHFT                           0x0

#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3C_ADDR                                    (BIMC_M_APP_MPORT_REG_BASE      + 0x00000058)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3C_RMSK                                    0xffffffff
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3C_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3C_ADDR, HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3C_RMSK)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3C_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3C_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3C_PIPE2_RCH_DEPTH_BMSK                    0xff000000
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3C_PIPE2_RCH_DEPTH_SHFT                          0x18
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3C_PIPE2_BCH_DEPTH_BMSK                      0xff0000
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3C_PIPE2_BCH_DEPTH_SHFT                          0x10
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3C_PIPE2_WCH_DEPTH_BMSK                        0xff00
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3C_PIPE2_WCH_DEPTH_SHFT                           0x8
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3C_PIPE2_ACH_DEPTH_BMSK                          0xff
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_3C_PIPE2_ACH_DEPTH_SHFT                           0x0

#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_4_ADDR                                     (BIMC_M_APP_MPORT_REG_BASE      + 0x00000060)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_4_RMSK                                         0xffff
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_4_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_4_ADDR, HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_4_RMSK)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_4_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_4_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_4_REORDER_BUFFER_DEPTH_BMSK                    0xff00
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_4_REORDER_BUFFER_DEPTH_SHFT                       0x8
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_4_REORDER_TABLE_DEPTH_BMSK                       0xff
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_4_REORDER_TABLE_DEPTH_SHFT                        0x0

#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_5A_ADDR                                    (BIMC_M_APP_MPORT_REG_BASE      + 0x00000070)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_5A_RMSK                                    0xffffffff
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_5A_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_5A_ADDR, HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_5A_RMSK)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_5A_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_5A_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_5A_ACH_PIPELINE_STAGES_BMSK                0xffffffff
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_5A_ACH_PIPELINE_STAGES_SHFT                       0x0

#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_5B_ADDR                                    (BIMC_M_APP_MPORT_REG_BASE      + 0x00000074)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_5B_RMSK                                    0xffffffff
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_5B_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_5B_ADDR, HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_5B_RMSK)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_5B_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_5B_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_5B_WCH_PIPELINE_STAGES_BMSK                0xffffffff
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_5B_WCH_PIPELINE_STAGES_SHFT                       0x0

#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_5C_ADDR                                    (BIMC_M_APP_MPORT_REG_BASE      + 0x00000078)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_5C_RMSK                                    0xffffffff
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_5C_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_5C_ADDR, HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_5C_RMSK)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_5C_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_5C_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_5C_BCH_PIPELINE_STAGES_BMSK                0xffffffff
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_5C_BCH_PIPELINE_STAGES_SHFT                       0x0

#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_5D_ADDR                                    (BIMC_M_APP_MPORT_REG_BASE      + 0x0000007c)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_5D_RMSK                                    0xffffffff
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_5D_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_5D_ADDR, HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_5D_RMSK)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_5D_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_5D_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_5D_RCH_PIPELINE_STAGES_BMSK                0xffffffff
#define HWIO_BIMC_M_APP_MPORT_CONFIGURATION_INFO_5D_RCH_PIPELINE_STAGES_SHFT                       0x0

#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_STATUS_ADDR                                         (BIMC_M_APP_MPORT_REG_BASE      + 0x00000100)
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_STATUS_RMSK                                               0xf3
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_STATUS_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_INTERRUPT_STATUS_ADDR, HWIO_BIMC_M_APP_MPORT_INTERRUPT_STATUS_RMSK)
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_STATUS_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_INTERRUPT_STATUS_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_STATUS_BWMON2_ZONE3_THRESHOLD_CROSSED_BMSK                0x80
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_STATUS_BWMON2_ZONE3_THRESHOLD_CROSSED_SHFT                 0x7
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_STATUS_BWMON2_ZONE2_THRESHOLD_CROSSED_BMSK                0x40
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_STATUS_BWMON2_ZONE2_THRESHOLD_CROSSED_SHFT                 0x6
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_STATUS_BWMON2_ZONE1_THRESHOLD_CROSSED_BMSK                0x20
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_STATUS_BWMON2_ZONE1_THRESHOLD_CROSSED_SHFT                 0x5
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_STATUS_BWMON2_ZONE0_THRESHOLD_CROSSED_BMSK                0x10
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_STATUS_BWMON2_ZONE0_THRESHOLD_CROSSED_SHFT                 0x4
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_STATUS_BWMON_OVERFLOW_BMSK                                 0x2
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_STATUS_BWMON_OVERFLOW_SHFT                                 0x1
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_STATUS_BWMON_THRESHOLD_CROSSED_BMSK                        0x1
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_STATUS_BWMON_THRESHOLD_CROSSED_SHFT                        0x0

#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_CLEAR_ADDR                                          (BIMC_M_APP_MPORT_REG_BASE      + 0x00000108)
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_CLEAR_RMSK                                                0xf3
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_CLEAR_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_INTERRUPT_CLEAR_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_CLEAR_BWMON2_ZONE3_THRESHOLD_CROSSED_BMSK                 0x80
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_CLEAR_BWMON2_ZONE3_THRESHOLD_CROSSED_SHFT                  0x7
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_CLEAR_BWMON2_ZONE2_THRESHOLD_CROSSED_BMSK                 0x40
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_CLEAR_BWMON2_ZONE2_THRESHOLD_CROSSED_SHFT                  0x6
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_CLEAR_BWMON2_ZONE1_THRESHOLD_CROSSED_BMSK                 0x20
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_CLEAR_BWMON2_ZONE1_THRESHOLD_CROSSED_SHFT                  0x5
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_CLEAR_BWMON2_ZONE0_THRESHOLD_CROSSED_BMSK                 0x10
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_CLEAR_BWMON2_ZONE0_THRESHOLD_CROSSED_SHFT                  0x4
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_CLEAR_BWMON_OVERFLOW_BMSK                                  0x2
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_CLEAR_BWMON_OVERFLOW_SHFT                                  0x1
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_CLEAR_BWMON_THRESHOLD_CROSSED_BMSK                         0x1
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_CLEAR_BWMON_THRESHOLD_CROSSED_SHFT                         0x0

#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_ENABLE_ADDR                                         (BIMC_M_APP_MPORT_REG_BASE      + 0x0000010c)
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_ENABLE_RMSK                                               0xf3
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_ENABLE_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_INTERRUPT_ENABLE_ADDR, HWIO_BIMC_M_APP_MPORT_INTERRUPT_ENABLE_RMSK)
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_ENABLE_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_INTERRUPT_ENABLE_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_ENABLE_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_INTERRUPT_ENABLE_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_INTERRUPT_ENABLE_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_INTERRUPT_ENABLE_IN)
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_ENABLE_BWMON2_ZONE3_THRESHOLD_CROSSED_BMSK                0x80
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_ENABLE_BWMON2_ZONE3_THRESHOLD_CROSSED_SHFT                 0x7
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_ENABLE_BWMON2_ZONE2_THRESHOLD_CROSSED_BMSK                0x40
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_ENABLE_BWMON2_ZONE2_THRESHOLD_CROSSED_SHFT                 0x6
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_ENABLE_BWMON2_ZONE1_THRESHOLD_CROSSED_BMSK                0x20
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_ENABLE_BWMON2_ZONE1_THRESHOLD_CROSSED_SHFT                 0x5
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_ENABLE_BWMON2_ZONE0_THRESHOLD_CROSSED_BMSK                0x10
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_ENABLE_BWMON2_ZONE0_THRESHOLD_CROSSED_SHFT                 0x4
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_ENABLE_BWMON_OVERFLOW_BMSK                                 0x2
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_ENABLE_BWMON_OVERFLOW_SHFT                                 0x1
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_ENABLE_BWMON_THRESHOLD_CROSSED_BMSK                        0x1
#define HWIO_BIMC_M_APP_MPORT_INTERRUPT_ENABLE_BWMON_THRESHOLD_CROSSED_SHFT                        0x0

#define HWIO_BIMC_M_APP_MPORT_CLOCK_CTRL_ADDR                                               (BIMC_M_APP_MPORT_REG_BASE      + 0x00000200)
#define HWIO_BIMC_M_APP_MPORT_CLOCK_CTRL_RMSK                                               0xff03001e
#define HWIO_BIMC_M_APP_MPORT_CLOCK_CTRL_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_CLOCK_CTRL_ADDR, HWIO_BIMC_M_APP_MPORT_CLOCK_CTRL_RMSK)
#define HWIO_BIMC_M_APP_MPORT_CLOCK_CTRL_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_CLOCK_CTRL_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_CLOCK_CTRL_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_CLOCK_CTRL_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_CLOCK_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_CLOCK_CTRL_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_CLOCK_CTRL_IN)
#define HWIO_BIMC_M_APP_MPORT_CLOCK_CTRL_IDLE_HYSTERESIS_BMSK                               0xff000000
#define HWIO_BIMC_M_APP_MPORT_CLOCK_CTRL_IDLE_HYSTERESIS_SHFT                                     0x18
#define HWIO_BIMC_M_APP_MPORT_CLOCK_CTRL_IDLE_CLOCK_ON_REQ_EN_BMSK                             0x20000
#define HWIO_BIMC_M_APP_MPORT_CLOCK_CTRL_IDLE_CLOCK_ON_REQ_EN_SHFT                                0x11
#define HWIO_BIMC_M_APP_MPORT_CLOCK_CTRL_IDLE_GATING_EN_BMSK                                   0x10000
#define HWIO_BIMC_M_APP_MPORT_CLOCK_CTRL_IDLE_GATING_EN_SHFT                                      0x10
#define HWIO_BIMC_M_APP_MPORT_CLOCK_CTRL_PIPE2_CLOCK_GATING_EN_BMSK                               0x10
#define HWIO_BIMC_M_APP_MPORT_CLOCK_CTRL_PIPE2_CLOCK_GATING_EN_SHFT                                0x4
#define HWIO_BIMC_M_APP_MPORT_CLOCK_CTRL_PIPE1_CLOCK_GATING_EN_BMSK                                0x8
#define HWIO_BIMC_M_APP_MPORT_CLOCK_CTRL_PIPE1_CLOCK_GATING_EN_SHFT                                0x3
#define HWIO_BIMC_M_APP_MPORT_CLOCK_CTRL_PIPE0_CLOCK_GATING_EN_BMSK                                0x4
#define HWIO_BIMC_M_APP_MPORT_CLOCK_CTRL_PIPE0_CLOCK_GATING_EN_SHFT                                0x2
#define HWIO_BIMC_M_APP_MPORT_CLOCK_CTRL_MASTER_CLOCK_GATING_EN_BMSK                               0x2
#define HWIO_BIMC_M_APP_MPORT_CLOCK_CTRL_MASTER_CLOCK_GATING_EN_SHFT                               0x1

#define HWIO_BIMC_M_APP_MPORT_CDC_CTRL_ADDR                                                 (BIMC_M_APP_MPORT_REG_BASE      + 0x00000208)
#define HWIO_BIMC_M_APP_MPORT_CDC_CTRL_RMSK                                                       0x1e
#define HWIO_BIMC_M_APP_MPORT_CDC_CTRL_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_CDC_CTRL_ADDR, HWIO_BIMC_M_APP_MPORT_CDC_CTRL_RMSK)
#define HWIO_BIMC_M_APP_MPORT_CDC_CTRL_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_CDC_CTRL_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_CDC_CTRL_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_CDC_CTRL_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_CDC_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_CDC_CTRL_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_CDC_CTRL_IN)
#define HWIO_BIMC_M_APP_MPORT_CDC_CTRL_PIPE2_CLOCK_DEMETA_SEL_BMSK                                0x10
#define HWIO_BIMC_M_APP_MPORT_CDC_CTRL_PIPE2_CLOCK_DEMETA_SEL_SHFT                                 0x4
#define HWIO_BIMC_M_APP_MPORT_CDC_CTRL_PIPE1_CLOCK_DEMETA_SEL_BMSK                                 0x8
#define HWIO_BIMC_M_APP_MPORT_CDC_CTRL_PIPE1_CLOCK_DEMETA_SEL_SHFT                                 0x3
#define HWIO_BIMC_M_APP_MPORT_CDC_CTRL_PIPE0_CLOCK_DEMETA_SEL_BMSK                                 0x4
#define HWIO_BIMC_M_APP_MPORT_CDC_CTRL_PIPE0_CLOCK_DEMETA_SEL_SHFT                                 0x2
#define HWIO_BIMC_M_APP_MPORT_CDC_CTRL_MASTER_CLOCK_DEMETA_SEL_BMSK                                0x2
#define HWIO_BIMC_M_APP_MPORT_CDC_CTRL_MASTER_CLOCK_DEMETA_SEL_SHFT                                0x1

#define HWIO_BIMC_M_APP_MPORT_MODE_ADDR                                                     (BIMC_M_APP_MPORT_REG_BASE      + 0x00000210)
#define HWIO_BIMC_M_APP_MPORT_MODE_RMSK                                                           0x7f
#define HWIO_BIMC_M_APP_MPORT_MODE_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_MODE_ADDR, HWIO_BIMC_M_APP_MPORT_MODE_RMSK)
#define HWIO_BIMC_M_APP_MPORT_MODE_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_MODE_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_MODE_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_MODE_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_MODE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_MODE_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_MODE_IN)
#define HWIO_BIMC_M_APP_MPORT_MODE_FAROB_BMSK                                                     0x40
#define HWIO_BIMC_M_APP_MPORT_MODE_FAROB_SHFT                                                      0x6
#define HWIO_BIMC_M_APP_MPORT_MODE_HWAUWD_BMSK                                                    0x20
#define HWIO_BIMC_M_APP_MPORT_MODE_HWAUWD_SHFT                                                     0x5
#define HWIO_BIMC_M_APP_MPORT_MODE_NARROW_WRITES_BMSK                                             0x10
#define HWIO_BIMC_M_APP_MPORT_MODE_NARROW_WRITES_SHFT                                              0x4
#define HWIO_BIMC_M_APP_MPORT_MODE_RFU_BMSK                                                        0x8
#define HWIO_BIMC_M_APP_MPORT_MODE_RFU_SHFT                                                        0x3
#define HWIO_BIMC_M_APP_MPORT_MODE_FIODV_BMSK                                                      0x4
#define HWIO_BIMC_M_APP_MPORT_MODE_FIODV_SHFT                                                      0x2
#define HWIO_BIMC_M_APP_MPORT_MODE_FIOSO_BMSK                                                      0x2
#define HWIO_BIMC_M_APP_MPORT_MODE_FIOSO_SHFT                                                      0x1
#define HWIO_BIMC_M_APP_MPORT_MODE_ORDERING_MODEL_BMSK                                             0x1
#define HWIO_BIMC_M_APP_MPORT_MODE_ORDERING_MODEL_SHFT                                             0x0

#define HWIO_BIMC_M_APP_MPORT_RD_INTERLEAVING_ADDR                                          (BIMC_M_APP_MPORT_REG_BASE      + 0x00000214)
#define HWIO_BIMC_M_APP_MPORT_RD_INTERLEAVING_RMSK                                                 0x3
#define HWIO_BIMC_M_APP_MPORT_RD_INTERLEAVING_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_RD_INTERLEAVING_ADDR, HWIO_BIMC_M_APP_MPORT_RD_INTERLEAVING_RMSK)
#define HWIO_BIMC_M_APP_MPORT_RD_INTERLEAVING_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_RD_INTERLEAVING_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_RD_INTERLEAVING_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_RD_INTERLEAVING_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_RD_INTERLEAVING_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_RD_INTERLEAVING_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_RD_INTERLEAVING_IN)
#define HWIO_BIMC_M_APP_MPORT_RD_INTERLEAVING_ENABLE_BMSK                                          0x3
#define HWIO_BIMC_M_APP_MPORT_RD_INTERLEAVING_ENABLE_SHFT                                          0x0

#define HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_ADDR                                            (BIMC_M_APP_MPORT_REG_BASE      + 0x00000218)
#define HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_RMSK                                            0xe0000fff
#define HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_ADDR, HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_RMSK)
#define HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_IN)
#define HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_ARMSA_BMSK                                      0x80000000
#define HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_ARMSA_SHFT                                            0x1f
#define HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_ARSP_BMSK                                       0x40000000
#define HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_ARSP_SHFT                                             0x1e
#define HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_RFU_BMSK                                        0x20000000
#define HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_RFU_SHFT                                              0x1d
#define HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_ROCSSH_BMSK                                          0x800
#define HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_ROCSSH_SHFT                                            0xb
#define HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_ROCOSH_BMSK                                          0x400
#define HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_ROCOSH_SHFT                                            0xa
#define HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_ROCISH_BMSK                                          0x200
#define HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_ROCISH_SHFT                                            0x9
#define HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_ROCNSH_BMSK                                          0x100
#define HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_ROCNSH_SHFT                                            0x8
#define HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_RICSSH_BMSK                                           0x80
#define HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_RICSSH_SHFT                                            0x7
#define HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_RICOSH_BMSK                                           0x40
#define HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_RICOSH_SHFT                                            0x6
#define HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_RICISH_BMSK                                           0x20
#define HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_RICISH_SHFT                                            0x5
#define HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_RICNSH_BMSK                                           0x10
#define HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_RICNSH_SHFT                                            0x4
#define HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_RNCSSH_BMSK                                            0x8
#define HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_RNCSSH_SHFT                                            0x3
#define HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_RNCOSH_BMSK                                            0x4
#define HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_RNCOSH_SHFT                                            0x2
#define HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_RNCISH_BMSK                                            0x2
#define HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_RNCISH_SHFT                                            0x1
#define HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_RNCNSH_BMSK                                            0x1
#define HWIO_BIMC_M_APP_MPORT_REDIRECT_CTRL_RNCNSH_SHFT                                            0x0

#define HWIO_BIMC_M_APP_MPORT_WR_WAY_CROSSING_ADDR                                          (BIMC_M_APP_MPORT_REG_BASE      + 0x00000220)
#define HWIO_BIMC_M_APP_MPORT_WR_WAY_CROSSING_RMSK                                                0x3f
#define HWIO_BIMC_M_APP_MPORT_WR_WAY_CROSSING_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_WR_WAY_CROSSING_ADDR, HWIO_BIMC_M_APP_MPORT_WR_WAY_CROSSING_RMSK)
#define HWIO_BIMC_M_APP_MPORT_WR_WAY_CROSSING_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_WR_WAY_CROSSING_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_WR_WAY_CROSSING_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_WR_WAY_CROSSING_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_WR_WAY_CROSSING_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_WR_WAY_CROSSING_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_WR_WAY_CROSSING_IN)
#define HWIO_BIMC_M_APP_MPORT_WR_WAY_CROSSING_REG_BMSK                                            0x3f
#define HWIO_BIMC_M_APP_MPORT_WR_WAY_CROSSING_REG_SHFT                                             0x0

#define HWIO_BIMC_M_APP_MPORT_PRIORITYLVL_OVERRIDE_ADDR                                     (BIMC_M_APP_MPORT_REG_BASE      + 0x00000230)
#define HWIO_BIMC_M_APP_MPORT_PRIORITYLVL_OVERRIDE_RMSK                                          0x301
#define HWIO_BIMC_M_APP_MPORT_PRIORITYLVL_OVERRIDE_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_PRIORITYLVL_OVERRIDE_ADDR, HWIO_BIMC_M_APP_MPORT_PRIORITYLVL_OVERRIDE_RMSK)
#define HWIO_BIMC_M_APP_MPORT_PRIORITYLVL_OVERRIDE_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_PRIORITYLVL_OVERRIDE_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_PRIORITYLVL_OVERRIDE_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_PRIORITYLVL_OVERRIDE_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_PRIORITYLVL_OVERRIDE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_PRIORITYLVL_OVERRIDE_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_PRIORITYLVL_OVERRIDE_IN)
#define HWIO_BIMC_M_APP_MPORT_PRIORITYLVL_OVERRIDE_PRIORITYLVL_BMSK                              0x300
#define HWIO_BIMC_M_APP_MPORT_PRIORITYLVL_OVERRIDE_PRIORITYLVL_SHFT                                0x8
#define HWIO_BIMC_M_APP_MPORT_PRIORITYLVL_OVERRIDE_OVERRIDE_PRIORITYLVL_BMSK                       0x1
#define HWIO_BIMC_M_APP_MPORT_PRIORITYLVL_OVERRIDE_OVERRIDE_PRIORITYLVL_SHFT                       0x0

#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_ADDR                                    (BIMC_M_APP_MPORT_REG_BASE      + 0x00000240)
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_RMSK                                     0x37f3fff
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_ADDR, HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_RMSK)
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_IN)
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_AREQPRIORITY_BMSK                        0x3000000
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_AREQPRIORITY_SHFT                             0x18
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_AMEMTYPE_BMSK                             0x7f0000
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_AMEMTYPE_SHFT                                 0x10
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_APORTMREL_BMSK                              0x2000
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_APORTMREL_SHFT                                 0xd
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_ATRANSIENT_BMSK                             0x1000
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_ATRANSIENT_SHFT                                0xc
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_ASHARED_BMSK                                 0x800
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_ASHARED_SHFT                                   0xb
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_AREDIRECT_BMSK                               0x400
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_AREDIRECT_SHFT                                 0xa
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_AOOO_BMSK                                    0x200
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_AOOO_SHFT                                      0x9
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_AINNERSHARED_BMSK                            0x100
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_AINNERSHARED_SHFT                              0x8
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_OVERRIDE_APORTMREL_BMSK                       0x80
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_OVERRIDE_APORTMREL_SHFT                        0x7
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_OVERRIDE_AREQPRIORITY_BMSK                    0x40
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_OVERRIDE_AREQPRIORITY_SHFT                     0x6
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_OVERRIDE_AMEMTYPE_BMSK                        0x20
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_OVERRIDE_AMEMTYPE_SHFT                         0x5
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_OVERRIDE_ATRANSIENT_BMSK                      0x10
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_OVERRIDE_ATRANSIENT_SHFT                       0x4
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_OVERRIDE_ASHARED_BMSK                          0x8
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_OVERRIDE_ASHARED_SHFT                          0x3
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_OVERRIDE_AREDIRECT_BMSK                        0x4
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_OVERRIDE_AREDIRECT_SHFT                        0x2
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_OVERRIDE_AOOO_BMSK                             0x2
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_OVERRIDE_AOOO_SHFT                             0x1
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_OVERRIDE_AINNERSHARED_BMSK                     0x1
#define HWIO_BIMC_M_APP_MPORT_READ_COMMAND_OVERRIDE_OVERRIDE_AINNERSHARED_SHFT                     0x0

#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_ADDR                                 (BIMC_M_APP_MPORT_REG_BASE      + 0x00000250)
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_RMSK                                  0x37f3fff
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_ADDR, HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_RMSK)
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_IN)
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_AREQPRIORITY_BMSK                     0x3000000
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_AREQPRIORITY_SHFT                          0x18
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_AMEMTYPE_BMSK                          0x7f0000
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_AMEMTYPE_SHFT                              0x10
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_APORTMREL_BMSK                           0x2000
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_APORTMREL_SHFT                              0xd
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_ATRANSIENT_BMSK                          0x1000
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_ATRANSIENT_SHFT                             0xc
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_ASHARED_BMSK                              0x800
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_ASHARED_SHFT                                0xb
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_AREDIRECT_BMSK                            0x400
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_AREDIRECT_SHFT                              0xa
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_AOOO_BMSK                                 0x200
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_AOOO_SHFT                                   0x9
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_AINNERSHARED_BMSK                         0x100
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_AINNERSHARED_SHFT                           0x8
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_OVERRIDE_APORTMREL_BMSK                    0x80
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_OVERRIDE_APORTMREL_SHFT                     0x7
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_OVERRIDE_AREQPRIORITY_BMSK                 0x40
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_OVERRIDE_AREQPRIORITY_SHFT                  0x6
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_OVERRIDE_AMEMTYPE_BMSK                     0x20
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_OVERRIDE_AMEMTYPE_SHFT                      0x5
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_OVERRIDE_ATRANSIENT_BMSK                   0x10
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_OVERRIDE_ATRANSIENT_SHFT                    0x4
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_OVERRIDE_ASHARED_BMSK                       0x8
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_OVERRIDE_ASHARED_SHFT                       0x3
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_OVERRIDE_AREDIRECT_BMSK                     0x4
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_OVERRIDE_AREDIRECT_SHFT                     0x2
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_OVERRIDE_AOOO_BMSK                          0x2
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_OVERRIDE_AOOO_SHFT                          0x1
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_OVERRIDE_AINNERSHARED_BMSK                  0x1
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_0_OVERRIDE_AINNERSHARED_SHFT                  0x0

#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_1_ADDR                                 (BIMC_M_APP_MPORT_REG_BASE      + 0x00000254)
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_1_RMSK                                      0x101
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_1_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_1_ADDR, HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_1_RMSK)
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_1_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_1_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_1_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_1_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_1_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_1_IN)
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_1_AFULL_BMSK                                0x100
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_1_AFULL_SHFT                                  0x8
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_1_OVERRIDE_AFULL_BMSK                         0x1
#define HWIO_BIMC_M_APP_MPORT_WRITE_COMMAND_OVERRIDE_1_OVERRIDE_AFULL_SHFT                         0x0

#define HWIO_BIMC_M_APP_MPORT_PIPE0_GATHERING_ADDR                                          (BIMC_M_APP_MPORT_REG_BASE      + 0x00000260)
#define HWIO_BIMC_M_APP_MPORT_PIPE0_GATHERING_RMSK                                          0x800f000f
#define HWIO_BIMC_M_APP_MPORT_PIPE0_GATHERING_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_PIPE0_GATHERING_ADDR, HWIO_BIMC_M_APP_MPORT_PIPE0_GATHERING_RMSK)
#define HWIO_BIMC_M_APP_MPORT_PIPE0_GATHERING_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_PIPE0_GATHERING_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_PIPE0_GATHERING_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_PIPE0_GATHERING_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_PIPE0_GATHERING_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_PIPE0_GATHERING_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_PIPE0_GATHERING_IN)
#define HWIO_BIMC_M_APP_MPORT_PIPE0_GATHERING_RFU_BMSK                                      0x80000000
#define HWIO_BIMC_M_APP_MPORT_PIPE0_GATHERING_RFU_SHFT                                            0x1f
#define HWIO_BIMC_M_APP_MPORT_PIPE0_GATHERING_WR_GATHER_BEATS_BMSK                             0xf0000
#define HWIO_BIMC_M_APP_MPORT_PIPE0_GATHERING_WR_GATHER_BEATS_SHFT                                0x10
#define HWIO_BIMC_M_APP_MPORT_PIPE0_GATHERING_RD_GATHER_BEATS_BMSK                                 0xf
#define HWIO_BIMC_M_APP_MPORT_PIPE0_GATHERING_RD_GATHER_BEATS_SHFT                                 0x0

#define HWIO_BIMC_M_APP_MPORT_PIPE1_GATHERING_ADDR                                          (BIMC_M_APP_MPORT_REG_BASE      + 0x00000264)
#define HWIO_BIMC_M_APP_MPORT_PIPE1_GATHERING_RMSK                                          0x800f000f
#define HWIO_BIMC_M_APP_MPORT_PIPE1_GATHERING_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_PIPE1_GATHERING_ADDR, HWIO_BIMC_M_APP_MPORT_PIPE1_GATHERING_RMSK)
#define HWIO_BIMC_M_APP_MPORT_PIPE1_GATHERING_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_PIPE1_GATHERING_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_PIPE1_GATHERING_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_PIPE1_GATHERING_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_PIPE1_GATHERING_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_PIPE1_GATHERING_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_PIPE1_GATHERING_IN)
#define HWIO_BIMC_M_APP_MPORT_PIPE1_GATHERING_RFU_BMSK                                      0x80000000
#define HWIO_BIMC_M_APP_MPORT_PIPE1_GATHERING_RFU_SHFT                                            0x1f
#define HWIO_BIMC_M_APP_MPORT_PIPE1_GATHERING_WR_GATHER_BEATS_BMSK                             0xf0000
#define HWIO_BIMC_M_APP_MPORT_PIPE1_GATHERING_WR_GATHER_BEATS_SHFT                                0x10
#define HWIO_BIMC_M_APP_MPORT_PIPE1_GATHERING_RD_GATHER_BEATS_BMSK                                 0xf
#define HWIO_BIMC_M_APP_MPORT_PIPE1_GATHERING_RD_GATHER_BEATS_SHFT                                 0x0

#define HWIO_BIMC_M_APP_MPORT_PIPE2_GATHERING_ADDR                                          (BIMC_M_APP_MPORT_REG_BASE      + 0x00000268)
#define HWIO_BIMC_M_APP_MPORT_PIPE2_GATHERING_RMSK                                          0x800f000f
#define HWIO_BIMC_M_APP_MPORT_PIPE2_GATHERING_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_PIPE2_GATHERING_ADDR, HWIO_BIMC_M_APP_MPORT_PIPE2_GATHERING_RMSK)
#define HWIO_BIMC_M_APP_MPORT_PIPE2_GATHERING_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_PIPE2_GATHERING_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_PIPE2_GATHERING_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_PIPE2_GATHERING_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_PIPE2_GATHERING_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_PIPE2_GATHERING_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_PIPE2_GATHERING_IN)
#define HWIO_BIMC_M_APP_MPORT_PIPE2_GATHERING_RFU_BMSK                                      0x80000000
#define HWIO_BIMC_M_APP_MPORT_PIPE2_GATHERING_RFU_SHFT                                            0x1f
#define HWIO_BIMC_M_APP_MPORT_PIPE2_GATHERING_WR_GATHER_BEATS_BMSK                             0xf0000
#define HWIO_BIMC_M_APP_MPORT_PIPE2_GATHERING_WR_GATHER_BEATS_SHFT                                0x10
#define HWIO_BIMC_M_APP_MPORT_PIPE2_GATHERING_RD_GATHER_BEATS_BMSK                                 0xf
#define HWIO_BIMC_M_APP_MPORT_PIPE2_GATHERING_RD_GATHER_BEATS_SHFT                                 0x0

#define HWIO_BIMC_M_APP_MPORT_RD_TRACKING_INDEX_ADDR                                        (BIMC_M_APP_MPORT_REG_BASE      + 0x00000270)
#define HWIO_BIMC_M_APP_MPORT_RD_TRACKING_INDEX_RMSK                                        0xc00fffff
#define HWIO_BIMC_M_APP_MPORT_RD_TRACKING_INDEX_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_RD_TRACKING_INDEX_ADDR, HWIO_BIMC_M_APP_MPORT_RD_TRACKING_INDEX_RMSK)
#define HWIO_BIMC_M_APP_MPORT_RD_TRACKING_INDEX_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_RD_TRACKING_INDEX_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_RD_TRACKING_INDEX_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_RD_TRACKING_INDEX_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_RD_TRACKING_INDEX_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_RD_TRACKING_INDEX_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_RD_TRACKING_INDEX_IN)
#define HWIO_BIMC_M_APP_MPORT_RD_TRACKING_INDEX_HASH_SELECT_BMSK                            0xc0000000
#define HWIO_BIMC_M_APP_MPORT_RD_TRACKING_INDEX_HASH_SELECT_SHFT                                  0x1e
#define HWIO_BIMC_M_APP_MPORT_RD_TRACKING_INDEX_INDEX_BMSK                                     0xfffff
#define HWIO_BIMC_M_APP_MPORT_RD_TRACKING_INDEX_INDEX_SHFT                                         0x0

#define HWIO_BIMC_M_APP_MPORT_WR_TRACKING_INDEX_ADDR                                        (BIMC_M_APP_MPORT_REG_BASE      + 0x00000274)
#define HWIO_BIMC_M_APP_MPORT_WR_TRACKING_INDEX_RMSK                                        0xc00fffff
#define HWIO_BIMC_M_APP_MPORT_WR_TRACKING_INDEX_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_WR_TRACKING_INDEX_ADDR, HWIO_BIMC_M_APP_MPORT_WR_TRACKING_INDEX_RMSK)
#define HWIO_BIMC_M_APP_MPORT_WR_TRACKING_INDEX_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_WR_TRACKING_INDEX_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_WR_TRACKING_INDEX_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_WR_TRACKING_INDEX_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_WR_TRACKING_INDEX_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_WR_TRACKING_INDEX_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_WR_TRACKING_INDEX_IN)
#define HWIO_BIMC_M_APP_MPORT_WR_TRACKING_INDEX_HASH_SELECT_BMSK                            0xc0000000
#define HWIO_BIMC_M_APP_MPORT_WR_TRACKING_INDEX_HASH_SELECT_SHFT                                  0x1e
#define HWIO_BIMC_M_APP_MPORT_WR_TRACKING_INDEX_INDEX_BMSK                                     0xfffff
#define HWIO_BIMC_M_APP_MPORT_WR_TRACKING_INDEX_INDEX_SHFT                                         0x0

#define HWIO_BIMC_M_APP_MPORT_BAMON_ADDR                                                    (BIMC_M_APP_MPORT_REG_BASE      + 0x00000278)
#define HWIO_BIMC_M_APP_MPORT_BAMON_RMSK                                                         0x77f
#define HWIO_BIMC_M_APP_MPORT_BAMON_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BAMON_ADDR, HWIO_BIMC_M_APP_MPORT_BAMON_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BAMON_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BAMON_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BAMON_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BAMON_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BAMON_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BAMON_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BAMON_IN)
#define HWIO_BIMC_M_APP_MPORT_BAMON_SAMPLING_DURATION_BMSK                                       0x700
#define HWIO_BIMC_M_APP_MPORT_BAMON_SAMPLING_DURATION_SHFT                                         0x8
#define HWIO_BIMC_M_APP_MPORT_BAMON_EVENT_SEL_BMSK                                                0x7f
#define HWIO_BIMC_M_APP_MPORT_BAMON_EVENT_SEL_SHFT                                                 0x0

#define HWIO_BIMC_M_APP_MPORT_BWMON_ENABLE_ADDR                                             (BIMC_M_APP_MPORT_REG_BASE      + 0x00000280)
#define HWIO_BIMC_M_APP_MPORT_BWMON_ENABLE_RMSK                                             0x801f0011
#define HWIO_BIMC_M_APP_MPORT_BWMON_ENABLE_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BWMON_ENABLE_ADDR, HWIO_BIMC_M_APP_MPORT_BWMON_ENABLE_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BWMON_ENABLE_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BWMON_ENABLE_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BWMON_ENABLE_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BWMON_ENABLE_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BWMON_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BWMON_ENABLE_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BWMON_ENABLE_IN)
#define HWIO_BIMC_M_APP_MPORT_BWMON_ENABLE_CLEAR_ON_INTR_BMSK                               0x80000000
#define HWIO_BIMC_M_APP_MPORT_BWMON_ENABLE_CLEAR_ON_INTR_SHFT                                     0x1f
#define HWIO_BIMC_M_APP_MPORT_BWMON_ENABLE_THROTTLE_OFFSET_BMSK                               0x1f0000
#define HWIO_BIMC_M_APP_MPORT_BWMON_ENABLE_THROTTLE_OFFSET_SHFT                                   0x10
#define HWIO_BIMC_M_APP_MPORT_BWMON_ENABLE_SCALING_FACTOR_BMSK                                    0x10
#define HWIO_BIMC_M_APP_MPORT_BWMON_ENABLE_SCALING_FACTOR_SHFT                                     0x4
#define HWIO_BIMC_M_APP_MPORT_BWMON_ENABLE_ENABLE_BMSK                                             0x1
#define HWIO_BIMC_M_APP_MPORT_BWMON_ENABLE_ENABLE_SHFT                                             0x0

#define HWIO_BIMC_M_APP_MPORT_BWMON_CLEAR_ADDR                                              (BIMC_M_APP_MPORT_REG_BASE      + 0x00000284)
#define HWIO_BIMC_M_APP_MPORT_BWMON_CLEAR_RMSK                                                     0x1
#define HWIO_BIMC_M_APP_MPORT_BWMON_CLEAR_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BWMON_CLEAR_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BWMON_CLEAR_CLEAR_BMSK                                               0x1
#define HWIO_BIMC_M_APP_MPORT_BWMON_CLEAR_CLEAR_SHFT                                               0x0

#define HWIO_BIMC_M_APP_MPORT_BWMON_BYTE_COUNT_ADDR                                         (BIMC_M_APP_MPORT_REG_BASE      + 0x00000288)
#define HWIO_BIMC_M_APP_MPORT_BWMON_BYTE_COUNT_RMSK                                         0xffffffff
#define HWIO_BIMC_M_APP_MPORT_BWMON_BYTE_COUNT_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BWMON_BYTE_COUNT_ADDR, HWIO_BIMC_M_APP_MPORT_BWMON_BYTE_COUNT_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BWMON_BYTE_COUNT_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BWMON_BYTE_COUNT_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BWMON_BYTE_COUNT_BYTE_COUNT_BMSK                              0xffffffff
#define HWIO_BIMC_M_APP_MPORT_BWMON_BYTE_COUNT_BYTE_COUNT_SHFT                                     0x0

#define HWIO_BIMC_M_APP_MPORT_BWMON_THRESHOLD_ADDR                                          (BIMC_M_APP_MPORT_REG_BASE      + 0x00000290)
#define HWIO_BIMC_M_APP_MPORT_BWMON_THRESHOLD_RMSK                                          0xffffffff
#define HWIO_BIMC_M_APP_MPORT_BWMON_THRESHOLD_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BWMON_THRESHOLD_ADDR, HWIO_BIMC_M_APP_MPORT_BWMON_THRESHOLD_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BWMON_THRESHOLD_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BWMON_THRESHOLD_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BWMON_THRESHOLD_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BWMON_THRESHOLD_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BWMON_THRESHOLD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BWMON_THRESHOLD_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BWMON_THRESHOLD_IN)
#define HWIO_BIMC_M_APP_MPORT_BWMON_THRESHOLD_THRESHOLD_BMSK                                0xffffffff
#define HWIO_BIMC_M_APP_MPORT_BWMON_THRESHOLD_THRESHOLD_SHFT                                       0x0

#define HWIO_BIMC_M_APP_MPORT_BWMON_MID_MASK_ADDR                                           (BIMC_M_APP_MPORT_REG_BASE      + 0x00000298)
#define HWIO_BIMC_M_APP_MPORT_BWMON_MID_MASK_RMSK                                               0xffff
#define HWIO_BIMC_M_APP_MPORT_BWMON_MID_MASK_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BWMON_MID_MASK_ADDR, HWIO_BIMC_M_APP_MPORT_BWMON_MID_MASK_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BWMON_MID_MASK_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BWMON_MID_MASK_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BWMON_MID_MASK_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BWMON_MID_MASK_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BWMON_MID_MASK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BWMON_MID_MASK_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BWMON_MID_MASK_IN)
#define HWIO_BIMC_M_APP_MPORT_BWMON_MID_MASK_MASK_BMSK                                          0xffff
#define HWIO_BIMC_M_APP_MPORT_BWMON_MID_MASK_MASK_SHFT                                             0x0

#define HWIO_BIMC_M_APP_MPORT_BWMON_MID_MATCH_ADDR                                          (BIMC_M_APP_MPORT_REG_BASE      + 0x0000029c)
#define HWIO_BIMC_M_APP_MPORT_BWMON_MID_MATCH_RMSK                                              0xffff
#define HWIO_BIMC_M_APP_MPORT_BWMON_MID_MATCH_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BWMON_MID_MATCH_ADDR, HWIO_BIMC_M_APP_MPORT_BWMON_MID_MATCH_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BWMON_MID_MATCH_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BWMON_MID_MATCH_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BWMON_MID_MATCH_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BWMON_MID_MATCH_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BWMON_MID_MATCH_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BWMON_MID_MATCH_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BWMON_MID_MATCH_IN)
#define HWIO_BIMC_M_APP_MPORT_BWMON_MID_MATCH_MATCH_BMSK                                        0xffff
#define HWIO_BIMC_M_APP_MPORT_BWMON_MID_MATCH_MATCH_SHFT                                           0x0

#define HWIO_BIMC_M_APP_MPORT_BWMON2_ENABLE_ADDR                                            (BIMC_M_APP_MPORT_REG_BASE      + 0x000002a0)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ENABLE_RMSK                                            0x801f0001
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ENABLE_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BWMON2_ENABLE_ADDR, HWIO_BIMC_M_APP_MPORT_BWMON2_ENABLE_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ENABLE_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BWMON2_ENABLE_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ENABLE_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BWMON2_ENABLE_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BWMON2_ENABLE_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BWMON2_ENABLE_IN)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ENABLE_EARLY_INTR_EN_BMSK                              0x80000000
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ENABLE_EARLY_INTR_EN_SHFT                                    0x1f
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ENABLE_THROTTLE_OFFSET_BMSK                              0x1f0000
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ENABLE_THROTTLE_OFFSET_SHFT                                  0x10
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ENABLE_ENABLE_BMSK                                            0x1
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ENABLE_ENABLE_SHFT                                            0x0

#define HWIO_BIMC_M_APP_MPORT_BWMON2_CLEAR_ADDR                                             (BIMC_M_APP_MPORT_REG_BASE      + 0x000002a4)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_CLEAR_RMSK                                                    0x3
#define HWIO_BIMC_M_APP_MPORT_BWMON2_CLEAR_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BWMON2_CLEAR_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_CLEAR_CLEAR_ALL_BMSK                                          0x2
#define HWIO_BIMC_M_APP_MPORT_BWMON2_CLEAR_CLEAR_ALL_SHFT                                          0x1
#define HWIO_BIMC_M_APP_MPORT_BWMON2_CLEAR_CLEAR_BMSK                                              0x1
#define HWIO_BIMC_M_APP_MPORT_BWMON2_CLEAR_CLEAR_SHFT                                              0x0

#define HWIO_BIMC_M_APP_MPORT_BWMON2_SAMPLING_WINDOW_ADDR                                   (BIMC_M_APP_MPORT_REG_BASE      + 0x000002a8)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_SAMPLING_WINDOW_RMSK                                      0xfffff
#define HWIO_BIMC_M_APP_MPORT_BWMON2_SAMPLING_WINDOW_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BWMON2_SAMPLING_WINDOW_ADDR, HWIO_BIMC_M_APP_MPORT_BWMON2_SAMPLING_WINDOW_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_SAMPLING_WINDOW_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BWMON2_SAMPLING_WINDOW_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_SAMPLING_WINDOW_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BWMON2_SAMPLING_WINDOW_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_SAMPLING_WINDOW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BWMON2_SAMPLING_WINDOW_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BWMON2_SAMPLING_WINDOW_IN)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_SAMPLING_WINDOW_REG_BMSK                                  0xfffff
#define HWIO_BIMC_M_APP_MPORT_BWMON2_SAMPLING_WINDOW_REG_SHFT                                      0x0

#define HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_ADDR                         (BIMC_M_APP_MPORT_REG_BASE      + 0x000002ac)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_RMSK                              0xfff
#define HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_ADDR, HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_IN)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_REG_BMSK                          0xfff
#define HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_REG_SHFT                            0x0

#define HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_ADDR                       (BIMC_M_APP_MPORT_REG_BASE      + 0x000002b0)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_RMSK                            0xfff
#define HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_ADDR, HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_IN)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_REG_BMSK                        0xfff
#define HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_REG_SHFT                          0x0

#define HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_LOW_ADDR                          (BIMC_M_APP_MPORT_REG_BASE      + 0x000002b4)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_LOW_RMSK                               0xfff
#define HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_LOW_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_LOW_ADDR, HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_LOW_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_LOW_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_LOW_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_LOW_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_LOW_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_LOW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_LOW_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_LOW_IN)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_LOW_REG_BMSK                           0xfff
#define HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_THRESHOLD_LOW_REG_SHFT                             0x0

#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_ACTIONS_ADDR                                      (BIMC_M_APP_MPORT_REG_BASE      + 0x000002b8)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_ACTIONS_RMSK                                      0xffffffff
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_ACTIONS_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_ACTIONS_ADDR, HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_ACTIONS_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_ACTIONS_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_ACTIONS_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_ACTIONS_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_ACTIONS_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_ACTIONS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_ACTIONS_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_ACTIONS_IN)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_ACTIONS_ZONE3_BMSK                                0xff000000
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_ACTIONS_ZONE3_SHFT                                      0x18
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_ACTIONS_ZONE2_BMSK                                  0xff0000
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_ACTIONS_ZONE2_SHFT                                      0x10
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_ACTIONS_ZONE1_BMSK                                    0xff00
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_ACTIONS_ZONE1_SHFT                                       0x8
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_ACTIONS_ZONE0_BMSK                                      0xff
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_ACTIONS_ZONE0_SHFT                                       0x0

#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_COUNT_THRESHOLD_ADDR                              (BIMC_M_APP_MPORT_REG_BASE      + 0x000002bc)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_COUNT_THRESHOLD_RMSK                              0xffffffff
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_COUNT_THRESHOLD_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_COUNT_THRESHOLD_ADDR, HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_COUNT_THRESHOLD_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_COUNT_THRESHOLD_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_COUNT_THRESHOLD_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_COUNT_THRESHOLD_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_COUNT_THRESHOLD_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_COUNT_THRESHOLD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_COUNT_THRESHOLD_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_COUNT_THRESHOLD_IN)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_COUNT_THRESHOLD_ZONE3_BMSK                        0xff000000
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_COUNT_THRESHOLD_ZONE3_SHFT                              0x18
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_COUNT_THRESHOLD_ZONE2_BMSK                          0xff0000
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_COUNT_THRESHOLD_ZONE2_SHFT                              0x10
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_COUNT_THRESHOLD_ZONE1_BMSK                            0xff00
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_COUNT_THRESHOLD_ZONE1_SHFT                               0x8
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_COUNT_THRESHOLD_ZONE0_BMSK                              0xff
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_COUNT_THRESHOLD_ZONE0_SHFT                               0x0

#define HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_ADDR                                        (BIMC_M_APP_MPORT_REG_BASE      + 0x000002d0)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_RMSK                                        0x30000fff
#define HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_ADDR, HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_CURRENT_ZONE_BMSK                           0x30000000
#define HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_CURRENT_ZONE_SHFT                                 0x1c
#define HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_CURRENT_BYTE_COUNT_BMSK                          0xfff
#define HWIO_BIMC_M_APP_MPORT_BWMON2_BYTE_COUNT_CURRENT_BYTE_COUNT_SHFT                            0x0

#define HWIO_BIMC_M_APP_MPORT_BWMON2_WINDOW_TIMER_ADDR                                      (BIMC_M_APP_MPORT_REG_BASE      + 0x000002d4)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_WINDOW_TIMER_RMSK                                         0xfffff
#define HWIO_BIMC_M_APP_MPORT_BWMON2_WINDOW_TIMER_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BWMON2_WINDOW_TIMER_ADDR, HWIO_BIMC_M_APP_MPORT_BWMON2_WINDOW_TIMER_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_WINDOW_TIMER_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BWMON2_WINDOW_TIMER_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_WINDOW_TIMER_CURRENT_WINDOW_TIMER_BMSK                    0xfffff
#define HWIO_BIMC_M_APP_MPORT_BWMON2_WINDOW_TIMER_CURRENT_WINDOW_TIMER_SHFT                        0x0

#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_COUNT_ADDR                                        (BIMC_M_APP_MPORT_REG_BASE      + 0x000002d8)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_COUNT_RMSK                                        0xffffffff
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_COUNT_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_COUNT_ADDR, HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_COUNT_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_COUNT_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_COUNT_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_COUNT_ZONE3_BMSK                                  0xff000000
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_COUNT_ZONE3_SHFT                                        0x18
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_COUNT_ZONE2_BMSK                                    0xff0000
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_COUNT_ZONE2_SHFT                                        0x10
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_COUNT_ZONE1_BMSK                                      0xff00
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_COUNT_ZONE1_SHFT                                         0x8
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_COUNT_ZONE0_BMSK                                        0xff
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONE_COUNT_ZONE0_SHFT                                         0x0

#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONEn_MAX_BYTE_COUNT_ADDR(n)                           (BIMC_M_APP_MPORT_REG_BASE      + 0x000002e0 + 0x4 * (n))
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONEn_MAX_BYTE_COUNT_RMSK                                   0xfff
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONEn_MAX_BYTE_COUNT_MAXn                                       3
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONEn_MAX_BYTE_COUNT_INI(n)        \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BWMON2_ZONEn_MAX_BYTE_COUNT_ADDR(n), HWIO_BIMC_M_APP_MPORT_BWMON2_ZONEn_MAX_BYTE_COUNT_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONEn_MAX_BYTE_COUNT_INMI(n,mask)    \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BWMON2_ZONEn_MAX_BYTE_COUNT_ADDR(n), mask)
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONEn_MAX_BYTE_COUNT_REG_BMSK                               0xfff
#define HWIO_BIMC_M_APP_MPORT_BWMON2_ZONEn_MAX_BYTE_COUNT_REG_SHFT                                 0x0

#define HWIO_BIMC_M_APP_MPORT_BKE_ENABLE_ADDR                                               (BIMC_M_APP_MPORT_REG_BASE      + 0x00000300)
#define HWIO_BIMC_M_APP_MPORT_BKE_ENABLE_RMSK                                               0xff0f0011
#define HWIO_BIMC_M_APP_MPORT_BKE_ENABLE_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE_ENABLE_ADDR, HWIO_BIMC_M_APP_MPORT_BKE_ENABLE_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE_ENABLE_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE_ENABLE_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE_ENABLE_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE_ENABLE_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE_ENABLE_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE_ENABLE_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE_ENABLE_QOS_POLICY_SEL_BMSK                                0xff000000
#define HWIO_BIMC_M_APP_MPORT_BKE_ENABLE_QOS_POLICY_SEL_SHFT                                      0x18
#define HWIO_BIMC_M_APP_MPORT_BKE_ENABLE_QOS_POLICY_SYNC_RATE_BMSK                             0xf0000
#define HWIO_BIMC_M_APP_MPORT_BKE_ENABLE_QOS_POLICY_SYNC_RATE_SHFT                                0x10
#define HWIO_BIMC_M_APP_MPORT_BKE_ENABLE_SCALING_FACTOR_BMSK                                      0x10
#define HWIO_BIMC_M_APP_MPORT_BKE_ENABLE_SCALING_FACTOR_SHFT                                       0x4
#define HWIO_BIMC_M_APP_MPORT_BKE_ENABLE_ENABLE_BMSK                                               0x1
#define HWIO_BIMC_M_APP_MPORT_BKE_ENABLE_ENABLE_SHFT                                               0x0

#define HWIO_BIMC_M_APP_MPORT_BKE_GRANT_PERIOD_ADDR                                         (BIMC_M_APP_MPORT_REG_BASE      + 0x00000304)
#define HWIO_BIMC_M_APP_MPORT_BKE_GRANT_PERIOD_RMSK                                              0x3ff
#define HWIO_BIMC_M_APP_MPORT_BKE_GRANT_PERIOD_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE_GRANT_PERIOD_ADDR, HWIO_BIMC_M_APP_MPORT_BKE_GRANT_PERIOD_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE_GRANT_PERIOD_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE_GRANT_PERIOD_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE_GRANT_PERIOD_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE_GRANT_PERIOD_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE_GRANT_PERIOD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE_GRANT_PERIOD_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE_GRANT_PERIOD_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE_GRANT_PERIOD_GRANT_PERIOD_BMSK                                 0x3ff
#define HWIO_BIMC_M_APP_MPORT_BKE_GRANT_PERIOD_GRANT_PERIOD_SHFT                                   0x0

#define HWIO_BIMC_M_APP_MPORT_BKE_GRANT_COUNT_ADDR                                          (BIMC_M_APP_MPORT_REG_BASE      + 0x00000308)
#define HWIO_BIMC_M_APP_MPORT_BKE_GRANT_COUNT_RMSK                                              0xffff
#define HWIO_BIMC_M_APP_MPORT_BKE_GRANT_COUNT_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE_GRANT_COUNT_ADDR, HWIO_BIMC_M_APP_MPORT_BKE_GRANT_COUNT_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE_GRANT_COUNT_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE_GRANT_COUNT_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE_GRANT_COUNT_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE_GRANT_COUNT_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE_GRANT_COUNT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE_GRANT_COUNT_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE_GRANT_COUNT_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE_GRANT_COUNT_GRANT_COUNT_BMSK                                  0xffff
#define HWIO_BIMC_M_APP_MPORT_BKE_GRANT_COUNT_GRANT_COUNT_SHFT                                     0x0

#define HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_HIGH_ADDR                                       (BIMC_M_APP_MPORT_REG_BASE      + 0x00000320)
#define HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_HIGH_RMSK                                           0xffff
#define HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_HIGH_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_HIGH_ADDR, HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_HIGH_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_HIGH_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_HIGH_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_HIGH_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_HIGH_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_HIGH_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_HIGH_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_HIGH_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_HIGH_THRESHOLD_BMSK                                 0xffff
#define HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_HIGH_THRESHOLD_SHFT                                    0x0

#define HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_MEDIUM_ADDR                                     (BIMC_M_APP_MPORT_REG_BASE      + 0x00000324)
#define HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_MEDIUM_RMSK                                         0xffff
#define HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_MEDIUM_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_MEDIUM_ADDR, HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_MEDIUM_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_MEDIUM_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_MEDIUM_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_MEDIUM_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_MEDIUM_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_MEDIUM_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_MEDIUM_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_MEDIUM_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_MEDIUM_THRESHOLD_BMSK                               0xffff
#define HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_MEDIUM_THRESHOLD_SHFT                                  0x0

#define HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_LOW_ADDR                                        (BIMC_M_APP_MPORT_REG_BASE      + 0x00000328)
#define HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_LOW_RMSK                                            0xffff
#define HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_LOW_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_LOW_ADDR, HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_LOW_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_LOW_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_LOW_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_LOW_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_LOW_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_LOW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_LOW_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_LOW_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_LOW_THRESHOLD_BMSK                                  0xffff
#define HWIO_BIMC_M_APP_MPORT_BKE_THRESHOLD_LOW_THRESHOLD_SHFT                                     0x0

#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_0_ADDR                                             (BIMC_M_APP_MPORT_REG_BASE      + 0x00000340)
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_0_RMSK                                             0x80000303
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_0_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_0_ADDR, HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_0_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_0_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_0_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_0_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_0_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_0_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_0_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_0_LIMIT_COMMANDS_BMSK                              0x80000000
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_0_LIMIT_COMMANDS_SHFT                                    0x1f
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_0_AREQPRIORITY_BMSK                                     0x300
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_0_AREQPRIORITY_SHFT                                       0x8
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_0_PRIORITYLVL_BMSK                                        0x3
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_0_PRIORITYLVL_SHFT                                        0x0

#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_1_ADDR                                             (BIMC_M_APP_MPORT_REG_BASE      + 0x00000344)
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_1_RMSK                                             0x80000303
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_1_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_1_ADDR, HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_1_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_1_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_1_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_1_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_1_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_1_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_1_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_1_LIMIT_COMMANDS_BMSK                              0x80000000
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_1_LIMIT_COMMANDS_SHFT                                    0x1f
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_1_AREQPRIORITY_BMSK                                     0x300
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_1_AREQPRIORITY_SHFT                                       0x8
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_1_PRIORITYLVL_BMSK                                        0x3
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_1_PRIORITYLVL_SHFT                                        0x0

#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_2_ADDR                                             (BIMC_M_APP_MPORT_REG_BASE      + 0x00000348)
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_2_RMSK                                             0x80000303
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_2_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_2_ADDR, HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_2_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_2_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_2_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_2_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_2_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_2_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_2_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_2_LIMIT_COMMANDS_BMSK                              0x80000000
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_2_LIMIT_COMMANDS_SHFT                                    0x1f
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_2_AREQPRIORITY_BMSK                                     0x300
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_2_AREQPRIORITY_SHFT                                       0x8
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_2_PRIORITYLVL_BMSK                                        0x3
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_2_PRIORITYLVL_SHFT                                        0x0

#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_3_ADDR                                             (BIMC_M_APP_MPORT_REG_BASE      + 0x0000034c)
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_3_RMSK                                                  0x303
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_3_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_3_ADDR, HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_3_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_3_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_3_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_3_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_3_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_3_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_3_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_3_AREQPRIORITY_BMSK                                     0x300
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_3_AREQPRIORITY_SHFT                                       0x8
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_3_PRIORITYLVL_BMSK                                        0x3
#define HWIO_BIMC_M_APP_MPORT_BKE_HEALTH_3_PRIORITYLVL_SHFT                                        0x0

#define HWIO_BIMC_M_APP_MPORT_STATUS_0A_ADDR                                                (BIMC_M_APP_MPORT_REG_BASE      + 0x00000400)
#define HWIO_BIMC_M_APP_MPORT_STATUS_0A_RMSK                                                  0xff00ff
#define HWIO_BIMC_M_APP_MPORT_STATUS_0A_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_0A_ADDR, HWIO_BIMC_M_APP_MPORT_STATUS_0A_RMSK)
#define HWIO_BIMC_M_APP_MPORT_STATUS_0A_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_0A_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_STATUS_0A_FRONTEND_WR_PENDING_BMSK                              0xff0000
#define HWIO_BIMC_M_APP_MPORT_STATUS_0A_FRONTEND_WR_PENDING_SHFT                                  0x10
#define HWIO_BIMC_M_APP_MPORT_STATUS_0A_FRONTEND_RD_PENDING_BMSK                                  0xff
#define HWIO_BIMC_M_APP_MPORT_STATUS_0A_FRONTEND_RD_PENDING_SHFT                                   0x0

#define HWIO_BIMC_M_APP_MPORT_STATUS_0B_ADDR                                                (BIMC_M_APP_MPORT_REG_BASE      + 0x00000404)
#define HWIO_BIMC_M_APP_MPORT_STATUS_0B_RMSK                                                    0xffff
#define HWIO_BIMC_M_APP_MPORT_STATUS_0B_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_0B_ADDR, HWIO_BIMC_M_APP_MPORT_STATUS_0B_RMSK)
#define HWIO_BIMC_M_APP_MPORT_STATUS_0B_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_0B_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_STATUS_0B_FRONTEND_COMMAND_BLOCK_BMSK                             0xffff
#define HWIO_BIMC_M_APP_MPORT_STATUS_0B_FRONTEND_COMMAND_BLOCK_SHFT                                0x0

#define HWIO_BIMC_M_APP_MPORT_STATUS_1A_ADDR                                                (BIMC_M_APP_MPORT_REG_BASE      + 0x00000410)
#define HWIO_BIMC_M_APP_MPORT_STATUS_1A_RMSK                                                   0xfffff
#define HWIO_BIMC_M_APP_MPORT_STATUS_1A_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_1A_ADDR, HWIO_BIMC_M_APP_MPORT_STATUS_1A_RMSK)
#define HWIO_BIMC_M_APP_MPORT_STATUS_1A_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_1A_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_STATUS_1A_FRONTEND_VALID_READY_BMSK                              0xfffff
#define HWIO_BIMC_M_APP_MPORT_STATUS_1A_FRONTEND_VALID_READY_SHFT                                  0x0

#define HWIO_BIMC_M_APP_MPORT_STATUS_2A_ADDR                                                (BIMC_M_APP_MPORT_REG_BASE      + 0x00000420)
#define HWIO_BIMC_M_APP_MPORT_STATUS_2A_RMSK                                                  0xff00ff
#define HWIO_BIMC_M_APP_MPORT_STATUS_2A_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_2A_ADDR, HWIO_BIMC_M_APP_MPORT_STATUS_2A_RMSK)
#define HWIO_BIMC_M_APP_MPORT_STATUS_2A_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_2A_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_STATUS_2A_PIPE0_WR_PENDING_PRE_BUF_BMSK                         0xff0000
#define HWIO_BIMC_M_APP_MPORT_STATUS_2A_PIPE0_WR_PENDING_PRE_BUF_SHFT                             0x10
#define HWIO_BIMC_M_APP_MPORT_STATUS_2A_PIPE0_RD_PENDING_PRE_BUF_BMSK                             0xff
#define HWIO_BIMC_M_APP_MPORT_STATUS_2A_PIPE0_RD_PENDING_PRE_BUF_SHFT                              0x0

#define HWIO_BIMC_M_APP_MPORT_STATUS_2B_ADDR                                                (BIMC_M_APP_MPORT_REG_BASE      + 0x00000424)
#define HWIO_BIMC_M_APP_MPORT_STATUS_2B_RMSK                                                  0xff00ff
#define HWIO_BIMC_M_APP_MPORT_STATUS_2B_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_2B_ADDR, HWIO_BIMC_M_APP_MPORT_STATUS_2B_RMSK)
#define HWIO_BIMC_M_APP_MPORT_STATUS_2B_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_2B_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_STATUS_2B_PIPE0_WR_PENDING_POST_BUF_BMSK                        0xff0000
#define HWIO_BIMC_M_APP_MPORT_STATUS_2B_PIPE0_WR_PENDING_POST_BUF_SHFT                            0x10
#define HWIO_BIMC_M_APP_MPORT_STATUS_2B_PIPE0_RD_PENDING_POST_BUF_BMSK                            0xff
#define HWIO_BIMC_M_APP_MPORT_STATUS_2B_PIPE0_RD_PENDING_POST_BUF_SHFT                             0x0

#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_ADDR                                                (BIMC_M_APP_MPORT_REG_BASE      + 0x00000430)
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_RMSK                                                0xff333333
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_3A_ADDR, HWIO_BIMC_M_APP_MPORT_STATUS_3A_RMSK)
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_3A_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_RCB_DATA_RD_FULL_BMSK                         0x80000000
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_RCB_DATA_RD_FULL_SHFT                               0x1f
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_RCB_DATA_RD_EMPTY_BMSK                        0x40000000
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_RCB_DATA_RD_EMPTY_SHFT                              0x1e
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_RCB_CTRL_RD_FULL_BMSK                         0x20000000
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_RCB_CTRL_RD_FULL_SHFT                               0x1d
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_RCB_CTRL_RD_EMPTY_BMSK                        0x10000000
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_RCB_CTRL_RD_EMPTY_SHFT                              0x1c
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_RCB_DATA_WR_FULL_BMSK                          0x8000000
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_RCB_DATA_WR_FULL_SHFT                               0x1b
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_RCB_DATA_WR_EMPTY_BMSK                         0x4000000
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_RCB_DATA_WR_EMPTY_SHFT                              0x1a
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_RCB_CTRL_WR_FULL_BMSK                          0x2000000
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_RCB_CTRL_WR_FULL_SHFT                               0x19
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_RCB_CTRL_WR_EMPTY_BMSK                         0x1000000
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_RCB_CTRL_WR_EMPTY_SHFT                              0x18
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_BCB_RD_FULL_BMSK                                0x200000
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_BCB_RD_FULL_SHFT                                    0x15
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_BCB_RD_EMPTY_BMSK                               0x100000
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_BCB_RD_EMPTY_SHFT                                   0x14
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_BCB_WR_FULL_BMSK                                 0x20000
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_BCB_WR_FULL_SHFT                                    0x11
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_BCB_WR_EMPTY_BMSK                                0x10000
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_BCB_WR_EMPTY_SHFT                                   0x10
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_WCB_RD_FULL_BMSK                                  0x2000
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_WCB_RD_FULL_SHFT                                     0xd
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_WCB_RD_EMPTY_BMSK                                 0x1000
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_WCB_RD_EMPTY_SHFT                                    0xc
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_WCB_WR_FULL_BMSK                                   0x200
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_WCB_WR_FULL_SHFT                                     0x9
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_WCB_WR_EMPTY_BMSK                                  0x100
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_WCB_WR_EMPTY_SHFT                                    0x8
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_ACB_RD_FULL_BMSK                                    0x20
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_ACB_RD_FULL_SHFT                                     0x5
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_ACB_RD_EMPTY_BMSK                                   0x10
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_ACB_RD_EMPTY_SHFT                                    0x4
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_ACB_WR_FULL_BMSK                                     0x2
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_ACB_WR_FULL_SHFT                                     0x1
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_ACB_WR_EMPTY_BMSK                                    0x1
#define HWIO_BIMC_M_APP_MPORT_STATUS_3A_PIPE0_ACB_WR_EMPTY_SHFT                                    0x0

#define HWIO_BIMC_M_APP_MPORT_STATUS_3B_ADDR                                                (BIMC_M_APP_MPORT_REG_BASE      + 0x00000434)
#define HWIO_BIMC_M_APP_MPORT_STATUS_3B_RMSK                                                  0x333333
#define HWIO_BIMC_M_APP_MPORT_STATUS_3B_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_3B_ADDR, HWIO_BIMC_M_APP_MPORT_STATUS_3B_RMSK)
#define HWIO_BIMC_M_APP_MPORT_STATUS_3B_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_3B_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_STATUS_3B_PIPE0_RGB_RD_FULL_BMSK                                0x200000
#define HWIO_BIMC_M_APP_MPORT_STATUS_3B_PIPE0_RGB_RD_FULL_SHFT                                    0x15
#define HWIO_BIMC_M_APP_MPORT_STATUS_3B_PIPE0_RGB_RD_EMPTY_BMSK                               0x100000
#define HWIO_BIMC_M_APP_MPORT_STATUS_3B_PIPE0_RGB_RD_EMPTY_SHFT                                   0x14
#define HWIO_BIMC_M_APP_MPORT_STATUS_3B_PIPE0_RGB_WR_FULL_BMSK                                 0x20000
#define HWIO_BIMC_M_APP_MPORT_STATUS_3B_PIPE0_RGB_WR_FULL_SHFT                                    0x11
#define HWIO_BIMC_M_APP_MPORT_STATUS_3B_PIPE0_RGB_WR_EMPTY_BMSK                                0x10000
#define HWIO_BIMC_M_APP_MPORT_STATUS_3B_PIPE0_RGB_WR_EMPTY_SHFT                                   0x10
#define HWIO_BIMC_M_APP_MPORT_STATUS_3B_PIPE0_W2AB_RD_FULL_BMSK                                 0x2000
#define HWIO_BIMC_M_APP_MPORT_STATUS_3B_PIPE0_W2AB_RD_FULL_SHFT                                    0xd
#define HWIO_BIMC_M_APP_MPORT_STATUS_3B_PIPE0_W2AB_RD_EMPTY_BMSK                                0x1000
#define HWIO_BIMC_M_APP_MPORT_STATUS_3B_PIPE0_W2AB_RD_EMPTY_SHFT                                   0xc
#define HWIO_BIMC_M_APP_MPORT_STATUS_3B_PIPE0_W2AB_WR_FULL_BMSK                                  0x200
#define HWIO_BIMC_M_APP_MPORT_STATUS_3B_PIPE0_W2AB_WR_FULL_SHFT                                    0x9
#define HWIO_BIMC_M_APP_MPORT_STATUS_3B_PIPE0_W2AB_WR_EMPTY_BMSK                                 0x100
#define HWIO_BIMC_M_APP_MPORT_STATUS_3B_PIPE0_W2AB_WR_EMPTY_SHFT                                   0x8
#define HWIO_BIMC_M_APP_MPORT_STATUS_3B_PIPE0_A2WB_RD_FULL_BMSK                                   0x20
#define HWIO_BIMC_M_APP_MPORT_STATUS_3B_PIPE0_A2WB_RD_FULL_SHFT                                    0x5
#define HWIO_BIMC_M_APP_MPORT_STATUS_3B_PIPE0_A2WB_RD_EMPTY_BMSK                                  0x10
#define HWIO_BIMC_M_APP_MPORT_STATUS_3B_PIPE0_A2WB_RD_EMPTY_SHFT                                   0x4
#define HWIO_BIMC_M_APP_MPORT_STATUS_3B_PIPE0_A2WB_WR_FULL_BMSK                                    0x2
#define HWIO_BIMC_M_APP_MPORT_STATUS_3B_PIPE0_A2WB_WR_FULL_SHFT                                    0x1
#define HWIO_BIMC_M_APP_MPORT_STATUS_3B_PIPE0_A2WB_WR_EMPTY_BMSK                                   0x1
#define HWIO_BIMC_M_APP_MPORT_STATUS_3B_PIPE0_A2WB_WR_EMPTY_SHFT                                   0x0

#define HWIO_BIMC_M_APP_MPORT_STATUS_4A_ADDR                                                (BIMC_M_APP_MPORT_REG_BASE      + 0x00000440)
#define HWIO_BIMC_M_APP_MPORT_STATUS_4A_RMSK                                                  0xff00ff
#define HWIO_BIMC_M_APP_MPORT_STATUS_4A_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_4A_ADDR, HWIO_BIMC_M_APP_MPORT_STATUS_4A_RMSK)
#define HWIO_BIMC_M_APP_MPORT_STATUS_4A_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_4A_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_STATUS_4A_PIPE1_WR_PENDING_PRE_BUF_BMSK                         0xff0000
#define HWIO_BIMC_M_APP_MPORT_STATUS_4A_PIPE1_WR_PENDING_PRE_BUF_SHFT                             0x10
#define HWIO_BIMC_M_APP_MPORT_STATUS_4A_PIPE1_RD_PENDING_PRE_BUF_BMSK                             0xff
#define HWIO_BIMC_M_APP_MPORT_STATUS_4A_PIPE1_RD_PENDING_PRE_BUF_SHFT                              0x0

#define HWIO_BIMC_M_APP_MPORT_STATUS_4B_ADDR                                                (BIMC_M_APP_MPORT_REG_BASE      + 0x00000444)
#define HWIO_BIMC_M_APP_MPORT_STATUS_4B_RMSK                                                  0xff00ff
#define HWIO_BIMC_M_APP_MPORT_STATUS_4B_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_4B_ADDR, HWIO_BIMC_M_APP_MPORT_STATUS_4B_RMSK)
#define HWIO_BIMC_M_APP_MPORT_STATUS_4B_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_4B_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_STATUS_4B_PIPE1_WR_PENDING_POST_BUF_BMSK                        0xff0000
#define HWIO_BIMC_M_APP_MPORT_STATUS_4B_PIPE1_WR_PENDING_POST_BUF_SHFT                            0x10
#define HWIO_BIMC_M_APP_MPORT_STATUS_4B_PIPE1_RD_PENDING_POST_BUF_BMSK                            0xff
#define HWIO_BIMC_M_APP_MPORT_STATUS_4B_PIPE1_RD_PENDING_POST_BUF_SHFT                             0x0

#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_ADDR                                                (BIMC_M_APP_MPORT_REG_BASE      + 0x00000450)
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_RMSK                                                0xff333333
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_5A_ADDR, HWIO_BIMC_M_APP_MPORT_STATUS_5A_RMSK)
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_5A_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_RCB_DATA_RD_FULL_BMSK                         0x80000000
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_RCB_DATA_RD_FULL_SHFT                               0x1f
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_RCB_DATA_RD_EMPTY_BMSK                        0x40000000
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_RCB_DATA_RD_EMPTY_SHFT                              0x1e
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_RCB_CTRL_RD_FULL_BMSK                         0x20000000
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_RCB_CTRL_RD_FULL_SHFT                               0x1d
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_RCB_CTRL_RD_EMPTY_BMSK                        0x10000000
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_RCB_CTRL_RD_EMPTY_SHFT                              0x1c
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_RCB_DATA_WR_FULL_BMSK                          0x8000000
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_RCB_DATA_WR_FULL_SHFT                               0x1b
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_RCB_DATA_WR_EMPTY_BMSK                         0x4000000
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_RCB_DATA_WR_EMPTY_SHFT                              0x1a
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_RCB_CTRL_WR_FULL_BMSK                          0x2000000
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_RCB_CTRL_WR_FULL_SHFT                               0x19
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_RCB_CTRL_WR_EMPTY_BMSK                         0x1000000
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_RCB_CTRL_WR_EMPTY_SHFT                              0x18
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_BCB_RD_FULL_BMSK                                0x200000
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_BCB_RD_FULL_SHFT                                    0x15
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_BCB_RD_EMPTY_BMSK                               0x100000
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_BCB_RD_EMPTY_SHFT                                   0x14
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_BCB_WR_FULL_BMSK                                 0x20000
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_BCB_WR_FULL_SHFT                                    0x11
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_BCB_WR_EMPTY_BMSK                                0x10000
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_BCB_WR_EMPTY_SHFT                                   0x10
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_WCB_RD_FULL_BMSK                                  0x2000
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_WCB_RD_FULL_SHFT                                     0xd
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_WCB_RD_EMPTY_BMSK                                 0x1000
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_WCB_RD_EMPTY_SHFT                                    0xc
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_WCB_WR_FULL_BMSK                                   0x200
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_WCB_WR_FULL_SHFT                                     0x9
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_WCB_WR_EMPTY_BMSK                                  0x100
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_WCB_WR_EMPTY_SHFT                                    0x8
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_ACB_RD_FULL_BMSK                                    0x20
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_ACB_RD_FULL_SHFT                                     0x5
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_ACB_RD_EMPTY_BMSK                                   0x10
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_ACB_RD_EMPTY_SHFT                                    0x4
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_ACB_WR_FULL_BMSK                                     0x2
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_ACB_WR_FULL_SHFT                                     0x1
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_ACB_WR_EMPTY_BMSK                                    0x1
#define HWIO_BIMC_M_APP_MPORT_STATUS_5A_PIPE1_ACB_WR_EMPTY_SHFT                                    0x0

#define HWIO_BIMC_M_APP_MPORT_STATUS_5B_ADDR                                                (BIMC_M_APP_MPORT_REG_BASE      + 0x00000454)
#define HWIO_BIMC_M_APP_MPORT_STATUS_5B_RMSK                                                  0x333333
#define HWIO_BIMC_M_APP_MPORT_STATUS_5B_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_5B_ADDR, HWIO_BIMC_M_APP_MPORT_STATUS_5B_RMSK)
#define HWIO_BIMC_M_APP_MPORT_STATUS_5B_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_5B_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_STATUS_5B_PIPE1_RGB_RD_FULL_BMSK                                0x200000
#define HWIO_BIMC_M_APP_MPORT_STATUS_5B_PIPE1_RGB_RD_FULL_SHFT                                    0x15
#define HWIO_BIMC_M_APP_MPORT_STATUS_5B_PIPE1_RGB_RD_EMPTY_BMSK                               0x100000
#define HWIO_BIMC_M_APP_MPORT_STATUS_5B_PIPE1_RGB_RD_EMPTY_SHFT                                   0x14
#define HWIO_BIMC_M_APP_MPORT_STATUS_5B_PIPE1_RGB_WR_FULL_BMSK                                 0x20000
#define HWIO_BIMC_M_APP_MPORT_STATUS_5B_PIPE1_RGB_WR_FULL_SHFT                                    0x11
#define HWIO_BIMC_M_APP_MPORT_STATUS_5B_PIPE1_RGB_WR_EMPTY_BMSK                                0x10000
#define HWIO_BIMC_M_APP_MPORT_STATUS_5B_PIPE1_RGB_WR_EMPTY_SHFT                                   0x10
#define HWIO_BIMC_M_APP_MPORT_STATUS_5B_PIPE1_W2AB_RD_FULL_BMSK                                 0x2000
#define HWIO_BIMC_M_APP_MPORT_STATUS_5B_PIPE1_W2AB_RD_FULL_SHFT                                    0xd
#define HWIO_BIMC_M_APP_MPORT_STATUS_5B_PIPE1_W2AB_RD_EMPTY_BMSK                                0x1000
#define HWIO_BIMC_M_APP_MPORT_STATUS_5B_PIPE1_W2AB_RD_EMPTY_SHFT                                   0xc
#define HWIO_BIMC_M_APP_MPORT_STATUS_5B_PIPE1_W2AB_WR_FULL_BMSK                                  0x200
#define HWIO_BIMC_M_APP_MPORT_STATUS_5B_PIPE1_W2AB_WR_FULL_SHFT                                    0x9
#define HWIO_BIMC_M_APP_MPORT_STATUS_5B_PIPE1_W2AB_WR_EMPTY_BMSK                                 0x100
#define HWIO_BIMC_M_APP_MPORT_STATUS_5B_PIPE1_W2AB_WR_EMPTY_SHFT                                   0x8
#define HWIO_BIMC_M_APP_MPORT_STATUS_5B_PIPE1_A2WB_RD_FULL_BMSK                                   0x20
#define HWIO_BIMC_M_APP_MPORT_STATUS_5B_PIPE1_A2WB_RD_FULL_SHFT                                    0x5
#define HWIO_BIMC_M_APP_MPORT_STATUS_5B_PIPE1_A2WB_RD_EMPTY_BMSK                                  0x10
#define HWIO_BIMC_M_APP_MPORT_STATUS_5B_PIPE1_A2WB_RD_EMPTY_SHFT                                   0x4
#define HWIO_BIMC_M_APP_MPORT_STATUS_5B_PIPE1_A2WB_WR_FULL_BMSK                                    0x2
#define HWIO_BIMC_M_APP_MPORT_STATUS_5B_PIPE1_A2WB_WR_FULL_SHFT                                    0x1
#define HWIO_BIMC_M_APP_MPORT_STATUS_5B_PIPE1_A2WB_WR_EMPTY_BMSK                                   0x1
#define HWIO_BIMC_M_APP_MPORT_STATUS_5B_PIPE1_A2WB_WR_EMPTY_SHFT                                   0x0

#define HWIO_BIMC_M_APP_MPORT_STATUS_6A_ADDR                                                (BIMC_M_APP_MPORT_REG_BASE      + 0x00000460)
#define HWIO_BIMC_M_APP_MPORT_STATUS_6A_RMSK                                                  0xff00ff
#define HWIO_BIMC_M_APP_MPORT_STATUS_6A_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_6A_ADDR, HWIO_BIMC_M_APP_MPORT_STATUS_6A_RMSK)
#define HWIO_BIMC_M_APP_MPORT_STATUS_6A_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_6A_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_STATUS_6A_PIPE2_WR_PENDING_PRE_BUF_BMSK                         0xff0000
#define HWIO_BIMC_M_APP_MPORT_STATUS_6A_PIPE2_WR_PENDING_PRE_BUF_SHFT                             0x10
#define HWIO_BIMC_M_APP_MPORT_STATUS_6A_PIPE2_RD_PENDING_PRE_BUF_BMSK                             0xff
#define HWIO_BIMC_M_APP_MPORT_STATUS_6A_PIPE2_RD_PENDING_PRE_BUF_SHFT                              0x0

#define HWIO_BIMC_M_APP_MPORT_STATUS_6B_ADDR                                                (BIMC_M_APP_MPORT_REG_BASE      + 0x00000464)
#define HWIO_BIMC_M_APP_MPORT_STATUS_6B_RMSK                                                  0xff00ff
#define HWIO_BIMC_M_APP_MPORT_STATUS_6B_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_6B_ADDR, HWIO_BIMC_M_APP_MPORT_STATUS_6B_RMSK)
#define HWIO_BIMC_M_APP_MPORT_STATUS_6B_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_6B_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_STATUS_6B_PIPE2_WR_PENDING_POST_BUF_BMSK                        0xff0000
#define HWIO_BIMC_M_APP_MPORT_STATUS_6B_PIPE2_WR_PENDING_POST_BUF_SHFT                            0x10
#define HWIO_BIMC_M_APP_MPORT_STATUS_6B_PIPE2_RD_PENDING_POST_BUF_BMSK                            0xff
#define HWIO_BIMC_M_APP_MPORT_STATUS_6B_PIPE2_RD_PENDING_POST_BUF_SHFT                             0x0

#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_ADDR                                                (BIMC_M_APP_MPORT_REG_BASE      + 0x00000470)
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_RMSK                                                0xff333333
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_7A_ADDR, HWIO_BIMC_M_APP_MPORT_STATUS_7A_RMSK)
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_7A_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_RCB_DATA_RD_FULL_BMSK                         0x80000000
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_RCB_DATA_RD_FULL_SHFT                               0x1f
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_RCB_DATA_RD_EMPTY_BMSK                        0x40000000
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_RCB_DATA_RD_EMPTY_SHFT                              0x1e
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_RCB_CTRL_RD_FULL_BMSK                         0x20000000
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_RCB_CTRL_RD_FULL_SHFT                               0x1d
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_RCB_CTRL_RD_EMPTY_BMSK                        0x10000000
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_RCB_CTRL_RD_EMPTY_SHFT                              0x1c
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_RCB_DATA_WR_FULL_BMSK                          0x8000000
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_RCB_DATA_WR_FULL_SHFT                               0x1b
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_RCB_DATA_WR_EMPTY_BMSK                         0x4000000
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_RCB_DATA_WR_EMPTY_SHFT                              0x1a
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_RCB_CTRL_WR_FULL_BMSK                          0x2000000
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_RCB_CTRL_WR_FULL_SHFT                               0x19
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_RCB_CTRL_WR_EMPTY_BMSK                         0x1000000
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_RCB_CTRL_WR_EMPTY_SHFT                              0x18
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_BCB_RD_FULL_BMSK                                0x200000
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_BCB_RD_FULL_SHFT                                    0x15
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_BCB_RD_EMPTY_BMSK                               0x100000
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_BCB_RD_EMPTY_SHFT                                   0x14
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_BCB_WR_FULL_BMSK                                 0x20000
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_BCB_WR_FULL_SHFT                                    0x11
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_BCB_WR_EMPTY_BMSK                                0x10000
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_BCB_WR_EMPTY_SHFT                                   0x10
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_WCB_RD_FULL_BMSK                                  0x2000
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_WCB_RD_FULL_SHFT                                     0xd
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_WCB_RD_EMPTY_BMSK                                 0x1000
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_WCB_RD_EMPTY_SHFT                                    0xc
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_WCB_WR_FULL_BMSK                                   0x200
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_WCB_WR_FULL_SHFT                                     0x9
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_WCB_WR_EMPTY_BMSK                                  0x100
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_WCB_WR_EMPTY_SHFT                                    0x8
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_ACB_RD_FULL_BMSK                                    0x20
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_ACB_RD_FULL_SHFT                                     0x5
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_ACB_RD_EMPTY_BMSK                                   0x10
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_ACB_RD_EMPTY_SHFT                                    0x4
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_ACB_WR_FULL_BMSK                                     0x2
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_ACB_WR_FULL_SHFT                                     0x1
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_ACB_WR_EMPTY_BMSK                                    0x1
#define HWIO_BIMC_M_APP_MPORT_STATUS_7A_PIPE2_ACB_WR_EMPTY_SHFT                                    0x0

#define HWIO_BIMC_M_APP_MPORT_STATUS_7B_ADDR                                                (BIMC_M_APP_MPORT_REG_BASE      + 0x00000474)
#define HWIO_BIMC_M_APP_MPORT_STATUS_7B_RMSK                                                  0x333333
#define HWIO_BIMC_M_APP_MPORT_STATUS_7B_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_7B_ADDR, HWIO_BIMC_M_APP_MPORT_STATUS_7B_RMSK)
#define HWIO_BIMC_M_APP_MPORT_STATUS_7B_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_7B_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_STATUS_7B_PIPE2_RGB_RD_FULL_BMSK                                0x200000
#define HWIO_BIMC_M_APP_MPORT_STATUS_7B_PIPE2_RGB_RD_FULL_SHFT                                    0x15
#define HWIO_BIMC_M_APP_MPORT_STATUS_7B_PIPE2_RGB_RD_EMPTY_BMSK                               0x100000
#define HWIO_BIMC_M_APP_MPORT_STATUS_7B_PIPE2_RGB_RD_EMPTY_SHFT                                   0x14
#define HWIO_BIMC_M_APP_MPORT_STATUS_7B_PIPE2_RGB_WR_FULL_BMSK                                 0x20000
#define HWIO_BIMC_M_APP_MPORT_STATUS_7B_PIPE2_RGB_WR_FULL_SHFT                                    0x11
#define HWIO_BIMC_M_APP_MPORT_STATUS_7B_PIPE2_RGB_WR_EMPTY_BMSK                                0x10000
#define HWIO_BIMC_M_APP_MPORT_STATUS_7B_PIPE2_RGB_WR_EMPTY_SHFT                                   0x10
#define HWIO_BIMC_M_APP_MPORT_STATUS_7B_PIPE2_W2AB_RD_FULL_BMSK                                 0x2000
#define HWIO_BIMC_M_APP_MPORT_STATUS_7B_PIPE2_W2AB_RD_FULL_SHFT                                    0xd
#define HWIO_BIMC_M_APP_MPORT_STATUS_7B_PIPE2_W2AB_RD_EMPTY_BMSK                                0x1000
#define HWIO_BIMC_M_APP_MPORT_STATUS_7B_PIPE2_W2AB_RD_EMPTY_SHFT                                   0xc
#define HWIO_BIMC_M_APP_MPORT_STATUS_7B_PIPE2_W2AB_WR_FULL_BMSK                                  0x200
#define HWIO_BIMC_M_APP_MPORT_STATUS_7B_PIPE2_W2AB_WR_FULL_SHFT                                    0x9
#define HWIO_BIMC_M_APP_MPORT_STATUS_7B_PIPE2_W2AB_WR_EMPTY_BMSK                                 0x100
#define HWIO_BIMC_M_APP_MPORT_STATUS_7B_PIPE2_W2AB_WR_EMPTY_SHFT                                   0x8
#define HWIO_BIMC_M_APP_MPORT_STATUS_7B_PIPE2_A2WB_RD_FULL_BMSK                                   0x20
#define HWIO_BIMC_M_APP_MPORT_STATUS_7B_PIPE2_A2WB_RD_FULL_SHFT                                    0x5
#define HWIO_BIMC_M_APP_MPORT_STATUS_7B_PIPE2_A2WB_RD_EMPTY_BMSK                                  0x10
#define HWIO_BIMC_M_APP_MPORT_STATUS_7B_PIPE2_A2WB_RD_EMPTY_SHFT                                   0x4
#define HWIO_BIMC_M_APP_MPORT_STATUS_7B_PIPE2_A2WB_WR_FULL_BMSK                                    0x2
#define HWIO_BIMC_M_APP_MPORT_STATUS_7B_PIPE2_A2WB_WR_FULL_SHFT                                    0x1
#define HWIO_BIMC_M_APP_MPORT_STATUS_7B_PIPE2_A2WB_WR_EMPTY_BMSK                                   0x1
#define HWIO_BIMC_M_APP_MPORT_STATUS_7B_PIPE2_A2WB_WR_EMPTY_SHFT                                   0x0

#define HWIO_BIMC_M_APP_MPORT_STATUS_8A_ADDR                                                (BIMC_M_APP_MPORT_REG_BASE      + 0x00000480)
#define HWIO_BIMC_M_APP_MPORT_STATUS_8A_RMSK                                                  0xff00ff
#define HWIO_BIMC_M_APP_MPORT_STATUS_8A_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_8A_ADDR, HWIO_BIMC_M_APP_MPORT_STATUS_8A_RMSK)
#define HWIO_BIMC_M_APP_MPORT_STATUS_8A_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_8A_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_STATUS_8A_PIPE3_WR_PENDING_PRE_BUF_BMSK                         0xff0000
#define HWIO_BIMC_M_APP_MPORT_STATUS_8A_PIPE3_WR_PENDING_PRE_BUF_SHFT                             0x10
#define HWIO_BIMC_M_APP_MPORT_STATUS_8A_PIPE3_RD_PENDING_PRE_BUF_BMSK                             0xff
#define HWIO_BIMC_M_APP_MPORT_STATUS_8A_PIPE3_RD_PENDING_PRE_BUF_SHFT                              0x0

#define HWIO_BIMC_M_APP_MPORT_STATUS_8B_ADDR                                                (BIMC_M_APP_MPORT_REG_BASE      + 0x00000484)
#define HWIO_BIMC_M_APP_MPORT_STATUS_8B_RMSK                                                  0xff00ff
#define HWIO_BIMC_M_APP_MPORT_STATUS_8B_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_8B_ADDR, HWIO_BIMC_M_APP_MPORT_STATUS_8B_RMSK)
#define HWIO_BIMC_M_APP_MPORT_STATUS_8B_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_8B_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_STATUS_8B_PIPE3_WR_PENDING_POST_BUF_BMSK                        0xff0000
#define HWIO_BIMC_M_APP_MPORT_STATUS_8B_PIPE3_WR_PENDING_POST_BUF_SHFT                            0x10
#define HWIO_BIMC_M_APP_MPORT_STATUS_8B_PIPE3_RD_PENDING_POST_BUF_BMSK                            0xff
#define HWIO_BIMC_M_APP_MPORT_STATUS_8B_PIPE3_RD_PENDING_POST_BUF_SHFT                             0x0

#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_ADDR                                                (BIMC_M_APP_MPORT_REG_BASE      + 0x00000490)
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_RMSK                                                0xff333333
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_9A_ADDR, HWIO_BIMC_M_APP_MPORT_STATUS_9A_RMSK)
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_9A_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_RCB_DATA_RD_FULL_BMSK                         0x80000000
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_RCB_DATA_RD_FULL_SHFT                               0x1f
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_RCB_DATA_RD_EMPTY_BMSK                        0x40000000
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_RCB_DATA_RD_EMPTY_SHFT                              0x1e
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_RCB_CTRL_RD_FULL_BMSK                         0x20000000
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_RCB_CTRL_RD_FULL_SHFT                               0x1d
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_RCB_CTRL_RD_EMPTY_BMSK                        0x10000000
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_RCB_CTRL_RD_EMPTY_SHFT                              0x1c
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_RCB_DATA_WR_FULL_BMSK                          0x8000000
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_RCB_DATA_WR_FULL_SHFT                               0x1b
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_RCB_DATA_WR_EMPTY_BMSK                         0x4000000
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_RCB_DATA_WR_EMPTY_SHFT                              0x1a
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_RCB_CTRL_WR_FULL_BMSK                          0x2000000
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_RCB_CTRL_WR_FULL_SHFT                               0x19
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_RCB_CTRL_WR_EMPTY_BMSK                         0x1000000
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_RCB_CTRL_WR_EMPTY_SHFT                              0x18
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_BCB_RD_FULL_BMSK                                0x200000
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_BCB_RD_FULL_SHFT                                    0x15
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_BCB_RD_EMPTY_BMSK                               0x100000
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_BCB_RD_EMPTY_SHFT                                   0x14
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_BCB_WR_FULL_BMSK                                 0x20000
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_BCB_WR_FULL_SHFT                                    0x11
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_BCB_WR_EMPTY_BMSK                                0x10000
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_BCB_WR_EMPTY_SHFT                                   0x10
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_WCB_RD_FULL_BMSK                                  0x2000
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_WCB_RD_FULL_SHFT                                     0xd
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_WCB_RD_EMPTY_BMSK                                 0x1000
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_WCB_RD_EMPTY_SHFT                                    0xc
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_WCB_WR_FULL_BMSK                                   0x200
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_WCB_WR_FULL_SHFT                                     0x9
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_WCB_WR_EMPTY_BMSK                                  0x100
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_WCB_WR_EMPTY_SHFT                                    0x8
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_ACB_RD_FULL_BMSK                                    0x20
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_ACB_RD_FULL_SHFT                                     0x5
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_ACB_RD_EMPTY_BMSK                                   0x10
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_ACB_RD_EMPTY_SHFT                                    0x4
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_ACB_WR_FULL_BMSK                                     0x2
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_ACB_WR_FULL_SHFT                                     0x1
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_ACB_WR_EMPTY_BMSK                                    0x1
#define HWIO_BIMC_M_APP_MPORT_STATUS_9A_PIPE3_ACB_WR_EMPTY_SHFT                                    0x0

#define HWIO_BIMC_M_APP_MPORT_STATUS_9B_ADDR                                                (BIMC_M_APP_MPORT_REG_BASE      + 0x00000494)
#define HWIO_BIMC_M_APP_MPORT_STATUS_9B_RMSK                                                  0x333333
#define HWIO_BIMC_M_APP_MPORT_STATUS_9B_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_9B_ADDR, HWIO_BIMC_M_APP_MPORT_STATUS_9B_RMSK)
#define HWIO_BIMC_M_APP_MPORT_STATUS_9B_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_STATUS_9B_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_STATUS_9B_PIPE3_RGB_RD_FULL_BMSK                                0x200000
#define HWIO_BIMC_M_APP_MPORT_STATUS_9B_PIPE3_RGB_RD_FULL_SHFT                                    0x15
#define HWIO_BIMC_M_APP_MPORT_STATUS_9B_PIPE3_RGB_RD_EMPTY_BMSK                               0x100000
#define HWIO_BIMC_M_APP_MPORT_STATUS_9B_PIPE3_RGB_RD_EMPTY_SHFT                                   0x14
#define HWIO_BIMC_M_APP_MPORT_STATUS_9B_PIPE3_RGB_WR_FULL_BMSK                                 0x20000
#define HWIO_BIMC_M_APP_MPORT_STATUS_9B_PIPE3_RGB_WR_FULL_SHFT                                    0x11
#define HWIO_BIMC_M_APP_MPORT_STATUS_9B_PIPE3_RGB_WR_EMPTY_BMSK                                0x10000
#define HWIO_BIMC_M_APP_MPORT_STATUS_9B_PIPE3_RGB_WR_EMPTY_SHFT                                   0x10
#define HWIO_BIMC_M_APP_MPORT_STATUS_9B_PIPE3_W2AB_RD_FULL_BMSK                                 0x2000
#define HWIO_BIMC_M_APP_MPORT_STATUS_9B_PIPE3_W2AB_RD_FULL_SHFT                                    0xd
#define HWIO_BIMC_M_APP_MPORT_STATUS_9B_PIPE3_W2AB_RD_EMPTY_BMSK                                0x1000
#define HWIO_BIMC_M_APP_MPORT_STATUS_9B_PIPE3_W2AB_RD_EMPTY_SHFT                                   0xc
#define HWIO_BIMC_M_APP_MPORT_STATUS_9B_PIPE3_W2AB_WR_FULL_BMSK                                  0x200
#define HWIO_BIMC_M_APP_MPORT_STATUS_9B_PIPE3_W2AB_WR_FULL_SHFT                                    0x9
#define HWIO_BIMC_M_APP_MPORT_STATUS_9B_PIPE3_W2AB_WR_EMPTY_BMSK                                 0x100
#define HWIO_BIMC_M_APP_MPORT_STATUS_9B_PIPE3_W2AB_WR_EMPTY_SHFT                                   0x8
#define HWIO_BIMC_M_APP_MPORT_STATUS_9B_PIPE3_A2WB_RD_FULL_BMSK                                   0x20
#define HWIO_BIMC_M_APP_MPORT_STATUS_9B_PIPE3_A2WB_RD_FULL_SHFT                                    0x5
#define HWIO_BIMC_M_APP_MPORT_STATUS_9B_PIPE3_A2WB_RD_EMPTY_BMSK                                  0x10
#define HWIO_BIMC_M_APP_MPORT_STATUS_9B_PIPE3_A2WB_RD_EMPTY_SHFT                                   0x4
#define HWIO_BIMC_M_APP_MPORT_STATUS_9B_PIPE3_A2WB_WR_FULL_BMSK                                    0x2
#define HWIO_BIMC_M_APP_MPORT_STATUS_9B_PIPE3_A2WB_WR_FULL_SHFT                                    0x1
#define HWIO_BIMC_M_APP_MPORT_STATUS_9B_PIPE3_A2WB_WR_EMPTY_BMSK                                   0x1
#define HWIO_BIMC_M_APP_MPORT_STATUS_9B_PIPE3_A2WB_WR_EMPTY_SHFT                                   0x0

#define HWIO_BIMC_M_APP_MPORT_BKE1_ENABLE_ADDR                                              (BIMC_M_APP_MPORT_REG_BASE      + 0x00000800)
#define HWIO_BIMC_M_APP_MPORT_BKE1_ENABLE_RMSK                                              0xff000011
#define HWIO_BIMC_M_APP_MPORT_BKE1_ENABLE_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE1_ENABLE_ADDR, HWIO_BIMC_M_APP_MPORT_BKE1_ENABLE_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE1_ENABLE_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE1_ENABLE_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE1_ENABLE_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE1_ENABLE_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE1_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE1_ENABLE_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE1_ENABLE_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE1_ENABLE_QOS_POLICY_SEL_BMSK                               0xff000000
#define HWIO_BIMC_M_APP_MPORT_BKE1_ENABLE_QOS_POLICY_SEL_SHFT                                     0x18
#define HWIO_BIMC_M_APP_MPORT_BKE1_ENABLE_SCALING_FACTOR_BMSK                                     0x10
#define HWIO_BIMC_M_APP_MPORT_BKE1_ENABLE_SCALING_FACTOR_SHFT                                      0x4
#define HWIO_BIMC_M_APP_MPORT_BKE1_ENABLE_ENABLE_BMSK                                              0x1
#define HWIO_BIMC_M_APP_MPORT_BKE1_ENABLE_ENABLE_SHFT                                              0x0

#define HWIO_BIMC_M_APP_MPORT_BKE1_GRANT_PERIOD_ADDR                                        (BIMC_M_APP_MPORT_REG_BASE      + 0x00000804)
#define HWIO_BIMC_M_APP_MPORT_BKE1_GRANT_PERIOD_RMSK                                             0x3ff
#define HWIO_BIMC_M_APP_MPORT_BKE1_GRANT_PERIOD_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE1_GRANT_PERIOD_ADDR, HWIO_BIMC_M_APP_MPORT_BKE1_GRANT_PERIOD_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE1_GRANT_PERIOD_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE1_GRANT_PERIOD_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE1_GRANT_PERIOD_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE1_GRANT_PERIOD_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE1_GRANT_PERIOD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE1_GRANT_PERIOD_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE1_GRANT_PERIOD_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE1_GRANT_PERIOD_GRANT_PERIOD_BMSK                                0x3ff
#define HWIO_BIMC_M_APP_MPORT_BKE1_GRANT_PERIOD_GRANT_PERIOD_SHFT                                  0x0

#define HWIO_BIMC_M_APP_MPORT_BKE1_GRANT_COUNT_ADDR                                         (BIMC_M_APP_MPORT_REG_BASE      + 0x00000808)
#define HWIO_BIMC_M_APP_MPORT_BKE1_GRANT_COUNT_RMSK                                             0xffff
#define HWIO_BIMC_M_APP_MPORT_BKE1_GRANT_COUNT_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE1_GRANT_COUNT_ADDR, HWIO_BIMC_M_APP_MPORT_BKE1_GRANT_COUNT_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE1_GRANT_COUNT_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE1_GRANT_COUNT_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE1_GRANT_COUNT_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE1_GRANT_COUNT_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE1_GRANT_COUNT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE1_GRANT_COUNT_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE1_GRANT_COUNT_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE1_GRANT_COUNT_GRANT_COUNT_BMSK                                 0xffff
#define HWIO_BIMC_M_APP_MPORT_BKE1_GRANT_COUNT_GRANT_COUNT_SHFT                                    0x0

#define HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_HIGH_ADDR                                      (BIMC_M_APP_MPORT_REG_BASE      + 0x00000820)
#define HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_HIGH_RMSK                                          0xffff
#define HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_HIGH_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_HIGH_ADDR, HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_HIGH_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_HIGH_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_HIGH_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_HIGH_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_HIGH_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_HIGH_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_HIGH_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_HIGH_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_HIGH_THRESHOLD_BMSK                                0xffff
#define HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_HIGH_THRESHOLD_SHFT                                   0x0

#define HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_MEDIUM_ADDR                                    (BIMC_M_APP_MPORT_REG_BASE      + 0x00000824)
#define HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_MEDIUM_RMSK                                        0xffff
#define HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_MEDIUM_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_MEDIUM_ADDR, HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_MEDIUM_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_MEDIUM_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_MEDIUM_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_MEDIUM_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_MEDIUM_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_MEDIUM_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_MEDIUM_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_MEDIUM_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_MEDIUM_THRESHOLD_BMSK                              0xffff
#define HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_MEDIUM_THRESHOLD_SHFT                                 0x0

#define HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_LOW_ADDR                                       (BIMC_M_APP_MPORT_REG_BASE      + 0x00000828)
#define HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_LOW_RMSK                                           0xffff
#define HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_LOW_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_LOW_ADDR, HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_LOW_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_LOW_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_LOW_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_LOW_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_LOW_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_LOW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_LOW_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_LOW_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_LOW_THRESHOLD_BMSK                                 0xffff
#define HWIO_BIMC_M_APP_MPORT_BKE1_THRESHOLD_LOW_THRESHOLD_SHFT                                    0x0

#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_0_ADDR                                            (BIMC_M_APP_MPORT_REG_BASE      + 0x00000840)
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_0_RMSK                                            0x80000303
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_0_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_0_ADDR, HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_0_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_0_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_0_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_0_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_0_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_0_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_0_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_0_LIMIT_COMMANDS_BMSK                             0x80000000
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_0_LIMIT_COMMANDS_SHFT                                   0x1f
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_0_AREQPRIORITY_BMSK                                    0x300
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_0_AREQPRIORITY_SHFT                                      0x8
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_0_PRIORITYLVL_BMSK                                       0x3
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_0_PRIORITYLVL_SHFT                                       0x0

#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_1_ADDR                                            (BIMC_M_APP_MPORT_REG_BASE      + 0x00000844)
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_1_RMSK                                            0x80000303
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_1_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_1_ADDR, HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_1_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_1_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_1_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_1_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_1_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_1_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_1_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_1_LIMIT_COMMANDS_BMSK                             0x80000000
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_1_LIMIT_COMMANDS_SHFT                                   0x1f
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_1_AREQPRIORITY_BMSK                                    0x300
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_1_AREQPRIORITY_SHFT                                      0x8
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_1_PRIORITYLVL_BMSK                                       0x3
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_1_PRIORITYLVL_SHFT                                       0x0

#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_2_ADDR                                            (BIMC_M_APP_MPORT_REG_BASE      + 0x00000848)
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_2_RMSK                                            0x80000303
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_2_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_2_ADDR, HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_2_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_2_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_2_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_2_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_2_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_2_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_2_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_2_LIMIT_COMMANDS_BMSK                             0x80000000
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_2_LIMIT_COMMANDS_SHFT                                   0x1f
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_2_AREQPRIORITY_BMSK                                    0x300
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_2_AREQPRIORITY_SHFT                                      0x8
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_2_PRIORITYLVL_BMSK                                       0x3
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_2_PRIORITYLVL_SHFT                                       0x0

#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_3_ADDR                                            (BIMC_M_APP_MPORT_REG_BASE      + 0x0000084c)
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_3_RMSK                                                 0x303
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_3_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_3_ADDR, HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_3_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_3_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_3_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_3_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_3_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_3_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_3_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_3_AREQPRIORITY_BMSK                                    0x300
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_3_AREQPRIORITY_SHFT                                      0x8
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_3_PRIORITYLVL_BMSK                                       0x3
#define HWIO_BIMC_M_APP_MPORT_BKE1_HEALTH_3_PRIORITYLVL_SHFT                                       0x0

#define HWIO_BIMC_M_APP_MPORT_BKE2_ENABLE_ADDR                                              (BIMC_M_APP_MPORT_REG_BASE      + 0x00000900)
#define HWIO_BIMC_M_APP_MPORT_BKE2_ENABLE_RMSK                                              0xff000011
#define HWIO_BIMC_M_APP_MPORT_BKE2_ENABLE_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE2_ENABLE_ADDR, HWIO_BIMC_M_APP_MPORT_BKE2_ENABLE_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE2_ENABLE_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE2_ENABLE_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE2_ENABLE_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE2_ENABLE_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE2_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE2_ENABLE_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE2_ENABLE_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE2_ENABLE_QOS_POLICY_SEL_BMSK                               0xff000000
#define HWIO_BIMC_M_APP_MPORT_BKE2_ENABLE_QOS_POLICY_SEL_SHFT                                     0x18
#define HWIO_BIMC_M_APP_MPORT_BKE2_ENABLE_SCALING_FACTOR_BMSK                                     0x10
#define HWIO_BIMC_M_APP_MPORT_BKE2_ENABLE_SCALING_FACTOR_SHFT                                      0x4
#define HWIO_BIMC_M_APP_MPORT_BKE2_ENABLE_ENABLE_BMSK                                              0x1
#define HWIO_BIMC_M_APP_MPORT_BKE2_ENABLE_ENABLE_SHFT                                              0x0

#define HWIO_BIMC_M_APP_MPORT_BKE2_GRANT_PERIOD_ADDR                                        (BIMC_M_APP_MPORT_REG_BASE      + 0x00000904)
#define HWIO_BIMC_M_APP_MPORT_BKE2_GRANT_PERIOD_RMSK                                             0x3ff
#define HWIO_BIMC_M_APP_MPORT_BKE2_GRANT_PERIOD_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE2_GRANT_PERIOD_ADDR, HWIO_BIMC_M_APP_MPORT_BKE2_GRANT_PERIOD_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE2_GRANT_PERIOD_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE2_GRANT_PERIOD_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE2_GRANT_PERIOD_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE2_GRANT_PERIOD_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE2_GRANT_PERIOD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE2_GRANT_PERIOD_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE2_GRANT_PERIOD_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE2_GRANT_PERIOD_GRANT_PERIOD_BMSK                                0x3ff
#define HWIO_BIMC_M_APP_MPORT_BKE2_GRANT_PERIOD_GRANT_PERIOD_SHFT                                  0x0

#define HWIO_BIMC_M_APP_MPORT_BKE2_GRANT_COUNT_ADDR                                         (BIMC_M_APP_MPORT_REG_BASE      + 0x00000908)
#define HWIO_BIMC_M_APP_MPORT_BKE2_GRANT_COUNT_RMSK                                             0xffff
#define HWIO_BIMC_M_APP_MPORT_BKE2_GRANT_COUNT_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE2_GRANT_COUNT_ADDR, HWIO_BIMC_M_APP_MPORT_BKE2_GRANT_COUNT_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE2_GRANT_COUNT_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE2_GRANT_COUNT_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE2_GRANT_COUNT_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE2_GRANT_COUNT_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE2_GRANT_COUNT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE2_GRANT_COUNT_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE2_GRANT_COUNT_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE2_GRANT_COUNT_GRANT_COUNT_BMSK                                 0xffff
#define HWIO_BIMC_M_APP_MPORT_BKE2_GRANT_COUNT_GRANT_COUNT_SHFT                                    0x0

#define HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_HIGH_ADDR                                      (BIMC_M_APP_MPORT_REG_BASE      + 0x00000920)
#define HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_HIGH_RMSK                                          0xffff
#define HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_HIGH_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_HIGH_ADDR, HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_HIGH_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_HIGH_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_HIGH_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_HIGH_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_HIGH_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_HIGH_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_HIGH_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_HIGH_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_HIGH_THRESHOLD_BMSK                                0xffff
#define HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_HIGH_THRESHOLD_SHFT                                   0x0

#define HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_MEDIUM_ADDR                                    (BIMC_M_APP_MPORT_REG_BASE      + 0x00000924)
#define HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_MEDIUM_RMSK                                        0xffff
#define HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_MEDIUM_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_MEDIUM_ADDR, HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_MEDIUM_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_MEDIUM_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_MEDIUM_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_MEDIUM_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_MEDIUM_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_MEDIUM_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_MEDIUM_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_MEDIUM_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_MEDIUM_THRESHOLD_BMSK                              0xffff
#define HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_MEDIUM_THRESHOLD_SHFT                                 0x0

#define HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_LOW_ADDR                                       (BIMC_M_APP_MPORT_REG_BASE      + 0x00000928)
#define HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_LOW_RMSK                                           0xffff
#define HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_LOW_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_LOW_ADDR, HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_LOW_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_LOW_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_LOW_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_LOW_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_LOW_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_LOW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_LOW_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_LOW_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_LOW_THRESHOLD_BMSK                                 0xffff
#define HWIO_BIMC_M_APP_MPORT_BKE2_THRESHOLD_LOW_THRESHOLD_SHFT                                    0x0

#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_0_ADDR                                            (BIMC_M_APP_MPORT_REG_BASE      + 0x00000940)
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_0_RMSK                                            0x80000303
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_0_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_0_ADDR, HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_0_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_0_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_0_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_0_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_0_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_0_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_0_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_0_LIMIT_COMMANDS_BMSK                             0x80000000
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_0_LIMIT_COMMANDS_SHFT                                   0x1f
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_0_AREQPRIORITY_BMSK                                    0x300
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_0_AREQPRIORITY_SHFT                                      0x8
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_0_PRIORITYLVL_BMSK                                       0x3
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_0_PRIORITYLVL_SHFT                                       0x0

#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_1_ADDR                                            (BIMC_M_APP_MPORT_REG_BASE      + 0x00000944)
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_1_RMSK                                            0x80000303
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_1_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_1_ADDR, HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_1_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_1_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_1_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_1_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_1_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_1_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_1_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_1_LIMIT_COMMANDS_BMSK                             0x80000000
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_1_LIMIT_COMMANDS_SHFT                                   0x1f
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_1_AREQPRIORITY_BMSK                                    0x300
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_1_AREQPRIORITY_SHFT                                      0x8
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_1_PRIORITYLVL_BMSK                                       0x3
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_1_PRIORITYLVL_SHFT                                       0x0

#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_2_ADDR                                            (BIMC_M_APP_MPORT_REG_BASE      + 0x00000948)
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_2_RMSK                                            0x80000303
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_2_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_2_ADDR, HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_2_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_2_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_2_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_2_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_2_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_2_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_2_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_2_LIMIT_COMMANDS_BMSK                             0x80000000
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_2_LIMIT_COMMANDS_SHFT                                   0x1f
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_2_AREQPRIORITY_BMSK                                    0x300
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_2_AREQPRIORITY_SHFT                                      0x8
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_2_PRIORITYLVL_BMSK                                       0x3
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_2_PRIORITYLVL_SHFT                                       0x0

#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_3_ADDR                                            (BIMC_M_APP_MPORT_REG_BASE      + 0x0000094c)
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_3_RMSK                                                 0x303
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_3_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_3_ADDR, HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_3_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_3_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_3_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_3_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_3_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_3_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_3_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_3_AREQPRIORITY_BMSK                                    0x300
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_3_AREQPRIORITY_SHFT                                      0x8
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_3_PRIORITYLVL_BMSK                                       0x3
#define HWIO_BIMC_M_APP_MPORT_BKE2_HEALTH_3_PRIORITYLVL_SHFT                                       0x0

#define HWIO_BIMC_M_APP_MPORT_BKE3_ENABLE_ADDR                                              (BIMC_M_APP_MPORT_REG_BASE      + 0x00000a00)
#define HWIO_BIMC_M_APP_MPORT_BKE3_ENABLE_RMSK                                              0xff000011
#define HWIO_BIMC_M_APP_MPORT_BKE3_ENABLE_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE3_ENABLE_ADDR, HWIO_BIMC_M_APP_MPORT_BKE3_ENABLE_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE3_ENABLE_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE3_ENABLE_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE3_ENABLE_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE3_ENABLE_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE3_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE3_ENABLE_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE3_ENABLE_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE3_ENABLE_QOS_POLICY_SEL_BMSK                               0xff000000
#define HWIO_BIMC_M_APP_MPORT_BKE3_ENABLE_QOS_POLICY_SEL_SHFT                                     0x18
#define HWIO_BIMC_M_APP_MPORT_BKE3_ENABLE_SCALING_FACTOR_BMSK                                     0x10
#define HWIO_BIMC_M_APP_MPORT_BKE3_ENABLE_SCALING_FACTOR_SHFT                                      0x4
#define HWIO_BIMC_M_APP_MPORT_BKE3_ENABLE_ENABLE_BMSK                                              0x1
#define HWIO_BIMC_M_APP_MPORT_BKE3_ENABLE_ENABLE_SHFT                                              0x0

#define HWIO_BIMC_M_APP_MPORT_BKE3_GRANT_PERIOD_ADDR                                        (BIMC_M_APP_MPORT_REG_BASE      + 0x00000a04)
#define HWIO_BIMC_M_APP_MPORT_BKE3_GRANT_PERIOD_RMSK                                             0x3ff
#define HWIO_BIMC_M_APP_MPORT_BKE3_GRANT_PERIOD_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE3_GRANT_PERIOD_ADDR, HWIO_BIMC_M_APP_MPORT_BKE3_GRANT_PERIOD_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE3_GRANT_PERIOD_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE3_GRANT_PERIOD_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE3_GRANT_PERIOD_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE3_GRANT_PERIOD_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE3_GRANT_PERIOD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE3_GRANT_PERIOD_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE3_GRANT_PERIOD_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE3_GRANT_PERIOD_GRANT_PERIOD_BMSK                                0x3ff
#define HWIO_BIMC_M_APP_MPORT_BKE3_GRANT_PERIOD_GRANT_PERIOD_SHFT                                  0x0

#define HWIO_BIMC_M_APP_MPORT_BKE3_GRANT_COUNT_ADDR                                         (BIMC_M_APP_MPORT_REG_BASE      + 0x00000a08)
#define HWIO_BIMC_M_APP_MPORT_BKE3_GRANT_COUNT_RMSK                                             0xffff
#define HWIO_BIMC_M_APP_MPORT_BKE3_GRANT_COUNT_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE3_GRANT_COUNT_ADDR, HWIO_BIMC_M_APP_MPORT_BKE3_GRANT_COUNT_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE3_GRANT_COUNT_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE3_GRANT_COUNT_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE3_GRANT_COUNT_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE3_GRANT_COUNT_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE3_GRANT_COUNT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE3_GRANT_COUNT_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE3_GRANT_COUNT_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE3_GRANT_COUNT_GRANT_COUNT_BMSK                                 0xffff
#define HWIO_BIMC_M_APP_MPORT_BKE3_GRANT_COUNT_GRANT_COUNT_SHFT                                    0x0

#define HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_HIGH_ADDR                                      (BIMC_M_APP_MPORT_REG_BASE      + 0x00000a20)
#define HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_HIGH_RMSK                                          0xffff
#define HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_HIGH_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_HIGH_ADDR, HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_HIGH_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_HIGH_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_HIGH_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_HIGH_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_HIGH_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_HIGH_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_HIGH_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_HIGH_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_HIGH_THRESHOLD_BMSK                                0xffff
#define HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_HIGH_THRESHOLD_SHFT                                   0x0

#define HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_MEDIUM_ADDR                                    (BIMC_M_APP_MPORT_REG_BASE      + 0x00000a24)
#define HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_MEDIUM_RMSK                                        0xffff
#define HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_MEDIUM_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_MEDIUM_ADDR, HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_MEDIUM_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_MEDIUM_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_MEDIUM_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_MEDIUM_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_MEDIUM_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_MEDIUM_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_MEDIUM_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_MEDIUM_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_MEDIUM_THRESHOLD_BMSK                              0xffff
#define HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_MEDIUM_THRESHOLD_SHFT                                 0x0

#define HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_LOW_ADDR                                       (BIMC_M_APP_MPORT_REG_BASE      + 0x00000a28)
#define HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_LOW_RMSK                                           0xffff
#define HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_LOW_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_LOW_ADDR, HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_LOW_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_LOW_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_LOW_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_LOW_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_LOW_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_LOW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_LOW_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_LOW_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_LOW_THRESHOLD_BMSK                                 0xffff
#define HWIO_BIMC_M_APP_MPORT_BKE3_THRESHOLD_LOW_THRESHOLD_SHFT                                    0x0

#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_0_ADDR                                            (BIMC_M_APP_MPORT_REG_BASE      + 0x00000a40)
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_0_RMSK                                            0x80000303
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_0_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_0_ADDR, HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_0_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_0_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_0_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_0_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_0_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_0_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_0_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_0_LIMIT_COMMANDS_BMSK                             0x80000000
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_0_LIMIT_COMMANDS_SHFT                                   0x1f
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_0_AREQPRIORITY_BMSK                                    0x300
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_0_AREQPRIORITY_SHFT                                      0x8
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_0_PRIORITYLVL_BMSK                                       0x3
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_0_PRIORITYLVL_SHFT                                       0x0

#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_1_ADDR                                            (BIMC_M_APP_MPORT_REG_BASE      + 0x00000a44)
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_1_RMSK                                            0x80000303
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_1_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_1_ADDR, HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_1_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_1_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_1_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_1_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_1_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_1_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_1_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_1_LIMIT_COMMANDS_BMSK                             0x80000000
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_1_LIMIT_COMMANDS_SHFT                                   0x1f
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_1_AREQPRIORITY_BMSK                                    0x300
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_1_AREQPRIORITY_SHFT                                      0x8
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_1_PRIORITYLVL_BMSK                                       0x3
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_1_PRIORITYLVL_SHFT                                       0x0

#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_2_ADDR                                            (BIMC_M_APP_MPORT_REG_BASE      + 0x00000a48)
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_2_RMSK                                            0x80000303
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_2_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_2_ADDR, HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_2_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_2_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_2_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_2_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_2_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_2_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_2_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_2_LIMIT_COMMANDS_BMSK                             0x80000000
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_2_LIMIT_COMMANDS_SHFT                                   0x1f
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_2_AREQPRIORITY_BMSK                                    0x300
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_2_AREQPRIORITY_SHFT                                      0x8
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_2_PRIORITYLVL_BMSK                                       0x3
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_2_PRIORITYLVL_SHFT                                       0x0

#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_3_ADDR                                            (BIMC_M_APP_MPORT_REG_BASE      + 0x00000a4c)
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_3_RMSK                                                 0x303
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_3_IN          \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_3_ADDR, HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_3_RMSK)
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_3_INM(m)      \
        in_dword_masked(HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_3_ADDR, m)
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_3_OUT(v)      \
        out_dword(HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_3_ADDR,v)
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_3_ADDR,m,v,HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_3_IN)
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_3_AREQPRIORITY_BMSK                                    0x300
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_3_AREQPRIORITY_SHFT                                      0x8
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_3_PRIORITYLVL_BMSK                                       0x3
#define HWIO_BIMC_M_APP_MPORT_BKE3_HEALTH_3_PRIORITYLVL_SHFT                                       0x0


#endif /* __DDR_HWIO_H__ */
