#ifndef __ABTIMEOUT_HWIO_H__
#define __ABTIMEOUT_HWIO_H__
/*
===========================================================================
*/
/**
  @file ABTimeout_HWIO.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    SDM660 (Starlord) [starlord_v1.0_p3q2r79]
 
  This file contains HWIO register definitions for the following modules:
    LPASS_AHBE_TIME
    LPASS_AHBI_TIME
    LPASS_AHBL_TIME
    LPASS_AHBS_LPASS_SENSOR_AHBI_BUS_TIMEOUT
    TCSR_TCSR_REGS

  'Include' filters applied: BASE[LPASS_AHBE_TIME] TIMEOUT[TCSR_TCSR_REGS] BASE[LPASS_AHBI_TIME] BASE[LPASS_AHBL_TIME] BASE[LPASS_AHBS_LPASS_SENSOR_AHBI_BUS_TIMEOUT] 
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

  $Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/icb/src/660/adsp_slpi/ABTimeout_HWIO.h#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $

  ===========================================================================
*/

#include "msmhwiobase.h"

/*----------------------------------------------------------------------------
 * MODULE: LPASS_AHBE_TIME
 *--------------------------------------------------------------------------*/

#define LPASS_AHBE_TIME_REG_BASE                                 (LPASS_BASE      + 0x000b7000)

/*----------------------------------------------------------------------------
 * MODULE: LPASS_AHBI_TIME
 *--------------------------------------------------------------------------*/

#define LPASS_AHBI_TIME_REG_BASE                                 (LPASS_BASE      + 0x000f6000)

/*----------------------------------------------------------------------------
 * MODULE: LPASS_AHBL_TIME
 *--------------------------------------------------------------------------*/

#define LPASS_AHBL_TIME_REG_BASE                                 (LPASS_BASE      + 0x002c3000)

/*----------------------------------------------------------------------------
 * MODULE: LPASS_AHBS_LPASS_SENSOR_AHBI_BUS_TIMEOUT
 *--------------------------------------------------------------------------*/

#define LPASS_AHBS_LPASS_SENSOR_AHBI_BUS_TIMEOUT_REG_BASE        (LPASS_BASE      + 0x00448000)

/*----------------------------------------------------------------------------
 * MODULE: TCSR_TCSR_REGS
 *--------------------------------------------------------------------------*/

#define TCSR_TCSR_REGS_REG_BASE                                                                               (CORE_TOP_CSR_BASE      + 0x000c0000)

#define HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_ADDR                                                                   (TCSR_TCSR_REGS_REG_BASE      + 0x00000800)
#define HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_RMSK                                                                               0x1
#define HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_IN          \
        in_dword_masked(HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_ADDR, HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_RMSK)
#define HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_INM(m)      \
        in_dword_masked(HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_ADDR, m)
#define HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_OUT(v)      \
        out_dword(HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_ADDR,v)
#define HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_ADDR,m,v,HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_IN)
#define HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_TIMEOUT_SLAVE_GLB_EN_BMSK                                                          0x1
#define HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_TIMEOUT_SLAVE_GLB_EN_SHFT                                                          0x0

#define HWIO_TCSR_TIMEOUT_INTERNAL_EN_ADDR                                                                         (TCSR_TCSR_REGS_REG_BASE      + 0x00000804)
#define HWIO_TCSR_TIMEOUT_INTERNAL_EN_RMSK                                                                                0x1
#define HWIO_TCSR_TIMEOUT_INTERNAL_EN_IN          \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTERNAL_EN_ADDR, HWIO_TCSR_TIMEOUT_INTERNAL_EN_RMSK)
#define HWIO_TCSR_TIMEOUT_INTERNAL_EN_INM(m)      \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTERNAL_EN_ADDR, m)
#define HWIO_TCSR_TIMEOUT_INTERNAL_EN_OUT(v)      \
        out_dword(HWIO_TCSR_TIMEOUT_INTERNAL_EN_ADDR,v)
#define HWIO_TCSR_TIMEOUT_INTERNAL_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_TIMEOUT_INTERNAL_EN_ADDR,m,v,HWIO_TCSR_TIMEOUT_INTERNAL_EN_IN)
#define HWIO_TCSR_TIMEOUT_INTERNAL_EN_TIMEOUT_INTERNAL_EN_BMSK                                                            0x1
#define HWIO_TCSR_TIMEOUT_INTERNAL_EN_TIMEOUT_INTERNAL_EN_SHFT                                                            0x0

#define HWIO_TCSR_TIMEOUT_INTR_STATUS_ADDR                                                                    (TCSR_TCSR_REGS_REG_BASE      + 0x00008020)
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_RMSK                                                                    0xffffffff
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_IN          \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_STATUS_ADDR, HWIO_TCSR_TIMEOUT_INTR_STATUS_RMSK)
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_INM(m)      \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_STATUS_ADDR, m)
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_SNOC_2_IRQ_BMSK                                                  0x80000000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_SNOC_2_IRQ_SHFT                                                        0x1f
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_USB3_IRQ_BMSK                                                    0x40000000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_USB3_IRQ_SHFT                                                          0x1e
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_USB2_IRQ_BMSK                                                    0x20000000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_USB2_IRQ_SHFT                                                          0x1d
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_TURING_IRQ_OUT_AHBS_TIMEOUT_1_BMSK                                           0x10000000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_TURING_IRQ_OUT_AHBS_TIMEOUT_1_SHFT                                                 0x1c
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_SOUTH_S0_IRQ_BMSK                                            0x8000000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_SOUTH_S0_IRQ_SHFT                                                 0x1b
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_SNOC_LPASS_1_IRQ_BMSK                                             0x4000000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_SNOC_LPASS_1_IRQ_SHFT                                                  0x1a
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_QHS_MMSS3_BUS_TIMEOUT_IRQ_BMSK                                           0x2000000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_QHS_MMSS3_BUS_TIMEOUT_IRQ_SHFT                                                0x19
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_WCSS_ECAHB_TSLV_INTR_BMSK                                                0x1000000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_WCSS_ECAHB_TSLV_INTR_SHFT                                                     0x18
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_SNOC_CDSP_3_IRQ_BMSK                                               0x800000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_SNOC_CDSP_3_IRQ_SHFT                                                   0x17
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_LPASS_IRQ_OUT_AHBI_TIMEOUT1_BMSK                                               0x400000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_LPASS_IRQ_OUT_AHBI_TIMEOUT1_SHFT                                                   0x16
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_LPASS_IRQ_OUT_AHBE_TIMEOUT0_BMSK                                               0x200000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_LPASS_IRQ_OUT_AHBE_TIMEOUT0_SHFT                                                   0x15
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_WCSS_TCSR_WAHB_TSLV_INTR_BMSK                                             0x100000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_WCSS_TCSR_WAHB_TSLV_INTR_SHFT                                                 0x14
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_QHS_MMSS2_BUS_TIMEOUT_IRQ_BMSK                                             0x80000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_QHS_MMSS2_BUS_TIMEOUT_IRQ_SHFT                                                0x13
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_QHS_MMSS1_BUS_TIMEOUT_IRQ_BMSK                                             0x40000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_QHS_MMSS1_BUS_TIMEOUT_IRQ_SHFT                                                0x12
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_QHS_MMSS_BUS_TIMEOUT_IRQ_BMSK                                              0x20000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_QHS_MMSS_BUS_TIMEOUT_IRQ_SHFT                                                 0x11
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CENTER_LEFT_S1_IRQ_BMSK                                        0x10000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CENTER_LEFT_S1_IRQ_SHFT                                           0x10
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_MM_CFG_IRQ_BMSK                                            0x8000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_MM_CFG_IRQ_SHFT                                               0xf
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_NORTH_S1_IRQ_BMSK                                               0x4000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_NORTH_S1_IRQ_SHFT                                                  0xe
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_NORTH_S0_IRQ_BMSK                                               0x2000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_NORTH_S0_IRQ_SHFT                                                  0xd
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_NORTH_S2_IRQ_BMSK                                               0x1000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_NORTH_S2_IRQ_SHFT                                                  0xc
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_WCSS_TCSR_WAPB_TSLV_IRQ_BMSK                                                 0x800
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_WCSS_TCSR_WAPB_TSLV_IRQ_SHFT                                                   0xb
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_MSS_CONFIG_TIMEOUT_SLAVE_IRQ_BMSK                                            0x400
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_MSS_CONFIG_TIMEOUT_SLAVE_IRQ_SHFT                                              0xa
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_SNOC_IPA_4_IRQ_BMSK                                                   0x200
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_SNOC_IPA_4_IRQ_SHFT                                                     0x9
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CENTER_LEFT_S0_IRQ_BMSK                                          0x100
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CENTER_LEFT_S0_IRQ_SHFT                                            0x8
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_TURING_IRQ_OUT_AHB_TIMEOUT_0_BMSK                                                  0x80
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_TURING_IRQ_OUT_AHB_TIMEOUT_0_SHFT                                                   0x7
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_WCSS_TCSR_NOC_INTR_BMSK                                                       0x40
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_WCSS_TCSR_NOC_INTR_SHFT                                                        0x6
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CTR_S5_IRQ_BMSK                                              0x20
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CTR_S5_IRQ_SHFT                                               0x5
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CTR_S4_IRQ_BMSK                                              0x10
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CTR_S4_IRQ_SHFT                                               0x4
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CTR_S3_IRQ_BMSK                                               0x8
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CTR_S3_IRQ_SHFT                                               0x3
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CTR_S2_IRQ_BMSK                                               0x4
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CTR_S2_IRQ_SHFT                                               0x2
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CTR_S1_IRQ_BMSK                                               0x2
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CTR_S1_IRQ_SHFT                                               0x1
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CTR_S0_IRQ_BMSK                                               0x1
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CTR_S0_IRQ_SHFT                                               0x0

#define HWIO_TCSR_TIMEOUT_INTR_STATUS1_ADDR                                                                        (TCSR_TCSR_REGS_REG_BASE      + 0x00008024)
#define HWIO_TCSR_TIMEOUT_INTR_STATUS1_RMSK                                                                               0x3
#define HWIO_TCSR_TIMEOUT_INTR_STATUS1_IN          \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_STATUS1_ADDR, HWIO_TCSR_TIMEOUT_INTR_STATUS1_RMSK)
#define HWIO_TCSR_TIMEOUT_INTR_STATUS1_INM(m)      \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_STATUS1_ADDR, m)
#define HWIO_TCSR_TIMEOUT_INTR_STATUS1_BUS_TIMEOUT_4_LPASS_IRQ_BMSK                                                       0x2
#define HWIO_TCSR_TIMEOUT_INTR_STATUS1_BUS_TIMEOUT_4_LPASS_IRQ_SHFT                                                       0x1
#define HWIO_TCSR_TIMEOUT_INTR_STATUS1_LPASS_IRQ_OUT_AHBL_TIMEOUT_BMSK                                                    0x1
#define HWIO_TCSR_TIMEOUT_INTR_STATUS1_LPASS_IRQ_OUT_AHBL_TIMEOUT_SHFT                                                    0x0

#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_ADDR                                                                     (TCSR_TCSR_REGS_REG_BASE      + 0x00008030)
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_RMSK                                                                     0xffffffff
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_ADDR, HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_RMSK)
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_ADDR, m)
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_ADDR,v)
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_ADDR,m,v,HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_IN)
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_SNOC_2_IRQ_ENABLE_BMSK                                       0x80000000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_SNOC_2_IRQ_ENABLE_SHFT                                             0x1f
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_USB3_IRQ_ENABLE_BMSK                                         0x40000000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_USB3_IRQ_ENABLE_SHFT                                               0x1e
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_USB2_IRQ_ENABLE_BMSK                                         0x20000000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_USB2_IRQ_ENABLE_SHFT                                               0x1d
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_TURING_IRQ_OUT_AHBS_TIMEOUT_1_ENABLE_BMSK                                0x10000000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_TURING_IRQ_OUT_AHBS_TIMEOUT_1_ENABLE_SHFT                                      0x1c
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S0_IRQ_ENABLE_BMSK                                 0x8000000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S0_IRQ_ENABLE_SHFT                                      0x1b
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_SNOC_LPASS_1_IRQ_ENABLE_BMSK                                  0x4000000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_SNOC_LPASS_1_IRQ_ENABLE_SHFT                                       0x1a
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_QHS_MMSS3_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                     0x2000000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_QHS_MMSS3_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                          0x19
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_WCSS_ECAHB_TSLV_INTR_ENABLE_BMSK                                          0x1000000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_WCSS_ECAHB_TSLV_INTR_ENABLE_SHFT                                               0x18
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_SNOC_CDSP_3_IRQ_ENABLE_BMSK                                    0x800000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_SNOC_CDSP_3_IRQ_ENABLE_SHFT                                        0x17
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_LPASS_IRQ_OUT_AHB_TIMEOUT1_ENABLE_BMSK                                     0x400000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_LPASS_IRQ_OUT_AHB_TIMEOUT1_ENABLE_SHFT                                         0x16
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_LPASS_IRQ_OUT_AHB_TIMEOUT0_ENABLE_BMSK                                     0x200000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_LPASS_IRQ_OUT_AHB_TIMEOUT0_ENABLE_SHFT                                         0x15
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_WCSS_TCSR_WAHB_TSLV_INTR_ENABLE_BMSK                                       0x100000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_WCSS_TCSR_WAHB_TSLV_INTR_ENABLE_SHFT                                           0x14
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_QHS_MMSS2_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                       0x80000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_QHS_MMSS2_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                          0x13
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_QHS_MMSS1_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                       0x40000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_QHS_MMSS1_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                          0x12
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_QHS_MMSS_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                        0x20000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_QHS_MMSS_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                           0x11
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_CENTER_LEFT_S1_IRQ_ENABLE_BMSK                             0x10000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_CENTER_LEFT_S1_IRQ_ENABLE_SHFT                                0x10
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_MM_CFG_IRQ_ENABLE_BMSK                                      0x8000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_MM_CFG_IRQ_ENABLE_SHFT                                         0xf
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUST_TIMEOUT_CNOC_NORTH_S1_IRQ_ENABLE_BMSK                                   0x4000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUST_TIMEOUT_CNOC_NORTH_S1_IRQ_ENABLE_SHFT                                      0xe
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUST_TIMEOUT_CNOC_NORTH_S0_IRQ_ENABLE_BMSK                                   0x2000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUST_TIMEOUT_CNOC_NORTH_S0_IRQ_ENABLE_SHFT                                      0xd
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUST_TIMEOUT_CNOC_NORTH_S2_IRQ_ENABLE_BMSK                                   0x1000
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUST_TIMEOUT_CNOC_NORTH_S2_IRQ_ENABLE_SHFT                                      0xc
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_WCSS_TCSR_WAPB_TSLV_IRQ_ENABLE_BMSK                                           0x800
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_WCSS_TCSR_WAPB_TSLV_IRQ_ENABLE_SHFT                                             0xb
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_MSS_CONFIG_TIMEOUT_SLAVE_IRQ_ENABLE_BMSK                                      0x400
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_MSS_CONFIG_TIMEOUT_SLAVE_IRQ_ENABLE_SHFT                                        0xa
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_SNOC_IPA_4_IRQ_ENABLE_BMSK                                        0x200
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_SNOC_IPA_4_IRQ_ENABLE_SHFT                                          0x9
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_CENTER_LEFT_S0_IRQ_ENABLE_BMSK                               0x100
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_CENTER_LEFT_S0_IRQ_ENABLE_SHFT                                 0x8
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_TURING_IRQ_OUT_AHB_TIMEOUT_0_ENABLE_BMSK                                       0x80
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_TURING_IRQ_OUT_AHB_TIMEOUT_0_ENABLE_SHFT                                        0x7
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_WCSS_TCSR_NOC_INTR_ENABLE_BMSK                                                 0x40
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_WCSS_TCSR_NOC_INTR_ENABLE_SHFT                                                  0x6
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_CTR_S5_IRQ_ENABLE_BMSK                                        0x20
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_CTR_S5_IRQ_ENABLE_SHFT                                         0x5
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_CTR_S4_IRQ_ENABLE_BMSK                                        0x10
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_CTR_S4_IRQ_ENABLE_SHFT                                         0x4
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_CTR_S3_IRQ_ENABLE_BMSK                                         0x8
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_CTR_S3_IRQ_ENABLE_SHFT                                         0x3
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_CTR_S2_IRQ_ENABLE_BMSK                                         0x4
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_CTR_S2_IRQ_ENABLE_SHFT                                         0x2
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_CTR_S1_IRQ_ENABLE_BMSK                                         0x2
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_CTR_S1_IRQ_ENABLE_SHFT                                         0x1
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_CTR_S0_IRQ_ENABLE_BMSK                                         0x1
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE_BUS_TIMEOUT_CNOC_CTR_S0_IRQ_ENABLE_SHFT                                         0x0

#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE1_ADDR                                                                    (TCSR_TCSR_REGS_REG_BASE      + 0x00008034)
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE1_RMSK                                                                           0x3
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE1_IN          \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE1_ADDR, HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE1_RMSK)
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE1_INM(m)      \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE1_ADDR, m)
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE1_OUT(v)      \
        out_dword(HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE1_ADDR,v)
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE1_ADDR,m,v,HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE1_IN)
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE1_BUS_TIMEOUT_4_LPASS_IRQ_ENABLE_BMSK                                            0x2
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE1_BUS_TIMEOUT_4_LPASS_IRQ_ENABLE_SHFT                                            0x1
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE1_LPASS_IRQ_OUT_AHBL_TIMEOUT_ENABLE_BMSK                                         0x1
#define HWIO_TCSR_TIMEOUT_INTR_RPM_ENABLE1_LPASS_IRQ_OUT_AHBL_TIMEOUT_ENABLE_SHFT                                         0x0

#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_ADDR                                                                    (TCSR_TCSR_REGS_REG_BASE      + 0x00008040)
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_RMSK                                                                    0xffffffff
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_ADDR, HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_RMSK)
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_ADDR, m)
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_ADDR,v)
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_ADDR,m,v,HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_IN)
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_SNOC_2_IRQ_ENABLE_BMSK                                      0x80000000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_SNOC_2_IRQ_ENABLE_SHFT                                            0x1f
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_USB3_IRQ_ENABLE_BMSK                                        0x40000000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_USB3_IRQ_ENABLE_SHFT                                              0x1e
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_USB2_IRQ_ENABLE_BMSK                                        0x20000000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_USB2_IRQ_ENABLE_SHFT                                              0x1d
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_TURING_IRQ_OUT_AHB_TIMEOUT_1_ENABLE_BMSK                                0x10000000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_TURING_IRQ_OUT_AHB_TIMEOUT_1_ENABLE_SHFT                                      0x1c
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S0_IRQ_ENABLE_BMSK                                0x8000000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S0_IRQ_ENABLE_SHFT                                     0x1b
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_SNOC_LPASS_1_IRQ_ENABLE_BMSK                                 0x4000000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_SNOC_LPASS_1_IRQ_ENABLE_SHFT                                      0x1a
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_QHS_MMSS3_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                    0x2000000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_QHS_MMSS3_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                         0x19
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_WCSS_ECAHB_TSLV_INTR_ENABLE_BMSK                                         0x1000000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_WCSS_ECAHB_TSLV_INTR_ENABLE_SHFT                                              0x18
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_SNOC_CDSP_3_IRQ_ENABLE_BMSK                                   0x800000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_SNOC_CDSP_3_IRQ_ENABLE_SHFT                                       0x17
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_LPASS_IRQ_OUT_AHB_TIMEOUT1_ENABLE_BMSK                                    0x400000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_LPASS_IRQ_OUT_AHB_TIMEOUT1_ENABLE_SHFT                                        0x16
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_LPASS_IRQ_OUT_AHB_TIMEOUT0_ENABLE_BMSK                                    0x200000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_LPASS_IRQ_OUT_AHB_TIMEOUT0_ENABLE_SHFT                                        0x15
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_WCSS_TCSR_WAHB_TSLV_INTR_ENABLE_BMSK                                      0x100000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_WCSS_TCSR_WAHB_TSLV_INTR_ENABLE_SHFT                                          0x14
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_QHS_MMSS2_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                      0x80000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_QHS_MMSS2_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                         0x13
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_QHS_MMSS1_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                      0x40000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_QHS_MMSS1_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                         0x12
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_QHS_MMSS_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                       0x20000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_QHS_MMSS_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                          0x11
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_CENTER_LEFT_S1_IRQ_ENABLE_BMSK                            0x10000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_CENTER_LEFT_S1_IRQ_ENABLE_SHFT                               0x10
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_MM_CFG_IRQ_ENABLE_BMSK                                     0x8000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_MM_CFG_IRQ_ENABLE_SHFT                                        0xf
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUST_TIMEOUT_CNOC_NORTH_S1_IRQ_ENABLE_BMSK                                  0x4000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUST_TIMEOUT_CNOC_NORTH_S1_IRQ_ENABLE_SHFT                                     0xe
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUST_TIMEOUT_CNOC_NORTH_S0_IRQ_ENABLE_BMSK                                  0x2000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUST_TIMEOUT_CNOC_NORTH_S0_IRQ_ENABLE_SHFT                                     0xd
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUST_TIMEOUT_CNOC_NORTH_S2_IRQ_ENABLE_BMSK                                  0x1000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUST_TIMEOUT_CNOC_NORTH_S2_IRQ_ENABLE_SHFT                                     0xc
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_WCSS_TCSR_WAPB_TSLV_IRQ_ENABLE_BMSK                                          0x800
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_WCSS_TCSR_WAPB_TSLV_IRQ_ENABLE_SHFT                                            0xb
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_MSS_CONFIG_TIMEOUT_SLAVE_IRQ_ENABLE_BMSK                                     0x400
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_MSS_CONFIG_TIMEOUT_SLAVE_IRQ_ENABLE_SHFT                                       0xa
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_SNOC_IPA_4_IRQ_ENABLE_BMSK                                       0x200
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_SNOC_IPA_4_IRQ_ENABLE_SHFT                                         0x9
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_CENTER_LEFT_S0_IRQ_ENABLE_BMSK                              0x100
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_CENTER_LEFT_S0_IRQ_ENABLE_SHFT                                0x8
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_TURING_IRQ_OUT_AHB_TIMEOUT_0_ENABLE_BMSK                                      0x80
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_TURING_IRQ_OUT_AHB_TIMEOUT_0_ENABLE_SHFT                                       0x7
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_WCSS_TCSR_NOC_INTR_ENABLE_BMSK                                                0x40
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_WCSS_TCSR_NOC_INTR_ENABLE_SHFT                                                 0x6
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_CTR_S5_IRQ_ENABLE_BMSK                                       0x20
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_CTR_S5_IRQ_ENABLE_SHFT                                        0x5
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_CTR_S4_IRQ_ENABLE_BMSK                                       0x10
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_CTR_S4_IRQ_ENABLE_SHFT                                        0x4
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_CTR_S3_IRQ_ENABLE_BMSK                                        0x8
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_CTR_S3_IRQ_ENABLE_SHFT                                        0x3
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_CTR_S2_IRQ_ENABLE_BMSK                                        0x4
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_CTR_S2_IRQ_ENABLE_SHFT                                        0x2
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_CTR_S1_IRQ_ENABLE_BMSK                                        0x2
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_CTR_S1_IRQ_ENABLE_SHFT                                        0x1
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_CTR_S0_IRQ_ENABLE_BMSK                                        0x1
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUS_TIMEOUT_CNOC_CTR_S0_IRQ_ENABLE_SHFT                                        0x0

#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE1_ADDR                                                                   (TCSR_TCSR_REGS_REG_BASE      + 0x00008044)
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE1_RMSK                                                                          0x3
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE1_IN          \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE1_ADDR, HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE1_RMSK)
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE1_INM(m)      \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE1_ADDR, m)
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE1_OUT(v)      \
        out_dword(HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE1_ADDR,v)
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE1_ADDR,m,v,HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE1_IN)
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE1_BUS_TIMEOUT_4_LPASS_IRQ_ENABLE_BMSK                                           0x2
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE1_BUS_TIMEOUT_4_LPASS_IRQ_ENABLE_SHFT                                           0x1
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE1_LPASS_IRQ_OUT_AHBL_TIMEOUT_ENABLE_BMSK                                        0x1
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE1_LPASS_IRQ_OUT_AHBL_TIMEOUT_ENABLE_SHFT                                        0x0

#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_ADDR                                                              (TCSR_TCSR_REGS_REG_BASE      + 0x00008050)
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_RMSK                                                              0xffffffff
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_ADDR, HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_RMSK)
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_ADDR, m)
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_ADDR,v)
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_ADDR,m,v,HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_IN)
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_SNOC_2_IRQ_ENABLE_BMSK                                     0x80000000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_SNOC_2_IRQ_ENABLE_SHFT                                           0x1f
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_USB3_IRQ_ENABLE_BMSK                                       0x40000000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_USB3_IRQ_ENABLE_SHFT                                             0x1e
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_USB2_IRQ_ENABLE_BMSK                                       0x20000000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_USB2_IRQ_ENABLE_SHFT                                             0x1d
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_TURING_IRQ_OUT_AHB_TIMEOUT_1_ENABLE_BMSK                               0x10000000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_TURING_IRQ_OUT_AHB_TIMEOUT_1_ENABLE_SHFT                                     0x1c
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S0_IRQ_ENABLE_BMSK                               0x8000000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S0_IRQ_ENABLE_SHFT                                    0x1b
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_SNOC_LPASS_1_IRQ_ENABLE_BMSK                                0x4000000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_SNOC_LPASS_1_IRQ_ENABLE_SHFT                                     0x1a
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_QHS_MMSS3_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                   0x2000000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_QHS_MMSS3_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                        0x19
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_WCSS_ECAHB_TSLV_INTR_ENABLE_BMSK                                        0x1000000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_WCSS_ECAHB_TSLV_INTR_ENABLE_SHFT                                             0x18
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_SNOC_CDSP_3_IRQ_ENABLE_BMSK                                  0x800000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_SNOC_CDSP_3_IRQ_ENABLE_SHFT                                      0x17
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_LPASS_IRQ_OUT_AHB_TIMEOUT1_ENABLE_BMSK                                   0x400000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_LPASS_IRQ_OUT_AHB_TIMEOUT1_ENABLE_SHFT                                       0x16
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_LPASS_IRQ_OUT_AHB_TIMEOUT0_ENABLE_BMSK                                   0x200000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_LPASS_IRQ_OUT_AHB_TIMEOUT0_ENABLE_SHFT                                       0x15
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_WCSS_TCSR_WAHB_TSLV_INTR_ENABLE_BMSK                                     0x100000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_WCSS_TCSR_WAHB_TSLV_INTR_ENABLE_SHFT                                         0x14
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_QHS_MMSS2_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                     0x80000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_QHS_MMSS2_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                        0x13
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_QHS_MMSS1_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                     0x40000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_QHS_MMSS1_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                        0x12
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_QHS_MMSS_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                      0x20000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_QHS_MMSS_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                         0x11
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_CENTER_LEFT_S1_IRQ_ENABLE_BMSK                           0x10000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_CENTER_LEFT_S1_IRQ_ENABLE_SHFT                              0x10
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_MM_CFG_IRQ_ENABLE_BMSK                                    0x8000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_MM_CFG_IRQ_ENABLE_SHFT                                       0xf
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUST_TIMEOUT_CNOC_NORTH_S1_IRQ_ENABLE_BMSK                                 0x4000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUST_TIMEOUT_CNOC_NORTH_S1_IRQ_ENABLE_SHFT                                    0xe
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUST_TIMEOUT_CNOC_NORTH_S0_IRQ_ENABLE_BMSK                                 0x2000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUST_TIMEOUT_CNOC_NORTH_S0_IRQ_ENABLE_SHFT                                    0xd
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUST_TIMEOUT_CNOC_NORTH_S2_IRQ_ENABLE_BMSK                                 0x1000
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUST_TIMEOUT_CNOC_NORTH_S2_IRQ_ENABLE_SHFT                                    0xc
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_WCSS_TCSR_WAPB_TSLV_IRQ_ENABLE_BMSK                                         0x800
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_WCSS_TCSR_WAPB_TSLV_IRQ_ENABLE_SHFT                                           0xb
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_MSS_CONFIG_TIMEOUT_SLAVE_IRQ_ENABLE_BMSK                                    0x400
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_MSS_CONFIG_TIMEOUT_SLAVE_IRQ_ENABLE_SHFT                                      0xa
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_SNOC_IPA_4_IRQ_ENABLE_BMSK                                      0x200
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_SNOC_IPA_4_IRQ_ENABLE_SHFT                                        0x9
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_CENTER_LEFT_S0_IRQ_ENABLE_BMSK                             0x100
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_CENTER_LEFT_S0_IRQ_ENABLE_SHFT                               0x8
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_TURING_IRQ_OUT_AHB_TIMEOUT_0_ENABLE_BMSK                                     0x80
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_TURING_IRQ_OUT_AHB_TIMEOUT_0_ENABLE_SHFT                                      0x7
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_WCSS_TCSR_NOC_INTR_ENABLE_BMSK                                               0x40
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_WCSS_TCSR_NOC_INTR_ENABLE_SHFT                                                0x6
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_CTR_S5_IRQ_ENABLE_BMSK                                      0x20
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_CTR_S5_IRQ_ENABLE_SHFT                                       0x5
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_CTR_S4_IRQ_ENABLE_BMSK                                      0x10
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_CTR_S4_IRQ_ENABLE_SHFT                                       0x4
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_CTR_S3_IRQ_ENABLE_BMSK                                       0x8
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_CTR_S3_IRQ_ENABLE_SHFT                                       0x3
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_CTR_S2_IRQ_ENABLE_BMSK                                       0x4
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_CTR_S2_IRQ_ENABLE_SHFT                                       0x2
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_CTR_S1_IRQ_ENABLE_BMSK                                       0x2
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_CTR_S1_IRQ_ENABLE_SHFT                                       0x1
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_CTR_S0_IRQ_ENABLE_BMSK                                       0x1
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_BUS_TIMEOUT_CNOC_CTR_S0_IRQ_ENABLE_SHFT                                       0x0

#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE1_ADDR                                                                  (TCSR_TCSR_REGS_REG_BASE      + 0x00008054)
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE1_RMSK                                                                         0x3
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE1_IN          \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE1_ADDR, HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE1_RMSK)
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE1_INM(m)      \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE1_ADDR, m)
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE1_OUT(v)      \
        out_dword(HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE1_ADDR,v)
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE1_ADDR,m,v,HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE1_IN)
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE1_BUS_TIMEOUT_4_LPASS_IRQ_ENABLE_BMSK                                          0x2
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE1_BUS_TIMEOUT_4_LPASS_IRQ_ENABLE_SHFT                                          0x1
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE1_LPASS_IRQ_OUT_AHBL_TIMEOUT_ENABLE_BMSK                                       0x1
#define HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE1_LPASS_IRQ_OUT_AHBL_TIMEOUT_ENABLE_SHFT                                       0x0

#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_ADDR                                                                     (TCSR_TCSR_REGS_REG_BASE      + 0x00008060)
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_RMSK                                                                     0xffffffff
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_ADDR, HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_RMSK)
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_ADDR, m)
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_ADDR,v)
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_ADDR,m,v,HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_IN)
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_SNOC_2_IRQ_ENABLE_BMSK                                       0x80000000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_SNOC_2_IRQ_ENABLE_SHFT                                             0x1f
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_USB3_IRQ_ENABLE_BMSK                                         0x40000000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_USB3_IRQ_ENABLE_SHFT                                               0x1e
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_USB2_IRQ_ENABLE_BMSK                                         0x20000000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_USB2_IRQ_ENABLE_SHFT                                               0x1d
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_TURING_IRQ_OUT_AHB_TIMEOUT_1_ENABLE_BMSK                                 0x10000000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_TURING_IRQ_OUT_AHB_TIMEOUT_1_ENABLE_SHFT                                       0x1c
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S0_IRQ_ENABLE_BMSK                                 0x8000000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S0_IRQ_ENABLE_SHFT                                      0x1b
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_SNOC_LPASS_1_IRQ_ENABLE_BMSK                                  0x4000000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_SNOC_LPASS_1_IRQ_ENABLE_SHFT                                       0x1a
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_QHS_MMSS3_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                     0x2000000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_QHS_MMSS3_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                          0x19
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_WCSS_ECAHB_TSLV_INTR_ENABLE_BMSK                                          0x1000000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_WCSS_ECAHB_TSLV_INTR_ENABLE_SHFT                                               0x18
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_SNOC_CDSP_3_IRQ_ENABLE_BMSK                                    0x800000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_SNOC_CDSP_3_IRQ_ENABLE_SHFT                                        0x17
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_LPASS_IRQ_OUT_AHB_TIMEOUT1_ENABLE_BMSK                                     0x400000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_LPASS_IRQ_OUT_AHB_TIMEOUT1_ENABLE_SHFT                                         0x16
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_LPASS_IRQ_OUT_AHB_TIMEOUT0_ENABLE_BMSK                                     0x200000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_LPASS_IRQ_OUT_AHB_TIMEOUT0_ENABLE_SHFT                                         0x15
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_WCSS_TCSR_WAHB_TSLV_INTR_ENABLE_BMSK                                       0x100000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_WCSS_TCSR_WAHB_TSLV_INTR_ENABLE_SHFT                                           0x14
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_QHS_MMSS2_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                       0x80000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_QHS_MMSS2_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                          0x13
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_QHS_MMSS1_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                       0x40000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_QHS_MMSS1_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                          0x12
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_QHS_MMSS_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                        0x20000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_QHS_MMSS_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                           0x11
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_CENTER_LEFT_S1_IRQ_ENABLE_BMSK                             0x10000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_CENTER_LEFT_S1_IRQ_ENABLE_SHFT                                0x10
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_MM_CFG_IRQ_ENABLE_BMSK                                      0x8000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_MM_CFG_IRQ_ENABLE_SHFT                                         0xf
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUST_TIMEOUT_CNOC_NORTH_S1_IRQ_ENABLE_BMSK                                   0x4000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUST_TIMEOUT_CNOC_NORTH_S1_IRQ_ENABLE_SHFT                                      0xe
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUST_TIMEOUT_CNOC_NORTH_S0_IRQ_ENABLE_BMSK                                   0x2000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUST_TIMEOUT_CNOC_NORTH_S0_IRQ_ENABLE_SHFT                                      0xd
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUST_TIMEOUT_CNOC_NORTH_S2_IRQ_ENABLE_BMSK                                   0x1000
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUST_TIMEOUT_CNOC_NORTH_S2_IRQ_ENABLE_SHFT                                      0xc
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_WCSS_TCSR_WAPB_TSLV_IRQ_ENABLE_BMSK                                           0x800
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_WCSS_TCSR_WAPB_TSLV_IRQ_ENABLE_SHFT                                             0xb
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_MSS_CONFIG_TIMEOUT_SLAVE_IRQ_ENABLE_BMSK                                      0x400
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_MSS_CONFIG_TIMEOUT_SLAVE_IRQ_ENABLE_SHFT                                        0xa
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_SNOC_IPA_4_IRQ_ENABLE_BMSK                                        0x200
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_SNOC_IPA_4_IRQ_ENABLE_SHFT                                          0x9
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_CENTER_LEFT_S0_IRQ_ENABLE_BMSK                               0x100
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_CENTER_LEFT_S0_IRQ_ENABLE_SHFT                                 0x8
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_TURING_IRQ_OUT_AHB_TIMEOUT_0_ENABLE_BMSK                                       0x80
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_TURING_IRQ_OUT_AHB_TIMEOUT_0_ENABLE_SHFT                                        0x7
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_WCSS_TCSR_NOC_INTR_ENABLE_BMSK                                                 0x40
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_WCSS_TCSR_NOC_INTR_ENABLE_SHFT                                                  0x6
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_CTR_S5_IRQ_ENABLE_BMSK                                        0x20
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_CTR_S5_IRQ_ENABLE_SHFT                                         0x5
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_CTR_S4_IRQ_ENABLE_BMSK                                        0x10
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_CTR_S4_IRQ_ENABLE_SHFT                                         0x4
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_CTR_S3_IRQ_ENABLE_BMSK                                         0x8
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_CTR_S3_IRQ_ENABLE_SHFT                                         0x3
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_CTR_S2_IRQ_ENABLE_BMSK                                         0x4
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_CTR_S2_IRQ_ENABLE_SHFT                                         0x2
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_CTR_S1_IRQ_ENABLE_BMSK                                         0x2
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_CTR_S1_IRQ_ENABLE_SHFT                                         0x1
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_CTR_S0_IRQ_ENABLE_BMSK                                         0x1
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE_BUS_TIMEOUT_CNOC_CTR_S0_IRQ_ENABLE_SHFT                                         0x0

#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE1_ADDR                                                                    (TCSR_TCSR_REGS_REG_BASE      + 0x00008064)
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE1_RMSK                                                                           0x3
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE1_IN          \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE1_ADDR, HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE1_RMSK)
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE1_INM(m)      \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE1_ADDR, m)
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE1_OUT(v)      \
        out_dword(HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE1_ADDR,v)
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE1_ADDR,m,v,HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE1_IN)
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE1_BUS_TIMEOUT_4_LPASS_IRQ_ENABLE_BMSK                                            0x2
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE1_BUS_TIMEOUT_4_LPASS_IRQ_ENABLE_SHFT                                            0x1
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE1_LPASS_IRQ_OUT_AHBL_TIMEOUT_ENABLE_BMSK                                         0x1
#define HWIO_TCSR_TIMEOUT_INTR_MSS_ENABLE1_LPASS_IRQ_OUT_AHBL_TIMEOUT_ENABLE_SHFT                                         0x0

#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_ADDR                                                                  (TCSR_TCSR_REGS_REG_BASE      + 0x00008070)
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_RMSK                                                                  0xffffffff
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_ADDR, HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_RMSK)
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_ADDR, m)
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_ADDR,v)
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_ADDR,m,v,HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_IN)
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_SNOC_2_IRQ_ENABLE_BMSK                                    0x80000000
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_SNOC_2_IRQ_ENABLE_SHFT                                          0x1f
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_USB3_IRQ_ENABLE_BMSK                                      0x40000000
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_USB3_IRQ_ENABLE_SHFT                                            0x1e
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_USB2_IRQ_ENABLE_BMSK                                      0x20000000
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_USB2_IRQ_ENABLE_SHFT                                            0x1d
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_TURING_IRQ_OUT_AHB_TIMEOUT_1_ENABLE_BMSK                              0x10000000
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_TURING_IRQ_OUT_AHB_TIMEOUT_1_ENABLE_SHFT                                    0x1c
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S0_IRQ_ENABLE_BMSK                              0x8000000
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_CNOC_SOUTH_S0_IRQ_ENABLE_SHFT                                   0x1b
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_SNOC_LPASS_1_IRQ_ENABLE_BMSK                               0x4000000
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_SNOC_LPASS_1_IRQ_ENABLE_SHFT                                    0x1a
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_QHS_MMSS3_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                  0x2000000
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_QHS_MMSS3_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                       0x19
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_WCSS_ECAHB_TSLV_INTR_ENABLE_BMSK                                       0x1000000
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_WCSS_ECAHB_TSLV_INTR_ENABLE_SHFT                                            0x18
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_SNOC_CDSP_3_IRQ_ENABLE_BMSK                                 0x800000
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_SNOC_CDSP_3_IRQ_ENABLE_SHFT                                     0x17
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_LPASS_IRQ_OUT_AHB_TIMEOUT1_ENABLE_BMSK                                  0x400000
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_LPASS_IRQ_OUT_AHB_TIMEOUT1_ENABLE_SHFT                                      0x16
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_LPASS_IRQ_OUT_AHB_TIMEOUT0_ENABLE_BMSK                                  0x200000
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_LPASS_IRQ_OUT_AHB_TIMEOUT0_ENABLE_SHFT                                      0x15
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_WCSS_TCSR_WAHB_TSLV_INTR_ENABLE_BMSK                                    0x100000
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_WCSS_TCSR_WAHB_TSLV_INTR_ENABLE_SHFT                                        0x14
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_QHS_MMSS2_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                    0x80000
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_QHS_MMSS2_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                       0x13
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_QHS_MMSS1_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                    0x40000
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_QHS_MMSS1_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                       0x12
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_QHS_MMSS_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                     0x20000
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_QHS_MMSS_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                        0x11
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_CNOC_CENTER_LEFT_S1_IRQ_ENABLE_BMSK                          0x10000
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_CNOC_CENTER_LEFT_S1_IRQ_ENABLE_SHFT                             0x10
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_CNOC_MM_CFG_IRQ_ENABLE_BMSK                                   0x8000
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_CNOC_MM_CFG_IRQ_ENABLE_SHFT                                      0xf
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUST_TIMEOUT_CNOC_NORTH_S1_IRQ_ENABLE_BMSK                                0x4000
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUST_TIMEOUT_CNOC_NORTH_S1_IRQ_ENABLE_SHFT                                   0xe
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUST_TIMEOUT_CNOC_NORTH_S0_IRQ_ENABLE_BMSK                                0x2000
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUST_TIMEOUT_CNOC_NORTH_S0_IRQ_ENABLE_SHFT                                   0xd
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUST_TIMEOUT_CNOC_NORTH_S2_IRQ_ENABLE_BMSK                                0x1000
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUST_TIMEOUT_CNOC_NORTH_S2_IRQ_ENABLE_SHFT                                   0xc
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_WCSS_TCSR_WAPB_TSLV_IRQ_ENABLE_BMSK                                        0x800
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_WCSS_TCSR_WAPB_TSLV_IRQ_ENABLE_SHFT                                          0xb
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_MSS_CONFIG_TIMEOUT_SLAVE_IRQ_ENABLE_BMSK                                   0x400
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_MSS_CONFIG_TIMEOUT_SLAVE_IRQ_ENABLE_SHFT                                     0xa
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_SNOC_IPA_4_IRQ_ENABLE_BMSK                                     0x200
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_SNOC_IPA_4_IRQ_ENABLE_SHFT                                       0x9
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_CNOC_CENTER_LEFT_S0_IRQ_ENABLE_BMSK                            0x100
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_CNOC_CENTER_LEFT_S0_IRQ_ENABLE_SHFT                              0x8
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_TURING_IRQ_OUT_AHB_TIMEOUT_0_ENABLE_BMSK                                    0x80
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_TURING_IRQ_OUT_AHB_TIMEOUT_0_ENABLE_SHFT                                     0x7
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_WCSS_TCSR_NOC_INTR_ENABLE_BMSK                                              0x40
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_WCSS_TCSR_NOC_INTR_ENABLE_SHFT                                               0x6
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_CNOC_CTR_S5_IRQ_ENABLE_BMSK                                     0x20
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_CNOC_CTR_S5_IRQ_ENABLE_SHFT                                      0x5
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_CNOC_CTR_S4_IRQ_ENABLE_BMSK                                     0x10
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_CNOC_CTR_S4_IRQ_ENABLE_SHFT                                      0x4
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_CNOC_CTR_S3_IRQ_ENABLE_BMSK                                      0x8
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_CNOC_CTR_S3_IRQ_ENABLE_SHFT                                      0x3
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_CNOC_CTR_S2_IRQ_ENABLE_BMSK                                      0x4
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_CNOC_CTR_S2_IRQ_ENABLE_SHFT                                      0x2
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_CNOC_CTR_S1_IRQ_ENABLE_BMSK                                      0x2
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_CNOC_CTR_S1_IRQ_ENABLE_SHFT                                      0x1
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_CNOC_CTR_S0_IRQ_ENABLE_BMSK                                      0x1
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE_BUS_TIMEOUT_CNOC_CTR_S0_IRQ_ENABLE_SHFT                                      0x0

#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE1_ADDR                                                                 (TCSR_TCSR_REGS_REG_BASE      + 0x00008074)
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE1_RMSK                                                                        0x3
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE1_IN          \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE1_ADDR, HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE1_RMSK)
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE1_INM(m)      \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE1_ADDR, m)
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE1_OUT(v)      \
        out_dword(HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE1_ADDR,v)
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE1_ADDR,m,v,HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE1_IN)
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE1_BUS_TIMEOUT_4_LPASS_IRQ_ENABLE_BMSK                                         0x2
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE1_BUS_TIMEOUT_4_LPASS_IRQ_ENABLE_SHFT                                         0x1
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE1_LPASS_IRQ_OUT_AHBL_TIMEOUT_ENABLE_BMSK                                      0x1
#define HWIO_TCSR_TIMEOUT_INTR_TURING_ENABLE1_LPASS_IRQ_OUT_AHBL_TIMEOUT_ENABLE_SHFT                                      0x0


#endif /* __ABTIMEOUT_HWIO_H__ */
