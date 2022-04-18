#ifndef __HALAONINTHWIO_H__
#define __HALAONINTHWIO_H__
/*
===========================================================================
*/
/**
  @file HALaonintHWIO.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    SDM660 (Starlord) [starlord_v1.0.2_p3q3r108_MTO]
 
  This file contains HWIO register definitions for the following modules:
    LPASS_SCSR_REGS
    LPASS_PMU_REGS
    LPASS_TCSR

  'Include' filters applied: AHBE_SPARE[LPASS_TCSR] 
  'Exclude' filters applied: 
*/
/*
  ===========================================================================

  Copyright (c) 2017 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

  Export of this technology or software is regulated by the U.S. Government.
  Diversion contrary to U.S. law prohibited.

  All ideas, data and information contained in or disclosed by
  this document are confidential and proprietary information of
  Qualcomm Technologies, Inc. and all rights therein are expressly reserved.
  By accepting this material the recipient agrees that this material
  and the information contained therein are held in confidence and in
  trust and will not be used, copied, reproduced in whole or in part,
  nor its contents revealed in any manner to others without the express
  written permission of Qualcomm Technologies, Inc.

  ===========================================================================

  $Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/aonint/hw/sdm660/HALaonintHWIO.h#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $

  ===========================================================================
*/
#include "msmhwiobase.h"
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
#define HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_SLP_CORR_EN_NOCORRECTION_FVAL                       0x0
#define HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_SLP_CORR_EN_CORRECT4TIMEINSLP_FVAL                  0x1
#define HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_SOURCE_BMSK                                         0x3
#define HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_SOURCE_SHFT                                         0x0
#define HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_SOURCE_QDSS_FVAL                                    0x0
#define HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_SOURCE_WCSSDBG_FVAL                                 0x1
#define HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_SOURCE_AUTO_FVAL                                    0x2

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
#define HWIO_LPASS_SCSR_WCSS_CLK_INFO_SRC_PLL_FVAL                                         0x0
#define HWIO_LPASS_SCSR_WCSS_CLK_INFO_SRC_XO_FVAL                                          0x1

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
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_TRIG_POS_PRE_TRIG_FVAL                     0x0
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_TRIG_POS_MID_TRIG_FVAL                     0x1
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_TRIG_POS_POST_TRIG_FVAL                    0x2

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
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_TRIG_SEL_TRIG_SEL0_FVAL                    0x0
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_TRIG_SEL_TRIG_SEL1_FVAL                    0x1
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_TRIG_SEL_TRIG_SEL2_FVAL                    0x2
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_TRIG_SEL_TRIG_SEL3_FVAL                    0x3
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_TRIG_SEL_TRIG_SEL4_FVAL                    0x4
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_TRIG_SEL_TRIG_SEL5_FVAL                    0x5
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_TRIG_SEL_TRIG_SEL6_FVAL                    0x6
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_TRIG_SEL_TRIG_SEL7_FVAL                    0x7
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_MODE_SEL_BMSK                             0x10
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_MODE_SEL_SHFT                              0x4
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_MODE_SEL_INTERRUPT_MODE_FVAL               0x0
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_MODE_SEL_WATERMARK_MODE_FVAL               0x1
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_VCO_FILTER_EN_BMSK                         0x8
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_VCO_FILTER_EN_SHFT                         0x3
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_SLOPE_DELTA_CYC_BMSK                       0x7
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_SLOPE_DELTA_CYC_SHFT                       0x0
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_1_FVAL        0x0
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_2_FVAL        0x1
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_4_FVAL        0x2
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_8_FVAL        0x3
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_16_FVAL        0x4
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_32_FVAL        0x5
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_48_FVAL        0x6
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_63_FVAL        0x7

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
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_TRIG_POS_PRE_TRIG_FVAL                     0x0
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_TRIG_POS_MID_TRIG_FVAL                     0x1
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_TRIG_POS_POST_TRIG_FVAL                    0x2

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
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_TRIG_SEL_TRIG_SEL0_FVAL                    0x0
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_TRIG_SEL_TRIG_SEL1_FVAL                    0x1
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_TRIG_SEL_TRIG_SEL2_FVAL                    0x2
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_TRIG_SEL_TRIG_SEL3_FVAL                    0x3
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_TRIG_SEL_TRIG_SEL4_FVAL                    0x4
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_TRIG_SEL_TRIG_SEL5_FVAL                    0x5
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_TRIG_SEL_TRIG_SEL6_FVAL                    0x6
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_TRIG_SEL_TRIG_SEL7_FVAL                    0x7
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_MODE_SEL_BMSK                             0x10
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_MODE_SEL_SHFT                              0x4
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_MODE_SEL_INTERRUPT_MODE_FVAL               0x0
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_MODE_SEL_WATERMARK_MODE_FVAL               0x1
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_VCO_FILTER_EN_BMSK                         0x8
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_VCO_FILTER_EN_SHFT                         0x3
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_SLOPE_DELTA_CYC_BMSK                       0x7
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_SLOPE_DELTA_CYC_SHFT                       0x0
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_1_FVAL        0x0
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_2_FVAL        0x1
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_4_FVAL        0x2
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_8_FVAL        0x3
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_16_FVAL        0x4
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_32_FVAL        0x5
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_48_FVAL        0x6
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_63_FVAL        0x7

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
 * MODULE: LPASS_PMU_REGS
 *--------------------------------------------------------------------------*/

#define LPASS_PMU_REGS_REG_BASE                                            (LPASS_BASE      + 0x00060000)

#define HWIO_LPASS_PMU_SPARE_ADDR                                          (LPASS_PMU_REGS_REG_BASE      + 0x00000000)
#define HWIO_LPASS_PMU_SPARE_RMSK                                          0xffffffff
#define HWIO_LPASS_PMU_SPARE_IN          \
        in_dword_masked(HWIO_LPASS_PMU_SPARE_ADDR, HWIO_LPASS_PMU_SPARE_RMSK)
#define HWIO_LPASS_PMU_SPARE_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_SPARE_ADDR, m)
#define HWIO_LPASS_PMU_SPARE_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_SPARE_ADDR,v)
#define HWIO_LPASS_PMU_SPARE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_PMU_SPARE_ADDR,m,v,HWIO_LPASS_PMU_SPARE_IN)
#define HWIO_LPASS_PMU_SPARE_PMU_SPARE_IN_BMSK                             0xffff0000
#define HWIO_LPASS_PMU_SPARE_PMU_SPARE_IN_SHFT                                   0x10
#define HWIO_LPASS_PMU_SPARE_PMU_SPARE_OUT_BMSK                                0xffff
#define HWIO_LPASS_PMU_SPARE_PMU_SPARE_OUT_SHFT                                   0x0

#define HWIO_LPASS_PMU_COUNTER_CFG_ADDR                                    (LPASS_PMU_REGS_REG_BASE      + 0x00000004)
#define HWIO_LPASS_PMU_COUNTER_CFG_RMSK                                           0x1
#define HWIO_LPASS_PMU_COUNTER_CFG_IN          \
        in_dword_masked(HWIO_LPASS_PMU_COUNTER_CFG_ADDR, HWIO_LPASS_PMU_COUNTER_CFG_RMSK)
#define HWIO_LPASS_PMU_COUNTER_CFG_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_COUNTER_CFG_ADDR, m)
#define HWIO_LPASS_PMU_COUNTER_CFG_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_COUNTER_CFG_ADDR,v)
#define HWIO_LPASS_PMU_COUNTER_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_PMU_COUNTER_CFG_ADDR,m,v,HWIO_LPASS_PMU_COUNTER_CFG_IN)
#define HWIO_LPASS_PMU_COUNTER_CFG_PMU_QCNTR_EN_BMSK                              0x1
#define HWIO_LPASS_PMU_COUNTER_CFG_PMU_QCNTR_EN_SHFT                              0x0

#define HWIO_LPASS_PMU_COUNTER_CTL_STAT_ADDR                               (LPASS_PMU_REGS_REG_BASE      + 0x00000008)
#define HWIO_LPASS_PMU_COUNTER_CTL_STAT_RMSK                                  0x18003
#define HWIO_LPASS_PMU_COUNTER_CTL_STAT_IN          \
        in_dword_masked(HWIO_LPASS_PMU_COUNTER_CTL_STAT_ADDR, HWIO_LPASS_PMU_COUNTER_CTL_STAT_RMSK)
#define HWIO_LPASS_PMU_COUNTER_CTL_STAT_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_COUNTER_CTL_STAT_ADDR, m)
#define HWIO_LPASS_PMU_COUNTER_CTL_STAT_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_COUNTER_CTL_STAT_ADDR,v)
#define HWIO_LPASS_PMU_COUNTER_CTL_STAT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_PMU_COUNTER_CTL_STAT_ADDR,m,v,HWIO_LPASS_PMU_COUNTER_CTL_STAT_IN)
#define HWIO_LPASS_PMU_COUNTER_CTL_STAT_PMU_QCNTR_LD_COMPL_BMSK               0x10000
#define HWIO_LPASS_PMU_COUNTER_CTL_STAT_PMU_QCNTR_LD_COMPL_SHFT                  0x10
#define HWIO_LPASS_PMU_COUNTER_CTL_STAT_PMU_QCNTR_SYNC_COMPL_BMSK              0x8000
#define HWIO_LPASS_PMU_COUNTER_CTL_STAT_PMU_QCNTR_SYNC_COMPL_SHFT                 0xf
#define HWIO_LPASS_PMU_COUNTER_CTL_STAT_PMU_QCNTR_SYNC_PULSE_BMSK                 0x2
#define HWIO_LPASS_PMU_COUNTER_CTL_STAT_PMU_QCNTR_SYNC_PULSE_SHFT                 0x1
#define HWIO_LPASS_PMU_COUNTER_CTL_STAT_PMU_QCNTR_PRE_LD_BMSK                     0x1
#define HWIO_LPASS_PMU_COUNTER_CTL_STAT_PMU_QCNTR_PRE_LD_SHFT                     0x0

#define HWIO_LPASS_PMU_COUNTER_OFF_ADDR                                    (LPASS_PMU_REGS_REG_BASE      + 0x0000000c)
#define HWIO_LPASS_PMU_COUNTER_OFF_RMSK                                        0xffff
#define HWIO_LPASS_PMU_COUNTER_OFF_IN          \
        in_dword_masked(HWIO_LPASS_PMU_COUNTER_OFF_ADDR, HWIO_LPASS_PMU_COUNTER_OFF_RMSK)
#define HWIO_LPASS_PMU_COUNTER_OFF_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_COUNTER_OFF_ADDR, m)
#define HWIO_LPASS_PMU_COUNTER_OFF_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_COUNTER_OFF_ADDR,v)
#define HWIO_LPASS_PMU_COUNTER_OFF_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_PMU_COUNTER_OFF_ADDR,m,v,HWIO_LPASS_PMU_COUNTER_OFF_IN)
#define HWIO_LPASS_PMU_COUNTER_OFF_PMU_QCNTR_OFFSET_BMSK                       0xffff
#define HWIO_LPASS_PMU_COUNTER_OFF_PMU_QCNTR_OFFSET_SHFT                          0x0

#define HWIO_LPASS_PMU_SLP_TMR_CTL_ADDR                                    (LPASS_PMU_REGS_REG_BASE      + 0x00000010)
#define HWIO_LPASS_PMU_SLP_TMR_CTL_RMSK                                       0x18003
#define HWIO_LPASS_PMU_SLP_TMR_CTL_IN          \
        in_dword_masked(HWIO_LPASS_PMU_SLP_TMR_CTL_ADDR, HWIO_LPASS_PMU_SLP_TMR_CTL_RMSK)
#define HWIO_LPASS_PMU_SLP_TMR_CTL_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_SLP_TMR_CTL_ADDR, m)
#define HWIO_LPASS_PMU_SLP_TMR_CTL_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_SLP_TMR_CTL_ADDR,v)
#define HWIO_LPASS_PMU_SLP_TMR_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_PMU_SLP_TMR_CTL_ADDR,m,v,HWIO_LPASS_PMU_SLP_TMR_CTL_IN)
#define HWIO_LPASS_PMU_SLP_TMR_CTL_PMU_SW_SLP_TMR_INT_RAW_BMSK                0x10000
#define HWIO_LPASS_PMU_SLP_TMR_CTL_PMU_SW_SLP_TMR_INT_RAW_SHFT                   0x10
#define HWIO_LPASS_PMU_SLP_TMR_CTL_PMU_SW_SLP_TMR_INT_BMSK                     0x8000
#define HWIO_LPASS_PMU_SLP_TMR_CTL_PMU_SW_SLP_TMR_INT_SHFT                        0xf
#define HWIO_LPASS_PMU_SLP_TMR_CTL_PMU_SW_SLP_TMR_EXP_WR_BMSK                     0x2
#define HWIO_LPASS_PMU_SLP_TMR_CTL_PMU_SW_SLP_TMR_EXP_WR_SHFT                     0x1
#define HWIO_LPASS_PMU_SLP_TMR_CTL_PMU_SW_SLP_TMR_INT_CLR_BMSK                    0x1
#define HWIO_LPASS_PMU_SLP_TMR_CTL_PMU_SW_SLP_TMR_INT_CLR_SHFT                    0x0

#define HWIO_LPASS_PMU_SLP_TMR_EXP_LO_ADDR                                 (LPASS_PMU_REGS_REG_BASE      + 0x00000014)
#define HWIO_LPASS_PMU_SLP_TMR_EXP_LO_RMSK                                 0xffffffff
#define HWIO_LPASS_PMU_SLP_TMR_EXP_LO_IN          \
        in_dword_masked(HWIO_LPASS_PMU_SLP_TMR_EXP_LO_ADDR, HWIO_LPASS_PMU_SLP_TMR_EXP_LO_RMSK)
#define HWIO_LPASS_PMU_SLP_TMR_EXP_LO_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_SLP_TMR_EXP_LO_ADDR, m)
#define HWIO_LPASS_PMU_SLP_TMR_EXP_LO_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_SLP_TMR_EXP_LO_ADDR,v)
#define HWIO_LPASS_PMU_SLP_TMR_EXP_LO_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_PMU_SLP_TMR_EXP_LO_ADDR,m,v,HWIO_LPASS_PMU_SLP_TMR_EXP_LO_IN)
#define HWIO_LPASS_PMU_SLP_TMR_EXP_LO_PMU_SW_SLP_TMR_EXP_LO_BMSK           0xffffffff
#define HWIO_LPASS_PMU_SLP_TMR_EXP_LO_PMU_SW_SLP_TMR_EXP_LO_SHFT                  0x0

#define HWIO_LPASS_PMU_SLP_TMR_EXP_HI_ADDR                                 (LPASS_PMU_REGS_REG_BASE      + 0x00000018)
#define HWIO_LPASS_PMU_SLP_TMR_EXP_HI_RMSK                                   0xffffff
#define HWIO_LPASS_PMU_SLP_TMR_EXP_HI_IN          \
        in_dword_masked(HWIO_LPASS_PMU_SLP_TMR_EXP_HI_ADDR, HWIO_LPASS_PMU_SLP_TMR_EXP_HI_RMSK)
#define HWIO_LPASS_PMU_SLP_TMR_EXP_HI_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_SLP_TMR_EXP_HI_ADDR, m)
#define HWIO_LPASS_PMU_SLP_TMR_EXP_HI_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_SLP_TMR_EXP_HI_ADDR,v)
#define HWIO_LPASS_PMU_SLP_TMR_EXP_HI_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_PMU_SLP_TMR_EXP_HI_ADDR,m,v,HWIO_LPASS_PMU_SLP_TMR_EXP_HI_IN)
#define HWIO_LPASS_PMU_SLP_TMR_EXP_HI_PMU_SW_SLP_TMR_EXP_HI_BMSK             0xffffff
#define HWIO_LPASS_PMU_SLP_TMR_EXP_HI_PMU_SW_SLP_TMR_EXP_HI_SHFT                  0x0

#define HWIO_LPASS_PMU_SM_CSR0_ADDR                                        (LPASS_PMU_REGS_REG_BASE      + 0x00000024)
#define HWIO_LPASS_PMU_SM_CSR0_RMSK                                        0xf0000c07
#define HWIO_LPASS_PMU_SM_CSR0_IN          \
        in_dword_masked(HWIO_LPASS_PMU_SM_CSR0_ADDR, HWIO_LPASS_PMU_SM_CSR0_RMSK)
#define HWIO_LPASS_PMU_SM_CSR0_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_SM_CSR0_ADDR, m)
#define HWIO_LPASS_PMU_SM_CSR0_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_SM_CSR0_ADDR,v)
#define HWIO_LPASS_PMU_SM_CSR0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_PMU_SM_CSR0_ADDR,m,v,HWIO_LPASS_PMU_SM_CSR0_IN)
#define HWIO_LPASS_PMU_SM_CSR0_PMU_PMU_AON_SM_BMSK                         0xf0000000
#define HWIO_LPASS_PMU_SM_CSR0_PMU_PMU_AON_SM_SHFT                               0x1c
#define HWIO_LPASS_PMU_SM_CSR0_PMU_PWRDN_REQ_BMSK                               0x800
#define HWIO_LPASS_PMU_SM_CSR0_PMU_PWRDN_REQ_SHFT                                 0xb
#define HWIO_LPASS_PMU_SM_CSR0_PMU_PEEL_MODE_OVRD_BMSK                          0x400
#define HWIO_LPASS_PMU_SM_CSR0_PMU_PEEL_MODE_OVRD_SHFT                            0xa
#define HWIO_LPASS_PMU_SM_CSR0_PMU_FAST_WAKEUP_EN_BMSK                            0x4
#define HWIO_LPASS_PMU_SM_CSR0_PMU_FAST_WAKEUP_EN_SHFT                            0x2
#define HWIO_LPASS_PMU_SM_CSR0_PMU_NO_RET_MSM_BMSK                                0x2
#define HWIO_LPASS_PMU_SM_CSR0_PMU_NO_RET_MSM_SHFT                                0x1
#define HWIO_LPASS_PMU_SM_CSR0_PMU_NO_RETENTION_BMSK                              0x1
#define HWIO_LPASS_PMU_SM_CSR0_PMU_NO_RETENTION_SHFT                              0x0

#define HWIO_LPASS_PMU_SM_CSR1_ADDR                                        (LPASS_PMU_REGS_REG_BASE      + 0x00000028)
#define HWIO_LPASS_PMU_SM_CSR1_RMSK                                             0xfff
#define HWIO_LPASS_PMU_SM_CSR1_IN          \
        in_dword_masked(HWIO_LPASS_PMU_SM_CSR1_ADDR, HWIO_LPASS_PMU_SM_CSR1_RMSK)
#define HWIO_LPASS_PMU_SM_CSR1_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_SM_CSR1_ADDR, m)
#define HWIO_LPASS_PMU_SM_CSR1_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_SM_CSR1_ADDR,v)
#define HWIO_LPASS_PMU_SM_CSR1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_PMU_SM_CSR1_ADDR,m,v,HWIO_LPASS_PMU_SM_CSR1_IN)
#define HWIO_LPASS_PMU_SM_CSR1_PMU_START_DLY_BMSK                               0xe00
#define HWIO_LPASS_PMU_SM_CSR1_PMU_START_DLY_SHFT                                 0x9
#define HWIO_LPASS_PMU_SM_CSR1_PMU_PEEL_TMR_EN_BMSK                             0x100
#define HWIO_LPASS_PMU_SM_CSR1_PMU_PEEL_TMR_EN_SHFT                               0x8
#define HWIO_LPASS_PMU_SM_CSR1_PMU_PEEL_LOCKDLY_WR_BMSK                          0x80
#define HWIO_LPASS_PMU_SM_CSR1_PMU_PEEL_LOCKDLY_WR_SHFT                           0x7
#define HWIO_LPASS_PMU_SM_CSR1_PMU_PEEL_LOCKDLY_BMSK                             0x7f
#define HWIO_LPASS_PMU_SM_CSR1_PMU_PEEL_LOCKDLY_SHFT                              0x0

#define HWIO_LPASS_PMU_SWITCHER_DLY_ADDR                                   (LPASS_PMU_REGS_REG_BASE      + 0x0000002c)
#define HWIO_LPASS_PMU_SWITCHER_DLY_RMSK                                   0xffffffff
#define HWIO_LPASS_PMU_SWITCHER_DLY_IN          \
        in_dword_masked(HWIO_LPASS_PMU_SWITCHER_DLY_ADDR, HWIO_LPASS_PMU_SWITCHER_DLY_RMSK)
#define HWIO_LPASS_PMU_SWITCHER_DLY_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_SWITCHER_DLY_ADDR, m)
#define HWIO_LPASS_PMU_SWITCHER_DLY_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_SWITCHER_DLY_ADDR,v)
#define HWIO_LPASS_PMU_SWITCHER_DLY_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_PMU_SWITCHER_DLY_ADDR,m,v,HWIO_LPASS_PMU_SWITCHER_DLY_IN)
#define HWIO_LPASS_PMU_SWITCHER_DLY_PMU_SWITCHER_DLY_WR_BMSK               0x80000000
#define HWIO_LPASS_PMU_SWITCHER_DLY_PMU_SWITCHER_DLY_WR_SHFT                     0x1f
#define HWIO_LPASS_PMU_SWITCHER_DLY_PMU_PBS_WAIT_DLY_BMSK                  0x7fff0000
#define HWIO_LPASS_PMU_SWITCHER_DLY_PMU_PBS_WAIT_DLY_SHFT                        0x10
#define HWIO_LPASS_PMU_SWITCHER_DLY_PMU_SWITCHER_DLY_BMSK                      0xffff
#define HWIO_LPASS_PMU_SWITCHER_DLY_PMU_SWITCHER_DLY_SHFT                         0x0

#define HWIO_LPASS_PMU_INT_ISO_ADDR                                        (LPASS_PMU_REGS_REG_BASE      + 0x00000030)
#define HWIO_LPASS_PMU_INT_ISO_RMSK                                               0x1
#define HWIO_LPASS_PMU_INT_ISO_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_INT_ISO_ADDR,v)
#define HWIO_LPASS_PMU_INT_ISO_PMU_INT_ISO_REQ_BMSK                               0x1
#define HWIO_LPASS_PMU_INT_ISO_PMU_INT_ISO_REQ_SHFT                               0x0

#define HWIO_LPASS_PMU_INT_CLR0_ADDR                                       (LPASS_PMU_REGS_REG_BASE      + 0x00000034)
#define HWIO_LPASS_PMU_INT_CLR0_RMSK                                       0xffffffff
#define HWIO_LPASS_PMU_INT_CLR0_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_INT_CLR0_ADDR,v)
#define HWIO_LPASS_PMU_INT_CLR0_PMU_INT_CLR0_BMSK                          0xffffffff
#define HWIO_LPASS_PMU_INT_CLR0_PMU_INT_CLR0_SHFT                                 0x0

#define HWIO_LPASS_PMU_INT_CLR1_ADDR                                       (LPASS_PMU_REGS_REG_BASE      + 0x00000038)
#define HWIO_LPASS_PMU_INT_CLR1_RMSK                                       0xffffffff
#define HWIO_LPASS_PMU_INT_CLR1_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_INT_CLR1_ADDR,v)
#define HWIO_LPASS_PMU_INT_CLR1_PMU_INT_CLR1_BMSK                          0xffffffff
#define HWIO_LPASS_PMU_INT_CLR1_PMU_INT_CLR1_SHFT                                 0x0

#define HWIO_LPASS_PMU_INT_CLR2_ADDR                                       (LPASS_PMU_REGS_REG_BASE      + 0x0000003c)
#define HWIO_LPASS_PMU_INT_CLR2_RMSK                                       0xffffffff
#define HWIO_LPASS_PMU_INT_CLR2_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_INT_CLR2_ADDR,v)
#define HWIO_LPASS_PMU_INT_CLR2_PMU_INT_CLR2_BMSK                          0xffffffff
#define HWIO_LPASS_PMU_INT_CLR2_PMU_INT_CLR2_SHFT                                 0x0

#define HWIO_LPASS_PMU_INT_CLR3_ADDR                                       (LPASS_PMU_REGS_REG_BASE      + 0x00000040)
#define HWIO_LPASS_PMU_INT_CLR3_RMSK                                       0xffffffff
#define HWIO_LPASS_PMU_INT_CLR3_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_INT_CLR3_ADDR,v)
#define HWIO_LPASS_PMU_INT_CLR3_PMU_INT_CLR3_BMSK                          0xffffffff
#define HWIO_LPASS_PMU_INT_CLR3_PMU_INT_CLR3_SHFT                                 0x0

#define HWIO_LPASS_PMU_INT_CLR4_ADDR                                       (LPASS_PMU_REGS_REG_BASE      + 0x00000044)
#define HWIO_LPASS_PMU_INT_CLR4_RMSK                                       0xffffffff
#define HWIO_LPASS_PMU_INT_CLR4_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_INT_CLR4_ADDR,v)
#define HWIO_LPASS_PMU_INT_CLR4_PMU_INT_CLR4_BMSK                          0xffffffff
#define HWIO_LPASS_PMU_INT_CLR4_PMU_INT_CLR4_SHFT                                 0x0

#define HWIO_LPASS_PMU_INT_POL0_ADDR                                       (LPASS_PMU_REGS_REG_BASE      + 0x00000048)
#define HWIO_LPASS_PMU_INT_POL0_RMSK                                       0xffffffff
#define HWIO_LPASS_PMU_INT_POL0_IN          \
        in_dword_masked(HWIO_LPASS_PMU_INT_POL0_ADDR, HWIO_LPASS_PMU_INT_POL0_RMSK)
#define HWIO_LPASS_PMU_INT_POL0_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_INT_POL0_ADDR, m)
#define HWIO_LPASS_PMU_INT_POL0_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_INT_POL0_ADDR,v)
#define HWIO_LPASS_PMU_INT_POL0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_PMU_INT_POL0_ADDR,m,v,HWIO_LPASS_PMU_INT_POL0_IN)
#define HWIO_LPASS_PMU_INT_POL0_PMU_INT_POL0_BMSK                          0xffffffff
#define HWIO_LPASS_PMU_INT_POL0_PMU_INT_POL0_SHFT                                 0x0

#define HWIO_LPASS_PMU_INT_POL1_ADDR                                       (LPASS_PMU_REGS_REG_BASE      + 0x0000004c)
#define HWIO_LPASS_PMU_INT_POL1_RMSK                                       0xffffffff
#define HWIO_LPASS_PMU_INT_POL1_IN          \
        in_dword_masked(HWIO_LPASS_PMU_INT_POL1_ADDR, HWIO_LPASS_PMU_INT_POL1_RMSK)
#define HWIO_LPASS_PMU_INT_POL1_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_INT_POL1_ADDR, m)
#define HWIO_LPASS_PMU_INT_POL1_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_INT_POL1_ADDR,v)
#define HWIO_LPASS_PMU_INT_POL1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_PMU_INT_POL1_ADDR,m,v,HWIO_LPASS_PMU_INT_POL1_IN)
#define HWIO_LPASS_PMU_INT_POL1_PMU_INT_POL1_BMSK                          0xffffffff
#define HWIO_LPASS_PMU_INT_POL1_PMU_INT_POL1_SHFT                                 0x0

#define HWIO_LPASS_PMU_INT_POL2_ADDR                                       (LPASS_PMU_REGS_REG_BASE      + 0x00000050)
#define HWIO_LPASS_PMU_INT_POL2_RMSK                                       0xffffffff
#define HWIO_LPASS_PMU_INT_POL2_IN          \
        in_dword_masked(HWIO_LPASS_PMU_INT_POL2_ADDR, HWIO_LPASS_PMU_INT_POL2_RMSK)
#define HWIO_LPASS_PMU_INT_POL2_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_INT_POL2_ADDR, m)
#define HWIO_LPASS_PMU_INT_POL2_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_INT_POL2_ADDR,v)
#define HWIO_LPASS_PMU_INT_POL2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_PMU_INT_POL2_ADDR,m,v,HWIO_LPASS_PMU_INT_POL2_IN)
#define HWIO_LPASS_PMU_INT_POL2_PMU_INT_POL2_BMSK                          0xffffffff
#define HWIO_LPASS_PMU_INT_POL2_PMU_INT_POL2_SHFT                                 0x0

#define HWIO_LPASS_PMU_INT_POL3_ADDR                                       (LPASS_PMU_REGS_REG_BASE      + 0x00000054)
#define HWIO_LPASS_PMU_INT_POL3_RMSK                                       0xffffffff
#define HWIO_LPASS_PMU_INT_POL3_IN          \
        in_dword_masked(HWIO_LPASS_PMU_INT_POL3_ADDR, HWIO_LPASS_PMU_INT_POL3_RMSK)
#define HWIO_LPASS_PMU_INT_POL3_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_INT_POL3_ADDR, m)
#define HWIO_LPASS_PMU_INT_POL3_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_INT_POL3_ADDR,v)
#define HWIO_LPASS_PMU_INT_POL3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_PMU_INT_POL3_ADDR,m,v,HWIO_LPASS_PMU_INT_POL3_IN)
#define HWIO_LPASS_PMU_INT_POL3_PMU_INT_POL3_BMSK                          0xffffffff
#define HWIO_LPASS_PMU_INT_POL3_PMU_INT_POL3_SHFT                                 0x0

#define HWIO_LPASS_PMU_INT_POL4_ADDR                                       (LPASS_PMU_REGS_REG_BASE      + 0x00000058)
#define HWIO_LPASS_PMU_INT_POL4_RMSK                                       0xffffffff
#define HWIO_LPASS_PMU_INT_POL4_IN          \
        in_dword_masked(HWIO_LPASS_PMU_INT_POL4_ADDR, HWIO_LPASS_PMU_INT_POL4_RMSK)
#define HWIO_LPASS_PMU_INT_POL4_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_INT_POL4_ADDR, m)
#define HWIO_LPASS_PMU_INT_POL4_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_INT_POL4_ADDR,v)
#define HWIO_LPASS_PMU_INT_POL4_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_PMU_INT_POL4_ADDR,m,v,HWIO_LPASS_PMU_INT_POL4_IN)
#define HWIO_LPASS_PMU_INT_POL4_PMU_INT_POL4_BMSK                          0xffffffff
#define HWIO_LPASS_PMU_INT_POL4_PMU_INT_POL4_SHFT                                 0x0

#define HWIO_LPASS_PMU_INT_POS_EDGE_EN0_ADDR                               (LPASS_PMU_REGS_REG_BASE      + 0x0000005c)
#define HWIO_LPASS_PMU_INT_POS_EDGE_EN0_RMSK                               0xffffffff
#define HWIO_LPASS_PMU_INT_POS_EDGE_EN0_IN          \
        in_dword_masked(HWIO_LPASS_PMU_INT_POS_EDGE_EN0_ADDR, HWIO_LPASS_PMU_INT_POS_EDGE_EN0_RMSK)
#define HWIO_LPASS_PMU_INT_POS_EDGE_EN0_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_INT_POS_EDGE_EN0_ADDR, m)
#define HWIO_LPASS_PMU_INT_POS_EDGE_EN0_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_INT_POS_EDGE_EN0_ADDR,v)
#define HWIO_LPASS_PMU_INT_POS_EDGE_EN0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_PMU_INT_POS_EDGE_EN0_ADDR,m,v,HWIO_LPASS_PMU_INT_POS_EDGE_EN0_IN)
#define HWIO_LPASS_PMU_INT_POS_EDGE_EN0_PMU_INT_POS_EDGE_EN0_BMSK          0xffffffff
#define HWIO_LPASS_PMU_INT_POS_EDGE_EN0_PMU_INT_POS_EDGE_EN0_SHFT                 0x0

#define HWIO_LPASS_PMU_INT_POS_EDGE_EN1_ADDR                               (LPASS_PMU_REGS_REG_BASE      + 0x00000060)
#define HWIO_LPASS_PMU_INT_POS_EDGE_EN1_RMSK                               0xffffffff
#define HWIO_LPASS_PMU_INT_POS_EDGE_EN1_IN          \
        in_dword_masked(HWIO_LPASS_PMU_INT_POS_EDGE_EN1_ADDR, HWIO_LPASS_PMU_INT_POS_EDGE_EN1_RMSK)
#define HWIO_LPASS_PMU_INT_POS_EDGE_EN1_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_INT_POS_EDGE_EN1_ADDR, m)
#define HWIO_LPASS_PMU_INT_POS_EDGE_EN1_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_INT_POS_EDGE_EN1_ADDR,v)
#define HWIO_LPASS_PMU_INT_POS_EDGE_EN1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_PMU_INT_POS_EDGE_EN1_ADDR,m,v,HWIO_LPASS_PMU_INT_POS_EDGE_EN1_IN)
#define HWIO_LPASS_PMU_INT_POS_EDGE_EN1_PMU_INT_POS_EDGE_EN1_BMSK          0xffffffff
#define HWIO_LPASS_PMU_INT_POS_EDGE_EN1_PMU_INT_POS_EDGE_EN1_SHFT                 0x0

#define HWIO_LPASS_PMU_INT_POS_EDGE_EN2_ADDR                               (LPASS_PMU_REGS_REG_BASE      + 0x00000064)
#define HWIO_LPASS_PMU_INT_POS_EDGE_EN2_RMSK                               0xffffffff
#define HWIO_LPASS_PMU_INT_POS_EDGE_EN2_IN          \
        in_dword_masked(HWIO_LPASS_PMU_INT_POS_EDGE_EN2_ADDR, HWIO_LPASS_PMU_INT_POS_EDGE_EN2_RMSK)
#define HWIO_LPASS_PMU_INT_POS_EDGE_EN2_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_INT_POS_EDGE_EN2_ADDR, m)
#define HWIO_LPASS_PMU_INT_POS_EDGE_EN2_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_INT_POS_EDGE_EN2_ADDR,v)
#define HWIO_LPASS_PMU_INT_POS_EDGE_EN2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_PMU_INT_POS_EDGE_EN2_ADDR,m,v,HWIO_LPASS_PMU_INT_POS_EDGE_EN2_IN)
#define HWIO_LPASS_PMU_INT_POS_EDGE_EN2_PMU_INT_POS_EDGE_EN2_BMSK          0xffffffff
#define HWIO_LPASS_PMU_INT_POS_EDGE_EN2_PMU_INT_POS_EDGE_EN2_SHFT                 0x0

#define HWIO_LPASS_PMU_INT_POS_EDGE_EN3_ADDR                               (LPASS_PMU_REGS_REG_BASE      + 0x00000068)
#define HWIO_LPASS_PMU_INT_POS_EDGE_EN3_RMSK                               0xffffffff
#define HWIO_LPASS_PMU_INT_POS_EDGE_EN3_IN          \
        in_dword_masked(HWIO_LPASS_PMU_INT_POS_EDGE_EN3_ADDR, HWIO_LPASS_PMU_INT_POS_EDGE_EN3_RMSK)
#define HWIO_LPASS_PMU_INT_POS_EDGE_EN3_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_INT_POS_EDGE_EN3_ADDR, m)
#define HWIO_LPASS_PMU_INT_POS_EDGE_EN3_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_INT_POS_EDGE_EN3_ADDR,v)
#define HWIO_LPASS_PMU_INT_POS_EDGE_EN3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_PMU_INT_POS_EDGE_EN3_ADDR,m,v,HWIO_LPASS_PMU_INT_POS_EDGE_EN3_IN)
#define HWIO_LPASS_PMU_INT_POS_EDGE_EN3_PMU_INT_POS_EDGE_EN2_BMSK          0xffffffff
#define HWIO_LPASS_PMU_INT_POS_EDGE_EN3_PMU_INT_POS_EDGE_EN2_SHFT                 0x0

#define HWIO_LPASS_PMU_INT_POS_EDGE_EN4_ADDR                               (LPASS_PMU_REGS_REG_BASE      + 0x0000006c)
#define HWIO_LPASS_PMU_INT_POS_EDGE_EN4_RMSK                               0xffffffff
#define HWIO_LPASS_PMU_INT_POS_EDGE_EN4_IN          \
        in_dword_masked(HWIO_LPASS_PMU_INT_POS_EDGE_EN4_ADDR, HWIO_LPASS_PMU_INT_POS_EDGE_EN4_RMSK)
#define HWIO_LPASS_PMU_INT_POS_EDGE_EN4_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_INT_POS_EDGE_EN4_ADDR, m)
#define HWIO_LPASS_PMU_INT_POS_EDGE_EN4_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_INT_POS_EDGE_EN4_ADDR,v)
#define HWIO_LPASS_PMU_INT_POS_EDGE_EN4_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_PMU_INT_POS_EDGE_EN4_ADDR,m,v,HWIO_LPASS_PMU_INT_POS_EDGE_EN4_IN)
#define HWIO_LPASS_PMU_INT_POS_EDGE_EN4_PMU_INT_POS_EDGE_EN2_BMSK          0xffffffff
#define HWIO_LPASS_PMU_INT_POS_EDGE_EN4_PMU_INT_POS_EDGE_EN2_SHFT                 0x0

#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN0_ADDR                               (LPASS_PMU_REGS_REG_BASE      + 0x00000070)
#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN0_RMSK                               0xffffffff
#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN0_IN          \
        in_dword_masked(HWIO_LPASS_PMU_INT_NEG_EDGE_EN0_ADDR, HWIO_LPASS_PMU_INT_NEG_EDGE_EN0_RMSK)
#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN0_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_INT_NEG_EDGE_EN0_ADDR, m)
#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN0_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_INT_NEG_EDGE_EN0_ADDR,v)
#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_PMU_INT_NEG_EDGE_EN0_ADDR,m,v,HWIO_LPASS_PMU_INT_NEG_EDGE_EN0_IN)
#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN0_PMU_INT_NEG_EDGE_EN0_BMSK          0xffffffff
#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN0_PMU_INT_NEG_EDGE_EN0_SHFT                 0x0

#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN1_ADDR                               (LPASS_PMU_REGS_REG_BASE      + 0x00000074)
#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN1_RMSK                               0xffffffff
#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN1_IN          \
        in_dword_masked(HWIO_LPASS_PMU_INT_NEG_EDGE_EN1_ADDR, HWIO_LPASS_PMU_INT_NEG_EDGE_EN1_RMSK)
#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN1_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_INT_NEG_EDGE_EN1_ADDR, m)
#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN1_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_INT_NEG_EDGE_EN1_ADDR,v)
#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_PMU_INT_NEG_EDGE_EN1_ADDR,m,v,HWIO_LPASS_PMU_INT_NEG_EDGE_EN1_IN)
#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN1_PMU_INT_NEG_EDGE_EN1_BMSK          0xffffffff
#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN1_PMU_INT_NEG_EDGE_EN1_SHFT                 0x0

#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN2_ADDR                               (LPASS_PMU_REGS_REG_BASE      + 0x00000078)
#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN2_RMSK                               0xffffffff
#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN2_IN          \
        in_dword_masked(HWIO_LPASS_PMU_INT_NEG_EDGE_EN2_ADDR, HWIO_LPASS_PMU_INT_NEG_EDGE_EN2_RMSK)
#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN2_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_INT_NEG_EDGE_EN2_ADDR, m)
#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN2_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_INT_NEG_EDGE_EN2_ADDR,v)
#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_PMU_INT_NEG_EDGE_EN2_ADDR,m,v,HWIO_LPASS_PMU_INT_NEG_EDGE_EN2_IN)
#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN2_PMU_INT_NEG_EDGE_EN2_BMSK          0xffffffff
#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN2_PMU_INT_NEG_EDGE_EN2_SHFT                 0x0

#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN3_ADDR                               (LPASS_PMU_REGS_REG_BASE      + 0x0000007c)
#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN3_RMSK                               0xffffffff
#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN3_IN          \
        in_dword_masked(HWIO_LPASS_PMU_INT_NEG_EDGE_EN3_ADDR, HWIO_LPASS_PMU_INT_NEG_EDGE_EN3_RMSK)
#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN3_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_INT_NEG_EDGE_EN3_ADDR, m)
#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN3_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_INT_NEG_EDGE_EN3_ADDR,v)
#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_PMU_INT_NEG_EDGE_EN3_ADDR,m,v,HWIO_LPASS_PMU_INT_NEG_EDGE_EN3_IN)
#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN3_PMU_INT_NEG_EDGE_EN3_BMSK          0xffffffff
#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN3_PMU_INT_NEG_EDGE_EN3_SHFT                 0x0

#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN4_ADDR                               (LPASS_PMU_REGS_REG_BASE      + 0x00000080)
#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN4_RMSK                               0xffffffff
#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN4_IN          \
        in_dword_masked(HWIO_LPASS_PMU_INT_NEG_EDGE_EN4_ADDR, HWIO_LPASS_PMU_INT_NEG_EDGE_EN4_RMSK)
#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN4_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_INT_NEG_EDGE_EN4_ADDR, m)
#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN4_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_INT_NEG_EDGE_EN4_ADDR,v)
#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN4_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_PMU_INT_NEG_EDGE_EN4_ADDR,m,v,HWIO_LPASS_PMU_INT_NEG_EDGE_EN4_IN)
#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN4_PMU_INT_NEG_EDGE_EN4_BMSK          0xffffffff
#define HWIO_LPASS_PMU_INT_NEG_EDGE_EN4_PMU_INT_NEG_EDGE_EN4_SHFT                 0x0

#define HWIO_LPASS_PMU_INT_EN0_ADDR                                        (LPASS_PMU_REGS_REG_BASE      + 0x00000084)
#define HWIO_LPASS_PMU_INT_EN0_RMSK                                        0xffffffff
#define HWIO_LPASS_PMU_INT_EN0_IN          \
        in_dword_masked(HWIO_LPASS_PMU_INT_EN0_ADDR, HWIO_LPASS_PMU_INT_EN0_RMSK)
#define HWIO_LPASS_PMU_INT_EN0_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_INT_EN0_ADDR, m)
#define HWIO_LPASS_PMU_INT_EN0_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_INT_EN0_ADDR,v)
#define HWIO_LPASS_PMU_INT_EN0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_PMU_INT_EN0_ADDR,m,v,HWIO_LPASS_PMU_INT_EN0_IN)
#define HWIO_LPASS_PMU_INT_EN0_PMU_INT_EN0_BMSK                            0xffffffff
#define HWIO_LPASS_PMU_INT_EN0_PMU_INT_EN0_SHFT                                   0x0

#define HWIO_LPASS_PMU_INT_EN1_ADDR                                        (LPASS_PMU_REGS_REG_BASE      + 0x00000088)
#define HWIO_LPASS_PMU_INT_EN1_RMSK                                        0xffffffff
#define HWIO_LPASS_PMU_INT_EN1_IN          \
        in_dword_masked(HWIO_LPASS_PMU_INT_EN1_ADDR, HWIO_LPASS_PMU_INT_EN1_RMSK)
#define HWIO_LPASS_PMU_INT_EN1_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_INT_EN1_ADDR, m)
#define HWIO_LPASS_PMU_INT_EN1_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_INT_EN1_ADDR,v)
#define HWIO_LPASS_PMU_INT_EN1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_PMU_INT_EN1_ADDR,m,v,HWIO_LPASS_PMU_INT_EN1_IN)
#define HWIO_LPASS_PMU_INT_EN1_PMU_INT_EN1_BMSK                            0xffffffff
#define HWIO_LPASS_PMU_INT_EN1_PMU_INT_EN1_SHFT                                   0x0

#define HWIO_LPASS_PMU_INT_EN2_ADDR                                        (LPASS_PMU_REGS_REG_BASE      + 0x0000008c)
#define HWIO_LPASS_PMU_INT_EN2_RMSK                                        0xffffffff
#define HWIO_LPASS_PMU_INT_EN2_IN          \
        in_dword_masked(HWIO_LPASS_PMU_INT_EN2_ADDR, HWIO_LPASS_PMU_INT_EN2_RMSK)
#define HWIO_LPASS_PMU_INT_EN2_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_INT_EN2_ADDR, m)
#define HWIO_LPASS_PMU_INT_EN2_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_INT_EN2_ADDR,v)
#define HWIO_LPASS_PMU_INT_EN2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_PMU_INT_EN2_ADDR,m,v,HWIO_LPASS_PMU_INT_EN2_IN)
#define HWIO_LPASS_PMU_INT_EN2_PMU_INT_EN2_BMSK                            0xffffffff
#define HWIO_LPASS_PMU_INT_EN2_PMU_INT_EN2_SHFT                                   0x0

#define HWIO_LPASS_PMU_INT_EN3_ADDR                                        (LPASS_PMU_REGS_REG_BASE      + 0x00000090)
#define HWIO_LPASS_PMU_INT_EN3_RMSK                                        0xffffffff
#define HWIO_LPASS_PMU_INT_EN3_IN          \
        in_dword_masked(HWIO_LPASS_PMU_INT_EN3_ADDR, HWIO_LPASS_PMU_INT_EN3_RMSK)
#define HWIO_LPASS_PMU_INT_EN3_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_INT_EN3_ADDR, m)
#define HWIO_LPASS_PMU_INT_EN3_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_INT_EN3_ADDR,v)
#define HWIO_LPASS_PMU_INT_EN3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_PMU_INT_EN3_ADDR,m,v,HWIO_LPASS_PMU_INT_EN3_IN)
#define HWIO_LPASS_PMU_INT_EN3_PMU_INT_EN2_BMSK                            0xffffffff
#define HWIO_LPASS_PMU_INT_EN3_PMU_INT_EN2_SHFT                                   0x0

#define HWIO_LPASS_PMU_INT_EN4_ADDR                                        (LPASS_PMU_REGS_REG_BASE      + 0x00000094)
#define HWIO_LPASS_PMU_INT_EN4_RMSK                                        0xffffffff
#define HWIO_LPASS_PMU_INT_EN4_IN          \
        in_dword_masked(HWIO_LPASS_PMU_INT_EN4_ADDR, HWIO_LPASS_PMU_INT_EN4_RMSK)
#define HWIO_LPASS_PMU_INT_EN4_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_INT_EN4_ADDR, m)
#define HWIO_LPASS_PMU_INT_EN4_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_INT_EN4_ADDR,v)
#define HWIO_LPASS_PMU_INT_EN4_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_PMU_INT_EN4_ADDR,m,v,HWIO_LPASS_PMU_INT_EN4_IN)
#define HWIO_LPASS_PMU_INT_EN4_PMU_INT_EN2_BMSK                            0xffffffff
#define HWIO_LPASS_PMU_INT_EN4_PMU_INT_EN2_SHFT                                   0x0

#define HWIO_LPASS_PMU_INT_STAT0_ADDR                                      (LPASS_PMU_REGS_REG_BASE      + 0x00000098)
#define HWIO_LPASS_PMU_INT_STAT0_RMSK                                      0xffffffff
#define HWIO_LPASS_PMU_INT_STAT0_IN          \
        in_dword_masked(HWIO_LPASS_PMU_INT_STAT0_ADDR, HWIO_LPASS_PMU_INT_STAT0_RMSK)
#define HWIO_LPASS_PMU_INT_STAT0_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_INT_STAT0_ADDR, m)
#define HWIO_LPASS_PMU_INT_STAT0_PMU_INT_STAT0_BMSK                        0xffffffff
#define HWIO_LPASS_PMU_INT_STAT0_PMU_INT_STAT0_SHFT                               0x0

#define HWIO_LPASS_PMU_INT_STAT1_ADDR                                      (LPASS_PMU_REGS_REG_BASE      + 0x0000009c)
#define HWIO_LPASS_PMU_INT_STAT1_RMSK                                      0xffffffff
#define HWIO_LPASS_PMU_INT_STAT1_IN          \
        in_dword_masked(HWIO_LPASS_PMU_INT_STAT1_ADDR, HWIO_LPASS_PMU_INT_STAT1_RMSK)
#define HWIO_LPASS_PMU_INT_STAT1_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_INT_STAT1_ADDR, m)
#define HWIO_LPASS_PMU_INT_STAT1_PMU_INT_STAT1_BMSK                        0xffffffff
#define HWIO_LPASS_PMU_INT_STAT1_PMU_INT_STAT1_SHFT                               0x0

#define HWIO_LPASS_PMU_INT_STAT2_ADDR                                      (LPASS_PMU_REGS_REG_BASE      + 0x00000100)
#define HWIO_LPASS_PMU_INT_STAT2_RMSK                                      0xffffffff
#define HWIO_LPASS_PMU_INT_STAT2_IN          \
        in_dword_masked(HWIO_LPASS_PMU_INT_STAT2_ADDR, HWIO_LPASS_PMU_INT_STAT2_RMSK)
#define HWIO_LPASS_PMU_INT_STAT2_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_INT_STAT2_ADDR, m)
#define HWIO_LPASS_PMU_INT_STAT2_PMU_INT_STAT2_BMSK                        0xffffffff
#define HWIO_LPASS_PMU_INT_STAT2_PMU_INT_STAT2_SHFT                               0x0

#define HWIO_LPASS_PMU_INT_STAT3_ADDR                                      (LPASS_PMU_REGS_REG_BASE      + 0x00000104)
#define HWIO_LPASS_PMU_INT_STAT3_RMSK                                      0xffffffff
#define HWIO_LPASS_PMU_INT_STAT3_IN          \
        in_dword_masked(HWIO_LPASS_PMU_INT_STAT3_ADDR, HWIO_LPASS_PMU_INT_STAT3_RMSK)
#define HWIO_LPASS_PMU_INT_STAT3_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_INT_STAT3_ADDR, m)
#define HWIO_LPASS_PMU_INT_STAT3_PMU_INT_STAT2_BMSK                        0xffffffff
#define HWIO_LPASS_PMU_INT_STAT3_PMU_INT_STAT2_SHFT                               0x0

#define HWIO_LPASS_PMU_INT_STAT4_ADDR                                      (LPASS_PMU_REGS_REG_BASE      + 0x00000108)
#define HWIO_LPASS_PMU_INT_STAT4_RMSK                                      0xffffffff
#define HWIO_LPASS_PMU_INT_STAT4_IN          \
        in_dword_masked(HWIO_LPASS_PMU_INT_STAT4_ADDR, HWIO_LPASS_PMU_INT_STAT4_RMSK)
#define HWIO_LPASS_PMU_INT_STAT4_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_INT_STAT4_ADDR, m)
#define HWIO_LPASS_PMU_INT_STAT4_PMU_INT_STAT2_BMSK                        0xffffffff
#define HWIO_LPASS_PMU_INT_STAT4_PMU_INT_STAT2_SHFT                               0x0

#define HWIO_LPASS_PMU_INT_RAW_STAT0_ADDR                                  (LPASS_PMU_REGS_REG_BASE      + 0x0000010c)
#define HWIO_LPASS_PMU_INT_RAW_STAT0_RMSK                                  0xffffffff
#define HWIO_LPASS_PMU_INT_RAW_STAT0_IN          \
        in_dword_masked(HWIO_LPASS_PMU_INT_RAW_STAT0_ADDR, HWIO_LPASS_PMU_INT_RAW_STAT0_RMSK)
#define HWIO_LPASS_PMU_INT_RAW_STAT0_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_INT_RAW_STAT0_ADDR, m)
#define HWIO_LPASS_PMU_INT_RAW_STAT0_PMU_INT_RAW_STAT0_BMSK                0xffffffff
#define HWIO_LPASS_PMU_INT_RAW_STAT0_PMU_INT_RAW_STAT0_SHFT                       0x0

#define HWIO_LPASS_PMU_INT_RAW_STAT1_ADDR                                  (LPASS_PMU_REGS_REG_BASE      + 0x00000110)
#define HWIO_LPASS_PMU_INT_RAW_STAT1_RMSK                                  0xffffffff
#define HWIO_LPASS_PMU_INT_RAW_STAT1_IN          \
        in_dword_masked(HWIO_LPASS_PMU_INT_RAW_STAT1_ADDR, HWIO_LPASS_PMU_INT_RAW_STAT1_RMSK)
#define HWIO_LPASS_PMU_INT_RAW_STAT1_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_INT_RAW_STAT1_ADDR, m)
#define HWIO_LPASS_PMU_INT_RAW_STAT1_PMU_INT_RAW_STAT1_BMSK                0xffffffff
#define HWIO_LPASS_PMU_INT_RAW_STAT1_PMU_INT_RAW_STAT1_SHFT                       0x0

#define HWIO_LPASS_PMU_INT_RAW_STAT2_ADDR                                  (LPASS_PMU_REGS_REG_BASE      + 0x00000114)
#define HWIO_LPASS_PMU_INT_RAW_STAT2_RMSK                                  0xffffffff
#define HWIO_LPASS_PMU_INT_RAW_STAT2_IN          \
        in_dword_masked(HWIO_LPASS_PMU_INT_RAW_STAT2_ADDR, HWIO_LPASS_PMU_INT_RAW_STAT2_RMSK)
#define HWIO_LPASS_PMU_INT_RAW_STAT2_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_INT_RAW_STAT2_ADDR, m)
#define HWIO_LPASS_PMU_INT_RAW_STAT2_PMU_INT_RAW_STAT2_BMSK                0xffffffff
#define HWIO_LPASS_PMU_INT_RAW_STAT2_PMU_INT_RAW_STAT2_SHFT                       0x0

#define HWIO_LPASS_PMU_INT_RAW_STAT3_ADDR                                  (LPASS_PMU_REGS_REG_BASE      + 0x00000118)
#define HWIO_LPASS_PMU_INT_RAW_STAT3_RMSK                                  0xffffffff
#define HWIO_LPASS_PMU_INT_RAW_STAT3_IN          \
        in_dword_masked(HWIO_LPASS_PMU_INT_RAW_STAT3_ADDR, HWIO_LPASS_PMU_INT_RAW_STAT3_RMSK)
#define HWIO_LPASS_PMU_INT_RAW_STAT3_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_INT_RAW_STAT3_ADDR, m)
#define HWIO_LPASS_PMU_INT_RAW_STAT3_PMU_INT_RAW_STAT2_BMSK                0xffffffff
#define HWIO_LPASS_PMU_INT_RAW_STAT3_PMU_INT_RAW_STAT2_SHFT                       0x0

#define HWIO_LPASS_PMU_INT_RAW_STAT4_ADDR                                  (LPASS_PMU_REGS_REG_BASE      + 0x0000011c)
#define HWIO_LPASS_PMU_INT_RAW_STAT4_RMSK                                  0xffffffff
#define HWIO_LPASS_PMU_INT_RAW_STAT4_IN          \
        in_dword_masked(HWIO_LPASS_PMU_INT_RAW_STAT4_ADDR, HWIO_LPASS_PMU_INT_RAW_STAT4_RMSK)
#define HWIO_LPASS_PMU_INT_RAW_STAT4_INM(m)      \
        in_dword_masked(HWIO_LPASS_PMU_INT_RAW_STAT4_ADDR, m)
#define HWIO_LPASS_PMU_INT_RAW_STAT4_PMU_INT_RAW_STAT2_BMSK                0xffffffff
#define HWIO_LPASS_PMU_INT_RAW_STAT4_PMU_INT_RAW_STAT2_SHFT                       0x0

#define HWIO_LPASS_PMU_INT_TO_TMR_IRQ_CLR_ADDR                             (LPASS_PMU_REGS_REG_BASE      + 0x00000120)
#define HWIO_LPASS_PMU_INT_TO_TMR_IRQ_CLR_RMSK                                    0x1
#define HWIO_LPASS_PMU_INT_TO_TMR_IRQ_CLR_OUT(v)      \
        out_dword(HWIO_LPASS_PMU_INT_TO_TMR_IRQ_CLR_ADDR,v)
#define HWIO_LPASS_PMU_INT_TO_TMR_IRQ_CLR_PMU_TO_TMR_IRQ_CLR_BMSK                 0x1
#define HWIO_LPASS_PMU_INT_TO_TMR_IRQ_CLR_PMU_TO_TMR_IRQ_CLR_SHFT                 0x0

/*----------------------------------------------------------------------------
 * MODULE: LPASS_TCSR
 *--------------------------------------------------------------------------*/

#define LPASS_TCSR_REG_BASE                                                              (LPASS_BASE      + 0x00080000)

#define HWIO_LPASS_AHBE_SPARE_ADDR                                                       (LPASS_TCSR_REG_BASE      + 0x00000040)
#define HWIO_LPASS_AHBE_SPARE_RMSK                                                       0xffffffff
#define HWIO_LPASS_AHBE_SPARE_IN          \
        in_dword_masked(HWIO_LPASS_AHBE_SPARE_ADDR, HWIO_LPASS_AHBE_SPARE_RMSK)
#define HWIO_LPASS_AHBE_SPARE_INM(m)      \
        in_dword_masked(HWIO_LPASS_AHBE_SPARE_ADDR, m)
#define HWIO_LPASS_AHBE_SPARE_OUT(v)      \
        out_dword(HWIO_LPASS_AHBE_SPARE_ADDR,v)
#define HWIO_LPASS_AHBE_SPARE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LPASS_AHBE_SPARE_ADDR,m,v,HWIO_LPASS_AHBE_SPARE_IN)
#define HWIO_LPASS_AHBE_SPARE_AHBE_SPARE_BMSK                                            0xffffffff
#define HWIO_LPASS_AHBE_SPARE_AHBE_SPARE_SHFT                                                   0x0


#endif /* __HALAONINTHWIO_H__ */
