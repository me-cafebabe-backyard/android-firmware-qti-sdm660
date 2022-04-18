#ifndef __SSC_QDSS_CSR_REGS_H__
#define __SSC_QDSS_CSR_REGS_H__
/*
===========================================================================
*/
/**
  @file ssc_qdss_csr_regs.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    SDM660 (Starlord) [starlord_v1.0_p3q3r97_MTO]
 
  This file contains HWIO register definitions for the following modules:
    LPASS_SCSR_REGS

  'Include' filters applied: 
  'Exclude' filters applied: 
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

  $Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/QdssStmTargetLib/HwioQdssSsc_csr.h#3 $
  $DateTime: 2017/04/25 03:06:40 $
  $Author: pwbldsvc $

  ===========================================================================
*/

#include "HALhwio.h"

/*----------------------------------------------------------------------------
 * MODULE: LPASS_SCSR_REGS
 *--------------------------------------------------------------------------*/

#define HWIO_LPASS_SCSR_TEST_BUS_SEL_CFG_ADDR(x)                                       ((x)      + 0x00000000)
#define HWIO_LPASS_SCSR_TEST_BUS_SEL_CFG_RMSK                                              0x1
#define HWIO_LPASS_SCSR_TEST_BUS_SEL_CFG_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_TEST_BUS_SEL_CFG_ADDR(x), HWIO_LPASS_SCSR_TEST_BUS_SEL_CFG_RMSK)
#define HWIO_LPASS_SCSR_TEST_BUS_SEL_CFG_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_TEST_BUS_SEL_CFG_ADDR(x), m)
#define HWIO_LPASS_SCSR_TEST_BUS_SEL_CFG_OUT(x,v)      \
        out_dword(HWIO_LPASS_SCSR_TEST_BUS_SEL_CFG_ADDR(x),v)
#define HWIO_LPASS_SCSR_TEST_BUS_SEL_CFG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_TEST_BUS_SEL_CFG_ADDR(x),m,v,HWIO_LPASS_SCSR_TEST_BUS_SEL_CFG_IN)
#define HWIO_LPASS_SCSR_TEST_BUS_SEL_CFG_SCSR_TEST_BUS_SEL_BMSK                            0x1
#define HWIO_LPASS_SCSR_TEST_BUS_SEL_CFG_SCSR_TEST_BUS_SEL_SHFT                            0x0

#define HWIO_LPASS_SCSR_HW_VERSION_ADDR(x)                                             ((x)      + 0x00000004)
#define HWIO_LPASS_SCSR_HW_VERSION_RMSK                                             0xffffffff
#define HWIO_LPASS_SCSR_HW_VERSION_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_HW_VERSION_ADDR(x), HWIO_LPASS_SCSR_HW_VERSION_RMSK)
#define HWIO_LPASS_SCSR_HW_VERSION_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_HW_VERSION_ADDR(x), m)
#define HWIO_LPASS_SCSR_HW_VERSION_MAJOR_BMSK                                       0xf0000000
#define HWIO_LPASS_SCSR_HW_VERSION_MAJOR_SHFT                                             0x1c
#define HWIO_LPASS_SCSR_HW_VERSION_MINOR_BMSK                                        0xfff0000
#define HWIO_LPASS_SCSR_HW_VERSION_MINOR_SHFT                                             0x10
#define HWIO_LPASS_SCSR_HW_VERSION_STEP_BMSK                                            0xffff
#define HWIO_LPASS_SCSR_HW_VERSION_STEP_SHFT                                               0x0

#define HWIO_LPASS_SCSR_XO_CLK_GATE_ADDR(x)                                            ((x)      + 0x00000008)
#define HWIO_LPASS_SCSR_XO_CLK_GATE_RMSK                                                   0x1
#define HWIO_LPASS_SCSR_XO_CLK_GATE_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_XO_CLK_GATE_ADDR(x), HWIO_LPASS_SCSR_XO_CLK_GATE_RMSK)
#define HWIO_LPASS_SCSR_XO_CLK_GATE_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_XO_CLK_GATE_ADDR(x), m)
#define HWIO_LPASS_SCSR_XO_CLK_GATE_OUT(x,v)      \
        out_dword(HWIO_LPASS_SCSR_XO_CLK_GATE_ADDR(x),v)
#define HWIO_LPASS_SCSR_XO_CLK_GATE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_XO_CLK_GATE_ADDR(x),m,v,HWIO_LPASS_SCSR_XO_CLK_GATE_IN)
#define HWIO_LPASS_SCSR_XO_CLK_GATE_SCSR_XO_CLK_GATE_EN_BMSK                               0x1
#define HWIO_LPASS_SCSR_XO_CLK_GATE_SCSR_XO_CLK_GATE_EN_SHFT                               0x0

#define HWIO_LPASS_SCSR_I2C_CFG_ADDR(x)                                                ((x)      + 0x0000000c)
#define HWIO_LPASS_SCSR_I2C_CFG_RMSK                                                       0xf
#define HWIO_LPASS_SCSR_I2C_CFG_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_I2C_CFG_ADDR(x), HWIO_LPASS_SCSR_I2C_CFG_RMSK)
#define HWIO_LPASS_SCSR_I2C_CFG_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_I2C_CFG_ADDR(x), m)
#define HWIO_LPASS_SCSR_I2C_CFG_OUT(x,v)      \
        out_dword(HWIO_LPASS_SCSR_I2C_CFG_ADDR(x),v)
#define HWIO_LPASS_SCSR_I2C_CFG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_I2C_CFG_ADDR(x),m,v,HWIO_LPASS_SCSR_I2C_CFG_IN)
#define HWIO_LPASS_SCSR_I2C_CFG_MODE_1_BMSK                                                0xc
#define HWIO_LPASS_SCSR_I2C_CFG_MODE_1_SHFT                                                0x2
#define HWIO_LPASS_SCSR_I2C_CFG_MODE_0_BMSK                                                0x3
#define HWIO_LPASS_SCSR_I2C_CFG_MODE_0_SHFT                                                0x0

#define HWIO_LPASS_SCSR_SW_ISLAND_MODE_DISABLE_ADDR(x)                                 ((x)      + 0x00000010)
#define HWIO_LPASS_SCSR_SW_ISLAND_MODE_DISABLE_RMSK                                        0x1
#define HWIO_LPASS_SCSR_SW_ISLAND_MODE_DISABLE_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_SW_ISLAND_MODE_DISABLE_ADDR(x), HWIO_LPASS_SCSR_SW_ISLAND_MODE_DISABLE_RMSK)
#define HWIO_LPASS_SCSR_SW_ISLAND_MODE_DISABLE_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_SW_ISLAND_MODE_DISABLE_ADDR(x), m)
#define HWIO_LPASS_SCSR_SW_ISLAND_MODE_DISABLE_DISABLE_BMSK                                0x1
#define HWIO_LPASS_SCSR_SW_ISLAND_MODE_DISABLE_DISABLE_SHFT                                0x0

#define HWIO_LPASS_SCSR_IEC_CTL_ADDR(x)                                                ((x)      + 0x00001000)
#define HWIO_LPASS_SCSR_IEC_CTL_RMSK                                                      0xff
#define HWIO_LPASS_SCSR_IEC_CTL_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_CTL_ADDR(x), HWIO_LPASS_SCSR_IEC_CTL_RMSK)
#define HWIO_LPASS_SCSR_IEC_CTL_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_CTL_ADDR(x), m)
#define HWIO_LPASS_SCSR_IEC_CTL_OUT(x,v)      \
        out_dword(HWIO_LPASS_SCSR_IEC_CTL_ADDR(x),v)
#define HWIO_LPASS_SCSR_IEC_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_IEC_CTL_ADDR(x),m,v,HWIO_LPASS_SCSR_IEC_CTL_IN)
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

#define HWIO_LPASS_SCSR_IEC_STAT_ADDR(x)                                               ((x)      + 0x00001004)
#define HWIO_LPASS_SCSR_IEC_STAT_RMSK                                                      0x1
#define HWIO_LPASS_SCSR_IEC_STAT_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_STAT_ADDR(x), HWIO_LPASS_SCSR_IEC_STAT_RMSK)
#define HWIO_LPASS_SCSR_IEC_STAT_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_STAT_ADDR(x), m)
#define HWIO_LPASS_SCSR_IEC_STAT_ISLAND_MODE_BMSK                                          0x1
#define HWIO_LPASS_SCSR_IEC_STAT_ISLAND_MODE_SHFT                                          0x0

#define HWIO_LPASS_SCSR_IEC_BSY_WAIT_ADDR(x)                                           ((x)      + 0x00001008)
#define HWIO_LPASS_SCSR_IEC_BSY_WAIT_RMSK                                                  0x3
#define HWIO_LPASS_SCSR_IEC_BSY_WAIT_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_BSY_WAIT_ADDR(x), HWIO_LPASS_SCSR_IEC_BSY_WAIT_RMSK)
#define HWIO_LPASS_SCSR_IEC_BSY_WAIT_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_BSY_WAIT_ADDR(x), m)
#define HWIO_LPASS_SCSR_IEC_BSY_WAIT_OUT(x,v)      \
        out_dword(HWIO_LPASS_SCSR_IEC_BSY_WAIT_ADDR(x),v)
#define HWIO_LPASS_SCSR_IEC_BSY_WAIT_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_IEC_BSY_WAIT_ADDR(x),m,v,HWIO_LPASS_SCSR_IEC_BSY_WAIT_IN)
#define HWIO_LPASS_SCSR_IEC_BSY_WAIT_BUSY_WAIT_EN_BMSK                                     0x2
#define HWIO_LPASS_SCSR_IEC_BSY_WAIT_BUSY_WAIT_EN_SHFT                                     0x1
#define HWIO_LPASS_SCSR_IEC_BSY_WAIT_BUSY_WAIT_RST_BMSK                                    0x1
#define HWIO_LPASS_SCSR_IEC_BSY_WAIT_BUSY_WAIT_RST_SHFT                                    0x0

#define HWIO_LPASS_SCSR_IEC_SQCNTR_VAL0_ADDR(x)                                        ((x)      + 0x0000100c)
#define HWIO_LPASS_SCSR_IEC_SQCNTR_VAL0_RMSK                                        0xffffffff
#define HWIO_LPASS_SCSR_IEC_SQCNTR_VAL0_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_SQCNTR_VAL0_ADDR(x), HWIO_LPASS_SCSR_IEC_SQCNTR_VAL0_RMSK)
#define HWIO_LPASS_SCSR_IEC_SQCNTR_VAL0_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_SQCNTR_VAL0_ADDR(x), m)
#define HWIO_LPASS_SCSR_IEC_SQCNTR_VAL0_SQCNTR_VAL0_BMSK                            0xffffffff
#define HWIO_LPASS_SCSR_IEC_SQCNTR_VAL0_SQCNTR_VAL0_SHFT                                   0x0

#define HWIO_LPASS_SCSR_IEC_SQCNTR_VAL1_ADDR(x)                                        ((x)      + 0x00001010)
#define HWIO_LPASS_SCSR_IEC_SQCNTR_VAL1_RMSK                                          0xffffff
#define HWIO_LPASS_SCSR_IEC_SQCNTR_VAL1_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_SQCNTR_VAL1_ADDR(x), HWIO_LPASS_SCSR_IEC_SQCNTR_VAL1_RMSK)
#define HWIO_LPASS_SCSR_IEC_SQCNTR_VAL1_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_SQCNTR_VAL1_ADDR(x), m)
#define HWIO_LPASS_SCSR_IEC_SQCNTR_VAL1_SQCNTR_VAL1_BMSK                              0xffffff
#define HWIO_LPASS_SCSR_IEC_SQCNTR_VAL1_SQCNTR_VAL1_SHFT                                   0x0

#define HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL0_ADDR(x)                                ((x)      + 0x00001014)
#define HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL0_RMSK                                0xffffffff
#define HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL0_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL0_ADDR(x), HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL0_RMSK)
#define HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL0_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL0_ADDR(x), m)
#define HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL0_BUSY_WAIT_CNTR_VAL0_BMSK            0xffffffff
#define HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL0_BUSY_WAIT_CNTR_VAL0_SHFT                   0x0

#define HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL1_ADDR(x)                                ((x)      + 0x00001018)
#define HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL1_RMSK                                  0xffffff
#define HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL1_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL1_ADDR(x), HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL1_RMSK)
#define HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL1_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL1_ADDR(x), m)
#define HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL1_BUSY_WAIT_CNTR_VAL1_BMSK              0xffffff
#define HWIO_LPASS_SCSR_IEC_BUSY_WAIT_CNTR_VAL1_BUSY_WAIT_CNTR_VAL1_SHFT                   0x0

#define HWIO_LPASS_SCSR_IEC_HADDR_VAL0_ADDR(x)                                         ((x)      + 0x0000101c)
#define HWIO_LPASS_SCSR_IEC_HADDR_VAL0_RMSK                                         0xffffffff
#define HWIO_LPASS_SCSR_IEC_HADDR_VAL0_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_HADDR_VAL0_ADDR(x), HWIO_LPASS_SCSR_IEC_HADDR_VAL0_RMSK)
#define HWIO_LPASS_SCSR_IEC_HADDR_VAL0_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_HADDR_VAL0_ADDR(x), m)
#define HWIO_LPASS_SCSR_IEC_HADDR_VAL0_HADDR_VAL0_BMSK                              0xffffffff
#define HWIO_LPASS_SCSR_IEC_HADDR_VAL0_HADDR_VAL0_SHFT                                     0x0

#define HWIO_LPASS_SCSR_IEC_HADDR_VAL1_ADDR(x)                                         ((x)      + 0x00001020)
#define HWIO_LPASS_SCSR_IEC_HADDR_VAL1_RMSK                                                0xf
#define HWIO_LPASS_SCSR_IEC_HADDR_VAL1_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_HADDR_VAL1_ADDR(x), HWIO_LPASS_SCSR_IEC_HADDR_VAL1_RMSK)
#define HWIO_LPASS_SCSR_IEC_HADDR_VAL1_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_HADDR_VAL1_ADDR(x), m)
#define HWIO_LPASS_SCSR_IEC_HADDR_VAL1_HADDR_VAL1_BMSK                                     0xf
#define HWIO_LPASS_SCSR_IEC_HADDR_VAL1_HADDR_VAL1_SHFT                                     0x0

#define HWIO_LPASS_SCSR_IEC_HMID_VAL_ADDR(x)                                           ((x)      + 0x00001024)
#define HWIO_LPASS_SCSR_IEC_HMID_VAL_RMSK                                                 0xff
#define HWIO_LPASS_SCSR_IEC_HMID_VAL_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_HMID_VAL_ADDR(x), HWIO_LPASS_SCSR_IEC_HMID_VAL_RMSK)
#define HWIO_LPASS_SCSR_IEC_HMID_VAL_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_HMID_VAL_ADDR(x), m)
#define HWIO_LPASS_SCSR_IEC_HMID_VAL_SCSR_IEC_HMID_VAL_BMSK                               0xff
#define HWIO_LPASS_SCSR_IEC_HMID_VAL_SCSR_IEC_HMID_VAL_SHFT                                0x0

#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL0_ADDR(x)                                      ((x)      + 0x00001028)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL0_RMSK                                      0xffffffff
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL0_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL0_ADDR(x), HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL0_RMSK)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL0_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL0_ADDR(x), m)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL0_OUT(x,v)      \
        out_dword(HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL0_ADDR(x),v)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL0_ADDR(x),m,v,HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL0_IN)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL0_SCSR_HWEVENTS_SEL0_BMSK                   0xffffffff
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL0_SCSR_HWEVENTS_SEL0_SHFT                          0x0

#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL1_ADDR(x)                                      ((x)      + 0x0000102c)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL1_RMSK                                      0xffffffff
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL1_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL1_ADDR(x), HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL1_RMSK)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL1_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL1_ADDR(x), m)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL1_OUT(x,v)      \
        out_dword(HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL1_ADDR(x),v)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL1_ADDR(x),m,v,HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL1_IN)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL1_SCSR_HWEVENTS_SEL1_BMSK                   0xffffffff
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL1_SCSR_HWEVENTS_SEL1_SHFT                          0x0

#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL2_ADDR(x)                                      ((x)      + 0x00001030)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL2_RMSK                                      0xffffffff
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL2_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL2_ADDR(x), HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL2_RMSK)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL2_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL2_ADDR(x), m)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL2_OUT(x,v)      \
        out_dword(HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL2_ADDR(x),v)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL2_ADDR(x),m,v,HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL2_IN)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL2_SCSR_HWEVENTS_SEL2_BMSK                   0xffffffff
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL2_SCSR_HWEVENTS_SEL2_SHFT                          0x0

#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL3_ADDR(x)                                      ((x)      + 0x00001034)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL3_RMSK                                      0xffffffff
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL3_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL3_ADDR(x), HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL3_RMSK)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL3_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL3_ADDR(x), m)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL3_OUT(x,v)      \
        out_dword(HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL3_ADDR(x),v)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL3_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL3_ADDR(x),m,v,HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL3_IN)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL3_SCSR_HWEVENTS_SEL3_BMSK                   0xffffffff
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_SEL3_SCSR_HWEVENTS_SEL3_SHFT                          0x0

#define HWIO_LPASS_SCSR_IEC_HWEVENTS_EN_ADDR(x)                                        ((x)      + 0x00001038)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_EN_RMSK                                        0xffffffff
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_EN_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_HWEVENTS_EN_ADDR(x), HWIO_LPASS_SCSR_IEC_HWEVENTS_EN_RMSK)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_EN_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_IEC_HWEVENTS_EN_ADDR(x), m)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_EN_OUT(x,v)      \
        out_dword(HWIO_LPASS_SCSR_IEC_HWEVENTS_EN_ADDR(x),v)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_EN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_IEC_HWEVENTS_EN_ADDR(x),m,v,HWIO_LPASS_SCSR_IEC_HWEVENTS_EN_IN)
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_EN_HWEVENTS_EN_BMSK                            0xffffffff
#define HWIO_LPASS_SCSR_IEC_HWEVENTS_EN_HWEVENTS_EN_SHFT                                   0x0

#define HWIO_LPASS_SCSR_DATA_BUS_CONFIG_ADDR(x)                                        ((x)      + 0x00002000)
#define HWIO_LPASS_SCSR_DATA_BUS_CONFIG_RMSK                                             0xfff
#define HWIO_LPASS_SCSR_DATA_BUS_CONFIG_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_DATA_BUS_CONFIG_ADDR(x), HWIO_LPASS_SCSR_DATA_BUS_CONFIG_RMSK)
#define HWIO_LPASS_SCSR_DATA_BUS_CONFIG_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_DATA_BUS_CONFIG_ADDR(x), m)
#define HWIO_LPASS_SCSR_DATA_BUS_CONFIG_OUT(x,v)      \
        out_dword(HWIO_LPASS_SCSR_DATA_BUS_CONFIG_ADDR(x),v)
#define HWIO_LPASS_SCSR_DATA_BUS_CONFIG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_DATA_BUS_CONFIG_ADDR(x),m,v,HWIO_LPASS_SCSR_DATA_BUS_CONFIG_IN)
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

#define HWIO_LPASS_SCSR_DATA_BUS_STATUS_ADDR(x)                                        ((x)      + 0x00002004)
#define HWIO_LPASS_SCSR_DATA_BUS_STATUS_RMSK                                               0x7
#define HWIO_LPASS_SCSR_DATA_BUS_STATUS_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_DATA_BUS_STATUS_ADDR(x), HWIO_LPASS_SCSR_DATA_BUS_STATUS_RMSK)
#define HWIO_LPASS_SCSR_DATA_BUS_STATUS_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_DATA_BUS_STATUS_ADDR(x), m)
#define HWIO_LPASS_SCSR_DATA_BUS_STATUS_AHBE_STATUS_BMSK                                   0x7
#define HWIO_LPASS_SCSR_DATA_BUS_STATUS_AHBE_STATUS_SHFT                                   0x0

#define HWIO_LPASS_SCSR_CFG_BUS_CONFIG_ADDR(x)                                         ((x)      + 0x00003000)
#define HWIO_LPASS_SCSR_CFG_BUS_CONFIG_RMSK                                              0xfff
#define HWIO_LPASS_SCSR_CFG_BUS_CONFIG_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_CFG_BUS_CONFIG_ADDR(x), HWIO_LPASS_SCSR_CFG_BUS_CONFIG_RMSK)
#define HWIO_LPASS_SCSR_CFG_BUS_CONFIG_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_CFG_BUS_CONFIG_ADDR(x), m)
#define HWIO_LPASS_SCSR_CFG_BUS_CONFIG_OUT(x,v)      \
        out_dword(HWIO_LPASS_SCSR_CFG_BUS_CONFIG_ADDR(x),v)
#define HWIO_LPASS_SCSR_CFG_BUS_CONFIG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_CFG_BUS_CONFIG_ADDR(x),m,v,HWIO_LPASS_SCSR_CFG_BUS_CONFIG_IN)
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

#define HWIO_LPASS_SCSR_CFG_BUS_STATUS_ADDR(x)                                         ((x)      + 0x00003004)
#define HWIO_LPASS_SCSR_CFG_BUS_STATUS_RMSK                                                0x7
#define HWIO_LPASS_SCSR_CFG_BUS_STATUS_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_CFG_BUS_STATUS_ADDR(x), HWIO_LPASS_SCSR_CFG_BUS_STATUS_RMSK)
#define HWIO_LPASS_SCSR_CFG_BUS_STATUS_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_CFG_BUS_STATUS_ADDR(x), m)
#define HWIO_LPASS_SCSR_CFG_BUS_STATUS_AHBE_STATUS_BMSK                                    0x7
#define HWIO_LPASS_SCSR_CFG_BUS_STATUS_AHBE_STATUS_SHFT                                    0x0

#define HWIO_LPASS_SCSR_TSGEN_PRELOAD_LO_ADDR(x)                                       ((x)      + 0x00004000)
#define HWIO_LPASS_SCSR_TSGEN_PRELOAD_LO_RMSK                                       0xffffffff
#define HWIO_LPASS_SCSR_TSGEN_PRELOAD_LO_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_TSGEN_PRELOAD_LO_ADDR(x), HWIO_LPASS_SCSR_TSGEN_PRELOAD_LO_RMSK)
#define HWIO_LPASS_SCSR_TSGEN_PRELOAD_LO_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_TSGEN_PRELOAD_LO_ADDR(x), m)
#define HWIO_LPASS_SCSR_TSGEN_PRELOAD_LO_OUT(x,v)      \
        out_dword(HWIO_LPASS_SCSR_TSGEN_PRELOAD_LO_ADDR(x),v)
#define HWIO_LPASS_SCSR_TSGEN_PRELOAD_LO_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_TSGEN_PRELOAD_LO_ADDR(x),m,v,HWIO_LPASS_SCSR_TSGEN_PRELOAD_LO_IN)
#define HWIO_LPASS_SCSR_TSGEN_PRELOAD_LO_TSGEN_PRELOAD_LO_BMSK                      0xffffffff
#define HWIO_LPASS_SCSR_TSGEN_PRELOAD_LO_TSGEN_PRELOAD_LO_SHFT                             0x0

#define HWIO_LPASS_SCSR_TSGEN_PRELOAD_HI_ADDR(x)                                       ((x)      + 0x00004004)
#define HWIO_LPASS_SCSR_TSGEN_PRELOAD_HI_RMSK                                       0xffffffff
#define HWIO_LPASS_SCSR_TSGEN_PRELOAD_HI_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_TSGEN_PRELOAD_HI_ADDR(x), HWIO_LPASS_SCSR_TSGEN_PRELOAD_HI_RMSK)
#define HWIO_LPASS_SCSR_TSGEN_PRELOAD_HI_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_TSGEN_PRELOAD_HI_ADDR(x), m)
#define HWIO_LPASS_SCSR_TSGEN_PRELOAD_HI_OUT(x,v)      \
        out_dword(HWIO_LPASS_SCSR_TSGEN_PRELOAD_HI_ADDR(x),v)
#define HWIO_LPASS_SCSR_TSGEN_PRELOAD_HI_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_TSGEN_PRELOAD_HI_ADDR(x),m,v,HWIO_LPASS_SCSR_TSGEN_PRELOAD_HI_IN)
#define HWIO_LPASS_SCSR_TSGEN_PRELOAD_HI_TSGEN_PRELOAD_HI_BMSK                      0xffffffff
#define HWIO_LPASS_SCSR_TSGEN_PRELOAD_HI_TSGEN_PRELOAD_HI_SHFT                             0x0

#define HWIO_LPASS_SCSR_TSGEN_CTR_LO_ADDR(x)                                           ((x)      + 0x00004008)
#define HWIO_LPASS_SCSR_TSGEN_CTR_LO_RMSK                                           0xffffffff
#define HWIO_LPASS_SCSR_TSGEN_CTR_LO_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_TSGEN_CTR_LO_ADDR(x), HWIO_LPASS_SCSR_TSGEN_CTR_LO_RMSK)
#define HWIO_LPASS_SCSR_TSGEN_CTR_LO_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_TSGEN_CTR_LO_ADDR(x), m)
#define HWIO_LPASS_SCSR_TSGEN_CTR_LO_TSGEN_CTR_LO_BMSK                              0xffffffff
#define HWIO_LPASS_SCSR_TSGEN_CTR_LO_TSGEN_CTR_LO_SHFT                                     0x0

#define HWIO_LPASS_SCSR_TSGEN_CTR_HI_ADDR(x)                                           ((x)      + 0x0000400c)
#define HWIO_LPASS_SCSR_TSGEN_CTR_HI_RMSK                                           0xffffffff
#define HWIO_LPASS_SCSR_TSGEN_CTR_HI_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_TSGEN_CTR_HI_ADDR(x), HWIO_LPASS_SCSR_TSGEN_CTR_HI_RMSK)
#define HWIO_LPASS_SCSR_TSGEN_CTR_HI_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_TSGEN_CTR_HI_ADDR(x), m)
#define HWIO_LPASS_SCSR_TSGEN_CTR_HI_TSGEN_CTR_HI_BMSK                              0xffffffff
#define HWIO_LPASS_SCSR_TSGEN_CTR_HI_TSGEN_CTR_HI_SHFT                                     0x0

#define HWIO_LPASS_SCSR_TSGEN_CTL_ADDR(x)                                              ((x)      + 0x00004010)
#define HWIO_LPASS_SCSR_TSGEN_CTL_RMSK                                                    0x13
#define HWIO_LPASS_SCSR_TSGEN_CTL_IN(x)          \
        in_dword_masked(HWIO_LPASS_SCSR_TSGEN_CTL_ADDR(x), HWIO_LPASS_SCSR_TSGEN_CTL_RMSK)
#define HWIO_LPASS_SCSR_TSGEN_CTL_INM(x,m)       \
        in_dword_masked(HWIO_LPASS_SCSR_TSGEN_CTL_ADDR(x), m)
#define HWIO_LPASS_SCSR_TSGEN_CTL_OUT(x,v)      \
        out_dword(HWIO_LPASS_SCSR_TSGEN_CTL_ADDR(x),v)
#define HWIO_LPASS_SCSR_TSGEN_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_TSGEN_CTL_ADDR(x),m,v,HWIO_LPASS_SCSR_TSGEN_CTL_IN(x))
#define HWIO_LPASS_SCSR_TSGEN_CTL_TSGEN_LEGACY_MODE_BMSK                                  0x10
#define HWIO_LPASS_SCSR_TSGEN_CTL_TSGEN_LEGACY_MODE_SHFT                                   0x4
#define HWIO_LPASS_SCSR_TSGEN_CTL_TSGEN_PRELOAD_EN_BMSK                                    0x2
#define HWIO_LPASS_SCSR_TSGEN_CTL_TSGEN_PRELOAD_EN_SHFT                                    0x1
#define HWIO_LPASS_SCSR_TSGEN_CTL_TSGEN_DISABLE_CNT_BMSK                                   0x1
#define HWIO_LPASS_SCSR_TSGEN_CTL_TSGEN_DISABLE_CNT_SHFT                                   0x0

#define HWIO_LPASS_SCSR_ATB_LOW_POWER_HANDSHAKE_ADDR(x)                                ((x)      + 0x00004020)
#define HWIO_LPASS_SCSR_ATB_LOW_POWER_HANDSHAKE_RMSK                                       0x7
#define HWIO_LPASS_SCSR_ATB_LOW_POWER_HANDSHAKE_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_ATB_LOW_POWER_HANDSHAKE_ADDR(x), HWIO_LPASS_SCSR_ATB_LOW_POWER_HANDSHAKE_RMSK)
#define HWIO_LPASS_SCSR_ATB_LOW_POWER_HANDSHAKE_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_ATB_LOW_POWER_HANDSHAKE_ADDR(x), m)
#define HWIO_LPASS_SCSR_ATB_LOW_POWER_HANDSHAKE_OUT(x,v)      \
        out_dword(HWIO_LPASS_SCSR_ATB_LOW_POWER_HANDSHAKE_ADDR(x),v)
#define HWIO_LPASS_SCSR_ATB_LOW_POWER_HANDSHAKE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_ATB_LOW_POWER_HANDSHAKE_ADDR(x),m,v,HWIO_LPASS_SCSR_ATB_LOW_POWER_HANDSHAKE_IN(x))
#define HWIO_LPASS_SCSR_ATB_LOW_POWER_HANDSHAKE_REQUEST_BMSK                               0x4
#define HWIO_LPASS_SCSR_ATB_LOW_POWER_HANDSHAKE_REQUEST_SHFT                               0x2
#define HWIO_LPASS_SCSR_ATB_LOW_POWER_HANDSHAKE_ACTIVE_BMSK                                0x2
#define HWIO_LPASS_SCSR_ATB_LOW_POWER_HANDSHAKE_ACTIVE_SHFT                                0x1
#define HWIO_LPASS_SCSR_ATB_LOW_POWER_HANDSHAKE_ACK_BMSK                                   0x1
#define HWIO_LPASS_SCSR_ATB_LOW_POWER_HANDSHAKE_ACK_SHFT                                   0x0

#define HWIO_LPASS_SCSR_APB_LOW_POWER_HANDSHAKE_ADDR(x)                                ((x)      + 0x00004024)
#define HWIO_LPASS_SCSR_APB_LOW_POWER_HANDSHAKE_RMSK                                       0x7
#define HWIO_LPASS_SCSR_APB_LOW_POWER_HANDSHAKE_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_APB_LOW_POWER_HANDSHAKE_ADDR(x), HWIO_LPASS_SCSR_APB_LOW_POWER_HANDSHAKE_RMSK)
#define HWIO_LPASS_SCSR_APB_LOW_POWER_HANDSHAKE_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_APB_LOW_POWER_HANDSHAKE_ADDR(x), m)
#define HWIO_LPASS_SCSR_APB_LOW_POWER_HANDSHAKE_OUT(x,v)      \
        out_dword(HWIO_LPASS_SCSR_APB_LOW_POWER_HANDSHAKE_ADDR(x),v)
#define HWIO_LPASS_SCSR_APB_LOW_POWER_HANDSHAKE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_APB_LOW_POWER_HANDSHAKE_ADDR(x),m,v,HWIO_LPASS_SCSR_APB_LOW_POWER_HANDSHAKE_IN)
#define HWIO_LPASS_SCSR_APB_LOW_POWER_HANDSHAKE_REQUEST_BMSK                               0x4
#define HWIO_LPASS_SCSR_APB_LOW_POWER_HANDSHAKE_REQUEST_SHFT                               0x2
#define HWIO_LPASS_SCSR_APB_LOW_POWER_HANDSHAKE_ACTIVE_BMSK                                0x2
#define HWIO_LPASS_SCSR_APB_LOW_POWER_HANDSHAKE_ACTIVE_SHFT                                0x1
#define HWIO_LPASS_SCSR_APB_LOW_POWER_HANDSHAKE_ACK_BMSK                                   0x1
#define HWIO_LPASS_SCSR_APB_LOW_POWER_HANDSHAKE_ACK_SHFT                                   0x0

#define HWIO_LPASS_SCSR_TS_LOW_POWER_HANDSHAKE_ADDR(x)                                 ((x)      + 0x00004028)
#define HWIO_LPASS_SCSR_TS_LOW_POWER_HANDSHAKE_RMSK                                       0x37
#define HWIO_LPASS_SCSR_TS_LOW_POWER_HANDSHAKE_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_TS_LOW_POWER_HANDSHAKE_ADDR(x), HWIO_LPASS_SCSR_TS_LOW_POWER_HANDSHAKE_RMSK)
#define HWIO_LPASS_SCSR_TS_LOW_POWER_HANDSHAKE_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_TS_LOW_POWER_HANDSHAKE_ADDR(x), m)
#define HWIO_LPASS_SCSR_TS_LOW_POWER_HANDSHAKE_OUT(x,v)      \
        out_dword(HWIO_LPASS_SCSR_TS_LOW_POWER_HANDSHAKE_ADDR(x),v)
#define HWIO_LPASS_SCSR_TS_LOW_POWER_HANDSHAKE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_TS_LOW_POWER_HANDSHAKE_ADDR(x),m,v,HWIO_LPASS_SCSR_TS_LOW_POWER_HANDSHAKE_IN(x))
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

#define HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_ADDR(x)                                         ((x)      + 0x00004100)
#define HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_RMSK                                             0x330f
#define HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_ADDR(x), HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_RMSK)
#define HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_ADDR(x), m)
#define HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_OUT(x,v)      \
        out_dword(HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_ADDR(x),v)
#define HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_ADDR(x),m,v,HWIO_LPASS_SCSR_WCSS_TSTMP_CFG_IN)
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

#define HWIO_LPASS_SCSR_WCSS_QDSS_TSTMP_VAL_LO_ADDR(x)                                 ((x)      + 0x00004104)
#define HWIO_LPASS_SCSR_WCSS_QDSS_TSTMP_VAL_LO_RMSK                                 0xffffffff
#define HWIO_LPASS_SCSR_WCSS_QDSS_TSTMP_VAL_LO_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_WCSS_QDSS_TSTMP_VAL_LO_ADDR(x), HWIO_LPASS_SCSR_WCSS_QDSS_TSTMP_VAL_LO_RMSK)
#define HWIO_LPASS_SCSR_WCSS_QDSS_TSTMP_VAL_LO_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_WCSS_QDSS_TSTMP_VAL_LO_ADDR(x), m)
#define HWIO_LPASS_SCSR_WCSS_QDSS_TSTMP_VAL_LO_TSTMP_VAL_31_0_BMSK                  0xffffffff
#define HWIO_LPASS_SCSR_WCSS_QDSS_TSTMP_VAL_LO_TSTMP_VAL_31_0_SHFT                         0x0

#define HWIO_LPASS_SCSR_WCSS_QDSS_TSTMP_VAL_HI_ADDR(x)                                 ((x)      + 0x00004108)
#define HWIO_LPASS_SCSR_WCSS_QDSS_TSTMP_VAL_HI_RMSK                                 0xffffffff
#define HWIO_LPASS_SCSR_WCSS_QDSS_TSTMP_VAL_HI_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_WCSS_QDSS_TSTMP_VAL_HI_ADDR(x), HWIO_LPASS_SCSR_WCSS_QDSS_TSTMP_VAL_HI_RMSK)
#define HWIO_LPASS_SCSR_WCSS_QDSS_TSTMP_VAL_HI_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_WCSS_QDSS_TSTMP_VAL_HI_ADDR(x), m)
#define HWIO_LPASS_SCSR_WCSS_QDSS_TSTMP_VAL_HI_TSTMP_VAL_63_32_BMSK                 0xffffffff
#define HWIO_LPASS_SCSR_WCSS_QDSS_TSTMP_VAL_HI_TSTMP_VAL_63_32_SHFT                        0x0

#define HWIO_LPASS_SCSR_WCSS_INT_TSTMP_VAL_LO_ADDR(x)                                  ((x)      + 0x0000410c)
#define HWIO_LPASS_SCSR_WCSS_INT_TSTMP_VAL_LO_RMSK                                  0xffffffff
#define HWIO_LPASS_SCSR_WCSS_INT_TSTMP_VAL_LO_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_WCSS_INT_TSTMP_VAL_LO_ADDR(x), HWIO_LPASS_SCSR_WCSS_INT_TSTMP_VAL_LO_RMSK)
#define HWIO_LPASS_SCSR_WCSS_INT_TSTMP_VAL_LO_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_WCSS_INT_TSTMP_VAL_LO_ADDR(x), m)
#define HWIO_LPASS_SCSR_WCSS_INT_TSTMP_VAL_LO_TSTMP_VAL_31_0_BMSK                   0xffffffff
#define HWIO_LPASS_SCSR_WCSS_INT_TSTMP_VAL_LO_TSTMP_VAL_31_0_SHFT                          0x0

#define HWIO_LPASS_SCSR_WCSS_INT_TSTMP_VAL_HI_ADDR(x)                                  ((x)      + 0x00004110)
#define HWIO_LPASS_SCSR_WCSS_INT_TSTMP_VAL_HI_RMSK                                  0xffffffff
#define HWIO_LPASS_SCSR_WCSS_INT_TSTMP_VAL_HI_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_WCSS_INT_TSTMP_VAL_HI_ADDR(x), HWIO_LPASS_SCSR_WCSS_INT_TSTMP_VAL_HI_RMSK)
#define HWIO_LPASS_SCSR_WCSS_INT_TSTMP_VAL_HI_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_WCSS_INT_TSTMP_VAL_HI_ADDR(x), m)
#define HWIO_LPASS_SCSR_WCSS_INT_TSTMP_VAL_HI_TSTMP_VAL_63_32_BMSK                  0xffffffff
#define HWIO_LPASS_SCSR_WCSS_INT_TSTMP_VAL_HI_TSTMP_VAL_63_32_SHFT                         0x0

#define HWIO_LPASS_SCSR_WCSS_CXO_FREQ_ADDR(x)                                          ((x)      + 0x00004114)
#define HWIO_LPASS_SCSR_WCSS_CXO_FREQ_RMSK                                           0x3ffffff
#define HWIO_LPASS_SCSR_WCSS_CXO_FREQ_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_WCSS_CXO_FREQ_ADDR(x), HWIO_LPASS_SCSR_WCSS_CXO_FREQ_RMSK)
#define HWIO_LPASS_SCSR_WCSS_CXO_FREQ_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_WCSS_CXO_FREQ_ADDR(x), m)
#define HWIO_LPASS_SCSR_WCSS_CXO_FREQ_OUT(x,v)      \
        out_dword(HWIO_LPASS_SCSR_WCSS_CXO_FREQ_ADDR(x),v)
#define HWIO_LPASS_SCSR_WCSS_CXO_FREQ_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_WCSS_CXO_FREQ_ADDR(x),m,v,HWIO_LPASS_SCSR_WCSS_CXO_FREQ_IN)
#define HWIO_LPASS_SCSR_WCSS_CXO_FREQ_FREQ_BMSK                                      0x3ffffff
#define HWIO_LPASS_SCSR_WCSS_CXO_FREQ_FREQ_SHFT                                            0x0

#define HWIO_LPASS_SCSR_WCSS_CXO_FREQ_IN_KHZ_ADDR(x)                                   ((x)      + 0x00004118)
#define HWIO_LPASS_SCSR_WCSS_CXO_FREQ_IN_KHZ_RMSK                                       0xffff
#define HWIO_LPASS_SCSR_WCSS_CXO_FREQ_IN_KHZ_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_WCSS_CXO_FREQ_IN_KHZ_ADDR(x), HWIO_LPASS_SCSR_WCSS_CXO_FREQ_IN_KHZ_RMSK)
#define HWIO_LPASS_SCSR_WCSS_CXO_FREQ_IN_KHZ_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_WCSS_CXO_FREQ_IN_KHZ_ADDR(x), m)
#define HWIO_LPASS_SCSR_WCSS_CXO_FREQ_IN_KHZ_OUT(x,v)      \
        out_dword(HWIO_LPASS_SCSR_WCSS_CXO_FREQ_IN_KHZ_ADDR(x),v)
#define HWIO_LPASS_SCSR_WCSS_CXO_FREQ_IN_KHZ_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_WCSS_CXO_FREQ_IN_KHZ_ADDR(x),m,v,HWIO_LPASS_SCSR_WCSS_CXO_FREQ_IN_KHZ_IN)
#define HWIO_LPASS_SCSR_WCSS_CXO_FREQ_IN_KHZ_FREQ_BMSK                                  0xffff
#define HWIO_LPASS_SCSR_WCSS_CXO_FREQ_IN_KHZ_FREQ_SHFT                                     0x0

#define HWIO_LPASS_SCSR_WCSS_CLK_INFO_ADDR(x)                                          ((x)      + 0x0000411c)
#define HWIO_LPASS_SCSR_WCSS_CLK_INFO_RMSK                                             0x331f1
#define HWIO_LPASS_SCSR_WCSS_CLK_INFO_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_WCSS_CLK_INFO_ADDR(x), HWIO_LPASS_SCSR_WCSS_CLK_INFO_RMSK)
#define HWIO_LPASS_SCSR_WCSS_CLK_INFO_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_WCSS_CLK_INFO_ADDR(x), m)
#define HWIO_LPASS_SCSR_WCSS_CLK_INFO_TSTMP_DIV_BMSK                                   0x30000
#define HWIO_LPASS_SCSR_WCSS_CLK_INFO_TSTMP_DIV_SHFT                                      0x10
#define HWIO_LPASS_SCSR_WCSS_CLK_INFO_APB_DIV_BMSK                                      0x3000
#define HWIO_LPASS_SCSR_WCSS_CLK_INFO_APB_DIV_SHFT                                         0xc
#define HWIO_LPASS_SCSR_WCSS_CLK_INFO_ATB_DIV_BMSK                                       0x1f0
#define HWIO_LPASS_SCSR_WCSS_CLK_INFO_ATB_DIV_SHFT                                         0x4
#define HWIO_LPASS_SCSR_WCSS_CLK_INFO_SRC_BMSK                                             0x1
#define HWIO_LPASS_SCSR_WCSS_CLK_INFO_SRC_SHFT                                             0x0

#define HWIO_LPASS_SCSR_WCSS_SPARE_ADDR(x)                                             ((x)      + 0x00004120)
#define HWIO_LPASS_SCSR_WCSS_SPARE_RMSK                                             0xffffffff
#define HWIO_LPASS_SCSR_WCSS_SPARE_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_WCSS_SPARE_ADDR(x), HWIO_LPASS_SCSR_WCSS_SPARE_RMSK)
#define HWIO_LPASS_SCSR_WCSS_SPARE_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_WCSS_SPARE_ADDR(x), m)
#define HWIO_LPASS_SCSR_WCSS_SPARE_OUT(x,v)      \
        out_dword(HWIO_LPASS_SCSR_WCSS_SPARE_ADDR(x),v)
#define HWIO_LPASS_SCSR_WCSS_SPARE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_WCSS_SPARE_ADDR(x),m,v,HWIO_LPASS_SCSR_WCSS_SPARE_IN)
#define HWIO_LPASS_SCSR_WCSS_SPARE_SPARE_BMSK                                       0xffffffff
#define HWIO_LPASS_SCSR_WCSS_SPARE_SPARE_SHFT                                              0x0

#define HWIO_LPASS_SCSR_HM_TESTBUS_SEL_ADDR(x)                                         ((x)      + 0x00005000)
#define HWIO_LPASS_SCSR_HM_TESTBUS_SEL_RMSK                                             0xffff
#define HWIO_LPASS_SCSR_HM_TESTBUS_SEL_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_HM_TESTBUS_SEL_ADDR(x), HWIO_LPASS_SCSR_HM_TESTBUS_SEL_RMSK)
#define HWIO_LPASS_SCSR_HM_TESTBUS_SEL_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_HM_TESTBUS_SEL_ADDR(x), m)
#define HWIO_LPASS_SCSR_HM_TESTBUS_SEL_OUT(x,v)      \
        out_dword(HWIO_LPASS_SCSR_HM_TESTBUS_SEL_ADDR(x),v)
#define HWIO_LPASS_SCSR_HM_TESTBUS_SEL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_HM_TESTBUS_SEL_ADDR(x),m,v,HWIO_LPASS_SCSR_HM_TESTBUS_SEL_IN)
#define HWIO_LPASS_SCSR_HM_TESTBUS_SEL_I_TESTBUS_SEL_BMSK                               0xffff
#define HWIO_LPASS_SCSR_HM_TESTBUS_SEL_I_TESTBUS_SEL_SHFT                                  0x0

#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_ADDR(x)                          ((x)      + 0x00006000)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_RMSK                          0xffffffff
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_ADDR(x), HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_RMSK)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_ADDR(x), m)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_OUT(x,v)      \
        out_dword(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_ADDR(x),v)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_ADDR(x),m,v,HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_IN(x))
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_RFU_BMSK                      0xfffffffc
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_RFU_SHFT                             0x2
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_TIMESTAMPENABLE_BMSK                 0x2
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_TIMESTAMPENABLE_SHFT                 0x1
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_CAPTURE_BMSK                         0x1
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_TIMESTAMPCTRL_CAPTURE_SHFT                         0x0

#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_AOTIMEVAL0_ADDR(x)                             ((x)      + 0x00006004)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_AOTIMEVAL0_RMSK                             0xffffffff
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_AOTIMEVAL0_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_AOTIMEVAL0_ADDR(x), HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_AOTIMEVAL0_RMSK)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_AOTIMEVAL0_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_AOTIMEVAL0_ADDR(x), m)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_AOTIMEVAL0_TIMEVAL_BMSK                     0xffffffff
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_AOTIMEVAL0_TIMEVAL_SHFT                            0x0

#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_AOTIMEVAL1_ADDR(x)                             ((x)      + 0x00006008)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_AOTIMEVAL1_RMSK                             0xffffffff
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_AOTIMEVAL1_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_AOTIMEVAL1_ADDR(x), HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_AOTIMEVAL1_RMSK)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_AOTIMEVAL1_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_AOTIMEVAL1_ADDR(x), m)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_AOTIMEVAL1_TIMEVAL_BMSK                     0xffffffff
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_AOTIMEVAL1_TIMEVAL_SHFT                            0x0

#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_ADDR(x)                           ((x)      + 0x0000600c)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_RMSK                           0xffffffff
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_ADDR(x), HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_RMSK)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_ADDR(x), m)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_TIMEVAL_BMSK                   0xffffffff
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMEVAL0_TIMEVAL_SHFT                          0x0

#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_ADDR(x)                           ((x)      + 0x00006010)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_RMSK                           0xffffffff
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_ADDR(x), HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_RMSK)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_ADDR(x), m)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_TIMEVAL_BMSK                   0xffffffff
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMEVAL1_TIMEVAL_SHFT                          0x0

#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_ADDR(x)                          ((x)      + 0x00006014)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_RMSK                          0xffffffff
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_ADDR(x), HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_RMSK)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_ADDR(x), m)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_OUT(x,v)      \
        out_dword(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_ADDR(x),v)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_ADDR(x),m,v,HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_IN)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_TIMELOAD_BMSK                 0xffffffff
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD0_TIMELOAD_SHFT                        0x0

#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_ADDR(x)                          ((x)      + 0x00006018)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_RMSK                          0xffffffff
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_ADDR(x), HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_RMSK)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_ADDR(x), m)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_OUT(x,v)      \
        out_dword(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_ADDR(x),v)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_ADDR(x),m,v,HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_IN)
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_TIMELOAD_BMSK                 0xffffffff
#define HWIO_LPASS_SCSR_QDSS_CS_QDSSCSR_QDSSTIMELOAD1_TIMELOAD_SHFT                        0x0

#define HWIO_LPASS_SCSR_WAKEUP_PRIMARY_IE_ADDR(x)                                      ((x)      + 0x00007000)
#define HWIO_LPASS_SCSR_WAKEUP_PRIMARY_IE_RMSK                                           0x1ff
#define HWIO_LPASS_SCSR_WAKEUP_PRIMARY_IE_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_WAKEUP_PRIMARY_IE_ADDR(x), HWIO_LPASS_SCSR_WAKEUP_PRIMARY_IE_RMSK)
#define HWIO_LPASS_SCSR_WAKEUP_PRIMARY_IE_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_WAKEUP_PRIMARY_IE_ADDR(x), m)
#define HWIO_LPASS_SCSR_WAKEUP_PRIMARY_IE_OUT(x,v)      \
        out_dword(HWIO_LPASS_SCSR_WAKEUP_PRIMARY_IE_ADDR(x),v)
#define HWIO_LPASS_SCSR_WAKEUP_PRIMARY_IE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_WAKEUP_PRIMARY_IE_ADDR(x),m,v,HWIO_LPASS_SCSR_WAKEUP_PRIMARY_IE_IN)
#define HWIO_LPASS_SCSR_WAKEUP_PRIMARY_IE_WAKEUP_IE_BMSK                                 0x1ff
#define HWIO_LPASS_SCSR_WAKEUP_PRIMARY_IE_WAKEUP_IE_SHFT                                   0x0

#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_ADDR(x)                                ((x)      + 0x00008000)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_RMSK                                0xfffffffc
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_ADDR(x), HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_RMSK)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_ADDR(x), m)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_OUT(x,v)      \
        out_dword(HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_ADDR(x),v)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_ADDR(x),m,v,HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_0_IN)
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

#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_ADDR(x)                                ((x)      + 0x00008004)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_RMSK                                0x80fffbff
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_ADDR(x), HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_RMSK)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_ADDR(x), m)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_OUT(x,v)      \
        out_dword(HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_ADDR(x),v)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_ADDR(x),m,v,HWIO_LPASS_SCSR_VSENSE_SENSOR0_CONFIG_1_IN)
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

#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_SUMMARY_ADDR(x)                                 ((x)      + 0x00008008)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_SUMMARY_RMSK                                    0x3ffff
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_SUMMARY_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_VSENSE_SENSOR0_SUMMARY_ADDR(x), HWIO_LPASS_SCSR_VSENSE_SENSOR0_SUMMARY_RMSK)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR0_SUMMARY_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_VSENSE_SENSOR0_SUMMARY_ADDR(x), m)
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

#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_ADDR(x)                                ((x)      + 0x0000800c)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_RMSK                                0xfffffffc
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_ADDR(x), HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_RMSK)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_ADDR(x), m)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_OUT(x,v)      \
        out_dword(HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_ADDR(x),v)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_ADDR(x),m,v,HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_0_IN)
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

#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_ADDR(x)                                ((x)      + 0x00008010)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_RMSK                                0x80fffbff
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_ADDR(x), HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_RMSK)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_ADDR(x), m)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_OUT(x,v)      \
        out_dword(HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_ADDR(x),v)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_ADDR(x),m,v,HWIO_LPASS_SCSR_VSENSE_SENSOR1_CONFIG_1_IN)
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

#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_SUMMARY_ADDR(x)                                 ((x)      + 0x00008014)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_SUMMARY_RMSK                                    0x3ffff
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_SUMMARY_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_VSENSE_SENSOR1_SUMMARY_ADDR(x), HWIO_LPASS_SCSR_VSENSE_SENSOR1_SUMMARY_RMSK)
#define HWIO_LPASS_SCSR_VSENSE_SENSOR1_SUMMARY_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_VSENSE_SENSOR1_SUMMARY_ADDR(x), m)
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

#define HWIO_LPASS_SCSR_WAKEUP_SECONDARY_IE_ADDR(x)                                    ((x)      + 0x00009000)
#define HWIO_LPASS_SCSR_WAKEUP_SECONDARY_IE_RMSK                                         0x1ff
#define HWIO_LPASS_SCSR_WAKEUP_SECONDARY_IE_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_WAKEUP_SECONDARY_IE_ADDR(x), HWIO_LPASS_SCSR_WAKEUP_SECONDARY_IE_RMSK)
#define HWIO_LPASS_SCSR_WAKEUP_SECONDARY_IE_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_WAKEUP_SECONDARY_IE_ADDR(x), m)
#define HWIO_LPASS_SCSR_WAKEUP_SECONDARY_IE_OUT(x,v)      \
        out_dword(HWIO_LPASS_SCSR_WAKEUP_SECONDARY_IE_ADDR(x),v)
#define HWIO_LPASS_SCSR_WAKEUP_SECONDARY_IE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_WAKEUP_SECONDARY_IE_ADDR(x),m,v,HWIO_LPASS_SCSR_WAKEUP_SECONDARY_IE_IN)
#define HWIO_LPASS_SCSR_WAKEUP_SECONDARY_IE_WAKEUP_IE_BMSK                               0x1ff
#define HWIO_LPASS_SCSR_WAKEUP_SECONDARY_IE_WAKEUP_IE_SHFT                                 0x0

#define HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_SEL_ADDR(x)                                     ((x)      + 0x0000a000)
#define HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_SEL_RMSK                                            0x1
#define HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_SEL_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_SEL_ADDR(x), HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_SEL_RMSK)
#define HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_SEL_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_SEL_ADDR(x), m)
#define HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_SEL_OUT(x,v)      \
        out_dword(HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_SEL_ADDR(x),v)
#define HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_SEL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_SEL_ADDR(x),m,v,HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_SEL_IN)
#define HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_SEL_SEL_BMSK                                        0x1
#define HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_SEL_SEL_SHFT                                        0x0

#define HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_ADDR_ADDR(x)                                    ((x)      + 0x0000a004)
#define HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_ADDR_RMSK                                     0xfffffff
#define HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_ADDR_IN(x)         \
        in_dword_masked(HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_ADDR_ADDR(x), HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_ADDR_RMSK)
#define HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_ADDR_INM(x,m)      \
        in_dword_masked(HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_ADDR_ADDR(x), m)
#define HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_ADDR_OUT(x,v)      \
        out_dword(HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_ADDR_ADDR(x),v)
#define HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_ADDR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_ADDR_ADDR(x),m,v,HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_ADDR_IN)
#define HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_ADDR_ADDR_BMSK                                0xffffff0
#define HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_ADDR_ADDR_SHFT                                      0x4
#define HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_ADDR_RSVD_BIT3_0_BMSK                               0xf
#define HWIO_LPASS_SCSR_EFUSE_Q6SS_EVB_ADDR_RSVD_BIT3_0_SHFT                               0x0


#endif /* __SSC_QDSS_CSR_REGS_H__ */
