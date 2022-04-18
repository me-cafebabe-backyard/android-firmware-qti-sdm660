#ifndef __QDSP_PM_CLOCKS_HWIO_660_CDSP_H__
#define __QDSP_PM_CLOCKS_HWIO_660_CDSP_H__
/*
===========================================================================
*/
/**
  @file qdsp_pm_clocks_hwio_660_cdsp.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    SDM660 (Starlord) [starlord_v1.0_p3q2r79]
 
  This file contains HWIO register definitions for the following modules:
    TURING_TURING_TCSR

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

  $Header: //components/rel/core.qdsp6/1.0.c2/power/qdsp_pm/config/660/cdsp/qdsp_pm_clocks_hwio_660_cdsp.h#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $

  ===========================================================================
*/

/*----------------------------------------------------------------------------
 * MODULE: TURING_TURING_TCSR
 *--------------------------------------------------------------------------*/

#define TURING_TURING_TCSR_REG_BASE                                         (TURING_BASE      + 0x00080000)
#define TURING_TURING_TCSR_REG_BASE_OFFS                                    0x00080000

#define HWIO_TURING_HW_VERSION_ADDR                                         (TURING_TURING_TCSR_REG_BASE      + 0x00000000)
#define HWIO_TURING_HW_VERSION_OFFS                                         (TURING_TURING_TCSR_REG_BASE_OFFS + 0x00000000)
#define HWIO_TURING_HW_VERSION_RMSK                                         0xffffffff
#define HWIO_TURING_HW_VERSION_IN          \
        in_dword_masked(HWIO_TURING_HW_VERSION_ADDR, HWIO_TURING_HW_VERSION_RMSK)
#define HWIO_TURING_HW_VERSION_INM(m)      \
        in_dword_masked(HWIO_TURING_HW_VERSION_ADDR, m)
#define HWIO_TURING_HW_VERSION_MAJOR_BMSK                                   0xf0000000
#define HWIO_TURING_HW_VERSION_MAJOR_SHFT                                         0x1c
#define HWIO_TURING_HW_VERSION_MINOR_BMSK                                    0xfff0000
#define HWIO_TURING_HW_VERSION_MINOR_SHFT                                         0x10
#define HWIO_TURING_HW_VERSION_STEP_BMSK                                        0xffff
#define HWIO_TURING_HW_VERSION_STEP_SHFT                                           0x0

#define HWIO_TURING_TCSR_DEBUG_CTL_ADDR                                     (TURING_TURING_TCSR_REG_BASE      + 0x00000004)
#define HWIO_TURING_TCSR_DEBUG_CTL_OFFS                                     (TURING_TURING_TCSR_REG_BASE_OFFS + 0x00000004)
#define HWIO_TURING_TCSR_DEBUG_CTL_RMSK                                        0x11fff
#define HWIO_TURING_TCSR_DEBUG_CTL_IN          \
        in_dword_masked(HWIO_TURING_TCSR_DEBUG_CTL_ADDR, HWIO_TURING_TCSR_DEBUG_CTL_RMSK)
#define HWIO_TURING_TCSR_DEBUG_CTL_INM(m)      \
        in_dword_masked(HWIO_TURING_TCSR_DEBUG_CTL_ADDR, m)
#define HWIO_TURING_TCSR_DEBUG_CTL_OUT(v)      \
        out_dword(HWIO_TURING_TCSR_DEBUG_CTL_ADDR,v)
#define HWIO_TURING_TCSR_DEBUG_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TCSR_DEBUG_CTL_ADDR,m,v,HWIO_TURING_TCSR_DEBUG_CTL_IN)
#define HWIO_TURING_TCSR_DEBUG_CTL_TURING_DEBUG_EN_BMSK                        0x10000
#define HWIO_TURING_TCSR_DEBUG_CTL_TURING_DEBUG_EN_SHFT                           0x10
#define HWIO_TURING_TCSR_DEBUG_CTL_SEL_ADDR_BMSK                                0x1f00
#define HWIO_TURING_TCSR_DEBUG_CTL_SEL_ADDR_SHFT                                   0x8
#define HWIO_TURING_TCSR_DEBUG_CTL_SEL_BMSK                                       0xff
#define HWIO_TURING_TCSR_DEBUG_CTL_SEL_SHFT                                        0x0

#define HWIO_TURING_AHBE_CFG_ADDR                                           (TURING_TURING_TCSR_REG_BASE      + 0x0000002c)
#define HWIO_TURING_AHBE_CFG_OFFS                                           (TURING_TURING_TCSR_REG_BASE_OFFS + 0x0000002c)
#define HWIO_TURING_AHBE_CFG_RMSK                                                0x111
#define HWIO_TURING_AHBE_CFG_IN          \
        in_dword_masked(HWIO_TURING_AHBE_CFG_ADDR, HWIO_TURING_AHBE_CFG_RMSK)
#define HWIO_TURING_AHBE_CFG_INM(m)      \
        in_dword_masked(HWIO_TURING_AHBE_CFG_ADDR, m)
#define HWIO_TURING_AHBE_CFG_OUT(v)      \
        out_dword(HWIO_TURING_AHBE_CFG_ADDR,v)
#define HWIO_TURING_AHBE_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_AHBE_CFG_ADDR,m,v,HWIO_TURING_AHBE_CFG_IN)
#define HWIO_TURING_AHBE_CFG_Q6SS_PRIORITY_BMSK                                  0x100
#define HWIO_TURING_AHBE_CFG_Q6SS_PRIORITY_SHFT                                    0x8
#define HWIO_TURING_AHBE_CFG_FABRIC_PRIORITY_BMSK                                 0x10
#define HWIO_TURING_AHBE_CFG_FABRIC_PRIORITY_SHFT                                  0x4
#define HWIO_TURING_AHBE_CFG_ROUND_ROBIN_EN_BMSK                                   0x1
#define HWIO_TURING_AHBE_CFG_ROUND_ROBIN_EN_SHFT                                   0x0

#define HWIO_TURING_AHBE_LOCK_CTL_ADDR                                      (TURING_TURING_TCSR_REG_BASE      + 0x00000030)
#define HWIO_TURING_AHBE_LOCK_CTL_OFFS                                      (TURING_TURING_TCSR_REG_BASE_OFFS + 0x00000030)
#define HWIO_TURING_AHBE_LOCK_CTL_RMSK                                             0x3
#define HWIO_TURING_AHBE_LOCK_CTL_IN          \
        in_dword_masked(HWIO_TURING_AHBE_LOCK_CTL_ADDR, HWIO_TURING_AHBE_LOCK_CTL_RMSK)
#define HWIO_TURING_AHBE_LOCK_CTL_INM(m)      \
        in_dword_masked(HWIO_TURING_AHBE_LOCK_CTL_ADDR, m)
#define HWIO_TURING_AHBE_LOCK_CTL_OUT(v)      \
        out_dword(HWIO_TURING_AHBE_LOCK_CTL_ADDR,v)
#define HWIO_TURING_AHBE_LOCK_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_AHBE_LOCK_CTL_ADDR,m,v,HWIO_TURING_AHBE_LOCK_CTL_IN)
#define HWIO_TURING_AHBE_LOCK_CTL_Q6SS_LOCK_EN_BMSK                                0x2
#define HWIO_TURING_AHBE_LOCK_CTL_Q6SS_LOCK_EN_SHFT                                0x1
#define HWIO_TURING_AHBE_LOCK_CTL_FABRIC_LOCK_EN_BMSK                              0x1
#define HWIO_TURING_AHBE_LOCK_CTL_FABRIC_LOCK_EN_SHFT                              0x0

#define HWIO_TURING_AHBE_STATUS_ADDR                                        (TURING_TURING_TCSR_REG_BASE      + 0x00000034)
#define HWIO_TURING_AHBE_STATUS_OFFS                                        (TURING_TURING_TCSR_REG_BASE_OFFS + 0x00000034)
#define HWIO_TURING_AHBE_STATUS_RMSK                                               0x7
#define HWIO_TURING_AHBE_STATUS_IN          \
        in_dword_masked(HWIO_TURING_AHBE_STATUS_ADDR, HWIO_TURING_AHBE_STATUS_RMSK)
#define HWIO_TURING_AHBE_STATUS_INM(m)      \
        in_dword_masked(HWIO_TURING_AHBE_STATUS_ADDR, m)
#define HWIO_TURING_AHBE_STATUS_AHBE_DECODE_BOUNDARY_ERROR_BMSK                    0x4
#define HWIO_TURING_AHBE_STATUS_AHBE_DECODE_BOUNDARY_ERROR_SHFT                    0x2
#define HWIO_TURING_AHBE_STATUS_AHBE_DECODE_ERROR_BMSK                             0x2
#define HWIO_TURING_AHBE_STATUS_AHBE_DECODE_ERROR_SHFT                             0x1
#define HWIO_TURING_AHBE_STATUS_AHBE_MISALIGNED_BMSK                               0x1
#define HWIO_TURING_AHBE_STATUS_AHBE_MISALIGNED_SHFT                               0x0

#define HWIO_TURING_AHBE_ACK_ADDR                                           (TURING_TURING_TCSR_REG_BASE      + 0x00000038)
#define HWIO_TURING_AHBE_ACK_OFFS                                           (TURING_TURING_TCSR_REG_BASE_OFFS + 0x00000038)
#define HWIO_TURING_AHBE_ACK_RMSK                                                  0x7
#define HWIO_TURING_AHBE_ACK_OUT(v)      \
        out_dword(HWIO_TURING_AHBE_ACK_ADDR,v)
#define HWIO_TURING_AHBE_ACK_AHBE_DECODE_BOUNDARY_ERROR_BMSK                       0x4
#define HWIO_TURING_AHBE_ACK_AHBE_DECODE_BOUNDARY_ERROR_SHFT                       0x2
#define HWIO_TURING_AHBE_ACK_AHBE_DECODE_ERROR_BMSK                                0x2
#define HWIO_TURING_AHBE_ACK_AHBE_DECODE_ERROR_SHFT                                0x1
#define HWIO_TURING_AHBE_ACK_AHBE_MISALIGNED_BMSK                                  0x1
#define HWIO_TURING_AHBE_ACK_AHBE_MISALIGNED_SHFT                                  0x0

#define HWIO_TURING_AHBE_INT_EN_ADDR                                        (TURING_TURING_TCSR_REG_BASE      + 0x0000003c)
#define HWIO_TURING_AHBE_INT_EN_OFFS                                        (TURING_TURING_TCSR_REG_BASE_OFFS + 0x0000003c)
#define HWIO_TURING_AHBE_INT_EN_RMSK                                               0x7
#define HWIO_TURING_AHBE_INT_EN_IN          \
        in_dword_masked(HWIO_TURING_AHBE_INT_EN_ADDR, HWIO_TURING_AHBE_INT_EN_RMSK)
#define HWIO_TURING_AHBE_INT_EN_INM(m)      \
        in_dword_masked(HWIO_TURING_AHBE_INT_EN_ADDR, m)
#define HWIO_TURING_AHBE_INT_EN_OUT(v)      \
        out_dword(HWIO_TURING_AHBE_INT_EN_ADDR,v)
#define HWIO_TURING_AHBE_INT_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_AHBE_INT_EN_ADDR,m,v,HWIO_TURING_AHBE_INT_EN_IN)
#define HWIO_TURING_AHBE_INT_EN_AHBE_DECODE_BOUNDARY_ERROR_BMSK                    0x4
#define HWIO_TURING_AHBE_INT_EN_AHBE_DECODE_BOUNDARY_ERROR_SHFT                    0x2
#define HWIO_TURING_AHBE_INT_EN_AHBE_DECODE_ERROR_BMSK                             0x2
#define HWIO_TURING_AHBE_INT_EN_AHBE_DECODE_ERROR_SHFT                             0x1
#define HWIO_TURING_AHBE_INT_EN_AHBE_MISALIGNED_BMSK                               0x1
#define HWIO_TURING_AHBE_INT_EN_AHBE_MISALIGNED_SHFT                               0x0

#define HWIO_TURING_AHBE_SPARE_ADDR                                         (TURING_TURING_TCSR_REG_BASE      + 0x00000040)
#define HWIO_TURING_AHBE_SPARE_OFFS                                         (TURING_TURING_TCSR_REG_BASE_OFFS + 0x00000040)
#define HWIO_TURING_AHBE_SPARE_RMSK                                         0xffffffff
#define HWIO_TURING_AHBE_SPARE_IN          \
        in_dword_masked(HWIO_TURING_AHBE_SPARE_ADDR, HWIO_TURING_AHBE_SPARE_RMSK)
#define HWIO_TURING_AHBE_SPARE_INM(m)      \
        in_dword_masked(HWIO_TURING_AHBE_SPARE_ADDR, m)
#define HWIO_TURING_AHBE_SPARE_OUT(v)      \
        out_dword(HWIO_TURING_AHBE_SPARE_ADDR,v)
#define HWIO_TURING_AHBE_SPARE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_AHBE_SPARE_ADDR,m,v,HWIO_TURING_AHBE_SPARE_IN)
#define HWIO_TURING_AHBE_SPARE_AHBE_SPARE_BMSK                              0xffffffff
#define HWIO_TURING_AHBE_SPARE_AHBE_SPARE_SHFT                                     0x0

#define HWIO_TURING_Q6SS_RST_EVB_SEL_ADDR                                   (TURING_TURING_TCSR_REG_BASE      + 0x00001000)
#define HWIO_TURING_Q6SS_RST_EVB_SEL_OFFS                                   (TURING_TURING_TCSR_REG_BASE_OFFS + 0x00001000)
#define HWIO_TURING_Q6SS_RST_EVB_SEL_RMSK                                          0x1
#define HWIO_TURING_Q6SS_RST_EVB_SEL_IN          \
        in_dword_masked(HWIO_TURING_Q6SS_RST_EVB_SEL_ADDR, HWIO_TURING_Q6SS_RST_EVB_SEL_RMSK)
#define HWIO_TURING_Q6SS_RST_EVB_SEL_INM(m)      \
        in_dword_masked(HWIO_TURING_Q6SS_RST_EVB_SEL_ADDR, m)
#define HWIO_TURING_Q6SS_RST_EVB_SEL_OUT(v)      \
        out_dword(HWIO_TURING_Q6SS_RST_EVB_SEL_ADDR,v)
#define HWIO_TURING_Q6SS_RST_EVB_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_Q6SS_RST_EVB_SEL_ADDR,m,v,HWIO_TURING_Q6SS_RST_EVB_SEL_IN)
#define HWIO_TURING_Q6SS_RST_EVB_SEL_SEL_BMSK                                      0x1
#define HWIO_TURING_Q6SS_RST_EVB_SEL_SEL_SHFT                                      0x0

#define HWIO_TURING_Q6SS_RST_EVB_ADDR                                       (TURING_TURING_TCSR_REG_BASE      + 0x00001004)
#define HWIO_TURING_Q6SS_RST_EVB_OFFS                                       (TURING_TURING_TCSR_REG_BASE_OFFS + 0x00001004)
#define HWIO_TURING_Q6SS_RST_EVB_RMSK                                        0xffffff0
#define HWIO_TURING_Q6SS_RST_EVB_IN          \
        in_dword_masked(HWIO_TURING_Q6SS_RST_EVB_ADDR, HWIO_TURING_Q6SS_RST_EVB_RMSK)
#define HWIO_TURING_Q6SS_RST_EVB_INM(m)      \
        in_dword_masked(HWIO_TURING_Q6SS_RST_EVB_ADDR, m)
#define HWIO_TURING_Q6SS_RST_EVB_OUT(v)      \
        out_dword(HWIO_TURING_Q6SS_RST_EVB_ADDR,v)
#define HWIO_TURING_Q6SS_RST_EVB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_Q6SS_RST_EVB_ADDR,m,v,HWIO_TURING_Q6SS_RST_EVB_IN)
#define HWIO_TURING_Q6SS_RST_EVB_EVB_BMSK                                    0xffffff0
#define HWIO_TURING_Q6SS_RST_EVB_EVB_SHFT                                          0x4

#define HWIO_TURING_STM_MUXSEL_n_ADDR(n)                                    (TURING_TURING_TCSR_REG_BASE      + 0x00003000 + 0x4 * (n))
#define HWIO_TURING_STM_MUXSEL_n_OFFS(n)                                    (TURING_TURING_TCSR_REG_BASE_OFFS + 0x00003000 + 0x4 * (n))
#define HWIO_TURING_STM_MUXSEL_n_RMSK                                       0x8000000f
#define HWIO_TURING_STM_MUXSEL_n_MAXn                                               31
#define HWIO_TURING_STM_MUXSEL_n_INI(n)        \
        in_dword_masked(HWIO_TURING_STM_MUXSEL_n_ADDR(n), HWIO_TURING_STM_MUXSEL_n_RMSK)
#define HWIO_TURING_STM_MUXSEL_n_INMI(n,mask)    \
        in_dword_masked(HWIO_TURING_STM_MUXSEL_n_ADDR(n), mask)
#define HWIO_TURING_STM_MUXSEL_n_OUTI(n,val)    \
        out_dword(HWIO_TURING_STM_MUXSEL_n_ADDR(n),val)
#define HWIO_TURING_STM_MUXSEL_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TURING_STM_MUXSEL_n_ADDR(n),mask,val,HWIO_TURING_STM_MUXSEL_n_INI(n))
#define HWIO_TURING_STM_MUXSEL_n_ENABLE_BMSK                                0x80000000
#define HWIO_TURING_STM_MUXSEL_n_ENABLE_SHFT                                      0x1f
#define HWIO_TURING_STM_MUXSEL_n_SEL_BMSK                                          0xf
#define HWIO_TURING_STM_MUXSEL_n_SEL_SHFT                                          0x0

#define HWIO_TURING_GP_IRQ_TS_MUX_CTL_0_ADDR                                (TURING_TURING_TCSR_REG_BASE      + 0x00004000)
#define HWIO_TURING_GP_IRQ_TS_MUX_CTL_0_OFFS                                (TURING_TURING_TCSR_REG_BASE_OFFS + 0x00004000)
#define HWIO_TURING_GP_IRQ_TS_MUX_CTL_0_RMSK                                     0x1ff
#define HWIO_TURING_GP_IRQ_TS_MUX_CTL_0_IN          \
        in_dword_masked(HWIO_TURING_GP_IRQ_TS_MUX_CTL_0_ADDR, HWIO_TURING_GP_IRQ_TS_MUX_CTL_0_RMSK)
#define HWIO_TURING_GP_IRQ_TS_MUX_CTL_0_INM(m)      \
        in_dword_masked(HWIO_TURING_GP_IRQ_TS_MUX_CTL_0_ADDR, m)
#define HWIO_TURING_GP_IRQ_TS_MUX_CTL_0_OUT(v)      \
        out_dword(HWIO_TURING_GP_IRQ_TS_MUX_CTL_0_ADDR,v)
#define HWIO_TURING_GP_IRQ_TS_MUX_CTL_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_GP_IRQ_TS_MUX_CTL_0_ADDR,m,v,HWIO_TURING_GP_IRQ_TS_MUX_CTL_0_IN)
#define HWIO_TURING_GP_IRQ_TS_MUX_CTL_0_VFR_BMSK                                 0x100
#define HWIO_TURING_GP_IRQ_TS_MUX_CTL_0_VFR_SHFT                                   0x8
#define HWIO_TURING_GP_IRQ_TS_MUX_CTL_0_SEL_BMSK                                  0xff
#define HWIO_TURING_GP_IRQ_TS_MUX_CTL_0_SEL_SHFT                                   0x0

#define HWIO_TURING_GP_IRQ_STC_MSB_0_ADDR                                   (TURING_TURING_TCSR_REG_BASE      + 0x00004004)
#define HWIO_TURING_GP_IRQ_STC_MSB_0_OFFS                                   (TURING_TURING_TCSR_REG_BASE_OFFS + 0x00004004)
#define HWIO_TURING_GP_IRQ_STC_MSB_0_RMSK                                     0xffffff
#define HWIO_TURING_GP_IRQ_STC_MSB_0_IN          \
        in_dword_masked(HWIO_TURING_GP_IRQ_STC_MSB_0_ADDR, HWIO_TURING_GP_IRQ_STC_MSB_0_RMSK)
#define HWIO_TURING_GP_IRQ_STC_MSB_0_INM(m)      \
        in_dword_masked(HWIO_TURING_GP_IRQ_STC_MSB_0_ADDR, m)
#define HWIO_TURING_GP_IRQ_STC_MSB_0_MSB_BMSK                                 0xffffff
#define HWIO_TURING_GP_IRQ_STC_MSB_0_MSB_SHFT                                      0x0

#define HWIO_TURING_GP_IRQ_STC_LSB_0_ADDR                                   (TURING_TURING_TCSR_REG_BASE      + 0x00004008)
#define HWIO_TURING_GP_IRQ_STC_LSB_0_OFFS                                   (TURING_TURING_TCSR_REG_BASE_OFFS + 0x00004008)
#define HWIO_TURING_GP_IRQ_STC_LSB_0_RMSK                                   0xffffffff
#define HWIO_TURING_GP_IRQ_STC_LSB_0_IN          \
        in_dword_masked(HWIO_TURING_GP_IRQ_STC_LSB_0_ADDR, HWIO_TURING_GP_IRQ_STC_LSB_0_RMSK)
#define HWIO_TURING_GP_IRQ_STC_LSB_0_INM(m)      \
        in_dword_masked(HWIO_TURING_GP_IRQ_STC_LSB_0_ADDR, m)
#define HWIO_TURING_GP_IRQ_STC_LSB_0_LSB_BMSK                               0xffffffff
#define HWIO_TURING_GP_IRQ_STC_LSB_0_LSB_SHFT                                      0x0

#define HWIO_TURING_GP_IRQ_TS_MUX_CTL_1_ADDR                                (TURING_TURING_TCSR_REG_BASE      + 0x00005000)
#define HWIO_TURING_GP_IRQ_TS_MUX_CTL_1_OFFS                                (TURING_TURING_TCSR_REG_BASE_OFFS + 0x00005000)
#define HWIO_TURING_GP_IRQ_TS_MUX_CTL_1_RMSK                                     0x1ff
#define HWIO_TURING_GP_IRQ_TS_MUX_CTL_1_IN          \
        in_dword_masked(HWIO_TURING_GP_IRQ_TS_MUX_CTL_1_ADDR, HWIO_TURING_GP_IRQ_TS_MUX_CTL_1_RMSK)
#define HWIO_TURING_GP_IRQ_TS_MUX_CTL_1_INM(m)      \
        in_dword_masked(HWIO_TURING_GP_IRQ_TS_MUX_CTL_1_ADDR, m)
#define HWIO_TURING_GP_IRQ_TS_MUX_CTL_1_OUT(v)      \
        out_dword(HWIO_TURING_GP_IRQ_TS_MUX_CTL_1_ADDR,v)
#define HWIO_TURING_GP_IRQ_TS_MUX_CTL_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_GP_IRQ_TS_MUX_CTL_1_ADDR,m,v,HWIO_TURING_GP_IRQ_TS_MUX_CTL_1_IN)
#define HWIO_TURING_GP_IRQ_TS_MUX_CTL_1_VFR_BMSK                                 0x100
#define HWIO_TURING_GP_IRQ_TS_MUX_CTL_1_VFR_SHFT                                   0x8
#define HWIO_TURING_GP_IRQ_TS_MUX_CTL_1_SEL_BMSK                                  0xff
#define HWIO_TURING_GP_IRQ_TS_MUX_CTL_1_SEL_SHFT                                   0x0

#define HWIO_TURING_GP_IRQ_STC_MSB_1_ADDR                                   (TURING_TURING_TCSR_REG_BASE      + 0x00005004)
#define HWIO_TURING_GP_IRQ_STC_MSB_1_OFFS                                   (TURING_TURING_TCSR_REG_BASE_OFFS + 0x00005004)
#define HWIO_TURING_GP_IRQ_STC_MSB_1_RMSK                                     0xffffff
#define HWIO_TURING_GP_IRQ_STC_MSB_1_IN          \
        in_dword_masked(HWIO_TURING_GP_IRQ_STC_MSB_1_ADDR, HWIO_TURING_GP_IRQ_STC_MSB_1_RMSK)
#define HWIO_TURING_GP_IRQ_STC_MSB_1_INM(m)      \
        in_dword_masked(HWIO_TURING_GP_IRQ_STC_MSB_1_ADDR, m)
#define HWIO_TURING_GP_IRQ_STC_MSB_1_MSB_BMSK                                 0xffffff
#define HWIO_TURING_GP_IRQ_STC_MSB_1_MSB_SHFT                                      0x0

#define HWIO_TURING_GP_IRQ_STC_LSB_1_ADDR                                   (TURING_TURING_TCSR_REG_BASE      + 0x00005008)
#define HWIO_TURING_GP_IRQ_STC_LSB_1_OFFS                                   (TURING_TURING_TCSR_REG_BASE_OFFS + 0x00005008)
#define HWIO_TURING_GP_IRQ_STC_LSB_1_RMSK                                   0xffffffff
#define HWIO_TURING_GP_IRQ_STC_LSB_1_IN          \
        in_dword_masked(HWIO_TURING_GP_IRQ_STC_LSB_1_ADDR, HWIO_TURING_GP_IRQ_STC_LSB_1_RMSK)
#define HWIO_TURING_GP_IRQ_STC_LSB_1_INM(m)      \
        in_dword_masked(HWIO_TURING_GP_IRQ_STC_LSB_1_ADDR, m)
#define HWIO_TURING_GP_IRQ_STC_LSB_1_LSB_BMSK                               0xffffffff
#define HWIO_TURING_GP_IRQ_STC_LSB_1_LSB_SHFT                                      0x0

#define HWIO_TURING_TCC_CSR_AON_CGCR_ADDR                                   (TURING_TURING_TCSR_REG_BASE      + 0x00006000)
#define HWIO_TURING_TCC_CSR_AON_CGCR_OFFS                                   (TURING_TURING_TCSR_REG_BASE_OFFS + 0x00006000)
#define HWIO_TURING_TCC_CSR_AON_CGCR_RMSK                                          0x3
#define HWIO_TURING_TCC_CSR_AON_CGCR_IN          \
        in_dword_masked(HWIO_TURING_TCC_CSR_AON_CGCR_ADDR, HWIO_TURING_TCC_CSR_AON_CGCR_RMSK)
#define HWIO_TURING_TCC_CSR_AON_CGCR_INM(m)      \
        in_dword_masked(HWIO_TURING_TCC_CSR_AON_CGCR_ADDR, m)
#define HWIO_TURING_TCC_CSR_AON_CGCR_OUT(v)      \
        out_dword(HWIO_TURING_TCC_CSR_AON_CGCR_ADDR,v)
#define HWIO_TURING_TCC_CSR_AON_CGCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TCC_CSR_AON_CGCR_ADDR,m,v,HWIO_TURING_TCC_CSR_AON_CGCR_IN)
#define HWIO_TURING_TCC_CSR_AON_CGCR_HW_CTL_BMSK                                   0x2
#define HWIO_TURING_TCC_CSR_AON_CGCR_HW_CTL_SHFT                                   0x1
#define HWIO_TURING_TCC_CSR_AON_CGCR_CLK_ENABLE_BMSK                               0x1
#define HWIO_TURING_TCC_CSR_AON_CGCR_CLK_ENABLE_SHFT                               0x0

#define HWIO_TURING_TCC_CSR_AON_HYSTERESIS_ADDR                             (TURING_TURING_TCSR_REG_BASE      + 0x00006004)
#define HWIO_TURING_TCC_CSR_AON_HYSTERESIS_OFFS                             (TURING_TURING_TCSR_REG_BASE_OFFS + 0x00006004)
#define HWIO_TURING_TCC_CSR_AON_HYSTERESIS_RMSK                                    0x7
#define HWIO_TURING_TCC_CSR_AON_HYSTERESIS_IN          \
        in_dword_masked(HWIO_TURING_TCC_CSR_AON_HYSTERESIS_ADDR, HWIO_TURING_TCC_CSR_AON_HYSTERESIS_RMSK)
#define HWIO_TURING_TCC_CSR_AON_HYSTERESIS_INM(m)      \
        in_dword_masked(HWIO_TURING_TCC_CSR_AON_HYSTERESIS_ADDR, m)
#define HWIO_TURING_TCC_CSR_AON_HYSTERESIS_OUT(v)      \
        out_dword(HWIO_TURING_TCC_CSR_AON_HYSTERESIS_ADDR,v)
#define HWIO_TURING_TCC_CSR_AON_HYSTERESIS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TCC_CSR_AON_HYSTERESIS_ADDR,m,v,HWIO_TURING_TCC_CSR_AON_HYSTERESIS_IN)
#define HWIO_TURING_TCC_CSR_AON_HYSTERESIS_ACTIVE_HYSTSEL_BMSK                     0x7
#define HWIO_TURING_TCC_CSR_AON_HYSTERESIS_ACTIVE_HYSTSEL_SHFT                     0x0

#define HWIO_TURING_TCSR_AON_CGCR_ADDR                                      (TURING_TURING_TCSR_REG_BASE      + 0x00007000)
#define HWIO_TURING_TCSR_AON_CGCR_OFFS                                      (TURING_TURING_TCSR_REG_BASE_OFFS + 0x00007000)
#define HWIO_TURING_TCSR_AON_CGCR_RMSK                                             0x3
#define HWIO_TURING_TCSR_AON_CGCR_IN          \
        in_dword_masked(HWIO_TURING_TCSR_AON_CGCR_ADDR, HWIO_TURING_TCSR_AON_CGCR_RMSK)
#define HWIO_TURING_TCSR_AON_CGCR_INM(m)      \
        in_dword_masked(HWIO_TURING_TCSR_AON_CGCR_ADDR, m)
#define HWIO_TURING_TCSR_AON_CGCR_OUT(v)      \
        out_dword(HWIO_TURING_TCSR_AON_CGCR_ADDR,v)
#define HWIO_TURING_TCSR_AON_CGCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TCSR_AON_CGCR_ADDR,m,v,HWIO_TURING_TCSR_AON_CGCR_IN)
#define HWIO_TURING_TCSR_AON_CGCR_HW_CTL_BMSK                                      0x2
#define HWIO_TURING_TCSR_AON_CGCR_HW_CTL_SHFT                                      0x1
#define HWIO_TURING_TCSR_AON_CGCR_CLK_ENABLE_BMSK                                  0x1
#define HWIO_TURING_TCSR_AON_CGCR_CLK_ENABLE_SHFT                                  0x0

#define HWIO_TURING_TCSR_AON_HYSTERESIS_ADDR                                (TURING_TURING_TCSR_REG_BASE      + 0x00007004)
#define HWIO_TURING_TCSR_AON_HYSTERESIS_OFFS                                (TURING_TURING_TCSR_REG_BASE_OFFS + 0x00007004)
#define HWIO_TURING_TCSR_AON_HYSTERESIS_RMSK                                       0x7
#define HWIO_TURING_TCSR_AON_HYSTERESIS_IN          \
        in_dword_masked(HWIO_TURING_TCSR_AON_HYSTERESIS_ADDR, HWIO_TURING_TCSR_AON_HYSTERESIS_RMSK)
#define HWIO_TURING_TCSR_AON_HYSTERESIS_INM(m)      \
        in_dword_masked(HWIO_TURING_TCSR_AON_HYSTERESIS_ADDR, m)
#define HWIO_TURING_TCSR_AON_HYSTERESIS_OUT(v)      \
        out_dword(HWIO_TURING_TCSR_AON_HYSTERESIS_ADDR,v)
#define HWIO_TURING_TCSR_AON_HYSTERESIS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TCSR_AON_HYSTERESIS_ADDR,m,v,HWIO_TURING_TCSR_AON_HYSTERESIS_IN)
#define HWIO_TURING_TCSR_AON_HYSTERESIS_ACTIVE_HYSTSEL_BMSK                        0x7
#define HWIO_TURING_TCSR_AON_HYSTERESIS_ACTIVE_HYSTSEL_SHFT                        0x0

#define HWIO_TURING_BUS_TIMEOUT_AON_CGCR_ADDR                               (TURING_TURING_TCSR_REG_BASE      + 0x00008000)
#define HWIO_TURING_BUS_TIMEOUT_AON_CGCR_OFFS                               (TURING_TURING_TCSR_REG_BASE_OFFS + 0x00008000)
#define HWIO_TURING_BUS_TIMEOUT_AON_CGCR_RMSK                                      0x3
#define HWIO_TURING_BUS_TIMEOUT_AON_CGCR_IN          \
        in_dword_masked(HWIO_TURING_BUS_TIMEOUT_AON_CGCR_ADDR, HWIO_TURING_BUS_TIMEOUT_AON_CGCR_RMSK)
#define HWIO_TURING_BUS_TIMEOUT_AON_CGCR_INM(m)      \
        in_dword_masked(HWIO_TURING_BUS_TIMEOUT_AON_CGCR_ADDR, m)
#define HWIO_TURING_BUS_TIMEOUT_AON_CGCR_OUT(v)      \
        out_dword(HWIO_TURING_BUS_TIMEOUT_AON_CGCR_ADDR,v)
#define HWIO_TURING_BUS_TIMEOUT_AON_CGCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_BUS_TIMEOUT_AON_CGCR_ADDR,m,v,HWIO_TURING_BUS_TIMEOUT_AON_CGCR_IN)
#define HWIO_TURING_BUS_TIMEOUT_AON_CGCR_HW_CTL_BMSK                               0x2
#define HWIO_TURING_BUS_TIMEOUT_AON_CGCR_HW_CTL_SHFT                               0x1
#define HWIO_TURING_BUS_TIMEOUT_AON_CGCR_CLK_ENABLE_BMSK                           0x1
#define HWIO_TURING_BUS_TIMEOUT_AON_CGCR_CLK_ENABLE_SHFT                           0x0

#define HWIO_TURING_BUS_TIMEOUT_AON_HYSTERESIS_ADDR                         (TURING_TURING_TCSR_REG_BASE      + 0x00008004)
#define HWIO_TURING_BUS_TIMEOUT_AON_HYSTERESIS_OFFS                         (TURING_TURING_TCSR_REG_BASE_OFFS + 0x00008004)
#define HWIO_TURING_BUS_TIMEOUT_AON_HYSTERESIS_RMSK                                0x7
#define HWIO_TURING_BUS_TIMEOUT_AON_HYSTERESIS_IN          \
        in_dword_masked(HWIO_TURING_BUS_TIMEOUT_AON_HYSTERESIS_ADDR, HWIO_TURING_BUS_TIMEOUT_AON_HYSTERESIS_RMSK)
#define HWIO_TURING_BUS_TIMEOUT_AON_HYSTERESIS_INM(m)      \
        in_dword_masked(HWIO_TURING_BUS_TIMEOUT_AON_HYSTERESIS_ADDR, m)
#define HWIO_TURING_BUS_TIMEOUT_AON_HYSTERESIS_OUT(v)      \
        out_dword(HWIO_TURING_BUS_TIMEOUT_AON_HYSTERESIS_ADDR,v)
#define HWIO_TURING_BUS_TIMEOUT_AON_HYSTERESIS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_BUS_TIMEOUT_AON_HYSTERESIS_ADDR,m,v,HWIO_TURING_BUS_TIMEOUT_AON_HYSTERESIS_IN)
#define HWIO_TURING_BUS_TIMEOUT_AON_HYSTERESIS_ACTIVE_HYSTSEL_BMSK                 0x7
#define HWIO_TURING_BUS_TIMEOUT_AON_HYSTERESIS_ACTIVE_HYSTSEL_SHFT                 0x0

#define HWIO_TURING_Q6AHB_AON_CGCR_ADDR                                     (TURING_TURING_TCSR_REG_BASE      + 0x00009000)
#define HWIO_TURING_Q6AHB_AON_CGCR_OFFS                                     (TURING_TURING_TCSR_REG_BASE_OFFS + 0x00009000)
#define HWIO_TURING_Q6AHB_AON_CGCR_RMSK                                            0x3
#define HWIO_TURING_Q6AHB_AON_CGCR_IN          \
        in_dword_masked(HWIO_TURING_Q6AHB_AON_CGCR_ADDR, HWIO_TURING_Q6AHB_AON_CGCR_RMSK)
#define HWIO_TURING_Q6AHB_AON_CGCR_INM(m)      \
        in_dword_masked(HWIO_TURING_Q6AHB_AON_CGCR_ADDR, m)
#define HWIO_TURING_Q6AHB_AON_CGCR_OUT(v)      \
        out_dword(HWIO_TURING_Q6AHB_AON_CGCR_ADDR,v)
#define HWIO_TURING_Q6AHB_AON_CGCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_Q6AHB_AON_CGCR_ADDR,m,v,HWIO_TURING_Q6AHB_AON_CGCR_IN)
#define HWIO_TURING_Q6AHB_AON_CGCR_HW_CTL_BMSK                                     0x2
#define HWIO_TURING_Q6AHB_AON_CGCR_HW_CTL_SHFT                                     0x1
#define HWIO_TURING_Q6AHB_AON_CGCR_CLK_ENABLE_BMSK                                 0x1
#define HWIO_TURING_Q6AHB_AON_CGCR_CLK_ENABLE_SHFT                                 0x0

#define HWIO_TURING_Q6AHB_AON_HYSTERESIS_ADDR                               (TURING_TURING_TCSR_REG_BASE      + 0x00009004)
#define HWIO_TURING_Q6AHB_AON_HYSTERESIS_OFFS                               (TURING_TURING_TCSR_REG_BASE_OFFS + 0x00009004)
#define HWIO_TURING_Q6AHB_AON_HYSTERESIS_RMSK                                      0x7
#define HWIO_TURING_Q6AHB_AON_HYSTERESIS_IN          \
        in_dword_masked(HWIO_TURING_Q6AHB_AON_HYSTERESIS_ADDR, HWIO_TURING_Q6AHB_AON_HYSTERESIS_RMSK)
#define HWIO_TURING_Q6AHB_AON_HYSTERESIS_INM(m)      \
        in_dword_masked(HWIO_TURING_Q6AHB_AON_HYSTERESIS_ADDR, m)
#define HWIO_TURING_Q6AHB_AON_HYSTERESIS_OUT(v)      \
        out_dword(HWIO_TURING_Q6AHB_AON_HYSTERESIS_ADDR,v)
#define HWIO_TURING_Q6AHB_AON_HYSTERESIS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_Q6AHB_AON_HYSTERESIS_ADDR,m,v,HWIO_TURING_Q6AHB_AON_HYSTERESIS_IN)
#define HWIO_TURING_Q6AHB_AON_HYSTERESIS_ACTIVE_HYSTSEL_BMSK                       0x7
#define HWIO_TURING_Q6AHB_AON_HYSTERESIS_ACTIVE_HYSTSEL_SHFT                       0x0

#define HWIO_TURING_MPU_CFG_AON_CGCR_ADDR                                   (TURING_TURING_TCSR_REG_BASE      + 0x0000a000)
#define HWIO_TURING_MPU_CFG_AON_CGCR_OFFS                                   (TURING_TURING_TCSR_REG_BASE_OFFS + 0x0000a000)
#define HWIO_TURING_MPU_CFG_AON_CGCR_RMSK                                          0x3
#define HWIO_TURING_MPU_CFG_AON_CGCR_IN          \
        in_dword_masked(HWIO_TURING_MPU_CFG_AON_CGCR_ADDR, HWIO_TURING_MPU_CFG_AON_CGCR_RMSK)
#define HWIO_TURING_MPU_CFG_AON_CGCR_INM(m)      \
        in_dword_masked(HWIO_TURING_MPU_CFG_AON_CGCR_ADDR, m)
#define HWIO_TURING_MPU_CFG_AON_CGCR_OUT(v)      \
        out_dword(HWIO_TURING_MPU_CFG_AON_CGCR_ADDR,v)
#define HWIO_TURING_MPU_CFG_AON_CGCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_MPU_CFG_AON_CGCR_ADDR,m,v,HWIO_TURING_MPU_CFG_AON_CGCR_IN)
#define HWIO_TURING_MPU_CFG_AON_CGCR_HW_CTL_BMSK                                   0x2
#define HWIO_TURING_MPU_CFG_AON_CGCR_HW_CTL_SHFT                                   0x1
#define HWIO_TURING_MPU_CFG_AON_CGCR_CLK_ENABLE_BMSK                               0x1
#define HWIO_TURING_MPU_CFG_AON_CGCR_CLK_ENABLE_SHFT                               0x0

#define HWIO_TURING_MPU_CFG_AON_HYSTERESIS_ADDR                             (TURING_TURING_TCSR_REG_BASE      + 0x0000a004)
#define HWIO_TURING_MPU_CFG_AON_HYSTERESIS_OFFS                             (TURING_TURING_TCSR_REG_BASE_OFFS + 0x0000a004)
#define HWIO_TURING_MPU_CFG_AON_HYSTERESIS_RMSK                                    0x7
#define HWIO_TURING_MPU_CFG_AON_HYSTERESIS_IN          \
        in_dword_masked(HWIO_TURING_MPU_CFG_AON_HYSTERESIS_ADDR, HWIO_TURING_MPU_CFG_AON_HYSTERESIS_RMSK)
#define HWIO_TURING_MPU_CFG_AON_HYSTERESIS_INM(m)      \
        in_dword_masked(HWIO_TURING_MPU_CFG_AON_HYSTERESIS_ADDR, m)
#define HWIO_TURING_MPU_CFG_AON_HYSTERESIS_OUT(v)      \
        out_dword(HWIO_TURING_MPU_CFG_AON_HYSTERESIS_ADDR,v)
#define HWIO_TURING_MPU_CFG_AON_HYSTERESIS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_MPU_CFG_AON_HYSTERESIS_ADDR,m,v,HWIO_TURING_MPU_CFG_AON_HYSTERESIS_IN)
#define HWIO_TURING_MPU_CFG_AON_HYSTERESIS_ACTIVE_HYSTSEL_BMSK                     0x7
#define HWIO_TURING_MPU_CFG_AON_HYSTERESIS_ACTIVE_HYSTSEL_SHFT                     0x0

#define HWIO_TURING_QOS_AHBS_AON_CGCR_ADDR                                  (TURING_TURING_TCSR_REG_BASE      + 0x0000b000)
#define HWIO_TURING_QOS_AHBS_AON_CGCR_OFFS                                  (TURING_TURING_TCSR_REG_BASE_OFFS + 0x0000b000)
#define HWIO_TURING_QOS_AHBS_AON_CGCR_RMSK                                         0x3
#define HWIO_TURING_QOS_AHBS_AON_CGCR_IN          \
        in_dword_masked(HWIO_TURING_QOS_AHBS_AON_CGCR_ADDR, HWIO_TURING_QOS_AHBS_AON_CGCR_RMSK)
#define HWIO_TURING_QOS_AHBS_AON_CGCR_INM(m)      \
        in_dword_masked(HWIO_TURING_QOS_AHBS_AON_CGCR_ADDR, m)
#define HWIO_TURING_QOS_AHBS_AON_CGCR_OUT(v)      \
        out_dword(HWIO_TURING_QOS_AHBS_AON_CGCR_ADDR,v)
#define HWIO_TURING_QOS_AHBS_AON_CGCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QOS_AHBS_AON_CGCR_ADDR,m,v,HWIO_TURING_QOS_AHBS_AON_CGCR_IN)
#define HWIO_TURING_QOS_AHBS_AON_CGCR_HW_CTL_BMSK                                  0x2
#define HWIO_TURING_QOS_AHBS_AON_CGCR_HW_CTL_SHFT                                  0x1
#define HWIO_TURING_QOS_AHBS_AON_CGCR_CLK_ENABLE_BMSK                              0x1
#define HWIO_TURING_QOS_AHBS_AON_CGCR_CLK_ENABLE_SHFT                              0x0

#define HWIO_TURING_QOS_AHBS_AON_HYSTERESIS_ADDR                            (TURING_TURING_TCSR_REG_BASE      + 0x0000b004)
#define HWIO_TURING_QOS_AHBS_AON_HYSTERESIS_OFFS                            (TURING_TURING_TCSR_REG_BASE_OFFS + 0x0000b004)
#define HWIO_TURING_QOS_AHBS_AON_HYSTERESIS_RMSK                                   0x7
#define HWIO_TURING_QOS_AHBS_AON_HYSTERESIS_IN          \
        in_dword_masked(HWIO_TURING_QOS_AHBS_AON_HYSTERESIS_ADDR, HWIO_TURING_QOS_AHBS_AON_HYSTERESIS_RMSK)
#define HWIO_TURING_QOS_AHBS_AON_HYSTERESIS_INM(m)      \
        in_dword_masked(HWIO_TURING_QOS_AHBS_AON_HYSTERESIS_ADDR, m)
#define HWIO_TURING_QOS_AHBS_AON_HYSTERESIS_OUT(v)      \
        out_dword(HWIO_TURING_QOS_AHBS_AON_HYSTERESIS_ADDR,v)
#define HWIO_TURING_QOS_AHBS_AON_HYSTERESIS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_QOS_AHBS_AON_HYSTERESIS_ADDR,m,v,HWIO_TURING_QOS_AHBS_AON_HYSTERESIS_IN)
#define HWIO_TURING_QOS_AHBS_AON_HYSTERESIS_ACTIVE_HYSTSEL_BMSK                    0x7
#define HWIO_TURING_QOS_AHBS_AON_HYSTERESIS_ACTIVE_HYSTSEL_SHFT                    0x0

#define HWIO_TURING_Q6_SMMU_DEBUG_ADDR                                      (TURING_TURING_TCSR_REG_BASE      + 0x0000c000)
#define HWIO_TURING_Q6_SMMU_DEBUG_OFFS                                      (TURING_TURING_TCSR_REG_BASE_OFFS + 0x0000c000)
#define HWIO_TURING_Q6_SMMU_DEBUG_RMSK                                             0xf
#define HWIO_TURING_Q6_SMMU_DEBUG_IN          \
        in_dword_masked(HWIO_TURING_Q6_SMMU_DEBUG_ADDR, HWIO_TURING_Q6_SMMU_DEBUG_RMSK)
#define HWIO_TURING_Q6_SMMU_DEBUG_INM(m)      \
        in_dword_masked(HWIO_TURING_Q6_SMMU_DEBUG_ADDR, m)
#define HWIO_TURING_Q6_SMMU_DEBUG_OUT(v)      \
        out_dword(HWIO_TURING_Q6_SMMU_DEBUG_ADDR,v)
#define HWIO_TURING_Q6_SMMU_DEBUG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_Q6_SMMU_DEBUG_ADDR,m,v,HWIO_TURING_Q6_SMMU_DEBUG_IN)
#define HWIO_TURING_Q6_SMMU_DEBUG_REQ_PRIORITY_BMSK                                0xc
#define HWIO_TURING_Q6_SMMU_DEBUG_REQ_PRIORITY_SHFT                                0x2
#define HWIO_TURING_Q6_SMMU_DEBUG_PRIORITY_LVL_BMSK                                0x3
#define HWIO_TURING_Q6_SMMU_DEBUG_PRIORITY_LVL_SHFT                                0x0

#define HWIO_TURING_TCSR_QOS_CTL_ADDR                                       (TURING_TURING_TCSR_REG_BASE      + 0x0000d000)
#define HWIO_TURING_TCSR_QOS_CTL_OFFS                                       (TURING_TURING_TCSR_REG_BASE_OFFS + 0x0000d000)
#define HWIO_TURING_TCSR_QOS_CTL_RMSK                                              0x1
#define HWIO_TURING_TCSR_QOS_CTL_IN          \
        in_dword_masked(HWIO_TURING_TCSR_QOS_CTL_ADDR, HWIO_TURING_TCSR_QOS_CTL_RMSK)
#define HWIO_TURING_TCSR_QOS_CTL_INM(m)      \
        in_dword_masked(HWIO_TURING_TCSR_QOS_CTL_ADDR, m)
#define HWIO_TURING_TCSR_QOS_CTL_OUT(v)      \
        out_dword(HWIO_TURING_TCSR_QOS_CTL_ADDR,v)
#define HWIO_TURING_TCSR_QOS_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TURING_TCSR_QOS_CTL_ADDR,m,v,HWIO_TURING_TCSR_QOS_CTL_IN)
#define HWIO_TURING_TCSR_QOS_CTL_QOS_ENABLE_BMSK                                   0x1
#define HWIO_TURING_TCSR_QOS_CTL_QOS_ENABLE_SHFT                                   0x0


#endif /* __QDSP_PM_CLOCKS_HWIO_660_CDSP_H__ */
