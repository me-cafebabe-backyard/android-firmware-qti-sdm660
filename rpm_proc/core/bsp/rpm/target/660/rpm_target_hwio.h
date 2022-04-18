#ifndef __RPM_TARGET_HWIO_H__
#define __RPM_TARGET_HWIO_H__
/*
===========================================================================
*/
/**
  @file rpm_target_hwio.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following modules:
    RPM_.+

  'Include' filters applied: <none>
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

  $Header: //components/rel/rpm.bf/1.8/core/bsp/rpm/target/660/rpm_target_hwio.h#2 $
  $DateTime: 2016/11/07 22:46:44 $
  $Author: pwbldsvc $

  ===========================================================================
*/

#include "msmhwiobase.h"

/*----------------------------------------------------------------------------
 * MODULE: RPM_DEC
 *--------------------------------------------------------------------------*/

#define RPM_DEC_REG_BASE                                                    (RPM_BASE      + 0x00080000)

#define HWIO_RPM_HW_VERSION_ADDR                                            (RPM_DEC_REG_BASE      + 0x00000000)
#define HWIO_RPM_HW_VERSION_RMSK                                            0xffffffff
#define HWIO_RPM_HW_VERSION_IN          \
        in_dword_masked(HWIO_RPM_HW_VERSION_ADDR, HWIO_RPM_HW_VERSION_RMSK)
#define HWIO_RPM_HW_VERSION_INM(m)      \
        in_dword_masked(HWIO_RPM_HW_VERSION_ADDR, m)
#define HWIO_RPM_HW_VERSION_MAJOR_BMSK                                      0xf0000000
#define HWIO_RPM_HW_VERSION_MAJOR_SHFT                                            0x1c
#define HWIO_RPM_HW_VERSION_MINOR_BMSK                                       0xfff0000
#define HWIO_RPM_HW_VERSION_MINOR_SHFT                                            0x10
#define HWIO_RPM_HW_VERSION_STEP_BMSK                                           0xffff
#define HWIO_RPM_HW_VERSION_STEP_SHFT                                              0x0

#define HWIO_RPM_WFI_CONFIG_ADDR                                            (RPM_DEC_REG_BASE      + 0x00000004)
#define HWIO_RPM_WFI_CONFIG_RMSK                                                   0x7
#define HWIO_RPM_WFI_CONFIG_IN          \
        in_dword_masked(HWIO_RPM_WFI_CONFIG_ADDR, HWIO_RPM_WFI_CONFIG_RMSK)
#define HWIO_RPM_WFI_CONFIG_INM(m)      \
        in_dword_masked(HWIO_RPM_WFI_CONFIG_ADDR, m)
#define HWIO_RPM_WFI_CONFIG_OUT(v)      \
        out_dword(HWIO_RPM_WFI_CONFIG_ADDR,v)
#define HWIO_RPM_WFI_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_WFI_CONFIG_ADDR,m,v,HWIO_RPM_WFI_CONFIG_IN)
#define HWIO_RPM_WFI_CONFIG_CHIP_SLEEP_UPON_WFI_BMSK                               0x4
#define HWIO_RPM_WFI_CONFIG_CHIP_SLEEP_UPON_WFI_SHFT                               0x2
#define HWIO_RPM_WFI_CONFIG_CHIP_SLEEP_UPON_WFI_NO_AFFECT_FVAL                     0x0
#define HWIO_RPM_WFI_CONFIG_CHIP_SLEEP_UPON_WFI_SLEEP_EN_FVAL                      0x1
#define HWIO_RPM_WFI_CONFIG_BUS_CLK_HALT_BMSK                                      0x2
#define HWIO_RPM_WFI_CONFIG_BUS_CLK_HALT_SHFT                                      0x1
#define HWIO_RPM_WFI_CONFIG_BUS_CLK_HALT_NO_AFFECT_FVAL                            0x0
#define HWIO_RPM_WFI_CONFIG_BUS_CLK_HALT_CLOCK_HALT_FVAL                           0x1
#define HWIO_RPM_WFI_CONFIG_PROC_CLK_HALT_BMSK                                     0x1
#define HWIO_RPM_WFI_CONFIG_PROC_CLK_HALT_SHFT                                     0x0
#define HWIO_RPM_WFI_CONFIG_PROC_CLK_HALT_NO_AFFECT_FVAL                           0x0
#define HWIO_RPM_WFI_CONFIG_PROC_CLK_HALT_CLOCK_HALT_FVAL                          0x1

#define HWIO_RPM_TIMERS_CLK_OFF_CTL_ADDR                                    (RPM_DEC_REG_BASE      + 0x00000008)
#define HWIO_RPM_TIMERS_CLK_OFF_CTL_RMSK                                           0x1
#define HWIO_RPM_TIMERS_CLK_OFF_CTL_IN          \
        in_dword_masked(HWIO_RPM_TIMERS_CLK_OFF_CTL_ADDR, HWIO_RPM_TIMERS_CLK_OFF_CTL_RMSK)
#define HWIO_RPM_TIMERS_CLK_OFF_CTL_INM(m)      \
        in_dword_masked(HWIO_RPM_TIMERS_CLK_OFF_CTL_ADDR, m)
#define HWIO_RPM_TIMERS_CLK_OFF_CTL_OUT(v)      \
        out_dword(HWIO_RPM_TIMERS_CLK_OFF_CTL_ADDR,v)
#define HWIO_RPM_TIMERS_CLK_OFF_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_TIMERS_CLK_OFF_CTL_ADDR,m,v,HWIO_RPM_TIMERS_CLK_OFF_CTL_IN)
#define HWIO_RPM_TIMERS_CLK_OFF_CTL_WDOG_TIMER_CLK_OFF_BMSK                        0x1
#define HWIO_RPM_TIMERS_CLK_OFF_CTL_WDOG_TIMER_CLK_OFF_SHFT                        0x0
#define HWIO_RPM_TIMERS_CLK_OFF_CTL_WDOG_TIMER_CLK_OFF_CLOCK_ON_FVAL               0x0
#define HWIO_RPM_TIMERS_CLK_OFF_CTL_WDOG_TIMER_CLK_OFF_CLOCK_OFF_FVAL              0x1

#define HWIO_RPM_IPC_ADDR                                                   (RPM_DEC_REG_BASE      + 0x0000000c)
#define HWIO_RPM_IPC_RMSK                                                   0xffffffff
#define HWIO_RPM_IPC_OUT(v)      \
        out_dword(HWIO_RPM_IPC_ADDR,v)
#define HWIO_RPM_IPC_VMM_IPC_BMSK                                           0xf0000000
#define HWIO_RPM_IPC_VMM_IPC_SHFT                                                 0x1c
#define HWIO_RPM_IPC_SSC_IPC_BMSK                                            0xf000000
#define HWIO_RPM_IPC_SSC_IPC_SHFT                                                 0x18
#define HWIO_RPM_IPC_TZ_IPC_BMSK                                              0xf00000
#define HWIO_RPM_IPC_TZ_IPC_SHFT                                                  0x14
#define HWIO_RPM_IPC_SPSS_IPC_BMSK                                             0xf0000
#define HWIO_RPM_IPC_SPSS_IPC_SHFT                                                0x10
#define HWIO_RPM_IPC_MPSS_IPC_BMSK                                              0xf000
#define HWIO_RPM_IPC_MPSS_IPC_SHFT                                                 0xc
#define HWIO_RPM_IPC_ADSP_IPC_BMSK                                               0xf00
#define HWIO_RPM_IPC_ADSP_IPC_SHFT                                                 0x8
#define HWIO_RPM_IPC_APCS_HLOS_IPC_BMSK                                           0xf0
#define HWIO_RPM_IPC_APCS_HLOS_IPC_SHFT                                            0x4
#define HWIO_RPM_IPC_RPM_RSRV_BMSK                                                 0xf
#define HWIO_RPM_IPC_RPM_RSRV_SHFT                                                 0x0

#define HWIO_RPM_GPO_WDATA_ADDR                                             (RPM_DEC_REG_BASE      + 0x00000010)
#define HWIO_RPM_GPO_WDATA_RMSK                                             0xffffffff
#define HWIO_RPM_GPO_WDATA_IN          \
        in_dword_masked(HWIO_RPM_GPO_WDATA_ADDR, HWIO_RPM_GPO_WDATA_RMSK)
#define HWIO_RPM_GPO_WDATA_INM(m)      \
        in_dword_masked(HWIO_RPM_GPO_WDATA_ADDR, m)
#define HWIO_RPM_GPO_WDATA_OUT(v)      \
        out_dword(HWIO_RPM_GPO_WDATA_ADDR,v)
#define HWIO_RPM_GPO_WDATA_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_GPO_WDATA_ADDR,m,v,HWIO_RPM_GPO_WDATA_IN)
#define HWIO_RPM_GPO_WDATA_WDATA_BMSK                                       0xffffffff
#define HWIO_RPM_GPO_WDATA_WDATA_SHFT                                              0x0

#define HWIO_RPM_GPO_WDSET_ADDR                                             (RPM_DEC_REG_BASE      + 0x00000014)
#define HWIO_RPM_GPO_WDSET_RMSK                                             0xffffffff
#define HWIO_RPM_GPO_WDSET_OUT(v)      \
        out_dword(HWIO_RPM_GPO_WDSET_ADDR,v)
#define HWIO_RPM_GPO_WDSET_WDSET_BMSK                                       0xffffffff
#define HWIO_RPM_GPO_WDSET_WDSET_SHFT                                              0x0
#define HWIO_RPM_GPO_WDSET_WDSET_DON_T_SET_FVAL                                    0x0
#define HWIO_RPM_GPO_WDSET_WDSET_SET_FVAL                                          0x1

#define HWIO_RPM_GPO_WDCLR_ADDR                                             (RPM_DEC_REG_BASE      + 0x00000018)
#define HWIO_RPM_GPO_WDCLR_RMSK                                             0xffffffff
#define HWIO_RPM_GPO_WDCLR_OUT(v)      \
        out_dword(HWIO_RPM_GPO_WDCLR_ADDR,v)
#define HWIO_RPM_GPO_WDCLR_WDCLR_BMSK                                       0xffffffff
#define HWIO_RPM_GPO_WDCLR_WDCLR_SHFT                                              0x0
#define HWIO_RPM_GPO_WDCLR_WDCLR_DON_T_CLEAR_FVAL                                  0x0
#define HWIO_RPM_GPO_WDCLR_WDCLR_CLEAR_FVAL                                        0x1

#define HWIO_RPM_SLAVES_CLK_GATING_ADDR                                     (RPM_DEC_REG_BASE      + 0x0000001c)
#define HWIO_RPM_SLAVES_CLK_GATING_RMSK                                            0xf
#define HWIO_RPM_SLAVES_CLK_GATING_IN          \
        in_dword_masked(HWIO_RPM_SLAVES_CLK_GATING_ADDR, HWIO_RPM_SLAVES_CLK_GATING_RMSK)
#define HWIO_RPM_SLAVES_CLK_GATING_INM(m)      \
        in_dword_masked(HWIO_RPM_SLAVES_CLK_GATING_ADDR, m)
#define HWIO_RPM_SLAVES_CLK_GATING_OUT(v)      \
        out_dword(HWIO_RPM_SLAVES_CLK_GATING_ADDR,v)
#define HWIO_RPM_SLAVES_CLK_GATING_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_SLAVES_CLK_GATING_ADDR,m,v,HWIO_RPM_SLAVES_CLK_GATING_IN)
#define HWIO_RPM_SLAVES_CLK_GATING_INTR_CLK_GATING_BMSK                            0x8
#define HWIO_RPM_SLAVES_CLK_GATING_INTR_CLK_GATING_SHFT                            0x3
#define HWIO_RPM_SLAVES_CLK_GATING_INTR_CLK_GATING_DYNAMIC_CLK_ON_FVAL             0x0
#define HWIO_RPM_SLAVES_CLK_GATING_INTR_CLK_GATING_CLOCK_ON_FVAL                   0x1
#define HWIO_RPM_SLAVES_CLK_GATING_RAM_CLK_GATING_BMSK                             0x4
#define HWIO_RPM_SLAVES_CLK_GATING_RAM_CLK_GATING_SHFT                             0x2
#define HWIO_RPM_SLAVES_CLK_GATING_RAM_CLK_GATING_DYNAMIC_CLK_ON_FVAL              0x0
#define HWIO_RPM_SLAVES_CLK_GATING_RAM_CLK_GATING_CLOCK_ON_FVAL                    0x1
#define HWIO_RPM_SLAVES_CLK_GATING_PERIPH_CLK_GATING_BMSK                          0x2
#define HWIO_RPM_SLAVES_CLK_GATING_PERIPH_CLK_GATING_SHFT                          0x1
#define HWIO_RPM_SLAVES_CLK_GATING_PERIPH_CLK_GATING_DYNAMIC_CLK_ON_FVAL           0x0
#define HWIO_RPM_SLAVES_CLK_GATING_PERIPH_CLK_GATING_CLOCK_ON_FVAL                 0x1
#define HWIO_RPM_SLAVES_CLK_GATING_SLP_WKUP_FSM_CLK_GATING_BMSK                    0x1
#define HWIO_RPM_SLAVES_CLK_GATING_SLP_WKUP_FSM_CLK_GATING_SHFT                    0x0
#define HWIO_RPM_SLAVES_CLK_GATING_SLP_WKUP_FSM_CLK_GATING_DYNAMIC_CLK_ON_FVAL        0x0
#define HWIO_RPM_SLAVES_CLK_GATING_SLP_WKUP_FSM_CLK_GATING_CLOCK_ON_FVAL           0x1

#define HWIO_RPM_INTR_POLARITY_0_ADDR                                       (RPM_DEC_REG_BASE      + 0x00000030)
#define HWIO_RPM_INTR_POLARITY_0_RMSK                                       0xffffffff
#define HWIO_RPM_INTR_POLARITY_0_IN          \
        in_dword_masked(HWIO_RPM_INTR_POLARITY_0_ADDR, HWIO_RPM_INTR_POLARITY_0_RMSK)
#define HWIO_RPM_INTR_POLARITY_0_INM(m)      \
        in_dword_masked(HWIO_RPM_INTR_POLARITY_0_ADDR, m)
#define HWIO_RPM_INTR_POLARITY_0_OUT(v)      \
        out_dword(HWIO_RPM_INTR_POLARITY_0_ADDR,v)
#define HWIO_RPM_INTR_POLARITY_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_INTR_POLARITY_0_ADDR,m,v,HWIO_RPM_INTR_POLARITY_0_IN)
#define HWIO_RPM_INTR_POLARITY_0_POLARITY_BMSK                              0xffffffff
#define HWIO_RPM_INTR_POLARITY_0_POLARITY_SHFT                                     0x0
#define HWIO_RPM_INTR_POLARITY_0_POLARITY_NEG_OR_LOW_FVAL                          0x0
#define HWIO_RPM_INTR_POLARITY_0_POLARITY_POS_OR_HIGH_FVAL                         0x1

#define HWIO_RPM_INTR_POLARITY_1_ADDR                                       (RPM_DEC_REG_BASE      + 0x00000034)
#define HWIO_RPM_INTR_POLARITY_1_RMSK                                       0xffffffff
#define HWIO_RPM_INTR_POLARITY_1_IN          \
        in_dword_masked(HWIO_RPM_INTR_POLARITY_1_ADDR, HWIO_RPM_INTR_POLARITY_1_RMSK)
#define HWIO_RPM_INTR_POLARITY_1_INM(m)      \
        in_dword_masked(HWIO_RPM_INTR_POLARITY_1_ADDR, m)
#define HWIO_RPM_INTR_POLARITY_1_OUT(v)      \
        out_dword(HWIO_RPM_INTR_POLARITY_1_ADDR,v)
#define HWIO_RPM_INTR_POLARITY_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_INTR_POLARITY_1_ADDR,m,v,HWIO_RPM_INTR_POLARITY_1_IN)
#define HWIO_RPM_INTR_POLARITY_1_POLARITY_BMSK                              0xffffffff
#define HWIO_RPM_INTR_POLARITY_1_POLARITY_SHFT                                     0x0
#define HWIO_RPM_INTR_POLARITY_1_POLARITY_NEG_OR_LOW_FVAL                          0x0
#define HWIO_RPM_INTR_POLARITY_1_POLARITY_POS_OR_HIGH_FVAL                         0x1

#define HWIO_RPM_INTR_EDG_LVL_0_ADDR                                        (RPM_DEC_REG_BASE      + 0x00000038)
#define HWIO_RPM_INTR_EDG_LVL_0_RMSK                                        0xffffffff
#define HWIO_RPM_INTR_EDG_LVL_0_IN          \
        in_dword_masked(HWIO_RPM_INTR_EDG_LVL_0_ADDR, HWIO_RPM_INTR_EDG_LVL_0_RMSK)
#define HWIO_RPM_INTR_EDG_LVL_0_INM(m)      \
        in_dword_masked(HWIO_RPM_INTR_EDG_LVL_0_ADDR, m)
#define HWIO_RPM_INTR_EDG_LVL_0_OUT(v)      \
        out_dword(HWIO_RPM_INTR_EDG_LVL_0_ADDR,v)
#define HWIO_RPM_INTR_EDG_LVL_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_INTR_EDG_LVL_0_ADDR,m,v,HWIO_RPM_INTR_EDG_LVL_0_IN)
#define HWIO_RPM_INTR_EDG_LVL_0_EDG_LVL_BMSK                                0xffffffff
#define HWIO_RPM_INTR_EDG_LVL_0_EDG_LVL_SHFT                                       0x0
#define HWIO_RPM_INTR_EDG_LVL_0_EDG_LVL_LEVEL_FVAL                                 0x0
#define HWIO_RPM_INTR_EDG_LVL_0_EDG_LVL_EDGE_FVAL                                  0x1

#define HWIO_RPM_INTR_EDG_LVL_1_ADDR                                        (RPM_DEC_REG_BASE      + 0x0000003c)
#define HWIO_RPM_INTR_EDG_LVL_1_RMSK                                        0xffffffff
#define HWIO_RPM_INTR_EDG_LVL_1_IN          \
        in_dword_masked(HWIO_RPM_INTR_EDG_LVL_1_ADDR, HWIO_RPM_INTR_EDG_LVL_1_RMSK)
#define HWIO_RPM_INTR_EDG_LVL_1_INM(m)      \
        in_dword_masked(HWIO_RPM_INTR_EDG_LVL_1_ADDR, m)
#define HWIO_RPM_INTR_EDG_LVL_1_OUT(v)      \
        out_dword(HWIO_RPM_INTR_EDG_LVL_1_ADDR,v)
#define HWIO_RPM_INTR_EDG_LVL_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_INTR_EDG_LVL_1_ADDR,m,v,HWIO_RPM_INTR_EDG_LVL_1_IN)
#define HWIO_RPM_INTR_EDG_LVL_1_EDG_LVL_BMSK                                0xffffffff
#define HWIO_RPM_INTR_EDG_LVL_1_EDG_LVL_SHFT                                       0x0
#define HWIO_RPM_INTR_EDG_LVL_1_EDG_LVL_LEVEL_FVAL                                 0x0
#define HWIO_RPM_INTR_EDG_LVL_1_EDG_LVL_EDGE_FVAL                                  0x1

#define HWIO_RPM_WDOG_RESET_ADDR                                            (RPM_DEC_REG_BASE      + 0x00000040)
#define HWIO_RPM_WDOG_RESET_RMSK                                                   0x3
#define HWIO_RPM_WDOG_RESET_IN          \
        in_dword_masked(HWIO_RPM_WDOG_RESET_ADDR, HWIO_RPM_WDOG_RESET_RMSK)
#define HWIO_RPM_WDOG_RESET_INM(m)      \
        in_dword_masked(HWIO_RPM_WDOG_RESET_ADDR, m)
#define HWIO_RPM_WDOG_RESET_OUT(v)      \
        out_dword(HWIO_RPM_WDOG_RESET_ADDR,v)
#define HWIO_RPM_WDOG_RESET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_WDOG_RESET_ADDR,m,v,HWIO_RPM_WDOG_RESET_IN)
#define HWIO_RPM_WDOG_RESET_SYNC_STATUS_BMSK                                       0x2
#define HWIO_RPM_WDOG_RESET_SYNC_STATUS_SHFT                                       0x1
#define HWIO_RPM_WDOG_RESET_WDOG_RESET_BMSK                                        0x1
#define HWIO_RPM_WDOG_RESET_WDOG_RESET_SHFT                                        0x0

#define HWIO_RPM_WDOG_CTRL_ADDR                                             (RPM_DEC_REG_BASE      + 0x00000044)
#define HWIO_RPM_WDOG_CTRL_RMSK                                                    0x3
#define HWIO_RPM_WDOG_CTRL_IN          \
        in_dword_masked(HWIO_RPM_WDOG_CTRL_ADDR, HWIO_RPM_WDOG_CTRL_RMSK)
#define HWIO_RPM_WDOG_CTRL_INM(m)      \
        in_dword_masked(HWIO_RPM_WDOG_CTRL_ADDR, m)
#define HWIO_RPM_WDOG_CTRL_OUT(v)      \
        out_dword(HWIO_RPM_WDOG_CTRL_ADDR,v)
#define HWIO_RPM_WDOG_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_WDOG_CTRL_ADDR,m,v,HWIO_RPM_WDOG_CTRL_IN)
#define HWIO_RPM_WDOG_CTRL_HW_WAKEUP_SLEEP_EN_BMSK                                 0x2
#define HWIO_RPM_WDOG_CTRL_HW_WAKEUP_SLEEP_EN_SHFT                                 0x1
#define HWIO_RPM_WDOG_CTRL_HW_WAKEUP_SLEEP_EN_DISABLE_FVAL                         0x0
#define HWIO_RPM_WDOG_CTRL_HW_WAKEUP_SLEEP_EN_ENABLE_FVAL                          0x1
#define HWIO_RPM_WDOG_CTRL_ENABLE_BMSK                                             0x1
#define HWIO_RPM_WDOG_CTRL_ENABLE_SHFT                                             0x0
#define HWIO_RPM_WDOG_CTRL_ENABLE_DISABLE_FVAL                                     0x0
#define HWIO_RPM_WDOG_CTRL_ENABLE_ENABLE_FVAL                                      0x1

#define HWIO_RPM_WDOG_STATUS_ADDR                                           (RPM_DEC_REG_BASE      + 0x00000048)
#define HWIO_RPM_WDOG_STATUS_RMSK                                             0x7fffff
#define HWIO_RPM_WDOG_STATUS_IN          \
        in_dword_masked(HWIO_RPM_WDOG_STATUS_ADDR, HWIO_RPM_WDOG_STATUS_RMSK)
#define HWIO_RPM_WDOG_STATUS_INM(m)      \
        in_dword_masked(HWIO_RPM_WDOG_STATUS_ADDR, m)
#define HWIO_RPM_WDOG_STATUS_WDOG_COUNT_BMSK                                  0x7ffff8
#define HWIO_RPM_WDOG_STATUS_WDOG_COUNT_SHFT                                       0x3
#define HWIO_RPM_WDOG_STATUS_WDOG_CNT_RESET_STATUS_BMSK                            0x4
#define HWIO_RPM_WDOG_STATUS_WDOG_CNT_RESET_STATUS_SHFT                            0x2
#define HWIO_RPM_WDOG_STATUS_WDOG_FROZEN_BMSK                                      0x2
#define HWIO_RPM_WDOG_STATUS_WDOG_FROZEN_SHFT                                      0x1
#define HWIO_RPM_WDOG_STATUS_WDOG_FROZEN_NOT_FROZEN_FVAL                           0x0
#define HWIO_RPM_WDOG_STATUS_WDOG_FROZEN_FROZEN_FVAL                               0x1
#define HWIO_RPM_WDOG_STATUS_WDOG_EXPIRED_STATUS_BMSK                              0x1
#define HWIO_RPM_WDOG_STATUS_WDOG_EXPIRED_STATUS_SHFT                              0x0
#define HWIO_RPM_WDOG_STATUS_WDOG_EXPIRED_STATUS_NOT_EXPIRED_FVAL                  0x0
#define HWIO_RPM_WDOG_STATUS_WDOG_EXPIRED_STATUS_EXPIRED_FVAL                      0x1

#define HWIO_RPM_WDOG_BARK_TIME_ADDR                                        (RPM_DEC_REG_BASE      + 0x0000004c)
#define HWIO_RPM_WDOG_BARK_TIME_RMSK                                          0x1fffff
#define HWIO_RPM_WDOG_BARK_TIME_IN          \
        in_dword_masked(HWIO_RPM_WDOG_BARK_TIME_ADDR, HWIO_RPM_WDOG_BARK_TIME_RMSK)
#define HWIO_RPM_WDOG_BARK_TIME_INM(m)      \
        in_dword_masked(HWIO_RPM_WDOG_BARK_TIME_ADDR, m)
#define HWIO_RPM_WDOG_BARK_TIME_OUT(v)      \
        out_dword(HWIO_RPM_WDOG_BARK_TIME_ADDR,v)
#define HWIO_RPM_WDOG_BARK_TIME_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_WDOG_BARK_TIME_ADDR,m,v,HWIO_RPM_WDOG_BARK_TIME_IN)
#define HWIO_RPM_WDOG_BARK_TIME_SYNC_STATUS_BMSK                              0x100000
#define HWIO_RPM_WDOG_BARK_TIME_SYNC_STATUS_SHFT                                  0x14
#define HWIO_RPM_WDOG_BARK_TIME_WDOG_BARK_VAL_BMSK                             0xfffff
#define HWIO_RPM_WDOG_BARK_TIME_WDOG_BARK_VAL_SHFT                                 0x0

#define HWIO_RPM_WDOG_BITE_TIME_ADDR                                        (RPM_DEC_REG_BASE      + 0x00000050)
#define HWIO_RPM_WDOG_BITE_TIME_RMSK                                          0x1fffff
#define HWIO_RPM_WDOG_BITE_TIME_IN          \
        in_dword_masked(HWIO_RPM_WDOG_BITE_TIME_ADDR, HWIO_RPM_WDOG_BITE_TIME_RMSK)
#define HWIO_RPM_WDOG_BITE_TIME_INM(m)      \
        in_dword_masked(HWIO_RPM_WDOG_BITE_TIME_ADDR, m)
#define HWIO_RPM_WDOG_BITE_TIME_OUT(v)      \
        out_dword(HWIO_RPM_WDOG_BITE_TIME_ADDR,v)
#define HWIO_RPM_WDOG_BITE_TIME_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_WDOG_BITE_TIME_ADDR,m,v,HWIO_RPM_WDOG_BITE_TIME_IN)
#define HWIO_RPM_WDOG_BITE_TIME_SYNC_STATUS_BMSK                              0x100000
#define HWIO_RPM_WDOG_BITE_TIME_SYNC_STATUS_SHFT                                  0x14
#define HWIO_RPM_WDOG_BITE_TIME_WDOG_BITE_VAL_BMSK                             0xfffff
#define HWIO_RPM_WDOG_BITE_TIME_WDOG_BITE_VAL_SHFT                                 0x0

#define HWIO_RPM_WDOG_TEST_LOAD_ADDR                                        (RPM_DEC_REG_BASE      + 0x00000054)
#define HWIO_RPM_WDOG_TEST_LOAD_RMSK                                               0x3
#define HWIO_RPM_WDOG_TEST_LOAD_IN          \
        in_dword_masked(HWIO_RPM_WDOG_TEST_LOAD_ADDR, HWIO_RPM_WDOG_TEST_LOAD_RMSK)
#define HWIO_RPM_WDOG_TEST_LOAD_INM(m)      \
        in_dword_masked(HWIO_RPM_WDOG_TEST_LOAD_ADDR, m)
#define HWIO_RPM_WDOG_TEST_LOAD_OUT(v)      \
        out_dword(HWIO_RPM_WDOG_TEST_LOAD_ADDR,v)
#define HWIO_RPM_WDOG_TEST_LOAD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_WDOG_TEST_LOAD_ADDR,m,v,HWIO_RPM_WDOG_TEST_LOAD_IN)
#define HWIO_RPM_WDOG_TEST_LOAD_SYNC_STATUS_BMSK                                   0x2
#define HWIO_RPM_WDOG_TEST_LOAD_SYNC_STATUS_SHFT                                   0x1
#define HWIO_RPM_WDOG_TEST_LOAD_LOAD_BMSK                                          0x1
#define HWIO_RPM_WDOG_TEST_LOAD_LOAD_SHFT                                          0x0

#define HWIO_RPM_WDOG_TEST_ADDR                                             (RPM_DEC_REG_BASE      + 0x00000058)
#define HWIO_RPM_WDOG_TEST_RMSK                                               0x1fffff
#define HWIO_RPM_WDOG_TEST_IN          \
        in_dword_masked(HWIO_RPM_WDOG_TEST_ADDR, HWIO_RPM_WDOG_TEST_RMSK)
#define HWIO_RPM_WDOG_TEST_INM(m)      \
        in_dword_masked(HWIO_RPM_WDOG_TEST_ADDR, m)
#define HWIO_RPM_WDOG_TEST_OUT(v)      \
        out_dword(HWIO_RPM_WDOG_TEST_ADDR,v)
#define HWIO_RPM_WDOG_TEST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_WDOG_TEST_ADDR,m,v,HWIO_RPM_WDOG_TEST_IN)
#define HWIO_RPM_WDOG_TEST_SYNC_STATUS_BMSK                                   0x100000
#define HWIO_RPM_WDOG_TEST_SYNC_STATUS_SHFT                                       0x14
#define HWIO_RPM_WDOG_TEST_LOAD_VALUE_BMSK                                     0xfffff
#define HWIO_RPM_WDOG_TEST_LOAD_VALUE_SHFT                                         0x0

#define HWIO_RPM_TEST_BUS_SEL_ADDR                                          (RPM_DEC_REG_BASE      + 0x0000005c)
#define HWIO_RPM_TEST_BUS_SEL_RMSK                                                 0xf
#define HWIO_RPM_TEST_BUS_SEL_IN          \
        in_dword_masked(HWIO_RPM_TEST_BUS_SEL_ADDR, HWIO_RPM_TEST_BUS_SEL_RMSK)
#define HWIO_RPM_TEST_BUS_SEL_INM(m)      \
        in_dword_masked(HWIO_RPM_TEST_BUS_SEL_ADDR, m)
#define HWIO_RPM_TEST_BUS_SEL_OUT(v)      \
        out_dword(HWIO_RPM_TEST_BUS_SEL_ADDR,v)
#define HWIO_RPM_TEST_BUS_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_TEST_BUS_SEL_ADDR,m,v,HWIO_RPM_TEST_BUS_SEL_IN)
#define HWIO_RPM_TEST_BUS_SEL_VAL_BMSK                                             0xf
#define HWIO_RPM_TEST_BUS_SEL_VAL_SHFT                                             0x0
#define HWIO_RPM_TEST_BUS_SEL_VAL_ALL_0_FVAL                                       0x0
#define HWIO_RPM_TEST_BUS_SEL_VAL_ALL_5_FVAL                                       0x1
#define HWIO_RPM_TEST_BUS_SEL_VAL_ALL_A_FVAL                                       0x2
#define HWIO_RPM_TEST_BUS_SEL_VAL_RPM_QTMR_TEST_BUS_FVAL                           0x3
#define HWIO_RPM_TEST_BUS_SEL_VAL_RPM_CSR_TEST_BUS_FVAL                            0x4
#define HWIO_RPM_TEST_BUS_SEL_VAL_RPM_M3_TEST_BUS_FVAL                             0x5
#define HWIO_RPM_TEST_BUS_SEL_VAL_RPM_LPAE_TEST_BUS_FVAL                           0x6
#define HWIO_RPM_TEST_BUS_SEL_VAL_RESERVED_7_FVAL                                  0x7
#define HWIO_RPM_TEST_BUS_SEL_VAL_NOC_MST_B2B_SLV_TEST_BUS_FVAL                    0x8
#define HWIO_RPM_TEST_BUS_SEL_VAL_NOC_MST_B2B_MST_TEST_BUS_FVAL                    0x9
#define HWIO_RPM_TEST_BUS_SEL_VAL_RPM_MST_B2B_SLV_TEST_BUS_FVAL                    0xa
#define HWIO_RPM_TEST_BUS_SEL_VAL_RPM_MST_B2B_MST_TEST_BUS_FVAL                    0xb

#define HWIO_RPM_SPARE_REG0_ADDR                                            (RPM_DEC_REG_BASE      + 0x00000060)
#define HWIO_RPM_SPARE_REG0_RMSK                                            0xffffffff
#define HWIO_RPM_SPARE_REG0_IN          \
        in_dword_masked(HWIO_RPM_SPARE_REG0_ADDR, HWIO_RPM_SPARE_REG0_RMSK)
#define HWIO_RPM_SPARE_REG0_INM(m)      \
        in_dword_masked(HWIO_RPM_SPARE_REG0_ADDR, m)
#define HWIO_RPM_SPARE_REG0_OUT(v)      \
        out_dword(HWIO_RPM_SPARE_REG0_ADDR,v)
#define HWIO_RPM_SPARE_REG0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_SPARE_REG0_ADDR,m,v,HWIO_RPM_SPARE_REG0_IN)
#define HWIO_RPM_SPARE_REG0_WDATA_BMSK                                      0xffffffff
#define HWIO_RPM_SPARE_REG0_WDATA_SHFT                                             0x0

#define HWIO_RPM_SPARE_REG1_ADDR                                            (RPM_DEC_REG_BASE      + 0x00000064)
#define HWIO_RPM_SPARE_REG1_RMSK                                            0xffffffff
#define HWIO_RPM_SPARE_REG1_IN          \
        in_dword_masked(HWIO_RPM_SPARE_REG1_ADDR, HWIO_RPM_SPARE_REG1_RMSK)
#define HWIO_RPM_SPARE_REG1_INM(m)      \
        in_dword_masked(HWIO_RPM_SPARE_REG1_ADDR, m)
#define HWIO_RPM_SPARE_REG1_OUT(v)      \
        out_dword(HWIO_RPM_SPARE_REG1_ADDR,v)
#define HWIO_RPM_SPARE_REG1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_SPARE_REG1_ADDR,m,v,HWIO_RPM_SPARE_REG1_IN)
#define HWIO_RPM_SPARE_REG1_WDATA_BMSK                                      0xffffffff
#define HWIO_RPM_SPARE_REG1_WDATA_SHFT                                             0x0

#define HWIO_RPM_SPARE_REG2_ADDR                                            (RPM_DEC_REG_BASE      + 0x00000068)
#define HWIO_RPM_SPARE_REG2_RMSK                                            0xffffffff
#define HWIO_RPM_SPARE_REG2_IN          \
        in_dword_masked(HWIO_RPM_SPARE_REG2_ADDR, HWIO_RPM_SPARE_REG2_RMSK)
#define HWIO_RPM_SPARE_REG2_INM(m)      \
        in_dword_masked(HWIO_RPM_SPARE_REG2_ADDR, m)
#define HWIO_RPM_SPARE_REG2_OUT(v)      \
        out_dword(HWIO_RPM_SPARE_REG2_ADDR,v)
#define HWIO_RPM_SPARE_REG2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_SPARE_REG2_ADDR,m,v,HWIO_RPM_SPARE_REG2_IN)
#define HWIO_RPM_SPARE_REG2_WDATA_BMSK                                      0xffffffff
#define HWIO_RPM_SPARE_REG2_WDATA_SHFT                                             0x0

#define HWIO_RPM_SPARE_REG3_ADDR                                            (RPM_DEC_REG_BASE      + 0x0000006c)
#define HWIO_RPM_SPARE_REG3_RMSK                                            0xffffffff
#define HWIO_RPM_SPARE_REG3_IN          \
        in_dword_masked(HWIO_RPM_SPARE_REG3_ADDR, HWIO_RPM_SPARE_REG3_RMSK)
#define HWIO_RPM_SPARE_REG3_INM(m)      \
        in_dword_masked(HWIO_RPM_SPARE_REG3_ADDR, m)
#define HWIO_RPM_SPARE_REG3_OUT(v)      \
        out_dword(HWIO_RPM_SPARE_REG3_ADDR,v)
#define HWIO_RPM_SPARE_REG3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_SPARE_REG3_ADDR,m,v,HWIO_RPM_SPARE_REG3_IN)
#define HWIO_RPM_SPARE_REG3_WDATA_BMSK                                      0xffffffff
#define HWIO_RPM_SPARE_REG3_WDATA_SHFT                                             0x0

#define HWIO_RPM_PAGE_SELECT_ADDR                                           (RPM_DEC_REG_BASE      + 0x00000070)
#define HWIO_RPM_PAGE_SELECT_RMSK                                                 0x3f
#define HWIO_RPM_PAGE_SELECT_IN          \
        in_dword_masked(HWIO_RPM_PAGE_SELECT_ADDR, HWIO_RPM_PAGE_SELECT_RMSK)
#define HWIO_RPM_PAGE_SELECT_INM(m)      \
        in_dword_masked(HWIO_RPM_PAGE_SELECT_ADDR, m)
#define HWIO_RPM_PAGE_SELECT_OUT(v)      \
        out_dword(HWIO_RPM_PAGE_SELECT_ADDR,v)
#define HWIO_RPM_PAGE_SELECT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_PAGE_SELECT_ADDR,m,v,HWIO_RPM_PAGE_SELECT_IN)
#define HWIO_RPM_PAGE_SELECT_PAGE_SELECT_BMSK                                     0x3f
#define HWIO_RPM_PAGE_SELECT_PAGE_SELECT_SHFT                                      0x0

#define HWIO_RPM_BRIDGES_CLK_GATING_ADDR                                    (RPM_DEC_REG_BASE      + 0x00000074)
#define HWIO_RPM_BRIDGES_CLK_GATING_RMSK                                           0x3
#define HWIO_RPM_BRIDGES_CLK_GATING_IN          \
        in_dword_masked(HWIO_RPM_BRIDGES_CLK_GATING_ADDR, HWIO_RPM_BRIDGES_CLK_GATING_RMSK)
#define HWIO_RPM_BRIDGES_CLK_GATING_INM(m)      \
        in_dword_masked(HWIO_RPM_BRIDGES_CLK_GATING_ADDR, m)
#define HWIO_RPM_BRIDGES_CLK_GATING_OUT(v)      \
        out_dword(HWIO_RPM_BRIDGES_CLK_GATING_ADDR,v)
#define HWIO_RPM_BRIDGES_CLK_GATING_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_BRIDGES_CLK_GATING_ADDR,m,v,HWIO_RPM_BRIDGES_CLK_GATING_IN)
#define HWIO_RPM_BRIDGES_CLK_GATING_RPM_BRIDGE_CLK_GATING_BMSK                     0x2
#define HWIO_RPM_BRIDGES_CLK_GATING_RPM_BRIDGE_CLK_GATING_SHFT                     0x1
#define HWIO_RPM_BRIDGES_CLK_GATING_RPM_BRIDGE_CLK_GATING_DYNAMIC_CLK_ON_FVAL        0x0
#define HWIO_RPM_BRIDGES_CLK_GATING_RPM_BRIDGE_CLK_GATING_CLOCK_ON_FVAL            0x1
#define HWIO_RPM_BRIDGES_CLK_GATING_NOC_BRIDGE_CLK_GATING_BMSK                     0x1
#define HWIO_RPM_BRIDGES_CLK_GATING_NOC_BRIDGE_CLK_GATING_SHFT                     0x0
#define HWIO_RPM_BRIDGES_CLK_GATING_NOC_BRIDGE_CLK_GATING_DYNAMIC_CLK_ON_FVAL        0x0
#define HWIO_RPM_BRIDGES_CLK_GATING_NOC_BRIDGE_CLK_GATING_CLOCK_ON_FVAL            0x1

#define HWIO_RPM_BRIDGES_HYSTERESIS_CNTR_ADDR                               (RPM_DEC_REG_BASE      + 0x00000078)
#define HWIO_RPM_BRIDGES_HYSTERESIS_CNTR_RMSK                               0x7fffffff
#define HWIO_RPM_BRIDGES_HYSTERESIS_CNTR_IN          \
        in_dword_masked(HWIO_RPM_BRIDGES_HYSTERESIS_CNTR_ADDR, HWIO_RPM_BRIDGES_HYSTERESIS_CNTR_RMSK)
#define HWIO_RPM_BRIDGES_HYSTERESIS_CNTR_INM(m)      \
        in_dword_masked(HWIO_RPM_BRIDGES_HYSTERESIS_CNTR_ADDR, m)
#define HWIO_RPM_BRIDGES_HYSTERESIS_CNTR_OUT(v)      \
        out_dword(HWIO_RPM_BRIDGES_HYSTERESIS_CNTR_ADDR,v)
#define HWIO_RPM_BRIDGES_HYSTERESIS_CNTR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_BRIDGES_HYSTERESIS_CNTR_ADDR,m,v,HWIO_RPM_BRIDGES_HYSTERESIS_CNTR_IN)
#define HWIO_RPM_BRIDGES_HYSTERESIS_CNTR_RPM_BRIDGE_HYST_CNTR_BMSK          0x7fff0000
#define HWIO_RPM_BRIDGES_HYSTERESIS_CNTR_RPM_BRIDGE_HYST_CNTR_SHFT                0x10
#define HWIO_RPM_BRIDGES_HYSTERESIS_CNTR_NOC_BRDG_SYNC_STATUS_BMSK              0x8000
#define HWIO_RPM_BRIDGES_HYSTERESIS_CNTR_NOC_BRDG_SYNC_STATUS_SHFT                 0xf
#define HWIO_RPM_BRIDGES_HYSTERESIS_CNTR_NOC_BRIDGE_HYST_CNTR_BMSK              0x7fff
#define HWIO_RPM_BRIDGES_HYSTERESIS_CNTR_NOC_BRIDGE_HYST_CNTR_SHFT                 0x0

#define HWIO_RPM_MISC_ADDR                                                  (RPM_DEC_REG_BASE      + 0x0000007c)
#define HWIO_RPM_MISC_RMSK                                                         0x3
#define HWIO_RPM_MISC_IN          \
        in_dword_masked(HWIO_RPM_MISC_ADDR, HWIO_RPM_MISC_RMSK)
#define HWIO_RPM_MISC_INM(m)      \
        in_dword_masked(HWIO_RPM_MISC_ADDR, m)
#define HWIO_RPM_MISC_OUT(v)      \
        out_dword(HWIO_RPM_MISC_ADDR,v)
#define HWIO_RPM_MISC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MISC_ADDR,m,v,HWIO_RPM_MISC_IN)
#define HWIO_RPM_MISC_RPM_BRIDGE_POST_EN_BMSK                                      0x2
#define HWIO_RPM_MISC_RPM_BRIDGE_POST_EN_SHFT                                      0x1
#define HWIO_RPM_MISC_RPM_BRIDGE_POST_EN_NO_POST_EN_FVAL                           0x0
#define HWIO_RPM_MISC_RPM_BRIDGE_POST_EN_POST_EN_FVAL                              0x1
#define HWIO_RPM_MISC_NOC_BRIDGE_POST_EN_BMSK                                      0x1
#define HWIO_RPM_MISC_NOC_BRIDGE_POST_EN_SHFT                                      0x0
#define HWIO_RPM_MISC_NOC_BRIDGE_POST_EN_NO_POST_EN_FVAL                           0x0
#define HWIO_RPM_MISC_NOC_BRIDGE_POST_EN_POST_EN_FVAL                              0x1

#define HWIO_RPM_CODE_RAM_DENSITY_ADDR                                      (RPM_DEC_REG_BASE      + 0x00000080)
#define HWIO_RPM_CODE_RAM_DENSITY_RMSK                                        0xffffff
#define HWIO_RPM_CODE_RAM_DENSITY_IN          \
        in_dword_masked(HWIO_RPM_CODE_RAM_DENSITY_ADDR, HWIO_RPM_CODE_RAM_DENSITY_RMSK)
#define HWIO_RPM_CODE_RAM_DENSITY_INM(m)      \
        in_dword_masked(HWIO_RPM_CODE_RAM_DENSITY_ADDR, m)
#define HWIO_RPM_CODE_RAM_DENSITY_DENSITY_BMSK                                0xffffff
#define HWIO_RPM_CODE_RAM_DENSITY_DENSITY_SHFT                                     0x0

#define HWIO_RPM_DATA_RAM_DENSITY_ADDR                                      (RPM_DEC_REG_BASE      + 0x00000084)
#define HWIO_RPM_DATA_RAM_DENSITY_RMSK                                        0xffffff
#define HWIO_RPM_DATA_RAM_DENSITY_IN          \
        in_dword_masked(HWIO_RPM_DATA_RAM_DENSITY_ADDR, HWIO_RPM_DATA_RAM_DENSITY_RMSK)
#define HWIO_RPM_DATA_RAM_DENSITY_INM(m)      \
        in_dword_masked(HWIO_RPM_DATA_RAM_DENSITY_ADDR, m)
#define HWIO_RPM_DATA_RAM_DENSITY_DENSITY_BMSK                                0xffffff
#define HWIO_RPM_DATA_RAM_DENSITY_DENSITY_SHFT                                     0x0

#define HWIO_RPM_MSG_RAM_DENSITY_ADDR                                       (RPM_DEC_REG_BASE      + 0x00000088)
#define HWIO_RPM_MSG_RAM_DENSITY_RMSK                                         0xffffff
#define HWIO_RPM_MSG_RAM_DENSITY_IN          \
        in_dword_masked(HWIO_RPM_MSG_RAM_DENSITY_ADDR, HWIO_RPM_MSG_RAM_DENSITY_RMSK)
#define HWIO_RPM_MSG_RAM_DENSITY_INM(m)      \
        in_dword_masked(HWIO_RPM_MSG_RAM_DENSITY_ADDR, m)
#define HWIO_RPM_MSG_RAM_DENSITY_DENSITY_BMSK                                 0xffffff
#define HWIO_RPM_MSG_RAM_DENSITY_DENSITY_SHFT                                      0x0

/*----------------------------------------------------------------------------
 * MODULE: RPM_QTMR_AC
 *--------------------------------------------------------------------------*/

#define RPM_QTMR_AC_REG_BASE                                       (RPM_BASE      + 0x00082000)

#define HWIO_RPM_QTMR_AC_CNTFRQ_ADDR                               (RPM_QTMR_AC_REG_BASE      + 0x00000000)
#define HWIO_RPM_QTMR_AC_CNTFRQ_RMSK                               0xffffffff
#define HWIO_RPM_QTMR_AC_CNTFRQ_IN          \
        in_dword_masked(HWIO_RPM_QTMR_AC_CNTFRQ_ADDR, HWIO_RPM_QTMR_AC_CNTFRQ_RMSK)
#define HWIO_RPM_QTMR_AC_CNTFRQ_INM(m)      \
        in_dword_masked(HWIO_RPM_QTMR_AC_CNTFRQ_ADDR, m)
#define HWIO_RPM_QTMR_AC_CNTFRQ_OUT(v)      \
        out_dword(HWIO_RPM_QTMR_AC_CNTFRQ_ADDR,v)
#define HWIO_RPM_QTMR_AC_CNTFRQ_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_QTMR_AC_CNTFRQ_ADDR,m,v,HWIO_RPM_QTMR_AC_CNTFRQ_IN)
#define HWIO_RPM_QTMR_AC_CNTFRQ_CNTFRQ_BMSK                        0xffffffff
#define HWIO_RPM_QTMR_AC_CNTFRQ_CNTFRQ_SHFT                               0x0

#define HWIO_RPM_QTMR_AC_CNTNSAR_FG0_ADDR                          (RPM_QTMR_AC_REG_BASE      + 0x00000004)
#define HWIO_RPM_QTMR_AC_CNTNSAR_FG0_RMSK                                 0x3
#define HWIO_RPM_QTMR_AC_CNTNSAR_FG0_IN          \
        in_dword_masked(HWIO_RPM_QTMR_AC_CNTNSAR_FG0_ADDR, HWIO_RPM_QTMR_AC_CNTNSAR_FG0_RMSK)
#define HWIO_RPM_QTMR_AC_CNTNSAR_FG0_INM(m)      \
        in_dword_masked(HWIO_RPM_QTMR_AC_CNTNSAR_FG0_ADDR, m)
#define HWIO_RPM_QTMR_AC_CNTNSAR_FG0_OUT(v)      \
        out_dword(HWIO_RPM_QTMR_AC_CNTNSAR_FG0_ADDR,v)
#define HWIO_RPM_QTMR_AC_CNTNSAR_FG0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_QTMR_AC_CNTNSAR_FG0_ADDR,m,v,HWIO_RPM_QTMR_AC_CNTNSAR_FG0_IN)
#define HWIO_RPM_QTMR_AC_CNTNSAR_FG0_NSN_BMSK                             0x3
#define HWIO_RPM_QTMR_AC_CNTNSAR_FG0_NSN_SHFT                             0x0
#define HWIO_RPM_QTMR_AC_CNTNSAR_FG0_NSN_SECURE_ONLY_FVAL                 0x0
#define HWIO_RPM_QTMR_AC_CNTNSAR_FG0_NSN_SECURE_OR_NONSECURE_FVAL         0x1

#define HWIO_RPM_QTMR_AC_CNTTIDR_FG0_ADDR                          (RPM_QTMR_AC_REG_BASE      + 0x00000008)
#define HWIO_RPM_QTMR_AC_CNTTIDR_FG0_RMSK                          0xffffffff
#define HWIO_RPM_QTMR_AC_CNTTIDR_FG0_IN          \
        in_dword_masked(HWIO_RPM_QTMR_AC_CNTTIDR_FG0_ADDR, HWIO_RPM_QTMR_AC_CNTTIDR_FG0_RMSK)
#define HWIO_RPM_QTMR_AC_CNTTIDR_FG0_INM(m)      \
        in_dword_masked(HWIO_RPM_QTMR_AC_CNTTIDR_FG0_ADDR, m)
#define HWIO_RPM_QTMR_AC_CNTTIDR_FG0_F7_CFG_BMSK                   0xf0000000
#define HWIO_RPM_QTMR_AC_CNTTIDR_FG0_F7_CFG_SHFT                         0x1c
#define HWIO_RPM_QTMR_AC_CNTTIDR_FG0_F6_CFG_BMSK                    0xf000000
#define HWIO_RPM_QTMR_AC_CNTTIDR_FG0_F6_CFG_SHFT                         0x18
#define HWIO_RPM_QTMR_AC_CNTTIDR_FG0_F5_CFG_BMSK                     0xf00000
#define HWIO_RPM_QTMR_AC_CNTTIDR_FG0_F5_CFG_SHFT                         0x14
#define HWIO_RPM_QTMR_AC_CNTTIDR_FG0_F4_CFG_BMSK                      0xf0000
#define HWIO_RPM_QTMR_AC_CNTTIDR_FG0_F4_CFG_SHFT                         0x10
#define HWIO_RPM_QTMR_AC_CNTTIDR_FG0_F3_CFG_BMSK                       0xf000
#define HWIO_RPM_QTMR_AC_CNTTIDR_FG0_F3_CFG_SHFT                          0xc
#define HWIO_RPM_QTMR_AC_CNTTIDR_FG0_F2_CFG_BMSK                        0xf00
#define HWIO_RPM_QTMR_AC_CNTTIDR_FG0_F2_CFG_SHFT                          0x8
#define HWIO_RPM_QTMR_AC_CNTTIDR_FG0_F1_CFG_BMSK                         0xf0
#define HWIO_RPM_QTMR_AC_CNTTIDR_FG0_F1_CFG_SHFT                          0x4
#define HWIO_RPM_QTMR_AC_CNTTIDR_FG0_F0_CFG_BMSK                          0xf
#define HWIO_RPM_QTMR_AC_CNTTIDR_FG0_F0_CFG_SHFT                          0x0
#define HWIO_RPM_QTMR_AC_CNTTIDR_FG0_F0_CFG_FI_FVAL                       0x0
#define HWIO_RPM_QTMR_AC_CNTTIDR_FG0_F0_CFG_FVI_FVAL                      0x1
#define HWIO_RPM_QTMR_AC_CNTTIDR_FG0_F0_CFG_FPLO_FVAL                     0x2
#define HWIO_RPM_QTMR_AC_CNTTIDR_FG0_F0_CFG_RSVD_FVAL                     0x3

#define HWIO_RPM_QTMR_AC_CNTACRn_FG0_ADDR(n)                       (RPM_QTMR_AC_REG_BASE      + 0x00000040 + 0x4 * (n))
#define HWIO_RPM_QTMR_AC_CNTACRn_FG0_RMSK                                0x3f
#define HWIO_RPM_QTMR_AC_CNTACRn_FG0_MAXn                                   1
#define HWIO_RPM_QTMR_AC_CNTACRn_FG0_INI(n)        \
        in_dword_masked(HWIO_RPM_QTMR_AC_CNTACRn_FG0_ADDR(n), HWIO_RPM_QTMR_AC_CNTACRn_FG0_RMSK)
#define HWIO_RPM_QTMR_AC_CNTACRn_FG0_INMI(n,mask)    \
        in_dword_masked(HWIO_RPM_QTMR_AC_CNTACRn_FG0_ADDR(n), mask)
#define HWIO_RPM_QTMR_AC_CNTACRn_FG0_OUTI(n,val)    \
        out_dword(HWIO_RPM_QTMR_AC_CNTACRn_FG0_ADDR(n),val)
#define HWIO_RPM_QTMR_AC_CNTACRn_FG0_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_RPM_QTMR_AC_CNTACRn_FG0_ADDR(n),mask,val,HWIO_RPM_QTMR_AC_CNTACRn_FG0_INI(n))
#define HWIO_RPM_QTMR_AC_CNTACRn_FG0_RWPT_BMSK                           0x20
#define HWIO_RPM_QTMR_AC_CNTACRn_FG0_RWPT_SHFT                            0x5
#define HWIO_RPM_QTMR_AC_CNTACRn_FG0_RWPT_ACCESS_DENIED_FVAL              0x0
#define HWIO_RPM_QTMR_AC_CNTACRn_FG0_RWPT_ACCESS_ALLOWED_FVAL             0x1
#define HWIO_RPM_QTMR_AC_CNTACRn_FG0_RWVT_BMSK                           0x10
#define HWIO_RPM_QTMR_AC_CNTACRn_FG0_RWVT_SHFT                            0x4
#define HWIO_RPM_QTMR_AC_CNTACRn_FG0_RWVT_ACCESS_DENIED_FVAL              0x0
#define HWIO_RPM_QTMR_AC_CNTACRn_FG0_RWVT_ACCESS_ALLOWED_FVAL             0x1
#define HWIO_RPM_QTMR_AC_CNTACRn_FG0_RVOFF_BMSK                           0x8
#define HWIO_RPM_QTMR_AC_CNTACRn_FG0_RVOFF_SHFT                           0x3
#define HWIO_RPM_QTMR_AC_CNTACRn_FG0_RVOFF_ACCESS_DENIED_FVAL             0x0
#define HWIO_RPM_QTMR_AC_CNTACRn_FG0_RVOFF_ACCESS_ALLOWED_FVAL            0x1
#define HWIO_RPM_QTMR_AC_CNTACRn_FG0_RFRQ_BMSK                            0x4
#define HWIO_RPM_QTMR_AC_CNTACRn_FG0_RFRQ_SHFT                            0x2
#define HWIO_RPM_QTMR_AC_CNTACRn_FG0_RFRQ_ACCESS_DENIED_FVAL              0x0
#define HWIO_RPM_QTMR_AC_CNTACRn_FG0_RFRQ_ACCESS_ALLOWED_FVAL             0x1
#define HWIO_RPM_QTMR_AC_CNTACRn_FG0_RPVCT_BMSK                           0x2
#define HWIO_RPM_QTMR_AC_CNTACRn_FG0_RPVCT_SHFT                           0x1
#define HWIO_RPM_QTMR_AC_CNTACRn_FG0_RPVCT_ACCESS_DENIED_FVAL             0x0
#define HWIO_RPM_QTMR_AC_CNTACRn_FG0_RPVCT_ACCESS_ALLOWED_FVAL            0x1
#define HWIO_RPM_QTMR_AC_CNTACRn_FG0_RPCT_BMSK                            0x1
#define HWIO_RPM_QTMR_AC_CNTACRn_FG0_RPCT_SHFT                            0x0
#define HWIO_RPM_QTMR_AC_CNTACRn_FG0_RPCT_ACCESS_DENIED_FVAL              0x0
#define HWIO_RPM_QTMR_AC_CNTACRn_FG0_RPCT_ACCESS_ALLOWED_FVAL             0x1

#define HWIO_RPM_QTMR_AC_CNTVOFF_FG0_LO_n_ADDR(n)                  (RPM_QTMR_AC_REG_BASE      + 0x00000080 + 0x8 * (n))
#define HWIO_RPM_QTMR_AC_CNTVOFF_FG0_LO_n_RMSK                     0xffffffff
#define HWIO_RPM_QTMR_AC_CNTVOFF_FG0_LO_n_MAXn                              1
#define HWIO_RPM_QTMR_AC_CNTVOFF_FG0_LO_n_INI(n)        \
        in_dword_masked(HWIO_RPM_QTMR_AC_CNTVOFF_FG0_LO_n_ADDR(n), HWIO_RPM_QTMR_AC_CNTVOFF_FG0_LO_n_RMSK)
#define HWIO_RPM_QTMR_AC_CNTVOFF_FG0_LO_n_INMI(n,mask)    \
        in_dword_masked(HWIO_RPM_QTMR_AC_CNTVOFF_FG0_LO_n_ADDR(n), mask)
#define HWIO_RPM_QTMR_AC_CNTVOFF_FG0_LO_n_OUTI(n,val)    \
        out_dword(HWIO_RPM_QTMR_AC_CNTVOFF_FG0_LO_n_ADDR(n),val)
#define HWIO_RPM_QTMR_AC_CNTVOFF_FG0_LO_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_RPM_QTMR_AC_CNTVOFF_FG0_LO_n_ADDR(n),mask,val,HWIO_RPM_QTMR_AC_CNTVOFF_FG0_LO_n_INI(n))
#define HWIO_RPM_QTMR_AC_CNTVOFF_FG0_LO_n_CNTVOFF_LO_BMSK          0xffffffff
#define HWIO_RPM_QTMR_AC_CNTVOFF_FG0_LO_n_CNTVOFF_LO_SHFT                 0x0

#define HWIO_RPM_QTMR_AC_CNTVOFF_FG0_HI_n_ADDR(n)                  (RPM_QTMR_AC_REG_BASE      + 0x00000084 + 0x8 * (n))
#define HWIO_RPM_QTMR_AC_CNTVOFF_FG0_HI_n_RMSK                       0xffffff
#define HWIO_RPM_QTMR_AC_CNTVOFF_FG0_HI_n_MAXn                              1
#define HWIO_RPM_QTMR_AC_CNTVOFF_FG0_HI_n_INI(n)        \
        in_dword_masked(HWIO_RPM_QTMR_AC_CNTVOFF_FG0_HI_n_ADDR(n), HWIO_RPM_QTMR_AC_CNTVOFF_FG0_HI_n_RMSK)
#define HWIO_RPM_QTMR_AC_CNTVOFF_FG0_HI_n_INMI(n,mask)    \
        in_dword_masked(HWIO_RPM_QTMR_AC_CNTVOFF_FG0_HI_n_ADDR(n), mask)
#define HWIO_RPM_QTMR_AC_CNTVOFF_FG0_HI_n_OUTI(n,val)    \
        out_dword(HWIO_RPM_QTMR_AC_CNTVOFF_FG0_HI_n_ADDR(n),val)
#define HWIO_RPM_QTMR_AC_CNTVOFF_FG0_HI_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_RPM_QTMR_AC_CNTVOFF_FG0_HI_n_ADDR(n),mask,val,HWIO_RPM_QTMR_AC_CNTVOFF_FG0_HI_n_INI(n))
#define HWIO_RPM_QTMR_AC_CNTVOFF_FG0_HI_n_CNTVOFF_HI_BMSK            0xffffff
#define HWIO_RPM_QTMR_AC_CNTVOFF_FG0_HI_n_CNTVOFF_HI_SHFT                 0x0

#define HWIO_RPM_QTMR_AC_CFG_ADDR                                  (RPM_QTMR_AC_REG_BASE      + 0x00000fc0)
#define HWIO_RPM_QTMR_AC_CFG_RMSK                                         0x3
#define HWIO_RPM_QTMR_AC_CFG_IN          \
        in_dword_masked(HWIO_RPM_QTMR_AC_CFG_ADDR, HWIO_RPM_QTMR_AC_CFG_RMSK)
#define HWIO_RPM_QTMR_AC_CFG_INM(m)      \
        in_dword_masked(HWIO_RPM_QTMR_AC_CFG_ADDR, m)
#define HWIO_RPM_QTMR_AC_CFG_OUT(v)      \
        out_dword(HWIO_RPM_QTMR_AC_CFG_ADDR,v)
#define HWIO_RPM_QTMR_AC_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_QTMR_AC_CFG_ADDR,m,v,HWIO_RPM_QTMR_AC_CFG_IN)
#define HWIO_RPM_QTMR_AC_CFG_DSBL_ATOMIC_BMSK                             0x2
#define HWIO_RPM_QTMR_AC_CFG_DSBL_ATOMIC_SHFT                             0x1
#define HWIO_RPM_QTMR_AC_CFG_TEST_BUS_EN_BMSK                             0x1
#define HWIO_RPM_QTMR_AC_CFG_TEST_BUS_EN_SHFT                             0x0

#define HWIO_RPM_QTMR_AC_VERSION_ADDR                              (RPM_QTMR_AC_REG_BASE      + 0x00000fd0)
#define HWIO_RPM_QTMR_AC_VERSION_RMSK                              0xffffffff
#define HWIO_RPM_QTMR_AC_VERSION_IN          \
        in_dword_masked(HWIO_RPM_QTMR_AC_VERSION_ADDR, HWIO_RPM_QTMR_AC_VERSION_RMSK)
#define HWIO_RPM_QTMR_AC_VERSION_INM(m)      \
        in_dword_masked(HWIO_RPM_QTMR_AC_VERSION_ADDR, m)
#define HWIO_RPM_QTMR_AC_VERSION_MAJOR_BMSK                        0xf0000000
#define HWIO_RPM_QTMR_AC_VERSION_MAJOR_SHFT                              0x1c
#define HWIO_RPM_QTMR_AC_VERSION_MINOR_BMSK                         0xfff0000
#define HWIO_RPM_QTMR_AC_VERSION_MINOR_SHFT                              0x10
#define HWIO_RPM_QTMR_AC_VERSION_STEP_BMSK                             0xffff
#define HWIO_RPM_QTMR_AC_VERSION_STEP_SHFT                                0x0

/*----------------------------------------------------------------------------
 * MODULE: RPM_F0_QTMR_V1_F0
 *--------------------------------------------------------------------------*/

#define RPM_F0_QTMR_V1_F0_REG_BASE                                  (RPM_BASE      + 0x00083000)

#define HWIO_RPM_F0_QTMR_V1_CNTPCT_LO_ADDR                          (RPM_F0_QTMR_V1_F0_REG_BASE      + 0x00000000)
#define HWIO_RPM_F0_QTMR_V1_CNTPCT_LO_RMSK                          0xffffffff
#define HWIO_RPM_F0_QTMR_V1_CNTPCT_LO_IN          \
        in_dword_masked(HWIO_RPM_F0_QTMR_V1_CNTPCT_LO_ADDR, HWIO_RPM_F0_QTMR_V1_CNTPCT_LO_RMSK)
#define HWIO_RPM_F0_QTMR_V1_CNTPCT_LO_INM(m)      \
        in_dword_masked(HWIO_RPM_F0_QTMR_V1_CNTPCT_LO_ADDR, m)
#define HWIO_RPM_F0_QTMR_V1_CNTPCT_LO_CNTPCT_LO_BMSK                0xffffffff
#define HWIO_RPM_F0_QTMR_V1_CNTPCT_LO_CNTPCT_LO_SHFT                       0x0

#define HWIO_RPM_F0_QTMR_V1_CNTPCT_HI_ADDR                          (RPM_F0_QTMR_V1_F0_REG_BASE      + 0x00000004)
#define HWIO_RPM_F0_QTMR_V1_CNTPCT_HI_RMSK                            0xffffff
#define HWIO_RPM_F0_QTMR_V1_CNTPCT_HI_IN          \
        in_dword_masked(HWIO_RPM_F0_QTMR_V1_CNTPCT_HI_ADDR, HWIO_RPM_F0_QTMR_V1_CNTPCT_HI_RMSK)
#define HWIO_RPM_F0_QTMR_V1_CNTPCT_HI_INM(m)      \
        in_dword_masked(HWIO_RPM_F0_QTMR_V1_CNTPCT_HI_ADDR, m)
#define HWIO_RPM_F0_QTMR_V1_CNTPCT_HI_CNTPCT_HI_BMSK                  0xffffff
#define HWIO_RPM_F0_QTMR_V1_CNTPCT_HI_CNTPCT_HI_SHFT                       0x0

#define HWIO_RPM_F0_QTMR_V1_CNTVCT_LO_ADDR                          (RPM_F0_QTMR_V1_F0_REG_BASE      + 0x00000008)
#define HWIO_RPM_F0_QTMR_V1_CNTVCT_LO_RMSK                          0xffffffff
#define HWIO_RPM_F0_QTMR_V1_CNTVCT_LO_IN          \
        in_dword_masked(HWIO_RPM_F0_QTMR_V1_CNTVCT_LO_ADDR, HWIO_RPM_F0_QTMR_V1_CNTVCT_LO_RMSK)
#define HWIO_RPM_F0_QTMR_V1_CNTVCT_LO_INM(m)      \
        in_dword_masked(HWIO_RPM_F0_QTMR_V1_CNTVCT_LO_ADDR, m)
#define HWIO_RPM_F0_QTMR_V1_CNTVCT_LO_CNTVCT_LO_BMSK                0xffffffff
#define HWIO_RPM_F0_QTMR_V1_CNTVCT_LO_CNTVCT_LO_SHFT                       0x0

#define HWIO_RPM_F0_QTMR_V1_CNTVCT_HI_ADDR                          (RPM_F0_QTMR_V1_F0_REG_BASE      + 0x0000000c)
#define HWIO_RPM_F0_QTMR_V1_CNTVCT_HI_RMSK                            0xffffff
#define HWIO_RPM_F0_QTMR_V1_CNTVCT_HI_IN          \
        in_dword_masked(HWIO_RPM_F0_QTMR_V1_CNTVCT_HI_ADDR, HWIO_RPM_F0_QTMR_V1_CNTVCT_HI_RMSK)
#define HWIO_RPM_F0_QTMR_V1_CNTVCT_HI_INM(m)      \
        in_dword_masked(HWIO_RPM_F0_QTMR_V1_CNTVCT_HI_ADDR, m)
#define HWIO_RPM_F0_QTMR_V1_CNTVCT_HI_CNTVCT_HI_BMSK                  0xffffff
#define HWIO_RPM_F0_QTMR_V1_CNTVCT_HI_CNTVCT_HI_SHFT                       0x0

#define HWIO_RPM_F0_QTMR_V1_CNTFRQ_ADDR                             (RPM_F0_QTMR_V1_F0_REG_BASE      + 0x00000010)
#define HWIO_RPM_F0_QTMR_V1_CNTFRQ_RMSK                             0xffffffff
#define HWIO_RPM_F0_QTMR_V1_CNTFRQ_IN          \
        in_dword_masked(HWIO_RPM_F0_QTMR_V1_CNTFRQ_ADDR, HWIO_RPM_F0_QTMR_V1_CNTFRQ_RMSK)
#define HWIO_RPM_F0_QTMR_V1_CNTFRQ_INM(m)      \
        in_dword_masked(HWIO_RPM_F0_QTMR_V1_CNTFRQ_ADDR, m)
#define HWIO_RPM_F0_QTMR_V1_CNTFRQ_CNTFRQ_BMSK                      0xffffffff
#define HWIO_RPM_F0_QTMR_V1_CNTFRQ_CNTFRQ_SHFT                             0x0

#define HWIO_RPM_F0_QTMR_V1_CNTPL0ACR_ADDR                          (RPM_F0_QTMR_V1_F0_REG_BASE      + 0x00000014)
#define HWIO_RPM_F0_QTMR_V1_CNTPL0ACR_RMSK                               0x303
#define HWIO_RPM_F0_QTMR_V1_CNTPL0ACR_IN          \
        in_dword_masked(HWIO_RPM_F0_QTMR_V1_CNTPL0ACR_ADDR, HWIO_RPM_F0_QTMR_V1_CNTPL0ACR_RMSK)
#define HWIO_RPM_F0_QTMR_V1_CNTPL0ACR_INM(m)      \
        in_dword_masked(HWIO_RPM_F0_QTMR_V1_CNTPL0ACR_ADDR, m)
#define HWIO_RPM_F0_QTMR_V1_CNTPL0ACR_OUT(v)      \
        out_dword(HWIO_RPM_F0_QTMR_V1_CNTPL0ACR_ADDR,v)
#define HWIO_RPM_F0_QTMR_V1_CNTPL0ACR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_F0_QTMR_V1_CNTPL0ACR_ADDR,m,v,HWIO_RPM_F0_QTMR_V1_CNTPL0ACR_IN)
#define HWIO_RPM_F0_QTMR_V1_CNTPL0ACR_PL0CTEN_BMSK                       0x200
#define HWIO_RPM_F0_QTMR_V1_CNTPL0ACR_PL0CTEN_SHFT                         0x9
#define HWIO_RPM_F0_QTMR_V1_CNTPL0ACR_PL0VTEN_BMSK                       0x100
#define HWIO_RPM_F0_QTMR_V1_CNTPL0ACR_PL0VTEN_SHFT                         0x8
#define HWIO_RPM_F0_QTMR_V1_CNTPL0ACR_PL0VCTEN_BMSK                        0x2
#define HWIO_RPM_F0_QTMR_V1_CNTPL0ACR_PL0VCTEN_SHFT                        0x1
#define HWIO_RPM_F0_QTMR_V1_CNTPL0ACR_PL0PCTEN_BMSK                        0x1
#define HWIO_RPM_F0_QTMR_V1_CNTPL0ACR_PL0PCTEN_SHFT                        0x0

#define HWIO_RPM_F0_QTMR_V1_CNTVOFF_LO_ADDR                         (RPM_F0_QTMR_V1_F0_REG_BASE      + 0x00000018)
#define HWIO_RPM_F0_QTMR_V1_CNTVOFF_LO_RMSK                         0xffffffff
#define HWIO_RPM_F0_QTMR_V1_CNTVOFF_LO_IN          \
        in_dword_masked(HWIO_RPM_F0_QTMR_V1_CNTVOFF_LO_ADDR, HWIO_RPM_F0_QTMR_V1_CNTVOFF_LO_RMSK)
#define HWIO_RPM_F0_QTMR_V1_CNTVOFF_LO_INM(m)      \
        in_dword_masked(HWIO_RPM_F0_QTMR_V1_CNTVOFF_LO_ADDR, m)
#define HWIO_RPM_F0_QTMR_V1_CNTVOFF_LO_CNTVOFF_L0_BMSK              0xffffffff
#define HWIO_RPM_F0_QTMR_V1_CNTVOFF_LO_CNTVOFF_L0_SHFT                     0x0

#define HWIO_RPM_F0_QTMR_V1_CNTVOFF_HI_ADDR                         (RPM_F0_QTMR_V1_F0_REG_BASE      + 0x0000001c)
#define HWIO_RPM_F0_QTMR_V1_CNTVOFF_HI_RMSK                           0xffffff
#define HWIO_RPM_F0_QTMR_V1_CNTVOFF_HI_IN          \
        in_dword_masked(HWIO_RPM_F0_QTMR_V1_CNTVOFF_HI_ADDR, HWIO_RPM_F0_QTMR_V1_CNTVOFF_HI_RMSK)
#define HWIO_RPM_F0_QTMR_V1_CNTVOFF_HI_INM(m)      \
        in_dword_masked(HWIO_RPM_F0_QTMR_V1_CNTVOFF_HI_ADDR, m)
#define HWIO_RPM_F0_QTMR_V1_CNTVOFF_HI_CNTVOFF_HI_BMSK                0xffffff
#define HWIO_RPM_F0_QTMR_V1_CNTVOFF_HI_CNTVOFF_HI_SHFT                     0x0

#define HWIO_RPM_F0_QTMR_V1_CNTP_CVAL_LO_ADDR                       (RPM_F0_QTMR_V1_F0_REG_BASE      + 0x00000020)
#define HWIO_RPM_F0_QTMR_V1_CNTP_CVAL_LO_RMSK                       0xffffffff
#define HWIO_RPM_F0_QTMR_V1_CNTP_CVAL_LO_IN          \
        in_dword_masked(HWIO_RPM_F0_QTMR_V1_CNTP_CVAL_LO_ADDR, HWIO_RPM_F0_QTMR_V1_CNTP_CVAL_LO_RMSK)
#define HWIO_RPM_F0_QTMR_V1_CNTP_CVAL_LO_INM(m)      \
        in_dword_masked(HWIO_RPM_F0_QTMR_V1_CNTP_CVAL_LO_ADDR, m)
#define HWIO_RPM_F0_QTMR_V1_CNTP_CVAL_LO_OUT(v)      \
        out_dword(HWIO_RPM_F0_QTMR_V1_CNTP_CVAL_LO_ADDR,v)
#define HWIO_RPM_F0_QTMR_V1_CNTP_CVAL_LO_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_F0_QTMR_V1_CNTP_CVAL_LO_ADDR,m,v,HWIO_RPM_F0_QTMR_V1_CNTP_CVAL_LO_IN)
#define HWIO_RPM_F0_QTMR_V1_CNTP_CVAL_LO_CNTP_CVAL_L0_BMSK          0xffffffff
#define HWIO_RPM_F0_QTMR_V1_CNTP_CVAL_LO_CNTP_CVAL_L0_SHFT                 0x0

#define HWIO_RPM_F0_QTMR_V1_CNTP_CVAL_HI_ADDR                       (RPM_F0_QTMR_V1_F0_REG_BASE      + 0x00000024)
#define HWIO_RPM_F0_QTMR_V1_CNTP_CVAL_HI_RMSK                         0xffffff
#define HWIO_RPM_F0_QTMR_V1_CNTP_CVAL_HI_IN          \
        in_dword_masked(HWIO_RPM_F0_QTMR_V1_CNTP_CVAL_HI_ADDR, HWIO_RPM_F0_QTMR_V1_CNTP_CVAL_HI_RMSK)
#define HWIO_RPM_F0_QTMR_V1_CNTP_CVAL_HI_INM(m)      \
        in_dword_masked(HWIO_RPM_F0_QTMR_V1_CNTP_CVAL_HI_ADDR, m)
#define HWIO_RPM_F0_QTMR_V1_CNTP_CVAL_HI_OUT(v)      \
        out_dword(HWIO_RPM_F0_QTMR_V1_CNTP_CVAL_HI_ADDR,v)
#define HWIO_RPM_F0_QTMR_V1_CNTP_CVAL_HI_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_F0_QTMR_V1_CNTP_CVAL_HI_ADDR,m,v,HWIO_RPM_F0_QTMR_V1_CNTP_CVAL_HI_IN)
#define HWIO_RPM_F0_QTMR_V1_CNTP_CVAL_HI_CNTP_CVAL_HI_BMSK            0xffffff
#define HWIO_RPM_F0_QTMR_V1_CNTP_CVAL_HI_CNTP_CVAL_HI_SHFT                 0x0

#define HWIO_RPM_F0_QTMR_V1_CNTP_TVAL_ADDR                          (RPM_F0_QTMR_V1_F0_REG_BASE      + 0x00000028)
#define HWIO_RPM_F0_QTMR_V1_CNTP_TVAL_RMSK                          0xffffffff
#define HWIO_RPM_F0_QTMR_V1_CNTP_TVAL_IN          \
        in_dword_masked(HWIO_RPM_F0_QTMR_V1_CNTP_TVAL_ADDR, HWIO_RPM_F0_QTMR_V1_CNTP_TVAL_RMSK)
#define HWIO_RPM_F0_QTMR_V1_CNTP_TVAL_INM(m)      \
        in_dword_masked(HWIO_RPM_F0_QTMR_V1_CNTP_TVAL_ADDR, m)
#define HWIO_RPM_F0_QTMR_V1_CNTP_TVAL_OUT(v)      \
        out_dword(HWIO_RPM_F0_QTMR_V1_CNTP_TVAL_ADDR,v)
#define HWIO_RPM_F0_QTMR_V1_CNTP_TVAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_F0_QTMR_V1_CNTP_TVAL_ADDR,m,v,HWIO_RPM_F0_QTMR_V1_CNTP_TVAL_IN)
#define HWIO_RPM_F0_QTMR_V1_CNTP_TVAL_CNTP_TVAL_BMSK                0xffffffff
#define HWIO_RPM_F0_QTMR_V1_CNTP_TVAL_CNTP_TVAL_SHFT                       0x0

#define HWIO_RPM_F0_QTMR_V1_CNTP_CTL_ADDR                           (RPM_F0_QTMR_V1_F0_REG_BASE      + 0x0000002c)
#define HWIO_RPM_F0_QTMR_V1_CNTP_CTL_RMSK                                  0x7
#define HWIO_RPM_F0_QTMR_V1_CNTP_CTL_IN          \
        in_dword_masked(HWIO_RPM_F0_QTMR_V1_CNTP_CTL_ADDR, HWIO_RPM_F0_QTMR_V1_CNTP_CTL_RMSK)
#define HWIO_RPM_F0_QTMR_V1_CNTP_CTL_INM(m)      \
        in_dword_masked(HWIO_RPM_F0_QTMR_V1_CNTP_CTL_ADDR, m)
#define HWIO_RPM_F0_QTMR_V1_CNTP_CTL_OUT(v)      \
        out_dword(HWIO_RPM_F0_QTMR_V1_CNTP_CTL_ADDR,v)
#define HWIO_RPM_F0_QTMR_V1_CNTP_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_F0_QTMR_V1_CNTP_CTL_ADDR,m,v,HWIO_RPM_F0_QTMR_V1_CNTP_CTL_IN)
#define HWIO_RPM_F0_QTMR_V1_CNTP_CTL_ISTAT_BMSK                            0x4
#define HWIO_RPM_F0_QTMR_V1_CNTP_CTL_ISTAT_SHFT                            0x2
#define HWIO_RPM_F0_QTMR_V1_CNTP_CTL_ISTAT_INTERRUPT_NOT_PENDING_FVAL        0x0
#define HWIO_RPM_F0_QTMR_V1_CNTP_CTL_ISTAT_INTERRUPT_PENDING_FVAL          0x1
#define HWIO_RPM_F0_QTMR_V1_CNTP_CTL_IMSK_BMSK                             0x2
#define HWIO_RPM_F0_QTMR_V1_CNTP_CTL_IMSK_SHFT                             0x1
#define HWIO_RPM_F0_QTMR_V1_CNTP_CTL_IMSK_UNMASK_INTERRUPT_FVAL            0x0
#define HWIO_RPM_F0_QTMR_V1_CNTP_CTL_IMSK_MASK_INTERRUPT_FVAL              0x1
#define HWIO_RPM_F0_QTMR_V1_CNTP_CTL_EN_BMSK                               0x1
#define HWIO_RPM_F0_QTMR_V1_CNTP_CTL_EN_SHFT                               0x0
#define HWIO_RPM_F0_QTMR_V1_CNTP_CTL_EN_DISABLED_FVAL                      0x0
#define HWIO_RPM_F0_QTMR_V1_CNTP_CTL_EN_ENABLED_FVAL                       0x1

#define HWIO_RPM_F0_QTMR_V1_CNTV_CVAL_LO_ADDR                       (RPM_F0_QTMR_V1_F0_REG_BASE      + 0x00000030)
#define HWIO_RPM_F0_QTMR_V1_CNTV_CVAL_LO_RMSK                       0xffffffff
#define HWIO_RPM_F0_QTMR_V1_CNTV_CVAL_LO_IN          \
        in_dword_masked(HWIO_RPM_F0_QTMR_V1_CNTV_CVAL_LO_ADDR, HWIO_RPM_F0_QTMR_V1_CNTV_CVAL_LO_RMSK)
#define HWIO_RPM_F0_QTMR_V1_CNTV_CVAL_LO_INM(m)      \
        in_dword_masked(HWIO_RPM_F0_QTMR_V1_CNTV_CVAL_LO_ADDR, m)
#define HWIO_RPM_F0_QTMR_V1_CNTV_CVAL_LO_OUT(v)      \
        out_dword(HWIO_RPM_F0_QTMR_V1_CNTV_CVAL_LO_ADDR,v)
#define HWIO_RPM_F0_QTMR_V1_CNTV_CVAL_LO_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_F0_QTMR_V1_CNTV_CVAL_LO_ADDR,m,v,HWIO_RPM_F0_QTMR_V1_CNTV_CVAL_LO_IN)
#define HWIO_RPM_F0_QTMR_V1_CNTV_CVAL_LO_CNTV_CVAL_L0_BMSK          0xffffffff
#define HWIO_RPM_F0_QTMR_V1_CNTV_CVAL_LO_CNTV_CVAL_L0_SHFT                 0x0

#define HWIO_RPM_F0_QTMR_V1_CNTV_CVAL_HI_ADDR                       (RPM_F0_QTMR_V1_F0_REG_BASE      + 0x00000034)
#define HWIO_RPM_F0_QTMR_V1_CNTV_CVAL_HI_RMSK                         0xffffff
#define HWIO_RPM_F0_QTMR_V1_CNTV_CVAL_HI_IN          \
        in_dword_masked(HWIO_RPM_F0_QTMR_V1_CNTV_CVAL_HI_ADDR, HWIO_RPM_F0_QTMR_V1_CNTV_CVAL_HI_RMSK)
#define HWIO_RPM_F0_QTMR_V1_CNTV_CVAL_HI_INM(m)      \
        in_dword_masked(HWIO_RPM_F0_QTMR_V1_CNTV_CVAL_HI_ADDR, m)
#define HWIO_RPM_F0_QTMR_V1_CNTV_CVAL_HI_OUT(v)      \
        out_dword(HWIO_RPM_F0_QTMR_V1_CNTV_CVAL_HI_ADDR,v)
#define HWIO_RPM_F0_QTMR_V1_CNTV_CVAL_HI_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_F0_QTMR_V1_CNTV_CVAL_HI_ADDR,m,v,HWIO_RPM_F0_QTMR_V1_CNTV_CVAL_HI_IN)
#define HWIO_RPM_F0_QTMR_V1_CNTV_CVAL_HI_CNTV_CVAL_HI_BMSK            0xffffff
#define HWIO_RPM_F0_QTMR_V1_CNTV_CVAL_HI_CNTV_CVAL_HI_SHFT                 0x0

#define HWIO_RPM_F0_QTMR_V1_CNTV_TVAL_ADDR                          (RPM_F0_QTMR_V1_F0_REG_BASE      + 0x00000038)
#define HWIO_RPM_F0_QTMR_V1_CNTV_TVAL_RMSK                          0xffffffff
#define HWIO_RPM_F0_QTMR_V1_CNTV_TVAL_IN          \
        in_dword_masked(HWIO_RPM_F0_QTMR_V1_CNTV_TVAL_ADDR, HWIO_RPM_F0_QTMR_V1_CNTV_TVAL_RMSK)
#define HWIO_RPM_F0_QTMR_V1_CNTV_TVAL_INM(m)      \
        in_dword_masked(HWIO_RPM_F0_QTMR_V1_CNTV_TVAL_ADDR, m)
#define HWIO_RPM_F0_QTMR_V1_CNTV_TVAL_OUT(v)      \
        out_dword(HWIO_RPM_F0_QTMR_V1_CNTV_TVAL_ADDR,v)
#define HWIO_RPM_F0_QTMR_V1_CNTV_TVAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_F0_QTMR_V1_CNTV_TVAL_ADDR,m,v,HWIO_RPM_F0_QTMR_V1_CNTV_TVAL_IN)
#define HWIO_RPM_F0_QTMR_V1_CNTV_TVAL_CNTV_TVAL_BMSK                0xffffffff
#define HWIO_RPM_F0_QTMR_V1_CNTV_TVAL_CNTV_TVAL_SHFT                       0x0

#define HWIO_RPM_F0_QTMR_V1_CNTV_CTL_ADDR                           (RPM_F0_QTMR_V1_F0_REG_BASE      + 0x0000003c)
#define HWIO_RPM_F0_QTMR_V1_CNTV_CTL_RMSK                                  0x7
#define HWIO_RPM_F0_QTMR_V1_CNTV_CTL_IN          \
        in_dword_masked(HWIO_RPM_F0_QTMR_V1_CNTV_CTL_ADDR, HWIO_RPM_F0_QTMR_V1_CNTV_CTL_RMSK)
#define HWIO_RPM_F0_QTMR_V1_CNTV_CTL_INM(m)      \
        in_dword_masked(HWIO_RPM_F0_QTMR_V1_CNTV_CTL_ADDR, m)
#define HWIO_RPM_F0_QTMR_V1_CNTV_CTL_OUT(v)      \
        out_dword(HWIO_RPM_F0_QTMR_V1_CNTV_CTL_ADDR,v)
#define HWIO_RPM_F0_QTMR_V1_CNTV_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_F0_QTMR_V1_CNTV_CTL_ADDR,m,v,HWIO_RPM_F0_QTMR_V1_CNTV_CTL_IN)
#define HWIO_RPM_F0_QTMR_V1_CNTV_CTL_ISTAT_BMSK                            0x4
#define HWIO_RPM_F0_QTMR_V1_CNTV_CTL_ISTAT_SHFT                            0x2
#define HWIO_RPM_F0_QTMR_V1_CNTV_CTL_ISTAT_INTERRUPT_NOT_PENDING_FVAL        0x0
#define HWIO_RPM_F0_QTMR_V1_CNTV_CTL_ISTAT_INTERRUPT_PENDING_FVAL          0x1
#define HWIO_RPM_F0_QTMR_V1_CNTV_CTL_IMSK_BMSK                             0x2
#define HWIO_RPM_F0_QTMR_V1_CNTV_CTL_IMSK_SHFT                             0x1
#define HWIO_RPM_F0_QTMR_V1_CNTV_CTL_IMSK_UNMASK_INTERRUPT_FVAL            0x0
#define HWIO_RPM_F0_QTMR_V1_CNTV_CTL_IMSK_MASK_INTERRUPT_FVAL              0x1
#define HWIO_RPM_F0_QTMR_V1_CNTV_CTL_EN_BMSK                               0x1
#define HWIO_RPM_F0_QTMR_V1_CNTV_CTL_EN_SHFT                               0x0
#define HWIO_RPM_F0_QTMR_V1_CNTV_CTL_EN_DISABLED_FVAL                      0x0
#define HWIO_RPM_F0_QTMR_V1_CNTV_CTL_EN_ENABLED_FVAL                       0x1

#define HWIO_RPM_F0_QTMR_V1_VERSION_ADDR                            (RPM_F0_QTMR_V1_F0_REG_BASE      + 0x00000fd0)
#define HWIO_RPM_F0_QTMR_V1_VERSION_RMSK                            0xffffffff
#define HWIO_RPM_F0_QTMR_V1_VERSION_IN          \
        in_dword_masked(HWIO_RPM_F0_QTMR_V1_VERSION_ADDR, HWIO_RPM_F0_QTMR_V1_VERSION_RMSK)
#define HWIO_RPM_F0_QTMR_V1_VERSION_INM(m)      \
        in_dword_masked(HWIO_RPM_F0_QTMR_V1_VERSION_ADDR, m)
#define HWIO_RPM_F0_QTMR_V1_VERSION_MAJOR_BMSK                      0xf0000000
#define HWIO_RPM_F0_QTMR_V1_VERSION_MAJOR_SHFT                            0x1c
#define HWIO_RPM_F0_QTMR_V1_VERSION_MINOR_BMSK                       0xfff0000
#define HWIO_RPM_F0_QTMR_V1_VERSION_MINOR_SHFT                            0x10
#define HWIO_RPM_F0_QTMR_V1_VERSION_STEP_BMSK                           0xffff
#define HWIO_RPM_F0_QTMR_V1_VERSION_STEP_SHFT                              0x0

/*----------------------------------------------------------------------------
 * MODULE: RPM_F1_QTMR_V1_F1
 *--------------------------------------------------------------------------*/

#define RPM_F1_QTMR_V1_F1_REG_BASE                                  (RPM_BASE      + 0x00084000)

#define HWIO_RPM_F1_QTMR_V1_CNTPCT_LO_ADDR                          (RPM_F1_QTMR_V1_F1_REG_BASE      + 0x00000000)
#define HWIO_RPM_F1_QTMR_V1_CNTPCT_LO_RMSK                          0xffffffff
#define HWIO_RPM_F1_QTMR_V1_CNTPCT_LO_IN          \
        in_dword_masked(HWIO_RPM_F1_QTMR_V1_CNTPCT_LO_ADDR, HWIO_RPM_F1_QTMR_V1_CNTPCT_LO_RMSK)
#define HWIO_RPM_F1_QTMR_V1_CNTPCT_LO_INM(m)      \
        in_dword_masked(HWIO_RPM_F1_QTMR_V1_CNTPCT_LO_ADDR, m)
#define HWIO_RPM_F1_QTMR_V1_CNTPCT_LO_CNTPCT_LO_BMSK                0xffffffff
#define HWIO_RPM_F1_QTMR_V1_CNTPCT_LO_CNTPCT_LO_SHFT                       0x0

#define HWIO_RPM_F1_QTMR_V1_CNTPCT_HI_ADDR                          (RPM_F1_QTMR_V1_F1_REG_BASE      + 0x00000004)
#define HWIO_RPM_F1_QTMR_V1_CNTPCT_HI_RMSK                            0xffffff
#define HWIO_RPM_F1_QTMR_V1_CNTPCT_HI_IN          \
        in_dword_masked(HWIO_RPM_F1_QTMR_V1_CNTPCT_HI_ADDR, HWIO_RPM_F1_QTMR_V1_CNTPCT_HI_RMSK)
#define HWIO_RPM_F1_QTMR_V1_CNTPCT_HI_INM(m)      \
        in_dword_masked(HWIO_RPM_F1_QTMR_V1_CNTPCT_HI_ADDR, m)
#define HWIO_RPM_F1_QTMR_V1_CNTPCT_HI_CNTPCT_HI_BMSK                  0xffffff
#define HWIO_RPM_F1_QTMR_V1_CNTPCT_HI_CNTPCT_HI_SHFT                       0x0

#define HWIO_RPM_F1_QTMR_V1_CNTVCT_LO_ADDR                          (RPM_F1_QTMR_V1_F1_REG_BASE      + 0x00000008)
#define HWIO_RPM_F1_QTMR_V1_CNTVCT_LO_RMSK                          0xffffffff
#define HWIO_RPM_F1_QTMR_V1_CNTVCT_LO_IN          \
        in_dword_masked(HWIO_RPM_F1_QTMR_V1_CNTVCT_LO_ADDR, HWIO_RPM_F1_QTMR_V1_CNTVCT_LO_RMSK)
#define HWIO_RPM_F1_QTMR_V1_CNTVCT_LO_INM(m)      \
        in_dword_masked(HWIO_RPM_F1_QTMR_V1_CNTVCT_LO_ADDR, m)
#define HWIO_RPM_F1_QTMR_V1_CNTVCT_LO_CNTVCT_LO_BMSK                0xffffffff
#define HWIO_RPM_F1_QTMR_V1_CNTVCT_LO_CNTVCT_LO_SHFT                       0x0

#define HWIO_RPM_F1_QTMR_V1_CNTVCT_HI_ADDR                          (RPM_F1_QTMR_V1_F1_REG_BASE      + 0x0000000c)
#define HWIO_RPM_F1_QTMR_V1_CNTVCT_HI_RMSK                            0xffffff
#define HWIO_RPM_F1_QTMR_V1_CNTVCT_HI_IN          \
        in_dword_masked(HWIO_RPM_F1_QTMR_V1_CNTVCT_HI_ADDR, HWIO_RPM_F1_QTMR_V1_CNTVCT_HI_RMSK)
#define HWIO_RPM_F1_QTMR_V1_CNTVCT_HI_INM(m)      \
        in_dword_masked(HWIO_RPM_F1_QTMR_V1_CNTVCT_HI_ADDR, m)
#define HWIO_RPM_F1_QTMR_V1_CNTVCT_HI_CNTVCT_HI_BMSK                  0xffffff
#define HWIO_RPM_F1_QTMR_V1_CNTVCT_HI_CNTVCT_HI_SHFT                       0x0

#define HWIO_RPM_F1_QTMR_V1_CNTFRQ_ADDR                             (RPM_F1_QTMR_V1_F1_REG_BASE      + 0x00000010)
#define HWIO_RPM_F1_QTMR_V1_CNTFRQ_RMSK                             0xffffffff
#define HWIO_RPM_F1_QTMR_V1_CNTFRQ_IN          \
        in_dword_masked(HWIO_RPM_F1_QTMR_V1_CNTFRQ_ADDR, HWIO_RPM_F1_QTMR_V1_CNTFRQ_RMSK)
#define HWIO_RPM_F1_QTMR_V1_CNTFRQ_INM(m)      \
        in_dword_masked(HWIO_RPM_F1_QTMR_V1_CNTFRQ_ADDR, m)
#define HWIO_RPM_F1_QTMR_V1_CNTFRQ_CNTFRQ_BMSK                      0xffffffff
#define HWIO_RPM_F1_QTMR_V1_CNTFRQ_CNTFRQ_SHFT                             0x0

#define HWIO_RPM_F1_QTMR_V1_CNTPL0ACR_ADDR                          (RPM_F1_QTMR_V1_F1_REG_BASE      + 0x00000014)
#define HWIO_RPM_F1_QTMR_V1_CNTPL0ACR_RMSK                               0x303
#define HWIO_RPM_F1_QTMR_V1_CNTPL0ACR_IN          \
        in_dword_masked(HWIO_RPM_F1_QTMR_V1_CNTPL0ACR_ADDR, HWIO_RPM_F1_QTMR_V1_CNTPL0ACR_RMSK)
#define HWIO_RPM_F1_QTMR_V1_CNTPL0ACR_INM(m)      \
        in_dword_masked(HWIO_RPM_F1_QTMR_V1_CNTPL0ACR_ADDR, m)
#define HWIO_RPM_F1_QTMR_V1_CNTPL0ACR_OUT(v)      \
        out_dword(HWIO_RPM_F1_QTMR_V1_CNTPL0ACR_ADDR,v)
#define HWIO_RPM_F1_QTMR_V1_CNTPL0ACR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_F1_QTMR_V1_CNTPL0ACR_ADDR,m,v,HWIO_RPM_F1_QTMR_V1_CNTPL0ACR_IN)
#define HWIO_RPM_F1_QTMR_V1_CNTPL0ACR_PL0CTEN_BMSK                       0x200
#define HWIO_RPM_F1_QTMR_V1_CNTPL0ACR_PL0CTEN_SHFT                         0x9
#define HWIO_RPM_F1_QTMR_V1_CNTPL0ACR_PL0VTEN_BMSK                       0x100
#define HWIO_RPM_F1_QTMR_V1_CNTPL0ACR_PL0VTEN_SHFT                         0x8
#define HWIO_RPM_F1_QTMR_V1_CNTPL0ACR_PL0VCTEN_BMSK                        0x2
#define HWIO_RPM_F1_QTMR_V1_CNTPL0ACR_PL0VCTEN_SHFT                        0x1
#define HWIO_RPM_F1_QTMR_V1_CNTPL0ACR_PL0PCTEN_BMSK                        0x1
#define HWIO_RPM_F1_QTMR_V1_CNTPL0ACR_PL0PCTEN_SHFT                        0x0

#define HWIO_RPM_F1_QTMR_V1_CNTVOFF_LO_ADDR                         (RPM_F1_QTMR_V1_F1_REG_BASE      + 0x00000018)
#define HWIO_RPM_F1_QTMR_V1_CNTVOFF_LO_RMSK                         0xffffffff
#define HWIO_RPM_F1_QTMR_V1_CNTVOFF_LO_IN          \
        in_dword_masked(HWIO_RPM_F1_QTMR_V1_CNTVOFF_LO_ADDR, HWIO_RPM_F1_QTMR_V1_CNTVOFF_LO_RMSK)
#define HWIO_RPM_F1_QTMR_V1_CNTVOFF_LO_INM(m)      \
        in_dword_masked(HWIO_RPM_F1_QTMR_V1_CNTVOFF_LO_ADDR, m)
#define HWIO_RPM_F1_QTMR_V1_CNTVOFF_LO_CNTVOFF_L0_BMSK              0xffffffff
#define HWIO_RPM_F1_QTMR_V1_CNTVOFF_LO_CNTVOFF_L0_SHFT                     0x0

#define HWIO_RPM_F1_QTMR_V1_CNTVOFF_HI_ADDR                         (RPM_F1_QTMR_V1_F1_REG_BASE      + 0x0000001c)
#define HWIO_RPM_F1_QTMR_V1_CNTVOFF_HI_RMSK                           0xffffff
#define HWIO_RPM_F1_QTMR_V1_CNTVOFF_HI_IN          \
        in_dword_masked(HWIO_RPM_F1_QTMR_V1_CNTVOFF_HI_ADDR, HWIO_RPM_F1_QTMR_V1_CNTVOFF_HI_RMSK)
#define HWIO_RPM_F1_QTMR_V1_CNTVOFF_HI_INM(m)      \
        in_dword_masked(HWIO_RPM_F1_QTMR_V1_CNTVOFF_HI_ADDR, m)
#define HWIO_RPM_F1_QTMR_V1_CNTVOFF_HI_CNTVOFF_HI_BMSK                0xffffff
#define HWIO_RPM_F1_QTMR_V1_CNTVOFF_HI_CNTVOFF_HI_SHFT                     0x0

#define HWIO_RPM_F1_QTMR_V1_CNTP_CVAL_LO_ADDR                       (RPM_F1_QTMR_V1_F1_REG_BASE      + 0x00000020)
#define HWIO_RPM_F1_QTMR_V1_CNTP_CVAL_LO_RMSK                       0xffffffff
#define HWIO_RPM_F1_QTMR_V1_CNTP_CVAL_LO_IN          \
        in_dword_masked(HWIO_RPM_F1_QTMR_V1_CNTP_CVAL_LO_ADDR, HWIO_RPM_F1_QTMR_V1_CNTP_CVAL_LO_RMSK)
#define HWIO_RPM_F1_QTMR_V1_CNTP_CVAL_LO_INM(m)      \
        in_dword_masked(HWIO_RPM_F1_QTMR_V1_CNTP_CVAL_LO_ADDR, m)
#define HWIO_RPM_F1_QTMR_V1_CNTP_CVAL_LO_OUT(v)      \
        out_dword(HWIO_RPM_F1_QTMR_V1_CNTP_CVAL_LO_ADDR,v)
#define HWIO_RPM_F1_QTMR_V1_CNTP_CVAL_LO_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_F1_QTMR_V1_CNTP_CVAL_LO_ADDR,m,v,HWIO_RPM_F1_QTMR_V1_CNTP_CVAL_LO_IN)
#define HWIO_RPM_F1_QTMR_V1_CNTP_CVAL_LO_CNTP_CVAL_L0_BMSK          0xffffffff
#define HWIO_RPM_F1_QTMR_V1_CNTP_CVAL_LO_CNTP_CVAL_L0_SHFT                 0x0

#define HWIO_RPM_F1_QTMR_V1_CNTP_CVAL_HI_ADDR                       (RPM_F1_QTMR_V1_F1_REG_BASE      + 0x00000024)
#define HWIO_RPM_F1_QTMR_V1_CNTP_CVAL_HI_RMSK                         0xffffff
#define HWIO_RPM_F1_QTMR_V1_CNTP_CVAL_HI_IN          \
        in_dword_masked(HWIO_RPM_F1_QTMR_V1_CNTP_CVAL_HI_ADDR, HWIO_RPM_F1_QTMR_V1_CNTP_CVAL_HI_RMSK)
#define HWIO_RPM_F1_QTMR_V1_CNTP_CVAL_HI_INM(m)      \
        in_dword_masked(HWIO_RPM_F1_QTMR_V1_CNTP_CVAL_HI_ADDR, m)
#define HWIO_RPM_F1_QTMR_V1_CNTP_CVAL_HI_OUT(v)      \
        out_dword(HWIO_RPM_F1_QTMR_V1_CNTP_CVAL_HI_ADDR,v)
#define HWIO_RPM_F1_QTMR_V1_CNTP_CVAL_HI_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_F1_QTMR_V1_CNTP_CVAL_HI_ADDR,m,v,HWIO_RPM_F1_QTMR_V1_CNTP_CVAL_HI_IN)
#define HWIO_RPM_F1_QTMR_V1_CNTP_CVAL_HI_CNTP_CVAL_HI_BMSK            0xffffff
#define HWIO_RPM_F1_QTMR_V1_CNTP_CVAL_HI_CNTP_CVAL_HI_SHFT                 0x0

#define HWIO_RPM_F1_QTMR_V1_CNTP_TVAL_ADDR                          (RPM_F1_QTMR_V1_F1_REG_BASE      + 0x00000028)
#define HWIO_RPM_F1_QTMR_V1_CNTP_TVAL_RMSK                          0xffffffff
#define HWIO_RPM_F1_QTMR_V1_CNTP_TVAL_IN          \
        in_dword_masked(HWIO_RPM_F1_QTMR_V1_CNTP_TVAL_ADDR, HWIO_RPM_F1_QTMR_V1_CNTP_TVAL_RMSK)
#define HWIO_RPM_F1_QTMR_V1_CNTP_TVAL_INM(m)      \
        in_dword_masked(HWIO_RPM_F1_QTMR_V1_CNTP_TVAL_ADDR, m)
#define HWIO_RPM_F1_QTMR_V1_CNTP_TVAL_OUT(v)      \
        out_dword(HWIO_RPM_F1_QTMR_V1_CNTP_TVAL_ADDR,v)
#define HWIO_RPM_F1_QTMR_V1_CNTP_TVAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_F1_QTMR_V1_CNTP_TVAL_ADDR,m,v,HWIO_RPM_F1_QTMR_V1_CNTP_TVAL_IN)
#define HWIO_RPM_F1_QTMR_V1_CNTP_TVAL_CNTP_TVAL_BMSK                0xffffffff
#define HWIO_RPM_F1_QTMR_V1_CNTP_TVAL_CNTP_TVAL_SHFT                       0x0

#define HWIO_RPM_F1_QTMR_V1_CNTP_CTL_ADDR                           (RPM_F1_QTMR_V1_F1_REG_BASE      + 0x0000002c)
#define HWIO_RPM_F1_QTMR_V1_CNTP_CTL_RMSK                                  0x7
#define HWIO_RPM_F1_QTMR_V1_CNTP_CTL_IN          \
        in_dword_masked(HWIO_RPM_F1_QTMR_V1_CNTP_CTL_ADDR, HWIO_RPM_F1_QTMR_V1_CNTP_CTL_RMSK)
#define HWIO_RPM_F1_QTMR_V1_CNTP_CTL_INM(m)      \
        in_dword_masked(HWIO_RPM_F1_QTMR_V1_CNTP_CTL_ADDR, m)
#define HWIO_RPM_F1_QTMR_V1_CNTP_CTL_OUT(v)      \
        out_dword(HWIO_RPM_F1_QTMR_V1_CNTP_CTL_ADDR,v)
#define HWIO_RPM_F1_QTMR_V1_CNTP_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_F1_QTMR_V1_CNTP_CTL_ADDR,m,v,HWIO_RPM_F1_QTMR_V1_CNTP_CTL_IN)
#define HWIO_RPM_F1_QTMR_V1_CNTP_CTL_ISTAT_BMSK                            0x4
#define HWIO_RPM_F1_QTMR_V1_CNTP_CTL_ISTAT_SHFT                            0x2
#define HWIO_RPM_F1_QTMR_V1_CNTP_CTL_ISTAT_INTERRUPT_NOT_PENDING_FVAL        0x0
#define HWIO_RPM_F1_QTMR_V1_CNTP_CTL_ISTAT_INTERRUPT_PENDING_FVAL          0x1
#define HWIO_RPM_F1_QTMR_V1_CNTP_CTL_IMSK_BMSK                             0x2
#define HWIO_RPM_F1_QTMR_V1_CNTP_CTL_IMSK_SHFT                             0x1
#define HWIO_RPM_F1_QTMR_V1_CNTP_CTL_IMSK_UNMASK_INTERRUPT_FVAL            0x0
#define HWIO_RPM_F1_QTMR_V1_CNTP_CTL_IMSK_MASK_INTERRUPT_FVAL              0x1
#define HWIO_RPM_F1_QTMR_V1_CNTP_CTL_EN_BMSK                               0x1
#define HWIO_RPM_F1_QTMR_V1_CNTP_CTL_EN_SHFT                               0x0
#define HWIO_RPM_F1_QTMR_V1_CNTP_CTL_EN_DISABLED_FVAL                      0x0
#define HWIO_RPM_F1_QTMR_V1_CNTP_CTL_EN_ENABLED_FVAL                       0x1

#define HWIO_RPM_F1_QTMR_V1_CNTV_CVAL_LO_ADDR                       (RPM_F1_QTMR_V1_F1_REG_BASE      + 0x00000030)
#define HWIO_RPM_F1_QTMR_V1_CNTV_CVAL_LO_RMSK                       0xffffffff
#define HWIO_RPM_F1_QTMR_V1_CNTV_CVAL_LO_IN          \
        in_dword_masked(HWIO_RPM_F1_QTMR_V1_CNTV_CVAL_LO_ADDR, HWIO_RPM_F1_QTMR_V1_CNTV_CVAL_LO_RMSK)
#define HWIO_RPM_F1_QTMR_V1_CNTV_CVAL_LO_INM(m)      \
        in_dword_masked(HWIO_RPM_F1_QTMR_V1_CNTV_CVAL_LO_ADDR, m)
#define HWIO_RPM_F1_QTMR_V1_CNTV_CVAL_LO_OUT(v)      \
        out_dword(HWIO_RPM_F1_QTMR_V1_CNTV_CVAL_LO_ADDR,v)
#define HWIO_RPM_F1_QTMR_V1_CNTV_CVAL_LO_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_F1_QTMR_V1_CNTV_CVAL_LO_ADDR,m,v,HWIO_RPM_F1_QTMR_V1_CNTV_CVAL_LO_IN)
#define HWIO_RPM_F1_QTMR_V1_CNTV_CVAL_LO_CNTV_CVAL_L0_BMSK          0xffffffff
#define HWIO_RPM_F1_QTMR_V1_CNTV_CVAL_LO_CNTV_CVAL_L0_SHFT                 0x0

#define HWIO_RPM_F1_QTMR_V1_CNTV_CVAL_HI_ADDR                       (RPM_F1_QTMR_V1_F1_REG_BASE      + 0x00000034)
#define HWIO_RPM_F1_QTMR_V1_CNTV_CVAL_HI_RMSK                         0xffffff
#define HWIO_RPM_F1_QTMR_V1_CNTV_CVAL_HI_IN          \
        in_dword_masked(HWIO_RPM_F1_QTMR_V1_CNTV_CVAL_HI_ADDR, HWIO_RPM_F1_QTMR_V1_CNTV_CVAL_HI_RMSK)
#define HWIO_RPM_F1_QTMR_V1_CNTV_CVAL_HI_INM(m)      \
        in_dword_masked(HWIO_RPM_F1_QTMR_V1_CNTV_CVAL_HI_ADDR, m)
#define HWIO_RPM_F1_QTMR_V1_CNTV_CVAL_HI_OUT(v)      \
        out_dword(HWIO_RPM_F1_QTMR_V1_CNTV_CVAL_HI_ADDR,v)
#define HWIO_RPM_F1_QTMR_V1_CNTV_CVAL_HI_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_F1_QTMR_V1_CNTV_CVAL_HI_ADDR,m,v,HWIO_RPM_F1_QTMR_V1_CNTV_CVAL_HI_IN)
#define HWIO_RPM_F1_QTMR_V1_CNTV_CVAL_HI_CNTV_CVAL_HI_BMSK            0xffffff
#define HWIO_RPM_F1_QTMR_V1_CNTV_CVAL_HI_CNTV_CVAL_HI_SHFT                 0x0

#define HWIO_RPM_F1_QTMR_V1_CNTV_TVAL_ADDR                          (RPM_F1_QTMR_V1_F1_REG_BASE      + 0x00000038)
#define HWIO_RPM_F1_QTMR_V1_CNTV_TVAL_RMSK                          0xffffffff
#define HWIO_RPM_F1_QTMR_V1_CNTV_TVAL_IN          \
        in_dword_masked(HWIO_RPM_F1_QTMR_V1_CNTV_TVAL_ADDR, HWIO_RPM_F1_QTMR_V1_CNTV_TVAL_RMSK)
#define HWIO_RPM_F1_QTMR_V1_CNTV_TVAL_INM(m)      \
        in_dword_masked(HWIO_RPM_F1_QTMR_V1_CNTV_TVAL_ADDR, m)
#define HWIO_RPM_F1_QTMR_V1_CNTV_TVAL_OUT(v)      \
        out_dword(HWIO_RPM_F1_QTMR_V1_CNTV_TVAL_ADDR,v)
#define HWIO_RPM_F1_QTMR_V1_CNTV_TVAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_F1_QTMR_V1_CNTV_TVAL_ADDR,m,v,HWIO_RPM_F1_QTMR_V1_CNTV_TVAL_IN)
#define HWIO_RPM_F1_QTMR_V1_CNTV_TVAL_CNTV_TVAL_BMSK                0xffffffff
#define HWIO_RPM_F1_QTMR_V1_CNTV_TVAL_CNTV_TVAL_SHFT                       0x0

#define HWIO_RPM_F1_QTMR_V1_CNTV_CTL_ADDR                           (RPM_F1_QTMR_V1_F1_REG_BASE      + 0x0000003c)
#define HWIO_RPM_F1_QTMR_V1_CNTV_CTL_RMSK                                  0x7
#define HWIO_RPM_F1_QTMR_V1_CNTV_CTL_IN          \
        in_dword_masked(HWIO_RPM_F1_QTMR_V1_CNTV_CTL_ADDR, HWIO_RPM_F1_QTMR_V1_CNTV_CTL_RMSK)
#define HWIO_RPM_F1_QTMR_V1_CNTV_CTL_INM(m)      \
        in_dword_masked(HWIO_RPM_F1_QTMR_V1_CNTV_CTL_ADDR, m)
#define HWIO_RPM_F1_QTMR_V1_CNTV_CTL_OUT(v)      \
        out_dword(HWIO_RPM_F1_QTMR_V1_CNTV_CTL_ADDR,v)
#define HWIO_RPM_F1_QTMR_V1_CNTV_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_F1_QTMR_V1_CNTV_CTL_ADDR,m,v,HWIO_RPM_F1_QTMR_V1_CNTV_CTL_IN)
#define HWIO_RPM_F1_QTMR_V1_CNTV_CTL_ISTAT_BMSK                            0x4
#define HWIO_RPM_F1_QTMR_V1_CNTV_CTL_ISTAT_SHFT                            0x2
#define HWIO_RPM_F1_QTMR_V1_CNTV_CTL_ISTAT_INTERRUPT_NOT_PENDING_FVAL        0x0
#define HWIO_RPM_F1_QTMR_V1_CNTV_CTL_ISTAT_INTERRUPT_PENDING_FVAL          0x1
#define HWIO_RPM_F1_QTMR_V1_CNTV_CTL_IMSK_BMSK                             0x2
#define HWIO_RPM_F1_QTMR_V1_CNTV_CTL_IMSK_SHFT                             0x1
#define HWIO_RPM_F1_QTMR_V1_CNTV_CTL_IMSK_UNMASK_INTERRUPT_FVAL            0x0
#define HWIO_RPM_F1_QTMR_V1_CNTV_CTL_IMSK_MASK_INTERRUPT_FVAL              0x1
#define HWIO_RPM_F1_QTMR_V1_CNTV_CTL_EN_BMSK                               0x1
#define HWIO_RPM_F1_QTMR_V1_CNTV_CTL_EN_SHFT                               0x0
#define HWIO_RPM_F1_QTMR_V1_CNTV_CTL_EN_DISABLED_FVAL                      0x0
#define HWIO_RPM_F1_QTMR_V1_CNTV_CTL_EN_ENABLED_FVAL                       0x1

#define HWIO_RPM_F1_QTMR_V1_VERSION_ADDR                            (RPM_F1_QTMR_V1_F1_REG_BASE      + 0x00000fd0)
#define HWIO_RPM_F1_QTMR_V1_VERSION_RMSK                            0xffffffff
#define HWIO_RPM_F1_QTMR_V1_VERSION_IN          \
        in_dword_masked(HWIO_RPM_F1_QTMR_V1_VERSION_ADDR, HWIO_RPM_F1_QTMR_V1_VERSION_RMSK)
#define HWIO_RPM_F1_QTMR_V1_VERSION_INM(m)      \
        in_dword_masked(HWIO_RPM_F1_QTMR_V1_VERSION_ADDR, m)
#define HWIO_RPM_F1_QTMR_V1_VERSION_MAJOR_BMSK                      0xf0000000
#define HWIO_RPM_F1_QTMR_V1_VERSION_MAJOR_SHFT                            0x1c
#define HWIO_RPM_F1_QTMR_V1_VERSION_MINOR_BMSK                       0xfff0000
#define HWIO_RPM_F1_QTMR_V1_VERSION_MINOR_SHFT                            0x10
#define HWIO_RPM_F1_QTMR_V1_VERSION_STEP_BMSK                           0xffff
#define HWIO_RPM_F1_QTMR_V1_VERSION_STEP_SHFT                              0x0

/*----------------------------------------------------------------------------
 * MODULE: RPM_MSTR_MPU
 *--------------------------------------------------------------------------*/

#define RPM_MSTR_MPU_REG_BASE                                                  (RPM_BASE      + 0x00086000)

#define HWIO_RPM_MSTR_MPU_XPU3_GCR0_ADDR                                       (RPM_MSTR_MPU_REG_BASE      + 0x00000000)
#define HWIO_RPM_MSTR_MPU_XPU3_GCR0_RMSK                                              0x1
#define HWIO_RPM_MSTR_MPU_XPU3_GCR0_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_GCR0_ADDR, HWIO_RPM_MSTR_MPU_XPU3_GCR0_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_GCR0_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_GCR0_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_GCR0_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_GCR0_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_GCR0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_GCR0_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_GCR0_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_GCR0_AADEN_BMSK                                        0x1
#define HWIO_RPM_MSTR_MPU_XPU3_GCR0_AADEN_SHFT                                        0x0

#define HWIO_RPM_MSTR_MPU_XPU3_SCR0_ADDR                                       (RPM_MSTR_MPU_REG_BASE      + 0x00000008)
#define HWIO_RPM_MSTR_MPU_XPU3_SCR0_RMSK                                            0x10f
#define HWIO_RPM_MSTR_MPU_XPU3_SCR0_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_SCR0_ADDR, HWIO_RPM_MSTR_MPU_XPU3_SCR0_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_SCR0_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_SCR0_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_SCR0_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_SCR0_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_SCR0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_SCR0_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_SCR0_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_SCR0_DYNAMIC_CLK_EN_BMSK                             0x100
#define HWIO_RPM_MSTR_MPU_XPU3_SCR0_DYNAMIC_CLK_EN_SHFT                               0x8
#define HWIO_RPM_MSTR_MPU_XPU3_SCR0_SCLEIE_BMSK                                       0x8
#define HWIO_RPM_MSTR_MPU_XPU3_SCR0_SCLEIE_SHFT                                       0x3
#define HWIO_RPM_MSTR_MPU_XPU3_SCR0_SCFGEIE_BMSK                                      0x4
#define HWIO_RPM_MSTR_MPU_XPU3_SCR0_SCFGEIE_SHFT                                      0x2
#define HWIO_RPM_MSTR_MPU_XPU3_SCR0_SCLERE_BMSK                                       0x2
#define HWIO_RPM_MSTR_MPU_XPU3_SCR0_SCLERE_SHFT                                       0x1
#define HWIO_RPM_MSTR_MPU_XPU3_SCR0_SCFGERE_BMSK                                      0x1
#define HWIO_RPM_MSTR_MPU_XPU3_SCR0_SCFGERE_SHFT                                      0x0

#define HWIO_RPM_MSTR_MPU_XPU3_CR0_ADDR                                        (RPM_MSTR_MPU_REG_BASE      + 0x00000010)
#define HWIO_RPM_MSTR_MPU_XPU3_CR0_RMSK                                             0x18f
#define HWIO_RPM_MSTR_MPU_XPU3_CR0_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_CR0_ADDR, HWIO_RPM_MSTR_MPU_XPU3_CR0_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_CR0_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_CR0_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_CR0_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_CR0_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_CR0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_CR0_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_CR0_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_CR0_DYNAMIC_CLK_EN_BMSK                              0x100
#define HWIO_RPM_MSTR_MPU_XPU3_CR0_DYNAMIC_CLK_EN_SHFT                                0x8
#define HWIO_RPM_MSTR_MPU_XPU3_CR0_VMIDEN_BMSK                                       0x80
#define HWIO_RPM_MSTR_MPU_XPU3_CR0_VMIDEN_SHFT                                        0x7
#define HWIO_RPM_MSTR_MPU_XPU3_CR0_CLEIE_BMSK                                         0x8
#define HWIO_RPM_MSTR_MPU_XPU3_CR0_CLEIE_SHFT                                         0x3
#define HWIO_RPM_MSTR_MPU_XPU3_CR0_CFGEIE_BMSK                                        0x4
#define HWIO_RPM_MSTR_MPU_XPU3_CR0_CFGEIE_SHFT                                        0x2
#define HWIO_RPM_MSTR_MPU_XPU3_CR0_CLERE_BMSK                                         0x2
#define HWIO_RPM_MSTR_MPU_XPU3_CR0_CLERE_SHFT                                         0x1
#define HWIO_RPM_MSTR_MPU_XPU3_CR0_CFGERE_BMSK                                        0x1
#define HWIO_RPM_MSTR_MPU_XPU3_CR0_CFGERE_SHFT                                        0x0

#define HWIO_RPM_MSTR_MPU_XPU3_RPU_ACR0_ADDR                                   (RPM_MSTR_MPU_REG_BASE      + 0x00000020)
#define HWIO_RPM_MSTR_MPU_XPU3_RPU_ACR0_RMSK                                   0xffffffff
#define HWIO_RPM_MSTR_MPU_XPU3_RPU_ACR0_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RPU_ACR0_ADDR, HWIO_RPM_MSTR_MPU_XPU3_RPU_ACR0_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_RPU_ACR0_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RPU_ACR0_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_RPU_ACR0_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_RPU_ACR0_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_RPU_ACR0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_RPU_ACR0_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_RPU_ACR0_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_RPU_ACR0_SUVMID_BMSK                            0xffffffff
#define HWIO_RPM_MSTR_MPU_XPU3_RPU_ACR0_SUVMID_SHFT                                   0x0

#define HWIO_RPM_MSTR_MPU_XPU3_UMR_RACR_ADDR                                   (RPM_MSTR_MPU_REG_BASE      + 0x00000040)
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_RACR_RMSK                                   0xffffffff
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_RACR_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_UMR_RACR_ADDR, HWIO_RPM_MSTR_MPU_XPU3_UMR_RACR_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_RACR_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_UMR_RACR_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_RACR_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_UMR_RACR_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_RACR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_UMR_RACR_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_UMR_RACR_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_RACR_RE_BMSK                                0xffffffff
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_RACR_RE_SHFT                                       0x0

#define HWIO_RPM_MSTR_MPU_XPU3_UMR_WACR_ADDR                                   (RPM_MSTR_MPU_REG_BASE      + 0x00000060)
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_WACR_RMSK                                   0xffffffff
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_WACR_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_UMR_WACR_ADDR, HWIO_RPM_MSTR_MPU_XPU3_UMR_WACR_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_WACR_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_UMR_WACR_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_WACR_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_UMR_WACR_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_WACR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_UMR_WACR_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_UMR_WACR_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_WACR_WE_BMSK                                0xffffffff
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_WACR_WE_SHFT                                       0x0

#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_GCR0_ADDR                                  (RPM_MSTR_MPU_REG_BASE      + 0x00000080)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_GCR0_RMSK                                         0x1
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_GCR0_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD0_GCR0_ADDR, HWIO_RPM_MSTR_MPU_XPU3_QAD0_GCR0_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_GCR0_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD0_GCR0_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_GCR0_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_QAD0_GCR0_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_GCR0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_QAD0_GCR0_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_QAD0_GCR0_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_GCR0_QAD0DEN_BMSK                                 0x1
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_GCR0_QAD0DEN_SHFT                                 0x0

#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_CR0_ADDR                                   (RPM_MSTR_MPU_REG_BASE      + 0x00000090)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_CR0_RMSK                                        0x10f
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_CR0_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD0_CR0_ADDR, HWIO_RPM_MSTR_MPU_XPU3_QAD0_CR0_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_CR0_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD0_CR0_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_CR0_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_QAD0_CR0_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_CR0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_QAD0_CR0_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_QAD0_CR0_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_CR0_DYNAMIC_CLK_EN_BMSK                         0x100
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_CR0_DYNAMIC_CLK_EN_SHFT                           0x8
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_CR0_CLEIE_BMSK                                    0x8
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_CR0_CLEIE_SHFT                                    0x3
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_CR0_CFGEIE_BMSK                                   0x4
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_CR0_CFGEIE_SHFT                                   0x2
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_CR0_CLERE_BMSK                                    0x2
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_CR0_CLERE_SHFT                                    0x1
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_CR0_CFGERE_BMSK                                   0x1
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_CR0_CFGERE_SHFT                                   0x0

#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_GCR0_ADDR                                  (RPM_MSTR_MPU_REG_BASE      + 0x00000100)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_GCR0_RMSK                                         0x1
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_GCR0_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD1_GCR0_ADDR, HWIO_RPM_MSTR_MPU_XPU3_QAD1_GCR0_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_GCR0_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD1_GCR0_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_GCR0_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_QAD1_GCR0_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_GCR0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_QAD1_GCR0_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_QAD1_GCR0_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_GCR0_QAD1DEN_BMSK                                 0x1
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_GCR0_QAD1DEN_SHFT                                 0x0

#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_CR0_ADDR                                   (RPM_MSTR_MPU_REG_BASE      + 0x00000110)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_CR0_RMSK                                        0x10f
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_CR0_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD1_CR0_ADDR, HWIO_RPM_MSTR_MPU_XPU3_QAD1_CR0_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_CR0_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD1_CR0_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_CR0_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_QAD1_CR0_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_CR0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_QAD1_CR0_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_QAD1_CR0_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_CR0_DYNAMIC_CLK_EN_BMSK                         0x100
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_CR0_DYNAMIC_CLK_EN_SHFT                           0x8
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_CR0_CLEIE_BMSK                                    0x8
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_CR0_CLEIE_SHFT                                    0x3
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_CR0_CFGEIE_BMSK                                   0x4
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_CR0_CFGEIE_SHFT                                   0x2
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_CR0_CLERE_BMSK                                    0x2
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_CR0_CLERE_SHFT                                    0x1
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_CR0_CFGERE_BMSK                                   0x1
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_CR0_CFGERE_SHFT                                   0x0

#define HWIO_RPM_MSTR_MPU_XPU3_UMR_GCR0_ADDR                                   (RPM_MSTR_MPU_REG_BASE      + 0x00000300)
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_GCR0_RMSK                                        0x107
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_GCR0_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_UMR_GCR0_ADDR, HWIO_RPM_MSTR_MPU_XPU3_UMR_GCR0_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_GCR0_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_UMR_GCR0_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_GCR0_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_UMR_GCR0_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_GCR0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_UMR_GCR0_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_UMR_GCR0_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_GCR0_UMR_SEC_APPS_BMSK                           0x100
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_GCR0_UMR_SEC_APPS_SHFT                             0x8
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_GCR0_UMR_OWNER_BMSK                                0x7
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_GCR0_UMR_OWNER_SHFT                                0x0

#define HWIO_RPM_MSTR_MPU_XPU3_UMR_CR0_ADDR                                    (RPM_MSTR_MPU_REG_BASE      + 0x00000310)
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_CR0_RMSK                                           0x1
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_CR0_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_UMR_CR0_ADDR, HWIO_RPM_MSTR_MPU_XPU3_UMR_CR0_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_CR0_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_UMR_CR0_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_CR0_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_UMR_CR0_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_CR0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_UMR_CR0_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_UMR_CR0_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_CR0_UMRSCLRDEN_APPS_BMSK                           0x1
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_CR0_UMRSCLRDEN_APPS_SHFT                           0x0

#define HWIO_RPM_MSTR_MPU_XPU3_UMR_CR1_ADDR                                    (RPM_MSTR_MPU_REG_BASE      + 0x00000314)
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_CR1_RMSK                                           0x7
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_CR1_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_UMR_CR1_ADDR, HWIO_RPM_MSTR_MPU_XPU3_UMR_CR1_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_CR1_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_UMR_CR1_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_CR1_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_UMR_CR1_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_CR1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_UMR_CR1_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_UMR_CR1_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_CR1_UMRCLRDEN_BMSK                                 0x7
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_CR1_UMRCLRDEN_SHFT                                 0x0

#define HWIO_RPM_MSTR_MPU_XPU3_UMR_CR2_ADDR                                    (RPM_MSTR_MPU_REG_BASE      + 0x00000318)
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_CR2_RMSK                                           0x1
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_CR2_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_UMR_CR2_ADDR, HWIO_RPM_MSTR_MPU_XPU3_UMR_CR2_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_CR2_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_UMR_CR2_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_CR2_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_UMR_CR2_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_CR2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_UMR_CR2_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_UMR_CR2_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_CR2_UMRSCLWREN_APPS_BMSK                           0x1
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_CR2_UMRSCLWREN_APPS_SHFT                           0x0

#define HWIO_RPM_MSTR_MPU_XPU3_UMR_CR3_ADDR                                    (RPM_MSTR_MPU_REG_BASE      + 0x0000031c)
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_CR3_RMSK                                           0x7
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_CR3_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_UMR_CR3_ADDR, HWIO_RPM_MSTR_MPU_XPU3_UMR_CR3_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_CR3_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_UMR_CR3_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_CR3_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_UMR_CR3_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_CR3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_UMR_CR3_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_UMR_CR3_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_CR3_UMRCLWREN_BMSK                                 0x7
#define HWIO_RPM_MSTR_MPU_XPU3_UMR_CR3_UMRCLWREN_SHFT                                 0x0

#define HWIO_RPM_MSTR_MPU_XPU3_IDR3_ADDR                                       (RPM_MSTR_MPU_REG_BASE      + 0x000003ec)
#define HWIO_RPM_MSTR_MPU_XPU3_IDR3_RMSK                                            0x3ff
#define HWIO_RPM_MSTR_MPU_XPU3_IDR3_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_IDR3_ADDR, HWIO_RPM_MSTR_MPU_XPU3_IDR3_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_IDR3_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_IDR3_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_IDR3_PT_BMSK                                         0x200
#define HWIO_RPM_MSTR_MPU_XPU3_IDR3_PT_SHFT                                           0x9
#define HWIO_RPM_MSTR_MPU_XPU3_IDR3_MV_BMSK                                         0x100
#define HWIO_RPM_MSTR_MPU_XPU3_IDR3_MV_SHFT                                           0x8
#define HWIO_RPM_MSTR_MPU_XPU3_IDR3_NVMID_BMSK                                       0xff
#define HWIO_RPM_MSTR_MPU_XPU3_IDR3_NVMID_SHFT                                        0x0

#define HWIO_RPM_MSTR_MPU_XPU3_IDR2_ADDR                                       (RPM_MSTR_MPU_REG_BASE      + 0x000003f0)
#define HWIO_RPM_MSTR_MPU_XPU3_IDR2_RMSK                                       0xffffff0f
#define HWIO_RPM_MSTR_MPU_XPU3_IDR2_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_IDR2_ADDR, HWIO_RPM_MSTR_MPU_XPU3_IDR2_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_IDR2_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_IDR2_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_IDR2_NONSEC_EN_BMSK                             0xff000000
#define HWIO_RPM_MSTR_MPU_XPU3_IDR2_NONSEC_EN_SHFT                                   0x18
#define HWIO_RPM_MSTR_MPU_XPU3_IDR2_SEC_EN_BMSK                                  0xff0000
#define HWIO_RPM_MSTR_MPU_XPU3_IDR2_SEC_EN_SHFT                                      0x10
#define HWIO_RPM_MSTR_MPU_XPU3_IDR2_VMIDACR_EN_BMSK                                0xff00
#define HWIO_RPM_MSTR_MPU_XPU3_IDR2_VMIDACR_EN_SHFT                                   0x8
#define HWIO_RPM_MSTR_MPU_XPU3_IDR2_NUM_QAD_BMSK                                      0xf
#define HWIO_RPM_MSTR_MPU_XPU3_IDR2_NUM_QAD_SHFT                                      0x0

#define HWIO_RPM_MSTR_MPU_XPU3_IDR1_ADDR                                       (RPM_MSTR_MPU_REG_BASE      + 0x000003f4)
#define HWIO_RPM_MSTR_MPU_XPU3_IDR1_RMSK                                       0x3f3f3f3f
#define HWIO_RPM_MSTR_MPU_XPU3_IDR1_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_IDR1_ADDR, HWIO_RPM_MSTR_MPU_XPU3_IDR1_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_IDR1_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_IDR1_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_IDR1_CLIENT_ADDR_WIDTH_BMSK                     0x3f000000
#define HWIO_RPM_MSTR_MPU_XPU3_IDR1_CLIENT_ADDR_WIDTH_SHFT                           0x18
#define HWIO_RPM_MSTR_MPU_XPU3_IDR1_CONFIG_ADDR_WIDTH_BMSK                       0x3f0000
#define HWIO_RPM_MSTR_MPU_XPU3_IDR1_CONFIG_ADDR_WIDTH_SHFT                           0x10
#define HWIO_RPM_MSTR_MPU_XPU3_IDR1_MSB_MPU_BMSK                                   0x3f00
#define HWIO_RPM_MSTR_MPU_XPU3_IDR1_MSB_MPU_SHFT                                      0x8
#define HWIO_RPM_MSTR_MPU_XPU3_IDR1_LSB_BMSK                                         0x3f
#define HWIO_RPM_MSTR_MPU_XPU3_IDR1_LSB_SHFT                                          0x0

#define HWIO_RPM_MSTR_MPU_XPU3_IDR0_ADDR                                       (RPM_MSTR_MPU_REG_BASE      + 0x000003f8)
#define HWIO_RPM_MSTR_MPU_XPU3_IDR0_RMSK                                        0x3ff0073
#define HWIO_RPM_MSTR_MPU_XPU3_IDR0_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_IDR0_ADDR, HWIO_RPM_MSTR_MPU_XPU3_IDR0_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_IDR0_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_IDR0_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_IDR0_NRG_BMSK                                    0x3ff0000
#define HWIO_RPM_MSTR_MPU_XPU3_IDR0_NRG_SHFT                                         0x10
#define HWIO_RPM_MSTR_MPU_XPU3_IDR0_BLED_BMSK                                        0x40
#define HWIO_RPM_MSTR_MPU_XPU3_IDR0_BLED_SHFT                                         0x6
#define HWIO_RPM_MSTR_MPU_XPU3_IDR0_CLIENTREQ_HALT_ACK_HW_EN_BMSK                    0x20
#define HWIO_RPM_MSTR_MPU_XPU3_IDR0_CLIENTREQ_HALT_ACK_HW_EN_SHFT                     0x5
#define HWIO_RPM_MSTR_MPU_XPU3_IDR0_XPU_CLIENT_PIPELINE_EN_BMSK                      0x10
#define HWIO_RPM_MSTR_MPU_XPU3_IDR0_XPU_CLIENT_PIPELINE_EN_SHFT                       0x4
#define HWIO_RPM_MSTR_MPU_XPU3_IDR0_XPUTYPE_BMSK                                      0x3
#define HWIO_RPM_MSTR_MPU_XPU3_IDR0_XPUTYPE_SHFT                                      0x0

#define HWIO_RPM_MSTR_MPU_XPU3_REV_ADDR                                        (RPM_MSTR_MPU_REG_BASE      + 0x000003fc)
#define HWIO_RPM_MSTR_MPU_XPU3_REV_RMSK                                        0xffffffff
#define HWIO_RPM_MSTR_MPU_XPU3_REV_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_REV_ADDR, HWIO_RPM_MSTR_MPU_XPU3_REV_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_REV_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_REV_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_REV_MAJOR_BMSK                                  0xf0000000
#define HWIO_RPM_MSTR_MPU_XPU3_REV_MAJOR_SHFT                                        0x1c
#define HWIO_RPM_MSTR_MPU_XPU3_REV_MINOR_BMSK                                   0xfff0000
#define HWIO_RPM_MSTR_MPU_XPU3_REV_MINOR_SHFT                                        0x10
#define HWIO_RPM_MSTR_MPU_XPU3_REV_STEP_BMSK                                       0xffff
#define HWIO_RPM_MSTR_MPU_XPU3_REV_STEP_SHFT                                          0x0

#define HWIO_RPM_MSTR_MPU_XPU3_RGN_FREESTATUSr_ADDR(r)                         (RPM_MSTR_MPU_REG_BASE      + 0x00000500 + 0x4 * (r))
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_FREESTATUSr_RMSK                               0xfffff
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_FREESTATUSr_MAXr                                     0
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_FREESTATUSr_INI(r)        \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGN_FREESTATUSr_ADDR(r), HWIO_RPM_MSTR_MPU_XPU3_RGN_FREESTATUSr_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_FREESTATUSr_INMI(r,mask)    \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGN_FREESTATUSr_ADDR(r), mask)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_FREESTATUSr_RGFREESTATUS_BMSK                  0xfffff
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_FREESTATUSr_RGFREESTATUS_SHFT                      0x0

#define HWIO_RPM_MSTR_MPU_XPU3_SEAR0_ADDR                                      (RPM_MSTR_MPU_REG_BASE      + 0x00000800)
#define HWIO_RPM_MSTR_MPU_XPU3_SEAR0_RMSK                                      0xffffffff
#define HWIO_RPM_MSTR_MPU_XPU3_SEAR0_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_SEAR0_ADDR, HWIO_RPM_MSTR_MPU_XPU3_SEAR0_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_SEAR0_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_SEAR0_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_SEAR0_ADDR_31_0_BMSK                            0xffffffff
#define HWIO_RPM_MSTR_MPU_XPU3_SEAR0_ADDR_31_0_SHFT                                   0x0

#define HWIO_RPM_MSTR_MPU_XPU3_SESR_ADDR                                       (RPM_MSTR_MPU_REG_BASE      + 0x00000808)
#define HWIO_RPM_MSTR_MPU_XPU3_SESR_RMSK                                              0xf
#define HWIO_RPM_MSTR_MPU_XPU3_SESR_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_SESR_ADDR, HWIO_RPM_MSTR_MPU_XPU3_SESR_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_SESR_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_SESR_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_SESR_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_SESR_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_SESR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_SESR_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_SESR_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_SESR_CLMULTI_BMSK                                      0x8
#define HWIO_RPM_MSTR_MPU_XPU3_SESR_CLMULTI_SHFT                                      0x3
#define HWIO_RPM_MSTR_MPU_XPU3_SESR_CFGMULTI_BMSK                                     0x4
#define HWIO_RPM_MSTR_MPU_XPU3_SESR_CFGMULTI_SHFT                                     0x2
#define HWIO_RPM_MSTR_MPU_XPU3_SESR_CLIENT_BMSK                                       0x2
#define HWIO_RPM_MSTR_MPU_XPU3_SESR_CLIENT_SHFT                                       0x1
#define HWIO_RPM_MSTR_MPU_XPU3_SESR_CFG_BMSK                                          0x1
#define HWIO_RPM_MSTR_MPU_XPU3_SESR_CFG_SHFT                                          0x0

#define HWIO_RPM_MSTR_MPU_XPU3_SESRRESTORE_ADDR                                (RPM_MSTR_MPU_REG_BASE      + 0x0000080c)
#define HWIO_RPM_MSTR_MPU_XPU3_SESRRESTORE_RMSK                                       0xf
#define HWIO_RPM_MSTR_MPU_XPU3_SESRRESTORE_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_SESRRESTORE_ADDR, HWIO_RPM_MSTR_MPU_XPU3_SESRRESTORE_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_SESRRESTORE_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_SESRRESTORE_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_SESRRESTORE_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_SESRRESTORE_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_SESRRESTORE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_SESRRESTORE_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_SESRRESTORE_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_SESRRESTORE_CLMULTI_BMSK                               0x8
#define HWIO_RPM_MSTR_MPU_XPU3_SESRRESTORE_CLMULTI_SHFT                               0x3
#define HWIO_RPM_MSTR_MPU_XPU3_SESRRESTORE_CFGMULTI_BMSK                              0x4
#define HWIO_RPM_MSTR_MPU_XPU3_SESRRESTORE_CFGMULTI_SHFT                              0x2
#define HWIO_RPM_MSTR_MPU_XPU3_SESRRESTORE_CLIENT_BMSK                                0x2
#define HWIO_RPM_MSTR_MPU_XPU3_SESRRESTORE_CLIENT_SHFT                                0x1
#define HWIO_RPM_MSTR_MPU_XPU3_SESRRESTORE_CFG_BMSK                                   0x1
#define HWIO_RPM_MSTR_MPU_XPU3_SESRRESTORE_CFG_SHFT                                   0x0

#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR0_ADDR                                    (RPM_MSTR_MPU_REG_BASE      + 0x00000810)
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR0_RMSK                                    0x60ffff0f
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR0_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_SESYNR0_ADDR, HWIO_RPM_MSTR_MPU_XPU3_SESYNR0_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR0_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_SESYNR0_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR0_AC_BMSK                                 0x40000000
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR0_AC_SHFT                                       0x1e
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR0_BURSTLEN_BMSK                           0x20000000
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR0_BURSTLEN_SHFT                                 0x1d
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR0_ASIZE_BMSK                                0xe00000
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR0_ASIZE_SHFT                                    0x15
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR0_ALEN_BMSK                                 0x1f0000
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR0_ALEN_SHFT                                     0x10
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR0_QAD_BMSK                                    0xff00
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR0_QAD_SHFT                                       0x8
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR0_XPRIV_BMSK                                     0x8
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR0_XPRIV_SHFT                                     0x3
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR0_XINST_BMSK                                     0x4
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR0_XINST_SHFT                                     0x2
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR0_AWRITE_BMSK                                    0x2
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR0_AWRITE_SHFT                                    0x1
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR0_XPROTNS_BMSK                                   0x1
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR0_XPROTNS_SHFT                                   0x0

#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR1_ADDR                                    (RPM_MSTR_MPU_REG_BASE      + 0x00000814)
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR1_RMSK                                    0xffffffff
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR1_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_SESYNR1_ADDR, HWIO_RPM_MSTR_MPU_XPU3_SESYNR1_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR1_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_SESYNR1_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR1_TID_BMSK                                0xff000000
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR1_TID_SHFT                                      0x18
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR1_VMID_BMSK                                 0xff0000
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR1_VMID_SHFT                                     0x10
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR1_BID_BMSK                                    0xe000
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR1_BID_SHFT                                       0xd
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR1_PID_BMSK                                    0x1f00
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR1_PID_SHFT                                       0x8
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR1_MID_BMSK                                      0xff
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR1_MID_SHFT                                       0x0

#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_ADDR                                    (RPM_MSTR_MPU_REG_BASE      + 0x00000818)
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_RMSK                                    0xffffff87
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_ADDR, HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_BAR_BMSK                                0xc0000000
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_BAR_SHFT                                      0x1e
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_BURST_BMSK                              0x20000000
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_BURST_SHFT                                    0x1d
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_CACHEABLE_BMSK                          0x10000000
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_CACHEABLE_SHFT                                0x1c
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_DEVICE_BMSK                              0x8000000
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_DEVICE_SHFT                                   0x1b
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_DEVICE_TYPE_BMSK                         0x6000000
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_DEVICE_TYPE_SHFT                              0x19
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_EARLYWRRESP_BMSK                         0x1000000
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_EARLYWRRESP_SHFT                              0x18
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_ERROR_BMSK                                0x800000
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_ERROR_SHFT                                    0x17
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_EXCLUSIVE_BMSK                            0x400000
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_EXCLUSIVE_SHFT                                0x16
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_FULL_BMSK                                 0x200000
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_FULL_SHFT                                     0x15
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_SHARED_BMSK                               0x100000
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_SHARED_SHFT                                   0x14
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_WRITETHROUGH_BMSK                          0x80000
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_WRITETHROUGH_SHFT                             0x13
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_INNERNOALLOCATE_BMSK                       0x40000
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_INNERNOALLOCATE_SHFT                          0x12
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_INNERCACHEABLE_BMSK                        0x20000
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_INNERCACHEABLE_SHFT                           0x11
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_INNERSHARED_BMSK                           0x10000
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_INNERSHARED_SHFT                              0x10
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_INNERTRANSIENT_BMSK                         0x8000
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_INNERTRANSIENT_SHFT                            0xf
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_INNERWRITETHROUGH_BMSK                      0x4000
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_INNERWRITETHROUGH_SHFT                         0xe
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_PORTMREL_BMSK                               0x2000
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_PORTMREL_SHFT                                  0xd
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_ORDEREDRD_BMSK                              0x1000
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_ORDEREDRD_SHFT                                 0xc
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_ORDEREDWR_BMSK                               0x800
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_ORDEREDWR_SHFT                                 0xb
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_OOORD_BMSK                                   0x400
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_OOORD_SHFT                                     0xa
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_OOOWR_BMSK                                   0x200
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_OOOWR_SHFT                                     0x9
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_NOALLOCATE_BMSK                              0x100
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_NOALLOCATE_SHFT                                0x8
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_TRANSIENT_BMSK                                0x80
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_TRANSIENT_SHFT                                 0x7
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_MEMTYPE_BMSK                                   0x7
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR2_MEMTYPE_SHFT                                   0x0

#define HWIO_RPM_MSTR_MPU_XPU3_SEAR1_ADDR                                      (RPM_MSTR_MPU_REG_BASE      + 0x00000804)
#define HWIO_RPM_MSTR_MPU_XPU3_SEAR1_RMSK                                      0xffffffff
#define HWIO_RPM_MSTR_MPU_XPU3_SEAR1_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_SEAR1_ADDR, HWIO_RPM_MSTR_MPU_XPU3_SEAR1_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_SEAR1_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_SEAR1_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_SEAR1_ADDR_63_32_BMSK                           0xffffffff
#define HWIO_RPM_MSTR_MPU_XPU3_SEAR1_ADDR_63_32_SHFT                                  0x0

#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR3_ADDR                                    (RPM_MSTR_MPU_REG_BASE      + 0x0000081c)
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR3_RMSK                                        0xffff
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR3_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_SESYNR3_ADDR, HWIO_RPM_MSTR_MPU_XPU3_SESYNR3_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR3_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_SESYNR3_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR3_SEC_AD_RG_MATCH_BMSK                        0xff00
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR3_SEC_AD_RG_MATCH_SHFT                           0x8
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR3_NONSEC_AD_RG_MATCH_BMSK                       0xff
#define HWIO_RPM_MSTR_MPU_XPU3_SESYNR3_NONSEC_AD_RG_MATCH_SHFT                        0x0

#define HWIO_RPM_MSTR_MPU_XPU3_RGN_START0_SSHADOW_ADDR                         (RPM_MSTR_MPU_REG_BASE      + 0x00000830)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_START0_SSHADOW_RMSK                         0xfffe0000
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_START0_SSHADOW_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGN_START0_SSHADOW_ADDR, HWIO_RPM_MSTR_MPU_XPU3_RGN_START0_SSHADOW_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_START0_SSHADOW_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGN_START0_SSHADOW_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_START0_SSHADOW_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_RGN_START0_SSHADOW_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_START0_SSHADOW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_RGN_START0_SSHADOW_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_RGN_START0_SSHADOW_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_START0_SSHADOW_ADDR_31_0_BMSK               0xfffe0000
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_START0_SSHADOW_ADDR_31_0_SHFT                     0x11

#define HWIO_RPM_MSTR_MPU_XPU3_RGN_START1_SSHADOW_ADDR                         (RPM_MSTR_MPU_REG_BASE      + 0x00000834)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_START1_SSHADOW_RMSK                                0xf
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_START1_SSHADOW_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGN_START1_SSHADOW_ADDR, HWIO_RPM_MSTR_MPU_XPU3_RGN_START1_SSHADOW_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_START1_SSHADOW_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGN_START1_SSHADOW_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_START1_SSHADOW_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_RGN_START1_SSHADOW_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_START1_SSHADOW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_RGN_START1_SSHADOW_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_RGN_START1_SSHADOW_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_START1_SSHADOW_ADDR_63_32_BMSK                     0xf
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_START1_SSHADOW_ADDR_63_32_SHFT                     0x0

#define HWIO_RPM_MSTR_MPU_XPU3_RGN_END0_SSHADOW_ADDR                           (RPM_MSTR_MPU_REG_BASE      + 0x00000838)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_END0_SSHADOW_RMSK                           0xfffe0000
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_END0_SSHADOW_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGN_END0_SSHADOW_ADDR, HWIO_RPM_MSTR_MPU_XPU3_RGN_END0_SSHADOW_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_END0_SSHADOW_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGN_END0_SSHADOW_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_END0_SSHADOW_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_RGN_END0_SSHADOW_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_END0_SSHADOW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_RGN_END0_SSHADOW_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_RGN_END0_SSHADOW_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_END0_SSHADOW_ADDR_31_0_BMSK                 0xfffe0000
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_END0_SSHADOW_ADDR_31_0_SHFT                       0x11

#define HWIO_RPM_MSTR_MPU_XPU3_RGN_END1_SSHADOW_ADDR                           (RPM_MSTR_MPU_REG_BASE      + 0x0000083c)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_END1_SSHADOW_RMSK                                  0xf
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_END1_SSHADOW_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGN_END1_SSHADOW_ADDR, HWIO_RPM_MSTR_MPU_XPU3_RGN_END1_SSHADOW_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_END1_SSHADOW_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGN_END1_SSHADOW_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_END1_SSHADOW_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_RGN_END1_SSHADOW_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_END1_SSHADOW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_RGN_END1_SSHADOW_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_RGN_END1_SSHADOW_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_END1_SSHADOW_ADDR_63_32_BMSK                       0xf
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_END1_SSHADOW_ADDR_63_32_SHFT                       0x0

#define HWIO_RPM_MSTR_MPU_XPU3_EAR0_ADDR                                       (RPM_MSTR_MPU_REG_BASE      + 0x00000880)
#define HWIO_RPM_MSTR_MPU_XPU3_EAR0_RMSK                                       0xffffffff
#define HWIO_RPM_MSTR_MPU_XPU3_EAR0_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_EAR0_ADDR, HWIO_RPM_MSTR_MPU_XPU3_EAR0_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_EAR0_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_EAR0_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_EAR0_ADDR_31_0_BMSK                             0xffffffff
#define HWIO_RPM_MSTR_MPU_XPU3_EAR0_ADDR_31_0_SHFT                                    0x0

#define HWIO_RPM_MSTR_MPU_XPU3_ESR_ADDR                                        (RPM_MSTR_MPU_REG_BASE      + 0x00000888)
#define HWIO_RPM_MSTR_MPU_XPU3_ESR_RMSK                                               0xf
#define HWIO_RPM_MSTR_MPU_XPU3_ESR_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_ESR_ADDR, HWIO_RPM_MSTR_MPU_XPU3_ESR_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_ESR_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_ESR_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_ESR_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_ESR_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_ESR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_ESR_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_ESR_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_ESR_CLMULTI_BMSK                                       0x8
#define HWIO_RPM_MSTR_MPU_XPU3_ESR_CLMULTI_SHFT                                       0x3
#define HWIO_RPM_MSTR_MPU_XPU3_ESR_CFGMULTI_BMSK                                      0x4
#define HWIO_RPM_MSTR_MPU_XPU3_ESR_CFGMULTI_SHFT                                      0x2
#define HWIO_RPM_MSTR_MPU_XPU3_ESR_CLIENT_BMSK                                        0x2
#define HWIO_RPM_MSTR_MPU_XPU3_ESR_CLIENT_SHFT                                        0x1
#define HWIO_RPM_MSTR_MPU_XPU3_ESR_CFG_BMSK                                           0x1
#define HWIO_RPM_MSTR_MPU_XPU3_ESR_CFG_SHFT                                           0x0

#define HWIO_RPM_MSTR_MPU_XPU3_ESRRESTORE_ADDR                                 (RPM_MSTR_MPU_REG_BASE      + 0x0000088c)
#define HWIO_RPM_MSTR_MPU_XPU3_ESRRESTORE_RMSK                                        0xf
#define HWIO_RPM_MSTR_MPU_XPU3_ESRRESTORE_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_ESRRESTORE_ADDR, HWIO_RPM_MSTR_MPU_XPU3_ESRRESTORE_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_ESRRESTORE_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_ESRRESTORE_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_ESRRESTORE_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_ESRRESTORE_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_ESRRESTORE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_ESRRESTORE_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_ESRRESTORE_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_ESRRESTORE_CLMULTI_BMSK                                0x8
#define HWIO_RPM_MSTR_MPU_XPU3_ESRRESTORE_CLMULTI_SHFT                                0x3
#define HWIO_RPM_MSTR_MPU_XPU3_ESRRESTORE_CFGMULTI_BMSK                               0x4
#define HWIO_RPM_MSTR_MPU_XPU3_ESRRESTORE_CFGMULTI_SHFT                               0x2
#define HWIO_RPM_MSTR_MPU_XPU3_ESRRESTORE_CLIENT_BMSK                                 0x2
#define HWIO_RPM_MSTR_MPU_XPU3_ESRRESTORE_CLIENT_SHFT                                 0x1
#define HWIO_RPM_MSTR_MPU_XPU3_ESRRESTORE_CFG_BMSK                                    0x1
#define HWIO_RPM_MSTR_MPU_XPU3_ESRRESTORE_CFG_SHFT                                    0x0

#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR0_ADDR                                     (RPM_MSTR_MPU_REG_BASE      + 0x00000890)
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR0_RMSK                                     0x60ffff0f
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR0_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_ESYNR0_ADDR, HWIO_RPM_MSTR_MPU_XPU3_ESYNR0_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR0_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_ESYNR0_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR0_AC_BMSK                                  0x40000000
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR0_AC_SHFT                                        0x1e
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR0_BURSTLEN_BMSK                            0x20000000
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR0_BURSTLEN_SHFT                                  0x1d
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR0_ASIZE_BMSK                                 0xe00000
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR0_ASIZE_SHFT                                     0x15
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR0_ALEN_BMSK                                  0x1f0000
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR0_ALEN_SHFT                                      0x10
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR0_QAD_BMSK                                     0xff00
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR0_QAD_SHFT                                        0x8
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR0_XPRIV_BMSK                                      0x8
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR0_XPRIV_SHFT                                      0x3
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR0_XINST_BMSK                                      0x4
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR0_XINST_SHFT                                      0x2
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR0_AWRITE_BMSK                                     0x2
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR0_AWRITE_SHFT                                     0x1
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR0_XPROTNS_BMSK                                    0x1
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR0_XPROTNS_SHFT                                    0x0

#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR1_ADDR                                     (RPM_MSTR_MPU_REG_BASE      + 0x00000894)
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR1_RMSK                                     0xffffffff
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR1_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_ESYNR1_ADDR, HWIO_RPM_MSTR_MPU_XPU3_ESYNR1_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR1_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_ESYNR1_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR1_TID_BMSK                                 0xff000000
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR1_TID_SHFT                                       0x18
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR1_VMID_BMSK                                  0xff0000
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR1_VMID_SHFT                                      0x10
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR1_BID_BMSK                                     0xe000
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR1_BID_SHFT                                        0xd
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR1_PID_BMSK                                     0x1f00
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR1_PID_SHFT                                        0x8
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR1_MID_BMSK                                       0xff
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR1_MID_SHFT                                        0x0

#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_ADDR                                     (RPM_MSTR_MPU_REG_BASE      + 0x00000898)
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_RMSK                                     0xffffff87
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_ADDR, HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_BAR_BMSK                                 0xc0000000
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_BAR_SHFT                                       0x1e
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_BURST_BMSK                               0x20000000
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_BURST_SHFT                                     0x1d
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_CACHEABLE_BMSK                           0x10000000
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_CACHEABLE_SHFT                                 0x1c
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_DEVICE_BMSK                               0x8000000
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_DEVICE_SHFT                                    0x1b
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_DEVICE_TYPE_BMSK                          0x6000000
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_DEVICE_TYPE_SHFT                               0x19
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_EARLYWRRESP_BMSK                          0x1000000
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_EARLYWRRESP_SHFT                               0x18
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_ERROR_BMSK                                 0x800000
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_ERROR_SHFT                                     0x17
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_EXCLUSIVE_BMSK                             0x400000
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_EXCLUSIVE_SHFT                                 0x16
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_FULL_BMSK                                  0x200000
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_FULL_SHFT                                      0x15
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_SHARED_BMSK                                0x100000
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_SHARED_SHFT                                    0x14
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_WRITETHROUGH_BMSK                           0x80000
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_WRITETHROUGH_SHFT                              0x13
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_INNERNOALLOCATE_BMSK                        0x40000
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_INNERNOALLOCATE_SHFT                           0x12
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_INNERCACHEABLE_BMSK                         0x20000
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_INNERCACHEABLE_SHFT                            0x11
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_INNERSHARED_BMSK                            0x10000
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_INNERSHARED_SHFT                               0x10
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_INNERTRANSIENT_BMSK                          0x8000
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_INNERTRANSIENT_SHFT                             0xf
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_INNERWRITETHROUGH_BMSK                       0x4000
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_INNERWRITETHROUGH_SHFT                          0xe
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_PORTMREL_BMSK                                0x2000
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_PORTMREL_SHFT                                   0xd
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_ORDEREDRD_BMSK                               0x1000
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_ORDEREDRD_SHFT                                  0xc
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_ORDEREDWR_BMSK                                0x800
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_ORDEREDWR_SHFT                                  0xb
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_OOORD_BMSK                                    0x400
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_OOORD_SHFT                                      0xa
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_OOOWR_BMSK                                    0x200
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_OOOWR_SHFT                                      0x9
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_NOALLOCATE_BMSK                               0x100
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_NOALLOCATE_SHFT                                 0x8
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_TRANSIENT_BMSK                                 0x80
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_TRANSIENT_SHFT                                  0x7
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_MEMTYPE_BMSK                                    0x7
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR2_MEMTYPE_SHFT                                    0x0

#define HWIO_RPM_MSTR_MPU_XPU3_EAR1_ADDR                                       (RPM_MSTR_MPU_REG_BASE      + 0x00000884)
#define HWIO_RPM_MSTR_MPU_XPU3_EAR1_RMSK                                       0xffffffff
#define HWIO_RPM_MSTR_MPU_XPU3_EAR1_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_EAR1_ADDR, HWIO_RPM_MSTR_MPU_XPU3_EAR1_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_EAR1_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_EAR1_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_EAR1_ADDR_63_32_BMSK                            0xffffffff
#define HWIO_RPM_MSTR_MPU_XPU3_EAR1_ADDR_63_32_SHFT                                   0x0

#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR3_ADDR                                     (RPM_MSTR_MPU_REG_BASE      + 0x0000089c)
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR3_RMSK                                         0xffff
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR3_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_ESYNR3_ADDR, HWIO_RPM_MSTR_MPU_XPU3_ESYNR3_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR3_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_ESYNR3_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR3_SEC_AD_RG_MATCH_BMSK                         0xff00
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR3_SEC_AD_RG_MATCH_SHFT                            0x8
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR3_NONSEC_AD_RG_MATCH_BMSK                        0xff
#define HWIO_RPM_MSTR_MPU_XPU3_ESYNR3_NONSEC_AD_RG_MATCH_SHFT                         0x0

#define HWIO_RPM_MSTR_MPU_XPU3_RGN_START0_SHADOW_ADDR                          (RPM_MSTR_MPU_REG_BASE      + 0x000008b0)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_START0_SHADOW_RMSK                          0xfffe0000
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_START0_SHADOW_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGN_START0_SHADOW_ADDR, HWIO_RPM_MSTR_MPU_XPU3_RGN_START0_SHADOW_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_START0_SHADOW_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGN_START0_SHADOW_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_START0_SHADOW_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_RGN_START0_SHADOW_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_START0_SHADOW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_RGN_START0_SHADOW_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_RGN_START0_SHADOW_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_START0_SHADOW_ADDR_31_0_BMSK                0xfffe0000
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_START0_SHADOW_ADDR_31_0_SHFT                      0x11

#define HWIO_RPM_MSTR_MPU_XPU3_RGN_START1_SHADOW_ADDR                          (RPM_MSTR_MPU_REG_BASE      + 0x000008b4)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_START1_SHADOW_RMSK                                 0xf
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_START1_SHADOW_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGN_START1_SHADOW_ADDR, HWIO_RPM_MSTR_MPU_XPU3_RGN_START1_SHADOW_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_START1_SHADOW_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGN_START1_SHADOW_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_START1_SHADOW_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_RGN_START1_SHADOW_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_START1_SHADOW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_RGN_START1_SHADOW_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_RGN_START1_SHADOW_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_START1_SHADOW_ADDR_63_32_BMSK                      0xf
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_START1_SHADOW_ADDR_63_32_SHFT                      0x0

#define HWIO_RPM_MSTR_MPU_XPU3_RGN_END0_SHADOW_ADDR                            (RPM_MSTR_MPU_REG_BASE      + 0x000008b8)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_END0_SHADOW_RMSK                            0xfffe0000
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_END0_SHADOW_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGN_END0_SHADOW_ADDR, HWIO_RPM_MSTR_MPU_XPU3_RGN_END0_SHADOW_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_END0_SHADOW_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGN_END0_SHADOW_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_END0_SHADOW_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_RGN_END0_SHADOW_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_END0_SHADOW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_RGN_END0_SHADOW_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_RGN_END0_SHADOW_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_END0_SHADOW_ADDR_31_0_BMSK                  0xfffe0000
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_END0_SHADOW_ADDR_31_0_SHFT                        0x11

#define HWIO_RPM_MSTR_MPU_XPU3_RGN_END1_SHADOW_ADDR                            (RPM_MSTR_MPU_REG_BASE      + 0x000008bc)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_END1_SHADOW_RMSK                                   0xf
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_END1_SHADOW_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGN_END1_SHADOW_ADDR, HWIO_RPM_MSTR_MPU_XPU3_RGN_END1_SHADOW_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_END1_SHADOW_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGN_END1_SHADOW_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_END1_SHADOW_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_RGN_END1_SHADOW_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_END1_SHADOW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_RGN_END1_SHADOW_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_RGN_END1_SHADOW_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_END1_SHADOW_ADDR_63_32_BMSK                        0xf
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_END1_SHADOW_ADDR_63_32_SHFT                        0x0

#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_EAR0_ADDR                                  (RPM_MSTR_MPU_REG_BASE      + 0x00000880)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_EAR0_RMSK                                  0xffffffff
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_EAR0_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD0_EAR0_ADDR, HWIO_RPM_MSTR_MPU_XPU3_QAD0_EAR0_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_EAR0_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD0_EAR0_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_EAR0_ADDR_31_0_BMSK                        0xffffffff
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_EAR0_ADDR_31_0_SHFT                               0x0

#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESR_ADDR                                   (RPM_MSTR_MPU_REG_BASE      + 0x00000888)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESR_RMSK                                          0xf
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESR_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESR_ADDR, HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESR_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESR_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESR_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESR_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESR_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESR_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESR_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESR_CLMULTI_BMSK                                  0x8
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESR_CLMULTI_SHFT                                  0x3
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESR_CFGMULTI_BMSK                                 0x4
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESR_CFGMULTI_SHFT                                 0x2
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESR_CLIENT_BMSK                                   0x2
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESR_CLIENT_SHFT                                   0x1
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESR_CFG_BMSK                                      0x1
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESR_CFG_SHFT                                      0x0

#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESRRESTORE_ADDR                            (RPM_MSTR_MPU_REG_BASE      + 0x0000088c)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESRRESTORE_RMSK                                   0xf
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESRRESTORE_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESRRESTORE_ADDR, HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESRRESTORE_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESRRESTORE_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESRRESTORE_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESRRESTORE_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESRRESTORE_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESRRESTORE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESRRESTORE_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESRRESTORE_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESRRESTORE_CLMULTI_BMSK                           0x8
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESRRESTORE_CLMULTI_SHFT                           0x3
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESRRESTORE_CFGMULTI_BMSK                          0x4
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESRRESTORE_CFGMULTI_SHFT                          0x2
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESRRESTORE_CLIENT_BMSK                            0x2
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESRRESTORE_CLIENT_SHFT                            0x1
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESRRESTORE_CFG_BMSK                               0x1
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESRRESTORE_CFG_SHFT                               0x0

#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR0_ADDR                                (RPM_MSTR_MPU_REG_BASE      + 0x00000890)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR0_RMSK                                0x60ffff0f
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR0_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR0_ADDR, HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR0_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR0_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR0_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR0_AC_BMSK                             0x40000000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR0_AC_SHFT                                   0x1e
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR0_BURSTLEN_BMSK                       0x20000000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR0_BURSTLEN_SHFT                             0x1d
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR0_ASIZE_BMSK                            0xe00000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR0_ASIZE_SHFT                                0x15
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR0_ALEN_BMSK                             0x1f0000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR0_ALEN_SHFT                                 0x10
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR0_QAD_BMSK                                0xff00
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR0_QAD_SHFT                                   0x8
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR0_XPRIV_BMSK                                 0x8
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR0_XPRIV_SHFT                                 0x3
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR0_XINST_BMSK                                 0x4
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR0_XINST_SHFT                                 0x2
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR0_AWRITE_BMSK                                0x2
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR0_AWRITE_SHFT                                0x1
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR0_XPROTNS_BMSK                               0x1
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR0_XPROTNS_SHFT                               0x0

#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR1_ADDR                                (RPM_MSTR_MPU_REG_BASE      + 0x00000894)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR1_RMSK                                0xffffffff
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR1_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR1_ADDR, HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR1_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR1_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR1_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR1_TID_BMSK                            0xff000000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR1_TID_SHFT                                  0x18
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR1_VMID_BMSK                             0xff0000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR1_VMID_SHFT                                 0x10
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR1_BID_BMSK                                0xe000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR1_BID_SHFT                                   0xd
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR1_PID_BMSK                                0x1f00
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR1_PID_SHFT                                   0x8
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR1_MID_BMSK                                  0xff
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR1_MID_SHFT                                   0x0

#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_ADDR                                (RPM_MSTR_MPU_REG_BASE      + 0x00000898)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_RMSK                                0xffffff87
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_ADDR, HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_BAR_BMSK                            0xc0000000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_BAR_SHFT                                  0x1e
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_BURST_BMSK                          0x20000000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_BURST_SHFT                                0x1d
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_CACHEABLE_BMSK                      0x10000000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_CACHEABLE_SHFT                            0x1c
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_DEVICE_BMSK                          0x8000000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_DEVICE_SHFT                               0x1b
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_DEVICE_TYPE_BMSK                     0x6000000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_DEVICE_TYPE_SHFT                          0x19
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_EARLYWRRESP_BMSK                     0x1000000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_EARLYWRRESP_SHFT                          0x18
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_ERROR_BMSK                            0x800000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_ERROR_SHFT                                0x17
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_EXCLUSIVE_BMSK                        0x400000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_EXCLUSIVE_SHFT                            0x16
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_FULL_BMSK                             0x200000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_FULL_SHFT                                 0x15
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_SHARED_BMSK                           0x100000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_SHARED_SHFT                               0x14
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_WRITETHROUGH_BMSK                      0x80000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_WRITETHROUGH_SHFT                         0x13
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_INNERNOALLOCATE_BMSK                   0x40000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_INNERNOALLOCATE_SHFT                      0x12
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_INNERCACHEABLE_BMSK                    0x20000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_INNERCACHEABLE_SHFT                       0x11
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_INNERSHARED_BMSK                       0x10000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_INNERSHARED_SHFT                          0x10
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_INNERTRANSIENT_BMSK                     0x8000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_INNERTRANSIENT_SHFT                        0xf
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_INNERWRITETHROUGH_BMSK                  0x4000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_INNERWRITETHROUGH_SHFT                     0xe
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_PORTMREL_BMSK                           0x2000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_PORTMREL_SHFT                              0xd
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_ORDEREDRD_BMSK                          0x1000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_ORDEREDRD_SHFT                             0xc
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_ORDEREDWR_BMSK                           0x800
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_ORDEREDWR_SHFT                             0xb
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_OOORD_BMSK                               0x400
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_OOORD_SHFT                                 0xa
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_OOOWR_BMSK                               0x200
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_OOOWR_SHFT                                 0x9
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_NOALLOCATE_BMSK                          0x100
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_NOALLOCATE_SHFT                            0x8
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_TRANSIENT_BMSK                            0x80
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_TRANSIENT_SHFT                             0x7
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_MEMTYPE_BMSK                               0x7
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR2_MEMTYPE_SHFT                               0x0

#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_EAR1_ADDR                                  (RPM_MSTR_MPU_REG_BASE      + 0x00000884)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_EAR1_RMSK                                  0xffffffff
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_EAR1_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD0_EAR1_ADDR, HWIO_RPM_MSTR_MPU_XPU3_QAD0_EAR1_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_EAR1_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD0_EAR1_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_EAR1_ADDR_63_32_BMSK                       0xffffffff
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_EAR1_ADDR_63_32_SHFT                              0x0

#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR3_ADDR                                (RPM_MSTR_MPU_REG_BASE      + 0x0000089c)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR3_RMSK                                    0xffff
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR3_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR3_ADDR, HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR3_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR3_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR3_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR3_SEC_AD_RG_MATCH_BMSK                    0xff00
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR3_SEC_AD_RG_MATCH_SHFT                       0x8
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR3_NONSEC_AD_RG_MATCH_BMSK                   0xff
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_ESYNR3_NONSEC_AD_RG_MATCH_SHFT                    0x0

#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_START0_SHADOW_ADDR                     (RPM_MSTR_MPU_REG_BASE      + 0x000008b0)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_START0_SHADOW_RMSK                     0xfffe0000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_START0_SHADOW_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_START0_SHADOW_ADDR, HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_START0_SHADOW_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_START0_SHADOW_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_START0_SHADOW_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_START0_SHADOW_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_START0_SHADOW_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_START0_SHADOW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_START0_SHADOW_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_START0_SHADOW_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_START0_SHADOW_ADDR_31_0_BMSK           0xfffe0000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_START0_SHADOW_ADDR_31_0_SHFT                 0x11

#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_START1_SHADOW_ADDR                     (RPM_MSTR_MPU_REG_BASE      + 0x000008b4)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_START1_SHADOW_RMSK                            0xf
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_START1_SHADOW_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_START1_SHADOW_ADDR, HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_START1_SHADOW_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_START1_SHADOW_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_START1_SHADOW_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_START1_SHADOW_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_START1_SHADOW_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_START1_SHADOW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_START1_SHADOW_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_START1_SHADOW_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_START1_SHADOW_ADDR_63_32_BMSK                 0xf
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_START1_SHADOW_ADDR_63_32_SHFT                 0x0

#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_END0_SHADOW_ADDR                       (RPM_MSTR_MPU_REG_BASE      + 0x000008b8)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_END0_SHADOW_RMSK                       0xfffe0000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_END0_SHADOW_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_END0_SHADOW_ADDR, HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_END0_SHADOW_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_END0_SHADOW_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_END0_SHADOW_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_END0_SHADOW_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_END0_SHADOW_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_END0_SHADOW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_END0_SHADOW_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_END0_SHADOW_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_END0_SHADOW_ADDR_31_0_BMSK             0xfffe0000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_END0_SHADOW_ADDR_31_0_SHFT                   0x11

#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_END1_SHADOW_ADDR                       (RPM_MSTR_MPU_REG_BASE      + 0x000008bc)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_END1_SHADOW_RMSK                              0xf
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_END1_SHADOW_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_END1_SHADOW_ADDR, HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_END1_SHADOW_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_END1_SHADOW_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_END1_SHADOW_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_END1_SHADOW_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_END1_SHADOW_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_END1_SHADOW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_END1_SHADOW_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_END1_SHADOW_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_END1_SHADOW_ADDR_63_32_BMSK                   0xf
#define HWIO_RPM_MSTR_MPU_XPU3_QAD0_RGN_END1_SHADOW_ADDR_63_32_SHFT                   0x0

#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_EAR0_ADDR                                  (RPM_MSTR_MPU_REG_BASE      + 0x00000880)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_EAR0_RMSK                                  0xffffffff
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_EAR0_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD1_EAR0_ADDR, HWIO_RPM_MSTR_MPU_XPU3_QAD1_EAR0_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_EAR0_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD1_EAR0_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_EAR0_ADDR_31_0_BMSK                        0xffffffff
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_EAR0_ADDR_31_0_SHFT                               0x0

#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESR_ADDR                                   (RPM_MSTR_MPU_REG_BASE      + 0x00000888)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESR_RMSK                                          0xf
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESR_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESR_ADDR, HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESR_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESR_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESR_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESR_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESR_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESR_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESR_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESR_CLMULTI_BMSK                                  0x8
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESR_CLMULTI_SHFT                                  0x3
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESR_CFGMULTI_BMSK                                 0x4
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESR_CFGMULTI_SHFT                                 0x2
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESR_CLIENT_BMSK                                   0x2
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESR_CLIENT_SHFT                                   0x1
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESR_CFG_BMSK                                      0x1
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESR_CFG_SHFT                                      0x0

#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESRRESTORE_ADDR                            (RPM_MSTR_MPU_REG_BASE      + 0x0000088c)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESRRESTORE_RMSK                                   0xf
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESRRESTORE_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESRRESTORE_ADDR, HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESRRESTORE_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESRRESTORE_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESRRESTORE_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESRRESTORE_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESRRESTORE_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESRRESTORE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESRRESTORE_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESRRESTORE_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESRRESTORE_CLMULTI_BMSK                           0x8
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESRRESTORE_CLMULTI_SHFT                           0x3
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESRRESTORE_CFGMULTI_BMSK                          0x4
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESRRESTORE_CFGMULTI_SHFT                          0x2
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESRRESTORE_CLIENT_BMSK                            0x2
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESRRESTORE_CLIENT_SHFT                            0x1
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESRRESTORE_CFG_BMSK                               0x1
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESRRESTORE_CFG_SHFT                               0x0

#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR0_ADDR                                (RPM_MSTR_MPU_REG_BASE      + 0x00000890)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR0_RMSK                                0x60ffff0f
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR0_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR0_ADDR, HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR0_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR0_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR0_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR0_AC_BMSK                             0x40000000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR0_AC_SHFT                                   0x1e
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR0_BURSTLEN_BMSK                       0x20000000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR0_BURSTLEN_SHFT                             0x1d
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR0_ASIZE_BMSK                            0xe00000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR0_ASIZE_SHFT                                0x15
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR0_ALEN_BMSK                             0x1f0000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR0_ALEN_SHFT                                 0x10
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR0_QAD_BMSK                                0xff00
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR0_QAD_SHFT                                   0x8
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR0_XPRIV_BMSK                                 0x8
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR0_XPRIV_SHFT                                 0x3
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR0_XINST_BMSK                                 0x4
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR0_XINST_SHFT                                 0x2
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR0_AWRITE_BMSK                                0x2
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR0_AWRITE_SHFT                                0x1
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR0_XPROTNS_BMSK                               0x1
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR0_XPROTNS_SHFT                               0x0

#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR1_ADDR                                (RPM_MSTR_MPU_REG_BASE      + 0x00000894)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR1_RMSK                                0xffffffff
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR1_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR1_ADDR, HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR1_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR1_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR1_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR1_TID_BMSK                            0xff000000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR1_TID_SHFT                                  0x18
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR1_VMID_BMSK                             0xff0000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR1_VMID_SHFT                                 0x10
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR1_BID_BMSK                                0xe000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR1_BID_SHFT                                   0xd
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR1_PID_BMSK                                0x1f00
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR1_PID_SHFT                                   0x8
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR1_MID_BMSK                                  0xff
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR1_MID_SHFT                                   0x0

#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_ADDR                                (RPM_MSTR_MPU_REG_BASE      + 0x00000898)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_RMSK                                0xffffff87
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_ADDR, HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_BAR_BMSK                            0xc0000000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_BAR_SHFT                                  0x1e
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_BURST_BMSK                          0x20000000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_BURST_SHFT                                0x1d
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_CACHEABLE_BMSK                      0x10000000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_CACHEABLE_SHFT                            0x1c
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_DEVICE_BMSK                          0x8000000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_DEVICE_SHFT                               0x1b
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_DEVICE_TYPE_BMSK                     0x6000000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_DEVICE_TYPE_SHFT                          0x19
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_EARLYWRRESP_BMSK                     0x1000000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_EARLYWRRESP_SHFT                          0x18
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_ERROR_BMSK                            0x800000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_ERROR_SHFT                                0x17
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_EXCLUSIVE_BMSK                        0x400000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_EXCLUSIVE_SHFT                            0x16
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_FULL_BMSK                             0x200000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_FULL_SHFT                                 0x15
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_SHARED_BMSK                           0x100000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_SHARED_SHFT                               0x14
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_WRITETHROUGH_BMSK                      0x80000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_WRITETHROUGH_SHFT                         0x13
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_INNERNOALLOCATE_BMSK                   0x40000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_INNERNOALLOCATE_SHFT                      0x12
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_INNERCACHEABLE_BMSK                    0x20000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_INNERCACHEABLE_SHFT                       0x11
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_INNERSHARED_BMSK                       0x10000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_INNERSHARED_SHFT                          0x10
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_INNERTRANSIENT_BMSK                     0x8000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_INNERTRANSIENT_SHFT                        0xf
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_INNERWRITETHROUGH_BMSK                  0x4000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_INNERWRITETHROUGH_SHFT                     0xe
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_PORTMREL_BMSK                           0x2000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_PORTMREL_SHFT                              0xd
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_ORDEREDRD_BMSK                          0x1000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_ORDEREDRD_SHFT                             0xc
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_ORDEREDWR_BMSK                           0x800
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_ORDEREDWR_SHFT                             0xb
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_OOORD_BMSK                               0x400
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_OOORD_SHFT                                 0xa
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_OOOWR_BMSK                               0x200
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_OOOWR_SHFT                                 0x9
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_NOALLOCATE_BMSK                          0x100
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_NOALLOCATE_SHFT                            0x8
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_TRANSIENT_BMSK                            0x80
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_TRANSIENT_SHFT                             0x7
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_MEMTYPE_BMSK                               0x7
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR2_MEMTYPE_SHFT                               0x0

#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_EAR1_ADDR                                  (RPM_MSTR_MPU_REG_BASE      + 0x00000884)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_EAR1_RMSK                                  0xffffffff
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_EAR1_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD1_EAR1_ADDR, HWIO_RPM_MSTR_MPU_XPU3_QAD1_EAR1_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_EAR1_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD1_EAR1_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_EAR1_ADDR_63_32_BMSK                       0xffffffff
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_EAR1_ADDR_63_32_SHFT                              0x0

#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR3_ADDR                                (RPM_MSTR_MPU_REG_BASE      + 0x0000089c)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR3_RMSK                                    0xffff
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR3_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR3_ADDR, HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR3_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR3_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR3_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR3_SEC_AD_RG_MATCH_BMSK                    0xff00
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR3_SEC_AD_RG_MATCH_SHFT                       0x8
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR3_NONSEC_AD_RG_MATCH_BMSK                   0xff
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_ESYNR3_NONSEC_AD_RG_MATCH_SHFT                    0x0

#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_START0_SHADOW_ADDR                     (RPM_MSTR_MPU_REG_BASE      + 0x000008b0)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_START0_SHADOW_RMSK                     0xfffe0000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_START0_SHADOW_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_START0_SHADOW_ADDR, HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_START0_SHADOW_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_START0_SHADOW_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_START0_SHADOW_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_START0_SHADOW_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_START0_SHADOW_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_START0_SHADOW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_START0_SHADOW_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_START0_SHADOW_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_START0_SHADOW_ADDR_31_0_BMSK           0xfffe0000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_START0_SHADOW_ADDR_31_0_SHFT                 0x11

#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_START1_SHADOW_ADDR                     (RPM_MSTR_MPU_REG_BASE      + 0x000008b4)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_START1_SHADOW_RMSK                            0xf
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_START1_SHADOW_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_START1_SHADOW_ADDR, HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_START1_SHADOW_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_START1_SHADOW_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_START1_SHADOW_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_START1_SHADOW_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_START1_SHADOW_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_START1_SHADOW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_START1_SHADOW_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_START1_SHADOW_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_START1_SHADOW_ADDR_63_32_BMSK                 0xf
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_START1_SHADOW_ADDR_63_32_SHFT                 0x0

#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_END0_SHADOW_ADDR                       (RPM_MSTR_MPU_REG_BASE      + 0x000008b8)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_END0_SHADOW_RMSK                       0xfffe0000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_END0_SHADOW_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_END0_SHADOW_ADDR, HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_END0_SHADOW_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_END0_SHADOW_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_END0_SHADOW_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_END0_SHADOW_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_END0_SHADOW_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_END0_SHADOW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_END0_SHADOW_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_END0_SHADOW_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_END0_SHADOW_ADDR_31_0_BMSK             0xfffe0000
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_END0_SHADOW_ADDR_31_0_SHFT                   0x11

#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_END1_SHADOW_ADDR                       (RPM_MSTR_MPU_REG_BASE      + 0x000008bc)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_END1_SHADOW_RMSK                              0xf
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_END1_SHADOW_IN          \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_END1_SHADOW_ADDR, HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_END1_SHADOW_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_END1_SHADOW_INM(m)      \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_END1_SHADOW_ADDR, m)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_END1_SHADOW_OUT(v)      \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_END1_SHADOW_ADDR,v)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_END1_SHADOW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_END1_SHADOW_ADDR,m,v,HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_END1_SHADOW_IN)
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_END1_SHADOW_ADDR_63_32_BMSK                   0xf
#define HWIO_RPM_MSTR_MPU_XPU3_QAD1_RGN_END1_SHADOW_ADDR_63_32_SHFT                   0x0

#define HWIO_RPM_MSTR_MPU_XPU3_RGN_OWNERSTATUSr_ADDR(r)                        (RPM_MSTR_MPU_REG_BASE      + 0x00000900 + 0x4 * (r))
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_OWNERSTATUSr_RMSK                              0xfffff
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_OWNERSTATUSr_MAXr                                    0
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_OWNERSTATUSr_INI(r)        \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGN_OWNERSTATUSr_ADDR(r), HWIO_RPM_MSTR_MPU_XPU3_RGN_OWNERSTATUSr_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_OWNERSTATUSr_INMI(r,mask)    \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGN_OWNERSTATUSr_ADDR(r), mask)
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_OWNERSTATUSr_RGOWNERSTATUS_BMSK                0xfffff
#define HWIO_RPM_MSTR_MPU_XPU3_RGN_OWNERSTATUSr_RGOWNERSTATUS_SHFT                    0x0

#define HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR0_ADDR(n)                                (RPM_MSTR_MPU_REG_BASE      + 0x00001000 + 0x80 * (n))
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR0_RMSK                                        0x107
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR0_MAXn                                           19
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR0_INI(n)        \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR0_ADDR(n), HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR0_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR0_INMI(n,mask)    \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR0_ADDR(n), mask)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR0_OUTI(n,val)    \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR0_ADDR(n),val)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR0_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR0_ADDR(n),mask,val,HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR0_INI(n))
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR0_RG_SEC_APPS_BMSK                            0x100
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR0_RG_SEC_APPS_SHFT                              0x8
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR0_RG_OWNER_BMSK                                 0x7
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR0_RG_OWNER_SHFT                                 0x0

#define HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR1_ADDR(n)                                (RPM_MSTR_MPU_REG_BASE      + 0x00001004 + 0x80 * (n))
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR1_RMSK                                   0x80000000
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR1_MAXn                                           19
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR1_INI(n)        \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR1_ADDR(n), HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR1_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR1_INMI(n,mask)    \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR1_ADDR(n), mask)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR1_OUTI(n,val)    \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR1_ADDR(n),val)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR1_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR1_ADDR(n),mask,val,HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR1_INI(n))
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR1_PD_BMSK                                0x80000000
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR1_PD_SHFT                                      0x1f

#define HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR2_ADDR(n)                                (RPM_MSTR_MPU_REG_BASE      + 0x00001008 + 0x80 * (n))
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR2_RMSK                                          0x3
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR2_MAXn                                           19
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR2_INI(n)        \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR2_ADDR(n), HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR2_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR2_INMI(n,mask)    \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR2_ADDR(n), mask)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR2_OUTI(n,val)    \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR2_ADDR(n),val)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR2_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR2_ADDR(n),mask,val,HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR2_INI(n))
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR2_ASRC_BMSK                                     0x2
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR2_ASRC_SHFT                                     0x1
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR2_CSRC_BMSK                                     0x1
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_GCR2_CSRC_SHFT                                     0x0

#define HWIO_RPM_MSTR_MPU_XPU3_RGn_CR0_ADDR(n)                                 (RPM_MSTR_MPU_REG_BASE      + 0x00001010 + 0x80 * (n))
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_CR0_RMSK                                           0x1
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_CR0_MAXn                                            19
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_CR0_INI(n)        \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGn_CR0_ADDR(n), HWIO_RPM_MSTR_MPU_XPU3_RGn_CR0_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_CR0_INMI(n,mask)    \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGn_CR0_ADDR(n), mask)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_CR0_OUTI(n,val)    \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_RGn_CR0_ADDR(n),val)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_CR0_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_RGn_CR0_ADDR(n),mask,val,HWIO_RPM_MSTR_MPU_XPU3_RGn_CR0_INI(n))
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_CR0_RGSCLRDEN_APPS_BMSK                            0x1
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_CR0_RGSCLRDEN_APPS_SHFT                            0x0

#define HWIO_RPM_MSTR_MPU_XPU3_RGn_CR1_ADDR(n)                                 (RPM_MSTR_MPU_REG_BASE      + 0x00001014 + 0x80 * (n))
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_CR1_RMSK                                           0x7
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_CR1_MAXn                                            19
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_CR1_INI(n)        \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGn_CR1_ADDR(n), HWIO_RPM_MSTR_MPU_XPU3_RGn_CR1_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_CR1_INMI(n,mask)    \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGn_CR1_ADDR(n), mask)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_CR1_OUTI(n,val)    \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_RGn_CR1_ADDR(n),val)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_CR1_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_RGn_CR1_ADDR(n),mask,val,HWIO_RPM_MSTR_MPU_XPU3_RGn_CR1_INI(n))
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_CR1_RGCLRDEN_BMSK                                  0x7
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_CR1_RGCLRDEN_SHFT                                  0x0

#define HWIO_RPM_MSTR_MPU_XPU3_RGn_CR2_ADDR(n)                                 (RPM_MSTR_MPU_REG_BASE      + 0x00001018 + 0x80 * (n))
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_CR2_RMSK                                           0x1
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_CR2_MAXn                                            19
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_CR2_INI(n)        \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGn_CR2_ADDR(n), HWIO_RPM_MSTR_MPU_XPU3_RGn_CR2_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_CR2_INMI(n,mask)    \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGn_CR2_ADDR(n), mask)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_CR2_OUTI(n,val)    \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_RGn_CR2_ADDR(n),val)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_CR2_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_RGn_CR2_ADDR(n),mask,val,HWIO_RPM_MSTR_MPU_XPU3_RGn_CR2_INI(n))
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_CR2_RGSCLWREN_APPS_BMSK                            0x1
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_CR2_RGSCLWREN_APPS_SHFT                            0x0

#define HWIO_RPM_MSTR_MPU_XPU3_RGn_CR3_ADDR(n)                                 (RPM_MSTR_MPU_REG_BASE      + 0x0000101c + 0x80 * (n))
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_CR3_RMSK                                           0x7
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_CR3_MAXn                                            19
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_CR3_INI(n)        \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGn_CR3_ADDR(n), HWIO_RPM_MSTR_MPU_XPU3_RGn_CR3_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_CR3_INMI(n,mask)    \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGn_CR3_ADDR(n), mask)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_CR3_OUTI(n,val)    \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_RGn_CR3_ADDR(n),val)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_CR3_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_RGn_CR3_ADDR(n),mask,val,HWIO_RPM_MSTR_MPU_XPU3_RGn_CR3_INI(n))
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_CR3_RGCLWREN_BMSK                                  0x7
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_CR3_RGCLWREN_SHFT                                  0x0

#define HWIO_RPM_MSTR_MPU_XPU3_RGn_START0_ADDR(n)                              (RPM_MSTR_MPU_REG_BASE      + 0x00001030 + 0x80 * (n))
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_START0_RMSK                                 0xfffe0000
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_START0_MAXn                                         19
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_START0_INI(n)        \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGn_START0_ADDR(n), HWIO_RPM_MSTR_MPU_XPU3_RGn_START0_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_START0_INMI(n,mask)    \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGn_START0_ADDR(n), mask)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_START0_OUTI(n,val)    \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_RGn_START0_ADDR(n),val)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_START0_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_RGn_START0_ADDR(n),mask,val,HWIO_RPM_MSTR_MPU_XPU3_RGn_START0_INI(n))
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_START0_ADDR_31_0_BMSK                       0xfffe0000
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_START0_ADDR_31_0_SHFT                             0x11

#define HWIO_RPM_MSTR_MPU_XPU3_RGn_START1_ADDR(n)                              (RPM_MSTR_MPU_REG_BASE      + 0x00001034 + 0x80 * (n))
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_START1_RMSK                                        0xf
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_START1_MAXn                                         19
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_START1_INI(n)        \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGn_START1_ADDR(n), HWIO_RPM_MSTR_MPU_XPU3_RGn_START1_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_START1_INMI(n,mask)    \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGn_START1_ADDR(n), mask)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_START1_OUTI(n,val)    \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_RGn_START1_ADDR(n),val)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_START1_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_RGn_START1_ADDR(n),mask,val,HWIO_RPM_MSTR_MPU_XPU3_RGn_START1_INI(n))
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_START1_ADDR_63_32_BMSK                             0xf
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_START1_ADDR_63_32_SHFT                             0x0

#define HWIO_RPM_MSTR_MPU_XPU3_RGn_END0_ADDR(n)                                (RPM_MSTR_MPU_REG_BASE      + 0x00001038 + 0x80 * (n))
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_END0_RMSK                                   0xfffe0000
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_END0_MAXn                                           19
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_END0_INI(n)        \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGn_END0_ADDR(n), HWIO_RPM_MSTR_MPU_XPU3_RGn_END0_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_END0_INMI(n,mask)    \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGn_END0_ADDR(n), mask)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_END0_OUTI(n,val)    \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_RGn_END0_ADDR(n),val)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_END0_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_RGn_END0_ADDR(n),mask,val,HWIO_RPM_MSTR_MPU_XPU3_RGn_END0_INI(n))
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_END0_ADDR_31_0_BMSK                         0xfffe0000
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_END0_ADDR_31_0_SHFT                               0x11

#define HWIO_RPM_MSTR_MPU_XPU3_RGn_END1_ADDR(n)                                (RPM_MSTR_MPU_REG_BASE      + 0x0000103c + 0x80 * (n))
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_END1_RMSK                                          0xf
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_END1_MAXn                                           19
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_END1_INI(n)        \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGn_END1_ADDR(n), HWIO_RPM_MSTR_MPU_XPU3_RGn_END1_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_END1_INMI(n,mask)    \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGn_END1_ADDR(n), mask)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_END1_OUTI(n,val)    \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_RGn_END1_ADDR(n),val)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_END1_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_RGn_END1_ADDR(n),mask,val,HWIO_RPM_MSTR_MPU_XPU3_RGn_END1_INI(n))
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_END1_ADDR_63_32_BMSK                               0xf
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_END1_ADDR_63_32_SHFT                               0x0

#define HWIO_RPM_MSTR_MPU_XPU3_RGn_RACR_ADDR(n)                                (RPM_MSTR_MPU_REG_BASE      + 0x00001040 + 0x80 * (n))
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_RACR_RMSK                                   0xffffffff
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_RACR_MAXn                                           19
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_RACR_INI(n)        \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGn_RACR_ADDR(n), HWIO_RPM_MSTR_MPU_XPU3_RGn_RACR_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_RACR_INMI(n,mask)    \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGn_RACR_ADDR(n), mask)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_RACR_OUTI(n,val)    \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_RGn_RACR_ADDR(n),val)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_RACR_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_RGn_RACR_ADDR(n),mask,val,HWIO_RPM_MSTR_MPU_XPU3_RGn_RACR_INI(n))
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_RACR_RE_BMSK                                0xffffffff
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_RACR_RE_SHFT                                       0x0

#define HWIO_RPM_MSTR_MPU_XPU3_RGn_WACR_ADDR(n)                                (RPM_MSTR_MPU_REG_BASE      + 0x00001060 + 0x80 * (n))
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_WACR_RMSK                                   0xffffffff
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_WACR_MAXn                                           19
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_WACR_INI(n)        \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGn_WACR_ADDR(n), HWIO_RPM_MSTR_MPU_XPU3_RGn_WACR_RMSK)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_WACR_INMI(n,mask)    \
        in_dword_masked(HWIO_RPM_MSTR_MPU_XPU3_RGn_WACR_ADDR(n), mask)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_WACR_OUTI(n,val)    \
        out_dword(HWIO_RPM_MSTR_MPU_XPU3_RGn_WACR_ADDR(n),val)
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_WACR_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_RPM_MSTR_MPU_XPU3_RGn_WACR_ADDR(n),mask,val,HWIO_RPM_MSTR_MPU_XPU3_RGn_WACR_INI(n))
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_WACR_WE_BMSK                                0xffffffff
#define HWIO_RPM_MSTR_MPU_XPU3_RGn_WACR_WE_SHFT                                       0x0

/*----------------------------------------------------------------------------
 * MODULE: RPM_VMIDMT
 *--------------------------------------------------------------------------*/

#define RPM_VMIDMT_REG_BASE                                      (RPM_BASE      + 0x00088000)

#define HWIO_RPM_VMIDMT_SCR0_ADDR                                (RPM_VMIDMT_REG_BASE      + 0x00000000)
#define HWIO_RPM_VMIDMT_SCR0_RMSK                                0x3fd707f5
#define HWIO_RPM_VMIDMT_SCR0_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_SCR0_ADDR, HWIO_RPM_VMIDMT_SCR0_RMSK)
#define HWIO_RPM_VMIDMT_SCR0_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_SCR0_ADDR, m)
#define HWIO_RPM_VMIDMT_SCR0_OUT(v)      \
        out_dword(HWIO_RPM_VMIDMT_SCR0_ADDR,v)
#define HWIO_RPM_VMIDMT_SCR0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_VMIDMT_SCR0_ADDR,m,v,HWIO_RPM_VMIDMT_SCR0_IN)
#define HWIO_RPM_VMIDMT_SCR0_NSCFG_BMSK                          0x30000000
#define HWIO_RPM_VMIDMT_SCR0_NSCFG_SHFT                                0x1c
#define HWIO_RPM_VMIDMT_SCR0_WACFG_BMSK                           0xc000000
#define HWIO_RPM_VMIDMT_SCR0_WACFG_SHFT                                0x1a
#define HWIO_RPM_VMIDMT_SCR0_RACFG_BMSK                           0x3000000
#define HWIO_RPM_VMIDMT_SCR0_RACFG_SHFT                                0x18
#define HWIO_RPM_VMIDMT_SCR0_SHCFG_BMSK                            0xc00000
#define HWIO_RPM_VMIDMT_SCR0_SHCFG_SHFT                                0x16
#define HWIO_RPM_VMIDMT_SCR0_MTCFG_BMSK                            0x100000
#define HWIO_RPM_VMIDMT_SCR0_MTCFG_SHFT                                0x14
#define HWIO_RPM_VMIDMT_SCR0_MEMATTR_BMSK                           0x70000
#define HWIO_RPM_VMIDMT_SCR0_MEMATTR_SHFT                              0x10
#define HWIO_RPM_VMIDMT_SCR0_USFCFG_BMSK                              0x400
#define HWIO_RPM_VMIDMT_SCR0_USFCFG_SHFT                                0xa
#define HWIO_RPM_VMIDMT_SCR0_GSE_BMSK                                 0x200
#define HWIO_RPM_VMIDMT_SCR0_GSE_SHFT                                   0x9
#define HWIO_RPM_VMIDMT_SCR0_STALLD_BMSK                              0x100
#define HWIO_RPM_VMIDMT_SCR0_STALLD_SHFT                                0x8
#define HWIO_RPM_VMIDMT_SCR0_TRANSIENTCFG_BMSK                         0xc0
#define HWIO_RPM_VMIDMT_SCR0_TRANSIENTCFG_SHFT                          0x6
#define HWIO_RPM_VMIDMT_SCR0_GCFGFIE_BMSK                              0x20
#define HWIO_RPM_VMIDMT_SCR0_GCFGFIE_SHFT                               0x5
#define HWIO_RPM_VMIDMT_SCR0_GCFGERE_BMSK                              0x10
#define HWIO_RPM_VMIDMT_SCR0_GCFGERE_SHFT                               0x4
#define HWIO_RPM_VMIDMT_SCR0_GFIE_BMSK                                  0x4
#define HWIO_RPM_VMIDMT_SCR0_GFIE_SHFT                                  0x2
#define HWIO_RPM_VMIDMT_SCR0_CLIENTPD_BMSK                              0x1
#define HWIO_RPM_VMIDMT_SCR0_CLIENTPD_SHFT                              0x0

#define HWIO_RPM_VMIDMT_SCR1_ADDR                                (RPM_VMIDMT_REG_BASE      + 0x00000004)
#define HWIO_RPM_VMIDMT_SCR1_RMSK                                 0x1000100
#define HWIO_RPM_VMIDMT_SCR1_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_SCR1_ADDR, HWIO_RPM_VMIDMT_SCR1_RMSK)
#define HWIO_RPM_VMIDMT_SCR1_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_SCR1_ADDR, m)
#define HWIO_RPM_VMIDMT_SCR1_OUT(v)      \
        out_dword(HWIO_RPM_VMIDMT_SCR1_ADDR,v)
#define HWIO_RPM_VMIDMT_SCR1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_VMIDMT_SCR1_ADDR,m,v,HWIO_RPM_VMIDMT_SCR1_IN)
#define HWIO_RPM_VMIDMT_SCR1_GASRAE_BMSK                          0x1000000
#define HWIO_RPM_VMIDMT_SCR1_GASRAE_SHFT                               0x18
#define HWIO_RPM_VMIDMT_SCR1_NSNUMSMRGO_BMSK                          0x100
#define HWIO_RPM_VMIDMT_SCR1_NSNUMSMRGO_SHFT                            0x8

#define HWIO_RPM_VMIDMT_SCR2_ADDR                                (RPM_VMIDMT_REG_BASE      + 0x00000008)
#define HWIO_RPM_VMIDMT_SCR2_RMSK                                      0x1f
#define HWIO_RPM_VMIDMT_SCR2_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_SCR2_ADDR, HWIO_RPM_VMIDMT_SCR2_RMSK)
#define HWIO_RPM_VMIDMT_SCR2_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_SCR2_ADDR, m)
#define HWIO_RPM_VMIDMT_SCR2_OUT(v)      \
        out_dword(HWIO_RPM_VMIDMT_SCR2_ADDR,v)
#define HWIO_RPM_VMIDMT_SCR2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_VMIDMT_SCR2_ADDR,m,v,HWIO_RPM_VMIDMT_SCR2_IN)
#define HWIO_RPM_VMIDMT_SCR2_BPVMID_BMSK                               0x1f
#define HWIO_RPM_VMIDMT_SCR2_BPVMID_SHFT                                0x0

#define HWIO_RPM_VMIDMT_SACR_ADDR                                (RPM_VMIDMT_REG_BASE      + 0x00000010)
#define HWIO_RPM_VMIDMT_SACR_RMSK                                0x70000013
#define HWIO_RPM_VMIDMT_SACR_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_SACR_ADDR, HWIO_RPM_VMIDMT_SACR_RMSK)
#define HWIO_RPM_VMIDMT_SACR_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_SACR_ADDR, m)
#define HWIO_RPM_VMIDMT_SACR_OUT(v)      \
        out_dword(HWIO_RPM_VMIDMT_SACR_ADDR,v)
#define HWIO_RPM_VMIDMT_SACR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_VMIDMT_SACR_ADDR,m,v,HWIO_RPM_VMIDMT_SACR_IN)
#define HWIO_RPM_VMIDMT_SACR_BPRCNSH_BMSK                        0x40000000
#define HWIO_RPM_VMIDMT_SACR_BPRCNSH_SHFT                              0x1e
#define HWIO_RPM_VMIDMT_SACR_BPRCISH_BMSK                        0x20000000
#define HWIO_RPM_VMIDMT_SACR_BPRCISH_SHFT                              0x1d
#define HWIO_RPM_VMIDMT_SACR_BPRCOSH_BMSK                        0x10000000
#define HWIO_RPM_VMIDMT_SACR_BPRCOSH_SHFT                              0x1c
#define HWIO_RPM_VMIDMT_SACR_BPREQPRIORITYCFG_BMSK                     0x10
#define HWIO_RPM_VMIDMT_SACR_BPREQPRIORITYCFG_SHFT                      0x4
#define HWIO_RPM_VMIDMT_SACR_BPREQPRIORITY_BMSK                         0x3
#define HWIO_RPM_VMIDMT_SACR_BPREQPRIORITY_SHFT                         0x0

#define HWIO_RPM_VMIDMT_SIDR0_ADDR                               (RPM_VMIDMT_REG_BASE      + 0x00000020)
#define HWIO_RPM_VMIDMT_SIDR0_RMSK                               0x88001eff
#define HWIO_RPM_VMIDMT_SIDR0_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_SIDR0_ADDR, HWIO_RPM_VMIDMT_SIDR0_RMSK)
#define HWIO_RPM_VMIDMT_SIDR0_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_SIDR0_ADDR, m)
#define HWIO_RPM_VMIDMT_SIDR0_SES_BMSK                           0x80000000
#define HWIO_RPM_VMIDMT_SIDR0_SES_SHFT                                 0x1f
#define HWIO_RPM_VMIDMT_SIDR0_SMS_BMSK                            0x8000000
#define HWIO_RPM_VMIDMT_SIDR0_SMS_SHFT                                 0x1b
#define HWIO_RPM_VMIDMT_SIDR0_NUMSIDB_BMSK                           0x1e00
#define HWIO_RPM_VMIDMT_SIDR0_NUMSIDB_SHFT                              0x9
#define HWIO_RPM_VMIDMT_SIDR0_NUMSMRG_BMSK                             0xff
#define HWIO_RPM_VMIDMT_SIDR0_NUMSMRG_SHFT                              0x0

#define HWIO_RPM_VMIDMT_SIDR1_ADDR                               (RPM_VMIDMT_REG_BASE      + 0x00000024)
#define HWIO_RPM_VMIDMT_SIDR1_RMSK                                   0x9f00
#define HWIO_RPM_VMIDMT_SIDR1_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_SIDR1_ADDR, HWIO_RPM_VMIDMT_SIDR1_RMSK)
#define HWIO_RPM_VMIDMT_SIDR1_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_SIDR1_ADDR, m)
#define HWIO_RPM_VMIDMT_SIDR1_SMCD_BMSK                              0x8000
#define HWIO_RPM_VMIDMT_SIDR1_SMCD_SHFT                                 0xf
#define HWIO_RPM_VMIDMT_SIDR1_SSDTP_BMSK                             0x1000
#define HWIO_RPM_VMIDMT_SIDR1_SSDTP_SHFT                                0xc
#define HWIO_RPM_VMIDMT_SIDR1_NUMSSDNDX_BMSK                          0xf00
#define HWIO_RPM_VMIDMT_SIDR1_NUMSSDNDX_SHFT                            0x8

#define HWIO_RPM_VMIDMT_SIDR2_ADDR                               (RPM_VMIDMT_REG_BASE      + 0x00000028)
#define HWIO_RPM_VMIDMT_SIDR2_RMSK                                     0xff
#define HWIO_RPM_VMIDMT_SIDR2_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_SIDR2_ADDR, HWIO_RPM_VMIDMT_SIDR2_RMSK)
#define HWIO_RPM_VMIDMT_SIDR2_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_SIDR2_ADDR, m)
#define HWIO_RPM_VMIDMT_SIDR2_OAS_BMSK                                 0xf0
#define HWIO_RPM_VMIDMT_SIDR2_OAS_SHFT                                  0x4
#define HWIO_RPM_VMIDMT_SIDR2_IAS_BMSK                                  0xf
#define HWIO_RPM_VMIDMT_SIDR2_IAS_SHFT                                  0x0

#define HWIO_RPM_VMIDMT_SIDR4_ADDR                               (RPM_VMIDMT_REG_BASE      + 0x00000030)
#define HWIO_RPM_VMIDMT_SIDR4_RMSK                               0xffffffff
#define HWIO_RPM_VMIDMT_SIDR4_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_SIDR4_ADDR, HWIO_RPM_VMIDMT_SIDR4_RMSK)
#define HWIO_RPM_VMIDMT_SIDR4_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_SIDR4_ADDR, m)
#define HWIO_RPM_VMIDMT_SIDR4_MAJOR_BMSK                         0xf0000000
#define HWIO_RPM_VMIDMT_SIDR4_MAJOR_SHFT                               0x1c
#define HWIO_RPM_VMIDMT_SIDR4_MINOR_BMSK                          0xfff0000
#define HWIO_RPM_VMIDMT_SIDR4_MINOR_SHFT                               0x10
#define HWIO_RPM_VMIDMT_SIDR4_STEP_BMSK                              0xffff
#define HWIO_RPM_VMIDMT_SIDR4_STEP_SHFT                                 0x0

#define HWIO_RPM_VMIDMT_SIDR5_ADDR                               (RPM_VMIDMT_REG_BASE      + 0x00000034)
#define HWIO_RPM_VMIDMT_SIDR5_RMSK                               0xffff03ff
#define HWIO_RPM_VMIDMT_SIDR5_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_SIDR5_ADDR, HWIO_RPM_VMIDMT_SIDR5_RMSK)
#define HWIO_RPM_VMIDMT_SIDR5_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_SIDR5_ADDR, m)
#define HWIO_RPM_VMIDMT_SIDR5_NUMSPDRB_BMSK                      0xff000000
#define HWIO_RPM_VMIDMT_SIDR5_NUMSPDRB_SHFT                            0x18
#define HWIO_RPM_VMIDMT_SIDR5_NUMMSDRB_BMSK                        0xff0000
#define HWIO_RPM_VMIDMT_SIDR5_NUMMSDRB_SHFT                            0x10
#define HWIO_RPM_VMIDMT_SIDR5_MSAE_BMSK                               0x200
#define HWIO_RPM_VMIDMT_SIDR5_MSAE_SHFT                                 0x9
#define HWIO_RPM_VMIDMT_SIDR5_QRIBE_BMSK                              0x100
#define HWIO_RPM_VMIDMT_SIDR5_QRIBE_SHFT                                0x8
#define HWIO_RPM_VMIDMT_SIDR5_NVMID_BMSK                               0xff
#define HWIO_RPM_VMIDMT_SIDR5_NVMID_SHFT                                0x0

#define HWIO_RPM_VMIDMT_SIDR7_ADDR                               (RPM_VMIDMT_REG_BASE      + 0x0000003c)
#define HWIO_RPM_VMIDMT_SIDR7_RMSK                                     0xff
#define HWIO_RPM_VMIDMT_SIDR7_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_SIDR7_ADDR, HWIO_RPM_VMIDMT_SIDR7_RMSK)
#define HWIO_RPM_VMIDMT_SIDR7_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_SIDR7_ADDR, m)
#define HWIO_RPM_VMIDMT_SIDR7_MAJOR_BMSK                               0xf0
#define HWIO_RPM_VMIDMT_SIDR7_MAJOR_SHFT                                0x4
#define HWIO_RPM_VMIDMT_SIDR7_MINOR_BMSK                                0xf
#define HWIO_RPM_VMIDMT_SIDR7_MINOR_SHFT                                0x0

#define HWIO_RPM_VMIDMT_SGFAR0_ADDR                              (RPM_VMIDMT_REG_BASE      + 0x00000040)
#define HWIO_RPM_VMIDMT_SGFAR0_RMSK                              0xffffffff
#define HWIO_RPM_VMIDMT_SGFAR0_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_SGFAR0_ADDR, HWIO_RPM_VMIDMT_SGFAR0_RMSK)
#define HWIO_RPM_VMIDMT_SGFAR0_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_SGFAR0_ADDR, m)
#define HWIO_RPM_VMIDMT_SGFAR0_SGFEA0_BMSK                       0xffffffff
#define HWIO_RPM_VMIDMT_SGFAR0_SGFEA0_SHFT                              0x0

#define HWIO_RPM_VMIDMT_SGFSR_ADDR                               (RPM_VMIDMT_REG_BASE      + 0x00000048)
#define HWIO_RPM_VMIDMT_SGFSR_RMSK                               0xc0000022
#define HWIO_RPM_VMIDMT_SGFSR_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_SGFSR_ADDR, HWIO_RPM_VMIDMT_SGFSR_RMSK)
#define HWIO_RPM_VMIDMT_SGFSR_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_SGFSR_ADDR, m)
#define HWIO_RPM_VMIDMT_SGFSR_OUT(v)      \
        out_dword(HWIO_RPM_VMIDMT_SGFSR_ADDR,v)
#define HWIO_RPM_VMIDMT_SGFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_VMIDMT_SGFSR_ADDR,m,v,HWIO_RPM_VMIDMT_SGFSR_IN)
#define HWIO_RPM_VMIDMT_SGFSR_MULTI_CLIENT_BMSK                  0x80000000
#define HWIO_RPM_VMIDMT_SGFSR_MULTI_CLIENT_SHFT                        0x1f
#define HWIO_RPM_VMIDMT_SGFSR_MULTI_CFG_BMSK                     0x40000000
#define HWIO_RPM_VMIDMT_SGFSR_MULTI_CFG_SHFT                           0x1e
#define HWIO_RPM_VMIDMT_SGFSR_CAF_BMSK                                 0x20
#define HWIO_RPM_VMIDMT_SGFSR_CAF_SHFT                                  0x5
#define HWIO_RPM_VMIDMT_SGFSR_USF_BMSK                                  0x2
#define HWIO_RPM_VMIDMT_SGFSR_USF_SHFT                                  0x1

#define HWIO_RPM_VMIDMT_SGFSRRESTORE_ADDR                        (RPM_VMIDMT_REG_BASE      + 0x0000004c)
#define HWIO_RPM_VMIDMT_SGFSRRESTORE_RMSK                        0xc0000022
#define HWIO_RPM_VMIDMT_SGFSRRESTORE_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_SGFSRRESTORE_ADDR, HWIO_RPM_VMIDMT_SGFSRRESTORE_RMSK)
#define HWIO_RPM_VMIDMT_SGFSRRESTORE_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_SGFSRRESTORE_ADDR, m)
#define HWIO_RPM_VMIDMT_SGFSRRESTORE_OUT(v)      \
        out_dword(HWIO_RPM_VMIDMT_SGFSRRESTORE_ADDR,v)
#define HWIO_RPM_VMIDMT_SGFSRRESTORE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_VMIDMT_SGFSRRESTORE_ADDR,m,v,HWIO_RPM_VMIDMT_SGFSRRESTORE_IN)
#define HWIO_RPM_VMIDMT_SGFSRRESTORE_MULTI_CLIENT_BMSK           0x80000000
#define HWIO_RPM_VMIDMT_SGFSRRESTORE_MULTI_CLIENT_SHFT                 0x1f
#define HWIO_RPM_VMIDMT_SGFSRRESTORE_MULTI_CFG_BMSK              0x40000000
#define HWIO_RPM_VMIDMT_SGFSRRESTORE_MULTI_CFG_SHFT                    0x1e
#define HWIO_RPM_VMIDMT_SGFSRRESTORE_CAF_BMSK                          0x20
#define HWIO_RPM_VMIDMT_SGFSRRESTORE_CAF_SHFT                           0x5
#define HWIO_RPM_VMIDMT_SGFSRRESTORE_USF_BMSK                           0x2
#define HWIO_RPM_VMIDMT_SGFSRRESTORE_USF_SHFT                           0x1

#define HWIO_RPM_VMIDMT_SGFSYNDR0_ADDR                           (RPM_VMIDMT_REG_BASE      + 0x00000050)
#define HWIO_RPM_VMIDMT_SGFSYNDR0_RMSK                                0x132
#define HWIO_RPM_VMIDMT_SGFSYNDR0_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_SGFSYNDR0_ADDR, HWIO_RPM_VMIDMT_SGFSYNDR0_RMSK)
#define HWIO_RPM_VMIDMT_SGFSYNDR0_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_SGFSYNDR0_ADDR, m)
#define HWIO_RPM_VMIDMT_SGFSYNDR0_MSSSELFAUTH_BMSK                    0x100
#define HWIO_RPM_VMIDMT_SGFSYNDR0_MSSSELFAUTH_SHFT                      0x8
#define HWIO_RPM_VMIDMT_SGFSYNDR0_NSATTR_BMSK                          0x20
#define HWIO_RPM_VMIDMT_SGFSYNDR0_NSATTR_SHFT                           0x5
#define HWIO_RPM_VMIDMT_SGFSYNDR0_NSSTATE_BMSK                         0x10
#define HWIO_RPM_VMIDMT_SGFSYNDR0_NSSTATE_SHFT                          0x4
#define HWIO_RPM_VMIDMT_SGFSYNDR0_WNR_BMSK                              0x2
#define HWIO_RPM_VMIDMT_SGFSYNDR0_WNR_SHFT                              0x1

#define HWIO_RPM_VMIDMT_SGFSYNDR1_ADDR                           (RPM_VMIDMT_REG_BASE      + 0x00000054)
#define HWIO_RPM_VMIDMT_SGFSYNDR1_RMSK                            0x1010001
#define HWIO_RPM_VMIDMT_SGFSYNDR1_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_SGFSYNDR1_ADDR, HWIO_RPM_VMIDMT_SGFSYNDR1_RMSK)
#define HWIO_RPM_VMIDMT_SGFSYNDR1_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_SGFSYNDR1_ADDR, m)
#define HWIO_RPM_VMIDMT_SGFSYNDR1_MSDINDEX_BMSK                   0x1000000
#define HWIO_RPM_VMIDMT_SGFSYNDR1_MSDINDEX_SHFT                        0x18
#define HWIO_RPM_VMIDMT_SGFSYNDR1_SSDINDEX_BMSK                     0x10000
#define HWIO_RPM_VMIDMT_SGFSYNDR1_SSDINDEX_SHFT                        0x10
#define HWIO_RPM_VMIDMT_SGFSYNDR1_STREAMINDEX_BMSK                      0x1
#define HWIO_RPM_VMIDMT_SGFSYNDR1_STREAMINDEX_SHFT                      0x0

#define HWIO_RPM_VMIDMT_SGFSYNDR2_ADDR                           (RPM_VMIDMT_REG_BASE      + 0x00000058)
#define HWIO_RPM_VMIDMT_SGFSYNDR2_RMSK                           0x3f1fffff
#define HWIO_RPM_VMIDMT_SGFSYNDR2_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_SGFSYNDR2_ADDR, HWIO_RPM_VMIDMT_SGFSYNDR2_RMSK)
#define HWIO_RPM_VMIDMT_SGFSYNDR2_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_SGFSYNDR2_ADDR, m)
#define HWIO_RPM_VMIDMT_SGFSYNDR2_ATID_BMSK                      0x3f000000
#define HWIO_RPM_VMIDMT_SGFSYNDR2_ATID_SHFT                            0x18
#define HWIO_RPM_VMIDMT_SGFSYNDR2_AVMID_BMSK                       0x1f0000
#define HWIO_RPM_VMIDMT_SGFSYNDR2_AVMID_SHFT                           0x10
#define HWIO_RPM_VMIDMT_SGFSYNDR2_ABID_BMSK                          0xe000
#define HWIO_RPM_VMIDMT_SGFSYNDR2_ABID_SHFT                             0xd
#define HWIO_RPM_VMIDMT_SGFSYNDR2_APID_BMSK                          0x1f00
#define HWIO_RPM_VMIDMT_SGFSYNDR2_APID_SHFT                             0x8
#define HWIO_RPM_VMIDMT_SGFSYNDR2_AMID_BMSK                            0xff
#define HWIO_RPM_VMIDMT_SGFSYNDR2_AMID_SHFT                             0x0

#define HWIO_RPM_VMIDMT_VMIDMTSCR0_ADDR                          (RPM_VMIDMT_REG_BASE      + 0x00000090)
#define HWIO_RPM_VMIDMT_VMIDMTSCR0_RMSK                                 0x1
#define HWIO_RPM_VMIDMT_VMIDMTSCR0_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_VMIDMTSCR0_ADDR, HWIO_RPM_VMIDMT_VMIDMTSCR0_RMSK)
#define HWIO_RPM_VMIDMT_VMIDMTSCR0_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_VMIDMTSCR0_ADDR, m)
#define HWIO_RPM_VMIDMT_VMIDMTSCR0_OUT(v)      \
        out_dword(HWIO_RPM_VMIDMT_VMIDMTSCR0_ADDR,v)
#define HWIO_RPM_VMIDMT_VMIDMTSCR0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_VMIDMT_VMIDMTSCR0_ADDR,m,v,HWIO_RPM_VMIDMT_VMIDMTSCR0_IN)
#define HWIO_RPM_VMIDMT_VMIDMTSCR0_CLKONOFFE_BMSK                       0x1
#define HWIO_RPM_VMIDMT_VMIDMTSCR0_CLKONOFFE_SHFT                       0x0

#define HWIO_RPM_VMIDMT_CR0_ADDR                                 (RPM_VMIDMT_REG_BASE      + 0x00000000)
#define HWIO_RPM_VMIDMT_CR0_RMSK                                  0xfd70ff5
#define HWIO_RPM_VMIDMT_CR0_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_CR0_ADDR, HWIO_RPM_VMIDMT_CR0_RMSK)
#define HWIO_RPM_VMIDMT_CR0_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_CR0_ADDR, m)
#define HWIO_RPM_VMIDMT_CR0_OUT(v)      \
        out_dword(HWIO_RPM_VMIDMT_CR0_ADDR,v)
#define HWIO_RPM_VMIDMT_CR0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_VMIDMT_CR0_ADDR,m,v,HWIO_RPM_VMIDMT_CR0_IN)
#define HWIO_RPM_VMIDMT_CR0_WACFG_BMSK                            0xc000000
#define HWIO_RPM_VMIDMT_CR0_WACFG_SHFT                                 0x1a
#define HWIO_RPM_VMIDMT_CR0_RACFG_BMSK                            0x3000000
#define HWIO_RPM_VMIDMT_CR0_RACFG_SHFT                                 0x18
#define HWIO_RPM_VMIDMT_CR0_SHCFG_BMSK                             0xc00000
#define HWIO_RPM_VMIDMT_CR0_SHCFG_SHFT                                 0x16
#define HWIO_RPM_VMIDMT_CR0_MTCFG_BMSK                             0x100000
#define HWIO_RPM_VMIDMT_CR0_MTCFG_SHFT                                 0x14
#define HWIO_RPM_VMIDMT_CR0_MEMATTR_BMSK                            0x70000
#define HWIO_RPM_VMIDMT_CR0_MEMATTR_SHFT                               0x10
#define HWIO_RPM_VMIDMT_CR0_VMIDPNE_BMSK                              0x800
#define HWIO_RPM_VMIDMT_CR0_VMIDPNE_SHFT                                0xb
#define HWIO_RPM_VMIDMT_CR0_USFCFG_BMSK                               0x400
#define HWIO_RPM_VMIDMT_CR0_USFCFG_SHFT                                 0xa
#define HWIO_RPM_VMIDMT_CR0_GSE_BMSK                                  0x200
#define HWIO_RPM_VMIDMT_CR0_GSE_SHFT                                    0x9
#define HWIO_RPM_VMIDMT_CR0_STALLD_BMSK                               0x100
#define HWIO_RPM_VMIDMT_CR0_STALLD_SHFT                                 0x8
#define HWIO_RPM_VMIDMT_CR0_TRANSIENTCFG_BMSK                          0xc0
#define HWIO_RPM_VMIDMT_CR0_TRANSIENTCFG_SHFT                           0x6
#define HWIO_RPM_VMIDMT_CR0_GCFGFIE_BMSK                               0x20
#define HWIO_RPM_VMIDMT_CR0_GCFGFIE_SHFT                                0x5
#define HWIO_RPM_VMIDMT_CR0_GCFGERE_BMSK                               0x10
#define HWIO_RPM_VMIDMT_CR0_GCFGERE_SHFT                                0x4
#define HWIO_RPM_VMIDMT_CR0_GFIE_BMSK                                   0x4
#define HWIO_RPM_VMIDMT_CR0_GFIE_SHFT                                   0x2
#define HWIO_RPM_VMIDMT_CR0_CLIENTPD_BMSK                               0x1
#define HWIO_RPM_VMIDMT_CR0_CLIENTPD_SHFT                               0x0

#define HWIO_RPM_VMIDMT_CR2_ADDR                                 (RPM_VMIDMT_REG_BASE      + 0x00000008)
#define HWIO_RPM_VMIDMT_CR2_RMSK                                       0x1f
#define HWIO_RPM_VMIDMT_CR2_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_CR2_ADDR, HWIO_RPM_VMIDMT_CR2_RMSK)
#define HWIO_RPM_VMIDMT_CR2_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_CR2_ADDR, m)
#define HWIO_RPM_VMIDMT_CR2_OUT(v)      \
        out_dword(HWIO_RPM_VMIDMT_CR2_ADDR,v)
#define HWIO_RPM_VMIDMT_CR2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_VMIDMT_CR2_ADDR,m,v,HWIO_RPM_VMIDMT_CR2_IN)
#define HWIO_RPM_VMIDMT_CR2_BPVMID_BMSK                                0x1f
#define HWIO_RPM_VMIDMT_CR2_BPVMID_SHFT                                 0x0

#define HWIO_RPM_VMIDMT_ACR_ADDR                                 (RPM_VMIDMT_REG_BASE      + 0x00000010)
#define HWIO_RPM_VMIDMT_ACR_RMSK                                 0x70000013
#define HWIO_RPM_VMIDMT_ACR_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_ACR_ADDR, HWIO_RPM_VMIDMT_ACR_RMSK)
#define HWIO_RPM_VMIDMT_ACR_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_ACR_ADDR, m)
#define HWIO_RPM_VMIDMT_ACR_OUT(v)      \
        out_dword(HWIO_RPM_VMIDMT_ACR_ADDR,v)
#define HWIO_RPM_VMIDMT_ACR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_VMIDMT_ACR_ADDR,m,v,HWIO_RPM_VMIDMT_ACR_IN)
#define HWIO_RPM_VMIDMT_ACR_BPRCNSH_BMSK                         0x40000000
#define HWIO_RPM_VMIDMT_ACR_BPRCNSH_SHFT                               0x1e
#define HWIO_RPM_VMIDMT_ACR_BPRCISH_BMSK                         0x20000000
#define HWIO_RPM_VMIDMT_ACR_BPRCISH_SHFT                               0x1d
#define HWIO_RPM_VMIDMT_ACR_BPRCOSH_BMSK                         0x10000000
#define HWIO_RPM_VMIDMT_ACR_BPRCOSH_SHFT                               0x1c
#define HWIO_RPM_VMIDMT_ACR_BPREQPRIORITYCFG_BMSK                      0x10
#define HWIO_RPM_VMIDMT_ACR_BPREQPRIORITYCFG_SHFT                       0x4
#define HWIO_RPM_VMIDMT_ACR_BPREQPRIORITY_BMSK                          0x3
#define HWIO_RPM_VMIDMT_ACR_BPREQPRIORITY_SHFT                          0x0

#define HWIO_RPM_VMIDMT_IDR0_ADDR                                (RPM_VMIDMT_REG_BASE      + 0x00000020)
#define HWIO_RPM_VMIDMT_IDR0_RMSK                                 0x8001eff
#define HWIO_RPM_VMIDMT_IDR0_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_IDR0_ADDR, HWIO_RPM_VMIDMT_IDR0_RMSK)
#define HWIO_RPM_VMIDMT_IDR0_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_IDR0_ADDR, m)
#define HWIO_RPM_VMIDMT_IDR0_SMS_BMSK                             0x8000000
#define HWIO_RPM_VMIDMT_IDR0_SMS_SHFT                                  0x1b
#define HWIO_RPM_VMIDMT_IDR0_NUMSIDB_BMSK                            0x1e00
#define HWIO_RPM_VMIDMT_IDR0_NUMSIDB_SHFT                               0x9
#define HWIO_RPM_VMIDMT_IDR0_NUMSMRG_BMSK                              0xff
#define HWIO_RPM_VMIDMT_IDR0_NUMSMRG_SHFT                               0x0

#define HWIO_RPM_VMIDMT_IDR1_ADDR                                (RPM_VMIDMT_REG_BASE      + 0x00000024)
#define HWIO_RPM_VMIDMT_IDR1_RMSK                                    0x9f00
#define HWIO_RPM_VMIDMT_IDR1_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_IDR1_ADDR, HWIO_RPM_VMIDMT_IDR1_RMSK)
#define HWIO_RPM_VMIDMT_IDR1_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_IDR1_ADDR, m)
#define HWIO_RPM_VMIDMT_IDR1_SMCD_BMSK                               0x8000
#define HWIO_RPM_VMIDMT_IDR1_SMCD_SHFT                                  0xf
#define HWIO_RPM_VMIDMT_IDR1_SSDTP_BMSK                              0x1000
#define HWIO_RPM_VMIDMT_IDR1_SSDTP_SHFT                                 0xc
#define HWIO_RPM_VMIDMT_IDR1_NUMSSDNDX_BMSK                           0xf00
#define HWIO_RPM_VMIDMT_IDR1_NUMSSDNDX_SHFT                             0x8

#define HWIO_RPM_VMIDMT_IDR2_ADDR                                (RPM_VMIDMT_REG_BASE      + 0x00000028)
#define HWIO_RPM_VMIDMT_IDR2_RMSK                                      0xff
#define HWIO_RPM_VMIDMT_IDR2_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_IDR2_ADDR, HWIO_RPM_VMIDMT_IDR2_RMSK)
#define HWIO_RPM_VMIDMT_IDR2_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_IDR2_ADDR, m)
#define HWIO_RPM_VMIDMT_IDR2_OAS_BMSK                                  0xf0
#define HWIO_RPM_VMIDMT_IDR2_OAS_SHFT                                   0x4
#define HWIO_RPM_VMIDMT_IDR2_IAS_BMSK                                   0xf
#define HWIO_RPM_VMIDMT_IDR2_IAS_SHFT                                   0x0

#define HWIO_RPM_VMIDMT_IDR4_ADDR                                (RPM_VMIDMT_REG_BASE      + 0x00000030)
#define HWIO_RPM_VMIDMT_IDR4_RMSK                                0xffffffff
#define HWIO_RPM_VMIDMT_IDR4_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_IDR4_ADDR, HWIO_RPM_VMIDMT_IDR4_RMSK)
#define HWIO_RPM_VMIDMT_IDR4_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_IDR4_ADDR, m)
#define HWIO_RPM_VMIDMT_IDR4_MAJOR_BMSK                          0xf0000000
#define HWIO_RPM_VMIDMT_IDR4_MAJOR_SHFT                                0x1c
#define HWIO_RPM_VMIDMT_IDR4_MINOR_BMSK                           0xfff0000
#define HWIO_RPM_VMIDMT_IDR4_MINOR_SHFT                                0x10
#define HWIO_RPM_VMIDMT_IDR4_STEP_BMSK                               0xffff
#define HWIO_RPM_VMIDMT_IDR4_STEP_SHFT                                  0x0

#define HWIO_RPM_VMIDMT_IDR5_ADDR                                (RPM_VMIDMT_REG_BASE      + 0x00000034)
#define HWIO_RPM_VMIDMT_IDR5_RMSK                                0xffff03ff
#define HWIO_RPM_VMIDMT_IDR5_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_IDR5_ADDR, HWIO_RPM_VMIDMT_IDR5_RMSK)
#define HWIO_RPM_VMIDMT_IDR5_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_IDR5_ADDR, m)
#define HWIO_RPM_VMIDMT_IDR5_NUMSPDRB_BMSK                       0xff000000
#define HWIO_RPM_VMIDMT_IDR5_NUMSPDRB_SHFT                             0x18
#define HWIO_RPM_VMIDMT_IDR5_NUMMSDRB_BMSK                         0xff0000
#define HWIO_RPM_VMIDMT_IDR5_NUMMSDRB_SHFT                             0x10
#define HWIO_RPM_VMIDMT_IDR5_MSAE_BMSK                                0x200
#define HWIO_RPM_VMIDMT_IDR5_MSAE_SHFT                                  0x9
#define HWIO_RPM_VMIDMT_IDR5_QRIBE_BMSK                               0x100
#define HWIO_RPM_VMIDMT_IDR5_QRIBE_SHFT                                 0x8
#define HWIO_RPM_VMIDMT_IDR5_NVMID_BMSK                                0xff
#define HWIO_RPM_VMIDMT_IDR5_NVMID_SHFT                                 0x0

#define HWIO_RPM_VMIDMT_IDR7_ADDR                                (RPM_VMIDMT_REG_BASE      + 0x0000003c)
#define HWIO_RPM_VMIDMT_IDR7_RMSK                                      0xff
#define HWIO_RPM_VMIDMT_IDR7_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_IDR7_ADDR, HWIO_RPM_VMIDMT_IDR7_RMSK)
#define HWIO_RPM_VMIDMT_IDR7_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_IDR7_ADDR, m)
#define HWIO_RPM_VMIDMT_IDR7_MAJOR_BMSK                                0xf0
#define HWIO_RPM_VMIDMT_IDR7_MAJOR_SHFT                                 0x4
#define HWIO_RPM_VMIDMT_IDR7_MINOR_BMSK                                 0xf
#define HWIO_RPM_VMIDMT_IDR7_MINOR_SHFT                                 0x0

#define HWIO_RPM_VMIDMT_GFAR0_ADDR                               (RPM_VMIDMT_REG_BASE      + 0x00000040)
#define HWIO_RPM_VMIDMT_GFAR0_RMSK                               0xffffffff
#define HWIO_RPM_VMIDMT_GFAR0_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_GFAR0_ADDR, HWIO_RPM_VMIDMT_GFAR0_RMSK)
#define HWIO_RPM_VMIDMT_GFAR0_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_GFAR0_ADDR, m)
#define HWIO_RPM_VMIDMT_GFAR0_GFEA0_BMSK                         0xffffffff
#define HWIO_RPM_VMIDMT_GFAR0_GFEA0_SHFT                                0x0

#define HWIO_RPM_VMIDMT_GFSR_ADDR                                (RPM_VMIDMT_REG_BASE      + 0x00000048)
#define HWIO_RPM_VMIDMT_GFSR_RMSK                                0xc00000a2
#define HWIO_RPM_VMIDMT_GFSR_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_GFSR_ADDR, HWIO_RPM_VMIDMT_GFSR_RMSK)
#define HWIO_RPM_VMIDMT_GFSR_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_GFSR_ADDR, m)
#define HWIO_RPM_VMIDMT_GFSR_OUT(v)      \
        out_dword(HWIO_RPM_VMIDMT_GFSR_ADDR,v)
#define HWIO_RPM_VMIDMT_GFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_VMIDMT_GFSR_ADDR,m,v,HWIO_RPM_VMIDMT_GFSR_IN)
#define HWIO_RPM_VMIDMT_GFSR_MULTI_CLIENT_BMSK                   0x80000000
#define HWIO_RPM_VMIDMT_GFSR_MULTI_CLIENT_SHFT                         0x1f
#define HWIO_RPM_VMIDMT_GFSR_MULTI_CFG_BMSK                      0x40000000
#define HWIO_RPM_VMIDMT_GFSR_MULTI_CFG_SHFT                            0x1e
#define HWIO_RPM_VMIDMT_GFSR_PF_BMSK                                   0x80
#define HWIO_RPM_VMIDMT_GFSR_PF_SHFT                                    0x7
#define HWIO_RPM_VMIDMT_GFSR_CAF_BMSK                                  0x20
#define HWIO_RPM_VMIDMT_GFSR_CAF_SHFT                                   0x5
#define HWIO_RPM_VMIDMT_GFSR_USF_BMSK                                   0x2
#define HWIO_RPM_VMIDMT_GFSR_USF_SHFT                                   0x1

#define HWIO_RPM_VMIDMT_GFSRRESTORE_ADDR                         (RPM_VMIDMT_REG_BASE      + 0x0000004c)
#define HWIO_RPM_VMIDMT_GFSRRESTORE_RMSK                         0xc00000a2
#define HWIO_RPM_VMIDMT_GFSRRESTORE_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_GFSRRESTORE_ADDR, HWIO_RPM_VMIDMT_GFSRRESTORE_RMSK)
#define HWIO_RPM_VMIDMT_GFSRRESTORE_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_GFSRRESTORE_ADDR, m)
#define HWIO_RPM_VMIDMT_GFSRRESTORE_OUT(v)      \
        out_dword(HWIO_RPM_VMIDMT_GFSRRESTORE_ADDR,v)
#define HWIO_RPM_VMIDMT_GFSRRESTORE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_VMIDMT_GFSRRESTORE_ADDR,m,v,HWIO_RPM_VMIDMT_GFSRRESTORE_IN)
#define HWIO_RPM_VMIDMT_GFSRRESTORE_MULTI_CLIENT_BMSK            0x80000000
#define HWIO_RPM_VMIDMT_GFSRRESTORE_MULTI_CLIENT_SHFT                  0x1f
#define HWIO_RPM_VMIDMT_GFSRRESTORE_MULTI_CFG_BMSK               0x40000000
#define HWIO_RPM_VMIDMT_GFSRRESTORE_MULTI_CFG_SHFT                     0x1e
#define HWIO_RPM_VMIDMT_GFSRRESTORE_PF_BMSK                            0x80
#define HWIO_RPM_VMIDMT_GFSRRESTORE_PF_SHFT                             0x7
#define HWIO_RPM_VMIDMT_GFSRRESTORE_CAF_BMSK                           0x20
#define HWIO_RPM_VMIDMT_GFSRRESTORE_CAF_SHFT                            0x5
#define HWIO_RPM_VMIDMT_GFSRRESTORE_USF_BMSK                            0x2
#define HWIO_RPM_VMIDMT_GFSRRESTORE_USF_SHFT                            0x1

#define HWIO_RPM_VMIDMT_GFSYNDR0_ADDR                            (RPM_VMIDMT_REG_BASE      + 0x00000050)
#define HWIO_RPM_VMIDMT_GFSYNDR0_RMSK                                 0x132
#define HWIO_RPM_VMIDMT_GFSYNDR0_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_GFSYNDR0_ADDR, HWIO_RPM_VMIDMT_GFSYNDR0_RMSK)
#define HWIO_RPM_VMIDMT_GFSYNDR0_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_GFSYNDR0_ADDR, m)
#define HWIO_RPM_VMIDMT_GFSYNDR0_MSSSELFAUTH_BMSK                     0x100
#define HWIO_RPM_VMIDMT_GFSYNDR0_MSSSELFAUTH_SHFT                       0x8
#define HWIO_RPM_VMIDMT_GFSYNDR0_NSATTR_BMSK                           0x20
#define HWIO_RPM_VMIDMT_GFSYNDR0_NSATTR_SHFT                            0x5
#define HWIO_RPM_VMIDMT_GFSYNDR0_NSSTATE_BMSK                          0x10
#define HWIO_RPM_VMIDMT_GFSYNDR0_NSSTATE_SHFT                           0x4
#define HWIO_RPM_VMIDMT_GFSYNDR0_WNR_BMSK                               0x2
#define HWIO_RPM_VMIDMT_GFSYNDR0_WNR_SHFT                               0x1

#define HWIO_RPM_VMIDMT_GFSYNDR1_ADDR                            (RPM_VMIDMT_REG_BASE      + 0x00000054)
#define HWIO_RPM_VMIDMT_GFSYNDR1_RMSK                             0x1010001
#define HWIO_RPM_VMIDMT_GFSYNDR1_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_GFSYNDR1_ADDR, HWIO_RPM_VMIDMT_GFSYNDR1_RMSK)
#define HWIO_RPM_VMIDMT_GFSYNDR1_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_GFSYNDR1_ADDR, m)
#define HWIO_RPM_VMIDMT_GFSYNDR1_MSDINDEX_BMSK                    0x1000000
#define HWIO_RPM_VMIDMT_GFSYNDR1_MSDINDEX_SHFT                         0x18
#define HWIO_RPM_VMIDMT_GFSYNDR1_SSDINDEX_BMSK                      0x10000
#define HWIO_RPM_VMIDMT_GFSYNDR1_SSDINDEX_SHFT                         0x10
#define HWIO_RPM_VMIDMT_GFSYNDR1_STREAMINDEX_BMSK                       0x1
#define HWIO_RPM_VMIDMT_GFSYNDR1_STREAMINDEX_SHFT                       0x0

#define HWIO_RPM_VMIDMT_GFSYNDR2_ADDR                            (RPM_VMIDMT_REG_BASE      + 0x00000058)
#define HWIO_RPM_VMIDMT_GFSYNDR2_RMSK                            0x3f1fffff
#define HWIO_RPM_VMIDMT_GFSYNDR2_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_GFSYNDR2_ADDR, HWIO_RPM_VMIDMT_GFSYNDR2_RMSK)
#define HWIO_RPM_VMIDMT_GFSYNDR2_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_GFSYNDR2_ADDR, m)
#define HWIO_RPM_VMIDMT_GFSYNDR2_ATID_BMSK                       0x3f000000
#define HWIO_RPM_VMIDMT_GFSYNDR2_ATID_SHFT                             0x18
#define HWIO_RPM_VMIDMT_GFSYNDR2_AVMID_BMSK                        0x1f0000
#define HWIO_RPM_VMIDMT_GFSYNDR2_AVMID_SHFT                            0x10
#define HWIO_RPM_VMIDMT_GFSYNDR2_ABID_BMSK                           0xe000
#define HWIO_RPM_VMIDMT_GFSYNDR2_ABID_SHFT                              0xd
#define HWIO_RPM_VMIDMT_GFSYNDR2_APID_BMSK                           0x1f00
#define HWIO_RPM_VMIDMT_GFSYNDR2_APID_SHFT                              0x8
#define HWIO_RPM_VMIDMT_GFSYNDR2_AMID_BMSK                             0xff
#define HWIO_RPM_VMIDMT_GFSYNDR2_AMID_SHFT                              0x0

#define HWIO_RPM_VMIDMT_VMIDMTCR0_ADDR                           (RPM_VMIDMT_REG_BASE      + 0x00000090)
#define HWIO_RPM_VMIDMT_VMIDMTCR0_RMSK                                  0x1
#define HWIO_RPM_VMIDMT_VMIDMTCR0_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_VMIDMTCR0_ADDR, HWIO_RPM_VMIDMT_VMIDMTCR0_RMSK)
#define HWIO_RPM_VMIDMT_VMIDMTCR0_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_VMIDMTCR0_ADDR, m)
#define HWIO_RPM_VMIDMT_VMIDMTCR0_OUT(v)      \
        out_dword(HWIO_RPM_VMIDMT_VMIDMTCR0_ADDR,v)
#define HWIO_RPM_VMIDMT_VMIDMTCR0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_VMIDMT_VMIDMTCR0_ADDR,m,v,HWIO_RPM_VMIDMT_VMIDMTCR0_IN)
#define HWIO_RPM_VMIDMT_VMIDMTCR0_CLKONOFFE_BMSK                        0x1
#define HWIO_RPM_VMIDMT_VMIDMTCR0_CLKONOFFE_SHFT                        0x0

#define HWIO_RPM_VMIDMT_VMIDMTACR_ADDR                           (RPM_VMIDMT_REG_BASE      + 0x0000009c)
#define HWIO_RPM_VMIDMT_VMIDMTACR_RMSK                           0xffffffff
#define HWIO_RPM_VMIDMT_VMIDMTACR_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_VMIDMTACR_ADDR, HWIO_RPM_VMIDMT_VMIDMTACR_RMSK)
#define HWIO_RPM_VMIDMT_VMIDMTACR_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_VMIDMTACR_ADDR, m)
#define HWIO_RPM_VMIDMT_VMIDMTACR_OUT(v)      \
        out_dword(HWIO_RPM_VMIDMT_VMIDMTACR_ADDR,v)
#define HWIO_RPM_VMIDMT_VMIDMTACR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_VMIDMT_VMIDMTACR_ADDR,m,v,HWIO_RPM_VMIDMT_VMIDMTACR_IN)
#define HWIO_RPM_VMIDMT_VMIDMTACR_RWE_BMSK                       0xffffffff
#define HWIO_RPM_VMIDMT_VMIDMTACR_RWE_SHFT                              0x0

#define HWIO_RPM_VMIDMT_NSCR0_ADDR                               (RPM_VMIDMT_REG_BASE      + 0x00000400)
#define HWIO_RPM_VMIDMT_NSCR0_RMSK                                0xfd70ff5
#define HWIO_RPM_VMIDMT_NSCR0_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_NSCR0_ADDR, HWIO_RPM_VMIDMT_NSCR0_RMSK)
#define HWIO_RPM_VMIDMT_NSCR0_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_NSCR0_ADDR, m)
#define HWIO_RPM_VMIDMT_NSCR0_OUT(v)      \
        out_dword(HWIO_RPM_VMIDMT_NSCR0_ADDR,v)
#define HWIO_RPM_VMIDMT_NSCR0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_VMIDMT_NSCR0_ADDR,m,v,HWIO_RPM_VMIDMT_NSCR0_IN)
#define HWIO_RPM_VMIDMT_NSCR0_WACFG_BMSK                          0xc000000
#define HWIO_RPM_VMIDMT_NSCR0_WACFG_SHFT                               0x1a
#define HWIO_RPM_VMIDMT_NSCR0_RACFG_BMSK                          0x3000000
#define HWIO_RPM_VMIDMT_NSCR0_RACFG_SHFT                               0x18
#define HWIO_RPM_VMIDMT_NSCR0_SHCFG_BMSK                           0xc00000
#define HWIO_RPM_VMIDMT_NSCR0_SHCFG_SHFT                               0x16
#define HWIO_RPM_VMIDMT_NSCR0_MTCFG_BMSK                           0x100000
#define HWIO_RPM_VMIDMT_NSCR0_MTCFG_SHFT                               0x14
#define HWIO_RPM_VMIDMT_NSCR0_MEMATTR_BMSK                          0x70000
#define HWIO_RPM_VMIDMT_NSCR0_MEMATTR_SHFT                             0x10
#define HWIO_RPM_VMIDMT_NSCR0_VMIDPNE_BMSK                            0x800
#define HWIO_RPM_VMIDMT_NSCR0_VMIDPNE_SHFT                              0xb
#define HWIO_RPM_VMIDMT_NSCR0_USFCFG_BMSK                             0x400
#define HWIO_RPM_VMIDMT_NSCR0_USFCFG_SHFT                               0xa
#define HWIO_RPM_VMIDMT_NSCR0_GSE_BMSK                                0x200
#define HWIO_RPM_VMIDMT_NSCR0_GSE_SHFT                                  0x9
#define HWIO_RPM_VMIDMT_NSCR0_STALLD_BMSK                             0x100
#define HWIO_RPM_VMIDMT_NSCR0_STALLD_SHFT                               0x8
#define HWIO_RPM_VMIDMT_NSCR0_TRANSIENTCFG_BMSK                        0xc0
#define HWIO_RPM_VMIDMT_NSCR0_TRANSIENTCFG_SHFT                         0x6
#define HWIO_RPM_VMIDMT_NSCR0_GCFGFIE_BMSK                             0x20
#define HWIO_RPM_VMIDMT_NSCR0_GCFGFIE_SHFT                              0x5
#define HWIO_RPM_VMIDMT_NSCR0_GCFGERE_BMSK                             0x10
#define HWIO_RPM_VMIDMT_NSCR0_GCFGERE_SHFT                              0x4
#define HWIO_RPM_VMIDMT_NSCR0_GFIE_BMSK                                 0x4
#define HWIO_RPM_VMIDMT_NSCR0_GFIE_SHFT                                 0x2
#define HWIO_RPM_VMIDMT_NSCR0_CLIENTPD_BMSK                             0x1
#define HWIO_RPM_VMIDMT_NSCR0_CLIENTPD_SHFT                             0x0

#define HWIO_RPM_VMIDMT_NSCR2_ADDR                               (RPM_VMIDMT_REG_BASE      + 0x00000408)
#define HWIO_RPM_VMIDMT_NSCR2_RMSK                                     0x1f
#define HWIO_RPM_VMIDMT_NSCR2_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_NSCR2_ADDR, HWIO_RPM_VMIDMT_NSCR2_RMSK)
#define HWIO_RPM_VMIDMT_NSCR2_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_NSCR2_ADDR, m)
#define HWIO_RPM_VMIDMT_NSCR2_OUT(v)      \
        out_dword(HWIO_RPM_VMIDMT_NSCR2_ADDR,v)
#define HWIO_RPM_VMIDMT_NSCR2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_VMIDMT_NSCR2_ADDR,m,v,HWIO_RPM_VMIDMT_NSCR2_IN)
#define HWIO_RPM_VMIDMT_NSCR2_BPVMID_BMSK                              0x1f
#define HWIO_RPM_VMIDMT_NSCR2_BPVMID_SHFT                               0x0

#define HWIO_RPM_VMIDMT_NSACR_ADDR                               (RPM_VMIDMT_REG_BASE      + 0x00000410)
#define HWIO_RPM_VMIDMT_NSACR_RMSK                               0x70000013
#define HWIO_RPM_VMIDMT_NSACR_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_NSACR_ADDR, HWIO_RPM_VMIDMT_NSACR_RMSK)
#define HWIO_RPM_VMIDMT_NSACR_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_NSACR_ADDR, m)
#define HWIO_RPM_VMIDMT_NSACR_OUT(v)      \
        out_dword(HWIO_RPM_VMIDMT_NSACR_ADDR,v)
#define HWIO_RPM_VMIDMT_NSACR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_VMIDMT_NSACR_ADDR,m,v,HWIO_RPM_VMIDMT_NSACR_IN)
#define HWIO_RPM_VMIDMT_NSACR_BPRCNSH_BMSK                       0x40000000
#define HWIO_RPM_VMIDMT_NSACR_BPRCNSH_SHFT                             0x1e
#define HWIO_RPM_VMIDMT_NSACR_BPRCISH_BMSK                       0x20000000
#define HWIO_RPM_VMIDMT_NSACR_BPRCISH_SHFT                             0x1d
#define HWIO_RPM_VMIDMT_NSACR_BPRCOSH_BMSK                       0x10000000
#define HWIO_RPM_VMIDMT_NSACR_BPRCOSH_SHFT                             0x1c
#define HWIO_RPM_VMIDMT_NSACR_BPREQPRIORITYCFG_BMSK                    0x10
#define HWIO_RPM_VMIDMT_NSACR_BPREQPRIORITYCFG_SHFT                     0x4
#define HWIO_RPM_VMIDMT_NSACR_BPREQPRIORITY_BMSK                        0x3
#define HWIO_RPM_VMIDMT_NSACR_BPREQPRIORITY_SHFT                        0x0

#define HWIO_RPM_VMIDMT_NSGFAR0_ADDR                             (RPM_VMIDMT_REG_BASE      + 0x00000440)
#define HWIO_RPM_VMIDMT_NSGFAR0_RMSK                             0xffffffff
#define HWIO_RPM_VMIDMT_NSGFAR0_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_NSGFAR0_ADDR, HWIO_RPM_VMIDMT_NSGFAR0_RMSK)
#define HWIO_RPM_VMIDMT_NSGFAR0_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_NSGFAR0_ADDR, m)
#define HWIO_RPM_VMIDMT_NSGFAR0_GFEA0_BMSK                       0xffffffff
#define HWIO_RPM_VMIDMT_NSGFAR0_GFEA0_SHFT                              0x0

#define HWIO_RPM_VMIDMT_NSGFSR_ADDR                              (RPM_VMIDMT_REG_BASE      + 0x00000448)
#define HWIO_RPM_VMIDMT_NSGFSR_RMSK                              0xc00000a2
#define HWIO_RPM_VMIDMT_NSGFSR_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_NSGFSR_ADDR, HWIO_RPM_VMIDMT_NSGFSR_RMSK)
#define HWIO_RPM_VMIDMT_NSGFSR_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_NSGFSR_ADDR, m)
#define HWIO_RPM_VMIDMT_NSGFSR_OUT(v)      \
        out_dword(HWIO_RPM_VMIDMT_NSGFSR_ADDR,v)
#define HWIO_RPM_VMIDMT_NSGFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_VMIDMT_NSGFSR_ADDR,m,v,HWIO_RPM_VMIDMT_NSGFSR_IN)
#define HWIO_RPM_VMIDMT_NSGFSR_MULTI_CLIENT_BMSK                 0x80000000
#define HWIO_RPM_VMIDMT_NSGFSR_MULTI_CLIENT_SHFT                       0x1f
#define HWIO_RPM_VMIDMT_NSGFSR_MULTI_CFG_BMSK                    0x40000000
#define HWIO_RPM_VMIDMT_NSGFSR_MULTI_CFG_SHFT                          0x1e
#define HWIO_RPM_VMIDMT_NSGFSR_PF_BMSK                                 0x80
#define HWIO_RPM_VMIDMT_NSGFSR_PF_SHFT                                  0x7
#define HWIO_RPM_VMIDMT_NSGFSR_CAF_BMSK                                0x20
#define HWIO_RPM_VMIDMT_NSGFSR_CAF_SHFT                                 0x5
#define HWIO_RPM_VMIDMT_NSGFSR_USF_BMSK                                 0x2
#define HWIO_RPM_VMIDMT_NSGFSR_USF_SHFT                                 0x1

#define HWIO_RPM_VMIDMT_NSGFSRRESTORE_ADDR                       (RPM_VMIDMT_REG_BASE      + 0x0000044c)
#define HWIO_RPM_VMIDMT_NSGFSRRESTORE_RMSK                       0xc00000a2
#define HWIO_RPM_VMIDMT_NSGFSRRESTORE_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_NSGFSRRESTORE_ADDR, HWIO_RPM_VMIDMT_NSGFSRRESTORE_RMSK)
#define HWIO_RPM_VMIDMT_NSGFSRRESTORE_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_NSGFSRRESTORE_ADDR, m)
#define HWIO_RPM_VMIDMT_NSGFSRRESTORE_OUT(v)      \
        out_dword(HWIO_RPM_VMIDMT_NSGFSRRESTORE_ADDR,v)
#define HWIO_RPM_VMIDMT_NSGFSRRESTORE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_VMIDMT_NSGFSRRESTORE_ADDR,m,v,HWIO_RPM_VMIDMT_NSGFSRRESTORE_IN)
#define HWIO_RPM_VMIDMT_NSGFSRRESTORE_MULTI_CLIENT_BMSK          0x80000000
#define HWIO_RPM_VMIDMT_NSGFSRRESTORE_MULTI_CLIENT_SHFT                0x1f
#define HWIO_RPM_VMIDMT_NSGFSRRESTORE_MULTI_CFG_BMSK             0x40000000
#define HWIO_RPM_VMIDMT_NSGFSRRESTORE_MULTI_CFG_SHFT                   0x1e
#define HWIO_RPM_VMIDMT_NSGFSRRESTORE_PF_BMSK                          0x80
#define HWIO_RPM_VMIDMT_NSGFSRRESTORE_PF_SHFT                           0x7
#define HWIO_RPM_VMIDMT_NSGFSRRESTORE_CAF_BMSK                         0x20
#define HWIO_RPM_VMIDMT_NSGFSRRESTORE_CAF_SHFT                          0x5
#define HWIO_RPM_VMIDMT_NSGFSRRESTORE_USF_BMSK                          0x2
#define HWIO_RPM_VMIDMT_NSGFSRRESTORE_USF_SHFT                          0x1

#define HWIO_RPM_VMIDMT_NSGFSYNDR0_ADDR                          (RPM_VMIDMT_REG_BASE      + 0x00000450)
#define HWIO_RPM_VMIDMT_NSGFSYNDR0_RMSK                               0x132
#define HWIO_RPM_VMIDMT_NSGFSYNDR0_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_NSGFSYNDR0_ADDR, HWIO_RPM_VMIDMT_NSGFSYNDR0_RMSK)
#define HWIO_RPM_VMIDMT_NSGFSYNDR0_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_NSGFSYNDR0_ADDR, m)
#define HWIO_RPM_VMIDMT_NSGFSYNDR0_MSSSELFAUTH_BMSK                   0x100
#define HWIO_RPM_VMIDMT_NSGFSYNDR0_MSSSELFAUTH_SHFT                     0x8
#define HWIO_RPM_VMIDMT_NSGFSYNDR0_NSATTR_BMSK                         0x20
#define HWIO_RPM_VMIDMT_NSGFSYNDR0_NSATTR_SHFT                          0x5
#define HWIO_RPM_VMIDMT_NSGFSYNDR0_NSSTATE_BMSK                        0x10
#define HWIO_RPM_VMIDMT_NSGFSYNDR0_NSSTATE_SHFT                         0x4
#define HWIO_RPM_VMIDMT_NSGFSYNDR0_WNR_BMSK                             0x2
#define HWIO_RPM_VMIDMT_NSGFSYNDR0_WNR_SHFT                             0x1

#define HWIO_RPM_VMIDMT_NSGFSYNDR1_ADDR                          (RPM_VMIDMT_REG_BASE      + 0x00000454)
#define HWIO_RPM_VMIDMT_NSGFSYNDR1_RMSK                           0x1010001
#define HWIO_RPM_VMIDMT_NSGFSYNDR1_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_NSGFSYNDR1_ADDR, HWIO_RPM_VMIDMT_NSGFSYNDR1_RMSK)
#define HWIO_RPM_VMIDMT_NSGFSYNDR1_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_NSGFSYNDR1_ADDR, m)
#define HWIO_RPM_VMIDMT_NSGFSYNDR1_MSDINDEX_BMSK                  0x1000000
#define HWIO_RPM_VMIDMT_NSGFSYNDR1_MSDINDEX_SHFT                       0x18
#define HWIO_RPM_VMIDMT_NSGFSYNDR1_SSDINDEX_BMSK                    0x10000
#define HWIO_RPM_VMIDMT_NSGFSYNDR1_SSDINDEX_SHFT                       0x10
#define HWIO_RPM_VMIDMT_NSGFSYNDR1_STREAMINDEX_BMSK                     0x1
#define HWIO_RPM_VMIDMT_NSGFSYNDR1_STREAMINDEX_SHFT                     0x0

#define HWIO_RPM_VMIDMT_NSGFSYNDR2_ADDR                          (RPM_VMIDMT_REG_BASE      + 0x00000458)
#define HWIO_RPM_VMIDMT_NSGFSYNDR2_RMSK                          0x3f1fffff
#define HWIO_RPM_VMIDMT_NSGFSYNDR2_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_NSGFSYNDR2_ADDR, HWIO_RPM_VMIDMT_NSGFSYNDR2_RMSK)
#define HWIO_RPM_VMIDMT_NSGFSYNDR2_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_NSGFSYNDR2_ADDR, m)
#define HWIO_RPM_VMIDMT_NSGFSYNDR2_ATID_BMSK                     0x3f000000
#define HWIO_RPM_VMIDMT_NSGFSYNDR2_ATID_SHFT                           0x18
#define HWIO_RPM_VMIDMT_NSGFSYNDR2_AVMID_BMSK                      0x1f0000
#define HWIO_RPM_VMIDMT_NSGFSYNDR2_AVMID_SHFT                          0x10
#define HWIO_RPM_VMIDMT_NSGFSYNDR2_ABID_BMSK                         0xe000
#define HWIO_RPM_VMIDMT_NSGFSYNDR2_ABID_SHFT                            0xd
#define HWIO_RPM_VMIDMT_NSGFSYNDR2_APID_BMSK                         0x1f00
#define HWIO_RPM_VMIDMT_NSGFSYNDR2_APID_SHFT                            0x8
#define HWIO_RPM_VMIDMT_NSGFSYNDR2_AMID_BMSK                           0xff
#define HWIO_RPM_VMIDMT_NSGFSYNDR2_AMID_SHFT                            0x0

#define HWIO_RPM_VMIDMT_NSVMIDMTCR0_ADDR                         (RPM_VMIDMT_REG_BASE      + 0x00000490)
#define HWIO_RPM_VMIDMT_NSVMIDMTCR0_RMSK                                0x1
#define HWIO_RPM_VMIDMT_NSVMIDMTCR0_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_NSVMIDMTCR0_ADDR, HWIO_RPM_VMIDMT_NSVMIDMTCR0_RMSK)
#define HWIO_RPM_VMIDMT_NSVMIDMTCR0_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_NSVMIDMTCR0_ADDR, m)
#define HWIO_RPM_VMIDMT_NSVMIDMTCR0_OUT(v)      \
        out_dword(HWIO_RPM_VMIDMT_NSVMIDMTCR0_ADDR,v)
#define HWIO_RPM_VMIDMT_NSVMIDMTCR0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_VMIDMT_NSVMIDMTCR0_ADDR,m,v,HWIO_RPM_VMIDMT_NSVMIDMTCR0_IN)
#define HWIO_RPM_VMIDMT_NSVMIDMTCR0_CLKONOFFE_BMSK                      0x1
#define HWIO_RPM_VMIDMT_NSVMIDMTCR0_CLKONOFFE_SHFT                      0x0

#define HWIO_RPM_VMIDMT_SSDR0_ADDR                               (RPM_VMIDMT_REG_BASE      + 0x00000080)
#define HWIO_RPM_VMIDMT_SSDR0_RMSK                                      0x1
#define HWIO_RPM_VMIDMT_SSDR0_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_SSDR0_ADDR, HWIO_RPM_VMIDMT_SSDR0_RMSK)
#define HWIO_RPM_VMIDMT_SSDR0_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_SSDR0_ADDR, m)
#define HWIO_RPM_VMIDMT_SSDR0_OUT(v)      \
        out_dword(HWIO_RPM_VMIDMT_SSDR0_ADDR,v)
#define HWIO_RPM_VMIDMT_SSDR0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_VMIDMT_SSDR0_ADDR,m,v,HWIO_RPM_VMIDMT_SSDR0_IN)
#define HWIO_RPM_VMIDMT_SSDR0_RWE_BMSK                                  0x1
#define HWIO_RPM_VMIDMT_SSDR0_RWE_SHFT                                  0x0

#define HWIO_RPM_VMIDMT_MSDR0_ADDR                               (RPM_VMIDMT_REG_BASE      + 0x00000480)
#define HWIO_RPM_VMIDMT_MSDR0_RMSK                                      0x1
#define HWIO_RPM_VMIDMT_MSDR0_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_MSDR0_ADDR, HWIO_RPM_VMIDMT_MSDR0_RMSK)
#define HWIO_RPM_VMIDMT_MSDR0_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_MSDR0_ADDR, m)
#define HWIO_RPM_VMIDMT_MSDR0_OUT(v)      \
        out_dword(HWIO_RPM_VMIDMT_MSDR0_ADDR,v)
#define HWIO_RPM_VMIDMT_MSDR0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_VMIDMT_MSDR0_ADDR,m,v,HWIO_RPM_VMIDMT_MSDR0_IN)
#define HWIO_RPM_VMIDMT_MSDR0_RWE_BMSK                                  0x1
#define HWIO_RPM_VMIDMT_MSDR0_RWE_SHFT                                  0x0

#define HWIO_RPM_VMIDMT_MCR_ADDR                                 (RPM_VMIDMT_REG_BASE      + 0x00000494)
#define HWIO_RPM_VMIDMT_MCR_RMSK                                        0x7
#define HWIO_RPM_VMIDMT_MCR_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_MCR_ADDR, HWIO_RPM_VMIDMT_MCR_RMSK)
#define HWIO_RPM_VMIDMT_MCR_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_MCR_ADDR, m)
#define HWIO_RPM_VMIDMT_MCR_OUT(v)      \
        out_dword(HWIO_RPM_VMIDMT_MCR_ADDR,v)
#define HWIO_RPM_VMIDMT_MCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_VMIDMT_MCR_ADDR,m,v,HWIO_RPM_VMIDMT_MCR_IN)
#define HWIO_RPM_VMIDMT_MCR_CLKONOFFE_BMSK                              0x4
#define HWIO_RPM_VMIDMT_MCR_CLKONOFFE_SHFT                              0x2
#define HWIO_RPM_VMIDMT_MCR_BPMSACFG_BMSK                               0x2
#define HWIO_RPM_VMIDMT_MCR_BPMSACFG_SHFT                               0x1
#define HWIO_RPM_VMIDMT_MCR_BPSMSACFG_BMSK                              0x1
#define HWIO_RPM_VMIDMT_MCR_BPSMSACFG_SHFT                              0x0

#define HWIO_RPM_VMIDMT_SPDR0_ADDR                               (RPM_VMIDMT_REG_BASE      + 0x00000580)
#define HWIO_RPM_VMIDMT_SPDR0_RMSK                                      0x1
#define HWIO_RPM_VMIDMT_SPDR0_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_SPDR0_ADDR, HWIO_RPM_VMIDMT_SPDR0_RMSK)
#define HWIO_RPM_VMIDMT_SPDR0_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_SPDR0_ADDR, m)
#define HWIO_RPM_VMIDMT_SPDR0_OUT(v)      \
        out_dword(HWIO_RPM_VMIDMT_SPDR0_ADDR,v)
#define HWIO_RPM_VMIDMT_SPDR0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_VMIDMT_SPDR0_ADDR,m,v,HWIO_RPM_VMIDMT_SPDR0_IN)
#define HWIO_RPM_VMIDMT_SPDR0_RWE_BMSK                                  0x1
#define HWIO_RPM_VMIDMT_SPDR0_RWE_SHFT                                  0x0

#define HWIO_RPM_VMIDMT_SPCR_ADDR                                (RPM_VMIDMT_REG_BASE      + 0x00000594)
#define HWIO_RPM_VMIDMT_SPCR_RMSK                                       0x7
#define HWIO_RPM_VMIDMT_SPCR_IN          \
        in_dword_masked(HWIO_RPM_VMIDMT_SPCR_ADDR, HWIO_RPM_VMIDMT_SPCR_RMSK)
#define HWIO_RPM_VMIDMT_SPCR_INM(m)      \
        in_dword_masked(HWIO_RPM_VMIDMT_SPCR_ADDR, m)
#define HWIO_RPM_VMIDMT_SPCR_OUT(v)      \
        out_dword(HWIO_RPM_VMIDMT_SPCR_ADDR,v)
#define HWIO_RPM_VMIDMT_SPCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_VMIDMT_SPCR_ADDR,m,v,HWIO_RPM_VMIDMT_SPCR_IN)
#define HWIO_RPM_VMIDMT_SPCR_CLKONOFFE_BMSK                             0x4
#define HWIO_RPM_VMIDMT_SPCR_CLKONOFFE_SHFT                             0x2
#define HWIO_RPM_VMIDMT_SPCR_BPSPDCFG_BMSK                              0x2
#define HWIO_RPM_VMIDMT_SPCR_BPSPDCFG_SHFT                              0x1
#define HWIO_RPM_VMIDMT_SPCR_BPSSPDCFG_BMSK                             0x1
#define HWIO_RPM_VMIDMT_SPCR_BPSSPDCFG_SHFT                             0x0

#define HWIO_RPM_VMIDMT_S2VRn_ADDR(n)                            (RPM_VMIDMT_REG_BASE      + 0x00000c00 + 0x4 * (n))
#define HWIO_RPM_VMIDMT_S2VRn_RMSK                               0x30ff7b1f
#define HWIO_RPM_VMIDMT_S2VRn_MAXn                                        0
#define HWIO_RPM_VMIDMT_S2VRn_INI(n)        \
        in_dword_masked(HWIO_RPM_VMIDMT_S2VRn_ADDR(n), HWIO_RPM_VMIDMT_S2VRn_RMSK)
#define HWIO_RPM_VMIDMT_S2VRn_INMI(n,mask)    \
        in_dword_masked(HWIO_RPM_VMIDMT_S2VRn_ADDR(n), mask)
#define HWIO_RPM_VMIDMT_S2VRn_OUTI(n,val)    \
        out_dword(HWIO_RPM_VMIDMT_S2VRn_ADDR(n),val)
#define HWIO_RPM_VMIDMT_S2VRn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_RPM_VMIDMT_S2VRn_ADDR(n),mask,val,HWIO_RPM_VMIDMT_S2VRn_INI(n))
#define HWIO_RPM_VMIDMT_S2VRn_TRANSIENTCFG_BMSK                  0x30000000
#define HWIO_RPM_VMIDMT_S2VRn_TRANSIENTCFG_SHFT                        0x1c
#define HWIO_RPM_VMIDMT_S2VRn_WACFG_BMSK                           0xc00000
#define HWIO_RPM_VMIDMT_S2VRn_WACFG_SHFT                               0x16
#define HWIO_RPM_VMIDMT_S2VRn_RACFG_BMSK                           0x300000
#define HWIO_RPM_VMIDMT_S2VRn_RACFG_SHFT                               0x14
#define HWIO_RPM_VMIDMT_S2VRn_NSCFG_BMSK                            0xc0000
#define HWIO_RPM_VMIDMT_S2VRn_NSCFG_SHFT                               0x12
#define HWIO_RPM_VMIDMT_S2VRn_TYPE_BMSK                             0x30000
#define HWIO_RPM_VMIDMT_S2VRn_TYPE_SHFT                                0x10
#define HWIO_RPM_VMIDMT_S2VRn_MEMATTR_BMSK                           0x7000
#define HWIO_RPM_VMIDMT_S2VRn_MEMATTR_SHFT                              0xc
#define HWIO_RPM_VMIDMT_S2VRn_MTCFG_BMSK                              0x800
#define HWIO_RPM_VMIDMT_S2VRn_MTCFG_SHFT                                0xb
#define HWIO_RPM_VMIDMT_S2VRn_SHCFG_BMSK                              0x300
#define HWIO_RPM_VMIDMT_S2VRn_SHCFG_SHFT                                0x8
#define HWIO_RPM_VMIDMT_S2VRn_VMID_BMSK                                0x1f
#define HWIO_RPM_VMIDMT_S2VRn_VMID_SHFT                                 0x0

#define HWIO_RPM_VMIDMT_AS2VRn_ADDR(n)                           (RPM_VMIDMT_REG_BASE      + 0x00000e00 + 0x4 * (n))
#define HWIO_RPM_VMIDMT_AS2VRn_RMSK                              0x70000013
#define HWIO_RPM_VMIDMT_AS2VRn_MAXn                                       0
#define HWIO_RPM_VMIDMT_AS2VRn_INI(n)        \
        in_dword_masked(HWIO_RPM_VMIDMT_AS2VRn_ADDR(n), HWIO_RPM_VMIDMT_AS2VRn_RMSK)
#define HWIO_RPM_VMIDMT_AS2VRn_INMI(n,mask)    \
        in_dword_masked(HWIO_RPM_VMIDMT_AS2VRn_ADDR(n), mask)
#define HWIO_RPM_VMIDMT_AS2VRn_OUTI(n,val)    \
        out_dword(HWIO_RPM_VMIDMT_AS2VRn_ADDR(n),val)
#define HWIO_RPM_VMIDMT_AS2VRn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_RPM_VMIDMT_AS2VRn_ADDR(n),mask,val,HWIO_RPM_VMIDMT_AS2VRn_INI(n))
#define HWIO_RPM_VMIDMT_AS2VRn_RCNSH_BMSK                        0x40000000
#define HWIO_RPM_VMIDMT_AS2VRn_RCNSH_SHFT                              0x1e
#define HWIO_RPM_VMIDMT_AS2VRn_RCISH_BMSK                        0x20000000
#define HWIO_RPM_VMIDMT_AS2VRn_RCISH_SHFT                              0x1d
#define HWIO_RPM_VMIDMT_AS2VRn_RCOSH_BMSK                        0x10000000
#define HWIO_RPM_VMIDMT_AS2VRn_RCOSH_SHFT                              0x1c
#define HWIO_RPM_VMIDMT_AS2VRn_REQPRIORITYCFG_BMSK                     0x10
#define HWIO_RPM_VMIDMT_AS2VRn_REQPRIORITYCFG_SHFT                      0x4
#define HWIO_RPM_VMIDMT_AS2VRn_REQPRIORITY_BMSK                         0x3
#define HWIO_RPM_VMIDMT_AS2VRn_REQPRIORITY_SHFT                         0x0

/*----------------------------------------------------------------------------
 * MODULE: RPM_M3_PPB_INT
 *--------------------------------------------------------------------------*/

#define RPM_M3_PPB_INT_REG_BASE                                                 (RPM_M3_CORTEXM3_T_BASE      + 0x00000000)

#define HWIO_RPM_M3_ITM_ITM_STIM0_ADDR                                          (RPM_M3_PPB_INT_REG_BASE      + 0x00000000)
#define HWIO_RPM_M3_ITM_ITM_STIM0_RMSK                                          0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM0_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM0_ADDR, HWIO_RPM_M3_ITM_ITM_STIM0_RMSK)
#define HWIO_RPM_M3_ITM_ITM_STIM0_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM0_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_STIM0_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_STIM0_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_STIM0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ITM_ITM_STIM0_ADDR,m,v,HWIO_RPM_M3_ITM_ITM_STIM0_IN)
#define HWIO_RPM_M3_ITM_ITM_STIM0_ITM_ITM_STIM0_BMSK                            0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM0_ITM_ITM_STIM0_SHFT                                   0x0

#define HWIO_RPM_M3_ITM_ITM_STIM1_ADDR                                          (RPM_M3_PPB_INT_REG_BASE      + 0x00000004)
#define HWIO_RPM_M3_ITM_ITM_STIM1_RMSK                                          0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM1_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM1_ADDR, HWIO_RPM_M3_ITM_ITM_STIM1_RMSK)
#define HWIO_RPM_M3_ITM_ITM_STIM1_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM1_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_STIM1_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_STIM1_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_STIM1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ITM_ITM_STIM1_ADDR,m,v,HWIO_RPM_M3_ITM_ITM_STIM1_IN)
#define HWIO_RPM_M3_ITM_ITM_STIM1_ITM_ITM_STIM1_BMSK                            0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM1_ITM_ITM_STIM1_SHFT                                   0x0

#define HWIO_RPM_M3_ITM_ITM_STIM2_ADDR                                          (RPM_M3_PPB_INT_REG_BASE      + 0x00000008)
#define HWIO_RPM_M3_ITM_ITM_STIM2_RMSK                                          0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM2_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM2_ADDR, HWIO_RPM_M3_ITM_ITM_STIM2_RMSK)
#define HWIO_RPM_M3_ITM_ITM_STIM2_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM2_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_STIM2_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_STIM2_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_STIM2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ITM_ITM_STIM2_ADDR,m,v,HWIO_RPM_M3_ITM_ITM_STIM2_IN)
#define HWIO_RPM_M3_ITM_ITM_STIM2_ITM_ITM_STIM2_BMSK                            0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM2_ITM_ITM_STIM2_SHFT                                   0x0

#define HWIO_RPM_M3_ITM_ITM_STIM3_ADDR                                          (RPM_M3_PPB_INT_REG_BASE      + 0x0000000c)
#define HWIO_RPM_M3_ITM_ITM_STIM3_RMSK                                          0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM3_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM3_ADDR, HWIO_RPM_M3_ITM_ITM_STIM3_RMSK)
#define HWIO_RPM_M3_ITM_ITM_STIM3_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM3_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_STIM3_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_STIM3_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_STIM3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ITM_ITM_STIM3_ADDR,m,v,HWIO_RPM_M3_ITM_ITM_STIM3_IN)
#define HWIO_RPM_M3_ITM_ITM_STIM3_ITM_ITM_STIM3_BMSK                            0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM3_ITM_ITM_STIM3_SHFT                                   0x0

#define HWIO_RPM_M3_ITM_ITM_STIM4_ADDR                                          (RPM_M3_PPB_INT_REG_BASE      + 0x00000010)
#define HWIO_RPM_M3_ITM_ITM_STIM4_RMSK                                          0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM4_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM4_ADDR, HWIO_RPM_M3_ITM_ITM_STIM4_RMSK)
#define HWIO_RPM_M3_ITM_ITM_STIM4_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM4_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_STIM4_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_STIM4_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_STIM4_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ITM_ITM_STIM4_ADDR,m,v,HWIO_RPM_M3_ITM_ITM_STIM4_IN)
#define HWIO_RPM_M3_ITM_ITM_STIM4_ITM_ITM_STIM4_BMSK                            0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM4_ITM_ITM_STIM4_SHFT                                   0x0

#define HWIO_RPM_M3_ITM_ITM_STIM5_ADDR                                          (RPM_M3_PPB_INT_REG_BASE      + 0x00000014)
#define HWIO_RPM_M3_ITM_ITM_STIM5_RMSK                                          0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM5_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM5_ADDR, HWIO_RPM_M3_ITM_ITM_STIM5_RMSK)
#define HWIO_RPM_M3_ITM_ITM_STIM5_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM5_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_STIM5_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_STIM5_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_STIM5_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ITM_ITM_STIM5_ADDR,m,v,HWIO_RPM_M3_ITM_ITM_STIM5_IN)
#define HWIO_RPM_M3_ITM_ITM_STIM5_ITM_ITM_STIM5_BMSK                            0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM5_ITM_ITM_STIM5_SHFT                                   0x0

#define HWIO_RPM_M3_ITM_ITM_STIM6_ADDR                                          (RPM_M3_PPB_INT_REG_BASE      + 0x00000018)
#define HWIO_RPM_M3_ITM_ITM_STIM6_RMSK                                          0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM6_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM6_ADDR, HWIO_RPM_M3_ITM_ITM_STIM6_RMSK)
#define HWIO_RPM_M3_ITM_ITM_STIM6_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM6_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_STIM6_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_STIM6_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_STIM6_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ITM_ITM_STIM6_ADDR,m,v,HWIO_RPM_M3_ITM_ITM_STIM6_IN)
#define HWIO_RPM_M3_ITM_ITM_STIM6_ITM_ITM_STIM6_BMSK                            0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM6_ITM_ITM_STIM6_SHFT                                   0x0

#define HWIO_RPM_M3_ITM_ITM_STIM7_ADDR                                          (RPM_M3_PPB_INT_REG_BASE      + 0x0000001c)
#define HWIO_RPM_M3_ITM_ITM_STIM7_RMSK                                          0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM7_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM7_ADDR, HWIO_RPM_M3_ITM_ITM_STIM7_RMSK)
#define HWIO_RPM_M3_ITM_ITM_STIM7_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM7_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_STIM7_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_STIM7_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_STIM7_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ITM_ITM_STIM7_ADDR,m,v,HWIO_RPM_M3_ITM_ITM_STIM7_IN)
#define HWIO_RPM_M3_ITM_ITM_STIM7_ITM_ITM_STIM7_BMSK                            0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM7_ITM_ITM_STIM7_SHFT                                   0x0

#define HWIO_RPM_M3_ITM_ITM_STIM8_ADDR                                          (RPM_M3_PPB_INT_REG_BASE      + 0x00000020)
#define HWIO_RPM_M3_ITM_ITM_STIM8_RMSK                                          0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM8_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM8_ADDR, HWIO_RPM_M3_ITM_ITM_STIM8_RMSK)
#define HWIO_RPM_M3_ITM_ITM_STIM8_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM8_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_STIM8_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_STIM8_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_STIM8_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ITM_ITM_STIM8_ADDR,m,v,HWIO_RPM_M3_ITM_ITM_STIM8_IN)
#define HWIO_RPM_M3_ITM_ITM_STIM8_ITM_ITM_STIM8_BMSK                            0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM8_ITM_ITM_STIM8_SHFT                                   0x0

#define HWIO_RPM_M3_ITM_ITM_STIM9_ADDR                                          (RPM_M3_PPB_INT_REG_BASE      + 0x00000024)
#define HWIO_RPM_M3_ITM_ITM_STIM9_RMSK                                          0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM9_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM9_ADDR, HWIO_RPM_M3_ITM_ITM_STIM9_RMSK)
#define HWIO_RPM_M3_ITM_ITM_STIM9_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM9_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_STIM9_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_STIM9_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_STIM9_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ITM_ITM_STIM9_ADDR,m,v,HWIO_RPM_M3_ITM_ITM_STIM9_IN)
#define HWIO_RPM_M3_ITM_ITM_STIM9_ITM_ITM_STIM9_BMSK                            0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM9_ITM_ITM_STIM9_SHFT                                   0x0

#define HWIO_RPM_M3_ITM_ITM_STIM10_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x00000028)
#define HWIO_RPM_M3_ITM_ITM_STIM10_RMSK                                         0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM10_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM10_ADDR, HWIO_RPM_M3_ITM_ITM_STIM10_RMSK)
#define HWIO_RPM_M3_ITM_ITM_STIM10_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM10_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_STIM10_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_STIM10_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_STIM10_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ITM_ITM_STIM10_ADDR,m,v,HWIO_RPM_M3_ITM_ITM_STIM10_IN)
#define HWIO_RPM_M3_ITM_ITM_STIM10_ITM_ITM_STIM10_BMSK                          0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM10_ITM_ITM_STIM10_SHFT                                 0x0

#define HWIO_RPM_M3_ITM_ITM_STIM11_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x0000002c)
#define HWIO_RPM_M3_ITM_ITM_STIM11_RMSK                                         0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM11_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM11_ADDR, HWIO_RPM_M3_ITM_ITM_STIM11_RMSK)
#define HWIO_RPM_M3_ITM_ITM_STIM11_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM11_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_STIM11_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_STIM11_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_STIM11_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ITM_ITM_STIM11_ADDR,m,v,HWIO_RPM_M3_ITM_ITM_STIM11_IN)
#define HWIO_RPM_M3_ITM_ITM_STIM11_ITM_ITM_STIM11_BMSK                          0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM11_ITM_ITM_STIM11_SHFT                                 0x0

#define HWIO_RPM_M3_ITM_ITM_STIM12_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x00000030)
#define HWIO_RPM_M3_ITM_ITM_STIM12_RMSK                                         0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM12_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM12_ADDR, HWIO_RPM_M3_ITM_ITM_STIM12_RMSK)
#define HWIO_RPM_M3_ITM_ITM_STIM12_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM12_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_STIM12_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_STIM12_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_STIM12_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ITM_ITM_STIM12_ADDR,m,v,HWIO_RPM_M3_ITM_ITM_STIM12_IN)
#define HWIO_RPM_M3_ITM_ITM_STIM12_ITM_ITM_STIM12_BMSK                          0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM12_ITM_ITM_STIM12_SHFT                                 0x0

#define HWIO_RPM_M3_ITM_ITM_STIM13_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x00000034)
#define HWIO_RPM_M3_ITM_ITM_STIM13_RMSK                                         0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM13_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM13_ADDR, HWIO_RPM_M3_ITM_ITM_STIM13_RMSK)
#define HWIO_RPM_M3_ITM_ITM_STIM13_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM13_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_STIM13_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_STIM13_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_STIM13_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ITM_ITM_STIM13_ADDR,m,v,HWIO_RPM_M3_ITM_ITM_STIM13_IN)
#define HWIO_RPM_M3_ITM_ITM_STIM13_ITM_ITM_STIM13_BMSK                          0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM13_ITM_ITM_STIM13_SHFT                                 0x0

#define HWIO_RPM_M3_ITM_ITM_STIM14_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x00000038)
#define HWIO_RPM_M3_ITM_ITM_STIM14_RMSK                                         0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM14_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM14_ADDR, HWIO_RPM_M3_ITM_ITM_STIM14_RMSK)
#define HWIO_RPM_M3_ITM_ITM_STIM14_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM14_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_STIM14_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_STIM14_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_STIM14_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ITM_ITM_STIM14_ADDR,m,v,HWIO_RPM_M3_ITM_ITM_STIM14_IN)
#define HWIO_RPM_M3_ITM_ITM_STIM14_ITM_ITM_STIM14_BMSK                          0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM14_ITM_ITM_STIM14_SHFT                                 0x0

#define HWIO_RPM_M3_ITM_ITM_STIM15_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x0000003c)
#define HWIO_RPM_M3_ITM_ITM_STIM15_RMSK                                         0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM15_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM15_ADDR, HWIO_RPM_M3_ITM_ITM_STIM15_RMSK)
#define HWIO_RPM_M3_ITM_ITM_STIM15_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM15_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_STIM15_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_STIM15_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_STIM15_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ITM_ITM_STIM15_ADDR,m,v,HWIO_RPM_M3_ITM_ITM_STIM15_IN)
#define HWIO_RPM_M3_ITM_ITM_STIM15_ITM_ITM_STIM15_BMSK                          0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM15_ITM_ITM_STIM15_SHFT                                 0x0

#define HWIO_RPM_M3_ITM_ITM_STIM16_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x00000040)
#define HWIO_RPM_M3_ITM_ITM_STIM16_RMSK                                         0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM16_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM16_ADDR, HWIO_RPM_M3_ITM_ITM_STIM16_RMSK)
#define HWIO_RPM_M3_ITM_ITM_STIM16_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM16_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_STIM16_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_STIM16_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_STIM16_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ITM_ITM_STIM16_ADDR,m,v,HWIO_RPM_M3_ITM_ITM_STIM16_IN)
#define HWIO_RPM_M3_ITM_ITM_STIM16_ITM_ITM_STIM16_BMSK                          0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM16_ITM_ITM_STIM16_SHFT                                 0x0

#define HWIO_RPM_M3_ITM_ITM_STIM17_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x00000044)
#define HWIO_RPM_M3_ITM_ITM_STIM17_RMSK                                         0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM17_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM17_ADDR, HWIO_RPM_M3_ITM_ITM_STIM17_RMSK)
#define HWIO_RPM_M3_ITM_ITM_STIM17_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM17_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_STIM17_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_STIM17_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_STIM17_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ITM_ITM_STIM17_ADDR,m,v,HWIO_RPM_M3_ITM_ITM_STIM17_IN)
#define HWIO_RPM_M3_ITM_ITM_STIM17_ITM_ITM_STIM17_BMSK                          0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM17_ITM_ITM_STIM17_SHFT                                 0x0

#define HWIO_RPM_M3_ITM_ITM_STIM18_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x00000048)
#define HWIO_RPM_M3_ITM_ITM_STIM18_RMSK                                         0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM18_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM18_ADDR, HWIO_RPM_M3_ITM_ITM_STIM18_RMSK)
#define HWIO_RPM_M3_ITM_ITM_STIM18_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM18_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_STIM18_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_STIM18_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_STIM18_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ITM_ITM_STIM18_ADDR,m,v,HWIO_RPM_M3_ITM_ITM_STIM18_IN)
#define HWIO_RPM_M3_ITM_ITM_STIM18_ITM_ITM_STIM18_BMSK                          0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM18_ITM_ITM_STIM18_SHFT                                 0x0

#define HWIO_RPM_M3_ITM_ITM_STIM19_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x0000004c)
#define HWIO_RPM_M3_ITM_ITM_STIM19_RMSK                                         0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM19_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM19_ADDR, HWIO_RPM_M3_ITM_ITM_STIM19_RMSK)
#define HWIO_RPM_M3_ITM_ITM_STIM19_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM19_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_STIM19_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_STIM19_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_STIM19_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ITM_ITM_STIM19_ADDR,m,v,HWIO_RPM_M3_ITM_ITM_STIM19_IN)
#define HWIO_RPM_M3_ITM_ITM_STIM19_ITM_ITM_STIM19_BMSK                          0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM19_ITM_ITM_STIM19_SHFT                                 0x0

#define HWIO_RPM_M3_ITM_ITM_STIM20_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x00000050)
#define HWIO_RPM_M3_ITM_ITM_STIM20_RMSK                                         0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM20_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM20_ADDR, HWIO_RPM_M3_ITM_ITM_STIM20_RMSK)
#define HWIO_RPM_M3_ITM_ITM_STIM20_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM20_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_STIM20_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_STIM20_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_STIM20_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ITM_ITM_STIM20_ADDR,m,v,HWIO_RPM_M3_ITM_ITM_STIM20_IN)
#define HWIO_RPM_M3_ITM_ITM_STIM20_ITM_ITM_STIM20_BMSK                          0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM20_ITM_ITM_STIM20_SHFT                                 0x0

#define HWIO_RPM_M3_ITM_ITM_STIM21_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x00000054)
#define HWIO_RPM_M3_ITM_ITM_STIM21_RMSK                                         0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM21_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM21_ADDR, HWIO_RPM_M3_ITM_ITM_STIM21_RMSK)
#define HWIO_RPM_M3_ITM_ITM_STIM21_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM21_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_STIM21_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_STIM21_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_STIM21_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ITM_ITM_STIM21_ADDR,m,v,HWIO_RPM_M3_ITM_ITM_STIM21_IN)
#define HWIO_RPM_M3_ITM_ITM_STIM21_ITM_ITM_STIM21_BMSK                          0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM21_ITM_ITM_STIM21_SHFT                                 0x0

#define HWIO_RPM_M3_ITM_ITM_STIM22_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x00000058)
#define HWIO_RPM_M3_ITM_ITM_STIM22_RMSK                                         0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM22_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM22_ADDR, HWIO_RPM_M3_ITM_ITM_STIM22_RMSK)
#define HWIO_RPM_M3_ITM_ITM_STIM22_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM22_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_STIM22_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_STIM22_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_STIM22_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ITM_ITM_STIM22_ADDR,m,v,HWIO_RPM_M3_ITM_ITM_STIM22_IN)
#define HWIO_RPM_M3_ITM_ITM_STIM22_ITM_ITM_STIM22_BMSK                          0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM22_ITM_ITM_STIM22_SHFT                                 0x0

#define HWIO_RPM_M3_ITM_ITM_STIM23_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x0000005c)
#define HWIO_RPM_M3_ITM_ITM_STIM23_RMSK                                         0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM23_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM23_ADDR, HWIO_RPM_M3_ITM_ITM_STIM23_RMSK)
#define HWIO_RPM_M3_ITM_ITM_STIM23_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM23_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_STIM23_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_STIM23_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_STIM23_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ITM_ITM_STIM23_ADDR,m,v,HWIO_RPM_M3_ITM_ITM_STIM23_IN)
#define HWIO_RPM_M3_ITM_ITM_STIM23_ITM_ITM_STIM23_BMSK                          0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM23_ITM_ITM_STIM23_SHFT                                 0x0

#define HWIO_RPM_M3_ITM_ITM_STIM24_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x00000060)
#define HWIO_RPM_M3_ITM_ITM_STIM24_RMSK                                         0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM24_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM24_ADDR, HWIO_RPM_M3_ITM_ITM_STIM24_RMSK)
#define HWIO_RPM_M3_ITM_ITM_STIM24_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM24_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_STIM24_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_STIM24_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_STIM24_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ITM_ITM_STIM24_ADDR,m,v,HWIO_RPM_M3_ITM_ITM_STIM24_IN)
#define HWIO_RPM_M3_ITM_ITM_STIM24_ITM_ITM_STIM24_BMSK                          0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM24_ITM_ITM_STIM24_SHFT                                 0x0

#define HWIO_RPM_M3_ITM_ITM_STIM25_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x00000064)
#define HWIO_RPM_M3_ITM_ITM_STIM25_RMSK                                         0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM25_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM25_ADDR, HWIO_RPM_M3_ITM_ITM_STIM25_RMSK)
#define HWIO_RPM_M3_ITM_ITM_STIM25_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM25_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_STIM25_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_STIM25_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_STIM25_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ITM_ITM_STIM25_ADDR,m,v,HWIO_RPM_M3_ITM_ITM_STIM25_IN)
#define HWIO_RPM_M3_ITM_ITM_STIM25_ITM_ITM_STIM25_BMSK                          0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM25_ITM_ITM_STIM25_SHFT                                 0x0

#define HWIO_RPM_M3_ITM_ITM_STIM26_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x00000068)
#define HWIO_RPM_M3_ITM_ITM_STIM26_RMSK                                         0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM26_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM26_ADDR, HWIO_RPM_M3_ITM_ITM_STIM26_RMSK)
#define HWIO_RPM_M3_ITM_ITM_STIM26_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM26_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_STIM26_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_STIM26_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_STIM26_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ITM_ITM_STIM26_ADDR,m,v,HWIO_RPM_M3_ITM_ITM_STIM26_IN)
#define HWIO_RPM_M3_ITM_ITM_STIM26_ITM_ITM_STIM26_BMSK                          0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM26_ITM_ITM_STIM26_SHFT                                 0x0

#define HWIO_RPM_M3_ITM_ITM_STIM27_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x0000006c)
#define HWIO_RPM_M3_ITM_ITM_STIM27_RMSK                                         0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM27_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM27_ADDR, HWIO_RPM_M3_ITM_ITM_STIM27_RMSK)
#define HWIO_RPM_M3_ITM_ITM_STIM27_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM27_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_STIM27_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_STIM27_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_STIM27_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ITM_ITM_STIM27_ADDR,m,v,HWIO_RPM_M3_ITM_ITM_STIM27_IN)
#define HWIO_RPM_M3_ITM_ITM_STIM27_ITM_ITM_STIM27_BMSK                          0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM27_ITM_ITM_STIM27_SHFT                                 0x0

#define HWIO_RPM_M3_ITM_ITM_STIM28_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x00000070)
#define HWIO_RPM_M3_ITM_ITM_STIM28_RMSK                                         0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM28_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM28_ADDR, HWIO_RPM_M3_ITM_ITM_STIM28_RMSK)
#define HWIO_RPM_M3_ITM_ITM_STIM28_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM28_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_STIM28_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_STIM28_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_STIM28_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ITM_ITM_STIM28_ADDR,m,v,HWIO_RPM_M3_ITM_ITM_STIM28_IN)
#define HWIO_RPM_M3_ITM_ITM_STIM28_ITM_ITM_STIM28_BMSK                          0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM28_ITM_ITM_STIM28_SHFT                                 0x0

#define HWIO_RPM_M3_ITM_ITM_STIM29_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x00000074)
#define HWIO_RPM_M3_ITM_ITM_STIM29_RMSK                                         0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM29_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM29_ADDR, HWIO_RPM_M3_ITM_ITM_STIM29_RMSK)
#define HWIO_RPM_M3_ITM_ITM_STIM29_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM29_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_STIM29_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_STIM29_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_STIM29_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ITM_ITM_STIM29_ADDR,m,v,HWIO_RPM_M3_ITM_ITM_STIM29_IN)
#define HWIO_RPM_M3_ITM_ITM_STIM29_ITM_ITM_STIM29_BMSK                          0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM29_ITM_ITM_STIM29_SHFT                                 0x0

#define HWIO_RPM_M3_ITM_ITM_STIM30_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x00000078)
#define HWIO_RPM_M3_ITM_ITM_STIM30_RMSK                                         0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM30_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM30_ADDR, HWIO_RPM_M3_ITM_ITM_STIM30_RMSK)
#define HWIO_RPM_M3_ITM_ITM_STIM30_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM30_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_STIM30_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_STIM30_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_STIM30_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ITM_ITM_STIM30_ADDR,m,v,HWIO_RPM_M3_ITM_ITM_STIM30_IN)
#define HWIO_RPM_M3_ITM_ITM_STIM30_ITM_ITM_STIM30_BMSK                          0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM30_ITM_ITM_STIM30_SHFT                                 0x0

#define HWIO_RPM_M3_ITM_ITM_STIM31_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x0000007c)
#define HWIO_RPM_M3_ITM_ITM_STIM31_RMSK                                         0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM31_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM31_ADDR, HWIO_RPM_M3_ITM_ITM_STIM31_RMSK)
#define HWIO_RPM_M3_ITM_ITM_STIM31_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_STIM31_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_STIM31_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_STIM31_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_STIM31_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ITM_ITM_STIM31_ADDR,m,v,HWIO_RPM_M3_ITM_ITM_STIM31_IN)
#define HWIO_RPM_M3_ITM_ITM_STIM31_ITM_ITM_STIM31_BMSK                          0xffffffff
#define HWIO_RPM_M3_ITM_ITM_STIM31_ITM_ITM_STIM31_SHFT                                 0x0

#define HWIO_RPM_M3_ITM_ITM_TER_ADDR                                            (RPM_M3_PPB_INT_REG_BASE      + 0x00000e00)
#define HWIO_RPM_M3_ITM_ITM_TER_RMSK                                            0xffffffff
#define HWIO_RPM_M3_ITM_ITM_TER_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_TER_ADDR, HWIO_RPM_M3_ITM_ITM_TER_RMSK)
#define HWIO_RPM_M3_ITM_ITM_TER_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_TER_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_TER_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_TER_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_TER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ITM_ITM_TER_ADDR,m,v,HWIO_RPM_M3_ITM_ITM_TER_IN)
#define HWIO_RPM_M3_ITM_ITM_TER_STIMENA_BMSK                                    0xffffffff
#define HWIO_RPM_M3_ITM_ITM_TER_STIMENA_SHFT                                           0x0

#define HWIO_RPM_M3_ITM_ITM_TPR_ADDR                                            (RPM_M3_PPB_INT_REG_BASE      + 0x00000e40)
#define HWIO_RPM_M3_ITM_ITM_TPR_RMSK                                                   0xf
#define HWIO_RPM_M3_ITM_ITM_TPR_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_TPR_ADDR, HWIO_RPM_M3_ITM_ITM_TPR_RMSK)
#define HWIO_RPM_M3_ITM_ITM_TPR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_TPR_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_TPR_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_TPR_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_TPR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ITM_ITM_TPR_ADDR,m,v,HWIO_RPM_M3_ITM_ITM_TPR_IN)
#define HWIO_RPM_M3_ITM_ITM_TPR_PRIVMASK_BMSK                                          0xf
#define HWIO_RPM_M3_ITM_ITM_TPR_PRIVMASK_SHFT                                          0x0

#define HWIO_RPM_M3_ITM_ITM_TCR_ADDR                                            (RPM_M3_PPB_INT_REG_BASE      + 0x00000e80)
#define HWIO_RPM_M3_ITM_ITM_TCR_RMSK                                              0xff031f
#define HWIO_RPM_M3_ITM_ITM_TCR_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_TCR_ADDR, HWIO_RPM_M3_ITM_ITM_TCR_RMSK)
#define HWIO_RPM_M3_ITM_ITM_TCR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_TCR_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_TCR_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_TCR_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_TCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ITM_ITM_TCR_ADDR,m,v,HWIO_RPM_M3_ITM_ITM_TCR_IN)
#define HWIO_RPM_M3_ITM_ITM_TCR_BUSY_BMSK                                         0x800000
#define HWIO_RPM_M3_ITM_ITM_TCR_BUSY_SHFT                                             0x17
#define HWIO_RPM_M3_ITM_ITM_TCR_ATBID_BMSK                                        0x7f0000
#define HWIO_RPM_M3_ITM_ITM_TCR_ATBID_SHFT                                            0x10
#define HWIO_RPM_M3_ITM_ITM_TCR_TSPRESCALE_BMSK                                      0x300
#define HWIO_RPM_M3_ITM_ITM_TCR_TSPRESCALE_SHFT                                        0x8
#define HWIO_RPM_M3_ITM_ITM_TCR_TSPRESCALE_ENUM_0B00_FVAL                              0x0
#define HWIO_RPM_M3_ITM_ITM_TCR_TSPRESCALE_ENUM_0B01_FVAL                              0x1
#define HWIO_RPM_M3_ITM_ITM_TCR_TSPRESCALE_ENUM_0B10_FVAL                              0x2
#define HWIO_RPM_M3_ITM_ITM_TCR_TSPRESCALE_ENUM_0B11_FVAL                              0x3
#define HWIO_RPM_M3_ITM_ITM_TCR_SWOENA_BMSK                                           0x10
#define HWIO_RPM_M3_ITM_ITM_TCR_SWOENA_SHFT                                            0x4
#define HWIO_RPM_M3_ITM_ITM_TCR_DWTENA_BMSK                                            0x8
#define HWIO_RPM_M3_ITM_ITM_TCR_DWTENA_SHFT                                            0x3
#define HWIO_RPM_M3_ITM_ITM_TCR_SYNCENA_BMSK                                           0x4
#define HWIO_RPM_M3_ITM_ITM_TCR_SYNCENA_SHFT                                           0x2
#define HWIO_RPM_M3_ITM_ITM_TCR_TSENA_BMSK                                             0x2
#define HWIO_RPM_M3_ITM_ITM_TCR_TSENA_SHFT                                             0x1
#define HWIO_RPM_M3_ITM_ITM_TCR_ITMENA_BMSK                                            0x1
#define HWIO_RPM_M3_ITM_ITM_TCR_ITMENA_SHFT                                            0x0

#define HWIO_RPM_M3_ITM_ITM_IWR_ADDR                                            (RPM_M3_PPB_INT_REG_BASE      + 0x00000ef8)
#define HWIO_RPM_M3_ITM_ITM_IWR_RMSK                                                   0x1
#define HWIO_RPM_M3_ITM_ITM_IWR_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_IWR_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_IWR_ATVALIDM_BMSK                                          0x1
#define HWIO_RPM_M3_ITM_ITM_IWR_ATVALIDM_SHFT                                          0x0
#define HWIO_RPM_M3_ITM_ITM_IWR_ATVALIDM_ENUM_0B0_FVAL                                 0x0
#define HWIO_RPM_M3_ITM_ITM_IWR_ATVALIDM_ENUM_0B1_FVAL                                 0x1

#define HWIO_RPM_M3_ITM_ITM_IMCR_ADDR                                           (RPM_M3_PPB_INT_REG_BASE      + 0x00000f00)
#define HWIO_RPM_M3_ITM_ITM_IMCR_RMSK                                                  0x1
#define HWIO_RPM_M3_ITM_ITM_IMCR_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_IMCR_ADDR, HWIO_RPM_M3_ITM_ITM_IMCR_RMSK)
#define HWIO_RPM_M3_ITM_ITM_IMCR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_IMCR_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_IMCR_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_IMCR_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_IMCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ITM_ITM_IMCR_ADDR,m,v,HWIO_RPM_M3_ITM_ITM_IMCR_IN)
#define HWIO_RPM_M3_ITM_ITM_IMCR_INTEGRATION_BMSK                                      0x1
#define HWIO_RPM_M3_ITM_ITM_IMCR_INTEGRATION_SHFT                                      0x0
#define HWIO_RPM_M3_ITM_ITM_IMCR_INTEGRATION_ENUM_0B0_FVAL                             0x0
#define HWIO_RPM_M3_ITM_ITM_IMCR_INTEGRATION_ENUM_0B1_FVAL                             0x1

#define HWIO_RPM_M3_ITM_ITM_LAR_ADDR                                            (RPM_M3_PPB_INT_REG_BASE      + 0x00000fb0)
#define HWIO_RPM_M3_ITM_ITM_LAR_RMSK                                            0xffffffff
#define HWIO_RPM_M3_ITM_ITM_LAR_OUT(v)      \
        out_dword(HWIO_RPM_M3_ITM_ITM_LAR_ADDR,v)
#define HWIO_RPM_M3_ITM_ITM_LAR_LOCK_ACCESS_BMSK                                0xffffffff
#define HWIO_RPM_M3_ITM_ITM_LAR_LOCK_ACCESS_SHFT                                       0x0

#define HWIO_RPM_M3_ITM_ITM_LSR_ADDR                                            (RPM_M3_PPB_INT_REG_BASE      + 0x00000fb4)
#define HWIO_RPM_M3_ITM_ITM_LSR_RMSK                                                   0x7
#define HWIO_RPM_M3_ITM_ITM_LSR_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_LSR_ADDR, HWIO_RPM_M3_ITM_ITM_LSR_RMSK)
#define HWIO_RPM_M3_ITM_ITM_LSR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_ITM_LSR_ADDR, m)
#define HWIO_RPM_M3_ITM_ITM_LSR_BYTEACC_BMSK                                           0x4
#define HWIO_RPM_M3_ITM_ITM_LSR_BYTEACC_SHFT                                           0x2
#define HWIO_RPM_M3_ITM_ITM_LSR_ACCESS_BMSK                                            0x2
#define HWIO_RPM_M3_ITM_ITM_LSR_ACCESS_SHFT                                            0x1
#define HWIO_RPM_M3_ITM_ITM_LSR_PRESENT_BMSK                                           0x1
#define HWIO_RPM_M3_ITM_ITM_LSR_PRESENT_SHFT                                           0x0

#define HWIO_RPM_M3_ITM_PID4_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x00000fd0)
#define HWIO_RPM_M3_ITM_PID4_RMSK                                               0xffffffff
#define HWIO_RPM_M3_ITM_PID4_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_PID4_ADDR, HWIO_RPM_M3_ITM_PID4_RMSK)
#define HWIO_RPM_M3_ITM_PID4_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_PID4_ADDR, m)
#define HWIO_RPM_M3_ITM_PID4_ITM_PID4_BMSK                                      0xffffffff
#define HWIO_RPM_M3_ITM_PID4_ITM_PID4_SHFT                                             0x0

#define HWIO_RPM_M3_ITM_PID5_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x00000fd4)
#define HWIO_RPM_M3_ITM_PID5_RMSK                                               0xffffffff
#define HWIO_RPM_M3_ITM_PID5_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_PID5_ADDR, HWIO_RPM_M3_ITM_PID5_RMSK)
#define HWIO_RPM_M3_ITM_PID5_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_PID5_ADDR, m)
#define HWIO_RPM_M3_ITM_PID5_ITM_PID5_BMSK                                      0xffffffff
#define HWIO_RPM_M3_ITM_PID5_ITM_PID5_SHFT                                             0x0

#define HWIO_RPM_M3_ITM_PID6_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x00000fd8)
#define HWIO_RPM_M3_ITM_PID6_RMSK                                               0xffffffff
#define HWIO_RPM_M3_ITM_PID6_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_PID6_ADDR, HWIO_RPM_M3_ITM_PID6_RMSK)
#define HWIO_RPM_M3_ITM_PID6_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_PID6_ADDR, m)
#define HWIO_RPM_M3_ITM_PID6_ITM_PID6_BMSK                                      0xffffffff
#define HWIO_RPM_M3_ITM_PID6_ITM_PID6_SHFT                                             0x0

#define HWIO_RPM_M3_ITM_PID7_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x00000fdc)
#define HWIO_RPM_M3_ITM_PID7_RMSK                                               0xffffffff
#define HWIO_RPM_M3_ITM_PID7_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_PID7_ADDR, HWIO_RPM_M3_ITM_PID7_RMSK)
#define HWIO_RPM_M3_ITM_PID7_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_PID7_ADDR, m)
#define HWIO_RPM_M3_ITM_PID7_ITM_PID7_BMSK                                      0xffffffff
#define HWIO_RPM_M3_ITM_PID7_ITM_PID7_SHFT                                             0x0

#define HWIO_RPM_M3_ITM_PID0_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x00000fe0)
#define HWIO_RPM_M3_ITM_PID0_RMSK                                               0xffffffff
#define HWIO_RPM_M3_ITM_PID0_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_PID0_ADDR, HWIO_RPM_M3_ITM_PID0_RMSK)
#define HWIO_RPM_M3_ITM_PID0_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_PID0_ADDR, m)
#define HWIO_RPM_M3_ITM_PID0_ITM_PID0_BMSK                                      0xffffffff
#define HWIO_RPM_M3_ITM_PID0_ITM_PID0_SHFT                                             0x0

#define HWIO_RPM_M3_ITM_PID1_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x00000fe4)
#define HWIO_RPM_M3_ITM_PID1_RMSK                                               0xffffffff
#define HWIO_RPM_M3_ITM_PID1_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_PID1_ADDR, HWIO_RPM_M3_ITM_PID1_RMSK)
#define HWIO_RPM_M3_ITM_PID1_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_PID1_ADDR, m)
#define HWIO_RPM_M3_ITM_PID1_ITM_PID1_BMSK                                      0xffffffff
#define HWIO_RPM_M3_ITM_PID1_ITM_PID1_SHFT                                             0x0

#define HWIO_RPM_M3_ITM_PID2_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x00000fe8)
#define HWIO_RPM_M3_ITM_PID2_RMSK                                               0xffffffff
#define HWIO_RPM_M3_ITM_PID2_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_PID2_ADDR, HWIO_RPM_M3_ITM_PID2_RMSK)
#define HWIO_RPM_M3_ITM_PID2_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_PID2_ADDR, m)
#define HWIO_RPM_M3_ITM_PID2_ITM_PID2_BMSK                                      0xffffffff
#define HWIO_RPM_M3_ITM_PID2_ITM_PID2_SHFT                                             0x0

#define HWIO_RPM_M3_ITM_PID3_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x00000fec)
#define HWIO_RPM_M3_ITM_PID3_RMSK                                               0xffffffff
#define HWIO_RPM_M3_ITM_PID3_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_PID3_ADDR, HWIO_RPM_M3_ITM_PID3_RMSK)
#define HWIO_RPM_M3_ITM_PID3_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_PID3_ADDR, m)
#define HWIO_RPM_M3_ITM_PID3_ITM_PID3_BMSK                                      0xffffffff
#define HWIO_RPM_M3_ITM_PID3_ITM_PID3_SHFT                                             0x0

#define HWIO_RPM_M3_ITM_CID0_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x00000ff0)
#define HWIO_RPM_M3_ITM_CID0_RMSK                                               0xffffffff
#define HWIO_RPM_M3_ITM_CID0_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_CID0_ADDR, HWIO_RPM_M3_ITM_CID0_RMSK)
#define HWIO_RPM_M3_ITM_CID0_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_CID0_ADDR, m)
#define HWIO_RPM_M3_ITM_CID0_ITM_CID0_BMSK                                      0xffffffff
#define HWIO_RPM_M3_ITM_CID0_ITM_CID0_SHFT                                             0x0

#define HWIO_RPM_M3_ITM_CID1_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x00000ff4)
#define HWIO_RPM_M3_ITM_CID1_RMSK                                               0xffffffff
#define HWIO_RPM_M3_ITM_CID1_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_CID1_ADDR, HWIO_RPM_M3_ITM_CID1_RMSK)
#define HWIO_RPM_M3_ITM_CID1_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_CID1_ADDR, m)
#define HWIO_RPM_M3_ITM_CID1_ITM_CID1_BMSK                                      0xffffffff
#define HWIO_RPM_M3_ITM_CID1_ITM_CID1_SHFT                                             0x0

#define HWIO_RPM_M3_ITM_CID2_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x00000ff8)
#define HWIO_RPM_M3_ITM_CID2_RMSK                                               0xffffffff
#define HWIO_RPM_M3_ITM_CID2_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_CID2_ADDR, HWIO_RPM_M3_ITM_CID2_RMSK)
#define HWIO_RPM_M3_ITM_CID2_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_CID2_ADDR, m)
#define HWIO_RPM_M3_ITM_CID2_ITM_CID2_BMSK                                      0xffffffff
#define HWIO_RPM_M3_ITM_CID2_ITM_CID2_SHFT                                             0x0

#define HWIO_RPM_M3_ITM_CID3_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x00000ffc)
#define HWIO_RPM_M3_ITM_CID3_RMSK                                               0xffffffff
#define HWIO_RPM_M3_ITM_CID3_IN          \
        in_dword_masked(HWIO_RPM_M3_ITM_CID3_ADDR, HWIO_RPM_M3_ITM_CID3_RMSK)
#define HWIO_RPM_M3_ITM_CID3_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ITM_CID3_ADDR, m)
#define HWIO_RPM_M3_ITM_CID3_ITM_CID3_BMSK                                      0xffffffff
#define HWIO_RPM_M3_ITM_CID3_ITM_CID3_SHFT                                             0x0

#define HWIO_RPM_M3_DWT_DWT_CTRL_ADDR                                           (RPM_M3_PPB_INT_REG_BASE      + 0x00001000)
#define HWIO_RPM_M3_DWT_DWT_CTRL_RMSK                                            0x37f1fff
#define HWIO_RPM_M3_DWT_DWT_CTRL_IN          \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_CTRL_ADDR, HWIO_RPM_M3_DWT_DWT_CTRL_RMSK)
#define HWIO_RPM_M3_DWT_DWT_CTRL_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_CTRL_ADDR, m)
#define HWIO_RPM_M3_DWT_DWT_CTRL_OUT(v)      \
        out_dword(HWIO_RPM_M3_DWT_DWT_CTRL_ADDR,v)
#define HWIO_RPM_M3_DWT_DWT_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_DWT_DWT_CTRL_ADDR,m,v,HWIO_RPM_M3_DWT_DWT_CTRL_IN)
#define HWIO_RPM_M3_DWT_DWT_CTRL_NOCYCCNT_BMSK                                   0x2000000
#define HWIO_RPM_M3_DWT_DWT_CTRL_NOCYCCNT_SHFT                                        0x19
#define HWIO_RPM_M3_DWT_DWT_CTRL_NOPRFCNT_BMSK                                   0x1000000
#define HWIO_RPM_M3_DWT_DWT_CTRL_NOPRFCNT_SHFT                                        0x18
#define HWIO_RPM_M3_DWT_DWT_CTRL_CYCEVTENA_BMSK                                   0x400000
#define HWIO_RPM_M3_DWT_DWT_CTRL_CYCEVTENA_SHFT                                       0x16
#define HWIO_RPM_M3_DWT_DWT_CTRL_CYCEVTENA_ENUM_0B0_FVAL                               0x0
#define HWIO_RPM_M3_DWT_DWT_CTRL_CYCEVTENA_ENUM_0B1_FVAL                               0x1
#define HWIO_RPM_M3_DWT_DWT_CTRL_FOLDEVTENA_BMSK                                  0x200000
#define HWIO_RPM_M3_DWT_DWT_CTRL_FOLDEVTENA_SHFT                                      0x15
#define HWIO_RPM_M3_DWT_DWT_CTRL_FOLDEVTENA_ENUM_0B0_FVAL                              0x0
#define HWIO_RPM_M3_DWT_DWT_CTRL_FOLDEVTENA_ENUM_0B1_FVAL                              0x1
#define HWIO_RPM_M3_DWT_DWT_CTRL_LSUEVTENA_BMSK                                   0x100000
#define HWIO_RPM_M3_DWT_DWT_CTRL_LSUEVTENA_SHFT                                       0x14
#define HWIO_RPM_M3_DWT_DWT_CTRL_LSUEVTENA_ENUM_0B0_FVAL                               0x0
#define HWIO_RPM_M3_DWT_DWT_CTRL_LSUEVTENA_ENUM_0B1_FVAL                               0x1
#define HWIO_RPM_M3_DWT_DWT_CTRL_SLEEPEVTENA_BMSK                                  0x80000
#define HWIO_RPM_M3_DWT_DWT_CTRL_SLEEPEVTENA_SHFT                                     0x13
#define HWIO_RPM_M3_DWT_DWT_CTRL_SLEEPEVTENA_ENUM_0B0_FVAL                             0x0
#define HWIO_RPM_M3_DWT_DWT_CTRL_SLEEPEVTENA_ENUM_0B1_FVAL                             0x1
#define HWIO_RPM_M3_DWT_DWT_CTRL_EXCEVTENA_BMSK                                    0x40000
#define HWIO_RPM_M3_DWT_DWT_CTRL_EXCEVTENA_SHFT                                       0x12
#define HWIO_RPM_M3_DWT_DWT_CTRL_EXCEVTENA_ENUM_0B0_FVAL                               0x0
#define HWIO_RPM_M3_DWT_DWT_CTRL_EXCEVTENA_ENUM_0B1_FVAL                               0x1
#define HWIO_RPM_M3_DWT_DWT_CTRL_CPIEVTENA_BMSK                                    0x20000
#define HWIO_RPM_M3_DWT_DWT_CTRL_CPIEVTENA_SHFT                                       0x11
#define HWIO_RPM_M3_DWT_DWT_CTRL_CPIEVTENA_ENUM_0B0_FVAL                               0x0
#define HWIO_RPM_M3_DWT_DWT_CTRL_CPIEVTENA_ENUM_0B1_FVAL                               0x1
#define HWIO_RPM_M3_DWT_DWT_CTRL_EXCTRCENA_BMSK                                    0x10000
#define HWIO_RPM_M3_DWT_DWT_CTRL_EXCTRCENA_SHFT                                       0x10
#define HWIO_RPM_M3_DWT_DWT_CTRL_EXCTRCENA_ENUM_0B0_FVAL                               0x0
#define HWIO_RPM_M3_DWT_DWT_CTRL_EXCTRCENA_ENUM_0B1_FVAL                               0x1
#define HWIO_RPM_M3_DWT_DWT_CTRL_PCSAMPLEENA_BMSK                                   0x1000
#define HWIO_RPM_M3_DWT_DWT_CTRL_PCSAMPLEENA_SHFT                                      0xc
#define HWIO_RPM_M3_DWT_DWT_CTRL_PCSAMPLEENA_ENUM_0B0_FVAL                             0x0
#define HWIO_RPM_M3_DWT_DWT_CTRL_PCSAMPLEENA_ENUM_0B1_FVAL                             0x1
#define HWIO_RPM_M3_DWT_DWT_CTRL_SYNCTAP_BMSK                                        0xc00
#define HWIO_RPM_M3_DWT_DWT_CTRL_SYNCTAP_SHFT                                          0xa
#define HWIO_RPM_M3_DWT_DWT_CTRL_SYNCTAP_ENUM_0B00_FVAL                                0x0
#define HWIO_RPM_M3_DWT_DWT_CTRL_SYNCTAP_ENUM_0B01_FVAL                                0x1
#define HWIO_RPM_M3_DWT_DWT_CTRL_SYNCTAP_ENUM_0B10_FVAL                                0x2
#define HWIO_RPM_M3_DWT_DWT_CTRL_SYNCTAP_ENUM_0B11_FVAL                                0x3
#define HWIO_RPM_M3_DWT_DWT_CTRL_CYCTAP_BMSK                                         0x200
#define HWIO_RPM_M3_DWT_DWT_CTRL_CYCTAP_SHFT                                           0x9
#define HWIO_RPM_M3_DWT_DWT_CTRL_CYCTAP_ENUM_0B0_FVAL                                  0x0
#define HWIO_RPM_M3_DWT_DWT_CTRL_CYCTAP_ENUM_0B1_FVAL                                  0x1
#define HWIO_RPM_M3_DWT_DWT_CTRL_POSTCNT_BMSK                                        0x1e0
#define HWIO_RPM_M3_DWT_DWT_CTRL_POSTCNT_SHFT                                          0x5
#define HWIO_RPM_M3_DWT_DWT_CTRL_POSTPRESET_BMSK                                      0x1e
#define HWIO_RPM_M3_DWT_DWT_CTRL_POSTPRESET_SHFT                                       0x1
#define HWIO_RPM_M3_DWT_DWT_CTRL_CYCCNTENA_BMSK                                        0x1
#define HWIO_RPM_M3_DWT_DWT_CTRL_CYCCNTENA_SHFT                                        0x0

#define HWIO_RPM_M3_DWT_DWT_CYCCNT_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x00001004)
#define HWIO_RPM_M3_DWT_DWT_CYCCNT_RMSK                                         0xffffffff
#define HWIO_RPM_M3_DWT_DWT_CYCCNT_IN          \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_CYCCNT_ADDR, HWIO_RPM_M3_DWT_DWT_CYCCNT_RMSK)
#define HWIO_RPM_M3_DWT_DWT_CYCCNT_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_CYCCNT_ADDR, m)
#define HWIO_RPM_M3_DWT_DWT_CYCCNT_OUT(v)      \
        out_dword(HWIO_RPM_M3_DWT_DWT_CYCCNT_ADDR,v)
#define HWIO_RPM_M3_DWT_DWT_CYCCNT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_DWT_DWT_CYCCNT_ADDR,m,v,HWIO_RPM_M3_DWT_DWT_CYCCNT_IN)
#define HWIO_RPM_M3_DWT_DWT_CYCCNT_CYCCNT_BMSK                                  0xffffffff
#define HWIO_RPM_M3_DWT_DWT_CYCCNT_CYCCNT_SHFT                                         0x0

#define HWIO_RPM_M3_DWT_DWT_CPICNT_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x00001008)
#define HWIO_RPM_M3_DWT_DWT_CPICNT_RMSK                                               0xff
#define HWIO_RPM_M3_DWT_DWT_CPICNT_IN          \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_CPICNT_ADDR, HWIO_RPM_M3_DWT_DWT_CPICNT_RMSK)
#define HWIO_RPM_M3_DWT_DWT_CPICNT_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_CPICNT_ADDR, m)
#define HWIO_RPM_M3_DWT_DWT_CPICNT_OUT(v)      \
        out_dword(HWIO_RPM_M3_DWT_DWT_CPICNT_ADDR,v)
#define HWIO_RPM_M3_DWT_DWT_CPICNT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_DWT_DWT_CPICNT_ADDR,m,v,HWIO_RPM_M3_DWT_DWT_CPICNT_IN)
#define HWIO_RPM_M3_DWT_DWT_CPICNT_CPICNT_BMSK                                        0xff
#define HWIO_RPM_M3_DWT_DWT_CPICNT_CPICNT_SHFT                                         0x0

#define HWIO_RPM_M3_DWT_DWT_EXCCNT_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x0000100c)
#define HWIO_RPM_M3_DWT_DWT_EXCCNT_RMSK                                               0xff
#define HWIO_RPM_M3_DWT_DWT_EXCCNT_IN          \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_EXCCNT_ADDR, HWIO_RPM_M3_DWT_DWT_EXCCNT_RMSK)
#define HWIO_RPM_M3_DWT_DWT_EXCCNT_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_EXCCNT_ADDR, m)
#define HWIO_RPM_M3_DWT_DWT_EXCCNT_OUT(v)      \
        out_dword(HWIO_RPM_M3_DWT_DWT_EXCCNT_ADDR,v)
#define HWIO_RPM_M3_DWT_DWT_EXCCNT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_DWT_DWT_EXCCNT_ADDR,m,v,HWIO_RPM_M3_DWT_DWT_EXCCNT_IN)
#define HWIO_RPM_M3_DWT_DWT_EXCCNT_EXCCNT_BMSK                                        0xff
#define HWIO_RPM_M3_DWT_DWT_EXCCNT_EXCCNT_SHFT                                         0x0

#define HWIO_RPM_M3_DWT_DWT_SLEEPCNT_ADDR                                       (RPM_M3_PPB_INT_REG_BASE      + 0x00001010)
#define HWIO_RPM_M3_DWT_DWT_SLEEPCNT_RMSK                                             0xff
#define HWIO_RPM_M3_DWT_DWT_SLEEPCNT_IN          \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_SLEEPCNT_ADDR, HWIO_RPM_M3_DWT_DWT_SLEEPCNT_RMSK)
#define HWIO_RPM_M3_DWT_DWT_SLEEPCNT_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_SLEEPCNT_ADDR, m)
#define HWIO_RPM_M3_DWT_DWT_SLEEPCNT_OUT(v)      \
        out_dword(HWIO_RPM_M3_DWT_DWT_SLEEPCNT_ADDR,v)
#define HWIO_RPM_M3_DWT_DWT_SLEEPCNT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_DWT_DWT_SLEEPCNT_ADDR,m,v,HWIO_RPM_M3_DWT_DWT_SLEEPCNT_IN)
#define HWIO_RPM_M3_DWT_DWT_SLEEPCNT_SLEEPCNT_BMSK                                    0xff
#define HWIO_RPM_M3_DWT_DWT_SLEEPCNT_SLEEPCNT_SHFT                                     0x0

#define HWIO_RPM_M3_DWT_DWT_LSUCNT_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x00001014)
#define HWIO_RPM_M3_DWT_DWT_LSUCNT_RMSK                                               0xff
#define HWIO_RPM_M3_DWT_DWT_LSUCNT_IN          \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_LSUCNT_ADDR, HWIO_RPM_M3_DWT_DWT_LSUCNT_RMSK)
#define HWIO_RPM_M3_DWT_DWT_LSUCNT_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_LSUCNT_ADDR, m)
#define HWIO_RPM_M3_DWT_DWT_LSUCNT_OUT(v)      \
        out_dword(HWIO_RPM_M3_DWT_DWT_LSUCNT_ADDR,v)
#define HWIO_RPM_M3_DWT_DWT_LSUCNT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_DWT_DWT_LSUCNT_ADDR,m,v,HWIO_RPM_M3_DWT_DWT_LSUCNT_IN)
#define HWIO_RPM_M3_DWT_DWT_LSUCNT_LSUCNT_BMSK                                        0xff
#define HWIO_RPM_M3_DWT_DWT_LSUCNT_LSUCNT_SHFT                                         0x0

#define HWIO_RPM_M3_DWT_DWT_FOLDCNT_ADDR                                        (RPM_M3_PPB_INT_REG_BASE      + 0x00001018)
#define HWIO_RPM_M3_DWT_DWT_FOLDCNT_RMSK                                              0xff
#define HWIO_RPM_M3_DWT_DWT_FOLDCNT_IN          \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_FOLDCNT_ADDR, HWIO_RPM_M3_DWT_DWT_FOLDCNT_RMSK)
#define HWIO_RPM_M3_DWT_DWT_FOLDCNT_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_FOLDCNT_ADDR, m)
#define HWIO_RPM_M3_DWT_DWT_FOLDCNT_OUT(v)      \
        out_dword(HWIO_RPM_M3_DWT_DWT_FOLDCNT_ADDR,v)
#define HWIO_RPM_M3_DWT_DWT_FOLDCNT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_DWT_DWT_FOLDCNT_ADDR,m,v,HWIO_RPM_M3_DWT_DWT_FOLDCNT_IN)
#define HWIO_RPM_M3_DWT_DWT_FOLDCNT_FOLDCNT_BMSK                                      0xff
#define HWIO_RPM_M3_DWT_DWT_FOLDCNT_FOLDCNT_SHFT                                       0x0

#define HWIO_RPM_M3_DWT_DWT_PCSR_ADDR                                           (RPM_M3_PPB_INT_REG_BASE      + 0x0000101c)
#define HWIO_RPM_M3_DWT_DWT_PCSR_RMSK                                           0xffffffff
#define HWIO_RPM_M3_DWT_DWT_PCSR_IN          \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_PCSR_ADDR, HWIO_RPM_M3_DWT_DWT_PCSR_RMSK)
#define HWIO_RPM_M3_DWT_DWT_PCSR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_PCSR_ADDR, m)
#define HWIO_RPM_M3_DWT_DWT_PCSR_EIASAMPLE_BMSK                                 0xffffffff
#define HWIO_RPM_M3_DWT_DWT_PCSR_EIASAMPLE_SHFT                                        0x0

#define HWIO_RPM_M3_DWT_DWT_COMP0_ADDR                                          (RPM_M3_PPB_INT_REG_BASE      + 0x00001020)
#define HWIO_RPM_M3_DWT_DWT_COMP0_RMSK                                          0xffffffff
#define HWIO_RPM_M3_DWT_DWT_COMP0_IN          \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_COMP0_ADDR, HWIO_RPM_M3_DWT_DWT_COMP0_RMSK)
#define HWIO_RPM_M3_DWT_DWT_COMP0_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_COMP0_ADDR, m)
#define HWIO_RPM_M3_DWT_DWT_COMP0_OUT(v)      \
        out_dword(HWIO_RPM_M3_DWT_DWT_COMP0_ADDR,v)
#define HWIO_RPM_M3_DWT_DWT_COMP0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_DWT_DWT_COMP0_ADDR,m,v,HWIO_RPM_M3_DWT_DWT_COMP0_IN)
#define HWIO_RPM_M3_DWT_DWT_COMP0_COMP_BMSK                                     0xffffffff
#define HWIO_RPM_M3_DWT_DWT_COMP0_COMP_SHFT                                            0x0

#define HWIO_RPM_M3_DWT_DWT_MASK0_ADDR                                          (RPM_M3_PPB_INT_REG_BASE      + 0x00001024)
#define HWIO_RPM_M3_DWT_DWT_MASK0_RMSK                                                 0xf
#define HWIO_RPM_M3_DWT_DWT_MASK0_IN          \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_MASK0_ADDR, HWIO_RPM_M3_DWT_DWT_MASK0_RMSK)
#define HWIO_RPM_M3_DWT_DWT_MASK0_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_MASK0_ADDR, m)
#define HWIO_RPM_M3_DWT_DWT_MASK0_OUT(v)      \
        out_dword(HWIO_RPM_M3_DWT_DWT_MASK0_ADDR,v)
#define HWIO_RPM_M3_DWT_DWT_MASK0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_DWT_DWT_MASK0_ADDR,m,v,HWIO_RPM_M3_DWT_DWT_MASK0_IN)
#define HWIO_RPM_M3_DWT_DWT_MASK0_MASK_BMSK                                            0xf
#define HWIO_RPM_M3_DWT_DWT_MASK0_MASK_SHFT                                            0x0

#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_ADDR                                      (RPM_M3_PPB_INT_REG_BASE      + 0x00001028)
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_RMSK                                       0x10fff2f
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_IN          \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_FUNCTION0_ADDR, HWIO_RPM_M3_DWT_DWT_FUNCTION0_RMSK)
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_FUNCTION0_ADDR, m)
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_OUT(v)      \
        out_dword(HWIO_RPM_M3_DWT_DWT_FUNCTION0_ADDR,v)
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_DWT_DWT_FUNCTION0_ADDR,m,v,HWIO_RPM_M3_DWT_DWT_FUNCTION0_IN)
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_MATCHED_BMSK                               0x1000000
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_MATCHED_SHFT                                    0x18
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_DATAVADDR1_BMSK                              0xf0000
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_DATAVADDR1_SHFT                                 0x10
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_DATAVADDR0_BMSK                               0xf000
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_DATAVADDR0_SHFT                                  0xc
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_DATAVSIZE_BMSK                                 0xc00
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_DATAVSIZE_SHFT                                   0xa
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_DATAVSIZE_ENUM_0B00_FVAL                         0x0
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_DATAVSIZE_ENUM_0B01_FVAL                         0x1
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_DATAVSIZE_ENUM_0B10_FVAL                         0x2
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_DATAVSIZE_ENUM_0B11_FVAL                         0x3
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_LNK1ENA_BMSK                                   0x200
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_LNK1ENA_SHFT                                     0x9
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_LNK1ENA_ENUM_0B0_FVAL                            0x0
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_LNK1ENA_ENUM_0B1_FVAL                            0x1
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_DATAVMATCH_BMSK                                0x100
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_DATAVMATCH_SHFT                                  0x8
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_EMITRANGE_BMSK                                  0x20
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_EMITRANGE_SHFT                                   0x5
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_FUNCTION_BMSK                                    0xf
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_FUNCTION_SHFT                                    0x0
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_FUNCTION_ENUM_0B0000_FVAL                        0x0
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_FUNCTION_ENUM_0B0001_FVAL                        0x1
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_FUNCTION_ENUM_0B0010_FVAL                        0x2
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_FUNCTION_ENUM_0B0011_FVAL                        0x3
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_FUNCTION_ENUM_0B0100_FVAL                        0x4
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_FUNCTION_ENUM_0B0101_FVAL                        0x5
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_FUNCTION_ENUM_0B0110_FVAL                        0x6
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_FUNCTION_ENUM_0B0111_FVAL                        0x7
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_FUNCTION_ENUM_0B1000_FVAL                        0x8
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_FUNCTION_ENUM_0B1001_FVAL                        0x9
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_FUNCTION_ENUM_0B1010_FVAL                        0xa
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_FUNCTION_ENUM_0B1011_FVAL                        0xb
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_FUNCTION_ENUM_0B1100_FVAL                        0xc
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_FUNCTION_ENUM_0B1101_FVAL                        0xd
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_FUNCTION_ENUM_0B1110_FVAL                        0xe
#define HWIO_RPM_M3_DWT_DWT_FUNCTION0_FUNCTION_ENUM_0B1111_FVAL                        0xf

#define HWIO_RPM_M3_DWT_DWT_COMP1_ADDR                                          (RPM_M3_PPB_INT_REG_BASE      + 0x00001030)
#define HWIO_RPM_M3_DWT_DWT_COMP1_RMSK                                          0xffffffff
#define HWIO_RPM_M3_DWT_DWT_COMP1_IN          \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_COMP1_ADDR, HWIO_RPM_M3_DWT_DWT_COMP1_RMSK)
#define HWIO_RPM_M3_DWT_DWT_COMP1_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_COMP1_ADDR, m)
#define HWIO_RPM_M3_DWT_DWT_COMP1_OUT(v)      \
        out_dword(HWIO_RPM_M3_DWT_DWT_COMP1_ADDR,v)
#define HWIO_RPM_M3_DWT_DWT_COMP1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_DWT_DWT_COMP1_ADDR,m,v,HWIO_RPM_M3_DWT_DWT_COMP1_IN)
#define HWIO_RPM_M3_DWT_DWT_COMP1_COMP_BMSK                                     0xffffffff
#define HWIO_RPM_M3_DWT_DWT_COMP1_COMP_SHFT                                            0x0

#define HWIO_RPM_M3_DWT_DWT_MASK1_ADDR                                          (RPM_M3_PPB_INT_REG_BASE      + 0x00001034)
#define HWIO_RPM_M3_DWT_DWT_MASK1_RMSK                                                 0xf
#define HWIO_RPM_M3_DWT_DWT_MASK1_IN          \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_MASK1_ADDR, HWIO_RPM_M3_DWT_DWT_MASK1_RMSK)
#define HWIO_RPM_M3_DWT_DWT_MASK1_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_MASK1_ADDR, m)
#define HWIO_RPM_M3_DWT_DWT_MASK1_OUT(v)      \
        out_dword(HWIO_RPM_M3_DWT_DWT_MASK1_ADDR,v)
#define HWIO_RPM_M3_DWT_DWT_MASK1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_DWT_DWT_MASK1_ADDR,m,v,HWIO_RPM_M3_DWT_DWT_MASK1_IN)
#define HWIO_RPM_M3_DWT_DWT_MASK1_MASK_BMSK                                            0xf
#define HWIO_RPM_M3_DWT_DWT_MASK1_MASK_SHFT                                            0x0

#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_ADDR                                      (RPM_M3_PPB_INT_REG_BASE      + 0x00001038)
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_RMSK                                       0x10fffaf
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_IN          \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_FUNCTION1_ADDR, HWIO_RPM_M3_DWT_DWT_FUNCTION1_RMSK)
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_FUNCTION1_ADDR, m)
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_OUT(v)      \
        out_dword(HWIO_RPM_M3_DWT_DWT_FUNCTION1_ADDR,v)
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_DWT_DWT_FUNCTION1_ADDR,m,v,HWIO_RPM_M3_DWT_DWT_FUNCTION1_IN)
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_MATCHED_BMSK                               0x1000000
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_MATCHED_SHFT                                    0x18
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_DATAVADDR1_BMSK                              0xf0000
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_DATAVADDR1_SHFT                                 0x10
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_DATAVADDR0_BMSK                               0xf000
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_DATAVADDR0_SHFT                                  0xc
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_DATAVSIZE_BMSK                                 0xc00
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_DATAVSIZE_SHFT                                   0xa
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_DATAVSIZE_ENUM_0B00_FVAL                         0x0
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_DATAVSIZE_ENUM_0B01_FVAL                         0x1
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_DATAVSIZE_ENUM_0B10_FVAL                         0x2
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_DATAVSIZE_ENUM_0B11_FVAL                         0x3
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_LNK1ENA_BMSK                                   0x200
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_LNK1ENA_SHFT                                     0x9
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_LNK1ENA_ENUM_0B0_FVAL                            0x0
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_LNK1ENA_ENUM_0B1_FVAL                            0x1
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_DATAVMATCH_BMSK                                0x100
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_DATAVMATCH_SHFT                                  0x8
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_CYCMATCH_BMSK                                   0x80
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_CYCMATCH_SHFT                                    0x7
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_EMITRANGE_BMSK                                  0x20
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_EMITRANGE_SHFT                                   0x5
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_FUNCTION_BMSK                                    0xf
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_FUNCTION_SHFT                                    0x0
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_FUNCTION_ENUM_0B0000_FVAL                        0x0
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_FUNCTION_ENUM_0B0001_FVAL                        0x1
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_FUNCTION_ENUM_0B0010_FVAL                        0x2
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_FUNCTION_ENUM_0B0011_FVAL                        0x3
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_FUNCTION_ENUM_0B0100_FVAL                        0x4
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_FUNCTION_ENUM_0B0101_FVAL                        0x5
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_FUNCTION_ENUM_0B0110_FVAL                        0x6
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_FUNCTION_ENUM_0B0111_FVAL                        0x7
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_FUNCTION_ENUM_0B1000_FVAL                        0x8
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_FUNCTION_ENUM_0B1001_FVAL                        0x9
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_FUNCTION_ENUM_0B1010_FVAL                        0xa
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_FUNCTION_ENUM_0B1011_FVAL                        0xb
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_FUNCTION_ENUM_0B1100_FVAL                        0xc
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_FUNCTION_ENUM_0B1101_FVAL                        0xd
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_FUNCTION_ENUM_0B1110_FVAL                        0xe
#define HWIO_RPM_M3_DWT_DWT_FUNCTION1_FUNCTION_ENUM_0B1111_FVAL                        0xf

#define HWIO_RPM_M3_DWT_DWT_COMP2_ADDR                                          (RPM_M3_PPB_INT_REG_BASE      + 0x00001040)
#define HWIO_RPM_M3_DWT_DWT_COMP2_RMSK                                          0xffffffff
#define HWIO_RPM_M3_DWT_DWT_COMP2_IN          \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_COMP2_ADDR, HWIO_RPM_M3_DWT_DWT_COMP2_RMSK)
#define HWIO_RPM_M3_DWT_DWT_COMP2_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_COMP2_ADDR, m)
#define HWIO_RPM_M3_DWT_DWT_COMP2_OUT(v)      \
        out_dword(HWIO_RPM_M3_DWT_DWT_COMP2_ADDR,v)
#define HWIO_RPM_M3_DWT_DWT_COMP2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_DWT_DWT_COMP2_ADDR,m,v,HWIO_RPM_M3_DWT_DWT_COMP2_IN)
#define HWIO_RPM_M3_DWT_DWT_COMP2_COMP_BMSK                                     0xffffffff
#define HWIO_RPM_M3_DWT_DWT_COMP2_COMP_SHFT                                            0x0

#define HWIO_RPM_M3_DWT_DWT_MASK2_ADDR                                          (RPM_M3_PPB_INT_REG_BASE      + 0x00001044)
#define HWIO_RPM_M3_DWT_DWT_MASK2_RMSK                                                 0xf
#define HWIO_RPM_M3_DWT_DWT_MASK2_IN          \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_MASK2_ADDR, HWIO_RPM_M3_DWT_DWT_MASK2_RMSK)
#define HWIO_RPM_M3_DWT_DWT_MASK2_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_MASK2_ADDR, m)
#define HWIO_RPM_M3_DWT_DWT_MASK2_OUT(v)      \
        out_dword(HWIO_RPM_M3_DWT_DWT_MASK2_ADDR,v)
#define HWIO_RPM_M3_DWT_DWT_MASK2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_DWT_DWT_MASK2_ADDR,m,v,HWIO_RPM_M3_DWT_DWT_MASK2_IN)
#define HWIO_RPM_M3_DWT_DWT_MASK2_MASK_BMSK                                            0xf
#define HWIO_RPM_M3_DWT_DWT_MASK2_MASK_SHFT                                            0x0

#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_ADDR                                      (RPM_M3_PPB_INT_REG_BASE      + 0x00001048)
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_RMSK                                       0x10fff2f
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_IN          \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_FUNCTION2_ADDR, HWIO_RPM_M3_DWT_DWT_FUNCTION2_RMSK)
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_FUNCTION2_ADDR, m)
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_OUT(v)      \
        out_dword(HWIO_RPM_M3_DWT_DWT_FUNCTION2_ADDR,v)
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_DWT_DWT_FUNCTION2_ADDR,m,v,HWIO_RPM_M3_DWT_DWT_FUNCTION2_IN)
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_MATCHED_BMSK                               0x1000000
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_MATCHED_SHFT                                    0x18
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_DATAVADDR1_BMSK                              0xf0000
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_DATAVADDR1_SHFT                                 0x10
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_DATAVADDR0_BMSK                               0xf000
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_DATAVADDR0_SHFT                                  0xc
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_DATAVSIZE_BMSK                                 0xc00
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_DATAVSIZE_SHFT                                   0xa
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_DATAVSIZE_ENUM_0B00_FVAL                         0x0
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_DATAVSIZE_ENUM_0B01_FVAL                         0x1
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_DATAVSIZE_ENUM_0B10_FVAL                         0x2
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_DATAVSIZE_ENUM_0B11_FVAL                         0x3
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_LNK1ENA_BMSK                                   0x200
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_LNK1ENA_SHFT                                     0x9
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_LNK1ENA_ENUM_0B0_FVAL                            0x0
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_LNK1ENA_ENUM_0B1_FVAL                            0x1
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_DATAVMATCH_BMSK                                0x100
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_DATAVMATCH_SHFT                                  0x8
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_EMITRANGE_BMSK                                  0x20
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_EMITRANGE_SHFT                                   0x5
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_FUNCTION_BMSK                                    0xf
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_FUNCTION_SHFT                                    0x0
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_FUNCTION_ENUM_0B0000_FVAL                        0x0
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_FUNCTION_ENUM_0B0001_FVAL                        0x1
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_FUNCTION_ENUM_0B0010_FVAL                        0x2
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_FUNCTION_ENUM_0B0011_FVAL                        0x3
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_FUNCTION_ENUM_0B0100_FVAL                        0x4
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_FUNCTION_ENUM_0B0101_FVAL                        0x5
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_FUNCTION_ENUM_0B0110_FVAL                        0x6
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_FUNCTION_ENUM_0B0111_FVAL                        0x7
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_FUNCTION_ENUM_0B1000_FVAL                        0x8
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_FUNCTION_ENUM_0B1001_FVAL                        0x9
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_FUNCTION_ENUM_0B1010_FVAL                        0xa
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_FUNCTION_ENUM_0B1011_FVAL                        0xb
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_FUNCTION_ENUM_0B1100_FVAL                        0xc
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_FUNCTION_ENUM_0B1101_FVAL                        0xd
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_FUNCTION_ENUM_0B1110_FVAL                        0xe
#define HWIO_RPM_M3_DWT_DWT_FUNCTION2_FUNCTION_ENUM_0B1111_FVAL                        0xf

#define HWIO_RPM_M3_DWT_DWT_COMP3_ADDR                                          (RPM_M3_PPB_INT_REG_BASE      + 0x00001050)
#define HWIO_RPM_M3_DWT_DWT_COMP3_RMSK                                          0xffffffff
#define HWIO_RPM_M3_DWT_DWT_COMP3_IN          \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_COMP3_ADDR, HWIO_RPM_M3_DWT_DWT_COMP3_RMSK)
#define HWIO_RPM_M3_DWT_DWT_COMP3_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_COMP3_ADDR, m)
#define HWIO_RPM_M3_DWT_DWT_COMP3_OUT(v)      \
        out_dword(HWIO_RPM_M3_DWT_DWT_COMP3_ADDR,v)
#define HWIO_RPM_M3_DWT_DWT_COMP3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_DWT_DWT_COMP3_ADDR,m,v,HWIO_RPM_M3_DWT_DWT_COMP3_IN)
#define HWIO_RPM_M3_DWT_DWT_COMP3_COMP_BMSK                                     0xffffffff
#define HWIO_RPM_M3_DWT_DWT_COMP3_COMP_SHFT                                            0x0

#define HWIO_RPM_M3_DWT_DWT_MASK3_ADDR                                          (RPM_M3_PPB_INT_REG_BASE      + 0x00001054)
#define HWIO_RPM_M3_DWT_DWT_MASK3_RMSK                                                 0xf
#define HWIO_RPM_M3_DWT_DWT_MASK3_IN          \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_MASK3_ADDR, HWIO_RPM_M3_DWT_DWT_MASK3_RMSK)
#define HWIO_RPM_M3_DWT_DWT_MASK3_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_MASK3_ADDR, m)
#define HWIO_RPM_M3_DWT_DWT_MASK3_OUT(v)      \
        out_dword(HWIO_RPM_M3_DWT_DWT_MASK3_ADDR,v)
#define HWIO_RPM_M3_DWT_DWT_MASK3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_DWT_DWT_MASK3_ADDR,m,v,HWIO_RPM_M3_DWT_DWT_MASK3_IN)
#define HWIO_RPM_M3_DWT_DWT_MASK3_MASK_BMSK                                            0xf
#define HWIO_RPM_M3_DWT_DWT_MASK3_MASK_SHFT                                            0x0

#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_ADDR                                      (RPM_M3_PPB_INT_REG_BASE      + 0x00001058)
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_RMSK                                       0x10fff2f
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_IN          \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_FUNCTION3_ADDR, HWIO_RPM_M3_DWT_DWT_FUNCTION3_RMSK)
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_DWT_DWT_FUNCTION3_ADDR, m)
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_OUT(v)      \
        out_dword(HWIO_RPM_M3_DWT_DWT_FUNCTION3_ADDR,v)
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_DWT_DWT_FUNCTION3_ADDR,m,v,HWIO_RPM_M3_DWT_DWT_FUNCTION3_IN)
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_MATCHED_BMSK                               0x1000000
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_MATCHED_SHFT                                    0x18
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_DATAVADDR1_BMSK                              0xf0000
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_DATAVADDR1_SHFT                                 0x10
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_DATAVADDR0_BMSK                               0xf000
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_DATAVADDR0_SHFT                                  0xc
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_DATAVSIZE_BMSK                                 0xc00
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_DATAVSIZE_SHFT                                   0xa
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_DATAVSIZE_ENUM_0B00_FVAL                         0x0
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_DATAVSIZE_ENUM_0B01_FVAL                         0x1
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_DATAVSIZE_ENUM_0B10_FVAL                         0x2
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_DATAVSIZE_ENUM_0B11_FVAL                         0x3
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_LNK1ENA_BMSK                                   0x200
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_LNK1ENA_SHFT                                     0x9
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_LNK1ENA_ENUM_0B0_FVAL                            0x0
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_LNK1ENA_ENUM_0B1_FVAL                            0x1
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_DATAVMATCH_BMSK                                0x100
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_DATAVMATCH_SHFT                                  0x8
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_EMITRANGE_BMSK                                  0x20
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_EMITRANGE_SHFT                                   0x5
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_FUNCTION_BMSK                                    0xf
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_FUNCTION_SHFT                                    0x0
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_FUNCTION_ENUM_0B0000_FVAL                        0x0
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_FUNCTION_ENUM_0B0001_FVAL                        0x1
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_FUNCTION_ENUM_0B0010_FVAL                        0x2
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_FUNCTION_ENUM_0B0011_FVAL                        0x3
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_FUNCTION_ENUM_0B0100_FVAL                        0x4
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_FUNCTION_ENUM_0B0101_FVAL                        0x5
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_FUNCTION_ENUM_0B0110_FVAL                        0x6
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_FUNCTION_ENUM_0B0111_FVAL                        0x7
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_FUNCTION_ENUM_0B1000_FVAL                        0x8
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_FUNCTION_ENUM_0B1001_FVAL                        0x9
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_FUNCTION_ENUM_0B1010_FVAL                        0xa
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_FUNCTION_ENUM_0B1011_FVAL                        0xb
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_FUNCTION_ENUM_0B1100_FVAL                        0xc
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_FUNCTION_ENUM_0B1101_FVAL                        0xd
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_FUNCTION_ENUM_0B1110_FVAL                        0xe
#define HWIO_RPM_M3_DWT_DWT_FUNCTION3_FUNCTION_ENUM_0B1111_FVAL                        0xf

#define HWIO_RPM_M3_DWT_PID4_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x00001fd0)
#define HWIO_RPM_M3_DWT_PID4_RMSK                                               0xffffffff
#define HWIO_RPM_M3_DWT_PID4_IN          \
        in_dword_masked(HWIO_RPM_M3_DWT_PID4_ADDR, HWIO_RPM_M3_DWT_PID4_RMSK)
#define HWIO_RPM_M3_DWT_PID4_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_DWT_PID4_ADDR, m)
#define HWIO_RPM_M3_DWT_PID4_DWT_PID4_BMSK                                      0xffffffff
#define HWIO_RPM_M3_DWT_PID4_DWT_PID4_SHFT                                             0x0

#define HWIO_RPM_M3_DWT_PID5_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x00001fd4)
#define HWIO_RPM_M3_DWT_PID5_RMSK                                               0xffffffff
#define HWIO_RPM_M3_DWT_PID5_IN          \
        in_dword_masked(HWIO_RPM_M3_DWT_PID5_ADDR, HWIO_RPM_M3_DWT_PID5_RMSK)
#define HWIO_RPM_M3_DWT_PID5_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_DWT_PID5_ADDR, m)
#define HWIO_RPM_M3_DWT_PID5_DWT_PID5_BMSK                                      0xffffffff
#define HWIO_RPM_M3_DWT_PID5_DWT_PID5_SHFT                                             0x0

#define HWIO_RPM_M3_DWT_PID6_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x00001fd8)
#define HWIO_RPM_M3_DWT_PID6_RMSK                                               0xffffffff
#define HWIO_RPM_M3_DWT_PID6_IN          \
        in_dword_masked(HWIO_RPM_M3_DWT_PID6_ADDR, HWIO_RPM_M3_DWT_PID6_RMSK)
#define HWIO_RPM_M3_DWT_PID6_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_DWT_PID6_ADDR, m)
#define HWIO_RPM_M3_DWT_PID6_DWT_PID6_BMSK                                      0xffffffff
#define HWIO_RPM_M3_DWT_PID6_DWT_PID6_SHFT                                             0x0

#define HWIO_RPM_M3_DWT_PID7_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x00001fdc)
#define HWIO_RPM_M3_DWT_PID7_RMSK                                               0xffffffff
#define HWIO_RPM_M3_DWT_PID7_IN          \
        in_dword_masked(HWIO_RPM_M3_DWT_PID7_ADDR, HWIO_RPM_M3_DWT_PID7_RMSK)
#define HWIO_RPM_M3_DWT_PID7_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_DWT_PID7_ADDR, m)
#define HWIO_RPM_M3_DWT_PID7_DWT_PID7_BMSK                                      0xffffffff
#define HWIO_RPM_M3_DWT_PID7_DWT_PID7_SHFT                                             0x0

#define HWIO_RPM_M3_DWT_PID0_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x00001fe0)
#define HWIO_RPM_M3_DWT_PID0_RMSK                                               0xffffffff
#define HWIO_RPM_M3_DWT_PID0_IN          \
        in_dword_masked(HWIO_RPM_M3_DWT_PID0_ADDR, HWIO_RPM_M3_DWT_PID0_RMSK)
#define HWIO_RPM_M3_DWT_PID0_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_DWT_PID0_ADDR, m)
#define HWIO_RPM_M3_DWT_PID0_DWT_PID0_BMSK                                      0xffffffff
#define HWIO_RPM_M3_DWT_PID0_DWT_PID0_SHFT                                             0x0

#define HWIO_RPM_M3_DWT_PID1_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x00001fe4)
#define HWIO_RPM_M3_DWT_PID1_RMSK                                               0xffffffff
#define HWIO_RPM_M3_DWT_PID1_IN          \
        in_dword_masked(HWIO_RPM_M3_DWT_PID1_ADDR, HWIO_RPM_M3_DWT_PID1_RMSK)
#define HWIO_RPM_M3_DWT_PID1_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_DWT_PID1_ADDR, m)
#define HWIO_RPM_M3_DWT_PID1_DWT_PID1_BMSK                                      0xffffffff
#define HWIO_RPM_M3_DWT_PID1_DWT_PID1_SHFT                                             0x0

#define HWIO_RPM_M3_DWT_PID2_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x00001fe8)
#define HWIO_RPM_M3_DWT_PID2_RMSK                                               0xffffffff
#define HWIO_RPM_M3_DWT_PID2_IN          \
        in_dword_masked(HWIO_RPM_M3_DWT_PID2_ADDR, HWIO_RPM_M3_DWT_PID2_RMSK)
#define HWIO_RPM_M3_DWT_PID2_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_DWT_PID2_ADDR, m)
#define HWIO_RPM_M3_DWT_PID2_DWT_PID2_BMSK                                      0xffffffff
#define HWIO_RPM_M3_DWT_PID2_DWT_PID2_SHFT                                             0x0

#define HWIO_RPM_M3_DWT_PID3_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x00001fec)
#define HWIO_RPM_M3_DWT_PID3_RMSK                                               0xffffffff
#define HWIO_RPM_M3_DWT_PID3_IN          \
        in_dword_masked(HWIO_RPM_M3_DWT_PID3_ADDR, HWIO_RPM_M3_DWT_PID3_RMSK)
#define HWIO_RPM_M3_DWT_PID3_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_DWT_PID3_ADDR, m)
#define HWIO_RPM_M3_DWT_PID3_DWT_PID3_BMSK                                      0xffffffff
#define HWIO_RPM_M3_DWT_PID3_DWT_PID3_SHFT                                             0x0

#define HWIO_RPM_M3_DWT_CID0_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x00001ff0)
#define HWIO_RPM_M3_DWT_CID0_RMSK                                               0xffffffff
#define HWIO_RPM_M3_DWT_CID0_IN          \
        in_dword_masked(HWIO_RPM_M3_DWT_CID0_ADDR, HWIO_RPM_M3_DWT_CID0_RMSK)
#define HWIO_RPM_M3_DWT_CID0_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_DWT_CID0_ADDR, m)
#define HWIO_RPM_M3_DWT_CID0_DWT_CID0_BMSK                                      0xffffffff
#define HWIO_RPM_M3_DWT_CID0_DWT_CID0_SHFT                                             0x0

#define HWIO_RPM_M3_DWT_CID1_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x00001ff4)
#define HWIO_RPM_M3_DWT_CID1_RMSK                                               0xffffffff
#define HWIO_RPM_M3_DWT_CID1_IN          \
        in_dword_masked(HWIO_RPM_M3_DWT_CID1_ADDR, HWIO_RPM_M3_DWT_CID1_RMSK)
#define HWIO_RPM_M3_DWT_CID1_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_DWT_CID1_ADDR, m)
#define HWIO_RPM_M3_DWT_CID1_DWT_CID1_BMSK                                      0xffffffff
#define HWIO_RPM_M3_DWT_CID1_DWT_CID1_SHFT                                             0x0

#define HWIO_RPM_M3_DWT_CID2_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x00001ff8)
#define HWIO_RPM_M3_DWT_CID2_RMSK                                               0xffffffff
#define HWIO_RPM_M3_DWT_CID2_IN          \
        in_dword_masked(HWIO_RPM_M3_DWT_CID2_ADDR, HWIO_RPM_M3_DWT_CID2_RMSK)
#define HWIO_RPM_M3_DWT_CID2_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_DWT_CID2_ADDR, m)
#define HWIO_RPM_M3_DWT_CID2_DWT_CID2_BMSK                                      0xffffffff
#define HWIO_RPM_M3_DWT_CID2_DWT_CID2_SHFT                                             0x0

#define HWIO_RPM_M3_DWT_CID3_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x00001ffc)
#define HWIO_RPM_M3_DWT_CID3_RMSK                                               0xffffffff
#define HWIO_RPM_M3_DWT_CID3_IN          \
        in_dword_masked(HWIO_RPM_M3_DWT_CID3_ADDR, HWIO_RPM_M3_DWT_CID3_RMSK)
#define HWIO_RPM_M3_DWT_CID3_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_DWT_CID3_ADDR, m)
#define HWIO_RPM_M3_DWT_CID3_DWT_CID3_BMSK                                      0xffffffff
#define HWIO_RPM_M3_DWT_CID3_DWT_CID3_SHFT                                             0x0

#define HWIO_RPM_M3_FPB_FP_CTRL_ADDR                                            (RPM_M3_PPB_INT_REG_BASE      + 0x00002000)
#define HWIO_RPM_M3_FPB_FP_CTRL_RMSK                                                0x3ff3
#define HWIO_RPM_M3_FPB_FP_CTRL_IN          \
        in_dword_masked(HWIO_RPM_M3_FPB_FP_CTRL_ADDR, HWIO_RPM_M3_FPB_FP_CTRL_RMSK)
#define HWIO_RPM_M3_FPB_FP_CTRL_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_FPB_FP_CTRL_ADDR, m)
#define HWIO_RPM_M3_FPB_FP_CTRL_OUT(v)      \
        out_dword(HWIO_RPM_M3_FPB_FP_CTRL_ADDR,v)
#define HWIO_RPM_M3_FPB_FP_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_FPB_FP_CTRL_ADDR,m,v,HWIO_RPM_M3_FPB_FP_CTRL_IN)
#define HWIO_RPM_M3_FPB_FP_CTRL_NUM_CODE2_BMSK                                      0x3000
#define HWIO_RPM_M3_FPB_FP_CTRL_NUM_CODE2_SHFT                                         0xc
#define HWIO_RPM_M3_FPB_FP_CTRL_NUM_LIT_BMSK                                         0xf00
#define HWIO_RPM_M3_FPB_FP_CTRL_NUM_LIT_SHFT                                           0x8
#define HWIO_RPM_M3_FPB_FP_CTRL_NUM_LIT_ENUM_0B0000_FVAL                               0x0
#define HWIO_RPM_M3_FPB_FP_CTRL_NUM_LIT_ENUM_0B0010_FVAL                               0x2
#define HWIO_RPM_M3_FPB_FP_CTRL_NUM_CODE1_BMSK                                        0xf0
#define HWIO_RPM_M3_FPB_FP_CTRL_NUM_CODE1_SHFT                                         0x4
#define HWIO_RPM_M3_FPB_FP_CTRL_NUM_CODE1_ENUM_0B0000_FVAL                             0x0
#define HWIO_RPM_M3_FPB_FP_CTRL_NUM_CODE1_ENUM_0B0010_FVAL                             0x2
#define HWIO_RPM_M3_FPB_FP_CTRL_NUM_CODE1_ENUM_0B0110_FVAL                             0x6
#define HWIO_RPM_M3_FPB_FP_CTRL_KEY_BMSK                                               0x2
#define HWIO_RPM_M3_FPB_FP_CTRL_KEY_SHFT                                               0x1
#define HWIO_RPM_M3_FPB_FP_CTRL_ENABLE_BMSK                                            0x1
#define HWIO_RPM_M3_FPB_FP_CTRL_ENABLE_SHFT                                            0x0
#define HWIO_RPM_M3_FPB_FP_CTRL_ENABLE_ENUM_0B0_FVAL                                   0x0
#define HWIO_RPM_M3_FPB_FP_CTRL_ENABLE_ENUM_0B1_FVAL                                   0x1

#define HWIO_RPM_M3_FPB_FP_REMAP_ADDR                                           (RPM_M3_PPB_INT_REG_BASE      + 0x00002004)
#define HWIO_RPM_M3_FPB_FP_REMAP_RMSK                                           0x1fffffe0
#define HWIO_RPM_M3_FPB_FP_REMAP_IN          \
        in_dword_masked(HWIO_RPM_M3_FPB_FP_REMAP_ADDR, HWIO_RPM_M3_FPB_FP_REMAP_RMSK)
#define HWIO_RPM_M3_FPB_FP_REMAP_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_FPB_FP_REMAP_ADDR, m)
#define HWIO_RPM_M3_FPB_FP_REMAP_OUT(v)      \
        out_dword(HWIO_RPM_M3_FPB_FP_REMAP_ADDR,v)
#define HWIO_RPM_M3_FPB_FP_REMAP_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_FPB_FP_REMAP_ADDR,m,v,HWIO_RPM_M3_FPB_FP_REMAP_IN)
#define HWIO_RPM_M3_FPB_FP_REMAP_REMAP_BMSK                                     0x1fffffe0
#define HWIO_RPM_M3_FPB_FP_REMAP_REMAP_SHFT                                            0x5

#define HWIO_RPM_M3_FPB_FP_COMP0_ADDR                                           (RPM_M3_PPB_INT_REG_BASE      + 0x00002008)
#define HWIO_RPM_M3_FPB_FP_COMP0_RMSK                                           0xdffffffd
#define HWIO_RPM_M3_FPB_FP_COMP0_IN          \
        in_dword_masked(HWIO_RPM_M3_FPB_FP_COMP0_ADDR, HWIO_RPM_M3_FPB_FP_COMP0_RMSK)
#define HWIO_RPM_M3_FPB_FP_COMP0_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_FPB_FP_COMP0_ADDR, m)
#define HWIO_RPM_M3_FPB_FP_COMP0_OUT(v)      \
        out_dword(HWIO_RPM_M3_FPB_FP_COMP0_ADDR,v)
#define HWIO_RPM_M3_FPB_FP_COMP0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_FPB_FP_COMP0_ADDR,m,v,HWIO_RPM_M3_FPB_FP_COMP0_IN)
#define HWIO_RPM_M3_FPB_FP_COMP0_REPLACE_BMSK                                   0xc0000000
#define HWIO_RPM_M3_FPB_FP_COMP0_REPLACE_SHFT                                         0x1e
#define HWIO_RPM_M3_FPB_FP_COMP0_REPLACE_ENUM_0B00_FVAL                                0x0
#define HWIO_RPM_M3_FPB_FP_COMP0_REPLACE_ENUM_0B01_FVAL                                0x1
#define HWIO_RPM_M3_FPB_FP_COMP0_REPLACE_ENUM_0B10_FVAL                                0x2
#define HWIO_RPM_M3_FPB_FP_COMP0_REPLACE_ENUM_0B11_FVAL                                0x3
#define HWIO_RPM_M3_FPB_FP_COMP0_COMP_BMSK                                      0x1ffffffc
#define HWIO_RPM_M3_FPB_FP_COMP0_COMP_SHFT                                             0x2
#define HWIO_RPM_M3_FPB_FP_COMP0_ENABLE_BMSK                                           0x1
#define HWIO_RPM_M3_FPB_FP_COMP0_ENABLE_SHFT                                           0x0
#define HWIO_RPM_M3_FPB_FP_COMP0_ENABLE_ENUM_0B0_FVAL                                  0x0
#define HWIO_RPM_M3_FPB_FP_COMP0_ENABLE_ENUM_0B1_FVAL                                  0x1

#define HWIO_RPM_M3_FPB_FP_COMP1_ADDR                                           (RPM_M3_PPB_INT_REG_BASE      + 0x0000200c)
#define HWIO_RPM_M3_FPB_FP_COMP1_RMSK                                           0xdffffffd
#define HWIO_RPM_M3_FPB_FP_COMP1_IN          \
        in_dword_masked(HWIO_RPM_M3_FPB_FP_COMP1_ADDR, HWIO_RPM_M3_FPB_FP_COMP1_RMSK)
#define HWIO_RPM_M3_FPB_FP_COMP1_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_FPB_FP_COMP1_ADDR, m)
#define HWIO_RPM_M3_FPB_FP_COMP1_OUT(v)      \
        out_dword(HWIO_RPM_M3_FPB_FP_COMP1_ADDR,v)
#define HWIO_RPM_M3_FPB_FP_COMP1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_FPB_FP_COMP1_ADDR,m,v,HWIO_RPM_M3_FPB_FP_COMP1_IN)
#define HWIO_RPM_M3_FPB_FP_COMP1_REPLACE_BMSK                                   0xc0000000
#define HWIO_RPM_M3_FPB_FP_COMP1_REPLACE_SHFT                                         0x1e
#define HWIO_RPM_M3_FPB_FP_COMP1_REPLACE_ENUM_0B00_FVAL                                0x0
#define HWIO_RPM_M3_FPB_FP_COMP1_REPLACE_ENUM_0B01_FVAL                                0x1
#define HWIO_RPM_M3_FPB_FP_COMP1_REPLACE_ENUM_0B10_FVAL                                0x2
#define HWIO_RPM_M3_FPB_FP_COMP1_REPLACE_ENUM_0B11_FVAL                                0x3
#define HWIO_RPM_M3_FPB_FP_COMP1_COMP_BMSK                                      0x1ffffffc
#define HWIO_RPM_M3_FPB_FP_COMP1_COMP_SHFT                                             0x2
#define HWIO_RPM_M3_FPB_FP_COMP1_ENABLE_BMSK                                           0x1
#define HWIO_RPM_M3_FPB_FP_COMP1_ENABLE_SHFT                                           0x0
#define HWIO_RPM_M3_FPB_FP_COMP1_ENABLE_ENUM_0B0_FVAL                                  0x0
#define HWIO_RPM_M3_FPB_FP_COMP1_ENABLE_ENUM_0B1_FVAL                                  0x1

#define HWIO_RPM_M3_FPB_FP_COMP2_ADDR                                           (RPM_M3_PPB_INT_REG_BASE      + 0x00002010)
#define HWIO_RPM_M3_FPB_FP_COMP2_RMSK                                           0xdffffffd
#define HWIO_RPM_M3_FPB_FP_COMP2_IN          \
        in_dword_masked(HWIO_RPM_M3_FPB_FP_COMP2_ADDR, HWIO_RPM_M3_FPB_FP_COMP2_RMSK)
#define HWIO_RPM_M3_FPB_FP_COMP2_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_FPB_FP_COMP2_ADDR, m)
#define HWIO_RPM_M3_FPB_FP_COMP2_OUT(v)      \
        out_dword(HWIO_RPM_M3_FPB_FP_COMP2_ADDR,v)
#define HWIO_RPM_M3_FPB_FP_COMP2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_FPB_FP_COMP2_ADDR,m,v,HWIO_RPM_M3_FPB_FP_COMP2_IN)
#define HWIO_RPM_M3_FPB_FP_COMP2_REPLACE_BMSK                                   0xc0000000
#define HWIO_RPM_M3_FPB_FP_COMP2_REPLACE_SHFT                                         0x1e
#define HWIO_RPM_M3_FPB_FP_COMP2_REPLACE_ENUM_0B00_FVAL                                0x0
#define HWIO_RPM_M3_FPB_FP_COMP2_REPLACE_ENUM_0B01_FVAL                                0x1
#define HWIO_RPM_M3_FPB_FP_COMP2_REPLACE_ENUM_0B10_FVAL                                0x2
#define HWIO_RPM_M3_FPB_FP_COMP2_REPLACE_ENUM_0B11_FVAL                                0x3
#define HWIO_RPM_M3_FPB_FP_COMP2_COMP_BMSK                                      0x1ffffffc
#define HWIO_RPM_M3_FPB_FP_COMP2_COMP_SHFT                                             0x2
#define HWIO_RPM_M3_FPB_FP_COMP2_ENABLE_BMSK                                           0x1
#define HWIO_RPM_M3_FPB_FP_COMP2_ENABLE_SHFT                                           0x0
#define HWIO_RPM_M3_FPB_FP_COMP2_ENABLE_ENUM_0B0_FVAL                                  0x0
#define HWIO_RPM_M3_FPB_FP_COMP2_ENABLE_ENUM_0B1_FVAL                                  0x1

#define HWIO_RPM_M3_FPB_FP_COMP3_ADDR                                           (RPM_M3_PPB_INT_REG_BASE      + 0x00002014)
#define HWIO_RPM_M3_FPB_FP_COMP3_RMSK                                           0xdffffffd
#define HWIO_RPM_M3_FPB_FP_COMP3_IN          \
        in_dword_masked(HWIO_RPM_M3_FPB_FP_COMP3_ADDR, HWIO_RPM_M3_FPB_FP_COMP3_RMSK)
#define HWIO_RPM_M3_FPB_FP_COMP3_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_FPB_FP_COMP3_ADDR, m)
#define HWIO_RPM_M3_FPB_FP_COMP3_OUT(v)      \
        out_dword(HWIO_RPM_M3_FPB_FP_COMP3_ADDR,v)
#define HWIO_RPM_M3_FPB_FP_COMP3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_FPB_FP_COMP3_ADDR,m,v,HWIO_RPM_M3_FPB_FP_COMP3_IN)
#define HWIO_RPM_M3_FPB_FP_COMP3_REPLACE_BMSK                                   0xc0000000
#define HWIO_RPM_M3_FPB_FP_COMP3_REPLACE_SHFT                                         0x1e
#define HWIO_RPM_M3_FPB_FP_COMP3_REPLACE_ENUM_0B00_FVAL                                0x0
#define HWIO_RPM_M3_FPB_FP_COMP3_REPLACE_ENUM_0B01_FVAL                                0x1
#define HWIO_RPM_M3_FPB_FP_COMP3_REPLACE_ENUM_0B10_FVAL                                0x2
#define HWIO_RPM_M3_FPB_FP_COMP3_REPLACE_ENUM_0B11_FVAL                                0x3
#define HWIO_RPM_M3_FPB_FP_COMP3_COMP_BMSK                                      0x1ffffffc
#define HWIO_RPM_M3_FPB_FP_COMP3_COMP_SHFT                                             0x2
#define HWIO_RPM_M3_FPB_FP_COMP3_ENABLE_BMSK                                           0x1
#define HWIO_RPM_M3_FPB_FP_COMP3_ENABLE_SHFT                                           0x0
#define HWIO_RPM_M3_FPB_FP_COMP3_ENABLE_ENUM_0B0_FVAL                                  0x0
#define HWIO_RPM_M3_FPB_FP_COMP3_ENABLE_ENUM_0B1_FVAL                                  0x1

#define HWIO_RPM_M3_FPB_FP_COMP4_ADDR                                           (RPM_M3_PPB_INT_REG_BASE      + 0x00002018)
#define HWIO_RPM_M3_FPB_FP_COMP4_RMSK                                           0xdffffffd
#define HWIO_RPM_M3_FPB_FP_COMP4_IN          \
        in_dword_masked(HWIO_RPM_M3_FPB_FP_COMP4_ADDR, HWIO_RPM_M3_FPB_FP_COMP4_RMSK)
#define HWIO_RPM_M3_FPB_FP_COMP4_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_FPB_FP_COMP4_ADDR, m)
#define HWIO_RPM_M3_FPB_FP_COMP4_OUT(v)      \
        out_dword(HWIO_RPM_M3_FPB_FP_COMP4_ADDR,v)
#define HWIO_RPM_M3_FPB_FP_COMP4_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_FPB_FP_COMP4_ADDR,m,v,HWIO_RPM_M3_FPB_FP_COMP4_IN)
#define HWIO_RPM_M3_FPB_FP_COMP4_REPLACE_BMSK                                   0xc0000000
#define HWIO_RPM_M3_FPB_FP_COMP4_REPLACE_SHFT                                         0x1e
#define HWIO_RPM_M3_FPB_FP_COMP4_REPLACE_ENUM_0B00_FVAL                                0x0
#define HWIO_RPM_M3_FPB_FP_COMP4_REPLACE_ENUM_0B01_FVAL                                0x1
#define HWIO_RPM_M3_FPB_FP_COMP4_REPLACE_ENUM_0B10_FVAL                                0x2
#define HWIO_RPM_M3_FPB_FP_COMP4_REPLACE_ENUM_0B11_FVAL                                0x3
#define HWIO_RPM_M3_FPB_FP_COMP4_COMP_BMSK                                      0x1ffffffc
#define HWIO_RPM_M3_FPB_FP_COMP4_COMP_SHFT                                             0x2
#define HWIO_RPM_M3_FPB_FP_COMP4_ENABLE_BMSK                                           0x1
#define HWIO_RPM_M3_FPB_FP_COMP4_ENABLE_SHFT                                           0x0
#define HWIO_RPM_M3_FPB_FP_COMP4_ENABLE_ENUM_0B0_FVAL                                  0x0
#define HWIO_RPM_M3_FPB_FP_COMP4_ENABLE_ENUM_0B1_FVAL                                  0x1

#define HWIO_RPM_M3_FPB_FP_COMP5_ADDR                                           (RPM_M3_PPB_INT_REG_BASE      + 0x0000201c)
#define HWIO_RPM_M3_FPB_FP_COMP5_RMSK                                           0xdffffffd
#define HWIO_RPM_M3_FPB_FP_COMP5_IN          \
        in_dword_masked(HWIO_RPM_M3_FPB_FP_COMP5_ADDR, HWIO_RPM_M3_FPB_FP_COMP5_RMSK)
#define HWIO_RPM_M3_FPB_FP_COMP5_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_FPB_FP_COMP5_ADDR, m)
#define HWIO_RPM_M3_FPB_FP_COMP5_OUT(v)      \
        out_dword(HWIO_RPM_M3_FPB_FP_COMP5_ADDR,v)
#define HWIO_RPM_M3_FPB_FP_COMP5_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_FPB_FP_COMP5_ADDR,m,v,HWIO_RPM_M3_FPB_FP_COMP5_IN)
#define HWIO_RPM_M3_FPB_FP_COMP5_REPLACE_BMSK                                   0xc0000000
#define HWIO_RPM_M3_FPB_FP_COMP5_REPLACE_SHFT                                         0x1e
#define HWIO_RPM_M3_FPB_FP_COMP5_REPLACE_ENUM_0B00_FVAL                                0x0
#define HWIO_RPM_M3_FPB_FP_COMP5_REPLACE_ENUM_0B01_FVAL                                0x1
#define HWIO_RPM_M3_FPB_FP_COMP5_REPLACE_ENUM_0B10_FVAL                                0x2
#define HWIO_RPM_M3_FPB_FP_COMP5_REPLACE_ENUM_0B11_FVAL                                0x3
#define HWIO_RPM_M3_FPB_FP_COMP5_COMP_BMSK                                      0x1ffffffc
#define HWIO_RPM_M3_FPB_FP_COMP5_COMP_SHFT                                             0x2
#define HWIO_RPM_M3_FPB_FP_COMP5_ENABLE_BMSK                                           0x1
#define HWIO_RPM_M3_FPB_FP_COMP5_ENABLE_SHFT                                           0x0
#define HWIO_RPM_M3_FPB_FP_COMP5_ENABLE_ENUM_0B0_FVAL                                  0x0
#define HWIO_RPM_M3_FPB_FP_COMP5_ENABLE_ENUM_0B1_FVAL                                  0x1

#define HWIO_RPM_M3_FPB_FP_COMP6_ADDR                                           (RPM_M3_PPB_INT_REG_BASE      + 0x00002020)
#define HWIO_RPM_M3_FPB_FP_COMP6_RMSK                                           0xdffffffd
#define HWIO_RPM_M3_FPB_FP_COMP6_IN          \
        in_dword_masked(HWIO_RPM_M3_FPB_FP_COMP6_ADDR, HWIO_RPM_M3_FPB_FP_COMP6_RMSK)
#define HWIO_RPM_M3_FPB_FP_COMP6_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_FPB_FP_COMP6_ADDR, m)
#define HWIO_RPM_M3_FPB_FP_COMP6_OUT(v)      \
        out_dword(HWIO_RPM_M3_FPB_FP_COMP6_ADDR,v)
#define HWIO_RPM_M3_FPB_FP_COMP6_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_FPB_FP_COMP6_ADDR,m,v,HWIO_RPM_M3_FPB_FP_COMP6_IN)
#define HWIO_RPM_M3_FPB_FP_COMP6_REPLACE_BMSK                                   0xc0000000
#define HWIO_RPM_M3_FPB_FP_COMP6_REPLACE_SHFT                                         0x1e
#define HWIO_RPM_M3_FPB_FP_COMP6_REPLACE_ENUM_0B00_FVAL                                0x0
#define HWIO_RPM_M3_FPB_FP_COMP6_REPLACE_ENUM_0B01_FVAL                                0x1
#define HWIO_RPM_M3_FPB_FP_COMP6_REPLACE_ENUM_0B10_FVAL                                0x2
#define HWIO_RPM_M3_FPB_FP_COMP6_REPLACE_ENUM_0B11_FVAL                                0x3
#define HWIO_RPM_M3_FPB_FP_COMP6_COMP_BMSK                                      0x1ffffffc
#define HWIO_RPM_M3_FPB_FP_COMP6_COMP_SHFT                                             0x2
#define HWIO_RPM_M3_FPB_FP_COMP6_ENABLE_BMSK                                           0x1
#define HWIO_RPM_M3_FPB_FP_COMP6_ENABLE_SHFT                                           0x0
#define HWIO_RPM_M3_FPB_FP_COMP6_ENABLE_ENUM_0B0_FVAL                                  0x0
#define HWIO_RPM_M3_FPB_FP_COMP6_ENABLE_ENUM_0B1_FVAL                                  0x1

#define HWIO_RPM_M3_FPB_FP_COMP7_ADDR                                           (RPM_M3_PPB_INT_REG_BASE      + 0x00002024)
#define HWIO_RPM_M3_FPB_FP_COMP7_RMSK                                           0xdffffffd
#define HWIO_RPM_M3_FPB_FP_COMP7_IN          \
        in_dword_masked(HWIO_RPM_M3_FPB_FP_COMP7_ADDR, HWIO_RPM_M3_FPB_FP_COMP7_RMSK)
#define HWIO_RPM_M3_FPB_FP_COMP7_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_FPB_FP_COMP7_ADDR, m)
#define HWIO_RPM_M3_FPB_FP_COMP7_OUT(v)      \
        out_dword(HWIO_RPM_M3_FPB_FP_COMP7_ADDR,v)
#define HWIO_RPM_M3_FPB_FP_COMP7_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_FPB_FP_COMP7_ADDR,m,v,HWIO_RPM_M3_FPB_FP_COMP7_IN)
#define HWIO_RPM_M3_FPB_FP_COMP7_REPLACE_BMSK                                   0xc0000000
#define HWIO_RPM_M3_FPB_FP_COMP7_REPLACE_SHFT                                         0x1e
#define HWIO_RPM_M3_FPB_FP_COMP7_REPLACE_ENUM_0B00_FVAL                                0x0
#define HWIO_RPM_M3_FPB_FP_COMP7_REPLACE_ENUM_0B01_FVAL                                0x1
#define HWIO_RPM_M3_FPB_FP_COMP7_REPLACE_ENUM_0B10_FVAL                                0x2
#define HWIO_RPM_M3_FPB_FP_COMP7_REPLACE_ENUM_0B11_FVAL                                0x3
#define HWIO_RPM_M3_FPB_FP_COMP7_COMP_BMSK                                      0x1ffffffc
#define HWIO_RPM_M3_FPB_FP_COMP7_COMP_SHFT                                             0x2
#define HWIO_RPM_M3_FPB_FP_COMP7_ENABLE_BMSK                                           0x1
#define HWIO_RPM_M3_FPB_FP_COMP7_ENABLE_SHFT                                           0x0
#define HWIO_RPM_M3_FPB_FP_COMP7_ENABLE_ENUM_0B0_FVAL                                  0x0
#define HWIO_RPM_M3_FPB_FP_COMP7_ENABLE_ENUM_0B1_FVAL                                  0x1

#define HWIO_RPM_M3_FPB_PID4_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x00002fd0)
#define HWIO_RPM_M3_FPB_PID4_RMSK                                               0xffffffff
#define HWIO_RPM_M3_FPB_PID4_IN          \
        in_dword_masked(HWIO_RPM_M3_FPB_PID4_ADDR, HWIO_RPM_M3_FPB_PID4_RMSK)
#define HWIO_RPM_M3_FPB_PID4_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_FPB_PID4_ADDR, m)
#define HWIO_RPM_M3_FPB_PID4_FPB_PID4_BMSK                                      0xffffffff
#define HWIO_RPM_M3_FPB_PID4_FPB_PID4_SHFT                                             0x0

#define HWIO_RPM_M3_FPB_PID5_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x00002fd4)
#define HWIO_RPM_M3_FPB_PID5_RMSK                                               0xffffffff
#define HWIO_RPM_M3_FPB_PID5_IN          \
        in_dword_masked(HWIO_RPM_M3_FPB_PID5_ADDR, HWIO_RPM_M3_FPB_PID5_RMSK)
#define HWIO_RPM_M3_FPB_PID5_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_FPB_PID5_ADDR, m)
#define HWIO_RPM_M3_FPB_PID5_FPB_PID5_BMSK                                      0xffffffff
#define HWIO_RPM_M3_FPB_PID5_FPB_PID5_SHFT                                             0x0

#define HWIO_RPM_M3_FPB_PID6_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x00002fd8)
#define HWIO_RPM_M3_FPB_PID6_RMSK                                               0xffffffff
#define HWIO_RPM_M3_FPB_PID6_IN          \
        in_dword_masked(HWIO_RPM_M3_FPB_PID6_ADDR, HWIO_RPM_M3_FPB_PID6_RMSK)
#define HWIO_RPM_M3_FPB_PID6_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_FPB_PID6_ADDR, m)
#define HWIO_RPM_M3_FPB_PID6_FPB_PID6_BMSK                                      0xffffffff
#define HWIO_RPM_M3_FPB_PID6_FPB_PID6_SHFT                                             0x0

#define HWIO_RPM_M3_FPB_PID7_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x00002fdc)
#define HWIO_RPM_M3_FPB_PID7_RMSK                                               0xffffffff
#define HWIO_RPM_M3_FPB_PID7_IN          \
        in_dword_masked(HWIO_RPM_M3_FPB_PID7_ADDR, HWIO_RPM_M3_FPB_PID7_RMSK)
#define HWIO_RPM_M3_FPB_PID7_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_FPB_PID7_ADDR, m)
#define HWIO_RPM_M3_FPB_PID7_FPB_PID7_BMSK                                      0xffffffff
#define HWIO_RPM_M3_FPB_PID7_FPB_PID7_SHFT                                             0x0

#define HWIO_RPM_M3_FPB_PID0_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x00002fe0)
#define HWIO_RPM_M3_FPB_PID0_RMSK                                               0xffffffff
#define HWIO_RPM_M3_FPB_PID0_IN          \
        in_dword_masked(HWIO_RPM_M3_FPB_PID0_ADDR, HWIO_RPM_M3_FPB_PID0_RMSK)
#define HWIO_RPM_M3_FPB_PID0_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_FPB_PID0_ADDR, m)
#define HWIO_RPM_M3_FPB_PID0_FPB_PID0_BMSK                                      0xffffffff
#define HWIO_RPM_M3_FPB_PID0_FPB_PID0_SHFT                                             0x0

#define HWIO_RPM_M3_FPB_PID1_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x00002fe4)
#define HWIO_RPM_M3_FPB_PID1_RMSK                                               0xffffffff
#define HWIO_RPM_M3_FPB_PID1_IN          \
        in_dword_masked(HWIO_RPM_M3_FPB_PID1_ADDR, HWIO_RPM_M3_FPB_PID1_RMSK)
#define HWIO_RPM_M3_FPB_PID1_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_FPB_PID1_ADDR, m)
#define HWIO_RPM_M3_FPB_PID1_FPB_PID1_BMSK                                      0xffffffff
#define HWIO_RPM_M3_FPB_PID1_FPB_PID1_SHFT                                             0x0

#define HWIO_RPM_M3_FPB_PID2_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x00002fe8)
#define HWIO_RPM_M3_FPB_PID2_RMSK                                               0xffffffff
#define HWIO_RPM_M3_FPB_PID2_IN          \
        in_dword_masked(HWIO_RPM_M3_FPB_PID2_ADDR, HWIO_RPM_M3_FPB_PID2_RMSK)
#define HWIO_RPM_M3_FPB_PID2_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_FPB_PID2_ADDR, m)
#define HWIO_RPM_M3_FPB_PID2_FPB_PID2_BMSK                                      0xffffffff
#define HWIO_RPM_M3_FPB_PID2_FPB_PID2_SHFT                                             0x0

#define HWIO_RPM_M3_FPB_PID3_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x00002fec)
#define HWIO_RPM_M3_FPB_PID3_RMSK                                               0xffffffff
#define HWIO_RPM_M3_FPB_PID3_IN          \
        in_dword_masked(HWIO_RPM_M3_FPB_PID3_ADDR, HWIO_RPM_M3_FPB_PID3_RMSK)
#define HWIO_RPM_M3_FPB_PID3_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_FPB_PID3_ADDR, m)
#define HWIO_RPM_M3_FPB_PID3_FPB_PID3_BMSK                                      0xffffffff
#define HWIO_RPM_M3_FPB_PID3_FPB_PID3_SHFT                                             0x0

#define HWIO_RPM_M3_FPB_CID0_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x00002ff0)
#define HWIO_RPM_M3_FPB_CID0_RMSK                                               0xffffffff
#define HWIO_RPM_M3_FPB_CID0_IN          \
        in_dword_masked(HWIO_RPM_M3_FPB_CID0_ADDR, HWIO_RPM_M3_FPB_CID0_RMSK)
#define HWIO_RPM_M3_FPB_CID0_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_FPB_CID0_ADDR, m)
#define HWIO_RPM_M3_FPB_CID0_FPB_CID0_BMSK                                      0xffffffff
#define HWIO_RPM_M3_FPB_CID0_FPB_CID0_SHFT                                             0x0

#define HWIO_RPM_M3_FPB_CID1_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x00002ff4)
#define HWIO_RPM_M3_FPB_CID1_RMSK                                               0xffffffff
#define HWIO_RPM_M3_FPB_CID1_IN          \
        in_dword_masked(HWIO_RPM_M3_FPB_CID1_ADDR, HWIO_RPM_M3_FPB_CID1_RMSK)
#define HWIO_RPM_M3_FPB_CID1_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_FPB_CID1_ADDR, m)
#define HWIO_RPM_M3_FPB_CID1_FPB_CID1_BMSK                                      0xffffffff
#define HWIO_RPM_M3_FPB_CID1_FPB_CID1_SHFT                                             0x0

#define HWIO_RPM_M3_FPB_CID2_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x00002ff8)
#define HWIO_RPM_M3_FPB_CID2_RMSK                                               0xffffffff
#define HWIO_RPM_M3_FPB_CID2_IN          \
        in_dword_masked(HWIO_RPM_M3_FPB_CID2_ADDR, HWIO_RPM_M3_FPB_CID2_RMSK)
#define HWIO_RPM_M3_FPB_CID2_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_FPB_CID2_ADDR, m)
#define HWIO_RPM_M3_FPB_CID2_FPB_CID2_BMSK                                      0xffffffff
#define HWIO_RPM_M3_FPB_CID2_FPB_CID2_SHFT                                             0x0

#define HWIO_RPM_M3_FPB_CID3_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x00002ffc)
#define HWIO_RPM_M3_FPB_CID3_RMSK                                               0xffffffff
#define HWIO_RPM_M3_FPB_CID3_IN          \
        in_dword_masked(HWIO_RPM_M3_FPB_CID3_ADDR, HWIO_RPM_M3_FPB_CID3_RMSK)
#define HWIO_RPM_M3_FPB_CID3_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_FPB_CID3_ADDR, m)
#define HWIO_RPM_M3_FPB_CID3_FPB_CID3_BMSK                                      0xffffffff
#define HWIO_RPM_M3_FPB_CID3_FPB_CID3_SHFT                                             0x0

#define HWIO_RPM_M3_SCS_ICTR_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x0000e004)
#define HWIO_RPM_M3_SCS_ICTR_RMSK                                                     0x1f
#define HWIO_RPM_M3_SCS_ICTR_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_ICTR_ADDR, HWIO_RPM_M3_SCS_ICTR_RMSK)
#define HWIO_RPM_M3_SCS_ICTR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_ICTR_ADDR, m)
#define HWIO_RPM_M3_SCS_ICTR_INTLINESNUM_BMSK                                         0x1f
#define HWIO_RPM_M3_SCS_ICTR_INTLINESNUM_SHFT                                          0x0

#define HWIO_RPM_M3_SCS_ACTLR_ADDR                                              (RPM_M3_PPB_INT_REG_BASE      + 0x0000e008)
#define HWIO_RPM_M3_SCS_ACTLR_RMSK                                                     0x7
#define HWIO_RPM_M3_SCS_ACTLR_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_ACTLR_ADDR, HWIO_RPM_M3_SCS_ACTLR_RMSK)
#define HWIO_RPM_M3_SCS_ACTLR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_ACTLR_ADDR, m)
#define HWIO_RPM_M3_SCS_ACTLR_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_ACTLR_ADDR,v)
#define HWIO_RPM_M3_SCS_ACTLR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_ACTLR_ADDR,m,v,HWIO_RPM_M3_SCS_ACTLR_IN)
#define HWIO_RPM_M3_SCS_ACTLR_DISFOLD_BMSK                                             0x4
#define HWIO_RPM_M3_SCS_ACTLR_DISFOLD_SHFT                                             0x2
#define HWIO_RPM_M3_SCS_ACTLR_DISDEFWBUF_BMSK                                          0x2
#define HWIO_RPM_M3_SCS_ACTLR_DISDEFWBUF_SHFT                                          0x1
#define HWIO_RPM_M3_SCS_ACTLR_DISMCYCINT_BMSK                                          0x1
#define HWIO_RPM_M3_SCS_ACTLR_DISMCYCINT_SHFT                                          0x0

#define HWIO_RPM_M3_SCS_STCSR_ADDR                                              (RPM_M3_PPB_INT_REG_BASE      + 0x0000e010)
#define HWIO_RPM_M3_SCS_STCSR_RMSK                                                 0x10007
#define HWIO_RPM_M3_SCS_STCSR_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_STCSR_ADDR, HWIO_RPM_M3_SCS_STCSR_RMSK)
#define HWIO_RPM_M3_SCS_STCSR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_STCSR_ADDR, m)
#define HWIO_RPM_M3_SCS_STCSR_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_STCSR_ADDR,v)
#define HWIO_RPM_M3_SCS_STCSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_STCSR_ADDR,m,v,HWIO_RPM_M3_SCS_STCSR_IN)
#define HWIO_RPM_M3_SCS_STCSR_COUNTFLAG_BMSK                                       0x10000
#define HWIO_RPM_M3_SCS_STCSR_COUNTFLAG_SHFT                                          0x10
#define HWIO_RPM_M3_SCS_STCSR_CLKSOURCE_BMSK                                           0x4
#define HWIO_RPM_M3_SCS_STCSR_CLKSOURCE_SHFT                                           0x2
#define HWIO_RPM_M3_SCS_STCSR_CLKSOURCE_ENUM_0B0_FVAL                                  0x0
#define HWIO_RPM_M3_SCS_STCSR_CLKSOURCE_ENUM_0B1_FVAL                                  0x1
#define HWIO_RPM_M3_SCS_STCSR_TICKINT_BMSK                                             0x2
#define HWIO_RPM_M3_SCS_STCSR_TICKINT_SHFT                                             0x1
#define HWIO_RPM_M3_SCS_STCSR_TICKINT_ENUM_0B0_FVAL                                    0x0
#define HWIO_RPM_M3_SCS_STCSR_TICKINT_ENUM_0B1_FVAL                                    0x1
#define HWIO_RPM_M3_SCS_STCSR_ENABLE_BMSK                                              0x1
#define HWIO_RPM_M3_SCS_STCSR_ENABLE_SHFT                                              0x0
#define HWIO_RPM_M3_SCS_STCSR_ENABLE_ENUM_0B0_FVAL                                     0x0
#define HWIO_RPM_M3_SCS_STCSR_ENABLE_ENUM_0B1_FVAL                                     0x1

#define HWIO_RPM_M3_SCS_STRVR_ADDR                                              (RPM_M3_PPB_INT_REG_BASE      + 0x0000e014)
#define HWIO_RPM_M3_SCS_STRVR_RMSK                                                0xffffff
#define HWIO_RPM_M3_SCS_STRVR_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_STRVR_ADDR, HWIO_RPM_M3_SCS_STRVR_RMSK)
#define HWIO_RPM_M3_SCS_STRVR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_STRVR_ADDR, m)
#define HWIO_RPM_M3_SCS_STRVR_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_STRVR_ADDR,v)
#define HWIO_RPM_M3_SCS_STRVR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_STRVR_ADDR,m,v,HWIO_RPM_M3_SCS_STRVR_IN)
#define HWIO_RPM_M3_SCS_STRVR_RELOAD_BMSK                                         0xffffff
#define HWIO_RPM_M3_SCS_STRVR_RELOAD_SHFT                                              0x0

#define HWIO_RPM_M3_SCS_STCVR_ADDR                                              (RPM_M3_PPB_INT_REG_BASE      + 0x0000e018)
#define HWIO_RPM_M3_SCS_STCVR_RMSK                                                0xffffff
#define HWIO_RPM_M3_SCS_STCVR_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_STCVR_ADDR, HWIO_RPM_M3_SCS_STCVR_RMSK)
#define HWIO_RPM_M3_SCS_STCVR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_STCVR_ADDR, m)
#define HWIO_RPM_M3_SCS_STCVR_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_STCVR_ADDR,v)
#define HWIO_RPM_M3_SCS_STCVR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_STCVR_ADDR,m,v,HWIO_RPM_M3_SCS_STCVR_IN)
#define HWIO_RPM_M3_SCS_STCVR_CURRENT_BMSK                                        0xffffff
#define HWIO_RPM_M3_SCS_STCVR_CURRENT_SHFT                                             0x0

#define HWIO_RPM_M3_SCS_STCR_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x0000e01c)
#define HWIO_RPM_M3_SCS_STCR_RMSK                                               0xc0ffffff
#define HWIO_RPM_M3_SCS_STCR_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_STCR_ADDR, HWIO_RPM_M3_SCS_STCR_RMSK)
#define HWIO_RPM_M3_SCS_STCR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_STCR_ADDR, m)
#define HWIO_RPM_M3_SCS_STCR_NOREF_BMSK                                         0x80000000
#define HWIO_RPM_M3_SCS_STCR_NOREF_SHFT                                               0x1f
#define HWIO_RPM_M3_SCS_STCR_SKEW_BMSK                                          0x40000000
#define HWIO_RPM_M3_SCS_STCR_SKEW_SHFT                                                0x1e
#define HWIO_RPM_M3_SCS_STCR_TENMS_BMSK                                           0xffffff
#define HWIO_RPM_M3_SCS_STCR_TENMS_SHFT                                                0x0

#define HWIO_RPM_M3_SCS_NVIC_ISER0_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x0000e100)
#define HWIO_RPM_M3_SCS_NVIC_ISER0_RMSK                                         0xffffffff
#define HWIO_RPM_M3_SCS_NVIC_ISER0_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_ISER0_ADDR, HWIO_RPM_M3_SCS_NVIC_ISER0_RMSK)
#define HWIO_RPM_M3_SCS_NVIC_ISER0_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_ISER0_ADDR, m)
#define HWIO_RPM_M3_SCS_NVIC_ISER0_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_NVIC_ISER0_ADDR,v)
#define HWIO_RPM_M3_SCS_NVIC_ISER0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_NVIC_ISER0_ADDR,m,v,HWIO_RPM_M3_SCS_NVIC_ISER0_IN)
#define HWIO_RPM_M3_SCS_NVIC_ISER0_SETENA_BMSK                                  0xffffffff
#define HWIO_RPM_M3_SCS_NVIC_ISER0_SETENA_SHFT                                         0x0

#define HWIO_RPM_M3_SCS_NVIC_ISER1_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x0000e104)
#define HWIO_RPM_M3_SCS_NVIC_ISER1_RMSK                                         0xffffffff
#define HWIO_RPM_M3_SCS_NVIC_ISER1_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_ISER1_ADDR, HWIO_RPM_M3_SCS_NVIC_ISER1_RMSK)
#define HWIO_RPM_M3_SCS_NVIC_ISER1_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_ISER1_ADDR, m)
#define HWIO_RPM_M3_SCS_NVIC_ISER1_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_NVIC_ISER1_ADDR,v)
#define HWIO_RPM_M3_SCS_NVIC_ISER1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_NVIC_ISER1_ADDR,m,v,HWIO_RPM_M3_SCS_NVIC_ISER1_IN)
#define HWIO_RPM_M3_SCS_NVIC_ISER1_SETENA_BMSK                                  0xffffffff
#define HWIO_RPM_M3_SCS_NVIC_ISER1_SETENA_SHFT                                         0x0

#define HWIO_RPM_M3_SCS_NVIC_ICER0_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x0000e180)
#define HWIO_RPM_M3_SCS_NVIC_ICER0_RMSK                                         0xffffffff
#define HWIO_RPM_M3_SCS_NVIC_ICER0_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_ICER0_ADDR, HWIO_RPM_M3_SCS_NVIC_ICER0_RMSK)
#define HWIO_RPM_M3_SCS_NVIC_ICER0_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_ICER0_ADDR, m)
#define HWIO_RPM_M3_SCS_NVIC_ICER0_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_NVIC_ICER0_ADDR,v)
#define HWIO_RPM_M3_SCS_NVIC_ICER0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_NVIC_ICER0_ADDR,m,v,HWIO_RPM_M3_SCS_NVIC_ICER0_IN)
#define HWIO_RPM_M3_SCS_NVIC_ICER0_CLRENA_BMSK                                  0xffffffff
#define HWIO_RPM_M3_SCS_NVIC_ICER0_CLRENA_SHFT                                         0x0

#define HWIO_RPM_M3_SCS_NVIC_ICER1_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x0000e184)
#define HWIO_RPM_M3_SCS_NVIC_ICER1_RMSK                                         0xffffffff
#define HWIO_RPM_M3_SCS_NVIC_ICER1_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_ICER1_ADDR, HWIO_RPM_M3_SCS_NVIC_ICER1_RMSK)
#define HWIO_RPM_M3_SCS_NVIC_ICER1_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_ICER1_ADDR, m)
#define HWIO_RPM_M3_SCS_NVIC_ICER1_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_NVIC_ICER1_ADDR,v)
#define HWIO_RPM_M3_SCS_NVIC_ICER1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_NVIC_ICER1_ADDR,m,v,HWIO_RPM_M3_SCS_NVIC_ICER1_IN)
#define HWIO_RPM_M3_SCS_NVIC_ICER1_CLRENA_BMSK                                  0xffffffff
#define HWIO_RPM_M3_SCS_NVIC_ICER1_CLRENA_SHFT                                         0x0

#define HWIO_RPM_M3_SCS_NVIC_ISPR0_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x0000e200)
#define HWIO_RPM_M3_SCS_NVIC_ISPR0_RMSK                                         0xffffffff
#define HWIO_RPM_M3_SCS_NVIC_ISPR0_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_ISPR0_ADDR, HWIO_RPM_M3_SCS_NVIC_ISPR0_RMSK)
#define HWIO_RPM_M3_SCS_NVIC_ISPR0_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_ISPR0_ADDR, m)
#define HWIO_RPM_M3_SCS_NVIC_ISPR0_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_NVIC_ISPR0_ADDR,v)
#define HWIO_RPM_M3_SCS_NVIC_ISPR0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_NVIC_ISPR0_ADDR,m,v,HWIO_RPM_M3_SCS_NVIC_ISPR0_IN)
#define HWIO_RPM_M3_SCS_NVIC_ISPR0_SETPEND_BMSK                                 0xffffffff
#define HWIO_RPM_M3_SCS_NVIC_ISPR0_SETPEND_SHFT                                        0x0

#define HWIO_RPM_M3_SCS_NVIC_ISPR1_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x0000e204)
#define HWIO_RPM_M3_SCS_NVIC_ISPR1_RMSK                                         0xffffffff
#define HWIO_RPM_M3_SCS_NVIC_ISPR1_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_ISPR1_ADDR, HWIO_RPM_M3_SCS_NVIC_ISPR1_RMSK)
#define HWIO_RPM_M3_SCS_NVIC_ISPR1_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_ISPR1_ADDR, m)
#define HWIO_RPM_M3_SCS_NVIC_ISPR1_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_NVIC_ISPR1_ADDR,v)
#define HWIO_RPM_M3_SCS_NVIC_ISPR1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_NVIC_ISPR1_ADDR,m,v,HWIO_RPM_M3_SCS_NVIC_ISPR1_IN)
#define HWIO_RPM_M3_SCS_NVIC_ISPR1_SETPEND_BMSK                                 0xffffffff
#define HWIO_RPM_M3_SCS_NVIC_ISPR1_SETPEND_SHFT                                        0x0

#define HWIO_RPM_M3_SCS_NVIC_ICPR0_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x0000e280)
#define HWIO_RPM_M3_SCS_NVIC_ICPR0_RMSK                                         0xffffffff
#define HWIO_RPM_M3_SCS_NVIC_ICPR0_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_ICPR0_ADDR, HWIO_RPM_M3_SCS_NVIC_ICPR0_RMSK)
#define HWIO_RPM_M3_SCS_NVIC_ICPR0_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_ICPR0_ADDR, m)
#define HWIO_RPM_M3_SCS_NVIC_ICPR0_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_NVIC_ICPR0_ADDR,v)
#define HWIO_RPM_M3_SCS_NVIC_ICPR0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_NVIC_ICPR0_ADDR,m,v,HWIO_RPM_M3_SCS_NVIC_ICPR0_IN)
#define HWIO_RPM_M3_SCS_NVIC_ICPR0_CLRPEND_BMSK                                 0xffffffff
#define HWIO_RPM_M3_SCS_NVIC_ICPR0_CLRPEND_SHFT                                        0x0

#define HWIO_RPM_M3_SCS_NVIC_ICPR1_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x0000e284)
#define HWIO_RPM_M3_SCS_NVIC_ICPR1_RMSK                                         0xffffffff
#define HWIO_RPM_M3_SCS_NVIC_ICPR1_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_ICPR1_ADDR, HWIO_RPM_M3_SCS_NVIC_ICPR1_RMSK)
#define HWIO_RPM_M3_SCS_NVIC_ICPR1_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_ICPR1_ADDR, m)
#define HWIO_RPM_M3_SCS_NVIC_ICPR1_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_NVIC_ICPR1_ADDR,v)
#define HWIO_RPM_M3_SCS_NVIC_ICPR1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_NVIC_ICPR1_ADDR,m,v,HWIO_RPM_M3_SCS_NVIC_ICPR1_IN)
#define HWIO_RPM_M3_SCS_NVIC_ICPR1_CLRPEND_BMSK                                 0xffffffff
#define HWIO_RPM_M3_SCS_NVIC_ICPR1_CLRPEND_SHFT                                        0x0

#define HWIO_RPM_M3_SCS_NVIC_IABR0_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x0000e300)
#define HWIO_RPM_M3_SCS_NVIC_IABR0_RMSK                                         0xffffffff
#define HWIO_RPM_M3_SCS_NVIC_IABR0_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_IABR0_ADDR, HWIO_RPM_M3_SCS_NVIC_IABR0_RMSK)
#define HWIO_RPM_M3_SCS_NVIC_IABR0_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_IABR0_ADDR, m)
#define HWIO_RPM_M3_SCS_NVIC_IABR0_ACTIVE_BMSK                                  0xffffffff
#define HWIO_RPM_M3_SCS_NVIC_IABR0_ACTIVE_SHFT                                         0x0

#define HWIO_RPM_M3_SCS_NVIC_IABR1_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x0000e304)
#define HWIO_RPM_M3_SCS_NVIC_IABR1_RMSK                                         0xffffffff
#define HWIO_RPM_M3_SCS_NVIC_IABR1_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_IABR1_ADDR, HWIO_RPM_M3_SCS_NVIC_IABR1_RMSK)
#define HWIO_RPM_M3_SCS_NVIC_IABR1_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_IABR1_ADDR, m)
#define HWIO_RPM_M3_SCS_NVIC_IABR1_ACTIVE_BMSK                                  0xffffffff
#define HWIO_RPM_M3_SCS_NVIC_IABR1_ACTIVE_SHFT                                         0x0

#define HWIO_RPM_M3_SCS_NVIC_IPR0_ADDR                                          (RPM_M3_PPB_INT_REG_BASE      + 0x0000e400)
#define HWIO_RPM_M3_SCS_NVIC_IPR0_RMSK                                          0xffffffff
#define HWIO_RPM_M3_SCS_NVIC_IPR0_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_IPR0_ADDR, HWIO_RPM_M3_SCS_NVIC_IPR0_RMSK)
#define HWIO_RPM_M3_SCS_NVIC_IPR0_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_IPR0_ADDR, m)
#define HWIO_RPM_M3_SCS_NVIC_IPR0_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_NVIC_IPR0_ADDR,v)
#define HWIO_RPM_M3_SCS_NVIC_IPR0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_NVIC_IPR0_ADDR,m,v,HWIO_RPM_M3_SCS_NVIC_IPR0_IN)
#define HWIO_RPM_M3_SCS_NVIC_IPR0_PRI_3_BMSK                                    0xff000000
#define HWIO_RPM_M3_SCS_NVIC_IPR0_PRI_3_SHFT                                          0x18
#define HWIO_RPM_M3_SCS_NVIC_IPR0_PRI_2_BMSK                                      0xff0000
#define HWIO_RPM_M3_SCS_NVIC_IPR0_PRI_2_SHFT                                          0x10
#define HWIO_RPM_M3_SCS_NVIC_IPR0_PRI_1_BMSK                                        0xff00
#define HWIO_RPM_M3_SCS_NVIC_IPR0_PRI_1_SHFT                                           0x8
#define HWIO_RPM_M3_SCS_NVIC_IPR0_PRI_0_BMSK                                          0xff
#define HWIO_RPM_M3_SCS_NVIC_IPR0_PRI_0_SHFT                                           0x0

#define HWIO_RPM_M3_SCS_NVIC_IPR1_ADDR                                          (RPM_M3_PPB_INT_REG_BASE      + 0x0000e404)
#define HWIO_RPM_M3_SCS_NVIC_IPR1_RMSK                                          0xffffffff
#define HWIO_RPM_M3_SCS_NVIC_IPR1_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_IPR1_ADDR, HWIO_RPM_M3_SCS_NVIC_IPR1_RMSK)
#define HWIO_RPM_M3_SCS_NVIC_IPR1_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_IPR1_ADDR, m)
#define HWIO_RPM_M3_SCS_NVIC_IPR1_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_NVIC_IPR1_ADDR,v)
#define HWIO_RPM_M3_SCS_NVIC_IPR1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_NVIC_IPR1_ADDR,m,v,HWIO_RPM_M3_SCS_NVIC_IPR1_IN)
#define HWIO_RPM_M3_SCS_NVIC_IPR1_PRI_7_BMSK                                    0xff000000
#define HWIO_RPM_M3_SCS_NVIC_IPR1_PRI_7_SHFT                                          0x18
#define HWIO_RPM_M3_SCS_NVIC_IPR1_PRI_6_BMSK                                      0xff0000
#define HWIO_RPM_M3_SCS_NVIC_IPR1_PRI_6_SHFT                                          0x10
#define HWIO_RPM_M3_SCS_NVIC_IPR1_PRI_5_BMSK                                        0xff00
#define HWIO_RPM_M3_SCS_NVIC_IPR1_PRI_5_SHFT                                           0x8
#define HWIO_RPM_M3_SCS_NVIC_IPR1_PRI_4_BMSK                                          0xff
#define HWIO_RPM_M3_SCS_NVIC_IPR1_PRI_4_SHFT                                           0x0

#define HWIO_RPM_M3_SCS_NVIC_IPR2_ADDR                                          (RPM_M3_PPB_INT_REG_BASE      + 0x0000e408)
#define HWIO_RPM_M3_SCS_NVIC_IPR2_RMSK                                          0xffffffff
#define HWIO_RPM_M3_SCS_NVIC_IPR2_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_IPR2_ADDR, HWIO_RPM_M3_SCS_NVIC_IPR2_RMSK)
#define HWIO_RPM_M3_SCS_NVIC_IPR2_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_IPR2_ADDR, m)
#define HWIO_RPM_M3_SCS_NVIC_IPR2_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_NVIC_IPR2_ADDR,v)
#define HWIO_RPM_M3_SCS_NVIC_IPR2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_NVIC_IPR2_ADDR,m,v,HWIO_RPM_M3_SCS_NVIC_IPR2_IN)
#define HWIO_RPM_M3_SCS_NVIC_IPR2_PRI_11_BMSK                                   0xff000000
#define HWIO_RPM_M3_SCS_NVIC_IPR2_PRI_11_SHFT                                         0x18
#define HWIO_RPM_M3_SCS_NVIC_IPR2_PRI_10_BMSK                                     0xff0000
#define HWIO_RPM_M3_SCS_NVIC_IPR2_PRI_10_SHFT                                         0x10
#define HWIO_RPM_M3_SCS_NVIC_IPR2_PRI_9_BMSK                                        0xff00
#define HWIO_RPM_M3_SCS_NVIC_IPR2_PRI_9_SHFT                                           0x8
#define HWIO_RPM_M3_SCS_NVIC_IPR2_PRI_8_BMSK                                          0xff
#define HWIO_RPM_M3_SCS_NVIC_IPR2_PRI_8_SHFT                                           0x0

#define HWIO_RPM_M3_SCS_NVIC_IPR3_ADDR                                          (RPM_M3_PPB_INT_REG_BASE      + 0x0000e40c)
#define HWIO_RPM_M3_SCS_NVIC_IPR3_RMSK                                          0xffffffff
#define HWIO_RPM_M3_SCS_NVIC_IPR3_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_IPR3_ADDR, HWIO_RPM_M3_SCS_NVIC_IPR3_RMSK)
#define HWIO_RPM_M3_SCS_NVIC_IPR3_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_IPR3_ADDR, m)
#define HWIO_RPM_M3_SCS_NVIC_IPR3_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_NVIC_IPR3_ADDR,v)
#define HWIO_RPM_M3_SCS_NVIC_IPR3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_NVIC_IPR3_ADDR,m,v,HWIO_RPM_M3_SCS_NVIC_IPR3_IN)
#define HWIO_RPM_M3_SCS_NVIC_IPR3_PRI_15_BMSK                                   0xff000000
#define HWIO_RPM_M3_SCS_NVIC_IPR3_PRI_15_SHFT                                         0x18
#define HWIO_RPM_M3_SCS_NVIC_IPR3_PRI_14_BMSK                                     0xff0000
#define HWIO_RPM_M3_SCS_NVIC_IPR3_PRI_14_SHFT                                         0x10
#define HWIO_RPM_M3_SCS_NVIC_IPR3_PRI_13_BMSK                                       0xff00
#define HWIO_RPM_M3_SCS_NVIC_IPR3_PRI_13_SHFT                                          0x8
#define HWIO_RPM_M3_SCS_NVIC_IPR3_PRI_12_BMSK                                         0xff
#define HWIO_RPM_M3_SCS_NVIC_IPR3_PRI_12_SHFT                                          0x0

#define HWIO_RPM_M3_SCS_NVIC_IPR4_ADDR                                          (RPM_M3_PPB_INT_REG_BASE      + 0x0000e410)
#define HWIO_RPM_M3_SCS_NVIC_IPR4_RMSK                                          0xffffffff
#define HWIO_RPM_M3_SCS_NVIC_IPR4_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_IPR4_ADDR, HWIO_RPM_M3_SCS_NVIC_IPR4_RMSK)
#define HWIO_RPM_M3_SCS_NVIC_IPR4_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_IPR4_ADDR, m)
#define HWIO_RPM_M3_SCS_NVIC_IPR4_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_NVIC_IPR4_ADDR,v)
#define HWIO_RPM_M3_SCS_NVIC_IPR4_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_NVIC_IPR4_ADDR,m,v,HWIO_RPM_M3_SCS_NVIC_IPR4_IN)
#define HWIO_RPM_M3_SCS_NVIC_IPR4_PRI_19_BMSK                                   0xff000000
#define HWIO_RPM_M3_SCS_NVIC_IPR4_PRI_19_SHFT                                         0x18
#define HWIO_RPM_M3_SCS_NVIC_IPR4_PRI_18_BMSK                                     0xff0000
#define HWIO_RPM_M3_SCS_NVIC_IPR4_PRI_18_SHFT                                         0x10
#define HWIO_RPM_M3_SCS_NVIC_IPR4_PRI_17_BMSK                                       0xff00
#define HWIO_RPM_M3_SCS_NVIC_IPR4_PRI_17_SHFT                                          0x8
#define HWIO_RPM_M3_SCS_NVIC_IPR4_PRI_16_BMSK                                         0xff
#define HWIO_RPM_M3_SCS_NVIC_IPR4_PRI_16_SHFT                                          0x0

#define HWIO_RPM_M3_SCS_NVIC_IPR5_ADDR                                          (RPM_M3_PPB_INT_REG_BASE      + 0x0000e414)
#define HWIO_RPM_M3_SCS_NVIC_IPR5_RMSK                                          0xffffffff
#define HWIO_RPM_M3_SCS_NVIC_IPR5_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_IPR5_ADDR, HWIO_RPM_M3_SCS_NVIC_IPR5_RMSK)
#define HWIO_RPM_M3_SCS_NVIC_IPR5_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_IPR5_ADDR, m)
#define HWIO_RPM_M3_SCS_NVIC_IPR5_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_NVIC_IPR5_ADDR,v)
#define HWIO_RPM_M3_SCS_NVIC_IPR5_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_NVIC_IPR5_ADDR,m,v,HWIO_RPM_M3_SCS_NVIC_IPR5_IN)
#define HWIO_RPM_M3_SCS_NVIC_IPR5_PRI_23_BMSK                                   0xff000000
#define HWIO_RPM_M3_SCS_NVIC_IPR5_PRI_23_SHFT                                         0x18
#define HWIO_RPM_M3_SCS_NVIC_IPR5_PRI_22_BMSK                                     0xff0000
#define HWIO_RPM_M3_SCS_NVIC_IPR5_PRI_22_SHFT                                         0x10
#define HWIO_RPM_M3_SCS_NVIC_IPR5_PRI_21_BMSK                                       0xff00
#define HWIO_RPM_M3_SCS_NVIC_IPR5_PRI_21_SHFT                                          0x8
#define HWIO_RPM_M3_SCS_NVIC_IPR5_PRI_20_BMSK                                         0xff
#define HWIO_RPM_M3_SCS_NVIC_IPR5_PRI_20_SHFT                                          0x0

#define HWIO_RPM_M3_SCS_NVIC_IPR6_ADDR                                          (RPM_M3_PPB_INT_REG_BASE      + 0x0000e418)
#define HWIO_RPM_M3_SCS_NVIC_IPR6_RMSK                                          0xffffffff
#define HWIO_RPM_M3_SCS_NVIC_IPR6_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_IPR6_ADDR, HWIO_RPM_M3_SCS_NVIC_IPR6_RMSK)
#define HWIO_RPM_M3_SCS_NVIC_IPR6_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_IPR6_ADDR, m)
#define HWIO_RPM_M3_SCS_NVIC_IPR6_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_NVIC_IPR6_ADDR,v)
#define HWIO_RPM_M3_SCS_NVIC_IPR6_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_NVIC_IPR6_ADDR,m,v,HWIO_RPM_M3_SCS_NVIC_IPR6_IN)
#define HWIO_RPM_M3_SCS_NVIC_IPR6_PRI_27_BMSK                                   0xff000000
#define HWIO_RPM_M3_SCS_NVIC_IPR6_PRI_27_SHFT                                         0x18
#define HWIO_RPM_M3_SCS_NVIC_IPR6_PRI_26_BMSK                                     0xff0000
#define HWIO_RPM_M3_SCS_NVIC_IPR6_PRI_26_SHFT                                         0x10
#define HWIO_RPM_M3_SCS_NVIC_IPR6_PRI_25_BMSK                                       0xff00
#define HWIO_RPM_M3_SCS_NVIC_IPR6_PRI_25_SHFT                                          0x8
#define HWIO_RPM_M3_SCS_NVIC_IPR6_PRI_24_BMSK                                         0xff
#define HWIO_RPM_M3_SCS_NVIC_IPR6_PRI_24_SHFT                                          0x0

#define HWIO_RPM_M3_SCS_NVIC_IPR7_ADDR                                          (RPM_M3_PPB_INT_REG_BASE      + 0x0000e41c)
#define HWIO_RPM_M3_SCS_NVIC_IPR7_RMSK                                          0xffffffff
#define HWIO_RPM_M3_SCS_NVIC_IPR7_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_IPR7_ADDR, HWIO_RPM_M3_SCS_NVIC_IPR7_RMSK)
#define HWIO_RPM_M3_SCS_NVIC_IPR7_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_IPR7_ADDR, m)
#define HWIO_RPM_M3_SCS_NVIC_IPR7_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_NVIC_IPR7_ADDR,v)
#define HWIO_RPM_M3_SCS_NVIC_IPR7_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_NVIC_IPR7_ADDR,m,v,HWIO_RPM_M3_SCS_NVIC_IPR7_IN)
#define HWIO_RPM_M3_SCS_NVIC_IPR7_PRI_31_BMSK                                   0xff000000
#define HWIO_RPM_M3_SCS_NVIC_IPR7_PRI_31_SHFT                                         0x18
#define HWIO_RPM_M3_SCS_NVIC_IPR7_PRI_30_BMSK                                     0xff0000
#define HWIO_RPM_M3_SCS_NVIC_IPR7_PRI_30_SHFT                                         0x10
#define HWIO_RPM_M3_SCS_NVIC_IPR7_PRI_29_BMSK                                       0xff00
#define HWIO_RPM_M3_SCS_NVIC_IPR7_PRI_29_SHFT                                          0x8
#define HWIO_RPM_M3_SCS_NVIC_IPR7_PRI_28_BMSK                                         0xff
#define HWIO_RPM_M3_SCS_NVIC_IPR7_PRI_28_SHFT                                          0x0

#define HWIO_RPM_M3_SCS_NVIC_IPR8_ADDR                                          (RPM_M3_PPB_INT_REG_BASE      + 0x0000e420)
#define HWIO_RPM_M3_SCS_NVIC_IPR8_RMSK                                          0xffffffff
#define HWIO_RPM_M3_SCS_NVIC_IPR8_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_IPR8_ADDR, HWIO_RPM_M3_SCS_NVIC_IPR8_RMSK)
#define HWIO_RPM_M3_SCS_NVIC_IPR8_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_IPR8_ADDR, m)
#define HWIO_RPM_M3_SCS_NVIC_IPR8_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_NVIC_IPR8_ADDR,v)
#define HWIO_RPM_M3_SCS_NVIC_IPR8_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_NVIC_IPR8_ADDR,m,v,HWIO_RPM_M3_SCS_NVIC_IPR8_IN)
#define HWIO_RPM_M3_SCS_NVIC_IPR8_PRI_35_BMSK                                   0xff000000
#define HWIO_RPM_M3_SCS_NVIC_IPR8_PRI_35_SHFT                                         0x18
#define HWIO_RPM_M3_SCS_NVIC_IPR8_PRI_34_BMSK                                     0xff0000
#define HWIO_RPM_M3_SCS_NVIC_IPR8_PRI_34_SHFT                                         0x10
#define HWIO_RPM_M3_SCS_NVIC_IPR8_PRI_33_BMSK                                       0xff00
#define HWIO_RPM_M3_SCS_NVIC_IPR8_PRI_33_SHFT                                          0x8
#define HWIO_RPM_M3_SCS_NVIC_IPR8_PRI_32_BMSK                                         0xff
#define HWIO_RPM_M3_SCS_NVIC_IPR8_PRI_32_SHFT                                          0x0

#define HWIO_RPM_M3_SCS_NVIC_IPR9_ADDR                                          (RPM_M3_PPB_INT_REG_BASE      + 0x0000e424)
#define HWIO_RPM_M3_SCS_NVIC_IPR9_RMSK                                          0xffffffff
#define HWIO_RPM_M3_SCS_NVIC_IPR9_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_IPR9_ADDR, HWIO_RPM_M3_SCS_NVIC_IPR9_RMSK)
#define HWIO_RPM_M3_SCS_NVIC_IPR9_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_IPR9_ADDR, m)
#define HWIO_RPM_M3_SCS_NVIC_IPR9_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_NVIC_IPR9_ADDR,v)
#define HWIO_RPM_M3_SCS_NVIC_IPR9_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_NVIC_IPR9_ADDR,m,v,HWIO_RPM_M3_SCS_NVIC_IPR9_IN)
#define HWIO_RPM_M3_SCS_NVIC_IPR9_PRI_39_BMSK                                   0xff000000
#define HWIO_RPM_M3_SCS_NVIC_IPR9_PRI_39_SHFT                                         0x18
#define HWIO_RPM_M3_SCS_NVIC_IPR9_PRI_38_BMSK                                     0xff0000
#define HWIO_RPM_M3_SCS_NVIC_IPR9_PRI_38_SHFT                                         0x10
#define HWIO_RPM_M3_SCS_NVIC_IPR9_PRI_37_BMSK                                       0xff00
#define HWIO_RPM_M3_SCS_NVIC_IPR9_PRI_37_SHFT                                          0x8
#define HWIO_RPM_M3_SCS_NVIC_IPR9_PRI_36_BMSK                                         0xff
#define HWIO_RPM_M3_SCS_NVIC_IPR9_PRI_36_SHFT                                          0x0

#define HWIO_RPM_M3_SCS_NVIC_IPR10_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x0000e428)
#define HWIO_RPM_M3_SCS_NVIC_IPR10_RMSK                                         0xffffffff
#define HWIO_RPM_M3_SCS_NVIC_IPR10_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_IPR10_ADDR, HWIO_RPM_M3_SCS_NVIC_IPR10_RMSK)
#define HWIO_RPM_M3_SCS_NVIC_IPR10_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_IPR10_ADDR, m)
#define HWIO_RPM_M3_SCS_NVIC_IPR10_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_NVIC_IPR10_ADDR,v)
#define HWIO_RPM_M3_SCS_NVIC_IPR10_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_NVIC_IPR10_ADDR,m,v,HWIO_RPM_M3_SCS_NVIC_IPR10_IN)
#define HWIO_RPM_M3_SCS_NVIC_IPR10_PRI_43_BMSK                                  0xff000000
#define HWIO_RPM_M3_SCS_NVIC_IPR10_PRI_43_SHFT                                        0x18
#define HWIO_RPM_M3_SCS_NVIC_IPR10_PRI_42_BMSK                                    0xff0000
#define HWIO_RPM_M3_SCS_NVIC_IPR10_PRI_42_SHFT                                        0x10
#define HWIO_RPM_M3_SCS_NVIC_IPR10_PRI_41_BMSK                                      0xff00
#define HWIO_RPM_M3_SCS_NVIC_IPR10_PRI_41_SHFT                                         0x8
#define HWIO_RPM_M3_SCS_NVIC_IPR10_PRI_40_BMSK                                        0xff
#define HWIO_RPM_M3_SCS_NVIC_IPR10_PRI_40_SHFT                                         0x0

#define HWIO_RPM_M3_SCS_NVIC_IPR11_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x0000e42c)
#define HWIO_RPM_M3_SCS_NVIC_IPR11_RMSK                                         0xffffffff
#define HWIO_RPM_M3_SCS_NVIC_IPR11_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_IPR11_ADDR, HWIO_RPM_M3_SCS_NVIC_IPR11_RMSK)
#define HWIO_RPM_M3_SCS_NVIC_IPR11_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_IPR11_ADDR, m)
#define HWIO_RPM_M3_SCS_NVIC_IPR11_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_NVIC_IPR11_ADDR,v)
#define HWIO_RPM_M3_SCS_NVIC_IPR11_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_NVIC_IPR11_ADDR,m,v,HWIO_RPM_M3_SCS_NVIC_IPR11_IN)
#define HWIO_RPM_M3_SCS_NVIC_IPR11_PRI_47_BMSK                                  0xff000000
#define HWIO_RPM_M3_SCS_NVIC_IPR11_PRI_47_SHFT                                        0x18
#define HWIO_RPM_M3_SCS_NVIC_IPR11_PRI_46_BMSK                                    0xff0000
#define HWIO_RPM_M3_SCS_NVIC_IPR11_PRI_46_SHFT                                        0x10
#define HWIO_RPM_M3_SCS_NVIC_IPR11_PRI_45_BMSK                                      0xff00
#define HWIO_RPM_M3_SCS_NVIC_IPR11_PRI_45_SHFT                                         0x8
#define HWIO_RPM_M3_SCS_NVIC_IPR11_PRI_44_BMSK                                        0xff
#define HWIO_RPM_M3_SCS_NVIC_IPR11_PRI_44_SHFT                                         0x0

#define HWIO_RPM_M3_SCS_NVIC_IPR12_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x0000e430)
#define HWIO_RPM_M3_SCS_NVIC_IPR12_RMSK                                         0xffffffff
#define HWIO_RPM_M3_SCS_NVIC_IPR12_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_IPR12_ADDR, HWIO_RPM_M3_SCS_NVIC_IPR12_RMSK)
#define HWIO_RPM_M3_SCS_NVIC_IPR12_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_IPR12_ADDR, m)
#define HWIO_RPM_M3_SCS_NVIC_IPR12_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_NVIC_IPR12_ADDR,v)
#define HWIO_RPM_M3_SCS_NVIC_IPR12_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_NVIC_IPR12_ADDR,m,v,HWIO_RPM_M3_SCS_NVIC_IPR12_IN)
#define HWIO_RPM_M3_SCS_NVIC_IPR12_PRI_51_BMSK                                  0xff000000
#define HWIO_RPM_M3_SCS_NVIC_IPR12_PRI_51_SHFT                                        0x18
#define HWIO_RPM_M3_SCS_NVIC_IPR12_PRI_50_BMSK                                    0xff0000
#define HWIO_RPM_M3_SCS_NVIC_IPR12_PRI_50_SHFT                                        0x10
#define HWIO_RPM_M3_SCS_NVIC_IPR12_PRI_49_BMSK                                      0xff00
#define HWIO_RPM_M3_SCS_NVIC_IPR12_PRI_49_SHFT                                         0x8
#define HWIO_RPM_M3_SCS_NVIC_IPR12_PRI_48_BMSK                                        0xff
#define HWIO_RPM_M3_SCS_NVIC_IPR12_PRI_48_SHFT                                         0x0

#define HWIO_RPM_M3_SCS_NVIC_IPR13_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x0000e434)
#define HWIO_RPM_M3_SCS_NVIC_IPR13_RMSK                                         0xffffffff
#define HWIO_RPM_M3_SCS_NVIC_IPR13_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_IPR13_ADDR, HWIO_RPM_M3_SCS_NVIC_IPR13_RMSK)
#define HWIO_RPM_M3_SCS_NVIC_IPR13_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_IPR13_ADDR, m)
#define HWIO_RPM_M3_SCS_NVIC_IPR13_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_NVIC_IPR13_ADDR,v)
#define HWIO_RPM_M3_SCS_NVIC_IPR13_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_NVIC_IPR13_ADDR,m,v,HWIO_RPM_M3_SCS_NVIC_IPR13_IN)
#define HWIO_RPM_M3_SCS_NVIC_IPR13_PRI_55_BMSK                                  0xff000000
#define HWIO_RPM_M3_SCS_NVIC_IPR13_PRI_55_SHFT                                        0x18
#define HWIO_RPM_M3_SCS_NVIC_IPR13_PRI_54_BMSK                                    0xff0000
#define HWIO_RPM_M3_SCS_NVIC_IPR13_PRI_54_SHFT                                        0x10
#define HWIO_RPM_M3_SCS_NVIC_IPR13_PRI_53_BMSK                                      0xff00
#define HWIO_RPM_M3_SCS_NVIC_IPR13_PRI_53_SHFT                                         0x8
#define HWIO_RPM_M3_SCS_NVIC_IPR13_PRI_52_BMSK                                        0xff
#define HWIO_RPM_M3_SCS_NVIC_IPR13_PRI_52_SHFT                                         0x0

#define HWIO_RPM_M3_SCS_NVIC_IPR14_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x0000e438)
#define HWIO_RPM_M3_SCS_NVIC_IPR14_RMSK                                         0xffffffff
#define HWIO_RPM_M3_SCS_NVIC_IPR14_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_IPR14_ADDR, HWIO_RPM_M3_SCS_NVIC_IPR14_RMSK)
#define HWIO_RPM_M3_SCS_NVIC_IPR14_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_IPR14_ADDR, m)
#define HWIO_RPM_M3_SCS_NVIC_IPR14_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_NVIC_IPR14_ADDR,v)
#define HWIO_RPM_M3_SCS_NVIC_IPR14_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_NVIC_IPR14_ADDR,m,v,HWIO_RPM_M3_SCS_NVIC_IPR14_IN)
#define HWIO_RPM_M3_SCS_NVIC_IPR14_PRI_59_BMSK                                  0xff000000
#define HWIO_RPM_M3_SCS_NVIC_IPR14_PRI_59_SHFT                                        0x18
#define HWIO_RPM_M3_SCS_NVIC_IPR14_PRI_58_BMSK                                    0xff0000
#define HWIO_RPM_M3_SCS_NVIC_IPR14_PRI_58_SHFT                                        0x10
#define HWIO_RPM_M3_SCS_NVIC_IPR14_PRI_57_BMSK                                      0xff00
#define HWIO_RPM_M3_SCS_NVIC_IPR14_PRI_57_SHFT                                         0x8
#define HWIO_RPM_M3_SCS_NVIC_IPR14_PRI_56_BMSK                                        0xff
#define HWIO_RPM_M3_SCS_NVIC_IPR14_PRI_56_SHFT                                         0x0

#define HWIO_RPM_M3_SCS_NVIC_IPR15_ADDR                                         (RPM_M3_PPB_INT_REG_BASE      + 0x0000e43c)
#define HWIO_RPM_M3_SCS_NVIC_IPR15_RMSK                                         0xffffffff
#define HWIO_RPM_M3_SCS_NVIC_IPR15_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_IPR15_ADDR, HWIO_RPM_M3_SCS_NVIC_IPR15_RMSK)
#define HWIO_RPM_M3_SCS_NVIC_IPR15_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_NVIC_IPR15_ADDR, m)
#define HWIO_RPM_M3_SCS_NVIC_IPR15_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_NVIC_IPR15_ADDR,v)
#define HWIO_RPM_M3_SCS_NVIC_IPR15_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_NVIC_IPR15_ADDR,m,v,HWIO_RPM_M3_SCS_NVIC_IPR15_IN)
#define HWIO_RPM_M3_SCS_NVIC_IPR15_PRI_63_BMSK                                  0xff000000
#define HWIO_RPM_M3_SCS_NVIC_IPR15_PRI_63_SHFT                                        0x18
#define HWIO_RPM_M3_SCS_NVIC_IPR15_PRI_62_BMSK                                    0xff0000
#define HWIO_RPM_M3_SCS_NVIC_IPR15_PRI_62_SHFT                                        0x10
#define HWIO_RPM_M3_SCS_NVIC_IPR15_PRI_61_BMSK                                      0xff00
#define HWIO_RPM_M3_SCS_NVIC_IPR15_PRI_61_SHFT                                         0x8
#define HWIO_RPM_M3_SCS_NVIC_IPR15_PRI_60_BMSK                                        0xff
#define HWIO_RPM_M3_SCS_NVIC_IPR15_PRI_60_SHFT                                         0x0

#define HWIO_RPM_M3_SCS_CPUID_ADDR                                              (RPM_M3_PPB_INT_REG_BASE      + 0x0000ed00)
#define HWIO_RPM_M3_SCS_CPUID_RMSK                                              0xffffffff
#define HWIO_RPM_M3_SCS_CPUID_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_CPUID_ADDR, HWIO_RPM_M3_SCS_CPUID_RMSK)
#define HWIO_RPM_M3_SCS_CPUID_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_CPUID_ADDR, m)
#define HWIO_RPM_M3_SCS_CPUID_IMPLEMENTER_BMSK                                  0xff000000
#define HWIO_RPM_M3_SCS_CPUID_IMPLEMENTER_SHFT                                        0x18
#define HWIO_RPM_M3_SCS_CPUID_VARIANT_BMSK                                        0xf00000
#define HWIO_RPM_M3_SCS_CPUID_VARIANT_SHFT                                            0x14
#define HWIO_RPM_M3_SCS_CPUID_CONSTANT_BMSK                                        0xf0000
#define HWIO_RPM_M3_SCS_CPUID_CONSTANT_SHFT                                           0x10
#define HWIO_RPM_M3_SCS_CPUID_PARTNO_BMSK                                           0xfff0
#define HWIO_RPM_M3_SCS_CPUID_PARTNO_SHFT                                              0x4
#define HWIO_RPM_M3_SCS_CPUID_REVISION_BMSK                                            0xf
#define HWIO_RPM_M3_SCS_CPUID_REVISION_SHFT                                            0x0

#define HWIO_RPM_M3_SCS_ICSR_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x0000ed04)
#define HWIO_RPM_M3_SCS_ICSR_RMSK                                               0x9ec3f9ff
#define HWIO_RPM_M3_SCS_ICSR_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_ICSR_ADDR, HWIO_RPM_M3_SCS_ICSR_RMSK)
#define HWIO_RPM_M3_SCS_ICSR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_ICSR_ADDR, m)
#define HWIO_RPM_M3_SCS_ICSR_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_ICSR_ADDR,v)
#define HWIO_RPM_M3_SCS_ICSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_ICSR_ADDR,m,v,HWIO_RPM_M3_SCS_ICSR_IN)
#define HWIO_RPM_M3_SCS_ICSR_NMIPENDSET_BMSK                                    0x80000000
#define HWIO_RPM_M3_SCS_ICSR_NMIPENDSET_SHFT                                          0x1f
#define HWIO_RPM_M3_SCS_ICSR_NMIPENDSET_ENUM_0B0_FVAL                                  0x0
#define HWIO_RPM_M3_SCS_ICSR_NMIPENDSET_ENUM_0B1_FVAL                                  0x1
#define HWIO_RPM_M3_SCS_ICSR_PENDSVSET_BMSK                                     0x10000000
#define HWIO_RPM_M3_SCS_ICSR_PENDSVSET_SHFT                                           0x1c
#define HWIO_RPM_M3_SCS_ICSR_PENDSVSET_ENUM_0B0_FVAL                                   0x0
#define HWIO_RPM_M3_SCS_ICSR_PENDSVSET_ENUM_0B1_FVAL                                   0x1
#define HWIO_RPM_M3_SCS_ICSR_PENDSVCLR_BMSK                                      0x8000000
#define HWIO_RPM_M3_SCS_ICSR_PENDSVCLR_SHFT                                           0x1b
#define HWIO_RPM_M3_SCS_ICSR_PENDSVCLR_ENUM_0B0_FVAL                                   0x0
#define HWIO_RPM_M3_SCS_ICSR_PENDSVCLR_ENUM_0B1_FVAL                                   0x1
#define HWIO_RPM_M3_SCS_ICSR_PENDSTSET_BMSK                                      0x4000000
#define HWIO_RPM_M3_SCS_ICSR_PENDSTSET_SHFT                                           0x1a
#define HWIO_RPM_M3_SCS_ICSR_PENDSTSET_ENUM_0B0_FVAL                                   0x0
#define HWIO_RPM_M3_SCS_ICSR_PENDSTSET_ENUM_0B1_FVAL                                   0x1
#define HWIO_RPM_M3_SCS_ICSR_PENDSTCLR_BMSK                                      0x2000000
#define HWIO_RPM_M3_SCS_ICSR_PENDSTCLR_SHFT                                           0x19
#define HWIO_RPM_M3_SCS_ICSR_PENDSTCLR_ENUM_0B0_FVAL                                   0x0
#define HWIO_RPM_M3_SCS_ICSR_PENDSTCLR_ENUM_0B1_FVAL                                   0x1
#define HWIO_RPM_M3_SCS_ICSR_ISRPREEMPT_BMSK                                      0x800000
#define HWIO_RPM_M3_SCS_ICSR_ISRPREEMPT_SHFT                                          0x17
#define HWIO_RPM_M3_SCS_ICSR_ISRPREEMPT_ENUM_0B0_FVAL                                  0x0
#define HWIO_RPM_M3_SCS_ICSR_ISRPREEMPT_ENUM_0B1_FVAL                                  0x1
#define HWIO_RPM_M3_SCS_ICSR_ISRPENDING_BMSK                                      0x400000
#define HWIO_RPM_M3_SCS_ICSR_ISRPENDING_SHFT                                          0x16
#define HWIO_RPM_M3_SCS_ICSR_ISRPENDING_ENUM_0B0_FVAL                                  0x0
#define HWIO_RPM_M3_SCS_ICSR_ISRPENDING_ENUM_0B1_FVAL                                  0x1
#define HWIO_RPM_M3_SCS_ICSR_VECTPENDING_BMSK                                      0x3f000
#define HWIO_RPM_M3_SCS_ICSR_VECTPENDING_SHFT                                          0xc
#define HWIO_RPM_M3_SCS_ICSR_RETTOBASE_BMSK                                          0x800
#define HWIO_RPM_M3_SCS_ICSR_RETTOBASE_SHFT                                            0xb
#define HWIO_RPM_M3_SCS_ICSR_VECTACTIVE_BMSK                                         0x1ff
#define HWIO_RPM_M3_SCS_ICSR_VECTACTIVE_SHFT                                           0x0

#define HWIO_RPM_M3_SCS_VTOR_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x0000ed08)
#define HWIO_RPM_M3_SCS_VTOR_RMSK                                               0x3fffff80
#define HWIO_RPM_M3_SCS_VTOR_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_VTOR_ADDR, HWIO_RPM_M3_SCS_VTOR_RMSK)
#define HWIO_RPM_M3_SCS_VTOR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_VTOR_ADDR, m)
#define HWIO_RPM_M3_SCS_VTOR_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_VTOR_ADDR,v)
#define HWIO_RPM_M3_SCS_VTOR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_VTOR_ADDR,m,v,HWIO_RPM_M3_SCS_VTOR_IN)
#define HWIO_RPM_M3_SCS_VTOR_TBLBASE_BMSK                                       0x20000000
#define HWIO_RPM_M3_SCS_VTOR_TBLBASE_SHFT                                             0x1d
#define HWIO_RPM_M3_SCS_VTOR_TBLOFF_BMSK                                        0x1fffff80
#define HWIO_RPM_M3_SCS_VTOR_TBLOFF_SHFT                                               0x7

#define HWIO_RPM_M3_SCS_AIRCR_ADDR                                              (RPM_M3_PPB_INT_REG_BASE      + 0x0000ed0c)
#define HWIO_RPM_M3_SCS_AIRCR_RMSK                                              0xffff8707
#define HWIO_RPM_M3_SCS_AIRCR_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_AIRCR_ADDR, HWIO_RPM_M3_SCS_AIRCR_RMSK)
#define HWIO_RPM_M3_SCS_AIRCR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_AIRCR_ADDR, m)
#define HWIO_RPM_M3_SCS_AIRCR_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_AIRCR_ADDR,v)
#define HWIO_RPM_M3_SCS_AIRCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_AIRCR_ADDR,m,v,HWIO_RPM_M3_SCS_AIRCR_IN)
#define HWIO_RPM_M3_SCS_AIRCR_VECTKEY_BMSK                                      0xffff0000
#define HWIO_RPM_M3_SCS_AIRCR_VECTKEY_SHFT                                            0x10
#define HWIO_RPM_M3_SCS_AIRCR_ENDIANESS_BMSK                                        0x8000
#define HWIO_RPM_M3_SCS_AIRCR_ENDIANESS_SHFT                                           0xf
#define HWIO_RPM_M3_SCS_AIRCR_ENDIANESS_ENUM_0B0_FVAL                                  0x0
#define HWIO_RPM_M3_SCS_AIRCR_ENDIANESS_ENUM_0B1_FVAL                                  0x1
#define HWIO_RPM_M3_SCS_AIRCR_PRIGROUP_BMSK                                          0x700
#define HWIO_RPM_M3_SCS_AIRCR_PRIGROUP_SHFT                                            0x8
#define HWIO_RPM_M3_SCS_AIRCR_SYSRESETREQ_BMSK                                         0x4
#define HWIO_RPM_M3_SCS_AIRCR_SYSRESETREQ_SHFT                                         0x2
#define HWIO_RPM_M3_SCS_AIRCR_VECTCLRACTIVE_BMSK                                       0x2
#define HWIO_RPM_M3_SCS_AIRCR_VECTCLRACTIVE_SHFT                                       0x1
#define HWIO_RPM_M3_SCS_AIRCR_VECTRESET_BMSK                                           0x1
#define HWIO_RPM_M3_SCS_AIRCR_VECTRESET_SHFT                                           0x0

#define HWIO_RPM_M3_SCS_SCR_ADDR                                                (RPM_M3_PPB_INT_REG_BASE      + 0x0000ed10)
#define HWIO_RPM_M3_SCS_SCR_RMSK                                                      0x16
#define HWIO_RPM_M3_SCS_SCR_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_SCR_ADDR, HWIO_RPM_M3_SCS_SCR_RMSK)
#define HWIO_RPM_M3_SCS_SCR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_SCR_ADDR, m)
#define HWIO_RPM_M3_SCS_SCR_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_SCR_ADDR,v)
#define HWIO_RPM_M3_SCS_SCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_SCR_ADDR,m,v,HWIO_RPM_M3_SCS_SCR_IN)
#define HWIO_RPM_M3_SCS_SCR_SEVONPEND_BMSK                                            0x10
#define HWIO_RPM_M3_SCS_SCR_SEVONPEND_SHFT                                             0x4
#define HWIO_RPM_M3_SCS_SCR_SLEEPDEEP_BMSK                                             0x4
#define HWIO_RPM_M3_SCS_SCR_SLEEPDEEP_SHFT                                             0x2
#define HWIO_RPM_M3_SCS_SCR_SLEEPDEEP_ENUM_0B0_FVAL                                    0x0
#define HWIO_RPM_M3_SCS_SCR_SLEEPDEEP_ENUM_0B1_FVAL                                    0x1
#define HWIO_RPM_M3_SCS_SCR_SLEEPONEXIT_BMSK                                           0x2
#define HWIO_RPM_M3_SCS_SCR_SLEEPONEXIT_SHFT                                           0x1
#define HWIO_RPM_M3_SCS_SCR_SLEEPONEXIT_ENUM_0B0_FVAL                                  0x0
#define HWIO_RPM_M3_SCS_SCR_SLEEPONEXIT_ENUM_0B1_FVAL                                  0x1

#define HWIO_RPM_M3_SCS_CCR_ADDR                                                (RPM_M3_PPB_INT_REG_BASE      + 0x0000ed14)
#define HWIO_RPM_M3_SCS_CCR_RMSK                                                     0x31b
#define HWIO_RPM_M3_SCS_CCR_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_CCR_ADDR, HWIO_RPM_M3_SCS_CCR_RMSK)
#define HWIO_RPM_M3_SCS_CCR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_CCR_ADDR, m)
#define HWIO_RPM_M3_SCS_CCR_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_CCR_ADDR,v)
#define HWIO_RPM_M3_SCS_CCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_CCR_ADDR,m,v,HWIO_RPM_M3_SCS_CCR_IN)
#define HWIO_RPM_M3_SCS_CCR_STKALIGN_BMSK                                            0x200
#define HWIO_RPM_M3_SCS_CCR_STKALIGN_SHFT                                              0x9
#define HWIO_RPM_M3_SCS_CCR_STKALIGN_ENUM_0B0_FVAL                                     0x0
#define HWIO_RPM_M3_SCS_CCR_STKALIGN_ENUM_0B1_FVAL                                     0x1
#define HWIO_RPM_M3_SCS_CCR_BFHFNMIGN_BMSK                                           0x100
#define HWIO_RPM_M3_SCS_CCR_BFHFNMIGN_SHFT                                             0x8
#define HWIO_RPM_M3_SCS_CCR_DIV_0_TRP_BMSK                                            0x10
#define HWIO_RPM_M3_SCS_CCR_DIV_0_TRP_SHFT                                             0x4
#define HWIO_RPM_M3_SCS_CCR_UNALIGN_TRP_BMSK                                           0x8
#define HWIO_RPM_M3_SCS_CCR_UNALIGN_TRP_SHFT                                           0x3
#define HWIO_RPM_M3_SCS_CCR_USERSETMPEND_BMSK                                          0x2
#define HWIO_RPM_M3_SCS_CCR_USERSETMPEND_SHFT                                          0x1
#define HWIO_RPM_M3_SCS_CCR_NONBASETHREDENA_BMSK                                       0x1
#define HWIO_RPM_M3_SCS_CCR_NONBASETHREDENA_SHFT                                       0x0

#define HWIO_RPM_M3_SCS_SHPR1_ADDR                                              (RPM_M3_PPB_INT_REG_BASE      + 0x0000ed18)
#define HWIO_RPM_M3_SCS_SHPR1_RMSK                                              0xffffffff
#define HWIO_RPM_M3_SCS_SHPR1_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_SHPR1_ADDR, HWIO_RPM_M3_SCS_SHPR1_RMSK)
#define HWIO_RPM_M3_SCS_SHPR1_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_SHPR1_ADDR, m)
#define HWIO_RPM_M3_SCS_SHPR1_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_SHPR1_ADDR,v)
#define HWIO_RPM_M3_SCS_SHPR1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_SHPR1_ADDR,m,v,HWIO_RPM_M3_SCS_SHPR1_IN)
#define HWIO_RPM_M3_SCS_SHPR1_PRI_7_BMSK                                        0xff000000
#define HWIO_RPM_M3_SCS_SHPR1_PRI_7_SHFT                                              0x18
#define HWIO_RPM_M3_SCS_SHPR1_PRI_6_BMSK                                          0xff0000
#define HWIO_RPM_M3_SCS_SHPR1_PRI_6_SHFT                                              0x10
#define HWIO_RPM_M3_SCS_SHPR1_PRI_5_BMSK                                            0xff00
#define HWIO_RPM_M3_SCS_SHPR1_PRI_5_SHFT                                               0x8
#define HWIO_RPM_M3_SCS_SHPR1_PRI_4_BMSK                                              0xff
#define HWIO_RPM_M3_SCS_SHPR1_PRI_4_SHFT                                               0x0

#define HWIO_RPM_M3_SCS_SHPR2_ADDR                                              (RPM_M3_PPB_INT_REG_BASE      + 0x0000ed1c)
#define HWIO_RPM_M3_SCS_SHPR2_RMSK                                              0xffffffff
#define HWIO_RPM_M3_SCS_SHPR2_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_SHPR2_ADDR, HWIO_RPM_M3_SCS_SHPR2_RMSK)
#define HWIO_RPM_M3_SCS_SHPR2_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_SHPR2_ADDR, m)
#define HWIO_RPM_M3_SCS_SHPR2_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_SHPR2_ADDR,v)
#define HWIO_RPM_M3_SCS_SHPR2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_SHPR2_ADDR,m,v,HWIO_RPM_M3_SCS_SHPR2_IN)
#define HWIO_RPM_M3_SCS_SHPR2_PRI_11_BMSK                                       0xff000000
#define HWIO_RPM_M3_SCS_SHPR2_PRI_11_SHFT                                             0x18
#define HWIO_RPM_M3_SCS_SHPR2_PRI_10_BMSK                                         0xff0000
#define HWIO_RPM_M3_SCS_SHPR2_PRI_10_SHFT                                             0x10
#define HWIO_RPM_M3_SCS_SHPR2_PRI_9_BMSK                                            0xff00
#define HWIO_RPM_M3_SCS_SHPR2_PRI_9_SHFT                                               0x8
#define HWIO_RPM_M3_SCS_SHPR2_PRI_8_BMSK                                              0xff
#define HWIO_RPM_M3_SCS_SHPR2_PRI_8_SHFT                                               0x0

#define HWIO_RPM_M3_SCS_SHPR3_ADDR                                              (RPM_M3_PPB_INT_REG_BASE      + 0x0000ed20)
#define HWIO_RPM_M3_SCS_SHPR3_RMSK                                              0xffffffff
#define HWIO_RPM_M3_SCS_SHPR3_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_SHPR3_ADDR, HWIO_RPM_M3_SCS_SHPR3_RMSK)
#define HWIO_RPM_M3_SCS_SHPR3_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_SHPR3_ADDR, m)
#define HWIO_RPM_M3_SCS_SHPR3_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_SHPR3_ADDR,v)
#define HWIO_RPM_M3_SCS_SHPR3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_SHPR3_ADDR,m,v,HWIO_RPM_M3_SCS_SHPR3_IN)
#define HWIO_RPM_M3_SCS_SHPR3_PRI_15_BMSK                                       0xff000000
#define HWIO_RPM_M3_SCS_SHPR3_PRI_15_SHFT                                             0x18
#define HWIO_RPM_M3_SCS_SHPR3_PRI_14_BMSK                                         0xff0000
#define HWIO_RPM_M3_SCS_SHPR3_PRI_14_SHFT                                             0x10
#define HWIO_RPM_M3_SCS_SHPR3_PRI_13_BMSK                                           0xff00
#define HWIO_RPM_M3_SCS_SHPR3_PRI_13_SHFT                                              0x8
#define HWIO_RPM_M3_SCS_SHPR3_PRI_12_BMSK                                             0xff
#define HWIO_RPM_M3_SCS_SHPR3_PRI_12_SHFT                                              0x0

#define HWIO_RPM_M3_SCS_SHCSR_ADDR                                              (RPM_M3_PPB_INT_REG_BASE      + 0x0000ed24)
#define HWIO_RPM_M3_SCS_SHCSR_RMSK                                                 0x7fd8b
#define HWIO_RPM_M3_SCS_SHCSR_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_SHCSR_ADDR, HWIO_RPM_M3_SCS_SHCSR_RMSK)
#define HWIO_RPM_M3_SCS_SHCSR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_SHCSR_ADDR, m)
#define HWIO_RPM_M3_SCS_SHCSR_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_SHCSR_ADDR,v)
#define HWIO_RPM_M3_SCS_SHCSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_SHCSR_ADDR,m,v,HWIO_RPM_M3_SCS_SHCSR_IN)
#define HWIO_RPM_M3_SCS_SHCSR_USGFAULTENA_BMSK                                     0x40000
#define HWIO_RPM_M3_SCS_SHCSR_USGFAULTENA_SHFT                                        0x12
#define HWIO_RPM_M3_SCS_SHCSR_USGFAULTENA_ENUM_0B0_FVAL                                0x0
#define HWIO_RPM_M3_SCS_SHCSR_USGFAULTENA_ENUM_0B1_FVAL                                0x1
#define HWIO_RPM_M3_SCS_SHCSR_BUSFAULTENA_BMSK                                     0x20000
#define HWIO_RPM_M3_SCS_SHCSR_BUSFAULTENA_SHFT                                        0x11
#define HWIO_RPM_M3_SCS_SHCSR_BUSFAULTENA_ENUM_0B0_FVAL                                0x0
#define HWIO_RPM_M3_SCS_SHCSR_BUSFAULTENA_ENUM_0B1_FVAL                                0x1
#define HWIO_RPM_M3_SCS_SHCSR_MEMFAULTENA_BMSK                                     0x10000
#define HWIO_RPM_M3_SCS_SHCSR_MEMFAULTENA_SHFT                                        0x10
#define HWIO_RPM_M3_SCS_SHCSR_MEMFAULTENA_ENUM_0B0_FVAL                                0x0
#define HWIO_RPM_M3_SCS_SHCSR_MEMFAULTENA_ENUM_0B1_FVAL                                0x1
#define HWIO_RPM_M3_SCS_SHCSR_SVCALLPENDED_BMSK                                     0x8000
#define HWIO_RPM_M3_SCS_SHCSR_SVCALLPENDED_SHFT                                        0xf
#define HWIO_RPM_M3_SCS_SHCSR_SVCALLPENDED_ENUM_0B0_FVAL                               0x0
#define HWIO_RPM_M3_SCS_SHCSR_SVCALLPENDED_ENUM_0B1_FVAL                               0x1
#define HWIO_RPM_M3_SCS_SHCSR_BUSFAULTPENDED_BMSK                                   0x4000
#define HWIO_RPM_M3_SCS_SHCSR_BUSFAULTPENDED_SHFT                                      0xe
#define HWIO_RPM_M3_SCS_SHCSR_BUSFAULTPENDED_ENUM_0B0_FVAL                             0x0
#define HWIO_RPM_M3_SCS_SHCSR_BUSFAULTPENDED_ENUM_0B1_FVAL                             0x1
#define HWIO_RPM_M3_SCS_SHCSR_MEMFAULTPENDED_BMSK                                   0x2000
#define HWIO_RPM_M3_SCS_SHCSR_MEMFAULTPENDED_SHFT                                      0xd
#define HWIO_RPM_M3_SCS_SHCSR_MEMFAULTPENDED_ENUM_0B0_FVAL                             0x0
#define HWIO_RPM_M3_SCS_SHCSR_MEMFAULTPENDED_ENUM_0B1_FVAL                             0x1
#define HWIO_RPM_M3_SCS_SHCSR_USGFAULTPENDED_BMSK                                   0x1000
#define HWIO_RPM_M3_SCS_SHCSR_USGFAULTPENDED_SHFT                                      0xc
#define HWIO_RPM_M3_SCS_SHCSR_USGFAULTPENDED_ENUM_0B0_FVAL                             0x0
#define HWIO_RPM_M3_SCS_SHCSR_USGFAULTPENDED_ENUM_0B1_FVAL                             0x1
#define HWIO_RPM_M3_SCS_SHCSR_SYSTICKACT_BMSK                                        0x800
#define HWIO_RPM_M3_SCS_SHCSR_SYSTICKACT_SHFT                                          0xb
#define HWIO_RPM_M3_SCS_SHCSR_SYSTICKACT_ENUM_0B0_FVAL                                 0x0
#define HWIO_RPM_M3_SCS_SHCSR_SYSTICKACT_ENUM_0B1_FVAL                                 0x1
#define HWIO_RPM_M3_SCS_SHCSR_PENDSVACT_BMSK                                         0x400
#define HWIO_RPM_M3_SCS_SHCSR_PENDSVACT_SHFT                                           0xa
#define HWIO_RPM_M3_SCS_SHCSR_PENDSVACT_ENUM_0B0_FVAL                                  0x0
#define HWIO_RPM_M3_SCS_SHCSR_PENDSVACT_ENUM_0B1_FVAL                                  0x1
#define HWIO_RPM_M3_SCS_SHCSR_MONITORACT_BMSK                                        0x100
#define HWIO_RPM_M3_SCS_SHCSR_MONITORACT_SHFT                                          0x8
#define HWIO_RPM_M3_SCS_SHCSR_MONITORACT_ENUM_0B0_FVAL                                 0x0
#define HWIO_RPM_M3_SCS_SHCSR_MONITORACT_ENUM_0B1_FVAL                                 0x1
#define HWIO_RPM_M3_SCS_SHCSR_SVCALLACT_BMSK                                          0x80
#define HWIO_RPM_M3_SCS_SHCSR_SVCALLACT_SHFT                                           0x7
#define HWIO_RPM_M3_SCS_SHCSR_SVCALLACT_ENUM_0B0_FVAL                                  0x0
#define HWIO_RPM_M3_SCS_SHCSR_SVCALLACT_ENUM_0B1_FVAL                                  0x1
#define HWIO_RPM_M3_SCS_SHCSR_USGFAULTACT_BMSK                                         0x8
#define HWIO_RPM_M3_SCS_SHCSR_USGFAULTACT_SHFT                                         0x3
#define HWIO_RPM_M3_SCS_SHCSR_USGFAULTACT_ENUM_0B0_FVAL                                0x0
#define HWIO_RPM_M3_SCS_SHCSR_USGFAULTACT_ENUM_0B1_FVAL                                0x1
#define HWIO_RPM_M3_SCS_SHCSR_BUSFAULTACT_BMSK                                         0x2
#define HWIO_RPM_M3_SCS_SHCSR_BUSFAULTACT_SHFT                                         0x1
#define HWIO_RPM_M3_SCS_SHCSR_BUSFAULTACT_ENUM_0B0_FVAL                                0x0
#define HWIO_RPM_M3_SCS_SHCSR_BUSFAULTACT_ENUM_0B1_FVAL                                0x1
#define HWIO_RPM_M3_SCS_SHCSR_MEMFAULTACT_BMSK                                         0x1
#define HWIO_RPM_M3_SCS_SHCSR_MEMFAULTACT_SHFT                                         0x0
#define HWIO_RPM_M3_SCS_SHCSR_MEMFAULTACT_ENUM_0B0_FVAL                                0x0
#define HWIO_RPM_M3_SCS_SHCSR_MEMFAULTACT_ENUM_0B1_FVAL                                0x1

#define HWIO_RPM_M3_SCS_CFSR_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x0000ed28)
#define HWIO_RPM_M3_SCS_CFSR_RMSK                                                0x30f9f9b
#define HWIO_RPM_M3_SCS_CFSR_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_CFSR_ADDR, HWIO_RPM_M3_SCS_CFSR_RMSK)
#define HWIO_RPM_M3_SCS_CFSR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_CFSR_ADDR, m)
#define HWIO_RPM_M3_SCS_CFSR_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_CFSR_ADDR,v)
#define HWIO_RPM_M3_SCS_CFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_CFSR_ADDR,m,v,HWIO_RPM_M3_SCS_CFSR_IN)
#define HWIO_RPM_M3_SCS_CFSR_DIVBYZERO_BMSK                                      0x2000000
#define HWIO_RPM_M3_SCS_CFSR_DIVBYZERO_SHFT                                           0x19
#define HWIO_RPM_M3_SCS_CFSR_UNALIGNED_BMSK                                      0x1000000
#define HWIO_RPM_M3_SCS_CFSR_UNALIGNED_SHFT                                           0x18
#define HWIO_RPM_M3_SCS_CFSR_NOCP_BMSK                                             0x80000
#define HWIO_RPM_M3_SCS_CFSR_NOCP_SHFT                                                0x13
#define HWIO_RPM_M3_SCS_CFSR_INVPC_BMSK                                            0x40000
#define HWIO_RPM_M3_SCS_CFSR_INVPC_SHFT                                               0x12
#define HWIO_RPM_M3_SCS_CFSR_INVSTATE_BMSK                                         0x20000
#define HWIO_RPM_M3_SCS_CFSR_INVSTATE_SHFT                                            0x11
#define HWIO_RPM_M3_SCS_CFSR_UNDEFINSTR_BMSK                                       0x10000
#define HWIO_RPM_M3_SCS_CFSR_UNDEFINSTR_SHFT                                          0x10
#define HWIO_RPM_M3_SCS_CFSR_BFARVALID_BMSK                                         0x8000
#define HWIO_RPM_M3_SCS_CFSR_BFARVALID_SHFT                                            0xf
#define HWIO_RPM_M3_SCS_CFSR_STKERR_BMSK                                            0x1000
#define HWIO_RPM_M3_SCS_CFSR_STKERR_SHFT                                               0xc
#define HWIO_RPM_M3_SCS_CFSR_UNSTKERR_BMSK                                           0x800
#define HWIO_RPM_M3_SCS_CFSR_UNSTKERR_SHFT                                             0xb
#define HWIO_RPM_M3_SCS_CFSR_IMPRECISERR_BMSK                                        0x400
#define HWIO_RPM_M3_SCS_CFSR_IMPRECISERR_SHFT                                          0xa
#define HWIO_RPM_M3_SCS_CFSR_PRECISERR_BMSK                                          0x200
#define HWIO_RPM_M3_SCS_CFSR_PRECISERR_SHFT                                            0x9
#define HWIO_RPM_M3_SCS_CFSR_IBUSERR_BMSK                                            0x100
#define HWIO_RPM_M3_SCS_CFSR_IBUSERR_SHFT                                              0x8
#define HWIO_RPM_M3_SCS_CFSR_MMARVALID_BMSK                                           0x80
#define HWIO_RPM_M3_SCS_CFSR_MMARVALID_SHFT                                            0x7
#define HWIO_RPM_M3_SCS_CFSR_MSTKERR_BMSK                                             0x10
#define HWIO_RPM_M3_SCS_CFSR_MSTKERR_SHFT                                              0x4
#define HWIO_RPM_M3_SCS_CFSR_MUNSTKERR_BMSK                                            0x8
#define HWIO_RPM_M3_SCS_CFSR_MUNSTKERR_SHFT                                            0x3
#define HWIO_RPM_M3_SCS_CFSR_DACCVIOL_BMSK                                             0x2
#define HWIO_RPM_M3_SCS_CFSR_DACCVIOL_SHFT                                             0x1
#define HWIO_RPM_M3_SCS_CFSR_IACCVIOL_BMSK                                             0x1
#define HWIO_RPM_M3_SCS_CFSR_IACCVIOL_SHFT                                             0x0

#define HWIO_RPM_M3_SCS_HFSR_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x0000ed2c)
#define HWIO_RPM_M3_SCS_HFSR_RMSK                                               0xc0000002
#define HWIO_RPM_M3_SCS_HFSR_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_HFSR_ADDR, HWIO_RPM_M3_SCS_HFSR_RMSK)
#define HWIO_RPM_M3_SCS_HFSR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_HFSR_ADDR, m)
#define HWIO_RPM_M3_SCS_HFSR_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_HFSR_ADDR,v)
#define HWIO_RPM_M3_SCS_HFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_HFSR_ADDR,m,v,HWIO_RPM_M3_SCS_HFSR_IN)
#define HWIO_RPM_M3_SCS_HFSR_DEBUGEVT_BMSK                                      0x80000000
#define HWIO_RPM_M3_SCS_HFSR_DEBUGEVT_SHFT                                            0x1f
#define HWIO_RPM_M3_SCS_HFSR_FORCED_BMSK                                        0x40000000
#define HWIO_RPM_M3_SCS_HFSR_FORCED_SHFT                                              0x1e
#define HWIO_RPM_M3_SCS_HFSR_VECTTBL_BMSK                                              0x2
#define HWIO_RPM_M3_SCS_HFSR_VECTTBL_SHFT                                              0x1

#define HWIO_RPM_M3_SCS_DFSR_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x0000ed30)
#define HWIO_RPM_M3_SCS_DFSR_RMSK                                                     0x1f
#define HWIO_RPM_M3_SCS_DFSR_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_DFSR_ADDR, HWIO_RPM_M3_SCS_DFSR_RMSK)
#define HWIO_RPM_M3_SCS_DFSR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_DFSR_ADDR, m)
#define HWIO_RPM_M3_SCS_DFSR_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_DFSR_ADDR,v)
#define HWIO_RPM_M3_SCS_DFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_DFSR_ADDR,m,v,HWIO_RPM_M3_SCS_DFSR_IN)
#define HWIO_RPM_M3_SCS_DFSR_EXTERNAL_BMSK                                            0x10
#define HWIO_RPM_M3_SCS_DFSR_EXTERNAL_SHFT                                             0x4
#define HWIO_RPM_M3_SCS_DFSR_EXTERNAL_ENUM_0B0_FVAL                                    0x0
#define HWIO_RPM_M3_SCS_DFSR_EXTERNAL_ENUM_0B1_FVAL                                    0x1
#define HWIO_RPM_M3_SCS_DFSR_VCATCH_BMSK                                               0x8
#define HWIO_RPM_M3_SCS_DFSR_VCATCH_SHFT                                               0x3
#define HWIO_RPM_M3_SCS_DFSR_VCATCH_ENUM_0B0_FVAL                                      0x0
#define HWIO_RPM_M3_SCS_DFSR_VCATCH_ENUM_0B1_FVAL                                      0x1
#define HWIO_RPM_M3_SCS_DFSR_DWTTRAP_BMSK                                              0x4
#define HWIO_RPM_M3_SCS_DFSR_DWTTRAP_SHFT                                              0x2
#define HWIO_RPM_M3_SCS_DFSR_DWTTRAP_ENUM_0B0_FVAL                                     0x0
#define HWIO_RPM_M3_SCS_DFSR_DWTTRAP_ENUM_0B1_FVAL                                     0x1
#define HWIO_RPM_M3_SCS_DFSR_BKPT_BMSK                                                 0x2
#define HWIO_RPM_M3_SCS_DFSR_BKPT_SHFT                                                 0x1
#define HWIO_RPM_M3_SCS_DFSR_BKPT_ENUM_0B0_FVAL                                        0x0
#define HWIO_RPM_M3_SCS_DFSR_BKPT_ENUM_0B1_FVAL                                        0x1
#define HWIO_RPM_M3_SCS_DFSR_HALTED_BMSK                                               0x1
#define HWIO_RPM_M3_SCS_DFSR_HALTED_SHFT                                               0x0
#define HWIO_RPM_M3_SCS_DFSR_HALTED_ENUM_0B0_FVAL                                      0x0
#define HWIO_RPM_M3_SCS_DFSR_HALTED_ENUM_0B1_FVAL                                      0x1

#define HWIO_RPM_M3_SCS_MMFAR_ADDR                                              (RPM_M3_PPB_INT_REG_BASE      + 0x0000ed34)
#define HWIO_RPM_M3_SCS_MMFAR_RMSK                                              0xffffffff
#define HWIO_RPM_M3_SCS_MMFAR_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_MMFAR_ADDR, HWIO_RPM_M3_SCS_MMFAR_RMSK)
#define HWIO_RPM_M3_SCS_MMFAR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_MMFAR_ADDR, m)
#define HWIO_RPM_M3_SCS_MMFAR_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_MMFAR_ADDR,v)
#define HWIO_RPM_M3_SCS_MMFAR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_MMFAR_ADDR,m,v,HWIO_RPM_M3_SCS_MMFAR_IN)
#define HWIO_RPM_M3_SCS_MMFAR_ADDRESS_BMSK                                      0xffffffff
#define HWIO_RPM_M3_SCS_MMFAR_ADDRESS_SHFT                                             0x0

#define HWIO_RPM_M3_SCS_BFAR_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x0000ed38)
#define HWIO_RPM_M3_SCS_BFAR_RMSK                                               0xffffffff
#define HWIO_RPM_M3_SCS_BFAR_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_BFAR_ADDR, HWIO_RPM_M3_SCS_BFAR_RMSK)
#define HWIO_RPM_M3_SCS_BFAR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_BFAR_ADDR, m)
#define HWIO_RPM_M3_SCS_BFAR_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_BFAR_ADDR,v)
#define HWIO_RPM_M3_SCS_BFAR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_BFAR_ADDR,m,v,HWIO_RPM_M3_SCS_BFAR_IN)
#define HWIO_RPM_M3_SCS_BFAR_ADDRESS_BMSK                                       0xffffffff
#define HWIO_RPM_M3_SCS_BFAR_ADDRESS_SHFT                                              0x0

#define HWIO_RPM_M3_SCS_AFSR_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x0000ed3c)
#define HWIO_RPM_M3_SCS_AFSR_RMSK                                               0xffffffff
#define HWIO_RPM_M3_SCS_AFSR_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_AFSR_ADDR, HWIO_RPM_M3_SCS_AFSR_RMSK)
#define HWIO_RPM_M3_SCS_AFSR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_AFSR_ADDR, m)
#define HWIO_RPM_M3_SCS_AFSR_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_AFSR_ADDR,v)
#define HWIO_RPM_M3_SCS_AFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_AFSR_ADDR,m,v,HWIO_RPM_M3_SCS_AFSR_IN)
#define HWIO_RPM_M3_SCS_AFSR_IMPDEF_BMSK                                        0xffffffff
#define HWIO_RPM_M3_SCS_AFSR_IMPDEF_SHFT                                               0x0

#define HWIO_RPM_M3_SCS_ID_PFR0_ADDR                                            (RPM_M3_PPB_INT_REG_BASE      + 0x0000ed40)
#define HWIO_RPM_M3_SCS_ID_PFR0_RMSK                                                  0xff
#define HWIO_RPM_M3_SCS_ID_PFR0_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_ID_PFR0_ADDR, HWIO_RPM_M3_SCS_ID_PFR0_RMSK)
#define HWIO_RPM_M3_SCS_ID_PFR0_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_ID_PFR0_ADDR, m)
#define HWIO_RPM_M3_SCS_ID_PFR0_STATE1_BMSK                                           0xf0
#define HWIO_RPM_M3_SCS_ID_PFR0_STATE1_SHFT                                            0x4
#define HWIO_RPM_M3_SCS_ID_PFR0_STATE1_ENUM_0B0000_FVAL                                0x0
#define HWIO_RPM_M3_SCS_ID_PFR0_STATE1_ENUM_0B0001_FVAL                                0x1
#define HWIO_RPM_M3_SCS_ID_PFR0_STATE1_ENUM_0B0010_FVAL                                0x2
#define HWIO_RPM_M3_SCS_ID_PFR0_STATE1_ENUM_0B0011_FVAL                                0x3
#define HWIO_RPM_M3_SCS_ID_PFR0_STATE0_BMSK                                            0xf
#define HWIO_RPM_M3_SCS_ID_PFR0_STATE0_SHFT                                            0x0
#define HWIO_RPM_M3_SCS_ID_PFR0_STATE0_ENUM_0B0000_FVAL                                0x0
#define HWIO_RPM_M3_SCS_ID_PFR0_STATE0_ENUM_0B0001_FVAL                                0x1

#define HWIO_RPM_M3_SCS_ID_PFR1_ADDR                                            (RPM_M3_PPB_INT_REG_BASE      + 0x0000ed44)
#define HWIO_RPM_M3_SCS_ID_PFR1_RMSK                                                 0xf00
#define HWIO_RPM_M3_SCS_ID_PFR1_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_ID_PFR1_ADDR, HWIO_RPM_M3_SCS_ID_PFR1_RMSK)
#define HWIO_RPM_M3_SCS_ID_PFR1_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_ID_PFR1_ADDR, m)
#define HWIO_RPM_M3_SCS_ID_PFR1_MICROCONTROLLER_PROGRAMMERS_MODEL_BMSK               0xf00
#define HWIO_RPM_M3_SCS_ID_PFR1_MICROCONTROLLER_PROGRAMMERS_MODEL_SHFT                 0x8
#define HWIO_RPM_M3_SCS_ID_PFR1_MICROCONTROLLER_PROGRAMMERS_MODEL_ENUM_0B0000_FVAL        0x0
#define HWIO_RPM_M3_SCS_ID_PFR1_MICROCONTROLLER_PROGRAMMERS_MODEL_ENUM_0B0010_FVAL        0x2

#define HWIO_RPM_M3_SCS_ID_DFR0_ADDR                                            (RPM_M3_PPB_INT_REG_BASE      + 0x0000ed48)
#define HWIO_RPM_M3_SCS_ID_DFR0_RMSK                                              0xf00000
#define HWIO_RPM_M3_SCS_ID_DFR0_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_ID_DFR0_ADDR, HWIO_RPM_M3_SCS_ID_DFR0_RMSK)
#define HWIO_RPM_M3_SCS_ID_DFR0_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_ID_DFR0_ADDR, m)
#define HWIO_RPM_M3_SCS_ID_DFR0_MICROCONTROLLER_DEBUG_MODEL_BMSK                  0xf00000
#define HWIO_RPM_M3_SCS_ID_DFR0_MICROCONTROLLER_DEBUG_MODEL_SHFT                      0x14
#define HWIO_RPM_M3_SCS_ID_DFR0_MICROCONTROLLER_DEBUG_MODEL_ENUM_0B0000_FVAL           0x0
#define HWIO_RPM_M3_SCS_ID_DFR0_MICROCONTROLLER_DEBUG_MODEL_ENUM_0B0001_FVAL           0x1

#define HWIO_RPM_M3_SCS_ID_AFR0_ADDR                                            (RPM_M3_PPB_INT_REG_BASE      + 0x0000ed4c)
#define HWIO_RPM_M3_SCS_ID_AFR0_RMSK                                            0xffffffff
#define HWIO_RPM_M3_SCS_ID_AFR0_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_ID_AFR0_ADDR, HWIO_RPM_M3_SCS_ID_AFR0_RMSK)
#define HWIO_RPM_M3_SCS_ID_AFR0_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_ID_AFR0_ADDR, m)
#define HWIO_RPM_M3_SCS_ID_AFR0_SCS_ID_AFR0_BMSK                                0xffffffff
#define HWIO_RPM_M3_SCS_ID_AFR0_SCS_ID_AFR0_SHFT                                       0x0

#define HWIO_RPM_M3_SCS_ID_MMFR0_ADDR                                           (RPM_M3_PPB_INT_REG_BASE      + 0x0000ed50)
#define HWIO_RPM_M3_SCS_ID_MMFR0_RMSK                                             0xf0fff0
#define HWIO_RPM_M3_SCS_ID_MMFR0_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_ID_MMFR0_ADDR, HWIO_RPM_M3_SCS_ID_MMFR0_RMSK)
#define HWIO_RPM_M3_SCS_ID_MMFR0_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_ID_MMFR0_ADDR, m)
#define HWIO_RPM_M3_SCS_ID_MMFR0_AUXILIARY_REGISTER_SUPPORT_BMSK                  0xf00000
#define HWIO_RPM_M3_SCS_ID_MMFR0_AUXILIARY_REGISTER_SUPPORT_SHFT                      0x14
#define HWIO_RPM_M3_SCS_ID_MMFR0_AUXILIARY_REGISTER_SUPPORT_ENUM_0B0000_FVAL           0x0
#define HWIO_RPM_M3_SCS_ID_MMFR0_AUXILIARY_REGISTER_SUPPORT_ENUM_0B0001_FVAL           0x1
#define HWIO_RPM_M3_SCS_ID_MMFR0_OUTER_NON_SHARABLE_SUPPORT_BMSK                    0xf000
#define HWIO_RPM_M3_SCS_ID_MMFR0_OUTER_NON_SHARABLE_SUPPORT_SHFT                       0xc
#define HWIO_RPM_M3_SCS_ID_MMFR0_OUTER_NON_SHARABLE_SUPPORT_ENUM_0B0000_FVAL           0x0
#define HWIO_RPM_M3_SCS_ID_MMFR0_OUTER_NON_SHARABLE_SUPPORT_ENUM_0B0001_FVAL           0x1
#define HWIO_RPM_M3_SCS_ID_MMFR0_CACHE_COHERENCE_SUPPORT_BMSK                        0xf00
#define HWIO_RPM_M3_SCS_ID_MMFR0_CACHE_COHERENCE_SUPPORT_SHFT                          0x8
#define HWIO_RPM_M3_SCS_ID_MMFR0_CACHE_COHERENCE_SUPPORT_ENUM_0B0000_FVAL              0x0
#define HWIO_RPM_M3_SCS_ID_MMFR0_CACHE_COHERENCE_SUPPORT_ENUM_0B0001_FVAL              0x1
#define HWIO_RPM_M3_SCS_ID_MMFR0_CACHE_COHERENCE_SUPPORT_ENUM_0B0010_FVAL              0x2
#define HWIO_RPM_M3_SCS_ID_MMFR0_CACHE_COHERENCE_SUPPORT_ENUM_0B0011_FVAL              0x3
#define HWIO_RPM_M3_SCS_ID_MMFR0_PMSA_SUPPORT_BMSK                                    0xf0
#define HWIO_RPM_M3_SCS_ID_MMFR0_PMSA_SUPPORT_SHFT                                     0x4
#define HWIO_RPM_M3_SCS_ID_MMFR0_PMSA_SUPPORT_ENUM_0B0000_FVAL                         0x0
#define HWIO_RPM_M3_SCS_ID_MMFR0_PMSA_SUPPORT_ENUM_0B0001_FVAL                         0x1
#define HWIO_RPM_M3_SCS_ID_MMFR0_PMSA_SUPPORT_ENUM_0B0010_FVAL                         0x2
#define HWIO_RPM_M3_SCS_ID_MMFR0_PMSA_SUPPORT_ENUM_0B0011_FVAL                         0x3

#define HWIO_RPM_M3_SCS_ID_MMFR1_ADDR                                           (RPM_M3_PPB_INT_REG_BASE      + 0x0000ed54)
#define HWIO_RPM_M3_SCS_ID_MMFR1_RMSK                                           0xffffffff
#define HWIO_RPM_M3_SCS_ID_MMFR1_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_ID_MMFR1_ADDR, HWIO_RPM_M3_SCS_ID_MMFR1_RMSK)
#define HWIO_RPM_M3_SCS_ID_MMFR1_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_ID_MMFR1_ADDR, m)
#define HWIO_RPM_M3_SCS_ID_MMFR1_SCS_ID_MMFR1_BMSK                              0xffffffff
#define HWIO_RPM_M3_SCS_ID_MMFR1_SCS_ID_MMFR1_SHFT                                     0x0

#define HWIO_RPM_M3_SCS_ID_MMFR2_ADDR                                           (RPM_M3_PPB_INT_REG_BASE      + 0x0000ed58)
#define HWIO_RPM_M3_SCS_ID_MMFR2_RMSK                                            0xf000000
#define HWIO_RPM_M3_SCS_ID_MMFR2_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_ID_MMFR2_ADDR, HWIO_RPM_M3_SCS_ID_MMFR2_RMSK)
#define HWIO_RPM_M3_SCS_ID_MMFR2_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_ID_MMFR2_ADDR, m)
#define HWIO_RPM_M3_SCS_ID_MMFR2_WAIT_FOR_INTERRUPT_STALLING_BMSK                0xf000000
#define HWIO_RPM_M3_SCS_ID_MMFR2_WAIT_FOR_INTERRUPT_STALLING_SHFT                     0x18
#define HWIO_RPM_M3_SCS_ID_MMFR2_WAIT_FOR_INTERRUPT_STALLING_ENUM_0B0000_FVAL          0x0
#define HWIO_RPM_M3_SCS_ID_MMFR2_WAIT_FOR_INTERRUPT_STALLING_ENUM_0B0001_FVAL          0x1

#define HWIO_RPM_M3_SCS_ID_MMFR3_ADDR                                           (RPM_M3_PPB_INT_REG_BASE      + 0x0000ed5c)
#define HWIO_RPM_M3_SCS_ID_MMFR3_RMSK                                           0xffffffff
#define HWIO_RPM_M3_SCS_ID_MMFR3_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_ID_MMFR3_ADDR, HWIO_RPM_M3_SCS_ID_MMFR3_RMSK)
#define HWIO_RPM_M3_SCS_ID_MMFR3_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_ID_MMFR3_ADDR, m)
#define HWIO_RPM_M3_SCS_ID_MMFR3_SCS_ID_MMFR3_BMSK                              0xffffffff
#define HWIO_RPM_M3_SCS_ID_MMFR3_SCS_ID_MMFR3_SHFT                                     0x0

#define HWIO_RPM_M3_SCS_ID_ISAR0_ADDR                                           (RPM_M3_PPB_INT_REG_BASE      + 0x0000ed60)
#define HWIO_RPM_M3_SCS_ID_ISAR0_RMSK                                            0xffffff0
#define HWIO_RPM_M3_SCS_ID_ISAR0_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_ID_ISAR0_ADDR, HWIO_RPM_M3_SCS_ID_ISAR0_RMSK)
#define HWIO_RPM_M3_SCS_ID_ISAR0_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_ID_ISAR0_ADDR, m)
#define HWIO_RPM_M3_SCS_ID_ISAR0_DIVIDE_INSTRS_BMSK                              0xf000000
#define HWIO_RPM_M3_SCS_ID_ISAR0_DIVIDE_INSTRS_SHFT                                   0x18
#define HWIO_RPM_M3_SCS_ID_ISAR0_DIVIDE_INSTRS_ENUM_0B0000_FVAL                        0x0
#define HWIO_RPM_M3_SCS_ID_ISAR0_DIVIDE_INSTRS_ENUM_0B0001_FVAL                        0x1
#define HWIO_RPM_M3_SCS_ID_ISAR0_DEBUG_INSTRS_BMSK                                0xf00000
#define HWIO_RPM_M3_SCS_ID_ISAR0_DEBUG_INSTRS_SHFT                                    0x14
#define HWIO_RPM_M3_SCS_ID_ISAR0_DEBUG_INSTRS_ENUM_0B0000_FVAL                         0x0
#define HWIO_RPM_M3_SCS_ID_ISAR0_DEBUG_INSTRS_ENUM_0B0001_FVAL                         0x1
#define HWIO_RPM_M3_SCS_ID_ISAR0_COPROC_INSTRS_BMSK                                0xf0000
#define HWIO_RPM_M3_SCS_ID_ISAR0_COPROC_INSTRS_SHFT                                   0x10
#define HWIO_RPM_M3_SCS_ID_ISAR0_COPROC_INSTRS_ENUM_0B0000_FVAL                        0x0
#define HWIO_RPM_M3_SCS_ID_ISAR0_COPROC_INSTRS_ENUM_0B0001_FVAL                        0x1
#define HWIO_RPM_M3_SCS_ID_ISAR0_COPROC_INSTRS_ENUM_0B0010_FVAL                        0x2
#define HWIO_RPM_M3_SCS_ID_ISAR0_COPROC_INSTRS_ENUM_0B0011_FVAL                        0x3
#define HWIO_RPM_M3_SCS_ID_ISAR0_COPROC_INSTRS_ENUM_0B0100_FVAL                        0x4
#define HWIO_RPM_M3_SCS_ID_ISAR0_CMPBRANCH_INSTRS_BMSK                              0xf000
#define HWIO_RPM_M3_SCS_ID_ISAR0_CMPBRANCH_INSTRS_SHFT                                 0xc
#define HWIO_RPM_M3_SCS_ID_ISAR0_CMPBRANCH_INSTRS_ENUM_0B0000_FVAL                     0x0
#define HWIO_RPM_M3_SCS_ID_ISAR0_CMPBRANCH_INSTRS_ENUM_0B0001_FVAL                     0x1
#define HWIO_RPM_M3_SCS_ID_ISAR0_BITFIELD_INSTRS_BMSK                                0xf00
#define HWIO_RPM_M3_SCS_ID_ISAR0_BITFIELD_INSTRS_SHFT                                  0x8
#define HWIO_RPM_M3_SCS_ID_ISAR0_BITFIELD_INSTRS_ENUM_0B0000_FVAL                      0x0
#define HWIO_RPM_M3_SCS_ID_ISAR0_BITFIELD_INSTRS_ENUM_0B0001_FVAL                      0x1
#define HWIO_RPM_M3_SCS_ID_ISAR0_BITCOUNT_INSTRS_BMSK                                 0xf0
#define HWIO_RPM_M3_SCS_ID_ISAR0_BITCOUNT_INSTRS_SHFT                                  0x4
#define HWIO_RPM_M3_SCS_ID_ISAR0_BITCOUNT_INSTRS_ENUM_0B0000_FVAL                      0x0
#define HWIO_RPM_M3_SCS_ID_ISAR0_BITCOUNT_INSTRS_ENUM_0B0001_FVAL                      0x1

#define HWIO_RPM_M3_SCS_ID_ISAR1_ADDR                                           (RPM_M3_PPB_INT_REG_BASE      + 0x0000ed64)
#define HWIO_RPM_M3_SCS_ID_ISAR1_RMSK                                            0xffff000
#define HWIO_RPM_M3_SCS_ID_ISAR1_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_ID_ISAR1_ADDR, HWIO_RPM_M3_SCS_ID_ISAR1_RMSK)
#define HWIO_RPM_M3_SCS_ID_ISAR1_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_ID_ISAR1_ADDR, m)
#define HWIO_RPM_M3_SCS_ID_ISAR1_INTERWORK_INSTRS_BMSK                           0xf000000
#define HWIO_RPM_M3_SCS_ID_ISAR1_INTERWORK_INSTRS_SHFT                                0x18
#define HWIO_RPM_M3_SCS_ID_ISAR1_INTERWORK_INSTRS_ENUM_0B0000_FVAL                     0x0
#define HWIO_RPM_M3_SCS_ID_ISAR1_INTERWORK_INSTRS_ENUM_0B0001_FVAL                     0x1
#define HWIO_RPM_M3_SCS_ID_ISAR1_INTERWORK_INSTRS_ENUM_0B0010_FVAL                     0x2
#define HWIO_RPM_M3_SCS_ID_ISAR1_INTERWORK_INSTRS_ENUM_0B0011_FVAL                     0x3
#define HWIO_RPM_M3_SCS_ID_ISAR1_IMMEDIATE_INSTRS_BMSK                            0xf00000
#define HWIO_RPM_M3_SCS_ID_ISAR1_IMMEDIATE_INSTRS_SHFT                                0x14
#define HWIO_RPM_M3_SCS_ID_ISAR1_IMMEDIATE_INSTRS_ENUM_0B0000_FVAL                     0x0
#define HWIO_RPM_M3_SCS_ID_ISAR1_IMMEDIATE_INSTRS_ENUM_0B0001_FVAL                     0x1
#define HWIO_RPM_M3_SCS_ID_ISAR1_IFTHEN_INSTRS_BMSK                                0xf0000
#define HWIO_RPM_M3_SCS_ID_ISAR1_IFTHEN_INSTRS_SHFT                                   0x10
#define HWIO_RPM_M3_SCS_ID_ISAR1_IFTHEN_INSTRS_ENUM_0B0000_FVAL                        0x0
#define HWIO_RPM_M3_SCS_ID_ISAR1_IFTHEN_INSTRS_ENUM_0B0001_FVAL                        0x1
#define HWIO_RPM_M3_SCS_ID_ISAR1_EXTEND_INSRS_BMSK                                  0xf000
#define HWIO_RPM_M3_SCS_ID_ISAR1_EXTEND_INSRS_SHFT                                     0xc
#define HWIO_RPM_M3_SCS_ID_ISAR1_EXTEND_INSRS_ENUM_0B0000_FVAL                         0x0
#define HWIO_RPM_M3_SCS_ID_ISAR1_EXTEND_INSRS_ENUM_0B0001_FVAL                         0x1
#define HWIO_RPM_M3_SCS_ID_ISAR1_EXTEND_INSRS_ENUM_0B0010_FVAL                         0x2

#define HWIO_RPM_M3_SCS_ID_ISAR2_ADDR                                           (RPM_M3_PPB_INT_REG_BASE      + 0x0000ed68)
#define HWIO_RPM_M3_SCS_ID_ISAR2_RMSK                                           0xf0ffffff
#define HWIO_RPM_M3_SCS_ID_ISAR2_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_ID_ISAR2_ADDR, HWIO_RPM_M3_SCS_ID_ISAR2_RMSK)
#define HWIO_RPM_M3_SCS_ID_ISAR2_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_ID_ISAR2_ADDR, m)
#define HWIO_RPM_M3_SCS_ID_ISAR2_REVERSAL_INSTRS_BMSK                           0xf0000000
#define HWIO_RPM_M3_SCS_ID_ISAR2_REVERSAL_INSTRS_SHFT                                 0x1c
#define HWIO_RPM_M3_SCS_ID_ISAR2_REVERSAL_INSTRS_ENUM_0B0000_FVAL                      0x0
#define HWIO_RPM_M3_SCS_ID_ISAR2_REVERSAL_INSTRS_ENUM_0B0001_FVAL                      0x1
#define HWIO_RPM_M3_SCS_ID_ISAR2_REVERSAL_INSTRS_ENUM_0B0010_FVAL                      0x2
#define HWIO_RPM_M3_SCS_ID_ISAR2_MULTU_INSTRS_BMSK                                0xf00000
#define HWIO_RPM_M3_SCS_ID_ISAR2_MULTU_INSTRS_SHFT                                    0x14
#define HWIO_RPM_M3_SCS_ID_ISAR2_MULTU_INSTRS_ENUM_0B0000_FVAL                         0x0
#define HWIO_RPM_M3_SCS_ID_ISAR2_MULTU_INSTRS_ENUM_0B0001_FVAL                         0x1
#define HWIO_RPM_M3_SCS_ID_ISAR2_MULTU_INSTRS_ENUM_0B0010_FVAL                         0x2
#define HWIO_RPM_M3_SCS_ID_ISAR2_MULTS_INSTRS_BMSK                                 0xf0000
#define HWIO_RPM_M3_SCS_ID_ISAR2_MULTS_INSTRS_SHFT                                    0x10
#define HWIO_RPM_M3_SCS_ID_ISAR2_MULTS_INSTRS_ENUM_0B0000_FVAL                         0x0
#define HWIO_RPM_M3_SCS_ID_ISAR2_MULTS_INSTRS_ENUM_0B0001_FVAL                         0x1
#define HWIO_RPM_M3_SCS_ID_ISAR2_MULTS_INSTRS_ENUM_0B0010_FVAL                         0x2
#define HWIO_RPM_M3_SCS_ID_ISAR2_MULTS_INSTRS_ENUM_0B0011_FVAL                         0x3
#define HWIO_RPM_M3_SCS_ID_ISAR2_MULT_INSTRS_BMSK                                   0xf000
#define HWIO_RPM_M3_SCS_ID_ISAR2_MULT_INSTRS_SHFT                                      0xc
#define HWIO_RPM_M3_SCS_ID_ISAR2_MULT_INSTRS_ENUM_0B0000_FVAL                          0x0
#define HWIO_RPM_M3_SCS_ID_ISAR2_MULT_INSTRS_ENUM_0B0001_FVAL                          0x1
#define HWIO_RPM_M3_SCS_ID_ISAR2_MULT_INSTRS_ENUM_0B0010_FVAL                          0x2
#define HWIO_RPM_M3_SCS_ID_ISAR2_MULTIACCESSINT_INSTRS_BMSK                          0xf00
#define HWIO_RPM_M3_SCS_ID_ISAR2_MULTIACCESSINT_INSTRS_SHFT                            0x8
#define HWIO_RPM_M3_SCS_ID_ISAR2_MULTIACCESSINT_INSTRS_ENUM_0B0000_FVAL                0x0
#define HWIO_RPM_M3_SCS_ID_ISAR2_MULTIACCESSINT_INSTRS_ENUM_0B0001_FVAL                0x1
#define HWIO_RPM_M3_SCS_ID_ISAR2_MULTIACCESSINT_INSTRS_ENUM_0B0010_FVAL                0x2
#define HWIO_RPM_M3_SCS_ID_ISAR2_MEMHINT_INSTRS_BMSK                                  0xf0
#define HWIO_RPM_M3_SCS_ID_ISAR2_MEMHINT_INSTRS_SHFT                                   0x4
#define HWIO_RPM_M3_SCS_ID_ISAR2_MEMHINT_INSTRS_ENUM_0B0000_FVAL                       0x0
#define HWIO_RPM_M3_SCS_ID_ISAR2_MEMHINT_INSTRS_ENUM_0B0001_FVAL                       0x1
#define HWIO_RPM_M3_SCS_ID_ISAR2_MEMHINT_INSTRS_ENUM_0B0010_FVAL                       0x2
#define HWIO_RPM_M3_SCS_ID_ISAR2_MEMHINT_INSTRS_ENUM_0B0011_FVAL                       0x3
#define HWIO_RPM_M3_SCS_ID_ISAR2_LOADSTORE_INSTRS_BMSK                                 0xf
#define HWIO_RPM_M3_SCS_ID_ISAR2_LOADSTORE_INSTRS_SHFT                                 0x0
#define HWIO_RPM_M3_SCS_ID_ISAR2_LOADSTORE_INSTRS_ENUM_0B0000_FVAL                     0x0
#define HWIO_RPM_M3_SCS_ID_ISAR2_LOADSTORE_INSTRS_ENUM_0B0001_FVAL                     0x1

#define HWIO_RPM_M3_SCS_ID_ISAR3_ADDR                                           (RPM_M3_PPB_INT_REG_BASE      + 0x0000ed6c)
#define HWIO_RPM_M3_SCS_ID_ISAR3_RMSK                                            0xfffffff
#define HWIO_RPM_M3_SCS_ID_ISAR3_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_ID_ISAR3_ADDR, HWIO_RPM_M3_SCS_ID_ISAR3_RMSK)
#define HWIO_RPM_M3_SCS_ID_ISAR3_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_ID_ISAR3_ADDR, m)
#define HWIO_RPM_M3_SCS_ID_ISAR3_TRUENOP_INSTRS_BMSK                             0xf000000
#define HWIO_RPM_M3_SCS_ID_ISAR3_TRUENOP_INSTRS_SHFT                                  0x18
#define HWIO_RPM_M3_SCS_ID_ISAR3_TRUENOP_INSTRS_ENUM_0B0000_FVAL                       0x0
#define HWIO_RPM_M3_SCS_ID_ISAR3_TRUENOP_INSTRS_ENUM_0B0001_FVAL                       0x1
#define HWIO_RPM_M3_SCS_ID_ISAR3_THUMBCOPY_INSTRS_BMSK                            0xf00000
#define HWIO_RPM_M3_SCS_ID_ISAR3_THUMBCOPY_INSTRS_SHFT                                0x14
#define HWIO_RPM_M3_SCS_ID_ISAR3_THUMBCOPY_INSTRS_ENUM_0B0000_FVAL                     0x0
#define HWIO_RPM_M3_SCS_ID_ISAR3_THUMBCOPY_INSTRS_ENUM_0B0001_FVAL                     0x1
#define HWIO_RPM_M3_SCS_ID_ISAR3_TABBRANCH_INSTRS_BMSK                             0xf0000
#define HWIO_RPM_M3_SCS_ID_ISAR3_TABBRANCH_INSTRS_SHFT                                0x10
#define HWIO_RPM_M3_SCS_ID_ISAR3_TABBRANCH_INSTRS_ENUM_0B0000_FVAL                     0x0
#define HWIO_RPM_M3_SCS_ID_ISAR3_TABBRANCH_INSTRS_ENUM_0B0001_FVAL                     0x1
#define HWIO_RPM_M3_SCS_ID_ISAR3_SYNCPRIM_INSTRS_BMSK                               0xf000
#define HWIO_RPM_M3_SCS_ID_ISAR3_SYNCPRIM_INSTRS_SHFT                                  0xc
#define HWIO_RPM_M3_SCS_ID_ISAR3_SYNCPRIM_INSTRS_ENUM_0B0000_FVAL                      0x0
#define HWIO_RPM_M3_SCS_ID_ISAR3_SYNCPRIM_INSTRS_ENUM_0B0001_FVAL                      0x1
#define HWIO_RPM_M3_SCS_ID_ISAR3_SYNCPRIM_INSTRS_ENUM_0B0010_FVAL                      0x2
#define HWIO_RPM_M3_SCS_ID_ISAR3_SVC_INSTRS_BMSK                                     0xf00
#define HWIO_RPM_M3_SCS_ID_ISAR3_SVC_INSTRS_SHFT                                       0x8
#define HWIO_RPM_M3_SCS_ID_ISAR3_SVC_INSTRS_ENUM_0B0000_FVAL                           0x0
#define HWIO_RPM_M3_SCS_ID_ISAR3_SVC_INSTRS_ENUM_0B0001_FVAL                           0x1
#define HWIO_RPM_M3_SCS_ID_ISAR3_SIMD_INSTRS_BMSK                                     0xf0
#define HWIO_RPM_M3_SCS_ID_ISAR3_SIMD_INSTRS_SHFT                                      0x4
#define HWIO_RPM_M3_SCS_ID_ISAR3_SIMD_INSTRS_ENUM_0B0000_FVAL                          0x0
#define HWIO_RPM_M3_SCS_ID_ISAR3_SIMD_INSTRS_ENUM_0B0001_FVAL                          0x1
#define HWIO_RPM_M3_SCS_ID_ISAR3_SIMD_INSTRS_ENUM_0B0011_FVAL                          0x3
#define HWIO_RPM_M3_SCS_ID_ISAR3_SATRUATE_INSTRS_BMSK                                  0xf
#define HWIO_RPM_M3_SCS_ID_ISAR3_SATRUATE_INSTRS_SHFT                                  0x0
#define HWIO_RPM_M3_SCS_ID_ISAR3_SATRUATE_INSTRS_ENUM_0B0000_FVAL                      0x0
#define HWIO_RPM_M3_SCS_ID_ISAR3_SATRUATE_INSTRS_ENUM_0B0001_FVAL                      0x1

#define HWIO_RPM_M3_SCS_ID_ISAR4_ADDR                                           (RPM_M3_PPB_INT_REG_BASE      + 0x0000ed70)
#define HWIO_RPM_M3_SCS_ID_ISAR4_RMSK                                            0xfff0fff
#define HWIO_RPM_M3_SCS_ID_ISAR4_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_ID_ISAR4_ADDR, HWIO_RPM_M3_SCS_ID_ISAR4_RMSK)
#define HWIO_RPM_M3_SCS_ID_ISAR4_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_ID_ISAR4_ADDR, m)
#define HWIO_RPM_M3_SCS_ID_ISAR4_PSR_M_INSTRS_BMSK                               0xf000000
#define HWIO_RPM_M3_SCS_ID_ISAR4_PSR_M_INSTRS_SHFT                                    0x18
#define HWIO_RPM_M3_SCS_ID_ISAR4_PSR_M_INSTRS_ENUM_0B0000_FVAL                         0x0
#define HWIO_RPM_M3_SCS_ID_ISAR4_PSR_M_INSTRS_ENUM_0B0001_FVAL                         0x1
#define HWIO_RPM_M3_SCS_ID_ISAR4_SYNCPRIM_INSTRS_FRAC_BMSK                        0xf00000
#define HWIO_RPM_M3_SCS_ID_ISAR4_SYNCPRIM_INSTRS_FRAC_SHFT                            0x14
#define HWIO_RPM_M3_SCS_ID_ISAR4_SYNCPRIM_INSTRS_FRAC_ENUM_0B0000_FVAL                 0x0
#define HWIO_RPM_M3_SCS_ID_ISAR4_SYNCPRIM_INSTRS_FRAC_ENUM_0B0011_FVAL                 0x3
#define HWIO_RPM_M3_SCS_ID_ISAR4_BARRIER_INSTRS_BMSK                               0xf0000
#define HWIO_RPM_M3_SCS_ID_ISAR4_BARRIER_INSTRS_SHFT                                  0x10
#define HWIO_RPM_M3_SCS_ID_ISAR4_BARRIER_INSTRS_ENUM_0B0000_FVAL                       0x0
#define HWIO_RPM_M3_SCS_ID_ISAR4_BARRIER_INSTRS_ENUM_0B0001_FVAL                       0x1
#define HWIO_RPM_M3_SCS_ID_ISAR4_WRITEBACK_INSTRS_BMSK                               0xf00
#define HWIO_RPM_M3_SCS_ID_ISAR4_WRITEBACK_INSTRS_SHFT                                 0x8
#define HWIO_RPM_M3_SCS_ID_ISAR4_WRITEBACK_INSTRS_ENUM_0B0000_FVAL                     0x0
#define HWIO_RPM_M3_SCS_ID_ISAR4_WRITEBACK_INSTRS_ENUM_0B0001_FVAL                     0x1
#define HWIO_RPM_M3_SCS_ID_ISAR4_WITHSHIFTS_INSTRS_BMSK                               0xf0
#define HWIO_RPM_M3_SCS_ID_ISAR4_WITHSHIFTS_INSTRS_SHFT                                0x4
#define HWIO_RPM_M3_SCS_ID_ISAR4_WITHSHIFTS_INSTRS_ENUM_0B0000_FVAL                    0x0
#define HWIO_RPM_M3_SCS_ID_ISAR4_WITHSHIFTS_INSTRS_ENUM_0B0001_FVAL                    0x1
#define HWIO_RPM_M3_SCS_ID_ISAR4_WITHSHIFTS_INSTRS_ENUM_0B0010_FVAL                    0x3
#define HWIO_RPM_M3_SCS_ID_ISAR4_WITHSHIFTS_INSTRS_ENUM_0B0100_FVAL                    0x4
#define HWIO_RPM_M3_SCS_ID_ISAR4_UNPRIV_INSTRS_BMSK                                    0xf
#define HWIO_RPM_M3_SCS_ID_ISAR4_UNPRIV_INSTRS_SHFT                                    0x0
#define HWIO_RPM_M3_SCS_ID_ISAR4_UNPRIV_INSTRS_ENUM_0B0000_FVAL                        0x0
#define HWIO_RPM_M3_SCS_ID_ISAR4_UNPRIV_INSTRS_ENUM_0B0001_FVAL                        0x1
#define HWIO_RPM_M3_SCS_ID_ISAR4_UNPRIV_INSTRS_ENUM_0B0010_FVAL                        0x2

#define HWIO_RPM_M3_SCS_CPACR_ADDR                                              (RPM_M3_PPB_INT_REG_BASE      + 0x0000ed88)
#define HWIO_RPM_M3_SCS_CPACR_RMSK                                                0xf00000
#define HWIO_RPM_M3_SCS_CPACR_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_CPACR_ADDR, HWIO_RPM_M3_SCS_CPACR_RMSK)
#define HWIO_RPM_M3_SCS_CPACR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_CPACR_ADDR, m)
#define HWIO_RPM_M3_SCS_CPACR_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_CPACR_ADDR,v)
#define HWIO_RPM_M3_SCS_CPACR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_CPACR_ADDR,m,v,HWIO_RPM_M3_SCS_CPACR_IN)
#define HWIO_RPM_M3_SCS_CPACR_CP11_BMSK                                           0xc00000
#define HWIO_RPM_M3_SCS_CPACR_CP11_SHFT                                               0x16
#define HWIO_RPM_M3_SCS_CPACR_CP10_BMSK                                           0x300000
#define HWIO_RPM_M3_SCS_CPACR_CP10_SHFT                                               0x14

#define HWIO_RPM_M3_SCS_MPU_TYPE_ADDR                                           (RPM_M3_PPB_INT_REG_BASE      + 0x0000ed90)
#define HWIO_RPM_M3_SCS_MPU_TYPE_RMSK                                             0xffff01
#define HWIO_RPM_M3_SCS_MPU_TYPE_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_MPU_TYPE_ADDR, HWIO_RPM_M3_SCS_MPU_TYPE_RMSK)
#define HWIO_RPM_M3_SCS_MPU_TYPE_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_MPU_TYPE_ADDR, m)
#define HWIO_RPM_M3_SCS_MPU_TYPE_IREGION_BMSK                                     0xff0000
#define HWIO_RPM_M3_SCS_MPU_TYPE_IREGION_SHFT                                         0x10
#define HWIO_RPM_M3_SCS_MPU_TYPE_DREGION_BMSK                                       0xff00
#define HWIO_RPM_M3_SCS_MPU_TYPE_DREGION_SHFT                                          0x8
#define HWIO_RPM_M3_SCS_MPU_TYPE_SEPARATE_BMSK                                         0x1
#define HWIO_RPM_M3_SCS_MPU_TYPE_SEPARATE_SHFT                                         0x0

#define HWIO_RPM_M3_SCS_MPU_CTRL_ADDR                                           (RPM_M3_PPB_INT_REG_BASE      + 0x0000ed94)
#define HWIO_RPM_M3_SCS_MPU_CTRL_RMSK                                                  0x7
#define HWIO_RPM_M3_SCS_MPU_CTRL_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_MPU_CTRL_ADDR, HWIO_RPM_M3_SCS_MPU_CTRL_RMSK)
#define HWIO_RPM_M3_SCS_MPU_CTRL_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_MPU_CTRL_ADDR, m)
#define HWIO_RPM_M3_SCS_MPU_CTRL_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_MPU_CTRL_ADDR,v)
#define HWIO_RPM_M3_SCS_MPU_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_MPU_CTRL_ADDR,m,v,HWIO_RPM_M3_SCS_MPU_CTRL_IN)
#define HWIO_RPM_M3_SCS_MPU_CTRL_PRIVDEFENA_BMSK                                       0x4
#define HWIO_RPM_M3_SCS_MPU_CTRL_PRIVDEFENA_SHFT                                       0x2
#define HWIO_RPM_M3_SCS_MPU_CTRL_HFNMIENA_BMSK                                         0x2
#define HWIO_RPM_M3_SCS_MPU_CTRL_HFNMIENA_SHFT                                         0x1
#define HWIO_RPM_M3_SCS_MPU_CTRL_ENABLE_BMSK                                           0x1
#define HWIO_RPM_M3_SCS_MPU_CTRL_ENABLE_SHFT                                           0x0
#define HWIO_RPM_M3_SCS_MPU_CTRL_ENABLE_ENUM_0B0_FVAL                                  0x0
#define HWIO_RPM_M3_SCS_MPU_CTRL_ENABLE_ENUM_0B1_FVAL                                  0x1

#define HWIO_RPM_M3_SCS_MPU_RNR_ADDR                                            (RPM_M3_PPB_INT_REG_BASE      + 0x0000ed98)
#define HWIO_RPM_M3_SCS_MPU_RNR_RMSK                                                  0xff
#define HWIO_RPM_M3_SCS_MPU_RNR_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_MPU_RNR_ADDR, HWIO_RPM_M3_SCS_MPU_RNR_RMSK)
#define HWIO_RPM_M3_SCS_MPU_RNR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_MPU_RNR_ADDR, m)
#define HWIO_RPM_M3_SCS_MPU_RNR_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_MPU_RNR_ADDR,v)
#define HWIO_RPM_M3_SCS_MPU_RNR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_MPU_RNR_ADDR,m,v,HWIO_RPM_M3_SCS_MPU_RNR_IN)
#define HWIO_RPM_M3_SCS_MPU_RNR_REGION_BMSK                                           0xff
#define HWIO_RPM_M3_SCS_MPU_RNR_REGION_SHFT                                            0x0

#define HWIO_RPM_M3_SCS_MPU_RBAR_ADDR                                           (RPM_M3_PPB_INT_REG_BASE      + 0x0000ed9c)
#define HWIO_RPM_M3_SCS_MPU_RBAR_RMSK                                           0xffffffff
#define HWIO_RPM_M3_SCS_MPU_RBAR_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_MPU_RBAR_ADDR, HWIO_RPM_M3_SCS_MPU_RBAR_RMSK)
#define HWIO_RPM_M3_SCS_MPU_RBAR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_MPU_RBAR_ADDR, m)
#define HWIO_RPM_M3_SCS_MPU_RBAR_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_MPU_RBAR_ADDR,v)
#define HWIO_RPM_M3_SCS_MPU_RBAR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_MPU_RBAR_ADDR,m,v,HWIO_RPM_M3_SCS_MPU_RBAR_IN)
#define HWIO_RPM_M3_SCS_MPU_RBAR_ADDR_BMSK                                      0xffffffe0
#define HWIO_RPM_M3_SCS_MPU_RBAR_ADDR_SHFT                                             0x5
#define HWIO_RPM_M3_SCS_MPU_RBAR_VALID_BMSK                                           0x10
#define HWIO_RPM_M3_SCS_MPU_RBAR_VALID_SHFT                                            0x4
#define HWIO_RPM_M3_SCS_MPU_RBAR_VALID_ENUM_0B0_FVAL                                   0x0
#define HWIO_RPM_M3_SCS_MPU_RBAR_VALID_ENUM_0B1_FVAL                                   0x1
#define HWIO_RPM_M3_SCS_MPU_RBAR_REGION_BMSK                                           0xf
#define HWIO_RPM_M3_SCS_MPU_RBAR_REGION_SHFT                                           0x0

#define HWIO_RPM_M3_SCS_MPU_RASR_ADDR                                           (RPM_M3_PPB_INT_REG_BASE      + 0x0000eda0)
#define HWIO_RPM_M3_SCS_MPU_RASR_RMSK                                           0x173fff3f
#define HWIO_RPM_M3_SCS_MPU_RASR_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_MPU_RASR_ADDR, HWIO_RPM_M3_SCS_MPU_RASR_RMSK)
#define HWIO_RPM_M3_SCS_MPU_RASR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_MPU_RASR_ADDR, m)
#define HWIO_RPM_M3_SCS_MPU_RASR_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_MPU_RASR_ADDR,v)
#define HWIO_RPM_M3_SCS_MPU_RASR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_MPU_RASR_ADDR,m,v,HWIO_RPM_M3_SCS_MPU_RASR_IN)
#define HWIO_RPM_M3_SCS_MPU_RASR_XN_BMSK                                        0x10000000
#define HWIO_RPM_M3_SCS_MPU_RASR_XN_SHFT                                              0x1c
#define HWIO_RPM_M3_SCS_MPU_RASR_XN_ENUM_0B0_FVAL                                      0x0
#define HWIO_RPM_M3_SCS_MPU_RASR_XN_ENUM_0B1_FVAL                                      0x1
#define HWIO_RPM_M3_SCS_MPU_RASR_AP_BMSK                                         0x7000000
#define HWIO_RPM_M3_SCS_MPU_RASR_AP_SHFT                                              0x18
#define HWIO_RPM_M3_SCS_MPU_RASR_AP_ENUM_0B000_FVAL                                    0x0
#define HWIO_RPM_M3_SCS_MPU_RASR_AP_ENUM_0B001_FVAL                                    0x1
#define HWIO_RPM_M3_SCS_MPU_RASR_AP_ENUM_0B010_FVAL                                    0x2
#define HWIO_RPM_M3_SCS_MPU_RASR_AP_ENUM_0B011_FVAL                                    0x3
#define HWIO_RPM_M3_SCS_MPU_RASR_AP_ENUM_0B101_FVAL                                    0x5
#define HWIO_RPM_M3_SCS_MPU_RASR_AP_ENUM_0B110_FVAL                                    0x6
#define HWIO_RPM_M3_SCS_MPU_RASR_AP_ENUM_0B111_FVAL                                    0x7
#define HWIO_RPM_M3_SCS_MPU_RASR_TEX_BMSK                                         0x380000
#define HWIO_RPM_M3_SCS_MPU_RASR_TEX_SHFT                                             0x13
#define HWIO_RPM_M3_SCS_MPU_RASR_S_BMSK                                            0x40000
#define HWIO_RPM_M3_SCS_MPU_RASR_S_SHFT                                               0x12
#define HWIO_RPM_M3_SCS_MPU_RASR_S_ENUM_0B0_FVAL                                       0x0
#define HWIO_RPM_M3_SCS_MPU_RASR_S_ENUM_0B1_FVAL                                       0x1
#define HWIO_RPM_M3_SCS_MPU_RASR_C_BMSK                                            0x20000
#define HWIO_RPM_M3_SCS_MPU_RASR_C_SHFT                                               0x11
#define HWIO_RPM_M3_SCS_MPU_RASR_C_ENUM_0B0_FVAL                                       0x0
#define HWIO_RPM_M3_SCS_MPU_RASR_C_ENUM_0B1_FVAL                                       0x1
#define HWIO_RPM_M3_SCS_MPU_RASR_B_BMSK                                            0x10000
#define HWIO_RPM_M3_SCS_MPU_RASR_B_SHFT                                               0x10
#define HWIO_RPM_M3_SCS_MPU_RASR_B_ENUM_0B0_FVAL                                       0x0
#define HWIO_RPM_M3_SCS_MPU_RASR_B_ENUM_0B1_FVAL                                       0x1
#define HWIO_RPM_M3_SCS_MPU_RASR_SRD_BMSK                                           0xff00
#define HWIO_RPM_M3_SCS_MPU_RASR_SRD_SHFT                                              0x8
#define HWIO_RPM_M3_SCS_MPU_RASR_SIZE_BMSK                                            0x3e
#define HWIO_RPM_M3_SCS_MPU_RASR_SIZE_SHFT                                             0x1
#define HWIO_RPM_M3_SCS_MPU_RASR_SIZE_ENUM_0B00100_FVAL                                0x4
#define HWIO_RPM_M3_SCS_MPU_RASR_SIZE_ENUM_0B00101_FVAL                                0x5
#define HWIO_RPM_M3_SCS_MPU_RASR_SIZE_ENUM_0B00110_FVAL                                0x6
#define HWIO_RPM_M3_SCS_MPU_RASR_SIZE_ENUM_0B00111_FVAL                                0x7
#define HWIO_RPM_M3_SCS_MPU_RASR_SIZE_ENUM_0B01000_FVAL                                0x8
#define HWIO_RPM_M3_SCS_MPU_RASR_SIZE_ENUM_0B01001_FVAL                                0x9
#define HWIO_RPM_M3_SCS_MPU_RASR_SIZE_ENUM_0B01010_FVAL                                0xa
#define HWIO_RPM_M3_SCS_MPU_RASR_SIZE_ENUM_0B01011_FVAL                                0xb
#define HWIO_RPM_M3_SCS_MPU_RASR_SIZE_ENUM_0B01100_FVAL                                0xc
#define HWIO_RPM_M3_SCS_MPU_RASR_SIZE_ENUM_0B01101_FVAL                                0xd
#define HWIO_RPM_M3_SCS_MPU_RASR_SIZE_ENUM_0B01110_FVAL                                0xe
#define HWIO_RPM_M3_SCS_MPU_RASR_SIZE_ENUM_0B01111_FVAL                                0xf
#define HWIO_RPM_M3_SCS_MPU_RASR_SIZE_ENUM_0B10000_FVAL                               0x10
#define HWIO_RPM_M3_SCS_MPU_RASR_SIZE_ENUM_0B10001_FVAL                               0x11
#define HWIO_RPM_M3_SCS_MPU_RASR_SIZE_ENUM_0B10010_FVAL                               0x12
#define HWIO_RPM_M3_SCS_MPU_RASR_SIZE_ENUM_0B10011_FVAL                               0x13
#define HWIO_RPM_M3_SCS_MPU_RASR_SIZE_ENUM_0B10100_FVAL                               0x14
#define HWIO_RPM_M3_SCS_MPU_RASR_SIZE_ENUM_0B10101_FVAL                               0x15
#define HWIO_RPM_M3_SCS_MPU_RASR_SIZE_ENUM_0B10110_FVAL                               0x16
#define HWIO_RPM_M3_SCS_MPU_RASR_SIZE_ENUM_0B10111_FVAL                               0x17
#define HWIO_RPM_M3_SCS_MPU_RASR_SIZE_ENUM_0B11000_FVAL                               0x18
#define HWIO_RPM_M3_SCS_MPU_RASR_SIZE_ENUM_0B11001_FVAL                               0x19
#define HWIO_RPM_M3_SCS_MPU_RASR_SIZE_ENUM_0B11010_FVAL                               0x1a
#define HWIO_RPM_M3_SCS_MPU_RASR_SIZE_ENUM_0B11011_FVAL                               0x1b
#define HWIO_RPM_M3_SCS_MPU_RASR_SIZE_ENUM_0B11100_FVAL                               0x1c
#define HWIO_RPM_M3_SCS_MPU_RASR_SIZE_ENUM_0B11101_FVAL                               0x1d
#define HWIO_RPM_M3_SCS_MPU_RASR_SIZE_ENUM_0B11110_FVAL                               0x1e
#define HWIO_RPM_M3_SCS_MPU_RASR_SIZE_ENUM_0B11111_FVAL                               0x1f
#define HWIO_RPM_M3_SCS_MPU_RASR_ENABLE_BMSK                                           0x1
#define HWIO_RPM_M3_SCS_MPU_RASR_ENABLE_SHFT                                           0x0

#define HWIO_RPM_M3_SCS_MPU_RBAR_A1_ADDR                                        (RPM_M3_PPB_INT_REG_BASE      + 0x0000eda4)
#define HWIO_RPM_M3_SCS_MPU_RBAR_A1_RMSK                                        0xffffffff
#define HWIO_RPM_M3_SCS_MPU_RBAR_A1_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_MPU_RBAR_A1_ADDR, HWIO_RPM_M3_SCS_MPU_RBAR_A1_RMSK)
#define HWIO_RPM_M3_SCS_MPU_RBAR_A1_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_MPU_RBAR_A1_ADDR, m)
#define HWIO_RPM_M3_SCS_MPU_RBAR_A1_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_MPU_RBAR_A1_ADDR,v)
#define HWIO_RPM_M3_SCS_MPU_RBAR_A1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_MPU_RBAR_A1_ADDR,m,v,HWIO_RPM_M3_SCS_MPU_RBAR_A1_IN)
#define HWIO_RPM_M3_SCS_MPU_RBAR_A1_SCS_MPU_RBAR_A1_BMSK                        0xffffffff
#define HWIO_RPM_M3_SCS_MPU_RBAR_A1_SCS_MPU_RBAR_A1_SHFT                               0x0

#define HWIO_RPM_M3_SCS_MPU_RASR_A1_ADDR                                        (RPM_M3_PPB_INT_REG_BASE      + 0x0000eda8)
#define HWIO_RPM_M3_SCS_MPU_RASR_A1_RMSK                                        0xffffffff
#define HWIO_RPM_M3_SCS_MPU_RASR_A1_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_MPU_RASR_A1_ADDR, HWIO_RPM_M3_SCS_MPU_RASR_A1_RMSK)
#define HWIO_RPM_M3_SCS_MPU_RASR_A1_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_MPU_RASR_A1_ADDR, m)
#define HWIO_RPM_M3_SCS_MPU_RASR_A1_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_MPU_RASR_A1_ADDR,v)
#define HWIO_RPM_M3_SCS_MPU_RASR_A1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_MPU_RASR_A1_ADDR,m,v,HWIO_RPM_M3_SCS_MPU_RASR_A1_IN)
#define HWIO_RPM_M3_SCS_MPU_RASR_A1_SCS_MPU_RASR_A1_BMSK                        0xffffffff
#define HWIO_RPM_M3_SCS_MPU_RASR_A1_SCS_MPU_RASR_A1_SHFT                               0x0

#define HWIO_RPM_M3_SCS_MPU_RBAR_A2_ADDR                                        (RPM_M3_PPB_INT_REG_BASE      + 0x0000edac)
#define HWIO_RPM_M3_SCS_MPU_RBAR_A2_RMSK                                        0xffffffff
#define HWIO_RPM_M3_SCS_MPU_RBAR_A2_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_MPU_RBAR_A2_ADDR, HWIO_RPM_M3_SCS_MPU_RBAR_A2_RMSK)
#define HWIO_RPM_M3_SCS_MPU_RBAR_A2_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_MPU_RBAR_A2_ADDR, m)
#define HWIO_RPM_M3_SCS_MPU_RBAR_A2_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_MPU_RBAR_A2_ADDR,v)
#define HWIO_RPM_M3_SCS_MPU_RBAR_A2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_MPU_RBAR_A2_ADDR,m,v,HWIO_RPM_M3_SCS_MPU_RBAR_A2_IN)
#define HWIO_RPM_M3_SCS_MPU_RBAR_A2_SCS_MPU_RBAR_A2_BMSK                        0xffffffff
#define HWIO_RPM_M3_SCS_MPU_RBAR_A2_SCS_MPU_RBAR_A2_SHFT                               0x0

#define HWIO_RPM_M3_SCS_MPU_RASR_A2_ADDR                                        (RPM_M3_PPB_INT_REG_BASE      + 0x0000edb0)
#define HWIO_RPM_M3_SCS_MPU_RASR_A2_RMSK                                        0xffffffff
#define HWIO_RPM_M3_SCS_MPU_RASR_A2_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_MPU_RASR_A2_ADDR, HWIO_RPM_M3_SCS_MPU_RASR_A2_RMSK)
#define HWIO_RPM_M3_SCS_MPU_RASR_A2_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_MPU_RASR_A2_ADDR, m)
#define HWIO_RPM_M3_SCS_MPU_RASR_A2_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_MPU_RASR_A2_ADDR,v)
#define HWIO_RPM_M3_SCS_MPU_RASR_A2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_MPU_RASR_A2_ADDR,m,v,HWIO_RPM_M3_SCS_MPU_RASR_A2_IN)
#define HWIO_RPM_M3_SCS_MPU_RASR_A2_SCS_MPU_RASR_A2_BMSK                        0xffffffff
#define HWIO_RPM_M3_SCS_MPU_RASR_A2_SCS_MPU_RASR_A2_SHFT                               0x0

#define HWIO_RPM_M3_SCS_MPU_RBAR_A3_ADDR                                        (RPM_M3_PPB_INT_REG_BASE      + 0x0000edb4)
#define HWIO_RPM_M3_SCS_MPU_RBAR_A3_RMSK                                        0xffffffff
#define HWIO_RPM_M3_SCS_MPU_RBAR_A3_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_MPU_RBAR_A3_ADDR, HWIO_RPM_M3_SCS_MPU_RBAR_A3_RMSK)
#define HWIO_RPM_M3_SCS_MPU_RBAR_A3_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_MPU_RBAR_A3_ADDR, m)
#define HWIO_RPM_M3_SCS_MPU_RBAR_A3_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_MPU_RBAR_A3_ADDR,v)
#define HWIO_RPM_M3_SCS_MPU_RBAR_A3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_MPU_RBAR_A3_ADDR,m,v,HWIO_RPM_M3_SCS_MPU_RBAR_A3_IN)
#define HWIO_RPM_M3_SCS_MPU_RBAR_A3_SCS_MPU_RBAR_A3_BMSK                        0xffffffff
#define HWIO_RPM_M3_SCS_MPU_RBAR_A3_SCS_MPU_RBAR_A3_SHFT                               0x0

#define HWIO_RPM_M3_SCS_MPU_RASR_A3_ADDR                                        (RPM_M3_PPB_INT_REG_BASE      + 0x0000edb8)
#define HWIO_RPM_M3_SCS_MPU_RASR_A3_RMSK                                        0xffffffff
#define HWIO_RPM_M3_SCS_MPU_RASR_A3_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_MPU_RASR_A3_ADDR, HWIO_RPM_M3_SCS_MPU_RASR_A3_RMSK)
#define HWIO_RPM_M3_SCS_MPU_RASR_A3_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_MPU_RASR_A3_ADDR, m)
#define HWIO_RPM_M3_SCS_MPU_RASR_A3_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_MPU_RASR_A3_ADDR,v)
#define HWIO_RPM_M3_SCS_MPU_RASR_A3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_MPU_RASR_A3_ADDR,m,v,HWIO_RPM_M3_SCS_MPU_RASR_A3_IN)
#define HWIO_RPM_M3_SCS_MPU_RASR_A3_SCS_MPU_RASR_A3_BMSK                        0xffffffff
#define HWIO_RPM_M3_SCS_MPU_RASR_A3_SCS_MPU_RASR_A3_SHFT                               0x0

#define HWIO_RPM_M3_SCS_DHCSR_ADDR                                              (RPM_M3_PPB_INT_REG_BASE      + 0x0000edf0)
#define HWIO_RPM_M3_SCS_DHCSR_RMSK                                               0x30f002f
#define HWIO_RPM_M3_SCS_DHCSR_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_DHCSR_ADDR, HWIO_RPM_M3_SCS_DHCSR_RMSK)
#define HWIO_RPM_M3_SCS_DHCSR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_DHCSR_ADDR, m)
#define HWIO_RPM_M3_SCS_DHCSR_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_DHCSR_ADDR,v)
#define HWIO_RPM_M3_SCS_DHCSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_DHCSR_ADDR,m,v,HWIO_RPM_M3_SCS_DHCSR_IN)
#define HWIO_RPM_M3_SCS_DHCSR_S_RESET_ST_BMSK                                    0x2000000
#define HWIO_RPM_M3_SCS_DHCSR_S_RESET_ST_SHFT                                         0x19
#define HWIO_RPM_M3_SCS_DHCSR_S_RETIRE_ST_BMSK                                   0x1000000
#define HWIO_RPM_M3_SCS_DHCSR_S_RETIRE_ST_SHFT                                        0x18
#define HWIO_RPM_M3_SCS_DHCSR_S_LOCKUP_BMSK                                        0x80000
#define HWIO_RPM_M3_SCS_DHCSR_S_LOCKUP_SHFT                                           0x13
#define HWIO_RPM_M3_SCS_DHCSR_S_SLEEP_BMSK                                         0x40000
#define HWIO_RPM_M3_SCS_DHCSR_S_SLEEP_SHFT                                            0x12
#define HWIO_RPM_M3_SCS_DHCSR_S_HALT_BMSK                                          0x20000
#define HWIO_RPM_M3_SCS_DHCSR_S_HALT_SHFT                                             0x11
#define HWIO_RPM_M3_SCS_DHCSR_S_REGRDY_BMSK                                        0x10000
#define HWIO_RPM_M3_SCS_DHCSR_S_REGRDY_SHFT                                           0x10
#define HWIO_RPM_M3_SCS_DHCSR_C_SNAPSTALL_BMSK                                        0x20
#define HWIO_RPM_M3_SCS_DHCSR_C_SNAPSTALL_SHFT                                         0x5
#define HWIO_RPM_M3_SCS_DHCSR_C_MASKINTS_BMSK                                          0x8
#define HWIO_RPM_M3_SCS_DHCSR_C_MASKINTS_SHFT                                          0x3
#define HWIO_RPM_M3_SCS_DHCSR_C_STEP_BMSK                                              0x4
#define HWIO_RPM_M3_SCS_DHCSR_C_STEP_SHFT                                              0x2
#define HWIO_RPM_M3_SCS_DHCSR_C_HALT_BMSK                                              0x2
#define HWIO_RPM_M3_SCS_DHCSR_C_HALT_SHFT                                              0x1
#define HWIO_RPM_M3_SCS_DHCSR_C_DEBUGEN_BMSK                                           0x1
#define HWIO_RPM_M3_SCS_DHCSR_C_DEBUGEN_SHFT                                           0x0

#define HWIO_RPM_M3_SCS_DCRSR_ADDR                                              (RPM_M3_PPB_INT_REG_BASE      + 0x0000edf4)
#define HWIO_RPM_M3_SCS_DCRSR_RMSK                                                 0x1001f
#define HWIO_RPM_M3_SCS_DCRSR_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_DCRSR_ADDR,v)
#define HWIO_RPM_M3_SCS_DCRSR_REGWNR_BMSK                                          0x10000
#define HWIO_RPM_M3_SCS_DCRSR_REGWNR_SHFT                                             0x10
#define HWIO_RPM_M3_SCS_DCRSR_REGSEL_BMSK                                             0x1f
#define HWIO_RPM_M3_SCS_DCRSR_REGSEL_SHFT                                              0x0
#define HWIO_RPM_M3_SCS_DCRSR_REGSEL_ENUM_0B00000_FVAL                                 0x0
#define HWIO_RPM_M3_SCS_DCRSR_REGSEL_ENUM_0B00001_FVAL                                 0x1
#define HWIO_RPM_M3_SCS_DCRSR_REGSEL_ENUM_0B00010_FVAL                                 0x2
#define HWIO_RPM_M3_SCS_DCRSR_REGSEL_ENUM_0B00011_FVAL                                 0x3
#define HWIO_RPM_M3_SCS_DCRSR_REGSEL_ENUM_0B00100_FVAL                                 0x4
#define HWIO_RPM_M3_SCS_DCRSR_REGSEL_ENUM_0B00101_FVAL                                 0x5
#define HWIO_RPM_M3_SCS_DCRSR_REGSEL_ENUM_0B00110_FVAL                                 0x6
#define HWIO_RPM_M3_SCS_DCRSR_REGSEL_ENUM_0B00111_FVAL                                 0x7
#define HWIO_RPM_M3_SCS_DCRSR_REGSEL_ENUM_0B01000_FVAL                                 0x8
#define HWIO_RPM_M3_SCS_DCRSR_REGSEL_ENUM_0B01001_FVAL                                 0x9
#define HWIO_RPM_M3_SCS_DCRSR_REGSEL_ENUM_0B01010_FVAL                                 0xa
#define HWIO_RPM_M3_SCS_DCRSR_REGSEL_ENUM_0B01011_FVAL                                 0xb
#define HWIO_RPM_M3_SCS_DCRSR_REGSEL_ENUM_0B01100_FVAL                                 0xc
#define HWIO_RPM_M3_SCS_DCRSR_REGSEL_ENUM_0B01101_FVAL                                 0xd
#define HWIO_RPM_M3_SCS_DCRSR_REGSEL_ENUM_0B01110_FVAL                                 0xe
#define HWIO_RPM_M3_SCS_DCRSR_REGSEL_ENUM_0B01111_FVAL                                 0xf
#define HWIO_RPM_M3_SCS_DCRSR_REGSEL_ENUM_0B10000_FVAL                                0x10
#define HWIO_RPM_M3_SCS_DCRSR_REGSEL_ENUM_0B10001_FVAL                                0x11
#define HWIO_RPM_M3_SCS_DCRSR_REGSEL_ENUM_0B10010_FVAL                                0x12
#define HWIO_RPM_M3_SCS_DCRSR_REGSEL_ENUM_0B10100_FVAL                                0x14

#define HWIO_RPM_M3_SCS_DCRDR_ADDR                                              (RPM_M3_PPB_INT_REG_BASE      + 0x0000edf8)
#define HWIO_RPM_M3_SCS_DCRDR_RMSK                                              0xffffffff
#define HWIO_RPM_M3_SCS_DCRDR_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_DCRDR_ADDR, HWIO_RPM_M3_SCS_DCRDR_RMSK)
#define HWIO_RPM_M3_SCS_DCRDR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_DCRDR_ADDR, m)
#define HWIO_RPM_M3_SCS_DCRDR_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_DCRDR_ADDR,v)
#define HWIO_RPM_M3_SCS_DCRDR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_DCRDR_ADDR,m,v,HWIO_RPM_M3_SCS_DCRDR_IN)
#define HWIO_RPM_M3_SCS_DCRDR_SCS_DCRDR_BMSK                                    0xffffffff
#define HWIO_RPM_M3_SCS_DCRDR_SCS_DCRDR_SHFT                                           0x0

#define HWIO_RPM_M3_SCS_DEMCR_ADDR                                              (RPM_M3_PPB_INT_REG_BASE      + 0x0000edfc)
#define HWIO_RPM_M3_SCS_DEMCR_RMSK                                               0x10f07f1
#define HWIO_RPM_M3_SCS_DEMCR_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_DEMCR_ADDR, HWIO_RPM_M3_SCS_DEMCR_RMSK)
#define HWIO_RPM_M3_SCS_DEMCR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_DEMCR_ADDR, m)
#define HWIO_RPM_M3_SCS_DEMCR_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_DEMCR_ADDR,v)
#define HWIO_RPM_M3_SCS_DEMCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_SCS_DEMCR_ADDR,m,v,HWIO_RPM_M3_SCS_DEMCR_IN)
#define HWIO_RPM_M3_SCS_DEMCR_TRCENA_BMSK                                        0x1000000
#define HWIO_RPM_M3_SCS_DEMCR_TRCENA_SHFT                                             0x18
#define HWIO_RPM_M3_SCS_DEMCR_MON_REQ_BMSK                                         0x80000
#define HWIO_RPM_M3_SCS_DEMCR_MON_REQ_SHFT                                            0x13
#define HWIO_RPM_M3_SCS_DEMCR_MON_REQ_ENUM_0B0_FVAL                                    0x0
#define HWIO_RPM_M3_SCS_DEMCR_MON_REQ_ENUM_0B1_FVAL                                    0x1
#define HWIO_RPM_M3_SCS_DEMCR_MON_STEP_BMSK                                        0x40000
#define HWIO_RPM_M3_SCS_DEMCR_MON_STEP_SHFT                                           0x12
#define HWIO_RPM_M3_SCS_DEMCR_MON_PEND_BMSK                                        0x20000
#define HWIO_RPM_M3_SCS_DEMCR_MON_PEND_SHFT                                           0x11
#define HWIO_RPM_M3_SCS_DEMCR_MON_EN_BMSK                                          0x10000
#define HWIO_RPM_M3_SCS_DEMCR_MON_EN_SHFT                                             0x10
#define HWIO_RPM_M3_SCS_DEMCR_VC_HARDERR_BMSK                                        0x400
#define HWIO_RPM_M3_SCS_DEMCR_VC_HARDERR_SHFT                                          0xa
#define HWIO_RPM_M3_SCS_DEMCR_VC_INTERR_BMSK                                         0x200
#define HWIO_RPM_M3_SCS_DEMCR_VC_INTERR_SHFT                                           0x9
#define HWIO_RPM_M3_SCS_DEMCR_VC_BUSERR_BMSK                                         0x100
#define HWIO_RPM_M3_SCS_DEMCR_VC_BUSERR_SHFT                                           0x8
#define HWIO_RPM_M3_SCS_DEMCR_VC_STATERR_BMSK                                         0x80
#define HWIO_RPM_M3_SCS_DEMCR_VC_STATERR_SHFT                                          0x7
#define HWIO_RPM_M3_SCS_DEMCR_VC_CHKERR_BMSK                                          0x40
#define HWIO_RPM_M3_SCS_DEMCR_VC_CHKERR_SHFT                                           0x6
#define HWIO_RPM_M3_SCS_DEMCR_VC_NOCPERR_BMSK                                         0x20
#define HWIO_RPM_M3_SCS_DEMCR_VC_NOCPERR_SHFT                                          0x5
#define HWIO_RPM_M3_SCS_DEMCR_VC_MMERR_BMSK                                           0x10
#define HWIO_RPM_M3_SCS_DEMCR_VC_MMERR_SHFT                                            0x4
#define HWIO_RPM_M3_SCS_DEMCR_VC_CORERESET_BMSK                                        0x1
#define HWIO_RPM_M3_SCS_DEMCR_VC_CORERESET_SHFT                                        0x0

#define HWIO_RPM_M3_SCS_STIR_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x0000ef00)
#define HWIO_RPM_M3_SCS_STIR_RMSK                                                    0x1ff
#define HWIO_RPM_M3_SCS_STIR_OUT(v)      \
        out_dword(HWIO_RPM_M3_SCS_STIR_ADDR,v)
#define HWIO_RPM_M3_SCS_STIR_INTID_BMSK                                              0x1ff
#define HWIO_RPM_M3_SCS_STIR_INTID_SHFT                                                0x0

#define HWIO_RPM_M3_SCS_PID4_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x0000efd0)
#define HWIO_RPM_M3_SCS_PID4_RMSK                                               0xffffffff
#define HWIO_RPM_M3_SCS_PID4_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_PID4_ADDR, HWIO_RPM_M3_SCS_PID4_RMSK)
#define HWIO_RPM_M3_SCS_PID4_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_PID4_ADDR, m)
#define HWIO_RPM_M3_SCS_PID4_SCS_PID4_BMSK                                      0xffffffff
#define HWIO_RPM_M3_SCS_PID4_SCS_PID4_SHFT                                             0x0

#define HWIO_RPM_M3_SCS_PID5_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x0000efd4)
#define HWIO_RPM_M3_SCS_PID5_RMSK                                               0xffffffff
#define HWIO_RPM_M3_SCS_PID5_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_PID5_ADDR, HWIO_RPM_M3_SCS_PID5_RMSK)
#define HWIO_RPM_M3_SCS_PID5_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_PID5_ADDR, m)
#define HWIO_RPM_M3_SCS_PID5_SCS_PID5_BMSK                                      0xffffffff
#define HWIO_RPM_M3_SCS_PID5_SCS_PID5_SHFT                                             0x0

#define HWIO_RPM_M3_SCS_PID6_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x0000efd8)
#define HWIO_RPM_M3_SCS_PID6_RMSK                                               0xffffffff
#define HWIO_RPM_M3_SCS_PID6_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_PID6_ADDR, HWIO_RPM_M3_SCS_PID6_RMSK)
#define HWIO_RPM_M3_SCS_PID6_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_PID6_ADDR, m)
#define HWIO_RPM_M3_SCS_PID6_SCS_PID6_BMSK                                      0xffffffff
#define HWIO_RPM_M3_SCS_PID6_SCS_PID6_SHFT                                             0x0

#define HWIO_RPM_M3_SCS_PID7_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x0000efdc)
#define HWIO_RPM_M3_SCS_PID7_RMSK                                               0xffffffff
#define HWIO_RPM_M3_SCS_PID7_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_PID7_ADDR, HWIO_RPM_M3_SCS_PID7_RMSK)
#define HWIO_RPM_M3_SCS_PID7_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_PID7_ADDR, m)
#define HWIO_RPM_M3_SCS_PID7_SCS_PID7_BMSK                                      0xffffffff
#define HWIO_RPM_M3_SCS_PID7_SCS_PID7_SHFT                                             0x0

#define HWIO_RPM_M3_SCS_PID0_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x0000efe0)
#define HWIO_RPM_M3_SCS_PID0_RMSK                                               0xffffffff
#define HWIO_RPM_M3_SCS_PID0_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_PID0_ADDR, HWIO_RPM_M3_SCS_PID0_RMSK)
#define HWIO_RPM_M3_SCS_PID0_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_PID0_ADDR, m)
#define HWIO_RPM_M3_SCS_PID0_SCS_PID0_BMSK                                      0xffffffff
#define HWIO_RPM_M3_SCS_PID0_SCS_PID0_SHFT                                             0x0

#define HWIO_RPM_M3_SCS_PID1_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x0000efe4)
#define HWIO_RPM_M3_SCS_PID1_RMSK                                               0xffffffff
#define HWIO_RPM_M3_SCS_PID1_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_PID1_ADDR, HWIO_RPM_M3_SCS_PID1_RMSK)
#define HWIO_RPM_M3_SCS_PID1_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_PID1_ADDR, m)
#define HWIO_RPM_M3_SCS_PID1_SCS_PID1_BMSK                                      0xffffffff
#define HWIO_RPM_M3_SCS_PID1_SCS_PID1_SHFT                                             0x0

#define HWIO_RPM_M3_SCS_PID2_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x0000efe8)
#define HWIO_RPM_M3_SCS_PID2_RMSK                                               0xffffffff
#define HWIO_RPM_M3_SCS_PID2_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_PID2_ADDR, HWIO_RPM_M3_SCS_PID2_RMSK)
#define HWIO_RPM_M3_SCS_PID2_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_PID2_ADDR, m)
#define HWIO_RPM_M3_SCS_PID2_SCS_PID2_BMSK                                      0xffffffff
#define HWIO_RPM_M3_SCS_PID2_SCS_PID2_SHFT                                             0x0

#define HWIO_RPM_M3_SCS_PID3_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x0000efec)
#define HWIO_RPM_M3_SCS_PID3_RMSK                                               0xffffffff
#define HWIO_RPM_M3_SCS_PID3_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_PID3_ADDR, HWIO_RPM_M3_SCS_PID3_RMSK)
#define HWIO_RPM_M3_SCS_PID3_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_PID3_ADDR, m)
#define HWIO_RPM_M3_SCS_PID3_SCS_PID3_BMSK                                      0xffffffff
#define HWIO_RPM_M3_SCS_PID3_SCS_PID3_SHFT                                             0x0

#define HWIO_RPM_M3_SCS_CID0_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x0000eff0)
#define HWIO_RPM_M3_SCS_CID0_RMSK                                               0xffffffff
#define HWIO_RPM_M3_SCS_CID0_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_CID0_ADDR, HWIO_RPM_M3_SCS_CID0_RMSK)
#define HWIO_RPM_M3_SCS_CID0_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_CID0_ADDR, m)
#define HWIO_RPM_M3_SCS_CID0_SCS_CID0_BMSK                                      0xffffffff
#define HWIO_RPM_M3_SCS_CID0_SCS_CID0_SHFT                                             0x0

#define HWIO_RPM_M3_SCS_CID1_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x0000eff4)
#define HWIO_RPM_M3_SCS_CID1_RMSK                                               0xffffffff
#define HWIO_RPM_M3_SCS_CID1_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_CID1_ADDR, HWIO_RPM_M3_SCS_CID1_RMSK)
#define HWIO_RPM_M3_SCS_CID1_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_CID1_ADDR, m)
#define HWIO_RPM_M3_SCS_CID1_SCS_CID1_BMSK                                      0xffffffff
#define HWIO_RPM_M3_SCS_CID1_SCS_CID1_SHFT                                             0x0

#define HWIO_RPM_M3_SCS_CID2_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x0000eff8)
#define HWIO_RPM_M3_SCS_CID2_RMSK                                               0xffffffff
#define HWIO_RPM_M3_SCS_CID2_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_CID2_ADDR, HWIO_RPM_M3_SCS_CID2_RMSK)
#define HWIO_RPM_M3_SCS_CID2_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_CID2_ADDR, m)
#define HWIO_RPM_M3_SCS_CID2_SCS_CID2_BMSK                                      0xffffffff
#define HWIO_RPM_M3_SCS_CID2_SCS_CID2_SHFT                                             0x0

#define HWIO_RPM_M3_SCS_CID3_ADDR                                               (RPM_M3_PPB_INT_REG_BASE      + 0x0000effc)
#define HWIO_RPM_M3_SCS_CID3_RMSK                                               0xffffffff
#define HWIO_RPM_M3_SCS_CID3_IN          \
        in_dword_masked(HWIO_RPM_M3_SCS_CID3_ADDR, HWIO_RPM_M3_SCS_CID3_RMSK)
#define HWIO_RPM_M3_SCS_CID3_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_SCS_CID3_ADDR, m)
#define HWIO_RPM_M3_SCS_CID3_SCS_CID3_BMSK                                      0xffffffff
#define HWIO_RPM_M3_SCS_CID3_SCS_CID3_SHFT                                             0x0

/*----------------------------------------------------------------------------
 * MODULE: RPM_M3_PPB_EXT
 *--------------------------------------------------------------------------*/

#define RPM_M3_PPB_EXT_REG_BASE                                                   (RPM_M3_CORTEXM3_T_BASE      + 0x00040000)

#define HWIO_RPM_M3_ETM_ETMCR_ADDR                                                (RPM_M3_PPB_EXT_REG_BASE      + 0x00001000)
#define HWIO_RPM_M3_ETM_ETMCR_RMSK                                                  0x232ff1
#define HWIO_RPM_M3_ETM_ETMCR_IN          \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMCR_ADDR, HWIO_RPM_M3_ETM_ETMCR_RMSK)
#define HWIO_RPM_M3_ETM_ETMCR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMCR_ADDR, m)
#define HWIO_RPM_M3_ETM_ETMCR_OUT(v)      \
        out_dword(HWIO_RPM_M3_ETM_ETMCR_ADDR,v)
#define HWIO_RPM_M3_ETM_ETMCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ETM_ETMCR_ADDR,m,v,HWIO_RPM_M3_ETM_ETMCR_IN)
#define HWIO_RPM_M3_ETM_ETMCR_PORT_SIZE_BIT_3_BMSK                                  0x200000
#define HWIO_RPM_M3_ETM_ETMCR_PORT_SIZE_BIT_3_SHFT                                      0x15
#define HWIO_RPM_M3_ETM_ETMCR_PORT_MODE_BITS_1_0_BMSK                                0x30000
#define HWIO_RPM_M3_ETM_ETMCR_PORT_MODE_BITS_1_0_SHFT                                   0x10
#define HWIO_RPM_M3_ETM_ETMCR_PORT_MODE_BIT_2_BMSK                                    0x2000
#define HWIO_RPM_M3_ETM_ETMCR_PORT_MODE_BIT_2_SHFT                                       0xd
#define HWIO_RPM_M3_ETM_ETMCR_ETMEN_BMSK                                               0x800
#define HWIO_RPM_M3_ETM_ETMCR_ETMEN_SHFT                                                 0xb
#define HWIO_RPM_M3_ETM_ETMCR_ETMEN_ENUM_0B0_FVAL                                        0x0
#define HWIO_RPM_M3_ETM_ETMCR_ETMEN_ENUM_0B1_FVAL                                        0x1
#define HWIO_RPM_M3_ETM_ETMCR_ETM_PROGRAMMING_BMSK                                     0x400
#define HWIO_RPM_M3_ETM_ETMCR_ETM_PROGRAMMING_SHFT                                       0xa
#define HWIO_RPM_M3_ETM_ETMCR_DEBUG_REQUEST_CONTROL_BMSK                               0x200
#define HWIO_RPM_M3_ETM_ETMCR_DEBUG_REQUEST_CONTROL_SHFT                                 0x9
#define HWIO_RPM_M3_ETM_ETMCR_BRANCH_OUTPUT_BMSK                                       0x100
#define HWIO_RPM_M3_ETM_ETMCR_BRANCH_OUTPUT_SHFT                                         0x8
#define HWIO_RPM_M3_ETM_ETMCR_STALL_PROCESSOR_BMSK                                      0x80
#define HWIO_RPM_M3_ETM_ETMCR_STALL_PROCESSOR_SHFT                                       0x7
#define HWIO_RPM_M3_ETM_ETMCR_PORT_SIZE_BITS_2_0_BMSK                                   0x70
#define HWIO_RPM_M3_ETM_ETMCR_PORT_SIZE_BITS_2_0_SHFT                                    0x4
#define HWIO_RPM_M3_ETM_ETMCR_ETM_POWER_DOWN_BMSK                                        0x1
#define HWIO_RPM_M3_ETM_ETMCR_ETM_POWER_DOWN_SHFT                                        0x0

#define HWIO_RPM_M3_ETM_ETMCCR_ADDR                                               (RPM_M3_PPB_EXT_REG_BASE      + 0x00001004)
#define HWIO_RPM_M3_ETM_ETMCCR_RMSK                                               0xffffffff
#define HWIO_RPM_M3_ETM_ETMCCR_IN          \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMCCR_ADDR, HWIO_RPM_M3_ETM_ETMCCR_RMSK)
#define HWIO_RPM_M3_ETM_ETMCCR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMCCR_ADDR, m)
#define HWIO_RPM_M3_ETM_ETMCCR_ETM_ETMCCR_BMSK                                    0xffffffff
#define HWIO_RPM_M3_ETM_ETMCCR_ETM_ETMCCR_SHFT                                           0x0

#define HWIO_RPM_M3_ETM_ETMTRIGGER_ADDR                                           (RPM_M3_PPB_EXT_REG_BASE      + 0x00001008)
#define HWIO_RPM_M3_ETM_ETMTRIGGER_RMSK                                              0x1ffff
#define HWIO_RPM_M3_ETM_ETMTRIGGER_IN          \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMTRIGGER_ADDR, HWIO_RPM_M3_ETM_ETMTRIGGER_RMSK)
#define HWIO_RPM_M3_ETM_ETMTRIGGER_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMTRIGGER_ADDR, m)
#define HWIO_RPM_M3_ETM_ETMTRIGGER_OUT(v)      \
        out_dword(HWIO_RPM_M3_ETM_ETMTRIGGER_ADDR,v)
#define HWIO_RPM_M3_ETM_ETMTRIGGER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ETM_ETMTRIGGER_ADDR,m,v,HWIO_RPM_M3_ETM_ETMTRIGGER_IN)
#define HWIO_RPM_M3_ETM_ETMTRIGGER_BOOLEAN_FUNCTION_BMSK                             0x1c000
#define HWIO_RPM_M3_ETM_ETMTRIGGER_BOOLEAN_FUNCTION_SHFT                                 0xe
#define HWIO_RPM_M3_ETM_ETMTRIGGER_BOOLEAN_FUNCTION_ENUM_0B000_FVAL                      0x0
#define HWIO_RPM_M3_ETM_ETMTRIGGER_BOOLEAN_FUNCTION_ENUM_0B001_FVAL                      0x1
#define HWIO_RPM_M3_ETM_ETMTRIGGER_BOOLEAN_FUNCTION_ENUM_0B010_FVAL                      0x2
#define HWIO_RPM_M3_ETM_ETMTRIGGER_BOOLEAN_FUNCTION_ENUM_0B011_FVAL                      0x3
#define HWIO_RPM_M3_ETM_ETMTRIGGER_BOOLEAN_FUNCTION_ENUM_0B100_FVAL                      0x4
#define HWIO_RPM_M3_ETM_ETMTRIGGER_BOOLEAN_FUNCTION_ENUM_0B101_FVAL                      0x5
#define HWIO_RPM_M3_ETM_ETMTRIGGER_BOOLEAN_FUNCTION_ENUM_0B110_FVAL                      0x6
#define HWIO_RPM_M3_ETM_ETMTRIGGER_BOOLEAN_FUNCTION_ENUM_0B111_FVAL                      0x7
#define HWIO_RPM_M3_ETM_ETMTRIGGER_RESOURCE_A_BMSK                                    0x3f80
#define HWIO_RPM_M3_ETM_ETMTRIGGER_RESOURCE_A_SHFT                                       0x7
#define HWIO_RPM_M3_ETM_ETMTRIGGER_RESOURCE_A_ENUM_0B0100000_FVAL                       0x20
#define HWIO_RPM_M3_ETM_ETMTRIGGER_RESOURCE_A_ENUM_0B0100001_FVAL                       0x21
#define HWIO_RPM_M3_ETM_ETMTRIGGER_RESOURCE_A_ENUM_0B0100010_FVAL                       0x22
#define HWIO_RPM_M3_ETM_ETMTRIGGER_RESOURCE_A_ENUM_0B0100011_FVAL                       0x23
#define HWIO_RPM_M3_ETM_ETMTRIGGER_RESOURCE_A_ENUM_0B1011111_FVAL                       0x5f
#define HWIO_RPM_M3_ETM_ETMTRIGGER_RESOURCE_A_ENUM_0B1100000_FVAL                       0x60
#define HWIO_RPM_M3_ETM_ETMTRIGGER_RESOURCE_A_ENUM_0B1100001_FVAL                       0x61
#define HWIO_RPM_M3_ETM_ETMTRIGGER_RESOURCE_A_ENUM_0B1101111_FVAL                       0x6f
#define HWIO_RPM_M3_ETM_ETMTRIGGER_RESOURCE_B_BMSK                                      0x7f
#define HWIO_RPM_M3_ETM_ETMTRIGGER_RESOURCE_B_SHFT                                       0x0
#define HWIO_RPM_M3_ETM_ETMTRIGGER_RESOURCE_B_ENUM_0B0100000_FVAL                       0x20
#define HWIO_RPM_M3_ETM_ETMTRIGGER_RESOURCE_B_ENUM_0B0100001_FVAL                       0x21
#define HWIO_RPM_M3_ETM_ETMTRIGGER_RESOURCE_B_ENUM_0B0100010_FVAL                       0x22
#define HWIO_RPM_M3_ETM_ETMTRIGGER_RESOURCE_B_ENUM_0B0100011_FVAL                       0x23
#define HWIO_RPM_M3_ETM_ETMTRIGGER_RESOURCE_B_ENUM_0B1011111_FVAL                       0x5f
#define HWIO_RPM_M3_ETM_ETMTRIGGER_RESOURCE_B_ENUM_0B1100000_FVAL                       0x60
#define HWIO_RPM_M3_ETM_ETMTRIGGER_RESOURCE_B_ENUM_0B1100001_FVAL                       0x61
#define HWIO_RPM_M3_ETM_ETMTRIGGER_RESOURCE_B_ENUM_0B1101111_FVAL                       0x6f

#define HWIO_RPM_M3_ETM_ETMSR_ADDR                                                (RPM_M3_PPB_EXT_REG_BASE      + 0x00001010)
#define HWIO_RPM_M3_ETM_ETMSR_RMSK                                                       0xf
#define HWIO_RPM_M3_ETM_ETMSR_IN          \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMSR_ADDR, HWIO_RPM_M3_ETM_ETMSR_RMSK)
#define HWIO_RPM_M3_ETM_ETMSR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMSR_ADDR, m)
#define HWIO_RPM_M3_ETM_ETMSR_OUT(v)      \
        out_dword(HWIO_RPM_M3_ETM_ETMSR_ADDR,v)
#define HWIO_RPM_M3_ETM_ETMSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ETM_ETMSR_ADDR,m,v,HWIO_RPM_M3_ETM_ETMSR_IN)
#define HWIO_RPM_M3_ETM_ETMSR_TRIGGER_FLAG_BMSK                                          0x8
#define HWIO_RPM_M3_ETM_ETMSR_TRIGGER_FLAG_SHFT                                          0x3
#define HWIO_RPM_M3_ETM_ETMSR_TRACE_START_STOP_RESOURCE_STATUS_BMSK                      0x4
#define HWIO_RPM_M3_ETM_ETMSR_TRACE_START_STOP_RESOURCE_STATUS_SHFT                      0x2
#define HWIO_RPM_M3_ETM_ETMSR_ETM_PROGRAMMING_BIT_VALUE_BMSK                             0x2
#define HWIO_RPM_M3_ETM_ETMSR_ETM_PROGRAMMING_BIT_VALUE_SHFT                             0x1
#define HWIO_RPM_M3_ETM_ETMSR_UNTRACED_OVERFLOW_FLAG_BMSK                                0x1
#define HWIO_RPM_M3_ETM_ETMSR_UNTRACED_OVERFLOW_FLAG_SHFT                                0x0

#define HWIO_RPM_M3_ETM_ETMSCR_ADDR                                               (RPM_M3_PPB_EXT_REG_BASE      + 0x00001014)
#define HWIO_RPM_M3_ETM_ETMSCR_RMSK                                                  0x20f07
#define HWIO_RPM_M3_ETM_ETMSCR_IN          \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMSCR_ADDR, HWIO_RPM_M3_ETM_ETMSCR_RMSK)
#define HWIO_RPM_M3_ETM_ETMSCR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMSCR_ADDR, m)
#define HWIO_RPM_M3_ETM_ETMSCR_NO_FETCH_COMPARISON_BMSK                              0x20000
#define HWIO_RPM_M3_ETM_ETMSCR_NO_FETCH_COMPARISON_SHFT                                 0x11
#define HWIO_RPM_M3_ETM_ETMSCR_PORT_MODE_SUPPORTED_BMSK                                0x800
#define HWIO_RPM_M3_ETM_ETMSCR_PORT_MODE_SUPPORTED_SHFT                                  0xb
#define HWIO_RPM_M3_ETM_ETMSCR_PORT_SIZE_SUPPORTED_BMSK                                0x400
#define HWIO_RPM_M3_ETM_ETMSCR_PORT_SIZE_SUPPORTED_SHFT                                  0xa
#define HWIO_RPM_M3_ETM_ETMSCR_MAXIMUM_PORT_SIZE_BIT_3_BMSK                            0x200
#define HWIO_RPM_M3_ETM_ETMSCR_MAXIMUM_PORT_SIZE_BIT_3_SHFT                              0x9
#define HWIO_RPM_M3_ETM_ETMSCR_FIFOFULL_SUPPORTED_BMSK                                 0x100
#define HWIO_RPM_M3_ETM_ETMSCR_FIFOFULL_SUPPORTED_SHFT                                   0x8
#define HWIO_RPM_M3_ETM_ETMSCR_MAXIMUM_PORT_SIZE_BITS_2_0_BMSK                           0x7
#define HWIO_RPM_M3_ETM_ETMSCR_MAXIMUM_PORT_SIZE_BITS_2_0_SHFT                           0x0

#define HWIO_RPM_M3_ETM_ETMTEEVR_ADDR                                             (RPM_M3_PPB_EXT_REG_BASE      + 0x00001020)
#define HWIO_RPM_M3_ETM_ETMTEEVR_RMSK                                                0x1ffff
#define HWIO_RPM_M3_ETM_ETMTEEVR_OUT(v)      \
        out_dword(HWIO_RPM_M3_ETM_ETMTEEVR_ADDR,v)
#define HWIO_RPM_M3_ETM_ETMTEEVR_BOOLEAN_FUNCTION_BMSK                               0x1c000
#define HWIO_RPM_M3_ETM_ETMTEEVR_BOOLEAN_FUNCTION_SHFT                                   0xe
#define HWIO_RPM_M3_ETM_ETMTEEVR_BOOLEAN_FUNCTION_ENUM_0B000_FVAL                        0x0
#define HWIO_RPM_M3_ETM_ETMTEEVR_BOOLEAN_FUNCTION_ENUM_0B001_FVAL                        0x1
#define HWIO_RPM_M3_ETM_ETMTEEVR_BOOLEAN_FUNCTION_ENUM_0B010_FVAL                        0x2
#define HWIO_RPM_M3_ETM_ETMTEEVR_BOOLEAN_FUNCTION_ENUM_0B011_FVAL                        0x3
#define HWIO_RPM_M3_ETM_ETMTEEVR_BOOLEAN_FUNCTION_ENUM_0B100_FVAL                        0x4
#define HWIO_RPM_M3_ETM_ETMTEEVR_BOOLEAN_FUNCTION_ENUM_0B101_FVAL                        0x5
#define HWIO_RPM_M3_ETM_ETMTEEVR_BOOLEAN_FUNCTION_ENUM_0B110_FVAL                        0x6
#define HWIO_RPM_M3_ETM_ETMTEEVR_BOOLEAN_FUNCTION_ENUM_0B111_FVAL                        0x7
#define HWIO_RPM_M3_ETM_ETMTEEVR_RESOURCE_A_BMSK                                      0x3f80
#define HWIO_RPM_M3_ETM_ETMTEEVR_RESOURCE_A_SHFT                                         0x7
#define HWIO_RPM_M3_ETM_ETMTEEVR_RESOURCE_A_ENUM_0B0100000_FVAL                         0x20
#define HWIO_RPM_M3_ETM_ETMTEEVR_RESOURCE_A_ENUM_0B0100001_FVAL                         0x21
#define HWIO_RPM_M3_ETM_ETMTEEVR_RESOURCE_A_ENUM_0B0100010_FVAL                         0x22
#define HWIO_RPM_M3_ETM_ETMTEEVR_RESOURCE_A_ENUM_0B0100011_FVAL                         0x23
#define HWIO_RPM_M3_ETM_ETMTEEVR_RESOURCE_A_ENUM_0B1011111_FVAL                         0x5f
#define HWIO_RPM_M3_ETM_ETMTEEVR_RESOURCE_A_ENUM_0B1100000_FVAL                         0x60
#define HWIO_RPM_M3_ETM_ETMTEEVR_RESOURCE_A_ENUM_0B1100001_FVAL                         0x61
#define HWIO_RPM_M3_ETM_ETMTEEVR_RESOURCE_A_ENUM_0B1101111_FVAL                         0x6f
#define HWIO_RPM_M3_ETM_ETMTEEVR_RESOURCE_B_BMSK                                        0x7f
#define HWIO_RPM_M3_ETM_ETMTEEVR_RESOURCE_B_SHFT                                         0x0
#define HWIO_RPM_M3_ETM_ETMTEEVR_RESOURCE_B_ENUM_0B0100000_FVAL                         0x20
#define HWIO_RPM_M3_ETM_ETMTEEVR_RESOURCE_B_ENUM_0B0100001_FVAL                         0x21
#define HWIO_RPM_M3_ETM_ETMTEEVR_RESOURCE_B_ENUM_0B0100010_FVAL                         0x22
#define HWIO_RPM_M3_ETM_ETMTEEVR_RESOURCE_B_ENUM_0B0100011_FVAL                         0x23
#define HWIO_RPM_M3_ETM_ETMTEEVR_RESOURCE_B_ENUM_0B1011111_FVAL                         0x5f
#define HWIO_RPM_M3_ETM_ETMTEEVR_RESOURCE_B_ENUM_0B1100000_FVAL                         0x60
#define HWIO_RPM_M3_ETM_ETMTEEVR_RESOURCE_B_ENUM_0B1100001_FVAL                         0x61
#define HWIO_RPM_M3_ETM_ETMTEEVR_RESOURCE_B_ENUM_0B1101111_FVAL                         0x6f

#define HWIO_RPM_M3_ETM_ETMTECR1_ADDR                                             (RPM_M3_PPB_EXT_REG_BASE      + 0x00001024)
#define HWIO_RPM_M3_ETM_ETMTECR1_RMSK                                              0x2000000
#define HWIO_RPM_M3_ETM_ETMTECR1_OUT(v)      \
        out_dword(HWIO_RPM_M3_ETM_ETMTECR1_ADDR,v)
#define HWIO_RPM_M3_ETM_ETMTECR1_TRACE_CONTROL_ENABLE_BMSK                         0x2000000
#define HWIO_RPM_M3_ETM_ETMTECR1_TRACE_CONTROL_ENABLE_SHFT                              0x19
#define HWIO_RPM_M3_ETM_ETMTECR1_TRACE_CONTROL_ENABLE_ENUM_0B0_FVAL                      0x0
#define HWIO_RPM_M3_ETM_ETMTECR1_TRACE_CONTROL_ENABLE_ENUM_0B1_FVAL                      0x1

#define HWIO_RPM_M3_ETM_ETMFFLR_ADDR                                              (RPM_M3_PPB_EXT_REG_BASE      + 0x00001028)
#define HWIO_RPM_M3_ETM_ETMFFLR_RMSK                                                    0xff
#define HWIO_RPM_M3_ETM_ETMFFLR_IN          \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMFFLR_ADDR, HWIO_RPM_M3_ETM_ETMFFLR_RMSK)
#define HWIO_RPM_M3_ETM_ETMFFLR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMFFLR_ADDR, m)
#define HWIO_RPM_M3_ETM_ETMFFLR_OUT(v)      \
        out_dword(HWIO_RPM_M3_ETM_ETMFFLR_ADDR,v)
#define HWIO_RPM_M3_ETM_ETMFFLR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ETM_ETMFFLR_ADDR,m,v,HWIO_RPM_M3_ETM_ETMFFLR_IN)
#define HWIO_RPM_M3_ETM_ETMFFLR_FIFO_FULL_LEVEL_BMSK                                    0xff
#define HWIO_RPM_M3_ETM_ETMFFLR_FIFO_FULL_LEVEL_SHFT                                     0x0

#define HWIO_RPM_M3_ETM_ETMCNTRLDVR1_ADDR                                         (RPM_M3_PPB_EXT_REG_BASE      + 0x00001140)
#define HWIO_RPM_M3_ETM_ETMCNTRLDVR1_RMSK                                               0xff
#define HWIO_RPM_M3_ETM_ETMCNTRLDVR1_IN          \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMCNTRLDVR1_ADDR, HWIO_RPM_M3_ETM_ETMCNTRLDVR1_RMSK)
#define HWIO_RPM_M3_ETM_ETMCNTRLDVR1_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMCNTRLDVR1_ADDR, m)
#define HWIO_RPM_M3_ETM_ETMCNTRLDVR1_OUT(v)      \
        out_dword(HWIO_RPM_M3_ETM_ETMCNTRLDVR1_ADDR,v)
#define HWIO_RPM_M3_ETM_ETMCNTRLDVR1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ETM_ETMCNTRLDVR1_ADDR,m,v,HWIO_RPM_M3_ETM_ETMCNTRLDVR1_IN)
#define HWIO_RPM_M3_ETM_ETMCNTRLDVR1_FIFO_FULL_LEVEL_BMSK                               0xff
#define HWIO_RPM_M3_ETM_ETMCNTRLDVR1_FIFO_FULL_LEVEL_SHFT                                0x0

#define HWIO_RPM_M3_ETM_ETMSYNCFR_ADDR                                            (RPM_M3_PPB_EXT_REG_BASE      + 0x000011e0)
#define HWIO_RPM_M3_ETM_ETMSYNCFR_RMSK                                                 0xfff
#define HWIO_RPM_M3_ETM_ETMSYNCFR_IN          \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMSYNCFR_ADDR, HWIO_RPM_M3_ETM_ETMSYNCFR_RMSK)
#define HWIO_RPM_M3_ETM_ETMSYNCFR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMSYNCFR_ADDR, m)
#define HWIO_RPM_M3_ETM_ETMSYNCFR_SYNCHRONIZATION_FREQUENCY_BMSK                       0xfff
#define HWIO_RPM_M3_ETM_ETMSYNCFR_SYNCHRONIZATION_FREQUENCY_SHFT                         0x0

#define HWIO_RPM_M3_ETM_ETMIDR_ADDR                                               (RPM_M3_PPB_EXT_REG_BASE      + 0x000011e4)
#define HWIO_RPM_M3_ETM_ETMIDR_RMSK                                               0xffffffff
#define HWIO_RPM_M3_ETM_ETMIDR_IN          \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMIDR_ADDR, HWIO_RPM_M3_ETM_ETMIDR_RMSK)
#define HWIO_RPM_M3_ETM_ETMIDR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMIDR_ADDR, m)
#define HWIO_RPM_M3_ETM_ETMIDR_ETM_ETMIDR_BMSK                                    0xffffffff
#define HWIO_RPM_M3_ETM_ETMIDR_ETM_ETMIDR_SHFT                                           0x0

#define HWIO_RPM_M3_ETM_ETMCCER_ADDR                                              (RPM_M3_PPB_EXT_REG_BASE      + 0x000011e8)
#define HWIO_RPM_M3_ETM_ETMCCER_RMSK                                              0xffffffff
#define HWIO_RPM_M3_ETM_ETMCCER_IN          \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMCCER_ADDR, HWIO_RPM_M3_ETM_ETMCCER_RMSK)
#define HWIO_RPM_M3_ETM_ETMCCER_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMCCER_ADDR, m)
#define HWIO_RPM_M3_ETM_ETMCCER_ETM_ETMCCER_BMSK                                  0xffffffff
#define HWIO_RPM_M3_ETM_ETMCCER_ETM_ETMCCER_SHFT                                         0x0

#define HWIO_RPM_M3_ETM_ETMTESSEICR_ADDR                                          (RPM_M3_PPB_EXT_REG_BASE      + 0x000011f0)
#define HWIO_RPM_M3_ETM_ETMTESSEICR_RMSK                                             0xf000f
#define HWIO_RPM_M3_ETM_ETMTESSEICR_IN          \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMTESSEICR_ADDR, HWIO_RPM_M3_ETM_ETMTESSEICR_RMSK)
#define HWIO_RPM_M3_ETM_ETMTESSEICR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMTESSEICR_ADDR, m)
#define HWIO_RPM_M3_ETM_ETMTESSEICR_OUT(v)      \
        out_dword(HWIO_RPM_M3_ETM_ETMTESSEICR_ADDR,v)
#define HWIO_RPM_M3_ETM_ETMTESSEICR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ETM_ETMTESSEICR_ADDR,m,v,HWIO_RPM_M3_ETM_ETMTESSEICR_IN)
#define HWIO_RPM_M3_ETM_ETMTESSEICR_STOP_RESOURCE_SELECT_BMSK                        0xf0000
#define HWIO_RPM_M3_ETM_ETMTESSEICR_STOP_RESOURCE_SELECT_SHFT                           0x10
#define HWIO_RPM_M3_ETM_ETMTESSEICR_START_RESOURCE_SELECT_BMSK                           0xf
#define HWIO_RPM_M3_ETM_ETMTESSEICR_START_RESOURCE_SELECT_SHFT                           0x0

#define HWIO_RPM_M3_ETM_ETMTSEVR_ADDR                                             (RPM_M3_PPB_EXT_REG_BASE      + 0x000011f8)
#define HWIO_RPM_M3_ETM_ETMTSEVR_RMSK                                             0xffffffff
#define HWIO_RPM_M3_ETM_ETMTSEVR_IN          \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMTSEVR_ADDR, HWIO_RPM_M3_ETM_ETMTSEVR_RMSK)
#define HWIO_RPM_M3_ETM_ETMTSEVR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMTSEVR_ADDR, m)
#define HWIO_RPM_M3_ETM_ETMTSEVR_ETM_ETMTSEVR_BMSK                                0xffffffff
#define HWIO_RPM_M3_ETM_ETMTSEVR_ETM_ETMTSEVR_SHFT                                       0x0

#define HWIO_RPM_M3_ETM_ETMTRACEIDR_ADDR                                          (RPM_M3_PPB_EXT_REG_BASE      + 0x00001200)
#define HWIO_RPM_M3_ETM_ETMTRACEIDR_RMSK                                                0x7f
#define HWIO_RPM_M3_ETM_ETMTRACEIDR_IN          \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMTRACEIDR_ADDR, HWIO_RPM_M3_ETM_ETMTRACEIDR_RMSK)
#define HWIO_RPM_M3_ETM_ETMTRACEIDR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMTRACEIDR_ADDR, m)
#define HWIO_RPM_M3_ETM_ETMTRACEIDR_OUT(v)      \
        out_dword(HWIO_RPM_M3_ETM_ETMTRACEIDR_ADDR,v)
#define HWIO_RPM_M3_ETM_ETMTRACEIDR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ETM_ETMTRACEIDR_ADDR,m,v,HWIO_RPM_M3_ETM_ETMTRACEIDR_IN)
#define HWIO_RPM_M3_ETM_ETMTRACEIDR_SIGNALS_TO_TRACE_BUS_BITS_BMSK                      0x7f
#define HWIO_RPM_M3_ETM_ETMTRACEIDR_SIGNALS_TO_TRACE_BUS_BITS_SHFT                       0x0

#define HWIO_RPM_M3_ETM_ETMIDR2_ADDR                                              (RPM_M3_PPB_EXT_REG_BASE      + 0x00001208)
#define HWIO_RPM_M3_ETM_ETMIDR2_RMSK                                                     0x3
#define HWIO_RPM_M3_ETM_ETMIDR2_IN          \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMIDR2_ADDR, HWIO_RPM_M3_ETM_ETMIDR2_RMSK)
#define HWIO_RPM_M3_ETM_ETMIDR2_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMIDR2_ADDR, m)
#define HWIO_RPM_M3_ETM_ETMIDR2_SWP_TRANSFER_ORDER_BMSK                                  0x2
#define HWIO_RPM_M3_ETM_ETMIDR2_SWP_TRANSFER_ORDER_SHFT                                  0x1
#define HWIO_RPM_M3_ETM_ETMIDR2_RFE_TRANSFER_ORDER_BMSK                                  0x1
#define HWIO_RPM_M3_ETM_ETMIDR2_RFE_TRANSFER_ORDER_SHFT                                  0x0

#define HWIO_RPM_M3_ETM_ETMPDSR_ADDR                                              (RPM_M3_PPB_EXT_REG_BASE      + 0x00001314)
#define HWIO_RPM_M3_ETM_ETMPDSR_RMSK                                                     0x1
#define HWIO_RPM_M3_ETM_ETMPDSR_IN          \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMPDSR_ADDR, HWIO_RPM_M3_ETM_ETMPDSR_RMSK)
#define HWIO_RPM_M3_ETM_ETMPDSR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMPDSR_ADDR, m)
#define HWIO_RPM_M3_ETM_ETMPDSR_ETM_POWERED_UP_BMSK                                      0x1
#define HWIO_RPM_M3_ETM_ETMPDSR_ETM_POWERED_UP_SHFT                                      0x0
#define HWIO_RPM_M3_ETM_ETMPDSR_ETM_POWERED_UP_ENUM_0B0_FVAL                             0x0
#define HWIO_RPM_M3_ETM_ETMPDSR_ETM_POWERED_UP_ENUM_0B1_FVAL                             0x1

#define HWIO_RPM_M3_ETM_ITMISCIN_ADDR                                             (RPM_M3_PPB_EXT_REG_BASE      + 0x00001ee0)
#define HWIO_RPM_M3_ETM_ITMISCIN_RMSK                                             0xffffffff
#define HWIO_RPM_M3_ETM_ITMISCIN_IN          \
        in_dword_masked(HWIO_RPM_M3_ETM_ITMISCIN_ADDR, HWIO_RPM_M3_ETM_ITMISCIN_RMSK)
#define HWIO_RPM_M3_ETM_ITMISCIN_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ETM_ITMISCIN_ADDR, m)
#define HWIO_RPM_M3_ETM_ITMISCIN_ETM_ITMISCIN_BMSK                                0xffffffff
#define HWIO_RPM_M3_ETM_ITMISCIN_ETM_ITMISCIN_SHFT                                       0x0

#define HWIO_RPM_M3_ETM_ITTRIGOUT_ADDR                                            (RPM_M3_PPB_EXT_REG_BASE      + 0x00001ee8)
#define HWIO_RPM_M3_ETM_ITTRIGOUT_RMSK                                            0xffffffff
#define HWIO_RPM_M3_ETM_ITTRIGOUT_OUT(v)      \
        out_dword(HWIO_RPM_M3_ETM_ITTRIGOUT_ADDR,v)
#define HWIO_RPM_M3_ETM_ITTRIGOUT_ETM_ITTRIGOUT_BMSK                              0xffffffff
#define HWIO_RPM_M3_ETM_ITTRIGOUT_ETM_ITTRIGOUT_SHFT                                     0x0

#define HWIO_RPM_M3_ETM_ETM_ITATBCTR2_ADDR                                        (RPM_M3_PPB_EXT_REG_BASE      + 0x00001ef0)
#define HWIO_RPM_M3_ETM_ETM_ITATBCTR2_RMSK                                        0xffffffff
#define HWIO_RPM_M3_ETM_ETM_ITATBCTR2_IN          \
        in_dword_masked(HWIO_RPM_M3_ETM_ETM_ITATBCTR2_ADDR, HWIO_RPM_M3_ETM_ETM_ITATBCTR2_RMSK)
#define HWIO_RPM_M3_ETM_ETM_ITATBCTR2_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ETM_ETM_ITATBCTR2_ADDR, m)
#define HWIO_RPM_M3_ETM_ETM_ITATBCTR2_ETM_ETM_ITATBCTR2_BMSK                      0xffffffff
#define HWIO_RPM_M3_ETM_ETM_ITATBCTR2_ETM_ETM_ITATBCTR2_SHFT                             0x0

#define HWIO_RPM_M3_ETM_ETM_ITATBCTR0_ADDR                                        (RPM_M3_PPB_EXT_REG_BASE      + 0x00001ef8)
#define HWIO_RPM_M3_ETM_ETM_ITATBCTR0_RMSK                                        0xffffffff
#define HWIO_RPM_M3_ETM_ETM_ITATBCTR0_OUT(v)      \
        out_dword(HWIO_RPM_M3_ETM_ETM_ITATBCTR0_ADDR,v)
#define HWIO_RPM_M3_ETM_ETM_ITATBCTR0_ETM_ETM_ITATBCTR0_BMSK                      0xffffffff
#define HWIO_RPM_M3_ETM_ETM_ITATBCTR0_ETM_ETM_ITATBCTR0_SHFT                             0x0

#define HWIO_RPM_M3_ETM_ETMITCTRL_ADDR                                            (RPM_M3_PPB_EXT_REG_BASE      + 0x00001f00)
#define HWIO_RPM_M3_ETM_ETMITCTRL_RMSK                                                   0x1
#define HWIO_RPM_M3_ETM_ETMITCTRL_IN          \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMITCTRL_ADDR, HWIO_RPM_M3_ETM_ETMITCTRL_RMSK)
#define HWIO_RPM_M3_ETM_ETMITCTRL_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMITCTRL_ADDR, m)
#define HWIO_RPM_M3_ETM_ETMITCTRL_OUT(v)      \
        out_dword(HWIO_RPM_M3_ETM_ETMITCTRL_ADDR,v)
#define HWIO_RPM_M3_ETM_ETMITCTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ETM_ETMITCTRL_ADDR,m,v,HWIO_RPM_M3_ETM_ETMITCTRL_IN)
#define HWIO_RPM_M3_ETM_ETMITCTRL_ENABLE_INTEGRATION_MODE_BMSK                           0x1
#define HWIO_RPM_M3_ETM_ETMITCTRL_ENABLE_INTEGRATION_MODE_SHFT                           0x0

#define HWIO_RPM_M3_ETM_ETMCLAIMSET_ADDR                                          (RPM_M3_PPB_EXT_REG_BASE      + 0x00001fa0)
#define HWIO_RPM_M3_ETM_ETMCLAIMSET_RMSK                                                 0xf
#define HWIO_RPM_M3_ETM_ETMCLAIMSET_IN          \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMCLAIMSET_ADDR, HWIO_RPM_M3_ETM_ETMCLAIMSET_RMSK)
#define HWIO_RPM_M3_ETM_ETMCLAIMSET_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMCLAIMSET_ADDR, m)
#define HWIO_RPM_M3_ETM_ETMCLAIMSET_OUT(v)      \
        out_dword(HWIO_RPM_M3_ETM_ETMCLAIMSET_ADDR,v)
#define HWIO_RPM_M3_ETM_ETMCLAIMSET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ETM_ETMCLAIMSET_ADDR,m,v,HWIO_RPM_M3_ETM_ETMCLAIMSET_IN)
#define HWIO_RPM_M3_ETM_ETMCLAIMSET_CLAIM_TAG_BMSK                                       0xf
#define HWIO_RPM_M3_ETM_ETMCLAIMSET_CLAIM_TAG_SHFT                                       0x0

#define HWIO_RPM_M3_ETM_ETMCLAIMCLR_ADDR                                          (RPM_M3_PPB_EXT_REG_BASE      + 0x00001fa4)
#define HWIO_RPM_M3_ETM_ETMCLAIMCLR_RMSK                                                 0xf
#define HWIO_RPM_M3_ETM_ETMCLAIMCLR_IN          \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMCLAIMCLR_ADDR, HWIO_RPM_M3_ETM_ETMCLAIMCLR_RMSK)
#define HWIO_RPM_M3_ETM_ETMCLAIMCLR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMCLAIMCLR_ADDR, m)
#define HWIO_RPM_M3_ETM_ETMCLAIMCLR_OUT(v)      \
        out_dword(HWIO_RPM_M3_ETM_ETMCLAIMCLR_ADDR,v)
#define HWIO_RPM_M3_ETM_ETMCLAIMCLR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RPM_M3_ETM_ETMCLAIMCLR_ADDR,m,v,HWIO_RPM_M3_ETM_ETMCLAIMCLR_IN)
#define HWIO_RPM_M3_ETM_ETMCLAIMCLR_CLAIM_TAG_BMSK                                       0xf
#define HWIO_RPM_M3_ETM_ETMCLAIMCLR_CLAIM_TAG_SHFT                                       0x0

#define HWIO_RPM_M3_ETM_ETMLAR_ADDR                                               (RPM_M3_PPB_EXT_REG_BASE      + 0x00001fb0)
#define HWIO_RPM_M3_ETM_ETMLAR_RMSK                                               0xffffffff
#define HWIO_RPM_M3_ETM_ETMLAR_OUT(v)      \
        out_dword(HWIO_RPM_M3_ETM_ETMLAR_ADDR,v)
#define HWIO_RPM_M3_ETM_ETMLAR_ETM_ETMLAR_BMSK                                    0xffffffff
#define HWIO_RPM_M3_ETM_ETMLAR_ETM_ETMLAR_SHFT                                           0x0

#define HWIO_RPM_M3_ETM_ETMLSR_ADDR                                               (RPM_M3_PPB_EXT_REG_BASE      + 0x00001fb4)
#define HWIO_RPM_M3_ETM_ETMLSR_RMSK                                               0xffffffff
#define HWIO_RPM_M3_ETM_ETMLSR_IN          \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMLSR_ADDR, HWIO_RPM_M3_ETM_ETMLSR_RMSK)
#define HWIO_RPM_M3_ETM_ETMLSR_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMLSR_ADDR, m)
#define HWIO_RPM_M3_ETM_ETMLSR_ETM_ETMLSR_BMSK                                    0xffffffff
#define HWIO_RPM_M3_ETM_ETMLSR_ETM_ETMLSR_SHFT                                           0x0

#define HWIO_RPM_M3_ETM_ETMAUTHSTATUS_ADDR                                        (RPM_M3_PPB_EXT_REG_BASE      + 0x00001fb8)
#define HWIO_RPM_M3_ETM_ETMAUTHSTATUS_RMSK                                              0xf3
#define HWIO_RPM_M3_ETM_ETMAUTHSTATUS_IN          \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMAUTHSTATUS_ADDR, HWIO_RPM_M3_ETM_ETMAUTHSTATUS_RMSK)
#define HWIO_RPM_M3_ETM_ETMAUTHSTATUS_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMAUTHSTATUS_ADDR, m)
#define HWIO_RPM_M3_ETM_ETMAUTHSTATUS_SECURE_NON_INVASIVE_DEBUG_BMSK                    0xc0
#define HWIO_RPM_M3_ETM_ETMAUTHSTATUS_SECURE_NON_INVASIVE_DEBUG_SHFT                     0x6
#define HWIO_RPM_M3_ETM_ETMAUTHSTATUS_SECURE_NON_INVASIVE_DEBUG_ENUM_0B10_FVAL           0x2
#define HWIO_RPM_M3_ETM_ETMAUTHSTATUS_SECURE_NON_INVASIVE_DEBUG_ENUM_0B11_FVAL           0x3
#define HWIO_RPM_M3_ETM_ETMAUTHSTATUS_SECURE_INVASIVE_DEBUG_BMSK                        0x30
#define HWIO_RPM_M3_ETM_ETMAUTHSTATUS_SECURE_INVASIVE_DEBUG_SHFT                         0x4
#define HWIO_RPM_M3_ETM_ETMAUTHSTATUS_NONSECURE_NON_INVASIVE_DEBUG_BMSK                  0x3
#define HWIO_RPM_M3_ETM_ETMAUTHSTATUS_NONSECURE_NON_INVASIVE_DEBUG_SHFT                  0x0

#define HWIO_RPM_M3_ETM_ETMDEVTYPE_ADDR                                           (RPM_M3_PPB_EXT_REG_BASE      + 0x00001fcc)
#define HWIO_RPM_M3_ETM_ETMDEVTYPE_RMSK                                                 0xff
#define HWIO_RPM_M3_ETM_ETMDEVTYPE_IN          \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMDEVTYPE_ADDR, HWIO_RPM_M3_ETM_ETMDEVTYPE_RMSK)
#define HWIO_RPM_M3_ETM_ETMDEVTYPE_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMDEVTYPE_ADDR, m)
#define HWIO_RPM_M3_ETM_ETMDEVTYPE_SUB_TYPE_BMSK                                        0xf0
#define HWIO_RPM_M3_ETM_ETMDEVTYPE_SUB_TYPE_SHFT                                         0x4
#define HWIO_RPM_M3_ETM_ETMDEVTYPE_SUB_TYPE_ENUM_0B0001_FVAL                             0x1
#define HWIO_RPM_M3_ETM_ETMDEVTYPE_MAIN_TYPE_BMSK                                        0xf
#define HWIO_RPM_M3_ETM_ETMDEVTYPE_MAIN_TYPE_SHFT                                        0x0
#define HWIO_RPM_M3_ETM_ETMDEVTYPE_MAIN_TYPE_ENUM_0B0011_FVAL                            0x3

#define HWIO_RPM_M3_ETM_ETMPID4_ADDR                                              (RPM_M3_PPB_EXT_REG_BASE      + 0x00001fd0)
#define HWIO_RPM_M3_ETM_ETMPID4_RMSK                                              0xffffffff
#define HWIO_RPM_M3_ETM_ETMPID4_IN          \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMPID4_ADDR, HWIO_RPM_M3_ETM_ETMPID4_RMSK)
#define HWIO_RPM_M3_ETM_ETMPID4_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMPID4_ADDR, m)
#define HWIO_RPM_M3_ETM_ETMPID4_ETM_ETMPID4_BMSK                                  0xffffffff
#define HWIO_RPM_M3_ETM_ETMPID4_ETM_ETMPID4_SHFT                                         0x0

#define HWIO_RPM_M3_ETM_ETMPID5_ADDR                                              (RPM_M3_PPB_EXT_REG_BASE      + 0x00001fd4)
#define HWIO_RPM_M3_ETM_ETMPID5_RMSK                                              0xffffffff
#define HWIO_RPM_M3_ETM_ETMPID5_IN          \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMPID5_ADDR, HWIO_RPM_M3_ETM_ETMPID5_RMSK)
#define HWIO_RPM_M3_ETM_ETMPID5_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMPID5_ADDR, m)
#define HWIO_RPM_M3_ETM_ETMPID5_ETM_ETMPID5_BMSK                                  0xffffffff
#define HWIO_RPM_M3_ETM_ETMPID5_ETM_ETMPID5_SHFT                                         0x0

#define HWIO_RPM_M3_ETM_ETMPID6_ADDR                                              (RPM_M3_PPB_EXT_REG_BASE      + 0x00001fd8)
#define HWIO_RPM_M3_ETM_ETMPID6_RMSK                                              0xffffffff
#define HWIO_RPM_M3_ETM_ETMPID6_IN          \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMPID6_ADDR, HWIO_RPM_M3_ETM_ETMPID6_RMSK)
#define HWIO_RPM_M3_ETM_ETMPID6_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMPID6_ADDR, m)
#define HWIO_RPM_M3_ETM_ETMPID6_ETM_ETMPID6_BMSK                                  0xffffffff
#define HWIO_RPM_M3_ETM_ETMPID6_ETM_ETMPID6_SHFT                                         0x0

#define HWIO_RPM_M3_ETM_ETMPID7_ADDR                                              (RPM_M3_PPB_EXT_REG_BASE      + 0x00001fdc)
#define HWIO_RPM_M3_ETM_ETMPID7_RMSK                                              0xffffffff
#define HWIO_RPM_M3_ETM_ETMPID7_IN          \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMPID7_ADDR, HWIO_RPM_M3_ETM_ETMPID7_RMSK)
#define HWIO_RPM_M3_ETM_ETMPID7_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMPID7_ADDR, m)
#define HWIO_RPM_M3_ETM_ETMPID7_ETM_ETMPID7_BMSK                                  0xffffffff
#define HWIO_RPM_M3_ETM_ETMPID7_ETM_ETMPID7_SHFT                                         0x0

#define HWIO_RPM_M3_ETM_ETMPID0_ADDR                                              (RPM_M3_PPB_EXT_REG_BASE      + 0x00001fe0)
#define HWIO_RPM_M3_ETM_ETMPID0_RMSK                                              0xffffffff
#define HWIO_RPM_M3_ETM_ETMPID0_IN          \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMPID0_ADDR, HWIO_RPM_M3_ETM_ETMPID0_RMSK)
#define HWIO_RPM_M3_ETM_ETMPID0_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMPID0_ADDR, m)
#define HWIO_RPM_M3_ETM_ETMPID0_ETM_ETMPID0_BMSK                                  0xffffffff
#define HWIO_RPM_M3_ETM_ETMPID0_ETM_ETMPID0_SHFT                                         0x0

#define HWIO_RPM_M3_ETM_ETMPID1_ADDR                                              (RPM_M3_PPB_EXT_REG_BASE      + 0x00001fe4)
#define HWIO_RPM_M3_ETM_ETMPID1_RMSK                                              0xffffffff
#define HWIO_RPM_M3_ETM_ETMPID1_IN          \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMPID1_ADDR, HWIO_RPM_M3_ETM_ETMPID1_RMSK)
#define HWIO_RPM_M3_ETM_ETMPID1_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMPID1_ADDR, m)
#define HWIO_RPM_M3_ETM_ETMPID1_ETM_ETMPID1_BMSK                                  0xffffffff
#define HWIO_RPM_M3_ETM_ETMPID1_ETM_ETMPID1_SHFT                                         0x0

#define HWIO_RPM_M3_ETM_ETMPID2_ADDR                                              (RPM_M3_PPB_EXT_REG_BASE      + 0x00001fe8)
#define HWIO_RPM_M3_ETM_ETMPID2_RMSK                                              0xffffffff
#define HWIO_RPM_M3_ETM_ETMPID2_IN          \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMPID2_ADDR, HWIO_RPM_M3_ETM_ETMPID2_RMSK)
#define HWIO_RPM_M3_ETM_ETMPID2_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMPID2_ADDR, m)
#define HWIO_RPM_M3_ETM_ETMPID2_ETM_ETMPID2_BMSK                                  0xffffffff
#define HWIO_RPM_M3_ETM_ETMPID2_ETM_ETMPID2_SHFT                                         0x0

#define HWIO_RPM_M3_ETM_ETMPID3_ADDR                                              (RPM_M3_PPB_EXT_REG_BASE      + 0x00001fec)
#define HWIO_RPM_M3_ETM_ETMPID3_RMSK                                              0xffffffff
#define HWIO_RPM_M3_ETM_ETMPID3_IN          \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMPID3_ADDR, HWIO_RPM_M3_ETM_ETMPID3_RMSK)
#define HWIO_RPM_M3_ETM_ETMPID3_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMPID3_ADDR, m)
#define HWIO_RPM_M3_ETM_ETMPID3_ETM_ETMPID3_BMSK                                  0xffffffff
#define HWIO_RPM_M3_ETM_ETMPID3_ETM_ETMPID3_SHFT                                         0x0

#define HWIO_RPM_M3_ETM_ETMCID0_ADDR                                              (RPM_M3_PPB_EXT_REG_BASE      + 0x00001ff0)
#define HWIO_RPM_M3_ETM_ETMCID0_RMSK                                              0xffffffff
#define HWIO_RPM_M3_ETM_ETMCID0_IN          \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMCID0_ADDR, HWIO_RPM_M3_ETM_ETMCID0_RMSK)
#define HWIO_RPM_M3_ETM_ETMCID0_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMCID0_ADDR, m)
#define HWIO_RPM_M3_ETM_ETMCID0_ETM_ETMCID0_BMSK                                  0xffffffff
#define HWIO_RPM_M3_ETM_ETMCID0_ETM_ETMCID0_SHFT                                         0x0

#define HWIO_RPM_M3_ETM_ETMCID1_ADDR                                              (RPM_M3_PPB_EXT_REG_BASE      + 0x00001ff4)
#define HWIO_RPM_M3_ETM_ETMCID1_RMSK                                              0xffffffff
#define HWIO_RPM_M3_ETM_ETMCID1_IN          \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMCID1_ADDR, HWIO_RPM_M3_ETM_ETMCID1_RMSK)
#define HWIO_RPM_M3_ETM_ETMCID1_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMCID1_ADDR, m)
#define HWIO_RPM_M3_ETM_ETMCID1_ETM_ETMCID1_BMSK                                  0xffffffff
#define HWIO_RPM_M3_ETM_ETMCID1_ETM_ETMCID1_SHFT                                         0x0

#define HWIO_RPM_M3_ETM_ETMCID2_ADDR                                              (RPM_M3_PPB_EXT_REG_BASE      + 0x00001ff8)
#define HWIO_RPM_M3_ETM_ETMCID2_RMSK                                              0xffffffff
#define HWIO_RPM_M3_ETM_ETMCID2_IN          \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMCID2_ADDR, HWIO_RPM_M3_ETM_ETMCID2_RMSK)
#define HWIO_RPM_M3_ETM_ETMCID2_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMCID2_ADDR, m)
#define HWIO_RPM_M3_ETM_ETMCID2_ETM_ETMCID2_BMSK                                  0xffffffff
#define HWIO_RPM_M3_ETM_ETMCID2_ETM_ETMCID2_SHFT                                         0x0

#define HWIO_RPM_M3_ETM_ETMCID3_ADDR                                              (RPM_M3_PPB_EXT_REG_BASE      + 0x00001ffc)
#define HWIO_RPM_M3_ETM_ETMCID3_RMSK                                              0xffffffff
#define HWIO_RPM_M3_ETM_ETMCID3_IN          \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMCID3_ADDR, HWIO_RPM_M3_ETM_ETMCID3_RMSK)
#define HWIO_RPM_M3_ETM_ETMCID3_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ETM_ETMCID3_ADDR, m)
#define HWIO_RPM_M3_ETM_ETMCID3_ETM_ETMCID3_BMSK                                  0xffffffff
#define HWIO_RPM_M3_ETM_ETMCID3_ETM_ETMCID3_SHFT                                         0x0

#define HWIO_RPM_M3_ROM_TABLE_SCS_ADDR                                            (RPM_M3_PPB_EXT_REG_BASE      + 0x000bf000)
#define HWIO_RPM_M3_ROM_TABLE_SCS_RMSK                                            0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_SCS_IN          \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_SCS_ADDR, HWIO_RPM_M3_ROM_TABLE_SCS_RMSK)
#define HWIO_RPM_M3_ROM_TABLE_SCS_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_SCS_ADDR, m)
#define HWIO_RPM_M3_ROM_TABLE_SCS_ROM_TABLE_SCS_BMSK                              0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_SCS_ROM_TABLE_SCS_SHFT                                     0x0

#define HWIO_RPM_M3_ROM_TABLE_DWT_ADDR                                            (RPM_M3_PPB_EXT_REG_BASE      + 0x000bf004)
#define HWIO_RPM_M3_ROM_TABLE_DWT_RMSK                                            0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_DWT_IN          \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_DWT_ADDR, HWIO_RPM_M3_ROM_TABLE_DWT_RMSK)
#define HWIO_RPM_M3_ROM_TABLE_DWT_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_DWT_ADDR, m)
#define HWIO_RPM_M3_ROM_TABLE_DWT_ROM_TABLE_DWT_BMSK                              0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_DWT_ROM_TABLE_DWT_SHFT                                     0x0

#define HWIO_RPM_M3_ROM_TABLE_FPB_ADDR                                            (RPM_M3_PPB_EXT_REG_BASE      + 0x000bf008)
#define HWIO_RPM_M3_ROM_TABLE_FPB_RMSK                                            0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_FPB_IN          \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_FPB_ADDR, HWIO_RPM_M3_ROM_TABLE_FPB_RMSK)
#define HWIO_RPM_M3_ROM_TABLE_FPB_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_FPB_ADDR, m)
#define HWIO_RPM_M3_ROM_TABLE_FPB_ROM_TABLE_FPB_BMSK                              0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_FPB_ROM_TABLE_FPB_SHFT                                     0x0

#define HWIO_RPM_M3_ROM_TABLE_ITM_ADDR                                            (RPM_M3_PPB_EXT_REG_BASE      + 0x000bf00c)
#define HWIO_RPM_M3_ROM_TABLE_ITM_RMSK                                            0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_ITM_IN          \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_ITM_ADDR, HWIO_RPM_M3_ROM_TABLE_ITM_RMSK)
#define HWIO_RPM_M3_ROM_TABLE_ITM_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_ITM_ADDR, m)
#define HWIO_RPM_M3_ROM_TABLE_ITM_ROM_TABLE_ITM_BMSK                              0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_ITM_ROM_TABLE_ITM_SHFT                                     0x0

#define HWIO_RPM_M3_ROM_TABLE_TPIU_ADDR                                           (RPM_M3_PPB_EXT_REG_BASE      + 0x000bf010)
#define HWIO_RPM_M3_ROM_TABLE_TPIU_RMSK                                           0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_TPIU_IN          \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_TPIU_ADDR, HWIO_RPM_M3_ROM_TABLE_TPIU_RMSK)
#define HWIO_RPM_M3_ROM_TABLE_TPIU_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_TPIU_ADDR, m)
#define HWIO_RPM_M3_ROM_TABLE_TPIU_ROM_TABLE_TPIU_BMSK                            0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_TPIU_ROM_TABLE_TPIU_SHFT                                   0x0

#define HWIO_RPM_M3_ROM_TABLE_ETM_ADDR                                            (RPM_M3_PPB_EXT_REG_BASE      + 0x000bf014)
#define HWIO_RPM_M3_ROM_TABLE_ETM_RMSK                                            0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_ETM_IN          \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_ETM_ADDR, HWIO_RPM_M3_ROM_TABLE_ETM_RMSK)
#define HWIO_RPM_M3_ROM_TABLE_ETM_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_ETM_ADDR, m)
#define HWIO_RPM_M3_ROM_TABLE_ETM_ROM_TABLE_ETM_BMSK                              0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_ETM_ROM_TABLE_ETM_SHFT                                     0x0

#define HWIO_RPM_M3_ROM_TABLE_END_ADDR                                            (RPM_M3_PPB_EXT_REG_BASE      + 0x000bf018)
#define HWIO_RPM_M3_ROM_TABLE_END_RMSK                                            0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_END_IN          \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_END_ADDR, HWIO_RPM_M3_ROM_TABLE_END_RMSK)
#define HWIO_RPM_M3_ROM_TABLE_END_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_END_ADDR, m)
#define HWIO_RPM_M3_ROM_TABLE_END_ROM_TABLE_END_BMSK                              0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_END_ROM_TABLE_END_SHFT                                     0x0

#define HWIO_RPM_M3_ROM_TABLE_SYSTEM_ACCESS_ADDR                                  (RPM_M3_PPB_EXT_REG_BASE      + 0x000bffcc)
#define HWIO_RPM_M3_ROM_TABLE_SYSTEM_ACCESS_RMSK                                  0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_SYSTEM_ACCESS_IN          \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_SYSTEM_ACCESS_ADDR, HWIO_RPM_M3_ROM_TABLE_SYSTEM_ACCESS_RMSK)
#define HWIO_RPM_M3_ROM_TABLE_SYSTEM_ACCESS_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_SYSTEM_ACCESS_ADDR, m)
#define HWIO_RPM_M3_ROM_TABLE_SYSTEM_ACCESS_ROM_TABLE_SYSTEM_ACCESS_BMSK          0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_SYSTEM_ACCESS_ROM_TABLE_SYSTEM_ACCESS_SHFT                 0x0

#define HWIO_RPM_M3_ROM_TABLE_PID4_ADDR                                           (RPM_M3_PPB_EXT_REG_BASE      + 0x000bffd0)
#define HWIO_RPM_M3_ROM_TABLE_PID4_RMSK                                           0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_PID4_IN          \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_PID4_ADDR, HWIO_RPM_M3_ROM_TABLE_PID4_RMSK)
#define HWIO_RPM_M3_ROM_TABLE_PID4_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_PID4_ADDR, m)
#define HWIO_RPM_M3_ROM_TABLE_PID4_ROM_TABLE_PID4_BMSK                            0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_PID4_ROM_TABLE_PID4_SHFT                                   0x0

#define HWIO_RPM_M3_ROM_TABLE_PID5_ADDR                                           (RPM_M3_PPB_EXT_REG_BASE      + 0x000bffd4)
#define HWIO_RPM_M3_ROM_TABLE_PID5_RMSK                                           0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_PID5_IN          \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_PID5_ADDR, HWIO_RPM_M3_ROM_TABLE_PID5_RMSK)
#define HWIO_RPM_M3_ROM_TABLE_PID5_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_PID5_ADDR, m)
#define HWIO_RPM_M3_ROM_TABLE_PID5_ROM_TABLE_PID5_BMSK                            0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_PID5_ROM_TABLE_PID5_SHFT                                   0x0

#define HWIO_RPM_M3_ROM_TABLE_PID6_ADDR                                           (RPM_M3_PPB_EXT_REG_BASE      + 0x000bffd8)
#define HWIO_RPM_M3_ROM_TABLE_PID6_RMSK                                           0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_PID6_IN          \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_PID6_ADDR, HWIO_RPM_M3_ROM_TABLE_PID6_RMSK)
#define HWIO_RPM_M3_ROM_TABLE_PID6_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_PID6_ADDR, m)
#define HWIO_RPM_M3_ROM_TABLE_PID6_ROM_TABLE_PID6_BMSK                            0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_PID6_ROM_TABLE_PID6_SHFT                                   0x0

#define HWIO_RPM_M3_ROM_TABLE_PID7_ADDR                                           (RPM_M3_PPB_EXT_REG_BASE      + 0x000bffdc)
#define HWIO_RPM_M3_ROM_TABLE_PID7_RMSK                                           0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_PID7_IN          \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_PID7_ADDR, HWIO_RPM_M3_ROM_TABLE_PID7_RMSK)
#define HWIO_RPM_M3_ROM_TABLE_PID7_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_PID7_ADDR, m)
#define HWIO_RPM_M3_ROM_TABLE_PID7_ROM_TABLE_PID7_BMSK                            0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_PID7_ROM_TABLE_PID7_SHFT                                   0x0

#define HWIO_RPM_M3_ROM_TABLE_PID0_ADDR                                           (RPM_M3_PPB_EXT_REG_BASE      + 0x000bffe0)
#define HWIO_RPM_M3_ROM_TABLE_PID0_RMSK                                           0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_PID0_IN          \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_PID0_ADDR, HWIO_RPM_M3_ROM_TABLE_PID0_RMSK)
#define HWIO_RPM_M3_ROM_TABLE_PID0_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_PID0_ADDR, m)
#define HWIO_RPM_M3_ROM_TABLE_PID0_ROM_TABLE_PID0_BMSK                            0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_PID0_ROM_TABLE_PID0_SHFT                                   0x0

#define HWIO_RPM_M3_ROM_TABLE_PID1_ADDR                                           (RPM_M3_PPB_EXT_REG_BASE      + 0x000bffe4)
#define HWIO_RPM_M3_ROM_TABLE_PID1_RMSK                                           0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_PID1_IN          \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_PID1_ADDR, HWIO_RPM_M3_ROM_TABLE_PID1_RMSK)
#define HWIO_RPM_M3_ROM_TABLE_PID1_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_PID1_ADDR, m)
#define HWIO_RPM_M3_ROM_TABLE_PID1_ROM_TABLE_PID1_BMSK                            0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_PID1_ROM_TABLE_PID1_SHFT                                   0x0

#define HWIO_RPM_M3_ROM_TABLE_PID2_ADDR                                           (RPM_M3_PPB_EXT_REG_BASE      + 0x000bffe8)
#define HWIO_RPM_M3_ROM_TABLE_PID2_RMSK                                           0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_PID2_IN          \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_PID2_ADDR, HWIO_RPM_M3_ROM_TABLE_PID2_RMSK)
#define HWIO_RPM_M3_ROM_TABLE_PID2_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_PID2_ADDR, m)
#define HWIO_RPM_M3_ROM_TABLE_PID2_ROM_TABLE_PID2_BMSK                            0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_PID2_ROM_TABLE_PID2_SHFT                                   0x0

#define HWIO_RPM_M3_ROM_TABLE_PID3_ADDR                                           (RPM_M3_PPB_EXT_REG_BASE      + 0x000bffec)
#define HWIO_RPM_M3_ROM_TABLE_PID3_RMSK                                           0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_PID3_IN          \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_PID3_ADDR, HWIO_RPM_M3_ROM_TABLE_PID3_RMSK)
#define HWIO_RPM_M3_ROM_TABLE_PID3_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_PID3_ADDR, m)
#define HWIO_RPM_M3_ROM_TABLE_PID3_ROM_TABLE_PID3_BMSK                            0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_PID3_ROM_TABLE_PID3_SHFT                                   0x0

#define HWIO_RPM_M3_ROM_TABLE_CID0_ADDR                                           (RPM_M3_PPB_EXT_REG_BASE      + 0x000bfff0)
#define HWIO_RPM_M3_ROM_TABLE_CID0_RMSK                                           0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_CID0_IN          \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_CID0_ADDR, HWIO_RPM_M3_ROM_TABLE_CID0_RMSK)
#define HWIO_RPM_M3_ROM_TABLE_CID0_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_CID0_ADDR, m)
#define HWIO_RPM_M3_ROM_TABLE_CID0_ROM_TABLE_CID0_BMSK                            0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_CID0_ROM_TABLE_CID0_SHFT                                   0x0

#define HWIO_RPM_M3_ROM_TABLE_CID1_ADDR                                           (RPM_M3_PPB_EXT_REG_BASE      + 0x000bfff4)
#define HWIO_RPM_M3_ROM_TABLE_CID1_RMSK                                           0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_CID1_IN          \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_CID1_ADDR, HWIO_RPM_M3_ROM_TABLE_CID1_RMSK)
#define HWIO_RPM_M3_ROM_TABLE_CID1_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_CID1_ADDR, m)
#define HWIO_RPM_M3_ROM_TABLE_CID1_ROM_TABLE_CID1_BMSK                            0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_CID1_ROM_TABLE_CID1_SHFT                                   0x0

#define HWIO_RPM_M3_ROM_TABLE_CID2_ADDR                                           (RPM_M3_PPB_EXT_REG_BASE      + 0x000bfff8)
#define HWIO_RPM_M3_ROM_TABLE_CID2_RMSK                                           0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_CID2_IN          \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_CID2_ADDR, HWIO_RPM_M3_ROM_TABLE_CID2_RMSK)
#define HWIO_RPM_M3_ROM_TABLE_CID2_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_CID2_ADDR, m)
#define HWIO_RPM_M3_ROM_TABLE_CID2_ROM_TABLE_CID2_BMSK                            0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_CID2_ROM_TABLE_CID2_SHFT                                   0x0

#define HWIO_RPM_M3_ROM_TABLE_CID3_ADDR                                           (RPM_M3_PPB_EXT_REG_BASE      + 0x000bfffc)
#define HWIO_RPM_M3_ROM_TABLE_CID3_RMSK                                           0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_CID3_IN          \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_CID3_ADDR, HWIO_RPM_M3_ROM_TABLE_CID3_RMSK)
#define HWIO_RPM_M3_ROM_TABLE_CID3_INM(m)      \
        in_dword_masked(HWIO_RPM_M3_ROM_TABLE_CID3_ADDR, m)
#define HWIO_RPM_M3_ROM_TABLE_CID3_ROM_TABLE_CID3_BMSK                            0xffffffff
#define HWIO_RPM_M3_ROM_TABLE_CID3_ROM_TABLE_CID3_SHFT                                   0x0

/*----------------------------------------------------------------------------
 * MODULE: RPM_MSG_RAM
 *--------------------------------------------------------------------------*/

#define RPM_MSG_RAM_REG_BASE (RPM_MSG_RAM_BASE      + 0x00000000)


#endif /* __RPM_TARGET_HWIO_H__ */
