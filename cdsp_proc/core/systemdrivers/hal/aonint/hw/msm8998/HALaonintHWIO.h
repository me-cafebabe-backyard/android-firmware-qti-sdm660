#ifndef __HALAONINTHWIO_H__
#define __HALAONINTHWIO_H__
/*
===========================================================================
*/
/**
  @file HALaonintHWIO.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    MSM8998 (Nazgul) [nazgul_v1.0_p3q2r21.2]
 
  This file contains HWIO register definitions for the following modules:
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

  $Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/aonint/hw/msm8998/HALaonintHWIO.h#1 $
  $DateTime: 2020/02/10 01:57:30 $
  $Author: pwbldsvc $

  ===========================================================================
*/

#include "msmhwiobase.h"

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
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_0_TRIG_POS_PRE_TRIG_FVAL                       0x0
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_0_TRIG_POS_MID_TRIG_FVAL                       0x1
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_0_TRIG_POS_POST_TRIG_FVAL                      0x2
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
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_TRIG_SEL_TRIG_SEL0_FVAL                      0x0
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_TRIG_SEL_TRIG_SEL1_FVAL                      0x1
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_TRIG_SEL_TRIG_SEL2_FVAL                      0x2
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_TRIG_SEL_TRIG_SEL3_FVAL                      0x3
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_TRIG_SEL_TRIG_SEL4_FVAL                      0x4
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_TRIG_SEL_TRIG_SEL5_FVAL                      0x5
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_TRIG_SEL_TRIG_SEL6_FVAL                      0x6
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_TRIG_SEL_TRIG_SEL7_FVAL                      0x7
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_MODE_SEL_BMSK                               0x10
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_MODE_SEL_SHFT                                0x4
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_MODE_SEL_INTERRUPT_MODE_FVAL                 0x0
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_MODE_SEL_WATERMARK_MODE_FVAL                 0x1
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_VCO_FILTER_EN_BMSK                           0x8
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_VCO_FILTER_EN_SHFT                           0x3
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_VCO_POWER_SEL_BMSK                           0x4
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_VCO_POWER_SEL_SHFT                           0x2
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_SLOPE_DELTA_CYC_BMSK                         0x3
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_SLOPE_DELTA_CYC_SHFT                         0x0
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_4_FVAL        0x0
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_8_FVAL        0x1
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_12_FVAL        0x2
#define HWIO_SSC_SSC_VSENSE_SENSOR0_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_16_FVAL        0x3

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
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_0_TRIG_POS_PRE_TRIG_FVAL                       0x0
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_0_TRIG_POS_MID_TRIG_FVAL                       0x1
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_0_TRIG_POS_POST_TRIG_FVAL                      0x2
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
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_TRIG_SEL_TRIG_SEL0_FVAL                      0x0
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_TRIG_SEL_TRIG_SEL1_FVAL                      0x1
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_TRIG_SEL_TRIG_SEL2_FVAL                      0x2
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_TRIG_SEL_TRIG_SEL3_FVAL                      0x3
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_TRIG_SEL_TRIG_SEL4_FVAL                      0x4
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_TRIG_SEL_TRIG_SEL5_FVAL                      0x5
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_TRIG_SEL_TRIG_SEL6_FVAL                      0x6
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_TRIG_SEL_TRIG_SEL7_FVAL                      0x7
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_MODE_SEL_BMSK                               0x10
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_MODE_SEL_SHFT                                0x4
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_MODE_SEL_INTERRUPT_MODE_FVAL                 0x0
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_MODE_SEL_WATERMARK_MODE_FVAL                 0x1
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_VCO_FILTER_EN_BMSK                           0x8
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_VCO_FILTER_EN_SHFT                           0x3
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_VCO_POWER_SEL_BMSK                           0x4
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_VCO_POWER_SEL_SHFT                           0x2
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_SLOPE_DELTA_CYC_BMSK                         0x3
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_SLOPE_DELTA_CYC_SHFT                         0x0
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_4_FVAL        0x0
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_8_FVAL        0x1
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_12_FVAL        0x2
#define HWIO_SSC_SSC_VSENSE_SENSOR1_CONFIG_1_SLOPE_DELTA_CYC_SLOPE_DELTA_LATEST_N_LATEST_MINUS_16_FVAL        0x3

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


#endif /* __HALAONINTHWIO_H__ */
