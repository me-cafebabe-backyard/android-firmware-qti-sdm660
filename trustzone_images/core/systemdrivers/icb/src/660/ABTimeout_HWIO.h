#ifndef __ABTIMEOUT_HWIO_H__
#define __ABTIMEOUT_HWIO_H__
/*
===========================================================================
*/
/**
  @file ABTimeout_HWIO.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    SDM660 (Starlord) [starlord_v1.0_p3q1r63]
 
  This file contains HWIO register definitions for the following modules:
    CNOC_0_CENTER_LEFT_BUS_TIMEOUT
    CNOC_0_CENTER_RIGHT_BUS_TIMEOUT
    CNOC_0_NORTH_BUS_TIMEOUT
    CNOC_0_SOUTH_BUS_TIMEOUT
    CNOC_1_CENTER_LEFT_BUS_TIMEOUT
    CNOC_1_CENTER_RIGHT_BUS_TIMEOUT
    CNOC_1_NORTH_BUS_TIMEOUT
    CNOC_2_CENTER_RIGHT_BUS_TIMEOUT
    CNOC_2_NORTH_BUS_TIMEOUT
    CNOC_3_CENTER_RIGHT_BUS_TIMEOUT
    CNOC_4_CENTER_RIGHT_BUS_TIMEOUT
    CNOC_5_CENTER_RIGHT_BUS_TIMEOUT
    CNOC_MM_BUS_TIMEOUT
    CNOC_USB2_BUS_TIMEOUT
    CNOC_USB3_BUS_TIMEOUT
    QHS_MMSS0_U_AHB_BUS_TIMEOUT0
    QHS_MMSS1_U_AHB_BUS_TIMEOUT1
    QHS_MMSS2_U_AHB_BUS_TIMEOUT2
    QHS_MMSS3_U_AHB_BUS_TIMEOUT3
    SNOC_1_BUS_TIMEOUT
    SNOC_2_BUS_TIMEOUT
    SNOC_3_BUS_TIMEOUT
    SNOC_4_BUS_TIMEOUT
    TCSR_TCSR_REGS

  'Include' filters applied: BASE[QHS_MMSS3_U_AHB_BUS_TIMEOUT3] BASE[CNOC_USB3_BUS_TIMEOUT] BASE[QHS_MMSS1_U_AHB_BUS_TIMEOUT1] BASE[CNOC_2_CENTER_RIGHT_BUS_TIMEOUT] BASE[CNOC_3_CENTER_RIGHT_BUS_TIMEOUT] BASE[QHS_MMSS2_U_AHB_BUS_TIMEOUT2] BASE[CNOC_5_CENTER_RIGHT_BUS_TIMEOUT] BASE[CNOC_0_SOUTH_BUS_TIMEOUT] BASE[CNOC_MM_BUS_TIMEOUT] BASE[QHS_MMSS0_U_AHB_BUS_TIMEOUT0] BASE[CNOC_0_CENTER_LEFT_BUS_TIMEOUT] BASE[SNOC_3_BUS_TIMEOUT] BASE[SNOC_2_BUS_TIMEOUT] BASE[CNOC_1_NORTH_BUS_TIMEOUT] BASE[CNOC_0_CENTER_RIGHT_BUS_TIMEOUT] TIMEOUT[TCSR_TCSR_REGS] INTR_HMSS_ENABLE[TCSR_TCSR_REGS] BASE[CNOC_2_NORTH_BUS_TIMEOUT] BASE[CNOC_USB2_BUS_TIMEOUT] BASE[SNOC_1_BUS_TIMEOUT] BASE[CNOC_4_CENTER_RIGHT_BUS_TIMEOUT] BASE[SNOC_4_BUS_TIMEOUT] BASE[CNOC_1_CENTER_LEFT_BUS_TIMEOUT] BASE[CNOC_0_NORTH_BUS_TIMEOUT] BASE[CNOC_1_CENTER_RIGHT_BUS_TIMEOUT] 
  'Exclude' filters applied: RESERVED DUMMY INTR_RPM[TCSR_TCSR_REGS] INTR_MSS[TCSR_TCSR_REGS] INTR_LPASS[TCSR_TCSR_REGS] INTR_TURING[TCSR_TCSR_REGS] INTR_HMSS_ENABLE_BUS_TIMEOUT[TCSR_TCSR_REGS] 
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

  $Header: //components/rel/core.tz/1.0.7.1/systemdrivers/icb/src/660/ABTimeout_HWIO.h#1 $
  $DateTime: 2020/01/14 12:35:09 $
  $Author: pwbldsvc $

  ===========================================================================
*/

#include "msmhwiobase.h"

/*----------------------------------------------------------------------------
 * MODULE: CNOC_0_CENTER_LEFT_BUS_TIMEOUT
 *--------------------------------------------------------------------------*/

#define CNOC_0_CENTER_LEFT_BUS_TIMEOUT_REG_BASE                          (CNOC_0_CENTER_LEFT_BUS_TIMEOUT_BASE      + 0x00000000)

/*----------------------------------------------------------------------------
 * MODULE: CNOC_0_CENTER_RIGHT_BUS_TIMEOUT
 *--------------------------------------------------------------------------*/

#define CNOC_0_CENTER_RIGHT_BUS_TIMEOUT_REG_BASE                          (CNOC_0_CENTER_RIGHT_BUS_TIMEOUT_BASE      + 0x00000000)

/*----------------------------------------------------------------------------
 * MODULE: CNOC_0_NORTH_BUS_TIMEOUT
 *--------------------------------------------------------------------------*/

#define CNOC_0_NORTH_BUS_TIMEOUT_REG_BASE                          (CNOC_0_NORTH_BUS_TIMEOUT_BASE      + 0x00000000)

/*----------------------------------------------------------------------------
 * MODULE: CNOC_0_SOUTH_BUS_TIMEOUT
 *--------------------------------------------------------------------------*/

#define CNOC_0_SOUTH_BUS_TIMEOUT_REG_BASE                          (CNOC_0_SOUTH_BUS_TIMEOUT_BASE      + 0x00000000)

/*----------------------------------------------------------------------------
 * MODULE: CNOC_1_CENTER_LEFT_BUS_TIMEOUT
 *--------------------------------------------------------------------------*/

#define CNOC_1_CENTER_LEFT_BUS_TIMEOUT_REG_BASE                          (CNOC_1_CENTER_LEFT_BUS_TIMEOUT_BASE      + 0x00000000)

/*----------------------------------------------------------------------------
 * MODULE: CNOC_1_CENTER_RIGHT_BUS_TIMEOUT
 *--------------------------------------------------------------------------*/

#define CNOC_1_CENTER_RIGHT_BUS_TIMEOUT_REG_BASE                          (CNOC_1_CENTER_RIGHT_BUS_TIMEOUT_BASE      + 0x00000000)

/*----------------------------------------------------------------------------
 * MODULE: CNOC_1_NORTH_BUS_TIMEOUT
 *--------------------------------------------------------------------------*/

#define CNOC_1_NORTH_BUS_TIMEOUT_REG_BASE                          (CNOC_1_NORTH_BUS_TIMEOUT_BASE      + 0x00000000)

/*----------------------------------------------------------------------------
 * MODULE: CNOC_2_CENTER_RIGHT_BUS_TIMEOUT
 *--------------------------------------------------------------------------*/

#define CNOC_2_CENTER_RIGHT_BUS_TIMEOUT_REG_BASE                          (CNOC_2_CENTER_RIGHT_BUS_TIMEOUT_BASE      + 0x00000000)

/*----------------------------------------------------------------------------
 * MODULE: CNOC_2_NORTH_BUS_TIMEOUT
 *--------------------------------------------------------------------------*/

#define CNOC_2_NORTH_BUS_TIMEOUT_REG_BASE                          (CNOC_2_NORTH_BUS_TIMEOUT_BASE      + 0x00000000)

/*----------------------------------------------------------------------------
 * MODULE: CNOC_3_CENTER_RIGHT_BUS_TIMEOUT
 *--------------------------------------------------------------------------*/

#define CNOC_3_CENTER_RIGHT_BUS_TIMEOUT_REG_BASE                          (CNOC_3_CENTER_RIGHT_BUS_TIMEOUT_BASE      + 0x00000000)

/*----------------------------------------------------------------------------
 * MODULE: CNOC_4_CENTER_RIGHT_BUS_TIMEOUT
 *--------------------------------------------------------------------------*/

#define CNOC_4_CENTER_RIGHT_BUS_TIMEOUT_REG_BASE                          (CNOC_4_CENTER_RIGHT_BUS_TIMEOUT_BASE      + 0x00000000)

/*----------------------------------------------------------------------------
 * MODULE: CNOC_5_CENTER_RIGHT_BUS_TIMEOUT
 *--------------------------------------------------------------------------*/

#define CNOC_5_CENTER_RIGHT_BUS_TIMEOUT_REG_BASE                          (CNOC_5_CENTER_RIGHT_BUS_TIMEOUT_BASE      + 0x00000000)

/*----------------------------------------------------------------------------
 * MODULE: CNOC_MM_BUS_TIMEOUT
 *--------------------------------------------------------------------------*/

#define CNOC_MM_BUS_TIMEOUT_REG_BASE                          (CNOC_MM_BUS_TIMEOUT_BASE      + 0x00000000)

/*----------------------------------------------------------------------------
 * MODULE: CNOC_USB2_BUS_TIMEOUT
 *--------------------------------------------------------------------------*/

#define CNOC_USB2_BUS_TIMEOUT_REG_BASE                          (CNOC_USB2_BUS_TIMEOUT_BASE      + 0x00000000)

/*----------------------------------------------------------------------------
 * MODULE: CNOC_USB3_BUS_TIMEOUT
 *--------------------------------------------------------------------------*/

#define CNOC_USB3_BUS_TIMEOUT_REG_BASE                          (CNOC_USB3_BUS_TIMEOUT_BASE      + 0x00000000)

/*----------------------------------------------------------------------------
 * MODULE: QHS_MMSS0_U_AHB_BUS_TIMEOUT0
 *--------------------------------------------------------------------------*/

#define QHS_MMSS0_U_AHB_BUS_TIMEOUT0_REG_BASE                   (MMSS_BASE      + 0x00000000)

/*----------------------------------------------------------------------------
 * MODULE: QHS_MMSS1_U_AHB_BUS_TIMEOUT1
 *--------------------------------------------------------------------------*/

#define QHS_MMSS1_U_AHB_BUS_TIMEOUT1_REG_BASE                   (MMSS_BASE      + 0x00001000)

/*----------------------------------------------------------------------------
 * MODULE: QHS_MMSS2_U_AHB_BUS_TIMEOUT2
 *--------------------------------------------------------------------------*/

#define QHS_MMSS2_U_AHB_BUS_TIMEOUT2_REG_BASE                   (MMSS_BASE      + 0x00002000)

/*----------------------------------------------------------------------------
 * MODULE: QHS_MMSS3_U_AHB_BUS_TIMEOUT3
 *--------------------------------------------------------------------------*/

#define QHS_MMSS3_U_AHB_BUS_TIMEOUT3_REG_BASE                   (MMSS_BASE      + 0x00003000)

/*----------------------------------------------------------------------------
 * MODULE: SNOC_1_BUS_TIMEOUT
 *--------------------------------------------------------------------------*/

#define SNOC_1_BUS_TIMEOUT_REG_BASE                          (SNOC_1_BUS_TIMEOUT_BASE      + 0x00000000)

/*----------------------------------------------------------------------------
 * MODULE: SNOC_2_BUS_TIMEOUT
 *--------------------------------------------------------------------------*/

#define SNOC_2_BUS_TIMEOUT_REG_BASE                          (SNOC_2_BUS_TIMEOUT_BASE      + 0x00000000)

/*----------------------------------------------------------------------------
 * MODULE: SNOC_3_BUS_TIMEOUT
 *--------------------------------------------------------------------------*/

#define SNOC_3_BUS_TIMEOUT_REG_BASE                          (SNOC_3_BUS_TIMEOUT_BASE      + 0x00000000)

/*----------------------------------------------------------------------------
 * MODULE: SNOC_4_BUS_TIMEOUT
 *--------------------------------------------------------------------------*/

#define SNOC_4_BUS_TIMEOUT_REG_BASE                          (SNOC_4_BUS_TIMEOUT_BASE      + 0x00000000)

/*----------------------------------------------------------------------------
 * MODULE: TCSR_TCSR_REGS
 *--------------------------------------------------------------------------*/

#define TCSR_TCSR_REGS_REG_BASE                                                                                (CORE_TOP_CSR_BASE      + 0x000c0000)

#define HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_ADDR                                                                    (TCSR_TCSR_REGS_REG_BASE      + 0x00000800)
#define HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_RMSK                                                                           0x1
#define HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_IN          \
        in_dword_masked(HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_ADDR, HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_RMSK)
#define HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_INM(m)      \
        in_dword_masked(HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_ADDR, m)
#define HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_OUT(v)      \
        out_dword(HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_ADDR,v)
#define HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_ADDR,m,v,HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_IN)
#define HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_TIMEOUT_SLAVE_GLB_EN_BMSK                                                      0x1
#define HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_TIMEOUT_SLAVE_GLB_EN_SHFT                                                      0x0

#define HWIO_TCSR_TIMEOUT_INTERNAL_EN_ADDR                                                                     (TCSR_TCSR_REGS_REG_BASE      + 0x00000804)
#define HWIO_TCSR_TIMEOUT_INTERNAL_EN_RMSK                                                                            0x1
#define HWIO_TCSR_TIMEOUT_INTERNAL_EN_IN          \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTERNAL_EN_ADDR, HWIO_TCSR_TIMEOUT_INTERNAL_EN_RMSK)
#define HWIO_TCSR_TIMEOUT_INTERNAL_EN_INM(m)      \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTERNAL_EN_ADDR, m)
#define HWIO_TCSR_TIMEOUT_INTERNAL_EN_OUT(v)      \
        out_dword(HWIO_TCSR_TIMEOUT_INTERNAL_EN_ADDR,v)
#define HWIO_TCSR_TIMEOUT_INTERNAL_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_TIMEOUT_INTERNAL_EN_ADDR,m,v,HWIO_TCSR_TIMEOUT_INTERNAL_EN_IN)
#define HWIO_TCSR_TIMEOUT_INTERNAL_EN_TIMEOUT_INTERNAL_EN_BMSK                                                        0x1
#define HWIO_TCSR_TIMEOUT_INTERNAL_EN_TIMEOUT_INTERNAL_EN_SHFT                                                        0x0

#define HWIO_TCSR_TIMEOUT_INTR_STATUS_ADDR                                                                     (TCSR_TCSR_REGS_REG_BASE      + 0x00008020)
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_RMSK                                                                     0xffffffff
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_IN          \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_STATUS_ADDR, HWIO_TCSR_TIMEOUT_INTR_STATUS_RMSK)
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_INM(m)      \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_STATUS_ADDR, m)
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_SNOC_S3_IRQ_BMSK                                             0x80000000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_SNOC_S3_IRQ_SHFT                                                   0x1f
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_SOUTH_S3_IRQ_BMSK                                       0x40000000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_SOUTH_S3_IRQ_SHFT                                             0x1e
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_SOUTH_S2_IRQ_BMSK                                       0x20000000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_SOUTH_S2_IRQ_SHFT                                             0x1d
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_TURING_IRQ_OUT_AHB_TIMEOUT_1_BMSK                                        0x10000000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_TURING_IRQ_OUT_AHB_TIMEOUT_1_SHFT                                              0x1c
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_SOUTH_S0_IRQ_BMSK                                        0x8000000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_SOUTH_S0_IRQ_SHFT                                             0x1b
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_SNOC_LPASS_IRQ_BMSK                                           0x4000000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_SNOC_LPASS_IRQ_SHFT                                                0x1a
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_QHS_MMSS3_BUS_TIMEOUT_IRQ_BMSK                                            0x2000000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_QHS_MMSS3_BUS_TIMEOUT_IRQ_SHFT                                                 0x19
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_WCSS_ECAHB_TSLV_INTR_BMSK                                                 0x1000000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_WCSS_ECAHB_TSLV_INTR_SHFT                                                      0x18
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_SNOC_CDSP_IRQ_BMSK                                             0x800000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_SNOC_CDSP_IRQ_SHFT                                                 0x17
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_LPASS_IRQ_OUT_AHB_TIMEOUT1_BMSK                                            0x400000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_LPASS_IRQ_OUT_AHB_TIMEOUT1_SHFT                                                0x16
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_LPASS_IRQ_OUT_AHB_TIMEOUT0_BMSK                                            0x200000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_LPASS_IRQ_OUT_AHB_TIMEOUT0_SHFT                                                0x15
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_WCSS_TCSR_WAHB_TSLV_INTR_BMSK                                              0x100000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_WCSS_TCSR_WAHB_TSLV_INTR_SHFT                                                  0x14
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_QHS_MMSS2_BUS_TIMEOUT_IRQ_BMSK                                              0x80000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_QHS_MMSS2_BUS_TIMEOUT_IRQ_SHFT                                                 0x13
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_QHS_MMSS1_BUS_TIMEOUT_IRQ_BMSK                                              0x40000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_QHS_MMSS1_BUS_TIMEOUT_IRQ_SHFT                                                 0x12
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_QHS_MMSS_BUS_TIMEOUT_IRQ_BMSK                                               0x20000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_QHS_MMSS_BUS_TIMEOUT_IRQ_SHFT                                                  0x11
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CENTER_LEFT_S1_IRQ_BMSK                                    0x10000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CENTER_LEFT_S1_IRQ_SHFT                                       0x10
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_MM_CFG_IRQ_BMSK                                             0x8000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_MM_CFG_IRQ_SHFT                                                0xf
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_NORTH_S1_IRQ_BMSK                                           0x4000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_NORTH_S1_IRQ_SHFT                                              0xe
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_NORTH_S0_IRQ_BMSK                                           0x2000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_NORTH_S0_IRQ_SHFT                                              0xd
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_NORTH_S2_IRQ_BMSK                                           0x1000
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_NORTH_S2_IRQ_SHFT                                              0xc
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_WCSS_TCSR_WAPB_TSLV_IRQ_BMSK                                                  0x800
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_WCSS_TCSR_WAPB_TSLV_IRQ_SHFT                                                    0xb
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_MSS_CONFIG_TIMEOUT_SLAVE_IRQ_BMSK                                             0x400
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_MSS_CONFIG_TIMEOUT_SLAVE_IRQ_SHFT                                               0xa
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_SNOC_IPA_IRQ_BMSK                                                 0x200
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_SNOC_IPA_IRQ_SHFT                                                   0x9
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CENTER_LEFT_S0_IRQ_BMSK                                      0x100
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CENTER_LEFT_S0_IRQ_SHFT                                        0x8
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_TURING_IRQ_OUT_AHB_TIMEOUT_0_BMSK                                              0x80
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_TURING_IRQ_OUT_AHB_TIMEOUT_0_SHFT                                               0x7
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_WCSS_TCSR_NOC_INTR_BMSK                                                        0x40
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_WCSS_TCSR_NOC_INTR_SHFT                                                         0x6
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CTR_S5_IRQ_BMSK                                               0x20
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CTR_S5_IRQ_SHFT                                                0x5
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CTR_S4_IRQ_BMSK                                               0x10
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CTR_S4_IRQ_SHFT                                                0x4
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CTR_S3_IRQ_BMSK                                                0x8
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CTR_S3_IRQ_SHFT                                                0x3
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CTR_S2_IRQ_BMSK                                                0x4
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CTR_S2_IRQ_SHFT                                                0x2
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CTR_S1_IRQ_BMSK                                                0x2
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CTR_S1_IRQ_SHFT                                                0x1
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CTR_S0_IRQ_BMSK                                                0x1
#define HWIO_TCSR_TIMEOUT_INTR_STATUS_BUS_TIMEOUT_CNOC_CTR_S0_IRQ_SHFT                                                0x0

#define HWIO_TCSR_TIMEOUT_INTR_STATUS1_ADDR                                                                    (TCSR_TCSR_REGS_REG_BASE      + 0x00008024)
#define HWIO_TCSR_TIMEOUT_INTR_STATUS1_RMSK                                                                           0x3
#define HWIO_TCSR_TIMEOUT_INTR_STATUS1_IN          \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_STATUS1_ADDR, HWIO_TCSR_TIMEOUT_INTR_STATUS1_RMSK)
#define HWIO_TCSR_TIMEOUT_INTR_STATUS1_INM(m)      \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_STATUS1_ADDR, m)
#define HWIO_TCSR_TIMEOUT_INTR_STATUS1_BUS_TIMEOUT_4_LPASS_IRQ_BMSK                                                   0x2
#define HWIO_TCSR_TIMEOUT_INTR_STATUS1_BUS_TIMEOUT_4_LPASS_IRQ_SHFT                                                   0x1
#define HWIO_TCSR_TIMEOUT_INTR_STATUS1_BUS_TIMEOUT_3_LPASS_IRQ_BMSK                                                   0x1
#define HWIO_TCSR_TIMEOUT_INTR_STATUS1_BUS_TIMEOUT_3_LPASS_IRQ_SHFT                                                   0x0

#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_ADDR                                                                (TCSR_TCSR_REGS_REG_BASE      + 0x00008040)
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_RMSK                                                                0xffffffff
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_IN          \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_ADDR, HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_RMSK)
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_INM(m)      \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_ADDR, m)
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_OUT(v)      \
        out_dword(HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_ADDR,v)
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_ADDR,m,v,HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_IN)
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_TURING_IRQ_OUT_AHB_TIMEOUT_1_ENABLE_BMSK                            0x10000000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_TURING_IRQ_OUT_AHB_TIMEOUT_1_ENABLE_SHFT                                  0x1c
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_QHS_MMSS3_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                0x2000000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_QHS_MMSS3_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                     0x19
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_WCSS_ECAHB_TSLV_INTR_ENABLE_BMSK                                     0x1000000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_WCSS_ECAHB_TSLV_INTR_ENABLE_SHFT                                          0x18
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_LPASS_IRQ_OUT_AHB_TIMEOUT1_ENABLE_BMSK                                0x400000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_LPASS_IRQ_OUT_AHB_TIMEOUT1_ENABLE_SHFT                                    0x16
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_LPASS_IRQ_OUT_AHB_TIMEOUT0_ENABLE_BMSK                                0x200000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_LPASS_IRQ_OUT_AHB_TIMEOUT0_ENABLE_SHFT                                    0x15
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_WCSS_TCSR_WAHB_TSLV_INTR_ENABLE_BMSK                                  0x100000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_WCSS_TCSR_WAHB_TSLV_INTR_ENABLE_SHFT                                      0x14
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_QHS_MMSS2_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                  0x80000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_QHS_MMSS2_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                     0x13
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_QHS_MMSS1_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                  0x40000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_QHS_MMSS1_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                     0x12
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_QHS_MMSS_BUS_TIMEOUT_IRQ_ENABLE_BMSK                                   0x20000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_QHS_MMSS_BUS_TIMEOUT_IRQ_ENABLE_SHFT                                      0x11
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUST_TIMEOUT_CNOC_NORTH_S1_IRQ_ENABLE_BMSK                              0x4000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUST_TIMEOUT_CNOC_NORTH_S1_IRQ_ENABLE_SHFT                                 0xe
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUST_TIMEOUT_CNOC_NORTH_S0_IRQ_ENABLE_BMSK                              0x2000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUST_TIMEOUT_CNOC_NORTH_S0_IRQ_ENABLE_SHFT                                 0xd
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUST_TIMEOUT_CNOC_NORTH_S2_IRQ_ENABLE_BMSK                              0x1000
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_BUST_TIMEOUT_CNOC_NORTH_S2_IRQ_ENABLE_SHFT                                 0xc
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_WCSS_TCSR_WAPB_TSLV_IRQ_ENABLE_BMSK                                      0x800
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_WCSS_TCSR_WAPB_TSLV_IRQ_ENABLE_SHFT                                        0xb
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_MSS_CONFIG_TIMEOUT_SLAVE_IRQ_ENABLE_BMSK                                 0x400
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_MSS_CONFIG_TIMEOUT_SLAVE_IRQ_ENABLE_SHFT                                   0xa
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_TURING_IRQ_OUT_AHB_TIMEOUT_0_ENABLE_BMSK                                  0x80
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_TURING_IRQ_OUT_AHB_TIMEOUT_0_ENABLE_SHFT                                   0x7
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_WCSS_TCSR_NOC_INTR_ENABLE_BMSK                                            0x40
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE_WCSS_TCSR_NOC_INTR_ENABLE_SHFT                                             0x6

#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE1_ADDR                                                               (TCSR_TCSR_REGS_REG_BASE      + 0x00008044)
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE1_RMSK                                                                      0x3
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE1_IN          \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE1_ADDR, HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE1_RMSK)
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE1_INM(m)      \
        in_dword_masked(HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE1_ADDR, m)
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE1_OUT(v)      \
        out_dword(HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE1_ADDR,v)
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE1_ADDR,m,v,HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE1_IN)
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE1_BUS_TIMEOUT_3_LPASS_IRQ_ENABLE_BMSK                                       0x2
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE1_BUS_TIMEOUT_3_LPASS_IRQ_ENABLE_SHFT                                       0x1
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE1_BUS_TIMEOUT_4_LPASS_IRQ_ENABLE_BMSK                                       0x1
#define HWIO_TCSR_TIMEOUT_INTR_HMSS_ENABLE1_BUS_TIMEOUT_4_LPASS_IRQ_ENABLE_SHFT                                       0x0


#endif /* __ABTIMEOUT_HWIO_H__ */