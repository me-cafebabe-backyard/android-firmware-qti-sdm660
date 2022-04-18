#ifndef __HWIO_LPASS_QOS_H__
#define __HWIO_LPASS_QOS_H__
/*
===========================================================================
*/
/**
  @file hwio_lpass_qos.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    SDM660 (Starlord) [starlord_v1.0_p3q2r79]
 
  This file contains HWIO register definitions for the following modules:
    LPASS_QOS_QOS_DANGER

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

  $Header: //components/rel/core.qdsp6/1.0.c2/power/dangergen/src/core/inc/hwio_lpass_qos.h#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $

  ===========================================================================
*/

/*----------------------------------------------------------------------------
 * MODULE: LPASS_QOS_QOS_DANGER
 *--------------------------------------------------------------------------*/

#define LPASS_QOS_QOS_DANGER_REG_BASE                                 (LPASS_BASE      + 0x000b0300)
#define LPASS_QOS_QOS_DANGER_REG_BASE_OFFS                            0x000b0300

#define HWIO_LPASS_QOS_LAT0_QTIMER_START_ADDR                         (LPASS_QOS_QOS_DANGER_REG_BASE      + 0x0000002c)
#define HWIO_LPASS_QOS_LAT0_QTIMER_START_OFFS                         (LPASS_QOS_QOS_DANGER_REG_BASE_OFFS + 0x0000002c)
#define HWIO_LPASS_QOS_LAT0_QTIMER_START_RMSK                         0xffffffff
#define HWIO_LPASS_QOS_LAT0_QTIMER_START_POR                          0x00000000
#define HWIO_LPASS_QOS_LAT0_QTIMER_START_POR_RMSK                     0xffffffff
#define HWIO_LPASS_QOS_LAT0_QTIMER_START_IN          \
        in_dword_masked(HWIO_LPASS_QOS_LAT0_QTIMER_START_ADDR, HWIO_LPASS_QOS_LAT0_QTIMER_START_RMSK)
#define HWIO_LPASS_QOS_LAT0_QTIMER_START_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_LAT0_QTIMER_START_ADDR, m)
#define HWIO_LPASS_QOS_LAT0_QTIMER_START_MSB_BMSK                     0xffffffff
#define HWIO_LPASS_QOS_LAT0_QTIMER_START_MSB_SHFT                            0x0

#define HWIO_LPASS_QOS_LAT0_QTIMER_END_ADDR                           (LPASS_QOS_QOS_DANGER_REG_BASE      + 0x00000030)
#define HWIO_LPASS_QOS_LAT0_QTIMER_END_OFFS                           (LPASS_QOS_QOS_DANGER_REG_BASE_OFFS + 0x00000030)
#define HWIO_LPASS_QOS_LAT0_QTIMER_END_RMSK                           0xffffffff
#define HWIO_LPASS_QOS_LAT0_QTIMER_END_POR                            0x00000000
#define HWIO_LPASS_QOS_LAT0_QTIMER_END_POR_RMSK                       0xffffffff
#define HWIO_LPASS_QOS_LAT0_QTIMER_END_IN          \
        in_dword_masked(HWIO_LPASS_QOS_LAT0_QTIMER_END_ADDR, HWIO_LPASS_QOS_LAT0_QTIMER_END_RMSK)
#define HWIO_LPASS_QOS_LAT0_QTIMER_END_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_LAT0_QTIMER_END_ADDR, m)
#define HWIO_LPASS_QOS_LAT0_QTIMER_END_MSB_BMSK                       0xffffffff
#define HWIO_LPASS_QOS_LAT0_QTIMER_END_MSB_SHFT                              0x0

#define HWIO_LPASS_QOS_LAT1_QTIMER_START_ADDR                         (LPASS_QOS_QOS_DANGER_REG_BASE      + 0x0000005c)
#define HWIO_LPASS_QOS_LAT1_QTIMER_START_OFFS                         (LPASS_QOS_QOS_DANGER_REG_BASE_OFFS + 0x0000005c)
#define HWIO_LPASS_QOS_LAT1_QTIMER_START_RMSK                         0xffffffff
#define HWIO_LPASS_QOS_LAT1_QTIMER_START_POR                          0x00000000
#define HWIO_LPASS_QOS_LAT1_QTIMER_START_POR_RMSK                     0xffffffff
#define HWIO_LPASS_QOS_LAT1_QTIMER_START_IN          \
        in_dword_masked(HWIO_LPASS_QOS_LAT1_QTIMER_START_ADDR, HWIO_LPASS_QOS_LAT1_QTIMER_START_RMSK)
#define HWIO_LPASS_QOS_LAT1_QTIMER_START_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_LAT1_QTIMER_START_ADDR, m)
#define HWIO_LPASS_QOS_LAT1_QTIMER_START_MSB_BMSK                     0xffffffff
#define HWIO_LPASS_QOS_LAT1_QTIMER_START_MSB_SHFT                            0x0

#define HWIO_LPASS_QOS_LAT1_QTIMER_END_ADDR                           (LPASS_QOS_QOS_DANGER_REG_BASE      + 0x00000060)
#define HWIO_LPASS_QOS_LAT1_QTIMER_END_OFFS                           (LPASS_QOS_QOS_DANGER_REG_BASE_OFFS + 0x00000060)
#define HWIO_LPASS_QOS_LAT1_QTIMER_END_RMSK                           0xffffffff
#define HWIO_LPASS_QOS_LAT1_QTIMER_END_POR                            0x00000000
#define HWIO_LPASS_QOS_LAT1_QTIMER_END_POR_RMSK                       0xffffffff
#define HWIO_LPASS_QOS_LAT1_QTIMER_END_IN          \
        in_dword_masked(HWIO_LPASS_QOS_LAT1_QTIMER_END_ADDR, HWIO_LPASS_QOS_LAT1_QTIMER_END_RMSK)
#define HWIO_LPASS_QOS_LAT1_QTIMER_END_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_LAT1_QTIMER_END_ADDR, m)
#define HWIO_LPASS_QOS_LAT1_QTIMER_END_MSB_BMSK                       0xffffffff
#define HWIO_LPASS_QOS_LAT1_QTIMER_END_MSB_SHFT                              0x0

#define HWIO_LPASS_QOS_LAT2_QTIMER_START_ADDR                         (LPASS_QOS_QOS_DANGER_REG_BASE      + 0x0000009c)
#define HWIO_LPASS_QOS_LAT2_QTIMER_START_OFFS                         (LPASS_QOS_QOS_DANGER_REG_BASE_OFFS + 0x0000009c)
#define HWIO_LPASS_QOS_LAT2_QTIMER_START_RMSK                         0xffffffff
#define HWIO_LPASS_QOS_LAT2_QTIMER_START_POR                          0x00000000
#define HWIO_LPASS_QOS_LAT2_QTIMER_START_POR_RMSK                     0xffffffff
#define HWIO_LPASS_QOS_LAT2_QTIMER_START_IN          \
        in_dword_masked(HWIO_LPASS_QOS_LAT2_QTIMER_START_ADDR, HWIO_LPASS_QOS_LAT2_QTIMER_START_RMSK)
#define HWIO_LPASS_QOS_LAT2_QTIMER_START_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_LAT2_QTIMER_START_ADDR, m)
#define HWIO_LPASS_QOS_LAT2_QTIMER_START_MSB_BMSK                     0xffffffff
#define HWIO_LPASS_QOS_LAT2_QTIMER_START_MSB_SHFT                            0x0

#define HWIO_LPASS_QOS_LAT2_QTIMER_END_ADDR                           (LPASS_QOS_QOS_DANGER_REG_BASE      + 0x000000a0)
#define HWIO_LPASS_QOS_LAT2_QTIMER_END_OFFS                           (LPASS_QOS_QOS_DANGER_REG_BASE_OFFS + 0x000000a0)
#define HWIO_LPASS_QOS_LAT2_QTIMER_END_RMSK                           0xffffffff
#define HWIO_LPASS_QOS_LAT2_QTIMER_END_POR                            0x00000000
#define HWIO_LPASS_QOS_LAT2_QTIMER_END_POR_RMSK                       0xffffffff
#define HWIO_LPASS_QOS_LAT2_QTIMER_END_IN          \
        in_dword_masked(HWIO_LPASS_QOS_LAT2_QTIMER_END_ADDR, HWIO_LPASS_QOS_LAT2_QTIMER_END_RMSK)
#define HWIO_LPASS_QOS_LAT2_QTIMER_END_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_LAT2_QTIMER_END_ADDR, m)
#define HWIO_LPASS_QOS_LAT2_QTIMER_END_MSB_BMSK                       0xffffffff
#define HWIO_LPASS_QOS_LAT2_QTIMER_END_MSB_SHFT                              0x0

#define HWIO_LPASS_QOS_LAT3_QTIMER_START_ADDR                         (LPASS_QOS_QOS_DANGER_REG_BASE      + 0x000000dc)
#define HWIO_LPASS_QOS_LAT3_QTIMER_START_OFFS                         (LPASS_QOS_QOS_DANGER_REG_BASE_OFFS + 0x000000dc)
#define HWIO_LPASS_QOS_LAT3_QTIMER_START_RMSK                         0xffffffff
#define HWIO_LPASS_QOS_LAT3_QTIMER_START_POR                          0x00000000
#define HWIO_LPASS_QOS_LAT3_QTIMER_START_POR_RMSK                     0xffffffff
#define HWIO_LPASS_QOS_LAT3_QTIMER_START_IN          \
        in_dword_masked(HWIO_LPASS_QOS_LAT3_QTIMER_START_ADDR, HWIO_LPASS_QOS_LAT3_QTIMER_START_RMSK)
#define HWIO_LPASS_QOS_LAT3_QTIMER_START_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_LAT3_QTIMER_START_ADDR, m)
#define HWIO_LPASS_QOS_LAT3_QTIMER_START_MSB_BMSK                     0xffffffff
#define HWIO_LPASS_QOS_LAT3_QTIMER_START_MSB_SHFT                            0x0

#define HWIO_LPASS_QOS_LAT3_QTIMER_END_ADDR                           (LPASS_QOS_QOS_DANGER_REG_BASE      + 0x000000e0)
#define HWIO_LPASS_QOS_LAT3_QTIMER_END_OFFS                           (LPASS_QOS_QOS_DANGER_REG_BASE_OFFS + 0x000000e0)
#define HWIO_LPASS_QOS_LAT3_QTIMER_END_RMSK                           0xffffffff
#define HWIO_LPASS_QOS_LAT3_QTIMER_END_POR                            0x00000000
#define HWIO_LPASS_QOS_LAT3_QTIMER_END_POR_RMSK                       0xffffffff
#define HWIO_LPASS_QOS_LAT3_QTIMER_END_IN          \
        in_dword_masked(HWIO_LPASS_QOS_LAT3_QTIMER_END_ADDR, HWIO_LPASS_QOS_LAT3_QTIMER_END_RMSK)
#define HWIO_LPASS_QOS_LAT3_QTIMER_END_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_LAT3_QTIMER_END_ADDR, m)
#define HWIO_LPASS_QOS_LAT3_QTIMER_END_MSB_BMSK                       0xffffffff
#define HWIO_LPASS_QOS_LAT3_QTIMER_END_MSB_SHFT                              0x0

#define HWIO_LPASS_QOS_CNT0_MONITOR_ADDR                              (LPASS_QOS_QOS_DANGER_REG_BASE      + 0x00000100)
#define HWIO_LPASS_QOS_CNT0_MONITOR_OFFS                              (LPASS_QOS_QOS_DANGER_REG_BASE_OFFS + 0x00000100)
#define HWIO_LPASS_QOS_CNT0_MONITOR_RMSK                               0x3333b01
#define HWIO_LPASS_QOS_CNT0_MONITOR_POR                               0x03210000
#define HWIO_LPASS_QOS_CNT0_MONITOR_POR_RMSK                          0xffffffff
#define HWIO_LPASS_QOS_CNT0_MONITOR_IN          \
        in_dword_masked(HWIO_LPASS_QOS_CNT0_MONITOR_ADDR, HWIO_LPASS_QOS_CNT0_MONITOR_RMSK)
#define HWIO_LPASS_QOS_CNT0_MONITOR_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_CNT0_MONITOR_ADDR, m)
#define HWIO_LPASS_QOS_CNT0_MONITOR_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_CNT0_MONITOR_ADDR,v)
#define HWIO_LPASS_QOS_CNT0_MONITOR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_CNT0_MONITOR_ADDR,m,v,HWIO_LPASS_QOS_CNT0_MONITOR_IN)
#define HWIO_LPASS_QOS_CNT0_MONITOR_DEF_DANGER_LEVEL_3_BMSK            0x3000000
#define HWIO_LPASS_QOS_CNT0_MONITOR_DEF_DANGER_LEVEL_3_SHFT                 0x18
#define HWIO_LPASS_QOS_CNT0_MONITOR_DEF_DANGER_LEVEL_2_BMSK             0x300000
#define HWIO_LPASS_QOS_CNT0_MONITOR_DEF_DANGER_LEVEL_2_SHFT                 0x14
#define HWIO_LPASS_QOS_CNT0_MONITOR_DEF_DANGER_LEVEL_1_BMSK              0x30000
#define HWIO_LPASS_QOS_CNT0_MONITOR_DEF_DANGER_LEVEL_1_SHFT                 0x10
#define HWIO_LPASS_QOS_CNT0_MONITOR_DEF_DANGER_LEVEL_0_BMSK               0x3000
#define HWIO_LPASS_QOS_CNT0_MONITOR_DEF_DANGER_LEVEL_0_SHFT                  0xc
#define HWIO_LPASS_QOS_CNT0_MONITOR_SW_DANGER_OVERRIDE_BMSK                0x800
#define HWIO_LPASS_QOS_CNT0_MONITOR_SW_DANGER_OVERRIDE_SHFT                  0xb
#define HWIO_LPASS_QOS_CNT0_MONITOR_SW_DANGER_LEVEL_BMSK                   0x300
#define HWIO_LPASS_QOS_CNT0_MONITOR_SW_DANGER_LEVEL_SHFT                     0x8
#define HWIO_LPASS_QOS_CNT0_MONITOR_MONITOR_EN_BMSK                          0x1
#define HWIO_LPASS_QOS_CNT0_MONITOR_MONITOR_EN_SHFT                          0x0

#define HWIO_LPASS_QOS_CNT0_COUNTER_ADDR                              (LPASS_QOS_QOS_DANGER_REG_BASE      + 0x00000104)
#define HWIO_LPASS_QOS_CNT0_COUNTER_OFFS                              (LPASS_QOS_QOS_DANGER_REG_BASE_OFFS + 0x00000104)
#define HWIO_LPASS_QOS_CNT0_COUNTER_RMSK                              0xffff0011
#define HWIO_LPASS_QOS_CNT0_COUNTER_POR                               0x4b000000
#define HWIO_LPASS_QOS_CNT0_COUNTER_POR_RMSK                          0xffffffff
#define HWIO_LPASS_QOS_CNT0_COUNTER_IN          \
        in_dword_masked(HWIO_LPASS_QOS_CNT0_COUNTER_ADDR, HWIO_LPASS_QOS_CNT0_COUNTER_RMSK)
#define HWIO_LPASS_QOS_CNT0_COUNTER_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_CNT0_COUNTER_ADDR, m)
#define HWIO_LPASS_QOS_CNT0_COUNTER_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_CNT0_COUNTER_ADDR,v)
#define HWIO_LPASS_QOS_CNT0_COUNTER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_CNT0_COUNTER_ADDR,m,v,HWIO_LPASS_QOS_CNT0_COUNTER_IN)
#define HWIO_LPASS_QOS_CNT0_COUNTER_CNT_SUB_CONST_BMSK                0xffff0000
#define HWIO_LPASS_QOS_CNT0_COUNTER_CNT_SUB_CONST_SHFT                      0x10
#define HWIO_LPASS_QOS_CNT0_COUNTER_CNT_SUB_MODE_BMSK                       0x10
#define HWIO_LPASS_QOS_CNT0_COUNTER_CNT_SUB_MODE_SHFT                        0x4
#define HWIO_LPASS_QOS_CNT0_COUNTER_CNT_RESET_BMSK                           0x1
#define HWIO_LPASS_QOS_CNT0_COUNTER_CNT_RESET_SHFT                           0x0

#define HWIO_LPASS_QOS_CNT0_WINDOW_ADDR                               (LPASS_QOS_QOS_DANGER_REG_BASE      + 0x00000108)
#define HWIO_LPASS_QOS_CNT0_WINDOW_OFFS                               (LPASS_QOS_QOS_DANGER_REG_BASE_OFFS + 0x00000108)
#define HWIO_LPASS_QOS_CNT0_WINDOW_RMSK                                0xfffffff
#define HWIO_LPASS_QOS_CNT0_WINDOW_POR                                0x00000000
#define HWIO_LPASS_QOS_CNT0_WINDOW_POR_RMSK                           0xffffffff
#define HWIO_LPASS_QOS_CNT0_WINDOW_IN          \
        in_dword_masked(HWIO_LPASS_QOS_CNT0_WINDOW_ADDR, HWIO_LPASS_QOS_CNT0_WINDOW_RMSK)
#define HWIO_LPASS_QOS_CNT0_WINDOW_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_CNT0_WINDOW_ADDR, m)
#define HWIO_LPASS_QOS_CNT0_WINDOW_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_CNT0_WINDOW_ADDR,v)
#define HWIO_LPASS_QOS_CNT0_WINDOW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_CNT0_WINDOW_ADDR,m,v,HWIO_LPASS_QOS_CNT0_WINDOW_IN)
#define HWIO_LPASS_QOS_CNT0_WINDOW_WINDOW_BMSK                         0xfffffff
#define HWIO_LPASS_QOS_CNT0_WINDOW_WINDOW_SHFT                               0x0

#define HWIO_LPASS_QOS_CNT0_THRESHOLD0_ADDR                           (LPASS_QOS_QOS_DANGER_REG_BASE      + 0x0000010c)
#define HWIO_LPASS_QOS_CNT0_THRESHOLD0_OFFS                           (LPASS_QOS_QOS_DANGER_REG_BASE_OFFS + 0x0000010c)
#define HWIO_LPASS_QOS_CNT0_THRESHOLD0_RMSK                            0xfffff00
#define HWIO_LPASS_QOS_CNT0_THRESHOLD0_POR                            0x00000000
#define HWIO_LPASS_QOS_CNT0_THRESHOLD0_POR_RMSK                       0xffffffff
#define HWIO_LPASS_QOS_CNT0_THRESHOLD0_IN          \
        in_dword_masked(HWIO_LPASS_QOS_CNT0_THRESHOLD0_ADDR, HWIO_LPASS_QOS_CNT0_THRESHOLD0_RMSK)
#define HWIO_LPASS_QOS_CNT0_THRESHOLD0_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_CNT0_THRESHOLD0_ADDR, m)
#define HWIO_LPASS_QOS_CNT0_THRESHOLD0_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_CNT0_THRESHOLD0_ADDR,v)
#define HWIO_LPASS_QOS_CNT0_THRESHOLD0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_CNT0_THRESHOLD0_ADDR,m,v,HWIO_LPASS_QOS_CNT0_THRESHOLD0_IN)
#define HWIO_LPASS_QOS_CNT0_THRESHOLD0_THRESHOLD0_BMSK                 0xfffff00
#define HWIO_LPASS_QOS_CNT0_THRESHOLD0_THRESHOLD0_SHFT                       0x8

#define HWIO_LPASS_QOS_CNT0_THRESHOLD1_ADDR                           (LPASS_QOS_QOS_DANGER_REG_BASE      + 0x00000110)
#define HWIO_LPASS_QOS_CNT0_THRESHOLD1_OFFS                           (LPASS_QOS_QOS_DANGER_REG_BASE_OFFS + 0x00000110)
#define HWIO_LPASS_QOS_CNT0_THRESHOLD1_RMSK                            0xfffff00
#define HWIO_LPASS_QOS_CNT0_THRESHOLD1_POR                            0x00000000
#define HWIO_LPASS_QOS_CNT0_THRESHOLD1_POR_RMSK                       0xffffffff
#define HWIO_LPASS_QOS_CNT0_THRESHOLD1_IN          \
        in_dword_masked(HWIO_LPASS_QOS_CNT0_THRESHOLD1_ADDR, HWIO_LPASS_QOS_CNT0_THRESHOLD1_RMSK)
#define HWIO_LPASS_QOS_CNT0_THRESHOLD1_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_CNT0_THRESHOLD1_ADDR, m)
#define HWIO_LPASS_QOS_CNT0_THRESHOLD1_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_CNT0_THRESHOLD1_ADDR,v)
#define HWIO_LPASS_QOS_CNT0_THRESHOLD1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_CNT0_THRESHOLD1_ADDR,m,v,HWIO_LPASS_QOS_CNT0_THRESHOLD1_IN)
#define HWIO_LPASS_QOS_CNT0_THRESHOLD1_THRESHOLD1_BMSK                 0xfffff00
#define HWIO_LPASS_QOS_CNT0_THRESHOLD1_THRESHOLD1_SHFT                       0x8

#define HWIO_LPASS_QOS_CNT0_THRESHOLD2_ADDR                           (LPASS_QOS_QOS_DANGER_REG_BASE      + 0x00000114)
#define HWIO_LPASS_QOS_CNT0_THRESHOLD2_OFFS                           (LPASS_QOS_QOS_DANGER_REG_BASE_OFFS + 0x00000114)
#define HWIO_LPASS_QOS_CNT0_THRESHOLD2_RMSK                            0xfffff00
#define HWIO_LPASS_QOS_CNT0_THRESHOLD2_POR                            0x00000000
#define HWIO_LPASS_QOS_CNT0_THRESHOLD2_POR_RMSK                       0xffffffff
#define HWIO_LPASS_QOS_CNT0_THRESHOLD2_IN          \
        in_dword_masked(HWIO_LPASS_QOS_CNT0_THRESHOLD2_ADDR, HWIO_LPASS_QOS_CNT0_THRESHOLD2_RMSK)
#define HWIO_LPASS_QOS_CNT0_THRESHOLD2_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_CNT0_THRESHOLD2_ADDR, m)
#define HWIO_LPASS_QOS_CNT0_THRESHOLD2_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_CNT0_THRESHOLD2_ADDR,v)
#define HWIO_LPASS_QOS_CNT0_THRESHOLD2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_CNT0_THRESHOLD2_ADDR,m,v,HWIO_LPASS_QOS_CNT0_THRESHOLD2_IN)
#define HWIO_LPASS_QOS_CNT0_THRESHOLD2_THRESHOLD2_BMSK                 0xfffff00
#define HWIO_LPASS_QOS_CNT0_THRESHOLD2_THRESHOLD2_SHFT                       0x8

#define HWIO_LPASS_QOS_CNT0_CNT_VALUE_ADDR                            (LPASS_QOS_QOS_DANGER_REG_BASE      + 0x00000118)
#define HWIO_LPASS_QOS_CNT0_CNT_VALUE_OFFS                            (LPASS_QOS_QOS_DANGER_REG_BASE_OFFS + 0x00000118)
#define HWIO_LPASS_QOS_CNT0_CNT_VALUE_RMSK                            0x8fffffff
#define HWIO_LPASS_QOS_CNT0_CNT_VALUE_POR                             0x00000000
#define HWIO_LPASS_QOS_CNT0_CNT_VALUE_POR_RMSK                        0xffffffff
#define HWIO_LPASS_QOS_CNT0_CNT_VALUE_IN          \
        in_dword_masked(HWIO_LPASS_QOS_CNT0_CNT_VALUE_ADDR, HWIO_LPASS_QOS_CNT0_CNT_VALUE_RMSK)
#define HWIO_LPASS_QOS_CNT0_CNT_VALUE_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_CNT0_CNT_VALUE_ADDR, m)
#define HWIO_LPASS_QOS_CNT0_CNT_VALUE_MAX_COUNT_REACHED_BMSK          0x80000000
#define HWIO_LPASS_QOS_CNT0_CNT_VALUE_MAX_COUNT_REACHED_SHFT                0x1f
#define HWIO_LPASS_QOS_CNT0_CNT_VALUE_CNT_BMSK                         0xfffffff
#define HWIO_LPASS_QOS_CNT0_CNT_VALUE_CNT_SHFT                               0x0

#define HWIO_LPASS_QOS_CNT1_MONITOR_ADDR                              (LPASS_QOS_QOS_DANGER_REG_BASE      + 0x00000120)
#define HWIO_LPASS_QOS_CNT1_MONITOR_OFFS                              (LPASS_QOS_QOS_DANGER_REG_BASE_OFFS + 0x00000120)
#define HWIO_LPASS_QOS_CNT1_MONITOR_RMSK                               0x3333b01
#define HWIO_LPASS_QOS_CNT1_MONITOR_POR                               0x03210000
#define HWIO_LPASS_QOS_CNT1_MONITOR_POR_RMSK                          0xffffffff
#define HWIO_LPASS_QOS_CNT1_MONITOR_IN          \
        in_dword_masked(HWIO_LPASS_QOS_CNT1_MONITOR_ADDR, HWIO_LPASS_QOS_CNT1_MONITOR_RMSK)
#define HWIO_LPASS_QOS_CNT1_MONITOR_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_CNT1_MONITOR_ADDR, m)
#define HWIO_LPASS_QOS_CNT1_MONITOR_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_CNT1_MONITOR_ADDR,v)
#define HWIO_LPASS_QOS_CNT1_MONITOR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_CNT1_MONITOR_ADDR,m,v,HWIO_LPASS_QOS_CNT1_MONITOR_IN)
#define HWIO_LPASS_QOS_CNT1_MONITOR_DEF_DANGER_LEVEL_3_BMSK            0x3000000
#define HWIO_LPASS_QOS_CNT1_MONITOR_DEF_DANGER_LEVEL_3_SHFT                 0x18
#define HWIO_LPASS_QOS_CNT1_MONITOR_DEF_DANGER_LEVEL_2_BMSK             0x300000
#define HWIO_LPASS_QOS_CNT1_MONITOR_DEF_DANGER_LEVEL_2_SHFT                 0x14
#define HWIO_LPASS_QOS_CNT1_MONITOR_DEF_DANGER_LEVEL_1_BMSK              0x30000
#define HWIO_LPASS_QOS_CNT1_MONITOR_DEF_DANGER_LEVEL_1_SHFT                 0x10
#define HWIO_LPASS_QOS_CNT1_MONITOR_DEF_DANGER_LEVEL_0_BMSK               0x3000
#define HWIO_LPASS_QOS_CNT1_MONITOR_DEF_DANGER_LEVEL_0_SHFT                  0xc
#define HWIO_LPASS_QOS_CNT1_MONITOR_SW_DANGER_OVERRIDE_BMSK                0x800
#define HWIO_LPASS_QOS_CNT1_MONITOR_SW_DANGER_OVERRIDE_SHFT                  0xb
#define HWIO_LPASS_QOS_CNT1_MONITOR_SW_DANGER_LEVEL_BMSK                   0x300
#define HWIO_LPASS_QOS_CNT1_MONITOR_SW_DANGER_LEVEL_SHFT                     0x8
#define HWIO_LPASS_QOS_CNT1_MONITOR_MONITOR_EN_BMSK                          0x1
#define HWIO_LPASS_QOS_CNT1_MONITOR_MONITOR_EN_SHFT                          0x0

#define HWIO_LPASS_QOS_CNT1_COUNTER_ADDR                              (LPASS_QOS_QOS_DANGER_REG_BASE      + 0x00000124)
#define HWIO_LPASS_QOS_CNT1_COUNTER_OFFS                              (LPASS_QOS_QOS_DANGER_REG_BASE_OFFS + 0x00000124)
#define HWIO_LPASS_QOS_CNT1_COUNTER_RMSK                              0xffff0011
#define HWIO_LPASS_QOS_CNT1_COUNTER_POR                               0x4b000000
#define HWIO_LPASS_QOS_CNT1_COUNTER_POR_RMSK                          0xffffffff
#define HWIO_LPASS_QOS_CNT1_COUNTER_IN          \
        in_dword_masked(HWIO_LPASS_QOS_CNT1_COUNTER_ADDR, HWIO_LPASS_QOS_CNT1_COUNTER_RMSK)
#define HWIO_LPASS_QOS_CNT1_COUNTER_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_CNT1_COUNTER_ADDR, m)
#define HWIO_LPASS_QOS_CNT1_COUNTER_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_CNT1_COUNTER_ADDR,v)
#define HWIO_LPASS_QOS_CNT1_COUNTER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_CNT1_COUNTER_ADDR,m,v,HWIO_LPASS_QOS_CNT1_COUNTER_IN)
#define HWIO_LPASS_QOS_CNT1_COUNTER_CNT_SUB_CONST_BMSK                0xffff0000
#define HWIO_LPASS_QOS_CNT1_COUNTER_CNT_SUB_CONST_SHFT                      0x10
#define HWIO_LPASS_QOS_CNT1_COUNTER_CNT_SUB_MODE_BMSK                       0x10
#define HWIO_LPASS_QOS_CNT1_COUNTER_CNT_SUB_MODE_SHFT                        0x4
#define HWIO_LPASS_QOS_CNT1_COUNTER_CNT_RESET_BMSK                           0x1
#define HWIO_LPASS_QOS_CNT1_COUNTER_CNT_RESET_SHFT                           0x0

#define HWIO_LPASS_QOS_CNT1_WINDOW_ADDR                               (LPASS_QOS_QOS_DANGER_REG_BASE      + 0x00000128)
#define HWIO_LPASS_QOS_CNT1_WINDOW_OFFS                               (LPASS_QOS_QOS_DANGER_REG_BASE_OFFS + 0x00000128)
#define HWIO_LPASS_QOS_CNT1_WINDOW_RMSK                                0xfffffff
#define HWIO_LPASS_QOS_CNT1_WINDOW_POR                                0x00000000
#define HWIO_LPASS_QOS_CNT1_WINDOW_POR_RMSK                           0xffffffff
#define HWIO_LPASS_QOS_CNT1_WINDOW_IN          \
        in_dword_masked(HWIO_LPASS_QOS_CNT1_WINDOW_ADDR, HWIO_LPASS_QOS_CNT1_WINDOW_RMSK)
#define HWIO_LPASS_QOS_CNT1_WINDOW_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_CNT1_WINDOW_ADDR, m)
#define HWIO_LPASS_QOS_CNT1_WINDOW_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_CNT1_WINDOW_ADDR,v)
#define HWIO_LPASS_QOS_CNT1_WINDOW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_CNT1_WINDOW_ADDR,m,v,HWIO_LPASS_QOS_CNT1_WINDOW_IN)
#define HWIO_LPASS_QOS_CNT1_WINDOW_WINDOW_BMSK                         0xfffffff
#define HWIO_LPASS_QOS_CNT1_WINDOW_WINDOW_SHFT                               0x0

#define HWIO_LPASS_QOS_CNT1_THRESHOLD0_ADDR                           (LPASS_QOS_QOS_DANGER_REG_BASE      + 0x0000012c)
#define HWIO_LPASS_QOS_CNT1_THRESHOLD0_OFFS                           (LPASS_QOS_QOS_DANGER_REG_BASE_OFFS + 0x0000012c)
#define HWIO_LPASS_QOS_CNT1_THRESHOLD0_RMSK                            0xfffff00
#define HWIO_LPASS_QOS_CNT1_THRESHOLD0_POR                            0x00000000
#define HWIO_LPASS_QOS_CNT1_THRESHOLD0_POR_RMSK                       0xffffffff
#define HWIO_LPASS_QOS_CNT1_THRESHOLD0_IN          \
        in_dword_masked(HWIO_LPASS_QOS_CNT1_THRESHOLD0_ADDR, HWIO_LPASS_QOS_CNT1_THRESHOLD0_RMSK)
#define HWIO_LPASS_QOS_CNT1_THRESHOLD0_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_CNT1_THRESHOLD0_ADDR, m)
#define HWIO_LPASS_QOS_CNT1_THRESHOLD0_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_CNT1_THRESHOLD0_ADDR,v)
#define HWIO_LPASS_QOS_CNT1_THRESHOLD0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_CNT1_THRESHOLD0_ADDR,m,v,HWIO_LPASS_QOS_CNT1_THRESHOLD0_IN)
#define HWIO_LPASS_QOS_CNT1_THRESHOLD0_THRESHOLD0_BMSK                 0xfffff00
#define HWIO_LPASS_QOS_CNT1_THRESHOLD0_THRESHOLD0_SHFT                       0x8

#define HWIO_LPASS_QOS_CNT1_THRESHOLD1_ADDR                           (LPASS_QOS_QOS_DANGER_REG_BASE      + 0x00000130)
#define HWIO_LPASS_QOS_CNT1_THRESHOLD1_OFFS                           (LPASS_QOS_QOS_DANGER_REG_BASE_OFFS + 0x00000130)
#define HWIO_LPASS_QOS_CNT1_THRESHOLD1_RMSK                            0xfffff00
#define HWIO_LPASS_QOS_CNT1_THRESHOLD1_POR                            0x00000000
#define HWIO_LPASS_QOS_CNT1_THRESHOLD1_POR_RMSK                       0xffffffff
#define HWIO_LPASS_QOS_CNT1_THRESHOLD1_IN          \
        in_dword_masked(HWIO_LPASS_QOS_CNT1_THRESHOLD1_ADDR, HWIO_LPASS_QOS_CNT1_THRESHOLD1_RMSK)
#define HWIO_LPASS_QOS_CNT1_THRESHOLD1_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_CNT1_THRESHOLD1_ADDR, m)
#define HWIO_LPASS_QOS_CNT1_THRESHOLD1_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_CNT1_THRESHOLD1_ADDR,v)
#define HWIO_LPASS_QOS_CNT1_THRESHOLD1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_CNT1_THRESHOLD1_ADDR,m,v,HWIO_LPASS_QOS_CNT1_THRESHOLD1_IN)
#define HWIO_LPASS_QOS_CNT1_THRESHOLD1_THRESHOLD1_BMSK                 0xfffff00
#define HWIO_LPASS_QOS_CNT1_THRESHOLD1_THRESHOLD1_SHFT                       0x8

#define HWIO_LPASS_QOS_CNT1_THRESHOLD2_ADDR                           (LPASS_QOS_QOS_DANGER_REG_BASE      + 0x00000134)
#define HWIO_LPASS_QOS_CNT1_THRESHOLD2_OFFS                           (LPASS_QOS_QOS_DANGER_REG_BASE_OFFS + 0x00000134)
#define HWIO_LPASS_QOS_CNT1_THRESHOLD2_RMSK                            0xfffff00
#define HWIO_LPASS_QOS_CNT1_THRESHOLD2_POR                            0x00000000
#define HWIO_LPASS_QOS_CNT1_THRESHOLD2_POR_RMSK                       0xffffffff
#define HWIO_LPASS_QOS_CNT1_THRESHOLD2_IN          \
        in_dword_masked(HWIO_LPASS_QOS_CNT1_THRESHOLD2_ADDR, HWIO_LPASS_QOS_CNT1_THRESHOLD2_RMSK)
#define HWIO_LPASS_QOS_CNT1_THRESHOLD2_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_CNT1_THRESHOLD2_ADDR, m)
#define HWIO_LPASS_QOS_CNT1_THRESHOLD2_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_CNT1_THRESHOLD2_ADDR,v)
#define HWIO_LPASS_QOS_CNT1_THRESHOLD2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_CNT1_THRESHOLD2_ADDR,m,v,HWIO_LPASS_QOS_CNT1_THRESHOLD2_IN)
#define HWIO_LPASS_QOS_CNT1_THRESHOLD2_THRESHOLD2_BMSK                 0xfffff00
#define HWIO_LPASS_QOS_CNT1_THRESHOLD2_THRESHOLD2_SHFT                       0x8

#define HWIO_LPASS_QOS_CNT1_CNT_VALUE_ADDR                            (LPASS_QOS_QOS_DANGER_REG_BASE      + 0x00000138)
#define HWIO_LPASS_QOS_CNT1_CNT_VALUE_OFFS                            (LPASS_QOS_QOS_DANGER_REG_BASE_OFFS + 0x00000138)
#define HWIO_LPASS_QOS_CNT1_CNT_VALUE_RMSK                            0x8fffffff
#define HWIO_LPASS_QOS_CNT1_CNT_VALUE_POR                             0x00000000
#define HWIO_LPASS_QOS_CNT1_CNT_VALUE_POR_RMSK                        0xffffffff
#define HWIO_LPASS_QOS_CNT1_CNT_VALUE_IN          \
        in_dword_masked(HWIO_LPASS_QOS_CNT1_CNT_VALUE_ADDR, HWIO_LPASS_QOS_CNT1_CNT_VALUE_RMSK)
#define HWIO_LPASS_QOS_CNT1_CNT_VALUE_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_CNT1_CNT_VALUE_ADDR, m)
#define HWIO_LPASS_QOS_CNT1_CNT_VALUE_MAX_COUNT_REACHED_BMSK          0x80000000
#define HWIO_LPASS_QOS_CNT1_CNT_VALUE_MAX_COUNT_REACHED_SHFT                0x1f
#define HWIO_LPASS_QOS_CNT1_CNT_VALUE_CNT_BMSK                         0xfffffff
#define HWIO_LPASS_QOS_CNT1_CNT_VALUE_CNT_SHFT                               0x0

#define HWIO_LPASS_QOS_CNT2_MONITOR_ADDR                              (LPASS_QOS_QOS_DANGER_REG_BASE      + 0x00000140)
#define HWIO_LPASS_QOS_CNT2_MONITOR_OFFS                              (LPASS_QOS_QOS_DANGER_REG_BASE_OFFS + 0x00000140)
#define HWIO_LPASS_QOS_CNT2_MONITOR_RMSK                               0x3333b01
#define HWIO_LPASS_QOS_CNT2_MONITOR_POR                               0x03210000
#define HWIO_LPASS_QOS_CNT2_MONITOR_POR_RMSK                          0xffffffff
#define HWIO_LPASS_QOS_CNT2_MONITOR_IN          \
        in_dword_masked(HWIO_LPASS_QOS_CNT2_MONITOR_ADDR, HWIO_LPASS_QOS_CNT2_MONITOR_RMSK)
#define HWIO_LPASS_QOS_CNT2_MONITOR_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_CNT2_MONITOR_ADDR, m)
#define HWIO_LPASS_QOS_CNT2_MONITOR_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_CNT2_MONITOR_ADDR,v)
#define HWIO_LPASS_QOS_CNT2_MONITOR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_CNT2_MONITOR_ADDR,m,v,HWIO_LPASS_QOS_CNT2_MONITOR_IN)
#define HWIO_LPASS_QOS_CNT2_MONITOR_DEF_DANGER_LEVEL_3_BMSK            0x3000000
#define HWIO_LPASS_QOS_CNT2_MONITOR_DEF_DANGER_LEVEL_3_SHFT                 0x18
#define HWIO_LPASS_QOS_CNT2_MONITOR_DEF_DANGER_LEVEL_2_BMSK             0x300000
#define HWIO_LPASS_QOS_CNT2_MONITOR_DEF_DANGER_LEVEL_2_SHFT                 0x14
#define HWIO_LPASS_QOS_CNT2_MONITOR_DEF_DANGER_LEVEL_1_BMSK              0x30000
#define HWIO_LPASS_QOS_CNT2_MONITOR_DEF_DANGER_LEVEL_1_SHFT                 0x10
#define HWIO_LPASS_QOS_CNT2_MONITOR_DEF_DANGER_LEVEL_0_BMSK               0x3000
#define HWIO_LPASS_QOS_CNT2_MONITOR_DEF_DANGER_LEVEL_0_SHFT                  0xc
#define HWIO_LPASS_QOS_CNT2_MONITOR_SW_DANGER_OVERRIDE_BMSK                0x800
#define HWIO_LPASS_QOS_CNT2_MONITOR_SW_DANGER_OVERRIDE_SHFT                  0xb
#define HWIO_LPASS_QOS_CNT2_MONITOR_SW_DANGER_LEVEL_BMSK                   0x300
#define HWIO_LPASS_QOS_CNT2_MONITOR_SW_DANGER_LEVEL_SHFT                     0x8
#define HWIO_LPASS_QOS_CNT2_MONITOR_MONITOR_EN_BMSK                          0x1
#define HWIO_LPASS_QOS_CNT2_MONITOR_MONITOR_EN_SHFT                          0x0

#define HWIO_LPASS_QOS_CNT2_COUNTER_ADDR                              (LPASS_QOS_QOS_DANGER_REG_BASE      + 0x00000144)
#define HWIO_LPASS_QOS_CNT2_COUNTER_OFFS                              (LPASS_QOS_QOS_DANGER_REG_BASE_OFFS + 0x00000144)
#define HWIO_LPASS_QOS_CNT2_COUNTER_RMSK                              0xffff0011
#define HWIO_LPASS_QOS_CNT2_COUNTER_POR                               0x4b000000
#define HWIO_LPASS_QOS_CNT2_COUNTER_POR_RMSK                          0xffffffff
#define HWIO_LPASS_QOS_CNT2_COUNTER_IN          \
        in_dword_masked(HWIO_LPASS_QOS_CNT2_COUNTER_ADDR, HWIO_LPASS_QOS_CNT2_COUNTER_RMSK)
#define HWIO_LPASS_QOS_CNT2_COUNTER_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_CNT2_COUNTER_ADDR, m)
#define HWIO_LPASS_QOS_CNT2_COUNTER_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_CNT2_COUNTER_ADDR,v)
#define HWIO_LPASS_QOS_CNT2_COUNTER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_CNT2_COUNTER_ADDR,m,v,HWIO_LPASS_QOS_CNT2_COUNTER_IN)
#define HWIO_LPASS_QOS_CNT2_COUNTER_CNT_SUB_CONST_BMSK                0xffff0000
#define HWIO_LPASS_QOS_CNT2_COUNTER_CNT_SUB_CONST_SHFT                      0x10
#define HWIO_LPASS_QOS_CNT2_COUNTER_CNT_SUB_MODE_BMSK                       0x10
#define HWIO_LPASS_QOS_CNT2_COUNTER_CNT_SUB_MODE_SHFT                        0x4
#define HWIO_LPASS_QOS_CNT2_COUNTER_CNT_RESET_BMSK                           0x1
#define HWIO_LPASS_QOS_CNT2_COUNTER_CNT_RESET_SHFT                           0x0

#define HWIO_LPASS_QOS_CNT2_WINDOW_ADDR                               (LPASS_QOS_QOS_DANGER_REG_BASE      + 0x00000148)
#define HWIO_LPASS_QOS_CNT2_WINDOW_OFFS                               (LPASS_QOS_QOS_DANGER_REG_BASE_OFFS + 0x00000148)
#define HWIO_LPASS_QOS_CNT2_WINDOW_RMSK                                0xfffffff
#define HWIO_LPASS_QOS_CNT2_WINDOW_POR                                0x00000000
#define HWIO_LPASS_QOS_CNT2_WINDOW_POR_RMSK                           0xffffffff
#define HWIO_LPASS_QOS_CNT2_WINDOW_IN          \
        in_dword_masked(HWIO_LPASS_QOS_CNT2_WINDOW_ADDR, HWIO_LPASS_QOS_CNT2_WINDOW_RMSK)
#define HWIO_LPASS_QOS_CNT2_WINDOW_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_CNT2_WINDOW_ADDR, m)
#define HWIO_LPASS_QOS_CNT2_WINDOW_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_CNT2_WINDOW_ADDR,v)
#define HWIO_LPASS_QOS_CNT2_WINDOW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_CNT2_WINDOW_ADDR,m,v,HWIO_LPASS_QOS_CNT2_WINDOW_IN)
#define HWIO_LPASS_QOS_CNT2_WINDOW_WINDOW_BMSK                         0xfffffff
#define HWIO_LPASS_QOS_CNT2_WINDOW_WINDOW_SHFT                               0x0

#define HWIO_LPASS_QOS_CNT2_THRESHOLD0_ADDR                           (LPASS_QOS_QOS_DANGER_REG_BASE      + 0x0000014c)
#define HWIO_LPASS_QOS_CNT2_THRESHOLD0_OFFS                           (LPASS_QOS_QOS_DANGER_REG_BASE_OFFS + 0x0000014c)
#define HWIO_LPASS_QOS_CNT2_THRESHOLD0_RMSK                            0xfffff00
#define HWIO_LPASS_QOS_CNT2_THRESHOLD0_POR                            0x00000000
#define HWIO_LPASS_QOS_CNT2_THRESHOLD0_POR_RMSK                       0xffffffff
#define HWIO_LPASS_QOS_CNT2_THRESHOLD0_IN          \
        in_dword_masked(HWIO_LPASS_QOS_CNT2_THRESHOLD0_ADDR, HWIO_LPASS_QOS_CNT2_THRESHOLD0_RMSK)
#define HWIO_LPASS_QOS_CNT2_THRESHOLD0_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_CNT2_THRESHOLD0_ADDR, m)
#define HWIO_LPASS_QOS_CNT2_THRESHOLD0_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_CNT2_THRESHOLD0_ADDR,v)
#define HWIO_LPASS_QOS_CNT2_THRESHOLD0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_CNT2_THRESHOLD0_ADDR,m,v,HWIO_LPASS_QOS_CNT2_THRESHOLD0_IN)
#define HWIO_LPASS_QOS_CNT2_THRESHOLD0_THRESHOLD0_BMSK                 0xfffff00
#define HWIO_LPASS_QOS_CNT2_THRESHOLD0_THRESHOLD0_SHFT                       0x8

#define HWIO_LPASS_QOS_CNT2_THRESHOLD1_ADDR                           (LPASS_QOS_QOS_DANGER_REG_BASE      + 0x00000150)
#define HWIO_LPASS_QOS_CNT2_THRESHOLD1_OFFS                           (LPASS_QOS_QOS_DANGER_REG_BASE_OFFS + 0x00000150)
#define HWIO_LPASS_QOS_CNT2_THRESHOLD1_RMSK                            0xfffff00
#define HWIO_LPASS_QOS_CNT2_THRESHOLD1_POR                            0x00000000
#define HWIO_LPASS_QOS_CNT2_THRESHOLD1_POR_RMSK                       0xffffffff
#define HWIO_LPASS_QOS_CNT2_THRESHOLD1_IN          \
        in_dword_masked(HWIO_LPASS_QOS_CNT2_THRESHOLD1_ADDR, HWIO_LPASS_QOS_CNT2_THRESHOLD1_RMSK)
#define HWIO_LPASS_QOS_CNT2_THRESHOLD1_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_CNT2_THRESHOLD1_ADDR, m)
#define HWIO_LPASS_QOS_CNT2_THRESHOLD1_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_CNT2_THRESHOLD1_ADDR,v)
#define HWIO_LPASS_QOS_CNT2_THRESHOLD1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_CNT2_THRESHOLD1_ADDR,m,v,HWIO_LPASS_QOS_CNT2_THRESHOLD1_IN)
#define HWIO_LPASS_QOS_CNT2_THRESHOLD1_THRESHOLD1_BMSK                 0xfffff00
#define HWIO_LPASS_QOS_CNT2_THRESHOLD1_THRESHOLD1_SHFT                       0x8

#define HWIO_LPASS_QOS_CNT2_THRESHOLD2_ADDR                           (LPASS_QOS_QOS_DANGER_REG_BASE      + 0x00000154)
#define HWIO_LPASS_QOS_CNT2_THRESHOLD2_OFFS                           (LPASS_QOS_QOS_DANGER_REG_BASE_OFFS + 0x00000154)
#define HWIO_LPASS_QOS_CNT2_THRESHOLD2_RMSK                            0xfffff00
#define HWIO_LPASS_QOS_CNT2_THRESHOLD2_POR                            0x00000000
#define HWIO_LPASS_QOS_CNT2_THRESHOLD2_POR_RMSK                       0xffffffff
#define HWIO_LPASS_QOS_CNT2_THRESHOLD2_IN          \
        in_dword_masked(HWIO_LPASS_QOS_CNT2_THRESHOLD2_ADDR, HWIO_LPASS_QOS_CNT2_THRESHOLD2_RMSK)
#define HWIO_LPASS_QOS_CNT2_THRESHOLD2_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_CNT2_THRESHOLD2_ADDR, m)
#define HWIO_LPASS_QOS_CNT2_THRESHOLD2_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_CNT2_THRESHOLD2_ADDR,v)
#define HWIO_LPASS_QOS_CNT2_THRESHOLD2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_CNT2_THRESHOLD2_ADDR,m,v,HWIO_LPASS_QOS_CNT2_THRESHOLD2_IN)
#define HWIO_LPASS_QOS_CNT2_THRESHOLD2_THRESHOLD2_BMSK                 0xfffff00
#define HWIO_LPASS_QOS_CNT2_THRESHOLD2_THRESHOLD2_SHFT                       0x8

#define HWIO_LPASS_QOS_CNT2_CNT_VALUE_ADDR                            (LPASS_QOS_QOS_DANGER_REG_BASE      + 0x00000158)
#define HWIO_LPASS_QOS_CNT2_CNT_VALUE_OFFS                            (LPASS_QOS_QOS_DANGER_REG_BASE_OFFS + 0x00000158)
#define HWIO_LPASS_QOS_CNT2_CNT_VALUE_RMSK                            0x8fffffff
#define HWIO_LPASS_QOS_CNT2_CNT_VALUE_POR                             0x00000000
#define HWIO_LPASS_QOS_CNT2_CNT_VALUE_POR_RMSK                        0xffffffff
#define HWIO_LPASS_QOS_CNT2_CNT_VALUE_IN          \
        in_dword_masked(HWIO_LPASS_QOS_CNT2_CNT_VALUE_ADDR, HWIO_LPASS_QOS_CNT2_CNT_VALUE_RMSK)
#define HWIO_LPASS_QOS_CNT2_CNT_VALUE_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_CNT2_CNT_VALUE_ADDR, m)
#define HWIO_LPASS_QOS_CNT2_CNT_VALUE_MAX_COUNT_REACHED_BMSK          0x80000000
#define HWIO_LPASS_QOS_CNT2_CNT_VALUE_MAX_COUNT_REACHED_SHFT                0x1f
#define HWIO_LPASS_QOS_CNT2_CNT_VALUE_CNT_BMSK                         0xfffffff
#define HWIO_LPASS_QOS_CNT2_CNT_VALUE_CNT_SHFT                               0x0

#define HWIO_LPASS_QOS_CNT3_MONITOR_ADDR                              (LPASS_QOS_QOS_DANGER_REG_BASE      + 0x00000160)
#define HWIO_LPASS_QOS_CNT3_MONITOR_OFFS                              (LPASS_QOS_QOS_DANGER_REG_BASE_OFFS + 0x00000160)
#define HWIO_LPASS_QOS_CNT3_MONITOR_RMSK                               0x3333b01
#define HWIO_LPASS_QOS_CNT3_MONITOR_POR                               0x03210000
#define HWIO_LPASS_QOS_CNT3_MONITOR_POR_RMSK                          0xffffffff
#define HWIO_LPASS_QOS_CNT3_MONITOR_IN          \
        in_dword_masked(HWIO_LPASS_QOS_CNT3_MONITOR_ADDR, HWIO_LPASS_QOS_CNT3_MONITOR_RMSK)
#define HWIO_LPASS_QOS_CNT3_MONITOR_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_CNT3_MONITOR_ADDR, m)
#define HWIO_LPASS_QOS_CNT3_MONITOR_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_CNT3_MONITOR_ADDR,v)
#define HWIO_LPASS_QOS_CNT3_MONITOR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_CNT3_MONITOR_ADDR,m,v,HWIO_LPASS_QOS_CNT3_MONITOR_IN)
#define HWIO_LPASS_QOS_CNT3_MONITOR_DEF_DANGER_LEVEL_3_BMSK            0x3000000
#define HWIO_LPASS_QOS_CNT3_MONITOR_DEF_DANGER_LEVEL_3_SHFT                 0x18
#define HWIO_LPASS_QOS_CNT3_MONITOR_DEF_DANGER_LEVEL_2_BMSK             0x300000
#define HWIO_LPASS_QOS_CNT3_MONITOR_DEF_DANGER_LEVEL_2_SHFT                 0x14
#define HWIO_LPASS_QOS_CNT3_MONITOR_DEF_DANGER_LEVEL_1_BMSK              0x30000
#define HWIO_LPASS_QOS_CNT3_MONITOR_DEF_DANGER_LEVEL_1_SHFT                 0x10
#define HWIO_LPASS_QOS_CNT3_MONITOR_DEF_DANGER_LEVEL_0_BMSK               0x3000
#define HWIO_LPASS_QOS_CNT3_MONITOR_DEF_DANGER_LEVEL_0_SHFT                  0xc
#define HWIO_LPASS_QOS_CNT3_MONITOR_SW_DANGER_OVERRIDE_BMSK                0x800
#define HWIO_LPASS_QOS_CNT3_MONITOR_SW_DANGER_OVERRIDE_SHFT                  0xb
#define HWIO_LPASS_QOS_CNT3_MONITOR_SW_DANGER_LEVEL_BMSK                   0x300
#define HWIO_LPASS_QOS_CNT3_MONITOR_SW_DANGER_LEVEL_SHFT                     0x8
#define HWIO_LPASS_QOS_CNT3_MONITOR_MONITOR_EN_BMSK                          0x1
#define HWIO_LPASS_QOS_CNT3_MONITOR_MONITOR_EN_SHFT                          0x0

#define HWIO_LPASS_QOS_CNT3_COUNTER_ADDR                              (LPASS_QOS_QOS_DANGER_REG_BASE      + 0x00000164)
#define HWIO_LPASS_QOS_CNT3_COUNTER_OFFS                              (LPASS_QOS_QOS_DANGER_REG_BASE_OFFS + 0x00000164)
#define HWIO_LPASS_QOS_CNT3_COUNTER_RMSK                              0xffff0011
#define HWIO_LPASS_QOS_CNT3_COUNTER_POR                               0x4b000000
#define HWIO_LPASS_QOS_CNT3_COUNTER_POR_RMSK                          0xffffffff
#define HWIO_LPASS_QOS_CNT3_COUNTER_IN          \
        in_dword_masked(HWIO_LPASS_QOS_CNT3_COUNTER_ADDR, HWIO_LPASS_QOS_CNT3_COUNTER_RMSK)
#define HWIO_LPASS_QOS_CNT3_COUNTER_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_CNT3_COUNTER_ADDR, m)
#define HWIO_LPASS_QOS_CNT3_COUNTER_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_CNT3_COUNTER_ADDR,v)
#define HWIO_LPASS_QOS_CNT3_COUNTER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_CNT3_COUNTER_ADDR,m,v,HWIO_LPASS_QOS_CNT3_COUNTER_IN)
#define HWIO_LPASS_QOS_CNT3_COUNTER_CNT_SUB_CONST_BMSK                0xffff0000
#define HWIO_LPASS_QOS_CNT3_COUNTER_CNT_SUB_CONST_SHFT                      0x10
#define HWIO_LPASS_QOS_CNT3_COUNTER_CNT_SUB_MODE_BMSK                       0x10
#define HWIO_LPASS_QOS_CNT3_COUNTER_CNT_SUB_MODE_SHFT                        0x4
#define HWIO_LPASS_QOS_CNT3_COUNTER_CNT_RESET_BMSK                           0x1
#define HWIO_LPASS_QOS_CNT3_COUNTER_CNT_RESET_SHFT                           0x0

#define HWIO_LPASS_QOS_CNT3_WINDOW_ADDR                               (LPASS_QOS_QOS_DANGER_REG_BASE      + 0x00000168)
#define HWIO_LPASS_QOS_CNT3_WINDOW_OFFS                               (LPASS_QOS_QOS_DANGER_REG_BASE_OFFS + 0x00000168)
#define HWIO_LPASS_QOS_CNT3_WINDOW_RMSK                                0xfffffff
#define HWIO_LPASS_QOS_CNT3_WINDOW_POR                                0x00000000
#define HWIO_LPASS_QOS_CNT3_WINDOW_POR_RMSK                           0xffffffff
#define HWIO_LPASS_QOS_CNT3_WINDOW_IN          \
        in_dword_masked(HWIO_LPASS_QOS_CNT3_WINDOW_ADDR, HWIO_LPASS_QOS_CNT3_WINDOW_RMSK)
#define HWIO_LPASS_QOS_CNT3_WINDOW_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_CNT3_WINDOW_ADDR, m)
#define HWIO_LPASS_QOS_CNT3_WINDOW_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_CNT3_WINDOW_ADDR,v)
#define HWIO_LPASS_QOS_CNT3_WINDOW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_CNT3_WINDOW_ADDR,m,v,HWIO_LPASS_QOS_CNT3_WINDOW_IN)
#define HWIO_LPASS_QOS_CNT3_WINDOW_WINDOW_BMSK                         0xfffffff
#define HWIO_LPASS_QOS_CNT3_WINDOW_WINDOW_SHFT                               0x0

#define HWIO_LPASS_QOS_CNT3_THRESHOLD0_ADDR                           (LPASS_QOS_QOS_DANGER_REG_BASE      + 0x0000016c)
#define HWIO_LPASS_QOS_CNT3_THRESHOLD0_OFFS                           (LPASS_QOS_QOS_DANGER_REG_BASE_OFFS + 0x0000016c)
#define HWIO_LPASS_QOS_CNT3_THRESHOLD0_RMSK                            0xfffff00
#define HWIO_LPASS_QOS_CNT3_THRESHOLD0_POR                            0x00000000
#define HWIO_LPASS_QOS_CNT3_THRESHOLD0_POR_RMSK                       0xffffffff
#define HWIO_LPASS_QOS_CNT3_THRESHOLD0_IN          \
        in_dword_masked(HWIO_LPASS_QOS_CNT3_THRESHOLD0_ADDR, HWIO_LPASS_QOS_CNT3_THRESHOLD0_RMSK)
#define HWIO_LPASS_QOS_CNT3_THRESHOLD0_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_CNT3_THRESHOLD0_ADDR, m)
#define HWIO_LPASS_QOS_CNT3_THRESHOLD0_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_CNT3_THRESHOLD0_ADDR,v)
#define HWIO_LPASS_QOS_CNT3_THRESHOLD0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_CNT3_THRESHOLD0_ADDR,m,v,HWIO_LPASS_QOS_CNT3_THRESHOLD0_IN)
#define HWIO_LPASS_QOS_CNT3_THRESHOLD0_THRESHOLD0_BMSK                 0xfffff00
#define HWIO_LPASS_QOS_CNT3_THRESHOLD0_THRESHOLD0_SHFT                       0x8

#define HWIO_LPASS_QOS_CNT3_THRESHOLD1_ADDR                           (LPASS_QOS_QOS_DANGER_REG_BASE      + 0x00000170)
#define HWIO_LPASS_QOS_CNT3_THRESHOLD1_OFFS                           (LPASS_QOS_QOS_DANGER_REG_BASE_OFFS + 0x00000170)
#define HWIO_LPASS_QOS_CNT3_THRESHOLD1_RMSK                            0xfffff00
#define HWIO_LPASS_QOS_CNT3_THRESHOLD1_POR                            0x00000000
#define HWIO_LPASS_QOS_CNT3_THRESHOLD1_POR_RMSK                       0xffffffff
#define HWIO_LPASS_QOS_CNT3_THRESHOLD1_IN          \
        in_dword_masked(HWIO_LPASS_QOS_CNT3_THRESHOLD1_ADDR, HWIO_LPASS_QOS_CNT3_THRESHOLD1_RMSK)
#define HWIO_LPASS_QOS_CNT3_THRESHOLD1_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_CNT3_THRESHOLD1_ADDR, m)
#define HWIO_LPASS_QOS_CNT3_THRESHOLD1_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_CNT3_THRESHOLD1_ADDR,v)
#define HWIO_LPASS_QOS_CNT3_THRESHOLD1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_CNT3_THRESHOLD1_ADDR,m,v,HWIO_LPASS_QOS_CNT3_THRESHOLD1_IN)
#define HWIO_LPASS_QOS_CNT3_THRESHOLD1_THRESHOLD1_BMSK                 0xfffff00
#define HWIO_LPASS_QOS_CNT3_THRESHOLD1_THRESHOLD1_SHFT                       0x8

#define HWIO_LPASS_QOS_CNT3_THRESHOLD2_ADDR                           (LPASS_QOS_QOS_DANGER_REG_BASE      + 0x00000174)
#define HWIO_LPASS_QOS_CNT3_THRESHOLD2_OFFS                           (LPASS_QOS_QOS_DANGER_REG_BASE_OFFS + 0x00000174)
#define HWIO_LPASS_QOS_CNT3_THRESHOLD2_RMSK                            0xfffff00
#define HWIO_LPASS_QOS_CNT3_THRESHOLD2_POR                            0x00000000
#define HWIO_LPASS_QOS_CNT3_THRESHOLD2_POR_RMSK                       0xffffffff
#define HWIO_LPASS_QOS_CNT3_THRESHOLD2_IN          \
        in_dword_masked(HWIO_LPASS_QOS_CNT3_THRESHOLD2_ADDR, HWIO_LPASS_QOS_CNT3_THRESHOLD2_RMSK)
#define HWIO_LPASS_QOS_CNT3_THRESHOLD2_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_CNT3_THRESHOLD2_ADDR, m)
#define HWIO_LPASS_QOS_CNT3_THRESHOLD2_OUT(v)      \
        out_dword(HWIO_LPASS_QOS_CNT3_THRESHOLD2_ADDR,v)
#define HWIO_LPASS_QOS_CNT3_THRESHOLD2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_QOS_CNT3_THRESHOLD2_ADDR,m,v,HWIO_LPASS_QOS_CNT3_THRESHOLD2_IN)
#define HWIO_LPASS_QOS_CNT3_THRESHOLD2_THRESHOLD2_BMSK                 0xfffff00
#define HWIO_LPASS_QOS_CNT3_THRESHOLD2_THRESHOLD2_SHFT                       0x8

#define HWIO_LPASS_QOS_CNT3_CNT_VALUE_ADDR                            (LPASS_QOS_QOS_DANGER_REG_BASE      + 0x00000178)
#define HWIO_LPASS_QOS_CNT3_CNT_VALUE_OFFS                            (LPASS_QOS_QOS_DANGER_REG_BASE_OFFS + 0x00000178)
#define HWIO_LPASS_QOS_CNT3_CNT_VALUE_RMSK                            0x8fffffff
#define HWIO_LPASS_QOS_CNT3_CNT_VALUE_POR                             0x00000000
#define HWIO_LPASS_QOS_CNT3_CNT_VALUE_POR_RMSK                        0xffffffff
#define HWIO_LPASS_QOS_CNT3_CNT_VALUE_IN          \
        in_dword_masked(HWIO_LPASS_QOS_CNT3_CNT_VALUE_ADDR, HWIO_LPASS_QOS_CNT3_CNT_VALUE_RMSK)
#define HWIO_LPASS_QOS_CNT3_CNT_VALUE_INM(m)      \
        in_dword_masked(HWIO_LPASS_QOS_CNT3_CNT_VALUE_ADDR, m)
#define HWIO_LPASS_QOS_CNT3_CNT_VALUE_MAX_COUNT_REACHED_BMSK          0x80000000
#define HWIO_LPASS_QOS_CNT3_CNT_VALUE_MAX_COUNT_REACHED_SHFT                0x1f
#define HWIO_LPASS_QOS_CNT3_CNT_VALUE_CNT_BMSK                         0xfffffff
#define HWIO_LPASS_QOS_CNT3_CNT_VALUE_CNT_SHFT                               0x0


#endif /* __HWIO_LPASS_QOS_H__ */
